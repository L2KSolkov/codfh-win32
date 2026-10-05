// match: _sub_243670 @ 0x00243670
void *
sub_243670(RwaFreeList *freeList, RwUInt32 hint)
{
    RwUInt32            bitmapSize = freeList->bitmapSize;
    rwaLink            *head = &freeList->blocks;
    rwaFreeListBlock   *block = (rwaFreeListBlock *)head->next;
    RwUInt32            entry = 0;

    while (&block->link != head)
    {
        RwUInt32    i;

        if (entry)
        {
            return (void *)entry;
        }

        hint = freeList->entriesPerBlock;
        for (i = 0; i < bitmapSize; i++)
        {
            RwUInt8     bits = block->bitmap[i];
            RwUInt32    bit;

            if (bits != 0xFF)
            {
                for (bit = 0; bit < 8; bit++, hint--)
                {
                    RwUInt8     mask;

                    if (hint <= 0)
                    {
                        break;
                    }

                    mask = (RwUInt8)(0x80 >> bit);
                    if (!(bits & mask))
                    {
                        block->bitmap[i] = bits | mask;
                        entry = rwaFreeListBlockData(block, bitmapSize, freeList->alignment) +
                                (bit + i * 8) * freeList->entrySize;
                        break;
                    }
                }

                if (entry)
                {
                    break;
                }
            }
            else
            {
                hint -= 8;
            }
        }

        block = (rwaFreeListBlock *)block->link.next;
    }

    if (entry)
    {
        return (void *)entry;
    }

    block = (rwaFreeListBlock *)sub_242170(freeList->entriesPerBlock * freeList->entrySize +
                                           freeList->alignment + bitmapSize +
                                           sizeof(rwaLink), hint);
    if (!block)
    {
        return NULL;
    }

    memset(block->bitmap, 0, bitmapSize);
    block->link.next = head->next;
    block->link.prev = head;
    head->next->prev = &block->link;
    head->next = &block->link;
    block->bitmap[0] = 0x80;

    return (void *)rwaFreeListBlockData(block, bitmapSize, freeList->alignment);
}

// match: _sub_2437A0 @ 0x002437A0
void
sub_2437A0(RwaFreeList *freeList, void *entry)
{
    RwUInt32            bitmapSize = freeList->bitmapSize;
    rwaLink            *head = &freeList->blocks;
    rwaFreeListBlock   *block;

    for (block = (rwaFreeListBlock *)head->next; &block->link != head;
         block = (rwaFreeListBlock *)block->link.next)
    {
        RwUInt8    *data = &block->bitmap[bitmapSize];

        if ((RwUInt8 *)entry >= data &&
            (RwUInt8 *)entry <= data + freeList->entriesPerBlock * freeList->entrySize)
        {
            RwUInt32    index = ((RwUInt8 *)entry - data) / freeList->entrySize;
            RwUInt32    byte = index >> 3;
            rwaLink    *first;

            block->bitmap[byte] &= ~(0x80 >> (index - byte * 8));

            block->link.prev->next = block->link.next;
            block->link.next->prev = block->link.prev;

            first = head->next;
            if (first != head && (freeList->flags & 2))
            {
                RwUInt32    used = 0;
                RwUInt32    i;

                for (i = 0; i < bitmapSize; i++)
                {
                    used += block->bitmap[i];
                }

                if (!used)
                {
                    sub_2421B0(block);

                    return;
                }

                block->link.prev = head;
                block->link.next = first;
                head->next->prev = &block->link;
                head->next = &block->link;

                return;
            }

            block->link.next = first;
            block->link.prev = head;
            head->next->prev = &block->link;
            head->next = &block->link;

            return;
        }
    }
}

