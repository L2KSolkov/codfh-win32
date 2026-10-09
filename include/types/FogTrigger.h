/*
 * FogTrigger (the class name it registers with the class factory at
 * 0x30B0C9, with its MakeNew, sub_CC370, and its size, 0xE0): a trigger of
 * kind 0x26 derived from Trigger that sets the fog and clip distances,
 * anchored at its vtables off_3D6ECC and off_3D6EC4 (+0x18), which its
 * constructor (sub_CC3F0) and destructor (sub_CC490) install.
 */
#ifndef FOGTRIGGER_H
#define FOGTRIGGER_H

#include "rw/ostypes.h"
#include "types/type_44350.h"

class FogTrigger : public Trigger
{
public:
    RWS_MAKENEWCLASS(FogTrigger);
    RWS_DECLARE_CLASSID(FogTrigger);

    FogTrigger(const RWS::CAttributePacket &attr);
    ~FogTrigger();

    virtual void HandleAttributes(const RWS::CAttributePacket &attr);
    // Folded (/OPT:ICF) into CCESSPoolTrigger's (sub_A2BF0): it passes its
    // events to Trigger's.
    virtual void HandleEvents(RWS::CMsg &pMsg);
    // Its kind (0x26).
    // Inline: the constructor's vtable emits them after it, before ??_G (the image's order).
    virtual RwInt32 vf_008()
    {
#ifdef CODFH_SP // single player numbers it 0x25 (its vtable 0x2E32E8 +8: SP 0x124460)
        return 0x25;
#else
        return 0x26;
#endif
    }

    // Sets the fog (sub_128C80) and clip (sub_128CD0) distances, their
    // changes over their times in seconds (arg_0 unused).
    void sub_CC5D0(RwInt32 arg_0);

    RwInt16 unk_C0;             // set once it has
    RwUInt8 unk_C2[0x2];
    RwReal unk_C4;              // command 0: the fog distance (20000)
    RwReal unk_C8;              // command 1: its time
    RwReal unk_CC;              // command 2: the clip distance (20000)
    RwReal unk_D0;              // command 3: its time
    RwUInt8 unk_D4[0xC];
};
typedef RwChar FogTrigger_size_check[sizeof(FogTrigger) == 0xE0 ? 1 : -1];

#endif
