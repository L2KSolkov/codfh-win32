// match: _sub_2442D0 @ 0x002442D0
void *
sub_2442D0(rwaPoolBlock *block, RwUInt32 size, RwUInt32 alignment)
{
    RwUInt32        needed = size + sizeof(rwaPoolChunk);
    rwaPoolChunk   *chunk = block->chunks;

    do
    {
        rwaPoolChunk   *next = chunk->next;

        if ((RwUInt32)next - chunk->size - (RwUInt32)chunk - sizeof(rwaPoolChunk) >= needed)
        {
            RwUInt32        used = (RwUInt32)chunk + chunk->size;
            rwaPoolChunk   *found;

            found = (rwaPoolChunk *)((((RwUInt32)used + alignment + 0x17) & ~(alignment - 1)) -
                                     sizeof(rwaPoolChunk));
            if ((RwUInt32)found + needed <= (RwUInt32)next &&
                (RwUInt32)found >= used + sizeof(rwaPoolChunk))
            {
                if (!found)
                {
                    return NULL;
                }

                found->prev = chunk;
                found->next = chunk->next;
                if (found->next != block->end)
                {
                    found->next->prev = found;
                }

                if (found->prev != block->end)
                {
                    found->prev->next = found;
                }

                found->size = size;

                return found + 1;
            }
        }

        chunk = next;
    }
    while (chunk != block->end);

    return NULL;
}

