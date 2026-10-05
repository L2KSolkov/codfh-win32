/*
 * AnimPackTrigger (the class name it registers with the class factory at
 * 0x30A589, with its MakeNew, sub_A11E0, and its size, 0x1C0): a trigger of
 * kind 0x10, derived from Trigger, anchored at its vtables off_3D5AA0 and
 * off_3D5A98 (+0x18), which its constructor (sub_A1260) and destructor
 * (sub_A13C0) install. Like CAnimPackSelector it holds six animation packs
 * and a key.
 */
#ifndef ANIMPACKTRIGGER_H
#define ANIMPACKTRIGGER_H

#include "rw/ostypes.h"
#include "types/type_44350.h"
#include "types/CAnimPackSelector.h"

class AnimPackTrigger : public Trigger
{
public:
    RWS_MAKENEWCLASS(AnimPackTrigger);
    RWS_DECLARE_CLASSID(AnimPackTrigger);

    AnimPackTrigger(const RWS::CAttributePacket &attr);
    ~AnimPackTrigger()
    {
    }

    virtual void HandleAttributes(const RWS::CAttributePacket &attr);
    // Its kind (0x10).
    // Inline: the constructor's vtable emits them after it, before ??_G (the image's order).
    virtual RwInt32 vf_008()
    {
        return 0x10;
    }
    // A new virtual: loads its packs where it stands, and plays its music
    // (its key) unless the key is 0x756CB864, 0x185BB351.
    virtual void vf_030();

    // Clears its packs.
    void sub_A1360();

    type_3DF8D8_04 unk_C0;
    CAnimPackSelector_pack unk_C8[6];
    RwUInt8 unk_1B8[0x8];
    // HandleEvents, as the image's vtable has it (a trivial body, folded into
    // sub_A2BF0 with every other copy).
    virtual void HandleEvents(RWS::CMsg &pMsg)
    {
        Trigger::HandleEvents(pMsg);
    }
};
typedef RwChar AnimPackTrigger_size_check[sizeof(AnimPackTrigger) == 0x1C0 ? 1 : -1];

#endif
