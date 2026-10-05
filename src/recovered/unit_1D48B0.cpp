// The peer masks' out-of-line helpers (types/type_1DDE20_mask.h): every
// peer, the highest and lowest peers, the peers as text and their count.

#include <stdio.h>

#include "types/type_1DDE20_mask.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x0042CD04
RwUInt8 byte_42CD04[16] = { 0x0, 0x1, 0x2, 0x1, 0x3, 0x1, 0x2, 0x1, 0x4, 0x1, 0x2, 0x1, 0x3, 0x1, 0x2, 0x1 };
// 0x004FEC78
RwChar byte_4FEC78[0x80];
// End of its data definitions.


// The bits a value up to arg_0 needs (game/netmsg.h).
RwInt32 sub_1F84A0(RwUInt32 arg_0);
// The lowest set bit of each nibble, one-based (0 for none).
extern RwUInt8 byte_42CD04[16];
// The text sub_1D4990 returns.
extern RwChar byte_4FEC78[0x80];

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_05LGDANENA@Empty?$AA@ @ 0x003E4F14
// match: ?byte_42CD04@@3PAEA @ 0x0042CD04

// match: ??0type_1DDE20_mask@@QAE@W4type_1DDE20_mask_fill@@@Z @ 0x001D48B0

type_1DDE20_mask::type_1DDE20_mask(type_1DDE20_mask_fill arg_0)
{
    switch (arg_0)
    {
    case type_1DDE20_mask_fill_all:
        unk_00 = 0xFFFF;
    }
}

// match: ?sub_1D48E0@type_1DDE20_mask@@QAEHXZ @ 0x001D48E0
RwInt32 type_1DDE20_mask::sub_1D48E0()
{
    // Two compiled-out checks (docs/toolchain.md): the registers after them
    // are four loads on.
    if (!unk_00)
    {
    }
    if (!unk_00)
    {
    }
    return sub_1F84A0(unk_00) - 1;
}

// match: ?sub_1D4900@type_1DDE20_mask@@QAEHXZ @ 0x001D4900
RwInt32 type_1DDE20_mask::sub_1D4900()
{
    RwUInt32 bits;
    RwInt32 n;
    RwInt32 v;

    bits = unk_00;
    v = 0;
    // Two compiled-out checks (docs/toolchain.md): the registers after them
    // are four loads on.
    if (!unk_00)
    {
    }
    if (!unk_00)
    {
    }
    if (!(bits & 0xFFFF))
    {
        v += 16;
        bits >>= 16;
    }
    if (!(bits & 0xFF))
    {
        v += 8;
        bits >>= 8;
    }
    if (!(bits & 0xF))
    {
        v += 4;
        bits >>= 4;
    }
    n = v + byte_42CD04[bits & 0xF] - 1;
    return n;
}

// match: ?sub_1D4990@type_1DDE20_mask@@QAEPBDXZ @ 0x001D4990
const RwChar *type_1DDE20_mask::sub_1D4990()
{
    RwInt32 first;
    RwInt32 len;
    RwUInt32 i;
    RwUInt32 last;
    RwInt32 lowest;

    if (!unk_00)
        return "Empty";
    lowest = sub_1D4900();
    last = sub_1D48E0();
    len = 0;
    first = 1;
    for (i = lowest; i <= last; i++)
    {
        // Two compiled-out checks (docs/toolchain.md): the registers after
        // them are four loads on.
        if (!unk_00)
        {
        }
        if (!unk_00)
        {
        }
        if (test(i))
        {
            if (!first)
                len += sprintf(&byte_4FEC78[len], ", ");
            len += sprintf(&byte_4FEC78[len], "%d", i);
            first = 0;
        }
    }
    byte_4FEC78[len] = 0;
    return byte_4FEC78;
}

// match: ?sub_1D4A60@type_1DDE20_mask@@QAEHXZ @ 0x001D4A60
RwInt32 type_1DDE20_mask::sub_1D4A60()
{
    RwUInt32 bits;
    RwInt32 n;

    bits = unk_00;
    n = 0;
    while (bits)
    {
        if (bits & 1)
            n++;
        bits >>= 1;
    }
    return n;
}
