/*
 * codfh-match: RenderWare 3.6's Xbox driver state caches
 * (driver/xbox/xbcache.c), written from the image.
 */
#ifndef XBCACHE_H
#define XBCACHE_H

#define RWXB_TEXTURESTAGES 4

extern DWORD _RwXbRenderStateCacheBuffer[D3DRS_MAX];
extern RwUInt32 _RwXbRenderStateCacheDirty[D3DRS_MAX];
extern D3DRENDERSTATETYPE _RwXbRenderStateCacheList[D3DRS_MAX];
extern RwUInt32 _RwXbRenderStateCacheCount;

extern DWORD _RwXbTextureStageCacheBuffer[D3DTSS_MAX][RWXB_TEXTURESTAGES];
extern RwUInt32 _RwXbTextureStageCacheDirty[D3DTSS_MAX][RWXB_TEXTURESTAGES];
extern D3DTEXTURESTAGESTATETYPE _RwXbTextureStageCacheList[D3DTSS_MAX][RWXB_TEXTURESTAGES];
extern RwUInt32 _RwXbTextureStageCacheCount[RWXB_TEXTURESTAGES];

extern D3DBaseTexture *_RwXbTextureCacheBuffer[RWXB_TEXTURESTAGES];
extern D3DBaseTexture *RwXbTextureCache[RWXB_TEXTURESTAGES];

/* Sets D3D render state state to value through the cache. */
#define RwXboxSetCachedRenderState(state, value)                            \
MACRO_START                                                                 \
{                                                                           \
    if (!_RwXbRenderStateCacheDirty[(state)])                               \
    {                                                                       \
        _RwXbRenderStateCacheDirty[(state)] = TRUE;                         \
        _RwXbRenderStateCacheList[_RwXbRenderStateCacheCount] = (state);    \
        _RwXbRenderStateCacheCount++;                                       \
    }                                                                       \
    _RwXbRenderStateCacheBuffer[(state)] = (value);                         \
}                                                                           \
MACRO_STOP

/* Gets D3D render state state from the cache into *value. */
#define RwXboxGetCachedRenderState(state, value)                            \
    (*(value) = _RwXbRenderStateCacheBuffer[(state)])

/* Sets D3D render state type to value now, past the dirty list. */
#define _rwXbRenderStateForce(type, value)                                  \
MACRO_START                                                                 \
{                                                                           \
    if (_RwXbRenderStateCacheBuffer[(type)] != (DWORD)(value))              \
    {                                                                       \
        _RwXbRenderStateCacheBuffer[(type)] = (value);                      \
        D3DDevice_SetRenderState((type), (value));                          \
    }                                                                       \
}                                                                           \
MACRO_STOP

/* Sets D3D texture stage state type of stage to value now. */
#define _rwXbTextureStageForce(stage, type, value)                          \
MACRO_START                                                                 \
{                                                                           \
    if (_RwXbTextureStageCacheBuffer[(type)][(stage)] != (DWORD)(value))    \
    {                                                                       \
        _RwXbTextureStageCacheBuffer[(type)][(stage)] = (value);            \
        D3DDevice_SetTextureStageState((stage), (type), (value));           \
    }                                                                       \
}                                                                           \
MACRO_STOP

/* An inline with no address, named for the texture-stage force operation.
 * Evidence: _rxXbDefaultRenderCallback (0x2E02A0) matches when the existing
 * force macro's operation has typed inline parameters: this preserves the
 * original dirty-flag and stage-value register scheduling. */
static __forceinline void
_rwXbTextureStageForceInline(DWORD stage, D3DTEXTURESTAGESTATETYPE type, DWORD value)
{
    if (_RwXbTextureStageCacheBuffer[type][stage] != value)
    {
        _RwXbTextureStageCacheBuffer[type][stage] = value;
        D3DDevice_SetTextureStageState(stage, type, value);
    }
}

/* Sets D3D texture stage state type of stage to value through the cache. */
#define RwXboxSetCachedTextureStageState(stage, type, value)                \
MACRO_START                                                                 \
{                                                                           \
    if (!_RwXbTextureStageCacheDirty[(type)][(stage)])                      \
    {                                                                       \
        _RwXbTextureStageCacheDirty[(type)][(stage)] = TRUE;                \
        _RwXbTextureStageCacheList[_RwXbTextureStageCacheCount[(stage)]][(stage)] = (type); \
        _RwXbTextureStageCacheCount[(stage)]++;                             \
    }                                                                       \
    _RwXbTextureStageCacheBuffer[(type)][(stage)] = (value);                \
}                                                                           \
MACRO_STOP

extern void _rwXbFlushCacheBuffer(void);
extern void _rwXbRenderStateInit(D3DRENDERSTATETYPE state, DWORD value);
extern void _rwXbTextureStageInit(DWORD stage, D3DTEXTURESTAGESTATETYPE type, DWORD value);
extern void _rwXbCacheInit(void);
extern void _rwXbTextureRelease(D3DBaseTexture *texture);
extern void RwXboxDrawIndexedVertices(D3DPRIMITIVETYPE primitiveType, UINT vertexCount,
                                      CONST WORD *indexData);
extern void RwXboxDrawVertices(D3DPRIMITIVETYPE primitiveType, UINT startVertex,
                               UINT vertexCount);
extern void RwXboxDrawVerticesUP(D3DPRIMITIVETYPE primitiveType, UINT vertexCount,
                                 CONST void *vertexStreamZeroData,
                                 UINT vertexStreamZeroStride);
extern void RwXboxSetRenderTarget(D3DSurface *renderTarget, D3DSurface *zStencil);

#endif /* XBCACHE_H */
