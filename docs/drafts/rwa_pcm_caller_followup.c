/* PARKED: 24A740, 54 normalized diff lines (old draft 58).
 * Use with helper/declarations from rwa_pcm_draft.c.
 * Explicit allocation size restores the original call/push ordering.
 * Registers and stack homes still differ; not a match. */
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

        RwUInt32 size;
        temp.sampleRate = to->sampleRate;
        size = sub_249BF0(&temp, to);
        buffer = (RwUInt8 *)sub_2421C0(size, 1, rwaMEMHINTDUR_FUNCTION | rwaID_806);
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
