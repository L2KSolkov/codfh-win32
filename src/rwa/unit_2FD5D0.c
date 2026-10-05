/*
 * codfh-match: RenderWare Audio's allocation bitmaps (0x2FD5D0-0x2FDB00),
 * linked after the XDK's voice codec: a run of bits per allocation unit,
 * a run allocated as a handle that packs its first unit and, above
 * `shift` bits, its length. The streamed-wave buffers (sub_24DBA0) are
 * carved from one.
 */
#include "rwa.h"
#include "rwaint.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x005125EC
RwaFreeList unk_5125EC;
// End of its data definitions.


extern void *sub_242170(RwUInt32 size, RwUInt32 hint);
extern void sub_2421B0(void *mem);
extern void *memset(void *dst, RwInt32 value, RwUInt32 size);
extern void *sub_243670(RwaFreeList *freeList, RwUInt32 hint);
extern void sub_2437A0(RwaFreeList *freeList, void *entry);

extern RwaFreeList unk_5125EC;      /* the bitmaps' free list */

/* rwaint.h's rwaLog2 on an unsigned value (logical shifts). */
#define rwaLog2U16(_v) \
    (((_v) & 0xFF00) ? _rwMsbBit[(_v) >> 8] + 7 : _rwMsbBit[(_v)] - 1)
#define rwaLog2U(_x) \
    (((_x) & 0xFFFF0000) ? rwaLog2U16((_x) >> 16) + 16 : rwaLog2U16(_x))

// match: _sub_2FD5D0 @ 0x002FD5D0
RwaAllocBitmap *
sub_2FD5D0(RwUInt32 numUnits, RwaAllocBitmap *bitmap, RwUInt8 *bits)
{
    RwUInt8     flags = 0;
    RwUInt32    rounded = (numUnits + 7) & ~7;
    RwUInt8     shift;

    shift = (RwUInt8)(rwaLog2U(rounded) + 1);
    rounded >>= 3;

    if (!bitmap)
    {
        bitmap = (RwaAllocBitmap *)sub_243670(&unk_5125EC, rwaMEMHINTDUR_EVENT | rwaID_800);
        flags = 1;
    }
    if (bitmap)
    {
        if (!bits)
        {
            bits = (RwUInt8 *)sub_242170(rounded, rwaMEMHINTDUR_EVENT);
            flags |= 2;
        }
        if (bits)
        {
            bitmap->shift = shift;
            bitmap->bits = bits;
            memset(bits, 0, rounded);
            bitmap->numBytes = rounded;
            bitmap->flags = flags;
        }
        else
        {
            if (flags & 1)
            {
                sub_2437A0(&unk_5125EC, bitmap);
            }
            bitmap = NULL;
        }
    }
    return bitmap;
}

// match: _rwaAllocBitmapDestroy @ 0x002FD6C0
void
rwaAllocBitmapDestroy(RwaAllocBitmap *bitmap)
{
    if (bitmap->flags & 2)
    {
        sub_2421B0(bitmap->bits);
    }
    if (bitmap->flags & 1)
    {
        sub_2437A0(&unk_5125EC, bitmap);
    }
}

/* Sets (value non-zero) or clears count bits from bit start. */
// match: _sub_2FD6F0 @ 0x002FD6F0
void
sub_2FD6F0(RwaAllocBitmap *bitmap, RwUInt32 start, RwUInt32 count, RwUInt32 value)
{
    RwUInt8     set = (value != 0);
    RwUInt8     firstBit = (RwUInt8)(start & 7);
    RwUInt32    first = start >> 3;
    RwUInt32    last = (start + count) >> 3;
    RwUInt8     lastBit = (RwUInt8)((start + count) & 7);
    RwUInt32    i;

    for (i = first; i <= last; i++)
    {
        RwUInt8     lo = 0;
        RwUInt8     hi = 8;

        if (i == first)
        {
            lo = firstBit;
        }
        if (i == last)
        {
            hi = lastBit;
        }

        if (lo == 0 && hi == 8)
        {
            bitmap->bits[i] = ~(RwUInt8)(set - 1);
        }
        else
        {
            RwUInt32    bit;

            for (bit = lo; bit < hi; bit++)
            {
                bitmap->bits[i] &= ~(1 << bit);
                bitmap->bits[i] |= set << bit;
            }
        }
    }
}

/* The number of free units. */
// match: _sub_2FD7A0 @ 0x002FD7A0
RwUInt32
sub_2FD7A0(RwaAllocBitmap *bitmap)
{
    RwUInt32    numBytes = bitmap->numBytes;
    RwUInt32    numFree = 0;
    RwUInt32    i;

    for (i = 0; i < numBytes; i++)
    {
        RwUInt8     byte = bitmap->bits[i];

        if (!byte)
        {
            numFree += 8;
        }
        else if (byte != 0xFF)
        {
            RwUInt32     value = byte;
            RwUInt32    bit;
            RwInt32     n;

            for (bit = 0, n = 8; n; n--, bit++)
            {
                if (!((1 << bit) & value))
                {
                    numFree++;
                }
            }
        }
    }

    return numFree;
}

// match: _sub_2FD800 @ 0x002FD800
RwUInt32 *
sub_2FD800(RwaAllocBitmap *bitmap, RwUInt32 *handle, RwUInt32 a3, RwUInt32 a4, RwUInt32 a5,
           RwUInt32 *out)
{
    *out = ((a4 / bitmap->unitSize) << bitmap->shift)
         | ((*handle & ((1 << bitmap->shift) - 1))
            + (a3 + bitmap->unitSize - a5) / bitmap->unitSize);
    return out;
}

// match: _sub_2FD850 @ 0x002FD850
RwUInt32
sub_2FD850(RwaAllocBitmap *bitmap, RwUInt32 handle0, RwUInt32 handle1)
{
    return bitmap->unitSize * ((handle1 & ((1 << bitmap->shift) - 1))
                             - (handle0 & ((1 << bitmap->shift) - 1)));
}

/* Frees a run sub_2FD880 allocated. */
/* _rwaAllocBitmapAlloc, rwad.dll 0x100BB929: the compiler unrolls
 * the ordinary bit loop. Clamp the run before breaking the byte loop. */
// match: _sub_2FD880 @ 0x002FD880
RwBool
sub_2FD880(RwaAllocBitmap *bitmap, RwUInt32 count, RwUInt32 *handle)
{
    RwUInt32 start = 0;
    RwUInt32 run = 0;
    RwUInt32 longest = 0;
    RwUInt32 i;

    for (i = 0; i < bitmap->numBytes; i++)
    {
        if (!bitmap->bits[i])
        {
            if (!run)
            {
                start = i * 8;
            }
            run += 8;
        }
        else if (bitmap->bits[i] != 0xFF)
        {
            RwUInt32 bit;
            for (bit = 0; bit < 8; bit++)
            {
                if (!((1 << bit) & bitmap->bits[i]))
                {
                    if (!run)
                    {
                        start = bit + i * 8;
                    }
                    run++;
                }
                else
                {
                    start = bit + i * 8;
                    run = 0;
                }
                if (run == count)
                {
                    break;
                }
            }
        }
        else
        {
            start = i * 8;
            run = 0;
        }
        if (run > longest)
        {
            longest = run;
        }
        if (run >= count)
        {
            run = count;
            break;
        }
    }
    if (run < count)
    {
        *handle = 0;
        return FALSE;
    }
    sub_2FD6F0(bitmap, start, run, 1);
    *handle = start | (run << bitmap->shift);
    return TRUE;
}

// match: _sub_2FDAC0 @ 0x002FDAC0
void
sub_2FDAC0(RwaAllocBitmap *bitmap, RwUInt32 *handle)
{
    sub_2FD6F0(bitmap, *handle & ((1 << bitmap->shift) - 1),
               (*handle & ~((1 << bitmap->shift) - 1)) >> bitmap->shift, 0);
}
