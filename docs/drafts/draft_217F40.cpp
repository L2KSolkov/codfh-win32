/*
 * The initial team selection (game/ingamepages.h): the team selection's
 * base with "auto", which lets the game pick the team.
 */
#include "game/ingamepages.h"
#include "game/uiglue.h"

using namespace kujuUI;

// match: ??0type_217F40@@QAE@PBDPAUtype_21A5E0@@@Z @ 0x00217F40
// match: __ehhandler$??0type_217F40@@QAE@PBDPAUtype_21A5E0@@@Z-0x24 @ 0x00307510
// match: __ehhandler$??0type_217F40@@QAE@PBDPAUtype_21A5E0@@@Z @ 0x00307534
type_217F40::type_217F40(const RwChar *arg_0, type_21A5E0 *arg_4)
    : type_220C40(arg_0, arg_4), unk_1CC(this, &type_217F40::sub_218110), unk_1D8(this, &type_217F40::sub_218130)
{
    sub_204FC0("team1", &unk_154);
    sub_204FC0("team2", &unk_160);
    sub_204FC0("auto", &unk_1CC);
    sub_204FC0("flag", &unk_190);
    sub_204FC0("autofocus", &unk_1D8);
    unk_1B0.sub_1EFCF0("auto", &unk_1C4);
}

// match: ??_Gtype_217F40@@UAEPAXI@Z @ 0x00218060
// match: ??1type_217F40@@UAE@XZ @ 0x00218090
type_217F40::~type_217F40()
{
    sub_221430();
}

// match: ?sub_218110@type_217F40@@QAEXXZ @ 0x00218110
void type_217F40::sub_218110()
{
    sub_221100(1);
    sub_1C4B10();
}

// match: ?sub_218130@type_217F40@@QAEXXZ @ 0x00218130
void type_217F40::sub_218130()
{
    sub_221140(1);
}

// The actions' members (game/kujuui.h's template, its definitions
// repeated here).
// match: ??0?$type_3E7CE8@Utype_217F40@@@kujuUI@@QAE@PAUtype_217F40@@P82@AEXXZ@Z @ 0x00218150
template <class T> type_3E7CE8<T>::type_3E7CE8(T *arg_0, void (T::*arg_4)())
{
    unk_04 = arg_0;
    unk_08 = arg_4;
}

// match: ??_G?$type_3E7CE8@Utype_217F40@@@kujuUI@@UAEPAXI@Z @ 0x002181B0
// match: ??1?$type_3E7CE8@Utype_217F40@@@kujuUI@@UAE@XZ @ 0x00218190
template <class T> type_3E7CE8<T>::~type_3E7CE8()
{
}

template <class T> void type_3E7CE8<T>::pvf_008()
{
    (unk_04->*unk_08)();
}
