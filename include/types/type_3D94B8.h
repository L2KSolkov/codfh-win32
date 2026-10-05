/*
 * type_3D94B8: the pickup entity, derived from type_3D3548, anchored at its
 * vtable off_3D94B8 (0x3D0 bytes, src/recovered/unit_0FA9E0.cpp). A
 * PickupTrigger spawns one (sub_FA9E0) with its settings (type_4C09B0,
 * dword_4C09B0) through the inline constructor; sub_FABC0 spawns one from
 * the settings directly (the out-of-line constructor sub_FAC70), and those
 * count in dword_4C09A8 while they are up.
 */
#ifndef TYPE_3D94B8_H
#define TYPE_3D94B8_H

#include "rw/ostypes.h"
#include "rw/bamatrix.h"
#include "types/type_3D3548.h"
#include "types/type_3DF8D8.h"
#include "types/type_4C09B0.h"

class PickupTrigger;

// The x, y and z axes (.rdata) the pickup's set-up turns its settings'
// angles about (sub_FADB0).
extern const RwV3d unk_3D9490;
extern const RwV3d unk_3D949C;
extern const RwV3d unk_3D94A8;

// The pickup's settings index and a value set with it (+0x3B0); anchored at
// its constructor. Its destructor is empty and out of line (pDtor, folded
// at 0x1E41C0).
struct type_FB6E0
{
    RwInt32 unk_00;             // set once given
    RwInt32 unk_04;
    RwInt32 unk_08;             // the settings index (-1 for none)

    type_FB6E0();
    ~type_FB6E0();
    RwInt32 sub_FB710();
    void sub_FB730(RwInt32 arg_0, RwInt32 arg_4);
    // What the settings' named object (sub_198800 of its key) gives
    // (sub_190A10); only the width is known.
    RwInt32 sub_FB760();
};

struct type_3D94B8 : type_3D3548
{
    // Built for the trigger arg_0: inline (sub_FA9E0 expands it).
    type_3D94B8(PickupTrigger *arg_0)
    {
        sub_FAD20(arg_0);
    }
    // Built from the settings directly (sub_FAC70), counted in dword_4C09A8.
    type_3D94B8(RwInt32 arg_0, RwInt32 arg_4, RwMatrix *arg_8, RwReal arg_C, RwInt32 arg_10, RwInt32 arg_14);
    // The placement pair it is built in entity memory with, as type_3D32F8's
    // (sub_6CCF0 and the empty sub_19A750).
    static void *operator new(RwUInt32 arg_0, void *arg_4);
    static void operator delete(void *arg_0, void *arg_4);
    // Its plain operator delete, for its scalar deleting destructor
    // (sub_FAB20): empty and out of line (folded into sub_19A750); the
    // placement one hides the base's.
    static void operator delete(void *arg_0);
    // Takes it down (vf_230), then its settings link's destructor runs.
    // Defined here: the network pick-up's destructor (sub_1BD5F0) expands
    // it; its out-of-line copy is sub_FAB50.
    ~type_3D94B8()
    {
        vf_230();
    }

    // Overrides.
    virtual void vf_03C(RwReal arg_0);
    virtual void vf_040(RwReal arg_0);
    virtual void vf_044(RwReal arg_0);
    // Empty: folded (/OPT:ICF) into sub_15FB30.
    virtual void vf_054(RwInt32 arg_0);
    // Whether arg_0 is its settings' key.
    virtual RwInt32 vf_058(type_3DF8D8_04 *arg_0);
    // Folded (/OPT:ICF) into another class's identical one (0x177080).
    virtual void Collision_DispatchAtomicIntersectionsBySelectorFlag(RpAtomic *arg_0, RpIntersection *arg_4,
                                                                     struct type_93700 *arg_8);
    // Landing: no more motion, gravity off.
    virtual void vf_1C4(RwInt32 arg_0);
    // Takes it down (its atomic and clump), uncounting it.
    virtual void vf_230();

    // The set-up from the trigger arg_0 (its settings, count and flag at
    // its matrix), and from the settings arg_0.
    RwInt32 sub_FAD20(PickupTrigger *arg_0);
    RwInt32 sub_FADB0(RwInt32 arg_0, RwInt32 arg_4, RwMatrix *arg_8, RwReal arg_C, RwInt32 arg_10,
                      RwInt32 arg_14);

    RwUInt8 unk_3A8[0x8];
    type_FB6E0 unk_3B0;
    RwInt32 unk_3BC;
    RwInt32 unk_3C0;            // counted in dword_4C09A8
    RwInt32 unk_3C4;            // set while it is up
    RwInt32 unk_3C8;
    RwInt32 unk_3CC;
};
typedef RwChar type_3D94B8_size_check[sizeof(type_3D94B8) == 0x3D0 ? 1 : -1];

// The pickups spawned from settings and up.
extern RwInt32 dword_4C09A8;

// Spawns a pickup from the settings (sub_FABC0).
type_3D94B8 *sub_FABC0(RwInt32 arg_0, RwInt32 arg_4, RwMatrix *arg_8, RwReal arg_C, RwInt32 arg_10, RwInt32 arg_14);

#endif
