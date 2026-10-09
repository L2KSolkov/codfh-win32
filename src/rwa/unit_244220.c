/*
 * codfh-match: RenderWare Audio's pools (0x244220-0x244630): blocks of
 * variably sized, aligned chunks, used for object instances (the instance
 * pools of rwaobjdef.c), the pools' free list (0x5070C4) and list
 * (0x5070BC).
 */
#include "rwa.h"
#include "rwaint.h"

#define rwaPoolFromLink(_link) ((rwaPool *)((RwUInt8 *)(_link) - 0x14))

static rwaLink dword_5070BC;        /* all pools */
static RwUInt8 unk_5070C4[0x24];    /* pools */
static RwUInt32 dword_5070E8;

extern void *sub_242170(RwUInt32 size, RwUInt32 hint);
extern void sub_2421B0(void *mem);
extern void *sub_243670(void *freeList, RwUInt32 hint);
extern void sub_2437A0(void *freeList, void *item);
extern void sub_2438E0(void *freeList);
extern void *sub_2442D0(rwaPoolBlock *block, RwUInt32 size, RwUInt32 alignment);
extern void *sub_243950(RwUInt32 size, RwUInt32 count, RwUInt32 align, RwInt32 a,
                        void *freeList, RwUInt32 hint);

// match: _sub_244220 @ 0x00244220
// sp-match: _sub_244220 @ 0x001587B0
RwBool
sub_244220(void)
{
    dword_5070BC.next = &dword_5070BC;
    dword_5070BC.prev = &dword_5070BC;

    if (sub_243950(sizeof(rwaPool), 8, 8, 0, unk_5070C4, rwaMEMHINTDUR_GLOBAL | rwaID_800))
    {
        dword_5070E8 = TRUE;

        return TRUE;
    }

    return FALSE;
}

// match: _sub_244260 @ 0x00244260
// sp-match: _sub_244260 @ 0x001587F0
static void
sub_244260(rwaPool *pool)
{
    if (!(pool->flags & 1))
    {
        sub_2437A0(unk_5070C4, pool);
    }
}

// match: _sub_244280 @ 0x00244280
// sp-match: _sub_244280 @ 0x00158810
rwaPoolBlock *
sub_244280(RwUInt32 size)
{
    rwaPoolBlock   *block = (rwaPoolBlock *)sub_242170(size, rwaMEMHINTDUR_EVENT | rwaID_800);

    if (block)
    {
        block->chunks = (rwaPoolChunk *)(block + 1);
        block->end = (rwaPoolChunk *)((RwUInt32)block + size);
        block->chunks->size = 0;
        block->chunks->prev = NULL;
        block->chunks->next = block->end;
    }

    return block;
}

// match: _sub_2442C0 @ 0x002442C0
// sp-match: _sub_2442C0 @ 0x00158850
void
sub_2442C0(rwaPoolBlock *block)
{
    sub_2421B0(block);
}

// match: _sub_2442D0 @ 0x002442D0
// sp-match: _sub_2442D0 @ 0x00158860
void *
sub_2442D0(rwaPoolBlock *block, RwUInt32 size, RwUInt32 alignment)
{
    RwUInt32        needed = size + sizeof(rwaPoolChunk);
    rwaPoolChunk   *chunk = block->chunks;
    rwaPoolChunk   *allocation = NULL;
    void          *result = NULL;

    do
    {
        rwaPoolChunk   *next = chunk->next;

        if ((RwUInt32)next - chunk->size - (RwUInt32)chunk - sizeof(rwaPoolChunk) >= needed)
        {
            RwUInt32        used = (RwUInt32)chunk + chunk->size;
            rwaPoolChunk   *found;

            found = (rwaPoolChunk *)(((used + alignment + 2 * sizeof(rwaPoolChunk) - 1) &
                                      ~(alignment - 1)) - sizeof(rwaPoolChunk));
            if ((RwUInt32)(found + 1) + size <= (RwUInt32)next &&
                (RwUInt32)found >= used + sizeof(rwaPoolChunk))
            {
                allocation = found;
                break;
            }
        }

        {
            /* Preserve the end read before advancing the cursor; the
             * original qualifier declaration is unknown. */
            rwaPoolChunk *end = *(rwaPoolChunk *volatile *)&block->end;
            chunk = chunk->next;
            if (chunk == end)
            {
                break;
            }
        }
    }
    while (1);

    if (allocation)
    {
        rwaPoolChunk *after = chunk->next;
        allocation->prev = chunk;
        allocation->next = after;
        if (allocation->next != block->end)
        {
            allocation->next->prev = allocation;
        }

        if (allocation->prev != block->end)
        {
            allocation->prev->next = allocation;
        }

        allocation->size = size;
        result = allocation + 1;
    }
    return result;
}


// match: _sub_244360 @ 0x00244360
// sp-match: _sub_244360 @ 0x001588F0
void
sub_244360(rwaPoolBlock *block, void *data)
{
    rwaPoolChunk   *chunk = block->chunks;

    do
    {
        if (chunk + 1 == (rwaPoolChunk *)data)
        {
            if (chunk->prev != block->end)
            {
                chunk->prev->next = chunk->next;
            }

            if (chunk->next != block->end)
            {
                chunk->next->prev = chunk->prev;
            }

            return;
        }

        chunk = chunk->next;
    }
    while (chunk != block->end);
}

// match: _sub_2443A0 @ 0x002443A0
// sp-match: _sub_2443A0 @ 0x00158930
RwBool
sub_2443A0(rwaPoolBlock *block)
{
    return block->chunks->next == block->end;
}

// match: _sub_2443C0 @ 0x002443C0
// sp-match: _sub_2443C0 @ 0x00158950
static rwaPoolBlock *
sub_2443C0(rwaPool *pool)
{
    rwaPoolBlock   *block = sub_244280(pool->blockSize);

    if (!block)
    {
        return NULL;
    }

    block->link.next = pool->blocks.next;
    block->link.prev = &pool->blocks;
    pool->blocks.next->prev = &block->link;
    pool->blocks.next = &block->link;

    return block;
}

// match: _sub_2443F0 @ 0x002443F0
// sp-match: _sub_2443F0 @ 0x00158980
void
sub_2443F0(rwaPool *pool)
{
    rwaLink    *block;

    while ((block = pool->blocks.next) != &pool->blocks)
    {
        block->prev->next = block->next;
        block->next->prev = block->prev;
        sub_2442C0((rwaPoolBlock *)block);
    }

    pool->link.prev->next = pool->link.next;
    pool->link.next->prev = pool->link.prev;
    sub_244260(pool);
}

// match: _sub_244440 @ 0x00244440
// sp-match: _sub_244440 @ 0x001589D0
void *
sub_244440(rwaPool *pool, RwUInt32 size)
{
    rwaLink        *head = &pool->blocks;
    rwaLink        *cur = head->next;
    void           *data = NULL;
    rwaPoolBlock   *block;

    while (cur != head)
    {
        data = sub_2442D0((rwaPoolBlock *)cur, size, pool->alignment);
        cur = cur->next;
        if (data)
        {
            break;
        }
    }

    if (!data)
    {
        block = sub_2443C0(pool);
        if (block)
        {
            return sub_2442D0(block, size, pool->alignment);
        }
    }

    return data;
}

// match: _sub_2444A0 @ 0x002444A0
// sp-match: _sub_2444A0 @ 0x00158A30
void
sub_2444A0(rwaPool *pool, void *data)
{
    rwaLink    *head = &pool->blocks;
    rwaLink    *block;
    rwaLink    *first;

    for (block = head->next; block != head; block = block->next)
    {
        if ((RwUInt32)data > (RwUInt32)block &&
            (RwUInt32)data < (RwUInt32)block + pool->blockSize)
        {
            sub_244360((rwaPoolBlock *)block, data);

            if (sub_2443A0((rwaPoolBlock *)block))
            {
                block->prev->next = block->next;
                block->next->prev = block->prev;

                first = head->next;
                if (first == head)
                {
                    block->prev = head;
                    block->next = first;
                    head->next->prev = block;
                    head->next = block;

                    return;
                }

                sub_2442C0((rwaPoolBlock *)block);
            }

            return;
        }
    }
}

// match: _sub_244510 @ 0x00244510
// sp-match: _sub_244510 @ 0x00158AA0
void
sub_244510(void)
{
    while (dword_5070BC.next != &dword_5070BC)
    {
        sub_2443F0(rwaPoolFromLink(dword_5070BC.next));
    }

    sub_2438E0(unk_5070C4);
    dword_5070E8 = 0;
}

// match: _sub_244550 @ 0x00244550
// sp-match: _sub_244550 @ 0x00158AE0
rwaPool *
sub_244550(RwUInt32 size, RwUInt32 count, RwUInt32 alignment, RwUInt32 noBlocks, rwaPool *pool)
{
    if (!pool)
    {
        pool = (rwaPool *)sub_243670(unk_5070C4, rwaMEMHINTDUR_EVENT | rwaID_800);
        if (!pool)
        {
            return NULL;
        }

        pool->flags = 0;
    }
    else
    {
        pool->flags = 1;
    }

    pool->alignment = alignment;
    pool->blockSize = (size + sizeof(rwaPoolChunk)) * count + alignment + 0x1C;
    pool->blocks.next = &pool->blocks;
    pool->blocks.prev = &pool->blocks;

    pool->link.next = dword_5070BC.next;
    pool->link.prev = &dword_5070BC;
    dword_5070BC.next->prev = &pool->link;
    dword_5070BC.next = &pool->link;

    while (noBlocks > 0)
    {
        noBlocks--;
        if (!sub_2443C0(pool))
        {
            sub_2443F0(pool);

            return NULL;
        }
    }

    return pool;
}
