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

#include <vector>

#include "../port.h"
#include "pdev.h"
#include "xstate.h"

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
/* the back buffer was locked this frame (the movie player writes its frames there): its memory
   becomes the frame at Present */
static int back_buffer_written;
static D3DSurface *render_target, *depth_target;
XState xs;

/* CODFH_TRACE=n: frame n's render-target changes, viewports, clears and draw counts logged. */
static int trace_frame = -1;
static unsigned trace_draws;
int port_trace_on(void)
{
    if (trace_frame < 0)
    {
        char v[16];
        trace_frame = GetEnvironmentVariableA("CODFH_TRACE", v, sizeof(v)) ? atoi(v) : 0;
    }
    return trace_frame && port_frame == (unsigned)trace_frame;
}
static void trace_flush(void)
{
    if (trace_draws && port_trace_on())
        plog("  trace: %u draws", trace_draws);
    trace_draws = 0;
}
void port_trace_draw(void)
{
    if (port_trace_on())
        trace_draws++;
}

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

/* Xbox Direct3D's state after device creation (the driver sets most of it again itself). */
static void default_states(void)
{
    static const float one = 1.0f, zero = 0.0f;
    DWORD f1, f0;
    memcpy(&f1, &one, 4);
    memcpy(&f0, &zero, 4);
    memset(D3D__RenderState, 0, sizeof(D3D__RenderState));
    D3D__RenderState[D3DRS_ZENABLE] = 1;
    D3D__RenderState[D3DRS_ZWRITEENABLE] = 1;
    D3D__RenderState[D3DRS_ZFUNC] = D3DCMP_LESSEQUAL;
    D3D__RenderState[D3DRS_ALPHAFUNC] = D3DCMP_ALWAYS;
    D3D__RenderState[D3DRS_SRCBLEND] = D3DBLEND_ONE;
    D3D__RenderState[D3DRS_DESTBLEND] = D3DBLEND_ZERO;
    D3D__RenderState[D3DRS_BLENDOP] = 0x8006;   /* ADD */
    D3D__RenderState[D3DRS_COLORWRITEENABLE] = D3DCOLORWRITEENABLE_ALL;
    D3D__RenderState[D3DRS_CULLMODE] = D3DCULL_CCW;
    D3D__RenderState[D3DRS_FRONTFACE] = 0x900;  /* CW */
    D3D__RenderState[D3DRS_FILLMODE] = 0x1B02;  /* SOLID */
    D3D__RenderState[D3DRS_BACKFILLMODE] = 0x1B02;
    D3D__RenderState[D3DRS_SHADEMODE] = D3DSHADE_GOURAUD;
    D3D__RenderState[D3DRS_STENCILFUNC] = D3DCMP_ALWAYS;
    D3D__RenderState[D3DRS_STENCILMASK] = 0xFF;
    D3D__RenderState[D3DRS_STENCILWRITEMASK] = 0xFF;
    D3D__RenderState[D3DRS_STENCILFAIL] = D3DSTENCILOP_KEEP;
    D3D__RenderState[D3DRS_STENCILZFAIL] = D3DSTENCILOP_KEEP;
    D3D__RenderState[D3DRS_STENCILPASS] = D3DSTENCILOP_KEEP;
    D3D__RenderState[D3DRS_LIGHTING] = 1;
    D3D__RenderState[D3DRS_COLORVERTEX] = 1;
    D3D__RenderState[D3DRS_DIFFUSEMATERIALSOURCE] = D3DMCS_COLOR1;
    D3D__RenderState[D3DRS_SPECULARMATERIALSOURCE] = 2;   /* COLOR2 */
    D3D__RenderState[D3DRS_AMBIENTMATERIALSOURCE] = D3DMCS_MATERIAL;
    D3D__RenderState[D3DRS_EMISSIVEMATERIALSOURCE] = D3DMCS_MATERIAL;
    D3D__RenderState[D3DRS_FOGSTART] = f0;
    D3D__RenderState[D3DRS_FOGEND] = f1;
    D3D__RenderState[D3DRS_FOGDENSITY] = f1;
    D3D__RenderState[D3DRS_POINTSIZE] = f1;
    D3D__RenderState[D3DRS_TEXTUREFACTOR] = 0xFFFFFFFF;
    D3D__RenderState[D3DRS_MULTISAMPLEMASK] = 0xFFFFFFFF;
    D3D__RenderState[D3DRS_MULTISAMPLEANTIALIAS] = 1;
    memset(D3D__TextureState, 0, sizeof(D3D__TextureState));
    for (int st = 0; st < D3DTSS_MAXSTAGES; st++)
    {
        D3D__TextureState[st][D3DTSS_COLOROP] = st ? D3DTOP_DISABLE : D3DTOP_MODULATE;
        D3D__TextureState[st][D3DTSS_COLORARG1] = D3DTA_TEXTURE;
        D3D__TextureState[st][D3DTSS_COLORARG2] = D3DTA_CURRENT;
        D3D__TextureState[st][D3DTSS_ALPHAOP] = st ? D3DTOP_DISABLE : D3DTOP_SELECTARG1;
        D3D__TextureState[st][D3DTSS_ALPHAARG1] = D3DTA_TEXTURE;
        D3D__TextureState[st][D3DTSS_ALPHAARG2] = D3DTA_CURRENT;
        D3D__TextureState[st][D3DTSS_ADDRESSU] = D3DTADDRESS_WRAP;
        D3D__TextureState[st][D3DTSS_ADDRESSV] = D3DTADDRESS_WRAP;
        D3D__TextureState[st][D3DTSS_ADDRESSW] = D3DTADDRESS_WRAP;
        D3D__TextureState[st][D3DTSS_MAGFILTER] = D3DTEXF_POINT;
        D3D__TextureState[st][D3DTSS_MINFILTER] = D3DTEXF_POINT;
        D3D__TextureState[st][D3DTSS_MAXANISOTROPY] = 1;
        D3D__TextureState[st][D3DTSS_TEXCOORDINDEX] = st;
        D3D__TextureState[st][D3DTSS_RESULTARG] = D3DTA_CURRENT;
    }
    for (int i = 0; i < 8; i++)
    {
        memset(&xs.transforms[i], 0, sizeof(D3DMATRIX));
        for (int k = 0; k < 4; k++)
            xs.transforms[i].m[k][k] = 1.0f;
    }
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
#ifdef CODFH_DEDICATED
        plog("dedicated server: no display (the bridge runs headless)");
#else
        pdev_init(port_hwnd, FRAME_W, FRAME_H, port_config.windowed, port_config.vsync);
#endif
    }
    plog("CreateDevice: %ux%u format 0x%lX flags 0x%lX interval 0x%lX", pp->BackBufferWidth,
         pp->BackBufferHeight, pp->BackBufferFormat, pp->Flags, pp->FullScreen_PresentationInterval);
    surface_init(&back_buffer, pp->BackBufferFormat, FRAME_W, FRAME_H, 4);
    surface_init(&depth_buffer, pp->AutoDepthStencilFormat, FRAME_W, FRAME_H, 4);
    render_target = &back_buffer.xb;
    D3DVIEWPORT8 vp0 = {0, 0, FRAME_W, FRAME_H, 0.0f, 1.0f};
    xs.viewport = vp0;
    default_states();
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

extern "C" void port_cli_present(void);
extern "C" void port_profile_start(void);
extern "C" void port_profile_report(LONGLONG start, LONGLONG end);

/* The slow-frame log's clock: when the game's work on a frame began (after the last present). */
static int work_start_pending;
static LARGE_INTEGER *work_start_slot;
static void mark_work_start(void)
{
    if (work_start_slot)
        QueryPerformanceCounter(work_start_slot);
}

extern "C" HRESULT WINAPI IDirect3DDevice8_Present(D3DDevice *, const RECT *, const RECT *, void *, void *)
{
    if (port_trace_on())
    {
        trace_flush();
        plog("  trace: present");
    }
    port_frame++;
    xdraw_frame_stats();
    /* a frame whose work took over 25 ms (the pacing's wait left out), in the log with what it
       did that ordinary frames do not: shaders compiled, textures uploaded */
    {
        static LARGE_INTEGER qf, work_start;
        work_start_slot = &work_start;
        LARGE_INTEGER now;
        if (!qf.QuadPart)
        {
            QueryPerformanceFrequency(&qf);
            port_profile_start();
        }
        QueryPerformanceCounter(&now);
        long compiles = port_shader_compiles, uploads = port_texture_uploads;
        port_shader_compiles = port_texture_uploads = 0;
        if (work_start.QuadPart)
        {
            double ms = (now.QuadPart - work_start.QuadPart) * 1000.0 / qf.QuadPart;
            static unsigned told;
            if (ms > 25 && port_frame > 300 && told < 200)
            {
                told++;
                plog("slow frame %u: %.1f ms of work; %ld shaders compiled, %ld textures uploaded, %u draws", port_frame,
                     ms, compiles, uploads, port_render_stats.draws);
                port_profile_report(work_start.QuadPart, now.QuadPart);
            }
        }
        work_start_pending = 1;
    }
    if (back_buffer_written)
    {
        back_buffer_written = 0;
        if (back_buffer.bits)
            pdev_upload_frame(back_buffer.bits, back_buffer.pitch);
    }
    pdev_present();
    pace_frame();
    port_pump_messages();
    /* (the next frame's work starts now) */
    if (work_start_pending)
    {
        work_start_pending = 0;
        mark_work_start();
    }
    port_cli_present();
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
    if (port_trace_on())
    {
        trace_flush();
        plog("  trace: clear flags 0x%lX colour %08lX rects %lu (first %ld,%ld-%ld,%ld) viewport %lu,%lu %lux%lu", Flags,
             Color, Count, Count ? pRects[0].x1 : 0, Count ? pRects[0].y1 : 0, Count ? pRects[0].x2 : 0,
             Count ? pRects[0].y2 : 0, xs.viewport.X, xs.viewport.Y, xs.viewport.Width, xs.viewport.Height);
    }
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
    if (port_trace_on())
    {
        trace_flush();
        plog("  trace: render target %p (%s, size %08lX) depth %p", pRenderTarget,
             pRenderTarget == &back_buffer.xb ? "back buffer" : "other", pRenderTarget ? pRenderTarget->Size : 0, pNewZStencil);
    }
    if (pRenderTarget)
        render_target = pRenderTarget;
    depth_target = pNewZStencil;
    if (pRenderTarget != &back_buffer.xb)
        PORT_STUB();    /* W2.2: render-to-texture */
}

extern "C" void WINAPI D3DDevice_CopyRects(D3DSurface *a, const RECT *, UINT, D3DSurface *b, const POINT *)
{
    if (port_trace_on())
    {
        trace_flush();
        plog("  trace: copy rects %p -> %p", a, b);
    }
    PORT_STUB();        /* W2.2 */
}

extern "C" void WINAPI D3DDevice_SetViewport(const D3DVIEWPORT8 *v)
{
    if (port_trace_on() && memcmp(v, &xs.viewport, sizeof(*v)))
    {
        trace_flush();
        plog("  trace: viewport %lu,%lu %lux%lu z %g-%g", v->X, v->Y, v->Width, v->Height, v->MinZ, v->MaxZ);
    }
    xs.viewport = *v;
    if (render_target == &back_buffer.xb)
        pdev_set_viewport(v->X, v->Y, v->Width, v->Height, v->MinZ, v->MaxZ);
}

extern "C" void WINAPI D3DDevice_GetViewportOffsetAndScale(D3DVECTOR4 *pOffset, D3DVECTOR4 *pScale)
{
    /* The Xbox's screen-space transform for vertex shaders: clip space to pixels, with the
       Xbox's 24-bit Z scale. */
    pScale->x = xs.viewport.Width * 0.5f;
    pScale->y = -(float)xs.viewport.Height * 0.5f;
    pScale->z = (xs.viewport.MaxZ - xs.viewport.MinZ) * 16777215.0f;
    pScale->w = 1.0f;
    pOffset->x = xs.viewport.X + xs.viewport.Width * 0.5f;
    pOffset->y = xs.viewport.Y + xs.viewport.Height * 0.5f;
    pOffset->z = xs.viewport.MinZ * 16777215.0f;
    pOffset->w = 0.0f;
}

/* The same, as plain floats for the draws (xdraw.cpp). */
extern "C" void port_viewport_offset_scale(float *offset, float *scale)
{
    D3DVECTOR4 o, sc;
    D3DDevice_GetViewportOffsetAndScale(&o, &sc);
    offset[0] = o.x; offset[1] = o.y; offset[2] = o.z; offset[3] = o.w;
    scale[0] = sc.x; scale[1] = sc.y; scale[2] = sc.z; scale[3] = sc.w;
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

extern "C" void WINAPI D3DDevice_SetTransform(D3DTRANSFORMSTATETYPE State, const D3DMATRIX *pMatrix)
{
    if (State < 8)
        xs.transforms[State] = *pMatrix;
}

extern "C" void WINAPI D3DDevice_SetMaterial(const D3DMATERIAL8 *pMaterial)
{
    xs.material = *pMaterial;
}

extern "C" HRESULT WINAPI D3DDevice_SetLight(DWORD Index, const D3DLIGHT8 *pLight)
{
    if (Index < 8)
        xs.lights[Index] = *pLight;
    return D3D_OK;
}

extern "C" HRESULT WINAPI D3DDevice_LightEnable(DWORD Index, BOOL Enable)
{
    if (Index < 8)
        xs.lightOn[Index] = Enable;
    return D3D_OK;
}

extern "C" void WINAPI D3DDevice_SetTexture(DWORD Stage, D3DBaseTexture *pTexture)
{
    if (Stage < 4)
        xs.textures[Stage] = pTexture;
}

extern "C" void WINAPI D3DDevice_SetPalette(DWORD Stage, D3DPalette *pPalette)
{
    if (Stage < 4)
        xs.palettes[Stage] = pPalette;
}

extern "C" void WINAPI D3DDevice_SetVertexDataColor(INT Register, D3DCOLOR Color)
{
    /* (the immediate-mode attribute: used where the declaration lacks the register) */
    if (Register >= 0 && Register < 16)
        xs.vertexDataColor[Register] = Color;
}

/*
 * Shaders (W2.4, W2.5)
 */

extern "C" HRESULT WINAPI D3DDevice_CreateVertexShader(const DWORD *pDeclaration, const DWORD *pFunction,
                                                       DWORD *pHandle, DWORD)
{
    XVertexShader *s = xdraw_create_vs(pDeclaration, pFunction);
    /* (bit 0 set: the Xbox tells shader handles from FVF codes by it) */
    *pHandle = (DWORD)(ULONG_PTR)s | 1;
    return D3D_OK;
}

extern "C" void WINAPI D3DDevice_DeleteVertexShader(DWORD Handle)
{
    XVertexShader *s = (XVertexShader *)(ULONG_PTR)(Handle & ~1u);
    if (!(Handle & 1) || !s)
        return;
    if (xs.programmable == s)
        xs.programmable = NULL;
    free((void *)s->program);
    free(s);
}

extern "C" void WINAPI D3DDevice_SetVertexShader(DWORD Handle)
{
    xs.vertexShader = Handle;
    xs.programmable = (Handle & 1) ? (XVertexShader *)(ULONG_PTR)(Handle & ~1u) : NULL;
}

extern "C" void WINAPI D3DDevice_LoadVertexShaderProgram(const DWORD *pFunction, DWORD Address)
{
    if (Address < 192)
        xs.loadedPrograms[Address] = pFunction;
}

extern "C" void WINAPI D3DDevice_SelectVertexShader(DWORD Handle, DWORD Address)
{
    D3DDevice_SetVertexShader(Handle);
    /* a declaration-only handle runs the program loaded at Address */
    if (xs.programmable && Address < 192 && xs.loadedPrograms[Address] &&
        xs.programmable->program != xs.loadedPrograms[Address])
    {
        XVertexShader *s = xs.programmable;
        if (!s->program || s->programIsText != -1)
        {
            free((void *)s->program);
            s->program = xs.loadedPrograms[Address];
            s->programIsText = -1;  /* borrowed: the caller's memory */
            s->device = NULL;
            s->failed = 0;
        }
    }
}

extern "C" void WINAPI D3DDevice_SetShaderConstantMode(D3DSHADERCONSTANTMODE Mode)
{
    xs.shaderConstantMode = Mode;
}

extern "C" void WINAPI D3DDevice_SetVertexShaderConstant(INT Register, const void *pConstantData, DWORD ConstantCount)
{
    /* (registers are -96..95 in the Xbox's 192-constant mode) */
    int r = Register + 96;
    if (r < 0 || r + (int)ConstantCount > 192)
        return;
    memcpy(xs.vsConstants[r], pConstantData, ConstantCount * 16);
}

extern "C" void WINAPI D3DDevice_SetVertexShaderConstantFast(INT Register, const void *pConstantData,
                                                             DWORD ConstantCount)
{
    D3DDevice_SetVertexShaderConstant(Register, pConstantData, ConstantCount);
}

/* Pixel shaders (W2.5): the definition kept; the draws translate it. */
extern "C" void WINAPI D3DDevice_CreatePixelShader(const D3DPIXELSHADERDEF *pPSDef, DWORD *pHandle)
{
    void *copy = malloc(60 * 4);
    memcpy(copy, pPSDef, 60 * 4);
    *pHandle = (DWORD)(ULONG_PTR)copy;
}

extern "C" void WINAPI D3DDevice_DeletePixelShader(DWORD Handle)
{
    if (xs.pixelShader == Handle)
        xs.pixelShader = 0;
    free((void *)(ULONG_PTR)Handle);
}

extern "C" void WINAPI D3DDevice_SetPixelShader(DWORD Handle)
{
    xs.pixelShader = Handle;
}

extern "C" void WINAPI D3DDevice_SetPixelShaderConstant(DWORD Register, const void *pConstantData, DWORD ConstantCount)
{
    if (Register + ConstantCount <= 16)
        memcpy(xs.psConstants[Register], pConstantData, ConstantCount * 16);
}

/*
 * Drawing (W2.3, W2.8)
 */

extern "C" void WINAPI D3DDevice_SetStreamSource(UINT StreamNumber, D3DVertexBuffer *pStreamData, UINT Stride)
{
    if (StreamNumber < 16)
    {
        xs.streams[StreamNumber] = pStreamData;
        xs.strides[StreamNumber] = Stride;
    }
}

extern "C" void WINAPI D3DDevice_DrawVertices(D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT VertexCount)
{
    xdraw_vertices(PrimitiveType, StartVertex, VertexCount);
}

extern "C" void WINAPI D3DDevice_DrawIndexedVertices(D3DPRIMITIVETYPE PrimitiveType, UINT VertexCount,
                                                     const WORD *pIndexData)
{
    xdraw_indexed(PrimitiveType, VertexCount, pIndexData);
}

extern "C" void WINAPI D3DDevice_DrawVerticesUP(D3DPRIMITIVETYPE PrimitiveType, UINT VertexCount,
                                                const void *pVertexStreamZeroData, UINT VertexStreamZeroStride)
{
    xdraw_up(PrimitiveType, VertexCount, pVertexStreamZeroData, VertexStreamZeroStride);
}


/*
 * Push buffers (W2.7): the NV2A method words the driver writes itself (the no-light submit, the
 * sprites, the device's overlay quad, the skin constants), decoded when they end.
 */

static std::vector<DWORD> push_buf;

extern "C" DWORD *WINAPI D3DDevice_BeginPush(DWORD Count)
{
    push_buf.resize(Count + 16);
    return &push_buf[0];
}

static void push_decode(const DWORD *p, const DWORD *end)
{
    static DWORD prim;
    static std::vector<DWORD> verts;
    static int load;
    while (p < end)
    {
        DWORD w = *p++;
        DWORD count = (w >> 18) & 0x7FF;
        DWORD method = w & 0x3FFFC;
        if (p + count > end)
            break;
        switch (method)
        {
        case D3DPUSH_SET_BEGIN_END:
            if (count && p[0])
            {
                prim = p[0];
                verts.clear();
            }
            else if (prim && !verts.empty())
            {
                xdraw_inline((D3DPRIMITIVETYPE)prim, &verts[0], (UINT)verts.size());
                prim = 0;
            }
            break;
        case D3DPUSH_INLINE_ARRAY:
            verts.insert(verts.end(), p, p + count);
            break;
        case D3DPUSH_SET_TRANSFORM_CONSTANT_LOAD:
            if (count)
                load = (int)p[0];
            break;
        case D3DPUSH_SET_TRANSFORM_CONSTANT:
            for (DWORD i = 0; i < count; i++, load += (i % 4 == 0))
                if (load >= 0 && load < 192)
                    memcpy(&xs.vsConstants[load][i % 4], &p[i], 4);
            break;
        default:
        {
            static DWORD logged[32];
            static int n;
            int seen = 0;
            for (int i = 0; i < n; i++)
                seen |= logged[i] == method;
            if (!seen && n < 32)
            {
                logged[n++] = method;
                plog("push buffer: method 0x%04lX (%lu words) not decoded", method, count);
            }
        }
        }
        p += count;
    }
}

extern "C" void WINAPI D3DDevice_EndPush(DWORD *pPush)
{
    if (!push_buf.empty())
        push_decode(&push_buf[0], pPush);
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
    /* (the bridge's own surfaces live as long as the device; a texture's device copy goes when
       its last reference does) */
    if (pThis && (pThis->Common & XB_COMMON_REFCOUNT_MASK))
    {
        pThis->Common--;
        if (!(pThis->Common & XB_COMMON_REFCOUNT_MASK))
            xdraw_texture_forget(pThis);
    }
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
        if (pThis == &back_buffer.xb)
            back_buffer_written = 1;
        return;
    }
    /* a surface over the driver's own memory: its rows as the Xbox lays them out */
    pLockedRect->pBits = (void *)(pThis->Data | 0x80000000);
    pLockedRect->Pitch = (INT)((((pThis->Size >> XB_SIZE_PITCH_SHIFT) & 0xFF) + 1) * 64);
}

extern "C" void WINAPI D3DSurface_UnlockRect(D3DSurface *pThis)
{
    if (pThis && pThis->Parent)
        xdraw_texture_dirty(pThis->Parent);
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

extern "C" void WINAPI D3DTexture_UnlockRect(D3DTexture *pThis, UINT)
{
    /* (the texture is uploaded again when next drawn with) */
    xdraw_texture_dirty(pThis);
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

extern "C" void WINAPI D3DPalette_Unlock(D3DPalette *pThis)
{
    xdraw_texture_dirty(pThis);
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
