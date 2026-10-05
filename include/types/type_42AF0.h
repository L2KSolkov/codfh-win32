/*
 * The action queue ("m_actionPool", sub_42990): actions queued for the next
 * tick (sub_42C50), 16-byte records drawn from the pool dword_439910 and
 * listed from dword_439904 to dword_439900 through unk_0C. While a tick runs
 * them (byte_439908 set), dword_4398FC is the one running and dword_43990C
 * the last of the tick; sub_42AF0 queues an action behind the running one or
 * at the tick's end.
 */
#ifndef TYPE_42AF0_H
#define TYPE_42AF0_H

#include "rw/ostypes.h"

// type_42AF0: one queued action, built by sub_42AF0 (after which it is
// named).
//
//   +0x00 unk_00  its kind: kind 16 runs (sub_42DA0) and drops (sub_42DE0)
//                 the object with handle unk_08
//   +0x04 unk_04  the sender's handle (type_3D2E7C::unk_04), 0 without one
//   +0x08 unk_08  a handle (sub_67620)
//   +0x0C unk_0C  the next action
struct type_42AF0
{
    RwInt32 unk_00;
    RwUInt32 unk_04;
    RwUInt32 unk_08;
    type_42AF0 *unk_0C;
};
typedef RwChar type_42AF0_size_check[sizeof(type_42AF0) == 0x10 ? 1 : -1];

// type_42E00_00: a message's kind, an entry of the loaded script image's
// message table (the script VM's dword_4492F4, 0x14 bytes); sub_42E00
// matches its unk_04 against an id.
struct type_42E00_00
{
    RwChar *unk_00;         // its name (sub_6A7F0 finds it by it)
    RwInt32 unk_04;         // its id
    RwInt32 unk_08;         // the keys sub_6A860 finds it by
    RwInt32 unk_0C;
    RwInt16 unk_10;         // its argument count (the words a send pops)
    RwInt16 unk_12;
};

// type_42E00_10: what a message's unk_10 comes from (sub_6B710's arg_C);
// only that field is known.
struct type_42E00_10
{
    RwUInt8 unk_00[0x3C];
    RwInt16 unk_3C;
};

// type_42E00: a message, the object of a kind-16 action (0x18 bytes from
// alfamessman's m_messagePool, registered in the handle table dword_439E78
// as kind 6 by sub_6B710; sub_67620 resolves it), as sub_42E00 reads it.
struct type_42E00
{
    type_42E00_00 *unk_00;  // its kind
    RwUInt32 unk_04;        // the handle of the script it is for (0 for all)
    RwUInt32 unk_08;        // the sender's handle
    RwUInt32 unk_0C;        // another object's handle
    RwInt16 unk_10;         // from sub_6B710's arg_C (-1 without one)
    RwInt16 unk_12;         // sub_42E00 drops only actions with it clear
    RwInt32 *unk_14;        // its arguments (unk_00->unk_10 words)
};
typedef RwChar type_42E00_size_check[sizeof(type_42E00) == 0x18 ? 1 : -1];

struct type_3D2E7C;

// sub_42AF0: queues an action of kind arg_4 with the handle arg_8 from
// arg_0 (unit_042990).
void sub_42AF0(type_3D2E7C *arg_0, RwInt32 arg_4, RwUInt32 arg_8, bool arg_C, bool arg_10);

#endif
