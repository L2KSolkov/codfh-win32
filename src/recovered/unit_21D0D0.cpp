/*
 * The quit asked (game/ingamepages.h): "yes" and "no" answered to the pause
 * menu, or to the page's parent without one, and its question set when
 * shown (slot 2).
 */
#include "game/ingamepages.h"
#include "game/uiglue.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003EA3B0
extern const RwReal flt_3EA3B0 = 0.01f;
// 0x003EA3B4
extern const RwReal flt_3EA3B4 = 0.01f;
// 0x003EA3B8
extern const RwReal flt_3EA3B8 = 16.666666f;
// End of its data definitions.


using namespace kujuUI;

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3EA3B0@@3MB @ 0x003EA3B0
// match: ?flt_3EA3B4@@3MB @ 0x003EA3B4
// match: ?flt_3EA3B8@@3MB @ 0x003EA3B8
// match: ??_7type_21D0D0@@6B@ @ 0x003EA3C0
// match: ??_7?$type_3E7CE8@Utype_21D0D0@@@kujuUI@@6B@ @ 0x003EA410
// match: __ehhandler$??0type_21D0D0@@QAE@PBDPAUtype_21A5E0@@@Z>1>8 @ 0x0042502C
// match: __ehhandler$??0type_21D0D0@@QAE@PBDPAUtype_21A5E0@@@Z>1 @ 0x0042504C
// match: __ehhandler$??1type_21D0D0@@UAE@XZ>1>8 @ 0x00425068
// match: __ehhandler$??1type_21D0D0@@UAE@XZ>1 @ 0x00425080
// match: __ehhandler$?vf_008@type_21D0D0@@UAEXXZ>1>8 @ 0x0042509C
// match: __ehhandler$?vf_008@type_21D0D0@@UAEXXZ>1 @ 0x004250AC

// match: ??0type_21D0D0@@QAE@PBDPAUtype_21A5E0@@@Z @ 0x0021D0D0
// match: __ehhandler$??0type_21D0D0@@QAE@PBDPAUtype_21A5E0@@@Z-0x32 @ 0x00307F20
// match: __ehhandler$??0type_21D0D0@@QAE@PBDPAUtype_21A5E0@@@Z @ 0x00307F52

type_21D0D0::type_21D0D0(const RwChar *arg_0, type_21A5E0 *arg_4)
    : type_21CB10(arg_0, arg_4, 0), unk_154(this, &type_21D0D0::sub_21D340), unk_160(this, &type_21D0D0::sub_21D390)
{
    sub_204FC0("yes", &unk_154);
    sub_204FC0("no", &unk_160);
    sub_204FC0("Prompt", &unk_16C);
    sub_20EA40();
}

// match: ??_Gtype_21D0D0@@UAEPAXI@Z @ 0x0021D1C0
// match: ??1type_21D0D0@@UAE@XZ @ 0x0021D1F0
// match: __ehhandler$??1type_21D0D0@@UAE@XZ-0x24 @ 0x00307F60
// match: __ehhandler$??1type_21D0D0@@UAE@XZ @ 0x00307F84
type_21D0D0::~type_21D0D0()
{
}

// Shown: the base's showing, then the question for the host or not.
// match: ?vf_008@type_21D0D0@@UAEXXZ @ 0x0021D270
// match: __ehhandler$?vf_008@type_21D0D0@@UAEXXZ-0x10 @ 0x00307F90
// match: __ehhandler$?vf_008@type_21D0D0@@UAEXXZ @ 0x00307FA0
void type_21D0D0::vf_008()
{
    type_21CB10::vf_008();
    if (sub_1C4BE0())
        unk_16C.sub_1F28C0(type_1CB670("QUIT_GAME_HOST", 0));
    else
        unk_16C.sub_1F28C0(type_1CB670("QUIT_GAME?", 0));
}

// match: ?sub_21D340@type_21D0D0@@QAEXXZ @ 0x0021D340
void type_21D0D0::sub_21D340()
{
    if (unk_130)
        unk_130->sub_21C2A0(1);
    else
        sub_1E3480()->vf_01C(2, 0);
}

// match: ?sub_21D390@type_21D0D0@@QAEXXZ @ 0x0021D390
void type_21D0D0::sub_21D390()
{
    if (unk_130)
        unk_130->sub_21C2A0(0);
    else
        sub_1E3480()->vf_01C(3, 0);
}

// The actions' members (game/kujuui.h's template, its definitions
// repeated here).
// match: ??0?$type_3E7CE8@Utype_21D0D0@@@kujuUI@@QAE@PAUtype_21D0D0@@P82@AEXXZ@Z @ 0x0021D3E0
template <class T> type_3E7CE8<T>::type_3E7CE8(T *arg_0, void (T::*arg_4)())
{
    unk_04 = arg_0;
    unk_08 = arg_4;
}

// match: ??_G?$type_3E7CE8@Utype_21D0D0@@@kujuUI@@UAEPAXI@Z @ 0x0021D440
// match: ??1?$type_3E7CE8@Utype_21D0D0@@@kujuUI@@UAE@XZ @ 0x0021D420
template <class T> type_3E7CE8<T>::~type_3E7CE8()
{
}

template <class T> void type_3E7CE8<T>::pvf_008()
{
    (unk_04->*unk_08)();
}
