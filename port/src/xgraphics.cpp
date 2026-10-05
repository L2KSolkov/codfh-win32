/*
 * The XGraphics library for the port (docs/WIN32_PORT.md W2.2, W2.4): texture and palette
 * headers over memory the RenderWare driver allocates, the Xbox's swizzled texture layout, the
 * matrix helpers (XG and D3DX), and the run-time vertex shader assembly the skin pipeline uses.
 *
 * Texture headers follow the Xbox's format word: the DMA channel, cube flag, dimension, format,
 * mip count and log2 width/height (swizzled and compressed formats), or a Size word with width,
 * height and pitch (linear formats). Levels are stored largest first, each face of a cube map
 * padded to 128 bytes.
 */
#include <xtl.h>
#include <xgraphics.h>
#include <d3dx8.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "port.h"

/* Bits per pixel of an Xbox format code (0 unknown), and whether it is linear. */
static int fmt_bpp(DWORD f)
{
    switch (f)
    {
    case 0x00: case 0x01: case 0x0B: case 0x13: case 0x19: case 0x1B: case 0x1F:
        return 8;
    case 0x06: case 0x07: case 0x12: case 0x1E: case 0x2A: case 0x2B: case 0x2E: case 0x2F:
    case 0x33: case 0x36: case 0x3A: case 0x3B: case 0x3C: case 0x3F: case 0x40: case 0x41:
        return 32;
    case 0x0C:
        return 4;   /* DXT1 */
    case 0x0E: case 0x0F:
        return 8;   /* DXT2/3, DXT4/5 */
    default:
        return 16;
    }
}

static int fmt_dxt(DWORD f)
{
    return f == 0x0C || f == 0x0E || f == 0x0F;
}

extern "C" int port_xb_format_linear(DWORD f)
{
    switch (f)
    {
    case 0x10: case 0x11: case 0x12: case 0x13: case 0x16: case 0x17: case 0x1C: case 0x1D:
    case 0x1E: case 0x1F: case 0x20: case 0x24: case 0x25: case 0x2E: case 0x2F: case 0x30:
    case 0x31: case 0x35: case 0x36: case 0x37: case 0x3D: case 0x3E: case 0x3F: case 0x40:
    case 0x41:
        return 1;
    }
    return 0;
}

extern "C" int port_xb_format_bpp(DWORD f)
{
    return fmt_bpp(f);
}

static int log2i(UINT v)
{
    int n = 0;
    while ((1u << n) < v)
        n++;
    return n;
}

/* A level's size in bytes (compressed formats in 4x4 blocks). */
static DWORD level_bytes(DWORD fmt, int w, int h)
{
    if (fmt_dxt(fmt))
    {
        int bw = (w + 3) / 4, bh = (h + 3) / 4;
        return (DWORD)(bw * bh * (fmt == 0x0C ? 8 : 16));
    }
    return (DWORD)(w * h * fmt_bpp(fmt) / 8);
}

/* The level's offset in the texture's memory, its size and its pitch, from the header. */
extern "C" int port_xb_texture_level(const D3DBaseTexture *t, UINT level, int face, DWORD *offset, int *width,
                                     int *height, int *pitch)
{
    DWORD f = t->Format;
    DWORD fmt = (f >> 8) & 0xFF;
    if (port_xb_format_linear(fmt))
    {
        *width = (int)(t->Size & 0xFFF) + 1;
        *height = (int)((t->Size >> 12) & 0xFFF) + 1;
        *pitch = (int)(((t->Size >> 24) & 0xFF) + 1) * 64;
        *offset = 0;
        return 1;
    }
    int levels = (f >> 16) & 0xF;
    int w = 1 << ((f >> 20) & 0xF), h = 1 << ((f >> 24) & 0xF);
    if (levels < 1)
        levels = 1;
    DWORD off = 0;
    if (face)
    {
        DWORD faceSize = 0;
        int lw = w, lh = h;
        for (int i = 0; i < levels; i++)
        {
            faceSize += level_bytes(fmt, lw, lh);
            lw = lw > 1 ? lw / 2 : 1;
            lh = lh > 1 ? lh / 2 : 1;
        }
        off = ((faceSize + 127) & ~127u) * face;
    }
    for (UINT i = 0; i < level && (int)i < levels; i++)
    {
        off += level_bytes(fmt, w, h);
        w = w > 1 ? w / 2 : 1;
        h = h > 1 ? h / 2 : 1;
    }
    *offset = off;
    *width = w;
    *height = h;
    *pitch = fmt_dxt(fmt) ? ((w + 3) / 4) * (fmt == 0x0C ? 8 : 16) : w * fmt_bpp(fmt) / 8;
    return 1;
}

extern "C" DWORD WINAPI XGSetTextureHeader(UINT Width, UINT Height, UINT Levels, DWORD, D3DFORMAT Format,
                                           D3DPOOL, D3DTexture *pTexture, UINT Data, UINT Pitch)
{
    memset(pTexture, 0, sizeof(*pTexture));
    pTexture->Common = 1 | 0x00040000;  /* one reference; a texture */
    pTexture->Data = Data;
    if (port_xb_format_linear(Format))
    {
        if (!Pitch)
            Pitch = (Width * fmt_bpp(Format) / 8 + 63) & ~63u;
        pTexture->Format = 1 | (2 << 4) | (Format << 8) | (1 << 16);
        pTexture->Size = (Width - 1) | ((Height - 1) << 12) | ((Pitch / 64 - 1) << 24);
        return Pitch * Height;
    }
    int lw = log2i(Width), lh = log2i(Height);
    int maxLevels = (lw > lh ? lw : lh) + 1;
    if (!Levels || (int)Levels > maxLevels)
        Levels = maxLevels;
    pTexture->Format = 1 | (2 << 4) | (Format << 8) | (Levels << 16) | (lw << 20) | (lh << 24);
    DWORD size = 0;
    int w = 1 << lw, h = 1 << lh;
    for (UINT i = 0; i < Levels; i++)
    {
        size += level_bytes(Format, w, h);
        w = w > 1 ? w / 2 : 1;
        h = h > 1 ? h / 2 : 1;
    }
    return size;
}

extern "C" VOID WINAPI XGSetPaletteHeader(D3DPALETTESIZE Size, D3DPalette *pPalette, UINT Data)
{
    memset(pPalette, 0, sizeof(*pPalette));
    /* one reference, a palette, and its size code in the top bits (0 = 256 entries ... 3 = 32) */
    pPalette->Common = 1 | 0x00030000 | ((DWORD)Size << 30);
    pPalette->Data = Data;
}

/*
 * Swizzling: the Xbox stores swizzled textures with x and y address bits interleaved (x first),
 * up to the smaller dimension; the larger dimension's remaining bits follow.
 */
static void swizzle_masks(DWORD w, DWORD h, DWORD *mx, DWORD *my)
{
    DWORD x = 0, y = 0, bit = 1;
    for (DWORD i = 1, j = 1; i < w || j < h; i <<= 1, j <<= 1)
    {
        if (i < w)
        {
            x |= bit;
            bit <<= 1;
        }
        if (j < h)
        {
            y |= bit;
            bit <<= 1;
        }
    }
    *mx = x;
    *my = y;
}

/* The swizzled index of (u, v) from per-axis masks (bit deposit). */
static DWORD deposit(DWORD v, DWORD mask)
{
    DWORD r = 0;
    for (DWORD bit = 1; mask; bit <<= 1)
    {
        DWORD low = mask & (~mask + 1);
        if (v & bit)
            r |= low;
        mask &= mask - 1;
    }
    return r;
}

extern "C" VOID WINAPI XGSwizzleRect(LPCVOID pSource, DWORD Pitch, LPCRECT pRect, LPVOID pDest, DWORD Width,
                                     DWORD Height, const LPPOINT pPoint, DWORD BytesPerPixel)
{
    RECT all = {0, 0, (LONG)Width, (LONG)Height};
    const RECT *r = pRect ? pRect : &all;
    POINT origin = {0, 0};
    const POINT *at = pPoint ? pPoint : &origin;
    DWORD rw = r->right - r->left, rh = r->bottom - r->top;
    if (!Pitch)
        Pitch = rw * BytesPerPixel;
    DWORD mx, my;
    swizzle_masks(Width, Height, &mx, &my);
    for (DWORD y = 0; y < rh; y++)
    {
        const BYTE *src = (const BYTE *)pSource + (r->top + y) * Pitch + r->left * BytesPerPixel;
        DWORD sy = deposit(at->y + y, my);
        for (DWORD x = 0; x < rw; x++)
            memcpy((BYTE *)pDest + (deposit(at->x + x, mx) | sy) * BytesPerPixel, src + x * BytesPerPixel,
                   BytesPerPixel);
    }
}

extern "C" VOID WINAPI XGUnswizzleRect(LPCVOID pSource, DWORD Width, DWORD Height, LPCRECT pRect, LPVOID pDest,
                                       DWORD Pitch, const LPPOINT pPoint, DWORD BytesPerPixel)
{
    RECT all = {0, 0, (LONG)Width, (LONG)Height};
    const RECT *r = pRect ? pRect : &all;
    POINT origin = {0, 0};
    const POINT *at = pPoint ? pPoint : &origin;
    DWORD rw = r->right - r->left, rh = r->bottom - r->top;
    if (!Pitch)
        Pitch = Width * BytesPerPixel;
    DWORD mx, my;
    swizzle_masks(Width, Height, &mx, &my);
    for (DWORD y = 0; y < rh; y++)
    {
        BYTE *dst = (BYTE *)pDest + (at->y + y) * Pitch + at->x * BytesPerPixel;
        DWORD sy = deposit(r->top + y, my);
        for (DWORD x = 0; x < rw; x++)
            memcpy(dst + x * BytesPerPixel,
                   (const BYTE *)pSource + (deposit(r->left + x, mx) | sy) * BytesPerPixel, BytesPerPixel);
    }
}

/*
 * Matrices (row vectors, as Direct3D's)
 */

extern "C" XGMATRIX *WINAPI XGMatrixMultiply(XGMATRIX *pOut, const XGMATRIX *a, const XGMATRIX *b)
{
    D3DMATRIX r;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            r.m[i][j] = a->m[i][0] * b->m[0][j] + a->m[i][1] * b->m[1][j] + a->m[i][2] * b->m[2][j] +
                        a->m[i][3] * b->m[3][j];
    memcpy(pOut, &r, sizeof(r));
    return pOut;
}

extern "C" XGMATRIX *WINAPI XGMatrixTranspose(XGMATRIX *pOut, const XGMATRIX *pM)
{
    D3DMATRIX r;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            r.m[i][j] = pM->m[j][i];
    memcpy(pOut, &r, sizeof(r));
    return pOut;
}

extern "C" D3DXMATRIX *WINAPI D3DXMatrixMultiply(D3DXMATRIX *pOut, const D3DXMATRIX *a, const D3DXMATRIX *b)
{
    return (D3DXMATRIX *)XGMatrixMultiply((XGMATRIX *)pOut, (const XGMATRIX *)a, (const XGMATRIX *)b);
}

static void v_sub(float *r, const D3DXVECTOR3 *a, const D3DXVECTOR3 *b)
{
    r[0] = a->x - b->x;
    r[1] = a->y - b->y;
    r[2] = a->z - b->z;
}

static void v_norm(float *v)
{
    float l = sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    if (l > 0)
    {
        v[0] /= l;
        v[1] /= l;
        v[2] /= l;
    }
}

static void v_cross(float *r, const float *a, const float *b)
{
    r[0] = a[1] * b[2] - a[2] * b[1];
    r[1] = a[2] * b[0] - a[0] * b[2];
    r[2] = a[0] * b[1] - a[1] * b[0];
}

static float v_dot(const float *a, const D3DXVECTOR3 *b)
{
    return a[0] * b->x + a[1] * b->y + a[2] * b->z;
}

extern "C" D3DXMATRIX *WINAPI D3DXMatrixLookAtRH(D3DXMATRIX *pOut, const D3DXVECTOR3 *pEye, const D3DXVECTOR3 *pAt,
                                                 const D3DXVECTOR3 *pUp)
{
    float z[3], x[3], y[3], up[3] = {pUp->x, pUp->y, pUp->z};
    v_sub(z, pEye, pAt);    /* right-handed: z points from the target to the eye */
    v_norm(z);
    v_cross(x, up, z);
    v_norm(x);
    v_cross(y, z, x);
    float m[16] = {x[0], y[0], z[0], 0, x[1], y[1], z[1], 0, x[2], y[2], z[2], 0,
                   -v_dot(x, pEye), -v_dot(y, pEye), -v_dot(z, pEye), 1};
    memcpy(pOut->m, m, sizeof(m));
    return pOut;
}

extern "C" D3DXMATRIX *WINAPI D3DXMatrixPerspectiveFovRH(D3DXMATRIX *pOut, float fovy, float Aspect, float zn,
                                                         float zf)
{
    float ys = 1.0f / tanf(fovy * 0.5f), xs = ys / Aspect;
    float m[16] = {xs, 0, 0, 0, 0, ys, 0, 0, 0, 0, zf / (zn - zf), -1, 0, 0, zn * zf / (zn - zf), 0};
    memcpy(pOut->m, m, sizeof(m));
    return pOut;
}

/*
 * Run-time shader assembly (the skin pipeline's permutations): the buffers hold the shader text
 * the game generated; the bridge maps it to its HLSL replacement when the shader is created
 * (W2.4). Splicing joins the texts.
 */
struct XGBuffer
{
    DWORD size;
    BYTE data[1];
};

static XGBuffer *buffer_new(const void *p, DWORD n)
{
    XGBuffer *b = (XGBuffer *)calloc(1, sizeof(XGBuffer) + n + 4);
    b->size = n;
    if (p)
        memcpy(b->data, p, n);
    return b;
}

extern "C" LPVOID WINAPI XGBuffer_GetBufferPointer(XGBuffer *pThis)
{
    return pThis->data;
}

extern "C" ULONG WINAPI XGBuffer_Release(XGBuffer *pThis)
{
    free(pThis);
    return 0;
}

/* The marker a spliced or assembled "program" starts with: the text follows. */
#define PORT_SHADER_TEXT_TAG 0x54584554     /* 'TEXT' */

extern "C" HRESULT WINAPI XGAssembleShader(LPCSTR, LPCVOID pSrcData, UINT SrcDataLen, DWORD, LPXGBUFFER *pConstants,
                                           LPXGBUFFER *pCompiledShader, LPXGBUFFER *pErrorLog, LPXGBUFFER *pListing,
                                           SASM_ResolverCallback, LPVOID, LPDWORD pShaderType)
{
    DWORD hdr[2] = {PORT_SHADER_TEXT_TAG, SrcDataLen};
    XGBuffer *b = buffer_new(NULL, 8 + SrcDataLen + 1);
    memcpy(b->data, hdr, 8);
    memcpy(b->data + 8, pSrcData, SrcDataLen);
    if (pCompiledShader)
        *pCompiledShader = b;
    else
        XGBuffer_Release(b);
    if (pConstants)
        *pConstants = NULL;
    if (pErrorLog)
        *pErrorLog = NULL;
    if (pListing)
        *pListing = NULL;
    if (pShaderType)
        *pShaderType = 0;
    return S_OK;
}

extern "C" HRESULT WINAPI XGSpliceVertexShaders(DWORD *pNewShader, DWORD *pcbNewShaderBufferSize,
                                                DWORD *pNewInstructionCount, const DWORD *const *ppShaderArray,
                                                DWORD NumShaders, BOOL)
{
    /* the texts joined, after one tag and the total length */
    DWORD total = 0;
    for (DWORD i = 0; i < NumShaders; i++)
        if (ppShaderArray[i] && ppShaderArray[i][0] == PORT_SHADER_TEXT_TAG)
            total += ppShaderArray[i][1];
    if (pcbNewShaderBufferSize)
    {
        if (*pcbNewShaderBufferSize && *pcbNewShaderBufferSize < total + 8)
            return E_FAIL;
        *pcbNewShaderBufferSize = total + 8;
    }
    if (pNewInstructionCount)
        *pNewInstructionCount = 0;
    if (!pNewShader)
        return S_OK;
    pNewShader[0] = PORT_SHADER_TEXT_TAG;
    pNewShader[1] = total;
    BYTE *out = (BYTE *)(pNewShader + 2);
    for (DWORD i = 0; i < NumShaders; i++)
        if (ppShaderArray[i] && ppShaderArray[i][0] == PORT_SHADER_TEXT_TAG)
        {
            memcpy(out, ppShaderArray[i] + 2, ppShaderArray[i][1]);
            out += ppShaderArray[i][1];
        }
    return S_OK;
}
