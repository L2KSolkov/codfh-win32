/*
 * The system link's menu (in-game menu 10, game/livemenu.h): finding a
 * session, creating one, the options, or back.
 */
#include "game/livemenu.h"
#include "game/ingamemenu.h"

// Its data definitions (PLAN M5), in the image's address order.
#ifndef CODFH_SP // MP only: unreferenced constants single player does not emit (not in default.xbe; /O2 keeps them only while they are external)
// 0x003E8B14
extern const RwReal flt_3E8B14 = 0.01f;
// 0x003E8B18
extern const RwReal flt_3E8B18 = 0.01f;
// 0x003E8B1C
extern const RwReal flt_3E8B1C = 16.666666f;
#endif
// End of its data definitions.


using namespace kujuUI;

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3E8B14@@3MB @ 0x003E8B14
// match: ?flt_3E8B18@@3MB @ 0x003E8B18
// match: ?flt_3E8B1C@@3MB @ 0x003E8B1C
// match: ??_C@_07KHIHFBFN@Options?$AA@ @ 0x003E8B20
// match: ??_C@_0O@MOPBCOJO@CreateSession?$AA@ @ 0x003E8B28
// match: ??_C@_0M@HBHEGHPM@FindSession?$AA@ @ 0x003E8B38
// match: ??_7type_2098F0@@6B@ @ 0x003E8B48
// match: ??_C@_0BD@LHLGEFLD@XboxSysLink?4layout?$AA@ @ 0x003E8B8C
// match: ??_7?$type_3E7CE8@Utype_2098F0@@@kujuUI@@6B@ @ 0x003E8BA0
// match: __ehhandler$??0type_2098F0@@QAE@XZ>1>8 @ 0x00422EAC
// match: __ehhandler$??0type_2098F0@@QAE@XZ>1 @ 0x00422ED4
// match: __ehhandler$??1type_2098F0@@UAE@XZ>1>8 @ 0x00422EF0
// match: __ehhandler$??1type_2098F0@@UAE@XZ>1 @ 0x00422F10

// match: ??0type_2098F0@@QAE@XZ @ 0x002098F0
// match: __ehhandler$??0type_2098F0@@QAE@XZ-0x40 @ 0x00305F00
// match: __ehhandler$??0type_2098F0@@QAE@XZ @ 0x00305F40

type_2098F0::type_2098F0()
    : type_2049D0("XboxSysLink.layout", 0, true), unk_188(this, &type_2098F0::sub_209AD0),
      unk_194(this, &type_2098F0::sub_209B00), unk_1A0(this, &type_2098F0::sub_20BE30),
      unk_1AC(this, &type_2098F0::sub_209B30)
{
    sub_204FC0("FindSession", &unk_188);
    sub_204FC0("CreateSession", &unk_194);
    sub_204FC0("Back", &unk_1A0);
    sub_204FC0("Options", &unk_1AC);
}

// match: ??_Gtype_2098F0@@UAEPAXI@Z @ 0x00209A10
// match: ??1type_2098F0@@UAE@XZ @ 0x00209A40
// match: __ehhandler$??1type_2098F0@@UAE@XZ-0x32 @ 0x00305F50
// match: __ehhandler$??1type_2098F0@@UAE@XZ @ 0x00305F82
type_2098F0::~type_2098F0()
{
}

// match: ?sub_209AD0@type_2098F0@@QAEXXZ @ 0x00209AD0
void type_2098F0::sub_209AD0()
{
    sub_1FC310()->sub_1FBDA0(sub_2046C0(9));
}

// match: ?sub_209B00@type_2098F0@@QAEXXZ @ 0x00209B00
void type_2098F0::sub_209B00()
{
    type_2053C0::sub_205BF0(0);
    sub_1FC310()->sub_1FBDA0(sub_2046C0(8));
}

// match: ?sub_209B30@type_2098F0@@QAEXXZ @ 0x00209B30
void type_2098F0::sub_209B30()
{
    sub_20B920(1);
    sub_1FC310()->sub_1FBDA0(sub_2046C0(5));
}

// The actions' members (game/kujuui.h's template, its definitions
// repeated here).
// match: ??0?$type_3E7CE8@Utype_2098F0@@@kujuUI@@QAE@PAUtype_2098F0@@P82@AEXXZ@Z @ 0x00209B60
template <class T> type_3E7CE8<T>::type_3E7CE8(T *arg_0, void (T::*arg_4)())
{
    unk_04 = arg_0;
    unk_08 = arg_4;
}

// match: ??_G?$type_3E7CE8@Utype_2098F0@@@kujuUI@@UAEPAXI@Z @ 0x00209BC0
// match: ??1?$type_3E7CE8@Utype_2098F0@@@kujuUI@@UAE@XZ @ 0x00209BA0
template <class T> type_3E7CE8<T>::~type_3E7CE8()
{
}

template <class T> void type_3E7CE8<T>::pvf_008()
{
    (unk_04->*unk_08)();
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?sub_20BE30@type_2098F0@@QAEXXZ (folded into 0x20BE30)
void type_2098F0::sub_20BE30()
{
    sub_1FC310()->sub_1FBDA0(sub_2046C0(13));
}
