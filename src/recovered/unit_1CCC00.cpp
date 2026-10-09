// The network game's players (types/type_DC400.h, type_4F8054_B0): their
// reset, and joining a server, peer by peer.

#include <xtl.h>
#include <string.h>

#include "types/type_DC400.h"
#include "game/data.h"
#include "game/gameloop.h"
#include "game/parsedfile.h"

// Its data definitions (PLAN M5), in the image's address order.
#ifndef CODFH_SP // MP only: unreferenced constants single player does not emit (not in default.xbe; /O2 keeps them only while they are external)
// 0x003E403C
extern const RwReal flt_3E403C = 0.01f;
// 0x003E4040
extern const RwReal flt_3E4040 = 0.01f;
// 0x003E4044
extern const RwReal flt_3E4044 = 16.666666f;
#endif
// 0x004FEC70
RwInt32 dword_4FEC70;
// End of its data definitions.


// A compiled-out check: no code, but the registers after it move on by the
// loads its condition would make (docs/toolchain.md). The conditions are not
// known; they are chosen for their loads.
#define PLAYERS_CHECK(e) { if (!(e)) { } }

// The debug print through a pointer (its target is empty in this build).
extern void (*off_42CD14)(const RwChar *arg_0, ...);
extern RwInt32 dword_4FEC70;

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3E403C@@3MB @ 0x003E403C
// match: ?flt_3E4040@@3MB @ 0x003E4040
// match: ?flt_3E4044@@3MB @ 0x003E4044
// match: ??_C@_0CH@MCDFMHPH@Swapping?5to?5not?9connected?5client@ @ 0x003E4048
// match: ??_C@_0CN@JPGMIKCA@Failed?5to?5connect?5to?5player?5?$CFd?0?5@ @ 0x003E4070
// match: ??_C@_0EG@CIEKEJDK@All?5connections?5successful?0?5proc@ @ 0x003E40A0
// match: ??_C@_0CL@FNFNAEIH@Which?5would?5explain?5why?5the?5NATN@ @ 0x003E40E8
// match: ??_C@_0EI@CNLKKAF@Now?5waiting?5briefly?5for?5any?5play@ @ 0x003E4118
// match: ??_C@_0CG@MNFFABCF@Connection?5attempted?5to?5all?5peer@ @ 0x003E4160
// match: ??_C@_0CB@FMKPMHKN@Now?5waiting?5for?5JoinPeerDetails?6@ @ 0x003E4188
// match: ??_C@_0CP@FNLCGLJD@Connecting?5?9?5sent?5joinPlayerDeta@ @ 0x003E41AC
// match: ??_C@_0CF@KHMKIEAH@Connecting?5?9?5sent?5joinPlayerDeta@ @ 0x003E41DC
// match: ??_C@_0CM@ECKJKDHA@cNetGameSessionManagement?3?5Closi@ @ 0x003E4204
// match: ??_C@_0CH@GOLBHOAA@Kicking?5player?5?$CFd?5?9?5?$CFs?5due?5to?5ti@ @ 0x003E4230
// match: ??_C@_0DH@KODGFNLG@handlePossibleDisconnections?3?3?5W@ @ 0x003E4258
// match: ??_C@_0CM@FENHKMF@Sent?5playerKickNotification?5?9?5pl@ @ 0x003E4290
// match: ??_C@_0DH@JOJEHGLJ@JOIN?5FAILURE?5?$CIDUE?5TO?5TIMEOUT?$CJ?4?4?5@ @ 0x003E42BC
// match: ??_C@_0CO@KMCOBEGL@PLAYER?5?$CFd?3?5?$CFs?5REMOVED?5?$CICONNECT?5F@ @ 0x003E42F4
// match: ??_C@_0CP@PEIAFAHD@JOIN?5FAILURE?5?$CIDUE?5TO?5PEER?5CONNEC@ @ 0x003E4324
// match: ??_C@_0DO@CELBNABC@Player?5?$CFd?5failed?5to?5connect?5to?5p@ @ 0x003E4354
// match: ??_C@_0BI@OGINFOJP@Sending?5joinDone?5to?5?$CFd?6?$AA@ @ 0x003E4394
// match: ??_C@_0EC@CAOPBMLD@Connecting?5?9?5got?5confirmation?5th@ @ 0x003E43B0
// match: ??_C@_0EP@KAKAPHI@Connecting?5?9?5Waiting?5for?5player?5@ @ 0x003E43F8
// match: ??_C@_03EBJOKFHF@?5?$CFd?$AA@ @ 0x003E4448
// match: ??_C@_0EN@IPPCNGAO@Failed?5waiting?5for?5peer?5connecti@ @ 0x003E4450
// match: ??_C@_0EN@BBHKLCAK@Connecting?5?9?5got?5confirmation?5th@ @ 0x003E44A0
// match: ??_C@_0DE@NEBCFLMH@Connecting?5?9?5Waiting?5peer?5connec@ @ 0x003E44F0
// match: ??_C@_0CP@IBFPJEEJ@Sending?5addPlayer?$CI?$CJ?5to?5following@ @ 0x003E4524
// match: ??_C@_0CO@PHHNMBH@Connecting?5?9?5sent?5joinPeerDetail@ @ 0x003E4554
// match: ??_C@_0DI@DEOCPELG@Connecting?5?9?5sent?5joinPeerDetail@ @ 0x003E4584
// match: ??_C@_0CO@DNKMFFP@Connecting?5?9?5got?5joinPlayer?5?9?5pl@ @ 0x003E45BC
// match: ??_C@_0CF@PNNEBENL@Connecting?5?9?5Waiting?5player?5deta@ @ 0x003E45EC
// match: ??_C@_0CH@IGAMOLFE@Connecting?5?9?5send?5joinBegin?5?9?5go@ @ 0x003E4614
// match: ??_C@_0BN@IIMHLLMI@Connecting?5?9?5sent?5joinBegin?6?$AA@ @ 0x003E463C
// match: ??_C@_0DL@IOKADHPL@KNET?5SESSION?3?5join?5game?5stage?50?0@ @ 0x003E465C
// match: ??_C@_0CI@GNPOHGJL@eNetGameEP_joinPlayerDetails?5?3?5n@ @ 0x003E4698
// match: ??_C@_0CG@FMOOLODJ@Current?5mServerConnectionStage?5?$DN@ @ 0x003E46C0
// match: ??_C@_0DD@GHADCBFB@eNetGameEP_joinPlayerDetails?5?3?5o@ @ 0x003E46E8
// match: ??_C@_0DP@IHNKKNIE@eNetGameEP_peerConnectionComplet@ @ 0x003E471C
// match: ??_C@_0FE@NFFMFLNM@eNetGameEP_joinPeerDetails?5?$CIinde@ @ 0x003E4760
// match: ??_C@_0DD@POFFLNDN@eNetGameEP_joinPeerDetails?0?5conn@ @ 0x003E47B4
// match: ??_C@_0CG@LILLOGBL@eNetGameEp_joinDone?5?9?5server?5nam@ @ 0x003E47E8
// match: ??_C@_0DG@PDIBLBKH@RECEIVED?3?5eNetGameEp_joinBeginPl@ @ 0x003E4810
// match: ??_C@_0CC@OCACMOIK@eNetGameEp_joinBegin?5?$CIindex?3?5?$CFd?$CJ@ @ 0x003E4848
// match: ??_C@_0M@MOKHBJAB@NATNeg?5with?$AA@ @ 0x003E486C
// match: ??_C@_0EB@FAOIBBPC@Removing?5player?5being?5kicked?5fro@ @ 0x003E4878
// match: ??_C@_0P@IHLGBDGM@to?5NATNeg?5with?$AA@ @ 0x003E48BC
// match: ??_C@_0DO@IGKEIBBG@Removing?5player?5being?5kicked?5fro@ @ 0x003E48CC
// match: ??_C@_0BH@CAPELIFL@to?5attempt?5NATNeg?5with?$AA@ @ 0x003E490C
// match: ??_C@_0CE@HBPHCOMN@Kicking?5player?5?$CFd?5at?5host?8s?5requ@ @ 0x003E4924
// match: ??_C@_0CK@DPIAOHNO@new?5client?5has?5NATNeg?8d?5successf@ @ 0x003E4948
// match: ??_C@_0DC@INDCNIFP@new?5client?5has?5failed?5to?5NATNeg?5@ @ 0x003E4974
// match: ??_C@_0DG@MHENMJFO@Removing?5player?5being?5kicked?5fro@ @ 0x003E49A8
// match: ??_C@_0EA@NFGCKAMO@for?5confirmation?5that?5new?5client@ @ 0x003E49E0
// match: ??_C@_0DP@MJPHEIKK@Removing?5player?5being?5kicked?5fro@ @ 0x003E4A20
// match: ??_C@_0CM@JFGNKNOP@KILLING?5PLAYER?5who?5sent?5broken?5k@ @ 0x003E4A60
// match: ??_C@_0EL@KBGPAPGE@Kick?5request?5received?5for?5a?5play@ @ 0x003E4A90
// match: ??_C@_0EM@DGBHMFKP@WARNING?3?5Interesting?5kick?5reques@ @ 0x003E4AE0
// match: ??_C@_0FH@LJKKLKPO@WARNING?3?5Kick?5request?5failed?5to?5@ @ 0x003E4B30
// match: ??_C@_0CL@IOMHABHE@eNetGameEP_addPlayer?5?9?5?$CIindex?3?$CFd@ @ 0x003E4B88
// match: ??_C@_0DA@JNCNFHJJ@sendPlayerKicks?$CI?$CJ?5?3?5Tell?5server?5@ @ 0x003E4BB4
// match: ??_C@_0DL@JHPCDECJ@Kicking?5player?5?$CFd?5now?5we?8ve?5told@ @ 0x003E4BE4
// match: ??_C@_0CK@NIOBMEEJ@sendPlayerKicks?$CI?$CJ?5?3?5killing?5play@ @ 0x003E4C20
// match: ??_C@_0DE@DHNFLEFE@sendPlayerKicks?$CI?$CJ?5?3?5Telling?5clie@ @ 0x003E4C4C
// match: ??_C@_0CA@INLOHMLD@Added?5player?5?$CFd?5?9?5?$CFs?5as?5Server?6?$AA@ @ 0x003E4C80
// match: ??_C@_0DC@MHNPJCFA@cNetGameSessionManagement?3?3?5clos@ @ 0x003E4CA0
// match: ??_C@_0EE@NKMKIDJI@Connecting?5?9?5informing?5host?5that@ @ 0x003E4CD8
// match: ??_C@_0EJ@JNAIPHAP@Connecting?5?9?5informing?5host?5that@ @ 0x003E4D20

// match: ?sub_1CCC00@type_4F8054_B0@@QAEXPAUtype_4F8054@@@Z @ 0x001CCC00

void type_4F8054_B0::sub_1CCC00(type_4F8054 *arg_0)
{
    unk_00 = arg_0;
    unk_04 = 666;
    unk_08 = 0;
    unk_0C.unk_00 = 0;
    unk_310 = 0;
    unk_34 = 0;
    unk_314 = 8;
    unk_38 = 0;
    unk_30.unk_00 = 0;
    unk_48.unk_00 = 0;
    unk_4A.unk_00 = 0;
    unk_4C.unk_00 = 0;
    memset(unk_50, 0, sizeof(unk_50));
    unk_3C = 666;
    unk_40 = 0;
    unk_44 = 0;
    memset(unk_90, 0, sizeof(unk_90));
    memset(unk_2D0, 0, 4);
    unk_320 = 0;
    dword_4FEC70 = 0;
    unk_368 = type_1CCA10();
}

// match: ?sub_1CCD20@type_4F8054_B0@@QAEXXZ @ 0x001CCD20
void type_4F8054_B0::sub_1CCD20()
{
    unk_30.unk_00 = 0;
    unk_0C.unk_00 = 0;
    unk_48.unk_00 = 0;
    unk_4A.unk_00 = 0;
    unk_4C.unk_00 = 0;
}

// match: ?sub_1CCD60@type_4F8054_B0@@QAEXABUtype_1CCA10@@@Z @ 0x001CCD60
void type_4F8054_B0::sub_1CCD60(const type_1CCA10 &arg_0)
{
    RwUInt32 var_4;
    RwInt32 v8;
    RwInt32 ebp_C;

    v8 = 0;
    ebp_C = 10;
    switch (unk_310)
    {
    case 0:
        if (unk_314 != 0)
            set_unk_31C(arg_0 + 40000);
        else if (arg_0 > unk_31C)
        {
            v8 = 1;
            ebp_C = 4;
        }
        if (!unk_00->vf_018(unk_08))
            break;
        break;
    case 1:
    {
        type_1D6230 var_2C;

        if (!unk_00->vf_018(unk_08))
            return;
        if (0)
            off_42CD14("Connecting - sent joinPlayerDetails\n");
        strcpy(var_2C.unk_00, unk_00->unk_80);
        var_2C.unk_18 = unk_00->sub_1CCB40();
        unk_310 = 2;
        v8 = var_2C.sub_1D6230(unk_00, type_1DDE20_mask(1 << get_unk_08()), &unk_318) == 0;
        ebp_C = 4;
        break;
    }
    case 2:
        if (unk_314 == 1)
            set_unk_31C(arg_0 + 40000);
        else if (arg_0 > unk_31C)
        {
            v8 = 1;
            ebp_C = 4;
        }
        if (unk_00->get_unk_AC()->sub_1D17B0(unk_318).empty())
        {
            if (0)
                off_42CD14("Connecting - sent joinPlayerDetails - got ack\n");
            unk_310 = 3;
            set_unk_31C(arg_0 + 40000);
        }
        break;
    case 3:
        if (unk_314 == 2)
        {
            if (0)
                off_42CD14("Now waiting for JoinPeerDetails\n");
            set_unk_31C(arg_0 + 40000);
        }
        else if (arg_0 > unk_31C)
        {
            v8 = 1;
            ebp_C = 4;
        }
        break;
    case 4:
        if (unk_48.empty())
        {
            if (0)
                off_42CD14("Connection attempted to all peers...\n");
            memset(unk_50, 0, sizeof(unk_50));
            unk_310 = 5;
        }
        break;
    case 5:
        if (unk_314 == 4)
        {
            if (0)
                off_42CD14("Now waiting briefly for any players we failed NATNeg with to be kicked\n");
            if (0)
                off_42CD14("Which would explain why the NATNeg failed\n");
            set_unk_31C(arg_0 + 33000);
        }
        if (unk_4C.empty())
        {
            if (0)
                off_42CD14("All connections successful, proceeding to wait for join done message\n");
            unk_310 = 6;
        }
        else if (arg_0 > unk_31C)
        {
            if (0)
                off_42CD14("Failed to connect to player %d, bailing out\n", unk_4C.sub_1D4900());
            v8 = 1;
            ebp_C = 3;
        }
        break;
    case 6:
        if (unk_314 == 5)
            set_unk_31C(arg_0 + 40000);
        else if (arg_0 > unk_31C)
        {
            v8 = 1;
            ebp_C = 4;
        }
        break;
    case 7:
        handlePossibleDisconnections();
        break;
    }
    if (v8)
    {
        unk_00->setError(3, ebp_C);
        unk_310 = 8;
        if (0)
            off_42CD14("Swapping to not-connected client mode\n");
        sub_1CFC20(unk_08);
        unk_08 = 0;
        for (var_4 = 0; var_4 < 0x10; var_4++)
        {
            if (unk_50[var_4])
                unk_00->get_unk_AC()->sub_1D18E0(unk_50[var_4]);
        }
        memset(unk_50, 0, sizeof(unk_50));
        if (unk_00->get_unk_A8())
            unk_00->get_unk_A8()->vf_008();
    }
}

// match: ?sub_1CD370@type_4F8054_B0@@QAEXXZ @ 0x001CD370
void type_4F8054_B0::sub_1CD370()
{
    RwUInt32 i;

    if (unk_310 != 8)
    {
        if (0)
            off_42CD14("cNetGameSessionManagement: Closing game...\n");
        for (i = 0; i < 0x10; i++)
        {
            // A compiled-out check: the registers after it are one load on
            // (docs/toolchain.md).
            if (!unk_0C.unk_00)
            {
            }
            if (unk_0C.test(i) && i != unk_04)
            {
                unk_00->vf_04C(type_1DDE20_mask(1 << i));
                sub_1CFC20(i);
            }
        }
        if (unk_00->get_unk_A8())
            unk_00->get_unk_A8()->vf_008();
        unk_310 = 8;
    }
}

// match: ?handlePossibleDisconnections@type_4F8054_B0@@QAEXXZ @ 0x001CD450
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_4F8054_B0::handlePossibleDisconnections()
{
    type_1CCA10 locc = unk_00->get_unk_7C() - 30000;
    type_1DDE20_mask bp_4;
    RwUInt32 x8;
    RwInt32 ebp_10;

    ebp_10 = 0;
    if (unk_04 != unk_08)
    {
        // A compiled-out check: the registers after it are one load on
        // (docs/toolchain.md).
        if (!unk_0C.unk_00)
        {
        }
        if (!unk_0C.test(unk_08))
            ebp_10 = 1;
    }
    for (x8 = 0; x8 < 0x10; x8++)
    {
        if (x8 == unk_04 || !in_game(x8))
            continue;
        if (unk_00->get_unk_AC()->get_unk_480(x8) < locc)
        {
            if (get_unk_2D0(x8) > 30000)
            {
                if (unk_08 != unk_04 && get_unk_2D0(get_unk_08()) < 60000)
                    ebp_10 = 1;
                else
                {
                    // Two compiled-out checks (docs/toolchain.md): the
                    // registers after them are four loads on.
                    if (!unk_0C.unk_00)
                    {
                    }
                    if (!unk_0C.unk_00)
                    {
                    }
                    bp_4.unk_00 |= 1 << x8;
                }
            }
        }
    }
    if (bp_4.empty() && !ebp_10)
        return;
    if (unk_04 != unk_08)
    {
        // Two compiled-out checks (docs/toolchain.md): the registers after
        // them are four loads on.
        if (!unk_0C.unk_00)
        {
        }
        if (!unk_0C.unk_00)
        {
        }
        if (bp_4.test(unk_08))
            ebp_10 = 1;
    }
    if (ebp_10)
    {
        if (0)
            off_42CD14("handlePossibleDisconnections:: We've lost the server!\n");
        sub_1CD370();
        unk_00->setError(7, 6);
        return;
    }
    for (x8 = 0; x8 < 0x10; x8++)
    {
        if (bp_4.test(x8))
        {
            if (0)
                off_42CD14("Kicking player %d - %s due to timeout\n", x8, unk_90[x8].unk_00);
            sub_1CD690(x8);
        }
    }
}

// match: ?sub_1CD690@type_4F8054_B0@@QAEXH@Z @ 0x001CD690
void type_4F8054_B0::sub_1CD690(RwInt32 arg_0)
{
    unk_00->vf_04C(type_1DDE20_mask(1 << arg_0));
    sub_1CFC20(arg_0);
    sendPlayerKicks(arg_0);
}

// match: ?sub_1CD6E0@type_4F8054_B0@@QAEXH@Z @ 0x001CD6E0
void type_4F8054_B0::sub_1CD6E0(RwInt32 arg_0)
{
    type_1D7870 var_1;
    RwInt32 var_8;
    RwInt32 lv_C;

    lv_C = 0;
    var_8 = var_1.sub_1D7870(unk_00, type_1DDE20_mask(1 << arg_0), &lv_C) == 0;
    if (0)
        off_42CD14("Sent playerKickNotification - player idx %d", arg_0);
    if (!var_8)
    {
        unk_324.set(arg_0);
        unk_328[arg_0] = lv_C;
    }
    else
        sub_1CD690(arg_0);
}

// match: ?sub_1CD780@type_4F8054_B0@@QAEXABUtype_1CCA10@@@Z @ 0x001CD780
void type_4F8054_B0::sub_1CD780(const type_1CCA10 &arg_0)
{
    RwUInt32 bp_4;
    RwInt32 x8;
    RwInt32 locc;
    RwInt32 ebp_10;
    RwInt32 y14;
    type_1D6020 bp_19;
    type_1D5DC0 lcl_1a;

    x8 = 0;
    y14 = 0;
    locc = 0;
    type_1CCA10 ebp_18;
    handlePossibleDisconnections();
    if (!unk_30.empty())
    {
        ebp_18 = arg_0 - unk_368;
        if (ebp_18 > 1000)
        {
            unk_368 = arg_0;
            for (bp_4 = 0; bp_4 < 0x10; bp_4++)
            {
                // Two compiled-out checks (docs/toolchain.md): the registers
                // after them are four loads on.
                if (!unk_30.unk_00)
                {
                }
                if (!unk_30.unk_00)
                {
                }
                if (unk_30.test(bp_4))
                    bp_19.sub_1D6020(unk_00, type_1DDE20_mask(1 << bp_4), &ebp_10);
            }
        }
    }
    switch (unk_34)
    {
    case 0:
        if (unk_30.empty())
            return;
        unk_34 = 1;
        unk_2C = 0;
    case 1:
        if (!unk_00->vf_014(unk_30.sub_1D4900()))
            return;
        unk_3C = unk_30.sub_1D4900();
        if (0)
            off_42CD14("KNET SESSION: join game stage 0, player index selected %d\n", unk_3C);
        lcl_1a.unk_00 = (RwUInt8)unk_3C;
        x8 = lcl_1a.sub_1D5DC0(unk_00, type_1DDE20_mask(1 << get_unk_3C()), &unk_40) == 0;
        set_unk_44(arg_0 + 40000);
        if (0)
            off_42CD14("Connecting - sent joinBegin\n");
        unk_34 = 2;
        break;
    case 2:
        if (unk_00->get_unk_AC()->sub_1D17B0(unk_40).empty())
        {
            if (0)
                off_42CD14("Connecting - send joinBegin - got ack\n");
            set_unk_44(arg_0 + 40000);
            unk_34 = 3;
        }
        else
        {
            if (arg_0 > unk_44)
                x8 = 1;
            break;
        }
        break;
    case 3:
        if (unk_38 != 3)
        {
            if (0)
                off_42CD14("Connecting - Waiting player details\n");
        }
        if (!unk_2C)
        {
            if (arg_0 > unk_44)
                x8 = 1;
        }
        else
        {
            if (0)
                off_42CD14("Connecting - got joinPlayer - player name %s\n", unk_10);
            strcpy(unk_90[unk_3C].unk_00, unk_10);
            unk_90[unk_3C].unk_1C = unk_28;
            unk_34 = 4;
            unk_0C.add(unk_3C);
        }
        break;
    case 4:
    {
        type_1D6700 details;

        unk_48.unk_00 = 0;
        unk_4A.unk_00 = 0;
        unk_4C.unk_00 = 0;
        // VC7.1 leaks the for-scope names (docs/toolchain.md).
        for (RwInt32 count = 0, p = 0; p < 0x10U; p++)
        {
            if (p == unk_08 || p == unk_3C)
                continue;
            // Two compiled-out checks (docs/toolchain.md): the registers after
            // them are four loads on.
            if (!unk_0C.unk_00)
            {
            }
            if (!unk_0C.unk_00)
            {
            }
            if (unk_0C.test(p))
            {
                details.unk_04[count] = unk_90[p];
                details.unk_244[count] = (RwUInt8)p;
                unk_00->vf_038(p, details.unk_254[count], 0xC);
                count++;
                unk_48.add(p);
            }
        }
        details.unk_00 = count;
        x8 = details.sub_1D6700(unk_00, type_1DDE20_mask(1 << get_unk_3C()), &unk_40) == 0;
        set_unk_44(arg_0 + 40000);
        unk_34 = 5;
        if (0)
            off_42CD14("Connecting - sent joinPeerDetails for %d other players\n", count);
        break;
    }
    case 5:
        if (unk_00->get_unk_AC()->sub_1D17B0(unk_40).empty())
        {
            unk_34 = 6;
            if (0)
                off_42CD14("Connecting - sent joinPeerDetails  - got ACK\n");
        }
        if (arg_0 > unk_44)
            x8 = 1;
        break;
    case 6:
    {
        type_1D6EB0 add;

        strcpy(add.unk_01, unk_90[unk_3C].unk_00);
        add.unk_2A = unk_90[unk_3C].unk_20;
        add.unk_25[0] = unk_90[unk_3C].unk_18[0];
        add.unk_25[1] = unk_90[unk_3C].unk_18[1];
        add.unk_25[2] = unk_90[unk_3C].unk_18[2];
        add.unk_25[3] = unk_90[unk_3C].unk_18[3];
        add.unk_00 = (RwUInt8)unk_3C;
        add.unk_2C = unk_90[unk_3C].unk_1C;
        unk_00->vf_038(unk_3C, add.unk_19, 0xC);
        // A compiled-out check (docs/toolchain.md): the registers after it
        // are one load on.
        if (!unk_00)
        {
        }
        type_1DDE20_mask m = unk_0C;

        m.clear(joiner());
        m.clear(self());
        if (0)
            off_42CD14("Sending addPlayer() to following players - %s\n", m.sub_1D4990());
        if (!m.empty())
            x8 = add.sub_1D6EB0(unk_00, m, &ebp_10) == 0;
        unk_34 = 7;
        break;
    }
    case 7:
    {
        RwInt32 k;

        if (unk_38 != 7)
        {
            if (0)
                off_42CD14("Connecting - Waiting peer connection confirmations\n");
            set_unk_44(arg_0 + 40000);
        }
        if (unk_48.empty())
        {
            if (0)
                off_42CD14("Connecting - got confirmation that client attempted connection to all peers\n");
            unk_34 = 8;
        }
        if (arg_0 > unk_44)
        {
            if (0)
                off_42CD14("Failed waiting for peer connection confirmation\nClient connections failed = ");
            for (k = 0; k < 0x10; k++)
            {
                // Two compiled-out checks (docs/toolchain.md): the registers
                // after them are four loads on.
                if (!unk_48.unk_00)
                {
                }
                if (!unk_48.unk_00)
                {
                }
                if (unk_48.test(k))
                {
                    if (0)
                        off_42CD14(" %d", k);
                }
            }
            if (0)
                off_42CD14("\n");
            x8 = 1;
            y14 = 1;
        }
        break;
    }
    case 8:
        if (unk_38 != 8)
        {
            if (0)
                off_42CD14("Connecting - Waiting for player drop/kicks to explain any connection failures\n");
            set_unk_44(arg_0 + 33000);
        }
        if (unk_4C.empty())
        {
            type_1D6C60 done;

            if (0)
                off_42CD14("Connecting - got confirmation that client connected to all peers\n");
            strcpy(done.unk_00, unk_90[unk_08].unk_00);
            if (0)
                off_42CD14("Sending joinDone to %d\n", unk_3C);
            done.sub_1D6C60(unk_00, type_1DDE20_mask(1 << get_unk_3C()), &ebp_10);
            if (unk_00->get_unk_A8())
                unk_00->get_unk_A8()->vf_000(unk_3C);
            unk_00->vf_080(1, 0);
            unk_00->get_unk_B4()->sub_1D4C60(unk_3C);
            unk_34 = 0;
            unk_30.clear(unk_3C);
            unk_3C = 666;
            unk_4A.unk_00 = 0;
            unk_4C.unk_00 = 0;
            unk_48.unk_00 = 0;
        }
        else if (arg_0 > unk_44)
        {
            if (0)
                off_42CD14("Player %d failed to connect to player %d, dropping player %d\n", unk_3C,
                           unk_4C.sub_1D4900(), unk_3C);
            x8 = 1;
            y14 = 1;
            locc = 3;
        }
        break;
    }
    if (x8)
    {
        if (locc == 3)
        {
            if (0)
                off_42CD14("JOIN FAILURE (DUE TO PEER CONNECTION FAILURE)\n");
            if (0)
                off_42CD14("PLAYER %d: %s REMOVED (CONNECT FAILED TO %d)\n", unk_3C, unk_90[unk_3C].unk_00,
                           unk_4C.sub_1D4900());
        }
        else if (0)
            off_42CD14("JOIN FAILURE (DUE TO TIMEOUT).. PLAYER %d: %s REMOVED\n", unk_3C, unk_90[unk_3C].unk_00);
        if (y14)
            sub_1CD690(unk_3C);
        else
        {
            unk_00->vf_04C(type_1DDE20_mask(1 << get_unk_3C()));
            unk_0C.clear(unk_3C);
            unk_00->get_unk_AC()->sub_1D0B30(type_1DDE20_mask(1 << get_unk_3C()));
        }
        unk_34 = 0;
        unk_30.clear(unk_3C);
        unk_3C = 666;
        unk_4A.unk_00 = 0;
        unk_4C.unk_00 = 0;
        unk_48.unk_00 = 0;
    }
}

// match: ?sub_1CE650@type_4F8054_B0@@QAEHHHHPAUtype_1F8560@@H@Z @ 0x001CE650
// The players' messages: message arg_0 from peer arg_8 (arg_4 passed on),
// in the stream arg_C of arg_10 bits; 0 for a message that is not theirs.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_4F8054_B0::sub_1CE650(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, type_1F8560 *arg_C, RwInt32 arg_10)
{
    RwInt32 handle;

    switch (arg_0)
    {
    case 8:
    case 9:
        return unk_00->vf_01C(arg_0, arg_4, arg_8, (RwInt32)arg_C, arg_10);
    case 5:
    {
        type_1D6EB0 add;

        add.sub_1D7010(arg_C, arg_10);
        if (0)
            off_42CD14("eNetGameEP_addPlayer - (index:%d name %s)\n", add.unk_00, add.unk_01);
        PLAYERS_CHECK(unk_04);
        unk_90[add.unk_00].unk_18[0] = add.unk_25[0];
        unk_90[add.unk_00].unk_18[1] = add.unk_25[1];
        unk_90[add.unk_00].unk_18[2] = add.unk_25[2];
        unk_90[add.unk_00].unk_18[3] = add.unk_25[3];
        unk_90[add.unk_00].unk_20 = add.unk_2A;
        unk_90[add.unk_00].unk_1C = add.unk_2C;
        strcpy(unk_90[add.unk_00].unk_00, add.unk_01);
        unk_00->vf_034(add.unk_00, (RwInt32)add.unk_19, 12);
        unk_00->vf_02C(add.unk_00, 2);
        if (unk_00->vf_048(add.unk_00, (RwInt32)&unk_90[add.unk_00]))
        {
            PLAYERS_CHECK(unk_04);
            PLAYERS_CHECK(unk_04); PLAYERS_CHECK(unk_04); unk_0C.add(add.unk_00);
            if (unk_00->get_unk_A8())
                unk_00->get_unk_A8()->vf_000(add.unk_00);
            unk_00->vf_080(1, 0);
            unk_00->get_unk_B4()->sub_1D4C60(add.unk_00);
        }
        return 1;
    }
    case 6:
    {
        type_1D7200 a;

        if (!a.sub_1D7340(arg_C, arg_10))
        {
            if (0)
                off_42CD14("WARNING: Kick request failed to unpack - assuming platform-specific data was invalid!\n");
            PLAYERS_CHECK(unk_04);
            return 1;
        }
        RwInt32 b = 0;
        RwInt32 c = 1;

        if (strcmp(unk_90[a.unk_00].unk_00, a.unk_01) || memcmp(unk_90[a.unk_00].unk_18, a.unk_19, 4))
        {
            if (unk_0C.test(a.unk_00))
            {
                b = 1;
                if (0)
                    off_42CD14("WARNING: Interesting kick request sent.. player details do not match ours!\n");
            }
            else
            {
                c = 0;
                if (0)
                    off_42CD14("Kick request received for a player not in our connection set, ignoring it\n");
            }
        }
        if (unk_04 == unk_08)
        {
            if (c)
            {
                if (b || a.unk_00 == unk_08)
                {
                    if (0)
                        off_42CD14("KILLING PLAYER who sent broken kick request");
                    unk_00->vf_04C(type_1DDE20_mask(1 << arg_8));
                    sub_1CFC20(arg_8);
                    a.unk_00 = (RwUInt8)arg_8;
                    strcpy(a.unk_01, unk_90[a.unk_00].unk_00);
                    memcpy(a.unk_19, unk_90[a.unk_00].unk_18, 4);
                    PLAYERS_CHECK(unk_04);
                    PLAYERS_CHECK(unk_04);
                    PLAYERS_CHECK(unk_04);
                    a.sub_1D7200(unk_00, sub_1A8050(), &handle);
                }
                else
                {
                    
                    a.sub_1D7200(unk_00, sub_1A8050(), &handle);
                    PLAYERS_CHECK(unk_04);
                    if (unk_48.test(a.unk_00))
                    {
                        if (0)
                            off_42CD14("Removing player being kicked from set of clients we're waiting");
                        if (0)
                            off_42CD14("for confirmation that new client has NATNeg'd successfully with");
                        unk_48.discard(a.unk_00);
                    }
                    PLAYERS_CHECK(unk_04);
                    if (unk_4C.test(a.unk_00))
                    {
                        if (0)
                            off_42CD14("Removing player being kicked from set of clients that");
                        if (0)
                            off_42CD14("new client has failed to NATNeg successfully with");
                        unk_4C.discard(a.unk_00);
                    }
                    PLAYERS_CHECK(unk_04);
                    if (unk_4A.test(a.unk_00))
                    {
                        if (0)
                            off_42CD14("Removing player being kicked from set of clients that");
                        if (0)
                            off_42CD14("new client has NATNeg'd successfully with");
                        unk_4A.discard(a.unk_00);
                    }
                }
            }
            PLAYERS_CHECK(unk_04);
        }
        else if (unk_08 == arg_8)
        {
            if (b)
            {
                sub_1CD370();
                unk_00->setError(7, 7);
            }
            else
            {
                if (0)
                    off_42CD14("Kicking player %d at host's request", a.unk_00);
                unk_00->vf_04C(type_1DDE20_mask(1 << a.unk_00));
                sub_1CFC20(a.unk_00);
                if (unk_48.test(a.unk_00))
                {
                    if (0)
                        off_42CD14("Removing player being kicked from set of clients we're waiting");
                    if (0)
                        off_42CD14("to attempt NATNeg with");
                    unk_48.discard(a.unk_00);
                    PLAYERS_CHECK(unk_04);
                }
                if (unk_4C.test(a.unk_00))
                {
                    if (0)
                        off_42CD14("Removing player being kicked from set of clients we've failed");
                    if (0)
                        off_42CD14("to NATNeg with");
                    unk_4C.discard(a.unk_00);
                    PLAYERS_CHECK(unk_04);
                }
                if (unk_4A.test(a.unk_00))
                {
                    if (0)
                        off_42CD14("Removing player being kicked from set of clients we've completed");
                    if (0)
                        off_42CD14("NATNeg with");
                    unk_4A.discard(a.unk_00);
                }
            }
        }
        return 1;
    }
    case 10:
    {
        type_1D7760 name;

        name.sub_1D7760(arg_C, arg_10);
        if (name.unk_00 <= 16 && name.unk_00 == arg_8)
            strcpy(unk_90[arg_8].unk_00, name.unk_01);
        return 1;
    }
    case 11:
    {
        type_1D77F0 server;

        server.sub_1D77F0(arg_C, arg_10);
        if (arg_8 == unk_08)
        {
            strncpy(unk_00->unk_1C, server.unk_00, 0x18);
            unk_00->unk_1C[0x17] = 0;
        }
        return 1;
    }
    case 1:
        PLAYERS_CHECK(unk_04);
        if (unk_310 == 0)
        {
            type_1D5DC0 begin;

            begin.sub_1D5E80(arg_C, arg_10);
            unk_04 = begin.unk_00;
            unk_310 = 1;
            if (0)
                off_42CD14("eNetGameEp_joinBegin (index: %d)\n", unk_04);
            sub_1CF750(unk_04);
            dword_4FEC70 = 1;
        }
        return 1;
    case 14:
        if (unk_310 == 0)
        {
            type_1D6020 wait;

            wait.sub_1D60D0(arg_C, arg_10);
            if (0)
                off_42CD14("RECEIVED: eNetGameEp_joinBeginPleaseWait from server\n");
            unk_31C = unk_00->get_unk_7C() + type_1CCA10(40000);
        }
        return 1;
    case 4:
    {
        type_1D6C60 done;

        done.sub_1D6D20(arg_C, arg_10);
        PLAYERS_CHECK(unk_04);
        unk_310 = 7;
        if (0)
            off_42CD14("eNetGameEp_joinDone - server name %s\n", done.unk_00);
        PLAYERS_CHECK(unk_04);
        unk_0C.add(unk_08);
        strcpy(unk_90[unk_08].unk_00, done.unk_00);
        if (unk_00->get_unk_A8())
            unk_00->get_unk_A8()->vf_000(unk_08);
        unk_00->vf_080(1, 0);
        unk_00->get_unk_B4()->sub_1D4C60(unk_08);
        return 1;
    }
    case 3:
        if (0)
            off_42CD14("eNetGameEP_joinPeerDetails, connection stage = %d\n", unk_310);
        PLAYERS_CHECK(unk_04);
        if (unk_310 == 3 || unk_310 == 2)
        {
            unk_48.unk_00 = 0;
            unk_4A.unk_00 = 0;
            unk_4C.unk_00 = 0;
            type_1D6700 a;
            RwUInt32 b;

            a.sub_1D6920(arg_C, arg_10);
            for (b = 0; b < (RwUInt32)a.unk_00; b++)
            {
                RwInt32 c = a.unk_244[b];

                unk_90[c] = a.unk_04[b];
                unk_0C.admit(c);
                unk_48.include(c);
                unk_00->vf_034(c, (RwInt32)a.unk_254[b], 12);
                unk_00->vf_02C(c, 2);
                if (0)
                    off_42CD14("eNetGameEP_joinPeerDetails (index %d, name %s, ip %d.%d.%d.%d port %d - cookie %d)\n", c,
                               unk_90[c].unk_00, unk_90[c].unk_18[0], unk_90[c].unk_18[1], unk_90[c].unk_18[2],
                               unk_90[c].unk_18[3], unk_90[c].unk_20, unk_90[c].unk_1C);
                unk_00->vf_084(c, (RwInt32)&unk_90[c]);
                if (unk_00->get_unk_A8())
                    unk_00->get_unk_A8()->vf_000(c);
                unk_00->vf_080(1, 0);
                unk_00->get_unk_B4()->sub_1D4C60(c);
            }
            unk_310 = 4;
        }
        return 1;
    case 13:
        PLAYERS_CHECK(unk_04);
        if (unk_34 == 7)
        {
            type_1D6480 report;

            report.sub_1D6550(arg_C, arg_10);
            PLAYERS_CHECK(unk_04);
            PLAYERS_CHECK(unk_04);
            if (0)
                off_42CD14("eNetGameEP_peerConnectionCompleted, player = %d, success = %d\n", report.unk_00, report.unk_04);
            PLAYERS_CHECK(unk_04);
            if (unk_48.test(report.unk_00))
            {
                unk_48.clear(report.unk_00);
                if (report.unk_04)
                    unk_4A.admit(report.unk_00);
                else
                    unk_4C.add(report.unk_00);
            }
            set_unk_44(sub_1CCA10() + 40000);
        }
        return 1;
    case 2:
        if (0)
            off_42CD14("eNetGameEP_joinPlayerDetails : our playerIndex %d\n", unk_04);
        if (0)
            off_42CD14("Current mServerConnectionStage == %d\n", unk_34);
        if ((unk_34 == 3 || unk_34 == 2) && arg_8 == unk_3C)
        {
            unk_2C = 1;
            ((type_1D6230 *)unk_10)->sub_1D62F0(arg_C, arg_10);
            if (0)
                off_42CD14("eNetGameEP_joinPlayerDetails : name %s\n", unk_10);
        }
        return 1;
    case 12:
    {
        type_1D7870 ready;

        ready.sub_1D7920(arg_C, arg_10);
        if (((kujuUI::type_1C8DF0_104_00 *)&dword_4FB9E0)->sub_1E3480() == 2)
            unk_4F7EB8.sub_1AAB30();
        else
            dword_4FB9E0.sub_1B6EA0();
        return 1;
    }
    default:
        return 0;
    }
}

// match: ?sub_1CF750@type_4F8054_B0@@QAEXH@Z @ 0x001CF750
void type_4F8054_B0::sub_1CF750(RwInt32 arg_0)
{
    // A compiled-out check (docs/toolchain.md): the registers after it
    // are one load on.
    if (!unk_00)
    {
    }
    unk_0C.add(arg_0);
    strcpy(unk_90[arg_0].unk_00, unk_00->unk_80);
    unk_04 = arg_0;
    unk_08 = 0;
}

// match: ?sendPlayerKicks@type_4F8054_B0@@QAEXH@Z @ 0x001CF7C0
void type_4F8054_B0::sendPlayerKicks(RwInt32 arg_0)
{
    type_1D7200 msg;

    {
        RwInt32 var_2C;
        RwInt32 var_28;

        var_2C = !(unk_08 - unk_04);
        msg.unk_00 = (RwUInt8)arg_0;
        strcpy(msg.unk_01, unk_90[arg_0].unk_00);
        memcpy(msg.unk_19, unk_90[arg_0].unk_18, 4);
        // Compiled-out checks (docs/toolchain.md) here and below: each moves
        // the registers after it on by the loads it makes (one for a dword
        // field, two for a mask).
        if (!unk_00)
        {
        }
        if (var_2C)
        {
            type_1DDE20_mask others = unk_0C;

            others.clear(self2());
            if (!unk_0C.unk_00)
            {
            }
            others.clear(arg_0);
            if (0)
                off_42CD14("sendPlayerKicks() : Telling clients to purge %d:%s\n", arg_0, unk_90[arg_0].unk_00);
            if (!others.empty())
                msg.sub_1D7200(unk_00, others, &var_28);
            if (!unk_0C.unk_00)
            {
            }
            if (!unk_0C.unk_00)
            {
            }
            if (unk_48.test(msg.unk_00))
            {
                if (0)
                    off_42CD14("Removing player being kicked from set of clients we're waiting");
                if (0)
                    off_42CD14("for confirmation that new client has NATNeg'd successfully with");
                unk_48.clear(msg.unk_00);
            }
            if (!unk_0C.unk_00)
            {
            }
            if (unk_4C.test(msg.unk_00))
            {
                if (0)
                    off_42CD14("Removing player being kicked from set of clients that");
                if (0)
                    off_42CD14("new client has failed to NATNeg successfully with");
                unk_4C.clear(msg.unk_00);
            }
            if (!unk_0C.unk_00)
            {
            }
            if (unk_4A.test(msg.unk_00))
            {
                if (0)
                    off_42CD14("Removing player being kicked from set of clients that");
                if (0)
                    off_42CD14("new client has NATNeg'd successfully with");
                unk_4A.clear(msg.unk_00);
            }
            if (0)
                off_42CD14("sendPlayerKicks() : killing player %d:%s\n", arg_0, unk_90[arg_0].unk_00);
            if (arg_0 != unk_08)
            {
                if (0)
                    off_42CD14("Kicking player %d now we've told all clients to kick them\n", arg_0);
                unk_00->vf_04C(type_1DDE20_mask(1 << arg_0));
                sub_1CFC20(arg_0);
            }
        }
        else
        {
            if (0)
                off_42CD14("sendPlayerKicks() : Tell server to purge %d:%s\n", arg_0, unk_90[arg_0].unk_00);
            msg.sub_1D7200(unk_00, type_1DDE20_mask(1 << get_unk_08()), &var_28);
        }
    }
}

// match: ?sub_1CFAC0@type_4F8054_B0@@QAEXHPBEG@Z @ 0x001CFAC0
void type_4F8054_B0::sub_1CFAC0(RwInt32 arg_0, const RwUInt8 *arg_4, RwUInt16 arg_8)
{
    // A compiled-out check (docs/toolchain.md): the registers after it
    // are one load on.
    if (!unk_00)
    {
    }
    unk_90[arg_0].unk_00[0] = '~';
    unk_90[arg_0].unk_00[1] = 0;
    unk_90[arg_0].unk_18[0] = arg_4[0];
    unk_90[arg_0].unk_18[1] = arg_4[1];
    unk_90[arg_0].unk_18[2] = arg_4[2];
    unk_90[arg_0].unk_18[3] = arg_4[3];
    unk_90[arg_0].unk_20 = arg_8;
    unk_30.add(arg_0);
}

// match: ?sub_1CFB80@type_4F8054_B0@@QAEXXZ @ 0x001CFB80
void type_4F8054_B0::sub_1CFB80()
{
    const RwChar *name;

    unk_08 = 0;
    unk_04 = 0;
    name = unk_00->unk_80;
    strcpy(unk_90[unk_08].unk_00, name);
    unk_0C.add(unk_08);
    if (0)
        off_42CD14("Added player %d - %s as Server\n", unk_08, name);
}

// match: ?sub_1CFC20@type_4F8054_B0@@QAEXH@Z @ 0x001CFC20
void type_4F8054_B0::sub_1CFC20(RwInt32 arg_0)
{
    if (0)
        off_42CD14("cNetGameSessionManagement:: close player %d - %s\n", arg_0, unk_90[arg_0].unk_00);
    // A compiled-out check (docs/toolchain.md): the registers after it
    // are one load on.
    if (!unk_00)
    {
    }
    if (unk_0C.test(arg_0))
    {
        // A compiled-out check (docs/toolchain.md): the registers after it
        // are two loads on.
        if (!unk_00->unk_04)
        {
        }
        if (!unk_30.test(arg_0))
        {
            if (unk_00->get_unk_A8())
                unk_00->get_unk_A8()->vf_004(arg_0);
            unk_00->vf_080(1, 0);
        }
    }
    unk_0C.clear(arg_0);
    unk_00->get_unk_AC()->sub_1D0B30(type_1DDE20_mask(1 << arg_0));
    unk_00->vf_030(arg_0);
    unk_00->get_unk_B4()->sub_1D4C00(arg_0);
}

// match: ?sub_1CFD50@type_4F8054_B0@@QAEXABUtype_1CCA10@@@Z @ 0x001CFD50
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_4F8054_B0::sub_1CFD50(const type_1CCA10 &arg_0)
{
    RwUInt32 y14;
    RwUInt32 x8;
    RwInt32 bp_4 = unk_310;
    RwInt32 locc = unk_34;
    type_1CCA10 ebp_10;

    ebp_10 = arg_0 - unk_320;
    if (unk_320.get_unk_00() == 0)
        ebp_10 = 1;
    unk_320 = arg_0;
    for (x8 = 0; x8 < 0x10; x8++)
    {
        if (unk_0C.test(x8))
            unk_2D0[x8] = unk_2D0[x8] + ebp_10.unk_00;
        else
            unk_2D0[x8] = 0;
    }
    if (unk_04 == unk_08)
    {
        if (unk_00->get_unk_04() == 2)
            sub_1CD780(arg_0);
    }
    else if (unk_00->get_unk_04() == 5)
        sub_1CCD60(arg_0);
    unk_314 = bp_4;
    unk_38 = locc;
    if (!unk_324.empty())
    {
        for (y14 = 0; y14 < 0x10; y14++)
        {
            // A compiled-out check: the registers after it are two loads
            // on (docs/toolchain.md).
            if (!unk_00->unk_04)
            {
            }
            if (unk_324.test(y14))
            {
                // Two compiled-out checks (docs/toolchain.md): the registers
                // after them are four loads on.
                if (!unk_0C.unk_00)
                {
                }
                if (!unk_0C.unk_00)
                {
                }
                if (!unk_0C.test(y14))
                    unk_324.clear(y14);
                else
                {
                    type_1DDE20_mask var_18 = unk_00->get_unk_AC()->sub_1D17B0(unk_328[y14]);

                    if (var_18.empty())
                    {
                        unk_324.clear(y14);
                        sub_1CD690(y14);
                    }
                }
            }
        }
    }
}

// match: ?sub_1CFF90@type_4F8054_B0@@QAEHXZ @ 0x001CFF90
RwInt32 type_4F8054_B0::sub_1CFF90()
{
    if ((RwUInt32)unk_04 < 0 || (RwUInt32)unk_04 >= 0x10)
        return 0;
    // A compiled-out check: the register after it is one load on
    // (docs/toolchain.md).
    if (!unk_04)
    {
    }
    return unk_04;
}

// match: ?sub_1CFFC0@type_4F8054_B0@@QAEHXZ @ 0x001CFFC0
RwInt32 type_4F8054_B0::sub_1CFFC0()
{
    if ((RwUInt32)unk_04 < 0 || (RwUInt32)unk_04 >= 0x10)
        return 0;
    return 1;
}

// match: ?sub_1CFFF0@type_4F8054_B0@@QAEXHH@Z @ 0x001CFFF0
void type_4F8054_B0::sub_1CFFF0(RwInt32 arg_0, RwInt32 arg_4)
{
    RwInt32 failed;
    type_1D6480 msg;

    // A compiled-out check (docs/toolchain.md): the registers after it
    // are two loads on.
    if (!unk_00->unk_04)
    {
    }
    if (unk_48.test(arg_0))
    {
        unk_48.remove(arg_0);
        if (arg_4)
        {
            unk_4A.set(arg_0);
            if (0)
                off_42CD14("Connecting - informing host that we successfully connected to player %d\n", arg_0);
        }
        else
        {
            unk_4C.insert(arg_0);
            if (0)
                off_42CD14("Connecting - informing host that we failed to connect to player %d\n", arg_0);
        }
        msg.unk_00 = (RwUInt8)arg_0;
        msg.unk_04 = arg_4;
        failed = msg.sub_1D6480(unk_00, type_1DDE20_mask(1 << get_unk_08()), &unk_50[arg_0]) == 0;
    }
}
