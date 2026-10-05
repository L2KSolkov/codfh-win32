/*
 * type_4E5D30: the 0x44-byte entries of the four-entry table dword_4E5D30,
 * named after that table (its first instance). Each holds a collision world
 * at +0x28 that AIData::sub_2CE90 and sub_92430 query while the entry is live
 * (+0x00 nonzero), and the worlds the main render draws (unit_125490).
 */
#ifndef TYPE_4E5D30_H
#define TYPE_4E5D30_H

#include "rw/ostypes.h"
#include "rw/rpcollis.h"

typedef struct RwTexDictionary RwTexDictionary;

// A section's arena: its base, the bytes used and its size.
struct type_4E5D30_10
{
    RwUInt32 unk_00;
    RwInt32 unk_04;
    RwInt32 unk_08;

    // Inline: no address, so no database name; named for its field. The
    // world manager's sub_173CE0 reads it through a local of its own.
    RwInt32 get_unk_04()
    {
        RwInt32 r = unk_04;
        return r;
    }
};

struct type_4E5D30
{
    RwInt32 unk_00;         // nonzero while the entry is live
    RwInt32 unk_04;         // cleared when a section loads (sub_D7F70, sub_142F70)
    RwUInt16 unk_08;        // the level section it holds
                            // ("IsLevelSectionLoaded")
    RwUInt16 unk_0A;        // its slot's own index (sub_D8660 skips it)
    RwInt32 unk_0C;
    type_4E5D30_10 unk_10;  // its arena (the world manager's sub_172820)
    RwInt32 unk_1C;
    RpWorld *unk_20;        // its world drawn opaque (the main render,
                            // sub_1254D0)
    RpWorld *unk_24;        // its world drawn in the second pass
    RpWorld *unk_28;        // the entry's collision world
    RpWorld *unk_2C;        // its world with animated UVs
    RwTexDictionary *unk_30;    // its texture dictionary (the world
                                // manager's sub_1742D0)
    RwUInt32 unk_34;        // the flags sub_1267D0 and sub_126930 test
    RwUInt32 unk_38;        // for unk_20, unk_24 and unk_28 (its
    RwUInt32 unk_3C;        // prelit and lit bits)
    RwUInt32 unk_40;        // and unk_2C's (the world manager's sub_173CE0
                            // copies each world's flags in)

    // Empty, out of line: folded (/OPT:ICF) into pDtor (0x1E41C0); the
    // exit functions of dword_4E5D30 and unk_4E5CD8 call it.
    ~type_4E5D30();

    // Inline accessors for unk_00 and unk_28, with no address and so no
    // database names; named for their fields. Evidence for their shape:
    // AIData::sub_2CE90 reads each through its own compiler temporary
    // (three in a row, the world twice), which is what inline functions
    // holding their result in a local expand to (docs/toolchain.md).
    RwInt32 get_unk_00()
    {
        RwInt32 r = unk_00;
        return r;
    }
    // An inline accessor for unk_08, likewise nameless, but with no result
    // local: "IsLevelSectionLoaded" (sub_4B770) compares it through a word
    // temporary packed two bytes under a dword one, where a local would
    // take a slot of its own.
    // Likewise for unk_04 (through a local of its own), and a setter for
    // unk_08 (through a two-byte parameter slot): the section trigger's
    // entry (sub_145060) reads and sets them so.
    RwInt32 get_unk_04()
    {
        RwInt32 r = unk_04;
        return r;
    }
    void set_unk_08(RwUInt16 arg_0)
    {
        unk_08 = arg_0;
    }
    RwUInt16 get_unk_08()
    {
        return unk_08;
    }
    // Likewise for unk_0A (the section streaming, sub_D8660).
    RwUInt16 get_unk_0A()
    {
        return unk_0A;
    }
    RpWorld *get_unk_28()
    {
        RpWorld *r = unk_28;
        return r;
    }
    // A constructor (0x1746E0; the initializers at 0x30BE00 and 0x30BE30
    // run it for dword_4E5D30 and unk_4E5CD8). Their destructor is empty,
    // folded by /OPT:ICF into pDtor (0x1E41C0); it is left undeclared.
    type_4E5D30();
    // Likewise for unk_20 (the world manager's sub_173750).
    RpWorld *get_unk_20()
    {
        RpWorld *r = unk_20;
        return r;
    }
    // Likewise for unk_1C (the world manager's sub_173CE0).
    RwInt32 get_unk_1C()
    {
        RwInt32 r = unk_1C;
        return r;
    }
    // Likewise for unk_24, unk_2C and unk_30 (the world manager's
    // sub_174060).
    RpWorld *get_unk_24()
    {
        RpWorld *r = unk_24;
        return r;
    }
    RpWorld *get_unk_2C()
    {
        RpWorld *r = unk_2C;
        return r;
    }
    RwTexDictionary *get_unk_30()
    {
        RwTexDictionary *r = unk_30;
        return r;
    }
    // Clears its worlds and flags (arg_0 unused), and with them its slot
    // and arena (sub_174790); sub_1747D0 warns of what is still held at
    // shutdown (unit_171DC0).
    void sub_174700(RwInt32 arg_0);
    void sub_174790();
    void sub_1747D0();
};
typedef RwChar type_4E5D30_size_check[sizeof(type_4E5D30) == 0x44 ? 1 : -1];

#endif
