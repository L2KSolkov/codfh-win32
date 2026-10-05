/*
 * The block pools' heaps (game/dlmalloc.h): Doug Lea's malloc 2.7.0 over a
 * state the caller picks, its memory carved from the state's own block.
 */
#include <string.h>
#include "game/dlmalloc.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x005043A8
malloc_state *dword_5043A8;
// End of its data definitions.


typedef malloc_chunk *mchunkptr;
typedef malloc_chunk *mbinptr;
typedef malloc_chunk *mfastbinptr;

// The library's macros, as its source spells them.
#define SIZE_SZ 4
#define MALLOC_ALIGNMENT 8
#define MALLOC_ALIGN_MASK (MALLOC_ALIGNMENT - 1)
#define MINSIZE 16
#define MORECORE_FAILURE (-1)
#define MORECORE(size) sub_1F9C00(size)
#define chunk2mem(p) ((void *)(((RwChar *)(p)) + 2 * SIZE_SZ))
#define mem2chunk(mem) ((mchunkptr)((RwChar *)(mem) - 2 * SIZE_SZ))
#define REQUEST_OUT_OF_RANGE(req) ((RwUInt32)(req) >= (RwUInt32)(-2 * MINSIZE))
#define request2size(req)                                                                                              \
    (((req) + SIZE_SZ + MALLOC_ALIGN_MASK < MINSIZE) ? MINSIZE : ((req) + SIZE_SZ + MALLOC_ALIGN_MASK) & ~MALLOC_ALIGN_MASK)
#define checked_request2size(req, sz)                                                                                  \
    if (REQUEST_OUT_OF_RANGE(req))                                                                                     \
    {                                                                                                                  \
        return 0;                                                                                                      \
    }                                                                                                                  \
    (sz) = request2size(req);
#define PREV_INUSE 0x1
#define prev_inuse(p) ((p)->size & PREV_INUSE)
#define IS_MMAPPED 0x2
#define chunk_is_mmapped(p) ((p)->size & IS_MMAPPED)
#define SIZE_BITS (PREV_INUSE | IS_MMAPPED)
#define chunk_at_offset(p, s) ((mchunkptr)(((RwChar *)(p)) + (s)))
#define inuse_bit_at_offset(p, s) (((mchunkptr)(((RwChar *)(p)) + (s)))->size & PREV_INUSE)
#define set_inuse_bit_at_offset(p, s) (((mchunkptr)(((RwChar *)(p)) + (s)))->size |= PREV_INUSE)
#define chunksize(p) ((p)->size & ~(SIZE_BITS))
#define set_head(p, s) ((p)->size = (s))
#define set_foot(p, s) (((mchunkptr)(((RwChar *)(p)) + (s)))->prev_size = (s))
#define bin_at(m, i) ((mbinptr)((RwChar *)&((m)->bins[(i) << 1]) - (SIZE_SZ << 1)))
#define next_bin(b) ((mbinptr)(((RwChar *)(b)) + (sizeof(mchunkptr) << 1)))
#define first(b) ((b)->fd)
#define last(b) ((b)->bk)
#define unlink(P, BK, FD)                                                                                              \
    {                                                                                                                  \
        FD = P->fd;                                                                                                    \
        BK = P->bk;                                                                                                    \
        FD->bk = BK;                                                                                                   \
        BK->fd = FD;                                                                                                   \
    }
#define NBINS 128
#define MIN_LARGE_SIZE 512
#define in_smallbin_range(sz) ((RwUInt32)(sz) < (RwUInt32)MIN_LARGE_SIZE)
#define smallbin_index(sz) (((RwUInt32)(sz)) >> 3)
#define largebin_index(sz)                                                                                             \
    (((((RwUInt32)(sz)) >> 6) <= 32)   ? 56 + (((RwUInt32)(sz)) >> 6)                                                \
     : ((((RwUInt32)(sz)) >> 9) <= 20)  ? 91 + (((RwUInt32)(sz)) >> 9)                                                \
     : ((((RwUInt32)(sz)) >> 12) <= 10) ? 110 + (((RwUInt32)(sz)) >> 12)                                              \
     : ((((RwUInt32)(sz)) >> 15) <= 4)  ? 119 + (((RwUInt32)(sz)) >> 15)                                              \
     : ((((RwUInt32)(sz)) >> 18) <= 2)  ? 124 + (((RwUInt32)(sz)) >> 18)                                              \
                                        : 126)
#define unsorted_chunks(M) (bin_at(M, 1))
#define initial_top(M) (unsorted_chunks(M))
#define BINMAPSHIFT 5
#define BINMAPSIZE (NBINS / (1U << BINMAPSHIFT))
#define idx2block(i) ((i) >> BINMAPSHIFT)
#define idx2bit(i) ((1U << ((i) & ((1U << BINMAPSHIFT) - 1))))
#define mark_bin(m, i) ((m)->binmap[idx2block(i)] |= idx2bit(i))
#define fastbin_index(sz) ((((RwUInt32)(sz)) >> 3) - 2)
#define DEFAULT_TRIM_THRESHOLD (128 * 1024)
#define FASTBIN_CONSOLIDATION_THRESHOLD ((RwUInt32)(DEFAULT_TRIM_THRESHOLD) >> 1)
#define FASTCHUNKS_BIT (1U)
#define have_fastchunks(M) (((M)->max_fast & FASTCHUNKS_BIT) == 0)
#define clear_fastchunks(M) ((M)->max_fast |= FASTCHUNKS_BIT)
#define set_fastchunks(M) ((M)->max_fast &= ~FASTCHUNKS_BIT)
#define NONCONTIGUOUS_BIT (2U)
#define contiguous(M) (((M)->max_fast & NONCONTIGUOUS_BIT) == 0)
#define set_max_fast(M, s)                                                                                             \
    (M)->max_fast = (((s) == 0) ? 8 : request2size(s)) | FASTCHUNKS_BIT | ((M)->max_fast & NONCONTIGUOUS_BIT)

// match: ?sub_1F90E0@@YAPAPAXXZ @ 0x001F90E0
void **sub_1F90E0()
{
    return (void **)&dword_5043A8;
}

// match: ?sub_1F90F0@@YAPAXPAX@Z @ 0x001F90F0
void *sub_1F90F0(void *arg_0)
{
    malloc_state *var_4 = dword_5043A8;
    dword_5043A8 = (malloc_state *)arg_0;
    return var_4;
}

// match: ?sub_1F9110@@YAXPAXI@Z @ 0x001F9110
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_1F9110(void *arg_0, RwUInt32 arg_4)
{
    RwUInt32 var_4 = sizeof(malloc_state);
    RwUInt32 varC = (var_4 + MALLOC_ALIGN_MASK) & ~MALLOC_ALIGN_MASK;
    type_1F9C00_region *v8 = &((malloc_state *)arg_0)->unk_474;
    memset(arg_0, 0, var_4);
    v8->unk_00 = ((RwChar *)(arg_0)) + varC;
    v8->unk_04 = arg_4 - varC;
    sub_1F90F0(arg_0);
}

// match: ?sub_1F9170@@YAPAXI@Z @ 0x001F9170
void *sub_1F9170(RwUInt32 bytes)
{
    malloc_state *av = dword_5043A8;
    RwUInt32 nb;
    RwUInt32 idx;
    mbinptr bin;
    mfastbinptr *fb;
    mchunkptr victim;
    RwUInt32 size;
    RwInt32 victim_index;
    mchunkptr remainder;
    RwUInt32 remainder_size;
    RwUInt32 block;
    RwUInt32 bit;
    RwUInt32 map;
    mchunkptr fwd;
    mchunkptr bck;

    checked_request2size(bytes, nb);
    if ((RwUInt32)(nb) <= (RwUInt32)(av->max_fast))
    {
        fb = &(av->fastbins[(fastbin_index(nb))]);
        if ((victim = *fb) != 0)
        {
            *fb = victim->fd;
            return chunk2mem(victim);
        }
    }
    if (in_smallbin_range(nb))
    {
        idx = smallbin_index(nb);
        bin = bin_at(av, idx);
        if ((victim = last(bin)) != bin)
        {
            if (victim == 0)
                sub_1F9F00(av);
            else
            {
                bck = victim->bk;
                set_inuse_bit_at_offset(victim, nb);
                bin->bk = bck;
                bck->fd = bin;
                return chunk2mem(victim);
            }
        }
    }
    else
    {
        idx = largebin_index(nb);
        if (have_fastchunks(av))
            sub_1F9F00(av);
    }
    for (;;)
    {
        while ((victim = unsorted_chunks(av)->bk) != unsorted_chunks(av))
        {
            bck = victim->bk;
            size = chunksize(victim);
            if (in_smallbin_range(nb) && bck == unsorted_chunks(av) && victim == av->last_remainder &&
                (RwUInt32)(size) > (RwUInt32)(nb + MINSIZE))
            {
                remainder_size = size - nb;
                remainder = chunk_at_offset(victim, nb);
                unsorted_chunks(av)->bk = unsorted_chunks(av)->fd = remainder;
                av->last_remainder = remainder;
                remainder->bk = remainder->fd = unsorted_chunks(av);
                set_head(victim, nb | PREV_INUSE);
                set_head(remainder, remainder_size | PREV_INUSE);
                set_foot(remainder, remainder_size);
                return chunk2mem(victim);
            }
            unsorted_chunks(av)->bk = bck;
            bck->fd = unsorted_chunks(av);
            if (size == nb)
            {
                set_inuse_bit_at_offset(victim, size);
                return chunk2mem(victim);
            }
            if (in_smallbin_range(size))
            {
                victim_index = smallbin_index(size);
                bck = bin_at(av, victim_index);
                fwd = bck->fd;
            }
            else
            {
                victim_index = largebin_index(size);
                bck = bin_at(av, victim_index);
                fwd = bck->fd;
                if (fwd != bck)
                {
                    size |= PREV_INUSE;
                    if ((RwUInt32)(size) <= (RwUInt32)(bck->bk->size))
                    {
                        fwd = bck;
                        bck = bck->bk;
                    }
                    else
                    {
                        while ((RwUInt32)(size) < (RwUInt32)(fwd->size))
                            fwd = fwd->fd;
                        bck = fwd->bk;
                    }
                }
            }
            mark_bin(av, victim_index);
            victim->bk = bck;
            victim->fd = fwd;
            fwd->bk = victim;
            bck->fd = victim;
        }
        if (!in_smallbin_range(nb))
        {
            bin = bin_at(av, idx);
            if ((victim = last(bin)) != bin && (RwUInt32)(first(bin)->size) >= (RwUInt32)(nb))
            {
                while (((RwUInt32)(size = chunksize(victim)) < (RwUInt32)(nb)))
                    victim = victim->bk;
                remainder_size = size - nb;
                unlink(victim, bck, fwd);
                if (remainder_size < MINSIZE)
                {
                    set_inuse_bit_at_offset(victim, size);
                    return chunk2mem(victim);
                }
                else
                {
                    remainder = chunk_at_offset(victim, nb);
                    unsorted_chunks(av)->bk = unsorted_chunks(av)->fd = remainder;
                    remainder->bk = remainder->fd = unsorted_chunks(av);
                    set_head(victim, nb | PREV_INUSE);
                    set_head(remainder, remainder_size | PREV_INUSE);
                    set_foot(remainder, remainder_size);
                    return chunk2mem(victim);
                }
            }
        }
        ++idx;
        bin = bin_at(av, idx);
        block = idx2block(idx);
        map = av->binmap[block];
        bit = idx2bit(idx);
        for (;;)
        {
            if (bit > map || bit == 0)
            {
                do
                {
                    if (++block >= BINMAPSIZE)
                        goto use_top;
                } while ((map = av->binmap[block]) == 0);
                bin = bin_at(av, (block << BINMAPSHIFT));
                bit = 1;
            }
            while ((bit & map) == 0)
            {
                bin = next_bin(bin);
                bit <<= 1;
            }
            victim = last(bin);
            if (victim == bin)
            {
                av->binmap[block] = map &= ~bit;
                bin = next_bin(bin);
                bit <<= 1;
            }
            else
            {
                size = chunksize(victim);
                remainder_size = size - nb;
                bck = victim->bk;
                bin->bk = bck;
                bck->fd = bin;
                if (remainder_size < MINSIZE)
                {
                    set_inuse_bit_at_offset(victim, size);
                    return chunk2mem(victim);
                }
                else
                {
                    remainder = chunk_at_offset(victim, nb);
                    unsorted_chunks(av)->bk = unsorted_chunks(av)->fd = remainder;
                    remainder->bk = remainder->fd = unsorted_chunks(av);
                    if (in_smallbin_range(nb))
                        av->last_remainder = remainder;
                    set_head(victim, nb | PREV_INUSE);
                    set_head(remainder, remainder_size | PREV_INUSE);
                    set_foot(remainder, remainder_size);
                    return chunk2mem(victim);
                }
            }
        }
    use_top:
        victim = av->top;
        size = chunksize(victim);
        if ((RwUInt32)(size) >= (RwUInt32)(nb + MINSIZE))
        {
            remainder_size = size - nb;
            remainder = chunk_at_offset(victim, nb);
            av->top = remainder;
            set_head(victim, nb | PREV_INUSE);
            set_head(remainder, remainder_size | PREV_INUSE);
            return chunk2mem(victim);
        }
        else if (have_fastchunks(av))
        {
            sub_1F9F00(av);
            idx = smallbin_index(nb);
        }
        else
            return sub_1F9940(nb, av);
    }
}

// match: ?sub_1F9940@@YAPAXIPAUmalloc_state@@@Z @ 0x001F9940
void *sub_1F9940(RwUInt32 nb, malloc_state *av)
{
    mchunkptr old_top;
    RwUInt32 old_size;
    RwChar *old_end;
    RwInt32 size;
    RwChar *brk;
    RwInt32 correction;
    RwChar *snd_brk;
    RwUInt32 front_misalign;
    RwUInt32 end_misalign;
    RwChar *aligned_brk;
    mchunkptr p;
    mchunkptr remainder;
    RwUInt32 remainder_size;
    RwUInt32 sum;
    RwUInt32 pagemask = av->pagesize - 1;

    old_top = av->top;
    old_size = chunksize(old_top);
    old_end = (RwChar *)(chunk_at_offset(old_top, old_size));
    brk = snd_brk = (RwChar *)(MORECORE_FAILURE);
    size = nb + av->top_pad + MINSIZE;
    if (contiguous(av))
        size -= old_size;
    size = (size + pagemask) & ~pagemask;
    if (size > 0)
        brk = (RwChar *)(MORECORE(size));
    if (brk != (RwChar *)(MORECORE_FAILURE))
    {
        av->sbrked_mem += size;
        if (brk == old_end && snd_brk == (RwChar *)(MORECORE_FAILURE))
        {
            set_head(old_top, (size + old_size) | PREV_INUSE);
        }
        else
        {
            front_misalign = 0;
            end_misalign = 0;
            correction = 0;
            aligned_brk = brk;
            if (contiguous(av))
            {
                front_misalign = (RwUInt32)chunk2mem(brk) & MALLOC_ALIGN_MASK;
                if (front_misalign > 0)
                {
                    correction = MALLOC_ALIGNMENT - front_misalign;
                    aligned_brk += correction;
                }
                correction += old_size;
                end_misalign = (RwUInt32)(brk + size + correction);
                correction += ((end_misalign + pagemask) & ~pagemask) - end_misalign;
                snd_brk = (RwChar *)(MORECORE(correction));
                if (snd_brk == (RwChar *)(MORECORE_FAILURE))
                {
                    correction = 0;
                    snd_brk = (RwChar *)(MORECORE(0));
                }
            }
            else
            {
                if (snd_brk == (RwChar *)(MORECORE_FAILURE))
                {
                    snd_brk = (RwChar *)(MORECORE(0));
                }
            }
            if (snd_brk != (RwChar *)(MORECORE_FAILURE))
            {
                av->top = (mchunkptr)aligned_brk;
                set_head(av->top, (snd_brk - aligned_brk + correction) | PREV_INUSE);
                av->sbrked_mem += correction;
                if (old_size != 0)
                {
                    old_size = (old_size - 3 * SIZE_SZ) & ~MALLOC_ALIGN_MASK;
                    set_head(old_top, old_size | PREV_INUSE);
                    chunk_at_offset(old_top, old_size)->size = SIZE_SZ | PREV_INUSE;
                    chunk_at_offset(old_top, old_size + SIZE_SZ)->size = SIZE_SZ | PREV_INUSE;
                    if (old_size >= MINSIZE)
                        sub_1F9C50(chunk2mem(old_top));
                }
            }
        }
        sum = av->sbrked_mem;
        if (sum > (RwUInt32)(av->max_sbrked_mem))
            av->max_sbrked_mem = sum;
        sum += av->mmapped_mem;
        if (sum > (RwUInt32)(av->max_total_mem))
            av->max_total_mem = sum;
        p = av->top;
        size = chunksize(p);
        if ((RwUInt32)(size) >= (RwUInt32)(nb + MINSIZE))
        {
            remainder_size = size - nb;
            remainder = chunk_at_offset(p, nb);
            av->top = remainder;
            set_head(p, nb | PREV_INUSE);
            set_head(remainder, remainder_size | PREV_INUSE);
            return chunk2mem(p);
        }
    }
    return 0;
}

// match: ?sub_1F9C00@@YAPAXH@Z @ 0x001F9C00
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void *sub_1F9C00(RwInt32 arg_0)
{
    type_1F9C00_region *local_8 = &dword_5043A8->unk_474;
    RwChar *var_4 = local_8->unk_00;
    if (local_8->unk_04 < arg_0)
        return (void *)MORECORE_FAILURE;
    local_8->unk_00 += arg_0;
    local_8->unk_04 -= arg_0;
    return var_4;
}

// match: ?sub_1F9C50@@YAXPAX@Z @ 0x001F9C50
void sub_1F9C50(void *mem)
{
    malloc_state *av = dword_5043A8;
    mchunkptr p;
    RwUInt32 size;
    mfastbinptr *fb;
    mchunkptr nextchunk;
    RwUInt32 nextsize;
    RwInt32 nextinuse;
    RwUInt32 prevsize;
    mchunkptr bck;
    mchunkptr fwd;

    if (mem != 0)
    {
        p = mem2chunk(mem);
        size = chunksize(p);
        if ((RwUInt32)(size) <= (RwUInt32)(av->max_fast))
        {
            set_fastchunks(av);
            fb = &(av->fastbins[fastbin_index(size)]);
            p->fd = *fb;
            *fb = p;
        }
        else if (!chunk_is_mmapped(p))
        {
            nextchunk = chunk_at_offset(p, size);
            nextsize = chunksize(nextchunk);
            if (!prev_inuse(p))
            {
                prevsize = p->prev_size;
                size += prevsize;
                p = chunk_at_offset(p, -((RwInt32)prevsize));
                unlink(p, bck, fwd);
            }
            if (nextchunk != av->top)
            {
                nextinuse = inuse_bit_at_offset(nextchunk, nextsize);
                set_head(nextchunk, nextsize);
                if (!nextinuse)
                {
                    unlink(nextchunk, bck, fwd);
                    size += nextsize;
                }
                bck = unsorted_chunks(av);
                fwd = bck->fd;
                p->bk = bck;
                p->fd = fwd;
                bck->fd = p;
                fwd->bk = p;
                set_head(p, size | PREV_INUSE);
                set_foot(p, size);
            }
            else
            {
                size += nextsize;
                set_head(p, size | PREV_INUSE);
                av->top = p;
            }
            if ((RwUInt32)(size) >= FASTBIN_CONSOLIDATION_THRESHOLD)
            {
                if (have_fastchunks(av))
                    sub_1F9F00(av);
                if ((RwUInt32)(chunksize(av->top)) >= (RwUInt32)(av->trim_threshold))
                    sub_1F9E40(av->top_pad, av);
            }
        }
    }
}

// match: ?sub_1F9E40@@YAHIPAUmalloc_state@@@Z @ 0x001F9E40
RwInt32 sub_1F9E40(RwUInt32 pad, malloc_state *av)
{
    RwInt32 top_size;
    RwInt32 extra;
    RwInt32 released;
    RwChar *current_brk;
    RwChar *new_brk;
    RwUInt32 pagesz;

    pagesz = av->pagesize;
    top_size = chunksize(av->top);
    extra = ((top_size - pad - MINSIZE + (pagesz - 1)) / pagesz - 1) * pagesz;
    if (extra > 0)
    {
        current_brk = (RwChar *)(MORECORE(0));
        if (current_brk == ((RwChar *)(av->top)) + top_size)
        {
            MORECORE(-extra);
            new_brk = (RwChar *)(MORECORE(0));
            if (new_brk != (RwChar *)MORECORE_FAILURE)
            {
                released = (RwInt32)(current_brk - new_brk);
                if (released != 0)
                {
                    av->sbrked_mem -= released;
                    set_head(av->top, (top_size - released) | PREV_INUSE);
                    return 1;
                }
            }
        }
    }
    return 0;
}

// match: ?sub_1F9F00@@YAXPAUmalloc_state@@@Z @ 0x001F9F00
void sub_1F9F00(malloc_state *av)
{
    mfastbinptr *fb;
    mfastbinptr *maxfb;
    mchunkptr p;
    mchunkptr nextp;
    mchunkptr unsorted_bin;
    mchunkptr first_unsorted;
    mchunkptr nextchunk;
    RwUInt32 size;
    RwUInt32 nextsize;
    RwUInt32 prevsize;
    RwInt32 nextinuse;
    mchunkptr bck;
    mchunkptr fwd;

    if (av->max_fast != 0)
    {
        clear_fastchunks(av);
        unsorted_bin = unsorted_chunks(av);
        maxfb = &(av->fastbins[fastbin_index(av->max_fast)]);
        fb = &(av->fastbins[0]);
        do
        {
            if ((p = *fb) != 0)
            {
                *fb = 0;
                do
                {
                    nextp = p->fd;
                    size = p->size & ~PREV_INUSE;
                    nextchunk = chunk_at_offset(p, size);
                    nextsize = chunksize(nextchunk);
                    if (!prev_inuse(p))
                    {
                        prevsize = p->prev_size;
                        size += prevsize;
                        p = chunk_at_offset(p, -((RwInt32)prevsize));
                        unlink(p, bck, fwd);
                    }
                    if (nextchunk != av->top)
                    {
                        nextinuse = inuse_bit_at_offset(nextchunk, nextsize);
                        set_head(nextchunk, nextsize);
                        if (!nextinuse)
                        {
                            size += nextsize;
                            unlink(nextchunk, bck, fwd);
                        }
                        first_unsorted = unsorted_bin->fd;
                        unsorted_bin->fd = p;
                        first_unsorted->bk = p;
                        set_head(p, size | PREV_INUSE);
                        p->bk = unsorted_bin;
                        p->fd = first_unsorted;
                        set_foot(p, size);
                    }
                    else
                    {
                        size += nextsize;
                        set_head(p, size | PREV_INUSE);
                        av->top = p;
                    }
                } while ((p = nextp) != 0);
            }
        } while (fb++ != maxfb);
    }
    else
    {
        sub_1FA0D0(av);
    }
}

// match: ?sub_1FA0D0@@YAXPAUmalloc_state@@@Z @ 0x001FA0D0
void sub_1FA0D0(malloc_state *av)
{
    RwInt32 i;
    mbinptr bin;

    for (i = 1; i < NBINS; ++i)
    {
        bin = bin_at(av, i);
        bin->fd = bin->bk = bin;
    }
    av->top_pad = 0;
    av->n_mmaps_max = 0;
    av->mmap_threshold = 128 * 1024;
    av->trim_threshold = DEFAULT_TRIM_THRESHOLD;
    set_max_fast(av, 64);
    av->top = initial_top(av);
    av->pagesize = 8;
}
