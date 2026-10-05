/*
 * codfh-match: RenderWare Audio's stream nodes (0x246FD0-0x247430): the
 * part every node of a stream container shares (its state from +0x28: the
 * node interface, play mode and status, and the creation callback), the
 * node interface calls, and the play queue's ring of items.
 */
#include "rwa.h"
#include "rwaint.h"

extern void *sub_242170(RwUInt32 size, RwUInt32 hint);
extern void *sub_243F40(const void *uuid);
extern void *sub_243FF0(void *objInterface, rwaObjDef *def, RwUInt32 a, RwUInt32 b);
extern RwInt32 sub_243B80(void *objInterface);
extern void sub_246FC0(void *mem, RwUInt32 unused);
extern RwBool sub_247220(rwaDecoder *obj, rwaObjInterface *iface, RwInt32 type, void *value);
extern RwBool sub_247260(rwaDecoder *obj, rwaObjInterface *iface, RwInt32 type, void *value);

extern const RwUInt8 unk_3ED964[];  /* the stream node interface */

/* Sets up a node's shared state from its creation parameters. */
// match: _sub_246FD0 @ 0x00246FD0
rwaDecoder *
sub_246FD0(rwaDecoder *obj, rwaInstance *parent, rwaStreamNodeParams *params)
{
    rwaStreamNodeState *state = (rwaStreamNodeState *)obj->inst.state;
    RwInt32     value;

    value = params->unk04;
    if (value < 0)
    {
        value = 1;
    }
    state->unk1C = value;
    value = params->unk00;
    if (value < 0)
    {
        value = 1;
    }
    state->unk0C = value;
    state->next = NULL;
    state->unk14 = 0;
    state->unk18 = 0;
    state->numCreated = 0;
    state->callback = params->callback;
    state->mode = 1;
    state->status = 2;
    state->iface = sub_243FF0(sub_243F40(unk_3ED964), obj->inst.def, params->unk14, params->unk18);

    return obj;
}

/* A node has been created: its status from its mode, then the callback. */
// match: _RwaStreamNodeCreationComplete @ 0x00247050
void
RwaStreamNodeCreationComplete(rwaDecoder *obj)
{
    rwaStreamNodeState *state = (rwaStreamNodeState *)obj->inst.state;

    if (state->status != 1)
    {
        switch (state->mode)
        {
        case 1:
            state->status = 3;
            break;
        case 2:
            state->status = 6;
            break;
        case 3:
            state->status = 4;
            break;
        }
        state->numCreated++;
    }

    if (state->callback)
    {
        state->callback->func((rwaQueueItem *)obj, state->callback->data);
    }
}

/* The node's status from its mode, unlinking it from its parent when it
 * plays. */
// match: _sub_2470A0 @ 0x002470A0
void
sub_2470A0(rwaDecoder *obj)
{
    switch (obj->mode)
    {
    case 1:
        if (obj->inst.subObjLink.next)
        {
            obj->inst.subObjLink.prev->next = obj->inst.subObjLink.next;
            obj->inst.subObjLink.next->prev = obj->inst.subObjLink.prev;
            obj->inst.subObjLink.prev = NULL;
            obj->inst.subObjLink.next = NULL;
        }
        obj->status = 3;
        break;
    case 2:
        obj->status = 6;
        break;
    case 3:
        obj->status = 5;
        break;
    }
}

// match: _RwaStreamNodeGetParams @ 0x002470F0
rwaDecoder *
RwaStreamNodeGetParams(rwaDecoder *obj, rwaStreamNodeParams *params)
{
    params->unk00 = (RwUInt32)-1;
    params->unk04 = (RwUInt32)-1;
    params->callback = NULL;
    params->unk08 = 0;
    params->unk0C = 1;
    params->unk14 = 0;
    params->unk18 = 0;
    return obj;
}

// match: _sub_247120 @ 0x00247120
void
sub_247120(rwaDecoder *obj, RwUInt32 unused)
{
    sub_243B80(obj->unk28);
}

// match: _sub_247130 @ 0x00247130
static RwUInt32
sub_247130(void)
{
    return 0;
}

/* The node's status (parameter 0). */
// match: _sub_247140 @ 0x00247140
rwaDecoder *
sub_247140(rwaDecoder *obj, void *data, RwInt32 *status)
{
    *status = ((rwaStreamNodeState *)obj->inst.state)->status;
    return obj;
}

/* Sets the node's play mode, and moves it to the front of its parent's
 * sub-objects. */
// match: _sub_247160 @ 0x00247160
rwaDecoder *
sub_247160(rwaDecoder *obj, void *data, RwInt32 *mode)
{
    RwInt32     value = *mode;
    rwaStreamNodeState *state = (rwaStreamNodeState *)obj->inst.state;

    switch (value)
    {
    case 1:
        if (state->status != 3)
        {
            state->status = 8;
        }
        break;
    case 3:
        if (state->status != 5)
        {
            state->status = 4;
        }
        break;
    }
    state->mode = value;

    if (obj->inst.subObjLink.next)
    {
        obj->inst.subObjLink.prev->next = obj->inst.subObjLink.next;
        obj->inst.subObjLink.next->prev = obj->inst.subObjLink.prev;
    }
    obj->inst.subObjLink.next = obj->inst.parent->subObjs.next;
    obj->inst.subObjLink.prev = &obj->inst.parent->subObjs;
    obj->inst.parent->subObjs.next->prev = &obj->inst.subObjLink;
    obj->inst.parent->subObjs.next = &obj->inst.subObjLink;

    return obj;
}

/* The node's reader: its node, a reader returning nothing and the data. */
// match: _sub_2471D0 @ 0x002471D0
rwaDecoder *
sub_2471D0(rwaDecoder *obj, void *data, rwaStreamConnect *connect)
{
    connect->reader->unk00 = (RwUInt32)obj;
    connect->reader->read = (rwaQueueItem *(*)(rwaDecoder *))sub_247130;
    connect->reader->data = (rwaDecoder *)connect->unk00;
    return obj;
}

// match: _sub_2471F0 @ 0x002471F0
rwaDecoder *
sub_2471F0(rwaDecoder *obj, void *data, rwaStreamConnect *connect)
{
    connect->reader = (rwaStreamReader *)&obj->next;
    return obj;
}

/* Calls a reader. */
// match: _sub_247200 @ 0x00247200
rwaQueueItem *
sub_247200(rwaStreamReader *reader)
{
    return ((rwaQueueItem *(*)(rwaDecoder *, rwaDecoder *))reader->read)((rwaDecoder *)reader->unk00,
                                                                         reader->data);
}

// match: _sub_247220 @ 0x00247220
RwBool
sub_247220(rwaDecoder *obj, rwaObjInterface *iface, RwInt32 type, void *value)
{
    rwaParamFunc *setter = &iface->setters[type];

    RwUInt32 param = setter->param;
    return setter->func((rwaInstance *)obj, param, value);
}

// match: _sub_247250 @ 0x00247250
void
sub_247250(rwaDecoder *obj, rwaObjInterface *iface, RwInt32 type, void *value)
{
    sub_247220(obj, iface, type, value);
}

// match: _sub_247260 @ 0x00247260
RwBool
sub_247260(rwaDecoder *obj, rwaObjInterface *iface, RwInt32 type, void *value)
{
    rwaParamFunc *getter = &iface->getters[type];

    RwUInt32 param = getter->param;
    return getter->func((rwaInstance *)obj, param, value);
}

// match: _sub_247290 @ 0x00247290
void
sub_247290(rwaDecoder *obj, rwaObjInterface *iface, RwInt32 type, ...)
{
    sub_247220(obj, iface, type, (&type) + 1);
}

// match: _RwaObjIntGetParamUInt32 @ 0x002472B0
RwUInt32
RwaObjIntGetParamUInt32(rwaDecoder *obj, rwaObjInterface *iface, RwUInt32 type)
{
    sub_247260(obj, iface, type, &type);
    return type;
}

/* Sets up a play queue over count items. */
// match: _sub_2472E0 @ 0x002472E0
rwaQueue *
sub_2472E0(rwaQueue *queue, rwaQueueItem *items, RwUInt8 size)
{
    queue->count = 0;
    queue->unk02 = 0;
    queue->head = 0;
    queue->size = size;
    queue->items = items;
    return queue;
}

/* The next free item, its flag 8 cleared. */
// match: _sub_247300 @ 0x00247300
rwaQueueItem *
sub_247300(rwaQueue *queue)
{
    rwaQueueItem *item = NULL;
    RwUInt8     count = queue->count;
    RwUInt8     size = queue->size;

    if (count != size)
    {
        RwUInt32    index = queue->head + queue->count;

        if (index >= size)
        {
            index -= size;
        }
        queue->count = count + 1;
        item = &queue->items[index];
    }
    item->flags &= ~8;
    return item;
}

/* Drops the first item. */
// match: _sub_247340 @ 0x00247340
void
sub_247340(rwaQueue *queue)
{
    RwUInt32    head = queue->head + 1;

    if (head >= queue->size)
    {
        head -= queue->size;
    }
    queue->count--;
    queue->head = (RwUInt8)head;
}

// match: _sub_247360 @ 0x00247360
RwInt32
sub_247360(rwaDecoder *obj)
{
    RwInt32     status;

    sub_247140(obj, NULL, &status);
    return status;
}

/* Connects source to node's input index: the source's output, then the
 * node's input. */
// match: _sub_247380 @ 0x00247380
void
sub_247380(rwaDecoder *node, RwUInt32 index, rwaDecoder *source, RwUInt32 d)
{
    rwaStreamConnect connect;

    connect.unk00 = d;
    sub_247260(source, source->unk28, 1, &connect);
    connect.unk00 = index;
    sub_247250(node, node->unk28, 1, &connect);
}

// match: _sub_2473D0 @ 0x002473D0
void *
sub_2473D0(RwUInt32 size, RwUInt32 unused)
{
    return sub_242170(size, rwaMEMHINTDUR_EVENT | rwaID_80E);
}

// match: __rwaStreamSourceCreationParamsInit @ 0x002473E0
rwaStreamSourceParams *
_rwaStreamSourceCreationParamsInit(rwaStreamSourceParams *params)
{
    params->values[0] = (RwUInt32)sub_2473D0;
    params->values[1] = (RwUInt32)sub_246FC0;
    params->values[2] = 0;
    params->callback = NULL;
    params->data = NULL;
    params->values[4] = 0;
    params->values[6] = 0;
    params->values[7] = 0;
    params->values[5] = 0;
    params->values[10] = 0;
    params->values[11] = 0;
    params->values[13] = 0;
    params->values[14] = 0;
    params->values[8] = 0;
    params->values[9] = 0;
    params->values[12] = 0;
    params->values[3] = 0;
    return params;
}
