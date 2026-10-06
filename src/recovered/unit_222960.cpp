/*
 * The vote on a player (game/ingamepages.h): the other players listed by
 * name, the one picked voted on after a confirmation.
 */
#include "game/fileio.h"
#include "game/ingamepages.h"
#include "game/uiglue.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003EAAB0
extern const RwReal flt_3EAAB0 = 0.01f;
// 0x003EAAB4
extern const RwReal flt_3EAAB4 = 0.01f;
// 0x003EAAB8
extern const RwReal flt_3EAAB8 = 16.666666f;
// End of its data definitions.


using namespace kujuUI;

// The this-adjusting thunk the columns' vtable (off_3EAAEC) holds for the
// deleting destructor.
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3EAAB0@@3MB @ 0x003EAAB0
// match: ?flt_3EAAB4@@3MB @ 0x003EAAB4
// match: ?flt_3EAAB8@@3MB @ 0x003EAAB8
// match: ??_C@_0BC@JOBGAELE@VotePlayerConfirm?$AA@ @ 0x003EAABC
// match: ??_C@_0BJ@BADICELI@VotePlayerConfirm?4layout?$AA@ @ 0x003EAAD0
// match: ??_7type_222960@@6Btype_218B80@@@ @ 0x003EAAEC
// match: ??_7type_222960@@6Btype_21CB10@@@ @ 0x003EAB08
// match: ??_C@_0CG@DEPIPMHE@Change?5in?5players?4?4?4?5refreshing?5@ @ 0x003EAB58
// match: ??_7?$type_3E7CE8@Utype_222960@@@kujuUI@@6B@ @ 0x003EAB80
// match: __ehhandler$??0type_222960@@QAE@PBDPAUtype_21A5E0@@@Z>1>8 @ 0x00425AEC
// match: __ehhandler$??0type_222960@@QAE@PBDPAUtype_21A5E0@@@Z>1 @ 0x00425B24
// match: __ehhandler$??1type_222960@@UAE@XZ>1>8 @ 0x00425B40
// match: __ehhandler$??1type_222960@@UAE@XZ>1 @ 0x00425B78
// match: __ehhandler$?sub_222D20@type_222960@@QAEXXZ>1>8 @ 0x00425B94
// match: __ehhandler$?sub_222D20@type_222960@@QAEXXZ>1 @ 0x00425B9C
// match: __ehhandler$?pvf_010@type_222960@@UAEXXZ>1>8 @ 0x00425BB8
// match: __ehhandler$?pvf_010@type_222960@@UAEXXZ>1 @ 0x00425BD0

// match: ??_Etype_222960@@WBFE@AEPAXI@Z @ 0x00223270
// match: ??0type_222960@@QAE@PBDPAUtype_21A5E0@@@Z @ 0x00222960
// match: __ehhandler$??0type_222960@@QAE@PBDPAUtype_21A5E0@@@Z-0x5C @ 0x00308AA0
// match: __ehhandler$??0type_222960@@QAE@PBDPAUtype_21A5E0@@@Z @ 0x00308AFC

type_222960::type_222960(const RwChar *arg_0, type_21A5E0 *arg_4)
    : type_21CB10(arg_0, arg_4, 0), type_218B80(1), unk_170("VotePlayerConfirm.layout", 0, false),
      unk_320(this, &type_222960::sub_223050), unk_330(this, &type_222960::sub_2231A0), unk_344(0)
{
    sub_204FC0("PlayerList", this);
    unk_170.sub_204FC0("VotePlayerConfirm", &unk_2F8);
    unk_170.sub_204FC0("Yes", &unk_320);
    unk_170.sub_204FC0("No", &unk_330);
}

// match: ??_Gtype_222960@@UAEPAXI@Z @ 0x00222B30
// match: ??1type_222960@@UAE@XZ @ 0x00222B60
// match: __ehhandler$??1type_222960@@UAE@XZ-0x77 @ 0x00308B10
// match: __ehhandler$??1type_222960@@UAE@XZ @ 0x00308B87
type_222960::~type_222960()
{
    sub_222C70();
}

// match: ?sub_222C70@type_222960@@QAEXXZ @ 0x00222C70
void type_222960::sub_222C70()
{
    type_218B80::sub_1E3480()->sub_1EB160();
    for (std::list<type_21CE60 *>::iterator var_4 = unk_164.begin(); var_4 != unk_164.end(); ++var_4)
        delete *var_4;
    unk_164.clear();
}

// match: ?sub_222D20@type_222960@@QAEXXZ @ 0x00222D20
// match: __ehhandler$?sub_222D20@type_222960@@QAEXXZ-0xB @ 0x00308BA0
// match: __ehhandler$?sub_222D20@type_222960@@QAEXXZ @ 0x00308BAB
void type_222960::sub_222D20()
{
    RwInt32 l14 = 0;

    sub_222C70();
    unk_340 = sub_1C48A0();
    take_out_peer(unk_340, 0);
    RwUInt32 var_10;
    for (var_10 = 0; var_10 < 16; var_10++)
    {
        if (unk_340.test(var_10))
        {
            type_21CE60 *var_1C;
            RwChar *var_18 = sub_1C4630(var_10);

            var_1C = new type_21CE60(var_10, var_18);

            unk_164.push_back(var_1C);
            sub_218BB0(var_1C);
            l14++;
        }
    }
    if (l14 > 0)
        type_218B80::sub_1E3480()->sub_1EB0B0(0);
    else
        vf_040();
}

// match: ?vf_008@type_222960@@UAEXXZ @ 0x00222F00
void type_222960::vf_008()
{
    type_21CB10::vf_008();
    sub_222D20();
}

// match: ?vf_00C@type_222960@@UAEXXZ @ 0x00222F20
void type_222960::vf_00C()
{
    if (sub_1E7CF0()->sub_1E7D00(&unk_170))
        sub_1E7CF0()->sub_1E7D90(&unk_170);
}

// A player picked: the confirmation names the player and is pushed.
// match: ?pvf_010@type_222960@@UAEXXZ @ 0x00222F60
// match: __ehhandler$?pvf_010@type_222960@@UAEXXZ-0x10 @ 0x00308BC0
// match: __ehhandler$?pvf_010@type_222960@@UAEXXZ @ 0x00308BD0
void type_222960::pvf_010()
{
    if (sub_1ECB40())
    {
        type_1CB670 lv_2C = sub_1CB720(sub_20E520()->sub_21D050().c_str());
        unk_2F8.sub_1F28C0(lv_2C);
        sub_1E7CF0()->sub_1E7D30(&unk_170);
    }
}

// match: ?sub_223050@type_222960@@QAEXXZ @ 0x00223050
void type_222960::sub_223050()
{
    if (sub_1ECB40())
    {
        type_21CE60 *var_4 = sub_20E520();

        if (var_4)
        {
            type_1DDE20_mask var_8 = sub_1C48A0();

            var_8.reset(0);
            if (var_8.in(var_4->sub_21D030()))
            {
                sub_1C4C80(2, var_4->sub_21D030());
                sub_1E7CF0()->sub_1E7D90(&unk_170);
                // A compiled-out check on the pause menu (it shifts the
                // registers).
                if (!unk_130)
                {
                }
                if (unk_130)
                    unk_130->sub_21C200(0, 0);
            }
            else
                sub_222D20();
        }
    }
}

// match: ?vf_014@type_222960@@UAEXM@Z @ 0x00223130
void type_222960::vf_014(RwReal arg_0)
{
    type_1DDE20_mask var_4 = sub_1C48A0();

    var_4.unset(0);
    if (!(unk_340 == var_4))
    {
        if (CODFH_DEBUG_LOGS)
            sub_1C8A30("Change in players... refreshing list\n");
        sub_222D20();
    }
}

// match: ?sub_2231A0@type_222960@@QAEXXZ @ 0x002231A0
void type_222960::sub_2231A0()
{
    sub_1E7CF0()->sub_1E7D90(&unk_170);
    vf_040();
}

// The actions' members (game/kujuui.h's template, its definitions
// repeated here).
// match: ??0?$type_3E7CE8@Utype_222960@@@kujuUI@@QAE@PAUtype_222960@@P82@AEXXZ@Z @ 0x002231D0
template <class T> type_3E7CE8<T>::type_3E7CE8(T *arg_0, void (T::*arg_4)())
{
    unk_04 = arg_0;
    unk_08 = arg_4;
}

// match: ??_G?$type_3E7CE8@Utype_222960@@@kujuUI@@UAEPAXI@Z @ 0x00223240
// match: ??1?$type_3E7CE8@Utype_222960@@@kujuUI@@UAE@XZ @ 0x00223220
template <class T> type_3E7CE8<T>::~type_3E7CE8()
{
}

template <class T> void type_3E7CE8<T>::pvf_008()
{
    (unk_04->*unk_08)();
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?vf_038@type_222960@@UAEXXZ (folded into 0x218680)
void type_222960::vf_038()
{
    unk_170.sub_20EA40();
}
