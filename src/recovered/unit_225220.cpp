/*
 * The Live engine's font renderer (game/uixfont.h): UIX's text drawn with
 * three kujuUI fonts, and the fonts' wide-string layout it uses.
 */
#include <string.h>

#include "game/uixfont.h"
#include "game/kujuui.h"
#include "game/fileio.h"
#include "game/parsedfile.h"

using namespace kujuUI;

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_7type_225220@@6B@ @ 0x003EACF0
// match: __ehhandler$??0type_225220@@QAE@PBD00@Z>1>8 @ 0x00425ED8
// match: __ehhandler$??0type_225220@@QAE@PBD00@Z>1 @ 0x00425F28
// match: __ehhandler$??1type_225220@@QAE@XZ>1>8 @ 0x00425F44
// match: __ehhandler$??1type_225220@@QAE@XZ>1 @ 0x00425F5C

// match: ??0type_225220@@QAE@PBD00@Z @ 0x00225220
// match: __ehhandler$??0type_225220@@QAE@PBD00@Z-0x4F @ 0x00308EC0
// match: __ehhandler$??0type_225220@@QAE@PBD00@Z @ 0x00308F0F

type_225220::type_225220(const RwChar *arg_0, const RwChar *arg_4, const RwChar *arg_8)
    : unk_54(sub_1E5A80(arg_0)), unk_58(sub_1E5A80(arg_4)), unk_5C(sub_1E5A80(arg_8))
{
    unk_60 = 0;
    unk_68 = 0xFFFFFFFF;
    unk_6C = 0;
    unk_B0 = false;
    unk_64 = unk_58->sub_1E60E0();
    unk_B4 = 1;
    memset(unk_70, 0, sizeof(unk_70));
}

// match: ?Release@type_225220@@UAGKXZ @ 0x00225390
ULONG type_225220::Release()
{
    return --unk_6C;
}

// match: ??1type_225220@@QAE@XZ @ 0x002253B0
// match: __ehhandler$??1type_225220@@QAE@XZ-0x2C @ 0x00308F20
// match: __ehhandler$??1type_225220@@QAE@XZ @ 0x00308F4C
type_225220::~type_225220()
{
}

// match: ?GetTextSize@type_225220@@UAGJPBGPAK1@Z @ 0x00225430
HRESULT type_225220::GetTextSize(LPCWSTR arg_0, DWORD *arg_4, DWORD *arg_8)
{
    RwUInt32 l8;
    RwUInt32 var_4;

    switch (unk_B4)
    {
    case 0:
        unk_54->sub_225BE0(arg_0, &l8, &var_4, -1);
        break;
    case 2:
        unk_5C->sub_225BE0(arg_0, &l8, &var_4, -1);
        break;
    default:
        unk_58->sub_225BE0(arg_0, &l8, &var_4, -1);
        break;
    }
    *arg_4 = l8;
    *arg_8 = var_4;
    return 0;
}

// match: ?SetColor@type_225220@@UAGJK@Z @ 0x002254D0
HRESULT type_225220::SetColor(D3DCOLOR arg_0)
{
    unk_68 = arg_0;
    return 0;
}

// match: ?SetHeight@type_225220@@UAGJK@Z @ 0x002254F0
HRESULT type_225220::SetHeight(DWORD arg_0)
{
    RwUInt32 var_4;

    if (arg_0 >= 0x14)
    {
        unk_B4 = 2;
        var_4 = unk_5C->sub_1E6100();
    }
    else if (arg_0 >= 0x10)
    {
        unk_B4 = 1;
        var_4 = unk_58->sub_1E6100();
    }
    else
    {
        unk_B4 = 0;
        var_4 = unk_54->sub_1E6100();
    }
    if (arg_0 >= var_4)
        unk_64 = arg_0;
    else
        unk_64 = var_4;
    return 0;
}

// match: ?DrawText@type_225220@@UAGJPBGKKK@Z @ 0x002255A0
HRESULT type_225220::DrawText(LPCWSTR arg_0, DWORD arg_4, DWORD arg_8, DWORD arg_C)
{
    RwUInt32 l4;
    RwUInt32 var_8 = arg_C <= 0 ? 0x280 - arg_4 : arg_C;
    RwInt32 lv_C;
    RwInt32 var_10;

    D3DDevice::SetVertexDataColor(3, unk_68);
    switch (unk_B4)
    {
    case 2:
        l4 = unk_5C->sub_1E6120();
        var_10 = unk_64 - unk_5C->sub_1E6100();
        unk_5C->sub_1E6140(var_10);
        unk_5C->sub_225C10(arg_0, unk_68, var_8, unk_60, unk_04, &lv_C);
        for (RwUInt32 var_1C = 0; var_1C < unk_5C->sub_1E5A40(); var_1C++)
        {
            type_1F5A50 *var_20 = &unk_04[var_1C];

            if (!var_20->test_unk_04())
            {
                RwRenderStateSet(rwRENDERSTATETEXTURERASTER, get_texture_raster(unk_5C->sub_1E5A60(var_1C)));
                var_20->sub_1F5CD0((RwReal)arg_4, (RwReal)arg_8);
                var_20->sub_1F5C00();
            }
        }
        unk_5C->sub_1E6140(l4);
        break;
    case 0:
        l4 = unk_54->sub_1E6120();
        var_10 = unk_64 - unk_54->sub_1E6100();
        unk_54->sub_1E6140(var_10);
        unk_54->sub_225C10(arg_0, unk_68, var_8, unk_60, unk_04, &lv_C);
        for (RwUInt32 var_14 = 0; var_14 < unk_54->sub_1E5A40(); var_14++)
        {
            type_1F5A50 *var_18 = &unk_04[var_14];

            if (!var_18->test_unk_04())
            {
                RwRenderStateSet(rwRENDERSTATETEXTURERASTER, get_texture_raster(unk_54->sub_1E5A60(var_14)));
                var_18->sub_1F5CD0((RwReal)arg_4, (RwReal)arg_8);
                var_18->sub_1F5C00();
            }
        }
        unk_54->sub_1E6140(l4);
        break;
    default:
        l4 = unk_58->sub_1E6120();
        var_10 = unk_64 - unk_58->sub_1E6100();
        unk_58->sub_1E6140(var_10);
        unk_58->sub_225C10(arg_0, unk_68, var_8, unk_60, unk_04, &lv_C);
        for (RwUInt32 var_24 = 0; var_24 < unk_58->sub_1E5A40(); var_24++)
        {
            type_1F5A50 *var_28 = &unk_04[var_24];

            if (!var_28->test_unk_04())
            {
                RwRenderStateSet(rwRENDERSTATETEXTURERASTER, get_texture_raster(unk_58->sub_1E5A60(var_24)));
                var_28->sub_1F5CD0((RwReal)arg_4, (RwReal)arg_8);
                var_28->sub_1F5C00();
            }
        }
        unk_58->sub_1E6140(l4);
        break;
    }
    return 0;
}

// match: ?sub_225A10@type_225220@@QAEXH@Z @ 0x00225A10
void type_225220::sub_225A10(RwInt32 arg_0)
{
    unk_60 = arg_0;
}

// match: ?sub_225A30@type_225220@@QAEIPBGPAI1H@Z @ 0x00225A30
RwUInt32 type_225220::sub_225A30(const wchar_t *arg_0, RwUInt32 *arg_4, RwUInt32 *arg_8, RwInt32 arg_C)
{
    RwUInt32 var_4;

    switch (unk_B4)
    {
    case 0:
        var_4 = unk_54->sub_225BE0(arg_0, arg_4, arg_8, arg_C);
        break;
    case 2:
        var_4 = unk_5C->sub_225BE0(arg_0, arg_4, arg_8, arg_C);
        break;
    default:
        var_4 = unk_58->sub_225BE0(arg_0, arg_4, arg_8, arg_C);
        break;
    }
    return var_4;
}

// match: ?sub_225AD0@type_225220@@QAEIPBGH@Z @ 0x00225AD0
RwUInt32 type_225220::sub_225AD0(const wchar_t *arg_0, RwInt32 arg_4)
{
    RwUInt32 var_4;

    switch (unk_B4)
    {
    case 0:
        var_4 = unk_54->sub_225F40(arg_0, arg_4);
        break;
    case 2:
        var_4 = unk_5C->sub_225F40(arg_0, arg_4);
        break;
    default:
        var_4 = unk_58->sub_225F40(arg_0, arg_4);
        break;
    }
    return var_4;
}

// match: ?sub_225B60@type_225220@@QAEGXZ @ 0x00225B60
RwUInt16 type_225220::sub_225B60()
{
    RwUInt16 var_4;

    switch (unk_B4)
    {
    case 0:
        var_4 = unk_54->sub_1E60E0();
        break;
    case 2:
        var_4 = unk_5C->sub_1E60E0();
        break;
    default:
        var_4 = unk_58->sub_1E60E0();
        break;
    }
    return var_4;
}

// match: ?sub_225BE0@type_1E5A60@@QAEIPBGPAI1H@Z @ 0x00225BE0
RwUInt32 type_1E5A60::sub_225BE0(const wchar_t *arg_0, RwUInt32 *arg_4, RwUInt32 *arg_8, RwInt32 arg_C)
{
    return sub_225F70(arg_0, 9999999, arg_4, arg_8, arg_C);
}

// match: ?sub_225C10@type_1E5A60@@QAEXPBGHIHPAUtype_1F5A50@@PAH@Z @ 0x00225C10
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_1E5A60::sub_225C10(const wchar_t *arg_0, RwInt32 arg_4, RwUInt32 arg_8, RwInt32 arg_C, type_1F5A50 *arg_10,
                             RwInt32 *arg_14)
{
    RwInt32 bp_8 = unk_0E / 2;
    RwReal locC = RwIm2DGetFarScreenZ();
    RwReal bp_4 = 20.0f;
    RwUInt32 var_14 = (arg_4 & 0xFF000000) + 0xFFFFFF;
    RwUInt32 ebp_10 = arg_4;

    for (RwInt32 var_18 = 0; var_18 != 4; ++var_18)
        arg_10[var_18].sub_1F5BA0();
    if (!*arg_0)
        return;
    if (!arg_8)
    {
        if (CODFH_DEBUG_LOGS)
            sub_1C8A30("Tried to draw text in an area 0 width. Text was %d chars long.\n", sub_1E6180(arg_0));
        return;
    }
    do
    {
        RwUInt32 frm_24;
        RwInt32 var_2C;
        const wchar_t *l1C;
        RwUInt32 loc20;

        sub_226050(arg_0, arg_8, &frm_24, &var_2C, &l1C);
        switch (arg_C)
        {
        case 0:
            loc20 = 0;
            break;
        case 1:
            loc20 = (arg_8 - frm_24) / 2;
            break;
        case 2:
            loc20 = arg_8 - frm_24;
            break;
        default:
            loc20 = 0;
            break;
        }
        RwInt32 var_28 = unk_08;
        while (arg_0 != l1C)
        {
            wchar_t lv_2D = *arg_0;
            RwUInt16 var_34 = lv_2D;
            switch (var_34)
            {
            case ' ':
                loc20 += var_28;
                break;
            case 9:
                loc20 += var_28 * 16;
                break;
            case 10:
                break;
            default:
                if (var_34 >= 1 && var_34 < 9)
                {
                    RwInt32 var_3C = var_34 - 1;
                    RwUInt32 var_38 = ((var_3C & 1) ? 0xFF : 0x60) | 0xFF000000 | ((var_3C & 2) ? 0xFF00 : 0x6000) |
                                      ((var_3C & 4) ? 0xFF0000 : 0x600000);
                    ebp_10 = arg_4 & var_38;
                }
                else
                {
                    type_1E2250 *bp_58 = sub_1E5940(var_34);
                    RwUInt32 p54 = bp_58->get_unk_12();
                    RwInt32 var_50 = bp_58->get_unk_13();
                    RwInt32 stk_64 = bp_8 - (RwInt8)bp_58->get_unk_14();
                    RwUInt32 var_60 = bp_58->get_unk_15();
                    type_1E0330_rect l4C;
                    l4C.unk_00 = (RwReal)loc20;
                    l4C.unk_04 = (RwReal)stk_64;
                    l4C.unk_08 = (RwReal)(loc20 + p54 + 1);
                    l4C.unk_0C = (RwReal)(stk_64 + var_50 + 1);
                    const type_1E0330_rect *var_5C = &bp_58->unk_00;
                    arg_10[var_60].sub_1F5C30(&l4C, locC, bp_4, var_5C, var_34 < 0x20 ? var_14 : ebp_10);
                    loc20 += unk_0A + p54;
                }
                break;
            }
            ++arg_0;
        }
        bp_8 += sub_1E60E0();
        arg_0 = l1C;
    } while (*arg_0);
    if (arg_14)
        *arg_14 = bp_8 - unk_0E / 2;
}

// match: ?sub_225F40@type_1E5A60@@QAEIPBGH@Z @ 0x00225F40
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwUInt32 type_1E5A60::sub_225F40(const wchar_t *arg_0, RwInt32 arg_4)
{
    RwUInt32 local_8;
    RwUInt32 var_4;
    return sub_225BE0(arg_0, &local_8, &var_4, arg_4);
}

// match: ?sub_225F70@type_1E5A60@@QAEIPBGIPAI1H@Z @ 0x00225F70
RwUInt32 type_1E5A60::sub_225F70(const wchar_t *arg_0, RwUInt32 arg_4, RwUInt32 *arg_8, RwUInt32 *arg_C, RwInt32 arg_10)
{
    RwInt32 bp_4;
    wchar_t var_208[0x100];
    RwInt32 l20C;
    if (arg_10 != -1)
    {
        memcpy(var_208, arg_0, arg_10);
        var_208[arg_10] = 0;
        arg_0 = var_208;
    }
    l20C = unk_0E / 2;
    while (*arg_0)
    {
        sub_226050(arg_0, arg_4, arg_8, &bp_4, &arg_0);
        l20C += sub_1E60E0();
        if (!*arg_0)
            *arg_C = l20C - unk_0E / 2;
    }
    return *arg_8;
}

// The first character of arg_0 past its spaces and tabs: an inline with no
// address, named for what it gives (the char layout's has its own).
inline const wchar_t *skip_blanks(const wchar_t *arg_0)
{
    while (*arg_0 == ' ' || *arg_0 == 9)
        ++arg_0;
    return arg_0;
}

// match: ?sub_226050@type_1E5A60@@QAEXPBGIPAIPAHPAPBG@Z @ 0x00226050
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_1E5A60::sub_226050(const wchar_t *arg_0, RwUInt32 arg_4, RwUInt32 *arg_8, RwInt32 *arg_C,
                             const wchar_t **arg_10)
{
    const wchar_t *l4 = arg_0;
    *arg_8 = 0;
    RwUInt32 local_C = 0;
    const wchar_t *var_8 = l4;
    *arg_10 = l4;
    while (1)
    {
        bool var_D = false;
        switch (*l4)
        {
        case 10:
            ++l4;
        case 0:
            var_D = true;
            *arg_10 = l4;
            *arg_8 += local_C;
            return;
        case ' ':
            var_D = true;
            local_C += unk_08;
            ++arg_C;
            break;
        default:
        {
            RwUInt16 var_14 = *l4;
            if (var_14 >= 9)
                local_C += sub_1E5940(var_14)->get_unk_12() + unk_0A;
            break;
        }
        }
        if (*arg_8 + local_C <= arg_4)
        {
            if (var_D)
            {
                *arg_8 += local_C;
                local_C = 0;
                var_8 = l4;
            }
        }
        else
        {
            if (var_8 == arg_0)
            {
                *arg_10 = l4 + 1;
                *arg_8 = local_C;
            }
            else
                *arg_10 = skip_blanks(var_8);
            return;
        }
        ++l4;
    }
}
