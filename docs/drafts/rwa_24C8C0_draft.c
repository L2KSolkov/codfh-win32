/* PARKED 2026-10-01: recovered interrupted draft of sub_24C8C0.
 * Append to src/rwa/unit_249490.c after sub_24C700; uses rwa.h/rwaint.h.
 * Additional externs: unk_3ED5FC, unk_3ED65C (RwaUUID),
 * sub_2421C0(RwUInt32,RwUInt32,RwUInt32) returning void *,
 * sub_242A30(const RwaWaveFormat *) returning RwUInt32.
 * VC7.0 /O2 /Ob1: first difference at the result initialization:
 * compiled xor ebp,ebp versus image store to [esp+0x10].
 * Register allocation, slot allocation, and loop scheduling differ throughout.
 * Existing interrupted form only recompiled/revalidated this session; no new
 * variants tried for the converter. Three block helpers match independently.
 * Static dispatchers sub_24C840/sub_24C880 match only with this caller present;
 * removing the caller eliminates them, and external linkage changes their
 * register calling conventions. Keep both parked with their caller.
 */
extern const RwaUUID unk_3ED5FC;
extern const RwaUUID unk_3ED65C;
extern void *sub_2421C0(RwUInt32 count, RwUInt32 size, RwUInt32 hint);
extern RwUInt32 sub_242A30(const RwaWaveFormat *format);
/* The stereo encoder: an empty function the linker folded into sub_247130. */
extern RwUInt32 sub_247130(const RwInt16 *src, RwUInt32 *dest, RwInt32 count);

/* The encoders by channel count (one channel at a time: stereo is not
 * encoded). */
// match: _sub_24C840 @ 0x0024C840
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
// Not yet matched: sub_24C8C0 (docs/questions.md).
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
            return result;
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
                RwUInt8    *out = buffer + c * perChannel;
                const RwUInt8 *in = src + c * 2;
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
                RwUInt8    *out = buffer + c * align;
                const RwUInt8 *in = dest + c * blockBytes;
                RwUInt32    n;

                for (n = blockBytes; n; n -= align)
                {
                    memcpy(out, in, align);
                    out += to->noChannels * align;
                    in += align;
                }
            }
            memcpy(dest, buffer, to->noChannels * blockBytes);
            sub_2421B0(buffer);
        }

        return result;
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
        memset(dest + *used, 0, result);
        sub_24C880(from, (const RwUInt32 *)(src + srcSize), (RwInt16 *)(dest + *used));
    }

    return result;
}
