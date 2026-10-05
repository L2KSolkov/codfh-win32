/*
 * LevelClumpBankParamTrigger (the class name it registers with the class
 * factory at 0x30AE59, with its MakeNew, sub_C60E0, and its size, 0xC0): a
 * trigger derived from Trigger that sets the clump banks' memory and the
 * default clump bank, and loads the banks on its events, anchored at its
 * vtables off_3D6B50 and off_3D6B48 (+0x18), which its constructor
 * (sub_C6160) and destructor (sub_C6210) install.
 */
#ifndef LEVELCLUMPBANKPARAMTRIGGER_H
#define LEVELCLUMPBANKPARAMTRIGGER_H

#include "rw/ostypes.h"
#include "types/type_44350.h"

class LevelClumpBankParamTrigger : public Trigger
{
public:
    RWS_MAKENEWCLASS(LevelClumpBankParamTrigger);
    RWS_DECLARE_CLASSID(LevelClumpBankParamTrigger);

    LevelClumpBankParamTrigger(const RWS::CAttributePacket &attr);
    ~LevelClumpBankParamTrigger();

    virtual void HandleAttributes(const RWS::CAttributePacket &attr);
    // On Id (once) and dword_4B67C0: loads the default clump bank (while
    // dword_4E5CC4 is set) and the level's three (dword_4E54E8).
    virtual void HandleEvents(RWS::CMsg &pMsg);
    // vf_008, as the image's vtable has it (a trivial body, folded into
    // sub_1936A0 with every other copy).
    virtual RwInt32 vf_008()
    {
        return 0x1C;
    }
};
typedef RwChar LevelClumpBankParamTrigger_size_check[sizeof(LevelClumpBankParamTrigger) == 0xC0 ? 1 : -1];

// The clump banks' memory, in bytes (command 1, in kilobytes, 32-aligned).
#ifdef CODFH_PLAIN
extern RwUInt32 &dword_4E51C0;
#else
extern RwUInt32 dword_4E51C0;
#endif
// The level's three clump banks.
extern RwInt32 dword_4E54E8[3];

// Loads the clump bank arg_0 (none for -1).
void sub_16EAB0(RwInt32 arg_0);
// Sets the level's clump bank arg_0 (0 to 2) to arg_4 (none for -1).
void sub_16F3E0(RwInt32 arg_0, RwInt32 arg_4);
// Sets the memory for the clump banks' clumps to arg_0 bytes (command 2, in
// kilobytes).
void sub_16FF00(RwUInt32 arg_0);

#endif
