/*
 * codfh-match: RenderWare 3.6's Xbox world pipeline instancing and default
 * rendering (world/pipe/p2/xbox/xbpipe.c), rebuilt from the image; names from
 * the Godfather PDB's copy of the same file.
 */

#include <xtl.h>
#include <stdlib.h>
#include <string.h>

#include <rwcore.h>
#include "bamateri.h"
#include "baworld.h"
#include "bageomet.h"

#include "xbmemory.h"
#include "xbcache.h"
#include "xbrendst.h"

#include "xbpipe.h"

/* RenderWare 3.6's RCS id string, which the image keeps (the 3.7.2 tree has none) */
static const char rcsid[] = "@@@@(#)$Id: //RenderWare/RW36Active/rwsdk/world/pipe/p2/xbox/xbpipe.c#1 $";

#define XbRoundUp16(_x) (((_x) + 15) & ~15)

/* The pixel shader plugin's offset (xbpixelshader.c). */
extern RwInt32 _RpXboxMaterialPixelShaderOffset;

#define RpXboxMaterialGetPixelShader(_material) \
    (*((DWORD *)(((RwUInt8 *)(_material)) + _RpXboxMaterialPixelShaderOffset)))

/* The fixed-function render state between meshes. */
static RwReal LastAmbientScale = RwRealMAXVAL;
static RwReal LastDiffuseScale = RwRealMAXVAL;
static D3DMATERIAL8 D3D8material =
{
    { 0.0f, 0.0f, 0.0f, 1.0f },     /* Diffuse */
    { 0.0f, 0.0f, 0.0f, 1.0f },     /* Ambient */
    { 0.0f, 0.0f, 0.0f, 1.0f },     /* Specular */
    { 0.0f, 0.0f, 0.0f, 1.0f },     /* Emissive */
    0.0f                            /* Power */
};

static RwBool setMaterial = FALSE;
static RwBool setMaterialColor = FALSE;
static RwBool modulateMaterial = FALSE;
static DWORD lightingEnabled = FALSE;
static RwUInt32 LastColor = 0;

/* RenderWare primitive types to D3D's. */
const D3DPRIMITIVETYPE RwXboxPrimConvTable[7] =
{
    (D3DPRIMITIVETYPE)0,    /* rwPRIMTYPENAPRIMTYPE */
    D3DPT_LINELIST,         /* rwPRIMTYPELINELIST */
    D3DPT_LINESTRIP,        /* rwPRIMTYPEPOLYLINE */
    D3DPT_TRIANGLELIST,     /* rwPRIMTYPETRILIST */
    D3DPT_TRIANGLESTRIP,    /* rwPRIMTYPETRISTRIP */
    D3DPT_TRIANGLEFAN,      /* rwPRIMTYPETRIFAN */
    D3DPT_POINTLIST         /* rwPRIMTYPEPOINTLIST */
};

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: _rcsid @ 0x00419418
// match: _RwXboxPrimConvTable @ 0x00419464
// match: _LastAmbientScale @ 0x00436CB8
// match: _LastDiffuseScale @ 0x00436CBC
// match: _D3D8material @ 0x00436CC0

// match: _XBMeshGetNumVerticesMinIndex @ 0x002DF670

void
XBMeshGetNumVerticesMinIndex(const RwUInt16 *indices, RwUInt32 numIndices,
                             RwInt32 *numVertices, RwUInt32 *min)
{
    if (numIndices)
    {
        RwUInt32    minVert = 0xFFFFFFFF;
        RwUInt32    maxVert = 0;

        do
        {
            const RwUInt16 index = *indices;

            minVert = (minVert >= index) ? index : minVert;
            maxVert = (maxVert <= index) ? index : maxVert;

            indices++;
        }
        while (--numIndices);

        *numVertices = maxVert - minVert + 1;
        *min = minVert;
    }
    else
    {
        *numVertices = 0;
        *min = 0;
    }
}

// match: __rwXBResourceEntryInstanceDataDestroy @ 0x002DF6C0
void
_rwXBResourceEntryInstanceDataDestroy(RwResEntry *repEntry)
{
    RxXboxResEntryHeader    *resEntryHeader = (RxXboxResEntryHeader *)(repEntry + 1);

    if (resEntryHeader->vertexBuffer)
    {
        RwXbReleaseVertexBuffer((D3DVertexBuffer *)resEntryHeader->vertexBuffer);
        resEntryHeader->vertexBuffer = NULL;
    }
}

/* qsort order for triangles: by their sorted vertex indices. */
// match: _SortTriangles @ 0x002DF6E0
static int
SortTriangles(const void *pA, const void *pB)
{
    const RwUInt16  *triA = (const RwUInt16 *)pA;
    const RwUInt16  *triB = (const RwUInt16 *)pB;
    RwUInt32        sortedIndexA[3];
    RwUInt32        sortedIndexB[3];
    RwUInt32        temp;

    sortedIndexA[0] = triA[0];
    sortedIndexA[1] = triA[1];
    sortedIndexA[2] = triA[2];

    if (sortedIndexA[0] > sortedIndexA[1])
    {
        temp = sortedIndexA[0];
        sortedIndexA[0] = sortedIndexA[1];
        sortedIndexA[1] = temp;
    }

    if (sortedIndexA[1] > sortedIndexA[2])
    {
        temp = sortedIndexA[1];
        sortedIndexA[1] = sortedIndexA[2];
        sortedIndexA[2] = temp;

        if (sortedIndexA[0] > sortedIndexA[1])
        {
            temp = sortedIndexA[0];
            sortedIndexA[0] = sortedIndexA[1];
            sortedIndexA[1] = temp;
        }
    }

    sortedIndexB[0] = triB[0];
    sortedIndexB[1] = triB[1];
    sortedIndexB[2] = triB[2];

    if (sortedIndexB[0] > sortedIndexB[1])
    {
        temp = sortedIndexB[0];
        sortedIndexB[0] = sortedIndexB[1];
        sortedIndexB[1] = temp;
    }

    if (sortedIndexB[1] > sortedIndexB[2])
    {
        temp = sortedIndexB[1];
        sortedIndexB[1] = sortedIndexB[2];
        sortedIndexB[2] = temp;

        if (sortedIndexB[0] > sortedIndexB[1])
        {
            temp = sortedIndexB[0];
            sortedIndexB[0] = sortedIndexB[1];
            sortedIndexB[1] = temp;
        }
    }

    if (sortedIndexA[0] == sortedIndexB[0])
    {
        if (sortedIndexA[1] == sortedIndexB[1])
        {
            return sortedIndexA[2] - sortedIndexB[2];
        }

        return sortedIndexA[1] - sortedIndexB[1];
    }

    return sortedIndexA[0] - sortedIndexB[0];
}

// match: __rxXBInstance @ 0x002DF760
RwResEntry *
_rxXBInstance(void *object,
              void *owner,
              RwResEntry **resEntryPointer,
              RpMeshHeader *meshHeader,
              RwInt32 numVertices,
              RxXboxAllInOneInstanceCallBack instanceCallback,
              RwBool allocateNative)
{
    RxXboxResEntryHeader    *resEntryHeader;
    RxXboxInstanceData      *instancedData;
    RwResEntry              *resEntry;
    const RpMesh            *mesh;
    RwInt16                 numMeshes;
    RwUInt32                size;
    RwUInt32                padSize;
    RwUInt32                totalNumIndex;
    RwUInt16                *curIndexBuffer;
    RwPrimitiveType         rwPrimType;
    RwBool                  convertToTriList;

    /* Calc the size of the header and the instance data */
    size = sizeof(RxXboxResEntryHeader) +
           (sizeof(RxXboxInstanceData) * meshHeader->numMeshes);
    padSize = size;
    size += 16;

    /* Add the index buffers, each 16-byte aligned */
    totalNumIndex = 0;
    mesh = (const RpMesh *)(meshHeader + 1);
    numMeshes = meshHeader->numMeshes;
    while (numMeshes--)
    {
        totalNumIndex += mesh->numIndices;
        size += XbRoundUp16(mesh->numIndices * sizeof(RwUInt16));

        mesh++;
    }

    if (allocateNative)
    {
        resEntry = (RwResEntry *)RwMalloc(sizeof(RwResEntry) + size,
                                          rwID_WORLDPIPEMODULE | rwMEMHINTDUR_EVENT);

        *resEntryPointer = resEntry;

        resEntry->link.next = (RwLLLink *)NULL;
        resEntry->link.prev = (RwLLLink *)NULL;
        resEntry->size = size;
        resEntry->owner = NULL;
        resEntry->ownerRef = (RwResEntry **)NULL;
        resEntry->destroyNotify = _rwXBResourceEntryInstanceDataDestroy;
    }
    else
    {
        resEntry = RwResourcesAllocateResEntry(owner, resEntryPointer, size,
                                               _rwXBResourceEntryInstanceDataDestroy);
    }

    resEntryHeader = (RxXboxResEntryHeader *)(resEntry + 1);

    /* The padding that aligns the first index buffer */
    padSize += sizeof(RwResEntry);
    padSize = XbRoundUp16((RwUInt32)resEntry + padSize) - ((RwUInt32)resEntry + padSize);

    memset(resEntryHeader, 0, sizeof(RxXboxResEntryHeader) +
                              (sizeof(RxXboxInstanceData) * meshHeader->numMeshes));

    resEntryHeader->size = size;
    resEntryHeader->serialNumber = meshHeader->serialNum;
    resEntryHeader->numMeshes = meshHeader->numMeshes;
    resEntryHeader->stride = 0;
    resEntryHeader->numVertices = numVertices;
    resEntryHeader->vertexBuffer = NULL;

    rwPrimType = RpMeshHeaderGetPrimType(meshHeader);

    convertToTriList = FALSE;
    if (rwPrimType == rwPRIMTYPETRISTRIP)
    {
        RwUInt32    numTriangles = 0x55555555;

        if (RwObjectGetType(owner) == rpGEOMETRY || RwObjectGetType(owner) == rpATOMIC)
        {
            numTriangles = RpGeometryGetNumTriangles(RpAtomicGetGeometry((RpAtomic *)object));
        }
        else if (RwObjectGetType(owner) == (RwUInt8)rwSECTORATOMIC)
        {
            numTriangles = RpWorldSectorGetNumTriangles((RpWorldSector *)object);
        }

        /* Strips longer than a list would be are converted to lists */
        if (totalNumIndex > 3 * (numTriangles + 1))
        {
            convertToTriList = TRUE;
            rwPrimType = rwPRIMTYPETRILIST;
        }
    }

    resEntryHeader->primType = RwXboxPrimConvTable[rwPrimType];
    resEntryHeader->vertexAlpha = FALSE;

    instancedData = (RxXboxInstanceData *)(resEntryHeader + 1);
    resEntryHeader->begin = instancedData;

    curIndexBuffer = (RwUInt16 *)(((RwUInt8 *)(instancedData + meshHeader->numMeshes)) + padSize);

    mesh = (const RpMesh *)(meshHeader + 1);
    numMeshes = meshHeader->numMeshes;
    while (numMeshes--)
    {
        XBMeshGetNumVerticesMinIndex(mesh->indices, mesh->numIndices,
                                     &instancedData->numVertices,
                                     &instancedData->minVert);

        instancedData->material = mesh->material;
        instancedData->vertexShader = 0;
        instancedData->indexBuffer = curIndexBuffer;

        if (convertToTriList)
        {
            const RwUInt16  *indexSrc = mesh->indices;
            RwUInt16        *indexDst = curIndexBuffer;
            RwUInt32        maxindex = mesh->numIndices - 2;
            RwUInt32        numIndices = 0;
            RwUInt32        n;

            for (n = 0; n < maxindex; n++)
            {
                if (indexSrc[0] != indexSrc[1] &&
                    indexSrc[0] != indexSrc[2] &&
                    indexSrc[1] != indexSrc[2])
                {
                    if (n & 1)
                    {
                        indexDst[2] = indexSrc[0];
                        indexDst[1] = indexSrc[1];
                        indexDst[0] = indexSrc[2];
                    }
                    else
                    {
                        indexDst[0] = indexSrc[0];
                        indexDst[1] = indexSrc[1];
                        indexDst[2] = indexSrc[2];
                    }

                    indexDst += 3;
                    numIndices += 3;
                }

                indexSrc++;
            }

            instancedData->numIndices = numIndices;
            curIndexBuffer += numIndices;
        }
        else
        {
            instancedData->numIndices = mesh->numIndices;

            memcpy(curIndexBuffer, mesh->indices, mesh->numIndices * sizeof(RwUInt16));

            curIndexBuffer += mesh->numIndices;
        }

        /* Sort triangle lists by vertex */
        if (resEntryHeader->primType == D3DPT_TRIANGLELIST)
        {
            qsort(instancedData->indexBuffer, instancedData->numIndices / 3,
                  sizeof(RwUInt16) * 3, SortTriangles);
        }

        curIndexBuffer = (RwUInt16 *)XbRoundUp16((RwUInt32)curIndexBuffer);

        instancedData++;
        mesh++;
    }

    resEntryHeader->end = instancedData;

    if (instanceCallback)
    {
        if (!instanceCallback(object, resEntryHeader, FALSE))
        {
            if (allocateNative)
            {
                RwFree(resEntry);
            }
            else
            {
                RwResourcesFreeResEntry(resEntry);
            }

            return NULL;
        }
    }

    return resEntry;
}

// match: __rxXbDefaultRenderFFPObjectSetUp @ 0x002DFAC0
void
_rxXbDefaultRenderFFPObjectSetUp(RxXboxResEntryHeader *instancedHeader,
                                 void *object __RWUNUSED__,
                                 RwUInt8 type __RWUNUSED__,
                                 RwUInt32 flags)
{
    RwXboxGetCachedRenderState(D3DRS_LIGHTING, &lightingEnabled);

    if (lightingEnabled && (flags & rpGEOMETRYLIGHT))
    {
        setMaterial = TRUE;

        if (flags & rpGEOMETRYMODULATEMATERIALCOLOR)
        {
            if (flags & rpGEOMETRYPRELIT)
            {
                setMaterialColor = FALSE;
                modulateMaterial = TRUE;
            }
            else
            {
                setMaterialColor = TRUE;
                modulateMaterial = FALSE;
            }
        }
        else
        {
            setMaterialColor = FALSE;
            modulateMaterial = FALSE;
        }

        LastColor = 0;
        LastAmbientScale = RwRealMAXVAL;
        LastDiffuseScale = RwRealMAXVAL;
    }
    else
    {
        setMaterial = FALSE;
        setMaterialColor = FALSE;
        modulateMaterial = TRUE;
    }

    if (lightingEnabled)
    {
        if (flags & rpGEOMETRYPRELIT)
        {
            _rwXbRenderStateForce(D3DRS_COLORVERTEX, TRUE);
            _rwXbRenderStateForce(D3DRS_EMISSIVEMATERIALSOURCE, D3DMCS_COLOR1);
        }
        else
        {
            _rwXbRenderStateForce(D3DRS_COLORVERTEX, FALSE);
            _rwXbRenderStateForce(D3DRS_EMISSIVEMATERIALSOURCE, D3DMCS_MATERIAL);
        }

        if (instancedHeader->vertexAlpha)
        {
            _rwXbRenderStateForce(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);
        }
        else
        {
            _rwXbRenderStateForce(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
        }
    }
}

// match: __rxXbDefaultRenderFFPMeshSetUp @ 0x002DFC20
void
_rxXbDefaultRenderFFPMeshSetUp(RxXboxInstanceData *mesh)
{
    if (setMaterial)
    {
        const RpMaterial    *material = mesh->material;

        if (LastColor != *((const RwUInt32 *)&material->color) ||
            *((const RwUInt32 *)&LastAmbientScale) != *((const RwUInt32 *)&material->surfaceProps.ambient) ||
            *((const RwUInt32 *)&LastDiffuseScale) != *((const RwUInt32 *)&material->surfaceProps.diffuse))
        {
            LastAmbientScale = material->surfaceProps.ambient;
            LastDiffuseScale = material->surfaceProps.diffuse;

            if (!setMaterialColor || *((const RwUInt32 *)&material->color) == 0xFFFFFFFF)
            {
                LastColor = 0xFFFFFFFF;

                D3D8material.Diffuse.r = LastDiffuseScale;
                D3D8material.Diffuse.g = LastDiffuseScale;
                D3D8material.Diffuse.b = LastDiffuseScale;
                D3D8material.Diffuse.a = 1.0f;

                D3D8material.Ambient.r = LastAmbientScale;
                D3D8material.Ambient.g = LastAmbientScale;
                D3D8material.Ambient.b = LastAmbientScale;
                D3D8material.Ambient.a = 1.0f;
            }
            else
            {
                const RwRGBA    *color = &material->color;
                RwReal          ambScale, diffScale;

                LastColor = *((const RwUInt32 *)color);

                ambScale = LastAmbientScale * (1.0f / 255.0f);
                diffScale = LastDiffuseScale * (1.0f / 255.0f);

                D3D8material.Diffuse.r = (RwReal)color->red * diffScale;
                D3D8material.Diffuse.g = (RwReal)color->green * diffScale;
                D3D8material.Diffuse.b = (RwReal)color->blue * diffScale;
                D3D8material.Diffuse.a = (RwReal)color->alpha * (1.0f / 255.0f);

                D3D8material.Ambient.r = (RwReal)color->red * ambScale;
                D3D8material.Ambient.g = (RwReal)color->green * ambScale;
                D3D8material.Ambient.b = (RwReal)color->blue * ambScale;
                D3D8material.Ambient.a = (RwReal)color->alpha * (1.0f / 255.0f);
            }

            D3DDevice_SetMaterial(&D3D8material);
        }
    }
}

// match: __rxXbDefaultRenderFFPMeshCombinerSetUp @ 0x002DFDB0
void
_rxXbDefaultRenderFFPMeshCombinerSetUp(RxXboxInstanceData *mesh, RwUInt32 flags)
{
    if (flags & (rpGEOMETRYTEXTURED | rpGEOMETRYTEXTURED2))
    {
        RwXboxSetCachedTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
        RwXboxSetCachedTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
        RwXboxSetCachedTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TEXTURE);
        RwXboxSetCachedTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
        RwXboxSetCachedTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
        RwXboxSetCachedTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);
    }
    else
    {
        RwXboxSetCachedTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
        RwXboxSetCachedTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
        RwXboxSetCachedTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
        RwXboxSetCachedTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
    }

    if (modulateMaterial)
    {
        RwUInt32        tFactor;
        const RwRGBA   *color = &mesh->material->color;

        if (!lightingEnabled && (flags & rpGEOMETRYLIGHT) && !(flags & rpGEOMETRYPRELIT))
        {
            if (flags & rpGEOMETRYMODULATEMATERIALCOLOR)
            {
                tFactor = ((RwUInt32)color->alpha) << 24;
            }
            else
            {
                tFactor = 0xFF000000;
            }
        }
        else
        {
            if (!(flags & rpGEOMETRYMODULATEMATERIALCOLOR) ||
                *((const RwUInt32 *)color) == 0xFFFFFFFF)
            {
                RwXboxSetCachedTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
                RwXboxSetCachedTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);

                return;
            }

            tFactor = ((RwUInt32)color->blue) |
                      (((RwUInt32)color->green) << 8) |
                      (((RwUInt32)color->red) << 16) |
                      (((RwUInt32)color->alpha) << 24);
        }

        _rwXbRenderStateForce(D3DRS_TEXTUREFACTOR, tFactor);

        RwXboxSetCachedTextureStageState(1, D3DTSS_COLOROP, D3DTOP_MODULATE);
        RwXboxSetCachedTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TFACTOR);
        RwXboxSetCachedTextureStageState(1, D3DTSS_COLORARG2, D3DTA_CURRENT);
        RwXboxSetCachedTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
        RwXboxSetCachedTextureStageState(1, D3DTSS_ALPHAARG1, D3DTA_TFACTOR);
        RwXboxSetCachedTextureStageState(1, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
    }
}

// match: __rxXbDefaultRenderFFPMeshCombinerTearDown @ 0x002E0190
void
_rxXbDefaultRenderFFPMeshCombinerTearDown(void)
{
    if (modulateMaterial)
    {
        RwXboxSetCachedTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
        RwXboxSetCachedTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
    }
}

// match: __rxXbDefaultRenderFFPMesh @ 0x002E0200
void
_rxXbDefaultRenderFFPMesh(RxXboxResEntryHeader *instancedHeader,
                          RxXboxInstanceData *mesh,
                          RwUInt32 flags)
{
    DWORD   pixelShader;

    if (flags & (rpGEOMETRYTEXTURED | rpGEOMETRYTEXTURED2))
    {
        RwXboxRenderStateSetTexture(mesh->material->texture, 0);
    }
    else
    {
        RwXboxRenderStateSetTexture(NULL, 0);
    }

    if (instancedHeader->vertexAlpha || mesh->material->color.alpha != 0xFF)
    {
        RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)TRUE);
    }
    else
    {
        RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)FALSE);
    }

    RwXboxSetCurrentVertexShader(mesh->vertexShader);

    pixelShader = RpXboxMaterialGetPixelShader(mesh->material);
    if (!pixelShader)
    {
        _rxXbDefaultRenderFFPMeshCombinerSetUp(mesh, flags);
    }

    RwXboxSetCurrentPixelShader(pixelShader);

    RwXboxDrawIndexedVertices((D3DPRIMITIVETYPE)instancedHeader->primType,
                              mesh->numIndices, mesh->indexBuffer);

    if (!pixelShader)
    {
        _rxXbDefaultRenderFFPMeshCombinerTearDown();
    }
}

// match: __rxXbDefaultRenderCallback @ 0x002E02A0
void
_rxXbDefaultRenderCallback(RxXboxResEntryHeader *resEntryHeader,
                           void *object,
                           RwUInt8 type,
                           RwUInt32 flags)
{
    RxXboxInstanceData  *mesh;
    DWORD               lastVertexShader;
    DWORD               lastPixelShader;
    DWORD               pixelShader;
    RwUInt32            lastTFactor;
    RwUInt32            tFactor;

    lastPixelShader = 0xFFFFFFFF;
    lastTFactor = 0xFFFFFFFF;
    tFactor = 0xFFFFFFFF;

    lastVertexShader = RwXboxGetCurrentVertexShader();

    D3DDevice_SetStreamSource(0, (D3DVertexBuffer *)resEntryHeader->vertexBuffer,
                              resEntryHeader->stride);

    _rxXbDefaultRenderFFPObjectSetUp(resEntryHeader, object, type, flags);

    for (mesh = resEntryHeader->begin; mesh != resEntryHeader->end; mesh++)
    {
        _rxXbDefaultRenderFFPMeshSetUp(mesh);

        if (lastVertexShader != mesh->vertexShader)
        {
            lastVertexShader = mesh->vertexShader;
            RwXboxSetCurrentVertexShader(mesh->vertexShader);
        }

        if (flags & (rpGEOMETRYTEXTURED | rpGEOMETRYTEXTURED2))
        {
            RwXboxRenderStateSetTexture(mesh->material->texture, 0);
        }
        else
        {
            RwXboxRenderStateSetTexture(NULL, 0);
        }

        if (resEntryHeader->vertexAlpha || mesh->material->color.alpha != 0xFF)
        {
            RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)TRUE);
        }
        else
        {
            RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)FALSE);
        }

        if (modulateMaterial)
        {
            const RwRGBA   *color = &mesh->material->color;

            if (!lightingEnabled && (flags & rpGEOMETRYLIGHT) && !(flags & rpGEOMETRYPRELIT))
            {
                if (flags & rpGEOMETRYMODULATEMATERIALCOLOR)
                {
                    tFactor = ((RwUInt32)color->alpha) << 24;
                }
                else
                {
                    tFactor = 0xFF000000;
                }
            }
            else
            {
                if (!(flags & rpGEOMETRYMODULATEMATERIALCOLOR) ||
                    *((const RwUInt32 *)color) == 0xFFFFFFFF)
                {
                    tFactor = 0xFFFFFFFF;
                }
                else
                {
                    tFactor = ((RwUInt32)color->blue) |
                              (((RwUInt32)color->green) << 8) |
                              (((RwUInt32)color->red) << 16) |
                              (((RwUInt32)color->alpha) << 24);
                }
            }
        }

        pixelShader = RpXboxMaterialGetPixelShader(mesh->material);

        if (lastPixelShader != pixelShader)
        {
            lastPixelShader = pixelShader;

            RwXboxSetCurrentPixelShader(pixelShader);

            if (!pixelShader)
            {
                if (flags & (rpGEOMETRYTEXTURED | rpGEOMETRYTEXTURED2))
                {
                    _rwXbTextureStageForceInline(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
                    _rwXbTextureStageForceInline(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
                    _rwXbTextureStageForceInline(0, D3DTSS_COLORARG2, D3DTA_TEXTURE);
                    _rwXbTextureStageForceInline(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
                    _rwXbTextureStageForceInline(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
                    _rwXbTextureStageForceInline(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);
                }
                else
                {
                    _rwXbTextureStageForceInline(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
                    _rwXbTextureStageForceInline(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
                    _rwXbTextureStageForceInline(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
                    _rwXbTextureStageForceInline(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
                }

                lastTFactor = ~tFactor;
            }
        }

        if (lastTFactor != tFactor)
        {
            lastTFactor = tFactor;

            if (tFactor != 0xFFFFFFFF)
            {
                _rwXbRenderStateForce(D3DRS_TEXTUREFACTOR, tFactor);

                _rwXbTextureStageForceInline(1, D3DTSS_COLOROP, D3DTOP_MODULATE);
                _rwXbTextureStageForceInline(1, D3DTSS_COLORARG1, D3DTA_TFACTOR);
                _rwXbTextureStageForceInline(1, D3DTSS_COLORARG2, D3DTA_CURRENT);
                _rwXbTextureStageForceInline(1, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
                _rwXbTextureStageForceInline(1, D3DTSS_ALPHAARG1, D3DTA_TFACTOR);
                _rwXbTextureStageForceInline(1, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
            }
            else
            {
                _rwXbTextureStageForceInline(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
                _rwXbTextureStageForceInline(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
            }
        }

        _rwXbFlushCacheBuffer();

        D3DDevice_DrawIndexedVertices((D3DPRIMITIVETYPE)resEntryHeader->primType,
                                      mesh->numIndices, mesh->indexBuffer);
    }

    if (lastTFactor != 0xFFFFFFFF)
    {
        RwXboxSetCachedTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
        RwXboxSetCachedTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
    }
}

// match: __rxXboxAllInOneSetInstanceCallBack @ 0x002E0780
void
_rxXboxAllInOneSetInstanceCallBack(RxPipelineNode *node,
                                   RxXboxAllInOneInstanceCallBack callback)
{
    RxXboxAllInOneInstanceCallBack *instanceData = (RxXboxAllInOneInstanceCallBack *)node->privateData;

    *instanceData = callback;
}

// match: __rxXboxAllInOneGetInstanceCallBack @ 0x002E0790
RxXboxAllInOneInstanceCallBack
_rxXboxAllInOneGetInstanceCallBack(RxPipelineNode *node)
{
    RxXboxAllInOneInstanceCallBack *instanceData = (RxXboxAllInOneInstanceCallBack *)node->privateData;

    return *instanceData;
}

/* /OPT:ICF folded it into the skin node's identical setter
 * (_rxXboxSkinAllInOneSetRenderCallBack, 0x2D4B10): no place of its own. */
void
_rxXboxAllInOneSetRenderCallBack(RxPipelineNode *node,
                                 RxXboxAllInOneRenderCallBack callback)
{
    _rxXboxInstanceNodeData *instanceData = (_rxXboxInstanceNodeData *)node->privateData;

    instanceData->renderCallback = callback;
}
