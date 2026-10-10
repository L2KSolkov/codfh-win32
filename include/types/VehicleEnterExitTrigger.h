/*
 * VehicleEnterExitTrigger (the class name it registers with the class
 * factory at 0x30AC49, with its MakeNew, sub_BEAB0, and its size, 0xF0): a
 * trigger derived from Trigger that runs a script's messages when the player
 * gets into or out of a vehicle ("VehicleEnterExitGroup"), anchored at its
 * vtables off_3D68E0 and off_3D68D8 (+0x18), which its constructor
 * (sub_BEB30) and destructor (sub_BECB0) install.
 */
#ifndef VEHICLEENTEREXITTRIGGER_H
#define VEHICLEENTEREXITTRIGGER_H

#include "rw/ostypes.h"
#include "types/alfamessman.h"
#include "types/type_3DF8D8.h"
#include "types/type_44350.h"

struct type_3D3548;

class VehicleEnterExitTrigger : public Trigger
{
public:
    RWS_MAKENEWCLASS(VehicleEnterExitTrigger);
    RWS_DECLARE_CLASSID(VehicleEnterExitTrigger);

    VehicleEnterExitTrigger(const RWS::CAttributePacket &attr);
    ~VehicleEnterExitTrigger();

    virtual void HandleAttributes(const RWS::CAttributePacket &attr);
    // On dword_4B67B8 it ends its registrations; on dword_4B67C0 it makes
    // them again.
    virtual void HandleEvents(RWS::CMsg &pMsg);
    // Its kind (folded, /OPT:ICF, into another's, sub_215B70).
    virtual RwInt32 vf_008();

    // Attaches the player of arg_0 (the vehicle, unk_DC, when it is in one;
    // unk_CC otherwise) to the task of the named object; returns 1.
    RwInt32 sub_BF310(type_3D3548 *arg_0);
    // Whether the object arg_0's player may use it (the vehicle's task is
    // known and done, or the other).
    RwInt32 sub_BF470(type_3D3548 *arg_0);
    // Runs sub_BF310 for a player (flag unk_2C_4) when unk_E8 allows.
    void sub_BF590(type_3D3548 *arg_0);
#ifdef CODFH_SP
    // What it does when the entity arg_0 leaves it: nothing. Single player's
    // sub_145640 calls it and LadderTrigger's as two calls (SP 0xF0731,
    // 0xF073C), both folded (/OPT:ICF) into the empty SP 0xD60D0.
    void sp_leave(type_3D3548 *arg_0);
#endif

    type_6B960 *unk_C0;         // its registrations for the messages
    type_6B960 *unk_C4;         // unk_C8 and unk_D8
    RwInt16 unk_C8;             // command 0's message
    RwUInt8 unk_CA[0x2];
    type_3DF8D8_04 unk_CC;      // command 1: the task (kind 0xC) added to
                                // the player to get in
    RwInt32 unk_D4;             // set once unk_C8 is done
    RwInt16 unk_D8;             // command 2's message
    RwUInt8 unk_DA[0x2];
    type_3DF8D8_04 unk_DC;      // command 3: the task (kind 0xC) added to
                                // the player to get out while in a vehicle
    RwInt32 unk_E4;             // set once unk_D8 is done
    RwInt32 unk_E8;             // command 4
    RwUInt8 unk_EC[0x4];
};
typedef RwChar VehicleEnterExitTrigger_size_check[sizeof(VehicleEnterExitTrigger) == 0xF0 ? 1 : -1];

// The callbacks sub_6BAE0 registers: its first or second message is done.
RwInt32 sub_BF510(VehicleEnterExitTrigger *arg_0);
RwInt32 sub_BF550(VehicleEnterExitTrigger *arg_0);

#endif
