/*
 * GimpTrigger (the class name it registers with the class factory at
 * 0x30AF19, with its MakeNew, sub_C6DF0, and its size, 0x160): a spawner of
 * kind 0x1F derived from Trigger, like SoldierTrigger, anchored at its
 * vtables off_3D6C88 and off_3D6C80 (+0x18), which its constructor
 * (sub_C6E70) and destructor (sub_C71F0) install.
 */
#ifndef GIMPTRIGGER_H
#define GIMPTRIGGER_H

#include "rw/ostypes.h"
#include "types/alfasched.h"
#include "types/type_3DF8D8.h"
#include "types/type_44350.h"
#include "types/type_D48D0.h"
#include "types/type_4B83A0.h"

class GimpTrigger : public Trigger
{
public:
    RWS_MAKENEWCLASS(GimpTrigger);
    RWS_DECLARE_CLASSID(GimpTrigger);

    GimpTrigger(const RWS::CAttributePacket &attr);
    ~GimpTrigger();

    virtual void HandleAttributes(const RWS::CAttributePacket &attr);
    // On iMsgStartSystem it finds its weapon's settings (by unk_E8) and
    // registers their names; on dword_4B67C0 it restores the number it may
    // spawn.
    virtual void HandleEvents(RWS::CMsg &pMsg);
    // Its kind (0x1F), folded (/OPT:ICF) into sub_1948F0.
    virtual RwInt32 vf_008();
    // How many it may spawn (unk_14C).
    // Inline: the constructor's vtable emits them after it, before ??_G (the image's order).
    virtual RwInt32 vf_00C()
    {
        return unk_14C;
    }
    virtual RwInt32 vf_014()
    {
        return unk_140;
    }
    // Adds arg_4 to (arg_0 set) or sets (arg_0 0) the number it may spawn,
    // unk_14C (0x7FFFFFFF: no limit).
    virtual void vf_010(RwInt32 arg_0, RwInt32 arg_4);
    // unk_140.
    // Its CCESS tracker's kind, by its definition's weapon class: 1, 2 or 4.
    virtual RwInt32 vf_018();
    // &unk_D8, folded (/OPT:ICF) into SimpleMechanicTrigger's (sub_B7530).
    virtual type_3DF8D8_04 *vf_01C();
    // Its gimp (sub_176E50), when its definition is known and pool 4 of
    // dword_4B83A0 and the first animation pool have room, or its
    // unk_24_18 is set.
    virtual type_3D3548 *vf_020();
    // 2, folded (/OPT:ICF) into sub_195D00.
    virtual RwInt32 vf_024();

    type_3DF8D8_04 unk_C0;      // command 2: its definition's name (kind 4)
    type_3DF8D8_04 unk_C8;      // command 6, of the kind 0xA
    type_3DF8D8_04 unk_D0;      // command 7 when set, of the kind 0xC
    type_3DF8D8_04 unk_D8;      // command 0, of the kind 0x2E
    type_3DF8D8_04 unk_E0;      // command 15, when set
    type_3DF8D8_04 unk_E8;      // command 9: its weapon's settings' name
    type_3DF8D8_04 unk_F0;      // command 22
    RwInt32 unk_F8;             // unk_E8's settings' index
    RwInt32 unk_FC;             // command 12
    RwUInt8 unk_100[0x6];       // cleared, the last two set; command 13's
                                // value at +2
    RwInt16 unk_106[0x5];       // -1
    RwInt32 unk_110;            // first command 3
    RwInt32 unk_114;            // first command 4
    RwInt32 unk_118;            // command 5
    RwInt32 unk_11C;            // command 14
    union
    {
        RwInt32 unk_120;        // command 8 (stored as its raw bits)
        RwReal unk_120_r;       // as the gimp's set-up reads it: its health
    };
    RwInt32 unk_124;            // commands 18 to 21 (1 each)
    RwInt32 unk_128;
    RwInt32 unk_12C;
    RwInt32 unk_130;
    RwUInt8 unk_134[0x4];
    RwInt32 unk_138;            // command 16
    RwInt32 unk_13C;            // command 27
    RwInt32 unk_140;            // command 10
    RwInt32 unk_144;            // command 17
    RwInt32 unk_148;            // command 11 (0x7FFFFFFF for none), kept
    RwInt32 unk_14C;            // and as it is spent (restored on
                                // dword_4B67C0)
    type_D48D0 unk_150;
    RwUInt8 unk_154[0xC];
};
typedef RwChar GimpTrigger_size_check[sizeof(GimpTrigger) == 0x160 ? 1 : -1];

// Spawns the gimp of the trigger arg_0.
type_3D3548 *sub_176E50(GimpTrigger *arg_0);

#endif
