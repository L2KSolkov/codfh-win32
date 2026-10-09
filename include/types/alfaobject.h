/*
 * The Alfa objects, the handle-table objects scripts run on, as their
 * classes: type_3D2C88 (the base, whose 18 virtual slots type_67620
 * describes), type_3D2C30 (a script host: stack, frame and code) and
 * type_3D2CD0 (an entity's script object), each named for its vtable. The
 * pools that hold them are set up at sub_713E0 ("m_pobjectPool" and the
 * others). type_67620 is the flattened view of the same objects that the
 * script commands and the VM read through.
 */
#ifndef ALFAOBJECT_H
#define ALFAOBJECT_H

#include "rw/ostypes.h"
#include "rw/bavector.h"
#include "game/vecutil.h"
#include "types/type_D48D0.h"
#include "types/type_67620.h"
#include "types/type_439E78.h"

struct type_3D2E7C;

// A record of type_3D2C88's ring of five (vf_038 adds them).
struct type_3D2C88_10
{
    RwInt32 unk_00;
    RwInt32 unk_04;
    RwInt32 unk_08;
    RwInt32 unk_0C;
};

// type_3D2C88: the base (constructor sub_6CB60); its own slots are the
// shared "return 0" (0x1E4CB0) or no-op (0x15FB30) functions but for the
// record ring and the line.
struct type_3D2C88
{
    virtual RwInt32 *vf_000();
    virtual RwInt32 *vf_004();
    virtual RwInt32 *vf_008();
    virtual RwInt32 vf_00C();
    virtual RwInt32 vf_010();
    virtual RwInt32 vf_014();
    virtual void vf_018(RwInt32 *arg_0);
    virtual void vf_01C(RwInt32 *arg_0);
    virtual void vf_020(RwInt32 *arg_0);
    virtual type_3D2E7C *vf_024();
    virtual RwInt32 vf_028();
    // +0x02C and +0x030: checked downcasts (0 here; type_3D2CD0 and type_3D2DB8
    // return themselves).
    virtual struct type_3D2CD0 *vf_02C();
    virtual struct type_3D2DB8 *vf_030();
    virtual struct type_3D2E20 *vf_034();
    // +0x038: adds a record to the ring (sub_6CA60).
    virtual void vf_038(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C);
    // +0x03C: the script's current line and file (sub_6CB20).
    virtual void vf_03C(RwInt32 arg_0, RwInt32 arg_4);
    // +0x040: the current line (folded by /OPT:ICF into a getter of +8, 0xFB710).
    virtual RwInt32 vf_040();
    // +0x044: the file (sub_6CB40).
    virtual RwInt32 vf_044();

    union
    {
        RwUInt32 unk_04;        // its handle
        type_439E78_00 unk_04_h;
    };
    RwInt32 unk_08;             // the current line (-1 at first)
    RwInt32 unk_0C;             // the current file
    type_3D2C88_10 unk_10[5];   // the last five records
    RwInt32 unk_60;             // the ring's next index

    type_3D2C88();
    // Frees it back to its pool (sub_71970) and clears its handle
    // (sub_70B70).
    void sub_70B70();
    // An inline accessor for its handle, with no address and so no database
    // name; named for the field. Evidence: type_3D2DB8::sub_6ED50 copies the
    // handle through a return temporary, stored before the destination is
    // loaded (a struct copy), or copied again into a by-value argument.
    type_439E78_00 get_unk_04_h()
    {
        return unk_04_h;
    }
    // Likewise for the handle as a word, through a local of its own, as
    // type_67620::get_unk_04. Evidence: sub_71970 and sub_717B0 pass it to
    // sub_67520 through a local each.
    RwUInt32 get_unk_04()
    {
        RwUInt32 r = unk_04;
        return r;
    }
    // Sets its handle (sub_1E7540: an out-of-line setter far from its
    // class, so likely one /OPT:ICF kept for several identical ones; only
    // its effect is known).
    void sub_1E7540(RwUInt32 arg_0);
};
typedef RwChar type_3D2C88_size_check[sizeof(type_3D2C88) == 0x64 ? 1 : -1];

// type_3D2C30: a script host (constructor sub_6CAF0, destructor sub_6CC90).
struct type_3D2C30 : type_3D2C88
{
    virtual RwInt32 *vf_004();
    virtual void vf_01C(RwInt32 *arg_0);
    virtual void vf_020(RwInt32 *arg_0);
    // +0x048
    virtual ~type_3D2C30();
    // +0x04C: resets it for the script arg_0 (sub_6CCB0).
    virtual void vf_04C(RwInt32 arg_0);
    // +0x050: empty here (pDtor, 0x1E41C0).
    virtual void vf_050();

    RwInt32 unk_64;             // its script
    RwInt32 *unk_68;            // its code pointer
    RwInt32 *unk_6C;            // the stack pointer
    RwInt32 *unk_70;            // the frame pointer
    type_67620_74 *unk_74;      // its script's code

    type_3D2C30();
    // vf_000, as the image's vtable has it (a trivial body, folded into
    // sub_6EA50 with every other copy).
    virtual RwInt32 *vf_000()
    {
        return unk_68;
    }
    // vf_008, as the image's vtable has it (a trivial body, folded into
    // sub_6EA30 with every other copy).
    virtual RwInt32 *vf_008()
    {
        return unk_70;
    }
    // vf_014, as the image's vtable has it (a trivial body, folded into
    // sub_21D720 with every other copy).
    virtual RwInt32 vf_014()
    {
        return unk_64;
    }
    // vf_018, as the image's vtable has it (a trivial body, folded into
    // sub_1A62D0 with every other copy).
    virtual void vf_018(RwInt32 *arg_0)
    {
        unk_68 = arg_0;
    }
};
typedef RwChar type_3D2C30_size_check[sizeof(type_3D2C30) == 0x78 ? 1 : -1];

// What type_3D2CD0::sub_6CF50 falls back to (arg_4); only its byte at +2
// is known.
struct type_6CF50_04
{
    RwUInt8 unk_00[0x2];
    RwInt8 unk_02;
    RwUInt8 unk_03;             // passed to the entity's vf_0B8 with unk_02
                                // (to vf_0B0) by sub_6D5A0
};

// dword_4B9304: the performance sets, as type_3D2CD0::sub_6CF50 looks them
// up (built by sub_195A50, freed by sub_195B00). Three lists of sets, each
// set a header and its groups inline; a group a header (three keys and its
// choices' count), then its choices, each a count, a weight in percent and
// that many values. All of it lives in one block (unk_18) read from the
// stream.
struct type_EDA50_item
{
    RwInt8 unk_00;              // the values' count
    RwInt8 unk_01;
    RwInt8 unk_02;              // its weight, in percent
    RwInt8 unk_03;
    RwInt32 unk_04[1];
};
struct type_EDA50_sub
{
    RwInt16 unk_00[3];          // its keys
    RwInt16 unk_06;             // its choices' count
    type_EDA50_item *unk_08[1]; // its choices
};
// A set of the first and third lists (by an id, its groups' count).
struct type_EDA50_a
{
    RwInt16 unk_00;
    RwInt16 unk_02;
};
// A set of the second list (by an entity's id).
struct type_EDA50_b
{
    RwInt32 unk_00;
    RwInt16 unk_04;
    RwInt16 unk_06;
};
struct RwStream;
struct type_4B9304
{
    type_EDA50_a **unk_00;
    RwInt32 unk_04;
    type_EDA50_b **unk_08;
    RwInt32 unk_0C;
    type_EDA50_a **unk_10;
    RwInt32 unk_14;
    RwUInt8 *unk_18;

    type_4B9304();
    // Frees it (sub_ED990) when its GodAsset (sub_195B00) deletes it.
    ~type_4B9304();
    // Reads it from arg_0 (sub_195A50).
    void sub_EDA50(RwStream *arg_0);
    // A choice drawn by weight from the group keyed arg_4 of the set for the
    // entity arg_0 (sub_EE1A0; the second list), the id arg_0 (sub_EDFE0;
    // the first) or the two bytes arg_0 and arg_4 with the group arg_8
    // (sub_EE360; the third, falling back to arg_0 alone); 0 when there is
    // none.
    RwInt32 sub_EE1A0(RwInt32 arg_0, RwInt16 arg_4);
    RwInt32 sub_EDFE0(RwInt16 arg_0, RwInt16 arg_4);
    RwInt32 sub_EE360(RwInt8 arg_0, RwInt8 arg_4, RwInt8 arg_8);
};
extern type_4B9304 *dword_4B9304;
// A setter with no address and so no database name. Evidence: its GodAsset
// (sub_195A50) stores it through a temporary holding the value.
inline void set_dword_4B9304(type_4B9304 *arg_0)
{
    dword_4B9304 = arg_0;
}

// An event's state in a type_3D2CD0: how often each handler ran, and the
// last one.
struct type_3D2CD0_B4
{
    RwInt8 unk_00[11];
    RwInt8 unk_0B;
};

// type_3D2CD0: an entity's script object (constructor sub_6CD00,
// destructor sub_6CD80), 0x150 bytes.
struct type_3D2CD0 : type_3D2C30
{
    // Inline: its vtable (the constructor's, sub_6CD00) emits it before ??_G.
    virtual RwInt32 vf_00C()
    {
        return (RwInt32)unk_80;
    }
    virtual type_3D2E7C *vf_024();
    virtual ~type_3D2CD0();
    virtual void vf_050();
    // +0x054: starts it for the script arg_0 with arg_4 (sub_6CE90).
    virtual void vf_054(RwInt32 arg_0, RwInt32 arg_4);

    type_D48D0 unk_78;          // its entity
    RwInt32 unk_7C;
    RwInt32 unk_80[0xC];        // its stack (unk_6C starts here)
    RwInt8 unk_B0[4];           // its flags (-1 clear; the VM's opcode 27)
    type_3D2CD0_B4 unk_B4[8];   // its events' state
    RwInt32 unk_114;
    RwInt32 unk_118;
    RwInt32 unk_11C;
    RwInt32 unk_120;
    RwReal unk_124;
    RwUInt8 unk_128;
    bool unk_129;
    RwUInt8 unk_12A;
    RwUInt8 unk_12B;
    RwV3d unk_12C;
    RwV3d unk_138;
    RwInt32 unk_144;
    RwInt32 unk_148;            // -1 at first
    RwInt32 unk_14C;

    type_3D2CD0();
    // The performance arg_0 of its entity for its script (sub_6CF50): from
    // the entity's set (1 in *arg_8), the script's (2) or the one for the
    // entity's posture and weapon class and arg_4's unk_02 (3); 0 if none.
    // arg_0 is an int the body narrows: sub_6D5A0 pushes the whole dword
    // unk_148 (a short parameter makes this compiler load a word).
    RwInt32 sub_6CF50(RwInt32 arg_0, struct type_6CF50_04 *arg_4, RwInt32 *arg_8);
    // Requests the performance arg_0 (none when it is the script's own and
    // no reset is asked), sub_6D320; and with the points arg_4 and arg_8 and
    // the flags arg_C to arg_1C, sub_6D380 (the VM's wait opcode passes only
    // the id).
    void sub_6D320(RwInt32 arg_0);
    void sub_6D380(RwInt32 arg_0, RwV3d *arg_4, RwV3d *arg_8, RwInt32 arg_C, RwInt32 arg_10,
                   RwInt32 arg_14, RwInt32 arg_18, RwInt32 arg_1C);
    // A cover transition's end (sub_6DD00): leaves the cover point unless
    // arg_0, and tells the script ("CoverTransitionFinished").
    void sub_6DD00(bool arg_0, RwInt32 arg_4);
    // Runs its script (sub_6DDD0).
    void sub_6DDD0();
    // Ends its performance, telling the script ("PerformanceFinished"; the
    // flags arg_0 and arg_4 queue the message), sub_6DDF0.
    void sub_6DDF0(bool arg_0, bool arg_4);
    // Plays the arg_0 animations at arg_4 (bit i of arg_8 each one's flag),
    // releasing the entity's last hold when arg_C is set; whether the last
    // played (the VM's animation opcodes).
#ifdef CODFH_SP // single player's sub_6DE40 has no speed (SP 0x5C340 ends ret 0x10)
    bool sub_6DE40(RwInt32 arg_0, RwInt32 *arg_4, RwInt32 arg_8, bool arg_C);
#else
    bool sub_6DE40(RwInt32 arg_0, RwInt32 *arg_4, RwInt32 arg_8, bool arg_C, RwReal arg_10);
#endif
    // Advances the performance (sub_6D5A0; the entity's vf_03C passes its
    // time step, unused): starts a requested one, steps its transition
    // (unk_118), then applies the entity's performance values.
    void sub_6D5A0(RwReal arg_0);
    // Its animation's end (sub_6DF90, reached through a callback): the next
    // transition animation, or the transition's or performance's end.
    void sub_6DF90(RwInt32 arg_0, bool arg_4);
    // Its entity: an inline with no address and so no database name, named
    // for the field. Evidence: sub_6DE40 reads the entity's unk_280 through
    // a local placed after its own (the inline's).
    struct type_3D3548 *get_unk_78()
    {
        struct type_3D3548 *r = unk_78.sub_D4910();
        return r;
    }
    // Sets it up for the entity arg_0 with arg_4 (sub_6CDA0).
    void sub_6CDA0(struct type_3D3548 *arg_0, RwInt32 arg_4);
    // Its script's state machine's reset and start (sub_6E390, sub_6E3B0);
    // only the widths are known.
    void sub_6E390();
    void sub_6E3B0();
    // Its flags (sub_6E400 tests, sub_6E430 sets, sub_6E450 counts down).
    bool sub_6E400(RwInt32 arg_0);
    void sub_6E430(RwInt32 arg_0, RwInt8 arg_4);
    bool sub_6E450(RwInt32 arg_0);
    // The code offset of the handler for event arg_0 with the value arg_8,
    // by the event's kind arg_4 (1 ranged or random, 2 ranged, 3 the first
    // allowed); 0 for none.
    RwInt32 sub_6E490(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8);
    RwInt32 sub_6E520(RwInt32 arg_0, RwInt32 arg_4);
    RwInt32 sub_6E570(RwInt32 arg_0, RwInt32 arg_4);
    RwInt32 sub_6E5B0(RwInt32 arg_0, RwInt32 arg_4);
    bool sub_6E6A0(RwInt32 arg_0, RwInt32 arg_4, RwInt32 *arg_8);
    bool sub_6E790(RwInt32 arg_0, RwInt32 arg_4, RwInt32 *arg_8);
    // An empty class operator delete: its objects live in pools, so its
    // deleting destructor (sub_6CD60) frees nothing.
    void operator delete(void *arg_0)
    {
    }
    // The placement pair the object manager builds it in its pool slot
    // with (sub_71870 to sub_71B90): operator new (sub_6CCF0, which returns
    // arg_4) and its operator delete, which the shared unwind funclet calls
    // and /OPT:ICF folded into the empty sub_19A750. Members, since the
    // class's own operator delete hides the global ones.
    static void *operator new(RwUInt32 arg_0, void *arg_4);
    static void operator delete(void *arg_0, void *arg_4);
    // vf_02C, as the image's vtable has it (a trivial body, folded into
    // sub_6FCD0 with every other copy).
    virtual struct type_3D2CD0 *vf_02C()
    {
        return this;
    }
    // vf_010, as the image's vtable has it (a trivial body, folded into
    // sub_BAD20 with every other copy).
    virtual RwInt32 vf_010()
    {
        return 0xC;
    }
};
typedef RwChar type_3D2CD0_size_check[sizeof(type_3D2CD0) == 0x150 ? 1 : -1];

// A state of a type_3D2DB8 (32 bytes): its parent state, its code, its
// message handlers (8-byte entries sorted by their id, bsearch'd by
// sub_6EFD0), and its index and entry offset.
// A function of a state (4 bytes): its id and code offset, sorted by id.
struct type_3D2DB8_6C_08
{
    RwUInt16 unk_00;
    RwUInt16 unk_02;
};

struct type_3D2DB8_6C
{
    type_3D2DB8_6C *unk_00;     // its parent state
    RwInt32 *unk_04;            // its code
    type_3D2DB8_6C_08 *unk_08;  // its functions
    struct type_6B9A0_08 *unk_0C;   // its message handlers
    RwInt16 unk_10;             // its index
    RwInt16 unk_12;             // its entry's code offset (-1 for none)
    RwInt16 unk_14;             // its exit code offset (-1 for none)
    RwInt16 unk_16;             // where its arguments go in the locals
    RwUInt8 unk_18[0x2];
    RwUInt8 unk_1A;             // its function count
    RwUInt8 unk_1B;             // its handler count
    RwUInt8 unk_1C;             // its argument count
    RwUInt8 unk_1D[0x3];
};

// A handle held by a type_3D2DB8 (its task links): assigned by value, so
// the value is copied first (sub_6ED50).
struct type_3D2DB8_h
{
    union
    {
        RwUInt32 unk_00;
        type_439E78_00 unk_00_h;
    };

    void operator=(RwUInt32 arg_0)
    {
        unk_00 = arg_0;
    }
    void operator=(type_439E78_00 arg_0)
    {
        unk_00_h = arg_0;
    }
    // An inline accessor, as type_3D2C88::get_unk_04_h (sub_6EDB0).
    type_439E78_00 get_h()
    {
        return unk_00_h;
    }
};

// type_3D2DB8: a script task (constructor sub_6E9A0, destructor sub_6EAF0),
// named for its vtable: a state machine whose states are 32-byte records
// (unk_8C), with child tasks linked by handle (unk_84 the first, unk_80 the
// next, unk_88 the parent). Its stack and frame are the shared
// dword_4493F8 and dword_4493FC.
// The VMs' shared stack bounds (its inline accessors read them; defined below).
extern RwInt32 *dword_4493F8;
extern RwInt32 *dword_4493FC;

struct type_3D2DB8 : type_3D2C88
{
    // Inline: the constructor's vtable emits them after it, before ??_G (the image's order).
    virtual RwInt32 vf_028()
    {
        return unk_70;
    }
    virtual RwInt32 * vf_000()
    {
        return unk_68;
    }
    virtual RwInt32 * vf_004()
    {
        return dword_4493F8;
    }
    virtual RwInt32 * vf_008()
    {
        return dword_4493FC;
    }
    virtual void vf_01C(RwInt32 *arg_0)
    {
        dword_4493F8 = arg_0;
    }
    virtual void vf_020(RwInt32 *arg_0)
    {
        dword_4493FC = arg_0;
    }
    // +0x00C: its locals' start (sub_6FB40); +0x010: 0x20 (sub_6FCA0,
    // shared with type_3D2E20); +0x024: its object (sub_6FB90).
    virtual RwInt32 vf_00C();
    virtual RwInt32 vf_010();
    virtual type_3D2E7C *vf_024();
    // +0x028: unk_70 (sub_6EA30, which type_3D2C30's +0x008 shares).
    // +0x048
    virtual ~type_3D2DB8();
    // +0x04C: resets it for the script arg_0 with arg_4 (sub_6EB10).
    virtual void vf_04C(RwInt32 arg_0, RwInt32 arg_4);
    // +0x050: stops it and its children (sub_6EB90).
    virtual void vf_050();

    RwInt32 unk_64;             // its script
    RwInt32 *unk_68;            // its code pointer
    struct type_3D2DB8_6C *unk_6C;  // its current state
    RwInt32 unk_70;             // -1 at first
    RwInt32 *unk_74;            // its locals (sub_71CE0)
    RwInt32 unk_78;             // their size
    union
    {
        RwUInt32 unk_7C;        // its object's handle
        type_439E78_00 unk_7C_h;
    };
    type_3D2DB8_h unk_80;       // the next child of its parent
    union
    {
        RwUInt32 unk_84;        // its first child
        type_439E78_00 unk_84_h;
    };
    type_3D2DB8_h unk_88;       // its parent
    struct type_3D2DB8_6C *unk_8C;  // its states
    RwInt16 unk_90;             // the current state's index
    RwInt16 unk_92;
    RwInt16 unk_94;
    RwUInt8 unk_96;             // its kind among its parent's children
    RwUInt8 unk_97;
    RwUInt32 unk_98;            // flags
    struct type_6B960 *unk_9C;  // its handlers' registrations

    type_3D2DB8();
    // The child of kind arg_0 (sub_6ECF0), adding one (sub_6ED50) and
    // unlinking one (sub_6EDB0).
    type_3D2DB8 *sub_6ECF0(RwInt32 arg_0);
    void sub_6ED50(type_3D2DB8 *arg_0);
    void sub_6EDB0(type_3D2DB8 *arg_0);
    // Points the shared stack and frame at their start (sub_6EEF0).
    void sub_6EEF0();
    // Only the widths are known.
    void sub_6F760(RwInt32 arg_0);
    // Starts it (sub_6EC60): its states arg_4, kind arg_8, arg_C bytes of
    // locals, object arg_10 and script arg_18, entering its first state
    // when arg_1C is set.
    void sub_6EC60(RwInt32 arg_0, type_3D2DB8_6C *arg_4, RwInt32 arg_8, RwInt32 arg_C,
                   type_3D2E7C *arg_10, RwInt32 arg_14, RwInt32 arg_18, RwInt32 arg_1C);
    // A new child of kind arg_4 running the script arg_0, replacing the old
    // one (sub_6EE50).
    type_3D2DB8 *sub_6EE50(RwInt32 arg_0, RwInt32 arg_4);
    // Enters its first state and runs its entry code (sub_6EF10).
    void sub_6EF10();
    // Delivers the message arg_0 through the registration arg_4 to the
    // handlers of its states, innermost first, then to its children
    // (sub_6EFD0).
    void sub_6EFD0(struct type_42E00 *arg_0, struct type_6B960 *arg_4);
    // Runs the handler the registration arg_4 found for the message arg_0,
    // with the message's value, sender, recipient and arguments on a fresh
    // stack (sub_6F110).
    void sub_6F110(struct type_42E00 *arg_0, struct type_6B960 *arg_4);
    // The function arg_0 of its states, innermost first (its entry in
    // *arg_4, its state's code in *arg_8), sub_6F290; calls it with the
    // arguments ending at arg_4 and restores its state (sub_6F340).
    bool sub_6F290(RwInt32 arg_0, type_3D2DB8_6C_08 **arg_4, RwInt32 **arg_8);
    bool sub_6F340(struct type_4492EC *arg_0, RwInt32 *arg_4);
    // Points the shared stack and frame at arg_0 (sub_6F460).
    void sub_6F460(RwInt32 *arg_0);
    // Makes the pending state change (unk_92) until none is left: leaves
    // and enters states (sub_6F490); sets it (sub_6F500).
    void sub_6F490();
    void sub_6F500(RwInt16 arg_0);
    // Whether the state arg_0 is a child of the current one (sub_6FB10);
    // leaves the states up to its parent, running their exit code
    // (sub_6FA30).
    bool sub_6FB10(RwInt32 arg_0);
    void sub_6FA30(RwInt32 arg_0);
    // Enters the state arg_0, leaving the states down to the common parent
    // and registering the new ones' handlers, and runs its entry code with
    // its arguments copied into the locals (sub_6F520).
    void sub_6F520(RwInt16 arg_0);
    // Registers the handlers of the state arg_0 (sub_6F690) and
    // unregisters those of the states from arg_0 (sub_6F760); links a
    // registration into its list, marking one it overrides (sub_6F7E0),
    // and unlinks one (sub_6F910).
    void sub_6F690(RwInt32 arg_0);
    void sub_6F7E0(struct type_6B960 *arg_0);
    void sub_6F910(struct type_6B960 *arg_0);
    // Sets its object (sub_6FBB0) and reads its object's unk_0C (sub_6FB50).
    void sub_6FBB0(type_3D2E7C *arg_0);
    RwInt32 sub_6FB50();
    // Pooled, as type_3D2CD0: its deleting destructor frees nothing.
    void operator delete(void *arg_0)
    {
    }
    // The placement pair the object manager builds it in its pool slot
    // with (sub_71870 to sub_71B90): operator new (sub_6CCF0, which returns
    // arg_4) and its operator delete, which the shared unwind funclet calls
    // and /OPT:ICF folded into the empty sub_19A750. Members, since the
    // class's own operator delete hides the global ones.
    static void *operator new(RwUInt32 arg_0, void *arg_4);
    static void operator delete(void *arg_0, void *arg_4);
    // vf_014, as the image's vtable has it (a trivial body, folded into
    // sub_21D720 with every other copy).
    virtual RwInt32 vf_014()
    {
        return unk_64;
    }
    // vf_018, as the image's vtable has it (a trivial body, folded into
    // sub_1A62D0 with every other copy).
    virtual void vf_018(RwInt32 *arg_0)
    {
        unk_68 = arg_0;
    }
    // vf_030, as the image's vtable has it (a trivial body, folded into
    // sub_6FCD0 with every other copy).
    virtual struct type_3D2DB8 *vf_030()
    {
        return this;
    }
};

extern RwInt32 *dword_4493F8;
extern RwInt32 *dword_4493FC;
extern RwInt32 unk_4498D0[1];
#ifdef CODFH_PLAIN
// (plain builds: the message argument stack, dword_4493F8, grows up from here; the image
// lets it run over the library statics that follow, a plain link puts the stack pointer itself
// there, so it gets room of its own)
extern RwInt32 unk_4498D4[0x400];
#else
extern RwInt32 unk_4498D4[1];
#endif
// sub_73470: detaches the task arg_0 from its scheduler; sub_71D50 frees
// the locals arg_0 (sub_71CE0 allocates them).
void sub_73470(type_3D2C88 *arg_0);
// sub_72990: the compiled script arg_0's header (its states, their count,
// its locals' count); sub_71A90: a new task.
struct type_72990
{
    RwInt32 unk_00;
    RwInt32 unk_04;             // its id (dword_449B0C's key)
    type_3D2DB8_6C *unk_08;     // its states
    RwUInt16 unk_0C;
    RwUInt16 unk_0E;            // its locals (words)
    RwUInt16 unk_10;            // its stack (words); also the count of
                                // unk_14's imports (sub_72920)
    RwUInt8 unk_12[0x2];
    struct type_72FC0 *unk_14;  // its imports
    RwInt32 unk_18;
};
type_72990 *sub_72990(RwInt32 arg_0);
type_3D2DB8 *sub_71A90();
void sub_71D50(RwInt32 *arg_0);
RwInt32 *sub_71CE0(RwInt32 arg_0);

// A call record of a type_3D2E20 (unk_118's list).
struct type_3D2E20_118
{
    struct type_6B960 *unk_00;  // its registration
    type_3D2E20_118 *unk_04;    // the next record
    RwInt32 *unk_08;            // where the call continues
    RwInt32 unk_0C;             // its id
    RwUInt8 unk_10;             // how often an interrupt may still run
    RwUInt8 unk_11[0x3];
    RwUInt32 unk_14_0 : 1;
    RwUInt32 unk_14_1 : 4;      // its kind (1 a call, 2 an interrupt)
    RwUInt32 unk_14_5 : 27;
};

// A task's thread (type_3D2E20::unk_114, sub_71CA0): its first task's and
// its current task's handles and a reference count.
struct type_3D2E20_114
{
    union
    {
        RwUInt32 unk_00;
        type_439E78_00 unk_00_h;
    };
    union
    {
        RwUInt32 unk_04;
        type_439E78_00 unk_04_h;
    };
    RwInt32 unk_08;
};

// type_3D2E20: a script task (constructor sub_6FBF0, destructor sub_6FD00),
// named for its vtable: a script host running a function (unk_108) with its
// stack in itself (unk_78), a child task (unk_100) and call records
// (unk_118). type_46120 is the flattened view the script VM reads.
struct type_3D2E20 : type_3D2C30
{
    // +0x00C: its stack's start (sub_6FC80); +0x010: 0x20 (sub_6FCA0);
    // +0x028: unk_110 (sub_6FCB0); +0x034: itself (sub_6FCD0, the shared
    // "return this").
    // Inline: the constructor's vtable emits them after it, before ??_G (the image's order).
    virtual RwInt32 vf_00C()
    {
        return (RwInt32)unk_78;
    }
    virtual RwInt32 vf_010()
    {
        return 0x20;
    }
    virtual RwInt32 vf_028()
    {
        return unk_110;
    }
    virtual type_3D2E20 * vf_034()
    {
        return this;
    }
    // +0x024: its object (sub_708D0).
    virtual type_3D2E7C *vf_024();
    virtual ~type_3D2E20();
    // +0x050: stops it (sub_6FD70); +0x054: resets it for the script arg_0
    // with arg_4 (sub_6FD20).
    virtual void vf_050();
    virtual void vf_054(RwInt32 arg_0, RwInt32 arg_4);

    RwInt32 unk_78[0x20];       // its stack
    type_3D2DB8_h unk_F8;       // its parent task
    type_3D2DB8_h unk_FC;       // the task it called
    type_3D2DB8_h unk_100;      // its child task
    union
    {
        RwUInt32 unk_104;       // its object's handle
        type_439E78_00 unk_104_h;
    };
    RwInt32 unk_108;            // its function
    bool unk_10C;               // whether it waits
    RwUInt8 unk_10D;
    RwUInt8 unk_10E[0x2];
    RwInt32 unk_110;            // -1 at first
    type_3D2E20_114 *unk_114;   // its thread
    type_3D2E20_118 *unk_118;   // its call records
    RwInt32 unk_11C;
    RwInt32 unk_120;

    type_3D2E20();
    // Frees its call records (sub_6FDB0).
    void sub_6FDB0();
    // Starts the function arg_0 (sub_6FE00): resets its stack and state
    // and ends its child (sub_6FE40, sub_6FEC0).
    void sub_6FE00(RwInt32 arg_0);
    void sub_6FE40();
    void sub_6FEC0();
    // Waits (sub_6FF00); waits on a call (kind 1, sub_6FF20) or an
    // interrupt (kind 2, sub_6FFD0) for the message arg_0 with the flags
    // arg_4 and arg_8, registering for it.
    void sub_6FF00();
    void sub_6FF20(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, bool arg_C);
    void sub_6FFD0(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, bool arg_C);
    // The current call's continuation (sub_70080) and id (sub_700A0).
    void sub_70080(RwInt32 *arg_0);
    RwInt32 sub_700A0();
    // A new call record of the kind arg_0 when arg_4, else the current one
    // (sub_700C0); pushes a new one (sub_70130); removes the interrupt
    // arg_0 (sub_70170, "RemoveInterrupt").
    type_3D2E20_118 *sub_700C0(RwInt32 arg_0, bool arg_4);
    type_3D2E20_118 *sub_70130();
    void sub_70170(RwInt32 arg_0);
    // Frees the record arg_0 (sub_70220), unregistering what it waits on
    // (sub_70290); drops its registration for the message arg_4, whether
    // none is left (sub_70420).
    void sub_70220(type_3D2E20_118 *arg_0);
    void sub_70290(type_3D2E20_118 *arg_0);
    RwInt32 sub_70420(type_3D2E20_118 *arg_0, struct type_42E00 *arg_4);
    // Readies it: its thread's current task (sub_70310); a new thread for it
    // (sub_70360); releases its thread (sub_703C0).
    void sub_70310();
    void sub_70360();
    void sub_703C0();
    // Whether it or a task below it is its thread's current task
    // (sub_704F0); the arguments are unused.
    RwInt32 sub_704F0(RwInt32 arg_0, RwInt32 arg_4);
    // Wakes it (sub_70590): unless it waits on a call and arg_0 is clear,
    // continues the call record arg_4 (an interrupt runs on the same
    // stack and returns) with the message arg_8's value, sender and
    // recipient on its frame.
    void sub_70590(bool arg_0, type_3D2E20_118 *arg_4, struct type_42E00 *arg_8);
    // Returns arg_0 to its parent task, or ends its thread (sub_70850).
    void sub_70850(RwInt32 arg_0);
    // Sets its object (sub_708F0).
    void sub_708F0(type_3D2E7C *arg_0);
    // Calls the task arg_0: as its child (arg_4), else as the task its
    // parent (or thread, arg_8) called, else at the end of its own call
    // chain (sub_70930); returns the task to run.
    type_3D2E20 *sub_70930(type_3D2E20 *arg_0, bool arg_4, bool arg_8);
    // Ends it and the tasks below it (sub_70AF0); unlinks it from its
    // parent (sub_70BA0); the task to resume after it (sub_70C40).
    void sub_70AF0();
    void sub_70BA0();
    type_3D2E20 *sub_70C40();
    // Inline accessors, with no address and so no database names, named for
    // the field. Evidence: sub_70930 copies its thread into the new task
    // through a by-value argument.
    void set_unk_114(type_3D2E20_114 *arg_0)
    {
        unk_114 = arg_0;
    }
    // Whether it is its thread's current task: an inline with no address
    // and so no database name, named for what it tests. Evidence: sub_704F0
    // tests each task's comparison as a bool return (movzx).
    bool is_current()
    {
        return unk_114->unk_04 == unk_04;
    }
    // Pooled: its deleting destructor frees nothing.
    void operator delete(void *arg_0)
    {
    }
    // The placement pair the object manager builds it in its pool slot
    // with (sub_71870 to sub_71B90): operator new (sub_6CCF0, which returns
    // arg_4) and its operator delete, which the shared unwind funclet calls
    // and /OPT:ICF folded into the empty sub_19A750. Members, since the
    // class's own operator delete hides the global ones.
    static void *operator new(RwUInt32 arg_0, void *arg_4);
    static void operator delete(void *arg_0, void *arg_4);
};
typedef RwChar type_3D2E20_size_check[sizeof(type_3D2E20) == 0x124 ? 1 : -1];

// sub_71820, sub_71850: a task call record from its pool, and back.
type_3D2E20_118 *sub_71820();
void sub_71850(type_3D2E20_118 *arg_0);
// dword_449404: the next interrupt id.
extern RwInt32 dword_449404;

// The next interrupt id: an inline with no address and so no database name.
// Evidence: type_3D2E20::sub_6FFD0 takes the id through a temporary after
// its own locals.
inline RwInt32 next_interrupt_id()
{
    return dword_449404++;
}
// sub_71970: frees the object arg_0 to its pool; sub_71770: a new object
// of the kind arg_0 (1 an entity's script object, 2 a state machine, 3 a
// task), and sub_717B0 frees one by its kind.
void sub_71970(type_3D2C88 *arg_0);
type_3D2C88 *sub_71770(RwInt32 arg_0);
void sub_717B0(type_3D2C88 *arg_0);
// sub_71990: a new entity script object; sub_71A60, sub_71B60, sub_71C60:
// destroy an entity script object, a state machine and a task
// (sub_67520 by their kind, 1 to 3).
type_3D2CD0 *sub_71990();
void sub_71A60(type_3D2CD0 *arg_0);
void sub_71B60(type_3D2DB8 *arg_0);
void sub_71C60(type_3D2E20 *arg_0);
// sub_71CA0, sub_71CC0: a task thread from its pool, and back.
type_3D2E20_114 *sub_71CA0();
void sub_71CC0(type_3D2E20_114 *arg_0);
// sub_72A30: the code of the function arg_0.
type_67620_74 *sub_72A30(RwInt32 arg_0);

#endif
