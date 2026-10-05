/*
 * The Live login pages (game/livemenu.h): the player's name and friends
 * list shown over each, and the network warning shown while the Xbox Live
 * connection is down (one instance, shared by the pages that ask for it),
 * and the player's status text (sub_205070).
 */
#include "game/livemenu.h"
#include "game/ingamemenu.h"
#include "types/cXboxLive.h"
#include "types/type_DC400.h"
#include "game/liveservice.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003E846C
extern const RwReal flt_3E846C = 0.01f;
// 0x003E8470
extern const RwReal flt_3E8470 = 0.01f;
// 0x003E8474
extern const RwReal flt_3E8474 = 16.666666f;
// 0x003E8478
extern const RwReal flt_3E8478 = 60.0f;
// 0x00504568
RwInt32 dword_504568;
// 0x0050456C
type_204B10 *dword_50456C;
// 0x00504570
RwInt32 dword_504570;
// End of its data definitions.

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3E846C@@3MB @ 0x003E846C
// match: ?flt_3E8470@@3MB @ 0x003E8470
// match: ?flt_3E8474@@3MB @ 0x003E8474
// match: ?flt_3E8478@@3MB @ 0x003E8478
// match: ??_C@_0BB@PFLFNFHN@LoginFriendsList?$AA@ @ 0x003E847C
// match: ??_C@_0BA@MFGBAFHO@LoginPlayerName?$AA@ @ 0x003E8490
// match: ??_7type_2049D0@@6B@ @ 0x003E84A0
// match: ??_C@_09OAJPIMOA@Countdown?$AA@ @ 0x003E84E4
// match: ??_C@_0M@LEMKNODK@Acknowledge?$AA@ @ 0x003E84F0
// match: ??_7type_204B10@@6B@ @ 0x003E8500
// match: ??_C@_0BN@KACCJBMK@NetworkWarningContext?4layout?$AA@ @ 0x003E8544
// match: ??_7?$type_3E7CE8@Utype_204B10@@@kujuUI@@6B@ @ 0x003E8564
// match: __ehhandler$??0type_2049D0@@QAE@PBDPAU?$type_1EFCF0@PAUtype_3E7D08@kujuUI@@@kujuUI@@_N@Z>1>8 @ 0x004226F4
// match: __ehhandler$??0type_2049D0@@QAE@PBDPAU?$type_1EFCF0@PAUtype_3E7D08@kujuUI@@@kujuUI@@_N@Z>1 @ 0x00422714
// match: __ehhandler$??0type_204B10@@QAE@XZ>1>8 @ 0x00422730
// match: __ehhandler$??0type_204B10@@QAE@XZ>1 @ 0x00422748
// match: __ehhandler$?vf_014@type_204B10@@UAEXM@Z>1>8 @ 0x00422764
// match: __ehhandler$?vf_014@type_204B10@@UAEXM@Z>1 @ 0x0042276C
// match: __ehhandler$??1type_204B10@@UAE@XZ>1>8 @ 0x00422788
// match: __ehhandler$??1type_204B10@@UAE@XZ>1 @ 0x00422798
// match: __ehhandler$??1type_2049D0@@UAE@XZ>1>8 @ 0x004227B4
// match: __ehhandler$??1type_2049D0@@UAE@XZ>1 @ 0x004227CC
// match: __ehhandler$?sub_205070@type_2049D0@@QAEXH@Z>1>8 @ 0x004227E8
// match: __ehhandler$?sub_205070@type_2049D0@@QAEXH@Z>1 @ 0x00422818
// match: .CRT$XCU+0 @ 0x00427364

// match: _$E2 @ 0x0030DAF0

// A copy of flt_3E8478's bits (60.0f), made when the program starts (its
// initializer moves the constant as a dword).
RwInt32 dword_504574 = *(const RwInt32 *)&flt_3E8478;

using namespace kujuUI;

// The pages' deleting destructors and the action's members.
// match: ??_Gtype_204B10@@UAEPAXI@Z @ 0x00204CB0
// match: ??_Gtype_2049D0@@UAEPAXI@Z @ 0x00204D50
// match: ??0?$type_3E7CE8@Utype_204B10@@@kujuUI@@QAE@PAUtype_204B10@@P82@AEXXZ@Z @ 0x00205330
// match: ??1?$type_3E7CE8@Utype_204B10@@@kujuUI@@UAE@XZ @ 0x00205370
// match: ??_G?$type_3E7CE8@Utype_204B10@@@kujuUI@@UAEPAXI@Z @ 0x00205390

// match: ??0type_2049D0@@QAE@PBDPAU?$type_1EFCF0@PAUtype_3E7D08@kujuUI@@@kujuUI@@_N@Z @ 0x002049D0
// match: __ehhandler$??0type_2049D0@@QAE@PBDPAU?$type_1EFCF0@PAUtype_3E7D08@kujuUI@@@kujuUI@@_N@Z-0x2F @ 0x003056A0
// match: __ehhandler$??0type_2049D0@@QAE@PBDPAU?$type_1EFCF0@PAUtype_3E7D08@kujuUI@@@kujuUI@@_N@Z @ 0x003056CF
type_2049D0::type_2049D0(const RwChar *arg_0, type_1EFCF0<type_3E7D08 *> *arg_4, bool arg_8)
    : type_20E850(arg_0, arg_4)
{
    unk_180 = -1;
    unk_184 = arg_8;
    sub_204FC0("LoginPlayerName", &unk_130);
    sub_204FC0("LoginFriendsList", &unk_158);
    if (unk_184)
    {
        if (dword_504570 == 0)
        {
            dword_504570++;
            dword_50456C = new type_204B10();
        }
        else
            dword_504570++;
    }
}

// match: ??0type_204B10@@QAE@XZ @ 0x00204B10
// match: __ehhandler$??0type_204B10@@QAE@XZ-0x24 @ 0x003056E0
// match: __ehhandler$??0type_204B10@@QAE@XZ @ 0x00305704
type_204B10::type_204B10() : type_2049D0("NetworkWarningContext.layout", 0, false), unk_188(this, &type_204B10::sub_204C50)
{
    sub_204FC0("Acknowledge", &unk_188);
    sub_204FC0("Countdown", &unk_194);
    sub_20EA40();
}

// match: ?vf_014@type_204B10@@UAEXM@Z @ 0x00204BD0
// match: __ehhandler$?vf_014@type_204B10@@UAEXM@Z-0x8 @ 0x00305710
// match: __ehhandler$?vf_014@type_204B10@@UAEXM@Z @ 0x00305718
void type_204B10::vf_014(RwReal arg_0)
{
    unk_194.sub_1F28C0(type_1CB670("", 0));
}

// match: ?sub_204C50@type_204B10@@QAEXXZ @ 0x00204C50
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_204B10::sub_204C50()
{
    type_1FBDA0_menu *l4 = sub_2046C0(13);
    type_1E7CF0 *var_8 = sub_1E7CF0();

    while ((RwInt32)var_8->sub_1E80D0() > 1)
        var_8->sub_1E7D90(var_8->sub_1E7FE0());
    sub_1FC310()->sub_1FBDA0(l4);
}

// match: ??1type_204B10@@UAE@XZ @ 0x00204CE0
// match: __ehhandler$??1type_204B10@@UAE@XZ-0x16 @ 0x00305730
// match: __ehhandler$??1type_204B10@@UAE@XZ @ 0x00305746
type_204B10::~type_204B10()
{
}

// match: ??1type_2049D0@@UAE@XZ @ 0x00204D80
// match: __ehhandler$??1type_2049D0@@UAE@XZ-0x24 @ 0x00305750
// match: __ehhandler$??1type_2049D0@@UAE@XZ @ 0x00305774
type_2049D0::~type_2049D0()
{
    if (unk_184 && --dword_504570 == 0 && dword_50456C)
    {
        delete dword_50456C;
        dword_50456C = 0;
    }
}

// match: ?sub_204E50@type_2049D0@@SA_NXZ @ 0x00204E50
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
bool type_2049D0::sub_204E50()
{
    type_4F8054 *l4 = dword_4F8054;
    bool var_5 = (bool)(l4 == 0 || (bool)l4->vf_050() == true);

    return var_5;
}

// match: ?sub_204EA0@type_2049D0@@SA_NXZ @ 0x00204EA0
bool type_2049D0::sub_204EA0()
{
    bool var_1 = true;

    return true;
}

// match: ?vf_014@type_2049D0@@UAEXM@Z @ 0x00204EB0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_2049D0::vf_014(RwReal arg_0)
{
    cXboxLive *var_14;
    type_1E7CF0 *ebp_10;
    bool var_9;
    type_1FBDA0_menu *frm_8;
    RwInt32 l4;

    if (dword_504568)
    {
        dword_504568 = 0;
        frm_8 = sub_2046C0(13);
        sub_1FC310()->sub_1FBDA0(frm_8);
    }
    var_14 = sub_1D8810();
    l4 = var_14->unk_2918;
    sub_205070(l4);
    type_20E850::vf_014(arg_0);
    if (sub_2046E0())
        sub_204700();
    if (unk_184)
    {
        ebp_10 = sub_1E7CF0();
        var_9 = sub_204E50();
        if (!byte_50438C && !var_9)
        {
            if (!ebp_10->sub_1E7D00(dword_50456C))
            {
                dword_504574 = *(const RwInt32 *)&flt_3E8478;
                ebp_10->sub_1E7D30(dword_50456C);
            }
        }
        else if (ebp_10->sub_1E7D00(dword_50456C))
            ebp_10->sub_1E7D90(dword_50456C);
    }
}

// match: ?sub_204FC0@type_20E850@@QAEXPBDPAUtype_3E70B0@kujuUI@@@Z @ 0x00204FC0
void type_20E850::sub_204FC0(const RwChar *arg_0, type_3E70B0 *arg_4)
{
    unk_118.sub_1EFCF0(arg_0, arg_4);
}

// match: ?vf_03C@type_2049D0@@UAEXXZ @ 0x00204FF0
void type_2049D0::vf_03C()
{
    unk_180 = -1;
}

// match: ?givenFocus@type_2049D0@@UAEXXZ @ 0x00205010
void type_2049D0::givenFocus()
{
    sub_20EA40();
    cLayoutPage::givenFocus();
}

// match: ?lostFocus@type_2049D0@@UAEXXZ @ 0x00205030
void type_2049D0::lostFocus()
{
    cLayoutPage::lostFocus();
}

// match: ?sub_205050@type_2049D0@@QAEXABUtype_1A5EA0@@@Z @ 0x00205050
void type_2049D0::sub_205050(const type_1A5EA0 &arg_0)
{
    unk_130.sub_1F28C0(arg_0);
}

// The status text for the sign-in state arg_0 (with the signed-in user's
// gamertag in state 4), kept in unk_180.
// match: ?sub_205070@type_2049D0@@QAEXH@Z @ 0x00205070
// match: __ehhandler$?sub_205070@type_2049D0@@QAEXH@Z-0x39 @ 0x00305780
// match: __ehhandler$?sub_205070@type_2049D0@@QAEXH@Z @ 0x003057B9
void type_2049D0::sub_205070(RwInt32 arg_0)
{
    type_1CB670 lv_2C;

    switch (arg_0)
    {
    case 4:
        {
            lv_2C = type_1CB670(dword_42D278[4], 0);
            XONLINE_USER *lv_34 = XOnlineGetLogonUsers();
            RwInt32 lv_30 = sub_227900(lv_34);

            if (lv_30 >= 0)
                lv_2C.sub_1FBB90(sub_1CB720(lv_34[lv_30].szGamertag));
        }
        break;
    case 1:
        lv_2C = type_1CB670(dword_42D278[1], 0);
        break;
    case 0:
        lv_2C = type_1CB670(dword_42D278[0], 0);
        break;
    case 2:
        lv_2C = type_1CB670(dword_42D278[2], 0);
        break;
    case 3:
        lv_2C = type_1CB670(dword_42D278[3], 0);
        break;
    }
    sub_205050(lv_2C);
    unk_180 = arg_0;
}

// The "Acknowledge" action's instance (game/kujuui.h's template, its
// definitions repeated here).
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

// Members /OPT:ICF folded into shared trivial bodies (config/aliases.txt): defined here for
// the authentic link (PLAN M7); the placement link takes the shared bodies.

// ?vf_040@type_2049D0@@UAEXXZ (folded into the empty body at 0x1E41C0)
void type_2049D0::vf_040()
{
}

// The base page's (type_20E850's) handling (folded by /OPT:ICF into
// type_21A5E0's, 0x21B8D0).
void type_2049D0::vf_018(kujuUI::type_1E4130 *arg_0)
{
    type_20E850::vf_018(arg_0);
}
