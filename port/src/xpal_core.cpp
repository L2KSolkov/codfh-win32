/*
 * The platform layer's core (docs/WIN32_PORT.md W0, W1): the log, the configuration, and the
 * Xbox drives mapped to Win32 directories (d:\ the disc's data, t:\ the title cache, u:\ the
 * saves, z:\ the scratch drive), with the path-taking Win32 calls the sources make routed
 * through the mapping (xtl.h's xpal_* macros).
 */
#include <xtl.h>
#include <shlobj.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "port.h"

#undef CreateFileA
#undef GetFileAttributesA
#undef CopyFileA
#undef OutputDebugStringA
#undef QueryPerformanceCounter
#undef GetTickCount

PortConfig port_config;
void *port_hwnd;
volatile int port_quit;
volatile unsigned port_frame;

static FILE *log_file;
static CRITICAL_SECTION log_lock;
static int log_ready;

static void exe_dir(char *out, size_t n)
{
    GetModuleFileNameA(NULL, out, (DWORD)n);
    char *slash = strrchr(out, '\\');
    if (slash)
        slash[1] = 0;
}

void plog(const char *fmt, ...)
{
    char line[1024];
    va_list ap;
    va_start(ap, fmt);
    _vsnprintf(line, sizeof(line) - 2, fmt, ap);
    va_end(ap);
    line[sizeof(line) - 2] = 0;
    size_t len = strlen(line);
    if (!len || line[len - 1] != '\n')
        strcat(line, "\n");
    if (!log_ready)
    {
        InitializeCriticalSection(&log_lock);
        log_ready = 1;
    }
    EnterCriticalSection(&log_lock);
    if (!log_file)
    {
        char path[MAX_PATH];
        exe_dir(path, sizeof(path));
#ifdef CODFH_DEDICATED
        strcat(path, "codfh_server.log");
#else
        strcat(path, "codfh.log");
#endif
        log_file = fopen(path, "w");
    }
    if (log_file)
    {
        fprintf(log_file, "[%8lu] %s", GetTickCount(), line);
        fflush(log_file);
    }
#ifdef CODFH_DEDICATED
    /* (the server's log is its console too) */
    {
        HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD n;
        if (out && out != INVALID_HANDLE_VALUE)
            WriteFile(out, line, (DWORD)strlen(line), &n, NULL);
    }
#endif
    LeaveCriticalSection(&log_lock);
    OutputDebugStringA(line);
}

void plog_stub(const char *name)
{
    static const char *seen[512];
    static int nseen;
    for (int i = 0; i < nseen; i++)
        if (seen[i] == name)
            return;
    if (nseen < 512)
        seen[nseen++] = name;
    plog("stub: %s", name);
}

static int ini_int(const char *ini, const char *section, const char *key, int def)
{
    return (int)GetPrivateProfileIntA(section, key, def, ini);
}

static void make_dirs(const char *path)
{
    char tmp[MAX_PATH];
    strncpy(tmp, path, sizeof(tmp) - 1);
    tmp[sizeof(tmp) - 1] = 0;
    for (char *p = tmp + 3; *p; p++)
        if (*p == '\\' || *p == '/')
        {
            char c = *p;
            *p = 0;
            CreateDirectoryA(tmp, NULL);
            *p = c;
        }
    CreateDirectoryA(tmp, NULL);
}

/* The disc's files are under root: its COD.PAK is there. */
static int has_data(const char *root)
{
    char path[MAX_PATH];
    _snprintf(path, sizeof(path), "%s\\COD.PAK", root);
    path[sizeof(path) - 1] = 0;
    return GetFileAttributesA(path) != INVALID_FILE_ATTRIBUTES;
}

/*
 * A data root with the disc's files when the configured one has none: the executable's directory
 * and up to three above it, then \CODFH_DUMP on each drive. Found, it is written to codfh.ini
 * ([data] root) for the next start; not found, the game cannot run (it would fail later, on the
 * first sound or texture it cannot find), and says so.
 */
static void find_data_root(const char *ini)
{
    if (has_data(port_config.dataRoot))
        return;
    char tried[MAX_PATH];
    strcpy(tried, port_config.dataRoot);
    char dir[MAX_PATH];
    exe_dir(dir, sizeof(dir));
    for (int up = 0; up <= 3; up++)
    {
        size_t n = strlen(dir);
        while (n > 3 && (dir[n - 1] == '\\' || dir[n - 1] == '/'))
            dir[--n] = 0;
        if (has_data(dir))
        {
            strcpy(port_config.dataRoot, dir);
            break;
        }
        char *slash = strrchr(dir, '\\');
        if (!slash || slash - dir < 3)
            break;
        *slash = 0;
    }
    for (char d = 'C'; !has_data(port_config.dataRoot) && d <= 'Z'; d++)
    {
        char root[16];
        _snprintf(root, sizeof(root), "%c:\\CODFH_DUMP", d);
        root[sizeof(root) - 1] = 0;
        char drive[4] = {d, ':', '\\', 0};
        if (GetDriveTypeA(drive) <= DRIVE_NO_ROOT_DIR)
            continue;
        if (has_data(root))
            strcpy(port_config.dataRoot, root);
    }
    if (has_data(port_config.dataRoot))
    {
        WritePrivateProfileStringA("data", "root", port_config.dataRoot, ini);
        plog("data root %s has no COD.PAK: using %s (written to codfh.ini)", tried, port_config.dataRoot);
        return;
    }
    char text[1024];
    _snprintf(text, sizeof(text),
              "The game's files were not found (no COD.PAK in %s).\n\n"
              "Set the folder that holds the disc's files (COD.PAK, AUDIO, SHELL...) in codfh.ini beside "
              "the game:\n\n[data]\nroot=D:\\path\\to\\the\\files\n\n"
              "or in the CODFH_DATA environment variable.", tried);
    text[sizeof(text) - 1] = 0;
    plog("no data root: %s has no COD.PAK", tried);
    MessageBoxA(NULL, text, "Call of Duty: Finest Hour", MB_OK | MB_ICONERROR);
    ExitProcess(1);
}

void port_config_load(void)
{
    char ini[MAX_PATH];
    exe_dir(ini, sizeof(ini));
    strcat(ini, "codfh.ini");

    /* The data root: the ini, then CODFH_DATA, then the executable's directory. */
    char def[MAX_PATH];
    if (!GetEnvironmentVariableA("CODFH_DATA", def, sizeof(def)))
        exe_dir(def, sizeof(def));
    GetPrivateProfileStringA("data", "root", def, port_config.dataRoot, sizeof(port_config.dataRoot), ini);
    {
        size_t n = strlen(port_config.dataRoot);
        while (n > 3 && (port_config.dataRoot[n - 1] == '\\' || port_config.dataRoot[n - 1] == '/'))
            port_config.dataRoot[--n] = 0;
    }
    find_data_root(ini);

    char user[MAX_PATH] = "";
    if (FAILED(SHGetFolderPathA(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, user)))
        exe_dir(user, sizeof(user));
    strcat(user, "\\CODFH");
    GetPrivateProfileStringA("data", "user", user, port_config.userRoot, sizeof(port_config.userRoot), ini);

    port_config.width = ini_int(ini, "video", "width", 1280);
    port_config.height = ini_int(ini, "video", "height", 960);
    port_config.windowed = ini_int(ini, "video", "windowed", 1);
    port_config.vsync = ini_int(ini, "video", "vsync", 1);
    port_config.widescreen = ini_int(ini, "video", "widescreen", 0);
    port_config.language = ini_int(ini, "game", "language", 0);
    {
        char user[64] = "Player";
        DWORD n = sizeof(user);
        if (!GetUserNameA(user, &n) || !user[0])
            strcpy(user, "Player");
        GetPrivateProfileStringA("game", "name", user, port_config.playerName, sizeof(port_config.playerName), ini);
        if (!port_config.playerName[0])
            strcpy(port_config.playerName, "Player");
    }
    char sens[32];
    GetPrivateProfileStringA("input", "mouse_sensitivity", "1.0", sens, sizeof(sens), ini);
    port_config.mouseSensitivity = (float)atof(sens);
    {
        char rs[32];
        GetPrivateProfileStringA("video", "render_scale", "0", rs, sizeof(rs), ini);
        port_config.renderScale = (float)atof(rs);
    }

    /* (no trailing separator on the roots: the mapped paths add one) */
    for (char *r = port_config.dataRoot; r; r = r == port_config.dataRoot ? port_config.userRoot : NULL)
    {
        size_t n = strlen(r);
        while (n > 3 && (r[n - 1] == '\\' || r[n - 1] == '/'))
            r[--n] = 0;
    }
    static const char *const sub[] = {"\\cache", "\\saves", "\\scratch"};
    for (int i = 0; i < 3; i++)
    {
        char d[MAX_PATH];
        strcpy(d, port_config.userRoot);
        strcat(d, sub[i]);
        make_dirs(d);
    }
    plog("data root %s, user root %s, %dx%d %s", port_config.dataRoot, port_config.userRoot,
         port_config.width, port_config.height, port_config.windowed ? "windowed" : "fullscreen");
}

const char *port_map_path(const char *x, char *out)
{
    if (!x || !x[0] || x[1] != ':' || (x[2] != '\\' && x[2] != '/' && x[2] != 0))
        return x;
    const char *root;
    const char *sub = "";
    switch (x[0] | 0x20)
    {
    case 'd': root = port_config.dataRoot; break;
    case 't': root = port_config.userRoot; sub = "\\cache"; break;
    case 'u': root = port_config.userRoot; sub = "\\saves"; break;
    case 'z': root = port_config.userRoot; sub = "\\scratch"; break;
    default: return x;
    }
    _snprintf(out, 519, "%s%s%s%s", root, sub, x[2] ? "" : "\\", x + 2);
    out[519] = 0;
    for (char *p = out; *p; p++)
        if (*p == '/')
            *p = '\\';
    return out;
}

extern "C" HANDLE WINAPI xpal_CreateFileA(LPCSTR name, DWORD access, DWORD share,
                                          LPSECURITY_ATTRIBUTES sa, DWORD disposition, DWORD flags,
                                          HANDLE templ)
{
    char buf[520];
    const char *path = port_map_path(name, buf);
    /* (the Xbox's no-buffering reads need sector-aligned buffers the sources do not keep on PC) */
    flags &= ~FILE_FLAG_NO_BUFFERING;
    HANDLE h = CreateFileA(path, access, share, sa, disposition, flags, templ);
    if (h == INVALID_HANDLE_VALUE)
        plog("CreateFile %s -> %s failed (%lu)", name, path, GetLastError());
    return h;
}

extern "C" DWORD WINAPI xpal_GetFileAttributesA(LPCSTR name)
{
    char buf[520];
    return GetFileAttributesA(port_map_path(name, buf));
}

extern "C" BOOL WINAPI xpal_CopyFileA(LPCSTR from, LPCSTR to, BOOL failIfExists)
{
    char a[520], b[520];
    return CopyFileA(port_map_path(from, a), port_map_path(to, b), failIfExists);
}

/* The game's language index (0 English, 1 German, 2 French, 5 Italian, 6 Spanish: sub_19BEA0's
   mapping to the console's languages): codfh.ini [game] language. */
extern "C" int port_language(void)
{
    return port_config.language >= 0 && port_config.language <= 8 ? port_config.language : 0;
}

extern "C" BOOL WINAPI xpal_QueryPerformanceCounter(LARGE_INTEGER *count)
{
    static LONGLONG base;
    LARGE_INTEGER now;
    BOOL ok = QueryPerformanceCounter(&now);
    if (!base)
    {
        /* (a second before the first read, so no count is ever 0) */
        LARGE_INTEGER f;
        QueryPerformanceFrequency(&f);
        InterlockedCompareExchange64(&base, now.QuadPart - f.QuadPart, 0);
    }
    count->QuadPart = now.QuadPart - base;
    return ok;
}

/* Milliseconds from the high-resolution counter, starting from Windows' own count (the Xbox's
   GetTickCount moves every millisecond; Windows' every 15.6). */
extern "C" DWORD WINAPI xpal_GetTickCount(void)
{
    static LONGLONG q0, freq;
    static DWORD t0;
    LARGE_INTEGER now;
    QueryPerformanceCounter(&now);
    if (!freq)
    {
        LARGE_INTEGER f;
        QueryPerformanceFrequency(&f);
        t0 = GetTickCount();
        q0 = now.QuadPart;
        freq = f.QuadPart;
    }
    return t0 + (DWORD)((now.QuadPart - q0) * 1000 / freq);
}

extern "C" VOID WINAPI xpal_OutputDebugStringA(LPCSTR text)
{
    if (text && text[0])
        plog("game: %s", text);
}

extern "C" DWORD WINAPI XGetDiskSectorSizeA(LPCSTR root)
{
    /* the disc's sectors; the hard disk's */
    return (root && (root[0] | 0x20) == 'd') ? 2048 : 512;
}
