/*
 * type_439E78: the entries of the handle table dword_439E78 (0x1444 of
 * them, 12 bytes each), named for the table. sub_673C0 registers an object
 * under a new handle, sub_67620 resolves one and sub_67520 releases one.
 *
 * A handle (type_439E78_00) is an entry's index in its low half and a
 * serial (dword_428A30, counting registrations from 1) in its high half, so
 * a released handle stops resolving once its entry is reused. The last four
 * indices released (dword_4491AC, a ring at dword_4491A8) are reused first.
 */
#ifndef TYPE_439E78_H
#define TYPE_439E78_H

#include "rw/ostypes.h"

struct type_67620;

struct type_439E78_00
{
    RwUInt16 unk_00;        // the entry's index
    RwUInt16 unk_02;        // the serial

    // The handle as a word: an inline with no address and so no database
    // name. Evidence: type_3D2DB8::sub_6EFD0 passes a task's handles to
    // sub_67620 through a return temporary each.
    operator RwUInt32()
    {
        return *(RwUInt32 *)this;
    }
};

struct type_439E78
{
    union
    {
        RwUInt32 unk_00;    // the handle registered here, 0 when free
        type_439E78_00 unk_00_h;
    };
    RwUInt8 unk_04;         // the object's kind (1 to 4), picking how
                            // sub_67520 destroys it
    type_67620 *unk_08;     // the object
};
typedef RwChar type_439E78_size_check[sizeof(type_439E78) == 0xC ? 1 : -1];

// sub_673C0, sub_67520: register arg_0 (of kind arg_4) under a new handle,
// and release the handle arg_0 (unit_067260).
RwUInt32 sub_673C0(type_67620 *arg_0, RwInt32 arg_4);
void sub_67520(RwUInt32 arg_0);

#endif
