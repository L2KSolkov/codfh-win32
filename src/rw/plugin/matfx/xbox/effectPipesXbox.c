/*
 * codfh-match: RenderWare 3.6's Xbox material effects pipelines, rebuilt
 * from the image; the file name is the image's RCS id string's, names and
 * shapes the Godfather PDB's copy (3.7; 3.6 differs in block layout,
 * the pixel shaders chosen and the multi-texture path).
 */

#include <xtl.h>

#include <rwcore.h>
#include <rpworld.h>

#include <rpcriter.h>

#include "rpplugin.h"
#include "effectPipes.h"

#include "xbmemory.h"
#include "xbcache.h"
#include "xbrendst.h"
#include "xbraster.h"
#include "xbpixelshader.h"
#include "xbpipe.h"
#include "xbvtxfmt.h"
#include "nodeXBoxAtomicAllInOne.h"
#include "nodeXBoxWorldSectorAllInOne.h"

#include "multiTex.h"
#include "multiTexEffect.h"
#include "multitexxbox.h"

// Its data definitions (PLAN M5), in the image's address order.
// End of its data definitions.


/* RenderWare 3.6's RCS id string, which the image keeps (the 3.7.2 tree has none) */
static const char rcsid[] = "@@@@(#)$Id: //RenderWare/RW36Active/rwsdk/plugin/matfx/xbox/effectPipesXbox.c#3 $";

/* A bump map vertex shader: the vertex format it was built for. */
typedef struct BumpMapVtxFmtDescItem BumpMapVtxFmtDescItem;
struct BumpMapVtxFmtDescItem
{
    RpXboxVtxFmt    format;
    DWORD           handle;
};

#define NUMBUMPMAPSHADERS 8

static RxXboxAllInOneInstanceCallBack worldInstancePipeline;
static BumpMapVtxFmtDescItem BumpMapVertexShaders[NUMBUMPMAPSHADERS];
static RxXboxAllInOneInstanceCallBack instancePipeline;
static RxPipeline *MatFXAtomicPipe;
static RxPipeline *MatFXWorldSectorPipe;
static DWORD EnvMapPixelShader;
static DWORD EnvMapNoBaseTexturePixelShader;
static DWORD BumpMapPixelShader;
static DWORD BumpEnvMapPixelShader;
static DWORD BumpEnvMapAlphaPixelShader;
static DWORD BumpMapNomatcolorPixelShader;
static DWORD BumpEnvMapNomatcolorPixelShader;
static DWORD BumpEnvMapNomatcolorAlphaPixelShader;
static RwUInt32 BumpMapNumShaders;
static RwUInt32 BumpMapNextShader;


/* The pixel shader microcode (the image's .data). */
DWORD dwEnvmapPixelShader[60] =
{
    0xD8D41010, 0xDCD11010, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x000000C0, 0x000000C0, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xC8C40000, 0xCCC10000,
    0xC9C120CC, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x000000C0, 0x000000C0, 0x00000C00,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00011103,
    0x00000021, 0x00000000, 0x00000000, 0xFFFFF10F, 0xFFFFFFFF, 0x000001FF,
};

DWORD dwEnvmapnobasePixelShader[60] =
{
    0xD4D11010, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x000000C0, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xC4C10000, 0xC8C120CC,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x000000C0, 0x00000C00, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00011102,
    0x00000001, 0x00000000, 0x00000000, 0xFFFFFF10, 0xFFFFFFFF, 0x000001FF,
};

DWORD dwBumpmapPixelShader[60] =
{
    0xD8D4D9D4, 0xD4301010, 0xDCD11010, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x000000CD, 0x000000C0, 0x000000C0, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xC8C4C9C4, 0xCC38CDD9,
    0xCCC10000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x000000CD, 0x00000C00, 0x000000C0,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00011103,
    0x00000021, 0x00000000, 0x00000000, 0xFFFFF0FF, 0xFFFFFFFF, 0x000001FF,
};

DWORD dwBumpenvmapPixelShader[60] =
{
    0xD8D4D9D4, 0xD4301010, 0xDCD1DADA, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x000000CD, 0x000000C0, 0x000000CD, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xC8C4C9C4, 0xCC38CDD9,
    0xCCC1CADA, 0xCDC120CC, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x000000CD, 0x00000C00, 0x000000CD,
    0x00000C00, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00011104,
    0x00000421, 0x00000000, 0x00000000, 0xFFFF10FF, 0xFFFFFFFF, 0x000001FF,
};

DWORD dwBumpenvmapalphaPixelShader[60] =
{
    0xD8D4D9D4, 0xDC38DDD9, 0xDCD1DADA, 0xDDDC1010, 0xD4301010, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x000000CD, 0x00000C00, 0x000000CD, 0x000000D0,
    0x000000C0, 0x00000000, 0x00000000, 0x00000000, 0xC8C4C9C4, 0xCC38CDD9,
    0xCCC1CADA, 0xCDDC0000, 0xCDC120CC, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x000000CD, 0x00000C00, 0x000000CD,
    0x000000D0, 0x00000C00, 0x00000000, 0x00000000, 0x00000000, 0x00011105,
    0x00000421, 0x00000000, 0x00000000, 0xFFF1F0FF, 0xFFFFFFFF, 0x000001FF,
};

DWORD dwBumpmapnomatcolorPixelShader[60] =
{
    0xD8D4D9D4, 0xD4301010, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x000000CD, 0x000000C0, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xC8C4C9C4, 0xCC38CDD9,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x000000CD, 0x00000C00, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00011102,
    0x00000021, 0x00000000, 0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0x000001FF,
};

DWORD dwBumpenvmapnomatcolorPixelShader[60] =
{
    0xD8D4D9D4, 0xD4301010, 0xDADA1010, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x000000CD, 0x000000C0, 0x000000D0, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xC8C4C9C4, 0xCC38CDD9,
    0xCADA0000, 0xCDC120CC, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x000000CD, 0x00000C00, 0x000000D0,
    0x00000C00, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00011104,
    0x00000421, 0x00000000, 0x00000000, 0xFFFF1FFF, 0xFFFFFFFF, 0x000001FF,
};

DWORD dwBumpenvmapnomatcoloralphaPixelShader[60] =
{
    0xD8D4D9D4, 0xDC38DDD9, 0xDADA1010, 0xDDDC1010, 0xD4301010, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x000000CD, 0x00000C00, 0x000000D0, 0x000000D0,
    0x000000C0, 0x00000000, 0x00000000, 0x00000000, 0xC8C4C9C4, 0xCC38CDD9,
    0xCADA0000, 0xCDDC0000, 0xCDC120CC, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x000000CD, 0x00000C00, 0x000000D0,
    0x000000D0, 0x00000C00, 0x00000000, 0x00000000, 0x00000000, 0x00011105,
    0x00000421, 0x00000000, 0x00000000, 0xFFF1FFFF, 0xFFFFFFFF, 0x000001FF,
};

#define RpXboxMaterialGetPixelShader(_material) \
    (*((DWORD *)(((RwUInt8 *)(_material)) + _RpXboxMaterialPixelShaderOffset)))

/* The bump map vertex declaration types of each component type. */
static const DWORD BumpMapVtxFmtToD3D_3Elems[rpCOMPTYPEMAX] =
{
    0,
    D3DVSDT_PBYTE3,
    D3DVSDT_SHORT3,
    D3DVSDT_NORMSHORT3,
    D3DVSDT_NORMPACKED3,
    D3DVSDT_FLOAT3
};

static const DWORD BumpMapVtxFmtToD3D_2Elems[rpCOMPTYPEMAX] =
{
    0,
    D3DVSDT_PBYTE2,
    D3DVSDT_SHORT2,
    D3DVSDT_NORMSHORT2,
    D3DVSDT_NORMPACKED3,
    D3DVSDT_FLOAT2
};

/* Unreferenced (Godfather keeps them unnamed too): between the bump map tables and the stage
   table; each under 64 bytes, since the image keeps them 4-aligned. */
static const RwUInt32 unk_41A7B4[6] =
{
    0,
    1,
    2,
    3,
    4,
    0,
};

static const RwUInt32 unk_41A7CC[10] =
{
    0,
    0,
    1,
    1,
    0,
    2,
    2,
    0,
    1,
    1,
};

static const RwUInt32 unk_41A7F4[10] =
{
    1,
    2,
    2,
    1,
    1,
    1,
    2,
    2,
    2,
    2,
};

/* The texture transform of each stage. */
static const D3DTRANSFORMSTATETYPE rxXbTexTrxTable[4] =
{
    D3DTS_TEXTURE0,
    D3DTS_TEXTURE1,
    D3DTS_TEXTURE2,
    D3DTS_TEXTURE3
};

/* RenderWare's blend functions as D3D blends. */
D3DBLEND _RwXbDualPassConvTable[] =
{
    (D3DBLEND)0,
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

/* The blend a multi-texture effect replaced. */
RwUInt32 MatFXMTOldSrcBlend = D3DBLEND_SRCALPHA;
RwUInt32 MatFXMTOldDestBlend = D3DBLEND_INVSRCALPHA;

extern void RwXboxSetCurrentVertexShader(DWORD handle);
extern void RwXboxSetCurrentPixelShader(DWORD handle);

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: _rcsid @ 0x0041A730
// match: _BumpMapVtxFmtToD3D_3Elems @ 0x0041A784
// match: _BumpMapVtxFmtToD3D_2Elems @ 0x0041A79C
// match: _unk_41A7B4 @ 0x0041A7B4
// match: _unk_41A7CC @ 0x0041A7CC
// match: _unk_41A7F4 @ 0x0041A7F4
// match: _rxXbTexTrxTable @ 0x0041A81C
// match: ?texMat@?1??ApplyEnvMapTextureMatrix@@9@9 @ 0x0041A830
// match: ?Identity@?1??rxXbAtomicMatFXRenderCallback@@9@9 @ 0x0041A870
// match: _dwEnvmapPixelShader @ 0x00436E90
// match: _dwEnvmapnobasePixelShader @ 0x00436F80
// match: _dwBumpmapPixelShader @ 0x00437070
// match: _dwBumpenvmapPixelShader @ 0x00437160
// match: _dwBumpenvmapalphaPixelShader @ 0x00437250
// match: _dwBumpmapnomatcolorPixelShader @ 0x00437340
// match: _dwBumpenvmapnomatcolorPixelShader @ 0x00437430
// match: _dwBumpenvmapnomatcoloralphaPixelShader @ 0x00437520
// match: __RwXbDualPassConvTable @ 0x00437610
// match: _MatFXMTOldSrcBlend @ 0x00437640
// match: _MatFXMTOldDestBlend @ 0x00437644
// match: ?texMat@?1??ApplyAnimTextureMatrix@@9@9 @ 0x00437650

// match: _rxXbMatFXInstanceCallback @ 0x002F7CA0

static RwBool
rxXbMatFXInstanceCallback(void *object,
                          RxXboxResEntryHeader *instancedHeader,
                          RwBool reinstance,
                          RxXboxAllInOneInstanceCallBack instancePipe)
{
    RxXboxInstanceData  *mesh;

    if (!instancePipe(object, instancedHeader, reinstance))
    {
        return FALSE;
    }

    for (mesh = instancedHeader->begin; mesh != instancedHeader->end; mesh++)
    {
        rpMatFXMaterialData *matFXData = *MATFXMATERIALGETDATA(mesh->material);

        if (matFXData)
        {
            switch (matFXData->flags)
            {
                case rpMATFXEFFECTBUMPMAP:
                case rpMATFXEFFECTBUMPENVMAP:
                    matFXData->data[rpSECONDPASS].data.bumpMap.bumpVertexShader = 0;
                    break;

                default:
                    break;
            }
        }
    }

    return TRUE;
}

// match: _XbAtomicMatFXInstanceCallback @ 0x002F7D00
static RwBool
XbAtomicMatFXInstanceCallback(void *object,
                              RxXboxResEntryHeader *instancedHeader,
                              RwBool reinstance)
{
    return rxXbMatFXInstanceCallback(object, instancedHeader, reinstance, instancePipeline);
}

// match: _XbWorldSectorMatFXInstanceCallback @ 0x002F7D20
static RwBool
XbWorldSectorMatFXInstanceCallback(void *object,
                                   RxXboxResEntryHeader *instancedHeader,
                                   RwBool reinstance)
{
    return rxXbMatFXInstanceCallback(object, instancedHeader, reinstance,
                                     worldInstancePipeline);
}

// match: __rpMatFXSetupBumpMapTexture @ 0x002F7D40
RwTexture *
_rpMatFXSetupBumpMapTexture(const RwTexture *baseTexture,
                            const RwTexture *effectTexture)
{
    RwTexture *texture = NULL;

    if (effectTexture != NULL)
    {
        RwBool usingCompressed = FALSE;

        /* We can NOT manipulate compressed textures */
        if (baseTexture != NULL)
        {
            if (RASTEREXTFROMRASTER(RwTextureGetRaster(baseTexture))->dxtFormat)
            {
                usingCompressed = TRUE;
            }
            else
            {
                if (RASTEREXTFROMRASTER(RwTextureGetRaster(effectTexture))->dxtFormat)
                {
                    usingCompressed = TRUE;
                }
            }
        }
        else
        {
            if (RASTEREXTFROMRASTER(RwTextureGetRaster(effectTexture))->dxtFormat)
            {
                usingCompressed = TRUE;
            }
        }

        if (!usingCompressed)
        {
            texture = _rpMatFXTextureMaskCreate(baseTexture, effectTexture);
        }
    }
    else
    {
        texture = (RwTexture *)baseTexture;
    }

    return texture;
}

// match: _BumpMapGetVertexShader @ 0x002F7DA0
static DWORD
BumpMapGetVertexShader(const RpXboxVtxFmt *fmt)
{
    DWORD       bumpDecl[8];
    DWORD       handle;
    RwUInt32    index;

    for (index = 0; index < BumpMapNumShaders; index++)
    {
        if (*(const RwUInt32 *)fmt == *(const RwUInt32 *)&BumpMapVertexShaders[index].format)
        {
            return BumpMapVertexShaders[index].handle;
        }
    }

    if (BumpMapVertexShaders[BumpMapNextShader].handle)
    {
        D3DDevice_DeleteVertexShader(BumpMapVertexShaders[BumpMapNextShader].handle);
    }

    if (fmt->prelit)
    {
        bumpDecl[0] = D3DVSD_STREAM(0);
        bumpDecl[1] = D3DVSD_REG(0, BumpMapVtxFmtToD3D_3Elems[fmt->pos]);
        bumpDecl[2] = D3DVSD_REG(2, BumpMapVtxFmtToD3D_3Elems[fmt->norm]);
        bumpDecl[3] = D3DVSD_REG(3, D3DVSDT_D3DCOLOR);
        bumpDecl[4] = D3DVSD_REG(9, BumpMapVtxFmtToD3D_2Elems[fmt->texCoord & 0xF]);
        bumpDecl[5] = D3DVSD_STREAM(1);
        bumpDecl[6] = D3DVSD_REG(10, D3DVSDT_FLOAT2);
        bumpDecl[7] = D3DVSD_END();
    }
    else
    {
        bumpDecl[0] = D3DVSD_STREAM(0);
        bumpDecl[1] = D3DVSD_REG(0, BumpMapVtxFmtToD3D_3Elems[fmt->pos]);
        bumpDecl[2] = D3DVSD_REG(2, BumpMapVtxFmtToD3D_3Elems[fmt->norm]);
        bumpDecl[3] = D3DVSD_REG(9, BumpMapVtxFmtToD3D_2Elems[fmt->texCoord & 0xF]);
        bumpDecl[4] = D3DVSD_STREAM(1);
        bumpDecl[5] = D3DVSD_REG(10, D3DVSDT_FLOAT2);
        bumpDecl[6] = D3DVSD_END();
    }

    D3DDevice_CreateVertexShader(bumpDecl, NULL, &handle, 0);

    BumpMapVertexShaders[BumpMapNextShader].handle = handle;
    BumpMapVertexShaders[BumpMapNextShader].format = *fmt;

    BumpMapNextShader++;
    if (BumpMapNextShader >= NUMBUMPMAPSHADERS)
    {
        BumpMapNextShader = 0;
    }

    if (BumpMapNumShaders < NUMBUMPMAPSHADERS)
    {
        BumpMapNumShaders++;
    }

    return handle;
}

// match: _rxXbAtomicMatFXBumpMapRender @ 0x002F7F20
static void
rxXbAtomicMatFXBumpMapRender(const RpXboxVtxFmt *fmt,
                             RxXboxResEntryHeader *resEntryHeader,
                             RxXboxInstanceData *mesh,
                             const rpMatFXMaterialData *matFXData __RWUNUSED__,
                             RwUInt32 flags,
                             const RwMatrix *transform)
{
    RwV2d               *bumpCoords;
    RwUInt32            offsetTexCoord;
    RwUInt32            vbSize;
    RwUInt8             *lockedVB;
    RwUInt8             *lockedTexVB;
    RwUInt32            i;
    MatFXBumpMapData    *bumpMapData;
    RwBool              alpha;
    RpXboxCompType      typetexCoords;
    RwUInt32            offsetNormal;
    RwFrame             *bumpFrame;
    RwReal              factor;
    const RwMatrix      *bumpMatrix;
    D3DVertexBuffer     *vb2;
    RwV3d               normal;
    RwV3d               lightUp;
    RwV3d               lightRight;
    DWORD               alphaBlend;
    DWORD               alphaTest;

    alpha = (resEntryHeader->vertexAlpha || mesh->material->color.alpha < 0xFF);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)alpha);

    bumpMapData = &(*MATFXMATERIALGETDATA(mesh->material))->data[rpSECONDPASS].data.bumpMap;

    D3DVertexBuffer_Lock((D3DVertexBuffer *)resEntryHeader->vertexBuffer, 0, 0,
                         &lockedVB, D3DLOCK_READONLY);
    lockedVB += mesh->minVert * resEntryHeader->stride;

    vbSize = 8 * (mesh->minVert + mesh->numVertices);
    lockedTexVB = RwXboxLockDynamicVertexBuffer(vbSize);
    lockedTexVB += 8 * mesh->minVert;

    offsetNormal = _rpXboxVtxFmtGetSize((RpXboxCompType)fmt->pos, 3);
    offsetTexCoord = offsetNormal + _rpXboxVtxFmtGetSize((RpXboxCompType)fmt->norm, 3) +
                     4 * fmt->prelit;
    typetexCoords = (RpXboxCompType)(fmt->texCoord & 0xF);

    bumpFrame = bumpMapData->frame;
    if (NULL == bumpFrame)
    {
        bumpFrame = RwCameraGetFrame(RwCameraGetCurrentCamera());
    }

    bumpMatrix = RwFrameGetLTM(bumpFrame);

    factor = bumpMapData->coef * bumpMapData->invBumpWidth;
    RwV3dScale(&lightUp, RwMatrixGetUp(bumpMatrix), factor);
    RwV3dScale(&lightRight, RwMatrixGetRight(bumpMatrix), factor);

    bumpCoords = (RwV2d *)lockedTexVB;
    for (i = 0; i < mesh->numVertices; i++)
    {
        RwV3d               trxNormal;
        RwV2d               texCoords;
        RwReal              xx;
        RwReal              yy;

        _rpXboxVtxFmtUnInstV3d((RpXboxCompType)fmt->norm, &normal, lockedVB + offsetNormal);

        RwV3dTransformVector(&trxNormal, &normal, transform);
        _rwV3dNormalize(&trxNormal, &trxNormal);

        xx = RwV3dDotProduct(&trxNormal, &lightRight);
        yy = RwV3dDotProduct(&trxNormal, &lightUp);

        if (typetexCoords != rpFLOAT)
        {
            _rpXboxVtxFmtUnInstV2d(typetexCoords, &texCoords, lockedVB + offsetTexCoord);
        }
        else
        {
            texCoords = *(const RwV2d *)(lockedVB + offsetTexCoord);
        }

        bumpCoords->x = texCoords.x + xx;
        bumpCoords->y = texCoords.y + yy;
        bumpCoords++;

        lockedVB += resEntryHeader->stride;
    }

    if (bumpMapData->texture)
    {
        RwXboxRenderStateSetTexture(bumpMapData->texture, 0);
        RwXboxRenderStateSetTexture(bumpMapData->texture, 1);
    }
    else
    {
        RwXboxRenderStateSetTexture(mesh->material->texture, 0);
        RwXboxRenderStateSetTexture(mesh->material->texture, 1);
    }

    RwXboxGetCachedRenderState(D3DRS_ALPHABLENDENABLE, &alphaBlend);
    RwXboxGetCachedRenderState(D3DRS_ALPHATESTENABLE, &alphaTest);

    if (!alpha)
    {
        RwXboxSetCachedRenderState(D3DRS_ALPHATESTENABLE, FALSE);
        RwXboxSetCachedRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
    }

    RwXboxSetCachedTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);
    RwXboxSetCachedTextureStageState(1, D3DTSS_TEXCOORDINDEX, 1);

    if ((flags & rxGEOMETRY_PRELIT) && (flags & rxGEOMETRY_MODULATE))
    {
        RwReal              MaterialColor[4];

        MaterialColor[0] = mesh->material->color.red * (1.0f / 255.0f);
        MaterialColor[1] = mesh->material->color.green * (1.0f / 255.0f);
        MaterialColor[2] = mesh->material->color.blue * (1.0f / 255.0f);
        MaterialColor[3] = mesh->material->color.alpha * (1.0f / 255.0f);

        RwXboxSetCurrentPixelShader(BumpMapPixelShader);
        D3DDevice_SetPixelShaderConstant(0, MaterialColor, 1);
    }
    else
    {
        RwXboxSetCurrentPixelShader(BumpMapNomatcolorPixelShader);
    }

    RwXboxSetCurrentVertexShader(BumpMapGetVertexShader(fmt));

    vb2 = RwXboxGetCurrentVertexBuffer();
    D3DDevice_SetStreamSource(1, vb2, 8);

    RwXboxDrawIndexedVertices((D3DPRIMITIVETYPE)resEntryHeader->primType, mesh->numIndices,
                              mesh->indexBuffer);

    RwXboxSetCurrentPixelShader(0);

    if (!alpha)
    {
        RwXboxSetCachedRenderState(D3DRS_ALPHABLENDENABLE, alphaBlend);
        RwXboxSetCachedRenderState(D3DRS_ALPHATESTENABLE, alphaTest);
    }

    RwXboxSetCachedTextureStageState(0, D3DTSS_COLOROP, D3DTOP_DISABLE);
    RwXboxSetCachedTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
    RwXboxSetCachedTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);
    RwXboxSetCachedTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
    RwXboxSetCachedTextureStageState(1, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
    RwXboxSetCachedTextureStageState(1, D3DTSS_TEXCOORDINDEX, 1);

    RwXboxRenderStateSetTexture(NULL, 1);

    D3DDevice_SetStreamSource(1, NULL, 0);
}

// match: _ApplyAnimTextureMatrix @ 0x002F84E0
static void
ApplyAnimTextureMatrix(RwUInt32 stage, const RwMatrix *matrix)
{
    static RwMatrix texMat =
    {
        { 0.0f, 0.0f, 0.0f }, 0,
        { 0.0f, 0.0f, 0.0f }, 0,
        { 0.0f, 0.0f, 1.0f }, 0,
        { 0.0f, 0.0f, 0.0f }, 0
    };

    if (matrix && !rwMatrixTestFlags(matrix, rwMATRIXINTERNALIDENTITY))
    {
        RwXboxSetCachedTextureStageState(stage, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);

        texMat.right.x = matrix->right.x;
        texMat.right.y = matrix->right.y;
        texMat.up.x = matrix->up.x;
        texMat.up.y = matrix->up.y;
        texMat.at.x = matrix->pos.x;
        texMat.at.y = matrix->pos.y;

        D3DDevice_SetTransform((D3DTRANSFORMSTATETYPE)(D3DTS_TEXTURE0 + stage),
                               (const D3DMATRIX *)&texMat);
    }
}

// match: _rxXbAtomicMatFXDualPassRender @ 0x002F85A0
static void
rxXbAtomicMatFXDualPassRender(RxXboxResEntryHeader *resEntryHeader,
                              RxXboxInstanceData *mesh,
                              const rpMatFXMaterialData *matFXData,
                              RwUInt32 flags)
{
    RwTexture           *texture;
    const MatFXDualData *dualData;
    const MatFXUVAnimData *uvAnim = NULL;
    RwBool              alpha;
    RwBool              needSecondPass;
    RwUInt32            lastUsedStage = 0;

    texture = mesh->material->texture;

    alpha = (resEntryHeader->vertexAlpha || mesh->material->color.alpha < 0xFF);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)alpha);

    if (matFXData->flags != rpMATFXEFFECTDUALUVTRANSFORM)
    {
        dualData = &(*MATFXMATERIALGETDATA(mesh->material))->data[rpSECONDPASS].data.dual;
    }
    else
    {
        dualData = &(*MATFXMATERIALGETDATA(mesh->material))->data[rpTHIRDPASS].data.dual;
        uvAnim = &(*MATFXMATERIALGETDATA(mesh->material))->data[rpSECONDPASS].data.uvAnim;
    }

    if ((flags & (rxGEOMETRY_TEXTURED | rxGEOMETRY_TEXTURED2)) && texture)
    {
        RwXboxRenderStateSetTexture(texture, 0);
    }
    else
    {
        RwXboxRenderStateSetTexture(NULL, 0);
    }

    if (uvAnim)
    {
        ApplyAnimTextureMatrix(0, uvAnim->baseTransform);
    }

    needSecondPass = TRUE;

    if ((dualData->srcBlendMode == rwBLENDDESTCOLOR && dualData->dstBlendMode == rwBLENDZERO) ||
        (dualData->srcBlendMode == rwBLENDZERO && dualData->dstBlendMode == rwBLENDSRCCOLOR))
    {
        RwXboxSetCachedTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
        RwXboxSetCachedTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
        RwXboxSetCachedTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TEXTURE);
        RwXboxSetCachedTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
        RwXboxSetCachedTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
        RwXboxSetCachedTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);
        RwXboxSetCachedTextureStageState(1, D3DTSS_COLOROP, D3DTOP_MODULATE);
        RwXboxSetCachedTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
        RwXboxSetCachedTextureStageState(1, D3DTSS_COLORARG2, D3DTA_CURRENT);
        RwXboxSetCachedTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2);
        RwXboxSetCachedTextureStageState(1, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

        needSecondPass = FALSE;
        lastUsedStage = 1;
    }
    else if (dualData->srcBlendMode == rwBLENDSRCALPHA &&
             dualData->dstBlendMode == rwBLENDINVSRCALPHA)
    {
        RwXboxSetCachedTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG2);
        RwXboxSetCachedTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TEXTURE);
        RwXboxSetCachedTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2);
        RwXboxSetCachedTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);
        RwXboxSetCachedTextureStageState(1, D3DTSS_COLOROP, D3DTOP_BLENDTEXTUREALPHA);
        RwXboxSetCachedTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
        RwXboxSetCachedTextureStageState(1, D3DTSS_COLORARG2, D3DTA_CURRENT);
        RwXboxSetCachedTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2);
        RwXboxSetCachedTextureStageState(1, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
        RwXboxSetCachedTextureStageState(2, D3DTSS_COLOROP, D3DTOP_MODULATE);
        RwXboxSetCachedTextureStageState(2, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
        RwXboxSetCachedTextureStageState(2, D3DTSS_COLORARG2, D3DTA_CURRENT);
        RwXboxSetCachedTextureStageState(2, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
        RwXboxSetCachedTextureStageState(2, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
        RwXboxSetCachedTextureStageState(2, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

        needSecondPass = FALSE;
        lastUsedStage = 2;
    }
    else if (dualData->srcBlendMode == rwBLENDDESTCOLOR &&
             dualData->dstBlendMode == rwBLENDSRCCOLOR)
    {
        RwXboxSetCachedTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
        RwXboxSetCachedTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
        RwXboxSetCachedTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TEXTURE);
        RwXboxSetCachedTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
        RwXboxSetCachedTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
        RwXboxSetCachedTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);
        RwXboxSetCachedTextureStageState(1, D3DTSS_COLOROP, D3DTOP_MODULATE2X);
        RwXboxSetCachedTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
        RwXboxSetCachedTextureStageState(1, D3DTSS_COLORARG2, D3DTA_CURRENT);
        RwXboxSetCachedTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2);
        RwXboxSetCachedTextureStageState(1, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

        needSecondPass = FALSE;
        lastUsedStage = 1;
    }
    else if (dualData->srcBlendMode == rwBLENDONE && dualData->dstBlendMode == rwBLENDONE)
    {
        RwXboxSetCachedTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
        RwXboxSetCachedTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
        RwXboxSetCachedTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TEXTURE);
        RwXboxSetCachedTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
        RwXboxSetCachedTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
        RwXboxSetCachedTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);
        RwXboxSetCachedTextureStageState(1, D3DTSS_COLOROP, D3DTOP_MULTIPLYADD);
        RwXboxSetCachedTextureStageState(1, D3DTSS_COLORARG0, D3DTA_CURRENT);
        RwXboxSetCachedTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
        RwXboxSetCachedTextureStageState(1, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
        RwXboxSetCachedTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2);
        RwXboxSetCachedTextureStageState(1, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

        needSecondPass = FALSE;
        lastUsedStage = 1;
    }
    else if (dualData->srcBlendMode == rwBLENDZERO && dualData->dstBlendMode == rwBLENDSRCALPHA)
    {
        RwXboxSetCachedTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
        RwXboxSetCachedTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
        RwXboxSetCachedTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TEXTURE);
        RwXboxSetCachedTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
        RwXboxSetCachedTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
        RwXboxSetCachedTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);
        RwXboxSetCachedTextureStageState(1, D3DTSS_COLOROP, D3DTOP_MODULATE);
        RwXboxSetCachedTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE | D3DTA_ALPHAREPLICATE);
        RwXboxSetCachedTextureStageState(1, D3DTSS_COLORARG2, D3DTA_CURRENT);
        RwXboxSetCachedTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2);
        RwXboxSetCachedTextureStageState(1, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

        needSecondPass = FALSE;
        lastUsedStage = 1;
    }

    if (!needSecondPass)
    {
        if (!(flags & rxGEOMETRY_TEXTURED2))
        {
            RwXboxSetCachedTextureStageState(1, D3DTSS_TEXCOORDINDEX, 0);
        }
        else
        {
            RwXboxSetCachedTextureStageState(1, D3DTSS_TEXCOORDINDEX, 1);
        }

        if (uvAnim)
        {
            ApplyAnimTextureMatrix(1, uvAnim->dualTransform);
        }

        RwXboxRenderStateSetTexture(dualData->texture, 1);
    }
    else
    {
        RwXboxSetCachedTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
        RwXboxSetCachedTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
        RwXboxSetCachedTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TEXTURE);
        RwXboxSetCachedTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
        RwXboxSetCachedTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
        RwXboxSetCachedTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);

        lastUsedStage = 0;
    }

    if ((flags & rxGEOMETRY_PRELIT) && (flags & rxGEOMETRY_MODULATE) &&
        *(const RwUInt32 *)&mesh->material->color != 0xFFFFFFFF)
    {
        const RwRGBA    *color = &mesh->material->color;
        RwUInt32        tFactor;

        tFactor = ((RwUInt32)color->alpha << 24) | ((RwUInt32)color->red << 16) |
                  ((RwUInt32)color->green << 8) | (RwUInt32)color->blue;

        RwXboxSetCachedRenderState(D3DRS_TEXTUREFACTOR, tFactor);

        lastUsedStage++;

        RwXboxSetCachedTextureStageState(lastUsedStage, D3DTSS_COLOROP, D3DTOP_MODULATE);
        RwXboxSetCachedTextureStageState(lastUsedStage, D3DTSS_COLORARG1, D3DTA_TFACTOR);
        RwXboxSetCachedTextureStageState(lastUsedStage, D3DTSS_COLORARG2, D3DTA_CURRENT);
        RwXboxSetCachedTextureStageState(lastUsedStage, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
        RwXboxSetCachedTextureStageState(lastUsedStage, D3DTSS_ALPHAARG1, D3DTA_TFACTOR);
        RwXboxSetCachedTextureStageState(lastUsedStage, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
    }

    RwXboxSetCurrentPixelShader(0);
    RwXboxSetCurrentVertexShader(mesh->vertexShader);

    RwXboxDrawIndexedVertices((D3DPRIMITIVETYPE)resEntryHeader->primType, mesh->numIndices,
                              mesh->indexBuffer);

    if (needSecondPass)
    {
        DWORD   cacheSrc, cacheDest, cacheCmpFunc, alphaBlend;
        DWORD   fogEnabled, fogColor;

        if (flags & rxGEOMETRY_TEXTURED2)
        {
            RwXboxSetCachedTextureStageState(0, D3DTSS_TEXCOORDINDEX, 1);
        }
        else
        {
            RwXboxSetCachedTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);
        }

        RwXboxRenderStateSetTexture(dualData->texture, 0);

        if (uvAnim)
        {
            ApplyAnimTextureMatrix(0, uvAnim->dualTransform);
        }

        RwXboxGetCachedRenderState(D3DRS_SRCBLEND, &cacheSrc);
        RwXboxGetCachedRenderState(D3DRS_DESTBLEND, &cacheDest);
        RwXboxGetCachedRenderState(D3DRS_ALPHAFUNC, &cacheCmpFunc);
        RwXboxGetCachedRenderState(D3DRS_ALPHABLENDENABLE, &alphaBlend);

        RwXboxSetCachedRenderState(D3DRS_SRCBLEND, _RwXbDualPassConvTable[dualData->srcBlendMode]);
        RwXboxSetCachedRenderState(D3DRS_DESTBLEND, _RwXbDualPassConvTable[dualData->dstBlendMode]);
        RwXboxSetCachedRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
        RwXboxSetCachedRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

        RwXboxSetCachedTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
        RwXboxSetCachedTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
        RwXboxSetCachedTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TEXTURE);
        RwXboxSetCachedTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
        RwXboxSetCachedTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
        RwXboxSetCachedTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);

        RwXboxGetCachedRenderState(D3DRS_FOGENABLE, &fogEnabled);
        if (fogEnabled)
        {
            RwXboxGetCachedRenderState(D3DRS_FOGCOLOR, &fogColor);

            if (dualData->dstBlendMode == rwBLENDONE)
            {
                RwXboxSetCachedRenderState(D3DRS_FOGCOLOR, 0);
            }
            else if (dualData->srcBlendMode == rwBLENDDESTCOLOR ||
                     dualData->dstBlendMode == rwBLENDSRCCOLOR)
            {
                RwXboxSetCachedRenderState(D3DRS_FOGCOLOR, 0xFFFFFFFF);
            }
        }

        RwXboxSetCurrentPixelShader(0);
        RwXboxSetCurrentVertexShader(mesh->vertexShader);

        RwXboxDrawIndexedVertices((D3DPRIMITIVETYPE)resEntryHeader->primType, mesh->numIndices,
                                  mesh->indexBuffer);

        if (fogEnabled)
        {
            RwXboxSetCachedRenderState(D3DRS_FOGCOLOR, fogColor);
        }

        RwXboxSetCachedRenderState(D3DRS_SRCBLEND, cacheSrc);
        RwXboxSetCachedRenderState(D3DRS_DESTBLEND, cacheDest);
        RwXboxSetCachedRenderState(D3DRS_ALPHAFUNC, cacheCmpFunc);
        RwXboxSetCachedRenderState(D3DRS_ALPHABLENDENABLE, alphaBlend);

        RwXboxSetCachedTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);
    }
    else
    {
        RwXboxSetCachedTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);
        RwXboxSetCachedTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
        RwXboxSetCachedTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
        RwXboxSetCachedTextureStageState(1, D3DTSS_TEXCOORDINDEX, 1);

        if (lastUsedStage > 1)
        {
            RwXboxSetCachedTextureStageState(2, D3DTSS_COLOROP, D3DTOP_DISABLE);
            RwXboxSetCachedTextureStageState(2, D3DTSS_ALPHAOP, D3DTOP_DISABLE);

            if (lastUsedStage > 2)
            {
                RwXboxSetCachedTextureStageState(3, D3DTSS_COLOROP, D3DTOP_DISABLE);
                RwXboxSetCachedTextureStageState(3, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
            }
        }
    }

    if (uvAnim)
    {
        RwXboxSetCachedTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
        RwXboxSetCachedTextureStageState(1, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
    }
}

// match: _ApplyEnvMapTextureMatrix @ 0x002F9A40
static RwBool
ApplyEnvMapTextureMatrix(RwTexture *texture, RwUInt32 stage, RwFrame *frame)
{
    static const RwMatrix texMat =
    {
        { 0.5f, 0.0f, 0.0f }, 0,
        { 0.0f, -0.5f, 0.0f }, 0,
        { 0.0f, 0.0f, 1.0f }, 0,
        { 0.5f, 0.5f, 0.0f }, 0
    };

    RwXboxRenderStateSetTexture(texture, stage);

    if (RASTEREXTFROMRASTER(RwTextureGetRaster(texture))->cube)
    {
        const RwMatrix  *camMtx;
        RwMatrix        invMtx;

        RwXboxSetCachedTextureStageState(stage, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT3);
        RwXboxSetCachedTextureStageState(stage, D3DTSS_TEXCOORDINDEX,
                                         D3DTSS_TCI_CAMERASPACEREFLECTIONVECTOR);

        camMtx = RwFrameGetLTM(RwCameraGetFrame(RwCameraGetCurrentCamera()));

        invMtx.right.x = -camMtx->right.x;
        invMtx.right.y = -camMtx->right.y;
        invMtx.right.z = -camMtx->right.z;
        invMtx.up.x = camMtx->up.x;
        invMtx.up.y = camMtx->up.y;
        invMtx.up.z = camMtx->up.z;
        invMtx.at.x = camMtx->at.x;
        invMtx.at.y = camMtx->at.y;
        invMtx.at.z = camMtx->at.z;
        invMtx.pos.x = 0.0f;
        invMtx.pos.y = 0.0f;
        invMtx.pos.z = 0.0f;
        invMtx.flags = 0;
        invMtx.pad1 = 0;
        invMtx.pad2 = 0;
        *(RwReal *)&invMtx.pad3 = 1.0f;

        D3DDevice_SetTransform((D3DTRANSFORMSTATETYPE)(D3DTS_TEXTURE0 + stage),
                               (const D3DMATRIX *)&invMtx);
    }
    else
    {
        RwXboxSetCachedTextureStageState(stage, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);
        RwXboxSetCachedTextureStageState(stage, D3DTSS_TEXCOORDINDEX,
                                         D3DTSS_TCI_CAMERASPACENORMAL);

        if (frame)
        {
            RwMatrix        *tmpMtx = RwMatrixCreate();
            RwMatrix        *envMtx = RwMatrixCreate();
            RwMatrix        *result = RwMatrixCreate();
            const RwMatrix  *camMtx;

            camMtx = RwFrameGetLTM(RwCameraGetFrame(RwCameraGetCurrentCamera()));

            RwMatrixInvert(tmpMtx, RwFrameGetLTM(frame));
            RwMatrixMultiply(envMtx, tmpMtx, camMtx);

            envMtx->right.x = -envMtx->right.x;
            envMtx->right.y = -envMtx->right.y;
            envMtx->right.z = -envMtx->right.z;
            envMtx->flags = 0;
            envMtx->pos.x = 0.0f;
            envMtx->pos.y = 0.0f;
            envMtx->pos.z = 0.0f;

            RwMatrixMultiply(result, envMtx, &texMat);

            D3DDevice_SetTransform((D3DTRANSFORMSTATETYPE)(D3DTS_TEXTURE0 + stage),
                                   (const D3DMATRIX *)result);

            RwMatrixDestroy(result);
            RwMatrixDestroy(envMtx);
            RwMatrixDestroy(tmpMtx);

            return TRUE;
        }

        D3DDevice_SetTransform((D3DTRANSFORMSTATETYPE)(D3DTS_TEXTURE0 + stage),
                               (const D3DMATRIX *)&texMat);
    }

    return TRUE;
}

// match: _rxXbAtomicMatFXBumpEnvMapRender @ 0x002F9D10
static void
rxXbAtomicMatFXBumpEnvMapRender(const RpXboxVtxFmt *fmt,
                                RxXboxResEntryHeader *resEntryHeader,
                                RxXboxInstanceData *mesh,
                                const rpMatFXMaterialData *matFXData,
                                RwUInt32 flags,
                                const RwMatrix *transform)
{
    RwFrame             *bumpFrame;
    RwV2d               *bumpCoords;
    RwUInt32            offsetTexCoord;
    DWORD               alphaBlend;
    RwUInt32            vbSize;
    DWORD               alphaTest;
    RwReal              factor;
    RwUInt8             *lockedVB;
    RwUInt8             *lockedTexVB;
    RwUInt32            i;
    const MatFXEnvMapData *envMapData;
    D3DVertexBuffer     *vb2;
    const MatFXBumpMapData *bumpMapData;
    RwBool              alpha;
    RpXboxCompType      typetexCoords;
    const RwMatrix      *bumpMatrix;
    RwV3d               lightUp;
    RwV3d               lightRight;
    RwUInt32            offsetNormal;
    RwV3d               normal;

    envMapData = &(*MATFXMATERIALGETDATA(mesh->material))->data[rpTHIRDPASS].data.envMap;

    if (NULL == envMapData->texture)
    {
        rxXbAtomicMatFXBumpMapRender(fmt, resEntryHeader, mesh, matFXData, flags, transform);
        return;
    }

    bumpMapData = &(*MATFXMATERIALGETDATA(mesh->material))->data[rpSECONDPASS].data.bumpMap;

    alpha = (resEntryHeader->vertexAlpha || mesh->material->color.alpha < 0xFF);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)alpha);

    D3DVertexBuffer_Lock((D3DVertexBuffer *)resEntryHeader->vertexBuffer, 0, 0,
                         &lockedVB, D3DLOCK_READONLY);
    lockedVB += mesh->minVert * resEntryHeader->stride;

    vbSize = 8 * (mesh->minVert + mesh->numVertices);
    lockedTexVB = RwXboxLockDynamicVertexBuffer(vbSize);
    lockedTexVB += 8 * mesh->minVert;

    offsetNormal = _rpXboxVtxFmtGetSize((RpXboxCompType)fmt->pos, 3);
    offsetTexCoord = offsetNormal + _rpXboxVtxFmtGetSize((RpXboxCompType)fmt->norm, 3) +
                     4 * fmt->prelit;
    typetexCoords = (RpXboxCompType)(fmt->texCoord & 0xF);

    bumpFrame = bumpMapData->frame;
    if (NULL == bumpFrame)
    {
        bumpFrame = RwCameraGetFrame(RwCameraGetCurrentCamera());
    }

    bumpMatrix = RwFrameGetLTM(bumpFrame);

    factor = bumpMapData->coef * bumpMapData->invBumpWidth;
    RwV3dScale(&lightUp, RwMatrixGetUp(bumpMatrix), factor);
    RwV3dScale(&lightRight, RwMatrixGetRight(bumpMatrix), factor);

    bumpCoords = (RwV2d *)lockedTexVB;
    for (i = 0; i < mesh->numVertices; i++)
    {
        RwReal  yy;
        RwV3d   trxNormal;
        RwReal  xx;
        RwV2d   texCoords;

        _rpXboxVtxFmtUnInstV3d((RpXboxCompType)fmt->norm, &normal, lockedVB + offsetNormal);

        RwV3dTransformVector(&trxNormal, &normal, transform);
        _rwV3dNormalize(&trxNormal, &trxNormal);

        xx = RwV3dDotProduct(&trxNormal, &lightRight);
        yy = RwV3dDotProduct(&trxNormal, &lightUp);

        if (typetexCoords != rpFLOAT)
        {
            _rpXboxVtxFmtUnInstV2d(typetexCoords, &texCoords, lockedVB + offsetTexCoord);
        }
        else
        {
            texCoords = *(const RwV2d *)(lockedVB + offsetTexCoord);
        }

        bumpCoords->x = texCoords.x + xx;
        bumpCoords->y = texCoords.y + yy;
        bumpCoords++;

        lockedVB += resEntryHeader->stride;
    }

    if (bumpMapData->texture)
    {
        RwXboxRenderStateSetTexture(bumpMapData->texture, 0);
        RwXboxRenderStateSetTexture(bumpMapData->texture, 1);
    }
    else
    {
        RwXboxRenderStateSetTexture(mesh->material->texture, 0);
        RwXboxRenderStateSetTexture(mesh->material->texture, 1);
    }

    ApplyEnvMapTextureMatrix(envMapData->texture, 2, envMapData->frame);

    RwXboxGetCachedRenderState(D3DRS_ALPHABLENDENABLE, &alphaBlend);
    RwXboxGetCachedRenderState(D3DRS_ALPHATESTENABLE, &alphaTest);

    RwXboxSetCachedTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);
    RwXboxSetCachedTextureStageState(1, D3DTSS_TEXCOORDINDEX, 1);

    if (!alpha)
    {
        RwXboxSetCachedRenderState(D3DRS_ALPHATESTENABLE, FALSE);
        RwXboxSetCachedRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
    }

    {
        RwReal  ShinyFloats[4];

        ShinyFloats[0] = envMapData->coef;
        ShinyFloats[1] = envMapData->coef;
        ShinyFloats[2] = envMapData->coef;
        ShinyFloats[3] = envMapData->coef;

        if ((flags & rxGEOMETRY_PRELIT) && (flags & rxGEOMETRY_MODULATE))
        {
            RwReal  MaterialColor[4];

            MaterialColor[0] = mesh->material->color.red * (1.0f / 255.0f);
            MaterialColor[1] = mesh->material->color.green * (1.0f / 255.0f);
            MaterialColor[2] = mesh->material->color.blue * (1.0f / 255.0f);
            MaterialColor[3] = mesh->material->color.alpha * (1.0f / 255.0f);

            if (envMapData->useFrameBufferAlpha)
            {
                RwXboxSetCurrentPixelShader(BumpEnvMapAlphaPixelShader);
            }
            else
            {
                RwXboxSetCurrentPixelShader(BumpEnvMapPixelShader);
            }

            D3DDevice_SetPixelShaderConstant(0, MaterialColor, 1);
        }
        else
        {
            if (envMapData->useFrameBufferAlpha)
            {
                RwXboxSetCurrentPixelShader(BumpEnvMapNomatcolorAlphaPixelShader);
            }
            else
            {
                RwXboxSetCurrentPixelShader(BumpEnvMapNomatcolorPixelShader);
            }
        }

        D3DDevice_SetPixelShaderConstant(1, ShinyFloats, 1);

        RwXboxSetCurrentVertexShader(BumpMapGetVertexShader(fmt));

        vb2 = RwXboxGetCurrentVertexBuffer();
        D3DDevice_SetStreamSource(1, vb2, 8);

        RwXboxDrawIndexedVertices((D3DPRIMITIVETYPE)resEntryHeader->primType, mesh->numIndices,
                                  mesh->indexBuffer);

        RwXboxSetCurrentPixelShader(0);

        if (!alpha)
        {
            RwXboxSetCachedRenderState(D3DRS_ALPHABLENDENABLE, alphaBlend);
            RwXboxSetCachedRenderState(D3DRS_ALPHATESTENABLE, alphaTest);
        }

        RwXboxSetCachedTextureStageState(0, D3DTSS_COLOROP, D3DTOP_DISABLE);
        RwXboxSetCachedTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
        RwXboxSetCachedTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);
        RwXboxSetCachedTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
        RwXboxSetCachedTextureStageState(1, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
        RwXboxSetCachedTextureStageState(1, D3DTSS_TEXCOORDINDEX, 1);
        RwXboxSetCachedTextureStageState(2, D3DTSS_COLOROP, D3DTOP_DISABLE);
        RwXboxSetCachedTextureStageState(2, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
        RwXboxSetCachedTextureStageState(2, D3DTSS_TEXCOORDINDEX, 2);

        RwXboxRenderStateSetTexture(NULL, 1);
        RwXboxRenderStateSetTexture(NULL, 2);
    }
}

// match: _rxXbAtomicMatFXEnvRender @ 0x002FA3D0
static void
rxXbAtomicMatFXEnvRender(RxXboxResEntryHeader *resEntryHeader,
                         RxXboxInstanceData *mesh,
                         RwUInt32 flags)
{
    const MatFXEnvMapData   *envMapData;
    RwUInt32                shinny;

    envMapData = &(*MATFXMATERIALGETDATA(mesh->material))->data[rpSECONDPASS].data.envMap;

    shinny = RwFastRealToUInt32(envMapData->coef * 255.0f) & 0xFF;

    if (shinny > 0 && envMapData->texture)
    {
        RwBool      alpha;
        RwBool      dualPass;
        RwUInt32    tFactor;

        alpha = (resEntryHeader->vertexAlpha || mesh->material->color.alpha < 0xFF);
        RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)alpha);

        RwXboxSetCachedRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
        RwXboxSetCachedRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);
        RwXboxSetCachedRenderState(D3DRS_COLORVERTEX, TRUE);

        dualPass = FALSE;

        if (mesh->material->texture)
        {
            if (!envMapData->useFrameBufferAlpha &&
                (alpha || RASTEREXTFROMRASTER(RwTextureGetRaster(mesh->material->texture))->alpha))
            {
                dualPass = TRUE;
            }
        }
        else if (!envMapData->useFrameBufferAlpha && alpha)
        {
            dualPass = TRUE;
        }

        if (!dualPass)
        {
            if ((flags & rxGEOMETRY_PRELIT) && (flags & rxGEOMETRY_MODULATE))
            {
                RwReal  ShinyFloats[4];
                RwReal  MaterialColor[4];

                ShinyFloats[0] = envMapData->coef;
                ShinyFloats[1] = envMapData->coef;
                ShinyFloats[2] = envMapData->coef;
                ShinyFloats[3] = envMapData->coef;

                MaterialColor[0] = mesh->material->color.red * (1.0f / 255.0f);
                MaterialColor[1] = mesh->material->color.green * (1.0f / 255.0f);
                MaterialColor[2] = mesh->material->color.blue * (1.0f / 255.0f);
                MaterialColor[3] = mesh->material->color.alpha * (1.0f / 255.0f);

                if ((flags & (rxGEOMETRY_TEXTURED | rxGEOMETRY_TEXTURED2)) && mesh->material->texture)
                {
                    RwXboxRenderStateSetTexture(mesh->material->texture, 0);
                    ApplyEnvMapTextureMatrix(envMapData->texture, 1, envMapData->frame);
                    RwXboxSetCurrentPixelShader(EnvMapPixelShader);
                }
                else
                {
                    ApplyEnvMapTextureMatrix(envMapData->texture, 0, envMapData->frame);
                    RwXboxSetCurrentPixelShader(EnvMapNoBaseTexturePixelShader);
                }

                D3DDevice_SetPixelShaderConstant(0, MaterialColor, 1);
                D3DDevice_SetPixelShaderConstant(1, ShinyFloats, 1);
            }
            else
            {
                if ((flags & (rxGEOMETRY_TEXTURED | rxGEOMETRY_TEXTURED2)) && mesh->material->texture)
                {
                    RwXboxRenderStateSetTexture(mesh->material->texture, 0);
                    ApplyEnvMapTextureMatrix(envMapData->texture, 1, envMapData->frame);

                    RwXboxSetCachedTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
                    RwXboxSetCachedTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
                    RwXboxSetCachedTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TEXTURE);
                    RwXboxSetCachedTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
                    RwXboxSetCachedTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
                    RwXboxSetCachedTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);
                    RwXboxSetCachedTextureStageState(1, D3DTSS_COLOROP, D3DTOP_MULTIPLYADD);
                    RwXboxSetCachedTextureStageState(1, D3DTSS_COLORARG0, D3DTA_CURRENT);
                    RwXboxSetCachedTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
                    RwXboxSetCachedTextureStageState(1, D3DTSS_COLORARG2, D3DTA_TFACTOR);
                    RwXboxSetCachedTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2);
                    RwXboxSetCachedTextureStageState(1, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
                    RwXboxSetCachedTextureStageState(1, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
                }
                else
                {
                    ApplyEnvMapTextureMatrix(envMapData->texture, 0, envMapData->frame);

                    RwXboxSetCachedTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MULTIPLYADD);
                    RwXboxSetCachedTextureStageState(0, D3DTSS_COLORARG0, D3DTA_DIFFUSE);
                    RwXboxSetCachedTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
                    RwXboxSetCachedTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TFACTOR);
                }

                shinny |= (shinny << 8) | (shinny << 16) | (shinny << 24);
                RwXboxSetCachedRenderState(D3DRS_TEXTUREFACTOR, shinny);

                RwXboxSetCurrentPixelShader(0);
            }
        }
        else
        {
            RwXboxRenderStateSetTexture(mesh->material->texture, 0);

            RwXboxSetCachedTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
            RwXboxSetCachedTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
            RwXboxSetCachedTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TEXTURE);
            RwXboxSetCachedTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
            RwXboxSetCachedTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
            RwXboxSetCachedTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);

            if ((flags & rxGEOMETRY_PRELIT) && (flags & rxGEOMETRY_MODULATE) &&
                *(const RwUInt32 *)&mesh->material->color != 0xFFFFFFFF)
            {
                const RwRGBA    *color = &mesh->material->color;

                tFactor = ((RwUInt32)color->alpha << 24) | ((RwUInt32)color->red << 16) |
                          ((RwUInt32)color->green << 8) | (RwUInt32)color->blue;

                RwXboxSetCachedRenderState(D3DRS_TEXTUREFACTOR, tFactor);

                RwXboxSetCachedTextureStageState(1, D3DTSS_COLOROP, D3DTOP_MODULATE);
                RwXboxSetCachedTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TFACTOR);
                RwXboxSetCachedTextureStageState(1, D3DTSS_COLORARG2, D3DTA_CURRENT);
                RwXboxSetCachedTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
                RwXboxSetCachedTextureStageState(1, D3DTSS_ALPHAARG1, D3DTA_TFACTOR);
                RwXboxSetCachedTextureStageState(1, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
            }
        }

        RwXboxSetCurrentVertexShader(mesh->vertexShader);

        RwXboxDrawIndexedVertices((D3DPRIMITIVETYPE)resEntryHeader->primType, mesh->numIndices,
                                  mesh->indexBuffer);

        if (dualPass)
        {
            DWORD   lighting, zWriteEnable, fogEnabled, fogColor, srcBlend, destBlend;

            ApplyEnvMapTextureMatrix(envMapData->texture, 0, envMapData->frame);

            RwXboxSetCachedTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
            RwXboxSetCachedTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TFACTOR);
            RwXboxSetCachedTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TEXTURE);
            RwXboxSetCachedTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2);
            RwXboxSetCachedTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);
            RwXboxSetCachedTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
            RwXboxSetCachedTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);

            shinny |= (shinny << 8) | (shinny << 16) | (shinny << 24);
            RwXboxSetCachedRenderState(D3DRS_TEXTUREFACTOR, shinny);

            RwXboxGetCachedRenderState(D3DRS_LIGHTING, &lighting);
            RwXboxGetCachedRenderState(D3DRS_ZWRITEENABLE, &zWriteEnable);
            RwXboxGetCachedRenderState(D3DRS_FOGENABLE, &fogEnabled);

            RwXboxSetCachedRenderState(D3DRS_LIGHTING, FALSE);
            RwXboxSetCachedRenderState(D3DRS_ZWRITEENABLE, FALSE);

            if (fogEnabled)
            {
                RwXboxGetCachedRenderState(D3DRS_FOGCOLOR, &fogColor);
                RwXboxSetCachedRenderState(D3DRS_FOGCOLOR, 0);
            }

            RwXboxGetCachedRenderState(D3DRS_SRCBLEND, &srcBlend);
            RwXboxGetCachedRenderState(D3DRS_DESTBLEND, &destBlend);

            RwXboxSetCachedRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
            RwXboxSetCachedRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

            RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)TRUE);

            RwXboxSetCurrentPixelShader(0);

            RwXboxDrawIndexedVertices((D3DPRIMITIVETYPE)resEntryHeader->primType,
                                      mesh->numIndices, mesh->indexBuffer);

            if (fogEnabled)
            {
                RwXboxSetCachedRenderState(D3DRS_FOGCOLOR, fogColor);
            }

            RwXboxSetCachedRenderState(D3DRS_ZWRITEENABLE, zWriteEnable);
            RwXboxSetCachedRenderState(D3DRS_LIGHTING, lighting);
            RwXboxSetCachedRenderState(D3DRS_SRCBLEND, srcBlend);
            RwXboxSetCachedRenderState(D3DRS_DESTBLEND, destBlend);
        }
        else if ((flags & rxGEOMETRY_PRELIT) && (flags & rxGEOMETRY_MODULATE))
        {
            RwXboxSetCurrentPixelShader(0);
        }

        RwXboxSetCachedTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
        RwXboxSetCachedTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);
        RwXboxSetCachedTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
        RwXboxSetCachedTextureStageState(1, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
        RwXboxSetCachedTextureStageState(1, D3DTSS_TEXCOORDINDEX, 1);

        RwXboxRenderStateSetTexture(NULL, 1);
    }
    else
    {
        _rxXbDefaultRenderFFPMesh(resEntryHeader, mesh, flags);
    }
}

// match: __rxXbSetCachedTextureStates @ 0x002FB150
static void
_rxXbSetCachedTextureStates(const RpMatFXXboxStage *stValue, RwUInt32 stage)
{
    RwXboxSetCachedTextureStageState(stage, D3DTSS_BORDERCOLOR, stValue->borderColor);
    RwXboxSetCachedTextureStageState(stage, D3DTSS_COLORSIGN, stValue->colorSign);
    RwXboxSetCachedTextureStageState(stage, D3DTSS_ALPHAKILL, stValue->alphaKill);
    RwXboxSetCachedTextureStageState(stage, D3DTSS_BUMPENVMAT00, *(const DWORD *)&stValue->bumpEnvMat00);
    RwXboxSetCachedTextureStageState(stage, D3DTSS_BUMPENVMAT01, *(const DWORD *)&stValue->bumpEnvMat01);
    RwXboxSetCachedTextureStageState(stage, D3DTSS_BUMPENVMAT10, *(const DWORD *)&stValue->bumpEnvMat10);
    RwXboxSetCachedTextureStageState(stage, D3DTSS_BUMPENVMAT11, *(const DWORD *)&stValue->bumpEnvMat11);
}

// match: __rxXbSetCachedFixedCombinerStates @ 0x002FB310
static void
_rxXbSetCachedFixedCombinerStates(const RpMatFXXboxStage *stValue, RwUInt32 stage)
{
    RwXboxSetCachedTextureStageState(stage, D3DTSS_ALPHAOP, stValue->alphaOp);
    RwXboxSetCachedTextureStageState(stage, D3DTSS_ALPHAARG0, stValue->alphaArg0);
    RwXboxSetCachedTextureStageState(stage, D3DTSS_ALPHAARG1, stValue->alphaArg1);
    RwXboxSetCachedTextureStageState(stage, D3DTSS_ALPHAARG2, stValue->alphaArg2);
    RwXboxSetCachedTextureStageState(stage, D3DTSS_COLOROP, stValue->colorOp);
    RwXboxSetCachedTextureStageState(stage, D3DTSS_COLORARG0, stValue->colorArg0);
    RwXboxSetCachedTextureStageState(stage, D3DTSS_COLORARG1, stValue->colorArg1);
    RwXboxSetCachedTextureStageState(stage, D3DTSS_COLORARG2, stValue->colorArg2);
    RwXboxSetCachedTextureStageState(stage, D3DTSS_RESULTARG, stValue->resultArg);
}

// match: __rxXbResetCachedFixedCombinerStates @ 0x002FB550
static void
_rxXbResetCachedFixedCombinerStates(void)
{
    RwXboxSetCachedTextureStageState(0, D3DTSS_COLOROP, D3DTOP_DISABLE);
    RwXboxSetCachedTextureStageState(0, D3DTSS_RESULTARG, D3DTA_CURRENT);
    RwXboxSetCachedTextureStageState(0, D3DTSS_COLORSIGN, 0);
    RwXboxSetCachedTextureStageState(0, D3DTSS_ALPHAKILL, D3DTALPHAKILL_DISABLE);
    RwXboxSetCachedTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
    RwXboxSetCachedTextureStageState(1, D3DTSS_RESULTARG, D3DTA_CURRENT);
    RwXboxSetCachedTextureStageState(1, D3DTSS_COLORSIGN, 0);
    RwXboxSetCachedTextureStageState(1, D3DTSS_ALPHAKILL, D3DTALPHAKILL_DISABLE);
    RwXboxSetCachedTextureStageState(2, D3DTSS_COLOROP, D3DTOP_DISABLE);
    RwXboxSetCachedTextureStageState(2, D3DTSS_RESULTARG, D3DTA_CURRENT);
    RwXboxSetCachedTextureStageState(2, D3DTSS_COLORSIGN, 0);
    RwXboxSetCachedTextureStageState(2, D3DTSS_ALPHAKILL, D3DTALPHAKILL_DISABLE);
    RwXboxSetCachedTextureStageState(3, D3DTSS_COLOROP, D3DTOP_DISABLE);
    RwXboxSetCachedTextureStageState(3, D3DTSS_RESULTARG, D3DTA_CURRENT);
    RwXboxSetCachedTextureStageState(3, D3DTSS_COLORSIGN, 0);
    RwXboxSetCachedTextureStageState(3, D3DTSS_ALPHAKILL, D3DTALPHAKILL_DISABLE);
}

// match: __rxXbSetCachedFixedVertexStates @ 0x002FB7F0
static void
_rxXbSetCachedFixedVertexStates(const RpMatFXXboxStage *stValue, RwUInt32 stage,
                                RwUInt8 texCoord)
{
    if (stValue->texCoordIndex != (RwInt32)stage)
    {
        RwXboxSetCachedTextureStageState(stage, D3DTSS_TEXCOORDINDEX, stValue->texCoordIndex);
    }
    else
    {
        RwXboxSetCachedTextureStageState(stage, D3DTSS_TEXCOORDINDEX, texCoord);
    }

    RwXboxSetCachedTextureStageState(stage, D3DTSS_TEXTURETRANSFORMFLAGS,
                                     stValue->textureTransformFlags);

    if (stValue->textureTransformFlags)
    {
        D3DDevice_SetTransform(rxXbTexTrxTable[stage], &stValue->texTransformMatrix);
    }
}

// match: __rxXbResetCachedFixedVertexStates @ 0x002FB8C0
static void
_rxXbResetCachedFixedVertexStates(void)
{
    RwXboxSetCachedTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
    RwXboxSetCachedTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);
    RwXboxSetCachedTextureStageState(1, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
    RwXboxSetCachedTextureStageState(1, D3DTSS_TEXCOORDINDEX, 1);
    RwXboxSetCachedTextureStageState(2, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
    RwXboxSetCachedTextureStageState(2, D3DTSS_TEXCOORDINDEX, 2);
    RwXboxSetCachedTextureStageState(3, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
    RwXboxSetCachedTextureStageState(3, D3DTSS_TEXCOORDINDEX, 3);
}

static void
_rxXbSetCachedMiscStates(const RpMatFXXboxMiscState *miscState)
{
    RwXboxSetCachedRenderState(D3DRS_TEXTUREFACTOR, miscState->textureFactor);
}

// match: __rxXbSetCachedFinalBlend @ 0x002FBA40
static void
_rxXbSetCachedFinalBlend(const RpMatFXXboxFinalBlend *finalBlend)
{
    RwXboxSetCachedRenderState(D3DRS_SRCBLEND, finalBlend->srcBlend);
    RwXboxSetCachedRenderState(D3DRS_DESTBLEND, finalBlend->dstBlend);
}

// match: __rpMatFXMTRenderStateSetUp @ 0x002FBAB0
void
_rpMatFXMTRenderStateSetUp(RwBool useVertexShader,
                           RpMultiTexture *multiTexture,
                           RpAtomic *atomic __RWUNUSED__,
                           RxXboxInstanceData *mesh)
{
    RpMatFXXboxMaterial *xboxMat;
    RwUInt32            i;

    xboxMat = RpXboxMTEffectGetConfig(multiTexture->effect);

    for (i = 0; i < multiTexture->numTextures; i++)
    {
        RwXboxRenderStateSetTexture(multiTexture->textures[i], i);
    }

    for (i = 0; i < (RwUInt32)xboxMat->nbStages; i++)
    {
        if (xboxMat->stages[i].alphaOp != D3DTOP_DISABLE &&
            xboxMat->stages[i].colorOp != D3DTOP_DISABLE)
        {
            _rxXbSetCachedTextureStates(&xboxMat->stages[i], i);
            _rxXbSetCachedFixedCombinerStates(&xboxMat->stages[i], i);

            if (!useVertexShader)
            {
                _rxXbSetCachedFixedVertexStates(&xboxMat->stages[i], i,
                                                multiTexture->coordMap[i]);
            }
        }
    }

    _rxXbSetCachedMiscStates(&xboxMat->miscState);

    RwXboxGetCachedRenderState(D3DRS_SRCBLEND, &MatFXMTOldSrcBlend);
    RwXboxGetCachedRenderState(D3DRS_DESTBLEND, &MatFXMTOldDestBlend);

    if (mesh->material->color.alpha != 0xFF)
    {
        RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)TRUE);
        _rxXbSetCachedFinalBlend(&xboxMat->blend);
    }
    else
    {
        RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)FALSE);
    }

    RwXboxSetCurrentPixelShader(RpXboxMaterialGetPixelShader(mesh->material));

    if (!useVertexShader)
    {
        RwXboxSetCurrentVertexShader(mesh->vertexShader);
    }
}

// match: __rpMatFXMTRenderStateCleanUp @ 0x002FBBF0
void
_rpMatFXMTRenderStateCleanUp(RwBool useVertexShader, RpMultiTexture *multiTexture)
{
    RwUInt32    i;

    RpXboxMTEffectGetConfig(multiTexture->effect);

    _rxXbResetCachedFixedCombinerStates();

    if (!useVertexShader)
    {
        _rxXbResetCachedFixedVertexStates();
    }

    RwXboxSetCachedRenderState(D3DRS_SRCBLEND, MatFXMTOldSrcBlend);
    RwXboxSetCachedRenderState(D3DRS_DESTBLEND, MatFXMTOldDestBlend);

    for (i = 0; i < multiTexture->numTextures; i++)
    {
        RwXboxRenderStateSetTexture(NULL, i);
    }
}

// match: _rxXbAtomicMatFXRenderCallback @ 0x002FBCA0
void
rxXbAtomicMatFXRenderCallback(RxXboxResEntryHeader *resEntryHeader,
                              void *object,
                              RwUInt8 type,
                              RwUInt32 flags)
{
    static const RwMatrix Identity =
    {
        { 1.0f, 0.0f, 0.0f }, rwMATRIXTYPEORTHONORMAL | rwMATRIXINTERNALIDENTITY,
        { 0.0f, 1.0f, 0.0f }, 0,
        { 0.0f, 0.0f, 1.0f }, 0,
        { 0.0f, 0.0f, 0.0f }, 0
    };
    const RwMatrix      *transform;
    const RpXboxVtxFmt  *format;
    RxXboxInstanceData  *mesh;

    if (type == rpATOMIC)
    {
        RpAtomic    *atomic = (RpAtomic *)object;

        transform = RwFrameGetLTM(RpAtomicGetFrame(atomic));
        format = RpXboxGeometryGetVtxFmt(RpAtomicGetGeometry(atomic));
    }
    else
    {
        transform = &Identity;
        format = RpXboxWorldGetVtxFmt(RpWorldSectorGetWorld((RpWorldSector *)object));
    }

    _rxXbDefaultRenderFFPObjectSetUp(resEntryHeader, object, type, flags);

    D3DDevice_SetStreamSource(0, (D3DVertexBuffer *)resEntryHeader->vertexBuffer,
                              resEntryHeader->stride);

    for (mesh = resEntryHeader->begin; mesh != resEntryHeader->end; mesh++)
    {
        RpMultiTexture  *multiTexture;

        _rxXbDefaultRenderFFPMeshSetUp(mesh);

        multiTexture = RpMaterialGetMultiTexture(mesh->material, rwID_XBOX);

        if (multiTexture && multiTexture->effect && multiTexture->effect->platformID == rwID_XBOX)
        {
            RpXboxMTEffectGetConfig(multiTexture->effect);

            _rpMatFXMTRenderStateSetUp(FALSE, multiTexture, (RpAtomic *)object, mesh);

            RwXboxDrawIndexedVertices((D3DPRIMITIVETYPE)resEntryHeader->primType,
                                      mesh->numIndices, mesh->indexBuffer);

            _rpMatFXMTRenderStateCleanUp(FALSE, multiTexture);
        }
        else
        {
            const rpMatFXMaterialData   *matFXData = *MATFXMATERIALGETDATA(mesh->material);
            RpMatFXMaterialFlags        effect;

            if (NULL == matFXData)
            {
                effect = rpMATFXEFFECTNULL;
            }
            else
            {
                effect = matFXData->flags;
            }

            switch (effect)
            {
                case rpMATFXEFFECTENVMAP:
                    rxXbAtomicMatFXEnvRender(resEntryHeader, mesh, flags);
                    break;

                case rpMATFXEFFECTBUMPMAP:
                    rxXbAtomicMatFXBumpMapRender(format, resEntryHeader, mesh, matFXData, flags,
                                                 transform);
                    break;

                case rpMATFXEFFECTDUAL:
                case rpMATFXEFFECTDUALUVTRANSFORM:
                    rxXbAtomicMatFXDualPassRender(resEntryHeader, mesh, matFXData, flags);
                    break;

                case rpMATFXEFFECTBUMPENVMAP:
                    rxXbAtomicMatFXBumpEnvMapRender(format, resEntryHeader, mesh, matFXData,
                                                    flags, transform);
                    break;

                case rpMATFXEFFECTUVTRANSFORM:
                    ApplyAnimTextureMatrix(0, matFXData->data[rpSECONDPASS].data.uvAnim.baseTransform);
                    _rxXbDefaultRenderFFPMesh(resEntryHeader, mesh, flags);
                    RwXboxSetCachedTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
                    break;

                default:
                    _rxXbDefaultRenderFFPMesh(resEntryHeader, mesh, flags);
                    break;
            }
        }
    }
}

// match: _rpAtomicMatFxPipelineCreate @ 0x002FBE70
static RxPipeline *
rpAtomicMatFxPipelineCreate(void)
{
    RxPipeline  *pipe;

    pipe = RxPipelineCreate();
    if (pipe)
    {
        RxLockedPipe    *lpipe;

        pipe->pluginId = rwID_MATERIALEFFECTSPLUGIN;
        if (NULL != (lpipe = RxPipelineLock(pipe)))
        {
            RxNodeDefinition    *instanceNode = RxNodeDefinitionGetXboxAtomicAllInOne();

            lpipe = RxLockedPipeAddFragment(lpipe, NULL, instanceNode, NULL);

            RxLockedPipeUnlock(lpipe);

            return pipe;
        }

        RxPipelineDestroy(pipe);
    }

    return NULL;
}

// match: _rpWorldSectorMatFxPipelineCreate @ 0x002FBEC0
static RxPipeline *
rpWorldSectorMatFxPipelineCreate(void)
{
    RxPipeline  *pipe;

    pipe = RxPipelineCreate();
    if (pipe)
    {
        RxLockedPipe    *lpipe;

        pipe->pluginId = rwID_MATERIALEFFECTSPLUGIN;
        if (NULL != (lpipe = RxPipelineLock(pipe)))
        {
            RxNodeDefinition    *instanceNode = RxNodeDefinitionGetXboxWorldSectorAllInOne();

            lpipe = RxLockedPipeAddFragment(lpipe, NULL, instanceNode, NULL);

            RxLockedPipeUnlock(lpipe);

            return pipe;
        }

        RxPipelineDestroy(pipe);
    }

    return NULL;
}

// match: __rpMatFXPipelinesCreate @ 0x002FBF10
RwBool
_rpMatFXPipelinesCreate(void)
{
    RxPipelineNode  *node;
    RwUInt32        i;

    MatFXAtomicPipe = rpAtomicMatFxPipelineCreate();

    node = RxPipelineFindNodeByName(MatFXAtomicPipe,
                                    RxNodeDefinitionGetXboxAtomicAllInOne()->name,
                                    NULL, NULL);

    instancePipeline = _rxXboxAllInOneGetInstanceCallBack(node);
    _rxXboxAllInOneSetInstanceCallBack(node, XbAtomicMatFXInstanceCallback);
    _rxXboxAllInOneSetRenderCallBack(node, rxXbAtomicMatFXRenderCallback);

    MatFXWorldSectorPipe = rpWorldSectorMatFxPipelineCreate();

    node = RxPipelineFindNodeByName(MatFXWorldSectorPipe,
                                    RxNodeDefinitionGetXboxWorldSectorAllInOne()->name,
                                    NULL, NULL);

    worldInstancePipeline = _rxXboxAllInOneGetInstanceCallBack(node);
    _rxXboxAllInOneSetInstanceCallBack(node, XbWorldSectorMatFXInstanceCallback);
    _rxXboxAllInOneSetRenderCallBack(node, rxXbAtomicMatFXRenderCallback);

    D3DDevice_CreatePixelShader((D3DPIXELSHADERDEF *)dwEnvmapPixelShader,
                                &EnvMapPixelShader);
    D3DDevice_CreatePixelShader((D3DPIXELSHADERDEF *)dwEnvmapnobasePixelShader,
                                &EnvMapNoBaseTexturePixelShader);
    D3DDevice_CreatePixelShader((D3DPIXELSHADERDEF *)dwBumpmapPixelShader,
                                &BumpMapPixelShader);
    D3DDevice_CreatePixelShader((D3DPIXELSHADERDEF *)dwBumpenvmapPixelShader,
                                &BumpEnvMapPixelShader);
    D3DDevice_CreatePixelShader((D3DPIXELSHADERDEF *)dwBumpenvmapalphaPixelShader,
                                &BumpEnvMapAlphaPixelShader);
    D3DDevice_CreatePixelShader((D3DPIXELSHADERDEF *)dwBumpmapnomatcolorPixelShader,
                                &BumpMapNomatcolorPixelShader);
    D3DDevice_CreatePixelShader((D3DPIXELSHADERDEF *)dwBumpenvmapnomatcolorPixelShader,
                                &BumpEnvMapNomatcolorPixelShader);
    D3DDevice_CreatePixelShader((D3DPIXELSHADERDEF *)dwBumpenvmapnomatcoloralphaPixelShader,
                                &BumpEnvMapNomatcolorAlphaPixelShader);

    for (i = 0; i < NUMBUMPMAPSHADERS; i++)
    {
        BumpMapVertexShaders[i].handle = 0;
    }

    BumpMapNumShaders = 0;
    BumpMapNextShader = 0;

    return TRUE;
}

// match: __rpMatFXPipelinesDestroy @ 0x002FC060
RwBool
_rpMatFXPipelinesDestroy(void)
{
    RwUInt32    i;

    for (i = 0; i < BumpMapNumShaders; i++)
    {
        if (BumpMapVertexShaders[i].handle)
        {
            D3DDevice_DeleteVertexShader(BumpMapVertexShaders[i].handle);
            BumpMapVertexShaders[i].handle = 0;
        }
    }

    BumpMapNumShaders = 0;
    BumpMapNextShader = 0;

    D3DDevice_DeletePixelShader(BumpMapNomatcolorPixelShader);
    D3DDevice_DeletePixelShader(BumpEnvMapNomatcolorPixelShader);
    D3DDevice_DeletePixelShader(BumpEnvMapNomatcolorAlphaPixelShader);
    D3DDevice_DeletePixelShader(BumpMapPixelShader);
    D3DDevice_DeletePixelShader(BumpEnvMapPixelShader);
    D3DDevice_DeletePixelShader(BumpEnvMapAlphaPixelShader);
    D3DDevice_DeletePixelShader(EnvMapPixelShader);
    D3DDevice_DeletePixelShader(EnvMapNoBaseTexturePixelShader);

    if (MatFXAtomicPipe)
    {
        RxPipelineDestroy(MatFXAtomicPipe);
        MatFXAtomicPipe = NULL;
    }

    if (MatFXWorldSectorPipe)
    {
        RxPipelineDestroy(MatFXWorldSectorPipe);
        MatFXWorldSectorPipe = NULL;
    }

    return TRUE;
}

// match: __rpMatFXPipelineWorldSectorSetup @ 0x002FC140
RpWorldSector *
_rpMatFXPipelineWorldSectorSetup(RpWorldSector *worldSector)
{
    return RpWorldSectorSetPipeline(worldSector, MatFXWorldSectorPipe);
}

// match: __rpMatFXPipelineAtomicSetup @ 0x002FC150
RpAtomic *
_rpMatFXPipelineAtomicSetup(RpAtomic *atomic)
{
    return RpAtomicSetPipeline(atomic, MatFXAtomicPipe);
}

/* The device's dual-pass render state: nothing to set up on Xbox. /OPT:ICF folded
 * it into _rwPipeAttach's body (`return TRUE`, 0x2B8CB0). */
RwBool
_rpMatFXSetupDualRenderState(MatFXDualData *dualData __RWUNUSEDRELEASE__,
                             RwRenderState nState __RWUNUSEDRELEASE__)
{
    return TRUE;
}
