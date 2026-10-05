/*
 * CCESSPoolTrigger (the class name it registers with the class factory at
 * 0x30A649, with its MakeNew, sub_A23F0, and its size, 0x160): the CCESS
 * pool manager, a trigger of kind 0x19 derived from Trigger, anchored at its
 * vtables off_3D5C38 and off_3D5C30 (+0x18), which its constructor
 * (sub_A2470) and destructor (sub_A2560) install. "SetCCESSPoolManager"
 * (sub_8B770) makes one the pool's (dword_4B2174, types/ccess.h); its data
 * are the pool's settings.
 */
#ifndef CCESSPOOLTRIGGER_H
#define CCESSPOOLTRIGGER_H

#include "rw/ostypes.h"
#include "types/type_44350.h"

// The settings for one kind of slot: per index, the most trackers, the
// delay, whether the delay is random, and the picks a round.
struct type_4B2174_C0
{
    RwInt32 unk_00[5];
    RwReal unk_14[5];
    RwInt32 unk_28[5];
    RwInt32 unk_3C[5];
};

class CCESSPoolTrigger : public Trigger
{
public:
    RWS_MAKENEWCLASS(CCESSPoolTrigger);
    RWS_DECLARE_CLASSID(CCESSPoolTrigger);

    CCESSPoolTrigger(const RWS::CAttributePacket &attr);
    ~CCESSPoolTrigger()
    {
    }

    virtual void HandleAttributes(const RWS::CAttributePacket &attr);
    virtual void HandleEvents(RWS::CMsg &pMsg);
    // Its kind (0x19).
    // Inline: the constructor's vtable emits them after it, before ??_G (the image's order).
    virtual RwInt32 vf_008()
    {
        return 0x19;
    }

    type_4B2174_C0 unk_C0[2];
};
typedef RwChar CCESSPoolTrigger_size_check[sizeof(CCESSPoolTrigger) == 0x160 ? 1 : -1];

#endif
