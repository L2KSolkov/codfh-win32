/*
 * The weapon banks (unit_16F2C0): WPNBANK\0_25 and 26_50\wbank_NN.bin, the
 * clump banks' scheme (game/clumpbank.h) for three slots at once: each
 * slot's loaded bank (dword_4E54D0, -1 for none), the bank requested for it
 * (dword_4E54DC), the level's (dword_4E54E8, LevelClumpBankParamTrigger), its
 * heap (dword_4E54F4), its state (dword_4E5518: a count in the high half and
 * a load in progress in the low) and its table of eight keys
 * (dword_4E5528).
 */
#ifndef GAME_WEAPONBANK_H
#define GAME_WEAPONBANK_H

#include "rw/ostypes.h"
#include "rw/bastream.h"
#include "game/clumpbank.h"

extern RwInt32 dword_4E54D0[3];
extern RwInt32 dword_4E54DC[3];
extern RwInt32 dword_4E54E8[3];
extern type_4E51B8 dword_4E54F4[3];
extern RwInt32 dword_4E5518[3];
extern type_4E51D0 dword_4E5528[3][8];

// A slot's state from its halves; an inline with no address and so no
// database name, named for what it makes. Evidence: the loads build it
// from constants at run time (`xor; shl 0x10; add 1`), which only an
// inlined function's substituted parameters leave unfolded.
inline RwInt32 make_bank_state(RwInt32 arg_0, RwInt32 arg_4)
{
    return (arg_0 << 16) + arg_4;
}
// A slot's state through a local of its own (the loads test it through a
// temporary).
inline RwInt32 get_bank_state(RwInt32 arg_0)
{
    RwInt32 r = dword_4E5518[arg_0];
    return r;
}

// Sets the slot arg_0's state from a count arg_4 and a load arg_8; an inline
// with no address and so no database name, named for what it does.
// Evidence: the player's step stores the slot into a temporary before the
// state, and widens a count from a byte (a substituted 8-bit argument).
inline void set_bank_state(RwInt32 arg_0, RwInt8 arg_4, RwInt32 arg_8)
{
    dword_4E5518[arg_0] = (arg_4 << 16) + arg_8;
}
// Clears the slot arg_0's state when its count (the high half) is arg_4;
// an inline with no address and so no database name, named for what it
// does. Evidence: the loader (sub_16F460) loads the count before the state
// (`xor eax, eax`) and branches on the compare: a substituted 16-bit
// argument, whose widening keeps the constant from folding (an int one
// folds into the compare).
inline void clear_bank_state(RwInt32 arg_0, RwInt16 arg_4)
{
    if (arg_4 == dword_4E5518[arg_0] >> 16)
        dword_4E5518[arg_0] = 0;
}
// Sets the slot arg_0's heap size; an inline with no address and so no
// database name, named for what it sets. Evidence: sub_16FF00 computes the
// slot's address before the size (a substituted argument).
inline void set_bank_size(RwInt32 arg_0, RwUInt32 arg_4)
{
    dword_4E54F4[arg_0].unk_08 = arg_4;
}

void sub_16F2C0(RwInt32 arg_0, RwInt32 arg_4);
void sub_16F3E0(RwInt32 arg_0, RwInt32 arg_4);
void sub_16F460(RwStream *arg_0, RwInt32 arg_4, RwInt32 arg_8);
type_4E51D0 *sub_16F750(void *arg_0, type_3DF8D8_04 *arg_4, RwInt32 arg_8);
void sub_16F770(RwChar *arg_0, RwInt32 arg_4, RwInt32 arg_8);
RwInt32 sub_16F860(RwInt32 arg_0);
RwInt32 sub_16F8A0(RwInt32 arg_0);
RwInt32 sub_16F8E0(RwInt32 arg_0, RwInt32 arg_4);
RwInt32 sub_16F900(RwInt32 arg_0, RwInt32 arg_4);
RwInt32 sub_16FA60(RwInt32 arg_0);
RwInt32 sub_16FAC0(RwInt32 arg_0);
void sub_16FAE0(RwInt32 arg_0);
void sub_16FC80();
void sub_16FD10();
void sub_16FD60();
type_4E51D0 *sub_16FDA0(RwInt32 arg_0);
type_4E51D0 *sub_16FE00(RwInt32 arg_0, type_3DF8D8_04 *arg_4, RwInt32 arg_8);
RwInt32 sub_16FE40(RwInt32 arg_0, RwUInt32 arg_4);
RwInt32 sub_16FE80(RwUInt32 arg_0);
void sub_16FF00(RwUInt32 arg_0);
RwInt32 sub_16FF40();

#endif
