/*
 * A doubly linked list whose nodes come from a memory pool (game/pool.h),
 * its methods at 0x1FA180 on: each node holds its neighbours and then the
 * element's bytes, and removed nodes wait on a free list for reuse. The
 * network game's parts keep their messages in lists derived from it. Only
 * the widths are known; the names say what the code does.
 */
#ifndef GAME_POOLLIST_H
#define GAME_POOLLIST_H

#include "rw/ostypes.h"
#include "game/pool.h"

// A node: the previous and next nodes; the element follows.
struct type_1FA180_node
{
    type_1FA180_node *unk_00;
    type_1FA180_node *unk_04;

    // Folded by /OPT:ICF into 0x1EFD70 (two stores).
    type_1FA180_node(type_1FA180_node *arg_0, type_1FA180_node *arg_4);
};

// A node from the pool arg_0 between arg_4 and arg_8 with arg_C bytes of
// element (0 when the pool is empty), and a node back to the pool.
type_1FA180_node *sub_1FA180(type_1F8BF0 *arg_0, type_1FA180_node *arg_4, type_1FA180_node *arg_8,
                             RwInt32 arg_C);
void sub_1FA210(type_1F8BF0 *arg_0, type_1FA180_node *arg_4);

struct type_1FA230
{
    type_1FA180_node *unk_00;   // the head
    type_1FA180_node *unk_04;   // the tail
    type_1FA180_node *unk_08;   // the cursor
    type_1FA180_node *unk_0C;   // the free nodes
    RwInt32 unk_10;             // the count
    type_1F8BF0 *unk_14;        // the pool

    type_1FA230(type_1F8BF0 *arg_0);
    ~type_1FA230();
    // Empties it (the nodes go to the free list); appends arg_0 bytes and
    // returns them (0 when out of memory); removes the head, the tail, and
    // the cursor's node (returning the next element); whether the cursor
    // is on a node; gives the free nodes back to the pool.
    void sub_1FA2A0();
    void *sub_1FA310(RwInt32 arg_0);
    void sub_1FA3A0();
    void sub_1FA420();
    void *sub_1FA4A0();
    RwInt32 sub_1FA590();
    // Its count: an out-of-line getter folded by /OPT:ICF into 0x191D80.
    RwInt32 sub_191D80();
    void sub_1FA5B0();
    // Puts arg_0 on the free list; takes a node off it between arg_0 and
    // arg_4; frees the free list; a node between arg_0 and arg_4 with
    // arg_8 bytes of element, reused when it can be.
    void sub_1FA5D0(type_1FA180_node *arg_0);
    type_1FA180_node *sub_1FA600(type_1FA180_node *arg_0, type_1FA180_node *arg_4);
    void sub_1FA640();
    type_1FA180_node *sub_1FA690(type_1FA180_node *arg_0, type_1FA180_node *arg_4, RwInt32 arg_8);
};

#endif
