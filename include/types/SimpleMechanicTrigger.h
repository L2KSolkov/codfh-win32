/*
 * SimpleMechanicTrigger (the class name it registers with the class factory
 * at 0x30AA99, with its MakeNew, sub_B7330, and its size, 0x110): a trigger
 * of kind 0x11 derived from Trigger that spawns a simple mechanism (a
 * type_3DAC58, sub_133230), anchored at its vtables off_3D64C4 and
 * off_3D64BC (+0x18), which its constructor (sub_B73B0) and destructor
 * (sub_B7570) install.
 */
#ifndef SIMPLEMECHANICTRIGGER_H
#define SIMPLEMECHANICTRIGGER_H

#include "rw/ostypes.h"
#include "types/type_3DF8D8.h"
#include "types/type_44350.h"

struct type_3DAC58;

class SimpleMechanicTrigger : public Trigger
{
public:
    RWS_MAKENEWCLASS(SimpleMechanicTrigger);
    RWS_DECLARE_CLASSID(SimpleMechanicTrigger);

    SimpleMechanicTrigger(const RWS::CAttributePacket &attr);
    ~SimpleMechanicTrigger()
    {
    }

    virtual void HandleAttributes(const RWS::CAttributePacket &attr);
    // Folded (/OPT:ICF) into CCESSPoolTrigger's (sub_A2BF0): it passes its
    // events to Trigger's.
    virtual void HandleEvents(RWS::CMsg &pMsg);
    // Its kind (0x11), its key (&unk_D8) and its child (a type_3DAC58,
    // sub_133230), when its model's name is known.
    // Inline: the constructor's vtable emits them after it, before ??_G (the image's order).
    virtual RwInt32 vf_008()
    {
        return 0x11;
    }
    virtual type_3DF8D8_04 * vf_01C()
    {
        return &unk_D8;
    }
    virtual type_3D3548 *vf_020();

    type_3DF8D8_04 unk_C0;      // command 2: its model's name, of the kind 3
                                // (0x30 with unk_E0 set)
    type_3DF8D8_04 unk_C8;      // command 5, of the kind 0xA when set
    type_3DF8D8_04 unk_D0;      // command 6 when set, of the kind 0xC
    type_3DF8D8_04 unk_D8;      // command 0, of the kind 0x2E when set
    RwInt32 unk_E0;             // commands 3 and 4
    RwInt32 unk_E4;
    type_3DF8D8_04 unk_E8;      // command 8, when set
    RwInt32 unk_F0;             // commands 9 and 7 (command 9's int is read
                                // as float bits: its spline speed, unk_3BC
                                // in unit_1331E0)
    RwInt32 unk_F4;
    RwInt32 unk_F8;             // command 10's name's value
    RwInt32 unk_FC;             // commands 11 to 14 (1 by default)
    RwInt32 unk_100;
    RwInt32 unk_104;
    RwInt32 unk_108;
    RwUInt8 unk_10C[0x4];
};
typedef RwChar SimpleMechanicTrigger_size_check[sizeof(SimpleMechanicTrigger) == 0x110 ? 1 : -1];

// Builds the mechanism for the trigger arg_0.
type_3DAC58 *sub_133230(type_712B0 *arg_0);

#endif
