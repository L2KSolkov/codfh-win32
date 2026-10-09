/*
 * codfh-match: RenderWare Audio's free lists (0x243670-0x243AE0): entries
 * allocated from bitmapped blocks, the list of all free lists (0x507030)
 * and the free list the free lists come from (0x507060).
 */
#include "rwa.h"
#include "rwaint.h"

#define rwaFreeListFromLink(_link) ((RwaFreeList *)((RwUInt8 *)(_link) - 0x1C))

static rwaLink dword_507030;        /* all free lists */
static RwUInt8 unk_507038[0x24];    /* the free list of free lists */
static RwUInt32 dword_50705C;
static RwaFreeList *dword_507060;

extern void *sub_242170(RwUInt32 size, RwUInt32 hint);
extern void sub_2421B0(void *mem);
extern void *memset(void *dst, RwInt32 value, RwUInt32 size);
extern void *sub_243670(RwaFreeList *freeList, RwUInt32 hint);
extern void sub_2437A0(RwaFreeList *freeList, void *entry);

/* Reconstructed alignment expression from 2436F8-243702 and 243778-243781.
 * The local helper name is descriptive; the original inline name is unknown.
 * bamemory.c's allocator also uses a heap pointer and a separate entry count. */
static __forceinline RwUInt32
rwaFreeListBlockData(rwaFreeListBlock *block, RwUInt32 size, RwUInt32 alignment)
{
    return ((RwUInt32)block + sizeof(rwaLink) + size + alignment - 1) &
           ~(alignment - 1);
}

// match: _sub_243670 @ 0x00243670
// sp-match: _sub_243670 @ 0x00158B90
void *
sub_243670(RwaFreeList *freeList, RwUInt32 hint)
{
    RwUInt32            bitmapSize = freeList->bitmapSize;
    rwaLink            *head = &freeList->blocks;
    rwaFreeListBlock   *block = (rwaFreeListBlock *)head->next;
    void              *entry = NULL;
    RwUInt32           checkEntries;

    while (&block->link != head)
    {
        RwUInt32    i;
        RwUInt8   *heap = block->bitmap;

        if (entry)
        {
            return (void *)entry;
        }

        checkEntries = freeList->entriesPerBlock;
        for (i = 0; i < bitmapSize; i++)
        {
            RwUInt8     bits = heap[i];
            RwUInt32    bit;

            if (bits != 0xFF)
            {
                for (bit = 0; bit < 8; bit++, checkEntries--)
                {
                    RwUInt8     mask;

                    if (checkEntries <= 0)
                    {
                        break;
                    }

                    mask = (RwUInt8)(0x80 >> bit);
                    if (!(bits & mask))
                    {
                        heap[i] = (RwUInt8)(heap[i] | mask);
                        entry = (void *)(rwaFreeListBlockData(block, bitmapSize, freeList->alignment) +
                                (bit + i * 8) * freeList->entrySize);
                        break;
                    }
                }
            }
            else
            {
                checkEntries -= 8;
            }
            if (entry)
            {
                break;
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
// sp-match: _sub_2437A0 @ 0x00158CC0
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
            RwUInt8   *heap;

            heap = block->bitmap;
            heap[byte] &= ~(0x80 >> (index - byte * 8));

            block->link.prev->next = block->link.next;
            block->link.next->prev = block->link.prev;

            first = head->next;
            if (first != head && (freeList->flags & 2))
            {
                RwUInt32    used = 0;
                RwUInt32    i;

                for (i = 0; i < bitmapSize; i++)
                {
                    used += heap[i];
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

// match: _sub_243880 @ 0x00243880
// sp-match: _sub_243880 @ 0x00158DA0
static void
sub_243880(RwaFreeList *freeList)
{
    rwaLink    *head = &freeList->blocks;
    rwaLink    *block;

    while ((block = head->next) != head)
    {
        block->prev->next = block->next;
        block->next->prev = block->prev;
        sub_2421B0(block);
    }

    if (!(freeList->flags & 1))
    {
        if (dword_507060 != freeList && dword_507060)
        {
            sub_2437A0(dword_507060, freeList);
        }
        else
        {
            sub_2421B0(freeList);
        }
    }
}

// match: _sub_2438E0 @ 0x002438E0
// sp-match: _sub_2438E0 @ 0x00158E00
void
sub_2438E0(RwaFreeList *freeList)
{
    freeList->link.prev->next = freeList->link.next;
    freeList->link.next->prev = freeList->link.prev;
    sub_243880(freeList);
}

// match: _sub_243900 @ 0x00243900
// sp-match: _sub_243900 @ 0x00158E20
void
sub_243900(void)
{
    while (dword_507030.next != &dword_507030)
    {
        sub_2438E0(rwaFreeListFromLink(dword_507030.next));
    }

    sub_2438E0(dword_507060);
    dword_507060 = NULL;
    dword_50705C = 0;
}

// match: _sub_243950 @ 0x00243950
// sp-match: _sub_243950 @ 0x00158E70
RwaFreeList *
sub_243950(RwUInt32 entrySize, RwUInt32 entriesPerBlock, RwUInt32 alignment, RwUInt32 noBlocks,
           RwaFreeList *freeList, RwUInt32 hint)
{
    RwUInt32    bitmapSize;
    rwaLink    *head;

    if (!alignment)
    {
        alignment = 1;
    }

    if (!freeList)
    {
        if (dword_507060)
        {
            freeList = (RwaFreeList *)sub_243670(dword_507060, rwaMEMHINTDUR_EVENT | rwaID_800);
        }
        else
        {
            freeList = (RwaFreeList *)sub_242170(sizeof(RwaFreeList), hint);
        }

        if (!freeList)
        {
            return NULL;
        }

        freeList->flags = 2;
    }
    else
    {
        freeList->flags = 3;
    }

    entrySize = (entrySize + alignment - 1) & ~(alignment - 1);
    bitmapSize = (entriesPerBlock + 7) >> 3;
    head = &freeList->blocks;
    freeList->entrySize = entrySize;
    freeList->entriesPerBlock = entriesPerBlock;
    freeList->alignment = alignment;
    freeList->bitmapSize = bitmapSize;
    freeList->blocks.next = head;
    freeList->blocks.prev = head;

    if (noBlocks > 0)
    {
        RwUInt32    blockSize = entrySize * entriesPerBlock + bitmapSize + alignment +
                                sizeof(rwaLink);

        do
        {
            rwaLink    *block = (rwaLink *)sub_242170(blockSize, hint);

            if (!block)
            {
                sub_243880(freeList);

                return NULL;
            }

            block->prev = NULL;
            block->next = NULL;
            block->next = head->next;
            block->prev = head;
            head->next->prev = block;
            head->next = block;
            memset(block + 1, 0, bitmapSize);
        }
        while (--noBlocks);
    }

    freeList->link.next = dword_507030.next;
    freeList->link.prev = &dword_507030;
    dword_507030.next->prev = &freeList->link;
    dword_507030.next = &freeList->link;

    return freeList;
}

// match: _sub_243A80 @ 0x00243A80
// sp-match: _sub_243A80 @ 0x00158FA0
RwBool
sub_243A80(void)
{
    dword_507030.next = &dword_507030;
    dword_507030.prev = &dword_507030;
    dword_50705C = 1;

    dword_507060 = sub_243950(sizeof(RwaFreeList), 0x10, 8, 0, (RwaFreeList *)unk_507038,
                              rwaMEMHINTDUR_GLOBAL | rwaID_800);
    if (!dword_507060)
    {
        dword_50705C = 0;

        return FALSE;
    }

    dword_507060->link.prev->next = dword_507060->link.next;
    dword_507060->link.next->prev = dword_507060->link.prev;

    return TRUE;
}
