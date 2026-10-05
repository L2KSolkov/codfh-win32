/*
 * type_3CE4B4: the kind-0 object sub_3CE20 creates (0x20 bytes), derived from
 * type_3CE6D0 and anchored at its vtable off_3CE4B4, which its constructor
 * sub_33520 installs. Its vf_030 returns 0 (sub_1E4CB0) and its vf_024
 * returns 1 (sub_1F5A00). It runs the group members it holds through their
 * action handlers (sub_33820), and adds a slot +0x034 (sub_34740).
 */
#ifndef TYPE_3CE4B4_H
#define TYPE_3CE4B4_H

#include "rw/ostypes.h"
#include "types/type_3CE6D0.h"

struct type_3D3548;
struct type_3DBC78;
struct type_3DF30;

struct type_3CE4B4 : type_3CE6D0
{
    RwInt32 unk_1C;         // set by sub_33820 once it runs a member;
                            // cleared by vf_004

    type_3CE4B4();
    virtual ~type_3CE4B4();
    virtual void vf_004(type_3DF30 *arg_0);
    virtual void vf_008();
    virtual RwInt32 vf_00C(RwReal arg_0, type_3D410 *arg_4);
    virtual RwInt32 vf_010(type_3D410 *arg_0);
    virtual RwInt32 vf_018(type_3D3548 *arg_0);
    virtual RwInt32 vf_01C(type_3D3548 *arg_0);
    virtual RwInt32 vf_024(type_3D3548 *arg_0);
    virtual RwInt32 vf_030();
    // +0x034 (sub_34740): runs the AI object's unk_1430 order for the member
    // arg_0 (sub_33820 calls it last); 0 without one.
    virtual RwInt32 vf_034(type_3DBC78 *arg_0, type_3D410 *arg_4);

    RwInt32 sub_336C0(type_3D3548 *arg_0);
    void sub_33820(type_3DBC78 *arg_0, type_3D410 *arg_4);
};

// dword_438E84: cleared by type_3CE4B4::vf_008 (sub_335B0), set by
// "RedSquareHax"; only its width is known.
extern RwInt32 dword_438E84;

#endif
