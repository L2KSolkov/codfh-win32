// The front end's world, and the simple mechanism (type_3DAC58, the entity
// SimpleMechanicTrigger spawns): it follows its spline path and takes damage.

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "rw/bamatrix.h"
#include "rw/bavector.h"
#include "rw/baframe.h"
#include "rw/rpworld.h"
#include "game/functions.h"
#include "game/vecutil.h"
#include "types/type_3D3548.h"
#include "types/type_3DF8D8.h"
#include "types/SimpleMechanicTrigger.h"
#include "types/SplinePath.h"
#include "types/type_3DAC58.h"
#include "types/type_3D32F8.h"
#include "types/type_3D51C0.h"
#include "types/type_4B85F8.h"
#include "types/type_D48D0.h"
#include "types/alfaobject.h"
#include "types/alfamessman.h"
#include "types/type_3D2E7C.h"
#include "game/data.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003DAC50
// The front end's world's half size (a constant of this unit's, read from
// memory).
const RwReal WorldHalfSize = 500000.0f;
// 0x003DAC54
extern const RwReal flt_3DAC54 = 16.666666f;
// End of its data definitions.

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: _WorldHalfSize @ 0x003DAC50
// match: ?flt_3DAC54@@3MB @ 0x003DAC54
// match: ??_7type_3DAC58@@6B@ @ 0x003DAC58
// match: ??_C@_0BF@NPKGKGI@SimpleMechanicEntity?$AA@ @ 0x003DAE90
// match: __ehhandler$?sub_133230@@YAPAUtype_3DAC58@@PAUtype_712B0@@@Z>1>8 @ 0x0041DA78
// match: __ehhandler$?sub_133230@@YAPAUtype_3DAC58@@PAUtype_712B0@@@Z>1 @ 0x0041DA88
// match: __ehhandler$??1type_3DAC58@@UAE@XZ>1>8 @ 0x0041DAA4
// match: __ehhandler$??1type_3DAC58@@UAE@XZ>1 @ 0x0041DAAC

// match: ?sub_1331E0@@YAPAURpWorld@@XZ @ 0x001331E0
// sp-match: ?sub_1331E0@@YAPAURpWorld@@XZ @ 0x000E3970

// Makes the front end's world: empty, a million units across.
RpWorld *sub_1331E0()
{
    RwBBox boundingBox;
    RpWorld *pWorld;

    boundingBox.inf.z = -WorldHalfSize;
    boundingBox.inf.y = boundingBox.inf.z;
    boundingBox.inf.x = boundingBox.inf.y;
    boundingBox.sup.z = WorldHalfSize;
    boundingBox.sup.y = boundingBox.sup.z;
    boundingBox.sup.x = boundingBox.sup.y;

    pWorld = RpWorldCreate(&boundingBox);

    return pWorld;
}

// match: ?sub_133230@@YAPAUtype_3DAC58@@PAUtype_712B0@@@Z @ 0x00133230
// match: __ehhandler$?sub_133230@@YAPAUtype_3DAC58@@PAUtype_712B0@@@Z-0x19 @ 0x00301810
// match: __ehhandler$?sub_133230@@YAPAUtype_3DAC58@@PAUtype_712B0@@@Z @ 0x00301829
// sp-match: ?sub_133230@@YAPAUtype_3DAC58@@PAUtype_712B0@@@Z @ 0x000E4340
// (its constructor, defined in the class: single player calls its out-of-line copy)
// sp-match: ??0type_3DAC58@@QAE@PAUtype_712B0@@@Z @ 0x000E41D0
type_3DAC58 *sub_133230(type_712B0 *arg_0)
{
    type_3DAC58 *var_10;

    var_10 = (type_3DAC58 *)sub_D56D0(0x420, arg_0->unk_24_18, arg_0->vf_008());
    if (var_10 != 0)
    {
        var_10 = new (var_10) type_3DAC58(arg_0);
        if (var_10->unk_28 & 0x400000) // not an address: entity flag
        {
            sub_D5A60(var_10, 0);
            var_10 = 0;
        }
    }
#ifndef CODFH_SP // single player compiles the debug print out
    else
    {
        sub_19A750("WARNING: A spawn could not be created due to lack of entity memory. Trigger "
                   "location(%6.2f,%6.2f,%6.2f)",
                   arg_0->unk_90, arg_0->unk_94, arg_0->unk_98);
    }
#endif
    return var_10;
}

// The class's inline overrides (rws header order), emitted with its vtable.
// match: ?vf_09C@type_3DAC58@@UAEHXZ @ 0x00133360
// match: ?vf_0A0@type_3DAC58@@UAEXI@Z @ 0x00133380
// match: ?vf_124@type_3DAC58@@UAEXM@Z @ 0x001333A0
// match: ?vf_128@type_3DAC58@@UAEMXZ @ 0x001333C0
// match: ?vf_174@type_3DAC58@@UAEHXZ @ 0x001333E0
// match: ?vf_178@type_3DAC58@@UAEXH@Z @ 0x00133400
// match: ?vf_180@type_3DAC58@@UAEXH@Z @ 0x00133420
// match: ?vf_17C@type_3DAC58@@UAEMXZ @ 0x00133470
// match: ?vf_0F4@type_3DAC58@@UAEPAUSplinePath@@XZ @ 0x00133490
// sp-match: ?vf_0F4@type_3DAC58@@UAEPAUSplinePath@@XZ @ 0x000E42C0
// sp-match: ?vf_09C@type_3DAC58@@UAEHXZ @ 0x000E4220
// sp-match: ?vf_0A0@type_3DAC58@@UAEXI@Z @ 0x000E4230
// sp-match: ?vf_124@type_3DAC58@@UAEXM@Z @ 0x000E4240
// sp-match: ?vf_128@type_3DAC58@@UAEMXZ @ 0x000E4250
// sp-match: ?vf_174@type_3DAC58@@UAEHXZ @ 0x000E4260
// sp-match: ?vf_178@type_3DAC58@@UAEXH@Z @ 0x000E4270
// sp-match: ?vf_180@type_3DAC58@@UAEXH@Z @ 0x000E4280
// sp-match: ?vf_17C@type_3DAC58@@UAEMXZ @ 0x000E42B0

// match: ??_Gtype_3DAC58@@UAEPAXI@Z @ 0x001334B0
// match: ??1type_3DAC58@@UAE@XZ @ 0x001334E0
// match: __ehhandler$??1type_3DAC58@@UAE@XZ-0x8 @ 0x00301840
// match: __ehhandler$??1type_3DAC58@@UAE@XZ @ 0x00301848
// sp-match: ??1type_3DAC58@@UAE@XZ @ 0x000E42F0
// sp-match: ??_Gtype_3DAC58@@UAEPAXI@Z @ 0x000E42D0
type_3DAC58::~type_3DAC58()
{
    vf_230();
}

// match: ?vf_234@type_3DAC58@@UAEHPAUtype_712B0@@@Z @ 0x00133540
// sp-match: ?vf_234@type_3DAC58@@UAEHPAUtype_712B0@@@Z @ 0x000E39B0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_3DAC58::vf_234(type_712B0 *arg_0)
{
    RwUInt32 var_2C;
    type_3DF8D8 *var_28;
    type_3DFEEC *ebp_24;
    type_3DF8D8 *var_20;
    type_3DF8D8 *l1C;
    type_3D2E7C *m_18;
    type_3DF8D8_3 *ebp_14;
    RwInt32 lv_10;
    type_3DFEEC *var_C;
    type_3DF8D8 *bp_8;
    SimpleMechanicTrigger *bp_4;

    bp_4 = (SimpleMechanicTrigger *)arg_0;
    if (bp_4->unk_D8.unk_00 != 0)
    {
        var_C = (type_3DFEEC *)sub_198800(&bp_4->unk_D8);
        ((type_D48D0 *)&var_C->unk_24_id)->sub_D48D0(this);
        var_C->unk_10 = 0x202;
    }
    unk_418 = 1;
    sub_CCCD0(arg_0);
    unk_28 = 4;
    unk_2C = 0x2000;            // not an address: kind bits
    unk_30 = -1;
    unk_414 = bp_4->unk_F4;
    unk_410 = unk_414;
    zero_v3d(&unk_118);
    set_xyz(&unk_124, 1.0e37f, 1.0e37f, 1.0e37f);
    unk_130 = 1;
    unk_3C0 = 1.0f;
    RwMatrixSetIdentityMacro(&unk_3D0);
    bp_8 = sub_198800(&bp_4->unk_C0);
    if (bp_8 == 0 || bp_8->vf_008() != 3)
    {
        sub_D3FB0("SimpleMechanicEntity", arg_0, &bp_4->unk_C0);
        unk_3B0 = 0;
        unk_3B8 = 0;
        unk_3B4 = 0.0f;
        unk_3BC = 0.0f;
        unk_28 |= 0x400000;     // not an address: a flag
        return 0;
    }
    ebp_14 = (type_3DF8D8_3 *)bp_8;
    unk_290 = ebp_14->get_unk_44();
    vf_224(ebp_14, 0, &lv_10);
    sub_16E080(get_unk_264(), ebp_14->get_unk_54());
    var_20 = sub_198800(&bp_4->unk_C8);
    var_2C = sub_71870();
    unk_3B0 = var_2C;
    m_18 = vf_098();
    m_18->sub_70DF0(this, 2);
    m_18->sub_70E10(var_20->get_unk_18(), 1);
    l1C = sub_198800(&bp_4->unk_D0);
    if (l1C != 0)
        m_18->sub_70F40(l1C->get_unk_18(), 1);
    sub_D5B80(this, 5);
    unk_3B8 = 0;
    unk_3B4 = 0.0f;
    if (bp_4->unk_E8.unk_00 != 0 || bp_4->unk_E8.unk_04 != 0)
    {
        var_28 = sub_198800(&bp_4->unk_E8);
        ebp_24 = (type_3DFEEC *)var_28;
        unk_3B8 = ebp_24->unk_24;
        unk_3BC = *(RwReal *)&bp_4->unk_F0;
    }
    return 1;
}

// match: ?vf_230@type_3DAC58@@UAEXXZ @ 0x00133910
// sp-match: ?vf_230@type_3DAC58@@UAEXXZ @ 0x000E3C10
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Takes it down: its trigger's particle system where it stands when it was
// destroyed, its AI object, and the trigger's key's entity.
void type_3DAC58::vf_230()
{
    type_3DFEEC *var_10;
    RwFrame *var_C;
    RwMatrix *bp_8;
    SimpleMechanicTrigger *bp_4;

    if (unk_418)
    {
        bp_4 = (SimpleMechanicTrigger *)unk_344.unk_08;
        if (unk_410 <= 0 && bp_4 != 0 && bp_4->unk_F8 != 0)
        {
            var_C = unk_338.unk_08;
            bp_8 = RwFrameGetLTM(var_C);
            sub_F2FF0(bp_4->unk_F8, bp_8, 0, 1, false, false);
        }
        unk_418 = 0;
        vf_228();
        if (vf_098())
        {
            sub_71970((type_3D2C88 *)vf_098());
            unk_3B0 = 0;
        }
        if (bp_4 != 0 && bp_4->unk_D8.unk_00 != 0)
        {
            var_10 = (type_3DFEEC *)sub_198800(&bp_4->unk_D8);
            ((type_D48D0 *)&var_10->unk_24_id)->sub_D48D0(0);
        }
    }
}

// match: ?vf_03C@type_3DAC58@@UAEXM@Z @ 0x00133A20
// sp-match: ?vf_03C@type_3DAC58@@UAEXM@Z @ 0x000E3CD0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Moves it along its path by its speed (turning back at the ends, stopping
// at the start or at the end by the path's mode), facing the next step, and
// tells its scripts when it arrives.
void type_3DAC58::vf_03C(RwReal arg_0)
{
#ifndef CODFH_SP // single player scopes it to its block (SP 0xE3CD0: sub esp 0x10, it shares a slot)
    RwReal var_1C;
#endif
    RwInt32 var_18;
    RwInt32 var_14;
    RwReal lv_10;
    RwV3d var_C;

    type_3D3548::vf_03C(arg_0);
    if (unk_3B8 != 0 && !unk_28_9)
    {
        var_14 = 0;
        var_18 = 0;
        lv_10 = unk_3B4;
        unk_3B4 += unk_3BC;
#ifdef CODFH_SP // shape: SP 0xE3D11 compares in single precision (fcom) and copies the limit
        if (unk_3B4 > unk_3C0)
        {
            unk_3B4 = unk_3C0;
        }
#else
        if ((RwDouble)unk_3B4 > (RwDouble)unk_3C0)
        {
            unk_3B4 = (RwReal)(RwDouble)unk_3C0;
        }
#endif
        else if (unk_3B4 < 0.0f)
        {
            unk_3B4 = 0.0f;
        }
        if (unk_3BC != 0.0f && (unk_3B4 >= unk_3C0 || unk_3B4 <= 0.0f))
        {
            if ((unk_3B8->unk_1C & 3) == 2)
                unk_3BC = -unk_3BC;
            else if ((unk_3B8->unk_1C & 3) == 1)
                unk_3B4 = 0.0f;
            else
                var_18 = 1;
            var_14 = 1;
        }
        lv_10 = unk_3B4 + unk_3BC;
        if (lv_10 > 1.0f)
            lv_10 = 1.0f;
        else if (lv_10 < 0.0f)
            lv_10 = 0.0f;
        unk_3B8->sub_BA990(unk_3B4, &var_C, &unk_3D0);
        vf_0C0(&var_C);
        unk_3B8->sub_BA990(lv_10, &var_C, &unk_3D0);
        vf_0D0(&var_C);
        if (var_14 != 0)
        {
#ifdef CODFH_SP
            RwReal var_1C;
#endif
            var_1C = deltaTime;
            sub_6B5F0("IHaveArrived", (type_67620 *)(vf_098()), 0, 0, (RwInt32 *)(&var_1C), 1, 1, 0);
            sub_6B5F0("SplinePath_ArrivedATDestination", (type_67620 *)(vf_098()), 0, 0, 0, 0, 1, 0);
        }
        if (var_18 != 0)
        {
            unk_3B8 = 0;
            unk_3B4 = 0.0f;
            unk_3C0 = 1.0f;
        }
    }
}

// match: ?vf_064@type_3DAC58@@UAEHPAUtype_75600@@@Z @ 0x00133CD0
// sp-match: ?vf_064@type_3DAC58@@UAEHPAUtype_75600@@@Z @ 0x000E3EC0
// Hit by a bullet: by its trigger's flags (unk_104 bullets at all, unk_FC
// and unk_100 from allies and enemies), off its health.
RwInt32 type_3DAC58::vf_064(type_75600 *arg_0)
{
    SimpleMechanicTrigger *v8;
    type_3D3548 *varC;
    RwInt32 var_4;

    if (arg_0 != 0 && arg_0->unk_28 > 0.0f)
    {
        v8 = (SimpleMechanicTrigger *)unk_344.unk_08;
        if (v8->unk_104 == 0)
            return 0;
        if (arg_0->unk_0C != 0)
        {
            varC = arg_0->unk_0C;
            if (v8->unk_FC == 0 && varC->unk_2C_0)
                return 0;
            if (v8->unk_100 == 0 && varC->unk_2C_1)
                return 0;
        }
        sub_6B5F0("HitByBullet", (type_67620 *)(vf_098()), 0, 0, 0, 0, 1, 0);
        var_4 = 0;
        sub_6B5F0("HitByBulletRWS", (type_67620 *)(vf_098()), 0, 0, &var_4, 1, 1, 0);
        unk_410 -= (RwInt32)arg_0->unk_28;
        sub_D2AD0(arg_0->unk_0C, arg_0->unk_04);
    }
    return 0;
}

// match: ?vf_068@type_3DAC58@@UAEHPAUtype_758F0@@@Z @ 0x00133E00
// sp-match: ?vf_068@type_3DAC58@@UAEHPAUtype_758F0@@@Z @ 0x000E3FA0
// Hit by an explosion: likewise (unk_108), telling the script where it came
// from and whether in front.
RwInt32 type_3DAC58::vf_068(type_758F0 *arg_0)
{
    RwV3d *ebp_34;
    RwFrame *var_30;
    RwV3d bp_2C;
    SimpleMechanicTrigger *local_20;
    RwMatrix *var_1C;
    RwInt32 var_18;
    type_758F0_14 var_14;

    if (arg_0 != 0 && arg_0->unk_2C > 0 && vf_070(arg_0, 0, 0)) {
        local_20 = (SimpleMechanicTrigger *)unk_344.unk_08;
        if (local_20->unk_108 == 0)
            return 0;
        unk_410 -= (RwInt32)arg_0->unk_2C;
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
    }
    return 0;
}

// match: ?vf_098@type_3DAC58@@UAEPAUtype_3D2E7C@@XZ @ 0x00133FD0
// sp-match: ?vf_098@type_3DAC58@@UAEPAUtype_3D2E7C@@XZ @ 0x000E4110
type_3D2E7C *type_3DAC58::vf_098()
{
    return (type_3D2E7C *)sub_67620(unk_3B0);
}

// Whether arg_0 is its trigger's model's name.
// match: ?vf_058@type_3DAC58@@UAEHPAUtype_3DF8D8_04@@@Z @ 0x00133FF0
// sp-match: ?vf_058@type_3DAC58@@UAEHPAUtype_3DF8D8_04@@@Z @ 0x000E4120
RwInt32 type_3DAC58::vf_058(type_3DF8D8_04 *arg_0)
{
    SimpleMechanicTrigger *var_4;

    var_4 = (SimpleMechanicTrigger *)get_unk_34C();
    if (arg_0->unk_00 == var_4->unk_C0.unk_00 && arg_0->unk_04 == var_4->unk_C0.unk_04)
        return 1;
    return 0;
}

// match: ?vf_0F8@type_3DAC58@@UAEXM@Z @ 0x00134040
// sp-match: ?vf_0F8@type_3DAC58@@UAEXM@Z @ 0x000E4150
// Puts it at arg_0 (0 to 1) along its path.
void type_3DAC58::vf_0F8(RwReal arg_0)
{
    RwV3d var_C;

    if (arg_0 < 0.0f)
        arg_0 = 0.0f;
    if (arg_0 > 1.0f)
        arg_0 = 1.0f;
    unk_3B4 = arg_0;
    if (unk_3B8 != 0)
    {
        unk_3B8->sub_BA990(unk_3B4, &var_C, &unk_3D0);
        vf_0C0(&var_C);
    }
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??2type_3DAC58@@SAPAXIPAX@Z (folded into 0x6CCF0)
void *type_3DAC58::operator new(RwUInt32 arg_0, void *arg_4)
{
    return arg_4;
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??3type_3DAC58@@SAXPAX@Z (folded into 0x19A750)
#ifndef CODFH_SP // single player keeps the call to the empty delete (SP 0xE42E0): its body is not in this object
void type_3DAC58::operator delete(void * arg_0)
{
}
#endif

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??3type_3DAC58@@SAXPAX0@Z (folded into 0x19A750)
void type_3DAC58::operator delete(void * arg_0, void * arg_4)
{
}
