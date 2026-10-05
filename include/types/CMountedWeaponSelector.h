/*
 * CMountedWeaponSelector (the class name it registers with the class
 * factory at 0x30AFA6, with its MakeNew, sub_CA790, and its size, 0x20): a
 * RenderWare Studio behaviour that clears the mounted weapons' settings'
 * unk_F8 and registers the mounted weapons' names, anchored at its vtables
 * off_3D6D18 and off_3D6D10 (CEventHandler part, at +0x18), which its
 * constructor (sub_CA810) and destructor (sub_CA8C0) install.
 */
#ifndef CMOUNTEDWEAPONSELECTOR_H
#define CMOUNTEDWEAPONSELECTOR_H

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/ceventhandler.h"
#include "rws/linearallocationpolicy.h"

class CMountedWeaponSelector : public RWS::CAttributeHandler, public RWS::CEventHandler,
                               public RWS::LinearAllocationPolicy
{
public:
    RWS_MAKENEWCLASS(CMountedWeaponSelector);
    RWS_DECLARE_CLASSID(CMountedWeaponSelector);

    CMountedWeaponSelector(const RWS::CAttributePacket &attr);
    ~CMountedWeaponSelector()
    {
    }

    // Empty: folded (/OPT:ICF) into sub_15FB30.
    virtual void HandleEvents(RWS::CMsg &pMsg);
    virtual void HandleAttributes(const RWS::CAttributePacket &attr);

    // Clears the seven mounted weapons' settings' unk_F8, then registers the
    // names of the list arg_0 (a count, then the names) as mounted weapons
    // (kind 0x2F).
    void sub_CA9C0(const RwUInt32 *arg_0);
};
typedef RwChar CMountedWeaponSelector_size_check[sizeof(CMountedWeaponSelector) == 0x20 ? 1 : -1];

#endif
