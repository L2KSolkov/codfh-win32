/* PARKED 2026-10-01: RW Audio's PCM channel conversion sub_249D00, IMA ADPCM encode sub_24BD30
 * (closest form: 36 lines, step/diff registers swapped), decode sub_24BDE0 and block decode
 * sub_24C560 (src/rwa/unit_249490.c; the step tables are word_42FD18/word_42FD38). The rest of
 * the x87 sample converters (0x249EF0-0x24C230) are not drafted yet. */

/* PCM channel conversion: mono to stereo duplicates, stereo to mono
 * averages (8 or 16 bits, unsigned when flags & 1). */

// match: _sub_249D00 @ 0x00249D00
RwUInt32
sub_249D00(const RwaWaveFormat *from, const RwUInt8 *src, RwUInt32 srcSize,
           const RwaWaveFormat *to, RwUInt8 *dest, RwUInt32 *used)
{
    RwUInt32    offset;
    RwUInt32    remaining;
    RwUInt32    size;
    RwUInt32    count;
    RwUInt8     bitDepth;
    RwUInt8    *out;
    RwUInt32    i;

    if (!used)
    {
        used = &srcSize;
    }
    offset = sub_249C90(to, from, srcSize);
    *used = offset;
    remaining = from->length - srcSize;
    src += srcSize;
    size = sub_249BF0(from, to);
    bitDepth = from->bitDepth;
    count = remaining / (bitDepth >> 3);
    if (!dest)
    {
        return size;
    }
    out = dest + offset;
    if (!out)
    {
        return size;
    }

    if (from->noChannels == 1 && to->noChannels == 2)
    {
        if (bitDepth == 8)
        {
            for (i = 0; i < count; i++)
            {
                *out++ = src[i];
                *out++ = src[i];
            }
        }
        else
        {
            RwUInt16   *out16 = (RwUInt16 *)out;

            for (i = 0; i < count; i++)
            {
                *out16++ = ((const RwUInt16 *)src)[i];
                *out16++ = ((const RwUInt16 *)src)[i];
            }
        }
    }
    else if (from->noChannels == 2 && to->noChannels == 1)
    {
        if (bitDepth == 8)
        {
            if (from->flags & 1)
            {
                for (i = 0; i < count; i += 2)
                {
                    *out++ = (RwUInt8)((RwUInt16)((RwUInt16)src[i] + (RwUInt16)src[i + 1]) >> 1);
                }
            }
            else
            {
                for (i = 0; i < count; i += 2)
                {
                    *out++ = (RwUInt8)((RwInt16)((RwInt8)src[i] + (RwInt8)src[i + 1]) / 2);
                }
            }
        }
        else if (from->flags & 1)
        {
            RwUInt16   *out16 = (RwUInt16 *)out;

            for (i = 0; i < count; i += 2)
            {
                *out16++ = (RwUInt16)((((const RwUInt16 *)src)[i]
                                       + ((const RwUInt16 *)src)[i + 1]) >> 1);
            }
        }
        else
        {
            RwInt16    *out16 = (RwInt16 *)out;

            for (i = 0; i < count; i += 2)
            {
                *out16++ = (RwInt16)((((const RwInt16 *)src)[i]
                                      + ((const RwInt16 *)src)[i + 1]) / 2);
            }
        }
    }
    else
    {
        memcpy(out, src, remaining);
    }

    return size;
}

/* IMA ADPCM: encodes a sample against the predictor and step index. */

RwUInt8
sub_24BD30(RwInt16 sample, RwInt32 *predicted, RwInt32 *index)
{
    RwInt32     step = word_42FD38[*index];
    RwInt32     s = sample;
    RwInt32     diff = s - *predicted;
    RwUInt8     code = 0;

    if (diff < 0)
    {
        code = 8;
        diff = -diff;
    }
    if (diff >= step)
    {
        code |= 4;
        diff -= step;
    }
    step >>= 1;
    if (diff >= step)
    {
        code |= 2;
        diff -= step;
    }
    step >>= 1;
    if (diff >= step)
    {
        code |= 1;
        diff -= step;
    }
    step >>= 1;
    if (code & 8)
    {
        *predicted = s - step + diff;
    }
    else
    {
        *predicted = step - diff + s;
    }
    if (*predicted > 32767)
    {
        *predicted = 32767;
    }
    else if (*predicted < -32768)
    {
        *predicted = -32768;
    }
    *index += word_42FD18[code];
    if (*index < 0)
    {
        *index = 0;
    }
    else if (*index > 88)
    {
        *index = 88;
    }

    return code;
}

/* IMA ADPCM: decodes a code into the predictor and step index. */

// match: _sub_24BDE0 @ 0x0024BDE0
void
sub_24BDE0(RwUInt32 code, RwInt32 *predicted, RwInt32 *index)
{
    RwUInt32    diff = ((code & 7) * 2 + 1) * word_42FD38[*index] >> 3;
    RwInt32     value = *predicted;

    if (code & 8)
    {
        value -= diff;
    }
    else
    {
        value += diff;
    }
    *predicted = value;
    if (value < -32768)
    {
        *predicted = -32768;
    }
    else if (value > 32767)
    {
        *predicted = 32767;
    }
    value = *index + word_42FD18[code];
    *index = value;
    if (value < 0)
    {
        *index = 0;
    }
    else if (value > 88)
    {
        *index = 88;
    }
}

/* Decodes mono IMA ADPCM blocks (a header, then 8 words of 8 codes; 65
 * samples). */

// match: _sub_24C560 @ 0x0024C560
RwBool
sub_24C560(const RwUInt32 *src, RwInt16 *dest, RwUInt32 blocks)
{
    while (blocks)
    {
        RwUInt32    header;
        RwInt32     predicted;
        RwInt32     index;
        RwInt32     j;

        blocks--;
        header = *src++;
        predicted = (RwInt16)header;
        index = (header >> 16) & 0x7F;
        if (index < 0 || index > 88)
        {
            return FALSE;
        }
        *dest++ = (RwInt16)predicted;
        for (j = 0; j < 8; j++)
        {
            RwUInt32    data = *src++;
            RwInt32     k;

            for (k = 0; k < 7 + (j != 7); k++)
            {
                sub_24BDE0(data & 0xF, &predicted, &index);
                *dest++ = (RwInt16)predicted;
                data >>= 4;
            }
        }
    }

    return TRUE;
}

extern const RwInt32 unk_42FCB0[][2];

/* XA-style ADPCM block decode (16-byte blocks: filter/range header, pad byte,
 * 28 nibbles); closest form: frame and instructions match, but the image keeps the older
 * history and the second coefficient in edi/ebp and the first coefficient in the count
 * argument's slot, where VC7.0 keeps the first coefficient in ebx. */

// match: _sub_24BC50 @ 0x0024BC50
void
sub_24BC50(const RwUInt8 *src, RwInt16 *dest, RwUInt32 blocks)
{
    RwInt32     s1 = 0;
    RwInt32     s2 = 0;
    RwInt32     k0;
    RwInt32     k1;
    RwInt32     shift;
    RwInt32     filter;
    RwUInt32    b;
    RwInt32     i;
    RwInt32     j;
    RwInt32     t;

    while (blocks--)
    {
        filter = *src >> 4;
        k0 = unk_42FCB0[filter][0];
        k1 = unk_42FCB0[filter][1];
        shift = 28 - (*src & 0x0F);
        src += 2;
        for (i = 0; i < 14; i++)
        {
            for (j = 0; j < 2; j++)
            {
                t = ((((RwInt32)((*src >> (j * 4)) << 28)) >> 28) << shift) + s1 * k0 + s2 * k1;
                t >>= 16;
                s2 = s1;
                s1 = t;
                *dest++ = (RwInt16)t;
            }
            src++;
        }
    }
}

/* sub_24B260, DSP ADPCM decode (closest form: the inner loop matches with two separate
 * parity tests -- one if/else lets VC7.0 hoist the coefficient products out of both
 * branches; the image indexes the coefficient pairs with [edx*4] and keeps the first
 * coefficient as a word in cx, this build shifts the index and widens at the load).
 * Needs #define HIST(_x) ((RwInt16)((_x) << 8) | ((_x) >> 8)). */
typedef struct { RwInt16 c1; RwInt16 c2; } rwaDSPCoef;

/* Decodes big-endian (GameCube DSP) ADPCM: the coefficients and the two
 * history samples from the format's header, then frames of a scale byte
 * and 14 nibbles. */
// match: _sub_24B260 @ 0x0024B260
void
sub_24B260(const RwaWaveFormat *format, const RwUInt8 *src, RwInt16 *dest)
{
    const RwUInt32 *header = (const RwUInt32 *)format->extra;
    const RwUInt16 *in;
    RwUInt32    remaining;
    RwUInt32    frames;
    RwUInt32    f;
    RwUInt32    count;
    RwUInt32    shift;
    RwUInt32    i;
    RwUInt32    j;
    RwInt32     hist1;
    RwInt32     hist2;
    RwInt16     c1;
    RwInt16     c2;
    RwInt32     sample;
    rwaDSPCoef  coef[8];
    const RwUInt8 *data = src;
    RwInt16    *out = dest;

    remaining = rwaSWAP32(header[0]) - 2;
    in = (const RwUInt16 *)&header[7];
    i = 0;
    do
    {
        ((RwInt16 *)coef)[i] = rwaSWAP16(*in);
        in++;
        i++;
    } while (i < 16);
    hist2 = HIST(((const RwUInt16 *)header)[0x20]);
    hist1 = HIST(((const RwUInt16 *)header)[0x21]);
    *out++ = (RwInt16)hist2;
    *out++ = (RwInt16)hist1;

    frames = (remaining + 13) / 14;
    for (f = 0; f < frames; f++)
    {
        c1 = coef[*data >> 4].c1;
        c2 = coef[*data >> 4].c2;
        shift = *data & 0x0F;
        data++;
        count = 14;
        if (remaining < 14)
        {
            count = remaining;
        }
        remaining -= count;
        for (j = 0; j < count; j++)
        {
            if (!(j & 1))
            {
                sample = ((((RwInt16)(*data << 8)) >> 12) << shift) + ((c2 * hist2) >> 11) + ((c1 * hist1) >> 11);
                if (sample > 0x7FFF)
                {
                    sample = 0x7FFF;
                }
                else if (sample < -0x8000)
                {
                    sample = -0x8000;
                }
                *out++ = (RwInt16)sample;

                hist2 = hist1;
                hist1 = sample;
                continue;
            }
            {
                sample = ((((RwInt16)(*data << 12)) >> 12) << shift) + ((c2 * hist2) >> 11) + ((c1 * hist1) >> 11);
                if (sample > 0x7FFF)
                {
                    sample = 0x7FFF;
                }
                else if (sample < -0x8000)
                {
                    sample = -0x8000;
                }
                *out++ = (RwInt16)sample;
                data++;
            }
            hist2 = hist1;
            hist1 = sample;
        }
    }
}

