/*
 * ConfinedAreaTrigger (the class name it registers with the class factory at
 * 0x30A679, with its MakeNew, sub_A2C20, and its size, 0xD0): a trigger of
 * kind 9 derived from Trigger, anchored at its vtables off_3D5C84 and
 * off_3D5C7C (+0x18), which its constructor (sub_A2CA0) and destructor
 * (sub_A2D00) install.
 */
#ifndef CONFINEDAREATRIGGER_H
#define CONFINEDAREATRIGGER_H

#include "rw/ostypes.h"
#include "types/type_44350.h"

class ConfinedAreaTrigger : public Trigger
{
public:
    RWS_MAKENEWCLASS(ConfinedAreaTrigger);
    RWS_DECLARE_CLASSID(ConfinedAreaTrigger);

    ConfinedAreaTrigger(const RWS::CAttributePacket &attr);
    ~ConfinedAreaTrigger()
    {
    }

    virtual void HandleAttributes(const RWS::CAttributePacket &attr);
    // Folded (/OPT:ICF) into CCESSPoolTrigger's (sub_A2BF0): it passes its
    // events to Trigger's.
    virtual void HandleEvents(RWS::CMsg &pMsg);
    // Its kind (9).
    // Inline: the constructor's vtable emits them after it, before ??_G (the image's order).
    virtual RwInt32 vf_008()
    {
        return 9;
    }

    RwInt32 unk_C0;             // its command 0, plus one

    // An inline accessor for unk_C0, with no address and so no database
    // name; named for its field. Evidence: entering the trigger
    // (sub_145060) copies it through a local of its own into the player.
    RwInt32 get_unk_C0()
    {
        RwInt32 r = unk_C0;
        return r;
    }
    RwUInt8 unk_C4[0xC];
};
typedef RwChar ConfinedAreaTrigger_size_check[sizeof(ConfinedAreaTrigger) == 0xD0 ? 1 : -1];

#endif
