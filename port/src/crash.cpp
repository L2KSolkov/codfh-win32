/*
 * Crash reports for the port (docs/WIN32_PORT.md W8): an unhandled exception's code, address and
 * call stack, symbolized from codfh.pdb, go to codfh.log before the process ends.
 */
#include <windows.h>
#include <dbghelp.h>
#include <stdio.h>

#include "port.h"

static const char crash_window_class[] = "CODFHCrashDialog";

static LRESULT CALLBACK crash_window_proc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
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
                              char trace[][512], int trace_count)
{
    WNDCLASSEXA wc;
    HWND owner = (HWND)port_hwnd;
    HWND hwnd, summary, list, close_button;
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

    hwnd = CreateWindowExA(WS_EX_DLGMODALFRAME | WS_EX_TOPMOST, crash_window_class,
                           "Call of Duty: Finest Hour - Crash Report",
                           WS_CAPTION | WS_SYSMENU | WS_CLIPCHILDREN,
                           CW_USEDEFAULT, CW_USEDEFAULT, width, height, owner, NULL, instance, NULL);
    if (!hwnd)
    {
        MessageBoxA(owner, where, "Call of Duty: Finest Hour crashed", MB_OK | MB_ICONERROR | MB_TOPMOST);
        return;
    }

    summary = CreateWindowExA(0, "STATIC", "The game encountered an unhandled exception. Stack trace:",
                              WS_CHILD | WS_VISIBLE | SS_LEFT, 14, 12, 650, 24,
                              hwnd, NULL, instance, NULL);
    list = CreateWindowExA(WS_EX_CLIENTEDGE, "LISTBOX", NULL,
                           WS_CHILD | WS_VISIBLE | WS_TABSTOP | LBS_NOINTEGRALHEIGHT,
                           14, 42, 656, 390, hwnd, (HMENU)1001, instance, NULL);
    close_button = CreateWindowExA(0, "BUTTON", "Close",
                                   WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_DEFPUSHBUTTON,
                                   574, 442, 96, 28, hwnd, (HMENU)IDOK, instance, NULL);
    if (!summary || !list || !close_button)
    {
        DestroyWindow(hwnd);
        MessageBoxA(owner, where, "Call of Duty: Finest Hour crashed", MB_OK | MB_ICONERROR | MB_TOPMOST);
        return;
    }

    char detail[640];
    _snprintf(detail, sizeof(detail), "Exception 0x%08lX at %s (frame %u)", code, where, frame);
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
    plog("CRASH: exception 0x%08lX at %s, frame %u", er->ExceptionCode, where, port_frame);
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
    show_crash_dialog(er->ExceptionCode, where, port_frame, trace, trace_count);
    return EXCEPTION_CONTINUE_SEARCH;
}

extern "C" void port_crash_handler_install(void)
{
    SetUnhandledExceptionFilter(on_crash);
}
