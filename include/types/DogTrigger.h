/*
 * DogTrigger (the class name it registers with the class factory at
 * 0x30A739, with its MakeNew, sub_A3E80, and its size, 0x130): a trigger of
 * kind 6 derived from Trigger, that spawns a dog, anchored at its vtables
 * off_3D5DC4 and off_3D5DBC (+0x18), which its constructor (sub_A3F00) and
 * destructor (sub_A4130) install.
 */
#ifndef DOGTRIGGER_H
#define DOGTRIGGER_H

#include "rw/ostypes.h"
#include "types/type_3DF8D8.h"
#include "types/type_44350.h"
#include "types/type_D48D0.h"

class DogTrigger : public Trigger
{
public:
    RWS_MAKENEWCLASS(DogTrigger);
    RWS_DECLARE_CLASSID(DogTrigger);

    DogTrigger(const RWS::CAttributePacket &attr);
    ~DogTrigger();

    virtual void HandleAttributes(const RWS::CAttributePacket &attr);
    // Folded (/OPT:ICF) into CCESSPoolTrigger's (sub_A2BF0): it passes its
    // events to Trigger's.
    virtual void HandleEvents(RWS::CMsg &pMsg);
    // Its kind (6; folded into another's, sub_15FD20) and its key (&unk_D0;
    // folded into SoldierTrigger's, sub_A17D0).
    virtual RwInt32 vf_008();
    virtual type_3DF8D8_04 *vf_01C();
    // Its child: a type_3D5658 spawned for it (sub_9C1E0), when its model's
    // name is known and the third animation pool has players free or its
    // unk_24_18 is set.
    virtual type_3D3548 *vf_020();

    // Posts the messages of its block (unk_124) to arg_0, up to the first
    // unused one (type_3D5658's sub_9C6E0).
    void sub_A48B0(type_3D2E7C *arg_0);

    RwUInt8 unk_C0[0x6];        // the last two set; command 15's value at +2
    RwInt16 unk_C6[0x5];        // -1; commands 16 to 18 set the first three
    type_3DF8D8_04 unk_D0;      // command 0, a name of the kind 0x2C
    type_3DF8D8_04 unk_D8;      // command 1: its model's name, of the kind
                                // 3 (0x30 with unk_118 set)
    type_3DF8D8_04 unk_E0;      // command 4, of the kind 0xA
    type_3DF8D8_04 unk_E8;      // command 5 when set, of the kind 0xC
    RwReal unk_F0;              // commands 8 and 9: the cosines of half
    RwReal unk_F4;              // their angles (in degrees)
    RwReal unk_F8;              // commands 10, 11, 12 and 13 (the first,
    RwReal unk_FC;              // second and fourth times 100)
    RwReal unk_100;
    RwReal unk_104;
    RwInt32 unk_108;            // command 14
    RwReal unk_10C;
    RwReal unk_110;
    RwInt32 unk_114;            // command 6 (0 read as 2)
    RwInt32 unk_118;            // commands 2 and 3
    RwInt32 unk_11C;
    type_D48D0 unk_120;         // an entity (a handle)
    RwUInt8 *unk_124;           // command 7: its messages' block (sub_BD490)
    RwUInt8 unk_128[0x8];
};
typedef RwChar DogTrigger_size_check[sizeof(DogTrigger) == 0x130 ? 1 : -1];

#endif
