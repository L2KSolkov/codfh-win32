/*
 * HitDeathTestTrigger (the class name it registers with the class factory at
 * 0x30A5E9, with its MakeNew, sub_A1CA0, and its size, 0x1B0): a soldier spawner (SoldierTrigger) for testing hit deaths,
 * anchored at its vtables off_3D5B70 and off_3D5B68 (+0x18), which its
 * constructor (sub_A1D20) and destructor (sub_A1DB0) install.
 */
#ifndef HITDEATHTESTTRIGGER_H
#define HITDEATHTESTTRIGGER_H

#include "rw/ostypes.h"
#include "types/SoldierTrigger.h"

class HitDeathTestTrigger : public SoldierTrigger
{
public:
    RWS_MAKENEWCLASS(HitDeathTestTrigger);
    RWS_DECLARE_CLASSID(HitDeathTestTrigger);

    HitDeathTestTrigger(const RWS::CAttributePacket &attr);
    ~HitDeathTestTrigger()
    {
    }

    virtual void HandleAttributes(const RWS::CAttributePacket &attr);

    RwInt8 unk_1A0[0xC];        // hit-death values: the last six set
    RwUInt8 unk_1AC[0x4];
};
typedef RwChar HitDeathTestTrigger_size_check[sizeof(HitDeathTestTrigger) == 0x1B0 ? 1 : -1];

#endif
