/*
 * kujuUI's editbox (game/kujuui.h): a text field typed on the on-screen
 * keyboard, kept in a text source, with actions over its own methods (a
 * template over the owner), and its creator ("editbox").
 */
#include "game/kujuui.h"
#include "game/parsedfile.h"
#include "game/frontend.h"
#include "types/type_4D1DB8.h"
// Vtables (.rdata, PLAN M5): each in its own placement range (config/splits.txt).
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_7type_3E7228@kujuUI@@6B@ @ 0x003E7204
// match: ??_7type_3E7228@kujuUI@@6Btype_3E76E4@1@@ @ 0x003E7210
// match: ??_7type_3E7228@kujuUI@@6Btype_3E75E8@1@@ @ 0x003E7214
// match: ??_7type_3E7228@kujuUI@@6Btype_3E7D08@1@@ @ 0x003E7228
// match: ??_7type_3E7258@kujuUI@@6B@ @ 0x003E7258
// match: ??_7?$type_3E7264@Utype_3E7228@kujuUI@@@kujuUI@@6B@ @ 0x003E7264
// match: ??_7type_1ED670_object@kujuUI@@6B@ @ 0x003E7274
// match: __ehhandler$??0type_3E7228@kujuUI@@QAE@PBD000HIIPBUtype_1E0330_rect@1@1HPAUtype_1ED670_object@1@2PAUtype_1F28C0@1@PAUtype_3E7D08@1@@Z>1>8 @ 0x0041FF58
// match: __ehhandler$??0type_3E7228@kujuUI@@QAE@PBD000HIIPBUtype_1E0330_rect@1@1HPAUtype_1ED670_object@1@2PAUtype_1F28C0@1@PAUtype_3E7D08@1@@Z>1 @ 0x0041FF80
// match: __ehhandler$??1type_3E7228@kujuUI@@UAE@XZ>1>8 @ 0x0041FF9C
// match: __ehhandler$??1type_3E7228@kujuUI@@UAE@XZ>1 @ 0x0041FFBC
// match: __ehhandler$?vf_014@type_3E7228@kujuUI@@UAEXM@Z>1>8 @ 0x0041FFD8
// match: __ehhandler$?vf_014@type_3E7228@kujuUI@@UAEXM@Z>1 @ 0x0041FFE8


namespace kujuUI {

// match: ??0type_3E7228@kujuUI@@QAE@PBD000HIIPBUtype_1E0330_rect@1@1HPAUtype_1ED670_object@1@2PAUtype_1F28C0@1@PAUtype_3E7D08@1@@Z @ 0x001E4250
// match: __ehhandler$??0type_3E7228@kujuUI@@QAE@PBD000HIIPBUtype_1E0330_rect@1@1HPAUtype_1ED670_object@1@2PAUtype_1F28C0@1@PAUtype_3E7D08@1@@Z-0x3D @ 0x003039B0
// match: __ehhandler$??0type_3E7228@kujuUI@@QAE@PBD000HIIPBUtype_1E0330_rect@1@1HPAUtype_1ED670_object@1@2PAUtype_1F28C0@1@PAUtype_3E7D08@1@@Z @ 0x003039ED
type_3E7228::type_3E7228(const RwChar *arg_0, const RwChar *arg_4, const RwChar *arg_8, const RwChar *arg_C,
                         RwInt32 arg_10, RwUInt32 arg_14, RwUInt32 arg_18, const type_1E0330_rect *arg_1C,
                         const type_1E0330_rect *arg_20, RwInt32 arg_24, type_1ED670_object *arg_28,
                         type_1ED670_object *arg_2C, type_1F28C0 *arg_30, type_3E7D08 *arg_34)
    : type_3E7BCC(arg_0, arg_4, arg_10, arg_1C, arg_20, arg_24, &unk_100, arg_2C, arg_34), unk_F4(0),
      unk_F8(arg_30), unk_100(this, &type_3E7228::sub_1E4BB0, &type_3E7228::sub_1E4BE0),
      unk_118(this, &type_3E7228::pDtor, &type_3E7228::sub_1E4BE0), unk_130(arg_28), unk_134(false)
{
    unk_F4 = new type_1F5D70(arg_8, arg_C, arg_4, arg_14, arg_18, arg_1C, arg_20, arg_24, arg_28, this);
    if (unk_F8)
    {
        const type_1A5EA0 &var_10 = unk_F8->unk_08;
        sub_1F51B0(var_10.c_str());
        sub_1F5250(var_10.size());
        unk_F8->sub_1E7540(this);
    }
}

// match: ??_Gtype_3E7228@kujuUI@@UAEPAXI@Z @ 0x001E44B0

// match: ??1type_3E7228@kujuUI@@UAE@XZ @ 0x001E44E0
// match: __ehhandler$??1type_3E7228@kujuUI@@UAE@XZ-0x4D @ 0x00303A00
// match: __ehhandler$??1type_3E7228@kujuUI@@UAE@XZ @ 0x00303A4D
type_3E7228::~type_3E7228()
{
    delete unk_F4;
}

// match: ?vf_014@type_3E7228@kujuUI@@UAEXM@Z @ 0x001E45D0
// match: __ehhandler$?vf_014@type_3E7228@kujuUI@@UAEXM@Z-0x10 @ 0x00303A60
// match: __ehhandler$?vf_014@type_3E7228@kujuUI@@UAEXM@Z @ 0x00303A70
void type_3E7228::vf_014(RwReal arg_0)
{
    RwInt32 var_10 = 0;

    if (unk_134)
    {
        switch (unk_F4->get_unk_188())
        {
        case 2:
        {
            type_1A5EA0 var_30 = unk_F4->sub_1F7310();
            sub_1F51B0(var_30.c_str());
            sub_1F5250(unk_F4->sub_1F73B0());
            if (unk_F8)
                unk_F8->sub_1F28C0(sub_1CB720(var_30.c_str()));
            unk_134 = false;
            sub_1E7CF0()->sub_1E7D90(unk_F4);
            vf_01C(0, 0);
            break;
        }
        case 1:
            unk_134 = false;
            sub_1E7CF0()->sub_1E7D90(unk_F4);
            break;
        }
    }
    else
    {
        sub_1F7720();
        // A compiled-out check: the registers after it are one load on
        // (docs/toolchain.md).
        if (!unk_F4)
        {
        }
    }
    if (unk_134 && unk_F4 && unk_F4->get_unk_188() == 0)
    {
        unk_F4->vf_014(arg_0);
        unk_F4->sub_1F73D0(var_10);
    }
}

// match: ?vf_018@type_3E7228@kujuUI@@UAEXPAUtype_1E4130@2@@Z @ 0x001E47F0
void type_3E7228::vf_018(type_1E4130 *arg_0)
{
    type_3E76B4::vf_018(arg_0);
    if (sub_1E4AA0() && sub_1F7720() && (!unk_F4 || unk_F4->get_unk_188() != 0))
        static_cast<type_3E7D08 *>(&unk_BC)->vf_018(arg_0);
    unk_1C.sub_1F1B10(arg_0);
}

// match: ?processEvent@type_3E7228@kujuUI@@UAE?AW4eEventWasHandled@2@ABVcStateChange@2@@Z @ 0x001E4880
eEventWasHandled type_3E7228::processEvent(const cStateChange &arg_0)
{
    eEventWasHandled var_4 = (eEventWasHandled)1;

    switch (arg_0.get_unk_00())
    {
    case 4:
        if (arg_0.get_unk_04() == 1)
        {
            sub_1E4980();
            if (dword_504378)
                dword_504378->vf_04(2);
        }
        var_4 = (eEventWasHandled)0;
        break;
    case 8:
        if (arg_0.get_unk_04() == 0)
        {
            sub_1E4AB0(0x22B2);
            if (dword_504378)
                dword_504378->vf_04(1);
        }
        var_4 = (eEventWasHandled)0;
        break;
    case 9:
        if (arg_0.get_unk_04() == 0)
        {
            sub_1E4AB0(0x22B3);
            if (dword_504378)
                dword_504378->vf_04(1);
        }
        var_4 = (eEventWasHandled)0;
        break;
    }
    return var_4;
}

// match: ?sub_1E4980@type_3E7228@kujuUI@@QAEXXZ @ 0x001E4980
void type_3E7228::sub_1E4980()
{
    unk_134 = true;
    unk_F4->sub_1F7370(sub_1F5230().c_str());
    if (sub_1E4AA0())
        unk_F4->sub_1F7390(sub_CB0A0());
    else
        unk_F4->sub_1F7390(sub_1F5230().size());
    sub_1E7CF0()->sub_1E7D30(unk_F4);
}

// match: ?pvf_004@type_3E7228@kujuUI@@UAEXH@Z @ 0x001E4A40
void type_3E7228::pvf_004(RwInt32 arg_0)
{
    unk_1C.sub_1F1E00(arg_0);
}

// match: ?pvf_008@type_3E7228@kujuUI@@UAEXABUtype_1A5EA0@@@Z @ 0x001E4A60
void type_3E7228::pvf_008(const type_1A5EA0 &arg_0)
{
    sub_1F51B0(arg_0.c_str());
}

// match: ?sub_1E4AA0@type_3E7228@kujuUI@@QAE_NXZ @ 0x001E4AA0
bool type_3E7228::sub_1E4AA0()
{
    return false;
}

// match: ?sub_1E4AB0@type_3E7228@kujuUI@@QAEXH@Z @ 0x001E4AB0
void type_3E7228::sub_1E4AB0(RwInt32 arg_0)
{
    if (arg_0)
    {
        sub_1F52C0(arg_0);
        if (unk_F8)
            unk_F8->sub_1F28C0(sub_1F5230());
    }
}

// match: ?vf_008@type_3E7228@kujuUI@@UAEXXZ @ 0x001E4B00
void type_3E7228::vf_008()
{
    type_3E7BCC::vf_008();
    if (unk_F4)
        unk_F4->vf_008();
}

// match: ?vf_00C@type_3E7228@kujuUI@@UAEXXZ @ 0x001E4B40
void type_3E7228::vf_00C()
{
    if (unk_134)
    {
        unk_134 = false;
        sub_1E7CF0()->sub_1E7D90(unk_F4);
    }
    if (unk_F4)
        unk_F4->vf_00C();
    type_3E7BCC::vf_00C();
}

// match: ?sub_1E4BB0@type_3E7228@kujuUI@@QAEXXZ @ 0x001E4BB0
void type_3E7228::sub_1E4BB0()
{
    if (unk_130)
        unk_130->pvf_008();
}

// match: ?sub_1E4BE0@type_3E7228@kujuUI@@QAE_NXZ @ 0x001E4BE0
bool type_3E7228::sub_1E4BE0()
{
    return unk_130 ? unk_130->pvf_00C() : 1 && unk_F4->sub_1F6EF0();
}

// match: ??0?$type_3E7264@Utype_3E7228@kujuUI@@@kujuUI@@QAE@PAUtype_3E7228@1@P821@AEXXZP821@AE_NXZ@Z @ 0x001E4C50
template <class T> type_3E7264<T>::type_3E7264(T *arg_0, void (T::*arg_4)(), bool (T::*arg_C)())
{
    unk_04 = arg_0;
    unk_08 = arg_4;
    unk_10 = arg_C;
}

// match: ?vf_000@type_1ED670_object@kujuUI@@UAEHXZ @ 0x001E4CB0

// match: ??1?$type_3E7264@Utype_3E7228@kujuUI@@@kujuUI@@UAE@XZ @ 0x001E4CC0
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

template struct type_3E7264<type_3E7228>;

// match: ??_G?$type_3E7264@Utype_3E7228@kujuUI@@@kujuUI@@UAEPAXI@Z @ 0x001E4CE0

// match: ??_Etype_3E7228@kujuUI@@WM@AEPAXI@Z @ 0x001E4D10
// match: ??_Etype_3E7228@kujuUI@@WPA@AEPAXI@Z @ 0x001E4D20







}

namespace kujuUI
{

}

// Empty and out of line (folded by /OPT:ICF into the shared pDtor, 0x1E41C0).
void kujuUI::type_3E7228::pDtor()
{
}
