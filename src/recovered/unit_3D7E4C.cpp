// An object whose code the original link dropped (/OPT:REF): only its data is in
// the image, at 0x3D7E4C-0x3D7E78, between unit_0D99F0's and unit_0D9CF0's. It
// starts with the 16.666666 header constant of the game's other objects, then the
// literals "r" and "Failed to get OS file interface.\n", which unit_188380's text
// map reader (sub_18A890) also uses: a same-named literal is the first object's,
// so they stay here.

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "rw/osintf.h"
#include <stdio.h>
#ifdef CODFH_WIN32
// (the port: the game's printf prints, which the Xbox showed on its debug output, to the log)
extern "C" void port_debug_print(const RwChar *fmt, ...);
#define printf port_debug_print
#endif

// Its data definitions (PLAN M5), in the image's address order.
// 0x003D7E4C
extern const RwReal flt_3D7E4C = 16.666666f;
// End of its data definitions.

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3D7E4C@@3MB @ 0x003D7E4C
// match: ??_C@_01KDCPPGHE@r?$AA@ @ 0x003D7E50
// match: ??_C@_0CC@HGMBGKGF@Failed?5to?5get?5OS?5file?5interface?4@ @ 0x003D7E54

// Not in the image: a stand-in for the dropped code that first used the two
// literals (opening a file for reading through the OS file interface, as
// sub_18A890 does), so that they come out here in the image's order (a
// function's literals come out last-referenced first). Unreferenced.
void *dropped_3D7E50(const RwChar *arg_0)
{
    RwFileFunctions *lv_4;

    lv_4 = RwOsGetFileInterface();
    if (!lv_4 || !lv_4->rwfopen)
    {
        printf("Failed to get OS file interface.\n");
        return 0;
    }
    return lv_4->rwfopen(arg_0, "r");
}
