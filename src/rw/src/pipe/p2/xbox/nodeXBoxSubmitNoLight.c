/*
 * codfh-match: RenderWare 3.6's Xbox Im3D nodes
 * (src/pipe/p2/xbox/nodeXBoxSubmitNoLight.c), rebuilt from the image after
 * 3.7.2's nodeD3D8SubmitNoLight.c; names from the Godfather PDB's copy.
 */

/****************************************************************************
 includes
 */

#include <xtl.h>

#include "batypes.h"
#include "bapipe.h"
#include "p2core.h"
#include "p2stdcls.h"
#include "baim3d.h"

#include "xbcache.h"
#include "xbmemory.h"
#include "xbrendst.h"

#include "nodeXBoxSubmitNoLight.h"

/* RenderWare 3.6's RCS id string, which the image keeps (the 3.7.2 tree has none) */
static const char rcsid[] = "@@@@(#)$Id: //RenderWare/RW36Active/rwsdk/src/pipe/p2/xbox/nodeXBoxSubmitNoLight.c#1 $";

/****************************************************************************
 local defines
 */

#define IM3D_FVF        (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define IM3D_NOTEX_FVF  (D3DFVF_XYZ | D3DFVF_DIFFUSE)

#define IM3D_PUSHMAX    0x2000

/* The Xbox object-space vertex (the Godfather PDB's RxObjSpace3DVertex). */
typedef struct _rxXbObjSpace3DVertex _rxXbObjSpace3DVertex;
struct _rxXbObjSpace3DVertex
{
    RwV3d       pos;
    RwV3d       normal;
    RwUInt32    emissiveColor;
    RwReal      u;
    RwReal      v;
};

typedef struct _rxXbIm3DVertex _rxXbIm3DVertex;
struct _rxXbIm3DVertex
{
    RwReal      x;
    RwReal      y;
    RwReal      z;
    RwUInt32    color;
    RwReal      u;
    RwReal      v;
};

typedef struct _rxXbIm3DVertexNoTex _rxXbIm3DVertexNoTex;
struct _rxXbIm3DVertexNoTex
{
    RwReal      x;
    RwReal      y;
    RwReal      z;
    RwUInt32    color;
};

/****************************************************************************
 Global variables
 */

D3DPRIMITIVETYPE RwXbPrimConv[6] =
{
    (D3DPRIMITIVETYPE)0,    /* rwPRIMTYPENAPRIMTYPE */
    D3DPT_LINELIST,         /* rwPRIMTYPELINELIST */
    D3DPT_LINESTRIP,        /* rwPRIMTYPEPOLYLINE */
    D3DPT_TRIANGLELIST,     /* rwPRIMTYPETRILIST */
    D3DPT_TRIANGLESTRIP,    /* rwPRIMTYPETRISTRIP */
    D3DPT_TRIANGLEFAN       /* rwPRIMTYPETRIFAN */
};

/****************************************************************************
 Local static variables
 */

static const rwIm3DPool *rwXbImmPool = NULL;

/****************************************************************************
 XbSubmitNode
*/
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: _rcsid @ 0x00417418
// match: _RwXbPrimConv @ 0x00435728
// match: ?_ImmInstance_csl@?1??RxNodeDefinitionGetXboxImmInstance@@9@9 @ 0x00435740
// match: ?nodeImmInstanceCSL@?1??RxNodeDefinitionGetXboxImmInstance@@9@9 @ 0x00435750
// match: ?_SubmitNoLight_csl@?1??RxNodeDefinitionGetXboxSubmitNoLight@@9@9 @ 0x00435790
// match: ?nodeXBoxSubmitNoLightCSL@?1??RxNodeDefinitionGetXboxSubmitNoLight@@9@9 @ 0x004357A8

// match: _XbSubmitNode @ 0x002BC460

static RwBool
XbSubmitNode(RxPipelineNodeInstance *self __RWUNUSED__,
             const RxPipelineNodeParam *params __RWUNUSED__)
{
    const _rwIm3DPoolStash  *stash;
    D3DMATRIX               matrix;
    RwUInt32                fvf;
    RwUInt32                stride;
    RwBool                  indexed;
    RwUInt32                totalSize;
    RwUInt32                n;

    stash = &rwXbImmPool->stash;

    /* World matrix */
    if (stash->ltm && !rwMatrixTestFlags(stash->ltm, rwMATRIXINTERNALIDENTITY))
    {
        matrix._11 = stash->ltm->right.x;
        matrix._12 = stash->ltm->right.y;
        matrix._13 = stash->ltm->right.z;
        matrix._14 = 0.0f;

        matrix._21 = stash->ltm->up.x;
        matrix._22 = stash->ltm->up.y;
        matrix._23 = stash->ltm->up.z;
        matrix._24 = 0.0f;

        matrix._31 = stash->ltm->at.x;
        matrix._32 = stash->ltm->at.y;
        matrix._33 = stash->ltm->at.z;
        matrix._34 = 0.0f;

        matrix._41 = stash->ltm->pos.x;
        matrix._42 = stash->ltm->pos.y;
        matrix._43 = stash->ltm->pos.z;
        matrix._44 = 1.0f;
    }
    else
    {
        matrix._11 = 1.0f;
        matrix._12 = 0.0f;
        matrix._13 = 0.0f;
        matrix._14 = 0.0f;

        matrix._21 = 0.0f;
        matrix._22 = 1.0f;
        matrix._23 = 0.0f;
        matrix._24 = 0.0f;

        matrix._31 = 0.0f;
        matrix._32 = 0.0f;
        matrix._33 = 1.0f;
        matrix._34 = 0.0f;

        matrix._41 = 0.0f;
        matrix._42 = 0.0f;
        matrix._43 = 0.0f;
        matrix._44 = 1.0f;
    }

    D3DDevice_SetTransform(D3DTS_WORLD, &matrix);

    /* Disable lighting */
    _rwXbRenderStateForce(D3DRS_LIGHTING, FALSE);

    /* Disable any pixel shader */
    RwXboxSetCurrentPixelShader(0);

    _rwXbTextureStageForce(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
    _rwXbTextureStageForce(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
    _rwXbTextureStageForce(0, D3DTSS_COLORARG2, D3DTA_TEXTURE);
    _rwXbTextureStageForce(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
    _rwXbTextureStageForce(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
    _rwXbTextureStageForce(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);

    /* Check vertex type */
    if (stash->flags & rwIM3D_VERTEXUV)
    {
        fvf = IM3D_FVF;
        stride = sizeof(_rxXbIm3DVertex);
    }
    else
    {
        fvf = IM3D_NOTEX_FVF;
        stride = sizeof(_rxXbIm3DVertexNoTex);
    }

    RwXboxSetCurrentVertexShader(fvf);

    indexed = (stash->indices != NULL && stash->numIndices > 0);

    totalSize = stride * rwXbImmPool->numElements;

    if (indexed || totalSize >= IM3D_PUSHMAX)
    {
        RwUInt8    *bufferMem;

        bufferMem = RwXboxLockDynamicVertexBuffer(totalSize);

        if (stash->flags & rwIM3D_VERTEXUV)
        {
            const _rxXbObjSpace3DVertex *source;
            _rxXbIm3DVertex             *dest;

            source = (const _rxXbObjSpace3DVertex *)rwXbImmPool->elements;
            dest = (_rxXbIm3DVertex *)bufferMem;
            for (n = 0; n < rwXbImmPool->numElements; n++)
            {
                dest->x = source->pos.x;
                dest->y = source->pos.y;
                dest->z = source->pos.z;
                dest->color = source->emissiveColor;
                dest->u = source->u;
                dest->v = source->v;

                source++;
                dest++;
            }
        }
        else
        {
            const _rxXbObjSpace3DVertex *source;
            _rxXbIm3DVertexNoTex        *dest;

            source = (const _rxXbObjSpace3DVertex *)rwXbImmPool->elements;
            dest = (_rxXbIm3DVertexNoTex *)bufferMem;
            for (n = 0; n < rwXbImmPool->numElements; n++)
            {
                dest->x = source->pos.x;
                dest->y = source->pos.y;
                dest->z = source->pos.z;
                dest->color = source->emissiveColor;

                source++;
                dest++;
            }
        }

        RwXboxSetCurrentStream(stride);

        if (indexed)
        {
            RwXboxDrawIndexedVertices(RwXbPrimConv[stash->primType],
                                      stash->numIndices, stash->indices);
        }
        else
        {
            RwXboxDrawVertices(RwXbPrimConv[stash->primType], 0,
                               rwXbImmPool->numElements);
        }
    }
    else
    {
        RwUInt32    pushSizeInDWORDs;
        DWORD      *pPush;

        pushSizeInDWORDs = totalSize >> 2;

        _rwXbFlushCacheBuffer();

        pPush = D3DDevice_BeginPush(pushSizeInDWORDs + 5);

        *pPush++ = D3DPUSH_ENCODE(D3DPUSH_SET_BEGIN_END, 1);
        *pPush++ = RwXbPrimConv[stash->primType];
        *pPush++ = D3DPUSH_ENCODE(D3DPUSH_NOINCREMENT_FLAG | D3DPUSH_INLINE_ARRAY, pushSizeInDWORDs);

        if (stash->flags & rwIM3D_VERTEXUV)
        {
            const _rxXbObjSpace3DVertex *source;
            _rxXbIm3DVertex             *dest;

            source = (const _rxXbObjSpace3DVertex *)rwXbImmPool->elements;
            dest = (_rxXbIm3DVertex *)pPush;
            for (n = 0; n < rwXbImmPool->numElements; n++)
            {
                dest->x = source->pos.x;
                dest->y = source->pos.y;
                dest->z = source->pos.z;
                dest->color = source->emissiveColor;
                dest->u = source->u;
                dest->v = source->v;

                source++;
                dest++;
            }

            pPush = (DWORD *)dest;
        }
        else
        {
            const _rxXbObjSpace3DVertex *source;
            _rxXbIm3DVertexNoTex        *dest;

            source = (const _rxXbObjSpace3DVertex *)rwXbImmPool->elements;
            dest = (_rxXbIm3DVertexNoTex *)pPush;
            for (n = 0; n < rwXbImmPool->numElements; n++)
            {
                dest->x = source->pos.x;
                dest->y = source->pos.y;
                dest->z = source->pos.z;
                dest->color = source->emissiveColor;

                source++;
                dest++;
            }

            pPush = (DWORD *)dest;
        }

        *pPush++ = D3DPUSH_ENCODE(D3DPUSH_SET_BEGIN_END, 1);
        *pPush++ = 0;

        D3DDevice_EndPush(pPush);
    }

    return TRUE;
}

/****************************************************************************
 XbImmInstanceNode
*/
// match: _XbImmInstanceNode @ 0x002BC8D0
static RwBool
XbImmInstanceNode(RxPipelineNodeInstance *self __RWUNUSED__,
                  const RxPipelineNodeParam *params)
{
    rwXbImmPool = (const rwIm3DPool *)RxPipelineNodeParamGetData(params);

    return TRUE;
}

/****************************************************************************
 RxNodeDefinitionGetXboxImmInstance
*/
// match: _RxNodeDefinitionGetXboxImmInstance @ 0x002BC8F0
RxNodeDefinition *
RxNodeDefinitionGetXboxImmInstance(void)
{
    static RwChar   _ImmInstance_csl[] = RWSTRING("ImmInstance.csl");
    static RxNodeDefinition nodeImmInstanceCSL = {
        _ImmInstance_csl,           /* Name */
        {                           /* Nodemethods */
            XbImmInstanceNode,      /* +-- nodebody */
            NULL,                   /* +-- nodeinit */
            NULL,                   /* +-- nodeterm */
            NULL,                   /* +-- pipelinenodeinit */
            NULL,                   /* +-- pipelineNodeTerm */
            NULL,                   /* +-- pipelineNodeConfig */
            NULL,                   /* +-- configMsgHandler */
        },
        {                           /* Io */
            0,                      /* +-- NumClustersOfInterest */
            NULL,                   /* +-- ClustersOfInterest */
            NULL,                   /* +-- InputRequirements */
            0,                      /* +-- NumOutputs */
            NULL                    /* +-- Outputs */
        },
        0,                          /* PipelineNodePrivateDataSize */
        rxNODEDEFCONST,             /* editable */
        0                           /* inPipes */
    };

    RWAPIFUNCTION(RWSTRING("RxNodeDefinitionGetXboxImmInstance"));

    RWRETURN((&nodeImmInstanceCSL));
}

/****************************************************************************
 RxNodeDefinitionGetXboxSubmitNoLight
*/
// match: _RxNodeDefinitionGetXboxSubmitNoLight @ 0x002BC900
RxNodeDefinition *
RxNodeDefinitionGetXboxSubmitNoLight(void)
{
    static RwChar _SubmitNoLight_csl[] = "XboxSubmitNoLight.csl";
    static RxNodeDefinition nodeXBoxSubmitNoLightCSL = {
        _SubmitNoLight_csl,         /* Name */
        {                           /* Nodemethods */
            XbSubmitNode,           /* +-- nodebody */
            NULL,                   /* +-- nodeinit */
            NULL,                   /* +-- nodeterm */
            NULL,                   /* +-- pipelinenodeinit */
            NULL,                   /* +-- pipelineNodeTerm */
            NULL,                   /* +-- pipelineNodeConfig */
            NULL,                   /* +-- configMsgHandler */
        },
        {                           /* Io */
            0,                      /* +-- NumClustersOfInterest */
            NULL,                   /* +-- ClustersOfInterest */
            NULL,                   /* +-- InputRequirements */
            0,                      /* +-- NumOutputs */
            NULL                    /* +-- Outputs */
        },
        0,                          /* PipelineNodePrivateDataSize */
        rxNODEDEFCONST,             /* editable */
        0                           /* inPipes */
    };

    RWAPIFUNCTION(RWSTRING("RxNodeDefinitionGetXboxSubmitNoLight"));

    RWRETURN(&nodeXBoxSubmitNoLightCSL);
}
