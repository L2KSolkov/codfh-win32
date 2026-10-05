/*
 * kujuUI's text field (game/kujuui.h): a selectable widget with a text and
 * a caret, typed into a key at a time (the escape and enter keys run its
 * actions, the pad's keys move the caret and delete).
 */
#include "game/kujuui.h"
#include "types/type_4D1DB8.h"

using namespace kujuUI;

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_7type_3E7BCC@kujuUI@@6Btype_3E76E4@1@@ @ 0x003E7BB4
// match: ??_7type_3E7BCC@kujuUI@@6Btype_3E75E8@1@@ @ 0x003E7BB8
// match: ??_7type_3E7BCC@kujuUI@@6Btype_3E7D08@1@@ @ 0x003E7BCC
// match: __ehhandler$??0type_3E7BCC@kujuUI@@QAE@PBD0HPBUtype_1E0330_rect@1@1HPAUtype_1ED670_object@1@2PAUtype_3E7D08@1@@Z>1>8 @ 0x00421210
// match: __ehhandler$??0type_3E7BCC@kujuUI@@QAE@PBD0HPBUtype_1E0330_rect@1@1HPAUtype_1ED670_object@1@2PAUtype_3E7D08@1@@Z>1 @ 0x00421228
// match: __ehhandler$??1type_3E7BCC@kujuUI@@UAE@XZ>1>8 @ 0x00421244
// match: __ehhandler$??1type_3E7BCC@kujuUI@@UAE@XZ>1 @ 0x00421254
// match: __ehhandler$?sub_1F52C0@type_3E7BCC@kujuUI@@QAEXI@Z>1>8 @ 0x00421270
// match: __ehhandler$?sub_1F52C0@type_3E7BCC@kujuUI@@QAEXI@Z>1 @ 0x00421288

// match: ??0type_3E7BCC@kujuUI@@QAE@PBD0HPBUtype_1E0330_rect@1@1HPAUtype_1ED670_object@1@2PAUtype_3E7D08@1@@Z @ 0x001F4D00
// match: __ehhandler$??0type_3E7BCC@kujuUI@@QAE@PBD0HPBUtype_1E0330_rect@1@1HPAUtype_1ED670_object@1@2PAUtype_3E7D08@1@@Z-0x21 @ 0x00304870
// match: __ehhandler$??0type_3E7BCC@kujuUI@@QAE@PBD0HPBUtype_1E0330_rect@1@1HPAUtype_1ED670_object@1@2PAUtype_3E7D08@1@@Z @ 0x00304891

type_3E7BCC::type_3E7BCC(const RwChar *arg_0, const RwChar *arg_4, RwInt32 arg_8, const type_1E0330_rect *arg_C,
                         const type_1E0330_rect *arg_10, RwInt32 arg_14, type_1ED670_object *arg_18,
                         type_1ED670_object *arg_1C, type_3E7D08 *arg_20)
    : type_3E76B4(arg_0, arg_C, arg_20), unk_1C(arg_8, arg_C, 1, true), unk_B8(arg_14), unk_BC(arg_4, arg_10, this),
      unk_E4(0), unk_E8(arg_18), unk_EC(arg_1C)
{
    sub_1F51B0("");
    unk_E4 = sub_1F5230().size();
    sub_1F5070();
    unk_1C.sub_1F2410(false);
}

// match: ??_Gtype_3E7BCC@kujuUI@@UAEPAXI@Z @ 0x001F4E20

// match: ??1type_3E7BCC@kujuUI@@UAE@XZ @ 0x001F4E50
// match: __ehhandler$??1type_3E7BCC@kujuUI@@UAE@XZ-0x13 @ 0x003048A0
// match: __ehhandler$??1type_3E7BCC@kujuUI@@UAE@XZ @ 0x003048B3
type_3E7BCC::~type_3E7BCC()
{
}

// match: ?vf_008@type_3E7BCC@kujuUI@@UAEXXZ @ 0x001F4ED0
void type_3E7BCC::vf_008()
{
    unk_E4 = unk_1C.unk_54.size();
    sub_1F5070();
    unk_1C.sub_1F1AA0();
    type_3E7D08::vf_008();
}

// match: ?vf_00C@type_3E7BCC@kujuUI@@UAEXXZ @ 0x001F4F10
void type_3E7BCC::vf_00C()
{
    unk_1C.sub_1F1AD0();
    type_3E7D08::vf_00C();
}

// match: ?givenFocus@type_3E7BCC@kujuUI@@UAEXXZ @ 0x001F4F30
void type_3E7BCC::givenFocus()
{
    RwInt32 var_4 = sub_1F5800() ? 1 : 4;
    unk_1C.sub_1F1E00(var_4);
    sub_1EFFA0(var_4);
}

// match: ?lostFocus@type_3E7BCC@kujuUI@@UAEXXZ @ 0x001F4F70
void type_3E7BCC::lostFocus()
{
    RwInt32 var_4 = sub_1F5800() ? 0 : 3;
    unk_1C.sub_1F1E00(var_4);
    sub_1EFFA0(var_4);
}

// match: ?vf_018@type_3E7BCC@kujuUI@@UAEXPAUtype_1E4130@2@@Z @ 0x001F4FB0
void type_3E7BCC::vf_018(type_1E4130 *arg_0)
{
    type_3E76B4::vf_018(arg_0);
    static_cast<type_3E7D08 &>(unk_BC).vf_018(arg_0);
    unk_1C.sub_1F1B10(arg_0);
}

// match: ?vf_014@type_3E7BCC@kujuUI@@UAEXM@Z @ 0x001F5000
void type_3E7BCC::vf_014(RwReal arg_0)
{
    static_cast<type_3E7D08 &>(unk_BC).vf_014(arg_0);
}

// match: ?processEvent@type_3E7BCC@kujuUI@@UAE?AW4eEventWasHandled@2@ABVcStateChange@2@@Z @ 0x001F5030
eEventWasHandled type_3E7BCC::processEvent(const cStateChange &arg_0)
{
    switch (arg_0.get_unk_00())
    {
    case 4:
    case 8:
    case 9:
        return (eEventWasHandled)1;
    }
    return (eEventWasHandled)0;
}

// match: ?sub_1F5070@type_3E7BCC@kujuUI@@QAEXXZ @ 0x001F5070
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3E7BCC::sub_1F5070()
{
    RwInt32 var_10 = unk_1C.sub_1F1ED0(sub_1F5230().c_str(), -1);
    RwInt32 stk_C = unk_1C.sub_1F1ED0(sub_1F5230().c_str(), unk_E4);
    const type_1E0330_rect *lv_14 = static_cast<type_3E76B4 *>(this)->pvf_004();
    RwReal var_4 = (lv_14->unk_00 + lv_14->unk_08) / 2.0f - var_10 / 2 + stk_C;
    RwReal v8 = lv_14->unk_0C - static_cast<type_3E76B4 &>(unk_BC).pvf_004()->height();
    var_4 -= static_cast<type_3E76B4 &>(unk_BC).pvf_004()->width() / 2.0f;
    unk_BC.sub_1EEA30((RwUInt32)var_4, (RwUInt32)v8);
}

// match: ?sub_1F51B0@type_3E7BCC@kujuUI@@QAEXPBD@Z @ 0x001F51B0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3E7BCC::sub_1F51B0(const RwChar *arg_0)
{
    unk_1C.sub_1F1D70(arg_0);
    const type_1E0330_rect *local_8 = static_cast<type_3E76B4 *>(this)->pvf_004();
    static_cast<type_3E75E8 &>(unk_1C).pvf_008(local_8);
    RwUInt32 var_4 = sub_1F5230().size();
    if (unk_E4 > var_4)
        unk_E4 = var_4;
    sub_1F5070();
}

// match: ?sub_1F5230@type_3E7BCC@kujuUI@@QAEABUtype_1A5EA0@@XZ @ 0x001F5230
const type_1A5EA0 &type_3E7BCC::sub_1F5230()
{
    return unk_1C.unk_54;
}

// match: ?sub_1F5250@type_3E7BCC@kujuUI@@QAEXI@Z @ 0x001F5250
void type_3E7BCC::sub_1F5250(RwUInt32 arg_0)
{
    if (arg_0 > sub_1F5230().size())
        unk_E4 = sub_1F5230().size();
    else
        unk_E4 = arg_0;
    sub_1F5070();
}

// match: ??_Etype_3E7BCC@kujuUI@@WM@AEPAXI@Z @ 0x001F5860

// match: ?sub_1F52C0@type_3E7BCC@kujuUI@@QAEXI@Z @ 0x001F52C0
// match: __ehhandler$?sub_1F52C0@type_3E7BCC@kujuUI@@QAEXI@Z-0x18 @ 0x003048C0
// match: __ehhandler$?sub_1F52C0@type_3E7BCC@kujuUI@@QAEXI@Z @ 0x003048D8
void type_3E7BCC::sub_1F52C0(RwUInt32 arg_0)
{
    if (arg_0 == 0x1B)
    {
        if (unk_EC && unk_EC->pvf_00C())
            unk_EC->pvf_008();
    }
    else if (arg_0 < 0x20)
        ;
    else if (arg_0 < 0x10000 && arg_0 != 0x22B2 && arg_0 != 0x22B3)
    {
        if (sub_1F5230().size() < (RwUInt32)unk_B8)
        {
            type_1A5EA0 var_2C(sub_1F5230());
            var_2C.sub_1C8300(unk_E4, (RwChar)arg_0);
            if ((RwReal)unk_1C.sub_1F1ED0(var_2C.c_str(), -1) < static_cast<type_3E76B4 *>(this)->pvf_004()->width())
            {
                sub_1F51B0(var_2C.c_str());
                ++unk_E4;
                if (unk_E4 > var_2C.size())
                    unk_E4 = var_2C.size();
                sub_1F5070();
            }
        }
    }
    else
    {
        switch (arg_0)
        {
        case 0x10000:
            if (unk_E4 > 0)
            {
                --unk_E4;
                type_1A5EA0 var_48(sub_1F5230());
                var_48.sub_1C8330(unk_E4, 1);
                sub_1F51B0(var_48.c_str());
                sub_1F5070();
            }
            break;
        case 0x10001:
            if (text_length() > 0)
            {
                type_1A5EA0 var_64(sub_1F5230());
                var_64.sub_1C8330(unk_E4, 1);
                sub_1F51B0(var_64.c_str());
                sub_1F5070();
            }
            break;
        case 0x22B2:
            if (unk_E4 > 0)
            {
                --unk_E4;
                sub_1F5070();
            }
            break;
        case 0x22B3:
            if (unk_E4 < sub_1F5230().size())
            {
                ++unk_E4;
                sub_1F5070();
            }
            break;
        case 0x1000B:
            if (unk_E8 && unk_E8->pvf_00C())
                unk_E8->pvf_008();
            break;
        }
    }
}

// match: ?sub_1F5800@type_3E7BCC@kujuUI@@QAE_NXZ @ 0x001F5800
bool type_3E7BCC::sub_1F5800()
{
    return unk_E8 ? unk_E8->pvf_00C() : true;
}

// match: ?sub_1F5840@type_3E7BCC@kujuUI@@QAEHXZ @ 0x001F5840
RwInt32 type_3E7BCC::sub_1F5840()
{
    return unk_B8;
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?sub_CB0A0@type_3E7BCC@kujuUI@@QAEHXZ (folded into 0xCB0A0)
RwInt32 kujuUI::type_3E7BCC::sub_CB0A0()
{
    return unk_E4;
}
