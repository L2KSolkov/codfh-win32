/*
 * The script VM: the interpreter that runs the compiled scripts (the
 * objects of the handle table, type_67620) over the loaded script image
 * dword_4492DC. sub_67B10 fills its opcode table dword_4491C0 and clears
 * its state, sub_67E30 loads an image (turning its offsets into pointers
 * and binding its commands by name with sub_441B0), and sub_68310 runs a
 * script until an opcode halts it (byte_449324).
 *
 * The image starts with a word, then the header type_4492DC_04 giving its
 * tables' counts and offsets. The database names two of the globals the
 * header fills from qsort's parameters (Base and NumOfElements, the command
 * table sub_67E30 sorts).
 */
#ifndef SCRIPTVM_H
#define SCRIPTVM_H

#include "rw/ostypes.h"
#include "types/type_44350.h"
#include "types/type_439E78.h"
#include "types/type_42AF0.h"

struct type_67620;
struct type_3D2E7C;

// The header of a script image (at +4).
struct type_4492DC_04
{
    RwInt32 unk_00;         // the command count (NumOfElements)
    RwInt32 unk_04;         // the counts of the three tables below
    RwInt32 unk_08;
    RwInt32 unk_0C;
    RwInt32 unk_10;         // the count of unk_24's entries
    void *unk_14;           // the offsets of the tables: the commands
    void *unk_18;           // (Base), unk_18, unk_1C, unk_20 and unk_24
    void *unk_1C;
    void *unk_20;
    struct type_449308 *unk_24;
    RwInt32 unk_28;         // the count of unk_2C's words
    void *unk_2C;
};

// The entries of dword_4492EC and dword_4492F4 (0x14 bytes) and of
// dword_4492FC (0x10 bytes): unk_04 is an index, which sub_68190 and
// sub_68250 sort the latter two by in place (-1 for none).
struct type_4492EC
{
    RwChar *unk_00;         // its name
    RwInt32 unk_04;
    RwInt32 unk_08;         // dword_4492EC's: the words a call pops, whether
    RwInt32 unk_0C;         // it returns and the words it returns
    RwInt32 unk_10;
};

struct type_4492FC
{
    RwChar *unk_00;         // its name
    RwInt32 unk_04;
    RwInt32 unk_08[2];
};

// A stack slot's value: the arithmetic opcodes build their result in one
// (an int, or a float for their float forms) and store it as a dword.
union type_449318
{
    RwInt32 unk_00;
    RwReal unk_00_f;
};

// Whether arg_0 has any of the bits arg_4: an inline with no address and
// so no database name, named for what it does. Evidence: the call opcodes
// (sub_69770, sub_69A90) turn their flag bits into bools with the
// conversion of a bool return (neg, sbb, neg), which widening to an int
// then zero-extends (movzx); the expression written in place gives neither.
inline bool test_flag(RwInt32 arg_0, RwInt32 arg_4)
{
    return (arg_0 & arg_4) != 0;
}

// The opcode handlers, by opcode (sub_67B10 leaves 30 empty).
extern void (*dword_4491C0[49])();

// The loaded image, its header's tables and their counts.
extern RwChar *dword_4492DC;
extern type_44350 *Base;           // the database's name
extern RwInt32 NumOfElements;       // the database's name
extern type_4492EC *dword_4492EC;
extern RwInt32 dword_4492F0;
extern type_42E00_00 *dword_4492F4;     // the message kinds
extern RwInt32 dword_4492F8;
extern type_4492FC *dword_4492FC;
extern RwInt32 dword_449300;
extern RwInt32 dword_449304;
// The loaded image's globals (dword_449304 of them, 0x44 bytes each): its
// id (the low 28 bits) and its name, which sub_73160 reads for its type.
struct type_449308
{
    RwUInt32 unk_00;
    RwChar unk_04[0x40];
};
extern type_449308 *dword_449308;
extern void **dword_449290;
extern RwInt32 dword_4492D4;

// The running script's state (sub_68310 swaps it in and out): the code
// pointer, the frame pointer and a fourth word (the stack pointer is
// dword_449318), whether an opcode halted it and whether it ended (its
// state is then not stored back), and the script itself (dword_449328).
extern RwInt32 *dword_449320;
extern RwInt32 *dword_44931C;
extern RwInt32 dword_4492E0;
extern RwUInt8 byte_449324;
extern RwUInt8 byte_449325;

// The running instruction's operand (its high half): an inline with no
// address and so no database name, named for what it returns. Evidence:
// the local opcodes (sub_69CF0, sub_69D50) keep it in a short temporary
// packed after their locals, written before the call that indexes by it
// and read after; the expression written in place, or a short local, gives
// neither.
inline RwInt16 get_operand()
{
    return (RwInt16)(*dword_449320 >> 16);
}

extern RwUInt8 byte_4492D8;         // set once sub_67B10 has run
extern RwInt32 dword_4492AC;
extern RwUInt8 byte_449314;
extern RwUInt8 byte_449315;

// sub_72B30: checks the image's version string; sub_72B80 also frees it.
RwInt32 sub_72B30(RwChar *arg_0);
void sub_72B80(RwChar *arg_0);
// sub_67E30: loads the script image arg_0 (unit_067B10; the Alfa files'
// resource handler hands it each data file).
void sub_67E30(RwChar *arg_0);
// sub_72B60: turns the offset at arg_0 (unless 0) into a pointer from arg_4.
void sub_72B60(void *arg_0, void *arg_4);
// CompareFunction (the database's name): qsort's order of two entries by
// their unk_04.
RwInt32 CompareFunction(const void *arg_0, const void *arg_4);
// byte_449298 takes a returning call's results (sub_69A90).
extern RwUInt8 byte_449298[0x10];
// sub_71B90: a new script task (the spawn opcode, sub_6A080).
struct type_46120 *sub_71B90();
// The records by index or name (sub_6A7D0 to sub_6A950).
type_42E00_00 *sub_6A7D0(RwInt32 arg_0);
type_42E00_00 *sub_6A7F0(const RwChar *arg_0);
RwInt32 sub_6A860(RwInt32 arg_0, RwInt32 arg_4);
type_4492FC *sub_6A8E0(const RwChar *arg_0);
type_4492EC *sub_6A950(RwInt32 arg_0);
// sub_6B060: the debugger's report of the script arg_0 (arg_4, arg_8).
bool sub_6B060(type_67620 *arg_0, const RwChar *arg_4, bool arg_8);
// sub_6B710 (alfamessman): a new message of kind arg_0 for the script arg_4
// (all when 0) from arg_8, with the arguments ending at arg_18 (reversed
// when arg_1C is clear); returns its handle.
type_439E78_00 sub_6B710(RwInt32 arg_0, type_67620 *arg_4, type_3D2E7C *arg_8,
                         type_42E00_10 *arg_C, type_3D2E7C *arg_10, RwInt32 arg_14, RwInt32 *arg_18,
                         bool arg_1C);
// sub_72900: opcode 36's function of the top word; only the widths are
// known.
RwInt32 sub_72900(RwInt32 arg_0);
// sub_68310: runs the script arg_0 until an opcode halts it.
void sub_68310(type_67620 *arg_0);
// sub_441B0: the script command named arg_0 (unit_0441B0).
type_4276E0_fn sub_441B0(const RwChar *arg_0);

#endif
