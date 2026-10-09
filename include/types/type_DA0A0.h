/*
 * The game's save record: 0xC8 bytes, "1DOC" (0x434F4431) and version 0x101,
 * cleared by sub_DA0A0 and filled from the save state dword_4F28F0 by
 * sub_D9EC0; named after its clearing function. It holds the settings
 * (type_DA150, "Player" by default) and the player's state (type_D90B0).
 */
#ifndef TYPE_DA0A0_H
#define TYPE_DA0A0_H

#include <string.h>

#include "rw/ostypes.h"

// The player's state as the save keeps it (0x5C bytes; the player fills it
// with sub_111040 and the checkpoint save, sub_D8F80, checks it): its
// weapons (unk_00 a weapon below 39 or -1, unk_04 0 or 1, two more in
// unk_08), unk_18's thirteen counts, unk_50 (100 when cleared) and unk_54
// (0 to 1, 1 when cleared). Named after its clearing function.
struct type_D90B0_18
{
    RwInt32 unk_00;             // 0, or 1 to 12
    RwInt32 unk_04[13];         // none negative

    // Clears the counts: an inline with no address and so no database
    // name, named for what it does (sub_D90B0 clears them through a `this`
    // temporary and a loop counter of its own).
    void clear()
    {
        unk_00 = 0;
        for (RwUInt32 i = 0; i < 13; i++)
        {
            unk_04[i] = 0;
        }
    }
    // Whether the counts are in range: likewise inline (sub_D9180 keeps its
    // result in a byte temporary).
    bool is_valid()
    {
        if ((unk_00 < 1 || unk_00 > 12) && unk_00 != 0)
        {
            return false;
        }
        for (RwUInt32 i = 0; i < 13; i++)
        {
            if (unk_04[i] < 0)
            {
                return false;
            }
        }
        return true;
    }
};
struct type_D90B0
{
    RwUInt32 unk_00;
    RwUInt32 unk_04;
    RwInt32 unk_08[2];
    RwInt32 unk_10[2];
    type_D90B0_18 unk_18;
    RwInt32 unk_50;
    RwReal unk_54;
    RwInt32 unk_58;

    // Clears the state, and its weapons.
#ifdef CODFH_SP // inline in single player: SP 0xA49F0 and 0x12EFE0 expand both
    void sub_D9120()
    {
        RwUInt32 var_4;

        unk_00 = 0;
        unk_04 = 0;
        for (var_4 = 0; var_4 < 2; var_4++)
        {
            unk_10[var_4] = 0;
            unk_08[var_4] = -1;
        }
    }
    void sub_D90B0()
    {
        RwInt32 var_4;              // never used; the image's frame keeps its slot

        sub_D9120();
        unk_18.clear();
        unk_54 = 1.0f;
        unk_50 = 100;
        unk_58 = 0;
    }
#else
    void sub_D90B0();
    void sub_D9120();
#endif
    // Whether the state, and its weapons, are in range (arg_0: stricter,
    // as the save wants it).
    bool sub_D9180(bool arg_0);
    bool sub_D9240(bool arg_0);
};
typedef RwChar type_D90B0_size_check[sizeof(type_D90B0) == 0x5C ? 1 : -1];

// The save's settings (0x44 bytes, cleared by sub_DA150).
struct type_DA150
{
    RwInt32 unk_00;
    RwInt32 unk_04;
    RwInt32 unk_08;
    RwUInt8 unk_0C;
    RwUInt8 unk_0D;
    RwUInt8 unk_0E;
    RwUInt8 unk_0F;
    RwUInt8 unk_10;
    RwUInt8 unk_11;
    RwUInt8 unk_12[0x2];
    RwInt32 unk_14;
    RwInt32 unk_18;
    RwInt32 unk_1C;
    RwChar unk_20[0x20];        // the player's name ("Player")
    RwUInt8 unk_40[0x2];
    RwUInt8 unk_42[0x2];

#ifdef CODFH_SP // inline in single player: SP 0x12EFE0 expands it (0xA4980 its copy)
    void sub_DA150()
    {
        unk_00 = 1;
        unk_04 = 1;
        unk_08 = 0;
        unk_0C = 1;
        unk_0D = 0;
        unk_0E = 1;
        unk_0F = 1;
        unk_10 = 1;
        unk_11 = 1;
        unk_14 = 1;
        unk_18 = 0;
        unk_1C = 0;
        memset(unk_20, 0, 0x20);
        strcpy(unk_20, "Player");
        memset(unk_40, 0, 2);
    }
#else
    void sub_DA150();
#endif
};
typedef RwChar type_DA150_size_check[sizeof(type_DA150) == 0x44 ? 1 : -1];

// The record's player block (0x64 bytes): the state and eight bytes more.
struct type_DA0A0_64
{
    type_D90B0 unk_00;
    RwUInt8 unk_5C[0x8];

    // Clears it: an inline with no address and so no database name, named
    // for what it does (sub_DA0A0 clears it through a `this` temporary).
    void clear()
    {
        unk_00.sub_D90B0();
        memset(unk_5C, 0, 8);
    }
    // Takes the state arg_0 (sub_D9EC0 when the level is the furthest);
    // returns itself.
    type_DA0A0_64 *sub_19AC40(type_D90B0 *arg_0);
};

struct type_DA0A0
{
    RwUInt32 unk_00;            // "1DOC"
    RwUInt16 unk_04;            // 0x101
    RwUInt16 unk_06;
    RwInt32 unk_08;             // its size, 0xC8
    RwUInt16 unk_0C;            // the level
    RwUInt16 unk_0E;            // the furthest level
    RwChar unk_10[0xC];
    RwUInt16 unk_1C;            // its checksum (sub_19ABA0)
    RwUInt16 unk_1E;
    type_DA150 unk_20;
    type_DA0A0_64 unk_64;

    // Clears the record (sub_DA0F0 the header, for a record of arg_0 bytes).
#ifdef CODFH_SP // inline in single player: SP 0xA4B10 and 0x12EFE0 expand both
    void sub_DA0F0(RwInt32 arg_0)
    {
        unk_00 = 0x434F4431;
        unk_04 = 0x101;
        arg_0 = arg_0;
        unk_0C = 1;
        unk_0E = 1;
        memset(unk_10, 0, 0xC);
        unk_1C = 0;
    }
    void sub_DA0A0()
    {
        sub_DA0F0(0xC8);
        unk_20.sub_DA150();
        unk_64.clear();
    }
#else
    void sub_DA0A0();
    void sub_DA0F0(RwInt32 arg_0);
#endif
    // Its checksum.
    // Whether it is blank ("KNLB"): an inline with no address and so no
    // database name, named for what it tests. Evidence: the checksum
    // (sub_19ABA0) tests the comparison's result as a bool (sete, movzx).
    bool is_blank()
    {
        return unk_00 == 0x424C4E4B;
    }
    RwUInt16 sub_19ABA0();
};
typedef RwChar type_DA0A0_size_check[sizeof(type_DA0A0) == 0xC8 ? 1 : -1];

// Fills the save record arg_0 from the save state.
void sub_D9EC0(type_DA0A0 *arg_0);

// The memory card the saves go to (a stub on this build: sub_D9D30 finds
// nothing): its port (-1 for none), its free space and the last result;
// named after its first method.
struct type_D9CF0
{
    RwInt32 unk_00;
    RwInt32 unk_04;
    RwInt32 unk_08;

    // Inline: its initializer (0x30B200) sets all three to -1, and its exit
    // function (0x30E3E0) is empty.
    type_D9CF0()
    {
        unk_00 = -1;
        unk_04 = -1;
        unk_08 = -1;
    }
    ~type_D9CF0()
    {
    }
    // Its free space, returned directly: an inline with no address. Evidence:
    // the card poll (sub_18B670) reads it through a return slot it never
    // writes first.
    RwInt32 get_unk_04()
    {
        return unk_04;
    }
    // Sets the saves up (1.225 into dword_4B8970); true.
    bool sub_D9CF0(RwInt32 arg_0, RwInt32 arg_4);
    // Looks for a card: 0.
    RwInt32 sub_D9D30();
    // The four slots' names into arg_4 (12 bytes each), arg_0[i] set for
    // an empty slot; whether any is in use.
    bool sub_D9D60(RwInt32 *arg_0, RwChar (*arg_4)[12]);
    // Saves into slot arg_0; 0.
    RwInt32 sub_D9E50(RwInt32 arg_0);
    RwInt32 sub_DA200();
#ifdef CODFH_SP
    // Loads slot arg_0's save into the save state; 0 (SP 0xA4CA0).
    RwInt32 sp_sub_A4CA0(RwInt32 arg_0);
#endif
    RwInt32 sub_DA220();
    // Whether a save fits: the space it needs (sub_DA280) against the free
    // space and the card's own (sub_DA220).
    bool sub_DA230();
    RwInt32 sub_DA280();
    // Empty: folded by /OPT:ICF into pDtor (0x1E41C0), whose database name
    // it takes; the shell (sub_1A2E40) calls it when it is done.
    void pDtor();
};
// The saves' slots (0xD4 bytes each, their names at +0x14) and whether
// each holds a save of the game's (dword_4F6158).
struct type_4F5DC4_04
{
    RwUInt8 unk_00[0x10];
    RwChar unk_10[0x14];
    RwUInt8 unk_24[0xAC];
};
struct type_4F5DC4
{
    RwInt32 unk_00;
    type_4F5DC4_04 unk_04;
};
#ifdef CODFH_PLAIN
extern type_4F5DC4 (&dword_4F5DC4)[4];
#else
extern type_4F5DC4 dword_4F5DC4[4];
#endif
// The same slots whole (unit_1A16D0, which reads and writes them as the
// profiles' save files, "DANTE%d.dat"): the slot's index (-1 when empty),
// whether it is in use, the save record, and whether it is the one chosen
// (sub_1A26B0).
struct type_4F5DC0
{
    RwInt32 unk_00;
    RwInt32 unk_04;
    type_DA0A0 unk_08;
    RwInt32 unk_D0;
};
typedef RwChar type_4F5DC0_size_check[sizeof(type_4F5DC0) == 0xD4 ? 1 : -1];
extern type_4F5DC0 dword_4F5DC0[4];
extern RwInt32 dword_4F6158[4];
extern RwInt32 dword_4B88AC;
extern RwReal dword_4B8970;
extern RwInt32 dword_4292B0;
RwInt32 sub_1A1790(RwInt32 arg_0);
RwInt32 sub_1A1D40();
void sub_1A1BB0(RwChar *arg_0, RwInt32 arg_4);
void sub_1A26B0(RwInt32 arg_0);
RwInt32 sub_1A1820(type_DA0A0 *arg_0, RwInt32 arg_4);
RwInt32 sub_19B080();

#endif
