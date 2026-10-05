/*
 * type_17CC40: an object that follows a trigger (ShrimpTrigger's unk_EC,
 * 0x24 bytes), anchored at its lowest known method sub_17CC40 and its vtable
 * off_3D6D8C (its deleting destructor only). sub_17CC40 ties it to its
 * trigger and registers it (sub_17D350); sub_17CCA0 undoes that, unless
 * dword_4E7240 is set.
 */
#ifndef TYPE_17CC40_H
#define TYPE_17CC40_H

#include "rw/ostypes.h"
#include "rw/rpatomic.h"

class Trigger;

struct type_17CC40
{
    // sub_CB040 (out of line for ShrimpTrigger's unwinding) and its deleting
    // destructor sub_CB060, both emitted with ShrimpTrigger.
    virtual ~type_17CC40()
    {
        sub_17CCA0();
    }

    // Ties it to the trigger arg_0 and registers it; returns 1.
    RwInt32 sub_17CC40(Trigger *arg_0);
    void sub_17CCA0();
    // Adds a shrimp at the start of its path (and takes its model and path
    // the first time), unless the trigger's chance (unk_DC out of 100)
    // fails; whether it added one (ShrimpTrigger's vf_020).
    bool sub_17CD10();
    // Moves its shrimps along the path by the frame's time (arg_0 unused);
    // at an end a path turns them back, wraps them or they go.
    void sub_17CE90(RwReal arg_0);
    // Draws them into the camera arg_0 (unused), each facing along the path.
    void sub_17CFF0(struct RwCamera *arg_0);
    // Links the shrimp arg_0 at the head of its list, and unlinks it.
    void sub_17D180(struct type_17CA70_node *arg_0);
    void sub_17D1D0(struct type_17CA70_node *arg_0);

    RwUInt8 unk_04;             // its model and path are taken
    RwUInt8 unk_05[0x3];
    Trigger *unk_08;            // its trigger
    struct SplinePath *unk_0C;  // the path its shrimps swim along
    RpAtomic *unk_10;           // their model
    struct type_17CA70_node *unk_14;    // its shrimps
    type_17CC40 *unk_18;        // the next holder (dword_4E7238)
    RwUInt8 unk_1C[0x8];
};
typedef RwChar type_17CC40_size_check[sizeof(type_17CC40) == 0x24 ? 1 : -1];

#endif
