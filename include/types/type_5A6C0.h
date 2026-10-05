/*
 * type_5A6C0: a ring-mounted gun, named after the one command known to use
 * it, "AttachRingMountGunToGunner" (sub_5A6C0); only what that command sets
 * is known.
 */
#ifndef TYPE_5A6C0_H
#define TYPE_5A6C0_H

#include "rw/ostypes.h"
#include "types/type_3D3548.h"

struct type_5A6C0 : type_3D3548
{
    RwUInt8 unk_3A8[0x77C];
    RwReal unk_B24;             // its turn towards its gunner, in degrees
};

#endif
