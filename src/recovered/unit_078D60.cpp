// Split from unit_078AF0.cpp at 0x078D60, where the image starts another object (type_7C8D0,
// its constructor first): its .rdata begins at 0x3D3CB0 with its own 16.666666, the
// unreferenced constant every game object starts its constants with, before the vtable (PLAN M7).

#include "rw/ostypes.h"
#include "game/functions.h"
#include "types/animobjpool.h"
#include "types/animbank.h"
#include "types/type_3D3548.h"
#include "rw/rtquat.h"
#include "rw/rpskin.h"
#include "game/clumpdata.h"
#include "rw/bavector.h"

#ifdef CODFH_SP // Compiler ordering for the root-motion function at 0x64690.
extern "C" void _WriteBarrier();
#pragma intrinsic(_WriteBarrier)
#endif

// Its data definitions (PLAN M5), in the image's address order.
// 0x003D3CB0
extern const RwReal flt_3D3CB0 = 16.666666f;

// match: ?flt_3D3CB0@@3MB @ 0x003D3CB0

#ifdef CODFH_SP
// Single player's deleting destructor (SP 0x64330) drops the call to this empty
// operator delete, so single player defines it in this unit (not unit_078AF0).
void type_7C8D0::operator delete(void *arg_0)
{
}
#endif

// match: ??0type_7C8D0@@QAE@H@Z @ 0x00078D60
// match: ??_7type_7C8D0@@6B@ @ 0x003D3CB4
// match: __real@47c35000 @ 0x003D3CB8
// sp-match: ??0type_7C8D0@@QAE@H@Z @ 0x00063390
type_7C8D0::type_7C8D0(RwInt32 arg_0)
{
    RwUInt32 var_4;

    unk_10 = 0;
    unk_12 = 0;
    unk_14 = 0;
    unk_18 = 0;
    unk_1C = 0;
    unk_24 = 0;
    unk_20 = 0;
    unk_180 = 0;
    unk_184 = 0;
    unk_2C = arg_0;
    unk_30 = (type_7C8D0_30 *)(this + 1);
    for (var_4 = 0; var_4 < unk_2C; var_4++) {
        unk_30[var_4].unk_00 = -1;
        unk_30[var_4].unk_04 = -1;
        unk_30[var_4].unk_08 = 0;
        unk_30[var_4].unk_0C = 0;
        unk_30[var_4].unk_10 = 0;
        unk_30[var_4].unk_14 = 0;
        unk_30[var_4].unk_18 = 0;
        unk_30[var_4].unk_1C = 0;
        unk_30[var_4].unk_20 = 0;
        unk_30[var_4].unk_24 = 1.0f;
        unk_30[var_4].unk_28 = 0;
    }
    for (var_4 = 0; var_4 < type_7C8D0_ring_size; var_4++) {
        unk_34[var_4].unk_04 = 0;
        unk_34[var_4].unk_00 = 0;
        unk_34[var_4].unk_08_0 = 0;
        unk_34[var_4].unk_08_30 = 0;
        unk_34[var_4].unk_0C = 0;
    }
    RwMatrixSetIdentityMacro(&unk_100);
    RwMatrixSetIdentityMacro(&unk_140);
    unk_1B0 = 0;
    unk_188 = 0;
    unk_190.z = 0;
    unk_190.y = 0;
    unk_190.x = 0;
    unk_18C = 0;
    unk_1A8 = 1.0f;
    unk_1A4 = 0;
    unk_1A0 = 0;
    unk_19C = 0;
    unk_1AC = 0;
    unk_28 = 1.0f;
}
// match: ??_Gtype_7C8D0@@UAEPAXI@Z @ 0x00079190
// match: ??1type_7C8D0@@UAE@XZ @ 0x000791C0
// sp-match: ??1type_7C8D0@@UAE@XZ @ 0x00063590
// sp-match: ??_Gtype_7C8D0@@UAEPAXI@Z @ 0x00064330
type_7C8D0::~type_7C8D0()
{
    RwUInt32 var_4;

    for (var_4 = 0; var_4 < unk_2C; var_4++) {
        if (unk_30[var_4].unk_1C != 0) {
            sub_806E0(unk_30[var_4].unk_1C);
            unk_30[var_4].unk_1C = 0;
        }
    }
    if (unk_1B0 != 0) {
        sub_806E0(unk_1B0);
        unk_1B0 = 0;
    }
}
// match: ?sub_79260@@YAXXZ @ 0x00079260
// sp-match: ?sub_79260@@YAXXZ @ 0x00064340
void sub_79260()
{
    sub_7A4A0();
    sub_7A540();
}
// match: ?sub_79270@@YA_NPAURpClump@@PAURpHAnimHierarchy@@@Z @ 0x00079270
// sp-match: ?sub_79270@@YA_NPAURpClump@@PAURpHAnimHierarchy@@@Z @ 0x00064350
// Without a hierarchy arg_4, gives the clump's hierarchy a fresh interpolator (freeing
// the old) with the clump's node vectors, and with a skin, each bone's
// matrix the inverse of its skin-to-bone matrix (in the clump frame's
// world space unless the matrices are local). Then its atomics take the
// hierarchy (sub_7C830); true.
bool sub_79270(RpClump *arg_0, RpHAnimHierarchy *arg_4)
{
    RpHAnimHierarchy *var_4;
    type_80300_150 *var_8;
    RpSkin *var_C;
    RwMatrix var_50;
    const RwMatrix *var_54;
    RwInt32 var_58;
    RwMatrix var_A0;
    RtAnimInterpolator *var_A4;

    if (!arg_4)
    {
        var_4 = sub_16D970(arg_0);
        if (var_4->currentAnim)
        {
            _rpCollTreeDestroy(var_4->currentAnim);
            var_4->currentAnim = 0;
        }
        var_4->currentAnim = (RtAnimInterpolator *)sub_80300(var_4->numNodes * 32 + 32, 1, 0x18);
        sub_80740((type_80300 *)var_4->currentAnim, 0x1142);
        var_8 = ((type_80300 *)var_4->currentAnim)->unk_144;
        var_8->unk_08 = sub_EC270(arg_0);
        var_C = RWS::SkinHelper::FindFirstSkin(*arg_0);
        if (var_C)
        {
            RwMatrixSetIdentityMacro(&var_50);
            var_54 = RpSkinGetSkinToBoneMatrices(var_C);
            for (var_58 = 0; var_58 < var_4->numNodes; var_58++)
            {
                RwMatrixInvert(&var_A0, &var_54[var_58]);
                if (!(var_4->flags & rpHANIMHIERARCHYLOCALSPACEMATRICES))
                {
                    RwMatrixMultiply(&var_50, &var_A0, RwFrameGetLTM(RpClumpGetFrame(arg_0)));
                }
                else
                {
                    var_50 = var_A0;
                }
                var_4->pMatrixArray[var_58] = var_50;
            }
        }
    }
    else
    {
        var_4 = arg_4;
        var_A4 = arg_4->currentAnim;
    }
    RpClumpForAllAtomics(arg_0, sub_7C830, var_4);
    return true;
}
// match: ?sub_79470@type_7C8D0@@QAEXPAURpHAnimHierarchy@@@Z @ 0x00079470
// sp-match: ?sub_79470@type_7C8D0@@QAEXPAURpHAnimHierarchy@@@Z @ 0x00063600
void type_7C8D0::sub_79470(RpHAnimHierarchy *arg_0)
{
    unk_18 = arg_0;
    unk_1B0 = sub_80550(arg_0->numNodes * 32 + 32, 0);
    sub_80740(unk_1B0, 0x1142);
}
// match: ?sub_794C0@type_7C8D0@@QAE_NM@Z @ 0x000794C0
// sp-match: ?sub_794C0@type_7C8D0@@QAE_NM@Z @ 0x00063640
// Queues a new animation record blending over arg_0 seconds, first
// dropping the oldest (and its tracks) when the ring is full.
bool type_7C8D0::sub_794C0(RwReal arg_0)
{
    RwUInt32 var_4;
    RwInt32 local_8;

#ifndef CODFH_SP // single player never drops the oldest record (SP 0x63649: a full ring returns false)
    if (unk_24 >= type_7C8D0_ring_size) {
        for (var_4 = 0; var_4 < unk_2C; var_4++) {
            if (unk_30[var_4].unk_04 == unk_20) {
                unk_30[var_4].unk_00 = -1;
                unk_30[var_4].unk_04 = -1;
            }
            if (unk_30[var_4].unk_04 == -1 && unk_30[var_4].unk_1C != 0) {
                sub_806E0(unk_30[var_4].unk_1C);
                unk_30[var_4].unk_1C = 0;
            }
        }
        unk_24--;
    }
#endif
    if (unk_24 < type_7C8D0_ring_size) {
        unk_24++;
        local_8 = (unk_20 + unk_24 - 1) % type_7C8D0_ring_size;
        unk_34[local_8].unk_00 = unk_14;
        unk_34[local_8].unk_04 = (RwInt32)(arg_0 * 100000.0f);
        unk_34[local_8].unk_08_0 = 0;
        unk_34[local_8].unk_08_30 = 1;
        unk_34[local_8].unk_0C = 0;
        unk_180 = 1;
        if (unk_188) {
            unk_188 = 0;
            unk_34[local_8].unk_0C = 1;
        } else
            unk_1AC = 0;
        return true;
    }
    return false;
}
// match: ?sub_796A0@type_7C8D0@@QAEHPAURtAnimAnimation@@HHPAUtype_783F0@@MMM@Z @ 0x000796A0
// sp-match: ?sub_796A0@type_7C8D0@@QAEHPAURtAnimAnimation@@HHPAUtype_783F0@@MMM@Z @ 0x000636E0
// Starts the animation arg_0 (id arg_4, with the events arg_C) on a free
// track at the time arg_10, with arg_14 and the weight arg_18; returns the
// track's serial, or -2 with no track free.
RwInt32 type_7C8D0::sub_796A0(RtAnimAnimation *arg_0, RwInt32 arg_4, RwInt32 arg_8,
                              type_783F0 *arg_C, RwReal arg_10, RwReal arg_14, RwReal arg_18)
{
    RwUInt32 var_4;
    RwInt32 v8;
    type_783F0_04 *stk_C;
    RwInt32 var_10;

    var_10 = (unk_20 + unk_24 - 1) % type_7C8D0_ring_size;
    for (var_4 = 0; var_4 < unk_2C; var_4++) {
        if (unk_30[var_4].unk_04 == -1)
            break;
    }
    if (var_4 == unk_2C)
        return -2;
    v8 = dword_44A5C0 << 8 | 0x80000000 | var_4;
    dword_44A5C0++;
    unk_30[var_4].unk_00 = v8;
    unk_30[var_4].unk_04 = (RwInt16)var_10;
    unk_30[var_4].unk_0C = 0;
    if (unk_34[var_10].unk_08_0 == 0)
        unk_30[var_4].unk_0C = 4;
    if (arg_C->sub_78550(0, 3) != 0 && !(unk_12 & 1))
        unk_30[var_4].unk_0C |= 1;
    if (arg_8)
        unk_30[var_4].unk_0C |= 0x10;
    unk_30[var_4].unk_10 = arg_0;
    unk_30[var_4].unk_14 = arg_C;
    unk_30[var_4].unk_08 = arg_4;
    unk_34[var_10].unk_08_0++;
    unk_30[var_4].unk_24 = arg_18;
    unk_30[var_4].unk_20 = arg_14;
    unk_30[var_4].unk_28 = (RwInt32)(arg_10 * 100000.0f);
    sub_807C0(unk_18->currentAnim, arg_0->pFrames);
    stk_C = arg_C->sub_78550(0, -1);
    while (stk_C != 0 && stk_C->unk_04 < arg_10)
        stk_C = arg_C->sub_785C0(stk_C, -1);
    unk_30[var_4].unk_18 = stk_C;
    return v8;
}
// match: ?sub_79930@type_7C8D0@@QAEHP6AXPAU1@PAUtype_80300@@H_N@ZMM@Z @ 0x00079930
// sp-match: ?sub_79930@type_7C8D0@@QAEHP6AXPAU1@PAUtype_80300@@H_N@ZMM@Z @ 0x00063880
RwInt32 type_7C8D0::sub_79930(void (*arg_0)(type_7C8D0 *, type_80300 *, RwInt32, bool),
                              RwReal arg_4, RwReal arg_8)
{
    RwUInt32 var_4;
    RwInt32 v8;
    RwInt32 varC;

    varC = (unk_20 + unk_24 - 1) % type_7C8D0_ring_size;
    for (var_4 = 0; var_4 < unk_2C; var_4++) {
        if (unk_30[var_4].unk_04 == -1)
            break;
    }
    if (var_4 == unk_2C)
        return -1;
    v8 = dword_44A5C0 << 8 | 0x80000000 | var_4;
    dword_44A5C0++;
    unk_30[var_4].unk_00 = v8;
    unk_30[var_4].unk_04 = (RwInt16)varC;
    unk_30[var_4].unk_0C = 8;
    if (unk_34[varC].unk_08_0 == 0)
        unk_30[var_4].unk_0C |= 4;
    unk_30[var_4].unk_10_cb = arg_0;
    unk_30[var_4].unk_14 = 0;
    unk_30[var_4].unk_08 = 0;
    unk_34[varC].unk_08_0++;
    if (unk_30[var_4].unk_1C == 0)
        unk_30[var_4].unk_1C = sub_80300(unk_18->numNodes * 32 + 32, 0, 0);
    unk_30[var_4].unk_1C->unk_EB = 0;
    unk_30[var_4].unk_24 = arg_8;
    unk_30[var_4].unk_20 = arg_4;
    unk_30[var_4].unk_28 = 0;
    sub_80740(unk_30[var_4].unk_1C, 0x1142);
    unk_30[var_4].unk_10_cb(this, unk_30[var_4].unk_1C, unk_1C, 1);
    sub_807C0(unk_18->currentAnim, unk_30[var_4].unk_1C->unk_128);
    return v8;
}
// match: ?sub_79BC0@type_7C8D0@@QAE_NH@Z @ 0x00079BC0
// sp-match: ?sub_79BC0@type_7C8D0@@QAE_NH@Z @ 0x000639F0
bool type_7C8D0::sub_79BC0(RwInt32 arg_0)
{
    bool var_1;
    RwInt32 var_8;

    var_8 = arg_0 & 0xFF;
    var_1 = false;
    if (unk_30[var_8].unk_00 == arg_0) {
        unk_34[unk_30[var_8].unk_04].unk_08_0--;
        unk_30[var_8].unk_00 = -1;
        unk_30[var_8].unk_04 = -1;
        var_1 = true;
    }
    return var_1;
}
// match: ?sub_79C90@type_7C8D0@@QAE_NHM@Z @ 0x00079C90
// sp-match: ?sub_79C90@type_7C8D0@@QAE_NHM@Z @ 0x00063A60
bool type_7C8D0::sub_79C90(RwInt32 arg_0, RwReal arg_4)
{
    bool var_1;
    RwInt32 var_8;

    var_8 = arg_0 & 0xFF;
    var_1 = false;
    if (unk_30[var_8].unk_00 == arg_0) {
        unk_30[var_8].unk_20 = arg_4;
        var_1 = true;
    }
    return var_1;
}
// match: ?sub_79CE0@type_7C8D0@@QAE_NH_N@Z @ 0x00079CE0
// sp-match: ?sub_79CE0@type_7C8D0@@QAE_NH_N@Z @ 0x00063A90
bool type_7C8D0::sub_79CE0(RwInt32 arg_0, bool arg_4)
{
    bool var_1;
    RwInt32 var_8;

    var_8 = arg_0 & 0xFF;
    var_1 = false;
    if (unk_30[var_8].unk_00 == arg_0) {
        unk_30[var_8].unk_0C = unk_30[var_8].unk_0C & ~2 | (arg_4 ? 2 : 0);
        var_1 = true;
    }
    return var_1;
}
RwInt32 sub_170ED0(RwReal arg_0);
#if defined(CODFH_DRAW_TRIGGERS) && !defined(CODFH_SP)
// (port/src/debug/trigtools.cpp: whether the entity is one of the debug tools' AI soldiers)
bool TrigIsAiSoldier(const void *pEntity);
#endif
// match: ?sub_79D50@type_7C8D0@@QAE_NPAURwV3d@@0@Z @ 0x00079D50
// sp-match: ?sub_79D50@type_7C8D0@@QAE_NPAURwV3d@@0@Z @ 0x00063AD0
bool type_7C8D0::sub_79D50(RwV3d *arg_0, RwV3d *arg_4)
{
    RwReal var_14;
    RtQuat var_28;
    RwMatrix var_70;
    RwV3d var_7C;
    RtQuat var_8C;
    RtQuat var_A0;
    RtQuat var_B0;
    RwV3d var_BC;

    unk_188 = 1;
    var_14 = atan2(arg_4->x, arg_4->z);
    sub_170ED0(var_14);
    var_28.real = cos(var_14 / 2.0f);
    var_28.imag.x = var_28.imag.z = 0.0f;
    var_28.imag.y = sin(var_14 / 2.0f);
    var_70 = *RwFrameGetLTM(RwFrameGetParent(unk_18->parentFrame));
    RwV3dSubMacro(&var_7C, arg_0, &var_70.pos);
    RtQuatConvertFromMatrix(&var_8C, &var_70);
    RtQuatReciprocalMacro(&var_A0, &var_8C);
    RtQuatMultiplyMacro(&var_B0, &var_A0, &var_28);
    RtQuatTransformVectors(&var_BC, &var_7C, 1, &var_A0);
    unk_190 = var_BC;
    unk_19C_q = var_B0;
    return true;
}
// match: ?sub_7A0A0@type_7C8D0@@QAE_NPAURwV3d@@@Z @ 0x0007A0A0
// sp-match: ?sub_7A0A0@type_7C8D0@@QAE_NPAURwV3d@@@Z @ 0x00063CF0
bool type_7C8D0::sub_7A0A0(RwV3d *arg_0)
{
    RwMatrix var_50;

    var_50 = *RwFrameGetLTM(RwFrameGetParent(unk_18->parentFrame));
    sub_79D50(&var_50.pos, arg_0);
    return true;
}
// match: ?sub_7A100@type_7C8D0@@QAE_NXZ @ 0x0007A100
// sp-match: ?sub_7A100@type_7C8D0@@QAE_NXZ @ 0x00064690
// Takes this frame's root motion: scales unk_190 by how far the root moved
// along it and turns it, and adds the root's rotation to unk_19C.
#ifdef CODFH_SP
bool type_7C8D0::sub_7A100()
{
    // shape: SP 0x64690 lays the box out as two vectors (12 bytes each, below the quaternions)
    RwReal var_68;
    RwReal loc64;
    RtQuat bp_60;
    RwV3d v_sup;
    RwV3d v_inf;
    RtQuat slot_38;
    RwReal loc28;
    RwReal slot_24;
    bool var_1D;
    RtQuat l1C;
    RwV3d var_C;

    var_1D = false;
    unk_1AC = 0;
    loc64 = sub_7C1A0((RwBBox *)&v_sup, &slot_38);
    if (loc64 == 0)
        return false;
    slot_24 = RwV3dLength(&v_sup);
    loc28 = RwV3dLength((RwV3d *)&unk_190);
    var_68 = RwV3dDotProductMacro(&unk_190, &v_sup);
    if (slot_24 * loc28 != 0)
        unk_18C = var_68 / (slot_24 * loc28);
    else
        unk_18C = 0;
    RwV3dScaleMacro(&var_C, &v_sup, unk_18C);
    RwV3dSubMacro(&v_inf, &unk_190, &var_C);
    RtQuatReciprocalMacro(&bp_60, &slot_38);
    // shape: SP 0x64690 keeps these stores ordered and separates the final product
    // from its sum. The ordering intrinsics emit no instructions.
    _WriteBarrier();
    l1C.real = unk_19C_q.real * bp_60.real - RwV3dDotProductMacro(&unk_19C_q.imag, &bp_60.imag);
    _WriteBarrier();
    RwV3dCrossProductMacro(&l1C.imag, &bp_60.imag, &unk_19C_q.imag);
    RwV3dIncrementScaledMacro(&l1C.imag, &unk_19C_q.imag, bp_60.real);
    l1C.imag.x = l1C.imag.x + bp_60.imag.x * unk_19C_q.real;
    l1C.imag.y = l1C.imag.y + bp_60.imag.y * unk_19C_q.real;
    {
        RwReal z = bp_60.imag.z * unk_19C_q.real;
        l1C.imag.z += z;
    }
    sub_19B650(&v_inf);
    unk_190 = v_inf;
    unk_19C_q = l1C;
    unk_1AC = 1;
    return var_1D;
}
#else
bool type_7C8D0::sub_7A100()
{
    RwReal var_68;
    RwReal loc64;
    RtQuat bp_60;
    RwBBox var_50;
    RtQuat slot_38;
    RwReal loc28;
    RwReal slot_24;
    bool var_1D;
    RtQuat l1C;
    RwV3d var_C;

    var_1D = false;
    unk_1AC = 0;
    loc64 = sub_7C1A0(&var_50, &slot_38);
    if (loc64 == 0)
        return false;
    slot_24 = RwV3dLength((RwV3d *)&var_50);
    loc28 = RwV3dLength((RwV3d *)&unk_190);
    var_68 = RwV3dDotProductMacro(&unk_190, &var_50.sup);
    if (slot_24 * loc28 != 0)
        unk_18C = var_68 / (slot_24 * loc28);
    else
        unk_18C = 0;
    RwV3dScaleMacro(&var_C, &var_50.sup, unk_18C);
    RwV3dSubMacro(&var_50.inf, &unk_190, &var_C);
    RtQuatReciprocalMacro(&bp_60, &slot_38);
    quatMultiplyMacro(&l1C, &unk_19C_q, &bp_60);
    sub_19B650(&var_50.inf);
    unk_190 = var_50.inf;
    unk_19C_q = l1C;
    unk_1AC = 1;
    return var_1D;
}
#endif
// match: ?sub_7A410@@YA_NHP6AXHPAXPAUtype_3D3548@@PAUtype_7C8D0_30@@PAUtype_7C8D0@@@Z@Z @ 0x0007A410
// sp-match: ?sub_7A410@@YA_NHP6AXHPAXPAUtype_3D3548@@PAUtype_7C8D0_30@@PAUtype_7C8D0@@@Z@Z @ 0x00063D40
// Registers the event callback arg_4 for the event id arg_0 (-1 takes the
// last slot); whether there was a slot.
bool sub_7A410(RwInt32 arg_0, type_7A410_cb arg_4)
{
    RwInt32 var_4;
    RwInt32 local_8;

    local_8 = 4;
    for (var_4 = 0; var_4 < 4; var_4++) {
        if (dword_44A5A0[var_4].unk_00 == arg_0)
            local_8 = var_4;
        if (dword_44A5A0[var_4].unk_04 == 0 && local_8 == 4 && (arg_0 != -1 || var_4 == 3))
            local_8 = var_4;
    }
    if (local_8 == 4)
        return false;
    dword_44A5A0[local_8].unk_00 = arg_0;
    dword_44A5A0[local_8].unk_04 = arg_4;
    return true;
}
// match: ?sub_7A4A0@@YA_NXZ @ 0x0007A4A0
// sp-match: ?sub_7A4A0@@YA_NXZ @ 0x00063E00
bool sub_7A4A0()
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 4; var_4++) {
        dword_44A5A0[var_4].unk_00 = -1;
        dword_44A5A0[var_4].unk_04 = 0;
    }
    return true;
}
// match: ?sub_7A4E0@@YAHP6AXPAUtype_7C8D0@@PAUtype_80300@@H_N@Z@Z @ 0x0007A4E0
// sp-match: ?sub_7A4E0@@YAHP6AXPAUtype_7C8D0@@PAUtype_80300@@H_N@Z@Z @ 0x00063E40
// Adds the update hook arg_0 in the last free slot; its slot, or -1.
RwInt32 sub_7A4E0(void (*arg_0)(type_7C8D0 *, type_80300 *, RwInt32, bool))
{
    RwInt32 var_4;
    RwInt32 local_8;

    local_8 = 8;
    for (var_4 = 0; var_4 < 8; var_4++) {
        if (dword_44A580[var_4] == 0)
            local_8 = var_4;
    }
    if (local_8 == 8)
        return -1;
    dword_44A580[local_8] = arg_0;
    return local_8;
}
// match: ?sub_7A540@@YA_NXZ @ 0x0007A540
bool sub_7A540()
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 8; var_4++)
        dword_44A580[var_4] = 0;
    return true;
}
// match: ?sub_7A580@type_7C8D0@@QAEXMPAURwV3d@@_N@Z @ 0x0007A580
// sp-match: ?sub_7A580@type_7C8D0@@QAEXMPAURwV3d@@_N@Z @ 0x00064910
// Advances the player by arg_0 seconds (arg_8: decode the keys): drops the
// queue records that have finished blending in, runs every record's tracks
// (starting their interpolators, advancing them, taking the root node's
// motion out of the newest record's) and blends them into its pose, then
// the pose into the hierarchy's; flags the pose and, when the newest
// record's first track ran past its end, sends the event 2. The root
// motion's frame update (into *arg_4, or the clump's frame) is disabled.
void type_7C8D0::sub_7A580(RwReal arg_0, RwV3d *arg_4, bool arg_8)
{
    RwInt32 lv_8;
    RwInt32 lv_c;
    bool lv_d;
    bool lv_e;
    type_7C8D0_30 *lv_14;
    RwUInt8 lv_15;
    RtQuat lv_28;
    RwV3d lv_34;
    RwReal lv_38;
    RwInt32 lv_3c;
    RwInt32 lv_40;
    RwInt16 lv_44;
    type_7CBD0_hdr lv_60;
    type_7CBD0 *lv_64;
    RwInt32 lv_68;
    RwInt32 lv_6c;
    RwInt32 lv_70;
    RwInt32 lv_74;
    RwInt32 lv_78;
    RwInt32 lv_7c;
    type_7C8D0_30 *lv_80;
    bool lv_81;
    RwReal lv_88;
    type_7CBD0_hdr *lv_8c;
    type_7CBD0_t *lv_9c;
    RwInt32 lv_a0;
    RwInt32 lv_a4;
    RtQuat *lv_b4;
    RwV3d lv_c0;
    RtQuat lv_d0;
    RwReal lv_d4;
    type_7CBD0_hdr *lv_dc;
    RwInt32 lv_e4;
    type_7CBD0 *lv_f4;
    type_7CBD0_t *lv_f8;
    RtQuat *lv_104;
    RwMatrix lv_150;
    RwReal lv_154;
    RwInt32 lv_158;
    RwInt32 lv_15c;
    type_7CBD0_hdr *lv_160;
    RtQuat *lv_164;
    RwInt32 lv_1d0;
    RwMatrix lv_230;
    RwFrame *lv_234;
    RwMatrix *lv_238;
    RwMatrix lv_290;
    RwFrame *lv_294;
    type_80300 *lv_298;

    lv_8 = 0;
    lv_c = RpHAnimIDGetIndex(unk_18, 100);
    lv_d = 0;
    lv_e = 0;
    lv_14 = 0;
    lv_15 = unk_1AC;
    lv_28 = unk_19C_q;
    lv_34 = unk_190;
    lv_38 = unk_18C;
    lv_3c = unk_20;
    lv_40 = unk_20 + unk_24 - 1;
    lv_44 = unk_12;
    unk_184 = 0;
    sub_807C0((RtAnimInterpolator *)unk_1B0, &lv_60);
    lv_64 = (type_7CBD0 *)unk_1B0->unk_144;
    lv_64->unk_04 = &lv_60;
    lv_60.unk_00 = 0;
    lv_60.unk_02 = 0;
    if (unk_180) {
        unk_180 = 0;
        unk_140 = *(RwMatrixTag *)RwFrameGetMatrix(RwFrameGetParent(unk_18->parentFrame));
        unk_100 = unk_140;
    }
    if (arg_4 != 0) {
        arg_4->x = 0.0f;
        arg_4->y = 0.0f;
        arg_4->z = 0.0f;
    }
    unk_14 += (RwInt32)(arg_0 * 100000.0f);
    lv_68 = unk_14;
    for (lv_6c = lv_40; lv_6c > lv_3c; lv_6c--) {
        lv_70 = lv_6c % type_7C8D0_ring_size;
        if (lv_68 - (unk_34[lv_70].unk_00 + unk_34[lv_70].unk_04) > 0) {
            unk_20 = lv_70;
            unk_24 = lv_40 - lv_6c + 1;
            for (lv_74 = 0; lv_74 < (RwInt32)unk_2C; lv_74++) {
                if (unk_30[lv_74].unk_04 != -1 && (unk_30[lv_74].unk_04 - unk_20 + type_7C8D0_ring_size) % type_7C8D0_ring_size >= unk_24) {
                    unk_30[lv_74].unk_00 = -1;
                    unk_30[lv_74].unk_04 = -1;
                }
                if (unk_30[lv_74].unk_04 == -1 && unk_30[lv_74].unk_1C != 0) {
                    sub_806E0(unk_30[lv_74].unk_1C);
                    unk_30[lv_74].unk_1C = 0;
                }
            }
            break;
        }
    }
    lv_3c = unk_20;
    lv_40 = unk_20 + unk_24 - 1;
    for (lv_6c = lv_3c; lv_6c <= lv_40; lv_6c++) {
        lv_78 = 0;
        lv_7c = lv_6c % type_7C8D0_ring_size;
        if (unk_34[lv_7c].unk_08_30)
            unk_34[lv_7c].unk_08_30 = 0;
        lv_80 = sub_7C350(lv_7c, 0);
        while (lv_80 != 0) {
            lv_81 = 0;
            if (lv_6c == lv_40 && (lv_80->unk_0C & 4))
                lv_14 = lv_80;
            if (unk_34[lv_7c].unk_0C != 0 && (lv_80->unk_0C & 4)) {
                unk_34[lv_7c].unk_0C = 0;
                if (lv_7c == lv_40 % type_7C8D0_ring_size)
                    sub_7A100();
            }
            if (lv_80->unk_1C == 0) {
                lv_80->unk_1C = sub_80550(unk_18->numNodes * 32 + 32, 1);
                lv_80->unk_1C->unk_EB = (lv_80->unk_0C & 0x10) ? 1 : 0;
                lv_81 = 1;
            }
            if (!(lv_80->unk_0C & 8)) {
                if (lv_81) {
                    if (lv_80->unk_18 != 0)
                        sub_808A0(lv_80->unk_1C, sub_7C4E0, lv_80->unk_18->unk_04, this);
                    sub_807E0(lv_80->unk_1C, lv_80->unk_10);
                    sub_81110(lv_80->unk_1C, (RwReal)lv_80->unk_28, arg_8);
                    sub_80880(lv_80->unk_1C, sub_7C740, this);
                    lv_80->unk_1C->unk_10C.x = lv_80->unk_1C->unk_10C.y = lv_80->unk_1C->unk_10C.z = 0.0f;
                    lv_80->unk_1C->unk_118.imag.x = lv_80->unk_1C->unk_118.imag.y =
                        lv_80->unk_1C->unk_118.imag.z = 0.0f;
                    lv_80->unk_1C->unk_118.real = 1.0f;
                }
                lv_88 = arg_0 * lv_80->unk_24;
                if (lv_80->unk_10->duration < lv_88 + lv_80->unk_1C->unk_E4)
                    lv_88 = lv_80->unk_10->duration - lv_80->unk_1C->unk_E4;
                sub_80910(lv_80->unk_1C, lv_88, arg_8);
            } else {
                if (lv_81) {
                    sub_80740(lv_80->unk_1C, 0x1142);
                    lv_80->unk_10_cb(this, lv_80->unk_1C, unk_1C, 1);
                }
                lv_80->unk_10_cb(this, lv_80->unk_1C, unk_1C, 0);
            }
            lv_8c = (type_7CBD0_hdr *)lv_80->unk_1C->unk_128;
            if (lv_c != -1 && lv_8c->unk_10 && ((RwUInt64)1 << lv_c & lv_8c->unk_08)) {
                {
                    lv_64 = (type_7CBD0 *)lv_80->unk_1C->unk_144;
                    lv_9c = (type_7CBD0_t *)&lv_64->unk_10[lv_8c->unk_00];
                    lv_a0 = 0;
                    for (lv_a4 = 0; lv_a4 < lv_8c->unk_02; lv_a4++) {
                        while (!((RwUInt64)1 << lv_a0 & lv_8c->unk_10))
                            lv_a0++;
                        if (lv_a0 == lv_c)
                            break;
                        lv_a0++;
                    }
                    lv_9c += lv_a4;
                    lv_b4 = &lv_64->unk_10[lv_c];
                    if (lv_6c == lv_40 && (lv_80->unk_0C & 2)) {
                        lv_c0 = lv_9c->unk_00;
                        lv_d0 = *lv_b4;
                        if (lv_81) {
                            lv_80->unk_1C->unk_10C = lv_c0;
                            lv_80->unk_1C->unk_118 = lv_d0;
                        }
                        RwV3dSub(&lv_9c->unk_00, &lv_9c->unk_00, &lv_80->unk_1C->unk_10C);
                        lv_80->unk_1C->unk_118.real = -lv_80->unk_1C->unk_118.real;
                        RtQuatMultiplyMacro(lv_b4, lv_b4, &lv_80->unk_1C->unk_118);
                        lv_80->unk_1C->unk_10C = lv_c0;
                        lv_80->unk_1C->unk_118 = lv_d0;
                        unk_180 = 1;
                    }
                    if (lv_6c != lv_40 || !(lv_80->unk_0C & 1)) {
                        lv_9c->unk_00.x = lv_9c->unk_00.y = lv_9c->unk_00.z = 0.0f;
                        lv_b4->imag.x = lv_b4->imag.y = lv_b4->imag.z = 0.0f;
                        lv_b4->real = 1.0f;
                    }
                }
            }
            if (lv_80->unk_04 != -1) {
                if (lv_80->unk_20 != 0.0f) {
                    if (lv_78 == 0) {
                        sub_808D0(unk_1B0, lv_80->unk_1C);
                        lv_e = 1;
                    } else {
                        lv_d4 = lv_80->unk_20;
                        sub_81170(unk_1B0, unk_1B0, lv_80->unk_1C, lv_d4);
                    }
                    lv_78++;
                }
            } else {
                sub_806E0(lv_80->unk_1C);
                lv_80->unk_1C = 0;
            }
            lv_80 = sub_7C350(lv_7c, lv_80);
        }
        if (lv_8 == 0) {
            sub_808D0((type_80300 *)unk_18->currentAnim, unk_1B0);
            lv_8++;
        } else {
            if (unk_34[lv_7c].unk_04 > 0)
                lv_d4 = (RwReal)(lv_68 - unk_34[lv_7c].unk_00) / unk_34[lv_7c].unk_04;
            else
                lv_d4 = 0.0f;
            if (lv_d4 != 0.0f) {
                if (lv_d4 > 1.0f)
                    lv_d4 = 1.0f;
                sub_81170((type_80300 *)unk_18->currentAnim, (type_80300 *)unk_18->currentAnim, unk_1B0, lv_d4);
                lv_dc = (type_7CBD0_hdr *)((type_80300 *)unk_18->currentAnim)->unk_128;
                if (lv_6c == lv_40 && lv_c != -1 && lv_dc->unk_10) {
                    {
                        lv_64 = (type_7CBD0 *)unk_1B0->unk_144;
                        lv_9c = (type_7CBD0_t *)&lv_64->unk_10[lv_dc->unk_00];
                        lv_e4 = 0;
                        for (lv_a4 = 0; lv_a4 < lv_dc->unk_02; lv_a4++) {
                            while (!((RwUInt64)1 << lv_e4 & lv_dc->unk_10))
                                lv_e4++;
                            if (lv_e4 == lv_c)
                                break;
                            lv_e4++;
                        }
                        lv_9c += lv_a4;
                        lv_b4 = &lv_64->unk_10[lv_c];
                        lv_dc = (type_7CBD0_hdr *)((type_80300 *)unk_18->currentAnim)->unk_128;
                        lv_f4 = (type_7CBD0 *)((type_80300 *)unk_18->currentAnim)->unk_144;
                        lv_f8 = (type_7CBD0_t *)&lv_f4->unk_10[lv_dc->unk_00];
                        lv_e4 = 0;
                        for (lv_a4 = 0; lv_a4 < lv_dc->unk_02; lv_a4++) {
                            while (!((RwUInt64)1 << lv_e4 & lv_dc->unk_10))
                                lv_e4++;
                            if (lv_e4 == lv_c)
                                break;
                            lv_e4++;
                        }
                        lv_f8 += lv_a4;
                        lv_104 = &lv_f4->unk_10[lv_c];
                        *lv_f8 = *lv_9c;
                        *lv_104 = *lv_b4;
                    }
                }
            }
            lv_8++;
        }
    }
    if (lv_e) {
        RwMatrixSetIdentity(&lv_150);
        lv_154 = 0.0f;
        if (lv_15 && lv_14 != 0) {
            lv_154 = lv_14->unk_1C->unk_E4 / lv_14->unk_10->duration;
            if (lv_154 > 1.0f) {
                lv_154 = 1.0f;
                lv_d = 1;
            }
        }
        lv_158 = 1;
        lv_15c = 1;
        // The root motion's frame update, disabled (`if (0)`, still emitted).
#ifdef CODFH_SP // single player moves the root unless unk_12's bit 0 is set or the hierarchy has no bone 100 (SP 0x654B0)
        if (!(lv_44 & 1) && lv_c != -1) {
#elif defined(CODFH_DRAW_TRIGGERS)
        // (the port's debug tools: an AI soldier in multiplayer moves and turns by its root, as in
        // single player)
        if (TrigIsAiSoldier((const void *)unk_1C) && !(lv_44 & 1) && lv_c != -1) {
#else
        if (0) {
#endif
            lv_160 = (type_7CBD0_hdr *)((type_80300 *)unk_18->currentAnim)->unk_128;
            lv_64 = (type_7CBD0 *)((type_80300 *)unk_18->currentAnim)->unk_144;
            if (lv_15c) {
                RtQuat lv_174;
                RtQuat lv_184;
                RtQuat lv_194;
                lv_164 = &lv_64->unk_10[lv_c];
                lv_174 = *lv_164;
                if (lv_154 > 0.0f) {
                    lv_184.imag.x = 0.0f;
                    lv_184.imag.y = 0.0f;
                    lv_184.imag.z = 0.0f;
                    lv_184.real = 1.0f;
                    sub_13FBC0(&lv_194, &lv_184, &lv_28, lv_154);
                    RtQuatMultiplyMacro(&lv_174, lv_164, &lv_194);
                }
                RtQuatConvertToMatrix(&lv_174, &lv_150);
            }
            if (lv_158) {
                if (lv_160->unk_10) {
                    RwV3d lv_1e4;
                    RwV3d lv_1f0;
                    lv_9c = (type_7CBD0_t *)&lv_64->unk_10[lv_160->unk_00];
                    lv_1d0 = 0;
                    for (lv_a4 = 0; lv_a4 < lv_160->unk_02; lv_a4++) {
                        while (!((RwUInt64)1 << lv_1d0 & lv_160->unk_10))
                            lv_1d0++;
                        if (lv_1d0 == lv_c)
                            break;
                        lv_1d0++;
                    }
                    lv_9c += lv_a4;
                    lv_1e4 = lv_9c->unk_00;
                    if (lv_154 > 0.0f) {
                        RwV3dScale(&lv_1f0, &lv_34, lv_154);
                        RwV3dScale(&lv_1e4, &lv_1e4, lv_38);
                        RwV3dAdd(&lv_1e4, &lv_1e4, &lv_1f0);
                    }
                    RwMatrixTranslate(&lv_150, &lv_1e4, rwCOMBINEPOSTCONCAT);
                }
            }
            if (arg_4 != 0) {
                RwV3d lv_244;
                RwMatrixSetIdentity(&lv_230);
                lv_234 = RwFrameGetParent(unk_18->parentFrame);
                lv_238 = RwFrameGetMatrix(lv_234);
                lv_230 = *lv_238;
                RwMatrixTransform(&lv_230, (RwMatrix *)&unk_100, rwCOMBINEREPLACE);
                RwMatrixTransform(&lv_230, &lv_150, rwCOMBINEPRECONCAT);
                arg_4->x = lv_230.pos.x - unk_140.pos.x;
                arg_4->y = lv_230.pos.y - unk_140.pos.y;
                arg_4->z = lv_230.pos.z - unk_140.pos.z;
                unk_140 = *(RwMatrixTag *)&lv_230;
                lv_244 = lv_238->pos;
                lv_230.pos.x = 0.0f;
                lv_230.pos.y = 0.0f;
                lv_230.pos.z = 0.0f;
                RwMatrixTransform(lv_238, &lv_230, rwCOMBINEREPLACE);
                lv_238->pos = lv_244;
                RwMatrixUpdate(lv_238);
                RwMatrixSetIdentity(&lv_290);
                RwMatrixInvert(&lv_290, &lv_230);
                sub_1414C0(&lv_244, arg_4, &lv_290);
                *arg_4 = lv_244;
            } else {
                lv_294 = RwFrameGetParent(unk_18->parentFrame);
                RwFrameTransform(lv_294, (RwMatrix *)&unk_100, rwCOMBINEREPLACE);
                RwFrameTransform(lv_294, &lv_150, rwCOMBINEPRECONCAT);
                unk_140 = *(RwMatrixTag *)RwFrameGetMatrix(lv_294);
            }
        }
        lv_298 = (type_80300 *)unk_18->currentAnim;
        if (arg_8)
            lv_298->unk_EA |= 1;
        else
            lv_298->unk_EA &= ~1;
        unk_184 = 1;
        if (lv_d) {
            for (lv_6c = 0; lv_6c < 4; lv_6c++) {
                if (dword_44A5A0[lv_6c].unk_04 != 0
                    && (dword_44A5A0[lv_6c].unk_00 == -1 || dword_44A5A0[lv_6c].unk_00 == 2))
                    dword_44A5A0[lv_6c].unk_04(2, 0, (type_3D3548 *)unk_1C, 0, this);
            }
        }
    }
}
// match: ?sub_7C090@type_7C8D0@@QAEXM_N@Z @ 0x0007C090
// sp-match: ?sub_7C090@type_7C8D0@@QAEXM_N@Z @ 0x00063F00
void type_7C8D0::sub_7C090(RwReal arg_0, bool arg_4)
{
    RwUInt32 var_4;
    bool local_5;
    RwInt32 varC;

    local_5 = false;
    for (var_4 = 0; var_4 < unk_2C; var_4++) {
        if (unk_30[var_4].unk_04 == -1 || unk_30[var_4].unk_1C == 0)
            continue;
        if (unk_30[var_4].unk_1C->unk_EB != 0) {
            local_5 = true;
            break;
        }
    }
    if (local_5)
        unk_12 |= 4;
    else
        unk_12 &= ~4;
    if (unk_184 != 0) {
        varC = 0;
        if (local_5)
            varC = 1;
        else if (arg_4)
            varC = 2;
        sub_7F3C0(unk_18, varC, unk_28);
        unk_184 = 0;
    }
}
// match: ?sub_7C1A0@type_7C8D0@@QAEMPAURwBBox@@PAURtQuat@@@Z @ 0x0007C1A0
// sp-match: ?sub_7C1A0@type_7C8D0@@QAEMPAURwBBox@@PAURtQuat@@@Z @ 0x000644E0
// The root's position (into arg_0's first corner) and rotation (arg_4) of
// the newest queue record, blended over its tracks; the longest weighted
// duration.
RwReal type_7C8D0::sub_7C1A0(RwBBox *arg_0, RtQuat *arg_4)
{
    RwV3d local_50;
    RtQuat slot_44;
    type_7C8D0_30 *ebp_34;
    RwV3d var_30;
    RwReal l24;
    RwReal l20;
    RwReal fp_1C;
    RtQuat loc18;
    bool local_5;
    RwInt32 var_4;

    l24 = 0;
    local_5 = true;
    var_4 = (unk_20 + unk_24 - 1) % type_7C8D0_ring_size;
    ebp_34 = sub_7C350(var_4, 0);
    while (ebp_34 != 0) {
        if (ebp_34->unk_0C & 1) {
            local_50 = ebp_34->unk_14->sub_78550(0, 3)->unk_08_v;
            loc18 = ebp_34->unk_14->sub_78550(0, 4)->unk_08_q;
            l20 = ebp_34->unk_10->duration * ebp_34->unk_24;
            if (local_5) {
                var_30 = local_50;
                slot_44 = loc18;
                local_5 = false;
                l24 = l20;
            } else {
                fp_1C = ebp_34->unk_20;
                sub_13FBC0(&slot_44, &slot_44, &loc18, fp_1C);
                var_30.x = (local_50.x - var_30.x) * fp_1C + var_30.x;
                var_30.y = (local_50.y - var_30.y) * fp_1C + var_30.y;
                var_30.z = (local_50.z - var_30.z) * fp_1C + var_30.z;
                if (l20 > l24)
                    l24 = l20;
            }
        }
        ebp_34 = sub_7C350(var_4, ebp_34);
    }
    arg_0->sup = var_30;
    *arg_4 = slot_44;
    return l24;
}
// match: ?sub_7C350@type_7C8D0@@QAEPAUtype_7C8D0_30@@HPAU2@@Z @ 0x0007C350
// sp-match: ?sub_7C350@type_7C8D0@@QAEPAUtype_7C8D0_30@@HPAU2@@Z @ 0x00063F90
type_7C8D0_30 *type_7C8D0::sub_7C350(RwInt32 arg_0, type_7C8D0_30 *arg_4)
{
    RwUInt32 var_4;
    RwUInt32 v8;
    RwInt32 varC;

    var_4 = 0;
    if (arg_4 != 0) {
        v8 = (RwUInt8 *)arg_4 - (RwUInt8 *)unk_30;
        var_4 = v8 / sizeof(type_7C8D0_30);
        var_4++;
    }
    for (varC = var_4; varC < (RwInt32)unk_2C; varC++) {
        if (unk_30[varC].unk_04 == arg_0)
            return &unk_30[varC];
    }
    return 0;
}
// match: ?sub_7C3E0@type_7C8D0@@QAEHHH@Z @ 0x0007C3E0
// sp-match: ?sub_7C3E0@type_7C8D0@@QAEHHH@Z @ 0x00063FF0
RwInt32 type_7C8D0::sub_7C3E0(RwInt32 arg_0, RwInt32 arg_4)
{
    RwInt32 var_4;
    RwInt32 v8;
    RwInt32 varC;

    v8 = (unk_20 + unk_24 - (arg_0 + 1)) % type_7C8D0_ring_size;
    var_4 = 0;
    if (arg_4 != 0) {
        var_4 = arg_4 & 0xFF;
        var_4++;
    }
    for (varC = var_4; varC < (RwInt32)unk_2C; varC++) {
        if (unk_30[varC].unk_04 == v8)
            return unk_30[varC].unk_00;
    }
    return 0;
}
// match: ?sub_7C480@type_7C8D0@@QAEPAUtype_783F0_04@@HMH@Z @ 0x0007C480
// sp-match: ?sub_7C480@type_7C8D0@@QAEPAUtype_783F0_04@@HMH@Z @ 0x00064060
type_783F0_04 *type_7C8D0::sub_7C480(RwInt32 arg_0, RwReal arg_4, RwInt32 arg_8)
{
    type_783F0_04 *var_4;
    type_783F0 *v8;
    RwInt32 varC;

    varC = arg_0 & 0xFF;
    var_4 = 0;
    if (unk_30[varC].unk_00 == arg_0) {
        v8 = unk_30[varC].unk_14;
        var_4 = v8->sub_78550(arg_4, arg_8);
    }
    return var_4;
}
// match: ?sub_7C4E0@@YAPAUtype_80300@@PAU1@PAX@Z @ 0x0007C4E0
// sp-match: ?sub_7C4E0@@YAPAUtype_80300@@PAU1@PAX@Z @ 0x000640A0
// Runs the event callbacks for the events the interpolator arg_0 has passed
// on its track of the player arg_4 (for the newest record, or event 0x898),
// and sets itself up again for the next event.
type_80300 *sub_7C4E0(type_80300 *arg_0, void *arg_4)
{
    RwInt32 l4;
    type_7C8D0 *var_8;
    RwReal fp_C;
    RwReal local_10;
    type_783F0_04 *stk_14;
    type_7C8D0_30 *loc18;

    var_8 = (type_7C8D0 *)arg_4;
    loc18 = 0;
    stk_14 = 0;
    local_10 = -1.0f;
    for (l4 = 0; l4 < (RwInt32)var_8->unk_2C; l4++) {
        if (arg_0 == var_8->unk_30[l4].unk_1C) {
            loc18 = &var_8->unk_30[l4];
            stk_14 = loc18->unk_18;
            break;
        }
    }
    fp_C = arg_0->unk_E4;
    if (stk_14 != 0 && arg_0->unk_E4 < stk_14->unk_04)
        fp_C += arg_0->unk_00->duration;
    while (stk_14 != 0) {
        RwInt32 var_1C;

        var_1C = (var_8->unk_20 + var_8->unk_24 - 1) % type_7C8D0_ring_size;
        if (loc18->unk_04 == var_1C && (loc18->unk_0C & 4)) {
            for (l4 = 0; l4 < 4; l4++) {
                if (dword_44A5A0[l4].unk_04 != 0
                    && (dword_44A5A0[l4].unk_00 == -1 || stk_14->unk_00 == dword_44A5A0[l4].unk_00)) {
                    dword_44A5A0[l4].unk_04(stk_14->unk_00, &stk_14->unk_08,
                                               (type_3D3548 *)var_8->unk_1C, loc18, var_8);
                    break;
                }
            }
        }
#ifndef CODFH_SP // single player has no event 0x898 pass (SP 0x64179 follows the first)
        if (loc18->unk_04 == var_1C && stk_14->unk_00 == 0x898) {
            for (l4 = 0; l4 < 4; l4++) {
                if (dword_44A5A0[l4].unk_04 != 0
                    && (dword_44A5A0[l4].unk_00 == -1 || stk_14->unk_00 == dword_44A5A0[l4].unk_00)) {
                    dword_44A5A0[l4].unk_04(stk_14->unk_00, &stk_14->unk_08,
                                               (type_3D3548 *)var_8->unk_1C, loc18, var_8);
                    break;
                }
            }
        }
#endif
        loc18->unk_18 = loc18->unk_14->sub_785C0(loc18->unk_18, -1);
        stk_14 = loc18->unk_18;
        if (stk_14 != 0 && stk_14->unk_04 > fp_C) {
            local_10 = stk_14->unk_04;
            stk_14 = 0;
        }
    }
    if (local_10 >= 0) {
        sub_808A0(arg_0, sub_7C4E0, local_10, var_8);
        return arg_0;
    }
    return 0;
}
// match: ?sub_7C740@@YAPAUtype_80300@@PAU1@PAX@Z @ 0x0007C740
// sp-match: ?sub_7C740@@YAPAUtype_80300@@PAU1@PAX@Z @ 0x000641E0
type_80300 *sub_7C740(type_80300 *arg_0, void *arg_4)
{
    RwInt32 var_4;
    type_7C8D0 *v8;
    type_7C8D0_30 *stk_C;
    RwV3d stk_18;

    v8 = (type_7C8D0 *)arg_4;
    stk_C = 0;
    for (var_4 = 0; var_4 < (RwInt32)v8->unk_2C; var_4++) {
        if (arg_0 == v8->unk_30[var_4].unk_1C) {
            stk_C = &v8->unk_30[var_4];
            break;
        }
    }
    if (stk_C->unk_0C & 1) {
        stk_18 = stk_C->unk_14->sub_78550(0, 3)->unk_08_v;
        RwV3dAddMacro(&stk_C->unk_1C->unk_10C, &stk_C->unk_1C->unk_10C, &stk_18);
    }
    return arg_0;
}
// match: ?sub_7C830@@YAPAURpAtomic@@PAU1@PAX@Z @ 0x0007C830
// sp-match: ?sub_7C830@@YAPAURpAtomic@@PAU1@PAX@Z @ 0x00064280
RpAtomic *sub_7C830(RpAtomic *atomic, void *data)
{
    RpSkinAtomicSetHAnimHierarchy(atomic, data);
    return atomic;
}
// match: ?sub_7C850@type_7C8D0@@QAEHXZ @ 0x0007C850
// sp-match: ?sub_7C850@type_7C8D0@@QAEHXZ @ 0x000642A0
RwInt32 type_7C8D0::sub_7C850()
{
    RwInt32 var_4;
    RwInt32 local_8;

    var_4 = (unk_20 + unk_24 - 1) % type_7C8D0_ring_size;
    for (local_8 = 0; local_8 < (RwInt32)unk_2C; local_8++) {
        if (unk_30[local_8].unk_04 == var_4)
            return unk_30[local_8].unk_08;
    }
    return 0;
}
// match: ?sub_7C8D0@type_7C8D0@@QAEMXZ @ 0x0007C8D0
// sp-match: ?sub_7C8D0@type_7C8D0@@QAEMXZ @ 0x000642F0
// The duration of the first track with flag 4, or 0.
RwReal type_7C8D0::sub_7C8D0()
{
    RwReal var_4;
    RwUInt32 local_8;

    var_4 = 0;
    for (local_8 = 0; local_8 < unk_2C; local_8++) {
        if (unk_30[local_8].unk_0C & 4)
            return unk_30[local_8].unk_10->duration;
    }
    return var_4;
}
// match: ?sub_7C940@type_7C8D0@@QAEHXZ @ 0x0007C940
RwInt32 type_7C8D0::sub_7C940()
{
    RwUInt32 var_4;
    RwInt32 local_8;

    local_8 = 0;
    for (var_4 = 0; var_4 < unk_2C; var_4++) {
        if (unk_30[var_4].unk_04 != -1)
            local_8++;
    }
    return local_8;
}
// match: ?sub_7C9A0@type_7C8D0@@QAEMH@Z @ 0x0007C9A0
RwReal type_7C8D0::sub_7C9A0(RwInt32 arg_0)
{
    RwInt32 var_4;

    var_4 = arg_0 & 0xFF;
    return unk_30[var_4].unk_20;
}
// match: ?sub_7C9D0@type_7C8D0@@QAE_NM@Z @ 0x0007C9D0
bool type_7C8D0::sub_7C9D0(RwReal arg_0)
{
    RwUInt32 var_4;
    bool local_5;

    local_5 = false;
    for (var_4 = 0; var_4 < unk_2C; var_4++) {
        unk_30[var_4].unk_24 = arg_0;
        local_5 = true;
    }
    return local_5;
}
