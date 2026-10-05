/*
 * codfh-match: RenderWare 3.6's Xbox native geometry and world sector
 * streaming, rebuilt from the image; the file name is the image's RCS id
 * string's, names and shapes the Godfather debug build's copy (3.7 there:
 * 3.6 writes the instanced meshes' materials as they are and never unlocks
 * the vertex buffer).
 */

#include <xtl.h>

#include <rwcore.h>
#include "bamateri.h"
#include "baworld.h"
#include "bageomet.h"

#include "xbmemory.h"

#include "xbpipe.h"
#include "native.h"

/* RenderWare 3.6's RCS id string, which the image keeps (the 3.7.2 tree has none) */
static const char rcsid[] = "@@@@(#)$Id: //RenderWare/RW36Active/rwsdk/world/pipe/p2/xbox/native.c#1 $";

static RwInt32
NativeSize(RwUInt32 flags, RwResEntry *resEntry)
{
    RwInt32     size = 0;

    if ((flags & rpGEOMETRYNATIVE) && resEntry)
    {
        RxXboxResEntryHeader    *resHeader = (RxXboxResEntryHeader *)(resEntry + 1);

        size = rwCHUNKHEADERSIZE + sizeof(RwPlatformID) + resHeader->size +
               resHeader->stride * resHeader->numVertices;
    }

    return size;
}

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: _rcsid @ 0x00419598
// match: ?id@?1??NativeWrite@@9@9 @ 0x004195E4

// match: _NativeWrite @ 0x002E1760

static RwStream *
NativeWrite(RwStream *stream, RwUInt32 flags, RwResEntry *resEntry)
{
    static const RwPlatformID id = rwID_XBOX;

    if (flags & rpGEOMETRYNATIVE)
    {
        RxXboxResEntryHeader    *resHeader;
        RxXboxInstanceData      *instancedData;
        RwUInt32                vbSize;
        RwUInt32                size;
        RwUInt8                 *lockedVertexBuffer;

        resHeader = (RxXboxResEntryHeader *)(resEntry + 1);

        vbSize = resHeader->stride * resHeader->numVertices;
        size = sizeof(RwPlatformID) + resHeader->size + vbSize;

        if (!RwStreamWriteChunkHeader(stream, rwID_STRUCT, size))
        {
            return NULL;
        }

        if (!RwStreamWrite(stream, &id, sizeof(RwPlatformID)))
        {
            return NULL;
        }

        /* The index buffers are written as offsets from the entry. */
        for (instancedData = resHeader->begin; instancedData != resHeader->end; instancedData++)
        {
            instancedData->indexBuffer = (RwUInt16 *)((RwUInt8 *)instancedData->indexBuffer -
                                                      (RwUInt8 *)resEntry);
        }

        if (!RwStreamWrite(stream, resHeader, resHeader->size))
        {
            return NULL;
        }

        for (instancedData = resHeader->begin; instancedData != resHeader->end; instancedData++)
        {
            instancedData->indexBuffer = (RwUInt16 *)((RwUInt8 *)instancedData->indexBuffer +
                                                      (RwUInt32)resEntry);
        }

        D3DVertexBuffer_Lock((D3DVertexBuffer *)resHeader->vertexBuffer, 0, vbSize,
                             &lockedVertexBuffer, 0);

        if (!RwStreamWrite(stream, lockedVertexBuffer, vbSize))
        {
            return NULL;
        }
    }

    return stream;
}

// match: _NativeRead @ 0x002E1820
static RwResEntry *
NativeRead(RwStream *stream, RwResEntry **resEntryPointer, RpMesh *mesh)
{
    RwUInt32                version;
    RwUInt32                size;
    RwPlatformID            id;
    RwResEntry              *resEntry;
    RxXboxResEntryHeader    *resEntryHeader;
    RxXboxInstanceData      *instancedData;
    RwUInt16                numMeshes;
    RwUInt8                 *lockedVertexBuffer;

    size = 0;

    if (!RwStreamFindChunk(stream, rwID_STRUCT, NULL, &version))
    {
        return NULL;
    }

    if ((version < rwLIBRARYBASEVERSION) || (version > rwLIBRARYCURRENTVERSION))
    {
        RWERROR((E_RW_BADVERSION));
        return NULL;
    }

    if (RwStreamRead(stream, &id, sizeof(RwPlatformID)) != sizeof(RwPlatformID))
    {
        return NULL;
    }

    if (rwID_XBOX != id)
    {
        return NULL;
    }

    if (RwStreamRead(stream, &size, sizeof(RwUInt32)) != sizeof(RwUInt32))
    {
        return NULL;
    }

    *resEntryPointer = (RwResEntry *)RwMalloc(sizeof(RwResEntry) + size,
                                              rwID_WORLDPIPEMODULE | rwMEMHINTDUR_EVENT);

    (*resEntryPointer)->link.next = (RwLLLink *)NULL;
    (*resEntryPointer)->link.prev = (RwLLLink *)NULL;
    (*resEntryPointer)->size = size;
    (*resEntryPointer)->owner = NULL;
    (*resEntryPointer)->ownerRef = (RwResEntry **)NULL;
    (*resEntryPointer)->destroyNotify = _rwXBResourceEntryInstanceDataDestroy;

    resEntry = *resEntryPointer;
    resEntryHeader = (RxXboxResEntryHeader *)(resEntry + 1);

    resEntryHeader->size = size;
    size -= sizeof(RwInt32);

    if (RwStreamRead(stream, &resEntryHeader->serialNumber, size) != size)
    {
        return NULL;
    }

    resEntryHeader->begin = (RxXboxInstanceData *)(resEntryHeader + 1);

    instancedData = resEntryHeader->begin;
    numMeshes = resEntryHeader->numMeshes;
    while (numMeshes--)
    {
        instancedData->material = mesh->material;
        instancedData->indexBuffer = (RwUInt16 *)((RwUInt8 *)instancedData->indexBuffer +
                                                  (RwUInt32)resEntry);
        instancedData->vertexShader = 0;

        instancedData++;
        mesh++;
    }

    resEntryHeader->end = instancedData;

    size = resEntryHeader->stride * resEntryHeader->numVertices;

    resEntryHeader->vertexBuffer = RwXbCreateVertexBuffer(size);
    if (NULL == resEntryHeader->vertexBuffer)
    {
        return NULL;
    }

    D3DVertexBuffer_Lock((D3DVertexBuffer *)resEntryHeader->vertexBuffer, 0, size,
                         &lockedVertexBuffer, 0);

    if (RwStreamRead(stream, lockedVertexBuffer, size) != size)
    {
        return NULL;
    }

    return resEntry;
}

// match: __rpGeometryNativeWrite @ 0x002E19B0
RwStream *
_rpGeometryNativeWrite(RwStream *stream, const RpGeometry *geometry)
{
    RwUInt32    flags = RpGeometryGetFlags(geometry);

    return NativeWrite(stream, flags, geometry->repEntry);
}

// match: __rpGeometryNativeRead @ 0x002E19D0
RpGeometry *
_rpGeometryNativeRead(RwStream *stream, RpGeometry *geometry)
{
    if (NativeRead(stream, &geometry->repEntry,
                   (RpMesh *)(geometry->mesh + 1)))
    {
        return geometry;
    }

    return NULL;
}

// match: __rpGeometryNativeSize @ 0x002E1A00
RwInt32
_rpGeometryNativeSize(const RpGeometry *geometry)
{
    return NativeSize(RpGeometryGetFlags(geometry), geometry->repEntry);
}

// match: __rpWorldSectorNativeWrite @ 0x002E1A30
RwStream *
_rpWorldSectorNativeWrite(RwStream *stream, const RpWorldSector *sector)
{
    RwUInt32    flags = RpWorldGetFlags(RpWorldSectorGetWorld(sector));

    return NativeWrite(stream, flags, sector->repEntry);
}

// match: __rpWorldSectorNativeRead @ 0x002E1A60
RpWorldSector *
_rpWorldSectorNativeRead(RwStream *stream, RpWorldSector *sector)
{
    if (NativeRead(stream, &sector->repEntry,
                   (RpMesh *)(sector->mesh + 1)))
    {
        return sector;
    }

    return NULL;
}

// match: __rpWorldSectorNativeSize @ 0x002E1A90
RwInt32
_rpWorldSectorNativeSize(const RpWorldSector *sector)
{
    const RpWorld   *world = RpWorldSectorGetWorld(sector);

    return NativeSize(RpWorldGetFlags(world), sector->repEntry);
}
