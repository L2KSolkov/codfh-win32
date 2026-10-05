/*
 * PASTrigger (the class name it registers with the class factory at
 * 0x30B0F9, with its MakeNew, sub_CC650, and its size, 0xD0): a trigger of
 * kind 0x27 derived from Trigger, anchored at its vtables off_3D6F14 and
 * off_3D6F0C (+0x18), which its constructor (sub_CC6D0) and destructor
 * (sub_CC750) install.
 */
#ifndef PASTRIGGER_H
#define PASTRIGGER_H

#include "rw/ostypes.h"
#include "types/type_44350.h"

class PASTrigger : public Trigger
{
public:
    RWS_MAKENEWCLASS(PASTrigger);
    RWS_DECLARE_CLASSID(PASTrigger);

    PASTrigger(const RWS::CAttributePacket &attr);
    ~PASTrigger();

    virtual void HandleAttributes(const RWS::CAttributePacket &attr);
    // Folded (/OPT:ICF) into CCESSPoolTrigger's (sub_A2BF0): it passes its
    // events to Trigger's.
    virtual void HandleEvents(RWS::CMsg &pMsg);
    // Its kind (0x27).
    // Inline: the constructor's vtable emits them after it, before ??_G (the image's order).
    virtual RwInt32 vf_008()
    {
        return 0x27;
    }

    // Entered and left (unk_C0; arg_0 unused).
    void sub_CC850(RwInt32 arg_0);
    void sub_CC870(RwInt32 arg_0);

    RwInt16 unk_C0;             // set while occupied
    RwUInt8 unk_C2[0x2];
    RwInt32 unk_C4;             // command 0: 0 to 2
    RwUInt8 unk_C8[0x8];
};
typedef RwChar PASTrigger_size_check[sizeof(PASTrigger) == 0xD0 ? 1 : -1];

#endif
