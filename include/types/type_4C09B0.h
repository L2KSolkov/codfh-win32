/*
 * type_4C09B0: a pickup's settings (0x24 bytes), 110 of them at
 * dword_4C09B0; sub_FB6C0 returns one by index (0 outside 0 to 109).
 * CPickupBehavior's HandleAttributes (sub_C5F80) fills one from its commands;
 * only the fields it writes are known.
 */
#ifndef TYPE_4C09B0_H
#define TYPE_4C09B0_H

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "types/type_3DF8D8.h"

struct type_4C09B0
{
    RwUInt8 unk_00;             // set while in use
    RwUInt8 unk_01[0x3];
    type_3DF8D8_04 unk_04;      // its named object's key (the pickup's
                                // vf_058 matches it)
    union
    {
        RwInt32 unk_0C;         // command 1
        RwReal unk_0C_f;        // 15.0 by default
    };
    RwV3d unk_10;               // command 2
    type_3DF8D8_04 unk_1C;      // command 3: a name's key

    // Out of line (sub_FB5B0) for the table's dynamic initializer.
    type_4C09B0();
    // Out of line (sub_FB640): the table's exit function passes it to the
    // vector destructor iterator.
    ~type_4C09B0();
    // Clears it and marks it used (sub_FB660) or unused (sub_FB690).
    bool sub_FB660();
    bool sub_FB690();
    // Returns true; /OPT:ICF folded it into another class's (0x2015D0).
    bool sub_2015D0();
};
typedef RwChar type_4C09B0_size_check[sizeof(type_4C09B0) == 0x24 ? 1 : -1];

extern type_4C09B0 dword_4C09B0[0x6E];

// Pickup settings arg_0 (0 outside 0 to 109).
type_4C09B0 *sub_FB6C0(RwInt32 arg_0);
// The table's set-up, a pass the image folds to true, and restart
// (src/recovered/unit_0FA9E0.cpp).
void sub_FB4F0();
void sub_FB530();
void sub_FB570();

#endif
