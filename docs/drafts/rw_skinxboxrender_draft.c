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

extern const DWORD *_rpSkinXboxGenerateShader(const _rpSkinXboxShaderDesc *desc);

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
            lpipe = RxLockedPipeAddFragment(lpipe, NULL,
                                            RxNodeDefinitionGetXboxSkinAtomicAllInOne(),
                                            NULL);

            RxLockedPipeUnlock(lpipe);

            return pipe;
        }

        RxPipelineDestroy(pipe);
    }

    return NULL;
}

// match: _BinaryFindVertexShader @ 0x002D3110
static RwInt32
BinaryFindVertexShader(const _rpSkinXboxShaderDesc *value,
                       const _rpSkinXboxShaderItemDesc *buffer,
                       RwInt32 numElems)
{
    RwInt32     lowerValue = 0;
    RwInt32     higherValue;
    RwInt32     midleValue;

    if (numElems > 0)
    {
        higherValue = numElems - 1;

        do
        {
            if (numElems <= 1)
            {
                if (*(const RwUInt32 *)value == *(const RwUInt32 *)&buffer[lowerValue].desc)
                {
                    return lowerValue;
                }

                if (*(const RwUInt32 *)value < *(const RwUInt32 *)&buffer[lowerValue].desc)
                {
                    return -(lowerValue + 1);
                }

                return -(lowerValue + 2);
            }

            midleValue = lowerValue + numElems / 2 - (1 - (numElems & 1));

            if (*(const RwUInt32 *)value == *(const RwUInt32 *)&buffer[midleValue].desc)
            {
                return midleValue;
            }

            if (*(const RwUInt32 *)value < *(const RwUInt32 *)&buffer[midleValue].desc)
            {
                higherValue = midleValue - 1;
            }
            else
            {
                lowerValue = midleValue + 1;
            }

            numElems = higherValue - lowerValue + 1;
        }
        while (numElems > 0);
    }

    return -(lowerValue + 1);
}

// match: __rpSkinXboxGetShader @ 0x002D3180
const DWORD *
_rpSkinXboxGetShader(const _rpSkinXboxShaderDesc *desc)
{
    RwInt32         index;
    const DWORD     *byteCode;

    if (*(const RwUInt32 *)&LastVertexShaderDesc->desc == *(const RwUInt32 *)desc)
    {
        LastVertexShaderDesc->renderFrame = RWSRCGLOBAL(renderFrame);

        return LastVertexShaderDesc->byteCode;
    }

    index = BinaryFindVertexShader(desc, VertexShaderCache, NumShadersInCache);
    if (index >= 0)
    {
        LastVertexShaderDesc = &VertexShaderCache[index];
        LastVertexShaderDesc->renderFrame = RWSRCGLOBAL(renderFrame);

        return LastVertexShaderDesc->byteCode;
    }

    byteCode = _rpSkinXboxGenerateShader(desc);

    if (NumShadersInCache >= rpSKINXBOXSHADERCACHESIZE)
    {
        _rpSkinXboxShaderItemDesc   *oldest = VertexShaderCache;
        RwInt32                     i;

        for (i = 1; i < NumShadersInCache; i++)
        {
            if (VertexShaderCache[i].renderFrame < oldest->renderFrame)
            {
                oldest = &VertexShaderCache[i];
            }
        }

        oldest->desc = *desc;
        oldest->renderFrame = RWSRCGLOBAL(renderFrame);

        if (oldest->byteCode)
        {
            RwFree((void *)oldest->byteCode);
        }

        oldest->byteCode = byteCode;

        LastVertexShaderDesc = oldest;
    }
    else
    {
        index = -(index + 1);

        if (index < NumShadersInCache)
        {
            memmove(&VertexShaderCache[index + 1], &VertexShaderCache[index],
                    (NumShadersInCache - index) * sizeof(_rpSkinXboxShaderItemDesc));
        }

        NumShadersInCache++;

        VertexShaderCache[index].desc = *desc;
        VertexShaderCache[index].byteCode = byteCode;

        LastVertexShaderDesc = &VertexShaderCache[index];
        LastVertexShaderDesc->renderFrame = RWSRCGLOBAL(renderFrame);
    }

    return byteCode;
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
