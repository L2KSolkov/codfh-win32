/*
 * codfh-match: RenderWare 3.6's Xbox world sector all-in-one node, rebuilt
 * from the image; the file name is the image's RCS id string's, names and
 * shapes the Godfather debug build's copy.
 */

#include <xtl.h>

#include <rwcore.h>
#include "bamateri.h"
#include "baworld.h"
#include "basector.h"

#include "xbcache.h"

#include "xbpipe.h"
#include "xbvtxfmt.h"
#include "xblights.h"
#include "nodeXBoxWorldSectorAllInOne.h"

/* RenderWare 3.6's RCS id string, which the image keeps (the 3.7.2 tree has none) */
static const char rcsid[] = "@@@@(#)$Id: //RenderWare/RW36Active/rwsdk/world/pipe/p2/xbox/nodeXBoxWorldSectorAllInOne.c#1 $";

static const D3DMATRIX matrix =
{
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
};

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: _rcsid @ 0x00419750
// match: ??_C@_0BM@FDEEOJN@XboxWorldSectorAllInOne?4csl?$AA@ @ 0x00419730
// match: _matrix @ 0x004197B0
// match: ?nodeXboxWorldSectorAllInOneCSL@?1??RxNodeDefinitionGetXboxWorldSectorAllInOne@@9@9 @ 0x00436D08

// match: __rwXbWorldSectorDefaultLightingCallback @ 0x002E1C40
// sp-match: __rwXbWorldSectorDefaultLightingCallback @ 0x001FC710

void
_rwXbWorldSectorDefaultLightingCallback(void *object)
{
    const RwUInt32  flags = RpWorldGetFlags((const RpWorld *)RWSRCGLOBAL(curWorld));

    if (flags & rxGEOMETRY_LIGHT)
    {
        RwUInt32    numLights;
        RwBool      lighting;

        numLights = 0;

        lighting = _rwXBLightsGlobalEnable(&numLights, 2, (flags & rxGEOMETRY_NORMALS) != 0);

        if (flags & rxGEOMETRY_NORMALS)
        {
            RwLLLink    *curLight;

            RWSRCGLOBAL(lightFrame)++;

            for (curLight = rwLinkListGetFirstLLLink(&((RpWorldSector *)object)->lightsInWorldSector);
                 curLight != rwLinkListGetTerminator(&((RpWorldSector *)object)->lightsInWorldSector);
                 curLight = rwLLLinkGetNext(curLight))
            {
                RpLightTie  *lightTie = rwLLLinkGetData(curLight, RpLightTie, lightInWorldSector);

                if (lightTie->light && (rwObjectTestFlags(lightTie->light, rpLIGHTLIGHTWORLD)))
                {
                    lighting |= _rxXBLightLocalEnable(lightTie->light, &numLights);
                }
            }
        }

        RwXboxLightsEnable(numLights, lighting);
    }
    else
    {
        RwXboxLightsEnable(0, FALSE);
    }
}

// match: __rxXBWorldSectorDefaultInstanceCallback @ 0x002E1CE0
// sp-match: __rxXBWorldSectorDefaultInstanceCallback @ 0x001FC7B0
RwBool
_rxXBWorldSectorDefaultInstanceCallback(void *object,
                                        RxXboxResEntryHeader *instancedHeader,
                                        RwBool reinstance __RWUNUSED__)
{
    RpWorldSector       *sector = (RpWorldSector *)object;
    RwUInt32            flags = RpWorldGetFlags((RpWorld *)RWSRCGLOBAL(curWorld));
    const RwTexCoords   **texCoordSets;
    RwInt32             numTexCoordSets;
    const RwRGBA        *color;
    const RpVertexNormal *packedNormals;

    if ((flags & rxGEOMETRY_TEXTURED) || (flags & rpWORLDTEXTURED2))
    {
        texCoordSets = (const RwTexCoords **)sector->texCoords;
    }
    else
    {
        texCoordSets = NULL;
    }

    if ((flags & rxGEOMETRY_TEXTURED) || (flags & rpWORLDTEXTURED2))
    {
        numTexCoordSets = ((RpWorld *)RWSRCGLOBAL(curWorld))->numTexCoordSets;
    }
    else
    {
        numTexCoordSets = 0;
    }

    if (flags & rxGEOMETRY_PRELIT)
    {
        color = sector->preLitLum;
    }
    else
    {
        color = NULL;
    }

    if (flags & rxGEOMETRY_NORMALS)
    {
        packedNormals = sector->normals;
    }
    else
    {
        packedNormals = NULL;
    }

    return _rpXboxDefaultInstance(RpXboxWorldGetVtxFmt((RpWorld *)RWSRCGLOBAL(curWorld)), flags, instancedHeader,
                                  sector->vertices, NULL, packedNormals, color,
                                  numTexCoordSets, texCoordSets, 0xFFF);
}

// match: _XBWorldSectorAllInOneNode @ 0x002E1D60
// sp-match: _XBWorldSectorAllInOneNode @ 0x001FC830
static RwBool
XBWorldSectorAllInOneNode(RxPipelineNode *self, const RxPipelineNodeParam *params)
{
    _rxXboxInstanceNodeData *privateData;
    RpWorldSector           *sector;
    RwResEntry              *repEntry;
    RwUInt32                worldFlags;

    sector = (RpWorldSector *)RxPipelineNodeParamGetData(params);

    privateData = (_rxXboxInstanceNodeData *)self->privateData;

    worldFlags = RpWorldGetFlags((const RpWorld *)RWSRCGLOBAL(curWorld));

    repEntry = sector->repEntry;

    if (!(rpWORLDNATIVE & worldFlags))
    {
        RpMeshHeader    *meshHeader;
        RwInt16         numMeshes;

        if (sector->numVertices <= 0)
        {
            return TRUE;
        }

        meshHeader = sector->mesh;
        numMeshes = meshHeader->numMeshes;
        if (numMeshes <= 0)
        {
            return TRUE;
        }

        if (repEntry)
        {
            if (((RxXboxResEntryHeader *)(repEntry + 1))->serialNumber != meshHeader->serialNum)
            {
                RwResourcesFreeResEntry(repEntry);
                repEntry = NULL;
            }
        }

        if (repEntry)
        {
            RwResourcesUseResEntry(repEntry);
        }
        else
        {
            repEntry = _rxXBInstance(sector, sector, &sector->repEntry, meshHeader,
                                     sector->numVertices, privateData->instanceCallback,
                                     (worldFlags & rpWORLDNATIVEINSTANCE) != 0);
            if (!repEntry)
            {
                return FALSE;
            }
        }
    }

    if (privateData->lightingCallback)
    {
        privateData->lightingCallback(sector);
    }

    D3DDevice_SetTransform(D3DTS_WORLD, &matrix);

    _rwXbRenderStateForce(D3DRS_NORMALIZENORMALS, FALSE);

    if (privateData->renderCallback)
    {
        privateData->renderCallback((RxXboxResEntryHeader *)(repEntry + 1), sector,
                                    rwSECTORATOMIC, worldFlags);
    }

    return TRUE;
}

// match: __rxXBWorldSectorAllInOnePipelineInit @ 0x002E1EB0
// sp-match: __rxXBWorldSectorAllInOnePipelineInit @ 0x001FC980
RwBool
_rxXBWorldSectorAllInOnePipelineInit(RxPipelineNode *node)
{
    _rxXboxInstanceNodeData *instanceData = (_rxXboxInstanceNodeData *)node->privateData;

    instanceData->instanceCallback = _rxXBWorldSectorDefaultInstanceCallback;
    instanceData->reinstanceCallback = NULL;
    instanceData->lightingCallback = _rwXbWorldSectorDefaultLightingCallback;
    instanceData->renderCallback = _rxXbDefaultRenderCallback;

    return TRUE;
}

// match: _RxNodeDefinitionGetXboxWorldSectorAllInOne @ 0x002E1EE0
// sp-match: _RxNodeDefinitionGetXboxWorldSectorAllInOne @ 0x001FC9B0
RxNodeDefinition *
RxNodeDefinitionGetXboxWorldSectorAllInOne(void)
{
    static RxNodeDefinition nodeXboxWorldSectorAllInOneCSL =
    {
        "XboxWorldSectorAllInOne.csl",
        {
            XBWorldSectorAllInOneNode,
            (RxNodeInitFn)NULL,
            (RxNodeTermFn)NULL,
            _rxXBWorldSectorAllInOnePipelineInit,
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

    return &nodeXboxWorldSectorAllInOneCSL;
}
