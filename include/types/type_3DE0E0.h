/*
 * type_3DE0E0: an entity class derived from type_3D3548, anchored at its
 * vtable off_3DE0E0, which sub_17E680 installs (off_3DE350, installed by
 * sub_180E00, derives from it). It is the class type_3D3548::vf_02C picks out:
 * its slot +0x02C returns this (sub_6FCD0). The script commands call it by
 * casting the entity once vf_02C is nonzero. It is the gimp vehicle a
 * GimpVehicleTrigger of type 0 makes (sub_17E680; unit_17E680): the string
 * after its vtable names "GimpVehicleEntity". Its guns are the tank's
 * (type_15B110), and several of its slots are folded (/OPT:ICF) with the
 * tank's.
 */
#ifndef TYPE_3DE0E0_H
#define TYPE_3DE0E0_H

#include "rw/ostypes.h"
#include "types/type_3D3548.h"
#include "types/type_D48D0.h"
#include "types/type_15B110.h"
#include "types/type_439E78.h"

struct type_3DE0E0 : type_3D3548
{
    virtual void vf_038(RwReal arg_0);
    virtual void vf_03C(RwReal arg_0);
    virtual void vf_04C(RwReal arg_0);
    virtual void vf_054(RwInt32 arg_0);
    virtual RwInt32 vf_058(struct type_3DF8D8_04 *arg_0);
    virtual RwInt32 vf_064(struct type_75600 *arg_0);
    virtual struct type_6D380 *vf_090();
    virtual void vf_094(RwUInt32 arg_0);
    virtual type_3D2E7C *vf_098();
    virtual RwInt32 vf_09C();
    virtual void vf_0A0(RwUInt32 arg_0);
    virtual RwUInt8 *vf_0E0();
    virtual void vf_0EC(RwInt32 arg_0, RwInt32 arg_4);
    virtual struct SplinePath *vf_0F4();
    virtual void vf_0F8(RwReal arg_0);
    virtual void vf_124(RwReal arg_0);
    // Its health (unk_980, up to unk_984), set, added to and as a fraction.
    virtual RwInt32 vf_174();
    virtual void vf_178(RwInt32 arg_0);
    virtual RwReal vf_17C();
    virtual void vf_180(RwInt32 arg_0);
    virtual void vf_230();
    // +0x234 (sub_17E860): fires continuously for arg_0
    // ("FireWeaponContinuous"): its guns' unk_300; returns 1.
    virtual RwInt32 vf_234(RwInt32 arg_0);
    // +0x238: 0 (folded into sub_32260); the subclass's sub_182960.
    virtual RwInt32 vf_238(RwInt32 arg_0)
    {
        return 0;
    }
    // +0x23C, +0x240: unk_988, and as a fraction of unk_98C.
    virtual RwInt32 vf_23C();
    virtual RwReal vf_240();
    // +0x244: 0 (folded into sub_1E4CB0); the subclass's sub_115460.
    virtual RwInt32 vf_244()
    {
        return 0;
    }
    // +0x248: -360 (the tank's vf_2E4 is folded into it).
    virtual RwReal vf_248();
    // +0x24C, +0x250: -1 and 360, folded into the tank's vf_2E8 and vf_2EC.
    virtual RwReal vf_24C()
    {
        return -1.0f;
    }
    virtual RwReal vf_250()
    {
        return 360.0f;
    }

    RwUInt8 unk_3A8[0x8];
    RwInt32 unk_3B0;            // how many of the bones 700 to 798 it has,
    RwInt16 unk_3B4[100];       // their indices (the set-up),
    RwInt16 unk_47C[100];       // and by index, 1 or 2 by the bind pose side
    RwInt32 unk_544;            // likewise the bones 650 to 698
    RwInt16 unk_548[50];
    RwInt16 unk_5AC[50];
    RwInt32 unk_610;            // the index of bone 100
    RwReal unk_614;             // its sides' track speeds, and the
    RwReal unk_618;             // angles its procedural track turns
    RwReal unk_61C;             // their wheels by (sub_17F620, in
    RwReal unk_620;             // degrees)
    RwInt32 unk_624;
    RwInt32 unk_628;
    RwInt32 unk_62C;
    struct type_7CBD0_hdr *unk_630; // its pose key (sub_17F620), its
                                    // rotations after it; freed by vf_230
    RwInt32 unk_634;            // that key's size
    RwInt32 unk_638;            // the gimp vehicle's move and fire states
    RwInt32 unk_63C;            // ("SetGimpVehicleMoveState", "...FireState")
    type_D48D0 unk_640;
    RwV3d unk_644;              // its goto point ("SetupGotoPoint")
    union                       // its move and rotation speeds
    {                           // ("SetGimpVehicleMoveSpeed", "...RotSpeed");
        RwReal unk_650;         // the set-up copies its trigger's commands 6
        RwInt32 unk_650_i;      // and 7 as they are
    };
    union
    {
        RwReal unk_654;
        RwInt32 unk_654_i;
    };
    type_15B110 unk_658;        // its guns
    RwInt32 unk_95C;
    RwInt32 unk_960;            // its trigger's type (unk_E0)
    RwUInt32 unk_964;           // its script object's handle (vf_09C, vf_0A0)
    union
    {
        RwUInt32 unk_968;       // its performance player's handle (vf_094;
        type_439E78_00 unk_968_h;   // the set-up copies it as the struct)
    };
    RwInt16 unk_96C[2];         // its scene map entry (vf_0E0, vf_0EC; the
    RwUInt8 unk_970[2];         // set-up clears the six bytes, then sets these)
    RwUInt8 unk_972[2];
    RwReal unk_974;             // its position on its spline path and the
    RwReal unk_978;             // speed along it (vf_124)
    struct SplinePath *unk_97C; // path ("SetSplinePathFromName"; vf_0F4)
    RwInt32 unk_980;            // its health, up to unk_984
    RwInt32 unk_984;
    RwInt32 unk_988;            // vf_23C, up to unk_98C
    RwInt32 unk_98C;

    // Built bare (the subclass's constructor, sub_180E00, sets it up).
    type_3DE0E0()
    {
    }
    // Built for the trigger arg_0 (its set-up, sub_17EA70).
    type_3DE0E0(class GimpVehicleTrigger *arg_0)
    {
        sub_17EA70(arg_0);
    }
    ~type_3DE0E0()
    {
        vf_230();
    }
    RwInt32 sub_17EA70(class GimpVehicleTrigger *arg_0);
    void sub_17F2E0(struct type_3DF8D8 *arg_0);
    // Drives toward arg_0 at the speed arg_4 turning at arg_8 over the step
    // arg_10; whether it is within arg_C of it.
    RwInt32 sub_1808D0(RwV3d *arg_0, RwReal arg_4, RwReal arg_8, RwReal arg_C, RwReal arg_10);
    // The placement pair it is built in entity memory with (sub_6CCF0 and
    // the empty sub_19A750), and its plain operator delete for its deleting
    // destructor (folded into sub_19A750 too).
    static void *operator new(RwUInt32 arg_0, void *arg_4);
    static void operator delete(void *arg_0, void *arg_4);
    static void operator delete(void *arg_0);

    // Targets arg_0 ("SetMyTarget").
    void sub_180CA0(type_3D3548 *arg_0);
    // vf_02C, as the image's vtable has it (a trivial body, folded into
    // sub_6FCD0 with every other copy).
    virtual struct type_3DE0E0 *vf_02C()
    {
        return this;
    }
};
// type_3DE350: the gimp vehicle of type 1 (sub_180CF0), anchored at its
// vtable off_3DE350, which its constructor sub_180E00 installs: a gimp
// vehicle with two more bones its procedural track (sub_181140) turns, its
// guns' tags "RIFA" to "RIFC", and three slots of its own. Its code shares
// unit_17E680 with its base's.
struct type_3DE350 : type_3DE0E0
{
    virtual void vf_038(RwReal arg_0);
    virtual void vf_03C(RwReal arg_0);
    virtual void vf_054(RwInt32 arg_0);
    virtual RwInt32 vf_058(struct type_3DF8D8_04 *arg_0);
    // Empty, folded into pDtor (0x1E41C0); its destructor calls it
    // directly (config/aliases.txt).
    virtual void vf_230();
    // Whether its gun arg_0 has rounds.
    virtual RwInt32 vf_238(RwInt32 arg_0);
    // +0x244: 1 (folded into sub_115460).
    virtual RwInt32 vf_244()
    {
        return 1;
    }
    // Fires its gun arg_0 (at the point arg_4, or ahead); 0 when it cannot.
    virtual RwInt32 vf_254(RwInt32 arg_0, RwV3d *arg_4);
    // Its turret's and its barrel's turn speeds (arg_4 unused).
    virtual void vf_258(RwReal arg_0, RwReal arg_4);
    virtual void vf_25C(RwReal arg_0, RwReal arg_4);

    RwInt32 unk_990;
    RwInt32 unk_994;
    RwReal unk_998;             // the angles its procedural track turns
    RwReal unk_99C;             // the bones unk_9A8 and unk_9AC by
    RwReal unk_9A0;             // its turret's and barrel's turn speeds
    RwReal unk_9A4;             // (vf_258, vf_25C)
    RwInt32 unk_9A8;            // the indices of bones 2 and 3
    RwInt32 unk_9AC;

    // The bare gimp vehicle, then its own set-up (sub_180F60). Defined in
    // the class but not inlined (sub_180CF0 still reserves its frame bytes).
    type_3DE350(class GimpVehicleTrigger *arg_0)
    {
        sub_180F60(arg_0);
    }
    ~type_3DE350()
    {
        vf_230();
    }
    RwInt32 sub_180F60(class GimpVehicleTrigger *arg_0);
    // Its main gun's shot (vf_254).
    RwInt32 sub_182990(RwInt32 arg_0);
    static void *operator new(RwUInt32 arg_0, void *arg_4);
    static void operator delete(void *arg_0, void *arg_4);
    static void operator delete(void *arg_0);
    // vf_030, as the image's vtable has it (a trivial body, folded into
    // sub_6FCD0 with every other copy).
    virtual struct type_3DE350 *vf_030()
    {
        return this;
    }
};
// How its turret and barrel, and its third gun, bear on a point
// (vf_03C).
RwInt32 sub_181A90(type_3DE350 *arg_0, RwV3d *arg_4, RwReal arg_8, RwV3d *arg_C, RwReal *arg_10, RwReal *arg_14,
                   RwReal *arg_18);
RwInt32 sub_181D20(type_3DE350 *arg_0, RwV3d *arg_4, RwV3d *arg_8, RwReal *arg_C);

typedef RwChar type_3DE350_size_check[sizeof(type_3DE350) == 0x9B0 ? 1 : -1];

// Its animation's procedural track (vf_038 starts it).
void sub_17F620(struct type_7C8D0 *arg_0, struct type_80300 *arg_4, RwInt32 arg_8, bool arg_C);
void sub_181140(struct type_7C8D0 *arg_0, struct type_80300 *arg_4, RwInt32 arg_8, bool arg_C);

typedef RwChar type_3DE0E0_size_check[sizeof(type_3DE0E0) == 0x990 ? 1 : -1];

#endif
