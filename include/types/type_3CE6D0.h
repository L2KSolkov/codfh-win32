/*
 * type_3CE6D0: the base of the objects sub_3CE20 creates (six kinds, through
 * sub_32210, sub_33520, sub_348D0, sub_36730, sub_390D0 and sub_3F120) and
 * registers with sub_3D2E0 in the handle table dword_4392A8. It is anchored
 * at its vtable off_3CE6D0, which its constructor sub_3CA10 installs.
 * sub_3D3E0 resolves a handle to one of these objects.
 *
 * The vtable has 13 slots, +0x000 to +0x030. Slots follow type_3D3548's
 * convention: vf_<byte offset>, `void ()` until their signature is known.
 * Slot 0 is the virtual destructor's scalar deleting destructor (sub_3CA40):
 * it runs the destructor (sub_3CA60) and returns this without freeing,
 * which is what an empty inline operator delete gives (the objects live in
 * a pool).
 */
#ifndef TYPE_3CE6D0_H
#define TYPE_3CE6D0_H

#include "rw/ostypes.h"
#include "types/type_365A0.h"
#include "types/type_3D410.h"

struct type_3D3548;
struct type_3DBC78;
struct type_F8350;
struct type_3D410;
struct type_3DF30;

struct type_3CE6D0
{
    type_3CE6D0();
    virtual ~type_3CE6D0();
    // +0x004 (sub_3CA80): joins the group arg_0 (type_3DF30::sub_3E2C0
    // passes itself), keeping it in unk_08; kinds reset their own state,
    // then call it.
    virtual void vf_004(type_3DF30 *arg_0);
    virtual void vf_008();
    // +0x00C (sub_3CAB0): the update, with the time step arg_0 and the
    // context arg_4; kinds run their own first and return its result.
    virtual RwInt32 vf_00C(RwReal arg_0, type_3D410 *arg_4);
    virtual RwInt32 vf_010(type_3D410 *arg_0);
    // +0x014 (sub_3CBB0): an entity leaves (type_3CE278 drops it first when
    // it is the one it holds).
    virtual void vf_014(type_3D3548 *arg_0);
    // +0x018 and +0x01C: take on the entity arg_0 (the base's +0x018 is
    // sub_32260, which returns 0; its +0x01C is sub_3CB00).
    virtual RwInt32 vf_018(type_3D3548 *arg_0);
    virtual RwInt32 vf_01C(type_3D3548 *arg_0);
    // +0x020: a flag only kind 5 acts on (sub_3A150 sets its unk_5D0 when
    // arg_0 is nonzero).
    virtual void vf_020(RwInt32 arg_0);
    // +0x024: AIData::sub_1A1F0 passes its owner and returns the result; the
    // base implementation (sub_32260) returns 0.
    virtual RwInt32 vf_024(type_3D3548 *arg_0);
    // +0x028: AIData::sub_1A2E0 passes its owner; the base implementation
    // (sub_15FB30) does nothing.
    virtual void vf_028(type_3D3548 *arg_0);
    // +0x02C: the object's priority: sub_3E2C0 keeps a group's objects in
    // its order (10 for type_3CE5AC, sub_36780).
    virtual RwInt32 vf_02C();
    // +0x030: the object's kind: -1 here (sub_9E030), 5 for type_3CE5E8
    // (sub_A17A0).
    virtual RwInt32 vf_030();

    RwInt32 unk_04;         // set by vf_004 until the first update (vf_00C)
    type_3DF30 *unk_08;     // the group (vf_004); zeroed by sub_3CA10
    RwUInt8 unk_0C[0x4];
    RwInt32 unk_10;         // cleared by vf_004
    union
    {
        RwUInt32 unk_14;        // the next object's handle in the group's list
        type_365A0 unk_14_h;    // (sub_3E2C0); zeroed by sub_3CA10
    };
    union
    {
        RwUInt32 unk_18;        // the object's handle, which sub_3CE20 stores
        type_365A0 unk_18_h;    // after registering it (sub_3D2E0)
    };

    // Its list links as handles: inline accessors with no addresses, named
    // for their fields. Evidence: the group's insertion and removal
    // (type_3DF30::sub_3E2C0, sub_3E3B0) copy each through a getter's and a
    // setter's temporary, the getters' numbered first.
    type_365A0 get_unk_14()
    {
        return unk_14_h;
    }
    void set_unk_14(type_365A0 arg_0)
    {
        unk_14_h = arg_0;
    }
    type_365A0 get_unk_18()
    {
        return unk_18_h;
    }
    void operator delete(void *arg_0)
    {
    }
    // The placement pair the AIManeuverManager's factory sub_3CE20 builds
    // the objects in their pool slots with: operator new (sub_6CCF0, which
    // returns arg_4; called, so not inline) and its operator delete, which
    // the factory's unwind funclets call and which /OPT:ICF folded into the
    // empty sub_19A750. Members, since the class's own operator delete
    // hides the global ones.
    static void *operator new(RwUInt32 arg_0, void *arg_4);
    static void operator delete(void *arg_0, void *arg_4);

    // Has the member arg_0 pick a target from the context (arg_4's
    // sub_3DCD0); the kinds' member drivers call it (type_3CE4B4's
    // sub_33820, type_3CE5E8's sub_3A9C0 and sub_3AC40).
    RwInt32 sub_34720(type_3DBC78 *arg_0, type_3D410 *arg_4);

    // Whether the kind can take on the node arg_0 for the context arg_4
    // (type_3CE278::sub_32DD0 asks).
    RwInt32 sub_18F420(type_F8350 *arg_0, type_3D410 *arg_4);
};

#endif
