/*
 * Crash reports for the port (docs/WIN32_PORT.md W8): an unhandled exception's code, address and
 * call stack, symbolized from codfh.pdb, go to codfh.log before the process ends.
 */
#include <windows.h>
#include <dbghelp.h>
#include <stdio.h>

#include "port.h"

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
    for (int i = 0; i < 40; i++)
    {
        if (!StackWalk64(IMAGE_FILE_MACHINE_I386, proc, thread, &sf, &ctx, NULL, SymFunctionTableAccess64,
                         SymGetModuleBase64, NULL) || !sf.AddrPC.Offset)
            break;
        describe(sf.AddrPC.Offset, where, sizeof(where));
        plog("  #%02d %s", i, where);
    }
    return EXCEPTION_CONTINUE_SEARCH;
}

extern "C" void port_crash_handler_install(void)
{
    SetUnhandledExceptionFilter(on_crash);
}
