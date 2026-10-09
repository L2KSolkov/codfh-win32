/*
 * Command-line level loading for the port: codfh.exe -map <name|number>
 * The SP front end also accepts -main-menu to skip Press Start and select the first saved
 * profile, or -no-main-menu to keep the normal title flow.
 * (MP additionally accepts -gametype DM|TDM|CTF|SD|SUP and -name <session name>).
 * [-name <session name>] hosts a System Link game on that level as soon as the front end's menus
 * are up, as the create-match page's Start Session does (type_2053C0::sub_205A40): the settings
 * copy's game type and level, the server name, startServer, then the menus closed.
 *
 * The level is matched by number (the level list's index) or by a case-insensitive part of its
 * name; the list is written to codfh.log the first time the menus run.
 *
 * The dedicated server (CODFH_DEDICATED) always hosts: the first level when no -map is given,
 * as "Dedicated server" when no -name is. Its own player never plays: once a level is up, the
 * server starts the round itself (what the host's press at the weapon selection does,
 * type_4F7EB8::sub_1AADF0: the rules' "waiting for host" word cleared, dword_4FB9E0.sub_1B6EF0),
 * without spawning.
 *
 * -movie <file> plays a movie from SHELL\MOVIES (Credits.bik, Act_1.bik...) through the game's
 * player (sub_E8AC0, as the credits are played) when the menus first run.
 */
#include <xtl.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "game/uiglue.h"
#include "game/livemenu.h"
#include "game/ingamemenu.h"
#include "game/gameloop.h"
#include "game/data.h"
#include "game/mpgame.h"
#include "game/parsedfile.h"
#ifdef CODFH_SP
#include "sp/sp_fend.h"
extern type_sp_AE5D0 *sp_dword_3B4724;
#endif

#include "port.h"

static char cli_map[64], cli_type[16], cli_name[64], cli_movie[64];
static int cli_pending;
#ifdef CODFH_SP
static int cli_auto_main_menu_phase;
#endif

/* Reads the options from the command line (WinMain). */
extern "C" void port_cli_parse(const char *cmd)
{
    char buf[1024];
    strncpy(buf, cmd ? cmd : "", sizeof(buf) - 1);
    buf[sizeof(buf) - 1] = 0;
    char *argv[32];
    int argc = 0;
    for (char *p = buf; *p && argc < 32;)
    {
        while (*p == ' ')
            p++;
        if (!*p)
            break;
        if (*p == '"')
        {
            argv[argc++] = ++p;
            while (*p && *p != '"')
                p++;
        }
        else
        {
            argv[argc++] = p;
            while (*p && *p != ' ')
                p++;
        }
        if (*p)
            *p++ = 0;
    }
    for (int i = 0; i < argc; i++)
    {
        if (!_stricmp(argv[i], "-map") && i + 1 < argc)
            strncpy(cli_map, argv[++i], sizeof(cli_map) - 1);
        else if (!_stricmp(argv[i], "-gametype") && i + 1 < argc)
            strncpy(cli_type, argv[++i], sizeof(cli_type) - 1);
        else if (!_stricmp(argv[i], "-name") && i + 1 < argc)
            strncpy(cli_name, argv[++i], sizeof(cli_name) - 1);
        else if (!_stricmp(argv[i], "-movie") && i + 1 < argc)
            strncpy(cli_movie, argv[++i], sizeof(cli_movie) - 1);
#ifdef CODFH_SP
        else if (!_stricmp(argv[i], "-main-menu"))
            cli_auto_main_menu_phase = 1;
        else if (!_stricmp(argv[i], "-no-main-menu"))
            cli_auto_main_menu_phase = 0;
#endif
    }
#ifdef CODFH_DEDICATED
    if (!cli_map[0])
        strcpy(cli_map, "0");
    if (!cli_name[0])
        strcpy(cli_name, "Dedicated server");
#endif
    cli_pending = cli_map[0] != 0;
#ifdef CODFH_SP
    /* Direct level startup takes precedence when both options are present. */
    if (cli_pending)
        cli_auto_main_menu_phase = 0;
    if (cli_auto_main_menu_phase)
        plog("command line: skip Press Start and select the first saved profile");
#endif
    if (cli_pending)
        plog("command line: map %s, game type %s, session %s", cli_map, cli_type[0] ? cli_type : "DM",
             cli_name[0] ? cli_name : "(default)");
}

#ifdef CODFH_SP
/* The SP front end consumes these in its normal menu and profile-selection callbacks. */
extern "C" int port_cli_auto_main_menu_start(void)
{
    if (cli_auto_main_menu_phase != 1)
        return 0;
    cli_auto_main_menu_phase = 2;
    return 1;
}

extern "C" int port_cli_auto_main_menu_profile_pending(void)
{
    return cli_auto_main_menu_phase == 2;
}

extern "C" void port_cli_auto_main_menu_finish(int slot)
{
    if (cli_auto_main_menu_phase != 2)
        return;
    cli_auto_main_menu_phase = 0;
    if (slot >= 0)
        plog("command line: selecting profile slot %d", slot + 1);
    else
        plog("command line: no saved profile found; leaving profile selection open");
}
#endif

static int game_type_bits(const char *t)
{
    static const char *const names[5] = {"DM", "TDM", "CTF", "SD", "SUP"};
    for (int i = 0; i < 5; i++)
        if (!_stricmp(t, names[i]))
            return 1 << i;
    return 1;
}

static int contains_nocase(const char *hay, const char *needle)
{
    size_t n = strlen(needle);
    for (; *hay; hay++)
        if (!_strnicmp(hay, needle, n))
            return 1;
    return 0;
}

#ifdef CODFH_SP
/* The SP command uses the campaign list's zero-based index; names are the
   game's L_1_1, L_1_1_B, ... identifiers from sub_19B060. */
static int sp_map_level(const char *map)
{
    char *end;
    long index = strtol(map, &end, 10);
    if (*map && !*end)
        return index >= 0 && index < 38 ? (int)index + 1 : -1;

    for (int level = 1; level <= 38; level++)
    {
        const char *name = sub_19B060(level);
        if (name && contains_nocase(name, map))
            return level;
    }
    return -1;
}
#endif

/* Run after each frame is presented: -movie once the game has a camera (a level is loaded; the
   movie player draws through it), outside the movie's own frames. */
#ifdef CODFH_DEDICATED
/* The server's own frame: each new round started for the clients (twice a second while a level is
   up; the rules ask again after a level change), and a heartbeat in the log. */
static void dedicated_frame(void)
{
    static unsigned last_round;
    if (port_frame % 30)
        return;
    /* (the rules' word as the HUD reads it: through the validator its getter folded into) */
    if (dword_4E5C74 && ((kujuUI::cScopeValidator *)&dword_4FB9E0)->sub_1CA260() && !unk_4F61F8.unk_104)
    {
        dword_4FB9E0.sub_1B6EF0(0);
        plog("dedicated server: round started (frame %u)", port_frame);
        last_round = port_frame;
    }
    if (port_frame % (60 * 60) == 0)
        plog("dedicated server: running, frame %u, %s", port_frame, dword_4E5C74 ? "in a level" : "between levels");
}
#endif

extern "C" void port_cli_present(void)
{
#ifdef CODFH_DEDICATED
    dedicated_frame();
#endif
    static int playing;
    if (cli_movie[0] && dword_4E5C74 && port_frame > 30 && !playing)
    {
        playing = 1;
        plog("command line: movie %s", cli_movie);
        char name[64];
        strcpy(name, cli_movie);
        cli_movie[0] = 0;
        sub_E8AC0(name, dword_4E5C74, 1, 0);
        plog("command line: movie %s ended", name);
        playing = 0;
    }
}

extern "C" unsigned port_menu_frame;
extern "C" void port_menu_mouse_frame(void);

/* Run once a frame by the menus' loop (InGameMenuManager::sub_1FBE70). */
extern "C" void port_cli_frame(void)
{
    /* (the menus are up: the mouse points at their items, menumouse.cpp) */
    port_menu_frame = port_frame ? port_frame : 1;
    port_menu_mouse_frame();
    /* a player with no profile (a new install has none) plays under the configured name, not
       an empty one */
    if (dword_4F28F0 && !dword_4F28F0->unk_183[0])
    {
        set_4F28F0_unk_183(port_config.playerName);
        plog("player name: %s", port_config.playerName);
    }
#ifndef CODFH_SP
    if (!cli_pending || !dword_4FD974 || !dword_4FD970)
        return;
    cli_pending = 0;
    plog("levels (%u):", dword_4FD970);
    for (RwUInt32 i = 0; i < dword_4FD970; i++)
        plog("  %2u %s (game types 0x%X)", i, dword_4FD974[i].unk_04.c_str(), dword_4FD974[i].unk_3C);

    int level = -1;
    char *end;
    long n = strtol(cli_map, &end, 10);
    if (!*end && n >= 0 && (RwUInt32)n < dword_4FD970)
        level = (int)n;
    for (RwUInt32 i = 0; level < 0 && i < dword_4FD970; i++)
        if (contains_nocase(dword_4FD974[i].unk_04.c_str(), cli_map))
            level = (int)i;
    if (level < 0)
    {
        plog("command line: no level matches \"%s\"", cli_map);
        return;
    }
    int type = game_type_bits(cli_type[0] ? cli_type : "DM");
    if (!(dword_4FD974[level].unk_3C & type))
        plog("command line: %s does not list game type %s (0x%X); hosting it anyway",
             dword_4FD974[level].unk_04.c_str(), cli_type, dword_4FD974[level].unk_3C);
    plog("command line: hosting %s (%d), game type 0x%X", dword_4FD974[level].unk_04.c_str(), level, type);

    unk_4FDBB0.unk_00 = type;
    unk_4FDBB0.unk_28 = level;
    sub_1C4300(cli_name[0] ? cli_name : "PC host");
    startServer(false);
    dword_42D28C = 3;
    sub_1FC310()->sub_1FBE20();
#else
    if (!cli_pending || !dword_4F28F0 || !sp_dword_3B4724)
        return;

    cli_pending = 0;
    plog("SP campaign levels (index: name):");
    for (RwInt32 i = 0; i < 38; i++)
        plog("  %2d: %s", i, sub_19B060(i + 1));

    int level = sp_map_level(cli_map);
    if (level < 0)
    {
        plog("command line: no SP level matches \"%s\"", cli_map);
        return;
    }
    plog("command line: starting SP level %s (index %d, game level %d)",
         sub_19B060(level), level - 1, level);
    sub_D8CC0(level);
    /* The SP front end owns a blocking frame loop. Leave it so the shared
       game-loop fade callback can finish and consume the level change. */
    sp_dword_3B4724->unk_04 = true;
#endif
}
