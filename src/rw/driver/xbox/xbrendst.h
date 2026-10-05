/*
 * codfh-match: RenderWare 3.6's Xbox driver render states
 * (driver/xbox/xbrendst.c), written from the image. Include xbcache.h first.
 */
#ifndef XBRENDST_H
#define XBRENDST_H

/* RenderWare's own render state values (RwXbStateCache, 0x58 bytes; the
   Godfather PDB's names). */
typedef struct _rwXbStateCache _rwXbStateCache;
struct _rwXbStateCache
{
    RwBool                  zTestEnable;
    RwBool                  zWriteEnable;
    RwStencilOperation      stencilFailOp;
    RwStencilOperation      stencilZFailOp;
    RwStencilOperation      stencilPassOp;
    RwStencilFunction       stencilFunction;
    RwBool                  vertexAlphaBlendEnable;
    RwBool                  textureAlphaBlendEnable;
    RwCullMode              cullMode;
    RwFogType               fogType;
    RwShadeMode             shadeMode;
    RwRaster               *curTexRaster;
    RwTextureFilterMode     filterMode;
    RwTextureAddressMode    texAddressU;
    RwTextureAddressMode    texAddressV;
    RwInt32                 maxAnisotropy;
    RwBlendFunction         srcBlend;
    RwBlendFunction         dstBlend;
    DWORD                   vertexShader;
    DWORD                   pixelShader;
    RwAlphaTestFunction     alphaTestFunction;
    RwBool                  alphaTestEnable;
};

extern _rwXbStateCache RwXbStateCache;

extern void _rwXbRenderStateOpen(void);
extern RwBool _rwXbGetRenderState(RwRenderState nState, void *param);
extern RwBool _rwXbRenderStateTextureRaster(RwRaster *raster);
extern void _rwXbRenderStateTextureRasterPurge(RwRaster *raster);
extern void RwXboxRenderStateSetTexture(RwTexture *texture, RwUInt32 stage);
extern void _rwXboxSetTextureAnisotropyOffset(RwInt32 offset);
extern RwBool _rwXbRenderStateStencilFail(RwStencilOperation operation);
extern RwBool _rwXbRenderStateStencilZFail(RwStencilOperation operation);
extern RwBool _rwXbRenderStateStencilPass(RwStencilOperation operation);
extern RwBool _rwXbRenderStateStencilFunction(RwStencilFunction function);
extern RwBool _rwXbSetRenderState(RwRenderState nState, void *param);

#endif /* XBRENDST_H */
