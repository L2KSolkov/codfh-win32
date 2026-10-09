/*
 * Single player's front-end screens' base (type_sp_AD970, SP 0xAD970-0xAE5CF; include/sp/sp_fend.h):
 * the maestro screens' loading, stepping and drawing, the front end's font and the cheats'
 * and sounds' .data. Not in the multiplayer image: single player only, never compiled for
 * multiplayer.
 *
 * Evidence: a file of its own in default.xbe: its unreferenced 16.666666f (SP 0x2E414C) heads
 * its .rdata between the language screen's strings (sp_fendlang.cpp) and the base's vtable
 * (SP 0x2E4150); the main menu (sp_fend.cpp) has its own one after the cheats' strings
 * (SP 0x2E43B0).
 */
#include <string.h>
#include <stdio.h>

#include "rw/ostypes.h"
#include "rw/baengine.h"
#include "rw/bastream.h"
#include "rw/babintex.h"
#include "rw/batextur.h"
#include "rw/badevice.h"
#include "rw/rt2d.h"
#ifdef CODFH_WIN32
#include "port_mouse.h"
#endif
#include "game/data.h"
#include "game/gameloop.h"
#include "game/xboxlive.h"
#include "game/lightscales.h"
#include "game/frontend.h"
#include "game/platform.h"
#include "types/type_DA580.h"
#include "types/type_8A980.h"
#include "types/type_3DF8D8.h"
#include "game/movie.h"
#include "game/savestate.h"
#include "game/waitscreen.h"
#include "game/levels.h"
#include "game/profiles.h"
#include "game/functions.h"
#include "types/type_4B8EF0.h"
#include "xbox/xapi.h"
#include "sp/sp_fend.h"

#if defined(CODFH_WIN32)
extern "C" void plog(const RwChar *fmt, ...);
extern "C" volatile RwUInt32 port_frame;
#endif

extern "C" RwMatrix *Rt2dObjectGetLTM(Rt2dObject *object);

// Its data definitions (PLAN SP5), in the image's address order (its .data is defined
// further down, where the image's order puts it).
// SP 0x002E414C
extern const RwReal sp_flt_2E414C = 16.666666f; // unreferenced, just before its vtable
// End of its data definitions.

// single player's own front-end .bss (sp_fend.cpp)
extern RwInt32 sp_dword_3B4718;
extern type_DA580 *sp_dword_3B481C;
extern bool sp_byte_3B4822;
extern RwReal sp_flt_3B4828[0x28];
extern type_4F45F8 sp_unk_3B48C8;
extern RwInt32 sp_dword_3B54C8;
extern type_44C4E8 *sp_dword_3EC3E4;

// The front end loop's (unit_0DA290).
extern bool sp_byte_3B4820;
extern bool sp_byte_3B4821;
extern bool sp_byte_3B4720;             // the menu is busy (a page is being shown)
extern RwInt32 sp_dword_3B4744;
extern RwTexDictionary *sp_dword_3B475C;
// The language screen's scroll and select sounds (unit_0DC400's .data, SP 0x3216A4, 0x3216AC).
extern type_3DF8D8_04 unk_4B8B48;
extern type_3DF8D8_04 unk_4B8B40;

void sub_19B0C0(RwInt32 arg_0);
void sub_D7F20(RwChar *arg_0, const RwChar *arg_4);
RwTexDictionary *sub_E8320(const RwChar *arg_0);
void sp_sub_129B50();
void sp_sub_1291D0(RwInt32 arg_0);
void sp_sub_129AC0(RwInt32 arg_0);
RwChar *sp_sub_121960();
void sp_sub_A4F60();
RwInt32 sp_sub_A55F0(RwCamera *arg_0, RwInt32 arg_4, type_D9CF0 *arg_8, RwInt32 arg_C);
void sp_sub_A5E60();
void sp_sub_A5EA0(RwTexDictionary *arg_0);
void sp_sub_A5EC0(RwCamera *arg_0);
void sp_sub_A5F50();
void sp_sub_A5F80();
void sp_sub_A5F90();
void sp_sub_A5FB0();
void sp_sub_A6000();
void sp_sub_A6050(RwReal arg_0);
void sp_sub_A6100();
void sp_sub_B1A10();
type_186020 sp_sub_11B890(RwCamera *arg_0, void (*arg_4)(RwCamera *, void *), void *arg_8);
type_186020 sp_sub_11B900(RwCamera *arg_0, type_D9CF0 *arg_4, RwInt32 arg_8,
                          void (*arg_C)(RwCamera *, void *), void *arg_10);
type_186020 sp_sub_11B930(RwCamera *arg_0, type_D9CF0 *arg_4, void (*arg_8)(RwCamera *, void *),
                          void *arg_C);
type_186020 sp_sub_11B9A0(RwCamera *arg_0, type_D9CF0 *arg_4, RwInt32 arg_8,
                          void (*arg_C)(RwCamera *, void *), void *arg_10);
type_186020 sp_sub_11BAE0(RwCamera *arg_0, type_D9CF0 *arg_4, RwInt32 arg_8,
                          void (*arg_C)(RwCamera *, void *), void *arg_10);

// The screens' base.

// sp-match: ??0type_sp_AD970@@QAE@XZ @ 0x000AD970
type_sp_AD970::type_sp_AD970()
{
}

// sp-match: ??1type_sp_AD970@@QAE@XZ @ 0x000AD980
type_sp_AD970::~type_sp_AD970()
{
}

// shape: Keep the camera and invalid-id defaults together, and copy the path/id
// words as an aggregate. The scoped references preserve the original store order.
// sp-match: ?sp_sub_AD990@type_sp_AD970@@QAE_NPAURwCamera@@@Z @ 0x000AD990
bool type_sp_AD970::sp_sub_AD990(RwCamera *arg_0)
{
#ifdef CODFH_WIN32
    port_menu_mouse_reset();
#endif
    RwChar path[0x80];
    RwUInt64 defaults = ((RwUInt64)(RwUInt32)arg_0 << 32) | 0xFFFFFFFFui64;
    sp_path_encoding context;
    RwUInt32 words[2] = {(RwUInt32)path, (RwUInt32)defaults};
    memcpy(&context, words, 8);

    unk_06 = true;
    { bool &r = unk_10; r = false; }
    { RwCamera *&out = unk_178; out = (RwCamera *)(RwUInt32)(defaults >> 32); }
    { Rt2dMaestro *&r = unk_17C; r = 0; }
    unk_08 = (RwInt32)(RwUInt32)defaults;
    unk_0C = (RwInt32)(RwUInt32)defaults;
    sp_dword_3B4718 = 0;
    unk_14C = (RwInt32)context.words.high;
    unk_150 = (RwInt32)context.words.high;
    unk_154 = (RwInt32)context.words.high;
    unk_158 = (RwInt32)context.words.high;
    unk_15C = (RwInt32)context.words.high;
    unk_160 = (RwInt32)context.words.high;
    unk_164 = (RwInt32)context.words.high;
    unk_168 = (RwInt32)context.words.high;
    { RwInt32 &r = unk_16C; r = (RwInt32)context.words.high; }
    unk_170 = 0;
    { RwInt32 &r = unk_174; r = 0; }
    unk_04 = false;
    unk_05 = false;
    sub_D7F20((RwChar *)context.words.low, "SHELL\\FONTS\\");
    Rt2dFontSetPath(path);
    unk_188 = 0;
    memset(unk_18C, 0, sizeof(unk_18C));
    return unk_06;
}

// sp-match: ?sp_sub_ADA70@type_sp_AD970@@QAEXXZ @ 0x000ADA70
void type_sp_AD970::sp_sub_ADA70()
{
#ifdef CODFH_WIN32
    port_menu_mouse_hide();
#endif
    unk_06 = false;
    if (unk_180)
    {
        RwTexDictionaryDestroy(unk_180);
        unk_180 = 0;
    }
    if (unk_184 && !unk_10)
    {
        RwTexDictionaryDestroy(unk_184);
        unk_184 = 0;
    }
    if (unk_17C)
    {
        sp_profileMouseMaestroDestroyed(unk_17C);
        Rt2dMaestroDestroy(unk_17C);
        unk_17C = 0;
    }
    unk_178 = 0;
}

// sp-match: ?sp_sub_ADAE0@type_sp_AD970@@QAE_NPBHI_N@Z @ 0x000ADAE0
bool type_sp_AD970::sp_sub_ADAE0(const RwInt32 *arg_0, RwUInt32 arg_4, bool arg_8)
{
    RwInt32 i;

    if (unk_188 < arg_4)
    {
        return false;
    }
    for (i = arg_4 - 1; i >= 0; i--)
    {
        if (unk_18C[unk_188 - arg_4 + i] != arg_0[i])
        {
            return false;
        }
    }
    if (arg_8 && unk_4B9308.sub_EE9A0(1, 0x21) == 0.0f)
    {
        return false;
    }
    return true;
}

// sp-match: ?sp_sub_ADB50@type_sp_AD970@@QAEXPAURwCamera@@@Z @ 0x000ADB50
void type_sp_AD970::sp_sub_ADB50(RwCamera *arg_0)
{
    RwInt32 zwrite;
    RwInt32 ztest;
    RwInt32 shade;
    RwInt32 filter;
    RwInt32 alpha;
    RwInt32 cull;
    RwInt32 src;
    RwInt32 dest;

    if (!arg_0)
    {
        arg_0 = (RwCamera *)dword_4E5CBC;
    }
    if (unk_17C && arg_0)
    {
        Rt2dFontTexDictionarySet(unk_184);
        RwTexDictionarySetCurrent(unk_180);
        RwCameraBeginUpdate(arg_0);
        RwRenderStateGet(rwRENDERSTATEZWRITEENABLE, &zwrite);
        RwRenderStateGet(rwRENDERSTATEZTESTENABLE, &ztest);
        RwRenderStateGet(rwRENDERSTATESHADEMODE, &shade);
        RwRenderStateGet(rwRENDERSTATETEXTUREFILTER, &filter);
        RwRenderStateGet(rwRENDERSTATEVERTEXALPHAENABLE, &alpha);
        RwRenderStateGet(rwRENDERSTATECULLMODE, &cull);
        RwRenderStateGet(rwRENDERSTATESRCBLEND, &src);
        RwRenderStateGet(rwRENDERSTATEDESTBLEND, &dest);
        RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void *)0);
        RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void *)0);
        RwRenderStateSet(rwRENDERSTATESHADEMODE, (void *)2);
        RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, (void *)2);
        RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)1);
        RwRenderStateSet(rwRENDERSTATECULLMODE, (void *)1);
        RwRenderStateSet(rwRENDERSTATESRCBLEND, (void *)5);
        RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void *)6);
        RwRenderStateSet(rwRENDERSTATECULLMODE, (void *)1);
        Rt2dCTMPush();
        Rt2dMaestroRender(unk_17C);
        Rt2dCTMPop();
        RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void *)zwrite);
        RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void *)ztest);
        RwRenderStateSet(rwRENDERSTATESHADEMODE, (void *)shade);
        RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, (void *)filter);
        RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)alpha);
        RwRenderStateSet(rwRENDERSTATECULLMODE, (void *)cull);
        RwRenderStateSet(rwRENDERSTATESRCBLEND, (void *)src);
        RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void *)dest);
        RwCameraEndUpdate(arg_0);
    }
}

// sp-match: ?sp_sub_ADD00@@YAPAURt2dObject@@PAU1@0PAX@Z @ 0x000ADD00
// Collects the string objects under arg_0 into the list arg_8 (a type_sp_ADD00).
Rt2dObject *sp_sub_ADD00(Rt2dObject *arg_0, Rt2dObject *arg_4, void *arg_8)
{
    type_sp_ADD00 *l;

    switch (arg_0->type)
    {
    case 1:
        return Rt2dSceneForAllChildren(arg_0, sp_sub_ADD00, arg_8);
    case 4:
        l = (type_sp_ADD00 *)arg_8;
        if (l->unk_00 < l->unk_04)
        {
            l->unk_08[l->unk_00] = arg_0;
            l->unk_00++;
        }
        break;
    }
    return arg_0;
}

// sp-match: ?sp_sub_ADD40@@YAPAURt2dMessage@@PAURt2dMaestro@@PAU1@@Z @ 0x000ADD40
// The maestros' message handler: a GETURL message goes to the screen's handler.
Rt2dMessage *sp_sub_ADD40(Rt2dMaestro *arg_0, Rt2dMessage *arg_4)
{
    type_sp_AD970 *screen;
    RwInt32 p;

    screen = (type_sp_AD970 *)sp_sub_170B80(arg_0);
    if (arg_4->messageType == 1 && (p = arg_4->intParam1) != 0x8B && p != 0x8A)
    {
        if (!sp_byte_3B4822)
        {
            if (p >= 4 && p <= 9)
            {
                sp_byte_3B4822 = true;
                sp_byte_3B4820 = true;
            }
        }
        else if (p < 4 || p > 9)
        {
            sp_byte_3B4822 = false;
            sp_byte_3B4821 = true;
        }
    }
    else if (arg_4->messageType == 5 && sp_byte_3B4822 && arg_4->intParam1 == 0x21
             && arg_4->intParam2 == 0xC2AC2A)
    {
        sp_byte_3B4822 = false;
        sp_byte_3B4821 = true;
    }
    if (arg_4->messageType != 7)
    {
        return Rt2dMessageHandlerDefaultCallBack(arg_0, arg_4);
    }
    screen->vf_000(arg_4->intParam1);
    return arg_4;
}

// sp-match: ?sp_sub_ADDF0@@YAPAURt2dMaestro@@PAU1@PAURt2dAnim@@PAURt2dAnimProps@@PAX@Z @ 0x000ADDF0
// Sends the button-by-label message arg_C (its label and transition) to the maestro.
Rt2dMaestro *sp_sub_ADDF0(Rt2dMaestro *arg_0, Rt2dAnim *arg_4, Rt2dAnimProps *arg_8, void *arg_C)
{
    Rt2dMessage m;

    m.messageType = 0xD;
    m.index = -1;
    m.intParam1 = ((RwInt32 *)arg_C)[0];
    m.intParam2 = ((RwInt32 *)arg_C)[1];
    Rt2dMaestroPostMessages(arg_0, &m, 1);
    return arg_0;
}

// sp-match: ?sp_sub_ADE30@type_sp_AD970@@QAEXPBDPAHH@Z @ 0x000ADE30
void type_sp_AD970::sp_sub_ADE30(const RwChar *arg_0, RwInt32 *arg_4, RwInt32 arg_8)
{
    if (unk_17C && arg_0 && arg_4)
    {
        Rt2dMaestroFindStringLabel(unk_17C, arg_8, arg_0, arg_4);
    }
}

// sp-match: ?sp_sub_ADE60@type_sp_AD970@@QAEXXZ @ 0x000ADE60
void type_sp_AD970::sp_sub_ADE60()
{
    sp_sub_ADE30("btnUp", &unk_14C, 3);
    sp_sub_ADE30("btnDown", &unk_150, 3);
    sp_sub_ADE30("btnLeft", &unk_154, 3);
    sp_sub_ADE30("btnRight", &unk_158, 3);
    sp_sub_ADE30("btnCancel", &unk_160, 3);
    sp_sub_ADE30("btnAction", &unk_15C, 3);
    sp_sub_ADE30("btnSquare", &unk_164, 3);
    sp_sub_ADE30("btnStart", &unk_168, 3);
    sp_sub_ADE30("btnSelect", &unk_16C, 3);
}

// sp-match: ?sp_sub_ADF20@type_sp_AD970@@QAE?AUtype_sp_ADF20@@PBD@Z @ 0x000ADF20
type_sp_ADF20 type_sp_AD970::sp_sub_ADF20(const RwChar *arg_0)
{
    type_sp_ADF20 r;
    RwInt32 index;
    Rt2dStringLabel *label;

    label = Rt2dMaestroFindStringLabel(unk_17C, 1, arg_0, &index);
    r.unk_00 = Rt2dMaestroGetAnimationsByIndex(unk_17C, (RwInt32)label->internalData);
    r.unk_04 = Rt2dMaestroGetAnimPropsByIndex(unk_17C, (RwInt32)label->internalData);
    r.unk_08 = label;
    return r;
}

// sp-match: ?sp_sub_ADF80@@YAPAURt2dFont@@PAU1@PBDMPAURwV2d@@PAURt2dBrush@@@Z @ 0x000ADF80
// Shows a maestro's text with the front end's font, in the brush's bottom colour; notes
// (sp_dword_3B4718) a "Single Player" text in any language.
Rt2dFont *sp_sub_ADF80(Rt2dFont *arg_0, const RwChar *arg_4, RwReal arg_8, RwV2d *arg_C,
                       Rt2dBrush *arg_10)
{
    RwInt32 len;
    RwRGBA c;

#if defined(CODFH_WIN32)
    static RwInt32 trace = -1;
    static RwInt32 trace_count;
    if (trace < 0)
    {
        RwChar enabled[2];
        trace = GetEnvironmentVariableA("CODFH_FONTTRACE", enabled, sizeof(enabled)) ? 1 : 0;
    }
    if (trace && port_frame >= 1500 && trace_count++ < 32)
    {
        plog("frontend text[%d] font=%p text='%s' height=%g pos=%g,%g brush=%p colour=%u,%u,%u,%u", trace_count,
             arg_0, arg_4, arg_8, arg_C->x, arg_C->y, arg_10, (RwUInt8)arg_10->bottom.col.red,
             (RwUInt8)arg_10->bottom.col.green, (RwUInt8)arg_10->bottom.col.blue, (RwUInt8)arg_10->bottom.col.alpha);
    }
#endif

    if (!strcmp(arg_4, "    Single Player"))
    {
        sp_dword_3B4718 = 1;
    }
    len = strlen(arg_4);
    if (len >= 4 && arg_4[len - 1] == 'o' && arg_4[len - 2] == 'l' && arg_4[len - 3] == 'o'
        && arg_4[len - 4] == 'S')
    {
        sp_dword_3B4718 = 1;
    }
    if (len >= 5 && arg_4[len - 2] == 'r' && arg_4[len - 3] == 'o' && arg_4[len - 4] == 'd'
        && arg_4[len - 5] == 'a')
    {
        sp_dword_3B4718 = 1;
    }
    if (len >= 4 && arg_4[len - 1] == 'o' && arg_4[len - 2] == 'l' && arg_4[len - 3] == 'o'
        && arg_4[len - 4] == 'g')
    {
        sp_dword_3B4718 = 1;
    }
    if (len >= 4 && arg_4[len - 1] == 'r' && arg_4[len - 2] == 'e' && arg_4[len - 3] == 'l'
        && arg_4[len - 4] == 'e')
    {
        sp_dword_3B4718 = 1;
    }
    c.red = (RwUInt8)arg_10->bottom.col.red;
    c.green = (RwUInt8)arg_10->bottom.col.green;
    c.blue = (RwUInt8)arg_10->bottom.col.blue;
    c.alpha = (RwUInt8)arg_10->bottom.col.alpha;
    sp_dword_3B481C->sub_DAB00(arg_4, arg_C, &c, arg_8, arg_0);
    return arg_0;
}

// Its .data (PLAN SP5), in the image's address order (SP 0x3216B8-0x3218F7; the art gallery's
// sequence, sp_sub_B0300's seq, follows at 0x3218F8, then vf_000's sp_dword_321914). Single player's
// image names: the weapons' names after the cheats' codes (their literals are this object's,
// SP 0x2E41D8-0x2E43AC), the two images' paths and the front end's sound keys; the release
// image's path, the six numbers, the weapons' table and the keys at 0x3218A0 and 0x3218A8
// have no reader in default.xbe.
// SP 0x003216B8
const RwChar *sp_off_3216B8[49] = {
    "#pw",
    "#ac",
    "#sf",
    "#ek",
    "#ht",
    "#md",
    "#al",
    "#hp",
    "#pr",
    0,
    "Bazooka",
    "Panzershreck",
    "BAR",
    "Bren",
    "DP",
    "M1919A6",
    "MG42",
    "MP40",
    "PPSH",
    "Sten",
    "Thompson",
    "Luger",
    "Enfield",
    "G43",
    "Mosin Nagant",
    "M1 Garand",
    "Kar98",
    "Nagant Sniper",
    "Springfield",
    "M8 Smoke",
    "Mark2 Frag",
    "RTD33",
    "Stielhandgrenate",
    "Browning 50cal",
    "M1919A4",
    "Maxim",
    "MG42 Mounted",
    "Flak38",
    "Flak88",
    "T34 Cannon",
    "T34 Coax",
    "ST74",
    "Mosin Ammo Clip",
    "Teller Mine",
    "KaiserBear Grenade",
    "Sherman Cannon",
    "Sherman Coax",
    "Grease Gun",
    "StickyBear Grenade",
};
// SP 0x0032177C
RwChar sp_byte_32177C[] = "d:\\game_xboxrelease.xbe";
// SP 0x00321794
RwChar sp_byte_321794[] = "d:\\game_xboxmultiplayer.xbe";
// SP 0x003217B0
RwInt32 sp_dword_3217B0[6] = { 0xD1, 0xCA, 0xCF, 0xCB, 0xD2, 0xD3 };
// SP 0x003217C8
type_3DF8D8_04 sp_unk_3217C8(0x11DA5571, 0x86F083EC);
// SP 0x003217D0
type_3DF8D8_04 sp_unk_3217D0(0x58A39CCC, 0xEB617950);
// SP 0x003217D8
type_3DF8D8_04 sp_unk_3217D8(0x7394BCC7, 0xD1705AEC);
// SP 0x003217E0
type_3DF8D8_04 sp_unk_3217E0(0x51108DB0, 0x073FCD0F);
// SP 0x003217E8
type_3DF8D8_04 sp_unk_3217E8(0xE0B41C35, 0x970BDA55);
// SP 0x003217F0
type_3DF8D8_04 sp_unk_3217F0(0x1AAE67CD, 0xC3D60776);
// SP 0x003217F8
type_3DF8D8_04 sp_unk_3217F8(0x5C7C6BAA, 0x72D4C8EE);
// SP 0x00321800
type_3DF8D8_04 sp_unk_321800(0x866DA32E, 0xC9A83201);
// SP 0x00321808
type_3DF8D8_04 sp_unk_321808(0x682668AC, 0x9DA699E8);
// SP 0x00321810
type_3DF8D8_04 sp_unk_321810(0x50F4562F, 0xC10C2DEF);
// SP 0x00321818
type_3DF8D8_04 sp_unk_321818(0xF412F872, 0xCBD2558D);
// SP 0x00321820
type_3DF8D8_04 sp_unk_321820(0xF40D804C, 0x19A42725);
// SP 0x00321828
type_3DF8D8_04 sp_unk_321828(0x0D9E1DB5, 0x82E7A523);
// SP 0x00321830
type_3DF8D8_04 sp_unk_321830(0xCC760BEC, 0x45B8D1DF);
// SP 0x00321838
type_3DF8D8_04 sp_unk_321838(0x1A4D474D, 0x1BABA346);
// SP 0x00321840
type_3DF8D8_04 sp_unk_321840(0x44490BA5, 0x82F5E719);
// SP 0x00321848
type_3DF8D8_04 sp_unk_321848(0xEF4244B1, 0xB66BF300);
// SP 0x00321850
type_3DF8D8_04 sp_unk_321850(0xDC5127A0, 0xCCAA4E99);
// SP 0x00321858
type_3DF8D8_04 sp_unk_321858(0x25428CEB, 0x9CE4D199);
// SP 0x00321860
type_3DF8D8_04 sp_unk_321860(0x3B33A4EB, 0x81C214DA);
// SP 0x00321868
type_3DF8D8_04 sp_unk_321868(0x836B8267, 0x7259B691);
// SP 0x00321870
type_3DF8D8_04 sp_unk_321870(0xE5F13A5F, 0x69EEE9B9);
// SP 0x00321878
type_3DF8D8_04 sp_unk_321878(0x0EECFDF8, 0x53FDD189);
// SP 0x00321880
type_3DF8D8_04 sp_unk_321880(0xC098A23B, 0xE618BE75);
// SP 0x00321888
type_3DF8D8_04 sp_unk_321888(0x67DCEEDD, 0xC93BC875);
// SP 0x00321890
type_3DF8D8_04 sp_unk_321890(0x84CE123E, 0x0337A60D);
// SP 0x00321898
type_3DF8D8_04 sp_unk_321898(0x677A3165, 0x8A1D61B9);
// SP 0x003218A0
type_3DF8D8_04 sp_unk_3218A0(0x6BD20740, 0xF3C02757);
// SP 0x003218A8
type_3DF8D8_04 sp_unk_3218A8(0xCD0349A6, 0x092ED5BB);
// SP 0x003218B0
type_3DF8D8_04 sp_unk_3218B0(0xBB80C522, 0x15292B39);
// SP 0x003218B8
type_3DF8D8_04 sp_unk_3218B8(0x0AB75B75, 0xFF381309);
// SP 0x003218C0
type_3DF8D8_04 sp_unk_3218C0(0x202702AC, 0x75C466F5);
// SP 0x003218C8
type_3DF8D8_04 sp_unk_3218C8(0xE6C904DB, 0x26D117FC);
// SP 0x003218D0
type_3DF8D8_04 sp_unk_3218D0(0xFCBA1CFB, 0x021184D7);
// SP 0x003218D8
type_3DF8D8_04 sp_unk_3218D8(0x7A0D76C2, 0x3EE69E29);
// SP 0x003218E0
type_3DF8D8_04 sp_unk_3218E0(0x13FDCB26, 0x6413F7CA);
// SP 0x003218E8
type_3DF8D8_04 sp_unk_3218E8(0x1C2C7CC4, 0xF42759C1);
// SP 0x003218F0
type_3DF8D8_04 sp_unk_3218F0(0x53294F15, 0x7D11BB6F);
// End of its .data.

// sp-match: ?sp_sub_AE0B0@@YAXXZ @ 0x000AE0B0
// Makes the front end's font.
void sp_sub_AE0B0()
{
    if (!sp_dword_3B481C)
    {
        sp_dword_3B481C = type_DA580::sub_DA680(0);
    }
}

// sp-match: ?sp_sub_AE0D0@type_sp_AD970@@QAEXM@Z @ 0x000AE0D0
void type_sp_AD970::sp_sub_AE0D0(RwReal arg_0)
{
    RwInt32 i;
    RwReal v;
    RwInt32 data[2];

    sp_dword_3B4718 = 0;
    if (!dword_4F30B8)
    {
        *(RwInt32 *)&dword_4F30A8.unk_0C = 1;
    }
    if (!dword_4B88AC && !unk_05)
    {
        for (i = 0; i < 0x28; i++)
        {
            v = unk_4B9308.sub_EE9A0(0, i);
            if (v > 0.2f && sp_flt_3B4828[i] == 0.0f)
            {
                data[1] = 0x40;
                switch (i)
                {
                case 0x21:
                    data[0] = unk_14C;
                    break;
                case 0x22:
                    data[0] = unk_150;
                    break;
                case 0x1F:
                    data[0] = unk_154;
                    break;
                case 0x20:
                    data[0] = unk_158;
                    break;
                case 0x17:
                    data[0] = unk_15C;
                    break;
                case 0x18:
                    data[0] = unk_160;
                    break;
                case 0x0B:
                    sp_sub_129B50();
                    data[0] = unk_168;
                    break;
                case 0x11:
                    data[0] = unk_16C;
                    break;
                case 0x19:
                    data[0] = unk_164;
                    break;
                default:
                    continue;
                }
                if (dword_4F3130.sp_sub_12AAD0())
                {
                    data[0] = 0;
                }
                Rt2dMaestroForAllVisibleAnimations(unk_17C, sp_sub_ADDF0, data);
                if (unk_188 == 20)
                {
                    RwInt32 j;
                    for (j = 0; j < 19; j++)
                    {
                        unk_18C[j] = unk_18C[j + 1];
                    }
                    unk_18C[19] = i;
                }
                else
                {
                    unk_18C[unk_188] = i;
                    unk_188++;
                }
            }
            sp_flt_3B4828[i] = v;
        }
#ifdef CODFH_WIN32
        /* Feed the pointer into RenderWare's native pick-region button state machine. */
        RwInt32 mouseX, mouseY, mouseButton;
        RwInt32 mouse = port_menu_mouse_poll(&mouseX, &mouseY, &mouseButton);
        Rt2dMessage mouseMessages[2];
        RwInt32 mouseMessageCount = 0;
        if (mouse & PORT_MENU_MOUSE_MOVE)
        {
            mouseMessages[mouseMessageCount].messageType = 10; /* MOUSEMOVETO */
            mouseMessages[mouseMessageCount].index = -1;
            mouseMessages[mouseMessageCount].intParam1 = mouseX;
            mouseMessages[mouseMessageCount].intParam2 = mouseY;
            mouseMessageCount++;
        }
        if (mouse & PORT_MENU_MOUSE_BUTTON)
        {
            mouseMessages[mouseMessageCount].messageType = 11; /* MOUSEBUTTONSTATE */
            mouseMessages[mouseMessageCount].index = -1;
            mouseMessages[mouseMessageCount].intParam1 = mouseButton;
            mouseMessages[mouseMessageCount].intParam2 = 0;
            mouseMessageCount++;
        }
        if (mouseMessageCount)
            Rt2dMaestroPostMessages(unk_17C, mouseMessages, mouseMessageCount);
        /* The title's Press Start prompt has no pick region in its animation. Preserve its
           controller Start transition as a mouse fallback on screens that expose btnStart. */
        if ((mouse & PORT_MENU_MOUSE_BUTTON) && mouseButton && (RwUInt32)unk_168 != 0xFFFFFFFFu)
        {
            data[0] = dword_4F3130.sp_sub_12AAD0() ? 0 : unk_168;
            data[1] = 0x40;
            Rt2dMaestroForAllVisibleAnimations(unk_17C, sp_sub_ADDF0, data);
        }
#endif
    }
    Rt2dFontTexDictionarySet(unk_184);
    RwTexDictionarySetCurrent(unk_180);
    Rt2dMaestroAddDeltaTime(unk_17C, arg_0 * (1.0f / 60.0f));
    Rt2dMaestroProcessMessages(unk_17C);
    Rt2dMaestroUpdateAnimations(unk_17C);
}

// sp-match: ?sp_sub_AE3C0@type_sp_AD970@@QAE_NPBD00@Z @ 0x000AE3C0
bool type_sp_AD970::sp_sub_AE3C0(const RwChar *arg_0, const RwChar *arg_4, const RwChar *arg_8)
{
    RwChar path[0x100];
    RwStream *stream;
    RwUInt32 length;
    RwUInt32 version;
    RwV2d xstep;
    RwV2d ystep;
    RwV2d origin;
    Rt2dObject *scene;
    Rt2dBBox *bbox;

    unk_0C = Width;
    unk_08 = Height;
    unk_180 = arg_4 ? sub_E8320(arg_4) : 0;
    unk_184 = arg_8 ? sub_E8320(arg_8) : 0;
    RwTexDictionarySetCurrent(unk_180);
    Rt2dFontTexDictionarySet(unk_184);
    sub_D7F20(path, arg_0);
    stream = RwStreamOpen(rwSTREAMFILENAME, rwSTREAMREAD, path);
    if (stream && RwStreamFindChunk(stream, 0x1B1, &length, &version))
    {
        dword_4E23A8 = 1;
        unk_17C = Rt2dMaestroStreamRead(0, stream);
        dword_4E23A8 = 0;
        RwStreamClose(stream, 0);
        if (unk_17C)
        {
            Rt2dDeviceGetStep(&xstep, &ystep, &origin);
            scene = Rt2dMaestroGetScene(unk_17C);
            bbox = Rt2dMaestroGetBBox(unk_17C);
            Rt2dObjectMTMScale(scene, (xstep.y + xstep.x) * ((RwReal)unk_0C / bbox->w),
                               (ystep.y + ystep.x) * ((RwReal)unk_08 / bbox->h));
            Rt2dObjectMTMTranslate(scene, 0.0f, bbox->h);
            Rt2dMaestroSetMessageHandler(unk_17C, sp_sub_ADD40);
            sp_sub_170B90(unk_17C, this);
            Rt2dSceneUpdateLTM(scene);
            Rt2dCTMSetIdentity();
            sp_sub_ADE60();
            return true;
        }
    }
    return false;
}

// sp-match: ?sp_sub_AE5A0@@YAXXZ @ 0x000AE5A0
// Lets the front end's font go.
void sp_sub_AE5A0()
{
    if (sp_dword_3B481C)
    {
        delete sp_dword_3B481C;
        sp_dword_3B481C = 0;
    }
}
