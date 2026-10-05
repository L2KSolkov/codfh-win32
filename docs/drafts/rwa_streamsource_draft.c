// match: _sub_241230 @ 0x00241230
void
sub_241230(rwaDecoderState *state, RwBool failed, rwaDecoder *obj)
{
    RwUInt32            count;
    rwaQueueItem       *items;
    rwaStreamPosition  *positions;
    RwUInt32            i;

    if (failed)
    {
        obj->status = 1;
    }
    else
    {
        items = obj->state.items;
        positions = obj->state.positions;
        count = obj->state.noItems;

        obj->state.callback.func = sub_240E20;
        obj->state.callback.data = obj;

        for (i = 0; i < count; i++)
        {
            items[i].flags = 0;
            items[i].unk04 = obj;
            items[i].callback = &obj->state.callback;
            items[i].unk08 = state->info->unk20;
            items[i].position = &positions[i];
            positions[i].type = 3;
            positions[i].unit = 2;
        }

        sub_2472E0(&obj->state.queue, items, count);
    }

    _RwaStreamNodeCreationComplete(obj);
}

