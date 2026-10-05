/*
 * The memory pools (unit_1F8BF0): a pool allocates through its slots 1 and
 * 2 and counts what it has out (unk_04). The heap pool (one, made on first
 * use by sub_1F8CF0) takes from new and delete; a block pool takes a block
 * of arg_4 bytes from its parent pool arg_0 and runs a heap in it (its
 * second base). Five block pools are globals (unk_4FEBBC to unk_4FEC3C,
 * 0x20 bytes each), built over blocks from the heap pool by their dynamic
 * initializers; sub_1CBC30 to sub_1CBC70 give them.
 */
#ifndef GAME_POOL_H
#define GAME_POOL_H

#include "rw/ostypes.h"

// A compiled-out check of a pool's count: no code, but its registers move
// on by the loads its condition would make (docs/toolchain.md).
#define POOL_CHECK(e) { if (!(e)) { } }

// A pool (off_3E7DFC; its constructor and destructor are out of line,
// sub_1F8C70 and sub_1F8CD0): allocates arg_0 bytes (counting it) and
// frees arg_0 (not counting a null one).
struct type_1F8BF0
{
    RwInt32 unk_04;

    type_1F8BF0();
    virtual ~type_1F8BF0();
    virtual void *vf_004(RwUInt32 arg_0) = 0;
    virtual void vf_008(void *arg_0) = 0;
    // +0xC: the image's vtable has a fourth slot (a pure call here).
    virtual void vf_00C() = 0;
    void *sub_1F8BF0(RwUInt32 arg_0);
    void sub_1F8C30(void *arg_0);
};

// The heap pool (off_3E7E0C; its destructor is the compiler's, sub_1F8DA0,
// which leaves the vtable as it is).
struct type_3E7E0C : type_1F8BF0
{
    type_3E7E0C()
    {
    }
    virtual void *vf_004(RwUInt32 arg_0);
    virtual void vf_008(void *arg_0);
    virtual void vf_00C();
};
type_1F8BF0 *sub_1F8CF0();

// The heaps a block pool runs (unit_1F90E0): the heap allocated from and
// freed to (dword_5043A8: its address given by sub_1F90E0, set by
// sub_1F90F0, which gives the one before), one built over the block arg_0
// of arg_4 bytes (sub_1F9110), arg_0 bytes allocated (sub_1F9170) and
// freed (sub_1F9C50).
void **sub_1F90E0();
void *sub_1F90F0(void *arg_0);
void sub_1F9110(void *arg_0, RwUInt32 arg_4);
void *sub_1F9170(RwUInt32 arg_0);
void sub_1F9C50(void *arg_0);

// A heap in a block (off_3E7E30, a block pool's second base): the block
// (unk_04), the current heap it sets before each call (unk_08), the size
// (unk_0C) and the count out (unk_10). Its allocation, freeing and reset
// are inlines with no addresses, named for what they do.
struct type_3E7E30
{
    void *unk_04;
    void **unk_08;
    RwUInt32 unk_0C;
    RwInt32 unk_10;

    type_3E7E30(void *arg_0, RwUInt32 arg_4)
    {
        unk_04 = arg_0;
        unk_08 = sub_1F90E0();
        unk_0C = arg_4;
        sub_1F9110(arg_0, arg_4);
        unk_10 = 0;
        unk_10 = 0;
    }
    virtual ~type_3E7E30()
    {
        POOL_CHECK(unk_10 == 0);
    }
    void *heap_alloc(RwUInt32 arg_0)
    {
        *unk_08 = unk_04;
        void *var_4 = sub_1F9170(arg_0);
        if (var_4)
            ++unk_10;
        return var_4;
    }
    void heap_free(void *arg_0)
    {
        if (arg_0)
        {
            POOL_CHECK(unk_10 > 0);
            --unk_10;
            *unk_08 = unk_04;
            sub_1F9C50(arg_0);
        }
    }
    void heap_reset()
    {
        sub_1F9110(unk_04, unk_0C);
        unk_10 = 0;
    }
};

// A block pool (off_3E7E20 and off_3E7E1C, 0x20 bytes): a heap in a block
// from the pool unk_1C, which gets the block back when it goes; slot 3
// empties the heap.
struct type_1F8E00 : type_1F8BF0, type_3E7E30
{
    type_1F8BF0 *unk_1C;

    type_1F8E00(type_1F8BF0 *arg_0, RwUInt32 arg_4);
    virtual ~type_1F8E00();
    virtual void *vf_004(RwUInt32 arg_0);
    virtual void vf_008(void *arg_0);
    virtual void vf_00C();
};

type_1F8BF0 *sub_1CBC30();
type_1F8BF0 *sub_1CBC40();
type_1F8BF0 *sub_1CBC50();
type_1F8BF0 *sub_1CBC60();
type_1F8BF0 *sub_1CBC70();
extern type_1F8E00 unk_4FEBBC;
extern type_1F8E00 unk_4FEBDC;
extern type_1F8E00 unk_4FEBFC;
extern type_1F8E00 unk_4FEC1C;
extern type_1F8E00 unk_4FEC3C;

#endif
