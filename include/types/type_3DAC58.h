/*
 * type_3DAC58: the simple mechanism ("SimpleMechanicEntity", the name its
 * set-up reports when its trigger has no model), an entity class derived
 * from type_3D3548, anchored at its vtable off_3DAC58. SimpleMechanicTrigger
 * spawns one (0x420 bytes, sub_133230) in entity memory through its inline
 * constructor, which sets it up with vf_234. It follows its spline path
 * (vf_0F4) back and forth or once, and takes damage from bullets and
 * explosions by its trigger's flags. It is the class type_3D3548::vf_020
 * returns: its slot +0x020 returns this (sub_6FCD0). The scripts move it
 * along paths ("SetSplinePathFromName", "DivorceSplinePath").
 */
#ifndef TYPE_3DAC58_H
#define TYPE_3DAC58_H

#include "rw/ostypes.h"
#include "rw/bamatrix.h"
#include "types/type_3D3548.h"
#include "game/functions.h"

struct type_3DAC58 : type_3D3548
{
    // Defined in the class: sub_133230 expands it (the base constructor,
    // the vtable, then vf_234).
    type_3DAC58(type_712B0 *arg_0)
    {
        vf_234(arg_0);
    }

    // Overrides defined in the class (emitted with the vtable, in this
    // order, in unit_1331E0).
    // Its AI object's handle, and setting it.
    virtual RwInt32 vf_09C()
    {
        return unk_3B0;
    }
    virtual void vf_0A0(RwUInt32 arg_0)
    {
        unk_3B0 = arg_0;
    }
    // Its speed along its path, and setting it.
    virtual void vf_124(RwReal arg_0)
    {
        unk_3BC = arg_0;
    }
    virtual RwReal vf_128()
    {
        return unk_3BC;
    }
    // Its health, setting it, and adding to it (no more than its full
    // health).
    virtual RwInt32 vf_174()
    {
        return unk_410;
    }
    virtual void vf_178(RwInt32 arg_0)
    {
        unk_410 = arg_0;
    }
    virtual void vf_180(RwInt32 arg_0)
    {
        unk_410 += arg_0;
        if (unk_410 > unk_414)
            unk_410 = unk_414;
    }
    // Its health as a share of its full health.
    virtual RwReal vf_17C()
    {
        return (RwReal)unk_410 / unk_414;
    }
    // The spline path it follows.
    virtual struct SplinePath *vf_0F4()
    {
        return unk_3B8;
    }

    // Its destructor (sub_1334E0) takes it down (vf_230); its scalar
    // deleting destructor is sub_1334B0.
    ~type_3DAC58();
    // The placement pair sub_133230 builds it in entity memory with, as
    // type_3D32F8's (sub_6CCF0 and the empty sub_19A750).
    static void *operator new(RwUInt32 arg_0, void *arg_4);
    static void operator delete(void *arg_0, void *arg_4);
    // Its plain operator delete, for its scalar deleting destructor: empty
    // and out of line (folded into sub_19A750) like the base's; the
    // placement one hides the base's.
    static void operator delete(void *arg_0);

    // Overrides (out of line in unit_1331E0).
    virtual void vf_230();
    virtual void vf_03C(RwReal arg_0);
    virtual RwInt32 vf_064(struct type_75600 *arg_0);
    virtual RwInt32 vf_068(struct type_758F0 *arg_0);
    virtual type_3D2E7C *vf_098();
    virtual RwInt32 vf_058(struct type_3DF8D8_04 *arg_0);
    virtual void vf_0F8(RwReal arg_0);
    // +0x234: sets it up from the trigger arg_0: the base set-up, its kind
    // and flags, its health (the trigger's unk_F4), its model, its AI object
    // and scripts, and its path (the trigger's unk_E8 and unk_F0); returns
    // 1, or 0 (and marks it for deletion) when the trigger has no model.
    virtual RwInt32 vf_234(type_712B0 *arg_0);

    // Sets the path's end, as type_3DA6C0::set_unk_444 (the clamp's result
    // dropped), out of line and inline, as type_3DDB98::sub_5B800.
    void sub_5B850(RwReal arg_0);
    void set_unk_3C0(RwReal arg_0)
    {
        unk_3C0 = arg_0;
        sub_22C20(unk_3C0, 0.0f, 1.0f);
    }

    // An inline accessor for unk_3D0, with no address and so no database name;
    // named for its field. Evidence: "SetSplineOffsetXYZ" holds the object
    // in a temporary of its own before taking the address.
    RwMatrix *get_unk_3D0()
    {
        return &unk_3D0;
    }

    RwUInt8 unk_3A8[0x8];
    RwUInt32 unk_3B0;           // its AI object's handle (vf_098)
    RwReal unk_3B4;             // where it is along its path (0 to unk_3C0)
    struct SplinePath *unk_3B8; // its path (vf_0F4)
    RwReal unk_3BC;             // its speed along it (vf_124)
    RwReal unk_3C0;             // the path's end (1; "DivorceSplinePath")
    RwUInt8 unk_3C4[0xC];
    RwMatrix unk_3D0;           // its offset from its path (sub_BA990;
                                // "SetSplineOffsetXYZ")
    RwInt32 unk_410;            // its health
    RwInt32 unk_414;            // its full health (the trigger's unk_F4)
    RwInt32 unk_418;            // set while it is up (vf_230)
    RwUInt8 unk_41C[0x4];
    // vf_020, as the image's vtable has it (a trivial body, folded into
    // sub_6FCD0 with every other copy).
    virtual type_3DAC58 *vf_020()
    {
        return this;
    }
};
typedef RwChar type_3DAC58_size_check[sizeof(type_3DAC58) == 0x420 ? 1 : -1];

// Builds the mechanism for the trigger arg_0, or warns that there is no
// entity memory for it.
type_3DAC58 *sub_133230(type_712B0 *arg_0);

#endif
