// The shell manager (types/type_4B8EF0.h). The original file name is not in
// the image, so it is named for its start address.

#include <stdio.h>

#include "rw/ostypes.h"
#include "rw/baengine.h"
#include "rw/bastream.h"
#include "rw/babintex.h"
#include "rw/batextur.h"
#include "rw/badevice.h"
#include "rw/rt2d.h"
#include "game/data.h"
#include "game/functions.h"
#include "game/gameloop.h"
#include "game/textmanager.h"
#include "types/type_4B8EF0.h"
#include "types/type_DC400.h"
#include "types/soundbank.h"

// Its data definitions (PLAN M5), in the image's address order.
#ifndef CODFH_SP // MP only: single player has no unreferenced 0.01f (its 16.666666f precedes the HUD texture name, SP 0x2E5340)
// 0x003D8D58
extern const RwReal flt_3D8D58 = 0.01f;
// 0x003D8D5C
extern const RwReal flt_3D8D5C = 0.01f;
#endif
// 0x003D8D60
extern const RwReal flt_3D8D60 = 16.666666f;
// 0x00429444
RwUInt8 byte_429444 = 192;
// 0x00429445
RwUInt8 byte_429445 = 128;
// 0x00429446
RwUInt8 byte_429446 = 255;
// 0x00429448
RwReal flt_429448 = 368.0f;
// 0x0042944C
RwReal flt_42944C = 7.0f;
// 0x00429450
RwReal flt_429450 = 73.0f;
// 0x00429454
RwReal flt_429454 = 392.0f;
// 0x004B8EE8
RwUInt8 byte_4B8EE8;
// End of its data definitions.

// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).
type_4B8EF0 dword_4B8EF0;


// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3D8D58@@3MB @ 0x003D8D58
// match: ?flt_3D8D5C@@3MB @ 0x003D8D5C
// match: ?flt_3D8D60@@3MB @ 0x003D8D60
// match: ??_C@_0CD@JDNLJPPJ@SHELL?2HUD?2INSTANCE?2XBOX?2HUD_MP?4T@ @ 0x003D8D64
// match: ??_C@_0CF@MAJJGOAL@SHELL?2FEND?2INSTANCE?2XBOX?2LOADING@ @ 0x003D8D88
// match: ??_C@_08CCKDOCHP@?$CFs?$CFs?4txd?$AA@ @ 0x003D8DB0
// match: ??_C@_0M@MIAPPNNB@?$CFs?$CFs_SD?4txd?$AA@ @ 0x003D8DBC
// match: ??_C@_0N@CCAGFBAI@?$CFs?$CFs_CTF?4txd?$AA@ @ 0x003D8DC8
// match: ??_C@_0N@FJGBAFDH@?$CFs?$CFs_TDM?4txd?$AA@ @ 0x003D8DD8
// match: ??_C@_0M@ENHJAOFJ@?$CFs?$CFs_DM?4txd?$AA@ @ 0x003D8DE8
// match: ??_C@_0M@JJDKCMMD@SHELL?2LOAD?2?$AA@ @ 0x003D8DF4
// match: ??_C@_0N@FMHBIPPB@ldbanner_spa?$AA@ @ 0x003D8E00
// match: ??_C@_0N@GENMJANG@ldbanner_ita?$AA@ @ 0x003D8E10
// match: ??_C@_0N@FMFODJDG@ldbanner_fre?$AA@ @ 0x003D8E20
// match: ??_C@_0N@PIAIGPDA@ldbanner_ger?$AA@ @ 0x003D8E30
// match: ??_C@_0N@GJOBKOEO@ldbanner_eng?$AA@ @ 0x003D8E40
// match: __ehhandler$?sub_E9790@type_4B8EF0@@QAEXHH@Z>1>8 @ 0x0041CF00
// match: __ehhandler$?sub_E9790@type_4B8EF0@@QAEXHH@Z>1 @ 0x0041CF08
// match: .CRT$XCU+0 @ 0x0042704C
// match: ?byte_429444@@3EA @ 0x00429444
// match: ?byte_429445@@3EA @ 0x00429445
// match: ?byte_429446@@3EA @ 0x00429446
// match: ?flt_429448@@3MA @ 0x00429448
// match: ?flt_42944C@@3MA @ 0x0042944C
// match: ?flt_429450@@3MA @ 0x00429450
// match: ?flt_429454@@3MA @ 0x00429454

// match: _$E2 @ 0x0030B500
// match: _$E3 @ 0x0030E4A0
// match: ??0type_4B8EF0@@QAE@XZ @ 0x000E8F40
// sp-match: ??0type_4B8EF0@@QAE@XZ @ 0x000B33E0
// sp-match: _$E2 @ 0x0021D580
// sp-match: _$E3 @ 0x0021E830

type_4B8EF0::type_4B8EF0()
{
    unk_32C = 0;
    unk_2A4 = 0;
}

// match: ??0type_E8F90@@QAE@XZ @ 0x000E8F90
// sp-match: ??0type_E8F90@@QAE@XZ @ 0x000B2980

// match: ??1type_4B8EF0@@QAE@XZ @ 0x000E9770
// sp-match: ??1type_4B8EF0@@QAE@XZ @ 0x000B3490
type_4B8EF0::~type_4B8EF0()
{
    sub_E99E0();
}

#ifdef CODFH_SP
void sub_19B0C0(RwInt32 arg_0);

// sp-match: ?sp_sub_B34A0@@YA_NXZ @ 0x000B34A0
// Sets the language to the first (English); true. Single player's front end calls it
// (SP 0xA5A24, 0xA5CF6).
bool sp_sub_B34A0()
{
    sub_19B0C0(0);
    return true;
}
#endif

// match: ?sub_E9790@type_4B8EF0@@QAEXHH@Z @ 0x000E9790
// match: __ehhandler$?sub_E9790@type_4B8EF0@@QAEXHH@Z-0xF @ 0x00300F30
// match: __ehhandler$?sub_E9790@type_4B8EF0@@QAEXHH@Z @ 0x00300F3F
// sp-match: ?sub_E9790@type_4B8EF0@@QAEXHH@Z @ 0x000B2C10
void type_4B8EF0::sub_E9790(RwInt32 arg_0, RwInt32 arg_4)
{
    RwInt32 var_10;

    Rt2dDeviceSetCamera((RwCamera *)arg_4);
    Rt2dDeviceSetFlat(32.0f);
    Rt2dDeviceSetLayerDepth(RwCameraGetNearClipPlane((RwCamera *)arg_4) + 0.1f);
    unk_32C = 0;
    unk_2A8 = (RwCamera *)arg_4;
    unk_2A4 = arg_0;
    unk_2A0 = 0;
    sub_D7F20(unk_2AC, "SHELL\\FONTS\\");
    Rt2dFontSetPath(unk_2AC);
    sub_EAA60();
    unk_00 = 0;
    unk_08 = 0;
    unk_04 = 0;
    unk_1C = 0;
    unk_20 = 0;
    unk_24 = 0;
    unk_28 = 0;
    unk_2C = 0;
    unk_27C = 0;
    unk_280 = 0;
    reset_unk_264();
    reset_unk_264();
    if (unk_2A4 & 4)
    {
        unk_2A0 = new (4) type_DC400;
        var_10 = unk_2A0->sub_DC5F0((RwCamera *)arg_4);
    }
}

// match: ?sub_E99A0@type_4B8EF0@@QAEXXZ @ 0x000E99A0
// sp-match: ?sub_E99A0@type_4B8EF0@@QAEXXZ @ 0x000B2D30
void type_4B8EF0::sub_E99A0()
{
    if (unk_2A4 & 4 && unk_2A0)
    {
        unk_2A0->sub_DF880();
    }
    sub_EAB00();
}

// match: ?sub_E99E0@type_4B8EF0@@QAEXXZ @ 0x000E99E0
// sp-match: ?sub_E99E0@type_4B8EF0@@QAEXXZ @ 0x000B3400
void type_4B8EF0::sub_E99E0()
{
    sub_EAB10();
    if (unk_2A4 & 1)
    {
        sub_E9C80(unk_2A4 & ~1);
    }
    if (unk_2A4 & 2)
    {
        sub_E9C80(unk_2A4 & ~2);
    }
    if (unk_2A4 & 4)
    {
        if (unk_2A0)
        {
            unk_2A0->sub_DF9F0();
            delete unk_2A0;
            unk_2A0 = 0;
        }
        sub_E9C80(unk_2A4 & ~4);
    }
}

// match: ?sub_E9AD0@type_4B8EF0@@QAEHM@Z @ 0x000E9AD0
// sp-match: ?sub_E9AD0@type_4B8EF0@@QAEHM@Z @ 0x000B2D50
RwInt32 type_4B8EF0::sub_E9AD0(RwReal arg_0)
{
    if (unk_2A0 && unk_2A0->unk_0C)
    {
        unk_2A0->sub_DD180(arg_0);
        unk_2A0->sub_DD1C0(arg_0);
        if (!unk_2A0->unk_04)
        {
            sub_EAAE0(arg_0);
            sub_17C750(arg_0);
        }
    }
    return 1;
}

// match: ?sub_E9B50@type_4B8EF0@@QAEXXZ @ 0x000E9B50
// sp-match: ?sub_E9B50@type_4B8EF0@@QAEXXZ @ 0x000B2DB0
void type_4B8EF0::sub_E9B50()
{
    if (unk_2A4 & 4 && unk_2A0 && unk_2A0->unk_0C)
    {
        unk_2A0->sub_DF000(unk_2A8);
    }
    if (unk_2A0 && !unk_2A0->unk_04)
    {
        sub_EAF10(unk_2A8);
        sub_17C830(unk_2A8);
    }
}

// match: ?sub_E9BE0@type_4B8EF0@@QAEXPBDPAURwV2d@@HMMM@Z @ 0x000E9BE0
// sp-match: ?sub_E9BE0@type_4B8EF0@@QAEXPBDPAURwV2d@@HMMM@Z @ 0x000B2E10
void type_4B8EF0::sub_E9BE0(const RwChar *arg_0, RwV2d *arg_4, RwInt32 arg_8, RwReal arg_C, RwReal arg_10,
                             RwReal arg_14)
{
    sub_EBAE0(unk_2A8, arg_0, arg_4, (type_DA580 *)arg_8, arg_C, arg_10, arg_14);
}

// match: ?sub_E9C20@type_4B8EF0@@QAEXXZ @ 0x000E9C20
// sp-match: ?sub_E9C20@type_4B8EF0@@QAEXXZ @ 0x000B2E40
void type_4B8EF0::sub_E9C20()
{
    Rt2dFontSetPath(unk_2AC);
    if (unk_2A4 & 4)
    {
#ifdef CODFH_SP // single player loads HUD.TXD, not HUD_MP.TXD (SP 0x2E5344)
        unk_2A0->sub_DFB00("SHELL\\HUD\\INSTANCE\\XBOX\\HUD.TXD", "SHELL\\HUD\\INSTANCE\\XBOX\\F_HUD.TXD");
#else
        unk_2A0->sub_DFB00("SHELL\\HUD\\INSTANCE\\XBOX\\HUD_MP.TXD", "SHELL\\HUD\\INSTANCE\\XBOX\\F_HUD.TXD");
#endif
        sub_EAC60();
        sub_EAF30();
        sub_17C4A0();
    }
}

// match: ?sub_E9C80@type_4B8EF0@@QAEXI@Z @ 0x000E9C80
// sp-match: ?sub_E9C80@type_4B8EF0@@QAEXI@Z @ 0x000B2E90
void type_4B8EF0::sub_E9C80(RwUInt32 arg_0)
{
    unk_2A4 = arg_0;
}

// match: ?sub_E9CA0@type_4B8EF0@@QAEXXZ @ 0x000E9CA0
// sp-match: ?sub_E9CA0@type_4B8EF0@@QAEXXZ @ 0x000B2EA0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_4B8EF0::sub_E9CA0()
{
    RwInt32 l120;
    const RwChar *var11C;
    RwTexture *var_118;
    RwTexDictionary *var_114;
    RwChar var_110[0x100];
    RwTexDictionary *fp_C;
    RwTexture *var8;
    const RwChar *bp_4;

    if (!sub_19B050())
    {
        return;
    }
    fp_C = 0;
    var_118 = 0;
    var_114 = 0;
    var8 = 0;
    bp_4 = sub_19B060(sub_19B050());
#ifdef CODFH_SP // single player has no game types: always the level's own picture (SP 0xB2EA0)
    sprintf(var_110, "%s%s.txd", "SHELL\\LOAD\\", bp_4);
#else
    switch (dword_4FB9E0.get_game_type())
    {
    case 1:
        sprintf(var_110, "%s%s_DM.txd", "SHELL\\LOAD\\", bp_4);
        break;
#ifdef CODFH_WIN32
    // (Supremacy, cut from the retail build: the port plays it with the team game's rules, its loading picture)
    case 16:
#endif
    case 2:
        sprintf(var_110, "%s%s_TDM.txd", "SHELL\\LOAD\\", bp_4);
        break;
    case 4:
        sprintf(var_110, "%s%s_CTF.txd", "SHELL\\LOAD\\", bp_4);
        break;
    case 8:
        sprintf(var_110, "%s%s_SD.txd", "SHELL\\LOAD\\", bp_4);
        break;
    default:
        sprintf(var_110, "%s%s.txd", "SHELL\\LOAD\\", bp_4);
        break;
    }
#endif
    fp_C = sub_EA9C0(var_110);
    var_114 = sub_EA9C0("SHELL\\FEND\\INSTANCE\\XBOX\\LOADING.TXD");
    if (fp_C)
    {
        RwTexDictionaryForAllTextures(fp_C, Clump_CaptureFirstAtomic, &var_118);
    }
    if (var_114)
    {
        var11C = off_429408[sub_19B0A0()];
        var8 = RwTexDictionaryFindNamedTexture(var_114, var11C);
    }
    for (l120 = 0; l120 < 2; l120++)
    {
        if (RwCameraBeginUpdate(unk_2A8))
        {
            if (var_118)
            {
                sub_EA640(var_118->raster, 0xFF, unk_2A8, 0.0f, 0.0f, 0.0f, 0.0f);
            }
            if (var8)
            {
                sub_EA640(var8->raster, 0xFF, unk_2A8, 150.0f, 365.0f, 360.0f, 385.0f);
            }
            RwCameraEndUpdate(unk_2A8);
            sub_126750(unk_2A8);
        }
    }
    if (fp_C)
    {
        RwTexDictionaryDestroy(fp_C);
        fp_C = 0;
        var_118 = 0;
    }
    if (var_114)
    {
        RwTexDictionaryDestroy(var_114);
        var_114 = 0;
        var8 = 0;
    }
}

// match: ?sub_E9FB0@type_4B8EF0@@QAEXH@Z @ 0x000E9FB0
// sp-match: ?sub_E9FB0@type_4B8EF0@@QAEXH@Z @ 0x000B3010
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_4B8EF0::sub_E9FB0(RwInt32 arg_0)
{
    RwIm2DVertex ebp_78[4];
    RwInt32 uD0;
    RwReal stk_CC;
    RwUInt8 lv_C5;
    void *lcl_C4;
    RwReal pC0;
    void *lBC;
    void *qB8;
    RwReal lB4;
    RwReal xB0;
    RwReal locAC;
    RwUInt8 var_A6;
    RwUInt8 lA5;
    void *lcl_A4;
    void *lcl_A0;
    RwReal ebp_9C;
    void *p98;
    void *s94;
    void *v90;
    RwReal l8C;
    RwReal var_88;
    RwUInt8 bp_81;
    RwReal ebp_80;
    RwReal v7C;
    RwReal bp_4;

    if (dword_4B8710)
    {
        return;
    }
    bp_4 = 0.0f;
    switch (arg_0)
    {
    case 1:
        bp_4 = 0.04f;
        break;
    case 2:
        bp_4 = 0.06f;
        break;
    case 3:
        bp_4 = 0.07f;
        break;
    case 4:
        bp_4 = 0.04f;
        break;
    case 5:
        bp_4 = 0.01f;
        break;
    case 6:
        bp_4 = 0.12f;
        break;
    case 7:
        bp_4 = 0.03f;
        break;
    case 8:
        bp_4 = 0.04f;
        break;
    case 9:
        bp_4 = 0.03f;
        break;
    case 10:
        bp_4 = 0.02f;
        break;
    case 11:
        bp_4 = 0.02f;
        break;
    case 12:
        bp_4 = 0.02f;
        break;
    case 13:
        bp_4 = 0.02f;
        break;
    case 14:
        bp_4 = 0.02f;
        break;
    case 15:
        bp_4 = 0.02f;
        break;
    case 16:
        bp_4 = 0.02f;
        break;
    case 17:
        bp_4 = 0.02f;
        break;
    case 18:
        bp_4 = 0.02f;
        break;
    case 19:
        bp_4 = 0.02f;
        break;
    case 20:
        bp_4 = 0.02f;
        break;
    default:
        return;
    }
    unk_32C = bp_4 + unk_32C;
    if (unk_32C > 1.0f)
    {
        unk_32C = 1.0f;
    }
    if (unk_2A8 && RwCameraBeginUpdate(unk_2A8))
    {
        lB4 = flt_429448 * unk_32C;
        xB0 = flt_42944C;
        l8C = flt_429450;
        var_88 = flt_429454;
        lv_C5 = byte_429444;
        var_A6 = byte_429445;
        lA5 = byte_4B8EE8;
        bp_81 = byte_429446;
        ebp_9C = l8C / 512.0f;
        locAC = var_88 / 448.0f;
        pC0 = lB4 / 512.0f;
        ebp_80 = xB0 / 448.0f;
        stk_CC = (RwReal)unk_2A8->frameBuffer->width;
        v7C = (RwReal)unk_2A8->frameBuffer->height;
        l8C = stk_CC * ebp_9C;
        var_88 = v7C * locAC;
        lB4 = stk_CC * pC0;
        xB0 = v7C * ebp_80;
        RwRenderStateGet(rwRENDERSTATESRCBLEND, &s94);
        RwRenderStateGet(rwRENDERSTATEDESTBLEND, &lBC);
        RwRenderStateGet(rwRENDERSTATEVERTEXALPHAENABLE, &lcl_A4);
        RwRenderStateGet(rwRENDERSTATEZWRITEENABLE, &lcl_A0);
        RwRenderStateGet(rwRENDERSTATEZTESTENABLE, &lcl_C4);
        RwRenderStateGet(rwRENDERSTATEFOGENABLE, &v90);
        RwRenderStateGet(rwRENDERSTATETEXTURERASTER, &p98);
        RwRenderStateGet(rwRENDERSTATESHADEMODE, &qB8);
        RwRenderStateSet(rwRENDERSTATESRCBLEND, (void *)rwBLENDSRCALPHA);
        RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void *)rwBLENDINVSRCALPHA);
        RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)TRUE);
        RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void *)FALSE);
        RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void *)FALSE);
        RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void *)FALSE);
        RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void *)NULL);
        RwRenderStateSet(rwRENDERSTATESHADEMODE, (void *)rwSHADEMODEGOURAUD);
        RwIm2DVertexSetScreenX(&ebp_78[0], l8C);
        RwIm2DVertexSetScreenY(&ebp_78[0], var_88);
        RwIm2DVertexSetScreenX(&ebp_78[1], l8C);
        RwIm2DVertexSetScreenY(&ebp_78[1], var_88 + xB0);
        RwIm2DVertexSetScreenX(&ebp_78[2], l8C + lB4);
        RwIm2DVertexSetScreenY(&ebp_78[2], var_88 + xB0);
        RwIm2DVertexSetScreenX(&ebp_78[3], l8C + lB4);
        RwIm2DVertexSetScreenY(&ebp_78[3], var_88);
        for (uD0 = 0; uD0 < 4; uD0++)
        {
            RwIm2DVertexSetScreenZ(&ebp_78[uD0], RwIm2DGetNearScreenZ());
            RwIm2DVertexSetRecipCameraZ(&ebp_78[uD0], 1.0f / RwCameraGetNearClipPlane(unk_2A8));
            RwIm2DVertexSetIntRGBA(&ebp_78[uD0], lv_C5, var_A6, lA5, bp_81);
        }
        RwIm2DRenderPrimitive(rwPRIMTYPETRIFAN, ebp_78, 4);
        RwRenderStateSet(rwRENDERSTATESRCBLEND, s94);
        RwRenderStateSet(rwRENDERSTATEDESTBLEND, lBC);
        RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, lcl_A4);
        RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, lcl_A0);
        RwRenderStateSet(rwRENDERSTATEZTESTENABLE, lcl_C4);
        RwRenderStateSet(rwRENDERSTATEFOGENABLE, v90);
        RwRenderStateSet(rwRENDERSTATETEXTURERASTER, p98);
        RwCameraEndUpdate(unk_2A8);
        sub_126750(unk_2A8);
    }
}

// Not in the image: a stand-in for a function the original object held last,
// which the link dropped (/OPT:REF) but whose literals stayed: the loading
// banners' names sit after sub_E9CA0's literals (0x3D8E00-0x3D8E50), before the
// next object's 16.666666, though their only user is sub_EA560's table (the next
// object's; a same-named literal is the first object's). A function's literals
// come out last-referenced first. Unreferenced.
const RwChar *dropped_3D8E00(RwInt32 arg_0)
{
    if (arg_0 == 0)
        return "ldbanner_eng";
    if (arg_0 == 1)
        return "ldbanner_ger";
    if (arg_0 == 2)
        return "ldbanner_fre";
    if (arg_0 == 3)
        return "ldbanner_ita";
    return "ldbanner_spa";
}




// Members /OPT:ICF folded into shared trivial bodies (config/aliases.txt): defined here for
// the authentic link (PLAN M7); the placement link takes the shared bodies.

// ?pDtor@type_4B8EF0@@QAEXXZ (folded into the empty body at 0x1E41C0)
void type_4B8EF0::pDtor()
{
}


#ifdef CODFH_PLAIN
// Plain builds (tools/plainbuild.py): the variables below are a second name for this unit's
// variables' bytes in the image (tools/session/overlapvars.py --aliases); only the placement
// link gives them one storage, so any other link binds them here at the image offset.
// (bound at start-up: the library initialization area runs before every game constructor)
#pragma warning(disable: 4073)
#pragma init_seg(lib)
struct type_3DF8D8_04_data;
struct type_DC400;
// 0x004B8EF4: dword_4B8EF0 + 0x4
RwV2d &unk_4B8EF4 = *(RwV2d *)((RwUInt8 *)&dword_4B8EF0 + 0x4);
// 0x004B8EFC: dword_4B8EF0 + 0xC
RwRGBA &unk_4B8EFC = *(RwRGBA *)((RwUInt8 *)&dword_4B8EF0 + 0xC);
// 0x004B8F00: dword_4B8EF0 + 0x10
RwRGBA &unk_4B8F00 = *(RwRGBA *)((RwUInt8 *)&dword_4B8EF0 + 0x10);
// 0x004B8F04: dword_4B8EF0 + 0x14
RwRGBA &unk_4B8F04 = *(RwRGBA *)((RwUInt8 *)&dword_4B8EF0 + 0x14);
// 0x004B8F08: dword_4B8EF0 + 0x18
RwReal &flt_4B8F08 = *(RwReal *)((RwUInt8 *)&dword_4B8EF0 + 0x18);
// 0x004B8F0C: dword_4B8EF0 + 0x1C
RwReal &flt_4B8F0C = *(RwReal *)((RwUInt8 *)&dword_4B8EF0 + 0x1C);
// 0x004B8F10: dword_4B8EF0 + 0x20
RwReal &flt_4B8F10 = *(RwReal *)((RwUInt8 *)&dword_4B8EF0 + 0x20);
// 0x004B8F14: dword_4B8EF0 + 0x24
RwReal &flt_4B8F14 = *(RwReal *)((RwUInt8 *)&dword_4B8EF0 + 0x24);
// 0x004B8F18: dword_4B8EF0 + 0x28
RwReal &flt_4B8F18 = *(RwReal *)((RwUInt8 *)&dword_4B8EF0 + 0x28);
// 0x004B8F1C: dword_4B8EF0 + 0x2C
RwReal &dword_4B8F1C = *(RwReal *)((RwUInt8 *)&dword_4B8EF0 + 0x2C);
// 0x004B8F20: dword_4B8EF0 + 0x30
RwRGBA &dword_4B8F20 = *(RwRGBA *)((RwUInt8 *)&dword_4B8EF0 + 0x30);
// 0x004B8F24: dword_4B8EF0 + 0x34
RwRGBA &dword_4B8F24 = *(RwRGBA *)((RwUInt8 *)&dword_4B8EF0 + 0x34);
// 0x004B8F2C: dword_4B8EF0 + 0x3C
RwReal &flt_4B8F2C = *(RwReal *)((RwUInt8 *)&dword_4B8EF0 + 0x3C);
// 0x004B8F30: dword_4B8EF0 + 0x40
RwReal &flt_4B8F30 = *(RwReal *)((RwUInt8 *)&dword_4B8EF0 + 0x40);
// 0x004B8F34: dword_4B8EF0 + 0x44
RwRGBA &unk_4B8F34 = *(RwRGBA *)((RwUInt8 *)&dword_4B8EF0 + 0x44);
// 0x004B8F38: dword_4B8EF0 + 0x48
RwRGBA &unk_4B8F38 = *(RwRGBA *)((RwUInt8 *)&dword_4B8EF0 + 0x48);
// 0x004B8F3C: dword_4B8EF0 + 0x4C
RwInt32 &dword_4B8F3C = *(RwInt32 *)((RwUInt8 *)&dword_4B8EF0 + 0x4C);
// 0x004B8F40: dword_4B8EF0 + 0x50
RwInt32 &dword_4B8F40 = *(RwInt32 *)((RwUInt8 *)&dword_4B8EF0 + 0x50);
// 0x004B8F44: dword_4B8EF0 + 0x54
RwRGBA &dword_4B8F44 = *(RwRGBA *)((RwUInt8 *)&dword_4B8EF0 + 0x54);
// 0x004B8F48: dword_4B8EF0 + 0x58
RwRGBA &dword_4B8F48 = *(RwRGBA *)((RwUInt8 *)&dword_4B8EF0 + 0x58);
// 0x004B8F4C: dword_4B8EF0 + 0x5C
RwRGBA &dword_4B8F4C = *(RwRGBA *)((RwUInt8 *)&dword_4B8EF0 + 0x5C);
// 0x004B8F50: dword_4B8EF0 + 0x60
RwRGBA &dword_4B8F50 = *(RwRGBA *)((RwUInt8 *)&dword_4B8EF0 + 0x60);
// 0x004B8F54: dword_4B8EF0 + 0x64
RwV2d &dword_4B8F54 = *(RwV2d *)((RwUInt8 *)&dword_4B8EF0 + 0x64);
// 0x004B8F5C: dword_4B8EF0 + 0x6C
// SP stores the pause fade duration and opacity as floats; keep those aliases
// floating-point in the Win32 plain build so the HUD fade math reads them correctly.
#ifdef CODFH_SP
RwReal &dword_4B8F5C = *(RwReal *)((RwUInt8 *)&dword_4B8EF0 + 0x6C);
#else
RwInt32 &dword_4B8F5C = *(RwInt32 *)((RwUInt8 *)&dword_4B8EF0 + 0x6C);
#endif
// 0x004B8F60: dword_4B8EF0 + 0x70
#ifdef CODFH_SP
RwReal &dword_4B8F60 = *(RwReal *)((RwUInt8 *)&dword_4B8EF0 + 0x70);
#else
RwInt32 &dword_4B8F60 = *(RwInt32 *)((RwUInt8 *)&dword_4B8EF0 + 0x70);
#endif
// 0x004B8F64: dword_4B8EF0 + 0x74
RwRGBA &dword_4B8F64 = *(RwRGBA *)((RwUInt8 *)&dword_4B8EF0 + 0x74);
// 0x004B8F68: dword_4B8EF0 + 0x78
RwV2d &dword_4B8F68 = *(RwV2d *)((RwUInt8 *)&dword_4B8EF0 + 0x78);
// 0x004B8F70: dword_4B8EF0 + 0x80
RwV3d &dword_4B8F70 = *(RwV3d *)((RwUInt8 *)&dword_4B8EF0 + 0x80);
// 0x004B8F7C: dword_4B8EF0 + 0x8C
RwReal &flt_4B8F7C = *(RwReal *)((RwUInt8 *)&dword_4B8EF0 + 0x8C);
// 0x004B8F80: dword_4B8EF0 + 0x90
RwReal &dword_4B8F80 = *(RwReal *)((RwUInt8 *)&dword_4B8EF0 + 0x90);
// 0x004B8F84: dword_4B8EF0 + 0x94
RwReal &dword_4B8F84 = *(RwReal *)((RwUInt8 *)&dword_4B8EF0 + 0x94);
// 0x004B8F88: dword_4B8EF0 + 0x98
RwV2d &dword_4B8F88 = *(RwV2d *)((RwUInt8 *)&dword_4B8EF0 + 0x98);
// 0x004B8F90: dword_4B8EF0 + 0xA0
type_3DF8D8_04_data &unk_4B8F90 = *(type_3DF8D8_04_data *)((RwUInt8 *)&dword_4B8EF0 + 0xA0);
// 0x004B8F98: dword_4B8EF0 + 0xA8
RwRGBA &dword_4B8F98 = *(RwRGBA *)((RwUInt8 *)&dword_4B8EF0 + 0xA8);
// 0x004B8F9C: dword_4B8EF0 + 0xAC
RwRGBA &dword_4B8F9C = *(RwRGBA *)((RwUInt8 *)&dword_4B8EF0 + 0xAC);
// 0x004B8FA0: dword_4B8EF0 + 0xB0
RwReal &dword_4B8FA0 = *(RwReal *)((RwUInt8 *)&dword_4B8EF0 + 0xB0);
// 0x004B8FA4: dword_4B8EF0 + 0xB4
type_3DF8D8_04_data &unk_4B8FA4 = *(type_3DF8D8_04_data *)((RwUInt8 *)&dword_4B8EF0 + 0xB4);
// 0x004B8FAC: dword_4B8EF0 + 0xBC
type_3DF8D8_04_data &unk_4B8FAC = *(type_3DF8D8_04_data *)((RwUInt8 *)&dword_4B8EF0 + 0xBC);
// 0x004B8FB4: dword_4B8EF0 + 0xC4
type_3DF8D8_04_data &unk_4B8FB4 = *(type_3DF8D8_04_data *)((RwUInt8 *)&dword_4B8EF0 + 0xC4);
// 0x004B8FBC: dword_4B8EF0 + 0xCC
type_3DF8D8_04_data &unk_4B8FBC = *(type_3DF8D8_04_data *)((RwUInt8 *)&dword_4B8EF0 + 0xCC);
// 0x004B8FC4: dword_4B8EF0 + 0xD4
type_3DF8D8_04_data &unk_4B8FC4 = *(type_3DF8D8_04_data *)((RwUInt8 *)&dword_4B8EF0 + 0xD4);
// 0x004B8FCC: dword_4B8EF0 + 0xDC
type_3DF8D8_04_data &unk_4B8FCC = *(type_3DF8D8_04_data *)((RwUInt8 *)&dword_4B8EF0 + 0xDC);
// 0x004B8FD4: dword_4B8EF0 + 0xE4
type_3DF8D8_04_data &unk_4B8FD4 = *(type_3DF8D8_04_data *)((RwUInt8 *)&dword_4B8EF0 + 0xE4);
// 0x004B8FDC: dword_4B8EF0 + 0xEC
type_3DF8D8_04_data &unk_4B8FDC = *(type_3DF8D8_04_data *)((RwUInt8 *)&dword_4B8EF0 + 0xEC);
// 0x004B8FE4: dword_4B8EF0 + 0xF4
type_3DF8D8_04_data &unk_4B8FE4 = *(type_3DF8D8_04_data *)((RwUInt8 *)&dword_4B8EF0 + 0xF4);
// 0x004B8FEC: dword_4B8EF0 + 0xFC
type_3DF8D8_04_data &unk_4B8FEC = *(type_3DF8D8_04_data *)((RwUInt8 *)&dword_4B8EF0 + 0xFC);
// 0x004B8FF4: dword_4B8EF0 + 0x104
type_3DF8D8_04_data &unk_4B8FF4 = *(type_3DF8D8_04_data *)((RwUInt8 *)&dword_4B8EF0 + 0x104);
// 0x004B8FFC: dword_4B8EF0 + 0x10C
type_3DF8D8_04_data &unk_4B8FFC = *(type_3DF8D8_04_data *)((RwUInt8 *)&dword_4B8EF0 + 0x10C);
// 0x004B9004: dword_4B8EF0 + 0x114
type_3DF8D8_04_data &unk_4B9004 = *(type_3DF8D8_04_data *)((RwUInt8 *)&dword_4B8EF0 + 0x114);
// 0x004B900C: dword_4B8EF0 + 0x11C
type_3DF8D8_04_data &unk_4B900C = *(type_3DF8D8_04_data *)((RwUInt8 *)&dword_4B8EF0 + 0x11C);
// 0x004B9014: dword_4B8EF0 + 0x124
type_3DF8D8_04_data &unk_4B9014 = *(type_3DF8D8_04_data *)((RwUInt8 *)&dword_4B8EF0 + 0x124);
// 0x004B901C: dword_4B8EF0 + 0x12C
type_3DF8D8_04_data &unk_4B901C = *(type_3DF8D8_04_data *)((RwUInt8 *)&dword_4B8EF0 + 0x12C);
// 0x004B9024: dword_4B8EF0 + 0x134
type_3DF8D8_04_data &unk_4B9024 = *(type_3DF8D8_04_data *)((RwUInt8 *)&dword_4B8EF0 + 0x134);
// 0x004B902C: dword_4B8EF0 + 0x13C
type_3DF8D8_04_data &unk_4B902C = *(type_3DF8D8_04_data *)((RwUInt8 *)&dword_4B8EF0 + 0x13C);
// 0x004B9034: dword_4B8EF0 + 0x144
type_3DF8D8_04_data &unk_4B9034 = *(type_3DF8D8_04_data *)((RwUInt8 *)&dword_4B8EF0 + 0x144);
// 0x004B903C: dword_4B8EF0 + 0x14C
type_3DF8D8_04_data &unk_4B903C = *(type_3DF8D8_04_data *)((RwUInt8 *)&dword_4B8EF0 + 0x14C);
// 0x004B9044: dword_4B8EF0 + 0x154
type_3DF8D8_04_data &unk_4B9044 = *(type_3DF8D8_04_data *)((RwUInt8 *)&dword_4B8EF0 + 0x154);
// 0x004B904C: dword_4B8EF0 + 0x15C
type_3DF8D8_04_data &unk_4B904C = *(type_3DF8D8_04_data *)((RwUInt8 *)&dword_4B8EF0 + 0x15C);
// 0x004B9054: dword_4B8EF0 + 0x164
type_3DF8D8_04_data &unk_4B9054 = *(type_3DF8D8_04_data *)((RwUInt8 *)&dword_4B8EF0 + 0x164);
// 0x004B905C: dword_4B8EF0 + 0x16C
type_3DF8D8_04_data &unk_4B905C = *(type_3DF8D8_04_data *)((RwUInt8 *)&dword_4B8EF0 + 0x16C);
// 0x004B9064: dword_4B8EF0 + 0x174
type_3DF8D8_04_data &unk_4B9064 = *(type_3DF8D8_04_data *)((RwUInt8 *)&dword_4B8EF0 + 0x174);
// 0x004B906C: dword_4B8EF0 + 0x17C
type_3DF8D8_04_data &unk_4B906C = *(type_3DF8D8_04_data *)((RwUInt8 *)&dword_4B8EF0 + 0x17C);
// 0x004B9074: dword_4B8EF0 + 0x184
type_3DF8D8_04_data &unk_4B9074 = *(type_3DF8D8_04_data *)((RwUInt8 *)&dword_4B8EF0 + 0x184);
// 0x004B907C: dword_4B8EF0 + 0x18C
type_3DF8D8_04_data &unk_4B907C = *(type_3DF8D8_04_data *)((RwUInt8 *)&dword_4B8EF0 + 0x18C);
// 0x004B9084: dword_4B8EF0 + 0x194
type_3DF8D8_04_data &unk_4B9084 = *(type_3DF8D8_04_data *)((RwUInt8 *)&dword_4B8EF0 + 0x194);
// 0x004B908C: dword_4B8EF0 + 0x19C
type_3DF8D8_04_data &unk_4B908C = *(type_3DF8D8_04_data *)((RwUInt8 *)&dword_4B8EF0 + 0x19C);
// 0x004B9094: dword_4B8EF0 + 0x1A4
type_3DF8D8_04_data &unk_4B9094 = *(type_3DF8D8_04_data *)((RwUInt8 *)&dword_4B8EF0 + 0x1A4);
// 0x004B909C: dword_4B8EF0 + 0x1AC
type_3DF8D8_04_data &unk_4B909C = *(type_3DF8D8_04_data *)((RwUInt8 *)&dword_4B8EF0 + 0x1AC);
// 0x004B90A4: dword_4B8EF0 + 0x1B4
type_3DF8D8_04_data &unk_4B90A4 = *(type_3DF8D8_04_data *)((RwUInt8 *)&dword_4B8EF0 + 0x1B4);
// 0x004B90AC: dword_4B8EF0 + 0x1BC
type_3DF8D8_04_data &unk_4B90AC = *(type_3DF8D8_04_data *)((RwUInt8 *)&dword_4B8EF0 + 0x1BC);
// 0x004B90B4: dword_4B8EF0 + 0x1C4
type_3DF8D8_04_data &unk_4B90B4 = *(type_3DF8D8_04_data *)((RwUInt8 *)&dword_4B8EF0 + 0x1C4);
// 0x004B90BC: dword_4B8EF0 + 0x1CC
type_3DF8D8_04_data &unk_4B90BC = *(type_3DF8D8_04_data *)((RwUInt8 *)&dword_4B8EF0 + 0x1CC);
// 0x004B90C4: dword_4B8EF0 + 0x1D4
type_3DF8D8_04_data &unk_4B90C4 = *(type_3DF8D8_04_data *)((RwUInt8 *)&dword_4B8EF0 + 0x1D4);
// 0x004B90CC: dword_4B8EF0 + 0x1DC
type_3DF8D8_04_data &unk_4B90CC = *(type_3DF8D8_04_data *)((RwUInt8 *)&dword_4B8EF0 + 0x1DC);
// 0x004B90D4: dword_4B8EF0 + 0x1E4
type_3DF8D8_04_data &unk_4B90D4 = *(type_3DF8D8_04_data *)((RwUInt8 *)&dword_4B8EF0 + 0x1E4);
// 0x004B90DC: dword_4B8EF0 + 0x1EC
type_3DF8D8_04_data &unk_4B90DC = *(type_3DF8D8_04_data *)((RwUInt8 *)&dword_4B8EF0 + 0x1EC);
// 0x004B90E4: dword_4B8EF0 + 0x1F4
type_3DF8D8_04_data &unk_4B90E4 = *(type_3DF8D8_04_data *)((RwUInt8 *)&dword_4B8EF0 + 0x1F4);
// 0x004B90EC: dword_4B8EF0 + 0x1FC
type_3DF8D8_04_data &unk_4B90EC = *(type_3DF8D8_04_data *)((RwUInt8 *)&dword_4B8EF0 + 0x1FC);
// 0x004B90F4: dword_4B8EF0 + 0x204
type_3DF8D8_04_data &unk_4B90F4 = *(type_3DF8D8_04_data *)((RwUInt8 *)&dword_4B8EF0 + 0x204);
// 0x004B90FC: dword_4B8EF0 + 0x20C
type_3DF8D8_04_data &unk_4B90FC = *(type_3DF8D8_04_data *)((RwUInt8 *)&dword_4B8EF0 + 0x20C);
// 0x004B9104: dword_4B8EF0 + 0x214
type_3DF8D8_04_data &unk_4B9104 = *(type_3DF8D8_04_data *)((RwUInt8 *)&dword_4B8EF0 + 0x214);
// 0x004B910C: dword_4B8EF0 + 0x21C
type_3DF8D8_04_data &unk_4B910C = *(type_3DF8D8_04_data *)((RwUInt8 *)&dword_4B8EF0 + 0x21C);
// 0x004B9114: dword_4B8EF0 + 0x224
type_3DF8D8_04_data &unk_4B9114 = *(type_3DF8D8_04_data *)((RwUInt8 *)&dword_4B8EF0 + 0x224);
// 0x004B911C: dword_4B8EF0 + 0x22C
type_3DF8D8_04_data &unk_4B911C = *(type_3DF8D8_04_data *)((RwUInt8 *)&dword_4B8EF0 + 0x22C);
// 0x004B9124: dword_4B8EF0 + 0x234
type_3DF8D8_04_data &unk_4B9124 = *(type_3DF8D8_04_data *)((RwUInt8 *)&dword_4B8EF0 + 0x234);
// 0x004B912C: dword_4B8EF0 + 0x23C
type_3DF8D8_04_data &unk_4B912C = *(type_3DF8D8_04_data *)((RwUInt8 *)&dword_4B8EF0 + 0x23C);
// 0x004B9134: dword_4B8EF0 + 0x244
type_3DF8D8_04_data &unk_4B9134 = *(type_3DF8D8_04_data *)((RwUInt8 *)&dword_4B8EF0 + 0x244);
// 0x004B913C: dword_4B8EF0 + 0x24C
type_3DF8D8_04_data &dword_4B913C = *(type_3DF8D8_04_data *)((RwUInt8 *)&dword_4B8EF0 + 0x24C);
// 0x004B9144: dword_4B8EF0 + 0x254
type_3DF8D8_04_data &dword_4B9144 = *(type_3DF8D8_04_data *)((RwUInt8 *)&dword_4B8EF0 + 0x254);
// 0x004B914C: dword_4B8EF0 + 0x25C
type_3DF8D8_04_data &dword_4B914C = *(type_3DF8D8_04_data *)((RwUInt8 *)&dword_4B8EF0 + 0x25C);
// 0x004B9154: dword_4B8EF0 + 0x264
RwReal &dword_4B9154 = *(RwReal *)((RwUInt8 *)&dword_4B8EF0 + 0x264);
// 0x004B9158: dword_4B8EF0 + 0x268
RwReal &dword_4B9158 = *(RwReal *)((RwUInt8 *)&dword_4B8EF0 + 0x268);
// 0x004B915C: dword_4B8EF0 + 0x26C
RwReal &flt_4B915C = *(RwReal *)((RwUInt8 *)&dword_4B8EF0 + 0x26C);
// 0x004B9160: dword_4B8EF0 + 0x270
RwReal &flt_4B9160 = *(RwReal *)((RwUInt8 *)&dword_4B8EF0 + 0x270);
// 0x004B9164: dword_4B8EF0 + 0x274
RwReal &flt_4B9164 = *(RwReal *)((RwUInt8 *)&dword_4B8EF0 + 0x274);
// 0x004B9168: dword_4B8EF0 + 0x278
RwReal &flt_4B9168 = *(RwReal *)((RwUInt8 *)&dword_4B8EF0 + 0x278);
// 0x004B916C: dword_4B8EF0 + 0x27C
RwInt32 &dword_4B916C = *(RwInt32 *)((RwUInt8 *)&dword_4B8EF0 + 0x27C);
// 0x004B9170: dword_4B8EF0 + 0x280
RwInt32 &dword_4B9170 = *(RwInt32 *)((RwUInt8 *)&dword_4B8EF0 + 0x280);
// 0x004B9174: dword_4B8EF0 + 0x284
RwV2d &dword_4B9174 = *(RwV2d *)((RwUInt8 *)&dword_4B8EF0 + 0x284);
// 0x004B917C: dword_4B8EF0 + 0x28C
RwRGBAReal &unk_4B917C = *(RwRGBAReal *)((RwUInt8 *)&dword_4B8EF0 + 0x28C);
// 0x004B918C: dword_4B8EF0 + 0x29C
RwInt32 &dword_4B918C = *(RwInt32 *)((RwUInt8 *)&dword_4B8EF0 + 0x29C);
// 0x004B9190: dword_4B8EF0 + 0x2A0
type_DC400 *&dword_4B9190 = *(type_DC400 * *)((RwUInt8 *)&dword_4B8EF0 + 0x2A0);
// 0x004B9194: dword_4B8EF0 + 0x2A4
RwUInt32 &dword_4B9194 = *(RwUInt32 *)((RwUInt8 *)&dword_4B8EF0 + 0x2A4);
// 0x004B919C: dword_4B8EF0 + 0x2AC
RwChar (&path)[132] = *(RwChar (*)[132])((RwUInt8 *)&dword_4B8EF0 + 0x2AC);
#endif
