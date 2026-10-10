/*
 * PickupTrigger (the class name it registers with the class factory at
 * 0x30A8B9, with its MakeNew, sub_A93B0, and its size, 0xE0): a trigger of
 * kind 0x18 derived from Trigger that spawns pickups (sub_FA9E0), anchored
 * at its vtables off_3D5F44 and off_3D5F3C (+0x18), which its constructor
 * (sub_A9430) and destructor (sub_A9530) install. Once its pickup is taken
 * (sub_A9910) it counts its respawn time on iMsgRunningTick and respawns it
 * when the player is within 5000 units; dword_4B67B8 restores its respawns.
 */
#ifndef PICKUPTRIGGER_H
#define PICKUPTRIGGER_H

#include "rw/ostypes.h"
#include "types/type_44350.h"

class PickupTrigger : public Trigger
{
public:
    RWS_MAKENEWCLASS(PickupTrigger);
    RWS_DECLARE_CLASSID(PickupTrigger);

    PickupTrigger(const RWS::CAttributePacket &attr);
    ~PickupTrigger();

    virtual void HandleAttributes(const RWS::CAttributePacket &attr);
    virtual void HandleEvents(RWS::CMsg &pMsg);
    // Its kind (0x18).
    // Inline: the constructor's vtable emits them after it, before ??_G (the image's order).
    virtual RwInt32 vf_008()
    {
        return 0x18;
    }
    // Its pickup (sub_FA9E0), while it has respawns left (unk_D8).
    virtual type_3D3548 *vf_020();

    // Its pickup was taken: starts the respawn clock, if it respawns
    // (sub_106A60).
    void sub_A9910();

    RwInt32 unk_C0;             // command 0 (-1 by default)
    RwInt32 unk_C4;             // command 1
    RwInt32 unk_C8;             // command 2 (1 by default)
    RwReal unk_CC;              // command 3: the respawn time, in seconds
                                // (times 60; -60 by default, none)
    RwReal unk_D0;              // the respawn clock
    RwInt32 unk_D4;             // set while it counts
    RwInt32 unk_D8;             // the respawns left (command 4; unk_DC
                                // again on dword_4B67B8; -1 by default,
                                // unlimited)
    RwInt32 unk_DC;             // command 4
};
typedef RwChar PickupTrigger_size_check[sizeof(PickupTrigger) == 0xE0 ? 1 : -1];

// Spawns the pickup of the trigger arg_0.
type_3D3548 *sub_FA9E0(PickupTrigger *arg_0);

#endif
