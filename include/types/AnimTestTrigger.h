/*
 * AnimTestTrigger (the class name it registers with the class factory at
 * 0x30A5B9, with its MakeNew, sub_A1690, and its size, 0x1C0): a soldier
 * spawner (SoldierTrigger) for testing animations, anchored at its vtables
 * off_3D5AEC and off_3D5AE4 (+0x18), which its constructor (sub_A1710) and
 * destructor (sub_A1830) install.
 */
#ifndef ANIMTESTTRIGGER_H
#define ANIMTESTTRIGGER_H

#include "rw/ostypes.h"
#include "types/SoldierTrigger.h"
#include "types/type_72810.h"

class AnimTestTrigger : public SoldierTrigger
{
public:
    RWS_MAKENEWCLASS(AnimTestTrigger);
    RWS_DECLARE_CLASSID(AnimTestTrigger);

    AnimTestTrigger(const RWS::CAttributePacket &attr);
    ~AnimTestTrigger()
    {
    }

    virtual void HandleAttributes(const RWS::CAttributePacket &attr);

    RwInt8 unk_1A0[0xC];        // hit-death values: the last six set
    type_198900_perf *unk_1AC;   // its performance maps (commands 7 and 9)
    type_198900_perf *unk_1B0;
    RwUInt8 unk_1B4[0xC];
};
typedef RwChar AnimTestTrigger_size_check[sizeof(AnimTestTrigger) == 0x1C0 ? 1 : -1];

#endif
