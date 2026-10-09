/*
 * The instant action's results (in-game menu 3, game/livemenu.h): the
 * search started with the game type picked, the sessions found scored and
 * sorted, the one shown stepped on, and the pages shown while searching,
 * after a failed join and when nothing is found.
 */
#include <stdio.h>
#include "game/liveservice.h"
#include "game/livemenu.h"
#include "game/loc.h"
#include "game/mpgame.h"
#include "game/uiglue.h"
#include "types/type_505188.h"
#include "game/ingamemenu.h"
#include "game/gameloop.h"
#include "types/cXboxLive.h"
#include "types/type_DC400.h"
#include "game/kujuui.h"

// Its data definitions (PLAN M5), in the image's address order.
#ifndef CODFH_SP // MP only: unreferenced constants single player does not emit (not in default.xbe; /O2 keeps them only while they are external)
// 0x003E88E4
extern const RwReal flt_3E88E4 = 0.01f;
// 0x003E88E8
extern const RwReal flt_3E88E8 = 0.01f;
// 0x003E88EC
extern const RwReal flt_3E88EC = 16.666666f;
#endif
// 0x0042D294
RwInt32 dword_42D294 = -1;
// End of its data definitions.


using namespace kujuUI;

// match: ??Mtype_207140@@QBE_NABU0@@Z @ 0x00207140
bool type_207140::operator<(const type_207140 &arg_0) const
{
    return unk_04 > arg_0.unk_04;
}

// match: ??0type_207160@@QAE@XZ @ 0x00207160
// match: __ehhandler$??0type_207160@@QAE@XZ-0xCC @ 0x00305BF0
// match: __ehhandler$??0type_207160@@QAE@XZ @ 0x00305CBC

type_207160::type_207160()
    : type_2049D0("InstantActionDetails.layout", 0, true), unk_188("Searching.layout", 0, true),
      unk_310("JoinFailed.layout", 0, true), unk_498("NoSessionsFound.layout", 0, false),
      unk_648(this, &type_207160::sub_207D10), unk_654(this, &type_207160::sub_207E30),
      unk_660(this, &type_207160::sub_208400), unk_66C(this, &type_207160::sub_207D90),
      unk_678(this, &type_207160::sub_208A00), unk_684(this, &type_207160::sub_208A50), unk_714(0),
      unk_724(unk_718.end()), unk_872C(0)
{
    sub_204FC0("Back", &unk_648);
    sub_204FC0("Join", &unk_654);
    sub_204FC0("Next", &unk_660);
    sub_204FC0("Details", &unk_620);
    unk_310.sub_204FC0("Reason", &unk_690);
    unk_310.sub_204FC0("FailHeader", &unk_6B8);
    unk_310.sub_204FC0("Back", &unk_66C);
    unk_188.sub_204FC0("SearchText", &unk_6E0);
    unk_188.sub_204FC0("Back", &unk_648);
    unk_498.sub_204FC0("Create", &unk_678);
    unk_498.sub_204FC0("Back", &unk_684);
    unk_310.sub_20EA40();
    unk_188.sub_20EA40();
}

// match: ??_Gtype_207160@@UAEPAXI@Z @ 0x002074A0
// match: ??1type_207160@@UAE@XZ @ 0x002074D0
// match: __ehhandler$??1type_207160@@UAE@XZ-0xBE @ 0x00305CD0
// match: __ehhandler$??1type_207160@@UAE@XZ @ 0x00305D8E
type_207160::~type_207160()
{
}

// match: ?sub_207650@type_207160@@QAEXXZ @ 0x00207650
void type_207160::sub_207650()
{
    unk_718.clear();
    unk_724 = unk_718.end();
}

// match: ?vf_03C@type_207160@@UAEXXZ @ 0x00207690
void type_207160::vf_03C()
{
    type_2049D0::vf_03C();
    unk_4F7E9C.sub_1CB790();
    unk_8728 = false;
    unk_872C = 0;
}

// match: ?vf_040@type_207160@@UAEXXZ @ 0x002076D0
void type_207160::vf_040()
{
    if (unk_714)
        unk_4F7EB8.get_unk_19C_direct()->vf_07C();
    sub_207650();
    unk_8728 = false;
}

// match: ?sub_207720@type_207160@@QAEXXZ @ 0x00207720
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_207160::sub_207720()
{
    RwInt32 var_44 = 0;
    RwInt32 var_40 = 0;
    RwInt32 stk_3C = 0;
    RwInt32 ebp_38 = 0;

    unk_724 = unk_718.end();
    unk_70D[0] = var_44;
    unk_70D[1] = var_40;
    unk_70D[2] = stk_3C;
    unk_70D[3] = ebp_38;
    unk_712 = word_4F62F8;
    unk_708 = sub_1C42E0();
    unk_70C = 1;
    type_4F8054_4C var_34;
    var_34.unk_00[0] = dword_42D294;
    var_34.unk_00[1] = -1;
    var_34.unk_00[2] = -1;
    var_34.unk_00[3] = -1;
    var_34.unk_10 = -1;
    var_34.unk_14 = -1;
    var_34.unk_18 = -1;
    var_34.unk_2C = 0;
    var_34.unk_1C = 0;
    if (var_34.unk_00[0] == 0x20)
        var_34.unk_00[0] = -1;
    if (sub_204EA0())
    {
        unk_4F7EB8.get_unk_19C_direct()->vf_070((const type_1CC1F0 *)&unk_708, &var_34, (RwInt32)unk_728, 0x8000);
        unk_714 = 1;
    }
    else
        sub_207D10();
}

// match: ?sub_207880@type_207160@@QAEXXZ @ 0x00207880
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_207160::sub_207880()
{
    type_207140 var_28;
    RwInt32 var_20;
    type_1D9270_session *l1C;
    type_1D9270_session *m_18;
    RwUInt32 ebp_14;
    type_1D9270_session *lv_10;
    RwInt32 var_C;
    RwUInt32 bp_8;
    RwInt32 bp_4;

    var_C = 1000000;
    bp_4 = -1000000;
    sub_207650();
    m_18 = (type_1D9270_session *)unk_4F7EB8.get_unk_19C_direct()->vf_078((RwInt32)&ebp_14);
    if (ebp_14 > 0)
    {
        for (bp_8 = 0; bp_8 < ebp_14; bp_8++)
        {
            l1C = m_18;
            lv_10 = &l1C[bp_8];
            if (lv_10 && lv_10->unk_34)
            {
                var_28.unk_00 = lv_10;
                var_28.unk_04 = 0;
                unk_718.push_back(var_28);
                var_20 = lv_10->unk_30.unk_00;
                var_C = var_20 < var_C ? var_20 : var_C;
                bp_4 = var_20 > bp_4 ? var_20 : bp_4;
            }
        }
        for (std::list<type_207140>::iterator var_2C = unk_718.begin(); var_2C != unk_718.end(); ++var_2C)
        {
            type_207140 *var_30 = &*var_2C;
            var_30->unk_04 = sub_207A40(var_30->unk_00, var_C, bp_4);
        }
        unk_718.sort();
        unk_724 = unk_718.begin();
    }
}

// match: ?sub_207A40@type_207160@@SAHPAUtype_1D9270_session@@HH@Z @ 0x00207A40
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_207160::sub_207A40(type_1D9270_session *arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    RwInt32 l4 = 0;

    if (arg_0->unk_29 >= arg_0->unk_2A * 3U / 4)
        l4 += 15;
    else if (arg_0->unk_29 >= arg_0->unk_2A / 2U)
        l4 += 10;
    RwInt32 var_8 = arg_8 - arg_4;
    if (var_8 > 0 && var_8 < 5000)
    {
        RwInt32 var_10 = arg_0->unk_30.unk_00;
        RwInt32 var_C = (var_10 - arg_4) * 20 / var_8 - 10;
        l4 -= var_C;
    }
    return l4;
}

// The session's details: its game type, its level and its players.
// match: ?sub_207AE0@type_207160@@QAEXXZ @ 0x00207AE0
// match: __ehhandler$?sub_207AE0@type_207160@@QAEXXZ-0x23 @ 0x00305DA0
// match: __ehhandler$?sub_207AE0@type_207160@@QAEXXZ @ 0x00305DC3
void type_207160::sub_207AE0()
{
    RwInt32 lv_10 = 0;

    if (!unk_718.empty())
    {
        type_1D9270_session *lv_14 = unk_724->unk_00;

        if (sub_2089A0())
        {
            RwChar lv_3C[8];
            type_1CB670 lv_34(sub_1A3C10(lv_14->unk_2B), 0);

            add_text(lv_34, *sub_1CB9B0());
            add_text(lv_34, type_1CB670(sub_1C4590(lv_14->unk_28), 0));
            add_text(lv_34, *sub_1CB9B0());
            add_text(lv_34, type_1CB670("Players:", 0));
            sprintf(lv_3C, "  %u/%u", lv_14->unk_29, lv_14->unk_2A);
            add_text(lv_34, sub_1CB720(lv_3C));
            unk_620.sub_1F28C0(lv_34);
        }
    }
    else
        sub_1E7CF0()->sub_1E7D30(&unk_498);
}

// match: ?sub_207D10@type_207160@@QAEXXZ @ 0x00207D10
void type_207160::sub_207D10()
{
    type_1E7CF0 *var_4 = sub_1E7CF0();

    if (var_4->sub_1E7D00(&unk_188))
        var_4->sub_1E7D90(&unk_188);
    if (var_4->sub_1E7D00(&unk_310))
        var_4->sub_1E7D90(&unk_310);
    sub_1FC310()->sub_1FBDA0(sub_2046C0(2));
}

// match: ?sub_207D90@type_207160@@QAEXXZ @ 0x00207D90
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_207160::sub_207D90()
{
    if (unk_8728)
    {
        unk_8728 = false;
        type_4F8054 *var_C = dword_4F8054;
        type_4F8054_B0 *bp_8 = var_C->unk_B0;
        if (!var_C || !bp_8)
            return;
        bp_8->sub_1CD370();
        var_C->setError(7, 9);
    }
    type_1E7CF0 *var_4 = sub_1E7CF0();
    if (var_4->sub_1E7D00(&unk_310))
    {
        var_4->sub_1E7D90(&unk_310);
        sub_207D10();
    }
}

// The join: the session a friend's invite names when there is one, else
// the one shown; the join failure page tells why a join failed.
// match: ?sub_207E30@type_207160@@QAEXXZ @ 0x00207E30
// match: __ehhandler$?sub_207E30@type_207160@@QAEXXZ-0x65 @ 0x00305DD0
// match: __ehhandler$?sub_207E30@type_207160@@QAEXXZ @ 0x00305E35
void type_207160::sub_207E30()
{
    RwInt32 lv_14 = 0;
    bool lv_D = false;

    if (((kujuUI::type_1EE900 *)sub_227560())->sub_1EE9D0())
    {
        unk_70D[0] = 0;
        unk_70D[1] = 0;
        unk_70D[2] = 0;
        unk_70D[3] = 0;
        unk_712 = word_4F62F8;
        unk_708 = sub_1C42E0();
        unk_70C = 1;
        sub_227560()->unk_00 = 0;
        sub_1C3D80(sub_227560()->unk_04.unk_28);
        sub_1E7CF0()->sub_1E7D30(&unk_310);
        unk_6B8.sub_1F28C0(type_1CB670("Joining", 0));
        unk_690.sub_1F28C0(type_1CB670());
        unk_8728 = true;
        lv_D = unk_4F7EB8.sub_1A9CE0((const type_1CC1F0 *)&unk_708, (const type_1CC3C0 *)&sub_227560()->unk_04,
                                     &lv_14, true);
    }
    else if (sub_2089A0())
    {
        type_1D9270_session *lv_18 = unk_724->unk_00;
        sub_1C3D80(lv_18->unk_28);
        sub_1E7CF0()->sub_1E7D30(&unk_310);
        unk_6B8.sub_1F28C0(type_1CB670("Joining", 0));
        unk_690.sub_1F28C0(type_1CB670());
        unk_8728 = true;
        lv_D = unk_4F7EB8.sub_1A9CE0((const type_1CC1F0 *)&unk_708, (const type_1CC3C0 *)lv_18, &lv_14, false);
    }
    else
    {
        unk_8728 = false;
        return;
    }
    if (lv_D)
    {
        sub_1E7CF0()->sub_1E7D90(&unk_310);
        sub_1FC310()->sub_1FBE20();
    }
    else if (sub_204EA0() && lv_14 != 9)
    {
        unk_6B8.sub_1F28C0(type_1CB670("Join Failed", 0));
        switch (lv_14)
        {
        case 1:
            unk_690.sub_1F28C0(type_1CB670("Game session is full", 0));
            break;
        case 3:
            unk_690.sub_1F28C0(type_1CB670("PEER_CONNECTION_FAILED", 0));
            break;
        case 2:
            unk_690.sub_1F28C0(type_1CB670("Blocked from game session", 0));
            break;
        case 4:
            unk_690.sub_1F28C0(type_1CB670("SERVER_CONNECTION_FAILED", 0));
            break;
        default:
            unk_690.sub_1F28C0(type_1CB670("UNEXPECTED_CONNECTION_FAILURE", 0));
            break;
        }
    }
    unk_8728 = false;
}

// match: ?sub_208400@type_207160@@QAEXXZ @ 0x00208400
void type_207160::sub_208400()
{
    if (!unk_718.empty())
    {
        ++unk_724;
        if (unk_724 == unk_718.end())
            unk_724 = unk_718.begin();
        sub_207AE0();
    }
}

// The update: back to the multiplayer menu when neither the system link
// nor the voice runs; else the search's steps (the invite's join, or the
// search started, on the third update), the joining and searching texts,
// and the sessions found shown once the search ends.
// match: ?vf_014@type_207160@@UAEXM@Z @ 0x002084A0
// match: __ehhandler$?vf_014@type_207160@@UAEXM@Z-0x36 @ 0x00305E40
// match: __ehhandler$?vf_014@type_207160@@UAEXM@Z @ 0x00305E76
void type_207160::vf_014(RwReal arg_0)
{
    type_2049D0::vf_014(arg_0);
    if (!sub_1D8810()->is_system_link() && !sub_1D8810()->voice_running())
    {
        sub_207D90();
        sub_1FC310()->sub_1FBE20();
        sub_1FC310()->sub_1FBDA0(sub_2046C0(13));
    }
    else
    {
        if (((kujuUI::type_1EE900 *)sub_227560())->sub_1EE9D0())
        {
            switch (unk_872C)
            {
            case 0:
                unk_872C = 1;
                break;
            case 1:
                unk_872C = 2;
                break;
            case 2:
                unk_872C = 3;
                sub_207E30();
                break;
            }
        }
        else
        {
            switch (unk_872C)
            {
            case 0:
                if (!sub_1E7CF0()->sub_1E7D00(&unk_188))
                    sub_1E7CF0()->sub_1E7D30(&unk_188);
                unk_6E0.sub_1F28C0(sub_20EB30(type_1CB670("Searching...", 0), arg_0 * 2));
                unk_872C = 1;
                break;
            case 1:
                unk_872C = 2;
                break;
            case 2:
                unk_872C = 3;
                sub_207720();
                break;
            }
        }
        if (unk_8728)
        {
            unk_6B8.sub_1F28C0(sub_20EB30(type_1CB670("Joining", 0), arg_0));
            unk_690.sub_1F28C0(unk_4F7E9C);
        }
        if (unk_714)
        {
            if (!sub_1E7CF0()->sub_1E7D00(&unk_188))
                sub_1E7CF0()->sub_1E7D30(&unk_188);
            unk_6E0.sub_1F28C0(sub_20EB30(type_1CB670("Searching...", 0), arg_0 * 2));
            if (unk_4F7EB8.get_unk_19C_direct()->vf_074())
            {
                sub_207880();
                sub_207AE0();
                sub_1E7CF0()->sub_1E7D90(&unk_188);
                unk_4F7EB8.get_unk_19C_direct()->vf_07C();
                unk_714 = 0;
            }
            unk_4F7EB8.sub_1AF750((RwInt32)arg_0, 1, 0);
        }
    }
}

// The game type the instant action searches with.
// match: ?sub_208990@@YAXH@Z @ 0x00208990
void sub_208990(RwInt32 arg_0)
{
    dword_42D294 = arg_0;
}

// match: ?sub_2089A0@type_207160@@QAE_NXZ @ 0x002089A0
bool type_207160::sub_2089A0()
{
    return !unk_718.empty() && !(unk_718.end() == unk_724);
}

// match: ?sub_208A00@type_207160@@QAEXXZ @ 0x00208A00
void type_207160::sub_208A00()
{
    sub_1E7CF0()->sub_1E7D90(&unk_498);
    type_2053C0::sub_205BF0(2);
    sub_1FC310()->sub_1FBDA0(sub_2046C0(0));
}

// match: ?sub_208A50@type_207160@@QAEXXZ @ 0x00208A50
void type_207160::sub_208A50()
{
    sub_1E7CF0()->sub_1E7D90(&unk_498);
    sub_207D10();
}

// The results list's and the actions' instances.
// The results list's size check (std::list's, throwing length_error).
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3E88E4@@3MB @ 0x003E88E4
// match: ?flt_3E88E8@@3MB @ 0x003E88E8
// match: ?flt_3E88EC@@3MB @ 0x003E88EC
// match: ??_C@_0L@GJKEAJGH@SearchText?$AA@ @ 0x003E88F0
// match: ??_C@_0L@IPPKPJBL@FailHeader?$AA@ @ 0x003E88FC
// match: ??_C@_06OLMNNNEN@Reason?$AA@ @ 0x003E8908
// match: ??_C@_07NJJEDOBB@Details?$AA@ @ 0x003E8910
// match: ??_C@_04MDFHGMOB@Next?$AA@ @ 0x003E8918
// match: ??_C@_04PEKDBJNJ@Join?$AA@ @ 0x003E8920
// match: ??_C@_0BH@LECDGFMB@NoSessionsFound?4layout?$AA@ @ 0x003E8928
// match: ??_C@_0BC@JADKDEIH@JoinFailed?4layout?$AA@ @ 0x003E8940
// match: ??_C@_0BB@DADPDFOA@Searching?4layout?$AA@ @ 0x003E8954
// match: ??_7type_207160@@6B@ @ 0x003E8968
// match: ??_C@_0BM@ENPDMLFI@InstantActionDetails?4layout?$AA@ @ 0x003E89AC
// match: ??_C@_07FONKDGLG@?5?5?$CFu?1?$CFu?$AA@ @ 0x003E89C8
// match: ??_C@_08OPGJMNB@Players?3?$AA@ @ 0x003E89D0
// match: ??_C@_0BO@KGMCHEGE@UNEXPECTED_CONNECTION_FAILURE?$AA@ @ 0x003E89DC
// match: ??_C@_0BJ@EIFKCNDI@SERVER_CONNECTION_FAILED?$AA@ @ 0x003E89FC
// match: ??_C@_0BK@DJOIHNLN@Blocked?5from?5game?5session?$AA@ @ 0x003E8A18
// match: ??_C@_0BH@LGAEDIBC@PEER_CONNECTION_FAILED?$AA@ @ 0x003E8A34
// match: ??_C@_0BF@OCBKODCE@Game?5session?5is?5full?$AA@ @ 0x003E8A4C
// match: ??_C@_0M@JDFLHFHG@Join?5Failed?$AA@ @ 0x003E8A64
// match: ??_C@_07HIFMPGMC@Joining?$AA@ @ 0x003E8A70
// match: ??_C@_0N@IPMHJFGC@Searching?4?4?4?$AA@ @ 0x003E8A78
// match: ??_7?$type_3E7CE8@Utype_207160@@@kujuUI@@6B@ @ 0x003E8A88
// match: __ehhandler$??0type_207160@@QAE@XZ>1>8 @ 0x00422B58
// match: __ehhandler$??0type_207160@@QAE@XZ>1 @ 0x00422BD0
// match: __ehhandler$??1type_207160@@UAE@XZ>1>8 @ 0x00422BEC
// match: __ehhandler$??1type_207160@@UAE@XZ>1 @ 0x00422C5C
// match: __ehhandler$?sub_207AE0@type_207160@@QAEXXZ>1>8 @ 0x00422C78
// match: __ehhandler$?sub_207AE0@type_207160@@QAEXXZ>1 @ 0x00422C98
// match: __ehhandler$?sub_207E30@type_207160@@QAEXXZ>1>8 @ 0x00422CB4
// match: __ehhandler$?sub_207E30@type_207160@@QAEXXZ>1 @ 0x00422D04
// match: __ehhandler$?vf_014@type_207160@@UAEXM@Z>1>8 @ 0x00422D20
// match: __ehhandler$?vf_014@type_207160@@UAEXM@Z>1 @ 0x00422D50
// match: __ehhandler$?sort@?$list@Utype_207140@@V?$allocator@Utype_207140@@@std@@@std@@QAEXXZ>1>8 @ 0x00422D6C
// match: __ehhandler$?sort@?$list@Utype_207140@@V?$allocator@Utype_207140@@@std@@@std@@QAEXXZ>1 @ 0x00422D7C
// match: __ehhandler$?_Buynode@?$list@Utype_207140@@V?$allocator@Utype_207140@@@std@@@std@@IAEPAU_Node@?$_List_nod@Utype_207140@@V?$allocator@Utype_207140@@@std@@@2@XZ>1>8 @ 0x00422D98
// match: __ehhandler$?_Buynode@?$list@Utype_207140@@V?$allocator@Utype_207140@@@std@@@std@@IAEPAU_Node@?$_List_nod@Utype_207140@@V?$allocator@Utype_207140@@@std@@@2@XZ>1>16>16 @ 0x00422DA8
// match: __ehhandler$?_Buynode@?$list@Utype_207140@@V?$allocator@Utype_207140@@@std@@@std@@IAEPAU_Node@?$_List_nod@Utype_207140@@V?$allocator@Utype_207140@@@std@@@2@XZ>1>16 @ 0x00422DB8
// match: __ehhandler$?_Buynode@?$list@Utype_207140@@V?$allocator@Utype_207140@@@std@@@std@@IAEPAU_Node@?$_List_nod@Utype_207140@@V?$allocator@Utype_207140@@@std@@@2@XZ>1 @ 0x00422DCC
// match: __ehhandler$?_Buynode@?$list@Utype_207140@@V?$allocator@Utype_207140@@@std@@@std@@IAEPAU_Node@?$_List_nod@Utype_207140@@V?$allocator@Utype_207140@@@std@@@2@PAU342@0ABUtype_207140@@@Z>1>8 @ 0x00422DE8
// match: __ehhandler$?_Buynode@?$list@Utype_207140@@V?$allocator@Utype_207140@@@std@@@std@@IAEPAU_Node@?$_List_nod@Utype_207140@@V?$allocator@Utype_207140@@@std@@@2@PAU342@0ABUtype_207140@@@Z>1>16>16 @ 0x00422DF8
// match: __ehhandler$?_Buynode@?$list@Utype_207140@@V?$allocator@Utype_207140@@@std@@@std@@IAEPAU_Node@?$_List_nod@Utype_207140@@V?$allocator@Utype_207140@@@std@@@2@PAU342@0ABUtype_207140@@@Z>1>16 @ 0x00422E08
// match: __ehhandler$?_Buynode@?$list@Utype_207140@@V?$allocator@Utype_207140@@@std@@@std@@IAEPAU_Node@?$_List_nod@Utype_207140@@V?$allocator@Utype_207140@@@std@@@2@PAU342@0ABUtype_207140@@@Z>1 @ 0x00422E1C
// match: __ehhandler$?_Incsize@?$list@Utype_207140@@V?$allocator@Utype_207140@@@std@@@std@@IAEXI@Z>1>8 @ 0x00422E38
// match: __ehhandler$?_Incsize@?$list@Utype_207140@@V?$allocator@Utype_207140@@@std@@@std@@IAEXI@Z>1 @ 0x00422E40
// match: __ehhandler$??$_Insert@Viterator@?$list@Utype_207140@@V?$allocator@Utype_207140@@@std@@@std@@@?$list@Utype_207140@@V?$allocator@Utype_207140@@@std@@@std@@QAEXViterator@01@00Uforward_iterator_tag@1@@Z>1>8 @ 0x00422E5C
// match: __ehhandler$??$_Insert@Viterator@?$list@Utype_207140@@V?$allocator@Utype_207140@@@std@@@std@@@?$list@Utype_207140@@V?$allocator@Utype_207140@@@std@@@std@@QAEXViterator@01@00Uforward_iterator_tag@1@@Z>1>16>16 @ 0x00422E6C
// match: __ehhandler$??$_Insert@Viterator@?$list@Utype_207140@@V?$allocator@Utype_207140@@@std@@@std@@@?$list@Utype_207140@@V?$allocator@Utype_207140@@@std@@@std@@QAEXViterator@01@00Uforward_iterator_tag@1@@Z>1>16 @ 0x00422E7C
// match: __ehhandler$??$_Insert@Viterator@?$list@Utype_207140@@V?$allocator@Utype_207140@@@std@@@std@@@?$list@Utype_207140@@V?$allocator@Utype_207140@@@std@@@std@@QAEXViterator@01@00Uforward_iterator_tag@1@@Z>1 @ 0x00422E90
// match: ?dword_42D294@@3HA @ 0x0042D294

// match: ?_Incsize@?$list@Utype_207140@@V?$allocator@Utype_207140@@@std@@@std@@IAEXI@Z @ 0x00209500
// match: __ehhandler$?_Incsize@?$list@Utype_207140@@V?$allocator@Utype_207140@@@std@@@std@@IAEXI@Z-0x8 @ 0x00305ED0
// match: __ehhandler$?_Incsize@?$list@Utype_207140@@V?$allocator@Utype_207140@@@std@@@std@@IAEXI@Z @ 0x00305ED8
// match: ?sort@?$list@Utype_207140@@V?$allocator@Utype_207140@@@std@@@std@@QAEXXZ @ 0x00208A80
// match: __ehhandler$?sort@?$list@Utype_207140@@V?$allocator@Utype_207140@@@std@@@std@@QAEXXZ-0x1E @ 0x00305E80
// match: __ehhandler$?sort@?$list@Utype_207140@@V?$allocator@Utype_207140@@@std@@@std@@QAEXXZ @ 0x00305E9E
// match: ??0?$list@Utype_207140@@V?$allocator@Utype_207140@@@std@@@std@@QAE@XZ @ 0x00208D10
// match: ??0?$list@Utype_207140@@V?$allocator@Utype_207140@@@std@@@std@@QAE@ABV?$allocator@Utype_207140@@@1@@Z @ 0x00208D40
// match: ?_Insert@?$list@Utype_207140@@V?$allocator@Utype_207140@@@std@@@std@@QAEXViterator@12@ABUtype_207140@@@Z @ 0x00208D70
// match: ?swap@?$list@Utype_207140@@V?$allocator@Utype_207140@@@std@@@std@@QAEXAAV12@@Z @ 0x00208DD0
// match: ?splice@?$list@Utype_207140@@V?$allocator@Utype_207140@@@std@@@std@@QAEXViterator@12@AAV12@0@Z @ 0x00208F20
// match: ?merge@?$list@Utype_207140@@V?$allocator@Utype_207140@@@std@@@std@@QAEXAAV12@@Z @ 0x00208FC0
// match: ?_Buynode@?$list@Utype_207140@@V?$allocator@Utype_207140@@@std@@@std@@IAEPAU_Node@?$_List_nod@Utype_207140@@V?$allocator@Utype_207140@@@std@@@2@XZ @ 0x00209100
// match: __ehhandler$?_Buynode@?$list@Utype_207140@@V?$allocator@Utype_207140@@@std@@@std@@IAEPAU_Node@?$_List_nod@Utype_207140@@V?$allocator@Utype_207140@@@std@@@2@XZ @ 0x00305EB0
// match: ??1?$list@Utype_207140@@V?$allocator@Utype_207140@@@std@@@std@@QAE@XZ @ 0x002091E0
// match: ?splice@?$list@Utype_207140@@V?$allocator@Utype_207140@@@std@@@std@@QAEXViterator@12@AAV12@00@Z @ 0x00209220
// match: ?_Splice@?$list@Utype_207140@@V?$allocator@Utype_207140@@@std@@@std@@QAEXViterator@12@AAV12@00I@Z @ 0x00209350
// match: ?_Buynode@?$list@Utype_207140@@V?$allocator@Utype_207140@@@std@@@std@@IAEPAU_Node@?$_List_nod@Utype_207140@@V?$allocator@Utype_207140@@@std@@@2@PAU342@0ABUtype_207140@@@Z @ 0x00209440
// match: __ehhandler$?_Buynode@?$list@Utype_207140@@V?$allocator@Utype_207140@@@std@@@std@@IAEPAU_Node@?$_List_nod@Utype_207140@@V?$allocator@Utype_207140@@@std@@@2@PAU342@0ABUtype_207140@@@Z @ 0x00305EC0
// match: ?erase@?$list@Utype_207140@@V?$allocator@Utype_207140@@@std@@@std@@QAE?AViterator@12@V312@0@Z @ 0x002095D0
// match: ??0?$type_3E7CE8@Utype_207160@@@kujuUI@@QAE@PAUtype_207160@@P82@AEXXZ@Z @ 0x00209670
// match: ??1?$type_3E7CE8@Utype_207160@@@kujuUI@@UAE@XZ @ 0x002096B0
// match: ??_G?$type_3E7CE8@Utype_207160@@@kujuUI@@UAEPAXI@Z @ 0x002096D0
// match: ??$_Insert@Viterator@?$list@Utype_207140@@V?$allocator@Utype_207140@@@std@@@std@@@?$list@Utype_207140@@V?$allocator@Utype_207140@@@std@@@std@@QAEXViterator@01@00Uforward_iterator_tag@1@@Z @ 0x00209700
// match: __ehhandler$??$_Insert@Viterator@?$list@Utype_207140@@V?$allocator@Utype_207140@@@std@@@std@@@?$list@Utype_207140@@V?$allocator@Utype_207140@@@std@@@std@@QAEXViterator@01@00Uforward_iterator_tag@1@@Z @ 0x00305EF0

// The actions' instances (game/kujuui.h's template, its definitions
// repeated here).
template <class T> type_3E7CE8<T>::type_3E7CE8(T *arg_0, void (T::*arg_4)())
{
    unk_04 = arg_0;
    unk_08 = arg_4;
}

template <class T> type_3E7CE8<T>::~type_3E7CE8()
{
}

template <class T> void type_3E7CE8<T>::pvf_008()
{
    (unk_04->*unk_08)();
}
