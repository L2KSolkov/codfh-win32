// The clump utilities (game/clumputil.h).

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "rw/baframe.h"
#include "rw/bamatrix.h"
#include "rw/rpatomic.h"
#include "rw/rphanim.h"
#include "game/clumputil.h"
#include "game/functions.h"
#include "rw/bavector.h"
#include "rw/rpmesh.h"
#include "rw/rpusrdat.h"
#include "types/type_92430.h"
#include "types/animobjpool.h"
#include "rw/rpworld.h"
#include "rw/rplight.h"
#include "rw/batextur.h"
#include <string.h>
#include <stdio.h>
#include "rws/csystemcommands.h"

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0BG@GBNNNFN@World?5has?5?$CFd?5Lights?4?5?$AA@ @ 0x003DCEFC
// match: ??_C@_0BG@MEEIKGHM@World?5has?5?$CFd?5Clumps?4?5?$AA@ @ 0x003DCF14
// match: ??_C@_0BH@EFKFHCAA@World?5has?5?$CFd?5Atomics?4?5?$AA@ @ 0x003DCF2C
// match: ??_C@_0DO@PNEMFKEB@Warning?3?5Texture?5cannot?5be?5delet@ @ 0x003DCF44
// match: ??_C@_0FC@HJOJEHHB@Warning?3?5Texture?5dictionary?5has?5@ @ 0x003DCF88

#ifdef CODFH_SP
// sp-match: ?sp_sub_10B070@@YA_NPAURwFrame@@0@Z @ 0x0010B070
// Single player only (SP 0x10B070, called from sub_948A0's SP 0x77DEB): whether
// arg_0 is one of arg_4's ancestors (stopping at a frame that is its own parent).
bool sp_sub_10B070(RwFrame *arg_0, RwFrame *arg_4)
{
    RwFrame *parent;

    for (parent = RwFrameGetParent(arg_4); parent; parent = RwFrameGetParent(parent))
    {
        if (arg_4 == parent)
            break;
        if (arg_0 == parent)
            return true;
        arg_4 = parent;
    }
    return false;
}
#endif

// match: ?sub_16D8C0@@YA_NPAURpClump@@PBD_N@Z @ 0x0016D8C0
// sp-match: ?sub_16D8C0@@YA_NPAURpClump@@PBD_N@Z @ 0x0010B860

bool sub_16D8C0(RpClump *arg_0, const RwChar *arg_4, bool arg_8)
{
    bool var_1;
    type_16E450 var_10;

    var_1 = false;
    var_10.unk_00 = arg_4;
    var_10.unk_04 = &arg_8;
    var_10.unk_08 = &var_1;
    RpClumpForAllAtomics(arg_0, sub_16E450, &var_10);
    return var_1;
}

// match: ?sub_16D900@@YAHPAURpClump@@PBD@Z @ 0x0016D900
// sp-match: ?sub_16D900@@YAHPAURpClump@@PBD@Z @ 0x0010B8A0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The atomic of the clump arg_0 named arg_4 (as its first word), or 0.
RwInt32 sub_16D900(RpClump *arg_0, const RwChar *arg_4)
{
    type_16E500 var_C;
    RwInt32 bp_4;

    bp_4 = 0;
    var_C.unk_00 = arg_4;
    var_C.unk_04 = &bp_4;
    RpClumpForAllAtomics(arg_0, sub_16E500, &var_C);
    return bp_4;
}

// match: ?sub_16D940@@YAPAURwFrame@@PAU1@H@Z @ 0x0016D940
// sp-match: ?sub_16D940@@YAPAURwFrame@@PAU1@H@Z @ 0x0010B8E0
RwFrame *sub_16D940(RwFrame *arg_0, RwInt32 arg_4)
{
    type_16DAB0 var_8;

    var_8.unk_00 = &arg_4;
    var_8.unk_04 = 0;
    RwFrameForAllChildren(arg_0, sub_16DAB0, &var_8);
    return var_8.unk_04;
}

// match: ?sub_16D970@@YAPAURpHAnimHierarchy@@PAURpClump@@@Z @ 0x0016D970
// sp-match: ?sub_16D970@@YAPAURpHAnimHierarchy@@PAURpClump@@@Z @ 0x0010B910
RpHAnimHierarchy *sub_16D970(RpClump *arg_0)
{
    RpHAnimHierarchy *var_4;

    var_4 = 0;
    GetHierarchyFrameRecurse(RpClumpGetFrame(arg_0), &var_4);
    return var_4;
}

// match: ?sub_16D9A0@@YAXPAURpClump@@@Z @ 0x0016D9A0
// sp-match: ?sub_16D9A0@@YAXPAURpClump@@@Z @ 0x0010BB30
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The pruning to the kept ids (sub_16DB20) is compiled out (`if (0)`);
// what runs detaches the hierarchy's frame, empties the clump frame's
// children of their atomics and frames, and puts the hierarchy's frame
// back.
void sub_16D9A0(RpClump *arg_0)
{
    RwFrame *var_10;
    RpHAnimHierarchy *var_C;
    RwFrame *bp_8;
    RwInt32 bp_4;

    var_10 = RpClumpGetFrame(arg_0);
    var_C = sub_16D970(arg_0);
    bp_8 = 0;
    bp_4 = sub_EC290(arg_0);
    if (0)
    {
        RwInt32 *v14;
        RwInt8 var_15;
        RwInt8 m_16;
        type_16DB20 var_2C;

        m_16 = -1;
        var_15 = 0;
        v14 = sub_EC2B0(arg_0);
        var_2C.unk_00 = var_10;
        var_2C.unk_04 = &bp_4;
        var_2C.unk_08 = v14;
        var_2C.unk_0C = &var_15;
        var_2C.unk_10 = &m_16;
        RwFrameForAllChildren(var_10, sub_16DB20, &var_2C);
        if (var_C)
            RpHAnimFrameSetHierarchy(var_10, var_C);
    }
    else
    {
        if (var_C)
        {
            bp_8 = var_C->parentFrame;
            RwFrameSetIdentity(bp_8);
            RwFrameRemoveChild(bp_8);
            RwFrameForAllChildren(bp_8, sub_16DC20, bp_8);
        }
        RwFrameForAllChildren(var_10, sub_16DC20, var_10);
        if (var_C)
            RwFrameAddChild(var_10, bp_8);
    }
}

// match: ?sub_16DAB0@@YAPAURwFrame@@PAU1@PAX@Z @ 0x0016DAB0
// sp-match: ?sub_16DAB0@@YAPAURwFrame@@PAU1@PAX@Z @ 0x0010B0A0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwFrame *sub_16DAB0(RwFrame *arg_0, void *arg_4)
{
    RwInt32 var_C;
    RwInt32 *bp_8;
    type_16DAB0 *bp_4;

    bp_4 = (type_16DAB0 *)arg_4;
    bp_8 = bp_4->unk_00;
    if (bp_4->unk_04)
        return arg_0;
    var_C = RpHAnimFrameGetID(arg_0);
    if (var_C == *bp_8)
    {
        bp_4->unk_04 = arg_0;
        return arg_0;
    }
    RwFrameForAllChildren(arg_0, sub_16DAB0, arg_4);
    return arg_0;
}

// match: ?sub_16DB20@@YAPAURwFrame@@PAU1@PAX@Z @ 0x0016DB20
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Destroys the frames (their atomics moved to the clump's frame) that are
// not kept and hold no kept frame below them.
RwFrame *sub_16DB20(RwFrame *arg_0, void *arg_4)
{
    RwInt32 var_24;
    RwInt32 var_20;
    RwInt8 *l1C;
    bool x15;
    RwFrame *ebp_14;
    RwInt32 *lv_10;
    type_16DB20 *var_C;
    RwInt32 *bp_8;
    RwInt8 *bp_4;

    var_C = (type_16DB20 *)arg_4;
    ebp_14 = var_C->unk_00;
    lv_10 = var_C->unk_04;
    bp_8 = var_C->unk_08;
    bp_4 = var_C->unk_0C;
    l1C = var_C->unk_10;
    x15 = false;
    var_20 = RpHAnimFrameGetID(arg_0);
    for (var_24 = 0; var_24 < *lv_10; var_24++)
    {
        if (bp_8[var_24] == var_20)
            x15 = true;
    }
    (*bp_4)++;
    RwFrameForAllChildren(arg_0, sub_16DB20, arg_4);
    (*bp_4)--;
    if (!x15 && *l1C <= *bp_4)
    {
        RwFrameForAllObjects(arg_0, sub_16DC70, ebp_14);
        RwFrameDestroy(arg_0);
    }
    else
    {
        *l1C = *bp_4;
    }
    return arg_0;
}

// match: ?sub_16DC20@@YAPAURwFrame@@PAU1@PAX@Z @ 0x0016DC20
// sp-match: ?sub_16DC20@@YAPAURwFrame@@PAU1@PAX@Z @ 0x0010B940
// Destroys arg_0 and the frames below it, moving their atomics to the
// frame arg_4.
RwFrame *sub_16DC20(RwFrame *arg_0, void *arg_4)
{
    RwFrame *var_4;

    var_4 = (RwFrame *)arg_4;
    RwFrameForAllChildren(arg_0, sub_16DC20, var_4);
    RwFrameForAllObjects(arg_0, sub_16DC70, var_4);
    RwFrameDestroy(arg_0);
    return arg_0;
}

// match: ?sub_16DC70@@YAPAURwObject@@PAU1@PAX@Z @ 0x0016DC70
// sp-match: ?sub_16DC70@@YAPAURwObject@@PAU1@PAX@Z @ 0x0010B0F0
RwObject *sub_16DC70(RwObject *arg_0, void *arg_4)
{
    RwFrame *var_4;

    var_4 = (RwFrame *)arg_4;
    RpAtomicSetFrame((RpAtomic *)arg_0, var_4);
    return arg_0;
}

// match: ?Clump_FindFirstAtomic@@YAPAURpAtomic@@PAURpClump@@@Z @ 0x0016DCA0
// sp-match: ?Clump_FindFirstAtomic@@YAPAURpAtomic@@PAURpClump@@@Z @ 0x0010B970
RpAtomic *Clump_FindFirstAtomic(RpClump *arg_0)
{
    RpAtomic *var_4;

    var_4 = 0;
    RpClumpForAllAtomics(arg_0, Clump_CaptureFirstAtomic, &var_4);
    return var_4;
}

// match: ?sub_16DCD0@@YAXPAURpClump@@PAURwSphere@@@Z @ 0x0016DCD0
// sp-match: ?sub_16DCD0@@YAXPAURpClump@@PAURwSphere@@@Z @ 0x0010B9A0
void sub_16DCD0(RpClump *arg_0, RwSphere *arg_4)
{
    RpAtomic *var_4;
    RwMatrix var_50;

    arg_4->center.z = 0;
    arg_4->center.y = 0;
    arg_4->center.x = 0;
    arg_4->radius = -1.0f;
    RpClumpForAllAtomics(arg_0, sub_16DD80, arg_4);
    var_4 = Clump_FindFirstAtomic(arg_0);
    if (var_4)
    {
        RwMatrixInvert(&var_50, RwFrameGetLTM(RpAtomicGetFrame(var_4)));
        sub_1414C0(&arg_4->center, &arg_4->center, &var_50);
    }
}

// match: ?sub_16DD80@@YAPAURpAtomic@@PAU1@PAX@Z @ 0x0016DD80
// sp-match: ?sub_16DD80@@YAPAURpAtomic@@PAU1@PAX@Z @ 0x0010B110
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RpAtomic *sub_16DD80(RpAtomic *arg_0, void *arg_4)
{
    RwV3d v48;
    RwV3d var_3C;
    RwV3d var_30;
    RwV3d var_24;
    RwReal bp_18;
    RwSphere *var_14;
    RwSphere lv_10;

    var_14 = (RwSphere *)arg_4;
    lv_10 = *RpAtomicGetWorldBoundingSphere(arg_0);
    if (var_14->radius < 0.0f)
    {
        var_14->center = lv_10.center;
        var_14->radius = lv_10.radius;
    }
    else
    {
        RwV3dSubMacro(&var_3C, &var_14->center, &lv_10.center);
        bp_18 = RwV3dNormalize(&var_30, &var_3C);
        if (bp_18 < 0.0f)
            bp_18 = -bp_18;
        bp_18 = lv_10.radius + var_14->radius + bp_18;
        if (2.0f * var_14->radius > bp_18)
            return arg_0;
        if (2.0f * lv_10.radius > bp_18)
        {
            var_14->center = lv_10.center;
            var_14->radius = lv_10.radius;
            return arg_0;
        }
        RwV3dScaleMacro(&var_24, &var_30, lv_10.radius);
        RwV3dSubMacro(&var_24, &lv_10.center, &var_24);
        RwV3dScaleMacro(&v48, &var_30, var_14->radius);
        RwV3dAddMacro(&v48, &v48, &var_14->center);
        var_14->radius = bp_18 * 0.5f;
        RwV3dAddMacro(&var_14->center, &var_24, &v48);
        RwV3dScaleMacro(&var_14->center, &var_14->center, 0.5f);
    }
    return arg_0;
}

// match: ?sub_16DFA0@@YAXPAURpClump@@PAURwV3d@@M@Z @ 0x0016DFA0
// sp-match: ?sub_16DFA0@@YAXPAURpClump@@PAURwV3d@@M@Z @ 0x0010BA10
void sub_16DFA0(RpClump *arg_0, RwV3d *arg_4, RwReal arg_8)
{
    RwSphere var_10;

    var_10.center = *arg_4;
    var_10.radius = arg_8;
    RpClumpForAllAtomics(arg_0, sub_16E210, &var_10);
}

// match: ?sub_16DFE0@@YAXPAURpClump@@H@Z @ 0x0016DFE0
// sp-match: ?sub_16DFE0@@YAXPAURpClump@@H@Z @ 0x0010BA50
void sub_16DFE0(RpClump *arg_0, RwInt32 arg_4)
{
    sub_FBBE0(arg_0, arg_4);
    RpClumpForAllAtomics(arg_0, sub_16E010, (void *)arg_4);
}

// match: ?sub_16E010@@YAPAURpAtomic@@PAU1@PAX@Z @ 0x0016E010
// sp-match: ?sub_16E010@@YAPAURpAtomic@@PAU1@PAX@Z @ 0x0010B2B0
RpAtomic *sub_16E010(RpAtomic *arg_0, void *arg_4)
{
    RwInt32 var_4;

    var_4 = (RwInt32)arg_4;
    sub_FB990(arg_0, var_4);
    return arg_0;
}

// match: ?sub_16E040@@YAXPAURpClump@@@Z @ 0x0016E040
// sp-match: ?sub_16E040@@YAXPAURpClump@@@Z @ 0x0010B2D0
void sub_16E040(RpClump *arg_0)
{
    RwFrame *var_4;

    if (!arg_0)
        return;
    var_4 = RpClumpGetFrame(arg_0);
    if (var_4)
        RwFrameRemoveChild(var_4);
    RpClumpForAllAtomics(arg_0, sub_7C830, 0);
}

// match: ?sub_16E080@@YAXPAURpClump@@I@Z @ 0x0016E080
// sp-match: ?sub_16E080@@YAXPAURpClump@@I@Z @ 0x0010BA80
void sub_16E080(RpClump *arg_0, RwUInt32 arg_4)
{
    type_16E250 var_8;

    if (!arg_0)
        return;
    var_8.unk_00 = 0;
    var_8.unk_04 = arg_4;
    RpClumpForAllAtomics(arg_0, sub_16E250, &var_8);
}

// match: ?sub_16E0C0@@YAIPAURpClump@@@Z @ 0x0016E0C0
// sp-match: ?sub_16E0C0@@YAIPAURpClump@@@Z @ 0x0010BAC0
RwUInt32 sub_16E0C0(RpClump *arg_0)
{
    type_16E250 var_8;

    if (!arg_0)
        return 0xFFFFFFFF;
    var_8.unk_00 = 0;
    var_8.unk_04 = 0;
    RpClumpForAllAtomics(arg_0, sub_16E370, &var_8);
    return var_8.unk_04;
}

// match: ?sub_16E100@@YAXPAURpClump@@0@Z @ 0x0016E100
// sp-match: ?sub_16E100@@YAXPAURpClump@@0@Z @ 0x0010BBA0
void sub_16E100(RpClump *arg_0, RpClump *arg_4)
{
    RwFrame *var_4;

    var_4 = RpClumpGetFrame(arg_4);
    RpClumpForAllAtomics(arg_4, sub_16E140, arg_0);
    ((RwObject *)arg_4)->parent = 0;
    RwFrameDestroyHierarchy(var_4);
}

// match: ?sub_16E140@@YAPAURpAtomic@@PAU1@PAX@Z @ 0x0016E140
// sp-match: ?sub_16E140@@YAPAURpAtomic@@PAU1@PAX@Z @ 0x0010BB00
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RpAtomic *sub_16E140(RpAtomic *arg_0, void *arg_4)
{
    RwInt32 var_14;
    RwFrame *lv_10;
    RpClump *var_C;
    RwFrame *bp_8;
    RwFrame *bp_4;

    var_C = (RpClump *)arg_4;
    lv_10 = RpAtomicGetFrame(arg_0);
    var_14 = RpHAnimFrameGetID(lv_10);
    bp_4 = RpClumpGetFrame(var_C);
    bp_8 = sub_16D940(bp_4, var_14);
    RpAtomicSetFrame(arg_0, bp_8);
    return arg_0;
}

// match: ?GetHierarchyFrameRecurse@@YAPAURwFrame@@PAU1@PAX@Z @ 0x0016E1A0
// sp-match: ?GetHierarchyFrameRecurse@@YAPAURwFrame@@PAU1@PAX@Z @ 0x0010B300
// The database's name: finds the first frame below arg_0 with a
// hierarchy, into *arg_4.
RwFrame *GetHierarchyFrameRecurse(RwFrame *arg_0, void *arg_4)
{
    RpHAnimHierarchy *var_4;

    var_4 = *(RpHAnimHierarchy **)arg_4;
    var_4 = RpHAnimFrameGetHierarchy(arg_0);
    if (!var_4)
    {
        RwFrameForAllChildren(arg_0, GetHierarchyFrameRecurse, arg_4);
        return arg_0;
    }
    *(RpHAnimHierarchy **)arg_4 = var_4;
    return 0;
}

// match: ?Clump_CaptureFirstAtomic@@YAPAURpAtomic@@PAU1@PAX@Z @ 0x0016E1F0
// sp-match: ?Clump_CaptureFirstAtomic@@YAPAURpAtomic@@PAU1@PAX@Z @ 0x0010B340
RpAtomic *Clump_CaptureFirstAtomic(RpAtomic *arg_0, void *arg_4)
{
    RpAtomic **var_4;

    var_4 = (RpAtomic **)arg_4;
    *var_4 = arg_0;
    return 0;
}

// The texture dictionary's form (its first texture, through
// RwTexDictionaryForAllTextures: unit_0E8F40), the same body; defined here
// for the authentic link (PLAN M7).
// ?Clump_CaptureFirstAtomic@@YAPAURwTexture@@PAU1@PAX@Z (folded into 0x16E1F0)
RwTexture *Clump_CaptureFirstAtomic(RwTexture *arg_0, void *arg_4)
{
    RwTexture **var_4;

    var_4 = (RwTexture **)arg_4;
    *var_4 = arg_0;
    return 0;
}

// match: ?sub_16E210@@YAPAURpAtomic@@PAU1@PAX@Z @ 0x0016E210
// sp-match: ?sub_16E210@@YAPAURpAtomic@@PAU1@PAX@Z @ 0x0010B350
RpAtomic *sub_16E210(RpAtomic *arg_0, void *arg_4)
{
    RwSphere *var_4;

    var_4 = (RwSphere *)arg_4;
    arg_0->boundingSphere.center = var_4->center;
    arg_0->boundingSphere.radius = var_4->radius;
    return arg_0;
}

// match: ?sub_16E250@@YAPAURpAtomic@@PAU1@PAX@Z @ 0x0016E250
// sp-match: ?sub_16E250@@YAPAURpAtomic@@PAU1@PAX@Z @ 0x0010B380
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Shows the atomic when its material's game data forces it (with that
// data's mask) or its bit of the mask is set, else hides it.
RpAtomic *sub_16E250(RpAtomic *arg_0, void *arg_4)
{
    RpMesh *var_10;
    type_16E250 *var_C;
    type_FC000 *bp_8;
    RpGeometry *bp_4;

    var_C = (type_16E250 *)arg_4;
    bp_4 = arg_0->geometry;
    if (bp_4)
    {
        var_10 = rpMeshHeaderGetFirstMesh(bp_4->mesh);
        bp_8 = sub_FC000(var_10->material);
    }
    if (bp_4 && bp_8 && bp_8->unk_04)
    {
        sub_FB9F0(arg_0, var_C->unk_04);
        RwInt8 var_11 = ((RwObject *)arg_0)->flags;
        var_11 |= rpATOMICRENDER;
        RpAtomicSetFlags(arg_0, var_11);
        RWS::RpAtomicCollisionProperties::SetIsSolid(*arg_0, 1);
    }
    else if ((1 << var_C->unk_00) & var_C->unk_04)
    {
        RwInt8 var_12 = ((RwObject *)arg_0)->flags;
        var_12 |= rpATOMICRENDER;
        RpAtomicSetFlags(arg_0, var_12);
        RWS::RpAtomicCollisionProperties::SetIsSolid(*arg_0, 1);
    }
    else
    {
        RwInt8 var_13 = ((RwObject *)arg_0)->flags;
        var_13 &= ~rpATOMICRENDER;
        RpAtomicSetFlags(arg_0, var_13);
        RWS::RpAtomicCollisionProperties::SetIsSolid(*arg_0, 0);
    }
    var_C->unk_00++;
    return arg_0;
}

// match: ?sub_16E370@@YAPAURpAtomic@@PAU1@PAX@Z @ 0x0016E370
// sp-match: ?sub_16E370@@YAPAURpAtomic@@PAU1@PAX@Z @ 0x0010B420
RpAtomic *sub_16E370(RpAtomic *arg_0, void *arg_4)
{
    RwInt8 var_1;
    type_16E250 *var_8;

    var_8 = (type_16E250 *)arg_4;
    var_1 = ((RwObject *)arg_0)->flags;
    if (var_1 & rpATOMICRENDER)
        var_8->unk_04 |= 1 << var_8->unk_00;
    var_8->unk_00++;
    return arg_0;
}

// match: ?sub_16E3C0@@YAPAURpUserDataArray@@PAURpAtomic@@PBD@Z @ 0x0016E3C0
// sp-match: ?sub_16E3C0@@YAPAURpUserDataArray@@PAURpAtomic@@PBD@Z @ 0x0010B450
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RpUserDataArray *sub_16E3C0(RpAtomic *arg_0, const RwChar *arg_4)
{
    RwChar *var_14;
    RpUserDataArray *lv_10;
    RwInt32 var_C;
    RwInt32 bp_8;
    RpGeometry *bp_4;

    bp_4 = arg_0->geometry;
    if (bp_4)
    {
        bp_8 = RpGeometryGetUserDataArrayCount(bp_4);
        for (var_C = 0; var_C < bp_8; var_C++)
        {
            lv_10 = RpGeometryGetUserDataArray(bp_4, var_C);
            if (lv_10->format == rpSTRINGUSERDATA)
            {
                var_14 = RpUserDataArrayGetString(lv_10, 0);
                if (!_strcmpi(var_14, arg_4))
                    return lv_10;
            }
        }
    }
    return 0;
}

// match: ?sub_16E450@@YAPAURpAtomic@@PAU1@PAX@Z @ 0x0016E450
// sp-match: ?sub_16E450@@YAPAURpAtomic@@PAU1@PAX@Z @ 0x0010B4C0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RpAtomic *sub_16E450(RpAtomic *arg_0, void *arg_4)
{
    bool *var_10;
    RpUserDataArray *var_C;
    bool *bp_8;
    const RwChar *bp_4;

    bp_4 = ((type_16E450 *)arg_4)->unk_00;
    var_10 = ((type_16E450 *)arg_4)->unk_04;
    bp_8 = ((type_16E450 *)arg_4)->unk_08;
    var_C = sub_16E3C0(arg_0, bp_4);
    if (var_C)
    {
        *bp_8 = true;
        if (*var_10)
        {
            RwInt8 var_11 = ((RwObject *)arg_0)->flags;
            var_11 |= rpATOMICRENDER;
            RpAtomicSetFlags(arg_0, var_11);
            RWS::RpAtomicCollisionProperties::SetIsSolid(*arg_0, 1);
        }
        else
        {
            RwInt8 var_12 = ((RwObject *)arg_0)->flags;
            var_12 &= ~rpATOMICRENDER;
            RpAtomicSetFlags(arg_0, var_12);
            RWS::RpAtomicCollisionProperties::SetIsSolid(*arg_0, 0);
        }
    }
    return arg_0;
}

// match: ?sub_16E500@@YAPAURpAtomic@@PAU1@PAX@Z @ 0x0016E500
// sp-match: ?sub_16E500@@YAPAURpAtomic@@PAU1@PAX@Z @ 0x0010B520
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RpAtomic *sub_16E500(RpAtomic *arg_0, void *arg_4)
{
    RpUserDataArray *var_C;
    RwInt32 *bp_8;
    const RwChar *bp_4;

    bp_4 = ((type_16E500 *)arg_4)->unk_00;
    bp_8 = ((type_16E500 *)arg_4)->unk_04;
    var_C = sub_16E3C0(arg_0, bp_4);
    if (var_C)
        *bp_8 = (RwInt32)arg_0;
    return arg_0;
}

// match: ?sub_16E540@@YAPAURpLight@@PAU1@PAX@Z @ 0x0016E540
// sp-match: ?sub_16E540@@YAPAURpLight@@PAU1@PAX@Z @ 0x0010B550
RpLight *sub_16E540(RpLight *arg_0, void *arg_4)
{
    type_16E5C0 *var_4;

    var_4 = (type_16E5C0 *)arg_4;
    var_4->unk_08++;
    return arg_0;
}

// match: ?sub_16E560@@YAPAURpClump@@PAU1@PAX@Z @ 0x0016E560
// sp-match: ?sub_16E560@@YAPAURpClump@@PAU1@PAX@Z @ 0x0010B560
RpClump *sub_16E560(RpClump *arg_0, void *arg_4)
{
    type_16E5C0 *var_4;

    var_4 = (type_16E5C0 *)arg_4;
    var_4->unk_04++;
    return arg_0;
}

// match: ?sub_16E580@@YAPAURpAtomic@@PAU1@PAX@Z @ 0x0016E580
// sp-match: ?sub_16E580@@YAPAURpAtomic@@PAU1@PAX@Z @ 0x0009DC70
RpAtomic *sub_16E580(RpAtomic *arg_0, void *arg_4)
{
    type_16E5C0 *var_4;

    var_4 = (type_16E5C0 *)arg_4;
    var_4->unk_00++;
    return arg_0;
}

// match: ?sub_16E5A0@@YAPAURpWorldSector@@PAU1@PAX@Z @ 0x0016E5A0
// sp-match: ?sub_16E5A0@@YAPAURpWorldSector@@PAU1@PAX@Z @ 0x0010B570
RpWorldSector *sub_16E5A0(RpWorldSector *arg_0, void *arg_4)
{
    RpWorldSectorForAllAtomics(arg_0, sub_16E580, arg_4);
    return arg_0;
}

// match: ?sub_16E5C0@@YA_NPAURpWorld@@HH@Z @ 0x0016E5C0
// sp-match: ?sub_16E5C0@@YA_NPAURpWorld@@HH@Z @ 0x0010B590
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Whether the world arg_0 is empty of atomics, clumps and lights (true
// with no world); arg_4 and arg_8 are unused.
bool sub_16E5C0(RpWorld *arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    RwChar var_118[0x100];
    bool local_D;
    type_16E5C0 var_C;

    if (arg_0)
    {
        local_D = true;
        var_C.unk_00 = 0;
        var_C.unk_04 = 0;
        var_C.unk_08 = 0;
        RpWorldForAllClumps(arg_0, sub_16E560, &var_C);
        RpWorldForAllLights(arg_0, sub_16E540, &var_C);
        RpWorldForAllWorldSectors(arg_0, sub_16E5A0, &var_C);
        if (var_C.unk_00 || var_C.unk_04 || var_C.unk_08)
        {
            sprintf(var_118, "World has %d Atomics. ", var_C.unk_00);
            sprintf(var_118, "World has %d Clumps. ", var_C.unk_04);
            sprintf(var_118, "World has %d Lights. ", var_C.unk_08);
            local_D = false;
        }
        return local_D;
    }
    return true;
}

// match: ?sub_16E6B0@@YAPAURwTexture@@PAU1@PAX@Z @ 0x0016E6B0
// sp-match: ?sub_16E6B0@@YAPAURwTexture@@PAU1@PAX@Z @ 0x0010B690
RwTexture *sub_16E6B0(RwTexture *arg_0, void *arg_4)
{
    RwInt32 *var_4;

    if (arg_0->refCount > 1)
    {
        var_4 = (RwInt32 *)arg_4;
        (*var_4)++;
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
        // single player compiles the debug prints out (SP 0x10B690)
        sub_19A750("Warning: Texture cannot be deleted! Texture has %d ref count!", arg_0->refCount);
#endif
    }
    return arg_0;
}

// match: ?sub_16E6F0@@YA_NPAURwTexDictionary@@@Z @ 0x0016E6F0
// sp-match: ?sub_16E6F0@@YA_NPAURwTexDictionary@@@Z @ 0x0010B6B0
// Whether every texture of the dictionary arg_0 can be deleted (none has
// another reference).
bool sub_16E6F0(RwTexDictionary *arg_0)
{
    RwInt32 var_4;

    var_4 = 0;
    RwTexDictionaryForAllTextures(arg_0, sub_16E6B0, &var_4);
    if (var_4 > 0)
    {
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
        // single player compiles the debug print out (SP 0x10B6B0)
        sub_19A750("Warning: Texture dictionary has %d textures that cannot be deleted! Refcount > 0!", var_4);
#endif
        return false;
    }
    return true;
}

// match: ?sub_16E740@@YAXPAX0PAURwV3d@@@Z @ 0x0016E740
// sp-match: ?sub_16E740@@YAXPAX0PAURwV3d@@@Z @ 0x0010B6E0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The unit normal of the triangle arg_0 over the vertices arg_4 into
// *arg_8.
void sub_16E740(void *arg_0, void *arg_4, RwV3d *arg_8)
{
    RwV3d *var_24;
    RwV3d var_20;
    RwV3d ebp_14;
    RwV3d *bp_8;
    RwV3d *bp_4;

    var_24 = &((RwV3d *)arg_4)[((RpTriangle *)arg_0)->vertIndex[0]];
    bp_4 = &((RwV3d *)arg_4)[((RpTriangle *)arg_0)->vertIndex[1]];
    bp_8 = &((RwV3d *)arg_4)[((RpTriangle *)arg_0)->vertIndex[2]];
    RwV3dSubMacro(&var_20, var_24, bp_8);
    RwV3dSubMacro(&ebp_14, bp_4, bp_8);
    RwV3dCrossProductMacro(arg_8, &var_20, &ebp_14);
    if (RwV3dDotProductMacro(arg_8, arg_8) > 0.0f)
        RwV3dNormalize(arg_8, arg_8);
}

// match: ?sub_16E860@@YAXPAURwV3d@@000@Z @ 0x0016E860
// sp-match: ?sub_16E860@@YAXPAURwV3d@@000@Z @ 0x0010B7B0
// The unit normal of the triangle arg_0, arg_4, arg_8 into *arg_C.
void sub_16E860(RwV3d *arg_0, RwV3d *arg_4, RwV3d *arg_8, RwV3d *arg_C)
{
    RwV3d var_C;
    RwV3d var_18;

    RwV3dSubMacro(&var_18, arg_0, arg_8);
    RwV3dSubMacro(&var_C, arg_4, arg_8);
    RwV3dCrossProductMacro(arg_C, &var_18, &var_C);
    if (RwV3dDotProductMacro(arg_C, arg_C) > 0.0f)
        RwV3dNormalize(arg_C, arg_C);
}

// match: ?sub_16E950@@YAXPADPBD@Z @ 0x0016E950
// sp-match: ?sub_16E950@@YAXPADPBD@Z @ 0x0010BBD0
void sub_16E950(RwChar *arg_0, const RwChar *arg_4)
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < (RwInt32)strlen(arg_4); var_4++)
    {
        if (arg_4[var_4] && arg_4[var_4] != '.')
            arg_0[var_4] = arg_4[var_4];
        else
            break;
    }
    arg_0[var_4] = 0;
}
