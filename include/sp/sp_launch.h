/*
 * sp_launch.h: single player's view of the launch data (dword_4F45F8, SP .bss 0x3EC3B0).
 * Only the fields the save load and the front end read are known.
 */
#ifndef SP_LAUNCH_H
#define SP_LAUNCH_H

#include "rw/ostypes.h"

struct sp_type_3EC3B0
{
    RwInt32 unk_00;
    RwInt32 unk_04;
    RwInt32 unk_08;
    RwInt32 unk_0C;
    RwInt32 unk_10;             // set: launched by the multiplayer image (no intro)
    RwInt32 unk_14;             // the profile slot to load
    RwInt32 unk_18;             // set: straight into the level unk_1C
    RwInt32 unk_1C;
    RwInt32 unk_20;
    RwInt32 unk_24;             // passed to sp_sub_B6A10 at start-up (SP 0xA5C60)
};
// The launch data is dword_4F45F8's (unit_19CB20, SP .bss 0x3EC3B0): single player reads it
// through this view, ((sp_type_3EC3B0 *)dword_4F45F8).
struct type_4F45F8;
extern type_4F45F8 *dword_4F45F8;

#endif
