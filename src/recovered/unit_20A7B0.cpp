/*
 * The message menu (in-game menu 4, game/livemenu.h): a text and an "OK"
 * that closes it and calls the caller's callback.
 */
#include "game/livemenu.h"
#include "game/ingamemenu.h"

// Its data definitions (PLAN M5), in the image's address order.
#ifndef CODFH_SP // MP only: unreferenced constants single player does not emit (not in default.xbe; /O2 keeps them only while they are external)
// 0x003E8E04
extern const RwReal flt_3E8E04 = 0.01f;
// 0x003E8E08
extern const RwReal flt_3E8E08 = 0.01f;
// 0x003E8E0C
extern const RwReal flt_3E8E0C = 16.666666f;
// 0x003E8E10
extern const RwReal flt_3E8E10 = 0.01f;
// 0x003E8E14
extern const RwReal flt_3E8E14 = 0.01f;
// 0x003E8E18
extern const RwReal flt_3E8E18 = 16.666666f;
#endif
// 0x0050457C
type_20A7B0 *dword_50457C;
// End of its data definitions.


using namespace kujuUI;

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3E8E04@@3MB @ 0x003E8E04
// match: ?flt_3E8E08@@3MB @ 0x003E8E08
// match: ?flt_3E8E0C@@3MB @ 0x003E8E0C
// match: ?flt_3E8E10@@3MB @ 0x003E8E10
// match: ?flt_3E8E14@@3MB @ 0x003E8E14
// match: ?flt_3E8E18@@3MB @ 0x003E8E18
// match: ??_C@_07BEIHKDLJ@Message?$AA@ @ 0x003E8E1C
// match: ??_C@_02GIPFHKNO@OK?$AA@ @ 0x003E8E24
// match: ??_7type_20A7B0@@6B@ @ 0x003E8E28
// match: ??_C@_0P@BLHEDMNB@Message?4layout?$AA@ @ 0x003E8E6C
// match: ??_7?$type_3E7CE8@Utype_20A7B0@@@kujuUI@@6B@ @ 0x003E8E7C
// match: __ehhandler$??0type_20A7B0@@QAE@XZ>1>8 @ 0x00423060
// match: __ehhandler$??0type_20A7B0@@QAE@XZ>1 @ 0x00423078
// match: __ehhandler$??1type_20A7B0@@UAE@XZ>1>8 @ 0x00423094
// match: __ehhandler$??1type_20A7B0@@UAE@XZ>1 @ 0x004230A4

// match: ??0type_20A7B0@@QAE@XZ @ 0x0020A7B0
// match: __ehhandler$??0type_20A7B0@@QAE@XZ-0x24 @ 0x00306100
// match: __ehhandler$??0type_20A7B0@@QAE@XZ @ 0x00306124

type_20A7B0::type_20A7B0() : type_2049D0("Message.layout", 0, true), unk_188(this, &type_20A7B0::sub_20A940)
{
    unk_1BC = 0;
    unk_1C0 = 0;
    sub_204FC0("OK", &unk_188);
    sub_204FC0("Message", &unk_194);
    dword_50457C = this;
    sub_20EA40();
}

// match: ??_Gtype_20A7B0@@UAEPAXI@Z @ 0x0020A890
// match: ??1type_20A7B0@@UAE@XZ @ 0x0020A8C0
// match: __ehhandler$??1type_20A7B0@@UAE@XZ-0x16 @ 0x00306130
// match: __ehhandler$??1type_20A7B0@@UAE@XZ @ 0x00306146
type_20A7B0::~type_20A7B0()
{
    dword_50457C = 0;
}

// match: ?sub_20A940@type_20A7B0@@QAEXXZ @ 0x0020A940
void type_20A7B0::sub_20A940()
{
    sub_1E7CF0()->sub_1E7D90(this);
    if (unk_1BC)
        unk_1BC(unk_1C0);
}

// The action's members (game/kujuui.h's template, its definitions
// repeated here).
// match: ??0?$type_3E7CE8@Utype_20A7B0@@@kujuUI@@QAE@PAUtype_20A7B0@@P82@AEXXZ@Z @ 0x0020A980
template <class T> type_3E7CE8<T>::type_3E7CE8(T *arg_0, void (T::*arg_4)())
{
    unk_04 = arg_0;
    unk_08 = arg_4;
}

// match: ??_G?$type_3E7CE8@Utype_20A7B0@@@kujuUI@@UAEPAXI@Z @ 0x0020A9E0
// match: ??1?$type_3E7CE8@Utype_20A7B0@@@kujuUI@@UAE@XZ @ 0x0020A9C0
template <class T> type_3E7CE8<T>::~type_3E7CE8()
{
}

template <class T> void type_3E7CE8<T>::pvf_008()
{
    (unk_04->*unk_08)();
}
