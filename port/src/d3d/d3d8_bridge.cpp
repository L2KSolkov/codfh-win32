/*
 * The D3D bridge's Xbox side (docs/WIN32_PORT.md W2): the Xbox Direct3D names the RenderWare
 * driver and the game call, over pdev (the device back end, Direct3D 11). This file sees only the bridge's Xbox
 * declarations (port/include/d3d8.h); pd11.cpp sees only d3d11.h.
 *
 * State so far (W0): the device, clears, presentation, viewports, gamma and the render-state
 * and texture-stage-state shadows; surfaces and locks give the game memory laid out as the Xbox
 * lays it out. Drawing, textures, shaders and push buffers are W2.2-W2.8: until then those calls
 * are accepted and logged once (plog_stub).
 */
#include <xtl.h>
#include <stdlib.h>
#include <string.h>

#include "../port.h"
#include "pdev.h"

DWORD D3D__RenderState[D3DRS_MAX];
DWORD D3D__TextureState[D3DTSS_MAXSTAGES][D3DTSS_MAX];

/* The Xbox's resource header words (the XDK's D3DCOMMON_* and D3DFORMAT_* layouts). */
#define XB_COMMON_REFCOUNT_MASK 0x0000FFFF
#define XB_COMMON_TYPE_SURFACE 0x00050000
#define XB_FORMAT_DIMENSION_SHIFT 4
#define XB_FORMAT_FORMAT_SHIFT 8
#define XB_SIZE_HEIGHT_SHIFT 12
#define XB_SIZE_PITCH_SHIFT 24

/* The 640x480 frame the game draws. */
enum { FRAME_W = 640, FRAME_H = 480 };

/* A surface the bridge owns (the back buffer, the depth buffer, a texture's level): the Xbox
   header first, so the game's D3DSurface * is this object. */
struct PortSurface
{
    D3DSurface xb;
    void *bits;         /* CPU memory for locks (W2.2: render targets read back on demand) */
    int width, height, pitch;
};

struct Direct3D
{
    int unused;
};

static Direct3D the_d3d_dummy;
static D3DDevice *the_device;
static PortSurface back_buffer, depth_buffer;
static D3DSurface *render_target, *depth_target;
static D3DVIEWPORT8 viewport = {0, 0, FRAME_W, FRAME_H, 0.0f, 1.0f};

static void surface_init(PortSurface *s, D3DFORMAT fmt, int w, int h, int bpp)
{
    memset(s, 0, sizeof(*s));
    s->width = w;
    s->height = h;
    s->pitch = w * bpp;
    s->xb.Common = 1 | XB_COMMON_TYPE_SURFACE | D3DCOMMON_D3DCREATED;
    s->xb.Format = (2 << XB_FORMAT_DIMENSION_SHIFT) | (fmt << XB_FORMAT_FORMAT_SHIFT);
    s->xb.Size = (w - 1) | ((h - 1) << XB_SIZE_HEIGHT_SHIFT) | ((s->pitch / 64 - 1) << XB_SIZE_PITCH_SHIFT);
    s->bits = calloc(1, (size_t)s->pitch * h);
}

/*
 * Direct3D
 */

/* The Xbox's modes: 640x480 in each back-buffer format, at 60 and 50 Hz, with every combination
   of the widescreen, interlaced, progressive, field and 10x11 aspect flags (the driver matches
   a mode's flags to its configuration's exactly). */
static const D3DFORMAT mode_formats[] = {D3DFMT_LIN_X8R8G8B8, D3DFMT_LIN_A8R8G8B8, D3DFMT_LIN_R5G6B5,
                                         D3DFMT_LIN_X1R5G5B5};
enum { MODE_FLAG_COMBOS = 32, MODE_COUNT = 4 * 2 * MODE_FLAG_COMBOS };

extern "C" Direct3D *WINAPI Direct3DCreate8(UINT)
{
    return &the_d3d_dummy;
}

extern "C" ULONG WINAPI Direct3D_Release(void)
{
    return 0;
}

extern "C" UINT WINAPI Direct3D_GetAdapterModeCount(UINT)
{
    return MODE_COUNT;
}

extern "C" HRESULT WINAPI Direct3D_EnumAdapterModes(UINT, UINT Mode, D3DDISPLAYMODE *pMode)
{
    if (Mode >= MODE_COUNT)
        return E_INVALIDARG;
    UINT combo = Mode % MODE_FLAG_COMBOS;
    UINT rate = (Mode / MODE_FLAG_COMBOS) % 2;
    UINT fmt = Mode / (MODE_FLAG_COMBOS * 2);
    pMode->Width = FRAME_W;
    pMode->Height = FRAME_H;
    pMode->RefreshRate = rate ? 50 : 60;
    pMode->Flags = combo << 4;      /* bits 0x10..0x100 */
    pMode->Format = mode_formats[fmt];
    return D3D_OK;
}

extern "C" int WINAPI Direct3D_SetPushBufferSize(unsigned int, unsigned int)
{
    return 0;
}

extern "C" HRESULT WINAPI Direct3D_CreateDevice(UINT, D3DDEVTYPE, void *, DWORD,
                                                D3DPRESENT_PARAMETERS *pp, D3DDevice **ppDevice)
{
    /* (without a device the bridge runs headless: the game goes on) */
    static int tried;
    if (!tried)
    {
        tried = 1;
        pdev_init(port_hwnd, FRAME_W, FRAME_H, port_config.windowed, port_config.vsync);
    }
    plog("CreateDevice: %ux%u format 0x%lX flags 0x%lX interval 0x%lX", pp->BackBufferWidth,
         pp->BackBufferHeight, pp->BackBufferFormat, pp->Flags, pp->FullScreen_PresentationInterval);
    surface_init(&back_buffer, pp->BackBufferFormat, FRAME_W, FRAME_H, 4);
    surface_init(&depth_buffer, pp->AutoDepthStencilFormat, FRAME_W, FRAME_H, 4);
    render_target = &back_buffer.xb;
    depth_target = &depth_buffer.xb;
    the_device = (D3DDevice *)&the_d3d_dummy;
    *ppDevice = the_device;
    return D3D_OK;
}

/*
 * The device: frames and presentation
 */

extern "C" ULONG WINAPI D3DDevice_Release(void)
{
    pdev_shutdown();
    return 0;
}

extern "C" void WINAPI D3DDevice_BeginScene(void)
{
    pdev_begin_scene();
}

extern "C" void WINAPI D3DDevice_EndScene(void)
{
    pdev_end_scene();
}

/* The Xbox presents at the television's 60 Hz (interval ONE) and the game's timing assumes it;
   the PC's vsync does not always block (Remote Desktop, some drivers), so frames are paced here. */
static void pace_frame(void)
{
    static LARGE_INTEGER freq, next;
    LARGE_INTEGER now;
    if (!freq.QuadPart)
    {
        QueryPerformanceFrequency(&freq);
        QueryPerformanceCounter(&next);
    }
    LONGLONG period = freq.QuadPart / 60;
    next.QuadPart += period;
    QueryPerformanceCounter(&now);
    if (now.QuadPart > next.QuadPart + period)
        next = now;     /* (behind: no catching up) */
    for (;;)
    {
        QueryPerformanceCounter(&now);
        LONGLONG left = next.QuadPart - now.QuadPart;
        if (left <= 0)
            break;
        DWORD ms = (DWORD)(left * 1000 / freq.QuadPart);
        Sleep(ms > 1 ? ms - 1 : 0);
    }
}

extern "C" HRESULT WINAPI IDirect3DDevice8_Present(D3DDevice *, const RECT *, const RECT *, void *, void *)
{
    pdev_present();
    pace_frame();
    port_pump_messages();
    return D3D_OK;
}

extern "C" void WINAPI D3DDevice_Clear(DWORD Count, const D3DRECT *pRects, DWORD Flags, D3DCOLOR Color,
                                       float Z, DWORD Stencil)
{
    unsigned f = 0;
    if (Flags & D3DCLEAR_TARGET)
        f |= PDEV_CLEAR_TARGET;
    if (Flags & D3DCLEAR_ZBUFFER)
        f |= PDEV_CLEAR_DEPTH;
    if (Flags & D3DCLEAR_STENCIL)
        f |= PDEV_CLEAR_STENCIL;
    (void)Count;
    (void)pRects;
    static int logged;
    if (!logged++)
        plog("first clear: flags 0x%lX colour 0x%08lX z %g", Flags, Color, Z);
    pdev_clear(f, Color, Z, Stencil);
}

extern "C" void WINAPI D3DDevice_BlockUntilVerticalBlank(void)
{
    /* (the presentation interval paces frames on PC) */
}

extern "C" HRESULT WINAPI D3DDevice_PersistDisplay(void)
{
    return D3D_OK;
}

extern "C" void WINAPI D3DDevice_EnableOverlay(BOOL)
{
}

extern "C" void WINAPI D3DDevice_SetSoftDisplayFilter(BOOL)
{
}

extern "C" void WINAPI D3DDevice_SetGammaRamp(DWORD, const D3DGAMMARAMP *pRamp)
{
    pdev_set_gamma(pRamp->red, pRamp->green, pRamp->blue);
}

extern "C" BOOL WINAPI D3DDevice_IsFencePending(DWORD)
{
    /* (the bridge's resources are never in flight when the game looks) */
    return FALSE;
}

/*
 * Render targets and viewports
 */

extern "C" void WINAPI D3DDevice_GetBackBuffer(INT, D3DBACKBUFFER_TYPE, D3DSurface **ppBackBuffer)
{
    *ppBackBuffer = &back_buffer.xb;
}

extern "C" D3DSurface *WINAPI D3DDevice_GetBackBuffer2(INT)
{
    return &back_buffer.xb;
}

extern "C" void WINAPI D3DDevice_GetBackBufferScale(float *pX, float *pY)
{
    *pX = 1.0f;
    *pY = 1.0f;
}

extern "C" HRESULT WINAPI D3DDevice_GetRenderTarget(D3DSurface **pp)
{
    *pp = render_target;
    return D3D_OK;
}

extern "C" HRESULT WINAPI D3DDevice_GetDepthStencilSurface(D3DSurface **pp)
{
    *pp = depth_target;
    return D3D_OK;
}

extern "C" void WINAPI D3DDevice_SetRenderTarget(D3DSurface *pRenderTarget, D3DSurface *pNewZStencil)
{
    if (pRenderTarget)
        render_target = pRenderTarget;
    depth_target = pNewZStencil;
    if (pRenderTarget != &back_buffer.xb)
        PORT_STUB();    /* W2.2: render-to-texture */
}

extern "C" void WINAPI D3DDevice_CopyRects(D3DSurface *, const RECT *, UINT, D3DSurface *, const POINT *)
{
    PORT_STUB();        /* W2.2 */
}

extern "C" void WINAPI D3DDevice_SetViewport(const D3DVIEWPORT8 *v)
{
    viewport = *v;
    if (render_target == &back_buffer.xb)
        pdev_set_viewport(v->X, v->Y, v->Width, v->Height, v->MinZ, v->MaxZ);
}

extern "C" void WINAPI D3DDevice_GetViewportOffsetAndScale(D3DVECTOR4 *pOffset, D3DVECTOR4 *pScale)
{
    /* The Xbox's screen-space transform for vertex shaders: clip space to pixels, with the
       Xbox's 24-bit Z scale. */
    pScale->x = viewport.Width * 0.5f;
    pScale->y = -(float)viewport.Height * 0.5f;
    pScale->z = (viewport.MaxZ - viewport.MinZ) * 16777215.0f;
    pScale->w = 1.0f;
    pOffset->x = viewport.X + viewport.Width * 0.5f;
    pOffset->y = viewport.Y + viewport.Height * 0.5f;
    pOffset->z = viewport.MinZ * 16777215.0f;
    pOffset->w = 0.0f;
}

/*
 * State: kept in the Xbox's shadows (the driver's cache compares against them); W2.6 flushes
 * them to the device before each draw.
 */

extern "C" void WINAPI D3DDevice_SetRenderState(D3DRENDERSTATETYPE State, DWORD Value)
{
    if (State < D3DRS_MAX)
        D3D__RenderState[State] = Value;
}

extern "C" void WINAPI D3DDevice_SetRenderStateNotInline(D3DRENDERSTATETYPE State, DWORD Value)
{
    D3DDevice_SetRenderState(State, Value);
}

extern "C" void WINAPI D3DDevice_SetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD Value)
{
    if (Stage < D3DTSS_MAXSTAGES && Type < D3DTSS_MAX)
        D3D__TextureState[Stage][Type] = Value;
}

extern "C" void WINAPI D3DDevice_SetTextureStageStateNotInline(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type,
                                                               DWORD Value)
{
    D3DDevice_SetTextureStageState(Stage, Type, Value);
}

static D3DMATRIX transforms[8];
static D3DMATERIAL8 material;
static D3DLIGHT8 lights[8];
static BOOL light_on[8];
static D3DBaseTexture *textures[4];
static D3DPalette *palettes[4];
static DWORD vertex_shader, pixel_shader;

extern "C" void WINAPI D3DDevice_SetTransform(D3DTRANSFORMSTATETYPE State, const D3DMATRIX *pMatrix)
{
    if (State < 8)
        transforms[State] = *pMatrix;
}

extern "C" void WINAPI D3DDevice_SetMaterial(const D3DMATERIAL8 *pMaterial)
{
    material = *pMaterial;
}

extern "C" HRESULT WINAPI D3DDevice_SetLight(DWORD Index, const D3DLIGHT8 *pLight)
{
    if (Index < 8)
        lights[Index] = *pLight;
    return D3D_OK;
}

extern "C" HRESULT WINAPI D3DDevice_LightEnable(DWORD Index, BOOL Enable)
{
    if (Index < 8)
        light_on[Index] = Enable;
    return D3D_OK;
}

extern "C" void WINAPI D3DDevice_SetTexture(DWORD Stage, D3DBaseTexture *pTexture)
{
    if (Stage < 4)
        textures[Stage] = pTexture;
}

extern "C" void WINAPI D3DDevice_SetPalette(DWORD Stage, D3DPalette *pPalette)
{
    if (Stage < 4)
        palettes[Stage] = pPalette;
}

extern "C" void WINAPI D3DDevice_SetVertexDataColor(INT, D3DCOLOR)
{
    PORT_STUB();        /* W2.9: the immediate-mode vertex colour */
}

/*
 * Shaders: handles now, programs in W2.4/W2.5.
 */

static DWORD next_handle = 0x10000;

extern "C" HRESULT WINAPI D3DDevice_CreateVertexShader(const DWORD *, const DWORD *, DWORD *pHandle, DWORD)
{
    PORT_STUB();
    /* (odd: the Xbox tells programmable handles from FVF codes by bit 0) */
    *pHandle = (next_handle += 2) | 1;
    return D3D_OK;
}

extern "C" void WINAPI D3DDevice_DeleteVertexShader(DWORD)
{
}

extern "C" void WINAPI D3DDevice_SetVertexShader(DWORD Handle)
{
    vertex_shader = Handle;
}

extern "C" void WINAPI D3DDevice_LoadVertexShaderProgram(const DWORD *, DWORD)
{
    PORT_STUB();
}

extern "C" void WINAPI D3DDevice_SelectVertexShader(DWORD Handle, DWORD)
{
    vertex_shader = Handle;
}

extern "C" void WINAPI D3DDevice_SetShaderConstantMode(D3DSHADERCONSTANTMODE)
{
}

static float vs_constants[192][4];

extern "C" void WINAPI D3DDevice_SetVertexShaderConstant(INT Register, const void *pConstantData, DWORD ConstantCount)
{
    /* (registers are -96..95 in the Xbox's 192-constant mode) */
    int r = Register + 96;
    if (r < 0 || r + (int)ConstantCount > 192)
        return;
    memcpy(vs_constants[r], pConstantData, ConstantCount * 16);
}

extern "C" void WINAPI D3DDevice_SetVertexShaderConstantFast(INT Register, const void *pConstantData,
                                                             DWORD ConstantCount)
{
    D3DDevice_SetVertexShaderConstant(Register, pConstantData, ConstantCount);
}

extern "C" void WINAPI D3DDevice_CreatePixelShader(const D3DPIXELSHADERDEF *, DWORD *pHandle)
{
    PORT_STUB();
    *pHandle = (next_handle += 2);
}

extern "C" void WINAPI D3DDevice_DeletePixelShader(DWORD)
{
}

extern "C" void WINAPI D3DDevice_SetPixelShader(DWORD Handle)
{
    pixel_shader = Handle;
}

extern "C" void WINAPI D3DDevice_SetPixelShaderConstant(DWORD, const void *, DWORD)
{
}

/*
 * Drawing (W2.3, W2.8)
 */

static D3DVertexBuffer *streams[16];
static UINT stream_strides[16];

extern "C" void WINAPI D3DDevice_SetStreamSource(UINT StreamNumber, D3DVertexBuffer *pStreamData, UINT Stride)
{
    if (StreamNumber < 16)
    {
        streams[StreamNumber] = pStreamData;
        stream_strides[StreamNumber] = Stride;
    }
}

extern "C" void WINAPI D3DDevice_DrawVertices(D3DPRIMITIVETYPE, UINT, UINT)
{
    PORT_STUB();
}

extern "C" void WINAPI D3DDevice_DrawIndexedVertices(D3DPRIMITIVETYPE, UINT, const WORD *)
{
    PORT_STUB();
}

extern "C" void WINAPI D3DDevice_DrawVerticesUP(D3DPRIMITIVETYPE, UINT, const void *, UINT)
{
    PORT_STUB();
}

/* Push buffers (W2.7): the driver's own method words land in a scratch buffer for now. */
static DWORD push_scratch[64 * 1024];

extern "C" DWORD *WINAPI D3DDevice_BeginPush(DWORD Count)
{
    PORT_STUB();
    return Count <= 64 * 1024 ? push_scratch : (DWORD *)calloc(Count, 4);
}

extern "C" void WINAPI D3DDevice_EndPush(DWORD *pPush)
{
    (void)pPush;
}

extern "C" DWORD *WINAPI D3DDevice_BeginState(DWORD Count)
{
    return D3DDevice_BeginPush(Count);
}

extern "C" void WINAPI D3DDevice_EndState(DWORD *pPush)
{
    D3DDevice_EndPush(pPush);
}

/*
 * Resources
 */

static PortSurface *surface_new(D3DFORMAT fmt, int w, int h, int bpp)
{
    PortSurface *s = (PortSurface *)calloc(1, sizeof(PortSurface));
    surface_init(s, fmt, w, h, bpp);
    return s;
}

extern "C" HRESULT WINAPI D3DDevice_CreateCubeTexture(UINT, UINT, DWORD, D3DFORMAT, D3DPOOL, D3DCubeTexture **pp)
{
    PORT_STUB();        /* W2.2 */
    *pp = (D3DCubeTexture *)calloc(1, sizeof(D3DCubeTexture) + 64);
    (*pp)->Common = 1;
    return D3D_OK;
}

extern "C" HRESULT WINAPI D3DDevice_CreateDepthStencilSurface(UINT Width, UINT Height, D3DFORMAT Format,
                                                              D3DMULTISAMPLE_TYPE, D3DSurface **ppSurface)
{
    *ppSurface = &surface_new(Format, Width, Height, 4)->xb;
    return D3D_OK;
}

extern "C" ULONG WINAPI D3DResource_Release(D3DResource *pThis)
{
    /* (the bridge's own surfaces live as long as the device; W2.2 frees textures) */
    if (pThis && (pThis->Common & XB_COMMON_REFCOUNT_MASK))
        pThis->Common--;
    return pThis ? pThis->Common & XB_COMMON_REFCOUNT_MASK : 0;
}

extern "C" void WINAPI D3DResource_BlockUntilNotBusy(D3DResource *)
{
}

extern "C" ULONG WINAPI D3DSurface_Release(D3DSurface *pThis)
{
    return D3DResource_Release(pThis);
}

static int is_port_surface(D3DSurface *s)
{
    return s == &back_buffer.xb || s == &depth_buffer.xb || (s && (s->Common & XB_COMMON_TYPE_SURFACE) &&
                                                             (s->Common & D3DCOMMON_D3DCREATED) && !s->Data);
}

extern "C" void WINAPI D3DSurface_LockRect(D3DSurface *pThis, D3DLOCKED_RECT *pLockedRect, const RECT *, DWORD)
{
    if (is_port_surface(pThis))
    {
        PortSurface *s = (PortSurface *)pThis;
        pLockedRect->pBits = s->bits;
        pLockedRect->Pitch = s->pitch;
        return;
    }
    /* a surface over the driver's own memory: its rows as the Xbox lays them out */
    pLockedRect->pBits = (void *)(pThis->Data | 0x80000000);
    pLockedRect->Pitch = (INT)((((pThis->Size >> XB_SIZE_PITCH_SHIFT) & 0xFF) + 1) * 64);
}

extern "C" void WINAPI D3DSurface_UnlockRect(D3DSurface *)
{
}

/* Texture levels: decoded from the Xbox format word XGSetTextureHeader wrote (xgraphics.cpp). */
extern "C" int port_xb_texture_level(const D3DBaseTexture *t, UINT level, int face, DWORD *offset, int *width,
                                     int *height, int *pitch);

extern "C" void WINAPI D3DTexture_GetLevelDesc(D3DTexture *pThis, UINT Level, D3DSURFACE_DESC *pDesc)
{
    DWORD off;
    int w, h, p;
    port_xb_texture_level(pThis, Level, 0, &off, &w, &h, &p);
    memset(pDesc, 0, sizeof(*pDesc));
    pDesc->Format = (pThis->Format >> XB_FORMAT_FORMAT_SHIFT) & 0xFF;
    pDesc->Width = w;
    pDesc->Height = h;
    pDesc->Size = p * h;
}

extern "C" HRESULT WINAPI D3DTexture_GetSurfaceLevel(D3DTexture *pTexture, UINT Level, D3DSurface **pp)
{
    DWORD off;
    int w, h, p;
    port_xb_texture_level(pTexture, Level, 0, &off, &w, &h, &p);
    D3DSurface *s = (D3DSurface *)calloc(1, sizeof(D3DSurface));
    s->Common = 1 | XB_COMMON_TYPE_SURFACE;
    s->Data = pTexture->Data + off;
    s->Format = pTexture->Format;
    s->Size = (w - 1) | ((h - 1) << XB_SIZE_HEIGHT_SHIFT) | ((p > 64 ? p / 64 - 1 : 0) << XB_SIZE_PITCH_SHIFT);
    s->Parent = pTexture;
    *pp = s;
    return D3D_OK;
}

extern "C" void WINAPI D3DTexture_LockRect(D3DTexture *pThis, UINT Level, D3DLOCKED_RECT *pLockedRect,
                                           const RECT *, DWORD)
{
    DWORD off;
    int w, h, p;
    port_xb_texture_level(pThis, Level, 0, &off, &w, &h, &p);
    pLockedRect->pBits = (void *)((pThis->Data | 0x80000000) + off);
    pLockedRect->Pitch = p;
}

extern "C" void WINAPI D3DTexture_UnlockRect(D3DTexture *, UINT)
{
    /* W2.2: the level is re-uploaded when next set */
}

extern "C" HRESULT WINAPI D3DCubeTexture_GetCubeMapSurface(D3DCubeTexture *pTexture, D3DCUBEMAP_FACES FaceType,
                                                            UINT Level, D3DSurface **pp)
{
    DWORD off;
    int w, h, p;
    port_xb_texture_level(pTexture, Level, FaceType, &off, &w, &h, &p);
    D3DSurface *s = (D3DSurface *)calloc(1, sizeof(D3DSurface));
    s->Common = 1 | XB_COMMON_TYPE_SURFACE;
    s->Data = pTexture->Data + off;
    s->Format = pTexture->Format;
    s->Parent = pTexture;
    *pp = s;
    return D3D_OK;
}

extern "C" void WINAPI D3DCubeTexture_LockRect(D3DCubeTexture *pThis, D3DCUBEMAP_FACES FaceType, UINT Level,
                                               D3DLOCKED_RECT *pLockedRect, const RECT *, DWORD)
{
    DWORD off;
    int w, h, p;
    port_xb_texture_level(pThis, Level, FaceType, &off, &w, &h, &p);
    pLockedRect->pBits = (void *)((pThis->Data | 0x80000000) + off);
    pLockedRect->Pitch = p;
}

extern "C" void WINAPI D3DPalette_Lock(D3DPalette *pPalette, D3DCOLOR **ppColors, DWORD)
{
    *ppColors = (D3DCOLOR *)(pPalette->Data | 0x80000000);
}

extern "C" void WINAPI D3DPalette_Unlock(D3DPalette *)
{
}

extern "C" void WINAPI D3DVertexBuffer_Lock(D3DVertexBuffer *pBuffer, UINT OffsetToLock, UINT, BYTE **ppbData,
                                            DWORD Flags)
{
    *ppbData = D3DVertexBuffer_Lock2(pBuffer, Flags) + OffsetToLock;
}

extern "C" BYTE *WINAPI D3DVertexBuffer_Lock2(D3DVertexBuffer *pThis, DWORD)
{
    /* (the driver's vertex memory, from XPhysicalAlloc: Data is its "physical" address) */
    return (BYTE *)(pThis->Data | 0x80000000);
}

extern "C" void WINAPI D3DVertexBuffer_Unlock(D3DVertexBuffer *)
{
}
