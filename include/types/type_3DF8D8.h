/*
 * type_3DF8D8: the base of the objects sub_198800 looks up by an 8-byte key
 * (in the map dword_4F2728), anchored at its vtable off_3DF8D8, which its
 * constructor sub_18F3C0 installs. The constructor copies the key into +0x04
 * and zeroes the words at +0x0C and +0x0E. Slot +0x008 gives the object's kind: 0 here
 * (sub_1E4CB0), 0x2C for type_3DFEEC (sub_196370), 0x2D for the object
 * behind off_3DFEC4 (sub_196190), 0x2E for the one behind off_3DFEB0
 * (sub_195F30), which derives from type_3DFEEC (its constructor sub_195F00
 * calls sub_1962D0). The 0x2C and 0x2D constructors both pass through the
 * intermediate class type_3DFED8.
 *
 * Slots follow type_3D3548's convention: vf_<byte offset>, `void ()` until
 * their signature is known.
 */
#ifndef TYPE_3DF8D8_H
#define TYPE_3DF8D8_H

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "rw/bamatrix.h"
#include "types/type_129_base.h"
#include "types/type_D48D0.h"

struct SplinePath;
struct type_F8350;

// The key's two dwords as the game's global keys hold them: plain data (the
// image has no initializers for the 59 keys in .bss, which a constructor
// would give them).
struct type_3DF8D8_04_data
{
    RwUInt32 unk_00;
    RwUInt32 unk_04;
};

// type_3DF8D8_04: the 8-byte key, two dwords, named after its place in
// type_3DF8D8. AIData keeps two (+0x13A0 and +0x1408); sub_198800 returns 0
// for a key whose halves are both 0.
struct type_3DF8D8_04 : type_3DF8D8_04_data
{
    // Inline: AIData's constructor zeroes both halves of its unk_13A0 and
    // unk_1408 through a `this` temporary, with no EH state.
    type_3DF8D8_04()
    {
        unk_00 = 0;
        unk_04 = 0;
    }
    // Inline: a key given its halves (the unreferenced keys of units
    // 0DC400 and 0E8800, whose initializers store the two constants).
    type_3DF8D8_04(RwUInt32 arg_0, RwUInt32 arg_4)
    {
        unk_00 = arg_0;
        unk_04 = arg_4;
    }
};

// type_3DF8E4: the kind-1 object (a variable), anchored at its vtable
// off_3DF8E4, which its constructor sub_18F880 installs after zeroing its
// value (unk_10).
// A reference to another object, its key at +4 (0xFF in the first dword
// when set up).
struct type_3DF8D8_ref
{
    RwInt32 unk_00;
    type_3DF8D8_04 unk_04;
};

typedef struct RwStream RwStream;
typedef struct RwTexDictionary RwTexDictionary;
// What a GodAsset's handler (vf_000) is given as it is read: its size (0x1C,
// only the header, when it is being registered) and what its clump's
// extension is handed (sub_FBC10); sub_19A8D0 and sub_19A830 keep models
// read before by it.
struct type_3DF8D8_ev
{
    RwInt32 unk_00;
    RwInt32 unk_04;             // the size one list reads instead (sub_1941C0)
    RwInt32 unk_08;
    type_3DF8D8_ref unk_0C;     // the object's reference (the model
                                // object's embedded objects, sub_190B20)
    void *unk_18;
};
typedef struct RpClump RpClump;
void *sub_19A8D0(type_3DF8D8_ev *arg_0, RwInt32 arg_4);
RpClump *sub_19A830(type_3DF8D8_ev *arg_0, RpClump *arg_4, RwInt32 arg_8);
// Hands a model's clump its extension's data (unit_0FB7A0).
void sub_FBC10(RpClump *arg_0, void *arg_4);

// The GodAsset base proper (0x10 bytes): its vtable off_3DF8D8 (three slots),
// its key and two words. Evidence: the kinds' constructors construct their
// own +0x10 parts before they install their vtables (a second base there,
// sub_18F940), so nothing of the base's lies past +0x10.
struct type_3DF8D8_base
{
    // Keeps the key arg_0 (sub_18F3C0); the destructor (sub_18F440) only
    // puts the vtable back.
    type_3DF8D8_base(const type_3DF8D8_04 &arg_0);
    ~type_3DF8D8_base();

    // Pooled: the manager builds each object in its pool slot (sub_199010)
    // with the placement pair: operator new (sub_6CCF0, which returns
    // arg_4) and an empty operator delete (folded into sub_19A750).
    static void *operator new(RwUInt32 arg_0, void *arg_4);
    static void operator delete(void *arg_0, void *arg_4);

    // Its handler: reads it from the stream arg_0 (arg_4's unk_08 the
    // event, 0x1C to register it); 1 here.
    virtual RwInt32 vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4);
    virtual void vf_004();
    // The object's kind (see above).
    virtual RwInt32 vf_008();

    type_3DF8D8_04 unk_04;
    RwInt16 unk_0C;         // zeroed by the constructor
    RwInt16 unk_0E;

    // A setter with no address and so no database name. Evidence: the
    // soldier definition's handler (sub_191450) passes each new object its
    // own unk_0C through a temporary of its own (the argument, widened).
    void set_unk_0C(RwInt32 arg_0)
    {
        unk_0C = arg_0;
    }
};

// type_3DF8D8: any GodAsset as the rest of the game views one, with the
// fields its kinds keep at +0x10 on.
struct type_3DF8D8 : type_3DF8D8_base
{
    // A point: AIData::sub_208F0 copies it into its leash centre (0 for
    // type_3DFED8, sub_1E4CB0).
    virtual RwV3d *vf_00C();
    // Another point: AIData::sub_1FF10 requires it and copies it into its
    // leash direction.
    virtual RwV3d *vf_010();

    union
    {
        RwUInt32 unk_10;    // flags for type_3DFEEC (0x80 tested by
                            // AIData::sub_20DA0 and sub_5B240); the 0x2D
                            // object's constructor stores an RwMatrix * here
        const RwChar *unk_10_name;  // a movie's file name (the movie
                                    // player's sub_E8910 and sub_E89E0)
        RwInt16 unk_10_w;           // a variable's value as a word and a
        RwUInt8 unk_10_b;           // byte (sub_18F8E0, sub_18F910)
        struct
        {
            RwUInt32 unk_10_0 : 1;  // "IsNamedEntityInTrigger" checks it
                                    // as a bitfield (and, push)
        };
    };
    RwInt32 unk_14;
    RwInt32 unk_18;
    RwInt32 unk_1C;

    // A localised string's text (type_3DFF18; "NULL - REPLACE ME" for none):
    // given a buffer arg_0, a copy with its first '#' replaced by the number
    // arg_4 ("SetCheckPointRegister" passes 0 and 0 for the string itself).
    const RwChar *sub_197550(RwChar *arg_0, RwInt32 arg_4);
    // The object its model names (VehicleTrigger's vf_020 requires one; a
    // FlakTrigger's must be of kind 3).
    type_3DF8D8 *sub_1954D0();
    // A model object's bounding box (sub_147080 bounds a vehicle's body
    // with it), or 0; only what it returns is known.
    struct RwBBox *sub_190A90();
    // The clump of the gun record arg_0's model object, or 0 (as
    // type_1917A0's sub_18F830, for a vehicle's data: the guns' set-up).
    struct RpClump *sub_18F830(struct type_14D2C0_0C *arg_0);
    // An inline accessor for unk_18, with no address and so no database
    // name; named for its field. Evidence: type_3D51C0's vf_234 passes it on
    // through a compiler temporary of its own.
    // A direct-return accessor for the value's word, with no address and so
    // no database name. Evidence: sub_18F8E0 keeps it in a word temporary
    // packed below its own local.
    RwInt16 get_unk_10_w()
    {
        return unk_10_w;
    }
    RwInt32 get_unk_18()
    {
        RwInt32 r = unk_18;
        return r;
    }
    // A value of the object's (the pickup settings' named object,
    // type_FB6E0::sub_FB760); only the width is known.
    RwInt32 sub_190A10();
};

// type_3DF8D8_3: the kind-3 object (a model) as type_3D32F8's set-up
// (sub_740B0) reads it; only its +0x44 (the entity's unk_290) and +0x54
// (sub_16E080's second argument) are known. The inline accessors have no
// addresses and so no database names; the set-up copies both through
// temporaries of their own.
struct type_3DF8D8_3 : type_3DF8D8
{
    RwUInt8 unk_20[0x24];
    RwInt32 unk_44;
    RwUInt8 unk_48[0xC];
    RwInt32 unk_54;

    RwInt32 get_unk_44()
    {
        RwInt32 r = unk_44;
        return r;
    }
    RwInt32 get_unk_54()
    {
        RwInt32 r = unk_54;
        return r;
    }
    // The same, returned directly (no local of its own): the gimp
    // vehicle's set-up (sub_17EA70) keeps the object in a temporary and
    // then the value in the inline's return slot.
    RwInt32 get_unk_54_direct()
    {
        return unk_54;
    }
};

// type_3DFED8: the class between type_3DF8D8 and the kind-0x2C and 0x2D
// objects, anchored at its vtable off_3DFED8, which their constructors
// (sub_1962D0, sub_196090) install before their own. Its vf_00C and later
// slots return 0 (sub_1E4CB0). AIData::sub_208F0 views any of the 0x2C to
// 0x2E objects as one.
struct type_3DFED8 : type_3DF8D8
{
};


// type_3DF8F0: the kind-7 object (a texture dictionary), anchored at its
// vtable off_3DF8F0, which its constructor sub_18F940 installs; its handler
// (sub_18F9E0) reads the dictionary and registers it (kind 6) under the key
// at +0x2C.
struct type_3DF8F0_10
{
    type_3DF8F0_10()
    {
        unk_10 = 0;
        unk_1C = 0;
        unk_14 = 0;
        unk_18 = -1;
    }

    RwInt32 unk_10;             // the arena its objects are read into
                                // (unk_0C 2; sub_2DAAF0)
    RwInt32 unk_14;             // what unk_1C is called with
    RwInt32 unk_18;
    RwInt32 unk_1C;             // told of each object made

    // Inlines with no addresses and so no database names, named for their
    // fields. Evidence: the model object's sub_190B20 copies unk_10 through
    // a temporary of its own each time and calls unk_1C through a `this`
    // temporary.
    RwInt32 get_unk_10()
    {
        RwInt32 r = unk_10;
        return r;
    }
    void call_unk_1C(type_3DF8D8_04 *arg_0, RwInt32 arg_4)
    {
        if (unk_1C)
            ((void (*)(RwInt32, type_3DF8D8_04 *, RwInt32))unk_1C)(unk_14, arg_0, arg_4);
    }
};
struct type_3DF8F0 : type_3DF8D8_base, type_3DF8F0_10
{
    RwInt32 unk_20;
    RwTexDictionary *unk_24;    // its dictionary
    type_3DF8D8_ref unk_28;     // the key it registers it under (kind 6)

    // An accessor with no address and so no database name. Evidence: the
    // model object's sub_190B20 copies the dictionary through a temporary of
    // its own each time.
    RwTexDictionary *get_unk_24()
    {
        RwTexDictionary *r = unk_24;
        return r;
    }

    type_3DF8F0(const type_3DF8D8_04 &arg_0);

    virtual RwInt32 vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4);
    virtual RwInt32 vf_008();
};

// type_3DF8FC: the kind-6 object (a model: a clump), anchored at its vtable
// off_3DF8FC, which its constructor sub_18FB70 installs. Its handler
// (sub_18FC80) reads the clump (or a clump data file) with its texture
// and UV animation dictionaries current and bounds its geometry; vf_004
// (sub_190070) lets it go.
struct type_3DF8FC : type_3DF8D8_base
{
    RwTexDictionary *unk_10;
    struct RtDict *unk_14;
    type_129940 unk_18;         // its clump
    RwBBox unk_24;
    RwInt32 unk_3C;             // unk_24 is set

    type_3DF8FC(const type_3DF8D8_04 &arg_0);

    virtual RwInt32 vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4);
    virtual void vf_004();
    virtual RwInt32 vf_008();

    // Its bounds, or 0 before they are set.
    RwBBox *sub_190040();
};

// type_3DF9A0: the kind-0x3A object (a UV animation dictionary), anchored at
// its vtable off_3DF9A0, which its constructor sub_1900B0 installs. Its
// handler (sub_190140) reads the dictionary and hands it to the texture
// dictionary (kind 7) under unk_14's key, or to the model (kind 6) under
// unk_20's; vf_004 (sub_1902D0) destroys it.
struct type_3DF9A0 : type_3DF8D8_base
{
    struct RtDict *unk_10;
    type_3DF8D8_ref unk_14;
    type_3DF8D8_ref unk_20;

    type_3DF9A0(const type_3DF8D8_04 &arg_0);

    // Setters with no addresses and so no database names. Evidence: the
    // model object's handler (sub_190640) stores each through a temporary
    // holding the dictionary (its `this`).
    void set_unk_14(const type_3DF8D8_ref &arg_0)
    {
        unk_14 = arg_0;
    }
    void set_unk_20(const type_3DF8D8_ref &arg_0)
    {
        unk_20 = arg_0;
    }

    virtual RwInt32 vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4);
    virtual void vf_004();
    virtual RwInt32 vf_008();
};

// type_3DF9AC: an object whose kind (unk_1C) is given to its constructor
// (sub_190300), anchored at its vtable off_3DF9AC; its handler (sub_190380)
// reads its reference and, for kind 8, registers what it names (kind 0x30,
// or kind 3 taking its unk_0C).
struct type_3DF9AC : type_3DF8D8_base
{
    type_3DF8D8_ref unk_10;
    RwInt32 unk_1C;

    type_3DF9AC(const type_3DF8D8_04 &arg_0, RwInt32 arg_4);

    virtual RwInt32 vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4);
    virtual RwInt32 vf_008();
};

// type_3DF9B8: the kind-9 object (a variable's registration), anchored at
// its vtable off_3DF9B8, which its constructor sub_190440 installs; its
// handler (sub_1904E0) registers the name it reads (sub_198900) with the
// callback and values sub_1904B0 sets.
struct type_3DF9B8 : type_3DF8D8_base
{
    type_3DF8D8_ref unk_10;
    RwInt32 unk_1C;             // the variable's kind
    void (*unk_20)(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8);
    RwInt32 unk_24;
    RwInt32 unk_28;

    type_3DF9B8(const type_3DF8D8_04 &arg_0);

    virtual RwInt32 vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4);
    virtual RwInt32 vf_008();

    void sub_1904B0(void (*arg_0)(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8), RwInt32 arg_4, RwInt32 arg_8);
};

// The kind in a reference's top five bits (its unk_00), through an inline
// with no address and so no database name. Evidence: sub_190900 shifts the
// mask it is given (0x1F) at run time, an inline's constant arguments not
// being folded, into three temporaries of its own.
inline RwUInt32 get_ref_kind(RwUInt32 arg_0, RwUInt32 arg_4)
{
    RwUInt32 v;
    RwUInt32 r;
    RwUInt32 m;

    r = arg_4 << 27;
    m = r & arg_0;
    v = m >> 27;
    return v;
}

// type_3DF9C4: the kind-3 object (a model object: its model, a second model,
// its texture dictionary and UV animation dictionary), anchored at its
// vtable off_3DF9C4, which its constructor sub_190540 installs after its
// +0x10 part (as type_3DF8F0's). Its handler (sub_190640) reads six typed
// references and keeps those it needs (sub_190900).
struct type_3DF9C4 : type_3DF8D8_base, type_3DF8F0_10
{
    type_3DF8D8_ref unk_20;     // its model (kind 6)
    type_3DF8D8_ref unk_2C;     // the second model (kind 6)
    type_3DF8D8_ref unk_38;     // its texture dictionary (kind 7)
    RwInt32 unk_44;
    type_3DF8D8_ref unk_48;     // its UV animation dictionary (kind 0x3A)
    RwInt32 unk_54;

    type_3DF9C4(const type_3DF8D8_04 &arg_0);

    virtual RwInt32 vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4);
    virtual void vf_004();
    virtual RwInt32 vf_008();

    type_3DF8D8_04 *sub_1908A0(RwInt32 arg_0);
    type_3DF8D8_ref *sub_190900(RwInt32 arg_0, type_3DF8D8_ref *arg_4, RwInt32 arg_8, RwInt32 arg_C,
                                RwUInt8 arg_10, type_3DF8D8_base **arg_14);
    struct RtDict *sub_1909C0();
    RpClump *sub_190A10();
    RpClump *sub_190A50();
    RwBBox *sub_190A90();
    RwInt32 sub_190B20(RwStream *arg_0, type_3DF8D8_ev *arg_4);
};

// The same with no result local (sub_191300 stores it straight into its
// own local).
inline RwUInt32 get_ref_kind_direct(RwUInt32 arg_0, RwUInt32 arg_4)
{
    RwUInt32 m;
    RwUInt32 v;

    v = arg_4 << 27;
    m = v & arg_0;
    return m >> 27;
}

// type_3DFA58: the kind-0x30 object, anchored at its vtable off_3DFA58, which
// its constructor sub_191230 installs; its handler (sub_191270) registers
// the model (kind 6) among the six references it reads.
struct type_3DFA58 : type_3DF8D8_base
{
    type_3DFA58(const type_3DF8D8_04 &arg_0);

    virtual RwInt32 vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4);
    virtual RwInt32 vf_008();

    type_3DF8D8_ref *sub_191300(RwInt32 arg_0, type_3DF8D8_ref *arg_4, RwInt32 arg_8, RwInt32 arg_C,
                                RwUInt8 arg_10, type_3DF8D8_base **arg_14);
};

// type_3DFA64: the kind-4 object (a soldier's definition, types/SoldierTrigger.h
// views it as type_1917A0), anchored at its vtable off_3DFA64, which its
// constructor sub_1913B0 installs. Its handler (sub_191450) reads eight typed
// references: its body, model and head records (each registering its model
// object, kind 8), four variables and a registration (kind 9).
struct type_3DFA64 : type_3DF8D8_base
{
    type_3DF8D8_ref unk_10;     // its body record
    type_3DF8D8_ref unk_1C;     // its model object
    type_3DF8D8_ref unk_28;     // its head record
    RwInt32 unk_34;
    RwInt32 unk_38;
    RwInt32 unk_3C;
    RwInt32 unk_40;
    RwInt32 unk_44;

    type_3DFA64(const type_3DF8D8_04 &arg_0);

    virtual RwInt32 vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4);
    virtual RwInt32 vf_008();
};

// type_3DFABC: the kind-5 object (a weapon's definition, which
// types/type_495F0.h views), anchored at its vtable off_3DFABC, which its
// constructor sub_191880 installs after its +0x10 part; its handler
// (sub_191950) keeps its model object and projectile object references
// (registering each, kind 3 or 0x30) and a variable (sub_191B30).
struct type_3DFABC : type_3DF8D8_base, type_3DF8F0_10
{
    type_3DF8D8_ref unk_20;
    type_3DF8D8_ref unk_2C;
    type_3DF8D8_ref unk_38;
    RwInt32 unk_44;

    type_3DFABC(const type_3DF8D8_04 &arg_0);

    virtual RwInt32 vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4);
    virtual RwInt32 vf_008();
};

// type_3DFAC8: the kind-0x1A object, anchored at its vtable off_3DFAC8, which
// its constructor sub_191BE0 installs; its handler (sub_191C30) keeps its
// model object reference and registers it (kind 3).
RwInt32 sub_191B30(type_3DF8D8 *arg_0, RwInt32 arg_4, void *arg_8);

struct type_3DFAC8 : type_3DF8D8_base
{
    type_3DF8D8_ref unk_10;

    type_3DFAC8(const type_3DF8D8_04 &arg_0);

    virtual RwInt32 vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4);
    virtual RwInt32 vf_008();
};

// type_3DFAD4: a loaded script file (kinds 10 to 13, given to its
// constructor sub_191D30), anchored at its vtable off_3DFAD4. Its handler
// (sub_191DA0) reads the file into a buffer of its own, relocates it
// (sub_72BA0) and registers it by its kind, keeping its id; vf_004
// (sub_191EA0) frees the buffer.
struct type_3DFAD4 : type_3DF8D8_base
{
    RwInt32 unk_10;             // its kind
    void *unk_14;               // the file
    RwInt32 unk_18;             // its id

    type_3DFAD4(const type_3DF8D8_04 &arg_0, RwInt32 arg_4);

    virtual RwInt32 vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4);
    virtual void vf_004();
    virtual RwInt32 vf_008();
};

// type_3DFAE0: the kind-0xF object (an animation set, sub_77E40), anchored at
// its vtable off_3DFAE0, which its constructor sub_191F50 installs.
struct type_3DFAE0 : type_3DF8D8_base
{
    struct type_77D30 *unk_10;

    type_3DFAE0(const type_3DF8D8_04 &arg_0);

    virtual RwInt32 vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4);
    virtual RwInt32 vf_008();
};

// type_3DFAEC: the performance lookup's GodAsset (dword_4B92FC), anchored at
// its vtable off_3DFAEC, which its constructor sub_191FC0 installs; its
// handler (sub_191FF0) makes and reads the lookup, vf_004 (sub_1920A0)
// deletes it.
struct type_3DFAEC : type_3DF8D8_base
{
    struct type_ED340 *unk_10;

    type_3DFAEC(const type_3DF8D8_04 &arg_0);

    virtual RwInt32 vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4);
    virtual void vf_004();
    virtual RwInt32 vf_008();
};

// type_3DFAF8: the kind-0 object anchored at its vtable off_3DFAF8, which its
// constructor sub_192110 installs; its handler (sub_192140) registers the
// keys it reads (kind 0xD).
struct type_3DFAF8 : type_3DF8D8_base
{
    type_3DFAF8(const type_3DF8D8_04 &arg_0);

    virtual RwInt32 vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4);
    virtual RwInt32 vf_008();
};

// type_3DFB04: the performance lookup dword_4B92D4's GodAsset, as
// type_3DFAEC is dword_4B92FC's (sub_1921F0, sub_192220, sub_1922D0).
struct type_3DFB04 : type_3DF8D8_base
{
    struct type_ECDA0 *unk_10;

    type_3DFB04(const type_3DF8D8_04 &arg_0);

    virtual RwInt32 vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4);
    virtual void vf_004();
    virtual RwInt32 vf_008();
};

// Kinds with no handler of their own (their vtables keep the base's
// vf_000), by their vtables; only their constructors are here.
struct type_3DFB10 : type_3DF8D8_base
{
    type_3DFB10(const type_3DF8D8_04 &arg_0);

    virtual RwInt32 vf_008();
};
struct type_3DFB1C : type_3DF8D8_base
{
    type_3DFB1C(const type_3DF8D8_04 &arg_0);

    virtual RwInt32 vf_008();
};
struct type_3DFB28 : type_3DF8D8_base
{
    type_3DFB28(const type_3DF8D8_04 &arg_0);

    virtual RwInt32 vf_008();
};
struct type_3DFB34 : type_3DF8D8_base
{
    type_3DFB34(const type_3DF8D8_04 &arg_0);

    virtual RwInt32 vf_008();
};
struct type_3DFB40 : type_3DF8D8_base
{
    type_3DFB40(const type_3DF8D8_04 &arg_0);

    virtual RwInt32 vf_008();
};

// type_3DFB4C: the scene lookup dword_4B9300's GodAsset, as type_3DFAEC is
// dword_4B92FC's (sub_192430, sub_192460, sub_192510).
struct type_3DFB4C : type_3DF8D8_base
{
    struct type_ED850 *unk_10;

    type_3DFB4C(const type_3DF8D8_04 &arg_0);

    virtual RwInt32 vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4);
    virtual void vf_004();
    virtual RwInt32 vf_008();
};

// type_3DFB6C: the base of the sound kinds (the music streams, types/
// musicplayer.h's type_44E8D8_248), anchored at its vtable off_3DFB6C, whose
// two further slots are pure: play (vf_00C) and a test (vf_010). Its
// constructor is inline (sub_192B20 installs its vtable and then its
// derived class's).
struct type_3DFB6C : type_3DF8D8_base
{
    type_3DFB6C(const type_3DF8D8_04 &arg_0)
        : type_3DF8D8_base(arg_0)
    {
    }

    virtual RwInt32 vf_00C(struct type_8A980 *arg_0, struct type_3D3548 *arg_4, RwInt32 arg_8, RwV3d *arg_C,
                           RwInt32 arg_10, RwInt32 arg_14) = 0;
    virtual bool vf_010(RwInt32 arg_0) = 0;
};

// Reference kinds: 0x23 and 0x24 (two typed references each), the one at
// off_3DFE38, and 0x26 (one reference whose key a sound list takes,
// sub_194510). Their handlers read the references (sub_194490, shared,
// /OPT:ICF, with the kind-1 variable's; 0x24's sub_1943F0 reads the size at
// +4 instead).
struct type_3DFE20 : type_3DF8D8_base
{
    type_3DF8D8_ref unk_10[2];

    type_3DFE20(const type_3DF8D8_04 &arg_0);

    virtual RwInt32 vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4);
    virtual RwInt32 vf_008();
};
struct type_3DFE2C : type_3DF8D8_base
{
    type_3DF8D8_ref unk_10[2];

    type_3DFE2C(const type_3DF8D8_04 &arg_0);

    virtual RwInt32 vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4);
    virtual RwInt32 vf_008();
};
struct type_3DFE38 : type_3DF8D8_base
{
    type_3DF8D8_ref unk_10[2];

    type_3DFE38(const type_3DF8D8_04 &arg_0);

    virtual RwInt32 vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4);
    virtual RwInt32 vf_008();
};
struct type_3DFE44 : type_3DF8D8_base
{
    type_3DF8D8_ref unk_10;

    type_3DFE44(const type_3DF8D8_04 &arg_0);

    virtual RwInt32 vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4);
    virtual RwInt32 vf_008();
};
RwInt32 sub_194510(type_3DFE44 *arg_0, RwInt32 arg_4, type_3DF8D8_04 *arg_8);

// type_3DFE70: the object anchored at its vtable off_3DFE70, which its
// constructor sub_1949C0 installs, with a 0x9C-byte block of its own.
// Its handler (sub_194AB0) fills it from 31 references: a kind-0x28 object,
// a model's key (kind 3, or 0x30 unless kept at 0), four references it
// registers (kind 8), 23 variables' values (kind 1, or through kind-9
// registrations) and a string (sub_195BA0).
struct type_3DFE70_10
{
    void *unk_00;               // the kind-0x28 object
    type_3DF8D8_04 unk_04;
    type_3DF8D8_ref unk_0C;
    type_3DF8D8_ref unk_18;
    type_3DF8D8_ref unk_24;
    type_3DF8D8_ref unk_30;
    RwInt32 unk_3C;
    RwInt32 unk_40;
    RwInt32 unk_44;
    RwInt32 unk_48;
    RwInt32 unk_4C;
    RwInt32 unk_50;
    RwInt32 unk_54;
    RwInt32 unk_58;
    RwInt32 unk_5C;
    RwInt32 unk_60;
    RwInt32 unk_64;
    RwInt32 unk_68;
    RwInt32 unk_6C;
    RwInt32 unk_70;
    RwInt32 unk_74;
    RwInt32 unk_78;
    RwInt32 unk_7C;
    RwInt32 unk_80;
    RwInt32 unk_84;
    RwInt32 unk_88;
    RwInt32 unk_8C;
    RwInt32 unk_90;
    RwInt32 unk_94;
    void *unk_98;
};
struct type_3DFE70 : type_3DF8D8_base
{
    type_3DFE70_10 *unk_10;

    type_3DFE70(const type_3DF8D8_04 &arg_0);

    virtual RwInt32 vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4);
    virtual void vf_004();
    virtual RwInt32 vf_008();
};
struct type_3DFE94;
RwInt32 sub_195BA0(type_3DFE94 *arg_0, RwInt32 arg_4, void *arg_8);

// type_3DFE7C: the kind-0x28 object, anchored at its vtable off_3DFE7C, which
// its constructor sub_1954F0 installs, with a 0x78-byte block of its own
// (its model's reference at +0: sub_1954D0 finds that sound... object).
struct type_3DFE7C_10
{
    RwInt32 unk_00;
    type_3DF8D8_04 unk_04;
    RwUInt8 unk_0C[0x6C];
};
struct type_3DFE7C : type_3DF8D8_base
{
    type_3DFE7C_10 *unk_10;

    type_3DFE7C(const type_3DF8D8_04 &arg_0);

    virtual RwInt32 vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4);
    virtual void vf_004();
    virtual RwInt32 vf_008();

    type_3DF8D8 *sub_1954D0();
};

// type_3DFE88: the performance sets' GodAsset (dword_4B9304), as type_3DFAEC is
// the performance lookup's (sub_195A20, sub_195A50, sub_195B00).
struct type_3DFE88 : type_3DF8D8_base
{
    struct type_4B9304 *unk_10;

    type_3DFE88(const type_3DF8D8_04 &arg_0);

    virtual RwInt32 vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4);
    virtual void vf_004();
    virtual RwInt32 vf_008();
};

// type_3DFE94: the kind-2 object (a string, unk_10), anchored at its vtable
// off_3DFE94, which its constructor sub_195CD0 installs; its handler
// (sub_195C50) reads the string. Its variable callbacks copy it
// (sub_195B70), duplicate it (sub_195BA0) or hash it upper-cased
// (sub_195C10).
struct type_3DFE94 : type_3DF8D8_base
{
    RwChar *unk_10;

    type_3DFE94(const type_3DF8D8_04 &arg_0);

    virtual RwInt32 vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4);
    virtual void vf_004();
    virtual RwInt32 vf_008();
    // +0xC: its string (the image's vtable has a fourth slot, the folded getter
    // sub_191D80).
    virtual RwChar *vf_00C();
};

// type_3DFEA4: the kind-0x2B object (a reference at +0x14), anchored at its
// vtable off_3DFEA4, which its constructor sub_195D10 installs.
struct type_3DFEA4 : type_3DF8D8_base
{
    RwInt32 unk_10;
    type_3DF8D8_ref unk_14;

    type_3DFEA4(const type_3DF8D8_04 &arg_0);

    virtual RwInt32 vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4);
    virtual RwInt32 vf_008();
};

// The bits of a reference's kind word under the mask arg_4 shifted by arg_8
// (and back by arg_C), through an inline as get_ref_kind's. Evidence: the
// kind-0x2E object's handler (sub_195F40) keeps `shl ecx, 0` and `shr edx,
// 0`, which only constant arguments give (a literal 0 shift is dropped); the
// shifts are unsigned (a signed one is copied into a temporary).
inline RwUInt32 get_ref_low(RwUInt32 arg_0, RwUInt32 arg_4, RwUInt32 arg_8, RwUInt32 arg_C)
{
    RwUInt32 v;
    RwUInt32 r;
    RwUInt32 m;

    r = arg_4 << arg_8;
    m = r & arg_0;
    v = m >> arg_C;
    return v;
}

// A trigger's direction (+0x80) and position (+0x90) as the kind-0x2C
// object reads them (vf_010, vf_00C).
struct type_3DFEEC_trig
{
    RwUInt8 unk_00[0x80];
    RwV3d unk_80;
    RwUInt8 unk_8C[0x4];
    RwV3d unk_90;
};
// What the kind-0x2C object keeps at +0x24 by its flags: an entity's handle
// (flag 2), a trigger at +0x08 (flag 1), or a path node (flag 0x10), as
// vf_00C (sub_196530) reads it.
struct type_3DFEEC_24
{
    void *unk_00;
    RwInt32 unk_04;
    type_3DFEEC_trig *unk_08;
};
// The AI objects as they are made (type_3DFED8, type_3DFEEC and the kind-0x2D
// object above view them as the rest of the game reads them): the class
// between the base and the kinds 0x2C and 0x2D (vtable off_3DFED8, its
// constructor inline), the kind-0x2C object (a point, sub_1962D0), the
// kind-0x2E object derived from it (sub_195F00) and the kind-0x2D object (a
// matrix, sub_196090).
struct type_3DFED8_obj : type_3DF8D8_base
{
    type_3DFED8_obj(const type_3DF8D8_04 &arg_0)
        : type_3DF8D8_base(arg_0)
    {
    }

    virtual RwV3d *vf_00C();
    virtual RwV3d *vf_010();
};
struct type_3DFEEC_obj : type_3DFED8_obj
{
    RwUInt32 unk_10;            // flags
    RwInt32 unk_14;
    type_3DF8D8_ref unk_18;
    type_3DFEEC_24 unk_24;
    RwInt32 unk_30;

    type_3DFEEC_obj(const type_3DF8D8_04 &arg_0);

    virtual RwInt32 vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4);
    virtual void vf_004();
    virtual RwInt32 vf_008();
    virtual RwV3d *vf_00C();
    virtual RwV3d *vf_010();
};

struct type_3DFEB0_obj : type_3DFEEC_obj
{
    type_3DFEB0_obj(const type_3DF8D8_04 &arg_0);

    virtual RwInt32 vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4);
    virtual void vf_004();
    virtual RwInt32 vf_008();
};
RwInt32 sub_196020(type_3DFEEC_obj *arg_0, RwInt32 arg_4, type_3DFEB0_obj *arg_8);
struct type_3DFEC4_obj : type_3DFED8_obj
{
    RwMatrix *unk_10;

    type_3DFEC4_obj(const type_3DF8D8_04 &arg_0);

    virtual RwInt32 vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4);
    virtual void vf_004();
    virtual RwInt32 vf_008();
    virtual RwV3d *vf_00C();
    virtual RwV3d *vf_010();
};
struct type_3DFE94;
RwInt32 sub_195EB0(type_3DF8D8 *arg_0, RwInt32 arg_4, type_3DF8D8_04 *arg_8);
RwInt32 sub_196480(struct type_3DFE94 *arg_0, RwInt32 arg_4, void *arg_8);

// type_3DFF00: the kind-0x2F object (a mounted weapon's animation record, as
// types/type_4E1B70.h's type_4E1B70_C8 views it), anchored at its vtable
// off_3DFF00, which its constructor sub_1968C0 installs; its handler
// (sub_196950) keeps its two model objects' references and three hashed
// names, and names the mounted weapon settings it belongs to (sub_196B70).
struct type_3DFF00 : type_3DF8D8_base
{
    RwInt32 unk_10;
    type_3DF8D8_ref unk_14;
    type_3DF8D8_ref unk_20;
    RwUInt32 unk_2C;
    RwUInt32 unk_30;
    RwUInt32 unk_34;

    type_3DFF00(const type_3DF8D8_04 &arg_0);

    virtual RwInt32 vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4);
    virtual RwInt32 vf_008();
};
RwInt32 sub_196B70(type_3DF8D8 *arg_0, RwInt32 arg_4, type_3DFF00 *arg_8);
// type_3DFF0C: the kind-0x31 object, anchored at its vtable off_3DFF0C, which
// its constructor sub_196C00 installs; its handler (sub_196C40) registers
// each reference it reads (kind 0x32).
struct type_3DFF0C : type_3DF8D8_base
{
    type_3DFF0C(const type_3DF8D8_04 &arg_0);

    virtual RwInt32 vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4);
    virtual RwInt32 vf_008();
};
// type_3DFF18: the kind-0x32 object, a localised string, anchored at its
// vtable off_3DFF18, which its constructor sub_196CD0 installs. Its handler
// (sub_196D30) keeps the one of its fifteen references whose language is
// the game's (sub_19B0A0); sub_1974B0 cuts it at its '}' and '{'.
struct type_3DFF18 : type_3DF8D8_base
{
    RwChar *unk_10;     // the string (type_3DF8D8's sub_197550 reads it)
    RwChar *unk_14;     // what follows its '{'
    RwChar *unk_18;     // what follows its '}'

    type_3DFF18(const type_3DF8D8_04 &arg_0);

    virtual RwInt32 vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4);
    virtual void vf_004();
    virtual RwInt32 vf_008();

    void sub_1974B0();
};
struct type_3DFE94;
RwInt32 sub_197520(type_3DFE94 *arg_0, type_3DFF18 *arg_4, void *arg_8);

// type_3DFF3C: the kind-0x33 object, the index-sound table's list, anchored
// at its vtable off_3DFF3C, which its constructor sub_197660 installs. Its
// handler (sub_1976C0) counts its references and registers each (kind 1)
// with sub_197760, which, once the last is in, builds dword_4E5E40 and asks
// for "Surfaces+Materials" (kind 0x34).
struct type_3DFF3C : type_3DF8D8_base
{
    RwInt32 unk_10;     // its references
    RwInt32 unk_14;     // the highest index they name
    RwInt32 unk_18;     // those registered so far

    type_3DFF3C(const type_3DF8D8_04 &arg_0);

    virtual RwInt32 vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4);
    virtual RwInt32 vf_008();
};
RwInt32 sub_197760(type_3DF8D8 *arg_0, type_3DFF3C *arg_4, RwInt32 arg_8);
// type_3DFF5C: the kind-0x34 object, anchored at its vtable off_3DFF5C, which
// its constructor sub_197880 installs; its handler (sub_1978C0) registers
// each reference it reads (kind 0x35).
struct type_3DFF5C : type_3DF8D8_base
{
    type_3DFF5C(const type_3DF8D8_04 &arg_0);

    virtual RwInt32 vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4);
    virtual RwInt32 vf_008();
};
// type_3DFF68: the kind-0x35 object, anchored at its vtable off_3DFF68, which
// its constructor sub_197950 installs; its handler (sub_197990) registers
// each reference it reads (kind 0x36).
struct type_3DFF68 : type_3DF8D8_base
{
    type_3DFF68(const type_3DF8D8_04 &arg_0);

    virtual RwInt32 vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4);
    virtual RwInt32 vf_008();
};
// type_3DFF74: the kind-0x36 object, an index sound, anchored at its vtable
// off_3DFF74, which its constructor sub_197A20 installs. Its handler
// (sub_197A90) has three variables fill its index and the entry's first two
// words, and a fourth (a real, truncated) its third; each (sub_197C80)
// writes the entry into dword_4E5E40.
struct type_3DFF74 : type_3DF8D8_base
{
    RwInt32 unk_10;     // its index in dword_4E5E40 (-1 for none yet)
    RwInt32 unk_14;
    RwInt32 unk_18;
    RwInt32 unk_1C;
    RwInt32 unk_20;     // variables in so far

    type_3DFF74(const type_3DF8D8_04 &arg_0);

    virtual RwInt32 vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4);
    virtual RwInt32 vf_008();
};
struct type_3DF8E4;
RwInt32 sub_197C80(type_3DF8E4 *arg_0, type_3DFF74 *arg_4, RwInt32 *arg_8);
// An entry of the kind-0x37 object's array: a variable's value (-1 until
// set) and a kind-0x39 object's key, set by the kind-0x38 objects.
struct type_3DFF80_e
{
    RwInt32 unk_00;
    type_3DF8D8_04 unk_04;

    type_3DFF80_e()
    {
        unk_00 = -1;
    }
};
// type_3DFF80: the kind-0x37 object, anchored at its vtable off_3DFF80, which
// its constructor sub_197D40 installs. Its handler (sub_197D90) stores its
// count of references through unk_10 and a new array of that many entries
// through unk_14, and points each reference's kind-0x38 object at one.
struct type_3DFF80 : type_3DF8D8_base
{
    RwInt32 *unk_10;
    type_3DFF80_e **unk_14;

    type_3DFF80(const type_3DF8D8_04 &arg_0);

    virtual RwInt32 vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4);
    virtual RwInt32 vf_008();
};
// type_3DFF8C: the kind-0x38 object, anchored at its vtable off_3DFF8C, which
// its constructor sub_197ED0 installs; its handler (sub_197F10) fills its
// entry from a variable (sub_18F8B0) and a kind-0x39 object (sub_198070).
struct type_3DFF8C : type_3DF8D8_base
{
    type_3DFF80_e *unk_10;

    type_3DFF8C(const type_3DF8D8_04 &arg_0);

    virtual RwInt32 vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4);
    virtual RwInt32 vf_008();
};
RwInt32 sub_198070(type_3DF8D8_base *arg_0, type_3DFF8C *arg_4, RwInt32 arg_8);
// type_3DFF98: the kind-0x39 object, a list of variables' values, anchored at
// its vtable off_3DFF98, which its constructor sub_1980A0 installs; its
// handler (sub_1980F0) has each variable (sub_18F8B0) fill one of unk_14's.
struct type_3DFF98 : type_3DF8D8_base
{
    RwInt32 unk_10;     // the count
    RwInt32 *unk_14;    // the values

    type_3DFF98(const type_3DF8D8_04 &arg_0);

    virtual RwInt32 vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4);
    virtual void vf_004();
    virtual RwInt32 vf_008();
};
// type_3DFFA4: the kind-0x3B object, a string, anchored at its vtable
// off_3DFFA4, which its constructor sub_198210 installs; its handler
// (sub_198250) takes a buffer from the sounds' name pool (sub_1986B0) and
// has its string variables copy into it (sub_195B70); vf_004 gives it back.
struct type_3DFFA4 : type_3DF8D8_base
{
    RwChar *unk_10;

    type_3DFFA4(const type_3DF8D8_04 &arg_0);

    virtual RwInt32 vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4);
    virtual void vf_004();
    virtual RwInt32 vf_008();
};

struct type_3DF8E4 : type_3DF8D8_base
{
    RwInt32 unk_10;             // its value

    type_3DF8E4(const type_3DF8D8_04 &arg_0);

    virtual RwInt32 vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4);
    virtual RwInt32 vf_008();
};

// type_3DFEEC: the kind-0x2C object, anchored at its vtable off_3DFEEC, which
// its constructor sub_1962D0 installs; it zeroes +0x10, +0x14 and +0x1C to
// +0x30. The kind-0x2E object derives from it.
struct type_3DFEEC : type_3DFED8
{
    RwInt32 unk_20;
    // +0x24 holds one of two things, by the flags unk_10: under 0x80 a
    // spline (sub_5B240 and AIData::sub_20DA0 follow it), under 2 the id of
    // an entity (AIData::sub_1FF10 assigns it to a handle).
    union
    {
        SplinePath *unk_24;
        RwInt32 unk_24_id;
        type_F8350 *unk_24_node;    // a cover node ("SetCoverPointFromName")
    };
    RwInt32 unk_28;
    // +0x2C: under flag 1 of unk_10, a trigger ("GetEntityFromName" takes
    // its type_3D2E7C from it with sub_BDF50).
    union
    {
        RwInt32 unk_2C;
        class type_712B0 *unk_2C_trigger;
    };
    RwInt32 unk_30;

    // An inline accessor for unk_24, with no address and so no database
    // name; named for its field. Evidence for its shape: AIData::sub_20DA0
    // loads +0x24 into a compiler temporary just above `this` and copies it
    // from there, which is what an inline function holding its result in a
    // local expands to (docs/toolchain.md).
    SplinePath *get_unk_24()
    {
        SplinePath *r = unk_24;
        return r;
    }

    // An inline accessor for the node unk_24 holds, with no address and so
    // no database name; named for the field. Evidence: "SetCoverPointFromName"
    // reads it through a compiler temporary at every use.
    type_F8350 *get_unk_24_node()
    {
        return unk_24_node;
    }
};

// type_5E730: a stream alias (kind 0x2A), as "PrimeAudioStream" (sub_5E730)
// reads it, named after that command.
struct type_5E730 : type_3DF8D8
{
    RwInt32 unk_20;         // its voice type (0 to 2)
};

#endif
