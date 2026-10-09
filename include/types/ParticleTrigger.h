/*
 * ParticleTrigger (the class name it registers with the class factory at
 * 0x30A829, with its MakeNew, sub_A6D80, and its size, 0x380): a trigger of
 * kind 0x12 derived from Trigger ("DestroyParticle" requires the kind) that
 * runs up to five particle emitters, anchored at its vtables off_3D5EC4 and
 * off_3D5EBC (+0x18), which its constructor (sub_A6E00) and destructor
 * (sub_A6F20) install. It listens to the messages dword_4B67B8 (which stops
 * its emitters) and dword_4B67C0.
 */
#ifndef PARTICLETRIGGER_H
#define PARTICLETRIGGER_H

#include "rw/ostypes.h"
#include "types/type_3DF8D8.h"
#include "types/type_44350.h"

struct type_F5740;

// An emitter's settings (0x8C bytes; commands in fives, one per emitter).
struct ParticleTrigger_entry
{
    RwInt16 unk_00;             // set when used
    RwInt16 unk_02;
    RwInt32 unk_04;             // a name's value (sub_18F8B0)
    union
    {
        RwInt32 unk_08;         // as its command stores it
        RwReal unk_08_f;        // the delay in seconds (sub_F5920)
    };
    RwV3d unk_0C;
    type_3DF8D8_04 unk_18;
    union
    {
        RwInt32 unk_20;
        RwInt16 unk_20_w;       // as sub_F5920 reads it
    };
    union
    {
        RwInt32 unk_24;
        RwInt16 unk_24_w;
    };
    type_F5740 *unk_28;         // the emitter it runs (sub_F5740)
    RwInt32 unk_2C;
    RwReal unk_30;
    union
    {
        RwInt32 unk_34;
        RwReal unk_34_f;        // single player reads a real (SP 0xBAC00: fld)
    };
    RwReal unk_38;
    RwReal unk_3C;
    RwInt32 unk_40;
    RwInt32 unk_44;
    RwReal unk_48;
    RwReal unk_4C;
    RwInt32 unk_50;
    RwInt32 unk_54;
    RwInt32 unk_58;
    RwReal unk_5C;
    RwInt32 unk_60;
    RwInt32 unk_64;             // the first's: the others follow it
    RwInt32 unk_68;
    union
    {
        RwInt32 unk_6C;
        RwReal unk_6C_f;        // the interval's bounds (sub_F5920)
    };
    union
    {
        RwInt32 unk_70;
        RwReal unk_70_f;
    };
    RwInt32 unk_74;
    RwInt32 unk_78;
    RwInt32 unk_7C;
    RwReal unk_80;
    RwReal unk_84;
    RwInt32 unk_88;
};
typedef RwChar ParticleTrigger_entry_size_check[sizeof(ParticleTrigger_entry) == 0x8C ? 1 : -1];

class ParticleTrigger : public Trigger
{
public:
    RWS_MAKENEWCLASS(ParticleTrigger);
    RWS_DECLARE_CLASSID(ParticleTrigger);

    ParticleTrigger(const RWS::CAttributePacket &attr);
    ~ParticleTrigger();

    virtual void HandleAttributes(const RWS::CAttributePacket &attr);
    virtual void HandleEvents(RWS::CMsg &pMsg);
    // Its kind (0x12).
    // Inline: the constructor's vtable emits them after it, before ??_G (the image's order).
    virtual RwInt32 vf_008()
    {
        return 0x12;
    }
    // Starts its emitters (none is its child: it returns 0).
    virtual type_3D3548 *vf_020();

    // Forgets the emitter arg_0 (its own copy ended).
    void sub_A8EE0(type_F5740 *arg_0);
    // Stops its emitters.
    void sub_A8F40();

    ParticleTrigger_entry unk_C0[5];
    RwUInt8 unk_37C[0x4];
};
typedef RwChar ParticleTrigger_size_check[sizeof(ParticleTrigger) == 0x380 ? 1 : -1];

// Starts emitter arg_4 of arg_0 with its settings arg_8; stops one; and
// makes the emitter arg_0 carry emitter arg_8's settings arg_C too.
type_F5740 *sub_F5740(ParticleTrigger *arg_0, RwInt32 arg_4, ParticleTrigger_entry *arg_8);
void sub_F5C70(type_F5740 *arg_0);
type_F5740 *sub_F5BC0(type_F5740 *arg_0, ParticleTrigger *arg_4, RwInt32 arg_8, ParticleTrigger_entry *arg_C);

#endif
