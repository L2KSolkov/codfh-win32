/*
 * type_3D410: the member a type_3DF30 group embeds at +0x4, anchored at its
 * constructor sub_3D410, which type_3DF30's constructor calls on it; sub_3D4C0
 * then points its unk_00 back at the group. 0x2A4 bytes (the group's own
 * fields follow at +0x2A8). It is the context the group's type_3CE6D0 objects receive in
 * their update (vf_00C) and elsewhere.
 *
 *   +0x000 unk_00   the group
 *   +0x004 unk_04   the targets the group sees (sub_3D7D0's count)
 *   +0x008 unk_08   a count: nothing is started while it is not positive
 *   +0x00C unk_0C   the members that see a target
 *   +0x010 unk_10   the previous unk_04
 *   +0x014 unk_14   two countdowns, one per periodic update (dword_427660)
 *   +0x01C unk_1C   32 target records (type_3D410_1C), by AI record number
 *   +0x11C unk_11C  32 candidate records (type_3D410_11C; sub_3D720 hands
 *                   them out)
 *   +0x29C unk_29C  a time since a target was seen (10000 with none);
 *                   AIData::sub_22110 compares it with 900 and zeroes it
 *   +0x2A0 unk_2A0  the time with no target seen
 */
#ifndef TYPE_3D410_H
#define TYPE_3D410_H

#include "rw/ostypes.h"
#include "types/type_D48D0.h"

struct type_3D3548;
struct type_3DF30;

// type_3D410_1C: a target record: the target and whether a member sees it.
struct type_3D410_1C
{
    type_D48D0 unk_00;
    RwUInt32 unk_04_0 : 1;
};

// type_3D410_11C: a candidate record (type_3CE5E8's sub_3B560 reads the
// handle of each of the 32); sub_3D760 clears it when its entity changes.
struct type_3D410_11C
{
    type_D48D0 unk_00;
    RwInt32 unk_04;
    RwUInt8 unk_08;
    RwUInt8 unk_09;         // while set, sub_3D6B0 clears unk_08
    RwUInt8 unk_0A[0x2];
};

struct type_3D410
{
    type_3DF30 *unk_00;
    RwInt32 unk_04;
    RwInt32 unk_08;
    RwInt32 unk_0C;
    RwInt32 unk_10;
    RwReal unk_14[2];
    type_3D410_1C unk_1C[32];
    type_3D410_11C unk_11C[32];
    RwReal unk_29C;
    RwReal unk_2A0;

    type_3D410();
    // Empty in the retail image: the squad's cleanup (type_3DF30::sub_3E0A0)
    // calls it last, and /OPT:ICF folded it into pDtor (0x1E41C0).
    void sub_1E41C0();
    // Points unk_00 at the group arg_0 and clears the rest.
    void sub_3D4C0(type_3DF30 *arg_0);
    // Runs the periodic updates (dword_427660) whose countdown has run out,
    // counting the rest down by arg_0.
    void sub_3D5F0(RwReal arg_0);
    void sub_3D6B0(RwReal arg_0);
    // The candidate record of the entity in unk_438CA8[arg_0], 0 without one.
    type_3D410_11C *sub_3D720(RwInt32 arg_0);
    type_3D410_11C *sub_3D760(type_3D3548 *arg_0, RwInt32 arg_4);

    // An inline accessor for unk_00, with no address and so no database
    // name; named for its field. Evidence: type_3CE5E8::vf_010 reads the
    // group through a temporary of its own each of the three times.
    type_3DF30 *get_unk_00()
    {
        type_3DF30 *r = unk_00;
        return r;
    }

    // An inline accessor for unk_29C, likewise nameless and named for its
    // field. Evidence for its shape: AIData::sub_22110 loads +0x29C into a
    // compiler temporary just above `this` and compares from there, which is
    // what an inline function holding its result in a local expands to
    // (docs/toolchain.md).
    RwReal get_unk_29C()
    {
        RwReal r = unk_29C;
        return r;
    }

    // Picks a target for the entity arg_0 among the 32 candidates
    // (sub_3D720), else drops its target (AIData::sub_18BB0).
    RwInt32 sub_3DCD0(type_3D3548 *arg_0);
};
typedef RwChar type_3D410_size_check[sizeof(type_3D410) == 0x2A4 ? 1 : -1];

#endif
