/*
 * The cheat flags (from game/startup.h, for units that cannot include it):
 * dword_4B8888 points at them.
 */
#ifndef GAME_CHEATS_H
#define GAME_CHEATS_H

#include "rw/ostypes.h"

extern RwUInt8 *dword_4B8888;
// The cheat flags as dword_4B8888 points at them, named after it: bit 4
// shrinks soldiers with their hit points (type_3DAFC8::sub_13C490 reads it
// as a bitfield); 2 and 5 are bullet damage cheats.
struct type_4B8888
{
    RwUInt32 unk_00_0 : 1;      // soldiers' second animation at double speed
                                // (type_3DAFC8::vf_04C)
    RwUInt32 unk_00_1 : 1;
    RwUInt32 unk_00_2 : 1;      // bullets kill with a head shot and do
                                // nothing otherwise (type_3DAFC8::vf_064)
    RwUInt32 unk_00_3 : 1;
    RwUInt32 unk_00_4 : 1;
    RwUInt32 unk_00_5 : 1;      // bullets kill (type_3DAFC8::vf_064)
    RwUInt32 unk_00_6 : 1;      // soldiers drawn smaller, at random
                                // (type_3DAFC8::sub_135430)
};

#endif
