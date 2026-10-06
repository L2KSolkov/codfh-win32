// The game data (dword_4FB9E0, game/data.h): its records, its settings
// block's reset, write and read, and its constructor, destructor and reset.

#include "game/liveservice.h"
#include "game/netmsg.h"
#include "game/data.h"
#include "game/mpgame.h"
#include "game/gameloop.h"
#include "types/type_DC400.h"
#include "game/fade.h"
#include "game/startup.h"
#include "game/netplayer.h"
#include "rw/rprandom.h"
#include "game/parsedfile.h"
#include "game/kujuui.h"
#include "game/ingamepages.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003E20CC
extern const RwReal flt_3E20CC = 16.666666f;
// 0x003E20D0
extern const RwReal flt_3E20D0 = 0.01f;
// 0x003E20D4
extern const RwReal flt_3E20D4 = 0.01f;
// 0x003E20D8
extern const RwReal flt_3E20D8 = 5.0f;
// 0x0042CAC0
const RwChar *off_42CAC0[4] = { "NET_GAME_STATE_GUI", "NET_GAME_STATE_GAME", "NET_GAME_STATE_LOADING_LEVEL", "NET_GAME_STATE_END_SCORES" };
// 0x0042CAD0
const RwChar *off_42CAD0[2] = { "HOST", "CLIENT" };
// 0x0042CAD8
const RwChar *off_42CAD8 = "Ran out of memory in packet engine";
// 0x0042CADC
const RwChar *off_42CADC = "Session over or network disconnected";
// 0x0042CAE0
const RwChar *off_42CAE0 = "Network error";
// 0x004F8154
#ifndef CODFH_PLAIN
RwInt32 dword_4F8154;
#endif
// End of its data definitions.

// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).
type_4FB9E0 dword_4FB9E0;


// The debug print (off_42CD14) and the front end's sub_1C5340; only the
// widths are known.
extern void (*off_42CD14)(const RwChar *arg_0, ...);
void sub_1C5340();
// The network game states' names and "HOST", "CLIENT" (.data).
extern const RwChar *off_42CAC0[4];
extern const RwChar *off_42CAD0[2];
// The network's keep-alive thread's start and stop (unit_1B18E0).
void sub_1B2810();
void sub_1B2860();
// The game's end messages ("Ran out of memory in packet engine", "Session
// over or network disconnected", "Network error"), a word the deathmatch's
// start sets to 2, and the front end's screens (sub_1C4A10 closes the
// overlay; sub_1C4A30, sub_1C4A60 and sub_1C4A90 open them). Only the widths
// are known.
extern const RwChar *off_42CAD8;
extern const RwChar *off_42CADC;
extern const RwChar *off_42CAE0;
#ifdef CODFH_PLAIN
// (plain builds: a field of the multiplayer manager unk_4F7EB8; see unit_1A8B20)
extern RwInt32 &dword_4F8154;
#else
extern RwInt32 dword_4F8154;
#endif
void sub_1C4A10();
void sub_1C4A30();
void sub_1C4A60();
void sub_1C4A90(const RwChar *arg_0);
void sub_1C3D80(RwInt32 arg_0);
void sub_1C3D20();
void sub_1C4C60();
void sub_1C49A0();
void sub_1C49E0();
void sub_1C4960();
// The data's callbacks (unit_1B18E0).
void sub_1B4510();
void sub_1B4520();
void sub_1B44A0();
void sub_1B4470();
void sub_1B4500();
void sub_1B44F0();

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0O@LPPFFDBI@Network?5error?$AA@ @ 0x003E1FFC
// match: ??_C@_0CF@MBBPIKMI@Session?5over?5or?5network?5disconne@ @ 0x003E200C
// match: ??_C@_0CD@BBDFOLKM@Ran?5out?5of?5memory?5in?5packet?5engi@ @ 0x003E2034
// match: ??_C@_06DCBACPNP@CLIENT?$AA@ @ 0x003E2058
// match: ??_C@_04CCAEFLLI@HOST?$AA@ @ 0x003E2060
// match: ??_C@_0BK@EGHAIHBP@NET_GAME_STATE_END_SCORES?$AA@ @ 0x003E2068
// match: ??_C@_0BN@CKKMCJFE@NET_GAME_STATE_LOADING_LEVEL?$AA@ @ 0x003E2084
// match: ??_C@_0BE@JKMIJNIH@NET_GAME_STATE_GAME?$AA@ @ 0x003E20A4
// match: ??_C@_0BD@ONLEKDG@NET_GAME_STATE_GUI?$AA@ @ 0x003E20B8
// match: ?flt_3E20CC@@3MB @ 0x003E20CC
// match: ?flt_3E20D0@@3MB @ 0x003E20D0
// match: ?flt_3E20D4@@3MB @ 0x003E20D4
// match: ?flt_3E20D8@@3MB @ 0x003E20D8
// match: ??_C@_0BJ@BKFHPFDC@Clean?5game?5flow?5manager?6?$AA@ @ 0x003E20DC
// match: ??_C@_0BN@JFJKPADI@?$CI?$CFs?$CJ?5Entering?5?$CFs?5game?5state?6?$AA@ @ 0x003E20F8
// match: ??_C@_0DN@HAMJLGOG@?$CIHOST?$CJ?5Send?5load?5level?5message?5?$CI@ @ 0x003E2118
// match: ??_C@_0CG@LLMCEJGL@?$CIHOST?$CJ?5Client?5index?3?5?$CFd?5joined?5g@ @ 0x003E2158
// match: ??_C@_0EK@CELCCPAM@?$CIHOST?$CJ?5Level?5load?5complete?$DL?5Send@ @ 0x003E2180
// match: ??_C@_0EF@PDEIOEMD@?$CICLIENT?$CJ?5Level?5load?5complete?$DL?5Se@ @ 0x003E21D0
// match: ??_C@_0DA@BACFONPH@?$CICLIENT?$CJ?5Reveived?5level?5load?5mes@ @ 0x003E2218
// match: ??_C@_0CC@KLIJKKOM@?$CI?$CFs?$CJ?5Set?5level?5index?5to?5load?3?5?$CFd@ @ 0x003E2248
// match: ??_C@_0EN@GMFBBENB@?$CIHOST?$CJ?5?$CILoading?5level?$CJ?5received?5@ @ 0x003E2270
// match: ??_C@_0EH@LLOJEGCL@?$CIHOST?$CJ?5?$CIIn?5game?$CJ?5received?5game?5s@ @ 0x003E22C0
// match: ??_C@_0CA@HPBMCIL@Level?5change?5to?5?$CFd?5?$CINO?5CHANGE?$CJ?6?$AA@ @ 0x003E2308
// match: ??_C@_0BN@IOFIILHD@Level?5change?5to?5?$CFd?5selected?6?$AA@ @ 0x003E2328
// match: ??_C@_0BK@HMDOCNPL@?$CIHOST?$CJ?5Round?5?$CFd?5finished?6?$AA@ @ 0x003E2348
// match: ??_C@_0CL@FBCOOANO@?$CIHOST?$CJ?5Game?5over?0?5send?5message?5t@ @ 0x003E2364
// match: ??_C@_0CM@CJONOMBF@?$CIHOST?$CJ?5Round?5over?0?5send?5message?5@ @ 0x003E2390
// match: ??_C@_0CD@HHELELED@?$CICLIENT?$CJ?5Receive?5round?5end?5notif@ @ 0x003E23BC
// match: ??_C@_0DA@OBOOFALI@?$CICLIENT?$CJ?5Load?5level?5message?5rece@ @ 0x003E23E0
// match: ??_C@_0FG@PHIMAGKB@?$CIHOST?$CJ?5All?5clients?5have?5quit?5the@ @ 0x003E2410
// match: ??_C@_0CL@DCABCAIP@?$CICLIENT?$CJ?5waiting?5for?5level?5load?5@ @ 0x003E2468
// match: __ehhandler$??0type_4FB9E0@@QAE@XZ>1>8 @ 0x0041EE80
// match: __ehhandler$??0type_4FB9E0@@QAE@XZ>1 @ 0x0041EE98
// match: __ehhandler$??1type_4FB9E0@@QAE@XZ>1>8 @ 0x0041EEB4
// match: __ehhandler$??1type_4FB9E0@@QAE@XZ>1 @ 0x0041EEC4
// match: __ehhandler$?sub_1B5860@type_4FB9E0@@QAEXPAUtype_1F8560@@@Z>1>8 @ 0x0041EEE0
// match: __ehhandler$?sub_1B5860@type_4FB9E0@@QAEXPAUtype_1F8560@@@Z>1 @ 0x0041EEE8
// match: __ehhandler$?sub_1B5BF0@type_4FB9E0@@QAEXXZ>1>8 @ 0x0041EF04
// match: __ehhandler$?sub_1B5BF0@type_4FB9E0@@QAEXXZ>1 @ 0x0041EF0C
// match: __ehhandler$?sub_1B6770@type_4FB9E0@@QAEHXZ>1>8 @ 0x0041EF28
// match: __ehhandler$?sub_1B6770@type_4FB9E0@@QAEHXZ>1 @ 0x0041EF30
// match: .CRT$XCU+0 @ 0x004271E4
// match: ?off_42CAC0@@3PAPBDA @ 0x0042CAC0
// match: ?off_42CAD0@@3PAPBDA @ 0x0042CAD0
// match: ?off_42CAD8@@3PBDB @ 0x0042CAD8
// match: ?off_42CADC@@3PBDB @ 0x0042CADC
// match: ?off_42CAE0@@3PBDB @ 0x0042CAE0

// match: _$E2 @ 0x0030C240
// match: _$E3 @ 0x0030EAB0
// match: ??0type_4FB9E0_74@@QAE@XZ @ 0x001B46B0

type_4FB9E0_74::type_4FB9E0_74()
{
    sub_1B46D0();
}

// match: ?sub_1B46D0@type_4FB9E0_74@@QAEXXZ @ 0x001B46D0
void type_4FB9E0_74::sub_1B46D0()
{
    unk_00 = 0;
}

// match: ?sub_1B46F0@type_4FB9E0_08@@QAEXXZ @ 0x001B46F0
void type_4FB9E0_08::sub_1B46F0()
{
    unk_00 = 1;
    unk_14 = 0;
    unk_18 = 0;
    unk_1C = 0;
    unk_20 = 0;
    unk_24 = 0;
    unk_04 = 0;
    unk_08 = 0;
    unk_0C = 0;
    unk_10 = 0;
    unk_28 = 0;
    unk_2C = 0;
    unk_30 = 0;
}

// match: ?sub_1B4780@type_4FB9E0_08@@QAEXPAUtype_1F8560@@@Z @ 0x001B4780
void type_4FB9E0_08::sub_1B4780(type_1F8560 *arg_0)
{
    RwInt32 var_4;

    arg_0->sub_1F8860(unk_00, 5);
    arg_0->sub_1F8520(unk_04);
    arg_0->sub_1F8520(unk_08);
    arg_0->sub_1F8520(unk_0C);
    arg_0->sub_1F8520(unk_10);
    arg_0->sub_1F85F0(unk_14);
    arg_0->sub_1F8520(unk_30);
    var_4 = sub_1F84A0(9999999);
    arg_0->sub_1F8860(unk_18, var_4);
    var_4 = sub_1F84A0(999);
    arg_0->sub_1F8860(unk_1C, var_4);
    arg_0->sub_1F8520(unk_20);
    var_4 = sub_1F84A0(6);
    arg_0->sub_1F8860(unk_24, var_4);
    var_4 = sub_1F84A0(8);
    arg_0->sub_1F8860(unk_28, var_4);
    arg_0->sub_1F85F0(unk_2C);
}

// match: ?sub_1B48A0@type_4FB9E0_08@@QAEXPAUtype_1F8560@@@Z @ 0x001B48A0
void type_4FB9E0_08::sub_1B48A0(type_1F8560 *arg_0)
{
    RwInt32 var_4;

    unk_00 = arg_0->sub_1F8810(5);
    unk_04 = arg_0->sub_1F8560();
    unk_08 = arg_0->sub_1F8560();
    unk_0C = arg_0->sub_1F8560();
    unk_10 = arg_0->sub_1F8560();
    unk_14 = arg_0->sub_1F85A0();
    unk_30 = arg_0->sub_1F8560();
    var_4 = sub_1F84A0(9999999);
    unk_18 = arg_0->sub_1F8810(var_4);
    var_4 = sub_1F84A0(999);
    unk_1C = arg_0->sub_1F8810(var_4);
    unk_20 = arg_0->sub_1F8560();
    var_4 = sub_1F84A0(6);
    unk_24 = arg_0->sub_1F8810(var_4);
    var_4 = sub_1F84A0(8);
    unk_28 = arg_0->sub_1F8810(var_4);
    unk_2C = arg_0->sub_1F85A0();
}

// match: ??0type_4FB9E0@@QAE@XZ @ 0x001B49B0
// match: __ehhandler$??0type_4FB9E0@@QAE@XZ-0x2C @ 0x00302C30
// match: __ehhandler$??0type_4FB9E0@@QAE@XZ @ 0x00302C5C
type_4FB9E0::type_4FB9E0()
{
    sub_1B4AA0();
}

// match: ??1type_4FB9E0@@QAE@XZ @ 0x001B4A30
// match: __ehhandler$??1type_4FB9E0@@QAE@XZ-0x16 @ 0x00302C70
// match: __ehhandler$??1type_4FB9E0@@QAE@XZ @ 0x00302C86
type_4FB9E0::~type_4FB9E0()
{
}

// match: ?sub_1B4AA0@type_4FB9E0@@QAEXXZ @ 0x001B4AA0
void type_4FB9E0::sub_1B4AA0()
{
    RwUInt32 var_4;

    sub_1C5340();
    if (CODFH_DEBUG_LOGS)
        off_42CD14("Clean game flow manager\n");
    unk_04 = 0;
    unk_08.sub_1B46F0();
    unk_3C = 0;
    unk_40.sub_1B46F0();
    for (var_4 = 0; var_4 < 16; var_4++)
        unk_74[var_4].sub_1B46D0();
    sub_1B5700();
    unk_B4 = 0;
    unk_B8 = 0;
    unk_BC = 0;
    unk_C0 = 0;
    unk_C4 = 0;
    unk_C8 = 0;
    unk_CC = 0;
    unk_D0 = 0;
    unk_D8 = 0;
    unk_D4 = 0;
    unk_F4 = 0;
    unk_F8 = 0;
    unk_100 = 0;
    unk_108 = 0;
    unk_104 = 0;
    unk_10C = 0;
    unk_114 = 1;
    unk_118 = 0;
}

// match: ?sub_1B4C10@type_4FB9E0@@QAEXPAUtype_1F8560@@@Z @ 0x001B4C10
void type_4FB9E0::sub_1B4C10(type_1F8560 *arg_0)
{
    RwInt32 var_4;

    unk_08.sub_1B4780(arg_0);
    var_4 = sub_1F84A0(999);
    arg_0->sub_1F8860(unk_B4, var_4);
    arg_0->sub_1F8520(unk_3C);
    arg_0->sub_1F8520(unk_10C);
}

// match: ?sub_1B4C80@type_4FB9E0@@QAEXPAUtype_1F8560@@@Z @ 0x001B4C80
void type_4FB9E0::sub_1B4C80(type_1F8560 *arg_0)
{
    RwInt32 var_4;

    unk_40.sub_1B48A0(arg_0);
    var_4 = sub_1F84A0(999);
    unk_B4 = arg_0->sub_1F8810(var_4);
    unk_3C = arg_0->sub_1F8560();
    unk_10C = arg_0->sub_1F8560();
}

// match: ?sub_1B4CF0@type_4FB9E0@@QAEXH@Z @ 0x001B4CF0
void type_4FB9E0::sub_1B4CF0(RwInt32 arg_0)
{
    // A compiled-out check (docs/toolchain.md): the registers after it
    // are one load on.
    if (!unk_04)
    {
    }
    if (CODFH_DEBUG_LOGS)
        off_42CD14("(%s) Entering %s game state\n", off_42CAD0[unk_4F61F8.unk_104], off_42CAC0[arg_0]);
    unk_04 = arg_0;
}

// match: ?sub_1B4D40@type_4FB9E0@@QAE?AUtype_1DDE20_mask@@XZ @ 0x001B4D40
type_1DDE20_mask type_4FB9E0::sub_1B4D40()
{
    // The locals' names state their slots (docs/toolchain.md).
    RwUInt32 bp_8;
    type_1DDE20_mask bp_4;

    bp_4.unk_00 = 0;
    for (bp_8 = 0; bp_8 < 16; bp_8++)
    {
        if (unk_74[bp_8].get_unk_00())
            bp_4.include(bp_8);
    }
    // A compiled-out check (docs/toolchain.md): the registers after it are
    // one load on.
    if (!unk_04)
    {
    }
    return bp_4;
}

// match: ?sub_1B4DB0@type_4FB9E0@@QAEXXZ @ 0x001B4DB0
void type_4FB9E0::sub_1B4DB0()
{
    RwUInt32 var_4;

    for (var_4 = 0; var_4 < 16; var_4++)
        unk_74[var_4].unk_00 = 0;
}

// match: ?sub_1B4DF0@type_4FB9E0@@QAEXXZ @ 0x001B4DF0
void type_4FB9E0::sub_1B4DF0()
{
    // The locals' names state their slots (docs/toolchain.md).
    type_1DDE20_mask bp_8;
    type_3E1074 bp_4;

    sub_1B4CF0(2);
    // Two compiled-out checks (docs/toolchain.md): the registers after
    // them are two loads on.
    if (!unk_04)
    {
    }
    if (!unk_04)
    {
    }
    unk_D8 = 0;
    unk_DC = 0;
    if (!unk_4F61F8.unk_104)
    {
        bp_8 = type_4F8054::get()->get_unk_B0()->sub_1A8050();
        unk_00->sub_1DDDB0(&bp_4, bp_8);
        unk_3C = 0;
        if (CODFH_DEBUG_LOGS)
            off_42CD14("(HOST) Broadcast level load start to clients\n");
    }
    sub_1B2810();
}

// Player arg_0 joined: the host sends it the rules message while the rules
// allow it (sub_1E3480 1 or 2).
// match: ?sub_1B4EA0@type_4FB9E0@@QAEXH@Z @ 0x001B4EA0
void type_4FB9E0::sub_1B4EA0(RwInt32 arg_0)
{
    type_1DDE20_mask bp_8;
    type_3E1074 bp_4;

    if (!unk_4F61F8.unk_104)
    {
        if (CODFH_DEBUG_LOGS)
            off_42CD14("(HOST) Client index: %d joined game \n", arg_0);
        if (((kujuUI::type_1C8DF0_104_00 *)this)->sub_1E3480() == 1 || ((kujuUI::type_1C8DF0_104_00 *)this)->sub_1E3480() == 2)
        {
            // A compiled-out check (docs/toolchain.md): the registers after it
            // are one load on.
            if (!unk_04)
            {
            }
            bp_8.only(arg_0);
            unk_00->sub_1DDDB0(&bp_4, bp_8);
            if (CODFH_DEBUG_LOGS)
                off_42CD14("(HOST) Send load level message (id: %d) to client index: %d\n", unk_08.unk_28, arg_0);
        }
    }
}

// match: ?sub_1B4F40@type_4FB9E0@@QAEXXZ @ 0x001B4F40
void type_4FB9E0::sub_1B4F40()
{
    // The locals' names state their slots (docs/toolchain.md).
    type_1DDE20_mask lv_10;
    type_3E10A4 slot_C;
    type_3E108C bp_8;
    type_3E105C bp_4;

    if (unk_D8)
        return;
    sub_1B4CF0(1);
    // Two compiled-out checks (docs/toolchain.md): the registers after
    // them are two loads on.
    if (!unk_04)
    {
    }
    if (!unk_04)
    {
    }
    unk_C0 = 0;
    unk_4F7EB8.sub_1A9440();
    sub_1B59F0();
    if (unk_4F61F8.unk_104)
    {
        if (type_4F8054::get()->get_unk_10() || unk_C8)
        {
            unk_C8 = 1;
            dword_4FB9E0.sub_1B6AA0();
            unk_4F7EB8.sub_1AB440();
        }
        else if (unk_C4)
        {
            dword_4FB9E0.sub_1B69B0();
            lv_10.just(0);
            unk_00->sub_1DDDB0(&bp_8, lv_10);
            dword_4FB9E0.sub_1B69B0();
        }
        else
        {
            // Two compiled-out checks (docs/toolchain.md): the registers after
            // them are two loads on.
            if (!unk_04)
            {
            }
            if (!unk_04)
            {
            }
            lv_10.just(0);
            unk_00->sub_1DDDB0(&slot_C, lv_10);
            if (CODFH_DEBUG_LOGS)
                off_42CD14("(CLIENT) Level load complete; Send game synchronise request to host\n");
        }
    }
    else
    {
        lv_10 = sub_1B4D40();
        unk_00->sub_1DDDB0(&bp_4, lv_10);
        sub_1B4DB0();
        if (CODFH_DEBUG_LOGS)
            off_42CD14("(HOST) Level load complete; Send game synchronise message to all clients\n");
        sub_1B6470();
        sub_1B51D0();
    }
    sub_1B2860();
    unk_D8 = 1;
}

// The game ends for reason arg_0 (once, unk_C8): state 3, the manager's
// leave (sub_1AF6F0), and outside a level load the end message.
// match: ?sub_1B5110@type_4FB9E0@@QAEXH@Z @ 0x001B5110
void type_4FB9E0::sub_1B5110(RwInt32 arg_0)
{
    const RwChar *var_4;

    if (unk_C8)
        return;
    switch (arg_0)
    {
    case 6:
        var_4 = off_42CAD8;
        break;
    case 7:
        var_4 = off_42CADC;
        break;
    default:
        var_4 = off_42CAE0;
        break;
    }
    unk_C8 = 1;
    unk_E4 = 0;
    unk_100 = 1;
    sub_1B4CF0(3);
    unk_4F7EB8.sub_1AF6F0();
    if (unk_04 == 2)
        unk_E0 = 1;
    else
    {
        unk_E0 = 0;
        sub_1C4A90(var_4);
    }
}

// match: ?sub_1B51D0@type_4FB9E0@@QAEXXZ @ 0x001B51D0
void type_4FB9E0::sub_1B51D0()
{
    unk_108 = 0;
    unk_104 = 0;
    if (unk_08.unk_00 == 1)
    {
        dword_4F8154 = 2;
        unk_4F7EB8.sub_1AFF20(2);
    }
    if (!unk_08.unk_0C && unk_08.unk_00 != 1)
    {
        sub_1C4A60();
        unk_108 = 1;
    }
    else
    {
        sub_1C4A30();
        unk_104 = 1;
    }
}

// match: ?sub_1B5250@type_4FB9E0@@QAEXH@Z @ 0x001B5250
void type_4FB9E0::sub_1B5250(RwInt32 arg_0)
{
    unk_E0 = arg_0;
    if (unk_108)
    {
        sub_1C4A10();
        sub_1C4A30();
        unk_104 = 1;
        unk_108 = 0;
    }
    else if (unk_104)
    {
        unk_104 = 0;
        sub_1C4A10();
        unk_4F7EB8.sub_1AB400(1);
    }
}

// The level load completes (the game loop's wrapper, sub_1A2D60): as
// sub_1B4F40, but the pickups reset first, and a client ending or
// rejoining fades out to its callback.
// match: ?sub_1B52D0@type_4FB9E0@@QAEXXZ @ 0x001B52D0
void type_4FB9E0::sub_1B52D0()
{
    // The locals' names state their slots (docs/toolchain.md).
    type_1DDE20_mask slot_C;
    type_3E10A4 bp_8;
    type_3E105C bp_4;

    if (unk_D8)
        return;
    sub_1B4CF0(1);
    // Two compiled-out checks (docs/toolchain.md): the registers after
    // them are two loads on.
    if (!unk_04)
    {
    }
    if (!unk_04)
    {
    }
    unk_C0 = 0;
    unk_4F7EB8.sub_1A9440();
    if (!unk_4F61F8.unk_104)
        dword_4FBB20.sub_1BD9F0();
    else
        dword_4FBB20.sub_1BD950();
    sub_1B59F0();
    if (unk_4F61F8.unk_104)
    {
        if (unk_C8)
        {
            sub_1252E0(sub_1B4520, 1);
            sub_124EE0(0.5f, 1);
        }
        else if (unk_C4)
        {
            sub_1252E0(sub_1B4510, 1);
            sub_124EE0(0.5f, 1);
        }
        else
        {
            // Two compiled-out checks (docs/toolchain.md): the registers after
            // them are two loads on.
            if (!unk_04)
            {
            }
            if (!unk_04)
            {
            }
            slot_C.just(0);
            unk_00->sub_1DDDB0(&bp_8, slot_C);
            if (CODFH_DEBUG_LOGS)
                off_42CD14("(CLIENT) Level load complete; Send game synchronise request to host\n");
        }
    }
    else
    {
        slot_C = sub_1B4D40();
        unk_00->sub_1DDDB0(&bp_4, slot_C);
        sub_1B4DB0();
        if (CODFH_DEBUG_LOGS)
            off_42CD14("(HOST) Level load complete; Send game synchronise message to all clients\n");
        sub_1B6470();
        sub_1B51D0();
    }
    unk_D8 = 1;
}

// The rules message arrives (a client's): unk_B8 cleared.
// match: ?sub_1B5470@type_4FB9E0@@QAEXABUtype_3E1074@@@Z @ 0x001B5470
void type_4FB9E0::sub_1B5470(const type_3E1074 &arg_0)
{
    if (unk_B8)
    {
        unk_B8 = 0;
        if (CODFH_DEBUG_LOGS)
            off_42CD14("(CLIENT) Reveived level load message from host\n");
    }
}

// match: ?sub_1B54B0@type_4FB9E0@@QAEXH@Z @ 0x001B54B0
void type_4FB9E0::sub_1B54B0(RwInt32 arg_0)
{
    // A compiled-out check (docs/toolchain.md): the registers after it
    // are one load on.
    if (!unk_04)
    {
    }
    unk_08.unk_28 = arg_0;
    sub_19B000(unk_08.unk_28 + 1);
    sub_1C3D80(unk_08.unk_28);
    if (CODFH_DEBUG_LOGS)
        off_42CD14("(%s) Set level index to load: %d\n", off_42CAD0[unk_4F61F8.unk_104], arg_0);
}

// A client asks to synchronise (the handler, sub_1AF370): in game the host
// sends it the full game state; while loading its record is set.
// match: ?sub_1B5510@type_4FB9E0@@QAEXH@Z @ 0x001B5510
void type_4FB9E0::sub_1B5510(RwInt32 arg_0)
{
    type_1DDE20_mask bp_8;
    type_3E105C bp_4;

    if (((kujuUI::type_1C8DF0_104_00 *)this)->sub_1E3480() == 1)
    {
        // Two compiled-out checks (docs/toolchain.md): the registers after
        // them are two loads on.
        if (!unk_04)
        {
        }
        if (!unk_04)
        {
        }
        bp_8.only(arg_0);
        unk_00->sub_1DDDB0(&bp_4, bp_8);
        if (CODFH_DEBUG_LOGS)
            off_42CD14("(HOST) (In game) received game synchronise request from client id: %d\n", arg_0);
    }
    else
    {
        unk_74[arg_0].unk_00 = 1;
        if (CODFH_DEBUG_LOGS)
            off_42CD14("(HOST) (Loading level) received game synchronise request from client id: %d\n", arg_0);
    }
}

// match: ?sub_1B55B0@type_4FB9E0@@QAEXPAUtype_4F8058@@@Z @ 0x001B55B0
void type_4FB9E0::sub_1B55B0(type_4F8058 *arg_0)
{
    // A compiled-out check (docs/toolchain.md): the registers after it
    // are one load on.
    if (!unk_04)
    {
    }
    unk_00 = arg_0;
}

// match: ?sub_1B55D0@type_4FB9E0@@QAEXABUtype_4FB9E0_08@@@Z @ 0x001B55D0
void type_4FB9E0::sub_1B55D0(const type_4FB9E0_08 &arg_0)
{
    unk_08 = arg_0;
}

// match: ?sub_1B5600@type_4FB9E0@@QAEXABUtype_4FB9E0_08@@H@Z @ 0x001B5600
void type_4FB9E0::sub_1B5600(const type_4FB9E0_08 &arg_0, RwInt32 arg_4)
{
    if (arg_0.unk_00 != unk_40.unk_00 || arg_0.unk_28 != unk_40.unk_28)
        unk_3C = 1;
    else
        unk_3C = 0;
    unk_40 = arg_0;
    if (unk_40.unk_04)
    {
        unk_40.unk_14 = 0;
        unk_40.unk_18 = 0;
    }
    if (arg_4)
        sub_1B6310();
    unk_F8 = arg_0.unk_28;
}

// match: ?sub_1B5690@type_4FB9E0@@QAEXXZ @ 0x001B5690
void type_4FB9E0::sub_1B5690()
{
    if (unk_40.unk_0C && !unk_08.unk_0C)
    {
        dword_4F8154 = 1;
        unk_4F7EB8.sub_1AFF20(1);
    }
    unk_08 = unk_40;
    sub_1C3D20();
    sub_1B54B0(unk_08.unk_28);
    unk_B8 = 0;
}

// match: ?sub_1B5700@type_4FB9E0@@QAEXXZ @ 0x001B5700
void type_4FB9E0::sub_1B5700()
{
    unk_4F7EB8.unk_04.sub_1B3820();
    unk_4F7EB8.unk_D0.sub_1B3820();
    unk_E8 = 0;
    unk_EC = 0;
    unk_118 = 0;
}

// match: ?sub_1B5750@type_4FB9E0@@QAEXXZ @ 0x001B5750
void type_4FB9E0::sub_1B5750()
{
    unk_4F7EB8.unk_04.sub_1B3820();
    sub_1C5340();
    unk_E8 = 0;
    unk_EC = 0;
    unk_118 = 0;
}

// match: ?sub_1B57A0@type_4FB9E0@@QAEXXZ @ 0x001B57A0
void type_4FB9E0::sub_1B57A0()
{
    unk_B4 = 0;
}

// match: ?sub_1B57C0@type_4FB9E0@@QAEXXZ @ 0x001B57C0
void type_4FB9E0::sub_1B57C0()
{
    unk_B8 = 1;
}

// Its part of the full game state (the message's write and read, unit_1B18E0).
// match: ?sub_1B57E0@type_4FB9E0@@QAEXPAUtype_1F8560@@@Z @ 0x001B57E0
void type_4FB9E0::sub_1B57E0(type_1F8560 *arg_0)
{
    RwInt32 var_4;

    unk_08.sub_1B4780(arg_0);
    var_4 = sub_1F84A0(999);
    arg_0->sub_1F8860(unk_B4, var_4);
    arg_0->sub_1F85F0(unk_C0);
    arg_0->sub_1F8520(unk_10C);
    arg_0->sub_1F8520(unk_114);
}

// A change of game type, level or team count ends the game (state 3 and
// the quit, sub_D8C00); a zero last word runs sub_1B6EF0(0).
// match: ?sub_1B5860@type_4FB9E0@@QAEXPAUtype_1F8560@@@Z @ 0x001B5860
// match: __ehhandler$?sub_1B5860@type_4FB9E0@@QAEXPAUtype_1F8560@@@Z-0x8 @ 0x00302C90
// match: __ehhandler$?sub_1B5860@type_4FB9E0@@QAEXPAUtype_1F8560@@@Z @ 0x00302C98
void type_4FB9E0::sub_1B5860(type_1F8560 *arg_0)
{
    // The locals' names state their slots (docs/toolchain.md).
    RwInt32 o4C;
    type_4FB9E0_08 q48;
    RwInt32 ebp_14;
    RwInt32 lv_10;

    q48.sub_1B48A0(arg_0);
    lv_10 = sub_1F84A0(999);
    unk_B4 = arg_0->sub_1F8810(lv_10);
    unk_C0 = arg_0->sub_1F85A0();
    ebp_14 = arg_0->sub_1F8560();
    o4C = arg_0->sub_1F8560();
    if (!o4C)
        sub_1B6EF0(0);
    if (unk_08.unk_00 != q48.unk_00)
    {
        sub_1B5700();
        unk_BC = 1;
        sub_1B4CF0(3);
        sub_D8C00();
    }
    if (unk_08.unk_28 != q48.unk_28)
    {
        unk_BC = 1;
        sub_1B4CF0(3);
        sub_D8C00();
    }
    if (unk_10C != ebp_14)
    {
        unk_BC = 1;
        sub_1B4CF0(3);
        sub_D8C00();
    }
    unk_08 = q48;
    unk_10C = ebp_14;
    sub_1B54B0(unk_08.unk_28);
    unk_B8 = 0;
}

// match: ?sub_1B59D0@type_4FB9E0@@QAEXXZ @ 0x001B59D0
void type_4FB9E0::sub_1B59D0()
{
    if (!unk_BC)
        sub_1B51D0();
}

// match: ?sub_1B59F0@type_4FB9E0@@QAEXXZ @ 0x001B59F0
void type_4FB9E0::sub_1B59F0()
{
    // A compiled-out check (docs/toolchain.md): the registers after it
    // are one load on.
    if (!unk_04)
    {
    }
    unk_D0 = sub_1CCA10().ref_unk_00() * 0.001f;
    if (!unk_4F61F8.unk_104)
        unk_C0 = 0;
}

// Its step (the multiplayer manager's): while the rules run (sub_1E3480 1
// or 3) the late service's word ends the game (sub_1B44A0); then the round's
// time counts on (unless the settings' unk_14 is 0) and the elapsed time
// goes to sub_1B6E00.
// match: ?sub_1B5A40@type_4FB9E0@@QAEXXZ @ 0x001B5A40
void type_4FB9E0::sub_1B5A40()
{
    RwReal var_4;

    if (((kujuUI::type_1C8DF0_104_00 *)&dword_4FB9E0)->sub_1E3480() != 1 && ((kujuUI::type_1C8DF0_104_00 *)&dword_4FB9E0)->sub_1E3480() != 3)
        return;
    if (((kujuUI::type_1EE900 *)sub_227560())->sub_1EE9D0())
    {
        unk_C8 = 1;
        sub_1B44A0();
    }
    if (unk_DC)
        return;
    if (((kujuUI::type_1C8DF0_104_00 *)this)->sub_1E3480() == 3)
    {
        sub_1B5BF0();
        return;
    }
    // A compiled-out check (docs/toolchain.md): the registers after it are
    // one load on.
    if (!unk_04)
    {
    }
    var_4 = sub_1CCA10().ref_unk_00() * 0.001f - unk_D0;
    unk_D0 = sub_1CCA10().ref_unk_00() * 0.001f;
    if (unk_08.unk_14 != 0.0f)
        unk_C0 += var_4;
    if (!unk_4F61F8.unk_104)
        sub_1B6130();
    sub_1B6E00(var_4);
}

// match: ?sub_1B5B50@type_4FB9E0@@QAEXH@Z @ 0x001B5B50
void type_4FB9E0::sub_1B5B50(RwInt32 arg_0)
{
    if (unk_08.unk_28 != arg_0)
    {
        unk_F4 = 1;
        if (CODFH_DEBUG_LOGS)
            sub_1C8A30("Level change to %d selected\n", arg_0);
    }
    else
    {
        if (CODFH_DEBUG_LOGS)
            sub_1C8A30("Level change to %d (NO CHANGE)\n", arg_0);
        unk_F4 = 0;
    }
    unk_F8 = arg_0;
}

// match: ?sub_1B5BC0@type_4FB9E0@@QAEXXZ @ 0x001B5BC0
void type_4FB9E0::sub_1B5BC0()
{
    if (unk_4F61F8.unk_104)
        sub_1B6B50();
    else
        sub_1B6200();
}

// The end of a round (the in-game step while the rules say 3): a client
// ending leaves, or takes the host's settings and fades to its callback; the
// host waits for the peers (sub_1B6CF0), may take a new level into its
// settings, resets and fades, swapping the teams' sides (unk_10C) when the
// settings' unk_08 is set.
// match: ?sub_1B5BF0@type_4FB9E0@@QAEXXZ @ 0x001B5BF0
// match: __ehhandler$?sub_1B5BF0@type_4FB9E0@@QAEXXZ-0x8 @ 0x00302CB0
// match: __ehhandler$?sub_1B5BF0@type_4FB9E0@@QAEXXZ @ 0x00302CB8
void type_4FB9E0::sub_1B5BF0()
{
    // Two compiled-out checks (docs/toolchain.md): the registers after them
    // are two loads on.
    if (!unk_04)
    {
    }
    if (!unk_04)
    {
    }
    if (unk_4F61F8.unk_104)
    {
        if (unk_C8)
        {
            unk_4F7EB8.sub_1AF6F0();
            if (unk_E0)
            {
                unk_DC = 1;
                sub_124EE0(0.5f, 1);
                sub_1252E0(sub_1B44A0, 1);
            }
        }
        else if (unk_C4 && !unk_B8)
        {
            unk_C4 = 0;
            unk_C0 = 0;
            sub_1B5F90();
            if (unk_3C)
            {
                sub_1B5700();
                sub_1252E0(sub_1B44A0, 1);
            }
            else if (unk_08.unk_28 != unk_40.unk_28)
                sub_1252E0(sub_1B44A0, 1);
            else
                sub_1252E0(sub_1B4470, 1);
            sub_1B5690();
            unk_3C = 0;
            unk_DC = 1;
            sub_124EE0(0.5f, 1);
        }
    }
    else if (unk_C8)
    {
        sub_1B6C20();
        if (sub_1B6CF0())
        {
            sub_1C4C60();
            if (!unk_100)
            {
                unk_4F7EB8.sub_1AF6F0();
                unk_100 = 1;
            }
            if (unk_E0)
            {
                unk_DC = 1;
                unk_100 = 0;
                sub_124EE0(0.5f, 1);
                sub_1252E0(sub_1B44A0, 1);
            }
        }
    }
    else if (unk_C4)
    {
        if ((unk_E0 || unk_E4) && unk_F8 != unk_40.unk_28)
        {
            type_4FB9E0_08 var_40 = unk_40;

            var_40.unk_28 = unk_F8;
            sub_1B5600(var_40, 0);
        }
        if (unk_E0 || unk_E4)
        {
            unk_C4 = 0;
            unk_C0 = 0;
            sub_1B5F90();
            if (unk_3C)
            {
                sub_1B5700();
                sub_1B5690();
                if (unk_F4 && (!unk_E4 || unk_FC))
                    sub_1B54B0(unk_F8);
                sub_1252E0(sub_1B44A0, 1);
            }
            else if (unk_F4 && (!unk_E4 || unk_FC))
            {
                sub_1B5690();
                sub_1252E0(sub_1B44A0, 1);
            }
            else
            {
                sub_1B5690();
                sub_1252E0(sub_1B4470, 1);
            }
            sub_1B60E0();
            unk_DC = 1;
            sub_124EE0(0.5f, 1);
            if (unk_08.unk_08)
                unk_10C = unk_10C == 0;
        }
    }
}

// match: ?sub_1B5F90@type_4FB9E0@@QAEXXZ @ 0x001B5F90
void type_4FB9E0::sub_1B5F90()
{
    // The locals' names state their slots (docs/toolchain.md).
    RwInt32 l1C;
    RwInt32 m_18;
    RwInt32 ebp_14;
    RwInt32 lv_10;
    RwInt32 slot_C;
    RwInt32 bp_8;
    RwInt32 bp_4;

    if (unk_08.unk_00 == 1)
        return;
    bp_4 = unk_4F7EB8.unk_04.sub_1B33C0(4);
    l1C = unk_4F7EB8.unk_04.sub_1B33C0(2);
    m_18 = dword_4F8288.sub_1C2500(4);
    bp_8 = dword_4F8288.sub_1C2500(2);
    ebp_14 = dword_4F8154;
    lv_10 = unk_4F7EB8.unk_04.sub_1B2AF0(unk_4F7EB8.sub_1AEC70(), ebp_14);
    if (m_18 == bp_8)
        return;
    slot_C = m_18 - bp_8;
    if (slot_C > 1 && ebp_14 == 4)
    {
        if (bp_4 > l1C)
        {
            if (lv_10 < slot_C)
            {
                unk_4F7EB8.sub_1AFF20(2);
                dword_4F8154 = 2;
            }
        }
        else if (lv_10 + slot_C > m_18)
        {
            unk_4F7EB8.sub_1AFF20(2);
            dword_4F8154 = 2;
        }
    }
    else if (slot_C < -1 && ebp_14 == 2)
    {
        slot_C = -slot_C;
        if (l1C > bp_4)
        {
            if (lv_10 < slot_C)
            {
                unk_4F7EB8.sub_1AFF20(4);
                dword_4F8154 = 4;
            }
        }
        else if (lv_10 + slot_C > m_18)
        {
            unk_4F7EB8.sub_1AFF20(4);
            dword_4F8154 = 4;
        }
    }
}

// Tells the network game the settings (vf_064): the time limit's index, the
// game type, unk_04, unk_0C and unk_10. A check compiled out of this build
// (an empty if) moves the registers one step on.
// match: ?sub_1B60E0@type_4FB9E0@@QAEXXZ @ 0x001B60E0
void type_4FB9E0::sub_1B60E0()
{
    if (!unk_00)
    {
    }
    unk_4F7EB8.get_unk_19C_direct()->vf_064(unk_08.unk_28, unk_08.unk_00, unk_08.unk_04, unk_08.unk_0C,
                                            unk_08.unk_10);
}

// The host's round check each step: the round ends when its time passes
// the settings' unk_14 or sub_1B6770 says so; the round's scores go into the
// game's, and the game ends (sub_1B6200) or the next round starts
// (sub_1B6310).
// match: ?sub_1B6130@type_4FB9E0@@QAEXXZ @ 0x001B6130
void type_4FB9E0::sub_1B6130()
{
    // A compiled-out check (docs/toolchain.md): the registers after it
    // are one load on.
    if (!unk_04)
    {
    }
    if (unk_C4 || unk_C8 || unk_BC)
        return;
    if (type_215740::sub_215910(&dword_5051D0))
        return;
    if (unk_C0 > unk_08.unk_14 || sub_1B6770())
    {
        if (CODFH_DEBUG_LOGS)
            off_42CD14("(HOST) Round %d finished\n", unk_B4);
        unk_4F7EB8.unk_D0.sub_1B38E0();
        unk_B4++;
        if (sub_1E4CB0())
            sub_1B6200();
        else
            sub_1B6310();
    }
}

// match: ?sub_1B6200@type_4FB9E0@@QAEXXZ @ 0x001B6200
void type_4FB9E0::sub_1B6200()
{
    if (!unk_C8)
    {
        sub_1252E0(sub_1B4500, 1);
        sub_124EE0(0.5f, 1);
        unk_C8 = 1;
    }
}

// match: ?sub_1B6250@type_4FB9E0@@QAEXXZ @ 0x001B6250
void type_4FB9E0::sub_1B6250()
{
    type_1DDE20_mask bp_8;
    type_3E0EB8 bp_4;

    if (CODFH_DEBUG_LOGS)
        off_42CD14("(HOST) Game over, send message to clients\n");
    sub_1B4CF0(3);
    unk_4F7EB8.sub_1AB400(2);
    bp_8 = type_4F8054::get()->get_unk_B0()->sub_1A8050();
    unk_00->sub_1DDDB0(&bp_4, bp_8);
    unk_E0 = 0;
    unk_E4 = 0;
    sub_1C49A0();
    sub_124EE0(0.5f, 0);
}

// match: ?sub_1B6310@type_4FB9E0@@QAEXXZ @ 0x001B6310
void type_4FB9E0::sub_1B6310()
{
    if (!unk_C4)
    {
        sub_1252E0(sub_1B44F0, 1);
        sub_124EE0(0.5f, 1);
        unk_C4 = 1;
    }
}

// A round ends (the host's): state 3, the manager's view, the rules sent,
// the level chosen for the next round (unk_68) taken if it changed.
// match: ?sub_1B6360@type_4FB9E0@@QAEXXZ @ 0x001B6360
void type_4FB9E0::sub_1B6360()
{
    type_1DDE20_mask bp_8;
    type_3E1044 bp_4;

    if (CODFH_DEBUG_LOGS)
        off_42CD14("(HOST) Round over, send message to clients\n");
    sub_1B4CF0(3);
    unk_4F7EB8.sub_1AB400(2);
    bp_8 = type_4F8054::get()->get_unk_B0()->sub_1A8050();
    unk_00->sub_1DDDB0(&bp_4, bp_8);
    unk_E0 = 0;
    unk_E4 = 0;
    sub_1C4960();
    if (unk_08.unk_28 != unk_40.unk_28)
    {
        unk_FC = 1;
        sub_1B5B50(unk_40.unk_28);
    }
    else
        unk_FC = 0;
    unk_F8 = unk_40.unk_28;
    sub_1B5B50(unk_40.unk_28);
    sub_124EE0(0.5f, 0);
}

// The next round's settings (unk_40): the current ones with the level
// moved on by the rotation (the settings' unk_24: 1 up, 2 down, 3 a
// different random one of the eight).
// match: ?sub_1B6470@type_4FB9E0@@QAEXXZ @ 0x001B6470
void type_4FB9E0::sub_1B6470()
{
    RwInt32 var_4;

    unk_40 = unk_08;
    switch (unk_08.unk_24)
    {
    case 1:
        unk_40.unk_28++;
        if (unk_40.unk_28 == 8)
            unk_40.unk_28 = 0;
        break;
    case 2:
        if (unk_40.unk_28 == 0)
            unk_40.unk_28 = 7;
        else
            unk_40.unk_28--;
        break;
    case 3:
        var_4 = unk_40.unk_28;
        while (var_4 == unk_40.unk_28)
            unk_40.unk_28 = RpRandom() % 8;
        break;
    }
}

// match: ?sub_1B6530@type_4FB9E0@@QAEXXZ @ 0x001B6530
void type_4FB9E0::sub_1B6530()
{
    unk_E8 = 1;
}

// match: ?sub_1B6550@type_4FB9E0@@QAEXH@Z @ 0x001B6550
void type_4FB9E0::sub_1B6550(RwInt32 arg_0)
{
    unk_EC = 1;
    unk_F0 = arg_0;
}

// match: ?sub_1B6580@type_4FB9E0@@QAEHXZ @ 0x001B6580
RwInt32 type_4FB9E0::sub_1B6580()
{
    RwInt32 slot_C;
    type_1DDE20_mask bp_8;
    RwUInt32 bp_4;

    slot_C = 0;
    if (!type_4F8054::get())
        return 0;
    if (!type_4F8054::get()->get_unk_B0())
        return 0;
    bp_8 = type_4F8054::get()->get_unk_B0()->get_unk_0C();
    for (bp_4 = 0; bp_4 < 16; bp_4++)
    {
        // Two compiled-out checks (docs/toolchain.md): the registers after
        // them are two loads on.
        if (!unk_04)
        {
        }
        if (!unk_04)
        {
        }
        if (bp_8.test(bp_4))
        {
            // A compiled-out check (docs/toolchain.md): the registers after
            // it are one load on.
            if (!unk_04)
            {
            }
            if (!unk_4F6B00[bp_4].get_unk_130())
                slot_C++;
        }
    }
    return slot_C;
}

// match: ?sub_1B6650@type_4FB9E0@@QAEHXZ @ 0x001B6650
RwInt32 type_4FB9E0::sub_1B6650()
{
    RwInt32 m_18;
    RwInt32 ebp_14;
    type_1DDE20_mask lv_10;
    RwUInt32 slot_C;
    RwUInt32 bp_8;
    RwUInt32 bp_4;

    bp_8 = 0;
    bp_4 = 0;
    if (!type_4F8054::get())
        return 0;
    if (!type_4F8054::get()->get_unk_B0())
        return 0;
    lv_10 = type_4F8054::get()->get_unk_B0()->get_unk_0C();
    for (slot_C = 0; slot_C < 16; slot_C++)
    {
        // Two compiled-out checks (docs/toolchain.md): the registers after
        // them are two loads on.
        if (!unk_04)
        {
        }
        if (!unk_04)
        {
        }
        if (lv_10.test(slot_C))
        {
            // A compiled-out check (docs/toolchain.md): the registers after
            // it are one load on.
            if (!unk_04)
            {
            }
            if (!unk_4F6B00[slot_C].get_unk_130())
            {
                m_18 = dword_4F8288.sub_1C2A90(slot_C);
                if (m_18 == 2)
                    bp_8++;
                if (m_18 == 4)
                    bp_4++;
            }
        }
    }
    ebp_14 = 0;
    if (bp_8 > 0)
        ebp_14++;
    if (bp_4 > 0)
        ebp_14++;
    return ebp_14;
}

// Whether the round ends early: with the settings' unk_04, a lone team or
// player left, the objectives done (search and destroy) or a win told; and
// by game type, the objectives done (8) or the score limit (unk_18) reached
// by the leading player (1) or a team (2, 4).
// match: ?sub_1B6770@type_4FB9E0@@QAEHXZ @ 0x001B6770
// match: __ehhandler$?sub_1B6770@type_4FB9E0@@QAEHXZ-0x8 @ 0x00302CD0
// match: __ehhandler$?sub_1B6770@type_4FB9E0@@QAEHXZ @ 0x00302CD8
RwInt32 type_4FB9E0::sub_1B6770()
{
    RwUInt32 ebp_14;
    type_3E1E3C *lv_10 = &unk_4F7EB8.unk_04;

    if (!lv_10)
        return 0;
    if (unk_08.unk_04)
    {
        ebp_14 = sub_1B6650();
        if (ebp_14 > (RwUInt32)unk_118)
            unk_118 = ebp_14;
        if (unk_08.unk_00 == 8 && unk_E8)
            return 1;
        if (!sub_1B6580() && unk_04 != 1)
            return 1;
        if (unk_EC)
            return 1;
    }
    switch (unk_08.unk_00)
    {
    case 8:
        return unk_E8;
    case 1:
        {
            if (!unk_08.unk_18)
                return 0;
            RwInt32 q28;
            std::vector<RwUInt32> frm_24;

            lv_10->sub_1B3480(frm_24);
            if (frm_24.size() < 0)
                return 0;
            q28 = lv_10->sub_1B3360(frm_24[0]);
            if (q28 >= unk_08.unk_18)
                return 1;
        }
        break;
    case 2:
    case 4:
        if (!unk_08.unk_18)
            return 0;
        if (lv_10->sub_1B33C0(2) >= unk_08.unk_18)
            return 1;
        if (lv_10->sub_1B33C0(4) >= unk_08.unk_18)
            return 1;
        break;
    }
    return 0;
}

// The host's round end arrives (a client's): state 3 while in game.
// match: ?sub_1B69B0@type_4FB9E0@@QAEXXZ @ 0x001B69B0
void type_4FB9E0::sub_1B69B0()
{
    if (CODFH_DEBUG_LOGS)
        off_42CD14("(CLIENT) Receive round end notify\n");
    unk_B8 = 1;
    unk_E0 = 0;
    unk_E4 = 0;
    if (unk_04 == 1)
    {
        sub_1B4CF0(3);
        unk_4F7EB8.sub_1AB400(2);
        sub_1C4960();
        sub_124EE0(0.5f, 0);
    }
}

// match: ?sub_1B6A30@type_4FB9E0@@QAEXABUtype_3E1044@@@Z @ 0x001B6A30
void type_4FB9E0::sub_1B6A30(const type_3E1044 &arg_0)
{
    sub_1B6A50();
}

// match: ?sub_1B6A50@type_4FB9E0@@QAEXXZ @ 0x001B6A50
void type_4FB9E0::sub_1B6A50()
{
    if (!unk_C4)
    {
        if (unk_04 == 1)
        {
            sub_1252E0(sub_1B4510, 1);
            sub_124EE0(0.5f, 1);
        }
        unk_C4 = 1;
    }
}

// The host's game over arrives (a client's).
// match: ?sub_1B6AA0@type_4FB9E0@@QAEXXZ @ 0x001B6AA0
void type_4FB9E0::sub_1B6AA0()
{
    if (CODFH_DEBUG_LOGS)
        off_42CD14("(CLIENT) Receive round end notify\n");
    unk_E0 = 0;
    unk_E4 = 0;
    if (unk_04 == 1)
    {
        sub_1B4CF0(3);
        unk_4F7EB8.sub_1AB400(2);
        sub_1C49A0();
        sub_124EE0(0.5f, 0);
    }
    else if (unk_04 == 3)
        unk_E0 = 1;
}

// match: ?sub_1B6B30@type_4FB9E0@@QAEXABUtype_3E0EB8@@@Z @ 0x001B6B30
void type_4FB9E0::sub_1B6B30(const type_3E0EB8 &arg_0)
{
    sub_1B6B50();
}

// match: ?sub_1B6B50@type_4FB9E0@@QAEXXZ @ 0x001B6B50
void type_4FB9E0::sub_1B6B50()
{
    if (!unk_C8)
    {
        if (unk_04 == 1)
        {
            sub_1252E0(sub_1B4520, 1);
            sub_124EE0(0.5f, 1);
        }
        else if (unk_04 == 3)
            sub_1B6AA0();
        unk_C8 = 1;
    }
}

// match: ?sub_1B6BB0@type_4FB9E0@@QAEHXZ @ 0x001B6BB0
RwInt32 type_4FB9E0::sub_1B6BB0()
{
    type_4F8054 *var_4;

    // Two compiled-out checks (docs/toolchain.md): the registers after them
    // are two loads on.
    if (!unk_04)
    {
    }
    if (!unk_04)
    {
    }
    var_4 = dword_4F8054;
    // A compiled-out check (docs/toolchain.md): the registers after it
    // are one load on.
    if (!unk_04)
    {
    }
    if (unk_B8 && var_4->get_unk_04() == 5)
        unk_4F7EB8.sub_1AF750(sub_1CCA10(), 1, 1);
    else
    {
        if (CODFH_DEBUG_LOGS)
            off_42CD14("(CLIENT) Load level message received from host\n");
        return 1;
    }
    return 0;
}

// The wait for the clients at a game's end starts (once).
// match: ?sub_1B6C20@type_4FB9E0@@QAEXXZ @ 0x001B6C20
void type_4FB9E0::sub_1B6C20()
{
    if (!unk_D4)
    {
        type_4F8054 *var_4 = dword_4F8054;

        // A compiled-out check (docs/toolchain.md): the registers after it
        // are one load on.
        if (!unk_04)
        {
        }
        unk_D0 = sub_1CCA10().ref_unk_00() * 0.001f;
        unk_CC = 0;
        unk_D4 = 1;
    }
}

// match: ?sub_1B6C80@type_4FB9E0@@QAEXXZ @ 0x001B6C80
void type_4FB9E0::sub_1B6C80()
{
    type_4F8054 *var_4 = dword_4F8054;

    // A compiled-out check (docs/toolchain.md): the registers after it
    // are one load on.
    if (!unk_04)
    {
    }
    unk_CC = sub_1CCA10().ref_unk_00() * 0.001f - unk_D0 + unk_CC;
    unk_D0 = sub_1CCA10().ref_unk_00() * 0.001f;
}

// Whether the game may end: every client gone, or five seconds waited.
// match: ?sub_1B6CF0@type_4FB9E0@@QAEHXZ @ 0x001B6CF0
RwInt32 type_4FB9E0::sub_1B6CF0()
{
    // The locals' names state their slots (docs/toolchain.md).
    type_1DDE20_mask bp_8;
    type_4F8054 *bp_4;

    // Two compiled-out checks (docs/toolchain.md): the registers after
    // them are two loads on.
    if (!unk_04)
    {
    }
    if (!unk_04)
    {
    }
    bp_4 = dword_4F8054;
    // A compiled-out check (docs/toolchain.md): the registers after it are
    // one load on.
    if (!unk_04)
    {
    }
    sub_1B6C80();
    bp_8 = bp_4->get_unk_B0()->sub_1A8050();
    if (unk_CC >= flt_3E20D8 || bp_4->get_unk_04() != 2 || bp_8.empty())
    {
        if (CODFH_DEBUG_LOGS)
            off_42CD14("(HOST) All clients have quit the game or the wait timer ran out, so end the net game\n");
        return 1;
    }
    return 0;
}

// match: ?sub_1B6D80@type_4FB9E0@@QAEMXZ @ 0x001B6D80
RwReal type_4FB9E0::sub_1B6D80()
{
    return unk_C0;
}

// match: ?sub_1B6DA0@type_4FB9E0@@QAEMXZ @ 0x001B6DA0
RwReal type_4FB9E0::sub_1B6DA0()
{
    RwReal var_4 = (RwDouble)unk_08.unk_14 - unk_C0;

    if (var_4 < 0.0f)
        var_4 = 0;
    return var_4;
}

// match: ?sub_1B6DE0@type_4FB9E0@@QAEXM@Z @ 0x001B6DE0
void type_4FB9E0::sub_1B6DE0(RwReal arg_0)
{
    unk_110 = arg_0;
}

// match: ?sub_1B6E00@type_4FB9E0@@QAEXM@Z @ 0x001B6E00
void type_4FB9E0::sub_1B6E00(RwReal arg_0)
{
    unk_110 -= arg_0;
    if (unk_110 < 0.0f)
        unk_110 = 0;
}

// match: ?sub_1B6E50@type_4FB9E0@@QAEHXZ @ 0x001B6E50
RwInt32 type_4FB9E0::sub_1B6E50()
{
    if (unk_110 > 0.0f)
        return 1;
    return 0;
}

// match: ?sub_1B6E80@type_4FB9E0@@QAEMXZ @ 0x001B6E80
RwReal type_4FB9E0::sub_1B6E80()
{
    return unk_110;
}

// The game ends (the multiplayer manager's step): state 3, the view, the
// end screen (sub_1C49E0).
// match: ?sub_1B6EA0@type_4FB9E0@@QAEXXZ @ 0x001B6EA0
void type_4FB9E0::sub_1B6EA0()
{
    sub_1B4CF0(3);
    unk_4F7EB8.sub_1AB400(2);
    unk_E0 = 0;
    unk_E4 = 0;
    sub_1C49E0();
    unk_C8 = 1;
}

// The host's word unk_114 set to arg_0; clearing it sends the kick message
// (unk_04 0) to the other peers.
// match: ?sub_1B6EF0@type_4FB9E0@@QAEXI@Z @ 0x001B6EF0
void type_4FB9E0::sub_1B6EF0(RwUInt32 arg_0)
{
    // The locals' names state their slots (docs/toolchain.md).
    if (unk_114 && !arg_0 && !unk_4F61F8.unk_104 && type_4F8054::get())
    {
        type_1DDE20_mask bp_4 = type_4F8054::get()->get_unk_B0()->sub_1A8050();
        type_3E10BC rC;

        rC.unk_04 = 0;
        type_4F8058::get()->sub_1DDDB0(&rC, bp_4);
    }
    unk_114 = arg_0;
}

// A client waits for the host's level load message, then takes its
// settings unless it is still waiting (unk_B8).
// match: ?sub_1B6F90@@YAXXZ @ 0x001B6F90
void sub_1B6F90()
{
    if (unk_4F61F8.unk_104)
    {
        if (CODFH_DEBUG_LOGS)
            off_42CD14("(CLIENT) waiting for level load directive\n");
        while (!dword_4FB9E0.sub_1B6BB0())
        {
        }
        if (!dword_4FB9E0.sub_1F5840())
            dword_4FB9E0.sub_1B5690();
    }
}

// Members /OPT:ICF folded into shared trivial bodies (config/aliases.txt): defined here for
// the authentic link (PLAN M7); the placement link takes the shared bodies.

// ?pDtor@type_4FB9E0@@QAEXXZ (folded into the empty body at 0x1E41C0)
void type_4FB9E0::pDtor()
{
}

// ?sub_1E4CB0@type_4FB9E0@@QAEHXZ (folded into `return 0` at 0x1E4CB0)
RwInt32 type_4FB9E0::sub_1E4CB0()
{
    return 0;
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??0type_4FB9E0_08@@QAE@XZ (folded into 0x6FCD0)
type_4FB9E0_08::type_4FB9E0_08()
{
    
}

// ??1type_4FB9E0_08@@QAE@XZ (folded into 0x1E41C0)
type_4FB9E0_08::~type_4FB9E0_08()
{
}

// ??1type_4FB9E0_74@@QAE@XZ (folded into 0x1E41C0)
type_4FB9E0_74::~type_4FB9E0_74()
{
}

// ?sub_1F5840@type_4FB9E0@@QAEHXZ (folded into 0x1F5840)
RwInt32 type_4FB9E0::sub_1F5840()
{
    return unk_B8;
}

// ?vf_004@type_3E108C@@UAEXPAUtype_1F8560@@@Z (folded into 0x15FB30)
void type_3E108C::vf_004(struct type_1F8560 *arg_0)
{
}

// ?vf_004@type_3E10A4@@UAEXPAUtype_1F8560@@@Z (folded into 0x15FB30)
void type_3E10A4::vf_004(struct type_1F8560 *arg_0)
{
}


#ifdef CODFH_PLAIN
// Plain builds (tools/plainbuild.py): the variables below are a second name for this unit's
// variables' bytes in the image (tools/session/overlapvars.py --aliases); only the placement
// link gives them one storage, so any other link binds them here at the image offset.
// (bound at start-up: the library initialization area runs before every game constructor)
#pragma warning(disable: 4073)
#pragma init_seg(lib)
// 0x004FB9F8: dword_4FB9E0 + 0x18
RwInt32 &dword_4FB9F8 = *(RwInt32 *)((RwUInt8 *)&dword_4FB9E0 + 0x18);
// 0x004FBA18: dword_4FB9E0 + 0x38
RwInt32 &dword_4FBA18 = *(RwInt32 *)((RwUInt8 *)&dword_4FB9E0 + 0x38);
// 0x004FBA9C: dword_4FB9E0 + 0xBC
RwInt32 &dword_4FBA9C = *(RwInt32 *)((RwUInt8 *)&dword_4FB9E0 + 0xBC);
// 0x004FBAA4: dword_4FB9E0 + 0xC4
RwInt32 &dword_4FBAA4 = *(RwInt32 *)((RwUInt8 *)&dword_4FB9E0 + 0xC4);
// 0x004FBAA8: dword_4FB9E0 + 0xC8
RwInt32 &dword_4FBAA8 = *(RwInt32 *)((RwUInt8 *)&dword_4FB9E0 + 0xC8);
#endif
