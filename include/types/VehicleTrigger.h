/*
 * VehicleTrigger (the class name it registers with the class factory at
 * 0x30ACA9, with its MakeNew, sub_BF960, and its size, 0x200): a trigger of
 * kind 7 derived from Trigger that spawns a vehicle (a jeep, sub_14C820, or a
 * tank, sub_155470, by unk_E8), anchored at its vtables off_3D69AC and
 * off_3D69A4 (+0x18), which its constructor (sub_BF9E0) and destructor
 * (sub_BFDA0) install. FlakTrigger derives from it.
 */
#ifndef VEHICLETRIGGER_H
#define VEHICLETRIGGER_H

#include "rw/batypes.h"
#include "rw/ostypes.h"
#include "types/type_3DF8D8.h"
#include "types/type_44350.h"

struct type_3D2E7C;

class VehicleTrigger : public Trigger
{
public:
    RWS_MAKENEWCLASS(VehicleTrigger);
    RWS_DECLARE_CLASSID(VehicleTrigger);

    VehicleTrigger(const RWS::CAttributePacket &attr);
    ~VehicleTrigger();

    virtual void HandleAttributes(const RWS::CAttributePacket &attr);
    // On dword_4B8750 (once) and dword_4B67C0 it creates its child.
    virtual void HandleEvents(RWS::CMsg &pMsg);
    // Its kind (7).
    // Inline: the constructor's vtable emits them after it, before ??_G (the image's order).
    virtual RwInt32 vf_008()
    {
        return 7;
    }
    // Its key (&unk_E0; folded, /OPT:ICF, into AnimatedBGTrigger's,
    // sub_9F4D0).
    virtual type_3DF8D8_04 *vf_01C();
    virtual type_3D3548 *vf_020();
    // Three of its flags (unk_1BC, bits 0 to 2): out of line after
    // FlakTrigger's constructor, the first object to use them.
    // Inline: the constructor's vtable emits them after it, before ??_G (the image's order).
    virtual RwInt32 vf_030()
    {
        return unk_1BC & 1;
    }
    virtual RwInt32 vf_034()
    {
        return unk_1BC & 2;
    }
    virtual RwInt32 vf_038()
    {
        return unk_1BC & 4;
    }

    // Tells its script object to create its child ("CreateChild") when it
    // has one and unk_EC is 2.
    void sub_C0F30();
    // Posts the messages of its block (unk_1FC) to arg_0, up to the first
    // unused one (as DogTrigger's sub_A48B0).
    void sub_C1010(type_3D2E7C *arg_0);

    type_3DF8D8_04 unk_C0;      // command 2: its model's name (kind 0x27)
    type_3DF8D8_04 unk_C8;      // commands 3, 13 to 15 and 0: names
    type_3DF8D8_04 unk_D0;
    type_3DF8D8_04 unk_D8;
    type_3DF8D8_04 unk_E0;      // its own name ("VehicleTrigger_GetMyName")
    RwInt32 unk_E8;             // its vehicle: 0 a jeep, 1 a tank (-1)
    RwInt32 unk_EC;
    RwInt32 unk_F0;             // 10000
    RwInt32 unk_F4;             // 7500
    RwReal unk_F8;              // 60
    RwInt32 unk_FC;
    RwInt32 unk_100;
    RwV3d unk_104;
    RwInt32 unk_110;
    RwInt32 unk_114;
    RwUInt8 unk_118[0xC];
    RwReal unk_124;             // the cosines of half two angles (in
    RwReal unk_128;             // degrees; 60 by default)
    RwReal unk_12C;             // 7000, times 100 from their commands
    RwReal unk_130;
    RwReal unk_134;             // 2500
    RwReal unk_138;             // 500
    RwInt32 unk_13C;
    RwInt32 unk_140;            // 200
    RwInt32 unk_144;            // 500
    RwInt32 unk_148;
    RwReal unk_14C;             // halved from their commands
    RwReal unk_150;
    RwReal unk_154;             // 1
    RwReal unk_158;             // the first angle, as given
    RwInt32 unk_15C;
    RwInt32 unk_160;
    RwInt32 unk_164;
    RwInt32 unk_168;
    RwInt32 unk_16C;            // (its command clears the next three)
    RwInt32 unk_170;
    RwInt32 unk_174;
    RwInt32 unk_178;
    RwInt32 unk_17C;
    RwInt32 unk_180;
    RwInt32 unk_184;
    RwInt32 unk_188;
    RwInt32 unk_18C;
    RwInt32 unk_190;
    RwInt32 unk_194;
    RwInt32 unk_198;
    RwInt32 unk_19C;
    RwReal unk_1A0;             // 360
    RwInt32 unk_1A4;
    RwInt32 unk_1A8;
    RwInt32 unk_1AC;
    RwInt32 unk_1B0;
    RwInt32 unk_1B4;
    RwInt32 unk_1B8;
    RwInt32 unk_1BC;            // flags (vf_030 to vf_038)
    type_3DF8D8_04 unk_1C0;     // a name of the kind 0xA
    RwInt32 unk_1C8;
    RwInt32 unk_1CC;
    RwInt32 unk_1D0;
    RwReal unk_1D4;             // halved unless -1
    RwReal unk_1D8;
    RwInt32 unk_1DC;
    RwInt32 unk_1E0;
    RwInt32 unk_1E4;
    RwInt32 unk_1E8;
    type_3DF8D8_04 unk_1EC;     // when set
    RwInt32 unk_1F4;            // commands 4 and 5
    RwInt32 unk_1F8;
    RwUInt8 *unk_1FC;           // its messages' block (sub_BD490)
};
typedef RwChar VehicleTrigger_size_check[sizeof(VehicleTrigger) == 0x200 ? 1 : -1];

#endif
