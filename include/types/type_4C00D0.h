/*
 * type_4C00D0: a per-frame counter pair, two of them (dword_4C00D0 and
 * dword_4C0150), anchored at sub_3ED10, which starts a new frame on each:
 * when unk_00 is not the frame number dword_4B87D8, it takes it, raises
 * unk_10 to unk_0C and clears unk_04 and unk_0C. The path code counts into
 * them (sub_F6DE0 into dword_4C00D0's unk_04 and unk_08, sub_F8970 into
 * dword_4C0150's unk_04 and unk_0C). Only these fields are known.
 */
#ifndef TYPE_4C00D0_H
#define TYPE_4C00D0_H

#include "rw/ostypes.h"

struct type_4C00D0
{
    RwUInt32 unk_00;        // the frame counted
    RwUInt32 unk_04;
    RwUInt32 unk_08;
    RwUInt32 unk_0C;        // this frame's count
    RwUInt32 unk_10;        // the highest count of a frame
};

#endif
