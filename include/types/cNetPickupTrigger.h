/*
 * cNetPickupTrigger: a RenderWare Studio behaviour, named by the class name
 * it registers with the class factory ("cNetPickupTrigger", with its
 * MakeNew, sub_1BE0B0, and size 0x100, docs/behaviours.md). A PickupTrigger
 * for network games: its pickups are network pick-ups (sub_1BD340), taken
 * into the pick-up list (dword_4FBB20) by the host when the game starts if
 * its game types (command 0) and team masks (command 1) allow; it registers
 * its visibility message, "kujuUpdateTriggerObjectVisibility". Vtables:
 * off_3E2EF8 and off_3E2EF0 (its CEventHandler part, at +0x18).
 */
#ifndef CNETPICKUPTRIGGER_H
#define CNETPICKUPTRIGGER_H

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/ceventhandler.h"
#include "game/netvis.h"
#include "types/PickupTrigger.h"

class cNetPickupTrigger : public PickupTrigger
{
public:
    RWS_MAKENEWCLASS(cNetPickupTrigger);
    RWS_DECLARE_CLASSID(cNetPickupTrigger);

    cNetPickupTrigger(const RWS::CAttributePacket &attr);
    ~cNetPickupTrigger();

    virtual void HandleAttributes(const RWS::CAttributePacket &attr);
    virtual void HandleEvents(RWS::CMsg &pMsg);
    // Its pickup: a network pick-up (sub_1BD340).
    virtual type_3D3548 *vf_020();

    // Commands 0 and 1.
    void sub_1BE460(RWS::CAttributeCommandIterator &arg_0);
    void sub_1BE490(RWS::CAttributeCommandIterator &arg_0);
    // Empty and out of line, folded (/OPT:ICF) into sub_15FB30: the
    // attributes' commands pass it unk_4FD6D4, the visibility message its
    // data; only the width is known.
    void sub_15FB30(void *arg_0);

    RwUInt32 unk_E0;            // command 0: the game types it spawns in
    RwUInt32 unk_E4;            // command 1: its team mask
    RWS::CEventId unk_E8;       // its visibility message
    RwUInt8 unk_F0[0x10];
};
typedef RwChar cNetPickupTrigger_size_check[sizeof(cNetPickupTrigger) == 0x100 ? 1 : -1];

#endif
