/*
 * Crash reports for the port (docs/WIN32_PORT.md W8): an unhandled exception's code, address and
 * call stack, symbolized from codfh.pdb, go to codfh.log before the process ends.
 *
 * A crash dump is written beside the log too, before the report window opens
 * (codfh_crash_<date>_<time>.dmp; CODFH_CRASHDUMP=0 none, 1 the default, 2 the full one), and the
 * window's "Save full dump" writes the full one. Both open in Visual Studio or WinDbg with the
 * build's codfh.pdb (the dump records its GUID: a debugger takes only the matching one).
 *  - the default: every thread's stack and registers, codfh.exe's data and bss (the game's
 *    globals: its entity, trigger and HUD tables, the pack, the god asset manager; no other
 *    module's: the graphics driver's alone are over 20 MB), the memory the stacks point into, and
 *    what the globals point to: the heaps' blocks of at most 256 KB (the game's objects, pools and
 *    lists, its largest pool some 216 KB; not the bulk buffers: sound and animation memory, rasters,
 *    files read) and the other private writable regions of at most 256 KB, 128 MB in all (some 15 to
 *    20 MB at the front end); with the memory map, handles
 *    and thread times;
 *  - the full one: all private writable memory.
 * Each carries the last 64 KB of codfh.log as its comment (WinDbg shows it on opening), and is
 * packed with the whole log into codfh_crash_<date>_<time>.zip (Windows' own tar.exe; a dump
 * compresses some eight times: the default some 3 to 4 MB), the file to send.
 * CODFH_CRASHTEST=<seconds> crashes a thread of its own that long after the start, to try it.
 */
#include <windows.h>
#include <dbghelp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "port.h"

extern "C" const char codfh_git_rev[];  /* (gitrev.c beside the executable, written by tools/portbuild.py) */

static const char crash_window_class[] = "CODFHCrashDialog";

enum { ID_FULL_DUMP = 1002, ID_DUMP_TEXT = 1003 };

// ---- crash dumps ----

static EXCEPTION_POINTERS *crash_ep;
static DWORD crash_thread;

// the default dump's extra ranges (crash_regions, then the MemoryCallback hands them out)
enum { MAX_REGIONS = 65536, MAX_HEAP_SPANS = 1024 };
static struct { ULONG64 base; ULONG size; } regions[MAX_REGIONS];
static int region_count, region_next;
static SIZE_T region_total;
static struct { ULONG_PTR lo, hi; } heap_spans[MAX_HEAP_SPANS];   // the heaps' own regions
static int heap_span_count;
static const SIZE_T block_max = 256u << 10, total_max = 128u << 20;

// a range for the dump: joined to the last one when it follows it closely (a heap block's header)
static void add_range(ULONG_PTR base, SIZE_T size)
{
    if (!size || region_total + size > total_max)
        return;
    if (region_count && base >= regions[region_count - 1].base
        && base - (ULONG_PTR)(regions[region_count - 1].base + regions[region_count - 1].size) <= 256)
    {
        SIZE_T end = base + size - (ULONG_PTR)regions[region_count - 1].base;

        region_total += end - regions[region_count - 1].size;
        regions[region_count - 1].size = (ULONG)end;
        return;
    }
    if (region_count >= MAX_REGIONS)
        return;
    regions[region_count].base = base;
    regions[region_count].size = (ULONG)size;
    region_count++;
    region_total += size;
}

// The heaps' blocks of at most block_max, and their regions noted (the walk under __try: a heap the
// crash corrupted ends it, and what it found is kept).
static void heap_blocks(void)
{
    HANDLE heaps[64];
    DWORD n = GetProcessHeaps(64, heaps);

    for (DWORD h = 0; h < n && h < 64; h++)
    {
        PROCESS_HEAP_ENTRY e;

        e.lpData = NULL;
        __try
        {
            while (HeapWalk(heaps[h], &e))
            {
                if ((e.wFlags & PROCESS_HEAP_REGION) && heap_span_count < MAX_HEAP_SPANS)
                {
                    heap_spans[heap_span_count].lo = (ULONG_PTR)e.lpData;
                    heap_spans[heap_span_count].hi = (ULONG_PTR)e.Region.lpLastBlock;
                    heap_span_count++;
                }
                else if ((e.wFlags & PROCESS_HEAP_ENTRY_BUSY) && e.cbData <= block_max)
                    add_range((ULONG_PTR)e.lpData - e.cbOverhead, e.cbData + e.cbOverhead);
            }
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
        }
    }
}

static int in_heap(ULONG_PTR p)
{
    for (int i = 0; i < heap_span_count; i++)
        if (p >= heap_spans[i].lo && p < heap_spans[i].hi)
            return 1;
    return 0;
}

static void crash_regions(void)
{
    MEMORY_BASIC_INFORMATION mbi;
    char *p = NULL;

    region_count = region_next = 0;
    region_total = 0;
    heap_span_count = 0;
    heap_blocks();
    // the other private writable regions (VirtualAlloc'd pools and lists), not the heaps' own, nor
    // those above 2 GB (allocated from the top down: the graphics driver's command buffers)
    while (VirtualQuery(p, &mbi, sizeof(mbi)) == sizeof(mbi))
    {
        if (mbi.State == MEM_COMMIT && mbi.Type == MEM_PRIVATE && !(mbi.Protect & (PAGE_GUARD | PAGE_NOACCESS))
            && (mbi.Protect & (PAGE_READWRITE | PAGE_EXECUTE_READWRITE | PAGE_WRITECOPY)) && mbi.RegionSize <= block_max
            && (ULONG_PTR)mbi.BaseAddress < 0x80000000u && !in_heap((ULONG_PTR)mbi.BaseAddress))
            add_range((ULONG_PTR)mbi.BaseAddress, mbi.RegionSize);
        p = (char *)mbi.BaseAddress + mbi.RegionSize;
        if (!p)
            break;
    }
}

static HMODULE main_module;

static BOOL CALLBACK dump_callback(PVOID param, const PMINIDUMP_CALLBACK_INPUT in, PMINIDUMP_CALLBACK_OUTPUT out)
{
    if (!in || !out)
        return FALSE;
    switch (in->CallbackType)
    {
    case ModuleCallback:
        // (the default dump: data sections of codfh.exe only)
        if (param && (HMODULE)(ULONG_PTR)in->Module.BaseOfImage != main_module)
            out->ModuleWriteFlags &= ~ModuleWriteDataSeg;
        return TRUE;
    case MemoryCallback:
        // (the default dump's regions, one each time it asks)
        if (!param || region_next >= region_count)
            return FALSE;
        out->MemoryBase = regions[region_next].base;
        out->MemorySize = regions[region_next].size;
        region_next++;
        return TRUE;
    case CancelCallback:
        return FALSE;
    default:
        return TRUE;
    }
}

// the log's tail, the dump's comment
static char log_tail[64 * 1024 + 64];

static void read_log_tail(void)
{
    char path[MAX_PATH], *slash;
    HANDLE f;
    DWORD size, got = 0;

    strcpy(log_tail, "codfh.log (its last 64 KB):\n");
    GetModuleFileNameA(NULL, path, sizeof(path));
    slash = strrchr(path, '\\');
    if (slash)
        slash[1] = 0;
#ifdef CODFH_DEDICATED
    strcat(path, "codfh_server.log");
#else
    strcat(path, "codfh.log");
#endif
    f = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
    if (f == INVALID_HANDLE_VALUE)
        return;
    size = GetFileSize(f, NULL);
    if (size != INVALID_FILE_SIZE)
    {
        DWORD want = size > 64 * 1024 ? 64 * 1024 : size, at = (DWORD)strlen(log_tail);

        SetFilePointer(f, size - want, NULL, FILE_BEGIN);
        ReadFile(f, log_tail + at, want, &got, NULL);
        log_tail[at + got] = 0;
    }
    CloseHandle(f);
}

struct dump_job
{
    char path[MAX_PATH];
    int full;
    BOOL ok;
    DWORD error;
};

// (a thread of its own writes it: MiniDumpWriteDump walks the crashed thread best from outside it)
static DWORD WINAPI dump_thread(LPVOID arg)
{
    dump_job *job = (dump_job *)arg;
    MINIDUMP_EXCEPTION_INFORMATION mei;
    MINIDUMP_USER_STREAM stream;
    MINIDUMP_USER_STREAM_INFORMATION streams;
    MINIDUMP_CALLBACK_INFORMATION cb;
    MINIDUMP_TYPE type;
    HANDLE f;

    f = CreateFileA(job->path, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (f == INVALID_HANDLE_VALUE)
    {
        job->error = GetLastError();
        return 0;
    }
    mei.ThreadId = crash_thread;
    mei.ExceptionPointers = crash_ep;
    mei.ClientPointers = FALSE;
    stream.Type = CommentStreamA;
    stream.BufferSize = (ULONG)strlen(log_tail) + 1;
    stream.Buffer = log_tail;
    streams.UserStreamCount = 1;
    streams.UserStreamArray = &stream;
    cb.CallbackRoutine = dump_callback;
    cb.CallbackParam = job->full ? NULL : (PVOID)1;
    type = (MINIDUMP_TYPE)(MiniDumpWithDataSegs | MiniDumpWithHandleData | MiniDumpWithThreadInfo
                           | MiniDumpWithFullMemoryInfo | MiniDumpWithUnloadedModules
                           | (job->full ? MiniDumpWithPrivateReadWriteMemory : MiniDumpWithIndirectlyReferencedMemory));
    region_next = 0;
    job->ok = MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), f, type, crash_ep ? &mei : NULL, &streams,
                                &cb);
    if (!job->ok)
        job->error = GetLastError();
    CloseHandle(f);
    if (!job->ok)
        DeleteFileA(job->path);
    return 0;
}

// The dump and the whole log packed beside them as <dump>.zip (Windows' tar.exe, its zip format),
// within a minute; whether it was.
static BOOL zip_dump(const char *dmp, char *zip, size_t n)
{
    char dir[MAX_PATH], tar[MAX_PATH], cmd[3 * MAX_PATH + 64], *name, *dot;
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    DWORD code = 1;

    strncpy(dir, dmp, sizeof(dir) - 1);
    dir[sizeof(dir) - 1] = 0;
    name = strrchr(dir, '\\');
    if (!name)
        return FALSE;
    *name++ = 0;
    _snprintf(zip, n, "%s\\%s", dir, name);
    zip[n - 1] = 0;
    dot = strrchr(zip, '.');
    if (dot)
        strcpy(dot, ".zip");
    GetSystemDirectoryA(tar, sizeof(tar));
    strcat(tar, "\\tar.exe");
#ifdef CODFH_DEDICATED
    _snprintf(cmd, sizeof(cmd), "\"%s\" -a -c -f \"%s\" -C \"%s\" \"%s\" codfh_server.log", tar, zip, dir, name);
#else
    _snprintf(cmd, sizeof(cmd), "\"%s\" -a -c -f \"%s\" -C \"%s\" \"%s\" codfh.log", tar, zip, dir, name);
#endif
    cmd[sizeof(cmd) - 1] = 0;
    memset(&si, 0, sizeof(si));
    si.cb = sizeof(si);
    if (!CreateProcessA(tar, cmd, NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, dir, &si, &pi))
        return FALSE;
    if (WaitForSingleObject(pi.hProcess, 60000) == WAIT_OBJECT_0)
        GetExitCodeProcess(pi.hProcess, &code);
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
    if (code)
        DeleteFileA(zip);
    return code == 0;
}

// Writes the dump (full or the default) beside the log; its path, or why it failed, into result.
static BOOL write_dump(int full, char *result, size_t n)
{
    static dump_job job;
    char *slash;
    SYSTEMTIME t;
    HANDLE th;
    WIN32_FILE_ATTRIBUTE_DATA fa;

    GetLocalTime(&t);
    GetModuleFileNameA(NULL, job.path, sizeof(job.path));
    slash = strrchr(job.path, '\\');
    if (slash)
        slash[1] = 0;
    _snprintf(job.path + strlen(job.path), sizeof(job.path) - strlen(job.path),
              "codfh_crash_%04u%02u%02u_%02u%02u%02u%s.dmp", t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond,
              full ? "_full" : "");
    job.path[sizeof(job.path) - 1] = 0;
    job.full = full;
    job.ok = FALSE;
    job.error = 0;
    th = CreateThread(NULL, 0, dump_thread, &job, 0, NULL);
    if (th)
    {
        WaitForSingleObject(th, INFINITE);
        CloseHandle(th);
    }
    else
        dump_thread(&job);
    if (job.ok && GetFileAttributesExA(job.path, GetFileExInfoStandard, &fa))
    {
        char zip[MAX_PATH];

        if (zip_dump(job.path, zip, sizeof(zip)) && GetFileAttributesExA(zip, GetFileExInfoStandard, &fa))
            _snprintf(result, n, "%s dump, with the log: %s (%.1f MB)", full ? "Full" : "Crash", zip,
                      fa.nFileSizeLow / (1024.0 * 1024.0) + fa.nFileSizeHigh * 4096.0);
        else
            _snprintf(result, n, "%s dump: %s (%.1f MB)", full ? "Full" : "Crash", job.path,
                      fa.nFileSizeLow / (1024.0 * 1024.0) + fa.nFileSizeHigh * 4096.0);
    }
    else
        _snprintf(result, n, "%s dump failed (error %lu): %s", full ? "Full" : "Crash", job.error, job.path);
    result[n - 1] = 0;
    plog("crash: %s", result);
    return job.ok;
}

static int dump_mode(void)
{
    char v[8];

    return GetEnvironmentVariableA("CODFH_CRASHDUMP", v, sizeof(v)) ? atoi(v) : 1;
}

// CODFH_CRASHTEST: a thread that crashes after that many seconds
static DWORD WINAPI crash_test_thread(LPVOID arg)
{
    Sleep((DWORD)(ULONG_PTR)arg * 1000);
    plog("crash test: crashing on purpose (CODFH_CRASHTEST)");
    *(volatile int *)0 = 0;
    return 0;
}

// ---- the report window ----

static LRESULT CALLBACK crash_window_proc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
    if (message == WM_COMMAND && LOWORD(wparam) == ID_FULL_DUMP)
    {
        char result[MAX_PATH + 96];

        SetDlgItemTextA(hwnd, ID_DUMP_TEXT, "Writing the full dump...");
        EnableWindow(GetDlgItem(hwnd, ID_FULL_DUMP), FALSE);
        SetCursor(LoadCursor(NULL, IDC_WAIT));
        write_dump(1, result, sizeof(result));
        SetDlgItemTextA(hwnd, ID_DUMP_TEXT, result);
        return 0;
    }
    if (message == WM_COMMAND && LOWORD(wparam) == IDOK)
    {
        DestroyWindow(hwnd);
        return 0;
    }
    if (message == WM_CLOSE)
    {
        DestroyWindow(hwnd);
        return 0;
    }
    if (message == WM_KEYDOWN && wparam == VK_ESCAPE)
    {
        DestroyWindow(hwnd);
        return 0;
    }
    return DefWindowProcA(hwnd, message, wparam, lparam);
}

static void show_crash_dialog(DWORD code, const char *where, unsigned frame,
                              char trace[][512], int trace_count, const char *dump_text)
{
    WNDCLASSEXA wc;
    HWND owner = (HWND)port_hwnd;
    HWND hwnd, summary, list, close_button, dump_label, dump_button;
    HINSTANCE instance = GetModuleHandleA(NULL);
    RECT work;
    int width = 700, height = 520;
    int x, y;
    MSG msg;

    memset(&wc, 0, sizeof(wc));
    wc.cbSize = sizeof(wc);
    wc.lpfnWndProc = crash_window_proc;
    wc.hInstance = instance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
    wc.lpszClassName = crash_window_class;
    if (!RegisterClassExA(&wc) && GetLastError() != ERROR_CLASS_ALREADY_EXISTS)
    {
        MessageBoxA(owner, where, "Call of Duty: Finest Hour crashed", MB_OK | MB_ICONERROR | MB_TOPMOST);
        return;
    }

    char title[160];
    _snprintf(title, sizeof(title), "Call of Duty: Finest Hour - Crash Report (build %s)", codfh_git_rev);
    title[sizeof(title) - 1] = 0;
    hwnd = CreateWindowExA(WS_EX_DLGMODALFRAME | WS_EX_TOPMOST, crash_window_class, title,
                           WS_CAPTION | WS_SYSMENU | WS_CLIPCHILDREN,
                           CW_USEDEFAULT, CW_USEDEFAULT, width, height, owner, NULL, instance, NULL);
    if (!hwnd)
    {
        MessageBoxA(owner, where, "Call of Duty: Finest Hour crashed", MB_OK | MB_ICONERROR | MB_TOPMOST);
        return;
    }

    summary = CreateWindowExA(0, "STATIC", "The game encountered an unhandled exception. Stack trace:",
                              WS_CHILD | WS_VISIBLE | SS_LEFT, 14, 10, 656, 30,
                              hwnd, NULL, instance, NULL);
    list = CreateWindowExA(WS_EX_CLIENTEDGE, "LISTBOX", NULL,
                           WS_CHILD | WS_VISIBLE | WS_TABSTOP | LBS_NOINTEGRALHEIGHT,
                           14, 46, 656, 386, hwnd, (HMENU)1001, instance, NULL);
    close_button = CreateWindowExA(0, "BUTTON", "Close",
                                   WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_DEFPUSHBUTTON,
                                   574, 442, 96, 28, hwnd, (HMENU)IDOK, instance, NULL);
    dump_label = CreateWindowExA(0, "STATIC", dump_text, WS_CHILD | WS_VISIBLE | SS_LEFT | SS_PATHELLIPSIS,
                                 14, 442, 430, 28, hwnd, (HMENU)ID_DUMP_TEXT, instance, NULL);
    dump_button = CreateWindowExA(0, "BUTTON", "Save full dump", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON,
                                  452, 442, 112, 28, hwnd, (HMENU)ID_FULL_DUMP, instance, NULL);
    if (!summary || !list || !close_button)
    {
        DestroyWindow(hwnd);
        MessageBoxA(owner, where, "Call of Duty: Finest Hour crashed", MB_OK | MB_ICONERROR | MB_TOPMOST);
        return;
    }

    char detail[640];
    /* (the build on a line of its own: the commit a crash report is matched to) */
    _snprintf(detail, sizeof(detail), "Exception 0x%08lX at %s (frame %u)\nBuild %s", code, where, frame,
              codfh_git_rev);
    detail[sizeof(detail) - 1] = 0;
    SetWindowTextA(summary, detail);
    for (int i = 0; i < trace_count; i++)
        SendMessageA(list, LB_ADDSTRING, 0, (LPARAM)trace[i]);
    if (!trace_count)
        SendMessageA(list, LB_ADDSTRING, 0, (LPARAM)"<no stack frames were available>");
    SendMessageA(hwnd, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), TRUE);
    SendMessageA(summary, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), TRUE);
    SendMessageA(list, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), TRUE);
    SendMessageA(close_button, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), TRUE);
    if (dump_label)
        SendMessageA(dump_label, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), TRUE);
    if (dump_button)
        SendMessageA(dump_button, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), TRUE);
    if (owner)
        EnableWindow(owner, FALSE);
    SystemParametersInfoA(SPI_GETWORKAREA, 0, &work, 0);
    x = work.left + ((work.right - work.left) - width) / 2;
    y = work.top + ((work.bottom - work.top) - height) / 2;
    SetWindowPos(hwnd, HWND_TOPMOST, x, y, width, height, SWP_SHOWWINDOW);
    SetForegroundWindow(hwnd);
    SetFocus(list);

    while (IsWindow(hwnd) && GetMessageA(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }
    if (owner)
    {
        EnableWindow(owner, TRUE);
        SetForegroundWindow(owner);
    }
}

static void describe(DWORD64 addr, char *out, size_t n)
{
    HANDLE proc = GetCurrentProcess();
    char buf[sizeof(SYMBOL_INFO) + 256];
    SYMBOL_INFO *sym = (SYMBOL_INFO *)buf;
    sym->SizeOfStruct = sizeof(SYMBOL_INFO);
    sym->MaxNameLen = 255;
    DWORD64 disp = 0;
    IMAGEHLP_LINE64 line;
    line.SizeOfStruct = sizeof(line);
    DWORD ldisp = 0;
    if (SymFromAddr(proc, addr, &disp, sym))
    {
        if (SymGetLineFromAddr64(proc, addr, &ldisp, &line))
            _snprintf(out, n, "%08llX %s+0x%llX (%s:%lu)", addr, sym->Name, disp, line.FileName, line.LineNumber);
        else
            _snprintf(out, n, "%08llX %s+0x%llX", addr, sym->Name, disp);
    }
    else
        _snprintf(out, n, "%08llX", addr);
    out[n - 1] = 0;
}

static LONG WINAPI on_crash(EXCEPTION_POINTERS *ep)
{
    static volatile LONG once;
    if (InterlockedExchange(&once, 1))
        return EXCEPTION_CONTINUE_SEARCH;
    HANDLE proc = GetCurrentProcess(), thread = GetCurrentThread();
    SymSetOptions(SYMOPT_LOAD_LINES | SYMOPT_DEFERRED_LOADS | SYMOPT_UNDNAME);
    SymInitialize(proc, NULL, TRUE);
    EXCEPTION_RECORD *er = ep->ExceptionRecord;
    char where[512];
    describe((DWORD64)(ULONG_PTR)er->ExceptionAddress, where, sizeof(where));
    plog("CRASH: exception 0x%08lX at %s, frame %u, build %s", er->ExceptionCode, where, port_frame, codfh_git_rev);
    if (er->ExceptionCode == EXCEPTION_ACCESS_VIOLATION && er->NumberParameters >= 2)
        plog("  %s address %08lX", er->ExceptionInformation[0] ? "writing" : "reading",
             (unsigned long)er->ExceptionInformation[1]);
    CONTEXT ctx = *ep->ContextRecord;
    plog("  eax %08lX ebx %08lX ecx %08lX edx %08lX esi %08lX edi %08lX ebp %08lX esp %08lX", ctx.Eax, ctx.Ebx,
         ctx.Ecx, ctx.Edx, ctx.Esi, ctx.Edi, ctx.Ebp, ctx.Esp);
    STACKFRAME64 sf;
    memset(&sf, 0, sizeof(sf));
    sf.AddrPC.Offset = ctx.Eip;
    sf.AddrPC.Mode = AddrModeFlat;
    sf.AddrFrame.Offset = ctx.Ebp;
    sf.AddrFrame.Mode = AddrModeFlat;
    sf.AddrStack.Offset = ctx.Esp;
    sf.AddrStack.Mode = AddrModeFlat;
    char trace[40][512];
    int trace_count = 0;
    for (int i = 0; i < 40; i++)
    {
        if (!StackWalk64(IMAGE_FILE_MACHINE_I386, proc, thread, &sf, &ctx, NULL, SymFunctionTableAccess64,
                         SymGetModuleBase64, NULL) || !sf.AddrPC.Offset)
            break;
        describe(sf.AddrPC.Offset, trace[trace_count], sizeof(trace[trace_count]));
        plog("  #%02d %s", i, trace[trace_count]);
        trace_count++;
    }
    // (the dump: the default, or the full one, or none, CODFH_CRASHDUMP)
    char dump_text[MAX_PATH + 96];
    int mode = dump_mode();

    crash_ep = ep;
    crash_thread = GetCurrentThreadId();
    main_module = GetModuleHandleA(NULL);
    read_log_tail();
    if (mode)
    {
        if (mode != 2)
            crash_regions();
        write_dump(mode == 2, dump_text, sizeof(dump_text));
    }
    else
        strcpy(dump_text, "No crash dump written (CODFH_CRASHDUMP=0).");
    show_crash_dialog(er->ExceptionCode, where, port_frame, trace, trace_count, dump_text);
    return EXCEPTION_CONTINUE_SEARCH;
}

extern "C" void port_crash_handler_install(void)
{
    char v[16];

    SetUnhandledExceptionFilter(on_crash);
    if (GetEnvironmentVariableA("CODFH_CRASHTEST", v, sizeof(v)) && atoi(v) > 0)
    {
        HANDLE th = CreateThread(NULL, 0, crash_test_thread, (LPVOID)(ULONG_PTR)atoi(v), 0, NULL);

        if (th)
            CloseHandle(th);
    }
}
