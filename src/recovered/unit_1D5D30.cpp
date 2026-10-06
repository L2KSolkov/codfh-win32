// The network layer's debug print and its hook: the text formatted, sent to
// the debugger and the game's (empty) debug print, and to the hook set with
// sub_1D5DB0. Its original file name is not in the image, so it is named for
// its start address.

#include <stdio.h>
#include <stdarg.h>
#include <xtl.h>
#include "rw/ostypes.h"
#include "game/functions.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x0042CD14
// The debug print the network code calls through (this unit's sub_1D5D30).
void sub_1D5D30(const RwChar *arg_0, ...);
void (*off_42CD14)(const RwChar *arg_0, ...) = sub_1D5D30;
// 0x004FECF8
void (*dword_4FECF8)(const RwChar *arg_0);
// End of its data definitions.


// The hook (dword_4FECF8), 0 for none.
extern void (*dword_4FECF8)(const RwChar *arg_0);

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?off_42CD14@@3P6AXPBDZZA @ 0x0042CD14

#ifdef CODFH_WIN32
extern "C" void port_debug_vprint(const RwChar *arg_0, va_list arg_4);
#endif

// match: ?sub_1D5D30@@YAXPBDZZ @ 0x001D5D30

void sub_1D5D30(const RwChar *arg_0, ...)
{
    RwChar var_808[0x800];
    va_list var_4;

    va_start(var_4, arg_0);
#ifdef CODFH_WIN32
    // (the port's safe print: a bad argument prints a note; the text is printed once, not
    // handed to sub_19A750 as a format too)
    port_debug_vprint(arg_0, var_4);
    var_808[0] = 0;
    if (dword_4FECF8)
        _vsnprintf(var_808, sizeof(var_808) - 1, arg_0, var_4);
    var_808[sizeof(var_808) - 1] = 0;
    va_end(var_4);
#else
    vsprintf(var_808, arg_0, var_4);
    va_end(var_4);
    OutputDebugStringA(var_808);
    sub_19A750(var_808);
#endif
    if (dword_4FECF8)
        dword_4FECF8(var_808);
}

// match: ?sub_1D5DB0@@YAXP6AXPBD@Z@Z @ 0x001D5DB0
void sub_1D5DB0(void (*arg_0)(const RwChar *arg_0))
{
    dword_4FECF8 = arg_0;
}
