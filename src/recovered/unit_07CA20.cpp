// The animation keyframes: decompressing the game's compressed keys and
// interpolating between them. The file's original name is not recovered
// (M1), so it is named for its start address.

#include <math.h>
#include <string.h>

#include "rw/ostypes.h"
#include "game/functions.h"
#include "types/animkey.h"
#include "types/animobjpool.h"
#include "types/type_3D3548.h"
#include "rw/badevice.h"
#ifdef CODFH_WIN32
// (the port: the shared key tables' words, port/src/animkeyref.cpp)
RwInt32 port_anim_key_pack(void *p);
void *port_anim_key_unpack(RwInt32 v);
#endif

#if !defined(CODFH_SP) || CODFH_SP_PART != 2 // single player compiles the interpolators (sub_7FC90 on)
                                             // in another file (src/sp/units/sp_unit_07CA20_2.cpp)

// Its data definitions (PLAN M5), in the image's address order.
// 0x00428C10
RwInt32 dword_428C10[64] = {
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    7,
    9,
    8,
    24,
    25,
    26,
    27,
    28,
    29,
    30,
    31,
    32,
    33,
    34,
    35,
    36,
    37,
    10,
    11,
    12,
    13,
    14,
    15,
    16,
    17,
    18,
    19,
    20,
    21,
    22,
    23,
    38,
    43,
    44,
    45,
    46,
    39,
    40,
    41,
    42,
    47,
    48,
    49,
    50,
    51,
    52,
    53,
    54,
    55,
    56,
    57,
    58,
    59,
    60,
    61,
    62,
    63,
};
// 0x00428D10
RwInt32 dword_428D10[25] = {
    0,
    1,
    2,
    3,
    5,
    4,
    6,
    9,
    8,
    7,
    10,
    12,
    11,
    14,
    13,
    18,
    17,
    16,
    15,
    20,
    19,
    24,
    23,
    22,
    21,
};
// 0x00428D74
RwInt32 dword_428D74[9] = {
    0,
    2,
    6,
    3,
    7,
    4,
    8,
    5,
    9,
};
// 0x00428D98
RwInt32 dword_428D98[30] = {
    130,
    120,
    135,
    235,
    140,
    240,
    145,
    245,
    150,
    250,
    151,
    251,
    152,
    252,
    153,
    253,
    154,
    254,
    155,
    255,
    156,
    256,
    157,
    257,
    158,
    258,
    159,
    259,
    202,
    203,
};
// 0x00428E10
RwInt32 dword_428E10 = 1;
// 0x0044A5D0
RwMatrix src2;
// 0x0044B638
RtAnimInterpolatorInfo dword_44B638[16];
// 0x0044BA38
RwInt32 dword_44BA38;
#ifndef CODFH_SP // file-static in single player (the second file defines them)
// 0x0044BA3C
void *dword_44BA3C;
// 0x0044BA40
void *dword_44BA40;
#endif
// End of its data definitions.







// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).
type_16C2A0 dword_44BA54;
type_16C2A0 dword_44BA74;
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: __real@47000000 @ 0x003D3CBC
// match: __real@42652ee2 @ 0x003D3CC0
// match: __real@426ffefa @ 0x003D3CC4
// match: __real@c7000000 @ 0x003D3CCC
// match: __real@46fffe00 @ 0x003D3CD0
// match: ??_C@_0BM@BFKGAKCF@_animInterpolatorHeaderPool?$AA@ @ 0x003D3CD4
// match: ??_C@_0BG@FNKOHPJI@_animInterpolatorPool?$AA@ @ 0x003D3CF0
// match: ??_C@_0EI@JHFAACJE@WARNING?$CB?5Animation?5is?5an?5old?5ver@ @ 0x003D3D08
// match: ??_C@_0BB@LNJAHGAD@this?5is?5bad?5shit?$AA@ @ 0x003D3D50
// match: .CRT$XCU+0 @ 0x00426DF0
// match: .CRT$XCU+4 @ 0x00426DF4
// match: ?dword_428C10@@3PAHA @ 0x00428C10
// match: ?dword_428D10@@3PAHA @ 0x00428D10
// match: ?dword_428D74@@3PAHA @ 0x00428D74
// match: ?dword_428D98@@3PAHA @ 0x00428D98
// match: ?dword_428E10@@3HA @ 0x00428E10

// match: _$E1 @ 0x00309C00
// match: _$E2 @ 0x0030DE70
// match: _$E4 @ 0x00309C20
// match: _$E5 @ 0x0030DE80
// match: ?sub_7CA20@@YAXPAURtQuat@@PAFH@Z @ 0x0007CA20
// sp-match: ?sub_7CA20@@YAXPAURtQuat@@PAFH@Z @ 0x00065C10
// sp-match: _$E1 @ 0x0021C690
// sp-match: _$E4 @ 0x0021C6B0
// sp-match: _$E2 @ 0x0021E2A0
// sp-match: _$E5 @ 0x0021E2B0

// A unit quaternion from three shorts (32768ths), its real part recovered.
void sub_7CA20(RtQuat *arg_0, RwInt16 *arg_4, RwInt32 arg_8)
{
    RtQuat *var_4;

    var_4 = arg_0;
    var_4->imag.x = arg_4[0] / 32768.0f;
    var_4->imag.y = arg_4[1] / 32768.0f;
    var_4->imag.z = arg_4[2] / 32768.0f;
    var_4->real = sqrtf_(1.0f - (var_4->imag.x * var_4->imag.x + var_4->imag.y * var_4->imag.y
                                 + var_4->imag.z * var_4->imag.z));
}

// match: ?sub_7CAC0@@YAXPAGPAURwV3d@@@Z @ 0x0007CAC0
// sp-match: ?sub_7CAC0@@YAXPAGPAURwV3d@@@Z @ 0x00065C80
// A vector from three half floats.
void sub_7CAC0(RwUInt16 *arg_0, RwV3d *arg_4)
{
    RwInt32 var_3C[15];         // unused; the image reserves them

    arg_4->x = sub_7CB10(arg_0[0]);
    arg_4->y = sub_7CB10(arg_0[1]);
    arg_4->z = sub_7CB10(arg_0[2]);
}

// match: ?sub_7CB10@@YAMG@Z @ 0x0007CB10
// A half float (1:5:10) as a float.
#ifdef CODFH_SP
inline // SP has no out-of-line copy: every call expands (0x65C80, 0x65D30)
#endif
RwReal sub_7CB10(RwUInt16 arg_0)
{
    RwReal var_4;
    RwInt32 v8;
    RwInt32 stk_C;
    RwInt32 var_10;
    RwInt32 lv_14;

    lv_14 = arg_0 >> 15;
#ifdef CODFH_SP // shape: unsigned shift (shr, mask 0x3FFFDF at 0x65C80)
    stk_C = (RwUInt32)(arg_0 & ~0x8000) >> 10;
#else
    stk_C = (arg_0 & ~0x8000) >> 10;
#endif
    v8 = arg_0 & 0x3FF;
    if (stk_C != 0)
        stk_C += 0x77;
    var_10 = lv_14 << 31 | stk_C << 23 | v8 << 13;
    var_4 = *(RwReal *)&var_10;
    return var_4;
}

// match: ?sub_7CB80@@YAXPAXPAUtype_7CB80@@1M@Z @ 0x0007CB80
// sp-match: ?sub_7CB80@@YAXPAXPAUtype_7CB80@@1M@Z @ 0x00066380
// Interpolates between the keys arg_4 and arg_8 at the time arg_C.
void sub_7CB80(void *arg_0, type_7CB80 *arg_4, type_7CB80 *arg_8, RwReal arg_C)
{
    RwReal var_4;
    type_7CB80 *v8;
    type_7CB80 *varC;

    v8 = arg_4;
    varC = arg_8;
    var_4 = (arg_C - v8->unk_00) / (varC->unk_00 - v8->unk_00);
    sub_7CBD0(arg_0, arg_4, arg_8, var_4);
}

// match: ?sub_7CBD0@@YAXPAXPAUtype_7CB80@@1M@Z @ 0x0007CBD0
// sp-match: ?sub_7CBD0@@YAXPAXPAUtype_7CB80@@1M@Z @ 0x00066100
// Blends the pose keys arg_4 and arg_8 by arg_C into arg_0: each node either
// key has, slerped (and its translation lerped) when both have it.
void sub_7CBD0(void *arg_0, type_7CB80 *arg_4, type_7CB80 *arg_8, RwReal arg_C)
{
    type_7CBD0 *v48;
    type_7CBD0 *slot_44;
    RtQuat *l40;
    RtQuat *var_3C;
    type_7CBD0_t *v38;
    type_7CBD0 *v34;
    type_7CBD0_t *v30;
    type_7CBD0_hdr *var_2C;
    type_7CBD0_t *loc28;
    RwInt32 slot_24;
    RwUInt64 v20;
    type_7CBD0_hdr *local_18;
    RtQuat *local_14;
    RwUInt64 local_10;
    type_7CBD0_hdr *lv_8;
    RwUInt32 var_4;

    v48 = (type_7CBD0 *)arg_0;
    v34 = (type_7CBD0 *)arg_4;
    slot_44 = (type_7CBD0 *)arg_8;
    lv_8 = v48->unk_04;
    var_2C = v34->unk_04;
    local_18 = slot_44->unk_04;
    slot_24 = 0;
    v20 = 0;
    v48->unk_00 = v34->unk_00;
    local_10 = 1;
    l40 = v48->unk_10;
    var_3C = v34->unk_10;
    local_14 = slot_44->unk_10;
    loc28 = (type_7CBD0_t *)&v48->unk_10[lv_8->unk_00];
    v30 = (type_7CBD0_t *)&v34->unk_10[var_2C->unk_00];
    v38 = (type_7CBD0_t *)&slot_44->unk_10[local_18->unk_00];
    for (var_4 = 0; var_4 < lv_8->unk_00; var_4++) {
        local_10 = (RwUInt64)1 << var_4;
        if ((var_2C->unk_08 & local_10) == 0) {
            if ((local_18->unk_08 & local_10) == 0)
                continue;
            l40[var_4] = local_14[var_4];
            if (local_10 & lv_8->unk_10)
                loc28[slot_24].unk_00 = v38[slot_24].unk_00;
        } else if ((local_18->unk_08 & local_10) == 0) {
            l40[var_4] = var_3C[var_4];
            if (local_10 & lv_8->unk_10)
                loc28[slot_24].unk_00 = v30[slot_24].unk_00;
        } else {
            sub_13FBC0(&l40[var_4], &var_3C[var_4], &local_14[var_4], arg_C);
            if (local_10 & lv_8->unk_10) {
                loc28[slot_24].unk_00.x = v30[slot_24].unk_00.x
                                          + (v38[slot_24].unk_00.x - v30[slot_24].unk_00.x) * arg_C;
                loc28[slot_24].unk_00.y = v30[slot_24].unk_00.y
                                          + (v38[slot_24].unk_00.y - v30[slot_24].unk_00.y) * arg_C;
                loc28[slot_24].unk_00.z = v30[slot_24].unk_00.z
                                          + (v38[slot_24].unk_00.z - v30[slot_24].unk_00.z) * arg_C;
            }
        }
        if (local_10 & lv_8->unk_10)
            slot_24++;
        v20 |= local_10;
    }
    lv_8->unk_08 = v20;
}

// match: ?sub_7CF40@@YAXPAUtype_7CF40@@PAUtype_7CBD0@@@Z @ 0x0007CF40
// sp-match: ?sub_7CF40@@YAXPAUtype_7CF40@@PAUtype_7CBD0@@@Z @ 0x00067880
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_7CF40(type_7CF40 *arg_0, type_7CBD0 *arg_4)
{
    RwInt32 var_8C[15];         // unused; the image reserves them
    RwInt16 (*loc28)[3];
    RwInt16 (*var_C)[3];
    RwUInt64 var_50;
    RwUInt64 local_48;
    RtQuat local_40;
    type_7CBD0_t *v30;
    type_7CF40 *l2C;
    RwInt32 slot_24;
    RwInt32 v20;
    RtQuat *loc1C;
    type_7CBD0 *bp_18;
    RwInt32 var14;
    RwUInt32 r10;
    RwUInt32 bp_8;
    type_7CBD0_hdr *bp_4;

    bp_18 = arg_4;
    l2C = arg_0;
    bp_4 = bp_18->unk_04;
    l2C->unk_12 = (RwInt16)(bp_18->unk_00 * 60.0f);
    loc1C = bp_18->unk_10;
    loc28 = l2C->unk_14;
    var14 = 0;
    for (bp_8 = 0; bp_8 < bp_4->unk_00; bp_8++) {
        local_48 = l2C->unk_00;
        if (local_48 & (RwUInt64)1 << bp_8) {
            sub_7FB40(loc28[var14], &loc1C[bp_8], 0);
            var14++;
        }
    }
    v30 = (type_7CBD0_t *)&bp_18->unk_10[bp_4->unk_00];
    var_C = (RwInt16 (*)[3])(((RwUInt32)l2C + (RwUInt32)(l2C->unk_00_56 * 6) + 0x17) & ~3);
    slot_24 = -1;
    r10 = 0;
    v20 = 0;
    if (bp_4->unk_10) {
        for (bp_8 = 0; bp_8 < bp_4->unk_02; bp_8++) {
            while (((RwUInt64)1 << r10 & bp_4->unk_10) == 0)
                r10++;
            if (r10 == bp_4->unk_05)
                slot_24 = bp_8;
            var_50 = l2C->unk_08;
            if (var_50 & (RwUInt64)1 << r10) {
                sub_7D220(&v30[bp_8].unk_00, (RwUInt16 *)var_C[v20]);
                v20++;
            }
            r10++;
        }
    }
    if (slot_24 >= 0) {
        local_40 = loc1C[bp_4->unk_05];
        local_40.imag.x = local_40.imag.z = 0;
        sub_13FB00(&local_40, &local_40);
#ifdef CODFH_SP // shape: 360/pi and 64 two multiplies (0x67A4B)
        l2C->unk_10 = (RwInt16)(64.0f * (rad2deg_(atan2f_(local_40.imag.y, local_40.real)) * 2.0f));
#else
        l2C->unk_10 = (RwInt16)(rad2deg_(2.0f * atan2f_(local_40.imag.y, local_40.real)) * 64.0f);
#endif
    }
}

// match: ?sub_7D220@@YAXPAURwV3d@@PAG@Z @ 0x0007D220
// sp-match: ?sub_7D220@@YAXPAURwV3d@@PAG@Z @ 0x00065D30
void sub_7D220(RwV3d *arg_0, RwUInt16 *arg_4)
{
    RwInt32 var_3C[15];         // unused; the image reserves them

    arg_4[0] = sub_7D270(arg_0->x);
    arg_4[1] = sub_7D270(arg_0->y);
    arg_4[2] = sub_7D270(arg_0->z);
}

// match: ?sub_7D270@@YAGM@Z @ 0x0007D270
#ifdef CODFH_SP
inline // SP has no out-of-line copy: every call expands (0x65C80, 0x65D30)
#endif
RwUInt16 sub_7D270(RwReal arg_0)
{
    RwUInt16 var_4;
    RwUInt32 v8;
    RwUInt32 stk_C;
    RwUInt32 var_10;
    RwUInt32 lv_14;

    var_10 = *(RwUInt32 *)&arg_0;
    lv_14 = var_10 >> 31;
    stk_C = (var_10 & 0x7FFFFFFF) >> 23;
    v8 = var_10 & 0x7FFFFF;
    if (stk_C != 0) {
        if (stk_C < 0x77)
            stk_C = 0;
        else
            stk_C -= 0x77;
        stk_C &= 0x1F;
    }
    var_4 = (RwUInt16)(lv_14 << 15 | stk_C << 10 | v8 >> 13);
    return var_4;
}

// match: ?sub_7D2F0@@YAXPAUtype_7CBD0@@PAUtype_80300@@@Z @ 0x0007D2F0
// sp-match: ?sub_7D2F0@@YAXPAUtype_7CBD0@@PAUtype_80300@@@Z @ 0x000663B0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_7D2F0(type_7CBD0 *arg_0, type_80300 *arg_4)
{
    RwReal var_8B4;
    RwReal var_8B0;
    RwReal ebp_8AC;
    RwReal var_8A8;
    type_7CBD0 *ebp_8A4;
    RwReal w8A0;
    RtQuat *var_89C;
    type_7CBD0_t loc898;
    type_7DCA0_q stk_888[0x40];
    RtQuat bp_704;
    RwInt32 bp_6F4;
    type_7DCA0_q var_6F0[0x40];
    type_80300 *m_570;
    type_7DCA0 *q56C;
    RwInt32 *r568;
    type_7CBD0_t r564;
    type_7DCA0 *m_554;
    RwInt32 var550;
    RwInt32 stk_54C;
    type_7CBD0_t *m_548;
    RwInt32 frm_544;
    type_7DCA0_q var_540[0x40];
    RwReal t3C0[0x40];
    RwInt32 m_2C0;
    RwInt32 *slot_2BC;
    RwReal frm_2B8[0x40];
    RwUInt64 var_1B8;
    RwUInt64 x1B0;
    RtQuat stk_1A8;
    RtAnimAnimation *x198;
    type_7CBD0_hdr *loc194;
    RwInt32 x190;
    type_7CBD0_hdr *l18C;
    type_7DCA0_q bp_188[0x40];
    RwInt32 bp_4;

    m_570 = arg_4;
    x198 = m_570->unk_00;
    ebp_8A4 = arg_0;
    frm_544 = 0;
    l18C = (type_7CBD0_hdr *)x198->pFrames;
    r568 = (RwInt32 *)(l18C + 1);
    var550 = 0;
    for (x190 = 0; x190 < l18C->unk_00; x190++)
    {
        var_1B8 = (RwUInt64)1 << x190;
        if (l18C->unk_08 & var_1B8)
        {
            slot_2BC = r568;
            if ((bp_4 = *slot_2BC & 0x7FFF) == 0)
            {
                bp_188[var550].unk_00[0] = bp_188[var550].unk_00[1] = bp_188[var550].unk_00[2] = 0;
                var_540[var550].unk_00[0] = var_540[var550].unk_00[1] = var_540[var550].unk_00[2] = 0;
                t3C0[var550] = 0;
                var550++;
                r568 = slot_2BC + 1;
                continue;
            }
            if (*slot_2BC & 0x80000000)
            {
#ifdef CODFH_WIN32
                m_554 = (type_7DCA0 *)port_anim_key_unpack(*slot_2BC);
#else
                m_554 = (type_7DCA0 *)(*slot_2BC & 0x3FFFFFFF);
#endif
                r568 = slot_2BC + 1;
            }
            else
            {
                m_554 = (type_7DCA0 *)(slot_2BC + 1);
                r568 = (RwInt32 *)(m_554 + bp_4);
            }
            stk_54C = m_570->unk_74[x190];
            m_2C0 = stk_54C;
            w8A0 = m_554[stk_54C].unk_06 / 59.999f;
#ifdef CODFH_EXTRA_LOGS // (the GameCube build, main.dol 0x80068A6C)
            if (w8A0 > m_570->unk_E4)
                sub_19A750("%s: Anim goes back!!!\n", "SkelKeyFrameUncompress");
#endif
            while (w8A0 < m_570->unk_E4)
            {
                m_2C0 = stk_54C;
                stk_54C++;
                if (stk_54C >= bp_4)
                {
                    break;
                }
                w8A0 = m_554[stk_54C].unk_06 / 59.999f;
            }
            m_570->unk_74[x190] = (RwInt16)m_2C0;
            bp_188[var550] = m_554[m_2C0].unk_00;
            var_540[var550] = m_554[m_2C0 + 1].unk_00;
            var_8A8 = m_554[m_2C0].unk_06 / 59.999f;
            ebp_8AC = m_554[m_2C0 + 1].unk_06 / 59.999f;
#ifdef CODFH_SP // shape: single player computes the numerator as its own step (SP 0x663B0)
            RwReal fNumerator = m_570->unk_E4 - var_8A8;
            t3C0[var550] = fNumerator / (ebp_8AC - var_8A8);
#else
            t3C0[var550] = (m_570->unk_E4 - var_8A8) / (ebp_8AC - var_8A8);
#endif
            var550++;
        }
    }
    for (x190 = 0; x190 < l18C->unk_00; x190++)
    {
        var_1B8 = (RwUInt64)1 << x190;
        if (l18C->unk_10 & var_1B8)
        {
            slot_2BC = r568;
            if ((bp_4 = *slot_2BC & 0x7FFF) == 0)
            {
                stk_888[x190].unk_00[0] = stk_888[x190].unk_00[1] = stk_888[x190].unk_00[2] = 0;
                var_6F0[x190].unk_00[0] = var_6F0[x190].unk_00[1] = var_6F0[x190].unk_00[2] = 0;
                frm_2B8[x190] = 0;
                r568 = slot_2BC + 1;
                continue;
            }
            if (*slot_2BC & 0x80000000)
            {
#ifdef CODFH_WIN32
                q56C = (type_7DCA0 *)port_anim_key_unpack(*slot_2BC);
#else
                q56C = (type_7DCA0 *)(*slot_2BC & 0x3FFFFFFF);
#endif
                r568 = slot_2BC + 1;
            }
            else
            {
                q56C = (type_7DCA0 *)(slot_2BC + 1);
                r568 = (RwInt32 *)(q56C + bp_4);
            }
            stk_54C = m_570->unk_04[x190];
            bp_6F4 = stk_54C;
            w8A0 = q56C[stk_54C].unk_06 / 59.999f;
            while (w8A0 < m_570->unk_E4)
            {
                bp_6F4 = stk_54C;
                stk_54C++;
                if (stk_54C >= bp_4)
                {
                    break;
                }
                w8A0 = q56C[stk_54C].unk_06 / 59.999f;
            }
            m_570->unk_04[x190] = (RwInt16)bp_6F4;
            stk_888[x190] = q56C[bp_6F4].unk_00;
            var_6F0[x190] = q56C[bp_6F4 + 1].unk_00;
            var_8B0 = q56C[bp_6F4].unk_06 / 59.999f;
            var_8B4 = q56C[bp_6F4 + 1].unk_06 / 59.999f;
            frm_2B8[x190] = (m_570->unk_E4 - var_8B0) / (var_8B4 - var_8B0);
        }
    }
    ebp_8A4->unk_00 = m_570->unk_E4;
    ebp_8A4->unk_04 = l18C;
    loc194 = ebp_8A4->unk_04;
    x1B0 = 1;
    var_89C = ebp_8A4->unk_10;
    m_548 = (type_7CBD0_t *)&ebp_8A4->unk_10[loc194->unk_00];
    var550 = 0;
    for (x190 = 0; x190 < loc194->unk_00; x190++)
    {
        x1B0 = (RwUInt64)1 << x190;
        if (x1B0 & l18C->unk_08)
        {
            sub_7CA20(&bp_704, bp_188[var550].unk_00, 0);
            sub_7CA20(&stk_1A8, var_540[var550].unk_00, 0);
            sub_13FBC0(&var_89C[x190], &bp_704, &stk_1A8, t3C0[var550]);
            var550++;
        }
        if (x1B0 & l18C->unk_10)
        {
            sub_7CAC0((RwUInt16 *)stk_888[x190].unk_00, &r564.unk_00);
            sub_7CAC0((RwUInt16 *)var_6F0[x190].unk_00, &loc898.unk_00);
            m_548[frm_544].unk_00.x = (loc898.unk_00.x - r564.unk_00.x) * frm_2B8[x190] + r564.unk_00.x;
            m_548[frm_544].unk_00.y = (loc898.unk_00.y - r564.unk_00.y) * frm_2B8[x190] + r564.unk_00.y;
            m_548[frm_544].unk_00.z = (loc898.unk_00.z - r564.unk_00.z) * frm_2B8[x190] + r564.unk_00.z;
            frm_544++;
        }
    }
}

// match: ?sub_7DCA0@@YAPAURtAnimAnimation@@PAU1@PAURwStream@@PAUtype_7CBD0_hdr@@@Z @ 0x0007DCA0
// sp-match: ?sub_7DCA0@@YAPAURtAnimAnimation@@PAU1@PAURwStream@@PAUtype_7CBD0_hdr@@@Z @ 0x00066C70
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RtAnimAnimation *sub_7DCA0(RtAnimAnimation *arg_0, RwStream *arg_4, type_7CBD0_hdr *arg_8)
{
    RwInt32 l4;
    RwInt32 var_8;
    RwUInt32 *fp_C;
    type_7DCA0 *local_10;
    RwUInt32 *stk_14;
    type_7DCA0 *loc18;

    stk_14 = (RwUInt32 *)(arg_8 + 1);
    for (var_8 = 0; var_8 < arg_8->unk_01; var_8++)
    {
        fp_C = stk_14;
        if (!RwStreamReadInt32(arg_4, (RwInt32 *)fp_C, sizeof(RwInt32)))
        {
            return 0;
        }
        if ((l4 = *fp_C & 0x7FFF) == 0)
        {
            stk_14 = fp_C + 1;
        }
        else if (*fp_C & 0x80000000)
        {
            stk_14 = fp_C + 1;
        }
        else
        {
            stk_14 = fp_C + 1;
            local_10 = (type_7DCA0 *)stk_14;
            if (!RwStreamReadInt16(arg_4, (RwInt16 *)local_10, l4 * sizeof(type_7DCA0)))
            {
                return 0;
            }
            local_10 += l4;
            stk_14 = (RwUInt32 *)local_10;
        }
    }
    for (var_8 = 0; var_8 < arg_8->unk_02; var_8++)
    {
        fp_C = stk_14;
        if (!RwStreamReadInt32(arg_4, (RwInt32 *)fp_C, sizeof(RwInt32)))
        {
            return 0;
        }
        l4 = *fp_C & 0x7FFF;
        stk_14 = fp_C + 1;
        if (l4 > 0)
        {
            loc18 = (type_7DCA0 *)stk_14;
            if (!RwStreamReadInt16(arg_4, (RwInt16 *)loc18, l4 * sizeof(type_7DCA0)))
            {
                return 0;
            }
            loc18 += l4;
            stk_14 = (RwUInt32 *)loc18;
        }
    }
    return arg_0;
}

// match: ?sub_7DE10@@YAHXZ @ 0x0007DE10
// sp-match: ?sub_7DE10@@YAHXZ @ 0x00067A70
RwInt32 sub_7DE10()
{
    RtAnimInterpolatorInfo var_40;

    var_40.typeID = 0x1142;
    var_40.unk_04 = (void *)sub_7DEB0;
    var_40.unk_08 = (void *)sub_7CBD0;
    var_40.unk_0C = (void *)sub_7CB80;
    var_40.unk_10 = (void *)sub_7CF40;
    var_40.unk_14 = (void *)sub_7D2F0;
    var_40.unk_18 = (void *)sub_7E3A0;
    var_40.unk_1C = sub_19A750;
    var_40.unk_20 = (void *)sub_7E420;
    var_40.unk_24 = sub_7E870;
    var_40.unk_28 = (void *)sub_7E990;
    var_40.unk_2C = (void *)sub_7ECB0;
    var_40.unk_30 = (void *)sub_7EE30;
    var_40.unk_34 = (void *)sub_7F0E0;
    var_40.unk_38 = (void *)sub_7F370;
    var_40.unk_3C = (void *)sub_7F2A0;
    if (!sub_7FD90(&var_40))
    {
        return 0;
    }
    return 1;
}

#ifdef CODFH_SP
static void sub_7E230(RtQuat *arg_0, RwMatrixTag *arg_4, RwUInt8 arg_8);
#endif

// match: ?sub_7DEB0@@YAXPAURwMatrixTag@@PAUtype_7CBD0@@H@Z @ 0x0007DEB0
// sp-match: ?sub_7DEB0@@YAXPAURwMatrixTag@@PAUtype_7CBD0@@H@Z @ 0x00065F20
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_7DEB0(RwMatrixTag *arg_0, type_7CBD0 *arg_4, RwInt32 arg_8)
{
    type_7CBD0_hdr *l4;
    type_7CBD0 *var_8;
    RwV3d *fp_C;
    RwUInt32 local_10;
    RwInt32 stk_14;
    type_7CBD0_t *lcl_18;
    RtQuat *fp_1C;
    RwMatrixTag *ebp_20;

    var_8 = arg_4;
    ebp_20 = arg_0;
    l4 = var_8->unk_04;
    fp_C = var_8->unk_08;
    fp_1C = var_8->unk_10;
    for (local_10 = 0; local_10 < l4->unk_00; local_10++)
    {
        if (arg_8 == 1)
        {
            if ((RwReal)fabs((RwDouble)fp_1C[dword_428C10[local_10]].real) <= 1.0f)
            {
                sub_7E230(&fp_1C[dword_428C10[local_10]], ebp_20, 1);
            }
            else
            {
                RwMatrixSetIdentity(ebp_20);
            }
        }
        else
        {
            if ((RwReal)fabs((RwDouble)fp_1C[local_10].real) <= 1.0f)
            {
                sub_7E230(&fp_1C[local_10], ebp_20, 0);
            }
            else
            {
                RwMatrixSetIdentity(ebp_20);
            }
        }
        if (fp_C)
        {
            ebp_20->pos.x = fp_C[local_10].x;
            ebp_20->pos.y = fp_C[local_10].y;
            ebp_20->pos.z = fp_C[local_10].z;
        }
        ebp_20++;
    }
    ebp_20 = arg_0;
    lcl_18 = (type_7CBD0_t *)&var_8->unk_10[l4->unk_00];
    stk_14 = 0;
    if (l4->unk_10)
    {
        for (local_10 = 0; local_10 < l4->unk_02; local_10++)
        {
            while (!((RwUInt64)1 << stk_14 & l4->unk_10))
            {
                stk_14++;
            }
            if (arg_8 == 1)
            {
                ebp_20[stk_14].pos.x = -lcl_18[local_10].unk_00.x;
            }
            else
            {
                ebp_20[stk_14].pos.x = lcl_18[local_10].unk_00.x;
            }
            ebp_20[stk_14].pos.y = lcl_18[local_10].unk_00.y;
            ebp_20[stk_14].pos.z = lcl_18[local_10].unk_00.z;
            stk_14++;
        }
    }
}

// match: ?sub_7E230@@YAXPAURtQuat@@PAURwMatrixTag@@E@Z @ 0x0007E230
// sp-match: ?sub_7E230@@YAXPAURtQuat@@PAURwMatrixTag@@E@Z @ 0x00065E00
#ifdef CODFH_SP // static: SP 0x65E00 takes arg_0 in ecx and arg_4 in eax
static
#endif
void sub_7E230(RtQuat *arg_0, RwMatrixTag *arg_4, RwUInt8 arg_8)
{
    RtQuat var_10;

    var_10 = *arg_0;
    if (arg_8)
    {
        var_10.imag.y = var_10.imag.y * -1.0f;
        var_10.imag.z = var_10.imag.z * -1.0f;
    }
    RtQuatUnitConvertToMatrix(&var_10, arg_4);
}

// match: ?sub_7E3A0@@YAXPAUtype_7CBD0@@0@Z @ 0x0007E3A0
// sp-match: ?sub_7E3A0@@YAXPAUtype_7CBD0@@0@Z @ 0x00066980
void sub_7E3A0(type_7CBD0 *arg_0, type_7CBD0 *arg_4)
{
    type_7CBD0_hdr *var_4;
    type_7CBD0_hdr *v8;
    type_7CBD0 *stk_C;
    type_7CBD0 *var_10;

    var_10 = arg_0;
    stk_C = arg_4;
    v8 = stk_C->unk_04;
    var_4 = var_10->unk_04;
    *var_4 = *v8;
    memcpy(var_10->unk_10, stk_C->unk_10, v8->unk_00 * sizeof(RtQuat) + v8->unk_02 * sizeof(RtQuat));
}

// match: ?sub_7E420@@YAXPAUtype_7CBD0@@0@Z @ 0x0007E420
// sp-match: ?sub_7E420@@YAXPAUtype_7CBD0@@0@Z @ 0x000669E0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_7E420(type_7CBD0 *arg_0, type_7CBD0 *arg_4)
{
    type_7CBD0 *w48;
    type_7CBD0 *loc44;
    RtQuat *fp_40;
    type_7CBD0_t *ebp_3C;
    RtQuat lcl_38;
    type_7CBD0_hdr *q28;
    type_7CBD0_hdr *frm_24;
    type_7CBD0_t *t20;
    RwInt32 l1C;
    RwUInt32 m_18;
    RtQuat *ebp_14;
    RtQuat lv_10;

    w48 = arg_0;
    loc44 = arg_4;
    frm_24 = w48->unk_04;
    q28 = loc44->unk_04;
    *frm_24 = *q28;
    ebp_14 = w48->unk_10;
    fp_40 = loc44->unk_10;
    for (m_18 = 0; m_18 < q28->unk_00; m_18++)
    {
        ebp_14 = &w48->unk_10[m_18];
        fp_40 = &loc44->unk_10[m_18];
        lcl_38 = ebp_14[m_18];
        RtQuatReciprocalMacro(&lv_10, &fp_40[m_18]);
#ifdef CODFH_SP // the reciprocal read through a reference (SP 0x669E0: the address sums associate the image's way)
        {
            const RtQuat &q = lv_10;
            RtQuatMultiplyMacro(&ebp_14[m_18], &q, &lcl_38);
        }
#else
        RtQuatMultiplyMacro(&ebp_14[m_18], &lv_10, &lcl_38);
#endif
    }
    t20 = (type_7CBD0_t *)&w48->unk_10[q28->unk_00];
    ebp_3C = (type_7CBD0_t *)&loc44->unk_10[q28->unk_00];
    l1C = 0;
    if (q28->unk_10)
    {
        for (m_18 = 0; m_18 < q28->unk_02; m_18++)
        {
            RwInt32 var_50;

            while (!((RwUInt64)1 << l1C & q28->unk_10))
            {
                l1C++;
            }
            var_50 = l1C;
            if ((RwUInt64)1 << l1C & q28->unk_08)
            {
                RwV3dSub(&t20[var_50].unk_00, &t20[var_50].unk_00, &ebp_3C[var_50].unk_00);
            }
            l1C++;
        }
    }
}

// match: ?sub_7E870@@YAPAURtAnimAnimation@@PAURwStream@@PAU1@H@Z @ 0x0007E870
// sp-match: ?sub_7E870@@YAPAURtAnimAnimation@@PAURwStream@@PAU1@H@Z @ 0x00066D40
RtAnimAnimation *sub_7E870(RwStream *arg_0, RtAnimAnimation *arg_4, RwInt32 arg_8)
{
    type_7CBD0_hdr *var_4;

    var_4 = (type_7CBD0_hdr *)arg_4->pFrames;
    if (!RwStreamRead(arg_0, &var_4->unk_00, 1))
    {
        return 0;
    }
    if (!RwStreamRead(arg_0, &var_4->unk_01, 1))
    {
        return 0;
    }
    if (!RwStreamRead(arg_0, &var_4->unk_02, 1))
    {
        return 0;
    }
    if (!RwStreamRead(arg_0, &var_4->unk_03, 1))
    {
        return 0;
    }
    if (!RwStreamRead(arg_0, &var_4->unk_04, 1))
    {
        return 0;
    }
    if (!RwStreamRead(arg_0, &var_4->unk_05, 1))
    {
        return 0;
    }
    if (!RwStreamReadInt32(arg_0, (RwInt32 *)&var_4->unk_08, sizeof(RwUInt64)))
    {
        return 0;
    }
    if (!RwStreamReadInt32(arg_0, (RwInt32 *)&var_4->unk_10, sizeof(RwUInt64)))
    {
        return 0;
    }
    return sub_7DCA0(arg_4, arg_0, var_4);
}

#ifdef CODFH_SP
static bool sub_7EAB0(RtAnimAnimation *arg_0, RwStream *arg_4, type_7CBD0_hdr *arg_8);
#endif

// match: ?sub_7E990@@YAHPAURtAnimAnimation@@PAURwStream@@@Z @ 0x0007E990
// sp-match: ?sub_7E990@@YAHPAURtAnimAnimation@@PAURwStream@@@Z @ 0x00066F30
RwInt32 sub_7E990(RtAnimAnimation *arg_0, RwStream *arg_4)
{
    type_7CBD0_hdr *var_4;

    var_4 = (type_7CBD0_hdr *)arg_0->pFrames;
    if (!RwStreamWrite(arg_4, &var_4->unk_00, 1))
    {
        return 0;
    }
    if (!RwStreamWrite(arg_4, &var_4->unk_01, 1))
    {
        return 0;
    }
    if (!RwStreamWrite(arg_4, &var_4->unk_02, 1))
    {
        return 0;
    }
    if (!RwStreamWrite(arg_4, &var_4->unk_03, 1))
    {
        return 0;
    }
    if (!RwStreamWrite(arg_4, &var_4->unk_04, 1))
    {
        return 0;
    }
    if (!RwStreamWrite(arg_4, &var_4->unk_05, 1))
    {
        return 0;
    }
    if (!RwStreamWriteInt32(arg_4, (RwInt32 *)&var_4->unk_08, sizeof(RwUInt64)))
    {
        return 0;
    }
    if (!RwStreamWriteInt32(arg_4, (RwInt32 *)&var_4->unk_10, sizeof(RwUInt64)))
    {
        return 0;
    }
    return sub_7EAB0(arg_0, arg_4, var_4);
}

// match: ?sub_7EAB0@@YA_NPAURtAnimAnimation@@PAURwStream@@PAUtype_7CBD0_hdr@@@Z @ 0x0007EAB0
// sp-match: ?sub_7EAB0@@YA_NPAURtAnimAnimation@@PAURwStream@@PAUtype_7CBD0_hdr@@@Z @ 0x00066E00
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
#ifdef CODFH_SP // static: SP 0x66E00 takes no arg_0
static
#endif
bool sub_7EAB0(RtAnimAnimation *arg_0, RwStream *arg_4, type_7CBD0_hdr *arg_8)
{
    type_7DCA0 *m_18;
    RwInt32 *ebp_14;
    type_7DCA0 *lv_10;
    RwInt32 *slot_C;
    RwInt32 bp_8;
    RwInt32 bp_4;

    ebp_14 = (RwInt32 *)(arg_8 + 1);
    for (bp_8 = 0; bp_8 < arg_8->unk_01; bp_8++)
    {
        slot_C = ebp_14;
        if ((bp_4 = *slot_C & 0x7FFF) == 0)
        {
            if (!RwStreamWriteInt32(arg_4, slot_C, sizeof(RwInt32)))
            {
                return false;
            }
            ebp_14 = slot_C + 1;
        }
        else if (*slot_C & 0x80000000)
        {
            if (!RwStreamWriteInt32(arg_4, slot_C, sizeof(RwInt32)))
            {
                return false;
            }
            if (*slot_C & 0x40000000)
            {
                ebp_14 = slot_C + 1;
                lv_10 = (type_7DCA0 *)ebp_14;
                lv_10 += bp_4;
                ebp_14 = (RwInt32 *)lv_10;
            }
            else
            {
                ebp_14 = slot_C + 1;
            }
        }
        else
        {
            ebp_14 = slot_C + 1;
            lv_10 = (type_7DCA0 *)ebp_14;
            if (!RwStreamWriteInt32(arg_4, slot_C, sizeof(RwInt32)))
            {
                return false;
            }
            if (!RwStreamWriteInt16(arg_4, (RwInt16 *)lv_10, bp_4 * sizeof(type_7DCA0)))
            {
                return false;
            }
            lv_10 += bp_4;
            ebp_14 = (RwInt32 *)lv_10;
        }
    }
    for (bp_8 = 0; bp_8 < arg_8->unk_02; bp_8++)
    {
        slot_C = ebp_14;
        bp_4 = *slot_C & 0x7FFF;
        ebp_14 = slot_C + 1;
        m_18 = (type_7DCA0 *)ebp_14;
        if (bp_4 == 0)
        {
            if (!RwStreamWriteInt32(arg_4, slot_C, sizeof(RwInt32)))
            {
                return false;
            }
        }
        else
        {
            if (!RwStreamWriteInt32(arg_4, slot_C, sizeof(RwInt32)))
            {
                return false;
            }
            if (!RwStreamWriteInt16(arg_4, (RwInt16 *)m_18, bp_4 * sizeof(type_7DCA0)))
            {
                return false;
            }
        }
        m_18 += bp_4;
        ebp_14 = (RwInt32 *)m_18;
    }
    return true;
}

// match: ?sub_7ECB0@@YAHPAURtAnimAnimation@@@Z @ 0x0007ECB0
// sp-match: ?sub_7ECB0@@YAHPAURtAnimAnimation@@@Z @ 0x00066FF0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_7ECB0(RtAnimAnimation *arg_0)
{
    type_7DCA0 *frm_24;
    RwInt32 *t20;
    type_7DCA0 *l1C;
    RwInt32 m_18;
    RwInt32 *ebp_14;
    RwInt32 lv_10;
    RwInt32 slot_C;
    type_7CBD0_hdr *bp_8;
    RwInt32 bp_4;

    bp_8 = (type_7CBD0_hdr *)arg_0->pFrames;
    t20 = (RwInt32 *)(bp_8 + 1);
    lv_10 = 0;
    for (slot_C = 0; slot_C < bp_8->unk_01; slot_C++)
    {
        ebp_14 = t20;
        if ((bp_4 = *ebp_14 & 0x7FFF) == 0)
        {
            lv_10 += sizeof(RwInt32);
            t20 = ebp_14 + 1;
        }
        else if (*ebp_14 & 0x80000000)
        {
            lv_10 += sizeof(RwInt32);
            if (*ebp_14 & 0x40000000)
            {
                t20 = ebp_14 + 1;
                l1C = (type_7DCA0 *)t20;
                l1C += bp_4;
                t20 = (RwInt32 *)l1C;
            }
            else
            {
                t20 = ebp_14 + 1;
            }
        }
        else
        {
            lv_10 += sizeof(RwInt32);
            lv_10 += bp_4 * sizeof(type_7DCA0);
            t20 = ebp_14 + 1;
            l1C = (type_7DCA0 *)t20;
            l1C += bp_4;
            t20 = (RwInt32 *)l1C;
        }
    }
    m_18 = 0;
    for (slot_C = 0; slot_C < bp_8->unk_02; slot_C++)
    {
        ebp_14 = t20;
        bp_4 = *ebp_14 & 0x7FFF;
        m_18 += sizeof(RwInt32);
        m_18 += bp_4 * sizeof(type_7DCA0);
        t20 = ebp_14 + 1;
        frm_24 = (type_7DCA0 *)t20;
        frm_24 += bp_4;
        t20 = (RwInt32 *)frm_24;
    }
    return m_18 + lv_10 + sizeof(type_7CBD0_hdr);
}

// match: ?sub_7EE30@@YAPAURtAnimAnimation@@PAURwStream@@PAU1@PAX@Z @ 0x0007EE30
// sp-match: ?sub_7EE30@@YAPAURtAnimAnimation@@PAURwStream@@PAU1@PAX@Z @ 0x00067070
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RtAnimAnimation *sub_7EE30(RwStream *arg_0, RtAnimAnimation *arg_4, void *arg_8)
{
    RwInt32 t20;
    RwInt16 *l1C;
    type_7CF40 *m_18;
    RwInt32 ebp_14;
    RwInt16 *lv_10;
    type_7CBD0_hdr *slot_C;
    void *bp_8;
    RwUInt32 bp_4;

    slot_C = (type_7CBD0_hdr *)arg_4->pFrames;
    bp_8 = arg_8;
    bp_4 = (RwUInt32)bp_8;
    for (ebp_14 = 0; ebp_14 < arg_4->numFrames; ebp_14++)
    {
        m_18 = (type_7CF40 *)bp_8;
        ((type_7CF40 **)arg_4->customData)[ebp_14] = m_18;
        if (!RwStreamReadInt16(arg_0, (RwInt16 *)&m_18->unk_00, sizeof(RwUInt64)))
        {
            return 0;
        }
        if (!RwStreamReadInt16(arg_0, (RwInt16 *)&m_18->unk_08, sizeof(RwUInt64)))
        {
            return 0;
        }
        if (!RwStreamReadInt16(arg_0, &m_18->unk_12, sizeof(RwInt16)))
        {
            return 0;
        }
        bp_4 += sizeof(type_7CF40);
        if (!RwStreamReadInt16(arg_0, &m_18->unk_10, sizeof(RwInt16)))
        {
            return 0;
        }
        if (m_18->unk_00_56)
        {
            lv_10 = m_18->unk_14[0];
            if (!RwStreamReadInt16(arg_0, lv_10, m_18->unk_00_56 * sizeof(m_18->unk_14[0])))
            {
                return 0;
            }
            bp_4 += ((m_18->unk_00_56 - 1) * sizeof(m_18->unk_14[0]) + 4 - 1) & ~3;
        }
        if (m_18->unk_08_56)
        {
            l1C = (RwInt16 *)(((RwUInt32)&m_18->unk_14[m_18->unk_00_56] + 3) & ~3);
            for (t20 = 0; t20 < m_18->unk_08_56; t20++)
            {
                if (!RwStreamReadInt16(arg_0, l1C, 3 * sizeof(RwInt16)))
                {
                    return 0;
                }
                l1C += 3;
            }
            bp_4 += (m_18->unk_08_56 * (3 * sizeof(RwInt16)) + 4 - 1) & ~3;
        }
        bp_8 = (void *)bp_4;
    }
    return arg_4;
}

// match: ?sub_7F0E0@@YAHPAURtAnimAnimation@@PAURwStream@@@Z @ 0x0007F0E0
// sp-match: ?sub_7F0E0@@YAHPAURtAnimAnimation@@PAURwStream@@@Z @ 0x002168E0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_7F0E0(RtAnimAnimation *arg_0, RwStream *arg_4)
{
    RwInt32 m_18;
    RwInt16 *ebp_14;
    type_7CF40 *lv_10;
    RwInt32 slot_C;
    RwInt16 *bp_8;
    type_7CBD0_hdr *bp_4;

    bp_4 = (type_7CBD0_hdr *)arg_0->pFrames;
    return 1;
    for (slot_C = 0; slot_C < arg_0->numFrames; slot_C++)
    {
        lv_10 = ((type_7CF40 **)arg_0->customData)[slot_C];
        if (!RwStreamWriteInt16(arg_4, (RwInt16 *)&lv_10->unk_00, sizeof(RwUInt64)))
        {
            return 0;
        }
        if (!RwStreamWriteInt16(arg_4, (RwInt16 *)&lv_10->unk_08, sizeof(RwUInt64)))
        {
            return 0;
        }
        if (!RwStreamWriteInt16(arg_4, &lv_10->unk_12, sizeof(RwInt16)))
        {
            return 0;
        }
        if (!RwStreamWriteInt16(arg_4, &lv_10->unk_10, sizeof(RwInt16)))
        {
            return 0;
        }
        bp_8 = lv_10->unk_14[0];
        if (!RwStreamWriteInt16(arg_4, bp_8, lv_10->unk_00_56 * sizeof(lv_10->unk_14[0])))
        {
            return 0;
        }
        ebp_14 = (RwInt16 *)(((RwUInt32)&lv_10->unk_14[lv_10->unk_00_56] + 3) & ~3);
        for (m_18 = 0; m_18 < lv_10->unk_08_56; m_18++)
        {
            if (!RwStreamWriteInt16(arg_4, ebp_14, 3 * sizeof(RwInt16)))
            {
                return 0;
            }
            ebp_14 += 3;
        }
    }
    return 1;
}

// match: ?sub_7F2A0@@YAIPAURtAnimAnimation@@H@Z @ 0x0007F2A0
// sp-match: ?sub_7F2A0@@YAIPAURtAnimAnimation@@H@Z @ 0x000671D0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwUInt32 sub_7F2A0(RtAnimAnimation *arg_0, RwInt32 arg_4)
{
    type_7CF40 *bp_8;
    RwUInt32 bp_4;

    bp_8 = ((type_7CF40 **)arg_0->customData)[arg_4];
    if (bp_8->unk_00_56 > 0)
    {
#ifdef CODFH_SP // shape: n*6 - 3 (0x671D0)
        bp_4 = (bp_8->unk_00_56 * sizeof(bp_8->unk_14[0]) - sizeof(bp_8->unk_14[0]) + 4 - 1) & ~3;
#else
        bp_4 = ((bp_8->unk_00_56 - 1) * sizeof(bp_8->unk_14[0]) + 4 - 1) & ~3;
#endif
    }
    else
    {
        bp_4 = 0;
    }
    return bp_4 + sizeof(type_7CF40) + ((bp_8->unk_08_56 * (3 * sizeof(RwInt16)) + 4 - 1) & ~3);
}

// match: ?sub_7F370@@YAIPAURtAnimAnimation@@@Z @ 0x0007F370
// sp-match: ?sub_7F370@@YAIPAURtAnimAnimation@@@Z @ 0x00067220
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwUInt32 sub_7F370(RtAnimAnimation *arg_0)
{
    RwUInt32 bp_8;
    RwInt32 bp_4;

    bp_8 = 0;
    for (bp_4 = 0; bp_4 < arg_0->numFrames; bp_4++)
    {
        bp_8 += sub_7F2A0(arg_0, bp_4);
    }
    return bp_8;
}

// The parent frame's world matrix sub_7F3C0 builds its bones on (the
// database's name), and RenderWare's dirty frame list.
extern RwMatrix src2;

// match: ?sub_7F3C0@@YAHPAURpHAnimHierarchy@@HM@Z @ 0x0007F3C0
// sp-match: ?sub_7F3C0@@YAHPAURpHAnimHierarchy@@HM@Z @ 0x00067250
// RenderWare's RpHAnimHierarchyUpdateMatrices with the game's scale: the
// parent's world matrix (identity for local-space matrices), the pose's
// matrices from the hierarchy's interpolator (identities when bit 0 of
// its unk_EA is set), the root scaled by arg_8 (mirrored in x for the mode 2), then
// each bone's matrix down the node stack into the hierarchy's matrices and,
// by its flags, its frame's modelling and world matrices; TRUE.
RwBool sub_7F3C0(RpHAnimHierarchy *arg_0, RwInt32 arg_4, RwReal arg_8)
{
    RwBool lv_4;
    RwFrame *lv_8;
    RwInt32 lv_c;
    type_80300 *lv_10;
    RwMatrix lv_50;
    RwMatrix *lv_54;
    RwFrame *lv_58;
    RwMatrix *lv_5c;
#ifdef CODFH_SP // shape: lv_a0 block-scoped; SP 0x67250 frame 0x1164
#else
    RwMatrix lv_a0;
#endif
    void (*lv_a4)(RwMatrix *, void *, RwInt32);
    void *lv_a8;
    RwInt32 lv_ac;
    RwMatrix lv_10b0[64];
    RwMatrix lv_10f0;
    RwMatrix lv_1130;
    RwMatrix *lv_11b0[32];
    RwMatrix **lv_11b4;                 // (from the second of RW's 32 entries)
    RpHAnimNodeInfo *lv_11b8;
    RwMatrix *lv_11bc;
    RwFrame *lv_11c0;

    lv_4 = FALSE;
    lv_8 = 0;
    lv_c = arg_0->flags;
    lv_10 = (type_80300 *)arg_0->currentAnim;
    if (lv_c & rpHANIMHIERARCHYLOCALSPACEMATRICES) {
        RwMatrixSetIdentity(&lv_50);
        lv_54 = &lv_50;
        if (lv_c & rpHANIMHIERARCHYUPDATELTMS) {
            lv_4 = TRUE;
            lv_8 = arg_0->parentFrame;
        }
    } else {
        lv_4 = TRUE;
        lv_8 = arg_0->parentFrame;
        lv_54 = &src2;
    }
    if (lv_4) {
        if (lv_8 != 0 && RwFrameGetParent(lv_8) != 0) {
            lv_58 = RwFrameGetParent(lv_8);
            if (!RwFrameDirty(lv_58))
                src2 = *RwFrameGetLTM(lv_58);
            else {
                lv_5c = RwFrameGetMatrix(lv_58);
                src2 = *lv_5c;
                lv_58 = RwFrameGetParent(lv_58);
                while (lv_58 != 0) {
#ifdef CODFH_SP
                    RwMatrix lv_a0;
#endif
                    lv_a0 = src2;
                    lv_5c = RwFrameGetMatrix(lv_58);
                    RwMatrixMultiply(&src2, &lv_a0, lv_5c);
                    lv_58 = RwFrameGetParent(lv_58);
                }
            }
        } else
            RwMatrixSetIdentity(&src2);
        sub_19B650(&src2);
    }
    if (lv_c & rpHANIMHIERARCHYUPDATELTMS) {
        if (!(arg_0->parentFrame->root->object.privateFlags & 3)) {
            arg_0->parentFrame->root->inDirtyListLink.next = RWSRCGLOBAL(dirtyFrameList).link.next;
            arg_0->parentFrame->root->inDirtyListLink.prev = &RWSRCGLOBAL(dirtyFrameList).link;
            RWSRCGLOBAL(dirtyFrameList).link.next->prev = &arg_0->parentFrame->root->inDirtyListLink;
            RWSRCGLOBAL(dirtyFrameList).link.next = &arg_0->parentFrame->root->inDirtyListLink;
            arg_0->parentFrame->root->object.privateFlags |= 2;
        }
    }
    lv_a4 = (void (*)(RwMatrix *, void *, RwInt32))lv_10->unk_12C;
    lv_a8 = ((type_80300 *)arg_0->currentAnim)->unk_144;
    if (lv_10->unk_EA & 1) {
        for (lv_ac = 0; lv_ac < arg_0->numNodes; lv_ac++)
            RwMatrixSetIdentity(&lv_10b0[lv_ac]);
    } else
        lv_a4(lv_10b0, lv_a8, arg_4);
    RwMatrixSetIdentity(&lv_10f0);
    if (arg_4 == 2)
        lv_10f0.right.x = -arg_8;
    else
        lv_10f0.right.x = arg_8;
    lv_10f0.up.y = arg_8;
    lv_10f0.at.z = arg_8;
    RwMatrixMultiply(&lv_1130, &lv_10b0[0], &lv_10f0);
    lv_10b0[0] = lv_1130;
    lv_10b0[0].flags = 0;
    lv_11b4 = &lv_11b0[1];
    lv_11b8 = arg_0->pNodeInfo;
    lv_11bc = arg_0->pMatrixArray;
    for (lv_ac = 0; lv_ac < arg_0->numNodes; lv_ac++) {
        RwMatrixMultiply(lv_11bc, &lv_10b0[lv_ac], lv_54);
        lv_11c0 = lv_11b8->pFrame;
        if (lv_11c0 != 0) {
            if (lv_c & rpHANIMHIERARCHYUPDATEMODELLINGMATRICES) {
                lv_11c0->modelling = lv_10b0[lv_ac];
                if (!(lv_c & rpHANIMHIERARCHYUPDATELTMS))
                    RwFrameUpdateObjects(lv_11c0);
            }
            if (lv_c & rpHANIMHIERARCHYUPDATELTMS) {
                if (lv_c & rpHANIMHIERARCHYLOCALSPACEMATRICES)
                    RwMatrixMultiply(&lv_11c0->ltm, lv_11bc, &src2);
                else
                    lv_11c0->ltm = *lv_11bc;
                sub_19B650(&lv_11c0->ltm);
                lv_11c0->object.privateFlags = (lv_11c0->object.privateFlags & ~4) | 8;
            }
        }
        switch (lv_11b8->flags & 3) {
        case 0:
            lv_54 = lv_11bc;
            break;
        case 1:
            lv_54 = *--lv_11b4;
            break;
        case 2:
            *lv_11b4++ = lv_54;
            lv_54 = lv_11bc;
            break;
        }
        lv_11bc++;
        lv_11b8++;
    }
    return TRUE;
}

// Not in the image: a stand-in for a function the original object held about here, which
// nothing called, so the link's /OPT:REF dropped it. It was the first to use pi/360 (the
// image keeps that literal, 0x3D3CC8, among this object's, between sub_7D2F0's and
// sub_7FB40's, though its first surviving user is sub_9D27D in unit_09C1E0). Its body is
// unknown: this one only uses the literal, as degrees to a half angle in radians.
// match: __real@3c0efa35 @ 0x003D3CC8
RwReal dropped_3D3CC8(RwReal arg_0)
{
    return arg_0 * 0.0087266462f;
}

// match: ?sub_7FB40@@YAXPAFPAURtQuat@@H@Z @ 0x0007FB40
// sp-match: ?sub_7FB40@@YAXPAFPAURtQuat@@H@Z @ 0x00067760
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_7FB40(RwInt16 *arg_0, RtQuat *arg_4, RwInt32 arg_8)
{
    RwReal l1C;
    RwReal *m_18;
    RtQuat ebp_14;
    RwInt32 bp_4;

    sub_13FB00(&ebp_14, arg_4);
    m_18 = (RwReal *)&ebp_14;
    if (m_18[3] < 0.0f)
    {
        for (bp_4 = 0; bp_4 < 4; bp_4++)
        {
            m_18[bp_4] = -m_18[bp_4];
        }
    }
    l1C = m_18[0] * 32768.0f;
    if (l1C > 32767.0f)
    {
        l1C = 32767.0f;
    }
    else if (l1C < -32768.0f)
    {
        l1C = -32768.0f;
    }
    arg_0[0] = (RwInt16)l1C;
    l1C = m_18[1] * 32768.0f;
    if (l1C > 32767.0f)
    {
        l1C = 32767.0f;
    }
    else if (l1C < -32768.0f)
    {
        l1C = -32768.0f;
    }
    arg_0[1] = (RwInt16)l1C;
    l1C = m_18[2] * 32768.0f;
    if (l1C > 32767.0f)
    {
        l1C = 32767.0f;
    }
    else if (l1C < -32768.0f)
    {
        l1C = -32768.0f;
    }
    arg_0[2] = (RwInt16)l1C;
}

#endif // (single player: the first file ends here)
#if !defined(CODFH_SP) || CODFH_SP_PART != 1 // single player: src/sp/units/sp_unit_07CA20_2.cpp, the second file
#ifdef CODFH_SP
// The interpolators' scratch memory is this file's own in single player: sub_80300 and sub_80550
// (SP 0x67ED0, 0x68030) match only with it static.
static void *dword_44BA3C;
static void *dword_44BA40;
#endif

// match: ?sub_7FC90@@YAHXZ @ 0x0007FC90
// sp-match: ?sub_7FC90@@YAHXZ @ 0x00067B10
RwInt32 sub_7FC90()
{
    dword_44BA54.sub_16C2C0(0x20, 0x870, "_animInterpolatorPool", 0x10, 1);
#ifdef CODFH_SP // SP 0x67B10: a pool of 0x140 headers
    dword_44BA74.sub_16C2C0(0x140, 0x150, "_animInterpolatorHeaderPool", 0x10, 1);
#else
    dword_44BA74.sub_16C2C0(0x208, 0x150, "_animInterpolatorHeaderPool", 0x10, 1);
#endif
    dword_44BA3C = RwMalloc(0x10E0, 0x34251); // not an address: an allocation tag
    dword_44BA40 = RwMalloc(0xE40, 0x34251); // not an address: an allocation tag
    return 1;
}

// match: ?sub_7FD10@@YAHXZ @ 0x0007FD10
// sp-match: ?sub_7FD10@@YAHXZ @ 0x00067B80
RwInt32 sub_7FD10()
{
    dword_44BA54.sub_16C4D0(1);
    dword_44BA74.sub_16C4D0(1);
    RwFree(dword_44BA3C);
    dword_44BA3C = 0;
    RwFree(dword_44BA40);
    dword_44BA40 = 0;
    return 1;
}

// match: ?sub_7FD70@@YAHXZ @ 0x0007FD70
// sp-match: ?sub_7FD70@@YAHXZ @ 0x00067BD0
RwInt32 sub_7FD70()
{
    dword_44BA38 = 0;
    return 1;
}

// match: ?sub_7FD90@@YAHPAURtAnimInterpolatorInfo@@@Z @ 0x0007FD90
// sp-match: ?sub_7FD90@@YAHPAURtAnimInterpolatorInfo@@@Z @ 0x00067BE0
RwInt32 sub_7FD90(RtAnimInterpolatorInfo *arg_0)
{
    RwInt32 var_4;

    if (dword_44BA38 < 16)
    {
        for (var_4 = 0; var_4 < dword_44BA38; var_4++)
        {
            if (dword_44B638[var_4].typeID == arg_0->typeID)
            {
                return 0;
            }
        }
        dword_44B638[dword_44BA38] = *arg_0;
        dword_44BA38++;
        return 1;
    }
    return 0;
}

// match: ?sub_7FE10@@YAPAURtAnimInterpolatorInfo@@H@Z @ 0x0007FE10
// sp-match: ?sub_7FE10@@YAPAURtAnimInterpolatorInfo@@H@Z @ 0x00067C40
RtAnimInterpolatorInfo *sub_7FE10(RwInt32 arg_0)
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < dword_44BA38; var_4++)
    {
        if (dword_44B638[var_4].typeID == arg_0)
        {
            return &dword_44B638[var_4];
        }
    }
    return 0;
}

// match: ?sub_7FE60@@YAPAURtAnimAnimation@@HHHMHH@Z @ 0x0007FE60
// sp-match: ?sub_7FE60@@YAPAURtAnimAnimation@@HHHMHH@Z @ 0x000688E0
RtAnimAnimation *sub_7FE60(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwReal arg_C, RwInt32 arg_10,
                           RwInt32 arg_14)
{
    void *local_8;
    RtAnimAnimation *var_4;

    arg_14 += 0x10;
    arg_14 &= ~0xF;
    local_8 = RwMalloc(sub_7FEF0(arg_4, arg_10, arg_14), 0x34251); // not an address: an allocation tag
    var_4 = sub_7FF20(local_8, arg_0, arg_4, arg_8, arg_C, arg_10, arg_14);
    if (!var_4)
    {
        RwFree(local_8);
        return 0;
    }
    var_4->unk_10 = 1;
    return var_4;
}

// match: ?sub_7FEF0@@YAIHHH@Z @ 0x0007FEF0
// sp-match: ?sub_7FEF0@@YAIHHH@Z @ 0x00067C70
RwUInt32 sub_7FEF0(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    return ((arg_4 + 3) & ~3) + (arg_8 + (sizeof(RtAnimAnimation) + 15 + ((arg_0 * sizeof(void *) + 3) & ~3)));
}

// match: ?sub_7FF20@@YAPAURtAnimAnimation@@PAXHHHMHH@Z @ 0x0007FF20
// sp-match: ?sub_7FF20@@YAPAURtAnimAnimation@@PAXHHHMHH@Z @ 0x00067CA0
RtAnimAnimation *sub_7FF20(void *arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C, RwReal arg_10,
                           RwInt32 arg_14, RwInt32 arg_18)
{
    RtAnimAnimation *local_8;
    RtAnimInterpolatorInfo *var_4;

    local_8 = (RtAnimAnimation *)arg_0;
    var_4 = sub_7FE10(arg_4);
    if (!var_4)
    {
        return 0;
    }
    local_8->interpInfo = var_4;
    local_8->numFrames = arg_8;
    local_8->flags = arg_C;
    local_8->duration = arg_10;
    if (arg_14)
    {
        local_8->pFrames = (void *)(((RwUInt32)local_8 + sizeof(RtAnimAnimation) + 15) & ~15);
    }
    else
    {
        local_8->pFrames = 0;
    }
    local_8->customData = 0;
    local_8->unk_10 = 0;
    return local_8;
}

// match: ?sub_7FFB0@@YAPAURtAnimAnimation@@PAU1@@Z @ 0x0007FFB0
// sp-match: ?sub_7FFB0@@YAPAURtAnimAnimation@@PAU1@@Z @ 0x00067D00
RtAnimAnimation *sub_7FFB0(RtAnimAnimation *arg_0)
{
    RwFree(arg_0);
    return arg_0;
}

// match: ?sub_7FFD0@@YA_NPAURwStream@@PAUtype_7FFD0@@@Z @ 0x0007FFD0
// sp-match: ?sub_7FFD0@@YA_NPAURwStream@@PAUtype_7FFD0@@@Z @ 0x00067D20
bool sub_7FFD0(RwStream *arg_0, type_7FFD0 *arg_4)
{
    RwInt32 var_4;
    RtAnimInterpolatorInfo *local_8;

    if (!RwStreamReadInt32(arg_0, &var_4, sizeof(RwInt32)))
    {
        return false;
    }
    if (var_4 != 0x101)
    {
#if defined(CODFH_SP) && !defined(CODFH_SP_LOGS) // SP 0x67D20 prints no warning
#else
        sub_19A750("WARNING! Animation is an old version!! Current ver # %x, File ver # %x\n", 0x101, var_4);
#endif
        return false;
    }
    if (!RwStreamReadInt32(arg_0, &arg_4->unk_00, sizeof(RwInt32)))
    {
        return false;
    }
    local_8 = sub_7FE10(arg_4->unk_00);
    if (!local_8)
    {
        return false;
    }
    if (!RwStreamReadInt32(arg_0, &arg_4->unk_04, sizeof(RwInt32)))
    {
        return false;
    }
    if (!RwStreamReadInt32(arg_0, &arg_4->unk_08, sizeof(RwInt32)))
    {
        return false;
    }
    if (!RwStreamReadInt32(arg_0, &arg_4->unk_0C, sizeof(RwInt32)))
    {
        return false;
    }
    if (!RwStreamReadInt32(arg_0, &arg_4->unk_10, sizeof(RwInt32)))
    {
        return false;
    }
    if (!RwStreamReadInt32(arg_0, (RwInt32 *)&arg_4->unk_14, sizeof(RwInt32)))
    {
        return false;
    }
    return true;
}

// match: ?sub_800F0@@YAPAXPAUtype_7CBD0_hdr@@HH@Z @ 0x000800F0
// sp-match: ?sub_800F0@@YAPAXPAUtype_7CBD0_hdr@@HH@Z @ 0x00067DE0
void *sub_800F0(type_7CBD0_hdr *arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    RwInt32 var_4;
    RwInt32 v8;
    RwUInt32 *stk_C;
    RwUInt64 *var_10;
    RwUInt32 *lv_14;

    lv_14 = (RwUInt32 *)(arg_0 + 1);
    for (v8 = 0; v8 < arg_0->unk_01; v8++)
    {
        if (v8 == arg_4)
        {
#if defined(CODFH_SP) && !defined(CODFH_SP_LOGS) // SP 0x67DE0 has no size check
#else
            stk_C = lv_14;
            var_4 = *stk_C & 0x7FFF;
            if (var_4 != arg_8)
            {
                sub_19A750("this is bad shit");
            }
#endif
            return lv_14 + 1;
        }
        stk_C = lv_14;
        if ((var_4 = *stk_C & 0x7FFF) == 0)
        {
            lv_14 = stk_C + 1;
        }
        else if (*stk_C & 0x80000000)
        {
            lv_14 = stk_C + 1;
        }
        else
        {
            lv_14 = stk_C + 1;
            var_10 = (RwUInt64 *)lv_14;
            var_10 += var_4;
            lv_14 = (RwUInt32 *)var_10;
        }
    }
    return 0;
}

// match: ?sub_801C0@@YAXPAURtAnimAnimation@@PAPAUtype_7CBD0_hdr@@H@Z @ 0x000801C0
// sp-match: ?sub_801C0@@YAXPAURtAnimAnimation@@PAPAUtype_7CBD0_hdr@@H@Z @ 0x00067E30
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_801C0(RtAnimAnimation *arg_0, type_7CBD0_hdr **arg_4, RwInt32 arg_8)
{
    void *bp_2C;
    type_7CBD0_hdr *local_28;
    RwInt32 *local_24;
    RwUInt64 *local_20;
    RwInt32 var_1C;
    type_7CBD0_hdr **var18;
    RwInt32 *stk_14;
    RwInt32 l10;
    RwInt32 local_C;
    type_7CBD0_hdr *lv_8;
    RwInt32 var_4;

    lv_8 = (type_7CBD0_hdr *)arg_0->pFrames;
    var18 = arg_4;
    local_24 = (RwInt32 *)(lv_8 + 1);
    for (l10 = 0; l10 < lv_8->unk_01; l10++)
    {
        stk_14 = local_24;
        if ((var_4 = *stk_14 & 0x7FFF) == 0)
        {
            local_24 = stk_14 + 1;
        }
        else if (*stk_14 & 0x80000000)
        {
            if (*stk_14 & 0x40000000)
            {
                var_1C = (*stk_14 & 0xFF8000) >> 15;
                local_C = (*stk_14 & 0x3F000000) >> 24;
                local_28 = var18[var_1C];
                bp_2C = sub_800F0(local_28, local_C, var_4);
#ifdef CODFH_WIN32
                // (the port: an index for the address, which may be over 1 GB: port/src/animkeyref.cpp)
                *stk_14 = port_anim_key_pack(bp_2C);
#else
                *stk_14 = (RwInt32)bp_2C | 0x80000000;
#endif
            }
            local_24 = stk_14 + 1;
        }
        else
        {
            local_24 = stk_14 + 1;
            local_20 = (RwUInt64 *)local_24;
            local_20 += var_4;
            local_24 = (RwInt32 *)local_20;
        }
    }
}

// match: ?sub_802D0@@YAPAURtAnimAnimation@@PAURwStream@@PAU1@HH@Z @ 0x000802D0
// sp-match: ?sub_802D0@@YAPAURtAnimAnimation@@PAURwStream@@PAU1@HH@Z @ 0x00067EB0
RtAnimAnimation *sub_802D0(RwStream *arg_0, RtAnimAnimation *arg_4, RwInt32 arg_8, RwInt32 arg_C)
{
    RtAnimInterpolatorInfo *var_4;

    var_4 = arg_4->interpInfo;
    if (!var_4->unk_24(arg_0, arg_4, arg_8))
    {
        return 0;
    }
    return arg_4;
}

// match: ?sub_80300@@YAPAUtype_80300@@H_NH@Z @ 0x00080300
// sp-match: ?sub_80300@@YAPAUtype_80300@@H_NH@Z @ 0x00067ED0
type_80300 *sub_80300(RwInt32 arg_0, bool arg_4, RwInt32 arg_8)
{
    type_80300 *var_4;
    void *v8;
    RwInt32 stk_C;
    RwInt32 var_10;

    v8 = 0;
    if (arg_0 & 0xF)
    {
        arg_0 += 0x10;
        arg_0 &= ~0xF;
    }
    if (arg_8 & 0xF)
    {
        arg_8 += 0x10;
        arg_8 &= ~0xF;
    }
    if (arg_4)
    {
        arg_0 = 0x720;
        stk_C = arg_0 + arg_8 + sizeof(type_80300);
        var_4 = (type_80300 *)RwMalloc(stk_C, 0x34251); // not an address: an allocation tag
        memset(var_4, 0, stk_C);
    }
    else
    {
        var_4 = (type_80300 *)dword_44BA54.sub_16C5A0(0);
        memset(var_4, 0, 0x870);
    }
    if (arg_8)
    {
        v8 = (void *)((RwUInt32)var_4 + arg_0 + sizeof(type_80300));
    }
    for (var_10 = 0; var_10 < 0x38; var_10++)
    {
        var_4->unk_74[var_10] = 0;
        var_4->unk_04[var_10] = 0;
    }
    var_4->unk_144 = (type_80300_150 *)(var_4 + 1);
    var_4->unk_00 = 0;
    var_4->unk_E4 = 0;
    var_4->unk_E8 = 0;
    var_4->unk_EA = 0;
    var_4->unk_EB = 0;
    var_4->unk_EC = dword_44BA40;
    var_4->unk_F0 = (void *)((RwUInt32)dword_44BA40 + 0x720);
    var_4->unk_F4 = 0;
    var_4->unk_F8 = 0;
    var_4->unk_FC = -1.0f;
    var_4->unk_100 = 0;
    var_4->unk_104 = 0;
    var_4->unk_108 = arg_0;
    var_4->unk_128 = 0;
    var_4->unk_12C = 0;
    var_4->unk_130 = 0;
    var_4->unk_134 = 0;
    var_4->unk_138 = 0;
    var_4->unk_13C = 0;
    var_4->unk_140 = 0;
    var_4->unk_128 = v8;
    var_4->unk_144->unk_04 = v8;
    var_4->unk_128 = v8;
    var_4->unk_144->unk_04 = v8;
    return var_4;
}

// match: ?sub_80550@@YAPAUtype_80300@@HH@Z @ 0x00080550
// sp-match: ?sub_80550@@YAPAUtype_80300@@HH@Z @ 0x00068030
type_80300 *sub_80550(RwInt32 arg_0, RwInt32 arg_4)
{
    type_80300 *var_4;
    RwInt32 local_8;

    if (arg_0 & 0xF)
    {
        arg_0 += 0x10;
        arg_0 &= ~0xF;
    }
    var_4 = (type_80300 *)dword_44BA74.sub_16C5A0(0);
    for (local_8 = 0; local_8 < 0x38; local_8++)
    {
        var_4->unk_74[local_8] = 0;
        var_4->unk_04[local_8] = 0;
    }
    var_4->unk_144 = (type_80300_150 *)(arg_4 * 0x870 + (RwUInt32)dword_44BA3C);
    var_4->unk_00 = 0;
    var_4->unk_E4 = 0;
    var_4->unk_E8 = 0;
    var_4->unk_EA = 0;
    var_4->unk_EB = 0;
    var_4->unk_EC = dword_44BA40;
    var_4->unk_F0 = (void *)((RwUInt32)dword_44BA40 + 0x720);
    var_4->unk_F4 = 0;
    var_4->unk_F8 = 0;
    var_4->unk_FC = -1.0f;
    var_4->unk_100 = 0;
    var_4->unk_104 = 0;
    var_4->unk_108 = arg_0;
    var_4->unk_128 = 0;
    var_4->unk_12C = 0;
    var_4->unk_130 = 0;
    var_4->unk_134 = 0;
    var_4->unk_138 = 0;
    var_4->unk_13C = 0;
    var_4->unk_140 = 0;
    return var_4;
}

// match: ?sub_806E0@@YAXPAUtype_80300@@@Z @ 0x000806E0
// sp-match: ?sub_806E0@@YAXPAUtype_80300@@@Z @ 0x00068110
void sub_806E0(type_80300 *arg_0)
{
    if (dword_44BA54.sub_16C770(arg_0))
    {
        dword_44BA54.sub_16C710(arg_0);
    }
    else if (dword_44BA74.sub_16C770(arg_0))
    {
        dword_44BA74.sub_16C710(arg_0);
    }
    else
    {
        RwFree(arg_0);
    }
}

// match: ?sub_80740@@YAHPAUtype_80300@@H@Z @ 0x00080740
// sp-match: ?sub_80740@@YAHPAUtype_80300@@H@Z @ 0x00068160
RwInt32 sub_80740(type_80300 *arg_0, RwInt32 arg_4)
{
    RtAnimInterpolatorInfo *var_4;

    var_4 = sub_7FE10(arg_4);
    if (!var_4)
    {
        return 0;
    }
    arg_0->unk_12C = var_4->unk_04;
    arg_0->unk_134 = var_4->unk_0C;
    arg_0->unk_130 = (type_80300_blend)var_4->unk_08;
    arg_0->unk_138 = (type_80300_decode)var_4->unk_14;
    arg_0->unk_13C = (type_80300_kf)var_4->unk_18;
    arg_0->unk_140 = (void *)var_4->unk_1C;
    return 1;
}

// match: ?sub_807C0@@YAHPAURtAnimInterpolator@@PAX@Z @ 0x000807C0
// sp-match: ?sub_807C0@@YAHPAURtAnimInterpolator@@PAX@Z @ 0x000681C0
RwInt32 sub_807C0(RtAnimInterpolator *arg_0, void *arg_4)
{
    ((type_80300 *)arg_0)->unk_128 = arg_4;
    return 1;
}

// match: ?sub_807E0@@YAHPAUtype_80300@@PAURtAnimAnimation@@@Z @ 0x000807E0
// sp-match: ?sub_807E0@@YAHPAUtype_80300@@PAURtAnimAnimation@@@Z @ 0x000681E0
RwInt32 sub_807E0(type_80300 *arg_0, RtAnimAnimation *arg_4)
{
    RtAnimInterpolatorInfo *var_4;

    arg_0->unk_00 = arg_4;
    arg_0->unk_E4 = 0;
    var_4 = arg_4->interpInfo;
    arg_0->unk_128 = arg_4->pFrames;
    arg_0->unk_12C = var_4->unk_04;
    arg_0->unk_134 = var_4->unk_0C;
    arg_0->unk_130 = (type_80300_blend)var_4->unk_08;
    arg_0->unk_138 = (type_80300_decode)var_4->unk_14;
    arg_0->unk_13C = (type_80300_kf)var_4->unk_18;
    arg_0->unk_140 = (void *)var_4->unk_1C;
    arg_0->unk_E8 = 0;
    return 1;
}

// match: ?sub_80880@@YAXPAUtype_80300@@P6APAU1@0PAX@Z1@Z @ 0x00080880
// sp-match: ?sub_80880@@YAXPAUtype_80300@@P6APAU1@0PAX@Z1@Z @ 0x00068250
void sub_80880(type_80300 *arg_0, type_80300_cb arg_4, void *arg_8)
{
    arg_0->unk_100 = arg_4;
    arg_0->unk_104 = arg_8;
}

// match: ?sub_808A0@@YAXPAUtype_80300@@P6APAU1@0PAX@ZM1@Z @ 0x000808A0
// sp-match: ?sub_808A0@@YAXPAUtype_80300@@P6APAU1@0PAX@ZM1@Z @ 0x00068270
void sub_808A0(type_80300 *arg_0, type_80300_cb arg_4, RwReal arg_8, void *arg_C)
{
    arg_0->unk_F4 = arg_4;
    arg_0->unk_FC = arg_8;
    arg_0->unk_F8 = arg_C;
}

// match: ?sub_808D0@@YAHPAUtype_80300@@0@Z @ 0x000808D0
// sp-match: ?sub_808D0@@YAHPAUtype_80300@@0@Z @ 0x000682A0
RwInt32 sub_808D0(type_80300 *arg_0, type_80300 *arg_4)
{
    type_80300_150 *var_4;
    type_80300_150 *local_8;

    var_4 = arg_4->unk_144;
    local_8 = arg_0->unk_144;
    arg_4->unk_13C(local_8, var_4);
    return 1;
}

// match: ?sub_80910@@YAHPAUtype_80300@@ME@Z @ 0x00080910
// sp-match: ?sub_80910@@YAHPAUtype_80300@@ME@Z @ 0x000682D0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_80910(type_80300 *arg_0, RwReal arg_4, RwUInt8 arg_8)
{
    RwReal zE0;
    RwReal locDC;
    RwReal var_D8;
    RwReal slot_D4;
    RtQuat *locD0;
    type_7CBD0 *fp_CC;
    RwReal yC8;
    type_7DCA0_q frm_C4;
    RtQuat var_BC;
    type_7CBD0_t bp_AC;
    RwInt32 y9C;
    type_7DCA0_q ebp_98;
    RwInt32 *lv_90;
    type_7DCA0 *lcl_8C;
    type_7CBD0_t p88;
    type_7DCA0 *l78;
    type_7CBD0_t *stk_74;
    RwInt32 var_70;
    RwInt32 bp_6C;
    type_7DCA0_q r68;
    RwReal p60;
    RwInt32 *p5C;
    RwInt32 stk_58;
    RwReal l54;
    RwUInt64 var50;
    RtQuat w48;
    type_7CBD0_hdr *ebp_38;
    RwInt32 var_34;
    type_7DCA0_q lv_30;
    RwInt32 frm_24;
    RwInt32 var_20;
    RwReal l1C;
    RwReal m_18;
    RwInt32 ebp_14;
    RwInt32 lv_10;
    RtAnimAnimation *var_C;
    type_80300_150 *bp_8;
    type_7CBD0_hdr *bp_4;

    var_C = arg_0->unk_00;
    m_18 = var_C->duration;
    ebp_14 = 0;
    lv_10 = 0;
    bp_4 = (type_7CBD0_hdr *)var_C->pFrames;
    ebp_14 |= arg_0->unk_E4 <= arg_0->unk_FC && arg_4 + arg_0->unk_E4 >= arg_0->unk_FC;
    arg_0->unk_E4 = arg_4 + arg_0->unk_E4;
    if (arg_0->unk_E4 > m_18)
    {
        while (arg_0->unk_E4 > m_18)
        {
            arg_0->unk_E4 = arg_0->unk_E4 - m_18;
            ebp_14 |= arg_0->unk_E4 >= arg_0->unk_FC;
            lv_10 = 1;
        }
        for (var_20 = 0; var_20 < bp_4->unk_00; var_20++)
        {
            arg_0->unk_74[var_20] = 0;
            arg_0->unk_04[var_20] = 0;
        }
        l1C = arg_0->unk_E4;
        sub_807E0(arg_0, var_C);
        arg_0->unk_E4 = l1C;
    }
    bp_8 = arg_0->unk_144;
    if (arg_8)
    {
        var_70 = 0;
        fp_CC = (type_7CBD0 *)bp_8;
        fp_CC->unk_04 = bp_4;
        ebp_38 = fp_CC->unk_04;
        fp_CC->unk_00 = arg_0->unk_E4;
        locD0 = fp_CC->unk_10;
        stk_74 = (type_7CBD0_t *)&fp_CC->unk_10[ebp_38->unk_00];
        lv_90 = (RwInt32 *)(ebp_38 + 1);
        for (var_34 = 0; var_34 < ebp_38->unk_00; var_34++)
        {
            var50 = (RwUInt64)1 << var_34;
            if (ebp_38->unk_08 & var50)
            {
                p5C = lv_90;
                if ((frm_24 = *p5C & 0x7FFF) == 0)
                {
                    lv_90 = p5C + 1;
                    continue;
                }
                if (*p5C & 0x80000000)
                {
#ifdef CODFH_WIN32
                    l78 = (type_7DCA0 *)port_anim_key_unpack(*p5C);
#else
                    l78 = (type_7DCA0 *)(*p5C & 0x3FFFFFFF);
#endif
                    lv_90 = p5C + 1;
                }
                else
                {
                    l78 = (type_7DCA0 *)(p5C + 1);
                    lv_90 = (RwInt32 *)(l78 + frm_24);
                }
                if (var_34 != ebp_38->unk_05)
                {
                    continue;
                }
                bp_6C = arg_0->unk_74[var_34];
                stk_58 = bp_6C;
                yC8 = l78[bp_6C].unk_06 / 59.999f;
#ifdef CODFH_EXTRA_LOGS // (the GameCube build, main.dol 0x80063238)
                if (yC8 > arg_0->unk_E4)
                    sub_19A750("%s: Anim goes back!!!\n", "SAnimInterpolatorAddAnimTime");
#endif
                while (yC8 < arg_0->unk_E4)
                {
                    stk_58 = bp_6C;
                    bp_6C++;
                    if (bp_6C >= frm_24)
                    {
                        break;
                    }
                    yC8 = l78[bp_6C].unk_06 / 59.999f;
                }
                arg_0->unk_74[var_34] = (RwInt16)stk_58;
                lv_30 = l78[stk_58].unk_00;
                r68 = l78[stk_58 + 1].unk_00;
                slot_D4 = l78[stk_58].unk_06 / 59.999f;
                var_D8 = l78[stk_58 + 1].unk_06 / 59.999f;
                p60 = (arg_0->unk_E4 - slot_D4) / (var_D8 - slot_D4);
                sub_7CA20(&var_BC, lv_30.unk_00, 0);
                sub_7CA20(&w48, r68.unk_00, 0);
                sub_13FBC0(&locD0[var_34], &var_BC, &w48, p60);
            }
        }
        for (var_34 = 0; var_34 < bp_4->unk_00; var_34++)
        {
            var50 = (RwUInt64)1 << var_34;
            if (bp_4->unk_10 & var50)
            {
                p5C = lv_90;
                if ((frm_24 = *p5C & 0x7FFF) == 0)
                {
                    var_70++;
                    lv_90 = p5C + 1;
                    continue;
                }
                if (*p5C & 0x80000000)
                {
#ifdef CODFH_WIN32
                    lcl_8C = (type_7DCA0 *)port_anim_key_unpack(*p5C);
#else
                    lcl_8C = (type_7DCA0 *)(*p5C & 0x3FFFFFFF);
#endif
                    lv_90 = p5C + 1;
                }
                else
                {
                    lcl_8C = (type_7DCA0 *)(p5C + 1);
                    lv_90 = (RwInt32 *)(lcl_8C + frm_24);
                }
                if (var_34 != ebp_38->unk_05)
                {
                    var_70++;
                    continue;
                }
                bp_6C = arg_0->unk_04[var_34];
                y9C = bp_6C;
                yC8 = lcl_8C[bp_6C].unk_06 / 59.999f;
                while (yC8 < arg_0->unk_E4)
                {
                    y9C = bp_6C;
                    bp_6C++;
                    if (bp_6C >= frm_24)
                    {
                        break;
                    }
                    yC8 = lcl_8C[bp_6C].unk_06 / 59.999f;
                }
                arg_0->unk_04[var_34] = (RwInt16)y9C;
                frm_C4 = lcl_8C[y9C].unk_00;
                ebp_98 = lcl_8C[y9C + 1].unk_00;
                locDC = lcl_8C[y9C].unk_06 / 59.999f;
                zE0 = lcl_8C[y9C + 1].unk_06 / 59.999f;
                l54 = (arg_0->unk_E4 - locDC) / (zE0 - locDC);
                sub_7CAC0((RwUInt16 *)frm_C4.unk_00, &p88.unk_00);
                sub_7CAC0((RwUInt16 *)ebp_98.unk_00, &bp_AC.unk_00);
                stk_74[var_70].unk_00.x = (bp_AC.unk_00.x - p88.unk_00.x) * l54 + p88.unk_00.x;
                stk_74[var_70].unk_00.y = (bp_AC.unk_00.y - p88.unk_00.y) * l54 + p88.unk_00.y;
                stk_74[var_70].unk_00.z = (bp_AC.unk_00.z - p88.unk_00.z) * l54 + p88.unk_00.z;
                var_70++;
            }
        }
    }
    else
    {
        arg_0->unk_138(bp_8, arg_0);
    }
    if (ebp_14 && arg_0->unk_F4)
    {
        if (!arg_0->unk_F4(arg_0, arg_0->unk_F8))
        {
            arg_0->unk_F4 = 0;
        }
    }
    if (lv_10 && arg_0->unk_100)
    {
        if (!arg_0->unk_100(arg_0, arg_0->unk_104))
        {
            arg_0->unk_100 = 0;
        }
    }
    return 1;
}

// match: ?sub_81110@@YAHPAUtype_80300@@ME@Z @ 0x00081110
// sp-match: ?sub_81110@@YAHPAUtype_80300@@ME@Z @ 0x00068860
RwInt32 sub_81110(type_80300 *arg_0, RwReal arg_4, RwUInt8 arg_8)
{
    RwReal var_4;

    var_4 = arg_4 - arg_0->unk_E4;
    if (var_4 < 0.0f)
    {
#ifdef CODFH_SP // SP 0x68860 makes no call for a backwards move (an empty inline there)
#else
        sub_31DB0(arg_0, -var_4, arg_8);
#endif
    }
    else
    {
        sub_80910(arg_0, var_4, arg_8);
    }
    return 1;
}

// match: ?sub_81170@@YAHPAUtype_80300@@00M@Z @ 0x00081170
// sp-match: ?sub_81170@@YAHPAUtype_80300@@00M@Z @ 0x000688A0
RwInt32 sub_81170(type_80300 *arg_0, type_80300 *arg_4, type_80300 *arg_8, RwReal arg_C)
{
    type_80300_150 *var_4;
    type_80300_150 *v8;
    type_80300_150 *varC;

    var_4 = arg_8->unk_144;
    v8 = arg_4->unk_144;
    varC = arg_0->unk_144;
    arg_0->unk_130(varC, v8, var_4, arg_C);
    return 1;
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?sub_19A750@@YAXPAUtype_7CBD0@@0@Z (folded into 0x19A750)
void sub_19A750(struct type_7CBD0 * arg_0, struct type_7CBD0 * arg_4)
{
}

#endif
