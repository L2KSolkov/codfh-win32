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

static RwV4d _rpSkinXboxAmbientLight;
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

// match: _FindLights @ 0x002D1D30
static RwV4d *
FindLights(RwV4d *shaderConstantPtr,
           RwInt32 *dirLightCount,
           RwInt32 *pointLightCount,
           const RpAtomic *atomic)
{
    RwMatrix        inverseAtomicLTM;
    RwMatrix        nonscaledInverseAtomicLTM;
    RwBool          notOrthonormal;
    RwBool          orthoNormalized;
    RwInt32         numPointLights;
    RwReal          *radiusBlock;
    const RpWorld   *world;
    RwLLLink        *cur, *end;

    RwMatrixInvert(&inverseAtomicLTM, RwFrameGetLTM(RpAtomicGetFrame(atomic)));

    notOrthonormal = (rwMatrixGetFlags(&inverseAtomicLTM) & rwMATRIXTYPEMASK) !=
                     rwMATRIXTYPEORTHONORMAL;
    orthoNormalized = FALSE;

    _rpSkinXboxAmbientLight.x = 0.0f;
    _rpSkinXboxAmbientLight.y = 0.0f;
    _rpSkinXboxAmbientLight.z = 0.0f;

    shaderConstantPtr++;

    world = (const RpWorld *)RWSRCGLOBAL(curWorld);

    cur = rwLinkListGetFirstLLLink(&world->directionalLightList);
    end = rwLinkListGetTerminator(&world->directionalLightList);
    if (cur != end)
    {
        do
        {
            RpLight *light = rwLLLinkGetData(cur, RpLight, inWorld);

            if (light && rwObjectTestFlags(light, rpLIGHTLIGHTATOMICS))
            {
                switch (RpLightGetType(light))
                {
                    case rpLIGHTDIRECTIONAL:
                    {
                        const RwV3d *at = RwMatrixGetAt(RwFrameGetLTM(RpLightGetFrame(light)));

                        if (notOrthonormal)
                        {
                            if (!orthoNormalized)
                            {
                                orthoNormalized = TRUE;
                                RwMatrixOrthoNormalize(&nonscaledInverseAtomicLTM,
                                                       &inverseAtomicLTM);
                            }

                            RwV3dTransformVector((RwV3d *)shaderConstantPtr, at,
                                                 &nonscaledInverseAtomicLTM);
                        }
                        else
                        {
                            RwV3dTransformVector((RwV3d *)shaderConstantPtr, at, &inverseAtomicLTM);
                        }

                        shaderConstantPtr->w = 0.0f;
                        shaderConstantPtr++;

                        shaderConstantPtr->x = light->color.red;
                        shaderConstantPtr->y = light->color.green;
                        shaderConstantPtr->z = light->color.blue;
                        shaderConstantPtr->w = 1.0f;
                        shaderConstantPtr++;

                        (*dirLightCount)++;

                        break;
                    }

                    case rpLIGHTAMBIENT:
                    {
                        _rpSkinXboxAmbientLight.x += light->color.red;
                        _rpSkinXboxAmbientLight.y += light->color.green;
                        _rpSkinXboxAmbientLight.z += light->color.blue;

                        break;
                    }
                }
            }

            cur = rwLLLinkGetNext(cur);
        }
        while (cur != end);

        if (!(1.0f > _rpSkinXboxAmbientLight.x))
        {
            _rpSkinXboxAmbientLight.x = 1.0f;
        }

        if (!(1.0f > _rpSkinXboxAmbientLight.y))
        {
            _rpSkinXboxAmbientLight.y = 1.0f;
        }

        if (!(1.0f > _rpSkinXboxAmbientLight.z))
        {
            _rpSkinXboxAmbientLight.z = 1.0f;
        }
    }

    if (RpGeometryGetFlags(RpAtomicGetGeometry(atomic)) & rpGEOMETRYPRELIT)
    {
        _rpSkinXboxAmbientLight.w = 0.0f;
    }
    else
    {
        _rpSkinXboxAmbientLight.w = 1.0f;
    }

    RWSRCGLOBAL(lightFrame)++;

    numPointLights = 0;

    for (cur = rwLinkListGetFirstLLLink(&atomic->llWorldSectorsInAtomic);
         cur != rwLinkListGetTerminator(&atomic->llWorldSectorsInAtomic);
         cur = rwLLLinkGetNext(cur))
    {
        RpTie       *tpTie = rwLLLinkGetData(cur, RpTie, lWorldSectorInAtomic);
        RwLLLink    *curLight, *endLight;

        curLight = rwLinkListGetFirstLLLink(&tpTie->worldSector->lightsInWorldSector);
        endLight = rwLinkListGetTerminator(&tpTie->worldSector->lightsInWorldSector);
        while (curLight != endLight)
        {
            RpLightTie  *lightTie = rwLLLinkGetData(curLight, RpLightTie, lightInWorldSector);
            RpLight     *light = lightTie->light;

            if (light && (light->lightFrame != RWSRCGLOBAL(lightFrame)) &&
                (rwObjectTestFlags(light, rpLIGHTLIGHTATOMICS)))
            {
                const RwV3d     *pos;
                const RwSphere  *sphere;
                RwV3d           distanceVector;
                RwReal          distanceSquare;
                RwReal          distanceCollision;

                light->lightFrame = RWSRCGLOBAL(lightFrame);

                pos = &(RwFrameGetLTM(RpLightGetFrame(light))->pos);
                sphere = RpAtomicGetWorldBoundingSphere((RpAtomic *)atomic);

                RwV3dSub(&distanceVector, &sphere->center, pos);

                distanceSquare = RwV3dDotProduct(&distanceVector, &distanceVector);

                distanceCollision = sphere->radius + RpLightGetRadius(light);

                if (distanceSquare < distanceCollision * distanceCollision)
                {
                    if (RpLightGetType(light) == rpLIGHTPOINT)
                    {
                        if ((numPointLights % 4) == 0)
                        {
                            radiusBlock = (RwReal *)shaderConstantPtr;
                            shaderConstantPtr++;
                        }

                        numPointLights++;

                        pos = &(RwFrameGetLTM(RpLightGetFrame(light))->pos);
                        RwV3dTransformPoint((RwV3d *)shaderConstantPtr, pos, &inverseAtomicLTM);
                        shaderConstantPtr->w = 0.0f;
                        shaderConstantPtr++;

                        shaderConstantPtr->x = light->color.red;
                        shaderConstantPtr->y = light->color.green;
                        shaderConstantPtr->z = light->color.blue;
                        shaderConstantPtr->w = 1.0f;
                        shaderConstantPtr++;

                        if (notOrthonormal)
                        {
                            RwV3d   radiusLocal;

                            radiusLocal.x = 0.57735026f;
                            radiusLocal.y = 0.57735026f;
                            radiusLocal.z = 0.57735026f;

                            RwV3dTransformVector(&radiusLocal, &radiusLocal, &inverseAtomicLTM);

                            *radiusBlock = RwV3dLength(&radiusLocal) / RpLightGetRadius(light);
                        }
                        else
                        {
                            *radiusBlock = 1.0f / RpLightGetRadius(light);
                        }

                        radiusBlock++;

                        (*pointLightCount)++;
                    }
                }
            }

            curLight = rwLLLinkGetNext(curLight);
        }
    }

    return shaderConstantPtr;
}

// match: __rpSkinXboxEnumerateLights @ 0x002D2130
RwV4d *
_rpSkinXboxEnumerateLights(RwV4d *shaderConstantPtr,
                           RwInt32 *dirLightCount,
                           RwInt32 *pointLightCount,
                           RpAtomic *atomic)
{
    RwUInt32    flags;

    *dirLightCount = 0;
    *pointLightCount = 0;

    flags = RpGeometryGetFlags(RpAtomicGetGeometry(atomic));

    if (flags & rxGEOMETRY_LIGHT)
    {
        shaderConstantPtr->x = 0.0f;
        shaderConstantPtr->y = 0.0f;
        shaderConstantPtr->z = 0.0f;
        shaderConstantPtr->w = 1.0f;

        if (RWSRCGLOBAL(curWorld))
        {
            return FindLights(shaderConstantPtr, dirLightCount, pointLightCount, atomic);
        }
    }
    else
    {
        RwReal  value = (flags & rxGEOMETRY_PRELIT) ? 0.0f : 1.0f;

        shaderConstantPtr->x = value;
        shaderConstantPtr->y = value;
        shaderConstantPtr->z = value;
        shaderConstantPtr->w = value;
    }

    return shaderConstantPtr + 1;
}

// match: __rpSkinXboxSetMaterialColor @ 0x002D24F0
void
_rpSkinXboxSetMaterialColor(const RpMaterial *material, RwUInt32 modulate)
{
    DWORD   *pPush;
    RwReal  ambient;

    /* The ambient colour: vertex shader constant -91. */
    pPush = D3DDevice_BeginState(7);

    *pPush++ = D3DPUSH_ENCODE(D3DPUSH_SET_TRANSFORM_CONSTANT_LOAD, 1);
    *pPush++ = 5;
    *pPush++ = D3DPUSH_ENCODE(D3DPUSH_SET_TRANSFORM_CONSTANT, 4);

    ambient = material->surfaceProps.ambient;
    if (ambient != 1.0f)
    {
        ((RwReal *)pPush)[0] = _rpSkinXboxAmbientLight.x * ambient;
        ((RwReal *)pPush)[1] = _rpSkinXboxAmbientLight.y * ambient;
        ((RwReal *)pPush)[2] = _rpSkinXboxAmbientLight.z * ambient;
    }
    else
    {
        ((RwReal *)pPush)[0] = _rpSkinXboxAmbientLight.x;
        ((RwReal *)pPush)[1] = _rpSkinXboxAmbientLight.y;
        ((RwReal *)pPush)[2] = _rpSkinXboxAmbientLight.z;
    }

    ((RwReal *)pPush)[3] = _rpSkinXboxAmbientLight.w;

    D3DDevice_EndState(pPush + 4);

    /* The material colour: vertex shader constant 95. */
    pPush = D3DDevice_BeginState(7);

    *pPush++ = D3DPUSH_ENCODE(D3DPUSH_SET_TRANSFORM_CONSTANT_LOAD, 1);
    *pPush++ = 0xBF;
    *pPush++ = D3DPUSH_ENCODE(D3DPUSH_SET_TRANSFORM_CONSTANT, 4);

    if (modulate && *(const RwUInt32 *)&material->color != 0xFFFFFFFF)
    {
        const RwReal    scale = material->surfaceProps.diffuse * (1.0f / 255.0f);

        ((RwReal *)pPush)[0] = (RwReal)material->color.red * scale;
        ((RwReal *)pPush)[1] = (RwReal)material->color.green * scale;
        ((RwReal *)pPush)[2] = (RwReal)material->color.blue * scale;
        ((RwReal *)pPush)[3] = (RwReal)material->color.alpha * (1.0f / 255.0f);
    }
    else
    {
        ((RwReal *)pPush)[0] = material->surfaceProps.diffuse;
        ((RwReal *)pPush)[1] = material->surfaceProps.diffuse;
        ((RwReal *)pPush)[2] = material->surfaceProps.diffuse;
        ((RwReal *)pPush)[3] = 1.0f;
    }

    D3DDevice_EndState(pPush + 4);
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
