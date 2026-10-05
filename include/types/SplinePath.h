/*
 * SplinePath (the class name it registers with the class factory at
 * 0x30AB56, with its MakeNew, sub_B9EA0, and its size, 0x38): a RenderWare
 * Studio behaviour wrapping an RpSpline, derived from RWS::CAttributeHandler
 * and anchored at its vtable off_3D6630 (4 slots: the destructor,
 * HandleAttributes and two of its own), which its constructor sub_B9F20
 * installs after the base's. AIData::unk_1410 and the +0xD14 pointer refer to
 * one (sub_20DA0 and sub_5B240 take it from another object's +0x24; its
 * command 0 names the object, a kind 0x2E, and sub_BA420 puts it there).
 *
 *   +0x1C unk_1C  its end mode and a flag (commands 1 and 2)
 *   +0x24 unk_24  a length: AIData::sub_17BF0 starts 200 along the spline,
 *                 as a parameter, by dividing by it ("GetSplineLength"
 *                 returns it)
 *   +0x28 unk_28  the spline: sub_BA450 and sub_BA990 pass it to
 *                 _RpSplineGetNumControlPoints and _RpSplineFindPosition
 *   +0x2C unk_2C  its name (command 0)
 *   +0x34 unk_34  sub_143D60's result for this object (sub_B9F20)
 */
#ifndef SPLINEPATH_H
#define SPLINEPATH_H

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "rw/rpspline.h"
#include "rw/bamatrix.h"
#include "rws/cattributehandler.h"
#include "rws/linearallocationpolicy.h"
#include "types/type_3DF8D8.h"

struct SplinePath : RWS::CAttributeHandler, RWS::LinearAllocationPolicy
{
    RWS_MAKENEWCLASS(SplinePath);
    RWS_DECLARE_CLASSID(SplinePath);

    SplinePath(const RWS::CAttributePacket &attr);
    ~SplinePath()
    {
    }

    virtual void HandleAttributes(const RWS::CAttributePacket &attr);
    // Its system commands: an attached resource (the spline) goes to
    // vf_00C (sub_BA230), which takes an "rwID_SPLINE" and measures it.
    virtual void vf_008(const RWS::CAttributePacket &attr);
    virtual void vf_00C(const void *arg_0);

    RwUInt8 unk_18[0x4];
    union
    {
        RwInt32 unk_1C;
        struct
        {
            RwUInt32 unk_1C_0 : 2;  // its end mode: 2 turns back, 1 wraps
                                    // (type_3D32F8's vf_03C; command 1)
            RwUInt32 unk_1C_2 : 1;  // command 2
            RwUInt32 unk_1C_3 : 29;
        };
    };
    RwUInt8 unk_20[0x4];
    RwReal unk_24;
    RpSpline *unk_28;
    type_3DF8D8_04 unk_2C;
    RwUInt32 unk_34;

    // The spline parameter nearest arg_0 (a point), searched with step
    // arg_4 (100.0f from AIData::sub_213B0) and arg_8 (1.0f); 0 for a spline
    // with fewer than two control points.
    RwReal sub_BA450(RwV3d *arg_0, RwReal arg_4, RwReal arg_8);
    // The point at parameter arg_0 into *arg_4 (_RpSplineFindPosition), and
    // when arg_8 is given something derived from it (AIData::sub_213B0
    // passes its unk_D30).
    void sub_BA990(RwReal arg_0, RwV3d *arg_4, RwMatrix *arg_8);
};

typedef RwChar SplinePath_size_check[sizeof(SplinePath) == 0x38 ? 1 : -1];

// The callback sub_198900 calls for a spline's name: the named object (a
// kind 0x2E, arg_0) takes the spline (arg_8) and its flag 0x80; returns 1.
RwInt32 sub_BA420(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8);
// What its constructor keeps (unk_34) for it; only the width is known.
RwUInt32 sub_143D60(SplinePath *arg_0);

#endif
