// An object whose code the original link dropped (/OPT:REF): only its data is in
// the image, at 0x3D8CA4-0x3D8CAC, between unit_0DC400's and unit_0E8F40's: the
// 16.666666 header constant of the game's other objects and the literal "/",
// which unit_1CA890's separator (sub_1CBB30) also uses: a same-named literal is
// the first object's, so it stays here.

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include <string.h>

// Its data definitions (PLAN M5), in the image's address order.
#ifndef CODFH_SP // MP only: single player has no unreferenced 16.666666f here: "/" follows sp_fendlang's texts (SP 0x2E4134)
// 0x003D8CA4
extern const RwReal flt_3D8CA4 = 16.666666f;
#endif
// End of its data definitions.

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3D8CA4@@3MB @ 0x003D8CA4
// match: ??_C@_01KMDKNFGN@?1?$AA@ @ 0x003D8CA8

// Not in the image: a stand-in for the dropped code that first used "/", so
// that it comes out here. Unreferenced.
void dropped_3D8CA8(RwChar *arg_0)
{
    strcat(arg_0, "/");
}
