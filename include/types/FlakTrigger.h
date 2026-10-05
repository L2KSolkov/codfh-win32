/*
 * FlakTrigger (the class name it registers with the class factory at
 * 0x30AC79, with its MakeNew, sub_BF650, and its size, 0x210): a vehicle
 * trigger (VehicleTrigger) that spawns a flak gun (sub_15A7B0), anchored at
 * its vtables off_3D6950 and off_3D6948 (+0x18), which its constructor
 * (sub_BF6D0) and destructor (sub_BF780) install.
 */
#ifndef FLAKTRIGGER_H
#define FLAKTRIGGER_H

#include "rw/ostypes.h"
#include "types/VehicleTrigger.h"

class FlakTrigger : public VehicleTrigger
{
public:
    RWS_MAKENEWCLASS(FlakTrigger);
    RWS_DECLARE_CLASSID(FlakTrigger);

    FlakTrigger(const RWS::CAttributePacket &attr);
    ~FlakTrigger()
    {
    }

    virtual void HandleAttributes(const RWS::CAttributePacket &attr);
    virtual void HandleEvents(RWS::CMsg &pMsg);
    // Its flak gun, when its model names an object of kind 3.
    virtual type_3D3548 *vf_020();

    RwReal unk_200;             // command 0, halved
    RwInt32 unk_204;            // commands 1 to 3
    RwInt32 unk_208;
    RwInt32 unk_20C;
};
typedef RwChar FlakTrigger_size_check[sizeof(FlakTrigger) == 0x210 ? 1 : -1];

#endif
