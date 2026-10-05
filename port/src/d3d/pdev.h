/*
 * The D3D bridge's device back end (docs/WIN32_PORT.md W2): what d3d8_bridge.cpp (the Xbox names)
 * asks of the PC's Direct3D, in plain C types. Only pd11.cpp includes d3d11.h; the Xbox and the PC
 * APIs share names with different values, so the two sides never meet in one file.
 *
 * The back end is Direct3D 11 (owner's decision, 2026-10-05: Direct3D 9 has no adapter over
 * Remote Desktop; Direct3D 11 runs on the GPU there, or on WARP).
 */
#ifndef PORT_PDEV_H
#define PORT_PDEV_H

#ifdef __cplusplus
extern "C" {
#endif

/* The device: the 640x480 frame the game draws, presented stretched to the window. Returns 0
   only when nothing can be created at all (the bridge then runs headless). */
int pdev_init(void *hwnd, int width, int height, int windowed, int vsync);
void pdev_shutdown(void);
int pdev_ready(void);

enum
{
    PDEV_CLEAR_TARGET = 1,
    PDEV_CLEAR_DEPTH = 2,
    PDEV_CLEAR_STENCIL = 4
};

/* Clears the current target (color is A8R8G8B8). */
void pdev_clear(unsigned flags, unsigned color, float z, unsigned stencil);
void pdev_begin_scene(void);
void pdev_end_scene(void);
void pdev_present(void);
void pdev_set_viewport(unsigned x, unsigned y, unsigned w, unsigned h, float minz, float maxz);
void pdev_set_gamma(const unsigned char *red, const unsigned char *green, const unsigned char *blue);
/* The frame replaced by CPU pixels (A8R8G8B8, the frame's size): what the game wrote into a
   locked back buffer (the movie player's blit). */
void pdev_upload_frame(const void *pixels, int pitch);

/*
 * Drawing. The Xbox side hands over vertices already converted to float4 per vertex register
 * (regs[k] is the register of the k-th float4), HLSL for both shaders, and the state in the
 * values below (Direct3D 11's own numbers, so the back end passes them through).
 */

/* Shaders: compiled once per text (the back end caches them); NULL when compilation fails. */
void *pdev_vertex_shader(const char *hlsl, const unsigned char *regs, int nregs);
void *pdev_pixel_shader(const char *hlsl);

/* Textures: 32-bit BGRA, or the compressed formats as they are. */
enum
{
    PDEV_TEX_BGRA8 = 0,
    PDEV_TEX_BC1 = 1,       /* DXT1 */
    PDEV_TEX_BC2 = 2,       /* DXT2/3 */
    PDEV_TEX_BC3 = 3        /* DXT4/5 */
};
void *pdev_texture_create(int width, int height, int levels, int format, int cube);
void pdev_texture_upload(void *texture, int level, int face, const void *data, int pitch);
void pdev_texture_release(void *texture);

/* Values: D3D11_BLEND, D3D11_BLEND_OP, D3D11_COMPARISON_FUNC, D3D11_STENCIL_OP, D3D11_FILTER
   pieces and D3D11_TEXTURE_ADDRESS_MODE numbers. */
typedef struct PDevSampler
{
    unsigned char filterMin, filterMag, filterMip;  /* 0 point, 1 linear, 2 anisotropic; mip 0 none */
    unsigned char addressU, addressV, addressW;     /* D3D11_TEXTURE_ADDRESS_MODE */
    unsigned char maxAnisotropy;
    unsigned char pad;
    unsigned border;                                /* A8R8G8B8 */
    float lodBias;
} PDevSampler;

enum
{
    PDEV_CULL_NONE = 1,     /* D3D11_CULL_MODE */
    PDEV_CULL_FRONT = 2,
    PDEV_CULL_BACK = 3
};

enum
{
    PDEV_PRIM_POINTS = 1,   /* D3D11_PRIMITIVE_TOPOLOGY */
    PDEV_PRIM_LINES = 2,
    PDEV_PRIM_LINESTRIP = 3,
    PDEV_PRIM_TRIANGLES = 4,
    PDEV_PRIM_TRISTRIP = 5
};

typedef struct PDevDraw
{
    void *vs, *ps;
    const float *vsConstants;   /* 320 float4: the Xbox's c[-96..95], then the fixed-function block */
    float viewport[8];          /* the screen-space offset and scale the shaders used */
    const float *psConstants;   /* 16 float4 */
    void *textures[4];
    PDevSampler samplers[4];

    unsigned char blendEnable, srcBlend, dstBlend, blendOp, srcBlendAlpha, dstBlendAlpha, blendOpAlpha;
    unsigned char writeMask;    /* D3D11_COLOR_WRITE_ENABLE bits */
    unsigned char depthEnable, depthWrite, depthFunc;
    unsigned char stencilEnable, stencilFunc, stencilFail, stencilDepthFail, stencilPass;
    unsigned char stencilRef, stencilReadMask, stencilWriteMask;
    unsigned char cull, frontCCW, wireframe;
    float depthBias, slopeBias;
    unsigned blendFactor;       /* A8R8G8B8 */

    int primitive;
    const void *vertices;       /* float4 per register, nregs per vertex */
    int stride;
    int vertexCount;
    const unsigned short *indices;
    int indexCount;
} PDevDraw;

void pdev_draw(const PDevDraw *draw);
/* Draws the device dropped since the last call. */
unsigned pdev_dropped(void);

#ifdef __cplusplus
}
#endif

#endif
