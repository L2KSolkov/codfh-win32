/*
 * EndLevelTrigger (the class name it registers with the class factory at
 * 0x30B099, with its MakeNew, sub_CC090, and its size, 0xD0): a trigger of
 * kind 0x24 derived from Trigger that ends the level (sub_CC2F0) once it is
 * both armed and reached, anchored at its vtables off_3D6E84 and off_3D6E7C
 * (+0x18), which its constructor (sub_CC110) and destructor (sub_CC190)
 * install.
 */
#ifndef ENDLEVELTRIGGER_H
#define ENDLEVELTRIGGER_H

#include "rw/ostypes.h"
#include "types/type_3DF8D8.h"
#include "types/type_44350.h"

class EndLevelTrigger : public Trigger
{
public:
    RWS_MAKENEWCLASS(EndLevelTrigger);
    RWS_DECLARE_CLASSID(EndLevelTrigger);

    EndLevelTrigger(const RWS::CAttributePacket &attr);
    ~EndLevelTrigger();

    virtual void HandleAttributes(const RWS::CAttributePacket &attr);
    // Folded (/OPT:ICF) into CCESSPoolTrigger's (sub_A2BF0): it passes its
    // events to Trigger's.
    virtual void HandleEvents(RWS::CMsg &pMsg);
    // Its kind (0x24), folded (/OPT:ICF) into sub_194310.
    virtual RwInt32 vf_008();

    // Reached (unk_C6 set): ends the level if it is armed (arg_0 unused).
    void sub_CC250(RwInt32 arg_0);
    // Left (unk_C6 cleared; arg_0 unused).
    void sub_CC280(RwInt32 arg_0);
    // Arms it (arg_0 set), ending the level at once if it is reached.
    void sub_CC2A0(RwInt32 arg_0);
    // Ends the level: records the checkpoint named by dword_4B9144's object
    // (sub_EACA0).
    void sub_CC2F0();
    // The next level for unk_C0 in single player; 0 in multiplayer
    // (an empty switch on it).
    RwInt32 sub_CC330();

    RwInt32 unk_C0;             // command 0: a level number (only single
                                // player maps it to the next level)
    RwInt16 unk_C4;             // armed
    RwInt16 unk_C6;             // reached
    RwUInt8 unk_C8[0x8];
};
typedef RwChar EndLevelTrigger_size_check[sizeof(EndLevelTrigger) == 0xD0 ? 1 : -1];

// The key of the object naming the level's end checkpoint.
struct type_3DF8D8_04_data;
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &dword_4B9144;
#else
extern type_3DF8D8_04_data dword_4B9144;
#endif

#endif
