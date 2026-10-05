/*
 * The session list page (game/livemenu.h), the base of the in-game menus 7
 * and 9: searching for sessions, listing them sorted in its columns, and
 * joining the one selected.
 */
#include "types/cXboxLive.h"
#include "game/livemenu.h"
#include "game/ingamemenu.h"
#include "game/gameloop.h"
#include "types/type_DC400.h"
#include "game/browser.h"
#include "game/uiglue.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003E9170
extern const RwReal flt_3E9170 = 0.01f;
// 0x003E9174
extern const RwReal flt_3E9174 = 0.01f;
// 0x003E9178
extern const RwReal flt_3E9178 = 16.666666f;
// End of its data definitions.


using namespace kujuUI;

// The this-adjusting thunk the columns' vtable (off_3E91DC) holds for the
// deleting destructor.
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3E9170@@3MB @ 0x003E9170
// match: ?flt_3E9174@@3MB @ 0x003E9174
// match: ?flt_3E9178@@3MB @ 0x003E9178
// match: ??_C@_09DGONONLF@Searching?$AA@ @ 0x003E917C
// match: ??_C@_08GAHMEBAA@SortText?$AA@ @ 0x003E9188
// match: ??_C@_08NIEJBOAC@NextSort?$AA@ @ 0x003E9194
// match: ??_C@_0P@HPLJJKOB@sessionsactive?$AA@ @ 0x003E91A0
// match: ??_C@_07POIENIBA@Refresh?$AA@ @ 0x003E91B0
// match: ??_C@_06FMBNCPDL@Cancel?$AA@ @ 0x003E91B8
// match: ??_C@_0BJ@IAAPDIAN@SearchingForGames?4layout?$AA@ @ 0x003E91C0
// match: ??_7type_20C470@@6Btype_20E4F0@@@ @ 0x003E91DC
// match: ??_7type_20C470@@6Btype_2049D0@@@ @ 0x003E91F8
// match: ?dword_3E9254@?1??sub_20DE80@type_20C470@@QAEXXZ@4QBHB @ 0x003E9254
// match: ??_C@_0O@JPPALMNF@Sorting?5by?5?$CF1?$AA@ @ 0x003E9264
// match: ??_C@_09OINJJDAC@Game?5type?$AA@ @ 0x003E9274
// match: ??_C@_0BC@KOJNFEGL@Number?5of?5players?$AA@ @ 0x003E9280
// match: ??_C@_03NBOPHIOC@Map?$AA@ @ 0x003E9294
// match: ??_7type_20E4F0@@6B@ @ 0x003E9298
// match: ??_7?$type_3E7264@Utype_20C470@@@kujuUI@@6B@ @ 0x003E92B4
// match: ??_7?$type_3E7CE8@Utype_20C470@@@kujuUI@@6B@ @ 0x003E92C4
// match: __ehhandler$??0type_20C470@@QAE@PBD_N@Z>1>8 @ 0x00423358
// match: __ehhandler$??0type_20C470@@QAE@PBD_N@Z>1 @ 0x004233E0
// match: __ehhandler$??1type_20C470@@UAE@XZ>1>8 @ 0x004233FC
// match: __ehhandler$??1type_20C470@@UAE@XZ>1 @ 0x0042347C
// match: __ehhandler$?sub_20CFB0@type_20C470@@QAEXXZ>1>8 @ 0x00423498
// match: __ehhandler$?sub_20CFB0@type_20C470@@QAEXXZ>1 @ 0x004234D8
// match: __ehhandler$?vf_014@type_20C470@@UAEXM@Z>1>8 @ 0x004234F4
// match: __ehhandler$?vf_014@type_20C470@@UAEXM@Z>1 @ 0x00423524
// match: __ehhandler$?sub_20D8D0@type_20C470@@QAEXXZ>1>8 @ 0x00423540
// match: __ehhandler$?sub_20D8D0@type_20C470@@QAEXXZ>1 @ 0x00423558
// match: __ehhandler$?sub_20DC80@type_20C470@@QAEHUtype_1A5EA0@@PBEG@Z>1>8 @ 0x00423574
// match: __ehhandler$?sub_20DC80@type_20C470@@QAEHUtype_1A5EA0@@PBEG@Z>1 @ 0x00423584
// match: __ehhandler$?sub_20E060@type_20C470@@QAEXXZ>1>8 @ 0x004235A0
// match: __ehhandler$?sub_20E060@type_20C470@@QAEXXZ>1 @ 0x004235C8
// match: __ehhandler$?_Buynode@?$list@PAUtype_1FB520@@V?$allocator@PAUtype_1FB520@@@std@@@std@@IAEPAU_Node@?$_List_nod@PAUtype_1FB520@@V?$allocator@PAUtype_1FB520@@@std@@@2@XZ>1>8 @ 0x004235E4
// match: __ehhandler$?_Buynode@?$list@PAUtype_1FB520@@V?$allocator@PAUtype_1FB520@@@std@@@std@@IAEPAU_Node@?$_List_nod@PAUtype_1FB520@@V?$allocator@PAUtype_1FB520@@@std@@@2@XZ>1>16>16 @ 0x004235F4
// match: __ehhandler$?_Buynode@?$list@PAUtype_1FB520@@V?$allocator@PAUtype_1FB520@@@std@@@std@@IAEPAU_Node@?$_List_nod@PAUtype_1FB520@@V?$allocator@PAUtype_1FB520@@@std@@@2@XZ>1>16 @ 0x00423604
// match: __ehhandler$?_Buynode@?$list@PAUtype_1FB520@@V?$allocator@PAUtype_1FB520@@@std@@@std@@IAEPAU_Node@?$_List_nod@PAUtype_1FB520@@V?$allocator@PAUtype_1FB520@@@std@@@2@XZ>1 @ 0x00423618
// match: __ehhandler$?_Buynode@?$list@PAUtype_1FB520@@V?$allocator@PAUtype_1FB520@@@std@@@std@@IAEPAU_Node@?$_List_nod@PAUtype_1FB520@@V?$allocator@PAUtype_1FB520@@@std@@@2@PAU342@0ABQAUtype_1FB520@@@Z>1>8 @ 0x00423634
// match: __ehhandler$?_Buynode@?$list@PAUtype_1FB520@@V?$allocator@PAUtype_1FB520@@@std@@@std@@IAEPAU_Node@?$_List_nod@PAUtype_1FB520@@V?$allocator@PAUtype_1FB520@@@std@@@2@PAU342@0ABQAUtype_1FB520@@@Z>1>16>16 @ 0x00423644
// match: __ehhandler$?_Buynode@?$list@PAUtype_1FB520@@V?$allocator@PAUtype_1FB520@@@std@@@std@@IAEPAU_Node@?$_List_nod@PAUtype_1FB520@@V?$allocator@PAUtype_1FB520@@@std@@@2@PAU342@0ABQAUtype_1FB520@@@Z>1>16 @ 0x00423654
// match: __ehhandler$?_Buynode@?$list@PAUtype_1FB520@@V?$allocator@PAUtype_1FB520@@@std@@@std@@IAEPAU_Node@?$_List_nod@PAUtype_1FB520@@V?$allocator@PAUtype_1FB520@@@std@@@2@PAU342@0ABQAUtype_1FB520@@@Z>1 @ 0x00423668
// match: __ehhandler$?_Incsize@?$list@PAUtype_1FB520@@V?$allocator@PAUtype_1FB520@@@std@@@std@@IAEXI@Z>1>8 @ 0x00423684
// match: __ehhandler$?_Incsize@?$list@PAUtype_1FB520@@V?$allocator@PAUtype_1FB520@@@std@@@std@@IAEXI@Z>1 @ 0x0042368C

// match: ??_Etype_20C470@@WBII@AEPAXI@Z @ 0x0020E840

// The rows' list's members (std::list<type_1FB520 *>).
// match: ?clear@?$list@PAUtype_1FB520@@V?$allocator@PAUtype_1FB520@@@std@@@std@@QAEXXZ @ 0x0020E1A0
// match: ?_Incsize@?$list@PAUtype_1FB520@@V?$allocator@PAUtype_1FB520@@@std@@@std@@IAEXI@Z @ 0x0020E420
// match: __ehhandler$?_Incsize@?$list@PAUtype_1FB520@@V?$allocator@PAUtype_1FB520@@@std@@@std@@IAEXI@Z-0x8 @ 0x00306810
// match: __ehhandler$?_Incsize@?$list@PAUtype_1FB520@@V?$allocator@PAUtype_1FB520@@@std@@@std@@IAEXI@Z @ 0x00306818
// match: ?_Insert@?$list@PAUtype_1FB520@@V?$allocator@PAUtype_1FB520@@@std@@@std@@QAEXViterator@12@ABQAUtype_1FB520@@@Z @ 0x0020E220
// match: ?_Buynode@?$list@PAUtype_1FB520@@V?$allocator@PAUtype_1FB520@@@std@@@std@@IAEPAU_Node@?$_List_nod@PAUtype_1FB520@@V?$allocator@PAUtype_1FB520@@@std@@@2@XZ @ 0x0020E280
// match: __ehhandler$?_Buynode@?$list@PAUtype_1FB520@@V?$allocator@PAUtype_1FB520@@@std@@@std@@IAEPAU_Node@?$_List_nod@PAUtype_1FB520@@V?$allocator@PAUtype_1FB520@@@std@@@2@XZ @ 0x003067F0
// match: ?_Buynode@?$list@PAUtype_1FB520@@V?$allocator@PAUtype_1FB520@@@std@@@std@@IAEPAU_Node@?$_List_nod@PAUtype_1FB520@@V?$allocator@PAUtype_1FB520@@@std@@@2@PAU342@0ABQAUtype_1FB520@@@Z @ 0x0020E360
// match: __ehhandler$?_Buynode@?$list@PAUtype_1FB520@@V?$allocator@PAUtype_1FB520@@@std@@@std@@IAEPAU_Node@?$_List_nod@PAUtype_1FB520@@V?$allocator@PAUtype_1FB520@@@std@@@2@PAU342@0ABQAUtype_1FB520@@@Z @ 0x00306800

// match: ??0type_20C470@@QAE@PBD_N@Z @ 0x0020C470
// match: __ehhandler$??0type_20C470@@QAE@PBD_N@Z-0xE8 @ 0x003064B0
// match: __ehhandler$??0type_20C470@@QAE@PBD_N@Z @ 0x00306598
type_20C470::type_20C470(const RwChar *arg_0, bool arg_4)
    : type_2049D0(arg_0, 0, arg_4), type_20E4F0(4), unk_81A4("NoSessionsFound.layout", 0, arg_4),
      unk_832C("JoinFailed.layout", 0, arg_4), unk_84B4("SearchingForGames.layout", 0, arg_4),
      unk_8640(this, &type_20C470::sub_20CFB0, &type_20C470::sub_20D420),
      unk_8658(this, &type_20C470::sub_20CF20), unk_8668(this, &type_20C470::sub_20D440),
      unk_8678(this, &type_20C470::sub_20CF70), unk_8688(this, &type_20C470::sub_20D470),
      unk_8698(this, &type_20C470::sub_20CB20), unk_86A8(this, &type_20C470::sub_20DE80)
{
    unk_8764 = 0;
    unk_876C = 0;
    sub_204FC0("Cancel", &unk_8658);
    sub_204FC0("Refresh", &unk_8698);
    sub_204FC0("Back", &unk_8658);
    sub_204FC0("sessionsactive", this);
    sub_204FC0("NextSort", &unk_86A8);
    sub_204FC0("SortText", &unk_8730);
    unk_81A4.sub_204FC0("Create", &unk_8668);
    unk_81A4.sub_204FC0("Back", &unk_8678);
    unk_832C.sub_204FC0("Back", &unk_8688);
    unk_832C.sub_204FC0("Reason", &unk_86B8);
    unk_832C.sub_204FC0("FailHeader", &unk_86E0);
    unk_84B4.sub_204FC0("Back", &unk_8658);
    unk_84B4.sub_204FC0("Searching", &unk_8708);
}

// match: ??_Gtype_20C470@@UAEPAXI@Z @ 0x0020C880
// match: ??1type_20C470@@UAE@XZ @ 0x0020C8B0
// match: __ehhandler$??1type_20C470@@UAE@XZ-0xF5 @ 0x003065B0
// match: __ehhandler$??1type_20C470@@UAE@XZ @ 0x003066A5
type_20C470::~type_20C470()
{
}

// match: ?sub_20CA70@type_20C470@@QAEXXZ @ 0x0020CA70
void type_20C470::sub_20CA70()
{
    for (std::list<type_1FB520 *>::iterator var_4 = unk_8758.begin(); var_4 != unk_8758.end(); ++var_4)
        delete *var_4;
    unk_8758.clear();
    type_1ECA30::sub_1E3480()->sub_1EB160();
}

// match: ?sub_20CB20@type_20C470@@QAEXXZ @ 0x0020CB20
void type_20C470::sub_20CB20()
{
    unk_4F7EB8.get_unk_19C_direct()->vf_07C();
    type_1ECA30::sub_1E3480()->sub_1EB160();
    unk_876C = 0;
}

// Starts the search: the session description from the settings copy
// (the server's name and the map), the search's filter (the game type, the
// level, the players (4, 8 or 16), the rules (4 for any) and the name), and
// the network game's search over Xbox Live, else the system link's.
// match: ?sub_20CB70@type_20C470@@QAEXXZ @ 0x0020CB70
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_20C470::sub_20CB70()
{
    RwUInt8 *var_38;
    type_4F8054_4C var_34;

    sub_20CA70();
    RwInt32 local_48[4] = {0, 0, 0, 0};

    unk_19D = local_48[0];
    unk_19E = local_48[1];
    unk_19F = local_48[2];
    unk_1A0 = local_48[3];
    unk_1A2 = word_4F62F8;
    unk_198 = sub_1C42E0();
    unk_19C = vf_044();
    var_34.unk_00[0] = unk_4FDBB0.unk_00;
    var_34.unk_00[1] = unk_4FDBB0.unk_28;
    var_34.unk_00[2] = dword_4F6300;
    var_34.unk_00[3] = dword_4FDAA0;
    var_34.unk_10 = dword_42CBA8;
    var_34.unk_14 = dword_42CBAC;
    var_34.unk_18 = dword_42CBB0;
    var_34.unk_2C = 0;
    var_38 = sub_1C4330();
    strncpy((RwChar *)&var_34.unk_1C, (const RwChar *)var_38, 16);
    var_34.unk_1D[0xE] = 0;
    if (var_34.unk_00[3] == 0)
        var_34.unk_00[3] = -1;
    if (var_34.unk_00[0] == 0x20)
        var_34.unk_00[0] = -1;
    if (var_34.unk_10 == 4)
        var_34.unk_10 = -1;
    else
        var_34.unk_10 = var_34.unk_10 == 2;
    if (var_34.unk_14 == 4)
        var_34.unk_14 = -1;
    else
        var_34.unk_14 = var_34.unk_14 == 2;
    if (var_34.unk_18 == 4)
        var_34.unk_18 = -1;
    else
        var_34.unk_18 = var_34.unk_18 == 2;
    switch (var_34.unk_00[2])
    {
    case 1:
        var_34.unk_00[2] = 4;
        break;
    case 2:
        var_34.unk_00[2] = 8;
        break;
    case 4:
        var_34.unk_00[2] = 16;
        break;
    default:
        var_34.unk_00[2] = -1;
        break;
    }
    if (sub_204EA0())
    {
        unk_4F7EB8.get_unk_19C_direct()->vf_070((const type_1CC1F0 *)&unk_198, &var_34, (RwInt32)unk_1A4, 0x8000);
        unk_8764 = 1;
    }
    else
    {
        sub_20CF20();
    }
    sub_1E41C0();
}

// match: ?vf_038@type_20C470@@UAEXXZ @ 0x0020CD80
void type_20C470::vf_038()
{
    sub_1ECB90(0, 0);
    sub_1ECB90(1, 0);
    sub_1ECB90(2, 0);
    sub_1ECB90(3, 0);
    sub_1ECB60(0, 0xC9);
    sub_1ECB60(1, 0x53);
    sub_1ECB60(2, 0x9D);
    sub_1ECB60(3, 0x4A);
}

// match: ?vf_03C@type_20C470@@UAEXXZ @ 0x0020CE30
void type_20C470::vf_03C()
{
    unk_8768 = false;
    unk_876C = 0;
    sub_1FBB60(0);
    sub_20E060();
    unk_4F7E9C.sub_1CB790();
}

// match: ?vf_040@type_20C470@@UAEXXZ @ 0x0020CE70
void type_20C470::vf_040()
{
    unk_8768 = false;
    unk_4F7EB8.get_unk_19C_direct()->vf_07C();
    sub_20CA70();
    type_1E7CF0 *var_4 = sub_1E7CF0();

    if (var_4->sub_1E7D00(&unk_832C))
        var_4->sub_1E7D90(&unk_832C);
}

// match: ?pvf_010@type_20C470@@UAEXXZ @ 0x0020CEE0
void type_20C470::pvf_010()
{
    sub_20CFB0();
}

// match: ?pvf_014@type_20C470@@UAEXXZ @ 0x0020CF00
void type_20C470::pvf_014()
{
    sub_20CF20();
}

// match: ?sub_20CF20@type_20C470@@QAEXXZ @ 0x0020CF20
void type_20C470::sub_20CF20()
{
    type_1E7CF0 *var_4 = sub_1E7CF0();

    if (var_4->sub_1E7D00(&unk_84B4))
        var_4->sub_1E7D90(&unk_84B4);
    vf_048();
}

// match: ?sub_20CF70@type_20C470@@QAEXXZ @ 0x0020CF70
void type_20C470::sub_20CF70()
{
    sub_1E7CF0()->sub_1E7D90(&unk_81A4);
    vf_050();
    sub_20CF20();
}

// The join (the selected row's session): "Joining" shown while the manager
// joins; on success the in-game menu is hidden, else the level picked is put
// back and, over Xbox Live, the failure is shown ("Join Failed" with the
// reason), or over the system link the failure page is taken down.
// match: ?sub_20CFB0@type_20C470@@QAEXXZ @ 0x0020CFB0
// match: __ehhandler$?sub_20CFB0@type_20C470@@QAEXXZ-0x4F @ 0x003066B0
// match: __ehhandler$?sub_20CFB0@type_20C470@@QAEXXZ @ 0x003066FF
void type_20C470::sub_20CFB0()
{
    type_1FB520_session *t20;
    RwInt32 l1C;
    type_1FB520 *m_18;
    RwInt32 ebp_14;
    bool bp_D;

    bp_D = false;
    ebp_14 = 0;
    sub_1E7CF0()->sub_1E7D30(&unk_832C);
    if (sub_1ECB40())
    {
        m_18 = (type_1FB520 *)sub_20E520();
        if (m_18)
        {
            unk_8768 = true;
            unk_86E0.sub_1F28C0(type_1A5EA0("Joining", 0));
            unk_86B8.sub_1F28C0(type_1CB670());
            type_2053C0::sub_205BF0(2);
            t20 = m_18->sub_21D030();
            l1C = unk_4FDBB0.unk_28;
            sub_1C3D80(t20->unk_28);
            bp_D = unk_4F7EB8.sub_1A9CE0((const type_1CC1F0 *)&unk_198, (const type_1CC3C0 *)t20, &ebp_14, 0);
            unk_8768 = false;
        }
    }
    if (ebp_14 == 0)
    {
        sub_1FC310()->sub_1FBE20();
        return;
    }
    sub_1C3D80(l1C);
    if (sub_204EA0())
    {
        switch (ebp_14)
        {
        case 1:
            unk_86B8.sub_1F28C0(type_1A5EA0("Game session is full", 0));
            break;
        case 3:
            unk_86B8.sub_1F28C0(type_1A5EA0("PEER_CONNECTION_FAILED", 0));
            break;
        case 2:
            unk_86B8.sub_1F28C0(type_1A5EA0("Blocked from game session", 0));
            break;
        case 4:
            unk_86B8.sub_1F28C0(type_1A5EA0("SERVER_CONNECTION_FAILED", 0));
            break;
        default:
            unk_86B8.sub_1F28C0(type_1A5EA0("UNEXPECTED_CONNECTION_FAILURE", 0));
            break;
        }
        unk_86E0.sub_1F28C0(type_1A5EA0("Join Failed", 0));
    }
    else
    {
        if (sub_1E7CF0()->sub_1E7D00(&unk_832C))
            sub_1E7CF0()->sub_1E7D90(&unk_832C);
    }
}

// match: ?sub_20D420@type_20C470@@QAE_NXZ @ 0x0020D420
bool type_20C470::sub_20D420()
{
    return sub_1ECB40();
}

// match: ?sub_20D440@type_20C470@@QAEXXZ @ 0x0020D440
void type_20C470::sub_20D440()
{
    sub_1E7CF0()->sub_1E7D90(&unk_81A4);
    vf_04C();
}

// match: ?sub_20D470@type_20C470@@QAEXXZ @ 0x0020D470
void type_20C470::sub_20D470()
{
    if (unk_8768)
    {
        unk_8768 = false;
        vf_058();
    }
    else
        vf_054();
    sub_1E7CF0()->sub_1E7D90(&unk_832C);
}

// The update: the searching page and text over three frames before the
// search starts (sub_20CB70); while it runs, the text and the sessions
// refreshed until the network game stops searching (then the "no
// sessions" page when none were found); after a failed join, its text.
// match: ?vf_014@type_20C470@@UAEXM@Z @ 0x0020D4C0
// match: __ehhandler$?vf_014@type_20C470@@UAEXM@Z-0x36 @ 0x00306710
// match: __ehhandler$?vf_014@type_20C470@@UAEXM@Z @ 0x00306746
void type_20C470::vf_014(RwReal arg_0)
{
    type_2049D0::vf_014(arg_0);
    if (unk_876C == 0)
    {
        if (!sub_1E7CF0()->sub_1E7D00(&unk_84B4))
            sub_1E7CF0()->sub_1E7D30(&unk_84B4);
        unk_8708.sub_1F28C0(sub_20EB30(type_1CB670("Searching...", 0), arg_0));
        unk_876C++;
    }
    else if (unk_876C == 1)
    {
        unk_876C++;
    }
    else if (unk_876C == 2)
    {
        sub_20CB70();
        unk_876C++;
    }
    type_1E7CF0 *lv_10 = sub_1E7CF0();

    if (unk_8764)
    {
        if (!lv_10->sub_1E7D00(&unk_84B4))
            lv_10->sub_1E7D30(&unk_84B4);
        unk_8708.sub_1F28C0(sub_20EB30(type_1CB670("Searching...", 0), arg_0));
        sub_20D8D0();
        unk_8764 = !unk_4F7EB8.get_unk_19C_direct()->vf_074();
        if (!unk_8764)
        {
            lv_10->sub_1E7D90(&unk_84B4);
            if (unk_8758.empty() && sub_204EA0())
                lv_10->sub_1E7D30(&unk_81A4);
        }
        unk_4F7EB8.sub_1AF750((RwInt32)arg_0, 1, 0);
    }
    else if (unk_8768)
    {
        unk_86E0.sub_1F28C0(sub_20EB30(type_1CB670("Joining", 0), arg_0));
        unk_86B8.sub_1F28C0(unk_4F7E9C);
    }
}

// The sessions' rows refilled from the network game's results, keeping
// the session selected (found again by its address, port and name) and the
// scroll above it.
// match: ?sub_20D8D0@type_20C470@@QAEXXZ @ 0x0020D8D0
// match: __ehhandler$?sub_20D8D0@type_20C470@@QAEXXZ-0x1E @ 0x00306750
// match: __ehhandler$?sub_20D8D0@type_20C470@@QAEXXZ @ 0x0030676E
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_20C470::sub_20D8D0()
{
    type_1FB520_session *slot_58;
    type_1FB520_session *l54;
    RwInt32 loc50;
    RwUInt16 x4C;
    RwUInt32 w48;
    RwInt32 loc44;
    RwInt32 fp_40;
    type_1FB520_session *ebp_3C;
    type_1FB520 *local_38;
    RwUInt8 local_34[4];
    type_1A5EA0 frm_30;
    RwUInt32 lv_10;

    x4C = 0;
    fp_40 = 0;
    if (sub_1ECB40())
    {
        local_38 = (type_1FB520 *)sub_20E520();
        if (local_38)
        {
            slot_58 = local_38->sub_21D030();
            if (slot_58)
            {
                memcpy(local_34, slot_58->unk_04, 4);
                x4C = slot_58->unk_08;
                frm_30 = local_38->sub_1FB760();
                fp_40 = type_1ECA30::sub_1E3480()->sub_1EB1F0() - type_1ECA30::sub_1E3480()->sub_1EB280();
                fp_40 = fp_40 < 0 ? 0 : fp_40;
            }
        }
    }
    // The results and their count (the Xbox Live override takes the count's
    // address and returns the array; the slot is declared over integers).
    l54 = (type_1FB520_session *)unk_4F7EB8.get_unk_19C_direct()->vf_078((RwInt32)&w48);
    if (w48 > 0)
    {
        type_1ECA30::sub_1E3480()->sub_1EB160();
        sub_20CA70();
        sub_1E41C0();
        for (lv_10 = 0; lv_10 < w48; lv_10++)
        {
            type_1FB520_session *lv_5C = l54;

            ebp_3C = &lv_5C[lv_10];
            if (ebp_3C && ebp_3C->unk_34)
            {
                type_1FB520 *lv_60 = new type_1FB520(ebp_3C);

                unk_8758.push_back(lv_60);
                sub_20E540(lv_60);
            }
        }
    }
    loc44 = -1;
    if (!frm_30.empty())
        loc44 = sub_20DC80(frm_30, local_34, x4C);
    loc50 = loc44 - fp_40;
    loc50 = loc50 < 0 ? 0 : loc50;
    if (loc44 != -1)
    {
        type_1ECA30::sub_1E3480()->sub_1EB210(loc50);
        type_1ECA30::sub_1E3480()->sub_1EB0B0(loc44);
    }
}

// The rows' index for the session arg_0 (by name) at the address arg_1C and
// port arg_20: the row already listing it, else the first whose name does
// not sort before it.
// match: ?sub_20DC80@type_20C470@@QAEHUtype_1A5EA0@@PBEG@Z @ 0x0020DC80
// match: __ehhandler$?sub_20DC80@type_20C470@@QAEHUtype_1A5EA0@@PBEG@Z-0x10 @ 0x00306780
// match: __ehhandler$?sub_20DC80@type_20C470@@QAEHUtype_1A5EA0@@PBEG@Z @ 0x00306790
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_20C470::sub_20DC80(type_1A5EA0 arg_0, const RwUInt8 *arg_1C, RwUInt16 arg_20)
{
    RwInt32 l1C;
    RwUInt32 m_18;
    RwUInt32 ebp_14;
    bool bp_D;

    l1C = 0;
    bp_D = false;
    ebp_14 = unk_8758.size();
    for (m_18 = 0; m_18 < ebp_14; m_18++)
    {
        type_1FB520 *lv_20 = sub_21DF90(m_18);
        type_1FB520_session *lv_24 = lv_20->sub_21D030();

        if (lv_24 && lv_24->unk_04[0] == arg_1C[0] && lv_24->unk_04[1] == arg_1C[1] && lv_24->unk_04[2] == arg_1C[2]
            && lv_24->unk_04[3] == arg_1C[3] && lv_24->unk_08 == arg_20)
        {
            bp_D = true;
            break;
        }
        l1C++;
    }
    if (!bp_D)
    {
        l1C = 0;
        for (std::list<type_1FB520 *>::iterator lv_28 = unk_8758.begin(); lv_28 != unk_8758.end(); ++lv_28)
        {
            type_1FB520 *lv_2C = *lv_28;

            if (!(lv_2C->sub_1FB760() < arg_0))
                break;
            l1C++;
        }
    }
    return l1C;
}

// match: ?sub_20DE80@type_20C470@@QAEXXZ @ 0x0020DE80
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_20C470::sub_20DE80()
{
    // The next sort mode after each (a static: the image has it with this function).
    static const RwInt32 dword_3E9254[4] = { 1, 2, 3, 0 };
    type_3E74C0 *lv_10;
    RwUInt32 var_C;
    type_3E7490 *bp_8;
    RwInt32 bp_4;

    bp_8 = type_1ECA30::sub_1E3480();
    lv_10 = sub_1ECB40() ? bp_8->sub_1EB020() : 0;
    type_1ECA30::sub_1E3480()->sub_1EB0D0();
    bp_4 = sub_1FBB50();
    sub_1FBB60(dword_3E9254[bp_4]);
    var_C = type_1ECA30::sub_1E3480()->sub_1EB070()->size();
    type_1ECA30::sub_1E3480()->sub_1EB160();
    type_1ECA30::sub_1E3480()->sub_1EABF0(var_C);
    for (std::list<type_1FB520 *>::iterator var_14 = unk_8758.begin(); var_14 != unk_8758.end(); ++var_14)
        sub_20E540(*var_14);
    if (!type_1ECA30::sub_1E3480()->sub_1EB070()->empty())
    {
        type_1ECA30::sub_1E3480()->sub_1EB0B0(0);
        type_1ECA30::sub_1E3480()->sub_1EB210(0);
    }
    sub_20E060();
}

// Shows the column the results are sorted by ("Sorting by %1" with its
// name).
// match: ?sub_20E060@type_20C470@@QAEXXZ @ 0x0020E060
// match: __ehhandler$?sub_20E060@type_20C470@@QAEXXZ-0x3C @ 0x003067A0
// match: __ehhandler$?sub_20E060@type_20C470@@QAEXXZ @ 0x003067DC
// The locals' names state their slots (docs/toolchain.md).
void type_20C470::sub_20E060()
{
    RwInt32 lv_10 = sub_1FBB50();
    type_1A5EA0 lv_A4[4] = {type_1A5EA0("Name", 0), type_1A5EA0("Map", 0), type_1A5EA0("Number of players", 0),
                             type_1A5EA0("Game type", 0)};

    type_1CB670 lv_30 = sub_1CB7B0("Sorting by %1", lv_A4[lv_10].c_str(), 0);

    unk_8730.sub_1F28C0(lv_30);
}

// match: ??0type_20E4F0@@QAE@I@Z @ 0x0020E4F0
type_20E4F0::type_20E4F0(RwUInt32 arg_0) : type_1ECA30(arg_0)
{
}

// match: ?sub_20E520@type_20E4F0@@QAEPAUtype_3E74C0@kujuUI@@XZ @ 0x0020E520
type_3E74C0 *type_20E4F0::sub_20E520()
{
    return type_1ECA30::sub_1E3480()->sub_1EB020();
}

// match: ?sub_20E540@type_20E4F0@@QAEHPAUtype_1FB520@@@Z @ 0x0020E540
RwInt32 type_20E4F0::sub_20E540(type_1FB520 *arg_0)
{
    RwInt32 var_4 = sub_20E710(arg_0);

    type_1ECA30::sub_1E3480()->sub_1EA980(arg_0, var_4);
    return var_4;
}

// The actions' members (game/kujuui.h's templates, their definitions
// repeated here).
// match: ??0?$type_3E7264@Utype_20C470@@@kujuUI@@QAE@PAUtype_20C470@@P82@AEXXZP82@AE_NXZ@Z @ 0x0020E580
template <class T> type_3E7264<T>::type_3E7264(T *arg_0, void (T::*arg_4)(), bool (T::*arg_C)())
{
    unk_04 = arg_0;
    unk_08 = arg_4;
    unk_10 = arg_C;
}

// match: ?pvf_008@?$type_3E7264@Utype_20C470@@@kujuUI@@UAEXXZ @ 0x0020E600
template <class T> void type_3E7264<T>::pvf_008()
{
    (unk_04->*unk_08)();
}

// match: ?pvf_00C@?$type_3E7264@Utype_20C470@@@kujuUI@@UAE_NXZ @ 0x0020E620
template <class T> bool type_3E7264<T>::pvf_00C()
{
    return (unk_04->*unk_10)();
}

// match: ??0?$type_3E7CE8@Utype_20C470@@@kujuUI@@QAE@PAUtype_20C470@@P82@AEXXZ@Z @ 0x0020E640
template <class T> type_3E7CE8<T>::type_3E7CE8(T *arg_0, void (T::*arg_4)())
{
    unk_04 = arg_0;
    unk_08 = arg_4;
}

// match: ??_G?$type_3E7264@Utype_20C470@@@kujuUI@@UAEPAXI@Z @ 0x0020E6B0
// match: ??1?$type_3E7264@Utype_20C470@@@kujuUI@@UAE@XZ @ 0x0020E5E0
template <class T> type_3E7264<T>::~type_3E7264()
{
}

// match: ??_G?$type_3E7CE8@Utype_20C470@@@kujuUI@@UAEPAXI@Z @ 0x0020E6E0
// match: ??1?$type_3E7CE8@Utype_20C470@@@kujuUI@@UAE@XZ @ 0x0020E690
template <class T> type_3E7CE8<T>::~type_3E7CE8()
{
}

// match: ?sub_20E710@type_20E4F0@@QAEHPAUtype_1FB520@@@Z @ 0x0020E710
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_20E4F0::sub_20E710(type_1FB520 *arg_0)
{
    bool var_25;
    RwUInt32 var_24;
    type_1FB520 *var_20;
    RwUInt32 l1C;
    bool x15;
    RwInt32 ebp_14;
    std::vector<type_3E74C0 *> *lv_10;
    type_1FB520 *var_C;
    RwUInt32 bp_8;
    RwUInt32 bp_4;

    lv_10 = type_1ECA30::sub_1E3480()->sub_1EB070();
    if (lv_10->size() == 0)
        return 0;
    bp_4 = 0;
    bp_8 = type_1ECA30::sub_1E3480()->sub_1EB070()->size();
    l1C = bp_8 - bp_4;
    while (l1C > 1)
    {
        var_24 = (bp_4 + bp_8) / 2;
        var_20 = sub_21DF90(var_24);
        var_25 = arg_0->sub_1FB5A0(*var_20);
        if (var_25)
            bp_8 = var_24;
        else
            bp_4 = var_24;
        l1C = bp_8 - bp_4;
    }
    var_C = sub_21DF90(bp_4);
    x15 = var_C->sub_1FB5A0(*arg_0);
    ebp_14 = x15 ? bp_4 + 1 : bp_4;
    return ebp_14;
}

template <class T> void type_3E7CE8<T>::pvf_008()
{
    (unk_04->*unk_08)();
}

// The rows' list's insertion, which the parked sessions' fill (sub_20D8D0)
// reaches through push_back.
#ifndef CODFH_WIN32
// (not on Win32: _Insert is VC7.1's list internals; the port's library has none)
template void std::list<type_1FB520 *>::_Insert(std::list<type_1FB520 *>::iterator, type_1FB520 *const &);
#endif

// Members /OPT:ICF folded into shared trivial bodies (config/aliases.txt): defined here for
// the authentic link (PLAN M7); the placement link takes the shared bodies.

// ?sub_1E41C0@type_20C470@@QAEXXZ (folded into the empty body at 0x1E41C0)
void type_20C470::sub_1E41C0()
{
}

// The menu's row by index, as type_21DDC0's: /OPT:ICF folded the two (0x21DF90).
type_1FB520 *type_20E4F0::sub_21DF90(RwUInt32 arg_0)
{
    return (type_1FB520 *)(*sub_1E3480()->sub_1EB070())[arg_0];
}
