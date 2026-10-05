/*
 * SoundBankTrigger (the class name it registers with the class factory at
 * 0x30AB29, with its MakeNew, sub_B99C0, and its size, 0x1C0): a trigger of
 * kind 0xA derived from Trigger that swaps the loaded sound banks (as
 * CSoundBankSelector picks them for a level), anchored at its vtables
 * off_3D65F4 and off_3D65EC (+0x18), which its constructor (sub_B9A40) and
 * destructor (sub_B9B20) install.
 */
#ifndef SOUNDBANKTRIGGER_H
#define SOUNDBANKTRIGGER_H

#include "rw/ostypes.h"
#include "types/soundbank.h"
#include "types/type_44350.h"

class SoundBankTrigger : public Trigger
{
public:
    RWS_MAKENEWCLASS(SoundBankTrigger);
    RWS_DECLARE_CLASSID(SoundBankTrigger);

    SoundBankTrigger(const RWS::CAttributePacket &attr);
    ~SoundBankTrigger()
    {
    }

    virtual void HandleAttributes(const RWS::CAttributePacket &attr);
    // Folded (/OPT:ICF) into CCESSPoolTrigger's (sub_A2BF0): it passes its
    // events to Trigger's.
    virtual void HandleEvents(RWS::CMsg &pMsg);
    // Its kind (0xA; folded into another's, sub_36780).
    virtual RwInt32 vf_008();

    // Queues its banks: its second set replaces dword_4B1B60's requests
    // (when it has one) and the queue restarts; its first set loads.
    void sub_B9D80();

    type_825E0 unk_C0[6];       // the first set (command 0)
    type_825E0 unk_120[0xA];    // the second set (slot 0x63 in the list)
};
typedef RwChar SoundBankTrigger_size_check[sizeof(SoundBankTrigger) == 0x1C0 ? 1 : -1];

#endif
