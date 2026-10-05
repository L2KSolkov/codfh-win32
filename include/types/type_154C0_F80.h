/*
 * type_154C0_F80: one result of a node search (type_154C0_1048), 8 bytes.
 * AIData holds 25 at +0xF80 (the +0x1048 request points at them) and
 * AIData::sub_28470 keeps 32 on the stack; named after that first container
 * and offset.
 *
 *   +0x00 unk_00  the node's index in the node table (unk_4C00E8.unk_2C)
 *   +0x04 unk_04  its distance, compared by sub_28470
 */
#ifndef TYPE_154C0_F80_H
#define TYPE_154C0_F80_H

#include "rw/ostypes.h"

struct type_154C0_F80
{
    RwInt16 unk_00;
    RwInt16 unk_02;         // set once AIData::sub_244E0 has tried the result
                            // (read with movsx)
    RwReal unk_04;
};
typedef RwChar type_154C0_F80_size_check[sizeof(type_154C0_F80) == 0x8 ? 1 : -1];

#endif
