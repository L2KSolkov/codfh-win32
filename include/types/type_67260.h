/*
 * type_67260: a 0x50-byte record built by its constructor sub_67260, named
 * for it; sub_F4890, sub_116870, sub_11DB10 (at +0x188 of its object),
 * sub_11E4A0, sub_15B150, sub_15C810 and sub_1AE8F0 build one. Only what
 * the constructor clears is known.
 */
#ifndef TYPE_67260_H
#define TYPE_67260_H

#include <string.h>
#include "rw/ostypes.h"

struct type_67260
{
    RwUInt16 unk_00;        // 1 once built
    RwUInt16 unk_02;
    union
    {
        RwInt32 unk_04;
        RwReal unk_04_r;    // a vehicle gun's damage (the tank's vf_2A8)
    };
    // Dwords, not bytes: the triggered particles' update (sub_F4890) keeps
    // one on its stack with no /GS cookie.
    RwInt32 unk_08[0xC];
    RwInt32 unk_38;         // a vehicle gun's model last fired
    RwInt32 unk_3C;
    union
    {
        RwInt32 unk_40;
        RwReal unk_40_r;    // the shells' generator (type_11E440) copies its
                            // trigger's unk_204 here
    };
    union
    {
        RwInt32 unk_44;
        RwReal unk_44_r;    // a thrown grenade's (the grenade handler, sub_1AE8F0)
    };
    RwInt32 unk_48;
    union
    {
        RwInt32 unk_4C;
        RwReal unk_4C_r;    // the generators copy their trigger's unk_194
    };

    type_67260();
};
typedef RwChar type_67260_size_check[sizeof(type_67260) == 0x50 ? 1 : -1];

// A 0x38-byte record, a bullet's settings as sub_15F2C0 takes them (its
// table 0): the weapon's at +0x29C and +0x2D4, built inline (sub_116870),
// and the bullets' generator's (type_11DB10); named for its first place.
// Only what the constructor clears is known.
struct type_10F710_1A48_29C
{
    RwUInt16 unk_00;
    RwUInt8 unk_02[0x2];
    union
    {
        RwInt32 unk_04;
        RwReal unk_04_r;        // the mounted weapon's fire (sub_169380)
    };                          // sets it from its settings' unk_1C
    RwUInt8 unk_08[0x30];

    type_10F710_1A48_29C()
    {
        unk_00 = 0;
        unk_04 = 0;
        memset(unk_08, 0, sizeof(unk_08));
    }
};

#endif
