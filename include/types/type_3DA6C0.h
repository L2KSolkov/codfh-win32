/*
 * type_3DA6C0: an entity class derived from type_3D3548, anchored at its
 * vtable off_3DA6C0, which sub_11E440 installs. It is the class
 * type_3D3548::vf_01C returns: its slot +0x01C returns this (sub_6FCD0).
 * Players attach to it ("AttachPlayerToAnimatedBGEntity"), and it follows
 * spline paths ("DivorceSplinePath").
 */
#ifndef TYPE_3DA6C0_H
#define TYPE_3DA6C0_H

#include "rw/ostypes.h"
#include "types/type_3D3548.h"
#include "game/functions.h"

struct type_3DA6C0 : type_3D3548
{
    virtual void vf_234();
    virtual void vf_238();
    virtual void vf_23C();
    // +0x240: whether it rolls procedurally on its spline
    // ("SetProceduralRollOnSpline").
    virtual void vf_240(bool arg_0);
    // +0x244: a state; a soldier it runs into reacts only at 1
    // (type_3DAFC8::vf_06C). Only the width is known.
    virtual RwInt32 vf_244();

    RwUInt8 unk_3A8[0x38];      // where type_3D3548 ends inside this is not known
    RwReal unk_3E0;             // its position on its spline path, the end
    RwUInt8 unk_3E4[0xC];
    RwMatrix unk_3F0;           // (its offset from the path, "SetSplineOffsetXYZ")
    RwUInt8 unk_430[0x14];
    RwReal unk_444;             // of it (0 to 1) and the path itself
    struct SplinePath *unk_448;    // ("SetSplinePathFromName",
                                    // "DivorceSplinePath")

    // Sets the path's end, clamped to 0 to 1 but for the result being
    // dropped: an inline function with no address and so no database name;
    // named for its field. Evidence: "SetSplinePathFromName" stores the end
    // twice and passes the clamp two temporaries of its own, as
    // type_3DDB98::sub_5B800 does out of line.
    void set_unk_444(RwReal arg_0)
    {
        unk_444 = arg_0;
        sub_22C20(unk_444, 0.0f, 1.0f);
    }

    // Its five-way blend on or off ("SetFiveWayBlend" mode 2).
    void sub_76860(bool arg_0);
    // Attaches the player arg_0 ("AttachPlayerToAnimatedBGEntity"): with
    // arg_C, its frame becomes a child of this one at the tag arg_4 (raised
    // by its trigger's unk_148 plus 10), else it rides it as a platform;
    // arg_8 turns its weapon off. Then posture 12. And detaches it.
    void sub_75AF0(type_10F710 *arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C);
    void sub_75CB0();

    // An inline accessor for unk_3F0, with no address and so no database name;
    // named for its field. Evidence: "SetSplineOffsetXYZ" holds the object
    // in a temporary of its own before taking the address.
    RwMatrix *get_unk_3F0()
    {
        return &unk_3F0;
    }
};

#endif
