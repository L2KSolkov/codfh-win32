/*
 * codfh-match: RenderWare Audio's stream splitter (0x24CC50-0x24D4C0; named
 * by the database's RwaStreamRendererInterfaceRegister): a stream node that
 * reads items of interleaved tracks from its source and hands each track a
 * track item into the same data; an item goes back to the source once every
 * track has played it. Then its definition's set-up and registration, and
 * the stream renderer interface.
 */
#include "rwa.h"
#include "rwaint.h"



extern void *sub_243F40(const void *uuid);
extern void *sub_243FF0(void *objInterface, rwaObjDef *def, RwUInt32 a, RwUInt32 b);
extern rwaDecoder *sub_246FD0(rwaDecoder *obj, rwaInstance *parent, rwaStreamNodeParams *params,
                              void *a, void *b);
extern void RwaStreamNodeCreationComplete(rwaDecoder *obj);
extern rwaDecoder *RwaStreamNodeGetParams(rwaDecoder *obj, rwaStreamNodeParams *params);
extern void sub_247120(rwaDecoder *obj, void *a, void *b);
extern void sub_247160(rwaDecoder *obj, void *data, RwInt32 *mode);
extern rwaDecoder *sub_2471D0(rwaDecoder *obj, void *data, rwaStreamConnect *connect);
extern rwaDecoder *sub_2471F0(rwaDecoder *obj, void *data, rwaStreamConnect *connect);
extern rwaQueueItem *sub_247200(rwaStreamReader *reader);
extern RwInt32 sub_247360(rwaDecoder *obj);
extern rwaObjDef *RwaObjDefAssignID(rwaObjDef *def, const void *uuid, const void *textID);
extern rwaObjDef *sub_23DFB0(void *parent, RwInt32 a, void *b, void *c, void *d, RwUInt32 hint);
extern RwBool _rwaObjDefSetupParams(rwaObjDef *def, void *sets, RwInt32 noSets, void *gets, RwInt32 noGets);
extern RwBool sub_23DB90(rwaObjDef *def);
extern void *sub_243E20(void *iface);
extern void RwaWaveDictAssignID(void *iface, const void *uuid, const void *textID);
extern void sub_243CD0(void *iface, void *sets, RwInt32 noSets, void *gets, RwInt32 noGets);
extern RwBool sub_243EA0(void *iface);

extern rwaObjDef *dword_516C60;
extern rwaObjDef unk_507BA8;        /* the splitter definition */
extern RwUInt8 unk_507C04[];
extern RwUInt8 unk_507C0C[];
extern RwUInt8 dword_507C4C[];      /* the stream renderer interface */
extern const RwUInt8 unk_3ED964[];  /* the stream node interface */
extern const RwUInt8 unk_3EDEBC[];  /* the splitter */
extern const RwUInt8 unk_3EDEFC[];  /* the stream renderer interface */
extern rwaNodeAllocator off_42FB3C; /* the default memory functions */

extern rwaSplitter *sub_24CC80(rwaSplitter *obj);
extern rwaQueueItem *sub_24CD50(rwaSplitter *obj, RwUInt32 track);
extern rwaSplitter *sub_24CFF0(rwaSplitter *obj, rwaInstance *parent, rwaSplitterParams *params,
                               void *a, void *b);

// Its data (PLAN M5): literals, constants and tables where the image has them.

// What its data definitions name.
extern void TkFSManagerGetValue(void);
rwaSplitter *sub_24CF70(rwaSplitter *obj, const void *param, const RwInt32 *value);
rwaSplitter *sub_24CF90(rwaSplitter *obj, const void *param, rwaStreamConnect *value);
rwaSplitter *sub_24CFB0(rwaSplitter *obj, const void *param, RwInt32 *value);
rwaSplitter *sub_24CFD0(rwaSplitter *obj, const void *param, rwaStreamConnect *value);
extern RwUInt8 unk_3ED4EC[];
extern RwUInt8 unk_3ED55C[];
extern RwUInt8 unk_3ED56C[];
extern RwUInt8 unk_3ED974[];
extern RwUInt8 unk_3ED984[];
extern RwUInt8 unk_3ED994[];
extern RwUInt8 unk_3ED9A4[];
extern RwUInt8 unk_3ED9B4[];
extern RwUInt8 unk_3EDEDC[];
extern RwUInt8 unk_3EDEEC[];
extern RwUInt8 unk_3EDF0C[];
extern RwUInt8 unk_3EDF1C[];
extern RwUInt8 unk_3EDF2C[];
extern RwUInt8 unk_3EDF3C[];
// Its data definitions (PLAN M5), in the image's address order.
// 0x0042FF88
void *off_42FF88[18] =
{
    (void *)&unk_3ED974,
    0,
    0,
    (void *)&unk_3ED4EC,
    (void *)0x1,
    (void *)sub_24CF70,
    (void *)&unk_3ED984,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)sub_24CF90,
    (void *)&unk_3ED9B4,
    0,
    0,
    (void *)&unk_3ED55C,
    (void *)0x1,
    (void *)TkFSManagerGetValue,
};
// 0x0042FFD0
void *off_42FFD0[48] =
{
    (void *)&unk_3ED994,
    0,
    0,
    (void *)&unk_3ED4EC,
    (void *)0x1,
    (void *)sub_24CFB0,
    (void *)&unk_3ED9A4,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)sub_24CFD0,
    (void *)&unk_3ED974,
    0,
    0,
    (void *)&unk_3ED4EC,
    (void *)0x1,
    (void *)&unk_3ED984,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)&unk_3ED9B4,
    0,
    0,
    (void *)&unk_3ED55C,
    (void *)0x1,
    0,
    (void *)&unk_3EDEDC,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)&unk_3EDEEC,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)&unk_3ED994,
    0,
    0,
    (void *)&unk_3ED4EC,
    (void *)0x1,
    (void *)&unk_3ED9A4,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
};
// 0x00430090
void *off_430090[26] =
{
    (void *)&unk_3EDF0C,
    0,
    0,
    (void *)&unk_3ED4EC,
    (void *)0x1,
    (void *)&unk_3EDF2C,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)&unk_3ED974,
    0,
    0,
    (void *)&unk_3ED4EC,
    (void *)0x1,
    (void *)&unk_3ED984,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)&unk_3ED9B4,
    0,
    0,
    (void *)&unk_3ED55C,
    (void *)0x1,
    0,
};
// 0x004300F8
void *off_4300F8[106] =
{
    (void *)&unk_3EDF1C,
    0,
    0,
    (void *)&unk_3ED4EC,
    (void *)0x1,
    (void *)&unk_3EDF3C,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)&unk_3ED994,
    0,
    0,
    (void *)&unk_3ED4EC,
    (void *)0x1,
    (void *)&unk_3ED9A4,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)0x206C6C41,
    (void *)0x65727473,
    (void *)0x62206D61,
    (void *)0x6B636F6C,
    (void *)0x69772073,
    (void *)0x62206C6C,
    (void *)0x61702065,
    (void *)0x64656464,
    (void *)0x20796220,
    (void *)0x62206425,
    (void *)0x73657479,
    (void *)0x726F6620,
    (void *)0x63657320,
    (void *)0x20726F74,
    (void *)0x67696C61,
    (void *)0x6E656D6E,
    (void *)0x74,
    (void *)0x616E6E55,
    (void *)0x64656D,
    0,
    (void *)0x73627553,
    (void *)0x61657274,
    (void *)0x7325206D,
    (void *)0x63617020,
    (void *)0x2074656B,
    (void *)0x6E207369,
    (void *)0x7420746F,
    (void *)0x73206568,
    (void *)0x20656D61,
    (void *)0x61727564,
    (void *)0x6E6F6974,
    (void *)0x20736120,
    (void *)0x206C6C61,
    (void *)0x6568746F,
    (void *)0x75732072,
    (void *)0x72747362,
    (void *)0x206D6165,
    (void *)0x6B636170,
    (void *)0x737465,
    (void *)0x616E6E55,
    (void *)0x64656D,
    (void *)0x616E6E55,
    (void *)0x64656D,
    (void *)0x616E6E55,
    (void *)0x64656D,
    (void *)0x253A7325,
    (void *)0x73253A73,
    (void *)0x6C697720,
    (void *)0x6562206C,
    (void *)0x64617020,
    (void *)0x20646564,
    (void *)0x25207962,
    (void *)0x79622064,
    (void *)0x2E736574,
    0,
    (void *)0x616E6E55,
    (void *)0x64656D,
    (void *)0x616E6E55,
    (void *)0x64656D,
    (void *)0x616E6E55,
    (void *)0x64656D,
    (void *)0x253A7325,
    (void *)0x73253A73,
    (void *)0x6C697720,
    (void *)0x6562206C,
    (void *)0x64617020,
    (void *)0x20646564,
    (void *)0x25207962,
    (void *)0x79622064,
    (void *)0x2E736574,
    0,
    (void *)0x616E6E55,
    (void *)0x64656D,
    (void *)0x65727453,
    (void *)0x25206D61,
    (void *)0x61682073,
    (void *)0x65622073,
    (void *)0x70206E65,
    (void *)0x65646461,
    (void *)0x79622064,
    (void *)0x74206120,
    (void *)0x6C61746F,
    (void *)0x20666F20,
    (void *)0x62206425,
    (void *)0x73657479,
    (void *)0x2E,
};
// 0x00507BA8
rwaObjDef unk_507BA8;
// 0x00507C04
RwUInt8 unk_507C04[8];
// 0x00507C0C
RwUInt8 unk_507C0C[64];
// 0x00507C4C
RwUInt8 dword_507C4C[44];
// End of its data definitions.

// match: _off_42FF88 @ 0x0042FF88


// match: _off_42FFD0 @ 0x0042FFD0


// match: _off_430090 @ 0x00430090


// match: _off_4300F8 @ 0x004300F8

// match: _sub_24CC40 @ 0x0024CC40

RwBool
sub_24CC40(void)
{
    return sub_23DB90(&unk_507BA8);
}

// match: _sub_24CC50 @ 0x0024CC50
static void
sub_24CC50(rwaSplitter *obj, void *a, void *b)
{
    obj->state.allocator->free(obj->state.masks, obj->state.allocator->data);
    sub_247120((rwaDecoder *)obj, a, b);
}

/* Source shape: rwad.dll _RwaStreamFanOutStartExecute, 0x10067D61.
 * Keep the incoming object and typed local separate. */
// match: _sub_24CC80 @ 0x0024CC80
rwaSplitter *
sub_24CC80(rwaSplitter *arg)
{
    rwaSplitter *obj = arg;
    if ((RwInt32)obj->state.node.numCreated > 0)
    {
        RwInt32     mode = obj->state.node.mode;

        switch (obj->state.node.status)
        {
            case 3:
                if (mode == 3 || mode == 2)
                {
                    obj->state.node.status = 4;
                }
                break;
            case 4:
            case 5:
            case 6:
                if (obj->state.starved)
                {
                    obj->state.node.status = 7;
                }
                if (mode == 3)
                {
                    obj->state.node.status = 4;
                }
                else if (mode == 1)
                {
                    obj->state.node.status = 3;
                }
                break;
            case 7:
                if (!obj->state.starved && mode == 2)
                {
                    obj->state.node.status = 6;
                }
                if (mode == 3)
                {
                    obj->state.node.status = 4;
                }
                if (mode == 1)
                {
                    obj->state.node.status = 3;
                }
                break;
            case 8:
                obj->state.node.status = 3;
                break;
        }
    }

    return obj;
}



/* The default creation parameters. */
// match: _sub_24CD20 @ 0x0024CD20
static void *
sub_24CD20(rwaSplitter *obj, rwaSplitterParams *params)
{
    RwaStreamNodeGetParams((rwaDecoder *)obj, (rwaStreamNodeParams *)params);
    params->unk00 = 1;
    params->unk04 = 1;
    params->allocator = &off_42FB3C;

    return obj;
}

// match: _sub_24CD50 @ 0x0024CD50
rwaQueueItem *
sub_24CD50(rwaSplitter *obj, RwUInt32 track)
{
    RwUInt32   *index;
    rwaQueueItem *item;

    if (obj->state.node.status == 3)
    {
        return NULL;
    }

    index = &obj->state.readIndex[track];
    if (!obj->state.items[*index])
    {
        obj->state.items[*index] = sub_247200((rwaStreamReader *)&obj->state.node.next);
        if (obj->state.items[*index])
        {
            obj->state.masks[*index] = 0xFFFFFFFF;
            obj->state.starved = FALSE;
        }
        else
        {
            obj->state.starved = TRUE;
            return NULL;
        }
    }
    if (obj->state.masks[*index] & (1 << track))
    {
        item = &obj->state.trackItems[*index + track * obj->state.noBuffers];
        item->flags = obj->state.items[*index]->flags;
        item->position = obj->state.items[*index]->position;
        item->unk08 = obj->state.info.tracks[track].unk20;
        item->unk04 = obj->state.items[*index]->unk04 + obj->state.info.tracks[track].unk24;
        if (++*index >= obj->state.noBuffers)
        {
            *index = 0;
        }

        return item;
    }
    return NULL;
}



// match: _sub_24CE70 @ 0x0024CE70
void
sub_24CE70(rwaSplitter *obj, RwInt32 mode)
{
    RwInt32     value = mode;

    sub_247160((rwaDecoder *)obj, NULL, &value);
}

// match: _sub_24CE90 @ 0x0024CE90
void
sub_24CE90(rwaSplitter *obj, rwaStreamConnect *connect)
{
    sub_2471D0((rwaDecoder *)obj, NULL, connect);
    connect->reader->data = (rwaDecoder *)connect->unk00;
    connect->reader->read = (rwaQueueItem *(*)(rwaDecoder *))sub_24CD50;
}

// match: _sub_24CEC0 @ 0x0024CEC0
RwInt32
sub_24CEC0(rwaSplitter *obj)
{
    return sub_247360((rwaDecoder *)obj);
}

// match: _sub_24CED0 @ 0x0024CED0
void
sub_24CED0(rwaSplitter *obj, rwaStreamConnect *connect)
{
    sub_2471F0((rwaDecoder *)obj, NULL, connect);
}

/* A track item played: the source's item goes back once every track has. */
// match: _sub_24CEF0 @ 0x0024CEF0
void
sub_24CEF0(rwaQueueItem *item, rwaSplitterTrack *track)
{
    RwUInt32    i = track->index;
    rwaSplitterState *state = track->owner;
    RwUInt32   *index = &state->writeIndex[i];

    state->masks[*index] &= ~(1 << i);
    if (!(state->masks[*index] & ((1 << state->info.noTracks) - 1)))
    {
        state->items[*index]->callback->func(state->items[*index],
                                             state->items[*index]->callback->data);
        state->items[*index] = NULL;
    }
    if (++*index >= state->noBuffers)
    {
        *index = 0;
    }
}

// match: _sub_24CF70 @ 0x0024CF70
rwaSplitter *
sub_24CF70(rwaSplitter *obj, const void *param, const RwInt32 *value)
{
    sub_24CE70(obj, *value);
    return obj;
}

// match: _sub_24CF90 @ 0x0024CF90
rwaSplitter *
sub_24CF90(rwaSplitter *obj, const void *param, rwaStreamConnect *value)
{
    sub_24CE90(obj, value);
    return obj;
}

// match: _sub_24CFB0 @ 0x0024CFB0
rwaSplitter *
sub_24CFB0(rwaSplitter *obj, const void *param, RwInt32 *value)
{
    *value = sub_24CEC0(obj);
    return obj;
}

// match: _sub_24CFD0 @ 0x0024CFD0
rwaSplitter *
sub_24CFD0(rwaSplitter *obj, const void *param, rwaStreamConnect *value)
{
    sub_24CED0(obj, value);
    return obj;
}

/* The update: nothing to do (folded by /OPT:ICF into 0x257AF0). */
rwaSplitter *
rwaSplitterUpdate(rwaSplitter *obj)
{
    return obj;
}
/* Local reconstruction helper (no original symbol): typed arguments make
 * VC7 compute the allocation size before loading allocator->data and alloc,
 * as at 0x24D05D-0x24D07C. Defined before its caller: VC7.0 defers a
 * function calling a forceinline defined later to the end of the unit. */
static __forceinline void *
splitAlloc(rwaNodeAllocator *allocator, RwUInt32 size)
{
    return allocator->alloc(size, allocator->data);
}

// match: _sub_24CFF0 @ 0x0024CFF0
rwaSplitter *
sub_24CFF0(rwaSplitter *obj, rwaInstance *parent, rwaSplitterParams *params, void *a, void *b)
{
    rwaSplitterState *state = &obj->state;
    RwUInt32    noTracks;
    RwUInt32    i;
    RwUInt32    j;
    rwaQueueCallback *callbacks;

    if (!sub_246FD0((rwaDecoder *)obj, parent, (rwaStreamNodeParams *)params, a, b))
    {
        return NULL;
    }

    obj->state.objInterface = sub_243FF0(sub_243F40(unk_3ED964), obj->inst.def, 0, 0);
    noTracks = params->info->noTracks;
    state->allocator = params->allocator;
    state->info = *params->info;
    state->noBuffers = params->noBuffers;
    state->masks = (RwUInt32 *)splitAlloc(state->allocator, noTracks * (state->noBuffers * sizeof(rwaQueueItem) + 24) + state->noBuffers * 24);
    if (!state->masks)
    {
        return NULL;
    }

    state->items = (rwaQueueItem **)(state->masks + state->noBuffers);
    state->readIndex = (RwUInt32 *)(state->items + state->noBuffers);
    state->writeIndex = state->readIndex + noTracks;
    state->trackItems = (rwaQueueItem *)(state->writeIndex + noTracks);
    callbacks = (rwaQueueCallback *)(state->trackItems + state->noBuffers * noTracks);
    state->tracks = (rwaSplitterTrack *)(callbacks + noTracks);
    state->callbacks = callbacks;
    for (i = 0; i < state->noBuffers; i++)
    {
        state->items[i] = NULL;
        state->masks[i] = 0;
    }
    for (i = 0; i < params->info->noTracks; i++)
    {
        state->readIndex[i] = 0;
        state->writeIndex[i] = 0;
        state->tracks[i].owner = state;
        /* Evidence: 0x24D124 reloads tracks before the index store at
         * 0x24D12A. This qualified access reproduces its address encoding;
         * it does not establish an original volatile declaration. */
        ((volatile rwaSplitterState *)state)->tracks[i].index = i;
        state->callbacks[i].func = (void (*)(rwaQueueItem *, rwaDecoder *))sub_24CEF0;
        state->callbacks[i].data = (rwaDecoder *)&state->tracks[i];
        for (j = 0; j < state->noBuffers; j++)
        {
            state->trackItems[state->noBuffers * i + j].callback = &state->callbacks[i];
        }
    }
    state->starved = FALSE;
    RwaStreamNodeCreationComplete((rwaDecoder *)obj);

    return obj;
}

// match: _sub_24D1B0 @ 0x0024D1B0
static void
sub_24D1B0(rwaObjDef *def)
{
    RwaObjDefAssignID(def, unk_3EDEBC, NULL);

    def->flags = sizeof(rwaSplitterState);
    rwaObjDefSetStateAlignment(def, rwaPow2(0x28));

    def->create = (RwBool (*)(rwaInstance *, rwaInstance *, void *, void *, void *))sub_24CFF0;
    def->unlink = (void (*)(rwaInstance *, void *, void *))sub_24CC50;
    def->unk2C = (rwaInstance *(*)(rwaInstance *))sub_24CC80;
    def->unk30 = (rwaInstance *(*)(rwaInstance *))rwaSplitterUpdate;
    def->query = (void (*)(void *, void *))sub_24CD20;
    def->paramsSize = sizeof(rwaSplitterParams);
}

// match: _sub_24D400 @ 0x0024D400
rwaObjDef *
sub_24D400(void)
{
    rwaObjDef  *def = sub_23DFB0(dword_516C60, 0xC, &unk_507BA8, unk_507C0C, unk_507C04,
                                 rwaMEMHINTDUR_EVENT | rwaID_80E);

    if (!def)
    {
        return NULL;
    }

    sub_24D1B0(def);

    if (!_rwaObjDefSetupParams(def, off_42FF88, 3, off_42FFD0, 2))
    {
        sub_23DB90(def);

        return NULL;
    }

    return def;
}

// match: _RwaStreamRendererInterfaceRegister @ 0x0024D460
void *
RwaStreamRendererInterfaceRegister(void)
{
    if (!sub_243E20(dword_507C4C))
    {
        return NULL;
    }

    RwaWaveDictAssignID(dword_507C4C, unk_3EDEFC, NULL);
    sub_243CD0(dword_507C4C, off_430090, 5, off_4300F8, 4);

    return dword_507C4C;
}

// match: _sub_24D4B0 @ 0x0024D4B0
RwBool
sub_24D4B0(void)
{
    return sub_243EA0(dword_507C4C);
}
