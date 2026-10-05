/*
 * codfh-match: RenderWare 3.6's Xbox skin all-in-one node, rebuilt from
 * the image; the file name is the image's RCS id string's, names and shapes
 * the Godfather debug build's copy (3.7 there adds the split-data asserts,
 * a viewport restore and the per-node callback getters and setters).
 */

#include <xtl.h>

#include <rwcore.h>
#include <rpworld.h>

#include "skin.h"

#include "xbcache.h"

#include "skinxbox.h"

/* An all-in-one skin node's private data. */
typedef struct _rxXboxSkinInstanceNodeData _rxXboxSkinInstanceNodeData;
struct _rxXboxSkinInstanceNodeData
{
    RxXboxAllInOneInstanceCallBack      instanceCallback;
    _rxXboxAllInOneReinstanceCallBack   reinstanceCallback;
    RwV4d                            *(*enumerateLightsCallback)(RwV4d *shaderConstants,
                                                                 RwInt32 *dirLightCount,
                                                                 RwInt32 *pointLightCount,
                                                                 RpAtomic *atomic);
    _rxXboxSkinAllInOneRenderCallBack   renderCallback;
};

// match: _XBoxSkinAtomicAllInOneNode @ 0x002D46F0
static RwBool
XBoxSkinAtomicAllInOneNode(RxPipelineNode *self, const RxPipelineNodeParam *params)
{
    _rxXboxSkinInstanceNodeData *privateData;
    RpAtomic                    *atomic;
    RpGeometry                  *geometry;
    RwResEntry                  *resEntry;
    RwUInt32                    geomFlags;

    atomic = (RpAtomic *)RxPipelineNodeParamGetData(params);

    geometry = RpAtomicGetGeometry(atomic);

    geomFlags = RpGeometryGetFlags(geometry);

    privateData = (_rxXboxSkinInstanceNodeData *)self->privateData;

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

    RwXboxLightsEnable(0, FALSE);

    if (privateData->renderCallback)
    {
        RxXboxResEntryHeader    *resEntryHeader;
        RxXboxInstanceData      *mesh;
        DWORD                   oldShader;
        RWALIGN(D3DVECTOR4 viewportScale, 16);
        RwV4d                   *shaderConstants;
        RwInt32                 dirLightCount;
        RwInt32                 pointLightCount;
        RpSkin                  *skin;
        const RwUInt8           *meshBatches;
        const RwUInt8           *boneBatches;
        RwUInt32                baseConstant;
        RwUInt32                numConstants;

        resEntryHeader = (RxXboxResEntryHeader *)(resEntry + 1);

        oldShader = RwXboxGetCurrentVertexShader();

        _rpSkinXboxPurgeShaderCache();

        _rpSkinXboxTo192Constants();

        D3DDevice_GetViewportOffsetAndScale((D3DVECTOR4 *)&_rpSkinXboxPerAtomicConstants[0],
                                            &viewportScale);

        _rpSkinXboxComputeProjViewWorld(&_rpSkinXboxCachedWorldMatrix,
                                        &_rpSkinXboxCachedViewMatrix,
                                        (D3DMATRIX *)&_rpSkinXboxPerAtomicConstants[1],
                                        atomic, &viewportScale);

        shaderConstants = &_rpSkinXboxPerAtomicConstants[5];
        if (privateData->enumerateLightsCallback)
        {
            shaderConstants = privateData->enumerateLightsCallback(shaderConstants,
                                                                   &dirLightCount,
                                                                   &pointLightCount,
                                                                   atomic);
        }

        skin = RpSkinGeometryGetSkin(RpAtomicGetGeometry(atomic));

        _rpSkinXboxMatrixUpdate(shaderConstants, atomic, skin);

        baseConstant = ((RwUInt32)shaderConstants - (RwUInt32)_rpSkinXboxPerAtomicConstants) /
                       sizeof(RwV4d);

        numConstants = baseConstant;

        meshBatches = skin->skinSplitData.meshRLECount;
        boneBatches = skin->skinSplitData.meshRLE;
        if (!meshBatches)
        {
            numConstants = baseConstant + 3 * skin->platformData.numBonesUsed;
        }

        D3DDevice_SetVertexShaderConstantFast(-96, _rpSkinXboxPerAtomicConstants, numConstants);

        D3DDevice_SetStreamSource(0, (D3DVertexBuffer *)resEntryHeader->vertexBuffer,
                                  resEntryHeader->stride);
        D3DDevice_SetStreamSource(1, (D3DVertexBuffer *)skin->platformData.weightsNindicesVB,
                                  skin->platformData.weightsNindicesVBStride);

        for (mesh = resEntryHeader->begin; mesh != resEntryHeader->end; mesh++)
        {
            if (meshBatches)
            {
                RwUInt32    rleStart = meshBatches[0];
                RwUInt32    rleCount = meshBatches[1];

                meshBatches += 2;

                if (rleCount > 0)
                {
                    const RwUInt8   *rle = boneBatches + 2 * rleStart;
                    RwUInt32        batchesLeft = rleCount;

                    do
                    {
                        RwUInt32    bone = rle[0];
                        RwUInt32    numBones = rle[1];

                        do
                        {
                            D3DDevice_SetVertexShaderConstantFast(
                                baseConstant + 3 * skin->skinSplitData.matrixRemapIndices[bone] - 96,
                                &_rpSkinXboxPerAtomicConstants[baseConstant +
                                    3 * skin->platformData.vertexIndexMap[bone]],
                                3);

                            bone++;
                        }
                        while (--numBones);

                        rle += 2;
                    }
                    while (--batchesLeft);
                }
            }

            _rpSkinXboxSetMaterialColor(mesh->material, geomFlags & rpGEOMETRYMODULATEMATERIALCOLOR);

            if (resEntryHeader->vertexAlpha || mesh->material->color.alpha != 0xFF)
            {
                RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)TRUE);
            }
            else
            {
                RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)FALSE);
            }

            privateData->renderCallback(resEntryHeader, mesh, atomic, geomFlags,
                                        skin->platformData.maxWeightsUsed,
                                        dirLightCount, pointLightCount);
        }

        _rpSkinXboxTo96Constants();

        D3DDevice_SetVertexShader(oldShader);

        D3DDevice_SetStreamSource(1, NULL, 0);
    }

    return TRUE;
}

// match: _XBoxSkinAtomicAllInOnePipelineInit @ 0x002D4AD0
RwBool
XBoxSkinAtomicAllInOnePipelineInit(RxPipelineNode *node)
{
    _rxXboxSkinInstanceNodeData *instanceData = (_rxXboxSkinInstanceNodeData *)node->privateData;

    instanceData->instanceCallback = _rpSkinXboxInstanceCallback;
    instanceData->reinstanceCallback = _rpSkinXboxReInstanceCallback;
    instanceData->enumerateLightsCallback = _rpSkinXboxEnumerateLights;
    instanceData->renderCallback = NULL;

    return TRUE;
}

// match: _RxNodeDefinitionGetXboxSkinAtomicAllInOne @ 0x002D4B00
RxNodeDefinition *
RxNodeDefinitionGetXboxSkinAtomicAllInOne(void)
{
    static RxNodeDefinition nodeXboxSkinAtomicAllInOneCSL =
    {
        "XboxSkinAtomicAllInOne.csl",
        {
            XBoxSkinAtomicAllInOneNode,
            (RxNodeInitFn)NULL,
            (RxNodeTermFn)NULL,
            XBoxSkinAtomicAllInOnePipelineInit,
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
        (RwUInt32)sizeof(_rxXboxSkinInstanceNodeData),
        (RxNodeDefEditable)FALSE,
        0
    };

    return &nodeXboxSkinAtomicAllInOneCSL;
}

// match: __rxXboxSkinAllInOneSetRenderCallBack @ 0x002D4B10
void
_rxXboxSkinAllInOneSetRenderCallBack(RxPipelineNode *node,
                                     _rxXboxSkinAllInOneRenderCallBack callback)
{
    _rxXboxSkinInstanceNodeData *instanceData = (_rxXboxSkinInstanceNodeData *)node->privateData;

    instanceData->renderCallback = callback;
}
