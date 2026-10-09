// A 1-D gradient noise (Ken Perlin's noise1: its permutation dword_4E6718
// and gradients dword_4E5F10, set up on first use) and its clock
// (type_4E6F20, unk_4E6F20), which the camera sway's noises read.

#include "rw/ostypes.h"
#include "game/data.h"
#include "types/type_4E5E50.h"
#include "types/type_4E6F20.h"
#include <stdlib.h>

// Its data definitions (PLAN M5), in the image's address order.
// 0x003DDB80
extern const RwReal flt_3DDB80 = 16.666666f;
// 0x0042A040
RwInt32 dword_42A040 = 1;
// 0x004E5F10
RwReal dword_4E5F10[0x202];
// 0x004E6718
RwInt32 dword_4E6718[0x202];
// End of its data definitions.

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3DDB80@@3MB @ 0x003DDB80
// match: __real@3c888889 @ 0x003DDB84
// match: __real@45800000 @ 0x003DDB88
// match: __real@46800000 @ 0x003DDB8C
// match: .CRT$XCU+0 @ 0x00427160
// match: ?dword_42A040@@3HA @ 0x0042A040

// match: _$E1 @ 0x0030BED0
// match: _$E2 @ 0x0030E970

type_4E6F20 unk_4E6F20;

// match: ?sub_176B30@@YAMXZ @ 0x00176B30
// sp-match: ?sub_176B30@@YAMXZ @ 0x00111960
// The clock: the frame count in seconds (at 60 a second).
RwReal sub_176B30()
{
    RwReal var_4;

    return var_4 = (var_4 = (RwReal)dword_4B87D8) * (1.0f / 60.0f);
}

// match: ??0type_4E6F20@@QAE@XZ @ 0x00176B60
// sp-match: ??0type_4E6F20@@QAE@XZ @ 0x00111980
type_4E6F20::type_4E6F20()
{
    unk_00 = sub_176B30;
}

// match: ?sub_176B80@type_4E6F20@@QAEMM@Z @ 0x00176B80
// sp-match: ?sub_176B80@type_4E6F20@@QAEMM@Z @ 0x00111AE0
// The noise at arg_0: Perlin's noise1, his declarations and macros
// (setup, s_curve, lerp) as written out; the locals' slots match his
// declaration order.
RwReal type_4E6F20::sub_176B80(RwReal arg_0)
{
    RwInt32 bx0, bx1;
    RwReal rx0, rx1, sx, t, u, v, vec[1];

    vec[0] = arg_0;
    if (dword_42A040)
        sub_176C50();
    t = vec[0] + 4096.0f;
    bx0 = (RwInt32)t & 0xFF;
    bx1 = (bx0 + 1) & 0xFF;
    rx0 = t - (RwInt32)t;
    rx1 = rx0 - 1.0f;
    sx = rx0 * rx0 * (3.0f - 2.0f * rx0);
    u = rx0 * dword_4E5F10[dword_4E6718[bx0]];
    v = rx1 * dword_4E5F10[dword_4E6718[bx1]];
    return u + sx * (v - u);
}

// match: ?sub_176C40@type_4E6F20@@QAEMXZ @ 0x00176C40
// sp-match: ?sub_176C40@type_4E6F20@@QAEMXZ @ 0x00111990
RwReal type_4E6F20::sub_176C40()
{
    return unk_00();
}

// match: ?sub_176C50@type_4E6F20@@QAEXXZ @ 0x00176C50
// sp-match: ?sub_176C50@type_4E6F20@@QAEXXZ @ 0x001119A0
// Sets the noise up once: the permutation shuffled, random gradients, each
// table repeated past its end.
void type_4E6F20::sub_176C50()
{
    RwInt32 i;
    RwInt32 k;
    RwInt32 j;

    if (dword_42A040)
        dword_42A040 = 0;
    else
        return;
    for (i = 0; i < 0x100; i++)
    {
        dword_4E6718[i] = i;
        dword_4E5F10[i] = (RwReal)(rand() % 0x200 - 0x100) / 0x100;
    }
    while (--i)
    {
        k = dword_4E6718[i];
        dword_4E6718[i] = dword_4E6718[j = rand() % 0x100];
        dword_4E6718[j] = k;
    }
    for (i = 0; i < 0x102; i++)
    {
        dword_4E6718[0x100 + i] = dword_4E6718[i];
        dword_4E5F10[0x100 + i] = dword_4E5F10[i];
    }
}

// match: ?sub_176D70@type_176040@@QAEMXZ @ 0x00176D70
// sp-match: ?sub_176D70@type_176040@@QAEMXZ @ 0x00111B60
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Its value now: its octaves of the noise along the clock by its speed
// from its seed (reseeded when out of range), each half the last, by its
// size.
RwReal type_176040::sub_176D70()
{
    RwReal var_10;
    RwReal var_C;
    RwUInt32 bp_8;
    RwReal bp_4;

    if (unk_00 < 0.0f || unk_00 > 16384.0f)
        unk_00 = (RwReal)(rand() % 16384);
    var_C = unk_4E6F20.sub_176C40() * unk_08 + unk_00;
    bp_4 = 0;
    bp_8 = 1;
    var_10 = 1.0f;
    while (bp_8 <= (RwUInt32)unk_04)
    {
        bp_4 += unk_4E6F20.sub_176B80(bp_8 * var_C) * var_10;
        var_10 *= 0.5f;
        bp_8++;
    }
    return bp_4 * unk_0C;
}
