// cTimeKeeper, the network game's third part (types/type_DC400.h): its
// constructor, start, peers joining and leaving, its step (the pings and
// each peer's latency and clock offset) and the ping message. Named by its
// trace; its original file name is not in the image, so it is named for its
// start address.

#include <string.h>
#include "rw/ostypes.h"
#include "types/type_DC400.h"
#include "types/type_1CCA10.h"
#include "types/type_1DDE20_mask.h"
#include "game/gameloop.h"
#include "game/netmsg.h"


extern void (*off_42CD14)(const RwChar *arg_0, ...);

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0HA@DHEMECHM@KNET?3?5cTimeKeeper?$CI?$CJ?5?9?5Packet?5sen@ @ 0x003E4F20
// match: ??_C@_0CK@FEGLOLIA@Warning?3?5error?5in?5unpack?5of?5ping@ @ 0x003E4F90

// match: ??0cTimeKeeper@@QAE@XZ @ 0x001D4AB0

cTimeKeeper::cTimeKeeper()
{
}

// match: ?sub_1D4B80@cTimeKeeper@@QAEXPAUtype_4F8054@@@Z @ 0x001D4B80
void cTimeKeeper::sub_1D4B80(type_4F8054 *arg_0)
{
    RwUInt32 var_4;

    for (var_4 = 0; var_4 < 16; var_4++)
        sub_1D4C00(var_4);
    unk_08 = 0;
    unk_04 = 0;
    unk_69C.unk_00 = 0;
    unk_00 = arg_0;
    memset(unk_60C, 0, 0x10);
}

// match: ?sub_1D4C00@cTimeKeeper@@QAEXH@Z @ 0x001D4C00
void cTimeKeeper::sub_1D4C00(RwInt32 arg_0)
{
    // A compiled-out check (docs/toolchain.md).
    if (!unk_08)
    {
    }
    memset(unk_0C[arg_0], 0, 0x60);
    unk_61C[arg_0] = 0;
    unk_65C[arg_0] = 0;
}

// match: ?sub_1D4C60@cTimeKeeper@@QAEXH@Z @ 0x001D4C60
void cTimeKeeper::sub_1D4C60(RwInt32 arg_0)
{
    unk_69C.include(arg_0);
}

// match: ?sub_1D4CA0@cTimeKeeper@@QAEXXZ @ 0x001D4CA0
void cTimeKeeper::sub_1D4CA0()
{
    RwUInt32 a;
    type_1CCA10 var_8 = sub_1CCA10();
    RwUInt32 b;

    if (var_8.get_unk_00() - unk_04.get_unk_00() >= 600)
    {
        type_1D7560 p;
        type_1DDE20_mask c;
        type_1DDE20_mask m = unk_00->get_unk_B0()->sub_1A8050();
        RwInt32 e;

        p.unk_00 = var_8;
        p.unk_04 = 0;
        for (a = 0; a < 4; a++)
        {
            b = unk_08 + a;
            c.include_checked((unk_08 + b) % 16);
        }
        unk_08 = b % 16;
        // A compiled-out check (docs/toolchain.md).
        if (!c.unk_00)
        {
        }
        c.unk_00 |= unk_69C.unk_00;
        unk_69C.unk_00 = 0;
        // Two compiled-out checks (docs/toolchain.md).
        if (!m.unk_00)
        {
        }
        if (!m.unk_00)
        {
        }
        m = m & c;
        if (!m.empty())
        {
            p.sub_1D7560(unk_00, m, &e);
            for (a = 0; a < 16; a++)
            {
                if (m.test(a))
                {
                    b = unk_60C[a];
                    unk_0C[a][b].unk_00 = p.unk_00;
                    unk_0C[a][b].unk_04 = 0;
                    unk_0C[a][b].unk_08 = 0;
                    unk_60C[a] = (unk_60C[a] + 1) % 8;
                }
            }
        }
        unk_04 = var_8;
        for (a = 0; a < 16; a++)
        {
            RwInt32 c = 0;
            RwInt32 d = 0;
            RwInt32 e = 0;

            for (b = 0; b < 8; b++)
            {
                if (unk_0C[a][b].unk_08.get_unk_00())
                {
                    // A compiled-out check (docs/toolchain.md).
                    if (!unk_08)
                    {
                    }
                    c++;
                    d += unk_0C[a][b].unk_08.get_unk_00() >> 1;
                    e += unk_0C[a][b].unk_04.get_unk_00() - unk_0C[a][b].unk_00.get_unk_00();
                }
            }
            unk_61C[a] = 0;
            unk_65C[a] = 0;
            if (c)
            {
                unk_61C[a] = type_1CCA10(d / c);
                unk_65C[a] = e / c;
            }
        }
    }
}

// match: ?sub_1D5010@cTimeKeeper@@QAEHHHHPAUtype_1F8560@@H@Z @ 0x001D5010
RwInt32 cTimeKeeper::sub_1D5010(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, type_1F8560 *arg_C, RwInt32 arg_10)
{
    type_1D7560 var_C;
    RwUInt32 bp_4;
    RwInt32 var_10;

    if (arg_0 != 7)
        return 0;
    if (!var_C.sub_1D7650(arg_C, arg_10))
    {
        if (CODFH_DEBUG_LOGS)
            off_42CD14("Warning: error in unpack of ping packet!\n");
        return 0;
    }
    if (!var_C.unk_04.unk_00)
    {
        var_C.unk_04 = sub_1CCA10();
        var_C.sub_1D7560(unk_00, type_1DDE20_mask(1 << arg_8), &var_10);
        return 1;
    }
    for (bp_4 = 0; bp_4 < 8; bp_4++)
    {
        if (var_C.unk_00 == unk_0C[arg_8][bp_4].unk_00)
        {
            unk_0C[arg_8][bp_4].unk_04 = var_C.unk_04;
            unk_0C[arg_8][bp_4].unk_00 = var_C.unk_00;
            unk_0C[arg_8][bp_4].unk_08 = sub_1CCA10().since(var_C.unk_00);
            return 1;
        }
    }
    if (CODFH_DEBUG_LOGS)
        off_42CD14("KNET: cTimeKeeper() - Packet sent back to us, which we don't remember sending... could "
                   "just be big time lapse!\n");
    return 1;
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??1cTimeKeeper@@QAE@XZ (folded into 0x1E41C0)
cTimeKeeper::~cTimeKeeper()
{
}

// Empty and out of line (folded by /OPT:ICF into the shared pDtor, 0x1E41C0).
void cTimeKeeper::pDtor()
{
}
