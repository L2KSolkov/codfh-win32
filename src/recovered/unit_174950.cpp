// The player's camera entity (type_3DD948).

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "rw/baframe.h"
#include "rw/bamatrix.h"
#include "rw/rpatomic.h"
#include "rw/rphanim.h"
#include "rw/rpspline.h"
#include "rw/rtquat.h"
#include "rws/camerahelper.h"
#include "game/functions.h"
#include "game/data.h"
#include "game/gameloop.h"
#include "game/vecutil.h"
#include "game/frand.h"
#include "game/clumputil.h"
#include "game/worldmgr.h"
#include "types/type_3D3548.h"
#include "types/type_3DD948.h"
#include "types/type_3DF8D8.h"
#include "types/type_3D2E7C.h"
#include "types/alfaobject.h"
#include "types/animbank.h"
#include "types/animkey.h"
#include "types/type_10F710.h"
#include "types/SplinePath.h"
#include "types/type_4E5E50.h"
#include "types/type_44350.h"
#include "types/type_3D32F8.h"
#include "types/type_3D51C0.h"
#include "types/type_62A60.h"
#include <string.h>
#include "rw/bavector.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003DD944
extern const RwReal flt_3DD944 = 16.666666f;
// End of its data definitions.


// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).
type_4E5E40 dword_4E5E40;
type_4E5E50 unk_4E5E50;
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3DD944@@3MB @ 0x003DD944
// match: ??_7type_3DD948@@6B@ @ 0x003DD948
// match: __ehhandler$??1type_3DD948@@UAE@XZ>1>8 @ 0x0041E304
// match: __ehhandler$??1type_3DD948@@UAE@XZ>1 @ 0x0041E314
// match: __ehhandler$?sub_174A70@@YAPAUtype_3DD948@@PAURwV3d@@MPAUtype_3D3548@@@Z>1>8 @ 0x0041E330
// match: __ehhandler$?sub_174A70@@YAPAUtype_3DD948@@PAURwV3d@@MPAUtype_3D3548@@@Z>1 @ 0x0041E338
// match: __ehhandler$??0type_3DD948@@QAE@PAURwV3d@@MPAUtype_3D3548@@@Z>1>8 @ 0x0041E354
// match: __ehhandler$??0type_3DD948@@QAE@PAURwV3d@@MPAUtype_3D3548@@@Z>1 @ 0x0041E364
// match: .CRT$XCU+0 @ 0x00427158
// match: .CRT$XCU+4 @ 0x0042715C

// match: _$E2 @ 0x0030BE80
// match: _$E4 @ 0x0030BEB0
// match: _$E5 @ 0x0030E960

// A switch compiled to 0: an inline with no address and so no database
// name, named for what it returns. Evidence: the camera's set-up tests it
// as `xor edx, edx; jne`, a substituted 0 that is not folded.
inline RwInt32 always_0()
{
    return 0;
}

// match: ?sub_174950@@YAXXZ @ 0x00174950
// Clears the index-sound table (the game loop's set-up).
void sub_174950()
{
    dword_4E5E40.unk_08 = 0;
    dword_4E5E40.unk_00[0] = 0;
    dword_4E5E40.unk_00[1] = 0;
}

// match: ?vf_0E0@type_3DD948@@UAEPAEXZ @ 0x00174980
RwUInt8 *type_3DD948::vf_0E0()
{
    return (RwUInt8 *)unk_424;
}

// match: ?vf_0EC@type_3DD948@@UAEXHH@Z @ 0x001749A0
void type_3DD948::vf_0EC(RwInt32 arg_0, RwInt32 arg_4)
{
    unk_424[arg_0] = (RwInt16)arg_4;
}

// match: ?vf_090@type_3DD948@@UAEPAUtype_6D380@@XZ @ 0x001749C0
type_6D380 *type_3DD948::vf_090()
{
    return (type_6D380 *)sub_67620(unk_3C8);
}

// match: ??_Gtype_3DD948@@UAEPAXI@Z @ 0x001749E0
// match: ??1type_3DD948@@UAE@XZ @ 0x00174A10
// match: __ehhandler$??1type_3DD948@@UAE@XZ-0x16 @ 0x00301FD0
// match: __ehhandler$??1type_3DD948@@UAE@XZ @ 0x00301FE6
// vf_230, called directly as in any destructor, then the members' destructors and the
// base's. Defined here, before the factory: the image has its EH handler first.
type_3DD948::~type_3DD948()
{
    vf_230();
}

// match: ?sub_174A70@@YAPAUtype_3DD948@@PAURwV3d@@MPAUtype_3D3548@@@Z @ 0x00174A70
// match: __ehhandler$?sub_174A70@@YAPAUtype_3DD948@@PAURwV3d@@MPAUtype_3D3548@@@Z-0x11 @ 0x00301FF0
// match: __ehhandler$?sub_174A70@@YAPAUtype_3DD948@@PAURwV3d@@MPAUtype_3D3548@@@Z @ 0x00302001
type_3DD948 *sub_174A70(RwV3d *arg_0, RwReal arg_4, type_3D3548 *arg_8)
{
    type_3DD948 *var_10;

    var_10 = 0;
    var_10 = (type_3DD948 *)sub_D56D0(0x440, 0, 0);
    if (var_10 != 0)
        var_10 = new (var_10) type_3DD948(arg_0, arg_4, arg_8);
    return var_10;
}

// match: ??0type_3DD948@@QAE@PAURwV3d@@MPAUtype_3D3548@@@Z @ 0x00174B20
// match: __ehhandler$??0type_3DD948@@QAE@PAURwV3d@@MPAUtype_3D3548@@@Z-0x16 @ 0x00302010
// match: __ehhandler$??0type_3DD948@@QAE@PAURwV3d@@MPAUtype_3D3548@@@Z @ 0x00302026
type_3DD948::type_3DD948(RwV3d *arg_0, RwReal arg_4, type_3D3548 *arg_8)
{
    unk_344.sub_144940(arg_8->get_unk_34C());
    sub_174BC0(arg_0, arg_4, arg_8);
}

// match: ?sub_174BC0@type_3DD948@@QAEHPAURwV3d@@MPAUtype_3D3548@@@Z @ 0x00174BC0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_3DD948::sub_174BC0(RwV3d *arg_0, RwReal arg_4, type_3D3548 *arg_8)
{
    RwUInt32 var_3C;
    RwUInt32 w38;
    RwInt32 ebp_34;
    type_3DFEEC *var_30;
    type_3DF8D8 *v2C;
    type_3DF8D8 *lcl_28;
    RwFrame *frm_24;
    type_3D2E7C *var_20;
    RpAtomic *l1C;
    type_3DF8D8 *m_18;
    RpAtomic *ebp_14;
    type_7C8D0 *lv_10;
    RpHAnimHierarchy *var_C;
    type_712B0_10F710 *bp_8;
    type_3D2CD0 *bp_4;

    unk_41C.sub_D48D0(arg_8);
    unk_3CC = 1;
    unk_88 |= 0x2000;
    unk_48 = arg_4;
    unk_4C = arg_4;
    unk_50_r = arg_4 / 2.0f;
    zero_v3d(&unk_3C_v);
    unk_28 = 0x14;
    unk_2C = 0x100000; // not an address: entity kind bits
    unk_30 = 0x40;
    set_xyz(&unk_10C, -1.0f, -1.0f, -1.0f);
    set_xyz(&unk_134, -1.0f, -1.0f, -1.0f);
    zero_v3d(&unk_118);
    set_xyz(&unk_124, 1000.0f, 1000.0f, 1000.0f);
    unk_130 = 0;
    sub_D5B80(this, 0xF);
    bp_8 = (type_712B0_10F710 *)arg_8->get_unk_34C();
    m_18 = sub_198800(&bp_8->unk_24C);
    if (!m_18 || m_18->vf_008() != 3)
        return 0;
    vf_224(m_18, 1, 0);
    ebp_14 = unk_250.unk_08;
    sub_173620(ebp_14);
    unk_28 &= ~0x20000; // not an address: entity flag
    frm_24 = unk_338.unk_08;
    l1C = RpAtomicCreate();
    RpAtomicSetFrame(l1C, frm_24);
    l1C->boundingSphere.center.x = 0;
    l1C->boundingSphere.center.y = 0;
    l1C->boundingSphere.center.z = 0;
    l1C->boundingSphere.radius = arg_4;
    l1C->object[2] = 1;
    sub_FB990(l1C, 4);
    sub_173320(l1C);
    unk_274.sub_129430(l1C);
    unk_274.sub_1294A0(this);
    unk_58 = 0;
    unk_3B0 = 0;
    unk_3B4 = 0;
    unk_3B8 = 0;
    unk_3BC = 0;
    w38 = sub_71870();
    unk_3C4 = w38;
    var_20 = vf_098();
    var_20->sub_70DF0(this, 2);
    if (bp_8->unk_450.unk_00 || bp_8->unk_450.unk_04)
    {
        lcl_28 = sub_198800(&bp_8->unk_450);
        var_20->sub_70E10(lcl_28->get_unk_18(), 1);
    }
    if (bp_8->unk_458.unk_00 || bp_8->unk_458.unk_04)
    {
        v2C = sub_198800(&bp_8->unk_458);
        var_20->sub_70F40(v2C->get_unk_18(), 1);
    }
    if (bp_8->unk_460.unk_00)
    {
        var_30 = (type_3DFEEC *)sub_198800(&bp_8->unk_460);
        ((type_D48D0 *)&var_30->unk_24_id)->sub_D48D0(this);
        var_30->unk_10 = 2;
    }
    var_3C = sub_78830(0);
    unk_280 = var_3C;
    lv_10 = (type_7C8D0 *)sub_78AC0(unk_280);
    unk_284 = lv_10;
    var_C = sub_16D970(get_unk_264());
    lv_10->sub_79470(var_C);
    lv_10->unk_1C = (RwInt32)this;
    bp_4 = (type_3D2CD0 *)sub_71770(1);
    unk_3C8_h = bp_4->get_unk_04_h();
    bp_4->sub_6CDA0(this, 4);
    memset(unk_424, 0, 6);
    for (ebp_34 = 0; ebp_34 < 2; ebp_34++)
        unk_428[ebp_34] = 1;
    unk_420 = (RwCamera *)dword_4E5C74;
    unk_418 = -1;
    unk_418 = unk_414;
    unk_414 = 0;
    sub_157680();
    if (!always_0())
        unk_28 = 0x14;
    else
        unk_28 = 0x10;
    unk_410 = 0.02f;
    RwMatrixSetIdentityMacro(&unk_3D0);
    unk_42C = 0;
    unk_430 = 0;
    unk_4E5E50.sub_176100();
    return 1;
}

// match: ?vf_230@type_3DD948@@UAEXXZ @ 0x00175190
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Shuts it down once: its collision atomic taken off its frame and
// released, its script object and performance player freed, its animation
// released.
void type_3DD948::vf_230()
{
    type_3D2E7C *var_8;
    RpAtomic *l4;

    if (unk_3CC)
    {
        unk_3CC = 0;
        l4 = unk_274.unk_08;
        RpAtomicSetFrame(l4, 0);
        unk_274.sub_1294D0();
        vf_228();
        var_8 = vf_098();
        if (var_8)
        {
            sub_71970((type_3D2C88 *)var_8);
            unk_3C4 = 0;
        }
        if (vf_090())
        {
            sub_717B0((type_3D2C88 *)vf_090());
            unk_3C8 = 0;
        }
        sub_78870(unk_280);
        unk_280 = 0;
    }
}

// match: ?vf_1C4@type_3DD948@@UAEXH@Z @ 0x00175280
void type_3DD948::vf_1C4(RwInt32 arg_0)
{
    unk_3B0 = 1;
}

// match: ?sub_1752A0@type_3DD948@@QAEXPAURwMatrixTag@@@Z @ 0x001752A0
void type_3DD948::sub_1752A0(RwMatrix *arg_0)
{
    RwFrame *var_4;

    var_4 = RwCameraGetFrame(unk_420);
    if (var_4)
        RwFrameTransform(var_4, arg_0, rwCOMBINEREPLACE);
}

// match: ?vf_03C@type_3DD948@@UAEXM@Z @ 0x001752E0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Moves the render camera by its mode (see types/type_3DD948.h), then the
// base step.
void type_3DD948::vf_03C(RwReal arg_0)
{
    RwV3d loc78;
    RwV3d bp_6C;
    RtQuat lv_60;
    RwReal lcl_50;
    RtQuat var_4C;
    RwReal p3C;
    RwReal stk_38;
    type_3D2E7C *t34;
    RwMatrix *slot_30;
    RwFrame *v2C;
    RwMatrix *lcl_28;
    RwFrame *frm_24;
    RwInt32 var_20;
    RwMatrix *l1C;
    RwV3d m_18;
    RwFrame *var_C;
    type_10F710 *bp_8;
    RwCamera *bp_4;

    bp_8 = (type_10F710 *)unk_41C.sub_D4910();
    bp_4 = unk_420;
    var_C = RwCameraGetFrame(bp_4);
    sub_19B650(RwFrameGetMatrix(RwCameraGetFrame(bp_4)));
    if (unk_414 == 0)
    {
        bp_8->vf_244();
        frm_24 = get_unk_340();
        var_20 = 1;
        if (bp_8->unk_19D0 == 10)
        {
            unk_28 |= 0x20;
            if (unk_3B0)
            {
                lcl_28 = RwFrameGetMatrix(frm_24);
                RwFrameTransform(var_C, lcl_28, rwCOMBINEREPLACE);
            }
        }
        l1C = RwFrameGetMatrix(var_C);
        m_18 = l1C->pos;
        if (var_20)
        {
            RwFrameTransform(frm_24, l1C, rwCOMBINEREPLACE);
            if (unk_3B0)
                l1C->pos = m_18;
        }
    }
    else if (unk_414 == 1)
    {
    }
    else if (unk_414 == 2 || unk_414 == 3)
    {
        v2C = get_unk_340();
        slot_30 = RwFrameGetMatrix(v2C);
        unk_88 &= ~0x200;
        if (unk_410 == 1.0f)
        {
            RwFrameTransform(v2C, &unk_3D0, rwCOMBINEREPLACE);
            t34 = vf_098();
            if (t34)
            {
                stk_38 = deltaTime;
                sub_6B5F0("IHaveArrived", (type_67620 *)t34, 0, 0, (RwInt32 *)(&stk_38), 1, 1, 0);
            }
        }
        else
        {
            lcl_50 = arg_0 * unk_410;
            if (lcl_50 < 0.0f)
                lcl_50 = 0.0f;
            else if (lcl_50 > 1.0f)
                lcl_50 = 1.0f;
            loc78.x = (unk_3D0.pos.x - slot_30->pos.x) * lcl_50 + slot_30->pos.x;
            loc78.y = (unk_3D0.pos.y - slot_30->pos.y) * lcl_50 + slot_30->pos.y;
            loc78.z = (unk_3D0.pos.z - slot_30->pos.z) * lcl_50 + slot_30->pos.z;
            RtQuatConvertFromMatrix(&lv_60, slot_30);
            RtQuatConvertFromMatrix(&var_4C, &unk_3D0);
            sub_13FBC0(&var_4C, &lv_60, &var_4C, lcl_50);
            RtQuatConvertToMatrix(&var_4C, slot_30);
            slot_30->pos.x = loc78.x;
            slot_30->pos.y = loc78.y;
            slot_30->pos.z = loc78.z;
            RwMatrixUpdate(slot_30);
            RwV3dSubMacro(&bp_6C, &slot_30->pos, &unk_3D0.pos);
            p3C = RwV3dLength((RwV3d *)&bp_6C);
            if (p3C < 10.0f)
            {
                type_3D2E7C *var_B4;
                RwReal vB0;
                RwReal stk_B8;

                vB0 = RwV3dDotProductMacro(&slot_30->at, &unk_3D0.at);
                if (vB0 >= 0.9f)
                {
                    var_B4 = vf_098();
                    if (var_B4)
                    {
                        stk_B8 = deltaTime;
                        sub_6B5F0("IHaveArrived", (type_67620 *)var_B4, 0, 0, (RwInt32 *)(&stk_B8), 1, 1, 0);
                    }
                }
            }
        }
        if (unk_414 != 3)
            RwFrameTransform(var_C, slot_30, rwCOMBINEREPLACE);
    }
    else if (unk_414 == 4)
    {
        RwV3d vC4;
        RwMatrix *lC8;

        if (unk_42C)
        {
            RwV3d var_D4;

            lC8 = RwFrameGetMatrix(var_C);
            RpSplineFindPosition(unk_42C->unk_28, rpSPLINEPATHSMOOTH, unk_430, &var_D4, &vC4);
            sub_140CE0(lC8, &var_D4, &vC4);
            unk_430 += arg_0 * unk_410;
            if (unk_430 >= 1.0f)
            {
                type_3D2E7C *var_D8;

                unk_430 = 0;
                var_D8 = vf_098();
                if (var_D8)
                    sub_6B5F0("SplinePath_ArrivedATDestination", (type_67620 *)(vf_098()), 0, 0, 0, 0, 1, 0);
            }
            RwMatrixUpdate(lC8);
            RwFrameTransform(get_unk_340(), lC8, rwCOMBINEREPLACE);
        }
    }
    // A check with its body compiled out (it shifts the registers after it).
    if (!RwCameraGetFrame(bp_4))
    {
    }
    sub_19B650(RwFrameGetMatrix(RwCameraGetFrame(bp_4)));
    RwFrameGetMatrix(RwCameraGetFrame(bp_4))->flags = 3;
    RwMatrixOrthoNormalize(RwFrameGetMatrix(RwCameraGetFrame(bp_4)), RwFrameGetMatrix(RwCameraGetFrame(bp_4)));
    sub_19B650(RwFrameGetMatrix(RwCameraGetFrame(bp_4)));
    type_3D3548::vf_03C(arg_0);
}

// match: ?vf_04C@type_3DD948@@UAEXM@Z @ 0x00175AD0
// Its render step: the base's animation step; in mode 1 the render camera
// on the entity's head bone (0x97); the shake; the object at unk_4E5E50
// given the camera's matrix; the field of view.
void type_3DD948::vf_04C(RwReal arg_0)
{
    RpHAnimHierarchy *var_8;
    RwMatrix *var_C;
    RwMatrix *var_10;
    RwMatrix var_50;
    RwCamera *var_54;
    RwFrame *var_58;
    RwMatrix *var_5C;
    RwV3d var_80;
    RwMatrix *var_C8;

    sub_CDF40(arg_0);
    if (unk_414 == 1)
    {
        unk_88 |= 0x200;
        var_8 = unk_284->unk_18;
        var_C = RpHAnimHierarchyGetMatrixArray(var_8);
        var_10 = &var_C[RpHAnimIDGetIndex(var_8, 0x97)];
        RwMatrixOrthoNormalize(&var_50, var_10);
        sub_1752A0(&var_50);
    }
    var_54 = unk_420;
    sub_19B650(RwFrameGetMatrix(RwCameraGetFrame(var_54)));
    var_58 = RwCameraGetFrame(var_54);
    if (unk_3B8 > 0.0f && unk_3B4 > 0.0f)
    {
        var_5C = RwFrameGetMatrix(var_58);
        var_80.x = frand_range(-unk_3B4, unk_3B4);
        var_80.y = frand_range(-unk_3B4, unk_3B4);
        var_80.z = frand_range(-unk_3B4, unk_3B4);
        RwFrameTranslate(var_58, &var_80, rwCOMBINEPOSTCONCAT);
        RwFrameRotate(var_58, &var_5C->at, frand_range(-unk_3B4, unk_3B4), rwCOMBINEPRECONCAT);
        unk_3B4 = unk_3B4 - unk_3BC;
        unk_3B8 = unk_3B8 - arg_0;
        if (unk_3B4 < 0.0f)
            unk_3B4 = 0;
    }
    var_C8 = RwFrameGetMatrix(var_58);
    unk_4E5E50.sub_1765E0(var_C8);
    RWS::CameraHelper::SetFieldOfView(unk_3C0, var_54);
    RwFrameUpdateObjects(var_58);
    sub_19B650(RwFrameGetMatrix(RwCameraGetFrame(var_54)));
    unk_418 = unk_414;
}

// match: ?vf_044@type_3DD948@@UAEXM@Z @ 0x00175E30
void type_3DD948::vf_044(RwReal arg_0)
{
    type_3D3548::vf_044(arg_0);
}

// match: ?sub_175E50@type_3DD948@@QAEXMMM@Z @ 0x00175E50
void type_3DD948::sub_175E50(RwReal arg_0, RwReal arg_4, RwReal arg_8)
{
    type_10F710 *var_4;

    var_4 = (type_10F710 *)unk_41C.sub_D4910();
    if (var_4 && var_4->unk_1B04 && arg_0 > 3.0f)
        arg_0 = 3.0f;
    if (arg_4 > unk_3B8)
    {
        unk_3B4 = arg_0 * 0.5f;
        unk_3B8 = arg_4;
        unk_3BC = arg_8;
    }
}

// match: ?vf_098@type_3DD948@@UAEPAUtype_3D2E7C@@XZ @ 0x00175EE0
type_3D2E7C *type_3DD948::vf_098()
{
    return (type_3D2E7C *)sub_67620(unk_3C4);
}

// match: ?sub_175F00@type_3DD948@@QAEXPAURwMatrixTag@@@Z @ 0x00175F00
void type_3DD948::sub_175F00(RwMatrix *arg_0)
{
    unk_3D0.pos.x = arg_0->pos.x;
    unk_3D0.pos.y = arg_0->pos.y;
    unk_3D0.pos.z = arg_0->pos.z;
    unk_3D0.up.x = arg_0->up.x;
    unk_3D0.up.y = arg_0->up.y;
    unk_3D0.up.z = arg_0->up.z;
    unk_3D0.right.x = arg_0->right.x;
    unk_3D0.right.y = arg_0->right.y;
    unk_3D0.right.z = arg_0->right.z;
    unk_3D0.at.x = arg_0->at.x;
    unk_3D0.at.y = arg_0->at.y;
    unk_3D0.at.z = arg_0->at.z;
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??2type_3DD948@@SAPAXIPAX@Z (folded into 0x6CCF0)
void *type_3DD948::operator new(RwUInt32 arg_0, void *arg_4)
{
    return arg_4;
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??3type_3DD948@@SAXPAX@Z (folded into 0x19A750)
void type_3DD948::operator delete(void * arg_0)
{
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??3type_3DD948@@SAXPAX0@Z (folded into 0x19A750)
void type_3DD948::operator delete(void * arg_0, void * arg_4)
{
}
