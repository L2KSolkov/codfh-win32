/*
 * CPickupBehavior (the class name it registers with the class factory at
 * 0x30AE26, with its MakeNew, sub_C5D70, and its size, 0x28): a RenderWare
 * Studio behaviour that sets up a pickup's settings (type_4C09B0), anchored
 * at its vtables off_3D6B20 and off_3D6B18 (CEventHandler part, at +0x18),
 * which its constructor (sub_C5DF0) and destructor (sub_C5EF0) install.
 */
#ifndef CPICKUPBEHAVIOR_H
#define CPICKUPBEHAVIOR_H

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/ceventhandler.h"
#include "rws/linearallocationpolicy.h"

class CPickupBehavior : public RWS::CAttributeHandler, public RWS::CEventHandler,
                        public RWS::LinearAllocationPolicy
{
public:
    RWS_MAKENEWCLASS(CPickupBehavior);
    RWS_DECLARE_CLASSID(CPickupBehavior);

    CPickupBehavior(const RWS::CAttributePacket &attr);
    ~CPickupBehavior();

    // Folded (/OPT:ICF) into CWeaponBehavior's (sub_C47F0), which it is
    // identical to: on dword_4B8750 it sets unk_24, once.
    virtual void HandleEvents(RWS::CMsg &pMsg);
    virtual void HandleAttributes(const RWS::CAttributePacket &attr);

    RwInt32 unk_20;             // command 0: which settings (sub_FB6C0; -1
                                // for none)
    RwInt32 unk_24;             // set on dword_4B8750
};
typedef RwChar CPickupBehavior_size_check[sizeof(CPickupBehavior) == 0x28 ? 1 : -1];

#endif
