/*
 * kujuUI's combobox (game/kujuui.h), after the font glyphs' helpers: the
 * widget named "combobox" and its creator.
 */
#include "game/kujuui.h"
#include "game/frontend.h"
#include "game/parsedfile.h"
#include "types/type_4D1DB8.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x00503318
namespace kujuUI { bool byte_503318; }
// End of its data definitions.

// Vtables (.rdata, PLAN M5): each in its own placement range (config/splits.txt).
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?unk_3E6F3C@kujuUI@@3QBHB @ 0x003E6F3C
// match: ?unk_3E6F4C@kujuUI@@3QBHB @ 0x003E6F4C
// match: ??_7type_3E6F74@kujuUI@@6Btype_3E76E4@1@@ @ 0x003E6F5C
// match: ??_7type_3E6F74@kujuUI@@6Btype_3E75E8@1@@ @ 0x003E6F60
// match: ??_7type_3E6F74@kujuUI@@6Btype_3E7D08@1@@ @ 0x003E6F74
// match: __ehhandler$??0type_3E6F74@kujuUI@@QAE@PBDPBUtype_1E0330_rect@1@_NPAUtype_1E34A0@1@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@4HPBUtype_1A5EA0@@1PBIHIHPAUtype_3E7D08@1@@Z>1>8 @ 0x0041FE18
// match: __ehhandler$??0type_3E6F74@kujuUI@@QAE@PBDPBUtype_1E0330_rect@1@_NPAUtype_1E34A0@1@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@4HPBUtype_1A5EA0@@1PBIHIHPAUtype_3E7D08@1@@Z>1 @ 0x0041FE40
// match: __ehhandler$??1type_3E6F74@kujuUI@@UAE@XZ>1>8 @ 0x0041FE5C
// match: __ehhandler$??1type_3E6F74@kujuUI@@UAE@XZ>1 @ 0x0041FE7C
// match: __ehhandler$?sub_1E2A50@type_3E6F74@kujuUI@@QAEXABUtype_1A5EA0@@@Z>1>8 @ 0x0041FE98
// match: __ehhandler$?sub_1E2A50@type_3E6F74@kujuUI@@QAEXABUtype_1A5EA0@@@Z>1 @ 0x0041FEA0


namespace kujuUI {

// match: ?sub_1E2160@kujuUI@@YAMM@Z @ 0x001E2160
RwReal sub_1E2160(RwReal arg_0)
{
    return (RwReal)(0.5 / arg_0);
}

// match: ?sub_1E2180@kujuUI@@YA?AUtype_1E0330_rect@1@IIIIMM@Z @ 0x001E2180
type_1E0330_rect sub_1E2180(RwUInt32 arg_0, RwUInt32 arg_4, RwUInt32 arg_8, RwUInt32 arg_C, RwReal arg_10,
                            RwReal arg_14)
{
    return type_1E0330_rect(arg_0 / arg_10 + sub_1E2160(arg_10), arg_4 / arg_14 + sub_1E2160(arg_14),
                            (arg_8 + 1) / arg_10 + sub_1E2160(arg_10), (arg_C + 1) / arg_14 + sub_1E2160(arg_14));
}

// match: ??0type_1E2250@kujuUI@@QAE@PBUtype_1E2250_entry@1@MM@Z @ 0x001E2250
type_1E2250::type_1E2250(const type_1E2250_entry *arg_0, RwReal arg_4, RwReal arg_8)
    : unk_00(sub_1E2180(arg_0->unk_0A, arg_0->unk_08, arg_0->unk_0E, arg_0->unk_0C, arg_4, arg_8))
{
    unk_10 = arg_0->unk_00;
    unk_12 = (RwUInt8)(arg_0->unk_0E - arg_0->unk_0A);
    unk_13 = (RwUInt8)(arg_0->unk_0C - arg_0->unk_08);
    unk_14 = (RwUInt8)-arg_0->unk_12;
    unk_15 = arg_0->unk_02;
}

// match: ??0type_1E2250@kujuUI@@QAE@ABU01@G@Z @ 0x001E22F0
type_1E2250::type_1E2250(const type_1E2250 &arg_0, RwUInt16 arg_4)
{
    unk_00 = arg_0.unk_00;
    unk_10 = arg_4;
    unk_12 = arg_0.get_unk_12();
    unk_13 = arg_0.get_unk_13();
    unk_14 = arg_0.get_unk_14();
    unk_15 = arg_0.get_unk_15();
}

// match: ??0type_1E2250@kujuUI@@QAE@XZ @ 0x001E2380
type_1E2250::type_1E2250()
{
    unk_00.unk_00 = 0;
    unk_00.unk_04 = 0;
    unk_00.unk_08 = 0;
    unk_00.unk_0C = 0;
    unk_10 = 0xFFFF;
    unk_12 = 0;
    unk_13 = 0;
    unk_14 = 0;
    unk_15 = 0;
}

// The pad's buttons that step a combobox's value down and up, by its
// orientation (0x3E6F3C and 0x3E6F4C).
extern const RwInt32 unk_3E6F3C[4] = { 3, 0, 14, 8 };
extern const RwInt32 unk_3E6F4C[4] = { 2, 1, 4, 9 };

// match: ??0type_3E6F74@kujuUI@@QAE@PBDPBUtype_1E0330_rect@1@_NPAUtype_1E34A0@1@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@4HPBUtype_1A5EA0@@1PBIHIHPAUtype_3E7D08@1@@Z @ 0x001E23E0
// match: __ehhandler$??0type_3E6F74@kujuUI@@QAE@PBDPBUtype_1E0330_rect@1@_NPAUtype_1E34A0@1@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@4HPBUtype_1A5EA0@@1PBIHIHPAUtype_3E7D08@1@@Z-0x3A @ 0x00303850
// match: __ehhandler$??0type_3E6F74@kujuUI@@QAE@PBDPBUtype_1E0330_rect@1@_NPAUtype_1E34A0@1@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@4HPBUtype_1A5EA0@@1PBIHIHPAUtype_3E7D08@1@@Z @ 0x0030388A
type_3E6F74::type_3E6F74(const RwChar *arg_0, const type_1E0330_rect *arg_4, bool arg_8, type_1E34A0 *arg_C,
                         const std::string &arg_10, const std::string &arg_14, RwInt32 arg_18,
                         const type_1A5EA0 *arg_1C, const type_1E0330_rect *arg_20, const RwUInt32 *arg_24,
                         RwInt32 arg_28, RwUInt32 arg_2C, RwInt32 arg_30, type_3E7D08 *arg_34)
    : type_3E76B4(arg_0, arg_4, arg_34), unk_1C(arg_C), unk_20(arg_8), unk_24(arg_30),
      unk_28(arg_18, arg_4, arg_2C, true), unk_C4(0), unk_C8(arg_10), unk_E4(arg_14)
{
    if (unk_1C)
        unk_1C->sub_1E34A0(this);
    if (arg_1C)
    {
        unk_C4 = new type_1F1420(arg_28, arg_20, *arg_24, true);
        unk_C4->sub_1F1D10(*arg_1C);
        unk_C4->pvf_008(unk_C4->pvf_004());
    }
    unk_28.sub_1F2410(0);
}

// match: ??_Gtype_3E6F74@kujuUI@@UAEPAXI@Z @ 0x001E2590

// match: ??1type_3E6F74@kujuUI@@UAE@XZ @ 0x001E25C0
// match: __ehhandler$??1type_3E6F74@kujuUI@@UAE@XZ-0x2F @ 0x003038A0
// match: __ehhandler$??1type_3E6F74@kujuUI@@UAE@XZ @ 0x003038CF
type_3E6F74::~type_3E6F74()
{
    delete unk_C4;
}

// match: ?givenFocus@type_3E6F74@kujuUI@@UAEXXZ @ 0x001E26A0
void type_3E6F74::givenFocus()
{
    if (unk_504210.sub_1EF160())
        unk_504210.sub_1EF140();
    sub_1E2B60(1);
}

// match: ?lostFocus@type_3E6F74@kujuUI@@UAEXXZ @ 0x001E26D0
void type_3E6F74::lostFocus()
{
    if (unk_504210.sub_1EF160())
        unk_504210.sub_1EF140();
    sub_1E2B60(0);
}

// match: ?vf_014@type_3E6F74@kujuUI@@UAEXM@Z @ 0x001E2700
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3E6F74::vf_014(RwReal arg_0)
{
    RwInt32 var_8;
    bool fp_2;
    bool var_1;

    fp_2 = (bool)(sub_1EFFC0() == 3);
    var_1 = unk_1C && unk_1C->vf_010() ? false : true;
    if (fp_2)
    {
        if (!var_1)
        {
            var_8 = sub_1F7720() ? 1 : 0;
            sub_1E2B60(var_8);
        }
    }
    else if (var_1)
        sub_1E2B60(3);
    if (sub_1EFFC0() == 1 && unk_504210.sub_1EF160() && unk_504210.sub_1EF090(arg_0) && unk_1C)
        byte_503318 ? (unk_1C->vf_008(unk_504210.sub_1EF180()), 0) : (unk_1C->vf_00C(unk_504210.sub_1EF180()), 0);
}

// match: ?processEvent@type_3E6F74@kujuUI@@UAE?AW4eEventWasHandled@2@ABVcStateChange@2@@Z @ 0x001E2830
eEventWasHandled type_3E6F74::processEvent(const cStateChange &arg_0)
{
    RwInt32 var_C = unk_3E6F3C[unk_24];
    RwInt32 var_10 = unk_3E6F4C[unk_24];
    RwInt32 var_8 = arg_0.get_unk_00();
    RwInt32 var_4 = 1;

    if (var_8 == var_10)
    {
        if (arg_0.get_unk_04() == 0 && sub_1E2B10())
        {
            unk_1C->vf_008(1);
            byte_503318 = true;
            if (dword_504378)
                dword_504378->vf_04(1);
        }
        var_4 = 0;
    }
    else if (var_8 == var_C)
    {
        if (arg_0.get_unk_04() == 0 && sub_1E2B10())
        {
            unk_1C->vf_00C(1);
            byte_503318 = false;
            if (dword_504378)
                dword_504378->vf_04(1);
        }
        var_4 = 0;
    }
    if (var_4 == 0)
    {
        if (unk_504210.sub_1EF160())
            unk_504210.sub_1EF140();
        if (arg_0.get_unk_04() == 0)
            unk_504210.sub_1EF120();
    }
    return (eEventWasHandled)var_4;
}

// match: ?vf_018@type_3E6F74@kujuUI@@UAEXPAUtype_1E4130@2@@Z @ 0x001E2980
void type_3E6F74::vf_018(type_1E4130 *arg_0)
{
    type_3E76B4::vf_018(arg_0);
    unk_28.sub_1F1B10(arg_0);
    if (unk_C4)
        unk_C4->sub_1F1B10(arg_0);
}

// match: ?vf_010@type_3E6F74@kujuUI@@UAE_NXZ @ 0x001E29D0
bool type_3E6F74::vf_010()
{
    return unk_20 || sub_1E2B10();
}

// match: ?vf_008@type_3E6F74@kujuUI@@UAEXXZ @ 0x001E2A10
void type_3E6F74::vf_008()
{
    unk_28.sub_1F1AA0();
    type_3E76B4::vf_008();
}

// match: ?vf_00C@type_3E6F74@kujuUI@@UAEXXZ @ 0x001E2A30
void type_3E6F74::vf_00C()
{
    unk_28.sub_1F1AD0();
    type_3E76B4::vf_00C();
}

// match: ?sub_1E2A50@type_3E6F74@kujuUI@@QAEXABUtype_1A5EA0@@@Z @ 0x001E2A50
// match: __ehhandler$?sub_1E2A50@type_3E6F74@kujuUI@@QAEXABUtype_1A5EA0@@@Z-0x8 @ 0x003038E0
// match: __ehhandler$?sub_1E2A50@type_3E6F74@kujuUI@@QAEXABUtype_1A5EA0@@@Z @ 0x003038E8
void type_3E6F74::sub_1E2A50(const type_1A5EA0 &arg_0)
{
    type_1CB670 var_2C((const std::string &)unk_C8);

    var_2C.sub_1C84F0(arg_0);
    var_2C.sub_1C84F0(unk_E4);
    unk_28.sub_1F1D10(var_2C);
    const type_1E0330_rect *var_30 = pvf_004();

    unk_28.pvf_008(var_30);
}

// match: ?sub_1E2B10@type_3E6F74@kujuUI@@QAE_NXZ @ 0x001E2B10
bool type_3E6F74::sub_1E2B10()
{
    return unk_1C && unk_1C->vf_010();
}

// match: ?sub_1E2B60@type_3E6F74@kujuUI@@QAEXH@Z @ 0x001E2B60
void type_3E6F74::sub_1E2B60(RwInt32 arg_0)
{
    sub_1EFFA0(arg_0);
    unk_28.sub_1F1E00(arg_0);
    if (unk_C4)
        unk_C4->sub_1F1E00(arg_0);
}

// match: ??_Etype_3E6F74@kujuUI@@WM@AEPAXI@Z @ 0x001E2BB0






}

namespace kujuUI
{

}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??1type_1E2250@kujuUI@@QAE@XZ (folded into 0x1E41C0)
kujuUI::type_1E2250::~type_1E2250()
{
}
