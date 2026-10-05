/*
 * MountedWeaponTrigger (the class name it registers with the class factory
 * at 0x30A799, with its MakeNew, sub_A5360, and its size, 0x100): a trigger
 * of kind 0x1B derived from Trigger, that spawns a mounted weapon, anchored
 * at its vtables off_3D5E40 and off_3D5E38 (+0x18), which its constructor
 * (sub_A53E0) and destructor (sub_A5510) install.
 */
#ifndef MOUNTEDWEAPONTRIGGER_H
#define MOUNTEDWEAPONTRIGGER_H

#include "rw/ostypes.h"
#include "types/type_3DF8D8.h"
#include "types/type_44350.h"

class MountedWeaponTrigger : public Trigger
{
public:
    RWS_MAKENEWCLASS(MountedWeaponTrigger);
    RWS_DECLARE_CLASSID(MountedWeaponTrigger);

    MountedWeaponTrigger(const RWS::CAttributePacket &attr);
    ~MountedWeaponTrigger()
    {
    }

    virtual void HandleAttributes(const RWS::CAttributePacket &attr);
    // Folded (/OPT:ICF) into CCESSPoolTrigger's (sub_A2BF0): it passes its
    // events to Trigger's.
    virtual void HandleEvents(RWS::CMsg &pMsg);
    // Its kind (0x1B; folded into another's, sub_1B3C20), its key (&unk_E4)
    // and its child, the mounted weapon (sub_1669B0).
    virtual RwInt32 vf_008();
    // Inline: the constructor's vtable emits them after it, before ??_G (the image's order).
    virtual type_3DF8D8_04 * vf_01C()
    {
        return &unk_E4;
    }
    virtual type_3D3548 *vf_020();

    RwInt32 unk_C0;             // command 1 (1 by default)
    RwInt32 unk_C4;             // command 3
    RwInt32 unk_C8;             // commands 4 and 5
    RwInt32 unk_CC;
    RwInt32 unk_D0;             // command 13
    RwReal unk_D4;              // commands 10 and 11, halved unless -1
    RwReal unk_D8;              // (-1 by default)
    RwInt32 unk_DC;             // command 12 (-1 by default)
    RwInt32 unk_E0;             // command 2
    type_3DF8D8_04 unk_E4;      // command 0, of the kind 0x2E when set
    RwInt32 unk_EC;             // commands 7 to 9
    RwInt32 unk_F0;
    RwInt32 unk_F4;
    type_3DF8D8_04 unk_F8;      // command 6, a name of the kind 0xA
};
typedef RwChar MountedWeaponTrigger_size_check[sizeof(MountedWeaponTrigger) == 0x100 ? 1 : -1];

#endif
