/*
 * The control sets' button tables (unit_19B0F0; set up by the pads'
 * library, sub_19DF40): dword_4F2AAC points at five of them.
 */
#ifndef GAME_LEVELS_H
#define GAME_LEVELS_H

#include "rw/ostypes.h"

// A control set's rows (0x20 bytes, ended by -1): an input (dword_42C5D8's
// index), how many of the pad manager's buttons it drives, those buttons,
// and whether button 5 is among them (sub_19B0F0; it negates the input,
// sub_19DE30).
struct type_42B740
{
    RwInt32 unk_00;
    RwInt32 unk_04;
    RwInt32 unk_08[5];
    RwInt32 unk_1C;
};
extern type_42B740 dword_42B740[];
extern type_42B740 dword_42BA20[];
extern type_42B740 dword_42BD00[];
extern type_42B740 dword_42BFE0[];
extern type_42B740 dword_42C2C0[];
extern type_42B740 *dword_4F2AAC[5];

// The stopwatch's state (sub_19B9E0): its frequency's inverse is taken once.
extern RwInt32 dword_4F30D0;
extern RwReal flt_4F30CC;
extern RwReal flt_4F30C8;       // when it started
extern RwReal flt_4F30C4;       // when it was paused

// What the front end's sub_20AD30 hands sub_19BE30: only its flags for the
// controllers that are in are known.
struct type_19BE30
{
    RwUInt8 unk_00[0x690];
    RwInt32 unk_690[4];
};
RwInt32 sub_19BE30(type_19BE30 *arg_0);

void sub_19B0F0();
type_42B740 *sub_19B1E0(RwInt32 arg_0);

#endif
