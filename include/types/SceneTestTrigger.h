/*
 * SceneTestTrigger (the class name it registers with the class factory at
 * 0x30A619, with its MakeNew, sub_A2080, and its size, 0x1B0): a soldier spawner (SoldierTrigger) for testing scenes,
 * anchored at its vtables off_3D5BD4 and off_3D5BCC (+0x18), which its
 * constructor (sub_A2100) and destructor (sub_A21A0) install.
 */
#ifndef SCENETESTTRIGGER_H
#define SCENETESTTRIGGER_H

#include "rw/ostypes.h"
#include "types/SoldierTrigger.h"
#include "types/type_72810.h"

class SceneTestTrigger : public SoldierTrigger
{
public:
    RWS_MAKENEWCLASS(SceneTestTrigger);
    RWS_DECLARE_CLASSID(SceneTestTrigger);

    SceneTestTrigger(const RWS::CAttributePacket &attr);
    ~SceneTestTrigger()
    {
    }

    virtual void HandleAttributes(const RWS::CAttributePacket &attr);

    RwInt8 unk_1A0[0x6];        // its scene values: the last two set
    RwUInt8 unk_1A6[0x2];
    type_198900_perf *unk_1A8;  // its performance map (command 3)
    RwUInt8 unk_1AC[0x4];
};
typedef RwChar SceneTestTrigger_size_check[sizeof(SceneTestTrigger) == 0x1B0 ? 1 : -1];

#endif
