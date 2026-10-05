/*
 * StreamVolume (the class name it registers with the class factory at
 * 0x30ABE9, with its MakeNew, sub_BB380, and its size, 0x110): a trigger of
 * kind 0xE derived from Trigger that fades a music stream's channels to new
 * volumes, anchored at its vtables off_3D6700 and off_3D66F8 (+0x18), which
 * its constructor (sub_BB400) and destructor (sub_BB460) install.
 */
#ifndef STREAMVOLUME_H
#define STREAMVOLUME_H

#include "rw/ostypes.h"
#include "types/type_44350.h"

class StreamVolume : public Trigger
{
public:
    RWS_MAKENEWCLASS(StreamVolume);
    RWS_DECLARE_CLASSID(StreamVolume);

    StreamVolume(const RWS::CAttributePacket &attr);
    ~StreamVolume()
    {
    }

    virtual void HandleAttributes(const RWS::CAttributePacket &attr);
    // Folded (/OPT:ICF) into CCESSPoolTrigger's (sub_A2BF0): it passes its
    // events to Trigger's.
    virtual void HandleEvents(RWS::CMsg &pMsg);
    // Its kind (0xE).
    // Inline: the constructor's vtable emits them after it, before ??_G (the image's order).
    virtual RwInt32 vf_008()
    {
        return 0xE;
    }

    // Fades its player's channels to its volumes (unk_C4, in percent of the
    // stream's) over unk_E4 frames each.
    // A new virtual (slot 12, 0x30: the image's vtable ends with it; IDA's sub_BB860).
    virtual void vf_030();

    RwInt32 unk_C0;             // command 0: the music player (0 to 2)
    RwInt32 unk_C4[8];          // commands 1 to 8: the channels' volumes
    RwInt32 unk_E4[8];          // commands 9 to 16: their fades' lengths
    RwUInt8 unk_104[0xC];
};
typedef RwChar StreamVolume_size_check[sizeof(StreamVolume) == 0x110 ? 1 : -1];

#endif
