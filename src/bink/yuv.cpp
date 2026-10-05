/*
 * codfh-match: Bink's colour conversion (the library's yuv.obj, C++): the
 * blit state S that the MMX converters (rgb*.asm, yuy2*.asm) work on, the
 * per-format edge helpers that convert the unaligned left and right
 * columns of a blit in C, and the blitters that drive them.
 */
#include "bink.h"
#include "binkint.h"

// RAD puts all of Bink's code in its BINK section (the image's 0x341480-0x34E01C).
#pragma code_seg("BINK")

extern "C" YUVSTATE S;
extern "C" U32 mono32[256];

// the half-height zoom buffers (setevenodd sizes them for the blit width)
extern "C" void *z2hbuf1;
extern "C" U8 *z2hbuf2;
extern "C" U32 z2hsize;

// the converters for a pair of rows the blitters call (EVEN and ODD rows,
// stdcall with the width), the plain ones the half-height zooms double
// (EVENx, ODDx), and the ones timing measures (EVENt, ODDt)
extern "C" ROWPAIRFN EVEN;
extern "C" ROWPAIRFN ODD;
extern "C" ROWPAIRFN EVENx;
extern "C" ROWPAIRFN ODDx;
extern "C" ROWPAIRFN EVENt;
extern "C" ROWPAIRFN ODDt;

// zoom timing: the measured state word (bit 0 decided, bit 1 the buffered
// zoom, bit 2 measuring, bits 2..7 a count, 8.. the cycles), whether the
// blit is still testing, rdtsc's availability, the left edge's cycles
extern "C" U32 *dbltimeaddr;
extern "C" U32 testing;
extern "C" S32 rdtscavail;
extern "C" U32 *alnaddr;
extern "C" U32 lastleft;


// the blit's edge helpers and the alignment the MMX converters need
extern "C" EDGEROWFN dounalignedrow;
extern "C" EDGECOLFN dounalignedcol;
extern "C" U32 alignshift;
extern "C" U32 align;
extern "C" U32 alignm1;
extern "C" U32 whichyuv;      // 1 while YUVTables are swapped for BINKRBINVERT
extern "C" S32 decode_use_MMX;
extern "C" void check_for_MMX(U32 flags);

// each destination format's blitters
extern "C" BLITS blits32;
extern "C" BLITS blits32a;
extern "C" BLITS blits16;
extern "C" BLITS blits16a4;
extern "C" BLITS blits16a1;
extern "C" BLITS blitsyuy2;


extern "C" U32 YUVTables[8][256];
extern "C" U32 mono16[256];
extern "C" S32 ytable[260];
extern "C" U32 clamp_r[];
extern "C" U32 clamp_g[];
extern "C" U32 clamp_b[];
extern "C" U32 clamp_a4[260];
extern "C" U32 *clamp_ytable[260];

// one 32-bit pixel: the Y row's clamp table indexed by the red, green and
// blue offsets of the shared U and V
#define YUV32(yt, r, g, b) ((((yt)[r] << 8) | (yt)[g]) << 8 | (yt)[b])

// The edge helpers are reached only through the blitters' function tables
// (blits32 and the others, at the end of this file); RAD's were probably
// statics, left external here.
#define EDGEFN

#define PUT32(p, c) (*(U32 *)(p) = (c))

// the colour offsets of the current U and V
#define UVOFFSETS                                                        \
    U32 b = YUVTables[0][*S.u];                                          \
    U32 g = YUVTables[2][*S.u] + YUVTables[1][*S.v];                     \
    U32 r = YUVTables[3][*S.v]

// a row of the left or right edge: n pixels from the first Y row, each
// written by PUT, the output advancing by STEP; U and V advance every
// second pixel (x is the edge's column)
#define EDGEROW(name, PIX, PUT, STEP, ADV)                               \
EDGEFN void name(U32 x, U32 n)                                           \
{                                                                        \
  U32 i = x;                                                             \
                                                                         \
  while (n)                                                              \
  {                                                                      \
    U32 *yt;                                                             \
    U32 c;                                                               \
    UVOFFSETS;                                                           \
                                                                         \
    yt = clamp_ytable[*S.y0++];                                                \
    c = PIX(yt, 0);                                                      \
    PUT(S.out0, c);                                                      \
    ADV(0);                                                              \
    S.out0 += STEP;                                                      \
    if (!(++i & 1))                                                      \
    {                                                                    \
      S.u++;                                                             \
      S.v++;                                                             \
    }                                                                    \
    --n;                                                                 \
  }                                                                      \
}

// both rows of an edge column pair
#define EDGECOL(name, PIX, PUT, STEP, ADV)                               \
EDGEFN S32 name(U32 n, S32 x)                                            \
{                                                                        \
  S32 col = x;                                                           \
  U32 i = n;                                                             \
                                                                         \
  do                                                                     \
  {                                                                      \
    U32 *yt;                                                             \
    U32 c;                                                               \
    UVOFFSETS;                                                           \
                                                                         \
    yt = clamp_ytable[*S.y0++];                                                \
    c = PIX(yt, 0);                                                      \
    PUT(S.out0, c);                                                      \
    ADV(0);                                                              \
    yt = clamp_ytable[*S.y1++];                                                \
    c = PIX(yt, 1);                                                      \
    PUT(S.out1, c);                                                      \
    ADV(1);                                                              \
    S.out0 += STEP;                                                      \
    S.out1 += STEP;                                                      \
    if (!(++col & 1))                                                    \
    {                                                                    \
      S.u++;                                                             \
      S.v++;                                                             \
    }                                                                    \
  } while (--i);                                                         \
  return col;                                                            \
}

#define PUT32_2H(p, c) (PUT32(p, c), PUT32((p) + S.pitch, c))

#define PUT32_2WH(p, c) (PUT32(p, c), PUT32((p) + 4, c), PUT32((p) + S.pitch, c), PUT32((p) + S.pitch + 4, c))

// a 32-bit pixel with alpha (the alpha byte on top)
#define YUV32A(yt, a, r, g, b) ((((((U32)(a) << 8) | (yt)[r]) << 8) | (yt)[g]) << 8 | (yt)[b])
#define PIX32(yt, row) YUV32(yt, r, g, b)
#define PIX32A(yt, row) YUV32A(yt, *S.a##row++, r, g, b)
// the undoubled edges step the alpha row after the store
#define PIX32AP(yt, row) YUV32A(yt, *S.a##row, r, g, b)
#define NOADV(row) ((void)0)
#define ADVA(row) (S.a##row++)

// a mono pixel of row ROW
#define MONO32A(row) (mono32[*S.y##row++] | ((U32)*S.a##row++ << 24))

#define PUT32_2W(p, c) (PUT32(p, c), PUT32((p) + 4, c))

// the mono rows and column pairs of an edge
#define EDGEROWM(name, MONO, PUT, STEP)                                  \
EDGEFN void name(U32 x, U32 n)                                           \
{                                                                        \
  while (n)                                                              \
  {                                                                      \
    U32 c = MONO(0);                                                     \
                                                                         \
    PUT(S.out0, c);                                                      \
    S.out0 += STEP;                                                      \
    --n;                                                                 \
  }                                                                      \
}

#define EDGECOLM(name, MONO, PUT, STEP)                                  \
EDGEFN S32 name(U32 n, S32 x)                                            \
{                                                                        \
  U32 i = n;                                                             \
                                                                         \
  do                                                                     \
  {                                                                      \
    U32 c = MONO(0);                                                     \
                                                                         \
    PUT(S.out0, c);                                                      \
    c = MONO(1);                                                         \
    PUT(S.out1, c);                                                      \
    S.out0 += STEP;                                                      \
    S.out1 += STEP;                                                      \
  } while (--i);                                                         \
  return x + n;                                                          \
}

// a 16-bit pixel: the clamp tables' parts for the Y offset plus the
// colour offsets (the tables are biased by 256 entries)
#define YUV16(yo, b, g, r) \
  ((U16)(clamp_b + 256)[(yo) + (b)] | (U16)(clamp_g + 256)[(yo) + (g)] | (U16)(clamp_r + 256)[(yo) + (r)])

#define PIX16(yo, row) YUV16(yo, r, g, b)
#define PIX16A4(yo, row) (YUV16(yo, r, g, b) | (U16)clamp_a4[*S.a##row++])
#define PIX16A4P(yo, row) (YUV16(yo, r, g, b) | (U16)clamp_a4[*S.a##row])
#define A1(a) ((U16)(((a) & 0x80) << 8))
#define PIX16A1(yo, row) (YUV16(yo, r, g, b) | A1(*S.a##row++))
#define PIX16A1P(yo, row) (YUV16(yo, r, g, b) | A1(*S.a##row))
#define MONO16A1(row) ((U16)mono16[*S.y##row++] | A1(*S.a##row++))
#define MONO16(row) ((U16)mono16[*S.y##row++])
#define MONO16A4(row) ((U16)mono16[*S.y##row++] | (U16)clamp_a4[*S.a##row++])

#define PUT16(p, c) (*(U16 *)(p) = (c))
#define PUT16_2W(p, c) (PUT16(p, c), PUT16((p) + 2, c))
#define PUT16_2H(p, c) (PUT16(p, c), PUT16((p) + S.pitch, c))
#define PUT16_2WH(p, c) (PUT16(p, c), PUT16((p) + 2, c), PUT16((p) + S.pitch, c), PUT16((p) + S.pitch + 2, c))

// the 16-bit edges
#define EDGEROW16(name, PIX, PUT, STEP, ADV)                             \
EDGEFN void name(U32 x, U32 n)                                           \
{                                                                        \
  U32 i = x;                                                             \
                                                                         \
  while (n)                                                              \
  {                                                                      \
    S32 yo;                                                              \
    U16 c;                                                               \
    UVOFFSETS;                                                           \
                                                                         \
    yo = ytable[*S.y0++];                                                \
    c = PIX(yo, 0);                                                      \
    PUT(S.out0, c);                                                      \
    ADV(0);                                                              \
    S.out0 += STEP;                                                      \
    if (!(++i & 1))                                                      \
    {                                                                    \
      S.u++;                                                             \
      S.v++;                                                             \
    }                                                                    \
    --n;                                                                 \
  }                                                                      \
}

#define EDGECOL16(name, PIX, PUT, STEP, ADV)                             \
EDGEFN S32 name(U32 n, S32 x)                                            \
{                                                                        \
  S32 col = x;                                                           \
  U32 i = n;                                                             \
                                                                         \
  do                                                                     \
  {                                                                      \
    S32 yo;                                                              \
    U16 c;                                                               \
    UVOFFSETS;                                                           \
                                                                         \
    yo = ytable[*S.y0++];                                                \
    c = PIX(yo, 0);                                                      \
    PUT(S.out0, c);                                                      \
    ADV(0);                                                              \
    yo = ytable[*S.y1++];                                                \
    c = PIX(yo, 1);                                                      \
    PUT(S.out1, c);                                                      \
    ADV(1);                                                              \
    S.out0 += STEP;                                                      \
    S.out1 += STEP;                                                      \
    if (!(++col & 1))                                                    \
    {                                                                    \
      S.u++;                                                             \
      S.v++;                                                             \
    }                                                                    \
  } while (--i);                                                         \
  return col;                                                            \
}

#define EDGEROWM16(name, MONO, PUT, STEP)                                \
EDGEFN void name(U32 x, U32 n)                                           \
{                                                                        \
  while (n)                                                              \
  {                                                                      \
    U16 c = MONO(0);                                                     \
                                                                         \
    PUT(S.out0, c);                                                      \
    S.out0 += STEP;                                                      \
    --n;                                                                 \
  }                                                                      \
}

#define EDGECOLM16(name, MONO, PUT, STEP)                                \
EDGEFN S32 name(U32 n, S32 x)                                            \
{                                                                        \
  U32 i = n;                                                             \
                                                                         \
  do                                                                     \
  {                                                                      \
    U16 c = MONO(0);                                                     \
                                                                         \
    PUT(S.out0, c);                                                      \
    c = MONO(1);                                                         \
    PUT(S.out1, c);                                                      \
    S.out0 += STEP;                                                      \
    S.out1 += STEP;                                                      \
  } while (--i);                                                         \
  return n + x;                                                          \
}

// YUY2: one dword holds two pixels (Y0 U Y1 V); the edges go two pixels
// at a time, the mono ones with U and V at 0x80
#define YUY2M(y0, y1) (((U32)(y1) << 16) | (y0) | 0x80008000)
// the next two pixels with the same U and V
#define YUY2NEXT(c, y0, y1) (((c) & 0xff00ff00) | ((U32)(y1) << 16) | (y0))
#define YUY2(y0, u, y1, v) (((((((U32)(v) << 8) | (y1)) << 8) | (u)) << 8) | (y0))

#define SWAPTABLES(a,b) { U32 *p=YUVTables[a]; U32 i=256; do { U32 s=*p; *p=p[((b)-(a))*256]; p[((b)-(a))*256]=s; ++p; } while (--i); }

// match: _FreeYUVGlobalMemory @ 0x0034A300
void FreeYUVGlobalMemory(void)
{
  if (z2hbuf1)
  {
    radfree(z2hbuf1);
    z2hbuf1 = 0;
    z2hsize = 0;
  }
}

// match: ?zoom2heven@@YGXJ@Z @ 0x0034A330
EDGEFN void __stdcall zoom2heven(S32 n)
{
  U8 *out0 = S.out0;
  U8 *out1 = S.out1;
  U8 *y0 = S.y0;
  U8 *y1 = S.y1;
  U8 *a0 = S.a0;
  U8 *a1 = S.a1;
  U8 *u = S.u;
  U8 *v = S.v;
  S32 adv;

  EVENx(n);
  adv = S.out1 - out1;
  S.out0 = out0 + S.pitch;
  S.out1 = out1 + S.pitch;
  S.y1 = y1;
  S.a0 = a0;
  S.a1 = a1;
  S.y0 = y0;
  S.u = u;
  S.v = v;
  EVENx(n);
  S.out0 = out0 + adv;
  S.out1 = out1 + adv;
}

// match: ?zoom2hodd@@YGXJ@Z @ 0x0034A400
EDGEFN void __stdcall zoom2hodd(S32 n)
{
  U8 *out0 = S.out0;
  U8 *out1 = S.out1;
  U8 *y0 = S.y0;
  U8 *y1 = S.y1;
  U8 *a0 = S.a0;
  U8 *a1 = S.a1;
  U8 *u = S.u;
  U8 *v = S.v;
  S32 adv;

  ODDx(n);
  adv = S.out1 - out1;
  S.out0 = out0 + S.pitch;
  S.out1 = out1 + S.pitch;
  S.y1 = y1;
  S.a0 = a0;
  S.a1 = a1;
  S.y0 = y0;
  S.u = u;
  S.v = v;
  ODDx(n);
  S.out0 = out0 + adv;
  S.out1 = out1 + adv;
}

// match: ?zoom2hevenbuf@@YGXJ@Z @ 0x0034A4D0
EDGEFN void __stdcall zoom2hevenbuf(S32 n)
{
  U8 *out0 = S.out0;
  U8 *out1 = S.out1;
  U32 len;

  S.out0 = (U8 *)z2hbuf1;
  S.out1 = z2hbuf2;
  EVENx(n);
  len = S.out0 - (U8 *)z2hbuf1;
  memcpy(out0, z2hbuf1, len);
  memcpy(out0 + S.pitch, z2hbuf1, len);
  memcpy(out1, z2hbuf2, len);
  memcpy(out1 + S.pitch, z2hbuf2, len);
  S.out0 = out0 + len;
  S.out1 = out1 + len;
}

// match: ?zoom2hoddbuf@@YGXJ@Z @ 0x0034A590
EDGEFN void __stdcall zoom2hoddbuf(S32 n)
{
  U8 *out0 = S.out0;
  U8 *out1 = S.out1;
  U32 len;

  S.out0 = (U8 *)z2hbuf1;
  S.out1 = z2hbuf2;
  ODDx(n);
  len = S.out0 - (U8 *)z2hbuf1;
  memcpy(out0, z2hbuf1, len);
  memcpy(out0 + S.pitch, z2hbuf1, len);
  memcpy(out1, z2hbuf2, len);
  memcpy(out1 + S.pitch, z2hbuf2, len);
  S.out0 = out0 + len;
  S.out1 = out1 + len;
}

// match: ?checktime@@YAXK@Z @ 0x0034A650
static void checktime(U32 cycles)
{
  U32 t = *dbltimeaddr;

  if (!(t & 2))
  {
    U32 count = (t >> 2) & 0x3f;

    if (cycles < (t >> 8))
    {
      if (count == 0)
      {
        *dbltimeaddr = 3;
        testing = 0;
        EVEN = zoom2hevenbuf;
        ODD = zoom2hoddbuf;
      }
      else
      {
        *dbltimeaddr = (((count - 1) & 0x3f) << 2) | 2;
        EVENt = zoom2heven;
        ODDt = zoom2hodd;
      }
    }
    else
    {
      if (count == 0x3f)
      {
        *dbltimeaddr = 1;
        testing = 0;
        EVEN = zoom2heven;
        ODD = zoom2hodd;
      }
      else
      {
        *dbltimeaddr = (((count + 1) & 0x3f) << 2) | 2;
        EVENt = zoom2heven;
        ODDt = zoom2hodd;
      }
    }
  }
  else
  {
    *dbltimeaddr = (t & 0xfd) | (cycles << 8);
    EVENt = zoom2hevenbuf;
    ODDt = zoom2hoddbuf;
  }
}

// match: ?timedbleven@@YGXJ@Z @ 0x0034A730
EDGEFN void __stdcall timedbleven(S32 n)
{
  U32 cycles;

  RADCycleTimerStartAddr(&cycles);
  EVENt(n);
  RADCycleTimerDeltaAddr(&cycles);
  checktime(cycles);
}

// match: ?timedblodd@@YGXJ@Z @ 0x0034A770
EDGEFN void __stdcall timedblodd(S32 n)
{
  U32 cycles;

  RADCycleTimerStartAddr(&cycles);
  ODDt(n);
  RADCycleTimerDeltaAddr(&cycles);
  checktime(cycles);
}

// match: ?dorightedge@@YAXXZ @ 0x0034AC40
EDGEFN void dorightedge(void)
{
  U32 *addr = alnaddr;
  U32 t = *addr;

  if (t & 4)
  {
    RADCycleTimerDeltaAddr(&lastleft);
    if (t & 2)
    {
      U32 count = (t >> 3) & 0x1f;

      if (lastleft < (t >> 8))
      {
        if (count == 0)
          *addr = 3;
        else
          *addr = ((count - 1) & 0x1f) << 3;
      }
      else
      {
        if (count == 0x1f)
          *addr = 1;
        else
          *addr = ((count + 1) & 0x1f) << 3;
      }
    }
    else
      *addr = (lastleft << 8) | (t & 0xfd) | 2;
  }
}

// match: ?checkrdtsc@@YAXXZ @ 0x0034BB10
// (its __try's scope table, .rdata)
// match: $T3588 @ 0x003EEDF0
EDGEFN void checkrdtsc(void)
{
  rdtscavail = -1;
  __try
  {
    __asm rdtsc
    rdtscavail = 1;
  }
  __except (1)
  {
    rdtscavail = -1;
  }
}


#pragma code_seg("BINK32")
// match: ?dounaligned32rowm2w@@YAXKK@Z @ 0x0034E020
EDGEFN void dounaligned32rowm2w(U32 x, U32 n)
{
  while (n)
  {
    U32 c = mono32[*S.y0++];

    PUT32(S.out0, c);
    PUT32(S.out0 + 4, c);
    S.out0 += 8;
    --n;
  }
}

// match: ?dounaligned32colm2w@@YAJKJ@Z @ 0x0034E070
EDGEFN S32 dounaligned32colm2w(U32 n, S32 x)
{
  U32 i = n;

  do
  {
    U32 c = mono32[*S.y0++];

    PUT32(S.out0, c);
    PUT32(S.out0 + 4, c);
    c = mono32[*S.y1++];
    PUT32(S.out1, c);
    PUT32(S.out1 + 4, c);
    S.out0 += 8;
    S.out1 += 8;
  } while (--i);
  return n + x;
}

// match: ?dounaligned32rowm2h@@YAXKK@Z @ 0x0034E100
EDGEFN void dounaligned32rowm2h(U32 x, U32 n)
{
  while (n)
  {
    U32 c = mono32[*S.y0++];

    PUT32(S.out0, c);
    PUT32(S.out0 + S.pitch, c);
    S.out0 += 4;
    --n;
  }
}

// match: ?dounaligned32colm2h@@YAJKJ@Z @ 0x0034E160
EDGEFN S32 dounaligned32colm2h(U32 n, S32 x)
{
  U32 i = n;

  do
  {
    U32 c = mono32[*S.y0++];

    PUT32(S.out0, c);
    PUT32(S.out0 + S.pitch, c);
    c = mono32[*S.y1++];
    PUT32(S.out1, c);
    PUT32(S.out1 + S.pitch, c);
    S.out0 += 4;
    S.out1 += 4;
  } while (--i);
  return n + x;
}

// match: ?dounaligned32rowm2wh@@YAXKK@Z @ 0x0034E200
EDGEFN void dounaligned32rowm2wh(U32 x, U32 n)
{
  while (n)
  {
    U32 c = mono32[*S.y0++];

    PUT32(S.out0, c);
    PUT32(S.out0 + 4, c);
    PUT32(S.out0 + S.pitch, c);
    PUT32(S.out0 + S.pitch + 4, c);
    S.out0 += 8;
    --n;
  }
}

// match: ?dounaligned32colm2wh@@YAJKJ@Z @ 0x0034E270
EDGEFN S32 dounaligned32colm2wh(U32 n, S32 x)
{
  U32 i = n;

  do
  {
    U32 c = mono32[*S.y0++];

    PUT32(S.out0, c);
    PUT32(S.out0 + 4, c);
    PUT32(S.out0 + S.pitch, c);
    PUT32(S.out0 + S.pitch + 4, c);
    c = mono32[*S.y1++];
    PUT32(S.out1, c);
    PUT32(S.out1 + 4, c);
    PUT32(S.out1 + S.pitch, c);
    PUT32(S.out1 + S.pitch + 4, c);
    S.out0 += 8;
    S.out1 += 8;
  } while (--i);
  return n + x;
}

// match: ?dounaligned32row2w@@YAXKK@Z @ 0x0034E340
EDGEFN void dounaligned32row2w(U32 x, U32 n)
{
  U32 i = x;

  while (n)
  {
    U32 *yt;
    U32 c;
    U32 b = YUVTables[0][*S.u];
    U32 g = YUVTables[2][*S.u] + YUVTables[1][*S.v];
    U32 r = YUVTables[3][*S.v];

    yt = clamp_ytable[*S.y0++];
    c = YUV32(yt, r, g, b);
    PUT32(S.out0, c);
    PUT32(S.out0 + 4, c);
    S.out0 += 8;
    if (!(++i & 1))
    {
      S.u++;
      S.v++;
    }
    --n;
  }
}

// match: ?dounaligned32col2w@@YAJKJ@Z @ 0x0034E410
EDGEFN S32 dounaligned32col2w(U32 n, S32 x)
{
  do
  {
    U32 *yt;
    U32 c;
    U32 b = YUVTables[0][*S.u];
    U32 g = YUVTables[2][*S.u] + YUVTables[1][*S.v];
    U32 r = YUVTables[3][*S.v];

    yt = clamp_ytable[*S.y0++];
    c = YUV32(yt, r, g, b);
    PUT32(S.out0, c);
    PUT32(S.out0 + 4, c);
    yt = clamp_ytable[*S.y1++];
    c = YUV32(yt, r, g, b);
    PUT32(S.out1, c);
    PUT32(S.out1 + 4, c);
    S.out0 += 8;
    S.out1 += 8;
    if (!(++x & 1))
    {
      S.u++;
      S.v++;
    }
  } while (--n);
  return x;
}

// match: ?dounaligned32row2h@@YAXKK@Z @ 0x0034E510
EDGEROW(dounaligned32row2h, PIX32, PUT32_2H, 4, NOADV)
// match: ?dounaligned32col2h@@YAJKJ@Z @ 0x0034E5E0
EDGECOL(dounaligned32col2h, PIX32, PUT32_2H, 4, NOADV)
// match: ?dounaligned32row2wh@@YAXKK@Z @ 0x0034E700
EDGEROW(dounaligned32row2wh, PIX32, PUT32_2WH, 8, NOADV)
// match: ?dounaligned32col2wh@@YAJKJ@Z @ 0x0034E7F0
EDGECOL(dounaligned32col2wh, PIX32, PUT32_2WH, 8, NOADV)

// match: ?dounaligned32row@@YAXKK@Z @ 0x0034EA20
EDGEROW(dounaligned32row, PIX32, PUT32, 4, NOADV)
// match: ?dounaligned32col@@YAJKJ@Z @ 0x0034EAE0
EDGECOL(dounaligned32col, PIX32, PUT32, 4, NOADV)

#pragma code_seg("BINK32A")
// match: ?dounaligned32arowm2w@@YAXKK@Z @ 0x0034F1C0
EDGEROWM(dounaligned32arowm2w, MONO32A, PUT32_2W, 8)
// match: ?dounaligned32acolm2w@@YAJKJ@Z @ 0x0034F230
EDGECOLM(dounaligned32acolm2w, MONO32A, PUT32_2W, 8)
// match: ?dounaligned32arowm2h@@YAXKK@Z @ 0x0034F2F0
EDGEROWM(dounaligned32arowm2h, MONO32A, PUT32_2H, 4)
// match: ?dounaligned32acolm2h@@YAJKJ@Z @ 0x0034F360
EDGECOLM(dounaligned32acolm2h, MONO32A, PUT32_2H, 4)
// match: ?dounaligned32arowm2wh@@YAXKK@Z @ 0x0034F420
EDGEROWM(dounaligned32arowm2wh, MONO32A, PUT32_2WH, 8)
// match: ?dounaligned32acolm2wh@@YAJKJ@Z @ 0x0034F4B0
EDGECOLM(dounaligned32acolm2wh, MONO32A, PUT32_2WH, 8)
// match: ?dounaligned32arow2w@@YAXKK@Z @ 0x0034F5B0
EDGEROW(dounaligned32arow2w, PIX32A, PUT32_2W, 8, NOADV)
// match: ?dounaligned32acol2w@@YAJKJ@Z @ 0x0034F690
EDGECOL(dounaligned32acol2w, PIX32A, PUT32_2W, 8, NOADV)
// match: ?dounaligned32arow2h@@YAXKK@Z @ 0x0034F7C0
EDGEROW(dounaligned32arow2h, PIX32A, PUT32_2H, 4, NOADV)
// match: ?dounaligned32acol2h@@YAJKJ@Z @ 0x0034F8B0
EDGECOL(dounaligned32acol2h, PIX32A, PUT32_2H, 4, NOADV)
// match: ?dounaligned32arow2wh@@YAXKK@Z @ 0x0034F9F0
EDGEROW(dounaligned32arow2wh, PIX32A, PUT32_2WH, 8, NOADV)
// match: ?dounaligned32acol2wh@@YAJKJ@Z @ 0x0034FAF0
EDGECOL(dounaligned32acol2wh, PIX32A, PUT32_2WH, 8, NOADV)
// match: ?dounaligned32arowm@@YAXKK@Z @ 0x0034FC60
EDGEFN void dounaligned32arowm(U32 x, U32 n)
{
  while (n)
  {
    PUT32(S.out0, mono32[*S.y0] | ((U32)*S.a0 << 24));
    S.a0++;
    S.y0++;
    S.out0 += 4;
    --n;
  }
}

// match: ?dounaligned32acolm@@YAJKJ@Z @ 0x0034FCD0
EDGEFN S32 dounaligned32acolm(U32 n, S32 x)
{
  U32 i = n;

  do
  {
    PUT32(S.out0, mono32[*S.y0] | ((U32)*S.a0 << 24));
    S.a0++;
    S.y0++;
    PUT32(S.out1, mono32[*S.y1] | ((U32)*S.a1 << 24));
    S.a1++;
    S.y1++;
    S.out0 += 4;
    S.out1 += 4;
  } while (--i);
  return x + n;
}

// match: ?dounaligned32arow@@YAXKK@Z @ 0x0034FD90
EDGEROW(dounaligned32arow, PIX32AP, PUT32, 4, ADVA)
// match: ?dounaligned32acol@@YAJKJ@Z @ 0x0034FE70
EDGECOL(dounaligned32acol, PIX32AP, PUT32, 4, ADVA)

#pragma code_seg("BINK16")
// match: ?dounaligned16rowm2h@@YAXKK@Z @ 0x00350620
EDGEROWM16(dounaligned16rowm2h, MONO16, PUT16_2H, 2)
// match: ?dounaligned16colm2h@@YAJKJ@Z @ 0x00350680
EDGECOLM16(dounaligned16colm2h, MONO16, PUT16_2H, 2)
// match: ?dounaligned16rowm2w@@YAXKK@Z @ 0x00350720
EDGEROWM16(dounaligned16rowm2w, MONO16, PUT16_2W, 4)
// match: ?dounaligned16colm2w@@YAJKJ@Z @ 0x00350770
EDGECOLM16(dounaligned16colm2w, MONO16, PUT16_2W, 4)
// match: ?dounaligned16rowm2wh@@YAXKK@Z @ 0x00350800
EDGEROWM16(dounaligned16rowm2wh, MONO16, PUT16_2WH, 4)
// match: ?dounaligned16colm2wh@@YAJKJ@Z @ 0x00350870
EDGECOLM16(dounaligned16colm2wh, MONO16, PUT16_2WH, 4)
// match: ?dounaligned16row2h@@YAXKK@Z @ 0x00350950
EDGEROW16(dounaligned16row2h, PIX16, PUT16_2H, 2, NOADV)
// match: ?dounaligned16col2h@@YAJKJ@Z @ 0x00350A30
EDGECOL16(dounaligned16col2h, PIX16, PUT16_2H, 2, NOADV)
// match: ?dounaligned16row2w@@YAXKK@Z @ 0x00350B60
EDGEROW16(dounaligned16row2w, PIX16, PUT16_2W, 4, NOADV)
// match: ?dounaligned16col2w@@YAJKJ@Z @ 0x00350C40
EDGECOL16(dounaligned16col2w, PIX16, PUT16_2W, 4, NOADV)
// match: ?dounaligned16row2wh@@YAXKK@Z @ 0x00350D70
EDGEROW16(dounaligned16row2wh, PIX16, PUT16_2WH, 4, NOADV)
// match: ?dounaligned16col2wh@@YAJKJ@Z @ 0x00350E70
EDGECOL16(dounaligned16col2wh, PIX16, PUT16_2WH, 4, NOADV)
// match: ?dounaligned16rowm@@YAXKK@Z @ 0x00350FE0
EDGEROWM16(dounaligned16rowm, MONO16, PUT16, 2)
// match: ?dounaligned16colm@@YAJKJ@Z @ 0x00351030
EDGECOLM16(dounaligned16colm, MONO16, PUT16, 2)
// match: ?dounaligned16row@@YAXKK@Z @ 0x003510B0
EDGEROW16(dounaligned16row, PIX16, PUT16, 2, NOADV)
// match: ?dounaligned16col@@YAJKJ@Z @ 0x00351180
EDGECOL16(dounaligned16col, PIX16, PUT16, 2, NOADV)

#pragma code_seg("BINK4444")
// match: ?dounaligned16a4rowm2h@@YAXKK@Z @ 0x00351880
EDGEROWM16(dounaligned16a4rowm2h, MONO16A4, PUT16_2H, 2)
// match: ?dounaligned16a4colm2h@@YAJKJ@Z @ 0x003518F0
EDGECOLM16(dounaligned16a4colm2h, MONO16A4, PUT16_2H, 2)
// match: ?dounaligned16a4rowm2w@@YAXKK@Z @ 0x003519D0
EDGEROWM16(dounaligned16a4rowm2w, MONO16A4, PUT16_2W, 4)
// match: ?dounaligned16a4colm2w@@YAJKJ@Z @ 0x00351A40
EDGECOLM16(dounaligned16a4colm2w, MONO16A4, PUT16_2W, 4)
// match: ?dounaligned16a4rowm2wh@@YAXKK@Z @ 0x00351B10
EDGEROWM16(dounaligned16a4rowm2wh, MONO16A4, PUT16_2WH, 4)
// match: ?dounaligned16a4colm2wh@@YAJKJ@Z @ 0x00351BA0
EDGECOLM16(dounaligned16a4colm2wh, MONO16A4, PUT16_2WH, 4)
// match: ?dounaligned16a4row2h@@YAXKK@Z @ 0x00351CB0
EDGEROW16(dounaligned16a4row2h, PIX16A4, PUT16_2H, 2, NOADV)
// match: ?dounaligned16a4col2h@@YAJKJ@Z @ 0x00351DA0
EDGECOL16(dounaligned16a4col2h, PIX16A4, PUT16_2H, 2, NOADV)
// match: ?dounaligned16a4row2w@@YAXKK@Z @ 0x00351F00
EDGEROW16(dounaligned16a4row2w, PIX16A4, PUT16_2W, 4, NOADV)
// match: ?dounaligned16a4col2w@@YAJKJ@Z @ 0x00351FF0
EDGECOL16(dounaligned16a4col2w, PIX16A4, PUT16_2W, 4, NOADV)
// match: ?dounaligned16a4row2wh@@YAXKK@Z @ 0x00352150
EDGEROW16(dounaligned16a4row2wh, PIX16A4, PUT16_2WH, 4, NOADV)
// match: ?dounaligned16a4col2wh@@YAJKJ@Z @ 0x00352260
EDGECOL16(dounaligned16a4col2wh, PIX16A4, PUT16_2WH, 4, NOADV)
// match: ?dounaligned16a4rowm@@YAXKK@Z @ 0x00352400
EDGEROWM16(dounaligned16a4rowm, MONO16A4, PUT16, 2)
// match: ?dounaligned16a4colm@@YAJKJ@Z @ 0x00352460
EDGECOLM16(dounaligned16a4colm, MONO16A4, PUT16, 2)
// match: ?dounaligned16a4row@@YAXKK@Z @ 0x00352520
EDGEROW16(dounaligned16a4row, PIX16A4P, PUT16, 2, ADVA)
// match: ?dounaligned16a4col@@YAJKJ@Z @ 0x00352610
EDGECOL16(dounaligned16a4col, PIX16A4P, PUT16, 2, ADVA)

#pragma code_seg("BINK5551")
// match: ?dounaligned16a1rowm2h@@YAXKK@Z @ 0x00352D60
EDGEROWM16(dounaligned16a1rowm2h, MONO16A1, PUT16_2H, 2)
// match: ?dounaligned16a1colm2h@@YAJKJ@Z @ 0x00352DD0
EDGECOLM16(dounaligned16a1colm2h, MONO16A1, PUT16_2H, 2)
// match: ?dounaligned16a1rowm2w@@YAXKK@Z @ 0x00352EB0
EDGEROWM16(dounaligned16a1rowm2w, MONO16A1, PUT16_2W, 4)
// match: ?dounaligned16a1colm2w@@YAJKJ@Z @ 0x00352F20
EDGECOLM16(dounaligned16a1colm2w, MONO16A1, PUT16_2W, 4)
// match: ?dounaligned16a1rowm2wh@@YAXKK@Z @ 0x00352FF0
EDGEROWM16(dounaligned16a1rowm2wh, MONO16A1, PUT16_2WH, 4)
// match: ?dounaligned16a1colm2wh@@YAJKJ@Z @ 0x00353080
EDGECOLM16(dounaligned16a1colm2wh, MONO16A1, PUT16_2WH, 4)
// match: ?dounaligned16a1row2h@@YAXKK@Z @ 0x00353190
EDGEROW16(dounaligned16a1row2h, PIX16A1, PUT16_2H, 2, NOADV)
// match: ?dounaligned16a1col2h@@YAJKJ@Z @ 0x00353280
EDGECOL16(dounaligned16a1col2h, PIX16A1, PUT16_2H, 2, NOADV)
// match: ?dounaligned16a1row2w@@YAXKK@Z @ 0x00353400
EDGEROW16(dounaligned16a1row2w, PIX16A1, PUT16_2W, 4, NOADV)
// match: ?dounaligned16a1col2w@@YAJKJ@Z @ 0x003534F0
EDGECOL16(dounaligned16a1col2w, PIX16A1, PUT16_2W, 4, NOADV)
// match: ?dounaligned16a1row2wh@@YAXKK@Z @ 0x00353660
EDGEROW16(dounaligned16a1row2wh, PIX16A1, PUT16_2WH, 4, NOADV)
// match: ?dounaligned16a1col2wh@@YAJKJ@Z @ 0x00353770
EDGECOL16(dounaligned16a1col2wh, PIX16A1, PUT16_2WH, 4, NOADV)
// match: ?dounaligned16a1rowm@@YAXKK@Z @ 0x00353920
EDGEROWM16(dounaligned16a1rowm, MONO16A1, PUT16, 2)
// match: ?dounaligned16a1colm@@YAJKJ@Z @ 0x00353980
EDGECOLM16(dounaligned16a1colm, MONO16A1, PUT16, 2)
// match: ?dounaligned16a1row@@YAXKK@Z @ 0x00353A30
EDGEROW16(dounaligned16a1row, PIX16A1P, PUT16, 2, ADVA)
// match: ?dounaligned16a1col@@YAJKJ@Z @ 0x00353B20
EDGECOL16(dounaligned16a1col, PIX16A1P, PUT16, 2, ADVA)

#pragma code_seg("BINKYUY2")
// match: ?dounalignedYUY2rowm2wh@@YAXKK@Z @ 0x00354280
EDGEFN void dounalignedYUY2rowm2wh(U32 x, U32 n)
{
  S32 i;

  for (i = (S32)n - 2; i >= 0; i -= 2)
  {
    U32 c0 = YUY2M(S.y0[0], S.y0[0]);
    U32 c1 = YUY2M(S.y0[1], S.y0[1]);

    PUT32(S.out0, c0);
    PUT32(S.out0 + 4, c1);
    PUT32(S.out0 + S.pitch, c0);
    PUT32(S.out0 + S.pitch + 4, c1);
    S.y0 += 2;
    S.out0 += 8;
  }
}

// match: ?dounalignedYUY2rowm2w@@YAXKK@Z @ 0x00354420
EDGEFN void dounalignedYUY2rowm2w(U32 x, U32 n)
{
  S32 i;

  for (i = (S32)n - 2; i >= 0; i -= 2)
  {
    U32 c = YUY2M(S.y0[0], S.y0[0]);

    PUT32(S.out0, c);
    c = YUY2M(S.y0[1], S.y0[1]);
    S.y0 += 2;
    PUT32(S.out0 + 4, c);
    S.out0 += 8;
  }
}

// match: ?dounalignedYUY2rowm2h@@YAXKK@Z @ 0x00354560
EDGEFN void dounalignedYUY2rowm2h(U32 x, U32 n)
{
  S32 i;

  for (i = (S32)n - 2; i >= 0; i -= 2)
  {
    U32 c = YUY2M(S.y0[0], S.y0[1]);

    S.y0 += 2;
    PUT32(S.out0, c);
    PUT32(S.out0 + S.pitch, c);
    S.out0 += 4;
  }
}

// match: ?dounalignedYUY2row2wh@@YAXKK@Z @ 0x00354670
EDGEFN void dounalignedYUY2row2wh(U32 x, U32 n)
{
  S32 i;

  for (i = (S32)n - 2; i >= 0; i -= 2)
  {
    U32 c0 = YUY2(S.y0[0], *S.u, S.y0[0], *S.v);
    U32 c1;

    S.v++;
    S.u++;
    c1 = (c0 & 0xff00ff00) | ((U32)S.y0[1] << 16) | S.y0[1];
    PUT32(S.out0, c0);
    PUT32(S.out0 + 4, c1);
    PUT32(S.out0 + S.pitch, c0);
    PUT32(S.out0 + S.pitch + 4, c1);
    S.y0 += 2;
    S.out0 += 8;
  }
}

// match: ?dounalignedYUY2row2w@@YAXKK@Z @ 0x00354860
EDGEFN void dounalignedYUY2row2w(U32 x, U32 n)
{
  S32 i;

  for (i = (S32)n - 2; i >= 0; i -= 2)
  {
    U32 c = YUY2(S.y0[0], *S.u, S.y0[0], *S.v);

    S.v++;
    S.u++;
    PUT32(S.out0, c);
    c = (c & 0xff00ff00) | ((U32)S.y0[1] << 16) | S.y0[1];
    S.y0 += 2;
    PUT32(S.out0 + 4, c);
    S.out0 += 8;
  }
}

// match: ?dounalignedYUY2row2h@@YAXKK@Z @ 0x00354A00
EDGEFN void dounalignedYUY2row2h(U32 x, U32 n)
{
  S32 i;

  for (i = (S32)n - 2; i >= 0; i -= 2)
  {
    U32 c = YUY2(S.y0[0], *S.u, S.y0[1], *S.v);

    S.y0 += 2;
    S.v++;
    S.u++;
    PUT32(S.out0, c);
    PUT32(S.out0 + S.pitch, c);
    S.out0 += 4;
  }
}

// match: ?dounalignedYUY2rowm@@YAXKK@Z @ 0x00354B60
EDGEFN void dounalignedYUY2rowm(U32 x, U32 n)
{
  S32 i;

  for (i = (S32)n - 2; i >= 0; i -= 2)
  {
    U32 c = YUY2M(S.y0[0], S.y0[1]);

    S.y0 += 2;
    PUT32(S.out0, c);
    S.out0 += 4;
  }
}

// match: ?dounalignedYUY2row@@YAXKK@Z @ 0x00354C40
EDGEFN void dounalignedYUY2row(U32 x, U32 n)
{
  S32 i;

  for (i = (S32)n - 2; i >= 0; i -= 2)
  {
    U32 c = YUY2(S.y0[0], *S.u, S.y0[1], *S.v);

    S.v++;
    S.u++;
    S.y0 += 2;
    PUT32(S.out0, c);
    S.out0 += 4;
  }
}

// match: ?dounalignedYUY2colm2wh@@YAJKJ@Z @ 0x00354310
EDGEFN S32 dounalignedYUY2colm2wh(U32 n, S32 x)
{
  U32 i = n;

  do
  {
    U32 c0 = YUY2M(S.y0[0], S.y0[0]);
    U32 c1 = YUY2M(S.y0[1], S.y0[1]);

    PUT32(S.out0, c0);
    PUT32(S.out0 + 4, c1);
    PUT32(S.out0 + S.pitch, c0);
    PUT32(S.out0 + S.pitch + 4, c1);
    c0 = YUY2M(S.y1[0], S.y1[0]);
    c1 = YUY2M(S.y1[1], S.y1[1]);
    PUT32(S.out1, c0);
    PUT32(S.out1 + 4, c1);
    PUT32(S.out1 + S.pitch, c0);
    PUT32(S.out1 + S.pitch + 4, c1);
    S.y0 += 2;
    S.y1 += 2;
    S.out0 += 8;
    S.out1 += 8;
  } while ((S32)(i -= 2) > 0);
  return x + n;
}

// match: ?dounalignedYUY2colm2w@@YAJKJ@Z @ 0x00354490
EDGEFN S32 dounalignedYUY2colm2w(U32 n, S32 x)
{
  U32 i = n;

  do
  {
    U32 c = YUY2M(S.y0[0], S.y0[0]);

    PUT32(S.out0, c);
    c = YUY2M(S.y0[1], S.y0[1]);
    S.y0 += 2;
    PUT32(S.out0 + 4, c);
    c = YUY2M(S.y1[0], S.y1[0]);
    PUT32(S.out1, c);
    c = YUY2M(S.y1[1], S.y1[1]);
    S.y1 += 2;
    PUT32(S.out1 + 4, c);
    S.out0 += 8;
    S.out1 += 8;
  } while ((S32)(i -= 2) > 0);
  return n + x;
}

// match: ?dounalignedYUY2colm2h@@YAJKJ@Z @ 0x003545C0
EDGEFN S32 dounalignedYUY2colm2h(U32 n, S32 x)
{
  U32 i = n;

  do
  {
    U32 c = YUY2M(S.y0[0], S.y0[1]);

    S.y0 += 2;
    PUT32(S.out0, c);
    PUT32(S.out0 + S.pitch, c);
    c = YUY2M(S.y1[0], S.y1[1]);
    S.y1 += 2;
    PUT32(S.out1, c);
    PUT32(S.out1 + S.pitch, c);
    S.out0 += 4;
    S.out1 += 4;
  } while ((S32)(i -= 2) > 0);
  return n + x;
}

// match: ?dounalignedYUY2col2wh@@YAJKJ@Z @ 0x00354730
EDGEFN S32 dounalignedYUY2col2wh(U32 n, S32 x)
{
  U32 i = n;

  do
  {
    U32 c0 = YUY2(S.y0[0], *S.u, S.y0[0], *S.v);
    U32 c1;

    S.v++;
    S.u++;
    c1 = YUY2NEXT(c0, S.y0[1], S.y0[1]);
    PUT32(S.out0, c0);
    PUT32(S.out0 + 4, c1);
    PUT32(S.out0 + S.pitch, c0);
    PUT32(S.out0 + S.pitch + 4, c1);
    c0 = YUY2NEXT(c0, S.y1[0], S.y1[0]);
    c1 = YUY2NEXT(c1, S.y1[1], S.y1[1]);
    PUT32(S.out1, c0);
    PUT32(S.out1 + 4, c1);
    PUT32(S.out1 + S.pitch, c0);
    PUT32(S.out1 + S.pitch + 4, c1);
    S.y0 += 2;
    S.y1 += 2;
    S.out0 += 8;
    S.out1 += 8;
  } while ((S32)(i -= 2) > 0);
  return n + x;
}

// match: ?dounalignedYUY2col2w@@YAJKJ@Z @ 0x00354900
EDGEFN S32 dounalignedYUY2col2w(U32 n, S32 x)
{
  U32 i = n;

  do
  {
    U32 c = YUY2(S.y0[0], *S.u, S.y0[0], *S.v);

    S.v++;
    S.u++;
    PUT32(S.out0, c);
    c = YUY2NEXT(c, S.y0[1], S.y0[1]);
    S.y0 += 2;
    PUT32(S.out0 + 4, c);
    c = YUY2NEXT(c, S.y1[0], S.y1[0]);
    PUT32(S.out1, c);
    c = YUY2NEXT(c, S.y1[1], S.y1[1]);
    S.y1 += 2;
    PUT32(S.out1 + 4, c);
    S.out0 += 8;
    S.out1 += 8;
  } while ((S32)(i -= 2) > 0);
  return x + n;
}

// match: ?dounalignedYUY2col2h@@YAJKJ@Z @ 0x00354A80
EDGEFN S32 dounalignedYUY2col2h(U32 n, S32 x)
{
  U32 i = n;

  do
  {
    U32 c = YUY2(S.y0[0], *S.u, S.y0[1], *S.v);

    S.y0 += 2;
    S.v++;
    S.u++;
    PUT32(S.out0, c);
    PUT32(S.out0 + S.pitch, c);
    c = YUY2NEXT(c, S.y1[0], S.y1[1]);
    S.y1 += 2;
    PUT32(S.out1, c);
    PUT32(S.out1 + S.pitch, c);
    S.out0 += 4;
    S.out1 += 4;
  } while ((S32)(i -= 2) > 0);
  return x + n;
}

// match: ?dounalignedYUY2colm@@YAJKJ@Z @ 0x00354BB0
EDGEFN S32 dounalignedYUY2colm(U32 n, S32 x)
{
  U32 i = n;

  do
  {
    U32 c = YUY2M(S.y0[0], S.y0[1]);

    S.y0 += 2;
    PUT32(S.out0, c);
    c = YUY2M(S.y1[0], S.y1[1]);
    S.y1 += 2;
    PUT32(S.out1, c);
    S.out0 += 4;
    S.out1 += 4;
  } while ((S32)(i -= 2) > 0);
  return n + x;
}

// match: ?dounalignedYUY2col@@YAJKJ@Z @ 0x00354CB0
EDGEFN S32 dounalignedYUY2col(U32 n, S32 x)
{
  U32 i = n;

  do
  {
    U32 c = YUY2(S.y0[0], *S.u, S.y0[1], *S.v);

    S.y0 += 2;
    S.v++;
    S.u++;
    PUT32(S.out0, c);
    c = YUY2NEXT(c, S.y1[0], S.y1[1]);
    S.y1 += 2;
    PUT32(S.out1, c);
    S.out0 += 4;
    S.out1 += 4;
  } while ((S32)(i -= 2) > 0);
  return x + n;
}

#pragma code_seg("BINK32")
// match: ?dounaligned32rowm@@YAXKK@Z @ 0x0034E940
EDGEFN void dounaligned32rowm(U32 x, U32 n)
{
  while (n)
  {
    PUT32(S.out0, mono32[*S.y0]);
    S.y0++;
    S.out0 += 4;
    --n;
  }
}

// match: ?dounaligned32colm@@YAJKJ@Z @ 0x0034E990
EDGEFN S32 dounaligned32colm(U32 n, S32 x)
{
  U32 i = n;

  do
  {
    PUT32(S.out0, mono32[*S.y0]);
    S.y0++;
    PUT32(S.out1, mono32[*S.y1]);
    S.y1++;
    S.out0 += 4;
    S.out1 += 4;
  } while (--i);
  return x + n;
}

#pragma code_seg("BINK")
#pragma code_seg("BINK")
// setevenodd (0x0034A840) and YUV_blit (0x0034ACD0), whose C does not match, stay binary in
// yuv_asm.asm with the two helpers only setevenodd calls (checkzoombufs, setdbls), and with them YUV_blit_mask (0x0034B150) and the six YUV_blit_* entry points,
// which call them in their register conventions (owner, 2026-10-04: unmatched Bink may be
// binarized); the masked entry points call YUV_blit_mask there.
void YUV_blit_mask(void *dest, U32 destx, U32 desty, U32 destpitch,
  U8 *mask, U32 maskpitch, void *yplane, U32 srcx, U32 srcy, U32 srcw,
  U32 srch, U32 ywidth, U32 yheight, U32 flags, void *aplane, BLITS *b);

#pragma code_seg("BINK32")
// match: _YUV_blit_32bpp_mask@60 @ 0x0034EC20
YUVBLITMASK(YUV_blit_32bpp_mask)
{
 YUV_blit_mask(dest,destx,desty,destpitch,(U8*)mask,maskpitch,yplane,srcx,srcy,srcw,srch,ywidth,yheight,flags,aplane,&blits32);
}

#pragma code_seg("BINK32A")
// match: _YUV_blit_32abpp_mask@60 @ 0x0034FFF0
YUVBLITMASK(YUV_blit_32abpp_mask)
{
 YUV_blit_mask(dest,destx,desty,destpitch,(U8*)mask,maskpitch,yplane,srcx,srcy,srcw,srch,ywidth,yheight,flags,aplane,&blits32a);
}

#pragma code_seg("BINK16")
// match: _YUV_blit_16bpp_mask@60 @ 0x003512E0
YUVBLITMASK(YUV_blit_16bpp_mask)
{
 YUV_blit_mask(dest,destx,desty,destpitch,(U8*)mask,maskpitch,yplane,srcx,srcy,srcw,srch,ywidth,yheight,flags,aplane,&blits16);
}

#pragma code_seg("BINK4444")
// match: _YUV_blit_16a4bpp_mask@60 @ 0x003527B0
YUVBLITMASK(YUV_blit_16a4bpp_mask)
{
 YUV_blit_mask(dest,destx,desty,destpitch,(U8*)mask,maskpitch,yplane,srcx,srcy,srcw,srch,ywidth,yheight,flags,aplane,&blits16a4);
}

#pragma code_seg("BINK5551")
// match: _YUV_blit_16a1bpp_mask@60 @ 0x00353CD0
YUVBLITMASK(YUV_blit_16a1bpp_mask)
{
 YUV_blit_mask(dest,destx,desty,destpitch,(U8*)mask,maskpitch,yplane,srcx,srcy,srcw,srch,ywidth,yheight,flags,aplane,&blits16a1);
}

#pragma code_seg("BINKYUY2")
// match: _YUV_blit_YUY2_mask@60 @ 0x00354DF0
YUVBLITMASK(YUV_blit_YUY2_mask)
{
 YUV_blit_mask(dest,destx,desty,destpitch,(U8*)mask,maskpitch,yplane,srcx,srcy,srcw,srch,ywidth,yheight,flags,aplane,&blitsyuy2);
}

#include "bink.h"
#include "binkint.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x00508254
extern "C" { U32 alignshift; }
// 0x00508258
extern "C" { ROWPAIRFN ODD; }
// 0x0050825C
extern "C" { ROWPAIRFN ODDx; }
// 0x00508260
extern "C" { U32 align; }
// 0x00508264
extern "C" { ROWPAIRFN EVENt; }
// 0x00508268
extern "C" { EDGECOLFN dounalignedcol; }
// 0x0050826C
extern "C" { ROWPAIRFN EVENx; }
// 0x00508270
extern "C" { ROWPAIRFN ODDt; }
// 0x00508274
extern "C" { U32 lastleft; }
// 0x00508278
extern "C" { U32 testing; }
// 0x0050827C
extern "C" { U32 *alnaddr; }
// 0x00508280
extern "C" { ROWPAIRFN EVEN; }
// 0x00508284
extern "C" { U32 alignm1; }
// 0x00508288
extern "C" { EDGEROWFN dounalignedrow; }
// 0x0050828C
extern "C" { U32 *dbltimeaddr; }
// End of its data definitions.

#pragma code_seg("BINK")
extern "C" {
extern S32 rdtscavail;
extern U64 RGBshift[6];
extern U32 pmemwRGB[2], pmemwYscalem[2], pmemw7F00m[2];
extern S32 lastsurface, done32, donetables;
extern S32 ytable_x4[260];
extern U32 clamp_r[772],clamp_g[772],clamp_b[772];
extern U32 clamp_rr[772],clamp_gg[772],clamp_bb[772];
extern U32 clamp32[772], *clamp_ytable[260];
extern U32 YUVTables[8][256],mono16[256],mono16x2[256],mono32[256];
}
void checkrdtsc(void);

#if 0   /* reading context only: the image's YUV_init is yuv_asm.asm's transcription (one definition) */
// Unmatched C context: _YUV_init@4 @ 0x34BB90
void __stdcall YUV_init(U32 surface)
{
  S32 i, v, rmax, gmax, bmax;
  S32 *p;
  if (!rdtscavail) checkrdtsc();
  switch (surface)
  {
  case 8:
  case 9:
    ((U32*)RGBshift)[3*2]=3; ((U32*)RGBshift)[0*2]=0;
    ((U32*)RGBshift)[4*2]=3; ((U32*)RGBshift)[1*2]=5;
    ((U32*)RGBshift)[5*2]=3; ((U32*)RGBshift)[2*2]=10;
    pmemwYscalem[0]=0x25422542; pmemwYscalem[1]=0x25422542;
    pmemw7F00m[0]=0x7fe07fe0; pmemw7F00m[1]=0x7fe07fe0;
    v=0x04210421;
setup16:
  pmemwRGB[0]=v; pmemwRGB[1]=v;
  if (lastsurface!=surface)
  {
    if (lastsurface==-1)
    {
      for (i=0;i<=16;++i) ytable_x4[i]=0;
      p=ytable_x4+17;
      for (i=17;i<=234;++i) *p++=((i-16)*32173/32768)*4;
      for (i=235;i<256;++i) ytable_x4[i]=255*4;
    }
    for(i=0;i<256;++i) clamp_r[i]=0;
    for(i=0;i<256;++i) clamp_r[i+256]=i>>((U32*)RGBshift)[3*2];
    rmax=(1<<(8-((U32*)RGBshift)[3*2]))-1;
    for(i=0;i<256;++i) clamp_r[i+512]=rmax;
    for(i=0;i<256;++i) clamp_g[i]=0;
    for(i=0;i<256;++i) clamp_g[i+256]=(i>>((U32*)RGBshift)[4*2])<<((U32*)RGBshift)[1*2];
    gmax=((1<<(8-((U32*)RGBshift)[4*2]))-1)<<((U32*)RGBshift)[1*2];
    for(i=0;i<256;++i) clamp_g[i+512]=gmax;
    for(i=0;i<256;++i) clamp_b[i]=0;
    for(i=0;i<256;++i) clamp_b[i+256]=(i>>((U32*)RGBshift)[5*2])<<((U32*)RGBshift)[2*2];
    bmax=((1<<(8-((U32*)RGBshift)[5*2]))-1)<<((U32*)RGBshift)[2*2];
    for(i=0;i<256;++i) clamp_b[i+512]=bmax;
    for(i=0;i<256;++i) clamp_rr[i]=0;
    for(i=0;i<256;++i) clamp_rr[i+256]=(i>>((U32*)RGBshift)[3*2])*65537;
    rmax*=65537;
    for(i=0;i<256;++i) clamp_rr[i+512]=rmax;
    for(i=0;i<256;++i) clamp_gg[i]=0;
    for(i=0;i<256;++i) clamp_gg[i+256]=((i>>((U32*)RGBshift)[4*2])<<((U32*)RGBshift)[1*2])*65537;
    gmax*=65537;
    for(i=0;i<256;++i) clamp_gg[i+512]=gmax;
    for(i=0;i<256;++i) clamp_bb[i]=0;
    for(i=0;i<256;++i) clamp_bb[i+256]=((i>>((U32*)RGBshift)[5*2])<<((U32*)RGBshift)[2*2])*65537;
    bmax*=65537;
    for(i=0;i<256;++i) clamp_bb[i+512]=bmax;
    lastsurface=surface;
  }
    goto tables;
  case 10:
    ((U32*)RGBshift)[3*2]=3; ((U32*)RGBshift)[0*2]=0;
    ((U32*)RGBshift)[4*2]=2; ((U32*)RGBshift)[1*2]=5;
    ((U32*)RGBshift)[5*2]=3; ((U32*)RGBshift)[2*2]=11;
    pmemwYscalem[0]=0x25422542; pmemwYscalem[1]=0x25422542;
    pmemw7F00m[0]=0x7fe07fe0; pmemw7F00m[1]=0x7fe07fe0;
    v=0x08410841;
    goto setup16;
  case 7:
    ((U32*)RGBshift)[3*2]=4; ((U32*)RGBshift)[0*2]=0;
    ((U32*)RGBshift)[4*2]=4; ((U32*)RGBshift)[1*2]=4;
    ((U32*)RGBshift)[5*2]=4; ((U32*)RGBshift)[2*2]=8;
    pmemwYscalem[0]=0x12a112a1; pmemwYscalem[1]=0x12a112a1;
    pmemw7F00m[0]=0x7ff07ff0; pmemw7F00m[1]=0x7ff07ff0;
    v=0x01110111;
    goto setup16;
  case 12:
    ((U32*)RGBshift)[3*2]=2; ((U32*)RGBshift)[0*2]=0;
    ((U32*)RGBshift)[4*2]=2; ((U32*)RGBshift)[1*2]=6;
    ((U32*)RGBshift)[5*2]=4; ((U32*)RGBshift)[2*2]=12;
    pmemwYscalem[0]=0x12a112a1; pmemwYscalem[1]=0x12a112a1;
    pmemw7F00m[0]=0x7ff07ff0; pmemw7F00m[1]=0x7ff07ff0;
    v=0x11041104;
    goto setup16;
  case 11:
    ((U32*)RGBshift)[3*2]=2; ((U32*)RGBshift)[0*2]=0;
    ((U32*)RGBshift)[4*2]=3; ((U32*)RGBshift)[1*2]=6;
    ((U32*)RGBshift)[5*2]=3; ((U32*)RGBshift)[2*2]=11;
    pmemwYscalem[0]=0x25422542; pmemwYscalem[1]=0x25422542;
    pmemw7F00m[0]=0x7fe07fe0; pmemw7F00m[1]=0x7fe07fe0;
    v=0x08420842;
    goto setup16;
  default:
    ((U32*)RGBshift)[3*2]=0; ((U32*)RGBshift)[0*2]=0;
    ((U32*)RGBshift)[4*2]=0; ((U32*)RGBshift)[1*2]=0;
    ((U32*)RGBshift)[5*2]=0; ((U32*)RGBshift)[2*2]=0;
    if (done32!=1)
    {
      for (i=0;i<256;++i)
      {
        v=(i-16)*32173;
        v=(v<=0)?0:((v>=219*32173)?255:v/32768);
        clamp_ytable[i]=clamp32+256+v;
        clamp32[i]=0;
        clamp32[i+256]=i;
        clamp32[i+512]=255;
        mono32[i]=v|((v|(v<<8))<<8);
      }
      done32=1;
    }
    goto tables;
  }
tables:
  if (!donetables)
  {
    for (i=0;i<256;++i) YUVTables[1][i]=((128-i)*26635)/32768;
    for (i=0;i<256;++i) YUVTables[2][i]=((128-i)*12804)/32768;
    for (i=0;i<256;++i) YUVTables[3][i]=((i-128)*52253)/32768;
    for (i=0;i<256;++i) YUVTables[0][i]=((i-128)*66084)/32768;
    for (i=0;i<256;++i) YUVTables[5][i]=(YUVTables[1][i]&0xffff)*65537;
    for (i=0;i<256;++i) YUVTables[6][i]=(YUVTables[2][i]&0xffff)*65537;
    for (i=0;i<256;++i) YUVTables[7][i]=(YUVTables[3][i]&0xffff)*65537;
    for (i=0;i<256;++i) YUVTables[4][i]=(YUVTables[0][i]&0xffff)*65537;
    for (i=0;i<=16;++i) mono16[i]=0;
    for (i=17;i<=234;++i)
    {
      v=(i-16)*32173/32768;
      mono16[i]=(v>>((U32*)RGBshift)[3*2])|((v>>((U32*)RGBshift)[4*2])<<((U32*)RGBshift)[1*2])|((v>>((U32*)RGBshift)[5*2])<<((U32*)RGBshift)[2*2]);
    }
    for (i=235;i<256;++i) mono16[i]=255;
    for (i=0;i<256;++i) { v=mono16[i]; mono16x2[i]=v|(v<<16); }
    donetables=1;
  }
}
#endif

// The colour converters' tables and state (the library's yuv.obj data, in BINKDATA, in the
// image's order: 0x52F7C0-0x538900; all zero but the two -1 words, set up by YUV_init).
#pragma data_seg("BINKDATA")
extern "C" {
// match: _ytable_x4 @ 0x0052F7C0
S32 ytable_x4[260] = { 0 };
// match: _ytable @ 0x0052FBD0
S32 ytable[260] = { 0 };
// match: _clamp_r @ 0x0052FFE0
U32 clamp_r[772] = { 0 };
// match: _clamp_g @ 0x00530BF0
U32 clamp_g[772] = { 0 };
// match: _clamp_b @ 0x00531800
U32 clamp_b[772] = { 0 };
// match: _clamp_a4 @ 0x00532410
U32 clamp_a4[260] = { 0 };
// match: _clamp_ytable @ 0x00532820
U32 *clamp_ytable[260] = { 0 };
// match: _clamp_rr @ 0x00532C30
U32 clamp_rr[772] = { 0 };
// match: _clamp_gg @ 0x00533840
U32 clamp_gg[772] = { 0 };
// match: _clamp_bb @ 0x00534450
U32 clamp_bb[772] = { 0 };
// match: _clamp32 @ 0x00535060
U32 clamp32[772] = { 0 };
// match: _mono16 @ 0x00535C70
U32 mono16[256] = { 0 };
// match: _mono16x2 @ 0x00536070
U32 mono16x2[256] = { 0 };
// match: _mono32 @ 0x00536470
U32 mono32[256] = { 0 };
// match: _S @ 0x00536870
YUVSTATE S = { 0 };
// match: _YUVTables @ 0x00536898
U32 YUVTables[8][256] = { 0 };
// match: _RGBshift @ 0x00538898
U64 RGBshift[6] = { 0 };
// match: _rdtscavail @ 0x005388C8
S32 rdtscavail = 0;
// match: _whichyuv @ 0x005388CC
U32 whichyuv = 0;
// match: _unk_5388D0 @ 0x005388D0
S32 unk_5388D0 = -1;
// match: _unk_5388D4 @ 0x005388D4
S32 unk_5388D4 = -1;
// match: _z2hsize @ 0x005388D8
U32 z2hsize = 0;
// match: _z2hbuf1 @ 0x005388DC
void *z2hbuf1 = 0;
// match: _z2hbuf2 @ 0x005388E0
U8 *z2hbuf2 = 0;
// match: _unk_5388E4 @ 0x005388E4
U32 unk_5388E4[7] = { 0 };
}
#pragma data_seg()

// Each destination format's blitters: the row-pair converters (even, odd, mono rows and the
// doubled ones, each with its shift) and the edge helpers, in BINKDATA after the library's
// other data (the image's 0x538900-0x538D80, 0xC0 apart).
// The colour converters (yuv_asm.asm and the rgb*/yuy2* modules) the tables name.
extern "C" void __stdcall YUV_32_4x2_even_MMX(S32 n);
extern "C" void __stdcall YUV_32_4x2_odd_MMX(S32 n);
extern "C" void __stdcall YUV_32m_8x2_MMX(S32 n);
extern "C" void __stdcall YUV_32x2_4x2_even_MMX(S32 n);
extern "C" void __stdcall YUV_32x2_4x2_odd_MMX(S32 n);
extern "C" void __stdcall YUV_32mx2_8x2_MMX(S32 n);
extern "C" void __stdcall YUV_32a_4x2_even_MMX(S32 n);
extern "C" void __stdcall YUV_32a_4x2_odd_MMX(S32 n);
extern "C" void __stdcall YUV_16_4x2_even_MMX(S32 n);
extern "C" void __stdcall YUV_16_4x2_odd_MMX(S32 n);
extern "C" void __stdcall YUV_16m_8x2_MMX(S32 n);
extern "C" void __stdcall YUV_16x2_4x2_even_MMX(S32 n);
extern "C" void __stdcall YUV_16x2_4x2_odd_MMX(S32 n);
extern "C" void __stdcall YUV_16mx2_8x2_MMX(S32 n);
extern "C" void __stdcall YUV_16a4_4x2_even_MMX(S32 n);
extern "C" void __stdcall YUV_16a4_4x2_odd_MMX(S32 n);
extern "C" void __stdcall YUV_16a1_4x2_even_MMX(S32 n);
extern "C" void __stdcall YUV_16a1_4x2_odd_MMX(S32 n);
extern "C" void __stdcall YUY2_8x2_MMX(S32 n);
extern "C" void __stdcall YUY2_m_4x2_MMX(S32 n);
extern "C" void __stdcall YUY2_x2_8x2_MMX(S32 n);
extern "C" void __stdcall YUY2_mx2_4x2_MMX(S32 n);

#pragma data_seg("BINKDATA")
// match: _blits32 @ 0x00538900
BLITS blits32 =
{
  4,
  2, YUV_32_4x2_even_MMX,
  2, YUV_32_4x2_odd_MMX,
  3, YUV_32m_8x2_MMX,
  2, YUV_32x2_4x2_even_MMX,
  2, YUV_32x2_4x2_odd_MMX,
  3, YUV_32mx2_8x2_MMX,
  { 0 }, { 0 },
  dounaligned32row, dounaligned32col,
  dounaligned32rowm, dounaligned32colm,
  dounaligned32row2w, dounaligned32col2w,
  dounaligned32rowm2w, dounaligned32colm2w,
  dounaligned32row2h, dounaligned32col2h,
  dounaligned32rowm2h, dounaligned32colm2h,
  dounaligned32row2wh, dounaligned32col2wh,
  dounaligned32rowm2wh, dounaligned32colm2wh
};

// match: _blits32a @ 0x005389C0
BLITS blits32a =
{
  4,
  2, YUV_32a_4x2_even_MMX,
  2, YUV_32a_4x2_odd_MMX,
  3, YUV_32m_8x2_MMX,
  2, YUV_32x2_4x2_even_MMX,
  2, YUV_32x2_4x2_odd_MMX,
  3, YUV_32mx2_8x2_MMX,
  { 0 }, { 0 },
  dounaligned32arow, dounaligned32acol,
  dounaligned32arowm, dounaligned32acolm,
  dounaligned32arow2w, dounaligned32acol2w,
  dounaligned32arowm2w, dounaligned32acolm2w,
  dounaligned32arow2h, dounaligned32acol2h,
  dounaligned32arowm2h, dounaligned32acolm2h,
  dounaligned32arow2wh, dounaligned32acol2wh,
  dounaligned32arowm2wh, dounaligned32acolm2wh
};

// match: _blits16 @ 0x00538A80
BLITS blits16 =
{
  2,
  2, YUV_16_4x2_even_MMX,
  2, YUV_16_4x2_odd_MMX,
  3, YUV_16m_8x2_MMX,
  2, YUV_16x2_4x2_even_MMX,
  2, YUV_16x2_4x2_odd_MMX,
  3, YUV_16mx2_8x2_MMX,
  { 0 }, { 0 },
  dounaligned16row, dounaligned16col,
  dounaligned16rowm, dounaligned16colm,
  dounaligned16row2w, dounaligned16col2w,
  dounaligned16rowm2w, dounaligned16colm2w,
  dounaligned16row2h, dounaligned16col2h,
  dounaligned16rowm2h, dounaligned16colm2h,
  dounaligned16row2wh, dounaligned16col2wh,
  dounaligned16rowm2wh, dounaligned16colm2wh
};

// match: _blits16a4 @ 0x00538B40
BLITS blits16a4 =
{
  2,
  2, YUV_16a4_4x2_even_MMX,
  2, YUV_16a4_4x2_odd_MMX,
  3, YUV_16m_8x2_MMX,
  2, YUV_16x2_4x2_even_MMX,
  2, YUV_16x2_4x2_odd_MMX,
  3, YUV_16mx2_8x2_MMX,
  { 0 }, { 0 },
  dounaligned16a4row, dounaligned16a4col,
  dounaligned16a4rowm, dounaligned16a4colm,
  dounaligned16a4row2w, dounaligned16a4col2w,
  dounaligned16a4rowm2w, dounaligned16a4colm2w,
  dounaligned16a4row2h, dounaligned16a4col2h,
  dounaligned16a4rowm2h, dounaligned16a4colm2h,
  dounaligned16a4row2wh, dounaligned16a4col2wh,
  dounaligned16a4rowm2wh, dounaligned16a4colm2wh
};

// match: _blits16a1 @ 0x00538C00
BLITS blits16a1 =
{
  2,
  2, YUV_16a1_4x2_even_MMX,
  2, YUV_16a1_4x2_odd_MMX,
  3, YUV_16m_8x2_MMX,
  2, YUV_16x2_4x2_even_MMX,
  2, YUV_16x2_4x2_odd_MMX,
  3, YUV_16mx2_8x2_MMX,
  { 0 }, { 0 },
  dounaligned16a1row, dounaligned16a1col,
  dounaligned16a1rowm, dounaligned16a1colm,
  dounaligned16a1row2w, dounaligned16a1col2w,
  dounaligned16a1rowm2w, dounaligned16a1colm2w,
  dounaligned16a1row2h, dounaligned16a1col2h,
  dounaligned16a1rowm2h, dounaligned16a1colm2h,
  dounaligned16a1row2wh, dounaligned16a1col2wh,
  dounaligned16a1rowm2wh, dounaligned16a1colm2wh
};

// match: _blitsyuy2 @ 0x00538CC0
BLITS blitsyuy2 =
{
  2,
  3, YUY2_8x2_MMX,
  3, YUY2_8x2_MMX,
  2, YUY2_m_4x2_MMX,
  3, YUY2_x2_8x2_MMX,
  3, YUY2_x2_8x2_MMX,
  2, YUY2_mx2_4x2_MMX,
  { 0 }, { 0 },
  dounalignedYUY2row, dounalignedYUY2col,
  dounalignedYUY2rowm, dounalignedYUY2colm,
  dounalignedYUY2row2w, dounalignedYUY2col2w,
  dounalignedYUY2rowm2w, dounalignedYUY2colm2w,
  dounalignedYUY2row2h, dounalignedYUY2col2h,
  dounalignedYUY2rowm2h, dounalignedYUY2colm2h,
  dounalignedYUY2row2wh, dounalignedYUY2col2wh,
  dounalignedYUY2rowm2wh, dounalignedYUY2colm2wh
};

#pragma data_seg()
