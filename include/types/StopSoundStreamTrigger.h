/*
 * StopSoundStreamTrigger (the class name it registers with the class
 * factory at 0x30AB89, with its MakeNew, sub_BA9E0, and its size, 0xD0): a
 * trigger of kind 0xF derived from Trigger that fades a music stream out,
 * anchored at its vtables off_3D666C and off_3D6664 (+0x18), which its
 * constructor (sub_BAA60) and destructor (sub_BAAC0) install.
 */
#ifndef STOPSOUNDSTREAMTRIGGER_H
#define STOPSOUNDSTREAMTRIGGER_H

#include "rw/ostypes.h"
#include "types/type_44350.h"

class StopSoundStreamTrigger : public Trigger
{
public:
    RWS_MAKENEWCLASS(StopSoundStreamTrigger);
    RWS_DECLARE_CLASSID(StopSoundStreamTrigger);

    StopSoundStreamTrigger(const RWS::CAttributePacket &attr);
    ~StopSoundStreamTrigger()
    {
    }

    virtual void HandleAttributes(const RWS::CAttributePacket &attr);
    // Folded (/OPT:ICF) into CCESSPoolTrigger's (sub_A2BF0): it passes its
    // events to Trigger's.
    virtual void HandleEvents(RWS::CMsg &pMsg);
    // Its kind (0xF).
    // Inline: the constructor's vtable emits them after it, before ??_G (the image's order).
    virtual RwInt32 vf_008()
    {
        return 0xF;
    }

    // Fades its stream's eight channels to silence over unk_C4 frames.
    // A new virtual (slot 12, 0x30: the image's vtable ends with it; IDA's sub_BABB0).
    virtual void vf_030();

    RwInt32 unk_C0;             // command 0: the music player (0 to 2),
    RwInt32 unk_C4;             // and the fade's length (at least 1)
    RwUInt8 unk_C8[0x8];
};
typedef RwChar StopSoundStreamTrigger_size_check[sizeof(StopSoundStreamTrigger) == 0xD0 ? 1 : -1];

#endif
