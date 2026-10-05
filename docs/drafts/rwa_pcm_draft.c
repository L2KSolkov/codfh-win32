/* PARKED 2026-10-01: RW Audio's PCM depth/signedness converter sub_24A260 (a static the
 * compiler passes dest in eax and src in ecx) and its caller sub_24A740
 * (src/rwa/unit_249490.c; place sub_24A260 before sub_24A660 and sub_24A740 after it, with
 * sub_2421C0 and sub_249EF0 declared). sub_24A260 differs only in the address operand order of
 * the last loop's load ([esi+edi] where the image has [edi+esi]); sub_24A740 keeps `to` in ebx
 * and the destination in ebp (the image: ebp and ebx), with the result in the destination's
 * argument slot where the image keeps the saved destination. */
extern void *sub_2421C0(RwUInt32 count, RwUInt32 size, RwUInt32 hint);
extern RwUInt32 sub_249EF0(const RwaWaveFormat *from, const RwUInt8 *src, RwUInt32 srcSize,
                           const RwaWaveFormat *to, RwUInt8 *dest, RwUInt32 *used);

/* PCM bit depth and signedness conversion: 8 to 16 bits, 16 to 8 bits and
 * signed to unsigned and back at the same depth (unsigned when flags & 1);
 * the same format is copied. */
// match: _sub_24A260 @ 0x0024A260
static RwUInt32
sub_24A260(const RwaWaveFormat *from, const RwUInt8 *src, RwUInt32 srcSize, const RwaWaveFormat *to,
           RwUInt8 *dest, RwUInt32 *used)
{
    RwUInt32    spare;
    RwUInt32    total;
    RwUInt32    count;
    RwUInt32    i;

    if (!used)
    {
        used = &spare;
    }
    *used = sub_249C90(to, from, srcSize);
    src += srcSize;
    if (dest)
    {
        dest += *used;
    }

    if (from->bitDepth == 8 && to->bitDepth == 16)
    {
        total = from->length * 2;
        count = from->length - srcSize;
        if (from->flags & 1)
        {
            if (to->flags & 1)
            {
                if (dest)
                {
                    for (i = 0; i < count; i++)
                    {
                        ((RwUInt16 *)dest)[i] = (RwUInt16)(src[i] * 255.99609375f);
                    }
                }
                return total;
            }
            else
            {
                if (dest)
                {
                    for (i = 0; i < count; i++)
                    {
                        ((RwInt16 *)dest)[i] = (RwInt16)((src[i] - 128.0f) * 255.9921875f);
                    }
                }
                return total;
            }
        }
        else
        {
            if (to->flags & 1)
            {
                if (dest)
                {
                    for (i = 0; i < count; i++)
                    {
                        ((RwUInt16 *)dest)[i] = (RwUInt16)((((const RwInt8 *)src)[i] + 128.0f) * 255.99609375f);
                    }
                }
                return total;
            }
            else
            {
                if (dest)
                {
                    for (i = 0; i < count; i++)
                    {
                        ((RwInt16 *)dest)[i] = (RwInt16)(((const RwInt8 *)src)[i] * 255.9921875f);
                    }
                }
                return total;
            }
        }
    }

    if (from->bitDepth == 16 && to->bitDepth == 8)
    {
        total = from->length / 2;
        count = total - *used;
        if (from->flags & 1)
        {
            if (to->flags & 1)
            {
                if (dest)
                {
                    for (i = 0; i < count; i++)
                    {
                        dest[i] = (RwUInt8)(((const RwUInt16 *)src)[i] * 0.0038909912109375f);
                    }
                }
                return total;
            }
            else
            {
                if (dest)
                {
                    for (i = 0; i < count; i++)
                    {
                        dest[i] = (RwUInt8)((((const RwUInt16 *)src)[i] - 32768.0f) * 0.003875732421875f);
                    }
                }
                return total;
            }
        }
        else
        {
            if (to->flags & 1)
            {
                if (dest)
                {
                    for (i = 0; i < count; i++)
                    {
                        dest[i] = (RwUInt8)((((const RwInt16 *)src)[i] + 32768.0f) * 0.003875732421875f);
                    }
                }
                return total;
            }
            else
            {
                if (dest)
                {
                    for (i = 0; i < count; i++)
                    {
                        dest[i] = (RwUInt8)(((const RwInt16 *)src)[i] * 0.003875732421875f);
                    }
                }
                return total;
            }
        }
    }

    if (!(from->flags & 1) && (to->flags & 1))
    {
        total = from->length;
        if (from->bitDepth == 8 && to->bitDepth == 8)
        {
            count = total - *used;
            if (dest)
            {
                for (i = 0; i < count; i++)
                {
                    dest[i] = (RwUInt8)(((const RwInt8 *)src)[i] + 128.0f);
                }
            }
            return total;
        }
        if (from->bitDepth == 16 && to->bitDepth == 16)
        {
            count = total / 2 - *used;
            if (dest)
            {
                for (i = 0; i < count; i++)
                {
                    ((RwUInt16 *)dest)[i] = (RwUInt16)(((const RwInt16 *)src)[i] + 32768.0f);
                }
            }
            return total;
        }
    }
    else if ((from->flags & 1) && !(to->flags & 1))
    {
        total = from->length;
        if (from->bitDepth == 8 && to->bitDepth == 8)
        {
            count = total - *used;
            if (dest)
            {
                for (i = 0; i < count; i++)
                {
                    dest[i] = (RwUInt8)(src[i] - 128.0f);
                }
            }
            return total;
        }
        if (from->bitDepth == 16 && to->bitDepth == 16)
        {
            count = total / 2 - *used;
            if (dest)
            {
                for (i = 0; i < count; i++)
                {
                    ((RwInt16 *)dest)[i] = (RwInt16)(((const RwUInt16 *)src)[i] - 32768.0f);
                }
            }
            return total;
        }
    }
    else if (from->bitDepth == to->bitDepth)
    {
        if (dest)
        {
            memcpy(dest, src, from->length);
        }
        return from->length;
    }

    return 0;
}

/* PCM conversion: the bit depth and signedness first (into a buffer when
 * the sample rate changes too), then the sample rate. */
// match: _sub_24A740 @ 0x0024A740
RwUInt32
sub_24A740(const RwaWaveFormat *from, const RwUInt8 *src, RwUInt32 srcSize, const RwaWaveFormat *to,
           RwUInt8 *dest, RwUInt32 *used)
{
    RwaWaveFormat format;
    RwUInt32    result;
    RwUInt32    spare;
    RwUInt8    *buffer = NULL;
    RwUInt8    *final = dest;

    result = from->length;
    format = *from;
    spare = srcSize;
    if (!used)
    {
        used = &spare;
    }
    else
    {
        *used = srcSize;
    }

    if (format.bitDepth != to->bitDepth && format.sampleRate != to->sampleRate && dest)
    {
        RwaWaveFormat temp = format;

        temp.sampleRate = to->sampleRate;
        buffer = (RwUInt8 *)sub_2421C0(sub_249BF0(&temp, to), 1, rwaMEMHINTDUR_FUNCTION | rwaID_806);
        if (!buffer)
        {
            return 0;
        }
        dest = buffer;
    }

    if (format.bitDepth != to->bitDepth || ((format.flags ^ to->flags) & 1))
    {
        format.length = result = sub_24A260(&format, src, srcSize, to, dest, used);
        format.bitDepth = to->bitDepth;
        srcSize = *used;
    }

    if (buffer)
    {
        dest = final;
        src = buffer;
    }

    if (format.sampleRate != to->sampleRate)
    {
        result = sub_249EF0(&format, src, srcSize, to, dest, used);
    }

    if (buffer)
    {
        sub_2421B0(buffer);
    }

    return result;
}
