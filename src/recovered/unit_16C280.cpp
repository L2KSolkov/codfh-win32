// The free-list pools (type_16C2A0, types/alfasched.h): fixed-size elements
// in one block, each with a trailing word that links the free ones (or, in
// a taken element, holds the guard 0x2F2F2F2F unless flag 2 is set).

#include "rw/ostypes.h"
#include "types/alfasched.h"
#include "game/functions.h"
#include "rw/badevice.h"


// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0DH@BGDPCBLA@Some?5elements?5were?5not?5freed?5on?5@ @ 0x003DCC88

// match: ??0type_16C2A0@@QAE@XZ @ 0x0016C280

type_16C2A0::type_16C2A0()
{
    sub_16C3E0();
}

// match: ??1type_16C2A0@@QAE@XZ @ 0x0016C2A0
type_16C2A0::~type_16C2A0()
{
    sub_16C4D0(1);
}

// match: ?sub_16C2C0@type_16C2A0@@QAEXHHPBDH_N@Z @ 0x0016C2C0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Allocates room for arg_0 elements of arg_4 bytes (a guard word each
// unless arg_10), each padded to the alignment arg_C (4, 8, 16 or 32; 4
// otherwise); arg_8, its name, is unused.
void type_16C2A0::sub_16C2C0(RwInt32 arg_0, RwInt32 arg_4, const RwChar *arg_8, RwInt32 arg_C, bool arg_10)
{
    RwInt32 var_14;
    RwInt32 lv_10;
    RwInt32 var_C;
    RwInt32 bp_8;
    RwUInt8 *bp_4;

    unk_00 |= arg_10 ? 0 : 2;
    var_C = arg_4;
    if (unk_00 & 2)
        var_C -= 4;
    if (arg_C != 4 && arg_C != 0x10 && arg_C != 0x20 && arg_C != 8)
        arg_C = 4;
    var_14 = var_C + 4;
    lv_10 = arg_0 * var_14;
    bp_8 = 0;
    if ((arg_C - 1) & var_14)
        bp_8 = arg_C - ((arg_C - 1) & var_14);
    bp_4 = (RwUInt8 *)RwMalloc(bp_8 * arg_0 + lv_10, 0x34259); // not an address: a memory hint
    sub_16C390(arg_0, arg_4 + bp_8, bp_4, 0);
}

// match: ?sub_16C390@type_16C2A0@@QAEXHHPAEH@Z @ 0x0016C390
void type_16C2A0::sub_16C390(RwInt32 arg_0, RwInt32 arg_4, RwUInt8 *arg_8, RwInt32 arg_C)
{
    unk_04 = arg_8;
    unk_0C = arg_0;
    unk_10 = arg_4;
    unk_18 = arg_0;
    unk_14 = 0;
    sub_16C430();
}

// match: ?sub_16C3E0@type_16C2A0@@QAEXXZ @ 0x0016C3E0
void type_16C2A0::sub_16C3E0()
{
    unk_00 = 0;
    unk_04 = 0;
    unk_08 = 0;
    unk_0C = 0;
    unk_10 = 0;
    unk_14 = 0;
    unk_18 = 0;
}

// match: ?sub_16C430@type_16C2A0@@QAEXXZ @ 0x0016C430
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_16C2A0::sub_16C430()
{
    RwInt32 var_C;
    RwInt32 bp_8;
    RwUInt8 *bp_4;

    bp_8 = unk_10;
    if (unk_00 & 2)
        bp_8 -= 4;
    bp_4 = unk_04;
    for (var_C = 0; var_C < unk_0C - 1; var_C++)
    {
        ((RwUInt8 **)bp_4)[bp_8 >> 2] = bp_4 + bp_8 + 4;
        bp_4 = bp_4 + bp_8 + 4;
    }
    ((RwUInt8 **)bp_4)[bp_8 >> 2] = 0;
    unk_08 = unk_04;
}

// match: ?sub_16C4D0@type_16C2A0@@QAEX_N@Z @ 0x0016C4D0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_16C2A0::sub_16C4D0(bool arg_0)
{
    RwInt32 var_8;
    RwUInt8 *l4;

    if (arg_0 && unk_18 != unk_0C)
    {
        if (!(unk_00 & 2))
        {
            l4 = unk_04;
            for (var_8 = 0; var_8 < unk_0C; var_8++)
            {
                if (((RwInt32 *)l4)[unk_10 >> 2] == 0x2F2F2F2F) // not an address: the guard word
                    sub_19A750("Some elements were not freed on shutdown for freelist!");
                l4 = l4 + unk_10 + 4;
            }
        }
        sub_19A750("Some elements were not freed on shutdown for freelist!");
    }
    if (!(unk_00 & 1) && unk_04)
    {
        RwFree(unk_04);
        unk_04 = 0;
    }
    sub_16C3E0();
}

// match: ?sub_16C5A0@type_16C2A0@@QAEPAXH@Z @ 0x0016C5A0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void *type_16C2A0::sub_16C5A0(RwInt32 arg_0)
{
    RwUInt8 *var_8;
    RwInt32 l4;

    l4 = unk_10;
    if (unk_00 & 2)
        l4 -= 4;
    if (!unk_08)
    {
        // a compiled-out assert or trace (it shifts the register rotation)
    }
    if (!unk_08)
        return 0;
    var_8 = unk_08;
    unk_08 = ((RwUInt8 **)unk_08)[l4 >> 2];
    unk_18--;
    if (!(unk_00 & 2))
        ((RwInt32 *)var_8)[unk_10 >> 2] = 0x2F2F2F2F; // not an address: the guard word
    if (unk_0C - unk_18 > unk_14)
        unk_14 = unk_0C - unk_18;
    return var_8;
}

// match: ?sub_16C650@type_16C2A0@@QAEIPAX@Z @ 0x0016C650
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwUInt32 type_16C2A0::sub_16C650(void *arg_0)
{
    RwUInt32 var_8;
    RwInt32 l4;

    l4 = unk_10;
    if (unk_00 & 2)
        l4 -= 4;
    var_8 = (RwUInt8 *)arg_0 - unk_04;
    return var_8 / (l4 + 4);
}

// match: ?sub_16C6A0@type_16C2A0@@QAEPAXH@Z @ 0x0016C6A0
void *type_16C2A0::sub_16C6A0(RwInt32 arg_0)
{
    RwInt32 var_4;

    var_4 = unk_10;
    if (unk_00 & 2)
        var_4 -= 4;
    return unk_04 + (var_4 + 4) * arg_0;
}

// match: ?sub_16C6E0@type_16C2A0@@QAEXH@Z @ 0x0016C6E0
void type_16C2A0::sub_16C6E0(RwInt32 arg_0)
{
    sub_16C710(sub_16C6A0(arg_0));
}

// match: ?sub_16C710@type_16C2A0@@QAEXPAX@Z @ 0x0016C710
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_16C2A0::sub_16C710(void *arg_0)
{
    RwInt32 var_8;
    RwUInt8 *l4;

    var_8 = unk_10;
    if (unk_00 & 2)
        var_8 -= 4;
    if (!unk_04)
    {
        // two compiled-out asserts (each shifts the register rotation)
    }
    if (!unk_0C)
    {
    }
    l4 = (RwUInt8 *)arg_0;
    ((RwUInt8 **)l4)[var_8 >> 2] = unk_08;
    unk_08 = l4;
    unk_18++;
}

// match: ?sub_16C770@type_16C2A0@@QAE_NPAX@Z @ 0x0016C770
bool type_16C2A0::sub_16C770(void *arg_0)
{
    RwInt32 var_4;

    var_4 = unk_10;
    if (unk_00 & 2)
        var_4 -= 4;
    return arg_0 >= unk_04 && arg_0 < unk_04 + (var_4 + 4) * unk_0C;
}

// match: ?sub_16C7E0@type_16C2A0@@QAE_NXZ @ 0x0016C7E0
bool type_16C2A0::sub_16C7E0()
{
    return unk_08 == 0;
}
