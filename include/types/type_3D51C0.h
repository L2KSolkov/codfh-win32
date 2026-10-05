/*
 * type_3D51C0: an entity class derived from type_3D3548, anchored at its
 * vtable off_3D51C0, which its constructor (sub_9AE50) and destructor
 * (sub_9AFE0) install. sub_9AD40 spawns one (0x3E0 bytes) in entity memory
 * for a trigger. Like the animated background entity (type_3D32F8) it keeps
 * a script object and an AI object by handle, answers bullets with the
 * "HitByBullet" messages and holds a scene (three words at +0x3C8).
 */
#ifndef TYPE_3D51C0_H
#define TYPE_3D51C0_H

#include "rw/ostypes.h"
#include "types/type_3D3548.h"
#include "types/type_129_base.h"
#include "types/type_3D32F8.h"
#include "types/alfaobject.h"
#include "game/functions.h"

// The frame and clump it keeps at +0x3B0 and +0x3BC (types/type_129_base.h;
// its destructor empties them with sub_129B10 and sub_129940).
struct type_3D51C0 : type_3D3548
{
    // Its constructor (sub_9AE50) builds it for the trigger arg_0. Defined
    // in the class but not expanded (sub_9AD40 keeps 8 bytes for it;
    // docs/toolchain.md).
    type_3D51C0(type_712B0 *arg_0)
    {
        vf_234(arg_0);
    }
    // Its destructor (sub_9AFE0; virtual, as the base's) takes it down
    // (vf_230) and empties its lists; its scalar deleting destructor is
    // sub_9AFB0.
    ~type_3D51C0();
    // The placement pair sub_9AD40 builds it in entity memory with, as
    // type_3D32F8's (sub_6CCF0 and the empty sub_19A750).
    static void *operator new(RwUInt32 arg_0, void *arg_4);
    static void operator delete(void *arg_0, void *arg_4);
    // Its plain operator delete, for its scalar deleting destructor: empty
    // and out of line (folded into sub_19A750) like the base's; the
    // placement one hides the base's.
    static void operator delete(void *arg_0);

    // Overrides (out of line in unit_09AD40).
    virtual void vf_054(RwInt32 arg_0);
    virtual RwInt32 vf_064(type_75600 *arg_0);
    virtual type_6D380 *vf_090();
    // Inline: the constructor's vtable emits them after it, before ??_G (the image's order).
    virtual RwInt32 vf_09C()
    {
        return unk_3D4;
    }
    virtual void vf_0A0(RwUInt32 arg_0)
    {
        unk_3D4 = arg_0;
    }
    virtual RwUInt8 * vf_0E0()
    {
        return (RwUInt8 *)unk_3C8;
    }
    virtual void vf_0EC(RwInt32 arg_0, RwInt32 arg_4)
    {
        unk_3C8[arg_0] = (RwUInt16)arg_4;
    }
    virtual void vf_094(RwUInt32 arg_0)
    {
        unk_3D0 = arg_0;
    }
    virtual void vf_230();
    // +0x234: sets it up from the trigger arg_0: the base set-up, its kind,
    // size and flags, its AI scripts (the trigger's unk_F0 and unk_F8), its
    // script object and its scene; returns 1.
    virtual RwInt32 vf_234(type_712B0 *arg_0);

    RwUInt8 unk_3A8[0x8];
    type_129B10 unk_3B0;
    type_129940 unk_3BC;
    RwUInt16 unk_3C8[3];        // its scene (vf_0E0, vf_0EC)
    RwUInt8 unk_3CE[0x2];
    RwUInt32 unk_3D0;           // its script object's handle (vf_090)
    RwUInt32 unk_3D4;           // its AI object's handle (vf_098)
    RwInt32 unk_3D8;            // set while it is up (vf_230)
    RwUInt8 unk_3DC[0x4];

    // Inline setters for unk_3D0 and unk_3D4, with no address and so no
    // database names; named for their fields. Evidence: vf_234 stores each
    // new handle through a temporary of its own (the expanded setter's
    // parameter), loading `this` after it.
    void set_unk_3D0(RwUInt32 arg_0)
    {
        unk_3D0 = arg_0;
    }
    void set_unk_3D4(RwUInt32 arg_0)
    {
        unk_3D4 = arg_0;
    }
    // vf_060, as the image's vtable has it (a trivial body, folded into
    // sub_32260 with every other copy).
    virtual RwInt32 vf_060(type_3D3548 *arg_0)
    {
        return 0;
    }
    // vf_068, as the image's vtable has it (a trivial body, folded into
    // sub_32260 with every other copy).
    virtual RwInt32 vf_068(struct type_758F0 *arg_0)
    {
        return 0;
    }
    // vf_03C, as the image's vtable has it (a trivial body, folded into
    // sub_FB410 with every other copy).
    virtual void vf_03C(RwReal arg_0)
    {
        type_3D3548::vf_03C(arg_0);
    }
    // vf_058, as the image's vtable has it (a trivial body, folded into
    // sub_75E40 with every other copy).
    virtual RwInt32 vf_058(struct type_3DF8D8_04 *arg_0)
    {
        type_712B0 *var_4;

        var_4 = get_unk_34C();
        if (arg_0->unk_00 == var_4->unk_C0.unk_00 && arg_0->unk_04 == var_4->unk_C0.unk_04)
            return 1;
        if (arg_0->unk_00 == var_4->unk_C8.unk_00 && arg_0->unk_04 == var_4->unk_C8.unk_04)
            return 1;
        return 0;
    }
    // vf_098, as the image's vtable has it (a trivial body, folded into
    // sub_9C140 with every other copy).
    virtual type_3D2E7C *vf_098()
    {
        return (type_3D2E7C *)sub_67620(unk_3D4);
    }
};
// sub_71870: a new AI object from its pool, by handle (unit_071360).
RwUInt32 sub_71870();
// sub_D5B80: registers the entity arg_0 with arg_4 (7 for type_3D51C0);
// only the widths are known.
void sub_D5B80(type_3D3548 *arg_0, RwInt32 arg_4);
// Builds the entity for the trigger arg_0, or warns that there is no entity
// memory for it.
type_3D51C0 *sub_9AD40(type_712B0 *arg_0);
typedef RwChar type_3D51C0_size_check[sizeof(type_3D51C0) == 0x3E0 ? 1 : -1];

#endif
