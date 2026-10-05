/*
 * codfh-match: RenderWare 3.6's Xbox skin rendering, rebuilt from the
 * image; the file name is the image's RCS id string's, names and shapes the
 * Godfather PDB's copy. The generated vertex shaders are cached by key,
 * the least recently used one replaced when the cache is full.
 */

#include <xtl.h>
#include <string.h>

#include <rwcore.h>
#include <rpworld.h>

#include "skin.h"

#include "skinxbox.h"

/* A cached skin vertex shader. */
typedef struct _rpSkinXboxShaderItemDesc _rpSkinXboxShaderItemDesc;
struct _rpSkinXboxShaderItemDesc
{
    _rpSkinXboxShaderDesc   desc;
    RwUInt32                renderFrame;
    const DWORD            *byteCode;
};

#define rpSKINXBOXSHADERCACHESIZE 256

static RwInt32 lastFormatIndex;
static const DWORD *lastShader;
static _rpSkinXboxShaderItemDesc VertexShaderCache[rpSKINXBOXSHADERCACHESIZE];

static _rpSkinXboxShaderItemDesc *LastVertexShaderDesc = VertexShaderCache;

static RwBool shadersInited;
static RwInt32 NumShadersInCache;

// match: __rpSkinXboxPurgeShaderCache @ 0x002D1840
void
_rpSkinXboxPurgeShaderCache(void)
{
    lastShader = (const DWORD *)-1;
    lastFormatIndex = -1;
}

// match: __rpSkinXboxInitShaders @ 0x002D1850
RwBool
_rpSkinXboxInitShaders(void)
{
    if (!shadersInited)
    {
        shadersInited = TRUE;

        _rpSkinXboxVertexFormatCreate();

        _rpSkinXboxPurgeShaderCache();

        memset(VertexShaderCache, 0, sizeof(VertexShaderCache));
    }

    return TRUE;
}

// match: __rpSkinXboxSetShader @ 0x002D1890
void
_rpSkinXboxSetShader(DWORD formatIndex, const DWORD *shader)
{
    if ((RwInt32)formatIndex != lastFormatIndex || shader != lastShader)
    {
        lastFormatIndex = formatIndex;
        lastShader = shader;

        D3DDevice_LoadVertexShaderProgram(shader, 12);
        D3DDevice_SelectVertexShader(formatIndex, 12);
    }
}

// match: _D3DMATRIXFromRwMatrix @ 0x002D21C0
static void
D3DMATRIXFromRwMatrix(D3DMATRIX *d, const RwMatrix *m)
{
    RwReal  *dst = (RwReal *)d;

    *dst++ = m->right.x;
    *dst++ = m->up.x;
    *dst++ = m->at.x;
    *dst++ = m->pos.x;

    *dst++ = m->right.y;
    *dst++ = m->up.y;
    *dst++ = m->at.y;
    *dst++ = m->pos.y;

    *dst++ = m->right.z;
    *dst++ = m->up.z;
    *dst++ = m->at.z;
    *dst = m->pos.z;
}

// match: __rpSkinXboxMatrixUpdate @ 0x002D2230
void
_rpSkinXboxMatrixUpdate(RwV4d *shaderConstants, RpAtomic *atomic, RpSkin *skin)
{
    RpHAnimHierarchy    *hierarchy = RPSKINATOMICGETDATA(atomic)->hierarchy;
    RwMatrix            result;
    RwInt32             i;

    if (hierarchy)
    {
        const RwMatrix  *matrixArray = hierarchy->pMatrixArray;
        const RwMatrix  *skinToBone = RpSkinGetSkinToBoneMatrices(skin);

        if (hierarchy->flags & rpHANIMHIERARCHYNOMATRICES)
        {
            RpHAnimNodeInfo *frameInfo = hierarchy->pNodeInfo;
            RwMatrix        inverseLtm;
            RwMatrix        tempMatrix;
            RwV4d           *constants;

            rwMatrixInitialize(&inverseLtm, 0);
            rwMatrixInitialize(&tempMatrix, 0);

            RwMatrixInvert(&inverseLtm, RwFrameGetLTM(RpAtomicGetFrame(atomic)));

            constants = shaderConstants;
            for (i = 0; i < skin->platformData.numBonesUsed; i++)
            {
                RwInt32 bone = skin->platformData.matrixIndexMap[i];

                RwMatrixMultiply(&tempMatrix, &skinToBone[bone],
                                 RwFrameGetLTM(frameInfo[bone].pFrame));
                RwMatrixMultiply(&result, &tempMatrix, &inverseLtm);

                D3DMATRIXFromRwMatrix((D3DMATRIX *)constants, &result);

                constants += 3;
            }
        }
        else if (hierarchy->flags & rpHANIMHIERARCHYLOCALSPACEMATRICES)
        {
            RwV4d   *constants = shaderConstants;

            for (i = 0; i < skin->platformData.numBonesUsed; i++)
            {
                RwInt32 bone = skin->platformData.matrixIndexMap[i];

                RwMatrixMultiply(&result, &skinToBone[bone], &matrixArray[bone]);

                D3DMATRIXFromRwMatrix((D3DMATRIX *)constants, &result);

                constants += 3;
            }
        }
        else
        {
            RwMatrix        inverseLtm;
            RwMatrix        tempMatrix;
            RwV4d           *constants;

            rwMatrixInitialize(&inverseLtm, 0);

            RwMatrixInvert(&inverseLtm, RwFrameGetLTM(RpAtomicGetFrame(atomic)));

            constants = shaderConstants;
            for (i = 0; i < skin->platformData.numBonesUsed; i++)
            {
                RwInt32 bone = skin->platformData.matrixIndexMap[i];

                RwMatrixMultiply(&tempMatrix, &skinToBone[bone], &matrixArray[bone]);
                RwMatrixMultiply(&result, &tempMatrix, &inverseLtm);

                D3DMATRIXFromRwMatrix((D3DMATRIX *)constants, &result);

                constants += 3;
            }
        }
    }
    else
    {
        RwReal  *dst = (RwReal *)shaderConstants;

        for (i = 0; i < skin->platformData.numBonesUsed; i++)
        {
            *dst++ = 1.0f;
            *dst++ = 0.0f;
            *dst++ = 0.0f;
            *dst++ = 0.0f;

            *dst++ = 0.0f;
            *dst++ = 1.0f;
            *dst++ = 0.0f;
            *dst++ = 0.0f;

            *dst++ = 0.0f;
            *dst++ = 0.0f;
            *dst++ = 1.0f;
            *dst++ = 0.0f;
        }
    }
}

// match: __rpSkinXboxCreateAtomicPipeline @ 0x002D2660
RxPipeline *
_rpSkinXboxCreateAtomicPipeline(void)
{
    RxPipeline  *pipe;

    pipe = RxPipelineCreate();
    if (pipe)
    {
        RxLockedPipe    *lpipe;

        lpipe = RxPipelineLock(pipe);
        if (NULL != lpipe)
        {
            RxNodeDefinition    *instanceNode = RxNodeDefinitionGetXboxSkinAtomicAllInOne();

            lpipe = RxLockedPipeAddFragment(lpipe, NULL, instanceNode, NULL);

            RxLockedPipeUnlock(lpipe);

            return pipe;
        }

        RxPipelineDestroy(pipe);
    }

    return NULL;
}

// match: _RpXboxSkinVertexShaderCachePurge @ 0x002D32A0
void
RpXboxSkinVertexShaderCachePurge(void)
{
    RwInt32 i;

    for (i = 0; i < NumShadersInCache; i++)
    {
        if (VertexShaderCache[i].byteCode)
        {
            RwFree((void *)VertexShaderCache[i].byteCode);
            VertexShaderCache[i].byteCode = NULL;
        }
    }

    NumShadersInCache = 0;

    LastVertexShaderDesc = VertexShaderCache;

    LastVertexShaderDesc->desc.numWeights = 0;
    LastVertexShaderDesc->desc.numDirect = 0;
    LastVertexShaderDesc->desc.numPoint = 0;
    LastVertexShaderDesc->desc.matfx = 0;
    LastVertexShaderDesc->desc.bnt = 0;
    LastVertexShaderDesc->desc.prelit = 0;
}

// match: __rpSkinXboxDestroyShaders @ 0x002D3310
void
_rpSkinXboxDestroyShaders(void)
{
    if (shadersInited)
    {
        shadersInited = FALSE;

        _rpSkinXboxVertexFormatDestroy();

        _rpSkinXboxPurgeShaderCache();
    }

    RpXboxSkinVertexShaderCachePurge();
}
