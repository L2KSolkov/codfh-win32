/*
 * The game's save state (unit_19AAB0): the state object byte_4F2908 that
 * dword_4F28F0 points at once it is set up (game/data.h's type_4F28F0), what
 * the shell hands it (dword_4F45F8), and the difficulty's multipliers.
 */
#ifndef GAME_SAVESTATE_H
#define GAME_SAVESTATE_H

#include "rw/ostypes.h"
#include "game/data.h"
#include "types/type_DA0A0.h"

// The shell's settings for the game it starts (dword_4F45F8, the front end
// fills it); only what sub_19AD20 hands the state is known.
struct type_4F45F8
{
    RwInt32 unk_00;             // set to 1 by the dashboard's launch
    RwUInt8 unk_04[0xC];
    RwInt32 unk_10;             // set: no files are read ahead (sub_19CDE0)
    RwInt32 unk_14;             // the profile (unk_4F5DD8's index)
    RwInt32 unk_18;             // cleared by the dashboard's launch
    RwUInt8 unk_1C[0x4];
    RwInt32 unk_20;             // set: the state keeps its defaults
    RwInt32 unk_24;             // the player's pad
    RwInt32 unk_28;             // the language
    RwInt32 unk_2C;
    RwInt32 unk_30;
    RwInt32 unk_34;             // the difficulty
    RwInt32 unk_38;             // set: the friend (unk_434) is to be joined
                                // after signing in (the late service)
    RwInt32 unk_3C;             // set: the multiplayer manager's leave
                                // (sub_1AA320) does nothing
    RwUInt8 unk_40;             // Xbox Live was chosen (the manager signs
                                // in again after a failure, sub_19BF20)
    RwUInt8 unk_41[0x3];
    type_4F5DC0 unk_44[4];      // the profiles' slots (sub_1A2650 and
                                // sub_1A2680 copy them out and back)
    RwInt32 unk_394;
    RwUInt8 unk_398[0x9C];      // an accepted game invite (the late service
                                // signs in with it)
    RwUInt8 unk_434[0x56];      // the friend whose session is joined
    RwUInt8 unk_48A[0x216];     // the Xbox Live logon state (the dashboard's
                                // launch, sub_20AD30, saves it)
};
typedef RwChar type_4F45F8_size_check[sizeof(type_4F45F8) == 0x6A0 ? 1 : -1];
// A profile (0xD4 bytes); only its name at +0 is known.
struct type_4F5DD8
{
    RwChar unk_00[0xD4];
};

extern type_4F45F8 *dword_4F45F8;
#ifdef CODFH_PLAIN
extern type_4F5DD8 (&unk_4F5DD8)[1];
#else
extern type_4F5DD8 unk_4F5DD8[];
#endif
extern type_4F28F0 byte_4F2908;     // the state itself
extern RwInt32 dword_4F28F4;        // the level (sub_19B050)
extern RwInt32 dword_4F28FC;        // the language before there is a state
extern RwInt32 dword_4F2900;        // the state is set up
#ifdef CODFH_PLAIN
extern RwInt32 &dword_4B9E5C;
#else
extern RwInt32 dword_4B9E5C;
#endif
extern RwUInt8 byte_4F28F8;

// The difficulty's multipliers, three each (sub_19AAB0 sets every one to 1).
extern RwReal flt_4F2860[3];
extern RwReal flt_4F286C[3];
extern RwReal flt_4F2878[3];
extern RwReal flt_4F2884[3];
extern RwReal flt_4F2890[3];
extern RwReal flt_4F289C[3];
extern RwReal flt_4F28A8[3];
extern RwReal flt_4F28B4[3];
extern RwReal flt_4F28C0[3];
extern RwReal flt_4F28CC[3];
extern RwReal flt_4F28D8[3];
extern RwReal flt_4F28E4[3];

// Sets the difficulty arg_4's entry of the multipliers arg_0 (three
// difficulties). Evidence: the shell's HandleAttributes (sub_B0980) bounds
// the constant index both ways after storing the value into a temporary.
inline void set_multiplier(RwReal *arg_0, RwInt32 arg_4, RwReal arg_8)
{
    if (arg_4 > -1 && arg_4 < 3)
        arg_0[arg_4] = arg_8;
}

void sub_19AAB0();
void sub_19AD20();
void sub_19B000(RwInt32 arg_0);
RwInt32 sub_19B050();
const RwChar *sub_19B060(RwInt32 arg_0);
RwInt32 sub_19B080();
RwInt32 sub_19B0A0();
void sub_19B0C0(RwInt32 arg_0);

#endif
