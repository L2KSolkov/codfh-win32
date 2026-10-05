/*
 * codfh-match: RenderWare 3.6's Xbox driver render states (driver/xbox/xbrendst.c),
 * which the 3.7.2 tree does not have. Written from the image; the names are
 * the image's, the conversion tables' by analogy with their neighbours
 * (_RwXbAddressConvTable, _RwXbFilterModeConvTable).
 */

#include <xtl.h>

#include "batypes.h"
#include "balibtyp.h"
#include "badebug.h"
#include "baraster.h"
#include "batextur.h"
#include "bacamera.h"
#include "barwtyp.h"

#include "xbdevice.h"
#include "xbraster.h"
#include "xbmemory.h"
#include "xbcache.h"
#include "xbrendst.h"

/* RenderWare 3.6's RCS id string, which the image keeps (the 3.7.2 tree has none) */
static const char rcsid[] = "@@@@(#)$Id: //RenderWare/RW36Active/rwsdk/driver/xbox/xbrendst.c#1 $";

_rwXbStateCache RwXbStateCache;

/* The texture stage the anisotropic filter goes to. */
static RwInt32 XboxAnisotTextureOffset;

/* RenderWare's modes as D3D's, in the image's order (0x4167A0 on). */
const DWORD _RwXbShadeModeConvTable[3] =
{
    0,
    D3DSHADE_FLAT,
    D3DSHADE_GOURAUD
};

const DWORD _RwXbFogConvTable[4] =
{
    0,
    D3DFOG_LINEAR,
    D3DFOG_EXP,
    D3DFOG_EXP2
};

const DWORD _RwXbAddressConvTable[5] =
{
    0,
    D3DTADDRESS_WRAP,
    D3DTADDRESS_MIRROR,
    D3DTADDRESS_CLAMP,
    D3DTADDRESS_BORDER
};

const DWORD _RwXbBlendConvTable[12] =
{
    0,
    D3DBLEND_ZERO,
    D3DBLEND_ONE,
    D3DBLEND_SRCCOLOR,
    D3DBLEND_INVSRCCOLOR,
    D3DBLEND_SRCALPHA,
    D3DBLEND_INVSRCALPHA,
    D3DBLEND_DESTALPHA,
    D3DBLEND_INVDESTALPHA,
    D3DBLEND_DESTCOLOR,
    D3DBLEND_INVDESTCOLOR,
    D3DBLEND_SRCALPHASAT
};

typedef struct _rwXbFilterMode _rwXbFilterMode;
struct _rwXbFilterMode
{
    DWORD   minmag;
    DWORD   mip;
};

/* The filter modes, then (from 8) the anisotropic ones. */
const _rwXbFilterMode _RwXbFilterModeConvTable[15] =
{
    { D3DTEXF_NONE, D3DTEXF_NONE },
    { D3DTEXF_POINT, D3DTEXF_NONE },
    { D3DTEXF_LINEAR, D3DTEXF_NONE },
    { D3DTEXF_POINT, D3DTEXF_POINT },
    { D3DTEXF_LINEAR, D3DTEXF_POINT },
    { D3DTEXF_POINT, D3DTEXF_LINEAR },
    { D3DTEXF_LINEAR, D3DTEXF_LINEAR },
    { D3DTEXF_NONE, D3DTEXF_NONE },
    { D3DTEXF_NONE, D3DTEXF_NONE },
    { D3DTEXF_ANISOTROPIC, D3DTEXF_NONE },
    { D3DTEXF_ANISOTROPIC, D3DTEXF_NONE },
    { D3DTEXF_ANISOTROPIC, D3DTEXF_POINT },
    { D3DTEXF_ANISOTROPIC, D3DTEXF_POINT },
    { D3DTEXF_ANISOTROPIC, D3DTEXF_LINEAR },
    { D3DTEXF_ANISOTROPIC, D3DTEXF_LINEAR }
};

const DWORD _RwXbCullModeConvTable[4] =
{
    0,
    D3DCULL_NONE,
    D3DCULL_CW,
    D3DCULL_CCW
};

const DWORD _RwXbStencilOpConvTable[9] =
{
    0,
    D3DSTENCILOP_KEEP,
    D3DSTENCILOP_ZERO,
    D3DSTENCILOP_REPLACE,
    D3DSTENCILOP_INCRSAT,
    D3DSTENCILOP_DECRSAT,
    D3DSTENCILOP_INVERT,
    D3DSTENCILOP_INCR,
    D3DSTENCILOP_DECR
};

const DWORD _RwXbCmpFuncConvTable[9] =
{
    0,
    D3DCMP_NEVER,
    D3DCMP_LESS,
    D3DCMP_EQUAL,
    D3DCMP_LESSEQUAL,
    D3DCMP_GREATER,
    D3DCMP_NOTEQUAL,
    D3DCMP_GREATEREQUAL,
    D3DCMP_ALWAYS
};

#define FLOATASDWORD(fvariable) (*((const DWORD *)&(fvariable)))

#define CONSTTEXTUREGETANISOT(tex) \
    (*((const RwUInt8 *)(((const RwUInt8 *)tex) + XboxAnisotTextureOffset)))

typedef union XbUnionParam XbUnionParam;
union XbUnionParam
{
    RwBlendFunction     BlendFunction;
    RwBool              Bool;
    RwCullMode          CullMode;
    RwFogType           FogType;
    RwInt32             Int32;
    RwRaster           *RasterPtr;
    RwReal             *RealPtr;
    RwShadeMode         ShadeMode;
    RwStencilFunction   StencilFunction;
    RwStencilOperation  StencilOperation;
    RwTextureAddressMode TextureAddressMode;
    RwTextureFilterMode TextureFilterMode;
    RwUInt32            UInt32;
    void               *VoidPtr;
    RwAlphaTestFunction AlphaTestFunction;
};

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: _rcsid @ 0x00416758
// match: __RwXbShadeModeConvTable @ 0x004167A0
// match: __RwXbFogConvTable @ 0x004167AC
// match: __RwXbAddressConvTable @ 0x004167BC
// match: __RwXbBlendConvTable @ 0x004167D0
// match: __RwXbFilterModeConvTable @ 0x00416800
// match: __RwXbCullModeConvTable @ 0x00416878
// match: __RwXbStencilOpConvTable @ 0x00416888
// match: __RwXbCmpFuncConvTable @ 0x004168AC

// match: __rwXbRenderStateOpen @ 0x002AF390

void
_rwXbRenderStateOpen(void)
{
    RwXbStateCache.fogType = rwFOGTYPELINEAR;
    RwXbStateCache.shadeMode = rwSHADEMODEGOURAUD;
    RwXbStateCache.zTestEnable = TRUE;
    RwXbStateCache.zWriteEnable = TRUE;
    RwXbStateCache.stencilFailOp = rwSTENCILOPERATIONKEEP;
    RwXbStateCache.stencilZFailOp = rwSTENCILOPERATIONKEEP;
    RwXbStateCache.stencilPassOp = rwSTENCILOPERATIONKEEP;
    RwXbStateCache.stencilFunction = rwSTENCILFUNCTIONALWAYS;
    RwXbStateCache.curTexRaster = NULL;
    RwXbStateCache.filterMode = rwFILTERLINEAR;
    RwXbStateCache.maxAnisotropy = 1;
    RwXbStateCache.texAddressU = rwTEXTUREADDRESSWRAP;
    RwXbStateCache.texAddressV = rwTEXTUREADDRESSWRAP;
    RwXbStateCache.srcBlend = rwBLENDSRCALPHA;
    RwXbStateCache.dstBlend = rwBLENDINVSRCALPHA;
    RwXbStateCache.vertexAlphaBlendEnable = FALSE;
    RwXbStateCache.textureAlphaBlendEnable = FALSE;
    RwXbStateCache.cullMode = rwCULLMODECULLBACK;

    RwXbStateCache.vertexShader = 0;
    D3DDevice_SetVertexShader(0);
    RwXbStateCache.pixelShader = 0;
    D3DDevice_SetPixelShader(0);

    RwXbStateCache.alphaTestEnable = TRUE;
    RwXbStateCache.alphaTestFunction = rwALPHATESTFUNCTIONGREATER;

    _rwXbCacheInit();
}

// match: __rwXbGetRenderState @ 0x002AF450
RwBool
_rwXbGetRenderState(RwRenderState nState, void *param)
{
    switch (nState)
    {
        case rwRENDERSTATEFOGENABLE:
            *(RwBool *)param = _RwXbRenderStateCacheBuffer[D3DRS_FOGENABLE];
            return TRUE;

        case rwRENDERSTATEFOGTYPE:
            *(RwFogType *)param = RwXbStateCache.fogType;
            return TRUE;

        case rwRENDERSTATEFOGCOLOR:
            *(RwUInt32 *)param = _RwXbRenderStateCacheBuffer[D3DRS_FOGCOLOR];
            return TRUE;

        case rwRENDERSTATEFOGDENSITY:
            *(DWORD *)param = _RwXbRenderStateCacheBuffer[D3DRS_FOGDENSITY];
            return TRUE;

        case rwRENDERSTATETEXTUREADDRESS:
            if (RwXbStateCache.texAddressU == RwXbStateCache.texAddressV)
            {
                *(RwTextureAddressMode *)param = RwXbStateCache.texAddressU;
                return TRUE;
            }
            break;

        case rwRENDERSTATETEXTUREADDRESSU:
            *(RwTextureAddressMode *)param = RwXbStateCache.texAddressU;
            return TRUE;

        case rwRENDERSTATETEXTUREADDRESSV:
            *(RwTextureAddressMode *)param = RwXbStateCache.texAddressV;
            return TRUE;

        case rwRENDERSTATETEXTUREFILTER:
            *(RwTextureFilterMode *)param = RwXbStateCache.filterMode;
            return TRUE;

        case rwRENDERSTATETEXTURERASTER:
            *(RwRaster **)param = RwXbStateCache.curTexRaster;
            return TRUE;

        case rwRENDERSTATEZWRITEENABLE:
            *(RwBool *)param = RwXbStateCache.zWriteEnable;
            return TRUE;

        case rwRENDERSTATEZTESTENABLE:
            *(RwBool *)param = RwXbStateCache.zTestEnable;
            return TRUE;

        case rwRENDERSTATESRCBLEND:
            *(RwBlendFunction *)param = RwXbStateCache.srcBlend;
            return TRUE;

        case rwRENDERSTATEDESTBLEND:
            *(RwBlendFunction *)param = RwXbStateCache.dstBlend;
            return TRUE;

        case rwRENDERSTATESHADEMODE:
            *(RwShadeMode *)param = RwXbStateCache.shadeMode;
            return TRUE;

        case rwRENDERSTATEVERTEXALPHAENABLE:
            *(RwBool *)param = RwXbStateCache.vertexAlphaBlendEnable;
            return TRUE;

        case rwRENDERSTATEBORDERCOLOR:
            *(RwUInt32 *)param = _RwXbTextureStageCacheBuffer[D3DTSS_BORDERCOLOR][0];
            return TRUE;

        case rwRENDERSTATETEXTUREPERSPECTIVE:
            *(RwBool *)param = TRUE;
            return TRUE;

        case rwRENDERSTATECULLMODE:
            *(RwCullMode *)param = RwXbStateCache.cullMode;
            return TRUE;

        case rwRENDERSTATESTENCILENABLE:
            *(RwBool *)param = _RwXbRenderStateCacheBuffer[D3DRS_STENCILENABLE];
            break;

        case rwRENDERSTATESTENCILFUNCTIONREF:
            *(RwInt32 *)param = _RwXbRenderStateCacheBuffer[D3DRS_STENCILREF];
            break;

        case rwRENDERSTATESTENCILFUNCTIONMASK:
            *(RwInt32 *)param = _RwXbRenderStateCacheBuffer[D3DRS_STENCILMASK];
            break;

        case rwRENDERSTATESTENCILFUNCTIONWRITEMASK:
            *(RwInt32 *)param = _RwXbRenderStateCacheBuffer[D3DRS_STENCILWRITEMASK];
            break;

        case rwRENDERSTATESTENCILFAIL:
            *(RwStencilOperation *)param = RwXbStateCache.stencilFailOp;
            break;

        case rwRENDERSTATESTENCILZFAIL:
            *(RwStencilOperation *)param = RwXbStateCache.stencilZFailOp;
            break;

        case rwRENDERSTATESTENCILPASS:
            *(RwStencilOperation *)param = RwXbStateCache.stencilPassOp;
            break;

        case rwRENDERSTATESTENCILFUNCTION:
            *(RwStencilFunction *)param = RwXbStateCache.stencilFunction;
            break;

        case rwRENDERSTATEALPHATESTFUNCTION:
            *(RwAlphaTestFunction *)param = RwXbStateCache.alphaTestFunction;
            return TRUE;

        case rwRENDERSTATEALPHATESTFUNCTIONREF:
            *(RwUInt32 *)param = _RwXbRenderStateCacheBuffer[D3DRS_ALPHAREF];
            return TRUE;

        default:
            break;
    }

    return FALSE;
}

// match: _XbRenderStateFogType @ 0x002AF6C0
static RwBool
XbRenderStateFogType(RwFogType fogType)
{
    if (fogType != RwXbStateCache.fogType)
    {
        RwXboxSetCachedRenderState(D3DRS_FOGTABLEMODE, _RwXbFogConvTable[fogType]);
        RwXbStateCache.fogType = fogType;
    }

    if (fogType == rwFOGTYPELINEAR)
    {
        const RwReal    fogPlane = dgGGlobals.curCamera->fogPlane;
        const RwReal    farPlane = dgGGlobals.curCamera->farPlane;

        RwXboxSetCachedRenderState(D3DRS_FOGSTART, FLOATASDWORD(fogPlane));
        RwXboxSetCachedRenderState(D3DRS_FOGEND, FLOATASDWORD(farPlane));
    }

    return TRUE;
}

// match: _XbRenderStateTextureAddress @ 0x002AF7A0
static RwBool
XbRenderStateTextureAddress(RwUInt32 stage, RwTextureAddressMode addressMode)
{
    RwXboxSetCachedTextureStageState(stage, D3DTSS_ADDRESSU, _RwXbAddressConvTable[addressMode]);
    RwXboxSetCachedTextureStageState(stage, D3DTSS_ADDRESSV, _RwXbAddressConvTable[addressMode]);

    if (stage == 0)
    {
        RwXbStateCache.texAddressU = addressMode;
        RwXbStateCache.texAddressV = addressMode;
    }

    return TRUE;
}

// match: _XbRenderStateTextureFilter @ 0x002AF840
static RwBool
XbRenderStateTextureFilter(RwUInt32 stage, RwTextureFilterMode filterMode)
{
    RwXboxSetCachedTextureStageState(stage, D3DTSS_MINFILTER, _RwXbFilterModeConvTable[filterMode].minmag);
    RwXboxSetCachedTextureStageState(stage, D3DTSS_MAGFILTER, _RwXbFilterModeConvTable[filterMode].minmag);
    RwXboxSetCachedTextureStageState(stage, D3DTSS_MIPFILTER, _RwXbFilterModeConvTable[filterMode].mip);

    if (stage == 0)
    {
        RwXbStateCache.filterMode = filterMode;
    }

    return TRUE;
}

// match: _XbRenderStateTextureStageRaster @ 0x002AF910
static void
XbRenderStateTextureStageRaster(RwRaster *raster, RwUInt32 stage)
{
    if (stage == 0)
    {
        if (raster != RwXbStateCache.curTexRaster)
        {
            if (raster)
            {
                RwXboxRasterExtension  *rasExt = RASTEREXTFROMRASTER(raster);

                _RwXbTextureCacheBuffer[0] = rasExt->texture;

                if (rasExt->palette)
                {
                    D3DDevice_SetPalette(0, rasExt->palette);
                }

                if (rasExt->alpha)
                {
                    /* Enable alpha blending if the texture has alpha */
                    if (!RwXbStateCache.textureAlphaBlendEnable)
                    {
                        if (!RwXbStateCache.vertexAlphaBlendEnable)
                        {
                            RwXboxSetCachedRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
                            RwXboxSetCachedRenderState(D3DRS_ALPHATESTENABLE,
                                                       RwXbStateCache.alphaTestEnable);
                        }

                        RwXbStateCache.textureAlphaBlendEnable = TRUE;
                    }
                }
                else
                {
                    if (RwXbStateCache.textureAlphaBlendEnable)
                    {
                        /* Disable alpha blending if it has not been explicitly set */
                        if (!RwXbStateCache.vertexAlphaBlendEnable)
                        {
                            RwXboxSetCachedRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
                            RwXboxSetCachedRenderState(D3DRS_ALPHATESTENABLE, FALSE);
                        }

                        RwXbStateCache.textureAlphaBlendEnable = FALSE;
                    }
                }
            }
            else
            {
                _RwXbTextureCacheBuffer[0] = NULL;

                if (RwXbStateCache.textureAlphaBlendEnable)
                {
                    if (!RwXbStateCache.vertexAlphaBlendEnable)
                    {
                        RwXboxSetCachedRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
                        RwXboxSetCachedRenderState(D3DRS_ALPHATESTENABLE, FALSE);
                    }

                    RwXbStateCache.textureAlphaBlendEnable = FALSE;
                }
            }

            RwXbStateCache.curTexRaster = raster;
        }
    }
    else
    {
        if (raster)
        {
            RwXboxRasterExtension  *rasExt = RASTEREXTFROMRASTER(raster);

            _RwXbTextureCacheBuffer[stage] = rasExt->texture;

            if (rasExt->palette)
            {
                D3DDevice_SetPalette(stage, rasExt->palette);
            }
        }
        else
        {
            _RwXbTextureCacheBuffer[stage] = NULL;
        }
    }
}

// match: __rwXboxSetTextureAnisotropyOffset @ 0x002AFA90
void
_rwXboxSetTextureAnisotropyOffset(RwInt32 offset)
{
    XboxAnisotTextureOffset = offset;
}

// match: _RwXboxRenderStateSetTexture @ 0x002AFAA0
void
RwXboxRenderStateSetTexture(RwTexture *texture, RwUInt32 stage)
{
    if (texture)
    {
        RwTextureAddressMode    addressingU = RwTextureGetAddressingU(texture);
        RwTextureAddressMode    addressingV = RwTextureGetAddressingV(texture);
        RwTextureFilterMode     filtering;
        RwInt32                 anisotropy;

        if (XboxAnisotTextureOffset > 0)
        {
            anisotropy = CONSTTEXTUREGETANISOT(texture);
            filtering = (RwTextureFilterMode)(RwTextureGetFilterMode(texture) |
                                              ((anisotropy > 1) << 3));
        }
        else
        {
            anisotropy = 1;
            filtering = RwTextureGetFilterMode(texture);
        }

        if (stage == 0)
        {
            if (addressingU != RwXbStateCache.texAddressU)
            {
                RwXboxSetCachedTextureStageState(0, D3DTSS_ADDRESSU, _RwXbAddressConvTable[addressingU]);
                RwXbStateCache.texAddressU = addressingU;
            }

            if (addressingV != RwXbStateCache.texAddressV)
            {
                RwXboxSetCachedTextureStageState(0, D3DTSS_ADDRESSV, _RwXbAddressConvTable[addressingV]);
                RwXbStateCache.texAddressV = addressingV;
            }

            if (filtering != RwXbStateCache.filterMode)
            {
                RwXboxSetCachedTextureStageState(0, D3DTSS_MINFILTER, _RwXbFilterModeConvTable[filtering].minmag);
                RwXboxSetCachedTextureStageState(0, D3DTSS_MAGFILTER, _RwXbFilterModeConvTable[filtering].minmag);
                RwXboxSetCachedTextureStageState(0, D3DTSS_MIPFILTER, _RwXbFilterModeConvTable[filtering].mip);
                RwXbStateCache.filterMode = filtering;
            }

            if (anisotropy != RwXbStateCache.maxAnisotropy)
            {
                RwXboxSetCachedTextureStageState(0, D3DTSS_MAXANISOTROPY, anisotropy);
                RwXbStateCache.maxAnisotropy = anisotropy;
            }

            XbRenderStateTextureStageRaster(texture->raster, 0);
        }
        else
        {
            RwXboxSetCachedTextureStageState(stage, D3DTSS_ADDRESSU, _RwXbAddressConvTable[addressingU]);
            RwXboxSetCachedTextureStageState(stage, D3DTSS_ADDRESSV, _RwXbAddressConvTable[addressingV]);
            RwXboxSetCachedTextureStageState(stage, D3DTSS_MINFILTER, _RwXbFilterModeConvTable[filtering].minmag);
            RwXboxSetCachedTextureStageState(stage, D3DTSS_MAGFILTER, _RwXbFilterModeConvTable[filtering].minmag);
            RwXboxSetCachedTextureStageState(stage, D3DTSS_MIPFILTER, _RwXbFilterModeConvTable[filtering].mip);
            RwXboxSetCachedTextureStageState(stage, D3DTSS_MAXANISOTROPY, anisotropy);

            XbRenderStateTextureStageRaster(texture->raster, stage);
        }
    }
    else
    {
        if (stage == 0)
        {
            if (RwXbStateCache.curTexRaster)
            {
                _RwXbTextureCacheBuffer[0] = NULL;

                if (RwXbStateCache.textureAlphaBlendEnable)
                {
                    if (!RwXbStateCache.vertexAlphaBlendEnable)
                    {
                        RwXboxSetCachedRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
                        RwXboxSetCachedRenderState(D3DRS_ALPHATESTENABLE, FALSE);
                    }

                    RwXbStateCache.textureAlphaBlendEnable = FALSE;
                }

                RwXbStateCache.curTexRaster = NULL;
            }
        }
        else
        {
            _RwXbTextureCacheBuffer[stage] = NULL;
        }
    }
}

// match: __rwXbRenderStateTextureRaster @ 0x002AFEA0
RwBool
_rwXbRenderStateTextureRaster(RwRaster *raster)
{
    XbRenderStateTextureStageRaster(raster, 0);

    return TRUE;
}

// match: __rwXbRenderStateTextureRasterPurge @ 0x002AFEC0
void
_rwXbRenderStateTextureRasterPurge(RwRaster *raster)
{
    RwRaster    *current = RwXbStateCache.curTexRaster;

    if (current == raster && current)
    {
        _RwXbTextureCacheBuffer[0] = NULL;

        if (RwXbStateCache.textureAlphaBlendEnable)
        {
            if (!RwXbStateCache.vertexAlphaBlendEnable)
            {
                RwXboxSetCachedRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
                RwXboxSetCachedRenderState(D3DRS_ALPHATESTENABLE, FALSE);
            }

            RwXbStateCache.textureAlphaBlendEnable = FALSE;
        }

        RwXbStateCache.curTexRaster = NULL;
    }
}

// match: _XbRenderStateZTestEnable @ 0x002AFF60
static RwBool
XbRenderStateZTestEnable(RwBool enable)
{
    if (enable)
    {
        if (!RwXbStateCache.zTestEnable)
        {
            RwXbStateCache.zTestEnable = TRUE;

            if (!RwXbStateCache.zWriteEnable)
            {
                RwXboxSetCachedRenderState(D3DRS_ZENABLE, TRUE);
            }

            RwXboxSetCachedRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
        }
    }
    else
    {
        if (RwXbStateCache.zTestEnable)
        {
            RwXbStateCache.zTestEnable = FALSE;

            if (!RwXbStateCache.zWriteEnable)
            {
                RwXboxSetCachedRenderState(D3DRS_ZENABLE, FALSE);
            }

            RwXboxSetCachedRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
        }
    }

    return TRUE;
}

// match: _XbRenderStateZWriteEnable @ 0x002B0060
static RwBool
XbRenderStateZWriteEnable(RwBool enable)
{
    if (enable)
    {
        if (!RwXbStateCache.zWriteEnable)
        {
            RwXbStateCache.zWriteEnable = TRUE;

            if (!RwXbStateCache.zTestEnable)
            {
                RwXboxSetCachedRenderState(D3DRS_ZENABLE, TRUE);
            }

            RwXboxSetCachedRenderState(D3DRS_ZWRITEENABLE, TRUE);
        }
    }
    else
    {
        if (RwXbStateCache.zWriteEnable)
        {
            RwXbStateCache.zWriteEnable = FALSE;

            if (!RwXbStateCache.zTestEnable)
            {
                RwXboxSetCachedRenderState(D3DRS_ZENABLE, FALSE);
            }

            RwXboxSetCachedRenderState(D3DRS_ZWRITEENABLE, FALSE);
        }
    }

    return TRUE;
}

// match: _XbRenderStateSrcBlend @ 0x002B0150
static RwBool
XbRenderStateSrcBlend(RwBlendFunction srcBlend)
{
    if (srcBlend != RwXbStateCache.srcBlend)
    {
        RwXboxSetCachedRenderState(D3DRS_SRCBLEND, _RwXbBlendConvTable[srcBlend]);
        RwXbStateCache.srcBlend = srcBlend;
    }

    return TRUE;
}

// match: _XbRenderStateDestBlend @ 0x002B01A0
static RwBool
XbRenderStateDestBlend(RwBlendFunction dstBlend)
{
    if (dstBlend != RwXbStateCache.dstBlend)
    {
        RwXboxSetCachedRenderState(D3DRS_DESTBLEND, _RwXbBlendConvTable[dstBlend]);
        RwXbStateCache.dstBlend = dstBlend;
    }

    return TRUE;
}

// match: _XbRenderStateShadeMode @ 0x002B01F0
static RwBool
XbRenderStateShadeMode(RwShadeMode shadeMode)
{
    if (shadeMode != RwXbStateCache.shadeMode)
    {
        RwXboxSetCachedRenderState(D3DRS_SHADEMODE, _RwXbShadeModeConvTable[shadeMode]);
        RwXbStateCache.shadeMode = shadeMode;
    }

    return TRUE;
}

// match: _XbRenderStateVertexAlphaEnable @ 0x002B0240
static RwBool
XbRenderStateVertexAlphaEnable(RwBool enable)
{
    if (enable)
    {
        if (!RwXbStateCache.vertexAlphaBlendEnable)
        {
            if (!RwXbStateCache.textureAlphaBlendEnable)
            {
                RwXboxSetCachedRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
                RwXboxSetCachedRenderState(D3DRS_ALPHATESTENABLE,
                                           RwXbStateCache.alphaTestEnable);
            }

            RwXbStateCache.vertexAlphaBlendEnable = TRUE;
        }
    }
    else
    {
        if (RwXbStateCache.vertexAlphaBlendEnable)
        {
            if (!RwXbStateCache.textureAlphaBlendEnable)
            {
                RwXboxSetCachedRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
                RwXboxSetCachedRenderState(D3DRS_ALPHATESTENABLE, FALSE);
            }

            RwXbStateCache.vertexAlphaBlendEnable = FALSE;
        }
    }

    return TRUE;
}

// match: _XbRenderStateCullMode @ 0x002B0330
static RwBool
XbRenderStateCullMode(RwCullMode cullMode)
{
    if (cullMode != RwXbStateCache.cullMode)
    {
        RwXboxSetCachedRenderState(D3DRS_CULLMODE, _RwXbCullModeConvTable[cullMode]);
        RwXbStateCache.cullMode = cullMode;
    }

    return TRUE;
}

// match: __rwXbRenderStateStencilFail @ 0x002B0380
RwBool
_rwXbRenderStateStencilFail(RwStencilOperation operation)
{
    if (operation != RwXbStateCache.stencilFailOp)
    {
        RwXboxSetCachedRenderState(D3DRS_STENCILFAIL, _RwXbStencilOpConvTable[operation]);
        RwXbStateCache.stencilFailOp = operation;
    }

    return TRUE;
}

// match: __rwXbRenderStateStencilZFail @ 0x002B03D0
RwBool
_rwXbRenderStateStencilZFail(RwStencilOperation operation)
{
    if (operation != RwXbStateCache.stencilZFailOp)
    {
        RwXboxSetCachedRenderState(D3DRS_STENCILZFAIL, _RwXbStencilOpConvTable[operation]);
        RwXbStateCache.stencilZFailOp = operation;
    }

    return TRUE;
}

// match: __rwXbRenderStateStencilPass @ 0x002B0420
RwBool
_rwXbRenderStateStencilPass(RwStencilOperation operation)
{
    if (operation != RwXbStateCache.stencilPassOp)
    {
        RwXboxSetCachedRenderState(D3DRS_STENCILPASS, _RwXbStencilOpConvTable[operation]);
        RwXbStateCache.stencilPassOp = operation;
    }

    return TRUE;
}

// match: __rwXbRenderStateStencilFunction @ 0x002B0470
RwBool
_rwXbRenderStateStencilFunction(RwStencilFunction function)
{
    if (function != RwXbStateCache.stencilFunction)
    {
        RwXboxSetCachedRenderState(D3DRS_STENCILFUNC, _RwXbCmpFuncConvTable[function]);
        RwXbStateCache.stencilFunction = function;
    }

    return TRUE;
}

// match: __rwXbSetRenderState @ 0x002B04C0
RwBool
_rwXbSetRenderState(RwRenderState nState, void *param)
{
    RwBool          result = TRUE;
    XbUnionParam    uparam;

    uparam.VoidPtr = param;

    switch (nState)
    {
        case rwRENDERSTATEFOGENABLE:
            RwXboxSetCachedRenderState(D3DRS_FOGENABLE, uparam.Bool);
            result = TRUE;
            break;

        case rwRENDERSTATEFOGCOLOR:
            RwXboxSetCachedRenderState(D3DRS_FOGCOLOR, uparam.UInt32);
            result = TRUE;
            break;

        case rwRENDERSTATEFOGTYPE:
            result = XbRenderStateFogType(uparam.FogType);
            break;

        case rwRENDERSTATEFOGDENSITY:
            RwXboxSetCachedRenderState(D3DRS_FOGDENSITY, FLOATASDWORD(*uparam.RealPtr));
            result = TRUE;
            break;

        case rwRENDERSTATETEXTUREADDRESS:
            result = XbRenderStateTextureAddress(0, uparam.TextureAddressMode);
            break;

        case rwRENDERSTATETEXTUREADDRESSU:
            RwXboxSetCachedTextureStageState(0, D3DTSS_ADDRESSU,
                                             _RwXbAddressConvTable[uparam.TextureAddressMode]);
            RwXbStateCache.texAddressU = uparam.TextureAddressMode;
            result = TRUE;
            break;

        case rwRENDERSTATETEXTUREADDRESSV:
            RwXboxSetCachedTextureStageState(0, D3DTSS_ADDRESSV,
                                             _RwXbAddressConvTable[uparam.TextureAddressMode]);
            RwXbStateCache.texAddressV = uparam.TextureAddressMode;
            result = TRUE;
            break;

        case rwRENDERSTATETEXTUREFILTER:
            result = XbRenderStateTextureFilter(0, uparam.TextureFilterMode);
            break;

        case rwRENDERSTATETEXTURERASTER:
            result = _rwXbRenderStateTextureRaster(uparam.RasterPtr);
            break;

        case rwRENDERSTATEZWRITEENABLE:
            result = XbRenderStateZWriteEnable(uparam.Bool);
            break;

        case rwRENDERSTATEZTESTENABLE:
            result = XbRenderStateZTestEnable(uparam.Bool);
            break;

        case rwRENDERSTATESRCBLEND:
            result = XbRenderStateSrcBlend(uparam.BlendFunction);
            break;

        case rwRENDERSTATEDESTBLEND:
            result = XbRenderStateDestBlend(uparam.BlendFunction);
            break;

        case rwRENDERSTATESHADEMODE:
            result = XbRenderStateShadeMode(uparam.ShadeMode);
            break;

        case rwRENDERSTATEVERTEXALPHAENABLE:
            result = XbRenderStateVertexAlphaEnable(uparam.Bool);
            break;

        case rwRENDERSTATEBORDERCOLOR:
            RwXboxSetCachedTextureStageState(0, D3DTSS_BORDERCOLOR, uparam.UInt32);
            result = TRUE;
            break;

        case rwRENDERSTATETEXTUREPERSPECTIVE:
            /* Always on */
            if (!uparam.Bool)
            {
                result = FALSE;
            }
            break;

        case rwRENDERSTATECULLMODE:
            result = XbRenderStateCullMode(uparam.CullMode);
            break;

        case rwRENDERSTATESTENCILENABLE:
            RwXboxSetCachedRenderState(D3DRS_STENCILENABLE, uparam.Bool);
            result = TRUE;
            break;

        case rwRENDERSTATESTENCILFAIL:
            result = _rwXbRenderStateStencilFail(uparam.StencilOperation);
            break;

        case rwRENDERSTATESTENCILZFAIL:
            result = _rwXbRenderStateStencilZFail(uparam.StencilOperation);
            break;

        case rwRENDERSTATESTENCILPASS:
            result = _rwXbRenderStateStencilPass(uparam.StencilOperation);
            break;

        case rwRENDERSTATESTENCILFUNCTION:
            result = _rwXbRenderStateStencilFunction(uparam.StencilFunction);
            break;

        case rwRENDERSTATESTENCILFUNCTIONREF:
            RwXboxSetCachedRenderState(D3DRS_STENCILREF, uparam.Int32);
            result = TRUE;
            break;

        case rwRENDERSTATESTENCILFUNCTIONMASK:
            RwXboxSetCachedRenderState(D3DRS_STENCILMASK, uparam.Int32);
            result = TRUE;
            break;

        case rwRENDERSTATESTENCILFUNCTIONWRITEMASK:
            RwXboxSetCachedRenderState(D3DRS_STENCILWRITEMASK, uparam.Int32);
            result = TRUE;
            break;

        case rwRENDERSTATEALPHATESTFUNCTION:
            if (uparam.AlphaTestFunction != RwXbStateCache.alphaTestFunction)
            {
                RwXbStateCache.alphaTestFunction = uparam.AlphaTestFunction;
                RwXbStateCache.alphaTestEnable =
                    (uparam.AlphaTestFunction != rwALPHATESTFUNCTIONALWAYS);

                if (_RwXbRenderStateCacheBuffer[D3DRS_ALPHABLENDENABLE])
                {
                    RwXboxSetCachedRenderState(D3DRS_ALPHATESTENABLE,
                                               RwXbStateCache.alphaTestEnable);
                }

                RwXboxSetCachedRenderState(D3DRS_ALPHAFUNC,
                                           _RwXbCmpFuncConvTable[uparam.AlphaTestFunction]);
            }
            result = TRUE;
            break;

        case rwRENDERSTATEALPHATESTFUNCTIONREF:
            RwXboxSetCachedRenderState(D3DRS_ALPHAREF, uparam.UInt32);
            break;

        default:
            result = FALSE;
            break;
    }

    return result;
}

// match: _RwXboxSetCurrentVertexShader @ 0x002B0900
void
RwXboxSetCurrentVertexShader(DWORD handle)
{
    if (RwXbStateCache.vertexShader != handle)
    {
        RwXbStateCache.vertexShader = handle;
        D3DDevice_SetVertexShader(handle);
    }
}

// match: _RwXboxGetCurrentVertexShader @ 0x002B0920
DWORD
RwXboxGetCurrentVertexShader(void)
{
    return RwXbStateCache.vertexShader;
}

// match: _RwXboxSetCurrentPixelShader @ 0x002B0930
void
RwXboxSetCurrentPixelShader(DWORD handle)
{
    if (RwXbStateCache.pixelShader != handle)
    {
        RwXbStateCache.pixelShader = handle;
        D3DDevice_SetPixelShader(handle);

        /* The pixel shader sets the texture modes */
        _RwXbRenderStateCacheBuffer[D3DRS_PSTEXTUREMODES] =
            D3D__RenderState[D3DRS_PSTEXTUREMODES];
    }
}
