/*
 * alfahash: a chained hash table of pointers, named from the image's own
 * string "alfahash::m_pool", which sub_677C0 passes when it sets up the pool
 * of its nodes at +0x10 (so the member is m_pool).
 *
 *   +0x00 unk_00  the node count m_pool is set up for
 *   +0x04 unk_04  the bucket count
 *   +0x08 unk_08  the hash function (taken modulo unk_04)
 *   +0x0C unk_0C  the equality test, of a node's key and a key
 *   +0x10 m_pool  a type_16C2A0 pool of alfahash_node
 *   +0x30 unk_30  the buckets, each a node list
 */
#ifndef ALFAHASH_H
#define ALFAHASH_H

#include "rw/ostypes.h"
#include "types/alfasched.h"

// alfahash_node: one of m_pool's 8-byte elements.
struct alfahash_node
{
    void *unk_00;               // the key
    alfahash_node *unk_04;      // the next node of its bucket
};

struct alfahash
{
    RwInt32 unk_00;
    RwInt32 unk_04;
    RwUInt32 (*unk_08)(void *arg_0);
    bool (*unk_0C)(void *arg_0, void *arg_4);
    type_16C2A0 m_pool;
    alfahash_node **unk_30;

    // sub_676A0, sub_676E0.
    alfahash();
    ~alfahash();
    // Sets the table up: arg_0 nodes, arg_4 buckets, the hash arg_8 and the
    // equality test arg_C.
    void sub_67730(RwInt32 arg_0, RwInt32 arg_4, RwUInt32 (*arg_8)(void *),
                   bool (*arg_C)(void *, void *));
    // Frees the buckets and shuts m_pool down.
    void sub_67780();
    // Sets m_pool up for arg_0 nodes.
    void sub_677C0(RwInt32 arg_0);
    // Allocates arg_0 empty buckets.
    void sub_677F0(RwInt32 arg_0);
    // Adds arg_0 unless it is present; whether it did.
    bool sub_67850(void *arg_0);
    // Removes arg_0, when present.
    void sub_678C0(void *arg_0);
    // The key equal to arg_0, or 0.
    void *sub_67970(void *arg_0);
    // The node of the list arg_0 whose key equals arg_4, or 0.
    alfahash_node *sub_679C0(alfahash_node *arg_0, void *arg_4);
    // The bucket of arg_0.
    RwUInt32 sub_67A10(void *arg_0);
    // A new node for arg_0, from m_pool.
    alfahash_node *sub_67A40(void *arg_0);
    // Returns the node arg_0 to m_pool.
    void sub_67A80(alfahash_node *arg_0);
    // Calls arg_0 on every key, stopping when it returns false.
    void sub_67AA0(bool (*arg_0)(void *));
};
typedef RwChar alfahash_size_check[sizeof(alfahash) == 0x34 ? 1 : -1];

#endif
