/*
 * type_3CE5AC: the kind-1 object sub_3CE20 creates (0x4C bytes), derived
 * from type_3CE6D0 and anchored at its vtable off_3CE5AC, which its
 * constructor sub_36730 installs. It pairs two members of its group at a
 * two-node spot near the group's leader (sub_37490 picks the spot and its
 * two nodes) and runs them through a sequence of actions ending in
 * "AIAction_AttackStand" (vf_00C). Its vf_02C (priority) returns 10
 * (sub_36780), its vf_010 0x7FFFFFFF (sub_371D0); its vf_008 is
 * type_3CE278's (sub_39440).
 */
#ifndef TYPE_3CE5AC_H
#define TYPE_3CE5AC_H

#include "rw/ostypes.h"
#include "types/type_3CE6D0.h"
#include "types/type_D48D0.h"

struct type_3D3548;
struct type_3DF30;
struct type_F8350;

// The member search sub_37C60 runs over the group (through sub_3E570, with
// sub_37D80 as the callback), a local at ebp-0x1C there: the searcher, the
// node's point, the best squared distance (1e37 to start), the member
// found, and the two members already held (skipped).
struct type_37C60_1C
{
    struct type_3CE5AC *unk_00;
    RwV3d *unk_04;
    RwReal unk_08;
    type_3D3548 *unk_0C;
    type_3D3548 *unk_10;
    type_3D3548 *unk_14;
};

// sub_37D80: sub_37C60's callback: keeps in the type_37C60_1C at arg_4 the
// member nearest the node (other than the two held and those with flag 4
// of unk_2C).
void sub_37D80(type_3D3548 *arg_0, void *arg_4);

struct type_3CE5AC : type_3CE6D0
{
    type_F8350 *unk_1C;     // the spot (sub_37490, through sub_371F0)
    type_F8350 *unk_20;     // the first member's node, and
    type_F8350 *unk_24;     // the second's (both set by sub_37490)
    RwInt32 unk_28;         // their node numbers (passed on with them)
    RwInt32 unk_2C;
    type_D48D0 unk_30;      // the first member
    type_D48D0 unk_34;      // the second member
    RwInt32 unk_38;         // set once the first member has been sent on
    RwInt32 unk_3C;         // likewise for the second
    RwReal unk_40;          // a countdown within states 2 and 6
    RwReal unk_44;          // time until the next look for a spot
    RwInt32 unk_48;         // state: 0 idle, 1 gathering, 2 to 6 the steps

    type_3CE5AC();
    virtual ~type_3CE5AC();
    virtual void vf_004(type_3DF30 *arg_0);
    virtual void vf_008();
    virtual RwInt32 vf_00C(RwReal arg_0, type_3D410 *arg_4);
    virtual RwInt32 vf_010(type_3D410 *arg_0);
    virtual void vf_014(type_3D3548 *arg_0);
    // Inline: the constructor's vtable emits them after it, before ??_G (the image's order).
    virtual RwInt32 vf_02C()
    {
        return 10;
    }
    virtual RwInt32 vf_030();

    void sub_36850(type_3D410 *arg_0);
    RwBool sub_371F0(type_3D410 *arg_0);
    type_F8350 *sub_37490(type_3D410 *arg_0);
    type_F8350 *sub_37270(type_3D3548 *arg_0, RwReal arg_4, RwReal arg_8);
    RwInt32 sub_37C20(type_F8350 *arg_0, type_3D410 *arg_4);
    type_3D3548 *sub_37C60(type_F8350 *arg_0, RwInt32 arg_4, type_3D410 *arg_8);
    RwInt32 sub_37E50(type_3D3548 *arg_0);
    RwInt32 sub_37FB0(type_3D410 *arg_0);
    RwInt32 sub_38050(type_3D410 *arg_0);
    RwBool sub_380F0(type_3D410 *arg_0);
    RwInt32 sub_38AD0(type_3D3548 *arg_0, type_F8350 *arg_4);
    RwInt32 sub_38D80(type_3D3548 *arg_0, type_F8350 *arg_4);
};
typedef RwChar type_3CE5AC_size_check[sizeof(type_3CE5AC) == 0x4C ? 1 : -1];

// sub_37220: the kind-1 entry of the table at 0x42762C (arg_4 the
// context): 0x7FFFFFFF when the group's unk_2BC entity has a vf_00C
// object, else -1.
RwInt32 sub_37220(RwInt32 arg_0, type_3D410 *arg_4);

#endif
