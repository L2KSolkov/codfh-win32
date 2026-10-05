/*
 * type_4B8600: the 16-byte records of the table at dword_4B8600 (16 of them;
 * sub_D5650 walks them by index), named for its first instance.
 *
 *   +0x00 unk_00  the first entity of a list linked through
 *                 type_3D3548::unk_10; AIData::sub_24BA0 walks record 1 for
 *                 an owner of kind 1 and record 0 for kind 2
 */
#ifndef TYPE_4B8600_H
#define TYPE_4B8600_H

#include "rw/ostypes.h"

struct type_3D3548;

struct type_4B8600
{
    type_3D3548 *unk_00;
    RwUInt8 unk_04[0xC];

    // The list's first entity: an inline accessor with no address and so no
    // database name; named for its field. Evidence: type_3D3548's sub_D29C0
    // copies each list head it passes on into a local of its own (the
    // accessor's result).
    type_3D3548 *get_unk_00()
    {
        type_3D3548 *r = unk_00;
        return r;
    }
};
typedef RwChar type_4B8600_size_check[sizeof(type_4B8600) == 0x10 ? 1 : -1];

#endif
