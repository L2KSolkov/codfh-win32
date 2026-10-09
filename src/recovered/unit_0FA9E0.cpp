// The pickups (types/type_3D94B8.h) and their settings table
// (types/type_4C09B0.h). The original file name is not in the image, so it
// is named for its start address.

#include "rw/ostypes.h"
#include "rw/bamatrix.h"
#include "rw/baframe.h"
#include "rw/rpatomic.h"
#include "game/functions.h"
#include "game/vecutil.h"
#include "types/type_3D32F8.h"
#include "types/type_3D3548.h"
#include "types/type_3D94B8.h"
#include "types/type_4C09B0.h"
#include "types/type_4B85F8.h"
#include "types/PickupTrigger.h"
#include "rws/clumphelper.h"
#include "types/type_3DF8D8.h"
#if !defined(CODFH_SP) || CODFH_SP_PART != 2 // single player compiles the rest in another file (src/sp/units/sp_unit_0FA9E0_2.cpp)

// Its data definitions (PLAN M5), in the image's address order.
// 0x003D94B4
extern const RwReal flt_3D94B4 = 16.666666f;
// 0x004C09A8
RwInt32 dword_4C09A8;
// End of its data definitions.


// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).
type_4C09B0 dword_4C09B0[0x6E];
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3D94B4@@3MB @ 0x003D94B4
// match: ??_7type_3D94B8@@6B@ @ 0x003D94B8
// match: __ehhandler$?sub_FA9E0@@YAPAUtype_3D3548@@PAVPickupTrigger@@@Z>1>8 @ 0x0041D150
// match: __ehhandler$?sub_FA9E0@@YAPAUtype_3D3548@@PAVPickupTrigger@@@Z>1 @ 0x0041D168
// match: __ehhandler$??1type_3D94B8@@UAE@XZ>1>8 @ 0x0041D184
// match: __ehhandler$??1type_3D94B8@@UAE@XZ>1 @ 0x0041D194
// match: __ehhandler$?sub_FABC0@@YAPAUtype_3D94B8@@HHPAURwMatrixTag@@MHH@Z>1>8 @ 0x0041D1B0
// match: __ehhandler$?sub_FABC0@@YAPAUtype_3D94B8@@HHPAURwMatrixTag@@MHH@Z>1 @ 0x0041D1B8
// match: __ehhandler$??0type_3D94B8@@QAE@HHPAURwMatrixTag@@MHH@Z>1>8 @ 0x0041D1D4
// match: __ehhandler$??0type_3D94B8@@QAE@HHPAURwMatrixTag@@MHH@Z>1 @ 0x0041D1E4
// match: .CRT$XCU+0 @ 0x0042708C

// match: _$E2 @ 0x0030B740
// match: _$E3 @ 0x0030E5C0
// match: ?sub_FA9E0@@YAPAUtype_3D3548@@PAVPickupTrigger@@@Z @ 0x000FA9E0
// match: __ehhandler$?sub_FA9E0@@YAPAUtype_3D3548@@PAVPickupTrigger@@@Z-0x27 @ 0x00301170
// match: __ehhandler$?sub_FA9E0@@YAPAUtype_3D3548@@PAVPickupTrigger@@@Z @ 0x00301197
// sp-match: _$E2 @ 0x0021D7B0
// sp-match: _$E3 @ 0x0021E950
// sp-match: ?sub_FA9E0@@YAPAUtype_3D3548@@PAVPickupTrigger@@@Z @ 0x000BEDD0
// Single player calls the inline constructor (types/type_3D94B8.h) out of line
// (SP 0xBEE36); this file emits it:
// sp-match: ??0type_3D94B8@@QAE@PAVPickupTrigger@@@Z @ 0x000BED70

type_3D3548 *sub_FA9E0(PickupTrigger *arg_0)
{
    type_3D94B8 *var_10;

    var_10 = (type_3D94B8 *)sub_D56D0(0x3D0, arg_0->unk_24_18, arg_0->vf_008());
    if (var_10 != 0)
    {
        var_10 = new (var_10) type_3D94B8(arg_0);
        if (var_10->unk_28 & 0x400000) // not an address: entity flag
        {
            sub_D5A60(var_10, 0);
            var_10 = 0;
        }
    }
#ifndef CODFH_SP // single player compiles the debug print out (SP 0xBEDD0)
    else
    {
        sub_19A750("WARNING: A spawn could not be created due to lack of entity memory. Trigger "
                   "location(%6.2f,%6.2f,%6.2f)",
                   arg_0->unk_90, arg_0->unk_94, arg_0->unk_98);
    }
#endif
    return var_10;
}

// match: ??_Gtype_3D94B8@@UAEPAXI@Z @ 0x000FAB20
// sp-match: ??_Gtype_3D94B8@@UAEPAXI@Z @ 0x000BEC90
// (Its scalar deleting destructor, compiler-written.)

// match: ??1type_3D94B8@@UAE@XZ @ 0x000FAB50
// match: __ehhandler$??1type_3D94B8@@UAE@XZ-0x16 @ 0x003011B0
// match: __ehhandler$??1type_3D94B8@@UAE@XZ @ 0x003011C6
// sp-match: ??1type_3D94B8@@UAE@XZ @ 0x000BECB0
// (In the class.)

// match: ?sub_FABC0@@YAPAUtype_3D94B8@@HHPAURwMatrixTag@@MHH@Z @ 0x000FABC0
// match: __ehhandler$?sub_FABC0@@YAPAUtype_3D94B8@@HHPAURwMatrixTag@@MHH@Z-0x11 @ 0x003011D0
// match: __ehhandler$?sub_FABC0@@YAPAUtype_3D94B8@@HHPAURwMatrixTag@@MHH@Z @ 0x003011E1
// sp-match: ?sub_FABC0@@YAPAUtype_3D94B8@@HHPAURwMatrixTag@@MHH@Z @ 0x000BEE70
type_3D94B8 *sub_FABC0(RwInt32 arg_0, RwInt32 arg_4, RwMatrix *arg_8, RwReal arg_C, RwInt32 arg_10, RwInt32 arg_14)
{
    type_3D94B8 *var_10 = 0;

    var_10 = (type_3D94B8 *)sub_D56D0(0x3D0, 0, 0x18);
    if (var_10 != 0)
    {
        var_10 = new (var_10) type_3D94B8(arg_0, arg_4, arg_8, arg_C, arg_10, arg_14);
    }
    return var_10;
}

// match: ??0type_3D94B8@@QAE@HHPAURwMatrixTag@@MHH@Z @ 0x000FAC70
// match: __ehhandler$??0type_3D94B8@@QAE@HHPAURwMatrixTag@@MHH@Z-0x16 @ 0x003011F0
// match: __ehhandler$??0type_3D94B8@@QAE@HHPAURwMatrixTag@@MHH@Z @ 0x00301206
// sp-match: ??0type_3D94B8@@QAE@HHPAURwMatrixTag@@MHH@Z @ 0x000BEBF0
type_3D94B8::type_3D94B8(RwInt32 arg_0, RwInt32 arg_4, RwMatrix *arg_8, RwReal arg_C, RwInt32 arg_10,
                         RwInt32 arg_14)
{
    unk_344.sub_144940(0);
    unk_3C0 = 1;
    sub_FADB0(arg_0, arg_4, arg_8, arg_C, arg_10, arg_14);
    dword_4C09A8++;
}

// match: ?sub_FAD20@type_3D94B8@@QAEHPAVPickupTrigger@@@Z @ 0x000FAD20
// sp-match: ?sub_FAD20@type_3D94B8@@QAEHPAVPickupTrigger@@@Z @ 0x000BED10
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_3D94B8::sub_FAD20(PickupTrigger *arg_0)
{
    RwInt32 slot_C;
    RwReal bp_8;
    PickupTrigger *bp_4;

    sub_CCCD0((type_712B0 *)arg_0);
    bp_4 = arg_0;
    unk_3C0 = 0;
    bp_8 = -1.0f;
    if (bp_4->unk_C8)
    {
        bp_8 = 0.0f;
    }
    slot_C = sub_FADB0(bp_4->unk_C0, bp_4->unk_C4, (RwMatrix *)arg_0->unk_60, bp_8, bp_4->unk_C8, 0);
    return slot_C;
}

// match: ?sub_FADB0@type_3D94B8@@QAEHHHPAURwMatrixTag@@MHH@Z @ 0x000FADB0
// sp-match: ?sub_FADB0@type_3D94B8@@QAEHHHPAURwMatrixTag@@MHH@Z @ 0x000BE700
// Sets the pickup up from the settings arg_0 (count arg_4): its size, its
// physics (falling unless placed with a height of -1), a clone of the model
// arg_14 (else the settings' named object's), placed at arg_8 raised by
// arg_C and, with arg_10, turned by the settings' angles; its collision
// atomic (a sphere twice the model's) on a child frame.
RwInt32 type_3D94B8::sub_FADB0(RwInt32 arg_0, RwInt32 arg_4, RwMatrix *arg_8, RwReal arg_C, RwInt32 arg_10,
                               RwInt32 arg_14)
{
    type_4C09B0 *var_8;
    RpClump *var_24;
    RwFrame *var_28;
    RwMatrix var_70;
    RpAtomic *var_74;
    RwSphere var_84;
    RwFrame *var_88;
    RwMatrix var_D0;
    Trigger *var_D4;

    var_8 = sub_FB6C0(arg_0);
    unk_3C4 = 1;
    unk_88 |= 0x2000;
    unk_48 = var_8->unk_0C_f;
    unk_4C = var_8->unk_0C_f;
    unk_50_r = var_8->unk_0C_f / 2.0f;
    zero_v3d(&unk_3C_v);
    if (arg_C != -1.0f)
    {
        unk_28 = 0x3C;
    }
    else
    {
        unk_28 = 4;
    }
    unk_2C = 0x4000;
    unk_30 = 0x53;
    set_xyz(&unk_10C, -1.0f, -1.0f, -1.0f);
    set_xyz(&unk_134, -1.0f, -1.0f, -1.0f);
    zero_v3d(&unk_118);
    set_xyz(&unk_124, 1000.0f, 1000.0f, 1000.0f);
    unk_130 = 0;
    unk_3B0.sub_FB730(arg_0, arg_4);
    var_24 = RpClumpClone(arg_14 ? (RpClump *)arg_14 : (RpClump *)unk_3B0.sub_FB760());
    var_28 = RpClumpGetFrame(var_24);
    if (var_28)
    {
        unk_338.sub_129B10();
        unk_338.sub_129A70(var_28);
    }
    else
    {
        var_28 = RwFrameCreate();
        RwFrameSetIdentity(var_28);
        unk_338.sub_129B10();
        unk_338.sub_129A70(var_28);
        RpClumpSetFrame(var_24, var_28);
    }
    unk_3BC = arg_10;
    if (arg_10)
    {
        RwMatrixSetIdentityMacro(&var_70);
        RwMatrixRotate(&var_70, &unk_3D94A8, var_8->unk_10.z, rwCOMBINEPRECONCAT);
        RwMatrixRotate(&var_70, &unk_3D949C, var_8->unk_10.y, rwCOMBINEPRECONCAT);
        RwMatrixRotate(&var_70, &unk_3D9490, var_8->unk_10.x, rwCOMBINEPRECONCAT);
        var_70.pos = arg_8->pos;
    }
    else
    {
        var_70 = *arg_8;
    }
    var_70.pos.y += arg_C;
    RwFrameTransform(var_28, &var_70, rwCOMBINEREPLACE);
    RwFrameUpdateObjects(var_28);
    unk_25C.sub_129940(0);
    unk_25C.sub_129620(var_24);
    RWS::ClumpHelper::SetCanCollide(*var_24, 1);
    RWS::ClumpHelper::SetIsVisible(*var_24, 1);
    unk_25C.sub_129690(this);
    sub_173180(var_24);
    sub_D5B80(this, 8);
    var_74 = Clump_FindFirstAtomic(var_24);
    sub_16DCD0(var_24, &var_84);
    var_74->boundingSphere.center = var_84.center;
    var_74->boundingSphere.radius = var_84.radius * 1.5f;
    var_74 = RpAtomicCreate();
    var_88 = RwFrameCreate();
    RwFrameSetIdentity(var_88);
    RwFrameTransform(var_88, &var_70, rwCOMBINEREPLACE);
    RwFrameUpdateObjects(var_88);
    RwMatrixInitializeMacro(&var_D0, rwMATRIXTYPENORMAL);
    RwMatrixInvert(&var_D0, RwFrameGetLTM(var_28));
    RwFrameTransform(var_88, &var_D0, rwCOMBINEPOSTCONCAT);
    RwFrameAddChild(var_28, var_88);
    RpAtomicSetFrame(var_74, var_88);
    var_74->boundingSphere.center = var_84.center;
    var_74->boundingSphere.radius = var_84.radius * 2.0f;
    RpAtomicSetFlags(var_74, rpATOMICCOLLISIONTEST);
    sub_FB990(var_74, 4);
    sub_173320(var_74);
    unk_274.sub_129430(var_74);
    unk_274.sub_1294A0(this);
    var_D4 = unk_344.unk_08;
    if (var_D4)
    {
        if (!var_D4->unk_24_9)
        {
            unk_28 |= 0x20000; // not an address: a flag
        }
    }
    else
    {
        unk_28 |= 0x20000; // not an address: a flag
    }
    return 1;
}

// match: ?vf_230@type_3D94B8@@UAEXXZ @ 0x000FB330
// sp-match: ?vf_230@type_3D94B8@@UAEXXZ @ 0x000BEAF0
void type_3D94B8::vf_230()
{
    if (unk_3C4)
    {
        unk_3C4 = 0;
        unk_274.sub_1294D0();
        unk_25C.sub_129940(0);
        if (unk_3C0)
        {
            dword_4C09A8--;
        }
    }
}

// match: ?vf_1C4@type_3D94B8@@UAEXH@Z @ 0x000FB390
// sp-match: ?vf_1C4@type_3D94B8@@UAEXH@Z @ 0x000BEB40
void type_3D94B8::vf_1C4(RwInt32 arg_0)
{
    RwV3d *var_4 = &unk_10C;

    var_4->x = -1.0f;
    var_4->y = -1.0f;
    var_4->z = -1.0f;
    vf_18C(0);
    if (arg_0)
    {
        unk_28 |= 2;
        unk_28 &= ~0x10;
        unk_28 &= ~0x20;
    }
}

// match: ?vf_03C@type_3D94B8@@UAEXM@Z @ 0x000FB410
// sp-match: ?vf_03C@type_3D94B8@@UAEXM@Z @ 0x000BEB80
void type_3D94B8::vf_03C(RwReal arg_0)
{
    type_3D3548::vf_03C(arg_0);
}

// match: ?vf_040@type_3D94B8@@UAEXM@Z @ 0x000FB430
// sp-match: ?vf_040@type_3D94B8@@UAEXM@Z @ 0x00106CA0
void type_3D94B8::vf_040(RwReal arg_0)
{
    type_3D3548::vf_040(arg_0);
}

// match: ?vf_044@type_3D94B8@@UAEXM@Z @ 0x000FB450
// sp-match: ?vf_044@type_3D94B8@@UAEXM@Z @ 0x000BEB90
void type_3D94B8::vf_044(RwReal arg_0)
{
    type_3D3548::vf_044(arg_0);
    if (unk_28 >> 1 & 1)
    {
        unk_28 &= ~0x10;
        unk_28 &= ~0x20;
    }
}

// match: ?vf_058@type_3D94B8@@UAEHPAUtype_3DF8D8_04@@@Z @ 0x000FB4A0
// sp-match: ?vf_058@type_3D94B8@@UAEHPAUtype_3DF8D8_04@@@Z @ 0x000BEBB0
RwInt32 type_3D94B8::vf_058(type_3DF8D8_04 *arg_0)
{
    type_4C09B0 *var_4 = sub_FB6C0(unk_3B0.sub_FB710());

    if (arg_0->unk_00 == var_4->unk_04.unk_00 && arg_0->unk_04 == var_4->unk_04.unk_04)
    {
        return 1;
    }
    return 0;
}

#endif
#if !defined(CODFH_SP) || CODFH_SP_PART != 1 // single player: sp_unit_0FA9E0_2.cpp, the second file
// match: ?sub_FB4F0@@YAXXZ @ 0x000FB4F0
// sp-match: ?sub_FB4F0@@YAXXZ @ 0x000BEFF0
void sub_FB4F0()
{
    RwInt32 var_4;

    dword_4C09A8 = 0;
    for (var_4 = 0; var_4 < 0x6E; var_4++)
    {
        dword_4C09B0[var_4].sub_FB660();
    }
}

// match: ?sub_FB530@@YAXXZ @ 0x000FB530
void sub_FB530()
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 0x6E; var_4++)
    {
        dword_4C09B0[var_4].sub_2015D0();
    }
}

// match: ?sub_FB570@@YAXXZ @ 0x000FB570
// sp-match: ?sub_FB570@@YAXXZ @ 0x000BF020
void sub_FB570()
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 0x6E; var_4++)
    {
        dword_4C09B0[var_4].sub_FB690();
    }
}

// match: ??0type_4C09B0@@QAE@XZ @ 0x000FB5B0
// sp-match: ??0type_4C09B0@@QAE@XZ @ 0x000BEF10
type_4C09B0::type_4C09B0()
{
    unk_00 = 0;
    unk_0C_f = 15.0f;
    unk_10.z = 0.0f;
    unk_10.y = 0.0f;
    unk_10.x = 0.0f;
    unk_1C.unk_04 = 0;
    unk_1C.unk_00 = 0;
}

// match: ??1type_4C09B0@@QAE@XZ @ 0x000FB640
// sp-match: ??1type_4C09B0@@QAE@XZ @ 0x000BEF40
type_4C09B0::~type_4C09B0()
{
    unk_00 = 0;
}

// match: ?sub_FB660@type_4C09B0@@QAE_NXZ @ 0x000FB660
// sp-match: ?sub_FB660@type_4C09B0@@QAE_NXZ @ 0x000BEF50
bool type_4C09B0::sub_FB660()
{
    unk_04.unk_00 = 0;
    unk_04.unk_04 = 0;
    unk_00 = 1;
    return true;
}

// match: ?sub_FB690@type_4C09B0@@QAE_NXZ @ 0x000FB690
// sp-match: ?sub_FB690@type_4C09B0@@QAE_NXZ @ 0x000BEF60
bool type_4C09B0::sub_FB690()
{
    unk_04.unk_00 = 0;
    unk_04.unk_04 = 0;
    unk_00 = 0;
    return true;
}

// match: ?sub_FB6C0@@YAPAUtype_4C09B0@@H@Z @ 0x000FB6C0
// sp-match: ?sub_FB6C0@@YAPAUtype_4C09B0@@H@Z @ 0x000BEF70
type_4C09B0 *sub_FB6C0(RwInt32 arg_0)
{
    if (arg_0 < 0 || arg_0 >= 0x6E)
    {
        return 0;
    }
    return &dword_4C09B0[arg_0];
}

// match: ??0type_FB6E0@@QAE@XZ @ 0x000FB6E0
// sp-match: ??0type_FB6E0@@QAE@XZ @ 0x000BEF90
type_FB6E0::type_FB6E0()
{
    unk_04 = 0;
    unk_00 = 0;
    unk_08 = -1;
}

// match: ?sub_FB710@type_FB6E0@@QAEHXZ @ 0x000FB710
// sp-match: ?sub_FB710@type_FB6E0@@QAEHXZ @ 0x0005BA70
RwInt32 type_FB6E0::sub_FB710()
{
    return unk_08;
}

// match: ?sub_FB730@type_FB6E0@@QAEXHH@Z @ 0x000FB730
// sp-match: ?sub_FB730@type_FB6E0@@QAEXHH@Z @ 0x000BEFB0
void type_FB6E0::sub_FB730(RwInt32 arg_0, RwInt32 arg_4)
{
    unk_08 = arg_0;
    unk_04 = arg_4;
    unk_00 = 1;
}

// match: ?sub_FB760@type_FB6E0@@QAEHXZ @ 0x000FB760
// sp-match: ?sub_FB760@type_FB6E0@@QAEHXZ @ 0x000BEFD0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_FB6E0::sub_FB760()
{
    type_3DF8D8 *slot_C;
    type_4C09B0 *bp_8;
    RwInt32 bp_4;

    bp_8 = &dword_4C09B0[unk_08];
    slot_C = sub_198800(&bp_8->unk_04);
    bp_4 = ((RwInt32)((type_3DF9C4 *)slot_C)->sub_190A10());
    return bp_4;
}

// Members /OPT:ICF folded into shared trivial bodies (config/aliases.txt): defined here for
// the authentic link (PLAN M7); the placement link takes the shared bodies.

// ?vf_054@type_3D94B8@@UAEXH@Z (folded into the empty body at 0x15FB30)
void type_3D94B8::vf_054(RwInt32 arg_0)
{
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??1type_FB6E0@@QAE@XZ (folded into 0x1E41C0)
#ifndef CODFH_SP // single player keeps the calls to the empty destructor (SP 0xBECB0, 0xBEBF0): defined elsewhere there
type_FB6E0::~type_FB6E0()
{
}
#endif

// ??2type_3D94B8@@SAPAXIPAX@Z (folded into 0x6CCF0)
void *type_3D94B8::operator new(RwUInt32 arg_0, void *arg_4)
{
    return arg_4;
}

// ?Collision_DispatchAtomicIntersectionsBySelectorFlag@type_3D94B8@@UAEXPAURpAtomic@@PAURpIntersection@@PAUtype_93700@@@Z (folded into 0x177080)
void type_3D94B8::Collision_DispatchAtomicIntersectionsBySelectorFlag(struct RpAtomic *arg_0, struct RpIntersection *arg_4, struct type_93700 *arg_8)
{
    if (arg_8)
        arg_8->unk_5C = 1;
}

// ?sub_2015D0@type_4C09B0@@QAE_NXZ (folded into 0x2015D0)
bool type_4C09B0::sub_2015D0()
{
    return true;
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??3type_3D94B8@@SAXPAX@Z (folded into 0x19A750)
#ifndef CODFH_SP // single player keeps the call to the empty operator delete (SP 0xBEC90 calls SP nullsub_1): defined elsewhere there
void type_3D94B8::operator delete(void * arg_0)
{
}
#endif

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??3type_3D94B8@@SAXPAX0@Z (folded into 0x19A750)
void type_3D94B8::operator delete(void * arg_0, void * arg_4)
{
}
#endif
