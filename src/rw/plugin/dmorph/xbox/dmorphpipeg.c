/*
 * codfh-match: RenderWare 3.6's Xbox delta morph pipeline, rebuilt from the
 * image; the file name is Godfather's debug build path (the image keeps no
 * RCS id for it), names the Godfather PDB's. All functions in this unit
 * match the game, including the instance callback and its block merger.
 */

#include <xtl.h>

#include <rwcore.h>
#include <rpworld.h>
#include <rpcriter.h>

#include "rpplugin.h"
#include "dmorph.h"
#include "dmphgeom.h"
#include "dmphintp.h"

#include "xbcache.h"
#include "xbmemory.h"
#include "xbpipe.h"
#include "xbvtxfmt.h"
#include "nodeXBoxAtomicAllInOne.h"

extern RwBool XboxDmorphAtomicInstanceCallback(void *object,
                                               RxXboxResEntryHeader *instancedHeader,
                                               RwBool reinstance);

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0BN@ENACMBJE@XboxDmoprhAtomicAllInOne?4csl?$AA@ @ 0x00419FB8
// match: _nodeXboxDmorphAtomicAllInOneCSL @ 0x00436E40

// match: _XBoxDmorphAtomicAllInOneNode @ 0x002F3F40
static RwBool
XBoxDmorphAtomicAllInOneNode(RxPipelineNode *self, const RxPipelineNodeParam *params)
{
    _rxXboxInstanceNodeData     *privateData;
    RpAtomic                    *atomic;
    RpGeometry                  *geometry;
    RwResEntry                  *resEntry;
    RwUInt32                    geomFlags;
    const rpDMorphGeometryData  *geometryData;
    const RwMatrix              *atomicLTM;
    D3DMATRIX                   matrix;

    atomic = (RpAtomic *)RxPipelineNodeParamGetData(params);

    geometry = RpAtomicGetGeometry(atomic);

    geomFlags = RpGeometryGetFlags(geometry);

    privateData = (_rxXboxInstanceNodeData *)self->privateData;

    geometryData = *RPDMORPHGEOMETRYGETCONSTDATA(geometry);

    if (!(rpGEOMETRYNATIVE & RpGeometryGetFlags(geometry)))
    {
        RpMeshHeader    *meshHeader;

        if (geometry->numVertices <= 0)
        {
            return TRUE;
        }

        meshHeader = geometry->mesh;
        if (meshHeader->numMeshes <= 0)
        {
            return TRUE;
        }

        if (RpGeometryGetNumMorphTargets(geometry) != 1)
        {
            resEntry = atomic->repEntry;
        }
        else
        {
            resEntry = geometry->repEntry;
        }

        if (resEntry)
        {
            if (((RxXboxResEntryHeader *)(resEntry + 1))->serialNumber != meshHeader->serialNum)
            {
                RwResourcesFreeResEntry(resEntry);
                resEntry = NULL;
            }
        }

        if (resEntry)
        {
            RxXboxResEntryHeader *resEntryHeader = (RxXboxResEntryHeader *)(resEntry + 1);

            RwResourcesUseResEntry(resEntry);

            if (geometryData)
            {
                XboxDmorphAtomicInstanceCallback(atomic, resEntryHeader, TRUE);
            }
            else if (geometry->lockedSinceLastInst && privateData->instanceCallback)
            {
                privateData->instanceCallback(atomic, resEntryHeader, TRUE);
            }
        }
        else
        {
            void        *owner;
            RwResEntry  **resEntryPointer;
            RwBool      nativeInstanceRequest;

            meshHeader = geometry->mesh;

            if (RpGeometryGetNumMorphTargets(geometry) != 1)
            {
                owner = (void *)atomic;
                resEntryPointer = &atomic->repEntry;
            }
            else
            {
                owner = (void *)geometry;
                resEntryPointer = &geometry->repEntry;
            }

            nativeInstanceRequest = (RpGeometryGetFlags(geometry) & rpGEOMETRYNATIVEINSTANCE) != 0;

            if (geometryData)
            {
                resEntry = _rxXBInstance(atomic, owner, resEntryPointer, meshHeader,
                                         geometry->numVertices,
                                         XboxDmorphAtomicInstanceCallback,
                                         nativeInstanceRequest);
            }
            else
            {
                resEntry = _rxXBInstance(atomic, owner, resEntryPointer, meshHeader,
                                         geometry->numVertices,
                                         privateData->instanceCallback,
                                         nativeInstanceRequest);
            }
            if (!resEntry)
            {
                return FALSE;
            }
        }

        geometry->lockedSinceLastInst = 0;
    }
    else
    {
        resEntry = geometry->repEntry;
    }

    if (rpGEOMETRYNATIVEINSTANCE & RpGeometryGetFlags(geometry))
    {
        return TRUE;
    }

    if (privateData->lightingCallback)
    {
        privateData->lightingCallback(atomic);
    }

    atomicLTM = RwFrameGetLTM(RpAtomicGetFrame(atomic));

    matrix._11 = atomicLTM->right.x;
    matrix._12 = atomicLTM->right.y;
    matrix._13 = atomicLTM->right.z;
    matrix._14 = 0.0f;

    matrix._21 = atomicLTM->up.x;
    matrix._22 = atomicLTM->up.y;
    matrix._23 = atomicLTM->up.z;
    matrix._24 = 0.0f;

    matrix._31 = atomicLTM->at.x;
    matrix._32 = atomicLTM->at.y;
    matrix._33 = atomicLTM->at.z;
    matrix._34 = 0.0f;

    matrix._41 = atomicLTM->pos.x;
    matrix._42 = atomicLTM->pos.y;
    matrix._43 = atomicLTM->pos.z;
    matrix._44 = 1.0f;

    D3DDevice_SetTransform(D3DTS_WORLD, &matrix);

    /* the morphed normals are not unit length */
    _rwXbRenderStateForce(D3DRS_NORMALIZENORMALS, TRUE);

    if (privateData->renderCallback)
    {
        if (geometryData && geometryData->platformData.vertexBuffer)
        {
            D3DDevice_SetStreamSource(1, (D3DVertexBuffer *)geometryData->platformData.vertexBuffer,
                                      geometryData->platformData.stride);
        }

        privateData->renderCallback((RxXboxResEntryHeader *)(resEntry + 1), atomic,
                                    rpATOMIC, geomFlags);

        if (geometryData && geometryData->platformData.vertexBuffer)
        {
            D3DDevice_SetStreamSource(1, NULL, 0);
        }
    }

    return TRUE;
}

static RxPipeline *_rwDMorphPipelines[rpDMORPHTYPEGENERIC + 1];

// match: _rxXBDmorphAtomicAllInOnePipelineInit @ 0x002F4200
RwBool
rxXBDmorphAtomicAllInOnePipelineInit(RxPipelineNode *node)
{
    _rxXboxInstanceNodeData *instanceData = (_rxXboxInstanceNodeData *)node->privateData;

    instanceData->instanceCallback = _rxXBAtomicDefaultInstanceCallback;
    instanceData->reinstanceCallback = NULL;
    instanceData->lightingCallback = _rwXbAtomicDefaultLightingCallback;
    instanceData->renderCallback = _rxXbDefaultRenderCallback;

    return TRUE;
}

static RxNodeDefinition nodeXboxDmorphAtomicAllInOneCSL =
{
    "XboxDmoprhAtomicAllInOne.csl",     /* sic: the image's and the Godfather PDB's name */
    {
        XBoxDmorphAtomicAllInOneNode,
        (RxNodeInitFn)NULL,
        (RxNodeTermFn)NULL,
        rxXBDmorphAtomicAllInOnePipelineInit,
        (RxPipelineNodeTermFn)NULL,
        (RxPipelineNodeConfigFn)NULL,
        (RxConfigMsgHandlerFn)NULL
    },
    {
        0,
        (RxClusterRef *)NULL,
        (RxClusterValidityReq *)NULL,
        0,
        (RwChar **)NULL
    },
    (RwUInt32)sizeof(_rxXboxInstanceNodeData),
    (RxNodeDefEditable)FALSE,
    0
};

// match: __rpDMorphGeometryDtor @ 0x002F2830
void
_rpDMorphGeometryDtor(rpDMorphGeometryData *geometryData)
{
    if (geometryData)
    {
        if (geometryData->platformData.vertexBuffer)
        {
            RwXbReleaseVertexBuffer((D3DVertexBuffer *)geometryData->platformData.vertexBuffer);
            geometryData->platformData.vertexBuffer = NULL;
        }
    }
}

typedef struct _BlockInfo _BlockInfo;
struct _BlockInfo
{
    RwUInt32    firstVertex;
    RwUInt32    numVertex;
};

// match: _XboxDMorphAddBlock @ 0x002F2860
static RwUInt32
XboxDMorphAddBlock(RwUInt32 numBlocks, _BlockInfo *blocks,
                   RwUInt32 firstVertex, RwUInt32 numVertex)
{
    RwUInt32    lastVertexBlockToAdd;
    RwUInt32    n;

    lastVertexBlockToAdd = firstVertex + numVertex;

    for (n = 0; n < numBlocks; n++)
    {
        if (firstVertex >= blocks[n].firstVertex)
        {
            RwUInt32    lastVertexBlock;

            lastVertexBlock = blocks[n].firstVertex + blocks[n].numVertex;

            if (firstVertex < lastVertexBlock)
            {
                if (lastVertexBlockToAdd > lastVertexBlock)
                {
                    blocks[n].numVertex += lastVertexBlockToAdd - lastVertexBlock;
                }
                break;
            }
            else if (firstVertex == lastVertexBlock)
            {
                blocks[n].numVertex += numVertex;
                break;
            }
        }
        else if (lastVertexBlockToAdd == blocks[n].firstVertex)
        {
            blocks[n].firstVertex = firstVertex;
            blocks[n].numVertex += numVertex;
            break;
        }
    }

    if (n >= numBlocks)
    {
        blocks[numBlocks].firstVertex = firstVertex;
        blocks[numBlocks].numVertex = numVertex;
        numBlocks++;
    }

    return numBlocks;
}

// match: _XboxDmorphAtomicInstanceCallback @ 0x002F28D0
RwBool
XboxDmorphAtomicInstanceCallback(void *object,
                                 RxXboxResEntryHeader *instancedHeader,
                                 RwBool reinstance)
{
    RpAtomic                *atomic = (RpAtomic *)object;
    RpGeometry              *geometry = RpAtomicGetGeometry(atomic);
    RwUInt32                flags = RpGeometryGetFlags(geometry);
    rpDMorphAtomicData      *atomicData = RPDMORPHATOMICGETDATA(atomic);
    rpDMorphGeometryData    *geometryData = *RPDMORPHGEOMETRYGETDATA(RpAtomicGetGeometry(atomic));
    RwUInt32                dmorphLockedSinceLastInst;
    RwUInt32                dmorphFlags;
    RwUInt32                numBlocks;
    RwUInt32                i;

    dmorphLockedSinceLastInst = 0;
    dmorphFlags = 0;
    numBlocks = 0;

    if (geometryData && atomicData->values)
    {
        for (i = 0; i < geometryData->numDMorphTargets; i++)
        {
            const RpDMorphTarget *dMorphTarget = &geometryData->dMorphTargets[i];

            dmorphFlags |= dMorphTarget->flags;

            if (atomicData->values[i] != geometryData->currValues[i])
            {
                const rpDMorphRLE   *rle = &dMorphTarget->rle;
                RwUInt32            j;

                for (j = 0; j < rle->numCodeElements; j++)
                {
                    if ((rle->code[j] & 0x7F) && (rle->code[j] & 0x80))
                    {
                        numBlocks++;
                    }
                }

                if (dMorphTarget->flags & rpGEOMETRYPOSITIONS)
                {
                    dmorphLockedSinceLastInst |= rpGEOMETRYLOCKVERTICES;
                }
                if (dMorphTarget->flags & rpGEOMETRYNORMALS)
                {
                    dmorphLockedSinceLastInst |= rpGEOMETRYLOCKNORMALS;
                }
                if (dMorphTarget->flags & rpGEOMETRYPRELIT)
                {
                    dmorphLockedSinceLastInst |= rpGEOMETRYLOCKPRELIGHT;
                }
                if (dMorphTarget->flags & rpGEOMETRYTEXTURED)
                {
                    dmorphLockedSinceLastInst |= rpGEOMETRYLOCKTEXCOORDS1;
                }
            }
        }
    }

    if (dmorphLockedSinceLastInst || !reinstance || geometry->lockedSinceLastInst)
    {
        RpXboxVtxFmt        *fmt;
        RwUInt32            vbSize;
        RwUInt8             *lockedVertexBuffer = NULL;
        RwUInt8             *lockedVertexBufferStatic = NULL;
        RwUInt8             *dstVertices = NULL;
        RwUInt8             *dstNormals = NULL;
        RwUInt8             *dstPreLightColors = NULL;
        RwUInt8             *dstTexCoords = NULL;
        RwUInt8             *currentVertexBuffer;
        RwUInt8             *currentVertexBufferStatic;
        RwV3d               *positions;
        RwV3d               *normals;
        RwRGBA              *color;
        RwUInt32            numTexCoordSets;
        RwTexCoords         **texCoordSets;
        RwUInt32            lockedSinceLastInst;
        RwUInt32            numVertices;
        RwUInt32            flagsStatic;

        fmt = RpXboxGeometryGetVtxFmt(geometry);

        positions = geometry->morphTarget->verts;

        normals = (flags & rxGEOMETRY_NORMALS) ? geometry->morphTarget->normals : NULL;

        color = (flags & rxGEOMETRY_PRELIT) ? RpGeometryGetPreLightColors(geometry) : NULL;

        numTexCoordSets = ((flags & rxGEOMETRY_TEXTURED) || (flags & rpGEOMETRYTEXTURED2)) ? geometry->numTexCoordSets : 0;

        texCoordSets = ((flags & rxGEOMETRY_TEXTURED) || (flags & rpGEOMETRYTEXTURED2)) ? geometry->texCoords : NULL;

        lockedSinceLastInst = (reinstance) ? geometry->lockedSinceLastInst : rpGEOMETRYLOCKALL;

        numVertices = instancedHeader->numVertices;

        if (numTexCoordSets > 4)
        {
            numTexCoordSets = 4;
        }

        if (*((RwUInt32 *)fmt) == 0)
        {
            RpXboxVtxFmtInit(fmt, flags, numTexCoordSets);
        }

        if (instancedHeader->vertexBuffer == NULL)
        {
            DWORD               vertexFormatDecl[256];
            DWORD               shader;
            RxXboxInstanceData  *mesh;

            if (dmorphFlags)
            {
                geometryData->platformData.geometryFlags = (flags & ~dmorphFlags) & rpGEOMETRYFLAGSMASK;
            }
            else
            {
                dmorphFlags = flags;
                geometryData->platformData.geometryFlags = 0;
            }

            vertexFormatDecl[0] = D3DVSD_STREAM(0);
            i = 1;
            instancedHeader->stride = 0;

            if (dmorphFlags & rxGEOMETRY_POSITIONS)
            {
                switch (fmt->pos)
                {
                    case rpPACKEDBYTE:
                        vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_POSITION, D3DVSDT_PBYTE3);
                        instancedHeader->stride += 3;
                        break;

                    case rpSHORT:
                        vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_POSITION, D3DVSDT_SHORT3);
                        instancedHeader->stride += 6;
                        break;

                    case rpNORMALIZEDSHORTS:
                        vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_POSITION, D3DVSDT_NORMSHORT3);
                        instancedHeader->stride += 6;
                        break;

                    case rpNORMALIZEDPACKED:
                        vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_POSITION, D3DVSDT_NORMPACKED3);
                        instancedHeader->stride += 4;
                        break;

                    case rpFLOAT:
                        vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_POSITION, D3DVSDT_FLOAT3);
                        instancedHeader->stride += 12;
                        break;
                }
            }

            if (dmorphFlags & rxGEOMETRY_NORMALS)
            {
                switch (fmt->norm)
                {
                    case rpPACKEDBYTE:
                        vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_NORMAL, D3DVSDT_PBYTE3);
                        instancedHeader->stride += 3;
                        break;

                    case rpSHORT:
                        vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_NORMAL, D3DVSDT_SHORT3);
                        instancedHeader->stride += 6;
                        break;

                    case rpNORMALIZEDSHORTS:
                        vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_NORMAL, D3DVSDT_NORMSHORT3);
                        instancedHeader->stride += 6;
                        break;

                    case rpNORMALIZEDPACKED:
                        vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_NORMAL, D3DVSDT_NORMPACKED3);
                        instancedHeader->stride += 4;
                        break;

                    case rpFLOAT:
                        vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_NORMAL, D3DVSDT_FLOAT3);
                        instancedHeader->stride += 12;
                        break;
                }
            }

            if (dmorphFlags & rxGEOMETRY_PRELIT)
            {
                vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_DIFFUSE, D3DVSDT_D3DCOLOR);
                instancedHeader->stride += 4;
            }

            if (dmorphFlags & rxGEOMETRY_TEXTURED)
            {
                RpXboxCompType type = (RpXboxCompType)(fmt->texCoord & 0xF);

                if (type != rpCOMPTYPENONE)
                {
                    switch (type)
                    {
                        case rpPACKEDBYTE:
                            vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_TEXCOORD0, D3DVSDT_PBYTE2);
                            instancedHeader->stride += 2;
                            break;

                        case rpSHORT:
                            vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_TEXCOORD0, D3DVSDT_SHORT2);
                            instancedHeader->stride += 4;
                            break;

                        case rpNORMALIZEDSHORTS:
                            vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_TEXCOORD0, D3DVSDT_NORMSHORT2);
                            instancedHeader->stride += 4;
                            break;

                        case rpNORMALIZEDPACKED:
                            vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_TEXCOORD0, D3DVSDT_NORMPACKED3);
                            instancedHeader->stride += 4;
                            break;

                        case rpFLOAT:
                            vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_TEXCOORD0, D3DVSDT_FLOAT2);
                            instancedHeader->stride += 8;
                            break;
                    }
                }
            }

            if (dmorphFlags & rpGEOMETRYTEXTURED2)
            {
                RpXboxCompType type = (RpXboxCompType)((fmt->texCoord >> 4) & 0xF);

                if (type != rpCOMPTYPENONE)
                {
                    switch (type)
                    {
                        case rpPACKEDBYTE:
                            vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_TEXCOORD1, D3DVSDT_PBYTE2);
                            instancedHeader->stride += 2;
                            break;

                        case rpSHORT:
                            vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_TEXCOORD1, D3DVSDT_SHORT2);
                            instancedHeader->stride += 4;
                            break;

                        case rpNORMALIZEDSHORTS:
                            vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_TEXCOORD1, D3DVSDT_NORMSHORT2);
                            instancedHeader->stride += 4;
                            break;

                        case rpNORMALIZEDPACKED:
                            vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_TEXCOORD1, D3DVSDT_NORMPACKED3);
                            instancedHeader->stride += 4;
                            break;

                        case rpFLOAT:
                            vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_TEXCOORD1, D3DVSDT_FLOAT2);
                            instancedHeader->stride += 8;
                            break;
                    }
                }
            }

            geometryData->platformData.stride = 0;

            if (geometryData->platformData.geometryFlags)
            {
                vertexFormatDecl[i++] = D3DVSD_STREAM(1);

                if (geometryData->platformData.geometryFlags & rxGEOMETRY_POSITIONS)
                {
                    switch (fmt->pos)
                    {
                        case rpPACKEDBYTE:
                            vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_POSITION, D3DVSDT_PBYTE3);
                            geometryData->platformData.stride += 3;
                            break;

                        case rpSHORT:
                            vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_POSITION, D3DVSDT_SHORT3);
                            geometryData->platformData.stride += 6;
                            break;

                        case rpNORMALIZEDSHORTS:
                            vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_POSITION, D3DVSDT_NORMSHORT3);
                            geometryData->platformData.stride += 6;
                            break;

                        case rpNORMALIZEDPACKED:
                            vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_POSITION, D3DVSDT_NORMPACKED3);
                            geometryData->platformData.stride += 4;
                            break;

                        case rpFLOAT:
                            vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_POSITION, D3DVSDT_FLOAT3);
                            geometryData->platformData.stride += 12;
                            break;
                    }
                }

                if (geometryData->platformData.geometryFlags & rxGEOMETRY_NORMALS)
                {
                    switch (fmt->norm)
                    {
                        case rpPACKEDBYTE:
                            vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_NORMAL, D3DVSDT_PBYTE3);
                            geometryData->platformData.stride += 3;
                            break;

                        case rpSHORT:
                            vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_NORMAL, D3DVSDT_SHORT3);
                            geometryData->platformData.stride += 6;
                            break;

                        case rpNORMALIZEDSHORTS:
                            vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_NORMAL, D3DVSDT_NORMSHORT3);
                            geometryData->platformData.stride += 6;
                            break;

                        case rpNORMALIZEDPACKED:
                            vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_NORMAL, D3DVSDT_NORMPACKED3);
                            geometryData->platformData.stride += 4;
                            break;

                        case rpFLOAT:
                            vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_NORMAL, D3DVSDT_FLOAT3);
                            geometryData->platformData.stride += 12;
                            break;
                    }
                }

                if (geometryData->platformData.geometryFlags & rxGEOMETRY_PRELIT)
                {
                    vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_DIFFUSE, D3DVSDT_D3DCOLOR);
                    geometryData->platformData.stride += 4;
                }

                if (geometryData->platformData.geometryFlags & rxGEOMETRY_TEXTURED)
                {
                    RpXboxCompType type = (RpXboxCompType)(fmt->texCoord & 0xF);

                    if (type != rpCOMPTYPENONE)
                    {
                        switch (type)
                        {
                            case rpPACKEDBYTE:
                                vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_TEXCOORD0, D3DVSDT_PBYTE2);
                                geometryData->platformData.stride += 2;
                                break;

                            case rpSHORT:
                                vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_TEXCOORD0, D3DVSDT_SHORT2);
                                geometryData->platformData.stride += 4;
                                break;

                            case rpNORMALIZEDSHORTS:
                                vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_TEXCOORD0, D3DVSDT_NORMSHORT2);
                                geometryData->platformData.stride += 4;
                                break;

                            case rpNORMALIZEDPACKED:
                                vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_TEXCOORD0, D3DVSDT_NORMPACKED3);
                                geometryData->platformData.stride += 4;
                                break;

                            case rpFLOAT:
                                vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_TEXCOORD0, D3DVSDT_FLOAT2);
                                geometryData->platformData.stride += 8;
                                break;
                        }
                    }
                }

                if (geometryData->platformData.geometryFlags & rpGEOMETRYTEXTURED2)
                {
                    RpXboxCompType type = (RpXboxCompType)((fmt->texCoord >> 4) & 0xF);

                    if (type != rpCOMPTYPENONE)
                    {
                        switch (type)
                        {
                            case rpPACKEDBYTE:
                                vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_TEXCOORD1, D3DVSDT_PBYTE2);
                                geometryData->platformData.stride += 2;
                                break;

                            case rpSHORT:
                                vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_TEXCOORD1, D3DVSDT_SHORT2);
                                geometryData->platformData.stride += 4;
                                break;

                            case rpNORMALIZEDSHORTS:
                                vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_TEXCOORD1, D3DVSDT_NORMSHORT2);
                                geometryData->platformData.stride += 4;
                                break;

                            case rpNORMALIZEDPACKED:
                                vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_TEXCOORD1, D3DVSDT_NORMPACKED3);
                                geometryData->platformData.stride += 4;
                                break;

                            case rpFLOAT:
                                vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_TEXCOORD1, D3DVSDT_FLOAT2);
                                geometryData->platformData.stride += 8;
                                break;
                        }
                    }
                }
            }

            vertexFormatDecl[i++] = D3DVSD_END();

            if (D3D_OK != D3DDevice_CreateVertexShader(vertexFormatDecl, NULL, &shader, 0))
            {
                return FALSE;
            }

            for (mesh = instancedHeader->begin; mesh != instancedHeader->end; mesh++)
            {
                mesh->vertexShader = shader;
            }

            vbSize = instancedHeader->stride * numVertices;
            instancedHeader->vertexBuffer = RwXbCreateVertexBuffer(vbSize);
            if (instancedHeader->vertexBuffer == NULL)
            {
                return FALSE;
            }

            D3DVertexBuffer_Lock((D3DVertexBuffer *)instancedHeader->vertexBuffer, 0, vbSize, &lockedVertexBuffer, 0);

            if (geometryData->platformData.vertexBuffer)
            {
                RwXbReleaseVertexBuffer((D3DVertexBuffer *)geometryData->platformData.vertexBuffer);
                geometryData->platformData.vertexBuffer = NULL;
            }

            if (geometryData->platformData.stride)
            {
                vbSize = geometryData->platformData.stride * numVertices;
                geometryData->platformData.vertexBuffer = RwXbCreateVertexBuffer(vbSize);
                if (geometryData->platformData.vertexBuffer == NULL)
                {
                    return FALSE;
                }

                D3DVertexBuffer_Lock((D3DVertexBuffer *)geometryData->platformData.vertexBuffer, 0, vbSize, &lockedVertexBufferStatic, 0);
            }
            else
            {
                geometryData->platformData.vertexBuffer = NULL;
            }
        }
        else
        {
            D3DVertexBuffer     *pBuffer = (D3DVertexBuffer *)instancedHeader->vertexBuffer;
            RwUInt32            lockFlagsStatic;

            lockFlagsStatic = 0;
            if (geometryData->platformData.geometryFlags & rxGEOMETRY_POSITIONS)
            {
                lockFlagsStatic = rpGEOMETRYLOCKVERTICES;
            }
            if (geometryData->platformData.geometryFlags & rxGEOMETRY_NORMALS)
            {
                lockFlagsStatic |= rpGEOMETRYLOCKNORMALS;
            }
            if (geometryData->platformData.geometryFlags & rxGEOMETRY_PRELIT)
            {
                lockFlagsStatic |= rpGEOMETRYLOCKPRELIGHT;
            }
            if (geometryData->platformData.geometryFlags & rxGEOMETRY_TEXTURED)
            {
                lockFlagsStatic |= rpGEOMETRYLOCKTEXCOORDS1;
            }
            if (geometryData->platformData.geometryFlags & rpGEOMETRYTEXTURED2)
            {
                lockFlagsStatic |= rpGEOMETRYLOCKTEXCOORDS2;
            }

            vbSize = instancedHeader->stride * numVertices;

            if (pBuffer->Lock && D3DDevice_IsFencePending(pBuffer->Lock))
            {
                lockedVertexBuffer = RwXbVertexBufferLockDiscard(pBuffer, vbSize);
                reinstance = FALSE;
                lockedSinceLastInst |= (~lockFlagsStatic & rpGEOMETRYLOCKALL);
            }
            else
            {
                D3DVertexBuffer_Lock(pBuffer, 0, vbSize, &lockedVertexBuffer, 0);
            }

            if (lockedSinceLastInst & lockFlagsStatic)
            {
                vbSize = geometryData->platformData.stride * numVertices;
                D3DVertexBuffer_Lock((D3DVertexBuffer *)geometryData->platformData.vertexBuffer, 0, vbSize, &lockedVertexBufferStatic, 0);
            }
        }

        flagsStatic = geometryData->platformData.geometryFlags;
        lockedSinceLastInst &= ~dmorphLockedSinceLastInst;

        currentVertexBuffer = lockedVertexBuffer;
        currentVertexBufferStatic = lockedVertexBufferStatic;

        if (positions)
        {
            RwInt32             size;
            if (flagsStatic & rxGEOMETRY_POSITIONS)
            {
                dstVertices = currentVertexBufferStatic;
                if (lockedSinceLastInst & rpGEOMETRYLOCKVERTICES)
                {
                    size = _rpXboxVtxFmtInstV3d((RpXboxCompType)fmt->pos,
                                                currentVertexBufferStatic,
                                                positions, numVertices,
                                                geometryData->platformData.stride);
                }
                else
                {
                    size = _rpXboxVtxFmtGetSize((RpXboxCompType)fmt->pos, 3);
                }
                currentVertexBufferStatic += size;
            }
            else
            {
                dstVertices = currentVertexBuffer;
                if (lockedSinceLastInst & rpGEOMETRYLOCKVERTICES)
                {
                    size = _rpXboxVtxFmtInstV3d((RpXboxCompType)fmt->pos,
                                                currentVertexBuffer,
                                                positions, numVertices,
                                                instancedHeader->stride);
                }
                else
                {
                    size = _rpXboxVtxFmtGetSize((RpXboxCompType)fmt->pos, 3);
                }
                currentVertexBuffer += size;
            }
        }

        if (normals)
        {
            if (flagsStatic & rxGEOMETRY_NORMALS)
            {
                dstNormals = currentVertexBufferStatic;
                if (lockedSinceLastInst & rpGEOMETRYLOCKNORMALS)
                {
                    currentVertexBufferStatic += _rpXboxVtxFmtInstV3d((RpXboxCompType)fmt->norm,
                                                                      currentVertexBufferStatic,
                                                                      normals, numVertices,
                                                                      geometryData->platformData.stride);
                }
                else
                {
                    currentVertexBufferStatic += _rpXboxVtxFmtGetSize((RpXboxCompType)fmt->norm, 3);
                }
            }
            else
            {
                dstNormals = currentVertexBuffer;
                if (lockedSinceLastInst & rpGEOMETRYLOCKNORMALS)
                {
                    currentVertexBuffer += _rpXboxVtxFmtInstV3d((RpXboxCompType)fmt->norm,
                                                                currentVertexBuffer,
                                                                normals, numVertices,
                                                                instancedHeader->stride);
                }
                else
                {
                    currentVertexBuffer += _rpXboxVtxFmtGetSize((RpXboxCompType)fmt->norm, 3);
                }
            }
        }

        if (color)
        {
            if (flagsStatic & rxGEOMETRY_PRELIT)
            {
                dstPreLightColors = currentVertexBufferStatic;
                if (lockedSinceLastInst & rpGEOMETRYLOCKPRELIGHT)
                {
                    instancedHeader->vertexAlpha =
                        _rpXboxVtxFmtInstColor(currentVertexBufferStatic, color, numVertices,
                                               geometryData->platformData.stride);
                }
                currentVertexBufferStatic += sizeof(RwRGBA);
            }
            else
            {
                dstPreLightColors = currentVertexBuffer;
                if (lockedSinceLastInst & rpGEOMETRYLOCKPRELIGHT)
                {
                    instancedHeader->vertexAlpha =
                        _rpXboxVtxFmtInstColor(currentVertexBuffer, color, numVertices,
                                               instancedHeader->stride);
                }
                currentVertexBuffer += sizeof(RwRGBA);
            }
        }

        if (flagsStatic & (rxGEOMETRY_TEXTURED | rpGEOMETRYTEXTURED2))
        {
            dstTexCoords = currentVertexBufferStatic;
            for (i = 0; i < (RwUInt32)numTexCoordSets; i++)
            {
                RpXboxCompType type = (RpXboxCompType)((fmt->texCoord >> (4 * i)) & 0xF);

                if (lockedSinceLastInst & (rpGEOMETRYLOCKTEXCOORDS1 << i))
                {
                    currentVertexBufferStatic += _rpXboxVtxFmtInstV2d(type, currentVertexBufferStatic,
                                                                      texCoordSets[i], numVertices,
                                                                      geometryData->platformData.stride);
                }
                else
                {
                    currentVertexBufferStatic += _rpXboxVtxFmtGetSize(type, 2);
                }
            }
        }
        else
        {
            dstTexCoords = currentVertexBuffer;
            for (i = 0; i < (RwUInt32)numTexCoordSets; i++)
            {
                RpXboxCompType type = (RpXboxCompType)((fmt->texCoord >> (4 * i)) & 0xF);

                if (lockedSinceLastInst & (rpGEOMETRYLOCKTEXCOORDS1 << i))
                {
                    currentVertexBuffer += _rpXboxVtxFmtInstV2d(type, currentVertexBuffer,
                                                                texCoordSets[i], numVertices,
                                                                instancedHeader->stride);
                }
                else
                {
                    currentVertexBuffer += _rpXboxVtxFmtGetSize(type, 2);
                }
            }
        }

        if (dmorphLockedSinceLastInst)
        {
            /* Shared across the attribute passes; retain these local lifetimes. */
            _BlockInfo             *blocks;
            RwUInt32                currentBlock;
            RwUInt32                l;
            RwUInt32                j;
            const RpDMorphTarget   *dMorphTarget;
            const rpDMorphRLE      *rle;
            RwReal                  scale;
            const RwV3d            *deltaVertices;
            const RwV3d            *deltaNormals;
            const RwRGBA           *deltaPreLightColors;
            const RwTexCoords      *deltaTexCoords;

            blocks = (_BlockInfo *)RwMalloc(sizeof(_BlockInfo) * numBlocks, 0);

            if (dmorphLockedSinceLastInst & rpGEOMETRYLOCKVERTICES)
            {
                currentBlock = 0;

                for (i = 0; i < geometryData->numDMorphTargets; i++)
                {
                    if (atomicData->values[i] != geometryData->currValues[i])
                    {
                        dMorphTarget = &geometryData->dMorphTargets[i];

                        if (dMorphTarget->flags & rpGEOMETRYPOSITIONS)
                        {
                            RwUInt32                k;

                            scale = atomicData->values[i] - geometryData->currValues[i];
                            rle = &dMorphTarget->rle;
                            deltaVertices = dMorphTarget->vertices;

                            for (j = 0, k = 0; j < rle->numCodeElements; j++)
                            {
                                RwUInt32    maxl = rle->code[j] & 0x7F;

                                if (maxl)
                                {
                                    if (rle->code[j] & 0x80)
                                    {
                                        if (reinstance)
                                        {
                                            currentBlock = XboxDMorphAddBlock(currentBlock, blocks, k, maxl);
                                        }

                                        for (l = 0; l < maxl; l++)
                                        {
                                            positions[k].x += deltaVertices->x * scale;
                                            positions[k].y += deltaVertices->y * scale;
                                            positions[k].z += deltaVertices->z * scale;
                                            k++;
                                            deltaVertices++;
                                        }
                                    }
                                    else
                                    {
                                        k += maxl;
                                    }
                                }
                            }
                        }
                    }
                }

                if (reinstance)
                {
                    const RwUInt32  stride = instancedHeader->stride;

                    for (l = 0; l < currentBlock; l++)
                    {
                        _rpXboxVtxFmtInstV3d((RpXboxCompType)fmt->pos,
                                             &dstVertices[stride * blocks[l].firstVertex],
                                             &positions[blocks[l].firstVertex],
                                             blocks[l].numVertex, stride);
                    }
                }
                else
                {
                    _rpXboxVtxFmtInstV3d((RpXboxCompType)fmt->pos, dstVertices, positions,
                                         numVertices, instancedHeader->stride);
                }
            }

            if (dmorphLockedSinceLastInst & rpGEOMETRYLOCKNORMALS)
            {
                currentBlock = 0;

                for (i = 0; i < geometryData->numDMorphTargets; i++)
                {
                    if (atomicData->values[i] != geometryData->currValues[i])
                    {
                        dMorphTarget = &geometryData->dMorphTargets[i];

                        if (dMorphTarget->flags & rpGEOMETRYNORMALS)
                        {
                            RwUInt32                k;

                            scale = atomicData->values[i] - geometryData->currValues[i];
                            rle = &dMorphTarget->rle;
                            deltaNormals = dMorphTarget->normals;

                            for (j = 0, k = 0; j < rle->numCodeElements; j++)
                            {
                                RwUInt32    maxl = rle->code[j] & 0x7F;

                                if (maxl)
                                {
                                    if (rle->code[j] & 0x80)
                                    {
                                        if (reinstance)
                                        {
                                            currentBlock = XboxDMorphAddBlock(currentBlock, blocks, k, maxl);
                                        }

                                        for (l = 0; l < maxl; l++)
                                        {
                                            normals[k].x += deltaNormals->x * scale;
                                            normals[k].y += deltaNormals->y * scale;
                                            normals[k].z += deltaNormals->z * scale;
                                            k++;
                                            deltaNormals++;
                                        }
                                    }
                                    else
                                    {
                                        k += maxl;
                                    }
                                }
                            }
                        }
                    }
                }

                if (reinstance)
                {
                    const RwUInt32  stride = instancedHeader->stride;

                    for (l = 0; l < currentBlock; l++)
                    {
                        _rpXboxVtxFmtInstV3d((RpXboxCompType)fmt->norm,
                                             &dstNormals[stride * blocks[l].firstVertex],
                                             &normals[blocks[l].firstVertex],
                                             blocks[l].numVertex, stride);
                    }
                }
                else
                {
                    _rpXboxVtxFmtInstV3d((RpXboxCompType)fmt->norm, dstNormals, normals,
                                         numVertices, instancedHeader->stride);
                }
            }

            if (dmorphLockedSinceLastInst & rpGEOMETRYLOCKPRELIGHT)
            {
                currentBlock = 0;

                for (i = 0; i < geometryData->numDMorphTargets; i++)
                {
                    if (atomicData->values[i] != geometryData->currValues[i])
                    {
                        dMorphTarget = &geometryData->dMorphTargets[i];

                        if (dMorphTarget->flags & rpGEOMETRYPRELIT)
                        {
                            RwUInt32                k;
                            RwUInt32                m;

                            rle = &dMorphTarget->rle;
                            deltaPreLightColors = dMorphTarget->preLightColors;

                            for (j = 0, k = 0, m = 0; j < rle->numCodeElements; j++)
                            {
                                RwUInt32    maxl = rle->code[j] & 0x7F;

                                if (maxl)
                                {
                                    if (rle->code[j] & 0x80)
                                    {
                                        if (reinstance)
                                        {
                                            currentBlock = XboxDMorphAddBlock(currentBlock, blocks, k, maxl);
                                        }

                                        for (l = 0; l < maxl; l++)
                                        {
                                            RwInt32 shift;
                                            const RwReal lastValue = geometryData->currValues[i];
                                            const RwReal thisValue = atomicData->values[i];

                                            shift = (RwInt32)(deltaPreLightColors[m].red * thisValue -
                                                                      deltaPreLightColors[m].red * lastValue);
                                            color[k].red += (RwUInt8)shift;
                                            shift = (RwInt32)(deltaPreLightColors[m].green * thisValue -
                                                                        deltaPreLightColors[m].green * lastValue);
                                            color[k].green += (RwUInt8)shift;
                                            shift = (RwInt32)(deltaPreLightColors[m].blue * thisValue -
                                                                       deltaPreLightColors[m].blue * lastValue);
                                            color[k].blue += (RwUInt8)shift;
                                            shift = (RwInt32)(deltaPreLightColors[m].alpha * thisValue -
                                                                        deltaPreLightColors[m].alpha * lastValue);
                                            color[k].alpha += (RwUInt8)shift;
                                            k++;
                                            m++;
                                        }
                                    }
                                    else
                                    {
                                        k += maxl;
                                    }
                                }
                            }
                        }
                    }
                }

                if (reinstance)
                {
                    const RwUInt32  stride = instancedHeader->stride;

                    for (l = 0; l < currentBlock; l++)
                    {
                        instancedHeader->vertexAlpha |=
                            _rpXboxVtxFmtInstColor(&dstPreLightColors[stride * blocks[l].firstVertex],
                                                   &color[blocks[l].firstVertex],
                                                   blocks[l].numVertex, stride);
                    }
                }
                else
                {
                    instancedHeader->vertexAlpha =
                        _rpXboxVtxFmtInstColor(dstPreLightColors, color, numVertices,
                                               instancedHeader->stride);
                }
            }

            if (dmorphLockedSinceLastInst & rpGEOMETRYLOCKTEXCOORDS1)
            {
                currentBlock = 0;

                for (i = 0; i < geometryData->numDMorphTargets; i++)
                {
                    if (atomicData->values[i] != geometryData->currValues[i])
                    {
                        dMorphTarget = &geometryData->dMorphTargets[i];

                        if (dMorphTarget->flags & rpGEOMETRYTEXTURED)
                        {
                            RwUInt32                k;
                            RwUInt32                m;

                            scale = atomicData->values[i] - geometryData->currValues[i];
                            rle = &dMorphTarget->rle;
                            deltaTexCoords = dMorphTarget->texCoords;

                            for (j = 0, k = 0, m = 0; j < rle->numCodeElements; j++)
                            {
                                RwUInt32    maxl = rle->code[j] & 0x7F;

                                if (maxl)
                                {
                                    if (rle->code[j] & 0x80)
                                    {
                                        if (reinstance)
                                        {
                                            currentBlock = XboxDMorphAddBlock(currentBlock, blocks, k, maxl);
                                        }

                                        for (l = 0; l < maxl; l++)
                                        {
                                            texCoordSets[0][k].u += deltaTexCoords[m].u * scale;
                                            texCoordSets[0][k].v += deltaTexCoords[m].v * scale;
                                            k++;
                                            m++;
                                        }
                                    }
                                    else
                                    {
                                        k += maxl;
                                    }
                                }
                            }
                        }
                    }
                }

                if (reinstance)
                {
                    const RwUInt32  stride = instancedHeader->stride;

                    for (l = 0; l < currentBlock; l++)
                    {
                        _rpXboxVtxFmtInstV2d((RpXboxCompType)(fmt->texCoord & 0xF),
                                             &dstTexCoords[stride * blocks[l].firstVertex],
                                             &texCoordSets[0][blocks[l].firstVertex],
                                             blocks[l].numVertex, stride);
                    }
                }
                else
                {
                    _rpXboxVtxFmtInstV2d((RpXboxCompType)(fmt->texCoord & 0xF), dstTexCoords,
                                         texCoordSets[0], numVertices, instancedHeader->stride);
                }
            }

            for (i = 0; i < geometryData->numDMorphTargets; i++)
            {
                geometryData->currValues[i] = atomicData->values[i];
            }

            RwFree(blocks);
        }

        D3DVertexBuffer_Unlock((D3DVertexBuffer *)instancedHeader->vertexBuffer);
        if (lockedVertexBufferStatic)
        {
            D3DVertexBuffer_Unlock((D3DVertexBuffer *)geometryData->platformData.vertexBuffer);
        }
    }

    return TRUE;
}

// match: __rpDMorphPipelinesCreate @ 0x002F4230
RwBool
_rpDMorphPipelinesCreate(RwUInt32 type __RWUNUSED__)
{
    RxPipeline      *pipeline;
    RxLockedPipe    *lpipe;

    pipeline = RxPipelineCreate();
    pipeline->pluginId = rwID_DMORPHPLUGIN;
    pipeline->pluginData = rpDMORPHTYPEGENERIC;

    lpipe = RxPipelineLock(pipeline);
    lpipe = RxLockedPipeAddFragment(lpipe, NULL, &nodeXboxDmorphAtomicAllInOneCSL, NULL);
    RxLockedPipeUnlock(lpipe);

    RxPipelineFindNodeByName(pipeline, nodeXboxDmorphAtomicAllInOneCSL.name, NULL, NULL);

    _rwDMorphPipelines[rpDMORPHTYPEGENERIC] = pipeline;

    return TRUE;
}

// match: __rpDMorphPipelinesDestroy @ 0x002F4290
RwBool
_rpDMorphPipelinesDestroy(void)
{
    if (_rwDMorphPipelines[rpDMORPHTYPEGENERIC])
    {
        RxPipelineDestroy(_rwDMorphPipelines[rpDMORPHTYPEGENERIC]);
        _rwDMorphPipelines[rpDMORPHTYPEGENERIC] = NULL;
    }

    return TRUE;
}

// match: __rpDMorphPipelinesAttach @ 0x002F42C0
RpAtomic *
_rpDMorphPipelinesAttach(RpAtomic *atomic, RpDMorphType type)
{
    return RpAtomicSetPipeline(atomic, _rwDMorphPipelines[type]);
}
