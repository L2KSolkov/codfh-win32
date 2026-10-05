/*
 * The objectives (unit_16FF90): the level script's objective records
 * (dword_4E56A0, fifteen of 0x58 bytes, linked in a list by a byte index at
 * +0x54 from byte_4E564D), the level script trigger that owns them
 * (dword_4E5690, dword_4E5650 set while one is registered) and the markers
 * (dword_4E5654). Scripts add and remove objectives by key, set and clear
 * their flags, their messages and their targets; the HUD draws them
 * (type_DC400::sub_E4030).
 */
#ifndef GAME_OBJECTIVES_H
#define GAME_OBJECTIVES_H

#include <vector>

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "types/type_3DF8D8.h"
#include "types/type_D48D0.h"
#include "types/type_129_base.h"
#include "types/SplinePath.h"

struct type_6B960;

// An objective record's object: only its position is known.
struct type_4E56A0_34
{
    RwUInt8 unk_00[0x90];
    RwV3d unk_90;
};

struct type_4E56A0
{
    type_3DF8D8 *unk_00;        // the objective's object (sub_198800 of its
                                // key)
    RwUInt32 unk_04;            // flags: 1 in use, 0x20 with unk_08, 0x100
                                // shows its pointer at full length, 2 and
                                // 0x80 pick its radar icon, 4 hides it
                                // (sub_E4030)
    RwInt8 unk_08;
    RwUInt8 unk_09[0x3];
    RwReal unk_0C;              // its nag timer (60 at first) and its
    RwReal unk_10;              // reload
    RwInt32 unk_14;
    type_6B960 *unk_18;         // its messages: activate, complete, fail,
    type_6B960 *unk_1C;         // counter up and counter down (freed by
    type_6B960 *unk_20;         // sub_6BC40)
    type_6B960 *unk_24;
    type_6B960 *unk_28;
    type_144940 unk_2C;         // its target object (unk_40 0)
    type_D48D0 unk_38;          // its target entity (unk_40 1)
    SplinePath *unk_3C;         // the path to it, when it has one
    RwInt32 unk_40;             // what it marks: 0, 1 or none (-1)
    RwReal unk_44;              // its pulse (sub_1712C0)
    RwReal unk_48;              // the squared step along unk_3C (-1 unset)
    RwReal unk_4C;              // the parameter step for it (-1 unset)
    RwReal unk_50;              // the step's adjustment
    RwInt8 unk_54;              // the next record's index (-1 none)
    RwUInt8 unk_55[0x3];
};
typedef RwChar type_4E56A0_size_check[sizeof(type_4E56A0) == 0x58 ? 1 : -1];

// An inline accessor with no address and so no database name, named for
// the field it reads. Evidence: the radar (type_DC400::sub_E4030) passes
// the object through a slot of its own.
inline RwV3d *get_unk_90(type_4E56A0_34 *arg_0)
{
    type_4E56A0_34 *r = arg_0;

    return &r->unk_90;
}

extern type_4E56A0 dword_4E56A0[15];
extern type_144940 dword_4E5690;
extern RwInt32 dword_4E5650;
extern RwInt8 byte_4E564D;
extern RwInt8 byte_4E564C;
// The markers (sub_171340 and the rest).
extern type_D48D0 dword_4E5654[15];

void sub_16FF90();
void sub_16FFF0();
void sub_1701B0();
void sub_1702F0();
void sub_170310(RwReal arg_0);

// The objectives text object's key (sub_170DF0 shows its name).
struct type_3DF8D8_04_data;
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &dword_4B913C;
#else
extern type_3DF8D8_04_data dword_4B913C;
#endif

// A message as the objectives' handlers see it: its registration's kind at
// +4 of its first field.
struct type_170DF0_00
{
    RwInt32 unk_00;
    RwInt32 unk_04;
};
struct type_170DF0
{
    type_170DF0_00 *unk_00;
};
RwInt32 sub_170DF0(RwInt32 arg_0, type_170DF0 *arg_4);
RwInt32 sub_170EE0(RwInt32 arg_0, type_170DF0 *arg_4);
void sub_171480(type_3DF8D8_04 *arg_0, RwInt32 arg_4);
struct type_3DF8D8_04;
RwInt32 sub_170FD0(type_3DF8D8_04 *arg_0, RwReal arg_4);
// Elsewhere: a handler that only returns (the counter messages').
RwInt32 sub_31DB0();

// The objective records sub_1708B0 walks, in order.
void sub_1708E0(std::vector<RwInt32> *arg_0);
// The size (*arg_4) and alpha (*arg_8) of record arg_0's pulse; 0 when it
// has none.
RwInt32 sub_1712C0(type_4E56A0 *arg_0, RwReal *arg_4, RwReal *arg_8);
// The position of marker arg_0 (0 to 14), or 0 when it has none.
RwV3d *sub_171340(RwInt32 arg_0);
// Record arg_0 of the list (0 for -1 or while the list is off).
type_4E56A0 *sub_1708B0(RwInt8 arg_0);
// The index after record arg_0's.
RwInt8 sub_170890(RwInt8 arg_0);

#endif
