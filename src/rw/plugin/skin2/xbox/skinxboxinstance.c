/*
 * codfh-match: RenderWare 3.6's Xbox skin instancing and native streaming,
 * rebuilt from the image; the file name is the image's RCS id string's,
 * names and shapes the Godfather debug build's copy.
 */

#include <xtl.h>
#include <string.h>

#include <rwcore.h>
#include <rpworld.h>

#include "skin.h"
#include "bsplit.h"

#include "xbmemory.h"

#include "xbvtxfmt.h"
#include "skinxbox.h"

/* RenderWare 3.6's RCS id string, which the image keeps (the 3.7.2 tree has none) */
static const char rcsid[] = "@@@@(#)$Id: //RenderWare/RW36Active/rwsdk/plugin/skin2/xbox/skinxboxinstance.c#3 $";

static RwUInt8
Weight2PackedWeight(RwReal weight)
{
    RwReal  x = weight * 255.0f + 0.5f;

    return (RwUInt8)RwFastRealToUInt32(x);
}

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: _rcsid @ 0x00418E90
// match: __real@3b008081 @ 0x00418EE4

// match: _InstanceWeightsAndIndices @ 0x002D3340
// sp-match: _InstanceWeightsAndIndices @ 0x001EDC90

static RwBool
InstanceWeightsAndIndices(const RxXboxResEntryHeader *instancedHeader,
                          RwInt32 weightsToInstance,
                          RpSkin *skin)
{
    RwInt32                 numVertices = instancedHeader->numVertices;
    RwInt32                 stride;
    RwUInt32                vbSize;
    RwUInt8                 *lockedVertexBuffer;
    RwUInt8                 *vertexBuffer;
    const RwMatrixWeights   *weights;
    const RwUInt32          *indices;
    RwInt32                 vertex;

    skin->platformData.weightsNindicesVBStride = 3 * weightsToInstance;
    stride = skin->platformData.weightsNindicesVBStride;
    vbSize = numVertices * stride;

    if (skin->platformData.weightsNindicesVB)
    {
        RwXbReleaseVertexBuffer((D3DVertexBuffer *)skin->platformData.weightsNindicesVB);
    }

    skin->platformData.weightsNindicesVB = RwXbCreateVertexBuffer(vbSize);
    if (NULL == skin->platformData.weightsNindicesVB)
    {
        return FALSE;
    }

    lockedVertexBuffer = D3DVertexBuffer_Lock2((D3DVertexBuffer *)skin->platformData.weightsNindicesVB, 0);

    vertexBuffer = lockedVertexBuffer;
    weights = skin->vertexMaps.matrixWeights;

    for (vertex = 0; vertex < numVertices; vertex++)
    {
        RwInt32 nonZeroInputWeightCount = 0;
        RwInt32 packedWeightSum;
        RwInt32 packedWeights[4];
        RwInt32 i;

        for (i = 0; i < weightsToInstance; i++)
        {
            RwReal  w = ((const RwReal *)weights)[i];

            if (*(RwInt32 *)&w > 0)
            {
                nonZeroInputWeightCount++;
            }

            packedWeights[i] = Weight2PackedWeight(w);
        }

        packedWeightSum = 0;
        for (i = 1; i < nonZeroInputWeightCount; i++)
        {
            packedWeightSum += packedWeights[i];
        }

        packedWeights[0] = 255 - packedWeightSum;

        for (i = 0; i < weightsToInstance; i++)
        {
            vertexBuffer[i] = (RwUInt8)packedWeights[i];
        }

        weights++;
        vertexBuffer += stride;
    }

    indices = skin->vertexMaps.matrixIndices;
    vertexBuffer = lockedVertexBuffer + weightsToInstance;

    if (skin->skinSplitData.meshRLECount)
    {
        if (skin->skinSplitData.matrixRemapIndices[0] >= skin->platformData.numBonesUsed)
        {
            skin->skinSplitData.matrixRemapIndices[0] = 0;
        }

        for (vertex = 0; vertex < numVertices; vertex++)
        {
            RwInt32 j;

            for (j = 0; j < weightsToInstance; j++)
            {
                RwUInt32    index = (*indices >> (8 * j)) & 0xFF;
                RwInt32     remapped = skin->skinSplitData.matrixRemapIndices[index];

                ((RwUInt16 *)vertexBuffer)[j] = (RwUInt16)(3 * remapped);
            }

            indices++;
            vertexBuffer += stride;
        }
    }
    else
    {
        for (vertex = 0; vertex < numVertices; vertex++)
        {
            RwInt32 k;

            for (k = 0; k < weightsToInstance; k++)
            {
                RwUInt32    index = (*indices >> (8 * k)) & 0xFF;
                RwInt32     mapped = skin->platformData.vertexIndexMap[index];

                ((RwUInt16 *)vertexBuffer)[k] = (RwUInt16)(3 * mapped);
            }

            indices++;
            vertexBuffer += stride;
        }
    }

    return TRUE;
}

// match: __rpSkinXboxInstanceAssignFormatShaders @ 0x002D3550
// sp-match: __rpSkinXboxInstanceAssignFormatShaders @ 0x001EDEA0
static void
_rpSkinXboxInstanceAssignFormatShaders(RpGeometry *geometry,
                                       RpSkin *skin,
                                       RxXboxResEntryHeader *instancedHeader)
{
    RwUInt32            maxWeights = skin->platformData.maxWeightsUsed;
    RpXboxVtxFmt        *format;
    _rpSkinXboxVtxFmt   skinFormat;
    DWORD               shader;
    RxXboxInstanceData  *mesh;

    format = RpXboxGeometryGetVtxFmt(geometry);

    if (0 == *(RwUInt32 *)format)
    {
        RpXboxVtxFmtInit((RpXboxVtxFmt *)&skinFormat, geometry->flags,
                         geometry->numTexCoordSets);
    }
    else
    {
        skinFormat.pos = format->pos;
        skinFormat.norm = format->norm;
        skinFormat.texCoord = format->texCoord;
        skinFormat.prelit = format->prelit;
        skinFormat.bnt = format->bnt;
    }

    skinFormat.numWeights = maxWeights;

    shader = _rpSkinXboxGetVertexFormatShader(&skinFormat);

    for (mesh = instancedHeader->begin; mesh != instancedHeader->end; mesh++)
    {
        mesh->vertexShader = shader;
    }
}

// match: _rpSkinXboxDefaultInstance @ 0x002D3610
// sp-match: _rpSkinXboxDefaultInstance @ 0x001EDF60
static RwBool
rpSkinXboxDefaultInstance(RxXboxResEntryHeader *instancedHeader,
                          RpXboxVtxFmt *fmt,
                          RwUInt32 flags,
                          const RwV3d *positions,
                          const RwV3d *normals,
                          const RwRGBA *color,
                          RwInt32 numTexCoordSets,
                          const RwTexCoords **texCoordSets,
                          RwBool reinstance)
{
    RwInt32     numVertices;
    RwUInt32    vbSize;
    RwUInt8     *lockedVertexBuffer;
    RwInt32     i;

    numVertices = instancedHeader->numVertices;

    if (numTexCoordSets > 4)
    {
        numTexCoordSets = 4;
    }

    if (0 == *(RwUInt32 *)fmt)
    {
        RpXboxVtxFmtInit(fmt, flags, numTexCoordSets);
    }

    if (!reinstance)
    {
        RxXboxInstanceData  *mesh;

        instancedHeader->stride = _rpXboxVtxFmtGetStride(fmt);

        for (mesh = instancedHeader->begin; mesh != instancedHeader->end; mesh++)
        {
            mesh->vertexShader = 0;
        }

        vbSize = numVertices * instancedHeader->stride;

        instancedHeader->vertexBuffer = RwXbCreateVertexBuffer(vbSize);
        if (NULL == instancedHeader->vertexBuffer)
        {
            return FALSE;
        }

        D3DVertexBuffer_Lock((D3DVertexBuffer *)instancedHeader->vertexBuffer, 0, vbSize,
                             &lockedVertexBuffer, 0);
    }
    else
    {
        D3DVertexBuffer *currentVertexBuffer = (D3DVertexBuffer *)instancedHeader->vertexBuffer;

        vbSize = numVertices * instancedHeader->stride;

        if (currentVertexBuffer->Lock && D3DDevice_IsFencePending(currentVertexBuffer->Lock))
        {
            lockedVertexBuffer = RwXbVertexBufferLockDiscard(currentVertexBuffer, vbSize);
        }
        else
        {
            D3DVertexBuffer_Lock(currentVertexBuffer, 0, vbSize, &lockedVertexBuffer, 0);
        }
    }

    if (positions)
    {
        RwUInt32    size;

        size = _rpXboxVtxFmtInstV3d((RpXboxCompType)fmt->pos, lockedVertexBuffer,
                                    positions, numVertices, instancedHeader->stride);
        lockedVertexBuffer += size;
    }

    if (normals)
    {
        RwUInt32    size;

        size = _rpXboxVtxFmtInstV3d((RpXboxCompType)fmt->norm, lockedVertexBuffer,
                                    normals, numVertices, instancedHeader->stride);
        lockedVertexBuffer += size;
    }

    if (color)
    {
        instancedHeader->vertexAlpha =
            _rpXboxVtxFmtInstColor(lockedVertexBuffer, color, numVertices,
                                   instancedHeader->stride);
        lockedVertexBuffer += sizeof(RwUInt32);
    }

    for (i = 0; i < numTexCoordSets; i++)
    {
        RwUInt32    type = (fmt->texCoord >> (4 * i)) & 0xF;
        RwUInt32    size;

        size = _rpXboxVtxFmtInstV2d((RpXboxCompType)type, lockedVertexBuffer,
                                    texCoordSets[i], numVertices,
                                    instancedHeader->stride);
        lockedVertexBuffer += size;
    }

    if (fmt->bnt)
    {
        if (normals)
        {
            _rpXboxVtxFmtInstBNT(lockedVertexBuffer, positions, normals,
                                 texCoordSets[numTexCoordSets - 1], instancedHeader,
                                 numVertices, instancedHeader->stride);
        }
    }

    D3DVertexBuffer_Unlock((D3DVertexBuffer *)instancedHeader->vertexBuffer);

    return TRUE;
}

// match: __rpSkinXboxInstanceCallback @ 0x002D37C0
// sp-match: __rpSkinXboxInstanceCallback @ 0x001EE110
RwBool
_rpSkinXboxInstanceCallback(void *object,
                            RxXboxResEntryHeader *instancedHeader,
                            RwBool reinstance)
{
    RpAtomic            *atomic = (RpAtomic *)object;
    RpGeometry          *geometry = RpAtomicGetGeometryMacro(atomic);
    RpSkin              *skin = RpSkinGeometryGetSkin(geometry);
    RwUInt32            flags = RpGeometryGetFlagsMacro(geometry);
    const RwTexCoords   **texCoordSets;
    RwInt32             numTexCoordSets;
    const RwRGBA        *color;

    if (flags & (rpGEOMETRYTEXTURED | rpGEOMETRYTEXTURED2))
    {
        texCoordSets = (const RwTexCoords **)geometry->texCoords;
    }
    else
    {
        texCoordSets = NULL;
    }

    if (flags & (rpGEOMETRYTEXTURED | rpGEOMETRYTEXTURED2))
    {
        numTexCoordSets = geometry->numTexCoordSets;
    }
    else
    {
        numTexCoordSets = 0;
    }

    if (flags & rpGEOMETRYPRELIT)
    {
        color = geometry->preLitLum;
    }
    else
    {
        color = NULL;
    }

    rpSkinXboxDefaultInstance(instancedHeader, RpXboxGeometryGetVtxFmt(geometry), flags,
                              geometry->morphTarget[0].verts,
                              geometry->morphTarget[0].normals,
                              color, numTexCoordSets, texCoordSets, reinstance);

    if (!reinstance)
    {
        RwInt32 weightsToInstance = skin->platformData.maxWeightsUsed;

        _rpSkinXboxInstanceAssignFormatShaders(geometry, skin, instancedHeader);

        return InstanceWeightsAndIndices(instancedHeader, weightsToInstance, skin);
    }

    return TRUE;
}

// match: __rpSkinXboxReInstanceCallback @ 0x002D3870
// sp-match: __rpSkinXboxReInstanceCallback @ 0x001EE1C0
RwBool
_rpSkinXboxReInstanceCallback(void *object, RxXboxResEntryHeader *instancedHeader)
{
    return _rpSkinXboxInstanceCallback(object, instancedHeader, TRUE);
}

#define FLOATASINT(f) (*((const RwInt32 *)&(f)))

// match: __rpSkinInitialize @ 0x002D3890
// sp-match: __rpSkinInitialize @ 0x001EE1E0
RpGeometry *
_rpSkinInitialize(RpGeometry *geometry)
{
    const RwReal    minWeight = 0.5f / 255.0f;
    RpSkin          *skin;
    RwUInt32        usedBones[256];
    RwInt32         maxWeights;
    RwInt32         numBonesUsed;
    RwInt32         i;

    skin = RpSkinGeometryGetSkin(geometry);
    if (!skin)
    {
        return NULL;
    }

    if (RpGeometryGetFlags(geometry) & rpGEOMETRYNATIVE)
    {
        return geometry;
    }

    skin->platformData.numBonesUsed = 0;
    skin->platformData.maxWeightsUsed = 0;
    skin->platformData.weightsNindicesVB = NULL;
    skin->platformData.weightsNindicesVBStride = 0;

    memset(usedBones, 0, sizeof(usedBones));
    maxWeights = 0;

    if (geometry->numVertices > 0)
    {
        const RwMatrixWeights   *matrixWeights = skin->vertexMaps.matrixWeights;
        const RwUInt32          *matrixIndices = skin->vertexMaps.matrixIndices;

        for (i = geometry->numVertices; i; i--)
        {
            const RwUInt32  indices = *matrixIndices;

            if (FLOATASINT(matrixWeights->w0) >= FLOATASINT(minWeight))
            {
                usedBones[indices & 0xFF] = 1;
                if (maxWeights < 1)
                {
                    maxWeights = 1;
                }
            }

            if (FLOATASINT(matrixWeights->w1) >= FLOATASINT(minWeight))
            {
                usedBones[(indices >> 8) & 0xFF] = 1;
                if (maxWeights < 2)
                {
                    maxWeights = 2;
                }
            }

            if (FLOATASINT(matrixWeights->w2) >= FLOATASINT(minWeight))
            {
                usedBones[(indices >> 16) & 0xFF] = 1;
                if (maxWeights < 3)
                {
                    maxWeights = 3;
                }
            }

            if (FLOATASINT(matrixWeights->w3) >= FLOATASINT(minWeight))
            {
                usedBones[(indices >> 24) & 0xFF] = 1;
                if (maxWeights < 4)
                {
                    maxWeights = 4;
                }
            }

            matrixIndices++;
            matrixWeights++;
        }
    }

    skin->platformData.maxWeightsUsed = maxWeights;

    numBonesUsed = 0;

    for (i = 0; i < 256; i++)
    {
        skin->platformData.vertexIndexMap[i] = -1;
        skin->platformData.matrixIndexMap[i] = -1;
    }

    for (i = 0; i < 256; i++)
    {
        if (usedBones[i])
        {
            skin->platformData.vertexIndexMap[i] = numBonesUsed++;
        }
    }

    skin->platformData.numBonesUsed = numBonesUsed;

    for (i = 0; i < 256; i++)
    {
        if (skin->platformData.vertexIndexMap[i] != -1)
        {
            skin->platformData.matrixIndexMap[skin->platformData.vertexIndexMap[i]] = i;
        }
    }

    for (i = 0; i < 256; i++)
    {
        if (skin->platformData.vertexIndexMap[i] == -1)
        {
            skin->platformData.vertexIndexMap[i] = 0;
        }
    }

    return geometry;
}

// match: __rpSkinDeinitialize @ 0x002D3A80
// sp-match: __rpSkinDeinitialize @ 0x001EE3D0
RpGeometry *
_rpSkinDeinitialize(RpGeometry *geometry)
{
    if (RpSkinGeometryGetSkin(geometry))
    {
        RpSkin  *skin = RpSkinGeometryGetSkin(geometry);

        if (skin->platformData.weightsNindicesVB)
        {
            RwXbReleaseVertexBuffer((D3DVertexBuffer *)skin->platformData.weightsNindicesVB);
            skin->platformData.weightsNindicesVB = NULL;
        }

        skin->platformData.weightsNindicesVBStride = 0;
    }

    return geometry;
}

// match: __rpSkinGeometryNativeSize @ 0x002D3AD0
// sp-match: __rpSkinGeometryNativeSize @ 0x001EE420
RwInt32
_rpSkinGeometryNativeSize(const RpGeometry *geometry)
{
    const RpSkin    *skin;
    RwInt32         size;

    skin = *RPSKINGEOMETRYGETCONSTDATA(geometry);

    size = skin->platformData.weightsNindicesVBStride * RpGeometryGetNumVertices(geometry) +
           2084;
    size += skin->boneData.numBones * sizeof(RwMatrix);
    size += _rpSkinSplitDataStreamGetSize(skin);

    return size;
}

// match: __rpSkinGeometryNativeWrite @ 0x002D3B00
// sp-match: __rpSkinGeometryNativeWrite @ 0x001EE450
RwStream *
_rpSkinGeometryNativeWrite(RwStream *stream, const RpGeometry *geometry)
{
    RwPlatformID    id = rwID_XBOX;
    const RpSkin    *skin;
    RwUInt32        vbSize;
    RwInt32         size;
    RwUInt8         *lockedVertexBuffer;

    if (!RwStreamWriteChunkHeader(stream, rwID_STRUCT,
                                  _rpSkinGeometryNativeSize(geometry) - rwCHUNKHEADERSIZE))
    {
        return NULL;
    }

    if (!RwStreamWriteInt32(stream, (RwInt32 *)&id, sizeof(RwPlatformID)))
    {
        return NULL;
    }

    skin = *RPSKINGEOMETRYGETCONSTDATA(geometry);

    if (!RwStreamWriteInt32(stream, (const RwInt32 *)&skin->boneData.numBones, sizeof(RwInt32)))
    {
        return NULL;
    }

    if (!RwStreamWrite(stream, &skin->platformData, sizeof(SkinPlatformData)))
    {
        return NULL;
    }

    vbSize = skin->platformData.weightsNindicesVBStride * RpGeometryGetNumVertices(geometry);

    D3DVertexBuffer_Lock((D3DVertexBuffer *)skin->platformData.weightsNindicesVB, 0, vbSize,
                         &lockedVertexBuffer, 0);

    if (!RwStreamWrite(stream, lockedVertexBuffer, vbSize))
    {
        return NULL;
    }

    if (!RwStreamWrite(stream, skin->boneData.invBoneToSkinMat,
                       skin->boneData.numBones * sizeof(RwMatrix)))
    {
        return NULL;
    }

    if (!_rpSkinSplitDataStreamWrite(stream, skin))
    {
        return NULL;
    }

    return stream;
}

// match: __rpSkinGeometryNativeRead @ 0x002D3C00
// sp-match: __rpSkinGeometryNativeRead @ 0x001EE550
RwStream *
_rpSkinGeometryNativeRead(RwStream *stream, RpGeometry *geometry)
{
    RwUInt32        version;
    RwUInt32        size;
    RwPlatformID    id;
    RpSkin          *skin;
    RwUInt8         *lockedVertexBuffer;

    if (!RwStreamFindChunk(stream, rwID_STRUCT, &size, &version))
    {
        return NULL;
    }

    if ((version < rwLIBRARYBASEVERSION) || (version > rwLIBRARYCURRENTVERSION))
    {
        RWERROR((E_RW_BADVERSION));
        return NULL;
    }

    if (!RwStreamReadInt32(stream, (RwInt32 *)&id, sizeof(RwPlatformID)))
    {
        return NULL;
    }

    if (rwID_XBOX != id)
    {
        return NULL;
    }

    skin = (RpSkin *)RwFreeListAlloc(_rpSkinGlobals.freeList,
                                     rwID_SKINPLUGIN | rwMEMHINTDUR_EVENT);
    memset(skin, 0, sizeof(RpSkin));

    if (!RwStreamReadInt32(stream, (RwInt32 *)&skin->boneData.numBones, sizeof(RwInt32)))
    {
        return NULL;
    }

    if (!RwStreamRead(stream, &skin->platformData, sizeof(SkinPlatformData)))
    {
        return NULL;
    }

    skin->vertexMaps.maxWeights = skin->platformData.maxWeightsUsed;

    size = skin->platformData.weightsNindicesVBStride * RpGeometryGetNumVertices(geometry);

    skin->platformData.weightsNindicesVB = RwXbCreateVertexBuffer(size);
    if (NULL == skin->platformData.weightsNindicesVB)
    {
        return NULL;
    }

    D3DVertexBuffer_Lock((D3DVertexBuffer *)skin->platformData.weightsNindicesVB, 0, size,
                         &lockedVertexBuffer, 0);

    if (RwStreamRead(stream, lockedVertexBuffer, size) != size)
    {
        return NULL;
    }

    size = skin->boneData.numBones * sizeof(RwMatrix) + 16;

    skin->unaligned = (SkinUnaligned *)RwMalloc(size, rwID_SKINPLUGIN | rwMEMHINTDUR_EVENT);
    skin->boneData.invBoneToSkinMat = (RwMatrix *)(((RwUInt32)skin->unaligned + 15) & ~15);

    if (!RwStreamRead(stream, skin->boneData.invBoneToSkinMat,
                      skin->boneData.numBones * sizeof(RwMatrix)))
    {
        return NULL;
    }

    if (!_rpSkinSplitDataStreamRead(stream, skin))
    {
        return NULL;
    }

    _rpSkinXboxInstanceAssignFormatShaders(geometry, skin,
                                           (RxXboxResEntryHeader *)(geometry->repEntry + 1));

    RpSkinGeometrySetSkin(geometry, skin);

    return stream;
}
