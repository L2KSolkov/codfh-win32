/*
 * codfh-match: Bink's colour conversion (the library's yuv.obj, C++): the
 * blit state S that the MMX converters (rgb*.asm, yuy2*.asm) work on, the
 * per-format edge helpers that convert the unaligned left and right
 * columns of a blit in C, and the blitters that drive them.
 */
#include "bink.h"
#include "binkint.h"

extern "C" YUVSTATE S;
extern "C" U32 mono32[256];

// the half-height zoom buffers (setevenodd sizes them for the blit width)
extern "C" void *z2hbuf1;
extern "C" U8 *z2hbuf2;
extern "C" U32 z2hsize;

// the converters for a pair of rows the blitters call (EVEN and ODD rows,
// stdcall with the width), the plain ones the half-height zooms double
// (EVENx, ODDx), and the ones timing measures (EVENt, ODDt)
typedef void (__stdcall *ROWPAIRFN)(S32 n);
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

// a destination format's blitters (blits32 and the others): the bytes per
// pixel, the MMX row-pair converters with the alignment (log2 pixels) each
// needs (plain, then doubled width), the timing words of the zooms and the
// edges, and the C edge helpers for each scaling
typedef void (*EDGEROWFN)(U32 x, U32 n);
typedef S32 (*EDGECOLFN)(U32 n, S32 x);
typedef struct BLITS {
  U32 bpp;
  U32 evenshift;
  ROWPAIRFN even;
  U32 oddshift;
  ROWPAIRFN odd;
  U32 monoshift;
  ROWPAIRFN mono;
  U32 even2shift;
  ROWPAIRFN even2;
  U32 odd2shift;
  ROWPAIRFN odd2;
  U32 mono2shift;
  ROWPAIRFN mono2;
  U32 dbltime[8];             // setdbls' words at [1], [3], [5], [7]
  U32 alntime[8];             // the edges' timing words at the same
  EDGEROWFN row;
  EDGECOLFN col;
  EDGEROWFN rowm;
  EDGECOLFN colm;
  EDGEROWFN row2w;
  EDGECOLFN col2w;
  EDGEROWFN rowm2w;
  EDGECOLFN colm2w;
  EDGEROWFN row2h;
  EDGECOLFN col2h;
  EDGEROWFN rowm2h;
  EDGECOLFN colm2h;
  EDGEROWFN row2wh;
  EDGECOLFN col2wh;
  EDGEROWFN rowm2wh;
  EDGECOLFN colm2wh;
} BLITS;

// the blit's edge helpers and the alignment the MMX converters need
extern "C" EDGEROWFN dounalignedrow;
extern "C" EDGECOLFN dounalignedcol;
extern "C" U32 alignshift;
extern "C" U32 align;
extern "C" U32 alignm1;
extern "C" U32 whichyuv;      // 1 while YUVTables are swapped for BINKRBINVERT
extern "C" S32 decode_use_MMX;
void check_for_MMX(U32 flags);

// each destination format's blitters
extern "C" BLITS blits32;
extern "C" BLITS blits32a;
extern "C" BLITS blits16;
extern "C" BLITS blits16a4;
extern "C" BLITS blits16a1;
extern "C" BLITS blitsyuy2;
extern "C" U32 YUVTables[8][256];
extern "C" U32 mono16[256];
extern "C" S32 ytable[256];
extern "C" U32 clamp_r[];
extern "C" U32 clamp_g[];
extern "C" U32 clamp_b[];
extern "C" U32 clamp_a4[256];
extern "C" U32 *clamp_ytable[256];

// one 32-bit pixel: the Y row's clamp table indexed by the red, green and
// blue offsets of the shared U and V
#define YUV32(yt, r, g, b) ((((yt)[r] << 8) | (yt)[g]) << 8 | (yt)[b])

// The edge helpers are RAD's statics, reached only through the blitters'
// function tables (blits32 and the others), which come with YUV_blit; until
// those are matched they are left external so they are emitted.
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

// swaps two of the colour tables (BINKRBINVERT exchanges the U and V terms)
#define SWAPTABLES(a, b)                                                 \
  {                                                                      \
    U32 *p = YUVTables[a];                                               \
    U32 i;                                                               \
                                                                         \
    for (i = 0; i < 256; i++)                                            \
    {                                                                    \
      U32 s = p[(b - a) * 256];                                          \
                                                                         \
      p[(b - a) * 256] = *p;                                             \
      *p++ = s;                                                          \
    }                                                                    \
  }

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

// match: ?checkzoombufs@@YAXK@Z @ 0x0034A2B0
static void checkzoombufs(U32 width)
{
  U32 w = (width + 31) & ~31;
  U32 size = w * 2;

  if (size > z2hsize)
  {
    if (z2hbuf1)
    {
      radfree(z2hbuf1);
      z2hbuf1 = 0;
    }
    z2hbuf1 = radmalloc(size);
    z2hsize = size;
  }
  z2hbuf2 = (U8 *)z2hbuf1 + w;
}

// match: ?zoom2heven@@YGXJ@Z @ 0x0034A330
static void __stdcall zoom2heven(S32 n)
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
static void __stdcall zoom2hodd(S32 n)
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
static void __stdcall zoom2hevenbuf(S32 n)
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
static void __stdcall zoom2hoddbuf(S32 n)
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
static void __stdcall timedbleven(S32 n)
{
  U32 cycles;

  RADCycleTimerStartAddr(&cycles);
  EVENt(n);
  RADCycleTimerDeltaAddr(&cycles);
  checktime(cycles);
}

// match: ?timedblodd@@YGXJ@Z @ 0x0034A770
static void __stdcall timedblodd(S32 n)
{
  U32 cycles;

  RADCycleTimerStartAddr(&cycles);
  ODDt(n);
  RADCycleTimerDeltaAddr(&cycles);
  checktime(cycles);
}

// match: ?setdbls@@YAXPAKK@Z @ 0x0034A7B0
static void setdbls(U32 *addr, U32 width)
{
  if (rdtscavail != 1)
    goto usebuf;
  {
    U32 t = *addr;

    if ((t & 1) && (t <= 0x2000))
    {
      t += width * 4;
      *addr = t;
      if (t & 2)
      {
       usebuf:
        EVEN = zoom2hevenbuf;
        ODD = zoom2hoddbuf;
        return;
      }
      EVEN = zoom2heven;
      ODD = zoom2hodd;
      return;
    }
    EVEN = timedbleven;
    ODD = timedblodd;
    dbltimeaddr = addr;
    *addr = 0x82;
    EVENt = zoom2heven;
    ODDt = zoom2hodd;
    testing = 1;
  }
}

// match: ?setevenodd@@YAXKPAKKKPAUBLITS@@0@Z @ 0x0034A840
static void setevenodd(U32 flags, U32 *pitch, U32 w, U32 h, BLITS *b, U32 *skip)
{
  S.pitch = *pitch;
  testing = 0;
  if (flags & BINKRBINVERT)
  {
    if (whichyuv != 1)
    {
      whichyuv = 1;
      SWAPTABLES(3, 0);
      SWAPTABLES(1, 2);
      SWAPTABLES(7, 4);
      SWAPTABLES(5, 6);
    }
  }
  else if (whichyuv != 0)
  {
    whichyuv = 0;
    SWAPTABLES(3, 0);
    SWAPTABLES(1, 2);
  }

  check_for_MMX(flags);
  if (!decode_use_MMX)
    goto done;

  switch (flags & 0x70000000)
  {
    case BINKCOPY2XH:
      checkzoombufs(b->bpp * w);
      *pitch *= 2;
      *skip = *pitch - b->bpp * w;
      if (flags & BINKGRAYSCALE)
      {
        alnaddr = &b->alntime[3];
        setdbls(&b->dbltime[3], h);
        EVENx = b->mono;
        ODDx = b->mono;
        dounalignedrow = b->rowm2h;
        dounalignedcol = b->colm2h;
        alignshift = b->monoshift;
      }
      else
      {
        alnaddr = &b->alntime[1];
        setdbls(&b->dbltime[1], h);
        dounalignedrow = b->row2h;
        dounalignedcol = b->col2h;
        EVENx = b->even;
        ODDx = b->odd;
        alignshift = (b->evenshift > b->oddshift) ? b->evenshift : b->oddshift;
      }
      break;

    case BINKCOPY2XWH:
      checkzoombufs(b->bpp * w * 2);
      *pitch *= 2;
      *skip = *pitch - b->bpp * w * 2;
      if (flags & BINKGRAYSCALE)
      {
        alnaddr = &b->alntime[7];
        setdbls(&b->dbltime[7], h);
        dounalignedcol = b->colm2wh;
        dounalignedrow = b->rowm2wh;
        EVENx = b->mono2;
        ODDx = b->mono2;
        alignshift = b->mono2shift;
      }
      else
      {
        alnaddr = &b->alntime[5];
        setdbls(&b->dbltime[5], h);
        dounalignedrow = b->row2wh;
        EVENx = b->even2;
        ODDx = b->odd2;
        dounalignedcol = b->col2wh;
        alignshift = (b->even2shift > b->odd2shift) ? b->even2shift : b->odd2shift;
      }
      break;

    case BINKCOPY2XW:
    case BINKCOPY2XWHI:
      *skip = *pitch - b->bpp * w * 2;
      if (flags & BINKGRAYSCALE)
      {
        dounalignedrow = b->rowm2w;
        dounalignedcol = b->colm2w;
        alnaddr = &b->alntime[7];
        EVEN = b->mono2;
        ODD = b->mono2;
        alignshift = b->mono2shift;
      }
      else
      {
        dounalignedrow = b->row2w;
        dounalignedcol = b->col2w;
        alnaddr = &b->alntime[5];
        EVEN = b->even2;
        ODD = b->odd2;
        alignshift = (b->even2shift > b->odd2shift) ? b->even2shift : b->odd2shift;
      }
      break;

    default:
      *skip = *pitch - b->bpp * w;
      if (flags & BINKGRAYSCALE)
      {
        dounalignedrow = b->rowm;
        dounalignedcol = b->colm;
        alnaddr = &b->alntime[3];
        EVEN = b->mono;
        ODD = b->mono;
        alignshift = b->monoshift;
      }
      else
      {
        dounalignedrow = b->row;
        alnaddr = &b->alntime[1];
        EVEN = b->even;
        ODD = b->odd;
        dounalignedcol = b->col;
        alignshift = (b->evenshift > b->oddshift) ? b->evenshift : b->oddshift;
      }
      break;
  }

 done:
  align = 1 << alignshift;
  alignm1 = align - 1;
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

// match: ?YUV_blit@@YAXPAXKKK0KKKKKKK0PAUBLITS@@@Z @ 0x0034ACD0
static void YUV_blit(void *dest, U32 destx, U32 desty, U32 destpitch, void *yplane, U32 srcx, U32 srcy,
                     U32 srcw, U32 srch, U32 ywidth, U32 yheight, U32 flags, void *aplane, BLITS *b)
{
  U32 mode = flags & 0x70000000;
  U32 yoff;
  S32 yskip;
  S32 uvskip;
  U32 end;
  U32 left;
  U32 odd;

  if (mode == BINKCOPY1XI)
  {
    srcy >>= 1;
    srch >>= 1;
    yheight >>= 1;
    ywidth *= 2;
    destpitch *= 2;
  }

  S.dest = dest;
  if (b->bpp == 2)
  {
    if (((U32)dest & 3) == 2)
    {
      destx++;
      dest = (void *)((U32)dest & ~3);
    }
  }
  else if (b->bpp == 3)
  {
    if (!(((U32)dest + 1) & 3))
    {
      destx++;
      dest = (U8 *)dest - 3;
    }
    else if (!(((U32)dest - 2) & 3))
    {
      destx += 2;
      dest = (U8 *)dest - 6;
    }
    else if (!(((U32)dest - 1) & 3))
    {
      destx += 3;
      dest = (U8 *)dest - 9;
    }
  }
  S.out0 = (U8 *)dest + b->bpp * destx + destpitch * desty;

  if ((mode == BINKCOPY2XHI) || (mode == BINKCOPY2XWHI))
    destpitch *= 2;

  // desty becomes the bytes from the end of one output row pair to the next
  setevenodd(flags, (U32 *)&destpitch, srcw, srch, b, &desty);

  S.out1 = S.out0 + destpitch;
  yoff = srcy * ywidth;
  S.y0 = (U8 *)yplane + yoff + srcx;
  S.y1 = S.y0 + ywidth;
  S.a0 = (U8 *)aplane + yoff + srcx;
  S.a1 = S.a0 + ywidth;
  yskip = ywidth - srcw;
  uvskip = (ywidth >> 1) - (srcw >> 1);
  if ((srcw & 1) && (srcx & 1))
    uvskip--;

  if (flags & BINKRBINVERT)
  {
    U8 *u = (U8 *)yplane + ywidth * yheight;

    S.v = u + (yheight >> 1) * (ywidth >> 1);
    S.u = u;
  }
  else
  {
    S.v = (U8 *)yplane + ywidth * yheight;
    S.u = S.v + (yheight >> 1) * (ywidth >> 1);
  }
  {
    U32 uvoff = (srcy >> 1) * (ywidth >> 1) + (srcx >> 1);

    S.u += uvoff;
    S.v += uvoff;
  }

  if (flags & 0x800)
  {
    U8 *y1 = S.y1;

    S.y1 = S.a1;
    S.a1 = y1;
    {
      U8 *y0 = S.y0;

      S.y0 = S.a0;
      S.a0 = y0;
    }
  }

  end = srcy + srch - 1;
  if ((srcy & 1) && (srcy <= end))
  {
    dounalignedrow(srcx, srcw);
    S.y0 += yskip;
    S.y1 = S.y0 + ywidth;
    S.a0 += yskip;
    S.a1 = S.a0 + ywidth;
    S.u += uvskip;
    S.v += uvskip;
    S.out0 += desty;
    S.out1 = S.out0 + destpitch;
    srcy++;
  }

  left = (0 - destx) & 3;
  if (left > srcw)
    left = srcw;
  odd = srcx & 1;
  if (odd > srcw)
    odd = srcw;

  {
    U32 t = *alnaddr;

    if (t & 1)
    {
      if (t > 0x2000)
        *alnaddr = 0x80;
      else
        *alnaddr = t + srch * 4;
    }
    else if (t == 0)
      *alnaddr = 0x80;
  }

  for (; (S32)srcy < (S32)end; srcy += 2)
  {
    U32 t = *alnaddr;
    U32 x = srcx;
    U32 n = srcw;
    U32 first;
    U32 mid;
    U32 right;

    if ((!testing) && (left != odd))
    {
      if (rdtscavail == 1)
      {
        if (!(t & 1))
        {
          *alnaddr = t | 4;
          RADCycleTimerStartAddr(&lastleft);
        }
      }
      else
      {
        first = left;
        goto doleft;
      }
    }
    first = (t & 2) ? odd : left;
   doleft:
    if (first)
    {
      x = dounalignedcol(first, srcx);
      n = srcw - first;
    }
    mid = n >> 2 & ~alignm1 >> 2;
    right = n - mid * 4;
    if (mid)
    {
      if (x & 1)
        ODD(mid);
      else
        EVEN(mid);
    }
    if (right)
      dounalignedcol(right, x + mid * 4);
    dorightedge();
    S.y0 = S.y1 + yskip;
    S.y1 = S.y0 + ywidth;
    S.a0 = S.a1 + yskip;
    S.a1 = S.a0 + ywidth;
    S.u += uvskip;
    S.v += uvskip;
    S.out0 = S.out1 + desty;
    S.out1 = S.out0 + destpitch;
  }

  if (srcy <= end)
    dounalignedrow(srcx, srcw);

  if (decode_use_MMX)
    __asm emms
}

// match: _YUV_blit_32bpp@52 @ 0x0034EBD0
YUVBLIT(YUV_blit_32bpp)
{
  YUV_blit(dest, destx, desty, destpitch, yplane, srcx, srcy, srcw, srch, ywidth, yheight, flags, aplane, &blits32);
}

// match: _YUV_blit_32abpp@52 @ 0x0034FFA0
YUVBLIT(YUV_blit_32abpp)
{
  YUV_blit(dest, destx, desty, destpitch, yplane, srcx, srcy, srcw, srch, ywidth, yheight, flags, aplane, &blits32a);
}

// match: _YUV_blit_16bpp@52 @ 0x00351290
YUVBLIT(YUV_blit_16bpp)
{
  YUV_blit(dest, destx, desty, destpitch, yplane, srcx, srcy, srcw, srch, ywidth, yheight, flags, aplane, &blits16);
}

// match: _YUV_blit_16a4bpp@52 @ 0x00352760
YUVBLIT(YUV_blit_16a4bpp)
{
  YUV_blit(dest, destx, desty, destpitch, yplane, srcx, srcy, srcw, srch, ywidth, yheight, flags, aplane, &blits16a4);
}

// match: _YUV_blit_16a1bpp@52 @ 0x00353C80
YUVBLIT(YUV_blit_16a1bpp)
{
  YUV_blit(dest, destx, desty, destpitch, yplane, srcx, srcy, srcw, srch, ywidth, yheight, flags, aplane, &blits16a1);
}

// match: _YUV_blit_YUY2@52 @ 0x00354D70
YUVBLIT(YUV_blit_YUY2)
{
  // YUY2 pairs pixels: start on an even dword and an even column
  if (((U32)dest & 3) == 2)
  {
    destx++;
    dest = (void *)((U32)dest & ~3);
  }
  if (destx & 1)
  {
    if (srcx & 1)
      srcx++;
    destx++;
    srcw--;
  }
  else if (srcx & 1)
  {
    srcx++;
    srcw--;
  }
  if (srcw & 1)
    srcw--;
  YUV_blit(dest, destx, desty, destpitch, yplane, srcx, srcy, srcw, srch, ywidth, yheight, flags, aplane, &blitsyuy2);
}

// match: ?checkrdtsc@@YAXXZ @ 0x0034BB10
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

ROWPAIRFN yuv_probe_zoom[] = { zoom2heven, zoom2hodd, zoom2hevenbuf, zoom2hoddbuf, timedbleven, timedblodd };

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
