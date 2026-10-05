// match: _sub_241230 @ 0x00241230
void
sub_241230(rwaDecoderState *state, RwBool failed, rwaDecoder *arg)
{
    rwaDecoder *obj = arg;
    RwUInt32 count;

    rwaStreamPosition  *positions;
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
        arg = (rwaDecoder *)obj->state.items;

        callback = &obj->state.callback;
        callback->func = sub_240E20;
        callback->data = obj;

        for (i = 0; i < count; i++)
        {
            ((rwaQueueItem *)arg)[i].flags = 0;
            ((rwaQueueItem *)arg)[i].unk04 = obj;
            ((rwaQueueItem *)arg)[i].callback = callback;
            ((rwaQueueItem *)arg)[i].unk08 = state->info->unk20;
            ((rwaQueueItem *)arg)[i].position = &positions[i];
            positions[i].type = 3;
            positions[i].unit = 2;
        }

        sub_2472E0(&obj->state.queue, (rwaQueueItem *)arg, count);
    }

    _RwaStreamNodeCreationComplete(obj);
}

