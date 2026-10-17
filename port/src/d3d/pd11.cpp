/*
 * The D3D bridge's device back end on Direct3D 11 (docs/WIN32_PORT.md W2.1): the device (the
 * GPU, or WARP when there is none, as over Remote Desktop), the swap chain, the depth buffer,
 * clears and presentation. The game draws a 640x480 frame (the Xbox's mode) into an offscreen
 * target; presenting copies it to the swap chain through the game's gamma ramp (the Xbox applies
 * the ramp in the display hardware; a windowed swap chain has none). The target is the frame times
 * the render scale ([video] render_scale; by default as large as the window holds): the game's
 * coordinates stay 640x480 and only the device's viewports are scaled, so everything it draws
 * comes out at the larger size. The swap chain is the
 * window's size; the frame keeps its 4:3 shape in it (black bars), or fills it with [video]
 * widescreen (the game told it is 16:9) or [video] fill (the 4:3 frame stretched; the overlay's
 * Renderer switch).
 */
#include <d3d11.h>
#include <d3dcompiler.h>
#include <dxgi1_6.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../port.h"
#include "pdev.h"
#include "pd11.h"
extern "C" int port_log_verbose;   /* (xpal_core.cpp: -verbose, the diagnostics' lines) */

ID3D11Device *pd11_dev;
ID3D11DeviceContext *pd11_ctx;
#define dev pd11_dev
#define ctx pd11_ctx
static IDXGISwapChain *swap;
static ID3D11RenderTargetView *rtv;          /* the game's frame (scene) */
static ID3D11RenderTargetView *back_rtv;     /* the swap chain's buffer */
static ID3D11Texture2D *scene;
static ID3D11ShaderResourceView *scene_srv;
static ID3D11DepthStencilView *dsv;
static ID3D11Texture2D *depth;
static int frame_w, frame_h, sync_interval, fill_window;
static float display_hz;

/* The refresh rate of the monitor the window is on (0 unknown). */
static float window_refresh(void *hwnd)
{
    HMONITOR mon = MonitorFromWindow((HWND)hwnd, MONITOR_DEFAULTTONEAREST);
    MONITORINFOEXA mi;
    memset(&mi, 0, sizeof(mi));
    mi.cbSize = sizeof(mi);
    if (!GetMonitorInfoA(mon, &mi))
        return 0;
    DEVMODEA dm;
    memset(&dm, 0, sizeof(dm));
    dm.dmSize = sizeof(dm);
    if (!EnumDisplaySettingsA(mi.szDevice, ENUM_CURRENT_SETTINGS, &dm))
        return 0;
    return (float)dm.dmDisplayFrequency;
}

/* The display paces the frames: vsync is on and the monitor refreshes about as often as the
   frame cap asks (the port's own timer, on a clock of its own, would drift against it and show
   a frame twice every so often). */
extern "C" int pdev_display_paces(int max_fps)
{
    return sync_interval && display_hz > 0 && max_fps > 0 && display_hz <= max_fps + 1.5f;
}
/* the target the frame is drawn into: frame_w x frame_h times render_scale */
static int target_w, target_h;
static float render_scale = 1.0f;
/* a movie's 640x480 frame (pdev_upload_frame), stretched over the target */
static ID3D11Texture2D *movie;
static ID3D11ShaderResourceView *movie_srv;
static ID3D11PixelShader *copy_ps;
static int back_w, back_h;
static void *the_hwnd;
static volatile LONG resize_pending;
static unsigned char gamma_ramp[3][256];
static int gamma_dirty;
static D3D11_VIEWPORT last_viewport;

/* The final pass: a triangle over the screen, the scene through the ramp (256x1, RGB). */
static ID3D11VertexShader *final_vs;
static ID3D11PixelShader *final_ps;
static ID3D11Texture2D *ramp;
static ID3D11ShaderResourceView *ramp_srv;
static ID3D11SamplerState *final_point, *final_linear;
static ID3D11RasterizerState *final_raster;
static ID3D11DepthStencilState *final_depth;
static ID3D11BlendState *final_blend;

static const char final_hlsl[] =
    "Texture2D scene : register(t0); Texture2D ramp : register(t1);\n"
    "SamplerState pt : register(s0); SamplerState lin : register(s1);\n"
    "struct V { float4 pos : SV_Position; float2 uv : TEXCOORD0; };\n"
    "V vs(uint id : SV_VertexID) {\n"
    "    V o; float2 t = float2((id << 1) & 2, id & 2);\n"
    "    o.pos = float4(t * float2(2, -2) + float2(-1, 1), 0, 1); o.uv = t; return o; }\n"
    "float4 ps(V i) : SV_Target {\n"
    "    float4 c = scene.Sample(lin, i.uv);\n"
    "    float3 idx = floor(saturate(c.rgb) * 255 + 0.5) / 256 + 1.0 / 512;\n"
    "    return float4(ramp.Sample(pt, float2(idx.r, 0.5)).r, ramp.Sample(pt, float2(idx.g, 0.5)).g,\n"
    "                  ramp.Sample(pt, float2(idx.b, 0.5)).b, 1); }\n"
    "float4 copy(V i) : SV_Target { return float4(scene.Sample(lin, i.uv).rgb, 1); }\n";

static void *compile(const char *entry, const char *target)
{
    ID3DBlob *code = NULL, *errors = NULL;
    HRESULT hr = D3DCompile(final_hlsl, sizeof(final_hlsl) - 1, "final", NULL, NULL, entry, target,
                            D3DCOMPILE_OPTIMIZATION_LEVEL3, 0, &code, &errors);
    if (errors)
    {
        plog("final pass %s: %s", entry, (const char *)errors->GetBufferPointer());
        errors->Release();
    }
    if (FAILED(hr))
        return NULL;
    void *out = NULL;
    if (target[0] == 'v')
        dev->CreateVertexShader(code->GetBufferPointer(), code->GetBufferSize(), NULL, (ID3D11VertexShader **)&out);
    else
        dev->CreatePixelShader(code->GetBufferPointer(), code->GetBufferSize(), NULL, (ID3D11PixelShader **)&out);
    code->Release();
    return out;
}

static int create_final_pass(void)
{
    final_vs = (ID3D11VertexShader *)compile("vs", "vs_4_0");
    final_ps = (ID3D11PixelShader *)compile("ps", "ps_4_0");
    copy_ps = (ID3D11PixelShader *)compile("copy", "ps_4_0");
    if (!final_vs || !final_ps || !copy_ps)
        return 0;
    D3D11_TEXTURE2D_DESC td;
    memset(&td, 0, sizeof(td));
    td.Width = 256;
    td.Height = 1;
    td.MipLevels = 1;
    td.ArraySize = 1;
    td.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    td.SampleDesc.Count = 1;
    td.Usage = D3D11_USAGE_DEFAULT;
    td.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    if (FAILED(dev->CreateTexture2D(&td, NULL, &ramp)) || FAILED(dev->CreateShaderResourceView(ramp, NULL, &ramp_srv)))
        return 0;
    for (int i = 0; i < 256; i++)
        gamma_ramp[0][i] = gamma_ramp[1][i] = gamma_ramp[2][i] = (unsigned char)i;
    gamma_dirty = 1;
    D3D11_SAMPLER_DESC sd;
    memset(&sd, 0, sizeof(sd));
    sd.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
    sd.AddressU = sd.AddressV = sd.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
    sd.MaxLOD = D3D11_FLOAT32_MAX;
    if (FAILED(dev->CreateSamplerState(&sd, &final_point)))
        return 0;
    sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    if (FAILED(dev->CreateSamplerState(&sd, &final_linear)))
        return 0;
    D3D11_RASTERIZER_DESC rd;
    memset(&rd, 0, sizeof(rd));
    rd.FillMode = D3D11_FILL_SOLID;
    rd.CullMode = D3D11_CULL_NONE;
    rd.DepthClipEnable = TRUE;
    D3D11_DEPTH_STENCIL_DESC dd;
    memset(&dd, 0, sizeof(dd));
    D3D11_BLEND_DESC bd;
    memset(&bd, 0, sizeof(bd));
    bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    return SUCCEEDED(dev->CreateRasterizerState(&rd, &final_raster)) &&
           SUCCEEDED(dev->CreateDepthStencilState(&dd, &final_depth)) && SUCCEEDED(dev->CreateBlendState(&bd, &final_blend));
}

static void final_pass(void)
{
    /* (the overlay's no-gamma switch: an identity ramp while it is on) */
    static int gamma_off;
    if (port_render_debug.noGamma != gamma_off)
    {
        gamma_off = port_render_debug.noGamma;
        gamma_dirty = 1;
    }
    if (gamma_dirty)
    {
        unsigned char px[256][4];
        for (int i = 0; i < 256; i++)
        {
            px[i][0] = gamma_off ? (unsigned char)i : gamma_ramp[0][i];
            px[i][1] = gamma_off ? (unsigned char)i : gamma_ramp[1][i];
            px[i][2] = gamma_off ? (unsigned char)i : gamma_ramp[2][i];
            px[i][3] = 255;
        }
        ctx->UpdateSubresource(ramp, 0, NULL, px, sizeof(px), 0);
        gamma_dirty = 0;
    }
    ID3D11ShaderResourceView *none[4] = {NULL, NULL, NULL, NULL};
    ctx->OMSetRenderTargets(1, &back_rtv, NULL);
    float bars[4] = {0, 0, 0, 1};
    ctx->ClearRenderTargetView(back_rtv, bars);
    /* the frame's 4:3 in the window, centred; or the whole window ([video] fill, widescreen) */
    float w = (float)back_w, h = (float)back_h, x = 0, y = 0;
    if (!fill_window && !port_config.fill)
    {
        if (w * frame_h > h * frame_w)
        {
            w = h * frame_w / frame_h;
            x = (back_w - w) / 2;
        }
        else
        {
            h = w * frame_h / frame_w;
            y = (back_h - h) / 2;
        }
    }
    D3D11_VIEWPORT vp = {x, y, w, h, 0, 1};
    ctx->RSSetViewports(1, &vp);
    ctx->IASetInputLayout(NULL);
    ctx->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    ctx->VSSetShader(final_vs, NULL, 0);
    ctx->PSSetShader(final_ps, NULL, 0);
    ID3D11ShaderResourceView *srv[2] = {scene_srv, ramp_srv};
    ctx->PSSetShaderResources(0, 2, srv);
    ID3D11SamplerState *smp[2] = {final_point, final_linear};
    ctx->PSSetSamplers(0, 2, smp);
    ctx->RSSetState(final_raster);
    ctx->OMSetDepthStencilState(final_depth, 0);
    float zero[4] = {0, 0, 0, 0};
    ctx->OMSetBlendState(final_blend, zero, 0xFFFFFFFF);
    ctx->Draw(3, 0);
    ctx->PSSetShaderResources(0, 4, none);
}

static int create_views(void)
{
    ID3D11Texture2D *back = NULL;
    if (FAILED(swap->GetBuffer(0, __uuidof(ID3D11Texture2D), (void **)&back)))
        return 0;
    HRESULT hr = dev->CreateRenderTargetView(back, NULL, &back_rtv);
    back->Release();
    if (FAILED(hr))
        return 0;
    D3D11_TEXTURE2D_DESC td;
    memset(&td, 0, sizeof(td));
    td.Width = target_w;
    td.Height = target_h;
    td.MipLevels = 1;
    td.ArraySize = 1;
    td.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    td.SampleDesc.Count = 1;
    td.Usage = D3D11_USAGE_DEFAULT;
    td.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
    if (FAILED(dev->CreateTexture2D(&td, NULL, &scene)) || FAILED(dev->CreateRenderTargetView(scene, NULL, &rtv)) ||
        FAILED(dev->CreateShaderResourceView(scene, NULL, &scene_srv)) || !create_final_pass())
        return 0;
    memset(&td, 0, sizeof(td));
    td.Width = target_w;
    td.Height = target_h;
    td.MipLevels = 1;
    td.ArraySize = 1;
    td.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    td.SampleDesc.Count = 1;
    td.Usage = D3D11_USAGE_DEFAULT;
    td.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    if (FAILED(dev->CreateTexture2D(&td, NULL, &depth)) || FAILED(dev->CreateDepthStencilView(depth, NULL, &dsv)))
        return 0;
    ctx->OMSetRenderTargets(1, &rtv, dsv);
    pdev_set_viewport(0, 0, frame_w, frame_h, 0.0f, 1.0f);
    return 1;
}

static void client_size(void *hwnd, int *w, int *h)
{
    RECT r;
    GetClientRect((HWND)hwnd, &r);
    *w = r.right - r.left > 0 ? r.right - r.left : 1;
    *h = r.bottom - r.top > 0 ? r.bottom - r.top : 1;
}

/* The adapters, logged; the one named by [video] adapter, else the high-performance one. */
static IDXGIAdapter1 *pick_adapter(void)
{
    IDXGIFactory6 *f6 = NULL;
    IDXGIFactory1 *f1 = NULL;
    if (FAILED(CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void **)&f1)))
        return NULL;
    f1->QueryInterface(__uuidof(IDXGIFactory6), (void **)&f6);
    IDXGIAdapter1 *chosen = NULL, *a = NULL;
    for (UINT i = 0;; i++)
    {
        HRESULT hr = f6 ? f6->EnumAdapterByGpuPreference(i, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, __uuidof(IDXGIAdapter1),
                                                         (void **)&a)
                        : f1->EnumAdapters1(i, &a);
        if (FAILED(hr))
            break;
        DXGI_ADAPTER_DESC1 ad;
        a->GetDesc1(&ad);
        char name[128];
        WideCharToMultiByte(CP_UTF8, 0, ad.Description, -1, name, sizeof(name), NULL, NULL);
        int software = (ad.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) != 0;
        plog("adapter %u: %s, %u MB%s", i, name, (unsigned)(ad.DedicatedVideoMemory >> 20), software ? " (software)" : "");
        int want = 0;
        if (port_config.adapter[0])
        {
            /* (a case-blind part of the name) */
            char lname[128], lwant[64];
            strncpy(lname, name, sizeof(lname));
            lname[sizeof(lname) - 1] = 0;
            strncpy(lwant, port_config.adapter, sizeof(lwant));
            lwant[sizeof(lwant) - 1] = 0;
            _strlwr(lname);
            _strlwr(lwant);
            want = strstr(lname, lwant) != NULL;
        }
        else
            want = !software;   /* the first in high-performance order */
        if (want && !chosen)
        {
            chosen = a;
            continue;
        }
        a->Release();
    }
    if (f6)
        f6->Release();
    f1->Release();
    if (port_config.adapter[0] && !chosen)
        plog("adapter: none named \"%s\" ([video] adapter): the default", port_config.adapter);
    return chosen;
}

extern "C" int pdev_init(void *hwnd, int width, int height, int windowed, int vsync)
{
    frame_w = width;
    frame_h = height;
    sync_interval = vsync ? 1 : 0;
    fill_window = port_config.widescreen;
    the_hwnd = hwnd;
    (void)windowed;
    client_size(hwnd, &back_w, &back_h);
    /* the render scale: configured, or the largest the window holds (whole and half steps are
       not needed: the final pass filters) */
    render_scale = port_config.renderScale;
    if (render_scale <= 0)
    {
        float sx = (float)back_w / width, sy = (float)back_h / height;
        render_scale = sx < sy ? sx : sy;
    }
    if (render_scale < 1)
        render_scale = 1;
    if (render_scale > 4)
        render_scale = 4;
    target_w = (int)(width * render_scale + 0.5f);
    target_h = (int)(height * render_scale + 0.5f);

    DXGI_SWAP_CHAIN_DESC sd;
    memset(&sd, 0, sizeof(sd));
    sd.BufferDesc.Width = back_w;
    sd.BufferDesc.Height = back_h;
    sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    sd.SampleDesc.Count = 1;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    /* the flip model (the compositor shows the buffers rather than copying them: steadier frame
       timing in a window), two buffers */
    sd.BufferCount = 2;
    sd.OutputWindow = (HWND)hwnd;
    sd.Windowed = TRUE;     /* fullscreen: a borderless window over the screen (WinMain) */
    sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

    /* the adapter: [video] adapter (a part of its name), else the high-performance one (a
       discrete GPU over an integrated one, as Windows' graphics settings rank them) */
    IDXGIAdapter1 *adapter = pick_adapter();
    static char gpu_name[128] = "the GPU";
    if (adapter)
    {
        DXGI_ADAPTER_DESC1 ad;
        adapter->GetDesc1(&ad);
        WideCharToMultiByte(CP_UTF8, 0, ad.Description, -1, gpu_name, sizeof(gpu_name), NULL, NULL);
    }
    static const D3D_DRIVER_TYPE drivers[] = {D3D_DRIVER_TYPE_HARDWARE, D3D_DRIVER_TYPE_WARP};
    const char *const names[] = {gpu_name, "WARP"};
    static const D3D_FEATURE_LEVEL levels[] = {D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0};
    for (int i = 0; i < 2; i++)
    {
        D3D_FEATURE_LEVEL got;
        /* (an adapter given needs the driver type UNKNOWN) */
        IDXGIAdapter *use = i == 0 ? adapter : NULL;
        HRESULT hr = D3D11CreateDeviceAndSwapChain(use, use ? D3D_DRIVER_TYPE_UNKNOWN : drivers[i], NULL,
                                                   D3D11_CREATE_DEVICE_BGRA_SUPPORT, levels, 3, D3D11_SDK_VERSION, &sd,
                                                   &swap, &dev, &got, &ctx);
        if (adapter && i == 0)
        {
            adapter->Release();
            adapter = NULL;
        }
        if (SUCCEEDED(hr) && create_views())
        {
            plog("Direct3D 11 on %s (feature level %X): %dx%d frame drawn at %dx%d (scale %.2f) in a %dx%d window",
                 names[i], got, width, height, target_w, target_h, render_scale, back_w, back_h);
            /* one frame queued ahead at most (smoother, and the input closer to the picture) */
            IDXGIDevice1 *dxdev = NULL;
            if (SUCCEEDED(dev->QueryInterface(__uuidof(IDXGIDevice1), (void **)&dxdev)))
            {
                dxdev->SetMaximumFrameLatency(1);
                dxdev->Release();
            }
            display_hz = window_refresh(hwnd);
            plog("display: %.2f Hz, vsync %s", display_hz, sync_interval ? "on" : "off");
#ifdef CODFH_IMGUI
            pdev_imgui_init(hwnd, names[i]);
#endif
            /* (Alt+Enter stays the window's: fullscreen is WinMain's borderless window) */
            IDXGIFactory *f = NULL;
            if (SUCCEEDED(swap->GetParent(__uuidof(IDXGIFactory), (void **)&f)))
            {
                f->MakeWindowAssociation((HWND)hwnd, DXGI_MWA_NO_ALT_ENTER);
                f->Release();
            }
            return 1;
        }
        plog("Direct3D 11 on %s failed (0x%08lX)", names[i], hr);
        pdev_shutdown();
    }
    plog("no Direct3D device: running headless");
    return 0;
}

extern "C" void pdev_shutdown(void)
{
#ifdef CODFH_IMGUI
    pdev_imgui_shutdown();
#endif
    if (ctx)
        ctx->ClearState();
    if (dsv) dsv->Release();
    if (depth) depth->Release();
    if (rtv) rtv->Release();
    if (back_rtv) back_rtv->Release();
    if (scene_srv) scene_srv->Release();
    if (scene) scene->Release();
    if (final_vs) final_vs->Release();
    if (copy_ps) copy_ps->Release();
    if (movie_srv) movie_srv->Release();
    if (movie) movie->Release();
    if (final_ps) final_ps->Release();
    if (ramp_srv) ramp_srv->Release();
    if (ramp) ramp->Release();
    if (final_point) final_point->Release();
    if (final_linear) final_linear->Release();
    if (final_raster) final_raster->Release();
    if (final_depth) final_depth->Release();
    if (final_blend) final_blend->Release();
    if (swap) swap->Release();
    if (ctx) ctx->Release();
    if (dev) dev->Release();
    dsv = NULL;
    depth = NULL;
    rtv = back_rtv = NULL;
    scene_srv = NULL;
    scene = NULL;
    final_vs = NULL;
    copy_ps = NULL;
    movie_srv = NULL;
    movie = NULL;
    final_ps = NULL;
    ramp_srv = NULL;
    ramp = NULL;
    final_point = final_linear = NULL;
    final_raster = NULL;
    final_depth = NULL;
    final_blend = NULL;
    swap = NULL;
    ctx = NULL;
    dev = NULL;
}

extern "C" int pdev_ready(void)
{
    return dev != NULL;
}

extern "C" void pdev_clear(unsigned flags, unsigned color, float z, unsigned stencil)
{
    if (!ctx)
        return;
    if ((flags & PDEV_CLEAR_TARGET) && rtv)
    {
        float c[4] = {((color >> 16) & 0xFF) / 255.0f, ((color >> 8) & 0xFF) / 255.0f, (color & 0xFF) / 255.0f,
                      ((color >> 24) & 0xFF) / 255.0f};
        ctx->ClearRenderTargetView(rtv, c);
    }
    UINT df = ((flags & PDEV_CLEAR_DEPTH) ? D3D11_CLEAR_DEPTH : 0) | ((flags & PDEV_CLEAR_STENCIL) ? D3D11_CLEAR_STENCIL : 0);
    if (df && dsv)
        ctx->ClearDepthStencilView(dsv, df, z, (UINT8)stencil);
}

extern "C" void pdev_begin_scene(void)
{
}

extern "C" void pdev_end_scene(void)
{
}

/* CODFH_SHOT=n: frame n written to shot.bmp beside the executable (and every n frames after
   with CODFH_SHOT_EVERY=1), for checking frames without watching them. */
static void capture(unsigned frame)
{
    static int shot = -1, every, from, to;
    if (shot < 0)
    {
        char v[32];
        shot = GetEnvironmentVariableA("CODFH_SHOT", v, sizeof(v)) ? atoi(v) : 0;
        every = GetEnvironmentVariableA("CODFH_SHOT_EVERY", v, sizeof(v)) ? atoi(v) : 0;
        /* (CODFH_SHOT_FROM / CODFH_SHOT_TO: the frames CODFH_SHOT_EVERY captures between) */
        from = GetEnvironmentVariableA("CODFH_SHOT_FROM", v, sizeof(v)) ? atoi(v) : 0;
        to = GetEnvironmentVariableA("CODFH_SHOT_TO", v, sizeof(v)) ? atoi(v) : 0;
    }
    if (!shot || (every ? frame % shot : frame != (unsigned)shot))
        return;
    if ((from && frame < (unsigned)from) || (to && frame > (unsigned)to))
        return;
    /* (the game's 640x480 frame, not the window's buffer, so captures compare across window sizes;
       CODFH_SHOT_WINDOW=1 takes the window's buffer instead) */
    static int window_shot = -1;
    if (window_shot < 0)
    {
        char v[8];
        window_shot = GetEnvironmentVariableA("CODFH_SHOT_WINDOW", v, sizeof(v)) ? 1 : 0;
    }
    ID3D11Texture2D *back = scene, *staging = NULL;
    if (!window_shot || FAILED(swap->GetBuffer(0, __uuidof(ID3D11Texture2D), (void **)&back)))
    {
        back = scene;
        back->AddRef();
    }
    D3D11_TEXTURE2D_DESC td;
    back->GetDesc(&td);
    td.Usage = D3D11_USAGE_STAGING;
    td.BindFlags = 0;
    td.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
    td.MiscFlags = 0;
    if (SUCCEEDED(dev->CreateTexture2D(&td, NULL, &staging)))
    {
        ctx->CopyResource(staging, back);
        D3D11_MAPPED_SUBRESOURCE m;
        if (SUCCEEDED(ctx->Map(staging, 0, D3D11_MAP_READ, 0, &m)))
        {
            char path[MAX_PATH];
            GetModuleFileNameA(NULL, path, MAX_PATH);
            char *slash = strrchr(path, '\\');
            if (every)
                sprintf(slash ? slash + 1 : path, "shot_%06u.bmp", frame);
            else
                strcpy(slash ? slash + 1 : path, "shot.bmp");
            FILE *f = fopen(path, "wb");
            if (f)
            {
                BITMAPFILEHEADER fh = {0x4D42, (DWORD)(54 + td.Width * td.Height * 4), 0, 0, 54};
                BITMAPINFOHEADER ih = {40, (LONG)td.Width, -(LONG)td.Height, 1, 32, BI_RGB};
                fwrite(&fh, sizeof(fh), 1, f);
                fwrite(&ih, sizeof(ih), 1, f);
                for (UINT y = 0; y < td.Height; y++)
                    fwrite((BYTE *)m.pData + y * m.RowPitch, 4, td.Width, f);
                fclose(f);
                plog("frame %u written to %s", frame, path);
            }
            ctx->Unmap(staging, 0);
        }
        staging->Release();
    }
    back->Release();
}

extern "C" void pdev_present(void)
{
    static unsigned frame;
    frame++;
    if (frame % 300 == 0 && port_log_verbose)
        plog("frame %u", frame);
    if (!swap)
        return;
    if (InterlockedExchange(&resize_pending, 0))
    {
        int w, h;
        client_size(the_hwnd, &w, &h);
        if (w != back_w || h != back_h)
        {
            ctx->OMSetRenderTargets(0, NULL, NULL);
            back_rtv->Release();
            back_rtv = NULL;
            if (SUCCEEDED(swap->ResizeBuffers(0, w, h, DXGI_FORMAT_UNKNOWN, 0)))
            {
                back_w = w;
                back_h = h;
            }
            ID3D11Texture2D *back = NULL;
            if (SUCCEEDED(swap->GetBuffer(0, __uuidof(ID3D11Texture2D), (void **)&back)))
            {
                dev->CreateRenderTargetView(back, NULL, &back_rtv);
                back->Release();
            }
            plog("window %dx%d", back_w, back_h);
        }
    }
    if (back_rtv)
    {
        final_pass();
#ifdef CODFH_IMGUI
        /* (over the finished frame, in the window's buffer: captures of the frame leave it out) */
        pdev_imgui_frame(back_w, back_h);
#endif
    }
    capture(frame);
    HRESULT hr = swap->Present(sync_interval, 0);
    if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
        plog("Direct3D 11 device lost (0x%08lX)", dev->GetDeviceRemovedReason());
    /* the game's target and viewport again */
    ctx->OMSetRenderTargets(1, &rtv, dsv);
    ctx->RSSetViewports(1, &last_viewport);
}

/* A position in the window's client area as a position in the 640x480 frame (where final_pass
   draws it); 0 outside the picture. */
extern "C" int pdev_window_to_frame(int x, int y, float *fx, float *fy)
{
    float w = (float)back_w, h = (float)back_h, ox = 0, oy = 0;
    if (!back_w || !back_h || !frame_w || !frame_h)
        return 0;
    if (!fill_window && !port_config.fill)
    {
        if (w * frame_h > h * frame_w)
        {
            w = h * frame_w / frame_h;
            ox = (back_w - w) / 2;
        }
        else
        {
            h = w * frame_h / frame_w;
            oy = (back_h - h) / 2;
        }
    }
    *fx = (x - ox) * frame_w / w;
    *fy = (y - oy) * frame_h / h;
    return *fx >= 0 && *fy >= 0 && *fx < frame_w && *fy < frame_h;
}

/* The window changed size: the swap chain follows at the next present (the game's thread). */
extern "C" void pdev_window_resized(void)
{
    InterlockedExchange(&resize_pending, 1);
}

extern "C" void pdev_upload_frame(const void *pixels, int pitch)
{
    if (!ctx || !rtv)
        return;
    if (!movie)
    {
        D3D11_TEXTURE2D_DESC td;
        memset(&td, 0, sizeof(td));
        td.Width = frame_w;
        td.Height = frame_h;
        td.MipLevels = 1;
        td.ArraySize = 1;
        td.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
        td.SampleDesc.Count = 1;
        td.Usage = D3D11_USAGE_DEFAULT;
        td.BindFlags = D3D11_BIND_SHADER_RESOURCE;
        if (FAILED(dev->CreateTexture2D(&td, NULL, &movie)) || FAILED(dev->CreateShaderResourceView(movie, NULL, &movie_srv)))
            return;
    }
    ctx->UpdateSubresource(movie, 0, NULL, pixels, pitch, 0);
    /* the 640x480 frame over the scaled target */
    ctx->OMSetRenderTargets(1, &rtv, NULL);
    D3D11_VIEWPORT vp = {0, 0, (float)target_w, (float)target_h, 0, 1};
    ctx->RSSetViewports(1, &vp);
    ctx->IASetInputLayout(NULL);
    ctx->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    ctx->VSSetShader(final_vs, NULL, 0);
    ctx->PSSetShader(copy_ps, NULL, 0);
    ctx->PSSetShaderResources(0, 1, &movie_srv);
    ID3D11SamplerState *smp[2] = {final_point, final_linear};
    ctx->PSSetSamplers(0, 2, smp);
    ctx->RSSetState(final_raster);
    ctx->OMSetDepthStencilState(final_depth, 0);
    float zero[4] = {0, 0, 0, 0};
    ctx->OMSetBlendState(final_blend, zero, 0xFFFFFFFF);
    ctx->Draw(3, 0);
    ID3D11ShaderResourceView *none = NULL;
    ctx->PSSetShaderResources(0, 1, &none);
    ctx->OMSetRenderTargets(1, &rtv, dsv);
    ctx->RSSetViewports(1, &last_viewport);
}

/* The target the frame is drawn into (the frame times the render scale). */
extern "C" void pdev_render_size(int *w, int *h)
{
    *w = target_w;
    *h = target_h;
}

extern "C" void pdev_set_viewport(unsigned x, unsigned y, unsigned w, unsigned h, float minz, float maxz)
{
    if (!ctx)
        return;
    /* (the game's 640x480 coordinates onto the scaled target) */
    D3D11_VIEWPORT vp = {x * render_scale, y * render_scale, w * render_scale, h * render_scale, minz, maxz};
    last_viewport = vp;
    ctx->RSSetViewports(1, &vp);
}

extern "C" void pdev_set_gamma(const unsigned char *red, const unsigned char *green, const unsigned char *blue)
{
    /* (applied by the frame's final pass, W2.9: a windowed swap chain has no hardware ramp) */
    if (!memcmp(gamma_ramp[0], red, 256) && !memcmp(gamma_ramp[1], green, 256) && !memcmp(gamma_ramp[2], blue, 256))
        return;
    memcpy(gamma_ramp[0], red, 256);
    memcpy(gamma_ramp[1], green, 256);
    memcpy(gamma_ramp[2], blue, 256);
    gamma_dirty = 1;
    plog("gamma ramp: 0 -> %u, 64 -> %u, 128 -> %u, 192 -> %u, 255 -> %u", green[0], green[64], green[128], green[192],
         green[255]);
}
