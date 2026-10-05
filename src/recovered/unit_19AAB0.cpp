// The game's save state (game/savestate.h): the difficulty, the state's
// defaults and set-up from the shell, and its accessors.

#include "rw/ostypes.h"
#include <string.h>
#include "game/savestate.h"
#include "game/data.h"
#include "game/gameloop.h"
#include "game/functions.h"
#include "types/type_DA0A0.h"

#include "types/type_4F2940.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x0042B714
RwInt32 dword_42B714 = -1;
// 0x004F2860
RwReal flt_4F2860[3];
// 0x004F286C
RwReal flt_4F286C[3];
// 0x004F2878
RwReal flt_4F2878[3];
// 0x004F2884
RwReal flt_4F2884[3];
// 0x004F2890
RwReal flt_4F2890[3];
// 0x004F289C
RwReal flt_4F289C[3];
// 0x004F28A8
RwReal flt_4F28A8[3];
// 0x004F28B4
RwReal flt_4F28B4[3];
// 0x004F28C0
RwReal flt_4F28C0[3];
// 0x004F28CC
RwReal flt_4F28CC[3];
// 0x004F28D8
RwReal flt_4F28D8[3];
// 0x004F28E4
RwReal flt_4F28E4[3];
// 0x004F28F0
type_4F28F0 *dword_4F28F0;
// 0x004F28F4
RwInt32 dword_4F28F4;
// 0x004F28F8
RwUInt8 byte_4F28F8;
// 0x004F28FC
RwInt32 dword_4F28FC;
// 0x004F2900
RwInt32 dword_4F2900;
// 0x004F2908
type_4F28F0 byte_4F2908;
// 0x004F5DD8
#ifndef CODFH_PLAIN
type_4F5DD8 unk_4F5DD8[1];
#endif
// End of its data definitions.


// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).
type_4F2940 unk_4F2940;
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0BM@OGNKNLDP@difficulty?5?$DN?5?$CFd?5from?5shell?6?$AA@ @ 0x003E00D0
// match: ??_C@_05KMGJCOIF@MP_10?$AA@ @ 0x003E00EC
// match: ??_C@_04DLNHHPIP@MP_9?$AA@ @ 0x003E00F4
// match: ??_C@_04KFFEFCAB@MP_7?$AA@ @ 0x003E00FC
// match: ??_C@_04LMEPGDEA@MP_6?$AA@ @ 0x003E0104
// match: ??_C@_04JHGCDAID@MP_5?$AA@ @ 0x003E010C
// match: ??_C@_04IOHJABMC@MP_4?$AA@ @ 0x003E0114
// match: ??_C@_04NICDKGEE@MP_2?$AA@ @ 0x003E011C
// match: ??_C@_04PDAOPFIH@MP_1?$AA@ @ 0x003E0124
// match: ??_C@_06CCLMOILL@L_NULL?$AA@ @ 0x003E012C
// match: ??_C@_03JBJLGPFL@end?$AA@ @ 0x003E0134
// match: ??_C@_05KKCIMGE@error?$AA@ @ 0x003E0138
// match: ??_C@_02KAJCLHKP@no?$AA@ @ 0x003E0140
// match: ??_C@_03ICICOMAL@yes?$AA@ @ 0x003E0144
// match: ??_C@_0L@GPECBCMJ@Liveupdate?$AA@ @ 0x003E0148
// match: ??_C@_08JLLDKAGD@Debugger?$AA@ @ 0x003E0154
// match: ??_C@_09NBJKPNHD@Dashboard?$AA@ @ 0x003E0160
// match: ??_C@_07NBCGADJA@Unknown?$AA@ @ 0x003E016C
// match: ??_C@_05PABKJLOM@Title?$AA@ @ 0x003E0174
// match: .CRT$XCU+0 @ 0x00427194
// match: ?dword_42B714@@3HA @ 0x0042B714
// match: ?off_42B718@?1??sub_19B060@@YAPBDH@Z@4PAPBDA @ 0x0042B718

// match: _$E1 @ 0x0030C0B0
// match: ?sub_19AAB0@@YAXXZ @ 0x0019AAB0

// Takes the difficulty from the state and resets its multipliers.
void sub_19AAB0()
{
    RwInt32 var_4;

    dword_42B714 = sub_19B080();
    sub_19A750("difficulty = %d from shell\n", dword_42B714);
    for (var_4 = 0; var_4 < 3; var_4++)
    {
        flt_4F286C[var_4] = 1.0f;
        flt_4F28E4[var_4] = 1.0f;
        flt_4F28A8[var_4] = 1.0f;
        flt_4F2878[var_4] = 1.0f;
        flt_4F2860[var_4] = 1.0f;
        flt_4F289C[var_4] = 1.0f;
        flt_4F2890[var_4] = 1.0f;
        flt_4F28B4[var_4] = 1.0f;
        flt_4F28D8[var_4] = 1.0f;
        flt_4F28C0[var_4] = 1.0f;
        flt_4F28CC[var_4] = 1.0f;
        flt_4F2884[var_4] = 1.0f;
    }
}

// match: ?sub_19ABA0@type_DA0A0@@QAEGXZ @ 0x0019ABA0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The record's checksum: its 200 bytes' sum less the checksum's own two
// (0 for a blank record, "KNLB").
RwUInt16 type_DA0A0::sub_19ABA0()
{
    RwUInt32 var_C;
    RwUInt16 bp_8;
    RwChar *bp_4;

    if (is_blank())
        return 0;
    bp_8 = 0;
    bp_4 = (RwChar *)this;
    for (var_C = 0; var_C < 200; var_C++)
    {
        bp_8 += *bp_4;
        bp_4++;
    }
    bp_4 = (RwChar *)&unk_1C;
    bp_8 -= *bp_4;
    bp_4++;
    bp_8 -= *bp_4;
    return bp_8;
}

// match: ?sub_19AC40@type_DA0A0_64@@QAEPAU1@PAUtype_D90B0@@@Z @ 0x0019AC40
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
type_DA0A0_64 *type_DA0A0_64::sub_19AC40(type_D90B0 *arg_0)
{
    RwUInt32 var_8;
    RwUInt32 l4;

    unk_00.unk_54 = arg_0->unk_54;
    unk_00.unk_50 = arg_0->unk_50;
    unk_00.unk_58 = arg_0->unk_58;
    unk_00.unk_00 = arg_0->unk_00;
    unk_00.unk_04 = arg_0->unk_04;
    for (l4 = 0; l4 < 2; l4++)
    {
        unk_00.unk_10[l4] = arg_0->unk_10[l4];
        unk_00.unk_08[l4] = arg_0->unk_08[l4];
    }
    unk_00.unk_18.unk_00 = arg_0->unk_18.unk_00;
    for (var_8 = 0; var_8 < 13; var_8++)
        unk_00.unk_18.unk_04[var_8] = arg_0->unk_18.unk_04[var_8];
    memset(unk_5C, 0, 8);
    return this;
}

// match: ?sub_19AD20@@YAXXZ @ 0x0019AD20
// Sets the state up once: its defaults, then what the shell chose (the
// language, player, pad, difficulty and profile name), or with no shell
// settings the first pad and profile.
void sub_19AD20()
{
    // Unused: the image keeps three slots above its inlines' temporaries.
    RwInt32 var_4;
    RwInt32 var_8;
    RwInt32 var_C;

    if (dword_4F2900)
        return;
    dword_4F2900 = 1;
    byte_4F28F8 = 0;
    byte_4F2908.sub_19AEA0();
    dword_4F28F0 = &byte_4F2908;
    dword_4F28F4 = dword_4F28F0->unk_10;
    if (dword_4F45F8 && !dword_4F45F8->unk_20)
    {
        sub_19B0C0(dword_4F45F8->unk_28);
        set_4F28F0_unk_1C(dword_4F45F8->unk_30);
        unk_4B9308.sub_EEAA0(dword_4F45F8->unk_24);
        dword_4B9E5C = 0;
        set_4F28F0_unk_22(dword_4F45F8->unk_2C != 0);
        set_4F28F0_unk_18(dword_4F45F8->unk_34);
        set_4F28F0_unk_183(unk_4F5DD8[dword_4F45F8->unk_14].unk_00);
    }
    else
    {
        unk_4B9308.sub_EEAA0(0);
        dword_4B9E5C = 0;
        sub_19B0C0(2);
        dword_4F28F0->unk_22 = 1;
        dword_4F45F8->unk_14 = 0;
        set_4F28F0_unk_183(unk_4F5DD8[dword_4F45F8->unk_14].unk_00);
    }
}

// A string copy with no address and so no database name, named for what it
// does. Evidence: the state's defaults (sub_19AEA0) copy "Player" through
// two temporaries holding the arguments.
inline void copy_string(RwChar *arg_0, const RwChar *arg_4)
{
    while (*arg_4)
    {
        *arg_0 = *arg_4;
        arg_0++;
        arg_4++;
    }
    *arg_0 = 0;
}

// match: ?sub_19AEA0@type_4F28F0@@QAEXXZ @ 0x0019AEA0
void type_4F28F0::sub_19AEA0()
{
    // Unused: the image keeps six slots above its inlines' temporaries.
    RwInt32 var_4;
    RwInt32 var_8;
    RwInt32 var_C;
    RwInt32 var_10;
    RwInt32 var_14;
    RwInt32 var_18;

    unk_00 = -1;
    unk_04 = -1;
    unk_08 = 0;
    unk_0C = 1;
    unk_10 = 1;
    unk_14 = 1;
    unk_18 = 1;
    unk_1C = 0;
    unk_20 = 1;
    unk_21 = 1;
    unk_22 = 0;
    unk_28 = 1;
    unk_24 = 1;
    unk_182 = 0;
    unk_2C = 0;
    unk_30 = 0;
    unk_34 = 0;
    unk_44 = 0;
    unk_48[0] = 0;
    unk_54 = 1;
    unk_58 = 0;
    unk_5C.sub_D90B0();
    unk_B8.sub_DA0A0();
    unk_38.clear();
    unk_180 = 1;
    unk_181 = 1;
    copy_string(unk_183, "Player");
}

// match: ?sub_19B000@@YAXH@Z @ 0x0019B000
// Sets the level (a negative one clears it).
void sub_19B000(RwInt32 arg_0)
{
    if (dword_4F28F0)
    {
        if (arg_0 >= 0)
        {
            dword_4F28F0->unk_08 = 1;
            dword_4F28F0->unk_10 = arg_0;
            dword_4F28F4 = arg_0;
        }
        else
            dword_4F28F0->unk_08 = 0;
    }
}

// match: ?sub_19B050@@YAHXZ @ 0x0019B050
RwInt32 sub_19B050()
{
    return dword_4F28F4;
}

// match: ?sub_19B060@@YAPBDH@Z @ 0x0019B060
// The level arg_0's name, once there is a state.
const RwChar *sub_19B060(RwInt32 arg_0)
{
    // The levels' names (0x42B718): a static of this function, its literals come out
    // with it, after sub_19AAB0's, as the image has them.
    static const RwChar *off_42B718[10] = { "L_NULL", "MP_1", "MP_2", "MP_4", "MP_5", "MP_6", "MP_7", "MP_9", "MP_10", 0 };
    if (dword_4F28F0)
        return off_42B718[arg_0];
    return 0;
}

// match: ?sub_19B080@@YAHXZ @ 0x0019B080
RwInt32 sub_19B080()
{
    if (dword_4F28F0)
        return dword_4F28F0->unk_24;
    return -1;
}

// match: ?sub_19B0A0@@YAHXZ @ 0x0019B0A0
// The language.
RwInt32 sub_19B0A0()
{
    if (dword_4F28F0)
        return dword_4F28F0->unk_34;
    return dword_4F28FC;
}

// match: ?sub_19B0C0@@YAXH@Z @ 0x0019B0C0
void sub_19B0C0(RwInt32 arg_0)
{
    if (dword_4F28F0)
        dword_4F28F0->unk_34 = arg_0;
    dword_4F28FC = arg_0;
}

// Not in the image: a stand-in for a function the original object held last, which
// the link dropped (/OPT:REF) but whose literals stayed first: "end", "error", "no",
// "yes" and the title kinds' names sit after the levels' names (0x3E0134-0x3E017C),
// before their users in later objects (unit_1E3430, XGRAPHICS, unit_216130,
// unit_19CB20's table). A function's literals come out last-referenced first.
// Unreferenced.
void dropped_3E0134(const RwChar **arg_0)
{
    arg_0[0] = "Title";
    arg_0[0] = "Unknown";
    arg_0[0] = "Dashboard";
    arg_0[0] = "Debugger";
    arg_0[0] = "Liveupdate";
    arg_0[1] = "yes";
    arg_0[2] = "no";
    arg_0[3] = "error";
    arg_0[4] = "end";
}
