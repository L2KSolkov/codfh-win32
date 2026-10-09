/*
 * The pulse zones (unit_17D590).
 */
#ifndef TYPE_17DB90_H
#define TYPE_17DB90_H

#include "rw/ostypes.h"
#include "game/frames.h"
#include "rw/bamatrix.h"
#include "types/type_D48D0.h"
#include "types/type_129_base.h"

// type_17DB90: a pulse zone (unit_17D590; the zone object of a type_4CFE30,
// "PZ_Manipulate"), anchored at its vtable off_3DE0B0, which its
// constructor sub_17D590 installs; named after its method sub_17DB90, which
// takes a spawned particle system (0 to stop). Up to 16 entities are in it
// (unk_10); every unk_CC frames (its trigger's) it pulses: its effect
// (unk_B4, from dword_42A4B4 by kind: 0 damage, 1 a charge that becomes an
// explosion, 2 holding the players, 3 none) runs on them, unk_C8 times (0: for ever).
// Leaving it runs its exit effect (unk_B8, from dword_42A4C4).
struct type_17DB90
{
    virtual ~type_17DB90();
    // Set up from the trigger arg_0 (its matrix, cleared state, vf_00C).
    virtual void vf_004(class PulseZoneTrigger *arg_0);
    // Lets its trigger go.
    virtual void vf_008();
    // Its count and effects from the trigger arg_0.
    virtual void vf_00C(class PulseZoneTrigger *arg_0);
    // Counts its timer down by arg_0, or drops the dead or riding entities
    // and pulses (sub_17D8B0); 0 once it has pulsed its count.
    virtual RwInt32 vf_010(RwReal arg_0);

    RwUInt8 unk_04[0xC];
    type_D48D0 unk_10[16];      // the entities in it
    type_17DB90 *unk_50;        // the next zone (the manager's list, dword_4E7374)
    RwInt32 unk_54;             // set while it runs
    RwReal unk_58;              // the time to the next pulse
    type_144940 unk_5C;         // its trigger (+0x64)
    RwUInt8 unk_68[0x8];
    RwMatrixTag unk_70;         // where it is (its trigger's matrix; the tag,
                                // not the aligned RwMatrix, as the trigger's)
    RwInt32 unk_B0;             // its handle (a type_17E3A0, sub_17E560)
    void (*unk_B4)(type_17DB90 *arg_0, RwInt32 arg_4, RwInt32 arg_8);  // its effect
    void (*unk_B8)(type_17DB90 *arg_0, struct type_3D3548 *arg_4);    // its exit effect
    RwInt32 unk_BC;             // its kind (0 to 3)
    RwInt32 unk_C0;             // the user data "PZ_SetUserData" sets (the
    RwInt32 unk_C4;             // effect's two arguments)
    RwInt32 unk_C8;             // how many pulses are left
    RwInt32 unk_CC;             // its particle system

    type_17DB90();
    // Sets unk_54: an inline with no address, named for what it does. Evidence:
    // "PZ_Manipulate" (sub_54B00, SP 0x42D10) stores through it when stopping a
    // zone, where the plain store keeps a copy of the zone pointer.
    void set_running(RwInt32 arg_0)
    {
        unk_54 = arg_0;
    }
    // Built in its pool's memory (sub_17E3A0): an inline placement operator
    // new (no call in sub_17E3A0) and a placement operator delete, empty and
    // folded into sub_19A750, which its unwind funclet calls. Its deleting
    // destructor (sub_17D600) still calls the global operator delete.
    static void *operator new(RwUInt32 arg_0, void *arg_4)
    {
        return arg_4;
    }
    static void operator delete(void *arg_0, void *arg_4);
    static void operator delete(void *arg_0)
    {
        ::operator delete(arg_0);
    }
    // Pulses: its effect on what is in it; whether it has pulses left.
    RwInt32 sub_17D8B0();
    void sub_17D920(RwInt32 arg_0);
    // PulseZoneTrigger's sub_CB960 and sub_CB990 pass their argument on: an
    // entity (of its trigger's side, or a player for side 3) comes in, and
    // one leaves.
    void sub_17D940(struct type_3D3548 *arg_0);
    void sub_17DA20(struct type_3D3548 *arg_0);
    void sub_17DA90(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8);
    void sub_17DB10(void (*arg_0)(type_17DB90 *, RwInt32, RwInt32), RwInt32 arg_4, RwInt32 arg_8);
    void sub_17DB50(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8);
    void sub_17DB90(RwInt32 arg_0);
    // Its trigger through a local of its own: an inline with no address and
    // so no database name, named for its offset. Evidence: sub_17D940 reads
    // it through a temporary before its own local.
    // Its next zone and its handle: inlines with no address and so no
    // database names, named for their offsets. Evidence: sub_17E3A0 passes
    // the list's head through a temporary, and returns the handle through one.
    void set_unk_50(type_17DB90 *arg_0)
    {
        unk_50 = arg_0;
    }
    struct type_17E3A0 get_unk_B0();
    class PulseZoneTrigger *get_unk_64()
    {
        class PulseZoneTrigger *r = (class PulseZoneTrigger *)unk_5C.unk_08;
        return r;
    }
};
typedef RwChar type_17DB90_size_check[sizeof(type_17DB90) == 0xD0 ? 1 : -1];


// The zones' effects and exit effects by kind (.data).
extern void (*dword_42A4B4[4])(type_17DB90 *arg_0, RwInt32 arg_4, RwInt32 arg_8);
extern void (*dword_42A4C4[4])(type_17DB90 *arg_0, struct type_3D3548 *arg_4);
void sub_17DBD0(type_17DB90 *arg_0, RwInt32 arg_4, RwInt32 arg_8);
void sub_17DD00(type_17DB90 *arg_0, RwInt32 arg_4, RwInt32 arg_8);
void sub_17DE90(type_17DB90 *arg_0, RwInt32 arg_4, RwInt32 arg_8);
void sub_17E200(type_17DB90 *arg_0, RwInt32 arg_4, RwInt32 arg_8);
void sub_17E260(type_17DB90 *arg_0, struct type_3D3548 *arg_4);

#endif
