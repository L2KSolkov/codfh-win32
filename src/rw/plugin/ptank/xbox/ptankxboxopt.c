/*
 * codfh-match: RenderWare 3.6's Xbox PTank optimized path (point sprites
 * from an application-filled vertex stream), rebuilt from the image; the
 * file name is the image's RCS id string's. RenderWare's 3.7.2 tree and the
 * Godfather PDB have no Xbox PTank, so the names follow ptankd3d8.c.
 */

#include <xtl.h>

#include "rpplugin.h"
#include <rwcore.h>
#include <rpworld.h>

#include "ptank.h"

#include "xbraster.h"
#include "xbcache.h"
#include "xbrendst.h"
#include "xbpipe.h"
#include "nodeXBoxAtomicAllInOne.h"

#include "ptankxbox.h"

/* RenderWare 3.6's RCS id string, which the image keeps (the 3.7.2 tree has none) */
static const char rcsid[] = "@@@@(#)$Id: //RenderWare/RW36Active/rwsdk/plugin/ptank/xbox/ptankxboxopt.c#1 $";

extern void RwXboxSetCurrentVertexShader(DWORD handle);
extern void RwXboxSetCurrentPixelShader(DWORD handle);
extern void RwXboxSetCurrentStream(RwUInt32 stride);

static const D3DMATRIX rpPTankXboxOptIdentity =
{
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
};

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: _rcsid @ 0x00419C98
// match: _rpPTankXboxOptIdentity @ 0x00419CE8

// match: __rpPTankXboxOptRenderCallBack @ 0x002EAA10
// sp-match: __rpPTankXboxOptRenderCallBack @ 0x002054C0

RwBool
_rpPTankXboxOptRenderCallBack(RpAtomic *atomic, RpPTankData *ptankGlobal, RwInt32 actPCount)
{
    RpMaterial              *material;
    const rpPTankXboxOptData *optData;
    RwXboxRasterExtension   *rasExt;
    RwReal                  pointSizeMin, pointSizeMax, pointSize;
    RwReal                  pointScaleAB, pointScaleC;
    RwUInt32                srcBlend, dstBlend;
    DWORD                   fvf;

    material = RpGeometryGetMaterial(RpAtomicGetGeometry(atomic), 0);

    _rwXbAtomicDefaultLightingCallback(atomic);

    D3DDevice_SetTransform(D3DTS_WORLD, &rpPTankXboxOptIdentity);

    pointSizeMin = 1.0f;
    pointScaleAB = 0.0f;
    pointSize = ptankGlobal->cSize.x;
    pointSizeMax = 64.0f;
    pointScaleC = 0.5f;

    RwXboxSetCachedRenderState(D3DRS_POINTSPRITEENABLE, TRUE);
    RwXboxSetCachedRenderState(D3DRS_POINTSCALEENABLE, TRUE);
    RwXboxSetCachedRenderState(D3DRS_POINTSIZE_MIN, *(DWORD *)&pointSizeMin);
    RwXboxSetCachedRenderState(D3DRS_POINTSIZE_MAX, *(DWORD *)&pointSizeMax);
    RwXboxSetCachedRenderState(D3DRS_POINTSIZE, *(DWORD *)&pointSize);
    RwXboxSetCachedRenderState(D3DRS_POINTSCALE_A, *(DWORD *)&pointScaleAB);
    RwXboxSetCachedRenderState(D3DRS_POINTSCALE_B, *(DWORD *)&pointScaleAB);
    RwXboxSetCachedRenderState(D3DRS_POINTSCALE_C, *(DWORD *)&pointScaleC);

    RwXboxSetCurrentPixelShader(0);

    optData = (const rpPTankXboxOptData *)RPATOMICPTANKPLUGINDATA(atomic)->publicData.userData;

    fvf = D3DFVF_XYZ;
    if (optData->stride == 16)
    {
        fvf = D3DFVF_XYZ | D3DFVF_DIFFUSE;
    }

    RwXboxSetCurrentVertexShader(fvf);

    RwXboxRenderStateSetTexture(material->texture, 3);

    if (material->texture)
    {
        rasExt = RASTEREXTFROMRASTER(RwTextureGetRaster(material->texture));
    }
    else
    {
        rasExt = NULL;
    }

    if (ptankGlobal->vertexAlphaBlend)
    {
        RwRenderStateGet(rwRENDERSTATESRCBLEND, (void *)&srcBlend);
        RwRenderStateSet(rwRENDERSTATESRCBLEND, (void *)ptankGlobal->srcBlend);
        RwRenderStateGet(rwRENDERSTATEDESTBLEND, (void *)&dstBlend);
        RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void *)ptankGlobal->dstBlend);
        RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)TRUE);
    }
    else if (rasExt && rasExt->alpha)
    {
        RwRenderStateGet(rwRENDERSTATESRCBLEND, (void *)&srcBlend);
        RwRenderStateSet(rwRENDERSTATESRCBLEND, (void *)rwBLENDSRCALPHA);
        RwRenderStateGet(rwRENDERSTATEDESTBLEND, (void *)&dstBlend);
        RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void *)rwBLENDINVSRCALPHA);
        RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)TRUE);
    }
    else
    {
        RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)FALSE);
    }

    if (optData->constantColor == TRUE)
    {
        RwUInt32    tFactor;

        tFactor = ((RwUInt32)ptankGlobal->cColor.alpha << 24) |
                  ((RwUInt32)ptankGlobal->cColor.red << 16) |
                  ((RwUInt32)ptankGlobal->cColor.green << 8) |
                  (RwUInt32)ptankGlobal->cColor.blue;

        RwXboxSetCachedRenderState(D3DRS_TEXTUREFACTOR, tFactor);

        if (material->texture)
        {
            RwXboxSetCachedTextureStageState(3, D3DTSS_COLOROP, D3DTOP_MODULATE);
        }
        else
        {
            RwXboxSetCachedTextureStageState(3, D3DTSS_COLOROP, D3DTOP_SELECTARG2);
        }

        RwXboxSetCachedTextureStageState(3, D3DTSS_COLORARG1, D3DTA_TEXTURE);
        RwXboxSetCachedTextureStageState(3, D3DTSS_COLORARG2, D3DTA_TFACTOR);

        if (ptankGlobal->vertexAlphaBlend)
        {
            if (material->texture)
            {
                RwXboxSetCachedTextureStageState(3, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
            }
            else
            {
                RwXboxSetCachedTextureStageState(3, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2);
            }
        }
        else
        {
            if (material->texture)
            {
                RwXboxSetCachedTextureStageState(3, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
            }
            else
            {
                RwXboxSetCachedTextureStageState(3, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
            }
        }

        RwXboxSetCachedTextureStageState(3, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
        RwXboxSetCachedTextureStageState(3, D3DTSS_ALPHAARG2, D3DTA_TFACTOR);
    }
    else
    {
        if (material->texture)
        {
            RwXboxSetCachedTextureStageState(3, D3DTSS_COLOROP, D3DTOP_MODULATE);
        }
        else
        {
            RwXboxSetCachedTextureStageState(3, D3DTSS_COLOROP, D3DTOP_SELECTARG2);
        }

        RwXboxSetCachedTextureStageState(3, D3DTSS_COLORARG1, D3DTA_TEXTURE);
        RwXboxSetCachedTextureStageState(3, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

        if (ptankGlobal->vertexAlphaBlend)
        {
            if (material->texture)
            {
                RwXboxSetCachedTextureStageState(3, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
            }
            else
            {
                RwXboxSetCachedTextureStageState(3, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2);
            }
        }
        else
        {
            if (material->texture)
            {
                RwXboxSetCachedTextureStageState(3, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
            }
            else
            {
                RwXboxSetCachedTextureStageState(3, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
            }
        }

        RwXboxSetCachedTextureStageState(3, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
        RwXboxSetCachedTextureStageState(3, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
    }

    RwXboxSetCurrentStream(optData->stride);

    RwXboxDrawVertices(D3DPT_POINTLIST, 0, actPCount);

    RwXboxSetCachedRenderState(D3DRS_POINTSPRITEENABLE, FALSE);

    RwXboxRenderStateSetTexture(NULL, 3);

    RwXboxSetCachedTextureStageState(3, D3DTSS_COLOROP, D3DTOP_DISABLE);

    if (ptankGlobal->vertexAlphaBlend || (rasExt && rasExt->alpha))
    {
        RwRenderStateSet(rwRENDERSTATESRCBLEND, (void *)srcBlend);
        RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void *)dstBlend);
    }

    return TRUE;
}

// match: __rpPTankXboxOptInstance @ 0x002EB1A0
// sp-match: __rpPTankXboxOptInstance @ 0x00205C50
RwBool
_rpPTankXboxOptInstance(RpAtomic *atomic, RpPTankData *ptankGlobal __RWUNUSED__,
                        RwInt32 actPCount __RWUNUSED__, RwUInt32 instFlags)
{
    RPATOMICPTANKPLUGINDATA(atomic)->instFlags = instFlags;

    return TRUE;
}

// match: __rpPTankXboxOptCreate @ 0x002EB1C0
// sp-match: __rpPTankXboxOptCreate @ 0x00205C70
RwBool
_rpPTankXboxOptCreate(RpAtomic *atomic __RWUNUSED__, RpPTankData *ptankGlobal,
                      RwInt32 maxPCount __RWUNUSED__, RwUInt32 dataFlags __RWUNUSED__,
                      RwUInt32 platFlags __RWUNUSED__)
{
    ptankGlobal->userData = NULL;

    return TRUE;
}
