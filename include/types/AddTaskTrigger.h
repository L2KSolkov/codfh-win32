/*
 * AddTaskTrigger (the class name it registers with the class factory at
 * 0x30A4C9, with its MakeNew, sub_9DD80, and its size, 0x100): a trigger of
 * kind 0x17, derived from Trigger, anchored at its vtable off_3D58D0 (a
 * second vtable, off_3D58C8, sits at +0x18). Its constructor is sub_9DE00
 * and its destructor sub_9E070. When its start message comes
 * (dword_4B67C0) it registers sub_9E850 on its task group's message
 * (unk_D4, "AddTaskGroup"), which each time hands the task unk_C4 (or
 * unk_CC) to the next entities, unk_DC of them in all: the nearest (flag
 * bit 7; within the band unk_F4 to unk_F8, squared, from its point or its
 * object unk_E8, in the entity lists unk_E4 picks) or the message's own
 * sender. The constant functions after its code (0x9DFF0 to 0x9E030) are
 * Trigger's own (its vtable off_3D674C).
 */
#ifndef ADDTASKTRIGGER_H
#define ADDTASKTRIGGER_H

#include "rw/ostypes.h"
#include "types/type_44350.h"

struct type_67620;
struct type_6B960;

// A candidate entity and its squared distance (sub_9ECE0 fills up to 0x100
// of them for sub_9E990).
struct type_9ECE0
{
    type_3D3548 *unk_00;
    RwReal unk_04;
};

// What the task group's message hands sub_9E850: only the sender's handle
// (+0x0C) is known.
struct type_9E850_4
{
    RwUInt8 unk_00[0xC];
    RwInt32 unk_0C;
};

class AddTaskTrigger : public Trigger
{
public:
    RWS_MAKENEWCLASS(AddTaskTrigger);
    RWS_DECLARE_CLASSID(AddTaskTrigger);

    AddTaskTrigger(const RWS::CAttributePacket &attr);
    ~AddTaskTrigger();
    virtual void HandleAttributes(const RWS::CAttributePacket &attr);
    virtual void HandleEvents(RWS::CMsg &pMsg);
    // Its kind (0x17), out of line in unit_09AD40.
    // Inline: the constructor's vtable emits them after it, before ??_G (the image's order).
    virtual RwInt32 vf_008()
    {
        return 0x17;
    }

    // Sends "AddTaskToObject" to the script object arg_0 (0 for its own
    // group's) about arg_4: the task named by the key arg_8, with unk_F0.
    void sub_9E930(struct type_3D2E7C *arg_0, type_67620 *arg_4, type_3DF8D8_04 *arg_8);
    // Hands the task to the nearest candidates, up to unk_E0 of them.
    void sub_9E990(type_67620 *arg_0);
    // Adds the entities of the list from arg_0 within its band to arg_4
    // (*arg_8 of them so far).
    void sub_9ECE0(type_3D3548 *arg_0, type_9ECE0 *arg_4, RwInt32 *arg_8);
    // Hands the task to the entity arg_0 by its side (flags 1, 3 and 5);
    // likewise with the second task when set (flags 2, 4 and 6).
    void sub_9EED0(type_3D3548 *arg_0);
    void sub_9EFD0(type_3D3548 *arg_0);

    type_6B960 *unk_C0;         // its registration on the task group
    type_3DF8D8_04 unk_C4;      // the task (command 1, of the kind 0xC)
    type_3DF8D8_04 unk_CC;      // a second task (command 12)
    RwInt16 unk_D4;             // its task group's message (-1 for none)
    RwUInt8 unk_D6[0x2];
    RwInt32 unk_D8;             // how many to hand out (command 0)
    RwInt32 unk_DC;             // how many are left
    RwInt32 unk_E0;             // how many at a time (command 8)
    RwInt32 unk_E4;             // the entity lists to search (command 10)
    type_3DF8D8_04 unk_E8;      // its point's object (command 11)
    RwInt32 unk_F0;             // the task's value (command 2)
    RwReal unk_F4;              // the band, squared (commands 7 and 6)
    RwReal unk_F8;
    union
    {
        RwUInt32 unk_FC;
        struct
        {
            RwUInt32 unk_FC_0 : 1;  // to the message's sender (command 3)
            RwUInt32 unk_FC_1 : 1;  // by side (commands 13 to 18)
            RwUInt32 unk_FC_2 : 1;
            RwUInt32 unk_FC_3 : 1;
            RwUInt32 unk_FC_4 : 1;
            RwUInt32 unk_FC_5 : 1;
            RwUInt32 unk_FC_6 : 1;
            RwUInt32 unk_FC_7 : 1;  // to the nearest (command 5)
        };
    };
};
typedef RwChar AddTaskTrigger_size_check[sizeof(AddTaskTrigger) == 0x100 ? 1 : -1];

// The task group's callback (registered by HandleEvents).
RwInt32 sub_9E850(AddTaskTrigger *arg_0, type_9E850_4 *arg_4);

#endif
