/*
 * The D3D bridge's draws (docs/WIN32_PORT.md W2.2-W2.8): what an Xbox draw call means, built from
 * the bridge's Xbox state (xstate.h) and handed to the device back end (pdev.h).
 *
 * - Vertices: each declared register converted to float4 (every Xbox element type, NORMPACKED3
 *   expanded), the streams read from the driver's own memory.
 * - Vertex shaders: Xbox microcode translated (xvsh.cpp); the fixed-function pipeline (FVF codes,
 *   declarations without a program) generated: transforms, lights, material sources, texture
 *   coordinate generation and transforms, fog.
 * - Pixel shaders: generated from the four texture stages (all the Xbox's operations), alpha
 *   kill and test, specular add and fog. Xbox register-combiner shaders: W2.5 (stage 0 until then).
 * - State: the Xbox's render and texture-stage states to Direct3D 11's.
 * - Textures: decoded from the Xbox's memory (unswizzled; P8 through the bound palette; DXT as
 *   it is) when first drawn with or after a lock, and kept per header.
 * - Primitives: fans, quads, quad strips, polygons and line loops become lists.
 */
#include <xtl.h>
#include <xgraphics.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <map>
#include <string>
#include <vector>

#include "../port.h"
#include "pdev.h"
#include "xstate.h"
#include "xvsh.h"

extern "C" int port_xb_texture_level(const D3DBaseTexture *t, UINT level, int face, DWORD *offset, int *width,
                                     int *height, int *pitch);
extern "C" int port_xb_format_linear(DWORD f);
extern "C" int port_xb_format_bpp(DWORD f);

#define RS(n) D3D__RenderState[n]
#define TSS(s, n) D3D__TextureState[s][n]

/* Xbox values the declarations above do not name. */
enum
{
    XB_TEXT_TAG = 0x54584554,   /* xgraphics.cpp's assembled-text marker */
    XB_RS_ZBIAS_SCALE = 1,
    XB_BLENDOP_ADD = 0x8006
};

/* The attribute defaults the translated shaders read for undeclared registers (c[300 + n]). */
enum { XFF_DEFAULTS = 300 };

/*
 * Vertex declarations and shaders
 */

static int element_size(int type)
{
    int ctype = type & 0xF, count = type >> 4;
    if (type == 0x40)
        return 4;   /* D3DCOLOR */
    if (type == 0x16)
        return 4;   /* NORMPACKED3 */
    if (type == 0x72)
        return 12;  /* FLOAT2H */
    switch (ctype)
    {
    case 1: case 5: return 2 * count;   /* NORMSHORT, SHORT */
    case 2: return 4 * count;           /* FLOAT */
    case 4: return count;               /* PBYTE */
    }
    return 0;
}

static void parse_declaration(XVertexShader *s, const DWORD *decl)
{
    unsigned stream = 0;
    unsigned offsets[16] = {0};
    for (const DWORD *t = decl; t && *t != 0xFFFFFFFF; t++)
    {
        DWORD tok = *t;
        switch (tok >> 29)
        {
        case 1:     /* stream */
            stream = tok & 0xF;
            break;
        case 2:     /* stream data */
            if (tok & 0x10000000)
            {
                unsigned n = (tok >> 16) & 0xF;
                offsets[stream] += (tok & 0x08000000) ? n : n * 4;
            }
            else if (s->count < 16)
            {
                XVertexElement &e = s->elements[s->count++];
                e.stream = (unsigned char)stream;
                e.reg = (unsigned char)(tok & 0x1F);
                e.type = (unsigned char)((tok >> 16) & 0xFF);
                e.offset = (unsigned short)offsets[stream];
                offsets[stream] += element_size(e.type);
                s->declared |= 1u << e.reg;
            }
            break;
        case 4:     /* constants: count in bits 25-28, the Xbox register in 0-7 */
        {
            unsigned n = (tok >> 25) & 0xF, at = tok & 0xFF;
            for (unsigned i = 0; i < n && at + i < 192; i++)
            {
                memcpy(s->constants[at + i], t + 1 + i * 4, 16);
                s->constantMask[(at + i) / 32] |= 1u << ((at + i) % 32);
            }
            t += n * 4;
            break;
        }
        case 5:     /* extension data */
            t += (tok >> 24) & 0x1F;
            break;
        default:
            break;
        }
    }
}

XVertexShader *xdraw_create_vs(const DWORD *decl, const DWORD *function)
{
    XVertexShader *s = (XVertexShader *)calloc(1, sizeof(XVertexShader));
    parse_declaration(s, decl);
    if (function)
    {
        size_t bytes;
        if (function[0] == XB_TEXT_TAG)
        {
            bytes = 8 + function[1];
            s->programIsText = 1;
        }
        else
            bytes = (1 + ((function[0] >> 16) & 0xFF) * 4) * 4;
        s->program = (const DWORD *)malloc(bytes + 1);
        memcpy((void *)s->program, function, bytes);
        ((char *)s->program)[bytes] = 0;
    }
    return s;
}

/* An FVF code as a declaration (stream 0, in the FVF's order). */
static void fvf_declaration(DWORD fvf, XVertexShader *s, int *pretransformed)
{
    memset(s, 0, sizeof(*s));
    unsigned off = 0;
    *pretransformed = 0;
    XVertexElement *e;
#define ADD(r, t)                         \
    e = &s->elements[s->count++];         \
    e->stream = 0;                        \
    e->reg = r;                           \
    e->type = t;                          \
    e->offset = (unsigned short)off;      \
    off += element_size(t);               \
    s->declared |= 1u << (r)
    switch (fvf & 0xE)
    {
    case 0x2: ADD(0, 0x32); break;                      /* XYZ */
    case 0x4: ADD(0, 0x42); *pretransformed = 1; break; /* XYZRHW */
    default:
        if ((fvf & 0xE) >= 0x6)
        {
            ADD(0, 0x32);
            int weights = ((fvf & 0xE) - 0x4) / 2;      /* XYZB1..B4 */
            ADD(1, (unsigned char)(0x02 | (weights << 4)));
        }
    }
    if (fvf & 0x10) { ADD(2, 0x32); }           /* normal */
    if (fvf & 0x40) { ADD(3, 0x40); }           /* diffuse */
    if (fvf & 0x80) { ADD(4, 0x40); }           /* specular */
    unsigned tex = (fvf >> 8) & 0xF;
    for (unsigned i = 0; i < tex && i < 4; i++)
    {
        static const int counts[4] = {2, 3, 4, 1};
        int n = counts[(fvf >> (16 + i * 2)) & 3];
        ADD(9 + i, (unsigned char)(0x02 | (n << 4)));
    }
#undef ADD
}

/*
 * Vertex conversion
 */

static void convert_element(const BYTE *p, int type, float *out)
{
    out[0] = out[1] = out[2] = 0.0f;
    out[3] = 1.0f;
    int ctype = type & 0xF, count = type >> 4;
    if (type == 0x40)
    {
        DWORD c = *(const DWORD *)p;
        out[0] = ((c >> 16) & 0xFF) / 255.0f;
        out[1] = ((c >> 8) & 0xFF) / 255.0f;
        out[2] = (c & 0xFF) / 255.0f;
        out[3] = ((c >> 24) & 0xFF) / 255.0f;
        return;
    }
    if (type == 0x16)
    {
        DWORD v = *(const DWORD *)p;
        int x = (int)(v << 21) >> 21, y = (int)(v << 10) >> 21, z = (int)v >> 22;
        out[0] = x / 1023.0f;
        out[1] = y / 1023.0f;
        out[2] = z / 511.0f;
        return;
    }
    if (type == 0x72)
    {
        const float *f = (const float *)p;
        out[0] = f[0];
        out[1] = f[1];
        out[3] = f[2];
        return;
    }
    for (int i = 0; i < count && i < 4; i++)
        switch (ctype)
        {
        case 1: { float v = ((const short *)p)[i] / 32767.0f; out[i] = v < -1.0f ? -1.0f : v; break; }
        case 2: out[i] = ((const float *)p)[i]; break;
        case 4: out[i] = p[i] / 255.0f; break;
        case 5: out[i] = (float)((const short *)p)[i]; break;
        }
}

static std::vector<float> vtx;
static unsigned char vtx_regs[16];
static int vtx_nregs;

/* Converts vertices first..first+count-1 (streams, or the UP pointer as stream 0). */
static int convert_vertices(const XVertexShader *s, UINT first, UINT count, const BYTE *up, UINT upStride)
{
    vtx_nregs = s->count;
    for (int k = 0; k < s->count; k++)
        vtx_regs[k] = s->elements[k].reg;
    vtx.resize((size_t)count * s->count * 4 + 4);
    const BYTE *base[16];
    UINT stride[16];
    for (int i = 0; i < 16; i++)
    {
        base[i] = xs.streams[i] ? (const BYTE *)(ULONG_PTR)(xs.streams[i]->Data | 0x80000000) : NULL;
        stride[i] = xs.strides[i];
    }
    if (up)
    {
        base[0] = up;
        stride[0] = upStride;
    }
    float *out = &vtx[0];
    for (UINT v = 0; v < count; v++)
        for (int k = 0; k < s->count; k++, out += 4)
        {
            const XVertexElement &e = s->elements[k];
            if (!base[e.stream])
            {
                out[0] = out[1] = out[2] = 0;
                out[3] = 1;
                continue;
            }
            convert_element(base[e.stream] + (size_t)(first + v) * stride[e.stream] + e.offset, e.type, out);
        }
    return 1;
}

/*
 * The fixed-function vertex pipeline
 */

static void put_matrix(int at, const D3DMATRIX &m)
{
    memcpy(xs.vsConstants[at], &m, 64);
}

static void mul_matrix(D3DMATRIX &r, const D3DMATRIX &a, const D3DMATRIX &b)
{
    D3DMATRIX t;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            t.m[i][j] = a.m[i][0] * b.m[0][j] + a.m[i][1] * b.m[1][j] + a.m[i][2] * b.m[2][j] + a.m[i][3] * b.m[3][j];
    r = t;
}

static void put4(int at, float a, float b, float c, float d)
{
    xs.vsConstants[at][0] = a;
    xs.vsConstants[at][1] = b;
    xs.vsConstants[at][2] = c;
    xs.vsConstants[at][3] = d;
}

static void put_color(int at, const D3DCOLORVALUE &c)
{
    put4(at, c.r, c.g, c.b, c.a);
}

static float dword_float(DWORD d)
{
    float f;
    memcpy(&f, &d, 4);
    return f;
}

static void put_argb(int at, DWORD c)
{
    put4(at, ((c >> 16) & 0xFF) / 255.0f, ((c >> 8) & 0xFF) / 255.0f, (c & 0xFF) / 255.0f, ((c >> 24) & 0xFF) / 255.0f);
}

/* Fills the fixed-function block: matrices, material, lights in view space, fog. */
static void ff_constants(void)
{
    put_matrix(XFF_WORLD, xs.transforms[D3DTS_WORLD]);
    put_matrix(XFF_VIEW, xs.transforms[D3DTS_VIEW]);
    put_matrix(XFF_PROJ, xs.transforms[D3DTS_PROJECTION]);
    for (int i = 0; i < 4; i++)
        put_matrix(XFF_TEX0 + i * 4, xs.transforms[D3DTS_TEXTURE0 + i]);
    put_color(XFF_MATERIAL + 0, xs.material.Diffuse);
    put_color(XFF_MATERIAL + 1, xs.material.Ambient);
    put_color(XFF_MATERIAL + 2, xs.material.Specular);
    put_color(XFF_MATERIAL + 3, xs.material.Emissive);
    put4(XFF_MATERIAL + 4, xs.material.Power, 0, 0, 0);
    put_argb(XFF_AMBIENT, RS(D3DRS_AMBIENT));
    put4(XFF_FOG, dword_float(RS(D3DRS_FOGSTART)), dword_float(RS(D3DRS_FOGEND)), dword_float(RS(D3DRS_FOGDENSITY)),
         (float)RS(D3DRS_FOGTABLEMODE));
    const D3DMATRIX &view = xs.transforms[D3DTS_VIEW];
    for (int i = 0; i < 8; i++)
    {
        int at = XFF_LIGHTS + i * 8;
        const D3DLIGHT8 &l = xs.lights[i];
        if (!xs.lightOn[i])
        {
            put4(at + 6, 0, 0, 0, 0);
            continue;
        }
        put_color(at + 0, l.Diffuse);
        put_color(at + 1, l.Specular);
        put_color(at + 2, l.Ambient);
        const D3DVECTOR &p = l.Position, &d = l.Direction;
        float vp[3], vd[3];
        for (int k = 0; k < 3; k++)
        {
            vp[k] = p.x * view.m[0][k] + p.y * view.m[1][k] + p.z * view.m[2][k] + view.m[3][k];
            vd[k] = d.x * view.m[0][k] + d.y * view.m[1][k] + d.z * view.m[2][k];
        }
        float len = sqrtf(vd[0] * vd[0] + vd[1] * vd[1] + vd[2] * vd[2]);
        if (len > 0)
            for (int k = 0; k < 3; k++)
                vd[k] /= len;
        put4(at + 3, vp[0], vp[1], vp[2], (float)l.Type);
        put4(at + 4, vd[0], vd[1], vd[2], 0);
        put4(at + 5, l.Range, l.Falloff, l.Attenuation0, l.Attenuation1);
        put4(at + 6, l.Attenuation2, cosf(l.Theta * 0.5f), cosf(l.Phi * 0.5f), 1);
    }
    put4(XFF_VIEWPORT, 0, 0, 0, 0);
}

static const char *const vs_header =
    "cbuffer XboxConstants : register(b0) { float4 c[320]; };\n"
    "cbuffer XboxViewport : register(b1) { float4 vpOffset; float4 vpScale; };\n"
    "struct VSOut {\n"
    "    float4 pos : SV_Position;\n"
    "    float4 d0 : COLOR0;\n"
    "    float4 d1 : COLOR1;\n"
    "    float4 t0 : TEXCOORD0;\n"
    "    float4 t1 : TEXCOORD1;\n"
    "    float4 t2 : TEXCOORD2;\n"
    "    float4 t3 : TEXCOORD3;\n"
    "    float fog : FOG;\n"
    "};\n"
    "float4 xform(float4 v, int m) { return v.x * c[m] + v.y * c[m + 1] + v.z * c[m + 2] + v.w * c[m + 3]; }\n"
    "float3 xform3(float3 v, int m) { return v.x * c[m].xyz + v.y * c[m + 1].xyz + v.z * c[m + 2].xyz; }\n";

/* The fixed-function shader for the current state. */
static std::string ff_vertex_shader(const XVertexShader *s, int pretransformed)
{
    char buf[8192];
    std::string h = vs_header;
    h += "struct VSIn {\n";
    for (int k = 0; k < s->count; k++)
    {
        _snprintf(buf, sizeof(buf) - 1, "    float4 v%d : V%d;\n", s->elements[k].reg, s->elements[k].reg);
        h += buf;
    }
    h += "    uint vid : SV_VertexID;\n};\n";
    unsigned d = s->declared;
    std::string get[16];
    for (int r = 0; r < 16; r++)
    {
        if (d & (1u << r))
            _snprintf(buf, sizeof(buf) - 1, "i.v%d", r);
        else
            _snprintf(buf, sizeof(buf) - 1, "c[%d]", XFF_DEFAULTS + r);
        get[r] = buf;
    }
    h += "VSOut main(VSIn i) {\n    VSOut o;\n";
    h += "    float4 diffuse = " + get[3] + ", specular = " + std::string((d & 0x10) ? "i.v4" : "float4(0, 0, 0, 0)") + ";\n";
    if (!(d & 8))
        h += "    diffuse = float4(1, 1, 1, 1);\n";
    if (pretransformed)
    {
        /* screen space (z scaled as the Xbox's), w from rhw */
        h += "    float4 p = " + get[0] + ";\n"
             "    float w = p.w != 0 ? 1.0 / p.w : 1.0;\n"
             "    float2 ndc = (p.xy - vpOffset.xy) / vpScale.xy;\n"
             "    float nz = vpScale.z != 0 ? (p.z - vpOffset.z) / vpScale.z : 0;\n"
             "    o.pos = float4(ndc * w, nz * w, w);\n"
             "    float3 vpos = float3(0, 0, 0), vn = float3(0, 0, 1);\n"
             "    float fogc = 1.0;\n";
    }
    else
    {
        sprintf(buf,
                "    float4 wp = xform(float4(%s.xyz, 1), %d);\n"
                "    float4 vp4 = xform(wp, %d);\n"
                "    o.pos = xform(vp4, %d);\n"
                "    float3 vpos = vp4.xyz;\n"
                "    float3 vn = normalize(xform3(xform3(%s.xyz, %d), %d) + 1e-20);\n"
                "    float fogc = abs(vp4.z);\n",
                get[0].c_str(), XFF_WORLD, XFF_VIEW, XFF_PROJ, get[2].c_str(), XFF_WORLD, XFF_VIEW);
        h += buf;
    }
    if (!pretransformed && RS(D3DRS_LIGHTING) && (d & 4))
    {
        /* material sources: 0 the material, 1 the diffuse vertex colour, 2 the specular */
        const char *src[3] = {"", "diffuse", "specular"};
        DWORD cv = RS(D3DRS_COLORVERTEX);
        int sd = cv ? (int)RS(D3DRS_DIFFUSEMATERIALSOURCE) : 0, sa = cv ? (int)RS(D3DRS_AMBIENTMATERIALSOURCE) : 0;
        int ss = cv ? (int)RS(D3DRS_SPECULARMATERIALSOURCE) : 0, se = cv ? (int)RS(D3DRS_EMISSIVEMATERIALSOURCE) : 0;
        sprintf(buf,
                "    float4 md = %s, ma = %s, ms = %s, me = %s;\n",
                sd > 0 && sd < 3 ? src[sd] : "c[220]", sa > 0 && sa < 3 ? src[sa] : "c[221]",
                ss > 0 && ss < 3 ? src[ss] : "c[222]", se > 0 && se < 3 ? src[se] : "c[223]");
        h += buf;
        sprintf(buf,
                "    float3 ld = 0, ls = 0, la = 0;\n"
                "    [loop] for (int n = 0; n < 8; n++) {\n"
                "        int b = %d + n * 8;\n"
                "        if (c[b + 6].w == 0) continue;\n"
                "        float3 L; float att = 1, spot = 1;\n"
                "        if (c[b + 3].w == 3) L = -c[b + 4].xyz;\n"
                "        else {\n"
                "            L = c[b + 3].xyz - vpos; float dist = length(L); L /= max(dist, 1e-20);\n"
                "            if (dist > c[b + 5].x) continue;\n"
                "            att = 1.0 / max(c[b + 5].z + c[b + 5].w * dist + c[b + 6].x * dist * dist, 1e-20);\n"
                "            if (c[b + 3].w == 2) {\n"
                "                float rho = dot(-L, c[b + 4].xyz);\n"
                "                spot = rho > c[b + 6].y ? 1 : rho <= c[b + 6].z ? 0 :\n"
                "                    pow(saturate((rho - c[b + 6].z) / max(c[b + 6].y - c[b + 6].z, 1e-6)), c[b + 5].y);\n"
                "            }\n"
                "        }\n"
                "        float k = att * spot;\n"
                "        ld += k * max(dot(vn, L), 0) * c[b].rgb;\n"
                "        la += k * c[b + 2].rgb;\n"
                "        if (%d) ls += k * pow(max(dot(vn, normalize(L - normalize(vpos))), 0), c[224].x) * c[b + 1].rgb;\n"
                "    }\n"
                "    o.d0 = saturate(float4(me.rgb + ma.rgb * (c[%d].rgb + la) + md.rgb * ld, md.a));\n"
                "    o.d1 = saturate(float4(ms.rgb * ls, 0));\n",
                XFF_LIGHTS, RS(D3DRS_SPECULARENABLE) ? 1 : 0, XFF_AMBIENT);
        h += buf;
    }
    else
        h += "    o.d0 = saturate(diffuse);\n    o.d1 = saturate(specular);\n";

    /* texture coordinates per stage: the set or the generated coordinates, then the matrix */
    for (int st = 0; st < 4; st++)
    {
        DWORD tci = TSS(st, D3DTSS_TEXCOORDINDEX);
        DWORD set = tci & 0xFFFF, gen = tci & 0xFFFF0000;
        std::string coord;
        if (gen == 0x10000)
            coord = "float4(vn, 1)";
        else if (gen == 0x20000)
            coord = "float4(vpos, 1)";
        else if (gen == 0x30000)
            coord = "float4(reflect(normalize(vpos), vn), 1)";
        else
            coord = set < 4 ? get[9 + set] : "float4(0, 0, 0, 1)";
        DWORD ttff = TSS(st, D3DTSS_TEXTURETRANSFORMFLAGS);
        _snprintf(buf, sizeof(buf) - 1, "    float4 tc%d = %s;\n", st, coord.c_str());
        h += buf;
        if ((ttff & 0xFF) && !pretransformed)
        {
            _snprintf(buf, sizeof(buf) - 1, "    tc%d = xform(float4(tc%d.xyz, 1), %d);\n", st, st, XFF_TEX0 + st * 4);
            h += buf;
        }
    }
    h += "    o.t0 = tc0; o.t1 = tc1; o.t2 = tc2; o.t3 = tc3;\n"
         "    o.fog = fogc;\n"
         "    return o;\n}\n";
    return h;
}

static const unsigned char *vtx_regs_of(const XVertexShader *s)
{
    static unsigned char r[16];
    for (int k = 0; k < s->count && k < 16; k++)
        r[k] = s->elements[k].reg;
    return r;
}

/* What the fixed-function shader depends on: the declaration's registers, and the lighting,
   material-source and texture-coordinate states. */
struct FFKey
{
    unsigned char regs[16];
    int count, pretransformed;
    DWORD rs[7];
    DWORD tss[4][2];
};

static void *ff_shader_cached(const XVertexShader *s, int pretransformed)
{
    FFKey k;
    memset(&k, 0, sizeof(k));
    for (int i = 0; i < s->count && i < 16; i++)
        k.regs[i] = s->elements[i].reg;
    k.count = s->count;
    k.pretransformed = pretransformed;
    k.rs[0] = RS(D3DRS_LIGHTING);
    k.rs[1] = RS(D3DRS_COLORVERTEX);
    k.rs[2] = RS(D3DRS_DIFFUSEMATERIALSOURCE);
    k.rs[3] = RS(D3DRS_AMBIENTMATERIALSOURCE);
    k.rs[4] = RS(D3DRS_SPECULARMATERIALSOURCE);
    k.rs[5] = RS(D3DRS_EMISSIVEMATERIALSOURCE);
    k.rs[6] = RS(D3DRS_SPECULARENABLE);
    for (int st = 0; st < 4; st++)
    {
        k.tss[st][0] = TSS(st, D3DTSS_TEXCOORDINDEX);
        k.tss[st][1] = TSS(st, D3DTSS_TEXTURETRANSFORMFLAGS);
    }
    static std::map<std::string, void *> cache;
    std::string key((const char *)&k, sizeof(k));
    std::map<std::string, void *>::iterator it = cache.find(key);
    if (it != cache.end())
        return it->second;
    std::string h = ff_vertex_shader(s, pretransformed);
    void *vs = pdev_vertex_shader(h.c_str(), vtx_regs_of(s), s->count);
    cache[key] = vs;
    return vs;
}

/* The device's vertex shader for the current state. */
static void *vertex_shader(XVertexShader **decl)
{
    static XVertexShader fvf_shader;
    static DWORD fvf_code = 0xFFFFFFFF;
    static int fvf_pretransformed;
    XVertexShader *s = xs.programmable;
    if (!s)
    {
        if (xs.vertexShader != fvf_code)
        {
            fvf_declaration(xs.vertexShader, &fvf_shader, &fvf_pretransformed);
            fvf_code = xs.vertexShader;
        }
        s = &fvf_shader;
        *decl = s;
        ff_constants();
        return ff_shader_cached(s, fvf_pretransformed);
    }
    *decl = s;
    if (!s->program)
    {
        ff_constants();
        return ff_shader_cached(s, 0);
    }
    if (!s->device && !s->failed)
    {
        XvshResult r = s->programIsText == 1 ? xvsh_from_text((const char *)(s->program + 2), s->program[1], s->declared)
                                             : xvsh_from_microcode((const unsigned *)s->program, s->declared);
        if (!r.ok)
        {
            plog("vertex shader not translated (%s, %d elements): fixed function instead",
                 s->programIsText == 1 ? "text" : "microcode", s->count);
            s->failed = 1;
        }
        else
            s->device = pdev_vertex_shader(r.hlsl.c_str(), vtx_regs_of(s), s->count);
    }
    if (s->failed)
    {
        ff_constants();
        return ff_shader_cached(s, 0);
    }
    for (int i = 0; i < 192; i++)
        if (s->constantMask[i / 32] & (1u << (i % 32)))
            memcpy(xs.vsConstants[i], s->constants[i], 16);
    return s->device;
}

/*
 * Pixel shaders from the texture stages
 */

static int stage_texture_kind(int st)
{
    D3DBaseTexture *t = xs.textures[st];
    if (!t)
        return 0;
    return (t->Format & 4) ? 2 : 1;     /* 2: a cube map */
}

static std::string stage_arg(int st, DWORD a, bool alpha)
{
    char buf[64];
    std::string v;
    switch (a & 0xF)
    {
    case 0: v = "i.d0"; break;                  /* diffuse */
    case 1: v = st ? "cur" : "i.d0"; break;     /* current */
    case 2: _snprintf(buf, sizeof(buf) - 1, "tex%d", st); v = buf; break;
    case 3: v = "psc[0]"; break;                /* the texture factor */
    case 4: v = "i.d1"; break;                  /* specular */
    case 5: v = "tmp"; break;
    default: v = "float4(1, 1, 1, 1)"; break;
    }
    if (a & 0x20)
        v = "(" + v + ").aaaa";
    if (a & 0x10)
        v = "(1 - " + v + ")";
    (void)alpha;
    return v;
}

static std::string stage_op(int st, DWORD op, const std::string &a0, const std::string &a1, const std::string &a2)
{
    char buf[32];
    _snprintf(buf, sizeof(buf) - 1, "tex%d", st);
    std::string tex = buf;
    switch (op)
    {
    case 0x2: return a1;                                        /* SELECTARG1 */
    case 0x3: return a2;                                        /* SELECTARG2 */
    case 0x4: return a1 + " * " + a2;                           /* MODULATE */
    case 0x5: return "2 * " + a1 + " * " + a2;
    case 0x6: return "4 * " + a1 + " * " + a2;
    case 0x7: return a1 + " + " + a2;                           /* ADD */
    case 0x8: return a1 + " + " + a2 + " - 0.5";                /* ADDSIGNED */
    case 0x9: return "2 * (" + a1 + " + " + a2 + " - 0.5)";
    case 0xA: return a1 + " - " + a2;                           /* SUBTRACT */
    case 0xB: return a1 + " + " + a2 + " - " + a1 + " * " + a2; /* ADDSMOOTH */
    case 0xC: return "lerp(" + a2 + ", " + a1 + ", i.d0.a)";    /* BLENDDIFFUSEALPHA */
    case 0xD: return "lerp(" + a2 + ", " + a1 + ", cur.a)";     /* BLENDCURRENTALPHA */
    case 0xE: return "lerp(" + a2 + ", " + a1 + ", " + tex + ".a)"; /* BLENDTEXTUREALPHA */
    case 0xF: return "lerp(" + a2 + ", " + a1 + ", psc[0].a)";  /* BLENDFACTORALPHA */
    case 0x10: return a1 + " + " + a2 + " * (1 - " + tex + ".a)";   /* BLENDTEXTUREALPHAPM */
    case 0x11: return a1;                                       /* PREMODULATE */
    case 0x12: return "float4((" + a1 + ").rgb + (" + a1 + ").a * (" + a2 + ").rgb, (" + a1 + ").a)";
    case 0x13: return "float4((" + a1 + ").rgb * (" + a2 + ").rgb + (" + a1 + ").a, (" + a1 + ").a)";
    case 0x14: return "float4((1 - (" + a1 + ").a) * (" + a2 + ").rgb + (" + a1 + ").rgb, (" + a1 + ").a)";
    case 0x15: return "float4((1 - (" + a1 + ").rgb) * (" + a2 + ").rgb + (" + a1 + ").a, (" + a1 + ").a)";
    case 0x16: return "saturate(dot((" + a1 + ").rgb * 2 - 1, (" + a2 + ").rgb * 2 - 1)).xxxx"; /* DOTPRODUCT3 */
    case 0x17: return a0 + " + " + a1 + " * " + a2;             /* MULTIPLYADD */
    case 0x18: return "lerp(" + a2 + ", " + a1 + ", " + a0 + ")";  /* LERP */
    default: return a1;                                         /* the bump-map ops: their first argument */
    }
}

static const char *cmp_hlsl(DWORD f)
{
    switch (f)
    {
    case 0x200: return "false";
    case 0x201: return "a < r";
    case 0x202: return "a == r";
    case 0x203: return "a <= r";
    case 0x204: return "a > r";
    case 0x205: return "a != r";
    case 0x206: return "a >= r";
    default: return "true";
    }
}

static std::string stage_pixel_shader(void)
{
    char buf[8192];
    std::string h =
        "cbuffer PS : register(b0) { float4 psc[16]; };\n"
        "Texture2D t2_0 : register(t0); Texture2D t2_1 : register(t1); Texture2D t2_2 : register(t2); Texture2D t2_3 : register(t3);\n"
        "SamplerState s0 : register(s0); SamplerState s1 : register(s1); SamplerState s2 : register(s2); SamplerState s3 : register(s3);\n"
        "struct PSIn {\n"
        "    float4 pos : SV_Position;\n"
        "    float4 d0 : COLOR0;\n"
        "    float4 d1 : COLOR1;\n"
        "    float4 t0 : TEXCOORD0;\n"
        "    float4 t1 : TEXCOORD1;\n"
        "    float4 t2 : TEXCOORD2;\n"
        "    float4 t3 : TEXCOORD3;\n"
        "    float fog : FOG;\n"
        "};\n";
    for (int st = 0; st < 4; st++)
        if (stage_texture_kind(st) == 2)
        {
            _snprintf(buf, sizeof(buf) - 1, "TextureCube tc_%d : register(t%d);\n", st, st);
            h += buf;
        }
    h += "float4 main(PSIn i) : SV_Target {\n"
         "    float4 cur = i.d0, tmp = float4(0, 0, 0, 0);\n";
    for (int st = 0; st < 4; st++)
    {
        DWORD cop = TSS(st, D3DTSS_COLOROP);
        if (cop == D3DTOP_DISABLE || cop == 0)
            break;
        DWORD aop = TSS(st, D3DTSS_ALPHAOP);
        int kind = stage_texture_kind(st);
        DWORD ttff = TSS(st, D3DTSS_TEXTURETRANSFORMFLAGS);
        if (kind == 2)
            _snprintf(buf, sizeof(buf) - 1, "    float4 tex%d = tc_%d.Sample(s%d, i.t%d.xyz);\n", st, st, st, st);
        else if (kind == 1 && (ttff & 0x100))
            _snprintf(buf, sizeof(buf) - 1, "    float4 tex%d = t2_%d.Sample(s%d, i.t%d.xy / i.t%d.%c);\n", st, st, st, st, st,
                    "wxyzw"[ttff & 0xFF]);
        else if (kind == 1)
            _snprintf(buf, sizeof(buf) - 1, "    float4 tex%d = t2_%d.Sample(s%d, i.t%d.xy);\n", st, st, st, st);
        else
            _snprintf(buf, sizeof(buf) - 1, "    float4 tex%d = float4(1, 1, 1, 1);\n", st);
        h += buf;
        if (kind && TSS(st, D3DTSS_ALPHAKILL) == 1)
        {
            _snprintf(buf, sizeof(buf) - 1, "    clip(tex%d.a - 0.5 / 255.0);\n", st);
            h += buf;
        }
        std::string c = stage_op(st, cop, stage_arg(st, TSS(st, D3DTSS_COLORARG0), false),
                                 stage_arg(st, TSS(st, D3DTSS_COLORARG1), false),
                                 stage_arg(st, TSS(st, D3DTSS_COLORARG2), false));
        std::string a = aop == D3DTOP_DISABLE || aop == 0
                            ? std::string("cur")
                            : stage_op(st, aop, stage_arg(st, TSS(st, D3DTSS_ALPHAARG0), true),
                                       stage_arg(st, TSS(st, D3DTSS_ALPHAARG1), true),
                                       stage_arg(st, TSS(st, D3DTSS_ALPHAARG2), true));
        const char *dst = TSS(st, D3DTSS_RESULTARG) == 5 ? "tmp" : "cur";
        _snprintf(buf, sizeof(buf) - 1, "    { float4 rc = saturate(%s);\n      float4 ra = saturate(%s);\n      %s = float4(rc.rgb, ra.a); }\n",
                c.c_str(), a.c_str(), dst);
        h += buf;
    }
    if (RS(D3DRS_SPECULARENABLE))
        h += "    cur.rgb = saturate(cur.rgb + i.d1.rgb);\n";
    if (RS(D3DRS_ALPHATESTENABLE))
    {
        _snprintf(buf, sizeof(buf) - 1, "    { float a = round(cur.a * 255), r = psc[2].x; if (!(%s)) discard; }\n",
                cmp_hlsl(RS(D3DRS_ALPHAFUNC)));
        h += buf;
    }
    if (RS(D3DRS_FOGENABLE))
    {
        /* the table modes from the fog coordinate (distance); none: it is the factor itself */
        switch (RS(D3DRS_FOGTABLEMODE))
        {
        case 1: h += "    float f = exp(-psc[2].w * i.fog);\n"; break;
        case 2: h += "    float f = exp(-(psc[2].w * i.fog) * (psc[2].w * i.fog));\n"; break;
        case 3: h += "    float f = (psc[2].z - i.fog) / max(psc[2].z - psc[2].y, 1e-6);\n"; break;
        default: h += "    float f = i.fog;\n"; break;
        }
        h += "    cur.rgb = lerp(psc[1].rgb, cur.rgb, saturate(f));\n";
    }
    h += "    return cur;\n}\n";
    return h;
}

/*
 * Xbox pixel shaders (W2.5): a D3DPIXELSHADERDEF (the NV2A register combiners) as HLSL. The
 * definition's 60 dwords: alpha inputs 0-7, final combiner inputs ABCD 8 and EFG 9, stage
 * constants 0 at 10-17 and 1 at 18-25, alpha outputs 26-33, RGB inputs 34-41, compare mode 42,
 * final constants 43-44, RGB outputs 45-52, the combiner count 53, texture modes 54, dot mapping
 * 55, input textures 56, the constants' mappings 57-58 (a register per stage, F for the stage's
 * own value) and the final combiner's 59.
 *
 * A combiner stage computes AB = A*B (or A.B), CD = C*D (or C.D) and their sum (or r0.a's mux)
 * for RGB and alpha apart, each input a register (zero, c0, c1, fog, v0, v1, t0-t3, r0, r1, the
 * final combiner's v1+r0 and E*F), its RGB or alpha, mapped (unsigned, inverted, expanded,
 * half-biased, signed, negated); outputs scaled and biased. r0.a starts as t0's alpha. Without
 * a final combiner the result is r0, fogged as Xbox D3D's default final combiner does.
 */

static std::string ps_input(DWORD in, bool alpha, int stage, const DWORD *def)
{
    char buf[96];
    int reg = in & 0xF, chan = (in >> 4) & 1, map = (in >> 5) & 7;
    std::string v;
    switch (reg)
    {
    case 0: v = "float4(0, 0, 0, 0)"; break;
    case 1: sprintf(buf, "c0_%d", stage); v = buf; break;
    case 2: sprintf(buf, "c1_%d", stage); v = buf; break;
    case 3: v = "fogv"; break;
    case 4: v = "v0"; break;
    case 5: v = "v1"; break;
    case 8: case 9: case 10: case 11: sprintf(buf, "t%d", reg - 8); v = buf; break;
    case 12: v = "r0"; break;
    case 13: v = "r1"; break;
    case 14: v = "v1r0"; break;
    case 15: v = "efp"; break;
    default: v = "float4(0, 0, 0, 0)"; break;
    }
    (void)def;
    /* the channel: alpha replicated, or the colour (with its blue as alpha, on the alpha side) */
    v = chan ? "(" + v + ").aaaa" : (alpha ? "(" + v + ").bbbb" : v);
    switch (map)
    {
    case 0: return "saturate(" + v + ")";
    case 1: return "(1 - saturate(" + v + "))";
    case 2: return "(2 * saturate(" + v + ") - 1)";
    case 3: return "(1 - 2 * saturate(" + v + "))";
    case 4: return "(saturate(" + v + ") - 0.5)";
    case 5: return "(0.5 - saturate(" + v + "))";
    case 6: return v;
    default: return "(-" + v + ")";
    }
}

static const char *ps_reg_name(int r)
{
    static const char *const names[16] = {0, "c0x", "c1x", "fogv", "v0", "v1", 0, 0, "t0", "t1", "t2", "t3", "r0", "r1", 0, 0};
    return names[r & 15];
}

static std::string ps_combiner(int stage, DWORD inputs, DWORD outputs, bool alpha, const DWORD *def)
{
    std::string a = ps_input((inputs >> 24) & 0xFF, alpha, stage, def);
    std::string b = ps_input((inputs >> 16) & 0xFF, alpha, stage, def);
    std::string c = ps_input((inputs >> 8) & 0xFF, alpha, stage, def);
    std::string d = ps_input(inputs & 0xFF, alpha, stage, def);
    int cdOut = outputs & 0xF, abOut = (outputs >> 4) & 0xF, sumOut = (outputs >> 8) & 0xF;
    bool cdDot = !alpha && (outputs & 0x1000), abDot = !alpha && (outputs & 0x2000), mux = (outputs & 0x4000) != 0;
    int scale = (outputs >> 15) & 7;
    bool cdBlueToAlpha = !alpha && (outputs & 0x40000), abBlueToAlpha = !alpha && (outputs & 0x80000);
    const char *sw = alpha ? ".a" : ".rgb";
    std::string h;
    char buf[512];
    h += "    {\n";
    h += "        float4 ab = " + (abDot ? "dot((" + a + ").rgb, (" + b + ").rgb).xxxx" : a + " * " + b) + ";\n";
    h += "        float4 cd = " + (cdDot ? "dot((" + c + ").rgb, (" + d + ").rgb).xxxx" : c + " * " + d) + ";\n";
    h += std::string("        float4 sm = ") + (mux ? "(r0.a >= 0.5 ? cd : ab)" : "ab + cd") + ";\n";
    static const char *const scales[8] = {"x", "(x - 0.5)", "(2 * x)", "(2 * (x - 0.5))", "(4 * x)", "x",
                                          "(x / 2)", "x"};
    std::string sc = scales[scale];
    std::string::size_type p;
    std::string sab = sc, scd = sc, ssm = sc;
    while ((p = sab.find('x')) != std::string::npos) sab.replace(p, 1, "ab");
    while ((p = scd.find('x')) != std::string::npos) scd.replace(p, 1, "cd");
    while ((p = ssm.find('x')) != std::string::npos) ssm.replace(p, 1, "sm");
    h += "        ab = clamp(" + sab + ", -1, 1); cd = clamp(" + scd + ", -1, 1); sm = clamp(" + ssm + ", -1, 1);\n";
    /* writes (to temporaries first: the stage reads its inputs before writing) */
    struct { int reg; const char *val; } w[3] = {{abOut, "ab"}, {cdOut, "cd"}, {sumOut, "sm"}};
    for (int i = 0; i < 3; i++)
    {
        int r = w[i].reg;
        if (!r || !ps_reg_name(r))
            continue;
        if (r == 1 || r == 2)
            continue;   /* (constants are not written) */
        sprintf(buf, "        %s%s = %s%s;\n", ps_reg_name(r), sw, w[i].val, sw);
        h += buf;
        if ((i == 0 && abBlueToAlpha) || (i == 1 && cdBlueToAlpha))
        {
            sprintf(buf, "        %s.a = %s.b;\n", ps_reg_name(r), w[i].val);
            h += buf;
        }
    }
    h += "    }\n";
    return h;
}

static std::string xbox_pixel_shader(const DWORD *def)
{
    char buf[512];
    std::string h =
        "cbuffer PS : register(b0) { float4 psc[16]; };\n"
        "SamplerState s0 : register(s0); SamplerState s1 : register(s1); SamplerState s2 : register(s2); SamplerState s3 : register(s3);\n"
        "struct PSIn {\n"
        "    float4 pos : SV_Position;\n"
        "    float4 d0 : COLOR0;\n"
        "    float4 d1 : COLOR1;\n"
        "    float4 t0 : TEXCOORD0;\n"
        "    float4 t1 : TEXCOORD1;\n"
        "    float4 t2 : TEXCOORD2;\n"
        "    float4 t3 : TEXCOORD3;\n"
        "    float fog : FOG;\n"
        "};\n"
        "";
    for (int st = 0; st < 4; st++)
    {
        sprintf(buf, stage_texture_kind(st) == 2 ? "TextureCube tc_%d : register(t%d);\n" : "Texture2D t2_%d : register(t%d);\n",
                st, st);
        h += buf;
    }
    h += "float4 main(PSIn i) : SV_Target {\n"
         "    float4 v0 = i.d0, v1 = i.d1;\n";
    /* the fog register: its colour, and the factor as alpha */
    h += "    float fogf = 1;\n";
    switch (RS(D3DRS_FOGTABLEMODE))
    {
    case 1: h += "    fogf = exp(-psc[10].w * i.fog);\n"; break;
    case 2: h += "    fogf = exp(-(psc[10].w * i.fog) * (psc[10].w * i.fog));\n"; break;
    case 3: h += "    fogf = (psc[10].z - i.fog) / max(psc[10].z - psc[10].y, 1e-6);\n"; break;
    default: h += "    fogf = i.fog;\n"; break;
    }
    h += "    float4 fogv = float4(psc[9].rgb, saturate(fogf));\n";
    DWORD modes = def[54];
    for (int st = 0; st < 4; st++)
    {
        int mode = (modes >> (5 * st)) & 31;
        int kind = stage_texture_kind(st);
        if (mode == 0 || !kind)
            sprintf(buf, "    float4 t%d = float4(0, 0, 0, %s);\n", st, mode == 4 ? "1" : "0");
        else if (mode == 3 || kind == 2)
            sprintf(buf, "    float4 t%d = tc_%d.Sample(s%d, i.t%d.xyz);\n", st, st, st, st);
        else if (mode == 4)
            sprintf(buf, "    float4 t%d = saturate(i.t%d);\n", st, st);
        else
            sprintf(buf, "    float4 t%d = t2_%d.Sample(s%d, i.t%d.xy / (i.t%d.w != 0 ? i.t%d.w : 1));\n", st, st, st, st,
                    st, st);
        h += buf;
    }
    h += "    float4 r0 = float4(0, 0, 0, t0.a), r1 = float4(0, 0, 0, 0);\n";
    int count = def[53] & 0xFF;
    if (count > 8)
        count = 8;
    for (int s = 0; s < count; s++)
    {
        /* the stage's constants: a register or its own value */
        for (int k = 0; k < 2; k++)
        {
            int map = (def[57 + k] >> (4 * s)) & 0xF;
            DWORD value = def[(k ? 18 : 10) + s];
            if (map != 0xF)
                sprintf(buf, "    float4 c%d_%d = psc[%d];\n", k, s, map & 7);
            else
                sprintf(buf, "    float4 c%d_%d = float4(%f, %f, %f, %f);\n", k, s, ((value >> 16) & 0xFF) / 255.0,
                        ((value >> 8) & 0xFF) / 255.0, (value & 0xFF) / 255.0, ((value >> 24) & 0xFF) / 255.0);
            h += buf;
        }
        h += ps_combiner(s, def[34 + s], def[45 + s], false, def);
        h += ps_combiner(s, def[s], def[26 + s], true, def);
    }
    if (def[8] || def[9])
    {
        /* the final combiner: rgb = A*B + (1-A)*C + D, alpha = G */
        int s = 8;  /* its constants */
        for (int k = 0; k < 2; k++)
        {
            int map = (def[59] >> (4 * k)) & 0xF;
            DWORD value = def[43 + k];
            if (map != 0xF)
                sprintf(buf, "    float4 c%d_%d = psc[%d];\n", k, s, map & 7);
            else
                sprintf(buf, "    float4 c%d_%d = float4(%f, %f, %f, %f);\n", k, s, ((value >> 16) & 0xFF) / 255.0,
                        ((value >> 8) & 0xFF) / 255.0, (value & 0xFF) / 255.0, ((value >> 24) & 0xFF) / 255.0);
            h += buf;
        }
        DWORD abcd = def[8], efg = def[9];
        h += "    float4 efp = " + ps_input((efg >> 24) & 0xFF, false, s, def) + " * " +
             ps_input((efg >> 16) & 0xFF, false, s, def) + ";\n";
        h += std::string("    float4 v1r0 = ") + ((efg & 0x80) ? "saturate(v1 + r0)" : "(v1 + r0)") + ";\n";
        std::string A = ps_input((abcd >> 24) & 0xFF, false, s, def), B = ps_input((abcd >> 16) & 0xFF, false, s, def);
        std::string C = ps_input((abcd >> 8) & 0xFF, false, s, def), D = ps_input(abcd & 0xFF, false, s, def);
        std::string G = ps_input((efg >> 8) & 0xFF, true, s, def);
        h += "    float4 outc = float4((" + A + " * " + B + " + (1 - " + A + ") * " + C + " + " + D + ").rgb, (" + G + ").a);\n";
    }
    else
    {
        /* Xbox D3D's default final combiner: r0, fogged */
        if (RS(D3DRS_FOGENABLE))
            h += "    float4 outc = float4(lerp(fogv.rgb, r0.rgb, fogv.a), r0.a);\n";
        else
            h += "    float4 outc = r0;\n";
    }
    h += "    outc = saturate(outc);\n";
    if (RS(D3DRS_ALPHATESTENABLE))
    {
        _snprintf(buf, sizeof(buf) - 1, "    { float a = round(outc.a * 255), r = psc[10].x; if (!(%s)) discard; }\n",
                  cmp_hlsl(RS(D3DRS_ALPHAFUNC)));
        h += buf;
    }
    h += "    return outc;\n}\n";
    return h;
}

/* What the generated pixel shader depends on: the stages' operations, arguments and texture
   kinds, and the alpha test, specular and fog states. */
struct PSKey
{
    DWORD stage[4][12];
    DWORD rs[6];
};

static void *pixel_shader(void)
{
    if (xs.pixelShader)
    {
        /* an Xbox pixel shader: cached by its definition and the states its text uses */
        struct
        {
            DWORD def[60];
            DWORD rs[4];
            int kinds[4];
        } xk;
        memcpy(xk.def, (const void *)(ULONG_PTR)xs.pixelShader, sizeof(xk.def));
        xk.rs[0] = RS(D3DRS_FOGENABLE);
        xk.rs[1] = RS(D3DRS_FOGTABLEMODE);
        xk.rs[2] = RS(D3DRS_ALPHATESTENABLE);
        xk.rs[3] = RS(D3DRS_ALPHATESTENABLE) ? RS(D3DRS_ALPHAFUNC) : 0;
        for (int st = 0; st < 4; st++)
            xk.kinds[st] = stage_texture_kind(st);
        static std::map<std::string, void *> xcache;
        std::string key((const char *)&xk, sizeof(xk));
        std::map<std::string, void *>::iterator it = xcache.find(key);
        if (it != xcache.end())
            return it->second;
        std::string h = xbox_pixel_shader(xk.def);
        void *ps = pdev_pixel_shader(h.c_str());
        xcache[key] = ps;
        return ps;
    }
    PSKey k;
    memset(&k, 0, sizeof(k));
    for (int st = 0; st < 4; st++)
    {
        static const int which[11] = {D3DTSS_COLOROP, D3DTSS_COLORARG0, D3DTSS_COLORARG1, D3DTSS_COLORARG2,
                                      D3DTSS_ALPHAOP, D3DTSS_ALPHAARG0, D3DTSS_ALPHAARG1, D3DTSS_ALPHAARG2,
                                      D3DTSS_RESULTARG, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTSS_ALPHAKILL};
        for (int i = 0; i < 11; i++)
            k.stage[st][i] = TSS(st, which[i]);
        k.stage[st][11] = (DWORD)stage_texture_kind(st);
        if (TSS(st, D3DTSS_COLOROP) == D3DTOP_DISABLE)
            break;
    }
    k.rs[0] = RS(D3DRS_SPECULARENABLE);
    k.rs[1] = RS(D3DRS_ALPHATESTENABLE);
    k.rs[2] = RS(D3DRS_ALPHATESTENABLE) ? RS(D3DRS_ALPHAFUNC) : 0;
    k.rs[3] = RS(D3DRS_FOGENABLE);
    k.rs[4] = RS(D3DRS_FOGENABLE) ? RS(D3DRS_FOGTABLEMODE) : 0;
    static std::map<std::string, void *> cache;
    std::string key((const char *)&k, sizeof(k));
    std::map<std::string, void *>::iterator it = cache.find(key);
    if (it != cache.end())
        return it->second;
    std::string h = stage_pixel_shader();
    void *ps = pdev_pixel_shader(h.c_str());
    cache[key] = ps;
    return ps;
}

/*
 * Textures
 */

struct TexEntry
{
    DWORD data, format, size;
    DWORD palette;
    unsigned paletteHash;
    int dirty;
    void *device;
};
static std::map<const void *, TexEntry> textures;

void xdraw_texture_dirty(const void *header)
{
    std::map<const void *, TexEntry>::iterator it = textures.find(header);
    if (it != textures.end())
        it->second.dirty = 1;
    /* (a palette: every texture drawn with it is checked by its hash) */
}

void xdraw_texture_forget(const void *header)
{
    std::map<const void *, TexEntry>::iterator it = textures.find(header);
    if (it != textures.end())
    {
        pdev_texture_release(it->second.device);
        textures.erase(it);
    }
}

static unsigned hash_bytes(const void *p, size_t n)
{
    unsigned h = 2166136261u;
    for (size_t i = 0; i < n; i++)
        h = (h ^ ((const unsigned char *)p)[i]) * 16777619u;
    return h;
}

static inline DWORD argb_from(DWORD fmt, const BYTE *p, const DWORD *pal)
{
    WORD w;
    switch (fmt)
    {
    case 0x06: case 0x12: return *(const DWORD *)p;
    case 0x07: case 0x1E: return *(const DWORD *)p | 0xFF000000;
    case 0x05: case 0x11:
        w = *(const WORD *)p;
        return 0xFF000000 | ((w >> 11) * 255 / 31) << 16 | (((w >> 5) & 63) * 255 / 63) << 8 | ((w & 31) * 255 / 31);
    case 0x03: case 0x1C:
        w = *(const WORD *)p;
        return 0xFF000000 | (((w >> 10) & 31) * 255 / 31) << 16 | (((w >> 5) & 31) * 255 / 31) << 8 | ((w & 31) * 255 / 31);
    case 0x02: case 0x10:
        w = *(const WORD *)p;
        return ((w & 0x8000) ? 0xFF000000 : 0) | (((w >> 10) & 31) * 255 / 31) << 16 | (((w >> 5) & 31) * 255 / 31) << 8 |
               ((w & 31) * 255 / 31);
    case 0x04: case 0x1D:
        w = *(const WORD *)p;
        return ((w >> 12) * 17) << 24 | (((w >> 8) & 15) * 17) << 16 | (((w >> 4) & 15) * 17) << 8 | ((w & 15) * 17);
    case 0x00: case 0x13: return 0xFF000000 | p[0] * 0x010101u;         /* L8 */
    case 0x01: case 0x1B: return (DWORD)p[0] << 24 | p[0] * 0x010101u;  /* AL8 */
    case 0x19: case 0x1F: return (DWORD)p[0] << 24 | 0xFFFFFF;          /* A8 */
    case 0x1A: case 0x20: return (DWORD)p[1] << 24 | p[0] * 0x010101u;  /* A8L8 */
    case 0x0B: return pal ? pal[p[0]] : 0xFF000000 | p[0] * 0x010101u; /* P8 */
    case 0x3A: case 0x3F:   /* A8B8G8R8 */
    {
        DWORD v = *(const DWORD *)p;
        return (v & 0xFF00FF00) | ((v >> 16) & 0xFF) | ((v & 0xFF) << 16);
    }
    default: return 0xFFFF00FF;     /* (magenta: a format to add) */
    }
}

/* DXT blocks to BGRA, for compressed textures too small for the device's block formats. */
static void decode_dxt(DWORD fmt, const BYTE *src, int w, int h, DWORD *out)
{
    int bw = (w + 3) / 4, bh = (h + 3) / 4, bsize = fmt == 0x0C ? 8 : 16;
    for (int by = 0; by < bh; by++)
        for (int bx = 0; bx < bw; bx++)
        {
            const BYTE *b = src + (by * bw + bx) * bsize;
            const BYTE *cb = fmt == 0x0C ? b : b + 8;
            WORD c0 = *(const WORD *)cb, c1 = *(const WORD *)(cb + 2);
            DWORD col[4];
            int r[4], g[4], bl[4];
            r[0] = (c0 >> 11) * 255 / 31; g[0] = ((c0 >> 5) & 63) * 255 / 63; bl[0] = (c0 & 31) * 255 / 31;
            r[1] = (c1 >> 11) * 255 / 31; g[1] = ((c1 >> 5) & 63) * 255 / 63; bl[1] = (c1 & 31) * 255 / 31;
            bool four = fmt != 0x0C || c0 > c1;
            if (four)
            {
                r[2] = (2 * r[0] + r[1]) / 3; g[2] = (2 * g[0] + g[1]) / 3; bl[2] = (2 * bl[0] + bl[1]) / 3;
                r[3] = (r[0] + 2 * r[1]) / 3; g[3] = (g[0] + 2 * g[1]) / 3; bl[3] = (bl[0] + 2 * bl[1]) / 3;
            }
            else
            {
                r[2] = (r[0] + r[1]) / 2; g[2] = (g[0] + g[1]) / 2; bl[2] = (bl[0] + bl[1]) / 2;
                r[3] = g[3] = bl[3] = 0;
            }
            for (int k = 0; k < 4; k++)
                col[k] = 0xFF000000 | r[k] << 16 | g[k] << 8 | bl[k];
            if (!four)
                col[3] = 0;
            DWORD bits = *(const DWORD *)(cb + 4);
            for (int py = 0; py < 4; py++)
                for (int px = 0; px < 4; px++)
                {
                    int x = bx * 4 + px, y = by * 4 + py;
                    if (x >= w || y >= h)
                        continue;
                    DWORD c = col[(bits >> ((py * 4 + px) * 2)) & 3];
                    int i = py * 4 + px;
                    if (fmt == 0x0E)
                        c = (c & 0xFFFFFF) | (((b[i / 2] >> ((i & 1) * 4)) & 15) * 17) << 24;
                    else if (fmt == 0x0F)
                    {
                        int a0 = b[0], a1 = b[1];
                        unsigned long long abits = 0;
                        memcpy(&abits, b + 2, 6);
                        int code = (int)((abits >> (i * 3)) & 7), a;
                        if (code == 0) a = a0;
                        else if (code == 1) a = a1;
                        else if (a0 > a1) a = ((8 - code) * a0 + (code - 1) * a1) / 7;
                        else if (code == 6) a = 0;
                        else if (code == 7) a = 255;
                        else a = ((6 - code) * a0 + (code - 1) * a1) / 5;
                        c = (c & 0xFFFFFF) | (DWORD)a << 24;
                    }
                    out[y * w + x] = c;
                }
        }
}

static std::vector<DWORD> tex_scratch, tex_linear;

static void *upload_texture(const D3DBaseTexture *t, const DWORD *pal)
{
    DWORD fmt = (t->Format >> 8) & 0xFF;
    int cube = (t->Format & 4) != 0;
    int linear = port_xb_format_linear(fmt);
    int levels = linear ? 1 : (int)((t->Format >> 16) & 0xF);
    if (levels < 1)
        levels = 1;
    DWORD off;
    int w, h, p;
    port_xb_texture_level(t, 0, 0, &off, &w, &h, &p);
    int dxt = fmt == 0x0C || fmt == 0x0E || fmt == 0x0F;
    int blocks = dxt && !(w & 3) && !(h & 3);
    if (blocks)
    {
        /* (every level must be whole blocks for the device's block formats: drop the small ones) */
        int n = 0;
        for (int lw = w, lh = h; n < levels && !(lw & 3) && !(lh & 3); n++, lw = lw > 1 ? lw / 2 : 1, lh = lh > 1 ? lh / 2 : 1)
            ;
        levels = n ? n : 1;
    }
    void *dt = pdev_texture_create(w, h, levels, blocks ? (fmt == 0x0C ? PDEV_TEX_BC1 : fmt == 0x0E ? PDEV_TEX_BC2 : PDEV_TEX_BC3)
                                                    : PDEV_TEX_BGRA8, cube);
    if (!dt)
        return NULL;
    const BYTE *mem = (const BYTE *)(ULONG_PTR)(t->Data | 0x80000000);
    int bpp = port_xb_format_bpp(fmt) / 8;
    for (int face = 0; face < (cube ? 6 : 1); face++)
        for (int lv = 0; lv < levels; lv++)
        {
            port_xb_texture_level(t, lv, face, &off, &w, &h, &p);
            const BYTE *src = mem + off;
            if (blocks)
            {
                pdev_texture_upload(dt, lv, face, src, ((w + 3) / 4) * (fmt == 0x0C ? 8 : 16));
                continue;
            }
            tex_scratch.resize((size_t)w * h);
            if (dxt)
                decode_dxt(fmt, src, w, h, &tex_scratch[0]);
            else
            {
                const BYTE *rows = src;
                int pitch = p;
                if (!linear)
                {
                    /* swizzled: rows first */
                    tex_linear.resize(((size_t)w * h * bpp + 3) / 4 + 1);
                    XGUnswizzleRect(src, w, h, NULL, &tex_linear[0], w * bpp, NULL, bpp);
                    rows = (const BYTE *)&tex_linear[0];
                    pitch = w * bpp;
                }
                for (int y = 0; y < h; y++)
                    for (int x = 0; x < w; x++)
                        tex_scratch[y * w + x] = argb_from(fmt, rows + y * pitch + x * bpp, pal);
            }
            pdev_texture_upload(dt, lv, face, &tex_scratch[0], w * 4);
        }
    return dt;
}

static void *stage_texture(int st)
{
    D3DBaseTexture *t = xs.textures[st];
    if (!t || !t->Data)
        return NULL;
    DWORD fmt = (t->Format >> 8) & 0xFF;
    const DWORD *pal = NULL;
    unsigned ph = 0;
    DWORD palData = 0;
    if (fmt == 0x0B && xs.palettes[st] && xs.palettes[st]->Data)
    {
        palData = xs.palettes[st]->Data;
        pal = (const DWORD *)(ULONG_PTR)(palData | 0x80000000);
        static const int entries[4] = {256, 128, 64, 32};
        ph = hash_bytes(pal, entries[(xs.palettes[st]->Common >> 30) & 3] * 4);
    }
    TexEntry &e = textures[t];
    if (e.device && !e.dirty && e.data == t->Data && e.format == t->Format && e.size == t->Size &&
        e.palette == palData && e.paletteHash == ph)
        return e.device;
    if (e.device)
        pdev_texture_release(e.device);
    e.data = t->Data;
    e.format = t->Format;
    e.size = t->Size;
    e.palette = palData;
    e.paletteHash = ph;
    e.dirty = 0;
    e.device = upload_texture(t, pal);
    return e.device;
}

/*
 * State
 */

static unsigned char cmp11(DWORD f)
{
    return (f >= 0x200 && f <= 0x207) ? (unsigned char)(f - 0x200 + 1) : 4 /* LESS_EQUAL */;
}

static unsigned char blend11(DWORD b)
{
    switch (b)
    {
    case 0: return 1;
    case 1: return 2;
    case 0x300: return 3;
    case 0x301: return 4;
    case 0x302: return 5;
    case 0x303: return 6;
    case 0x304: return 7;
    case 0x305: return 8;
    case 0x306: return 9;
    case 0x307: return 10;
    case 0x308: return 11;
    case 0x8001: case 0x8003: return 14;    /* the blend factor */
    case 0x8002: case 0x8004: return 15;
    }
    return 2;
}

static unsigned char blendop11(DWORD op)
{
    switch (op)
    {
    case 0x800A: return 2;
    case 0x800B: return 3;
    case 0x8007: return 4;
    case 0x8008: return 5;
    }
    return 1;
}

static unsigned char stencilop11(DWORD op)
{
    switch (op)
    {
    case 0: return 2;
    case 0x1E01: return 3;
    case 0x1E02: return 4;
    case 0x1E03: return 5;
    case 0x150A: return 6;
    case 0x8507: return 7;
    case 0x8508: return 8;
    }
    return 1;   /* KEEP */
}

static unsigned char address11(DWORD a)
{
    switch (a)
    {
    case 2: return 2;           /* MIRROR */
    case 3: case 5: return 3;   /* CLAMP, CLAMPTOEDGE */
    case 4: return 4;           /* BORDER */
    }
    return 1;                   /* WRAP */
}

static unsigned char filter11(DWORD f)
{
    return f == 3 ? 2 : f >= 2 ? 1 : 0;
}

static void fill_state(PDevDraw &d)
{
    d.blendEnable = RS(D3DRS_ALPHABLENDENABLE) ? 1 : 0;
    d.srcBlend = d.srcBlendAlpha = blend11(RS(D3DRS_SRCBLEND));
    d.dstBlend = d.dstBlendAlpha = blend11(RS(D3DRS_DESTBLEND));
    d.blendOp = d.blendOpAlpha = blendop11(RS(D3DRS_BLENDOP));
    DWORD wm = RS(D3DRS_COLORWRITEENABLE);
    d.writeMask = (unsigned char)(((wm & 0x10000) ? 1 : 0) | ((wm & 0x100) ? 2 : 0) | ((wm & 1) ? 4 : 0) | ((wm & 0x1000000) ? 8 : 0));
    d.blendFactor = RS(D3DRS_BLENDCOLOR);
    d.depthEnable = RS(D3DRS_ZENABLE) ? 1 : 0;
    d.depthWrite = RS(D3DRS_ZWRITEENABLE) ? 1 : 0;
    d.depthFunc = cmp11(RS(D3DRS_ZFUNC));
    d.stencilEnable = RS(D3DRS_STENCILENABLE) ? 1 : 0;
    d.stencilFunc = cmp11(RS(D3DRS_STENCILFUNC));
    d.stencilFail = stencilop11(RS(D3DRS_STENCILFAIL));
    d.stencilDepthFail = stencilop11(RS(D3DRS_STENCILZFAIL));
    d.stencilPass = stencilop11(RS(D3DRS_STENCILPASS));
    d.stencilRef = (unsigned char)RS(D3DRS_STENCILREF);
    d.stencilReadMask = (unsigned char)RS(D3DRS_STENCILMASK);
    d.stencilWriteMask = (unsigned char)RS(D3DRS_STENCILWRITEMASK);
    /* CULLMODE culls the faces of that winding; the Xbox's front faces are clockwise */
    DWORD cull = RS(D3DRS_CULLMODE);
    d.cull = cull == 0x900 ? PDEV_CULL_FRONT : cull == 0x901 ? PDEV_CULL_BACK : PDEV_CULL_NONE;
    d.frontCCW = 0;
    d.wireframe = RS(D3DRS_FILLMODE) == 0x1B01;
    d.depthBias = -(float)RS(D3DRS_ZBIAS) * 4096.0f;
    d.slopeBias = 0;
    for (int st = 0; st < 4; st++)
    {
        PDevSampler &s = d.samplers[st];
        s.filterMin = filter11(TSS(st, D3DTSS_MINFILTER));
        s.filterMag = filter11(TSS(st, D3DTSS_MAGFILTER));
        DWORD mip = TSS(st, D3DTSS_MIPFILTER);
        s.filterMip = (unsigned char)(mip == 0 ? 0 : mip == 1 ? 1 : 2);
        s.addressU = address11(TSS(st, D3DTSS_ADDRESSU));
        s.addressV = address11(TSS(st, D3DTSS_ADDRESSV));
        s.addressW = address11(TSS(st, D3DTSS_ADDRESSW));
        s.maxAnisotropy = (unsigned char)TSS(st, D3DTSS_MAXANISOTROPY);
        s.border = TSS(st, D3DTSS_BORDERCOLOR);
        s.lodBias = dword_float(TSS(st, D3DTSS_MIPMAPLODBIAS));
        d.textures[st] = stage_texture(st);
    }
    /* the pixel stage's constants: texture factor, fog colour, (alpha ref, fog start, end, density) */
    static float psc[16][4];
    memcpy(psc, xs.psConstants, sizeof(psc));
    DWORD tf = RS(D3DRS_TEXTUREFACTOR), fc = RS(D3DRS_FOGCOLOR);
    float tfv[4] = {((tf >> 16) & 0xFF) / 255.0f, ((tf >> 8) & 0xFF) / 255.0f, (tf & 0xFF) / 255.0f, ((tf >> 24) & 0xFF) / 255.0f};
    float fcv[4] = {((fc >> 16) & 0xFF) / 255.0f, ((fc >> 8) & 0xFF) / 255.0f, (fc & 0xFF) / 255.0f, 1};
    /* the stages' shaders: texture factor, fog colour, (alpha ref, fog start, end, density) at
       0-2; an Xbox pixel shader's: its eight constant registers, then fog colour at 9 and the
       rest at 10 */
    int base = xs.pixelShader ? 9 : 1;
    if (!xs.pixelShader)
        memcpy(psc[0], tfv, 16);
    memcpy(psc[base], fcv, 16);
    psc[base + 1][0] = (float)(RS(D3DRS_ALPHAREF) & 0xFF);
    psc[base + 1][1] = dword_float(RS(D3DRS_FOGSTART));
    psc[base + 1][2] = dword_float(RS(D3DRS_FOGEND));
    psc[base + 1][3] = dword_float(RS(D3DRS_FOGDENSITY));
    d.psConstants = &psc[0][0];
}

/*
 * Draws
 */

extern "C" void port_viewport_offset_scale(float *offset, float *scale);

static std::vector<WORD> idx;

/* Lists from the Xbox's other primitives: indices over n vertices (base 0), or none needed. */
static int list_indices(D3DPRIMITIVETYPE prim, const WORD *in, UINT n, int *topology)
{
    idx.clear();
#define I(k) (in ? in[k] : (WORD)(k))
    switch (prim)
    {
    case D3DPT_POINTLIST: *topology = PDEV_PRIM_POINTS; break;
    case D3DPT_LINELIST: *topology = PDEV_PRIM_LINES; break;
    case D3DPT_LINESTRIP: *topology = PDEV_PRIM_LINESTRIP; break;
    case D3DPT_TRIANGLELIST: *topology = PDEV_PRIM_TRIANGLES; break;
    case D3DPT_TRIANGLESTRIP: *topology = PDEV_PRIM_TRISTRIP; break;
    case 3: /* LINELOOP */
        *topology = PDEV_PRIM_LINES;
        for (UINT i = 0; i < n; i++)
        {
            idx.push_back(I(i));
            idx.push_back(I((i + 1) % n));
        }
        return 1;
    case D3DPT_TRIANGLEFAN:
    case 10:    /* POLYGON */
        *topology = PDEV_PRIM_TRIANGLES;
        for (UINT i = 1; i + 1 < n; i++)
        {
            idx.push_back(I(0));
            idx.push_back(I(i));
            idx.push_back(I(i + 1));
        }
        return 1;
    case D3DPT_QUADLIST:
        *topology = PDEV_PRIM_TRIANGLES;
        for (UINT i = 0; i + 3 < n; i += 4)
        {
            WORD q[6] = {I(i), I(i + 1), I(i + 2), I(i), I(i + 2), I(i + 3)};
            idx.insert(idx.end(), q, q + 6);
        }
        return 1;
    case 9:     /* QUADSTRIP */
        *topology = PDEV_PRIM_TRIANGLES;
        for (UINT i = 0; i + 3 < n; i += 2)
        {
            WORD q[6] = {I(i), I(i + 1), I(i + 3), I(i), I(i + 3), I(i + 2)};
            idx.insert(idx.end(), q, q + 6);
        }
        return 1;
    default:
        *topology = PDEV_PRIM_TRIANGLES;
    }
#undef I
    if (in)
    {
        idx.assign(in, in + n);
        return 1;
    }
    return 0;
}

/* Draw statistics, logged every 300 frames (CODFH_STATS=1). */
static struct
{
    unsigned draws, vertices;
    LONGLONG shaders, convert, state, device;
} st;

static LONGLONG now_ticks(void)
{
    LARGE_INTEGER t;
    QueryPerformanceCounter(&t);
    return t.QuadPart;
}

void xdraw_frame_stats(void)
{
    static int on = -1;
    if (on < 0)
    {
        char v[8];
        on = GetEnvironmentVariableA("CODFH_STATS", v, sizeof(v)) ? 1 : 0;
    }
    static unsigned frames;
    if (!on || ++frames % 300)
        return;
    LARGE_INTEGER f;
    QueryPerformanceFrequency(&f);
    double ms = 1000.0 / f.QuadPart / 300;
    plog("stats per frame: %u draws, %u vertices; shaders %.2f ms, convert %.2f ms, state %.2f ms, device %.2f ms",
         st.draws / 300, st.vertices / 300, st.shaders * ms, st.convert * ms, st.state * ms, st.device * ms);
    memset(&st, 0, sizeof(st));
}

static void submit(D3DPRIMITIVETYPE prim, UINT first, UINT count, const WORD *indices, UINT nidx, const BYTE *up,
                   UINT upStride)
{
    if (!pdev_ready() || !count)
        return;
    LONGLONG t0 = now_ticks();
    XVertexShader *decl = NULL;
    void *vs = vertex_shader(&decl);
    void *ps = pixel_shader();
    if (!vs || !ps || !decl)
        return;
    LONGLONG t1 = now_ticks();
    st.shaders += t1 - t0;
    st.draws++;
    st.vertices += count;
    convert_vertices(decl, first, count, up, upStride);
    LONGLONG t2 = now_ticks();
    st.convert += t2 - t1;
    for (int r = 0; r < 16; r++)
    {
        DWORD c = xs.vertexDataColor[r];
        put4(XFF_DEFAULTS + r, ((c >> 16) & 0xFF) / 255.0f, ((c >> 8) & 0xFF) / 255.0f, (c & 0xFF) / 255.0f,
             c ? ((c >> 24) & 0xFF) / 255.0f : 1.0f);
    }
    PDevDraw d;
    memset(&d, 0, sizeof(d));
    d.vs = vs;
    d.ps = ps;
    d.vsConstants = &xs.vsConstants[0][0];
    port_viewport_offset_scale(d.viewport, d.viewport + 4);
    fill_state(d);
    LONGLONG t3 = now_ticks();
    st.state += t3 - t2;
    int topology;
    int haveIdx = list_indices(prim, indices, indices ? nidx : count, &topology);
    d.primitive = topology;
    d.vertices = &vtx[0];
    d.stride = decl->count * 16;
    d.vertexCount = count;
    if (haveIdx)
    {
        if (idx.empty())
            return;
        d.indices = &idx[0];
        d.indexCount = (int)idx.size();
    }
    pdev_draw(&d);
    st.device += now_ticks() - t3;
}

void xdraw_vertices(D3DPRIMITIVETYPE prim, UINT start, UINT count)
{
    submit(prim, start, count, NULL, 0, NULL, 0);
}

void xdraw_indexed(D3DPRIMITIVETYPE prim, UINT count, const WORD *indices)
{
    if (!count || !indices)
        return;
    WORD lo = 0xFFFF, hi = 0;
    for (UINT i = 0; i < count; i++)
    {
        if (indices[i] < lo) lo = indices[i];
        if (indices[i] > hi) hi = indices[i];
    }
    static std::vector<WORD> rebased;
    rebased.resize(count);
    for (UINT i = 0; i < count; i++)
        rebased[i] = (WORD)(indices[i] - lo);
    submit(prim, lo, hi - lo + 1, &rebased[0], count, NULL, 0);
}

void xdraw_up(D3DPRIMITIVETYPE prim, UINT count, const void *data, UINT stride)
{
    submit(prim, 0, count, NULL, 0, (const BYTE *)data, stride);
}

void xdraw_inline(D3DPRIMITIVETYPE prim, const DWORD *data, UINT dwords)
{
    XVertexShader fvf;
    const XVertexShader *s = xs.programmable;
    if (!s)
    {
        int pretransformed;
        fvf_declaration(xs.vertexShader, &fvf, &pretransformed);
        s = &fvf;
    }
    UINT stride = 0;
    for (int k = 0; k < s->count; k++)
        if (s->elements[k].stream == 0)
        {
            UINT e = s->elements[k].offset + element_size(s->elements[k].type);
            if (e > stride)
                stride = e;
        }
    if (!stride)
        return;
    submit(prim, 0, dwords * 4 / stride, NULL, 0, (const BYTE *)data, stride);
}
