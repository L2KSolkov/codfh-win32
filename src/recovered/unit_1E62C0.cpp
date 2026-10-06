// kujuUI's font lookups: split from unit_1E5280.cpp at 0x1E62C0, where the image ends that object
// (its deferred functions come before the next out-of-line one; PLAN M7).

#include <string.h>
#include "game/kujuui.h"
#include "game/kujufont.h"
#include "game/fileio.h"
#include "game/parsedfile.h"

using namespace kujuUI;

// match: .CRT$XCU+0 @ 0x0042732C
// match: .CRT$XCU+4 @ 0x00427330
// match: .CRT$XCU+8 @ 0x00427334
// match: .CRT$XCU+12 @ 0x00427338
// match: .CRT$XCU+16 @ 0x0042733C
// match: .CRT$XCU+20 @ 0x00427340
// match: .CRT$XCU+24 @ 0x00427344
// match: _$E1 @ 0x0030D860
// match: _$E2 @ 0x0030EFA0
// match: _$E4 @ 0x0030D8A0
// match: _$E5 @ 0x0030EFB0
// match: _$E7 @ 0x0030D8E0
// match: _$E8 @ 0x0030EFC0
// match: _$E10 @ 0x0030D920
// match: _$E11 @ 0x0030EFD0
// match: _$E13 @ 0x0030D960
// match: _$E14 @ 0x0030EFE0
// match: _$E16 @ 0x0030D9A0
// match: _$E17 @ 0x0030EFF0
// match: _$E19 @ 0x0030D9E0
// match: _$E20 @ 0x0030F000

// match: __ehhandler$??0type_1E6350@@QAE@ABU0@@Z>1>8 @ 0x004200E8
// match: __ehhandler$??0type_1E6350@@QAE@ABU0@@Z>1 @ 0x004200F0
// match: __ehhandler$??_F?$type_E8780@Utype_1E5A60@@@@QAEXXZ>1>8 @ 0x0042010C
// match: __ehhandler$??_F?$type_E8780@Utype_1E5A60@@@@QAEXXZ>1 @ 0x00420114
// match: __ehhandler$??0type_1E6350@@QAE@PBU?$type_E8780@Utype_1E5A60@@@@PBI@Z>1>8 @ 0x00420130
// match: __ehhandler$??0type_1E6350@@QAE@PBU?$type_E8780@Utype_1E5A60@@@@PBI@Z>1 @ 0x00420138
// match: __ehhandler$?sub_1E6610@type_1E6350@@QAE?AU?$type_E8780@Utype_1E5A60@@@@H@Z>1>8 @ 0x00420154
// match: __ehhandler$?sub_1E6610@type_1E6350@@QAE?AU?$type_E8780@Utype_1E5A60@@@@H@Z>1 @ 0x00420164
// match: __ehhandler$??_F?$type_E8780@Utype_1E5A60@@@@QAEXXZ-0x8 @ 0x00303B60
// match: __ehhandler$??_F?$type_E8780@Utype_1E5A60@@@@QAEXXZ @ 0x00303B68
// match: ??_F?$type_E8780@Utype_1E5A60@@@@QAEXXZ @ 0x001E63F0
// match: ??_C@_0EA@JJPGDHKA@Tried?5to?5draw?5text?5in?5an?5area?50?5@ @ 0x003E7360
// match: ??_C@_07LDMOCHMI@fontset?$AA@ @ 0x003E73A0

// match: ?sub_1E62C0@@YAXHHHPAU?$type_E8780@Utype_1E5A60@@@@PAI@Z @ 0x001E62C0
void sub_1E62C0(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, type_E8780<type_1E5A60> *arg_C, RwUInt32 *arg_10)
{
    if (arg_C[arg_0].sub_E87C0())
    {
        if (!arg_C[arg_4].sub_E87C0())
        {
            arg_C[arg_0] = arg_C[arg_4];
            arg_10[arg_0] = arg_10[arg_4];
        }
        else
        {
            arg_C[arg_0] = arg_C[arg_8];
            arg_10[arg_0] = arg_10[arg_8];
        }
    }
}
// match: ??0type_1E6350@@QAE@PBU?$type_E8780@Utype_1E5A60@@@@PBI@Z @ 0x001E6350
// match: __ehhandler$??0type_1E6350@@QAE@PBU?$type_E8780@Utype_1E5A60@@@@PBI@Z-0x13 @ 0x00303B80
// match: __ehhandler$??0type_1E6350@@QAE@PBU?$type_E8780@Utype_1E5A60@@@@PBI@Z @ 0x00303B93
type_1E6350::type_1E6350(const type_E8780<type_1E5A60> *arg_0, const RwUInt32 *arg_4)
{
    for (RwInt32 var_10 = 0; var_10 != 6; ++var_10)
        unk_00[var_10] = arg_0[var_10];
    memcpy(unk_18, arg_4, 0x18);
}
// match: ??0type_1E6350@@QAE@ABU0@@Z @ 0x001E6450
type_1E6350::type_1E6350(const type_1E6350 &arg_0)
{
    for (RwInt32 var_10 = 0; var_10 != 6; ++var_10)
        unk_00[var_10] = arg_0.unk_00[var_10];
    memcpy(unk_18, arg_0.unk_18, 0x18);
}
// match: ??1type_1E6350@@QAE@XZ @ 0x001E64F0
type_1E6350::~type_1E6350()
{
}
// match: ?sub_1E6510@@YAXPAU?$type_E8780@Utype_1E5A60@@@@PAI@Z @ 0x001E6510
void sub_1E6510(type_E8780<type_1E5A60> *arg_0, RwUInt32 *arg_4)
{
    sub_1E62C0(3, 0, 0, arg_0, arg_4);
    sub_1E62C0(4, 3, 0, arg_0, arg_4);
    sub_1E62C0(1, 0, 0, arg_0, arg_4);
    sub_1E62C0(2, 1, 0, arg_0, arg_4);
    sub_1E62C0(5, 1, 0, arg_0, arg_4);
}

namespace kujuUI
{
extern type_1C9590 unk_503FE4;
extern type_1C9590 unk_504010;
extern type_1C9590 unk_50403C;
extern type_1C9590 unk_504068;
extern type_1C9590 unk_504094;
extern type_1C9590 unk_5040C0;
extern cScopeValidator unk_5040F0;
}
extern kujuUI::cScopeValidator *dword_503FE0;
// match: ?sub_1E6590@@YAPBVcScopeValidator@kujuUI@@XZ @ 0x001E6590
const cScopeValidator *sub_1E6590()
{
    if (!dword_503FE0)
    {
        unk_5040F0.sub_1C9F50(&unk_504068);
        unk_5040F0.sub_1C9F50(&unk_50403C);
        unk_5040F0.sub_1C9F50(&unk_504094);
        unk_5040F0.sub_1C9F50(&unk_504010);
        unk_5040F0.sub_1C9F50(&unk_5040C0);
        unk_5040F0.sub_1C9F50(&unk_503FE4);
        dword_503FE0 = &unk_5040F0;
    }
    return dword_503FE0;
}
// match: ?sub_1E6610@type_1E6350@@QAE?AU?$type_E8780@Utype_1E5A60@@@@H@Z @ 0x001E6610
// match: __ehhandler$?sub_1E6610@type_1E6350@@QAE?AU?$type_E8780@Utype_1E5A60@@@@H@Z-0x21 @ 0x00303BA0
// match: __ehhandler$?sub_1E6610@type_1E6350@@QAE?AU?$type_E8780@Utype_1E5A60@@@@H@Z @ 0x00303BC1
type_E8780<type_1E5A60> type_1E6350::sub_1E6610(RwInt32 arg_0)
{
    return type_E8780<type_1E5A60>(unk_00[arg_0]);
}
// match: ?sub_1E6690@type_1E5A60@@QAEXPBDHIHPAUtype_1F5A50@@PAH@Z @ 0x001E6690
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_1E5A60::sub_1E6690(const RwChar *arg_0, RwInt32 arg_4, RwUInt32 arg_8, RwInt32 arg_C, type_1F5A50 *arg_10,
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
            sub_1C8A30("Tried to draw text in an area 0 width. Text was %d chars long.\n", sub_1E6160(arg_0));
        return;
    }
    do
    {
        RwUInt32 frm_24;
        RwInt32 var_2C;
        const RwChar *l1C;
        RwUInt32 loc20;

        sub_1E69D0(arg_0, arg_8, &frm_24, &var_2C, &l1C);
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
            RwChar lv_2D = *arg_0;
            RwUInt16 var_34 = char_code(lv_2D);
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
// The first character of arg_0 past its spaces and tabs: an inline with no
// address, named for what it gives. Evidence: the line measure
// (sub_1E69D0) walks a copy of the pointer in a slot after its own locals.
inline const RwChar *skip_blanks(const RwChar *arg_0)
{
    while (*arg_0 == ' ' || *arg_0 == 9)
        ++arg_0;
    return arg_0;
}

// match: ?sub_1E69D0@type_1E5A60@@QAEXPBDIPAIPAHPAPBD@Z @ 0x001E69D0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_1E5A60::sub_1E69D0(const RwChar *arg_0, RwUInt32 arg_4, RwUInt32 *arg_8, RwInt32 *arg_C,
                             const RwChar **arg_10)
{
    const RwChar *l4 = arg_0;
    *arg_8 = 0;
    RwUInt32 local_C = 0;
    const RwChar *var_8 = l4;
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
            RwUInt16 var_14 = char_code(*l4);
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

namespace kujuUI
{

// The value definitions and scope validators, built by their dynamic
// initializers (their exit functions call the out-of-line destructors).
type_1C9590 unk_504068(sub_1F80C0(), 1, 3, 3, 3, 3, 0, 0, 0);
type_1C9590 unk_50403C(sub_1F80D0(), 1, 3, 3, 3, 3, 0, 0, 0);
type_1C9590 unk_504094(sub_1F80E0(), 1, 3, 3, 3, 3, 0, 0, 0);
type_1C9590 unk_504010(sub_1F80F0(), 1, 3, 3, 3, 3, 0, 0, 0);
type_1C9590 unk_5040C0(sub_1F8100(), 1, 3, 3, 3, 3, 0, 0, 0);
type_1C9590 unk_503FE4(sub_1F8110(), 1, 3, 3, 3, 3, 0, 0, 0);
cScopeValidator unk_5040F0("fontset", "end", 2);
}
