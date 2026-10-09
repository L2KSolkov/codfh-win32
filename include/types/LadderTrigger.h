/*
 * LadderTrigger (the class name it registers with the class factory at
 * 0x30AFD9, with its MakeNew, sub_CAA90, and its size, 0xE0): a trigger of
 * kind 0x20 derived from Trigger that puts a player on a ladder, anchored
 * at its vtables off_3D6D48 and off_3D6D40 (+0x18), which its constructor
 * (sub_CAB10) and destructor (sub_CABE0) install.
 */
#ifndef LADDERTRIGGER_H
#define LADDERTRIGGER_H

#include "rw/ostypes.h"
#include "types/type_3DF8D8.h"
#include "types/type_44350.h"

class LadderTrigger : public Trigger
{
public:
    RWS_MAKENEWCLASS(LadderTrigger);
    RWS_DECLARE_CLASSID(LadderTrigger);

    LadderTrigger(const RWS::CAttributePacket &attr);
    ~LadderTrigger();

    // Trigger's only.
    virtual void HandleAttributes(const RWS::CAttributePacket &attr);
    // Folded (/OPT:ICF) into CCESSPoolTrigger's (sub_A2BF0): it passes its
    // events to Trigger's.
    virtual void HandleEvents(RWS::CMsg &pMsg);
    // Its kind (0x20), folded (/OPT:ICF) into type_3D2E20's vf_010
    // (sub_6FCA0).
    virtual RwInt32 vf_008();
    // &unk_C0.
    // Inline: the constructor's vtable emits them after it, before ??_G (the image's order).
    virtual type_3DF8D8_04 * vf_01C()
    {
        return &unk_C0;
    }
    // Whether the matrix arg_0 is on it: nearer its top than its bottom, or
    // Trigger's test of it, then (failing that) the same turned half round
    // about the y axis, which sets unk_D4 (sub_CAC70).
    virtual RwInt32 vf_028(struct RwMatrixTag *arg_0);

    // Puts the player arg_0 on it (type_10F710::sub_114920) while unk_D0 is
    // set.
    void sub_CAC30(type_3D3548 *arg_0);
#ifdef CODFH_SP
    // What it does when the entity arg_0 leaves it: nothing (single player's
    // sub_145640 calls it at SP 0xF073C; folded, /OPT:ICF, into the empty SP
    // 0xD60D0).
    void sp_leave(type_3D3548 *arg_0);
#endif

    type_3DF8D8_04 unk_C0;
    RwInt32 unk_C8;
    RwInt32 unk_CC;
    RwInt32 unk_D0;             // set to be used (1)
    RwInt32 unk_D4;             // set when the player faces away from it
    RwInt32 unk_D8;
    RwUInt8 unk_DC[0x4];
};
// The y axis LadderTrigger's vf_028 turns the matrix about (.rdata).
extern const RwV3d stru_3D6D34;

typedef RwChar LadderTrigger_size_check[sizeof(LadderTrigger) == 0xE0 ? 1 : -1];

#endif
