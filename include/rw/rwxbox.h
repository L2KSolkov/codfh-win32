/*
 * The RenderWare Xbox driver functions the game calls. Neither source tree
 * has the Xbox driver's headers, so these prototypes are the image's: each
 * is called cdecl with the arguments shown (the clones, unit_122FB0, call
 * all of them). The raster extension is found as the RenderWare drivers do
 * (RASTEREXTFROMRASTER, from the image's own _RwXbRasterExtOffset); its
 * layout is the caller's.
 */
#ifndef RW_RWXBOX_H
#define RW_RWXBOX_H

#include <xtl.h>

#include "rw/batypes.h"
#include "rw/baraster.h"
#include "rw/batextur.h"

#ifdef    __cplusplus
extern "C"
{
#endif         /* __cplusplus */

extern RwInt32 _RwXbRasterExtOffset;

extern D3DVertexBuffer *RwXbCreateVertexBuffer(RwUInt32 size);
extern void RwXbReleaseVertexBuffer(D3DVertexBuffer *vertexBuffer);
extern void _rwXbFlushCacheBuffer(void);
extern void RwXboxSetCurrentVertexShader(DWORD handle);
extern void RwXboxSetCurrentPixelShader(DWORD handle);
extern void RwXboxRenderStateSetTexture(RwTexture *texture, RwUInt32 stage);
/* Reads the texture name from its DDS file (RenderWare Studio's DDS read
 * callback, 0x132610, tries it first). */
extern RwTexture *RwXboxDDSTextureRead(const RwChar *name, const RwChar *maskName);
/* Draws arg_8's arg_4 vertices of arg_C bytes as primitives of the type
 * arg_0 (0x2AF2D0; the full-screen quad, sub_19B6D0, draws a quad list). */
extern void RwXboxDrawVerticesUP(D3DPRIMITIVETYPE primType, RwUInt32 numVertices, void *vertices,
                                 RwUInt32 stride);

/* The driver's texture stage state cache: by state and stage, each stage's
 * changed states listed in order until they are flushed. */
extern RwUInt32 _RwXbTextureStageCacheDirty[][4];
extern RwUInt32 _RwXbTextureStageCacheList[][4];
extern RwUInt32 _RwXbTextureStageCacheCount[4];
extern RwUInt32 _RwXbTextureStageCacheBuffer[][4];

#ifdef    __cplusplus
}
#endif         /* __cplusplus */

#define RASTEREXTFROMRASTER(raster) \
    ((void *)(((RwUInt8 *)(raster)) + _RwXbRasterExtOffset))

/* Sets a stage's cached texture stage state (the full-screen quad, sub_19B6D0,
 * sets each stage's addressing so): a plain block, as no `while (0)` test
 * follows it in the image. Reconstructed from the image; the Xbox driver's
 * header is not available. */
#define RwXbSetCachedTextureStageState(_stage, _type, _value)                \
{                                                                            \
    if (!_RwXbTextureStageCacheDirty[(_type)][(_stage)])                     \
    {                                                                        \
        _RwXbTextureStageCacheDirty[(_type)][(_stage)] = TRUE;               \
        _RwXbTextureStageCacheList[_RwXbTextureStageCacheCount[(_stage)]++][(_stage)] = (_type); \
    }                                                                        \
    _RwXbTextureStageCacheBuffer[(_type)][(_stage)] = (_value);             \
}

/* Sets a stage's texture stage state at once when it differs from the cache
 * (the particles, sub_19FB20): the cache compared and stored, then the XDK's
 * D3DDevice_SetTextureStageState inline. Named for what it does;
 * reconstructed from the image. */
#define RwXbSetTextureStageStateIfChanged(_stage, _type, _value)            \
{                                                                            \
    if (_RwXbTextureStageCacheBuffer[(_type)][(_stage)] != (_value))         \
    {                                                                        \
        _RwXbTextureStageCacheBuffer[(_type)][(_stage)] = (_value);         \
        D3DDevice_SetTextureStageState((_stage), (_type), (_value));        \
    }                                                                        \
}

#endif
