/*
 * cNetSpawnPoint: a RenderWare Studio behaviour, named by the class name it
 * registers with the class factory ("cNetSpawnPoint", with its MakeNew,
 * sub_1C0910, and size 0x100, docs/behaviours.md). A Trigger marking where
 * network players spawn: when the game starts it joins the spawn points'
 * lists (unk_4FBC50, sub_1C1CE0) if its game types (command 0) and team
 * masks (command 1) allow, by the teams it serves (command 2) and its group
 * (commands 3 and 4); it registers its visibility message,
 * "kujuUpdateTriggerObjectVisibility". Vtables: off_3E3338 and off_3E3330
 * (its CEventHandler part, at +0x18).
 */
#ifndef CNETSPAWNPOINT_H
#define CNETSPAWNPOINT_H

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/ceventhandler.h"
#include "game/netvis.h"
#include "types/type_44350.h"
#include "game/netvec.h"

class cNetSpawnPoint : public Trigger
{
public:
    RWS_MAKENEWCLASS(cNetSpawnPoint);
    RWS_DECLARE_CLASSID(cNetSpawnPoint);

    cNetSpawnPoint(const RWS::CAttributePacket &attr);
    ~cNetSpawnPoint();

    virtual void HandleEvents(RWS::CMsg &pMsg);
    virtual void HandleAttributes(const RWS::CAttributePacket &attr);
    // Its kind: 0x25.
    // Inline: the constructor's vtable emits them after it, before ??_G (the image's order).
    virtual RwInt32 vf_008()
    {
        return 0x25;
    }

    // Commands 0 to 4.
    void sub_1C0D80(RWS::CAttributeCommandIterator &arg_0);
    void sub_1C0DB0(RWS::CAttributeCommandIterator &arg_0);
    void sub_1C0DE0(RWS::CAttributeCommandIterator &arg_0);
    void sub_1C0E10(RWS::CAttributeCommandIterator &arg_0);
    void sub_1C0E60(RWS::CAttributeCommandIterator &arg_0);
    // Empty and out of line, folded (/OPT:ICF) into sub_15FB30: the
    // attributes' commands pass it unk_4FD6D4, the visibility message its
    // data; only the width is known.
    void sub_15FB30(void *arg_0);
    // Its position (its matrix's) into *arg_0 (the spawn lists' tests).
    void sub_1C0F20(type_1F8560_v *arg_0);

    // Inline accessors for unk_C0 and unk_D0, with no addresses and so no
    // database names; named for their fields. Evidence: the spawn lists'
    // pick (sub_1C1010) and sorting (sub_1C1CE0) read each through a slot
    // of its own.
    RwInt32 get_unk_C0()
    {
        RwInt32 r = unk_C0;
        return r;
    }
    RwInt32 get_unk_D0()
    {
        RwInt32 r = unk_D0;
        return r;
    }

    RwInt32 unk_C0;             // its index in the list of all points
                                // (sub_1C1CE0)
    RwUInt32 unk_C4;            // command 0: the game types it serves
    RwUInt32 unk_C8;            // command 1: the player limits it serves
                                // (tested against unk_4F61F8.unk_108)
    RwUInt32 unk_CC;            // command 2: the teams it spawns (2, 4)
    RwInt32 unk_D0;             // command 3: set when its value is -1
    RwInt32 unk_D4;             // command 4: its group (-1 at first)
    RWS::CEventId unk_D8;       // its visibility message
    RwUInt32 unk_E0;            // commands 5 to 8: four level sections
    RwUInt32 unk_E4;            // streamed when a player spawns here
    RwUInt32 unk_E8;            // (sub_1C1B60 gives them to the manager)
    RwUInt32 unk_EC;
    RwUInt8 unk_F0[0x10];
};
typedef RwChar cNetSpawnPoint_size_check[sizeof(cNetSpawnPoint) == 0x100 ? 1 : -1];

#endif
