/*
 * GimpVehicleTrigger (the class name it registers with the class factory
 * at 0x30B069, with its MakeNew, sub_CB9D0, and its size, 0x100): a spawner
 * of kind 0x23 derived from Trigger that makes a gimp vehicle (a
 * type_3DE0E0), anchored at its vtables off_3D6E38 and off_3D6E30 (+0x18),
 * which its constructor (sub_CBA50) and destructor (sub_CBC20) install.
 */
#ifndef GIMPVEHICLETRIGGER_H
#define GIMPVEHICLETRIGGER_H

#include "rw/ostypes.h"
#include "types/type_3DF8D8.h"
#include "types/type_44350.h"

class GimpVehicleTrigger : public Trigger
{
public:
    RWS_MAKENEWCLASS(GimpVehicleTrigger);
    RWS_DECLARE_CLASSID(GimpVehicleTrigger);

    GimpVehicleTrigger(const RWS::CAttributePacket &attr);
    ~GimpVehicleTrigger();

    virtual void HandleAttributes(const RWS::CAttributePacket &attr);
    // Folded (/OPT:ICF) into CCESSPoolTrigger's (sub_A2BF0): it passes its
    // events to Trigger's.
    virtual void HandleEvents(RWS::CMsg &pMsg);
    // Its kind (0x23), folded (/OPT:ICF) into sub_194290.
    virtual RwInt32 vf_008();
    // Its vehicle, of the type unk_E0 (sub_17E680 or sub_180CF0), once its
    // definition's (unk_C0) object is known.
    virtual type_3D3548 *vf_020();

    type_3DF8D8_04 unk_C0;      // command 2: its definition's name (kind
                                // 0x27)
    type_3DF8D8_04 unk_C8;      // command 8, of the kind 0xA
    type_3DF8D8_04 unk_D0;      // command 9, of the kind 0xC
    type_3DF8D8_04 unk_D8;      // command 0, of the kind 0x2E
    RwInt32 unk_E0;             // command 5: its type (-1)
    RwInt32 unk_E4;             // command 10 (200)
    RwInt32 unk_E8;             // command 11 (500)
    RwInt32 unk_EC;             // command 6
    RwInt32 unk_F0;             // command 7
    RwInt32 unk_F4;             // first command 3
    RwInt32 unk_F8;             // first command 4
    RwUInt8 unk_FC[0x4];
};
typedef RwChar GimpVehicleTrigger_size_check[sizeof(GimpVehicleTrigger) == 0x100 ? 1 : -1];

// Make the gimp vehicle of the trigger arg_0: a type_3DE0E0 (type 0) or
// its subclass off_3DE350 (type 1).
type_3D3548 *sub_17E680(GimpVehicleTrigger *arg_0);
type_3D3548 *sub_180CF0(GimpVehicleTrigger *arg_0);

#endif
