/*
 * type_62A60: the camera entity (kind 0x100000 in unk_2C), named after the
 * first command reading it, "SetCameraMode" (sub_62A60); its vtable is not
 * identified.
 */
#ifndef TYPE_62A60_H
#define TYPE_62A60_H

#include "rw/ostypes.h"
#include "rw/bamatrix.h"
#include "types/type_3D3548.h"

struct type_62A60 : type_3D3548
{
    RwUInt8 unk_3A8[0x68];      // where type_3D3548 ends inside this is not known
    RwInt32 unk_410;            // its align target's arg ("SetCameraAlignTargetFromNamedPoint")
    RwInt32 unk_414;            // its mode ("SetCameraMode") and the one
    RwInt32 unk_418;            // before it
    RwUInt8 unk_41C[0x10];
    struct SplinePath *unk_42C;    // its spline path ("SetCameraSplinePathFromName")

    // An inline setter for unk_410, with no address and so no database
    // name; named for its field. Evidence: "SetCameraAlignTargetFromNamedPoint"
    // passes the script argument through a local of its own (the inline's
    // parameter) before storing it.
    void set_unk_410(RwInt32 arg_0)
    {
        unk_410 = arg_0;
    }
    // An inline accessor for unk_414, likewise named for its field.
    // Evidence: the HUD's render (type_DC400::sub_DF000) reads the mode
    // through a result of its own.
    RwInt32 get_unk_414()
    {
        RwInt32 r = unk_414;
        return r;
    }
    // Aligns to the matrix arg_0 (sub_1752A0) and aims at it (sub_175F00);
    // only the widths are known.
    void sub_1752A0(RwMatrix *arg_0);
    void sub_175F00(RwMatrix *arg_0);
};

// sub_157680: applies the camera mode ("SetCameraMode"); only the width is
// known.
void sub_157680();
// deltaTime (the database's name, 0x429284): the frame's time step.
extern RwReal deltaTime;

#endif
