/*
 * PlaySoundTrigger (the class name it registers with the class factory at
 * 0x30AEE9, with its MakeNew, sub_C6A80, and its size, 0x120): a trigger of
 * kind 0xD derived from Trigger that plays a sound, at itself or from the
 * first player, anchored at its vtables off_3D6C3C and off_3D6C34 (+0x18),
 * which its constructor (sub_C6B00) and destructor (sub_C6B70) install.
 */
#ifndef PLAYSOUNDTRIGGER_H
#define PLAYSOUNDTRIGGER_H

#include "rw/ostypes.h"
#include "types/type_3DF8D8.h"
#include "types/type_44350.h"

class PlaySoundTrigger : public Trigger
{
public:
    RWS_MAKENEWCLASS(PlaySoundTrigger);
    RWS_DECLARE_CLASSID(PlaySoundTrigger);

    PlaySoundTrigger(const RWS::CAttributePacket &attr);
    ~PlaySoundTrigger();

    virtual void HandleAttributes(const RWS::CAttributePacket &attr);
    // Folded (/OPT:ICF) into StreamTrigger's (sub_BB1B0), which it is
    // identical to: on dword_4B67B8 it may play again (unk_24_6).
    virtual void HandleEvents(RWS::CMsg &pMsg);
    // Its kind (0xD), folded (/OPT:ICF) into sub_1B3C10.
    virtual RwInt32 vf_008();

    // Plays its sound (once, unless unk_10C is 0): from the first player
    // with unk_110 set, else at the trigger's position.
    // A new virtual (slot 12, 0x30: the image's vtable ends with it; IDA's sub_C6CF0).
    virtual void vf_030();

    RwInt32 unk_C0;             // command 0
    type_3DF8D8_04 unk_C4;      // command 2: the sound's key
    RwUInt8 unk_CC[0x40];
    RwInt32 unk_10C;            // command 1: set to play it only once
    RwInt32 unk_110;            // command 3: set to play it from the player
    RwInt32 unk_114;            // command 4: set to let it take over a
                                // busy voice when none is free (sub_8A980)
    RwUInt8 unk_118[0x8];
};
typedef RwChar PlaySoundTrigger_size_check[sizeof(PlaySoundTrigger) == 0x120 ? 1 : -1];

#endif
