/*
 * SectionTrigger (the class name it registers with the class factory at
 * 0x30A9D9, with its MakeNew, sub_B0180, and its size, 0xE0): a trigger of
 * kind 4 derived from Trigger, anchored at its vtables off_3D63E4 and
 * off_3D63DC (+0x18), which its constructor (sub_B0200) and destructor
 * (sub_B0290) install.
 */
#ifndef SECTIONTRIGGER_H
#define SECTIONTRIGGER_H

#include "rw/ostypes.h"
#include "types/type_44350.h"

class SectionTrigger : public Trigger
{
public:
    RWS_MAKENEWCLASS(SectionTrigger);
    RWS_DECLARE_CLASSID(SectionTrigger);

    SectionTrigger(const RWS::CAttributePacket &attr);
    ~SectionTrigger()
    {
    }

    virtual void HandleAttributes(const RWS::CAttributePacket &attr);
    // Folded (/OPT:ICF) into CCESSPoolTrigger's (sub_A2BF0): it passes its
    // events to Trigger's.
    virtual void HandleEvents(RWS::CMsg &pMsg);
    // Its kind (4; folded into Trigger's vf_018, sub_9E000).
    virtual RwInt32 vf_008();

    RwInt32 unk_C0;             // commands 0 to 4
    RwInt32 unk_C4;
    RwInt32 unk_C8;
    RwInt32 unk_CC;
    RwInt32 unk_D0;
    RwUInt8 unk_D4[0xC];
};
typedef RwChar SectionTrigger_size_check[sizeof(SectionTrigger) == 0xE0 ? 1 : -1];

#endif
