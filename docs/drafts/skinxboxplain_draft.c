/*
 * codfh-match: RenderWare 3.6's Xbox plain skin pipeline, rebuilt from the
 * image; the file name is the image's RCS id string's, names and shapes
 * the Godfather debug build's copy (its skinxboxplain.h and
 * skinxboxrender.h keep the material set-up and render callback).
 */

#include <xtl.h>

#include <rwcore.h>
#include <rpworld.h>

#include "skin.h"

#include "xbcache.h"
#include "xbrendst.h"

#include "skinxbox.h"

// match: __rpSkinXboxPlainMaterialSetUp @ 0x002D4020
RwInt32
_rpSkinXboxPlainMaterialSetUp(const RpAtomic *atomic __RWUNUSED__,
                              const RxXboxInstanceData *mesh __RWUNUSED__,
                              const RpMaterial *material,
                              RwUInt32 pass __RWUNUSED__)
{
    RwXboxSetCurrentPixelShader(0);

    if (material->texture)
    {
        RwXboxSetCachedTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
        RwXboxSetCachedTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
        RwXboxSetCachedTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TEXTURE);
        RwXboxSetCachedTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
        RwXboxSetCachedTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
        RwXboxSetCachedTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);

        RwXboxRenderStateSetTexture(material->texture, 0);
    }
    else
    {
        RwXboxSetCachedTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
        RwXboxSetCachedTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
        RwXboxSetCachedTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
        RwXboxSetCachedTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);

        RwXboxRenderStateSetTexture(NULL, 0);
    }

    return 0;
}

// match: __rpSkinXboxRenderCallback @ 0x002D4220
static void
_rpSkinXboxRenderCallback(RxXboxResEntryHeader *resEntryHeader,
                          RxXboxInstanceData *mesh,
                          RpAtomic *atomic,
                          RwUInt32 flags,
                          RwUInt32 maxWeightsUsed,
                          RwUInt32 dirLightCount,
                          RwUInt32 pointLightCount)
{
    RwUInt32    pass = 1;
    RwInt32     passesLeft;

    do
    {
        _rpSkinXboxShaderDesc   desc;
        const DWORD             *shader;

        desc.numWeights = (RwUInt8)maxWeightsUsed;
        desc.numDirect = (RwUInt8)dirLightCount;
        desc.numPoint = (RwUInt8)pointLightCount;
        desc.matfx = 0;
        desc.bnt = 0;
        desc.prelit = (flags >> 3);

        shader = _rpSkinXboxGetShader(&desc);

        _rpSkinXboxSetShader(mesh->vertexShader, shader);

        passesLeft = _rpSkinXboxPlainMaterialSetUp(atomic, mesh, mesh->material, pass++);

        RwXboxDrawIndexedVertices((D3DPRIMITIVETYPE)resEntryHeader->primType,
                                  mesh->numIndices, mesh->indexBuffer);
    }
    while (passesLeft > 0);
}

// match: __rpSkinXboxCreatePlainPipe @ 0x002D42A0
RxPipeline *
_rpSkinXboxCreatePlainPipe(void)
{
    RxPipeline      *pipeline;
    RxPipelineNode  *node;

    if (!_rpSkinXboxInitShaders())
    {
        return NULL;
    }

    pipeline = _rpSkinXboxCreateAtomicPipeline();

    node = RxPipelineFindNodeByName(pipeline,
                                    RxNodeDefinitionGetXboxSkinAtomicAllInOne()->name,
                                    NULL, NULL);

    _rxXboxSkinAllInOneSetRenderCallBack(node, _rpSkinXboxRenderCallback);

    pipeline->pluginId = rwID_SKINPLUGIN;
    pipeline->pluginData = rpSKINTYPEGENERIC;

    _rpSkinPipeline(rpSKINXBOXPIPELINEGENERIC) = pipeline;

    return pipeline;
}

// match: __rpSkinXboxDestroyPlainPipe @ 0x002D42F0
void
_rpSkinXboxDestroyPlainPipe(void)
{
    if (_rpSkinPipeline(rpSKINXBOXPIPELINEGENERIC))
    {
        RxPipelineDestroy(_rpSkinPipeline(rpSKINXBOXPIPELINEGENERIC));
        _rpSkinPipeline(rpSKINXBOXPIPELINEGENERIC) = NULL;
    }

    _rpSkinXboxDestroyShaders();
}
