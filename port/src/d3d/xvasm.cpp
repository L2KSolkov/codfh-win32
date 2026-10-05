/*
 * The Xbox vertex shader assembler for the port (docs/WIN32_PORT.md W2.4): XGAssembleShader's
 * text (xvs.1.1 with the Xbox's registers) to NV2A microcode, the format the skin pipeline
 * splices and edits (skinxboxrender.c reads and adjusts the header's instruction count, byte 2,
 * dropping the two-instruction screen-space epilogue the Xbox assembler appends), and the
 * translator (xvsh.cpp) reads.
 *
 * Each text instruction becomes one microcode instruction: a vector (MAC) or a scalar (ILU)
 * operation, its sources in the A, B and C slots (one vertex register and one constant per
 * instruction, as the hardware allows), its destination a temporary or an output register.
 */
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include <string>
#include <vector>

#include "../port.h"

namespace
{

enum { MUX_R = 1, MUX_V = 2, MUX_C = 3 };

struct Src
{
    int mux, index, neg, relative;
    int swz[4];
};

struct Ins
{
    unsigned w[4];
};

void put(Ins &in, int dw, int shift, int bits, unsigned v)
{
    unsigned mask = ((1u << bits) - 1) << shift;
    in.w[dw] = (in.w[dw] & ~mask) | ((v << shift) & mask);
}

const char *skip_ws(const char *p)
{
    while (*p == ' ' || *p == '\t')
        p++;
    return p;
}

/* A constant index: terms added ("a0.x + 4", "2 + -90", "0 + 93"); relative when a0.x appears. */
int const_expr(const std::string &e, int *relative)
{
    int sum = 0;
    *relative = 0;
    const char *p = e.c_str();
    int sign = 1;
    while (*p)
    {
        p = skip_ws(p);
        if (*p == '+')
        {
            p++;
            continue;
        }
        if (*p == '-')
        {
            sign = -sign;
            p++;
            continue;
        }
        if (!strncmp(p, "a0.x", 4))
        {
            *relative = 1;
            p += 4;
            sign = 1;
            continue;
        }
        if (isdigit((unsigned char)*p))
        {
            sum += sign * (int)strtol(p, (char **)&p, 10);
            sign = 1;
            continue;
        }
        if (*p)
            p++;
    }
    return sum;
}

void swizzle(const char *s, int *swz)
{
    int n = 0;
    int v[4] = {0, 1, 2, 3};
    for (; s && *s && n < 4; s++)
    {
        const char *k = strchr("xyzw", *s);
        if (!k)
            break;
        v[n++] = (int)(k - "xyzw");
    }
    for (int i = n; n && i < 4; i++)
        v[i] = v[n - 1];
    memcpy(swz, v, sizeof(v));
}

bool parse_src(std::string t, Src &s)
{
    memset(&s, 0, sizeof(s));
    s.swz[0] = 0; s.swz[1] = 1; s.swz[2] = 2; s.swz[3] = 3;
    const char *p = skip_ws(t.c_str());
    if (*p == '-')
    {
        s.neg = 1;
        p = skip_ws(p + 1);
    }
    std::string rest = p;
    std::string::size_type dot;
    if (rest[0] == 'c' && rest.size() > 1 && rest[1] == '[')
    {
        std::string::size_type close = rest.find(']');
        if (close == std::string::npos)
            return false;
        s.mux = MUX_C;
        s.index = const_expr(rest.substr(2, close - 2), &s.relative) + 96;
        dot = rest.find('.', close);
    }
    else
    {
        dot = rest.find('.');
        std::string reg = rest.substr(0, dot);
        if (reg[0] == 'r')
        {
            s.mux = MUX_R;
            s.index = atoi(reg.c_str() + 1);
        }
        else if (reg[0] == 'v')
        {
            s.mux = MUX_V;
            s.index = atoi(reg.c_str() + 1);
        }
        else if (reg[0] == 'c')
        {
            s.mux = MUX_C;
            s.index = atoi(reg.c_str() + 1) + 96;
        }
        else if (reg == "oPos")
        {
            s.mux = MUX_R;
            s.index = 12;
        }
        else
            return false;
    }
    if (dot != std::string::npos)
        swizzle(rest.c_str() + dot + 1, s.swz);
    return true;
}

void put_src(Ins &in, int slot, const Src &s)
{
    unsigned sw = (unsigned)s.swz[0], sy = (unsigned)s.swz[1], sz = (unsigned)s.swz[2], swv = (unsigned)s.swz[3];
    if (s.mux == MUX_V)
        put(in, 1, 9, 4, s.index);
    if (s.mux == MUX_C)
    {
        put(in, 1, 13, 8, s.index);
        put(in, 3, 1, 1, s.relative);
    }
    if (slot == 0)
    {
        put(in, 1, 8, 1, s.neg);
        put(in, 1, 6, 2, sw); put(in, 1, 4, 2, sy); put(in, 1, 2, 2, sz); put(in, 1, 0, 2, swv);
        put(in, 2, 28, 4, s.mux == MUX_R ? s.index : 0);
        put(in, 2, 26, 2, s.mux);
    }
    else if (slot == 1)
    {
        put(in, 2, 25, 1, s.neg);
        put(in, 2, 23, 2, sw); put(in, 2, 21, 2, sy); put(in, 2, 19, 2, sz); put(in, 2, 17, 2, swv);
        put(in, 2, 13, 4, s.mux == MUX_R ? s.index : 0);
        put(in, 2, 11, 2, s.mux);
    }
    else
    {
        put(in, 2, 10, 1, s.neg);
        put(in, 2, 8, 2, sw); put(in, 2, 6, 2, sy); put(in, 2, 4, 2, sz); put(in, 2, 2, 2, swv);
        unsigned r = s.mux == MUX_R ? (unsigned)s.index : 0;
        put(in, 2, 0, 2, r >> 2);
        put(in, 3, 30, 2, r & 3);
        put(in, 3, 28, 2, s.mux);
    }
}

int mask_of(const char *m)
{
    if (!m || !*m)
        return 0xF;
    int r = 0;
    for (; *m; m++)
    {
        if (*m == 'x') r |= 8;
        else if (*m == 'y') r |= 4;
        else if (*m == 'z') r |= 2;
        else if (*m == 'w') r |= 1;
    }
    return r;
}

/* The output registers' numbers. */
int out_reg(const std::string &n)
{
    static const char *const names[] = {"oPos", 0, 0, "oD0", "oD1", "oFog", "oPts", "oB0", "oB1",
                                        "oT0", "oT1", "oT2", "oT3"};
    for (int i = 0; i < 13; i++)
        if (names[i] && n == names[i])
            return i;
    return -1;
}

std::vector<std::string> split_operands(const std::string &s)
{
    std::vector<std::string> out;
    std::string cur;
    int depth = 0;
    for (size_t i = 0; i < s.size(); i++)
    {
        char c = s[i];
        if (c == '[')
            depth++;
        if (c == ']')
            depth--;
        if (c == ',' && !depth)
        {
            out.push_back(cur);
            cur.clear();
            continue;
        }
        cur += c;
    }
    if (!cur.empty())
        out.push_back(cur);
    for (size_t i = 0; i < out.size(); i++)
    {
        std::string &t = out[i];
        size_t a = t.find_first_not_of(" \t"), b = t.find_last_not_of(" \t\r");
        t = a == std::string::npos ? std::string() : t.substr(a, b - a + 1);
    }
    return out;
}

bool assemble_line(const std::string &line, std::vector<Ins> &out)
{
    std::string l = line;
    std::string::size_type c = l.find(';');
    if (c != std::string::npos)
        l = l.substr(0, c);
    c = l.find("//");
    if (c != std::string::npos)
        l = l.substr(0, c);
    const char *p = skip_ws(l.c_str());
    if (!*p || *p == '\r' || !strncmp(p, "xvs", 3) || *p == '#')
        return true;
    std::string op;
    while (*p && !isspace((unsigned char)*p))
        op += (char)tolower((unsigned char)*p++);
    std::vector<std::string> ops = split_operands(p);
    if (ops.empty())
        return false;

    static const char *const mac_names[] = {"nop", "mov", "mul", "add", "mad", "dp3", "dph", "dp4", "dst",
                                            "min", "max", "slt", "sge", "arl"};
    static const char *const ilu_names[] = {"nop", "imov", "rcp", "rcc", "rsq", "exp", "log", "lit"};
    int mac = -1, ilu = -1;
    for (int i = 0; i < 14; i++)
        if (op == mac_names[i])
            mac = i;
    for (int i = 2; i < 8; i++)
        if (op == ilu_names[i] || (i == 5 && op == "expp") || (i == 6 && op == "logp"))
            ilu = i;
    if (mac < 0 && ilu < 0)
    {
        plog("vertex assembler: unknown instruction \"%s\"", line.c_str());
        return false;
    }

    Ins in;
    memset(&in, 0, sizeof(in));
    /* every unused slot reads r0 (the mux must be legal) */
    Src r0;
    memset(&r0, 0, sizeof(r0));
    r0.mux = MUX_R;
    r0.swz[0] = 0; r0.swz[1] = 1; r0.swz[2] = 2; r0.swz[3] = 3;
    put_src(in, 0, r0);
    put_src(in, 1, r0);
    put_src(in, 2, r0);

    std::string dst = ops[0];
    std::string dreg = dst, dmask;
    std::string::size_type dot = dst.find('.');
    if (dot != std::string::npos)
    {
        dreg = dst.substr(0, dot);
        dmask = dst.substr(dot + 1);
    }
    if (dreg == "a0")
        mac = 13;   /* mov a0.x: the address load */
    std::vector<Src> srcs;
    for (size_t i = 1; i < ops.size(); i++)
    {
        Src s;
        if (!parse_src(ops[i], s))
        {
            plog("vertex assembler: bad source \"%s\" in \"%s\"", ops[i].c_str(), line.c_str());
            return false;
        }
        srcs.push_back(s);
    }
    if (srcs.empty())
        return false;
    int mask = mask_of(dmask.c_str());
    int o = out_reg(dreg);
    if (mac >= 0)
    {
        put(in, 1, 21, 4, mac);
        /* the slots: mov/arl A; add A, C; mad A, B, C; the rest A, B */
        if (mac == 3)
        {
            put_src(in, 0, srcs[0]);
            if (srcs.size() > 1)
                put_src(in, 2, srcs[1]);
        }
        else
            for (size_t i = 0; i < srcs.size() && i < 3; i++)
                put_src(in, (int)i, srcs[i]);
        if (mac != 13)
        {
            if (o >= 0)
            {
                put(in, 3, 12, 4, mask);
                put(in, 3, 11, 1, 1);
                put(in, 3, 3, 8, o);
                put(in, 3, 2, 1, 0);
            }
            else if (dreg[0] == 'r')
            {
                put(in, 3, 24, 4, mask);
                put(in, 3, 20, 4, atoi(dreg.c_str() + 1));
            }
        }
    }
    else
    {
        put(in, 1, 25, 3, ilu);
        put_src(in, 2, srcs[0]);
        if (o >= 0)
        {
            put(in, 3, 12, 4, mask);
            put(in, 3, 11, 1, 1);
            put(in, 3, 3, 8, o);
            put(in, 3, 2, 1, 1);
        }
        else if (dreg[0] == 'r')
        {
            put(in, 3, 16, 4, mask);
            put(in, 3, 20, 4, atoi(dreg.c_str() + 1));
        }
    }
    out.push_back(in);
    return true;
}

} // namespace

/* Text to microcode: the header (count in byte 2, the Xbox's type word) and the instructions,
   with the two-instruction epilogue's place filled by no-ops. Returns the dword count, 0 on
   failure. */
std::vector<unsigned> xvasm_assemble(const char *text, size_t length, bool *ok)
{
    std::vector<Ins> ins;
    std::string src(text, length);
    size_t at = 0;
    *ok = true;
    while (at < src.size())
    {
        size_t nl = src.find('\n', at);
        if (nl == std::string::npos)
            nl = src.size();
        if (!assemble_line(src.substr(at, nl - at), ins))
            *ok = false;
        at = nl + 1;
    }
    for (int i = 0; i < 2; i++)
    {
        Ins nop;
        memset(&nop, 0, sizeof(nop));
        Src r0;
        memset(&r0, 0, sizeof(r0));
        r0.mux = MUX_R;
        r0.swz[1] = 1; r0.swz[2] = 2; r0.swz[3] = 3;
        put_src(nop, 0, r0);
        put_src(nop, 1, r0);
        put_src(nop, 2, r0);
        ins.push_back(nop);
    }
    std::vector<unsigned> out;
    out.push_back(((unsigned)ins.size() << 16) | 0x2078);
    for (size_t i = 0; i < ins.size(); i++)
        for (int k = 0; k < 4; k++)
            out.push_back(ins[i].w[k]);
    out.back() |= 1;    /* the final instruction */
    return out;
}
