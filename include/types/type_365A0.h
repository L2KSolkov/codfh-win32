/*
 * type_365A0: a handle, named after the Distance Scheduler's sub_365A0,
 * which hands them out for its table dword_438E90: the table index in the
 * low word and a serial in the high word; a handle is valid while the entry
 * holds the same dword. The AIManeuverManager's table dword_4392A8 uses the
 * same form (sub_3D2E0 hands its handles out). Four bytes with no
 * constructor, so it is returned in eax and passed by value as a dword.
 */
#ifndef TYPE_365A0_H
#define TYPE_365A0_H

#include "rw/ostypes.h"

union type_365A0
{
    RwUInt32 unk_00;
    struct
    {
        RwUInt16 unk_00_lo;
        RwUInt16 unk_02;
    };
};

#endif
