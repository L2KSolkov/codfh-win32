// The animated background entity (type_3D32F8, "AnimatedBGEntity"): its
// spawn, set-up and handlers. The file's original name is not recovered
// (M1), so it is named for its start address.

#include "types/type_3DA6C0.h"
#include "game/clumpdata.h"
#include <stdio.h>
#include <xmmintrin.h>
#include "rw/ostypes.h"
#include "game/functions.h"
#include "types/type_3D3548.h"
#include "types/type_3D32F8.h"
#include "types/type_439E78.h"
#include "types/alfaobject.h"
#include "game/data.h"
#include "rw/bavector.h"
#include "rw/baframe.h"
#include "rw/rprandom.h"
#include <string.h>
#include <math.h>
#include "game/frand.h"
#include "types/type_10F710.h"
#include "types/type_3DAFC8.h"
#include "types/type_3DBC78.h"
#include "types/type_3D2E7C.h"
#include "types/type_72810.h"
#include "types/type_92430.h"
#include "types/type_DC400.h"
#include "types/animbank.h"
#include "types/type_3D51C0.h"
#include "types/soundbank.h"
#include "types/type_4B85F8.h"
#include "game/vecutil.h"
#include "rw/rphanim.h"
#include "game/pooledconsts.h"
#include "types/type_4B9E90.h"
#include "game/frames.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003D3280
extern const RwV3d stru_3D3280 = { 0.0f, 0.0f, 1.0f };
// 0x003D328C
extern const RwReal flt_3D328C = 16.666666f;
// 0x00428BE0
#ifndef CODFH_SP // MP only: the five-way blend's (sub_76960; single player has none, and default.xbe has no { 0.2f, 0.03f, 0 })
type_428BE0 unk_428BE0 = { 0.2f, 0.03f, 0 };
#endif
// 0x00449B68
RwReal flt_449B68[5];
// 0x00449B7C
RwReal flt_449B7C;
// 0x00449B80
RwReal flt_449B80;
// 0x00449B84
RwReal flt_449B84;
// 0x00449B88
RwReal flt_449B88;
// End of its data definitions.



// The axis the entity turns about (0, 0, 1).
extern const RwV3d stru_3D3280;

// A magnitude: a macro with no name in the image, named for what it gives.
// Evidence: its argument is not parenthesised where it is negated, so
// ABS(a - b) negates only a (sub_74A30: fld a; fchs; fsub b); the other arm
// is a cast, evaluated rather than copied (fld, fstp even for a plain
// field).
#define ABS(x) ((x) < 0 ? -x : (RwReal)(x))

// Keeps v within lo and hi: a macro with no name in the image, named for what
// it does. Evidence: vf_03C compares with and assigns a field bound through
// the FPU (fld v; fld hi; fcompp; fld hi; fstp v), as a cast arm is.
// A float's magnitude through the C library: an inline with no address and
// so no database name, named for what it gives. Evidence: sub_75EC0 copies
// its argument into a temporary before converting it for fabs, and keeps
// the result in another (fst) before comparing it.
inline RwReal absf(RwReal x)
{
    return (RwReal)fabs(x);
}

#define CLAMP(v, lo, hi)     if ((v) > (RwReal)(hi))         (v) = (RwReal)(hi);     else if ((v) < (RwReal)(lo))         (v) = (RwReal)(lo)

// Vtables (.rdata, PLAN M5): each in its own placement range (config/splits.txt).
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?stru_3D3280@@3URwV3d@@B @ 0x003D3280
// match: ?flt_3D328C@@3MB @ 0x003D328C
// match: ??_C@_0GI@PONPIBCO@WARNING?3?5A?5spawn?5could?5not?5be?5cr@ @ 0x003D3290
// match: ??_7type_3D32F8@@6B@ @ 0x003D32F8
// match: ??_7type_3D3548@@6B@ @ 0x003D3548
// match: ??_C@_0BB@OHHGHJDD@AnimatedBGEntity?$AA@ @ 0x003D377C
// match: ??_C@_0IC@PCMDLGGG@No?5atMT?5attach?5locator?5found?5to?5@ @ 0x003D3790
// match: ??_C@_09KDBKJCNL@Destroyed?$AA@ @ 0x003D3814
// match: ??_C@_0P@KIMIDIP@HitByBulletRWS?$AA@ @ 0x003D3820
// match: ??_C@_0M@IFADELBH@HitByBullet?$AA@ @ 0x003D3830
// match: ??_C@_0BO@EFCOKONH@CollisionByPlayerNotification?$AA@ @ 0x003D383C
// match: ??_C@_0BO@NKELEHMB@CollisionByEntityNotification?$AA@ @ 0x003D385C
// match: ??_C@_0BC@EEIPHDNN@HitByExplosionRWS?$AA@ @ 0x003D387C
// match: ??_C@_0P@EGAKCHIF@HitByExplosion?$AA@ @ 0x003D3890
// match: __real@bfc00000 @ 0x003D38A0
// match: __real@41c80000 @ 0x003D38A4
// match: __real@41400000 @ 0x003D38A8
// match: __ehhandler$?sub_73710@@YAPAUtype_3D32F8@@PAUtype_712B0@@@Z>1>8 @ 0x0041B568
// match: __ehhandler$?sub_73710@@YAPAUtype_3D32F8@@PAUtype_712B0@@@Z>1 @ 0x0041B580
// match: __ehhandler$??1type_3D3548@@UAE@XZ>1>8 @ 0x0041B59C
// match: __ehhandler$??1type_3D3548@@UAE@XZ>1 @ 0x0041B604
// match: __ehhandler$??1type_129940@@QAE@XZ>1>8 @ 0x0041B620
// match: __ehhandler$??1type_129940@@QAE@XZ>1 @ 0x0041B628
// match: __ehhandler$??1type_1294D0@@QAE@XZ>1>8 @ 0x0041B644
// match: __ehhandler$??1type_1294D0@@QAE@XZ>1 @ 0x0041B64C
// match: __ehhandler$??1type_129B10@@QAE@XZ>1>8 @ 0x0041B668
// match: __ehhandler$??1type_129B10@@QAE@XZ>1 @ 0x0041B670
// match: __ehhandler$??1type_3D32F8@@UAE@XZ>1>8 @ 0x0041B68C
// match: __ehhandler$??1type_3D32F8@@UAE@XZ>1 @ 0x0041B69C
// match: ?unk_428BE0@@3Utype_428BE0@@A @ 0x00428BE0

// match: ?sub_73710@@YAPAUtype_3D32F8@@PAUtype_712B0@@@Z @ 0x00073710
// match: __ehhandler$?sub_73710@@YAPAUtype_3D32F8@@PAUtype_712B0@@@Z-0x27 @ 0x002FF8C0
// match: __ehhandler$?sub_73710@@YAPAUtype_3D32F8@@PAUtype_712B0@@@Z @ 0x002FF8E7
// sp-match: ?sub_73710@@YAPAUtype_3D32F8@@PAUtype_712B0@@@Z @ 0x000620E0
// (its constructor, defined in the class: single player calls its out-of-line copy)
// sp-match: ??0type_3D32F8@@QAE@PAUtype_712B0@@@Z @ 0x00061EE0

// Builds the entity for the trigger arg_0, or warns that there is no
// entity memory for it.
type_3D32F8 *sub_73710(type_712B0 *arg_0)
{
    type_3D32F8 *var_10;

#ifdef CODFH_SP // single player's entity is 0x460 bytes (SP 0x620E0)
    var_10 = (type_3D32F8 *)sub_D56D0(0x460, arg_0->unk_24_18, arg_0->vf_008());
#else
    var_10 = (type_3D32F8 *)sub_D56D0(0x490, arg_0->unk_24_18, arg_0->vf_008());
#endif
    if (var_10 != 0) {
        var_10 = new (var_10) type_3D32F8(arg_0);
        if (var_10->unk_28 & 0x400000) { // not an address: entity flag
            sub_D5A60(var_10, 0);
            var_10 = 0;
        }
    }
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS) // single player compiles the debug print out (SP 0x620E0)
    else
        sub_19A750("WARNING: A spawn could not be created due to lack of entity memory. Trigger "
                   "location(%6.2f,%6.2f,%6.2f)",
                   arg_0->unk_90, arg_0->unk_94, arg_0->unk_98);
#endif
    return var_10;
}

// match: ??1type_3D3548@@UAE@XZ @ 0x00073850
// match: __ehhandler$??1type_3D3548@@UAE@XZ-0xA2 @ 0x002FF900
// match: __ehhandler$??1type_3D3548@@UAE@XZ @ 0x002FF9A2
// sp-match: ??1type_3D3548@@UAE@XZ @ 0x00061C40
// (Defined in the class, in type_3D3548.h: vf_230, called directly as in
// any destructor, then the members' destructors from unk_35C down to
// unk_1C0; out of line here for type_3D32F8's unwinding.)

// match: ??1type_129B10@@QAE@XZ @ 0x00073A10
// match: __ehhandler$??1type_129B10@@QAE@XZ-0x8 @ 0x002FF9B0
// match: __ehhandler$??1type_129B10@@QAE@XZ @ 0x002FF9B8
// match: ??1type_129940@@QAE@XZ @ 0x00073A70
// match: ??1type_1294D0@@QAE@XZ @ 0x00073AD0
// match: ??1type_144940@@QAE@XZ @ 0x00073B30
// sp-match: ??1type_129940@@QAE@XZ @ 0x00061BF0
// (The holders' destructors, defined in their structs in type_129_base.h;
// out of line here for the destructor's unwinding. The three with an empty
// base share one handler, folded by /OPT:ICF.)

// The base's inline virtual defaults, out of line here (each serves both
// type_3D3548's and type_3D32F8's vtables; /OPT:ICF folded the identical
// ones into one body, so one definition stands for each).

// match: ?vf_07C@type_3D3548@@UAEHCPAURpIntersection@@PAMH@Z @ 0x00073B50
// sp-match: ?vf_07C@type_3D3548@@UAEHCPAURpIntersection@@PAMH@Z @ 0x00061D50
RwInt32 type_3D3548::vf_07C(RwInt8 arg_0, RpIntersection *arg_4, RwReal *arg_8, RwInt32 arg_C)
{
    return 0;
}

// match: ?vf_08C@type_3D3548@@UAEPAEHH@Z @ 0x00073B60
// sp-match: ?vf_08C@type_3D3548@@UAEPAEHH@Z @ 0x0012AE50
RwUInt8 *type_3D3548::vf_08C(RwInt32 arg_0, RwInt32 arg_4)
{
    return 0;
}

// match: ?vf_0E4@type_3D3548@@UAEHH@Z @ 0x00073B70
// sp-match: ?vf_0E4@type_3D3548@@UAEHH@Z @ 0x00061D60
RwInt32 type_3D3548::vf_0E4(RwInt32 arg_0)
{
    return -1;
}

// match: ?vf_0FC@type_3D3548@@UAEMXZ @ 0x00073B80
// sp-match: ?vf_0FC@type_3D3548@@UAEMXZ @ 0x00061D80
// Also vf_100.
RwReal type_3D3548::vf_0FC()
{
    return 1.0f;
}

// match: ?vf_134@type_3D3548@@UAEHPAURwV3d@@PAU1@HHPAH2H@Z @ 0x00073BA0
// sp-match: ?vf_134@type_3D3548@@UAEHPAURwV3d@@PAU1@HHPAH2H@Z @ 0x00061D90
RwInt32 type_3D3548::vf_134(RwV3d *arg_0, type_3D3548 *arg_4, RwInt32 arg_8, RwInt32 arg_C,
                            RwInt32 *arg_10, RwInt32 *arg_14, RwInt32 arg_18)
{
    return 1;
}

// match: ?vf_10C@type_3D3548@@UAEMXZ @ 0x00073BC0
// Also vf_114, vf_130, vf_144 to vf_158, vf_164, vf_168, vf_17C, vf_1E0,
// vf_1F0 and vf_1F4.
RwReal type_3D3548::vf_10C()
{
    return 0.0f;
}

// match: ?vf_184@type_3D3548@@UAEHXZ @ 0x00073BE0
// sp-match: ?vf_184@type_3D3548@@UAEHXZ @ 0x00061DB0
RwInt32 type_3D3548::vf_184()
{
    return unk_350;
}

// match: ?vf_188@type_3D3548@@UAEXH@Z @ 0x00073C00
// sp-match: ?vf_188@type_3D3548@@UAEXH@Z @ 0x00061DC0
void type_3D3548::vf_188(RwInt32 arg_0)
{
    unk_350 = arg_0;
}

// match: ?vf_194@type_3D3548@@UAEXH@Z @ 0x00073C20
// sp-match: ?vf_194@type_3D3548@@UAEXH@Z @ 0x00061DD0
void type_3D3548::vf_194(RwInt32 arg_0)
{
    unk_28_15 = arg_0;
}

// match: ?vf_198@type_3D3548@@UAEXH@Z @ 0x00073C50
// sp-match: ?vf_198@type_3D3548@@UAEXH@Z @ 0x00061DF0
void type_3D3548::vf_198(RwInt32 arg_0)
{
    unk_28_23 = arg_0;
}

// match: ?vf_19C@type_3D3548@@UAEXH@Z @ 0x00073C80
// sp-match: ?vf_19C@type_3D3548@@UAEXH@Z @ 0x00061E10
void type_3D3548::vf_19C(RwInt32 arg_0)
{
    unk_28_24 = arg_0;
}

// match: ?vf_1B8@type_3D3548@@UAEXH@Z @ 0x00073CB0
// sp-match: ?vf_1B8@type_3D3548@@UAEXH@Z @ 0x00061E30
void type_3D3548::vf_1B8(RwInt32 arg_0)
{
    unk_28_6 = arg_0;
}

// match: ?vf_1BC@type_3D3548@@UAEXH@Z @ 0x00073CE0
// sp-match: ?vf_1BC@type_3D3548@@UAEXH@Z @ 0x00061E50
void type_3D3548::vf_1BC(RwInt32 arg_0)
{
    unk_88_13 = arg_0;
}

// match: ?vf_1D4@type_3D3548@@UAEHXZ @ 0x00073D10
// sp-match: ?vf_1D4@type_3D3548@@UAEHXZ @ 0x00061E70
RwInt32 type_3D3548::vf_1D4()
{
    return unk_290;
}

// match: ?vf_1D8@type_3D3548@@UAEXH@Z @ 0x00073D30
// sp-match: ?vf_1D8@type_3D3548@@UAEXH@Z @ 0x00061E80
void type_3D3548::vf_1D8(RwInt32 arg_0)
{
    unk_28_16 = arg_0;
}

// match: ?vf_1F8@type_3D3548@@UAEPAU1@H@Z @ 0x00073D60
// sp-match: ?vf_1F8@type_3D3548@@UAEPAU1@H@Z @ 0x00061EA0
type_3D3548 *type_3D3548::vf_1F8(RwInt32 arg_0)
{
    return unk_35C[arg_0].sub_D4910();
}

// match: ?vf_204@type_3D3548@@UAEXHHH@Z @ 0x00073D80
// sp-match: ?vf_204@type_3D3548@@UAEXHHH@Z @ 0x000FEB20
// Also vf_218 (the same empty body, folded by /OPT:ICF).
void type_3D3548::vf_204(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
}

// match: ?vf_0B0@type_3D3548@@UAEXHH@Z @ 0x00073D90
// sp-match: ?vf_0B0@type_3D3548@@UAEXHH@Z @ 0x0007C260
// Also vf_0EC and vf_220.
void type_3D3548::vf_0B0(RwInt32 arg_0, RwInt32 arg_4)
{
}

// match: ??_Gtype_3D3548@@UAEPAXI@Z @ 0x00073DA0
// sp-match: ??_Gtype_3D3548@@UAEPAXI@Z @ 0x00061EC0
// (The scalar deleting destructor, compiler-written; its operator delete is
// the empty sub_19A750. It also fills type_3D32F8's slot +0x254, folded by
// /OPT:ICF.)

// type_3D32F8's inline accessors, out of line here.

// match: ?vf_094@type_3D32F8@@UAEXI@Z @ 0x00073DD0
// sp-match: ?vf_094@type_3D32F8@@UAEXI@Z @ 0x00061F40
void type_3D32F8::vf_094(RwUInt32 arg_0)
{
    unk_3DC = arg_0;
}

// match: ?vf_09C@type_3D32F8@@UAEHXZ @ 0x00073DF0
// sp-match: ?vf_09C@type_3D32F8@@UAEHXZ @ 0x00061F50
RwInt32 type_3D32F8::vf_09C()
{
    return unk_3D8;
}

// match: ?vf_0A0@type_3D32F8@@UAEXI@Z @ 0x00073E10
// sp-match: ?vf_0A0@type_3D32F8@@UAEXI@Z @ 0x00061F60
void type_3D32F8::vf_0A0(RwUInt32 arg_0)
{
    unk_3D8 = arg_0;
}

// match: ?vf_0E0@type_3D32F8@@UAEPAEXZ @ 0x00073E30
// sp-match: ?vf_0E0@type_3D32F8@@UAEPAEXZ @ 0x00061F70
RwUInt8 *type_3D32F8::vf_0E0()
{
    return (RwUInt8 *)unk_44C;
}

// match: ?vf_124@type_3D32F8@@UAEXM@Z @ 0x00073E50
// sp-match: ?vf_124@type_3D32F8@@UAEXM@Z @ 0x00061F80
void type_3D32F8::vf_124(RwReal arg_0)
{
    unk_440 = arg_0;
}

// match: ?vf_128@type_3D32F8@@UAEMXZ @ 0x00073E70
// sp-match: ?vf_128@type_3D32F8@@UAEMXZ @ 0x00061F90
RwReal type_3D32F8::vf_128()
{
    return unk_440;
}

// match: ?vf_0F4@type_3D32F8@@UAEPAUSplinePath@@XZ @ 0x00073E90
// sp-match: ?vf_0F4@type_3D32F8@@UAEPAUSplinePath@@XZ @ 0x00061FA0
SplinePath *type_3D32F8::vf_0F4()
{
    return unk_448;
}

// match: ?vf_234@type_3D32F8@@UAEPAUtype_3D3548@@XZ @ 0x00073EB0
// sp-match: ?vf_234@type_3D32F8@@UAEPAUtype_3D3548@@XZ @ 0x00061FB0
type_3D3548 *type_3D32F8::vf_234()
{
    return unk_454.sub_D4910();
}

// match: ?vf_240@type_3D32F8@@UAEX_N@Z @ 0x00073ED0
// sp-match: ?vf_240@type_3D32F8@@UAEX_N@Z @ 0x00061FC0
void type_3D32F8::vf_240(bool arg_0)
{
    unk_43C = arg_0;
}

// match: ?vf_244@type_3D32F8@@UAEHXZ @ 0x00073EF0
// sp-match: ?vf_244@type_3D32F8@@UAEHXZ @ 0x00061FD0
RwInt32 type_3D32F8::vf_244()
{
    return unk_458 != 0 ? unk_458->unk_01 : 0;
}

// match: ?vf_248@type_3D32F8@@UAEXPAUtype_76290@@@Z @ 0x00073F30
// sp-match: ?vf_248@type_3D32F8@@UAEXPAUtype_76290@@@Z @ 0x00061FF0
void type_3D32F8::vf_248(type_76290 *arg_0)
{
    unk_458 = arg_0;
}

// match: ?vf_24C@type_3D32F8@@UAEPAUtype_76290@@XZ @ 0x00073F50
// sp-match: ?vf_24C@type_3D32F8@@UAEPAUtype_76290@@XZ @ 0x00062000
type_76290 *type_3D32F8::vf_24C()
{
    return unk_458;
}

// match: ?vf_174@type_3D32F8@@UAEHXZ @ 0x00073F70
// sp-match: ?vf_174@type_3D32F8@@UAEHXZ @ 0x00062010
RwInt32 type_3D32F8::vf_174()
{
    return unk_430;
}

// match: ?vf_178@type_3D32F8@@UAEXH@Z @ 0x00073F90
// sp-match: ?vf_178@type_3D32F8@@UAEXH@Z @ 0x00062020
void type_3D32F8::vf_178(RwInt32 arg_0)
{
    unk_430 = arg_0;
}

// match: ?vf_180@type_3D32F8@@UAEXH@Z @ 0x00073FB0
// sp-match: ?vf_180@type_3D32F8@@UAEXH@Z @ 0x00062030
void type_3D32F8::vf_180(RwInt32 arg_0)
{
    unk_430 += arg_0;
    if (unk_430 > unk_434)
        unk_430 = unk_434;
}

// match: ?vf_17C@type_3D32F8@@UAEMXZ @ 0x00074000
// sp-match: ?vf_17C@type_3D32F8@@UAEMXZ @ 0x00062060
RwReal type_3D32F8::vf_17C()
{
    return (RwReal)unk_430 / unk_434;
}

// match: ??_Gtype_3D32F8@@UAEPAXI@Z @ 0x00074020
// match: ??1type_3D32F8@@UAE@XZ @ 0x00074050
// match: __ehhandler$??1type_3D32F8@@UAE@XZ-0x16 @ 0x002FF9D0
// match: __ehhandler$??1type_3D32F8@@UAE@XZ @ 0x002FF9E6
// sp-match: ??1type_3D32F8@@UAE@XZ @ 0x00062090
// sp-match: ??_Gtype_3D32F8@@UAEPAXI@Z @ 0x00062070
// (Its scalar deleting destructor and its destructor, defined in the class
// in type_3D32F8.h.)

// match: ?sub_740B0@type_3D32F8@@QAEHPAUtype_712B0@@@Z @ 0x000740B0
// sp-match: ?sub_740B0@type_3D32F8@@QAEHPAUtype_712B0@@@Z @ 0x000600B0
// The animated background entity's set-up from its trigger arg_0: the base's
// (sub_CCCD0), its spline object's handle, its physics, its model (kind 3;
// without one it is left inert, flagged 0x400000, and 0 returned), its
// animation, AI object (its script and tasks), sounds, spline and speed, and
// a mounted weapon when the trigger asks for one.
RwInt32 type_3D32F8::sub_740B0(type_712B0 *arg_0)
{
    RwInt32 var_8;
    type_712B0 *var_C;
    type_3DFEEC *var_10;
    type_3DF8D8 *var_28;
    type_3DF8D8_3 *var_2C;
    RwInt32 var_34;
    RwUInt32 var_40;
    type_7C8D0 *var_44;
    RpHAnimHierarchy *var_4C;
    RwInt32 var_50;
    type_3DF8D8 *var_54;
    RwUInt32 var_58;
    type_3D2E7C *var_5C;
    type_3DF8D8 *var_64;
    type_3D2CD0 *var_6C;
    type_3DFEEC *var_74;
    type_3DFEEC *var_78;
    RwMatrix var_C0;
    type_712B0 *var_C4;
    type_3D3548 *var_C8;
    RwInt32 var_CC;

    var_8 = 0;
    var_C = arg_0;
    sub_CCCD0(arg_0);
    unk_488 = 1;
    unk_88 &= ~0x2000;
    unk_438 = 0;
    unk_43C = 0;
    unk_3D4 = -1;
    unk_434 = (RwInt32)var_C->unk_120;
    unk_430 = unk_434;
    RwMatrixSetIdentityMacro(&unk_3F0);
    if (var_C->unk_E0.unk_00)
    {
        var_10 = (type_3DFEEC *)sub_198800(&var_C->unk_E0);
        var_8 = var_10->unk_14;
        ((type_D48D0 *)&var_10->unk_24_id)->sub_D48D0(this);
        var_10->unk_10 = 0x102;
    }
    unk_28 = 0x14;
    unk_2C = 0x100;
    unk_30 = -1;
    switch (var_C->unk_11C)
    {
    case 1:
        unk_2C |= 2;
        break;
    case 2:
        unk_2C |= 1;
        break;
    }
    set_xyz(&unk_10C, -1.0f, 0.0f, -1.0f);
    set_xyz(&unk_134, -1.0f, -1.0f, -1.0f);
    unk_130 = 0;
    zero_v3d(&unk_118);
    set_xyz(&unk_124, 1.0e37f, 1.0e37f, 1.0e37f);
    unk_3E0 = 0.0f;
    unk_444 = 1.0f;
    unk_458 = 0;
    var_28 = sub_198800(&var_C->unk_C0);
    if (!var_28 || var_28->vf_008() != 3)
    {
        sub_D3FB0("AnimatedBGEntity", arg_0, &var_C->unk_C0);
        unk_3D8 = 0;
        unk_3DC = 0;
        unk_448 = 0;
        unk_3E0 = 0.0f;
        unk_440 = 0.0f;
        unk_454.sub_D48D0(0);
        unk_28 |= 0x400000; // not an address: a flag
        return 0;
    }
    var_2C = (type_3DF8D8_3 *)var_28;
    unk_290 = var_2C->get_unk_44();
    vf_224(var_2C, 0, &var_34);
    sub_16E080(get_unk_264(), var_2C->get_unk_54());
#ifdef CODFH_SP // single player asks for animation object kind 0 (SP 0x600B0: push ebx, ebx = 0)
    var_40 = sub_78830(0);
#else
    var_40 = sub_78830(2);
#endif
    unk_280 = var_40;
    var_44 = (type_7C8D0 *)sub_78AC0(unk_280);
    unk_284 = var_44;
    var_4C = sub_16D970(get_unk_264());
    var_44->sub_79470(var_4C);
    var_44->unk_1C = (RwInt32)this;
    RpHAnimHierarchyAttach(var_4C);
    var_50 = var_4C->flags;
    var_50 |= rpHANIMHIERARCHYUPDATEMODELLINGMATRICES;
    var_4C->flags = var_50;
    var_54 = sub_198800(&var_C->unk_D0);
    var_58 = sub_71870();
    unk_3D8 = var_58;
    var_5C = vf_098();
    var_5C->sub_70DF0(this, 2);
    var_5C->sub_70E10(var_54->get_unk_18(), 1);
    var_64 = sub_198800(&var_C->unk_D8);
    if (var_64)
    {
        var_5C->sub_70F40(var_64->get_unk_18(), 1);
    }
    var_6C = (type_3D2CD0 *)sub_71770(1);
    // Its handle as the object's handle struct (a struct copy: the value is
    // loaded before the destination).
    *(type_439E78_00 *)&unk_3DC = var_6C->get_unk_04_h();
    var_6C->sub_6CDA0(this, 4);
    memcpy(unk_44C, var_C->unk_104, 6);
    sub_D5B80(this, 4);
    sub_83850(2, &unk_1C0, &unk_3B0);
    unk_448 = 0;
    unk_3E0 = 0.0f;
    if (var_C->unk_F0.unk_00 || var_C->unk_F0.unk_04)
    {
        var_74 = (type_3DFEEC *)sub_198800(&var_C->unk_F0);
        var_78 = var_74;
        unk_448 = var_78->unk_24;
        if (var_C->unk_F8.unk_04)
        {
            unk_440 = var_C->unk_100_f;
        }
        else
        {
            unk_440 = *(RwReal *)&var_C->unk_F8.unk_00;
        }
    }
    unk_454.sub_D48D0(0);
    if (var_C->unk_13C)
    {
        RwMatrixSetIdentityMacro(&var_C0);
        var_C4 = (type_712B0 *)unk_344.unk_08;
        var_C8 = sub_166D40(var_C->unk_140, var_C->unk_148, &var_C0, 0, var_C4, 2, var_C->unk_158, var_C->unk_15C,
                            var_C->unk_160, var_C->unk_17C, var_C->unk_14C);
        unk_454.sub_D48D0(var_C8);
    }
    if (var_C->unk_178)
    {
        unk_28 |= 0x8000;
    }
#ifndef CODFH_SP // single player has no five-way blend (SP 0x600B0 ends with the weapon)
    unk_45C = 0;
    unk_460 = -1;
    for (var_CC = 0; var_CC < 5; var_CC++)
    {
        unk_464[var_CC] = 0;
    }
    unk_47C = 0.0f;
    unk_484 = 0.0f;
    unk_478 = 0.0f;
    unk_480 = 0.0f;
#endif
    return 1;
}

// match: ?vf_230@type_3D32F8@@UAEXXZ @ 0x000748C0
// sp-match: ?vf_230@type_3D32F8@@UAEXXZ @ 0x00060560
void type_3D32F8::vf_230()
{
    type_3D3548 *var_4;
    type_3DFEEC *varC;
    type_712B0 *local_8;

    if (unk_488 != 0) {
        unk_488 = 0;
        vf_228();
#ifdef CODFH_SP // shape: single player releases it through release_anim (SP 0x60560)
        if (unk_280 != 0)
            release_anim(unk_280);
#else
        if (unk_280 != 0) {
            sub_78870(unk_280);
            unk_280 = 0;
        }
#endif
        sub_8B840(this);
        if (vf_090() != 0) {
            sub_717B0((type_3D2C88 *)vf_090());
            unk_3DC = 0;
        }
        if (vf_098() != 0) {
            sub_71970((type_3D2C88 *)vf_098());
            unk_3D8 = 0;
        }
        local_8 = get_unk_34C();
        if (local_8->unk_E0.unk_00 != 0) {
            varC = (type_3DFEEC *)sub_198800(&local_8->unk_E0);
            ((type_D48D0 *)&varC->unk_24_id)->sub_D48D0(0);
        }
        if (unk_458 != 0) {
            unk_458->unk_00 = 0;
            unk_458 = 0;
        }
        var_4 = unk_454.sub_D4910();
        if (var_4 != 0)
            sub_D5A60(var_4, 0);
    }
}

// match: ?sub_74A30@type_3D32F8@@QAEXM@Z @ 0x00074A30
// sp-match: ?sub_74A30@type_3D32F8@@QAEXM@Z @ 0x00060650
void type_3D32F8::sub_74A30(RwReal arg_0)
{
#ifdef CODFH_SP // shape: separate locals, the last argument a plain 0 (SP 0x60650: frame 0x2C)
    RwFrame *var_4;
    RwInt32 s2C;
    RwInt32 s04;
    RwInt32 s00;
    RwInt32 s14;
    RwReal s18;
    RwV3d pos;
    RwV3d rad;

    var_4 = unk_338.unk_08;
    if (var_4 != 0) {
        pos = RwFrameGetLTM(var_4)->pos;
        rad.x = unk_4C;
        rad.y = unk_48;
        rad.z = unk_4C;
        s14 = 0;
        s00 = 0;
        s04 = 0;
        s2C = 0;
        if (ABS(unk_68 - pos.x) > 0.01f || ABS(unk_6C - pos.y) > 0.01f
            || ABS(unk_70 - pos.z) > 0.01f || ABS(unk_F0) > 0.01f
            || ABS(unk_F4) > 0.01f || ABS(unk_F8) > 0.01f || !unk_88_2)
            sub_950C0(this, var_4, (RwV3d *)unk_3C, *(RwReal *)&unk_50, &s14, &rad,
                      &s18, &s00, &s04, &s2C, 0);
    }
#else
    RwFrame *var_4;
    type_74A30 v34;

    var_4 = unk_338.unk_08;
    if (var_4 != 0) {
        v34.unk_08 = RwFrameGetLTM(var_4)->pos;
        v34.unk_20.x = unk_4C;
        v34.unk_20.y = unk_48;
        v34.unk_20.z = unk_4C;
        v34.unk_14 = 0;
        v34.unk_00 = 0;
        v34.unk_04 = 0;
        v34.unk_2C = 0;
        v34.unk_1C = 0;
        if (ABS(unk_68 - v34.unk_08.x) > 0.01f || ABS(unk_6C - v34.unk_08.y) > 0.01f
            || ABS(unk_70 - v34.unk_08.z) > 0.01f || ABS(unk_F0) > 0.01f
            || ABS(unk_F4) > 0.01f || ABS(unk_F8) > 0.01f || !unk_88_2)
            sub_950C0(this, var_4, (RwV3d *)unk_3C, *(RwReal *)&unk_50, &v34.unk_14, (RwV3d *)&v34.unk_20,
                      (RwReal *)&v34.unk_18, &v34.unk_00, &v34.unk_04, &v34.unk_2C,
                      (type_3DAFC8_1DDC *)v34.unk_1C);
    }
#endif
}

// match: ?vf_03C@type_3D32F8@@UAEXM@Z @ 0x00074CA0
// sp-match: ?vf_03C@type_3D32F8@@UAEXM@Z @ 0x00060800
void type_3D32F8::vf_03C(RwReal arg_0)
{
    type_712B0 *var_4;

    type_3D3548::vf_03C(arg_0);
    var_4 = (type_712B0 *)unk_344.unk_08;
    if (!(unk_28 & 0x20) && var_4 != 0 && var_4->unk_178 != 0)
        sub_74A30(arg_0);
    if (unk_448 != 0 && !unk_28_9) {
        RwV3d local_3C;
        RwV3d v30;
        RwV3d var20;
        RwV3d lv_10;
        RwInt32 lv_40 = 0;
        RwInt32 slot_44 = 0;
        RwReal slot_24 = unk_3E0;
        RwReal var_14 = 0;

        if (unk_440 > 1.0f)
#ifdef CODFH_SP // shape: SP 0x60800 divides first, then scales by arg_0
            var_14 = arg_0 * (unk_440 / unk_448->unk_24);
#else
            var_14 = unk_440 / unk_448->unk_24 * arg_0;
#endif
        else
            var_14 = arg_0 * unk_440 * 0.5f;
        unk_3E0 = var_14 + unk_3E0;
        CLAMP(unk_3E0, 0, unk_444);
        if (unk_440 != 0) {
            if (unk_3E0 >= unk_444 || unk_3E0 <= 0) {
                if ((unk_448->unk_1C & 3) == 2)
                    unk_440 = -unk_440;
                else if ((unk_448->unk_1C & 3) == 1)
                    unk_3E0 = 0;
                else
                    slot_44 = 1;
                lv_40 = 1;
            }
        }
        slot_24 = var_14 + unk_3E0;
        CLAMP(slot_24, 0, 1.0f);
        unk_448->sub_BA990(unk_3E0, &lv_10, &unk_3F0);
        vf_0C0(&lv_10);
        unk_448->sub_BA990(slot_24, &v30, &unk_3F0);
        vf_0D0(&v30);
        if (unk_43C != 0) {
            RwReal var_48;
            RwV3d var54;
            RwMatrix *bp_58;
            RwReal var_5C;
            RwReal var60;
            RwReal stk_64;

            var_48 = 0;
            if (unk_440 > 0)
                var_48 = unk_440 / unk_448->unk_24;
            else
                var_48 = unk_440;
            var_5C = var_48 * 30.0f + unk_3E0;
            CLAMP(var_5C, 0, 1.0f);
            unk_448->sub_BA990(var_5C, &var54, &unk_3F0);
            RwV3dSubMacro(&local_3C, &v30, &lv_10);
            RwV3dSubMacro(&var20, &var54, &lv_10);
            local_3C.y = 0;
            var60 = local_3C.x;
            local_3C.x = -local_3C.z;
            local_3C.z = var60;
            var20.y = 0;
            stk_64 = 0;
            if (RwV3dDotProductMacro(&local_3C, &local_3C) != 0 && RwV3dDotProductMacro(&var20, &var20) != 0) {
                RwV3dNormalize(&local_3C, &local_3C);
                RwV3dNormalize(&var20, &var20);
                stk_64 = RwV3dDotProductMacro(&local_3C, &var20);
            }
            stk_64 = stk_64 * 90.0f;
            bp_58 = RwFrameGetMatrix(get_unk_340());
            RwMatrixRotate(bp_58, &stru_3D3280, stk_64, rwCOMBINEPRECONCAT);
        }
        if (lv_40) {
            RwReal var_68;

            var_68 = deltaTime;
            sub_6B5F0("IHaveArrived", (type_67620 *)(vf_098()), 0, 0, (RwInt32 *)(&var_68), 1, 1, 0);
            sub_6B5F0("SplinePath_ArrivedATDestination", (type_67620 *)(vf_098()), 0, 0, 0, 0, 1, 0);
        }
        if (slot_44) {
            unk_448 = 0;
            unk_3E0 = 0;
            unk_444 = 1.0f;
        }
    }
}

// match: ?vf_04C@type_3D32F8@@UAEXM@Z @ 0x000751A0
// sp-match: ?vf_04C@type_3D32F8@@UAEXM@Z @ 0x00060BC0
// Its update: the base's, then its mounted weapon (unk_454) placed at its
// clump's tag "PGN0" plus its trigger's unk_144 mod 10, less the weapon's
// "ATMT" attach point.
void type_3D32F8::vf_04C(RwReal arg_0)
{
    type_3D3548 *var_C;
    type_712B0 *var_14;
    RwFrame *var_1C;
    RwMatrix *var_20;
    RwMatrix *var_28;
    RwInt32 var_2C;
    RwMatrix var_70;
    type_EC1F0 *var_78;
    RwV3d var_84;
    RwChar var_190[0x100];
    RwMatrix var_1D0;

    type_3D3548::vf_04C(arg_0);
    var_C = unk_454.sub_D4910();
    if (var_C)
    {
        var_14 = get_unk_34C();
        var_1C = var_C->get_unk_340();
        var_20 = RwFrameGetMatrix(var_1C);
        var_28 = RwFrameGetMatrix(get_unk_340());
        var_2C = var_14->unk_144 % 10 + 0x50474E30; // not an address: a tag
        if (!sub_EC2D0(get_unk_264(), (RwInt32)&var_70, var_2C, 0, 1))
        {
            var_70 = *var_28;
        }
        var_78 = sub_EC1F0(var_C->get_unk_264(), 0x41544D54); // not an address: a tag
        if (!var_78)
        {
            var_84.x = 0.0f;
            var_84.y = 0.0f;
            var_84.z = 0.0f;
            if (var_C->get_unk_34C())
            {
                var_84 = *(RwV3d *)&var_C->get_unk_34C()->unk_90;
            }
            sprintf(var_190,
                    "No atMT attach locator found to attach the mounted weapon to this AnimBGEntity.  Triggered @ "
                    "position %9.4f, %9.4f, %9.4f (JBTY)\n",
                    var_84.x, var_84.y, var_84.z);
            RwMatrixSetIdentityMacro(&var_1D0);
        }
        else
        {
            RwMatrixInvert(&var_1D0, &var_78->unk_10);
        }
        RwMatrixTransform(&var_70, &var_1D0, rwCOMBINEPRECONCAT);
        *var_20 = var_70;
        RwFrameUpdateObjects(var_1C);
    }
}

// match: ?vf_170@type_3D32F8@@UAEXHHHH@Z @ 0x00075440
// sp-match: ?vf_170@type_3D32F8@@UAEXHHHH@Z @ 0x00060D90
void type_3D32F8::vf_170(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C)
{
    if (unk_88_13)
        return;
    type_3D3548::vf_170(arg_0, arg_4, arg_8, arg_C);
}

// match: ?vf_0E4@type_3D32F8@@UAEHH@Z @ 0x00075480
// sp-match: ?vf_0E4@type_3D32F8@@UAEHH@Z @ 0x00060DB0
RwInt32 type_3D32F8::vf_0E4(RwInt32 arg_0)
{
    type_712B0 *var_4;

    var_4 = get_unk_34C();
    return var_4->unk_10A[arg_0];
}

// match: ?vf_0E8@type_3D32F8@@UAEHXZ @ 0x000754B0
// sp-match: ?vf_0E8@type_3D32F8@@UAEHXZ @ 0x00060DD0
RwInt32 type_3D32F8::vf_0E8()
{
    RwInt32 var_4;
    type_712B0 *local_8;

    local_8 = get_unk_34C();
    for (var_4 = 0; var_4 < 5; var_4++) {
        if (local_8->unk_10A[var_4] == -1)
            break;
    }
    return var_4;
}

// match: ?vf_0EC@type_3D32F8@@UAEXHH@Z @ 0x00075510
// sp-match: ?vf_0EC@type_3D32F8@@UAEXHH@Z @ 0x00060DF0
void type_3D32F8::vf_0EC(RwInt32 arg_0, RwInt32 arg_4)
{
    unk_44C[arg_0] = (RwInt16)arg_4;
}

// match: ?sub_75530@type_3D32F8@@QAEXXZ @ 0x00075530
// sp-match: ?sub_75530@type_3D32F8@@QAEXXZ @ 0x00060E10
void type_3D32F8::sub_75530()
{
    type_712B0 *var_4;
    type_3DF8D8 *v8;
    type_3DF8D8 *varC;

    var_4 = get_unk_34C();
    if (var_4 != 0) {
        if (var_4->unk_C0.unk_00 == var_4->unk_C8.unk_00
            && var_4->unk_C0.unk_04 == var_4->unk_C8.unk_04)
            unk_438 = 1;
        else if (var_4->unk_138 != 0) {
            v8 = sub_198800(&var_4->unk_C8);
            if (v8 == 0 || v8->vf_008() != 3)
                return;
            varC = v8;
            vf_228();
            vf_224(varC, 0, 0);
            unk_438 = 1;
        }
    }
}

// match: ?vf_064@type_3D32F8@@UAEHPAUtype_75600@@@Z @ 0x00075600
// sp-match: ?vf_064@type_3D32F8@@UAEHPAUtype_75600@@@Z @ 0x00060E90
RwInt32 type_3D32F8::vf_064(type_75600 *arg_0)
{
    type_712B0 *v8;
    type_3D3548 *varC;
    RwInt32 var_4;

    if (arg_0 != 0) {
        v8 = (type_712B0 *)unk_344.unk_08;
        if (v8->unk_130 == 0)
            return 0;
        if (arg_0->unk_0C != 0) {
            varC = arg_0->unk_0C;
            if (v8->unk_128 == 0 && varC->unk_2C_0)
                return 0;
            if (v8->unk_12C == 0 && varC->unk_2C_1)
                return 0;
        }
        unk_430 -= (RwInt32)arg_0->unk_28;
        sub_6B5F0("HitByBullet", (type_67620 *)(vf_098()), 0, 0, 0, 0, 1, 0);
        var_4 = 0;
        sub_6B5F0("HitByBulletRWS", (type_67620 *)(vf_098()), 0, 0, &var_4, 1, 1, 0);
        sub_D2AD0(arg_0->unk_0C, arg_0->unk_04);
        if (vf_174() <= 0 && unk_438 == 0) {
            sub_6B5F0("Destroyed", (type_67620 *)(vf_098()), 0, 0, 0, 0, 1, 0);
            sub_75530();
        }
    }
    return 0;
}

// match: ?vf_06C@type_3D32F8@@UAEHPAUtype_3D3548@@@Z @ 0x00075770
// sp-match: ?vf_06C@type_3D32F8@@UAEHPAUtype_3D3548@@@Z @ 0x00060FC0
RwInt32 type_3D32F8::vf_06C(type_3D3548 *arg_0)
{
    RwFrame *l24;
    RwMatrix *local_18;
    RwMatrix *var_1C;
    RwReal local_14;
    RwReal local_10;
    type_75770_0C var_C;
    type_712B0 *l20;

    l24 = unk_338.unk_08;
    local_18 = RwFrameGetLTM(l24);
    l24 = arg_0->get_unk_340();
    var_1C = RwFrameGetLTM(l24);
    local_14 = RwV3dDotProductMacro(&local_18->at, &var_1C->at);
    local_10 = RwV3dDotProductMacro(&local_18->right, &var_1C->right);
    var_C.unk_00 = arg_0->vf_09C();
    var_C.unk_04 = local_14;
    var_C.unk_08 = local_10;
    sub_6B5F0("CollisionByEntityNotification", (type_67620 *)(vf_098()), 0, 0, (RwInt32 *)(&var_C), 3, 1, 0);
    if (arg_0->vf_00C() != 0)
        sub_6B5F0("CollisionByPlayerNotification", (type_67620 *)(vf_098()), 0, 0, (RwInt32 *)(&var_C), 3, 1, 0);
    l20 = (type_712B0 *)unk_344.unk_08;
    if (l20 != 0 && arg_0 != 0) {
        RwInt32 var_28 = 0;
        type_3D2E7C *var_2C = arg_0->vf_098();

        var_28 = l20->unk_178;
        if (var_28 != 0)
            l20->sub_BDAC0(var_28, 0, var_2C);
    }
    return 0;
}

// match: ?vf_068@type_3D32F8@@UAEHPAUtype_758F0@@@Z @ 0x000758F0
// sp-match: ?vf_068@type_3D32F8@@UAEHPAUtype_758F0@@@Z @ 0x000610D0
RwInt32 type_3D32F8::vf_068(type_758F0 *arg_0)
{
    RwV3d *ebp_34;
    RwFrame *var_30;
    RwV3d bp_2C;
    type_712B0 *local_20;
    RwMatrix *var_1C;
    RwInt32 var_18;
    type_758F0_14 var_14;

    if (arg_0 != 0 && arg_0->unk_2C > 0 && vf_070(arg_0, 0, 0)) {
        local_20 = (type_712B0 *)unk_344.unk_08;
        if (local_20->unk_134 == 0)
            return 0;
        unk_430 -= (RwInt32)arg_0->unk_2C;
        ebp_34 = RwMatrixGetPos(arg_0->unk_0C);
        var_30 = unk_338.unk_08;
        var_1C = RwFrameGetLTM(var_30);
        bp_2C = *RwMatrixGetPos(var_1C);
        RwV3dSubMacro(&bp_2C, &bp_2C, ebp_34);
        var_14.unk_00 = ebp_34->x;
        var_14.unk_04 = ebp_34->y;
        var_14.unk_08 = ebp_34->z;
        var_14.unk_0C = arg_0->unk_14;
        var_14.unk_10 = RwV3dDotProductMacro(&var_1C->at, &bp_2C) <= 0 ? 1 : 0;
        sub_6B5F0("HitByExplosion", (type_67620 *)(vf_098()), 0, 0, (RwInt32 *)(&var_14), 5, 1, 0);
        var_18 = 0;
        sub_6B5F0("HitByExplosionRWS", (type_67620 *)(vf_098()), 0, 0, &var_18, 1, 1, 0);
        sub_D2AD0(arg_0->unk_04.sub_D4910(), arg_0->unk_08);
        if (vf_174() <= 0 && unk_438 == 0)
            sub_75530();
    }
    return 0;
}

// match: ?sub_75AF0@type_3DA6C0@@QAEXPAUtype_10F710@@HHH@Z @ 0x00075AF0
// sp-match: ?sub_75AF0@type_3DA6C0@@QAEXPAUtype_10F710@@HHH@Z @ 0x00061260
void type_3DA6C0::sub_75AF0(type_10F710 *arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C)
{
    RpClump *var_8;
    RpHAnimHierarchy *var_C;
    RwMatrix var_50;
    RwFrame *var_58;
    RwFrame *var_60;
    RwMatrix var_A0;
    type_712B0_10F710 *var_A4;

    if (arg_C)
    {
        var_8 = unk_25C.unk_08;
        var_C = sub_16D970(var_8);
        RwMatrixSetIdentityMacro(&var_50);
        if (arg_4)
        {
            sub_EC310(var_8, var_C, &var_50, arg_4, 0, 1);
        }
        var_58 = arg_0->get_unk_340();
        var_60 = get_unk_340();
        RwFrameTransform(var_58, &var_50, rwCOMBINEREPLACE);
        RwMatrixInitializeMacro(&var_A0, rwMATRIXTYPENORMAL);
        RwMatrixInvert(&var_A0, RwFrameGetLTM(var_60));
        RwFrameTransform(var_58, &var_A0, rwCOMBINEPOSTCONCAT);
        arg_0->unk_1A04 = 0;
        var_A4 = (type_712B0_10F710 *)arg_0->unk_344.unk_08;
        var_58->modelling.pos.y += var_A4->unk_148 + 10.0f;
        RwFrameAddChild(var_60, var_58);
    }
    else
    {
        arg_0->sub_10F8A0(this, arg_4);
    }
    arg_0->unk_1B3C = arg_8;
    arg_0->sub_1090F0(0xC);
}

// match: ?sub_75CB0@type_3D32F8@@QAEXXZ @ 0x00075CB0
// sp-match: ?sub_75CB0@type_3D32F8@@QAEXXZ @ 0x000613B0
void type_3D32F8::sub_75CB0()
{
    RwInt32 var_4;
    type_10F710 *loc8;
    RwMatrix *local_C;
    RwFrame *var10;
    RwV3d fp_1C;

    loc8 = (type_10F710 *)sub_1745A0(0);
    if (loc8 == 0)
        return;
    var_4 = loc8->get_unk_19D0_r();
    if (var_4 == 12) {
        var10 = loc8->get_unk_340();
        local_C = RwFrameGetMatrix(get_unk_340());
        if (RwFrameGetParent(var10) == get_unk_340()) {
            RwFrameRemoveChild(var10);
            fp_1C.x = 0;
            fp_1C.y = 0;
            fp_1C.z = 0;
            RwFrameTranslate(var10, &fp_1C, rwCOMBINEPRECONCAT);
            RwFrameTransform(var10, local_C, rwCOMBINEPOSTCONCAT);
        }
        loc8->sub_1090F0(0);
        loc8->sub_10F8A0(0, 0);
        loc8->sub_FF030();
    }
}

// match: ?vf_0F8@type_3D32F8@@UAEXM@Z @ 0x00075DA0
// sp-match: ?vf_0F8@type_3D32F8@@UAEXM@Z @ 0x00061440
void type_3D32F8::vf_0F8(RwReal arg_0)
{
    RwV3d var_C;

    unk_3E0 = arg_0;
    if (unk_448 != 0) {
        unk_448->sub_BA990(unk_3E0, &var_C, &unk_3F0);
        vf_0C0(&var_C);
    }
}

// match: ?vf_098@type_3D32F8@@UAEPAUtype_3D2E7C@@XZ @ 0x00075E00
// sp-match: ?vf_098@type_3D32F8@@UAEPAUtype_3D2E7C@@XZ @ 0x00061490
type_3D2E7C *type_3D32F8::vf_098()
{
    return (type_3D2E7C *)sub_67620(unk_3D8);
}

// match: ?vf_090@type_3D32F8@@UAEPAUtype_6D380@@XZ @ 0x00075E20
// sp-match: ?vf_090@type_3D32F8@@UAEPAUtype_6D380@@XZ @ 0x000614A0
type_6D380 *type_3D32F8::vf_090()
{
    return (type_6D380 *)sub_67620(unk_3DC);
}

// match: ?vf_058@type_3D32F8@@UAEHPAUtype_3DF8D8_04@@@Z @ 0x00075E40
// sp-match: ?vf_058@type_3D32F8@@UAEHPAUtype_3DF8D8_04@@@Z @ 0x000614B0
RwInt32 type_3D32F8::vf_058(type_3DF8D8_04 *arg_0)
{
    type_712B0 *var_4;

    var_4 = get_unk_34C();
    if (arg_0->unk_00 == var_4->unk_C0.unk_00 && arg_0->unk_04 == var_4->unk_C0.unk_04)
        return 1;
    if (arg_0->unk_00 == var_4->unk_C8.unk_00 && arg_0->unk_04 == var_4->unk_C8.unk_04)
        return 1;
    return 0;
}

// match: ?sub_75EC0@@YAXPAUtype_3D3548@@@Z @ 0x00075EC0
// sp-match: ?sub_75EC0@@YAXPAUtype_3D3548@@@Z @ 0x00061500
// The debris callback (type_3D32F8's vf_204 installs it): tips the entity
// over, bouncing it on the ground until it has no bounces left.
void sub_75EC0(type_3D3548 *arg_0)
{
    RwSphere ebp_48;
    RwV3d v34;
    RwMatrix *local_28;
    RpAtomic *local_24;
    RwV3d local_20;
    RwInt32 local_14;
    RwV3d local_10;
    RwFrame *var_4;
    type_3D32F8 *l38 = (type_3D32F8 *)arg_0;
    type_76290 *stk_4C = l38->vf_24C();

    stk_4C->unk_20 += stk_4C->unk_24;
#ifdef CODFH_SP // shape: SP 0x61500 multiplies by 0.05 and adds (no folding into 1.05)
    {
        RwReal grow = stk_4C->unk_24 * 0.05f;
        stk_4C->unk_24 += grow;
    }
#else
    stk_4C->unk_24 += stk_4C->unk_24 * 0.05f;
#endif
    if (stk_4C->unk_20 >= 8.0f)
        stk_4C->unk_20 = 8.0f;
    stk_4C->unk_1C += stk_4C->unk_20;
    local_24 = l38->unk_250.unk_08;
    if (local_24 != 0)
        ebp_48 = *RpAtomicGetWorldBoundingSphere(local_24);
    else
        ebp_48.radius = l38->unk_48;
    var_4 = l38->get_unk_340();
    local_28 = RwFrameGetLTM(var_4);
    local_10 = *RwMatrixGetUp(local_28);
    RwV3dScaleMacro(&local_10, &local_10, ebp_48.radius);
    RwV3dAddMacro(&v34, (RwV3d *)l38->vf_0C4(), &local_10);
    local_14 = 0;
    if (stk_4C->unk_20 > 0) {
        type_92430 var_78;

        sub_92430(&v34, &var_78, 50.0f);
        if (var_78.unk_20 != 0) {
            if (absf(var_78.unk_04) < 50.0f)
                local_14 = 1;
        } else if (stk_4C->unk_1C > 90.0f)
            local_14 = 1;
    }
    if (local_14 != 0) {
        if (stk_4C->unk_2C != 0) {
            stk_4C->unk_28 = lerp(-1.5f, 1.5f, frand());
            stk_4C->unk_2C--;
            stk_4C->unk_1C = 90.0f;
            stk_4C->unk_24 *= 0.2f;
            stk_4C->unk_20 = -stk_4C->unk_20 * 0.2f;
        } else {
            l38->sub_D3700(0, 0, 0);
            l38->vf_190(0);
            stk_4C->sub_761F0();
            l38->vf_248(0);
        }
    }
    local_20 = *RwMatrixGetPos(local_28);
    RwFrameRotate(var_4, RwMatrixGetUp(local_28), stk_4C->unk_28, rwCOMBINEPOSTCONCAT);
    RwFrameUpdateObjects(var_4);
    RwFrameRotate(var_4, &stk_4C->unk_10, stk_4C->unk_20, rwCOMBINEPRECONCAT);
    RwFrameUpdateObjects(var_4);
    l38->vf_0C0(&local_20);
}

#ifndef CODFH_SP // single player has it inline (include/types/type_3D32F8.h)
// match: ?sub_761F0@type_76290@@QAEXXZ @ 0x000761F0
void type_76290::sub_761F0()
{
    unk_00 = 0;
    unk_02 = -1;
    unk_01 = 0;
    unk_01 = 1;
    unk_2C = 0;
    unk_10.z = 0;
    unk_10.y = 0;
    unk_10.x = 0;
    unk_04.z = 0;
    unk_04.y = 0;
    unk_04.x = 0;
    unk_28 = 0;
    unk_1C = 0;
    unk_24 = 0;
    unk_20 = 0;
}
#endif

// match: ?vf_204@type_3D32F8@@UAEXHHH@Z @ 0x00076290
// sp-match: ?vf_204@type_3D32F8@@UAEXHHH@Z @ 0x00061790
void type_3D32F8::vf_204(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    switch (arg_0) {
    case 1:
        if (vf_24C() == 0) {
            type_3D3548 *var_4;
            type_3D2E7C *v8;
            RwInt32 stk_C;
            type_76290 *var_10;

            vf_248(sub_D63A0(unk_4B8220, 8));
            if (vf_24C() == 0)
                return;
            var_10 = vf_24C();
            stk_C = arg_8;
            v8 = (type_3D2E7C *)sub_67620(stk_C);
            var_4 = v8->sub_71300();
            if (var_4 != 0) {
                RwInt32 var_14;
                RwChar var_24[10];
                type_73050 var_2C;
                type_F1230 *v30;
                RwInt32 v34;
                type_3DBC78 *l38;
                RwInt32 var_3C;

                var_10->unk_2C = 2;
                var_10->unk_24 = 0.0125f;
                RwV3dSubMacro(&var_10->unk_04, (RwV3d *)vf_0C4(), (RwV3d *)var_4->vf_0C4());
                var_10->unk_04.y = ((RwV3d *)vf_0C4())->y;
                RwV3dNormalize(&var_10->unk_04, &var_10->unk_04);
                RwV3dCrossProductMacro(&var_10->unk_10,
                                       RwMatrixGetUp(RwFrameGetLTM(var_4->get_unk_340())),
                                       &var_10->unk_04);
                RwV3dNormalize(&var_10->unk_10, &var_10->unk_10);
                var_10->unk_20 = 0;
                l38 = var_4->vf_010();
                if (l38 != 0) {
                    RwReal var_40;

                    var_40 = RwV3dLength((RwV3d *)&((type_76290_574 *)l38)->unk_574);
                    if (var_40 > 5.0f && var_40 < 12.0f)
                        var_10->unk_24 = 0.0175f;
                    else if (var_40 > 12.0f && var_40 < 25.0f)
                        var_10->unk_24 = 0.025f;
                    else if (var_40 > 25.0f)
                        var_10->unk_24 = 0.035f;
                } else
                    return;
                vf_190(0);
                sub_D3700(sub_75EC0, arg_4, arg_8);
                var_2C.unk_00 = 0;
                var_2C.unk_04 = 0;
                var_2C.unk_00 = 0x0E5E8875;
                var_2C.unk_04 = 0xB3311AEF;
                dword_4B1E98.sub_8A980((type_3DF8D8_04 *)&var_2C, 0, 0x40, (RwV3d *)vf_0C4(), 0, 0);
                v34 = RpRandom() % 6 + 3;
                memset(var_24, 0, 10);
                while (v34 != 0) {
                    var_3C = RpRandom() % 10;
                    if (var_24[var_3C] == 0) {
                        v34--;
                        var_24[var_3C] = 1;
                    }
                }
                for (var_14 = 0; var_14 < 10; var_14++) {
                    if (var_24[var_14] != 0) {
                        type_F1230 *var_44;

                        var_44 = (type_F1230 *)sub_F1230();
                        ((type_4B9E90 *)var_44)->sub_F0880(0x9743E24, RpRandom() % 21 + 20,
                                          seconds_to_frames(0.1f), 0);
                        ((type_4B9E90 *)var_44)->sub_F0A10(this, var_14 + 1, 1);
                    }
                }
                v30 = (type_F1230 *)sub_F1230();
                ((type_4B9E90 *)v30)->sub_F0880(0xC9D05219, 1, seconds_to_frames(0.5f), 0);
                ((type_4B9E90 *)v30)->sub_F0A10(this, 11, 1);
            }
        }
        break;
    default:
        sub_D3700(0, 0, 0);
    }
}

// match: ?vf_238@type_3D32F8@@UAEXPAUtype_10F710@@@Z @ 0x00076750
// sp-match: ?vf_238@type_3D32F8@@UAEXPAUtype_10F710@@@Z @ 0x00061B10
void type_3D32F8::vf_238(type_10F710 *arg_0)
{
    type_3DC9B0 *var_4;

    var_4 = (type_3DC9B0 *)unk_454.sub_D4910();
    if (var_4 != 0) {
        var_4->sub_168820(arg_0);
        arg_0->sub_1090F0(7);
        arg_0->unk_210C.sub_D48D0(var_4);
        if (dword_4B9190 != 0)
            dword_4B9190->sub_DEB80(2);
        var_4->unk_47C = 0;
        var_4->unk_48C = 0;
    }
}

// match: ?vf_23C@type_3D32F8@@UAEXXZ @ 0x000767D0
// sp-match: ?vf_23C@type_3D32F8@@UAEXXZ @ 0x00061B70
void type_3D32F8::vf_23C()
{
    type_3DC9B0 *var_4;
    type_10F710 *local_8;

    var_4 = (type_3DC9B0 *)unk_454.sub_D4910();
    if (var_4 != 0) {
        local_8 = (type_10F710 *)var_4->unk_5C0.sub_D4910();
        if (local_8->unk_2C_4) {
            var_4->unk_48C = 1;
            var_4->sub_168A90(local_8);
            local_8->sub_1090F0(0);
            if (dword_4B9190 != 0)
                dword_4B9190->sub_DEB80(0);
            local_8->sub_10F7E0(4, 0);
        }
    }
}

#ifndef CODFH_SP // single player has no five-way blend (type_3D32F8 is 0x460 bytes there; no twin)
// match: ?sub_76860@type_3D32F8@@QAEX_N@Z @ 0x00076860
void type_3D32F8::sub_76860(bool arg_0)
{
    RwInt32 var_4;
    RwInt32 local_8;           // unused; the image reserves its slot

    unk_45C = arg_0;
    unk_460 = -1;
    for (var_4 = 0; var_4 < 5; var_4++)
        unk_464[var_4] = 0;
    if (arg_0 && unk_284->sub_76920())
        unk_460 = unk_284->get_unk_34_id(0);
}
#endif

#ifndef CODFH_SP // single player has it inline (include/types/type_3D3548.h)
// match: ?sub_76920@type_7C8D0@@QAE_NXZ @ 0x00076920
bool type_7C8D0::sub_76920()
{
    RwInt32 var_4;

    var_4 = (unk_20 + unk_24 - 1) % type_7C8D0_ring_size;
    return (bool)unk_34[var_4].unk_08_30;
}
#endif

#ifndef CODFH_SP // single player has no five-way blend (type_3D32F8 is 0x460 bytes there; no twin)
// match: ?sub_76960@type_3D32F8@@QAEXXZ @ 0x00076960
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3D32F8::sub_76960()
{
    RwV2d var_24;
    RwV2d var_3C;
    RwV2d var_4C;
    RwReal qC8[5];
    RwInt32 local_B4;
    RwInt32 ebp_B0;
    RwInt32 local_AC;
    RwInt32 ebp_14;
    RwInt32 lv_10;
    RwInt32 slot_C;
    RwReal bp_8;

    bp_8 = unk_428BE0.unk_04;
    if (!unk_45C)
    {
        return;
    }
    if (unk_464[0] && !unk_284->sub_76E00(unk_464[0]))
    {
        unk_45C = 0;
        for (slot_C = 0; slot_C < 5; slot_C++)
        {
            unk_464[slot_C] = 0;
        }
        return;
    }
    if (!unk_464[0])
    {
        lv_10 = 0;
        ebp_14 = 0;
        while (lv_10 < unk_460 + 5)
        {
            ebp_14 = unk_284->sub_7C3E0(0, ebp_14);
            if (lv_10 >= unk_460)
            {
                unk_284->sub_79CE0(ebp_14, true);
                unk_464[lv_10 - unk_460] = ebp_14;
            }
            lv_10++;
        }
        unk_428BE0.unk_00 = 1.0f;
    }
    var_24.x = cos(unk_47C) * unk_484;
    var_24.y = sin(unk_47C) * unk_484;
    var_3C.x = cos(unk_478) * unk_480;
    var_3C.y = sin(unk_478) * unk_480;
    var_4C.x = (1.0f - bp_8) * var_24.x + var_3C.x * bp_8;
    var_4C.y = (1.0f - bp_8) * var_24.y + var_3C.y * bp_8;
    do
    {
        __m128 var_70 = _mm_set_ss(var_4C.x * var_4C.x + var_4C.y * var_4C.y);
        __m128 var_A0 = _mm_sqrt_ss(var_70);
        _mm_store_ss(&unk_484, var_A0);
    } while (0);
    if (unk_484 > 0.001f)
    {
        unk_47C = acos(var_4C.x / unk_484);
    }
    else
    {
        unk_47C = 0.0f;
    }
    if (var_4C.y < 0.0f)
    {
        unk_47C = -unk_47C;
    }
    local_AC = 0;
    ebp_B0 = 0;
    for (local_B4 = 0; local_B4 < 5; local_B4++)
    {
        qC8[local_B4] = 0.0f;
    }
    if (var_4C.x > 0.0f)
    {
        local_AC = 1;
    }
    else if (var_4C.x < 0.0f)
    {
        local_AC = 2;
        var_4C.x = -var_4C.x;
    }
    if (var_4C.y > 0.0f)
    {
        ebp_B0 = 3;
    }
    else if (var_4C.y < 0.0f)
    {
        ebp_B0 = 4;
        var_4C.y = -var_4C.y;
    }
    qC8[local_AC] = var_4C.x;
    qC8[ebp_B0] = var_4C.y;
    qC8[0] = 1.0f - unk_484;
    for (local_B4 = 0; local_B4 < 5; local_B4++)
    {
        flt_449B68[local_B4] = qC8[local_B4];
    }
    flt_449B7C = unk_47C;
    flt_449B80 = unk_484;
    flt_449B84 = unk_478;
    flt_449B88 = unk_480;
    sub_76E70(unk_464, qC8, unk_428BE0.unk_00);
}
#endif

#ifndef CODFH_SP // single player defines it in the class (include/types/type_3D3548.h)
// match: ?sub_76E00@type_7C8D0@@QAE_NH@Z @ 0x00076E00
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
bool type_7C8D0::sub_76E00(RwInt32 arg_0)
{
    RwInt32 var_4;
    RwInt32 local_8;

    local_8 = arg_0 & 0xFF;
    var_4 = (unk_20 + unk_24 - 1) % type_7C8D0_ring_size;
    if (unk_30[local_8].unk_00 == arg_0)
        return unk_30[local_8].unk_04 == var_4;
    return false;
}
#endif

#ifndef CODFH_SP // single player has no five-way blend (type_3D32F8 is 0x460 bytes there; no twin)
// match: ?sub_76E70@type_3D32F8@@QAEXPAHPAMM@Z @ 0x00076E70
void type_3D32F8::sub_76E70(RwInt32 *arg_0, RwReal *arg_4, RwReal arg_8)
{
    RwReal var_4;
    RwInt32 v8;
    RwReal fp_1C[5];
    bool var1D;

    var1D = false;
    fp_1C[0] = 1.0f;
    fp_1C[4] = arg_4[4];
    for (v8 = 3; v8 > 0; v8--) {
        if (var1D || arg_4[v8] == 0)
            fp_1C[v8] = 0;
        else {
            RwInt32 var_24;

            var_4 = 1.0f;
            for (var_24 = v8 + 1; var_24 < 5; var_24++)
                var_4 *= 1.0f - fp_1C[var_24];
            if (var_4 == 0)
                fp_1C[v8] = 0;
            else
                fp_1C[v8] = arg_4[v8] / var_4;
            if (fp_1C[v8] >= 1.0f) {
                fp_1C[v8] = 1.0f;
                var1D = true;
            }
        }
    }
    for (v8 = 0; v8 < 5; v8++) {
        if (fp_1C[v8] < 0.001f && unk_284->sub_7C9A0(arg_0[v8]) < 0.001f)
            fp_1C[v8] = 0;
        else
            fp_1C[v8] = arg_8 * fp_1C[v8]
                            + unk_284->sub_7C9A0(arg_0[v8]) * (1.0f - arg_8);
        unk_284->sub_79C90(arg_0[v8], fp_1C[v8]);
    }
}

// match: ?vf_208@type_3D32F8@@UAEHHHHMMMH@Z @ 0x00077030
RwInt32 type_3D32F8::vf_208(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwReal arg_C,
                            RwReal arg_10, RwReal arg_14, RwInt32 arg_18)
{
    RwInt32 var_4;              // unused; the image reserves its slot

    if ((arg_8 != 0 || !unk_284->sub_76920()) && unk_45C != 0) {
        if (unk_460 == -1)
            unk_460 = 0;
        else
            unk_45C = 0;
    }
    return type_3D3548::vf_208(arg_0, arg_4, arg_8, arg_C, arg_10, arg_14, arg_18);
}
#endif

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??2type_3D32F8@@SAPAXIPAX@Z (folded into 0x6CCF0)
void *type_3D32F8::operator new(RwUInt32 arg_0, void *arg_4)
{
    return arg_4;
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?sub_75CB0@type_3DA6C0@@QAEXXZ (folded into 0x75CB0)
void type_3DA6C0::sub_75CB0()
{
    RwInt32 var_4;
    type_10F710 *loc8;
    RwMatrix *local_C;
    RwFrame *var10;
    RwV3d fp_1C;

    loc8 = (type_10F710 *)sub_1745A0(0);
    if (loc8 == 0)
        return;
    var_4 = loc8->get_unk_19D0_r();
    if (var_4 == 12) {
        var10 = loc8->get_unk_340();
        local_C = RwFrameGetMatrix(get_unk_340());
        if (RwFrameGetParent(var10) == get_unk_340()) {
            RwFrameRemoveChild(var10);
            fp_1C.x = 0;
            fp_1C.y = 0;
            fp_1C.z = 0;
            RwFrameTranslate(var10, &fp_1C, rwCOMBINEPRECONCAT);
            RwFrameTransform(var10, local_C, rwCOMBINEPOSTCONCAT);
        }
        loc8->sub_1090F0(0);
        loc8->sub_10F8A0(0, 0);
        loc8->sub_FF030();
    }
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??3type_3D32F8@@SAXPAX@Z (folded into 0x19A750)
#ifndef CODFH_SP // single player keeps the call to the empty operator delete (SP 0x62070 calls SP nullsub_1): defined elsewhere there
void type_3D32F8::operator delete(void * arg_0)
{
}
#endif

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??3type_3D32F8@@SAXPAX0@Z (folded into 0x19A750)
void type_3D32F8::operator delete(void * arg_0, void * arg_4)
{
}
