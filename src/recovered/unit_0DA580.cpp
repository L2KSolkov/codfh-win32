// The game's font (type_DA580): a wrapper of an Rt2d font with the text
// layout the shell and the HUD use. The original file name is not in the
// image, so it is named for its start address.

#include <stdio.h>
#include <string.h>

#include "rw/ostypes.h"
#include "rw/rt2d.h"
#include "rw/rt2dfont.h"
#include "rw/bastream.h"
#include "rw/babintex.h"
#include "rw/badevice.h"
#include "rw/baengine.h"
#include "game/functions.h"
#include "game/gameloop.h"
#include "types/type_DA580.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003D7FA8
extern const RwReal flt_3D7FA8 = 16.666666f;
// 0x003D7FAC
extern const RwReal flt_3D7FAC = 16.666666f;
// 0x003D7FB0
extern const RwReal flt_3D7FB0 = 16.666666f;
// 0x004292C8
RwReal flt_4292C8 = 1.0f;
// 0x004292D0
type_4292D0 unk_4292D0[20] = {
    { 15, "$ac$" },
    { 4, "$jm$" },
    { 3, "$sh$" },
    { 12, "$af$" },
    { 7, "$re$" },
    { 6, "$am$" },
    { 4, "$pu$" },
    { 10, "$pd$" },
    { 13, "$cw$" },
    { 14, "$ce$" },
    { 16, "$ue$" },
    { 23, "$ms$" },
    { 24, "$mc$" },
    { 11, "$pa$" },
    { 40, "$he$" },
    { 18, "$rc$" },
    { 1001, "$ud$" },
    { 1002, "$lr$" },
    { 1003, "$da$" },
    { 25, "$sv$" },
};
// 0x004B8930
RwUInt32 dword_4B8930[2];
// 0x004B8938
RwInt32 dword_4B8938[2];
// 0x004B8940
RwChar byte_4B8940[2][12];
// 0x004B8958
RwTexDictionary *dword_4B8958;
// 0x004B895C
RwTexDictionary *dword_4B895C;
// 0x004B8960
RwInt32 dword_4B8960;
// 0x004B8964
Rt2dBrush *brush;
// 0x004B8968
RwInt32 dword_4B8968;
// End of its data definitions.


// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3D7FA8@@3MB @ 0x003D7FA8
// match: ?flt_3D7FAC@@3MB @ 0x003D7FAC
// match: ?flt_3D7FB0@@3MB @ 0x003D7FB0
// match: ??_C@_0CC@FBOLPKIP@SHELL?2HUD?2INSTANCE?2XBOX?2F_HUD?4TX@ @ 0x003D7FB4
// match: ??_C@_0BC@LJHCEKJC@SHELL?2PAD?2PAD?4TXD?$AA@ @ 0x003D7FD8
// match: ??_C@_06LLCHCAHO@?5?5?5?5?$CFc?$AA@ @ 0x003D7FEC
// match: ??_C@_08FGEAILBK@?$CFc?5?5?5?5?$CFc?$AA@ @ 0x003D7FF4
// match: ??_C@_0CH@MDOJCJMM@Unable?5to?5open?5texture?5dictionar@ @ 0x003D8000
// match: ??_C@_0DA@OLPFEPAH@Loading?5HUD?5Texture?5Dictionary?5f@ @ 0x003D8028
// match: __ehhandler$?sub_DA680@type_DA580@@SAPAU1@PBD@Z>1>8 @ 0x0041CC98
// match: __ehhandler$?sub_DA680@type_DA580@@SAPAU1@PBD@Z>1 @ 0x0041CCA0
// match: ?flt_4292C8@@3MA @ 0x004292C8
// match: ?unk_4292D0@@3PAUtype_4292D0@@A @ 0x004292D0

// match: ??0type_DA580@@QAE@XZ @ 0x000DA580

type_DA580::type_DA580()
{
    RwRGBA var_4;

    unk_00 = 0;
    var_4.alpha = var_4.red = var_4.green = var_4.blue = 0xFF;
    Rt2dBrushSetRGBA(brush, &var_4, &var_4, &var_4, &var_4);
    dword_4B8960++;
}

// match: ??1type_DA580@@QAE@XZ @ 0x000DA5E0
type_DA580::~type_DA580()
{
    if (unk_00)
    {
        Rt2dFontDestroy(unk_00);
    }
    if (!--dword_4B8960 && dword_4B8958)
    {
        if (dword_4B8958)
        {
            RwTexDictionaryDestroy(dword_4B8958);
            dword_4B8958 = 0;
        }
        if (brush)
        {
            Rt2dBrushDestroy(brush);
            brush = 0;
        }
        if (dword_4B895C)
        {
            RwTexDictionaryDestroy(dword_4B895C);
            dword_4B895C = 0;
        }
    }
}

// match: ?sub_DA680@type_DA580@@SAPAU1@PBD@Z @ 0x000DA680
// match: __ehhandler$?sub_DA680@type_DA580@@SAPAU1@PBD@Z-0xB @ 0x00300CF0
// match: __ehhandler$?sub_DA680@type_DA580@@SAPAU1@PBD@Z @ 0x00300CFB
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
type_DA580 *type_DA580::sub_DA680(const RwChar *arg_0)
{
    type_DA580 *var_14;
    Rt2dFont *lv_10;

    lv_10 = 0;
    dword_4E23A8 = 1;
    if (!brush)
    {
        brush = Rt2dBrushCreate();
    }
    if (!dword_4B895C)
    {
        dword_4B895C = sub_DC000("SHELL\\PAD\\PAD.TXD");
    }
    if (arg_0)
    {
        if (!dword_4B8958)
        {
            dword_4B8958 = sub_DC000("SHELL\\HUD\\INSTANCE\\XBOX\\F_HUD.TXD");
            Rt2dFontTexDictionarySet(dword_4B8958);
        }
        lv_10 = Rt2dFontRead(arg_0);
        if (!lv_10)
        {
            return 0;
        }
    }
    var_14 = new type_DA580;
    var_14->unk_00 = lv_10;
    flt_4292C8 = 1.0f;
    dword_4E23A8 = 0;
    return var_14;
}

// match: ?sub_DA790@type_DA580@@QAEMXZ @ 0x000DA790
RwReal type_DA580::sub_DA790()
{
    return Rt2dFontGetHeight(unk_00);
}

// match: ?sub_DA7B0@type_DA580@@QAEMPBDM@Z @ 0x000DA7B0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwReal type_DA580::sub_DA7B0(const RwChar *arg_0, RwReal arg_4)
{
    const RwChar *var_80C;
    RwChar v808[0x800];

    var_80C = arg_0;
    if (Rt2dFontIsUnicode(unk_00))
    {
        sub_DA860(arg_0, (RwUInt16 *)v808);
        var_80C = v808;
    }
    if (arg_4 == 0.0f)
    {
        arg_4 = Rt2dFontGetHeight(unk_00);
    }
    {
        // Never used; the image's frame keeps their slots.
        RwInt32 var_810;
        RwInt32 var_814;
    }
    return Rt2dFontGetStringWidth(unk_00, var_80C, arg_4);
}

// match: ?sub_DA860@@YAXPBDPAG@Z @ 0x000DA860
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_DA860(const RwChar *arg_0, RwUInt16 *arg_4)
{
    const RwUInt8 *var_8;
    RwUInt32 l4;

    var_8 = (const RwUInt8 *)arg_0;
    for (l4 = 0; l4 < strlen(arg_0); l4++)
    {
        arg_4[l4] = var_8[l4];
    }
    arg_4[l4] = 0;
}

// match: ?sub_DA8C0@type_DA580@@QAEMPBDPAURt2dBBox@@M@Z @ 0x000DA8C0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwReal type_DA580::sub_DA8C0(const RwChar *arg_0, Rt2dBBox *arg_4, RwReal arg_8)
{
    bool var_825;
    const RwChar *var824;
    RwReal ebp_820;
    RwReal var_81C;
    const RwChar *loc818;
    RwInt32 slot_814;
    const RwChar *loc810;
    RwReal p80C;
    RwChar var808[0x800];

    slot_814 = 0;
    p80C = 0.0f;
    var_81C = 0.0f;
    var_825 = false;
    loc818 = arg_0;
    if (Rt2dFontIsUnicode(unk_00))
    {
        sub_DA860(arg_0, (RwUInt16 *)var808);
        loc818 = var808;
        var_825 = true;
    }
    if (arg_8 == 0.0f)
    {
        arg_8 = Rt2dFontGetHeight(unk_00);
    }
    loc810 = loc818;
    ebp_820 = arg_4->w / arg_8;
    slot_814 = FONT_CHAR(var_825, loc810);
    while (slot_814)
    {
        var824 = sub_DB3E0(loc810, ebp_820, &p80C);
        var_81C += arg_8;
        loc810 = FONT_CHAR(var_825, var824) ? FONT_NEXT(var_825, var824) : var824;
        slot_814 = FONT_CHAR(var_825, loc810);
    }
    {
        // Never used; the image's frame keeps their slots.
        RwInt32 var_82C;
        RwInt32 var_830;
    }
    return var_81C;
}

// match: ?sub_DAB00@type_DA580@@QAEXPBDPAURwV2d@@PAURwRGBA@@MPAURt2dFont@@@Z @ 0x000DAB00
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_DA580::sub_DAB00(const RwChar *arg_0, RwV2d *arg_4, RwRGBA *arg_8, RwReal arg_C, Rt2dFont *arg_10)
{
    Rt2dFont *var_814;
    RwInt32 local_810;
    const RwChar *var_80C;
    RwChar v808[0x800];

    var_814 = unk_00;
    if (arg_10)
    {
        unk_00 = arg_10;
    }
    if (!unk_00)
    {
        return;
    }
    var_80C = arg_0;
    if (Rt2dFontIsUnicode(unk_00))
    {
        sub_DA860(arg_0, (RwUInt16 *)v808);
        var_80C = v808;
    }
    if (arg_C == 0.0f)
    {
        arg_C = Rt2dFontGetHeight(unk_00);
    }
    Rt2dBrushSetRGBA(brush, arg_8, arg_8, arg_8, arg_8);
    local_810 = sub_19BD80(arg_0);
    if (!local_810)
    {
        sub_DB620(var_80C, arg_C, arg_4);
        Rt2dFontShow(unk_00, var_80C, arg_C, arg_4, brush);
    }
    sub_DBA10(var_80C);
    {
        // Never used; the image's frame keeps their slots.
        RwInt32 var_818;
        RwInt32 var_81C;
    }
    unk_00 = var_814;
}

// match: ?sub_DAC60@type_DA580@@QAEXPBDPAURt2dBBox@@MHPAURwRGBA@@M@Z @ 0x000DAC60
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_DA580::sub_DAC60(const RwChar *arg_0, Rt2dBBox *arg_4, RwReal arg_8, RwInt32 arg_C,
                           RwRGBA *arg_10, RwReal arg_14)
{
    bool var_831;
    RwReal v830;
    RwChar *var_82C;
    RwReal var_828;
    const RwChar *slot_824;
    RwChar *slot_820;
    RwInt32 var_81C;
    RwChar lcl_815;
    RwV2d slot_814;
    RwReal p80C;
    RwChar var808[0x800];

    var_81C = 0;
    p80C = 0.0f;
    var_831 = false;
    slot_824 = arg_0;
    if (Rt2dFontIsUnicode(unk_00))
    {
        sub_DA860(arg_0, (RwUInt16 *)var808);
        slot_824 = var808;
        var_831 = true;
    }
    switch (arg_C)
    {
    default:
        v830 = 0.0f;
        break;
    case 1:
        v830 = arg_14 * 0.5f;
        break;
    case 2:
        v830 = arg_14;
        break;
    }
    if (arg_14 == 0.0f)
    {
        arg_14 = Rt2dFontGetHeight(unk_00);
    }
    Rt2dBrushSetRGBA(brush, arg_10, arg_10, arg_10, arg_10);
    slot_820 = (RwChar *)slot_824;
    slot_814.y = arg_4->y + arg_4->h - arg_14 + arg_8;
    var_828 = arg_4->w / arg_14;
    var_81C = FONT_CHAR(var_831, slot_820);
    while (var_81C == ' ')
    {
        slot_820 = FONT_NEXT(var_831, slot_820);
        var_81C = FONT_CHAR(var_831, slot_820);
    }
    var_81C = FONT_CHAR(var_831, slot_820);
    while (var_81C)
    {
        var_82C = (RwChar *)sub_DB3E0(slot_820, var_828, &p80C);
        lcl_815 = *var_82C;
        *var_82C = 0;
        slot_814.x = (var_828 - p80C) * v830 + arg_4->x;
        if (slot_814.y + arg_14 <= arg_4->y + arg_4->h)
        {
            sub_DB620(slot_820, arg_14, &slot_814);
            Rt2dFontShow(unk_00, slot_820, arg_14, &slot_814, brush);
            sub_DBA10(slot_820);
        }
        *var_82C = lcl_815;
        slot_820 = FONT_CHAR(var_831, var_82C) ? FONT_NEXT(var_831, var_82C) : var_82C;
        var_81C = FONT_CHAR(var_831, slot_820);
        slot_814.y -= arg_14;
        if (slot_814.y < arg_4->y)
        {
            break;
        }
        var_81C = FONT_CHAR(var_831, slot_820);
        while (var_81C == ' ')
        {
            slot_820 = FONT_NEXT(var_831, slot_820);
            var_81C = FONT_CHAR(var_831, slot_820);
        }
    }
    {
        // Never used; the image's frame keeps their slots.
        RwInt32 var_838;
        RwInt32 var_83C;
    }
}

// match: ?sub_DB180@type_DA580@@QAEIPBDMM@Z @ 0x000DB180
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwUInt32 type_DA580::sub_DB180(const RwChar *arg_0, RwReal arg_4, RwReal arg_8)
{
    bool var_825;
    const RwChar *var824;
    RwReal ebp_820;
    const RwChar *var_81C;
    const RwChar *loc818;
    RwInt32 slot_814;
    RwUInt32 loc810;
    RwReal p80C;
    RwChar var808[0x800];

    slot_814 = 0;
    p80C = 0.0f;
    var_825 = false;
    loc810 = 0;
    var_81C = arg_0;
    if (Rt2dFontIsUnicode(unk_00))
    {
        sub_DA860(arg_0, (RwUInt16 *)var808);
        var_81C = var808;
        var_825 = true;
    }
    if (arg_8 == 0.0f)
    {
        arg_8 = Rt2dFontGetHeight(unk_00);
    }
    loc818 = var_81C;
    ebp_820 = arg_4 / arg_8;
    slot_814 = FONT_CHAR(var_825, loc818);
    while (slot_814 == ' ')
    {
        loc818 = FONT_NEXT(var_825, loc818);
        slot_814 = FONT_CHAR(var_825, loc818);
        loc810++;
    }
    slot_814 = FONT_CHAR(var_825, loc818);
    if (slot_814)
    {
        var824 = sub_DB3E0(loc818, ebp_820, &p80C);
        loc810 = var824 - var_81C;
        if (var_825)
        {
            loc810 /= 2;
        }
    }
    {
        // Never used; the image's frame keeps their slots.
        RwInt32 var_82C;
        RwInt32 var_830;
    }
    return loc810;
}

// match: ?sub_DB3E0@type_DA580@@QAEPBDPBDMPAM@Z @ 0x000DB3E0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
const RwChar *type_DA580::sub_DB3E0(const RwChar *arg_0, RwReal arg_4, RwReal *arg_8)
{
    rt2dCharRect *local_28;
    RwInt32 local_24;
    bool var_1D;
    RwInt32 loc1C;
    const RwChar *bp_18;
    const RwChar *var_14;
    RwReal lv_10;
    const RwChar *var_C;
    rt2dCharRect *bp_8;
    RwInt32 bp_4;

    bp_4 = 0;
    loc1C = 0;
    var_1D = false;
    *arg_8 = 0.0f;
    bp_8 = (rt2dCharRect *)rwSListGetArray(unk_00->charMap);
    var_1D = (bool)Rt2dFontIsUnicode(unk_00);
    bp_18 = arg_0;
    bp_4 = FONT_CHAR(var_1D, bp_18);
    while (bp_4 == ' ')
    {
        bp_18 = FONT_NEXT(var_1D, bp_18);
        bp_4 = FONT_CHAR(var_1D, bp_18);
    }
    var_14 = bp_18;
    var_C = bp_18;
    local_24 = 1;
    lv_10 = 0.0f;
    while (bp_4 > 0)
    {
        FontCharGetCode(loc1C, bp_4, unk_00);
        if (local_24 && bp_4 == ' ')
        {
            local_24 = 0;
            var_C = bp_18;
            *arg_8 = lv_10;
        }
        else
        {
            local_24 = 1;
            if (bp_4 == '\n')
            {
                var_C = bp_18;
                *arg_8 = lv_10;
            }
        }
        if (loc1C >= 0)
        {
            local_28 = &bp_8[loc1C];
            lv_10 += local_28->width + unk_00->intergap;
        }
        if (lv_10 > arg_4 || bp_4 == '\n')
        {
            return var_C;
        }
        bp_18 = FONT_NEXT(var_1D, bp_18);
        bp_4 = FONT_CHAR(var_1D, bp_18);
    }
    return bp_18;
}

// match: ?sub_DB620@type_DA580@@QAEXPBDMPAURwV2d@@@Z @ 0x000DB620
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_DA580::sub_DB620(const RwChar *arg_0, RwReal arg_4, RwV2d *arg_8)
{
    RwUInt32 local_74;
    RwUInt16 *var_70;
    RwUInt32 l6C;
    RwChar local_68[0x48];
    RwChar *bp_18;
    bool var_11;
    RwChar *lv_10;
    RwInt32 var_C;
    RwChar *bp_8;
    RwInt32 bp_4;

    var_11 = false;
    bp_18 = (RwChar *)arg_0;
    if (!dword_4B895C)
    {
        return;
    }
    dword_4B8968 = 0;
    var_11 = (bool)Rt2dFontIsUnicode(unk_00);
    var_C = 0;
    bp_8 = bp_18;
    bp_4 = FONT_CHAR(var_11, bp_8);
    while (bp_4)
    {
        if (bp_4 == '$')
        {
            lv_10 = FONT_NEXT(var_11, bp_8);
            if (!FONT_CHAR(var_11, lv_10))
            {
                return;
            }
            bp_4 = FONT_CHAR(var_11, lv_10);
            while (bp_4)
            {
                if (bp_4 == '$')
                {
                    break;
                }
                lv_10 = FONT_NEXT(var_11, lv_10);
                bp_4 = FONT_CHAR(var_11, lv_10);
            }
            if (!bp_4)
            {
                return;
            }
            l6C = FONT_NEXT(var_11, lv_10) - bp_8;
            if (l6C >= 0x40)
            {
                return;
            }
            var_C = bp_8 - bp_18;
            memcpy(byte_4B8940[dword_4B8968], bp_8, l6C);
            byte_4B8940[dword_4B8968][l6C] = 0;
            byte_4B8940[dword_4B8968][l6C + 1] = 0;
            dword_4B8938[dword_4B8968] = var_C;
            dword_4B8930[dword_4B8968] = l6C;
            if (var_11)
            {
                FONT_NARROW(local_68, byte_4B8940[dword_4B8968]);
            }
            else
            {
                strcpy(local_68, byte_4B8940[dword_4B8968]);
            }
            if (sub_DBB80(local_68, bp_18, bp_8, arg_8, arg_4))
            {
                if (var_11)
                {
                    var_70 = (RwUInt16 *)(bp_18 + var_C);
                    for (local_74 = 0; local_74 < l6C / 2; local_74++)
                    {
                        *var_70 = ' ';
                        var_70++;
                    }
                }
                else
                {
                    memset(bp_18 + var_C, ' ', l6C);
                }
                dword_4B8968++;
            }
            bp_8 = lv_10;
        }
        bp_8 = FONT_NEXT(var_11, bp_8);
        bp_4 = FONT_CHAR(var_11, bp_8);
    }
}

// match: ?sub_DBA10@type_DA580@@QAEXPBD@Z @ 0x000DBA10
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_DA580::sub_DBA10(const RwChar *arg_0)
{
    RwInt32 var_8;
    RwChar *l4;

    l4 = (RwChar *)arg_0;
    for (var_8 = 0; var_8 < dword_4B8968; var_8++)
    {
        memcpy(l4 + dword_4B8938[var_8], byte_4B8940[var_8], dword_4B8930[var_8]);
    }
    dword_4B8968 = 0;
}

// match: ?sub_DBA80@type_DA580@@QAEPAURwRaster@@PBD@Z @ 0x000DBA80
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwRaster *type_DA580::sub_DBA80(const RwChar *arg_0)
{
    RwUInt32 var_5C;
    RwTexture *bp_58;
    RwInt32 p54;
    RwChar var_50[0x40];
    RwRaster *var_C;
    RwInt32 bp_8;
    RwUInt32 bp_4;

    bp_4 = 20;
    p54 = -1;
    for (var_5C = 0; var_5C < bp_4; var_5C++)
    {
        if (!strcmp(arg_0, unk_4292D0[var_5C].unk_04))
        {
            p54 = unk_4292D0[var_5C].unk_00;
            break;
        }
    }
    if (p54 == -1)
    {
        return 0;
    }
    if (p54 < 1000)
    {
        bp_8 = unk_4B9308.sub_EE7F0(p54, 0);
        sprintf(var_50, "%.4d", bp_8);
    }
    else
    {
        sprintf(var_50, "%.4d", p54);
    }
    bp_58 = RwTexDictionaryFindNamedTexture(dword_4B895C, var_50);
    var_C = 0;
    if (bp_58)
    {
        var_C = bp_58->raster;
    }
    return var_C;
}

// match: ?sub_DBB80@type_DA580@@QAE_NPADPBD1PAURwV2d@@M@Z @ 0x000DBB80
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
bool type_DA580::sub_DBB80(RwChar *arg_0, const RwChar *arg_4, const RwChar *arg_8, RwV2d *arg_C, RwReal arg_10)
{
    RwInt32 var_120;
    RwChar *var_11C;
    RwReal slot_118;
    bool var_111;
    RwV2d local_110;
    RwV2d lv_108;
    RwChar var_100[0x40];
    RwReal var_C0;
    RwReal m_BC;
    RwV2d local_B8;
    RwRaster *local_B0;
    RwReal local_AC;
    RwChar pA8[0x80];
    RwReal frm_24;
    RwReal var_20;
    RwV2d l1C;
    RwReal ebp_14;
    RwReal lv_10;
    RwReal var_C;
    RwReal bp_8;
    RwReal bp_4;

    local_B8 = *arg_C;
    var_111 = (bool)Rt2dFontIsUnicode(unk_00);
    local_B0 = sub_DBA80(arg_0);
    if (!local_B0)
    {
        return false;
    }
    if (arg_4 != arg_8)
    {
        var_11C = (RwChar *)FONT_PREV(var_111, arg_8);
        sprintf(var_100, "%c    %c", (RwChar)FONT_CHAR(var_111, var_11C),
                (RwChar)FONT_CHAR(var_111, FONT_SKIP(var_111, arg_8, strlen(arg_0))));
        var_120 = FONT_CHAR(var_111, var_11C);
        FONT_PUT(var_111, var_11C, 0);
        local_AC = Rt2dFontGetStringWidth(unk_00, arg_4, arg_10);
        FONT_PUT(var_111, var_11C, var_120);
    }
    else
    {
        sprintf(var_100, "    %c", (RwChar)FONT_CHAR(var_111, FONT_SKIP(var_111, arg_8, strlen(arg_0))));
        local_AC = 0.0f;
    }
    // Two slots below the inlines' with no code (see unused_slot).
    unused_slot();
    unused_slot();
    if (var_111)
    {
        sub_DA860(var_100, (RwUInt16 *)pA8);
    }
    else
    {
        strcpy(pA8, var_100);
    }
    var_C = Rt2dFontGetStringWidth(unk_00, pA8, arg_10);
    Rt2dDeviceGetMetric(&var_C0, &m_BC, &var_20, &frm_24);
    Rt2dDeviceGetStep(&local_110, &l1C, &lv_108);
    ebp_14 = (RwReal)local_B0->width;
    slot_118 = (RwReal)local_B0->height;
    bp_4 = arg_10 * local_110.x;
    lv_10 = ebp_14 / slot_118;
    bp_8 = bp_4 * lv_10 * l1C.y;
    bp_8 *= flt_4292C8;
    bp_4 *= flt_4292C8;
    local_B8.x = (-1.0f * lv_108.x + arg_C->x + local_AC + var_C / 2.0f) / local_110.x;
    // Height is read unsigned here (fild of a zero-extended qword).
    local_B8.y = (RwReal)(RwUInt32)Height - (-1.0f * lv_108.y + arg_C->y + arg_10 / 4.0f) / l1C.y;
    sub_DC0D0(local_B0, &local_B8, bp_8, bp_4, brush);
    return true;
}

// match: ?sub_DC000@@YAPAURwTexDictionary@@PBD@Z @ 0x000DC000
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwTexDictionary *sub_DC000(const RwChar *arg_0)
{
    RwChar var_468[0x258];
    RwChar var_210[0x200];
    RwTexDictionary *var8;
    RwStream *l4;

    var8 = 0;
    l4 = 0;
    sub_D7F20(var_210, arg_0);
    sub_16C220("Loading HUD Texture Dictionary file from: %s...", var_210);
    l4 = RwStreamOpen(rwSTREAMFILENAME, rwSTREAMREAD, var_210);
    sprintf(var_468, "Unable to open texture dictionary: %s\n", var_210);
    if (l4)
    {
        if (RwStreamFindChunk(l4, rwID_TEXDICTIONARY, 0, 0))
        {
            var8 = RwTexDictionaryStreamRead(l4, 0);
        }
        RwStreamClose(l4, 0);
    }
    return var8;
}

// match: ?sub_DC0D0@@YAXPAURwRaster@@PAURwV2d@@MMPAURt2dBrush@@@Z @ 0x000DC0D0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_DC0D0(RwRaster *arg_0, RwV2d *arg_4, RwReal arg_8, RwReal arg_C, Rt2dBrush *arg_10)
{
    RwInt32 var_B4;
    RwIm2DVertex vB0[4];
    RwReal m_40;
    RwReal v3C;
    void *r38;
    RwCamera *z34;
    void *ebp_30;
    void *v2C;
    void *lcl_28;
    void *frm_24;
    void *var_20;
    void *l1C;
    void *m_18;
    void *ebp_14;
    void *lv_10;
    RwReal var_C;
    RwReal bp_8;
    RwInt32 bp_4;

    z34 = RwCameraGetCurrentCamera();
    var_C = arg_4->x;
    bp_8 = arg_4->y;
    bp_4 = 0;
    for (var_B4 = 0; var_B4 < 4; var_B4++)
    {
        RwIm2DVertexSetScreenZ(&vB0[var_B4], RwIm2DGetNearScreenZ());
        RwIm2DVertexSetRecipCameraZ(&vB0[var_B4], 1.0f / RwCameraGetNearClipPlane(z34));
        RwIm2DVertexSetIntRGBA(&vB0[var_B4], 255, 255, 255, arg_10->colorCache.alpha);
    }
    m_40 = arg_8 / 2.0f;
    v3C = arg_C / 2.0f;
    RwIm2DVertexSetScreenX(&vB0[0], var_C - m_40);
    RwIm2DVertexSetScreenY(&vB0[0], bp_8 + v3C);
    RwIm2DVertexSetScreenX(&vB0[1], var_C - m_40);
    RwIm2DVertexSetScreenY(&vB0[1], bp_8 - v3C);
    RwIm2DVertexSetScreenX(&vB0[2], var_C + m_40);
    RwIm2DVertexSetScreenY(&vB0[2], bp_8 + v3C);
    RwIm2DVertexSetScreenX(&vB0[3], var_C + m_40);
    RwIm2DVertexSetScreenY(&vB0[3], bp_8 - v3C);
    RwIm2DVertexSetU(&vB0[0], 0.0f, 1.0f);
    RwIm2DVertexSetV(&vB0[0], 1.0f, 1.0f);
    RwIm2DVertexSetU(&vB0[1], 0.0f, 1.0f);
    RwIm2DVertexSetV(&vB0[1], 0.0f, 1.0f);
    RwIm2DVertexSetU(&vB0[2], 1.0f, 1.0f);
    RwIm2DVertexSetV(&vB0[2], 1.0f, 1.0f);
    RwIm2DVertexSetU(&vB0[3], 1.0f, 1.0f);
    RwIm2DVertexSetV(&vB0[3], 0.0f, 1.0f);
    v2C = 0;
    RwRenderStateGet(rwRENDERSTATETEXTURERASTER, &v2C);
    RwRenderStateGet(rwRENDERSTATETEXTUREFILTER, &lv_10);
    RwRenderStateGet(rwRENDERSTATEFOGENABLE, &ebp_30);
    RwRenderStateGet(rwRENDERSTATEZTESTENABLE, &frm_24);
    RwRenderStateGet(rwRENDERSTATEZWRITEENABLE, &ebp_14);
    RwRenderStateGet(rwRENDERSTATETEXTUREADDRESS, &lcl_28);
    RwRenderStateGet(rwRENDERSTATEVERTEXALPHAENABLE, &l1C);
    RwRenderStateGet(rwRENDERSTATESRCBLEND, &r38);
    RwRenderStateGet(rwRENDERSTATEDESTBLEND, &var_20);
    RwRenderStateGet(rwRENDERSTATECULLMODE, &m_18);
    RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, (void *)rwFILTERLINEAR);
    RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void *)FALSE);
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void *)FALSE);
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void *)FALSE);
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void *)arg_0);
    RwRenderStateSet(rwRENDERSTATETEXTUREADDRESS, (void *)rwTEXTUREADDRESSCLAMP);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)TRUE);
    RwRenderStateSet(rwRENDERSTATESRCBLEND, (void *)rwBLENDSRCALPHA);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void *)rwBLENDINVSRCALPHA);
    RwRenderStateSet(rwRENDERSTATECULLMODE, (void *)rwCULLMODECULLNONE);
    RwIm2DRenderPrimitive(rwPRIMTYPETRISTRIP, vB0, 4);
    RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, lv_10);
    RwRenderStateSet(rwRENDERSTATEFOGENABLE, ebp_30);
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, frm_24);
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, ebp_14);
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, v2C);
    RwRenderStateSet(rwRENDERSTATETEXTUREADDRESS, lcl_28);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, l1C);
    RwRenderStateSet(rwRENDERSTATESRCBLEND, r38);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, var_20);
    RwRenderStateSet(rwRENDERSTATECULLMODE, m_18);
}
