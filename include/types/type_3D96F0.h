/*
 * type_3D96F0: the game's extension of a RenderWare object (0x1C bytes),
 * anchored at its vtable off_3D96F0: the plugins of src/recovered/
 * unit_0FB7A0.cpp build one in the atomic's (0x42B0), clump's (0x42B1) and
 * frame's (0x42B2) plugin data, and the derived type_3D96FC and type_3D9718
 * in a light's (0x42B3) and world's (0x42B5). It ties the object to an
 * entity (by handle, unk_14) and keeps a list of nodes (unk_18).
 */
#ifndef TYPE_3D96F0_H
#define TYPE_3D96F0_H

#include "rw/ostypes.h"
#include "rw/rpatomic.h"
#include "types/type_D48D0.h"

struct type_3D3548;

// The extension's entity handle: type_D48D0's layout and methods without
// its destructor. Evidence: the plugins expand the extension's constructor
// inline (sub_FB800), which VC7.1 never does while a member has a
// destructor; sub_D4910 is type_D48D0's (config/aliases.txt).
struct type_3D96F0_14
{
    union
    {
        RwInt32 unk_00;
        type_3D3548_384 unk_00_h;
    };

    type_3D96F0_14()
    {
        unk_00 = 0;
    }
    void operator=(RwInt32 arg_0)
    {
        unk_00 = arg_0;
    }
    type_3D3548 *sub_D4910();
    // Sets the handle arg_0 (passed by value): an inline with no address,
    // named for what it does. Evidence: the set-entity functions (sub_FB910
    // and its three siblings) copy the entity's handle through a slot of its
    // own after the getter's.
    void set_h(type_3D3548_384 arg_0)
    {
        unk_00_h = arg_0;
    }
};

// An extension's flags (bit 3: collision skips it; sub_FB9C0), a byte kept
// in a dword: the plugins copy it whole, and read back its byte.
struct type_3D96F0_04
{
    union
    {
        struct
        {
            RwUInt8 unk_00;
            RwUInt8 unk_01[0x3];
        };
        struct
        {
            RwUInt32 unk_00_0 : 1;
            RwUInt32 unk_00_1 : 1;  // in the section's alpha world and
            RwUInt32 unk_00_2 : 1;  // collision world (the world manager's
            RwUInt32 unk_00_3 : 1;  // sub_172C60)
        };
    };
};

// A node of an extension's list (12 bytes).
struct type_3D96F0_node
{
    type_3D96F0_node *unk_00;
    type_3D96F0_node *unk_04;
    RwInt32 unk_08;
};

struct type_3D96F0
{
    // +0x000: sets it up; +0x004: copies arg_0's; +0x008: takes it down for
    // the object arg_0.
    virtual void vf_000();
    virtual void vf_004(type_3D96F0 *arg_0);
    virtual void vf_008(void *arg_0);

    // Its constructor is implicit (the plugins' constructors expand it);
    // its destructor is out of line (sub_FB8F0).
    ~type_3D96F0();
    // Its placement new (sub_6CCF0) and its delete, empty (folded by
    // /OPT:ICF into sub_19A750).
    static void *operator new(RwUInt32 arg_0, void *arg_4);
    static void operator delete(void *arg_0);
    static void operator delete(void *arg_0, void *arg_4);

    // Links and unlinks the node arg_0.
    void sub_FC360(type_3D96F0_node *arg_0);
    void sub_FC3B0(type_3D96F0_node *arg_0);
    // unk_08 as a word (0xFF: 0xFFFF, 0x7F: 0x7FFF), and set from one.
    RwUInt16 sub_FC440();
    void sub_FC490(RwUInt16 arg_0);

    type_3D96F0_04 unk_04;      // the flags
    RwUInt8 unk_08;
    RwUInt8 unk_09;
    RwUInt16 unk_0A;
    void *unk_0C;
    RwInt32 unk_10;
    type_3D96F0_14 unk_14;      // the entity
    type_3D96F0_node *unk_18;   // its holders (unit_129430)

    // unk_18 through a result temporary: an inline with no address, named
    // for its field. Evidence: each holder's release (sub_1294D0 and the
    // others) tests it through a temporary of its own.
    type_3D96F0_node *get_unk_18()
    {
        return unk_18;
    }
    // unk_0A likewise (the world manager's sub_172F60 compares two worlds'
    // through word temporaries).
    RwUInt16 get_unk_0A()
    {
        return unk_0A;
    }
};
typedef RwChar type_3D96F0_size_check[sizeof(type_3D96F0) == 0x1C ? 1 : -1];

// A light's extension (0x24 bytes).
struct type_3D96FC : type_3D96F0
{
    // Inline (the plugin's constructor expands it); left implicit, VC7.1
    // calls it out of line.
    type_3D96FC()
    {
    }

    virtual void vf_000();
    virtual void vf_008(void *arg_0);
    virtual void vf_00C(type_3D96FC *arg_0);

    RpLight *unk_1C;            // the world manager's list of the level's
    RpLight *unk_20;            // lights: the next and the previous
                                // (sub_173800, sub_1738D0)

    // unk_1C and unk_20 through result locals: inlines with no address,
    // named for their fields. Evidence: the list's unlink (sub_1738D0)
    // copies each through a temporary of its own before storing it.
    RpLight *get_unk_1C()
    {
        RpLight *r = unk_1C;
        return r;
    }
    RpLight *get_unk_20()
    {
        RpLight *r = unk_20;
        return r;
    }
};
typedef RwChar type_3D96FC_size_check[sizeof(type_3D96FC) == 0x24 ? 1 : -1];

// A world's extension (0x20 bytes, then a word the plugin sets while it is
// built).
struct type_3D9718 : type_3D96F0
{
    // Inline (the plugin's constructor expands it); left implicit, VC7.1
    // calls it out of line.
    type_3D9718()
    {
    }

    virtual void vf_000();
    virtual void vf_008(void *arg_0);
    virtual void vf_00C(type_3D9718 *arg_0);

    RwInt32 unk_1C;

    // unk_1C through a result temporary: an inline with no address, named
    // for its field. Evidence: the main render (sub_1254D0) reads a world's
    // unk_1C into a temporary of its own before passing it on.
    RwInt32 get_unk_1C()
    {
        return unk_1C;
    }
};
typedef RwChar type_3D9718_size_check[sizeof(type_3D9718) == 0x20 ? 1 : -1];

// A world's extension (sub_FC4E0) and a light's (sub_FBDD0, returned as the
// base; the main render follows a light list through type_3D96FC's unk_1C),
// both in unit_0FB7A0.
type_3D9718 *sub_FC4E0(void *arg_0);
type_3D96F0 *sub_FBDD0(void *arg_0);
// An atomic's, clump's and frame's extensions (sub_FB7A0, sub_FBA10,
// sub_FBC30), and the entity each is set to (0 for none; sub_FB910,
// sub_FBB60, sub_FBD80, sub_FBF20 for a light), unit_0FB7A0.
type_3D96F0 *sub_FB7A0(void *arg_0);
type_3D96F0 *sub_FBA10(void *arg_0);
void sub_FB910(RpAtomic *arg_0, struct type_3D3548 *arg_4);
void sub_FBB60(RpClump *arg_0, struct type_3D3548 *arg_4);
void sub_FBD80(RwFrame *arg_0, struct type_3D3548 *arg_4);
void sub_FBF20(RpLight *arg_0, struct type_3D3548 *arg_4);

// A material's extension (8 bytes), anchored at its vtable off_3D970C.
struct type_3D970C
{
    virtual void vf_000();
    virtual void vf_004(type_3D970C *arg_0);
    // Empty: folded (/OPT:ICF) into sub_15FB30.
    virtual void vf_008(void *arg_0);

    static void *operator new(RwUInt32 arg_0, void *arg_4);

    // The surface id (low word, 0xFFFF none) and flags (high word), as
    // streamed (a high word of 0xFFFF drops).
    RwUInt32 unk_04;
};
typedef RwChar type_3D970C_size_check[sizeof(type_3D970C) == 0x8 ? 1 : -1];

#endif
