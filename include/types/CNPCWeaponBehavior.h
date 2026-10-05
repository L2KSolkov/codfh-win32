/*
 * CNPCWeaponBehavior (the class name it registers with the class factory at
 * 0x30A7C6, with its MakeNew, sub_A58B0, and its size, 0x24): a RenderWare
 * Studio behaviour that sets up an NPC weapon's settings (type_4D53F8),
 * anchored at its vtables off_3D5E90 and off_3D5E88 (CEventHandler part, at
 * +0x18), which its constructor (sub_A5930) and destructor (sub_A5A30)
 * install.
 */
#ifndef CNPCWEAPONBEHAVIOR_H
#define CNPCWEAPONBEHAVIOR_H

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/ceventhandler.h"
#include "rws/linearallocationpolicy.h"

class CNPCWeaponBehavior : public RWS::CAttributeHandler, public RWS::CEventHandler,
                           public RWS::LinearAllocationPolicy
{
public:
    RWS_MAKENEWCLASS(CNPCWeaponBehavior);
    RWS_DECLARE_CLASSID(CNPCWeaponBehavior);

    CNPCWeaponBehavior(const RWS::CAttributePacket &attr);
    ~CNPCWeaponBehavior();

    virtual void HandleEvents(RWS::CMsg &pMsg);
    virtual void HandleAttributes(const RWS::CAttributePacket &attr);

    RwInt32 unk_20;             // command 0: which settings (sub_15CB10; -1
                                // for none)
};
typedef RwChar CNPCWeaponBehavior_size_check[sizeof(CNPCWeaponBehavior) == 0x24 ? 1 : -1];

#endif
