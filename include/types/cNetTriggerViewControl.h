/*
 * cNetTriggerViewControl: a RenderWare Studio behaviour, named by the class
 * name it registers with the class factory ("cNetTriggerViewControl", with
 * its MakeNew, sub_1C2AB0, and size 0x40, docs/behaviours.md). Its commands
 * set the network triggers' visibility (game types, team mask, teams, the
 * "any group" flag and the group), sent with the message
 * "kujuUpdateTriggerObjectVisibility" (game/netvis.h) whenever any is given.
 * Vtables: off_3E348C and off_3E3484 (its CEventHandler part, at +0x18).
 */
#ifndef CNETTRIGGERVIEWCONTROL_H
#define CNETTRIGGERVIEWCONTROL_H

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/ceventhandler.h"
#include "rws/linearallocationpolicy.h"
#include "game/netvis.h"

class cNetTriggerViewControl : public RWS::CAttributeHandler, public RWS::CEventHandler,
                               public RWS::LinearAllocationPolicy
{
public:
    RWS_MAKENEWCLASS(cNetTriggerViewControl);
    RWS_DECLARE_CLASSID(cNetTriggerViewControl);

    cNetTriggerViewControl(const RWS::CAttributePacket &attr);
    ~cNetTriggerViewControl();

    // Empty (folded by /OPT:ICF into sub_15FB30).
    virtual void HandleEvents(RWS::CMsg &pMsg)
    {
    }
    virtual void HandleAttributes(const RWS::CAttributePacket &attr);

    // Commands 0 to 4.
    void sub_1C2E80(RWS::CAttributeCommandIterator &arg_0);
    void sub_1C2EB0(RWS::CAttributeCommandIterator &arg_0);
    void sub_1C2EE0(RWS::CAttributeCommandIterator &arg_0);
    void sub_1C2F10(RWS::CAttributeCommandIterator &arg_0);
    void sub_1C2F50(RWS::CAttributeCommandIterator &arg_0);

    RwUInt8 unk_20[0x4];
    RwUInt32 unk_24;            // command 0: the game types
    RwUInt32 unk_28;            // command 1: the team mask
    RwUInt32 unk_2C;            // command 2: the teams
    RwInt32 unk_30;             // command 3: set when its value is -1
    RwInt32 unk_34;             // command 4: the group
    RWS::CEventId unk_38;       // the visibility message
};
typedef RwChar cNetTriggerViewControl_size_check[sizeof(cNetTriggerViewControl) == 0x40 ? 1 : -1];

#endif
