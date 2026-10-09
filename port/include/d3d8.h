/*
 * Win32 port bridge (docs/WIN32_PORT.md W2): stands in for the XDK's d3d8.h (Xbox Direct3D 8).
 * The bridge keeps the Xbox API's names (D3DDevice_*, D3DTexture_*, D3D__RenderState...) and
 * implements them over Direct3D 11 (port/src/d3d). Nothing here includes a PC Direct3D header: the
 * Xbox and the PC APIs share names with different values (d3d8values.h), so only the bridge's
 * device back end (pd11.cpp), which never includes this header, sees Direct3D 11.
 *
 * Declared from what the RenderWare Xbox driver, pipelines and plugins and the game's direct
 * Direct3D units use. Every call that the XDK makes an inline (state setters, lock wrappers,
 * Get*Surface forms) is an ordinary function here: the bridge decides what each one does.
 */
#ifndef PORT_D3D8_H
#define PORT_D3D8_H
/* The XDK header's own guard: shared headers that declare a d3d8.h name themselves test it. */
#define _D3D8_H_

#include <xtl.h>
#include <d3d8values.h>

#ifdef __cplusplus
extern "C" {
#endif

#define D3D_OK S_OK
#define D3D_SDK_VERSION 0

typedef DWORD D3DCOLOR;
typedef DWORD D3DFORMAT;
typedef DWORD D3DRENDERSTATETYPE;
typedef DWORD D3DTEXTURESTAGESTATETYPE;
typedef DWORD D3DTRANSFORMSTATETYPE;
typedef DWORD D3DPRIMITIVETYPE;
typedef DWORD D3DMULTISAMPLE_TYPE;
typedef DWORD D3DSWAPEFFECT;
typedef DWORD D3DDEVTYPE;
typedef DWORD D3DPOOL;
typedef DWORD D3DLIGHTTYPE;
typedef DWORD D3DBLEND;
typedef DWORD D3DCUBEMAP_FACES;
typedef DWORD D3DPALETTESIZE;
typedef DWORD D3DBACKBUFFER_TYPE;
typedef DWORD D3DSHADERCONSTANTMODE;
typedef DWORD D3DRESOURCETYPE;

typedef struct _D3DVECTOR
{
    float x, y, z;
} D3DVECTOR;

typedef struct _D3DVECTOR4
{
    float x, y, z, w;
} D3DVECTOR4;

typedef struct _D3DCOLORVALUE
{
    float r, g, b, a;
} D3DCOLORVALUE;

typedef struct _D3DRECT
{
    LONG x1, y1, x2, y2;
} D3DRECT;

typedef struct _D3DMATRIX
{
    union
    {
        struct
        {
            float _11, _12, _13, _14;
            float _21, _22, _23, _24;
            float _31, _32, _33, _34;
            float _41, _42, _43, _44;
        };
        float m[4][4];
    };
} D3DMATRIX;

typedef struct _D3DVIEWPORT8
{
    DWORD X, Y, Width, Height;
    float MinZ, MaxZ;
} D3DVIEWPORT8;

typedef struct _D3DMATERIAL8
{
    D3DCOLORVALUE Diffuse;
    D3DCOLORVALUE Ambient;
    D3DCOLORVALUE Specular;
    D3DCOLORVALUE Emissive;
    float Power;
} D3DMATERIAL8;

typedef struct _D3DLIGHT8
{
    D3DLIGHTTYPE Type;
    D3DCOLORVALUE Diffuse;
    D3DCOLORVALUE Specular;
    D3DCOLORVALUE Ambient;
    D3DVECTOR Position;
    D3DVECTOR Direction;
    float Range;
    float Falloff;
    float Attenuation0;
    float Attenuation1;
    float Attenuation2;
    float Theta;
    float Phi;
} D3DLIGHT8;

typedef struct _D3DLOCKED_RECT
{
    INT Pitch;
    void *pBits;
} D3DLOCKED_RECT;

typedef struct _D3DSURFACE_DESC
{
    D3DFORMAT Format;
    D3DRESOURCETYPE Type;
    DWORD Usage;
    UINT Size;
    D3DMULTISAMPLE_TYPE MultiSampleType;
    UINT Width;
    UINT Height;
} D3DSURFACE_DESC;

/* A display mode: Flags are D3DPRESENTFLAG_* (interlaced, widescreen...). */
typedef struct _D3DDISPLAYMODE
{
    UINT Width;
    UINT Height;
    UINT RefreshRate;
    DWORD Flags;
    D3DFORMAT Format;
} D3DDISPLAYMODE;

/* The gamma ramp: the Xbox's ramps are bytes. */
typedef struct _D3DGAMMARAMP
{
    BYTE red[256];
    BYTE green[256];
    BYTE blue[256];
} D3DGAMMARAMP;

/* A pixel shader definition: the matfx pipelines hand the device their own dword tables. */
typedef struct _D3DPIXELSHADERDEF D3DPIXELSHADERDEF;

/*
 * Resources. The driver builds resource headers itself (vertex buffers, palettes and textures
 * over its own memory: Common, Data and Lock written directly), so the headers keep the Xbox
 * layout. In C++ they inherit, as the XDK's do, and carry the methods the game's units call.
 */
typedef struct D3DResource D3DResource;
typedef struct D3DBaseTexture D3DBaseTexture;
typedef struct D3DTexture D3DTexture;
typedef struct D3DCubeTexture D3DCubeTexture;
typedef struct D3DSurface D3DSurface;
typedef struct D3DPalette D3DPalette;
typedef struct D3DVertexBuffer D3DVertexBuffer;
typedef struct Direct3D Direct3D;
typedef struct D3DDevice D3DDevice;

typedef D3DTexture IDirect3DTexture8;
typedef D3DSurface IDirect3DSurface8;
typedef D3DPalette IDirect3DPalette8;

#ifdef __cplusplus
#define PORT_D3D_BASE(base) : public base
#define PORT_D3D_FIELDS(fields)
#else
#define PORT_D3D_BASE(base)
#define PORT_D3D_FIELDS(fields) fields
#endif

#define PORT_D3D_RESOURCE_FIELDS \
    DWORD Common;   /* reference count, type and flags */ \
    DWORD Data;     /* the resource's memory */ \
    DWORD Lock;     /* its GPU fence */

#define PORT_D3D_PIXEL_FIELDS PORT_D3D_RESOURCE_FIELDS \
    DWORD Format;   /* the Xbox format word (format, dimensions, mip count) */ \
    DWORD Size;     /* a linear texture's size, zero for a swizzled one */

struct D3DResource
{
    PORT_D3D_RESOURCE_FIELDS
#ifdef __cplusplus
    ULONG Release();
#endif
};

#ifdef __cplusplus
struct D3DPixelContainer : public D3DResource
{
    DWORD Format;
    DWORD Size;
};
#endif

struct D3DBaseTexture PORT_D3D_BASE(D3DPixelContainer)
{
    PORT_D3D_FIELDS(PORT_D3D_PIXEL_FIELDS)
};

struct D3DTexture PORT_D3D_BASE(D3DBaseTexture)
{
    PORT_D3D_FIELDS(PORT_D3D_PIXEL_FIELDS)
#ifdef __cplusplus
    HRESULT GetLevelDesc(UINT Level, D3DSURFACE_DESC *pDesc);
    HRESULT LockRect(UINT Level, D3DLOCKED_RECT *pLockedRect, const RECT *pRect, DWORD Flags);
#endif
};

struct D3DCubeTexture PORT_D3D_BASE(D3DBaseTexture)
{
    PORT_D3D_FIELDS(PORT_D3D_PIXEL_FIELDS)
};

struct D3DSurface PORT_D3D_BASE(D3DPixelContainer)
{
    PORT_D3D_FIELDS(PORT_D3D_PIXEL_FIELDS)
    D3DBaseTexture *Parent;     /* the texture it is a level of, if any */
#ifdef __cplusplus
    HRESULT LockRect(D3DLOCKED_RECT *pLockedRect, const RECT *pRect, DWORD Flags);
    HRESULT UnlockRect();
#endif
};

struct D3DPalette PORT_D3D_BASE(D3DResource)
{
    PORT_D3D_FIELDS(PORT_D3D_RESOURCE_FIELDS)
};

struct D3DVertexBuffer PORT_D3D_BASE(D3DResource)
{
    PORT_D3D_FIELDS(PORT_D3D_RESOURCE_FIELDS)
#ifdef __cplusplus
    HRESULT Lock(UINT OffsetToLock, UINT UnusedSizeToLock, BYTE **ppbData, DWORD Flags);
    HRESULT Unlock();
#endif
};

typedef struct _D3DPRESENT_PARAMETERS_
{
    UINT BackBufferWidth;
    UINT BackBufferHeight;
    D3DFORMAT BackBufferFormat;
    UINT BackBufferCount;
    D3DMULTISAMPLE_TYPE MultiSampleType;
    D3DSWAPEFFECT SwapEffect;
    HWND hDeviceWindow;
    BOOL Windowed;
    BOOL EnableAutoDepthStencil;
    D3DFORMAT AutoDepthStencilFormat;
    DWORD Flags;                /* D3DPRESENTFLAG_* */
    UINT FullScreen_RefreshRateInHz;
    UINT FullScreen_PresentationInterval;
    D3DSurface *BufferSurfaces[3];
    D3DSurface *DepthStencilSurface;
} D3DPRESENT_PARAMETERS;

/* Vertex shader declarations (the driver's and pipelines' static declaration tables). */
#define D3DVSD_STREAM(stream) ((1u << 29) | (stream))
#define D3DVSD_REG(reg, type) ((2u << 29) | ((type) << 16) | (reg))
#define D3DVSD_END() 0xFFFFFFFF

/* A raw push-buffer method word (the 2D, sprite and no-light submit paths write their own). */
#define D3DPUSH_ENCODE(method, count) (((count) << 18) + (method))

/* The render-state and texture-stage-state shadows the driver's state cache compares against;
   the bridge keeps them current and flushes them to the device before each draw. */
extern DWORD D3D__RenderState[D3DRS_MAX];
extern DWORD D3D__TextureState[D3DTSS_MAXSTAGES][D3DTSS_MAX];

/* Direct3D */
Direct3D *WINAPI Direct3DCreate8(UINT SDKVersion);
ULONG WINAPI Direct3D_Release(void);
UINT WINAPI Direct3D_GetAdapterModeCount(UINT Adapter);
HRESULT WINAPI Direct3D_EnumAdapterModes(UINT Adapter, UINT Mode, D3DDISPLAYMODE *pMode);
HRESULT WINAPI Direct3D_CreateDevice(UINT Adapter, D3DDEVTYPE DeviceType, void *pUnused,
                                     DWORD BehaviorFlags, D3DPRESENT_PARAMETERS *pPresentationParameters,
                                     D3DDevice **ppReturnedDeviceInterface);
/* Declared as game/startup.h declares it too (int/unsigned int), so the two agree whichever comes
   first; the game ignores the result. */
int WINAPI Direct3D_SetPushBufferSize(unsigned int PushBufferSize, unsigned int KickOffSize);

/* The device: frames and presentation */
ULONG WINAPI D3DDevice_Release(void);
void WINAPI D3DDevice_BeginScene(void);
void WINAPI D3DDevice_EndScene(void);
HRESULT WINAPI IDirect3DDevice8_Present(D3DDevice *pThis, const RECT *pSourceRect,
                                        const RECT *pDestRect, void *pUnused, void *pUnused2);
void WINAPI D3DDevice_Clear(DWORD Count, const D3DRECT *pRects, DWORD Flags, D3DCOLOR Color,
                            float Z, DWORD Stencil);
void WINAPI D3DDevice_BlockUntilVerticalBlank(void);
HRESULT WINAPI D3DDevice_PersistDisplay(void);
void WINAPI D3DDevice_EnableOverlay(BOOL Enable);
void WINAPI D3DDevice_SetSoftDisplayFilter(BOOL Enable);
void WINAPI D3DDevice_SetGammaRamp(DWORD Flags, const D3DGAMMARAMP *pRamp);
BOOL WINAPI D3DDevice_IsFencePending(DWORD Fence);

/* Render targets and viewports */
void WINAPI D3DDevice_GetBackBuffer(INT BackBuffer, D3DBACKBUFFER_TYPE UnusedType,
                                    D3DSurface **ppBackBuffer);
D3DSurface *WINAPI D3DDevice_GetBackBuffer2(INT BackBuffer);
void WINAPI D3DDevice_GetBackBufferScale(float *pX, float *pY);
HRESULT WINAPI D3DDevice_GetRenderTarget(D3DSurface **ppRenderTarget);
D3DSurface *WINAPI D3DDevice_GetRenderTarget2(void);
HRESULT WINAPI D3DDevice_GetDepthStencilSurface(D3DSurface **ppZStencilSurface);
void WINAPI D3DDevice_SetRenderTarget(D3DSurface *pRenderTarget, D3DSurface *pNewZStencil);
void WINAPI D3DDevice_CopyRects(D3DSurface *pSourceSurface, const RECT *pSourceRectsArray,
                                UINT cRects, D3DSurface *pDestinationSurface,
                                const POINT *pDestPointsArray);
void WINAPI D3DDevice_SetViewport(const D3DVIEWPORT8 *pViewport);
void WINAPI D3DDevice_GetViewportOffsetAndScale(D3DVECTOR4 *pOffset, D3DVECTOR4 *pScale);

/* State */
void WINAPI D3DDevice_SetRenderState(D3DRENDERSTATETYPE State, DWORD Value);
void WINAPI D3DDevice_SetRenderStateNotInline(D3DRENDERSTATETYPE State, DWORD Value);
void WINAPI D3DDevice_SetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD Value);
void WINAPI D3DDevice_SetTextureStageStateNotInline(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type,
                                                    DWORD Value);
void WINAPI D3DDevice_SetTransform(D3DTRANSFORMSTATETYPE State, const D3DMATRIX *pMatrix);
void WINAPI D3DDevice_SetMaterial(const D3DMATERIAL8 *pMaterial);
HRESULT WINAPI D3DDevice_SetLight(DWORD Index, const D3DLIGHT8 *pLight);
HRESULT WINAPI D3DDevice_LightEnable(DWORD Index, BOOL Enable);
void WINAPI D3DDevice_SetTexture(DWORD Stage, D3DBaseTexture *pTexture);
void WINAPI D3DDevice_SetPalette(DWORD Stage, D3DPalette *pPalette);
void WINAPI D3DDevice_SetVertexDataColor(INT Register, D3DCOLOR Color);

/* Shaders */
HRESULT WINAPI D3DDevice_CreateVertexShader(const DWORD *pDeclaration, const DWORD *pFunction,
                                            DWORD *pHandle, DWORD Usage);
void WINAPI D3DDevice_DeleteVertexShader(DWORD Handle);
void WINAPI D3DDevice_SetVertexShader(DWORD Handle);
void WINAPI D3DDevice_LoadVertexShaderProgram(const DWORD *pFunction, DWORD Address);
void WINAPI D3DDevice_SelectVertexShader(DWORD Handle, DWORD Address);
void WINAPI D3DDevice_SetShaderConstantMode(D3DSHADERCONSTANTMODE Mode);
void WINAPI D3DDevice_SetVertexShaderConstant(INT Register, const void *pConstantData,
                                              DWORD ConstantCount);
void WINAPI D3DDevice_SetVertexShaderConstantFast(INT Register, const void *pConstantData,
                                                  DWORD ConstantCount);
void WINAPI D3DDevice_CreatePixelShader(const D3DPIXELSHADERDEF *pPSDef, DWORD *pHandle);
void WINAPI D3DDevice_DeletePixelShader(DWORD Handle);
void WINAPI D3DDevice_SetPixelShader(DWORD Handle);
void WINAPI D3DDevice_SetPixelShaderConstant(DWORD Register, const void *pConstantData,
                                             DWORD ConstantCount);

/* Drawing */
void WINAPI D3DDevice_SetStreamSource(UINT StreamNumber, D3DVertexBuffer *pStreamData, UINT Stride);
void WINAPI D3DDevice_DrawVertices(D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex,
                                   UINT VertexCount);
void WINAPI D3DDevice_DrawIndexedVertices(D3DPRIMITIVETYPE PrimitiveType, UINT VertexCount,
                                          const WORD *pIndexData);
void WINAPI D3DDevice_DrawVerticesUP(D3DPRIMITIVETYPE PrimitiveType, UINT VertexCount,
                                     const void *pVertexStreamZeroData,
                                     UINT VertexStreamZeroStride);

/* Push buffers: the method words the driver writes itself, decoded by the bridge (W2.7). */
DWORD *WINAPI D3DDevice_BeginPush(DWORD Count);
void WINAPI D3DDevice_EndPush(DWORD *pPush);
DWORD *WINAPI D3DDevice_BeginState(DWORD Count);
void WINAPI D3DDevice_EndState(DWORD *pPush);

/* Resource creation */
HRESULT WINAPI D3DDevice_CreateCubeTexture(UINT EdgeLength, UINT Levels, DWORD Usage,
                                           D3DFORMAT Format, D3DPOOL UnusedPool,
                                           D3DCubeTexture **ppCubeTexture);
HRESULT WINAPI D3DDevice_CreateDepthStencilSurface(UINT Width, UINT Height, D3DFORMAT Format,
                                                   D3DMULTISAMPLE_TYPE UnusedMultiSample,
                                                   D3DSurface **ppSurface);

/* Resources */
ULONG WINAPI D3DResource_Release(D3DResource *pThis);
void WINAPI D3DResource_BlockUntilNotBusy(D3DResource *pThis);
ULONG WINAPI D3DSurface_Release(D3DSurface *pThis);
void WINAPI D3DSurface_LockRect(D3DSurface *pThis, D3DLOCKED_RECT *pLockedRect, const RECT *pRect,
                                DWORD Flags);
void WINAPI D3DSurface_UnlockRect(D3DSurface *pThis);
void WINAPI D3DTexture_GetLevelDesc(D3DTexture *pThis, UINT Level, D3DSURFACE_DESC *pDesc);
HRESULT WINAPI D3DTexture_GetSurfaceLevel(D3DTexture *pTexture, UINT Level,
                                          D3DSurface **ppSurfaceLevel);
void WINAPI D3DTexture_LockRect(D3DTexture *pThis, UINT Level, D3DLOCKED_RECT *pLockedRect,
                                const RECT *pRect, DWORD Flags);
void WINAPI D3DTexture_UnlockRect(D3DTexture *pThis, UINT Level);
HRESULT WINAPI D3DCubeTexture_GetCubeMapSurface(D3DCubeTexture *pTexture, D3DCUBEMAP_FACES FaceType,
                                                UINT Level, D3DSurface **ppCubeMapSurface);
void WINAPI D3DCubeTexture_LockRect(D3DCubeTexture *pThis, D3DCUBEMAP_FACES FaceType, UINT Level,
                                    D3DLOCKED_RECT *pLockedRect, const RECT *pRect, DWORD Flags);
void WINAPI D3DPalette_Lock(D3DPalette *pPalette, D3DCOLOR **ppColors, DWORD Flags);
void WINAPI D3DPalette_Unlock(D3DPalette *pThis);
void WINAPI D3DVertexBuffer_Lock(D3DVertexBuffer *pBuffer, UINT OffsetToLock,
                                 UINT UnusedSizeToLock, BYTE **ppbData, DWORD Flags);
BYTE *WINAPI D3DVertexBuffer_Lock2(D3DVertexBuffer *pThis, DWORD Flags);
void WINAPI D3DVertexBuffer_Unlock(D3DVertexBuffer *pThis);

/* Layout checks: the sizes the Xbox build has (the driver builds these headers itself). */
typedef char port_check_D3DSurface[sizeof(D3DSurface) == 0x18 ? 1 : -1];
typedef char port_check_D3DVertexBuffer[sizeof(D3DVertexBuffer) == 0x0C ? 1 : -1];
typedef char port_check_D3DBaseTexture[sizeof(D3DBaseTexture) == 0x14 ? 1 : -1];
typedef char port_check_D3DPRESENT_PARAMETERS[sizeof(D3DPRESENT_PARAMETERS) == 0x44 ? 1 : -1];
typedef char port_check_D3DLIGHT8[sizeof(D3DLIGHT8) == 0x68 ? 1 : -1];

#ifdef __cplusplus
}

/* The C++ forms the game's units call. */
inline ULONG D3DResource::Release() { return D3DResource_Release(this); }
inline HRESULT D3DTexture::GetLevelDesc(UINT Level, D3DSURFACE_DESC *pDesc)
{
    D3DTexture_GetLevelDesc(this, Level, pDesc);
    return D3D_OK;
}
inline HRESULT D3DTexture::LockRect(UINT Level, D3DLOCKED_RECT *pLockedRect, const RECT *pRect,
                                    DWORD Flags)
{
    D3DTexture_LockRect(this, Level, pLockedRect, pRect, Flags);
    return D3D_OK;
}
inline HRESULT D3DSurface::LockRect(D3DLOCKED_RECT *pLockedRect, const RECT *pRect, DWORD Flags)
{
    D3DSurface_LockRect(this, pLockedRect, pRect, Flags);
    return D3D_OK;
}
inline HRESULT D3DSurface::UnlockRect()
{
    D3DSurface_UnlockRect(this);
    return D3D_OK;
}
inline HRESULT D3DVertexBuffer::Lock(UINT OffsetToLock, UINT UnusedSizeToLock, BYTE **ppbData,
                                     DWORD Flags)
{
    D3DVertexBuffer_Lock(this, OffsetToLock, UnusedSizeToLock, ppbData, Flags);
    return D3D_OK;
}
inline HRESULT D3DVertexBuffer::Unlock()
{
    D3DVertexBuffer_Unlock(this);
    return D3D_OK;
}

struct D3DDevice
{
    static void SetVertexDataColor(INT Register, D3DCOLOR Color)
    {
        D3DDevice_SetVertexDataColor(Register, Color);
    }
};
#endif

#endif
