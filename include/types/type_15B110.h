/*
 * type_15B110: a vehicle's guns (type_3DBC78::unk_DFC), four 0xC0-byte
 * records built with the compiler's `eh vector constructor iterator'
 * (sub_15B150 and sub_15B1C0 per record) and a -1 after them. Its
 * constructor sub_15B110 and destructor sub_15B220 are in unit_15B110; the
 * vehicle's constructor (sub_14C930) builds and unwinds it.
 */
#ifndef TYPE_15B110_H
#define TYPE_15B110_H

#include "rw/ostypes.h"
#include "types/type_129_base.h"
#include "types/type_67260.h"
#include "types/vec4.h"

// A gun (0xC0 bytes): its projectile's model, its firing settings and
// state, its tag in the vehicle's clump at +0x38 (AIData::sub_1BAA0 reads
// the main gun's, sub_1BD50 the third's), and the projectile settings it
// hands sub_15F2C0. Its constructor and destructor are defined in the
// class; the guns' eh vector iterators take their out-of-line copies
// (sub_15B150, sub_15B1C0).
struct type_15B110_00
{
    type_129940 unk_00;     // its projectile's model (a clump; with none
                            // it fires bullets: the tank's vf_2A8)
    RwReal unk_0C;          // its projectile's speed
    RwInt32 unk_10;         // the particle systems it fires with
    RwInt32 unk_14;
    RwReal unk_18;          // the time since the magazine started (cleared
                            // when a full one starts); past unk_1C it
    RwReal unk_1C;          // is reloaded (sub_15B510)
    RwInt32 unk_20;         // its rounds (the tank's vf_2A4 needs some)
    RwInt32 unk_24;         // the projectile's damage (copied to unk_3C)
    RwInt32 unk_28;         // (copied to unk_90 by the main gun)
    RwReal unk_2C;          // its reload, ready once it reaches unk_30
    RwReal unk_30;          // (the tank's vf_2A4)
    RwInt32 unk_34;         // a full magazine
    RwInt32 unk_38;
    type_67260 unk_3C;      // the projectile's settings: its kind (3 with a
                            // model, else 0), its damage, the model last
                            // fired and, for the main gun, its weapon's
                            // shell settings (the tank's vf_300)
    RwReal unk_8C;
    union
    {
        RwReal unk_90;      // (the tank's main gun converts unk_28 into it;
        RwInt32 unk_90_i;   // the gimp vehicle's copies weapon data's unk_4B8)
    };
    RwReal unk_94;
    RwReal unk_98;
    RwInt32 unk_9C;
    RwInt32 unk_A0;
    RwReal unk_A4;
    RwReal unk_A8;
    RwInt32 unk_AC;
    RwInt32 unk_B0;
    RwInt32 unk_B4;
    RwReal unk_B8;
    RwInt32 unk_BC;

    type_15B110_00()
    {
    }
    ~type_15B110_00()
    {
    }
    // An inline accessor for its model, through a local of its own
    // (docs/toolchain.md): the tank's vf_2A8 tests and copies it through
    // temporaries of their own.
    RpClump *get_unk_08()
    {
        RpClump *r = unk_00.unk_08;
        return r;
    }
};
typedef RwChar type_15B110_00_size_check[sizeof(type_15B110_00) == 0xC0 ? 1 : -1];

struct type_15B110
{
    type_15B110_00 unk_00[4];
    RwInt32 unk_300;            // -1 when built

    type_15B110();
    ~type_15B110();
    // Takes the vehicle's model arg_0 (vf_2F8 passes its arguments on);
    // only the widths are known.
    void sub_15B2A0(struct type_3DF8D8 *arg_0, void *arg_4);
    // Their step by arg_0: reload and fire timers (the vehicle's
    // vf_03C).
    void sub_15B510(RwReal arg_0);
};
typedef RwChar type_15B110_size_check[sizeof(type_15B110) == 0x304 ? 1 : -1];

// A quad sub_15B730 makes from four corners: its matrix (the corners'
// centre), the corners in its plane, their UVs, and room for more.
struct type_15B730_00
{
    RwMatrix unk_00;
    RwV2d unk_40[4];
    RwV2d unk_60[4];
    RwUInt8 unk_80[0x40];
    RwUInt32 unk_C0;            // its decals' flags from bit 8
    RwUInt8 unk_C4[0xC];
};
// A list of such quads and its count.
struct type_15B730
{
    type_15B730_00 *unk_00;
    RwInt32 unk_04;
};

// A decal extra (a decal's unk_130): its link in the manager's list and its
// decal.
struct type_15BB60
{
    RwUInt8 unk_00[0x54];
    type_15BB60 *unk_54;
    struct type_15BCC0 *unk_58;
};

// A decal (0x150 bytes, the manager's pool): its matrix, its points (in its
// plane, in the world) and UVs, its colours, their count, flags (the low
// byte: 1 in use, 0x44 kept), its owner, its links and its quad.
struct type_15BCC0
{
    RwMatrix unk_00;
    RwV2d unk_40[5];
    RwV3d unk_68[5];
    RwV2d unk_A4[5];
    RwUInt8 unk_CC[0x4];
    type_140490 unk_D0[5];      // their colours (128 each; the 16-aligned local)
    RwInt32 unk_120;
    union
    {
        RwUInt32 unk_124;
        struct
        {
            RwInt32 unk_124_0 : 8;  // 1 in use, 0x44 kept
            RwUInt32 unk_124_8 : 24;
        };
    };
    struct type_4D5170 *unk_128;
    type_15BCC0 *unk_12C;
    type_15BB60 *unk_130;
    struct type_15B730_00 *unk_134;
    RwInt32 unk_138;
    RwInt32 unk_13C;
    RwInt32 unk_140;
    RwUInt8 unk_144[0xC];

    // Back to the manager's pool: out of its slots, its extra dropped, off
    // its owner's list.
    void sub_15BA00();
};
typedef RwChar type_15BCC0_size_check[sizeof(type_15BCC0) == 0x150 ? 1 : -1];

// dword_4D5170: an object only the dead part of type_4D51C0::sub_15B5D0
// builds (an identity matrix, what sub_15B730 makes of four corners, and a
// count) before its sub_15BC10; only its widths are known.
struct type_4D5170
{
    RwMatrix unk_00;
    type_15B730 *unk_40;
    type_15BCC0 *unk_44;    // its decals (through their unk_12C)

    void sub_15BC10();
};
extern type_4D5170 dword_4D5170;
// sub_15B730: one quad from the four corners arg_0.
type_15B730 *sub_15B730(RwV3d *arg_0);

#endif
