// The gimp vehicle (type_3DE0E0), the entity a GimpVehicleTrigger of type 0
// makes.

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "rw/osintf.h"
#include "game/functions.h"
#include "game/data.h"
#include "types/type_3D3548.h"
#include "types/type_3DE0E0.h"
#include "types/GimpVehicleTrigger.h"
#include "types/type_44350.h"
#include "types/type_3D32F8.h"
#include "types/type_3DF8D8.h"
#include "types/type_3DBC78.h"
#include "game/vecutil.h"
#include "rw/rphanim.h"
#include "types/alfaobject.h"
#include "types/animbank.h"
#include "rw/bamemory.h"
#include "game/clumpdata.h"
#include <string.h>
#include "types/type_3D51C0.h"
#include "types/type_4B85F8.h"
#include "types/SoldierTrigger.h"
#include "types/SplinePath.h"
#include "types/alfasched.h"
#include "types/animkey.h"
#include "rw/rtanim.h"
#include "rw/rtquat.h"
#include "rw/bamatrix.h"
#include "game/gameloop.h"
#include "types/type_4E5D30.h"
#include "rw/baframe.h"
#include "rw/bavector.h"
#include <math.h>
#include "types/type_3DC048.h"
#include "types/type_4C19C0.h"
#include "game/frand.h"
#include "types/type_10F710.h"
#include "rws/maths.h"

#ifdef CODFH_SP // static in single player (defined below)
static RwInt32 sub_181A90(type_3DE350 *arg_0, RwV3d *arg_4, RwReal arg_8, RwV3d *arg_C, RwReal *arg_10,
                          RwReal *arg_14, RwReal *arg_18);
static RwInt32 sub_181D20(type_3DE350 *arg_0, RwV3d *arg_4, RwV3d *arg_8, RwReal *arg_C);
#endif

// Its data definitions (PLAN M5), in the image's address order.
// 0x003DE0DC
extern const RwReal flt_3DE0DC = 16.666666f;
// End of its data definitions.


// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3DE0DC@@3MB @ 0x003DE0DC
// match: ??_7type_3DE0E0@@6B@ @ 0x003DE0E0
// match: __real@3fc66666 @ 0x003DE334
// match: ??_C@_0BC@PFKJHMGH@GimpVehicleEntity?$AA@ @ 0x003DE338
// match: ??_7type_3DE350@@6B@ @ 0x003DE350
// match: ??_C@_02GMLFBBN@wb?$AA@ @ 0x003DE5B0
// match: __ehhandler$?sub_17E680@@YAPAUtype_3D3548@@PAVGimpVehicleTrigger@@@Z>1>8 @ 0x0041E564
// match: __ehhandler$?sub_17E680@@YAPAUtype_3D3548@@PAVGimpVehicleTrigger@@@Z>1 @ 0x0041E584
// match: __ehhandler$??1type_3DE0E0@@UAE@XZ>1>8 @ 0x0041E5A0
// match: __ehhandler$??1type_3DE0E0@@UAE@XZ>1 @ 0x0041E5B8
// match: __ehhandler$?sub_180CF0@@YAPAUtype_3D3548@@PAVGimpVehicleTrigger@@@Z>1>8 @ 0x0041E5D4
// match: __ehhandler$?sub_180CF0@@YAPAUtype_3D3548@@PAVGimpVehicleTrigger@@@Z>1 @ 0x0041E5DC
// match: __ehhandler$??0type_3DE350@@QAE@PAVGimpVehicleTrigger@@@Z>1>8 @ 0x0041E5F8
// match: __ehhandler$??0type_3DE350@@QAE@PAVGimpVehicleTrigger@@@Z>1 @ 0x0041E610
// match: __ehhandler$??1type_3DE350@@UAE@XZ>1>8 @ 0x0041E62C
// match: __ehhandler$??1type_3DE350@@UAE@XZ>1 @ 0x0041E64C

// match: ?sub_17E680@@YAPAUtype_3D3548@@PAVGimpVehicleTrigger@@@Z @ 0x0017E680
// match: __ehhandler$?sub_17E680@@YAPAUtype_3D3548@@PAVGimpVehicleTrigger@@@Z-0x35 @ 0x00302220
// match: __ehhandler$?sub_17E680@@YAPAUtype_3D3548@@PAVGimpVehicleTrigger@@@Z @ 0x00302255
// sp-match: ?sub_17E680@@YAPAUtype_3D3548@@PAVGimpVehicleTrigger@@@Z @ 0x00119A70

// Builds the gimp vehicle for the trigger arg_0, or warns that there is no
// entity memory for it.
type_3D3548 *sub_17E680(GimpVehicleTrigger *arg_0)
{
    type_3DE0E0 *var_10;

    var_10 = (type_3DE0E0 *)sub_D56D0(0x990, arg_0->unk_24_18, arg_0->vf_008());
    if (var_10 != 0) {
        var_10 = new (var_10) type_3DE0E0(arg_0);
        if (var_10->unk_28 & 0x400000) { // not an address: entity flag
            sub_D5A60(var_10, 0);
            var_10 = 0;
        }
    }
#ifndef CODFH_SP
    // Single player compiles the debug print out (SP 0x119A70).
    else
        sub_19A750("WARNING: A spawn could not be created due to lack of entity memory. Trigger "
                   "location(%6.2f,%6.2f,%6.2f)",
                   arg_0->unk_90, arg_0->unk_94, arg_0->unk_98);
#endif
    return var_10;
}

// match: ?vf_0E0@type_3DE0E0@@UAEPAEXZ @ 0x0017E7E0
// sp-match: ?vf_0E0@type_3DE0E0@@UAEPAEXZ @ 0x00117C80
RwUInt8 *type_3DE0E0::vf_0E0()
{
    return (RwUInt8 *)unk_96C;
}

// match: ?vf_094@type_3DE0E0@@UAEXI@Z @ 0x0017E800
// sp-match: ?vf_094@type_3DE0E0@@UAEXI@Z @ 0x00117C90
void type_3DE0E0::vf_094(RwUInt32 arg_0)
{
    unk_968 = arg_0;
}

// match: ?vf_09C@type_3DE0E0@@UAEHXZ @ 0x0017E820
// sp-match: ?vf_09C@type_3DE0E0@@UAEHXZ @ 0x00117CA0
RwInt32 type_3DE0E0::vf_09C()
{
    return unk_964;
}

// match: ?vf_0A0@type_3DE0E0@@UAEXI@Z @ 0x0017E840
// sp-match: ?vf_0A0@type_3DE0E0@@UAEXI@Z @ 0x00117CB0
void type_3DE0E0::vf_0A0(RwUInt32 arg_0)
{
    unk_964 = arg_0;
}

// match: ?vf_234@type_3DE0E0@@UAEHH@Z @ 0x0017E860
// sp-match: ?vf_234@type_3DE0E0@@UAEHH@Z @ 0x00117CC0
RwInt32 type_3DE0E0::vf_234(RwInt32 arg_0)
{
    unk_658.unk_300 = arg_0;
    return 1;
}

// match: ?vf_174@type_3DE0E0@@UAEHXZ @ 0x0017E880
// sp-match: ?vf_174@type_3DE0E0@@UAEHXZ @ 0x00117CE0
RwInt32 type_3DE0E0::vf_174()
{
    return unk_980;
}

// match: ?vf_180@type_3DE0E0@@UAEXH@Z @ 0x0017E8A0
// sp-match: ?vf_180@type_3DE0E0@@UAEXH@Z @ 0x00117CF0
void type_3DE0E0::vf_180(RwInt32 arg_0)
{
    unk_980 += arg_0;
    if (unk_980 > unk_984)
        unk_980 = unk_984;
}

// match: ?vf_178@type_3DE0E0@@UAEXH@Z @ 0x0017E8F0
// sp-match: ?vf_178@type_3DE0E0@@UAEXH@Z @ 0x00117D20
void type_3DE0E0::vf_178(RwInt32 arg_0)
{
    unk_980 = arg_0;
}

// match: ?vf_17C@type_3DE0E0@@UAEMXZ @ 0x0017E910
// sp-match: ?vf_17C@type_3DE0E0@@UAEMXZ @ 0x00117D30
RwReal type_3DE0E0::vf_17C()
{
    return (RwReal)unk_980 / unk_984;
}

// match: ?vf_23C@type_3DE0E0@@UAEHXZ @ 0x0017E930
// sp-match: ?vf_23C@type_3DE0E0@@UAEHXZ @ 0x00117D40
RwInt32 type_3DE0E0::vf_23C()
{
    return unk_988;
}

// match: ?vf_240@type_3DE0E0@@UAEMXZ @ 0x0017E950
// sp-match: ?vf_240@type_3DE0E0@@UAEMXZ @ 0x00117D50
RwReal type_3DE0E0::vf_240()
{
    return (RwReal)unk_988 / unk_98C;
}

// match: ?vf_124@type_3DE0E0@@UAEXM@Z @ 0x0017E970
// sp-match: ?vf_124@type_3DE0E0@@UAEXM@Z @ 0x00117D60
void type_3DE0E0::vf_124(RwReal arg_0)
{
    unk_978 = arg_0;
}

// match: ?vf_0F4@type_3DE0E0@@UAEPAUSplinePath@@XZ @ 0x0017E990
// sp-match: ?vf_0F4@type_3DE0E0@@UAEPAUSplinePath@@XZ @ 0x00117D70
SplinePath *type_3DE0E0::vf_0F4()
{
    return unk_97C;
}

// match: ?vf_248@type_3DE0E0@@UAEMXZ @ 0x0017E9B0
// sp-match: ?vf_248@type_3DE0E0@@UAEMXZ @ 0x000FEBD0
RwReal type_3DE0E0::vf_248()
{
    return -360.0f;
}

#ifdef CODFH_SP
// sp-match: ??0type_3DE0E0@@QAE@XZ @ 0x00117D80
// (Defined in the class: the bare constructor, which single player calls out
// of line from the subclass's (SP 0x119A0D); multiplayer expands it.)
#endif

// match: ??_Gtype_3DE0E0@@UAEPAXI@Z @ 0x0017E9D0
// match: ??1type_3DE0E0@@UAE@XZ @ 0x0017EA00
// match: __ehhandler$??1type_3DE0E0@@UAE@XZ-0x24 @ 0x00302260
// match: __ehhandler$??1type_3DE0E0@@UAE@XZ @ 0x00302284
// sp-match: ??1type_3DE0E0@@UAE@XZ @ 0x00117C20
// sp-match: ??_Gtype_3DE0E0@@UAEPAXI@Z @ 0x00117DE0
// (Defined in the class: vf_230, called directly as in any destructor,
// then the members' destructors and the base's.)

// match: ?sub_17EA70@type_3DE0E0@@QAEHPAVGimpVehicleTrigger@@@Z @ 0x0017EA70
// sp-match: ?sub_17EA70@type_3DE0E0@@QAEHPAVGimpVehicleTrigger@@@Z @ 0x00117E00
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Its set-up from its trigger arg_0, as the tank's (type_3DBC78's
// sub_14D2C0): its trigger's object told of it, the base's set-up, its
// type, flags and side by its data's kind, its model (sub_17F2E0) and
// animation, its tracks' bones (700 to 798 and 650 to 698, by the bind
// pose's side) and bone 100, its script object and scripts, its
// performance player, its path and goto point, speeds, health and unk_988.
// Returns 1.
RwInt32 type_3DE0E0::sub_17EA70(GimpVehicleTrigger *arg_0)
{
    RwUInt32 ebp_34;
    RwUInt32 var_30;
    type_3DFEEC *v2C;
    type_3DF8D8 *lcl_28;
    type_3DF8D8 *frm_24;
    type_3DF8D8 *var_20;
    GimpVehicleTrigger *l1C;
    type_3D2E7C *m_18;
    type_7C8D0 *ebp_14;
    RwInt32 lv_10;
    RpHAnimHierarchy *var_C;
    RwMatrix *bp_8;
    type_3D2CD0 *bp_4;

    lv_10 = 0;
    l1C = arg_0;
    var_20 = sub_198800(&l1C->unk_C0);
    if (l1C->unk_D8.unk_00)
    {
        v2C = (type_3DFEEC *)sub_198800(&l1C->unk_D8);
        ((type_D48D0 *)&v2C->unk_24_id)->sub_D48D0(this);
        v2C->unk_10 = 0x22;
    }
    unk_95C = 1;
    sub_CCCD0((type_712B0 *)arg_0);
    unk_960 = l1C->unk_E0;
    unk_28 = 0x1C;
    unk_130 = 0;
    switch (((type_14D2C0_10 *)var_20->unk_10)->get_unk_8C())
    {
    case 0:
    case 2:
        unk_2C = 0x1000002; // not an address: kind flags
        break;
    case 1:
    case 3:
    case 4:
        unk_2C = 0x1000001; // not an address: kind flags
        break;
    }
    unk_30 = -1;
    sub_17F2E0(var_20);
    sub_16E080(get_unk_264(), ((type_3DF8D8_3 *)((type_3DFE7C *)var_20)->sub_1954D0())->get_unk_54_direct());
    sub_16D8C0(get_unk_264(), "destroyed", 0);
    var_30 = sub_78830(0);
    unk_280 = var_30;
    ebp_14 = (type_7C8D0 *)sub_78AC0(unk_280);
    unk_284 = ebp_14;
    var_C = sub_16D970(get_unk_264());
    ebp_14->sub_79470(var_C);
    ebp_14->unk_1C = (RwInt32)this;
    memset(unk_96C, 0, 6);
    for (lv_10 = 0; lv_10 < 2; lv_10++)
        unk_970[lv_10] = 1;
    set_xyz(&unk_10C, -1.0f, -1.0f, -1.0f);
    set_xyz(&unk_134, -1.0f, -1.0f, -1.0f);
    zero_v3d(&unk_118);
    set_xyz(&unk_124, 1000.0f, 1000.0f, 1000.0f);
    if ((unk_2C & 7) == 2)
        sub_D5B80(this, 2);
    else
        sub_D5B80(this, 3);
    unk_62C = 0;
    unk_630 = 0;
    unk_634 = 0;
    unk_624 = 1;
    unk_628 = 0;
    unk_61C = 0;
    unk_620 = 0;
    unk_618 = 0;
    unk_614 = 0;
    bp_8 = RpHAnimHierarchyGetMatrixArray(get_unk_284()->get_unk_18());
    for (lv_10 = 700, unk_3B0 = 0; lv_10 < 799; lv_10++)
    {
        unk_3B4[unk_3B0] = RpHAnimIDGetIndex(get_unk_284()->get_unk_18(), lv_10);
        if (unk_3B4[unk_3B0] != -1)
        {
            if (bp_8[unk_3B4[unk_3B0]].pos.x < 0.0f)
                unk_47C[unk_3B4[unk_3B0]] = 1;
            else
                unk_47C[unk_3B4[unk_3B0]] = 2;
            unk_3B0++;
        }
    }
    for (lv_10 = 650, unk_544 = 0; lv_10 < 699; lv_10++)
    {
        unk_548[unk_544] = RpHAnimIDGetIndex(get_unk_284()->get_unk_18(), lv_10);
        if (unk_548[unk_544] != -1)
        {
            if (bp_8[unk_548[unk_544]].pos.x < 0.0f)
                unk_5AC[unk_548[unk_544]] = 1;
            else
                unk_5AC[unk_548[unk_544]] = 2;
            unk_544++;
        }
    }
    unk_610 = RpHAnimIDGetIndex(unk_284->get_unk_18(), 100);
    lcl_28 = sub_198800(&l1C->unk_C8);
    ebp_34 = sub_71870();
    unk_964 = ebp_34;
    m_18 = vf_098();
    m_18->sub_70DF0(this, 2);
    m_18->sub_70E10(lcl_28->get_unk_18(), 1);
    bp_4 = (type_3D2CD0 *)sub_71770(1);
    unk_968_h = bp_4->get_unk_04_h();
    bp_4->sub_6CDA0(this, 5);
    frm_24 = sub_198800(&l1C->unk_D0);
    if (frm_24)
        m_18->sub_70F40(frm_24->get_unk_18(), 1);
    unk_974 = 0;
    unk_97C = 0;
    unk_978 = 0;
    unk_638 = 0;
    unk_63C = 0;
    unk_644.z = 0;
    unk_644.y = 0;
    unk_644.x = 0;
    unk_650_i = l1C->unk_EC;
    unk_654_i = l1C->unk_F0;
    unk_984 = l1C->unk_E4;
    unk_980 = unk_984;
    unk_98C = l1C->unk_E8;
    unk_988 = unk_98C;
    return 1;
}

// match: ?sub_17F2E0@type_3DE0E0@@QAEXPAUtype_3DF8D8@@@Z @ 0x0017F2E0
// sp-match: ?sub_17F2E0@type_3DE0E0@@QAEXPAUtype_3DF8D8@@@Z @ 0x00116CD0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Its model from its data arg_0 (as the tank's vf_2F8): for its own
// trigger (kind 0x23), the base's set-up of the model object arg_0 names
// (a warning without one of kind 3), its unk_290, its atomic's bounding
// radius grown by 55%, and its guns.
void type_3DE0E0::sub_17F2E0(type_3DF8D8 *arg_0)
{
    type_712B0 *var_10;
    RpAtomic *var_C;
    type_3DF8D8 *bp_8;
    RwInt32 bp_4;

    if (get_unk_34C())
    {
        var_10 = (type_712B0 *)unk_344.unk_08;
        if (var_10->vf_008() != 0x23)
            return;
        bp_8 = ((type_3DFE7C *)arg_0)->sub_1954D0();
        if (!bp_8 || bp_8->vf_008() != 3)
        {
            sub_D3FB0("GimpVehicleEntity", var_10, &arg_0->unk_04);
            return;
        }
        vf_224(bp_8, 0, &bp_4);
        unk_290 = ((type_3DF8D8_3 *)bp_8)->get_unk_44();
        var_C = Clump_FindFirstAtomic(get_unk_264());
        if (var_C)
            var_C->boundingSphere.radius *= 1.55f;
        unk_658.sub_15B2A0(arg_0, 0);
    }
}

// match: ?vf_230@type_3DE0E0@@UAEXXZ @ 0x0017F3E0
// sp-match: ?vf_230@type_3DE0E0@@UAEXXZ @ 0x00116D80
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Shuts it down once: its performance player and script object released,
// its animation and its trigger's object let go, and unk_630 freed.
void type_3DE0E0::vf_230()
{
    type_3DFEEC *var_C;
    GimpVehicleTrigger *bp_8;
    type_3D2E7C *bp_4;

    if (unk_95C)
    {
        if (vf_090())
        {
            sub_717B0((type_3D2C88 *)vf_090());
            unk_968 = 0;
        }
        bp_4 = vf_098();
        if (bp_4)
        {
            sub_330E0(bp_4->sub_71340(), 0);
            sub_34E40(bp_4->sub_71340());
            sub_35330(bp_4->sub_71340());
            sub_40AE0(bp_4->sub_71340());
            sub_71970((type_3D2C88 *)bp_4);
            unk_964 = 0;
        }
        unk_95C = 0;
        vf_228();
        sub_78870(unk_280);
        unk_280 = 0;
        bp_8 = (GimpVehicleTrigger *)get_unk_34C();
        if (bp_8->unk_D8.unk_00)
        {
            var_C = (type_3DFEEC *)sub_198800(&bp_8->unk_D8);
            ((type_D48D0 *)&var_C->unk_24_id)->sub_D48D0(0);
        }
        if (unk_630)
        {
            RwFree(unk_630);
            unk_630 = 0;
        }
    }
}

// match: ?vf_058@type_3DE0E0@@UAEHPAUtype_3DF8D8_04@@@Z @ 0x0017F550
// sp-match: ?vf_058@type_3DE0E0@@UAEHPAUtype_3DF8D8_04@@@Z @ 0x00116E80
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Whether arg_0 is one of the keys 0 to 2 of its data's model object (the
// tank's vf_058 is folded into it).
RwInt32 type_3DE0E0::vf_058(type_3DF8D8_04 *arg_0)
{
    type_3DF8D8 *var_10;
    GimpVehicleTrigger *var_C;
    type_1908A0 *bp_8;
    type_3DF8D8_04 *bp_4;

    var_C = (GimpVehicleTrigger *)get_unk_34C();
    var_10 = sub_198800(&var_C->unk_C0);
    bp_8 = (type_1908A0 *)((type_3DFE7C *)var_10)->sub_1954D0();
    bp_4 = ((type_3DF9C4 *)bp_8)->sub_1908A0(0);
    if (arg_0->unk_00 == bp_4->unk_00 && arg_0->unk_04 == bp_4->unk_04)
        return 1;
    bp_4 = ((type_3DF9C4 *)bp_8)->sub_1908A0(1);
    if (arg_0->unk_00 == bp_4->unk_00 && arg_0->unk_04 == bp_4->unk_04)
        return 1;
    bp_4 = ((type_3DF9C4 *)bp_8)->sub_1908A0(2);
    if (arg_0->unk_00 == bp_4->unk_00 && arg_0->unk_04 == bp_4->unk_04)
        return 1;
    return 0;
}

// match: ?sub_17F620@@YAXPAUtype_7C8D0@@PAUtype_80300@@H_N@Z @ 0x0017F620
// sp-match: ?sub_17F620@@YAXPAUtype_7C8D0@@PAUtype_80300@@H_N@Z @ 0x00118200
// Its animation's procedural track (vf_038 starts it; arg_8 is the gimp
// vehicle), as the tank's (sub_150350): at its start it builds its pose key
// once (every node's rotation relative to its frame, bone 100 translated),
// then reuses it. Each step its track wheels (the bones 700 to 798) turn by
// their side's angle and the bones 650 to 698 tilt by 45 degrees and turn.
void sub_17F620(type_7C8D0 *arg_0, type_80300 *arg_4, RwInt32 arg_8, bool arg_C)
{
    type_3DE0E0 *var_4;
    type_7CBD0 *var_8;
    RwFrame *var_10;
    RpHAnimHierarchy *var_18;
    RwMatrix *var_1C;
    RtQuat *var_20;
    type_7CBD0_hdr *var_24;
    type_7CBD0_t *var_28;
    RwMatrix var_70;
    RwInt32 var_74;
    RwMatrix var_C0;
    RwInt32 var_C4;
    RtQuat *var_C8;
    RpHAnimHierarchy *var_D4;
    RtQuat *var_D8;
    RtQuat *var_DC;
    RwV3d var_EC;
    RwV3d var_F8;
    RwReal var_FC;

    var_4 = (type_3DE0E0 *)arg_8;
    var_8 = (type_7CBD0 *)arg_4->unk_144;
    if (arg_C && !var_4->unk_630)
    {
        var_10 = var_4->get_unk_340();
        var_18 = var_4->get_unk_284()->unk_18;
        var_1C = RpHAnimHierarchyGetMatrixArray(var_18);
        var_4->unk_634 = var_18->numNodes * sizeof(RtQuat) + sizeof(type_7CBD0_hdr);
        var_4->unk_630 = (type_7CBD0_hdr *)RwMalloc(var_4->unk_634, 0x34251); // not an address: a memory hint
        memset(var_4->unk_630, 0, var_4->unk_634);
        var_4->unk_630->unk_00 = var_18->numNodes;
        var_4->unk_630->unk_01 = var_18->numNodes;
        var_4->unk_630->unk_02 = 1;
        var_4->unk_630->unk_08 = (RwUInt64)-1;
        var_4->unk_630->unk_10 = (RwUInt64)(1 << var_4->unk_610);
        sub_807C0((RtAnimInterpolator *)arg_4, var_4->unk_630);
        var_20 = var_8->unk_10;
        var_24 = var_4->unk_630;
        var_28 = (type_7CBD0_t *)&var_8->unk_10[var_24->unk_00];
        RwMatrixInvert(&var_70, RwFrameGetLTM(var_10));
        for (var_74 = 0; var_74 < var_18->numNodes; var_74++)
        {
            var_C0 = var_70;
            var_C4 = RpHAnimIDGetIndex(var_18, var_18->pNodeInfo[var_74].nodeID);
            RwMatrixTransform(&var_C0, &var_1C[var_C4], rwCOMBINEPRECONCAT);
            RtQuatConvertFromMatrix(&var_20[var_74], &var_C0);
        }
        for (var_74 = 0; var_74 < var_4->unk_630->unk_02; var_74++)
        {
            var_28[var_74].unk_00.z = 0.0f;
            var_28[var_74].unk_00.y = 0.0f;
            var_28[var_74].unk_00.x = 0.0f;
        }
        var_C8 = (RtQuat *)(var_4->unk_630 + 1);
        memcpy(var_C8, var_20, var_18->numNodes * sizeof(RtQuat));
        var_8->unk_04 = var_4->unk_630;
        var_8->unk_08 = sub_EC270(var_4->get_unk_264());
    }
    else if (arg_C && var_4->unk_630)
    {
        var_D4 = var_4->get_unk_284()->unk_18;
        var_D8 = (RtQuat *)(var_4->unk_630 + 1);
        var_DC = var_8->unk_10;
        memcpy(var_DC, var_D8, var_D4->numNodes * sizeof(RtQuat));
        sub_807C0((RtAnimInterpolator *)arg_4, var_4->unk_630);
        var_8->unk_04 = var_4->unk_630;
        var_8->unk_08 = sub_EC270(var_4->get_unk_264());
    }
    else
    {
        var_EC.x = 1.0f;
        var_EC.y = 0.0f;
        var_EC.z = 0.0f;
        var_4->unk_61C += var_4->unk_614 * 57.295784f;
        var_4->unk_620 += var_4->unk_618 * 57.295784f;
        for (var_74 = 0; var_74 < var_4->unk_3B0; var_74++)
        {
            if (var_4->unk_47C[var_4->unk_3B4[var_74]] == 1)
                var_4->sub_17FC00(var_8, var_4->unk_3B4[var_74], 0, &var_EC, var_4->unk_61C, 1);
            else
                var_4->sub_17FC00(var_8, var_4->unk_3B4[var_74], 0, &var_EC, var_4->unk_620, 1);
        }
        var_F8.x = 0.0f;
        var_F8.y = 1.0f;
        var_F8.z = 0.0f;
        var_FC = 45.0f;
        for (var_74 = 0; var_74 < var_4->unk_544; var_74++)
            var_4->sub_17FC00(var_8, var_4->unk_548[var_74], 0, &var_F8, var_FC, 1);
        for (var_74 = 0; var_74 < var_4->unk_544; var_74++)
        {
            if (var_4->unk_5AC[var_4->unk_548[var_74]] == 1)
                var_4->sub_17FC00(var_8, var_4->unk_548[var_74], 0, &var_EC, var_4->unk_61C, 0);
            else
                var_4->sub_17FC00(var_8, var_4->unk_548[var_74], 0, &var_EC, var_4->unk_620, 0);
        }
    }
}

// match: ?sub_17FC00@type_3D3548@@QAEXPAUtype_7CBD0@@HPAURwV3d@@1MH@Z @ 0x0017FC00
// sp-match: ?sub_17FC00@type_3D3548@@QAEXPAUtype_7CBD0@@HPAURwV3d@@1MH@Z @ 0x00116F00
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Moves node arg_4 of the pose key arg_0 by arg_8 (when given) and turns it
// about the axis arg_C by arg_10 degrees (RtQuatRotate): its rotation
// replaced (arg_14 set) or turned further (RtQuatMultiplyMacro) and
// normalised (sub_13FB00).
void type_3D3548::sub_17FC00(type_7CBD0 *arg_0, RwInt32 arg_4, RwV3d *arg_8, RwV3d *arg_C, RwReal arg_10,
                             RwInt32 arg_14)
{
    RtQuat var_34;
    RwInt32 frm_24;
    type_7CBD0_t *var_20;
    RtQuat *l1C;
    RwInt32 m_18;
    RtQuat ebp_14;
    type_7CBD0_hdr *bp_4;

    var_20 = 0;
    l1C = 0;
    bp_4 = arg_0->unk_04;
    if (arg_8)
        var_20 = (type_7CBD0_t *)&arg_0->unk_10[bp_4->unk_00];
    if (arg_C)
        l1C = arg_0->unk_10;
    m_18 = arg_4;
    frm_24 = m_18;
    if (arg_8)
        RwV3dAddMacro(&var_20[frm_24].unk_00, &var_20[frm_24].unk_00, arg_8);
    if (arg_C && (arg_10 != 0.0f || arg_14))
    {
        RtQuatRotate(&ebp_14, arg_C, arg_10, rwCOMBINEREPLACE);
        if (arg_14)
            l1C[m_18] = ebp_14;
        else
        {
            RtQuatMultiplyMacro(&var_34, &l1C[m_18], &ebp_14);
            l1C[m_18] = var_34;
            sub_13FB00(&l1C[m_18], &l1C[m_18]);
        }
    }
}

// match: ?vf_038@type_3DE0E0@@UAEXM@Z @ 0x0017FEB0
// sp-match: ?vf_038@type_3DE0E0@@UAEXM@Z @ 0x00118600
// Its animation's procedural track (sub_17F620) started once (as the
// tank's).
void type_3DE0E0::vf_038(RwReal arg_0)
{
    if (!unk_62C)
    {
        get_unk_284()->sub_794C0(0);
        unk_62C = get_unk_284()->sub_79930(sub_17F620, 1.0f, 1.0f);
#ifdef CODFH_SP // SP expands type_78AC0::sub_6DF40 here (SP 0x11863A: % 4 ring)
        get_unk_284()->clear_last_unk_08_30();
#else
        ((type_78AC0 *)get_unk_284())->sub_6DF40();
#endif
        unused_slot();
    }
}

// match: ?vf_03C@type_3DE0E0@@UAEXM@Z @ 0x0017FF30
// sp-match: ?vf_03C@type_3DE0E0@@UAEXM@Z @ 0x00118670
// The step arg_0: the base's, its guns; then by its move state (unk_638):
// 1 drives to its goto point (sub_1808D0), sending "IHaveArrived" once
// there, else stands it on the ground below the point facing ahead; 2
// follows its spline path (unless it is dead), stepping along it once
// within 500 of its point and turning back, wrapping or ending at its ends
// by the path's mode ("IHaveArrived" and
// "SplinePath_ArrivedATDestination"), driving to the next point and
// standing on the ground there facing it.
void type_3DE0E0::vf_03C(RwReal arg_0)
{
    type_3D3548::vf_03C(arg_0);
    unk_658.sub_15B510(arg_0);
    if (!unk_638)
        return;
    if (unk_638 == 1)
    {
        if (sub_1808D0(&unk_644, unk_650, unk_654, 100.0f, arg_0))
        {
            type_3D2E7C *var_8;
            RwReal var_C;

            var_8 = vf_098();
            if (var_8)
            {
                var_C = deltaTime;
                sub_6B5F0("IHaveArrived", (type_67620 *)var_8, 0, 0, (RwInt32 *)(&var_C), 1, 1, 0);
            }
        }
        else
        {
            RwV3d *var_10;
            RpIntersection var_2C;
            RwInt32 var_30;
            type_4E5D30 *var_34;
            type_91F40 var_68;

            var_10 = &unk_644;
            var_2C.type = rpINTERSECTLINE;
            var_2C.t.line.start = *var_10;
            var_2C.t.line.end = *var_10;
            var_2C.t.line.start.y += 100.0f;
            var_2C.t.line.end.y -= 100.0f;
            for (var_30 = 0; var_30 < 4; var_30++)
            {
                var_34 = &dword_4E5D30[var_30];
                if (var_34->get_unk_00() && sub_91F40(var_34->get_unk_28(), &var_2C.t.line, &var_68, 1, 0x40000, 1)) // not an address: line-test flags
                {
                    RwMatrix *var_70;
                    RwV3d *var_74;
                    RwMatrix var_C0;

                    var_70 = RwFrameGetMatrix(get_unk_340());
                    var_74 = (RwV3d *)vf_0C4();
                    var_C0.up = var_68.unk_14;
                    var_C0.pos = *var_74;
                    var_C0.at = var_70->at;
                    RwV3dCrossProductMacro(&var_C0.right, &var_C0.up, &var_C0.at);
                    RwV3dNormalize(&var_C0.right, &var_C0.right);
                    RwV3dCrossProductMacro(&var_C0.up, &var_C0.at, &var_C0.right);
                    RwV3dNormalize(&var_C0.up, &var_C0.up);
                    RwMatrixOptimize(&var_C0, 0);
                    RwMatrixOrthoNormalize(&var_C0, &var_C0);
                    RwFrameTransform(get_unk_340(), &var_C0, rwCOMBINEREPLACE);
                    break;
                }
            }
        }
    }
    else if (unk_638 == 2 && unk_97C && !unk_28_9)
    {
        RwInt32 var_C8;
        RwInt32 var_CC;
        RwReal var_D0;
        RwV3d var_DC;
        RwV3d var_E8;
        RwReal var_EC;

        var_C8 = 0;
        var_CC = 0;
        var_D0 = unk_974;
        unk_97C->sub_BA990(unk_974, &var_DC, 0);
        RwV3dSubMacro(&var_E8, (RwV3d *)vf_0C4(), &var_DC);
        var_EC = RwV3dLength((RwV3d *)&var_E8);
        if (var_EC < 500.0f)
        {
            unk_974 += unk_978;
            if (unk_974 > 1.0f)
                unk_974 = 1.0f;
            else if (unk_974 < 0.0f)
                unk_974 = 0;
        }
        if (unk_974 == 1.0f || unk_974 == 0.0f)
        {
            if ((unk_97C->unk_1C & 3) == 2)
                unk_978 = -unk_978;
            else if ((unk_97C->unk_1C & 3) == 1)
                unk_974 = 0;
            else
                var_CC = 1;
            var_C8 = 1;
        }
        var_D0 = unk_974 + unk_978;
        if (var_D0 > 1.0f)
            var_D0 = 1.0f;
        else if (var_D0 < 0.0f)
            var_D0 = 0;
        unk_97C->sub_BA990(var_D0, &var_DC, 0);
        if (sub_1808D0(&var_DC, unk_650, unk_654, 100.0f, arg_0))
        {
            // (Nothing: the image tests the result with an empty branch.)
        }
        else
        {
            RwV3d *var_F0;
            RpIntersection var_10C;
            RwInt32 var_110;
            type_4E5D30 *var_114;
            type_91F40 var_148;

            var_F0 = &var_DC;
            var_10C.type = rpINTERSECTLINE;
            var_10C.t.line.start = *var_F0;
            var_10C.t.line.end = *var_F0;
            var_10C.t.line.start.y += 100.0f;
            var_10C.t.line.end.y -= 100.0f;
            for (var_110 = 0; var_110 < 4; var_110++)
            {
                var_114 = &dword_4E5D30[var_110];
                if (var_114->get_unk_00() && sub_91F40(var_114->get_unk_28(), &var_10C.t.line, &var_148, 1, 0x40000, 1)) // not an address: line-test flags
                {
                    RwV3d *var_14C;
                    RwMatrix var_190;

                    var_14C = (RwV3d *)vf_0C4();
                    var_190.up = var_148.unk_14;
                    var_190.pos = *var_14C;
                    RwV3dSubMacro(&var_190.at, var_F0, &var_190.pos);
                    RwV3dNormalize(&var_190.at, &var_190.at);
                    RwV3dCrossProductMacro(&var_190.right, &var_190.up, &var_190.at);
                    RwV3dNormalize(&var_190.right, &var_190.right);
                    RwV3dCrossProductMacro(&var_190.up, &var_190.at, &var_190.right);
                    RwV3dNormalize(&var_190.up, &var_190.up);
                    RwMatrixOptimize(&var_190, 0);
                    RwMatrixOrthoNormalize(&var_190, &var_190);
                    RwFrameTransform(get_unk_340(), &var_190, rwCOMBINEREPLACE);
                    break;
                }
            }
        }
        if (var_C8)
        {
            RwReal var_198;

            var_198 = deltaTime;
            sub_6B5F0("IHaveArrived", (type_67620 *)(vf_098()), 0, 0, (RwInt32 *)(&var_198), 1, 1, 0);
            sub_6B5F0("SplinePath_ArrivedATDestination", (type_67620 *)(vf_098()), 0, 0, 0, 0, 1, 0);
        }
        if (var_CC)
        {
            unk_97C = 0;
            unk_974 = 0;
        }
    }
}

// match: ?sub_1808D0@type_3DE0E0@@QAEHPAURwV3d@@MMMM@Z @ 0x001808D0
// sp-match: ?sub_1808D0@type_3DE0E0@@QAEHPAURwV3d@@MMMM@Z @ 0x001170A0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Drives toward the point arg_0 over the step arg_10: whether it is there
// (within arg_C across the ground, or within twice that and behind it);
// else its speed arg_4 and a turn toward the point's heading, at most arg_8
// and none within 0.05 degrees a step.
RwInt32 type_3DE0E0::sub_1808D0(RwV3d *arg_0, RwReal arg_4, RwReal arg_8, RwReal arg_C, RwReal arg_10)
{
    RwReal local_48;
    RwV3d *local_44;
    RwV3d local_40;
    RwReal l34;
    RwReal var30;
    bool y29;
    RwReal lcl_28;
    RwReal frm_24;
    RwReal var_20;
    RwMatrix *l1C;
    RwReal m_18;
    RwReal ebp_14;
    RwV3d lv_10;
    RwReal bp_4;

    local_44 = (RwV3d *)vf_0C4();
    l1C = RwFrameGetMatrix(get_unk_340());
    RwV3dSubMacro(&lv_10, arg_0, local_44);
    lv_10.y = 0;
    var30 = RwV3dLength((RwV3d *)&lv_10);
    y29 = false;
    if (var30 < arg_C)
        y29 = true;
    else
    {
        RwV3dNormalize(&lv_10, &lv_10);
        local_48 = RwV3dDotProductMacro(&l1C->at, &lv_10);
        if (local_48 < 0.0f && arg_C * 2.0f > var30)
            y29 = true;
    }
    if (y29)
        return 1;
    if (fabs(RwV3dDotProductMacro(&lv_10, &lv_10)) > 0.0001f)
        RwV3dNormalize(&local_40, &lv_10);
    else
    {
        local_40.x = 0;
        local_40.y = 0;
        local_40.z = 0;
    }
    lcl_28 = atan2f_(local_40.z, local_40.x) * 57.295776f;
    lcl_28 = sub_13F9E0(lcl_28);
    m_18 = RwV3dDotProductMacro(&local_40, &l1C->right);
    ebp_14 = atan2f_(l1C->right.x, l1C->at.x) * 57.295776f;
    ebp_14 = sub_13F9E0(ebp_14);
    var_20 = fabs(bp_4 = RWS::DegAngDiff(lcl_28, ebp_14));
    var_20 = fabs(l34 = bp_4 / arg_10);
    if (var_20 > arg_8)
    {
        if (m_18 < 0.0f)
            frm_24 = -arg_8;
        else
            frm_24 = arg_8;
    }
    else if (var_20 <= 0.05f)
        frm_24 = 0;
    else
        frm_24 = l34;
    unk_C0.z = arg_4;
    unk_E8 = frm_24;
    sub_19B650(unk_E4);
    return 0;
}

// match: ?vf_0F8@type_3DE0E0@@UAEXM@Z @ 0x00180B90
// sp-match: ?vf_0F8@type_3DE0E0@@UAEXM@Z @ 0x00117280
// Puts it at arg_0 along its spline path (as the gimp's).
void type_3DE0E0::vf_0F8(RwReal arg_0)
{
    RwV3d var_C;

    unk_974 = arg_0;
    if (unk_97C)
    {
        unk_97C->sub_BA990(unk_974, &var_C, 0);
        vf_0C0(&var_C);
    }
}

// match: ?vf_04C@type_3DE0E0@@UAEXM@Z @ 0x00180BF0
// sp-match: ?vf_04C@type_3DE0E0@@UAEXM@Z @ 0x001172C0
void type_3DE0E0::vf_04C(RwReal arg_0)
{
    type_3D3548::vf_04C(arg_0);
}

// match: ?vf_054@type_3DE0E0@@UAEXH@Z @ 0x00180C10
// sp-match: ?vf_054@type_3DE0E0@@UAEXH@Z @ 0x001172D0
// The base's, between two debug prints.
void type_3DE0E0::vf_054(RwInt32 arg_0)
{
    sub_19A750(1);
    type_3D3548::vf_054(arg_0);
    sub_19A750(0);
}

// match: ?vf_0EC@type_3DE0E0@@UAEXHH@Z @ 0x00180C40
// sp-match: ?vf_0EC@type_3DE0E0@@UAEXHH@Z @ 0x00117300
void type_3DE0E0::vf_0EC(RwInt32 arg_0, RwInt32 arg_4)
{
    unk_96C[arg_0] = (RwInt16)arg_4;
}

// match: ?vf_098@type_3DE0E0@@UAEPAUtype_3D2E7C@@XZ @ 0x00180C60
// sp-match: ?vf_098@type_3DE0E0@@UAEPAUtype_3D2E7C@@XZ @ 0x00117320
type_3D2E7C *type_3DE0E0::vf_098()
{
    return (type_3D2E7C *)sub_67620(unk_964);
}

// match: ?vf_090@type_3DE0E0@@UAEPAUtype_6D380@@XZ @ 0x00180C80
// sp-match: ?vf_090@type_3DE0E0@@UAEPAUtype_6D380@@XZ @ 0x00117330
struct type_6D380 *type_3DE0E0::vf_090()
{
    return (type_6D380 *)sub_67620(unk_968);
}

// match: ?sub_180CA0@type_3DE0E0@@QAEXPAUtype_3D3548@@@Z @ 0x00180CA0
// sp-match: ?sub_180CA0@type_3DE0E0@@QAEXPAUtype_3D3548@@@Z @ 0x00117340
void type_3DE0E0::sub_180CA0(type_3D3548 *arg_0)
{
    if (arg_0 != unk_640.sub_D4910())
    {
        if (arg_0)
            unk_640.sub_D48D0(arg_0);
        else
            unk_640.sub_D48D0(0);
    }
}

// match: ?sub_180CF0@@YAPAUtype_3D3548@@PAVGimpVehicleTrigger@@@Z @ 0x00180CF0
// match: __ehhandler$?sub_180CF0@@YAPAUtype_3D3548@@PAVGimpVehicleTrigger@@@Z-0x11 @ 0x00302290
// match: __ehhandler$?sub_180CF0@@YAPAUtype_3D3548@@PAVGimpVehicleTrigger@@@Z @ 0x003022A1
// sp-match: ?sub_180CF0@@YAPAUtype_3D3548@@PAVGimpVehicleTrigger@@@Z @ 0x00119B10
// Builds the gimp vehicle of type 1 for the trigger arg_0, or warns that
// there is no entity memory for it.
type_3D3548 *sub_180CF0(GimpVehicleTrigger *arg_0)
{
    type_3DE350 *var_10;

    var_10 = (type_3DE350 *)sub_D56D0(0x9B0, arg_0->unk_24_18, arg_0->vf_008());
    if (var_10 != 0) {
        var_10 = new (var_10) type_3DE350(arg_0);
        if (var_10->unk_28 & 0x400000) { // not an address: entity flag
            sub_D5A60(var_10, 0);
            var_10 = 0;
        }
    }
#ifndef CODFH_SP
    // Single player compiles the debug print out (SP 0x119B10).
    else
        sub_19A750("WARNING: A spawn could not be created due to lack of entity memory. Trigger "
                   "location(%6.2f,%6.2f,%6.2f)",
                   arg_0->unk_90, arg_0->unk_94, arg_0->unk_98);
#endif
    return var_10;
}

#ifdef CODFH_SP
// sp-match: ??0type_3DE0E0@@QAE@PAVGimpVehicleTrigger@@@Z @ 0x00119980
// (Defined in the class: the constructor for a trigger, which single player
// calls out of line from sub_17E680 (SP 0x119AD6); multiplayer expands it.)
#endif

// match: ??0type_3DE350@@QAE@PAVGimpVehicleTrigger@@@Z @ 0x00180E00
// match: __ehhandler$??0type_3DE350@@QAE@PAVGimpVehicleTrigger@@@Z-0x1E @ 0x003022B0
// match: __ehhandler$??0type_3DE350@@QAE@PAVGimpVehicleTrigger@@@Z @ 0x003022CE
// sp-match: ??0type_3DE350@@QAE@PAVGimpVehicleTrigger@@@Z @ 0x001199F0
// (Defined in the class.)

// match: ??_Gtype_3DE350@@UAEPAXI@Z @ 0x00180EA0
// match: ??1type_3DE350@@UAE@XZ @ 0x00180ED0
// match: __ehhandler$??1type_3DE350@@UAE@XZ-0x2C @ 0x003022E0
// match: __ehhandler$??1type_3DE350@@UAE@XZ @ 0x0030230C
// sp-match: ??1type_3DE350@@UAE@XZ @ 0x00119A60
// sp-match: ??_Gtype_3DE350@@UAEPAXI@Z @ 0x00119A40
// (Defined in the class: its vf_230, called directly as in any destructor,
// then the base's destructor inline.)

// match: ?sub_180F60@type_3DE350@@QAEHPAVGimpVehicleTrigger@@@Z @ 0x00180F60
// sp-match: ?sub_180F60@type_3DE350@@QAEHPAVGimpVehicleTrigger@@@Z @ 0x00118CF0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Its set-up from its trigger arg_0: the base's (sub_17EA70), its side by
// its data's kind, its track's two bones (2 and 3), and its first three
// guns' tags ("RIFA" to "RIFC", 0 where its model has none). Returns 1.
RwInt32 type_3DE350::sub_180F60(GimpVehicleTrigger *arg_0)
{
    type_3DF8D8 *var_C;
    GimpVehicleTrigger *bp_8;
    RpHAnimHierarchy *bp_4;

    bp_8 = arg_0;
    var_C = sub_198800(&bp_8->unk_C0);
    sub_17EA70(arg_0);
    switch (((type_14D2C0_10 *)var_C->unk_10)->get_unk_8C())
    {
    case 0:
    case 2:
        unk_2C = 0x2000002; // not an address: kind flags
        break;
    case 1:
    case 3:
    case 4:
        unk_2C = 0x2000001; // not an address: kind flags
        break;
    }
    unk_998 = 0;
    unk_99C = 0;
    unk_990 = 0;
    unk_994 = 0;
    unk_9A0 = 0;
    unk_9A4 = 0;
    bp_4 = get_unk_284()->unk_18;
    unk_9A8 = RpHAnimIDGetIndex(bp_4, 2);
    unk_9AC = RpHAnimIDGetIndex(bp_4, 3);
    if (sub_EC1F0(get_unk_264(), 0x41464952)) // not an address: the tag "RIFA"
        unk_658.unk_00[0].unk_38 = 0x41464952; // not an address: the tag "RIFA"
    else
        unk_658.unk_00[0].unk_38 = 0;
    if (sub_EC1F0(get_unk_264(), 0x42464952)) // not an address: the tag "RIFB"
        unk_658.unk_00[1].unk_38 = 0x42464952; // not an address: the tag "RIFB"
    else
        unk_658.unk_00[1].unk_38 = 0;
    if (sub_EC1F0(get_unk_264(), 0x43464952)) // not an address: the tag "RIFC"
        unk_658.unk_00[2].unk_38 = 0x43464952; // not an address: the tag "RIFC"
    else
        unk_658.unk_00[2].unk_38 = 0;
    return 1;
}

// match: ?sub_181140@@YAXPAUtype_7C8D0@@PAUtype_80300@@H_N@Z @ 0x00181140
// sp-match: ?sub_181140@@YAXPAUtype_7C8D0@@PAUtype_80300@@H_N@Z @ 0x00118E10
// Its animation's procedural track (vf_038 starts it; arg_8 is the
// vehicle), as its base's (sub_17F620) but with room for a translation for
// every node in its pose key, which it builds again at every start; each
// step the base's, then bone unk_9A8 turned
// about its up axis by unk_998 and bone unk_9AC about its right axis by
// unk_99C.
void sub_181140(type_7C8D0 *arg_0, type_80300 *arg_4, RwInt32 arg_8, bool arg_C)
{
    type_3DE350 *var_4;
    type_7CBD0 *var_8;
    RwFrame *var_10;
    RpHAnimHierarchy *var_18;
    RwMatrix *var_1C;
    RtQuat *var_20;
    type_7CBD0_hdr *var_24;
    type_7CBD0_t *var_28;
    RwMatrix var_70;
    RwInt32 var_74;
    RwMatrix var_C0;
    RwInt32 var_C4;
    RtQuat *var_C8;
    RpHAnimHierarchy *var_D4;
    RtQuat *var_D8;
    RtQuat *var_DC;
    RwV3d var_EC;
    RwV3d var_F8;

    var_4 = (type_3DE350 *)arg_8;
    var_8 = (type_7CBD0 *)arg_4->unk_144;
    if (arg_C)
    {
        var_10 = var_4->get_unk_340();
        var_18 = var_4->get_unk_284()->unk_18;
        var_1C = RpHAnimHierarchyGetMatrixArray(var_18);
        var_4->unk_634 = var_18->numNodes * (sizeof(RtQuat) + sizeof(RwV3d)) + sizeof(type_7CBD0_hdr);
        var_4->unk_630 = (type_7CBD0_hdr *)RwMalloc(var_4->unk_634, 0x34251); // not an address: a memory hint
        memset(var_4->unk_630, 0, var_4->unk_634);
        var_4->unk_630->unk_00 = var_18->numNodes;
        var_4->unk_630->unk_01 = var_18->numNodes;
        var_4->unk_630->unk_02 = 1;
        var_4->unk_630->unk_08 = (RwUInt64)-1;
        var_4->unk_630->unk_10 = 1 << var_4->unk_610;
        sub_807C0((RtAnimInterpolator *)arg_4, var_4->unk_630);
        var_20 = var_8->unk_10;
        var_24 = var_4->unk_630;
        var_28 = (type_7CBD0_t *)&var_8->unk_10[var_24->unk_00];
        RwMatrixInvert(&var_70, RwFrameGetLTM(var_10));
        for (var_74 = 0; var_74 < var_18->numNodes; var_74++)
        {
            var_C0 = var_70;
            var_C4 = RpHAnimIDGetIndex(var_18, var_18->pNodeInfo[var_74].nodeID);
            RwMatrixTransform(&var_C0, &var_1C[var_C4], rwCOMBINEPRECONCAT);
            RtQuatConvertFromMatrix(&var_20[var_74], &var_C0);
        }
        for (var_74 = 0; var_74 < var_4->unk_630->unk_02; var_74++)
        {
            var_28[var_74].unk_00.z = 0.0f;
            var_28[var_74].unk_00.y = 0.0f;
            var_28[var_74].unk_00.x = 0.0f;
        }
        var_C8 = (RtQuat *)(var_4->unk_630 + 1);
        memcpy(var_C8, var_20, var_18->numNodes * sizeof(RtQuat));
        var_8->unk_04 = var_4->unk_630;
        var_8->unk_08 = sub_EC270(var_4->get_unk_264());
    }
    else if (arg_C && var_4->unk_630)
    {
        var_D4 = var_4->get_unk_284()->unk_18;
        var_D8 = (RtQuat *)(var_4->unk_630 + 1);
        var_DC = var_8->unk_10;
        memcpy(var_DC, var_D8, var_D4->numNodes * sizeof(RtQuat));
        sub_807C0((RtAnimInterpolator *)arg_4, var_4->unk_630);
        var_8->unk_04 = var_4->unk_630;
        var_8->unk_08 = sub_EC270(var_4->get_unk_264());
    }
    else
    {
        var_EC.x = 0.0f;
        var_EC.y = 1.0f;
        var_EC.z = 0.0f;
        var_F8.x = 1.0f;
        var_F8.y = 0.0f;
        var_F8.z = 0.0f;
        sub_17F620(arg_0, arg_4, arg_8, arg_C);
        if (var_4->unk_9A8 != -1 && var_4->unk_9AC != -1)
        {
            var_4->sub_17FC00(var_8, var_4->unk_9A8, 0, &var_EC, var_4->unk_998, 1);
            var_4->sub_17FC00(var_8, var_4->unk_9AC, 0, &var_F8, var_4->unk_99C, 1);
        }
    }
}

// match: ?vf_038@type_3DE350@@UAEXM@Z @ 0x001815A0
// sp-match: ?vf_038@type_3DE350@@UAEXM@Z @ 0x001190C0
// Its animation's procedural track (sub_181140) started once.
void type_3DE350::vf_038(RwReal arg_0)
{
    if (!unk_62C)
    {
        get_unk_284()->sub_794C0(0);
        unk_62C = get_unk_284()->sub_79930(sub_181140, 1.0f, 1.0f);
#ifdef CODFH_SP // SP expands type_78AC0::sub_6DF40 here (SP 0x1190FA: % 4 ring)
        get_unk_284()->clear_last_unk_08_30();
#else
        ((type_78AC0 *)get_unk_284())->sub_6DF40();
#endif
        unused_slot();
    }
}

// match: ?vf_03C@type_3DE350@@UAEXM@Z @ 0x00181620
// sp-match: ?vf_03C@type_3DE350@@UAEXM@Z @ 0x00119130
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The step arg_0: its base's; its guns fire continuously while it is told
// to (vf_254 with its guns' unk_300); in fire state 1 with a target it
// aims its turret and barrel at it (sub_181A90), firing its main gun (0),
// or its second (1) while roughly on, and its third (2) at the target when
// that gun bears on it (sub_181D20); then its barrel and turret turn at
// their speeds (unk_9A4 and unk_9A0), the barrel within 45 degrees and the
// turret within its arc (vf_248 to vf_250) when it has one (vf_244).
void type_3DE350::vf_03C(RwReal arg_0)
{
#ifndef CODFH_SP
    RwReal v48;
    RwReal var_44;
#endif
    RwReal ebp_40;
    RwReal local_3C;
    RwReal v38;
    type_3D3548 *v34;
    RwInt32 v30;
    RwReal v2C;
    RwV3d w28;
    type_3DE350 *loc1C;
    RwInt32 bp_18;
    RwReal var14;
    RwV3d r10;
    RwReal l4;

    type_3DE0E0::vf_03C(arg_0);
    if (unk_658.unk_300 >= 0)
        vf_254(unk_658.unk_300, 0);
    if (unk_63C == 1 && unk_640.sub_D4910())
    {
        v34 = unk_640.sub_D4910();
        v38 = 1000000.0f;
        v30 = 1;
        bp_18 = 1;
        loc1C = this;
        v34->vf_110(&w28, this, 0);
        if (sub_181A90(loc1C, &w28, v38, &r10, &l4, &v2C, &var14))
        {
            if (l4 < 0.6f)
            {
                v30 = 0;
                bp_18 = 0;
            }
            else if (l4 < 0.985)
                v30 = 0;
            if (r10.y > 0.0f)
                loc1C->vf_258(1.0f - l4, 1.0f);
            else if (r10.y < 0.0f)
                loc1C->vf_258(-1.0f + l4, 1.0f);
            local_3C = v2C - var14;
            if (local_3C < 0.0872 && local_3C > -0.0872)
                loc1C->vf_25C(-local_3C, 1.0f);
            else if (local_3C > 0.0f)
            {
                loc1C->vf_25C(-1.0f, 1.0f);
                v30 = 0;
                bp_18 = 0;
            }
            else
            {
                loc1C->vf_25C(1.0f, 1.0f);
                v30 = 0;
                bp_18 = 0;
            }
            if (v30)
                loc1C->vf_254(0, 0);
            else if (bp_18)
                loc1C->vf_254(1, 0);
        }
        v34->vf_110(&w28, this, 0);
        if (sub_181D20(loc1C, &w28, &r10, &l4) && l4 > 0.3301f)
            loc1C->vf_254(2, &w28);
    }
    if (unk_9A4 != 0.0f)
    {
#ifdef CODFH_SP
        // shape: the step in frames in a local (SP 0x119370 multiplies by 1/60, then by
        // 40), and the barrel's bounds local to this block (frame 0x30).
        RwReal frames = arg_0 / 60.0f;
        unk_99C += frames * 40.0f * unk_9A4;
        RwReal var_44;
        RwReal v48;
#else
        unk_99C += arg_0 / 60.0f * 40.0f * unk_9A4;
#endif
        var_44 = 45.0f;
        v48 = -45.0f;
        unk_99C = sub_22C20(unk_99C, v48, var_44);
    }
    if (unk_9A0 != 0.0f)
    {
#ifdef CODFH_SP
        RwReal frames = arg_0 / 60.0f;
        unk_998 += frames * 40.0f * unk_9A0;
#else
        unk_998 += arg_0 / 60.0f * 40.0f * unk_9A0;
#endif
        if (unk_998 < 0.0f)
            unk_998 = 360.0f + unk_998;
        if (unk_998 > 360.0f)
            unk_998 -= 360.0f;
        if (vf_244())
        {
            ebp_40 = unk_998 > 180.0f ? unk_998 - 360.0f : unk_998;
            if (vf_248() > ebp_40)
                unk_998 = vf_248() + 360.0f;
            if (vf_250() < ebp_40)
                unk_998 = vf_250();
        }
    }
}

// match: ?sub_181A90@@YAHPAUtype_3DE350@@PAURwV3d@@M1PAM22@Z @ 0x00181A90
// sp-match: ?sub_181A90@@YAHPAUtype_3DE350@@PAURwV3d@@M1PAM22@Z @ 0x00117380
// How its turret and barrel bear on the point arg_4 (arg_8 unused): from
// its main gun's tag, the turn toward it across the ground (the cross
// product arg_C), how nearly it faces it (arg_10: the dot product, eased up
// within 400 and from 0.99 scaled to 0 to 1), the point's pitch (arg_14)
// and the barrel's (arg_18). 0 without the tag or looking straight up or
// down.
#ifdef CODFH_SP
// shape: internal linkage in single player, which passes arg_0 in ecx (SP 0x117380).
static
#endif
RwInt32 sub_181A90(type_3DE350 *arg_0, RwV3d *arg_4, RwReal arg_8, RwV3d *arg_C, RwReal *arg_10, RwReal *arg_14,
                   RwReal *arg_18)
{
    RpClump *var_4;
    RwMatrix var_50;
    RwV3d *var_54;
    RwV3d var_60;
    RwReal var_64;
    RwV3d var_70;
    RwV3d var_7C;
    RwV3d var_88;

    if (!arg_0->unk_658.unk_00[0].unk_38)
        return 0;
    var_4 = arg_0->unk_25C.unk_08;
    if (!sub_EC2D0(var_4, (RwInt32)&var_50, arg_0->unk_658.unk_00[0].unk_38, 0, 1))
        return 0;
    var_54 = &var_50.pos;
    RwV3dSubMacro(&var_60, arg_4, var_54);
    var_64 = RwV3dLength((RwV3d *)&var_60);
    *arg_14 = var_60.y / var_64;
    if (var_60.y == 1.0f || var_60.y == -1.0f)
        return 0;
    var_60.y = 0;
    RwV3dNormalize(&var_70, &var_60);
    var_7C = var_50.at;
    *arg_18 = var_7C.y;
    if (*arg_18 == 1.0f || *arg_18 == -1.0f)
        return 0;
    var_7C.y = 0;
    RwV3dNormalize(&var_88, &var_7C);
    RwV3dCrossProductMacro(arg_C, &var_88, &var_70);
    *arg_10 = RwV3dDotProductMacro(&var_88, &var_70);
    if (var_64 < 400.0f)
    {
        if (var_64 > 200.0f)
        {
#ifdef CODFH_SP
            // shape: the closeness in a local, by a two-hundredth (SP 0x11753C multiplies by
            // 0.005, then by the factor).
            RwReal closeness = (400.0f - var_64) * 0.005f;
            *arg_10 *= closeness * 0.034074172f + 1.0f;
#else
            *arg_10 *= (400.0f - var_64) / 200.0f * 0.034074172f + 1.0f;
#endif
            if (*arg_10 < 0.0f)
                *arg_10 *= -1.0f;
            if (*arg_10 > 1.0f)
                *arg_10 = 1.0f;
        }
        else
            *arg_10 = 1.0f;
    }
    if (*arg_10 < 0.99f)
        *arg_10 = 0;
    else
        *arg_10 = (*arg_10 - 0.99f) * 100.0f;
    return 1;
}

// match: ?sub_181D20@@YAHPAUtype_3DE350@@PAURwV3d@@1PAM@Z @ 0x00181D20
// sp-match: ?sub_181D20@@YAHPAUtype_3DE350@@PAURwV3d@@1PAM@Z @ 0x001175C0
// Likewise for its third gun's tag: the turn toward the point arg_4 (arg_8)
// and how nearly the gun faces it (arg_C, from 0.8 scaled by 5).
#ifdef CODFH_SP
// shape: internal linkage in single player, which passes arg_0 in ecx (SP 0x1175C0).
static
#endif
RwInt32 sub_181D20(type_3DE350 *arg_0, RwV3d *arg_4, RwV3d *arg_8, RwReal *arg_C)
{
    RpClump *var_4;
    RwMatrix var_50;
    RwV3d *var_54;
    RwV3d var_60;
    RwV3d var_6C;
    RwV3d var_78;
    RwV3d var_84;

    if (!arg_0->unk_658.unk_00[2].unk_38)
        return 0;
    var_4 = arg_0->unk_25C.unk_08;
    if (!sub_EC2D0(var_4, (RwInt32)&var_50, arg_0->unk_658.unk_00[2].unk_38, 0, 1))
        return 0;
    var_54 = &var_50.pos;
    RwV3dSubMacro(&var_60, arg_4, var_54);
    if (var_60.y == 1.0f || var_60.y == -1.0f)
        return 0;
    var_60.y = 0;
    RwV3dNormalize(&var_6C, &var_60);
    var_78 = var_50.at;
    var_78.y = 0;
    RwV3dNormalize(&var_84, &var_78);
    RwV3dCrossProductMacro(arg_8, &var_84, &var_6C);
    *arg_C = RwV3dDotProductMacro(&var_84, &var_6C);
    if (*arg_C < 0.8f)
        *arg_C = 0;
    else
        *arg_C = (*arg_C - 0.8f) * 5.0f;
    return 1;
}

// match: ?vf_258@type_3DE350@@UAEXMM@Z @ 0x00181EC0
// sp-match: ?vf_258@type_3DE350@@UAEXMM@Z @ 0x00117730
// Sets unk_9A0 while its set-up has run (unk_624; arg_4 unused).
void type_3DE350::vf_258(RwReal arg_0, RwReal arg_4)
{
    if (!unk_624)
        return;
    unk_9A0 = arg_0;
}

// match: ?vf_25C@type_3DE350@@UAEXMM@Z @ 0x00181EF0
// sp-match: ?vf_25C@type_3DE350@@UAEXMM@Z @ 0x00117750
// Likewise unk_9A4.
void type_3DE350::vf_25C(RwReal arg_0, RwReal arg_4)
{
    if (!unk_624)
        return;
    unk_9A4 = arg_0;
}

// match: ?vf_054@type_3DE350@@UAEXH@Z @ 0x00181F20
// sp-match: ?vf_054@type_3DE350@@UAEXH@Z @ 0x00117770
void type_3DE350::vf_054(RwInt32 arg_0)
{
    type_3DE0E0::vf_054(arg_0);
}

// match: ?vf_058@type_3DE350@@UAEHPAUtype_3DF8D8_04@@@Z @ 0x00181F40
// sp-match: ?vf_058@type_3DE350@@UAEHPAUtype_3DF8D8_04@@@Z @ 0x00117780
RwInt32 type_3DE350::vf_058(type_3DF8D8_04 *arg_0)
{
    return type_3DE0E0::vf_058(arg_0);
}

// match: ?vf_254@type_3DE350@@UAEHHPAURwV3d@@@Z @ 0x00181F60
// sp-match: ?vf_254@type_3DE350@@UAEHHPAURwV3d@@@Z @ 0x001194D0
// Fires its gun arg_0 (as the tank's vf_2A8): once it has rounds (vf_238),
// a round spent (a full magazine starting again); gun 0 is its main gun
// (sub_182990); guns 1 and 2, once set up, fire from their tags at the point
// arg_4 (or ahead), spread by the difficulty, with weapon 30's damage; gun 3
// likewise, straight ahead. 0 when it cannot.
RwInt32 type_3DE350::vf_254(RwInt32 arg_0, RwV3d *arg_4)
{
    RwV3d var_A8;
    type_4C19C0 *var_AC;

    if (!vf_238(arg_0))
        return 0;
    if (unk_658.unk_00[arg_0].unk_20 == unk_658.unk_00[arg_0].unk_34)
        unk_658.unk_00[arg_0].unk_18 = 0.0f;
    unk_658.unk_00[arg_0].unk_20 = unk_658.unk_00[arg_0].unk_20 - 1;
    switch (arg_0)
    {
    case 0:
        if (!sub_182990(arg_0))
            return 0;
        break;
    case 1:
    case 2:
    {
        RwMatrix var_50;
        RwV3d var_5C;
        RwReal var_80;
        RwInt32 var_B8;

        if (!unk_624)
            return 0;
        if (!sub_EC2D0(get_unk_264(), (RwInt32)&var_50, unk_658.unk_00[arg_0].unk_38, 0, 0))
            return 0;
        if (arg_4)
        {
            RwV3dSubMacro(&var_5C, arg_4, &var_50.pos);
            RwV3dNormalize(&var_5C, &var_5C);
            var_50.at = var_5C;
            RwV3dCrossProductMacro(&var_50.up, &var_50.right, &var_50.at);
            RwV3dCrossProductMacro(&var_50.right, &var_50.at, &var_50.up);
        }
        var_80 = frand_range(-vf_164() * difficulty_4F2890(),
                             vf_164() * difficulty_4F2890());
        RwMatrixRotate(&var_50, &var_50.up, var_80, rwCOMBINEPRECONCAT);
        var_80 = frand_range(-vf_168() * difficulty_4F2890(),
                             vf_168() * difficulty_4F2890());
        RwMatrixRotate(&var_50, &var_50.right, var_80, rwCOMBINEPRECONCAT);
        RwV3dScale(&var_A8, &var_50.at, unk_658.unk_00[arg_0].unk_0C);
        var_AC = sub_119B70(30);
        if (unk_658.unk_00[arg_0].get_unk_08())
        {
            unk_658.unk_00[arg_0].unk_3C.unk_00 = 3;
            unk_658.unk_00[arg_0].unk_3C.unk_38 = (RwInt32)unk_658.unk_00[arg_0].get_unk_08();
            if ((unk_2C & 7) == 2)
                var_B8 = 0x1002;
            else
                var_B8 = 0x1001;
        }
        else
        {
            unk_658.unk_00[arg_0].unk_3C.unk_00 = 0;
            if ((unk_2C & 7) == 2)
                var_B8 = 0x202;
            else
                var_B8 = 0x201;
        }
        unk_658.unk_00[arg_0].unk_3C.unk_04_r = (RwReal)(RwUInt32)var_AC->unk_C4;
        sub_15F2C0(var_B8, (RwInt32)this, &var_50, &var_A8, unk_628, (type_439A48 *)&unk_658.unk_00[arg_0].unk_3C, 0);
        sub_F2FF0(unk_658.unk_00[arg_0].unk_10, &var_50, 0, 0, 0, 0);
        sub_F2FF0(unk_658.unk_00[arg_0].unk_14, &var_50, 0, 0, 0, 0);
        break;
    }
    case 3:
    {
        RwMatrix var_110;
        RwReal var_130;
        RwInt32 var_158;

        if (!sub_EC2D0(get_unk_264(), (RwInt32)&var_110, unk_658.unk_00[arg_0].unk_38, 0, 0))
            return 0;
        var_130 = frand_range(-vf_164() * difficulty_4F2890(),
                              vf_164() * difficulty_4F2890());
        RwMatrixRotate(&var_110, &var_110.up, var_130, rwCOMBINEPRECONCAT);
        var_130 = frand_range(-vf_168() * difficulty_4F2890(),
                              vf_168() * difficulty_4F2890());
        RwMatrixRotate(&var_110, &var_110.right, var_130, rwCOMBINEPRECONCAT);
        RwV3dScale(&var_A8, &var_110.at, unk_658.unk_00[arg_0].unk_0C);
        var_AC = sub_119B70(30);
        if (unk_658.unk_00[arg_0].get_unk_08())
        {
            unk_658.unk_00[arg_0].unk_3C.unk_00 = 3;
            unk_658.unk_00[arg_0].unk_3C.unk_38 = (RwInt32)unk_658.unk_00[arg_0].get_unk_08();
            if ((unk_2C & 7) == 2)
                var_158 = 0x1002;
            else
                var_158 = 0x1001;
        }
        else
        {
            unk_658.unk_00[arg_0].unk_3C.unk_00 = 0;
            if ((unk_2C & 7) == 2)
                var_158 = 0x202;
            else
                var_158 = 0x201;
        }
        unk_658.unk_00[arg_0].unk_3C.unk_04_r = (RwReal)(RwUInt32)var_AC->unk_C4;
        sub_15F2C0(var_158, (RwInt32)this, &var_110, &var_A8, unk_628, (type_439A48 *)&unk_658.unk_00[arg_0].unk_3C, 0);
        sub_F2FF0(unk_658.unk_00[arg_0].unk_10, &var_110, 0, 0, 0, 0);
        sub_F2FF0(unk_658.unk_00[arg_0].unk_14, &var_110, 0, 0, 0, 0);
        break;
    }
    }
    return 1;
}

// match: ?vf_238@type_3DE350@@UAEHH@Z @ 0x00182960
// sp-match: ?vf_238@type_3DE350@@UAEHH@Z @ 0x00117790
RwInt32 type_3DE350::vf_238(RwInt32 arg_0)
{
    if (unk_658.unk_00[arg_0].unk_20 <= 0)
        return 0;
    return 1;
}

// match: ?sub_182990@type_3DE350@@QAEHH@Z @ 0x00182990
// sp-match: ?sub_182990@type_3DE350@@QAEHH@Z @ 0x001177B0
// Its main gun's shot (gun arg_0, from vf_254; as the tank's vf_300): from
// its tag, spread by a quarter of the difficulty's spread, with the shell
// settings of weapon 29.
RwInt32 type_3DE350::sub_182990(RwInt32 arg_0)
{
    RwMatrix var_50;
    RwReal var_70;
    RwV3d var_98;
    type_4C19C0 *var_9C;
    RwInt32 var_B0;

    if (!sub_EC2D0(get_unk_264(), (RwInt32)&var_50, unk_658.unk_00[arg_0].unk_38, 0, 0))
        return 0;
    var_70 = frand_range(-vf_164() * difficulty_4F2890(),
                         vf_164() * difficulty_4F2890());
    RwMatrixRotate(&var_50, &var_50.up, var_70 * 0.25f, rwCOMBINEPRECONCAT);
    var_70 = frand_range(-vf_168() * difficulty_4F2890(),
                         vf_168() * difficulty_4F2890());
    RwMatrixRotate(&var_50, &var_50.right, var_70 * 0.25f, rwCOMBINEPRECONCAT);
    RwV3dScale(&var_98, &var_50.at, unk_658.unk_00[arg_0].unk_0C);
    var_9C = sub_119B70(29);
    unk_658.unk_00[arg_0].unk_3C.unk_00 = 3;
    unk_658.unk_00[arg_0].unk_3C.unk_04_r = (RwReal)(RwUInt32)var_9C->unk_C4;
    unk_658.unk_00[arg_0].unk_3C.unk_38 = (RwInt32)unk_658.unk_00[arg_0].get_unk_08();
    unk_658.unk_00[arg_0].unk_3C.unk_3C = 1;
    unk_658.unk_00[arg_0].unk_3C.unk_40 = var_9C->unk_C0;
    unk_658.unk_00[arg_0].unk_3C.unk_44 = var_9C->unk_194;
    unk_658.unk_00[arg_0].unk_3C.unk_48 = var_9C->unk_198;
    unk_658.unk_00[arg_0].unk_3C.unk_4C_r = var_9C->unk_D0;
    unk_658.unk_00[arg_0].unk_8C = var_9C->unk_4B4;
    unk_658.unk_00[arg_0].unk_90_i = var_9C->unk_4B8;
    unk_658.unk_00[arg_0].unk_94 = var_9C->unk_4BC;
    unk_658.unk_00[arg_0].unk_98 = var_9C->unk_4C0;
    unk_658.unk_00[arg_0].unk_9C = var_9C->unk_4C4;
    unk_658.unk_00[arg_0].unk_A0 = var_9C->unk_4C8;
    unk_658.unk_00[arg_0].unk_A4 = var_9C->unk_4CC;
    unk_658.unk_00[arg_0].unk_AC = var_9C->unk_98;
    unk_658.unk_00[arg_0].unk_A8 = var_9C->unk_9C;
    unk_658.unk_00[arg_0].unk_B4 = var_9C->unk_A0;
    unk_658.unk_00[arg_0].unk_B0 = var_9C->unk_A4;
    unk_658.unk_00[arg_0].unk_B8 = var_9C->unk_A8;
    unk_658.unk_00[arg_0].unk_BC = var_9C->unk_AC;
    if ((unk_2C & 7) == 2)
        var_B0 = 0x1002;
    else
        var_B0 = 0x1001;
    sub_15F2C0(var_B0, (RwInt32)this, &var_50, &var_98, unk_628, (type_439A48 *)&unk_658.unk_00[arg_0].unk_3C, 0);
    sub_F2FF0(unk_658.unk_00[arg_0].unk_10, &var_50, 0, 0, 0, 0);
    sub_F2FF0(unk_658.unk_00[arg_0].unk_14, &var_50, 0, 0, 0, 0);
    return 1;
}

// match: ?vf_064@type_3DE0E0@@UAEHPAUtype_75600@@@Z @ 0x00182F60
// sp-match: ?vf_064@type_3DE0E0@@UAEHPAUtype_75600@@@Z @ 0x00117B10
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// A hit arg_0 (as the tank's): a player's weapon of type 0x17 does a fifth of
// its damage as a hit of kind 4; hits of kinds 3, 4 and 6 wear its armour
// (unk_988) first, then its health, and send "HitByBullet". Returns 0.
RwInt32 type_3DE0E0::vf_064(type_75600 *arg_0)
{
    RwReal var_8;
    RwInt32 l4;

    if (arg_0->unk_04)
    {
        l4 = ((type_758F0_08 *)arg_0->unk_04_p)->vf_058();
        if (arg_0->unk_0C && arg_0->unk_0C->vf_00C() && arg_0->unk_0C->vf_00C()->get_hand()
            && arg_0->unk_0C->vf_00C()->get_hand()->get_unk_458() == 0x17)
        {
            arg_0->unk_28 /= 5.0f;
            l4 = 4;
        }
        if (l4 == 4 || l4 == 3 || l4 == 6)
        {
            var_8 = arg_0->unk_28;
            if (unk_988 > 0)
            {
                unk_988 = unk_988 - (RwInt32)var_8;
                if (unk_988 < 0)
                {
                    unk_980 = unk_980 + unk_988;
                    unk_988 = 0;
                }
            }
            else
            {
                unk_980 = unk_980 - (RwInt32)var_8;
                if (unk_980 < 0)
                    unk_980 = 0;
            }
            sub_6B5F0("HitByBullet", (type_67620 *)(vf_098()), 0, 0, 0, 0, 1, 0);
            sub_D2AD0(arg_0->unk_0C, arg_0->unk_04);
        }
    }
    return 0;
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??2type_3DE0E0@@SAPAXIPAX@Z (folded into 0x6CCF0)
void *type_3DE0E0::operator new(RwUInt32 arg_0, void *arg_4)
{
    return arg_4;
}

// ??2type_3DE350@@SAPAXIPAX@Z (folded into 0x6CCF0)
void *type_3DE350::operator new(RwUInt32 arg_0, void *arg_4)
{
    return arg_4;
}

// ?vf_230@type_3DE350@@UAEXXZ (folded into 0x1E41C0)
void type_3DE350::vf_230()
{
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??3type_3DE0E0@@SAXPAX@Z (folded into 0x19A750)
#ifndef CODFH_SP
// Single player keeps the deleting destructor's call (SP 0x117DF0), so the empty body is
// not in this file there.
void type_3DE0E0::operator delete(void * arg_0)
{
}
#endif

// ??3type_3DE350@@SAXPAX@Z (folded into 0x19A750)
#ifndef CODFH_SP
// Single player keeps the deleting destructor's call (SP 0x119A50), so the empty body is
// not in this file there.
void type_3DE350::operator delete(void * arg_0)
{
}
#endif

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??3type_3DE0E0@@SAXPAX0@Z (folded into 0x19A750)
void type_3DE0E0::operator delete(void * arg_0, void * arg_4)
{
}

// ??3type_3DE350@@SAXPAX0@Z (folded into 0x19A750)
void type_3DE350::operator delete(void * arg_0, void * arg_4)
{
}

// Not in the image: a stand-in for a function the original object held last, which
// the link dropped (/OPT:REF) but whose literal stayed: "wb" sits after this
// object's vtable (0x3DE5B0), before unit_183130's data, though its only user is
// RenderWare's stream code (bastream.c, a library member linked later; a same-named
// literal is the first object's). Unreferenced.
void *dropped_3DE5B0(const RwChar *arg_0)
{
    return RwOsGetFileInterface()->rwfopen(arg_0, "wb");
}
