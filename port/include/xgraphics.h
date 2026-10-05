/*
 * Win32 port bridge (docs/WIN32_PORT.md W2): stands in for the XDK's xgraphics.h. The driver's
 * rasters (xbraster.c) build texture and palette headers and swizzle locked pixels with it; the
 * skin pipeline (skinxboxrender.c) assembles and splices its vertex shaders at run time. The
 * bridge implements these: swizzling stays (the disc's textures are swizzled), and the shader
 * calls hand back the text the bridge maps to its HLSL replacements (section 8).
 */
#ifndef PORT_XGRAPHICS_H
#define PORT_XGRAPHICS_H

#include <d3d8.h>
#include <xgmath.h>

#ifdef __cplusplus
extern "C" {
#endif

/* An assembler output buffer. */
typedef struct XGBuffer XGBuffer;
typedef XGBuffer *LPXGBUFFER;

LPVOID WINAPI XGBuffer_GetBufferPointer(XGBuffer *pThis);
ULONG WINAPI XGBuffer_Release(XGBuffer *pThis);

/* XGAssembleShader's flags, as the skin pipeline passes them. */
#define SASM_SKIPVALIDATION (1 << 1)
#define SASM_DONOTOPTIMIZE (1 << 2)
#define SASM_SKIPPREPROCESSOR (1 << 13)
#define SASM_DISABLE_GLOBAL_OPTIMIZATIONS (1 << 14)

typedef HRESULT (*SASM_ResolverCallback)(LPVOID pResolverUserData, BOOL fSystemInclude,
                                         LPCSTR pFileName, LPXGBUFFER *ppResult);

HRESULT WINAPI XGAssembleShader(LPCSTR pSourceFileName, LPCVOID pSrcData, UINT SrcDataLen,
                                DWORD Flags, LPXGBUFFER *pConstants, LPXGBUFFER *pCompiledShader,
                                LPXGBUFFER *pErrorLog, LPXGBUFFER *pListing,
                                SASM_ResolverCallback pResolver, LPVOID pResolverUserData,
                                LPDWORD pShaderType);
HRESULT WINAPI XGSpliceVertexShaders(DWORD *pNewShader, DWORD *pcbNewShaderBufferSize,
                                     DWORD *pNewInstructionCount,
                                     const DWORD *const *ppShaderArray, DWORD NumShaders,
                                     BOOL bOptimizeResults);

/* Texture and palette headers over memory the driver allocated itself. */
DWORD WINAPI XGSetTextureHeader(UINT Width, UINT Height, UINT Levels, DWORD Usage, D3DFORMAT Format,
                                D3DPOOL Pool, D3DTexture *pTexture, UINT Data, UINT Pitch);
VOID WINAPI XGSetPaletteHeader(D3DPALETTESIZE Size, D3DPalette *pPalette, UINT Data);

/* Swizzling between the Xbox's swizzled texture layout and linear rows. */
VOID WINAPI XGSwizzleRect(LPCVOID pSource, DWORD Pitch, LPCRECT pRect, LPVOID pDest, DWORD Width,
                          DWORD Height, const LPPOINT pPoint, DWORD BytesPerPixel);
VOID WINAPI XGUnswizzleRect(LPCVOID pSource, DWORD Width, DWORD Height, LPCRECT pRect,
                            LPVOID pDest, DWORD Pitch, const LPPOINT pPoint, DWORD BytesPerPixel);

#ifdef __cplusplus
}
#endif

#endif
