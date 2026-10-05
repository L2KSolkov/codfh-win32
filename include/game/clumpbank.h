/*
 * The clump banks (unit_16E9C0): cbank_NN.bin files of clumps by key, one
 * bank loaded at a time (dword_4E51C4, -1 for none) into a memory heap of
 * its own (dword_4E51B8), with a table of the keys it made (dword_4E51D0)
 * so they can be unloaded together. Loads are synchronous (sub_16E9E0,
 * sub_16EAB0) or queued on the loading thread (sub_16EEC0).
 */
#ifndef GAME_CLUMPBANK_H
#define GAME_CLUMPBANK_H

#include "rw/ostypes.h"
#include "rw/bastream.h"
#include "rw/batextur.h"
#include "types/type_3DF8D8.h"
#include "types/type_141C10.h"

// The heap the bank's clumps are made in: its base, the bytes used, and its
// size (dword_4E51C0, LevelClumpBankParamTrigger's command 1).
struct type_4E51B8
{
    RwUInt32 unk_00;
    RwInt32 unk_04;
    RwUInt32 unk_08;
};

// A key the bank made, and its kind (3 a clump, 6, 7 one holding a texture
// dictionary at +0x24).
struct type_4E51D0
{
    type_3DF8D8_04 unk_00;
    RwInt32 unk_08;
};

// A bank file's directory entry: a clump's key and the bytes of its data.
struct type_16EAE0
{
    type_3DF8D8_04 unk_00;
    RwInt32 unk_08;
    RwInt32 unk_0C;
};

// The file's header: its entries.
struct type_16EAE0_hdr
{
    RwInt32 unk_00;
    RwInt32 unk_04;
};

// A clump object (kind 3) as the bank sees it: read by its first virtual,
// its heap and the callback that records the keys it makes.
struct type_16EAE0_obj_10
{
    type_4E51B8 *unk_00;
    RwInt32 unk_04;
    RwInt32 unk_08;
    type_4E51D0 *(*unk_0C)(void *arg_0, type_3DF8D8_04 *arg_4, RwInt32 arg_8);

    // Sets the callback and the value it is given (the weapon banks' slot);
    // an inline with no address and so no database name, named for its
    // field. Evidence: the bank loaders (sub_16EAE0, sub_16F460) reach both
    // through a `this` temporary allocated after their record's constructor
    // temporaries.
    void set_unk_0C(type_4E51D0 *(*arg_0)(void *arg_0, type_3DF8D8_04 *arg_4, RwInt32 arg_8), RwInt32 arg_4)
    {
        unk_0C = arg_0;
        unk_04 = arg_4;
    }
};
struct type_16EAE0_obj
{
    virtual void vf_000(RwStream *arg_0, type_141C10 *arg_4);
    RwUInt8 unk_04[0x8];
    RwInt16 unk_0C;
    RwUInt8 unk_0E[0x2];
    type_16EAE0_obj_10 unk_10;
    RwUInt8 unk_20[0x4];
    RwTexDictionary *unk_24;
};

extern type_4E51B8 dword_4E51B8;

// Sets the heap's size to arg_0, 32-aligned; an inline with no address and
// so no database name, named for what it sets. Evidence: the world
// manager's sub_172A80 clears it as `xor; and 0xFFFFFFE0` (a substituted
// argument).
inline void set_clump_heap_size(RwUInt32 arg_0)
{
    dword_4E51B8.unk_08 = arg_0 & ~0x1F;
}
extern RwInt32 dword_4E51C4;
extern RwInt32 dword_4E51C8;
extern type_4E51D0 dword_4E51D0[64];

void sub_16E9C0();
void sub_16E9E0(RwInt32 arg_0);
void sub_16EAB0(RwInt32 arg_0);
void sub_16EAE0(RwStream *arg_0, RwInt32 arg_4);
type_4E51D0 *sub_16ED90(void *arg_0, type_3DF8D8_04 *arg_4, RwInt32 arg_8);
void sub_16EDB0(RwChar *arg_0, RwInt32 arg_4, RwInt32 arg_8);
RwInt32 sub_16EE80(RwInt32 arg_0);
RwInt32 sub_16EEA0();
void sub_16EEC0(RwInt32 arg_0);
RwInt32 sub_16EF70();
void sub_16EFD0();
void sub_16F160();
void sub_16F1C0();
void sub_16F1D0();
type_4E51D0 *sub_16F200();
type_4E51D0 *sub_16F250(type_3DF8D8_04 *arg_0, RwInt32 arg_4);
RwInt32 sub_16F280(RwUInt32 arg_0);

// Elsewhere: the entity manager's notice that an asset is going
// (NotificationOfGodAssetTermination), the key's object removed, and the
// loading queue's requests (types/asynchload.h).
void sub_D61F0(type_3DF8D8_04 *arg_0);
void sub_198F00(type_3DF8D8_04 *arg_0);
void sub_81EB0(RwInt32 arg_0, const RwChar *arg_4, RwInt32 arg_8);

#endif
