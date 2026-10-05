/*
 * type_67620: the objects in the handle table dword_439E78 (12-byte entries:
 * the handle, then the object at +8), which sub_67620 resolves; named after
 * that resolver, as nothing else anchors them yet. type_3D2E7C::sub_71340
 * returns one and sub_32F70 takes one; its vf_024 returns the
 * type_3D2E7C whose sub_71300 gives the entity (the CanShoot and A*
 * scheduler callbacks).
 */
#ifndef TYPE_67620_H
#define TYPE_67620_H

#include "rw/ostypes.h"
#include "types/type_439E78.h"

struct type_3D2E7C;

// type_67620_74: a script's code, as the script VM reads it.
// A script's event handler (8 bytes): the range of event values it takes,
// its code offset, how often it may run (0 for always) and whether it may
// not run twice in a row.
struct type_67620_74_h
{
    RwInt16 unk_00;
    RwInt16 unk_02;
    RwUInt16 unk_04;            // its code offset
    RwUInt8 unk_06;
    RwInt8 unk_07;
};

// A script's handlers for one event (8 bytes).
struct type_67620_74_e
{
    type_67620_74_h *unk_00;
    RwUInt8 unk_04;             // the handler count
    RwUInt8 unk_05[0x3];
};

struct type_67620_74
{
    RwInt32 unk_00;             // (a scalar: a byte array here would give
                                // sub_72AC0's key a /GS cookie)
    RwUInt16 unk_04;            // its id (the performance lookup's key,
                                // type_3D2CD0::sub_6CF50)
    RwUInt8 unk_06;             // its events' count (sub_72C40)
    RwUInt8 unk_07;
    RwInt32 *unk_08;            // the first instruction
    RwInt32 unk_0C;
    type_67620_74_e *unk_10;    // its events' handlers
};

struct type_67620
{
    // +0x000 to +0x00C: its script's saved state, which the script VM
    // (sub_68310) loads to run it: the code pointer, the stack pointer, the
    // frame pointer and a fourth word.
    virtual RwInt32 *vf_000();
    virtual RwInt32 *vf_004();
    virtual RwInt32 *vf_008();
    virtual RwInt32 vf_00C();
    virtual void vf_010();
    // +0x014: a kind; "SetFiveWayBlend" sets unk_129 on kind 1 only.
    virtual RwInt32 vf_014();
    // +0x018 to +0x020: store the code, stack and frame pointers back when
    // the script VM yields (sub_68310).
    virtual void vf_018(RwInt32 *arg_0);
    virtual void vf_01C(RwInt32 *arg_0);
    virtual void vf_020(RwInt32 *arg_0);
    virtual type_3D2E7C *vf_024();
    virtual RwInt32 vf_028();
    virtual void vf_02C();
    // +0x030: the object's script thread manager (the script command
    // "CreateThread", sub_44820, starts a thread through it).
    virtual struct type_6EE50 *vf_030();
    // +0x034: the object's script task ("GetTaskReturnRegister",
    // "GetWakeUpMessageID").
    virtual struct type_46120 *vf_034();
    virtual void vf_038();
    // +0x03C: the script's current line and file (the line opcode,
    // sub_6A6F0).
    virtual void vf_03C(RwInt32 arg_0, RwInt32 arg_4);

    union
    {
        RwUInt32 unk_04;        // its handle (the call opcode, sub_69330,
                                // passes it to the command)
        type_439E78_00 unk_04_h;
    };
    RwUInt8 unk_08[0x6C];
    struct type_67620_74 *unk_74;   // its script's code (the event opcode,
                                    // sub_695A0, jumps into unk_08)
    RwUInt8 unk_78[0x94];
    bool unk_10C;               // a task's: whether it is waiting (the kill
                                // opcode, sub_69F40, wakes it first)
    RwUInt8 unk_10D[0x7];
    struct type_3D2E20_114 *unk_114; // a task's thread (the thread opcode,
                                     // sub_6A1A0)
    // +0x118 to +0x120: a script task's (type_46120, kind 3) fields.
    struct type_46120_118 *unk_118;
    RwInt32 unk_11C;            // the message that woke it ("GetWakeUpMessageID")
    RwInt32 unk_120;            // its return register ("GetTaskReturnRegister")
    RwReal unk_124;             // "SetFiveWayBlend" sets it to 2/15 with unk_129
    RwUInt8 unk_128[0x1];
    bool unk_129;               // set by "SetFiveWayBlend" when vf_014 is 1

    // An inline setter for unk_129, with no address and so no database name;
    // named for its field. Evidence: "SetFiveWayBlend" converts a constant 1
    // to the flag at run time (mov eax, 1; test eax, eax; setnz), which is
    // what a constant argument of an inline function expands to
    // (docs/toolchain.md).
    void set_unk_129(RwBool arg_0)
    {
        unk_129 = (bool)arg_0;
    }

    // An inline accessor for unk_04, with no address and so no database
    // name; named for its field. Evidence: alfamessman's sub_6B710 copies
    // it through a local of its own, as type_3D2E7C::get_unk_04 does.
    RwUInt32 get_unk_04()
    {
        RwUInt32 r = unk_04;
        return r;
    }
    // Likewise, the handle as its struct, with no result local. Evidence:
    // sub_6B9A0 and sub_6BA60 copy it into a registration through a return
    // temporary, loading it before the registration's pointer.
    type_439E78_00 get_unk_04_h()
    {
        return unk_04_h;
    }

    // The script VM's calls on the running script (sub_693A0 to sub_69620);
    // only the widths are known. sub_6DE40 plays the animation arg_0 words
    // at arg_4 describe (whether it could), sub_6DDF0 ends the script,
    // sub_6D380 waits (the wait opcode, sub_69500), sub_6E390 resumes;
    // sub_6E490 picks the event handler (a code offset), and sub_6E400,
    // sub_6E430 and sub_6E450 test, set and test the flag arg_0.
    bool sub_6DE40(RwInt32 arg_0, RwInt32 *arg_4, RwInt32 arg_8, RwInt8 arg_C, RwReal arg_10);
    void sub_6DDF0(RwInt8 arg_0, RwUInt8 arg_4);
    void sub_6D380(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 *arg_C, RwInt32 *arg_10,
                   RwInt32 arg_14, RwInt32 arg_18, RwInt32 arg_1C);
    void sub_6E390();
    RwInt32 sub_6E490(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8);
    bool sub_6E400(RwInt32 arg_0);
    void sub_6E430(RwInt32 arg_0, RwInt8 arg_4);
    bool sub_6E450(RwInt32 arg_0);
    // sub_6F500 sleeps arg_0 (the sleep opcode, sub_69B70); sub_6FB50 is
    // its script's locals; sub_6F460 and sub_6F340 pass a call's arguments
    // at arg_4 (the stack) to the script, the latter to the function arg_0
    // (whether it ran). Only the widths are known.
    void sub_6F500(RwInt16 arg_0);
    // Delivers the message arg_0 through the registration arg_4 (a kind-1
    // registration's script, sub_6C8B0); only the widths are known.
    void sub_6F110(struct type_42E00 *arg_0, struct type_6B960 *arg_4);
    RwInt32 *sub_6FB50();
    void sub_6F460(RwInt32 *arg_0);
    bool sub_6F340(struct type_4492EC *arg_0, RwInt32 *arg_4);
};

#endif
