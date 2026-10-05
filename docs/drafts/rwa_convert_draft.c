/*
 * codfh-match: RenderWare Audio's wave format conversion (0x249490-):
 * the converters (51 at 0x42FDF0, each a step between two wave format
 * descriptions), the search for a chain of them between two formats (with
 * the last five chains cached), and the sample converters themselves.
 */
#include "rwa.h"
#include "rwaint.h"

extern RwBool sub_2429D0(const RwaWaveFormat *format1, const RwaWaveFormat *format2);
extern RwBool sub_242CC0(const rwaWaveFormatDesc *desc, const RwaWaveFormat *format);
extern void sub_242C60(const rwaWaveFormatDesc *desc, RwaWaveFormat *format, RwBool init);
extern void sub_2421B0(void *mem);
extern void *memcpy(void *dst, const void *src, RwUInt32 size);

extern rwaConverter unk_42FDF0[rwaNUMCONVERTERS];
extern rwaConversionPath unk_507A28[5];   /* the last chains found */
extern RwUInt32 dword_507BA4;               /* the next to replace */

/* The converter description reading (from) or writing format. */
// match: _sub_249490 @ 0x00249490
static const rwaWaveFormatDesc *
sub_249490(const RwaWaveFormat *format, RwBool from)
{
    RwUInt32    i;

    for (i = 0; i < rwaNUMCONVERTERS; i++)
    {
        if (from)
        {
            if (sub_242CC0(unk_42FDF0[i].info->from, format))
            {
                return unk_42FDF0[i].info->from;
            }
        }
        else if (sub_242CC0(unk_42FDF0[i].info->to, format))
        {
            return unk_42FDF0[i].info->to;
        }
    }

    return NULL;
}

/* A chain of at most maxSteps converters from (from, fromRate) to (to,
 * toRate): its steps in path, its length the result (0 when there is none).
 * The shortest found is cached. */
// match: _sub_2494F0 @ 0x002494F0
RwUInt32
sub_2494F0(const rwaWaveFormatDesc *from, RwUInt32 fromRate, const rwaWaveFormatDesc *to,
           RwUInt32 toRate, const rwaConverter **path, const rwaConverter **steps,
           RwUInt32 maxSteps, RwUInt32 depth, RwUInt32 best)
{
    RwUInt32    i;

    if (depth == maxSteps)
    {
        return 0;
    }

    if (!depth)
    {
        RwaWaveFormat fromFormat;
        RwaWaveFormat toFormat;
        rwaConversionPath *cached;

        sub_242C60(from, &fromFormat, TRUE);
        fromFormat.sampleRate = fromRate;
        sub_242C60(to, &toFormat, TRUE);
        toFormat.sampleRate = toRate;
        for (i = 0, cached = unk_507A28; i < sizeof(unk_507A28); i += sizeof(rwaConversionPath),
             cached++)
        {
            if (cached->count && sub_2429D0(&fromFormat, &cached->from)
                && sub_2429D0(&toFormat, &cached->to))
            {
                RwUInt32    n;

                for (n = 0; n < cached->count; n++)
                {
                    path[n] = cached->steps[n];
                }
                return cached->count;
            }
        }

        for (i = 0; i < rwaNUMCONVERTERS; i++)
        {
            const rwaConverterInfo *info = unk_42FDF0[i].info;

            if (from == info->from && to == info->to
                && (fromRate == toRate || (info->flags & 1)))
            {
                path[0] = &unk_42FDF0[i];
                return 1;
            }
        }
    }

    for (i = 0; i < rwaNUMCONVERTERS; i++)
    {
        const rwaConverter *converter = &unk_42FDF0[i];
        const rwaConverterInfo *info = converter->info;

        if (from == info->from)
        {
            RwUInt32    n;

            for (n = 0; n < depth; n++)
            {
                if (steps[n] == converter)
                {
                    break;
                }
            }
            if (n < depth)
            {
                continue;
            }

            if (to == info->to && (fromRate == toRate || (info->flags & 1)))
            {
                steps[depth] = converter;
                memcpy(path, steps, depth * 4 + 4);
                return depth ? depth : 1;
            }
            else
            {
                RwUInt32    rate = fromRate;
                RwUInt32    found;

                steps[depth] = converter;
                if (depth == best)
                {
                    return 0;
                }
                if (converter->info->flags & 1)
                {
                    rate = toRate;
                }
                found = sub_2494F0(converter->info->to, rate, to, toRate, path, steps, maxSteps,
                                   depth + 1, best);
                if (found)
                {
                    best = found;
                }
            }
        }
    }

    if (best == (RwUInt32)-1)
    {
        return 0;
    }
    if (!depth)
    {
        rwaConversionPath *cached = &unk_507A28[dword_507BA4];
        RwUInt32    n;

        best++;
        sub_242C60(from, &cached->from, TRUE);
        sub_242C60(to, &cached->to, TRUE);
        cached->from.sampleRate = fromRate;
        cached->count = best;
        cached->to.sampleRate = toRate;
        for (n = 0; n < best; n++)
        {
            cached->steps[n] = path[n];
        }
        if (++dword_507BA4 == 5)
        {
            dword_507BA4 = 0;
        }
    }
    return best;
}

/* The size of srcSize bytes of format from converted to format to (through
 * a chain of converters), and the source bytes used in *used. */
// match: _sub_2497A0 @ 0x002497A0
RwUInt32
sub_2497A0(const RwaWaveFormat *from, const void *src, const RwaWaveFormat *to,
           RwUInt32 srcSize, RwUInt32 *used)
{
    RwUInt32    i;
    RwUInt32    count;
    RwUInt32    size;
    const rwaConverter *path[4];
    RwaWaveFormat next;
    RwaWaveFormat current;
    const rwaWaveFormatDesc *fromDesc;
    const rwaWaveFormatDesc *toDesc;

    if (sub_2429D0(from, to))
    {
        if (used)
        {
            *used = srcSize;
        }
        return from->length;
    }

    fromDesc = sub_249490(from, TRUE);
    toDesc = sub_249490(to, FALSE);
    i = 0;
    count = sub_2494F0(fromDesc, from->sampleRate, toDesc, to->sampleRate, path,
                       (const rwaConverter **)&next, 4, 0, (RwUInt32)-1);
    current = *from;
    if (i < count)
    {
        do
        {
            sub_242C60(path[i]->info->to, &next, TRUE);
            if (path[i]->info->flags & 1)
            {
                next.sampleRate = to->sampleRate;
            }
            else
            {
                next.sampleRate = current.sampleRate;
            }
            next.length = path[i]->convert(&current, src, srcSize, &next, NULL, &size);
            if (!next.length)
            {
                return 0;
            }
            i++;
            srcSize = size;
            current = next;
        }
        while (i < count);
    }
    if (used)
    {
        *used = size;
    }
    return next.length;
}

// match: _sub_2498D0 @ 0x002498D0
RwUInt32
sub_2498D0(const RwaWaveFormat *from, const void *src, RwUInt32 srcSize, const RwaWaveFormat *to)
{
    RwUInt32    used;

    sub_2497A0(from, src, to, srcSize, &used);
    return used;
}

// match: _sub_249900 @ 0x00249900
RwUInt32
sub_249900(const RwaWaveFormat *from, const void *src, const RwaWaveFormat *to)
{
    return sub_2497A0(from, src, to, 0, NULL);
}
