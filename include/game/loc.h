/*
 * The localised text (unit_1CA890): three tables of wide strings (loaded
 * from LOC\<language><file>.loc), each a dictionary from a key to its text,
 * and the manager that holds them for the current language (unk_4FEB0C).
 * Only the widths are known where no comment says more.
 */
#ifndef GAME_LOCTEXT_H
#define GAME_LOCTEXT_H

#include "rw/ostypes.h"
#include "game/fileio.h"
#include "types/type_505188.h"
#include "game/pool.h"

// The language arg_0's directory name (dword_42CCD4).
const RwChar *sub_1CA890(RwInt32 arg_0);
extern const RwChar *dword_42CCD4[];

// A dictionary entry: its key and its (wide) text.
struct type_1CA8A0_00
{
    const RwChar *unk_00;
    const RwUInt16 *unk_04;
};

// A dictionary sorted by key: its entries, its capacity, their count,
// whether keys compare with case, and lookup and comparison counters.
struct type_1CA8A0
{
    type_1CA8A0_00 *unk_00;
    RwInt32 unk_04;
    RwInt32 unk_08;
    RwInt32 unk_0C;
    RwInt32 unk_10;
    RwInt32 unk_14;
    RwInt32 unk_18;

    type_1CA8A0(RwInt32 arg_0, RwInt32 arg_4);
    ~type_1CA8A0();
    // Compares two keys (the same pointer is equal).
    RwInt32 sub_1CA940(const RwChar *arg_0, const RwChar *arg_4);
    // Sorts the entries from arg_0 on (insertion).
    void sub_1CA9A0(RwInt32 arg_0);
    // The entry for the key arg_0 (binary search), or 0; its text.
    type_1CA8A0_00 *sub_1CAA80(const RwChar *arg_0);
    const RwUInt16 *sub_1CAB70(const RwChar *arg_0);
    // Adds the key arg_0 with the text arg_4 when missing.
    void sub_1CABA0(const RwChar *arg_0, const RwUInt16 *arg_4);
    // Empties it: an inline with no address, named for what it does.
    // Evidence: the table's load (sub_1CB390) clears the count through a
    // `this` temporary.
    void sub_reset()
    {
        unk_08 = 0;
    }
};

// A table: its data, its dictionary, the data's size and the strings'
// count. Built with new and no constructor of its own.
struct type_1CB260
{
    RwUInt8 *unk_00;
    type_1CA8A0 *unk_04;
    RwUInt32 unk_08;
    RwUInt32 unk_0C;

    type_1CB260()
    {
    }
    ~type_1CB260();
    // Allocates arg_0 bytes of data and a dictionary for arg_4 strings.
    void sub_1CB260(RwUInt32 arg_0, RwUInt32 arg_4);
    // Frees them.
    void sub_1CB310();
    // Loads LOC\<arg_0>.loc.
    bool sub_1CB390(const RwChar *arg_0);
    // The text for the key arg_0, or 0.
    const RwUInt16 *sub_1CB640(const RwChar *arg_0);
};

// The manager: its three tables and the language.
struct type_1CAC10
{
    type_1CB260 *unk_00[3];
    RwInt32 unk_0C;

    type_1CAC10();
    ~type_1CAC10();
    // Unloads the tables (the first too when arg_0 is set); unloads table
    // arg_0.
    void sub_1CAC60(bool arg_0);
    bool sub_1CACC0(RwInt32 arg_0);
    // Sets the language (reloading the tables); false when unchanged.
    bool sub_1CAD40(RwInt32 arg_0);
    // Loads table arg_0 in the current language.
    void sub_1CADA0(RwInt32 arg_0, bool *arg_4);
    // The text for the key arg_0 in table arg_4 (else in table 0), or 0.
    const RwUInt16 *sub_1CAEA0(const RwChar *arg_0, RwInt32 arg_4);
    // The text for the key arg_0 in table arg_4 as a narrow string (the key
    // itself when there is none, "" for no key; sub_E3970 returns it).
    type_1A5EA0 sub_1CAF30(const RwChar *arg_0, RwInt32 arg_4);
};
// Formats the text arg_4 into arg_0 with its "%1" (and "%2") taking
// arg_8 (and arg_C), in the order they appear.
void sub_1CB000(RwChar *arg_0, const RwChar *arg_4, const RwChar *arg_8);
void sub_1CB0F0(RwChar *arg_0, const RwChar *arg_4, const RwChar *arg_8, const RwChar *arg_C);
// A text built from a string (its type_1A5EA0 base from the string's
// characters).
struct type_1CB670 : type_1A5EA0
{
    // Empty, declared out of line: folded (/OPT:ICF) with the other string
    // types' out-of-line default constructors at sub_E87E0, which the image
    // calls for texts (sub_1AFBB0, the text widgets' sub_1F2790) where
    // type_1A5EA0's own is expanded inline (config/aliases.txt).
    type_1CB670();
    type_1CB670(const std::string &arg_0);
    // Out of line: the option selectors' labels are copied through it
    // (sub_1FCEB0), folded (/OPT:ICF) into the constructor above.
    type_1CB670(const type_1CB670 &arg_0);
    type_1CB670(RwInt32 arg_0, const type_1A5EA0 &arg_4);
    // The localised text for the key arg_0 in table arg_4. Out of line:
    // sub_1CB6B0 initializes the type_1A5EA0 base through sub_E3970's
    // return buffer; the option selectors' constructors
    // (sub_20EE00) call it with the text's `this` kept across the call.
    type_1CB670(const RwChar *arg_0, RwInt32 arg_4);
    // Empties it.
    void sub_1CB790();
};
// The text arg_0 as a type_1CB670.
type_1CB670 sub_1CB720(const RwChar *arg_0);
// The localised text for the key arg_0 in table arg_8 with its "%1" (and
// "%2") replaced by arg_4 (and arg_8).
type_1CB670 sub_1CB7B0(const RwChar *arg_0, const RwChar *arg_4, RwInt32 arg_8);
type_1CB670 sub_1CB8B0(const RwChar *arg_0, const RwChar *arg_4, const RwChar *arg_8, RwInt32 arg_C);
// Texts made once (static locals).
type_1CB670 *sub_1CB9B0();
type_1CB670 *sub_1CBA30();
type_1CB670 *sub_1CBAB0();
type_1CB670 *sub_1CBB30();
// The ellipsis ("..."; returned by reference: the text's cut to fit,
// sub_1F2110, copies it without a temporary).
const type_1CB670 &sub_1CBBB0();
extern type_1CAC10 unk_4FEB0C;
extern bool byte_4FEAEC;

#endif
