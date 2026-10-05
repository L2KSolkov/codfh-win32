/*
 * The light scales (unit_19B0F0's dword_4F30A8), apart from game/clones.h so
 * that units without Direct3D's headers (the debug menu's, unit_183130) can
 * reach them.
 */
#ifndef GAME_LIGHTSCALES_H
#define GAME_LIGHTSCALES_H

#include "rw/ostypes.h"

// The light scales (0x18 bytes, dword_4F30A8, built by its dynamic
// initializer with sub_19B220): the ambient's and the lights' colours are
// scaled by unk_00 and unk_04 (sub_19B270).
struct type_4F30A8
{
    RwReal unk_00;
    RwReal unk_04;
    RwReal unk_08;
    RwReal unk_0C;
    RwReal unk_10;
    RwReal unk_14;

    type_4F30A8();
};
extern type_4F30A8 dword_4F30A8;

#endif
