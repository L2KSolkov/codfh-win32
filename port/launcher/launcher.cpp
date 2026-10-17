/*
 * codfh_launcher.exe: the port's command line and environment options in one window, built
 * beside codfh.exe by tools/portbuild.py (build/port_sp, build/port) and launching the codfh.exe
 * in its own folder, from that folder. Its settings are kept in codfh_launcher.ini beside it.
 *
 * Every option is a row of g_aOpt, on one of four tabs: the command line port/src/cli.cpp reads
 * (-map, -checkpoint, -cpvalue, -main-menu, -no-main-menu, -movie, -gametype, -name, -verbose) and
 * every CODFH_ variable the port reads (port/src: the data root, the console, the overlay, the
 * live link, System Link between instances, crash dumps; the debug tools' views at start; the
 * renderer's switches; the logs, captures and scripted input). A field takes any other argument,
 * NAME=value lines any other variable. A variable left off is taken out of the game's
 * environment (most are read as set or not, whatever their value).
 *
 * The inputs are checked as they change (Validate), against what the game takes: a level it has,
 * a checkpoint that level has, a movie in the data root, numbers where numbers go, the scripted
 * input's buttons and the menu clicks' points, the options of the build beside the launcher (SP
 * or MP, every-section loading or not). Errors are listed under the command line and stop the
 * launch; warnings (an option the game will ignore) are listed but do not.
 */
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <commctrl.h>
#include <shlobj.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>

// The single player's levels -map takes by number: the campaign table's index from 0 (cli.cpp's
// sp_map_level: n is unit_19AAB0.cpp's sub_19B060(n + 1)), only those COD.PAK has. The table's
// other names (L_1_1_C, L_1_2_C, L_1_3_C, L_1_4, L_1_5_C, L_2_1_C, L_2_2_C, L_2_3 to L_2_6,
// L_3_2 to L_3_2_C, L_3_3_B, L_3_3_C, L_3_4_B, L_3_4_C) have no files; L_3_4 has no GODDATA.DFF
// and the campaign skips it. Each with its title, the front end's (SHELL\FEND\FEND.CSV, $1_1a
// for L_1_1 and on: English). (The multiplayer levels' names are MP_1 and the rest: GLOBAL.LOC
// has no other English names for them.)
static const struct { int n; const char *name, *title; } g_aSpLevel[] = {
    {0, "L_1_1", "Not One Step Back"}, {1, "L_1_1_B", "The Flag Must Fall"}, {3, "L_1_2", "Dead in Her Sights"},
    {4, "L_1_2_B", "Defend the Factory"}, {6, "L_1_3_A", "Breakdown"}, {7, "L_1_3_B", "Into Red Square"},
    {10, "L_1_5", "Op. Little Saturn"}, {11, "L_1_5_B", "Airfield Ambush"}, {13, "L_2_1", "Mission: Matmata"},
    {14, "L_2_1_B", "Depot Saboteurs"}, {16, "L_2_2", "A Desert Ride"}, {17, "L_2_2_B", "Raiding the Fortress"},
    {23, "L_3_1", "First City to Fall"}, {24, "L_3_1_B", "Underground Passage"}, {25, "L_3_1_C", "Surrender at Aachen"},
    {29, "L_3_3", "Come Out Fighting"}, {35, "L_3_5", "Road to Remagen"}, {36, "L_3_5_B", "Last Bridge Standing"},
    {37, "L_3_5_C", "Into the Heartland"},
};

// The whole campaign table (sub_19B060(1) to (38)), for -map's name match as cli.cpp makes it (the
// first level whose name holds the text), and the levels' checkpoints (cli_checkpoints.inc: 1 to
// n each; the others have none).
static const char *const g_apszSpTable[38] = {
    "L_1_1", "L_1_1_B", "L_1_1_C", "L_1_2", "L_1_2_B", "L_1_2_C", "L_1_3_A", "L_1_3_B", "L_1_3_C", "L_1_4",
    "L_1_5", "L_1_5_B", "L_1_5_C", "L_2_1", "L_2_1_B", "L_2_1_C", "L_2_2", "L_2_2_B", "L_2_2_C", "L_2_3",
    "L_2_4", "L_2_5", "L_2_6", "L_3_1", "L_3_1_B", "L_3_1_C", "L_3_2", "L_3_2_B", "L_3_2_C", "L_3_3",
    "L_3_3_B", "L_3_3_C", "L_3_4", "L_3_4_B", "L_3_4_C", "L_3_5", "L_3_5_B", "L_3_5_C",
};
static const struct { const char *name; int n; } g_aCheckpoints[] = {
    {"L_1_1", 1}, {"L_1_1_B", 1}, {"L_1_2", 1}, {"L_1_3_B", 1}, {"L_1_5_B", 1}, {"L_2_1", 1},
    {"L_3_1", 1}, {"L_3_1_B", 1}, {"L_3_1_C", 1}, {"L_3_3", 2}, {"L_3_5", 1}, {"L_3_5_B", 1},
};
// The buttons CODFH_INPUT presses (xpal_sys.cpp's scripted input).
static const char *const g_apszButton[] = {
    "A", "B", "X", "Y", "BLACK", "WHITE", "LT", "RT", "START", "BACK", "UP", "DOWN", "LEFT", "RIGHT",
    "LUP", "LDOWN", "LLEFT", "LRIGHT", "MUP", "MDOWN", "MLEFT", "MRIGHT",
};
// The options cli.cpp reads, for "other arguments" (and how many words each takes).
static const struct { const char *name; int args; } g_aKnownArg[] = {
    {"-map", 1}, {"-gametype", 1}, {"-name", 1}, {"-movie", 1}, {"-verbose", 0}, {"-main-menu", 0},
    {"-no-main-menu", 0}, {"-checkpoint", 1}, {"-cp", 1}, {"-cpvalue", 1},
};

enum Page { P_GAME, P_VIEWS, P_RENDER, P_LOGS, P_COUNT };
static const char *const g_apszPage[P_COUNT] = {"Game", "Debug views", "Renderer", "Logs and capture"};

enum Kind
{
    K_ARG,      // -name <text>
    K_ARGFLAG,  // -name when checked
    K_ARGLIST,  // a choice: its first word after -name (or itself, a flag, without a name)
    K_ENV,      // NAME=<text>
    K_ENVFLAG,  // NAME=<choices, or 1> when checked; taken out when not
    K_ENVLIST,  // NAME=<the choice's first word>; the first choice takes it out
};
enum
{
    F_WIDE = 1,     // a field across the whole row
    F_MAP = 2,      // the levels' list
    F_MOVIE = 4,    // SHELL\MOVIES's files
    F_BROWSE = 8,   // a folder browser beside it
    F_OFF0 = 16,    // K_ENVFLAG: 0 when not checked (not taken out)
    F_UINT = 32,    // a number from 0 (digits only)
    F_INT = 64,     // a number, negative too
    F_SP = 128,     // single player's only
    F_MP = 256,     // multiplayer's only
};

struct Opt
{
    int page;
    Kind kind;
    const char *name;
    const char *label;
    const char *choices;
    int flags;
};

static const Opt g_aOpt[] = {
    // ---- the command line (port/src/cli.cpp) ----
    {P_GAME, K_ARG, "-map", "Level (-map)", NULL, F_MAP},
    {P_GAME, K_ARG, "-movie", "Movie (-movie)", NULL, F_MOVIE},
    {P_GAME, K_ARG, "-checkpoint", "Checkpoint (SP, 0 lists)", NULL, F_UINT | F_SP},
    {P_GAME, K_ARG, "-cpvalue", "Checkpoint register (SP)", NULL, F_INT | F_SP},
    {P_GAME, K_ARGLIST, "", "Front end (SP)", "default|-main-menu (no title)|-no-main-menu", F_SP},
    {P_GAME, K_ARGLIST, "-gametype", "Game type (MP)", "default|DM|TDM|CTF|SD|SUP", F_MP},
    {P_GAME, K_ARG, "-name", "Host as (MP, -name)", NULL, F_MP},
    {P_GAME, K_ENVLIST, "CODFH_NETLOOP", "Link instance (MP)", "off|1|2|3|4", F_MP},
    {P_GAME, K_ENV, "CODFH_LIVE", "Live link (1, or a port)", NULL, 0},
    {P_GAME, K_ENVLIST, "CODFH_CRASHDUMP", "Crash dump", "default (small)|0 (none)|2 (full memory)", 0},
    {P_GAME, K_ENV, "CODFH_CRASHTEST", "Crash test after (s)", NULL, F_UINT},
    {P_GAME, K_ENV, "CODFH_DATA", "Data root (CODFH_DATA)", NULL, F_WIDE | F_BROWSE},
    {P_GAME, K_ARGFLAG, "-verbose", "Port diagnostics in the log (-verbose)", NULL, 0},
    {P_GAME, K_ENVFLAG, "CODFH_CONSOLE", "Console window (CONSOLE)", NULL, F_OFF0},
    {P_GAME, K_ENVFLAG, "CODFH_OVERLAY", "Overlay shown at start (OVERLAY, F1)", NULL, 0},
    {P_GAME, K_ENVFLAG, "CODFH_INPUTCACHE", "Input polled live (INPUTCACHE=0)", "0", 0},

    // ---- the debug tools' views, on from the start (port/src/debug) ----
    {P_VIEWS, K_ENVLIST, "CODFH_TRIGGERS", "Triggers (TRIGGERS)", "off|1|2 (with the collision)", 0},
    {P_VIEWS, K_ENVLIST, "CODFH_AI", "AI (AI)", "off|1 (state and notes)|2 (with cover and fighting)", 0},
    {P_VIEWS, K_ENVLIST, "CODFH_MODELS", "Models coloured (MODELS)", "off|1 (by section)|2 (skip flags)|3 (by owner)", 0},
    {P_VIEWS, K_ENVFLAG, "CODFH_FREECAM", "Free camera (FREECAM)", NULL, 0},
    {P_VIEWS, K_ENVFLAG, "CODFH_PATHNODES", "Path nodes (PATHNODES)", NULL, 0},
    {P_VIEWS, K_ENVFLAG, "CODFH_PG", "Projectile generators (PG)", NULL, 0},
    {P_VIEWS, K_ENVFLAG, "CODFH_PROJECTILES", "Projectiles (PROJECTILES)", NULL, 0},
    {P_VIEWS, K_ENVFLAG, "CODFH_RAYS", "Line tests (RAYS)", NULL, 0},
    {P_VIEWS, K_ENVFLAG, "CODFH_HITS", "Hits and bone boxes (HITS)", NULL, 0},
    {P_VIEWS, K_ENVFLAG, "CODFH_SOUNDS", "Sounds playing (SOUNDS)", NULL, 0},
    {P_VIEWS, K_ENVFLAG, "CODFH_HEARING", "Hearing (HEARING)", NULL, 0},
    {P_VIEWS, K_ENVFLAG, "CODFH_LIGHTS", "Lights (LIGHTS)", NULL, 0},
    {P_VIEWS, K_ENVFLAG, "CODFH_SPLINES", "Splines (SPLINES)", NULL, 0},
    {P_VIEWS, K_ENVFLAG, "CODFH_ZONES", "Lighting zones (ZONES)", NULL, 0},
    {P_VIEWS, K_ENVFLAG, "CODFH_SQUADS", "Squads (SQUADS)", NULL, 0},
    {P_VIEWS, K_ENVFLAG, "CODFH_GIMPS", "Gimps (GIMPS)", NULL, 0},
    {P_VIEWS, K_ENVFLAG, "CODFH_SHRIMPS", "Shrimps (SHRIMPS)", NULL, 0},
    {P_VIEWS, K_ENVFLAG, "CODFH_MOUNTS", "Mount points (MOUNTS)", NULL, 0},
    {P_VIEWS, K_ENVFLAG, "CODFH_SKELETONS", "Skeletons (SKELETONS)", NULL, 0},
    {P_VIEWS, K_ENVFLAG, "CODFH_INSPECT", "Inspector (INSPECT)", NULL, 0},
    {P_VIEWS, K_ENVFLAG, "CODFH_ALLSECTIONS", "Every section at once (ALLSECTIONS)", NULL, 0},

    // ---- the renderer's switches (port/src/d3d) ----
    {P_RENDER, K_ENVFLAG, "CODFH_WIREFRAME", "Wireframe (WIREFRAME)", NULL, 0},
    {P_RENDER, K_ENVFLAG, "CODFH_NODEPTH", "No depth test (NODEPTH)", NULL, 0},
    {P_RENDER, K_ENVFLAG, "CODFH_NOCULL", "No culling (NOCULL)", NULL, 0},
    {P_RENDER, K_ENVFLAG, "CODFH_NOFOG", "No fog (NOFOG)", NULL, 0},
    {P_RENDER, K_ENVFLAG, "CODFH_FULLBRIGHT", "Full bright (FULLBRIGHT)", NULL, 0},
    {P_RENDER, K_ENVFLAG, "CODFH_LIGHTINGONLY", "Lighting only (LIGHTINGONLY)", NULL, 0},
    {P_RENDER, K_ENVFLAG, "CODFH_NOALPHATEST", "No alpha test (NOALPHATEST)", NULL, 0},
    {P_RENDER, K_ENVFLAG, "CODFH_NOBLEND", "No blending (NOBLEND)", NULL, 0},
    {P_RENDER, K_ENVFLAG, "CODFH_POINTFILTER", "Point filtering (POINTFILTER)", NULL, 0},
    {P_RENDER, K_ENVFLAG, "CODFH_HIDEPARTICLES", "Hide particles (HIDEPARTICLES)", NULL, 0},
    {P_RENDER, K_ENVFLAG, "CODFH_HIDE2D", "Hide 2D (HIDE2D)", NULL, 0},
    {P_RENDER, K_ENVFLAG, "CODFH_NOGAMMA", "No gamma (NOGAMMA)", NULL, 0},
    {P_RENDER, K_ENVFLAG, "CODFH_NOVBCACHE", "No vertex cache (NOVBCACHE)", NULL, 0},
    {P_RENDER, K_ENVFLAG, "CODFH_QUADTEX", "Particles' texture alone (QUADTEX)", NULL, 0},

    // ---- logs, captures and scripted input ----
    {P_LOGS, K_ENV, "CODFH_TRACE", "Render log frame (TRACE)", NULL, F_UINT},
    {P_LOGS, K_ENV, "CODFH_DRAWID", "Draw ids from (DRAWID)", NULL, F_UINT},
    {P_LOGS, K_ENV, "CODFH_DRAWID_TO", "To frame (DRAWID_TO)", NULL, F_UINT},
    {P_LOGS, K_ENV, "CODFH_DRAWDETAIL", "Detail (DRAWDETAIL)", NULL, F_UINT},
    {P_LOGS, K_ENV, "CODFH_SHOT", "Screenshot frame (SHOT)", NULL, F_UINT},
    {P_LOGS, K_ENV, "CODFH_SHOT_EVERY", "Every n (SHOT_EVERY)", NULL, F_UINT},
    {P_LOGS, K_ENV, "CODFH_SHOT_FROM", "From (SHOT_FROM)", NULL, F_UINT},
    {P_LOGS, K_ENV, "CODFH_SHOT_TO", "To (SHOT_TO)", NULL, F_UINT},
    {P_LOGS, K_ENV, "CODFH_SPDUMP", "Menu dump from (SP)", NULL, F_UINT | F_SP},
    {P_LOGS, K_ENV, "CODFH_WAV", "Record the sound to (WAV)", NULL, F_WIDE},
    {P_LOGS, K_ENV, "CODFH_INPUT", "Pad presses (frame:button,...)", NULL, F_WIDE},
    {P_LOGS, K_ENV, "CODFH_SPMOUSE", "Menu clicks (SP, frame:x:y[:c],...)", NULL, F_WIDE | F_SP},
    {P_LOGS, K_ENVFLAG, "CODFH_STATS", "Draw statistics (STATS)", NULL, 0},
    {P_LOGS, K_ENVFLAG, "CODFH_PROFILE", "Slow-frame profiler (PROFILE)", NULL, 0},
    {P_LOGS, K_ENVFLAG, "CODFH_ASTARLOG", "Path finding (ASTARLOG)", NULL, 0},
    {P_LOGS, K_ENVFLAG, "CODFH_AUDIOTRACE", "Every sound play (AUDIOTRACE)", NULL, 0},
    {P_LOGS, K_ENVFLAG, "CODFH_FONTTRACE", "Font draws (FONTTRACE)", NULL, 0},
    {P_LOGS, K_ENVFLAG, "CODFH_MSGS", "Messages recorded (MSGS)", NULL, 0},
    {P_LOGS, K_ENVFLAG, "CODFH_RNG", "Random numbers recorded (RNG)", NULL, 0},
    {P_LOGS, K_ENVFLAG, "CODFH_FRAMES", "Frame timing sampled (FRAMES)", NULL, 0},
    {P_LOGS, K_ENVFLAG, "CODFH_WAITS", "Timers and waits, 20 s in (WAITS)", NULL, 0},
    {P_LOGS, K_ENVFLAG, "CODFH_SHOT_WINDOW", "Screenshots of the window (SHOT_WINDOW)", NULL, 0},
    {P_LOGS, K_ENVFLAG, "CODFH_DRAWID_NOALPHA", "Draw ids without alpha (DRAWID_NOALPHA)", NULL, 0},
};
static const int g_nOpt = (int)(sizeof(g_aOpt) / sizeof(g_aOpt[0]));

enum { ID_TAB = 90, ID_OPT = 100, ID_BROWSE = 900, ID_EXTRAARGS, ID_EXTRAENV, ID_PREVIEW, ID_LAUNCH, ID_SAVE,
       ID_STATUS };

static HWND g_hWnd, g_hTab;
static HFONT g_hFont;
static char g_szDir[MAX_PATH], g_szIni[MAX_PATH], g_szExe[MAX_PATH];
static std::vector<std::pair<HWND, int> > g_aPaged;    // each control on a tab, and its tab
// The build beside the launcher: 1 multiplayer, 0 single player, -1 not known (no codfh.exe);
// whether it has every-section loading; codfh.ini's data root, which the game takes before
// CODFH_DATA (xpal_core.cpp's port_config_load).
static int g_nMp = -1, g_nAllSections = -1;
static char g_szIniRoot[MAX_PATH];
static int g_nErrors, g_nWarnings;

// ---- the controls ----

static std::string Text(int id)
{
    char sz[4096];

    GetDlgItemTextA(g_hWnd, id, sz, sizeof(sz));
    return sz;
}

static int Sel(int id)
{
    int n = (int)SendDlgItemMessageA(g_hWnd, id, CB_GETCURSEL, 0, 0);
    return n < 0 ? 0 : n;
}

static bool Checked(int id)
{
    return IsDlgButtonChecked(g_hWnd, id) == BST_CHECKED;
}

static std::string Trim(const std::string &s)
{
    size_t a = s.find_first_not_of(" \t\r\n"), b = s.find_last_not_of(" \t\r\n");
    return a == std::string::npos ? std::string() : s.substr(a, b - a + 1);
}

// The choices of a list option, '|' separated.
static std::vector<std::string> Choices(const char *psz)
{
    std::vector<std::string> out;
    std::string s = psz ? psz : "";
    size_t p;

    while ((p = s.find('|')) != std::string::npos)
    {
        out.push_back(s.substr(0, p));
        s = s.substr(p + 1);
    }
    out.push_back(s);
    return out;
}

static std::string FirstWord(const std::string &s)
{
    size_t p = s.find(' ');
    return p == std::string::npos ? s : s.substr(0, p);
}

static HWND Make(const char *cls, const char *text, DWORD style, int x, int y, int w, int h, int id, int page)
{
    HWND hCtl = CreateWindowExA(!strcmp(cls, "EDIT") ? WS_EX_CLIENTEDGE : 0, cls, text, WS_CHILD | style,
                                x, y, w, h, g_hWnd, (HMENU)(INT_PTR)id, GetModuleHandleA(NULL), NULL);

    SendMessageA(hCtl, WM_SETFONT, (WPARAM)g_hFont, TRUE);
    if (page >= 0)
        g_aPaged.push_back(std::make_pair(hCtl, page));
    else
        ShowWindow(hCtl, SW_SHOW);
    return hCtl;
}

static void ComboItems(int id, const std::vector<std::string> &items)
{
    for (size_t i = 0; i < items.size(); i++)
        SendDlgItemMessageA(g_hWnd, id, CB_ADDSTRING, 0, (LPARAM)items[i].c_str());
}

// The names in dir matching pattern (files only), sorted by FindFirstFile.
static std::vector<std::string> Files(const char *dir, const char *pattern)
{
    std::vector<std::string> out;
    char sz[MAX_PATH];
    WIN32_FIND_DATAA fd;
    HANDLE h;

    _snprintf(sz, sizeof(sz), "%s\\%s", dir, pattern);
    sz[sizeof(sz) - 1] = 0;
    h = FindFirstFileA(sz, &fd);
    if (h == INVALID_HANDLE_VALUE)
        return out;
    do
    {
        if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
            out.push_back(fd.cFileName);
    } while (FindNextFileA(h, &fd));
    FindClose(h);
    return out;
}

// The map entries: the multiplayer front end's level list where the game has written it to the
// codfh.log beside the launcher ("levels (n):", then "  i name (game types ...)" lines, cli.cpp),
// else the single player's levels; each "number  name", the number what -map is given.
static std::vector<std::string> MapEntries()
{
    std::vector<std::string> out;
    char szLog[MAX_PATH], szLine[512];
    FILE *pFile;

    _snprintf(szLog, sizeof(szLog), "%s\\codfh.log", g_szDir);
    szLog[sizeof(szLog) - 1] = 0;
    pFile = fopen(szLog, "r");
    if (pFile)
    {
        bool in = false;

        while (fgets(szLine, sizeof(szLine), pFile))
        {
            const char *p = strchr(szLine, ']');
            int n;
            char szName[128];

            p = p ? p + 1 : szLine;
            while (*p == ' ')
                p++;
            if (!strncmp(p, "levels (", 8))
            {
                in = true;
                out.clear();
                continue;
            }
            if (in && sscanf(p, "%d %127[^(]", &n, szName) == 2)
            {
                char sz[160];

                sprintf(sz, "%d  %s", n, Trim(szName).c_str());
                out.push_back(sz);
            }
            else
                in = false;
        }
        fclose(pFile);
    }
    if (!out.empty())
        return out;
    for (int i = 0; i < (int)(sizeof(g_aSpLevel) / sizeof(g_aSpLevel[0])); i++)
    {
        char sz[80];

        sprintf(sz, "%d  %s  %s", g_aSpLevel[i].n, g_aSpLevel[i].name, g_aSpLevel[i].title);
        out.push_back(sz);
    }
    return out;
}

// A text option's value: an entry's number for the levels' list ("1  L_1_1_B"), else the text.
static std::string Value(int i)
{
    std::string v = Trim(Text(ID_OPT + i));

    if (g_aOpt[i].flags & F_MAP)
    {
        size_t n = 0;

        while (n < v.size() && v[n] >= '0' && v[n] <= '9')
            n++;
        if (n && n + 1 < v.size() && v[n] == ' ' && v[n + 1] == ' ')
            return v.substr(0, n);
    }
    return v;
}

static std::string Arguments();

// ---- the checks ----

static int OptIndex(const char *name)
{
    for (int i = 0; i < g_nOpt; i++)
        if (!strcmp(g_aOpt[i].name, name))
            return i;
    return -1;
}

static std::string OptValue(const char *name)
{
    int i = OptIndex(name);
    return i < 0 ? std::string() : Value(i);
}

static bool IsUInt(const std::string &v)
{
    if (v.empty() || v.size() > 9)
        return false;
    for (size_t i = 0; i < v.size(); i++)
        if (v[i] < '0' || v[i] > '9')
            return false;
    return true;
}

static bool IsInt(const std::string &v)
{
    return v.size() > 1 && v[0] == '-' ? IsUInt(v.substr(1)) : IsUInt(v);
}

static bool ContainsNoCase(const std::string &hay, const std::string &needle)
{
    std::string a = hay, b = needle;

    for (size_t i = 0; i < a.size(); i++)
        a[i] = (char)tolower((unsigned char)a[i]);
    for (size_t i = 0; i < b.size(); i++)
        b[i] = (char)tolower((unsigned char)b[i]);
    return a.find(b) != std::string::npos;
}

// Whether the file holds the text (the build's marks: PauseMenu.layout is multiplayer's front end,
// "load every section at once" the debug tools' every-section switch).
static int FileHas(const char *path, const char *text)
{
    FILE *f = fopen(path, "rb");
    std::vector<char> buf(1 << 20);
    size_t n, keep = 0, len = strlen(text);
    int found = 0;

    if (!f)
        return -1;
    while (!found && (n = fread(&buf[keep], 1, buf.size() - keep, f)) > 0)
    {
        n += keep;
        for (size_t i = 0; i + len <= n && !found; i++)
            found = !memcmp(&buf[i], text, len);
        keep = n < len ? n : len - 1;
        memmove(&buf[0], &buf[n - keep], keep);
    }
    fclose(f);
    return found;
}

// The data root the game will use: codfh.ini's, else CODFH_DATA's field, else its own folder.
static std::string DataRoot()
{
    std::string v = OptValue("CODFH_DATA");

    if (g_szIniRoot[0])
        return g_szIniRoot;
    return v.empty() ? std::string(g_szDir) : v;
}

static bool Exists(const std::string &path, bool folder)
{
    DWORD a = GetFileAttributesA(path.c_str());
    return a != INVALID_FILE_ATTRIBUTES && ((a & FILE_ATTRIBUTE_DIRECTORY) != 0) == folder;
}

// The single player's level -map names (cli.cpp's sp_map_level), or NULL; *pbFiles whether the
// pack has it.
static const char *SpLevel(const std::string &v, bool *pbFiles)
{
    const char *name = NULL;

    if (IsUInt(v))
        name = atoi(v.c_str()) < 38 ? g_apszSpTable[atoi(v.c_str())] : NULL;
    else
        for (int i = 0; i < 38 && !name; i++)
            if (ContainsNoCase(g_apszSpTable[i], v))
                name = g_apszSpTable[i];
    *pbFiles = false;
    for (size_t i = 0; name && i < sizeof(g_aSpLevel) / sizeof(g_aSpLevel[0]); i++)
        if (!strcmp(g_aSpLevel[i].name, name))
            *pbFiles = true;
    return name;
}

static void Validate(std::vector<std::string> &errs, std::vector<std::string> &warns)
{
    std::string map = OptValue("-map"), v;
    const char *level = NULL;
    bool files = false;

    // (each option for the other build: the game ignores it)
    for (int i = 0; i < g_nOpt; i++)
    {
        const Opt &o = g_aOpt[i];
        bool set = (o.kind == K_ARG || o.kind == K_ENV) ? !Value(i).empty()
                   : (o.kind == K_ARGFLAG || o.kind == K_ENVFLAG) ? Checked(ID_OPT + i) : Sel(ID_OPT + i) > 0;

        if (!set)
            continue;
        if ((o.flags & F_SP) && g_nMp == 1)
            warns.push_back(std::string(o.label) + ": single player's only; this is the multiplayer build");
        if ((o.flags & F_MP) && g_nMp == 0)
            warns.push_back(std::string(o.label) + ": multiplayer's only; this is the single-player build");
        if ((o.flags & F_UINT) && !IsUInt(Value(i)))
            errs.push_back(std::string(o.label) + ": a whole number from 0");
        if ((o.flags & F_INT) && !IsInt(Value(i)))
            errs.push_back(std::string(o.label) + ": a whole number");
        if (o.kind == K_ARG && Value(i).size() > 63)
            errs.push_back(std::string(o.label) + ": at most 63 characters (the game keeps 64)");
    }

    // the level
    if (!map.empty() && g_nMp != 1)
    {
        level = SpLevel(map, &files);
        if (!level)
            errs.push_back("Level: no single-player level is \"" + map + "\" (a number from the list, or part of a name)");
        else if (!files)
            errs.push_back(std::string("Level: ") + level + " has no files in COD.PAK");
    }
    else if (!map.empty())
    {
        HWND h = GetDlgItem(g_hWnd, ID_OPT + OptIndex("-map"));
        int n = (int)SendMessageA(h, CB_GETCOUNT, 0, 0) - 1, found = 0;

        for (int i = 1; i <= n && !found; i++)
        {
            char sz[256];

            SendMessageA(h, CB_GETLBTEXT, i, (LPARAM)sz);
            found = IsUInt(map) ? atoi(sz) == atoi(map.c_str()) : ContainsNoCase(sz, map);
        }
        if (n <= 0)
            warns.push_back("Level: the multiplayer levels are not known yet (the game lists them in codfh.log once it has run)");
        else if (!found)
            errs.push_back("Level: no multiplayer level is \"" + map + "\"");
    }

    // the checkpoint
    if (!(v = OptValue("-checkpoint")).empty() && IsUInt(v))
    {
        if (map.empty())
            errs.push_back("Checkpoint: needs a level (-map)");
        else if (level && files && atoi(v.c_str()) > 0)
        {
            int n = 0;

            for (size_t i = 0; i < sizeof(g_aCheckpoints) / sizeof(g_aCheckpoints[0]); i++)
                if (!strcmp(g_aCheckpoints[i].name, level))
                    n = g_aCheckpoints[i].n;
            if (!n)
                errs.push_back(std::string("Checkpoint: ") + level + " has no checkpoints");
            else if (atoi(v.c_str()) > n)
            {
                char sz[160];

                sprintf(sz, "Checkpoint: %s has %d checkpoint%s (1%s)", level, n, n > 1 ? "s" : "", n > 1 ? " to 2" : "");
                errs.push_back(sz);
            }
        }
    }
    if (!OptValue("-cpvalue").empty() && OptValue("-checkpoint").empty())
        warns.push_back("Checkpoint register: used only with a checkpoint");

    // what a level on the command line overrides or needs
    if (!map.empty() && Sel(ID_OPT + OptIndex("")) > 0)
        warns.push_back("Front end: ignored with a level (-map starts it straight away)");
    if (map.empty() && Sel(ID_OPT + OptIndex("-gametype")) > 0)
        warns.push_back("Game type: used only with a level (-map)");
    if (map.empty() && !OptValue("-name").empty())
        warns.push_back("Host as: hosts only with a level (-map)");

    // the data root and the movie
    if (!(v = OptValue("CODFH_DATA")).empty())
    {
        if (g_szIniRoot[0])
            warns.push_back(std::string("Data root: codfh.ini's [data] root (") + g_szIniRoot + ") is taken before CODFH_DATA");
        else if (!Exists(v, true))
            errs.push_back("Data root: no folder " + v);
        else if (!Exists(v + "\\COD.PAK", false))
            errs.push_back("Data root: no COD.PAK in " + v);
    }
    if (!(v = OptValue("-movie")).empty() && !Exists(DataRoot() + "\\SHELL\\MOVIES\\" + v, false))
        errs.push_back("Movie: no " + v + " in " + DataRoot() + "\\SHELL\\MOVIES");

    // the live link's port
    if (!(v = OptValue("CODFH_LIVE")).empty() && !(v == "1" || (IsUInt(v) && atoi(v.c_str()) >= 1024 && atoi(v.c_str()) <= 65535)))
        errs.push_back("Live link: 1 (the port 8771) or a port from 1024 to 65535");
    if (!(v = OptValue("CODFH_CRASHTEST")).empty() && IsUInt(v) && atoi(v.c_str()) == 0)
        errs.push_back("Crash test: from 1 second (0 does nothing)");

    // the frame ranges
    if (!OptValue("CODFH_DRAWID_TO").empty() && OptValue("CODFH_DRAWID").empty())
        warns.push_back("Draw ids: DRAWID_TO is used only with DRAWID");
    else if (IsUInt(OptValue("CODFH_DRAWID_TO")) && IsUInt(OptValue("CODFH_DRAWID")) &&
             atoi(OptValue("CODFH_DRAWID_TO").c_str()) < atoi(OptValue("CODFH_DRAWID").c_str()))
        errs.push_back("Draw ids: the last frame (DRAWID_TO) is before the first (DRAWID)");
    if (!OptValue("CODFH_DRAWID").empty() && IsUInt(OptValue("CODFH_DRAWID")) && !atoi(OptValue("CODFH_DRAWID").c_str()))
        errs.push_back("Draw ids from: from frame 1 (0 is off)");
    if (!OptValue("CODFH_SHOT").empty() && IsUInt(OptValue("CODFH_SHOT")) && !atoi(OptValue("CODFH_SHOT").c_str()))
        errs.push_back("Screenshot frame: from frame 1 (0 is off)");
    if ((!OptValue("CODFH_SHOT_FROM").empty() || !OptValue("CODFH_SHOT_TO").empty()) && OptValue("CODFH_SHOT_EVERY").empty())
        warns.push_back("Screenshots: SHOT_FROM and SHOT_TO are used only with SHOT_EVERY");
    if (IsUInt(OptValue("CODFH_SHOT_FROM")) && IsUInt(OptValue("CODFH_SHOT_TO")) &&
        atoi(OptValue("CODFH_SHOT_TO").c_str()) < atoi(OptValue("CODFH_SHOT_FROM").c_str()))
        errs.push_back("Screenshots: SHOT_TO is before SHOT_FROM");
    if (!OptValue("CODFH_SHOT_EVERY").empty() && OptValue("CODFH_SHOT").empty())
        warns.push_back("Screenshots: SHOT_EVERY is used only with SHOT");

    // the sound recording's folder
    if (!(v = OptValue("CODFH_WAV")).empty())
    {
        std::string path = v.size() > 1 && (v[1] == ':' || v[0] == '\\') ? v : std::string(g_szDir) + "\\" + v;
        size_t slash = path.find_last_of("\\/");

        if (slash != std::string::npos && !Exists(path.substr(0, slash), true))
            errs.push_back("Record the sound to: no folder " + path.substr(0, slash));
    }

    // the scripted input: frame:BUTTON,...
    if (!(v = OptValue("CODFH_INPUT")).empty())
    {
        std::string s = v;
        int n = 0;

        while (!s.empty())
        {
            size_t c = s.find(','), colon;
            std::string tok = Trim(s.substr(0, c)), button;
            bool ok = false;

            s = c == std::string::npos ? std::string() : s.substr(c + 1);
            n++;
            colon = tok.find(':');
            if (colon != std::string::npos && IsUInt(tok.substr(0, colon)))
            {
                button = tok.substr(colon + 1);
                for (size_t b = 0; b < sizeof(g_apszButton) / sizeof(g_apszButton[0]); b++)
                    ok = ok || button == g_apszButton[b];
            }
            if (!ok)
            {
                errs.push_back("Pad presses: \"" + tok + "\" is not frame:BUTTON (A B X Y BLACK WHITE LT RT START "
                               "BACK UP DOWN LEFT RIGHT LUP LDOWN LLEFT LRIGHT MUP MDOWN MLEFT MRIGHT)");
                break;
            }
        }
        if (n > 256)
            errs.push_back("Pad presses: at most 256");
        if (v.size() > 4095)
            errs.push_back("Pad presses: at most 4095 characters");
    }

    // the menu clicks: frame:x:y[:c],...
    if (!(v = OptValue("CODFH_SPMOUSE")).empty())
    {
        std::string s = v;
        int n = 0;

        while (!s.empty())
        {
            size_t c = s.find(',');
            std::string tok = Trim(s.substr(0, c));
            unsigned frame;
            float x, y;
            char k = 0, extra = 0;
            int got = sscanf(tok.c_str(), "%u:%f:%f:%c%c", &frame, &x, &y, &k, &extra);

            s = c == std::string::npos ? std::string() : s.substr(c + 1);
            n++;
            if (got < 3 || got == 5 || (got == 4 && k != 'c') || x < 0 || x >= 640 || y < 0 || y >= 480)
            {
                errs.push_back("Menu clicks: \"" + tok + "\" is not frame:x:y or frame:x:y:c (x below 640, y below 480)");
                break;
            }
        }
        if (n > 64)
            errs.push_back("Menu clicks: at most 64");
    }

    // every section at once, in a build without it
    if (Checked(ID_OPT + OptIndex("CODFH_ALLSECTIONS")) && g_nAllSections == 0)
        warns.push_back("Every section at once: this build has no every-section loading (built with --no-all-sections)");

    // the other variables and arguments
    {
        std::string extra = Text(ID_EXTRAENV);

        while (!extra.empty())
        {
            size_t p = extra.find('\n'), eq;
            std::string line = Trim(extra.substr(0, p));
            bool ok = true;

            extra = p == std::string::npos ? std::string() : extra.substr(p + 1);
            if (line.empty() || line[0] == '#')
                continue;
            eq = line.find('=');
            ok = eq != std::string::npos && eq > 0;
            for (size_t j = 0; ok && j < eq; j++)
                ok = isalnum((unsigned char)line[j]) || line[j] == '_';
            if (!ok)
                errs.push_back("Other variables: \"" + line + "\" is not NAME=value");
        }
    }
    {
        std::string a = Trim(Text(ID_EXTRAARGS));
        std::vector<std::string> words;
        size_t i = 0;

        while (i < a.size())
        {
            while (i < a.size() && a[i] == ' ')
                i++;
            if (i >= a.size())
                break;
            size_t j = a[i] == '"' ? a.find('"', i + 1) : a.find(' ', i);
            words.push_back(a.substr(a[i] == '"' ? i + 1 : i, j == std::string::npos ? std::string::npos : j - (a[i] == '"' ? i + 1 : i)));
            i = j == std::string::npos ? a.size() : j + 1;
        }
        for (size_t w = 0; w < words.size(); w++)
        {
            int known = -1;

            for (size_t k = 0; k < sizeof(g_aKnownArg) / sizeof(g_aKnownArg[0]); k++)
                if (!_stricmp(words[w].c_str(), g_aKnownArg[k].name))
                    known = g_aKnownArg[k].args;
            if (known < 0)
                warns.push_back("Other arguments: the game ignores \"" + words[w] + "\"");
            else
                w += known;
        }
    }
    {
        // (cli.cpp's parse: a 1024-character line, 32 words)
        std::string a = Arguments();
        int words = 0;

        for (size_t i = 0; i < a.size(); i++)
            if (a[i] != ' ' && (i == 0 || a[i - 1] == ' '))
                words++;
        if (a.size() > 1000)
            errs.push_back("Command line: longer than the game reads (1024 characters)");
        if (words > 32)
            errs.push_back("Command line: more than the game reads (32 words)");
    }
}

// ---- the command line and the environment ----

static std::string Quote(const std::string &s)
{
    return s.find_first_of(" \t\"") == std::string::npos && !s.empty() ? s : "\"" + s + "\"";
}

static std::string Arguments()
{
    std::string a, v;

    for (int i = 0; i < g_nOpt; i++)
    {
        const Opt &o = g_aOpt[i];

        if (o.kind == K_ARG && !(v = Value(i)).empty())
            a += std::string(" ") + o.name + " " + Quote(v);
        else if (o.kind == K_ARGFLAG && Checked(ID_OPT + i))
            a += std::string(" ") + o.name;
        else if (o.kind == K_ARGLIST && Sel(ID_OPT + i) > 0)
        {
            v = FirstWord(Choices(o.choices)[Sel(ID_OPT + i)]);
            a += o.name[0] ? std::string(" ") + o.name + " " + v : " " + v;
        }
    }
    if (!(v = Trim(Text(ID_EXTRAARGS))).empty())
        a += " " + v;
    return a;
}

// The variables the launcher sets: NAME=value each, in order (an empty value for one it takes out).
static std::vector<std::string> Variables()
{
    std::vector<std::string> out;
    std::string v, extra;
    size_t p;

    for (int i = 0; i < g_nOpt; i++)
    {
        const Opt &o = g_aOpt[i];

        if (o.kind == K_ENV)
            out.push_back(std::string(o.name) + "=" + Value(i));
        else if (o.kind == K_ENVFLAG)
            out.push_back(std::string(o.name) + "=" +
                          (Checked(ID_OPT + i) ? (o.choices ? o.choices : "1") : (o.flags & F_OFF0) ? "0" : ""));
        else if (o.kind == K_ENVLIST)
            out.push_back(std::string(o.name) + "=" +
                          (Sel(ID_OPT + i) > 0 ? FirstWord(Choices(o.choices)[Sel(ID_OPT + i)]) : ""));
    }
    extra = Text(ID_EXTRAENV);
    while (!extra.empty())
    {
        std::string line;

        p = extra.find('\n');
        line = Trim(extra.substr(0, p));
        extra = p == std::string::npos ? std::string() : extra.substr(p + 1);
        if (line.find('=') != std::string::npos && line[0] != '=' && line[0] != '#')
            out.push_back(line);
    }
    return out;
}

static std::string Preview()
{
    std::string s;
    std::vector<std::string> vars = Variables();

    for (size_t i = 0; i < vars.size(); i++)
        if (vars[i][vars[i].size() - 1] != '=')
            s += vars[i] + " ";
    return s + "codfh.exe" + Arguments();
}

static std::string Problems()
{
    std::vector<std::string> errs, warns;
    std::string s;

    Validate(errs, warns);
    g_nErrors = (int)errs.size();
    g_nWarnings = (int)warns.size();
    for (size_t i = 0; i < errs.size(); i++)
        s += "Error: " + errs[i] + "\r\n";
    for (size_t i = 0; i < warns.size(); i++)
        s += "Warning: " + warns[i] + "\r\n";
    return s.empty() ? std::string("No problems found.") : s;
}

static void UpdatePreview()
{
    SetDlgItemTextA(g_hWnd, ID_PREVIEW, Preview().c_str());
    SetDlgItemTextA(g_hWnd, ID_STATUS, Problems().c_str());
    InvalidateRect(GetDlgItem(g_hWnd, ID_STATUS), NULL, TRUE);
}

// The launcher's environment with the variables it sets put in (or taken out, for an empty value).
static std::vector<char> Environment()
{
    std::vector<std::string> vars = Variables(), all;
    std::vector<char> block;
    char *pEnv = GetEnvironmentStringsA(), *p;

    for (p = pEnv; *p; p += strlen(p) + 1)
    {
        std::string e = p;
        bool replaced = false;

        for (size_t i = 0; i < vars.size() && !replaced; i++)
        {
            size_t eq = vars[i].find('=');

            replaced = e.size() > eq && !_strnicmp(e.c_str(), vars[i].c_str(), eq + 1);
        }
        if (!replaced)
            all.push_back(e);
    }
    FreeEnvironmentStringsA(pEnv);
    for (size_t i = 0; i < vars.size(); i++)
        if (vars[i][vars[i].size() - 1] != '=')
            all.push_back(vars[i]);
    for (size_t i = 0; i < all.size(); i++)
        block.insert(block.end(), all[i].c_str(), all[i].c_str() + all[i].size() + 1);
    block.push_back(0);
    return block;
}

// ---- the settings (the ini's [launcher] section, a key per option's name) ----

static void SaveText(const char *key, std::string v)
{
    // (the extra environment's lines, kept as | separated)
    for (size_t j = 0; j < v.size(); j++)
        if (v[j] == '\r')
            v.erase(j--, 1);
        else if (v[j] == '\n')
            v[j] = '|';
    WritePrivateProfileStringA("launcher", key, v.c_str(), g_szIni);
}

static void Save()
{
    char sz[16];

    for (int i = 0; i < g_nOpt; i++)
    {
        const Opt &o = g_aOpt[i];
        const char *key = o.name[0] ? o.name : "frontend";

        if (o.kind == K_ARGFLAG || o.kind == K_ENVFLAG)
            SaveText(key, Checked(ID_OPT + i) ? "1" : "0");
        else if (o.kind == K_ARGLIST || o.kind == K_ENVLIST)
            SaveText(key, (sprintf(sz, "%d", Sel(ID_OPT + i)), sz));
        else
            SaveText(key, Text(ID_OPT + i));
    }
    SaveText("extraargs", Text(ID_EXTRAARGS));
    SaveText("extraenv", Text(ID_EXTRAENV));
    sprintf(sz, "%d", TabCtrl_GetCurSel(g_hTab));
    SaveText("tab", sz);
}

static bool LoadText(const char *key, std::string *pv)
{
    char sz[4096];

    if (!GetPrivateProfileStringA("launcher", key, "\x01", sz, sizeof(sz), g_szIni) || sz[0] == 1)
        return false;
    *pv = sz;
    for (size_t j = 0; j < pv->size(); j++)
        if ((*pv)[j] == '|')
            pv->replace(j, 1, "\r\n"), j++;
    return true;
}

// The key an option had in the launcher's first ini: its name without the dash or CODFH_, in
// lower case ("map", "freecam"); the front end's "mainmenu".
static std::string LegacyKey(const Opt &o)
{
    std::string k = !o.name[0] ? "mainmenu" : o.name[0] == '-' ? o.name + 1 : !strncmp(o.name, "CODFH_", 6) ? o.name + 6 : o.name;

    for (size_t j = 0; j < k.size(); j++)
        k[j] = (char)tolower((unsigned char)k[j]);
    return k;
}

static void Load()
{
    std::string v;

    for (int i = 0; i < g_nOpt; i++)
    {
        const Opt &o = g_aOpt[i];

        if (!LoadText(o.name[0] ? o.name : "frontend", &v))
        {
            if (!LoadText(LegacyKey(o).c_str(), &v))
                continue;
            // (the first launcher's live link was a switch: 0 is off here, an empty field)
            if (!strcmp(o.name, "CODFH_LIVE") && v == "0")
                v.clear();
        }
        // (a level kept from before: the list's entry it starts (one saved without its title), or
        // none when the list no longer has it, one with no files)
        if ((o.flags & F_MAP) && v.find("  ") != std::string::npos)
        {
            LRESULT n = SendDlgItemMessageA(g_hWnd, ID_OPT + i, CB_FINDSTRING, (WPARAM)-1, (LPARAM)v.c_str());
            char sz[256];

            if (n == CB_ERR || SendDlgItemMessageA(g_hWnd, ID_OPT + i, CB_GETLBTEXTLEN, n, 0) >= (LRESULT)sizeof(sz))
                v.clear();
            else
            {
                SendDlgItemMessageA(g_hWnd, ID_OPT + i, CB_GETLBTEXT, n, (LPARAM)sz);
                v = sz;
            }
        }
        if (o.kind == K_ARGFLAG || o.kind == K_ENVFLAG)
            CheckDlgButton(g_hWnd, ID_OPT + i, atoi(v.c_str()) ? BST_CHECKED : BST_UNCHECKED);
        else if (o.kind == K_ARGLIST || o.kind == K_ENVLIST)
            SendDlgItemMessageA(g_hWnd, ID_OPT + i, CB_SETCURSEL, atoi(v.c_str()), 0);
        else
            SetDlgItemTextA(g_hWnd, ID_OPT + i, v.c_str());
    }
    if (LoadText("extraargs", &v))
        SetDlgItemTextA(g_hWnd, ID_EXTRAARGS, v.c_str());
    if (LoadText("extraenv", &v))
        SetDlgItemTextA(g_hWnd, ID_EXTRAENV, v.c_str());
    if (LoadText("tab", &v))
        TabCtrl_SetCurSel(g_hTab, atoi(v.c_str()) >= 0 && atoi(v.c_str()) < P_COUNT ? atoi(v.c_str()) : 0);
}

// ---- launching ----

static void Launch()
{
    std::string cmd = "\"" + std::string(g_szExe) + "\"" + Arguments();
    std::vector<char> env = Environment();
    std::vector<char> line(cmd.begin(), cmd.end());
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;

    Save();
    Problems();
    if (g_nErrors)
    {
        MessageBoxA(g_hWnd, ("Not launched: fix the errors first.\n\n" + Problems()).c_str(), "CODFH launcher",
                    MB_ICONWARNING);
        return;
    }
    line.push_back(0);
    memset(&si, 0, sizeof(si));
    si.cb = sizeof(si);
    if (GetFileAttributesA(g_szExe) == INVALID_FILE_ATTRIBUTES)
    {
        MessageBoxA(g_hWnd, ("No codfh.exe beside the launcher:\n" + std::string(g_szExe)).c_str(), "CODFH launcher",
                    MB_ICONERROR);
        return;
    }
    if (!CreateProcessA(g_szExe, &line[0], NULL, NULL, FALSE, 0, &env[0], g_szDir, &si, &pi))
    {
        char sz[64];

        sprintf(sz, "CreateProcess failed (error %lu)", GetLastError());
        MessageBoxA(g_hWnd, sz, "CODFH launcher", MB_ICONERROR);
        return;
    }
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
}

static void Browse(int id)
{
    BROWSEINFOA bi;
    char sz[MAX_PATH];
    LPITEMIDLIST pidl;

    memset(&bi, 0, sizeof(bi));
    bi.hwndOwner = g_hWnd;
    bi.pszDisplayName = sz;
    bi.lpszTitle = "The data root (the folder holding COD.PAK, LEVELS, SHELL and the rest; CODFH_DATA)";
    bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
    pidl = SHBrowseForFolderA(&bi);
    if (pidl && SHGetPathFromIDListA(pidl, sz))
        SetDlgItemTextA(g_hWnd, id, sz);
    if (pidl)
        CoTaskMemFree(pidl);
}

// ---- the window ----

static void ShowPage(int page)
{
    for (size_t i = 0; i < g_aPaged.size(); i++)
        ShowWindow(g_aPaged[i].first, g_aPaged[i].second == page ? SW_SHOW : SW_HIDE);
}

enum { W = 640, TOP = 40, TABH = 424, LABELW = 150, FIELDW = 152, COLW = 312 };

// One tab's options: the fields first, two a row (a wide one a row of its own), then the
// switches, two a row.
static void BuildPage(int page)
{
    char szMovies[MAX_PATH];
    int y = TOP, col = 0;

    _snprintf(szMovies, sizeof(szMovies), "%s\\SHELL\\MOVIES", g_szIniRoot[0] ? g_szIniRoot : g_szDir);
    szMovies[sizeof(szMovies) - 1] = 0;
    for (int i = 0; i < g_nOpt; i++)
    {
        const Opt &o = g_aOpt[i];
        int id = ID_OPT + i, x;

        if (o.page != page || o.kind == K_ARGFLAG || o.kind == K_ENVFLAG)
            continue;
        if (o.flags & F_WIDE)
        {
            if (col)
                y += 28, col = 0;
            Make("STATIC", o.label, 0, 16, y + 3, LABELW + 60, 18, -1, page);
            int fw = W - 16 - (16 + LABELW + 60) - ((o.flags & F_BROWSE) ? 80 : 0);
            Make("EDIT", "", ES_AUTOHSCROLL | WS_TABSTOP, 16 + LABELW + 60, y, fw, 22, id, page);
            if (o.flags & F_BROWSE)
                Make("BUTTON", "Browse...", BS_PUSHBUTTON | WS_TABSTOP, W - 16 - 74, y, 74, 22, ID_BROWSE, page);
            y += 28;
            continue;
        }
        x = 16 + col * COLW;
        Make("STATIC", o.label, 0, x, y + 3, LABELW, 18, -1, page);
        if (o.kind == K_ARGLIST || o.kind == K_ENVLIST)
        {
            std::vector<std::string> items = Choices(o.choices);

            Make("COMBOBOX", "", CBS_DROPDOWNLIST | WS_VSCROLL | WS_TABSTOP, x + LABELW, y, FIELDW, 300, id, page);
            ComboItems(id, items);
            SendDlgItemMessageA(g_hWnd, id, CB_SETCURSEL, 0, 0);
            SendDlgItemMessageA(g_hWnd, id, CB_SETDROPPEDWIDTH, 220, 0);
        }
        else if (o.flags & (F_MAP | F_MOVIE))
        {
            std::vector<std::string> items = (o.flags & F_MAP) ? MapEntries() : Files(szMovies, "*.bik");

            items.insert(items.begin(), "");
            Make("COMBOBOX", "", CBS_DROPDOWN | CBS_AUTOHSCROLL | WS_VSCROLL | WS_TABSTOP, x + LABELW, y, FIELDW, 300,
                 id, page);
            ComboItems(id, items);
            SendDlgItemMessageA(g_hWnd, id, CB_SETDROPPEDWIDTH, (o.flags & F_MAP) ? 300 : 220, 0);
        }
        else
            Make("EDIT", "", ES_AUTOHSCROLL | WS_TABSTOP | ((o.flags & F_UINT) ? ES_NUMBER : 0), x + LABELW, y, FIELDW, 22,
                 id, page);
        if (++col == 2)
            y += 28, col = 0;
    }
    if (col)
        y += 28, col = 0;
    y += 8;
    for (int i = 0; i < g_nOpt; i++)
    {
        const Opt &o = g_aOpt[i];

        if (o.page != page || (o.kind != K_ARGFLAG && o.kind != K_ENVFLAG))
            continue;
        Make("BUTTON", o.label, BS_AUTOCHECKBOX | WS_TABSTOP, 16 + col * COLW, y, COLW - 8, 20, ID_OPT + i, page);
        if (++col == 2)
            y += 24, col = 0;
    }
}

static void Build()
{
    TCITEMA ti;
    int y = TOP + TABH - 30;

    g_hTab = CreateWindowExA(0, WC_TABCONTROLA, "", WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_TABSTOP, 8, 8, W - 8,
                             TABH, g_hWnd, (HMENU)(INT_PTR)ID_TAB, GetModuleHandleA(NULL), NULL);
    SendMessageA(g_hTab, WM_SETFONT, (WPARAM)g_hFont, TRUE);
    memset(&ti, 0, sizeof(ti));
    ti.mask = TCIF_TEXT;
    for (int p = 0; p < P_COUNT; p++)
    {
        ti.pszText = (LPSTR)g_apszPage[p];
        TabCtrl_InsertItem(g_hTab, p, &ti);
    }
    for (int p = 0; p < P_COUNT; p++)
        BuildPage(p);
    y = 8 + TABH + 10;
    Make("STATIC", "Other variables (NAME=value a line)", 0, 8, y + 3, 200, 18, -1, -1);
    Make("EDIT", "", ES_MULTILINE | ES_AUTOVSCROLL | WS_VSCROLL | ES_WANTRETURN | WS_TABSTOP, 210, y, W - 210, 52,
         ID_EXTRAENV, -1);
    y += 58;
    Make("STATIC", "Other arguments", 0, 8, y + 3, 200, 18, -1, -1);
    Make("EDIT", "", ES_AUTOHSCROLL | WS_TABSTOP, 210, y, W - 210, 22, ID_EXTRAARGS, -1);
    y += 34;
    Make("STATIC", "Command line", 0, 8, y, 200, 18, -1, -1);
    y += 20;
    Make("EDIT", "", ES_MULTILINE | ES_READONLY | ES_AUTOVSCROLL | WS_VSCROLL, 8, y, W - 8, 58, ID_PREVIEW, -1);
    y += 64;
    Make("EDIT", "", ES_MULTILINE | ES_READONLY | ES_AUTOVSCROLL | WS_VSCROLL, 8, y, W - 8, 62, ID_STATUS, -1);
    y += 70;
    Make("BUTTON", "Launch", BS_DEFPUSHBUTTON | WS_TABSTOP, W - 168, y, 80, 28, ID_LAUNCH, -1);
    Make("BUTTON", "Save", BS_PUSHBUTTON | WS_TABSTOP, W - 80, y, 80, 28, ID_SAVE, -1);
    // (the console's default in the ini is on; the launcher's is off until checked)
    for (int i = 0; i < g_nOpt; i++)
        if (!strcmp(g_aOpt[i].name, "CODFH_CONSOLE"))
            CheckDlgButton(g_hWnd, ID_OPT + i, BST_UNCHECKED);
}

static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CREATE:
        g_hWnd = hWnd;
        Build();
        Load();
        ShowPage(TabCtrl_GetCurSel(g_hTab));
        UpdatePreview();
        return 0;
    case WM_NOTIFY:
        if (((NMHDR *)lParam)->idFrom == ID_TAB && ((NMHDR *)lParam)->code == TCN_SELCHANGE)
            ShowPage(TabCtrl_GetCurSel(g_hTab));
        return 0;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case ID_LAUNCH:
            Launch();
            return 0;
        case ID_SAVE:
            Save();
            return 0;
        case ID_BROWSE:
            for (int i = 0; i < g_nOpt; i++)
                if (g_aOpt[i].flags & F_BROWSE)
                    Browse(ID_OPT + i);
            break;
        }
        if (HIWORD(wParam) == EN_CHANGE || HIWORD(wParam) == CBN_SELCHANGE || HIWORD(wParam) == CBN_EDITCHANGE
            || HIWORD(wParam) == BN_CLICKED)
            UpdatePreview();
        return 0;
    case WM_CTLCOLORSTATIC:
        // (the problems: red with an error, amber with only warnings, green with none)
        if ((HWND)lParam == GetDlgItem(hWnd, ID_STATUS))
            SetTextColor((HDC)wParam, g_nErrors ? RGB(190, 0, 0) : g_nWarnings ? RGB(160, 100, 0) : RGB(0, 120, 0));
        SetBkMode((HDC)wParam, TRANSPARENT);
        return (LRESULT)GetSysColorBrush(COLOR_BTNFACE);
    case WM_CLOSE:
        Save();
        DestroyWindow(hWnd);
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProcA(hWnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int)
{
    WNDCLASSA wc;
    MSG msg;
    char *p;
    RECT rc = {0, 0, W + 8, 8 + TABH + 10 + 58 + 34 + 20 + 64 + 70 + 28 + 10};
    NONCLIENTMETRICSA ncm;
    INITCOMMONCONTROLSEX icc;

    GetModuleFileNameA(NULL, g_szDir, sizeof(g_szDir));
    p = strrchr(g_szDir, '\\');
    if (p)
        *p = 0;
    _snprintf(g_szIni, sizeof(g_szIni), "%s\\codfh_launcher.ini", g_szDir);
    _snprintf(g_szExe, sizeof(g_szExe), "%s\\codfh.exe", g_szDir);
    g_szIni[sizeof(g_szIni) - 1] = g_szExe[sizeof(g_szExe) - 1] = 0;
    g_nMp = FileHas(g_szExe, "PauseMenu.layout");
    g_nAllSections = FileHas(g_szExe, "load every section at once");
    {
        char szGameIni[MAX_PATH];

        _snprintf(szGameIni, sizeof(szGameIni), "%s\\codfh.ini", g_szDir);
        szGameIni[sizeof(szGameIni) - 1] = 0;
        GetPrivateProfileStringA("data", "root", "", g_szIniRoot, sizeof(g_szIniRoot), szGameIni);
    }
    CoInitialize(NULL);
    icc.dwSize = sizeof(icc);
    icc.dwICC = ICC_TAB_CLASSES;
    InitCommonControlsEx(&icc);
    ncm.cbSize = sizeof(ncm);
    SystemParametersInfoA(SPI_GETNONCLIENTMETRICS, sizeof(ncm), &ncm, 0);
    g_hFont = CreateFontIndirectA(&ncm.lfMessageFont);
    memset(&wc, 0, sizeof(wc));
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInst;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = GetSysColorBrush(COLOR_BTNFACE);
    wc.lpszClassName = "CodfhLauncher";
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    RegisterClassA(&wc);
    AdjustWindowRect(&rc, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, FALSE);
    CreateWindowA("CodfhLauncher", "Call of Duty: Finest Hour (port) launcher",
                  WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT,
                  rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, hInst, NULL);
    while (GetMessageA(&msg, NULL, 0, 0))
    {
        if (!IsDialogMessageA(g_hWnd, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessageA(&msg);
        }
    }
    return 0;
}
