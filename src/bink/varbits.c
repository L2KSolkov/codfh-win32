/*
 * codfh-match: Bink's variable bit-length tables (binkxbox.lib's varbits.obj, whose .rdata the
 * image keeps at 0x3EEE00 though nothing reads it there; its VarBitsCopy is not in the image).
 * Each table follows an 8-byte zero that aligns it, as the library's `...align` symbols do.
 */

#include "bink.h"
#include "binkint.h"

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: _VarBitsLensalign @ 0x003EEE00
// match: _VarBitsLens @ 0x003EEE08
// match: __bitlevelsalign @ 0x003EEE90
// match: __bitlevels @ 0x003EEE98

const F64 VarBitsLensalign = 0;

/* n bits' mask */
#define M(n) (0xffffffffUL >> (32 - (n)))

const U32 VarBitsLens[33] =
{
  0,
  M(1), M(2), M(3), M(4), M(5), M(6), M(7), M(8),
  M(9), M(10), M(11), M(12), M(13), M(14), M(15), M(16),
  M(17), M(18), M(19), M(20), M(21), M(22), M(23), M(24),
  M(25), M(26), M(27), M(28), M(29), M(30), M(31), M(32),
};

const F64 _bitlevelsalign = 0;

const U8 _bitlevels[129] =
{
  0, 1, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4,
  5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
  6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
  6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
  7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
  7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
  7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
  7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
  8,
};
