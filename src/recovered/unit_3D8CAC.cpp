// An object whose code the original link dropped (/OPT:REF): only its data is in
// the image, at 0x3D8CAC-0x3D8CC0, between unit_3D8CA4's and unit_0E8800's: the
// 16.666666 header constant of the game's other objects and the literal
// "SHELL\\FONTS\\", which the loading screen's set-up (type_4B8EF0::sub_E9790,
// unit_0E8F40) also uses: a same-named literal is the first object's, so it
// stays here.

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "rw/rt2d.h"
#include "game/gameloop.h"

// Its data definitions (PLAN M5), in the image's address order.
#ifndef CODFH_SP // MP only: single player has no unreferenced 16.666666f here: the fonts path follows sp_fendbase's vtable (SP 0x2E4154)
// 0x003D8CAC
extern const RwReal flt_3D8CAC = 16.666666f;
#endif
// End of its data definitions.

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3D8CAC@@3MB @ 0x003D8CAC
// match: ??_C@_0N@GJJPGDED@SHELL?2FONTS?2?$AA@ @ 0x003D8CB0

// Not in the image: a stand-in for the dropped code that first used the fonts'
// folder (setting the 2D font path, as sub_E9790 does), so that it comes out
// here. Unreferenced.
void dropped_3D8CB0(RwChar *arg_0)
{
    sub_D7F20(arg_0, "SHELL\\FONTS\\");
    Rt2dFontSetPath(arg_0);
}
