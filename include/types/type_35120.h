/*
 * The Distance Scheduler's data ("Somebody forgot to unregister in the
 * Distance Scheduler!", sub_350D0): its registrations (type_35120), drawn
 * from the pool dword_4391EC ("m_freeDistanceParams") and addressed through
 * the handle table dword_438E90 (type_365A0 handles).
 */
#ifndef TYPE_35120_H
#define TYPE_35120_H

#include "rw/ostypes.h"
#include "types/alfasched.h"
#include "types/type_365A0.h"

struct type_35120;

// An entry of dword_438E90: the handle it was given and its registration.
struct type_438E90
{
    type_365A0 unk_00;
    type_35120 *unk_04;
};

// type_35120: one registration, 0x24 bytes, built by sub_35120 (after which
// it is named).
//
//   +0x00 unk_00  its handle (sub_365A0)
//   +0x04 unk_04  the test: 3, 5 and 10 against another object's entity;
//                 7, 12, 8, 9, 11, 13 and 14 through the AI object
//                 (sub_21610, sub_21910, sub_221E0, sub_21790); any other
//                 value against every listed entity (sub_35AA0 filters)
//   +0x08 unk_08  the squared minimum distance
//   +0x0C unk_0C  the squared maximum distance
//   +0x10 unk_10  the other object's handle (type_3D2E7C::unk_04), and
//   +0x14 unk_14  its serial (type_3D2E7C::unk_24)
//   +0x18 unk_18  the message sent in range, -1 for "TargetInRange"
//   +0x1C unk_1C  the message sent out of range, -1 for "TargetOutOfRange"
//   +0x20         flags: bit 0 ends the registration once the answer
//                 matches; bit 1 asks for "in range" rather than "out of
//                 range"
struct type_35120
{
    type_365A0 unk_00;
    RwInt32 unk_04;
    RwReal unk_08;
    RwReal unk_0C;
    RwUInt32 unk_10;
    RwInt32 unk_14;
    RwInt32 unk_18;
    RwInt32 unk_1C;
    RwUInt32 unk_20_0 : 1;
    RwUInt32 unk_20_1 : 1;
};
typedef RwChar type_35120_size_check[sizeof(type_35120) == 0x24 ? 1 : -1];

// type_35FD0: the two dwords sent with "TargetInRange" / "TargetOutOfRange"
// (sub_35FD0 and sub_362F0 build one on the stack and pass it with a count
// of 2): the target object's handle (0 when there is none) and the distance.
struct type_35FD0
{
    RwUInt32 unk_00;
    RwReal unk_04;
};

#endif
