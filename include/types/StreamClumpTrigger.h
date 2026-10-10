/*
 * StreamClumpTrigger (the class name it registers with the class factory at
 * 0x30AE89, with its MakeNew, sub_C64A0, and its size, 0xD0): a trigger of
 * kind 0x1C derived from Trigger that requests a clump bank's load, for
 * the level or the player, anchored at its vtables off_3D6BA0 and
 * off_3D6B98 (+0x18), which its constructor (sub_C6520) and destructor
 * (sub_C6570) install.
 */
#ifndef STREAMCLUMPTRIGGER_H
#define STREAMCLUMPTRIGGER_H

#include "rw/ostypes.h"
#include "types/type_44350.h"

class StreamClumpTrigger : public Trigger
{
public:
    RWS_MAKENEWCLASS(StreamClumpTrigger);
    RWS_DECLARE_CLASSID(StreamClumpTrigger);

    StreamClumpTrigger(const RWS::CAttributePacket &attr);
    ~StreamClumpTrigger();

    virtual void HandleAttributes(const RWS::CAttributePacket &attr);
    // Folded (/OPT:ICF) into CCESSPoolTrigger's (sub_A2BF0): it passes its
    // events to Trigger's.
    virtual void HandleEvents(RWS::CMsg &pMsg);
    // Its kind (0x1C), folded (/OPT:ICF) into sub_1936A0.
    virtual RwInt32 vf_008();

    // Requests its clump bank's load: the level's (sub_16EEC0), or with
    // unk_C4 set the first player's (type_10F710::sub_10DA70).
    void sub_C6650();

    RwInt32 unk_C0;             // command 0: the clump bank (with unk_C4
                                // set, sub_10DA70 takes it as a weapon
                                // index: wbank_%02d.bin)
    RwInt32 unk_C4;             // command 1: set for the player's
    RwUInt8 unk_C8[0x8];
};
typedef RwChar StreamClumpTrigger_size_check[sizeof(StreamClumpTrigger) == 0xD0 ? 1 : -1];

#endif
