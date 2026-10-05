/*
 * The network player's motion curves (game/netplayer.h): a cubic set from a
 * Bezier segment, a straight segment, and the motion between two updates
 * that picks one of them.
 */
#include "game/netplayer.h"

// A compiled-out check of a curve: no code, but its registers move on by
// the loads its condition would make (docs/toolchain.md); the condition is
// not known and is chosen for its load.
#define CURVE_CHECK(e) { if (!(e)) { } }
// A compiled-out check that kept a local of its own: the motion's fit
// (sub_1FAF00) has a slot no instruction touches between its direction's
// temporaries and the straight segment's.
inline void CURVE_CHECK_SLOT()
{
    RwInt32 check_0;
}

// match: ??0type_1FA6E0@@QAE@XZ @ 0x001FA6E0
type_1FA6E0::type_1FA6E0()
{
}

// match: ?sub_1FA780@type_1FA6E0@@QAEXABUtype_1F8560_v@@000@Z @ 0x001FA780
void type_1FA6E0::sub_1FA780(const type_1F8560_v &arg_0, const type_1F8560_v &arg_4, const type_1F8560_v &arg_8,
                             const type_1F8560_v &arg_C)
{
    type_1F8560_v var_C = arg_0 + arg_4;
    type_1F8560_v var_18 = arg_8 + arg_C;
    unk_18 = 3.0f * (var_C - arg_0);
    unk_0C = 3.0f * (var_18 - var_C) - unk_18;
    unk_00 = arg_8 - arg_0 - unk_18 - unk_0C;
    unk_24 = arg_0;
}

// match: ?sub_1FAB10@type_1FA6E0@@QAE?AUtype_1F8560_v@@M@Z @ 0x001FAB10
type_1F8560_v type_1FA6E0::sub_1FAB10(RwReal arg_0)
{
    CURVE_CHECK(&unk_18);
    RwReal x8;
    RwReal bp_4 = (x8 = arg_0 * arg_0) * arg_0;
    type_1F8560_v var14 = arg_0 * unk_18;
    type_1F8560_v w20 = x8 * unk_0C;
    type_1F8560_v t2C = bp_4 * unk_00;
    type_1F8560_v fp_38 = t2C + unk_24;
    type_1F8560_v bp_44 = fp_38 + w20;
    return bp_44 + var14;
}

// match: ?sub_1FACC0@type_1FA6E0@@QAE?AUtype_1F8560_v@@M@Z @ 0x001FACC0
type_1F8560_v type_1FA6E0::sub_1FACC0(RwReal arg_0)
{
    CURVE_CHECK(&unk_18);
    RwReal bp_4 = arg_0 * arg_0;
    type_1F8560_v r10 = 2.0f * unk_0C;
    type_1F8560_v lcl_1C = arg_0 * r10;
    type_1F8560_v w28 = 3.0f * unk_00;
    type_1F8560_v t34 = bp_4 * w28;
    type_1F8560_v bp_40 = t34 + lcl_1C;
    return bp_40 + unk_18;
}

// match: ??0type_1FAE60@@QAE@XZ @ 0x001FAE60
type_1FAE60::type_1FAE60()
{
    unk_60 = 0;
    unk_64 = 0;
}

// match: ?sub_1FAF00@type_1FAE60@@QAEXABUtype_1F8560_v@@0M00M@Z @ 0x001FAF00
void type_1FAE60::sub_1FAF00(const type_1F8560_v &arg_0, const type_1F8560_v &arg_4, RwReal arg_8,
                             const type_1F8560_v &arg_C, const type_1F8560_v &arg_10, RwReal arg_14)
{
    unk_60 = arg_8;
    unk_64 = arg_14 - arg_8;
    type_1F8560_v var_24 = arg_10 - arg_4;
    type_1F8560_v var_C = arg_C - arg_0;
    type_1F8560_v var_18 = var_C.normal();
    if (var_C.dot(var_C) < var_24.dot(var_18) * unk_64)
    {
        CURVE_CHECK_SLOT();
        unk_30.set(arg_0, arg_8, arg_C, arg_14);
        unk_50 = var_C / unk_64;
        unk_5C = 0;
    }
    else
    {
        unk_00.sub_1FA780(arg_0, unk_64 / 3.0f * arg_4, arg_C, unk_64 / 3.0f * -arg_10);
        unk_5C = 1;
    }
}

// match: ?sub_1FB250@type_1FAE60@@QAE?AUtype_1F8560_v@@M@Z @ 0x001FB250
type_1F8560_v type_1FAE60::sub_1FB250(RwReal arg_0)
{
    switch (unk_5C)
    {
    case 1:
        return unk_00.sub_1FAB10((arg_0 - unk_60) / unk_64);
    case 0:
        return unk_30.sub_1FB3C0(arg_0);
    }
    CURVE_CHECK(unk_5C < 2);
    return type_1F8560_v();
}

// match: ?sub_1FB3C0@type_1FB3C0@@QAE?AUtype_1F8560_v@@M@Z @ 0x001FB3C0
// (The straight segment's point, an inline the compiler kept out of line
// here, with its frame reserved in sub_1FB250.)

// match: ?sub_1FB2E0@type_1FAE60@@QAE?AUtype_1F8560_v@@M@Z @ 0x001FB2E0
type_1F8560_v type_1FAE60::sub_1FB2E0(RwReal arg_0)
{
    switch (unk_5C)
    {
    case 1:
        return unk_00.sub_1FACC0((arg_0 - unk_60) / unk_64) / (RwReal)(RwDouble)unk_64;
    case 0:
        return unk_50;
    }
    CURVE_CHECK(unk_5C < 2);
    return type_1F8560_v();
}
