// Split from unit_09AD40.cpp at 0x09C1E0, where the image starts another object
// (type_3D5658, its factory function first, with the .data at 0x42910C): its .rdata begins at 0x3D5654 with its own copy of the
// unreferenced 16.666666 every game object starts its constants with (PLAN M7).

#include "rw/ostypes.h"
#include "game/functions.h"
#include "types/type_3D3548.h"
#include "types/type_3D32F8.h"
#include "types/type_3D51C0.h"
#include "types/type_3D5400.h"
#include "types/type_9BB60.h"
#include "types/type_3D5658.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "rws/ceventhandler.h"
#include "types/alfamessman.h"
#include "types/scriptvm.h"
#include "types/AddTaskTrigger.h"
#include "types/type_72810.h"
#include "types/AnimatedBGTrigger.h"
#include "types/vec4.h"
#include "rw/bavector.h"
#include "rw/rprandom.h"
#include "types/type_D48D0.h"
#include "types/alfaobject.h"
#include "types/type_3D2E7C.h"
#include "types/type_3DF8D8.h"
#include "types/type_44350.h"
#include "types/CustomTrigger.h"
#include "types/DogTrigger.h"
#include "types/type_10F710.h"
#include "game/vecutil.h"
#include "types/MeshSwapDestructableObjectTrigger.h"
#include "types/soundbank.h"
#include "rw/rphanim.h"
#include "game/clumpdata.h"
#include "types/animbank.h"
#include <string.h>
#include <math.h>

// Its data definitions (PLAN M5), in the image's address order.
// 0x003D5654
extern const RwReal flt_3D5654 = 16.666666f;
// 0x0042910C
RwReal dword_42910C = -2.0f;
// 0x00429110
RwReal flt_429110 = 30.0f;
// 0x00429114
RwReal flt_429114 = 0.2f;
// 0x00429118
RwReal flt_429118 = 1.5f;
// 0x0042911C
RwReal flt_42911C = 0.28f;
// 0x00429120
RwReal flt_429120 = 1.5f;

// match: ?flt_3D5654@@3MB @ 0x003D5654
// match: ?dword_42910C@@3MA @ 0x0042910C
// match: ?flt_429110@@3MA @ 0x00429110
// match: ?flt_429114@@3MA @ 0x00429114
// match: ?flt_429118@@3MA @ 0x00429118
// match: ?flt_42911C@@3MA @ 0x0042911C
// match: ?flt_429120@@3MA @ 0x00429120


// match: __ehhandler$?sub_9C1E0@@YAPAUtype_3D5658@@PAUtype_712B0@@@Z>1>8 @ 0x0041B810
// match: __ehhandler$?sub_9C1E0@@YAPAUtype_3D5658@@PAUtype_712B0@@@Z>1 @ 0x0041B818
// match: __ehhandler$??0type_3D5658@@QAE@PAUtype_712B0@@@Z>1>8 @ 0x0041B834
// match: __ehhandler$??0type_3D5658@@QAE@PAUtype_712B0@@@Z>1 @ 0x0041B84C
// match: __ehhandler$??1type_3D5658@@UAE@XZ>1>8 @ 0x0041B868
// match: __ehhandler$??1type_3D5658@@UAE@XZ>1 @ 0x0041B880
// match: ?vf_094@type_3D5658@@UAEXI@Z @ 0x0009C370
// match: ?vf_0A4@type_3D5658@@UAEXH@Z @ 0x0009C390
// match: ?vf_0A8@type_3D5658@@UAEHXZ @ 0x0009C3B0
// match: ?vf_08C@type_3D5658@@UAEPAEHH@Z @ 0x0009C3D0
// match: ?vf_09C@type_3D5658@@UAEHXZ @ 0x0009C3F0
// match: ?vf_0A0@type_3D5658@@UAEXI@Z @ 0x0009C410
// match: ?vf_0AC@type_3D5658@@UAEHXZ @ 0x0009C430
// match: ?vf_0B0@type_3D5658@@UAEXHH@Z @ 0x0009C450
// match: ?vf_0B4@type_3D5658@@UAEXXZ @ 0x0009C480
// match: ?vf_0B8@type_3D5658@@UAEXH@Z @ 0x0009C4A0
// match: ?vf_0E0@type_3D5658@@UAEPAEXZ @ 0x0009C4C0
// match: ?vf_0F0@type_3D5658@@UAEPACXZ @ 0x0009C4E0
// match: ?vf_174@type_3D5658@@UAEHXZ @ 0x0009C500
// match: ?vf_178@type_3D5658@@UAEXH@Z @ 0x0009C520
// match: ?vf_180@type_3D5658@@UAEXH@Z @ 0x0009C540
// match: ?vf_1B0@type_3D5658@@UAEXH@Z @ 0x0009C570
// match: ?vf_23C@type_3D5658@@UAEHXZ @ 0x0009C590
// match: ?vf_118@type_3D5658@@UAEPAUtype_3D3548@@XZ @ 0x0009C5D0
// match: ?vf_11C@type_3D5658@@UAEXPAUtype_3D3548@@@Z @ 0x0009C5F0
// match: ?vf_120@type_3D5658@@UAEPAUAIData@@XZ @ 0x0009C610
// match: ??_Gtype_3D5658@@UAEPAXI@Z @ 0x0009C630
// match: ??_7type_3D5658@@6B@ @ 0x003D5658
// match: ??_C@_09BBGEBPMF@DogEntity?$AA@ @ 0x003D5898
// match: ??_C@_07GPBECKHN@HitWall?$AA@ @ 0x003D58A4
// match: ??_C@_09IKNPGHMO@HitGround?$AA@ @ 0x003D58AC
// sp-match: ?vf_094@type_3D5658@@UAEXI@Z @ 0x0007BF00
// sp-match: ?vf_0A4@type_3D5658@@UAEXH@Z @ 0x0007BF10
// sp-match: ?vf_0A8@type_3D5658@@UAEHXZ @ 0x0007BF20
// sp-match: ?vf_08C@type_3D5658@@UAEPAEHH@Z @ 0x0007BF30
// sp-match: ?vf_09C@type_3D5658@@UAEHXZ @ 0x0007BF40
// sp-match: ?vf_0A0@type_3D5658@@UAEXI@Z @ 0x0007BF50
// sp-match: ?vf_0AC@type_3D5658@@UAEHXZ @ 0x0007BF60
// sp-match: ?vf_0B4@type_3D5658@@UAEXXZ @ 0x0007BF90
// sp-match: ?vf_0B8@type_3D5658@@UAEXH@Z @ 0x0007BFA0
// sp-match: ?vf_0E0@type_3D5658@@UAEPAEXZ @ 0x0007BFB0
// sp-match: ?vf_0F0@type_3D5658@@UAEPACXZ @ 0x0007BFC0
// sp-match: ?vf_174@type_3D5658@@UAEHXZ @ 0x0007BFD0
// sp-match: ?vf_178@type_3D5658@@UAEXH@Z @ 0x0007BFE0
// sp-match: ?vf_180@type_3D5658@@UAEXH@Z @ 0x0007BFF0
// sp-match: ?vf_1B0@type_3D5658@@UAEXH@Z @ 0x0007C010
// sp-match: ?vf_23C@type_3D5658@@UAEHXZ @ 0x0007C020
// sp-match: ?vf_118@type_3D5658@@UAEPAUtype_3D3548@@XZ @ 0x0007C040
// sp-match: ?vf_11C@type_3D5658@@UAEXPAUtype_3D3548@@@Z @ 0x0007C050
// sp-match: ?vf_120@type_3D5658@@UAEPAUAIData@@XZ @ 0x0007C060
// sp-match: ??_Gtype_3D5658@@UAEPAXI@Z @ 0x0007C070
// sp-match: ?vf_0B0@type_3D5658@@UAEXHH@Z @ 0x0007BF70

// match: ?sub_9C1E0@@YAPAUtype_3D5658@@PAUtype_712B0@@@Z @ 0x0009C1E0
// match: __ehhandler$?sub_9C1E0@@YAPAUtype_3D5658@@PAUtype_712B0@@@Z-0x11 @ 0x002FFB10
// match: __ehhandler$?sub_9C1E0@@YAPAUtype_3D5658@@PAUtype_712B0@@@Z @ 0x002FFB21
// sp-match: ?sub_9C1E0@@YAPAUtype_3D5658@@PAUtype_712B0@@@Z @ 0x0007C100
type_3D5658 *sub_9C1E0(type_712B0 *arg_0)
{
    type_3D5658 *var_10;

    var_10 = (type_3D5658 *)sub_D56D0(0x19C0, arg_0->unk_24_18, arg_0->vf_008());
    if (var_10 != 0)
    {
        var_10 = new (var_10) type_3D5658(arg_0);
        if (var_10->unk_28 & 0x400000) // not an address: entity flag
        {
            sub_D5A60(var_10, 0);
            var_10 = 0;
        }
    }
#ifndef CODFH_SP
    else
    {
        sub_19A750("WARNING: A spawn could not be created due to lack of entity memory. Trigger "
                   "location(%6.2f,%6.2f,%6.2f)",
                   arg_0->unk_90, arg_0->unk_94, arg_0->unk_98);
    }
#endif
    return var_10;
}
// match: ??0type_3D5658@@QAE@PAUtype_712B0@@@Z @ 0x0009C2F0
// match: __ehhandler$??0type_3D5658@@QAE@PAUtype_712B0@@@Z-0x24 @ 0x002FFB30
// match: __ehhandler$??0type_3D5658@@QAE@PAUtype_712B0@@@Z @ 0x002FFB54
// sp-match: ??0type_3D5658@@QAE@PAUtype_712B0@@@Z @ 0x0007BE90
type_3D5658::type_3D5658(type_712B0 *arg_0)
{
    sub_9C6E0(arg_0);
}
// match: ??1type_3D5658@@UAE@XZ @ 0x0009C660
// match: __ehhandler$??1type_3D5658@@UAE@XZ-0x24 @ 0x002FFB60
// match: __ehhandler$??1type_3D5658@@UAE@XZ @ 0x002FFB84
// sp-match: ??1type_3D5658@@UAE@XZ @ 0x0007C090
type_3D5658::~type_3D5658()
{
    vf_230();
}
// match: ?sub_9C6E0@type_3D5658@@QAEHPAUtype_712B0@@@Z @ 0x0009C6E0
// sp-match: ?sub_9C6E0@type_3D5658@@QAEHPAUtype_712B0@@@Z @ 0x0007AF70
// Sets the dog up from its trigger arg_0: the base's set-up and its kind
// (by the trigger's unk_114: 1 an ally, 2 or 4 an enemy); its landing and
// wall points unset; its health and AI parameters from the trigger; its
// name object (unk_D0) told it is the entity; its model (unk_D8, a kind-3
// object), without which it reports the trigger and hides itself (0); an
// animation player over its clump; its performance values; an AI object
// running the trigger's two objects' scripts; a script object running
// script 2; its scene and messages; pool 9 or 10; its AI, squad, vision,
// distance, and A* registrations; its sounds.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_3D5658::sub_9C6E0(type_712B0 *arg_0)
{
    RwUInt32 v38;
    RwUInt32 v34;
    RwInt32 v30;
    type_3DF8D8 *var_2C;
    type_3DF8D8 *loc28;
    type_3D2E7C *slot_24;
    type_3D2E7C *v20;
    type_3DF8D8 *slot_1C;
    type_7C8D0 *local_18;
    type_3D2C88 *local_14;
    type_3DFEEC *local_10;
    DogTrigger *fp_C;
    type_3DF8D8 *lv_8;
    RpHAnimHierarchy *var_4;

    fp_C = (DogTrigger *)arg_0;
    unk_19BC = 1;
    unk_88_13 = 0;
    sub_CCCD0(arg_0);
    unk_28 = 0x83C;
    unk_19B8 = 0;
    set_xyz(&unk_10C, -1.0f, -1.0f, -1.0f);
    set_xyz(&unk_134, -1.0f, -1.0f, -1.0f);
    zero_v3d(&unk_118);
    set_xyz(&unk_124, 1000.0f, 1000.0f, 1000.0f);
#ifdef CODFH_SP // shape: the timer's store before the two clears
    unk_108 = dword_42910C;
    unk_130 = 0;
    unk_19A4 = 0;
#else
    unk_130 = 0;
    unk_19A4 = 0;
    unk_108 = dword_42910C;
#endif
    unk_19A0 = fp_C->unk_108;
    unk_4F0 = fp_C->unk_F0;
    unk_4F4 = fp_C->unk_F4;
    unk_4F8 = fp_C->unk_F8;
    unk_4FC = fp_C->unk_FC;
    unk_500 = fp_C->unk_100;
    unk_504 = fp_C->unk_104;
    unk_508 = fp_C->unk_10C;
    unk_50C = fp_C->unk_110;
    if (fp_C->unk_D0.unk_00 != 0) {
        local_10 = (type_3DFEEC *)sub_198800(&fp_C->unk_D0);
        // +0x24 as a handle (a type_D48D0, which cannot join its union).
        ((type_D48D0 *)&local_10->unk_24_id)->sub_D48D0(this);
        local_10->unk_10 = 0x42;
    }
    switch (fp_C->unk_114) {
    case 1:
        unk_2C = 0x20001;       // not an address: kind bits
        unk_30 = 0x27BFF7;      // not an address: kind bits
        break;
    case 2:
        unk_2C = 0x20002;       // not an address: kind bits
        unk_30 = 0x27BFF7;      // not an address: kind bits
        break;
    case 4:
        unk_2C = 0x20002;       // not an address: kind bits
        unk_30 = 0x27BFF7;      // not an address: kind bits
        break;
    }
    unk_34 = 0x30;
    lv_8 = sub_198800(&fp_C->unk_D8);
    if (lv_8 == 0 || lv_8->vf_008() != 3) {
        sub_D3FB0("DogEntity", arg_0, &fp_C->unk_D8);
        unk_4D4 = 0;
        unk_4D8 = 0;
        unk_28_22 = 1;
        return 0;
    }
    slot_1C = lv_8;
    vf_224(slot_1C, 0, 0);
    unk_48 = 90.0f;
    unk_4C = 45.0f;
    unk_50 = 0x42A00000;        // not an address: 80.0f
    zero_v3d(&unk_3C_v);
    unk_40 = 90.0f;
    v34 = sub_78830(2);
    unk_280 = v34;
    local_18 = (type_7C8D0 *)sub_78AC0(unk_280);
    unk_284 = local_18;
    var_4 = sub_16D970(get_unk_264());
    local_18->sub_79470(var_4);
    local_18->unk_1C = (RwInt32)this;
    memset(unk_4DC, 0, 0xC);
    for (v30 = 0; v30 < 6; v30++)
        unk_4DC[v30 + 6] = 1;
    vf_0B0(0, 0);
    var_2C = sub_198800(&fp_C->unk_E0);
    v38 = sub_71870();
    unk_4D4 = v38;
    v20 = vf_098();
    v20->sub_70DF0(this, 2);
    v20->sub_70E10(var_2C->get_unk_18(), 1);
    loc28 = sub_198800(&fp_C->unk_E8);
    if (loc28 != 0)
        v20->sub_70F40(loc28->get_unk_18(), 1);
    local_14 = sub_71770(1);
    // The handle as its struct, stored before the entity is loaded (a
    // struct copy through the getter's return temporary).
    *(type_439E78_00 *)&unk_4D8 = local_14->get_unk_04_h();
    ((type_3D2CD0 *)local_14)->sub_6CDA0(this, 2);
    memcpy(unk_510, fp_C->unk_C0, 6);
    slot_24 = vf_098();
    fp_C->sub_A48B0(slot_24);
    if ((unk_2C & 7) == 2)
        sub_D5B80(this, 9);
    else
        sub_D5B80(this, 10);
    unk_520.sub_16BC0(this);
    sub_3EE10(this);
    sub_40A60(v20->sub_71340(), 2, 0, 1, 0);
    sub_35200(v20->sub_71340(), 0.0f, 1.0e37f, 6, 0, 0, 0, -1, -1);
    sub_34E20(v20->sub_71340());
    sub_32F70(v20->sub_71340(), 0, 100.0f, 0);
    sub_83850(5, &unk_1C0, &unk_4B0);
    unk_58 = 1;
    if (!unk_88_1) {
        vf_078();
        unk_88_1 = 1;
    }
    return 1;
}
// Takes it down: its AI's registrations, the trigger's AI script's
// entity, its AI, its animation, and its objects.
// match: ?vf_230@type_3D5658@@UAEXXZ @ 0x0009CD00
// sp-match: ?vf_230@type_3D5658@@UAEXXZ @ 0x0007B340
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3D5658::vf_230()
{
    type_3DFEEC *var_C;
    type_712B0 *bp_8;
    type_3D2E7C *bp_4;

    if (unk_19BC)
    {
        unk_19BC = 0;
        bp_4 = vf_098();
        if (bp_4)
        {
            sub_330E0(bp_4->sub_71340(), 0);
            sub_34E40(bp_4->sub_71340());
            sub_35330(bp_4->sub_71340());
            sub_40AE0(bp_4->sub_71340());
        }
        bp_8 = get_unk_34C();
        if (bp_8->unk_D0.unk_00)
        {
            var_C = (type_3DFEEC *)sub_198800(&bp_8->unk_D0);
            ((type_D48D0 *)&var_C->unk_24_id)->sub_D48D0(0);
        }
        unk_520.sub_16C50();
        vf_228();
#ifdef CODFH_SP // shape: single player releases it through release_anim (SP 0x7B3E6)
        if (unk_280)
            release_anim(unk_280);
#else
        if (unk_280)
        {
            sub_78870(unk_280);
            unk_280 = 0;
        }
#endif
        if (vf_090())
        {
            sub_717B0((type_3D2C88 *)vf_090());
            unk_4D8 = 0;
        }
        if (bp_4)
        {
            sub_71970((type_3D2C88 *)bp_4);
            unk_4D4 = 0;
        }
    }
}
// match: ?vf_038@type_3D5658@@UAEXM@Z @ 0x0009CE70
// sp-match: ?vf_038@type_3D5658@@UAEXM@Z @ 0x0007B440
void type_3D5658::vf_038(RwReal arg_0)
{
    type_3D3548::vf_038(arg_0);
    sub_16D7F0(0x18);
    unk_520.sub_17190(arg_0);
    sub_16D850(0x18);
}
// match: ?vf_03C@type_3D5658@@UAEXM@Z @ 0x0009CEB0
// sp-match: ?vf_03C@type_3D5658@@UAEXM@Z @ 0x0007B480
void type_3D5658::vf_03C(RwReal arg_0)
{
    if (unk_19A8 > 0.0f)
    {
        unk_19A8 -= arg_0;
    }
    type_3D3548::vf_03C(arg_0);
    sub_16D7F0(0x18);
    unk_520.sub_172F0(arg_0);
    sub_16D850(0x18);
}
// match: ?vf_04C@type_3D5658@@UAEXM@Z @ 0x0009CF20
// sp-match: ?vf_04C@type_3D5658@@UAEXM@Z @ 0x0007B4E0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3D5658::vf_04C(RwReal arg_0)
{
    RpHAnimHierarchy *var_20;
    type_7C8D0 *l1C;
    RpHAnimHierarchy *m_18;
    type_7C8D0 *ebp_14;
    RwReal lv_10;
    RwMatrix *var_C;
    RwMatrix *bp_8;
    RpAtomic *bp_4;

    type_3D3548::vf_04C(arg_0);
    bp_4 = unk_250.unk_08;
    if (bp_4)
    {
        if (unk_28_13)
        {
            ebp_14 = unk_284;
            m_18 = ebp_14->unk_18;
            bp_8 = RpHAnimHierarchyGetMatrixArray(m_18);
            var_C = RwFrameGetLTM(RpAtomicGetFrame(bp_4));
            l1C = unk_284;
            var_20 = l1C->unk_18;
            lv_10 = bp_8[RpHAnimIDGetIndex(var_20, 1)].pos.y - var_C->pos.y;
            bp_4->boundingSphere.center.y = lv_10;
        }
        else
        {
            bp_4->boundingSphere.center.y = unk_48 / 2.0f;
        }
    }
    sub_16D7F0(0x18);
    unk_520.sub_17A20(arg_0);
    sub_16D850(0x18);
}
// match: ?vf_210@type_3D5658@@UAEXPAUtype_D05C0@@@Z @ 0x0009D010
// sp-match: ?vf_210@type_3D5658@@UAEXPAUtype_D05C0@@@Z @ 0x0007B580
void type_3D5658::vf_210(type_D05C0 *arg_0)
{
    if (unk_28_3 && unk_28_5 && !unk_28_7)
    {
        if (unk_19A4 == 1)
        {
            arg_0->unk_00.y += arg_0->unk_48 / flt_429120;
        }
        else
        {
            arg_0->unk_00.y += arg_0->unk_48;
        }
    }
}
// match: ?vf_224@type_3D5658@@UAE_NPAUtype_3DF8D8@@HPAH@Z @ 0x0009D080
// sp-match: ?vf_224@type_3D5658@@UAE_NPAUtype_3DF8D8@@HPAH@Z @ 0x0007B5B0
bool type_3D5658::vf_224(type_3DF8D8 *arg_0, RwInt32 arg_4, RwInt32 *arg_8)
{
    RpAtomic *var_4;

    type_3D3548::vf_224(arg_0, 0, 0);
    var_4 = unk_274.unk_08;
    ((RwObject *)var_4)->flags = 1;
    return true;
}
// match: ?vf_0E4@type_3D5658@@UAEHH@Z @ 0x0009D0C0
// sp-match: ?vf_0E4@type_3D5658@@UAEHH@Z @ 0x0007B5E0
RwInt32 type_3D5658::vf_0E4(RwInt32 arg_0)
{
    type_712B0 *var_4;

    var_4 = get_unk_34C();
    return ((type_3D5658_trigger *)var_4)->unk_C6[arg_0];
}
// match: ?vf_0E8@type_3D5658@@UAEHXZ @ 0x0009D0F0
// sp-match: ?vf_0E8@type_3D5658@@UAEHXZ @ 0x0007B600
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_3D5658::vf_0E8()
{
    type_712B0 *var_8;
    RwInt32 l4;

    var_8 = get_unk_34C();
    for (l4 = 0; l4 < 5; l4++)
    {
        if (((type_3D5658_trigger *)var_8)->unk_C6[l4] == -1)
        {
            break;
        }
    }
    return l4;
}
// match: ?vf_0EC@type_3D5658@@UAEXHH@Z @ 0x0009D150
// sp-match: ?vf_0EC@type_3D5658@@UAEXHH@Z @ 0x0007B620
void type_3D5658::vf_0EC(RwInt32 arg_0, RwInt32 arg_4)
{
    unk_510[arg_0] = (RwUInt16)arg_4;
}
// match: ?vf_0FC@type_3D5658@@UAEMXZ @ 0x0009D170
// sp-match: ?vf_0FC@type_3D5658@@UAEMXZ @ 0x0007B640
RwReal type_3D5658::vf_0FC()
{
    return unk_4F0;
}
// match: ?vf_100@type_3D5658@@UAEMXZ @ 0x0009D190
// sp-match: ?vf_100@type_3D5658@@UAEMXZ @ 0x0007B650
RwReal type_3D5658::vf_100()
{
    return unk_4F4;
}
// match: ?vf_10C@type_3D5658@@UAEMXZ @ 0x0009D1B0
// sp-match: ?vf_10C@type_3D5658@@UAEMXZ @ 0x0007B660
RwReal type_3D5658::vf_10C()
{
    if (unk_520.unk_520)
    {
        return unk_4FC;
    }
    return unk_4F8;
}
// match: ?vf_130@type_3D5658@@UAEMXZ @ 0x0009D1E0
// sp-match: ?vf_130@type_3D5658@@UAEMXZ @ 0x0007B680
RwReal type_3D5658::vf_130()
{
    return unk_504;
}
// match: ?vf_114@type_3D5658@@UAEMXZ @ 0x0009D200
// sp-match: ?vf_114@type_3D5658@@UAEMXZ @ 0x0007B690
RwReal type_3D5658::vf_114()
{
    return unk_4FC * unk_500;
}
// Sets AI parameter arg_0 to arg_4, a float's bits as the script passes
// them.
// match: ?vf_16C@type_3D5658@@UAEHHH@Z @ 0x0009D220
// sp-match: ?vf_16C@type_3D5658@@UAEHHH@Z @ 0x0007B6A0
RwInt32 type_3D5658::vf_16C(RwInt32 arg_0, RwInt32 arg_4)
{
    RwInt32 var_4;

    var_4 = 1;
    switch (arg_0)
    {
    case 0:
        unk_508 = *(RwReal *)&arg_4 * 0.5f;
        break;
    case 1:
        unk_50C = *(RwReal *)&arg_4 * 0.5f;
        break;
    case 2:
        unk_4F0 = cos(*(RwReal *)&arg_4 *= 0.0087266462f);
        break;
    case 3:
        *(RwReal *)&arg_4 = 0.0087266462f;
        unk_4F4 = cos(*(RwReal *)&arg_4);
        break;
    case 4:
        unk_4F8 = *(RwReal *)&arg_4 * 100.0f;
        break;
    case 5:
        unk_4FC = *(RwReal *)&arg_4 * 100.0f;
        break;
    case 6:
        unk_500 = *(RwReal *)&arg_4;
        break;
    case 7:
        unk_504 = *(RwReal *)&arg_4 * 100.0f;
        break;
    }
    return var_4;
}
// match: ?vf_238@type_3D5658@@UAEMXZ @ 0x0009D340
// sp-match: ?vf_238@type_3D5658@@UAEMXZ @ 0x0007B790
RwReal type_3D5658::vf_238()
{
    unk_19A8 = 60.0f;
    return unk_19A8;
}
// Its head's matrix (bone 0x199) while its animation drives it, else 150
// above its frame.
// match: ?vf_104@type_3D5658@@UAEXPAURwMatrixTag@@@Z @ 0x0009D370
// sp-match: ?vf_104@type_3D5658@@UAEXPAURwMatrixTag@@@Z @ 0x0007B7B0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3D5658::vf_104(RwMatrix *arg_0)
{
    type_7C8D0 *var_28;
    type_7C8D0 *ebp_24;
    RwV3d var_20;
    RwMatrix *ebp_14;
    RwInt32 lv_10;
    RpHAnimHierarchy *var_C;
    RpClump *bp_8;
    RwFrame *bp_4;

    bp_8 = unk_25C.unk_08;
    bp_4 = RpClumpGetFrame(bp_8);
    ebp_24 = unk_284;
    if (ebp_24 && unk_28_13)
    {
        var_28 = unk_284;
        var_C = var_28->unk_18;
        ebp_14 = RpHAnimHierarchyGetMatrixArray(var_C);
        lv_10 = RpHAnimIDGetIndex(var_C, 0x199);
        *arg_0 = ebp_14[lv_10];
    }
    else
    {
        var_20.x = var_20.z = 0.0f;
        var_20.y = 150.0f;
        *arg_0 = *RwFrameGetLTM(bp_4);
        RwMatrixTranslate(arg_0, &var_20, rwCOMBINEPOSTCONCAT);
    }
}
// Its eye point: its head (bone 0x199) while its animation drives it, else
// 150 above its frame.
// match: ?vf_108@type_3D5658@@UAEXPAURwV3d@@@Z @ 0x0009D450
// sp-match: ?vf_108@type_3D5658@@UAEXPAURwV3d@@@Z @ 0x0007B850
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3D5658::vf_108(RwV3d *arg_0)
{
    RwMatrix *var_18;
    RwMatrix *var_14;
    RwInt32 lv_10;
    RpHAnimHierarchy *var_C;
    RpClump *bp_8;
    RwFrame *bp_4;

    bp_8 = unk_25C.unk_08;
    bp_4 = RpClumpGetFrame(bp_8);
    if (unk_284 && unk_28_13)
    {
        var_C = unk_284->unk_18;
        var_14 = RpHAnimHierarchyGetMatrixArray(var_C);
        lv_10 = RpHAnimIDGetIndex(var_C, 0x199);
        *arg_0 = var_14[lv_10].pos;
    }
    else
    {
        var_18 = RwFrameGetLTM(bp_4);
        *arg_0 = var_18->pos;
        arg_0->y += 150.0f;
    }
}
// Its aim point (bone 0x71) while its animation drives it, else 50 above
// its frame.
// match: ?vf_110@type_3D5658@@UAEXPAURwV3d@@PAUtype_3D3548@@H@Z @ 0x0009D520
// sp-match: ?vf_110@type_3D5658@@UAEXPAURwV3d@@PAUtype_3D3548@@H@Z @ 0x0007B8E0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3D5658::vf_110(RwV3d *arg_0, type_3D3548 *arg_4, RwInt32 arg_8)
{
    type_7C8D0 *var_28;
    type_7C8D0 *ebp_24;
    RwV3d var_20;
    RwMatrix *ebp_14;
    RwInt32 lv_10;
    RpHAnimHierarchy *var_C;
    RpClump *bp_8;
    RwFrame *bp_4;

    bp_8 = unk_25C.unk_08;
    bp_4 = RpClumpGetFrame(bp_8);
    ebp_24 = unk_284;
    if (ebp_24 && unk_28_13)
    {
        var_28 = unk_284;
        var_C = var_28->unk_18;
        ebp_14 = RpHAnimHierarchyGetMatrixArray(var_C);
        lv_10 = RpHAnimIDGetIndex(var_C, 0x71);
        *arg_0 = ebp_14[lv_10].pos;
    }
    else
    {
        var_20.x = 0.0f;
        var_20.y = 50.0f;
        var_20.z = 0.0f;
        sub_1414C0(arg_0, &var_20, RwFrameGetLTM(bp_4));
    }
}
// match: ?vf_078@type_3D5658@@UAEXXZ @ 0x0009D5F0
// sp-match: ?vf_078@type_3D5658@@UAEXXZ @ 0x0007B980
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3D5658::vf_078()
{
    RpHAnimHierarchy *var_8;
    type_7C8D0 *l4;

    l4 = unk_284;
    var_8 = l4->unk_18;
    sub_8D580(var_8, 2);
}
// The line of arg_4 against its bone boxes: the first test when arg_0 is
// 1, else the other; -1 for a miss or while unk_88_1 is clear.
// match: ?vf_07C@type_3D5658@@UAEHCPAURpIntersection@@PAMH@Z @ 0x0009D620
// sp-match: ?vf_07C@type_3D5658@@UAEHCPAURpIntersection@@PAMH@Z @ 0x0007B9A0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_3D5658::vf_07C(RwInt8 arg_0, RpIntersection *arg_4, RwReal *arg_8, RwInt32 arg_C)
{
    RpHAnimHierarchy *var_14;
    type_7C8D0 *lv_10;
    RpHAnimHierarchy *var_C;
    type_7C8D0 *bp_8;
    RwInt32 bp_4;

    if (!unk_88_1)
    {
        return -1;
    }
    bp_4 = -1;
    if (arg_0 == 1)
    {
        bp_8 = unk_284;
        var_C = bp_8->unk_18;
        bp_4 = sub_8D660(0xB, var_C, arg_4, 2, 0);
    }
    else
    {
        lv_10 = unk_284;
        var_14 = lv_10->unk_18;
        bp_4 = sub_8E330(0xB, var_14, arg_4, 2, 0);
    }
    return bp_4;
}
// A bullet: resets its hit-death values, takes the damage and tells its
// script.
// match: ?vf_064@type_3D5658@@UAEHPAUtype_75600@@@Z @ 0x0009D6C0
// sp-match: ?vf_064@type_3D5658@@UAEHPAUtype_75600@@@Z @ 0x0007BA00
RwInt32 type_3D5658::vf_064(type_75600 *arg_0)
{
    RwInt32 var_4;

    if (arg_0->unk_24 != -1)
    {
        unk_19AC[0] = 0;
        unk_19AC[1] = 0x19;
        unk_19AC[2] = 1;
        unk_19AC[3] = 0;
        unk_19AC[4] = 0;
        unk_19AC[5] = 0;
        for (var_4 = 0; var_4 < 6; var_4++)
        {
            unk_19AC[var_4 + 6] = 1;
        }
        unk_19A0 -= (RwInt32)arg_0->unk_28;
        sub_6B5F0("HitByBullet", (type_67620 *)(vf_098()), 0, 0, 0, 0, 1, 0);
        sub_D2AD0(arg_0->unk_0C, arg_0->unk_04);
    }
    return 0;
}
// An explosion that reaches it: resets its hit-death values, takes the
// damage and tells its script where it came from and whether from behind.
// match: ?vf_068@type_3D5658@@UAEHPAUtype_758F0@@@Z @ 0x0009D7A0
// sp-match: ?vf_068@type_3D5658@@UAEHPAUtype_758F0@@@Z @ 0x0007BAA0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_3D5658::vf_068(type_758F0 *arg_0)
{
    RwInt32 var_30;
    RwV3d *var_2C;
    RwFrame *lv_28;
    RwV3d var_24;
    RwMatrix *bp_18;
    type_758F0_14 var_14;

    if (arg_0->unk_2C != 0.0f && vf_070(arg_0, 0, 0))
    {
        unk_19AC[0] = 0;
        unk_19AC[1] = 0x19;
        unk_19AC[2] = 1;
        unk_19AC[3] = 0;
        unk_19AC[4] = 0;
        unk_19AC[5] = 0;
        for (var_30 = 0; var_30 < 6; var_30++)
        {
            unk_19AC[var_30 + 6] = 1;
        }
        unk_19A0 -= (RwInt32)arg_0->unk_2C;
        var_2C = RwMatrixGetPos(arg_0->unk_0C);
        lv_28 = unk_338.unk_08;
        bp_18 = RwFrameGetLTM(lv_28);
        var_24 = *RwMatrixGetPos(bp_18);
        RwV3dSubMacro(&var_24, &var_24, var_2C);
        var_14.unk_00 = var_2C->x;
        var_14.unk_04 = var_2C->y;
        var_14.unk_08 = var_2C->z;
        var_14.unk_0C = arg_0->unk_14;
        var_14.unk_10 = RwV3dDotProductMacro(&bp_18->at, &var_24) <= 0 ? 1 : 0;
        sub_6B5F0("HitByExplosion", (type_67620 *)(vf_098()), 0, 0, (RwInt32 *)(&var_14), 5, 1, 0);
        sub_D2AD0(arg_0->unk_04.sub_D4910(), arg_0->unk_08);
    }
    return 0;
}
// A collision with the entity arg_0 (a vehicle or a heavy object) moving
// faster than 0.2: resets its hit-death values with a random one, takes
// 100 and tells its script as an explosion of 1.
// match: ?vf_060@type_3D5658@@UAEHPAUtype_3D3548@@@Z @ 0x0009D980
// sp-match: ?vf_060@type_3D5658@@UAEHPAUtype_3D3548@@@Z @ 0x0007BBF0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_3D5658::vf_060(type_3D3548 *arg_0)
{
    RwInt32 ebp_34;
    RwV3d *var_30;
    RwFrame *var_2C;
    RwV3d lcl_28;
    RwMatrix *ebp_1C;
    type_758F0_14 l18;
    RwReal l4;

    if (arg_0 && (arg_0->unk_2C & 0x3FFFFF0 & 0x40080)) // not an address: kind bits
    {
        l4 = RwV3dLength((RwV3d *)&arg_0->unk_D8);
        if (l4 > 0.2f)
        {
            unk_19AC[0] = 0;
            unk_19AC[1] = 0;
            unk_19AC[2] = (RwInt8)(RpRandom() % 9);
            unk_19AC[3] = 0;
            unk_19AC[4] = 0;
            unk_19AC[5] = 0;
            for (ebp_34 = 0; ebp_34 < 6; ebp_34++)
            {
                unk_19AC[ebp_34 + 6] = 1;
            }
            unk_19A0 -= 100;
            var_30 = arg_0->sub_CD550();
            var_2C = unk_338.unk_08;
            ebp_1C = RwFrameGetLTM(var_2C);
            lcl_28 = *RwMatrixGetPos(ebp_1C);
            RwV3dSubMacro(&lcl_28, &lcl_28, var_30);
            l18.unk_00 = var_30->x;
            l18.unk_04 = var_30->y;
            l18.unk_08 = var_30->z;
            l18.unk_0C = 1.0f;
            l18.unk_10 = RwV3dDotProductMacro(&ebp_1C->at, &lcl_28) <= 0 ? 1 : 0;
            sub_6B5F0("HitByExplosion", (type_67620 *)(vf_098()), 0, 0, (RwInt32 *)(&l18), 5, 1, 0);
        }
    }
    return 0;
}
// match: ?vf_054@type_3D5658@@UAEXH@Z @ 0x0009DB60
// sp-match: ?vf_054@type_3D5658@@UAEXH@Z @ 0x0007BD40
void type_3D5658::vf_054(RwInt32 arg_0)
{
    RpClump *var_4;

    sub_16D7F0(0x11);
    var_4 = unk_25C.unk_08;
    if (var_4)
    {
        sub_D2920(var_4, 0);
    }
    sub_16D850(0x11);
}
// Lands (arg_0 set) or hits a wall while falling or flying: resets its
// motion and tells its script.
// match: ?vf_1C4@type_3D5658@@UAEXH@Z @ 0x0009DBB0
// sp-match: ?vf_1C4@type_3D5658@@UAEXH@Z @ 0x0007BD70
void type_3D5658::vf_1C4(RwInt32 arg_0)
{
    if (!unk_19A4)
    {
        return;
    }
    if (arg_0)
    {
        unk_130 = 0;
        set_v3d(&unk_10C, -1.0f, -1.0f, -1.0f);
        unk_19A4 = 0;
        sub_6B5F0("HitGround", (type_67620 *)(vf_098()), 0, 0, 0, 0, 1, 0);
    }
    else if (unk_19A4 == 1)
    {
        set_v3d(&unk_10C, -1.0f, 0.0f, -1.0f);
        unk_DC = 0.0f;
        unk_19A4 = 2;
        sub_6B5F0("HitWall", (type_67620 *)(vf_098()), 0, 0, 0, 0, 1, 0);
    }
}
// match: ?vf_098@type_3D5658@@UAEPAUtype_3D2E7C@@XZ @ 0x0009DCC0
// sp-match: ?vf_098@type_3D5658@@UAEPAUtype_3D2E7C@@XZ @ 0x0007BE20
type_3D2E7C *type_3D5658::vf_098()
{
    return (type_3D2E7C *)sub_67620(unk_4D4);
}
// match: ?vf_090@type_3D5658@@UAEPAUtype_6D380@@XZ @ 0x0009DCE0
// sp-match: ?vf_090@type_3D5658@@UAEPAUtype_6D380@@XZ @ 0x0007BE30
type_6D380 *type_3D5658::vf_090()
{
    return (type_6D380 *)sub_67620(unk_4D8);
}
// Whether arg_0 is one of its keys (the trigger's AI script and tasks).
// match: ?vf_058@type_3D5658@@UAEHPAUtype_3DF8D8_04@@@Z @ 0x0009DD00
// sp-match: ?vf_058@type_3D5658@@UAEHPAUtype_3DF8D8_04@@@Z @ 0x0007BE40
RwInt32 type_3D5658::vf_058(type_3DF8D8_04 *arg_0)
{
    type_712B0 *var_4;

    var_4 = get_unk_34C();
    if (arg_0->unk_00 == var_4->unk_D0.unk_00 && arg_0->unk_04 == var_4->unk_D0.unk_04)
    {
        return 1;
    }
    if (arg_0->unk_00 == var_4->unk_D8.unk_00 && arg_0->unk_04 == var_4->unk_D8.unk_04)
    {
        return 1;
    }
    return 0;
}
// ??2type_3D51C0@@SAPAXIPAX@Z (folded into 0x6CCF0)
void *type_3D51C0::operator new(RwUInt32 arg_0, void *arg_4)
{
    return arg_4;
}
