/*
 * type_3CE4F0: the kind-3 object sub_3CE20 creates (0x20 bytes), derived from
 * type_3CE6D0 and anchored at its vtable off_3CE4F0, which its constructor
 * sub_348D0 installs. Its vf_030 returns 3 (sub_C5540); its vf_004 is
 * type_3CE4B4's (sub_33580, folded by /OPT:ICF) and its vf_008 is
 * type_3CE278's (sub_39440). Its update runs the group members it holds
 * that carry flag 0x80 in unk_2C (sub_34A60).
 */
#ifndef TYPE_3CE4F0_H
#define TYPE_3CE4F0_H

#include "rw/ostypes.h"
#include "types/type_3CE6D0.h"

struct type_3D3548;
struct type_3DBC78;
struct type_3DF30;

struct type_3CE4F0 : type_3CE6D0
{
    RwInt32 unk_1C;         // set by sub_34A60 once it runs a member;
                            // cleared by vf_004

    type_3CE4F0();
    virtual ~type_3CE4F0();
    virtual void vf_004(type_3DF30 *arg_0);
    virtual void vf_008();
    virtual RwInt32 vf_00C(RwReal arg_0, type_3D410 *arg_4);
    virtual RwInt32 vf_010(type_3D410 *arg_0);
    virtual RwInt32 vf_018(type_3D3548 *arg_0);
    virtual RwInt32 vf_030();

    void sub_34A60(type_3DBC78 *arg_0, type_3D410 *arg_4);
    void sub_34C60(type_3DBC78 *arg_0, type_3D410 *arg_4);
};

#endif
