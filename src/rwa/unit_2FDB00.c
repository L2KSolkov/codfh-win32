/*
 * codfh-match: RenderWare Audio's stream voice (0x2FDB00-0x2FEC60), linked
 * after the allocation bitmaps: a stream node (definition 0x512658) that
 * uploads its queue items into the entries of a streamed wave and plays it
 * looping through an embedded Xbox voice, following the voice's position to
 * return each played item; its rate, levels and position parameters, its
 * definition's set-up and registration, and the handlers of the voices it
 * mutes (0x5126B4).
 */
#include "rwa.h"
#include "rwaint.h"



extern void *memset(void *dst, RwInt32 value, RwUInt32 size);

extern rwaObjDef *sub_23DCA0(rwaObjDef *parent, const void *uuid, const void *textID);
extern RwBool sub_23DB90(rwaObjDef *def);
extern void sub_23D8B0(rwaInstance *obj, void *a, void *b);
extern rwaObjDef *sub_23DFB0(void *parent, RwInt32 a, void *b, void *c, void *d, RwUInt32 hint);
extern RwBool _rwaObjDefSetupParams(rwaObjDef *def, void *sets, RwInt32 noSets, void *gets, RwInt32 noGets);
extern rwaObjDef *sub_23D740(rwaObjDef *def, void *iface);
extern rwaObjDef *RwaObjDefAssignID(rwaObjDef *def, const void *uuid, const void *textID);
extern RwUInt8 sub_242150(RwUInt32 value);
extern rwaInstance *_rwaObjFindFixed(rwaObjDef *def);
extern rwaInstance *sub_23F0D0(rwaInstance *obj, RwBool flag);
extern rwaInstance *sub_23F140(rwaInstance *obj, RwBool flag);
extern RwInt32 sub_23F960(RwaObjHandle *handle, RwInt32 param, RwInt32 type, RwInt32 value);
extern void RwaObjHandleSetParamUInt8(RwaObjHandle *handle, RwInt32 param, RwInt32 type, RwUInt32 value);
extern void *sub_243F40(const void *uuid);
extern void *sub_243FF0(void *objInterface, rwaObjDef *def, RwUInt32 a, RwUInt32 b);
extern RwInt32 sub_243B80(void *objInterface);
extern RwUInt32 sub_2433C0(const RwaWaveFormat *format, RwUInt32 size);
extern RwBool sub_242570(RwaWave *wave);
extern RwaWave *sub_242810(RwaWave *wave, RwUInt32 offset, void *buffer, RwUInt32 size);
extern rwaDecoder *sub_246FD0(rwaDecoder *obj, rwaInstance *parent, void *params, void *a, void *b);
extern void RwaStreamNodeCreationComplete(rwaDecoder *obj);
extern rwaDecoder *RwaStreamNodeGetParams(rwaDecoder *obj, void *params);
extern void sub_2470A0(rwaDecoder *obj);
extern void sub_247120(rwaDecoder *obj, void *a, void *b);
extern void sub_247160(rwaDecoder *obj, void *data, RwInt32 *mode);
extern rwaQueueItem *sub_247200(rwaStreamReader *reader);
extern void sub_247290(rwaDecoder *obj, void *objInterface, RwInt32 type, ...);
extern RwaWave *sub_24DA70(void *params, const RwaWaveFormat *format, RwaWaveFormat *target, RwBool mono,
                           RwaWave *wave);
extern void sub_24DAA0(RwaWave *wave);
extern rwaInstance *RwaStreamCreate_2(rwaInstance *parent, void *params, void *def, void *allocFunc, void *data);
extern void DSPHandle_Stop(rwaInstance *obj, void *a, void *b);
extern void sub_24F040(rwaXboxVoice *obj, const rwaI3DL2Listener *settings);
extern void sub_24F1A0(rwaXboxVoice *obj, RwReal frequency);
extern RwReal sub_24F1C0(rwaXboxVoice *obj);
extern void sub_24F1D0(rwaXboxVoice *obj, RwReal volume);
extern RwReal sub_24F1F0(rwaXboxVoice *obj);
extern void sub_24F200(rwaXboxVoice *obj, RwBool play);
extern RwBool sub_24F240(rwaXboxVoice *obj);
extern void sub_24F270(rwaXboxVoice *obj, RwUInt32 position);
extern RwUInt32 sub_24F2F0(rwaXboxVoice *obj);
extern void sub_24F300(rwaXboxVoice *obj, RwBool loop);
extern void sub_24F410(rwaXboxVoice *obj, RwaWave *wave);
extern RwaWave *sub_24F7E0(rwaXboxVoice *obj);
extern void sub_24F7F0(rwaXboxVoice *obj, RwReal pan);
extern RwReal sub_24F810(rwaXboxVoice *obj);

extern rwaObjDef unk_512658;        /* the stream voice definition */
extern RwUInt8 unk_512638[];
extern RwUInt8 unk_512650[];
extern const RwUInt8 unk_3ED964[];  /* the stream node interface */
extern const RwUInt8 unk_3EDEFC[];  /* the stream renderer interface */
extern const RwUInt8 unk_3EDF5C[];
extern const RwUInt8 unk_3EDF6C[];  /* the voice */
extern rwaNodeAllocator off_42FB3C; /* the default memory functions */

static RwaObjHandle **dword_5126B4; /* the voices it mutes */
static RwUInt32 dword_5126B8;

static void sub_2FDF80(rwaDecoder *obj, RwBool play, RwBool rewind);
static void sub_2FE1E0(rwaStreamVoiceState *state);

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: _unk_41AB64 @ 0x0041AB64
// match: _unk_438B98 @ 0x00438B98

// What its data definitions name.
extern void sub_247140(void);
extern void sub_2471F0(void);
rwaDecoder *sub_2FE210(rwaDecoder *obj, const void *param, const RwUInt32 *value);
rwaDecoder *sub_2FE230(rwaDecoder *obj, const void *param, RwUInt32 *value);
rwaDecoder *sub_2FE250(rwaDecoder *obj, const void *param, const rwaChannelLevel *value);
rwaDecoder *sub_2FE270(rwaDecoder *obj, const void *param, rwaStreamPosition **value);
rwaDecoder *sub_2FE800(rwaDecoder *obj, const void *param, const RwBool *value);
extern RwUInt8 unk_3ED4EC[];
extern RwUInt8 unk_3ED55C[];
extern RwUInt8 unk_3ED56C[];
extern RwUInt8 unk_3ED974[];
extern RwUInt8 unk_3ED984[];
extern RwUInt8 unk_3ED994[];
extern RwUInt8 unk_3ED9A4[];
extern RwUInt8 unk_3ED9B4[];
extern RwUInt8 unk_3EDF0C[];
extern RwUInt8 unk_3EDF1C[];
extern RwUInt8 unk_3EDF2C[];
extern RwUInt8 unk_3EDF3C[];
// Its data definitions (PLAN M5), in the image's address order.
// 0x0041AB64
const RwaUUID unk_41AB64 = { 0x97EF880B, 0xF418, 0x44F5, { 0x8D, 0x75, 0x16, 0x22, 0x8B, 0x45, 0xD4, 0x81 } };
// 0x00438B98
void *unk_438B98[6] =
{
    (void *)0x1,
    0,
    0,
    (void *)0x20,
    0,
    0,
};
// 0x00438BB0
void *off_438BB0[30] =
{
    (void *)&unk_3EDF0C,
    0,
    0,
    (void *)&unk_3ED4EC,
    (void *)0x1,
    (void *)sub_2FE210,
    (void *)&unk_3EDF2C,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)sub_2FE250,
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
    0,
    (void *)&unk_3ED9B4,
    0,
    0,
    (void *)&unk_3ED55C,
    (void *)0x1,
    (void *)sub_2FE800,
};
// 0x00438C28
void *off_438C28[24] =
{
    (void *)&unk_3EDF1C,
    0,
    0,
    (void *)&unk_3ED4EC,
    (void *)0x1,
    (void *)sub_2FE230,
    (void *)&unk_3EDF3C,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)sub_2FE270,
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
};
// 0x00512638
RwUInt8 unk_512638[24];
// 0x00512650
RwUInt8 unk_512650[8];
// 0x00512658
rwaObjDef unk_512658;
// End of its data definitions.

// match: _off_438BB0 @ 0x00438BB0


// match: _off_438C28 @ 0x00438C28

// match: _sub_2FDB00 @ 0x002FDB00
// sp-match: _sub_2FDB00 @ 0x00217DC0

RwBool
sub_2FDB00(void)
{
    return sub_23DB90(&unk_512658);
}

/* The embedded voice's allocation: its place in the stream voice's state
 * unless the caller's allocation callback gives another. */
// match: _sub_2FDB10 @ 0x002FDB10
// sp-match: _sub_2FDB10 @ 0x00217DD0
static void *
sub_2FDB10(rwaObjDef *def, rwaStreamVoiceAlloc *alloc, rwaXboxVoiceParams *params, void *data)
{
    void       *mem = NULL;

    if (def == sub_23DCA0(NULL, unk_3EDF6C, NULL))
    {
        mem = &alloc->state->voice;
    }
    params->headroomGain = 1.0f;
    params->flags |= rwaXBVOICEHEADROOM;
    if (alloc->func)
    {
        void       *result = ((void *(*)(rwaObjDef *, void *, rwaXboxVoiceParams *, void *))alloc->func)(def, alloc->data, params, data);

        if (result)
        {
            mem = result;
        }
    }

    return mem;
}

/* Its release: the caller's callback, else filled in debug fashion (its
 * own place) or released. */
// match: _sub_2FDB70 @ 0x002FDB70
// sp-match: _sub_2FDB70 @ 0x00217E30
static void
sub_2FDB70(rwaInstance *obj, rwaStreamVoiceAlloc *alloc)
{
    if (alloc->func)
    {
        ((void (*)(rwaInstance *, void *))alloc->func)(obj, alloc->data);
        return;
    }
    if (obj->def == sub_23DCA0(NULL, unk_3EDF6C, NULL))
    {
        memset(&alloc->state->voice, 0xCD, sizeof(rwaXboxVoice));
        return;
    }
    sub_23D8B0(obj, alloc->func, alloc->data);
}

// match: _sub_2FDBD0 @ 0x002FDBD0
// sp-match: _sub_2FDBD0 @ 0x00217E90
static rwaDecoder *
sub_2FDBD0(rwaDecoder *obj, rwaInstance *parent, rwaStreamVoiceParams *params, void *a, void *b)
{
    rwaStreamVoiceState *state = (rwaStreamVoiceState *)obj->inst.state;
    rwaStreamTrack *track;
    rwaStreamVoiceAlloc alloc;
    rwaInstance *found;
    rwaStreamVoiceEntry *entries;
    RwUInt8    *silence;
    RwUInt32    i;

    if (!sub_246FD0(obj, parent, params, NULL, NULL))
    {
        return NULL;
    }

    state->objInterface = sub_243FF0(sub_243F40(unk_3EDEFC), obj->inst.def, params->unk14, params->unk18);
    track = params->track;
    state->entrySize = track->unk20;
    state->item = NULL;
    state->noEntries = params->noEntries;
    state->allocator = *params->allocator;
    state->flags = 0;
    state->filled = 0;
    state->lastPosition = 0;
    state->lastEntry = 0;
    state->done = params->done;
    state->doneData = params->doneData;
    state->refill = state->noEntries * 2;
    state->written = 0;
    entries = (rwaStreamVoiceEntry *)state->allocator.alloc(state->entrySize
                                                            + state->noEntries * sizeof(rwaStreamVoiceEntry),
                                                            state->allocator.data);
    state->entries = entries;
    if (!entries)
    {
        sub_247120(obj, NULL, NULL);
        return NULL;
    }

    silence = (RwUInt8 *)&entries[state->noEntries];
    state->silence.flags = 0;
    state->silence.unk04 = silence;
    state->silence.unk08 = state->entrySize;
    state->silence.callback = NULL;
    state->silence.position = NULL;
    memset(silence, 0, state->entrySize);
    for (i = 0; i < state->noEntries; i++)
    {
        state->entries[i].position.value = 0;
        state->entries[i].position.type = 3;
        state->entries[i].position.pos = 0;
        state->entries[i].position.unit = 2;
        state->entries[i].frames = 0;
    }
    state->position.unit = 2;
    state->position.value = 0;
    state->position.type = 3;
    state->position.pos = 0;

    {
        RwaWaveFormat format;

        format = *(RwaWaveFormat *)track->format;
        format.length = state->entrySize * state->noEntries;
        format.unk19 = 1;
        state->noChannels = format.noChannels;
        state->totalFrames = sub_2433C0(&format, format.length);
        state->entryFrames = sub_2433C0(&format, state->entrySize);
        if (!sub_24DA70(parent, &format, &format, params->mono, &state->wave))
        {
            state->allocator.free(state->entries, state->allocator.data);
            sub_247120(obj, NULL, NULL);
            return NULL;
        }
    }

    found = _rwaObjFindFixed(sub_23DCA0(NULL, unk_3EDF6C, NULL));
    alloc.data = b;
    alloc.func = a;
    alloc.state = state;
    if (!RwaStreamCreate_2(parent, NULL, found, sub_2FDB10, &alloc))
    {
        sub_24DAA0(&state->wave);
        state->allocator.free(state->entries, state->allocator.data);
        sub_247120(obj, NULL, NULL);
        return NULL;
    }

    sub_24F410(&state->voice, &state->wave);
    sub_24F300(&state->voice, TRUE);
    {
        rwaI3DL2Listener settings;

        settings.room = -10000;
        settings.roomHF = 0;
        settings.roomRolloffFactor = 10.0f;
        settings.decayTime = 1.49f;
        settings.decayHFRatio = 0.83f;
        settings.reflections = -2602;
        settings.reflectionsDelay = 0.007f;
        settings.reverb = 200;
        settings.reverbDelay = 0.011f;
        settings.diffusion = 100.0f;
        settings.density = 100.0f;
        settings.hfReference = 5000.0f;
        sub_24F040(&state->voice, &settings);
    }

    state->voice.inst.parent = &obj->inst;
    if (state->voice.inst.subObjLink.next)
    {
        state->voice.inst.subObjLink.prev->next = state->voice.inst.subObjLink.next;
        state->voice.inst.subObjLink.next->prev = state->voice.inst.subObjLink.prev;
    }
    state->voice.inst.subObjLink.next = obj->inst.subObjs.next;
    state->voice.inst.subObjLink.prev = &obj->inst.subObjs;
    obj->inst.subObjs.next->prev = &state->voice.inst.subObjLink;
    obj->inst.subObjs.next = &state->voice.inst.subObjLink;

    sub_247290(obj, obj->unk28, 0, 1);
    RwaStreamNodeCreationComplete(obj);

    return obj;
}

/* Starts or stops the voice, from the start (rewind) or where it stopped. */
// match: _sub_2FDF80 @ 0x002FDF80
// sp-match: _sub_2FDF80 @ 0x00218240
static void
sub_2FDF80(rwaDecoder *obj, RwBool play, RwBool rewind)
{
    rwaStreamVoiceState *state = (rwaStreamVoiceState *)obj->inst.state;

    if (rewind)
    {
        state->lastEntry = 0;
        state->lastPosition = 0;
    }
    else if (play)
    {
        sub_24F270(&state->voice, state->lastPosition);
    }
    else
    {
        state->lastPosition = sub_24F2F0(&state->voice);
    }
    sub_24F200(&state->voice, play);
}

// match: _sub_2FDFE0 @ 0x002FDFE0
// sp-match: _sub_2FDFE0 @ 0x002182A0
static rwaDecoder *
sub_2FDFE0(rwaDecoder *obj)
{
    sub_23F0D0(&obj->inst, TRUE);

    return obj;
}

/* The default creation parameters. */
// match: _sub_2FE000 @ 0x002FE000
// sp-match: _sub_2FE000 @ 0x002182C0
static rwaDecoder *
sub_2FE000(rwaDecoder *obj, rwaStreamVoiceParams *params)
{
    RwaStreamNodeGetParams(obj, params);
    params->track = NULL;
    params->done = NULL;
    params->doneData = NULL;
    params->unk04 = 0;
    params->mono = FALSE;
    params->allocator = &off_42FB3C;
    params->unk00 = 1;
    params->noEntries = 2;

    return obj;
}

// match: _sub_2FE040 @ 0x002FE040
// sp-match: _sub_2FE040 @ 0x00218300
void
sub_2FE040(rwaDecoder *obj, RwUInt32 rate)
{
    sub_24F1A0(&((rwaStreamVoiceState *)obj->inst.state)->voice, (RwReal)rate);
}

// match: _sub_2FE070 @ 0x002FE070
// sp-match: _sub_2FE070 @ 0x00218330
RwUInt32
sub_2FE070(rwaDecoder *obj)
{
    rwaStreamVoiceState *state = (rwaStreamVoiceState *)obj->inst.state;

    return (RwUInt32)sub_24F1C0(&state->voice);
}

/* Sets one channel's level (both for mono), keeping the other: the voice's
 * volume is the louder and its pan their difference over it. */
// match: _sub_2FE090 @ 0x002FE090
// sp-match: _sub_2FE090 @ 0x00218350
void
sub_2FE090(rwaDecoder *obj, const rwaChannelLevel *value)
{
    rwaStreamVoiceState *state = (rwaStreamVoiceState *)obj->inst.state;
    rwaXboxVoice *voice;
    RwReal      pan;
    RwReal      volume;
    RwReal      left;
    RwReal      right;
    RwReal      inv;

    if (value->index >= 2)
    {
        return;
    }
    if (state->noChannels == 2 && value->index != value->channel)
    {
        return;
    }

    voice = &state->voice;
    pan = sub_24F810(voice);
    volume = sub_24F1F0(voice);
    if (pan >= 0.0f)
    {
        left = (1.0f - pan) * volume;
        right = volume;
    }
    else
    {
        right = (pan + 1.0f) * volume;
        left = volume;
    }
    if ((state->noChannels == 1 ? value->index : value->channel) == 0)
    {
        left = value->level;
    }
    else
    {
        right = value->level;
    }
    if (left > right)
    {
        inv = (left > 0.00001f && left != 0.0f) ? 1.0f / left : 0.0f;
        volume = left;
    }
    else
    {
        inv = (right > 0.00001f && right != 0.0f) ? 1.0f / right : 0.0f;
        volume = right;
    }
    sub_24F7F0(voice, right * inv - left * inv);
    sub_24F1D0(voice, volume);
}

// match: _sub_2FE1D0 @ 0x002FE1D0
// sp-match: _sub_2FE1D0 @ 0x00218490
rwaStreamPosition *
sub_2FE1D0(rwaDecoder *obj)
{
    return &((rwaStreamVoiceState *)obj->inst.state)->position;
}

// match: _sub_2FE1E0 @ 0x002FE1E0
// sp-match: _sub_2FE1E0 @ 0x002184A0
static void
sub_2FE1E0(rwaStreamVoiceState *state)
{
    state->filled = 0;
    state->lastPosition = 0;
    state->lastEntry = 0;
    state->refill = state->noEntries * 2;
}

// match: _sub_2FE210 @ 0x002FE210
// sp-match: _sub_2FE210 @ 0x002184D0
rwaDecoder *
sub_2FE210(rwaDecoder *obj, const void *param, const RwUInt32 *value)
{
    sub_2FE040(obj, *value);
    return obj;
}

// match: _sub_2FE230 @ 0x002FE230
// sp-match: _sub_2FE230 @ 0x002184F0
rwaDecoder *
sub_2FE230(rwaDecoder *obj, const void *param, RwUInt32 *value)
{
    *value = sub_2FE070(obj);
    return obj;
}

// match: _sub_2FE250 @ 0x002FE250
// sp-match: _sub_2FE250 @ 0x00218510
rwaDecoder *
sub_2FE250(rwaDecoder *obj, const void *param, const rwaChannelLevel *value)
{
    sub_2FE090(obj, value);
    return obj;
}

// match: _sub_2FE270 @ 0x002FE270
// sp-match: _sub_2FE270 @ 0x00218530
rwaDecoder *
sub_2FE270(rwaDecoder *obj, const void *param, rwaStreamPosition **value)
{
    *value = sub_2FE1D0(obj);
    return obj;
}

/* The update: follows the voice's position (returning played entries and
 * reporting where it plays), then by mode uploads the next queue item (or
 * silence) into the free entry, or stops. */
// match: _sub_2FE290 @ 0x002FE290
// sp-match: _sub_2FE290 @ 0x00218550
static rwaDecoder *
sub_2FE290(rwaInstance *base)
{
    rwaDecoder *obj = (rwaDecoder *)base;
    rwaDecoder *node = (rwaDecoder *)base;
    rwaStreamVoiceState *state = (rwaStreamVoiceState *)obj->inst.state;
    RwUInt32 entry;
    RwBool wrapped = FALSE;
    entry = state->lastEntry;

    if (sub_24F240(&state->voice))
    {
        RwUInt32 played = 0;
        RwUInt32    pos = sub_24F2F0(&state->voice);
        rwaStreamVoiceEntry *current;
        RwUInt32    offset;
        RwUInt32    index;
        RwUInt32 remaining;
        RwBool      empty;

        entry = pos / state->entryFrames;
        if (entry < state->lastEntry)
        {
            played += state->noEntries;
        }
        played = played + entry - state->lastEntry;
        /* The Xbox release leaves current unassigned on underrun. Its stack
         * slot then still holds the incoming object. Assigning obj explicitly
         * changes register allocation and does not match. The later debug DLL
         * (FinishExecute, 0x10072BAC) adds a clamp and valid fallback entry. */
        if (played <= state->filled)
            current = &state->entries[entry];

        if (current->position.unit == 2)
        {
            offset = pos - state->entryFrames * entry;
        }
        else
        {
            offset = state->entryFrames - 1;
        }
        state->filled -= played;
        state->position.unit = 2;
        state->position.pos = current->position.pos + offset;
        state->position.type = current->position.type;
        state->position.value = current->position.value;

        remaining = played;
        index = entry;
        empty = FALSE;
        if (entry == state->refill && offset >= state->entries[entry].frames - 1)
        {
            wrapped = TRUE;
        }
        while (remaining > 0)
        {
            remaining--;
            if (index == 0)
            {
                index = state->noEntries - 1;
            }
            else
            {
                index--;
            }
            if (index == state->refill)
            {
                wrapped = TRUE;
                break;
            }
            if (!state->entries[index].position.unit)
            {
                empty = TRUE;
            }
        }
        if (wrapped)
        {
            RwInt32 mode = 1;
            sub_247160(node, NULL, &mode);
            if (state->item == &state->silence)
            {
                state->item = NULL;
            }
        }
        else if (empty)
        {
            state->status = 7;
            sub_2FDF80(obj, FALSE, TRUE);
        }
        state->lastEntry = entry;
        state->lastPosition = pos;
    }

    switch (state->mode)
    {
    case 2:
        if (state->status != 6 && state->status != 7)
        {
            if (state->filled == state->noEntries)
            {
                if (!sub_24F240(&state->voice))
                {
                    sub_2FDF80(obj, TRUE, FALSE);
                }
                sub_2470A0(node);
            }
            else
            {
                state->status = 4;
            }
        }
        /* fall through */
    case 3:
        if (state->status != 4)
        {
            if (state->status == 7 && state->filled == state->noEntries)
            {
                if (state->mode == 3)
                {
                    state->status = 4;
                }
                else
                {
                    state->status = 6;
                    sub_2FDF80(obj, TRUE, TRUE);
                }
            }
        }
        else
        {
            if (sub_24F240(&state->voice))
            {
                sub_2FDF80(obj, FALSE, FALSE);
            }
            if (state->mode == 3 && state->filled == state->noEntries && !sub_24F240(&state->voice))
            {
                sub_2470A0(node);
            }
        }

        if (state->flags & 1)
        {
            if (!sub_242570(&state->wave) && state->item)
            {
                if (state->item->flags & 8)
                {
                    state->refill = state->written;
                }
                state->filled++;
                if (state->item->callback)
                {
                    state->item->callback->func(state->item, state->item->callback->data);
                }
                state->item = NULL;
            }
            state->flags &= ~1;
        }
        if (!(state->flags & 1) && state->filled < state->noEntries)
        {
            if (!state->item)
            {
                if (state->refill < state->noEntries)
                {
                    state->item = &state->silence;
                }
                else
                {
                    state->item = sub_247200(&state->reader);
                    if (state->item)
                    {
                        if (state->item->flags == 0x10)
                        {
                            if (state->written == state->noEntries * 2)
                            {
                                RwInt32     mode = 1;

                                sub_247160(node, NULL, &mode);
                                sub_2FE1E0(state);
                            }
                            if (state->item->callback)
                            {
                                state->item->callback->func(state->item, state->item->callback->data);
                            }
                        }
                        else
                        {
                            state->item->position->unit &= 3;
                        }
                    }
                    else if (state->status != 4)
                    {
                        state->item = &state->silence;
                    }
                }
            }
            if (state->item)
            {
                RwUInt32    index = state->filled + entry;

                if (index >= state->noEntries)
                {
                    index -= state->noEntries;
                }
                if (sub_242810(&state->wave, state->entrySize * index, state->item->unk04, state->entrySize))
                {
                    state->entries[index].position = *state->item->position;
                    state->entries[index].frames = sub_2433C0(&state->wave.format, state->item->unk08);
                    if (state->item != &state->silence)
                    {
                        state->silence.position = &state->entries[index].position;
                    }
                    else
                    {
                        state->entries[index].position.unit = 0;
                    }
                    state->written = index;
                    state->flags |= 1;
                }
            }
        }
        break;
    case 1:
        if (state->status == 8 && sub_24F240(&state->voice))
        {
            sub_2FDF80(obj, FALSE, FALSE);
            if (wrapped)
            {
                sub_2FE1E0(state);
            }
        }
        sub_2470A0(node);
        if (state->done)
        {
            state->done(node, state->doneData);
        }
        break;
    }
    sub_23F140(base, TRUE);

    return (rwaDecoder *)base;
}

/* Resets the entries (flush: returns the item being uploaded, stops the
 * voice and forgets what played). */
// match: _sub_2FE780 @ 0x002FE780
// sp-match: _sub_2FE780 @ 0x00218A40
void
sub_2FE780(rwaDecoder *obj, RwBool flush)
{
    rwaStreamVoiceState *state = (rwaStreamVoiceState *)obj->inst.state;

    state->refill = state->noEntries * 2;
    if (!flush)
    {
        return;
    }
    if (state->item)
    {
        if (state->item->callback)
        {
            state->item->callback->func(state->item, state->item->callback->data);
        }
        state->item = NULL;
    }
    if (sub_24F240(&state->voice))
    {
        sub_2FDF80(obj, FALSE, TRUE);
        state->status = 7;
    }
    sub_2FE1E0(state);
}

// match: _sub_2FE800 @ 0x002FE800
// sp-match: _sub_2FE800 @ 0x00218AC0
rwaDecoder *
sub_2FE800(rwaDecoder *obj, const void *param, const RwBool *value)
{
    sub_2FE780(obj, *value);
    return obj;
}

// match: _sub_2FE820 @ 0x002FE820
// sp-match: _sub_2FE820 @ 0x00218AE0
static void
sub_2FE820(rwaDecoder *obj, void *a, void *b)
{
    rwaStreamVoiceState *state = (rwaStreamVoiceState *)obj->inst.state;
    rwaStreamVoiceAlloc alloc;

    sub_2FE780(obj, TRUE);
    if (sub_24F7E0(&state->voice))
    {
        sub_2FDF80(obj, FALSE, TRUE);
    }
    sub_24F410(&state->voice, NULL);
    alloc.data = b;
    alloc.func = a;
    alloc.state = state;
    DSPHandle_Stop(&state->voice.inst, sub_2FDB70, &alloc);
    sub_24DAA0(&state->wave);
    state->allocator.free(state->entries, state->allocator.data);
    sub_243B80(state->objInterface);
    sub_247120(obj, a, b);
}

// match: _sub_2FE8C0 @ 0x002FE8C0
// sp-match: _sub_2FE8C0 @ 0x00218B80
static void
sub_2FE8C0(rwaObjDef *def)
{
    RwaObjDefAssignID(def, &unk_41AB64, NULL);

    def->flags = sizeof(rwaStreamVoiceState);
    rwaObjDefSetStateAlignment(def, rwaPow2(0x28));

    def->create = (RwBool (*)(rwaInstance *, rwaInstance *, void *, void *, void *))sub_2FDBD0;
    def->unlink = (void (*)(rwaInstance *, void *, void *))sub_2FE820;
    def->unk2C = (rwaInstance *(*)(rwaInstance *))sub_2FDFE0;
    def->unk30 = (rwaInstance *(*)(rwaInstance *))sub_2FE290;
    def->query = (void (*)(void *, void *))sub_2FE000;
    def->paramsSize = sizeof(rwaStreamVoiceParams);
    def->unk54 = unk_438B98;
}

// match: _sub_2FEB10 @ 0x002FEB10
// sp-match: _sub_2FEB10 @ 0x00218DD0
rwaObjDef *
sub_2FEB10(void)
{
    rwaObjDef  *def = sub_23DFB0(sub_23DCA0(NULL, unk_3EDF5C, NULL), 0xC, &unk_512658, unk_512638, unk_512650,
                                 rwaMEMHINTDUR_EVENT | rwaID_80E);

    if (!def)
    {
        return NULL;
    }

    sub_2FE8C0(def);

    if (!_rwaObjDefSetupParams(def, off_438BB0, 5, off_438C28, 4))
    {
        sub_23DB90(def);

        return NULL;
    }

    sub_23D740(def, sub_243F40(unk_3ED964));

    return def;
}

/* The voices it mutes: unmutes the old ones and takes the new list. */
// match: _sub_2FEB90 @ 0x002FEB90
// sp-match: _sub_2FEB90 @ 0x00219380
void *
sub_2FEB90(void *obj, const void *param, const rwaHandleList *value)
{
    RwUInt32    i;

    if (dword_5126B4)
    {
        for (i = 0; i < dword_5126B8; i++)
        {
            RwaObjHandleSetParamUInt8(dword_5126B4[i], 6, 1, 0);
        }
    }
    if (value)
    {
        dword_5126B4 = value->handles;
        dword_5126B8 = value->count;
    }
    else
    {
        dword_5126B4 = NULL;
        dword_5126B8 = 0;
    }

    return obj;
}

/* The first of them not muted (0: all are). */
// match: _sub_2FEC00 @ 0x002FEC00
// sp-match: _sub_2FEC00 @ 0x002193F0
void *
sub_2FEC00(void *obj, const void *param, RwaObjHandle **value)
{
    RwUInt32    i;

    for (i = 0; i < dword_5126B8; i++)
    {
        if (!sub_23F960(dword_5126B4[i], 6, 2, 0))
        {
            *value = dword_5126B4[i];
            return obj;
        }
    }
    *value = NULL;

    return obj;
}
