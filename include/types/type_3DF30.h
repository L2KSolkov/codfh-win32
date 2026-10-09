/*
 * type_3DF30: a squad ("m_freeSquadList", sub_3EC40), anchored at its
 * constructor sub_3DF30 (no vtable, returns this). 0x2E0 bytes, the pool's
 * element size. sub_3EEE0 builds one in a pool slot, gives it an id
 * (sub_3DF90) and puts it at the head of the squad list dword_4395F0.
 *
 *   +0x000 unk_00   the squad's first entity; the entities are listed through
 *                   their vf_118 / vf_11C
 *   +0x004 unk_04   the context its objects get (type_3D410)
 *   +0x2A8 unk_2A8  the handle of its first object (type_3CE6D0); the objects
 *                   are listed through their unk_14, by priority (sub_3E2C0)
 *   +0x2AC unk_2AC  the next squad in the list dword_4395F0
 *   +0x2B0 unk_2B0  its side: the first entity's unk_2C & 7 (sub_3E650)
 *   +0x2B4 unk_2B4  its id (sub_3EEE0 hands out dword_4395F4); an entity's
 *                   AIData::unk_570 keeps it (sub_17030), sub_3F080 finds it
 *   +0x2B8 unk_2B8  zeroed by sub_3DF90; only its width is known
 *   +0x2BC unk_2BC  handle to an entity (AIData::sub_170C0 reads it; set by
 *                   sub_3E780)
 *   +0x2C0 unk_2C0  per kind (7), whether the squad keeps an object of that
 *                   kind (sub_3EA20; sub_3E3B0 does not drop them)
 *   +0x2DC unk_2DC  a mask of kinds (sub_3EB80), handed to sub_3D150
 */
#ifndef TYPE_3DF30_H
#define TYPE_3DF30_H

#include "rw/ostypes.h"
#include "types/type_D48D0.h"
#include "types/type_3D410.h"
#include "types/type_365A0.h"

struct type_3D3548;
struct type_3CE6D0;

struct type_3DF30
{
    type_3D3548 *unk_00;
    type_3D410 unk_04;
    union
    {
        RwUInt32 unk_2A8;
        type_365A0 unk_2A8_h;   // the same as a handle (sub_3E2C0, sub_3E3B0)
    };
    type_3DF30 *unk_2AC;
    RwInt32 unk_2B0;
    RwInt32 unk_2B4;
    RwInt32 unk_2B8;
    type_D48D0 unk_2BC;
    RwInt32 unk_2C0[7];
    RwInt32 unk_2DC;

    type_3DF30();
    // Lets the entities and the objects go; sub_3EFB0 calls it before
    // freeing the squad's slot (not a destructor: it has no unwind frame).
    void sub_3E0A0();
    // Sets the squad up with the id arg_0 and its first objects: kinds 0,
    // 6, 4 and 3.
    void sub_3DF90(RwInt32 arg_0);
    // The update, with the time step arg_0.
    void sub_3E180(RwReal arg_0);
    // Adds the object with handle arg_0, keeping the list in priority order.
    void sub_3E2C0(type_365A0 arg_0);
    // Drops the object with handle arg_0 unless unk_2C0 keeps its kind; the
    // entities it had go to the first object that takes them on (sub_3D150
    // passes those whose update test fails). Stays binary (docs/units.md).
#ifdef CODFH_SP // single player passes the handle struct (SP 0x2E80D, 0x2F78F)
    void sub_3E3B0(type_365A0 arg_0);
#else
    void sub_3E3B0(RwUInt32 arg_0);
#endif
    // Calls arg_4 with each member entity and arg_C, for the members whose
    // object ranks below arg_0's (by vf_02C) or who have none, with
    // AIData::unk_51C set, a unk_2C bit in arg_8 and flag 4 of
    // AIData::unk_49C.
    void sub_3E570(type_3CE6D0 *arg_0, void (*arg_4)(type_3D3548 *, void *), RwInt32 arg_8,
                   void *arg_C);
    // Adds the entity arg_0 at the head of the list; with arg_4, the first
    // object that takes it on (vf_018) gets it.
    void sub_3E650(type_3D3548 *arg_0, RwInt32 arg_4);
    // How well the entity arg_0 fits the squad: -1 for another side, else 1.
    RwInt32 sub_3E710(type_3D3548 *arg_0);
    void sub_3E780(type_3D3548 *arg_0);
    // Removes the entity arg_0 from the squad (AIData::sub_17080 passes the
    // AI object's owner).
    void sub_3E7C0(type_3D3548 *arg_0);
    // Adds an object of kind arg_0 unless the squad has one.
    void sub_3E8F0(RwInt32 arg_0);
    // Has the object of kind arg_4 (added if missing) take on the entity
    // arg_0 (vf_01C).
    void sub_3E990(type_3D3548 *arg_0, RwInt32 arg_4);
    // Sets whether the squad keeps an object of kind arg_0 (arg_4), adding
    // one when it does; type_3CE5E8::vf_010 passes its own kind.
    void sub_3EA20(RwInt32 arg_0, RwInt32 arg_4);
    // Hands the point arg_0 to the squad's kind-5 object (sub_3A170).
    void sub_3EA50(RwV3d *arg_0);
    // Sets the kind-5 object's range to arg_0 (and its outer range to
    // arg_0 + 500), with their squares.
    void sub_3EAD0(RwReal arg_0);
    // Sets or clears (arg_0) kind arg_4 in unk_2DC and passes arg_0 to the
    // kind's object (vf_020).
    void sub_3EB80(RwInt32 arg_0, RwInt32 arg_4);

    // Inline accessors, with no address and so no database names; named for
    // their fields. Evidence: type_3CE5E8::vf_010 reads unk_2B0, and
    // type_3D410's sub_3DB40 unk_2B4 (twice), through temporaries of their
    // own.
    RwInt32 get_unk_2B4()
    {
        RwInt32 r = unk_2B4;
        return r;
    }
    RwInt32 get_unk_2B0()
    {
        RwInt32 r = unk_2B0;
        return r;
    }
};
typedef RwChar type_3DF30_size_check[sizeof(type_3DF30) == 0x2E0 ? 1 : -1];

#endif
