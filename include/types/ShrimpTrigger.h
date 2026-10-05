/*
 * ShrimpTrigger (the class name it registers with the class factory at
 * 0x30B009, with its MakeNew, sub_CAE20, and its size, 0x110): a spawner of
 * kind 0x21 derived from Trigger, anchored at its vtables off_3D6D98 and
 * off_3D6D90 (+0x18), which its constructor (sub_CAEA0) and destructor
 * (sub_CB0E0) install.
 */
#ifndef SHRIMPTRIGGER_H
#define SHRIMPTRIGGER_H

#include "rw/ostypes.h"
#include "types/type_17CC40.h"
#include "types/type_3DF8D8.h"
#include "types/type_44350.h"
#include "types/type_D48D0.h"

class ShrimpTrigger : public Trigger
{
public:
    RWS_MAKENEWCLASS(ShrimpTrigger);
    RWS_DECLARE_CLASSID(ShrimpTrigger);

    ShrimpTrigger(const RWS::CAttributePacket &attr);
    ~ShrimpTrigger();

    virtual void HandleAttributes(const RWS::CAttributePacket &attr);
    // Folded (/OPT:ICF) into CCESSPoolTrigger's (sub_A2BF0): it passes its
    // events to Trigger's.
    virtual void HandleEvents(RWS::CMsg &pMsg);
    // Its kind (0x21), folded (/OPT:ICF) into sub_1940D0.
    virtual RwInt32 vf_008();
    // How many it may spawn (unk_E4).
    virtual RwInt32 vf_00C();
    // Adds arg_4 to (arg_0 set) or sets (arg_0 0) the number it may spawn,
    // unk_E4 (0x7FFFFFFF: no limit).
    virtual void vf_010(RwInt32 arg_0, RwInt32 arg_4);
    // 1, folded (/OPT:ICF) into sub_115460.
    virtual RwInt32 vf_018();
    // Its spawn (dword_4E723C, made by sub_17D330 when there is none), once
    // unk_EC is ready.
    virtual type_3D3548 *vf_020();

    type_3DF8D8_04 unk_C0;      // command 0: a name, of the kind 3 (0x30
                                // with unk_D4 set)
    type_3DF8D8_04 unk_C8;      // command 1, when set
    union
    {
        RwInt32 unk_D0;         // command 2 (stored as its raw bits)
        RwReal unk_D0_r;        // as the shrimps read it: their speed
    };
    RwInt32 unk_D4;
    RwInt32 unk_D8;
    RwReal unk_DC;              // command 4 (1)
    RwInt32 unk_E0;             // command 3 (0x7FFFFFFF for none), kept
    RwInt32 unk_E4;             // and as it is spent
    type_D48D0 unk_E8;
    type_17CC40 unk_EC;
    // vf_024, as the image's vtable has it (a trivial body, folded into
    // sub_9E000 with every other copy).
    virtual RwInt32 vf_024()
    {
        return 4;
    }
};
typedef RwChar ShrimpTrigger_size_check[sizeof(ShrimpTrigger) == 0x110 ? 1 : -1];

// The spawn ShrimpTrigger's vf_020 returns.
extern type_3D3548 *dword_4E723C;
// Makes the spawn of the trigger arg_0 (into dword_4E723C).
void sub_17D330(ShrimpTrigger *arg_0);

#endif
