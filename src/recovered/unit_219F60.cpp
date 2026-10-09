/*
 * The host options pages' base (game/ingamepages.h): the host's options over
 * an in-game page, saved, and their advanced page opened, cancelled and
 * closed.
 */
#include "game/ingamepages.h"
#include "game/uiglue.h"

// Its data definitions (PLAN M5), in the image's address order.
#ifndef CODFH_SP // MP only: unreferenced constants single player does not emit (not in default.xbe; /O2 keeps them only while they are external)
// 0x003E9F18
extern const RwReal flt_3E9F18 = 0.01f;
// 0x003E9F1C
extern const RwReal flt_3E9F1C = 0.01f;
// 0x003E9F20
extern const RwReal flt_3E9F20 = 16.666666f;
#endif
// End of its data definitions.


using namespace kujuUI;

// The advanced page's destructor (the compiler's) and its deleting form.
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3E9F18@@3MB @ 0x003E9F18
// match: ?flt_3E9F1C@@3MB @ 0x003E9F1C
// match: ?flt_3E9F20@@3MB @ 0x003E9F20
// match: ??_7type_219F60@@6B@ @ 0x003E9F28
// match: ??_C@_04INACKGJP@Save?$AA@ @ 0x003E9F6C
// match: ??_7type_219FE0@@6Btype_200B90@@@ @ 0x003E9F74
// match: ??_7type_219FE0@@6Btype_21CB10@@@ @ 0x003E9F78
// match: ??_7?$type_3E7CE8@Utype_219FE0@@@kujuUI@@6B@ @ 0x003E9FC8
// match: __ehhandler$??0type_219FE0@@QAE@PBD0PAUtype_21A5E0@@_N@Z>1>8 @ 0x00424B6C
// match: __ehhandler$??0type_219FE0@@QAE@PBD0PAUtype_21A5E0@@_N@Z>1 @ 0x00424BAC
// match: __ehhandler$??1type_219FE0@@UAE@XZ>1>8 @ 0x00424BC8
// match: __ehhandler$??1type_219FE0@@UAE@XZ>1 @ 0x00424BF8

// match: ??_Gtype_219F60@@UAEPAXI@Z @ 0x00219F90
// match: ??1type_219F60@@UAE@XZ @ 0x00219FC0
// match: ??0type_219F60@@QAE@PBDPAU?$type_1EFCF0@PAUtype_3E7D08@kujuUI@@@kujuUI@@_N@Z @ 0x00219F60

type_219F60::type_219F60(const RwChar *arg_0, type_1EFCF0<type_3E7D08 *> *arg_4, bool arg_8)
    : type_2049D0(arg_0, arg_4, arg_8)
{
}

// match: ??0type_219FE0@@QAE@PBD0PAUtype_21A5E0@@_N@Z @ 0x00219FE0
// match: __ehhandler$??0type_219FE0@@QAE@PBD0PAUtype_21A5E0@@_N@Z-0x64 @ 0x00307910
// match: __ehhandler$??0type_219FE0@@QAE@PBD0PAUtype_21A5E0@@_N@Z @ 0x00307974
type_219FE0::type_219FE0(const RwChar *arg_0, const RwChar *arg_4, type_21A5E0 *arg_8, bool arg_C)
    : type_21CB10(arg_0, arg_8, 0), type_200B90(arg_C), unk_4F8(this, &type_219FE0::sub_21A460),
      unk_508(this, &type_219FE0::sub_21A490), unk_518(this, &type_219FE0::sub_21A4C0),
      unk_528(this, &type_219FE0::sub_21A4F0), unk_538(arg_4, 0, false)
{
    unk_39C = false;
    sub_204FC0("Save", &unk_4F8);
    sub_204FC0("Name", &(type_200B90::unk_90));
    sub_204FC0("ScoreLimit", &unk_1B4);
    sub_204FC0("MapRotation", &unk_2AC);
    unk_538.sub_204FC0("SwapSides", &unk_2EC);
    sub_204FC0("TimeLimit", &unk_194);
    unk_538.sub_204FC0("TeamBalancing", &unk_30C);
    sub_204FC0("MaxPlayers", &unk_174);
    sub_204FC0("MapType", &unk_32C);
    sub_204FC0("Level", &unk_D8);
    unk_538.sub_204FC0("RespawnTime", &unk_230);
    unk_538.sub_204FC0("FriendlyFire", &unk_2CC);
    unk_538.sub_204FC0("PrivateSlots", &unk_F8);
    sub_204FC0("OpenAdvanced", &unk_508);
    unk_538.sub_204FC0("CancelAdvanced", &unk_518);
    unk_538.sub_204FC0("CloseAdvanced", &unk_528);
    type_200B90::unk_90.sub_1F28C0(sub_1CB720(sub_1C4320()));
    unk_538.sub_20EA40();
}

// match: ??_Gtype_219FE0@@UAEPAXI@Z @ 0x0021A320
// match: ??1type_219FE0@@UAE@XZ @ 0x0021A350
// match: __ehhandler$??1type_219FE0@@UAE@XZ-0x69 @ 0x00307980
// match: __ehhandler$??1type_219FE0@@UAE@XZ @ 0x003079E9
type_219FE0::~type_219FE0()
{
}

// match: ?vf_008@type_219FE0@@UAEXXZ @ 0x0021A430
void type_219FE0::vf_008()
{
    type_21CB10::vf_008();
    sub_1C3D20();
    sub_201890();
}

// match: ?sub_21A460@type_219FE0@@QAEXXZ @ 0x0021A460
void type_219FE0::sub_21A460()
{
    sub_201A70();
    sub_1C3D60(0);
    vf_040();
}

// match: ?sub_21A490@type_219FE0@@QAEXXZ @ 0x0021A490
void type_219FE0::sub_21A490()
{
    sub_201CD0();
    sub_1E7CF0()->sub_1E7D30(&unk_538);
}

// match: ?sub_21A4C0@type_219FE0@@QAEXXZ @ 0x0021A4C0
void type_219FE0::sub_21A4C0()
{
    sub_201D60();
    sub_1E7CF0()->sub_1E7D90(&unk_538);
}

// match: ?sub_21A4F0@type_219FE0@@QAEXXZ @ 0x0021A4F0
void type_219FE0::sub_21A4F0()
{
    sub_1E7CF0()->sub_1E7D90(&unk_538);
}

// match: ?vf_00C@type_219FE0@@UAEXXZ @ 0x0021A510
void type_219FE0::vf_00C()
{
    if (sub_1E7CF0()->sub_1E7D00(&unk_538))
        sub_21A4C0();
}

// The actions' members (game/kujuui.h's template, its definitions
// repeated here).
// match: ??0?$type_3E7CE8@Utype_219FE0@@@kujuUI@@QAE@PAUtype_219FE0@@P82@AEXXZ@Z @ 0x0021A540
template <class T> type_3E7CE8<T>::type_3E7CE8(T *arg_0, void (T::*arg_4)())
{
    unk_04 = arg_0;
    unk_08 = arg_4;
}

// match: ??_G?$type_3E7CE8@Utype_219FE0@@@kujuUI@@UAEPAXI@Z @ 0x0021A5B0
// match: ??1?$type_3E7CE8@Utype_219FE0@@@kujuUI@@UAE@XZ @ 0x0021A590
template <class T> type_3E7CE8<T>::~type_3E7CE8()
{
}

template <class T> void type_3E7CE8<T>::pvf_008()
{
    (unk_04->*unk_08)();
}

// The actions' constructor, which only the page's constructor uses.
template struct kujuUI::type_3E7CE8<type_219FE0>;

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?vf_014@type_219FE0@@UAEXM@Z (folded into 0x223810)
void type_219FE0::vf_014(RwReal arg_0)
{
    type_21CB10::vf_014(arg_0);
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?vf_024@type_219FE0@@UAEHXZ (folded into 0x222540)
RwInt32 type_219FE0::vf_024()
{
        return 0x3A;
    }
