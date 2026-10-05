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

// match: __rpSkinXboxInstanceAssignFormatShaders @ 0x002D3550
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
    RwUInt8     *lockedVertexBuffer;

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

        instancedHeader->vertexBuffer =
            RwXbCreateVertexBuffer(instancedHeader->stride * numVertices);
        if (NULL == instancedHeader->vertexBuffer)
        {
            return FALSE;
        }

        lockedVertexBuffer = D3DVertexBuffer_Lock2((D3DVertexBuffer *)instancedHeader->vertexBuffer, 0);
    }
    else
    {
        D3DVertexBuffer *vertexBuffer = (D3DVertexBuffer *)instancedHeader->vertexBuffer;
        RwUInt32        vbSize = instancedHeader->stride * numVertices;

        if (vertexBuffer->Lock && D3DDevice_IsFencePending(vertexBuffer->Lock))
        {
            lockedVertexBuffer = RwXbVertexBufferLockDiscard(vertexBuffer, vbSize);
        }
        else
        {
            lockedVertexBuffer = D3DVertexBuffer_Lock2(vertexBuffer, 0);
        }
    }

    if (positions)
    {
        lockedVertexBuffer += _rpXboxVtxFmtInstV3d((RpXboxCompType)fmt->pos, lockedVertexBuffer,
                                                   positions, numVertices,
                                                   instancedHeader->stride);
    }

    if (normals)
    {
        lockedVertexBuffer += _rpXboxVtxFmtInstV3d((RpXboxCompType)fmt->norm, lockedVertexBuffer,
                                                   normals, numVertices,
                                                   instancedHeader->stride);
    }

    if (color)
    {
        instancedHeader->vertexAlpha =
            _rpXboxVtxFmtInstColor(lockedVertexBuffer, color, numVertices,
                                   instancedHeader->stride);
        lockedVertexBuffer += sizeof(RwUInt32);
    }

    if (numTexCoordSets > 0)
    {
        RwInt32 i;

        for (i = 0; i < numTexCoordSets; i++)
        {
            lockedVertexBuffer +=
                _rpXboxVtxFmtInstV2d((RpXboxCompType)((fmt->texCoord >> (4 * i)) & 0xF),
                                     lockedVertexBuffer, texCoordSets[i], numVertices,
                                     instancedHeader->stride);
        }
    }

    if (fmt->bnt && normals)
    {
        _rpXboxVtxFmtInstBNT(lockedVertexBuffer, positions, normals,
                             texCoordSets[fmt->bnt - 1], instancedHeader,
                             numVertices, instancedHeader->stride);
    }

    return TRUE;
}

// match: __rpSkinXboxReInstanceCallback @ 0x002D3870
RwBool
_rpSkinXboxReInstanceCallback(void *object, RxXboxResEntryHeader *instancedHeader)
{
    return _rpSkinXboxInstanceCallback(object, instancedHeader, TRUE);
}

// match: __rpSkinDeinitialize @ 0x002D3A80
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
