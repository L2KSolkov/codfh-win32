/*
 * type_3D5400: another entity class derived from type_3D3548, anchored at
 * its vtable off_3D5400. sub_9B700 spawns one (0x3E0 bytes) in entity
 * memory for a trigger through its inline constructor, which sets it up
 * with vf_234 (sub_9B8C0); its destructor (sub_9B860) takes it down with sub_9BAB0.
 */
#ifndef TYPE_3D5400_H
#define TYPE_3D5400_H

#include "rw/ostypes.h"
#include "types/type_3D3548.h"

struct type_3D5400 : type_3D3548
{
    // Defined in the class: sub_9B700 expands it (the base constructor, the
    // vtable, then vf_234).
    type_3D5400(type_712B0 *arg_0)
    {
        vf_234(arg_0);
    }
    // Sets it up from the trigger arg_0: a new virtual (slot 0x234: the image's vtable ends
    // with it, as type_3D51C0's does with its own; IDA's sub_9B8C0).
    virtual RwInt32 vf_234(type_712B0 *arg_0);

    // Overrides (out of line in unit_09AD40).
    // Struck by a vehicle or tank; hit by a bullet; by an explosion.
    virtual RwInt32 vf_060(type_3D3548 *arg_0);
    virtual RwInt32 vf_064(struct type_75600 *arg_0);
    virtual RwInt32 vf_068(struct type_758F0 *arg_0);
    virtual RwInt32 vf_058(struct type_3DF8D8_04 *arg_0);
    virtual type_3D2E7C *vf_098();
    virtual void vf_230();

    RwUInt8 unk_3A8[0x8];
    RwInt32 *unk_3B0;           // its sounds' state (sub_83850, kind 3)
    RwUInt8 unk_3B4[0x20];
    RwUInt32 unk_3D4;           // its AI object's handle (vf_098)
    RwInt32 unk_3D8;            // its health, from its trigger (sub_9B8C0)
    RwInt32 unk_3DC;            // set while it is up (vf_230)

    // Its destructor (sub_9B860) takes it down (vf_230); its scalar
    // deleting destructor is sub_9B830.
    ~type_3D5400();
    // The placement pair sub_9B700 builds it in entity memory with, as
    // type_3D32F8's (sub_6CCF0 and the empty sub_19A750).
    static void *operator new(RwUInt32 arg_0, void *arg_4);
    static void operator delete(void *arg_0, void *arg_4);
    // Its plain operator delete, for its scalar deleting destructor: empty
    // and out of line (folded into sub_19A750) like the base's; the
    // placement one hides the base's.
    static void operator delete(void *arg_0);
    // vf_034, as the image's vtable has it (a trivial body, folded into
    // sub_6FCD0 with every other copy).
    virtual RwInt32 vf_034()
    {
        return (RwInt32)this;
    }
    // vf_09C, as the image's vtable has it (a trivial body, folded into
    // sub_9AF10 with every other copy).
    virtual RwInt32 vf_09C()
    {
        return unk_3D4;
    }
    // vf_0A0, as the image's vtable has it (a trivial body, folded into
    // sub_9AF30 with every other copy).
    virtual void vf_0A0(RwUInt32 arg_0)
    {
        unk_3D4 = arg_0;
    }
    // vf_03C, as the image's vtable has it (a trivial body, folded into
    // sub_FB410 with every other copy).
    virtual void vf_03C(RwReal arg_0)
    {
        type_3D3548::vf_03C(arg_0);
    }
};
typedef RwChar type_3D5400_size_check[sizeof(type_3D5400) == 0x3E0 ? 1 : -1];

// Builds the entity for the trigger arg_0, or warns that there is no entity
// memory for it.
type_3D5400 *sub_9B700(type_712B0 *arg_0);

#endif
