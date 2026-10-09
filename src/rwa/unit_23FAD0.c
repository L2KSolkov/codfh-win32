/*
 * codfh-match: RenderWare Audio's stream object (0x23FAD0-0x240980): an
 * instance that plays a stream file through its player (+0xEC) and play
 * queue (+0x154). A worker thread runs the playing streams (list 0x506AB4)
 * under a semaphore; the object's parameter handlers wrap the locked
 * operations.
 */
#include "rwa.h"
#include "rwaint.h"



/* 23FC00 passes a second argument unused by 245E90. */
extern void sub_245E90(rwaStreamPlayer *player, const void *unusedSet);

#define rwaStreamFromSubLink(_link) ((rwaStream *)((RwUInt8 *)(_link) - 0x14))
#define rwaINFINITE 0xFFFFFFFF

static RwUInt32 dword_506A94;       /* the worker should stop */
static rwaLink dword_506AB4;        /* playing streams */
static RwInt32 dword_506B38;        /* stream count */
void *hSemaphore;
void *hObject;               /* the worker's exit */
extern rwaObjDef unk_506AD8;        /* the stream object definition */
extern RwUInt8 unk_506A98[];        /* the worker thread */
extern RwUInt8 unk_506AAC[];
extern RwUInt8 unk_506ABC[];
extern RwUInt32 dword_506B40;       /* the worker's priority */
extern const RwUInt8 unk_3ED864[];
extern const RwUInt8 unk_3EDF5C[];

extern RwUInt32 __stdcall WaitForSingleObject(void *handle, RwUInt32 milliseconds);
extern RwBool __stdcall ReleaseSemaphore(void *semaphore, RwInt32 count, RwInt32 *previous);
extern RwBool __stdcall CloseHandle(void *handle);
extern void __stdcall Sleep(RwUInt32 milliseconds);

extern void sub_23FEE0(rwaStream *stream, rwaStreamQuery *out);
extern void sub_23FC00(rwaStream *stream);
extern rwaObjDef *RwaObjDefAssignID(rwaObjDef *def, const void *uuid, const void *textID);
extern void *sub_23DCA0(void *a, const void *uuid, void *b);
extern rwaObjDef *sub_23DFB0(void *parent, RwInt32 a, void *b, void *c, void *d, RwUInt32 hint);
extern RwBool _rwaObjDefSetupParams(rwaObjDef *def, void *sets, RwInt32 noSets, void *gets,
                                    RwInt32 noGets);
extern rwaObjDef *sub_23D740(rwaObjDef *def, void *iface);
extern void *sub_243F40(const void *uuid);
extern RwBool sub_2416D0(void **handle, RwInt32 a, RwInt32 b);
extern RwBool _RwaThreadCreate(void *thread, RwUInt32 (*func)(void *), RwUInt32 priority,
                               void *data);
extern RwBool sub_241770(void *thread, RwInt32 a);
extern rwaInstance *sub_23F0D0(rwaInstance *obj, RwBool ok);
extern rwaInstance *sub_23F140(rwaInstance *obj, RwBool ok);
extern rwaInstance *sub_23F2F0(void);
extern rwaInstance *sub_23F4C0(rwaObjDef *def, rwaInstance *parent, RwUInt32 flags, void *params,
                               void *allocFunc, void *data);
extern RwBool sub_23DB90(rwaObjDef *def);
extern void *sub_2452D0(rwaStreamPlayer *player, void *callback, void *data);
extern void sub_245350(void *item, void *callback, void *data);
extern RwBool sub_246BD0(rwaStreamPlayer *player, rwaInstance *parent, RwUInt32 rate,
                         RwUInt32 a, RwUInt32 b, RwUInt32 c);
extern void sub_246D20(rwaStreamPlayer *player);
extern void sub_246E70(void *queue, rwaStreamPlay *play);
extern void sub_246EA0(void *queue, rwaStreamOpenParams *open);
extern void sub_246EB0(void *queue, RwUInt32 a, void *b);
extern void sub_246ED0(void *queue, void *a, RwUInt32 b, RwUInt32 c, RwUInt32 d, RwUInt32 e);
extern void sub_246F80(void *queue, RwUInt32 a);
extern void sub_246F90(void *queue, RwUInt32 a);
extern RwUInt32 sub_247510(rwaDecoderState *state, RwUInt32 value);
extern RwUInt32 sub_247570(rwaDecoderState *state, RwUInt32 value);
extern rwaStreamInfo *RwaObjIntGetParamUInt32(rwaDecoder *obj, void *objInterface, RwInt32 type);
extern RwChar *strncpy(RwChar *dst, const RwChar *src, RwUInt32 count);

// Its data (PLAN M5): literals, constants and tables where the image has them.

// What its data definitions name.
rwaStream *sub_240410(rwaStream *stream, RwUInt32 param, void *value);
rwaStream *sub_240430(rwaStream *stream, RwUInt32 param, void *value);
rwaStream *sub_240450(rwaStream *stream, RwUInt32 param, void *value);
rwaStream *sub_240470(rwaStream *stream, RwUInt32 param, void *value);
rwaStream *sub_240490(rwaStream *stream, RwUInt32 param, void *value);
rwaStream *sub_2404B0(rwaStream *stream, RwUInt32 param, void *value);
rwaStream *sub_2404D0(rwaStream *stream, RwUInt32 param, void *value);
rwaStream *sub_2404F0(rwaStream *stream, RwUInt32 param, void *value);
rwaStream *sub_240510(rwaStream *stream, RwUInt32 param, void *value);
rwaStream *sub_240530(rwaStream *stream, RwUInt32 param, void *value);
rwaStream *sub_240550(rwaStream *stream, RwUInt32 param, void *value);
rwaStream *sub_240570(rwaStream *stream, RwUInt32 param, void *value);
rwaStream *sub_240590(rwaStream *stream, RwUInt32 param, void *value);
rwaStream *sub_2405B0(rwaStream *stream, RwUInt32 param, void *value);
rwaStream *sub_2405D0(rwaStream *stream, RwUInt32 param, void *value);
extern RwUInt8 unk_3ED4EC[];
extern RwUInt8 unk_3ED52C[];
extern RwUInt8 unk_3ED55C[];
extern RwUInt8 unk_3ED56C[];
extern RwUInt8 unk_3ED874[];
extern RwUInt8 unk_3ED884[];
extern RwUInt8 unk_3ED894[];
extern RwUInt8 unk_3ED8A4[];
extern RwUInt8 unk_3ED8B4[];
extern RwUInt8 unk_3ED8C4[];
extern RwUInt8 unk_3ED8D4[];
extern RwUInt8 unk_3ED8E4[];
extern RwUInt8 unk_3ED8F4[];
extern RwUInt8 unk_3ED904[];
extern RwUInt8 unk_3ED914[];
extern RwUInt8 unk_3ED924[];
extern RwUInt8 unk_3ED934[];
extern RwUInt8 unk_3ED944[];
extern RwUInt8 unk_3ED954[];
// Its data definitions (PLAN M5), in the image's address order.
// 0x003ED28C
const RwaUUID unk_3ED28C = { 0xBFA372E2, 0x46FE, 0x4238, { 0x8A, 0xF5, 0xF4, 0xD2, 0x4C, 0x02, 0x34, 0x1C } };
// 0x0042E708
void *unk_42E708[36] =
{
    (void *)&unk_3ED874,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)sub_240410,
    (void *)&unk_3ED894,
    0,
    0,
    (void *)&unk_3ED55C,
    (void *)0x1,
    (void *)sub_240450,
    (void *)&unk_3ED8A4,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)sub_240470,
    (void *)&unk_3ED8B4,
    0,
    0,
    (void *)&unk_3ED4EC,
    (void *)0x1,
    (void *)sub_240490,
    (void *)&unk_3ED8F4,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)sub_240510,
    (void *)&unk_3ED914,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)sub_240550,
};
// 0x0042E798
#ifdef CODFH_SP // nine entries, no tail: unit_23CC10's unk_42E488 follows at SP 0x32AAA8 (table at SP 0x32A9D0)
void *unk_42E798[54] =
#else
void *unk_42E798[66] =
#endif
{
    (void *)&unk_3ED884,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)sub_240430,
    (void *)&unk_3ED8C4,
    0,
    0,
    (void *)&unk_3ED4EC,
    (void *)0x1,
    (void *)sub_2404B0,
    (void *)&unk_3ED8D4,
    0,
    0,
    (void *)&unk_3ED4EC,
    (void *)0x1,
    (void *)sub_2404D0,
    (void *)&unk_3ED8E4,
    0,
    0,
    (void *)&unk_3ED4EC,
    (void *)0x1,
    (void *)sub_2404F0,
    (void *)&unk_3ED904,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)sub_240530,
    (void *)&unk_3ED924,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)sub_240570,
    (void *)&unk_3ED934,
    0,
    0,
    (void *)&unk_3ED4EC,
    (void *)0x1,
    (void *)sub_240590,
    (void *)&unk_3ED944,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)sub_2405B0,
    (void *)&unk_3ED954,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)sub_2405D0,
#ifndef CODFH_SP
    (void *)0x1,
    (void *)0x382E3825,
    (void *)0x34252D78,
    (void *)0x2D78342E,
    (void *)0x342E3425,
    (void *)0x32252D78,
    (void *)0x2578322E,
    (void *)0x78322E32,
    (void *)0x2D,
    (void *)0x322E3225,
    (void *)0x78,
    0,
#endif
};
// 0x00506A98
RwUInt8 unk_506A98[20];
// 0x00506AAC
RwUInt8 unk_506AAC[8];
// 0x00506ABC
RwUInt8 unk_506ABC[28];
// 0x00506AD8
rwaObjDef unk_506AD8;
// 0x00506B40
RwUInt32 dword_506B40;
// End of its data definitions.

// match: _unk_3ED28C @ 0x003ED28C


// match: _unk_42E708 @ 0x0042E708


// match: _unk_42E798 @ 0x0042E798

// match: _RwaStreamCreate_0 @ 0x0023FAD0
// sp-match: _RwaStreamCreate_0 @ 0x00152660

rwaInstance *
RwaStreamCreate_0(rwaInstance *parent, void *params, RwUInt32 flags, void *allocFunc, void *data)
{
    return sub_23F4C0(&unk_506AD8, parent, flags, params, allocFunc, data);
}

// match: _sub_23FB00 @ 0x0023FB00
// sp-match: _sub_23FB00 @ 0x00152690
RwBool
sub_23FB00(void)
{
    dword_506A94 = 1;
    WaitForSingleObject(hObject, rwaINFINITE);
    CloseHandle(hSemaphore);
    CloseHandle(hObject);
    return sub_23DB90(&unk_506AD8);
}

// match: _sub_23FB40 @ 0x0023FB40
// sp-match: _sub_23FB40 @ 0x001526D0
rwaStream *
sub_23FB40(rwaStream *stream, rwaInstance *parent, RwUInt32 *params)
{
    RwInt32 count;
    if (stream->inst.subObjLink.next)
    {
        stream->inst.subObjLink.prev->next = stream->inst.subObjLink.next;
        stream->inst.subObjLink.next->prev = stream->inst.subObjLink.prev;
        stream->inst.subObjLink.prev = NULL;
        stream->inst.subObjLink.next = NULL;
    }

    stream->flags = 0;

    if (!sub_246BD0(&stream->player, parent, 48000, params[0], params[1], params[2]))
    {
        return NULL;
    }

    if (dword_506B38)
    {
        WaitForSingleObject(hSemaphore, rwaINFINITE);
    }

    /* Keep the count reload before relinking, as at 23FBC1. */
    count = *(volatile RwInt32 *)&dword_506B38;
    stream->inst.subObjLink.next = dword_506AB4.next;
    stream->inst.subObjLink.prev = &dword_506AB4;
    dword_506AB4.next->prev = &stream->inst.subObjLink;
    dword_506AB4.next = &stream->inst.subObjLink;

    if (count)
    {
        ReleaseSemaphore(hSemaphore, 1, NULL);
    }

    dword_506B38++;

    return stream;
}

// match: _sub_23FC00 @ 0x0023FC00
// sp-match: _sub_23FC00 @ 0x00152790
void
sub_23FC00(rwaStream *volatile input)
{
    /* Preserve the image's count load, input load, decrement/store order.
     * The original qualifiers are unknown; these accesses reproduce it. */
    rwaStream *stream;
    RwInt32 count = *(volatile RwInt32 *)&dword_506B38;
    stream = input;
    count--;
    *(volatile RwInt32 *)&dword_506B38 = count;
    WaitForSingleObject(hSemaphore, rwaINFINITE);

    sub_245E90(&stream->player, stream->unk148);

    if (stream->inst.subObjLink.next)
    {
        stream->inst.subObjLink.prev->next = stream->inst.subObjLink.next;
        stream->inst.subObjLink.next->prev = stream->inst.subObjLink.prev;
        stream->inst.subObjLink.prev = NULL;
        stream->inst.subObjLink.next = NULL;
    }

    ReleaseSemaphore(hSemaphore, 1, NULL);
}

// match: _sub_23FC60 @ 0x0023FC60
// sp-match: _sub_23FC60 @ 0x001527F0
RwUInt32
sub_23FC60(void *data)
{
    while (!dword_506A94)
    {
        rwaLink    *cur;

        WaitForSingleObject(hSemaphore, rwaINFINITE);

        for (cur = dword_506AB4.next; cur != &dword_506AB4; cur = cur->next)
        {
            rwaStream  *stream = rwaStreamFromSubLink(cur);

            sub_23F0D0(&stream->inst, FALSE);
            sub_23F140(&stream->inst, FALSE);
        }

        ReleaseSemaphore(hSemaphore, 1, NULL);
        Sleep(17);
    }

    ReleaseSemaphore(hObject, 1, NULL);

    return 0;
}

// match: _sub_23FCF0 @ 0x0023FCF0
// sp-match: _sub_23FCF0 @ 0x00152880
void
sub_23FCF0(rwaInstance *obj, rwaInstance *parent)
{
    if (obj->subObjLink.next)
    {
        obj->subObjLink.prev->next = obj->subObjLink.next;
        obj->subObjLink.next->prev = obj->subObjLink.prev;
    }

    obj->subObjLink.next = parent->subObjs.next;
    obj->subObjLink.prev = &parent->subObjs;
    parent->subObjs.next->prev = &obj->subObjLink;
    parent->subObjs.next = &obj->subObjLink;
    obj->parent = parent;
}

// match: _sub_23FD30 @ 0x0023FD30
// sp-match: _sub_23FD30 @ 0x001528C0
rwaStream *
sub_23FD30(rwaStream *stream)
{
    sub_246D20(&stream->player);

    if ((stream->flags & 1) && stream->player.state >= 5)
    {
        void       *item = sub_2452D0(&stream->player, sub_23FCF0, stream);

        if (item)
        {
            sub_245350(item, sub_23FCF0, stream);
        }

        sub_23F0D0(&stream->inst, TRUE);
        sub_23F140(&stream->inst, TRUE);

        WaitForSingleObject(hSemaphore, rwaINFINITE);

        if (stream->inst.subObjLink.next)
        {
            stream->inst.subObjLink.prev->next = stream->inst.subObjLink.next;
            stream->inst.subObjLink.next->prev = stream->inst.subObjLink.prev;
            stream->inst.subObjLink.prev = NULL;
            stream->inst.subObjLink.next = NULL;
        }

        stream->inst.subObjLink.next = dword_506AB4.next;
        stream->inst.subObjLink.prev = &dword_506AB4;
        dword_506AB4.next->prev = &stream->inst.subObjLink;
        dword_506AB4.next = &stream->inst.subObjLink;

        stream->flags &= ~1;

        ReleaseSemaphore(hSemaphore, 1, NULL);
    }

    return stream;
}

// match: _sub_23FE10 @ 0x0023FE10
// sp-match: _sub_23FE10 @ 0x001529A0
void *
sub_23FE10(void *obj, RwUInt32 *params)
{
    params[0] = 0;
    params[1] = 0;
    params[2] = 0;

    return obj;
}

// match: _sub_23FE30 @ 0x0023FE30
// sp-match: _sub_23FE30 @ 0x001529C0
void
sub_23FE30(rwaStream *stream, rwaStreamOpenParams *params)
{
    rwaStreamOpenParams *open;

    stream->open = *params;
    open = &stream->open;
    stream->sourceCopy = *params->source;
    open->source = &stream->sourceCopy;

    if (params->source->type == 1)
    {
        strncpy(stream->name, (const RwChar *)params->source->data, sizeof(stream->name));
    }
    else if (params->source->type == 2)
    {
        stream->uuid = *(RwaUUID *)params->source->data;
    }

    WaitForSingleObject(hSemaphore, rwaINFINITE);
    sub_246EA0(stream->queue, open);
    ReleaseSemaphore(hSemaphore, 1, NULL);
}
extern rwaStreamPosition *sub_245D90(rwaStreamPlayer *player, const rwaNodeSet *set);
// match: _sub_23FEE0 @ 0x0023FEE0
// sp-match: _sub_23FEE0 @ 0x00152A70
void
sub_23FEE0(rwaStream *stream, rwaStreamQuery *query)
{
    rwaStreamQuery *out = query;
    rwaStreamPosition  *cur;
    rwaDecoderState    *state;

    WaitForSingleObject(hSemaphore, rwaINFINITE);

    cur = sub_245D90(&stream->player, (const rwaNodeSet *)stream->unk148);
    if (!cur)
    {
        out->pos = 0;
        out->value = 0;
        ReleaseSemaphore(hSemaphore, 1, NULL);

        return;
    }

    ReleaseSemaphore(hSemaphore, 1, NULL);

    state = &stream->player.decoder->state;

    switch (out->unit)
    {
        case 1:
            *(RwReal *)&out->pos = (RwReal)cur->pos /
                                   (RwReal)stream->player.info->tracks->format->rate;
            break;
        case 2:
            out->pos = cur->pos;
            break;
    }

    switch (out->type)
    {
        case 1:
            out->value = (RwUInt32)state->info->markers[cur->value].name;
            break;
        case 2:
            out->value = (RwUInt32)state->info->markers[cur->value].uuid;
            break;
        case 3:
            out->value = cur->value;
            break;
    }
}

// match: _sub_23FFD0 @ 0x0023FFD0
// sp-match: _sub_23FFD0 @ 0x00152B60
void
sub_23FFD0(rwaStream *stream, RwUInt32 a)
{
    WaitForSingleObject(hSemaphore, rwaINFINITE);
    sub_246F80(stream->queue, a);
    ReleaseSemaphore(hSemaphore, 1, NULL);
}

// match: _sub_240010 @ 0x00240010
// sp-match: _sub_240010 @ 0x00152BA0
void
sub_240010(rwaStream *stream, rwaStreamPlay *play)
{
    WaitForSingleObject(hSemaphore, rwaINFINITE);

    if (play)
    {
        if (play->settings)
        {
            stream->settings = *play->settings;
        }

        stream->play = *play;
        play = &stream->play;
        play->settings = &stream->settings;
    }

    sub_246E70(stream->queue, play);

    stream->inst.subObjLink.prev->next = stream->inst.subObjLink.next;
    stream->inst.subObjLink.next->prev = stream->inst.subObjLink.prev;

    stream->flags |= 1;

    ReleaseSemaphore(hSemaphore, 1, NULL);

    if (stream->inst.subObjLink.next)
    {
        stream->inst.subObjLink.prev->next = stream->inst.subObjLink.next;
        stream->inst.subObjLink.next->prev = stream->inst.subObjLink.prev;
    }

    stream->inst.subObjLink.next = sub_23F2F0()->subObjs.next;
    stream->inst.subObjLink.prev = &sub_23F2F0()->subObjs;
    sub_23F2F0()->subObjs.next->prev = &stream->inst.subObjLink;
    sub_23F2F0()->subObjs.next = &stream->inst.subObjLink;
}

// match: _sub_2400E0 @ 0x002400E0
// sp-match: _sub_2400E0 @ 0x00152C70
void
sub_2400E0(rwaStream *stream, RwUInt32 a)
{
    WaitForSingleObject(hSemaphore, rwaINFINITE);
    sub_246F90(stream->queue, a);
    ReleaseSemaphore(hSemaphore, 1, NULL);
}

// match: _sub_240120 @ 0x00240120
// sp-match: _sub_240120 @ 0x00152CB0
RwUInt32
sub_240120(rwaStream *stream)
{
    return stream->unkD6C;
}

// match: _sub_240130 @ 0x00240130
// sp-match: _sub_240130 @ 0x00152CC0
RwUInt32
sub_240130(rwaStream *stream)
{
    return stream->unkD70;
}

// match: _sub_240140 @ 0x00240140
// sp-match: _sub_240140 @ 0x00152CD0
RwUInt32
sub_240140(rwaStream *stream)
{
    return stream->unkD74;
}

// match: _sub_240150 @ 0x00240150
// sp-match: _sub_240150 @ 0x00152CE0
void
sub_240150(rwaStream *stream, rwaStreamCue *cue)
{
    WaitForSingleObject(hSemaphore, rwaINFINITE);
    sub_246ED0(stream->queue, stream->unk148, cue->unk00, cue->unk04, cue->unk08, cue->unk0C);
    ReleaseSemaphore(hSemaphore, 1, NULL);
}

// match: _sub_2401A0 @ 0x002401A0
// sp-match: _sub_2401A0 @ 0x00152D30
void *
sub_2401A0(rwaStream *stream)
{
    return stream->unk16C;
}

// match: _sub_2401B0 @ 0x002401B0
// sp-match: _sub_2401B0 @ 0x00152D40
void
sub_2401B0(rwaStream *stream, RwUInt32 a)
{
    WaitForSingleObject(hSemaphore, rwaINFINITE);
    sub_246EB0(stream->queue, a, stream->unk148);
    ReleaseSemaphore(hSemaphore, 1, NULL);
}

// match: _sub_2401F0 @ 0x002401F0
// sp-match: _sub_2401F0 @ 0x00152D80
RwReal
sub_2401F0(rwaStream *stream)
{
    return stream->player.unk34;
}

// match: _sub_240200 @ 0x00240200
// sp-match: _sub_240200 @ 0x00152D90
RwUInt32
sub_240200(rwaStream *stream)
{
    rwaDecoder *decoder;
    RwUInt32    value;

    WaitForSingleObject(hSemaphore, rwaINFINITE);
    decoder = stream->player.decoder;
    value = RwaObjIntGetParamUInt32(decoder, decoder->objInterface, 2)->unk0C;
    ReleaseSemaphore(hSemaphore, 1, NULL);

    return value;
}

// match: _sub_240240 @ 0x00240240
// sp-match: _sub_240240 @ 0x00152DD0
void
sub_240240(rwaStream *stream, rwaStreamQuery *out)
{
    rwaDecoder     *decoder;
    rwaStreamInfo  *info;
    RwUInt32        index;
    rwaStreamMarker *marker;

    WaitForSingleObject(hSemaphore, rwaINFINITE);

    decoder = stream->player.decoder;

    switch (out->type)
    {
        case 1:
            index = sub_247570(&decoder->state, out->value);
            break;
        case 2:
            index = sub_247510(&decoder->state, out->value);
            break;
        case 3:
            index = out->value;
            break;
    }

    info = RwaObjIntGetParamUInt32(decoder, decoder->objInterface, 2);

    marker = &info->markers[index];
    if (marker && info->noTracks)
    {
        rwaStreamTrack *track;
        RwUInt32        channels;

        out->pos = *marker->unk0C;
        out->unk10 = info->noTracks;
        out->value = index;
        out->type = 3;

        track = info->tracks;
        channels = (track->format->flags & 4) ? 1 : track->format->channels;
        out->pos = track->unk0C * out->pos / track->unk1A / channels;

        switch (out->unit)
        {
            case 1:
                *(RwReal *)&out->pos = (RwReal)out->pos / (RwReal)info->tracks->format->rate;
                break;
        }

        ReleaseSemaphore(hSemaphore, 1, NULL);
    }
    else
    {
        out->type = 0;
        out->unit = 0;
        out->unk10 = 0;

        ReleaseSemaphore(hSemaphore, 1, NULL);
    }
}

// match: _sub_240370 @ 0x00240370
// sp-match: _sub_240370 @ 0x00152F00
void
sub_240370(rwaStream *stream, rwaStreamQuery *out)
{
    rwaDecoder     *decoder;
    rwaStreamInfo  *info;

    WaitForSingleObject(hSemaphore, rwaINFINITE);

    decoder = stream->player.decoder;
    info = RwaObjIntGetParamUInt32(decoder, decoder->objInterface, 2);

    if (out->pos < info->noTracks && &info->tracks[out->pos])
    {
        rwaStreamTrack *track = &info->tracks[out->pos];

        out->unit = (track->format->flags & 4) ? 1 : track->format->channels;
    }
    else
    {
        out->unit = 0;
    }

    ReleaseSemaphore(hSemaphore, 1, NULL);
}

// match: _sub_240410 @ 0x00240410
// sp-match: _sub_240410 @ 0x00152FA0
rwaStream *
sub_240410(rwaStream *stream, RwUInt32 param, void *value)
{
    sub_23FE30(stream, (rwaStreamOpenParams *)value);

    return stream;
}

// match: _sub_240430 @ 0x00240430
// sp-match: _sub_240430 @ 0x00152FC0
rwaStream *
sub_240430(rwaStream *stream, RwUInt32 param, void *value)
{
    sub_23FEE0(stream, (rwaStreamQuery *)value);

    return stream;
}

// match: _sub_240450 @ 0x00240450
// sp-match: _sub_240450 @ 0x00152FE0
rwaStream *
sub_240450(rwaStream *stream, RwUInt32 param, void *value)
{
    sub_23FFD0(stream, *(RwUInt32 *)value);

    return stream;
}

// match: _sub_240470 @ 0x00240470
// sp-match: _sub_240470 @ 0x00153000
rwaStream *
sub_240470(rwaStream *stream, RwUInt32 param, void *value)
{
    sub_240010(stream, (rwaStreamPlay *)value);

    return stream;
}

// match: _sub_240490 @ 0x00240490
// sp-match: _sub_240490 @ 0x00153020
rwaStream *
sub_240490(rwaStream *stream, RwUInt32 param, void *value)
{
    sub_2400E0(stream, *(RwUInt32 *)value);

    return stream;
}

// match: _sub_2404B0 @ 0x002404B0
// sp-match: _sub_2404B0 @ 0x00153040
rwaStream *
sub_2404B0(rwaStream *stream, RwUInt32 param, void *value)
{
    *(RwUInt32 *)value = sub_240120(stream);

    return stream;
}

// match: _sub_2404D0 @ 0x002404D0
// sp-match: _sub_2404D0 @ 0x00153060
rwaStream *
sub_2404D0(rwaStream *stream, RwUInt32 param, void *value)
{
    *(RwUInt32 *)value = sub_240130(stream);

    return stream;
}

// match: _sub_2404F0 @ 0x002404F0
// sp-match: _sub_2404F0 @ 0x00153080
rwaStream *
sub_2404F0(rwaStream *stream, RwUInt32 param, void *value)
{
    *(RwUInt32 *)value = sub_240140(stream);

    return stream;
}

// match: _sub_240510 @ 0x00240510
// sp-match: _sub_240510 @ 0x001530A0
rwaStream *
sub_240510(rwaStream *stream, RwUInt32 param, void *value)
{
    sub_240150(stream, (rwaStreamCue *)value);

    return stream;
}

// match: _sub_240530 @ 0x00240530
// sp-match: _sub_240530 @ 0x001530C0
rwaStream *
sub_240530(rwaStream *stream, RwUInt32 param, void *value)
{
    *(void **)value = sub_2401A0(stream);

    return stream;
}

// match: _sub_240550 @ 0x00240550
// sp-match: _sub_240550 @ 0x001530E0
rwaStream *
sub_240550(rwaStream *stream, RwUInt32 param, void *value)
{
    sub_2401B0(stream, *(RwUInt32 *)value);

    return stream;
}

// match: _sub_240570 @ 0x00240570
// sp-match: _sub_240570 @ 0x00153100
rwaStream *
sub_240570(rwaStream *stream, RwUInt32 param, void *value)
{
    *(RwReal *)value = sub_2401F0(stream);

    return stream;
}

// match: _sub_240590 @ 0x00240590
// sp-match: _sub_240590 @ 0x00153120
rwaStream *
sub_240590(rwaStream *stream, RwUInt32 param, void *value)
{
    *(RwUInt32 *)value = sub_240200(stream);

    return stream;
}

// match: _sub_2405B0 @ 0x002405B0
// sp-match: _sub_2405B0 @ 0x00153140
rwaStream *
sub_2405B0(rwaStream *stream, RwUInt32 param, void *value)
{
    sub_240240(stream, (rwaStreamQuery *)value);

    return stream;
}

// match: _sub_2405D0 @ 0x002405D0
// sp-match: _sub_2405D0 @ 0x00153160
rwaStream *
sub_2405D0(rwaStream *stream, RwUInt32 param, void *value)
{
    sub_240370(stream, (rwaStreamQuery *)value);

    return stream;
}

// match: _sub_2405F0 @ 0x002405F0
// sp-match: _sub_2405F0 @ 0x00153180
static void
sub_2405F0(rwaObjDef *def)
{
    RwaObjDefAssignID(def, &unk_3ED28C, NULL);

    def->flags = sizeof(rwaStream) - sizeof(rwaInstance);
    rwaObjDefSetStateAlignment(def, rwaPow2(0x28));

    def->create = (RwBool (*)(rwaInstance *, rwaInstance *, void *, void *, void *))sub_23FB40;
    def->unlink = (void (*)(rwaInstance *, void *, void *))sub_23FC00;
    def->unk30 = (rwaInstance *(*)(rwaInstance *))sub_23FD30;
    def->query = (void (*)(void *, void *))sub_23FE10;
    def->paramsSize = 0xC;

    dword_506AB4.next = &dword_506AB4;
    dword_506AB4.prev = &dword_506AB4;

    if (sub_2416D0(&hSemaphore, 1, 1))
    {
        if (sub_2416D0(&hObject, 0, 1))
        {
            dword_506A94 = 0;
            if (_RwaThreadCreate(unk_506A98, sub_23FC60, dword_506B40, NULL) &&
                sub_241770(unk_506A98, 0))
            {
                return;
            }

            CloseHandle(hObject);
        }

        CloseHandle(hSemaphore);
    }
}

// match: _sub_2408C0 @ 0x002408C0
// sp-match: _sub_2408C0 @ 0x00153450
rwaObjDef *
sub_2408C0(void)
{
    rwaObjDef  *def = sub_23DFB0(sub_23DCA0(NULL, unk_3EDF5C, NULL), 0, &unk_506AD8, NULL, NULL,
                                 rwaMEMHINTDUR_EVENT | rwaID_80E);

    if (!def)
    {
        return NULL;
    }

    sub_2405F0(def);

    return def;
}

extern rwaStreamPosition *sub_245D90(rwaStreamPlayer *player, const rwaNodeSet *set);

// match: _sub_240900 @ 0x00240900
// sp-match: _sub_240900 @ 0x00153490
rwaObjDef *
sub_240900(void)
{
    rwaObjDef  *def = sub_23DFB0(sub_23DCA0(NULL, unk_3EDF5C, NULL), 0xC, &unk_506AD8,
                                 unk_506ABC, unk_506AAC, rwaMEMHINTDUR_EVENT | rwaID_80E);

    if (!def)
    {
        return NULL;
    }

    sub_2405F0(def);

    if (!_rwaObjDefSetupParams(def, unk_42E708, 6, unk_42E798, 9))
    {
        sub_23DB90(def);

        return NULL;
    }

    sub_23D740(def, sub_243F40(unk_3ED864));

    return def;
}
