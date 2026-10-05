/*
 * type_3CE1FC: an iterator over a path node's link words, anchored at its
 * vtable off_3CE1FC (one slot, the scalar deleting destructor sub_31AA0).
 * Its destructor (sub_31960) is inline: the deleting destructor stores the
 * vtable itself before freeing; both are emitted after AIData::sub_31240,
 * the first function to build one. Callers build it inline (sub_31240,
 * sub_37490, sub_542E0, sub_D2530, sub_F7620, ...).
 *
 *   +0x04 unk_04  the current link word
 *   +0x08 unk_08  which half of it: 0 the low 12 bits (and bit 24), 1 the
 *                 next 12 (and bit 25)
 *   +0x0C unk_0C  the linked node's index; 0 or -1 ends the walk
 *   +0x10 unk_10  the half's flag bit
 */
#ifndef TYPE_3CE1FC_H
#define TYPE_3CE1FC_H

#include "rw/ostypes.h"

struct type_3CE1FC
{
    // The walk over the link words from arg_0: inline, no address.
    // Evidence: "SetDoorPathNodeState" (sub_542E0) stores the vtable and
    // the four fields in order, then calls sub_31980.
    type_3CE1FC(RwUInt32 *arg_0)
    {
        unk_04 = arg_0;
        unk_08 = 0;
        unk_0C = 0;
        unk_10 = 0;
        sub_31980();
    }
    virtual ~type_3CE1FC()
    {
    }

    RwUInt32 *unk_04;
    RwInt32 unk_08;
    RwInt32 unk_0C;
    RwInt32 unk_10;

    // Whether the walk has ended: inline, with no address and so no
    // database name; named for what it tests. Evidence: sub_31A10 computes
    // it into a compiler temporary before testing it, as an inline function
    // returning a comparison does.
    RwInt32 at_end()
    {
        return unk_04 == 0 || unk_0C == 0 || unk_0C == -1;
    }

    // The linked node's index: inline, with no address and so no database
    // name; named for its field. Evidence: "SetDoorPathNodeState"
    // (sub_542E0) loads it before the node table it indexes, which the
    // plain member does not do (a reference, since no temporary holds it).
    RwInt32 &get_unk_0C()
    {
        return unk_0C;
    }

    // Decodes the current half of the link word into unk_0C and unk_10.
    // Inline but never expanded (its switch): emitted after the destructor
    // by the units that call it, and the vtable's ??_G after them, the image's
    // order (0x31960-0x31AA0, aidatapathing.cpp).
    void sub_31980()
    {
        if (unk_04 != 0) {
            switch (unk_08) {
            case 0:
                unk_0C = *unk_04 & 0xFFF;
                unk_10 = (*unk_04 >> 24) & 1;
                break;
            case 1:
                unk_0C = (*unk_04 >> 12) & 0xFFF;
                unk_10 = (*unk_04 >> 25) & 1;
                break;
            }
        }
    }
    // Steps to the next half (or the next word) unless the walk has ended,
    // and decodes it; returns this (inline, as sub_31980).
    type_3CE1FC *sub_31A10()
    {
        if (at_end())
            return this;
        switch (unk_08) {
        case 0:
            unk_08 = unk_08 + 1;
            break;
        case 1:
            unk_04 = unk_04 + 1;
            unk_08 = 0;
            break;
        }
        sub_31980();
        return this;
    }
    // Steps to the next half (or the next word) and decodes it, without
    // the end test (the A* finder's expansion, sub_F7620).
    void sub_F7B00();
};

#endif
