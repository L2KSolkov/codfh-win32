/*
 * SceneTrigger (the class name it registers with the class factory at
 * 0x30A979, with its MakeNew, sub_AF9C0, and its size, 0xD0): a trigger
 * derived from Trigger that plays a scene, anchored at its vtables
 * off_3D6380 and off_3D6378 (+0x18), which its constructor (sub_AFA40) and
 * destructor (sub_AFAD0) install.
 */
#ifndef SCENETRIGGER_H
#define SCENETRIGGER_H

#include "rw/ostypes.h"
#include "types/type_44350.h"

class SceneTrigger : public Trigger
{
public:
    RWS_MAKENEWCLASS(SceneTrigger);
    RWS_DECLARE_CLASSID(SceneTrigger);

    SceneTrigger(const RWS::CAttributePacket &attr);
    ~SceneTrigger()
    {
    }

    virtual void HandleAttributes(const RWS::CAttributePacket &attr);

    RwInt16 unk_C0;             // command 1
    RwInt16 unk_C2;             // command 0
    RwUInt8 unk_C4[0x2];        // both set
    RwUInt8 unk_C6[0xA];
};
typedef RwChar SceneTrigger_size_check[sizeof(SceneTrigger) == 0xD0 ? 1 : -1];

#endif
