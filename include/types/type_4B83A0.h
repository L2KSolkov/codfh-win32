/*
 * type_4B83A0: the entity pools (the image's GameEntityPool, from its warning
 * "GameEntityPool:: %d was not empty at restart!"), the 0x34-byte records of
 * dword_4B83A0 (nine of them; the type is named after that array), one per
 * entity size. sub_D5320 sets each up from the size and count table
 * dword_3D7130 (or the counts it is given); the entities come out of their
 * pool's type_16C2A0 at +0x14, and type_3D3548::unk_20 records which pool.
 */
#ifndef TYPE_4B83A0_H
#define TYPE_4B83A0_H

#include "rw/ostypes.h"
#include "types/alfasched.h"

struct type_4B83A0
{
    RwInt32 unk_00;             // the entity size
    RwInt32 unk_04;             // how many
    RwInt32 unk_08;             // set up
    RwInt32 unk_0C;             // its index (10 when not set up)
    RwInt32 unk_10;             // how many are out
    type_16C2A0 unk_14;

    // sub_D63F0 and sub_D6440: the array's constructor and destructor run
    // them on each record.
    type_4B83A0();
    ~type_4B83A0();
    // Clears the record (the index back to 10).
    void sub_D6460();
    // Sets the pool arg_0 up for arg_8 entities of arg_4 bytes (a pool with
    // no entities when arg_8 is 0); returns 1.
    RwInt32 sub_D64A0(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8);
    // Warns when entities are still out.
    void sub_D6550();
    // Shuts the pool down.
    void sub_D65A0();
    // An entity's memory, or 0 when the pool is full.
    void *sub_D65C0();
    // Returns the entity memory arg_0.
    void sub_D6600(void *arg_0);
};
typedef RwChar type_4B83A0_size_check[sizeof(type_4B83A0) == 0x34 ? 1 : -1];
extern type_4B83A0 dword_4B83A0[9];

// Record arg_0: an inline with no address and so no database name, named
// for its array. Evidence: GimpTrigger's vf_020 computes the constant
// record's place at run time, as get_pool's callers do.
inline type_4B83A0 &get_4B83A0(RwInt32 arg_0)
{
    return dword_4B83A0[arg_0];
}

// The pools' entity sizes and counts (sub_D5320).
struct type_3D7130
{
    RwInt32 unk_00;             // the entity size
    RwInt32 unk_04;             // how many
};
extern const type_3D7130 dword_3D7130[];

#endif
