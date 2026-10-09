/*
 * The debug menu (game/ingamepages.h): killing the player, resetting the
 * round and adding to its time, then back to the game.
 */
#include "game/ingamepages.h"
#include "game/uiglue.h"

// Its data definitions (PLAN M5), in the image's address order.
#ifndef CODFH_SP // MP only: unreferenced constants single player does not emit (not in default.xbe; /O2 keeps them only while they are external)
// 0x003E9764
extern const RwReal flt_3E9764 = 0.01f;
// 0x003E9768
extern const RwReal flt_3E9768 = 0.01f;
// 0x003E976C
extern const RwReal flt_3E976C = 16.666666f;
#endif
// End of its data definitions.


using namespace kujuUI;

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3E9764@@3MB @ 0x003E9764
// match: ?flt_3E9768@@3MB @ 0x003E9768
// match: ?flt_3E976C@@3MB @ 0x003E976C
// match: ??_C@_06OHOCBCMJ@round5?$AA@ @ 0x003E9770
// match: ??_C@_05MIMAKCN@round?$AA@ @ 0x003E9778
// match: ??_C@_05CFMALAOA@reset?$AA@ @ 0x003E9780
// match: ??_C@_04BJJEOANI@kill?$AA@ @ 0x003E9788
// match: ??_7type_216440@@6B@ @ 0x003E9790
// match: ??_7?$type_3E7CE8@Utype_216440@@@kujuUI@@6B@ @ 0x003E97E0
// match: __ehhandler$??0type_216440@@QAE@PBDPAUtype_21A5E0@@@Z>1>8 @ 0x00424368
// match: __ehhandler$??0type_216440@@QAE@PBDPAUtype_21A5E0@@@Z>1 @ 0x00424390
// match: __ehhandler$??1type_216440@@UAE@XZ>1>8 @ 0x004243AC
// match: __ehhandler$??1type_216440@@UAE@XZ>1 @ 0x004243CC

// match: ??0type_216440@@QAE@PBDPAUtype_21A5E0@@@Z @ 0x00216440
// match: __ehhandler$??0type_216440@@QAE@PBDPAUtype_21A5E0@@@Z-0x40 @ 0x00307150
// match: __ehhandler$??0type_216440@@QAE@PBDPAUtype_21A5E0@@@Z @ 0x00307190

type_216440::type_216440(const RwChar *arg_0, type_21A5E0 *arg_4)
    : type_21CB10(arg_0, arg_4, 0), unk_154(this, &type_216440::sub_217120), unk_160(this, &type_216440::sub_216620),
      unk_16C(this, &type_216440::sub_216650), unk_178(this, &type_216440::sub_216690)
{
    sub_204FC0("kill", &unk_154);
    sub_204FC0("reset", &unk_160);
    sub_204FC0("round", &unk_16C);
    sub_204FC0("round5", &unk_178);
}

// match: ??_Gtype_216440@@UAEPAXI@Z @ 0x00216560
// match: ??1type_216440@@UAE@XZ @ 0x00216590
// match: __ehhandler$??1type_216440@@UAE@XZ-0x32 @ 0x003071A0
// match: __ehhandler$??1type_216440@@UAE@XZ @ 0x003071D2
type_216440::~type_216440()
{
}

// match: ?sub_216620@type_216440@@QAEXXZ @ 0x00216620
void type_216440::sub_216620()
{
    sub_1C4520();
    unk_130->sub_21C200(0, 0);
    unk_130->sub_21C360();
}

// match: ?sub_216650@type_216440@@QAEXXZ @ 0x00216650
void type_216440::sub_216650()
{
    sub_1C45B0(30.0f);
    unk_130->sub_21C200(0, 0);
    unk_130->sub_21C360();
}

// match: ?sub_216690@type_216440@@QAEXXZ @ 0x00216690
void type_216440::sub_216690()
{
    sub_1C45B0(5.0f);
    unk_130->sub_21C200(0, 0);
    unk_130->sub_21C360();
}

// The actions' members (game/kujuui.h's template, its definitions
// repeated here).
// match: ??0?$type_3E7CE8@Utype_216440@@@kujuUI@@QAE@PAUtype_216440@@P82@AEXXZ@Z @ 0x002166D0
template <class T> type_3E7CE8<T>::type_3E7CE8(T *arg_0, void (T::*arg_4)())
{
    unk_04 = arg_0;
    unk_08 = arg_4;
}

// match: ??_G?$type_3E7CE8@Utype_216440@@@kujuUI@@UAEPAXI@Z @ 0x00216730
// match: ??1?$type_3E7CE8@Utype_216440@@@kujuUI@@UAE@XZ @ 0x00216710
template <class T> type_3E7CE8<T>::~type_3E7CE8()
{
}

template <class T> void type_3E7CE8<T>::pvf_008()
{
    (unk_04->*unk_08)();
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?sub_217120@type_216440@@QAEXXZ (folded into 0x217120)
void type_216440::sub_217120()
{
    sub_1C44F0();
    unk_130->sub_21C200(0, 0);
    unk_130->sub_21C360();
}
