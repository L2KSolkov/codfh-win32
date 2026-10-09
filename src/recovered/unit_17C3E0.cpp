// The help messages (game/helpmessages.h).

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "rw/rt2d.h"
#include "rw/badevice.h"
#include "game/functions.h"
#include "game/gameloop.h"
#include "game/data.h"
#include "game/textmanager.h"
#include "game/helpmessages.h"
#include "types/type_3DF8D8.h"
#include "types/type_DA580.h"
#include "types/type_DC400.h"
#include "types/type_DA0A0.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x004E6F28
type_4E6F38 *dword_4E6F28;
// 0x004E6F2C
RwInt32 dword_4E6F2C;
// 0x004E6F30
type_DA580 *dword_4E6F30;
// 0x004E6F34
RwInt32 dword_4E6F34;
// End of its data definitions.


// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).
type_4E6F38 dword_4E6F38[32];
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: .CRT$XCU+0 @ 0x00427164

// match: _$E2 @ 0x0030BEF0
// match: ?sub_17C3E0@type_4E6F38@@QAEXXZ @ 0x0017C3E0
// sp-match: ?sub_17C3E0@type_4E6F38@@QAEXXZ @ 0x00115440

void type_4E6F38::sub_17C3E0()
{
    unk_00.unk_04 = 0;
    unk_00.unk_00 = 0;
    unk_08 = 0;
    unk_0C = 1.0f;
    unk_10 = 0;
    unk_14 = 0;
}

// match: ?sub_17C430@@YAXXZ @ 0x0017C430
// sp-match: ?sub_17C430@@YAXXZ @ 0x00115460
// Clears the list.
void sub_17C430()
{
    RwInt32 var_4;

    dword_4E6F34 = 0;
    dword_4E6F28 = 0;
    dword_4E6F2C = 0;
    dword_4E6F30 = 0;
    for (var_4 = 0; var_4 < 0x20; var_4++)
        dword_4E6F38[var_4].sub_17C3E0();
    dword_4E6F34 = 1;
}

// match: ?sub_17C4A0@@YAXXZ @ 0x0017C4A0
// sp-match: ?sub_17C4A0@@YAXXZ @ 0x001154A0
// Takes the HUD's font.
void sub_17C4A0()
{
    dword_4E6F30 = dword_4B9190->unk_1A028;
}

// match: ?sub_17C4C0@@YAXXZ @ 0x0017C4C0
// sp-match: ?sub_17C4C0@@YAXXZ @ 0x001154C0
// Sets the list up again (when it has been set up).
void sub_17C4C0()
{
    if (!dword_4E6F34)
        return;
    sub_17C430();
    sub_17C4A0();
}

// match: ?sub_17C4E0@@YAXXZ @ 0x0017C4E0
// sp-match: ?sub_17C4E0@@YAXXZ @ 0x001154E0
// Shuts it down.
void sub_17C4E0()
{
    sub_17C430();
    dword_4E6F34 = 0;
}

// match: ?sub_17C500@@YAHPAUtype_3DF8D8_04@@HH@Z @ 0x0017C500
// sp-match: ?sub_17C500@@YAHPAUtype_3DF8D8_04@@HH@Z @ 0x001154F0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Shows the message under the key arg_0 in a free slot (arg_4 its killed
// flag), first (arg_8) or last; 0 without a key or a free slot.
RwInt32 sub_17C500(type_3DF8D8_04 *arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    type_4E6F38 *var_14;
    type_4E6F38 *lv_10;
    RwInt32 var_C;
    RwInt32 bp_8;
    RwInt32 bp_4;

    bp_4 = -1;
    bp_8 = 0;
    if (!arg_0->unk_00 || !arg_0->unk_04)
        return 0;
    for (var_C = 0; var_C < 0x20 && !bp_8; var_C++)
    {
        if (!dword_4E6F38[var_C].unk_00.unk_00 && !dword_4E6F38[var_C].unk_00.unk_04)
        {
            bp_4 = var_C;
            bp_8 = 1;
        }
    }
    if (bp_4 != -1)
    {
        dword_4E6F2C++;
        lv_10 = &dword_4E6F38[bp_4];
        lv_10->sub_17C3E0();
        lv_10->unk_00.unk_00 = arg_0->unk_00;
        lv_10->unk_00.unk_04 = arg_0->unk_04;
        lv_10->unk_10 = arg_4;
        if (!dword_4E6F28)
        {
            dword_4E6F28 = lv_10;
        }
        else if (arg_8)
        {
            lv_10->unk_14 = dword_4E6F28;
            dword_4E6F28 = lv_10;
        }
        else
        {
            var_14 = dword_4E6F28;
            while (var_14->unk_14)
                var_14 = var_14->unk_14;
            var_14->unk_14 = lv_10;
        }
    }
    else
    {
        return 0;
    }
    return 1;
}

// match: ?sub_17C630@@YAPAUtype_3DF8D8_04@@XZ @ 0x0017C630
// sp-match: ?sub_17C630@@YAPAUtype_3DF8D8_04@@XZ @ 0x001155F0
// The message shown (its key), or 0.
type_3DF8D8_04 *sub_17C630()
{
    return (type_3DF8D8_04 *)dword_4E6F28;
}

// match: ?sub_17C640@@YAXPAUtype_3DF8D8_04@@@Z @ 0x0017C640
// sp-match: ?sub_17C640@@YAXPAUtype_3DF8D8_04@@@Z @ 0x00115600
// Kills the message under the key arg_0: it fades out.
void sub_17C640(type_3DF8D8_04 *arg_0)
{
    type_4E6F38 *var_4;

    var_4 = dword_4E6F28;
    if (!var_4)
        return;
    while (var_4)
    {
        if (var_4->unk_00.unk_00 == arg_0->unk_00 && var_4->unk_00.unk_04 == arg_0->unk_04)
        {
            var_4->unk_08 = dword_4B8F84;
            var_4->unk_10 = 1;
            dword_4E6F2C--;
            var_4 = 0;
        }
        else
        {
            var_4 = var_4->unk_14;
        }
    }
}

// match: ?sub_17C6C0@@YAXH@Z @ 0x0017C6C0
// sp-match: ?sub_17C6C0@@YAXH@Z @ 0x00115650
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Clears the messages: with arg_0 the one shown fades out, the rest go.
void sub_17C6C0(RwInt32 arg_0)
{
    type_4E6F38 *var_8;
    type_4E6F38 *l4;

    l4 = dword_4E6F28;
    var_8 = 0;
    if (!l4)
        return;
    dword_4E6F2C = 0;
    if (arg_0)
    {
        l4->unk_08 = dword_4B8F84;
        l4->unk_10 = 1;
        l4 = l4->unk_14;
        dword_4E6F2C = 1;
    }
    else
    {
        dword_4E6F28 = 0;
    }
    while (l4)
    {
        var_8 = l4->unk_14;
        l4->sub_17C3E0();
        l4 = var_8;
    }
}

// match: ?sub_17C750@@YAXM@Z @ 0x0017C750
// sp-match: ?sub_17C750@@YAXM@Z @ 0x001156B0
// Fades the message shown out by the time arg_0 once it is killed; gone
// when it is clear.
void sub_17C750(RwReal arg_0)
{
    if (dword_4E6F34 && dword_4E6F28 && dword_4E6F28->unk_10)
    {
        dword_4E6F28->unk_08 = arg_0 + dword_4E6F28->unk_08;
        if (dword_4E6F28->unk_08 > dword_4B8F84)
            dword_4E6F28->unk_0C = 1.0f - (dword_4E6F28->unk_08 - dword_4B8F84) / dword_4B8F80;
        else
            dword_4E6F28->unk_0C = 1.0f;
        if (dword_4E6F28->unk_0C < 0.0f)
        {
            dword_4E6F28->unk_00.unk_04 = 0;
            dword_4E6F28->unk_00.unk_00 = 0;
            dword_4E6F2C--;
            dword_4E6F28 = dword_4E6F28->unk_14;
        }
    }
}

#ifdef CODFH_SP
// Single player only (SP 0x12A3B0, outside this unit): expands the text
// arg_0's $...$ markers into arg_4; 0 when there is nothing to draw.
RwInt32 sp_sub_12A3B0(const RwChar *arg_0, RwChar *arg_4);
#endif

// match: ?sub_17C830@@YAXPAURwCamera@@@Z @ 0x0017C830
// sp-match: ?sub_17C830@@YAXPAURwCamera@@@Z @ 0x00115760
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Draws the message shown into the camera arg_0: its text, centred in its
// box, in its colour at its opacity.
void sub_17C830(RwCamera *arg_0)
{
    RwInt32 var_38;
    Rt2dBBox var_34;
    RwInt32 frm_24;
    RwInt32 var_20;
    RwV2d l1C;
    RwRGBA ebp_14;
    RwReal lv_10;
    const RwChar *var_C;
    type_3DF8D8 *bp_8;
    type_4E6F38 *bp_4;
#ifdef CODFH_SP
    RwChar buf[0x400];
#endif

    if (dword_4E6F34)
    {
        if (!dword_4E6F30)
            return;
        bp_4 = (type_4E6F38 *)sub_17C630();
        if (bp_4)
        {
            bp_8 = sub_198800(&bp_4->unk_00);
            if (bp_8)
            {
                var_C = bp_8->sub_197550(0, 0);
                if (var_C)
                {
                    RwCameraBeginUpdate(arg_0);
                    RwRenderStateGet(rwRENDERSTATEZWRITEENABLE, &var_38);
                    RwRenderStateGet(rwRENDERSTATEZTESTENABLE, &frm_24);
                    RwRenderStateGet(rwRENDERSTATEFOGENABLE, &var_20);
                    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void *)0);
                    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void *)0);
                    RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void *)0);
                    Rt2dCTMPush();
                    Rt2dCTMSetIdentity();
                    Rt2dCTMScale(1.0f / (RwReal)(RwUInt32)Height * dword_4B8970, 1.0f / (RwReal)(RwUInt32)Height);
                    lv_10 = dword_4E6F30->sub_DA7B0(var_C, 0);
                    l1C = dword_4B8F68;
                    l1C.x = l1C.x - lv_10 / 2.0f;
#ifdef CODFH_SP // shape: the opacity computed before the colour's copy
                    {
                        RwReal a = bp_4->unk_0C * 255.0f;
                        ebp_14 = dword_4B8F64;
                        ebp_14.alpha = (RwUInt8)a;
                    }
#else
                    ebp_14 = dword_4B8F64;
                    ebp_14.alpha = (RwUInt8)(bp_4->unk_0C * 255.0f);
#endif
                    var_34.h = (RwReal)(RwUInt32)Height * dword_4B8F70.y;
                    var_34.w = (RwReal)(RwUInt32)Width * dword_4B8F70.x;
                    var_34.x = (RwReal)(RwUInt32)Width * dword_4B8F68.x;
                    var_34.y = (RwReal)(RwUInt32)Height * dword_4B8F68.y;
                    var_34.x = var_34.x / dword_4B8970;
#ifdef CODFH_SP
                    // Single player draws the expanded text, at 1.7 times
                    // the font's scale (SP 0x1158EE).
                    if (sp_sub_12A3B0(var_C, buf))
                    {
                        flt_4292C8 = 1.7f;
                        dword_4E6F30->sub_DAC60(buf, &var_34, 0, 1, &ebp_14, 0);
                        flt_4292C8 = 1.0f;
                    }
#else
                    dword_4E6F30->sub_DAC60(var_C, &var_34, 0, 1, &ebp_14, 0);
#endif
                    Rt2dCTMPop();
                    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void *)var_38);
                    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void *)frm_24);
                    RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void *)var_20);
                    RwCameraEndUpdate(arg_0);
                }
            }
        }
    }
}
