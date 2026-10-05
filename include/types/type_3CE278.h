/*
 * type_3CE278: the kind-6 object sub_3CE20 creates, derived from type_3CE6D0
 * and anchored at its vtable off_3CE278, which its constructor sub_32210
 * installs after calling type_3CE6D0's sub_3CA10 (it then builds the handles
 * at +0x20 and +0x24). Its vf_030 returns 6 (sub_15FD20). It sends an entity
 * of its group to a node and has it stand alert there ("LTA_StartAlertStand").
 */
#ifndef TYPE_3CE278_H
#define TYPE_3CE278_H

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "types/type_3CE6D0.h"

#include "types/type_D48D0.h"

struct type_F8350;
struct type_3D3548;
struct type_3CE278;
struct type_3DF30;

// The node search sub_32A50 runs over the group (through sub_3E570, with
// sub_32B40 as the callback), a local at ebp-0x20 there (its first
// instance): the searcher, the node's point, the best squared distance
// (1e37 to start), the entity found and the entity to skip.
struct type_32A50_20
{
    type_3CE278 *unk_00;
    RwV3d *unk_04;
    RwReal unk_08;
    type_3D3548 *unk_0C;
    type_3D3548 *unk_10;
    RwInt32 unk_14;         // not set by sub_32A50; the frame shows 0x18 bytes
};

// sub_32B40: sub_32A50's callback: keeps in the type_32A50_20 at arg_4 the
// member nearest the node (other than the one to skip).
void sub_32B40(type_3D3548 *arg_0, void *arg_4);

struct type_3CE278 : type_3CE6D0
{
    // unk_18 (type_3CE6D0), the object's handle: sub_32BF0 makes it the
    // entity's AIData::unk_574.
    type_F8350 *unk_1C;     // a node: AIData::sub_28780 heads for its point
    type_D48D0 unk_20;      // cleared by sub_322E0
    type_D48D0 unk_24;      // the entity sent to the node
    RwReal unk_28;          // the stand's countdown (300 from state 3)
    RwReal unk_2C;          // time until the next look for a node (60)
    RwInt32 unk_30;         // state: 0 idle, 1 sent, 2 standing, 3 done

    type_3CE278();
    virtual ~type_3CE278();
    virtual void vf_004(type_3DF30 *arg_0);
    virtual void vf_008();
    virtual RwInt32 vf_00C(RwReal arg_0, type_3D410 *arg_4);
    // sub_32260: also the base's (and other kinds') slots +0x018 and +0x024,
    // folded by /OPT:ICF. Inline: the out-of-line constructor's vtable emits
    // it, before ??_G (the image's order at 0x32210-0x32270).
    virtual RwInt32 vf_010(type_3D410 *arg_0)
    {
        return 0;
    }
    virtual void vf_014(type_3D3548 *arg_0);
    virtual RwInt32 vf_02C();
    virtual RwInt32 vf_030();

    void sub_322E0(type_3D410 *arg_0);
    RwInt32 sub_326D0(type_3D410 *arg_0);
    type_F8350 *sub_32750(type_3D410 *arg_0);
    type_3D3548 *sub_32A50(type_F8350 *arg_0, RwInt32 arg_4, type_3D410 *arg_8);
    RwInt32 sub_32BF0(type_3D3548 *arg_0);
    RwInt32 sub_32D30(type_3D410 *arg_0);
    RwInt32 sub_32DD0(type_3D410 *arg_0);
};

#endif
