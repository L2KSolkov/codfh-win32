/*
 * The loaded script files (unit_072810): four alfahash tables of the
 * loaded files' contents, keyed by their ids, the files' relocation on
 * load (sub_72BA0, by the kind in their header) and the resolution of their
 * imports (sub_72FC0). The kinds' layouts are named for the functions that
 * look them up; each view holds only what those functions read.
 */
#ifndef TYPE_72810_H
#define TYPE_72810_H

#include "rw/ostypes.h"
#include "types/alfahash.h"
#include "types/type_67620.h"

struct type_72990;

// A loaded file's four-byte header: the version string's first bytes
// (sub_72B30 checks it), whether it has been relocated, and its kind (0 to
// 4, sub_72BA0).
struct type_72BA0
{
    RwChar unk_00[0x2];
    RwInt8 unk_02;
    RwInt8 unk_03;
};

// An import of a loaded file (12 bytes): an 8-byte name and its kind in
// the top four bits of unk_08 (the rest indexes dword_449308 for kind 0).
struct type_72FC0
{
    RwInt32 unk_00;
    RwInt32 unk_04;
    RwUInt32 unk_08;
};

// The 8-byte name sub_198900 registers (sub_73050 to sub_730D0 copy it
// from an import).
struct type_73050
{
    RwInt32 unk_00;
    RwInt32 unk_04;
};

// dword_449AD8's entries (sub_728C0, sub_72900): the id and the imports.
struct type_72900
{
    RwInt32 unk_00;
    RwInt32 unk_04;             // its id
    RwInt32 unk_08;
    RwInt32 unk_0C;
    RwUInt16 unk_10;
    RwUInt16 unk_12;            // its imports' count
    type_72FC0 *unk_14;         // its imports
    RwInt32 unk_18;
};

// dword_449AA4's entries, the functions (kind 4, sub_72F00): the id, the
// code and the imports.
struct type_72A30
{
    RwInt32 unk_00;
    RwInt32 unk_04;             // its id
    RwInt32 *unk_08;            // its code
    type_72FC0 *unk_0C;         // its imports
    RwInt16 unk_10;
    RwInt16 unk_12;             // its imports' count
};

// The tables (sub_72810 sets them up): by id, dword_449AD8 (sub_72900),
// dword_449AA4 (functions, sub_72A30) and dword_449B0C (state machines,
// sub_72990); by word id, dword_449A70 (sub_72AC0).
extern alfahash dword_449A70;
extern alfahash dword_449AA4;
extern alfahash dword_449AD8;
extern alfahash dword_449B0C;

// The version string sub_72B30 compares with.
extern const RwChar *off_428A4C;

// A named variable of the kind 0xD as sub_198900 returns it (a performance
// map's): only its value at +0x18 is known, the performance map id that
// "ChangeStateToPerformanceID" takes. The inline accessor has no address
// and so no database name; evidence: AnimTestTrigger::HandleAttributes
// (sub_A1860) and SceneTestTrigger's (sub_A21D0) read it twice, each time
// through a return temporary.
struct type_198900_perf
{
    RwInt32 unk_00[6];
    RwInt32 unk_18;

    RwInt32 get_unk_18()
    {
        return unk_18;
    }
};

// Registers the name arg_0 as a variable of the kind arg_4; only the widths
// of the others are known (all 0 here, but arg_14 for sets).
struct type_3DF8D8_04;
struct type_3DF8D8_base;
type_3DF8D8_base *sub_198900(type_3DF8D8_04 *arg_0, RwInt32 arg_4, void (*arg_8)(RwInt32, RwInt32, RwInt32),
                 RwInt32 arg_C, RwInt32 arg_10, RwInt32 arg_14);

// Callbacks for sub_198900 (its arg_8): each stores the value at arg_0 + 0x10
// at arg_8, a dword (sub_18F8B0), a word (sub_18F8E0) or a byte (sub_18F910).
struct type_3DF8D8;
RwInt32 sub_18F8B0(type_3DF8D8 *arg_0, RwInt32 arg_4, void *arg_8);
struct type_3DF8D8;
RwInt32 sub_18F8E0(type_3DF8D8 *arg_0, RwInt32 arg_4, void *arg_8);
struct type_3DF8D8;
RwInt32 sub_18F910(type_3DF8D8 *arg_0, RwInt32 arg_4, void *arg_8);
// Likewise, but it stores the hash (FNV, 0x811C9DC5 on) of the upper-cased
// string at arg_0 + 0x10 (CWeaponBehavior's names).
struct type_3DFE94;
RwInt32 sub_195C10(type_3DFE94 *arg_0, RwInt32 arg_4, void *arg_8);

struct type_3DF8D8_04;

// The key (*arg_4) of the name arg_0.
void sub_198A20(const RwChar *arg_0, type_3DF8D8_04 *arg_4);

void sub_72810();
void sub_72890();
void *sub_72BA0(RwChar *arg_0);
// The kind 3 files' imports resolved and released (sub_72920, sub_72960).
void sub_72920(type_72990 *arg_0);
// The other kinds' registrations (unit_072810): kind 0 (sub_728C0), kind 4
// (sub_729F0) and kind 2 (sub_72AA0).
void sub_728C0(type_72900 *arg_0);
void sub_729F0(type_72A30 *arg_0);
void sub_72AA0(struct type_67620_74 *arg_0);
void sub_72960(type_72990 *arg_0);
type_67620_74 *sub_72C40(RwChar *arg_0, bool arg_4);
type_72990 *sub_72D00(RwChar *arg_0, bool arg_4);
type_72A30 *sub_72F00(RwChar *arg_0, bool arg_4);
void sub_72FC0(RwInt32 arg_0, type_72FC0 *arg_4);
void sub_73050(type_72FC0 *arg_0);
void sub_73090(type_72FC0 *arg_0);
void sub_730D0(type_72FC0 *arg_0);
void sub_73160(type_73050 *arg_0, const RwChar *String1);

#endif
