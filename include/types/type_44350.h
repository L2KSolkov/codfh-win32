/*
 * The script interpreter's commands ("efuncs"): the table String1
 * (0x4276E0) pairs each command's name with its function, which sub_441B0
 * looks up by name. A command takes the object that runs the script (a
 * handle, sub_67620) and its call record (type_44350), reads its arguments
 * off the script stack dword_449318 (SCRIPT_ARG) and ends by popping them and
 * pushing its results (sub_44350).
 */
#ifndef TYPE_44350_H
#define TYPE_44350_H

#include "rw/ostypes.h"
#include "types/type_3DF8D8.h"
#include "types/type_67620.h"
#include "rw/bamatrix.h"
#include "types/type_D48D0.h"
#include "types/type_129_base.h"
#include "types/type_3D2E7C.h"
#include "types/alfasched.h"
#include "rws/cattributehandler.h"
#include "rws/ceventhandler.h"
#include "rws/linearallocationpolicy.h"

struct type_3D3548;

// A command's function.
struct type_44350;
typedef void (*type_4276E0_fn)(RwUInt32 arg_0, type_44350 *arg_4);

// type_44350: a command's call record, named after sub_44350, which pops
// and pushes by it. The script image holds them (the script VM's command
// table, Base): the image names the command, which the loader binds to its
// function (sub_67E30), and the call opcode (sub_69330) passes the record.
struct type_44350
{
    RwChar *unk_00;         // the command's name
    RwInt32 unk_04;         // its key (the table is sorted by it)
    RwUInt8 unk_08[0x4];
    RwInt32 unk_0C;         // the stack slots the call pops
    RwUInt8 unk_10[0x4];
    RwInt32 unk_14;         // the results it pushes
    type_4276E0_fn unk_18;  // the command's function
    RwInt8 *unk_1C;         // each argument's slot, counted up from the
                            // first popped
};

// An entry of String1: a command's name and its function.
struct type_4276E0
{
    const RwChar *unk_00;
    type_4276E0_fn unk_04;
};

struct type_67620;

// The script stack (its top), and the object of the script being debugged
// (sub_44220 reads it; only its type is known).
extern RwInt32 *dword_449318;
extern type_67620 *dword_449328;
extern type_4276E0 String1[];

// Argument n (from 1) of the call ctx, as an RwInt32 lvalue: an inline
// function with no address, so no database name; named for what it does.
// Evidence for its shape: the commands compute the index's `n - 1` at run
// time with n a constant (an inline's parameter, unfolded at /Od), and load
// the argument straight into their own local (a reference, no temporary).
inline RwInt32 &SCRIPT_ARG(type_44350 *ctx, RwInt32 n)
{
    return (dword_449318 - ctx->unk_0C)[ctx->unk_1C[n - 1]];
}

// Trigger: the base trigger behaviour ("Trigger" in the class factory,
// MakeNew sub_BB9B0, 0xC0 bytes; docs/behaviours.md), an attribute handler
// with an event handler at +0x18 (vtables off_3D674C and off_3D6744).
// Its fields end at 0xC0; the kinds derived from it add their own, which
// type_712B0 (below) declares as the scripts read them. A trigger is what type_3D2E7C::sub_712B0 returns, a script's trigger (the
// "GetMyTrigger..." commands), as the commands read it.
// A key as some kinds of trigger keep it in their kind-specific data (as
// type_3DF8D8_04, without its constructor, so it can share a union).
struct Trigger_key
{
    RwInt32 unk_00;
    RwInt32 unk_04;
};
// Makes *arg_0 its absolute value and returns it; an inline with no
// address, named for what it does. Evidence: Trigger's vf_028 and vf_02C
// store the ternary's result and then copy the variable onto itself, which
// only a reference returned from an inline gives.
inline RwReal &absref(RwReal &arg_0)
{
    arg_0 = arg_0 < 0.0f ? -arg_0 : arg_0;
    return arg_0;
}

// The buffer at Trigger::unk_B0 (commands 36 to 39).
struct Trigger_B0
{
    // Read as integers (the commands) and as sizes: type_3D3548::vf_224
    // copies them into its unk_4C, unk_48 and unk_50.
    union
    {
        RwInt32 unk_00;
        RwReal unk_00_r;
    };
    union
    {
        RwInt32 unk_04;
        RwReal unk_04_r;
    };
    RwInt32 unk_08;
    RwV3d unk_0C;
};

// Its seven blocks (message and task lists read by sub_BD490; unk_00[5] is
// the block sub_BD860 runs).
struct Trigger_30
{
    RwUInt8 *unk_00[7];
};
// One of those blocks (0x20 bytes, sub_BD490): up to five messages' values
// and their ids (-1 ends them).
struct Trigger_block
{
    RwInt32 unk_00[5];
    RwUInt16 unk_14[6];
};
// A named object as Trigger::sub_BD900 reads it: with flag 2 an entity
// (unk_24), else a trigger (unk_2C).
class Trigger;
struct type_3DF8D8_BD900 : type_3DF8D8
{
    RwUInt8 unk_20[0x4];
    type_D48D0 unk_24;
    RwUInt8 unk_28[0x4];
    Trigger *unk_2C;
};
class Trigger : public RWS::CAttributeHandler, public RWS::CEventHandler,
                public RWS::LinearAllocationPolicy
{
public:
    // Its constructor and destructor (sub_BBA30, sub_BBD10); the triggers
    // derived from it call them.
    RWS_MAKENEWCLASS(Trigger);
    RWS_DECLARE_CLASSID(Trigger);

    Trigger(const RWS::CAttributePacket &attr);
    ~Trigger();
    virtual void HandleEvents(RWS::CMsg &pMsg);
    virtual void HandleAttributes(const RWS::CAttributePacket &attr);
    // +0x008: its kind ("DestroyParticle" requires 0x12).
    virtual RwInt32 vf_008();
    // +0x00C: how many CCESS slots it may serve at once (sub_8AFF0).
    // Inline: the constructor's vtable emits them after it, before ??_G (the image's order).
    virtual RwInt32 vf_00C()
    {
        return 0x7FFFFFFF;
    }
    // +0x010: the number of entities it may spawn, arg_0 and arg_4
    // ("SetNumSpawnableEntities"); only the widths are known.
    virtual void vf_010(RwInt32 arg_0, RwInt32 arg_4);
    // +0x014: whether its entities live only once ("IsOnlyLiveOnce").
    virtual RwInt32 vf_014();
    // +0x018: its CCESS tracker's kind (1 or 2; sub_8B180, sub_8B4C0).
    // Inline: the constructor's vtable emits them after it, before ??_G (the image's order).
    virtual RwInt32 vf_018()
    {
        return 4;
    }
    // +0x01C: its key (&unk_28; AddTaskTrigger's sub_9E010).
    // Inline: the constructor's vtable emits them after it, before ??_G (the image's order).
    virtual type_3DF8D8_04 * vf_01C()
    {
        return &unk_28;
    }
    // +0x020: the trigger's child entity ("CreateMyChild", sub_453F0).
    virtual type_3D3548 *vf_020();
    // +0x024: the CCESS slot it answers (sub_8AFF0, sub_8B3C0).
    // Inline: the constructor's vtable emits them after it, before ??_G (the image's order).
    virtual RwInt32 vf_024()
    {
        return -1;
    }
    // +0x028: a test of the matrix arg_0 against the trigger (sub_BE110; 1
    // while its unk_24_7 is clear). LadderTrigger's (binary for now, a
    // realigned frame) also tries it turned half round.
    virtual RwInt32 vf_028(struct RwMatrixTag *arg_0);
    // +0x02C: likewise against the direction to the trigger (sub_BE410; 1
    // while its unk_24_12 is clear).
    virtual RwInt32 vf_02C(struct RwMatrixTag *arg_0);

    // Reads a count and that many entries from arg_0 into a new 0x20-byte
    // block (*arg_4, from sub_145770, first filled with 0xFF); nothing when
    // the count is 0 (CustomTrigger's commands 2 and 3).
    void sub_BD490(const RwChar *arg_0, RwUInt8 **arg_4);
    // Frees the block *arg_0 (sub_145790) and clears it.
    void sub_BD350(RwUInt8 **arg_0);
    // Forgets its entity (the entity's vf_230, sub_CCD30).
    void sub_BD860();
    // Its own type_3D2E7C (its script object; VehicleTrigger's sub_C0F30,
    // "GetEntityFromName").
    struct type_3D2E7C *sub_BDF50();
    // Set the trigger's action icon ("SetMyTriggerActionIcon"), move it
    // ("SetMyTriggerPosition") and move it back ("RestoreMyTriggerPosition");
    // only the widths are known.
    void sub_BBF80(RwInt32 arg_0);
    void sub_BE710(RwReal arg_0, RwReal arg_4, RwReal arg_8);
    void sub_BE810();
    // Starts the trigger's physics message arg_0 for the entity's type_3D2E7C
    // arg_8 (a type_3D32F8's collisions, vf_06C); arg_4 only known by width.
    void sub_BDAC0(RwInt32 arg_0, RwInt32 arg_4, struct type_3D2E7C *arg_8);
    // Lets the script object *arg_0 go (sub_71970) and clears it.
    void sub_BD310(RwInt32 *arg_0);
    // Frees the block list *arg_0 and clears it; makes a new one.
    void sub_BD380(struct Trigger_30 **arg_0);
    void sub_BD3B0(struct Trigger_30 **arg_0);
    // Frees the filter list *arg_0 and clears it (and unk_45).
    void sub_BD460(struct type_71250 **arg_0);
    // Adds the handle arg_0 to its list; takes it off again.
    void sub_BD1A0(struct type_144940 *arg_0);
    void sub_BD200(struct type_144940 *arg_0);
    // The 0x18-byte buffer at unk_B0, made on first use.
    RwUInt8 *sub_BEA60();
    // Frees the block list *arg_0 once all its blocks are gone.
    void sub_BD3D0(struct Trigger_30 **arg_0);
    // Runs the block for the entity arg_0's kind: on entering (sub_BD560),
    // leaving (sub_BD780), and block 6 (sub_BD8A0); sub_BD900 sends a
    // block's messages from the entity arg_4.
    void sub_BD560(struct type_3D3548 *arg_0);
    void sub_BD780(struct type_3D3548 *arg_0);
    void sub_BD8A0(struct type_3D3548 *arg_0);
    // What kinds 26 and 32 (LadderTrigger) do when an entity leaves them:
    // an empty method /OPT:ICF folded into sub_15FB30 (sub_145640).
    void sub_15FB30(struct type_3D3548 *arg_0);
    void sub_BD900(RwUInt8 *arg_0, struct type_3D3548 *arg_4);
    // Makes a new script object in *arg_0 for it, starting the script
    // arg_4 and the task function arg_8 (each -1 for none).
    void sub_BD290(RwInt32 *arg_0, RwUInt16 arg_4, RwUInt16 arg_8);
    // Builds its message filter list from a count and that many pairs of
    // named variables (sub_BDC90, sub_BDD10 fill it in).
    void sub_BDB60(const RwChar *arg_0);
    // Sets its script and its task function (starting each once its
    // script object is live).
    void sub_BDE70(RwUInt16 arg_0);
    void sub_BDEE0(RwUInt16 arg_0);
    // A random point inside its shape, through its matrix, into *arg_0.
    void sub_BDF70(RwV3d *arg_0);
    // Its system commands (its matrix).
    void sub_BD0B0(const RWS::CAttributePacket &attr);
    // An inline setter for unk_24_3, with no address and so no database
    // name; named for its field. Evidence: HandleEvents clears the bit
    // through `!` on a constant, which only an inline's parameter keeps.
    void set_unk_24_3(bool arg_0)
    {
        unk_24_3 = !arg_0;
    }
    // Its reading, likewise inverted. Evidence: the spatial table's cell
    // mask (sub_145B40) turns the bit into 0 or 1 (neg, sbb, inc) before
    // it tests it.
    RwInt32 get_unk_24_3()
    {
        return !unk_24_3;
    }
    // Counts one more of its filter entries' values in (sub_BDC90,
    // sub_BDD10); inlines with no address, named for what they do.
    // Evidence: both read the new count back into a byte temporary after
    // keeping the old one in a second temporary below it, which only a
    // nested inline's return value gives.
    RwUInt8 post_inc_unk_45()
    {
        return unk_45++;
    }
    RwUInt8 inc_unk_45()
    {
        post_inc_unk_45();
        return unk_45;
    }

    RwUInt8 unk_20[0x4];
    union
    {
        RwUInt32 unk_24;
        struct
        {
            RwUInt32 unk_24_0 : 1;  // VehicleEnterExitTrigger: both its
                                    // vehicle and exit tasks are done
            RwUInt32 unk_24_1 : 1;
            RwUInt32 unk_24_2 : 1;  // command 29
            RwUInt32 unk_24_3 : 1;  // set while proximity checks are off
                                    // ("SetTriggerProximityChecks")
            RwUInt32 unk_24_4 : 1;  // command 30
            RwUInt32 unk_24_5 : 1;  // command 33
            RwUInt32 unk_24_6 : 1;  // StreamTrigger: its stream started
                                    // (sub_BB1F0; dword_4B67B8 clears it)
            RwUInt32 unk_24_7 : 1;
            RwUInt32 unk_24_8 : 1;
            RwUInt32 unk_24_9 : 1;  // a pickup it spawns is not flagged 0x20000
                                    // (type_3D94B8::sub_FADB0)
            RwUInt32 unk_24_10 : 1; // command 12
            RwUInt32 unk_24_11 : 1;
            RwUInt32 unk_24_12 : 1; // the facing test vf_02C applies
            RwUInt32 unk_24_13 : 1; // its blocks' messages go to the named
                                    // object unk_A0 (sub_BD900)
            RwUInt32 unk_24_14 : 1; // SoldierTrigger registers its weapons'
                                    // names at once with it (sub_B8000)
            RwUInt32 unk_24_15 : 1; // set while moved (sub_BE710; sub_BE810
                                    // moves it back)
            RwUInt32 unk_24_16 : 1; // it keeps the buffer at unk_B0 (command 35)
            RwUInt32 unk_24_17 : 1; // command 31
            RwUInt32 unk_24_18 : 1; // passed to sub_D56D0 for its spawn
                                    // (sub_73710)
            RwUInt32 unk_24_19 : 1; // its entity may make way for a
                                    // priority spawn (sub_D56D0)
            RwUInt32 unk_24_20 : 1; // SoldierTrigger: its soldier's unk_88_10
                                    // (type_3DAFC8::sub_135430)
        };
    };
    type_3DF8D8_04 unk_28;  // a key (sub_198800)
    struct Trigger_30 *unk_30;  // its blocks (sub_BD3B0; the destructor
                                // frees them)
    RwReal unk_34;          // the facing tests' limits (vf_028, vf_02C):
    RwReal unk_38;          // the cosines level and upright
    RwInt16 unk_3C;         // what "GetMyTriggerPointer" returns (its
                            // handle, sub_144C00)
    RwUInt16 unk_3E;        // its script's id (-1 for none; HandleEvents)
    RwUInt16 unk_40;        // a task function's (-1 for none)
    RwUInt8 unk_42;         // its action icon in the low four bits
                            // (sub_BBF80)
    RwUInt8 unk_43;
    RwInt8 unk_44;          // its entity's callback, an index into
                            // dword_429238 (-1 for none; sub_CCCD0)
    RwUInt8 unk_45;
    RwUInt8 unk_46;        // its shape: 0 a sphere (radius unk_48), 1 a
                            // cylinder (radius, height), 2 a box (sub_F54E0)
    RwUInt8 unk_47;
    RwReal unk_48;          // the three metrics "GetMyTriggerMetric" returns
    RwReal unk_4C;
    RwReal unk_50;
    RwReal unk_54;          // SoldierTrigger's command 32, times 100
    RwUInt8 unk_58[0x8];
    union
    {
        struct
        {
            RwUInt8 unk_60[0x4];    // a matrix, where "SpawnParticle"
                                    // spawns without an entity
            RwUInt8 unk_64[0x2C];
            RwReal unk_90;          // the matrix's position (sub_73710's
            RwReal unk_94;          // warning)
            RwReal unk_98;
            RwUInt8 unk_9C[0x4];
        };
        RwMatrixTag unk_60_m;       // (identity at first; RwMatrixTag, as
                                    // RwMatrix's alignment would move the
                                    // fields above)
    };
    type_3DF8D8_04 unk_A0;
    RwInt32 unk_A8;             // its script object (sub_BDF50; sub_BD310
                                // lets it go)
    struct type_71250 *unk_AC;  // its message filter list
    RwUInt8 *unk_B0;            // a 0x18-byte buffer (sub_BEA60)
    struct type_144940 *unk_B4; // the handles holding it (sub_BD1A0,
                                // sub_BD200)
    RwUInt8 unk_B8[0x8];

    // Inline accessors for the metrics, with no address and so no database
    // names; named for their fields. Evidence: the triggered particles'
    // spread (sub_F54E0) reads each through a temporary.
    // The shape as a word: the same spread switches on it as a whole
    // register (a switch on the byte itself compares bytes).
    RwInt32 get_unk_46()
    {
        return unk_46;
    }
    RwReal get_unk_48()
    {
        RwReal r = unk_48;
        return r;
    }
    RwReal get_unk_4C()
    {
        RwReal r = unk_4C;
        return r;
    }
    RwReal get_unk_50()
    {
        RwReal r = unk_50;
        return r;
    }
};

// The trigger handles' table (sub_144C00 gives a trigger its handle,
// sub_144C50 frees it) and the trigger blocks' pool (sub_1457D0 makes a
// Trigger_30, sub_1457B0 frees one).
RwInt32 sub_144C00(Trigger *arg_0);
// A moved trigger's record (sub_145830 takes one from the pool dword_4D1D98,
// sub_145870 frees it): the trigger's handle and where it was.
struct type_145830
{
    RwInt32 unk_00;
    RwV3d unk_04;
};
extern type_16C2A0 dword_4D1D98;
type_145830 *sub_145830();
void sub_145870(type_145830 *arg_0);
// Updates the trigger arg_0 in the trigger table after it moved.
void sub_145A40(Trigger *arg_0);
// Tells the trigger table the trigger arg_0's blocks changed.
void sub_145A10(Trigger *arg_0);
// The script-name variables' callback (sub_198900; commands 13 and 14).
RwInt32 sub_191EE0(void *arg_0, void *arg_4);
// A trigger-handle variable as sub_BDE40 fills it (sub_198900's callback).
struct type_BDE40
{
    RwUInt8 unk_00[0x10];
    RwInt32 unk_10;
    RwUInt8 unk_14[0x10];
    type_144940 unk_24;
};
// The filter entries' callbacks and their sort (sub_BDB60).
RwInt32 sub_BDC90(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8);
RwInt32 sub_BDD10(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8);
void sub_BDD90(type_71250 *arg_0);
RwInt32 __cdecl sub_BDDC0(const void *arg_0, const void *arg_4);
RwInt32 sub_BDE40(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8);
void sub_144C50(Trigger *arg_0);
Trigger_30 *sub_1457D0();
void sub_1457B0(Trigger_30 *arg_0);

// type_712B0: a trigger as the scripts and the entities read it, the base
// Trigger with the fields of the kinds derived from it (from +0xC0; each
// kind uses its own). Its methods are the base's own non-virtual ones.
typedef RwChar Trigger_size_check[sizeof(Trigger) == 0xC0 ? 1 : -1];

struct type_712B0 : Trigger
{
    // Keys an animated background entity (type_3D32F8) takes: its model
    // (unk_C0), its AI script (unk_D0) and its tasks (unk_D8); vf_058 also
    // matches unk_C8.
    type_3DF8D8_04 unk_C0;
    type_3DF8D8_04 unk_C8;
    type_3DF8D8_04 unk_D0;
    type_3DF8D8_04 unk_D8;
    // Keys (names, two script slots each) by the trigger's kind: a vehicle
    // trigger's own name (kind 7, "VehicleTrigger_GetMyName"), a vehicle's
    // name (kinds 5 and 0x1F, "SoldierTrigger_GetMyVehiclesName"), and the
    // default spline paths "SetSplinePathFromName" takes for a type_3DDB98
    // (unk_E0), a type_3DAC58 (unk_E8), a type_3DA6C0 (unk_F0) and a soldier
    // (unk_F8).
    type_3DF8D8_04 unk_E0;
    type_3DF8D8_04 unk_E8;
    type_3DF8D8_04 unk_F0;
    type_3DF8D8_04 unk_F8;  // a type_3D32F8 reads it as its speed along its
                            // spline (a float) and a flag (unk_100_f
                            // instead while set)
    union
    {
        struct
        {
            union
            {
                RwInt32 unk_100;
                RwReal unk_100_f;
            };
            RwInt16 unk_104[0x3];   // copied into a type_3D32F8's unk_44C
            RwInt16 unk_10A[0x5];   // a type_3D32F8's (vf_0E4, vf_0E8; -1
                                    // ends them)
        };
        struct
        {
            Trigger_key unk_100_k;   // a type_3D5400's two keys (vf_058)
            Trigger_key unk_108_k;
        };
    };
    RwInt32 unk_114;        // a vehicle trigger's gun kind (1: the player
                            // takes weapon 0x23 aboard, else 0x1D)
    RwUInt8 unk_118[0x4];
    RwInt32 unk_11C;        // a kind-8 trigger's CCESS side (vf_018: 1 gives
                            // tracker kind 2, 2 gives 1, else 4)
    RwReal unk_120;         // a type_3D32F8's unk_430 and unk_434 (truncated)
    RwUInt8 unk_124[0x4];
    RwInt32 unk_128;        // whether allies, enemies, bullets and explosions
    RwInt32 unk_12C;        // may damage a type_3D32F8 (vf_064, vf_068)
    RwInt32 unk_130;
    RwInt32 unk_134;
    RwInt32 unk_138;        // a type_3D32F8 takes its model from unk_C8
                            // while set (sub_75530)
    RwInt32 unk_13C;        // whether a type_3D32F8 spawns a mounted weapon
    RwInt32 unk_140;        // (sub_166D40, with these and unk_148 to unk_17C)
    RwInt32 unk_144;        // its mounted weapon's tag digit (type_3D32F8's
                            // vf_04C, mod 10)
    RwInt32 unk_148;
    RwUInt32 unk_14C;       // a kind-8 trigger's flags (AnimatedBGTrigger's
                            // vf_030 to vf_038 test bits 0 to 2)
    type_3DF8D8_04 unk_150;     // an animated background entity's mounted
                                // weapon's script (type_3DC9B0::sub_166FA0)
    RwInt32 unk_158;
    RwInt32 unk_15C;
    RwInt32 unk_160;
    RwUInt8 unk_164[0x4];
    RwInt32 unk_168;        // its start state ("GetStartState")
    RwUInt8 unk_16C[0xC];
    RwInt32 unk_178;        // a type_3D32F8 runs its physics while set
    RwInt32 unk_17C;
    RwUInt8 unk_180[0x40];
    type_3DF8D8_04 unk_1C0;     // a vehicle's mounted weapon's script
                                // (type_3DC9B0::sub_166FA0)
    RwUInt8 unk_1C8[0x24];
    type_3DF8D8_04 unk_1EC; // a vehicle's default spline path
                            // ("SetSplinePathFromName")
    RwUInt8 unk_1F4[0x30];
    struct type_1227C0 *unk_224;    // a kind-0x13 trigger's projectile
                                    // generator ("PG_TargetObjectByScript")

    // Destroys the trigger's particle ("DestroyParticle").
    void sub_A8F40();
    // Enables an end-level trigger (kind 0x24) with arg_0
    // ("EnableEndLevelTrigger"); only the width is known.
    void sub_CC2A0(RwInt32 arg_0);
    // An inline accessor for unk_AC, with no address and so no database
    // name; named for its field. Evidence: type_3D2E7C::sub_71250 copies it
    // through a local of its own.
    struct type_71250 *get_unk_AC()
    {
        struct type_71250 *r = unk_AC;
        return r;
    }
};

// Views of type_712B0 as the trigger (type_3D3548::unk_34C) of four entity
// kinds, each holding whether allies, enemies, bullets and explosions may
// damage the entity ("SetCanAlliesDamage", "SetCanEnemiesDamage",
// "SetCanBulletsDamage", "SetCanExplosionsDamage" and their getters). They
// overlap type_712B0's keys, so they are separate views, named for the kind.
// The trigger of a type_3DA6C0 (vf_01C).
struct type_712B0_3DA6C0
{
    RwUInt8 unk_00[0x128];
    RwInt32 unk_128;
    RwInt32 unk_12C;
    RwInt32 unk_130;
    RwInt32 unk_134;
};
// The trigger of a type_3DDB98 (vf_024).
struct type_712B0_3DDB98
{
    RwUInt8 unk_00[0x124];
    RwInt32 unk_124;
    RwInt32 unk_128;
    RwInt32 unk_12C;
    RwInt32 unk_130;
};
// The trigger of a type_3DAC58 (vf_020).
struct type_712B0_3DAC58
{
    RwUInt8 unk_00[0xFC];
    RwInt32 unk_FC;
    RwInt32 unk_100;
    RwInt32 unk_104;
    RwInt32 unk_108;
};
// The trigger of the vf_034 kind.
struct type_712B0_034
{
    RwUInt8 unk_00[0xE8];
    RwInt32 unk_E8;
    RwInt32 unk_EC;
    RwInt32 unk_F0;
    RwInt32 unk_F4;
};

// type_46120_118: a script task's current call, as the script VM's call
// opcodes (sub_698A0, sub_69930) set it.
struct type_46120_118
{
    RwUInt8 unk_00[0x10];
    RwInt8 unk_10;
    RwUInt8 unk_11[0x3];
    RwUInt32 unk_14_0 : 1;
    RwUInt32 unk_14_1 : 31;
};

// type_46120: an object's script task (type_67620::vf_034), named after the
// first command reading it, sub_46120: the handle-table object of kind 3
// (the script VM checks vf_014 before treating the running script as one).
// Its fields are type_67620's +0x118 to +0x120.
struct type_46120 : type_67620
{

    // Inline accessors, with no address and so no database names; named for
    // their fields. Evidence: sub_46120 and sub_46180 copy each through a
    // temporary allocated after the check's locals (an inline's local).
    RwInt32 get_unk_11C()
    {
        RwInt32 r = unk_11C;
        return r;
    }
    RwInt32 get_unk_120()
    {
        RwInt32 r = unk_120;
        return r;
    }
    // Removes the interrupt arg_0 ("RemoveInterrupt"); only the width is
    // known.
    void sub_70170(RwInt32 arg_0);
    // The script VM's calls on a running task (sub_69770 to sub_69A90); only
    // the widths are known. sub_6FFD0 and sub_6FF20 start a call (the
    // popped word arg_0, bytes 2 and 3, and a flag: type_3D2E20's, which the
    // VM calls through that type), sub_6FF00 a third kind; sub_70080
    // continues at the code arg_0 and sub_700A0 is its result; sub_70850 and
    // sub_70B70 return (arg_0) and resume.
    void sub_6FF00();
    void sub_70080(RwInt32 *arg_0);
    RwInt32 sub_700A0();
    void sub_70850(RwInt32 arg_0);
    void sub_70B70();
    // sub_70590 wakes the task; sub_6FE00 starts it at function arg_0 and
    // sub_70310 readies it (the spawn opcode, sub_6A080). Only the widths
    // are known.
    void sub_70590(RwUInt8 arg_0, RwInt32 arg_4, RwInt32 arg_8);
    void sub_6FE00(RwInt32 arg_0);
    void sub_70310();
    // Adds the task arg_0 below it (arg_4 and arg_8 its interrupt flags);
    // returns the task to run (the thread opcode, sub_6A1A0).
    type_46120 *sub_70930(type_46120 *arg_0, bool arg_4, bool arg_8);
    // Inline accessors, with no address and so no database names, named for
    // their fields. Evidence: the thread opcode (sub_6A1A0) copies each
    // through a return temporary.
    type_3D2E20_114 *get_unk_114()
    {
        return unk_114;
    }
    bool get_unk_10C()
    {
        return unk_10C;
    }
};

// type_55ED0: a custom trigger (kind 0x0B), as the "Custom_" commands read
// it, named after the first, "Custom_GetStartMessage" (sub_55ED0). Its
// fields overlap type_712B0's unknown middle, so it is a separate view.
// Its message lists (+0x104 and +0x108): up to five messages, their data
// and their ids (0xFFFF ends the list); "Custom_GetStartMessage" reads the
// first id of unk_104, "Custom_SendMessages" sends unk_108's.
struct type_55ED0_104
{
    RwInt32 unk_00[5];
    RwUInt16 unk_14[5];
};
struct type_55ED0_10C
{
    RwInt16 unk_00;
    RwInt16 unk_02;         // a scene id ("Custom_GetSceneID")
    RwInt16 unk_04;
};
struct type_55ED0
{
    RwUInt8 unk_00[0x104];
    type_55ED0_104 *unk_104;
    type_55ED0_104 *unk_108;
    type_55ED0_10C unk_10C[1];  // the scenes, counted from 1 by the script
};

// type_5FC30: a playing sound as a script handle, named after the first
// command reading it, "SoundStillPlaying" (sub_5FC30); only its flags are
// known.
struct type_5FC30
{
    RwUInt8 unk_00[0x34];
    RwUInt32 unk_34;        // bit 1 while it plays
};

void sub_44350(type_44350 *arg_0, void *arg_4);
#ifdef CODFH_SP // an inline in single player: expanded in the script commands (SP 0x58CD0),
                // kept out of line where VC declines (SP 0x32F30)
type_3DF8D8 *sub_198800(type_3DF8D8_04 *arg_0);   // (game/functions.h)
inline void sub_44220(bool arg_0)
{
    type_67620 *stk_18;
    type_3DF8D8 *l14;
    RwInt32 var_10;
    RwUInt8 *ebp_C;
    type_712B0 *v8;
    type_3D2E7C *var_4;

    if (arg_0 == 0 && dword_449328 != 0) {
        stk_18 = dword_449328;
        var_4 = stk_18->vf_024();
        if (var_4 != 0) {
            v8 = var_4->sub_712B0();
            if (v8 != 0) {
                var_10 = 0;
                ebp_C = 0;
                if (v8->unk_28.unk_00 != 0 || v8->unk_28.unk_04 != 0) {
                    l14 = sub_198800(&v8->unk_28);
                    if (l14 != 0)
                        var_10 = l14->unk_14;
                }
                if (v8->unk_60 != 0)
                    ebp_C = v8->unk_60;
            }
        }
    }
}
#else
void sub_44220(bool arg_0);
#endif

// Argument n (from 1) of the call ctx as a T lvalue: the commands load 16-bit
// arguments with a word move and floats with fld (the same accessor, typed).
template <class T> inline T &SCRIPT_ARGT(type_44350 *ctx, RwInt32 n)
{
    return *(T *)&(dword_449318 - ctx->unk_0C)[ctx->unk_1C[n - 1]];
}

// Argument n of the call ctx as a float, by value: an inline function with no
// address, named for what it does. Evidence: "RenderFadeOut" and
// "RenderFadeIn" (sub_44D00, sub_44DA0) copy their argument into their local
// through the FPU, where the reference form moves it as a dword.
inline RwReal SCRIPT_ARGF(type_44350 *ctx, RwInt32 n)
{
    return SCRIPT_ARGT<RwReal>(ctx, n);
}

// A check on the script's behalf, handing e to the debugger's hook
// sub_44220: a macro that passes the condition straight from the expression
// (an inline function's parameter would take a temporary when the condition
// makes a call, sub_45170), then expands an inline function declaring five
// locals it never uses. Evidence for its shape: every function calling
// sub_44220 reserves five more locals per call (sub_441B0, sub_442D0,
// sub_44820) after its own, and those slots come in source order with other
// inline functions' locals and after every block's ("SnapToCover", sub_46D60,
// puts them after get_unk_F60's `this` temporary). Neither the macro nor the
// function has an address or database name; they are named for what they do.
inline void SCRIPT_CHECK_SLOTS()
{
    RwInt32 check_4;
    RwInt32 check_3;
    RwInt32 check_2;
    RwInt32 check_1;
    RwInt32 check_0;
}
#define SCRIPT_CHECK(e) \
    { \
        sub_44220(e); \
        SCRIPT_CHECK_SLOTS(); \
    }

// Another check, with six more unused locals around SCRIPT_CHECK: some call
// sites reserve eleven locals rather than five (sub_450E0, sub_451E0,
// sub_454A0, sub_45540), whatever their condition.
#define SCRIPT_CHECK2(e) \
    { \
        RwInt32 check2_0; \
        RwInt32 check2_1; \
        RwInt32 check2_2; \
        RwInt32 check2_3; \
        RwInt32 check2_4; \
        RwInt32 check2_5; \
        SCRIPT_CHECK(e); \
    }

#endif
