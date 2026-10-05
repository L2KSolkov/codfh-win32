// An entity class spawned from triggers (type_3D51C0): its spawn, set-up
// and handlers. The file's original name is not recovered (M1), so it is
// named for its start address.

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
// 0x003D51B4
extern const RwReal flt_3D51B4 = 16.666666f;
// 0x003D51B8
extern const RwReal flt_3D51B8 = 16.666666f;
// 0x003D51BC
extern const RwReal flt_3D51BC = 0.0f;
// 0x004B8690
#ifndef CODFH_PLAIN
type_3D3548 *dword_4B8690;
#endif
// 0x004B86A0
#ifndef CODFH_PLAIN
type_3D3548 *dword_4B86A0;
#endif
// End of its data definitions.


// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).
RWS::CEventId dword_4B67B8;
RWS::CEventId dword_4B67C0;
RWS::CEventId dword_4B67B0;
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3D51B4@@3MB @ 0x003D51B4
// match: ?flt_3D51B8@@3MB @ 0x003D51B8
// match: ?flt_3D51BC@@3MB @ 0x003D51BC
// match: ??_7type_3D51C0@@6B@ @ 0x003D51C0
// match: __ehhandler$?sub_9AD40@@YAPAUtype_3D51C0@@PAUtype_712B0@@@Z>1>8 @ 0x0041B724
// match: __ehhandler$?sub_9AD40@@YAPAUtype_3D51C0@@PAUtype_712B0@@@Z>1 @ 0x0041B72C
// match: __ehhandler$??0type_3D51C0@@QAE@PAUtype_712B0@@@Z>1>8 @ 0x0041B748
// match: __ehhandler$??0type_3D51C0@@QAE@PAUtype_712B0@@@Z>1 @ 0x0041B760
// match: __ehhandler$??1type_3D51C0@@UAE@XZ>1>8 @ 0x0041B77C
// match: __ehhandler$??1type_3D51C0@@UAE@XZ>1 @ 0x0041B7A4
// match: .CRT$XCU+0 @ 0x00426ED4
// match: .CRT$XCU+4 @ 0x00426ED8
// match: .CRT$XCU+8 @ 0x00426EDC

// match: _$E2 @ 0x0030A450
// match: _$E3 @ 0x0030DF30
// match: _$E5 @ 0x0030A470
// match: _$E6 @ 0x0030DF40
// match: _$E8 @ 0x0030A490
// match: _$E9 @ 0x0030DF50


// The registration initializers pass these exact exits to atexit.

// (The class factory's registration and its exit thunk.)

// match: ?sub_9AD40@@YAPAUtype_3D51C0@@PAUtype_712B0@@@Z @ 0x0009AD40
// match: __ehhandler$?sub_9AD40@@YAPAUtype_3D51C0@@PAUtype_712B0@@@Z-0x11 @ 0x002FFA30
// match: __ehhandler$?sub_9AD40@@YAPAUtype_3D51C0@@PAUtype_712B0@@@Z @ 0x002FFA41
type_3D51C0 *sub_9AD40(type_712B0 *arg_0)
{
    type_3D51C0 *var_10;

    var_10 = (type_3D51C0 *)sub_D56D0(0x3E0, arg_0->unk_24_18, arg_0->vf_008());
    if (var_10 != 0)
    {
        var_10 = new (var_10) type_3D51C0(arg_0);
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

// match: ??0type_3D51C0@@QAE@PAUtype_712B0@@@Z @ 0x0009AE50
// match: __ehhandler$??0type_3D51C0@@QAE@PAUtype_712B0@@@Z-0x24 @ 0x002FFA50
// match: __ehhandler$??0type_3D51C0@@QAE@PAUtype_712B0@@@Z @ 0x002FFA74
// (Defined in the class, in type_3D51C0.h.)

// match: ?vf_09C@type_3D51C0@@UAEHXZ @ 0x0009AF10

// match: ?vf_0A0@type_3D51C0@@UAEXI@Z @ 0x0009AF30

// match: ?vf_0E0@type_3D51C0@@UAEPAEXZ @ 0x0009AF50

// match: ?vf_0EC@type_3D51C0@@UAEXHH@Z @ 0x0009AF70

// match: ?vf_094@type_3D51C0@@UAEXI@Z @ 0x0009AF90

// match: ??_Gtype_3D51C0@@UAEPAXI@Z @ 0x0009AFB0
// (Its scalar deleting destructor, compiler-written.)

// match: ??1type_3D51C0@@UAE@XZ @ 0x0009AFE0
// match: __ehhandler$??1type_3D51C0@@UAE@XZ-0x34 @ 0x002FFA80
// match: __ehhandler$??1type_3D51C0@@UAE@XZ @ 0x002FFAB4
type_3D51C0::~type_3D51C0()
{
    vf_230();
}

// match: ?vf_234@type_3D51C0@@UAEHPAUtype_712B0@@@Z @ 0x0009B0B0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_3D51C0::vf_234(type_712B0 *arg_0)
{
    // These two named setter values precede the struct-return temporary
    // at -0x24. zero_v3d and the script getters supply -0x28/-0x2C/-0x30.
    RwUInt32 var_20;
    RwUInt32 l1C;
    type_3D2E7C *m_18;
    type_3DF8D8 *ebp_14;
    type_3D2E7C *lv_10;
    type_3DF8D8 *var_C;
    CustomTrigger *bp_8;
    type_3D2C88 *bp_4;

    bp_8 = (CustomTrigger *)arg_0;
    unk_3D8 = 1;
    sub_CCCD0(arg_0);
    unk_28 = 0x34;
    unk_2C = 0x10000; // not an address: entity kind
    unk_30 = -1;
    unk_48 = 90.0f;
    unk_4C = 45.0f;
    unk_50_r = 80.0f;
    zero_v3d(&unk_3C_v);
    unk_40 = 90.0f;
    if (bp_8->unk_C0.unk_30.unk_00 && bp_8->unk_C0.unk_30.unk_04)
    {
        ebp_14 = sub_198800(&bp_8->unk_C0.unk_30);
        lv_10 = vf_098();
        if (!lv_10)
        {
            l1C = sub_71870();
            unk_3D4 = l1C;
            lv_10 = vf_098();
            lv_10->sub_70DF0(this, 2);
        }
        lv_10->sub_70E10(ebp_14->get_unk_18(), 1);
    }
    var_C = sub_198800(&bp_8->unk_C0.unk_38);
    if (var_C)
    {
        m_18 = vf_098();
        if (!m_18)
        {
            var_20 = sub_71870();
            unk_3D4 = var_20;
            m_18 = vf_098();
            m_18->sub_70DF0(this, 2);
        }
        m_18->sub_70F40(var_C->get_unk_18(), 1);
    }
    bp_4 = sub_71770(1);
    *(type_439E78_00 *)&unk_3D0 = bp_4->get_unk_04_h();
    ((type_3D2CD0 *)bp_4)->sub_6CDA0(this, 3);
    memcpy(unk_3C8, bp_8->unk_10C, 6);
    sub_D5B80(this, 7);
    return 1;
}

// match: ?sub_9B2C0@type_3D3548@@QAEXH@Z @ 0x0009B2C0
// "Custom_SetAnimatedObject": for an entity in a custom trigger (kind 0xB),
// drops its current object and animation, then takes on the trigger's
// animated object arg_0 (a kind-3 object) with a new animation player over
// its clump's hierarchy.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3D3548::sub_9B2C0(RwInt32 arg_0)
{
    RwInt32 l4;
    CustomTrigger *var_8;
    RwInt32 fp_C;
    RpHAnimHierarchy *v10;
    type_7C8D0 *local_14;
    type_3DF8D8 *var18;
    type_3DF8D8 *var_1C;
    type_712B0 *l20;
    RwUInt32 fp_24;

    if (get_unk_34C() == 0)
        return;
    l20 = (type_712B0 *)unk_344.unk_08;
    if (l20->vf_008() != 0xB)
        return;
    var_8 = (CustomTrigger *)l20;
    vf_228();
    sub_78870(unk_280);
    unk_280 = 0;
    if (arg_0 < 0)
        return;
    var18 = sub_198800(&var_8->unk_C0.unk_10[arg_0]);
    if (var18 == 0 || var18->vf_008() != 3)
        return;
    var_1C = var18;
    vf_224(var_1C, 0, &fp_C);
    fp_24 = sub_78830(0);
    unk_280 = fp_24;
    local_14 = (type_7C8D0 *)sub_78AC0(unk_280);
    unk_284 = local_14;
    v10 = sub_16D970(get_unk_264());
    local_14->sub_79470(v10);
    local_14->unk_1C = (RwInt32)this;
    RpHAnimHierarchyAttach(v10);
    l4 = v10->flags;
    l4 |= rpHANIMHIERARCHYUPDATEMODELLINGMATRICES;
    v10->flags = l4;
}

// match: ?sub_9B430@type_3D3548@@QAEXH@Z @ 0x0009B430
// "Custom_SetObject": likewise with the trigger's object arg_0, without an
// animation.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3D3548::sub_9B430(RwInt32 arg_0)
{
    CustomTrigger *var_4;
    RwInt32 v8;
    type_3DF8D8 *stk_C;
    type_3DF8D8 *var_10;
    type_712B0 *lv_14;

    if (get_unk_34C() == 0)
        return;
    lv_14 = (type_712B0 *)unk_344.unk_08;
    if (lv_14->vf_008() != 0xB)
        return;
    var_4 = (CustomTrigger *)lv_14;
    vf_228();
    sub_78870(unk_280);
    unk_280 = 0;
    if (arg_0 < 0)
        return;
    stk_C = sub_198800(&var_4->unk_C0.unk_00[arg_0]);
    if (stk_C == 0 || stk_C->vf_008() != 3)
        return;
    var_10 = stk_C;
    vf_224(var_10, 0, &v8);
}

// Takes it down: its script object, its animation and its objects.
// match: ?vf_230@type_3D51C0@@UAEXXZ @ 0x0009B510
void type_3D51C0::vf_230()
{
    if (unk_3D8)
    {
        unk_3D8 = 0;
        vf_228();
        unk_3BC.sub_129940(0);
        sub_78870(unk_280);
        unk_280 = 0;
        if (vf_090())
        {
            sub_717B0((type_3D2C88 *)vf_090());
            unk_3D0 = 0;
        }
        if (vf_098())
        {
            sub_71970((type_3D2C88 *)vf_098());
            unk_3D4 = 0;
        }
    }
}

// match: ?vf_054@type_3D51C0@@UAEXH@Z @ 0x0009B5F0
void type_3D51C0::vf_054(RwInt32 arg_0)
{
    type_3D3548::vf_054(arg_0);
}

// A bullet from a player tells its script.
// match: ?vf_064@type_3D51C0@@UAEHPAUtype_75600@@@Z @ 0x0009B610
RwInt32 type_3D51C0::vf_064(type_75600 *arg_0)
{
    RwInt32 var_4;

    if (arg_0 && arg_0->unk_28 > 0.0f)
    {
        if (arg_0->unk_0C)
        {
            if (!arg_0->unk_0C->unk_2C_4)
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
        sub_6B5F0("HitByBullet", (type_67620 *)(vf_098()), 0, 0, 0, 0, 1, 0);
        var_4 = 0;
        sub_6B5F0("HitByBulletRWS", (type_67620 *)(vf_098()), 0, 0, &var_4, 1, 1, 0);
        sub_D2AD0(arg_0->unk_0C, arg_0->unk_04);
    }
    return 0;
}

// match: ?vf_090@type_3D51C0@@UAEPAUtype_6D380@@XZ @ 0x0009B6E0
type_6D380 *type_3D51C0::vf_090()
{
    return (type_6D380 *)sub_67620(unk_3D0);
}


// (Its scalar deleting destructor, compiler-written.)
































// (Its scalar deleting destructor, compiler-written.)

































// Trigger's own constant functions (slots 0x0C, 0x18, 0x1C and 0x24 of
// off_3D674C), which the image keeps after AddTaskTrigger's code.















// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.


// ??2type_3D5400@@SAPAXIPAX@Z (folded into 0x6CCF0)
void *type_3D5400::operator new(RwUInt32 arg_0, void *arg_4)
{
    return arg_4;
}

// ??2type_3D5658@@SAPAXIPAX@Z (folded into 0x6CCF0)
void *type_3D5658::operator new(RwUInt32 arg_0, void *arg_4)
{
    return arg_4;
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??3type_3D51C0@@SAXPAX@Z (folded into 0x19A750)
void type_3D51C0::operator delete(void * arg_0)
{
}

// ??3type_3D5400@@SAXPAX@Z (folded into 0x19A750)
void type_3D5400::operator delete(void * arg_0)
{
}

// ??3type_3D5658@@SAXPAX@Z (folded into 0x19A750)
void type_3D5658::operator delete(void * arg_0)
{
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??3type_3D51C0@@SAXPAX0@Z (folded into 0x19A750)
void type_3D51C0::operator delete(void * arg_0, void * arg_4)
{
}

// ??3type_3D5400@@SAXPAX0@Z (folded into 0x19A750)
void type_3D5400::operator delete(void * arg_0, void * arg_4)
{
}

// ??3type_3D5658@@SAXPAX0@Z (folded into 0x19A750)
void type_3D5658::operator delete(void * arg_0, void * arg_4)
{
}
