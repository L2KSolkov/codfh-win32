/*
 * CPickupSelector (the class name it registers with the class factory at
 * 0x30A886, with its MakeNew, sub_A90E0, and its size, 0x20): a RenderWare
 * Studio behaviour that registers the pickups' names, anchored at its
 * vtables off_3D5F20 and off_3D5F18 (CEventHandler part, at +0x18), which
 * its constructor (sub_A9160) and destructor (sub_A9210) install.
 */
#ifndef CPICKUPSELECTOR_H
#define CPICKUPSELECTOR_H

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/ceventhandler.h"
#include "rws/linearallocationpolicy.h"

class CPickupSelector : public RWS::CAttributeHandler, public RWS::CEventHandler,
                        public RWS::LinearAllocationPolicy
{
public:
    RWS_MAKENEWCLASS(CPickupSelector);
    RWS_DECLARE_CLASSID(CPickupSelector);

    CPickupSelector(const RWS::CAttributePacket &attr);
    ~CPickupSelector()
    {
    }

    // Empty: folded (/OPT:ICF) into sub_15FB30.
    virtual void HandleEvents(RWS::CMsg &pMsg);
    virtual void HandleAttributes(const RWS::CAttributePacket &attr);

    // Registers the names of the list arg_0 (a count, then the names) as
    // pickups (kind 0x2B).
    void sub_A9310(const RwUInt32 *arg_0);
};
typedef RwChar CPickupSelector_size_check[sizeof(CPickupSelector) == 0x20 ? 1 : -1];

#endif
