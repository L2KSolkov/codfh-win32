/*
 * The network's bit stream (game/netmsg.h): its big-endian words read and
 * written a bit field at a time, and the bits, floats, signed and ranged
 * values, message numbers and bytes built on them.
 */
#include <stdlib.h>
#include "game/netmsg.h"

// The words' bytes are swapped by inline assembly, into dst from the word at
// src and into the word at dst from src.
#define LOAD_SWAPPED(dst, src)                                                                                         \
    {                                                                                                                  \
        RwUInt32 *lcl_30 = (src);                                                                                      \
        RwUInt32 local_2C;                                                                                             \
        __asm {                                                                                                        \
            __asm mov eax, lcl_30                                                                                      \
            __asm mov ebx, [eax]                                                                                       \
            __asm ror bx, 8                                                                                            \
            __asm ror ebx, 16                                                                                          \
            __asm ror bx, 8                                                                                            \
            __asm mov local_2C, ebx                                                                                    \
        }                                                                                                              \
        (dst) = local_2C;                                                                                              \
    }
#define STORE_SWAPPED(dst, src)                                                                                        \
    {                                                                                                                  \
        RwUInt32 *lcl_30 = (dst);                                                                                      \
        __asm {                                                                                                        \
            __asm mov eax, lcl_30                                                                                      \
            __asm mov ebx, src                                                                                         \
            __asm ror bx, 8                                                                                            \
            __asm ror ebx, 16                                                                                          \
            __asm ror bx, 8                                                                                            \
            __asm mov [eax], ebx                                                                                       \
        }                                                                                                              \
    }

// match: ?sub_1F81E0@@YAIPAIIII@Z @ 0x001F81E0
RwUInt32 sub_1F81E0(RwUInt32 *arg_0, RwUInt32 arg_4, RwUInt32 arg_8, RwUInt32 arg_C)
{
    RwUInt64 r10 = arg_8 >> 5;
    RwInt32 lv_1C = 64 - (arg_8 & 31) - arg_C;
    BITSTREAM_CHECK((arg_8 & 31) + arg_C <= 64);
    RwUInt32 bp_4;
    LOAD_SWAPPED(bp_4, arg_0 + r10);
    RwUInt32 lv_20;
    LOAD_SWAPPED(lv_20, arg_0 + (r10 + 1));
    RwUInt64 bp_18 = (((RwUInt64)1 << arg_C) - 1) << lv_1C;
    RwUInt64 lv_28 = ((RwUInt64)bp_4 & (bp_18 >> 32)) << 32;
    BITSTREAM_CHECK(lv_1C >= 0);
    lv_28 |= (RwUInt64)lv_20 & (bp_18 & 0xFFFFFFFF);
    lv_28 >>= lv_1C;
    return (RwUInt32)lv_28;
}

// match: ?sub_1F8300@@YAXPAIIIII@Z @ 0x001F8300
void sub_1F8300(RwUInt32 *arg_0, RwUInt32 arg_4, RwUInt32 arg_8, RwUInt32 arg_C, RwUInt32 arg_10)
{
    RwUInt64 lv_28 = arg_C;
    BITSTREAM_CHECK((arg_8 & 31) + arg_10 <= 64);
    RwInt32 lv_1C = 64 - (arg_8 & 31) - arg_10;
    BITSTREAM_CHECK(!(arg_C >> arg_10));
    RwUInt64 r10 = arg_8 >> 5;
    lv_28 <<= lv_1C;
    RwUInt64 bp_18 = ~((((RwUInt64)1 << arg_10) - 1) << lv_1C);
    RwUInt32 bp_4;
    LOAD_SWAPPED(bp_4, arg_0 + r10);
    RwUInt32 lv_20;
    LOAD_SWAPPED(lv_20, arg_0 + (r10 + 1));
    bp_4 &= bp_18 >> 32;
    bp_4 |= lv_28 >> 32;
    lv_20 &= bp_18 & 0xFFFFFFFF;
    lv_20 |= lv_28 & 0xFFFFFFFF;
    STORE_SWAPPED(arg_0 + r10, bp_4);
    STORE_SWAPPED(arg_0 + (r10 + 1), lv_20);
}

// match: ?sub_1F84A0@@YAHI@Z @ 0x001F84A0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_1F84A0(RwUInt32 arg_0)
{
    RwUInt32 local_8 = arg_0;
    RwInt32 var_4 = 0;
    if (local_8 >= 0x10000)
    {
        var_4 += 16;
        local_8 >>= 16;
    }
    BITSTREAM_CHECK(!(local_8 >> 16));
    if (local_8 >= 0x100)
    {
        var_4 += 8;
        local_8 >>= 8;
    }
    BITSTREAM_CHECK(!(local_8 >> 8));
    if (local_8 >= 0x10)
    {
        var_4 += 4;
        local_8 >>= 4;
    }
    BITSTREAM_CHECK(!(local_8 >> 4));
    var_4 += unk_42D25C[local_8];
    return var_4;
}

// match: ?sub_1F8520@type_1F8560@@QAEXI@Z @ 0x001F8520
void type_1F8560::sub_1F8520(RwUInt32 arg_0)
{
    BITSTREAM_CHECK(unk_00);
    sub_1F8300((RwUInt32 *)unk_00, unk_04, unk_08, arg_0, 1);
    unk_08 += 1;
}

// match: ?sub_1F8560@type_1F8560@@QAEIXZ @ 0x001F8560
RwUInt32 type_1F8560::sub_1F8560()
{
    RwUInt32 var_4 = sub_1F81E0((RwUInt32 *)unk_00, unk_04, unk_08, 1);
    unk_08 += 1;
    return var_4;
}

// match: ?sub_1F85A0@type_1F8560@@QAEMXZ @ 0x001F85A0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwReal type_1F8560::sub_1F85A0()
{
    RwUInt32 var_4 = sub_1F81E0((RwUInt32 *)unk_00, unk_04, unk_08, 32);
    RwReal *local_8 = (RwReal *)&var_4;
    unk_08 += 32;
    return *local_8;
}

// match: ?sub_1F85F0@type_1F8560@@QAEXM@Z @ 0x001F85F0
void type_1F8560::sub_1F85F0(RwReal arg_0)
{
    RwUInt32 *var_4 = (RwUInt32 *)&arg_0;
    sub_1F8300((RwUInt32 *)unk_00, unk_04, unk_08, *var_4, 32);
    unk_08 += 32;
}

// match: ?sub_1F8640@type_1F8560@@QAEMMMH@Z @ 0x001F8640
RwReal type_1F8560::sub_1F8640(RwReal arg_0, RwReal arg_4, RwInt32 arg_8)
{
    RwReal bp_4;
    RwReal ebp_10 = arg_4 - arg_0;
    BITSTREAM_CHECK(unk_00);
    BITSTREAM_CHECK(unk_00);
    RwReal x8 = (1 << arg_8) - 1.0f;
    RwUInt32 locC = sub_1F81E0((RwUInt32 *)unk_00, unk_04, unk_08, arg_8);
    unk_08 += arg_8;
    bp_4 = locC / x8 * ebp_10 + arg_0;
    BITSTREAM_CHECK(unk_00);
    return bp_4;
}

// match: ?sub_1F86D0@type_1F8560@@QAEXMMMH@Z @ 0x001F86D0
void type_1F8560::sub_1F86D0(RwReal arg_0, RwReal arg_4, RwReal arg_8, RwInt32 arg_C)
{
    RwReal x8 = arg_8 - arg_4;
    BITSTREAM_CHECK(unk_00);
    BITSTREAM_CHECK(unk_00);
    RwReal bp_4 = (1 << arg_C) - 1.0f;
    arg_0 = (arg_0 - arg_4) * bp_4 / x8;
    BITSTREAM_CHECK(unk_00);
    sub_1F8300((RwUInt32 *)unk_00, unk_04, unk_08, (RwInt32)arg_0, arg_C);
    unk_08 += arg_C;
}

// match: ?sub_1F8750@type_1F8560@@QAEHH@Z @ 0x001F8750
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_1F8560::sub_1F8750(RwInt32 arg_0)
{
    RwUInt32 local_8 = sub_1F8560();
    BITSTREAM_CHECK(unk_00);
    RwInt32 var_4 = sub_1F81E0((RwUInt32 *)unk_00, unk_04, unk_08, arg_0 - 1);
    unk_08 += arg_0;
    if (local_8)
        var_4 = -var_4;
    return var_4;
}

// match: ?sub_1F87B0@type_1F8560@@QAEXHH@Z @ 0x001F87B0
void type_1F8560::sub_1F87B0(RwInt32 arg_0, RwInt32 arg_4)
{
    BITSTREAM_CHECK(unk_00);
    sub_1F8520(arg_0 < 0);
    sub_1F8300((RwUInt32 *)unk_00, unk_04, unk_08, abs(arg_0), arg_4 - 1);
    unk_08 += arg_4;
}

// match: ?sub_1F8810@type_1F8560@@QAEIH@Z @ 0x001F8810
RwUInt32 type_1F8560::sub_1F8810(RwInt32 arg_0)
{
    RwUInt32 var_4 = sub_1F81E0((RwUInt32 *)unk_00, unk_04, unk_08, arg_0);
    unk_08 += arg_0;
    return var_4;
}

// match: ?sub_1F8860@type_1F8560@@QAEXIH@Z @ 0x001F8860
void type_1F8560::sub_1F8860(RwUInt32 arg_0, RwInt32 arg_4)
{
    sub_1F8300((RwUInt32 *)unk_00, unk_04, unk_08, arg_0, arg_4);
    unk_08 += arg_4;
}

// match: ?sub_1F88A0@type_1F8560@@QAEXI@Z @ 0x001F88A0
void type_1F8560::sub_1F88A0(RwUInt32 arg_0)
{
    RwUInt32 x8 = sub_1F84A0(arg_0);
    RwUInt32 bp_4 = (x8 + 3) / 4 - 1;
    BITSTREAM_CHECK(unk_00);
    if (++bp_4 == 0)
        bp_4 = 1;
    sub_1F8300((RwUInt32 *)unk_00, unk_04, unk_08, bp_4 - 1, 3);
    unk_08 += 3;
    sub_1F8300((RwUInt32 *)unk_00, unk_04, unk_08, arg_0, bp_4 * 4);
    unk_08 += bp_4 * 4;
}

// match: ?sub_1F8950@type_1F8560@@QAEHXZ @ 0x001F8950
RwInt32 type_1F8560::sub_1F8950()
{
    RwUInt32 locC = sub_1F81E0((RwUInt32 *)unk_00, unk_04, unk_08, 3);
    unk_08 += 3;
    BITSTREAM_CHECK(unk_00);
    RwUInt32 x8 = locC * 4 + 4;
    RwInt32 bp_4 = sub_1F81E0((RwUInt32 *)unk_00, unk_04, unk_08, x8);
    unk_08 += x8;
    return bp_4;
}

// match: ?sub_1F89D0@type_1F8560@@QAEXPBXH@Z @ 0x001F89D0
void type_1F8560::sub_1F89D0(const void *arg_0, RwInt32 arg_4)
{
    type_1F8560 var_C(arg_0, arg_4);
    RwUInt32 var_10 = arg_4;
    while (var_10 >= 32)
    {
        sub_1F8860(var_C.sub_1F8810(32), 32);
        var_10 -= 32;
    }
    if (var_10)
        sub_1F8860(var_C.sub_1F8810(var_10), var_10);
}

// match: ?sub_1F8A40@type_1F8560@@QAEXPADH@Z @ 0x001F8A40
void type_1F8560::sub_1F8A40(RwChar *arg_0, RwInt32 arg_4)
{
    type_1F8560 var_C(arg_0, arg_4);
    RwUInt32 var_10 = arg_4;
    while (var_10 >= 32)
    {
        var_C.sub_1F8860(sub_1F8810(32), 32);
        var_10 -= 32;
    }
    if (var_10)
        var_C.sub_1F8860(sub_1F8810(var_10), var_10);
}

// match: ?sub_1F8AB0@type_1F8560@@QAEXH@Z @ 0x001F8AB0
void type_1F8560::sub_1F8AB0(RwInt32 arg_0)
{
    sub_1F8520(arg_0 < 0);
    if (arg_0 < 0)
        arg_0 = -arg_0;
    sub_1F88A0(arg_0);
}

// match: ?sub_1F8AF0@type_1F8560@@QAEHXZ @ 0x001F8AF0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_1F8560::sub_1F8AF0()
{
    RwUInt32 local_8 = sub_1F8560();
    RwInt32 var_4 = sub_1F8950();
    if (local_8)
        return -var_4;
    return var_4;
}

// match: ?sub_1F8B30@type_1F8560@@QAEHHH@Z @ 0x001F8B30
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_1F8560::sub_1F8B30(RwInt32 arg_0, RwInt32 arg_4)
{
    RwUInt32 local_8 = sub_1F84A0(arg_4 - arg_0);
    RwInt32 var_4 = sub_1F81E0((RwUInt32 *)unk_00, unk_04, unk_08, local_8);
    unk_08 += local_8;
    var_4 += arg_0;
    return var_4;
}

// match: ?sub_1F8B90@type_1F8560@@QAEXHHH@Z @ 0x001F8B90
void type_1F8560::sub_1F8B90(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    BITSTREAM_CHECK(unk_00);
    RwUInt32 var_4 = sub_1F84A0(arg_8 - arg_4);
    sub_1F8300((RwUInt32 *)unk_00, unk_04, unk_08, arg_0 - arg_4, var_4);
    unk_08 += var_4;
}
