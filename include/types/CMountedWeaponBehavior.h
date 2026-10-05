/*
 * CMountedWeaponBehavior (the class name it registers with the class factory
 * at 0x30A766, with its MakeNew, sub_A4950, and its size, 0x24): a RenderWare
 * Studio behaviour that sets up a mounted weapon's settings (type_4E1B70),
 * anchored at its vtables off_3D5E14 and off_3D5E0C (CEventHandler part, at
 * +0x18), which its constructor (sub_A49D0) and destructor (sub_A4A80)
 * install.
 */
#ifndef CMOUNTEDWEAPONBEHAVIOR_H
#define CMOUNTEDWEAPONBEHAVIOR_H

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/ceventhandler.h"
#include "rws/linearallocationpolicy.h"

class CMountedWeaponBehavior : public RWS::CAttributeHandler, public RWS::CEventHandler,
                               public RWS::LinearAllocationPolicy
{
public:
    RWS_MAKENEWCLASS(CMountedWeaponBehavior);
    RWS_DECLARE_CLASSID(CMountedWeaponBehavior);

    CMountedWeaponBehavior(const RWS::CAttributePacket &attr);
    ~CMountedWeaponBehavior()
    {
    }

    // Empty: folded (/OPT:ICF) into sub_15FB30.
    virtual void HandleEvents(RWS::CMsg &pMsg);
    virtual void HandleAttributes(const RWS::CAttributePacket &attr);

    RwInt32 unk_20;             // command 0: which settings (sub_166990)
};
typedef RwChar CMountedWeaponBehavior_size_check[sizeof(CMountedWeaponBehavior) == 0x24 ? 1 : -1];

#endif
