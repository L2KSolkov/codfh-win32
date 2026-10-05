/*
 * codfh-match: RenderWare 3.6's Xbox driver state caches
 * (driver/xbox/xbcache.c), which the 3.7.2 tree does not have. Written from
 * the image; the file layout and names follow the Godfather debug build's copy
 * of the driver (RenderWare 3.7). The caches hold the D3D render, texture
 * stage and texture states RenderWare sets; the dirty ones are listed and sent
 * to D3D by _rwXbFlushCacheBuffer before drawing.
 */

#include <xtl.h>

#include "batypes.h"
#include "balibtyp.h"
#include "badebug.h"

#include "xbdevice.h"
#include "xbmemory.h"
#include "xbcache.h"

/* RenderWare 3.6's RCS id string, which the image keeps (the 3.7.2 tree has none) */
static const char rcsid[] = "@@@@(#)$Id: //RenderWare/RW36Active/rwsdk/driver/xbox/xbcache.c#4 $";

#define FLOATASDWORD(fvariable) (*((const DWORD *)&(fvariable)))

DWORD _RwXbRenderStateCacheBuffer[D3DRS_MAX];
RwUInt32 _RwXbRenderStateCacheDirty[D3DRS_MAX];
D3DRENDERSTATETYPE _RwXbRenderStateCacheList[D3DRS_MAX];
RwUInt32 _RwXbRenderStateCacheCount;

DWORD _RwXbTextureStageCacheBuffer[D3DTSS_MAX][RWXB_TEXTURESTAGES];
RwUInt32 _RwXbTextureStageCacheDirty[D3DTSS_MAX][RWXB_TEXTURESTAGES];
D3DTEXTURESTAGESTATETYPE _RwXbTextureStageCacheList[D3DTSS_MAX][RWXB_TEXTURESTAGES];
RwUInt32 _RwXbTextureStageCacheCount[RWXB_TEXTURESTAGES];

D3DBaseTexture *_RwXbTextureCacheBuffer[RWXB_TEXTURESTAGES];
D3DBaseTexture *RwXbTextureCache[RWXB_TEXTURESTAGES];

static D3DSurface *CurrentRenderSurface;
static D3DSurface *CurrentStencilSurface;

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: _rcsid @ 0x00416710

// match: __rwXbFlushCacheBuffer @ 0x002AE5C0
void
_rwXbFlushCacheBuffer(void)
{
    RwUInt32        i;
    RwUInt32        stage;

    if (_RwXbRenderStateCacheCount)
    {
        i = 0;
        do
        {
            D3DRENDERSTATETYPE state = _RwXbRenderStateCacheList[i];

            if (_RwXbRenderStateCacheBuffer[state] != D3D__RenderState[state])
            {
                D3DDevice_SetRenderStateNotInline(state, _RwXbRenderStateCacheBuffer[state]);
            }

            _RwXbRenderStateCacheDirty[state] = FALSE;
            i++;
        }
        while (i < _RwXbRenderStateCacheCount);

        _RwXbRenderStateCacheCount = 0;
    }

    for (stage = 0; stage < RWXB_TEXTURESTAGES; stage++)
    {
        if (_RwXbTextureStageCacheCount[stage])
        {
            i = 0;
            do
            {
                D3DTEXTURESTAGESTATETYPE type = _RwXbTextureStageCacheList[i][stage];

                if (_RwXbTextureStageCacheBuffer[type][stage] != D3D__TextureState[stage][type])
                {
                    D3DDevice_SetTextureStageStateNotInline(stage, type,
                                                            _RwXbTextureStageCacheBuffer[type][stage]);
                }

                _RwXbTextureStageCacheDirty[type][stage] = FALSE;
                i++;
            }
            while (i < _RwXbTextureStageCacheCount[stage]);

            _RwXbTextureStageCacheCount[stage] = 0;
        }
    }

    for (stage = 0; stage < RWXB_TEXTURESTAGES; stage++)
    {
        D3DBaseTexture *texture = _RwXbTextureCacheBuffer[stage];

        if (RwXbTextureCache[stage] != texture)
        {
            RwXbTextureCache[stage] = texture;
            D3DDevice_SetTexture(stage, texture);
        }
    }
}

// match: __rwXbRenderStateInit @ 0x002AE6B0
void
_rwXbRenderStateInit(D3DRENDERSTATETYPE state, DWORD value)
{
    _RwXbRenderStateCacheBuffer[state] = value;
    D3DDevice_SetRenderStateNotInline(state, value);
}

// match: __rwXbTextureStageInit @ 0x002AE6D0
void
_rwXbTextureStageInit(DWORD stage, D3DTEXTURESTAGESTATETYPE type, DWORD value)
{
    _RwXbTextureStageCacheBuffer[type][stage] = value;
    D3DDevice_SetTextureStageStateNotInline(stage, type, value);
}

// match: __rwXbCacheInit @ 0x002AE700
void
_rwXbCacheInit(void)
{
    RwReal      zero = 0.0f;
    RwReal      one = 1.0f;
    RwUInt32    i;
    RwUInt32    j;

    /* Render states */
    for (i = 0; i < D3DRS_MAX; i++)
    {
        _RwXbRenderStateCacheBuffer[i] = D3D__RenderState[i];
        _RwXbRenderStateCacheDirty[i] = FALSE;
    }
    _RwXbRenderStateCacheCount = 0;

    _rwXbRenderStateInit(D3DRS_ZFUNC, 0x203);
    _rwXbRenderStateInit(D3DRS_ALPHAFUNC, 0x204);
    _rwXbRenderStateInit(D3DRS_ALPHABLENDENABLE, 0);
    _rwXbRenderStateInit(D3DRS_ALPHATESTENABLE, 0);
    _rwXbRenderStateInit(D3DRS_ALPHAREF, 0);
    _rwXbRenderStateInit(D3DRS_SRCBLEND, 0x302);
    _rwXbRenderStateInit(D3DRS_DESTBLEND, 0x303);
    _rwXbRenderStateInit(D3DRS_ZWRITEENABLE, 1);
    _rwXbRenderStateInit(D3DRS_DITHERENABLE, 1);
    _rwXbRenderStateInit(D3DRS_SHADEMODE, 0x1D01);
    _rwXbRenderStateInit(D3DRS_COLORWRITEENABLE, 0x1010101);
    _rwXbRenderStateInit(D3DRS_STENCILZFAIL, 0x1E00);
    _rwXbRenderStateInit(D3DRS_STENCILPASS, 0x1E00);
    _rwXbRenderStateInit(D3DRS_STENCILFUNC, 0x207);
    _rwXbRenderStateInit(D3DRS_STENCILREF, 0);
    _rwXbRenderStateInit(D3DRS_STENCILMASK, 0xFFFFFFFF);
    _rwXbRenderStateInit(D3DRS_STENCILWRITEMASK, 0xFFFFFFFF);
    _rwXbRenderStateInit(D3DRS_BLENDOP, 0x8006);
    _rwXbRenderStateInit(D3DRS_BLENDCOLOR, 0);
    _rwXbRenderStateInit(D3DRS_SWATHWIDTH, 4);
    _rwXbRenderStateInit(D3DRS_POLYGONOFFSETZSLOPESCALE, FLOATASDWORD(zero));
    _rwXbRenderStateInit(D3DRS_POLYGONOFFSETZOFFSET, FLOATASDWORD(zero));
    _rwXbRenderStateInit(D3DRS_POINTOFFSETENABLE, 0);
    _rwXbRenderStateInit(D3DRS_WIREFRAMEOFFSETENABLE, 0);
    _rwXbRenderStateInit(D3DRS_SOLIDOFFSETENABLE, 0);
    _rwXbRenderStateInit(D3DRS_FOGENABLE, 0);
    _rwXbRenderStateInit(D3DRS_FOGTABLEMODE, 3);
    _rwXbRenderStateInit(D3DRS_FOGSTART, FLOATASDWORD(zero));
    _rwXbRenderStateInit(D3DRS_FOGEND, FLOATASDWORD(one));
    _rwXbRenderStateInit(D3DRS_FOGDENSITY, FLOATASDWORD(one));
    _rwXbRenderStateInit(D3DRS_RANGEFOGENABLE, 0);
    _rwXbRenderStateInit(D3DRS_WRAP0, 0);
    _rwXbRenderStateInit(D3DRS_WRAP1, 0);
    _rwXbRenderStateInit(D3DRS_WRAP2, 0);
    _rwXbRenderStateInit(D3DRS_WRAP3, 0);
    _rwXbRenderStateInit(D3DRS_LIGHTING, 0);
    _rwXbRenderStateInit(D3DRS_SPECULARENABLE, 0);
    _rwXbRenderStateInit(D3DRS_LOCALVIEWER, 0);
    _rwXbRenderStateInit(D3DRS_COLORVERTEX, 1);
    _rwXbRenderStateInit(D3DRS_BACKSPECULARMATERIALSOURCE, 2);
    _rwXbRenderStateInit(D3DRS_BACKDIFFUSEMATERIALSOURCE, 1);
    _rwXbRenderStateInit(D3DRS_BACKAMBIENTMATERIALSOURCE, 2);
    _rwXbRenderStateInit(D3DRS_BACKEMISSIVEMATERIALSOURCE, 0);
    _rwXbRenderStateInit(D3DRS_SPECULARMATERIALSOURCE, 0);
    _rwXbRenderStateInit(D3DRS_DIFFUSEMATERIALSOURCE, 0);
    _rwXbRenderStateInit(D3DRS_AMBIENTMATERIALSOURCE, 0);
    _rwXbRenderStateInit(D3DRS_EMISSIVEMATERIALSOURCE, 0);
    _rwXbRenderStateInit(D3DRS_BACKAMBIENT, 0);
    _rwXbRenderStateInit(D3DRS_AMBIENT, 0);
    _rwXbRenderStateInit(D3DRS_POINTSIZE, FLOATASDWORD(one));
    _rwXbRenderStateInit(D3DRS_POINTSIZE_MIN, FLOATASDWORD(zero));
    _rwXbRenderStateInit(D3DRS_POINTSPRITEENABLE, 0);
    _rwXbRenderStateInit(D3DRS_POINTSCALEENABLE, 0);
    _rwXbRenderStateInit(D3DRS_POINTSCALE_A, FLOATASDWORD(one));
    _rwXbRenderStateInit(D3DRS_POINTSCALE_B, FLOATASDWORD(one));
    _rwXbRenderStateInit(D3DRS_POINTSCALE_C, FLOATASDWORD(one));
    _rwXbRenderStateInit(D3DRS_POINTSIZE_MAX, FLOATASDWORD(one));
    _rwXbRenderStateInit(D3DRS_PATCHEDGESTYLE, 0);
    _rwXbRenderStateInit(D3DRS_PATCHSEGMENTS, FLOATASDWORD(one));
    _rwXbRenderStateInit(D3DRS_VERTEXBLEND, 0);
    _rwXbRenderStateInit(D3DRS_FOGCOLOR, 0xFFFFFFFF);
    _rwXbRenderStateInit(D3DRS_FILLMODE, 0x1B02);
    _rwXbRenderStateInit(D3DRS_BACKFILLMODE, 0x1B02);
    _rwXbRenderStateInit(D3DRS_TWOSIDEDLIGHTING, 0);
    _rwXbRenderStateInit(D3DRS_NORMALIZENORMALS, 0);
    _rwXbRenderStateInit(D3DRS_ZENABLE, 1);
    _rwXbRenderStateInit(D3DRS_STENCILENABLE, 0);
    _rwXbRenderStateInit(D3DRS_STENCILFAIL, 0x1E00);
    _rwXbRenderStateInit(D3DRS_FRONTFACE, 0x901);
    _rwXbRenderStateInit(D3DRS_CULLMODE, 0x900);
    _rwXbRenderStateInit(D3DRS_TEXTUREFACTOR, 0);
    _rwXbRenderStateInit(D3DRS_ZBIAS, 0);
    _rwXbRenderStateInit(D3DRS_LOGICOP, 0);
    _rwXbRenderStateInit(D3DRS_EDGEANTIALIAS, 0);
    _rwXbRenderStateInit(D3DRS_MULTISAMPLEANTIALIAS, 1);
    _rwXbRenderStateInit(D3DRS_MULTISAMPLEMASK, 0xFFFFFFFF);
    _rwXbRenderStateInit(D3DRS_SHADOWFUNC, 0x200);
    _rwXbRenderStateInit(D3DRS_LINEWIDTH, FLOATASDWORD(one));
    _rwXbRenderStateInit(D3DRS_DXT1NOISEENABLE, 1);
    _rwXbRenderStateInit(D3DRS_YUVENABLE, 0);
    _rwXbRenderStateInit(D3DRS_OCCLUSIONCULLENABLE, 1);
    _rwXbRenderStateInit(D3DRS_STENCILCULLENABLE, 1);
    _rwXbRenderStateInit(D3DRS_ROPZCMPALWAYSREAD, 0);
    _rwXbRenderStateInit(D3DRS_ROPZREAD, 0);
    _rwXbRenderStateInit(D3DRS_DONOTCULLUNCOMPRESSED, 0);

    switch (_RwXbDeviceGlobals.config.multiSampleType)
    {
        case D3DMULTISAMPLE_2_SAMPLES_MULTISAMPLE_LINEAR:
            _rwXbRenderStateInit(D3DRS_SWAPFILTER, D3DTEXF_LINEAR);
            _rwXbRenderStateInit(D3DRS_MULTISAMPLEMODE, D3DMULTISAMPLEMODE_2X);
            _rwXbRenderStateInit(D3DRS_MULTISAMPLERENDERTARGETMODE, D3DMULTISAMPLEMODE_2X);
            break;

        case D3DMULTISAMPLE_2_SAMPLES_MULTISAMPLE_QUINCUNX:
            _rwXbRenderStateInit(D3DRS_SWAPFILTER, D3DTEXF_QUINCUNX);
            _rwXbRenderStateInit(D3DRS_MULTISAMPLEMODE, D3DMULTISAMPLEMODE_2X);
            _rwXbRenderStateInit(D3DRS_MULTISAMPLERENDERTARGETMODE, D3DMULTISAMPLEMODE_2X);
            break;

        case D3DMULTISAMPLE_2_SAMPLES_SUPERSAMPLE_HORIZONTAL_LINEAR:
            _rwXbRenderStateInit(D3DRS_SWAPFILTER, D3DTEXF_LINEAR);
            _rwXbRenderStateInit(D3DRS_MULTISAMPLEMODE, D3DMULTISAMPLEMODE_1X);
            _rwXbRenderStateInit(D3DRS_MULTISAMPLERENDERTARGETMODE, D3DMULTISAMPLEMODE_1X);
            break;

        case D3DMULTISAMPLE_2_SAMPLES_SUPERSAMPLE_VERTICAL_LINEAR:
            _rwXbRenderStateInit(D3DRS_SWAPFILTER, D3DTEXF_LINEAR);
            _rwXbRenderStateInit(D3DRS_MULTISAMPLEMODE, D3DMULTISAMPLEMODE_1X);
            _rwXbRenderStateInit(D3DRS_MULTISAMPLERENDERTARGETMODE, D3DMULTISAMPLEMODE_1X);
            break;

        case D3DMULTISAMPLE_4_SAMPLES_MULTISAMPLE_LINEAR:
            _rwXbRenderStateInit(D3DRS_SWAPFILTER, D3DTEXF_LINEAR);
            _rwXbRenderStateInit(D3DRS_MULTISAMPLEMODE, D3DMULTISAMPLEMODE_4X);
            _rwXbRenderStateInit(D3DRS_MULTISAMPLERENDERTARGETMODE, D3DMULTISAMPLEMODE_4X);
            break;

        case D3DMULTISAMPLE_4_SAMPLES_MULTISAMPLE_GAUSSIAN:
            _rwXbRenderStateInit(D3DRS_SWAPFILTER, D3DTEXF_GAUSSIANCUBIC);
            _rwXbRenderStateInit(D3DRS_MULTISAMPLEMODE, D3DMULTISAMPLEMODE_4X);
            _rwXbRenderStateInit(D3DRS_MULTISAMPLERENDERTARGETMODE, D3DMULTISAMPLEMODE_4X);
            break;

        case D3DMULTISAMPLE_4_SAMPLES_SUPERSAMPLE_LINEAR:
            _rwXbRenderStateInit(D3DRS_SWAPFILTER, D3DTEXF_LINEAR);
            _rwXbRenderStateInit(D3DRS_MULTISAMPLEMODE, D3DMULTISAMPLEMODE_1X);
            _rwXbRenderStateInit(D3DRS_MULTISAMPLERENDERTARGETMODE, D3DMULTISAMPLEMODE_1X);
            break;

        case D3DMULTISAMPLE_4_SAMPLES_SUPERSAMPLE_GAUSSIAN:
            _rwXbRenderStateInit(D3DRS_SWAPFILTER, D3DTEXF_GAUSSIANCUBIC);
            _rwXbRenderStateInit(D3DRS_MULTISAMPLEMODE, D3DMULTISAMPLEMODE_1X);
            _rwXbRenderStateInit(D3DRS_MULTISAMPLERENDERTARGETMODE, D3DMULTISAMPLEMODE_1X);
            break;

        case D3DMULTISAMPLE_9_SAMPLES_MULTISAMPLE_GAUSSIAN:
            _rwXbRenderStateInit(D3DRS_SWAPFILTER, D3DTEXF_GAUSSIANCUBIC);
            _rwXbRenderStateInit(D3DRS_MULTISAMPLEMODE, D3DMULTISAMPLEMODE_4X);
            _rwXbRenderStateInit(D3DRS_MULTISAMPLERENDERTARGETMODE, D3DMULTISAMPLEMODE_4X);
            break;

        case D3DMULTISAMPLE_9_SAMPLES_SUPERSAMPLE_GAUSSIAN:
            _rwXbRenderStateInit(D3DRS_SWAPFILTER, D3DTEXF_GAUSSIANCUBIC);
            _rwXbRenderStateInit(D3DRS_MULTISAMPLEMODE, D3DMULTISAMPLEMODE_1X);
            _rwXbRenderStateInit(D3DRS_MULTISAMPLERENDERTARGETMODE, D3DMULTISAMPLEMODE_1X);
            break;

        default:
            _rwXbRenderStateInit(D3DRS_SWAPFILTER, D3DTEXF_POINT);
            _rwXbRenderStateInit(D3DRS_MULTISAMPLEMODE, D3DMULTISAMPLEMODE_1X);
            _rwXbRenderStateInit(D3DRS_MULTISAMPLERENDERTARGETMODE, D3DMULTISAMPLEMODE_1X);
            break;
    }

    /* Texture i states */
    for (i = 0; i < RWXB_TEXTURESTAGES; i++)
    {
        _RwXbTextureStageCacheCount[i] = 0;

        for (j = 0; j < D3DTSS_MAX; j++)
        {
            _RwXbTextureStageCacheBuffer[j][i] = D3D__TextureState[i][j];
            _RwXbTextureStageCacheDirty[j][i] = FALSE;
        }
    }

    _rwXbTextureStageInit(0, D3DTSS_COLOROP, 2);
    _rwXbTextureStageInit(0, D3DTSS_COLORARG0, 1);
    _rwXbTextureStageInit(0, D3DTSS_COLORARG1, 0);
    _rwXbTextureStageInit(0, D3DTSS_COLORARG2, 1);
    _rwXbTextureStageInit(0, D3DTSS_ALPHAOP, 2);
    _rwXbTextureStageInit(0, D3DTSS_ALPHAARG0, 1);
    _rwXbTextureStageInit(0, D3DTSS_ALPHAARG1, 0);
    _rwXbTextureStageInit(0, D3DTSS_ALPHAARG2, 1);
    _rwXbTextureStageInit(0, D3DTSS_RESULTARG, 1);
    _rwXbTextureStageInit(0, D3DTSS_TEXTURETRANSFORMFLAGS, 0);
    _rwXbTextureStageInit(0, D3DTSS_ADDRESSU, 1);
    _rwXbTextureStageInit(0, D3DTSS_ADDRESSV, 1);
    _rwXbTextureStageInit(0, D3DTSS_ADDRESSW, 1);
    _rwXbTextureStageInit(0, D3DTSS_MAGFILTER, 2);
    _rwXbTextureStageInit(0, D3DTSS_MINFILTER, 2);
    _rwXbTextureStageInit(0, D3DTSS_MIPFILTER, 0);
    _rwXbTextureStageInit(0, D3DTSS_MIPMAPLODBIAS, FLOATASDWORD(zero));
    _rwXbTextureStageInit(0, D3DTSS_MAXMIPLEVEL, 0);
    _rwXbTextureStageInit(0, D3DTSS_MAXANISOTROPY, 1);
    _rwXbTextureStageInit(0, D3DTSS_COLORKEYOP, 0);
    _rwXbTextureStageInit(0, D3DTSS_COLORSIGN, 0);
    _rwXbTextureStageInit(0, D3DTSS_ALPHAKILL, 0);
    _rwXbTextureStageInit(0, D3DTSS_BUMPENVMAT00, FLOATASDWORD(zero));
    _rwXbTextureStageInit(0, D3DTSS_BUMPENVMAT01, FLOATASDWORD(zero));
    _rwXbTextureStageInit(0, D3DTSS_BUMPENVMAT10, FLOATASDWORD(zero));
    _rwXbTextureStageInit(0, D3DTSS_BUMPENVMAT11, FLOATASDWORD(zero));
    _rwXbTextureStageInit(0, D3DTSS_BUMPENVLSCALE, FLOATASDWORD(zero));
    _rwXbTextureStageInit(0, D3DTSS_BUMPENVLOFFSET, FLOATASDWORD(zero));
    _rwXbTextureStageInit(0, D3DTSS_TEXCOORDINDEX, 0);
    _rwXbTextureStageInit(0, D3DTSS_BORDERCOLOR, 0xFF000000);
    _rwXbTextureStageInit(0, D3DTSS_COLORKEYCOLOR, 0);

    for (i = 1; i < RWXB_TEXTURESTAGES; i++)
    {
        _rwXbTextureStageInit(i, D3DTSS_COLOROP, 1);
        _rwXbTextureStageInit(i, D3DTSS_COLORARG0, 1);
        _rwXbTextureStageInit(i, D3DTSS_COLORARG1, 0);
        _rwXbTextureStageInit(i, D3DTSS_COLORARG2, 1);
        _rwXbTextureStageInit(i, D3DTSS_ALPHAOP, 1);
        _rwXbTextureStageInit(i, D3DTSS_ALPHAARG0, 1);
        _rwXbTextureStageInit(i, D3DTSS_ALPHAARG1, 0);
        _rwXbTextureStageInit(i, D3DTSS_ALPHAARG2, 1);
        _rwXbTextureStageInit(i, D3DTSS_RESULTARG, 1);
        _rwXbTextureStageInit(i, D3DTSS_TEXTURETRANSFORMFLAGS, 0);
        _rwXbTextureStageInit(i, D3DTSS_ADDRESSU, 1);
        _rwXbTextureStageInit(i, D3DTSS_ADDRESSV, 1);
        _rwXbTextureStageInit(i, D3DTSS_ADDRESSW, 1);
        _rwXbTextureStageInit(i, D3DTSS_MAGFILTER, 2);
        _rwXbTextureStageInit(i, D3DTSS_MINFILTER, 2);
        _rwXbTextureStageInit(i, D3DTSS_MIPFILTER, 0);
        _rwXbTextureStageInit(i, D3DTSS_MIPMAPLODBIAS, FLOATASDWORD(zero));
        _rwXbTextureStageInit(i, D3DTSS_MAXMIPLEVEL, 0);
        _rwXbTextureStageInit(i, D3DTSS_MAXANISOTROPY, 1);
        _rwXbTextureStageInit(i, D3DTSS_COLORKEYOP, 0);
        _rwXbTextureStageInit(i, D3DTSS_COLORSIGN, 0);
        _rwXbTextureStageInit(i, D3DTSS_ALPHAKILL, 0);
        _rwXbTextureStageInit(i, D3DTSS_BUMPENVMAT00, FLOATASDWORD(zero));
        _rwXbTextureStageInit(i, D3DTSS_BUMPENVMAT01, FLOATASDWORD(zero));
        _rwXbTextureStageInit(i, D3DTSS_BUMPENVMAT10, FLOATASDWORD(zero));
        _rwXbTextureStageInit(i, D3DTSS_BUMPENVMAT11, FLOATASDWORD(zero));
        _rwXbTextureStageInit(i, D3DTSS_BUMPENVLSCALE, FLOATASDWORD(zero));
        _rwXbTextureStageInit(i, D3DTSS_BUMPENVLOFFSET, FLOATASDWORD(zero));
        _rwXbTextureStageInit(i, D3DTSS_TEXCOORDINDEX, i);
        _rwXbTextureStageInit(i, D3DTSS_BORDERCOLOR, 0xFF000000);
        _rwXbTextureStageInit(i, D3DTSS_COLORKEYCOLOR, 0);
    }

    /* Textures */
    for (i = 0; i < RWXB_TEXTURESTAGES; i++)
    {
        D3DDevice_SetTexture(i, NULL);
        _RwXbTextureCacheBuffer[i] = NULL;
        RwXbTextureCache[i] = NULL;
    }
}

// match: _RwXboxDrawIndexedVertices @ 0x002AF290
void
RwXboxDrawIndexedVertices(D3DPRIMITIVETYPE primitiveType, UINT vertexCount,
                          CONST WORD *indexData)
{
    _rwXbFlushCacheBuffer();
    D3DDevice_DrawIndexedVertices(primitiveType, vertexCount, indexData);
}

// match: _RwXboxDrawVertices @ 0x002AF2B0
void
RwXboxDrawVertices(D3DPRIMITIVETYPE primitiveType, UINT startVertex, UINT vertexCount)
{
    _rwXbFlushCacheBuffer();
    D3DDevice_DrawVertices(primitiveType, startVertex, vertexCount);
}

// match: _RwXboxDrawVerticesUP @ 0x002AF2D0
void
RwXboxDrawVerticesUP(D3DPRIMITIVETYPE primitiveType, UINT vertexCount,
                     CONST void *vertexStreamZeroData, UINT vertexStreamZeroStride)
{
    _rwXbFlushCacheBuffer();
    D3DDevice_DrawVerticesUP(primitiveType, vertexCount, vertexStreamZeroData,
                             vertexStreamZeroStride);
}

// match: _RwXboxSetRenderTarget @ 0x002AF2F0
void
RwXboxSetRenderTarget(D3DSurface *renderTarget, D3DSurface *zStencil)
{
    if (renderTarget != CurrentRenderSurface || zStencil != CurrentStencilSurface)
    {
        CurrentRenderSurface = renderTarget;
        CurrentStencilSurface = zStencil;
        _rwXbFlushCacheBuffer();
        D3DDevice_SetRenderTarget(renderTarget, zStencil);
    }
}

// match: __rwXbTextureRelease @ 0x002AF330
void
_rwXbTextureRelease(D3DBaseTexture *texture)
{
    if (texture->Common & D3DCOMMON_D3DCREATED)
    {
        D3DResource_Release((D3DResource *)texture);
        return;
    }

    if (texture->Common & D3DCOMMON_INTREFCOUNT_MASK)
    {
        RwUInt32    stage;

        for (stage = 0; stage < RWXB_TEXTURESTAGES; stage++)
        {
            _RwXbTextureCacheBuffer[stage] = NULL;
            RwXbTextureCache[stage] = NULL;
            D3DDevice_SetTexture(stage, NULL);
        }
    }

    D3DResource_BlockUntilNotBusy((D3DResource *)texture);
    _rwXbMemoryPhysicalFree((void *)texture->Data);
}
