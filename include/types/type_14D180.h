/*
 * type_14D180: the 44-byte records type_3DBC78 holds at +0x263C (12 of
 * them), anchored at their constructor sub_14D180, which only type_3DBC78's
 * constructors (sub_1555A0, sub_14C930) pass to the compiler's `eh vector
 * constructor iterator'. The constructor zeroes the handle at +0x10.
 *
 *   +0x00 unk_00  flags: sub_23980 requires bits 0 and 1, sub_23050 tests bit 2
 *   +0x10 unk_10  handle to an entity
 *   +0x14 unk_14  a point: AIData::sub_1FA00 measures the owner's distance to it
 */
#ifndef TYPE_14D180_H
#define TYPE_14D180_H

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "rw/bamatrix.h"
#include "types/type_D48D0.h"

// A cover point's node in its vehicle's model: a bone (or, without a skin,
// a node frame) unk_04 and the offset unk_10 from it (sub_154EA0).
struct type_14D180_0C
{
    RwInt32 unk_00;
    RwInt32 unk_04;
    RwUInt8 unk_08[0x8];
    RwMatrixTag unk_10;
};

struct type_14D180
{
    union
    {
        RwUInt32 unk_00;
        struct
        {
            RwUInt32 unk_00_0 : 1;  // enabled ("EnableVehicleCoverPoints",
                                    // sub_154E30)
            RwUInt32 unk_00_1 : 1;  // clear: no wall between it and the
                                    // vehicle, and it is not moving toward
                                    // it too fast (sub_154EA0)
            RwUInt32 unk_00_2 : 30;
        };
    };
    RwInt32 unk_04;         // with unk_08, copied into a type_154C0_12F4
    RwInt32 unk_08;         // record's unk_00 / unk_04 by AIData::sub_24BA0;
                            // unk_08 is also a tag in the vehicle's clump
                            // (sub_1553E0)
    struct type_14D180_0C *unk_0C;  // its node in the vehicle's model
                                    // (sub_14D2C0; sub_154E30 skips records
                                    // without one)
    type_D48D0 unk_10;
    RwV3d unk_14;
    RwV3d unk_20;           // a facing: AIData::sub_28890 dots it with the
                            // direction from the cover point to an entity

    type_14D180();
};
typedef RwChar type_14D180_size_check[sizeof(type_14D180) == 0x2C ? 1 : -1];

#endif
