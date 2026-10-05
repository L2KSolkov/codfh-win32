/*
 * Xbox (NV2A) vertex shaders to HLSL vs_4_0 (docs/WIN32_PORT.md W2.4).
 *
 * Microcode: a header dword (the instruction count in bits 16-23) and four dwords per
 * instruction, each a vector (MAC) and a scalar (ILU) operation issued together: inputs A, B, C
 * from temporaries r0-r12, vertex registers v0-v15 or constants c[0-191] (optionally relative to
 * a0.x), each swizzled and optionally negated; outputs to a temporary and/or an output register
 * (oPos, oD0/oD1, oFog, oPts, oB0/oB1, oT0-oT3), masked. r12 reads oPos.
 *
 * Xbox shaders write oPos in screen space (the viewport's offset and scale applied, divided by
 * w) with w kept; the epilogue turns that back into clip space for Direct3D 11. Constants are
 * the Xbox's 192 (registers -96..95 at c[0..191]).
 */
#include "xvsh.h"

#include <stdio.h>
#include <string.h>

namespace
{

enum SrcType { S_R, S_V, S_C };
enum { OP_NOP, OP_MOV, OP_MUL, OP_ADD, OP_MAD, OP_DP3, OP_DPH, OP_DP4, OP_DST, OP_MIN, OP_MAX, OP_SLT, OP_SGE,
       OP_ARL, OP_RCP, OP_RCC, OP_RSQ, OP_EXP, OP_LOG, OP_LIT };

struct Src
{
    int type, index, relative, neg;
    int swz[4];
};

/* A destination: a temporary (0-12), an output register (o), or nothing. */
struct Dst
{
    int temp;       /* -1: none */
    int tempMask;
    int out;        /* -1: none; else the Xbox output register number */
    int outMask;
};

struct Ins
{
    int op;
    Src a, b, c;
    Dst d;
};

const char *const out_names[13] = {"oPos", 0, 0, "oD0", "oD1", "oFog", "oPts", "oB0", "oB1",
                                   "oT0", "oT1", "oT2", "oT3"};

unsigned field(const unsigned *ins, int dw, int shift, int bits)
{
    return (ins[dw] >> shift) & ((1u << bits) - 1);
}

Src decode_src(const unsigned *ins, int which)
{
    Src s;
    memset(&s, 0, sizeof(s));
    int mux, neg, sx, sy, sz, sw, reg;
    if (which == 0)
    {
        neg = field(ins, 1, 8, 1);
        sx = field(ins, 1, 6, 2); sy = field(ins, 1, 4, 2); sz = field(ins, 1, 2, 2); sw = field(ins, 1, 0, 2);
        reg = field(ins, 2, 28, 4);
        mux = field(ins, 2, 26, 2);
    }
    else if (which == 1)
    {
        neg = field(ins, 2, 25, 1);
        sx = field(ins, 2, 23, 2); sy = field(ins, 2, 21, 2); sz = field(ins, 2, 19, 2); sw = field(ins, 2, 17, 2);
        reg = field(ins, 2, 13, 4);
        mux = field(ins, 2, 11, 2);
    }
    else
    {
        neg = field(ins, 2, 10, 1);
        sx = field(ins, 2, 8, 2); sy = field(ins, 2, 6, 2); sz = field(ins, 2, 4, 2); sw = field(ins, 2, 2, 2);
        reg = (field(ins, 2, 0, 2) << 2) | field(ins, 3, 30, 2);
        mux = field(ins, 3, 28, 2);
    }
    s.neg = neg;
    s.swz[0] = sx; s.swz[1] = sy; s.swz[2] = sz; s.swz[3] = sw;
    if (mux == 1)
    {
        s.type = S_R;
        s.index = reg;
    }
    else if (mux == 2)
    {
        s.type = S_V;
        s.index = field(ins, 1, 9, 4);
    }
    else
    {
        s.type = S_C;
        s.index = field(ins, 1, 13, 8);
        s.relative = field(ins, 3, 1, 1);
    }
    return s;
}

std::string mask_str(int m)
{
    std::string s;
    if (m & 8) s += 'x';
    if (m & 4) s += 'y';
    if (m & 2) s += 'z';
    if (m & 1) s += 'w';
    return s;
}

struct Gen
{
    std::string body;
    unsigned inputs;
    unsigned declared;

    std::string src(const Src &s)
    {
        char buf[64];
        switch (s.type)
        {
        case S_R:
            if (s.index == 12)
                strcpy(buf, "oPos");
            else
                sprintf(buf, "r%d", s.index);
            break;
        case S_V:
            inputs |= 1u << s.index;
            if (declared & (1u << s.index))
                sprintf(buf, "i.v%d", s.index);
            else    /* the attribute's default (SetVertexDataColor, or 0,0,0,1) */
                sprintf(buf, "c[%d]", 300 + s.index);
            break;
        default:
            if (s.relative)
                sprintf(buf, "c[clamp(a0 + %d, 0, 191)]", s.index);
            else
                sprintf(buf, "c[%d]", s.index);
        }
        std::string r = buf;
        if (!(s.swz[0] == 0 && s.swz[1] == 1 && s.swz[2] == 2 && s.swz[3] == 3))
        {
            r = "(" + r + ").";
            for (int i = 0; i < 4; i++)
                r += "xyzw"[s.swz[i]];
        }
        return s.neg ? "(-" + r + ")" : r;
    }

    void assign(const Dst &d, const std::string &expr)
    {
        body += "    t = " + expr + ";\n";
        if (d.temp >= 0 && d.tempMask)
        {
            std::string m = mask_str(d.tempMask);
            char name[8];
            if (d.temp == 12)
                strcpy(name, "oPos");
            else
                sprintf(name, "r%d", d.temp);
            body += std::string("    ") + name + "." + m + " = t." + m + ";\n";
        }
        if (d.out >= 0 && d.outMask && d.out < 13 && out_names[d.out])
        {
            std::string m = mask_str(d.outMask);
            body += std::string("    ") + out_names[d.out] + "." + m + " = t." + m + ";\n";
        }
    }

    void emit(const Ins &in)
    {
        std::string a = src(in.a), b = src(in.b), c = src(in.c);
        switch (in.op)
        {
        case OP_MOV: assign(in.d, a); break;
        case OP_MUL: assign(in.d, a + " * " + b); break;
        case OP_ADD: assign(in.d, a + " + " + c); break;
        case OP_MAD: assign(in.d, a + " * " + b + " + " + c); break;
        case OP_DP3: assign(in.d, "dot((" + a + ").xyz, (" + b + ").xyz).xxxx"); break;
        case OP_DPH: assign(in.d, "(dot((" + a + ").xyz, (" + b + ").xyz) + (" + b + ").w).xxxx"); break;
        case OP_DP4: assign(in.d, "dot(" + a + ", " + b + ").xxxx"); break;
        case OP_DST:
            assign(in.d, "float4(1, (" + a + ").y * (" + b + ").y, (" + a + ").z, (" + b + ").w)");
            break;
        case OP_MIN: assign(in.d, "min(" + a + ", " + b + ")"); break;
        case OP_MAX: assign(in.d, "max(" + a + ", " + b + ")"); break;
        case OP_SLT: assign(in.d, "float4((" + a + ") < (" + b + "))"); break;
        case OP_SGE: assign(in.d, "float4((" + a + ") >= (" + b + "))"); break;
        case OP_ARL: body += "    a0 = (int)floor((" + a + ").x + 0.001);\n"; break;
        /* the scalar unit takes C's first swizzled component */
        case OP_RCP: assign(in.d, "(1.0 / (" + c + ").x).xxxx"); break;
        case OP_RCC: assign(in.d, "rcc((" + c + ").x).xxxx"); break;
        case OP_RSQ: assign(in.d, "rsqrt(abs((" + c + ").x)).xxxx"); break;
        case OP_EXP: assign(in.d, "xexp((" + c + ").x)"); break;
        case OP_LOG: assign(in.d, "xlog((" + c + ").x)"); break;
        case OP_LIT: assign(in.d, "xlit(" + c + ")"); break;
        default: break;
        }
    }
};

std::string assemble(const Gen &g)
{
    std::string s =
        "cbuffer XboxConstants : register(b0) { float4 c[320]; };\n"
        "cbuffer XboxViewport : register(b1) { float4 vpOffset; float4 vpScale; };\n"
        "struct VSIn {\n";
    char buf[96];
    for (int i = 0; i < 16; i++)
        if ((g.inputs & g.declared) & (1u << i))
        {
            sprintf(buf, "    float4 v%d : V%d;\n", i, i);
            s += buf;
        }
    s += "    uint vid : SV_VertexID;\n};\n"
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
         "float rcc(float x) {\n"
         "    float r = 1.0 / x;\n"
         "    return r < 0 ? clamp(r, -1.884467e19, -5.42101e-20) : clamp(r, 5.42101e-20, 1.884467e19);\n"
         "}\n"
         "float4 xexp(float x) { float f = floor(x); return float4(exp2(f), x - f, exp2(x), 1); }\n"
         "float4 xlog(float x) {\n"
         "    float a = abs(x); if (a == 0) return float4(-1.#INF, 1, -1.#INF, 1);\n"
         "    float e = floor(log2(a)); return float4(e, a / exp2(e), log2(a), 1);\n"
         "}\n"
         "float4 xlit(float4 s) {\n"
         "    float d = max(s.x, 0), h = max(s.y, 0), p = clamp(s.w, -128, 128);\n"
         "    return float4(1, d, s.x > 0 ? pow(h, p) : 0, 1);\n"
         "}\n"
         "VSOut main(VSIn i) {\n"
         "    float4 r0 = 0, r1 = 0, r2 = 0, r3 = 0, r4 = 0, r5 = 0, r6 = 0, r7 = 0, r8 = 0, r9 = 0, r10 = 0, r11 = 0;\n"
         "    float4 oPos = float4(0, 0, 0, 1), oD0 = float4(0, 0, 0, 1), oD1 = float4(0, 0, 0, 1);\n"
         "    float4 oFog = float4(0, 0, 0, 1), oPts = float4(0, 0, 0, 1), oB0 = float4(0, 0, 0, 1), oB1 = float4(0, 0, 0, 1);\n"
         "    float4 oT0 = float4(0, 0, 0, 1), oT1 = float4(0, 0, 0, 1), oT2 = float4(0, 0, 0, 1), oT3 = float4(0, 0, 0, 1);\n"
         "    float4 t; int a0 = 0;\n";
    s += g.body;
    s += "    VSOut o;\n"
         "    /* screen space back to clip space */\n"
         "    float w = oPos.w;\n"
         "    if (abs(w) < 5.42101e-20) w = w < 0 ? -5.42101e-20 : 5.42101e-20;\n"
         "    float2 ndc = (oPos.xy - vpOffset.xy) / vpScale.xy;\n"
         "    float nz = vpScale.z != 0 ? (oPos.z - vpOffset.z) / vpScale.z : 0;\n"
         "    o.pos = float4(ndc * w, nz * w, w);\n"
         "    o.d0 = saturate(oD0); o.d1 = saturate(oD1);\n"
         "    o.t0 = oT0; o.t1 = oT1; o.t2 = oT2; o.t3 = oT3;\n"
         "    o.fog = oFog.x;\n"
         "    return o;\n"
         "}\n";
    return s;
}

} // namespace

XvshResult xvsh_from_microcode(const unsigned *program, unsigned declared)
{
    static const int mac_ops[16] = {OP_NOP, OP_MOV, OP_MUL, OP_ADD, OP_MAD, OP_DP3, OP_DPH, OP_DP4, OP_DST,
                                    OP_MIN, OP_MAX, OP_SLT, OP_SGE, OP_ARL, OP_NOP, OP_NOP};
    static const int ilu_ops[8] = {OP_NOP, OP_MOV, OP_RCP, OP_RCC, OP_RSQ, OP_EXP, OP_LOG, OP_LIT};
    XvshResult r;
    r.ok = false;
    r.inputs = 0;
    unsigned count = (program[0] >> 16) & 0xFF;
    if (!count || count > 136)
        return r;
    Gen g;
    g.inputs = 0;
    g.declared = declared;
    for (unsigned n = 0; n < count; n++)
    {
        const unsigned *ins = program + 1 + n * 4;
        int mac = field(ins, 1, 21, 4), ilu = field(ins, 1, 25, 3);
        int outMask = field(ins, 3, 12, 4), outReg = field(ins, 3, 3, 8);
        int toOut = field(ins, 3, 11, 1);       /* 0: a constant (not supported: dropped) */
        int outFromIlu = field(ins, 3, 2, 1);
        Src a = decode_src(ins, 0), b = decode_src(ins, 1), c = decode_src(ins, 2);
        /* (both units read the registers as they were before the instruction) */
        if (mac && ilu)
            g.body += "    {\n";
        if (mac)
        {
            Ins in;
            in.op = mac_ops[mac];
            in.a = a; in.b = b; in.c = c;
            in.d.temp = field(ins, 3, 20, 4);
            in.d.tempMask = field(ins, 3, 24, 4);
            in.d.out = (!outFromIlu && toOut) ? outReg : -1;
            in.d.outMask = outMask;
            if (ilu)
            {
                /* the scalar result goes to r1: compute it first from the old values */
                Ins s;
                s.op = ilu_ops[ilu];
                /* (the scalar unit reads C only: its mov is of C, not of the MAC's A) */
                s.a = c; s.b = b; s.c = c;
                s.d.temp = -1;
                s.d.tempMask = 0;
                s.d.out = -1;
                s.d.outMask = 0;
                Gen tmp = g;
                tmp.body.clear();
                tmp.emit(s);
                g.inputs = tmp.inputs;
                g.body += tmp.body + "    float4 ilu = t;\n";
                g.emit(in);
                int iluMask = field(ins, 3, 16, 4);
                if (iluMask)
                    g.body += "    r1." + mask_str(iluMask) + " = ilu." + mask_str(iluMask) + ";\n";
                if (outFromIlu && toOut && outMask && outReg < 13 && out_names[outReg])
                    g.body += std::string("    ") + out_names[outReg] + "." + mask_str(outMask) + " = ilu." +
                              mask_str(outMask) + ";\n";
            }
            else
                g.emit(in);
        }
        else if (ilu)
        {
            Ins in;
            in.op = ilu_ops[ilu];
            in.a = c; in.b = b; in.c = c;
            in.d.temp = field(ins, 3, 20, 4);
            in.d.tempMask = field(ins, 3, 16, 4);
            in.d.out = (outFromIlu && toOut) ? outReg : -1;
            in.d.outMask = outMask;
            g.emit(in);
        }
        if (mac && ilu)
            g.body += "    }\n";
        if (field(ins, 3, 0, 1))
            break;
    }
    r.hlsl = assemble(g);
    r.inputs = g.inputs;
    r.ok = true;
    return r;
}

XvshResult xvsh_from_text(const char *, size_t, unsigned)
{
    /* W2.4: the skin pipeline's generated text (a parser into the same instructions) */
    XvshResult r;
    r.ok = false;
    r.inputs = 0;
    return r;
}
