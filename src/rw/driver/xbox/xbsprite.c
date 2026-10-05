/*
 * codfh-match: RenderWare 3.6's Xbox driver raster rendering and clearing
 * (driver/xbox/xbsprite.c), rebuilt from the image after d3d8raster.c's
 * sprite functions; names from the Godfather PDB's copy of the driver.
 */

#include <xtl.h>
#include "batypes.h"
#include "batype.h"
#include "balibtyp.h"
#include "barwtyp.h"
#include "badebug.h"
#include "bamemory.h"
#include "badevice.h"
#include "baraster.h"
#include "batextur.h"
#include "baimmedi.h"
#include "xbraster.h"
#include "xbdevice.h"
#include "xbcache.h"
#include "xbrendst.h"
#include "xb2drend.h"
#include "xbsprite.h"

/* RenderWare 3.6's RCS id string, which the image keeps (the 3.7.2 tree has none) */
static const char rcsid[] = "@@@@(#)$Id: //RenderWare/RW36Active/rwsdk/driver/xbox/xbsprite.c#2 $";

/* A pre-transformed, textured quad vertex. */
typedef struct _rwXbQuadVertex _rwXbQuadVertex;
struct _rwXbQuadVertex
{
    RwReal      x;
    RwReal      y;
    RwReal      z;
    RwReal      rhw;
    RwReal      u;
    RwReal      v;
};

/* The raster RwRasterPushContext made current (static here; only this file
   uses it). */
static RwRaster *RwXbCurrentRasterTarget = NULL;

/****************************************************************************
 XbRasterRenderQuad

 Purpose    : Renders a quad into the current raster target.

 On entry   : Source raster
            : Rect (where image is to be written)
            : scaled (does the src raster need to be scaled 'RwRasterRenderScaled')
            : alpha (does the src raster need to preserve alpha 'RwRasterRenderFast')
 */
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: _rcsid @ 0x00417328
// match: ??_C@_0DB@JGBKFGGL@SRC?0?5DST?5Raster?5render?5combinati@ @ 0x00417370
// match: ??_C@_0CG@KAKONOEN@Only?5the?5entire?5raster?5can?5be?5cl@ @ 0x004173A4

// match: _XbRasterRenderQuad @ 0x002BA550

static void
XbRasterRenderQuad(RwRaster *raster, RwRect *rect, RwBool scaled, RwBool alpha)
{
    RwTextureFilterMode     filterMode;
    RwCullMode              cullMode;
    RwBlendFunction         dstBlend;
    RwBlendFunction         srcBlend;
    RwBool                  fogEnable;
    DWORD                   zEnabled;
    D3DVIEWPORT8            viewport;
    RwRaster               *curRaster;
    DWORD                  *pPush;
    RwBool                  vertexAlpha;
    RwTextureAddressMode    addressModeU;
    RwRaster               *parentRaster;
    RwTextureAddressMode    addressModeV;
    RwRaster               *parentRasterDest;
    _rwXbQuadVertex        *quadVerts;
    RwUInt32                pushSizeInDWORDs = 24;

    parentRaster = RwRasterGetParent(raster);
    parentRasterDest = RwRasterGetParent(RwXbCurrentRasterTarget);

    if (parentRasterDest->cType == rwRASTERTYPECAMERATEXTURE)
    {
        RwXboxRasterExtension  *rasDestExt;
        D3DSurface             *surfaceLevel;

        rasDestExt = RASTEREXTFROMRASTER(parentRasterDest);

        if (rasDestExt->cube)
        {
            D3DCubeTexture_GetCubeMapSurface((D3DCubeTexture *)rasDestExt->texture,
                                             (D3DCUBEMAP_FACES)rasDestExt->face, 0, &surfaceLevel);
        }
        else
        {
            D3DTexture_GetSurfaceLevel((D3DTexture *)rasDestExt->texture, 0, &surfaceLevel);
        }

        RwXboxSetRenderTarget(surfaceLevel, NULL);

        D3DSurface_Release(surfaceLevel);
    }
    else
    {
        _rwXbEnsureDefaultRenderTarget();
    }

    /*
     * Set the viewport
     */
    viewport.X = RwXbCurrentRasterTarget->nOffsetX;
    viewport.Y = RwXbCurrentRasterTarget->nOffsetY;
    viewport.Width = RwXbCurrentRasterTarget->width;
    viewport.Height = RwXbCurrentRasterTarget->height;
    viewport.MinZ = 0.0f;
    viewport.MaxZ = 1.0f;

    D3DDevice_SetViewport(&viewport);

    _rwXbIm2DRenderSetVertexShader(FALSE, TRUE);
    RwXboxSetCurrentPixelShader(0);

    /* Save the render states */
    RwXboxGetCachedRenderState(D3DRS_ZENABLE, &zEnabled);
    _rwXbGetRenderState(rwRENDERSTATESRCBLEND, (void *)&srcBlend);
    _rwXbGetRenderState(rwRENDERSTATEDESTBLEND, (void *)&dstBlend);
    _rwXbGetRenderState(rwRENDERSTATEVERTEXALPHAENABLE, (void *)&vertexAlpha);
    _rwXbGetRenderState(rwRENDERSTATEFOGENABLE, (void *)&fogEnable);
    _rwXbGetRenderState(rwRENDERSTATECULLMODE, (void *)&cullMode);
    _rwXbGetRenderState(rwRENDERSTATETEXTUREFILTER, (void *)&filterMode);
    _rwXbGetRenderState(rwRENDERSTATETEXTUREADDRESSU, (void *)&addressModeU);
    _rwXbGetRenderState(rwRENDERSTATETEXTUREADDRESSV, (void *)&addressModeV);
    _rwXbGetRenderState(rwRENDERSTATETEXTURERASTER, (void *)&curRaster);

    /* Set the quad's */
    RwXboxSetCachedRenderState(D3DRS_ZENABLE, FALSE);

    if (alpha)
    {
        _rwXbSetRenderState(rwRENDERSTATESRCBLEND, (void *)rwBLENDSRCALPHA);
        _rwXbSetRenderState(rwRENDERSTATEDESTBLEND, (void *)rwBLENDINVSRCALPHA);
    }
    else
    {
        _rwXbSetRenderState(rwRENDERSTATESRCBLEND, (void *)rwBLENDONE);
        _rwXbSetRenderState(rwRENDERSTATEDESTBLEND, (void *)rwBLENDZERO);
    }

    _rwXbSetRenderState(rwRENDERSTATEVERTEXALPHAENABLE, (void *)FALSE);
    _rwXbSetRenderState(rwRENDERSTATEFOGENABLE, (void *)FALSE);
    _rwXbSetRenderState(rwRENDERSTATECULLMODE, (void *)rwCULLMODECULLNONE);
    _rwXbSetRenderState(rwRENDERSTATETEXTUREFILTER,
                        (void *)(scaled ? rwFILTERLINEAR : rwFILTERNEAREST));
    _rwXbSetRenderState(rwRENDERSTATETEXTUREADDRESS, (void *)rwTEXTUREADDRESSCLAMP);
    _rwXbRenderStateTextureRaster(parentRaster);

    _rwXbTextureStageForce(0, D3DTSS_COLOROP, D3DTOP_SELECTARG2);
    _rwXbTextureStageForce(0, D3DTSS_COLORARG2, D3DTA_TEXTURE);
    _rwXbTextureStageForce(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2);
    _rwXbTextureStageForce(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);

    _rwXbFlushCacheBuffer();

    /* The quad */
    pPush = D3DDevice_BeginPush(pushSizeInDWORDs + 5);

    *pPush++ = D3DPUSH_ENCODE(D3DPUSH_SET_BEGIN_END, 1);
    *pPush++ = D3DPT_QUADLIST;
    *pPush++ = D3DPUSH_ENCODE(D3DPUSH_NOINCREMENT_FLAG | D3DPUSH_INLINE_ARRAY, pushSizeInDWORDs);

    quadVerts = (_rwXbQuadVertex *)pPush;

    if (scaled)
    {
        quadVerts[0].x = (RwReal)(RwXbCurrentRasterTarget->nOffsetX + rect->x);
        quadVerts[0].y = (RwReal)(RwXbCurrentRasterTarget->nOffsetY + rect->y);
        quadVerts[0].z = 0.0f;
        quadVerts[0].rhw = 1.0f;

        quadVerts[1].x = (RwReal)(RwXbCurrentRasterTarget->nOffsetX + rect->x);
        quadVerts[1].y = (RwReal)(RwXbCurrentRasterTarget->nOffsetY + rect->y + rect->h);
        quadVerts[1].z = 0.0f;
        quadVerts[1].rhw = 1.0f;

        quadVerts[2].x = (RwReal)(RwXbCurrentRasterTarget->nOffsetX + rect->x + rect->w);
        quadVerts[2].y = (RwReal)(RwXbCurrentRasterTarget->nOffsetY + rect->y + rect->h);
        quadVerts[2].z = 0.0f;
        quadVerts[2].rhw = 1.0f;

        quadVerts[3].x = (RwReal)(RwXbCurrentRasterTarget->nOffsetX + rect->x + rect->w);
        quadVerts[3].y = (RwReal)(RwXbCurrentRasterTarget->nOffsetY + rect->y);
        quadVerts[3].z = 0.0f;
        quadVerts[3].rhw = 1.0f;
    }
    else
    {
        quadVerts[0].x = (RwReal)(RwXbCurrentRasterTarget->nOffsetX + rect->x);
        quadVerts[0].y = (RwReal)(RwXbCurrentRasterTarget->nOffsetY + rect->y);
        quadVerts[0].z = 0.0f;
        quadVerts[0].rhw = 1.0f;

        quadVerts[1].x = (RwReal)(RwXbCurrentRasterTarget->nOffsetX + rect->x);
        quadVerts[1].y = (RwReal)(RwXbCurrentRasterTarget->nOffsetY + rect->y + raster->height);
        quadVerts[1].z = 0.0f;
        quadVerts[1].rhw = 1.0f;

        quadVerts[2].x = (RwReal)(RwXbCurrentRasterTarget->nOffsetX + rect->x + raster->width);
        quadVerts[2].y = (RwReal)(RwXbCurrentRasterTarget->nOffsetY + rect->y + raster->height);
        quadVerts[2].z = 0.0f;
        quadVerts[2].rhw = 1.0f;

        quadVerts[3].x = (RwReal)(RwXbCurrentRasterTarget->nOffsetX + rect->x + raster->width);
        quadVerts[3].y = (RwReal)(RwXbCurrentRasterTarget->nOffsetY + rect->y);
        quadVerts[3].z = 0.0f;
        quadVerts[3].rhw = 1.0f;
    }

    if (raster->cType == rwRASTERTYPENORMAL)
    {
        /* Linear textures take texel coordinates */
        quadVerts[0].u = (RwReal)raster->nOffsetX + 0.5f;
        quadVerts[0].v = (RwReal)raster->nOffsetY + 0.5f;

        quadVerts[1].u = (RwReal)raster->nOffsetX + 0.5f;
        quadVerts[1].v = (RwReal)(raster->nOffsetY + raster->height);

        quadVerts[2].u = (RwReal)(raster->nOffsetX + raster->width);
        quadVerts[2].v = (RwReal)(raster->nOffsetY + raster->height);

        quadVerts[3].u = (RwReal)(raster->nOffsetX + raster->width);
        quadVerts[3].v = (RwReal)raster->nOffsetY + 0.5f;
    }
    else
    {
        quadVerts[0].u = (RwReal)raster->nOffsetX / (RwReal)parentRaster->width;
        quadVerts[0].v = (RwReal)raster->nOffsetY / (RwReal)parentRaster->height;

        quadVerts[1].u = (RwReal)raster->nOffsetX / (RwReal)parentRaster->width;
        quadVerts[1].v = (RwReal)(raster->nOffsetY + raster->height) / (RwReal)parentRaster->height;

        quadVerts[2].u = (RwReal)(raster->nOffsetX + raster->width) / (RwReal)parentRaster->width;
        quadVerts[2].v = (RwReal)(raster->nOffsetY + raster->height) / (RwReal)parentRaster->height;

        quadVerts[3].u = (RwReal)(raster->nOffsetX + raster->width) / (RwReal)parentRaster->width;
        quadVerts[3].v = (RwReal)raster->nOffsetY / (RwReal)parentRaster->height;
    }

    pPush += pushSizeInDWORDs;

    *pPush++ = D3DPUSH_ENCODE(D3DPUSH_SET_BEGIN_END, 1);
    *pPush++ = 0;

    D3DDevice_EndPush(pPush);

    /* Restore the render states */
    RwXboxSetCachedRenderState(D3DRS_ZENABLE, zEnabled);
    _rwXbSetRenderState(rwRENDERSTATESRCBLEND, (void *)srcBlend);
    _rwXbSetRenderState(rwRENDERSTATEDESTBLEND, (void *)dstBlend);
    _rwXbSetRenderState(rwRENDERSTATEVERTEXALPHAENABLE, (void *)vertexAlpha);
    _rwXbSetRenderState(rwRENDERSTATEFOGENABLE, (void *)fogEnable);
    _rwXbSetRenderState(rwRENDERSTATECULLMODE, (void *)cullMode);
    _rwXbSetRenderState(rwRENDERSTATETEXTUREFILTER, (void *)filterMode);
    _rwXbSetRenderState(rwRENDERSTATETEXTUREADDRESSU, (void *)addressModeU);
    _rwXbSetRenderState(rwRENDERSTATETEXTUREADDRESSV, (void *)addressModeV);
    _rwXbRenderStateTextureRaster(curRaster);
}

/****************************************************************************
 XbRasterCopyQuad

 Purpose    : Copies a raster into the current raster target.

 On entry   : Source raster
            : Rect (where image is to be written)
 On exit    : TRUE on success
 */
// match: _XbRasterCopyQuad @ 0x002BAB60
static RwBool
XbRasterCopyQuad(RwRaster *raster, RwRect *rect)
{
    RwRaster               *topRasterSrc;
    RwRaster               *topRasterDest;
    RwXboxRasterExtension  *rasExtSrc;
    RwXboxRasterExtension  *rasExtDest;
    D3DSurface             *surfaceSrc;
    D3DSurface             *surfaceDest;
    HRESULT                 hr;

    /* Get the top level raster as this is the only one with a valid texture */
    topRasterSrc = raster;
    while (RwRasterGetParent(topRasterSrc) != topRasterSrc)
    {
        topRasterSrc = RwRasterGetParent(topRasterSrc);
    };

    rasExtSrc = RASTEREXTFROMRASTER(topRasterSrc);

    if (topRasterSrc->cType != rwRASTERTYPECAMERA)
    {
        if (rasExtSrc->cube)
        {
            D3DCubeTexture_GetCubeMapSurface((D3DCubeTexture *)rasExtSrc->texture,
                                             (D3DCUBEMAP_FACES)rasExtSrc->face, 0, &surfaceSrc);
        }
        else
        {
            D3DTexture_GetSurfaceLevel((D3DTexture *)rasExtSrc->texture, 0, &surfaceSrc);
        }
    }
    else
    {
        hr = D3DDevice_GetRenderTarget(&surfaceSrc);
    }

    /* Get the top level raster as this is the only one with a valid texture */
    topRasterDest = RwXbCurrentRasterTarget;
    while (RwRasterGetParent(topRasterDest) != topRasterDest)
    {
        topRasterDest = RwRasterGetParent(topRasterDest);
    };

    rasExtDest = RASTEREXTFROMRASTER(topRasterDest);

    if (topRasterDest->cType != rwRASTERTYPECAMERA)
    {
        if (rasExtDest->cube)
        {
            D3DCubeTexture_GetCubeMapSurface((D3DCubeTexture *)rasExtDest->texture,
                                             (D3DCUBEMAP_FACES)rasExtDest->face, 0, &surfaceDest);
        }
        else
        {
            D3DTexture_GetSurfaceLevel((D3DTexture *)rasExtDest->texture, 0, &surfaceDest);
        }
    }
    else
    {
        hr = D3DDevice_GetRenderTarget(&surfaceDest);
    }

    if (topRasterSrc->cFormat != topRasterDest->cFormat)
    {
        hr = E_FAIL;
    }
    else
    {
        RECT    rectSrc;
        POINT   pointDest;

        rectSrc.left = raster->nOffsetX;
        rectSrc.top = raster->nOffsetY;
        rectSrc.right = rectSrc.left + raster->width;
        rectSrc.bottom = rectSrc.top + raster->height;

        pointDest.x = RwXbCurrentRasterTarget->nOffsetX + rect->x;
        pointDest.y = RwXbCurrentRasterTarget->nOffsetY + rect->y;

        D3DDevice_CopyRects(surfaceSrc, &rectSrc, 1, surfaceDest, &pointDest);
        hr = D3D_OK;
    }

    D3DSurface_Release(surfaceDest);
    D3DSurface_Release(surfaceSrc);

    return (SUCCEEDED(hr));
}

/****************************************************************************
 XbRasterRenderGeneric

 Purpose    : Renders a raster into the current raster target.

 On entry   : Source raster
            : Rect (where image is to be written)
            : scaled, alpha
 On exit    : TRUE on success
 */
// match: _XbRasterRenderGeneric @ 0x002BAC90
static RwBool
XbRasterRenderGeneric(RwRaster *raster, RwRect *rect, RwBool scaled, RwBool alpha)
{
    switch (RwXbCurrentRasterTarget->cType)
    {
        case rwRASTERTYPENORMAL:
        case rwRASTERTYPETEXTURE:
            switch (raster->cType)
            {
                case rwRASTERTYPENORMAL:
                case rwRASTERTYPECAMERA:
                case rwRASTERTYPETEXTURE:
                case rwRASTERTYPECAMERATEXTURE:
                    if (!scaled)
                    {
                        return XbRasterCopyQuad(raster, rect);
                    }

                    RWERROR((E_RW_DEVICEERROR,
                             RWSTRING("SRC, DST Raster render combination not supported")));
                    return FALSE;

                case rwRASTERTYPEZBUFFER:
                    RWERROR((E_RW_DEVICEERROR,
                             RWSTRING("SRC, DST Raster render combination not supported")));
                    return FALSE;
            }
            break;

        case rwRASTERTYPECAMERA:
        case rwRASTERTYPECAMERATEXTURE:
            switch (raster->cType)
            {
                case rwRASTERTYPENORMAL:
                case rwRASTERTYPETEXTURE:
                case rwRASTERTYPECAMERATEXTURE:
                    XbRasterRenderQuad(raster, rect, scaled, alpha);
                    break;

                case rwRASTERTYPECAMERA:
                    if (!scaled)
                    {
                        return XbRasterCopyQuad(raster, rect);
                    }

                    RWERROR((E_RW_DEVICEERROR,
                             RWSTRING("SRC, DST Raster render combination not supported")));
                    return FALSE;

                case rwRASTERTYPEZBUFFER:
                    RWERROR((E_RW_DEVICEERROR,
                             RWSTRING("SRC, DST Raster render combination not supported")));
                    return FALSE;
            }
            break;

        default:
            RWERROR((E_RW_DEVICEERROR,
                     RWSTRING("SRC, DST Raster render combination not supported")));
            return FALSE;
    }

    return TRUE;
}

// match: __rwXbRasterRender @ 0x002BADD0
RwBool
_rwXbRasterRender(void *rasterIn, void *rectIn, RwInt32 flags __RWUNUSED__)
{
    return XbRasterRenderGeneric((RwRaster *)rasterIn, (RwRect *)rectIn, FALSE, TRUE);
}

// match: __rwXbRasterRenderFast @ 0x002BADF0
RwBool
_rwXbRasterRenderFast(void *rasterIn, void *rectIn, RwInt32 flags __RWUNUSED__)
{
    return XbRasterRenderGeneric((RwRaster *)rasterIn, (RwRect *)rectIn, FALSE, FALSE);
}

// match: __rwXbRasterRenderScaled @ 0x002BAE10
RwBool
_rwXbRasterRenderScaled(void *rasterIn, void *rectIn, RwInt32 flags __RWUNUSED__)
{
    return XbRasterRenderGeneric((RwRaster *)rasterIn, (RwRect *)rectIn, TRUE, TRUE);
}

/****************************************************************************
 _rwXbRasterClearGeneric

 Purpose    : Clears a rectangle of the current raster target.

 On entry   : rect, packedColor
 On exit    : TRUE on success
 */
// match: __rwXbRasterClearGeneric @ 0x002BAE30
RwBool
_rwXbRasterClearGeneric(RwRect *rect, RwInt32 packedColor)
{
    switch (RwXbCurrentRasterTarget->cType)
    {
        case rwRASTERTYPECAMERA:
            {
                D3DVIEWPORT8    viewport;

                viewport.X = RwXbCurrentRasterTarget->nOffsetX + rect->x;
                viewport.Y = RwXbCurrentRasterTarget->nOffsetY + rect->y;
                viewport.Width = rect->w;
                viewport.Height = rect->h;
                viewport.MinZ = 0.0f;
                viewport.MaxZ = 1.0f;

                D3DDevice_SetViewport(&viewport);

                D3DDevice_Clear(0, NULL, D3DCLEAR_TARGET, packedColor, 1.0f, 0);
            }
            break;

        case rwRASTERTYPEZBUFFER:
            {
                D3DVIEWPORT8    viewport;

                viewport.X = RwXbCurrentRasterTarget->nOffsetX + rect->x;
                viewport.Y = RwXbCurrentRasterTarget->nOffsetY + rect->y;
                viewport.Width = rect->w;
                viewport.Height = rect->h;
                viewport.MinZ = 0.0f;
                viewport.MaxZ = 1.0f;

                D3DDevice_SetViewport(&viewport);

                D3DDevice_Clear(0, NULL, D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
            }
            break;

        case rwRASTERTYPENORMAL:
        case rwRASTERTYPETEXTURE:
        case rwRASTERTYPECAMERATEXTURE:
            {
                RwBool  rasterLocked = FALSE;

                if (RwRasterGetParent(RwXbCurrentRasterTarget) != RwXbCurrentRasterTarget ||
                    rect->x != 0 || rect->y != 0 ||
                    RwXbCurrentRasterTarget->width != rect->w ||
                    RwXbCurrentRasterTarget->height != rect->h)
                {
                    RWERROR((E_RW_DEVICEERROR,
                             RWSTRING("Only the entire raster can be cleared")));
                    return FALSE;
                }

                if (!(RwXbCurrentRasterTarget->privateFlags & rwRASTERPIXELLOCKEDWRITE))
                {
                    rasterLocked = TRUE;
                    RwRasterLock(RwXbCurrentRasterTarget, 0,
                                 rwRASTERLOCKWRITE | rwRASTERLOCKRAW);
                }

                if (!packedColor)
                {
                    memset(RwXbCurrentRasterTarget->cpPixels, 0,
                           RwXbCurrentRasterTarget->height * RwXbCurrentRasterTarget->stride);
                }
                else
                {
                    switch (RwXbCurrentRasterTarget->depth)
                    {
                        case 4:
                        case 8:
                            memset(RwXbCurrentRasterTarget->cpPixels, (RwUInt8)packedColor,
                                   RwXbCurrentRasterTarget->height *
                                   RwXbCurrentRasterTarget->stride);
                            break;

                        case 16:
                            {
                                RwUInt16    col = (RwUInt16)packedColor;
                                RwInt32     y;

                                for (y = 0; y < RwXbCurrentRasterTarget->height; y++)
                                {
                                    RwUInt16   *pixel;
                                    RwInt32     x;

                                    pixel = (RwUInt16 *)(RwXbCurrentRasterTarget->cpPixels +
                                                         y * RwXbCurrentRasterTarget->stride);
                                    for (x = 0; x < RwXbCurrentRasterTarget->width; x++)
                                    {
                                        *pixel++ = col;
                                    }
                                }
                            }
                            break;

                        case 24:
                        case 32:
                            {
                                RwInt32     i;

                                for (i = 0; i < RwXbCurrentRasterTarget->height; i++)
                                {
                                    RwUInt32   *pixel;
                                    RwInt32     j;

                                    pixel = (RwUInt32 *)(RwXbCurrentRasterTarget->cpPixels +
                                                         i * RwXbCurrentRasterTarget->stride);
                                    for (j = 0; j < RwXbCurrentRasterTarget->width; j++)
                                    {
                                        *pixel++ = packedColor;
                                    }
                                }
                            }
                            break;

                        default:
                            RWERROR((E_RW_INVRASTERDEPTH));
                            break;
                    }
                }

                if (rasterLocked)
                {
                    RwRasterUnlock(RwXbCurrentRasterTarget);
                }
            }
            break;

        default:
            RWERROR((E_RW_INVRASTERFORMAT));
            return FALSE;
    }

    return TRUE;
}

// match: __rwXbRasterClearRect @ 0x002BB150
RwBool
_rwXbRasterClearRect(void *unused1 __RWUNUSED__, void *rectIn, RwInt32 packedColor)
{
    return _rwXbRasterClearGeneric((RwRect *)rectIn, packedColor);
}

// match: __rwXbRasterClear @ 0x002BB170
RwBool
_rwXbRasterClear(void *unused1 __RWUNUSED__, void *unused2 __RWUNUSED__, RwInt32 packedColor)
{
    RwRect  rect;

    rect.x = 0;
    rect.y = 0;
    rect.w = RwXbCurrentRasterTarget->width;
    rect.h = RwXbCurrentRasterTarget->height;

    return _rwXbRasterClearGeneric(&rect, packedColor);
}

// match: __rwXbSetRasterContext @ 0x002BB1B0
RwBool
_rwXbSetRasterContext(void *unused1 __RWUNUSED__, void *rasIn, RwInt32 unused3 __RWUNUSED__)
{
    RwXbCurrentRasterTarget = (RwRaster *)rasIn;

    return TRUE;
}
