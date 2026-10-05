/*
 * AnimatedBGTrigger (the class name it registers with the class factory at
 * 0x30A4F9, with its MakeNew, sub_9F130, and its size, 0x190): a trigger of
 * kind 8, derived from Trigger, anchored at its vtables off_3D5948 and
 * off_3D5940 (+0x18), which its constructor (sub_9F1B0) and destructor
 * (sub_9F570) install. The animated background entity (type_3D32F8) reads
 * it as a type_712B0; its slot 0x0C is Trigger's own (sub_9DFF0).
 */
#ifndef ANIMATEDBGTRIGGER_H
#define ANIMATEDBGTRIGGER_H

#include "rw/ostypes.h"
#include "types/type_44350.h"

class AnimatedBGTrigger : public Trigger
{
public:
    RWS_MAKENEWCLASS(AnimatedBGTrigger);
    RWS_DECLARE_CLASSID(AnimatedBGTrigger);

    AnimatedBGTrigger(const RWS::CAttributePacket &attr);
    ~AnimatedBGTrigger();
    virtual void HandleAttributes(const RWS::CAttributePacket &attr);
    // Overrides (out of line in unit_09AD40): its kind (8) and its key
    // (&unk_E0).
    // Inline: the constructor's vtable emits them after it, before ??_G (the image's order).
    virtual RwInt32 vf_008()
    {
        return 8;
    }
    virtual type_3DF8D8_04 * vf_01C()
    {
        return &unk_E0;
    }
    virtual RwUInt32 vf_030()
    {
        return unk_14C & 1;
    }
    virtual RwUInt32 vf_034()
    {
        return unk_14C & 2;
    }
    virtual RwUInt32 vf_038()
    {
        return unk_14C & 4;
    }
    virtual RwInt32 vf_018();
    // Spawns its animated background entity (sub_73710) when its model's
    // key resolves.
    virtual type_3D3548 *vf_020();
    // New virtuals: bits 0, 1 and 2 of unk_14C.

    // Its keys (the entity's model, AI script and tasks and the like; see
    // type_712B0).
    type_3DF8D8_04 unk_C0;
    type_3DF8D8_04 unk_C8;
    type_3DF8D8_04 unk_D0;
    type_3DF8D8_04 unk_D8;
    type_3DF8D8_04 unk_E0;
    type_3DF8D8_04 unk_E8;
    type_3DF8D8_04 unk_F0;
    RwInt32 unk_F8;
    RwInt32 unk_FC;
    RwInt32 unk_100;
    RwUInt8 unk_104[0x6];       // its scene (the last two set)
    RwInt16 unk_10A[0x5];       // -1 at first
    RwInt32 unk_114;
    RwInt32 unk_118;
    RwInt32 unk_11C;            // its CCESS side (vf_018)
    RwInt32 unk_120;
    RwInt32 unk_124;
    RwInt32 unk_128;            // whether allies, enemies, bullets and
    RwInt32 unk_12C;            // explosions may damage its entity
    RwInt32 unk_130;
    RwInt32 unk_134;
    RwInt32 unk_138;
    RwInt32 unk_13C;
    RwInt32 unk_140;
    RwInt32 unk_144;
    RwInt32 unk_148;
    RwUInt32 unk_14C;           // its flags (vf_030 to vf_038)
    type_3DF8D8_04 unk_150;
    RwInt32 unk_158;
    RwInt32 unk_15C;
    RwInt32 unk_160;
    RwReal unk_164;             // halved unless -1 (commands 35 and 36)
    RwReal unk_168;
    RwInt32 unk_16C;
    RwInt32 unk_170;
    RwInt32 unk_174;
    RwUInt8 *unk_178;           // a block (freed with sub_BD350)
    RwInt32 unk_17C;
    type_D48D0 unk_180;         // its entity (a handle)
    RwUInt8 unk_184[0xC];
    // HandleEvents, as the image's vtable has it (a trivial body, folded into
    // sub_A2BF0 with every other copy).
    virtual void HandleEvents(RWS::CMsg &pMsg)
    {
        Trigger::HandleEvents(pMsg);
    }
    // vf_024, as the image's vtable has it (a trivial body, folded into
    // sub_C5540 with every other copy).
    virtual RwInt32 vf_024()
    {
        return 3;
    }
};
typedef RwChar AnimatedBGTrigger_size_check[sizeof(AnimatedBGTrigger) == 0x190 ? 1 : -1];

#endif
