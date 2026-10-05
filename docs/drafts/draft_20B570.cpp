/*
 * The in-game options (in-game menu 5, game/livemenu.h): the front end's
 * options page (game/options.h) under "Options.layout", with "Back" and
 * "Accept", following the voice chat's speakers.
 */
#include "game/livemenu.h"
#include "game/ingamemenu.h"

using namespace kujuUI;

// match: ??0type_20B570@@QAE@XZ @ 0x0020B570
type_20B570::type_20B570()
    : type_2049D0("Options.layout", 0, true), type_1FC320(0, 0, 0, 0), unk_340(this, &type_20B570::sub_20B8A0),
      unk_350(this, &type_20B570::sub_20B8F0)
{
    sub_204FC0("Volume", &unk_00);
    sub_204FC0("Sensitivity", &unk_7C);
    sub_204FC0("Sound", &unk_F8);
    sub_204FC0("Turn", &unk_118);
    sub_204FC0("YAxis", &unk_138);
    sub_204FC0("Controls", &unk_158);
    sub_204FC0("Vibration", &unk_178);
    sub_204FC0("VoiceChatSpeakers", &unk_198);
    sub_204FC0("Back", &unk_340);
    sub_204FC0("Accept", &unk_350);
}

// match: ??_Gtype_20B570@@UAEPAXI@Z @ 0x0020B720
// match: ??1type_20B570@@UAE@XZ @ 0x0020B750
type_20B570::~type_20B570()
{
}

// match: ?vf_03C@type_20B570@@UAEXXZ @ 0x0020B7F0
void type_20B570::vf_03C()
{
    type_2049D0::vf_03C();
    sub_1FCC80();
    unk_360 = (type_1FD490_value)sub_1C51A0();
    unk_198.sub_201EC0(unk_360);
}

// match: ?vf_014@type_20B570@@UAEXM@Z @ 0x0020B840
void type_20B570::vf_014(RwReal arg_0)
{
    type_2049D0::vf_014(arg_0);
    RwInt32 var_4 = sub_1C51A0();
    if (var_4 != unk_360)
    {
        unk_360 = (type_1FD490_value)var_4;
        unk_198.sub_201EC0(unk_360);
    }
}

// match: ?sub_20B8A0@type_20B570@@QAEXXZ @ 0x0020B8A0
void type_20B570::sub_20B8A0()
{
    RwInt32 var_8 = dword_42D2A8 ? 10 : 6;
    type_1FBDA0_menu *var_4 = sub_2046C0(var_8);

    sub_1FC310()->sub_1FBDA0(var_4);
}

// match: ?sub_20B8F0@type_20B570@@QAEXXZ @ 0x0020B8F0
void type_20B570::sub_20B8F0()
{
    sub_1FCD10();
    sub_1C5220();
    sub_20B8A0();
}

// match: ?sub_20B920@@YAXH@Z @ 0x0020B920
void sub_20B920(RwInt32 arg_0)
{
    dword_42D2A8 = arg_0;
}

// The actions' members (game/kujuui.h's template, its definitions
// repeated here).
// match: ??0?$type_3E7CE8@Utype_20B570@@@kujuUI@@QAE@PAUtype_20B570@@P82@AEXXZ@Z @ 0x0020B930
template <class T> type_3E7CE8<T>::type_3E7CE8(T *arg_0, void (T::*arg_4)())
{
    unk_04 = arg_0;
    unk_08 = arg_4;
}

// match: ??_G?$type_3E7CE8@Utype_20B570@@@kujuUI@@UAEPAXI@Z @ 0x0020B9A0
// match: ??1?$type_3E7CE8@Utype_20B570@@@kujuUI@@UAE@XZ @ 0x0020B980
template <class T> type_3E7CE8<T>::~type_3E7CE8()
{
}

template <class T> void type_3E7CE8<T>::pvf_008()
{
    (unk_04->*unk_08)();
}
