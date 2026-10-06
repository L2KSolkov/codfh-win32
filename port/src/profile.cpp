/*
 * A sampling profiler for slow frames (CODFH_PROFILE=1): a thread looks at the game's thread
 * every millisecond (its program counter and a few callers, from its frame pointers), and a frame whose
 * work took over 25 ms (d3d8_bridge.cpp's slow-frame log) gets the functions its samples fell in,
 * most first, in the log: the first one in the game's executable, and where the thread actually
 * was when that is a library's or the system's.
 */
#include <windows.h>
#include <dbghelp.h>
#include <stdio.h>
#include <string.h>

#include "port.h"

/* (the port's counter, which the slow-frame log's times come from: port/include/xtl.h) */
extern "C" BOOL WINAPI xpal_QueryPerformanceCounter(LARGE_INTEGER *count);

enum { RING = 16384, DEPTH = 6 };
struct Sample
{
    LONGLONG t;
    DWORD pc[DEPTH];
};
static Sample ring[RING];
static volatile LONG ring_at;
static HANDLE game_thread, sampler;
static CRITICAL_SECTION dbghelp_lock;
static DWORD exe_lo, exe_hi;
static volatile int running;

static DWORD WINAPI sample_loop(void *)
{
    HANDLE proc = GetCurrentProcess();
    while (running)
    {
        Sleep(1);
        if (SuspendThread(game_thread) == (DWORD)-1)
            continue;
        CONTEXT ctx;
        memset(&ctx, 0, sizeof(ctx));
        ctx.ContextFlags = CONTEXT_CONTROL | CONTEXT_INTEGER;
        Sample s;
        memset(&s, 0, sizeof(s));
        /* (no dbghelp here, nor anything else that allocates or locks: the game's thread may be
           holding the heap's lock while it is suspended; the frame pointers are walked by hand,
           the port and the system keeping them) */
        if (GetThreadContext(game_thread, &ctx))
        {
            s.pc[0] = ctx.Eip;
            DWORD ebp = ctx.Ebp;
            __try
            {
                for (int i = 1; i < DEPTH && ebp && !(ebp & 3) && ebp >= ctx.Esp && ebp - ctx.Esp < 0x100000; i++)
                {
                    DWORD next = ((const DWORD *)(ULONG_PTR)ebp)[0];
                    s.pc[i] = ((const DWORD *)(ULONG_PTR)ebp)[1];
                    if (next <= ebp)
                        break;
                    ebp = next;
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
        }
        ResumeThread(game_thread);
        LARGE_INTEGER now;
        xpal_QueryPerformanceCounter(&now);
        s.t = now.QuadPart;
        LONG at = InterlockedIncrement(&ring_at) % RING;
        ring[at] = s;
    }
    return 0;
}

/* Starts sampling the calling thread (the game's) when CODFH_PROFILE is set. */
extern "C" void port_profile_start(void)
{
    char v[8];
    if (running || !GetEnvironmentVariableA("CODFH_PROFILE", v, sizeof(v)))
        return;
    InitializeCriticalSection(&dbghelp_lock);
    HANDLE proc = GetCurrentProcess();
    SymSetOptions(SYMOPT_LOAD_LINES | SYMOPT_DEFERRED_LOADS | SYMOPT_UNDNAME);
    SymInitialize(proc, NULL, TRUE);
    DuplicateHandle(proc, GetCurrentThread(), proc, &game_thread, THREAD_ALL_ACCESS, FALSE, 0);
    HMODULE exe = GetModuleHandleA(NULL);
    IMAGE_NT_HEADERS *nt = (IMAGE_NT_HEADERS *)((BYTE *)exe + ((IMAGE_DOS_HEADER *)exe)->e_lfanew);
    exe_lo = (DWORD)(ULONG_PTR)exe;
    exe_hi = exe_lo + nt->OptionalHeader.SizeOfImage;
    running = 1;
    sampler = CreateThread(NULL, 0, sample_loop, NULL, 0, NULL);
    SetThreadPriority(sampler, THREAD_PRIORITY_TIME_CRITICAL);
    plog("profile: sampling the game's thread every millisecond");
}

static void name_of(DWORD pc, char *out, size_t n)
{
    char buf[sizeof(SYMBOL_INFO) + 256];
    SYMBOL_INFO *sym = (SYMBOL_INFO *)buf;
    memset(buf, 0, sizeof(buf));
    sym->SizeOfStruct = sizeof(SYMBOL_INFO);
    sym->MaxNameLen = 255;
    DWORD64 disp = 0;
    if (SymFromAddr(GetCurrentProcess(), pc, &disp, sym))
        _snprintf(out, n, "%s", sym->Name);
    else
        _snprintf(out, n, "%08lX", pc);
    out[n - 1] = 0;
}

struct Count
{
    char name[160];
    int n;
};

/* The samples between start and end (performance counts), by function, into the log. */
extern "C" void port_profile_report(LONGLONG start, LONGLONG end)
{
    if (!running)
        return;
    static Count counts[64];
    int ncounts = 0, total = 0;
    EnterCriticalSection(&dbghelp_lock);
    LONG last = ring_at;
    for (LONG k = 0; k < RING; k++)
    {
        const Sample &s = ring[(last - k + RING) % RING];
        if (!s.t || s.t < start)
            break;
        if (s.t > end)
            continue;
        total++;
        /* the first frame in the game's executable, with the top one when that is elsewhere */
        char name[160] = "?", top[96] = "";
        int game = -1;
        for (int i = 0; i < DEPTH && s.pc[i]; i++)
            if (s.pc[i] >= exe_lo && s.pc[i] < exe_hi)
            {
                game = i;
                break;
            }
        if (game >= 0)
            name_of(s.pc[game], name, sizeof(name));
        if (game != 0 && s.pc[0])
        {
            name_of(s.pc[0], top, sizeof(top));
            size_t n = strlen(name);
            _snprintf(name + n, sizeof(name) - n, " (in %s)", top);
            name[sizeof(name) - 1] = 0;
        }
        int j = 0;
        while (j < ncounts && strcmp(counts[j].name, name))
            j++;
        if (j == ncounts && ncounts < 64)
        {
            strcpy(counts[ncounts].name, name);
            counts[ncounts++].n = 0;
        }
        if (j < ncounts)
            counts[j].n++;
    }
    LeaveCriticalSection(&dbghelp_lock);
    for (int a = 0; a < ncounts; a++)
        for (int b = a + 1; b < ncounts; b++)
            if (counts[b].n > counts[a].n)
            {
                Count t = counts[a];
                counts[a] = counts[b];
                counts[b] = t;
            }
    for (int a = 0; a < ncounts && a < 6; a++)
        plog("  %3d of %d samples: %s", counts[a].n, total, counts[a].name);
}
