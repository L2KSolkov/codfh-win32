/*
 * The Live login pages (game/livemenu.h): the player's name and friends
 * list shown over each, and the network warning shown while the Xbox Live
 * connection is down (one instance, shared by the pages that ask for it).
 * The player's status text (sub_205070) builds a std::string through the
 * library's out-of-line default constructor (sub_E87E0) and is not matched
 * yet (docs/questions.md).
 */
#include "game/livemenu.h"
#include "game/ingamemenu.h"
#include "types/cXboxLive.h"

using namespace kujuUI;

// match: ??0type_2049D0@@QAE@PBDPAU?$type_1EFCF0@PAUtype_3E7D08@kujuUI@@@kujuUI@@_N@Z @ 0x002049D0
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
type_204B10::type_204B10() : type_2049D0("NetworkWarningContext.layout", 0, false), unk_188(this, &type_204B10::sub_204C50)
{
    sub_204FC0("Acknowledge", &unk_188);
    sub_204FC0("Countdown", &unk_194);
    sub_20EA40();
}

// match: ?vf_014@type_204B10@@UAEXM@Z @ 0x00204BD0
void type_204B10::vf_014(RwReal arg_0)
{
    unk_194.sub_1F28C0(type_1A5EA0("", 0));
}

// match: ?sub_204C50@type_204B10@@QAEXXZ @ 0x00204C50
void type_204B10::sub_204C50()
{
    type_1FBDA0_menu *var_4 = sub_2046C0(13);
    type_1E7CF0 *var_8 = sub_1E7CF0();

    while (var_8->sub_1E80D0() > 1)
        var_8->sub_1E7D90(var_8->sub_1E7FE0());
    sub_1FC310()->sub_1FBDA0(var_4);
}

// match: ??1type_204B10@@UAE@XZ @ 0x00204CE0
type_204B10::~type_204B10()
{
}

// match: ??1type_2049D0@@UAE@XZ @ 0x00204D80
type_2049D0::~type_2049D0()
{
    if (unk_184 && --dword_504570 == 0 && dword_50456C)
    {
        delete dword_50456C;
        dword_50456C = 0;
    }
}

// match: ?sub_204E50@type_2049D0@@SA_NXZ @ 0x00204E50
bool type_2049D0::sub_204E50()
{
    type_4F8054 *var_4 = dword_4F8054;
    bool var_5 = var_4 == 0 || (var_4->vf_050() != 0) == 1;

    return var_5;
}

// match: ?vf_014@type_2049D0@@UAEXM@Z @ 0x00204EB0
void type_2049D0::vf_014(RwReal arg_0)
{
    if (dword_504568)
    {
        dword_504568 = 0;
        type_1FBDA0_menu *var_8 = sub_2046C0(13);
        sub_1FC310()->sub_1FBDA0(var_8);
    }
    sub_205070(sub_1D8810()->get_unk_2918());
    type_20E850::vf_014(arg_0);
    if (sub_2046E0())
        sub_204700();
    if (unk_184)
    {
        type_1E7CF0 *var_10 = sub_1E7CF0();
        bool var_9 = sub_204E50();
        if (!byte_50438C && !var_9)
        {
            if (!var_10->sub_1E7D00(dword_50456C))
            {
                dword_504574 = dword_3E8478;
                var_10->sub_1E7D30(dword_50456C);
            }
        }
        else if (var_10->sub_1E7D00(dword_50456C))
            var_10->sub_1E7D90(dword_50456C);
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
