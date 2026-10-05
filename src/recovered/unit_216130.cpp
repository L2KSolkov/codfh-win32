/*
 * The votes' base (game/ingamepages.h): a page over the pause menu with the
 * question and "yes" and "no".
 */
#include "game/ingamepages.h"

using namespace kujuUI;

// The actions' targets: the compiler's thunks calling slots 20 and 21.
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_08IBLBOAEL@VoteText?$AA@ @ 0x003E96E8
// match: ??_7type_216130@@6B@ @ 0x003E96F8
// match: ??_7?$type_3E7CE8@Utype_216130@@@kujuUI@@6B@ @ 0x003E9754
// match: __ehhandler$??0type_216130@@QAE@PBDPAUtype_21A5E0@@@Z>1>8 @ 0x004242D4
// match: __ehhandler$??0type_216130@@QAE@PBDPAUtype_21A5E0@@@Z>1 @ 0x004242F4
// match: __ehhandler$??1type_216130@@UAE@XZ>1>8 @ 0x00424310
// match: __ehhandler$??1type_216130@@UAE@XZ>1 @ 0x00424328
// match: __ehhandler$?vf_008@type_216130@@UAEXXZ>1>8 @ 0x00424344
// match: __ehhandler$?vf_008@type_216130@@UAEXXZ>1 @ 0x0042434C

// match: ??_9@$BFA@AE @ 0x00216420
// match: ??_9@$BFE@AE @ 0x00216430
// match: ??0type_216130@@QAE@PBDPAUtype_21A5E0@@@Z @ 0x00216130
// match: __ehhandler$??0type_216130@@QAE@PBDPAUtype_21A5E0@@@Z-0x32 @ 0x003070C0
// match: __ehhandler$??0type_216130@@QAE@PBDPAUtype_21A5E0@@@Z @ 0x003070F2

type_216130::type_216130(const RwChar *arg_0, type_21A5E0 *arg_4)
    : type_21CB10(arg_0, arg_4, 0), unk_154(this, &type_216130::vf_050), unk_160(this, &type_216130::vf_054)
{
    sub_204FC0("VoteText", &unk_16C);
    sub_204FC0("yes", &unk_154);
    sub_204FC0("no", &unk_160);
}

// match: ??_Gtype_216130@@UAEPAXI@Z @ 0x00216220
// match: ??1type_216130@@UAE@XZ @ 0x00216250
// match: __ehhandler$??1type_216130@@UAE@XZ-0x24 @ 0x00307100
// match: __ehhandler$??1type_216130@@UAE@XZ @ 0x00307124
type_216130::~type_216130()
{
}

// Shown: the base's showing, then the question (slot 22).
// match: ?vf_008@type_216130@@UAEXXZ @ 0x002162D0
// match: __ehhandler$?vf_008@type_216130@@UAEXXZ-0x8 @ 0x00307130
// match: __ehhandler$?vf_008@type_216130@@UAEXXZ @ 0x00307138
void type_216130::vf_008()
{
    type_21CB10::vf_008();
    unk_16C.sub_1F28C0(vf_058());
}

// match: ?vf_050@type_216130@@UAEXXZ @ 0x00216350
void type_216130::vf_050()
{
    unk_130->sub_21C250(1);
}

// match: ?vf_054@type_216130@@UAEXXZ @ 0x00216370
void type_216130::vf_054()
{
    unk_130->sub_21C250(0);
}

// The actions' members (game/kujuui.h's template, its definitions
// repeated here).
// match: ??0?$type_3E7CE8@Utype_216130@@@kujuUI@@QAE@PAUtype_216130@@P82@AEXXZ@Z @ 0x00216390
template <class T> type_3E7CE8<T>::type_3E7CE8(T *arg_0, void (T::*arg_4)())
{
    unk_04 = arg_0;
    unk_08 = arg_4;
}

// match: ??_G?$type_3E7CE8@Utype_216130@@@kujuUI@@UAEPAXI@Z @ 0x002163F0
// match: ??1?$type_3E7CE8@Utype_216130@@@kujuUI@@UAE@XZ @ 0x002163D0
template <class T> type_3E7CE8<T>::~type_3E7CE8()
{
}

template <class T> void type_3E7CE8<T>::pvf_008()
{
    (unk_04->*unk_08)();
}
