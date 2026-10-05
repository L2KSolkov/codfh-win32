/*
 * An entity's zone (unit_08AB60; type_3D3548::unk_90): the zone it is in
 * and the one it left, and their fades.
 */
#ifndef TYPES_TYPE_8E670_H
#define TYPES_TYPE_8E670_H

#include "rw/ostypes.h"
#include "rw/batypes.h"

struct type_8F3E0;
struct type_8BEC0;
struct type_8F210;

// An entity's zone at +0x90 (sub_94060 finds the smallest zone around the
// entity each frame and hands it to sub_8E670, then fades with sub_8E750):
// the zone it is in and its weight fading in, the one it left fading out.
struct type_8E670
{
    type_8F3E0 *unk_00;         // the current zone
    RwReal unk_04;              // its weight, rising to 1
    type_8F3E0 *unk_08;         // the zone before
    RwReal unk_0C;              // its weight, falling to 0
    RwInt32 unk_10;
    RwInt32 unk_14;
    RwInt32 unk_18;
    RwReal unk_1C;              // counts down by 0.1 a frame
    RwInt32 unk_20;             // while set, dword_4B2560 runs down

    // Inline: type_3D3548's constructor clears it through a `this`
    // temporary, in this order.
    type_8E670()
    {
        unk_08 = 0;
        unk_00 = 0;
        unk_0C = 0.0f;
        unk_04 = 0.0f;
        unk_1C = 0.0f;
        unk_18 = 0;
        unk_14 = 0;
        unk_10 = 0;
        unk_20 = 0;
    }

    void sub_8E670(type_8F3E0 *arg_0);
    // Clears it, as its constructor does (type_3D3548's vf_22C).
    void sub_CCC60();
    void sub_8E750();
    void sub_8F140(RwInt32 arg_0, RwReal arg_4, RwV3d *arg_8, struct type_8BEC0 *arg_C,
                   RwV3d *arg_10, struct type_8BEC0 *arg_14);
    void sub_8F210(struct type_8F210 *arg_0);
    // Fills the light list arg_0 from the zones and hands it on.
    void sub_8E870(struct type_8F210 *arg_0);
};

#endif
