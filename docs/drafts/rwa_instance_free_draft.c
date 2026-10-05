extern RwUInt32 sub_23F300(rwaObjDef *def, RwUInt32 flags, RwUInt32 *stateOffset);
extern void sub_2437A0(void *freeList, void *entry);
extern void sub_2444A0(void *pool, void *entry);
extern void sub_2421B0(void *entry);

// match: _sub_23D8B0 @ 0x0023D8B0
void
sub_23D8B0(rwaInstance *input, void (*release)(void *, void *), void *data)
{
    rwaInstance *obj = input;
    rwaObjDef *def = obj->def;
    void *memory = obj;

    if (obj->flags & 8)
    {
        memory = ((void **)obj)[-1];
    }
    else if (obj->flags & 0x10)
    {
        RwUInt32 size = sub_23F300(def, obj->flags & 7, (RwUInt32 *)&input);
        memory = *(void **)((RwUInt8 *)obj + size);
    }

    if (def->instances && (!release || !(obj->flags & 0x20)))
    {
        if (def->flags0C & 0x40)
        {
            sub_2437A0(def->instances, memory);
        }
        else if (def->flags0C & 0x80)
        {
            sub_2444A0(def->instances, memory);
        }
        else
        {
            sub_2421B0(memory);
        }
    }
    else if (release)
    {
        release(memory, data);
    }
}
