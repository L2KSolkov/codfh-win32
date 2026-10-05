/*
 * type_4AE70: a blast request for sub_9A960, 0x34 bytes, anchored at its
 * out-of-line constructor sub_4AE70 (it zeroes every field, the handle at +4
 * through its own inline constructor). "PlayParticleSystemAtXYZ" (sub_4AB90)
 * builds one on the stack for the explosive particle systems, and
 * "CreateExplosionZone" (sub_4B490) for a blast of its own. The remote
 * grenade hit (sub_1AD0F0) builds one to hand the players' network parts;
 * it has the layout of an explosion's hit (type_758F0, types/type_3D32F8.h).
 *
 *   +0x00 unk_00  flags (0x804 from sub_4AB90; 0x801, 0x802 or 0x804 from
 *                 sub_4B490)
 *   +0x04 unk_04  handle to an entity
 *   +0x0C unk_0C  the matrix whose position is the centre
 *   +0x10 unk_10  three radii; sub_9A960 takes the largest
 *   +0x1C unk_1C  an offset sub_9A960 adds to the centre
 */
#ifndef TYPE_4AE70_H
#define TYPE_4AE70_H

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "types/type_D48D0.h"

struct type_4AE70
{
    type_4AE70();
    // Empty; out of line it is pDtor (0x1E41C0), folded by /OPT:ICF: the
    // unwind funclet of sub_4AB90 calls it, the normal path drops it.
    ~type_4AE70()
    {
    }

    RwUInt32 unk_00;
    type_D48D0 unk_04;
    RwInt32 unk_08;
    RwMatrix *unk_0C;
    RwReal unk_10;
    RwReal unk_14;
    RwReal unk_18;
    RwV3d unk_1C;
    RwInt32 unk_28;
    RwReal unk_2C;          // 200.0 from sub_4AB90
    RwInt32 unk_30;
};
typedef RwChar type_4AE70_size_check[sizeof(type_4AE70) == 0x34 ? 1 : -1];

// Sets off the blast arg_0 (damage around its centre).
void sub_9A960(type_4AE70 *arg_0);

#endif
