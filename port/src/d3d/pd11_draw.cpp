/*
 * The Direct3D 11 back end's drawing (docs/WIN32_PORT.md W2.2-W2.6): shaders compiled from the
 * HLSL the Xbox side generates (cached by text), input layouts of float4 per vertex register,
 * ring-buffered dynamic vertex and index data, the Xbox constants as constant buffers, state
 * objects cached by their descriptions, and textures.
 */
#include <d3d11.h>
#include <d3dcompiler.h>

#include <map>
#include <unordered_map>
#include <string>
#include <string.h>

#include "../port.h"
#include "pdev.h"

volatile long port_shader_compiles, port_texture_uploads;
#include "pd11.h"

#define dev pd11_dev
#define ctx pd11_ctx

static ID3D11Buffer *vb, *ib, *cb_vs, *cb_vp, *cb_ps;
static const UINT vb_size = 16 << 20, ib_size = 2 << 20;
static UINT vb_pos, ib_pos;

static int ensure_buffers(void)
{
    if (vb)
        return 1;
    D3D11_BUFFER_DESC bd;
    memset(&bd, 0, sizeof(bd));
    bd.Usage = D3D11_USAGE_DYNAMIC;
    bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    bd.ByteWidth = vb_size;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    if (FAILED(dev->CreateBuffer(&bd, NULL, &vb)))
        return 0;
    bd.ByteWidth = ib_size;
    bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    if (FAILED(dev->CreateBuffer(&bd, NULL, &ib)))
        return 0;
    bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    bd.ByteWidth = 320 * 16;
    dev->CreateBuffer(&bd, NULL, &cb_vs);
    bd.ByteWidth = 32;
    dev->CreateBuffer(&bd, NULL, &cb_vp);
    bd.ByteWidth = 16 * 16;
    dev->CreateBuffer(&bd, NULL, &cb_ps);
    return cb_vs && cb_vp && cb_ps;
}

/* Appends data to a ring buffer: no-overwrite while it fits, discard when it wraps. */
static UINT ring_write(ID3D11Buffer *buf, UINT size, UINT *pos, const void *data, UINT bytes, UINT align)
{
    UINT at = (*pos + align - 1) / align * align;
    D3D11_MAP mode = D3D11_MAP_WRITE_NO_OVERWRITE;
    if (at + bytes > size)
    {
        at = 0;
        mode = D3D11_MAP_WRITE_DISCARD;
    }
    D3D11_MAPPED_SUBRESOURCE m;
    if (FAILED(ctx->Map(buf, 0, mode, 0, &m)))
        return 0xFFFFFFFF;
    memcpy((BYTE *)m.pData + at, data, bytes);
    ctx->Unmap(buf, 0);
    *pos = at + bytes;
    return at;
}

static void set_constants(ID3D11Buffer *buf, const void *data, UINT bytes)
{
    D3D11_MAPPED_SUBRESOURCE m;
    if (SUCCEEDED(ctx->Map(buf, 0, D3D11_MAP_WRITE_DISCARD, 0, &m)))
    {
        memcpy(m.pData, data, bytes);
        ctx->Unmap(buf, 0);
    }
}

/* FNV-1a, 64 bits. */
static unsigned long long fnv64(const void *data, size_t n, unsigned long long h = 0xCBF29CE484222325ull)
{
    const unsigned char *p = (const unsigned char *)data;
    for (size_t i = 0; i < n; i++)
        h = (h ^ p[i]) * 0x100000001B3ull;
    return h;
}

/*
 * Compiled shaders on disk (the user directory's shaders folder, a file per shader named by the
 * hash of its target and source): a shader compiles once, not at its first draw in every run,
 * where its 30 to 60 ms stall the frame.
 */
static void shader_path(const char *hlsl, const char *target, char *out, size_t n)
{
    unsigned long long h = fnv64(target, strlen(target));
    h = fnv64(hlsl, strlen(hlsl), h);
    _snprintf(out, n, "%s\\shaders\\%016llx.%s", port_config.userRoot, h, target);
    out[n - 1] = 0;
}

static ID3DBlob *cached(const char *path)
{
    HANDLE f = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
    if (f == INVALID_HANDLE_VALUE)
        return NULL;
    ID3DBlob *code = NULL;
    DWORD size = GetFileSize(f, NULL), got = 0;
    if (size && size < (16u << 20) && SUCCEEDED(D3DCreateBlob(size, &code)) &&
        !(ReadFile(f, code->GetBufferPointer(), size, &got, NULL) && got == size))
    {
        code->Release();
        code = NULL;
    }
    CloseHandle(f);
    return code;
}

static void store(const char *path, ID3DBlob *code)
{
    static int made;
    if (!made)
    {
        char dir[MAX_PATH];
        _snprintf(dir, sizeof(dir), "%s\\shaders", port_config.userRoot);
        dir[sizeof(dir) - 1] = 0;
        CreateDirectoryA(port_config.userRoot, NULL);
        CreateDirectoryA(dir, NULL);
        made = 1;
    }
    HANDLE f = CreateFileA(path, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
    if (f == INVALID_HANDLE_VALUE)
        return;
    DWORD put = 0;
    WriteFile(f, code->GetBufferPointer(), (DWORD)code->GetBufferSize(), &put, NULL);
    CloseHandle(f);
}

static ID3DBlob *compile(const char *hlsl, const char *target)
{
    char path[MAX_PATH];
    shader_path(hlsl, target, path, sizeof(path));
    if (ID3DBlob *code = cached(path))
        return code;
    ID3DBlob *code = NULL, *errors = NULL;
    port_shader_compiles++;
    HRESULT hr = D3DCompile(hlsl, strlen(hlsl), NULL, NULL, NULL, "main", target, D3DCOMPILE_OPTIMIZATION_LEVEL1, 0,
                            &code, &errors);
    if (FAILED(hr))
    {
        plog("shader compile failed (%s): %s", target, errors ? (const char *)errors->GetBufferPointer() : "?");
        plog("%s", hlsl);
    }
    if (errors)
        errors->Release();
    if (SUCCEEDED(hr))
        store(path, code);
    return SUCCEEDED(hr) ? code : NULL;
}

struct VSEntry
{
    ID3D11VertexShader *vs;
    ID3D11InputLayout *layout;
};
static std::map<std::string, VSEntry *> vs_cache;
static std::map<std::string, ID3D11PixelShader *> ps_cache;

extern "C" void *pdev_vertex_shader(const char *hlsl, const unsigned char *regs, int nregs)
{
    if (!dev)
        return NULL;
    std::string key(hlsl);
    key.append((const char *)regs, nregs);
    std::map<std::string, VSEntry *>::iterator it = vs_cache.find(key);
    if (it != vs_cache.end())
        return it->second;
    VSEntry *e = new VSEntry();
    e->vs = NULL;
    e->layout = NULL;
    ID3DBlob *code = compile(hlsl, "vs_4_0");
    if (code)
    {
        dev->CreateVertexShader(code->GetBufferPointer(), code->GetBufferSize(), NULL, &e->vs);
        D3D11_INPUT_ELEMENT_DESC el[16];
        int n = nregs < 16 ? nregs : 16;
        for (int k = 0; k < n; k++)
        {
            memset(&el[k], 0, sizeof(el[k]));
            el[k].SemanticName = "V";
            el[k].SemanticIndex = regs[k];
            el[k].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
            el[k].AlignedByteOffset = k * 16;
            el[k].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
        }
        if (n)
        {
            HRESULT hr = dev->CreateInputLayout(el, n, code->GetBufferPointer(), code->GetBufferSize(), &e->layout);
            if (FAILED(hr))
                plog("input layout failed (0x%08lX)", hr);
        }
        code->Release();
    }
    vs_cache[key] = e;
    return e;
}

extern "C" void *pdev_pixel_shader(const char *hlsl)
{
    if (!dev)
        return NULL;
    std::map<std::string, ID3D11PixelShader *>::iterator it = ps_cache.find(hlsl);
    if (it != ps_cache.end())
        return it->second;
    ID3D11PixelShader *ps = NULL;
    ID3DBlob *code = compile(hlsl, "ps_4_0");
    if (code)
    {
        dev->CreatePixelShader(code->GetBufferPointer(), code->GetBufferSize(), NULL, &ps);
        code->Release();
    }
    ps_cache[hlsl] = ps;
    return ps;
}

/*
 * Textures
 */

struct PTexture
{
    ID3D11Texture2D *tex;
    ID3D11ShaderResourceView *srv;
    int format, levels, cube;
};

extern "C" void *pdev_texture_create(int width, int height, int levels, int format, int cube)
{
    if (!dev)
        return NULL;
    static const DXGI_FORMAT fmts[] = {DXGI_FORMAT_B8G8R8A8_UNORM, DXGI_FORMAT_BC1_UNORM, DXGI_FORMAT_BC2_UNORM,
                                       DXGI_FORMAT_BC3_UNORM};
    D3D11_TEXTURE2D_DESC td;
    memset(&td, 0, sizeof(td));
    td.Width = width;
    td.Height = height;
    td.MipLevels = levels;
    td.ArraySize = cube ? 6 : 1;
    td.Format = fmts[format & 3];
    td.SampleDesc.Count = 1;
    td.Usage = D3D11_USAGE_DEFAULT;
    td.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    td.MiscFlags = cube ? D3D11_RESOURCE_MISC_TEXTURECUBE : 0;
    PTexture *t = new PTexture();
    t->tex = NULL;
    t->srv = NULL;
    t->format = format;
    t->levels = levels;
    t->cube = cube;
    if (FAILED(dev->CreateTexture2D(&td, NULL, &t->tex)) || FAILED(dev->CreateShaderResourceView(t->tex, NULL, &t->srv)))
    {
        plog("texture %dx%d (%d levels, format %d) failed", width, height, levels, format);
        if (t->tex)
            t->tex->Release();
        delete t;
        return NULL;
    }
    return t;
}

extern "C" void pdev_texture_upload(void *texture, int level, int face, const void *data, int pitch)
{
    PTexture *t = (PTexture *)texture;
    if (t && ctx)
        ctx->UpdateSubresource(t->tex, D3D11CalcSubresource(level, face, t->levels), NULL, data, pitch, 0);
}

extern "C" void pdev_texture_release(void *texture)
{
    PTexture *t = (PTexture *)texture;
    if (!t)
        return;
    t->srv->Release();
    t->tex->Release();
    delete t;
}

/*
 * State objects, cached by their descriptions
 */

/* The device's state objects by their descriptions: a hash of the bytes, the description kept
   to tell collisions apart (a string-keyed map was a measurable share of every draw). */
template <class D, class S> struct StateCache
{
    struct Entry
    {
        D desc;
        S *state;
    };
    std::unordered_multimap<unsigned long long, Entry> map;
    S *get(const D &d, HRESULT (STDMETHODCALLTYPE ID3D11Device::*create)(const D *, S **))
    {
        unsigned long long h = fnv64(&d, sizeof(d));
        typedef typename std::unordered_multimap<unsigned long long, Entry>::iterator It;
        std::pair<It, It> r = map.equal_range(h);
        for (It it = r.first; it != r.second; ++it)
            if (!memcmp(&it->second.desc, &d, sizeof(d)))
                return it->second.state;
        Entry e;
        e.desc = d;
        e.state = NULL;
        (dev->*create)(&d, &e.state);
        map.insert(std::make_pair(h, e));
        return e.state;
    }
};
static StateCache<D3D11_BLEND_DESC, ID3D11BlendState> blend_cache;
static StateCache<D3D11_DEPTH_STENCIL_DESC, ID3D11DepthStencilState> depth_cache;
static StateCache<D3D11_RASTERIZER_DESC, ID3D11RasterizerState> raster_cache;
static StateCache<D3D11_SAMPLER_DESC, ID3D11SamplerState> sampler_cache;

static D3D11_FILTER filter_of(const PDevSampler &s)
{
    if (s.filterMin == 2 || s.filterMag == 2)
        return D3D11_FILTER_ANISOTROPIC;
    int min = s.filterMin ? 1 : 0, mag = s.filterMag ? 1 : 0, mip = s.filterMip == 2 ? 1 : 0;
    return (D3D11_FILTER)((min << 4) | (mag << 2) | mip);
}

static void unpack_color(unsigned c, float *out)
{
    out[0] = ((c >> 16) & 0xFF) / 255.0f;
    out[1] = ((c >> 8) & 0xFF) / 255.0f;
    out[2] = (c & 0xFF) / 255.0f;
    out[3] = ((c >> 24) & 0xFF) / 255.0f;
}

static unsigned dropped;

extern "C" unsigned pdev_dropped(void)
{
    unsigned n = dropped;
    dropped = 0;
    return n;
}

extern "C" void pdev_draw(const PDevDraw *d)
{
    if (!dev || !d->vs || !d->ps || !ensure_buffers())
    {
        dropped++;
        return;
    }
    VSEntry *vse = (VSEntry *)d->vs;
    if (!vse->vs || (!vse->layout && d->stride))
    {
        static int told;
        if (!told++)
            plog("draw dropped: vertex shader %p, layout %p (stride %d)", vse->vs, vse->layout, d->stride);
        dropped++;
        return;
    }

    UINT stride = d->stride ? d->stride : 16;
    UINT vbytes = d->stride * d->vertexCount;
    UINT voff = 0;
    if (vbytes)
    {
        if (vbytes > vb_size)
        {
            dropped++;
            return;
        }
        voff = ring_write(vb, vb_size, &vb_pos, d->vertices, vbytes, stride);
        if (voff == 0xFFFFFFFF)
            return;
    }
    UINT ioff = 0;
    if (d->indices)
    {
        UINT ibytes = d->indexCount * 2;
        if (ibytes > ib_size)
            return;
        ioff = ring_write(ib, ib_size, &ib_pos, d->indices, ibytes, 2);
        if (ioff == 0xFFFFFFFF)
            return;
    }

    set_constants(cb_vs, d->vsConstants, 320 * 16);
    set_constants(cb_vp, d->viewport, 32);
    if (d->psConstants)
        set_constants(cb_ps, d->psConstants, 16 * 16);
    ID3D11Buffer *vsb[2] = {cb_vs, cb_vp};
    ctx->VSSetConstantBuffers(0, 2, vsb);
    ctx->PSSetConstantBuffers(0, 1, &cb_ps);
    ctx->VSSetShader(vse->vs, NULL, 0);
    ctx->PSSetShader((ID3D11PixelShader *)d->ps, NULL, 0);
    ctx->IASetInputLayout(vse->layout);
    UINT zero = 0;
    ctx->IASetVertexBuffers(0, 1, &vb, &stride, &zero);
    ctx->IASetPrimitiveTopology((D3D11_PRIMITIVE_TOPOLOGY)d->primitive);

    ID3D11ShaderResourceView *srv[4];
    ID3D11SamplerState *smp[4];
    for (int i = 0; i < 4; i++)
    {
        PTexture *t = (PTexture *)d->textures[i];
        srv[i] = t ? t->srv : NULL;
        D3D11_SAMPLER_DESC sd;
        memset(&sd, 0, sizeof(sd));
        const PDevSampler &s = d->samplers[i];
        sd.Filter = filter_of(s);
        sd.AddressU = (D3D11_TEXTURE_ADDRESS_MODE)(s.addressU ? s.addressU : 1);
        sd.AddressV = (D3D11_TEXTURE_ADDRESS_MODE)(s.addressV ? s.addressV : 1);
        sd.AddressW = (D3D11_TEXTURE_ADDRESS_MODE)(s.addressW ? s.addressW : 1);
        sd.MaxAnisotropy = s.maxAnisotropy ? (s.maxAnisotropy > 16 ? 16 : s.maxAnisotropy) : 1;
        sd.MipLODBias = s.lodBias;
        sd.ComparisonFunc = D3D11_COMPARISON_NEVER;
        unpack_color(s.border, sd.BorderColor);
        sd.MinLOD = 0;
        sd.MaxLOD = s.filterMip ? D3D11_FLOAT32_MAX : 0;
        smp[i] = sampler_cache.get(sd, &ID3D11Device::CreateSamplerState);
    }
    ctx->PSSetShaderResources(0, 4, srv);
    ctx->PSSetSamplers(0, 4, smp);

    D3D11_BLEND_DESC bd;
    memset(&bd, 0, sizeof(bd));
    D3D11_RENDER_TARGET_BLEND_DESC &rt = bd.RenderTarget[0];
    rt.BlendEnable = d->blendEnable;
    rt.SrcBlend = (D3D11_BLEND)(d->srcBlend ? d->srcBlend : D3D11_BLEND_ONE);
    rt.DestBlend = (D3D11_BLEND)(d->dstBlend ? d->dstBlend : D3D11_BLEND_ZERO);
    rt.BlendOp = (D3D11_BLEND_OP)(d->blendOp ? d->blendOp : D3D11_BLEND_OP_ADD);
    rt.SrcBlendAlpha = (D3D11_BLEND)(d->srcBlendAlpha ? d->srcBlendAlpha : D3D11_BLEND_ONE);
    rt.DestBlendAlpha = (D3D11_BLEND)(d->dstBlendAlpha ? d->dstBlendAlpha : D3D11_BLEND_ZERO);
    rt.BlendOpAlpha = (D3D11_BLEND_OP)(d->blendOpAlpha ? d->blendOpAlpha : D3D11_BLEND_OP_ADD);
    rt.RenderTargetWriteMask = d->writeMask;
    float factor[4];
    unpack_color(d->blendFactor, factor);
    ctx->OMSetBlendState(blend_cache.get(bd, &ID3D11Device::CreateBlendState), factor, 0xFFFFFFFF);

    D3D11_DEPTH_STENCIL_DESC dd;
    memset(&dd, 0, sizeof(dd));
    dd.DepthEnable = d->depthEnable;
    dd.DepthWriteMask = d->depthWrite ? D3D11_DEPTH_WRITE_MASK_ALL : D3D11_DEPTH_WRITE_MASK_ZERO;
    dd.DepthFunc = (D3D11_COMPARISON_FUNC)(d->depthFunc ? d->depthFunc : D3D11_COMPARISON_LESS_EQUAL);
    dd.StencilEnable = d->stencilEnable;
    dd.StencilReadMask = d->stencilReadMask;
    dd.StencilWriteMask = d->stencilWriteMask;
    dd.FrontFace.StencilFunc = (D3D11_COMPARISON_FUNC)(d->stencilFunc ? d->stencilFunc : D3D11_COMPARISON_ALWAYS);
    dd.FrontFace.StencilFailOp = (D3D11_STENCIL_OP)(d->stencilFail ? d->stencilFail : 1);
    dd.FrontFace.StencilDepthFailOp = (D3D11_STENCIL_OP)(d->stencilDepthFail ? d->stencilDepthFail : 1);
    dd.FrontFace.StencilPassOp = (D3D11_STENCIL_OP)(d->stencilPass ? d->stencilPass : 1);
    dd.BackFace = dd.FrontFace;
    ctx->OMSetDepthStencilState(depth_cache.get(dd, &ID3D11Device::CreateDepthStencilState), d->stencilRef);

    D3D11_RASTERIZER_DESC rd;
    memset(&rd, 0, sizeof(rd));
    rd.FillMode = d->wireframe ? D3D11_FILL_WIREFRAME : D3D11_FILL_SOLID;
    rd.CullMode = (D3D11_CULL_MODE)(d->cull ? d->cull : D3D11_CULL_NONE);
    rd.FrontCounterClockwise = d->frontCCW;
    rd.DepthBias = (INT)d->depthBias;
    rd.SlopeScaledDepthBias = d->slopeBias;
    rd.DepthClipEnable = TRUE;
    ctx->RSSetState(raster_cache.get(rd, &ID3D11Device::CreateRasterizerState));

    if (d->indices)
    {
        ctx->IASetIndexBuffer(ib, DXGI_FORMAT_R16_UINT, ioff);
        ctx->DrawIndexed(d->indexCount, 0, voff / stride);
    }
    else
        ctx->Draw(d->vertexCount, voff / stride);
}
