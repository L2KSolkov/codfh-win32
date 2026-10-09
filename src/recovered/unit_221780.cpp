/*
 * A vote's confirmation (game/ingamepages.h): "ok" carries the vote out and
 * "cancel" takes the confirmation off the pad's widget stack. Its question
 * (sub_221A80) is built in a fixed buffer, with a compiled-out debug print.
 */
#include <stdio.h>
#include "game/ingamepages.h"
#include "game/uiglue.h"
#include "game/mpgame.h"
#include "game/loc.h"

// Its data definitions (PLAN M5), in the image's address order.
#ifndef CODFH_SP // MP only: unreferenced constants single player does not emit (not in default.xbe; /O2 keeps them only while they are external)
// 0x003EA860
extern const RwReal flt_3EA860 = 0.01f;
// 0x003EA864
extern const RwReal flt_3EA864 = 0.01f;
// 0x003EA868
extern const RwReal flt_3EA868 = 16.666666f;
#endif
// End of its data definitions.


using namespace kujuUI;

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3EA860@@3MB @ 0x003EA860
// match: ?flt_3EA864@@3MB @ 0x003EA864
// match: ?flt_3EA868@@3MB @ 0x003EA868
// match: ??_C@_06JDKABGKH@cancel?$AA@ @ 0x003EA86C
// match: ??_C@_02MFDMBIJM@ok?$AA@ @ 0x003EA874
// match: ??_C@_0BG@MDIMHNFH@WillStartRound?4layout?$AA@ @ 0x003EA878
// match: ??_7type_221780@@6B@ @ 0x003EA890
// match: ??_C@_02PHMGELLB@?6?6?$AA@ @ 0x003EA8EC
// match: ??_C@_0N@PGBHIHP@vote?$CF1kick?$CF2?$AA@ @ 0x003EA8F0
// match: ??_C@_0BB@DFCKPDDH@vote?$CF1gamemode?$CF2?$AA@ @ 0x003EA900
// match: ??_C@_0M@HCFEGODI@vote?$CF1map?$CF2?$AA@ @ 0x003EA914
// match: ??_C@_09BNPOCOIJ@?$CFuyes?$CFuno?$AA@ @ 0x003EA920
// match: ??_7?$type_3E7CE8@Utype_221780@@@kujuUI@@6B@ @ 0x003EA92C
// match: __ehhandler$??0type_221780@@QAE@PBDPAUtype_21A5E0@@@Z>1>8 @ 0x004258A8
// match: __ehhandler$??0type_221780@@QAE@PBDPAUtype_21A5E0@@@Z>1 @ 0x004258C8
// match: __ehhandler$??1type_221780@@UAE@XZ>1>8 @ 0x004258E4
// match: __ehhandler$??1type_221780@@UAE@XZ>1 @ 0x004258FC
// match: __ehhandler$?vf_058@type_221780@@UAE?AUtype_1CB670@@XZ>1>8 @ 0x00425918
// match: __ehhandler$?vf_058@type_221780@@UAE?AUtype_1CB670@@XZ>1 @ 0x00425980

// match: ??0type_221780@@QAE@PBDPAUtype_21A5E0@@@Z @ 0x00221780
// match: __ehhandler$??0type_221780@@QAE@PBDPAUtype_21A5E0@@@Z-0x32 @ 0x00308830
// match: __ehhandler$??0type_221780@@QAE@PBDPAUtype_21A5E0@@@Z @ 0x00308862

type_221780::type_221780(const RwChar *arg_0, type_21A5E0 *arg_4)
    : type_216130(arg_0, arg_4), unk_194("WillStartRound.layout", 0, false),
      unk_31C(this, &type_221780::sub_2219A0), unk_328(this, &type_221780::sub_2219E0), unk_334(-1), unk_338(0)
{
    unk_194.sub_204FC0("ok", &unk_31C);
    unk_194.sub_204FC0("cancel", &unk_328);
}

// match: ??_Gtype_221780@@UAEPAXI@Z @ 0x00221880
// match: ??1type_221780@@UAE@XZ @ 0x002218B0
// match: __ehhandler$??1type_221780@@UAE@XZ-0x24 @ 0x00308870
// match: __ehhandler$??1type_221780@@UAE@XZ @ 0x00308894
type_221780::~type_221780()
{
}

// match: ?vf_008@type_221780@@UAEXXZ @ 0x00221930
void type_221780::vf_008()
{
    type_216130::vf_008();
}

// match: ?vf_00C@type_221780@@UAEXXZ @ 0x00221950
void type_221780::vf_00C()
{
    if (sub_1E7CF0()->sub_1E7D00(&unk_194))
        sub_1E7CF0()->sub_1E7D90(&unk_194);
    type_21CB10::vf_00C();
}

// match: ?sub_2219A0@type_221780@@QAEXXZ @ 0x002219A0
void type_221780::sub_2219A0()
{
    sub_1E7CF0()->sub_1E7D90(&unk_194);
    unk_130->sub_21C200(0, 0);
    sub_1C4E50();
    sub_221FC0();
}

// match: ?sub_2219E0@type_221780@@QAEXXZ @ 0x002219E0
void type_221780::sub_2219E0()
{
    sub_1E7CF0()->sub_1E7D90(&unk_194);
}

// match: ?vf_050@type_221780@@UAEXXZ @ 0x00221A00
void type_221780::vf_050()
{
    if (unk_334 == 2)
    {
        unk_130->sub_21C200(0, 0);
        sub_1C4E50();
        sub_221FC0();
    }
    else
        sub_1E7CF0()->sub_1E7D30(&unk_194);
}

// match: ?vf_054@type_221780@@UAEXXZ @ 0x00221A50
void type_221780::vf_054()
{
    sub_1C4E50();
    unk_130->sub_21C200(0, 0);
}

// The question: the vote (the level, the game type or a player's kick) and
// who called it, then the votes for and against.
// match: ?vf_058@type_221780@@UAE?AUtype_1CB670@@XZ @ 0x00221A80
// match: __ehhandler$?vf_058@type_221780@@UAE?AUtype_1CB670@@XZ-0x9A @ 0x003088A0
// match: __ehhandler$?vf_058@type_221780@@UAE?AUtype_1CB670@@XZ @ 0x0030893A
type_1CB670 type_221780::vf_058()
{
    type_1CB670 text;
    type_1CB670 stk_2C("%uyes%uno", 0);
    type_1CB670 var_64;
    RwChar local_164[256];
    RwUInt32 var_168;
    RwUInt32 var_16C;

    unk_334 = sub_1C4D60();
    unk_338 = sub_1C4D80();
    sub_1C4DA0(&var_16C, &var_168);
    var_64 = sub_1C4DD0();
    switch (unk_334)
    {
    case 0:
        {
            type_1CB670 var_1A4("vote%1map%2", 0);
            type_1CB670 bp_188(sub_1C4590(unk_338), 0);

            sub_1CB0F0(local_164, var_1A4.c_str(), var_64.c_str(), bp_188.c_str());
        }
        break;
    case 1:
        {
            type_1CB670 var_1C0("vote%1gamemode%2", 0);
            type_1CB670 var1DC(sub_1C4E60(unk_338), 0);

            sub_1CB0F0(local_164, var_1C0.c_str(), var_64.c_str(), var1DC.c_str());
        }
        break;
    case 2:
        {
            type_1CB670 lv_1F8("vote%1kick%2", 0);
            {
                RwChar *lv_1FC = sub_1C4630(unk_338);

                sub_1CB0F0(local_164, lv_1F8.c_str(), var_64.c_str(), lv_1FC);
            }
        }
        break;
    }
    text = sub_1CB720(local_164);
    add_text(text, sub_1CB720("\n\n"));
    sprintf(local_164, stk_2C.c_str(), var_16C, var_168);
    debug_text(local_164);
    add_text(text, sub_1CB720(local_164));
    return text;
}

// match: ?sub_221FC0@type_221780@@QAEXXZ @ 0x00221FC0
void type_221780::sub_221FC0()
{
    switch (unk_334)
    {
    case 0:
        sub_1C3D20();
        sub_1C3D80(unk_338);
        sub_1C3D60(1);
        break;
    case 1:
        sub_1C3D20();
        unk_4FDBB0.set_unk_00(unk_338);
        sub_1C3D60(1);
        break;
    case 2:
        sub_1C4560(unk_338);
        break;
    }
}

// The actions' members (game/kujuui.h's template, its definitions
// repeated here).
// match: ??0?$type_3E7CE8@Utype_221780@@@kujuUI@@QAE@PAUtype_221780@@P82@AEXXZ@Z @ 0x00222050
template <class T> type_3E7CE8<T>::type_3E7CE8(T *arg_0, void (T::*arg_4)())
{
    unk_04 = arg_0;
    unk_08 = arg_4;
}

// match: ??_G?$type_3E7CE8@Utype_221780@@@kujuUI@@UAEPAXI@Z @ 0x002220B0
// match: ??1?$type_3E7CE8@Utype_221780@@@kujuUI@@UAE@XZ @ 0x00222090
template <class T> type_3E7CE8<T>::~type_3E7CE8()
{
}

template <class T> void type_3E7CE8<T>::pvf_008()
{
    (unk_04->*unk_08)();
}
