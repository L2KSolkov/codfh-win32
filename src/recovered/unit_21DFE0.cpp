/*
 * A scoreboard's options (game/ingamepages.h): the host's settings, level
 * and countdown, a client's quit and wait, and continuing.
 */
#include "game/ingamepages.h"
#include "game/uiglue.h"
#include "game/kujuui.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003EA46C
extern const RwReal flt_3EA46C = 0.01f;
// 0x003EA470
extern const RwReal flt_3EA470 = 0.01f;
// 0x003EA474
extern const RwReal flt_3EA474 = 16.666666f;
// End of its data definitions.


using namespace kujuUI;

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3EA46C@@3MB @ 0x003EA46C
// match: ?flt_3EA470@@3MB @ 0x003EA470
// match: ?flt_3EA474@@3MB @ 0x003EA474
// match: ??_C@_04PNOAOIAG@wait?$AA@ @ 0x003EA478
// match: ??_C@_0BM@DEDOJIJM@EndRoundHostSettings?4layout?$AA@ @ 0x003EA480
// match: ??_C@_09KPMCIPDA@countdown?$AA@ @ 0x003EA49C
// match: ??_7type_21DFE0@@6B@ @ 0x003EA4A8
// match: ??_C@_0M@GAMAGJKL@Continue?5in?$AA@ @ 0x003EA4F8
// match: ??_7?$type_3E7CE8@Utype_21DFE0@@@kujuUI@@6B@ @ 0x003EA504
// match: ??_7?$type_3E7264@Utype_21DFE0@@@kujuUI@@6B@ @ 0x003EA514
// match: __ehhandler$??0type_21DFE0@@QAE@HPBDPAUtype_21A5E0@@@Z>1>8 @ 0x00425284
// match: __ehhandler$??0type_21DFE0@@QAE@HPBDPAUtype_21A5E0@@@Z>1 @ 0x004252DC
// match: __ehhandler$??1type_21DFE0@@UAE@XZ>1>8 @ 0x004252F8
// match: __ehhandler$??1type_21DFE0@@UAE@XZ>1 @ 0x00425348
// match: __ehhandler$?sub_21E3E0@type_21DFE0@@QAEXXZ>1>8 @ 0x00425364
// match: __ehhandler$?sub_21E3E0@type_21DFE0@@QAEXXZ>1 @ 0x00425374
// match: __ehhandler$?vf_008@type_21DFE0@@UAEXXZ>1>8 @ 0x00425390
// match: __ehhandler$?vf_008@type_21DFE0@@UAEXXZ>1 @ 0x00425398
// match: __ehhandler$?vf_01C@type_21DFE0@@UAE_NHH@Z>1>8 @ 0x004253B4
// match: __ehhandler$?vf_01C@type_21DFE0@@UAE_NHH@Z>1 @ 0x004253BC
// match: __ehhandler$?sub_21E880@type_21DFE0@@QAEXXZ>1>8 @ 0x004253D8
// match: __ehhandler$?sub_21E880@type_21DFE0@@QAEXXZ>1 @ 0x004253F8

// match: ??0type_21DFE0@@QAE@HPBDPAUtype_21A5E0@@@Z @ 0x0021DFE0
// match: __ehhandler$??0type_21DFE0@@QAE@HPBDPAUtype_21A5E0@@@Z-0x91 @ 0x003080C0
// match: __ehhandler$??0type_21DFE0@@QAE@HPBDPAUtype_21A5E0@@@Z @ 0x00308151

type_21DFE0::type_21DFE0(RwInt32 arg_0, const RwChar *arg_4, type_21A5E0 *arg_8)
    : type_21CB10(arg_4, arg_8, 0), unk_154(arg_0), unk_158(this, &type_21DFE0::sub_21E4D0),
      unk_164(this, &type_21DFE0::sub_220A80, &type_21DFE0::sub_21E780), unk_174(this, &type_21DFE0::sub_21E530),
      unk_180(this, &type_21DFE0::sub_21E880), unk_18C(this, &type_21DFE0::sub_1E41C0),
      unk_198(this, &type_21DFE0::sub_21E9A0), unk_1A4(this, &type_21DFE0::sub_1E41C0), unk_1B0(0, &unk_174),
      unk_1F8(0), unk_200(true)
{
    sub_21E3B0();
    if (unk_154 == 1)
    {
        if (sub_1C4BE0())
        {
            sub_204FC0("settings", &unk_158);
            sub_204FC0("Level", &unk_1B0);
            sub_204FC0("countdown", &unk_1D0);
            unk_1F8 = new type_216990("EndRoundHostSettings.layout", "OnlineSettingsAdvanced.layout", this);
        }
        else
        {
            sub_204FC0("quit", &unk_180);
            sub_204FC0("wait", &unk_18C);
        }
    }
    sub_204FC0("continue", &unk_164);
}

// match: ??_Gtype_21DFE0@@UAEPAXI@Z @ 0x0021E260
// match: ??1type_21DFE0@@UAE@XZ @ 0x0021E290
// match: __ehhandler$??1type_21DFE0@@UAE@XZ-0x86 @ 0x00308160
// match: __ehhandler$??1type_21DFE0@@UAE@XZ @ 0x003081E6
type_21DFE0::~type_21DFE0()
{
    delete unk_1F8;
}

// match: ?sub_21E3B0@type_21DFE0@@QAEXXZ @ 0x0021E3B0
void type_21DFE0::sub_21E3B0()
{
    unk_1FC = 10.0f;
    unk_1FC = 0.5f;
}

// The countdown's text: "Continue in" and the seconds left, rounded.
// match: ?sub_21E3E0@type_21DFE0@@QAEXXZ @ 0x0021E3E0
// match: __ehhandler$?sub_21E3E0@type_21DFE0@@QAEXXZ-0x10 @ 0x003081F0
// match: __ehhandler$?sub_21E3E0@type_21DFE0@@QAEXXZ @ 0x00308200
void type_21DFE0::sub_21E3E0()
{
    RwInt32 lv_10;
    type_1CB670 lv_30("Continue in", 0);

    add_text(lv_30, sub_1CB720(" "));
    lv_10 = (RwInt32)(unk_1FC + 0.99f);
    if (lv_10 < 0)
        lv_10 = 0;
    lv_30.sub_214A70(lv_10);
    unk_1D0.sub_1F28C0(lv_30);
}

// match: ?sub_21E4D0@type_21DFE0@@QAEXXZ @ 0x0021E4D0
void type_21DFE0::sub_21E4D0()
{
    if (unk_1F8)
    {
        sub_1E7CF0()->sub_1E7D30(unk_1F8);
        unk_1F8->vf_008();
    }
}

// match: ?sub_21E520@type_21DFE0@@QAEXXZ @ 0x0021E520
void type_21DFE0::sub_21E520()
{
    sub_1C4B90();
}

// match: ?sub_21E530@type_21DFE0@@QAEXXZ @ 0x0021E530
void type_21DFE0::sub_21E530()
{
    if (vf_048())
    {
        type_505188 *var_4 = unk_1B0.sub_1FD030().get_unk_00();

        sub_1C4BA0(((kujuUI::type_1EE900 *)var_4)->sub_1EE9D0());
        sub_21E3B0();
    }
}

// match: ?vf_038@type_21DFE0@@UAEXXZ @ 0x0021E590
void type_21DFE0::vf_038()
{
    if (unk_154 == 2 && sub_1C4BE0())
        unk_200 = false;
}

// match: ?vf_00C@type_21DFE0@@UAEXXZ @ 0x0021E5C0
void type_21DFE0::vf_00C()
{
    if (unk_1F8)
    {
        if (sub_1E7CF0()->sub_1E7D00(unk_1F8))
            sub_1E7CF0()->sub_1E7D90(unk_1F8);
        unk_1F8->vf_00C();
    }
    sub_2172A0();
    type_21CB10::vf_00C();
}

// match: ?vf_008@type_21DFE0@@UAEXXZ @ 0x0021E630
// match: __ehhandler$?vf_008@type_21DFE0@@UAEXXZ-0x8 @ 0x00308210
// match: __ehhandler$?vf_008@type_21DFE0@@UAEXXZ @ 0x00308218
void type_21DFE0::vf_008()
{
    type_21CB10::vf_008();
    if (unk_154 == 1)
    {
        type_211860_key var_10(picked_level());

        unk_1B0.sub_201EC0(var_10);
    }
    if (unk_1F8)
        unk_1F8->vf_008();
}

// match: ?vf_014@type_21DFE0@@UAEXM@Z @ 0x0021E6D0
void type_21DFE0::vf_014(RwReal arg_0)
{
    type_21CB10::vf_014(arg_0);
    if (arg_0 > 0.0f && !sub_1E7CF0()->sub_1E7D00(unk_1F8))
    {
        sub_21E3E0();
        unk_1FC -= arg_0;
        if (unk_1FC < 0.0f)
            sub_21E520();
    }
}

// match: ?vf_04C@type_21DFE0@@UAEXXZ @ 0x0021E760
void type_21DFE0::vf_04C()
{
    unk_200 = true;
}

// match: ?sub_21E780@type_21DFE0@@QAE_NXZ @ 0x0021E780
bool type_21DFE0::sub_21E780()
{
    return unk_200;
}

// match: ?vf_01C@type_21DFE0@@UAE_NHH@Z @ 0x0021E7A0
// match: __ehhandler$?vf_01C@type_21DFE0@@UAE_NHH@Z-0x8 @ 0x00308230
// match: __ehhandler$?vf_01C@type_21DFE0@@UAE_NHH@Z @ 0x00308238
bool type_21DFE0::vf_01C(RwInt32 arg_0, RwInt32 arg_4)
{
    switch (arg_0)
    {
    case 1:
    {
        sub_1E7CF0()->sub_1E7D90(unk_1F8);
        type_211860_key var_14(picked_level());

        unk_1B0.sub_201EC0(var_14);
        type_505188 *lv_10 = unk_1B0.sub_1FD030().get_unk_00();

        sub_1C4BA0(((kujuUI::type_1EE900 *)lv_10)->sub_1EE9D0());
        sub_21E3B0();
        return true;
    }
    }
    return type_21CB10::vf_01C(arg_0, arg_4);
}

// "quit": asks whether to quit the game, "yes" and "no" running unk_198 and
// unk_1A4 (unk_1A4 also on backing out).
// match: ?sub_21E880@type_21DFE0@@QAEXXZ @ 0x0021E880
// match: __ehhandler$?sub_21E880@type_21DFE0@@QAEXXZ-0x20 @ 0x00308250
// match: __ehhandler$?sub_21E880@type_21DFE0@@QAEXXZ @ 0x00308270
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_21DFE0::sub_21E880()
{
    type_1CB670 var_2C("QUIT_GAME", 0);
    type_1CB670 local_80("QUIT_GAME?", 0);
    type_1CB670 loc64("Yes", 0);
    type_1CB670 local_48("No", 0);

    sub_2171F0(var_2C, local_80, loc64, &unk_198, local_48, &unk_1A4, &unk_1A4);
}

// match: ?sub_21E9A0@type_21DFE0@@QAEXXZ @ 0x0021E9A0
void type_21DFE0::sub_21E9A0()
{
    sub_1C44A0();
}

// match: ?vf_024@type_21DFE0@@UAEHXZ @ 0x0021E9B0
RwInt32 type_21DFE0::vf_024()
{
    if (unk_1F8)
        return 0x32;
    if (unk_200)
    {
        if (!sub_1C4BE0())
            return 0x12;
        return 2;
    }
    return 0;
}

// The actions' members (game/kujuui.h's templates, their definitions
// repeated here).
// match: ??0?$type_3E7CE8@Utype_21DFE0@@@kujuUI@@QAE@PAUtype_21DFE0@@P82@AEXXZ@Z @ 0x0021EA00
template <class T> type_3E7CE8<T>::type_3E7CE8(T *arg_0, void (T::*arg_4)())
{
    unk_04 = arg_0;
    unk_08 = arg_4;
}

// match: ??_G?$type_3E7CE8@Utype_21DFE0@@@kujuUI@@UAEPAXI@Z @ 0x0021EAD0
// match: ??1?$type_3E7CE8@Utype_21DFE0@@@kujuUI@@UAE@XZ @ 0x0021EA40
template <class T> type_3E7CE8<T>::~type_3E7CE8()
{
}

template <class T> void type_3E7CE8<T>::pvf_008()
{
    (unk_04->*unk_08)();
}

// match: ??0?$type_3E7264@Utype_21DFE0@@@kujuUI@@QAE@PAUtype_21DFE0@@P82@AEXXZP82@AE_NXZ@Z @ 0x0021EA60
template <class T> type_3E7264<T>::type_3E7264(T *arg_0, void (T::*arg_4)(), bool (T::*arg_C)())
{
    unk_04 = arg_0;
    unk_08 = arg_4;
    unk_10 = arg_C;
}

// match: ??_G?$type_3E7264@Utype_21DFE0@@@kujuUI@@UAEPAXI@Z @ 0x0021EB00
// match: ??1?$type_3E7264@Utype_21DFE0@@@kujuUI@@UAE@XZ @ 0x0021EAB0
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

// Members /OPT:ICF folded into shared trivial bodies (config/aliases.txt): defined here for
// the authentic link (PLAN M7); the placement link takes the shared bodies.

// ?sub_1E41C0@type_21DFE0@@QAEXXZ (folded into the empty body at 0x1E41C0)
void type_21DFE0::sub_1E41C0()
{
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?sub_220A80@type_21DFE0@@QAEXXZ (folded into 0x220A80)
void type_21DFE0::sub_220A80()
{
    sub_1C4B10();
}
