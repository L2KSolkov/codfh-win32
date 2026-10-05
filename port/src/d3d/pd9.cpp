/*
 * The D3D bridge's Direct3D 9 side (docs/WIN32_PORT.md W2.1): the device, frames and the
 * presentation. The game draws a 640x480 frame (the Xbox's mode); the back buffer is that size
 * and Present stretches it to the window's client area.
 */
#include <d3d9.h>
#include <string.h>

#include "../port.h"
#include "pd9.h"

static IDirect3D9 *d3d;
static IDirect3DDevice9 *dev;
static D3DPRESENT_PARAMETERS pp;
static int in_scene;
static HWND hwnd_;
static int retry_width, retry_height, retry_vsync;

static void fill_present(int width, int height, int windowed, int vsync)
{
    memset(&pp, 0, sizeof(pp));
    pp.BackBufferWidth = width;
    pp.BackBufferHeight = height;
    pp.BackBufferFormat = D3DFMT_X8R8G8B8;
    pp.BackBufferCount = 1;
    pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    pp.hDeviceWindow = hwnd_;
    pp.Windowed = TRUE;     /* fullscreen: a borderless window over the screen (WinMain) */
    pp.EnableAutoDepthStencil = TRUE;
    pp.AutoDepthStencilFormat = D3DFMT_D24S8;
    pp.PresentationInterval = vsync ? D3DPRESENT_INTERVAL_ONE : D3DPRESENT_INTERVAL_IMMEDIATE;
    (void)windowed;
}

extern "C" int pd9_init(void *hwnd, int width, int height, int windowed, int vsync)
{
    hwnd_ = (HWND)hwnd;
    d3d = Direct3DCreate9(D3D_SDK_VERSION);
    if (!d3d)
    {
        plog("Direct3DCreate9 failed");
        return 0;
    }
    retry_width = width;
    retry_height = height;
    retry_vsync = vsync;
    static const DWORD tries[] = {
        D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_FPU_PRESERVE | D3DCREATE_MULTITHREADED,
        D3DCREATE_MIXED_VERTEXPROCESSING | D3DCREATE_FPU_PRESERVE | D3DCREATE_MULTITHREADED,
        D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_FPU_PRESERVE | D3DCREATE_MULTITHREADED,
    };
    HRESULT hr = E_FAIL;
    for (int i = 0; i < 3 && FAILED(hr); i++)
    {
        fill_present(width, height, windowed, vsync);
        hr = d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd_, tries[i], &pp, &dev);
        if (FAILED(hr))
            plog("CreateDevice (behaviour 0x%lX, window %p %s) failed: 0x%08lX", tries[i], hwnd_,
                 IsWindow(hwnd_) ? "valid" : "invalid", hr);
    }
    if (FAILED(hr))
    {
        /* (no device, as in a Remote Desktop session without a display: the game runs headless;
           pd9_present retries now and then) */
        plog("no Direct3D 9 device: running headless");
        return 1;
    }
    plog("Direct3D 9 device: %dx%d back buffer", width, height);
    return 1;
}

extern "C" void pd9_shutdown(void)
{
    if (dev)
        dev->Release();
    if (d3d)
        d3d->Release();
    dev = NULL;
    d3d = NULL;
}

extern "C" int pd9_ready(void)
{
    return d3d != NULL;
}

extern "C" void pd9_clear(unsigned flags, unsigned color, float z, unsigned stencil)
{
    if (dev)
        dev->Clear(0, NULL, flags, color, z, stencil);
}

extern "C" void pd9_begin_scene(void)
{
    if (dev && !in_scene && SUCCEEDED(dev->BeginScene()))
        in_scene = 1;
}

extern "C" void pd9_end_scene(void)
{
    if (dev && in_scene)
    {
        dev->EndScene();
        in_scene = 0;
    }
}

static void retry_device(void)
{
    static DWORD last;
    DWORD now = GetTickCount();
    if (now - last < 5000)
        return;
    last = now;
    fill_present(retry_width, retry_height, 1, retry_vsync);
    if (SUCCEEDED(d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd_,
                                    D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_FPU_PRESERVE |
                                        D3DCREATE_MULTITHREADED,
                                    &pp, &dev)))
        plog("Direct3D 9 device created (late)");
}

extern "C" void pd9_present(void)
{
    if (!dev)
    {
        if (d3d)
            retry_device();
        return;
    }
    pd9_end_scene();
    HRESULT hr = dev->Present(NULL, NULL, NULL, NULL);
    if (hr == D3DERR_DEVICELOST)
    {
        /* (W2.1: resources are recreated on reset; until then, wait for the device) */
        if (dev->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
            dev->Reset(&pp);
    }
}

extern "C" void pd9_set_viewport(unsigned x, unsigned y, unsigned w, unsigned h, float minz, float maxz)
{
    if (!dev)
        return;
    D3DVIEWPORT9 vp = {x, y, w, h, minz, maxz};
    dev->SetViewport(&vp);
}

extern "C" void pd9_set_gamma(const unsigned char *red, const unsigned char *green, const unsigned char *blue)
{
    if (!dev)
        return;
    D3DGAMMARAMP ramp;
    for (int i = 0; i < 256; i++)
    {
        ramp.red[i] = (WORD)(red[i] * 257);
        ramp.green[i] = (WORD)(green[i] * 257);
        ramp.blue[i] = (WORD)(blue[i] * 257);
    }
    dev->SetGammaRamp(0, D3DSGR_NO_CALIBRATION, &ramp);
}
