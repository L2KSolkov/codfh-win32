/*
 * type_4E5E50: the camera's sway (unit_175FC0, unk_4E5E50, constructed by
 * the initializer at 0x30BEB0): three effects from the table dword_429EB8,
 * by the entries' kind: 0 a shake (unk_10, faded by the distance from the
 * render camera, with a pad rumble), 1 a sway (unk_3C, with a rumble) and
 * any other a steady drift (unk_68, left under a sway). Each runs two noises
 * (type_176040) on the view's pitch and yaw. The camera entity resets it in
 * its set-up (sub_176100) and has it turn the render camera's matrix each
 * frame (sub_1765E0); the weapon copies start effects 4 and 8 (sub_119050,
 * through sub_176180).
 */
#ifndef TYPE_4E5E50_H
#define TYPE_4E5E50_H

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "rw/bamatrix.h"
#include <stdlib.h>

// An effect of the table dword_429EB8 (32 bytes; the entry with id -1 ends
// it).
struct type_429EB8
{
    RwInt16 unk_00;             // its id (and priority: a lower one does
                                // not interrupt a higher one of its kind)
    RwInt16 unk_02;             // its kind (0 shake, 1 sway, other drift)
    RwReal unk_04;              // its time, in seconds
    RwReal unk_08;              // its noises' speed
    RwReal unk_0C;              // and size
    RwReal unk_10;              // a shake's distance scale
    RwInt32 unk_14;             // its rumble strength (0 for none)
    RwReal unk_18;              // the least time between two starts
    RwReal unk_1C;              // when it last started

    // Inline accessors for unk_08 and unk_0C, with no address and so no
    // database name; named for their fields. Evidence: sub_176470 copies
    // each through a temporary of its own.
    RwReal get_unk_08()
    {
        RwReal r = unk_08;
        return r;
    }
    RwReal get_unk_0C()
    {
        RwReal r = unk_0C;
        return r;
    }
    // Likewise for unk_14 (sub_176A10 converts it through the temporary).
    RwInt32 get_unk_14()
    {
        RwInt32 r = unk_14;
        return r;
    }
};
extern type_429EB8 dword_429EB8[];

// A noise (16 bytes): its seed, octaves, speed and size. Its constructor
// (sub_176040, run by the eh vector constructor iterator) is out of line;
// its destructor is empty, folded by /OPT:ICF into pDtor (0x1E41C0).
struct type_176040
{
    RwReal unk_00;
    RwInt32 unk_04;
    RwReal unk_08;
    RwReal unk_0C;

    type_176040();
    ~type_176040();
    // Its value now (unit_176B30).
    RwReal sub_176D70();
    // A new seed, two octaves, speed and size 1: an inline with no address
    // and so no database name, named for what it does. Evidence: sub_176470
    // expands it twice, the second time through a `this` temporary.
    void reset()
    {
        unk_00 = (RwReal)(rand() % 16384);
        unk_04 = 2;
        unk_08 = 1.0f;
        unk_0C = 1.0f;
    }
};

struct type_4E5E50
{
    RwReal unk_00;              // the shake's strength by its distance
    RwUInt32 unk_04;            // the frame last advanced (dword_4B87D8)
    RwReal unk_08;              // the sway's and
    RwReal unk_0C;              // the shake's phase speed (0: none)
    RwInt32 unk_10;             // the shake's effect (0: none)
    RwReal unk_14;              // its time left
    RwReal unk_18;              // its size
    type_176040 unk_1C[2];      // its noises
    RwInt32 unk_3C;             // the sway's effect (0: none)
    RwReal unk_40;              // its time left
    RwReal unk_44;              // its size
    type_176040 unk_48[2];      // its noises (the drift's too)
    RwInt32 unk_68;             // the drift's effect (0: none)
    RwReal unk_6C;              // its size
    RwMatrix unk_70;            // the turned matrix

    type_4E5E50();
    ~type_4E5E50();
    void sub_176100();
    void sub_176180(RwInt32 arg_0, RwV3d *arg_4, RwReal arg_8, RwReal arg_C);
    type_429EB8 *sub_176420(RwInt32 arg_0);
    type_429EB8 *sub_176470(RwInt32 arg_0, RwReal arg_4);
    RwMatrix *sub_1765E0(RwMatrix *arg_0);
    void sub_176A10();
    void sub_176A90();
    void sub_176AB0(type_176040 *arg_0, RwReal arg_4, RwReal arg_8, RwReal arg_C, RwV3d *arg_10,
                    RwInt32 arg_14);
};
typedef RwChar type_4E5E50_size_check[sizeof(type_4E5E50) == 0xB0 ? 1 : -1];
extern type_4E5E50 unk_4E5E50;
// Set while the rumble is off for the sway (.bss after it).
extern RwInt32 dword_4E5F00;
// The rumble's scales (.data): strength and length.
extern RwReal flt_42A038;
extern RwReal flt_42A03C;

#endif
