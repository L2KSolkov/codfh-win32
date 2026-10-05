/*
 * codfh-match: RenderWare Audio's stream container (0x2452A0-0x246FD0):
 * the decoders, sources and output node a stream plays through, its play
 * state from theirs, and the conversion chains it builds between a track's
 * format and the output's. The database names its command set-up
 * `_rwaStreamContainerCommandInitialize`.
 */
#include "rwa.h"
#include "rwaint.h"

extern RwInt32 _InterlockedExchange(RwInt32 volatile *target, RwInt32 value);
extern RwInt32 _InterlockedIncrement(RwInt32 volatile *addend);
extern RwInt32 _InterlockedDecrement(RwInt32 volatile *addend);
#pragma intrinsic(_InterlockedExchange, _InterlockedIncrement, _InterlockedDecrement)

extern RwInt32 RwaUUIDCompare(const RwaUUID *uuid1, const RwaUUID *uuid2);
extern RwUInt32 RwaObjIntGetParamUInt32(rwaDecoder *obj, void *objInterface, RwInt32 type);
extern void sub_247290(rwaDecoder *obj, void *objInterface, RwInt32 type, ...);
extern void sub_247250(rwaDecoder *obj, void *objInterface, RwInt32 type, void *value);
extern RwBool sub_2417B0(volatile RwInt32 *target, RwInt32 value);
rwaContainerCommand *rwaStreamContainerCommandInitialize(rwaContainerCommand *command);
RwBool sub_246500(rwaStreamPlayer *player, rwaNodeSet *set);
RwUInt32 sub_246D70(rwaNodeSetEntry *entries, RwUInt32 maxEntries, const rwaStreamInfo *info);
RwBool sub_246240(rwaStreamPlayer *player, void *key, void *iface, struct rwaConversion *last,
                  rwaLink *list, RwaLLNode *convDefs);
extern void DSPHandle_Stop(rwaDecoder *obj, void *a, void *b);
extern void *sub_242170(RwUInt32 size, RwUInt32 hint);
extern void sub_2421B0(void *mem);
extern void *sub_243F40(const void *uuid);
extern RwBool sub_23DC60(rwaObjDef *root, void *iface, RwaLLNode *list);
extern rwaObjDef *sub_23DCA0(rwaObjDef *root, const void *uuid, rwaObjDef **parentOut);
extern void sub_2435D0(RwaLLNode *list);
extern const RwChar *sub_245210(const RwChar *name);
extern RwInt32 sub_240B90(const RwChar *string1, const RwChar *string2, RwUInt32 count);
extern RwBool sub_242CC0(const rwaWaveFormatDesc *desc, const RwaWaveFormat *format);
extern void sub_242C60(const rwaWaveFormatDesc *desc, RwaWaveFormat *format, RwBool init);
extern RwUInt32 sub_242E30(const RwaWaveFormat *format);
extern RwUInt32 sub_242A30(const RwaWaveFormat *format);
extern void sub_247380(rwaDecoder *node, RwUInt32 index, rwaDecoder *source, RwUInt32 d);
extern RwBool RwaObjDefGetDefaultCreationParams(rwaObjDef *def, void *params);
extern rwaDecoder *sub_23F4C0(rwaObjDef *def, rwaInstance *parent, RwUInt32 flags, void *params,
                              void *a, void *b);

extern const RwaUUID unk_3EDEBC;    /* the format converter's definition */
extern const RwUInt8 unk_3ED9C4[];  /* the decoder interface */
extern const RwUInt8 unk_3ED964[];  /* the track splitter's key */
extern const RwUInt8 unk_3EDEFC[];  /* the track decoder interface */
extern const RwUInt8 unk_3EDECC[];  /* the converter interface */
extern const RwChar aA_1[];         /* the default decoder */

/* A decoder's completion: one more playing when it plays, one fewer pending. */
// match: _sub_2452A0 @ 0x002452A0
void
sub_2452A0(rwaDecoder *node, rwaStreamPlayer *player)
{
    if (RwaObjIntGetParamUInt32(node, node->unk28, 0) == 1)
    {
        _InterlockedIncrement(&player->numPlaying);
    }
    _InterlockedDecrement(&player->numPending);
}

/* Walks each node chain up to the output node or a format converter, calling
 * func on the nodes before it; returns the last chain's stop node (the walk
 * stops after the first chain without a func). */
// match: _sub_2452D0 @ 0x002452D0
rwaDecoder *
sub_2452D0(rwaStreamPlayer *player, rwaContainerNodeFunc func, void *data)
{
    rwaLink    *link;
    rwaDecoder *found;

    found = NULL;
    link = player->nodes.next;
    while (link != &player->nodes)
    {
            rwaDecoder *node = rwaDecoderFromLink(link);

            link = link->next;
            do
            {
                rwaDecoder *next = node->next;
                rwaObjDef  *def = node->inst.def;

                if (player->decoder == node
                    || !RwaUUIDCompare(def->uniqueID.uuid, &unk_3EDEBC))
                {
                    found = node;
                    break;
                }
                if (func)
                {
                    func(node, data);
                }
                node = next;
            }
            while (node);
        if (!func)
        {
            break;
        }
    }

    return found;
}

/* Calls func on node and the nodes chained after it. */
// match: _sub_245350 @ 0x00245350
void
sub_245350(rwaDecoder *node, rwaContainerNodeFunc func, void *data)
{
    do
    {
        rwaDecoder *next = node->next;

        func(node, data);
        node = next;
    }
    while (node);
}

/* Calls func on each source. */
// match: _sub_245380 @ 0x00245380
void
sub_245380(rwaStreamPlayer *player, rwaContainerNodeFunc func, void *data)
{
    rwaLink    *link = player->sources.next;

    while (link != &player->sources)
    {
        rwaDecoder *node = rwaDecoderFromLink(link);

        link = link->next;
        func(node, data);
    }
}

// match: _sub_2453C0 @ 0x002453C0
static void
sub_2453C0(rwaDecoder *node, rwaStreamPlayer *player)
{
    node->link.prev->next = node->link.next;
    node->link.next->prev = node->link.prev;
    DSPHandle_Stop(node, player->unk54, player->unk58);
}

/* Unlinks and stops every node. */
// match: _sub_2453F0 @ 0x002453F0
static void
sub_2453F0(rwaStreamPlayer *player)
{
    rwaDecoder *node;

    node = sub_2452D0(player, (rwaContainerNodeFunc)sub_2453C0, player);
    if (node)
    {
        sub_245350(node, (rwaContainerNodeFunc)sub_2453C0, player);
    }
    sub_245380(player, (rwaContainerNodeFunc)sub_2453C0, player);
}

/* The decoders' combined state. */
// match: _sub_245430 @ 0x00245430
static RwInt32
sub_245430(rwaStreamPlayer *player)
{
    RwInt32     result;
    rwaLink    *link;

    switch (player->state)
    {
    case 2:
    case 3:
    case 4:
        result = 2;
        break;
    case 5:
        link = player->nodes.next;
        switch (player->mode)
        {
        case 1:
            result = 3;
            for (; link != &player->nodes; link = link->next)
            {
                rwaDecoder *node = rwaDecoderFromLink(link);

                if (RwaObjIntGetParamUInt32(node, node->unk28, 0) != 3)
                {
                    result = 8;
                    goto done;
                }
            }
            break;
        case 2:
            {
                RwBool      allStopped = TRUE;

                result = 6;
                for (; link != &player->nodes; link = link->next)
                {
                    rwaDecoder *node = rwaDecoderFromLink(link);
                    RwUInt32    state = RwaObjIntGetParamUInt32(node, node->unk28, 0);

                    if (state == 7)
                    {
                        result = 7;
                        goto done;
                    }
                    if (state != 3)
                    {
                        allStopped = FALSE;
                    }
                }
                if (allStopped == TRUE)
                {
                    result = 3;
                }
            }
            break;
        case 3:
            result = 5;
            for (; link != &player->nodes; link = link->next)
            {
                rwaDecoder *node = rwaDecoderFromLink(link);

                if (RwaObjIntGetParamUInt32(node, node->unk28, 0) != 5)
                {
                    result = 4;
                    goto done;
                }
            }
            break;
        default:
            result = 0;
            break;
        }
        break;
    case 6:
        result = 0;
        break;
    default:
        result = 0;
        break;
    }

done:
    return result;
}

/* The output node's state. */
// match: _sub_245560 @ 0x00245560
static RwInt32
sub_245560(rwaStreamPlayer *player)
{
    RwInt32     result;

    switch (player->state)
    {
    case 3:
    case 4:
    case 5:
        result = RwaObjIntGetParamUInt32(player->decoder, player->decoder->objInterface, 3);
        break;
    case 2:
        result = 0;
        break;
    case 6:
        result = 0;
        break;
    default:
        result = 0;
        break;
    }

    return result;
}

/* The container's state from its decoders' and output's. */
// match: _sub_2455A0 @ 0x002455A0
static RwInt32
sub_2455A0(rwaStreamPlayer *player, void *unused)
{
    RwInt32     result;
    RwInt32     decoders;

    switch (player->state)
    {
    case 6:
        result = 9;
        break;
    case 2:
    case 3:
    case 4:
        result = 2;
        break;
    case 5:
        decoders = sub_245430(player);
        result = sub_245560(player);
        switch (player->mode)
        {
        case 1:
            if (result == 3 && decoders == 3)
            {
                result = 3;
            }
            else
            {
                result = 8;
            }
            break;
        case 2:
            result = decoders;
            break;
        case 3:
            if ((result == 5 || result == 3) && decoders == 5)
            {
                result = decoders;
            }
            else
            {
                result = 4;
            }
            break;
        default:
            result = 0;
            break;
        }
        break;
    default:
        result = 0;
        break;
    }

    return result;
}

// match: _sub_245630 @ 0x00245630
void
sub_245630(rwaStreamPlayer *player, void *unused, RwInt32 *states)
{
    states[0] = sub_2455A0(player, unused);
    states[1] = sub_245560(player);
    states[2] = sub_245430(player);
}

// match: _sub_245670 @ 0x00245670
void
sub_245670(rwaDecoder *node, RwInt32 value)
{
    sub_247290(node, node->unk28, 2, value);
}

/* The index-th node, walked from the nearer end. */
// match: _sub_245690 @ 0x00245690
static rwaDecoder *
sub_245690(rwaStreamPlayer *player, const rwaNodeSet *set, RwUInt32 index)
{
    rwaLink    *link;

    if (index < set->numNodes >> 1)
    {
        for (link = player->nodes.next; index; index--)
        {
            link = link->next;
        }
    }
    else
    {
        RwUInt32    n;

        link = player->nodes.prev;
        for (n = set->numNodes - 1; n != index; n--)
        {
            link = link->prev;
        }
    }

    return rwaDecoderFromLink(link);
}

// match: _sub_2456D0 @ 0x002456D0
static void
sub_2456D0(rwaDecoder *node, RwInt32 value)
{
    sub_247290(node, node->unk28, 0, value);
}

// match: _sub_2456F0 @ 0x002456F0
static void
sub_2456F0(rwaStreamPlayer *player, const rwaNodeSet *set, RwInt32 type)
{
    rwaDecoder *node;

    if (type == 2)
    {
        _InterlockedExchange(&player->numBusy, set->numNodes);
    }
    node = sub_2452D0(player, (rwaContainerNodeFunc)sub_2456D0, (void *)type);
    sub_245350(node, (rwaContainerNodeFunc)sub_2456D0, (void *)type);
}

// match: _sub_245720 @ 0x00245720
static void
sub_245720(rwaStreamPlayer *player, rwaContainerCommand *command)
{
    player->unk30 = command->unk14;
    sub_247290(player->decoder, player->decoder->objInterface, 1, command->unk14);
}

/* Sets the playback rate: each node plays its track at the rate's share of
 * the track's sample rate. */
// match: _sub_245740 @ 0x00245740
static void
sub_245740(rwaContainerCommand *command, rwaStreamPlayer *player, const rwaNodeSet *set)
{
    rwaStreamTrack *track;
    rwaLink    *link;

    player->unk34 = command->rate;
    track = player->info->tracks;
    for (link = player->nodes.next; link != &player->nodes; link = link->next)
    {
        RwReal      rate = (RwReal)(track++)->format->rate * player->unk34;
        rwaDecoder *node = rwaDecoderFromLink(link);

        sub_247290(node, node->objInterface, 0, (RwInt32)rate);
    }
}

/* Creates the source's decoder and makes it the output node: the decoder
 * for the file's extension (type 1) or the format (type 2), or the default
 * (type 3). */
// match: _sub_2457A0 @ 0x002457A0
static RwBool
sub_2457A0(const rwaContainerSource *source, rwaStreamPlayer *player)
{
    RwUInt32    i = 0;
    rwaObjDef  *found = NULL;
    RwaLLNode  *node;
    const RwChar *ext;
    rwaObjDef  *parent;
    RwaLLNode   list;
    rwaStreamNodeParams *params;
    rwaDecoder *decoder;

    switch (source->type)
    {
    case 1:
        list.prev = &list;
        list.next = &list;
        list.data = NULL;
        if (!sub_23DC60(NULL, sub_243F40(unk_3ED9C4), &list))
        {
            return FALSE;
        }
        ext = sub_245210(source->name);
        if (ext == source->name)
        {
            sub_2435D0(&list);
            return FALSE;
        }
        for (node = list.next; node != &list; node = node->next)
        {
            rwaObjDef  *def;
            rwaCodecInfo *codec;

            if (found)
            {
                break;
            }
            def = (rwaObjDef *)node->data;
            codec = (rwaCodecInfo *)def->unk54;
            for (; i < codec->numEntries; i++)
            {
                if (!sub_240B90(((const RwChar **)codec->entries)[i], ext, rwstrlen(((const RwChar **)codec->entries)[i])))
                {
                    found = def;
                    break;
                }
            }
            i = 0;
        }
        sub_2435D0(&list);
        break;
    case 2:
        if (!source->format)
        {
            return FALSE;
        }
        list.prev = &list;
        list.next = &list;
        list.data = NULL;
        if (!sub_23DC60(NULL, sub_243F40(unk_3ED9C4), &list))
        {
            return FALSE;
        }
        for (node = list.next; node != &list; node = node->next)
        {
            rwaObjDef  *def = (rwaObjDef *)node->data;
            rwaCodecInfo *codec = (rwaCodecInfo *)def->unk54;

            for (; i < codec->numFormats; i++)
            {
                if (sub_242CC0(codec->formats[i], source->format))
                {
                    found = def;
                    break;
                }
            }
            i = 0;
        }
        sub_2435D0(&list);
        break;
    case 3:
        found = sub_23DCA0(NULL, aA_1, &parent);
        break;
    default:
        return FALSE;
    }

    if (!found)
    {
        return FALSE;
    }

    params = (rwaStreamNodeParams *)sub_242170(found->paramsSize,
                                               rwaMEMHINTDUR_FUNCTION | rwaID_80E);
    if (!params)
    {
        return FALSE;
    }
    if (!RwaObjDefGetDefaultCreationParams(found, params))
    {
        sub_2421B0(params);
        return FALSE;
    }

    params->unk00 = 0;
    params->unk04 = 1;
    params->unk08 = 0;
    params->callback = &player->callback;
    params->source[4] = (RwUInt32)source->name;
    params->source[5] = source->type;
    params->source[3] = (RwUInt32)source->format;
    params->source[6] = source->unk0C;
    params->source[7] = source->unk10;
    params->source[9] = source->unk18;
    params->source[10] = source->unk14;
    player->unk10 = source->unk1C;
    if (source->unk20)
    {
        params->source[12] = source->unk1C;
    }
    else
    {
        params->source[12] = 0;
    }
    params->source[8] = 0;
    params->source[11] = 0;
    params->source[14] = 0;
    params->source[13] = 0;

    decoder = sub_23F4C0(found, NULL, 0, params, player->unk50, player->unk58);
    if (!decoder)
    {
        sub_2421B0(params);
        return FALSE;
    }

    decoder->link.next = player->sources.next;
    decoder->link.prev = &player->sources;
    player->sources.next->prev = &decoder->link;
    player->sources.next = &decoder->link;
    player->decoder = decoder;

    sub_2421B0(params);
    return TRUE;
}

/* The decoder definition among defs that reads format. */
// match: _sub_245A60 @ 0x00245A60
static rwaObjDef *
sub_245A60(const RwaWaveFormat *format, RwaLLNode *defs)
{
    RwaLLNode  *node;

    for (node = defs->next; node != defs; node = node->next)
    {
        rwaObjDef  *def = (rwaObjDef *)node->data;
        rwaCodecInfo *codec = (rwaCodecInfo *)def->unk54;
        RwUInt32    i;

        for (i = 0; i < codec->numEntries; i++)
        {
            const rwaWaveFormatDesc *desc = ((const rwaWaveFormatDesc **)codec->entries)[i];
            RwUInt32    descFlag = desc->flags & 1;
            RwUInt32    formatFlag = format->flags & 1;

            if (!RwaUUIDCompare(format->dataType, desc->dataType)
                && format->bitDepth == desc->bitDepth
                && descFlag == formatFlag
                && format->noChannels == desc->noChannels
                && format->sampleRate <= desc->maxRate
                && format->sampleRate >= desc->minRate)
            {
                return def;
            }
        }
    }

    return NULL;
}

/* The definition among defs with the smallest capacity of at least size. */
// match: _sub_245B20 @ 0x00245B20
static rwaObjDef *
sub_245B20(RwUInt32 size, RwaLLNode *defs)
{
    RwaLLNode  *node;
    rwaObjDef  *best = NULL;
    RwUInt32    bestSize = 0xFFFFFFFF;

    for (node = defs->next; node != defs; node = node->next)
    {
        rwaObjDef  *def = (rwaObjDef *)node->data;
        RwUInt32    capacity = ((rwaCodecInfo *)def->unk54)->numFormats;

        if (capacity >= size && size <= bestSize)
        {
            best = def;
            bestSize = capacity;
        }
    }

    return best;
}

/* Creates a conversion node from format from to format to for the track
 * index. */
// match: _sub_245B60 @ 0x00245B60
rwaDecoder *
sub_245B60(rwaObjDef *def, const RwaWaveFormat *from, const RwaWaveFormat *to, RwUInt32 index,
           rwaStreamPlayer *player)
{
    rwaConversionParams params;

    RwaObjDefGetDefaultCreationParams(def, &params);
    params.info = player->info;
    params.unk58 = player->unk10;
    params.unk54 = player->info->tracks[index].unk20;
    params.from = *from;
    params.to = *to;
    return sub_23F4C0(def, NULL, 4, &params, player->unk50, player->unk58);
}

/* Rounds each decoder's rate to the output's granularity. */
// match: _sub_245BF0 @ 0x00245BF0
static void
sub_245BF0(rwaStreamPlayer *player, const rwaNodeSet *set)
{
    rwaLink    *link = player->nodes.next;

    if (link != &player->nodes)
    {
        RwUInt32    offset = 0;

        do
        {
            rwaDecoder *node = rwaDecoderFromLink(link);

            if (((rwaCodecInfo *)node->inst.def->unk54)->formats)
            {
                RwUInt32    rate = ((rwaStreamTrack *)((RwUInt8 *)player->info->tracks + offset))
                                       ->format->rate;

                if (set->unk00 & 2)
                {
                    RwUInt32    n = player->unk44;

                    if (n < 32)
                    {
                        RwUInt32    bits = player->unk40;
                        RwUInt32    shift = 2;

                        while (rate == bits && bits)
                        {
                            bits >>= 1;
                            shift--;
                        }
                        n -= shift;
                        rate = (player->unk4C * ((rate << n) / player->unk4C)) >> n;
                    }
                }
                sub_247290(node, node->objInterface, 0, rate);
            }
            link = link->next;
            offset += sizeof(rwaStreamTrack);
        }
        while (link != &player->nodes);
    }
}

/* A decoder became idle: one fewer busy, and the container plays on when
 * none is. */
// match: _sub_245CA0 @ 0x00245CA0
void
sub_245CA0(rwaDecoder *node, rwaStreamPlayer *player)
{
    _InterlockedDecrement(&player->numBusy);
    if (!player->numBusy)
    {
        player->mode = 1;
    }
}

/* A new conversion step in list. */
// match: _sub_245CC0 @ 0x00245CC0
static rwaConversion *
sub_245CC0(rwaLink *list, const RwaWaveFormat *from, const RwaWaveFormat *to, rwaObjDef *def,
           void *key, RwUInt32 index, rwaConversion *next)
{
    rwaConversion *conversion = (rwaConversion *)sub_242170(sizeof(rwaConversion),
                                                            rwaMEMHINTDUR_EVENT | rwaID_80E);

    if (conversion)
    {
        conversion->link.next = list->next;
        conversion->link.prev = list;
        list->next->prev = &conversion->link;
        list->next = &conversion->link;
        if (from)
        {
            conversion->from = *from;
        }
        if (to)
        {
            conversion->to = *to;
        }
        conversion->def = def;
        conversion->key = key;
        conversion->index = index;
        conversion->next = next;
        conversion->node = NULL;
    }

    return conversion;
}

// match: _sub_245D30 @ 0x00245D30
static void
sub_245D30(rwaConversion *conversion)
{
    if (conversion->link.next)
    {
        conversion->link.prev->next = conversion->link.next;
        conversion->link.next->prev = conversion->link.prev;
    }
    sub_2421B0(conversion);
}

// match: _sub_245D50 @ 0x00245D50
static void
sub_245D50(rwaLink *list)
{
    while (list->next != list)
    {
        sub_245D30(rwaConversionFromLink(list->next));
    }
}

// match: _sub_245D70 @ 0x00245D70
static rwaConversion *
sub_245D70(rwaLink *list, void *key)
{
    rwaLink    *link;

    for (link = list->next; link != list; link = link->next)
    {
        rwaConversion *conversion = rwaConversionFromLink(link);

        if (conversion->key == key)
        {
            return conversion;
        }
    }

    return NULL;
}

// match: _sub_245D90 @ 0x00245D90
RwUInt32
sub_245D90(rwaStreamPlayer *player, const rwaNodeSet *set)
{
    rwaDecoder *node;

    if (player->state != 5)
    {
        return 0;
    }
    node = sub_245690(player, set, 0);
    return RwaObjIntGetParamUInt32(node, node->objInterface, 1);
}

/* Sets up a stream container. */
// match: _sub_245DC0 @ 0x00245DC0
rwaStreamPlayer *
sub_245DC0(rwaStreamPlayer *player, rwaNodeSet *set, rwaContainerCommand *command, RwUInt32 a4,
           RwUInt32 a5, void *a6, void *a7, void *a8)
{
    if (!sub_2417B0(&player->numPlaying, 0)
        || !sub_2417B0(&player->numPending, 0)
        || !sub_2417B0(&player->numBusy, 0))
    {
        return NULL;
    }

    set->unk00 = 0;
    set->numNodes = 0;
    set->numEntries = 0;
    rwaStreamContainerCommandInitialize(command);
    player->sources.prev = &player->sources;
    player->sources.next = &player->sources;
    player->nodes.prev = &player->nodes;
    player->nodes.next = &player->nodes;
    player->unk48 = a4;
    player->unk4C = a5;
    player->unk30 = 0;
    player->info = NULL;
    player->decoder = NULL;
    player->unk40 = 0;
    player->unk10 = 0;
    player->callback.func = (void (*)(rwaQueueItem *, rwaDecoder *))sub_2452A0;
    player->callback.data = (rwaDecoder *)player;
    player->mode = 1;
    player->unk34 = 1.0f;
    player->state = 6;
    player->unk44 = 32;
    player->unk50 = a6;
    player->unk54 = a7;
    player->unk58 = a8;

    return player;
}

// match: _sub_245E90 @ 0x00245E90
void
sub_245E90(rwaStreamPlayer *player)
{
    sub_2453F0(player);
}

// match: _sub_245EA0 @ 0x00245EA0
static void
sub_245EA0(rwaStreamPlayer *player, rwaContainerCommand *command, rwaNodeSet *set)
{
    if (command->settings->unk04 || player->mode != 1)
    {
        rwaDecoder *node = sub_2452D0(player, (rwaContainerNodeFunc)sub_245670,
                                      (void *)command->settings->unk04);

        sub_245350(node, (rwaContainerNodeFunc)sub_245670, (void *)command->settings->unk04);
    }
    sub_2456F0(player, set, player->mode);
    command->settings->unk04 = 0;
    sub_247250(player->decoder, player->decoder->objInterface, 0, command->settings);
}

// match: _sub_245F10 @ 0x00245F10
static void
sub_245F10(rwaStreamPlayer *player, rwaNodeSetEntry *entries, const rwaNodeSet *set)
{
    RwUInt32    i;

    for (i = 0; i < set->numEntries; i++)
    {
        if (entries[i].track & 0x80000000)
        {
            entries[i].track &= 0x7FFFFFFF;
            sub_247250(sub_245690(player, set, entries[i].track),
                       sub_245690(player, set, entries[i].track)->objInterface, 1, &entries[i].channel);
        }
    }
}

/* Builds a chain of converters from format from to format to for the track
 * index, from the converter definitions defs: a converter whose input reads
 * from and whose output is to, or one whose output another chain converts
 * on. The steps are added to list; *out is the first. */
// match: _sub_245F80 @ 0x00245F80
RwBool
sub_245F80(const RwaWaveFormat *from, const RwaWaveFormat *to, RwUInt32 index, void *key,
           RwaLLNode *defs, rwaLink *list, rwaStreamPlayer *player, rwaConversion **out)
{
    RwaLLNode  *node;

    for (node = defs->next; node != defs; node = node->next)
    {
        rwaObjDef  *def = (rwaObjDef *)node->data;
        rwaCodecInfo *codec = (rwaCodecInfo *)def->unk54;
        rwaLink    *link;
        RwUInt32    i;

        /* each converter once per track */
        for (link = list->next; link != list; link = link->next)
        {
            rwaConversion *step = rwaConversionFromLink(link);

            if (step->def == def && step->index == index)
            {
                goto next;
            }
        }

        if (!codec->entries)
        {
            rwaDecoder *converter = sub_245B60(def, from, to, index, player);

            if (converter)
            {
                DSPHandle_Stop(converter, player->unk54, player->unk58);
                return sub_245CC0(list, from, to, def, key, index, NULL) != NULL;
            }
        }
        else
        {
            for (i = 0; i < codec->numEntries; i++)
            {
                if (sub_242CC0(((const rwaWaveFormatDesc **)codec->entries[i])[0], from))
                {
                    rwaConversion *step;
                    rwaConversion *next;
                    RwaWaveFormat format;

                    if (sub_242CC0(((const rwaWaveFormatDesc **)codec->entries[i])[1], to))
                    {
                        step = sub_245CC0(list, from, to, def, key, index, NULL);
                        if (!step)
                        {
                            return FALSE;
                        }
                        if (out)
                        {
                            *out = step;
                        }
                        return TRUE;
                    }

                    rwaWaveFormatInit(&format);
                    format.sampleRate = from->sampleRate;
                    sub_242C60(((const rwaWaveFormatDesc **)codec->entries[i])[1], &format, TRUE);
                    if (sub_245F80(&format, to, index, key, defs, list, player, &next))
                    {
                        step = sub_245CC0(list, from, to, def, key, index, next);
                        if (!step)
                        {
                            for (link = list->next; link != list; )
                            {
                                rwaConversion *other =
                                    rwaConversionFromLink(link);

                                link = link->next;
                                if (index == other->index)
                                {
                                    sub_245D30(other);
                                }
                            }
                            return FALSE;
                        }
                        if (out)
                        {
                            *out = step;
                        }
                        return TRUE;
                    }
                }
            }
        }
    next:
        ;
    }

    return FALSE;
}

/* A decoder step for each track whose format a decoder of defs reads. */
// match: _sub_2461B0 @ 0x002461B0
RwBool
sub_2461B0(rwaStreamPlayer *player, void *key, rwaConversion *next, rwaLink *list, RwaLLNode *defs)
{
    RwUInt32    i;

    for (i = 0; i < player->info->noTracks; i++)
    {
        RwaWaveFormat *format = (RwaWaveFormat *)player->info->tracks[i].format;
        rwaObjDef  *def = sub_245A60(format, defs);

        if (def && !sub_245CC0(list, format, NULL, def, key, i, next))
        {
            sub_245D50(list);
            return FALSE;
        }
    }

    return TRUE;
}

/* Creates a step's node. */
// match: _sub_2464B0 @ 0x002464B0
static rwaDecoder *
sub_2464B0(rwaStreamPlayer *player, RwUInt32 value, rwaStreamNodeParams *params,
           rwaConversion *step)
{
    params->source[0] = value;
    params->unk0C = player->unk10;
    params->source[3] = (RwUInt32)player;
    params->source[2] = (RwUInt32)sub_245CA0;
    _InterlockedIncrement(&player->numPending);
    return sub_23F4C0(step->def, (rwaInstance *)player->unk48, 4, params,
                      player->unk50, player->unk58);
}

/* For each track without a step in list, a chain of converters from its
 * format through the smallest converter definitions of convDefs that lead
 * to a format the decoders of iface read; the chain's steps move to list. */
// match: _sub_246240 @ 0x00246240
RwBool
sub_246240(rwaStreamPlayer *player, void *key, void *iface, rwaConversion *last, rwaLink *list,
           RwaLLNode *convDefs)
{
    RwUInt32    size = 0;
    RwUInt32    i;
    RwBool      haveDefs = FALSE;
    RwUInt32    offset;
    RwaLLNode   defs;
    rwaLink     chain;
    RwaWaveFormat format;

    for (i = 0, offset = 0; i < player->info->noTracks; i++, offset += sizeof(rwaStreamTrack))
    {
        rwaLink    *link;
        RwaWaveFormat *from;
        RwBool      found;
        rwaObjDef  *def;

        for (link = list->next; link != list; link = link->next)
        {
            if ((rwaConversionFromLink(link))->index == i)
            {
                goto next;
            }
        }

        if (!iface)
        {
            return FALSE;
        }
        if (!haveDefs)
        {
            defs.prev = &defs;
            defs.next = &defs;
            defs.data = NULL;
            if (!sub_23DC60(NULL, iface, &defs))
            {
                return FALSE;
            }
            haveDefs = TRUE;
        }

        chain.next = &chain;
        chain.prev = &chain;
        from = (RwaWaveFormat *)((rwaStreamTrack *)((RwUInt8 *)player->info->tracks + offset))
                   ->format;
        found = FALSE;
        for (;;)
        {
            rwaCodecInfo *codec;
            RwUInt32    j;

            def = sub_245B20(size, convDefs);
            if (!def)
            {
                break;
            }
            codec = (rwaCodecInfo *)def->unk54;
            size = codec->numFormats + 1;
            for (j = 0; j < codec->numEntries; j++)
            {
                rwaWaveFormatInit(&format);
                format.sampleRate = from->sampleRate;
                sub_242C60((const rwaWaveFormatDesc *)codec->entries[j], &format, FALSE);
                if (sub_245F80(from, &format, i, iface, &defs, &chain, player, NULL))
                {
                    found = TRUE;
                    break;
                }
            }
            if (found)
            {
                break;
            }
        }
        if (!found)
        {
            sub_2435D0(&defs);
            return FALSE;
        }

        rwaConversionFromLink(chain.next)->next = last;
        if (!sub_245CC0(&chain, &format, NULL, def, key, i, rwaConversionFromLink(chain.prev)))
        {
            sub_2435D0(&defs);
            sub_245D50(&chain);
            return FALSE;
        }

        for (link = chain.next; link != &chain; )
        {
            rwaLink    *nextLink = link->next;
            rwaConversion *step = rwaConversionFromLink(link);

            link->prev->next = link->next;
            link->next->prev = link->prev;
            step->link.next = NULL;
            step->link.prev = NULL;
            step->link.next = list->next;
            step->link.prev = list;
            list->next->prev = &step->link;
            list->next = &step->link;
            link = nextLink;
        }
        size = 0;

    next:
        ;
    }

    return TRUE;
}

/* Builds the node graph: the output node (one track) or a converter node
 * splitting the tracks, a decoder or converter chain for each track, and
 * the nodes in track order. */
// match: _sub_246500 @ 0x00246500
RwBool
sub_246500(rwaStreamPlayer *player, rwaNodeSet *set)
{
    RwUInt32    maxRate = 0;
    rwaLink     list;
    rwaConversion *first;
    void       *iface;
    void       *convIface;
    RwaLLNode   defs;
    rwaStreamTrack *tracks;
    rwaLink    *link;
    RwUInt32    paramsSize;
    RwUInt32    minShift;
    RwUInt32    rate;
    rwaStreamNodeParams *params;
    rwaConversion *chain;
    rwaConversion *step;
    rwaConversion local;

    player->unk40 = 0;
    player->unk44 = 32;
    if (!player->info)
    {
        return FALSE;
    }

    set->numNodes = player->info->noTracks;
    list.prev = &list;
    list.next = &list;
    if (set->numNodes > 1)
    {
        first = sub_245CC0(&list, NULL, NULL, sub_23DCA0(NULL, &unk_3EDEBC, NULL),
                           sub_243F40(unk_3ED964), (RwUInt32)-1, NULL);
        if (!first)
        {
            return FALSE;
        }
        maxRate = 0;
    }
    else
    {
        local.next = NULL;
        local.key = sub_243F40(unk_3ED9C4);
        local.node = player->decoder;
        local.def = local.node->inst.def;
        local.index = (RwUInt32)-1;
        rwaWaveFormatInit(&local.from);
        rwaWaveFormatInit(&local.to);
        local.link.prev = NULL;
        local.link.next = NULL;
        first = &local;
    }

    iface = sub_243F40(unk_3EDEFC);
    convIface = sub_243F40(unk_3EDECC);
    defs.prev = &defs;
    defs.next = &defs;
    defs.data = NULL;
    if (!sub_23DC60(NULL, iface, &defs))
    {
        return FALSE;
    }
    if (!sub_2461B0(player, iface, first, &list, &defs))
    {
        sub_2435D0(&defs);
        return FALSE;
    }
    if (!sub_246240(player, iface, convIface, first, &list, &defs))
    {
        sub_245D50(&list);
        sub_2435D0(&defs);
        return FALSE;
    }
    sub_2435D0(&defs);

    /* the rate and granularity the decoders need, and the largest node
     * parameters */
    tracks = player->info->tracks;
    minShift = (RwUInt32)-1;
    rate = 0;
    paramsSize = 0;
    for (link = list.next; link != &list; link = link->next)
    {
        step = rwaConversionFromLink(link);
        if (step->key == iface)
        {
            RwUInt32    shift = (RwUInt32)((rwaCodecInfo *)step->def->unk54)->formats;

            if (!shift)
            {
                set->unk00 |= 1;
            }
            else
            {
                if (tracks[step->index].format->rate > maxRate)
                {
                    maxRate = tracks[step->index].format->rate;
                }
                if (shift < minShift)
                {
                    minShift = shift;
                }
            }
            if (tracks[step->index].format->rate > rate)
            {
                if (rate)
                {
                    set->unk00 |= 3;
                }
                rate = player->info->tracks[step->index].format->rate;
            }
        }
        if (step->def->paramsSize > paramsSize)
        {
            paramsSize = step->def->paramsSize;
        }
    }
    player->unk44 = minShift;
    player->unk40 = maxRate;

    params = (rwaStreamNodeParams *)sub_242170(paramsSize, rwaMEMHINTDUR_FUNCTION | rwaID_80E);
    if (!params)
    {
        sub_245D50(&list);
        return FALSE;
    }

    if (first != &local)
    {
        if (!RwaObjDefGetDefaultCreationParams(first->def, params))
        {
            goto fail;
        }
        _InterlockedIncrement(&player->numPending);
        params->unk08 = (RwUInt32)player->info;
        params->unk0C = player->unk10;
        params->callback = &player->callback;
        first->node = sub_23F4C0(first->def, NULL, 4, params, player->unk50, player->unk58);
        if (!first->node)
        {
            goto fail;
        }
        first->node->link.next = player->sources.next;
        first->node->link.prev = &player->sources;
        player->sources.next->prev = &first->node->link;
        player->sources.next = &first->node->link;
        sub_247380(player->decoder, 0, first->node, 0);
    }

    while ((chain = sub_245D70(&list, iface)) != NULL)
    {
        do
        {
            rwaConversion *last;

            /* the step before the first one with a node */
            step = chain;
            while (!step->node)
            {
                last = step;
                step = step->next;
                if (!step)
                {
                    goto create;
                }
            }
            step = last;

        create:
            if (!RwaObjDefGetDefaultCreationParams(step->def, params))
            {
                goto fail;
            }
            params->unk08 = (RwUInt32)player->info;
            params->callback = &player->callback;
            if (step->key == iface)
            {
                rwaStreamTrack *track = &player->info->tracks[step->index];
                rwaLink    *prev = NULL;
                rwaStreamFormat *format;
                RwUInt16    unk1A;
                RwUInt32    unk0C;

                if (step->next->key == convIface)
                {
                    unk0C = track->unk0C;
                    format = track->format;
                    unk1A = track->unk1A;
                    track->format = (rwaStreamFormat *)&step->from;
                    track->unk0C = sub_242E30(&step->from);
                    track->unk1A = (RwUInt16)sub_242A30((RwaWaveFormat *)track->format);
                }
                step->node = sub_2464B0(player, (RwUInt32)track, params, step);
                if (step->next->key == convIface)
                {
                    track->format = format;
                    track->unk1A = unk1A;
                    track->unk0C = unk0C;
                }
                if (!step->node)
                {
                    goto fail;
                }

                /* the nodes in track order */
                step->node->unk4C = step->index;
                for (link = player->nodes.next; link != &player->nodes; link = link->next)
                {
                    if (rwaDecoderFromLink(link)->unk4C > step->index)
                    {
                        break;
                    }
                    prev = link;
                }
                if (prev)
                {
                    step->node->link.next = prev->next;
                    step->node->link.prev = prev;
                    prev->next->prev = &step->node->link;
                    prev->next = &step->node->link;
                }
                else
                {
                    step->node->link.next = player->nodes.next;
                    step->node->link.prev = &player->nodes;
                    player->nodes.next->prev = &step->node->link;
                    player->nodes.next = &step->node->link;
                }
            }
            else
            {
                step->node = sub_245B60(step->def, &step->from, &step->to, step->index, player);
                if (!step->node)
                {
                    goto fail;
                }
                step->node->link.next = player->sources.next;
                step->node->link.prev = &player->sources;
                player->sources.next->prev = &step->node->link;
                player->sources.next = &step->node->link;
            }
            sub_247380(step->next->node, step->next == first ? step->index : 0, step->node, 0);
        }
        while (step != chain);

        /* the chain's steps are done with */
        while (chain != first)
        {
            step = chain;
            chain = chain->next;
            sub_245D30(step);
        }
    }

    for (link = player->nodes.next; link != &player->nodes; link = link->next)
    {
        rwaDecoderFromLink(link)->unk4C = 1;
    }
    sub_2421B0(params);
    sub_245D50(&list);
    return TRUE;

fail:
    sub_2421B0(params);
    sub_245D50(&list);
    return FALSE;
}

/* Advances the container's set-up: the source's decoder (state 2), the
 * node graph once it has opened (3), the node set once the nodes are ready
 * (4); state 6 when anything fails. */
// match: _sub_246AD0 @ 0x00246AD0
static void
sub_246AD0(rwaStreamPlayer *player, rwaNodeSet *set, rwaContainerCommand *command)
{
    RwBool      failed = FALSE;

    switch (player->state)
    {
    case 2:
        if (!command->source)
        {
            goto fail;
        }
        _InterlockedExchange(&player->numPlaying, 0);
        _InterlockedExchange(&player->numPending, 1);
        player->mode = 1;
        if (sub_2457A0(command->source, player))
        {
            player->state = 3;
            return;
        }
        failed = TRUE;
        break;
    case 3:
        if ((RwUInt32)player->numPlaying > 0)
        {
            failed = TRUE;
            break;
        }
        if ((RwUInt32)player->numPending > 0)
        {
            return;
        }
        player->info = (rwaStreamInfo *)RwaObjIntGetParamUInt32(player->decoder,
                                                               player->decoder->objInterface, 2);
        if (!sub_246500(player, set))
        {
            failed = TRUE;
            break;
        }
        player->state = 4;
        /* fall through */
    case 4:
        if ((RwUInt32)player->numPlaying > 0)
        {
            failed = TRUE;
            player->state = 6;
        }
        if ((RwUInt32)player->numPending <= 0)
        {
            set->numEntries = sub_246D70(command->entries, 0xC0, player->info);
            if (!set->numEntries)
            {
                failed = TRUE;
                break;
            }
            sub_245BF0(player, set);
            player->state = 5;
        }
        break;
    default:
        sub_2453F0(player);
        player->state = 6;
        return;
    }

    if (failed)
    {
        sub_2453F0(player);
fail:
        player->state = 6;
    }
}
// match: _sub_246BD0 @ 0x00246BD0
rwaStreamContainer *
sub_246BD0(rwaStreamContainer *container, RwUInt32 a2, RwUInt32 a3, void *a4, void *a5, void *a6)
{
    rwaStreamContainer *result = (rwaStreamContainer *)sub_245DC0(&container->player,
                                                                  &container->set,
                                                                  &container->command,
                                                                  a2, a3, a4, a5, a6);

    if (result)
    {
        result->states[1] = 0;
        result->states[2] = 0;
        result->states[0] = 0;
    }

    return result;
}

/* Applies the command's changes; TRUE once the container plays. */
// match: _sub_246C20 @ 0x00246C20
RwBool
sub_246C20(rwaStreamPlayer *player, rwaNodeSet *set, rwaContainerCommand *command)
{
    RwBool      ready = FALSE;

    if ((command->flags & 4) && !player->numPending)
    {
        sub_2453F0(player);
        player->state = 2;
        command->flags &= ~4;
    }
    if (player->state < 5)
    {
        sub_246AD0(player, set, command);
        if (player->state < 5)
        {
            return FALSE;
        }
        ready = TRUE;
    }
    if (player->state != 6)
    {
        if (command->flags & 8)
        {
            sub_245EA0(player, command, set);
            command->flags &= ~8;
        }
        if (command->flags & 0x20)
        {
            sub_245740(command, player, set);
            command->flags &= ~0x20;
        }
        if (command->flags & 0x10)
        {
            sub_245F10(player, command->entries, set);
            command->flags &= ~0x10;
        }
        if (command->flags & 0x40)
        {
            sub_245720(player, command);
            command->flags &= ~0x40;
        }
        if (command->flags & 0x80)
        {
            if (player->mode != command->mode)
            {
                sub_2456F0(player, set, command->mode);
                player->mode = command->mode;
            }
            command->flags &= ~0x80;
        }
    }

    return ready;
}

// match: _sub_246D20 @ 0x00246D20
RwBool
sub_246D20(rwaStreamContainer *container)
{
    RwBool      ready = sub_246C20(&container->player, &container->set, &container->command);

    sub_245630(&container->player, &container->set, container->states);
    return ready;
}

// match: _rwaStreamContainerCommandInitialize @ 0x00246D50
rwaContainerCommand *
rwaStreamContainerCommandInitialize(rwaContainerCommand *command)
{
    command->flags = 0;
    command->mode = 1;
    command->source = NULL;
    command->settings = NULL;
    command->rate = 1.0f;
    command->unk14 = 0;
    return command;
}

/* The node set's entries for the tracks' channels: four per channel (kinds
 * 0 to 3, value 1.0); the number of entries, or 0 when they do not fit. */
// match: _sub_246D70 @ 0x00246D70
RwUInt32
sub_246D70(rwaNodeSetEntry *entries, RwUInt32 maxEntries, const rwaStreamInfo *info)
{
    RwUInt32    numChannels = 0;
    RwUInt32    track;
    RwUInt32    n;

    for (track = 0; track < info->noTracks; track++)
    {
        numChannels += info->tracks[track].format->channels;
    }
    if (numChannels * 4 > maxEntries)
    {
        return 0;
    }

    n = 0;
    for (track = 0; track < info->noTracks; track++)
    {
        RwUInt32    channel;

        for (channel = 0; channel < info->tracks[track].format->channels; channel++)
        {
            entries[n * 4].channel = channel;
            entries[n * 4].track = track;
            entries[n * 4].kind = 0;
            entries[n * 4].value = 1.0f;
            entries[n * 4 + 1].channel = channel;
            entries[n * 4 + 1].track = track;
            entries[n * 4 + 1].kind = 1;
            entries[n * 4 + 1].value = 1.0f;
            entries[n * 4 + 2].channel = channel;
            entries[n * 4 + 2].track = track;
            entries[n * 4 + 2].kind = 2;
            entries[n * 4 + 2].value = 1.0f;
            entries[n * 4 + 3].channel = channel;
            entries[n * 4 + 3].track = track;
            entries[n * 4 + 3].kind = 3;
            entries[n * 4 + 3].value = 1.0f;
            n++;
        }
    }

    return n * 4;
}

// match: _sub_246E70 @ 0x00246E70
rwaContainerCommand *
sub_246E70(rwaContainerCommand *command, const rwaContainerSource *source)
{
    command->source = source;
    command->flags = (command->flags & ~8) | 4;
    command->settings = NULL;
    command->rate = 1.0f;
    command->mode = 1;
    command->unk14 = 0;
    return command;
}

// match: _sub_246EA0 @ 0x00246EA0
rwaContainerCommand *
sub_246EA0(rwaContainerCommand *command, rwaPlaySettings *settings)
{
    command->settings = settings;
    command->flags |= 8;
    return command;
}

// match: _sub_246EB0 @ 0x00246EB0
RwBool
sub_246EB0(rwaContainerCommand *command, RwReal rate, const rwaNodeSet *set)
{
    if (set->unk00 & 1)
    {
        return FALSE;
    }
    command->flags |= 0x20;
    command->rate = rate;
    return TRUE;
}

/* Sets value for the entries of the given track, channel and kind (-1:
 * any; kinds 0 to 3). */
// match: _sub_246ED0 @ 0x00246ED0
rwaContainerCommand *
sub_246ED0(rwaContainerCommand *command, const rwaNodeSet *set, RwInt32 track, RwInt32 channel,
           RwInt32 kind, RwReal value)
{
    RwInt32     trackEnd = set->numNodes;
    RwUInt32    i = 0;
    RwInt32     kindStart = 0;
    RwInt32     trackStart = 0;
    RwInt32     kindEnd = 4;

    if (track != -1)
    {
        trackStart = track;
        trackEnd = track + 1;
    }
    if (kind != -1)
    {
        kindStart = kind;
        kindEnd = kind + 1;
    }

    for (; i < set->numEntries; i++)
    {
        RwInt32     index = command->entries[i].track;

        if (index < 0)
        {
            index &= ~0x80000000;
        }
        if (index >= trackStart && index < trackEnd
            && (RwInt32)command->entries[i].kind >= kindStart
            && (RwInt32)command->entries[i].kind < kindEnd
            && ((RwInt32)command->entries[i].channel == channel || channel < 0))
        {
            command->entries[i].value = value;
            command->entries[i].track = index | 0x80000000;
        }
    }

    command->flags |= 0x10;
    return command;
}

// match: _sub_246F80 @ 0x00246F80
rwaContainerCommand *
sub_246F80(rwaContainerCommand *command, RwUInt32 value)
{
    command->unk14 = value;
    command->flags |= 0x40;
    return command;
}

// match: _sub_246F90 @ 0x00246F90
rwaContainerCommand *
sub_246F90(rwaContainerCommand *command, RwInt32 mode)
{
    command->mode = mode;
    command->flags |= 0x80;
    return command;
}

// match: _sub_246FB0 @ 0x00246FB0
void *
sub_246FB0(RwUInt32 size, RwUInt32 unused)
{
    return sub_242170(size, rwaMEMHINTDUR_EVENT | rwaID_80F);
}

// match: _sub_246FC0 @ 0x00246FC0
void
sub_246FC0(void *mem, RwUInt32 unused)
{
    sub_2421B0(mem);
}
