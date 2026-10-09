/*
 * The create session page (game/livemenu.h): its actions over the host's
 * options and the advanced options' page, the options' defaults for the
 * game type and the check on the session's name. The texts' fill
 * (sub_205880) passes the session's name to a compiled-out debug print.
 */
#include "game/livemenu.h"
#include "game/ingamemenu.h"
#include "game/liveservice.h"
#include "game/data.h"
#include "game/uiglue.h"

// Its data definitions (PLAN M5), in the image's address order.
#ifndef CODFH_SP // MP only: unreferenced constants single player does not emit (not in default.xbe; /O2 keeps them only while they are external)
// 0x003E8574
extern const RwReal flt_3E8574 = 0.01f;
// 0x003E8578
extern const RwReal flt_3E8578 = 0.01f;
// 0x003E857C
extern const RwReal flt_3E857C = 16.666666f;
#endif
// 0x0042D28C
RwInt32 dword_42D28C = 3;
// 0x0042D290
RwInt32 dword_42D290 = 3;
// End of its data definitions.


using namespace kujuUI;

// The page's deleting destructor and the actions' members.
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3E8574@@3MB @ 0x003E8574
// match: ?flt_3E8578@@3MB @ 0x003E8578
// match: ?flt_3E857C@@3MB @ 0x003E857C
// match: ??_C@_0O@IIBEDCPB@?$CIplaceholder?$CJ?$AA@ @ 0x003E8580
// match: ??_C@_0O@BMFJIJEK@CloseAdvanced?$AA@ @ 0x003E8590
// match: ??_C@_0P@DCLNIDJD@CancelAdvanced?$AA@ @ 0x003E85A0
// match: ??_C@_0N@DBNFMEOM@OpenAdvanced?$AA@ @ 0x003E85B0
// match: ??_C@_0N@LJEFEIDD@PrivateSlots?$AA@ @ 0x003E85C0
// match: ??_C@_0N@EHJMDHLK@FriendlyFire?$AA@ @ 0x003E85D0
// match: ??_C@_0M@EMHMAMIO@RespawnTime?$AA@ @ 0x003E85E0
// match: ??_C@_05KOHFLOFG@Level?$AA@ @ 0x003E85EC
// match: ??_C@_07JJHJMMJF@MapType?$AA@ @ 0x003E85F4
// match: ??_C@_0L@INDPAOFE@MaxPlayers?$AA@ @ 0x003E85FC
// match: ??_C@_09OHILOMME@TimeLimit?$AA@ @ 0x003E8608
// match: ??_C@_0O@JCONCAAA@TeamBalancing?$AA@ @ 0x003E8614
// match: ??_C@_09MKMPFIBP@SwapSides?$AA@ @ 0x003E8624
// match: ??_C@_0M@DBJMIEHM@MapRotation?$AA@ @ 0x003E8630
// match: ??_C@_0L@NCHEENDH@ScoreLimit?$AA@ @ 0x003E863C
// match: ??_C@_04FABLJDN@Name?$AA@ @ 0x003E8648
// match: ??_C@_04FEOMFELI@Back?$AA@ @ 0x003E8650
// match: ??_C@_06MIKANEJK@Create?$AA@ @ 0x003E8658
// match: ??_C@_0BN@MFNAMEBJ@CreateSessionAdvanced?4layout?$AA@ @ 0x003E8660
// match: ??_7type_2053C0@@6Btype_200B90@@@ @ 0x003E8680
// match: ??_7type_2053C0@@6Btype_2049D0@@@ @ 0x003E8688
// match: ??_7?$type_3E7264@Utype_2053C0@@@kujuUI@@6B@ @ 0x003E86D4
// match: ??_7?$type_3E7CE8@Utype_2053C0@@@kujuUI@@6B@ @ 0x003E86E4
// match: __ehhandler$??0type_2053C0@@QAE@PBD_N@Z>1>8 @ 0x00422834
// match: __ehhandler$??0type_2053C0@@QAE@PBD_N@Z>1 @ 0x0042287C
// match: __ehhandler$??1type_2053C0@@UAE@XZ>1>8 @ 0x00422898
// match: __ehhandler$??1type_2053C0@@UAE@XZ>1 @ 0x004228D0
// match: __ehhandler$?vf_03C@type_2053C0@@UAEXXZ>1>8 @ 0x004228EC
// match: __ehhandler$?vf_03C@type_2053C0@@UAEXXZ>1 @ 0x0042290C
// match: ?dword_42D28C@@3HA @ 0x0042D28C
// match: ?dword_42D290@@3HA @ 0x0042D290

// match: ??0type_2053C0@@QAE@PBD_N@Z @ 0x002053C0
// match: __ehhandler$??0type_2053C0@@QAE@PBD_N@Z-0x72 @ 0x003057D0
// match: __ehhandler$??0type_2053C0@@QAE@PBD_N@Z @ 0x00305842

type_2053C0::type_2053C0(const RwChar *arg_0, bool arg_4)
    : type_2049D0(arg_0, &unk_37C, arg_4), type_200B90(true),
      unk_528(this, &type_2053C0::sub_205A40, &type_2053C0::sub_205F70),
      unk_540(this, &type_2053C0::sub_205A90), unk_550(this, &type_2053C0::sub_205AD0),
      unk_560(this, &type_2053C0::sub_205B40), unk_570(this, &type_2053C0::sub_205BA0),
      unk_580("CreateSessionAdvanced.layout", 0, true), unk_708(0), unk_70C(0)
{
    sub_204FC0("Create", &unk_528);
    sub_204FC0("Back", &unk_540);
    sub_204FC0("Name", &(type_200B90::unk_90));
    sub_204FC0("ScoreLimit", &unk_1B4);
    sub_204FC0("MapRotation", &unk_2AC);
    unk_580.sub_204FC0("SwapSides", &unk_2EC);
    unk_580.sub_204FC0("TeamBalancing", &unk_30C);
    sub_204FC0("TimeLimit", &unk_194);
    sub_204FC0("MaxPlayers", &unk_174);
    sub_204FC0("MapType", &unk_32C);
    sub_204FC0("Level", &unk_D8);
    unk_580.sub_204FC0("RespawnTime", &unk_230);
    unk_580.sub_204FC0("FriendlyFire", &unk_2CC);
    unk_580.sub_204FC0("PrivateSlots", &unk_F8);
    sub_204FC0("OpenAdvanced", &unk_550);
    unk_580.sub_204FC0("CancelAdvanced", &unk_560);
    unk_580.sub_204FC0("CloseAdvanced", &unk_570);
    type_200B90::unk_90.sub_1F28C0(sub_1CB720("(placeholder)"));
}

// match: ??_Gtype_2053C0@@UAEPAXI@Z @ 0x00205760
// match: ??0?$type_3E7264@Utype_2053C0@@@kujuUI@@QAE@PAUtype_2053C0@@P82@AEXXZP82@AE_NXZ@Z @ 0x00206040
// match: ??1?$type_3E7264@Utype_2053C0@@@kujuUI@@UAE@XZ @ 0x002060A0
// match: ??0?$type_3E7CE8@Utype_2053C0@@@kujuUI@@QAE@PAUtype_2053C0@@P82@AEXXZ@Z @ 0x002060C0
// match: ??1?$type_3E7CE8@Utype_2053C0@@@kujuUI@@UAE@XZ @ 0x00206110
// match: ??_G?$type_3E7264@Utype_2053C0@@@kujuUI@@UAEPAXI@Z @ 0x00206130
// match: ??_G?$type_3E7CE8@Utype_2053C0@@@kujuUI@@UAEPAXI@Z @ 0x00206160

// match: ??1type_2053C0@@UAE@XZ @ 0x00205790
// match: __ehhandler$??1type_2053C0@@UAE@XZ-0x77 @ 0x00305850
// match: __ehhandler$??1type_2053C0@@UAE@XZ @ 0x003058C7
type_2053C0::~type_2053C0()
{
}

// Loaded: the host options' fields, the level picked (the first when none
// is), 16 players, and the server's name (else the signed-in user's name,
// or the player's own).
// match: ?vf_03C@type_2053C0@@UAEXXZ @ 0x00205880
// match: __ehhandler$?vf_03C@type_2053C0@@UAEXXZ-0x20 @ 0x003058E0
// match: __ehhandler$?vf_03C@type_2053C0@@UAEXXZ @ 0x00305900
void type_2053C0::vf_03C()
{
    sub_205C10();
    if (unk_4FDBB0.unk_28 == -1)
        sub_1C3D80(0);
    LEVELS_CHECK(unk_4FDBB0.unk_28);
    LEVELS_CHECK(unk_4FDBB0.unk_28);
    type_211860_key lv_10(&dword_4FD974[unk_4FDBB0.unk_28]);

    unk_D8.sub_201EC0(lv_10);
    unk_174.sub_201EC0((type_2138C0_value)4);
    type_1CB670 lv_30 = sub_1CB720(sub_1C4320());

    if (lv_30.empty())
    {
        if (sub_227560()->sub_228100())
        {
            lv_30 = sub_1CB720(sub_1C42E0());
            debug_text(lv_30);
        }
        else
            lv_30 = sub_1CB720(dword_4F28F0->unk_183);
    }
    unk_90.sub_1F28C0(lv_30);
}

// match: ?sub_205A40@type_2053C0@@QAEXXZ @ 0x00205A40
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_2053C0::sub_205A40()
{
    RwInt32 var_8;
    RwInt32 l4;

    var_8 = 0;
    l4 = -1;
    sub_201A70();
    vf_044();
    dword_42D28C = 3;
    sub_1FC310()->sub_1FBE20();
}

// match: ?sub_205A90@type_2053C0@@QAEXXZ @ 0x00205A90
void type_2053C0::sub_205A90()
{
    type_1FBDA0_menu *var_4 = vf_048();

    dword_42D28C = 3;
    sub_1FC310()->sub_1FBDA0(var_4);
}

// match: ?sub_205AD0@type_2053C0@@QAEXXZ @ 0x00205AD0
void type_2053C0::sub_205AD0()
{
    sub_201CD0();
    unk_708 = sub_1E8C50();
    sub_1E7CF0()->sub_1E7D30(&unk_580);
    if (unk_70C)
        unk_580.sub_1E8B50(unk_70C);
}

// match: ?sub_205B40@type_2053C0@@QAEXXZ @ 0x00205B40
void type_2053C0::sub_205B40()
{
    sub_201D60();
    unk_70C = unk_580.sub_1E8C50();
    sub_1E7CF0()->sub_1E7D90(&unk_580);
    sub_1E8B50(unk_708);
}

// match: ?sub_205BA0@type_2053C0@@QAEXXZ @ 0x00205BA0
void type_2053C0::sub_205BA0()
{
    unk_70C = unk_580.sub_1E8C50();
    sub_1E7CF0()->sub_1E7D90(&unk_580);
    sub_1E8B50(unk_708);
}

// match: ?sub_205BF0@type_2053C0@@SAXH@Z @ 0x00205BF0
void type_2053C0::sub_205BF0(RwInt32 arg_0)
{
    dword_42D28C = arg_0;
}

// match: ?sub_205C00@type_2053C0@@SAHXZ @ 0x00205C00
RwInt32 type_2053C0::sub_205C00()
{
    return dword_42D28C;
}

// match: ?sub_205C10@type_2053C0@@QAEXXZ @ 0x00205C10
void type_2053C0::sub_205C10()
{
    type_210430_value var_4 = (type_210430_value)1;

    unk_32C.sub_201EC0(var_4);
    sub_2016A0();
}

// match: ?vf_014@type_2053C0@@UAEXM@Z @ 0x00205C50
void type_2053C0::vf_014(RwReal arg_0)
{
    type_2049D0::vf_014(arg_0);
    sub_201C70();
}

// match: ?vf_00@type_2053C0@@UAEXXZ @ 0x00205C80
void type_2053C0::vf_00()
{
    switch (unk_32C.sub_1FD030())
    {
    case 1:
        unk_2AC.sub_201EC0((type_212C70_value)3);
        unk_194.sub_201EC0(5);
        unk_1B4.sub_1E7BB0(0);
        unk_174.sub_201EC0((type_2138C0_value)4);
        unk_230.sub_1E7BB0(5);
        unk_2CC.sub_201EC0((type_214C30_value)0);
        break;
    case 2:
        unk_2AC.sub_201EC0((type_212C70_value)3);
        unk_194.sub_201EC0(10);
        unk_1B4.sub_1E7BB0(0);
        unk_174.sub_201EC0((type_2138C0_value)4);
        unk_230.sub_1E7BB0(5);
        unk_2CC.sub_201EC0((type_214C30_value)1);
        unk_30C.sub_201EC0((type_214C30_value)0);
        break;
    case 4:
        unk_2AC.sub_201EC0((type_212C70_value)3);
        unk_194.sub_201EC0(10);
        unk_1B4.sub_1E7BB0(0);
        unk_174.sub_201EC0((type_2138C0_value)4);
        unk_230.sub_1E7BB0(5);
        unk_2CC.sub_201EC0((type_214C30_value)1);
        unk_30C.sub_201EC0((type_214C30_value)0);
        unk_2EC.sub_201EC0((type_214C30_value)0);
        break;
    case 8:
        unk_2AC.sub_201EC0((type_212C70_value)3);
        unk_194.sub_201EC0(5);
        unk_174.sub_201EC0((type_2138C0_value)4);
        unk_230.sub_1E7BB0(5);
        unk_2CC.sub_201EC0((type_214C30_value)1);
        unk_30C.sub_201EC0((type_214C30_value)0);
        unk_2EC.sub_201EC0((type_214C30_value)1);
        break;
    }
}

// match: ?sub_205F70@type_2053C0@@QAE_NXZ @ 0x00205F70
bool type_2053C0::sub_205F70()
{
    bool var_1 = false;

    if (unk_374)
    {
        type_1CB670 var_24(unk_90.unk_08);
        for (std::string::iterator var_28 = var_24.begin(); var_28 != var_24.end(); ++var_28)
        {
            if (*var_28 != ' ')
            {
                var_1 = true;
                break;
            }
        }
    }
    else
        return true;
    return var_1;
}

// The actions' instances (game/kujuui.h's templates, their definitions
// repeated here).
template <class T> type_3E7264<T>::type_3E7264(T *arg_0, void (T::*arg_4)(), bool (T::*arg_C)())
{
    unk_04 = arg_0;
    unk_08 = arg_4;
    unk_10 = arg_C;
}

template <class T> type_3E7264<T>::~type_3E7264()
{
}

template <class T> void type_3E7264<T>::pvf_008()
{
    (unk_04->*unk_08)();
}

template <class T> bool type_3E7264<T>::pvf_00C()
{
    return (unk_04->*unk_10)();
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

// The page's two actions (their constructors are out of line: the page's
// constructor builds them).
template struct kujuUI::type_3E7264<type_2053C0>;
template struct kujuUI::type_3E7CE8<type_2053C0>;
