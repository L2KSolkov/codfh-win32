/*
 * type_3CE854: the kind-4 object sub_3CE20 creates (0x24 bytes), derived
 * from type_3CE4F0 (kind 3, whose constructor sub_348D0 and destructor
 * sub_34910 its own call) and anchored at its vtable off_3CE854, which its
 * constructor sub_3F120 installs. Its update drives each group member it
 * holds (sub_3F310); it takes on only members with flag 0x40000 in unk_2C
 * (vf_018). Its vf_02C (sub_9F4C0) and vf_030 (sub_9E000) lie elsewhere.
 */
#ifndef TYPE_3CE854_H
#define TYPE_3CE854_H

#include "rw/ostypes.h"
#include "types/type_3CE4F0.h"

struct type_3D3548;
struct type_3DBC78;
struct type_3D410;
struct type_3DF30;

struct type_3CE854 : type_3CE4F0
{
    RwInt32 unk_20;         // set by sub_3F310 once it drives a member;
                            // cleared by vf_004

    type_3CE854();
    virtual ~type_3CE854();
    virtual void vf_004(type_3DF30 *arg_0);
    virtual void vf_008();
    virtual RwInt32 vf_00C(RwReal arg_0, type_3D410 *arg_4);
    virtual RwInt32 vf_018(type_3D3548 *arg_0);

    // Drives the member arg_0 by its AI object's state (unk_5C): the
    // actions it tries (sub_12030), in an order per state.
    void sub_3F310(type_3DBC78 *arg_0, type_3D410 *arg_4);
    // vf_030, as the image's vtable has it (a trivial body, folded into
    // sub_9E000 with every other copy).
    virtual RwInt32 vf_030()
    {
        return 4;
    }
    // vf_02C, as the image's vtable has it (a trivial body, folded into
    // sub_9F4C0 with every other copy).
    virtual RwInt32 vf_02C()
    {
        return 8;
    }
};
typedef RwChar type_3CE854_size_check[sizeof(type_3CE854) == 0x24 ? 1 : -1];

#endif
