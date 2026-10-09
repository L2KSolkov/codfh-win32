// The message boxes (type_4EBE00, game/waitscreen.h): their set-up, their
// lines and choices, and the parser of the message text they are built from.

#include "game/xboxlive.h"
#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "game/functions.h"
#include "game/waitscreen.h"
#include "game/data.h"
#include "game/objectives.h"
#include "game/gameloop.h"
#include <string.h>
#include <stdio.h>
#include "xbox/xapi.h"
#include "rw/baengine.h"
#include "rw/osintf.h"
#include <stdlib.h>
#include "rws/gftime.h"
#include "types/type_DA0A0.h"
#include "types/type_DA580.h"
#include "types/type_DC400.h"
#include "types/soundbank.h"
#include "types/type_10F710.h"
#include "types/PlayerTrigger.h"

// The messages' openers (defined below; the last, sub_1A2580, in
// unit_1A16D0), for their table.
void sub_18B700(type_4EBE00 *arg_0, RwInt32 arg_4);
void sub_18B8C0(type_4EBE00 *arg_0, RwInt32 arg_4);
void sub_18BA40(type_4EBE00 *arg_0, RwInt32 arg_4);
void sub_18BA90(type_4EBE00 *arg_0, RwInt32 arg_4);
void sub_18BBB0(type_4EBE00 *arg_0, RwInt32 arg_4);
void sub_18BCD0(type_4EBE00 *arg_0, RwInt32 arg_4);
void sub_18BD90(type_4EBE00 *arg_0, RwInt32 arg_4);
void sub_18BF10(type_4EBE00 *arg_0, RwInt32 arg_4);
void sub_18BF50(type_4EBE00 *arg_0, RwInt32 arg_4);
void sub_18BFF0(type_4EBE00 *arg_0, RwInt32 arg_4);
void sub_18C090(type_4EBE00 *arg_0, RwInt32 arg_4);
void sub_18C130(type_4EBE00 *arg_0, RwInt32 arg_4);
void sub_18C1D0(type_4EBE00 *arg_0, RwInt32 arg_4);
void sub_18C270(type_4EBE00 *arg_0, RwInt32 arg_4);
void sub_18C310(type_4EBE00 *arg_0, RwInt32 arg_4);
void sub_18C430(type_4EBE00 *arg_0, RwInt32 arg_4);
void sub_18C4D0(type_4EBE00 *arg_0, RwInt32 arg_4);
void sub_18C5F0(type_4EBE00 *arg_0, RwInt32 arg_4);
void sub_18C6A0(type_4EBE00 *arg_0, RwInt32 arg_4);
void sub_18C800(type_4EBE00 *arg_0, RwInt32 arg_4);
void sub_18C920(type_4EBE00 *arg_0, RwInt32 arg_4);
void sub_18C9C0(type_4EBE00 *arg_0, RwInt32 arg_4);
void sub_18CB10(type_4EBE00 *arg_0, RwInt32 arg_4);
void sub_18CB50(type_4EBE00 *arg_0, RwInt32 arg_4);
void sub_18CD20(type_4EBE00 *arg_0, RwInt32 arg_4);
void sub_18CFA0(type_4EBE00 *arg_0, RwInt32 arg_4);
void sub_18D220(type_4EBE00 *arg_0, RwInt32 arg_4);
void sub_18D260(type_4EBE00 *arg_0, RwInt32 arg_4);
void sub_18D2A0(type_4EBE00 *arg_0, RwInt32 arg_4);
void sub_18D3C0(type_4EBE00 *arg_0, RwInt32 arg_4);
void sub_18D520(type_4EBE00 *arg_0, RwInt32 arg_4);
void sub_18D680(type_4EBE00 *arg_0, RwInt32 arg_4);
void sub_18D8A0(type_4EBE00 *arg_0, RwInt32 arg_4);
void sub_18D940(type_4EBE00 *arg_0, RwInt32 arg_4);
void sub_18D9E0(type_4EBE00 *arg_0, RwInt32 arg_4);
void sub_18DA80(type_4EBE00 *arg_0, RwInt32 arg_4);
void sub_18DB70(type_4EBE00 *arg_0, RwInt32 arg_4);
void sub_18DCA0(type_4EBE00 *arg_0, RwInt32 arg_4);
void sub_18DDD0(type_4EBE00 *arg_0, RwInt32 arg_4);
void sub_18DE80(type_4EBE00 *arg_0, RwInt32 arg_4);
void sub_18DF80(type_4EBE00 *arg_0, RwInt32 arg_4);
void sub_18E640(type_4EBE00 *arg_0, RwInt32 arg_4);
void sub_18F020(type_4EBE00 *arg_0, RwInt32 arg_4);
void sub_18F1C0(type_4EBE00 *arg_0, RwInt32 arg_4);
void sub_18F330(type_4EBE00 *arg_0, RwInt32 arg_4);
void sub_1A2580(type_4EBE00 *arg_0, RwInt32 arg_4);

#ifdef CODFH_SP
// SP callback @ 0x00121970 replaces MP callback @ 0x0018D680.
void sp_sub_121970(type_4EBE00 *arg_0, RwInt32 arg_4);
#endif

// Its data definitions (PLAN M5), in the image's address order.
// 0x0042B518
// The messages' openers by number (sub_186E70), ended by -1.
type_42B518 off_42B518[47] = {
    { 5, sub_18D220 },
    { 6, sub_18D260 },
    { 7, sub_18D2A0 },
    { 8, sub_18C1D0 },
    { 9, sub_18D3C0 },
    { 10, sub_18D520 },
    { 11, sub_18CD20 },
    { 12, sub_18CFA0 },
    { 13, sub_18CB50 },
    { 20, sub_18CB10 },
    { 14, sub_18BA40 },
    { 15, sub_18BCD0 },
    { 16, sub_18BD90 },
    { 17, sub_18BF10 },
    { 18, sub_18BF50 },
    { 19, sub_18BFF0 },
    { 21, sub_18C920 },
    { 22, sub_18C9C0 },
    { 26, sub_18C430 },
    { 23, sub_18C800 },
    { 24, sub_18C5F0 },
    { 25, sub_18C6A0 },
    { 27, sub_18C4D0 },
    { 28, sub_18C090 },
    { 29, sub_18C130 },
    { 30, sub_18C270 },
    { 31, sub_18C310 },
    { 32, sub_18B8C0 },
    { 33, sub_18B700 },
    { 34, sub_18BA90 },
    { 35, sub_18BBB0 },
    { 36, sub_18D8A0 },
    { 37, sub_18D940 },
    { 38, sub_18D9E0 },
    { 39, sub_18DA80 },
    { 40, sub_18DB70 },
    { 41, sub_18DCA0 },
    { 42, sub_18DDD0 },
    { 43, sub_18DE80 },
#ifdef CODFH_SP
    { 44, sp_sub_121970 }, // SP 0x00121970; MP 0x0018D680.
#else
    { 44, sub_18D680 },
#endif
    { 0, sub_18DF80 },
    { 1, sub_18E640 },
    { 3, sub_18F020 },
    { 2, sub_18F1C0 },
    { 4, sub_18F330 },
    { 45, sub_1A2580 },
    { -1, 0 },
};
// 0x004F2348
RwInt32 dword_4F2348;
// 0x004F234C
RwInt32 dword_4F234C;
// 0x004F2350
RwInt32 dword_4F2350;
// 0x004F2354
RwInt32 dword_4F2354;
// 0x004F2358
RwInt32 dword_4F2358;
// 0x004F235C
RwInt32 dword_4F235C;
// 0x004F2360
RwInt32 dword_4F2360;
// 0x004F2364
RwInt32 dword_4F2364;
// 0x004F2368
RwInt32 dword_4F2368;
// 0x004F2370
RwChar *dword_4F2370[0x4D];
// 0x004F24A8
type_4F24A8 dword_4F24A8[4];
// 0x004F616C
RwInt32 dword_4F616C;
// End of its data definitions.


// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).
extern type_4F3130 dword_4F3130;   // unit_19BF20 defines it (its initializer, .CRT$XCU entry and implicit destructor are its)
// Vtables (.rdata, PLAN M5): each in its own placement range (config/splits.txt).
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: __real@413e0000 @ 0x003DEFE0
// match: __real@420e8000 @ 0x003DEFE4
// match: __real@41980000 @ 0x003DEFE8
// match: __real@40be0000 @ 0x003DEFEC
// match: __real@3f892492 @ 0x003DEFF0
// match: ??_C@_02LMMGGCAJ@?3?5?$AA@ @ 0x003DEFF4
// match: ??_C@_0JA@IBNIPLHH@ERROR?3?5tag?5?$CC?$CFs?$FL?4?4?4?$FN?$CC?5was?5too?5lon@ @ 0x003DEFF8
// match: ??_C@_0DG@MJFGICNF@Localized?5string?5corresponding?5t@ @ 0x003DF088
// match: ??_C@_0DM@HCJBHOEI@ERROR?3?5No?5localized?5string?5found@ @ 0x003DF0C0
// match: ??_C@_0IP@KGDPNHMN@ERROR?3?5?$CFd?5bytes?5were?5allocated?5f@ @ 0x003DF100
// match: ??_C@_0DO@JOACOMIN@ERROR?3?5Unable?5to?5allocate?5?$CFd?5byt@ @ 0x003DF190
// match: ??_C@_0HK@NBDADLED@ERROR?3?5Message?5strings?5file?5?$CC?$CFs?$CC@ @ 0x003DF1D0
// match: ??_C@_0EM@GNOIKDGO@ERROR?3?5Message?5strings?5file?5?$CC?$CFs?$CC@ @ 0x003DF250
// match: ??_C@_0DN@ONEFAKCN@ERROR?3?5Unable?5to?5allocate?5?$CFd?5byt@ @ 0x003DF29C
// match: ?off_42B518@@3PAUtype_42B518@@A @ 0x0042B518

// match: ??0type_4EBE00@@QAE@XZ @ 0x00188380
// sp-match: ??0type_4EBE00@@QAE@XZ @ 0x0011E380

type_4EBE00::type_4EBE00()
{
    sub_1883B0();
}

// match: ?sub_1883B0@type_4EBE00@@QAEXXZ @ 0x001883B0
// sp-match: ?sub_1883B0@type_4EBE00@@QAEXXZ @ 0x0011D7C0
void type_4EBE00::sub_1883B0()
{
    RwInt32 var_4;

    unk_1C = 100.0f;
    unk_20 = 100.0f;
    unk_24 = 0;
    unk_28 = 0;
    unk_00 = 0;
    unk_2C = 0;
    unk_38 = -1;
    unk_2CDC = -1;
    unk_2CE0 = 1;
    unk_2CE4 = 0;
    unk_2CE8 = 0;
    unk_2CEC = 0;
    unk_2CF0 = 0;
    unk_04.sub_18A430();
    for (var_4 = 0; var_4 < 5; var_4++)
        unk_27DC[var_4][0] = 0;
}

// match: ?sub_188490@type_4EBE00@@QAEXXZ @ 0x00188490
// sp-match: ?sub_188490@type_4EBE00@@QAEXXZ @ 0x0011D830
// Closes it.
void type_4EBE00::sub_188490()
{
    sub_1883B0();
    unk_00 = 0;
}

// match: ?sub_1884B0@type_4EBE00@@QAEXMM@Z @ 0x001884B0
// sp-match: ?sub_1884B0@type_4EBE00@@QAEXMM@Z @ 0x0011E3A0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Its width: the widest heading line or line with its widest choice (a
// choice with a button icon, $, drawn at the small size); its height from
// its lines and heading lines.
void type_4EBE00::sub_1884B0(RwReal arg_0, RwReal arg_4)
{
    RwInt32 var_148;
    RwInt32 lv_144;
    RwReal ebp_140;
    RwReal s13C;
    RwInt32 local_138;
    RwReal loc134;
    RwReal bp_130;
    RwInt32 l12C;
    RwReal var_128;
    RwReal v124;
    RwReal v120;
    RwInt32 frm_11C;
    RwChar local_118[0x100];
    RwInt32 lv_10;
    RwReal var_C;
    RwInt32 bp_8;
    RwInt32 bp_4;

    var_128 = 0;
    v124 = 0;
    lv_10 = 0;
    local_138 = 0;
    l12C = 0;
    for (lv_10 = 0; lv_10 < 5; lv_10++)
    {
        s13C = dword_4EBD2C->sub_DA7B0(unk_27DC[lv_10], 19.0f);
        if (s13C > var_128)
            var_128 = s13C;
    }
    for (lv_10 = 0; lv_10 < unk_2C; lv_10++)
    {
        var_C = dword_4EBD2C->sub_DA7B0(unk_DC[lv_10].unk_00, 19.0f);
        bp_130 = 0;
        for (local_138 = 0; local_138 < unk_DC[lv_10].unk_260; local_138++)
        {
            loc134 = 19.0f * flt_42B478;
            strcpy(local_118, unk_DC[lv_10].unk_100[local_138].unk_00);
            lv_144 = strlen(local_118);
            for (l12C = 0; l12C < 0x100 && local_118[l12C]; l12C++)
            {
                if (local_118[l12C] == '$')
                {
                    local_118[lv_144 - 2] = 0;
                    loc134 = 19.0f;
                    unk_DC[lv_10].unk_26C = 1;
                    break;
                }
            }
            v120 = dword_4EBD2C->sub_DA7B0(local_118, loc134);
            if (v120 > bp_130)
                bp_130 = v120;
        }
        ebp_140 = bp_130 + var_C;
        if (ebp_140 > var_128)
            var_128 = ebp_140;
    }
    v124 = (RwReal)(unk_2C - 1) * 19.0f + 35.625f;
    bp_8 = 0;
    for (lv_10 = 0; lv_10 < 5; lv_10++)
    {
        if (unk_27DC[lv_10][0])
        {
            v124 += 20.0f;
            bp_8++;
        }
    }
    if (!bp_8)
        v124 -= 11.875f;
    v124 += 20.0f;
    unk_1C = var_128 * 1.2f + 20.0f;
    sub_1889C0(arg_0, arg_4);
    unk_20 = v124;
    sub_1889C0(arg_0, arg_4);
    frm_11C = sub_189FB0(-1);
    bp_4 = frm_11C;
    if (frm_11C != -1)
    {
        do
        {
            var_148 = unk_DC[bp_4].unk_264;
            if (var_148 == -1)
                unk_DC[bp_4].unk_264 = 0;
            bp_4 = sub_189FB0(bp_4);
        } while (bp_4 != frm_11C);
    }
    if (unk_38 == -1)
        unk_38 = frm_11C;
}

// match: ?sub_1888F0@type_4EBE00@@QAEXPAURwCamera@@M@Z @ 0x001888F0
// sp-match: ?sub_1888F0@type_4EBE00@@QAEXPAURwCamera@@M@Z @ 0x0011C2F0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_4EBE00::sub_1888F0(RwCamera *arg_0, RwReal arg_4)
{
    RwInt32 var_14;
    RwReal lv_10;
    RwReal var_C;
    RwReal bp_8;
    RwReal bp_4;

    bp_8 = 1.0f / (arg_0->nearPlane);
    lv_10 = RwIm2DGetFarScreenZ();
    bp_4 = RwIm2DGetNearScreenZ();
    var_C = (lv_10 - bp_4) * arg_4 + bp_4;
    for (var_14 = 0; var_14 < 4; var_14++)
    {
        RwIm2DVertexSetScreenZ(&unk_3C[var_14], var_C);
        RwIm2DVertexSetRecipCameraZ(&unk_3C[var_14], bp_8);
    }
}

// match: ?sub_188970@type_4EBE00@@QAEPAUtype_4EBE00_DC@@XZ @ 0x00188970
// sp-match: ?sub_188970@type_4EBE00@@QAEPAUtype_4EBE00_DC@@XZ @ 0x0011E6B0
type_4EBE00_DC *type_4EBE00::sub_188970()
{
    unk_DC[unk_2C].sub_18A110();
    unk_2C = unk_2C + 1;
    return &unk_DC[unk_2C - 1];
}

// match: ?sub_1889C0@type_4EBE00@@QAEXMM@Z @ 0x001889C0
// sp-match: ?sub_1889C0@type_4EBE00@@QAEXMM@Z @ 0x0011C340
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Lays it out: its corners about the boxes' centre (dword_4EBD08, higher
// and shorter, while a level script runs) offset by arg_0 and arg_4 and
// its own offset, from the 512x448 layout to the screen; then the
// heading's backdrop and the frame's pieces, and their colours.
void type_4EBE00::sub_1889C0(RwReal arg_0, RwReal arg_4)
{
    RwInt32 var_28C;
    RwV3d var_288[4];
    RwV2d var_258;
    RwV3d stk_250[4];
    RwV3d l220[4];
    RwV3d local_1F0[4];
    RwReal bp_1C0;
    RwV3d var_1BC[4];
    RwV3d m_18C[4];
    RwV3d l15C[4];
    RwV3d l12C[4];
    RwReal uFC;
    RwV3d lF8[4];
    RwV3d qC8[4];
    RwV3d var98[4];
    RwInt32 q68;
    RwV3d var_64[4];
    RwV3d var_34[4];
    RwReal l4;

    if (!unk_00)
        return;
    var_258 = dword_4EBCF8;
    bp_1C0 = unk_20;
    if (byte_4E564D != -1 && unk_2CDC != 1 && unk_2CF0 != 1)
    {
        var_258 = dword_4EBD08;
        var_258.y -= 10.0f;
        bp_1C0 -= 10.0f;
    }
    var_258.x += arg_0;
    var_258.y += arg_4;
    unk_AC[0].x = var_258.x - unk_1C * 0.5f;
    unk_AC[0].y = bp_1C0 * 0.5f + var_258.y;
    unk_AC[1].x = var_258.x - unk_1C * 0.5f;
    unk_AC[1].y = var_258.y - bp_1C0 * 0.5f;
    unk_AC[2].x = unk_1C * 0.5f + var_258.x;
    unk_AC[2].y = bp_1C0 * 0.5f + var_258.y;
    unk_AC[3].x = unk_1C * 0.5f + var_258.x;
    unk_AC[3].y = var_258.y - bp_1C0 * 0.5f;
    for (q68 = 0; q68 < 4; q68++)
    {
        unk_AC[q68].x += unk_24;
        unk_AC[q68].y += unk_28;
    }
    l4 = 256.0f;
    uFC = 224.0f;
    for (q68 = 0; q68 < 4; q68++)
    {
        unk_AC[q68].x = l4 + unk_AC[q68].x;
        unk_AC[q68].y = uFC + unk_AC[q68].y;
    }
    RwIm2DVertexSetScreenX(&unk_3C[0], scale_screen_x(+unk_AC[0].x));
    RwIm2DVertexSetScreenY(&unk_3C[0], scale_screen_y(+unk_AC[0].y));
    RwIm2DVertexSetScreenX(&unk_3C[1], scale_screen_x(+unk_AC[1].x));
    RwIm2DVertexSetScreenY(&unk_3C[1], scale_screen_y(+unk_AC[1].y));
    RwIm2DVertexSetScreenX(&unk_3C[2], scale_screen_x(+unk_AC[2].x));
    RwIm2DVertexSetScreenY(&unk_3C[2], scale_screen_y(+unk_AC[2].y));
    RwIm2DVertexSetScreenX(&unk_3C[3], scale_screen_x(+unk_AC[3].x));
    RwIm2DVertexSetScreenY(&unk_3C[3], scale_screen_y(+unk_AC[3].y));
    for (q68 = 0; q68 < 4; q68++)
        RwIm2DVertexSetIntRGBA(&unk_3C[q68], dword_4EBD20.red, dword_4EBD20.green, dword_4EBD20.blue, dword_4EBD20.alpha);
    var_28C = 0;
    for (q68 = 0; q68 < 5; q68++)
    {
        if (unk_27DC[q68][0])
            var_28C++;
    }
    var_64[0].x = unk_AC[1].x;
    var_64[0].y = unk_AC[1].y + 17.8125f + (RwReal)var_28C * 11.875f + (RwReal)(var_28C - 1) * 5.9375f;
    var_64[1].x = var_64[0].x;
    var_64[1].y = var_64[0].y + 1.0f;
    var_64[2].x = unk_AC[3].x;
    var_64[2].y = var_64[0].y;
    var_64[3].x = var_64[2].x;
    var_64[3].y = var_64[1].y;
    qC8[0].x = unk_AC[1].x - 1.0f;
    qC8[0].y = unk_AC[1].y;
    qC8[1].x = qC8[0].x;
    qC8[1].y = qC8[0].y - 1.0f;
    qC8[2].x = unk_AC[3].x + 1.0f;
    qC8[2].y = qC8[0].y;
    qC8[3].x = qC8[2].x;
    qC8[3].y = qC8[0].y - 1.0f;
    l15C[0].x = unk_AC[0].x - 1.0f;
    l15C[0].y = unk_AC[0].y;
    l15C[1].x = l15C[0].x;
    l15C[1].y = l15C[0].y + 1.0f;
    l15C[2].x = unk_AC[2].x + 1.0f;
    l15C[2].y = l15C[0].y;
    l15C[3].x = l15C[2].x;
    l15C[3].y = l15C[0].y + 1.0f;
    var_34[0].x = unk_AC[0].x - 1.0f;
    var_34[0].y = unk_AC[0].y;
    var_34[1].x = unk_AC[1].x - 1.0f;
    var_34[1].y = unk_AC[1].y;
    var_34[2].x = unk_AC[0].x;
    var_34[2].y = unk_AC[0].y;
    var_34[3].x = unk_AC[1].x;
    var_34[3].y = unk_AC[1].y;
    lF8[0].x = unk_AC[2].x;
    lF8[0].y = unk_AC[2].y;
    lF8[1].x = unk_AC[3].x;
    lF8[1].y = unk_AC[3].y;
    lF8[2].x = unk_AC[2].x + 1.0f;
    lF8[2].y = unk_AC[2].y;
    lF8[3].x = unk_AC[3].x + 1.0f;
    lF8[3].y = unk_AC[3].y;
    var_288[0].x = unk_AC[1].x - 10.0f;
    var_288[0].y = unk_AC[1].y;
    var_288[1].x = unk_AC[1].x - 10.0f;
    var_288[1].y = unk_AC[1].y - 10.0f;
    var_288[2].x = unk_AC[3].x + 10.0f;
    var_288[2].y = unk_AC[3].y;
    var_288[3].x = unk_AC[3].x + 10.0f;
    var_288[3].y = unk_AC[3].y - 10.0f;
    local_1F0[0].x = unk_AC[0].x - 10.0f;
    local_1F0[0].y = unk_AC[0].y + 10.0f;
    local_1F0[1].x = unk_AC[0].x - 10.0f;
    local_1F0[1].y = unk_AC[0].y;
    local_1F0[2].x = unk_AC[2].x + 10.0f;
    local_1F0[2].y = unk_AC[2].y + 10.0f;
    local_1F0[3].x = unk_AC[2].x + 10.0f;
    local_1F0[3].y = unk_AC[2].y;
    stk_250[0].x = unk_AC[0].x - 10.0f;
    stk_250[0].y = unk_AC[0].y;
    stk_250[1].x = unk_AC[1].x - 10.0f;
    stk_250[1].y = unk_AC[1].y;
    stk_250[2].x = unk_AC[0].x;
    stk_250[2].y = unk_AC[0].y;
    stk_250[3].x = unk_AC[1].x;
    stk_250[3].y = unk_AC[1].y;
    m_18C[0].x = unk_AC[2].x;
    m_18C[0].y = unk_AC[2].y;
    m_18C[1].x = unk_AC[3].x;
    m_18C[1].y = unk_AC[3].y;
    m_18C[2].x = unk_AC[2].x + 10.0f;
    m_18C[2].y = unk_AC[2].y;
    m_18C[3].x = unk_AC[3].x + 10.0f;
    m_18C[3].y = unk_AC[3].y;
    l12C[0].x = unk_AC[1].x - 10.0f - 2.0f;
    l12C[0].y = unk_AC[1].y - 10.0f;
    l12C[1].x = unk_AC[1].x - 10.0f - 2.0f;
    l12C[1].y = unk_AC[1].y - 10.0f - 2.0f;
    l12C[2].x = unk_AC[3].x + 10.0f + 2.0f;
    l12C[2].y = unk_AC[3].y - 10.0f;
    l12C[3].x = unk_AC[3].x + 10.0f + 2.0f;
    l12C[3].y = unk_AC[3].y - 10.0f - 2.0f;
    var98[0].x = unk_AC[0].x - 10.0f - 2.0f;
    var98[0].y = unk_AC[0].y + 10.0f + 2.0f;
    var98[1].x = unk_AC[0].x - 10.0f - 2.0f;
    var98[1].y = unk_AC[0].y + 10.0f;
    var98[2].x = unk_AC[2].x + 10.0f + 2.0f;
    var98[2].y = unk_AC[2].y + 10.0f + 2.0f;
    var98[3].x = unk_AC[2].x + 10.0f + 2.0f;
    var98[3].y = unk_AC[2].y + 10.0f;
    var_1BC[0].x = unk_AC[0].x - 10.0f - 2.0f;
    var_1BC[0].y = unk_AC[0].y + 10.0f + 2.0f;
    var_1BC[1].x = unk_AC[1].x - 10.0f - 2.0f;
    var_1BC[1].y = unk_AC[1].y - 10.0f - 2.0f;
    var_1BC[2].x = unk_AC[0].x - 10.0f;
    var_1BC[2].y = unk_AC[0].y + 10.0f + 2.0f;
    var_1BC[3].x = unk_AC[1].x - 10.0f;
    var_1BC[3].y = unk_AC[1].y - 10.0f - 2.0f;
    l220[0].x = unk_AC[2].x + 10.0f;
    l220[0].y = unk_AC[2].y + 10.0f + 2.0f;
    l220[1].x = unk_AC[3].x + 10.0f;
    l220[1].y = unk_AC[3].y - 10.0f - 2.0f;
    l220[2].x = unk_AC[2].x + 10.0f + 2.0f;
    l220[2].y = unk_AC[2].y + 10.0f + 2.0f;
    l220[3].x = unk_AC[3].x + 10.0f + 2.0f;
    l220[3].y = unk_AC[3].y - 10.0f - 2.0f;
    for (q68 = 0; q68 < 4; q68++)
    {
        RwIm2DVertexSetScreenX(&unk_2CF4[q68], scale_screen_x(+var_64[q68].x));
        RwIm2DVertexSetScreenY(&unk_2CF4[q68], scale_screen_y(+var_64[q68].y));
        RwIm2DVertexSetScreenX(&unk_2D64[q68], scale_screen_x(+qC8[q68].x));
        RwIm2DVertexSetScreenY(&unk_2D64[q68], scale_screen_y(+qC8[q68].y));
        RwIm2DVertexSetScreenX(&unk_2DD4[q68], scale_screen_x(+l15C[q68].x));
        RwIm2DVertexSetScreenY(&unk_2DD4[q68], scale_screen_y(+l15C[q68].y));
        RwIm2DVertexSetScreenX(&unk_2E44[q68], scale_screen_x(+var_34[q68].x));
        RwIm2DVertexSetScreenY(&unk_2E44[q68], scale_screen_y(+var_34[q68].y));
        RwIm2DVertexSetScreenX(&unk_2EB4[q68], scale_screen_x(+lF8[q68].x));
        RwIm2DVertexSetScreenY(&unk_2EB4[q68], scale_screen_y(+lF8[q68].y));
        RwIm2DVertexSetScreenX(&unk_2F24[q68], scale_screen_x(+var_288[q68].x));
        RwIm2DVertexSetScreenY(&unk_2F24[q68], scale_screen_y(+var_288[q68].y));
        RwIm2DVertexSetScreenX(&unk_2F94[q68], scale_screen_x(+local_1F0[q68].x));
        RwIm2DVertexSetScreenY(&unk_2F94[q68], scale_screen_y(+local_1F0[q68].y));
        RwIm2DVertexSetScreenX(&unk_3004[q68], scale_screen_x(+stk_250[q68].x));
        RwIm2DVertexSetScreenY(&unk_3004[q68], scale_screen_y(+stk_250[q68].y));
        RwIm2DVertexSetScreenX(&unk_3074[q68], scale_screen_x(+m_18C[q68].x));
        RwIm2DVertexSetScreenY(&unk_3074[q68], scale_screen_y(+m_18C[q68].y));
        RwIm2DVertexSetScreenX(&unk_30E4[q68], scale_screen_x(+l12C[q68].x));
        RwIm2DVertexSetScreenY(&unk_30E4[q68], scale_screen_y(+l12C[q68].y));
        RwIm2DVertexSetScreenX(&unk_3154[q68], scale_screen_x(+var98[q68].x));
        RwIm2DVertexSetScreenY(&unk_3154[q68], scale_screen_y(+var98[q68].y));
        RwIm2DVertexSetScreenX(&unk_31C4[q68], scale_screen_x(+var_1BC[q68].x));
        RwIm2DVertexSetScreenY(&unk_31C4[q68], scale_screen_y(+var_1BC[q68].y));
        RwIm2DVertexSetScreenX(&unk_3234[q68], scale_screen_x(+l220[q68].x));
        RwIm2DVertexSetScreenY(&unk_3234[q68], scale_screen_y(+l220[q68].y));
    }
    for (q68 = 0; q68 < 4; q68++)
    {
        RwIm2DVertexSetIntRGBA(&unk_2CF4[q68], dword_4EBD24.red, dword_4EBD24.green, dword_4EBD24.blue, dword_4EBD24.alpha);
        RwIm2DVertexSetIntRGBA(&unk_2D64[q68], dword_4EBD24.red, dword_4EBD24.green, dword_4EBD24.blue, dword_4EBD24.alpha);
        RwIm2DVertexSetIntRGBA(&unk_2DD4[q68], dword_4EBD24.red, dword_4EBD24.green, dword_4EBD24.blue, dword_4EBD24.alpha);
        RwIm2DVertexSetIntRGBA(&unk_2E44[q68], dword_4EBD24.red, dword_4EBD24.green, dword_4EBD24.blue, dword_4EBD24.alpha);
        RwIm2DVertexSetIntRGBA(&unk_2EB4[q68], dword_4EBD24.red, dword_4EBD24.green, dword_4EBD24.blue, dword_4EBD24.alpha);
        RwIm2DVertexSetIntRGBA(&unk_2F24[q68], dword_4EBDE8.red, dword_4EBDE8.green, dword_4EBDE8.blue, dword_4EBDE8.alpha);
        RwIm2DVertexSetIntRGBA(&unk_2F94[q68], dword_4EBDE8.red, dword_4EBDE8.green, dword_4EBDE8.blue, dword_4EBDE8.alpha);
        RwIm2DVertexSetIntRGBA(&unk_3004[q68], dword_4EBDE8.red, dword_4EBDE8.green, dword_4EBDE8.blue, dword_4EBDE8.alpha);
        RwIm2DVertexSetIntRGBA(&unk_3074[q68], dword_4EBDE8.red, dword_4EBDE8.green, dword_4EBDE8.blue, dword_4EBDE8.alpha);
        RwIm2DVertexSetIntRGBA(&unk_30E4[q68], dword_4EBD24.red, dword_4EBD24.green, dword_4EBD24.blue, dword_4EBD24.alpha);
        RwIm2DVertexSetIntRGBA(&unk_3154[q68], dword_4EBD24.red, dword_4EBD24.green, dword_4EBD24.blue, dword_4EBD24.alpha);
        RwIm2DVertexSetIntRGBA(&unk_31C4[q68], dword_4EBD24.red, dword_4EBD24.green, dword_4EBD24.blue, dword_4EBD24.alpha);
        RwIm2DVertexSetIntRGBA(&unk_3234[q68], dword_4EBD24.red, dword_4EBD24.green, dword_4EBD24.blue, dword_4EBD24.alpha);
    }
}

// match: ?sub_189FB0@type_4EBE00@@QAEHH@Z @ 0x00189FB0
// sp-match: ?sub_189FB0@type_4EBE00@@QAEHH@Z @ 0x0011D840
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The first selectable line below arg_0 (wrapping), or -1.
RwInt32 type_4EBE00::sub_189FB0(RwInt32 arg_0)
{
    RwInt32 var_8;
    RwInt32 l4;

    if ((arg_0 != -1 && arg_0 < 0) || arg_0 + 1 >= unk_2C)
        arg_0 = -1;
    l4 = arg_0 == -1 ? 0 : arg_0 + 1;
    for (var_8 = 0; var_8 < unk_2C; var_8++)
    {
        if (unk_DC[l4].sub_18A380())
            return l4;
        l4 += 1 % unk_2C;
    }
    return -1;
}

// match: ?sub_18A060@type_4EBE00@@QAEHH@Z @ 0x0018A060
// sp-match: ?sub_18A060@type_4EBE00@@QAEHH@Z @ 0x0011D8B0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The first selectable line above arg_0 (wrapping), or -1.
RwInt32 type_4EBE00::sub_18A060(RwInt32 arg_0)
{
    RwInt32 var_8;
    RwInt32 l4;

    if ((arg_0 != -1 && arg_0 - 1 < 0) || arg_0 >= unk_2C)
        arg_0 = -1;
    l4 = arg_0 == -1 ? unk_2C - 1 : arg_0 - 1;
    for (var_8 = 0; var_8 < unk_2C; var_8++)
    {
        if (unk_DC[l4].sub_18A380())
            return l4;
        if ((l4 = l4 - 1) < 0)
            l4 = unk_2C - 1;
    }
    return -1;
}

// match: ?sub_18A110@type_4EBE00_DC@@QAEXXZ @ 0x0018A110
// sp-match: ?sub_18A110@type_4EBE00_DC@@QAEXXZ @ 0x0011D930
void type_4EBE00_DC::sub_18A110()
{
    RwInt32 var_4;

    var_4 = 0;
    unk_00[0] = 0;
    for (var_4 = 0; var_4 < 8; var_4++)
        unk_100[var_4].sub_18A3E0();
    unk_260 = 0;
    unk_264 = -1;
    unk_268 = 1;
    unk_26C = 0;
}

// match: ?sub_18A190@type_4EBE00_DC@@QAEPAUtype_4EBE00_100@@PBD@Z @ 0x0018A190
// sp-match: ?sub_18A190@type_4EBE00_DC@@QAEPAUtype_4EBE00_100@@PBD@Z @ 0x0011D050
type_4EBE00_100 *type_4EBE00_DC::sub_18A190(const RwChar *arg_0)
{
    strcpy(unk_100[unk_260].unk_00, arg_0);
    unk_260 = unk_260 + 1;
    return &unk_100[unk_260 - 1];
}

// match: ?sub_18A1F0@type_4EBE00_DC@@QAEXHPAURwV2d@@PAUtype_4EBE00@@@Z @ 0x0018A1F0
// sp-match: ?sub_18A1F0@type_4EBE00_DC@@QAEXHPAURwV2d@@PAUtype_4EBE00@@@Z @ 0x0011D090
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Draws the line at *arg_4 in the style arg_0: its text, ": " and its
// choice selected; centred in the box arg_8 when it is (without its last
// four characters when a gap goes before it).
void type_4EBE00_DC::sub_18A1F0(RwInt32 arg_0, RwV2d *arg_4, type_4EBE00 *arg_8)
{
    RwReal var_198;
    RwReal ebp_194;
    RwChar lv_190[0x100];
    RwChar var_90[0x80];
    RwV2d bp_8;

    var_90[0] = 0;
    if (unk_00[0])
    {
        strcpy(var_90, unk_00);
        if (unk_260)
            strcat(var_90, ": ");
    }
    if (unk_264 != -1)
        strcat(var_90, unk_100[unk_264].unk_00);
    bp_8 = *arg_4;
    if (unk_268)
    {
        var_198 = 1.0f;
        if (arg_0 == 1)
            var_198 = flt_42B478;
        strcpy(lv_190, var_90);
        if (unk_26C)
            lv_190[strlen(var_90) - 4] = 0;
        ebp_194 = dword_4EBD2C->sub_DA7B0(lv_190, 19.0f) * var_198 * 0.5f;
        bp_8.x = (arg_8->unk_AC[1].x + arg_8->unk_AC[3].x) / 2.0f - ebp_194;
    }
    sub_1879F0(arg_0, &bp_8, var_90, 0);
}

// match: ?sub_18A380@type_4EBE00_DC@@QAEHXZ @ 0x0018A380
// sp-match: ?sub_18A380@type_4EBE00_DC@@QAEHXZ @ 0x0011D230
RwInt32 type_4EBE00_DC::sub_18A380()
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < unk_260; var_4++)
    {
        if (unk_100[var_4].unk_24 || unk_100[var_4].unk_1C)
            return 1;
    }
    return 0;
}

// match: ?sub_18A3E0@type_4EBE00_100@@QAEXXZ @ 0x0018A3E0
// sp-match: ?sub_18A3E0@type_4EBE00_100@@QAEXXZ @ 0x0011D270
void type_4EBE00_100::sub_18A3E0()
{
    unk_00[0] = 0;
    unk_1C = 0;
    unk_24 = 0;
}

// match: ??0type_4EBE00_04@@QAE@XZ @ 0x0018A410
// sp-match: ??0type_4EBE00_04@@QAE@XZ @ 0x0011D980
type_4EBE00_04::type_4EBE00_04()
{
    sub_18A430();
}

// match: ?sub_18A430@type_4EBE00_04@@QAEXXZ @ 0x0018A430
// sp-match: ?sub_18A430@type_4EBE00_04@@QAEXXZ @ 0x0011D280
void type_4EBE00_04::sub_18A430()
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 5; var_4++)
        unk_00[var_4] = 0;
}

// match: ?sub_18A470@@YAPAUtype_18A470@@PBDPAU1@@Z @ 0x0018A470
// sp-match: ?sub_18A470@@YAPAUtype_18A470@@PBDPAU1@@Z @ 0x0011E6E0
// The entry of the table arg_4 named arg_0, or 0.
type_18A470 *sub_18A470(const RwChar *arg_0, type_18A470 *arg_4)
{
    for (; arg_4->unk_00; arg_4++)
    {
        if (!strcmp(arg_0, arg_4->unk_00))
            return arg_4;
    }
    return 0;
}

// match: ?sub_18A4B0@@YAPADPAD0@Z @ 0x0018A4B0
// sp-match: ?sub_18A4B0@@YAPADPAD0@Z @ 0x0011E740
// The start of the line after arg_0 (before arg_4), skipping escaped
// characters and newlines inside quotes; 0 at the end.
RwChar *sub_18A4B0(RwChar *arg_0, RwChar *arg_4)
{
    bool var_1;

    var_1 = false;
    for (; arg_0 < arg_4; arg_0++)
    {
        if (*arg_0 == '\\')
            arg_0++;
        else
        {
            if (!var_1 && *arg_0 == '\n' && arg_0 < arg_4 - 1)
                return arg_0 + 1;
            if (*arg_0 == '"')
                var_1 = !var_1;
        }
    }
    return 0;
}

// match: ?sub_18A530@@YAPADPAUtype_18A530@@@Z @ 0x0018A530
// sp-match: ?sub_18A530@@YAPADPAUtype_18A530@@@Z @ 0x0011E790
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The end of the cursor's field (a comma or a newline).
RwChar *sub_18A530(type_18A530 *arg_0)
{
    RwChar *var_8;
    RwChar *l4;

    l4 = arg_0->unk_00;
    var_8 = arg_0->unk_04;
    for (; l4 < var_8 && *l4 != ',' && *l4 != '\n'; l4++)
        ;
    return l4;
}

// match: ?sub_18A580@@YAPADPAUtype_18A530@@@Z @ 0x0018A580
// sp-match: ?sub_18A580@@YAPADPAUtype_18A530@@@Z @ 0x0011E7C0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Copies the cursor's field into its buffer (at most 31 characters, with a
// warning when longer); where it ends (a newline ends it early).
RwChar *sub_18A580(type_18A530 *arg_0)
{
    RwChar *var_14;
    bool lD;
    RwInt32 var_C;
    RwChar *bp_8;
    RwChar *bp_4;

    bp_4 = arg_0->unk_00;
    var_14 = arg_0->unk_04;
    bp_8 = arg_0->unk_08;
    lD = false;
    var_C = 0;
    for (; bp_4 < var_14 && *bp_4 != ','; bp_4++)
    {
        if (*bp_4 == '\n')
            return bp_4;
        if (var_C < 0x1F)
        {
            bp_8[var_C] = *bp_4;
            var_C++;
        }
        else
            lD = true;
    }
    bp_8[var_C] = 0;
    if (lD)
        printf("ERROR: tag \"%s[...]\" was too long and thus truncated, which might cause it to be assigned "
               "incorrectly or a match for it cannot be found at all\n",
               bp_8);
    return bp_4;
}

// match: ?sub_18A630@@YAPADPAX@Z @ 0x0018A630
// sp-match: ?sub_18A630@@YAPADPAX@Z @ 0x0011E820
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Measures the cursor's quoted field (its token a count): the characters
// counted, a quote pair dropped and an escaped quote kept; where it ends.
RwChar *sub_18A630(void *arg_0)
{
    bool var_11;
    RwInt32 *lv_10;
    type_18A530 *var_C;
    RwChar *bp_8;
    RwChar *bp_4;

    var_C = (type_18A530 *)arg_0;
    bp_4 = var_C->unk_00;
    bp_8 = var_C->unk_04;
    lv_10 = (RwInt32 *)var_C->unk_08;
    var_11 = false;
    while (bp_4 < bp_8)
    {
        if (*bp_4 == '\\' && bp_4 + 1 < bp_8 && bp_4[1] == '"')
        {
            bp_4++;
            bp_4++;
            (*lv_10)++;
        }
        else
        {
            if (!var_11 && *bp_4 == ',')
            {
                bp_4++;
                break;
            }
            if (!var_11 && *bp_4 == '\n')
                break;
            if (*bp_4 == '"')
                var_11 = !var_11;
            else
                (*lv_10)++;
        }
        bp_4++;
    }
    (*lv_10)++;
    return bp_4;
}

// match: ?sub_18A730@@YAPADPAX@Z @ 0x0018A730
// sp-match: ?sub_18A730@@YAPADPAX@Z @ 0x0011E890
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Copies the cursor's quoted field to its output (a quote pair dropped, an
// escaped quote kept, then a terminator), and points the tag's string at
// it; where it ends.
RwChar *sub_18A730(void *arg_0)
{
    bool var_1D;
    type_18A730 *t1C;
    RwChar *var_18;
    type_18A470 *var_14;
    type_18A470 *lv_10;
    RwChar *var_C;
    RwChar *bp_8;
    RwChar *bp_4;

    t1C = (type_18A730 *)arg_0;
    bp_4 = t1C->unk_00;
    var_18 = t1C->unk_04;
    var_C = t1C->unk_08;
    bp_8 = t1C->unk_0C;
    lv_10 = t1C->unk_10;
    var_1D = false;
    while (bp_4 < var_18)
    {
        if (*bp_4 == '\\' && bp_4 + 1 < var_18 && bp_4[1] == '"')
        {
            bp_4++;
            bp_4++;
            *var_C = *bp_4;
            var_C++;
        }
        else
        {
            if (!var_1D && *bp_4 == ',')
            {
                bp_4++;
                break;
            }
            if (!var_1D && *bp_4 == '\n')
                break;
            if (*bp_4 == '"')
                var_1D = !var_1D;
            else
            {
                *var_C = *bp_4;
                var_C++;
            }
        }
        bp_4++;
    }
    *var_C = 0;
    var_C++;
    var_14 = sub_18A470(bp_8, lv_10);
    if (var_14)
        *var_14->unk_04 = t1C->unk_08;
    else
        printf("Localized string corresponding to tag \"%s\" is unused\n", bp_8);
    t1C->unk_08 = var_C;
    return bp_4;
}

// match: ?sub_18A890@@YAPADPBDPAUtype_18A470@@PAD@Z @ 0x0018A890
// sp-match: ?sub_18A890@@YAPADPBDPAUtype_18A470@@PAD@Z @ 0x0011E940
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Loads the message strings file arg_0 (a CSV of tags and a column per
// language) into the name table arg_4's strings: a first pass sizes them,
// a second copies them (into arg_8 when given, else allocated); the
// strings, or 0 on an error.
RwChar *sub_18A890(const RwChar *arg_0, type_18A470 *arg_4, RwChar *arg_8)
{
    RwChar *(*l4)(type_18A530 *);
    RwChar *(*locC)(type_18A530 *);
    RwUInt32 v2B4;
    RwInt32 var_2B0;
    RwUInt32 local_2AC;
    RwChar *slot_2A8;
    RwFileFunctions *slot_2A4;
    size_t lv_2A0;
    type_18A530 *l29C;
    type_18A530 var_298;
    RwUInt32 stk_28C;
    type_18A890 loc288[2];
    RwChar s268[0x200];
    RwInt32 local_64;
    void *lv_60;
    type_18A530 *l5C;
    type_18A530 m_58;
    RwChar *var_4C;
    type_18A730 frm_48;
    RwChar *l34;
    RwChar var30[0x20];
    RwChar *frm_8;

    memset(s268, 0, 0x200);
    sub_D7F20(s268, arg_0);
    slot_2A4 = RwOsGetFileInterface();
    if (!slot_2A4 || !slot_2A4->rwfopen)
    {
        printf("Failed to get OS file interface.\n");
        return 0;
    }
    lv_60 = slot_2A4->rwfopen(s268, "r");
    if (!lv_60)
    {
        printf("Failed to open text map for reading. Bailing out!\n");
        return 0;
    }
    stk_28C = sub_16D200(lv_60);
    if (!arg_8)
        l34 = (RwChar *)calloc(stk_28C, 1);
    else
        l34 = arg_8;
    if (!l34)
    {
        printf("ERROR: Unable to allocate %d bytes for message strings file\n", stk_28C);
        free(l34);
        return 0;
    }
    lv_2A0 = slot_2A4->rwfread(l34, 1, stk_28C, lv_60);
    var_2B0 = sub_19B0A0();
    local_64 = 0;
    switch (var_2B0)
    {
    case 0:
        local_64 = 0;
        break;
    case 1:
        local_64 = 1;
        break;
    case 2:
        local_64 = 2;
        break;
    case 5:
        local_64 = 3;
        break;
    case 6:
        local_64 = 4;
        break;
    default:
        local_64 = 0;
        break;
    }
    frm_8 = 0;
    slot_2A8 = l34 + stk_28C;
    local_2AC = 0;
    var_4C = 0;
    locC = 0;
    l5C = 0;
    l4 = 0;
    l29C = 0;
    m_58.unk_00 = 0;
    m_58.unk_04 = 0;
    m_58.unk_08 = var30;
    var_298.unk_00 = 0;
    var_298.unk_00 = 0;
    var_298.unk_08 = (RwChar *)&local_2AC;
    frm_48.unk_00 = 0;
    frm_48.unk_04 = 0;
    frm_48.unk_08 = 0;
    frm_48.unk_0C = var30;
    frm_48.unk_10 = arg_4;
    loc288[0].unk_00 = sub_18A530;
    loc288[0].unk_04 = &m_58;
    loc288[0].unk_08 = (RwChar *(*)(type_18A530 *))sub_18A630;
    loc288[0].unk_0C = &var_298;
    loc288[1].unk_00 = sub_18A580;
    loc288[1].unk_04 = &m_58;
    loc288[1].unk_08 = (RwChar *(*)(type_18A530 *))sub_18A730;
    loc288[1].unk_0C = &frm_48;
    for (v2B4 = 0; v2B4 < 2; v2B4++)
    {
        locC = loc288[v2B4].unk_00;
        l5C = loc288[v2B4].unk_04;
        l4 = loc288[v2B4].unk_08;
        l29C = loc288[v2B4].unk_0C;
        frm_8 = l34;
        while ((frm_8 = sub_18A4B0(frm_8, slot_2A8)) != 0)
        {
            RwInt32 local_2B8;
            bool var_2BA;
            bool var_2B9;

            l5C->unk_00 = frm_8;
            l5C->unk_04 = slot_2A8;
            frm_8 = locC(l5C);
            if (*frm_8 == '\n')
                continue;
            frm_8++;
            if (frm_8 >= slot_2A8)
            {
                printf("ERROR: Message strings file \"%s\" has at least one row with too few columns?", arg_0);
                if (!arg_8)
                    free(l34);
                slot_2A4->rwfclose(lv_60);
                if (v2B4 && !arg_8)
                    free(var_4C);
                return 0;
            }
            local_2B8 = 0;
            var_2BA = false;
            var_2B9 = false;
            while (local_2B8 < local_64 && frm_8 < slot_2A8)
            {
                if (*frm_8 == '\\' && frm_8 + 1 < slot_2A8 && frm_8[1] == '"')
                {
                    frm_8++;
                    frm_8++;
                }
                else if (!var_2BA && *frm_8 == ',')
                    local_2B8++;
                else
                {
                    if (!var_2BA && *frm_8 == '\n')
                    {
                        var_2B9 = true;
                        break;
                    }
                    if (*frm_8 == '"')
                        var_2BA = !var_2BA;
                }
                frm_8++;
            }
            if (var_2B9)
                continue;
            if (frm_8 >= slot_2A8)
            {
                printf("ERROR: Message strings file \"%s\" incorrectly delimited -- check for missing quotes or invalid use of escape character (\\)", arg_0);
                if (!arg_8)
                    free(l34);
                slot_2A4->rwfclose(lv_60);
                if (v2B4 && !arg_8)
                    free(var_4C);
                return 0;
            }
            l29C->unk_00 = frm_8;
            l29C->unk_04 = slot_2A8;
            frm_8 = l4(l29C);
            if (*frm_8 == '\n')
                continue;
        }
        if (!v2B4)
        {
            if (!arg_8)
                var_4C = (RwChar *)calloc(local_2AC, 1);
            else
                var_4C = slot_2A8;
            if (!var_4C)
            {
                printf("ERROR: Unable to allocate %d bytes localized message strings\n", local_2AC);
                if (!arg_8)
                    free(l34);
                slot_2A4->rwfclose(lv_60);
                return 0;
            }
            frm_48.unk_08 = var_4C;
        }
    }
    if (frm_48.unk_08 - var_4C != local_2AC)
    {
        printf("ERROR: %d bytes were allocated for localized strings and %d bytes were used, for some reason the parser didn't read the CSV file correctly...\n", local_2AC, frm_48.unk_08 - var_4C);
        if (!arg_8)
        {
            free(l34);
            free(var_4C);
        }
        slot_2A4->rwfclose(lv_60);
        return 0;
    }
    for (; arg_4->unk_00; arg_4++)
    {
        if (!*arg_4->unk_04)
        {
            *arg_4->unk_04 = byte_42B4FC;
            printf("ERROR: No localized string found in file \"%s\" for tag \"%s\"\n", arg_0, arg_4->unk_00);
        }
    }
    slot_2A4->rwfclose(lv_60);
    if (!arg_8)
        free(l34);
    return var_4C;
}













































































