/*
 * codfh-match: RenderWare 3.6's Xbox atomic all-in-one node, rebuilt from
 * the image; the file name is the image's RCS id string's, names and shapes
 * the Godfather debug build's copy (3.7 there: 3.6 never unlocks the
 * morphed vertex buffer).
 */

#include <xtl.h>

#include <rwcore.h>
#include "bamateri.h"
#include "baworld.h"
#include "bageomet.h"
#include "baclump.h"

#include "xbcache.h"
#include "xbmemory.h"

#include "xbpipe.h"
#include "xbvtxfmt.h"
#include "xblights.h"
#include "nodeXBoxAtomicAllInOne.h"

// match: __rwXbAtomicDefaultLightingCallback @ 0x002E1EF0
void
_rwXbAtomicDefaultLightingCallback(void *object)
{
    RpAtomic        *atomic = (RpAtomic *)object;
    RpGeometryFlag  flags = (RpGeometryFlag)RpGeometryGetFlags(RpAtomicGetGeometry(atomic));

    if ((flags & rxGEOMETRY_LIGHT) && (NULL != RWSRCGLOBAL(curWorld)))
    {
        RwUInt32    numLights;
        RwBool      lighting;

        numLights = 0;

        lighting = _rwXBLightsGlobalEnable(&numLights, 1, (flags & rxGEOMETRY_NORMALS) != 0);

        if (flags & rxGEOMETRY_NORMALS)
        {
            RwLLLink    *cur, *end;

            RWSRCGLOBAL(lightFrame)++;

            cur = rwLinkListGetFirstLLLink(&atomic->llWorldSectorsInAtomic);
            end = rwLinkListGetTerminator(&atomic->llWorldSectorsInAtomic);
            while (cur != end)
            {
                RpTie       *tpTie = rwLLLinkGetData(cur, RpTie, lWorldSectorInAtomic);
                RwLLLink    *curLight, *endLight;

                curLight = rwLinkListGetFirstLLLink(&tpTie->worldSector->lightsInWorldSector);
                endLight = rwLinkListGetTerminator(&tpTie->worldSector->lightsInWorldSector);
                while (curLight != endLight)
                {
                    RpLightTie  *lightTie = rwLLLinkGetData(curLight, RpLightTie, lightInWorldSector);
                    RpLight     *theLight = lightTie->light;

                    if (theLight && (theLight->lightFrame != RWSRCGLOBAL(lightFrame)) &&
                        (rwObjectTestFlags(theLight, rpLIGHTLIGHTATOMICS)))
                    {
                        const RwV3d     *pos;
                        const RwSphere  *sphere;
                        RwV3d           distanceVector;
                        RwReal          distanceSquare;
                        RwReal          distanceCollision;

                        theLight->lightFrame = RWSRCGLOBAL(lightFrame);

                        pos = &(RwFrameGetLTM(RpLightGetFrame(theLight))->pos);
                        sphere = RpAtomicGetWorldBoundingSphere(atomic);

                        RwV3dSub(&distanceVector, &sphere->center, pos);

                        distanceSquare = RwV3dDotProduct(&distanceVector, &distanceVector);

                        distanceCollision = sphere->radius + RpLightGetRadius(theLight);

                        if (distanceSquare < distanceCollision * distanceCollision)
                        {
                            lighting |= _rxXBLightLocalEnable(theLight, &numLights);
                        }
                    }

                    curLight = rwLLLinkGetNext(curLight);
                }

                cur = rwLLLinkGetNext(cur);
            }
        }

        RwXboxLightsEnable(numLights, lighting);
    }
    else
    {
        RwXboxLightsEnable(0, FALSE);
    }
}

// match: _rwXBInstanceDataMorphUpdate @ 0x002E2080
static void
rwXBInstanceDataMorphUpdate(RpGeometry *geometry,
                            RxXboxResEntryHeader *instancedHeader,
                            const RpInterpolator *interp)
{
    RpXboxVtxFmt        *format;
    RwInt32             startMT, endMT;
    RwUInt32            vbSize;
    D3DVertexBuffer     *vertexBuffer;
    RwUInt8             *vertexData;
    RwUInt32            lockedSinceLastInst;
    RwReal              scale;
    RwInt32             numVertices;
    RwUInt32            offset;

    format = RpXboxGeometryGetVtxFmt(geometry);

    startMT = interp->startMorphTarget;
    endMT = interp->endMorphTarget;
    if (startMT >= geometry->numMorphTargets || endMT >= geometry->numMorphTargets)
    {
        endMT = 0;
        startMT = 0;
    }

    vbSize = instancedHeader->stride * geometry->numVertices;

    vertexBuffer = (D3DVertexBuffer *)instancedHeader->vertexBuffer;
    if (vertexBuffer->Lock && D3DDevice_IsFencePending(vertexBuffer->Lock))
    {
        vertexData = RwXbVertexBufferLockDiscard(vertexBuffer, vbSize);
        lockedSinceLastInst = 0xFFF;
    }
    else
    {
        D3DVertexBuffer_Lock(vertexBuffer, 0, vbSize, &vertexData, 0);
        lockedSinceLastInst = geometry->lockedSinceLastInst;
    }

    scale = interp->position * interp->recipTime;

    if (startMT != endMT && scale != 0.0f)
    {
        const RwV3d *vertex1 = geometry->morphTarget[startMT].verts;
        const RwV3d *vertex2 = geometry->morphTarget[endMT].verts;

        numVertices = geometry->numVertices;

        offset = _rpXboxVtxFmtInstV3dMorph((RpXboxCompType)format->pos, vertexData,
                                           vertex1, vertex2, scale,
                                           numVertices, instancedHeader->stride);

        if (geometry->flags & rxGEOMETRY_NORMALS)
        {
            _rpXboxVtxFmtInstV3dMorph((RpXboxCompType)format->norm, vertexData + offset,
                                      geometry->morphTarget[startMT].normals,
                                      geometry->morphTarget[endMT].normals, scale,
                                      numVertices, instancedHeader->stride);
        }
    }
    else
    {
        const RpMorphTarget *morphTarget = &geometry->morphTarget[startMT];

        numVertices = geometry->numVertices;

        offset = _rpXboxVtxFmtInstV3d((RpXboxCompType)format->pos, vertexData,
                                      morphTarget->verts, numVertices,
                                      instancedHeader->stride);

        if (geometry->flags & rxGEOMETRY_NORMALS)
        {
            _rpXboxVtxFmtInstV3d((RpXboxCompType)format->norm, vertexData + offset,
                                 morphTarget->normals, numVertices,
                                 instancedHeader->stride);
        }
    }

    if (lockedSinceLastInst)
    {
        numVertices = geometry->numVertices;

        offset = _rpXboxVtxFmtGetSize((RpXboxCompType)format->pos, 3);

        if (geometry->flags & rxGEOMETRY_NORMALS)
        {
            offset += _rpXboxVtxFmtGetSize((RpXboxCompType)format->norm, 3);
        }

        if (geometry->flags & rxGEOMETRY_PRELIT)
        {
            if (lockedSinceLastInst & rpGEOMETRYLOCKPRELIGHT)
            {
                instancedHeader->vertexAlpha =
                    _rpXboxVtxFmtInstColor(vertexData + offset, geometry->preLitLum,
                                           numVertices, instancedHeader->stride);
            }

            offset += sizeof(RwUInt32);
        }

        if ((geometry->flags & (rxGEOMETRY_TEXTURED | rpGEOMETRYTEXTURED2)) &&
            (lockedSinceLastInst & rpGEOMETRYLOCKTEXCOORDSALL))
        {
            RwTexCoords **texCoordSets = geometry->texCoords;
            RwInt32     numTexCoordSets = geometry->numTexCoordSets;
            RwInt32     i;

            for (i = 0; i < numTexCoordSets; i++)
            {
                RpXboxCompType  type = (RpXboxCompType)((format->texCoord >> (4 * i)) & 0xF);

                offset += _rpXboxVtxFmtInstV2d(type, vertexData + offset,
                                               texCoordSets[i], numVertices,
                                               instancedHeader->stride);
            }
        }
    }
}

// match: __rxXBAtomicDefaultInstanceCallback @ 0x002E22F0
RwBool
_rxXBAtomicDefaultInstanceCallback(void *object,
                                   RxXboxResEntryHeader *instancedHeader,
                                   RwBool reinstance)
{
    RpGeometry          *geometry = RpAtomicGetGeometry((RpAtomic *)object);
    RpGeometryFlag      flags = (RpGeometryFlag)RpGeometryGetFlags(geometry);
    RwUInt32            lockedSinceLastInst;
    const RwTexCoords   **texCoordSets;
    RwInt32             numTexCoordSets;
    const RwRGBA        *color;
    const RwV3d         *normals;

    if (reinstance)
    {
        lockedSinceLastInst = geometry->lockedSinceLastInst;
    }
    else
    {
        lockedSinceLastInst = 0xFFF;
    }

    if ((flags & rxGEOMETRY_TEXTURED) || (flags & rpGEOMETRYTEXTURED2))
    {
        texCoordSets = (const RwTexCoords **)geometry->texCoords;
    }
    else
    {
        texCoordSets = NULL;
    }

    if ((flags & rxGEOMETRY_TEXTURED) || (flags & rpGEOMETRYTEXTURED2))
    {
        numTexCoordSets = geometry->numTexCoordSets;
    }
    else
    {
        numTexCoordSets = 0;
    }

    if (flags & rxGEOMETRY_PRELIT)
    {
        color = geometry->preLitLum;
    }
    else
    {
        color = NULL;
    }

    if (flags & rxGEOMETRY_NORMALS)
    {
        normals = geometry->morphTarget->normals;
    }
    else
    {
        normals = NULL;
    }

    return _rpXboxDefaultInstance(RpXboxGeometryGetVtxFmt(geometry), flags, instancedHeader,
                                  geometry->morphTarget->verts, normals, NULL, color,
                                  numTexCoordSets, texCoordSets, lockedSinceLastInst);
}

// match: __rxXBAtomicDefaultReinstanceCallback @ 0x002E2380
RwBool
_rxXBAtomicDefaultReinstanceCallback(void *object,
                                     RxXboxResEntryHeader *instancedHeader)
{
    RpAtomic    *atomic = (RpAtomic *)object;
    RpGeometry  *geometry = RpAtomicGetGeometry(atomic);

    if (RpGeometryGetNumMorphTargets(geometry) != 1)
    {
        if ((atomic->interpolator.flags & rpINTERPOLATORDIRTYINSTANCE) ||
            geometry->lockedSinceLastInst)
        {
            rwXBInstanceDataMorphUpdate(geometry, instancedHeader, &atomic->interpolator);
        }
    }
    else if (geometry->lockedSinceLastInst)
    {
        if (!_rxXBAtomicDefaultInstanceCallback(object, instancedHeader, TRUE))
        {
            return FALSE;
        }
    }

    return TRUE;
}

// match: _XBAtomicAllInOneNode @ 0x002E23E0
static RwBool
XBAtomicAllInOneNode(RxPipelineNode *self, const RxPipelineNodeParam *params)
{
    _rxXboxInstanceNodeData *privateData;
    RpAtomic                *atomic;
    RpGeometry              *geometry;
    RwResEntry              *resEntry;
    RwUInt32                geomFlags;
    const RwMatrix          *atomicLTM;
    D3DMATRIX               matrix;
    RwBool                  normalizeNormals;

    atomic = (RpAtomic *)RxPipelineNodeParamGetData(params);

    geometry = RpAtomicGetGeometry(atomic);

    geomFlags = RpGeometryGetFlags(geometry);

    privateData = (_rxXboxInstanceNodeData *)self->privateData;

    if (!(rpGEOMETRYNATIVE & geomFlags))
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
            if (geometry->lockedSinceLastInst || RpGeometryGetNumMorphTargets(geometry) != 1)
            {
                if (privateData->reinstanceCallback)
                {
                    privateData->reinstanceCallback(atomic, (RxXboxResEntryHeader *)(resEntry + 1));
                }

                atomic->interpolator.flags &= ~rpINTERPOLATORDIRTYINSTANCE;
                geometry->lockedSinceLastInst = 0;
            }

            RwResourcesUseResEntry(resEntry);
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

            resEntry = _rxXBInstance(atomic, owner, resEntryPointer, meshHeader,
                                     geometry->numVertices, privateData->instanceCallback,
                                     nativeInstanceRequest);
            if (!resEntry)
            {
                return FALSE;
            }

            geometry->lockedSinceLastInst = 0;

            if (RpGeometryGetNumMorphTargets(geometry) != 1)
            {
                if (privateData->reinstanceCallback)
                {
                    privateData->reinstanceCallback(atomic, (RxXboxResEntryHeader *)(resEntry + 1));
                }
            }
        }
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

    normalizeNormals = FALSE;

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

    if ((geomFlags & rxGEOMETRY_NORMALS) &&
        !rwMatrixTestFlags(atomicLTM, (rwMATRIXTYPENORMAL | rwMATRIXINTERNALIDENTITY)))
    {
        const RwV3d *row[3];
        RwUInt32    i;

        row[0] = &atomicLTM->right;
        row[1] = &atomicLTM->up;
        row[2] = &atomicLTM->at;

        for (i = 0; i < 3; i++)
        {
            const RwReal    length = RwV3dDotProduct(row[i], row[i]);

            if (length > 1.05f || length < 0.95f)
            {
                normalizeNormals = TRUE;
                break;
            }
        }
    }

    _rwXbRenderStateForce(D3DRS_NORMALIZENORMALS, normalizeNormals);

    if (privateData->renderCallback)
    {
        privateData->renderCallback((RxXboxResEntryHeader *)(resEntry + 1), atomic,
                                    rpATOMIC, geomFlags);
    }

    return TRUE;
}

// match: __rxXBAtomicAllInOnePipelineInit @ 0x002E26E0
RwBool
_rxXBAtomicAllInOnePipelineInit(RxPipelineNode *node)
{
    _rxXboxInstanceNodeData *instanceData = (_rxXboxInstanceNodeData *)node->privateData;

    instanceData->instanceCallback = _rxXBAtomicDefaultInstanceCallback;
    instanceData->reinstanceCallback = _rxXBAtomicDefaultReinstanceCallback;
    instanceData->lightingCallback = _rwXbAtomicDefaultLightingCallback;
    instanceData->renderCallback = _rxXbDefaultRenderCallback;

    return TRUE;
}

// match: _RxNodeDefinitionGetXboxAtomicAllInOne @ 0x002E2710
RxNodeDefinition *
RxNodeDefinitionGetXboxAtomicAllInOne(void)
{
    static RxNodeDefinition nodeXboxAtomicAllInOneCSL =
    {
        "XboxAtomicAllInOne.csl",
        {
            XBAtomicAllInOneNode,
            (RxNodeInitFn)NULL,
            (RxNodeTermFn)NULL,
            _rxXBAtomicAllInOnePipelineInit,
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

    return &nodeXboxAtomicAllInOneCSL;
}
