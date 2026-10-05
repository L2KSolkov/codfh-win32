/*
 * The instant action page (in-game menu 2, game/livemenu.h): a game of the
 * type picked found at once (the in-game menu 3 then), or back to the Live
 * menu.
 */
#include "game/livemenu.h"
#include "game/ingamemenu.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003E8828
extern const RwReal flt_3E8828 = 0.01f;
// 0x003E882C
extern const RwReal flt_3E882C = 0.01f;
// 0x003E8830
extern const RwReal flt_3E8830 = 16.666666f;
// End of its data definitions.


using namespace kujuUI;

// The actions' members.
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3E8828@@3MB @ 0x003E8828
// match: ?flt_3E882C@@3MB @ 0x003E882C
// match: ?flt_3E8830@@3MB @ 0x003E8830
// match: ??_C@_0BB@FBLMCOJP@SearchAndDestroy?$AA@ @ 0x003E8834
// match: ??_C@_0P@OABLPCMB@CaptureTheFlag?$AA@ @ 0x003E8848
// match: ??_C@_0P@NIPLLOAC@TeamDeathmatch?$AA@ @ 0x003E8858
// match: ??_7type_206D10@@6B@ @ 0x003E8868
// match: ??_C@_0BF@IEINDECK@InstantAction?4layout?$AA@ @ 0x003E88AC
// match: ??_7?$type_3E88C4@Utype_206D10@@@kujuUI@@6B@ @ 0x003E88C4
// match: ??_7?$type_3E7CE8@Utype_206D10@@@kujuUI@@6B@ @ 0x003E88D4
// match: __ehhandler$??0type_206D10@@QAE@XZ>1>8 @ 0x00422AB8
// match: __ehhandler$??0type_206D10@@QAE@XZ>1 @ 0x00422AF0
// match: __ehhandler$??1type_206D10@@UAE@XZ>1>8 @ 0x00422B0C
// match: __ehhandler$??1type_206D10@@UAE@XZ>1 @ 0x00422B3C

// match: ??0?$type_3E88C4@Utype_206D10@@@kujuUI@@QAE@PAUtype_206D10@@P82@AEXH@ZH@Z @ 0x00206FF0
// match: ??1?$type_3E88C4@Utype_206D10@@@kujuUI@@UAE@XZ @ 0x00207040
// match: ?pvf_008@?$type_3E88C4@Utype_206D10@@@kujuUI@@UAEXXZ @ 0x00207060
// match: ??0?$type_3E7CE8@Utype_206D10@@@kujuUI@@QAE@PAUtype_206D10@@P82@AEXXZ@Z @ 0x00207080
// match: ??1?$type_3E7CE8@Utype_206D10@@@kujuUI@@UAE@XZ @ 0x002070C0
// match: ??_G?$type_3E88C4@Utype_206D10@@@kujuUI@@UAEPAXI@Z @ 0x002070E0
// match: ??_G?$type_3E7CE8@Utype_206D10@@@kujuUI@@UAEPAXI@Z @ 0x00207110
// match: ??0type_206D10@@QAE@XZ @ 0x00206D10
// match: __ehhandler$??0type_206D10@@QAE@XZ-0x5C @ 0x00305B20
// match: __ehhandler$??0type_206D10@@QAE@XZ @ 0x00305B7C

type_206D10::type_206D10()
    : type_2049D0("InstantAction.layout", 0, true), unk_188(this, &type_206D10::sub_206F90, 0x20),
      unk_198(this, &type_206D10::sub_206F90, 1), unk_1A8(this, &type_206D10::sub_206F90, 2),
      unk_1B8(this, &type_206D10::sub_206F90, 4), unk_1C8(this, &type_206D10::sub_206F90, 8),
      unk_1D8(this, &type_206D10::sub_206FC0)
{
    sub_204FC0("Any", &unk_188);
    sub_204FC0("Deathmatch", &unk_198);
    sub_204FC0("TeamDeathmatch", &unk_1A8);
    sub_204FC0("CaptureTheFlag", &unk_1B8);
    sub_204FC0("SearchAndDestroy", &unk_1C8);
    sub_204FC0("Back", &unk_1D8);
}

// match: ??_Gtype_206D10@@UAEPAXI@Z @ 0x00206EA0
// match: ??1type_206D10@@UAE@XZ @ 0x00206ED0
// match: __ehhandler$??1type_206D10@@UAE@XZ-0x4E @ 0x00305B90
// match: __ehhandler$??1type_206D10@@UAE@XZ @ 0x00305BDE
type_206D10::~type_206D10()
{
}

// match: ?sub_206F90@type_206D10@@QAEXH@Z @ 0x00206F90
void type_206D10::sub_206F90(RwInt32 arg_0)
{
    sub_208990(arg_0);
    sub_1FC310()->sub_1FBDA0(sub_2046C0(3));
}

// match: ?sub_206FC0@type_206D10@@QAEXXZ @ 0x00206FC0
void type_206D10::sub_206FC0()
{
    sub_1FC310()->sub_1FBDA0(sub_2046C0(6));
}

// The actions' instances (game/kujuui.h's templates, their definitions
// repeated here).
template <class T> type_3E88C4<T>::type_3E88C4(T *arg_0, void (T::*arg_4)(RwInt32), RwInt32 arg_8)
{
    unk_04 = arg_0;
    unk_08 = arg_4;
    unk_0C = arg_8;
}

template <class T> type_3E88C4<T>::~type_3E88C4()
{
}

template <class T> void type_3E88C4<T>::pvf_008()
{
    (unk_04->*unk_08)(unk_0C);
}

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
