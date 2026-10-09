// The network game's vote (type_4F8348, unk_4F8348; game/gameloop.h): its
// reset and step, a vote called here or by another player, the votes
// given, its end on the host and its result on a client, with their
// console messages. The functions are named by their traces ("VOTE
// localVoteCall" and so on); the original file name is not in the image,
// so it is named for its start address.

#include <stdio.h>
#include <string.h>
#include "rw/ostypes.h"
#include "game/gameloop.h"
#include "game/netmsg.h"
#include "game/mpgame.h"
#include "game/data.h"
#include "game/functions.h"
#include "game/loc.h"
#include "types/type_DC400.h"
#include "types/type_1DDE20_mask.h"

// Its data definitions (PLAN M5), in the image's address order.
#ifndef CODFH_SP // MP only: unreferenced constants single player does not emit (not in default.xbe; /O2 keeps them only while they are external)
// 0x003E3494
extern const RwReal flt_3E3494 = 0.01f;
// 0x003E3498
extern const RwReal flt_3E3498 = 0.01f;
// 0x003E349C
extern const RwReal flt_3E349C = 16.666666f;
#endif
// End of its data definitions.


// The debug print (compiled out in these traces).
extern void (*off_42CD14)(const RwChar *arg_0, ...);

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3E3494@@3MB @ 0x003E3494
// match: ?flt_3E3498@@3MB @ 0x003E3498
// match: ?flt_3E349C@@3MB @ 0x003E349C
// match: ??_C@_0CN@JFMIKEJH@VOTE?5update?5?$CIserver?5only?$CJ?3?5all?5v@ @ 0x003E34A0
// match: ??_C@_0DF@GFAIKEDC@VOTE?5update?5?$CIserver?5only?$CJ?3?5vote?5@ @ 0x003E34D0
// match: ??_C@_0DF@NNCBACBF@VOTE?5localVoteCall?5?$CIserver?$CJ?5?9?5se@ @ 0x003E3508
// match: ??_C@_0BN@DIIDCJDJ@VOTE?5localVoteCall?5?$CIclient?$CJ?6?$AA@ @ 0x003E3540
// match: ??_C@_0DG@KNECCEBK@VOTE?5remoteVoteCall?5?$CIserver?$CJ?5?9?5s@ @ 0x003E3560
// match: ??_C@_0CJ@BHMENGJ@VOTE?5remoteVoteCall?5?$CIclient?$CJ?5?5id@ @ 0x003E3598
// match: ??_C@_0M@JPCJNIMF@Vote?5called?$AA@ @ 0x003E35C4
// match: ??_C@_0DG@DNJFNHFK@VOTE?5localVoteRespond?5?$CIserver?$CJ?5?9@ @ 0x003E35D0
// match: ??_C@_0CL@MFIAHEJK@VOTE?5localVoteRespond?5?$CIclient?$CJ?5?9@ @ 0x003E3608
// match: ??_C@_0DK@KHECCCGP@VOTE?5localVoteRespond?5?5?9?5?$CK?$CK?$CK?$CK?5CA@ @ 0x003E3634
// match: ??_C@_0DI@KDIODDNL@VOTE?5localVoteRespond?5?5?9?5?$CK?$CK?$CK?$CK?5CA@ @ 0x003E3670
// match: ??_C@_0DM@JDLDOKCL@VOTE?5remoteVoteRespond?5?$CIserver?5o@ @ 0x003E36A8
// match: ??_C@_0DH@GMANMMJ@VOTE?5localVoteEnd?5?$CIserver?5only?$CJ?5@ @ 0x003E36E4
// match: ??_C@_08LCBDGEBH@?$CFs?$CFd?$CFs?$CFd?$AA@ @ 0x003E371C
// match: ??_C@_0L@MCAFGMOO@?5against?3?5?$AA@ @ 0x003E3728
// match: ??_C@_0BI@OJKNKMGL@Voting?5complete?5?9?5for?3?5?$AA@ @ 0x003E3734
// match: ??_C@_0DI@IOBLHIKL@VOTE?5remoteVoteEnd?5?$CIclient?5only?$CJ@ @ 0x003E374C
// match: ??_C@_0BA@IFGAKNEA@Voting?5complete?$AA@ @ 0x003E3784
// match: __ehhandler$?sub_1C32B0@type_4F8348@@QAEXHH@Z>1>8 @ 0x0041F3E0
// match: __ehhandler$?sub_1C32B0@type_4F8348@@QAEXHH@Z>1 @ 0x0041F3E8
// match: __ehhandler$?sub_1C3520@type_4F8348@@QAEXHIII@Z>1>8 @ 0x0041F404
// match: __ehhandler$?sub_1C3520@type_4F8348@@QAEXHIII@Z>1 @ 0x0041F40C
// match: __ehhandler$?sub_1C3740@type_4F8348@@SAXXZ>1>8 @ 0x0041F428
// match: __ehhandler$?sub_1C3740@type_4F8348@@SAXXZ>1 @ 0x0041F430
// match: __ehhandler$?sub_1C3A40@type_4F8348@@SAXII@Z>1>8 @ 0x0041F44C
// match: __ehhandler$?sub_1C3A40@type_4F8348@@SAXII@Z>1 @ 0x0041F45C
// match: __ehhandler$?sub_1C3BA0@type_4F8348@@SAXXZ>1>8 @ 0x0041F478
// match: __ehhandler$?sub_1C3BA0@type_4F8348@@SAXXZ>1 @ 0x0041F480

// match: ?sub_1C3120@type_4F8348@@QAEXXZ @ 0x001C3120

void type_4F8348::sub_1C3120()
{
    unk_00 = -1;
    unk_04 = 0;
    unk_0C = 0;
    unk_08 = 0;
    unk_10 = 0;
    unk_14 = 0;
    unk_18 = 0;
    unk_1C.sub_1CB790();
    unk_38 = 1;
    unk_3C = -1;
    unk_40 = 0;
    unk_44 = 0;
    unk_48 = 0;
    unk_4C.sub_1CB790();
    unk_68 = 0;
}

// On the host the countdown runs, and the vote ends when it runs out or
// every vote is in; a passed vote's time runs down.
// match: ?sub_1C31D0@type_4F8348@@QAEXM@Z @ 0x001C31D0
void type_4F8348::sub_1C31D0(RwReal arg_0)
{
    RwReal var_4;

    if (unk_4F61F8.unk_104)
        return;
    var_4 = arg_0 / 60.0f;
    if (unk_00 != -1 && unk_0C > 0.0f)
    {
        unk_0C -= var_4;
        if (unk_0C <= 0.0f)
        {
            if (CODFH_DEBUG_LOGS)
                off_42CD14("VOTE update (server only): vote countdown has ended\n");
            sub_1C3970();
        }
        else if (unk_10 + unk_14 >= unk_18)
        {
            if (CODFH_DEBUG_LOGS)
                off_42CD14("VOTE update (server only): all votes are in\n");
            sub_1C3970();
        }
    }
    if (unk_68 > 0.0f)
        unk_68 -= var_4;
}

// match: ?sub_1C32B0@type_4F8348@@QAEXHH@Z @ 0x001C32B0
// match: __ehhandler$?sub_1C32B0@type_4F8348@@QAEXHH@Z-0x8 @ 0x00303090
// match: __ehhandler$?sub_1C32B0@type_4F8348@@QAEXHH@Z @ 0x00303098
void type_4F8348::sub_1C32B0(RwInt32 arg_0, RwInt32 arg_4)
{
    if (unk_4F61F8.unk_104)
    {
        if (CODFH_DEBUG_LOGS)
            off_42CD14("VOTE localVoteCall (client)\n");
        type_3E0FE4 var_24;
        var_24.unk_04 = arg_0;
        var_24.unk_08 = arg_4;
        var_24.unk_10 = unk_4F7EB8.sub_1AEC70();
        type_1DDE20_mask m_10;
        m_10.mark(0);
        type_4F8058::get()->sub_1DDE20(&var_24, m_10);
        unk_38 = 1;
    }
    else if (unk_00 == -1)
    {
        if (CODFH_DEBUG_LOGS)
            off_42CD14("VOTE localVoteCall (server) - sending out vote call\n");
        unk_00 = arg_0;
        unk_04 = arg_4;
        unk_10 = 1;
        unk_14 = 0;
        unk_38 = 1;
        unk_18 = unk_4F7EB8.sub_1ACA70();
        unk_1C = sub_1CB720(dword_4F28F0->unk_183);
        unk_0C = 60.0f;
        type_3E0FE4 var_38;
        var_38.unk_04 = arg_0;
        var_38.unk_08 = arg_4;
        var_38.unk_0C = unk_08;
        var_38.unk_10 = 0;
        type_4F8058::get()->sub_1DDE20(&var_38, type_4F8054::get()->get_unk_B0_checked()->others_checked());
    }
}

// match: ?sub_1C3520@type_4F8348@@QAEXHIII@Z @ 0x001C3520
// match: __ehhandler$?sub_1C3520@type_4F8348@@QAEXHIII@Z-0x8 @ 0x003030B0
// match: __ehhandler$?sub_1C3520@type_4F8348@@QAEXHIII@Z @ 0x003030B8
void type_4F8348::sub_1C3520(RwInt32 arg_0, RwUInt32 arg_4, RwUInt32 arg_8, RwUInt32 arg_C)
{
    if (unk_4F61F8.unk_104)
    {
        if (CODFH_DEBUG_LOGS)
            off_42CD14("VOTE remoteVoteCall (client)  idx %d %d\n", arg_8, unk_08);
        if (arg_8 >= unk_08)
        {
            unk_00 = arg_0;
            unk_04 = arg_4;
            unk_08 = arg_8;
            unk_38 = arg_C == unk_4F7EB8.sub_1AEC70();
            sub_1C3740();
        }
    }
    else if (unk_00 == -1)
    {
        if (CODFH_DEBUG_LOGS)
            off_42CD14("VOTE remoteVoteCall (server) - sending out vote call\n");
        unk_00 = arg_0;
        unk_04 = arg_4;
        unk_10 = 1;
        unk_14 = 0;
        unk_38 = 0;
        unk_18 = unk_4F7EB8.sub_1ACA70();
        unk_1C = sub_1CB720(type_4F8054::get()->get_unk_B0()->unk_90[arg_C].unk_00);
        unk_0C = 60.0f;
        type_3E0FE4 var_20;
        var_20.unk_04 = arg_0;
        var_20.unk_08 = arg_4;
        var_20.unk_0C = unk_08;
        var_20.unk_10 = arg_C;
        type_4F8058::get()->sub_1DDE20(&var_20, type_4F8054::get()->get_unk_B0_checked()->others_checked());
        sub_1C3740();
    }
}

// match: ?sub_1C3740@type_4F8348@@SAXXZ @ 0x001C3740
// match: __ehhandler$?sub_1C3740@type_4F8348@@SAXXZ-0x8 @ 0x003030D0
// match: __ehhandler$?sub_1C3740@type_4F8348@@SAXXZ @ 0x003030D8
void type_4F8348::sub_1C3740()
{
    RwChar var_6C[0x40];
    type_1A5EA0 var_2C("Vote called", 0);

    strcpy(var_6C, var_2C.c_str());
    sub_EACA0(var_6C, 1, 0);
}

// match: ?sub_1C37E0@type_4F8348@@QAEXH@Z @ 0x001C37E0
void type_4F8348::sub_1C37E0(RwInt32 arg_0)
{
    if (unk_38)
    {
        if (CODFH_DEBUG_LOGS)
            off_42CD14("VOTE localVoteRespond  - **** CANT VOTE more than once\n");
        return;
    }
    if (unk_00 == -1)
    {
        if (CODFH_DEBUG_LOGS)
            off_42CD14("VOTE localVoteRespond  - **** CANT VOTE: no current vote\n");
        return;
    }
    if (unk_4F61F8.unk_104)
    {
        type_3E0FFC var_10;
        var_10.unk_04 = arg_0;
        var_10.unk_08 = unk_08;
        type_1DDE20_mask var_4;
        var_4.put(0);
        type_4F8058::get()->sub_1DDE20(&var_10, var_4);
        if (CODFH_DEBUG_LOGS)
            off_42CD14("VOTE localVoteRespond (client) - agree:%d\n", arg_0);
    }
    else
    {
        if (arg_0)
            unk_10++;
        else
            unk_14++;
        if (CODFH_DEBUG_LOGS)
            off_42CD14("VOTE localVoteRespond (server) - for: %d against: %d\n", unk_10, unk_14);
    }
    unk_38 = 1;
}

// match: ?sub_1C3900@type_4F8348@@QAEXII@Z @ 0x001C3900
void type_4F8348::sub_1C3900(RwUInt32 arg_0, RwUInt32 arg_4)
{
    // A compiled-out check (docs/toolchain.md).
    if (!unk_08)
    {
    }
    if (unk_00 != -1 && unk_08 == arg_4)
    {
        if (arg_0)
            unk_10++;
        else
            unk_14++;
        if (CODFH_DEBUG_LOGS)
            off_42CD14("VOTE remoteVoteRespond (server only) - for: %d against: %d\n", unk_10, unk_14);
    }
}

// match: ?sub_1C3970@type_4F8348@@QAEXXZ @ 0x001C3970
void type_4F8348::sub_1C3970()
{
    // A compiled-out check (docs/toolchain.md).
    if (!unk_08)
    {
    }
    if (CODFH_DEBUG_LOGS)
        off_42CD14("VOTE localVoteEnd (server only) - for: %d against: %d\n", unk_10, unk_14);
    type_3E1014 var_10;
    var_10.unk_04 = unk_10;
    var_10.unk_08 = unk_14;
    var_10.unk_0C = unk_08;
    type_4F8058::get()->sub_1DDE20(&var_10, type_4F8054::get()->get_unk_B0()->sub_1A8050());
    sub_1C3A40(unk_10, unk_14);
    sub_1C3C40();
    if (var_10.unk_04 > var_10.unk_08)
        unk_68 = 60.0f;
    else
        unk_68 = 0;
}

// match: ?sub_1C3A40@type_4F8348@@SAXII@Z @ 0x001C3A40
// match: __ehhandler$?sub_1C3A40@type_4F8348@@SAXII@Z-0x10 @ 0x003030F0
// match: __ehhandler$?sub_1C3A40@type_4F8348@@SAXII@Z @ 0x00303100
void type_4F8348::sub_1C3A40(RwUInt32 arg_0, RwUInt32 arg_4)
{
    type_1A5EA0 var_2C("Voting complete - for: ", 0);
    type_1A5EA0 bp_48(" against: ", 0);
    {
        RwChar var_CC[0x80];

        sprintf(var_CC, "%s%d%s%d", var_2C.c_str(), arg_0, bp_48.c_str(), arg_4);
        sub_EACA0(var_CC, 1, 0);
    }
}

// match: ?sub_1C3B40@type_4F8348@@QAEXIII@Z @ 0x001C3B40
void type_4F8348::sub_1C3B40(RwUInt32 arg_0, RwUInt32 arg_4, RwUInt32 arg_8)
{
    // A compiled-out check (docs/toolchain.md).
    if (!unk_08)
    {
    }
    if (CODFH_DEBUG_LOGS)
        off_42CD14("VOTE remoteVoteEnd (client only) - for: %d against: %d\n", arg_0, arg_4);
    if (arg_8 >= unk_08)
    {
        unk_10 = arg_0;
        unk_14 = arg_4;
        sub_1C3BA0();
        sub_1C3C40();
    }
}

// match: ?sub_1C3BA0@type_4F8348@@SAXXZ @ 0x001C3BA0
void type_4F8348::sub_1C3BA0()
{
    RwChar var_6C[0x40];
    type_1A5EA0 var_2C("Voting complete", 0);

    strcpy(var_6C, var_2C.c_str());
    sub_EACA0(var_6C, 1, 0);
}

// match: ?sub_1C3C40@type_4F8348@@QAEXXZ @ 0x001C3C40
void type_4F8348::sub_1C3C40()
{
    unk_3C = unk_00;
    unk_40 = unk_04;
    unk_44 = unk_10;
    unk_48 = unk_14;
    unk_4C = unk_1C;
    unk_00 = -1;
    unk_08++;
}

// match: ?sub_1C3CC0@type_4F8348@@QAEHXZ @ 0x001C3CC0
RwInt32 type_4F8348::sub_1C3CC0()
{
    if (unk_4F61F8.unk_104)
        return 0;
    return unk_68 > 0.0f ? 1 : 0;
}

// match: ?sub_1C3D00@type_4F8348@@QAEXXZ @ 0x001C3D00
void type_4F8348::sub_1C3D00()
{
    // A compiled-out check (docs/toolchain.md).
    if (!unk_08)
    {
    }
    unk_68 = 0;
}
