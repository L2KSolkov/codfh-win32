/* rwaint.h's rwaLog2 on an unsigned value (logical shifts). */
#define rwaLog2U16(_v)                                                          (((_v) & 0xFF00) ? byte_435388[(_v) >> 8] + 7 : byte_435388[(_v)] - 1)

#define rwaLog2U(_x)                                                            (((_x) & 0xFFFF0000) ? rwaLog2U16((_x) >> 16) + 16 : rwaLog2U16(_x))

// match: _sub_2FD5D0 @ 0x002FD5D0
RwaAllocBitmap *
sub_2FD5D0(RwUInt32 numUnits, RwaAllocBitmap *bitmap, RwUInt8 *bits)
{
    RwUInt8     flags = 0;
    RwUInt32    rounded = (numUnits + 7) & ~7;
    RwUInt8     shift;
    RwUInt32    numBytes;

    shift = (RwUInt8)(rwaLog2U(rounded) + 1);
    numBytes = rounded >> 3;

    if (!bitmap)
    {
        bitmap = (RwaAllocBitmap *)sub_243670(&unk_5125EC, 0x30800);
        flags = 1;
        if (!bitmap)
        {
            return NULL;
        }
    }

    if (!bits)
    {
        bits = (RwUInt8 *)sub_242170(numBytes, 0x30000);
        flags |= 2;
        if (!bits)
        {
            if (flags & 1)
            {
                sub_2437A0(&unk_5125EC, bitmap);
            }
            return NULL;
        }
    }

    bitmap->shift = shift;
    bitmap->bits = bits;
    memset(bits, 0, numBytes);
    bitmap->numBytes = numBytes;
    bitmap->flags = flags;

    return bitmap;
}

/* Allocates a run of count units: the first fitting run, set, its handle in
 * *handle; 0 (and a zero handle) when none is long enough. */
// match: _sub_2FD880 @ 0x002FD880
RwBool
sub_2FD880(RwaAllocBitmap *bitmap, RwUInt32 count, RwUInt32 *handle)
{
    RwUInt32    i;
    RwUInt32    start = 0;
    RwUInt32    run = 0;
    RwUInt32    longest = 0;

    for (i = 0; i < bitmap->numBytes; i++)
    {
        RwUInt8     byte = bitmap->bits[i];

        if (!byte)
        {
            if (!run)
            {
                start = i * 8;
            }
            run += 8;
        }
        else if (byte != 0xFF)
        {
            RwUInt32    bit;

            for (bit = 0; bit < 8; bit += 8)
            {
                if (!((1 << bit) & byte))
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
                if (!((1 << (bit + 1)) & byte))
                {
                    if (!run)
                    {
                        start = (bit + 1) + i * 8;
                    }
                    run++;
                }
                else
                {
                    start = (bit + 1) + i * 8;
                    run = 0;
                }
                if (run == count)
                {
                    break;
                }
                if (!((1 << (bit + 2)) & byte))
                {
                    if (!run)
                    {
                        start = (bit + 2) + i * 8;
                    }
                    run++;
                }
                else
                {
                    start = (bit + 2) + i * 8;
                    run = 0;
                }
                if (run == count)
                {
                    break;
                }
                if (!((1 << (bit + 3)) & byte))
                {
                    if (!run)
                    {
                        start = (bit + 3) + i * 8;
                    }
                    run++;
                }
                else
                {
                    start = (bit + 3) + i * 8;
                    run = 0;
                }
                if (run == count)
                {
                    break;
                }
                if (!((1 << (bit + 4)) & byte))
                {
                    if (!run)
                    {
                        start = (bit + 4) + i * 8;
                    }
                    run++;
                }
                else
                {
                    start = (bit + 4) + i * 8;
                    run = 0;
                }
                if (run == count)
                {
                    break;
                }
                if (!((1 << (bit + 5)) & byte))
                {
                    if (!run)
                    {
                        start = (bit + 5) + i * 8;
                    }
                    run++;
                }
                else
                {
                    start = (bit + 5) + i * 8;
                    run = 0;
                }
                if (run == count)
                {
                    break;
                }
                if (!((1 << (bit + 6)) & byte))
                {
                    if (!run)
                    {
                        start = (bit + 6) + i * 8;
                    }
                    run++;
                }
                else
                {
                    start = (bit + 6) + i * 8;
                    run = 0;
                }
                if (run == count)
                {
                    break;
                }
                if (!((1 << (bit + 7)) & byte))
                {
                    if (!run)
                    {
                        start = (bit + 7) + i * 8;
                    }
                    run++;
                }
                else
                {
                    start = (bit + 7) + i * 8;
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
            break;
        }
    }

    if (run >= count)
    {
        run = count;
        sub_2FD6F0(bitmap, start, run, 1);
        *handle = start | (run << bitmap->shift);
        return TRUE;
    }

    *handle = 0;
    return FALSE;
}

