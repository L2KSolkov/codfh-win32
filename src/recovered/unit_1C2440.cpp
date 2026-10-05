// The players' teams (type_4F8288, dword_4F8288; game/netstate.h): the
// team a joining player gets, the count in a team, the reset, a player's
// team taken (with its console message), its state and leave, and the
// table written to and read from the network. Its original file name is
// not in the image, so it is named for its start address.

#include "rw/ostypes.h"
#include "game/netstate.h"
#include "game/netmsg.h"
#include "game/gameloop.h"
#include "game/data.h"
#include "game/functions.h"
#include "types/type_DC400.h"
#include "types/type_1DDE20_mask.h"
#include "game/loc.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003E342C
extern const RwReal flt_3E342C = 0.01f;
// 0x003E3430
extern const RwReal flt_3E3430 = 0.01f;
// 0x003E3434
extern const RwReal flt_3E3434 = 16.666666f;
// End of its data definitions.


// The team for a new player: red (4) when blue has more players in the
// game, else blue (2).
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3E342C@@3MB @ 0x003E342C
// match: ?flt_3E3430@@3MB @ 0x003E3430
// match: ?flt_3E3434@@3MB @ 0x003E3434
// match: ??_C@_0BA@LPCAJFKM@MW_GEN_JOINBLUE?$AA@ @ 0x003E3438
// match: ??_C@_0P@PKFDEACM@MW_GEN_JOINRED?$AA@ @ 0x003E3448
// match: ??_C@_0O@PNLOJPFN@MW_GEN_JOINDM?$AA@ @ 0x003E3458
// match: __ehhandler$?sub_1C2600@type_4F8288@@QAEXHH@Z>1>8 @ 0x0041F320
// match: __ehhandler$?sub_1C2600@type_4F8288@@QAEXHH@Z>1 @ 0x0041F338

// match: ?sub_1C2440@type_4F8288@@QAEHXZ @ 0x001C2440

// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_4F8288::sub_1C2440()
{
    type_1DDE20_mask local_C;
    RwInt32 l4 = 0;
    RwInt32 var_10 = 0;
    RwUInt32 var_8;

    local_C = type_4F8054::get()->get_unk_B0()->get_unk_0C();
    for (var_8 = 0; var_8 < 16; var_8++)
    {
        // A compiled-out check (docs/toolchain.md).
        if (!unk_00[0].unk_00)
        {
        }
        if (local_C.test(var_8))
        {
            if (unk_00[var_8].unk_00 == 4)
                l4++;
            else if (unk_00[var_8].unk_00 == 2)
                var_10++;
        }
    }
    if (var_10 > l4)
        return 4;
    return 2;
}

// match: ?sub_1C2500@type_4F8288@@QAEHH@Z @ 0x001C2500
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_4F8288::sub_1C2500(RwInt32 arg_0)
{
    type_1DDE20_mask local_C;
    RwInt32 l4 = 0;
    RwUInt32 var_8;

    local_C = type_4F8054::get()->get_unk_B0()->get_unk_0C();
    for (var_8 = 0; var_8 < 16; var_8++)
    {
        // A compiled-out check (docs/toolchain.md).
        if (!unk_00[0].unk_00)
        {
        }
        if (local_C.test(var_8) && unk_00[var_8].unk_08 && unk_00[var_8].unk_00 == arg_0)
            l4++;
    }
    return l4;
}

// match: ?sub_1C25A0@type_4F8288@@QAEXXZ @ 0x001C25A0
void type_4F8288::sub_1C25A0()
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 16; var_4++)
    {
        unk_00[var_4].unk_00 = 1;
        unk_00[var_4].unk_04 = 1;
        unk_00[var_4].unk_08 = 0;
    }
}

// match: ?sub_1C2600@type_4F8288@@QAEXHH@Z @ 0x001C2600
// match: __ehhandler$?sub_1C2600@type_4F8288@@QAEXHH@Z-0x21 @ 0x00302FC0
// match: __ehhandler$?sub_1C2600@type_4F8288@@QAEXHH@Z @ 0x00302FE1
// Player arg_0 takes the team arg_4: unless it has it, the console says so
// ("MW_GEN_JOINDM" in deathmatch, else "MW_GEN_JOINRED" or "MW_GEN_JOINBLUE",
// with its name).
void type_4F8288::sub_1C2600(RwInt32 arg_0, RwInt32 arg_4)
{
    RwChar var_114[0x100];

    // Two compiled-out checks (docs/toolchain.md).
    if (!unk_00[0].unk_00)
    {
    }
    if (!unk_00[0].unk_00)
    {
    }
    if (arg_4 != unk_00[arg_0].unk_00)
    {
        if (dword_4FB9E0.get_unk_08() == 1)
            sub_1CB000(var_114, sub_E3970("MW_GEN_JOINDM", 1).c_str(),
                       type_4F8054::get()->get_unk_B0()->unk_90[arg_0].unk_00);
        else if (arg_4 == 4)
            sub_1CB000(var_114, sub_E3970("MW_GEN_JOINRED", 1).c_str(),
                       type_4F8054::get()->get_unk_B0()->unk_90[arg_0].unk_00);
        else
            sub_1CB000(var_114, sub_E3970("MW_GEN_JOINBLUE", 1).c_str(),
                       type_4F8054::get()->get_unk_B0()->unk_90[arg_0].unk_00);
        sub_EACA0(var_114, 0, 0);
    }
    set_team(this, arg_0, arg_4);
}

// match: ?sub_1C28F0@type_4F8288@@QAEXHIH@Z @ 0x001C28F0
void type_4F8288::sub_1C28F0(RwInt32 arg_0, RwUInt32 arg_4, RwInt32 arg_8)
{
    if (!arg_8)
    {
        // A compiled-out check (docs/toolchain.md).
        if (!unk_00[0].unk_00)
        {
        }
        sub_1C2600(arg_0, arg_4);
    }
    unk_00[arg_0].unk_04 = arg_8;
    unk_00[arg_0].unk_08 = 1;
}

// match: ?sub_1C2940@type_4F8288@@QAEXH@Z @ 0x001C2940
void type_4F8288::sub_1C2940(RwInt32 arg_0)
{
    unk_00[arg_0].unk_00 = 1;
    unk_00[arg_0].unk_08 = 0;
}

// match: ?sub_1C2970@type_4F8288@@QAEXPAUtype_1F8560@@@Z @ 0x001C2970
void type_4F8288::sub_1C2970(type_1F8560 *arg_0)
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 16; var_4++)
    {
        arg_0->sub_1F8860(unk_00[var_4].unk_00, 3);
        arg_0->sub_1F8520(unk_00[var_4].unk_04);
    }
}

// Reads the table: each other player's team and state (the team kept once
// taken here, unless it says none); a player with no state yet is asked to
// respawn.
// match: ?sub_1C29D0@type_4F8288@@QAEXPAUtype_1F8560@@@Z @ 0x001C29D0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_4F8288::sub_1C29D0(type_1F8560 *arg_0)
{
    RwUInt32 var_C;
    RwUInt32 bp_8;
    RwUInt32 bp_4;

    for (bp_4 = 0; bp_4 < 16; bp_4++)
    {
        bp_8 = arg_0->sub_1F8810(3);
        var_C = arg_0->sub_1F8560();
        if (bp_4 != unk_4F7EB8.sub_1AEC70())
        {
            if (bp_8 != 1 && !unk_00[bp_4].unk_08)
            {
                unk_00[bp_4].unk_00 = bp_8;
                unk_00[bp_4].unk_04 = var_C;
            }
            if (!unk_00[bp_4].unk_04)
                unk_4F7EB8.sub_1AED80(bp_4, unk_00[bp_4].unk_00, -1);
        }
    }
}

// match: ?sub_1C2A90@type_4F8288@@QAEHH@Z @ 0x001C2A90
RwInt32 type_4F8288::sub_1C2A90(RwInt32 arg_0)
{
    // A compiled-out check (docs/toolchain.md).
    if (!unk_00[0].unk_00)
    {
    }
    return unk_00[arg_0].unk_00;
}
