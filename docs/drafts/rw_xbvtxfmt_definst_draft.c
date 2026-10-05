/*
 * codfh-match: RenderWare 3.6's Xbox vertex formats
 * (world/pipe/p2/xbox/xbvtxfmt.c), rebuilt from the image; names from the
 * Godfather PDB's copy of the same file.
 */

#include <xtl.h>
#include <stdlib.h>
#include <string.h>

#include <rwcore.h>
#include "bamateri.h"
#include "baworld.h"
#include "bageomet.h"

#include "xbmemory.h"

#include "xbpipe.h"
#include "xbvtxfmt.h"

/****************************************************************************
 Globals
 */

RwModuleInfo RpVtxFmtModule;
RwInt32 _rpXboxGeomVtxFmtOffset = 0;
RwInt32 rpXboxWorldVtxFmtOffset = 0;
/* codfh-match: static here (only this file uses them, and the loops keep
 * the array pointer in a register across stores); public in Godfather's 3.7 */
static _rpXboxVtxFmtDescItem *rwXboxVertexFormatArray = NULL;
static RwInt32 rwXboxVertexFormatMaxElems = 0;
static RwInt32 rwXboxVertexFormatNumElems = 0;
static RwBool rwXboxVertexFormatArrayInited = FALSE;

/* The size of each component type. */
const RwUInt32 RpXboxCompSize[rpCOMPTYPEMAX] =
{
    0,                  /* rpCOMPTYPENONE */
    sizeof(RwUInt8),    /* rpPACKEDBYTE */
    sizeof(RwInt16),    /* rpSHORT */
    sizeof(RwInt16),    /* rpNORMALIZEDSHORTS */
    sizeof(RwUInt32),   /* rpNORMALIZEDPACKED */
    sizeof(RwReal)      /* rpFLOAT */
};

/* The vertex registers of the four texture coordinate sets. */
const RwUInt32 rpWorldVSDETexFlags[4] =
{
    D3DVSDE_TEXCOORD0,
    D3DVSDE_TEXCOORD1,
    D3DVSDE_TEXCOORD2,
    D3DVSDE_TEXCOORD3
};

/* The plugin's constructor and destructor: nothing to do. /OPT:ICF folded it
 * into colldata.c's CollisionDataConstructor (aliased), so it has no place of
 * its own here. */
static void *
rxXboxVertexFmtConst(void *object,
                     RwInt32 offsetInObject __RWUNUSED__,
                     RwInt32 sizeInObject __RWUNUSED__)
{
    return object;
}

// match: _rwXboxVertexFormatCreate @ 0x002DCB70
void
rwXboxVertexFormatCreate(void)
{
    if (!rwXboxVertexFormatArrayInited)
    {
        RwInt32 i;

        rwXboxVertexFormatMaxElems = 128;
        rwXboxVertexFormatArray = (_rpXboxVtxFmtDescItem *)
            RwMalloc(sizeof(_rpXboxVtxFmtDescItem) * rwXboxVertexFormatMaxElems,
                     rwID_WORLDPIPEMODULE | rwMEMHINTDUR_GLOBAL |
                     rwMEMHINTFLAG_RESIZABLE);

        for (i = 0; i < rwXboxVertexFormatMaxElems; i++)
        {
            rwXboxVertexFormatArray[i].handle = 0;
        }

        rwXboxVertexFormatNumElems = 0;
        rwXboxVertexFormatArrayInited = TRUE;
    }
}

// match: _rwXboxVertexFormatDestroy @ 0x002DCBE0
void
rwXboxVertexFormatDestroy(void)
{
    if (rwXboxVertexFormatArrayInited)
    {
        RwInt32 i;

        for (i = 0; i < rwXboxVertexFormatNumElems; i++)
        {
            if (rwXboxVertexFormatArray[i].handle)
            {
                D3DDevice_DeleteVertexShader(rwXboxVertexFormatArray[i].handle);
                rwXboxVertexFormatArray[i].handle = 0;
            }
        }

        RwFree(rwXboxVertexFormatArray);
        rwXboxVertexFormatArray = NULL;

        rwXboxVertexFormatMaxElems = 0;
        rwXboxVertexFormatNumElems = 0;
        rwXboxVertexFormatArrayInited = FALSE;
    }
}

// match: __rpXboxVtxFmtGetSize @ 0x002DCC50
RwUInt32
_rpXboxVtxFmtGetSize(RpXboxCompType type, RwUInt32 numElems)
{
    if (type == rpNORMALIZEDPACKED)
    {
        return 4;
    }

    return RpXboxCompSize[type] * numElems;
}

// match: __rpXboxVtxFmtGetStride @ 0x002DCC70
RwUInt32
_rpXboxVtxFmtGetStride(const RpXboxVtxFmt *fmt)
{
    RwUInt32    stride = 0;

    if (fmt->pos)
    {
        if (fmt->pos == rpNORMALIZEDPACKED)
        {
            stride = 4;
        }
        else
        {
            stride = 3 * RpXboxCompSize[fmt->pos];
        }
    }

    if (fmt->norm)
    {
        if (fmt->norm == rpNORMALIZEDPACKED)
        {
            stride += 4;
        }
        else
        {
            stride += 3 * RpXboxCompSize[fmt->norm];
        }
    }

    if (fmt->prelit)
    {
        stride += 4;
    }

    if (fmt->bnt)
    {
        stride += 8;
    }

    if (fmt->texCoord)
    {
        RwInt32 i;

        for (i = 0; i < 4; i++)
        {
            RpXboxCompType type = (RpXboxCompType)((fmt->texCoord >> (4 * i)) & 0xF);

            if (type == rpCOMPTYPENONE)
            {
                break;
            }

            if (type == rpNORMALIZEDPACKED)
            {
                stride += 4;
            }
            else
            {
                stride += 2 * RpXboxCompSize[type];
            }
        }
    }

    return stride;
}

// match: __rpXboxVtxFmtInstColor @ 0x002DDAF0
RwBool
_rpXboxVtxFmtInstColor(RwUInt8 *dst, const RwRGBA *src,
                       RwInt32 numVerts, RwUInt32 stride)
{
    RwUInt32   *dstColor;
    RwInt32     i;
    RwUInt8     alpha = 0xFF;

    dstColor = (RwUInt32 *)dst;
    for (i = 0; i < numVerts; i++)
    {
        *dstColor = ((RwUInt32)src[i].blue) |
                    ((RwUInt32)src[i].green << 8) |
                    ((RwUInt32)src[i].red << 16) |
                    ((RwUInt32)src[i].alpha << 24);

        alpha &= src[i].alpha;

        dstColor = (RwUInt32 *)(((RwUInt8 *)dstColor) + stride);
    }

    return (alpha != 0xFF);
}

// match: __rpXboxVtxFmtUnInstV3d @ 0x002DE6B0
void
_rpXboxVtxFmtUnInstV3d(RpXboxCompType type, RwV3d *dst, const RwUInt8 *src)
{
    switch (type)
    {
        case rpPACKEDBYTE:
            dst->x = ((RwReal)src[0]) / 255.0f;
            dst->y = ((RwReal)src[1]) / 255.0f;
            dst->z = ((RwReal)src[2]) / 255.0f;
            break;

        case rpSHORT:
            dst->x = (RwReal)((const RwInt16 *)src)[0];
            dst->y = (RwReal)((const RwInt16 *)src)[1];
            dst->z = (RwReal)((const RwInt16 *)src)[2];
            break;

        case rpNORMALIZEDSHORTS:
            dst->x = (RwReal)((const RwInt16 *)src)[0] * (1.0f / 32767.0f);
            dst->y = (RwReal)((const RwInt16 *)src)[1] * (1.0f / 32767.0f);
            dst->z = (RwReal)((const RwInt16 *)src)[2] * (1.0f / 32767.0f);
            break;

        case rpNORMALIZEDPACKED:
            {
                RwUInt32    nx, ny, nz;

                nx = (*(const RwUInt32 *)src) & 0x7FF;
                ny = ((*(const RwUInt32 *)src) >> 11) & 0x7FF;
                nz = (*(const RwUInt32 *)src) >> 22;

                dst->x = ((RwReal)nx) / 1023.0f;
                dst->y = ((RwReal)ny) / 1023.0f;
                dst->z = ((RwReal)nz) / 511.0f;
            }
            break;

        case rpFLOAT:
            *dst = *(const RwV3d *)src;
            break;

        default:
            dst->x = 0.0f;
            dst->y = 0.0f;
            dst->z = 0.0f;
            break;
    }
}

// match: __rpXboxVtxFmtUnInstV2d @ 0x002DE830
void
_rpXboxVtxFmtUnInstV2d(RpXboxCompType type, RwV2d *dst, const RwUInt8 *src)
{
    switch (type)
    {
        case rpPACKEDBYTE:
            dst->x = ((RwReal)src[0]) / 255.0f;
            dst->y = ((RwReal)src[1]) / 255.0f;
            break;

        case rpSHORT:
            dst->x = (RwReal)((const RwInt16 *)src)[0];
            dst->y = (RwReal)((const RwInt16 *)src)[1];
            break;

        case rpNORMALIZEDSHORTS:
            dst->x = (RwReal)((const RwInt16 *)src)[0] * (1.0f / 32767.0f);
            dst->y = (RwReal)((const RwInt16 *)src)[1] * (1.0f / 32767.0f);
            break;

        case rpNORMALIZEDPACKED:
            {
                RwUInt32    nx, ny;

                nx = (*(const RwUInt32 *)src) & 0x7FF;
                ny = ((*(const RwUInt32 *)src) >> 11) & 0x7FF;

                dst->x = ((RwReal)nx) / 1023.0f;
                dst->y = ((RwReal)ny) / 1023.0f;
            }
            break;

        case rpFLOAT:
            *dst = *(const RwV2d *)src;
            break;

        default:
            dst->x = 0.0f;
            dst->y = 0.0f;
            break;
    }
}

// match: _rxXboxVertexFmtCopy @ 0x002DE950
static void *
rxXboxVertexFmtCopy(void *dstObject, const void *srcObject,
                    RwInt32 offsetInObject,
                    RwInt32 sizeInObject __RWUNUSED__)
{
    *(RpXboxVtxFmt *)(((RwUInt8 *)dstObject) + offsetInObject) =
        *(const RpXboxVtxFmt *)(((const RwUInt8 *)srcObject) + offsetInObject);

    return dstObject;
}

// match: _rpXboxVtxFmtOpen @ 0x002DE970
static void *
rpXboxVtxFmtOpen(void *instance,
                 RwInt32 offset __RWUNUSED__,
                 RwInt32 size __RWUNUSED__)
{
    if (++RpVtxFmtModule.numInstances == 1)
    {
        rwXboxVertexFormatCreate();
    }

    return instance;
}

// match: _rpXboxVtxFmtClose @ 0x002DE990
static void *
rpXboxVtxFmtClose(void *instance,
                  RwInt32 offset __RWUNUSED__,
                  RwInt32 size __RWUNUSED__)
{
    if (--RpVtxFmtModule.numInstances == 0)
    {
        rwXboxVertexFormatDestroy();
    }

    return instance;
}

// match: _rxXboxVtxFmtSize @ 0x002DE9B0
static RwInt32
rxXboxVtxFmtSize(const void *object __RWUNUSED__,
                 RwInt32 offsetInObject __RWUNUSED__,
                 RwInt32 sizeInObject __RWUNUSED__)
{
    return sizeof(RpXboxVtxFmt);
}

// match: _rxXboxVtxFmtWrite @ 0x002DE9C0
static RwStream *
rxXboxVtxFmtWrite(RwStream *stream,
                  RwInt32 binaryLength __RWUNUSED__,
                  const void *object,
                  RwInt32 offsetInObject,
                  RwInt32 sizeInObject __RWUNUSED__)
{
    return RwStreamWriteInt32(stream,
                              (const RwInt32 *)(((const RwUInt8 *)object) + offsetInObject),
                              sizeof(RpXboxVtxFmt));
}

// match: _RpXboxVtxFmtInit @ 0x002DE9E0
void
RpXboxVtxFmtInit(RpXboxVtxFmt *fmt, RwUInt32 flags, RwUInt32 numTexCoordSets)
{
    RwUInt32    i;

    fmt->pos = rpFLOAT;

    if (flags & rpGEOMETRYNORMALS)
    {
        fmt->norm = rpNORMALIZEDPACKED;
    }
    else
    {
        fmt->norm = rpCOMPTYPENONE;
    }

    if (flags & (rpGEOMETRYTEXTURED | rpGEOMETRYTEXTURED2))
    {
        for (i = 0; i < numTexCoordSets; i++)
        {
            fmt->texCoord = (RwUInt16)((rpFLOAT << (4 * i)) |
                                       (~(0xF << (4 * i)) & fmt->texCoord));
        }

        for (; i < 4; i++)
        {
            fmt->texCoord = (RwUInt16)((rpCOMPTYPENONE << (4 * i)) |
                                       (~(0xF << (4 * i)) & fmt->texCoord));
        }
    }
    else
    {
        fmt->texCoord = 0;
    }

    if (flags & rpGEOMETRYPRELIT)
    {
        fmt->prelit = TRUE;
    }
    else
    {
        fmt->prelit = FALSE;
    }

    fmt->bnt = 0;
    fmt->reserved = 0;
}

// match: _RpXboxGeometryGetVtxFmt @ 0x002DEAB0
RpXboxVtxFmt *
RpXboxGeometryGetVtxFmt(RpGeometry *geometry)
{
    return (RpXboxVtxFmt *)(((RwUInt8 *)geometry) + _rpXboxGeomVtxFmtOffset);
}

// match: _RpXboxWorldGetVtxFmt @ 0x002DEAC0
RpXboxVtxFmt *
RpXboxWorldGetVtxFmt(RpWorld *world)
{
    return (RpXboxVtxFmt *)(((RwUInt8 *)world) + rpXboxWorldVtxFmtOffset);
}

/* Finds fmt in the sorted buffer: its index, or -(insertion point + 1).
 * /OPT:ICF kept the skin plugin's identical copy, SkinBinaryFindVertexFormat. */
// match: _BinaryFindVertexFormat @ 0x002D43D0
static RwInt32
BinaryFindVertexFormat(const RpXboxVtxFmt *value,
                       const _rpXboxVtxFmtDescItem *buffer,
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
                if (*(const RwUInt32 *)value == *(const RwUInt32 *)&buffer[lowerValue].format)
                {
                    return lowerValue;
                }

                if (*(const RwUInt32 *)value < *(const RwUInt32 *)&buffer[lowerValue].format)
                {
                    return -(lowerValue + 1);
                }

                return -(lowerValue + 2);
            }

            midleValue = lowerValue + numElems / 2 - (1 - (numElems & 1));

            if (*(const RwUInt32 *)value == *(const RwUInt32 *)&buffer[midleValue].format)
            {
                return midleValue;
            }

            if (*(const RwUInt32 *)value < *(const RwUInt32 *)&buffer[midleValue].format)
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

// match: _RxXboxGetVertexFormatShader @ 0x002DEAD0
DWORD
RxXboxGetVertexFormatShader(const RpXboxVtxFmt *fmt)
{
    RwInt32     index;
    DWORD       vertexFormatDecl[256];
    RwUInt32    v;
    RwUInt32    lastTexCoord;

    index = BinaryFindVertexFormat(fmt, rwXboxVertexFormatArray, rwXboxVertexFormatNumElems);
    if (index >= 0)
    {
        return rwXboxVertexFormatArray[index].handle;
    }

    vertexFormatDecl[0] = D3DVSD_STREAM(0);
    v = 1;

    switch (fmt->pos)
    {
        case rpPACKEDBYTE:
            vertexFormatDecl[v++] = D3DVSD_REG(D3DVSDE_POSITION, D3DVSDT_PBYTE3);
            break;

        case rpSHORT:
            vertexFormatDecl[v++] = D3DVSD_REG(D3DVSDE_POSITION, D3DVSDT_SHORT3);
            break;

        case rpNORMALIZEDSHORTS:
            vertexFormatDecl[v++] = D3DVSD_REG(D3DVSDE_POSITION, D3DVSDT_NORMSHORT3);
            break;

        case rpNORMALIZEDPACKED:
            vertexFormatDecl[v++] = D3DVSD_REG(D3DVSDE_POSITION, D3DVSDT_NORMPACKED3);
            break;

        case rpFLOAT:
            vertexFormatDecl[v++] = D3DVSD_REG(D3DVSDE_POSITION, D3DVSDT_FLOAT3);
            break;
    }

    switch (fmt->norm)
    {
        case rpPACKEDBYTE:
            vertexFormatDecl[v++] = D3DVSD_REG(D3DVSDE_NORMAL, D3DVSDT_PBYTE3);
            break;

        case rpSHORT:
            vertexFormatDecl[v++] = D3DVSD_REG(D3DVSDE_NORMAL, D3DVSDT_SHORT3);
            break;

        case rpNORMALIZEDSHORTS:
            vertexFormatDecl[v++] = D3DVSD_REG(D3DVSDE_NORMAL, D3DVSDT_NORMSHORT3);
            break;

        case rpNORMALIZEDPACKED:
            vertexFormatDecl[v++] = D3DVSD_REG(D3DVSDE_NORMAL, D3DVSDT_NORMPACKED3);
            break;

        case rpFLOAT:
            vertexFormatDecl[v++] = D3DVSD_REG(D3DVSDE_NORMAL, D3DVSDT_FLOAT3);
            break;
    }

    if (fmt->prelit)
    {
        vertexFormatDecl[v++] = D3DVSD_REG(D3DVSDE_DIFFUSE, D3DVSDT_D3DCOLOR);
    }

    lastTexCoord = 0;
    if (fmt->texCoord)
    {
        RwUInt32    i;

        for (i = 0; i < 4; i++)
        {
            RpXboxCompType type = (RpXboxCompType)((fmt->texCoord >> (4 * i)) & 0xF);

            if (type == rpCOMPTYPENONE)
            {
                break;
            }

            switch (type)
            {
                case rpPACKEDBYTE:
                    vertexFormatDecl[v++] = D3DVSD_REG(rpWorldVSDETexFlags[i], D3DVSDT_PBYTE2);
                    break;

                case rpSHORT:
                    vertexFormatDecl[v++] = D3DVSD_REG(rpWorldVSDETexFlags[i], D3DVSDT_SHORT2);
                    break;

                case rpNORMALIZEDSHORTS:
                    vertexFormatDecl[v++] = D3DVSD_REG(rpWorldVSDETexFlags[i], D3DVSDT_NORMSHORT2);
                    break;

                case rpNORMALIZEDPACKED:
                    vertexFormatDecl[v++] = D3DVSD_REG(rpWorldVSDETexFlags[i], D3DVSDT_NORMPACKED3);
                    break;

                case rpFLOAT:
                    vertexFormatDecl[v++] = D3DVSD_REG(rpWorldVSDETexFlags[i], D3DVSDT_FLOAT2);
                    break;
            }
        }

        lastTexCoord = i;
    }

    if (fmt->bnt)
    {
        vertexFormatDecl[v++] = D3DVSD_REG(D3DVSDE_TEXCOORD0 + lastTexCoord, D3DVSDT_NORMPACKED3);
        vertexFormatDecl[v++] = D3DVSD_REG(D3DVSDE_TEXCOORD1 + lastTexCoord, D3DVSDT_NORMPACKED3);
    }

    vertexFormatDecl[v++] = D3DVSD_END();

    index = -(index + 1);

    if (rwXboxVertexFormatNumElems >= rwXboxVertexFormatMaxElems)
    {
        rwXboxVertexFormatMaxElems += 128;
        rwXboxVertexFormatArray = (_rpXboxVtxFmtDescItem *)
            RwRealloc(rwXboxVertexFormatArray,
                      sizeof(_rpXboxVtxFmtDescItem) * rwXboxVertexFormatMaxElems,
                      rwID_WORLDPIPEMODULE | rwMEMHINTDUR_FUNCTION |
                      rwMEMHINTFLAG_RESIZABLE);

        if (index > rwXboxVertexFormatNumElems)
        {
            index = rwXboxVertexFormatNumElems;
        }
    }
    else if (index < rwXboxVertexFormatNumElems)
    {
        memmove(&rwXboxVertexFormatArray[index + 1], &rwXboxVertexFormatArray[index],
                (rwXboxVertexFormatNumElems - index) * sizeof(_rpXboxVtxFmtDescItem));
    }

    rwXboxVertexFormatNumElems++;

    rwXboxVertexFormatArray[index].format = *fmt;

    if (D3D_OK != D3DDevice_CreateVertexShader(vertexFormatDecl, NULL,
                                               &rwXboxVertexFormatArray[index].handle, 0))
    {
        return 0;
    }

    return rwXboxVertexFormatArray[index].handle;
}

// match: __rpXboxDefaultInstance @ 0x002DED60
RwBool
_rpXboxDefaultInstance(RpXboxVtxFmt *fmt,
                       RwUInt32 flags,
                       RxXboxResEntryHeader *instancedHeader,
                       const RwV3d *positions,
                       const RwV3d *normals,
                       const RpVertexNormal *packedNormals,
                       const RwRGBA *color,
                       RwInt32 numTexCoordSets,
                       const RwTexCoords **texCoordSets,
                       RwUInt32 lockedSinceLastInst)
{
    RwInt32             numVertices;
    RwUInt8            *lockedVertexBuffer;
    RwUInt32            vbSize;
    RwUInt32            size;
    RwInt32             i;

    numVertices = instancedHeader->numVertices;

    if (numTexCoordSets > 4)
    {
        numTexCoordSets = 4;
    }

    if (*(RwUInt32 *)fmt == 0)
    {
        RpXboxVtxFmtInit(fmt, flags, numTexCoordSets);
    }

    if (!instancedHeader->vertexBuffer)
    {
        RxXboxInstanceData *instancedData;
        DWORD               shader;

        instancedHeader->stride = _rpXboxVtxFmtGetStride(fmt);

        shader = RxXboxGetVertexFormatShader(fmt);
        for (instancedData = instancedHeader->begin;
             instancedData != instancedHeader->end;
             instancedData++)
        {
            instancedData->vertexShader = shader;
        }

        vbSize = instancedHeader->stride * numVertices;
        instancedHeader->vertexBuffer = RwXbCreateVertexBuffer(vbSize);
        if (!instancedHeader->vertexBuffer)
        {
            return FALSE;
        }

        D3DVertexBuffer_Lock((D3DVertexBuffer *)instancedHeader->vertexBuffer, 0,
                             vbSize, &lockedVertexBuffer, 0);
    }
    else
    {
        D3DVertexBuffer    *currentVertexBuffer = (D3DVertexBuffer *)instancedHeader->vertexBuffer;

        vbSize = instancedHeader->stride * numVertices;

        if (currentVertexBuffer->Lock && D3DDevice_IsFencePending(currentVertexBuffer->Lock))
        {
            lockedVertexBuffer = RwXbVertexBufferLockDiscard(currentVertexBuffer, vbSize);
            lockedSinceLastInst = rpGEOMETRYLOCKALL;
        }
        else
        {
            D3DVertexBuffer_Lock(currentVertexBuffer, 0, vbSize, &lockedVertexBuffer, 0);
        }
    }

    if (positions)
    {
        if (lockedSinceLastInst & rpGEOMETRYLOCKVERTICES)
        {
            lockedVertexBuffer += _rpXboxVtxFmtInstV3d((RpXboxCompType)fmt->pos, lockedVertexBuffer,
                                        positions, numVertices, instancedHeader->stride);
        }
        else
        {
            lockedVertexBuffer += _rpXboxVtxFmtGetSize((RpXboxCompType)fmt->pos, 3);
        }

    }

    if (normals)
    {
        if (lockedSinceLastInst & rpGEOMETRYLOCKNORMALS)
        {
            size = _rpXboxVtxFmtInstV3d((RpXboxCompType)fmt->norm, lockedVertexBuffer,
                                        normals, numVertices, instancedHeader->stride);
        }
        else
        {
            size = _rpXboxVtxFmtGetSize((RpXboxCompType)fmt->norm, 3);
        }

        lockedVertexBuffer += size;
    }

    if (packedNormals)
    {
        if (lockedSinceLastInst & rpGEOMETRYLOCKNORMALS)
        {
            size = _rpXboxVtxFmtInstV3dComp((RpXboxCompType)fmt->norm, lockedVertexBuffer,
                                            packedNormals, numVertices, instancedHeader->stride);
        }
        else
        {
            size = _rpXboxVtxFmtGetSize((RpXboxCompType)fmt->norm, 3);
        }

        lockedVertexBuffer += size;
    }

    if (color)
    {
        if (lockedSinceLastInst & rpGEOMETRYLOCKPRELIGHT)
        {
            instancedHeader->vertexAlpha =
                _rpXboxVtxFmtInstColor(lockedVertexBuffer, color, numVertices,
                                       instancedHeader->stride);
        }

        lockedVertexBuffer += sizeof(RwUInt32);
    }

    for (i = 0; i < numTexCoordSets; i++)
    {
        RpXboxCompType type = (RpXboxCompType)((fmt->texCoord >> (4 * i)) & 0xF);

        if (lockedSinceLastInst & (rpGEOMETRYLOCKTEXCOORDS1 << i))
        {
            size = _rpXboxVtxFmtInstV2d(type, lockedVertexBuffer, (const RwV2d *)texCoordSets[i],
                                        numVertices, instancedHeader->stride);
        }
        else
        {
            size = _rpXboxVtxFmtGetSize(type, 2);
        }

        lockedVertexBuffer += size;
    }

    if (fmt->bnt &&
        (lockedSinceLastInst & (rpGEOMETRYLOCKPOLYGONS | rpGEOMETRYLOCKVERTICES |
                                rpGEOMETRYLOCKNORMALS)))
    {
        if (normals)
        {
            _rpXboxVtxFmtInstBNT(lockedVertexBuffer, positions, normals,
                                 texCoordSets[fmt->bnt - 1], instancedHeader,
                                 numVertices, instancedHeader->stride);
        }
        else
        {
            _rpXboxVtxFmtInstBNTComp(lockedVertexBuffer, positions, packedNormals,
                                     texCoordSets[fmt->bnt - 1], instancedHeader,
                                     numVertices, instancedHeader->stride);
        }
    }

    return TRUE;
}

// match: _rxXboxVtxFmtGeometryRead @ 0x002DF000
static RwStream *
rxXboxVtxFmtGeometryRead(RwStream *stream,
                         RwInt32 binaryLength __RWUNUSED__,
                         void *object,
                         RwInt32 offsetInObject __RWUNUSED__,
                         RwInt32 sizeInObject __RWUNUSED__)
{
    RpGeometry         *geometry = (RpGeometry *)object;
    RpXboxVtxFmt       *fmt;

    fmt = RpXboxGeometryGetVtxFmt(geometry);

    stream = RwStreamReadInt32(stream, (RwInt32 *)fmt, sizeof(RpXboxVtxFmt));
    if (stream)
    {
        RwResEntry *resEntry = geometry->repEntry;

        if (resEntry)
        {
            RxXboxResEntryHeader   *resEntryHeader = (RxXboxResEntryHeader *)(resEntry + 1);
            RxXboxInstanceData     *instancedData;
            DWORD                   shader;

            shader = RxXboxGetVertexFormatShader(fmt);

            for (instancedData = resEntryHeader->begin;
                 instancedData != resEntryHeader->end;
                 instancedData++)
            {
                instancedData->vertexShader = shader;
            }
        }
    }

    return stream;
}

// match: _rxXboxVtxFmtWorldSectorFixVertexShader @ 0x002DF060
static RpWorldSector *
rxXboxVtxFmtWorldSectorFixVertexShader(RpWorldSector *worldSector, void *data)
{
    RwResEntry *resEntry = worldSector->repEntry;

    if (resEntry)
    {
        RxXboxResEntryHeader   *resEntryHeader = (RxXboxResEntryHeader *)(resEntry + 1);
        RxXboxInstanceData     *instancedData;
        DWORD                   shader;

        shader = RxXboxGetVertexFormatShader((const RpXboxVtxFmt *)data);

        for (instancedData = resEntryHeader->begin;
             instancedData != resEntryHeader->end;
             instancedData++)
        {
            instancedData->vertexShader = shader;
        }
    }

    return worldSector;
}

// match: _rxXboxVtxFmtWorldRead @ 0x002DF0A0
static RwStream *
rxXboxVtxFmtWorldRead(RwStream *stream,
                      RwInt32 binaryLength __RWUNUSED__,
                      void *object,
                      RwInt32 offsetInObject __RWUNUSED__,
                      RwInt32 sizeInObject __RWUNUSED__)
{
    RpWorld            *world = (RpWorld *)object;
    RpXboxVtxFmt       *fmt;

    fmt = RpXboxWorldGetVtxFmt(world);

    stream = RwStreamReadInt32(stream, (RwInt32 *)fmt, sizeof(RpXboxVtxFmt));
    if (stream)
    {
        RpWorldForAllWorldSectors(world, rxXboxVtxFmtWorldSectorFixVertexShader, fmt);
    }

    return stream;
}

// match: __rpXboxVtxFmtPluginAttach @ 0x002DF0E0
RwBool
_rpXboxVtxFmtPluginAttach(void)
{
    if (RwEngineRegisterPlugin(0, rwID_VERTEXFMTPLUGIN,
                               rpXboxVtxFmtOpen, rpXboxVtxFmtClose) < 0)
    {
        return FALSE;
    }

    _rpXboxGeomVtxFmtOffset = RpGeometryRegisterPlugin(sizeof(RpXboxVtxFmt),
                                                       rwID_VERTEXFMTPLUGIN,
                                                       rxXboxVertexFmtConst,
                                                       rxXboxVertexFmtConst,
                                                       rxXboxVertexFmtCopy);
    if (_rpXboxGeomVtxFmtOffset < 0)
    {
        return FALSE;
    }

    RpGeometryRegisterPluginStream(rwID_VERTEXFMTPLUGIN,
                                   rxXboxVtxFmtGeometryRead,
                                   rxXboxVtxFmtWrite,
                                   rxXboxVtxFmtSize);

    rpXboxWorldVtxFmtOffset = RpWorldRegisterPlugin(sizeof(RpXboxVtxFmt),
                                                    rwID_VERTEXFMTPLUGIN,
                                                    rxXboxVertexFmtConst,
                                                    rxXboxVertexFmtConst,
                                                    rxXboxVertexFmtCopy);
    if (rpXboxWorldVtxFmtOffset < 0)
    {
        return FALSE;
    }

    RpWorldRegisterPluginStream(rwID_VERTEXFMTPLUGIN,
                                rxXboxVtxFmtWorldRead,
                                rxXboxVtxFmtWrite,
                                rxXboxVtxFmtSize);

    return TRUE;
}
