/*
 * codfh-match: RenderWare Audio's stream source object (0x240C50-0x2416D0;
 * named after the database's RwaStreamSourceInterfaceRegister and
 * _rwaStreamSourceCreationParamsInit): a stream node (+0x5C) that reads a
 * stream file's regions into a play queue, its execute and creation
 * callbacks, position requests and parameter handlers, and its definition's
 * set-up and registration.
 */
#include "rwa.h"
#include "rwaint.h"



extern rwaObjDef unk_506B70;        /* the stream source definition */
extern RwUInt8 unk_506BCC[];
extern RwUInt8 unk_506BE4[];
extern rwaObjDef *dword_516C60;
extern const RwUInt8 unk_3ED9C4[];

extern RwBool sub_249480(void);
extern RwBool sub_23DB90(rwaObjDef *def);
extern void sub_2470A0(rwaDecoder *obj);
extern RwInt32 sub_248520(rwaDecoderState *state);
extern void sub_248410(rwaDecoderState *state);
extern void RwaStreamNodeGetParams(rwaDecoder *obj, rwaStreamNodeParams *params);
extern void _rwaStreamSourceCreationParamsInit(rwaStreamSourceParams *params);
extern void sub_247160(rwaDecoder *obj, RwUInt32 a, RwUInt32 *value);
extern void sub_247E00(rwaDecoderState *state, void *a);
extern void sub_247340(rwaQueue *queue, rwaQueueItem *item);
extern void *sub_247C50(rwaDecoderState *state, rwaStreamRegion **region);
extern rwaQueueItem *sub_247300(rwaQueue *queue);
extern RwUInt32 sub_248360(rwaDecoderState *state, rwaStreamRegion *region, RwUInt32 a);
extern void sub_2481E0(rwaDecoderState *state);
extern void sub_247FE0(rwaDecoderState *state, RwUInt32 a, RwUInt32 bytes);
extern void sub_2483B0(rwaDecoderState *state, RwUInt32 value);
extern void sub_2483E0(rwaDecoderState *state, RwUInt32 value);
extern void sub_2471D0(rwaDecoder *obj, RwUInt32 a, rwaStreamConnect *connect);
extern RwInt32 sub_243B80(void *objInterface);
extern void sub_247500(rwaDecoderState *state);
extern void sub_247120(rwaDecoder *obj, void *a, void *b);
extern void RwaStreamNodeCreationComplete(rwaDecoder *obj);
extern rwaQueue *sub_2472E0(rwaQueue *queue, rwaQueueItem *items, RwUInt8 count);
extern RwBool sub_246FD0(rwaDecoder *obj, rwaInstance *parent, rwaStreamNodeParams *params,
                         void *a, void *b);
extern void sub_241230(rwaDecoderState *state, RwBool failed, rwaDecoder *obj);
extern RwBool sub_249160(rwaDecoderState *state, rwaStreamSourceParams *params);
extern void *sub_243F40(const void *uuid);
extern void *sub_243FF0(void *objInterface, rwaObjDef *def, RwUInt32 a, RwUInt32 b);
extern rwaObjDef *RwaObjDefAssignID(rwaObjDef *def, const void *uuid, const void *textID);
extern rwaObjDef *sub_23DFB0(void *parent, RwInt32 a, void *b, void *c, void *d, RwUInt32 hint);
extern RwBool _rwaObjDefSetupParams(rwaObjDef *def, void *sets, RwInt32 noSets, void *gets, RwInt32 noGets);
extern void *RwaStreamSourceInterfaceRegister(void);
extern rwaObjDef *sub_23D740(rwaObjDef *def, void *iface);

// Its data (PLAN M5): literals, constants and tables where the image has them.

// What its data definitions name.
rwaDecoder *sub_241110(rwaDecoder *obj, RwUInt32 param, void *value);
rwaDecoder *sub_241130(rwaDecoder *obj, RwUInt32 param, void *value);
rwaDecoder *sub_241150(rwaDecoder *obj, RwUInt32 param, void *value);
rwaDecoder *sub_241170(rwaDecoder *obj, RwUInt32 param, void *value);
rwaDecoder *sub_241190(rwaDecoder *obj, RwUInt32 param, void *value);
rwaDecoder *sub_2411B0(rwaDecoder *obj, RwUInt32 param, void *value);
rwaDecoder *sub_2411D0(rwaDecoder *obj, RwUInt32 param, void *value);
extern void sub_247140(void);
extern void sub_2471F0(void);
extern RwUInt8 unk_3ED4EC[];
extern RwUInt8 unk_3ED55C[];
extern RwUInt8 unk_3ED56C[];
extern RwUInt8 unk_3ED974[];
extern RwUInt8 unk_3ED984[];
extern RwUInt8 unk_3ED994[];
extern RwUInt8 unk_3ED9A4[];
extern RwUInt8 unk_3ED9B4[];
extern RwUInt8 unk_3ED9D4[];
extern RwUInt8 unk_3ED9E4[];
extern RwUInt8 unk_3ED9F4[];
extern RwUInt8 unk_3EDA04[];
extern RwUInt8 unk_3EDA14[];
// Its data definitions (PLAN M5), in the image's address order.
// 0x003ED29C
const RwaUUID unk_3ED29C = { 0xAEE9415B, 0x116E, 0x4574, { 0xBC, 0xCD, 0x23, 0xE7, 0x31, 0xE0, 0x5C, 0xC6 } };
// 0x0042E8A0
void *unk_42E8A0[30] =
{
    (void *)&unk_3ED9D4,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)sub_241110,
    (void *)&unk_3ED9F4,
    0,
    0,
    (void *)&unk_3ED55C,
    (void *)0x1,
    (void *)sub_241150,
    (void *)&unk_3ED974,
    0,
    0,
    (void *)&unk_3ED4EC,
    (void *)0x1,
    (void *)sub_247160,
    (void *)&unk_3ED984,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)sub_2411B0,
    (void *)&unk_3ED9B4,
    0,
    0,
    (void *)&unk_3ED55C,
    (void *)0x1,
    (void *)sub_2411D0,
};
// 0x0042E918
void *unk_42E918[32] =
{
    (void *)&unk_3ED9E4,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)sub_241130,
    (void *)&unk_3EDA04,
    0,
    0,
    (void *)&unk_3ED55C,
    (void *)0x1,
    (void *)sub_241170,
    (void *)&unk_3EDA14,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)sub_241190,
    (void *)&unk_3ED994,
    0,
    0,
    (void *)&unk_3ED4EC,
    (void *)0x1,
    (void *)sub_247140,
    (void *)&unk_3ED9A4,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)sub_2471F0,
    (void *)0x737772,
    (void *)&unk_42E918[30],
};
// 0x0042E998
void *unk_42E998[6] =
{
    (void *)0x3,
    (void *)&unk_42E918[31],
    (void *)0x1,
    0,
    0,
    0,
};
// 0x00506B70
rwaObjDef unk_506B70;
// 0x00506BCC
RwUInt8 unk_506BCC[24];
// 0x00506BE4
RwUInt8 unk_506BE4[8];
// End of its data definitions.

// match: _unk_3ED29C @ 0x003ED29C


// match: _unk_42E8A0 @ 0x0042E8A0


// match: _unk_42E918 @ 0x0042E918


// match: _unk_42E998 @ 0x0042E998

// match: _sub_240C50 @ 0x00240C50
// sp-match: _sub_240C50 @ 0x00154D90

RwBool
sub_240C50(void)
{
    if (!sub_249480())
    {
        return FALSE;
    }

    return sub_23DB90(&unk_506B70);
}

// match: _sub_240C70 @ 0x00240C70
// sp-match: _sub_240C70 @ 0x00154DB0
rwaDecoder *
sub_240C70(rwaDecoder *obj)
{
    rwaDecoderState *state = &obj->state;

    switch (obj->mode)
    {
        case 1:
            if (obj->status != 3)
            {
                sub_2470A0(obj);
            }

            return obj;

        case 2:
            if (obj->status != 6 && obj->status != 7)
            {
                sub_2470A0(obj);
            }

            if (state->flags & 0x10000)
            {
                obj->status = ((state->entries[state->entry].flags & 1) ||
                               (state->entries[state->entry].flags & 4)) ? 7 : 6;
            }
            else
            {
                obj->status = (state->unk154 == state->unk14C &&
                               state->regions[state->unk14C].flags == 1) ? 7 : 6;
            }

            /* fall through */

        case 3:
        {
            RwInt32     result = sub_248520(state);

            if (result == 3 || result == 4)
            {
                if (obj->status == 4)
                {
                    sub_2470A0(obj);
                }

                if (result == 4 && obj->mode == 2)
                {
                    obj->mode = 1;
                    sub_2470A0(obj);
                }
            }

            sub_248410(state);

            return obj;
        }
    }

    return obj;
}

// match: _sub_240D80 @ 0x00240D80
// sp-match: _sub_240D80 @ 0x00154EC0
rwaDecoder *
sub_240D80(rwaDecoder *obj, rwaStreamNodeParams *params)
{
    rwaStreamSourceParams   defaults;

    RwaStreamNodeGetParams(obj, params);
    params->unk00 = 0;
    _rwaStreamSourceCreationParamsInit(&defaults);

    params->source[0] = defaults.values[0];
    params->source[6] = defaults.values[6];
    params->source[7] = defaults.values[7];
    params->source[2] = defaults.values[2];
    params->source[4] = defaults.values[4];
    params->source[5] = defaults.values[5];
    params->source[3] = defaults.values[3];
    params->source[1] = defaults.values[1];
    params->source[14] = defaults.values[14];
    params->source[13] = defaults.values[13];
    params->source[8] = defaults.values[8];
    params->source[9] = defaults.values[9];
    params->source[11] = defaults.values[11];
    params->source[10] = defaults.values[10];

    return obj;
}

// match: _sub_240E20 @ 0x00240E20
// sp-match: _sub_240E20 @ 0x00154F60
void
sub_240E20(rwaQueueItem *item, rwaDecoder *obj)
{
    if (item->flags & 8)
    {
        RwUInt32    value;

        item->flags &= ~8;
        value = 1;
        sub_247160(obj, 0, &value);
    }

    sub_247E00(&obj->state, item->unk04);
    sub_247340(&obj->state.queue, item);
}

// match: _sub_240E70 @ 0x00240E70
// sp-match: _sub_240E70 @ 0x00154FB0
rwaQueueItem *
sub_240E70(rwaDecoder *obj)
{
    rwaDecoderState *state = &obj->state;
    rwaStreamRegion *region;
    void           *data;
    rwaQueueItem   *item;

    if (obj->state.queue.count != obj->state.queue.size)
    {
        data = sub_247C50(state, &region);
        if (data)
        {
            item = sub_247300(&obj->state.queue);
            item->unk04 = data;
            item->position->unit = 2;
            item->position->value = ((RwUInt32)region->marker - (RwUInt32)state->info->markers) /
                                    sizeof(rwaStreamMarker);
            item->position->pos = sub_248360(state, region, 0);

            if (!state->unkFC && !(state->flags & 0x4000))
            {
                item->flags |= 8;
            }

            return item;
        }
    }

    return NULL;
}

// match: _sub_240F10 @ 0x00240F10
// sp-match: _sub_240F10 @ 0x00155050
void
sub_240F10(rwaDecoder *obj, rwaStreamSeek *seek)
{
    rwaDecoderState    *state = &obj->state;
    rwaStreamTrack     *track;
    RwUInt32            samples;
    RwUInt32            bytes;

    if (seek->flush)
    {
        sub_2481E0(state);
    }

    track = state->info->tracks;

    if (seek->position->unit == 1)
    {
        samples = (RwUInt32)((RwReal)track->format->rate * *(RwReal *)&seek->position->pos);
        samples = (samples + track->unk0C - 1) & ~(track->unk0C - 1);
    }
    else
    {
        samples = seek->position->pos;
    }

    bytes = samples / track->unk0C * track->format->channels * track->unk1A;

    switch (seek->position->type)
    {
        case 3:
            state->marker = &state->info->markers[seek->position->value];
            break;

        case 2:
            sub_2483B0(state, seek->position->value);
            break;

        case 1:
            sub_2483E0(state, seek->position->value);
            break;
    }

    sub_247FE0(state, 0, bytes);
}

// match: _sub_240FF0 @ 0x00240FF0
// sp-match: _sub_240FF0 @ 0x00155130
void
sub_240FF0(rwaDecoder *obj, rwaStreamPosition *out)
{
    rwaDecoderState *state = &obj->state;
    rwaStreamRegion *region = &state->regions[state->region];

    switch (out->type)
    {
        case 1:
            out->value = (RwUInt32)region->marker->name;
            break;

        case 2:
            out->value = (RwUInt32)region->marker->uuid;
            break;

        default:
            out->type = 3;
            out->value = ((RwUInt32)region->marker - (RwUInt32)state->info->markers) /
                         sizeof(rwaStreamMarker);
            break;
    }

    out->unit = 2;
    out->pos = sub_248360(state, region, 0);
}

// match: _sub_241060 @ 0x00241060
// sp-match: _sub_241060 @ 0x001551A0
void
sub_241060(rwaDecoder *obj, RwBool enable)
{
    if (enable)
    {
        obj->state.flags |= 0x4000;
    }
    else
    {
        obj->state.flags &= ~0x4000;
    }
}

// match: _sub_2410A0 @ 0x002410A0
// sp-match: _sub_2410A0 @ 0x001551E0
RwUInt32
sub_2410A0(rwaDecoder *obj)
{
    return obj->state.flags & 0x4000;
}

// match: _sub_2410B0 @ 0x002410B0
// sp-match: _sub_2410B0 @ 0x001551F0
rwaStreamInfo *
sub_2410B0(rwaDecoder *obj)
{
    return obj->state.info;
}

// match: _sub_2410C0 @ 0x002410C0
// sp-match: _sub_2410C0 @ 0x00155200
void
sub_2410C0(rwaDecoder *obj, rwaStreamConnect *connect)
{
    sub_2471D0(obj, 0, connect);
    connect->reader->read = sub_240E70;
    connect->reader->data = obj;
}

// match: _sub_2410F0 @ 0x002410F0
// sp-match: _sub_2410F0 @ 0x00155230
void
sub_2410F0(rwaDecoder *obj, RwBool flush)
{
    if (flush)
    {
        sub_2481E0(&obj->state);
    }
}

// match: _sub_241110 @ 0x00241110
// sp-match: _sub_241110 @ 0x00155250
rwaDecoder *
sub_241110(rwaDecoder *obj, RwUInt32 param, void *value)
{
    sub_240F10(obj, (rwaStreamSeek *)value);

    return obj;
}

// match: _sub_241130 @ 0x00241130
// sp-match: _sub_241130 @ 0x00155270
rwaDecoder *
sub_241130(rwaDecoder *obj, RwUInt32 param, void *value)
{
    sub_240FF0(obj, (rwaStreamPosition *)value);

    return obj;
}

// match: _sub_241150 @ 0x00241150
// sp-match: _sub_241150 @ 0x00155290
rwaDecoder *
sub_241150(rwaDecoder *obj, RwUInt32 param, void *value)
{
    sub_241060(obj, *(RwBool *)value);

    return obj;
}

// match: _sub_241170 @ 0x00241170
// sp-match: _sub_241170 @ 0x001552B0
rwaDecoder *
sub_241170(rwaDecoder *obj, RwUInt32 param, void *value)
{
    *(RwUInt32 *)value = sub_2410A0(obj);

    return obj;
}

// match: _sub_241190 @ 0x00241190
// sp-match: _sub_241190 @ 0x001552D0
rwaDecoder *
sub_241190(rwaDecoder *obj, RwUInt32 param, void *value)
{
    *(rwaStreamInfo **)value = sub_2410B0(obj);

    return obj;
}

// match: _sub_2411B0 @ 0x002411B0
// sp-match: _sub_2411B0 @ 0x001552F0
rwaDecoder *
sub_2411B0(rwaDecoder *obj, RwUInt32 param, void *value)
{
    sub_2410C0(obj, (rwaStreamConnect *)value);

    return obj;
}

// match: _sub_2411D0 @ 0x002411D0
// sp-match: _sub_2411D0 @ 0x00155310
rwaDecoder *
sub_2411D0(rwaDecoder *obj, RwUInt32 param, void *value)
{
    sub_2410F0(obj, *(RwBool *)value);

    return obj;
}

// match: _sub_2411F0 @ 0x002411F0
// sp-match: _sub_2411F0 @ 0x00155330
void
sub_2411F0(rwaDecoder *obj, void *a, void *b)
{
    sub_2410F0(obj, TRUE);
    sub_243B80(obj->objInterface);
    sub_247500(&obj->state);
    sub_247120(obj, a, b);
}

// match: _sub_241230 @ 0x00241230
// sp-match: _sub_241230 @ 0x00155370
void
sub_241230(rwaDecoderState *state, RwBool failed, rwaDecoder *arg)
{
    rwaDecoder *obj = arg;
    RwUInt32 count;
    rwaQueueItem *items;
    rwaStreamPosition *positions;
    RwUInt32 i;
    rwaQueueCallback *callback;

    if (failed)
    {
        obj->status = 1;
    }
    else
    {
        positions = obj->state.positions;
        count = obj->state.noItems;
        items = obj->state.items;

        callback = &obj->state.callback;
        callback->func = sub_240E20;
        callback->data = obj;

        for (i = 0; i < count; i++)
        {
            items[i].flags = 0;
            items[i].unk04 = (RwUInt8 *)obj;
            items[i].callback = callback;
            items[i].unk08 = state->info->unk20;
            items[i].position = &positions[i];
            positions[i].type = 3;
            positions[i].unit = 2;
        }

        sub_2472E0(&obj->state.queue, items, count);
    }

    RwaStreamNodeCreationComplete(obj);
}


// match: _sub_2412F0 @ 0x002412F0
// sp-match: _sub_2412F0 @ 0x00155430
rwaDecoder *
sub_2412F0(rwaDecoder *obj, rwaInstance *parent, rwaStreamNodeParams *params, void *a, void *b)
{
    rwaStreamSourceParams   source;

    source.values[0] = params->source[0];
    source.values[6] = params->source[6];
    source.values[7] = params->source[7];
    source.values[2] = params->source[2];
    source.values[4] = params->source[4];
    source.values[5] = params->source[5];
    source.values[3] = params->source[3];
    source.values[1] = params->source[1];
    source.values[14] = params->source[14];
    source.values[13] = params->source[13];
    source.values[12] = params->source[12];
    source.values[8] = params->source[8];
    source.values[9] = params->source[9];
    source.data = obj;
    source.callback = sub_241230;
    source.values[11] = params->source[11];
    source.values[10] = params->source[10];

    sub_2472E0(&obj->state.queue, NULL, 0);

    if (obj->inst.subObjLink.next)
    {
        obj->inst.subObjLink.prev->next = obj->inst.subObjLink.next;
        obj->inst.subObjLink.next->prev = obj->inst.subObjLink.prev;
        obj->inst.subObjLink.prev = NULL;
        obj->inst.subObjLink.next = NULL;
    }

    if (!sub_246FD0(obj, parent, params, a, b))
    {
        return NULL;
    }

    if (!sub_249160(&obj->state, &source))
    {
        return NULL;
    }

    obj->objInterface = sub_243FF0(sub_243F40(unk_3ED9C4), obj->inst.def, params->unk14,
                                   params->unk18);

    return obj;
}

// match: _sub_241410 @ 0x00241410
// sp-match: _sub_241410 @ 0x00155550
static void
sub_241410(rwaObjDef *def)
{
    RwaObjDefAssignID(def, &unk_3ED29C, NULL);

    def->flags = sizeof(rwaDecoder) - sizeof(rwaInstance);
    rwaObjDefSetStateAlignment(def, rwaPow2(0x28));

    def->create = (RwBool (*)(rwaInstance *, rwaInstance *, void *, void *, void *))sub_2412F0;
    def->unlink = (void (*)(rwaInstance *, void *, void *))sub_2411F0;
    def->unk2C = (rwaInstance *(*)(rwaInstance *))sub_240C70;
    def->query = (void (*)(void *, void *))sub_240D80;
    def->paramsSize = sizeof(rwaStreamNodeParams);
    def->unk54 = unk_42E998;
}

// match: _sub_241660 @ 0x00241660
// sp-match: _sub_241660 @ 0x001557A0
rwaObjDef *
sub_241660(void)
{
    rwaObjDef  *def = sub_23DFB0(dword_516C60, 0xC, &unk_506B70, unk_506BCC, unk_506BE4,
                                 rwaMEMHINTDUR_EVENT | rwaID_80E);
    void       *iface;

    if (!def)
    {
        return NULL;
    }

    sub_241410(def);

    if (!_rwaObjDefSetupParams(def, unk_42E8A0, 5, unk_42E918, 5))
    {
        sub_23DB90(def);

        return NULL;
    }

    iface = RwaStreamSourceInterfaceRegister();
    if (!iface)
    {
        sub_23DB90(def);

        return NULL;
    }

    sub_23D740(def, iface);

    return def;
}
