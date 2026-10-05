/*
 * The heaps the block pools run (unit_1F90E0): Doug Lea's malloc 2.7.0
 * (the layout of its state, its bins' and fast bins' macros and the code of
 * its malloc, free, sYSMALLOc, sYSTRIm, malloc_consolidate and
 * malloc_init_state match that version), built without mmap, with a 128K
 * trim threshold and an 8-byte page, over a state the caller picks
 * (dword_5043A8, game/pool.h) and a MORECORE that carves the state's own
 * block (unk_474). The structs keep the library's names.
 */
#ifndef GAME_DLMALLOC_H
#define GAME_DLMALLOC_H

#include "rw/ostypes.h"
#include "game/pool.h"

struct malloc_chunk
{
    RwUInt32 prev_size;
    RwUInt32 size;
    malloc_chunk *fd;
    malloc_chunk *bk;
};

// What MORECORE carves: the next byte and how many are left.
struct type_1F9C00_region
{
    RwChar *unk_00;
    RwInt32 unk_04;
};

struct malloc_state
{
    RwUInt32 max_fast;
    malloc_chunk *fastbins[10];
    malloc_chunk *top;
    malloc_chunk *last_remainder;
    malloc_chunk *bins[128 * 2];
    RwUInt32 binmap[4];
    RwUInt32 trim_threshold;
    RwUInt32 top_pad;
    RwUInt32 mmap_threshold;
    RwInt32 n_mmaps;
    RwInt32 n_mmaps_max;
    RwInt32 max_n_mmaps;
    RwUInt32 pagesize;
    RwUInt32 mmapped_mem;
    RwUInt32 sbrked_mem;
    RwUInt32 max_sbrked_mem;
    RwUInt32 max_mmapped_mem;
    RwUInt32 max_total_mem;
    type_1F9C00_region unk_474;
};

extern malloc_state *dword_5043A8;

// sYSMALLOc, MORECORE, sYSTRIm, malloc_consolidate and malloc_init_state.
void *sub_1F9940(RwUInt32 arg_0, malloc_state *arg_4);
void *sub_1F9C00(RwInt32 arg_0);
RwInt32 sub_1F9E40(RwUInt32 arg_0, malloc_state *arg_4);
void sub_1F9F00(malloc_state *arg_0);
void sub_1FA0D0(malloc_state *arg_0);

#endif
