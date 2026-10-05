// Split from unit_09AD40.cpp at 0x09B700, where the image starts another object
// (type_3D5400, its factory function first): its .rdata begins at 0x3D53F8 with its own copy of the
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
// 0x003D53F8
extern const RwReal flt_3D53F8 = 16.666666f;
// 0x003D53FC
extern const RwReal flt_3D53FC = 0.0f;

// match: ?flt_3D53F8@@3MB @ 0x003D53F8
// match: ?flt_3D53FC@@3MB @ 0x003D53FC


// match: __ehhandler$?sub_9B700@@YAPAUtype_3D5400@@PAUtype_712B0@@@Z>1>8 @ 0x0041B7C0
// match: __ehhandler$?sub_9B700@@YAPAUtype_3D5400@@PAUtype_712B0@@@Z>1 @ 0x0041B7D0
// match: __ehhandler$??1type_3D5400@@UAE@XZ>1>8 @ 0x0041B7EC
// match: __ehhandler$??1type_3D5400@@UAE@XZ>1 @ 0x0041B7F4
// match: ??_Gtype_3D5400@@UAEPAXI@Z @ 0x0009B830
// match: ??_7type_3D5400@@6B@ @ 0x003D5400
// match: ??_C@_0BL@MFGJPJCP@MeshSwapDestructableEntity?$AA@ @ 0x003D5638

// match: ?sub_9B700@@YAPAUtype_3D5400@@PAUtype_712B0@@@Z @ 0x0009B700
// match: __ehhandler$?sub_9B700@@YAPAUtype_3D5400@@PAUtype_712B0@@@Z-0x19 @ 0x002FFAC0
// match: __ehhandler$?sub_9B700@@YAPAUtype_3D5400@@PAUtype_712B0@@@Z @ 0x002FFAD9
type_3D5400 *sub_9B700(type_712B0 *arg_0)
{
    type_3D5400 *var_10;

    var_10 = (type_3D5400 *)sub_D56D0(0x3E0, arg_0->unk_24_18, arg_0->vf_008());
    if (var_10 != 0)
    {
        var_10 = new (var_10) type_3D5400(arg_0);
        if (var_10->unk_28 & 0x400000) // not an address: entity flag
        {
            sub_D5A60(var_10, 0);
            var_10 = 0;
        }
    }
    else
    {
        sub_19A750("WARNING: A spawn could not be created due to lack of entity memory. Trigger "
                   "location(%6.2f,%6.2f,%6.2f)",
                   arg_0->unk_90, arg_0->unk_94, arg_0->unk_98);
    }
    return var_10;
}
// match: ??1type_3D5400@@UAE@XZ @ 0x0009B860
// match: __ehhandler$??1type_3D5400@@UAE@XZ-0x8 @ 0x002FFAF0
// match: __ehhandler$??1type_3D5400@@UAE@XZ @ 0x002FFAF8
type_3D5400::~type_3D5400()
{
    vf_230();
}
// match: ?vf_234@type_3D5400@@UAEHPAUtype_712B0@@@Z @ 0x0009B8C0
// Sets the mesh-swap destructable entity up from its trigger arg_0: the
// base's set-up and its kind; its health from the trigger's +0xE0; its
// name object (unk_D0) told it is the entity (flags 0x402); its first mesh
// (unk_100, a kind-3 object), without which it reports the trigger and
// hides itself (0); its sounds; an AI object running the trigger's two
// objects' scripts (unk_C0 as a state machine, unk_C8 as a task); pool 6.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_3D5400::vf_234(type_712B0 *arg_0)
{
    RwInt32 bp_2C;
    RwInt32 local_28;
    RwUInt32 local_24;
    type_3DF8D8 *local_20;
    type_3DF8D8 *var_1C;
    type_3D2E7C *var18;
    type_3DF8D8 *stk_14;
    RwInt32 l10;
    type_3DFEEC *local_C;
    MeshSwapDestructableObjectTrigger *lv_8;
    type_3DF8D8 *var_4;

    lv_8 = (MeshSwapDestructableObjectTrigger *)arg_0;
    unk_3DC = 1;
    sub_CCCD0(arg_0);
    unk_28 = 4;
    unk_2C = 0x10000;           // not an address: kind bits
    unk_30 = 0xFFFFFFFF;
    // The trigger's +0xE0 read as a float here (its own set-up stores an
    // int there).
    unk_3D8 = (RwInt32)*(RwReal *)&lv_8->unk_E0;
    if (lv_8->unk_D0.unk_00 != 0) {
        local_C = (type_3DFEEC *)sub_198800(&lv_8->unk_D0);
        // +0x24 as a handle (a type_D48D0, which cannot join its union).
        ((type_D48D0 *)&local_C->unk_24_id)->sub_D48D0(this);
        local_C->unk_10 = 0x402;
    }
    var_4 = sub_198800(&lv_8->unk_100);
    if (var_4 == 0 || var_4->vf_008() != 3) {
        sub_D3FB0("MeshSwapDestructableEntity", arg_0, &lv_8->unk_100);
        unk_3D4 = 0;
        unk_28_22 = 1;
        return 0;
    }
    stk_14 = var_4;
    vf_224(stk_14, 0, &l10);
    local_20 = sub_198800(&lv_8->unk_C0);
    sub_83850(3, &unk_1C0, &unk_3B0);
    local_24 = sub_71870();
    unk_3D4 = local_24;
    var18 = vf_098();
    var18->sub_70DF0(this, 2);
    local_28 = local_20->unk_18;
    var18->sub_70E10(local_28, 1);
    var_1C = sub_198800(&lv_8->unk_C8);
    if (var_1C != 0) {
        bp_2C = var_1C->unk_18;
        var18->sub_70F40(bp_2C, 1);
    }
    sub_D5B80(this, 6);
    return 1;
}
// Takes it down: its AI object, and the trigger's AI script's entity.
// match: ?vf_230@type_3D5400@@UAEXXZ @ 0x0009BAB0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3D5400::vf_230()
{
    type_3DFEEC *var_8;
    type_712B0 *l4;

    if (unk_3DC)
    {
        unk_3DC = 0;
        vf_228();
        if (vf_098())
        {
            sub_71970((type_3D2C88 *)vf_098());
            unk_3D4 = 0;
        }
        l4 = get_unk_34C();
        if (l4->unk_D0.unk_00)
        {
            var_8 = (type_3DFEEC *)sub_198800(&l4->unk_D0);
            ((type_D48D0 *)&var_8->unk_24_id)->sub_D48D0(0);
        }
    }
}
// match: ?sub_9BB60@type_9BB60@@QAEXXZ @ 0x0009BB60
// "SwapToDestroyedVersion" (type_9BB60 is type_3D5400 as the script command
// sees it): takes on its trigger's second mesh (unk_108, a kind-3 object)
// when it has one, spawns the trigger's particle system (unk_DC) where it
// stands, and stops being hit by explosions unless the trigger says
// otherwise (unk_E4).
void type_9BB60::sub_9BB60()
{
    MeshSwapDestructableObjectTrigger *var_8;
    type_3DF8D8 *var_C;
    type_3DF8D8 *var_10;
    RwMatrix var_50;

    var_8 = (MeshSwapDestructableObjectTrigger *)unk_344.unk_08;
    if (var_8->unk_108.unk_00 != 0 || var_8->unk_108.unk_04 != 0) {
        vf_228();
        var_C = sub_198800(&var_8->unk_108);
        if (var_C == 0 || var_C->vf_008() != 3)
            return;
        var_10 = var_C;
        vf_224(var_10, 0, 0);
    }
    if (var_8->unk_DC != 0) {
        RwMatrixSetIdentityMacro(&var_50);
        var_50.pos = *sub_CD550();
        sub_F2FF0(var_8->unk_DC, &var_50, 0, 1, false, false);
    }
    if (var_8->unk_E4 == 0)
        unk_28_2 = 0;
}
// match: ?vf_064@type_3D5400@@UAEHPAUtype_75600@@@Z @ 0x0009BCC0
// Hit by a bullet: as type_3D32F8's (unit_073710), by its trigger's flags
// (unk_F0 bullets at all, unk_E8 and unk_EC from allies and enemies), off
// its health unk_3D8.
RwInt32 type_3D5400::vf_064(type_75600 *arg_0)
{
    DestructableObjectTrigger *v8;
    type_3D3548 *varC;
    RwInt32 var_4;

    if (arg_0 != 0) {
        v8 = (DestructableObjectTrigger *)unk_344.unk_08;
        if (v8->unk_F0 == 0)
            return 0;
        if (arg_0->unk_0C != 0) {
            varC = arg_0->unk_0C;
            if (v8->unk_E8 == 0 && varC->unk_2C_0)
                return 0;
            if (v8->unk_EC == 0 && varC->unk_2C_1)
                return 0;
        }
        unk_3D8 -= (RwInt32)arg_0->unk_28;
        sub_6B5F0("HitByBullet", (type_67620 *)(vf_098()), 0, 0, 0, 0, 1, 0);
        var_4 = 0;
        sub_6B5F0("HitByBulletRWS", (type_67620 *)(vf_098()), 0, 0, &var_4, 1, 1, 0);
        sub_D2AD0(arg_0->unk_0C, arg_0->unk_04);
    }
    return 0;
}
// match: ?vf_068@type_3D5400@@UAEHPAUtype_758F0@@@Z @ 0x0009BDE0
// Hit by an explosion: likewise (unk_F4), telling the script where it came
// from and whether in front.
RwInt32 type_3D5400::vf_068(type_758F0 *arg_0)
{
    RwV3d *ebp_34;
    RwFrame *var_30;
    RwV3d bp_2C;
    DestructableObjectTrigger *local_20;
    RwMatrix *var_1C;
    RwInt32 var_18;
    type_758F0_14 var_14;

    if (arg_0 != 0 && arg_0->unk_2C > 0 && vf_070(arg_0, 0, 0)) {
        local_20 = (DestructableObjectTrigger *)unk_344.unk_08;
        if (local_20->unk_F4 == 0)
            return 0;
        unk_3D8 -= (RwInt32)arg_0->unk_2C;
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
// match: ?vf_060@type_3D5400@@UAEHPAUtype_3D3548@@@Z @ 0x0009BFB0
// Struck by an entity of kind 0x80 or 0x40000 (a vehicle, a tank): 100 off
// its health, told to the script as an explosion at the entity of strength 1.
RwInt32 type_3D5400::vf_060(type_3D3548 *arg_0)
{
    RwV3d *ebp_34;
    RwFrame *var_30;
    RwV3d bp_2C;
    DestructableObjectTrigger *local_20;
    RwMatrix *var_1C;
    RwInt32 var_18;
    type_758F0_14 var_14;

    if (arg_0 != 0 && ((arg_0->unk_2C & 0x3FFFFF0) & 0x40080) != 0) {  // not an address: kind bits
        local_20 = (DestructableObjectTrigger *)unk_344.unk_08;
        if (local_20->unk_F4 == 0)
            return 0;
        unk_3D8 -= 100;
        ebp_34 = arg_0->sub_CD550();
        var_30 = unk_338.unk_08;
        var_1C = RwFrameGetLTM(var_30);
        bp_2C = *RwMatrixGetPos(var_1C);
        RwV3dSubMacro(&bp_2C, &bp_2C, ebp_34);
        var_14.unk_00 = ebp_34->x;
        var_14.unk_04 = ebp_34->y;
        var_14.unk_08 = ebp_34->z;
        var_14.unk_0C = 1.0f;
        var_14.unk_10 = RwV3dDotProductMacro(&var_1C->at, &bp_2C) <= 0 ? 1 : 0;
        sub_6B5F0("HitByExplosion", (type_67620 *)(vf_098()), 0, 0, (RwInt32 *)(&var_14), 5, 1, 0);
        var_18 = 0;
        sub_6B5F0("HitByExplosionRWS", (type_67620 *)(vf_098()), 0, 0, &var_18, 1, 1, 0);
    }
    return 0;
}
// match: ?vf_098@type_3D5400@@UAEPAUtype_3D2E7C@@XZ @ 0x0009C140
type_3D2E7C *type_3D5400::vf_098()
{
    return (type_3D2E7C *)sub_67620(unk_3D4);
}
// Whether arg_0 is one of its keys (the trigger's unk_100_k and unk_108_k).
// match: ?vf_058@type_3D5400@@UAEHPAUtype_3DF8D8_04@@@Z @ 0x0009C160
RwInt32 type_3D5400::vf_058(type_3DF8D8_04 *arg_0)
{
    type_712B0 *var_4;

    var_4 = get_unk_34C();
    if (arg_0->unk_00 == var_4->unk_100_k.unk_00 && arg_0->unk_04 == var_4->unk_100_k.unk_04)
    {
        return 1;
    }
    if (arg_0->unk_00 == var_4->unk_108_k.unk_00 && arg_0->unk_04 == var_4->unk_108_k.unk_04)
    {
        return 1;
    }
    return 0;
}
