/*
 * LevelScriptTrigger (the class name it registers with the class factory at
 * 0x30AEB9, with its MakeNew, sub_C66C0, and its size, 0xD0): a trigger of
 * kind 0x1E derived from Trigger that holds the level's script (the one
 * sub_16FFB0 registers), anchored at its vtables off_3D6BF0 and off_3D6BE8
 * (+0x18), which its constructor (sub_C6740) and destructor (sub_C6820)
 * install.
 */
#ifndef LEVELSCRIPTTRIGGER_H
#define LEVELSCRIPTTRIGGER_H

#include "rw/ostypes.h"
#include "types/type_44350.h"

class LevelScriptTrigger : public Trigger
{
public:
    RWS_MAKENEWCLASS(LevelScriptTrigger);
    RWS_DECLARE_CLASSID(LevelScriptTrigger);

    LevelScriptTrigger(const RWS::CAttributePacket &attr);
    ~LevelScriptTrigger();

    virtual void HandleAttributes(const RWS::CAttributePacket &attr);
    // Trigger's, then on dword_4B8750 it stops listening for it.
    virtual void HandleEvents(RWS::CMsg &pMsg);
    // Its kind (0x1E), folded (/OPT:ICF) into sub_1945A0.
    virtual RwInt32 vf_008();

    RwUInt8 *unk_C0;            // command 0: its script's block
                                // (Trigger::sub_BD490)
    RwUInt8 unk_C4[0xC];
};
typedef RwChar LevelScriptTrigger_size_check[sizeof(LevelScriptTrigger) == 0xD0 ? 1 : -1];

// Registers the level's script trigger arg_0 (warning when one is already).
void sub_16FFB0(Trigger *arg_0);

#endif
