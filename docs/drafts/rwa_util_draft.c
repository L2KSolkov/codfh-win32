/*
 * codfh-match: RenderWare Audio's numeric helpers (0x241F90-0x242170): a
 * gain to hundredths of a decibel, the byte-swapping stream copy, a
 * vector's length through the library's table square root, a 32 by 32 bit
 * multiply into two 31-bit halves and a value's lowest set bit.
 */
#include "rwa.h"
#include <math.h>

#include "rwaint.h"

extern const RwInt16 word_42F1A0[];

/* An in-place table square root of the float at _root. */
#define rwaSqrtInPlace(_root)                                               \
    if (*(_root) != 0.0f)                                                   \
    {                                                                       \
        RwUInt32   *_bits = (RwUInt32 *)(_root);                            \
        RwInt16     _exp = (RwInt16)((*_bits >> 23) - 127);                 \
                                                                            \
        *_bits &= 0x7FFFFF;                                                 \
        if (_exp & 1)                                                       \
        {                                                                   \
            *_bits |= 0x800000;                                             \
        }                                                                   \
                                                                            \
        _exp >>= 1;                                                         \
        *_bits = ((RwUInt32)(RwInt32)word_42F1A0[*_bits >> 16] << 16) |     \
                 ((RwUInt32)(_exp + 127) << 23);                            \
    }

// match: _sub_241F90 @ 0x00241F90
RwInt32
sub_241F90(RwReal gain)
{
    RwInt32     level;

    if (gain < 1e-5f)
    {
        return -10000;
    }

    level = (RwInt32)((RwReal)log10(gain) * 2000.0f);

    return level > 0 ? 0 : level;
}

// match: _sub_241FD0 @ 0x00241FD0
void
sub_241FD0(RwUInt8 **cursor, const void *src, RwInt32 size)
{
    switch (size)
    {
        case 1:
        {
            RwUInt8    *dst = *cursor;

            *dst = *(const RwUInt8 *)src;
            *cursor = dst + 1;
            break;
        }

        case 2:
        {
            RwUInt8    *dst = *cursor;

            *(RwUInt16 *)dst = (RwUInt16)((((const RwUInt8 *)src)[0] << 8) | ((const RwUInt8 *)src)[1]);
            *cursor = dst + 2;
            break;
        }

        case 4:
        {
            RwUInt8    *dst = *cursor;
            RwUInt32    value = *(const RwUInt32 *)src;

            *(RwUInt32 *)dst = (value << 24) | ((value & 0xFF00) << 8) |
                               ((value >> 8) & 0xFF00) | ((const RwUInt8 *)src)[3];
            *cursor = dst + 4;
            break;
        }
    }
}

// match: _sub_242050 @ 0x00242050
void
sub_242050(RwReal *length, const RwaV3d *vector)
{
    *length = vector->x * vector->x + vector->y * vector->y + vector->z * vector->z;
    rwaSqrtInPlace(length);
}

