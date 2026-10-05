/*
 * type_3CE5E8: the kind-5 object sub_3CE20 creates (0x5F4 bytes), derived
 * from type_3CE6D0 and anchored at its vtable off_3CE5E8 (13 slots), which
 * its constructor sub_390D0 installs after calling type_3CE6D0's sub_3CA10.
 * Its vf_030 returns 5 (sub_A17A0) and its vf_02C (priority) 11 (sub_39180).
 * It runs a fire-and-movement advance on a point ("FireAndMovementFinished",
 * "FireAndMovementCleared"): the group members it holds are split between
 * two teams (unk_1C and unk_29C) that move up in turn.
 */
#ifndef TYPE_3CE5E8_H
#define TYPE_3CE5E8_H

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "types/type_3CE6D0.h"
#include "types/type_D48D0.h"

struct type_3D3548;
struct type_3DF30;
struct type_3DBC78;

// type_39250_14: one member slot of a team, 0x14 bytes, named after
// vf_004 (sub_39250), which clears them. Its implicit constructor and
// destructor are type_D48D0's (VC7.1 passes them, folded as pCtor and
// pDtor, to the `eh vector constructor iterator').
//
//   +0x00 unk_00  the member
//   +0x08 unk_08  set while the member holds a node (sub_3A9C0, sub_3AC40)
//   +0x0C unk_0C  set by sub_3AC40 for a member at action 0x16, state 2
//   +0x10 unk_10  the member's squared distance from the point unk_5AC
struct type_39250_14
{
    type_D48D0 unk_00;
    RwInt32 unk_04;
    RwInt32 unk_08;
    RwInt32 unk_0C;
    RwReal unk_10;
};

struct type_3CE5E8 : type_3CE6D0
{
    type_39250_14 unk_1C[32];   // the first team
    type_39250_14 unk_29C[32];  // the second team
    RwInt32 unk_51C;            // the first team's count
    RwInt32 unk_520;            // the second team's count
    type_D48D0 unk_524[32];     // the members in range of the point
    type_39250_14 *unk_5A4;     // unk_1C
    type_39250_14 *unk_5A8;     // unk_29C
    RwV3d unk_5AC;              // the point (AIData::sub_23C30 hands it out)
    RwInt32 unk_5B8;            // set by sub_3B680 when a team has moved
    RwInt32 unk_5BC;            // set by sub_3B680 near the end of unk_5CC
    RwInt32 unk_5C0;
    RwInt32 unk_5C4;            // set while there is a point (sub_3A170)
    RwReal unk_5C8;             // time since the last swap (sub_3B680)
    RwReal unk_5CC;             // the time between swaps
    RwInt32 unk_5D0;            // set by vf_020
    RwInt32 unk_5D4;
    RwReal unk_5D8;             // a countdown
    RwReal unk_5DC;             // 1000, and
    RwReal unk_5E0;             // its square
    RwReal unk_5E4;             // 1500, and
    RwReal unk_5E8;             // its square
    RwInt32 unk_5EC;            // 360
    RwInt32 unk_5F0;            // 480

    type_3CE5E8();
    virtual ~type_3CE5E8();
    virtual void vf_004(type_3DF30 *arg_0);
    virtual void vf_008();
    virtual RwInt32 vf_00C(RwReal arg_0, type_3D410 *arg_4);
    virtual RwInt32 vf_010(type_3D410 *arg_0);
    virtual void vf_014(type_3D3548 *arg_0);
    virtual RwInt32 vf_018(type_3D3548 *arg_0);
    virtual RwInt32 vf_01C(type_3D3548 *arg_0);
    virtual void vf_020(RwInt32 arg_0);
    virtual RwInt32 vf_024(type_3D3548 *arg_0);
    // Inline: the constructor's vtable emits them after it, before ??_G (the image's order).
    virtual RwInt32 vf_02C()
    {
        return 11;
    }
    virtual RwInt32 vf_030();

    void sub_3A170(RwV3d *arg_0);
    RwInt32 sub_3A450(type_3D3548 *arg_0);
    void sub_3A9C0(type_3DBC78 *arg_0, type_39250_14 *arg_4, type_3D410 *arg_8);
    void sub_3AC40(type_3DBC78 *arg_0, type_39250_14 *arg_4, type_3D410 *arg_8);
    RwInt32 sub_3B680();
    RwInt32 sub_3B7E0();
    RwInt32 sub_3C070();
    void sub_3C110();
};

// sub_3B0A0's table, a local at ebp-0x1090 there: per candidate, how many
// other candidates it is near, and which.
struct type_3B0A0_84
{
    RwInt32 unk_00;
    RwInt32 unk_04[32];
};

// Free helpers of the unit (arg_0 of sub_3B560 is the context; the
// type_D48D0 arrays are 32 members).
RwBool sub_3B0A0(type_D48D0 *arg_0, type_3D410 *arg_4);
RwV3d sub_3B490(type_D48D0 *arg_0);
RwBool sub_3B560(type_3D410 *arg_0, type_D48D0 *arg_4);
typedef RwChar type_3CE5E8_size_check[sizeof(type_3CE5E8) == 0x5F4 ? 1 : -1];

#endif
