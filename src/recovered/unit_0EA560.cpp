// Split from unit_0E8F40.cpp at 0x0EA560, where the image ends that object (its deferred
// functions come before the next out-of-line one; PLAN M7).

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
// 0x003D8E50
extern const RwReal flt_3D8E50 = 16.666666f;

// match: ?flt_3D8E50@@3MB @ 0x003D8E50


// match: ?sub_EA560@@YAXPAURwCamera@@@Z @ 0x000EA560
// match: ??_C@_0O@KKFOMDPE@ldbanner_xbox?$AA@ @ 0x003D8E54
// match: ??_C@_0CG@DBNGCFCJ@shell?2fend?2INSTANCE?2xbox?2LDBANNE@ @ 0x003D8E64
// match: ?off_429458@?1??sub_EA560@@YAXPAURwCamera@@@Z@4PAPBDA @ 0x00429458
// sp-match: ?sub_EA560@@YAXPAURwCamera@@@Z @ 0x000B3840
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_EA560(RwCamera *arg_0)
{
    // The loading banners by language (0x429458): a static of this function, its
    // literals come out with it, as the image has them.
    static const RwChar *off_429458[15] = {
        "ldbanner_eng",
        "ldbanner_ger",
        "ldbanner_fre",
        "ldbanner_ger",
        "ldbanner_fre",
        "ldbanner_ita",
        "ldbanner_spa",
        "ldbanner_eng",
        "ldbanner_eng",
        "ldbanner_eng",
        "ldbanner_eng",
        "ldbanner_eng",
        "ldbanner_eng",
        "ldbanner_eng",
        "ldbanner_eng",
    };
    RwInt32 local_C;
    const RwChar *var_8;
    RwTexDictionary *bp_4;

    if (!arg_0)
    {
        return;
    }
    bp_4 = sub_EA9C0("shell\\fend\\INSTANCE\\xbox\\LDBANNER.TXD");
    var_8 = off_429458[sub_19B0A0()];
    if (!sub_19B0A0())
    {
        var_8 = "ldbanner_xbox";
    }
    for (local_C = 0; local_C < 2; local_C++)
    {
        if (RwCameraBeginUpdate(arg_0))
        {
            if (RwTexDictionaryFindNamedTexture(bp_4, var_8))
            {
                sub_EA640(RwTexDictionaryFindNamedTexture(bp_4, var_8)->raster, 0xFF, arg_0, 0.0f, 0.0f, 0.0f, 0.0f);
            }
            RwCameraEndUpdate(arg_0);
        }
        RwRasterShowRaster(arg_0->frameBuffer, 0, 1);
    }
    RwTexDictionaryDestroy(bp_4);
}
// match: ?sub_EA640@@YAXPAURwRaster@@EPAURwCamera@@MMMM@Z @ 0x000EA640
// sp-match: ?sub_EA640@@YAXPAURwRaster@@EPAURwCamera@@MMMM@Z @ 0x000B34B0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_EA640(RwRaster *arg_0, RwUInt8 arg_4, RwCamera *arg_8, RwReal arg_C, RwReal arg_10, RwReal arg_14,
               RwReal arg_18)
{
    RwIm2DVertex var_A0[4];
    void *var_2C;
    void *var_28;
    void *ebp_24;
    void *var_20;
    RwReal l1C;
    void *m_18;
    void *ebp_14;
    void *lv_10;
    RwReal var_C;
    void *bp_8;
    void *bp_4;

    if (arg_C == arg_14)
    {
        arg_C = arg_10 = 0.0f;
        arg_14 = 512.0f;
        arg_18 = 448.0f;
    }
    var_C = (RwReal)arg_8->frameBuffer->width / 512.0f;
    l1C = (RwReal)arg_8->frameBuffer->height / 448.0f;
    arg_C *= var_C;
    arg_14 *= var_C;
    arg_10 *= l1C;
    arg_18 *= l1C;
    RwIm2DVertexSetScreenX(&var_A0[0], arg_C);
    RwIm2DVertexSetScreenY(&var_A0[0], arg_10);
    RwIm2DVertexSetScreenZ(&var_A0[0], RwIm2DGetNearScreenZ());
    RwIm2DVertexSetRecipCameraZ(&var_A0[0], 1.0f / RwCameraGetNearClipPlane(arg_8));
    RwIm2DVertexSetU(&var_A0[0], 0.0f, 1.0f);
    RwIm2DVertexSetV(&var_A0[0], 0.0f, 1.0f);
    RwIm2DVertexSetIntRGBA(&var_A0[0], 255, 255, 255, arg_4);
    RwIm2DVertexSetScreenX(&var_A0[1], arg_C);
    RwIm2DVertexSetScreenY(&var_A0[1], arg_18);
    RwIm2DVertexSetScreenZ(&var_A0[1], RwIm2DGetNearScreenZ());
    RwIm2DVertexSetRecipCameraZ(&var_A0[1], 1.0f / RwCameraGetNearClipPlane(arg_8));
    RwIm2DVertexSetU(&var_A0[1], 0.0f, 1.0f);
    RwIm2DVertexSetV(&var_A0[1], 1.0f, 1.0f);
    RwIm2DVertexSetIntRGBA(&var_A0[1], 255, 255, 255, arg_4);
    RwIm2DVertexSetScreenX(&var_A0[2], arg_14);
    RwIm2DVertexSetScreenY(&var_A0[2], arg_10);
    RwIm2DVertexSetScreenZ(&var_A0[2], RwIm2DGetNearScreenZ());
    RwIm2DVertexSetRecipCameraZ(&var_A0[2], 1.0f / RwCameraGetNearClipPlane(arg_8));
    RwIm2DVertexSetU(&var_A0[2], 1.0f, 1.0f);
    RwIm2DVertexSetV(&var_A0[2], 0.0f, 1.0f);
    RwIm2DVertexSetIntRGBA(&var_A0[2], 255, 255, 255, arg_4);
    RwIm2DVertexSetScreenX(&var_A0[3], arg_14);
    RwIm2DVertexSetScreenY(&var_A0[3], arg_18);
    RwIm2DVertexSetScreenZ(&var_A0[3], RwIm2DGetNearScreenZ());
    RwIm2DVertexSetRecipCameraZ(&var_A0[3], 1.0f / RwCameraGetNearClipPlane(arg_8));
    RwIm2DVertexSetU(&var_A0[3], 1.0f, 1.0f);
    RwIm2DVertexSetV(&var_A0[3], 1.0f, 1.0f);
    RwIm2DVertexSetIntRGBA(&var_A0[3], 255, 255, 255, arg_4);
    bp_4 = 0;
    RwRenderStateGet(rwRENDERSTATETEXTURERASTER, &bp_4);
    RwRenderStateGet(rwRENDERSTATETEXTUREFILTER, &bp_8);
    RwRenderStateGet(rwRENDERSTATEFOGENABLE, &var_28);
    RwRenderStateGet(rwRENDERSTATEZTESTENABLE, &var_20);
    RwRenderStateGet(rwRENDERSTATEZWRITEENABLE, &lv_10);
    RwRenderStateGet(rwRENDERSTATETEXTUREADDRESS, &ebp_24);
    RwRenderStateGet(rwRENDERSTATEVERTEXALPHAENABLE, &ebp_14);
    RwRenderStateGet(rwRENDERSTATESRCBLEND, &var_2C);
    RwRenderStateGet(rwRENDERSTATEDESTBLEND, &m_18);
    RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, (void *)rwFILTERLINEAR);
    RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void *)FALSE);
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void *)FALSE);
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void *)FALSE);
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, arg_0);
    RwRenderStateSet(rwRENDERSTATETEXTUREADDRESS, (void *)rwTEXTUREADDRESSCLAMP);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)TRUE);
    RwRenderStateSet(rwRENDERSTATESRCBLEND, (void *)rwBLENDSRCALPHA);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void *)rwBLENDINVSRCALPHA);
    RwIm2DRenderPrimitive(rwPRIMTYPETRISTRIP, var_A0, 4);
    RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, bp_8);
    RwRenderStateSet(rwRENDERSTATEFOGENABLE, var_28);
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, var_20);
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, lv_10);
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, bp_4);
    RwRenderStateSet(rwRENDERSTATETEXTUREADDRESS, ebp_24);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, ebp_14);
    RwRenderStateSet(rwRENDERSTATESRCBLEND, var_2C);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, m_18);
}
#ifdef CODFH_SP
// Single player's own copy of the path helper (SP 0xB37B0, sprintf of "%s"),
// static here, so sub_EA9C0 passes it the buffer in ecx and the name in eax.
// sp-match: ?sp_sub_B37B0@@YAXPADPBD@Z @ 0x000B37B0
static void sp_sub_B37B0(RwChar *arg_0, const RwChar *arg_4)
{
    sprintf(arg_0, "%s", arg_4);
}
#endif

// match: ?sub_EA9C0@@YAPAURwTexDictionary@@PBD@Z @ 0x000EA9C0
// sp-match: ?sub_EA9C0@@YAPAURwTexDictionary@@PBD@Z @ 0x000B37C0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwTexDictionary *sub_EA9C0(const RwChar *arg_0)
{
    RwChar var_210[0x200];
    RwTexDictionary *var8;
    RwStream *l4;

    var8 = 0;
    l4 = 0;
#ifdef CODFH_SP // single player calls its own static copy (SP 0xB37CF)
    sp_sub_B37B0(var_210, arg_0);
#else
    sub_D7F20(var_210, arg_0);
#endif
    l4 = RwStreamOpen(rwSTREAMFILENAME, rwSTREAMREAD, var_210);
    if (l4)
    {
        if (RwStreamFindChunk(l4, 0x16, 0, 0))
        {
            var8 = RwTexDictionaryStreamRead(l4, 0);
        }
        RwStreamClose(l4, 0);
    }
    return var8;
}
