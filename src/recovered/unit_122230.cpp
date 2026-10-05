// Split from unit_11EE20.cpp at 0x122230, where the image starts another object (the
// projectile generators' list and triggers): its .rdata begins at 0x3DA744 with its own
// 16.666666, the unreferenced constant every game object starts its constants with (PLAN M7).

#include <math.h>
#include <string.h>
#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "rw/bamatrix.h"
#include "rw/bavector.h"
#include "rw/baframe.h"
#include "rw/rprandom.h"
#include "types/type_1227C0.h"
#include "types/ProjectileGeneratorTrigger.h"
#include "types/type_3D3548.h"
#include "types/type_F2FF0.h"
#include "types/SplinePath.h"
#include "types/AIData.h"
#include "game/functions.h"
#include "game/clumpdata.h"
#include "game/data.h"
#include "game/frand.h"
#include "types/CGlobalSounds.h"
#include "types/type_10F710.h"
#include "types/alfasched.h"
#include "game/pooledconsts.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003DA744
extern const RwReal flt_3DA744 = 16.666666f;

// match: ?flt_3DA744@@3MB @ 0x003DA744


// match: __ehhandler$?sub_1224F0@@YAHPAVProjectileGeneratorTrigger@@@Z>1>8 @ 0x0041D4B0
// match: __ehhandler$?sub_1224F0@@YAHPAVProjectileGeneratorTrigger@@@Z>1 @ 0x0041D4B8
// match: __ehhandler$?sub_122410@@YAHPAVProjectileGeneratorTrigger@@@Z>1>8 @ 0x0041D4D4
// match: __ehhandler$?sub_122410@@YAHPAVProjectileGeneratorTrigger@@@Z>1 @ 0x0041D4DC
// match: ??_C@_0BE@KEBPELHC@m_freeGeneratorList?$AA@ @ 0x003DA748
// match: ??_C@_0BP@MINIHGIG@StopProjectileGeneratorForever?$AA@ @ 0x003DA75C

// match: ?sub_122230@@YAXXZ @ 0x00122230
// Sets up the pool, sized for the larger kind, the list and the id table.
void sub_122230()
{
    if (sizeof(type_11DB10) >= sizeof(type_11E440))
    {
        dword_4CEA48.sub_16C2C0(0x28, sizeof(type_11DB10), "m_freeGeneratorList", 0x10, 0);
    }
    else
    {
        dword_4CEA48.sub_16C2C0(0x28, sizeof(type_11E440), "m_freeGeneratorList", 0x10, 0);
    }
    dword_4CE8F8 = 0;
    memset(dword_4CE900, 0, sizeof(dword_4CE900));
    dword_4CE8F0 = 0;
}
// match: ?sub_1222A0@@YAXXZ @ 0x001222A0
void sub_1222A0()
{
    sub_122680();
    memset(dword_4CE900, 0, sizeof(dword_4CE900));
    dword_4CE8F0 = 0;
}
// match: ?sub_1222D0@@YAXXZ @ 0x001222D0
void sub_1222D0()
{
    sub_122680();
    dword_4CEA48.sub_16C4D0(1);
}
// match: ?sub_1222F0@@YAXM@Z @ 0x001222F0
// Updates each generator whose parent, turret and barrel still stand; one
// that lost them tells its script ("StopProjectileGeneratorForever"), or is
// destroyed without one.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_1222F0(RwReal arg_0)
{
    type_1227C0 *var_4;
    type_1227C0 *v8;
    ProjectileGeneratorTrigger *stk_C;
    RwInt32 var_10;

    v8 = dword_4CE8F8;
    while (v8)
    {
        var_4 = v8->unk_100;
        if (v8->unk_14 == 1)
        {
            v8->unk_14 = 2;
        }
        if (v8->sub_11F8E0())
        {
            v8->vf_010(arg_0);
        }
        else
        {
            stk_C = v8->get_trigger();
            if (stk_C && stk_C->sub_BDF50())
            {
                sub_6B5F0("StopProjectileGeneratorForever", (type_67620 *)(stk_C->sub_BDF50()), 0, 0, &var_10, 1, 1, 0);
            }
            else
            {
                sub_1225D0(v8);
            }
        }
        v8 = var_4;
    }
}
// match: ?sub_1223B0@@YAHPAUtype_712B0@@@Z @ 0x001223B0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_1223B0(type_712B0 *arg_0)
{
    RwInt32 var_4;
    RwInt32 v8;
    RwInt32 varC;

    switch (((ProjectileGeneratorTrigger *)arg_0)->unk_E0)
    {
    case 0:
        v8 = sub_122410((ProjectileGeneratorTrigger *)arg_0);
        return v8;
    case 1:
        varC = sub_1224F0((ProjectileGeneratorTrigger *)arg_0);
        return varC;
    }
    var_4 = 0;
    return var_4;
}
// The list's head through a local of its own: an inline with no address
// and so no database name, named for what it returns. Evidence: the
// factories read dword_4CE8F8 into a temporary before linking it.
inline type_1227C0 *get_generator_list()
{
    type_1227C0 *head = dword_4CE8F8;
    return head;
}
// match: ?sub_122410@@YAHPAVProjectileGeneratorTrigger@@@Z @ 0x00122410
// match: __ehhandler$?sub_122410@@YAHPAVProjectileGeneratorTrigger@@@Z-0x11 @ 0x00301560
// match: __ehhandler$?sub_122410@@YAHPAVProjectileGeneratorTrigger@@@Z @ 0x00301571
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Creates a bullets' generator for the trigger arg_0 in the pool, links it
// and gives it an id, which it returns.
RwInt32 sub_122410(ProjectileGeneratorTrigger *arg_0)
{
    RwInt32 var_18;
    type_1227C0 *var_14;
    void *lv_10;

    lv_10 = dword_4CEA48.sub_16C5A0(0);
    var_14 = new (lv_10) type_11DB10;
    var_14->vf_004(arg_0);
    var_14->unk_100 = get_generator_list();
    dword_4CE8F8 = var_14;
    var_18 = sub_1226D0(var_14);
    var_14->sub_121B30(var_18);
    return var_14->get_unk_104_h().unk_00;
}
// match: ?sub_1224F0@@YAHPAVProjectileGeneratorTrigger@@@Z @ 0x001224F0
// Likewise a shells' generator (its unwinding is sub_122410's, identical,
// folded by /OPT:ICF).
RwInt32 sub_1224F0(ProjectileGeneratorTrigger *arg_0)
{
    RwInt32 var_18;
    type_1227C0 *var_14;
    void *lv_10;

    lv_10 = dword_4CEA48.sub_16C5A0(0);
    var_14 = new (lv_10) type_11E440;
    var_14->vf_004(arg_0);
    var_14->unk_100 = get_generator_list();
    dword_4CE8F8 = var_14;
    var_18 = sub_1226D0(var_14);
    var_14->sub_121B30(var_18);
    return var_14->get_unk_104_h().unk_00;
}
// match: ?sub_1225D0@@YAXPAUtype_1227C0@@@Z @ 0x001225D0
// Destroys the generator arg_0: unlinks it, frees its id, stops it and
// returns it to the pool.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_1225D0(type_1227C0 *arg_0)
{
    type_1227C0 *var_4;
    RwInt32 local_8;

    for (var_4 = dword_4CE8F8; var_4; var_4 = var_4->unk_100)
    {
        if (var_4->get_unk_100() == arg_0)
        {
            break;
        }
    }
    if (var_4)
    {
        var_4->unk_100 = arg_0->get_unk_100();
    }
    else
    {
        dword_4CE8F8 = arg_0->get_unk_100();
    }
    local_8 = arg_0->unk_104;
    sub_122790(local_8);
    arg_0->vf_008();
    dword_4CEA48.sub_16C710(arg_0);
}
// match: ?sub_122680@@YAXXZ @ 0x00122680
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_122680()
{
    type_1227C0 *var_4;
    type_1227C0 *local_8;

    var_4 = dword_4CE8F8;
    local_8 = 0;
    while (var_4)
    {
        local_8 = var_4->unk_100;
        sub_1225D0(var_4);
        var_4 = local_8;
    }
    dword_4CE8F8 = 0;
}
// match: ?sub_1226D0@@YAHPAUtype_1227C0@@@Z @ 0x001226D0
// Gives arg_0 the first free entry of the id table (from 1) with the next
// serial (from 1); its id, or garbage when the table is full.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_1226D0(type_1227C0 *arg_0)
{
    RwInt32 var_4;
    type_4CE900_00 v8;
    RwInt32 varC;

    var_4 = 0;
    for (varC = 1; varC < 41; varC++)
    {
        if (dword_4CE900[varC].unk_00 == 0 && dword_4CE900[varC].unk_04 == 0)
        {
            if (dword_4CE8F0 == 0)
            {
                dword_4CE8F0 = 1;
            }
            dword_4CE900[varC].unk_00_w = varC;
            v8.unk_00_w = varC;
            dword_4CE900[varC].unk_02_w = dword_4CE8F0;
            v8.unk_02_w = dword_4CE8F0;
            dword_4CE900[v8.unk_00_w].unk_04 = arg_0;
            var_4 = 1;
            dword_4CE8F0++;
            break;
        }
    }
    return v8.unk_00;
}
// match: ?sub_122790@@YAXH@Z @ 0x00122790
void sub_122790(RwInt32 arg_0)
{
    dword_4CE900[(RwUInt16)arg_0].unk_00 = 0;
    dword_4CE900[(RwUInt16)arg_0].unk_04 = 0;
}
// match: ?sub_1227C0@@YAPAUtype_1227C0@@H@Z @ 0x001227C0
// The generator with the id arg_0, or 0 when its entry holds another id.
type_1227C0 *sub_1227C0(RwInt32 arg_0)
{
    if (dword_4CE900[(RwUInt16)arg_0].unk_00 == arg_0)
    {
        return dword_4CE900[(RwUInt16)arg_0].unk_04;
    }
    return 0;
}
