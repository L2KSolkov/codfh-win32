/*
 * CWeaponBehavior (the class name it registers with the class factory at
 * 0x30ACD6, with its MakeNew, sub_C10B0, and its size, 0x28): a RenderWare
 * Studio behaviour that sets up a weapon's settings (type_4C19C0), anchored
 * at its vtables off_3D6A5C and off_3D6A54 (CEventHandler part, at +0x18),
 * which its constructor (sub_C1130) and destructor (sub_C1230) install.
 * CExplosiveBehavior, CTankBehavior, CAntiTankBehavior and CGrenadeBehavior
 * come from the same source file (their MakeNews share one EH handler, and
 * their this-adjusting thunks follow CGrenadeBehavior's functions).
 */
#ifndef CWEAPONBEHAVIOR_H
#define CWEAPONBEHAVIOR_H

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/ceventhandler.h"
#include "rws/linearallocationpolicy.h"

class CWeaponBehavior : public RWS::CAttributeHandler, public RWS::CEventHandler,
                        public RWS::LinearAllocationPolicy
{
public:
    RWS_MAKENEWCLASS(CWeaponBehavior);
    RWS_DECLARE_CLASSID(CWeaponBehavior);

    CWeaponBehavior(const RWS::CAttributePacket &attr);
    ~CWeaponBehavior();

    virtual void HandleEvents(RWS::CMsg &pMsg);
    virtual void HandleAttributes(const RWS::CAttributePacket &attr);

    RwInt32 unk_20;             // command 0, less 1: which settings
                                // (sub_119B70; -1 for none)
    RwInt32 unk_24;             // set on dword_4B8750: the players have
                                // their weapons, so some commands update
                                // their copies too
};
typedef RwChar CWeaponBehavior_size_check[sizeof(CWeaponBehavior) == 0x28 ? 1 : -1];

// CExplosiveBehavior (registered at 0x30AD06, with its MakeNew, sub_C4830;
// 0x28 bytes): a CWeaponBehavior whose commands 0 to 12 set the settings'
// explosion fields, anchored at its vtables off_3D6A6C and off_3D6A64
// (+0x18), which its constructor (sub_C48B0) and destructor (sub_C4900)
// install.
class CExplosiveBehavior : public CWeaponBehavior
{
public:
    RWS_MAKENEWCLASS(CExplosiveBehavior);
    RWS_DECLARE_CLASSID(CExplosiveBehavior);

    CExplosiveBehavior(const RWS::CAttributePacket &attr);
    ~CExplosiveBehavior();

    virtual void HandleEvents(RWS::CMsg &pMsg);
    virtual void HandleAttributes(const RWS::CAttributePacket &attr);
};

// CTankBehavior (registered at 0x30AD36, with its MakeNew, sub_C4C10; 0x28
// bytes): a CExplosiveBehavior with no commands of its own, anchored at its
// vtables off_3D6A7C and off_3D6A74 (+0x18).
class CTankBehavior : public CExplosiveBehavior
{
public:
    RWS_MAKENEWCLASS(CTankBehavior);
    RWS_DECLARE_CLASSID(CTankBehavior);

    CTankBehavior(const RWS::CAttributePacket &attr);
    ~CTankBehavior();

    virtual void HandleEvents(RWS::CMsg &pMsg);
    virtual void HandleAttributes(const RWS::CAttributePacket &attr);
};

// CAntiTankBehavior (registered at 0x30AD66, with its MakeNew, sub_C4D30;
// 0x28 bytes): a CExplosiveBehavior whose command 0 names a value
// (unk_4DC), anchored at its vtables off_3D6A8C and off_3D6A84 (+0x18).
class CAntiTankBehavior : public CExplosiveBehavior
{
public:
    RWS_MAKENEWCLASS(CAntiTankBehavior);
    RWS_DECLARE_CLASSID(CAntiTankBehavior);

    CAntiTankBehavior(const RWS::CAttributePacket &attr);
    ~CAntiTankBehavior();

    virtual void HandleEvents(RWS::CMsg &pMsg);
    virtual void HandleAttributes(const RWS::CAttributePacket &attr);
};

// CGrenadeBehavior (registered at 0x30AD96, with its MakeNew, sub_C4F10; 0x28
// bytes): a CExplosiveBehavior for settings 1 unless its CWeaponBehavior
// command 0 says otherwise, whose commands 0 to 11 set more, anchored at its
// vtables off_3D6A9C and off_3D6A94 (+0x18).
class CGrenadeBehavior : public CExplosiveBehavior
{
public:
    RWS_MAKENEWCLASS(CGrenadeBehavior);
    RWS_DECLARE_CLASSID(CGrenadeBehavior);

    CGrenadeBehavior(const RWS::CAttributePacket &attr);
    ~CGrenadeBehavior();

    virtual void HandleEvents(RWS::CMsg &pMsg);
    virtual void HandleAttributes(const RWS::CAttributePacket &attr);
};

#endif
