/*
 * kujuUI's fonts (game/kujufont.h): the font (its glyphs and texture pages,
 * the list of those loaded), the loader, the layout of a string into text
 * pages, and the font sets.
 */
#include <string.h>
#include "game/kujuui.h"
#include "game/kujufont.h"
#include "game/fileio.h"
#include "game/parsedfile.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x0042CF80
type_42CF80 unk_42CF80[40] = {
    { 256, 22 },
    { 257, 20 },
    { 258, 23 },
    { 259, 21 },
    { 260, 28 },
    { 261, 28 },
    { 262, 28 },
    { 263, 28 },
    { 264, 28 },
    { 265, 28 },
    { 266, 28 },
    { 267, 28 },
    { 268, 28 },
    { 269, 28 },
    { 270, 28 },
    { 271, 28 },
    { 320, 28 },
    { 321, 28 },
    { 322, 28 },
    { 323, 28 },
    { 324, 28 },
    { 325, 28 },
    { 326, 28 },
    { 327, 28 },
    { 328, 28 },
    { 329, 28 },
    { 330, 28 },
    { 332, 28 },
    { 333, 28 },
    { 334, 28 },
    { 335, 28 },
    { 384, 28 },
    { 385, 28 },
    { 394, 25 },
    { 395, 26 },
    { 396, 25 },
    { 397, 25 },
    { 398, 26 },
    { 399, 26 },
    { -1, 20 },
};
// 0x0042D0C0
const RwChar *dword_42D0C0 = "";
// 0x0042D0C4
const RwChar *dword_42D0C4 = ".dds";
// 0x0042D0C8
const RwChar *dword_42D0C8 = ".bin";
// 0x00503FD0
type_1E5A60 *dword_503FD0;
// 0x00503FE0
kujuUI::cScopeValidator *dword_503FE0;
// End of its data definitions.

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_04GKHLBAIJ@?4bin?$AA@ @ 0x003E7308
// match: ??_7type_1E5A60@@6B@ @ 0x003E7310
// match: ??_7type_3E7314@@6B@ @ 0x003E7314
// match: ??_C@_04JCAPCJAP@?4tga?$AA@ @ 0x003E7318
// match: ??_C@_0DL@MFAFKIMP@Maximum?5number?5of?5textures?5per?5f@ @ 0x003E7320
// match: __ehhandler$??0type_1E5A60@@QAE@PBDPBUtype_1E5A80_header@@PBUtype_1E2250_entry@kujuUI@@HPBQAUtype_1E5830@@H@Z>1>8 @ 0x00420028
// match: __ehhandler$??0type_1E5A60@@QAE@PBDPBUtype_1E5A80_header@@PBUtype_1E2250_entry@kujuUI@@HPBQAUtype_1E5830@@H@Z>1 @ 0x00420040
// match: __ehhandler$??1type_1E5A60@@UAE@XZ>1>8 @ 0x0042005C
// match: __ehhandler$??1type_1E5A60@@UAE@XZ>1 @ 0x0042006C
// match: __ehhandler$??1type_1E5830@@QAE@XZ>1>8 @ 0x00420088
// match: __ehhandler$??1type_1E5830@@QAE@XZ>1 @ 0x00420090
// match: __ehhandler$?sub_1E5A80@@YA?AU?$type_E8780@Utype_1E5A60@@@@PBD@Z>1>8 @ 0x004200AC
// match: __ehhandler$?sub_1E5A80@@YA?AU?$type_E8780@Utype_1E5A60@@@@PBD@Z>1 @ 0x004200CC
// match: .CRT$XCU+0 @ 0x00427320
// match: .CRT$XCU+4 @ 0x00427324
// match: .CRT$XCU+8 @ 0x00427328
// match: ?unk_42CF80@@3PAUtype_42CF80@@A @ 0x0042CF80
// match: ?dword_42D0C0@@3PBDB @ 0x0042D0C0
// match: ?dword_42D0C4@@3PBDB @ 0x0042D0C4
// match: ?dword_42D0C8@@3PBDB @ 0x0042D0C8

// match: _$E1 @ 0x0030D800
// match: _$E3 @ 0x0030D820
// match: _$E5 @ 0x0030D840

using namespace kujuUI;

// The font's last glyph (the one for missing characters): an inline with
// no address. Evidence: the constructor's frame is 32 bytes larger when
// it takes the address directly (the name's declined string constructor
// leaves its slots reserved until an inline call).
inline kujuUI::type_1E2250 *last_glyph(type_1E5A60 *arg_0)
{
    return &arg_0->unk_30[arg_0->unk_38 - 1];
}

// match: ??0type_1E5A60@@QAE@PBDPBUtype_1E5A80_header@@PBUtype_1E2250_entry@kujuUI@@HPBQAUtype_1E5830@@H@Z @ 0x001E5280
// match: __ehhandler$??0type_1E5A60@@QAE@PBDPBUtype_1E5A80_header@@PBUtype_1E2250_entry@kujuUI@@HPBQAUtype_1E5830@@H@Z-0x24 @ 0x00303AA0
// match: __ehhandler$??0type_1E5A60@@QAE@PBDPBUtype_1E5A80_header@@PBUtype_1E2250_entry@kujuUI@@HPBQAUtype_1E5830@@H@Z @ 0x00303AC4
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
type_1E5A60::type_1E5A60(const RwChar *arg_0, const type_1E5A80_header *arg_4, const type_1E2250_entry *arg_8,
                         RwInt32 arg_C, type_1E5830 *const *arg_10, RwInt32 arg_14)
    : unk_08(arg_4->unk_18), unk_0A(arg_4->unk_1A), unk_0C(arg_4->unk_1C), unk_0E(arg_4->unk_16), unk_10(arg_0)
{
    RwInt32 lv_10;
    const type_42CF80 *var_14;

    unk_2C = dword_503FD0;
    unk_38 = arg_C;
    unk_3A = arg_14;
    unk_30 = new type_1E2250[arg_C + 0x27];
    for (RwInt32 var_18 = 0; var_18 != arg_C; ++var_18)
    {
        type_1E2250 *l1C;
        RwInt32 loc20;
        const type_1E2250_entry *w24;
        RwRaster *var_28;
        RwUInt32 var_2C;
        RwUInt32 var_30;

        w24 = &arg_8[var_18];
        loc20 = w24->unk_02;
        var_28 = arg_10[loc20]->unk_1C->unk_00;
        var_30 = var_28->width;
        var_2C = var_28->height;
        {
            type_1E2250 var_48(w24, (RwReal)var_30, (RwReal)var_2C);
            l1C = &unk_30[var_18];
            *l1C = var_48;
        }
    }
    for (lv_10 = 0; lv_10 != arg_14; ++lv_10)
        unk_3C[lv_10] = arg_10[lv_10];
    for (; lv_10 != 4; ++lv_10)
        unk_3C[lv_10] = 0;
    dword_503FD0 = this;
    var_14 = unk_42CF80;
    while (var_14->unk_00 != -1)
    {
        type_1E2250 *lv_64 = sub_1E5940(var_14->unk_04);
        type_1E2250 lcl_60(*lv_64, (RwUInt16)var_14->unk_00);
        unk_30[unk_38] = lcl_60;
        ++unk_38;
        ++var_14;
    }
    unk_34 = last_glyph(this);
}

// match: ??1type_3E7314@@UAE@XZ @ 0x001E5600
// match: ??_Gtype_3E7314@@UAEPAXI@Z @ 0x001E5620
// match: ??_Gtype_1E5A60@@UAEPAXI@Z @ 0x001E5650
// match: ??_Etype_1E2250@kujuUI@@QAEPAXI@Z @ 0x001E5680

// match: ??1type_1E5A60@@UAE@XZ @ 0x001E56F0
// match: __ehhandler$??1type_1E5A60@@UAE@XZ-0x13 @ 0x00303AD0
// match: __ehhandler$??1type_1E5A60@@UAE@XZ @ 0x00303AE3
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
type_1E5A60::~type_1E5A60()
{
    delete[] unk_30;
    type_1E5A60 *lv_10 = 0;
    type_1E5A60 *var_14 = dword_503FD0;
    while (var_14 != this)
    {
        lv_10 = var_14;
        var_14 = var_14->unk_2C;
    }
    for (RwUInt32 var_18 = 0; var_18 < 4; ++var_18)
    {
        type_1E5830 *var_1C = unk_3C[var_18];
        delete var_1C;
    }
    if (lv_10)
        lv_10->unk_2C = unk_2C;
    else
        dword_503FD0 = unk_2C;
}

// match: ??1type_1E5830@@QAE@XZ @ 0x001E5830
// match: __ehhandler$??1type_1E5830@@QAE@XZ-0x8 @ 0x00303AF0
// match: __ehhandler$??1type_1E5830@@QAE@XZ @ 0x00303AF8

// match: ?sub_1E58C0@type_1E5A60@@SAPAU1@PBD@Z @ 0x001E58C0
type_1E5A60 *type_1E5A60::sub_1E58C0(const RwChar *arg_0)
{
    type_1E5A60 *var_4 = dword_503FD0;
    while (var_4 && !(var_4->unk_10 == arg_0))
        var_4 = var_4->unk_2C;
    return var_4;
}

// match: ?sub_1E5920@type_1E5A60@@QAEPAUtype_1E2250@kujuUI@@XZ @ 0x001E5920
type_1E2250 *type_1E5A60::sub_1E5920()
{
    return unk_34;
}

// match: ?sub_1E5940@type_1E5A60@@QAEPAUtype_1E2250@kujuUI@@G@Z @ 0x001E5940
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
type_1E2250 *type_1E5A60::sub_1E5940(RwUInt16 arg_0)
{
    type_1E2250 *local_C = sub_1E5920();
    RwUInt32 bp_4 = 0;
    RwUInt32 var_8 = unk_38 - 1;
    while (var_8 - bp_4 > 1)
    {
        RwUInt32 var_18 = (var_8 - bp_4) / 2 + bp_4;
        type_1E2250 *lv_10 = &unk_30[var_18];
        RwUInt16 var_14 = lv_10->unk_10;
        if (var_14 == arg_0)
            return lv_10;
        if (var_14 < arg_0)
            bp_4 = var_18;
        else
            var_8 = var_18;
    }
    if (unk_30[bp_4].get_unk_10() == arg_0)
        local_C = &unk_30[bp_4];
    else if (unk_30[var_8].get_unk_10() == arg_0)
        local_C = &unk_30[var_8];
    return local_C;
}

// match: ?sub_1E5A40@type_1E5A60@@QAEHXZ @ 0x001E5A40
RwInt32 type_1E5A60::sub_1E5A40()
{
    return unk_3A;
}

// match: ?sub_1E5A60@type_1E5A60@@QAEPAURwTexture@@H@Z @ 0x001E5A60
RwTexture *type_1E5A60::sub_1E5A60(RwInt32 arg_0)
{
    return (RwTexture *)unk_3C[arg_0]->unk_1C;
}

extern const RwChar *dword_42D0C0;
extern const RwChar *dword_42D0C4;
extern const RwChar *dword_42D0C8;
extern RwUInt32 dword_503FD4;
extern RwUInt32 dword_503FD8;
extern RwUInt32 dword_503FDC;

// match: ?sub_1E5A80@@YA?AU?$type_E8780@Utype_1E5A60@@@@PBD@Z @ 0x001E5A80
// match: __ehhandler$?sub_1E5A80@@YA?AU?$type_E8780@Utype_1E5A60@@@@PBD@Z-0x46 @ 0x00303B10
// match: __ehhandler$?sub_1E5A80@@YA?AU?$type_E8780@Utype_1E5A60@@@@PBD@Z @ 0x00303B56
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
type_E8780<type_1E5A60> sub_1E5A80(const RwChar *arg_0)
{
    cFileIn *lv_10;
    RwChar local_94[0x80];
    RwUInt32 var98;
    type_1E5A60 *var_A0 = 0;
    type_E8780<type_1E5A60> var_9C(type_1E5A60::sub_1E58C0(arg_0));

    if (!var_9C.sub_E87C0())
        return var_9C;
    var98 = strlen(arg_0);
    memcpy(local_94, dword_42D0C0, dword_503FD4);
    memcpy(&local_94[dword_503FD4], arg_0, var98);
    memcpy(&local_94[var98 + dword_503FD4], dword_42D0C8, dword_503FD8 + 1);
    lv_10 = 0;
    sub_1C8CA0(local_94, &lv_10);
    if (lv_10)
    {
        type_1E5A80_header var_C4;
        if (lv_10->sub_1C8BA0(&var_C4, 0x24))
        {
            type_1E61A0<type_1E2250_entry, 0x800> var_A334;
            RwUInt32 var_31C = var_C4.unk_12;
            for (RwUInt32 var_A338 = 0; var_A338 != var_31C; ++var_A338)
                lv_10->sub_1C8BA0(var_A334.next(), 0x14);
            type_1E61A0<type_1E5A80_page, 4> var_108;
            RwUInt32 frm_10C = var_C4.unk_14;
            if (frm_10C > 4)
            {
                if (CODFH_DEBUG_LOGS)
                    sub_1C8A30("Maximum number of textures per font exceded - %d in \"%s\".\n", frm_10C, arg_0);
            }
            for (RwUInt32 var_A33C = 0; var_A33C != frm_10C; ++var_A33C)
                lv_10->sub_1C8BA0(var_108.next(), 0xC);
            RwUInt32 bp_318 = 0;
            RwChar x314[4][0x80];
            for (bp_318 = 0; bp_318 != frm_10C; ++bp_318)
                memcpy(x314[bp_318], dword_42D0C0, dword_503FD4);
            RwUInt32 lv_110 = 0x80 - dword_503FD4;
            RwUInt32 lcl_D4[4];
            for (bp_318 = 0; bp_318 != frm_10C; ++bp_318)
            {
                lv_10->sub_1C8C00(&x314[bp_318][dword_503FD4], lv_110);
                RwUInt32 var_A340 = strlen(x314[bp_318]);
                lcl_D4[bp_318] = var_A340;
            }
            delete lv_10;
            type_1E5830 *local_32C[4];
            for (bp_318 = 0; bp_318 != frm_10C; ++bp_318)
            {
                RwChar *var_A34C = x314[bp_318];
                type_1EEEE0 *lv_A344 = 0;
                RwUInt32 var_A348 = lcl_D4[bp_318];
                if (!lv_A344)
                {
                    RwChar *var_A350 = var_A34C + var_A348;
                    memcpy(var_A350, dword_42D0C4, dword_503FDC);
                    sub_1EEFB0(var_A34C, &lv_A344);
                    if (!lv_A344)
                    {
                        strcpy(var_A350, ".tga");
                        sub_1EEF20(var_A34C, &lv_A344);
                    }
                    if (lv_A344)
                    {
                        *var_A350 = 0;
                        type_1E5830 *var_A354 = new type_1E5830(var_A34C, lv_A344);
                        local_32C[bp_318] = var_A354;
                    }
                }
            }
            if (bp_318 == frm_10C)
                var_A0 = new type_1E5A60(arg_0, &var_C4, var_A334.items(), var_A334.count(), local_32C,
                                         frm_10C);
        }
        else
            delete lv_10;
    }
    return var_A0;
}

// match: ?sub_1E60E0@type_1E5A60@@QAEGXZ @ 0x001E60E0
RwUInt16 type_1E5A60::sub_1E60E0()
{
    return unk_0C + unk_0E;
}

// match: ?sub_1E6100@type_1E5A60@@QAEGXZ @ 0x001E6100
RwUInt16 type_1E5A60::sub_1E6100()
{
    return unk_0C;
}

// match: ?sub_1E6120@type_1E5A60@@QAEGXZ @ 0x001E6120
RwUInt16 type_1E5A60::sub_1E6120()
{
    return unk_0E;
}

// match: ?sub_1E6140@type_1E5A60@@QAEXG@Z @ 0x001E6140
void type_1E5A60::sub_1E6140(RwUInt16 arg_0)
{
    unk_0E = arg_0;
}

// match: ?sub_1E6160@@YAHPBD@Z @ 0x001E6160
RwInt32 sub_1E6160(const RwChar *arg_0)
{
    return strlen(arg_0);
}

// match: ?sub_1E6180@@YAHPBG@Z @ 0x001E6180
RwInt32 sub_1E6180(const wchar_t *arg_0)
{
    return wcslen(arg_0);
}

// match: ??0?$type_1E61A0@Utype_1E2250_entry@kujuUI@@$0IAA@@@QAE@XZ @ 0x001E61A0
// match: ?next@?$type_1E61A0@Utype_1E2250_entry@kujuUI@@$0IAA@@@QAEPAUtype_1E2250_entry@kujuUI@@XZ @ 0x001E61C0
// match: ?count@?$type_1E61A0@Utype_1E2250_entry@kujuUI@@$0IAA@@@QAEIXZ @ 0x001E6200
// match: ?items@?$type_1E61A0@Utype_1E2250_entry@kujuUI@@$0IAA@@@QAEPAUtype_1E2250_entry@kujuUI@@XZ @ 0x001E6220
// match: ??0?$type_1E61A0@Utype_1E5A80_page@@$03@@QAE@XZ @ 0x001E6240
// match: ?next@?$type_1E61A0@Utype_1E5A80_page@@$03@@QAEPAUtype_1E5A80_page@@XZ @ 0x001E6260
// match: ?item_size@?$type_1E61A0@Utype_1E2250_entry@kujuUI@@$0IAA@@@SAIXZ @ 0x001E62A0
// match: ?item_size@?$type_1E61A0@Utype_1E5A80_page@@$03@@SAIXZ @ 0x001E62B0







namespace kujuUI
{
}


// The prefix and suffix lengths, measured when the program starts.
RwUInt32 dword_503FDC = strlen(dword_42D0C4) + 1;
RwUInt32 dword_503FD4 = strlen(dword_42D0C0);
RwUInt32 dword_503FD8 = strlen(dword_42D0C8);

namespace kujuUI
{

}
