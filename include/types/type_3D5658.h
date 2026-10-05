/*
 * type_3D5658: an AI-driven entity class derived from type_3D3548,
 * anchored at its vtable off_3D5658, which its constructor (sub_9C2F0)
 * installs. sub_9C1E0 spawns one (0x19C0 bytes) in entity memory for a
 * trigger. It embeds a type_15CCE0 at +0x3B0 and its AI (AIData) at +0x520.
 */
#ifndef TYPE_3D5658_H
#define TYPE_3D5658_H

#include "rw/ostypes.h"
#include "types/type_3D3548.h"
#include "types/type_15CCE0.h"
#include "types/AIData.h"
#include "types/type_3D32F8.h"

struct type_3D5658 : type_3D3548
{
    // Builds it for the trigger arg_0: its members, then sub_9C6E0.
    type_3D5658(type_712B0 *arg_0);
    // Sets it up from the trigger arg_0.
    RwInt32 sub_9C6E0(type_712B0 *arg_0);

    // Overrides (out of line in unit_09AD40).
    virtual RwInt32 vf_16C(RwInt32 arg_0, RwInt32 arg_4);
    virtual void vf_1C4(RwInt32 arg_0);
    virtual void vf_210(type_D05C0 *arg_0);
    virtual void vf_230();
    virtual void vf_038(RwReal arg_0);
    virtual void vf_03C(RwReal arg_0);
    virtual void vf_04C(RwReal arg_0);
    virtual void vf_054(RwInt32 arg_0);
    virtual RwInt32 vf_058(struct type_3DF8D8_04 *arg_0);
    virtual void vf_078();
    virtual RwInt32 vf_07C(RwInt8 arg_0, RpIntersection *arg_4, RwReal *arg_8, RwInt32 arg_C);
    virtual RwInt32 vf_064(type_75600 *arg_0);
    virtual RwInt32 vf_068(type_758F0 *arg_0);
    // +0x060: a collision (its vtable's slot; +0x06C stays the base's).
    virtual RwInt32 vf_060(type_3D3548 *arg_0);
    virtual type_6D380 *vf_090();
    virtual type_3D2E7C *vf_098();
    virtual RwInt32 vf_0E4(RwInt32 arg_0);
    virtual RwInt32 vf_0E8();
    virtual void vf_0EC(RwInt32 arg_0, RwInt32 arg_4);
    virtual RwReal vf_0FC();
    virtual RwReal vf_100();
    virtual void vf_104(RwMatrix *arg_0);
    virtual void vf_108(RwV3d *arg_0);
    virtual RwReal vf_10C();
    virtual void vf_110(RwV3d *arg_0, type_3D3548 *arg_4, RwInt32 arg_8);
    virtual RwReal vf_114();
    virtual RwReal vf_130();
    virtual bool vf_224(struct type_3DF8D8 *arg_0, RwInt32 arg_4, RwInt32 *arg_8);
    // New virtuals: +0x234 returns this (sub_6FCD0, folded with others by
    // /OPT:ICF), +0x238 restarts unk_19A8 at 60, +0x23C whether it is
    // positive.
    virtual type_3D5658 *vf_234();
    virtual RwReal vf_238();
    // Inline: the constructor's vtable emits them after it, before ??_G (the image's order).
    virtual void vf_094(RwUInt32 arg_0)
    {
        unk_4D8 = arg_0;
    }
    virtual void vf_0A4(RwInt32 arg_0)
    {
        unk_19B8 = arg_0;
    }
    virtual RwInt32 vf_0A8()
    {
        return unk_19B8;
    }
    virtual RwUInt8 * vf_08C(RwInt32 arg_0, RwInt32 arg_4)
    {
        return unk_4DC;
    }
    virtual RwInt32 vf_09C()
    {
        return unk_4D4;
    }
    virtual void vf_0A0(RwUInt32 arg_0)
    {
        unk_4D4 = arg_0;
    }
    virtual RwInt32 vf_0AC()
    {
        return unk_4E8;
    }
    virtual void vf_0B0(RwInt32 arg_0, RwInt32 arg_4)
    {
        unk_4E8 = arg_0;
        vf_0B4();
    }
    virtual void vf_0B4()
    {
        unk_4EC = unk_4DC[3];
    }
    virtual void vf_0B8(RwInt32 arg_0)
    {
        unk_4EC = arg_0;
    }
    virtual RwUInt8 * vf_0E0()
    {
        return (RwUInt8 *)unk_510;
    }
    virtual RwInt8 * vf_0F0()
    {
        return unk_19AC;
    }
    virtual RwInt32 vf_174()
    {
        return unk_19A0;
    }
    virtual void vf_178(RwInt32 arg_0)
    {
        unk_19A0 = arg_0;
    }
    virtual void vf_180(RwInt32 arg_0)
    {
        unk_19A0 += arg_0;
    }
    virtual void vf_1B0(RwInt32 arg_0)
    {
        unk_520.unk_524 = arg_0;
    }
    virtual RwInt32 vf_23C()
    {
        return unk_19A8 > 0.0f ? 1 : 0;
    }
    virtual type_3D3548 * vf_118()
    {
        return unk_520.unk_54.sub_D4910();
    }
    virtual void vf_11C(type_3D3548 *arg_0)
    {
        unk_520.unk_54.sub_D48D0(arg_0);
    }
    virtual AIData * vf_120()
    {
        return &unk_520;
    }

    RwUInt8 unk_3A8[0x8];
    type_15CCE0 unk_3B0;
    RwInt32 *unk_4B0;           // its sounds' state (sub_83850, kind 5)
    RwUInt8 unk_4B4[0x20];
    RwUInt32 unk_4D4;           // its AI object's handle (vf_09C, vf_0A0)
    RwUInt32 unk_4D8;           // its script object's handle (vf_094)
    RwUInt8 unk_4DC[0xC];       // vf_08C's bytes; the fourth is vf_0B4's
                                // default (sub_9C6E0 clears them and sets
                                // the last six)
    RwInt32 unk_4E8;            // its posture (vf_0AC, vf_0B0)
    RwInt32 unk_4EC;            // vf_0B4, vf_0B8
    RwReal unk_4F0;             // vf_0FC: the cosine of AI parameter 2's
                                // half-angle
    RwReal unk_4F4;             // vf_100: likewise, a fixed half degree
    RwReal unk_4F8;             // vf_10C without a target
    RwReal unk_4FC;             // vf_10C with one; vf_114 by unk_500
    RwReal unk_500;
    RwReal unk_504;             // vf_130
    RwReal unk_508;             // AI parameters 0 and 1 (halved)
    RwReal unk_50C;
    RwUInt16 unk_510[8];        // its scene (vf_0E0, vf_0EC)
    AIData unk_520;             // its AI
    RwInt32 unk_19A0;           // its health (vf_174, vf_178, vf_180)
    RwInt32 unk_19A4;           // 1: vf_210 raises the step by two thirds
    RwReal unk_19A8;            // a countdown (vf_03C runs it down, vf_238
                                // restarts it at 60)
    RwInt8 unk_19AC[0xC];       // its hit-death values (vf_0F0)
    RwInt32 unk_19B8;           // performances disabled (vf_0A4, vf_0A8)
    RwInt32 unk_19BC;           // set while it is up (vf_230)

    // Its destructor (sub_9C660) takes it down (vf_230), then its AI and
    // its unk_3B0 go; its scalar deleting destructor is sub_9C630.
    ~type_3D5658();
    // The placement pair sub_9C1E0 builds it in entity memory with, as
    // type_3D32F8's (sub_6CCF0 and the empty sub_19A750).
    static void *operator new(RwUInt32 arg_0, void *arg_4);
    static void operator delete(void *arg_0, void *arg_4);
    // Its plain operator delete, for its scalar deleting destructor: empty
    // and out of line (folded into sub_19A750) like the base's; the
    // placement one hides the base's.
    static void operator delete(void *arg_0);
    // Collision_DispatchAtomicIntersectionsBySelectorFlag, as the image's vtable has it (a trivial body, folded into
    // sub_177080 with every other copy).
    virtual void Collision_DispatchAtomicIntersectionsBySelectorFlag(RpAtomic *arg_0,
                                                                     RpIntersection *arg_4,
                                                                     struct type_93700 *arg_8)
    {
        if (arg_8)
            arg_8->unk_5C = 1;
    }
    // vf_228, as the image's vtable has it (a trivial body, folded into
    // sub_13ACC0 with every other copy).
    virtual bool vf_228()
    {
        type_3D3548::vf_228();
        return true;
    }
    // vf_170, as the image's vtable has it (a trivial body, folded into
    // sub_75440 with every other copy).
    virtual void vf_170(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C)
    {
        if (unk_88_13)
            return;
        type_3D3548::vf_170(arg_0, arg_4, arg_8, arg_C);
    }
};
// Its trigger as it reads its scene actions: five words at +0xC6, -1
// ending them (vf_0E4, vf_0E8).
struct type_3D5658_trigger
{
    RwUInt8 unk_00[0xC6];
    RwInt16 unk_C6[5];
};
// Sets the vector arg_0: an inline function with no address, named for what
// it does. Evidence: vf_1C4 fills the entity's unk_10C through a pointer
// temporary, which an expanded function's parameter is.
inline void set_v3d(RwV3d *arg_0, RwReal arg_4, RwReal arg_8, RwReal arg_C)
{
    arg_0->x = arg_4;
    arg_0->y = arg_8;
    arg_0->z = arg_C;
}
// flt_429120 (1.5, in .data): what vf_210 divides the step's height by.
extern RwReal flt_429120;
typedef RwChar type_3D5658_size_check[sizeof(type_3D5658) == 0x19C0 ? 1 : -1];

// Builds the entity for the trigger arg_0, or warns that there is no entity
// memory for it.
type_3D5658 *sub_9C1E0(type_712B0 *arg_0);

#endif
