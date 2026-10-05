/*
 * The Vision Scheduler's data ("Somebody forgot to unregister in the Vision
 * Scheduler!", sub_408D0): its registrations (type_409A0), drawn from the
 * pool dword_43988C ("m_freeVisionParams") and addressed through the handle
 * table dword_439618 (type_365A0 handles, handed out by sub_42870).
 */
#ifndef TYPE_409A0_H
#define TYPE_409A0_H

#include "rw/ostypes.h"
#include "types/type_365A0.h"

struct type_409A0;

// An entry of dword_439618: the handle it was given and its registration.
struct type_439618
{
    type_365A0 unk_00;
    type_409A0 *unk_04;
};

// type_409A0: one registration, 0x20 bytes, built by sub_409A0 (after which
// it is named).
//
//   +0x00 unk_00  its handle (sub_42870)
//   +0x04 unk_04  the test
//   +0x08 unk_08  the squared view range (sub_40BD0)
//   +0x0C unk_0C  the other object's handle (type_3D2E7C::unk_04), and
//   +0x10 unk_10  its serial (type_3D2E7C::unk_24)
//   +0x14 unk_14  the time of the last look (RWS::Time::GetTime, sub_40EA0)
//   +0x18 unk_18  a countdown: a random start below dword_42767C + 1,
//                 wrapping to dword_42767C (sub_40EA0)
//   +0x1C         flags, from sub_409A0's arg_4 (bit 0) and arg_8 (bit 1)
struct type_409A0
{
    type_365A0 unk_00;
    RwInt32 unk_04;
    RwReal unk_08;
    RwUInt32 unk_0C;
    RwInt32 unk_10;
    RwUInt32 unk_14;
    RwInt8 unk_18;
    RwUInt32 unk_1C_0 : 1;
    RwUInt32 unk_1C_1 : 1;
};
typedef RwChar type_409A0_size_check[sizeof(type_409A0) == 0x20 ? 1 : -1];

struct type_3D3548;

// type_42210: the line-of-sight test's data, which sub_42210 hands to the
// atomic callback sub_42350 and it to the triangle callback sub_42580.
struct type_42210
{
    type_3D3548 *unk_00;    // the looking entity, and
    type_3D3548 *unk_04;    // its target: their own atomics do not block
    RwReal unk_08;          // the nearest blocking distance found
    RwUInt8 unk_0C;         // set when a triangle is hit (sub_42580)
    RwUInt8 unk_0D;         // clear to stop at the first blocking atomic
};

#endif
