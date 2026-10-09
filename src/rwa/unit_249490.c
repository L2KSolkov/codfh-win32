/*
 * codfh-match: RenderWare Audio's wave format conversion (0x249490-):
 * the converters (51 at 0x42FDF0, each a step between two wave format
 * descriptions), the search for a chain of them between two formats (with
 * the last five chains cached), and the sample converters themselves.
 */
#include "rwa.h"
#include "rwaint.h"

/* Big-endian (GameCube DSP) byte order. */
#define rwaSWAP32(_x) (((((_x) & 0xFF0000) | ((_x) >> 16)) >> 8) | ((((_x) & 0xFF00) | ((_x) << 16)) << 8))
#define rwaSWAP16(_x) ((RwUInt16)((((_x) >> 8) & 0xFF) | ((_x) << 8)))

extern const RwaUUID unk_3ED5CC;
extern RwInt32 RwaUUIDCompare(const RwaUUID *uuid1, const RwaUUID *uuid2);
extern const RwaUUID unk_3ED5BC;
extern RwReal flt_42FC88[5][2];  /* VAG prediction coefficients */
extern RwReal flt_42FCD8[16];  /* ADPCM filter coefficients */
extern void sub_242B30(RwaWaveFormat *format);
extern void *sub_242170(RwUInt32 size, RwUInt32 hint);
extern const RwReal flt_3D3CBC;   /* 32768 */

extern RwBool sub_2429D0(const RwaWaveFormat *format1, const RwaWaveFormat *format2);
extern RwBool sub_242CC0(const rwaWaveFormatDesc *desc, const RwaWaveFormat *format);
extern void sub_242C60(const rwaWaveFormatDesc *desc, RwaWaveFormat *format, RwBool init);
extern RwInt16 word_42FD18[16];   /* IMA ADPCM index steps */
extern RwInt16 word_42FD38[89];   /* IMA ADPCM step sizes */
extern void sub_2421B0(void *mem);

extern rwaConverter unk_42FDF0[rwaNUMCONVERTERS];
extern rwaConversionPath unk_507A28[5];
extern RwUInt32 dword_507BA4;
extern void *memcpy(void *, const void *, RwUInt32);


RwUInt32 sub_2494F0(const rwaWaveFormatDesc *from, RwUInt32 fromRate, const rwaWaveFormatDesc *to,
                    RwUInt32 toRate, const rwaConverter **path, const rwaConverter **steps,
                    RwUInt32 maxSteps, RwUInt32 depth, RwUInt32 best);

extern void sub_24BDE0(RwUInt32 code, RwInt32 *predicted, RwInt32 *index);
extern RwUInt8 sub_24BD30(RwInt16 sample, RwInt32 *predicted, RwInt32 *index);

/* The converter description reading (from) or writing format. */
extern void *sub_2421C0(RwUInt32 count, RwUInt32 size, RwUInt32 hint);

extern RwInt32 unk_42FCB0[][2];

#define RwaPcmDuplicateMacro(type) do { \
    const type *input = (const type *)src; \
    type *output = (type *)dest; \
    RwUInt32 outIndex = 0; \
    RwUInt32 inIndex; \
    for (inIndex = 0; inIndex < count; inIndex++) { \
        output[outIndex++] = input[inIndex]; \
        output[outIndex++] = input[inIndex]; \
    } \
} while (0)

#define RwaPcmAverageMacro(type, wide) do { \
    wide sample; \
    const type *input = (const type *)src; \
    type *output = (type *)dest; \
    RwUInt32 outIndex = 0; \
    RwUInt32 inIndex = 0; \
    while (inIndex < count) { \
        sample = input[inIndex++]; \
        sample += input[inIndex++]; \
        sample /= 2; \
        output[outIndex++] = (type)sample; \
    } \
} while (0)

#define RwaDspSwap16Macro(v) ((((v) & 0xFF00) >> 8) | (((v) & 0xFF) << 8))
#define RwaDspSwap32Macro(v) ((((v) & 0xFF000000) >> 24) | (((v) & 0xFF0000) >> 8) | (((v) & 0xFF00) << 8) | (((v) & 0xFF) << 24))

#include <math.h>


extern const RwaUUID unk_3ED5EC;
extern void sub_24B260(const RwaWaveFormat *format, const RwUInt8 *src, RwInt16 *dest);


// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: __real@3b7e0000 @ 0x003EDEA4
// match: __real@3b7f0000 @ 0x003EDEA8
// match: __real@437ffe00 @ 0x003EDEAC
// match: __real@437fff00 @ 0x003EDEB0
// match: __real@38000000 @ 0x003EDEB4
// match: __real@45000000 @ 0x003EDEB8

// What its data definitions name.
RwUInt32 sub_249D00(const RwaWaveFormat *from, const RwUInt8 *src, RwUInt32 srcSize, const RwaWaveFormat *to, RwUInt8 *dest, RwUInt32 *used);
extern RwUInt32 sub_249EF0(const RwaWaveFormat *from, const RwUInt8 *src, RwUInt32 srcSize, const RwaWaveFormat *to, RwUInt8 *dest, RwUInt32 *used);
RwUInt32 sub_24A660(const RwaWaveFormat *from, const RwUInt8 *src, RwUInt32 srcSize, const RwaWaveFormat *to, RwUInt8 *dest, RwUInt32 *used);
RwUInt32 sub_24A740(const RwaWaveFormat *from, const RwUInt8 *src, RwUInt32 srcSize, const RwaWaveFormat *to, RwUInt8 *dest, RwUInt32 *used);
RwUInt32 sub_24BE60(const RwaWaveFormat *from, const RwUInt8 *src, RwUInt32 srcSize, RwaWaveFormat *to, RwUInt8 *dest, RwUInt32 *used);
RwUInt32 sub_24BEF0(const RwaWaveFormat *from, const RwUInt8 *src, RwUInt32 srcSize, RwaWaveFormat *to, RwUInt8 *dest, RwUInt32 *used);
RwUInt32 sub_24C230(const RwaWaveFormat *from, const RwUInt8 *src, RwUInt32 srcSize, const RwaWaveFormat *to, RwUInt8 *dest, RwUInt32 *used);
RwUInt32 sub_24C8C0(const RwaWaveFormat *from, const RwUInt8 *src, RwUInt32 srcSize, const RwaWaveFormat *to, RwUInt8 *dest, RwUInt32 *used);
extern RwUInt8 unk_3EDC40[];
extern RwUInt8 unk_3EDC4C[];
extern RwUInt8 unk_3EDC58[];
extern RwUInt8 unk_3EDC64[];
extern RwUInt8 unk_3EDC70[];
extern RwUInt8 unk_3EDC7C[];
extern RwUInt8 unk_3EDC88[];
extern RwUInt8 unk_3EDC94[];
extern RwUInt8 unk_3EDCA0[];
extern RwUInt8 unk_3EDCAC[];
extern RwUInt8 unk_3EDCB8[];
extern RwUInt8 unk_3EDCC4[];
extern RwUInt8 unk_3EDCD0[];
extern RwUInt8 unk_3EDCDC[];
extern RwUInt8 unk_3EDCE8[];
extern RwUInt8 unk_3EDCF4[];
extern RwUInt8 unk_3EDD00[];
extern RwUInt8 unk_3EDD0C[];
extern RwUInt8 unk_3EDD18[];
extern RwUInt8 unk_3EDD24[];
extern RwUInt8 unk_3EDD30[];
extern RwUInt8 unk_3EDD3C[];
extern RwUInt8 unk_3EDD48[];
extern RwUInt8 unk_3EDD54[];
extern RwUInt8 unk_3EDD60[];
extern RwUInt8 unk_3EDD6C[];
extern RwUInt8 unk_3EDD78[];
extern RwUInt8 unk_3EDD84[];
extern RwUInt8 unk_3EDD90[];
extern RwUInt8 unk_3EDD9C[];
extern RwUInt8 unk_3EDDA8[];
extern RwUInt8 unk_3EDDB4[];
extern RwUInt8 unk_3EDDC0[];
extern RwUInt8 unk_3EDDCC[];
extern RwUInt8 unk_3EDDD8[];
extern RwUInt8 unk_3EDDE4[];
extern RwUInt8 unk_3EDDF0[];
extern RwUInt8 unk_3EDDFC[];
extern RwUInt8 unk_3EDE08[];
extern RwUInt8 unk_3EDE14[];
extern RwUInt8 unk_3EDE20[];
extern RwUInt8 unk_3EDE2C[];
extern RwUInt8 unk_3EDE38[];
extern RwUInt8 unk_3EDE44[];
extern RwUInt8 unk_3EDE50[];
extern RwUInt8 unk_3EDE5C[];
extern RwUInt8 unk_3EDE68[];
extern RwUInt8 unk_3EDE74[];
extern RwUInt8 unk_3EDE80[];
extern RwUInt8 unk_3EDE8C[];
extern RwUInt8 unk_3EDE98[];
// Its data definitions (PLAN M5), in the image's address order.
// 0x0042FC88
RwReal flt_42FC88[5][2] = {
    { 0.0f, 0.0f },
    { -0.9375f, 0.0f },
    { -1.796875f, 0.8125f },
    { -1.53125f, 0.859375f },
    { -1.90625f, 0.9375f },
};
// 0x0042FCB0
RwInt32 unk_42FCB0[5][2] = {
    { 0, 0 },
    { 61440, 0 },
    { 117760, -53248 },
    { 100352, -56320 },
    { 124928, -61440 },
};
// 0x0042FCD8
RwReal flt_42FCD8[16] = {
    0.0f,
    0.0f,
    0.9375f,
    0.0f,
    1.796875f,
    -0.8125f,
    1.53125f,
    -0.859375f,
    1.90625f,
    -0.9375f,
    1.2851562f,
    -0.828125f,
    1.9414062f,
    -0.9609375f,
    1.7382812f,
    -0.7578125f,
};
// 0x0042FD18
RwInt16 word_42FD18[16] = {
    -1,
    -1,
    -1,
    -1,
    2,
    4,
    6,
    8,
    -1,
    -1,
    -1,
    -1,
    2,
    4,
    6,
    8,
};
// 0x0042FD38
RwInt16 word_42FD38[89] = {
    7,
    8,
    9,
    10,
    11,
    12,
    13,
    14,
    16,
    17,
    19,
    21,
    23,
    25,
    28,
    31,
    34,
    37,
    41,
    45,
    50,
    55,
    60,
    66,
    73,
    80,
    88,
    97,
    107,
    118,
    130,
    143,
    157,
    173,
    190,
    209,
    230,
    253,
    279,
    307,
    337,
    371,
    408,
    449,
    494,
    544,
    598,
    658,
    724,
    796,
    876,
    963,
    1060,
    1166,
    1282,
    1411,
    1552,
    1707,
    1878,
    2066,
    2272,
    2499,
    2749,
    3024,
    3327,
    3660,
    4026,
    4428,
    4871,
    5358,
    5894,
    6484,
    7132,
    7845,
    8630,
    9493,
    10442,
    11487,
    12635,
    13899,
    15289,
    16818,
    18500,
    20350,
    22385,
    24623,
    27086,
    29794,
    32767,
};
// 0x0042FDF0
rwaConverter unk_42FDF0[51] = {
    { &unk_3EDC40, sub_24BE60 },
    { &unk_3EDC4C, sub_249EF0 },
    { &unk_3EDC58, sub_24A740 },
    { &unk_3EDC64, sub_24A740 },
    { &unk_3EDC70, sub_24A740 },
    { &unk_3EDC7C, sub_249D00 },
    { &unk_3EDC88, sub_249D00 },
    { &unk_3EDC94, sub_249EF0 },
    { &unk_3EDCA0, sub_249EF0 },
    { &unk_3EDCAC, sub_24A740 },
    { &unk_3EDCB8, sub_24A740 },
    { &unk_3EDCC4, sub_24A740 },
    { &unk_3EDCD0, sub_249D00 },
    { &unk_3EDCDC, sub_249D00 },
    { &unk_3EDCE8, sub_249EF0 },
    { &unk_3EDCF4, sub_249EF0 },
    { &unk_3EDD00, sub_24A740 },
    { &unk_3EDD0C, sub_24A740 },
    { &unk_3EDD18, sub_24A740 },
    { &unk_3EDD24, sub_249D00 },
    { &unk_3EDD30, sub_249D00 },
    { &unk_3EDD3C, sub_249EF0 },
    { &unk_3EDD48, sub_249EF0 },
    { &unk_3EDD54, sub_24A740 },
    { &unk_3EDD60, sub_24A740 },
    { &unk_3EDD6C, sub_24A740 },
    { &unk_3EDD78, sub_24A660 },
    { &unk_3EDD84, sub_24A660 },
    { &unk_3EDD90, sub_24C230 },
    { &unk_3EDD9C, sub_24C230 },
    { &unk_3EDDA8, sub_24C230 },
    { &unk_3EDDB4, sub_249D00 },
    { &unk_3EDDC0, sub_249D00 },
    { &unk_3EDDCC, sub_249EF0 },
    { &unk_3EDDD8, sub_24C230 },
    { &unk_3EDDE4, sub_24BEF0 },
    { &unk_3EDDF0, sub_24BEF0 },
    { &unk_3EDDFC, sub_24BEF0 },
    { &unk_3EDE5C, sub_249EF0 },
    { &unk_3EDE68, sub_249EF0 },
    { &unk_3EDE08, sub_24C8C0 },
    { &unk_3EDE14, sub_24C8C0 },
    { &unk_3EDE20, sub_24C8C0 },
    { &unk_3EDE2C, sub_24C8C0 },
    { &unk_3EDE38, sub_24C8C0 },
    { &unk_3EDE44, sub_24C8C0 },
    { &unk_3EDE50, sub_24C8C0 },
    { &unk_3EDE74, sub_24C8C0 },
    { &unk_3EDE80, sub_24C8C0 },
    { &unk_3EDE8C, sub_24C8C0 },
    { &unk_3EDE98, sub_24C8C0 },
};
// 0x00507A28
rwaConversionPath unk_507A28[5];
// 0x00507BA4
RwUInt32 dword_507BA4;
// End of its data definitions.

// match: _flt_42FC88 @ 0x0042FC88


// match: _unk_42FCB0 @ 0x0042FCB0


// match: _flt_42FCD8 @ 0x0042FCD8


// match: _word_42FD18 @ 0x0042FD18


// match: _word_42FD38 @ 0x0042FD38


// match: _unk_42FDF0 @ 0x0042FDF0

// match: _sub_249490 @ 0x00249490
// sp-match: _sub_249490 @ 0x0015D5D0

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

/* Debug _RwaWaveConvFindPath, rwad.dll 0x100AABAD: separate cache counter,
 * validity local and recursive depth updates preserve the original lifetimes. */
// match: _sub_2494F0 @ 0x002494F0
// sp-match: _sub_2494F0 @ 0x0015D630
RwUInt32
sub_2494F0(const rwaWaveFormatDesc *from, RwUInt32 fromRate, const rwaWaveFormatDesc *to,
           RwUInt32 toRate, const rwaConverter **path, const rwaConverter **steps,
           RwUInt32 maxSteps, RwUInt32 depth, RwUInt32 best)
{
    RwUInt32 i;
    RwUInt32 cacheIndex;

    if (depth == maxSteps)
        return 0;
    if (!depth)
    {
        RwaWaveFormat fromFormat;
        RwaWaveFormat toFormat;
        sub_242C60(from, &fromFormat, TRUE);
        fromFormat.sampleRate = fromRate;
        sub_242C60(to, &toFormat, TRUE);
        toFormat.sampleRate = toRate;
        for (cacheIndex = 0; cacheIndex < 5; cacheIndex++)
        {
            rwaConversionPath *cached = &unk_507A28[cacheIndex];
            if (cached->count && sub_2429D0(&fromFormat, &cached->from)
                && sub_2429D0(&toFormat, &cached->to))
            {
                for (cacheIndex = 0; cacheIndex < cached->count; cacheIndex++)
                    path[cacheIndex] = cached->steps[cacheIndex];
                return cached->count;
            }
        }
        for (i = 0; i < rwaNUMCONVERTERS; i++)
        {
            if (from == unk_42FDF0[i].info->from && to == unk_42FDF0[i].info->to
                && (fromRate == toRate || (fromRate != toRate && (unk_42FDF0[i].info->flags & 1))))
            {
                path[0] = &unk_42FDF0[i];
                return 1;
            }
        }
    }
    for (i = 0; i < rwaNUMCONVERTERS; i++)
    {
        RwBool valid = FALSE;
        if (from == unk_42FDF0[i].info->from)
        {
            RwUInt32 n;
            valid = TRUE;
            for (n = 0; n < depth; n++)
            {
                if (steps[n] == &unk_42FDF0[i])
                {
                    valid = FALSE;
                    break;
                }
            }
        }
        if (valid)
        {
            if (to == unk_42FDF0[i].info->to
                && (fromRate == toRate || (fromRate != toRate && (unk_42FDF0[i].info->flags & 1))))
            {
                steps[depth] = &unk_42FDF0[i];
                memcpy(path, steps, depth * 4 + 4);
                best = 0;
                if (depth == 0)
                    return 1;
                else
                    return depth;
            }
            else
            {
                RwUInt32 rate = fromRate;
                RwUInt32 found;
                steps[depth] = &unk_42FDF0[i];
                if (depth == best)
                    return 0;
                depth++;
                if (unk_42FDF0[i].info->flags & 1)
                    rate = toRate;
                found = sub_2494F0(unk_42FDF0[i].info->to, rate, to, toRate,
                                   path, steps, maxSteps, depth, best);
                depth--;
                if (found > 0)
                    best = found;
            }
        }
    }
    if (best != (RwUInt32)-1)
    {
        if (!depth)
        {
            rwaConversionPath *cached;
            RwUInt32 n;
            best++;
            cached = &unk_507A28[dword_507BA4];
            sub_242C60(from, &cached->from, TRUE);
            sub_242C60(to, &cached->to, TRUE);
            cached->count = best;
            cached->from.sampleRate = fromRate;
            cached->to.sampleRate = toRate;
            for (n = 0; n < best; n++)
                cached->steps[n] = path[n];
            /* Xbox does not contain the debug DLL's unused-step clearing loop. */
            if (++dword_507BA4 == 5)
                dword_507BA4 = 0;
        }
        return best;
    }
    else
        return 0;
}

/* The size of srcSize bytes of format from converted to format to (through
 * a chain of converters), and the source bytes used in *used. */
// match: _sub_2497A0 @ 0x002497A0
// sp-match: _sub_2497A0 @ 0x0015D8E0
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
// sp-match: _sub_2498D0 @ 0x0015DA10
RwUInt32
sub_2498D0(const RwaWaveFormat *from, const void *src, RwUInt32 srcSize, const RwaWaveFormat *to)
{
    RwUInt32    used;

    sub_2497A0(from, src, to, srcSize, &used);
    return used;
}

// match: _sub_249900 @ 0x00249900
// sp-match: _sub_249900 @ 0x0015DA40
RwUInt32
sub_249900(const RwaWaveFormat *from, const void *src, const RwaWaveFormat *to)
{
    return sub_2497A0(from, src, to, 0, NULL);
}

// match: _sub_249920 @ 0x00249920
// sp-match: _sub_249920 @ 0x0015DA60
RwUInt32
sub_249920(const RwaWaveFormat *from, const void *src, RwUInt32 srcSize,
           RwaWaveFormat *to, void *dest)
{
    RwUInt32 resultSize;
    RwUInt32 i;
    RwUInt32 count;
    RwUInt32 inputSize;
    RwUInt32 outputSize;
    RwUInt32 used;
    RwBool releaseExtra;
    const rwaConverter *path[4];
    RwaWaveFormat next;
    RwaWaveFormat current;
    const rwaWaveFormatDesc *fromDesc;
    const rwaWaveFormatDesc *toDesc;
    void *input;
    void *output;

    if (sub_2429D0(from, to))
    {
        memcpy(dest, src, from->length);
        return from->length;
    }

    fromDesc = sub_249490(from, TRUE);
    toDesc = sub_249490(to, FALSE);
    count = sub_2494F0(fromDesc, from->sampleRate, toDesc, to->sampleRate,
                       path, (const rwaConverter **)&next, 4, 0, (RwUInt32)-1);
    outputSize = 0;
    output = NULL;
    current = *from;
    rwaWaveFormatInit(&next);
    input = sub_2421C0(from->length, 1, rwaMEMHINTDUR_FUNCTION | rwaID_806);
    if (!input)
    {
        return 0;
    }
    inputSize = from->length;
    memcpy(input, src, inputSize);

    for (i = 0; i < count; i++)
    {
        RwUInt32 result;
        releaseExtra = TRUE;
        sub_242C60(path[i]->info->to, &next, TRUE);
        if (path[i]->info->flags & 1)
        {
            next.sampleRate = to->sampleRate;
        }
        else
        {
            next.sampleRate = current.sampleRate;
        }
        next.length = path[i]->convert(&current, src, srcSize, &next, NULL, &used);
        if (next.length > outputSize)
        {
            if (output)
            {
                sub_2421B0(output);
            }
            output = sub_2421C0(next.length, 1, rwaMEMHINTDUR_FUNCTION | rwaID_806);
            if (!output)
            {
                goto failed;
            }
            outputSize = next.length;
        }
        next.extra = to->extra;
        next.extraSize = to->extraSize;
        if (next.extra)
        {
            releaseExtra = FALSE;
        }
        result = next.length;
        if (result != path[i]->convert(&current, input, 0, &next, output, NULL))
        {
            goto failed;
        }
        if (i == count - 1)
        {
            to->extra = next.extra;
            to->extraSize = next.extraSize;
        }
        else if (releaseExtra)
        {
            sub_242B30(&next);
        }
        srcSize = used;
        current = next;
        {
            void *temp = input;
            input = output;
            output = temp;
        }
        {
            RwUInt32 tempSize = inputSize;
            inputSize = outputSize;
            outputSize = tempSize;
        }
    }
    resultSize = next.length;
    memcpy(dest, input, resultSize);
    sub_2421B0(input);
    sub_2421B0(output);
    return resultSize;

failed:
    if (output)
    {
        sub_2421B0(output);
    }
    if (input)
    {
        sub_2421B0(input);
    }
    return 0;
}

// match: _sub_249BF0 @ 0x00249BF0
// sp-match: _sub_249BF0 @ 0x0015DD30
static RwUInt32
sub_249BF0(const RwaWaveFormat *from, const RwaWaveFormat *to)
{
    RwUInt32    align = to->bitDepth >> 3;
    RwReal      size;

    size = ((RwReal)to->noChannels / from->noChannels) * ((RwReal)to->bitDepth / from->bitDepth)
           * ((RwReal)to->sampleRate / (RwReal)from->sampleRate) * (RwReal)from->length;
    size = (RwReal)(((RwUInt32)size + align - 1) & ~(align - 1));

    return (RwUInt32)size;
}

/* The converted size of srcSize bytes (whole samples, rounded to nearest). */

// match: _sub_249C90 @ 0x00249C90
// sp-match: _sub_249C90 @ 0x0015DDD0
static RwUInt32
sub_249C90(const RwaWaveFormat *from, RwUInt32 srcSize, const RwaWaveFormat *to)
{
    RwUInt32    align = to->bitDepth >> 3;
    RwUInt32    size;

    size = (RwUInt32)(((RwReal)sub_249BF0(from, to) / (RwReal)from->length) * (RwReal)srcSize);
    if (size & (align - 1))
    {
        size = (size - (align >> 1)) / align * align;
    }

    return size;
}

/* PCM channel conversion: mono to stereo duplicates, stereo to mono
 * averages (8 or 16 bits, unsigned when flags & 1). */

/* Debug reference: rwad.dll _RwaWaveConvChannelPCM, core at 0x100AC076. */
// match: _sub_249D00 @ 0x00249D00
// sp-match: _sub_249D00 @ 0x0015DE40
RwUInt32
sub_249D00(const RwaWaveFormat *from, const RwUInt8 *src, RwUInt32 srcSize,
           const RwaWaveFormat *to, RwUInt8 *dest, RwUInt32 *used)
{
    RwUInt32 size;
    RwUInt32 spare;
    RwUInt32 count;
    RwUInt32 remaining;

    if (!used)
    {
        used = &spare;
    }
    *used = sub_249C90(from, srcSize, to);
    remaining = from->length - srcSize;
    src += srcSize;
    size = sub_249BF0(from, to);
    count = remaining / (from->bitDepth >> 3);
    if (dest)
    {
        dest += *used;
    }
    if (dest)
    {
        if (from->noChannels == 1 && to->noChannels == 2)
        {
            if (from->bitDepth == 8)
            {
                RwaPcmDuplicateMacro(RwUInt8);
            }
            else
            {
                RwaPcmDuplicateMacro(RwUInt16);
            }
        }
        else if (from->noChannels == 2 && to->noChannels == 1)
        {
            if (from->bitDepth == 8)
            {
                if (from->flags & 1)
                {
                    RwaPcmAverageMacro(RwUInt8, RwUInt16);
                }
                else
                {
                    RwaPcmAverageMacro(RwInt8, RwInt16);
                }
            }
            else if (from->flags & 1)
            {
                RwaPcmAverageMacro(RwUInt16, RwUInt32);
            }
            else
            {
                RwaPcmAverageMacro(RwInt16, RwInt32);
            }
        }
        else
        {
            memcpy(dest, src, remaining);
        }
    }
    return size;
}
#undef RwaPcmDuplicateMacro
#undef RwaPcmAverageMacro

/* 16-bit PCM to float samples and back (the float ones are
 * RwaWaveFormat 0x3ED5CC). */
extern RwUInt32 sub_249EF0(const RwaWaveFormat *from, const RwUInt8 *src, RwUInt32 srcSize, const RwaWaveFormat *to, RwUInt8 *dest, RwUInt32 *used);

/* Debug reference: rwad.dll 0x100AC936 (_RwaWaveConvResamplePCM). */
// match: _sub_249EF0 @ 0x00249EF0
// sp-match: _sub_249EF0 @ 0x0015E030
RwUInt32
sub_249EF0(const RwaWaveFormat *from, const RwUInt8 *src, RwUInt32 srcSize,
           const RwaWaveFormat *to, RwUInt8 *dest, RwUInt32 *used)
{
    RwUInt32 total;
    RwUInt32 spare;
    RwUInt32 kind;
    RwReal ratio;
    RwUInt32 count;
    RwReal result;
    RwReal value;
    RwUInt32 outputIndex;
    RwUInt32 channel;
    RwUInt32 sourceIndex;
    RwReal phase;
    RwReal next[6];
    RwReal previous[6];
    RwReal fraction;
    RwUInt32 inputIndex;
    RwUInt8 channels;

    if (!used)
    {
        used = &spare;
    }
    *used = sub_249C90(from, srcSize, to);
    src += srcSize;
    total = sub_249BF0(from, to);
    if (dest)
    {
        dest += *used;
    }
    if (to->bitDepth == 8)
    {
        kind = (to->flags & 1) ? 1 : 2;
    }
    else
    {
        kind = (to->flags & 1) ? 3 : 4;
    }
    value = 0.0f;
    channels = to->noChannels;
    count = (total - *used) / (to->bitDepth >> 3);
    ratio = (RwReal)from->sampleRate / (RwReal)to->sampleRate;
    if (channels > 1)
    {
        count &= ~(channels - 1);
    }
    if (!dest || from->sampleRate == to->sampleRate)
    {
        if (dest)
        {
            memcpy(dest, src, total);
        }
        return total - *used;
    }
    for (channel = 0; channel < channels; channel++)
    {
        switch (kind)
        {
            case 1: value = src[channel]; break;
            case 2: value = (RwInt8)src[channel]; break;
            case 3: value = ((const RwUInt16 *)src)[channel]; break;
            case 4: value = ((const RwInt16 *)src)[channel]; break;
            default: return 0;
        }
        previous[channel] = value;
    }
    outputIndex = 0;
    inputIndex = 0;
    phase = 0.0f;
    while (outputIndex < count)
    {
        fraction = phase - (RwUInt32)phase;
        for (channel = 0; channel < channels; channel++)
        {
            sourceIndex = channels * inputIndex + channel;
            switch (kind)
            {
                case 1: value = src[sourceIndex]; break;
                case 2: value = (RwInt8)src[sourceIndex]; break;
                case 3: value = ((const RwUInt16 *)src)[sourceIndex]; break;
                case 4: value = ((const RwInt16 *)src)[sourceIndex]; break;
            }
            next[channel] = value;
            result = fraction * next[channel] + (1.0f - fraction) * previous[channel];
            switch (kind)
            {
                case 1: dest[outputIndex] = (RwUInt8)(RwUInt32)result; break;
                case 2: dest[outputIndex] = (RwUInt8)(RwInt8)(RwUInt32)result; break;
                case 3: ((RwUInt16 *)dest)[outputIndex] = (RwUInt16)(RwUInt32)result; break;
                case 4: ((RwInt16 *)dest)[outputIndex] = (RwInt16)(RwUInt32)result; break;
            }
            outputIndex++;
            previous[channel] = next[channel];
        }
        phase += ratio;
        while (phase > 1.0f)
        {
            phase -= 1.0f;
            inputIndex++;
        }
    }
    return total;
}
/* PCM bit depth and signedness conversion: 8 to 16 bits, 16 to 8 bits and
 * signed to unsigned and back at the same depth (unsigned when flags & 1);
 * the same format is copied. */
// match: _sub_24A260 @ 0x0024A260
// sp-match: _sub_24A260 @ 0x0015E3A0
static RwUInt32
sub_24A260(const RwaWaveFormat *from, const RwUInt8 *src, RwUInt32 srcSize, const RwaWaveFormat *to,
           RwUInt8 *dest, RwUInt32 *used)
{
    RwUInt32    spare;
    RwUInt32    total;
    RwUInt32    count;


    if (!used)
    {
        used = &spare;
    }
    *used = sub_249C90(from, srcSize, to);
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
                    RwUInt32 i;
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
                    RwUInt32 i;
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
                    RwUInt32 i;
                    for (i = 0; i < count; i++)
                    {
                        ((RwUInt16 *)dest)[i] = (RwUInt16)(((RwInt8)src[i] + 128.0f) * 255.99609375f);
                    }
                }
                return total;
            }
            else
            {
                if (dest)
                {
                    RwUInt32 i;
                    for (i = 0; i < count; i++)
                    {
                        ((RwInt16 *)dest)[i] = (RwInt16)((RwInt8)src[i] * 255.9921875f);
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
                    RwUInt32 i;
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
                    RwUInt32 i;
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
                    RwUInt32 i;
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
                    RwUInt32 i;
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
                RwUInt32 i;
                for (i = 0; i < count; i++)
                {
                    dest[i] = (RwUInt8)((RwInt8)src[i] + 128.0f);
                }
            }
            return total;
        }
        if (from->bitDepth == 16 && to->bitDepth == 16)
        {
            count = total / 2 - *used;
            if (dest)
            {
                RwUInt32 i;
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
                RwUInt32 i;
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
                RwUInt32 i;
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



// match: _sub_24A660 @ 0x0024A660
// sp-match: _sub_24A660 @ 0x0015E7A0
RwUInt32
sub_24A660(const RwaWaveFormat *from, const RwUInt8 *src, RwUInt32 srcSize, const RwaWaveFormat *to,
           RwUInt8 *dest, RwUInt32 *used)
{
    RwUInt32    total;
    RwUInt32    spare;
    RwUInt32    count;
    RwUInt32    i;

    if (!used)
    {
        used = &spare;
    }
    if (!RwaUUIDCompare(from->dataType, &unk_3ED5CC))
    {
        const RwInt16 *in;
        RwReal     *out;

        total = from->length * 2;
        *used = srcSize * 2;
        count = (total - srcSize * 2) / 4;
        in = (const RwInt16 *)(src + srcSize);
        out = (RwReal *)(dest + srcSize * 2);
        if (dest)
        {
            for (i = 0; i < count; i++)
            {
                out[i] = in[i] * (1.0f / 32768.0f);
            }
        }
    }
    else
    {
        const RwReal *in;
        RwInt16    *out;

        total = from->length / 2;
        *used = srcSize / 2;
        count = (total - srcSize / 2) / 2;
        in = (const RwReal *)(src + srcSize);
        out = (RwInt16 *)(dest + srcSize / 2);
        if (dest)
        {
            for (i = 0; i < count; i++)
            {
                out[i] = (RwInt16)(in[i] * 32768.0f);
            }
        }
    }

    return total;
}

/* PCM conversion: the bit depth and signedness first (into a buffer when
 * the sample rate changes too), then the sample rate. */
// match: _sub_24A740 @ 0x0024A740
// sp-match: _sub_24A740 @ 0x0015E880
RwUInt32
sub_24A740(const RwaWaveFormat *from, const RwUInt8 *src, RwUInt32 srcSize, const RwaWaveFormat *to,
           RwUInt8 *dest, RwUInt32 *used)
{
    RwaWaveFormat format;
    RwUInt32    result;
    RwUInt32    spare;
    RwUInt8 *buffer;
    RwUInt8 *final;

    result = from->length;
    spare = srcSize;
    buffer = NULL;
    final = dest;
    format = *from;
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

/* Writes the 0x60-byte big-endian ADPCM header into the format's extra
 * data: the sample count, the nibble count, the 16 coefficients and the
 * two history samples; returns its size. */
// match: _sub_24A880 @ 0x0024A880
// sp-match: _sub_24A880 @ 0x0015E9C0
static RwUInt32
sub_24A880(RwaWaveFormat *format, const RwInt16 *history, RwUInt32 size, const RwaWaveFormat *from)
{
    RwUInt32   *header;
    RwUInt16   *coef;
    RwUInt32    samples;
    RwUInt32    nibbles;
    RwUInt16    c;

    if (format->extraSize < 0x60)
    {
        sub_242B30(format);
    }
    if (!format->extra)
    {
        format->extra = sub_242170(0x60, rwaMEMHINTDUR_EVENT | rwaID_806);
        if (!format->extra)
        {
            return 0;
        }
        format->extraSize = 0x60;
    }

    header = (RwUInt32 *)format->extra;
    memset(header, 0, 0x60);

    samples = 0;
    if (!RwaUUIDCompare(from->dataType, &unk_3ED5BC))
    {
        samples = size * 7 / 4;
    }
    else if (!RwaUUIDCompare(from->dataType, &unk_3ED5CC))
    {
        if (from->bitDepth == 16)
        {
            samples = size / 2;
        }
        else if (from->bitDepth == 8)
        {
            samples = size;
        }
    }
    header[0] = rwaSWAP32(samples);

    nibbles = ((samples / 14) * 16 + samples % 14 + 1) & ~1;
    header[1] = rwaSWAP32(nibbles);

    coef = (RwUInt16 *)&header[7];
    *coef++ = rwaSWAP16((RwUInt16)(RwInt16)(flt_42FCD8[0] * 2048.0f));
    *coef++ = rwaSWAP16((RwUInt16)(RwInt16)(flt_42FCD8[1] * 2048.0f));
    *coef++ = rwaSWAP16((RwUInt16)(RwInt16)(flt_42FCD8[2] * 2048.0f));
    *coef++ = rwaSWAP16((RwUInt16)(RwInt16)(flt_42FCD8[3] * 2048.0f));
    *coef++ = rwaSWAP16((RwUInt16)(RwInt16)(flt_42FCD8[4] * 2048.0f));
    *coef++ = rwaSWAP16((RwUInt16)(RwInt16)(flt_42FCD8[5] * 2048.0f));
    *coef++ = rwaSWAP16((RwUInt16)(RwInt16)(flt_42FCD8[6] * 2048.0f));
    *coef++ = rwaSWAP16((RwUInt16)(RwInt16)(flt_42FCD8[7] * 2048.0f));
    *coef++ = rwaSWAP16((RwUInt16)(RwInt16)(flt_42FCD8[8] * 2048.0f));
    *coef++ = rwaSWAP16((RwUInt16)(RwInt16)(flt_42FCD8[9] * 2048.0f));
    *coef++ = rwaSWAP16((RwUInt16)(RwInt16)(flt_42FCD8[10] * 2048.0f));
    *coef++ = rwaSWAP16((RwUInt16)(RwInt16)(flt_42FCD8[11] * 2048.0f));
    *coef++ = rwaSWAP16((RwUInt16)(RwInt16)(flt_42FCD8[12] * 2048.0f));
    *coef++ = rwaSWAP16((RwUInt16)(RwInt16)(flt_42FCD8[13] * 2048.0f));
    *coef++ = rwaSWAP16((RwUInt16)(RwInt16)(flt_42FCD8[14] * 2048.0f));
    *coef++ = rwaSWAP16((RwUInt16)(RwInt16)(flt_42FCD8[15] * 2048.0f));

    c = history[0];
    ((RwUInt16 *)header)[0x20] = rwaSWAP16(c);
    c = history[1];
    ((RwUInt16 *)header)[0x21] = rwaSWAP16(c);

    return 0x60;
}

/* Repacks 16-byte ADPCM blocks (a header byte, a pad byte and 14 data bytes)
 * into two 8-byte groups, each the header's converted step index then seven
 * nibble-swapped data bytes; returns the bytes written. */
/* _RwaWaveConvGCNADPCMEncode, rwad.dll 0x100AF723: staged residuals,
 * signed histories and the 32767.0f residual scale match the Xbox encoder. */
// match: _sub_24AB90 @ 0x0024AB90
// sp-match: _sub_24AB90 @ 0x0015ECD0
static RwUInt32
sub_24AB90(const RwInt16 *src, RwUInt32 srcSize, RwUInt8 *dest,
          RwInt8 channels, RwInt8 channel, RwUInt32 destSize)
{
    RwUInt32 remaining;
    RwInt32 best;
    RwUInt32 amount;
    RwReal predicted;
    RwUInt8 block[8];
    RwInt32 shift;
    RwReal residual[14];
    RwInt32 value;
    RwUInt32 samples;
    RwReal error1;
    RwReal error2;
    RwReal s1;
    RwReal input[14];
    RwUInt32 i;
    RwReal delta;
    RwReal s2;
    RwUInt8 *output;
    RwUInt32 frames;
    RwReal reconstructed;
    RwReal minimum;
    RwUInt32 f;
    RwUInt8 *nibble;
    RwUInt8 *filters;
    RwInt32 quantized;
    RwReal peak;
    RwReal history1;
    const RwInt16 *data;
    RwUInt32 frame;
    RwInt32 encoded;
    RwReal history2;

    samples = (srcSize / 2) / channels;
    frames = (samples + 13) / 14;
    output = dest;
    data = src + channel;
    filters = sub_242170(frames, rwaMEMHINTDUR_FUNCTION | rwaID_806);
    history2 = *data * (1.0f / 32768.0f);
    data += channels;
    history1 = *data * (1.0f / 32768.0f);
    data += channels;
    remaining = samples - 2;
    for (frame = 0; frame < frames; frame++)
    {
        amount = 14;
        if (remaining < 14)
            amount = remaining;
        remaining -= amount;
        memset(input, 0, sizeof(input));
        for (i = 0; i < amount; i++)
        {
            input[i] = *data * (1.0f / 32768.0f);
            data += channels;
        }
        minimum = 3.402823466e+38F; /* FLT_MAX */
        best = -1;
        for (f = 0; f < 8; f++)
        {
            s2 = history2;
            s1 = history1;
            peak = 0;
            for (i = 0; i < 14; i++)
            {
                delta = input[i] - ((s1 * flt_42FCD8[f * 2]) + s2 * flt_42FCD8[f * 2 + 1]);
                s2 = s1;
                s1 = input[i];
                if ((RwReal)fabs(delta) >= peak)
                    peak = (RwReal)fabs(delta);
            }
            if (peak <= minimum)
            {
                minimum = peak;
                best = f;
            }
        }
        history2 = s2;
        history1 = s1;
        filters[frame] = (RwUInt8)best;
    }
    data = src + channel;
    s2 = *data * (1.0f / 32768.0f);
    data += channels;
    s1 = *data * (1.0f / 32768.0f);
    data += channels;
    error2 = 0;
    error1 = 0;
    remaining = samples - 2;
    for (frame = 0; frame < frames; frame++)
    {
        amount = 14;
        if (remaining < 14)
            amount = remaining;
        remaining -= amount;
        memset(input, 0, sizeof(input));
        for (i = 0; i < amount; i++)
        {
            input[i] = *data * (1.0f / 32768.0f);
            data += channels;
        }
        minimum = 0;
        for (i = 0; i < 14; i++)
        {
            delta = input[i] - (s1 * flt_42FCD8[filters[frame] * 2] + s2 * flt_42FCD8[filters[frame] * 2 + 1]);
            s2 = s1;
            s1 = input[i];
            residual[i] = delta * 32767.0f;
            if ((RwReal)fabs(residual[i]) > minimum)
                minimum = (RwReal)fabs(residual[i]);
        }
        value = (RwInt32)minimum;
        if (value > 32767)
            value = 32767;
        if (value < -32768)
            value = -32768;
        i = 0x4000;
        for (shift = 12; shift >= 0; shift--, i >>= 1)
        {
            if ((value + (i >> 3)) & i)
                break;
        }
        if (shift < 0)
            shift = 0;
        else if (shift > 12)
            shift = 12;
        memset(block, 0, 8);
        block[0] = (RwUInt8)((filters[frame] << 4) | shift);
        shift = 12 - shift;
        nibble = block + 1;
        for (i = 0; i < amount; i++)
        {
            predicted = residual[i] - (error1 * flt_42FCD8[filters[frame] * 2] + error2 * flt_42FCD8[filters[frame] * 2 + 1]);
            encoded = (RwInt32)(predicted * (1 << shift));
            quantized = (encoded + 0x800) & ~0xFFF;
            if (quantized > 32767)
                quantized = 32767;
            else if (quantized < -32768)
                quantized = -32768;
            if (i & 1)
            {
                *nibble |= (RwUInt8)((quantized >> 12) & 15);
                nibble++;
            }
            else
                *nibble = (RwUInt8)((quantized >> 8) & 0xF0);
            reconstructed = (RwReal)(quantized >> shift);
            error2 = error1;
            error1 = reconstructed - predicted;
        }
        memcpy(output, block, 8);
        output += 8;
    }
    sub_2421B0(filters);
    return frames * 8;
}

/* Debug reference: rwad.dll _RwaWaveConvGCNADPCMDecode at 0x100B007E. */
// match: _sub_24B260 @ 0x0024B260
// sp-match: _sub_24B260 @ 0x0015F3A0
void
sub_24B260(const RwaWaveFormat *format, const RwUInt8 *src, RwInt16 *dest)
{
    const RwUInt8 *header;
    RwUInt32 number;
    RwUInt32 remaining;
    RwUInt32 count;
    RwInt32 result;
    RwInt16 coef[16];
    RwInt16 sample;
    RwUInt32 shift;
    RwInt16 c1;
    RwInt16 c2;
    RwUInt32 i;
    RwUInt32 j;
    RwUInt32 frames;
    RwInt32 hist1;
    RwInt32 hist2;
    RwUInt32 filter;
    const RwUInt8 *data;
    RwInt16 *out;

    header = (const RwUInt8 *)format->extra;
    number = *(const RwUInt32 *)header;
    number = RwaDspSwap32Macro(number);
    remaining = number - 2;
    for (i = 0; i < 16; i++)
    {
        sample = ((const RwInt16 *)(header + 0x1C))[i];
        sample = RwaDspSwap16Macro(sample);
        coef[i] = sample;
    }
    sample = *(const RwInt16 *)(header + 0x40);
    sample = RwaDspSwap16Macro(sample);
    hist2 = sample;
    sample = *(const RwInt16 *)(header + 0x42);
    sample = RwaDspSwap16Macro(sample);
    hist1 = sample;
    frames = (remaining + 13) / 14;
    data = src;
    out = dest;
    *out++ = (RwInt16)hist2;
    *out++ = (RwInt16)hist1;
    for (i = 0; i < frames; i++)
    {
        filter = *data >> 4;
        shift = *data & 15;
        c1 = coef[filter << 1];
        c2 = coef[(filter << 1) + 1];
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
                sample = (*data & 0xF0) << 8;
                sample >>= 12;
                result = (sample << shift) + ((c1 * hist1) >> 11) + ((c2 * hist2) >> 11);
                if (result > 32767)
                    result = 32767;
                else if (result < -32768)
                    result = -32768;
                *out++ = (RwInt16)result;
                hist2 = hist1;
                hist1 = result;
            }
            else
            {
                sample = (*data & 15) << 12;
                sample >>= 12;
                result = (sample << shift) + ((c1 * hist1) >> 11) + ((c2 * hist2) >> 11);
                if (result > 32767)
                    result = 32767;
                else if (result < -32768)
                    result = -32768;
                *out++ = (RwInt16)result;
                hist2 = hist1;
                hist1 = result;
                data++;
            }
        }
    }
}


// match: _sub_24B430 @ 0x0024B430
// sp-match: _sub_24B430 @ 0x0015F570
RwUInt32
sub_24B430(const RwUInt8 *src, RwInt32 size, RwUInt8 *dest)
{
    RwInt32     blocks = (size + 15) / 16;
    RwInt32     groups = blocks * 2;
    const RwUInt8 *in = src;
    RwUInt8    *out = dest;
    RwInt32     i;
    RwInt32     j;
    RwInt32     k;
    RwUInt8     header;

    for (i = 0; i < blocks; i++)
    {
        header = (RwUInt8)((in[0] & 0xF0) | (12 - (in[0] & 0x0F)));
        in += 2;
        for (j = 0; j < 2; j++)
        {
            *out++ = header;
            for (k = 0; k < 7; k++)
            {
                out[k] = (RwUInt8)((*in >> 4) | (*in << 4));
                in++;
            }
            out += 7;
        }
    }

    return groups * 8;
}

/* PCM to the big-endian ADPCM format: the header into the output format's
 * extra data, then the samples repacked. */
// match: _sub_24B510 @ 0x0024B510
// sp-match: _sub_24B510 @ 0x0015F650
static void
sub_24B510(const RwInt16 *src, RwUInt8 *dest, RwInt32 *history1,
          RwInt32 *history2, RwReal *error1, RwReal *error2)
{
    RwReal sample;
    RwReal magnitude;
    RwReal error;
    RwReal maximum[5];
    RwInt32 shift;
    RwReal residual[5][28];
    RwInt32 value;
    RwInt32 i;
    RwInt32 filter;
    RwInt32 j;
    RwInt32 s1;
    RwInt16 clamped[28];
    RwInt32 s2;
    RwInt32 quantized;
    RwReal predicted;
    RwReal minimum = 10000000000.0f;
    s1 = 0;
    s2 = 0;
    filter = 0;

    for (i = 0; i < 28; i++)
    {
        if (src[i] > 0x77FF)
            clamped[i] = 0x77FF;
        else if (src[i] < -0x7800)
            clamped[i] = -0x7800;
        else
            clamped[i] = src[i];
    }
    for (j = 0; j < 5; j++)
    {
        s1 = *history1;
        s2 = *history2;
        maximum[j] = 0;
        for (i = 0; i < 28; i++)
        {
            sample = (RwReal)clamped[i];
            sample += s1 * flt_42FC88[j][0] + s2 * flt_42FC88[j][1];
            residual[j][i] = sample;
            magnitude = (RwReal)fabs(sample);
            if (maximum[j] < magnitude)
                maximum[j] = magnitude;
            s2 = s1;
            s1 = clamped[i];
        }
        if (minimum > maximum[j])
        {
            minimum = maximum[j];
            filter = j;
        }
        if (j == 0 && maximum[0] <= 7.0f)
        {
            filter = 0;
            break;
        }
    }
    *history1 = s1;
    *history2 = s2;
    value = (RwInt32)maximum[filter];
    if (value > 32767)
        value = 32767;
    else if (value < -32768)
        value = -32768;
    i = 0x4000;
    for (shift = 0; shift < 12; shift++, i >>= 1)
    {
        if ((value + (i >> 3)) & i)
            break;
    }
    {
        /* Preserve the selected row while filter becomes the packed header. */
        RwInt32 selectedFilter = filter;
        filter = ((selectedFilter << 4) & 0xF0) | (shift & 15);
        dest[0] = (RwUInt8)filter;
        dest[1] = 0;
        dest += 2;
        for (i = 0; i < 28; i++)
        {
            const RwReal *coefficient0 = &flt_42FC88[selectedFilter][0];
            const RwReal *coefficient1 = &flt_42FC88[selectedFilter][1];
            predicted = residual[selectedFilter][i]
                      + ((*error1) * (*coefficient0))
                      + ((*error2) * (*coefficient1));
            value = (RwInt32)(predicted * (1 << shift));
            quantized = (value + 0x800) & ~0xFFF;
            if (quantized > 32767)
                quantized = 32767;
            else if (quantized < -32768)
                quantized = -32768;
            if (i & 1)
            {
                *dest |= (RwUInt8)((quantized >> 8) & 0xF0);
                dest++;
            }
            else
                *dest = (RwUInt8)((quantized >> 12) & 15);
            magnitude = (RwReal)(quantized >> shift);
            error = magnitude - predicted;
            *error2 = *error1;
            *error1 = error;
        }
    }
}

// match: _sub_24BB00 @ 0x0024BB00
// sp-match: _sub_24BB00 @ 0x0015FC40
static RwUInt32
sub_24BB00(const RwInt16 *src, RwUInt32 srcSize, RwUInt8 *dest,
          RwInt8 channels, RwInt8 channel, RwInt32 destSize)
{
    RwInt32 samples = srcSize >> 1;
    RwInt32 history1 = 0;
    RwInt32 history2 = 0;
    RwInt32 written = 0;
    RwReal error1 = 0;
    RwReal error2 = 0;
    RwInt32 offset;
    RwUInt8 block[16];
    RwInt16 input[28];
    RwInt32 i;
    RwInt32 amount;

    offset = 0;
    while (written + 16 <= destSize)
    {
        amount = samples - offset;
        if (amount > 28)
            amount = 28;
        for (i = 0; i < amount; i++)
            input[i] = src[offset + i * channels + channel];
        for (; i < 28; i++)
            input[i] = 0;
        sub_24B510(input, block, &history1, &history2, &error1, &error2);
        block[1] = 2;
        memcpy(dest, block, 16);
        offset += channels * 28;
        dest += 16;
        written += 16;
    }
    return written;
}


/* Debug reference: rwad.dll _RwaWaveConvVAGDecode at 0x100B13BB. */
// match: _sub_24BC50 @ 0x0024BC50
// sp-match: _sub_24BC50 @ 0x0015FD90
void
sub_24BC50(const RwUInt8 *src, RwInt16 *dest, RwUInt32 blocks)
{
    RwInt32 history2 = 0;
    RwInt32 history1 = 0;

    while (blocks)
    {
        RwInt32 filter;
        RwInt32 shift;
        RwInt32 k0;
        RwInt32 k1;
        RwInt32 s1;
        RwInt32 s2;
        RwInt32 i;
        RwInt32 prediction;
        RwInt32 sample;
        RwInt32 result;

        filter = (*src >> 4) & 15;
        shift = 12 - (*src & 15) + 16;
        src += 2;
        k0 = unk_42FCB0[filter][0];
        k1 = unk_42FCB0[filter][1];
        s1 = history1;
        s2 = history2;
        for (i = 0; i < 14; i++)
        {
            prediction = s1 * k0 + s2 * k1;
            sample = *src & 15;
            sample = (sample << 28) >> 28;
            result = (prediction + (sample << shift)) >> 16;
            *dest++ = (RwInt16)result;
            s2 = s1;
            s1 = result;

            prediction = s1 * k0 + s2 * k1;
            sample = (*src >> 4) & 15;
            sample = (sample << 28) >> 28;
            result = (prediction + (sample << shift)) >> 16;
            *dest++ = (RwInt16)result;
            s2 = s1;
            s1 = result;
            src++;
        }
        history1 = s1;
        history2 = s2;
        blocks--;
    }
}

/* Source shape corroborated by Studio's rwad.dll debug export
 * _rwaWaveConvXADPCMEncodeSample at 0x100B24BC: three locals, and
 * the final step shift inside each predictor expression. */
// match: _sub_24BD30 @ 0x0024BD30
// sp-match: _sub_24BD30 @ 0x0015FE70
RwUInt8
sub_24BD30(RwInt16 sample, RwInt32 *predicted, RwInt32 *index)
{
    RwInt32 step = word_42FD38[*index];
    RwInt32 diff = sample - *predicted;
    RwUInt8 code = 0;

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
    if (code & 8)
    {
        *predicted = sample + diff - (step >> 1);
    }
    else
    {
        *predicted = sample - diff + (step >> 1);
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

extern const RwaUUID unk_3ED5FC;
extern const RwaUUID unk_3ED65C;
extern void *sub_2421C0(RwUInt32 count, RwUInt32 size, RwUInt32 hint);
extern RwUInt32 sub_242A30(const RwaWaveFormat *format);
/* The stereo encoder: nothing (stereo is not encoded); /OPT:ICF folded it into
 * unit_246FD0's `return 0` (sub_247130), whose address it shares. */
static RwUInt32
sub_247130(const RwInt16 *src, RwUInt32 *dest, RwInt32 count)
{
    return 0;
}

// match: _sub_24BDE0 @ 0x0024BDE0
// sp-match: _sub_24BDE0 @ 0x0015FF20
void
sub_24BDE0(RwUInt32 code, RwInt32 *predicted, RwInt32 *index)
{
    RwUInt32    diff = ((code & 7) * 2 + 1) * word_42FD38[*index] >> 3;
    RwInt32 value;

    if (code & 8)
    {
        *predicted -= diff;
    }
    else
    {
        *predicted += diff;
    }
    value = *predicted;
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
    if (*index < 0)
    {
        *index = 0;
    }
    else if (*index > 88)
    {
        *index = 88;
    }
}

// match: _sub_24BE60 @ 0x0024BE60
// sp-match: _sub_24BE60 @ 0x0015FFA0
RwUInt32
sub_24BE60(const RwaWaveFormat *from, const RwUInt8 *src, RwUInt32 srcSize, RwaWaveFormat *to,
           RwUInt8 *dest, RwUInt32 *used)
{
    RwUInt32    length = from->length;
    RwUInt32    spare;
    RwUInt32    total;
    RwInt16     history[2];

    if (!used)
    {
        used = &spare;
    }
    *used = srcSize;
    total = from->noChannels * length;
    if (dest)
    {
        history[0] = 0;
        history[1] = 0;
        memset(dest + srcSize, 0, length);
        if (!sub_24A880(to, history, length - srcSize, from))
        {
            return 0;
        }
        sub_24B430(src + srcSize, length - srcSize, dest + srcSize);
    }

    return total;
}

// match: _sub_24BEF0 @ 0x0024BEF0
// sp-match: _sub_24BEF0 @ 0x00160030
RwUInt32
sub_24BEF0(const RwaWaveFormat *from, const RwUInt8 *src, RwUInt32 srcSize,
          RwaWaveFormat *to, RwUInt8 *dest, RwUInt32 *used)
{
    RwUInt32 total;
    RwUInt32 spare;
    RwUInt32 perChannel;
    RwUInt32 size;
    RwUInt32 encodedChannel;
    RwUInt8 *output;
    RwUInt8 *buffer;
    const RwUInt8 *input;
    RwUInt32 encoded;
    RwUInt32 c;

    if (!used)
        used = &spare;
    if (!RwaUUIDCompare(from->dataType, &unk_3ED5CC) &&
        !RwaUUIDCompare(to->dataType, &unk_3ED5EC))
    {
        perChannel = from->length / from->noChannels;
        encodedChannel = ((perChannel / 2 + 13) / 14) * 8;
        *used = ((srcSize / 2 + 13) / 14) * 8;
        total = encodedChannel * from->noChannels;
        size = total;
        if (dest)
        {
            buffer = NULL;
            if (to->noChannels > 1)
            {
                buffer = sub_2421C0(1, from->length, rwaMEMHINTDUR_FUNCTION | rwaID_806);
                if (!buffer)
                    return 0;
                perChannel &= ~1;
                for (c = 0; c < from->noChannels; c++)
                {
                    RwUInt32 left;
                    input = src + c * 2;
                    output = buffer + perChannel * c;
                    left = perChannel;
                    while (left)
                    {
                        *(RwInt16 *)output = *(const RwInt16 *)input;
                        input += from->noChannels * 2;
                        output += 2;
                        left -= 2;
                    }
                }
            }
            else
                buffer = (RwUInt8 *)src;
            for (c = 0; c < from->noChannels; c++)
            {
                output = dest + encodedChannel * c;
                input = buffer + srcSize + perChannel * c;
                memset(output, 0, encodedChannel);
                if (!sub_24A880(to, (const RwInt16 *)input, perChannel - srcSize, from))
                    return 0;
                encoded = sub_24AB90((const RwInt16 *)input, perChannel - srcSize,
                                    output, 1, 0, encodedChannel - *used);
            }
            if (to->noChannels > 1)
            {
                for (c = 0; c < to->noChannels; c++)
                {
                    RwUInt32 left;
                    input = dest + encodedChannel * c;
                    output = buffer + c * 8;
                    left = encodedChannel;
                    while (left)
                    {
                        memcpy(output, input, 8);
                        input += 8;
                        output += to->noChannels * 8;
                        left -= 8;
                    }
                }
                memcpy(dest, buffer, encodedChannel * to->noChannels);
                sub_2421B0(buffer);
            }
        }
    }
    else
    {
        RwUInt32 samples;
        const RwUInt32 *header;
        *used = (srcSize / 8) * 28;
        if (!from->extra || from->extraSize != 0x60)
            samples = ((from->length / 8) * 28) / 2;
        else
        {
            header = from->extra;
            samples = header[0];
            samples = rwaSWAP32(samples);
        }
        total = samples * 2;
        if (dest)
        {
            if (!from->extra || from->extraSize != 0x60)
                return 0;
            dest += *used;
            src += srcSize;
            memset(dest, 0, total);
            sub_24B260(from, src, (RwInt16 *)dest);
        }
    }
    return total;
}
#undef RwaDspSwap16Macro
#undef RwaDspSwap32Macro

// match: _sub_24C230 @ 0x0024C230
// sp-match: _sub_24C230 @ 0x00160370
RwUInt32
sub_24C230(const RwaWaveFormat *from, const RwUInt8 *src, RwUInt32 srcSize,
          const RwaWaveFormat *to, RwUInt8 *dest, RwUInt32 *used)
{
    RwUInt32 size;
    RwUInt32 total;
    RwUInt32 spare;
    RwUInt32 perChannel;
    RwUInt32 encodedChannel;
    RwUInt8 *output;
    RwUInt8 *buffer;
    const RwUInt8 *input;
    RwUInt32 encoded;
    RwUInt32 c;

    if (!used)
        used = &spare;
    if (!RwaUUIDCompare(from->dataType, &unk_3ED5CC) &&
        !RwaUUIDCompare(to->dataType, &unk_3ED5BC))
    {
        perChannel = from->length / from->noChannels;
        encodedChannel = (perChannel * 2) / 7;
        encodedChannel = (encodedChannel + 15) & ~15;
        *used = (srcSize * 2) / 7;
        *used = (*used + 15) & ~15;
        size = encodedChannel * from->noChannels;
        total = size;
        size -= *used;
        if (dest)
        {
            buffer = NULL;
            if (to->noChannels > 1)
            {
                buffer = sub_2421C0(1, from->length, rwaMEMHINTDUR_FUNCTION | rwaID_806);
                if (!buffer)
                    return 0;
                perChannel &= ~1;
                for (c = 0; c < from->noChannels; c++)
                {
                    RwUInt32 left;
                    input = src + c * 2;
                    output = buffer + perChannel * c;
                    left = perChannel;
                    while (left)
                    {
                        *(RwInt16 *)output = *(const RwInt16 *)input;
                        input += from->noChannels * 2;
                        output += 2;
                        left -= 2;
                    }
                }
            }
            else
                buffer = (RwUInt8 *)src;
            for (c = 0; c < from->noChannels; c++)
            {
                output = dest + *used + encodedChannel * c;
                input = buffer + srcSize + perChannel * c;
                memset(output, 0, encodedChannel);
                encoded = sub_24BB00((const RwInt16 *)input, perChannel - srcSize,
                                    output, 1, 0, encodedChannel - *used);
            }
            if (to->noChannels > 1)
            {
                for (c = 0; c < to->noChannels; c++)
                {
                    RwUInt32 left;
                    input = dest + encodedChannel * c;
                    output = buffer + c * 16;
                    left = encodedChannel;
                    while (left)
                    {
                        memcpy(output, input, 16);
                        input += 16;
                        output += to->noChannels * 16;
                        left -= 16;
                    }
                }
                memcpy(dest, buffer, encodedChannel * to->noChannels);
                sub_2421B0(buffer);
            }
        }
    }
    else
    {
        *used = (srcSize * 7) / 2;
        total = (from->length * 7) / 2;
        size = total - *used;
        if (dest)
        {
            dest += *used;
            src += srcSize;
            memset(dest, 0, size);
            sub_24BC50(src, (RwInt16 *)dest, from->length / 16);
        }
    }
    return total;
}

// match: _sub_24C560 @ 0x0024C560
// sp-match: _sub_24C560 @ 0x001606A0
RwBool
sub_24C560(const RwUInt32 *src, RwInt16 *dest, RwUInt32 blocks)
{
    const RwUInt32 *in = src;
    RwInt16    *out = dest;

    while (blocks)
    {
        RwUInt32    header;
        RwInt32     predicted;
        RwInt32     index;
        RwInt32     j;

        blocks--;
        header = *in++;
        predicted = (RwInt16)header;
        index = (header >> 16) & 0x7F;
        if (index < 0 || index > 88)
        {
            return FALSE;
        }
        *out++ = (RwInt16)predicted;
        for (j = 0; j < 8; j++)
        {
            RwUInt32    data = *in++;
            RwInt32     k;

            for (k = 0; k < 7 + (j != 7); k++)
            {
                sub_24BDE0(data & 0xF, &predicted, &index);
                *out++ = (RwInt16)predicted;
                data >>= 4;
            }
        }
    }

    return TRUE;
}



// match: _sub_24C620 @ 0x0024C620
// sp-match: _sub_24C620 @ 0x00160760
RwUInt32
sub_24C620(const RwInt16 *src, RwUInt32 *dest, RwInt32 count)
{
    const RwInt16 *in;
    RwUInt32   *out;
    RwUInt32    blocks;
    RwUInt32    size;
    RwInt32     index;
    RwInt32     predicted;
    RwInt32     remaining;
    RwUInt32    b;

    blocks = (RwUInt32)(count + 63) / 64;
    size = blocks * 36;
    in = src;
    out = dest;
    remaining = count;
    index = 0;

    for (b = blocks; b; b--)
    {
        RwUInt32    data;
        RwInt32     n;

        predicted = *in;
        in++;
        remaining--;
        *out++ = (index << 16) | (RwUInt16)predicted;

        data = 0;
        for (n = 0; n < 64; n++)
        {
            RwInt32     sample;

            data >>= 4;
            if (remaining > 0 && n < 63)
            {
                sample = *in++;
                remaining--;
            }
            else
            {
                sample = 0;
            }
            data |= (RwUInt32)sub_24BD30(sample, &predicted, &index) << 28;
            if ((n & 7) == 7)
            {
                *out++ = data;
                data = 0;
            }
        }
    }

    return size;
}


/* IMA ADPCM decode, stereo: per block, each channel's header (first
 * sample and step index), then eight pairs of nibble words. */
// match: _sub_24C700 @ 0x0024C700
// sp-match: _sub_24C700 @ 0x00160840
RwBool
sub_24C700(const RwUInt32 *src, RwInt16 *dest, RwUInt32 blocks)
{
    const RwUInt32 *in = src;
    RwInt16    *out = dest;

    while (blocks)
    {
        RwUInt32    left;
        RwUInt32    right;
        RwInt32     predictedLeft;
        RwInt32     predictedRight;
        RwInt32     indexLeft;
        RwInt32     indexRight;
        RwInt32     j;

        blocks--;
        left = *in++;
        right = *in++;
        predictedLeft = (RwInt16)left;
        predictedRight = (RwInt16)right;
        indexLeft = (left >> 16) & 0x7F;
        indexRight = (right >> 16) & 0x7F;
        if (indexLeft < 0 || indexLeft > 88 || indexRight < 0 || indexRight > 88)
        {
            return FALSE;
        }
        *out++ = (RwInt16)predictedLeft;
        *out++ = (RwInt16)predictedRight;
        for (j = 0; j < 8; j++)
        {
            RwUInt32    dataLeft = *in++;
            RwUInt32    dataRight = *in++;
            RwInt32     k;

            for (k = 0; k < 7 + (j != 7); k++)
            {
                sub_24BDE0(dataLeft & 0xF, &predictedLeft, &indexLeft);
                sub_24BDE0(dataRight & 0xF, &predictedRight, &indexRight);
                *out++ = (RwInt16)predictedLeft;
                *out++ = (RwInt16)predictedRight;
                dataLeft >>= 4;
                dataRight >>= 4;
            }
        }
    }

    return TRUE;
}

/* The encoders by channel count (one channel at a time: stereo is not
 * encoded). */
// match: _sub_24C840 @ 0x0024C840
// sp-match: _sub_24C840 @ 0x00160980
static RwUInt32
sub_24C840(const RwInt16 *src, RwInt32 size, RwInt8 channels, void *unused, RwUInt32 *dest,
           RwUInt32 destSize)
{
    RwInt32     count = (size >> 1) / channels;
    RwUInt32    encoded = 0;

    if (channels == 1)
    {
        encoded = sub_24C620(src, dest, count);
    }
    else if (channels == 2)
    {
        encoded = sub_247130(src, dest, count);
    }

    return encoded;
}

/* The decoders by channel count. */
// match: _sub_24C880 @ 0x0024C880
// sp-match: _sub_24C880 @ 0x001609C0
static void
sub_24C880(const RwaWaveFormat *format, const RwUInt32 *src, RwInt16 *dest)
{
    RwUInt8     channels = format->noChannels;
    RwUInt32    blocks = format->length / (channels * 36);

    if (channels == 1)
    {
        sub_24C560(src, dest, blocks);
    }
    else if (channels == 2)
    {
        sub_24C700(src, dest, blocks);
    }
}

/* IMA ADPCM conversion: 16-bit PCM encoded channel by channel (split from
 * and merged back into the interleaved data through a buffer), or
 * decoded. */
// match: _sub_24C8C0 @ 0x0024C8C0
// sp-match: _sub_24C8C0 @ 0x00160A00
RwUInt32
sub_24C8C0(const RwaWaveFormat *from, const RwUInt8 *src, RwUInt32 srcSize, const RwaWaveFormat *to,
           RwUInt8 *dest, RwUInt32 *used)
{
    RwUInt32    result = 0;
    RwUInt32    spare;
    RwUInt32    perChannel;
    RwUInt32    blockBytes;
    RwUInt8    *buffer;
    RwUInt32    c;

    if (!used)
    {
        used = &spare;
    }

    if (!RwaUUIDCompare(from->dataType, &unk_3ED5CC)
        && (!RwaUUIDCompare(to->dataType, &unk_3ED5FC) || !RwaUUIDCompare(to->dataType, &unk_3ED65C)))
    {
        perChannel = from->length / from->noChannels;
        *used = ((srcSize >> 1) + 63) / 64 * 36;
        blockBytes = ((perChannel >> 1) + 63) / 64 * 36;
        result = from->noChannels * blockBytes - *used;
        if (!dest)
        {
            goto done;
        }

        if (to->noChannels > 1)
        {
            buffer = (RwUInt8 *)sub_2421C0(1, from->length, rwaMEMHINTDUR_FUNCTION | rwaID_806);
            if (!buffer)
            {
                return 0;
            }
            perChannel &= ~1;
            for (c = 0; c < from->noChannels; c++)
            {
                const RwUInt8 *in = src + c * 2;
                RwUInt8 *out = buffer + c * perChannel;
                RwUInt32    n;

                for (n = perChannel; n; n -= 2)
                {
                    *(RwInt16 *)out = *(const RwInt16 *)in;
                    out += 2;
                    in += from->noChannels * 2;
                }
            }
        }
        else
        {
            buffer = (RwUInt8 *)src;
        }

        for (c = 0; c < from->noChannels; c++)
        {
            RwUInt8    *out = dest + *used + c * blockBytes;

            memset(out, 0, blockBytes);
            sub_24C840((const RwInt16 *)(buffer + srcSize + c * perChannel), perChannel - srcSize, 1, NULL,
                       (RwUInt32 *)out, blockBytes - *used);
        }

        if (to->noChannels > 1)
        {
            RwUInt32    align = sub_242A30(to);

            for (c = 0; c < to->noChannels; c++)
            {
                const RwUInt8 *in = dest + c * blockBytes;
                RwUInt8 *out = buffer + c * align;
                RwUInt32    n;

                for (n = blockBytes; n; n -= align)
                {
                    memcpy(out, in, align);
                    in += align;
                    out += to->noChannels * align;
                }
            }
            memcpy(dest, buffer, to->noChannels * blockBytes);
            sub_2421B0(buffer);
        }

        goto done;
    }

    if (from->noChannels == 1)
    {
        *used = srcSize / 36 * 128;
        result = from->length / 36 * 128;
    }
    else if (from->noChannels == 2)
    {
        *used = srcSize / 72 * 256;
        result = from->length / 72 * 256;
    }
    result -= *used;
    if (dest)
    {
        dest += *used;
        memset(dest, 0, result);
        sub_24C880(from, (const RwUInt32 *)(src + srcSize), (RwInt16 *)dest);
    }

done:
    return result;
}
