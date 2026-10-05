/*
 * The D3D bridge's device back end on Direct3D 11 (docs/WIN32_PORT.md W2.1): the device (the
 * GPU, or WARP when there is none, as over Remote Desktop), the swap chain, the depth buffer,
 * clears and presentation. The game draws a 640x480 frame (the Xbox's mode) into an offscreen
 * target; presenting copies it to the swap chain through the game's gamma ramp (the Xbox applies
 * the ramp in the display hardware; a windowed swap chain has none), and DXGI stretches the
 * swap chain's buffer to the window.
 */
#include <d3d11.h>
#include <d3dcompiler.h>
#include <dxgi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../port.h"
#include "pdev.h"
#include "pd11.h"

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
static int frame_w, frame_h, sync_interval;
static unsigned char gamma_ramp[3][256];
static int gamma_dirty;
static D3D11_VIEWPORT last_viewport;

/* The final pass: a triangle over the screen, the scene through the ramp (256x1, RGB). */
static ID3D11VertexShader *final_vs;
static ID3D11PixelShader *final_ps;
static ID3D11Texture2D *ramp;
static ID3D11ShaderResourceView *ramp_srv;
static ID3D11SamplerState *final_point;
static ID3D11RasterizerState *final_raster;
static ID3D11DepthStencilState *final_depth;
static ID3D11BlendState *final_blend;

static const char final_hlsl[] =
    "Texture2D scene : register(t0); Texture2D ramp : register(t1); SamplerState pt : register(s0);\n"
    "struct V { float4 pos : SV_Position; float2 uv : TEXCOORD0; };\n"
    "V vs(uint id : SV_VertexID) {\n"
    "    V o; float2 t = float2((id << 1) & 2, id & 2);\n"
    "    o.pos = float4(t * float2(2, -2) + float2(-1, 1), 0, 1); o.uv = t; return o; }\n"
    "float4 ps(V i) : SV_Target {\n"
    "    float4 c = scene.Sample(pt, i.uv);\n"
    "    float3 idx = floor(saturate(c.rgb) * 255 + 0.5) / 256 + 1.0 / 512;\n"
    "    return float4(ramp.Sample(pt, float2(idx.r, 0.5)).r, ramp.Sample(pt, float2(idx.g, 0.5)).g,\n"
    "                  ramp.Sample(pt, float2(idx.b, 0.5)).b, 1); }\n";

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
    if (!final_vs || !final_ps)
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
    return SUCCEEDED(dev->CreateSamplerState(&sd, &final_point)) && SUCCEEDED(dev->CreateRasterizerState(&rd, &final_raster)) &&
           SUCCEEDED(dev->CreateDepthStencilState(&dd, &final_depth)) && SUCCEEDED(dev->CreateBlendState(&bd, &final_blend));
}

static void final_pass(void)
{
    if (gamma_dirty)
    {
        unsigned char px[256][4];
        for (int i = 0; i < 256; i++)
        {
            px[i][0] = gamma_ramp[0][i];
            px[i][1] = gamma_ramp[1][i];
            px[i][2] = gamma_ramp[2][i];
            px[i][3] = 255;
        }
        ctx->UpdateSubresource(ramp, 0, NULL, px, sizeof(px), 0);
        gamma_dirty = 0;
    }
    ID3D11ShaderResourceView *none[4] = {NULL, NULL, NULL, NULL};
    ctx->OMSetRenderTargets(1, &back_rtv, NULL);
    D3D11_VIEWPORT vp = {0, 0, (float)frame_w, (float)frame_h, 0, 1};
    ctx->RSSetViewports(1, &vp);
    ctx->IASetInputLayout(NULL);
    ctx->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    ctx->VSSetShader(final_vs, NULL, 0);
    ctx->PSSetShader(final_ps, NULL, 0);
    ID3D11ShaderResourceView *srv[2] = {scene_srv, ramp_srv};
    ctx->PSSetShaderResources(0, 2, srv);
    ctx->PSSetSamplers(0, 1, &final_point);
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
    td.Width = frame_w;
    td.Height = frame_h;
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
    td.Width = frame_w;
    td.Height = frame_h;
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

extern "C" int pdev_init(void *hwnd, int width, int height, int windowed, int vsync)
{
    frame_w = width;
    frame_h = height;
    sync_interval = vsync ? 1 : 0;
    (void)windowed;

    DXGI_SWAP_CHAIN_DESC sd;
    memset(&sd, 0, sizeof(sd));
    sd.BufferDesc.Width = width;
    sd.BufferDesc.Height = height;
    sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    sd.SampleDesc.Count = 1;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.BufferCount = 1;
    sd.OutputWindow = (HWND)hwnd;
    sd.Windowed = TRUE;     /* fullscreen: a borderless window over the screen (WinMain) */
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    static const D3D_DRIVER_TYPE drivers[] = {D3D_DRIVER_TYPE_HARDWARE, D3D_DRIVER_TYPE_WARP};
    static const char *const names[] = {"the GPU", "WARP"};
    static const D3D_FEATURE_LEVEL levels[] = {D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0};
    for (int i = 0; i < 2; i++)
    {
        D3D_FEATURE_LEVEL got;
        HRESULT hr = D3D11CreateDeviceAndSwapChain(NULL, drivers[i], NULL, D3D11_CREATE_DEVICE_BGRA_SUPPORT, levels, 3,
                                                   D3D11_SDK_VERSION, &sd, &swap, &dev, &got, &ctx);
        if (SUCCEEDED(hr) && create_views())
        {
            plog("Direct3D 11 on %s (feature level %X): %dx%d frame", names[i], got, width, height);
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
    if (ctx)
        ctx->ClearState();
    if (dsv) dsv->Release();
    if (depth) depth->Release();
    if (rtv) rtv->Release();
    if (back_rtv) back_rtv->Release();
    if (scene_srv) scene_srv->Release();
    if (scene) scene->Release();
    if (final_vs) final_vs->Release();
    if (final_ps) final_ps->Release();
    if (ramp_srv) ramp_srv->Release();
    if (ramp) ramp->Release();
    if (final_point) final_point->Release();
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
    final_ps = NULL;
    ramp_srv = NULL;
    ramp = NULL;
    final_point = NULL;
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
    static int shot = -1, every;
    if (shot < 0)
    {
        char v[32];
        shot = GetEnvironmentVariableA("CODFH_SHOT", v, sizeof(v)) ? atoi(v) : 0;
        every = GetEnvironmentVariableA("CODFH_SHOT_EVERY", v, sizeof(v)) ? atoi(v) : 0;
    }
    if (!shot || (every ? frame % shot : frame != (unsigned)shot))
        return;
    ID3D11Texture2D *back = NULL, *staging = NULL;
    if (FAILED(swap->GetBuffer(0, __uuidof(ID3D11Texture2D), (void **)&back)))
        return;
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
    if (frame % 300 == 0)
        plog("frame %u", frame);
    if (!swap)
        return;
    final_pass();
    capture(frame);
    HRESULT hr = swap->Present(sync_interval, 0);
    if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
        plog("Direct3D 11 device lost (0x%08lX)", dev->GetDeviceRemovedReason());
    /* the game's target and viewport again */
    ctx->OMSetRenderTargets(1, &rtv, dsv);
    ctx->RSSetViewports(1, &last_viewport);
}

extern "C" void pdev_set_viewport(unsigned x, unsigned y, unsigned w, unsigned h, float minz, float maxz)
{
    if (!ctx)
        return;
    D3D11_VIEWPORT vp = {(float)x, (float)y, (float)w, (float)h, minz, maxz};
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
