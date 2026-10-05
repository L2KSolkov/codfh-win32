/*
 * CustomTrigger (the class name it registers with the class factory at
 * 0x30A6A9, with its MakeNew, sub_A2DD0, and its size, 0x120): a trigger
 * derived from Trigger, anchored at its vtables off_3D5CCC and off_3D5CC4
 * (+0x18), which its constructor (sub_A2E50) and destructor (sub_A3080)
 * install.
 */
#ifndef CUSTOMTRIGGER_H
#define CUSTOMTRIGGER_H

#include "rw/ostypes.h"
#include "types/type_3DF8D8.h"
#include "types/type_44350.h"

// Its keys (0x40 bytes at +0xC0); the compiler writes their constructor
// (sub_A2F70).
struct type_A2F70
{
    type_3DF8D8_04 unk_00[2];   // commands 4 and 5
    type_3DF8D8_04 unk_10[2];   // commands 6 and 7
    type_3DF8D8_04 unk_20[2];
    type_3DF8D8_04 unk_30;      // command 0
    type_3DF8D8_04 unk_38;      // command 1
};

class CustomTrigger : public Trigger
{
public:
    RWS_MAKENEWCLASS(CustomTrigger);
    RWS_DECLARE_CLASSID(CustomTrigger);

    CustomTrigger(const RWS::CAttributePacket &attr);
    ~CustomTrigger();

    virtual void HandleAttributes(const RWS::CAttributePacket &attr);
    // Folded (/OPT:ICF) into CCESSPoolTrigger's (sub_A2BF0): it passes its
    // events to Trigger's.
    virtual void HandleEvents(RWS::CMsg &pMsg);
    // Its child: a type_3D51C0 spawned for it (sub_9AD40).
    virtual type_3D3548 *vf_020();

    // Frees its two blocks and clears its keys (arg_0, its unk_C0).
    void sub_A30F0(type_A2F70 *arg_0);

    type_A2F70 unk_C0;
    RwUInt8 unk_100[0x4];
    RwUInt8 *unk_104;           // blocks of 0x20 bytes (commands 2 and 3)
    RwUInt8 *unk_108;
    RwUInt8 unk_10C[0x6];       // the last two set; command 8's value
                                // at +2
    RwUInt8 unk_112[0x6];       // the last two set; command 9's value
                                // at +2
    RwUInt8 unk_118[0x8];
    // vf_008, as the image's vtable has it (a trivial body, folded into
    // sub_39180 with every other copy).
    virtual RwInt32 vf_008()
    {
        return 11;
    }
};
typedef RwChar CustomTrigger_size_check[sizeof(CustomTrigger) == 0x120 ? 1 : -1];

// Frees a 0x20-byte block (to the pool at 0x4D1D78; sub_145770 takes one).
void sub_145790(void *arg_0);
void *sub_145770();

#endif
