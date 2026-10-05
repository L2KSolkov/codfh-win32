// Split from unit_1DFBB0.cpp at 0x1DFF50, where the image ends that object (its deferred
// functions come before the next out-of-line one; PLAN M7).

#include <string.h>
#include "game/kujuui.h"
#include "game/frontend.h"
#include "game/parsedfile.h"
#include "types/type_4D1DB8.h"

// The border's measures (0x3E6CF4 on): the quads' reciprocal depth, the
// frame's width and height, the caption bar's lines, and its inset.
static const RwReal unk_3E6CF4 = 20.0f;
static const RwReal unk_3E6CF8 = 3.0f;
static const RwReal unk_3E6CFC = 3.0f;
static const RwReal unk_3E6D00 = 1.0f;
static const RwReal unk_3E6D04 = 1.0f;
static const RwReal unk_3E6D08 = 13.0f;

// match: __ehhandler$??0type_3E6D0C@kujuUI@@QAE@ABUtype_1E0330_rect@1@HPAUtype_3E7D08@1@@Z>1>8 @ 0x0041FC80
// match: __ehhandler$??0type_3E6D0C@kujuUI@@QAE@ABUtype_1E0330_rect@1@HPAUtype_3E7D08@1@@Z>1 @ 0x0041FC98
// match: __ehhandler$??1type_3E6D0C@kujuUI@@UAE@XZ>1>8 @ 0x0041FCB4
// match: __ehhandler$??1type_3E6D0C@kujuUI@@UAE@XZ>1 @ 0x0041FCC4
// match: __ehhandler$?vf_008@type_3E6D3C@kujuUI@@UAEXPAUtype_1C8DF0@2@HHPAUtype_1ED670@2@PAUtype_3E7D08@2@PAPAU52@@Z>1>8 @ 0x0041FCE0
// match: __ehhandler$?vf_008@type_3E6D3C@kujuUI@@UAEXPAUtype_1C8DF0@2@HHPAUtype_1ED670@2@PAUtype_3E7D08@2@PAPAU52@@Z>1 @ 0x0041FCE8
// match: ??_Gtype_3E6D0C@kujuUI@@UAEPAXI@Z @ 0x001E0290
// match: ??_Gtype_3E6D3C@kujuUI@@UAEPAXI@Z @ 0x001E0460
// match: ??_7type_3E6D0C@kujuUI@@6B@ @ 0x003E6D0C
// match: ??_7type_3E6D3C@kujuUI@@6B@ @ 0x003E6D3C
// match: ??_C@_06ODFLABIG@border?$AA@ @ 0x003E6D4C

namespace kujuUI
{
// The border (type_3E6D0C): an inner frame 3 units in from the rectangle,
// and (arg_4 clear) a darker panel with a caption bar.
// match: _unk_3E6D08 @ 0x003E6D08
// match: _unk_3E6D04 @ 0x003E6D04
// match: _unk_3E6D00 @ 0x003E6D00
// match: _unk_3E6CFC @ 0x003E6CFC
// match: _unk_3E6CF8 @ 0x003E6CF8
// match: _unk_3E6CF4 @ 0x003E6CF4
// match: ??0type_3E6D0C@kujuUI@@QAE@ABUtype_1E0330_rect@1@HPAUtype_3E7D08@1@@Z @ 0x001DFF50
// match: __ehhandler$??0type_3E6D0C@kujuUI@@QAE@ABUtype_1E0330_rect@1@HPAUtype_3E7D08@1@@Z-0x1E @ 0x00303750
// match: __ehhandler$??0type_3E6D0C@kujuUI@@QAE@ABUtype_1E0330_rect@1@HPAUtype_3E7D08@1@@Z @ 0x0030376E
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
type_3E6D0C::type_3E6D0C(const type_1E0330_rect &arg_0, RwInt32 arg_4, type_3E7D08 *arg_8)
    : type_3E7D08(arg_8), unk_0C(78)
{
    RwReal var_2C;
    RwReal var_28;
    RwReal ebp_24;
    RwReal var_20;
    RwReal l1C;
    RwReal m_18;
    RwReal ebp_14;
    RwReal lv_10;

    unk_D0 = arg_0;
    unk_E0 = 0;
    m_18 = unk_3E6CF8 + arg_0.unk_00;
    lv_10 = arg_0.unk_08 - unk_3E6CF8;
    l1C = unk_3E6CFC + arg_0.unk_04;
    ebp_14 = arg_0.unk_0C - unk_3E6CFC;
    sub_1E0330(arg_0.unk_00, arg_0.unk_04, arg_0.unk_08, l1C, 0xC0FFFFFF);
    sub_1E0330(arg_0.unk_00, l1C, m_18, ebp_14, 0xC0FFFFFF);
    sub_1E0330(lv_10, l1C, unk_D0.unk_08, ebp_14, 0xC0FFFFFF);
    sub_1E0330(arg_0.unk_00, ebp_14, arg_0.unk_08, arg_0.unk_0C, 0xC0FFFFFF);
    if (!arg_4)
    {
        var_28 = unk_3E6D08 + arg_0.unk_00;
        var_2C = arg_0.unk_08 - unk_3E6D08;
        var_20 = unk_3E6D08 + arg_0.unk_04;
        ebp_24 = arg_0.unk_0C - unk_3E6D08;
        sub_1E0330(var_28 - unk_3E6D00, var_20, var_2C + unk_3E6D00, var_20 + unk_3E6D04, 0xC0FFFFFF);
        sub_1E0330(var_28 - unk_3E6D00, ebp_24, var_2C + unk_3E6D00, ebp_24 + unk_3E6D04, 0xC0FFFFFF);
        sub_1E0330(var_28, var_20, var_28 + unk_3E6D00, ebp_24, 0xC0FFFFFF);
        sub_1E0330(var_2C, var_20, var_2C + unk_3E6D00, ebp_24, 0xC0FFFFFF);
        sub_1E0330(m_18, l1C, lv_10, var_20, 0x804B4B4B);
        sub_1E0330(m_18, var_20, var_28, ebp_24, 0x804B4B4B);
        sub_1E0330(var_2C, var_20, lv_10, ebp_24, 0x804B4B4B);
        sub_1E0330(m_18, ebp_24, lv_10, ebp_14, 0x804B4B4B);
        sub_1E0330(var_28 + unk_3E6D00, var_20 + unk_3E6D00, var_2C - unk_3E6D00, ebp_24 - unk_3E6D00, 0xA0000000);
    }
    else
    {
        sub_1E0330(m_18, l1C, lv_10, ebp_14, 0xA0000000);
    }
}
// match: ??1type_3E6D0C@kujuUI@@UAE@XZ @ 0x001E02C0
// match: __ehhandler$??1type_3E6D0C@kujuUI@@UAE@XZ-0x13 @ 0x00303780
// match: __ehhandler$??1type_3E6D0C@kujuUI@@UAE@XZ @ 0x00303793
type_3E6D0C::~type_3E6D0C()
{
}
// match: ?sub_1E0330@type_3E6D0C@kujuUI@@QAEXMMMMI@Z @ 0x001E0330
void type_3E6D0C::sub_1E0330(RwReal arg_0, RwReal arg_4, RwReal arg_8, RwReal arg_C, RwUInt32 arg_10)
{
    type_1E0330_rect var_10;

    var_10.unk_00 = arg_0;
    var_10.unk_04 = arg_4;
    var_10.unk_08 = arg_8;
    var_10.unk_0C = arg_C;
    unk_0C.sub_1F5C30(&var_10, RwIm2DGetFarScreenZ(), unk_3E6CF4, &unk_503308, arg_10);
}
// match: ?vf_018@type_3E6D0C@kujuUI@@UAEXPAUtype_1E4130@2@@Z @ 0x001E0380
void type_3E6D0C::vf_018(type_1E4130 *arg_0)
{
    arg_0->sub_1E4130(0);
    unk_0C.sub_1F5C00();
    if (unk_E0)
        unk_20.sub_1EEB60();
}
// match: ?vf_020@type_3E6D0C@kujuUI@@UAE?AUtype_1E0330_rect@2@XZ @ 0x001E03C0
type_1E0330_rect type_3E6D0C::vf_020()
{
    return unk_D0;
}
// match: ?sub_1E0400@type_3E6D0C@kujuUI@@QAEXPBUtype_1E0330_rect@2@@Z @ 0x001E0400
void type_3E6D0C::sub_1E0400(const type_1E0330_rect *arg_0)
{
    unk_20.sub_1EEC20(arg_0, RwIm2DGetFarScreenZ(), unk_3E6CF4, &unk_503308, 0xC0FFFFFF);
    unk_E0 = 1;
}
// match: ??0type_3E6D3C@kujuUI@@QAE@XZ @ 0x001E0440
type_3E6D3C::type_3E6D3C()
{
}
// match: ??1type_3E6D3C@kujuUI@@UAE@XZ @ 0x001E0490
type_3E6D3C::~type_3E6D3C()
{
}
// match: ?vf_004@type_3E6D3C@kujuUI@@UAEPBDXZ @ 0x001E04B0
const RwChar *type_3E6D3C::vf_004()
{
    return "border";
}
// match: ?vf_008@type_3E6D3C@kujuUI@@UAEXPAUtype_1C8DF0@2@HHPAUtype_1ED670@2@PAUtype_3E7D08@2@PAPAU52@@Z @ 0x001E04C0
// match: __ehhandler$?vf_008@type_3E6D3C@kujuUI@@UAEXPAUtype_1C8DF0@2@HHPAUtype_1ED670@2@PAUtype_3E7D08@2@PAPAU52@@Z-0xB @ 0x003037A0
// match: __ehhandler$?vf_008@type_3E6D3C@kujuUI@@UAEXPAUtype_1C8DF0@2@HHPAUtype_1ED670@2@PAUtype_3E7D08@2@PAPAU52@@Z @ 0x003037AB
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3E6D3C::vf_008(type_1C8DF0 *arg_0, RwInt32 arg_4, RwInt32 arg_8, type_1ED670 *arg_C, type_3E7D08 *arg_10,
                         type_3E7D08 **arg_14)
{
    RwInt32 var_18;
    type_1C9590 *var_14;
    type_1C8DF0_104 *lv_10;

    var_14 = sub_1E34E0();
    sub_1F7A60(arg_0, var_14->get_unk_00());
    lv_10 = arg_0->sub_1C90B0(var_14);
    sub_1F7A60(lv_10 != 0, "");
    if (lv_10)
    {
        var_18 = arg_0->sub_1C90B0(sub_1E3630()) ? 1 : 0;
        type_1E0330_rect var_28((RwReal)lv_10->sub_1C9890(0)->sub_1E3480(), (RwReal)lv_10->sub_1C9890(1)->sub_1E3480(),
                                (RwReal)lv_10->sub_1C9890(2)->sub_1E3480(), (RwReal)lv_10->sub_1C9890(3)->sub_1E3480());

        *arg_14 = new type_3E6D0C(var_28, var_18, arg_10);
    }
}
// match: ?vf_00C@type_3E6D3C@kujuUI@@UAEXPAVcScopeValidator@2@@Z @ 0x001E0630
void type_3E6D3C::vf_00C(cScopeValidator *arg_0)
{
    arg_0->sub_1C9F50(sub_1E34E0());
    arg_0->sub_1C9F50(sub_1E3620());
    arg_0->sub_1C9F50(sub_1E3630());
}
}
