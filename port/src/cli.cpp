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
 * -verbose writes the port's own diagnostic lines to codfh.log: the renderer's first untextured
 * draws ("untextured:"), a "frame N" line every 300 frames and the first sound plays
 * ("audio: play").
 *
 * -movie <file> plays a movie from SHELL\MOVIES (Credits.bik, Act_1.bik...) through the game's
 * player (sub_E8AC0, as the credits are played) when the menus first run.
 *
 * SP: -checkpoint <n> (or -cp <n>) starts the -map level at its checkpoint n (from 1, in the
 * order of cli_checkpoints.inc; 0 lists them in codfh.log). Nothing of a checkpoint goes into the
 * save: the scripts, on reaching one, set the restart's state live (SetCheckPointRegister,
 * SetDefaultClumpBank, SetStartingSections, SetRestartAnimGroup) and a death then only restarts
 * the level (bit 3 of dword_4B86F8; sub_D7410 runs sub_D6A50). So, once the level has run two
 * seconds (its master script has taken its level-start snapshot, which clears the register),
 * the checkpoint's calls are made as its script makes them and the level restarted as a death
 * restarts it. The scripts then see its register and GetNumberOfRestarts() == 1, and the restart
 * loads its sections, clump bank and animation groups. -cpvalue <v> gives the register where the
 * script computes it (the player's health on L_1_2); else the one the level set already, or 100.
 *
 * -leveldir <folder> loads the -map level's files from LEVELS\<folder> instead of its own
 * (sub_D7F40, the level-file path): a level folder under the data root's LEVELS, played as the
 * -map level is (its number, loading picture and save); its ANIMPACKS.TXT and SOUNDBANKS.TXT
 * name extra animation packs and sound banks to load.
 *
 * -autospawn (MP) spawns the local player as soon as the game lets it: the spawn button's own
 * calls (the fade, then the playing view, which respawns), made by the port while there is no
 * local soldier (port/src/debug/trigtools.cpp, AutoSpawnTick).
 */
#include <xtl.h>
#include <ctype.h>
#include <stdio.h>
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
#include "game/functions.h"
#include "types/CAnimPackSelector.h"
extern type_sp_AE5D0 *sp_dword_3B4724;
#endif

#include "port.h"

static char cli_map[64], cli_type[16], cli_name[64], cli_movie[64];
/* The -map argument (the debug tools' path graphs are saved by it). */
extern "C" const char *port_map_name;
extern "C" const char *port_map_name = cli_map;

/* -leveldir's folder, or NULL (src/recovered/unit_0D7F20.cpp, sub_D7F40). */
static char cli_level_dir[64];
extern "C" const char *port_level_dir;
extern "C" const char *port_level_dir = NULL;

/* -autospawn: the local player spawned as soon as the game lets it (port/src/debug/trigtools.cpp). */
extern "C" int port_autospawn;
extern "C" int port_autospawn = 0;

/* A -leveldir test level's extra animation packs, past the six its CAnimPackSelector loads: the
 * folder's ANIMPACKS.TXT, a pack's file name a line ("MPA_00Ger.ads"; '#' a comment), read
 * once; each loaded into a bank of its own after the six (src/recovered/unit_0A02D0.cpp's
 * CAnimBankInfo and unit_0A0A50.cpp's CAnimPackSelector). Its count; *pppNames their names. */
#define PORT_ANIM_PACKS 8
extern "C" int port_anim_packs(const char *const **pppNames)
{
    static char s_aszName[PORT_ANIM_PACKS][32];
    static const char *s_apszName[PORT_ANIM_PACKS];
    static int s_n = -1;

    if (s_n < 0)
    {
        char szPath[260], szLine[128];
        FILE *pFile;

        s_n = 0;
        if (port_level_dir)
        {
            _snprintf(szPath, sizeof(szPath), "LEVELS\\%s\\ANIMPACKS.TXT", port_level_dir);
            szPath[sizeof(szPath) - 1] = 0;
            pFile = fopen(szPath, "r");
            if (pFile)
            {
                while (s_n < PORT_ANIM_PACKS && fgets(szLine, sizeof(szLine), pFile))
                {
                    char *p = szLine, *e;

                    while (*p == ' ' || *p == '\t')
                        p++;
                    for (e = p + strlen(p); e > p && (unsigned char)e[-1] <= ' '; e--)
                        ;
                    *e = 0;
                    if (!*p || *p == '#')
                        continue;
                    strncpy(s_aszName[s_n], p, sizeof(s_aszName[s_n]) - 1);
                    s_apszName[s_n] = s_aszName[s_n];
                    plog("animation packs: extra pack %d (bank %d): %s", s_n, 6 + s_n, s_aszName[s_n]);
                    s_n++;
                }
                fclose(pFile);
            }
        }
        // (CODFH_ANIMPACKS: extra packs for any level, comma separated; the debug tools' AI
        // soldiers in multiplayer take single player's animations from them)
        if (s_n == 0)
        {
            char szEnv[512], *p;

            if (GetEnvironmentVariableA("CODFH_ANIMPACKS", szEnv, sizeof(szEnv)))
                for (p = strtok(szEnv, ", "); p && s_n < PORT_ANIM_PACKS; p = strtok(NULL, ", "))
                {
                    strncpy(s_aszName[s_n], p, sizeof(s_aszName[s_n]) - 1);
                    s_apszName[s_n] = s_aszName[s_n];
                    plog("animation packs: extra pack %d (bank %d): %s (CODFH_ANIMPACKS)", s_n, 6 + s_n, s_aszName[s_n]);
                    s_n++;
                }
        }
    }
    *pppNames = s_apszName;
    return s_n;
}

/* A -leveldir test level's extra sound banks, past the five (and the random one) its
 * CSoundBankSelector loads: the folder's SOUNDBANKS.TXT, a bank a line, its id's two words in hex
 * and its number ("A6FA4330 750E091F 221": SB_AWD/SB_AGD's XBX_0221; '#' a comment), read once;
 * each loaded into a slot of its own after the six (include/types/soundbank.h's SOUND_BANK_SLOTS,
 * src/recovered/unit_0B9110.cpp's sub_B9800). Its count, at most nMax copied out. */
#define PORT_SOUND_BANKS 8
extern "C" int port_sound_banks(unsigned *pKeys, int *pBanks, int nMax)
{
    static unsigned s_auKey[PORT_SOUND_BANKS][2];
    static int s_anBank[PORT_SOUND_BANKS];
    static int s_n = -1;
    int i;

    if (s_n < 0)
    {
        char szPath[260], szLine[128];
        FILE *pFile;

        s_n = 0;
        if (port_level_dir)
        {
            _snprintf(szPath, sizeof(szPath), "LEVELS\\%s\\SOUNDBANKS.TXT", port_level_dir);
            szPath[sizeof(szPath) - 1] = 0;
            pFile = fopen(szPath, "r");
            if (pFile)
            {
                while (s_n < PORT_SOUND_BANKS && fgets(szLine, sizeof(szLine), pFile))
                {
                    if (szLine[0] == '#'
                        || sscanf(szLine, "%x %x %d", &s_auKey[s_n][0], &s_auKey[s_n][1], &s_anBank[s_n]) != 3)
                        continue;
                    plog("sound banks: extra bank %d (slot %d): %08X,%08X, XBX_%04d", s_n, 6 + s_n,
                         s_auKey[s_n][0], s_auKey[s_n][1], s_anBank[s_n]);
                    s_n++;
                }
                fclose(pFile);
            }
        }
    }
    for (i = 0; i < s_n && i < nMax; i++)
    {
        pKeys[i * 2] = s_auKey[i][0];
        pKeys[i * 2 + 1] = s_auKey[i][1];
        pBanks[i] = s_anBank[i];
    }
    return s_n < nMax ? s_n : nMax;
}

static int cli_pending;
#ifdef CODFH_SP
static int cli_auto_main_menu_phase;
static int cli_checkpoint = -1, cli_checkpoint_level, cli_checkpoint_value = -1;

/* The levels' checkpoints (generated from their scripts). */
#define CLI_CP_UNKNOWN 0x7FFFFFFF
struct cli_checkpoint_anim
{
    RwInt32 slot;
    RwUInt32 a, b;
};
struct cli_checkpoint_entry
{
    const char *level;
    RwInt32 reg, clump, sections[4], anims;
    cli_checkpoint_anim anim[6];
    const char *script;
};
static const cli_checkpoint_entry cli_checkpoints[] = {
#include "cli_checkpoints.inc"
};
#endif

extern "C" int port_log_verbose;   /* (xpal_core.cpp: -verbose, the diagnostics' lines) */

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
        else if (!_stricmp(argv[i], "-verbose"))
            port_log_verbose = 1;
        else if (!_stricmp(argv[i], "-autospawn"))
            port_autospawn = 1;
        else if (!_stricmp(argv[i], "-leveldir") && i + 1 < argc)
        {
            strncpy(cli_level_dir, argv[++i], sizeof(cli_level_dir) - 1);
            port_level_dir = cli_level_dir;
        }
#ifdef CODFH_SP
        else if (!_stricmp(argv[i], "-main-menu"))
            cli_auto_main_menu_phase = 1;
        else if (!_stricmp(argv[i], "-no-main-menu"))
            cli_auto_main_menu_phase = 0;
        else if ((!_stricmp(argv[i], "-checkpoint") || !_stricmp(argv[i], "-cp")) && i + 1 < argc)
            cli_checkpoint = atoi(argv[++i]);
        else if (!_stricmp(argv[i], "-cpvalue") && i + 1 < argc)
            cli_checkpoint_value = atoi(argv[++i]);
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
#ifdef CODFH_SP
    if (cli_checkpoint >= 0 && !cli_pending)
    {
        plog("command line: -checkpoint needs -map; ignored");
        cli_checkpoint = -1;
    }
    else if (cli_checkpoint >= 0)
        plog("command line: checkpoint %d", cli_checkpoint);
#endif
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

#ifdef CODFH_SP
/* -checkpoint: the command-line level restarted at its checkpoint n, two seconds after it is up. */
static void checkpoint_frame(void)
{
    static unsigned running;
    if (cli_checkpoint < 0 || !cli_checkpoint_level)
        return;
    if (!dword_4B8710 || !dword_4E5C74 || sub_19B050() != cli_checkpoint_level || (dword_4B86F8 & 0x3A))
    {
        running = 0;
        return;
    }
    if (++running < 120)
        return;

    const char *name = sub_19B060(cli_checkpoint_level);
    const cli_checkpoint_entry *cp = NULL;
    int n = 0;
    plog("command line: %s's checkpoints:", name);
    for (int i = 0; i < (int)(sizeof(cli_checkpoints) / sizeof(cli_checkpoints[0])); i++)
    {
        const cli_checkpoint_entry *e = &cli_checkpoints[i];
        if (_stricmp(e->level, name))
            continue;
        n++;
        if (e->reg == CLI_CP_UNKNOWN)
            plog("  %d: register (computed), clump bank %d, sections %d %d %d %d, %d animation groups (%s)", n,
                 e->clump, e->sections[0], e->sections[1], e->sections[2], e->sections[3], e->anims, e->script);
        else
            plog("  %d: register %d, clump bank %d, sections %d %d %d %d, %d animation groups (%s)", n, e->reg,
                 e->clump, e->sections[0], e->sections[1], e->sections[2], e->sections[3], e->anims, e->script);
        if (n == cli_checkpoint)
            cp = e;
    }
    int wanted = cli_checkpoint;
    cli_checkpoint = -1;
    if (!cp)
    {
        if (wanted)
            plog("command line: %s has no checkpoint %d (%d found); not restarting", name, wanted, n);
        return;
    }

    /* the checkpoint's calls, as its script makes them */
    RwInt32 reg = cp->reg;
    if (reg == CLI_CP_UNKNOWN)
        reg = cli_checkpoint_value >= 0 ? cli_checkpoint_value : dword_4B8780 ? dword_4B8780 : 100;
    else if (cli_checkpoint_value >= 0)
        reg = cli_checkpoint_value;
    dword_4B8780 = reg;                         /* SetCheckPointRegister */
    if (cp->clump >= 0)
        dword_429EA8 = cp->clump;               /* SetDefaultClumpBank */
    if (cp->sections[0] >= 0)
    {
        RwInt32 sections[4] = {cp->sections[0], cp->sections[1], cp->sections[2], cp->sections[3]};
        sub_1727E0(sections);                   /* SetStartingSections */
    }
    for (int i = 0; i < cp->anims && dword_4B67CC; i++)
    {
        type_3DF8D8_04 key(cp->anim[i].a, cp->anim[i].b);
        dword_4B67CC->sub_A1130(cp->anim[i].slot - 1, &key);   /* SetRestartAnimGroup */
    }
    plog("command line: restarting %s at checkpoint %d: register %d, clump bank %d, sections %d %d %d %d, "
         "%d animation groups (%d restarts so far)", name, wanted, reg, dword_429EA8, cp->sections[0],
         cp->sections[1], cp->sections[2], cp->sections[3], cp->anims, dword_4B8720);
    /* the restart, as a death's fade ends it (sub_150B00) */
    dword_4B86F8 |= 8;
}
#endif

extern "C" void port_cli_present(void)
{
#ifdef CODFH_DEDICATED
    dedicated_frame();
#endif
#ifdef CODFH_SP
    checkpoint_frame();
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
    cli_checkpoint_level = level;
    sub_D8CC0(level);
    /* The SP front end owns a blocking frame loop. Leave it so the shared
       game-loop fade callback can finish and consume the level change. */
    sp_dword_3B4724->unk_04 = true;
#endif
}
