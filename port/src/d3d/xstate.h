/*
 * The D3D bridge's Xbox-side device state (docs/WIN32_PORT.md W2), shared by d3d8_bridge.cpp (the
 * API calls that set it) and xdraw.cpp (the draws that read it). Xbox names only.
 */
#ifndef PORT_XSTATE_H
#define PORT_XSTATE_H

#include <xtl.h>

/* A vertex declaration's element: where one register's data is and how it is stored. */
struct XVertexElement
{
    unsigned char stream, reg, type;
    unsigned short offset;
};

/* A vertex shader: its declaration, and its program (microcode, the assembler's text, or none
   for the fixed-function pipeline); the device's shader once translated. */
struct XVertexShader
{
    XVertexElement elements[16];
    int count;
    unsigned declared;          /* bit n: the declaration supplies vn */
    const DWORD *program;       /* microcode or text (copied); NULL: fixed function */
    int programIsText;
    float constants[192][4];    /* D3DVSD_CONST values from the declaration */
    unsigned constantMask[6];   /* which of them it set */
    void *device;               /* the device's shader (pdev) */
    int failed;
};

/* The fixed-function block of the vertex constant buffer (after the Xbox's 192). */
enum
{
    XFF_BASE = 192,
    XFF_WORLD = XFF_BASE + 0,       /* 4 rows each */
    XFF_VIEW = XFF_BASE + 4,
    XFF_PROJ = XFF_BASE + 8,
    XFF_TEX0 = XFF_BASE + 12,       /* 4 texture matrices */
    XFF_MATERIAL = XFF_BASE + 28,   /* diffuse, ambient, specular, emissive, (power) */
    XFF_AMBIENT = XFF_BASE + 33,
    XFF_FOG = XFF_BASE + 34,        /* start, end, density, table mode */
    XFF_VIEWPORT = XFF_BASE + 35,   /* pretransformed: offset; scale at +1 */
    XFF_LIGHTS = XFF_BASE + 40,     /* 8 lights, 8 rows each */
    XFF_COUNT = 128
};

struct XState
{
    float vsConstants[192 + XFF_COUNT][4];
    DWORD vertexShader;             /* a handle (bit 0 set) or an FVF code */
    XVertexShader *programmable;    /* the handle's shader, when it is one */
    const DWORD *loadedPrograms[192];   /* LoadVertexShaderProgram's, by address */
    DWORD pixelShader;
    D3DVertexBuffer *streams[16];
    UINT strides[16];
    D3DBaseTexture *textures[4];
    D3DPalette *palettes[4];
    D3DMATRIX transforms[8];
    D3DMATERIAL8 material;
    D3DLIGHT8 lights[8];
    BOOL lightOn[8];
    D3DVIEWPORT8 viewport;
    float psConstants[16][4];
    DWORD vertexDataColor[16];
};

extern XState xs;

/* xdraw.cpp */
void xdraw_vertices(D3DPRIMITIVETYPE prim, UINT start, UINT count);
void xdraw_indexed(D3DPRIMITIVETYPE prim, UINT count, const WORD *indices);
void xdraw_up(D3DPRIMITIVETYPE prim, UINT count, const void *data, UINT stride);
XVertexShader *xdraw_create_vs(const DWORD *decl, const DWORD *function);
void xdraw_texture_dirty(const void *header);
void xdraw_texture_forget(const void *header);

#endif
