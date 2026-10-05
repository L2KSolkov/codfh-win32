/*
 * The D3D bridge's device back end on Direct3D 11 (docs/WIN32_PORT.md W2.1): the device (the
 * GPU, or WARP when there is none, as over Remote Desktop), the swap chain, the depth buffer,
 * clears and presentation. The game draws a 640x480 frame (the Xbox's mode); the swap chain's
 * buffers are that size and DXGI stretches them to the window.
 */
#include <d3d11.h>
#include <dxgi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../port.h"
#include "pdev.h"

static ID3D11Device *dev;
static ID3D11DeviceContext *ctx;
static IDXGISwapChain *swap;
static ID3D11RenderTargetView *rtv;
static ID3D11DepthStencilView *dsv;
static ID3D11Texture2D *depth;
static int frame_w, frame_h, sync_interval;
static unsigned char gamma_ramp[3][256];
static int gamma_set;

static int create_views(void)
{
    ID3D11Texture2D *back = NULL;
    if (FAILED(swap->GetBuffer(0, __uuidof(ID3D11Texture2D), (void **)&back)))
        return 0;
    HRESULT hr = dev->CreateRenderTargetView(back, NULL, &rtv);
    back->Release();
    if (FAILED(hr))
        return 0;
    D3D11_TEXTURE2D_DESC td;
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
    if (swap) swap->Release();
    if (ctx) ctx->Release();
    if (dev) dev->Release();
    dsv = NULL;
    depth = NULL;
    rtv = NULL;
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
    capture(frame);
    HRESULT hr = swap->Present(sync_interval, 0);
    if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
        plog("Direct3D 11 device lost (0x%08lX)", dev->GetDeviceRemovedReason());
    /* (DISCARD: the targets are bound again each frame) */
    ctx->OMSetRenderTargets(1, &rtv, dsv);
}

extern "C" void pdev_set_viewport(unsigned x, unsigned y, unsigned w, unsigned h, float minz, float maxz)
{
    if (!ctx)
        return;
    D3D11_VIEWPORT vp = {(float)x, (float)y, (float)w, (float)h, minz, maxz};
    ctx->RSSetViewports(1, &vp);
}

extern "C" void pdev_set_gamma(const unsigned char *red, const unsigned char *green, const unsigned char *blue)
{
    /* (applied by the frame's final pass, W2.9: a windowed swap chain has no hardware ramp) */
    memcpy(gamma_ramp[0], red, 256);
    memcpy(gamma_ramp[1], green, 256);
    memcpy(gamma_ramp[2], blue, 256);
    gamma_set = 1;
}
