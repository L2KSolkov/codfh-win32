/*
 * type_3D2E7C: the object an entity's vf_098 returns, anchored at its vtable
 * off_3D2E7C, which its constructor sub_70CA0 installs. sub_71870 allocates
 * 0x2C bytes for one, constructs it and registers it (kind 4) in the handle
 * table dword_439E78 with sub_673C0; the entity vf_098 implementations
 * (sub_13F620, sub_155430) resolve their handle to it with sub_67620.
 * sub_31E00 calls sub_71340 on it, which resolves the +0x20 handle that
 * sub_70CA0 zeroes.
 *
 * The vtable has one slot (sub_70D20); a string follows it.
 */
#ifndef TYPE_3D2E7C_H
#define TYPE_3D2E7C_H

#include "rw/ostypes.h"
#include "types/type_67620.h"
#include "types/type_439E78.h"

struct type_3D3548;

// type_71250: a message filter list (type_3D2E7C::sub_71250, and a
// performance map's unk_AC): a count, then that many 4-byte entries, each a
// channel and a rank, sorted; sub_6C6D0 compares two.
struct type_71250_02
{
    RwUInt8 unk_00;         // the channel
    RwUInt8 unk_01;
    RwUInt16 unk_02;        // the rank
};

struct type_71250
{
    RwUInt8 unk_00;         // the entry count
    RwUInt8 unk_01;
    type_71250_02 unk_02[1];
};
// Whether two filter lists share the channel arg_8 at a rank arg_C's high
// nibble allows (sub_6C6D0; AddTaskTrigger matches its group with it).
bool sub_6C6D0(type_71250 *arg_0, type_71250 *arg_4, RwUInt8 arg_8, RwInt8 arg_C);
// A new filter list for arg_0 entries, and its freeing to its pool.
type_71250 *sub_6C9D0(RwInt32 arg_0);
void sub_6CA20(type_71250 *arg_0);

struct type_3D2E7C
{
    // +0x000: resets it with the serial arg_0 (sub_70D20).
    virtual void vf_000(RwInt32 arg_0);

    union
    {
        RwUInt32 unk_04;    // its handle (the Distance Scheduler records it)
        type_439E78_00 unk_04_h;
    };
    struct type_72990 *unk_08; // its script's header
    RwInt32 unk_0C;         // its locals (sub_71CE0)
    type_3D3548 *unk_10;    // the entity, for kind 2 (a trigger for kind 1)
    RwInt32 unk_14;         // a kind
    union
    {
        RwUInt32 unk_18;    // its task
        type_439E78_00 unk_18_h;
    };
    union
    {
        RwUInt32 unk_1C;    // its first task
        type_439E78_00 unk_1C_h;
    };
    union
    {
        RwUInt32 unk_20;    // a handle: sub_71340 resolves it with sub_67620
        type_439E78_00 unk_20_h;    // (its thread manager)
    };
    RwInt32 unk_24;         // a serial the Distance Scheduler checks along
                            // with unk_04
    RwUInt8 unk_28[0x4];

    // The object the unk_20 handle refers to (sub_67620).
    type_67620 *sub_71340();
    type_3D2E7C();
    // Its handle's setter (sub_1E7540, shared through /OPT:ICF with
    // type_3D2C88's).
    void sub_1E7540(RwUInt32 arg_0);
    // The placement pair sub_71870 builds it in its pool slot with, as
    // type_3D2CD0's (sub_6CCF0 and the empty sub_19A750).
    static void *operator new(RwUInt32 arg_0, void *arg_4);
    static void operator delete(void *arg_0, void *arg_4);
    // Ends its script (sub_70D40), its first task (sub_70DB0); sets its
    // entity and kind (sub_70DF0); starts the script arg_0 as a state
    // machine (sub_70E10) or the function arg_0 as a task (sub_70F40),
    // telling it "Initialize" when arg_4 is set.
    void sub_70D40();
    void sub_70DF0(type_3D3548 *arg_0, RwInt32 arg_4);
    void sub_70E10(RwInt32 arg_0, RwInt32 arg_4);
    void sub_70F40(RwInt32 arg_0, RwInt32 arg_4);
    // Ends the object with the reason arg_0 ("DestroySelf", sub_454A0); only
    // the width is known.
    void sub_71100(RwInt32 arg_0);
    // What the script debugger (sub_44220) inspects; only its layout's
    // few fields are known (type_712B0).
    class type_712B0 *sub_712B0();
    // The entity unk_10 for kind 2, else 0 (the scheduler callbacks reach
    // their entity through it).
    type_3D3548 *sub_71300();
    // Ends the object's task (the kill and spawn opcodes, sub_69FB0 and
    // sub_6A080), and gives it the task arg_0; only the widths are known.
    void sub_70DB0();
    void sub_71220(struct type_46120 *arg_0);
    // Its task (sub_71090), and the delivery of the message arg_0 to it
    // through the registration arg_4 (sub_710B0); only the widths are known.
    struct type_46120 *sub_71090();
    // Links the task arg_0 to it (type_3D2E20::sub_70310); only the width
    // is known.
    void sub_71050(struct type_3D2E20 *arg_0);
    // Its first task (sub_71010) and the removal of a task's link
    // (sub_70FF0); only the widths are known.
    void sub_71010(struct type_3D2E20 *arg_0);
    void sub_70FF0(RwUInt32 arg_0);
    // Its message filter list (sub_6C5A0 compares two); only the width is
    // known.
    struct type_71250 *sub_71250();
    void sub_710B0(struct type_42E00 *arg_0, struct type_6B960 *arg_4);

    // Inline accessors for unk_04 and unk_24, with no address and so no
    // database names; named for their fields. Evidence: sub_35120 copies
    // each through a compiler temporary.
    RwUInt32 get_unk_04()
    {
        RwUInt32 r = unk_04;
        return r;
    }
    // Likewise, returned directly, with no result local. Evidence: sub_4BE70
    // ("GetSquadLeader") and sub_63110 ("GetClosestAlarmObject") keep the
    // vf_098() result in a `this` temporary and store the field straight
    // into a named local.
    RwUInt32 get_unk_04_d()
    {
        return unk_04;
    }
    // The handle as its struct, with no result local (type_3D2DB8::sub_6FBB0
    // stores it before loading the destination: a struct copy).
    type_439E78_00 get_unk_04_h()
    {
        return unk_04_h;
    }
    // Likewise (type_3D2DB8::sub_6FB50).
    RwInt32 get_unk_0C()
    {
        RwInt32 r = unk_0C;
        return r;
    }
    // unk_24 returned directly, with no result local. Evidence: the
    // debugger's delivery report (sub_6A970) keeps the object in a `this`
    // temporary and the value in a return temporary allocated after it.
    RwInt32 get_unk_24_d()
    {
        return unk_24;
    }
    RwInt32 get_unk_24()
    {
        RwInt32 r = unk_24;
        return r;
    }
    // Inline accessors for unk_14 and unk_10 with no result local, likewise
    // nameless and named for their fields. Evidence: "OrientToCoverPoint" and
    // the like hold the object in a compiler temporary (the inline's `this`)
    // and test the kind through a second one allocated after it (a return
    // value's), and read the entity straight into their own local.
    RwInt32 get_unk_14()
    {
        return unk_14;
    }
    type_3D3548 *get_unk_10()
    {
        return unk_10;
    }
};
typedef RwChar type_3D2E7C_size_check[sizeof(type_3D2E7C) == 0x2C ? 1 : -1];

#endif
