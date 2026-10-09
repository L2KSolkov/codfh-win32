// The RenderWare object holders (types/type_129_base.h): holding an atomic,
// clump, frame or light, handing an entity to what they hold, and releasing
// it, destroying it once no holder is left. The original file name is not
// in the image, so it is named for its start address.

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "rw/bamatrix.h"
#include "rw/baframe.h"
#include "rw/rpatomic.h"
#include "rw/rplight.h"
#include "rw/rpworld.h"
#include "rws/framehelper.h"
#include "types/type_129_base.h"
#include "types/type_3D96F0.h"
#include "types/type_3D3548.h"
#include "game/functions.h"

RwFrame *sub_129730(RwFrame *arg_0, void *arg_4);

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0DM@CHALABKL@Warning?$CB?5Cannot?5delete?5atomic?5?9?5@ @ 0x003DA860
// match: ??_C@_0DL@MGAINJOM@Warning?$CB?5Cannot?5delete?5clump?5?9?5s@ @ 0x003DA89C
// match: ??_C@_0DN@MCBAILDB@Warning?$CB?5Cannot?5delete?5RwFrame?5?9@ @ 0x003DA8D8
// match: ??_C@_0DL@FNBMHNBL@Warning?$CB?5Cannot?5delete?5light?5?9?5s@ @ 0x003DA918

// match: ?sub_129430@type_1294D0@@QAEXPAURpAtomic@@@Z @ 0x00129430
// sp-match: ?sub_129430@type_1294D0@@QAEXPAURpAtomic@@@Z @ 0x000DDAB0

// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_1294D0::sub_129430(RpAtomic *arg_0)
{
    type_3D96F0 *var_C;
    type_3D96F0 *bp_8;
    RpAtomic *bp_4;

    bp_4 = unk_08;
    if (bp_4)
    {
        if (bp_4 == arg_0)
        {
            return;
        }
        bp_8 = sub_FB7A0(bp_4);
        bp_8->sub_FC3B0((type_3D96F0_node *)this);
    }
    if (arg_0)
    {
        var_C = sub_FB7A0(arg_0);
        var_C->sub_FC360((type_3D96F0_node *)this);
    }
    unk_08 = arg_0;
}

// match: ?sub_1294A0@type_1294D0@@QAEXPAUtype_3D3548@@@Z @ 0x001294A0
// sp-match: ?sub_1294A0@type_1294D0@@QAEXPAUtype_3D3548@@@Z @ 0x000DDBE0
void type_1294D0::sub_1294A0(type_3D3548 *arg_0)
{
    RpAtomic *var_4;

    var_4 = unk_08;
    if (var_4)
    {
        sub_1295E0(var_4, arg_0);
    }
}

// match: ?sub_1294D0@type_1294D0@@QAEHXZ @ 0x001294D0
// sp-match: ?sub_1294D0@type_1294D0@@QAEHXZ @ 0x000DDB00
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Releases the atomic, destroying it (and its frame) if no holder is left.
RwBool type_1294D0::sub_1294D0()
{
    RpClump *var_18;
    RpWorld *var_14;
    RwFrame *lv_10;
    type_3D96F0 *var_C;
    RpAtomic *bp_8;
    RwBool bp_4;

    bp_4 = 1;
    if (unk_08)
    {
        bp_8 = unk_08;
        var_C = sub_FB7A0(bp_8);
        var_C->sub_FC3B0((type_3D96F0_node *)this);
        if (!var_C->get_unk_18())
        {
            lv_10 = RpAtomicGetFrame(bp_8);
            if (lv_10)
            {
                RwFrameForAllChildren(lv_10, RWS::FrameHelper::RemoveChildFrame, 0);
                if (rwObjectGetParent(lv_10))
                {
                    RwFrameRemoveChild(lv_10);
                }
                RpAtomicSetFrame(bp_8, 0);
                RWS::FrameHelper::FrameDestroy(lv_10);
            }
            var_18 = bp_8->clump;
            if (var_18)
            {
                RpClumpRemoveAtomic(var_18, bp_8);
            }
            var_14 = RpAtomicGetWorld(bp_8);
            if (var_14)
            {
                RpWorldRemoveAtomic(var_14, bp_8);
            }
            bp_4 = RpAtomicDestroy(bp_8);
        }
#ifndef CODFH_SP
        // Single player compiles the debug print out (SP 0xDDB00).
        else
        {
            sub_19A750("Warning! Cannot delete atomic - somebody is pointing at it!");
        }
#endif
    }
    return bp_4;
}

// match: ?sub_1295E0@type_1294D0@@QAEXPAURpAtomic@@PAUtype_3D3548@@@Z @ 0x001295E0
// sp-match: ?sub_1295E0@type_1294D0@@QAEXPAURpAtomic@@PAUtype_3D3548@@@Z @ 0x000DDBB0
void type_1294D0::sub_1295E0(RpAtomic *arg_0, type_3D3548 *arg_4)
{
    RwFrame *var_4;

    sub_FB910(arg_0, arg_4);
    var_4 = RpAtomicGetFrame(arg_0);
    if (var_4)
    {
        sub_FBD80(var_4, arg_4);
    }
}

// match: ?sub_129620@type_129940@@QAEXPAURpClump@@@Z @ 0x00129620
// sp-match: ?sub_129620@type_129940@@QAEXPAURpClump@@@Z @ 0x000DDC00
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_129940::sub_129620(RpClump *arg_0)
{
    type_3D96F0 *var_C;
    type_3D96F0 *bp_8;
    RpClump *bp_4;

    bp_4 = unk_08;
    if (bp_4)
    {
        if (bp_4 == arg_0)
        {
            return;
        }
        bp_8 = sub_FBA10(bp_4);
        bp_8->sub_FC3B0((type_3D96F0_node *)this);
    }
    if (arg_0)
    {
        var_C = sub_FBA10(arg_0);
        var_C->sub_FC360((type_3D96F0_node *)this);
    }
    unk_08 = arg_0;
}

// match: ?sub_129690@type_129940@@QAEXPAUtype_3D3548@@@Z @ 0x00129690
// sp-match: ?sub_129690@type_129940@@QAEXPAUtype_3D3548@@@Z @ 0x000DDF00
void type_129940::sub_129690(type_3D3548 *arg_0)
{
    RpClump *var_4;

    var_4 = unk_08;
    if (var_4)
    {
        sub_129750(var_4, arg_0);
    }
}

// match: ?sub_1296C0@@YAPAURpAtomic@@PAU1@PAX@Z @ 0x001296C0
// sp-match: ?sub_1296C0@@YAPAURpAtomic@@PAU1@PAX@Z @ 0x000DDE60
RpAtomic *sub_1296C0(RpAtomic *arg_0, void *arg_4)
{
    RwFrame *var_4;

    sub_FB910(arg_0, (type_3D3548 *)arg_4);
    var_4 = RpAtomicGetFrame(arg_0);
    if (var_4)
    {
        RwFrameForAllChildren(var_4, sub_129730, arg_4);
        sub_FBD80(var_4, (type_3D3548 *)arg_4);
    }
    return arg_0;
}

// match: ?sub_129710@@YAPAURpLight@@PAU1@PAX@Z @ 0x00129710
// sp-match: ?sub_129710@@YAPAURpLight@@PAU1@PAX@Z @ 0x000DDC50
RpLight *sub_129710(RpLight *arg_0, void *arg_4)
{
    sub_FBF20(arg_0, (type_3D3548 *)arg_4);
    return arg_0;
}

// match: ?sub_129730@@YAPAURwFrame@@PAU1@PAX@Z @ 0x00129730
// sp-match: ?sub_129730@@YAPAURwFrame@@PAU1@PAX@Z @ 0x000DDC70
RwFrame *sub_129730(RwFrame *arg_0, void *arg_4)
{
    sub_FBD80(arg_0, (type_3D3548 *)arg_4);
    return arg_0;
}

// match: ?sub_129750@type_129940@@QAEXPAURpClump@@PAUtype_3D3548@@@Z @ 0x00129750
// sp-match: ?sub_129750@type_129940@@QAEXPAURpClump@@PAUtype_3D3548@@@Z @ 0x000DDEA0
void type_129940::sub_129750(RpClump *arg_0, type_3D3548 *arg_4)
{
    RwFrame *var_4;

    RpClumpForAllAtomics(arg_0, sub_1296C0, arg_4);
    RpClumpForAllLights(arg_0, sub_129710, arg_4);
    var_4 = RpClumpGetFrame(arg_0);
    if (var_4)
    {
        RwFrameForAllChildren(var_4, sub_129730, arg_4);
        sub_FBD80(var_4, arg_4);
    }
    sub_FBB60(arg_0, arg_4);
}

// match: ?sub_1297D0@@YAPAURpAtomic@@PAU1@PAX@Z @ 0x001297D0
// sp-match: ?sub_1297D0@@YAPAURpAtomic@@PAU1@PAX@Z @ 0x000DDC90
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The clump's release: an atomic of its entity leaves the world, another
// only the clump.
RpAtomic *sub_1297D0(RpAtomic *arg_0, void *arg_4)
{
    RpWorld *var_10;
    type_3D96F0 *var_C;
    type_3D3548 *bp_8;
    type_129940_data *bp_4;

    bp_4 = (type_129940_data *)arg_4;
    var_C = sub_FB7A0(arg_0);
    bp_8 = var_C->unk_14.sub_D4910();
    if (bp_8 != bp_4->unk_04)
    {
        RpClumpRemoveAtomic(bp_4->unk_00, arg_0);
    }
    else
    {
        var_10 = RpAtomicGetWorld(arg_0);
        if (var_10)
        {
            RpWorldRemoveAtomic(var_10, arg_0);
        }
    }
    return arg_0;
}

// match: ?sub_129850@@YAPAURpLight@@PAU1@PAX@Z @ 0x00129850
// sp-match: ?sub_129850@@YAPAURpLight@@PAU1@PAX@Z @ 0x000DDCE0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RpLight *sub_129850(RpLight *arg_0, void *arg_4)
{
    RpWorld *var_10;
    type_3D96F0 *var_C;
    type_3D3548 *bp_8;
    type_129940_data *bp_4;

    bp_4 = (type_129940_data *)arg_4;
    var_C = sub_FBDD0(arg_0);
    bp_8 = var_C->unk_14.sub_D4910();
    if (bp_8 != bp_4->unk_04)
    {
        RpClumpRemoveLight(bp_4->unk_00, arg_0);
    }
    else
    {
        var_10 = RpLightGetWorld(arg_0);
        if (var_10)
        {
            RpWorldRemoveLight(var_10, arg_0);
        }
    }
    return arg_0;
}

// match: ?sub_1298D0@@YAPAURwFrame@@PAU1@PAX@Z @ 0x001298D0
// sp-match: ?sub_1298D0@@YAPAURwFrame@@PAU1@PAX@Z @ 0x000DDD30
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// A frame of another entity keeps where it is and leaves the clump's.
RwFrame *sub_1298D0(RwFrame *arg_0, void *arg_4)
{
    type_3D96F0 *var_C;
    type_3D3548 *bp_8;
    type_129940_data *bp_4;

    bp_4 = (type_129940_data *)arg_4;
    var_C = sub_FBC30(arg_0);
    bp_8 = var_C->unk_14.sub_D4910();
    if (bp_8 != bp_4->unk_04)
    {
        arg_0->modelling = *RwFrameGetLTM(arg_0);
        RwFrameRemoveChild(arg_0);
    }
    return arg_0;
}

// match: ?sub_129940@type_129940@@QAEHH@Z @ 0x00129940
// sp-match: ?sub_129940@type_129940@@QAEHH@Z @ 0x000DDD80
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwBool type_129940::sub_129940(RwInt32 arg_0)
{
    type_3D3548 *var_20;
    type_129940_data l1C;
    RpWorld *ebp_14;
    RwFrame *lv_10;
    type_3D96F0 *var_C;
    RpClump *bp_8;
    RwBool bp_4;

    bp_4 = 1;
    if (unk_08)
    {
        bp_8 = unk_08;
        var_C = sub_FBA10(bp_8);
        var_C->sub_FC3B0((type_3D96F0_node *)this);
#ifdef CODFH_SP
        // shape: the print's branch kept as an empty if (SP 0xDDE51 lays that return out last).
        if (var_C->get_unk_18() && !arg_0)
        {
        }
        else
#else
        if (!var_C->get_unk_18() || arg_0)
#endif
        {
            var_20 = var_C->unk_14.sub_D4910();
            l1C.unk_00 = bp_8;
            l1C.unk_04 = var_20;
            RpClumpForAllAtomics(bp_8, sub_1297D0, &l1C);
            RpClumpForAllLights(bp_8, sub_129850, &l1C);
            lv_10 = RpClumpGetFrame(bp_8);
            if (lv_10)
            {
                RwFrameForAllChildren(lv_10, sub_1298D0, &l1C);
                if (rwObjectGetParent(lv_10))
                {
                    RwFrameRemoveChild(lv_10);
                }
            }
            ebp_14 = RpClumpGetWorld(bp_8);
            if (ebp_14)
            {
                RpWorldRemoveClump(ebp_14, bp_8);
            }
            bp_4 = RpClumpDestroy(bp_8);
        }
#ifndef CODFH_SP
        // Single player compiles the debug print out (SP 0xDDD80).
        else
        {
            sub_19A750("Warning! Cannot delete clump - somebody is pointing at it!");
        }
#endif
    }
    return bp_4;
}

// match: ?sub_129A70@type_129B10@@QAEXPAURwFrame@@@Z @ 0x00129A70
// sp-match: ?sub_129A70@type_129B10@@QAEXPAURwFrame@@@Z @ 0x000DDF20
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_129B10::sub_129A70(RwFrame *arg_0)
{
    type_3D96F0 *var_C;
    type_3D96F0 *bp_8;
    RwFrame *bp_4;

    bp_4 = unk_08;
    if (bp_4)
    {
        if (bp_4 == arg_0)
        {
            return;
        }
        bp_8 = sub_FBC30(bp_4);
        bp_8->sub_FC3B0((type_3D96F0_node *)this);
    }
    if (arg_0)
    {
        var_C = sub_FBC30(arg_0);
        var_C->sub_FC360((type_3D96F0_node *)this);
    }
    unk_08 = arg_0;
}

// match: ?sub_129AE0@type_129B10@@QAEXPAUtype_3D3548@@@Z @ 0x00129AE0
// sp-match: ?sub_129AE0@type_129B10@@QAEXPAUtype_3D3548@@@Z @ 0x000DDFF0
void type_129B10::sub_129AE0(type_3D3548 *arg_0)
{
    RwFrame *var_4;

    var_4 = unk_08;
    if (var_4)
    {
        sub_129BB0(var_4, arg_0);
    }
}

// match: ?sub_129B10@type_129B10@@QAEHXZ @ 0x00129B10
// sp-match: ?sub_129B10@type_129B10@@QAEHXZ @ 0x000DDF70
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_129B10::sub_129B10()
{
    RwFrame *var_10;
    type_3D96F0 *var_C;
    RwFrame *bp_8;
    RwInt32 bp_4;

    bp_4 = 1;
    if (unk_08)
    {
        bp_8 = unk_08;
        var_C = sub_FBC30(bp_8);
        var_C->sub_FC3B0((type_3D96F0_node *)this);
        if (!var_C->get_unk_18())
        {
            RwFrameForAllChildren(bp_8, RWS::FrameHelper::RemoveChildFrame, 0);
            var_10 = RwFrameGetParent(bp_8);
            if (var_10)
            {
                RwFrameRemoveChild(bp_8);
            }
            bp_4 = RWS::FrameHelper::FrameDestroy(bp_8);
        }
#ifndef CODFH_SP
        // Single player compiles the debug print out (SP 0xDDF70).
        else
        {
            sub_19A750("Warning! Cannot delete RwFrame - somebody is pointing at it!");
        }
#endif
    }
    return bp_4;
}

// match: ?sub_129BB0@type_129B10@@QAEXPAURwFrame@@PAUtype_3D3548@@@Z @ 0x00129BB0
// sp-match: ?sub_129BB0@type_129B10@@QAEXPAURwFrame@@PAUtype_3D3548@@@Z @ 0x000DDFD0
void type_129B10::sub_129BB0(RwFrame *arg_0, type_3D3548 *arg_4)
{
    sub_FBD80(arg_0, arg_4);
}

// match: ?sub_129BD0@type_129BD0@@QAEXPAURpLight@@@Z @ 0x00129BD0
// sp-match: ?sub_129BD0@type_129BD0@@QAEXPAURpLight@@@Z @ 0x000DE010
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_129BD0::sub_129BD0(RpLight *arg_0)
{
    type_3D96F0 *var_C;
    type_3D96F0 *bp_8;
    RpLight *bp_4;

    bp_4 = unk_08;
    if (bp_4)
    {
        if (bp_4 == arg_0)
        {
            return;
        }
        bp_8 = sub_FBDD0(bp_4);
        bp_8->sub_FC3B0((type_3D96F0_node *)this);
    }
    if (arg_0)
    {
        var_C = sub_FBDD0(arg_0);
        var_C->sub_FC360((type_3D96F0_node *)this);
    }
    unk_08 = arg_0;
}

// match: ?sub_129C40@type_129BD0@@QAEHXZ @ 0x00129C40
// sp-match: ?sub_129C40@type_129BD0@@QAEHXZ @ 0x000DE060
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwBool type_129BD0::sub_129C40()
{
    RpClump *var_18;
    RpWorld *var_14;
    RwFrame *lv_10;
    type_3D96F0 *var_C;
    RpLight *bp_8;
    RwBool bp_4;

    bp_4 = 1;
    if (unk_08)
    {
        bp_8 = unk_08;
        var_C = sub_FBDD0(bp_8);
        var_C->sub_FC3B0((type_3D96F0_node *)this);
        if (!var_C->get_unk_18())
        {
            lv_10 = RpLightGetFrame(bp_8);
            if (lv_10)
            {
                RwFrameForAllChildren(lv_10, RWS::FrameHelper::RemoveChildFrame, 0);
                if (rwObjectGetParent(lv_10))
                {
                    RwFrameRemoveChild(lv_10);
                }
                RpLightSetFrame(bp_8, 0);
                RWS::FrameHelper::FrameDestroy(lv_10);
            }
            var_18 = RpLightGetClump(bp_8);
            if (var_18)
            {
                RpClumpRemoveLight(var_18, bp_8);
            }
            var_14 = RpLightGetWorld(bp_8);
            if (var_14)
            {
                RpWorldRemoveLight(var_14, bp_8);
            }
            bp_4 = RpLightDestroy(bp_8);
        }
#ifndef CODFH_SP
        // Single player compiles the debug print out (SP 0xDE060).
        else
        {
            sub_19A750("Warning! Cannot delete light - somebody is pointing at it!");
        }
#endif
    }
    return bp_4;
}
