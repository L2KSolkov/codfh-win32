/*
 * StreamTrigger (the class name it registers with the class factory at
 * 0x30ABB9, with its MakeNew, sub_BAC50, and its size, 0x110): a trigger of
 * kind 0xC derived from Trigger that starts a music stream, anchored at its
 * vtables off_3D66B8 and off_3D66B0 (+0x18), which its constructor
 * (sub_BACD0) and destructor (sub_BAD50) install.
 */
#ifndef STREAMTRIGGER_H
#define STREAMTRIGGER_H

#include "rw/ostypes.h"
#include "types/type_3DF8D8.h"
#include "types/type_44350.h"

class StreamTrigger : public Trigger
{
public:
    RWS_MAKENEWCLASS(StreamTrigger);
    RWS_DECLARE_CLASSID(StreamTrigger);

    StreamTrigger(const RWS::CAttributePacket &attr);
    ~StreamTrigger()
    {
    }

    virtual void HandleAttributes(const RWS::CAttributePacket &attr);
    // On dword_4B67B8 its stream may start again (unk_24_6).
    virtual void HandleEvents(RWS::CMsg &pMsg);
    // Its kind (0xC).
    // Inline: the constructor's vtable emits them after it, before ??_G (the image's order).
    virtual RwInt32 vf_008()
    {
        return 0xC;
    }

    // Starts its stream (once, unless unk_108 is 0), with its channels'
    // volumes (unk_C8, in percent of the stream's) and fades (unk_E8).
    // A new virtual (slot 12, 0x30: the image's vtable ends with it; IDA's sub_BB1F0).
    virtual void vf_030();

    type_3DF8D8_04 unk_C0;      // command 1: the stream's name
    RwInt32 unk_C8[8];          // commands 2 to 9: its channels' volumes
    RwInt32 unk_E8[8];          // commands 10 to 17: their fades' lengths
    RwInt32 unk_108;            // command 0: set to play it only once
    RwUInt8 unk_10C[0x4];
};
typedef RwChar StreamTrigger_size_check[sizeof(StreamTrigger) == 0x110 ? 1 : -1];

#endif
