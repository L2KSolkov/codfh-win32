/* The node's status from its mode and whether its source ran dry. */
// match: _sub_24CC80 @ 0x0024CC80
static rwaSplitter *
sub_24CC80(rwaSplitter *obj)
{
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
                    break;
                }
                if (mode == 1)
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


/* A track's read: its next item, reading one from the source when no
 * track has it yet. */
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
    if (!(obj->state.masks[*index] & (1 << track)))
    {
        return NULL;
    }

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


// match: _sub_24CFF0 @ 0x0024CFF0
static rwaSplitter *
sub_24CFF0(rwaSplitter *obj, rwaInstance *parent, rwaSplitterParams *params, void *a, void *b)
{
    rwaSplitterState *state = &obj->state;
    RwUInt32    noTracks;
    RwUInt32    i;
    RwUInt32    j;

    if (!sub_246FD0((rwaDecoder *)obj, parent, (rwaStreamNodeParams *)params, a, b))
    {
        return NULL;
    }

    obj->state.objInterface = sub_243FF0(sub_243F40(unk_3ED964), obj->inst.def, 0, 0);
    noTracks = params->info->noTracks;
    state->allocator = params->allocator;
    state->info = *params->info;
    state->noBuffers = params->noBuffers;
    state->masks = (RwUInt32 *)state->allocator->alloc(
        noTracks * (state->noBuffers * sizeof(rwaQueueItem) + 24) + state->noBuffers * 24,
        state->allocator->data);
    if (!state->masks)
    {
        return NULL;
    }

    state->items = (rwaQueueItem **)(state->masks + state->noBuffers);
    state->readIndex = (RwUInt32 *)(state->items + state->noBuffers);
    state->writeIndex = state->readIndex + noTracks;
    state->trackItems = (rwaQueueItem *)(state->writeIndex + noTracks);
    state->tracks = (rwaSplitterTrack *)((rwaQueueCallback *)(state->trackItems
                                                              + state->noBuffers * noTracks)
                                         + noTracks);
    state->callbacks = (rwaQueueCallback *)(state->trackItems + state->noBuffers * noTracks);
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
        state->tracks[i].index = i;
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

