/*
 * The AIHearing class ("Somebody forgot to unregister in the AIHearing
 * Class!", sub_3C290): listeners (type_3C720) and lasting sounds
 * (type_3C540), each drawn from a pool ("m_freeHearingParams",
 * "m_freeLongSound") and kept in a list; a listener that hears a sound gets
 * "AIAction_HearSound" with a type_3C7D0_1C.
 */
#ifndef TYPE_3C540_H
#define TYPE_3C540_H

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "types/type_D48D0.h"

struct type_3D3548;

// type_3C720: a listener, 12 bytes, named after sub_3C720, which registers
// one.
struct type_3C720
{
    type_3D3548 *unk_00;    // the listening entity
    RwInt32 unk_04;         // set once it has heard a sound this update
    type_3C720 *unk_08;     // the next listener
};

// Registers and unregisters the entity arg_0 as a listener (unit_03C1D0).
void sub_3C720(type_3D3548 *arg_0);
void sub_3C760(type_3D3548 *arg_0);

// type_3C540: a lasting sound, 36 bytes, named after sub_3C540, which
// registers one.
struct type_3C540
{
    RwInt32 unk_00;         // its id (sub_3C6C0 removes by it)
    RwReal unk_04;          // the time left, for a timed sound
    RwV3d *unk_08;          // where it is
    type_D48D0 unk_0C;      // the entity making it
    RwInt32 unk_10;         // its kind (1 for a player, 2 for type_3DAFC8)
    RwInt32 unk_14;         // its class
    RwReal unk_18;          // its range
    RwUInt32 unk_1C_0 : 1;  // timed
    RwUInt32 unk_1C_1 : 1;  // loud (heard before the others)
    RwUInt32 unk_1C_2 : 1;  // seen by one update (sub_8A950 decides when
                            // an untimed sound ends)
    type_3C540 *unk_20;     // the next sound
};

// type_3C7D0_1C: what "AIAction_HearSound" carries (7 dwords), a local at
// ebp-0x1C in sub_3C7D0: the sound's class and kind, the source's side and
// handle, and the point.
struct type_3C7D0_1C
{
    RwInt32 unk_00;
    RwInt32 unk_04;
    RwInt32 unk_08;
    RwUInt32 unk_0C;
    RwV3d unk_10;
};

#endif
