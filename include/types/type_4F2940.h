/*
 * type_4F2940: a record no code reads (0x4F2940, defined in unit_19AAB0).
 */
#ifndef TYPE_4F2940_H
#define TYPE_4F2940_H

#include <string.h>
#include "rw/ostypes.h"

// A record no code reads (0x4F2940): 8 bytes cleared and a word of -1,
// set by its inline constructor through a pointer of its own (the
// initializer keeps it in a slot). Named after its address.
struct type_4F2940
{
    RwUInt8 unk_00[8];
    RwInt32 unk_08;

    type_4F2940()
    {
        type_4F2940 *m = this;

        memset(m, 0, sizeof(m->unk_00));
        m->unk_08 = -1;
    }
};

#endif
