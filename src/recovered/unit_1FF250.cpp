/*
 * The in-game screens (game/ingamescreens.h): the pause menu, the controls'
 * legend and the screens over the game, built for the game type, shown,
 * hidden and run a frame at a time. The legend's update (sub_1FFE80)
 * builds its text in a std::string through the library's out-of-line
 * default constructor (sub_E87E0) and is not matched yet
 * (docs/questions.md).
 */
#include "game/liveservice.h"
#include "game/ingamescreens.h"
#include "game/ingamepages.h"
#include "game/data.h"
#include "game/functions.h"
#include "game/gameloop.h"
#include "game/startup.h"
#include "game/uiglue.h"
#include "game/waitscreen.h"
#include "game/livebase.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003E7FFC
extern const RwReal flt_3E7FFC = 0.01f;
// 0x003E8000
extern const RwReal flt_3E8000 = 0.01f;

// match: ?flt_3E7FFC@@3MB @ 0x003E7FFC
// match: ?flt_3E8000@@3MB @ 0x003E8000
// 0x003E8004
extern const RwReal flt_3E8004 = 16.666666f;
// 0x005043BC
type_1FF250 *dword_5043BC;
// 0x005043C0
type_218DD0 *dword_5043C0;
// End of its data definitions.


using namespace kujuUI;

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3E8004@@3MB @ 0x003E8004
// match: ??_C@_0BG@KKBPCMEM@IngameControls?4layout?$AA@ @ 0x003E8008
// match: ??_C@_0BB@EMNOLCLM@PauseMenu?4layout?$AA@ @ 0x003E8020
// match: ??_C@_0BB@EAFDENJA@JoinError?4layout?$AA@ @ 0x003E8034
// match: ??_C@_0BD@HMFCGGJA@ErrorScreen?4layout?$AA@ @ 0x003E8048
// match: ??_C@_0BJ@KCGIFHDA@InitialTeamSelect?4layout?$AA@ @ 0x003E805C
// match: ??_C@_0CA@OFFGCMAO@DisconnectScoreBoardTeam?4layout?$AA@ @ 0x003E8078
// match: ??_C@_0BK@CHKFNBGH@QuitScoreBoardTeam?4layout?$AA@ @ 0x003E8098
// match: ??_C@_0BM@ENAANMDD@KickedScoreBoardTeam?4layout?$AA@ @ 0x003E80B4
// match: ??_C@_0BN@CIDMKCHG@EndGameScoreBoardTeam?4layout?$AA@ @ 0x003E80D0
// match: ??_C@_0BO@MBEBHDIP@EndRoundScoreBoardTeam?4layout?$AA@ @ 0x003E80F0
// match: ??_C@_0BG@CJPEADOG@ScoreBoardTeam?4layout?$AA@ @ 0x003E8110
// match: ??_C@_0CB@FKBGCKOE@DisconnectScoreBoardDeath?4layout@ @ 0x003E8128
// match: ??_C@_0BL@GOLKAAOF@QuitScoreBoardDeath?4layout?$AA@ @ 0x003E814C
// match: ??_C@_0BN@CNGDAAF@KickedScoreBoardDeath?4layout?$AA@ @ 0x003E8168
// match: ??_C@_0CA@IANOLMJE@ScoreBoardContinueOption?4layout?$AA@ @ 0x003E8188
// match: ??_C@_0BM@OFIMAEBC@ScoreBoardQuitOption?4layout?$AA@ @ 0x003E81A8
// match: ??_C@_0BO@EAFLJGE@EndGameScoreBoardDeath?4layout?$AA@ @ 0x003E81C4
// match: ??_C@_0BK@DPMIFMOL@HostEndGameOptions?4layout?$AA@ @ 0x003E81E4
// match: ??_C@_0BP@MAINIOAN@EndRoundScoreBoardDeath?4layout?$AA@ @ 0x003E8200
// match: ??_C@_0BL@NLGDPCNO@HostEndRoundOptions?4layout?$AA@ @ 0x003E8220
// match: ??_C@_0BH@PEALOCIB@ScoreBoardDeath?4layout?$AA@ @ 0x003E823C
// match: ??_C@_0O@PJCODEOL@LEGEND_CHANGE?$AA@ @ 0x003E8254
// match: ??_C@_0M@JJPCKJL@LEGEND_MOVE?$AA@ @ 0x003E8264
// match: ??_C@_0BD@JJMLIDKA@LEGEND_MOVE_CHANGE?$AA@ @ 0x003E8270
// match: ??_C@_0M@OPHOIGGM@LEGEND_BACK?$AA@ @ 0x003E8284
// match: ??_C@_0O@DKFLHODN@CANCEL_BUTTON?$AA@ @ 0x003E8290
// match: ??_C@_02KNHHEEKP@?5?5?$AA@ @ 0x003E82A0
// match: ??_C@_0O@FJCPHDIH@LEGEND_SELECT?$AA@ @ 0x003E82A4
// match: ??_C@_0DA@GAPLBPPB@IngameScreens?5InGameMenuManager?3@ @ 0x003E82B4
// match: ??_C@_0DA@LGFPIIHD@IngameScreens?5InGameMenuManager?3@ @ 0x003E82E4
// match: ??_C@_0BJ@DDEJDAKJ@GAME_SESSION_UNAVAILABLE?$AA@ @ 0x003E8314
// match: __ehhandler$??0type_1FF250@@QAE@XZ>1>8 @ 0x00421FD8
// match: __ehhandler$??0type_1FF250@@QAE@XZ>1 @ 0x00421FF0
// match: __ehhandler$?sub_1FF3F0@type_1FF250@@QAEXXZ>1>8 @ 0x0042200C
// match: __ehhandler$?sub_1FF3F0@type_1FF250@@QAEXXZ>1 @ 0x004220B4
// match: __ehhandler$?sub_1FFE80@type_1FF250@@QAEXXZ>1>8 @ 0x004220D0
// match: __ehhandler$?sub_1FFE80@type_1FF250@@QAEXXZ>1 @ 0x00422128
// match: __ehhandler$?sub_2003E0@type_1FF250@@QAEXM@Z>1>8 @ 0x00422144
// match: __ehhandler$?sub_2003E0@type_1FF250@@QAEXM@Z>1 @ 0x00422154

// match: ?sub_1FF250@@YAPAUtype_1FF250@@XZ @ 0x001FF250

type_1FF250 *sub_1FF250()
{
    return dword_5043BC;
}

// match: ??0type_1FF250@@QAE@XZ @ 0x001FF260
// match: __ehhandler$??0type_1FF250@@QAE@XZ-0x21 @ 0x00304F20
// match: __ehhandler$??0type_1FF250@@QAE@XZ @ 0x00304F41
type_1FF250::type_1FF250()
{
    unk_00 = 0;
    unk_04 = 0;
    unk_08 = 0;
    unk_0C = 0;
    unk_3C = 0;
    unk_40 = 0;
    INGAMESCREENS_CHECK();
    dword_5043BC = this;
    for (RwInt32 var_10 = 0; var_10 < 11; var_10++)
        unk_10[var_10] = 0;
    unk_08 = new type_3E75B8(0);
    unk_00 = new type_21A5E0("PauseMenu.layout");
    dword_5043C0 = new type_218DD0("IngameControls.layout", unk_00);
    ((type_20E850 *)dword_5043C0)->sub_20EA40();
}

// match: ?sub_1FF3F0@type_1FF250@@QAEXXZ @ 0x001FF3F0
// match: __ehhandler$?sub_1FF3F0@type_1FF250@@QAEXXZ-0xFC @ 0x00304F50
// match: __ehhandler$?sub_1FF3F0@type_1FF250@@QAEXXZ @ 0x0030504C
void type_1FF250::sub_1FF3F0()
{
    RwInt32 var_10 = dword_4FB9E0.get_unk_08_00();

    switch (var_10)
    {
    case 1:
        unk_10[0] = (type_1FBDA0_menu *)new type_2207A0(0, "ScoreBoardDeath.layout", 0, unk_00);
        if (sub_1C4BE0())
        {
            unk_10[1] = (type_1FBDA0_menu *)new type_2207A0(1, "EndRoundScoreBoardDeath.layout", "HostEndRoundOptions.layout", unk_00);
            unk_10[2] = (type_1FBDA0_menu *)new type_2207A0(2, "EndGameScoreBoardDeath.layout", "HostEndGameOptions.layout", unk_00);
        }
        else
        {
            unk_10[1] = (type_1FBDA0_menu *)new type_2207A0(1, "EndRoundScoreBoardDeath.layout", "ScoreBoardQuitOption.layout", unk_00);
            unk_10[2] = (type_1FBDA0_menu *)new type_2207A0(2, "EndGameScoreBoardDeath.layout", "ScoreBoardContinueOption.layout", unk_00);
        }
        unk_10[3] = (type_1FBDA0_menu *)new type_2207A0(2, "KickedScoreBoardDeath.layout", "ScoreBoardContinueOption.layout", unk_00);
        unk_10[4] = (type_1FBDA0_menu *)new type_2207A0(2, "QuitScoreBoardDeath.layout", "ScoreBoardContinueOption.layout", unk_00);
        unk_10[5] = (type_1FBDA0_menu *)new type_2207A0(2, "DisconnectScoreBoardDeath.layout", "ScoreBoardContinueOption.layout", unk_00);
        break;
    default:
        unk_10[0] = (type_1FBDA0_menu *)new type_2207A0(0, "ScoreBoardTeam.layout", 0, unk_00);
        if (sub_1C4BE0())
        {
            unk_10[1] = (type_1FBDA0_menu *)new type_2207A0(1, "EndRoundScoreBoardTeam.layout", "HostEndRoundOptions.layout", unk_00);
            unk_10[2] = (type_1FBDA0_menu *)new type_2207A0(2, "EndGameScoreBoardTeam.layout", "HostEndGameOptions.layout", unk_00);
        }
        else
        {
            unk_10[1] = (type_1FBDA0_menu *)new type_2207A0(1, "EndRoundScoreBoardTeam.layout", "ScoreBoardQuitOption.layout", unk_00);
            unk_10[2] = (type_1FBDA0_menu *)new type_2207A0(2, "EndGameScoreBoardTeam.layout", "ScoreBoardContinueOption.layout", unk_00);
        }
        unk_10[3] = (type_1FBDA0_menu *)new type_2207A0(2, "KickedScoreBoardTeam.layout", "ScoreBoardContinueOption.layout", unk_00);
        unk_10[4] = (type_1FBDA0_menu *)new type_2207A0(2, "QuitScoreBoardTeam.layout", "ScoreBoardContinueOption.layout", unk_00);
        unk_10[5] = (type_1FBDA0_menu *)new type_2207A0(2, "DisconnectScoreBoardTeam.layout", "ScoreBoardContinueOption.layout", unk_00);
        break;
    }
    unk_10[6] = (type_1FBDA0_menu *)new type_223280(1, 0);
    unk_10[7] = (type_1FBDA0_menu *)new type_217F40("InitialTeamSelect.layout", 0);
    unk_10[8] = (type_1FBDA0_menu *)new type_216C10("ErrorScreen.layout", 0);
    unk_10[9] = (type_1FBDA0_menu *)new type_216C10("JoinError.layout", 0);
    unk_10[10] = (type_1FBDA0_menu *)new type_215740(0);
}

// match: ?sub_1FFD10@type_1FF250@@QAEXXZ @ 0x001FFD10
void type_1FF250::sub_1FFD10()
{
    for (RwInt32 var_4 = 0; var_4 < 11; var_4++)
        delete unk_10[var_4];
}

// match: ??1type_1FF250@@QAE@XZ @ 0x001FFD70
type_1FF250::~type_1FF250()
{
    INGAMESCREENS_CHECK();
    dword_5043BC = 0;
    if (sub_1E7CF0()->sub_1E7D00(unk_08))
        sub_1E7CF0()->sub_1E7D90(unk_08);
    if (sub_1E7CF0()->sub_1E7D00(unk_00))
        sub_1E7CF0()->sub_1E7D90(unk_00);
    delete unk_08;
    delete unk_00;
    delete dword_5043C0;
    dword_5043C0 = 0;
    sub_1FFD10();
    sub_1C4ED0();
}

// The legend bar's draw: a free inline with no address. Evidence: the
// legend update (sub_1FFE80) is a frame slot short without it.
inline void show_legend(kujuUI::type_1E4130 *arg_0)
{
    dword_5043C0->vf_018(arg_0);
}

// match: ?sub_1FFE80@type_1FF250@@QAEXXZ @ 0x001FFE80
// match: __ehhandler$?sub_1FFE80@type_1FF250@@QAEXXZ-0x79 @ 0x00305060
// match: __ehhandler$?sub_1FFE80@type_1FF250@@QAEXXZ @ 0x003050D9
void type_1FF250::sub_1FFE80()
{
    kujuUI::type_1E4130 local_CC;
    kujuUI::type_3E7D08 *ebp_14;

    ebp_14 = 0;

    if (dword_42926C && sub_188350() != 4 && !get_unk_1120(sub_227560()))
    {
        if (sub_1EF160())
        {
            if (sub_1E7CF0())
                ebp_14 = sub_1E7CF0()->sub_1E7FE0();
            if (!ebp_14)
            {
                sub_21A5E0()->get_shown(ebp_14);
            }
        }
        else if (sub_200780())
        {
            if (sub_1E7CF0())
                ebp_14 = sub_1E7CF0()->sub_1E7FE0();
            if (!ebp_14)
                ebp_14 = sub_1FF250()->sub_200900();
        }
    }
    RwInt32 lv_10 = 0;
    INGAMESCREENS_CHECK();
    if (ebp_14)
    {
        sub_1E7CF0()->vf_018(&local_CC);
        lv_10 = ebp_14->vf_024();
    }
    if (unk_40 != lv_10)
    {
        unk_40 = lv_10;
        type_1CB670 lv_EC;

        if (unk_40 & 2)
        {
            add_text(lv_EC, type_1CB670("LEGEND_SELECT", 0));
            add_text(lv_EC, sub_1CB720("  "));
        }
        if (unk_40 & 4)
        {
            add_text(lv_EC, type_1CB670("CANCEL_BUTTON", 0));
            add_text(lv_EC, sub_1CB720("  "));
        }
        else if (unk_40 & 8)
        {
            add_text(lv_EC, type_1CB670("LEGEND_BACK", 0));
            add_text(lv_EC, sub_1CB720("  "));
        }
        if ((unk_40 & 0x30) == 0x30)
            add_text(lv_EC, type_1CB670("LEGEND_MOVE_CHANGE", 0));
        else if (unk_40 & 0x10)
            add_text(lv_EC, type_1CB670("LEGEND_MOVE", 0));
        else if (unk_40 & 0x20)
            add_text(lv_EC, type_1CB670("LEGEND_CHANGE", 0));
        dword_5043C0->sub_218F20(lv_EC);
    }
    if (unk_40)
        show_legend(&local_CC);
    sub_227560()->sub_227070();
}

// match: ?sub_2003E0@type_1FF250@@QAEXM@Z @ 0x002003E0
// match: __ehhandler$?sub_2003E0@type_1FF250@@QAEXM@Z-0x1C @ 0x003050F0
// match: __ehhandler$?sub_2003E0@type_1FF250@@QAEXM@Z @ 0x0030510C
void type_1FF250::sub_2003E0(RwReal arg_0)
{
    sub_1C40B0(arg_0);
    if (sub_1EF160() || sub_200780())
    {
        type_1E3DB0 *var_10 = sub_1C4EA0();
        INGAMESCREENS_CHECK();
        static type_1EE900 unk_5044CC;
        static type_1E7560 unk_5043C8;

        if (var_10->sub_2015D0())
        {
            type_1EE900 var_1C = var_10->sub_1E3DD0();
            var_1C.sub_1EE940(&unk_5044CC, &unk_5043C8);
            unk_5044CC = var_1C;
        }
        while (unk_5043C8.sub_1E75F0())
        {
            if (sub_227560()->sub_2280E0())
                unk_5043C8.sub_1E7610();
            else
                sub_1E7CF0()->processEvent(unk_5043C8.sub_1E7610());
        }
        sub_1E7CF0()->vf_014(arg_0);
        if (sub_227560()->get_unk_A4() && sub_1EF160() && sub_1FF250()->get_unk_0C() != 9)
            sub_1C4A90("GAME_SESSION_UNAVAILABLE");
    }
    if (dword_42926C == 0 && sub_188350() != 4)
    {
        if (0)
        {
            sub_1C8A30("IngameScreens InGameMenuManager::ShowMenu() %d\n", sub_186D00());
        }
        sub_186E70(4, 0, 0);
    }
    else if (sub_188350() == 4 && dword_42926C != 0)
    {
        if (0)
        {
            sub_1C8A30("IngameScreens InGameMenuManager::KillMenu() %d\n", sub_186D00());
        }
        sub_186F80(4, 1);
    }
}

// match: _$E3 @ 0x0030F050
// (The compiler's exit thunk for sub_2003E0's event queue: it runs the
// queue's destructor.)

// match: ?sub_200630@type_1FF250@@QAEXXZ @ 0x00200630
void type_1FF250::sub_200630()
{
    unk_00->vf_03C();
    sub_1FFD10();
    sub_1FF3F0();
    for (RwUInt32 var_4 = 0; var_4 < 11; var_4++)
    {
        ((type_20E850 *)unk_10[var_4])->sub_20EA40();
        unk_10[var_4]->vf_03C();
    }
}

// match: ?sub_2006A0@type_1FF250@@QAE_N_N@Z @ 0x002006A0
bool type_1FF250::sub_2006A0(bool arg_0)
{
    if (unk_04 != arg_0)
    {
    unk_04 = arg_0;
    if (unk_04)
    {
        sub_1E7CF0()->sub_1E7D30(unk_08);
        unk_00->sub_21C200(0, 0);
        unk_00->vf_008();
    }
    else
    {
        sub_1E7CF0()->sub_1E7D90(unk_08);
        unk_00->sub_21C200(0, 0);
        unk_00->vf_00C();
    }
    return true;
    }
    return false;
}

// match: ?sub_200740@type_1FF250@@QAE_NXZ @ 0x00200740
bool type_1FF250::sub_200740()
{
    return unk_3C || unk_04;
}

// match: ?sub_200780@type_1FF250@@QAE_NXZ @ 0x00200780
bool type_1FF250::sub_200780()
{
    return unk_3C;
}

// match: ?sub_2007A0@type_1FF250@@QAE_N_N@Z @ 0x002007A0
bool type_1FF250::sub_2007A0(bool arg_0)
{
    if (unk_3C != arg_0 && sub_200890(unk_0C))
    {
    unk_3C = arg_0;
    if (unk_3C)
    {
        sub_1E7CF0()->sub_1E7D30(unk_10[unk_0C]);
        unk_10[unk_0C]->vf_008();
    }
    else if (sub_1E7CF0()->sub_1E7D00(unk_10[unk_0C]))
    {
        sub_1E7CF0()->sub_1E7D90(unk_10[unk_0C]);
        unk_10[unk_0C]->vf_00C();
    }
    return true;
    }
    return false;
}

// match: ?sub_200890@type_1FF250@@QAE_NH@Z @ 0x00200890
bool type_1FF250::sub_200890(RwInt32 arg_0)
{
    return unk_10[arg_0] != 0;
}

// match: ?sub_2008B0@type_1FF250@@QAE_NH@Z @ 0x002008B0
bool type_1FF250::sub_2008B0(RwInt32 arg_0)
{
    if (unk_0C != arg_0 && sub_200890(arg_0))
    {
        sub_2007A0(0);
        unk_0C = arg_0;
        return true;
    }
    return false;
}

// match: ?sub_200900@type_1FF250@@QAEPAUtype_1FBDA0_menu@@XZ @ 0x00200900
type_1FBDA0_menu *type_1FF250::sub_200900()
{
    return unk_10[unk_0C];
}

// match: ?sub_200920@type_1FF250@@QAEXXZ @ 0x00200920
void type_1FF250::sub_200920()
{
    if (sub_200780())
        unk_10[unk_0C]->vf_04C();
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?sub_1EF160@type_1FF250@@QAE_NXZ (folded into 0x1EF160)
bool type_1FF250::sub_1EF160()
{
    return unk_04;
}
