/*
 * DestructableObjectTrigger (the class name it registers with the class
 * factory at 0x30A6D9, with its MakeNew, sub_A3510, and its size, 0x100): a
 * trigger of kind 0x14 derived from Trigger, anchored at its vtables
 * off_3D5D20 and off_3D5D18 (+0x18), which its constructor (sub_A3590) and
 * destructor (sub_A36E0) install.
 */
#ifndef DESTRUCTABLEOBJECTTRIGGER_H
#define DESTRUCTABLEOBJECTTRIGGER_H

#include "rw/ostypes.h"
#include "types/type_3DF8D8.h"
#include "types/type_44350.h"

class DestructableObjectTrigger : public Trigger
{
public:
    RWS_MAKENEWCLASS(DestructableObjectTrigger);
    RWS_DECLARE_CLASSID(DestructableObjectTrigger);

    DestructableObjectTrigger(const RWS::CAttributePacket &attr);
    // Out of line: MeshSwapDestructableObjectTrigger's destructor calls it.
    ~DestructableObjectTrigger();

    virtual void HandleAttributes(const RWS::CAttributePacket &attr);
    // Folded (/OPT:ICF) into CCESSPoolTrigger's (sub_A2BF0): it passes its
    // events to Trigger's.
    virtual void HandleEvents(RWS::CMsg &pMsg);
    // Its kind (0x14; folded into another's, sub_1A32A0) and its key
    // (&unk_D0; folded into SoldierTrigger's, sub_A17D0).
    virtual RwInt32 vf_008();
    virtual type_3DF8D8_04 *vf_01C();

    type_3DF8D8_04 unk_C0;      // command 1, a name of the kind 0xA
    type_3DF8D8_04 unk_C8;      // command 2 when set, of the kind 0xC
    type_3DF8D8_04 unk_D0;      // command 0, of the kind 0x2E when set
    RwInt16 unk_D8;             // command 5: the word at +0x14 of its block
    RwUInt8 unk_DA[0x2];
    RwInt32 unk_DC;             // command 4's name's value
    RwInt32 unk_E0;             // command 3: its health (an int, but its
                                // entity reads the bits as a float and
                                // truncates it, unit_09B700)
    RwInt32 unk_E4;             // commands 6 to 10
    RwInt32 unk_E8;
    RwInt32 unk_EC;
    RwInt32 unk_F0;
    RwInt32 unk_F4;
    RwUInt8 unk_F8[0x8];
};
typedef RwChar DestructableObjectTrigger_size_check[sizeof(DestructableObjectTrigger) == 0x100 ? 1 : -1];

#endif
