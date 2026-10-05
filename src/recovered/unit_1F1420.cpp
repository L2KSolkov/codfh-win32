/*
 * kujuUI's text (game/kujuui.h): a string laid out in a font set's font over
 * a rectangle into four texture pages, pulsing when highlighted and cut to
 * fit with an ellipsis; the font's measures it uses; the text object a
 * widget shows and edits; and the text source's destructor.
 */
#include <math.h>
#include <string.h>
#include "game/kujuui.h"
#include "game/loc.h"

using namespace kujuUI;

// Vtables (.rdata, PLAN M5): each in its own placement range (config/splits.txt).
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_7type_1F1420@kujuUI@@6B@ @ 0x003E7A18
// match: __real@40490e56 @ 0x003E7A2C
// match: __ehhandler$??0type_1F1420@kujuUI@@QAE@HPBUtype_1E0330_rect@1@IH@Z>1>8 @ 0x00420CD4
// match: __ehhandler$??0type_1F1420@kujuUI@@QAE@HPBUtype_1E0330_rect@1@IH@Z>1 @ 0x00420CE4
// match: __ehhandler$??1type_1F1420@kujuUI@@UAE@XZ>1>8 @ 0x00420D00
// match: __ehhandler$??1type_1F1420@kujuUI@@UAE@XZ>1 @ 0x00420D10
// match: __ehhandler$?sub_1F15C0@type_1F1420@kujuUI@@QAEXXZ>1>8 @ 0x00420D2C
// match: __ehhandler$?sub_1F15C0@type_1F1420@kujuUI@@QAEXXZ>1 @ 0x00420D4C
// match: __ehhandler$?sub_1F1B10@type_1F1420@kujuUI@@QAEXPAUtype_1E4130@2@@Z>1>8 @ 0x00420D68
// match: __ehhandler$?sub_1F1B10@type_1F1420@kujuUI@@QAEXPAUtype_1E4130@2@@Z>1 @ 0x00420D80
// match: __ehhandler$?sub_1F1D70@type_1F1420@kujuUI@@QAEXPBD@Z>1>8 @ 0x00420D9C
// match: __ehhandler$?sub_1F1D70@type_1F1420@kujuUI@@QAEXPBD@Z>1 @ 0x00420DA4
// match: __ehhandler$?sub_1F1ED0@type_1F1420@kujuUI@@QAEIPBDH@Z>1>8 @ 0x00420DC0
// match: __ehhandler$?sub_1F1ED0@type_1F1420@kujuUI@@QAEIPBDH@Z>1 @ 0x00420DD8
// match: __ehhandler$?sub_1F2110@type_1F1420@kujuUI@@QAE?AUtype_1CB670@@XZ>1>8 @ 0x00420DF4
// match: __ehhandler$?sub_1F2110@type_1F1420@kujuUI@@QAE?AUtype_1CB670@@XZ>1 @ 0x00420E2C
// match: __ehhandler$??$?HDU?$char_traits@D@std@@V?$allocator@D@1@@std@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@0@ABV10@PBD@Z>1>8 @ 0x00420E48
// match: __ehhandler$??$?HDU?$char_traits@D@std@@V?$allocator@D@1@@std@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@0@ABV10@PBD@Z>1 @ 0x00420E58

// match: ??0type_1F1420@kujuUI@@QAE@HPBUtype_1E0330_rect@1@IH@Z @ 0x001F1420
// match: __ehhandler$??0type_1F1420@kujuUI@@QAE@HPBUtype_1E0330_rect@1@IH@Z-0x1E @ 0x00304390
// match: __ehhandler$??0type_1F1420@kujuUI@@QAE@HPBUtype_1E0330_rect@1@IH@Z @ 0x003043AE

type_1F1420::type_1F1420(RwInt32 arg_0, const type_1E0330_rect *arg_4, RwUInt32 arg_8, RwInt32 arg_C)
    : unk_70((type_1E6350 *)arg_0), unk_74(*arg_4), unk_84(0), unk_8C(0), unk_90(arg_8), unk_94(arg_C), unk_98(false),
      unk_99(true)
{
}

// match: ??_Gtype_1F1420@kujuUI@@UAEPAXI@Z @ 0x001F1510

// match: ??1type_1F1420@kujuUI@@UAE@XZ @ 0x001F1540
// match: __ehhandler$??1type_1F1420@kujuUI@@UAE@XZ-0x1E @ 0x003043C0
// match: __ehhandler$??1type_1F1420@kujuUI@@UAE@XZ @ 0x003043DE
type_1F1420::~type_1F1420()
{
}

// match: ?sub_1F15C0@type_1F1420@kujuUI@@QAEXXZ @ 0x001F15C0
// match: __ehhandler$?sub_1F15C0@type_1F1420@kujuUI@@QAEXXZ-0x18 @ 0x003043F0
// match: __ehhandler$?sub_1F15C0@type_1F1420@kujuUI@@QAEXXZ @ 0x00304408
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_1F1420::sub_1F15C0()
{
    if (!unk_54.empty())
    {
        type_E8780<type_1E5A60> m_18(unk_70->sub_1E6610(unk_8C));
        RwUInt32 ebp_14;
        RwUInt32 lv_10 = unk_70->unk_18[unk_8C];
        if (unk_8C == 1)
        {
            RwUInt32 t20 = lv_10 >> 24 & 0xFF;
            RwUInt32 lcl_38 = lv_10 >> 16 & 0xFF;
            RwUInt32 r34 = lv_10 >> 8 & 0xFF;
            RwUInt32 lv_30 = lv_10 & 0xFF;
            RwUInt32 fp_2C = unk_70->get_colour(0);
            RwUInt32 stk_3C = fp_2C >> 24 & 0xFF;
            RwUInt32 q28 = fp_2C >> 16 & 0xFF;
            RwUInt32 frm_24 = fp_2C >> 8 & 0xFF;
            RwUInt32 l1C = fp_2C & 0xFF;
            RwReal loc40 = (RwReal)cos((RwReal)((RwReal)(unk_88 * 2) * 3.1415f / 50.0f)) * 0.5f + 0.5f;
            lcl_38 = (RwUInt32)((RwReal)lcl_38 * loc40 + (RwReal)q28 * (1.0f - loc40));
            r34 = (RwUInt32)((RwReal)r34 * loc40 + (RwReal)frm_24 * (1.0f - loc40));
            lv_30 = (RwUInt32)((RwReal)lv_30 * loc40 + (RwReal)l1C * (1.0f - loc40));
            t20 = (RwUInt32)((RwReal)t20 * loc40 + (RwReal)stk_3C * (1.0f - loc40));
            lv_10 = t20 << 24 | lcl_38 << 16 | r34 << 8 | lv_30;
        }
        if (unk_99)
        {
            m_18->sub_1E6690(unk_54.c_str(), lv_10, (RwUInt32)pvf_004()->width(), unk_90, unk_04,
                               (RwInt32 *)&ebp_14);
        }
        else
        {
            m_18->sub_1E6690(sub_1F2110().c_str(), lv_10, (RwUInt32)pvf_004()->width(), unk_90, unk_04,
                               (RwInt32 *)&ebp_14);
        }
        switch (unk_94)
        {
        case 0:
            unk_84 = 0;
            break;
        case 1:
            unk_84 = (RwInt32)((pvf_004()->height() - (RwReal)ebp_14) / 2.0f);
            break;
        }
    }
}

// match: ?sub_1F1AA0@type_1F1420@kujuUI@@QAEXXZ @ 0x001F1AA0
void type_1F1420::sub_1F1AA0()
{
    sub_1F15C0();
    pvf_008(&unk_74);
}

// match: ?sub_1F1AD0@type_1F1420@kujuUI@@QAEXXZ @ 0x001F1AD0
void type_1F1420::sub_1F1AD0()
{
    for (RwUInt32 var_4 = 0; var_4 != 4; ++var_4)
        unk_04[var_4].sub_1F5BA0();
}

// match: ?sub_1F1B10@type_1F1420@kujuUI@@QAEXPAUtype_1E4130@2@@Z @ 0x001F1B10
// match: __ehhandler$?sub_1F1B10@type_1F1420@kujuUI@@QAEXPAUtype_1E4130@2@@Z-0x10 @ 0x00304420
// match: __ehhandler$?sub_1F1B10@type_1F1420@kujuUI@@QAEXPAUtype_1E4130@2@@Z @ 0x00304430
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_1F1420::sub_1F1B10(type_1E4130 *arg_0)
{
    if (!unk_98 && !unk_54.empty())
    {
        if (unk_8C == 1)
        {
            sub_1F15C0();
            RwUInt32 local_14 = (RwUInt32)unk_74.unk_00;
            RwUInt32 v10 = (RwUInt32)(unk_84 + unk_74.unk_04);
            for (RwUInt32 var18 = 0; var18 != 4; ++var18)
            {
                type_1F5A50 *var_1C = &unk_04[var18];
                var_1C->sub_1F5CD0((RwReal)local_14, (RwReal)v10);
            }
            ++unk_88;
            if (unk_88 >= 50)
                unk_88 -= 50;
        }
        arg_0->sub_1E4160(1);
        for (RwUInt32 l20 = 0; l20 != 4; ++l20)
        {
            type_1F5A50 *fp_28 = &unk_04[l20];
            type_E8780<type_1E5A60> fp_24(unk_70->sub_1E6610(unk_8C));
            if (!fp_28->test_unk_04())
            {
                arg_0->sub_1E4130((RwInt32)get_texture_raster(fp_24->sub_1E5A60(l20)));
                fp_28->sub_1F5C00();
            }
        }
    }
}

// match: ?sub_1F1D10@type_1F1420@kujuUI@@QAEXABUtype_1A5EA0@@@Z @ 0x001F1D10
void type_1F1420::sub_1F1D10(const type_1A5EA0 &arg_0)
{
    static_cast<type_1A5EA0 &>(unk_54) = arg_0;
    if (!unk_99)
        sub_1F2110();
    sub_1F15C0();
}

// match: ?sub_1F1D70@type_1F1420@kujuUI@@QAEXPBD@Z @ 0x001F1D70
// match: __ehhandler$?sub_1F1D70@type_1F1420@kujuUI@@QAEXPBD@Z-0x8 @ 0x00304440
// match: __ehhandler$?sub_1F1D70@type_1F1420@kujuUI@@QAEXPBD@Z @ 0x00304448
void type_1F1420::sub_1F1D70(const RwChar *arg_0)
{
    unk_54 = sub_1CB720(arg_0);
    sub_1F15C0();
}

// match: ?sub_1F1E00@type_1F1420@kujuUI@@QAEXH@Z @ 0x001F1E00
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_1F1420::sub_1F1E00(RwInt32 arg_0)
{
    if (arg_0 != unk_8C)
    {
        unk_8C = arg_0;
        sub_1F15C0();
        RwUInt32 v8 = (RwUInt32)unk_74.unk_00;
        RwUInt32 var_4 = (RwUInt32)(unk_84 + unk_74.unk_04);
        for (RwUInt32 stk_C = 0; stk_C != 4; ++stk_C)
        {
            type_1F5A50 *var_10 = &unk_04[stk_C];
            var_10->sub_1F5CD0((RwReal)v8, (RwReal)var_4);
        }
        unk_88 = 0;
    }
}

// match: ?sub_1F1ED0@type_1F1420@kujuUI@@QAEIPBDH@Z @ 0x001F1ED0
// match: __ehhandler$?sub_1F1ED0@type_1F1420@kujuUI@@QAEIPBDH@Z-0x10 @ 0x00304460
// match: __ehhandler$?sub_1F1ED0@type_1F1420@kujuUI@@QAEIPBDH@Z @ 0x00304470
RwUInt32 type_1F1420::sub_1F1ED0(const RwChar *arg_0, RwInt32 arg_4)
{
    type_E8780<type_1E5A60> var_10(unk_70->sub_1E6610(unk_8C));
    return var_10->sub_1F2490(arg_0, arg_4);
}

// match: ?pvf_004@type_1F1420@kujuUI@@UAEPBUtype_1E0330_rect@2@XZ @ 0x001F1F70
const type_1E0330_rect *type_1F1420::pvf_004()
{
    return &unk_74;
}

// match: ?pvf_008@type_1F1420@kujuUI@@UAEXPBUtype_1E0330_rect@2@@Z @ 0x001F1F90
void type_1F1420::pvf_008(const type_1E0330_rect *arg_0)
{
    if (arg_0->width() != unk_74.width() || arg_0->height() != unk_74.height())
    {
        unk_74 = *arg_0;
        sub_1F15C0();
    }
    else
        unk_74 = *arg_0;
    RwInt32 v8 = (RwInt32)unk_74.unk_00;
    RwInt32 var_4 = (RwInt32)(unk_84 + unk_74.unk_04);
    for (RwUInt32 stk_C = 0; stk_C != 4; ++stk_C)
    {
        type_1F5A50 *var_10 = &unk_04[stk_C];
        var_10->sub_1F5CD0((RwReal)v8, (RwReal)var_4);
    }
}

// match: ?pvf_00C@type_1F1420@kujuUI@@UAE_NXZ @ 0x001F20A0
bool type_1F1420::pvf_00C()
{
    return unk_98;
}

// match: ?pvf_010@type_1F1420@kujuUI@@UAEX_N@Z @ 0x001F20C0
void type_1F1420::pvf_010(bool arg_0)
{
    unk_98 = arg_0;
}

// match: ?sub_1F20E0@type_1F1420@kujuUI@@QAEXH@Z @ 0x001F20E0
void type_1F1420::sub_1F20E0(RwInt32 arg_0)
{
    if (arg_0 != unk_90)
    {
        unk_90 = arg_0;
        sub_1F15C0();
    }
}

// match: ?sub_1F2110@type_1F1420@kujuUI@@QAE?AUtype_1CB670@@XZ @ 0x001F2110
// match: __ehhandler$?sub_1F2110@type_1F1420@kujuUI@@QAE?AUtype_1CB670@@XZ-0x41 @ 0x00304480
// match: __ehhandler$?sub_1F2110@type_1F1420@kujuUI@@QAE?AUtype_1CB670@@XZ @ 0x003044C1
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
type_1CB670 type_1F1420::sub_1F2110()
{
    RwInt32 var_1C;
    RwInt32 l20;
    type_E8780<type_1E5A60> var18(unk_70->sub_1E6610(unk_8C));
    RwInt32 v10 = var18->sub_1F2490(unk_54.c_str(), -1);
    RwInt32 local_14 = (RwInt32)unk_74.width();
    if (v10 > local_14)
    {
        type_1CB670 l40(static_cast<const std::string &>(sub_1CBBB0()));
        var_1C = var18->sub_1F2490(l40.c_str(), -1);
        l20 = var18->sub_1F24C0(unk_54.c_str(), local_14 - var_1C);
        return sub_1CB720((unk_54.substr(0, l20) + l40.c_str()).c_str());
    }
    return type_1CB670(unk_54);
}

// match: ?sub_1F2410@type_1F1420@kujuUI@@QAEX_N@Z @ 0x001F2410
void type_1F1420::sub_1F2410(bool arg_0)
{
    if (arg_0 != unk_99)
    {
        unk_99 = arg_0;
        sub_1F15C0();
        pvf_008(&unk_74);
    }
}

// match: ?sub_1F2460@type_1E5A60@@QAEIPBDPAI1H@Z @ 0x001F2460
RwUInt32 type_1E5A60::sub_1F2460(const RwChar *arg_0, RwUInt32 *arg_4, RwUInt32 *arg_8, RwInt32 arg_C)
{
    return sub_1F26B0(arg_0, 9999999, arg_4, arg_8, arg_C);
}

// match: ?sub_1F2490@type_1E5A60@@QAEIPBDH@Z @ 0x001F2490
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwUInt32 type_1E5A60::sub_1F2490(const RwChar *arg_0, RwInt32 arg_4)
{
    RwUInt32 local_8;
    RwUInt32 var_4;
    return sub_1F2460(arg_0, &local_8, &var_4, arg_4);
}

// match: ?sub_1F24C0@type_1E5A60@@QAEHPBDH@Z @ 0x001F24C0
RwInt32 type_1E5A60::sub_1F24C0(const RwChar *arg_0, RwInt32 arg_4)
{
    RwInt32 lv_C = 0;
    RwInt32 var_10 = 0;
    bool var_1 = true;
    RwUInt32 var_8 = unk_08;
    while (var_1)
    {
        RwInt32 l18;
        RwChar loc11;
        RwInt32 v1c;
        RwUInt16 w20;
        loc11 = *arg_0;
        w20 = loc11;
        switch (w20)
        {
        case ' ':
            v1c = var_8;
            break;
        case '\t':
            v1c = var_8 << 4;
            break;
        case 0:
        case '\n':
            var_1 = false;
            v1c = 0;
            break;
        default:
            if (w20 >= 1)
            {
                kujuUI::type_1E2250 *var_24 = sub_1E5940(w20);
                RwUInt8 var_25 = var_24->unk_12;
                v1c = var_25 + unk_0A;
            }
            else
                v1c = 0;
        }
        l18 = lv_C + v1c;
        if (l18 > arg_4)
            return var_10;
        ++var_10;
        ++arg_0;
        lv_C = l18;
    }
    return var_10;
}


// match: ??$?HDU?$char_traits@D@std@@V?$allocator@D@1@@std@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@0@ABV10@PBD@Z @ 0x001F25F0
// match: __ehhandler$??$?HDU?$char_traits@D@std@@V?$allocator@D@1@@std@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@0@ABV10@PBD@Z-0x21 @ 0x003044D0
// match: __ehhandler$??$?HDU?$char_traits@D@std@@V?$allocator@D@1@@std@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@0@ABV10@PBD@Z @ 0x003044F1







// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?sub_1E7540@type_1F28C0@kujuUI@@QAEXPAUtype_3E7258@2@@Z (folded into 0x1E7540)
void kujuUI::type_1F28C0::sub_1E7540(struct kujuUI::type_3E7258 * arg_0)
{
    unk_04 = arg_0;
}
