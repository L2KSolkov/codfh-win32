/*
 * kujuUI's parsed files (\COD\SHARED\fileIO\cParsedFile.cpp,
 * unit_1C8DF0). A parsed file (cParsedFile, named by loadBinaryFile's
 * assertion) holds its string table (type_1CA4E0) and its root scope
 * (type_1C8DF0), a tree of scopes each with its child scopes (unk_00) and
 * its values (unk_104), read from a binary file and built through a scope
 * validator. Only the widths are known where no comment says more.
 */
#ifndef GAME_PARSEDFILE_H
#define GAME_PARSEDFILE_H

#include "rw/ostypes.h"
#include "game/fileio.h"

namespace kujuUI
{
// Named by loadBinaryFile's assertion: what builds a parsed file's
// scopes, with the file format version it takes (sub_6FCB0, a getter
// folded by /OPT:ICF).
struct type_1C8DF0;
struct type_1C8DF0_104;
struct type_1C8DF0_104_00;
struct type_1C9590;

struct type_1CA430;
// An iterator over a type_1CA430: its element and its array (its methods
// are shared through /OPT:ICF with other element types' and built
// elsewhere).
struct type_1EFD70
{
    void **unk_00;
    const type_1CA430 *unk_04;

    type_1EFD70(void **arg_0, const type_1CA430 *arg_4);
    type_1EFD70 &sub_204990();
    bool sub_1E8310(const type_1EFD70 &arg_0) const;
    void **sub_1EE9D0() const;
};

// A const iterator over a type_1CA430, built from an iterator (out of line,
// sub_204960); its other methods are the iterator's (shared through
// /OPT:ICF).
struct type_204960
{
    void *const *unk_00;
    const type_1CA430 *unk_04;

    type_204960(const type_1EFD70 &arg_0);
    type_204960 &sub_204990();
    bool sub_1E8310(const type_204960 &arg_0) const;
    void *const *sub_1EE9D0() const;
};

// Up to 32 pointers and their count: built empty; the next slot; the
// iterators at its end and its start.
struct type_1CA430
{
    void *unk_00[32];
    RwUInt32 unk_80;

    type_1CA430();
    void **sub_1CA3C0();
    type_1EFD70 sub_1CA400();
    type_1EFD70 sub_1CA450();
};

class cScopeValidator
{
public:
    type_1CA430 unk_00;     // the child scopes' validators
    type_1CA430 unk_84;     // the value definitions (type_1C9590)
    const RwChar *unk_108;  // the scope's name
    const RwChar *unk_10C;  // the keyword closing the scope (the creators' "end")
    RwInt32 unk_110;        // the format's version: a sum over its tree
    RwInt32 unk_114;        // the scope's kind (2: nameless)

    cScopeValidator();
    cScopeValidator(const RwChar *arg_0, const RwChar *arg_4, RwInt32 arg_8);
    // Empty and out of line (pDtor, folded by /OPT:ICF): the image
    // libraries' validator (sub_1EF2F0) calls it.
    ~cScopeValidator();
    // Adds the value definition arg_0; adds the child validator arg_0.
    void sub_1C9F50(type_1C9590 *arg_0);
    void sub_1C9F70(cScopeValidator *arg_0);
    // Takes over arg_0's children and definitions.
    void sub_1CA1A0(const cScopeValidator &arg_0);
    RwInt32 sub_1CA260() const;
    const RwChar *sub_1CA280() const;
    // Works out the version (sub_1CA2C0) and keeps it.
    void sub_1CA2A0();
    RwInt32 sub_1CA2C0();
    RwInt32 sub_6FCB0() const;
    RwInt32 sub_1C9FC0(const RwChar *arg_0, const RwChar *arg_4, type_1C8DF0 *arg_8, type_1C8DF0 **arg_C) const;
    // Builds the child scope named arg_0 (of kind arg_4) of arg_8 into
    // *arg_C (0 when done); builds the value named arg_0 (hash arg_4) from
    // its parts arg_8 (arg_C of them) into *arg_10.
    RwInt32 sub_1C9F90(const RwChar *arg_0, const RwChar *arg_4, type_1C8DF0 *arg_8, type_1C8DF0 **arg_C) const;
    void sub_1CA110(const RwChar *arg_0, RwInt32 arg_4, type_1C8DF0_104_00 *arg_8, RwUInt32 arg_C,
                    type_1C8DF0_104 **arg_10) const;
};

// The element size of the definitions' id arrays (4; a function of its
// own, shared by other element types through /OPT:ICF).
RwInt32 sub_200B80();

// A parsed file's string table (0x5008 bytes): the strings' count, the
// characters used, each string's offset and the characters. Its
// constructor clears the counts (folded by /OPT:ICF with type_ED850's,
// 0xED650); its destructor is empty (pDtor, 0x1E41C0).
struct type_1CA4E0
{
    RwInt32 unk_00;
    RwUInt32 unk_04;
    RwUInt32 unk_08[0x400];
    RwChar unk_1008[0x4000];

    type_1CA4E0();
    ~type_1CA4E0();
    // Its count (folded by /OPT:ICF into 0x1EE9D0).
    RwInt32 sub_1EE9D0() const;
    // The string equal to arg_0, added when missing; string arg_0 (0 when
    // out of range or -1).
    const RwChar *sub_1CA620(const RwChar *arg_0);
    const RwChar *sub_1CA720(RwUInt32 arg_0);
};
// Reads a string table from the file arg_0 into *arg_4 (left as it is when
// the read fails).
void sub_1CA4E0(cFileIn *arg_0, type_1CA4E0 **arg_4);

// Up to eight ids and their count (sub_1C9780 builds it empty; sub_1C97A0
// gives the next slot).
struct type_1C9780
{
    RwInt32 unk_00[8];
    RwUInt32 unk_20;

    type_1C9780();
    RwInt32 *sub_1C97A0();
};

struct type_1C8DF0_104_00;
struct type_1C8DF0_104;

// A value definition: its name, the ids of its (up to eight) parts, and a
// hash of them and the name's first character (unk_28).
struct type_1C9590
{
    const RwChar *unk_00;
    type_1C9780 unk_04;
    RwInt32 unk_28;

    type_1C9590(const RwChar *arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C, RwInt32 arg_10,
                RwInt32 arg_14, RwInt32 arg_18, RwInt32 arg_1C, RwInt32 arg_20);
    // Empty and out of line (pDtor, folded by /OPT:ICF): the image
    // libraries' validator (sub_1EF2F0) calls it.
    ~type_1C9590();
    // Adds the id arg_0 (false for 0).
    bool sub_1C9660(RwInt32 arg_0);
    // Inline accessors with no addresses, named for their fields.
    // Evidence: kujuUI's border creator (sub_1E04C0) reads the name, and the
    // validator's version sum (sub_1CA2C0) adds the hash, through
    // temporaries of their own.
    const RwChar *get_unk_00() const
    {
        return unk_00;
    }
    RwInt32 get_unk_28() const
    {
        return unk_28;
    }
    // Builds the value read with the name arg_0 and hash arg_4 from its
    // parts arg_8 (arg_C of them) into *arg_10 when it is this definition:
    // 1 for another hash, 2 for another name, 0 when built.
    RwInt32 sub_1C96B0(const RwChar *arg_0, RwInt32 arg_4, const type_1C8DF0_104_00 *arg_8, RwUInt32 arg_C,
                       type_1C8DF0_104 **arg_10) const;
};

// A value's part (8 bytes: its kind and its value; its constructor clears
// it and is folded by /OPT:ICF with type_ED850's, 0xED650).
struct type_1C8DF0_104_00
{
    RwInt32 unk_00;
    RwInt32 unk_04;

    type_1C8DF0_104_00();
    // Reads its kind and value from the file arg_0; a string's value is its
    // index in the table arg_4 (kinds 1 and 2), turned into the string.
    type_1C8DF0_104_00(cFileIn *arg_0, type_1CA4E0 *arg_4);
    // Its kind (folded by /OPT:ICF into 0x1EE9D0).
    RwInt32 sub_1EE9D0() const;
    // Its value as a number.
    RwReal sub_1CA870() const;
    // Its value as an integer (the word at +4; folded by /OPT:ICF with RWS's
    // CAttributeCommand::GetCommandId, 0x1E3480).
    RwInt32 sub_1E3480() const;
};

// A value of a scope: its parts, their count and its definition. Its
// destructor is empty (folded by /OPT:ICF into pDtor, 0x1E41C0).
struct type_1C8DF0_104
{
    type_1C8DF0_104_00 unk_00[8];
    RwUInt32 unk_40;
    const type_1C9590 *unk_44;

    type_1C8DF0_104(const type_1C8DF0_104_00 *arg_0, RwUInt32 arg_4, const type_1C9590 *arg_8);
    ~type_1C8DF0_104();
    // Its definition's name; part arg_0.
    const RwChar *sub_1C9870();
    type_1C8DF0_104_00 *sub_1C9890(RwUInt32 arg_0);
    // Its parts' count (unk_40; out of line and shared through /OPT:ICF,
    // 0x21D030).
    RwUInt32 sub_21D030();
    // Its parts (returns this: folded by /OPT:ICF into sub_6FCD0).
    type_1C8DF0_104_00 *sub_6FCD0();
    // An inline accessor with no address and so no database name, named for
    // its field. Evidence: the value lookup (sub_1C90B0) reads the
    // definition through a result local.
    const type_1C9590 *get_unk_44()
    {
        const type_1C9590 *r = unk_44;
        return r;
    }
};

// A scope: its child scopes, its values, its name (from the string
// table), its parent, the string table and the validator that builds its
// children.
struct type_1C8DF0
{
    type_1C8DF0 *unk_00[64];
    RwUInt32 unk_100;
    type_1C8DF0_104 *unk_104[32];
    RwUInt32 unk_184;
    const RwChar *unk_188;
    type_1C8DF0 *unk_18C;
    type_1CA4E0 *unk_190;
    const cScopeValidator *unk_194;

    type_1C8DF0(type_1CA4E0 *arg_0, const cScopeValidator *arg_4);
    type_1C8DF0(const RwChar *arg_0, type_1C8DF0 *arg_4, const cScopeValidator *arg_8);
    ~type_1C8DF0();
    const RwChar *sub_1C8FC0();
    const cScopeValidator *sub_1C8FE0();
    // Its child arg_0 (unk_00[arg_0]: shared through /OPT:ICF with the
    // look's state getter, 0x1E3BF0).
    type_1C8DF0 *sub_1E3BF0(RwUInt32 arg_0);
    // Takes the value *arg_0 (and clears it); takes the child *arg_0.
    void sub_1C9000(type_1C8DF0_104 **arg_0);
    void sub_1C9050(type_1C8DF0 **arg_0);
    RwUInt32 sub_1C9090();
    // The value with the definition arg_0, or 0; the values' count; value
    // arg_0.
    type_1C8DF0_104 *sub_1C90B0(const type_1C9590 *arg_0);
    RwUInt32 sub_1C9120();
    type_1C8DF0_104 *sub_1C9140(RwUInt32 arg_0);
    // Reads its contents from the file arg_0.
    bool sub_1C9160(cFileIn *arg_0);
    bool sub_1C9190(cFileIn *arg_0, type_1CA4E0 *arg_4);
};

// A parsed file: its string table and its root scope, taken from their
// pointers (which it clears) and deleted with it.
class cParsedFile
{
public:
    type_1CA4E0 *unk_00;
    type_1C8DF0 *unk_04;

    cParsedFile(type_1C8DF0 **arg_0, type_1CA4E0 **arg_4);
    ~cParsedFile();
    // Loads the binary file arg_0 (built through the validator arg_4) into
    // *arg_8, or leaves it 0.
    static void loadBinaryFile(const RwChar *arg_0, const cScopeValidator *arg_4, cParsedFile **arg_8);
    // Its root scope (the word at +4: folded by /OPT:ICF into 0x1E3480).
    type_1C8DF0 *sub_1E3480();
};

// The image libraries' validator (0x144 bytes: the "images" definition,
// unk_118, and the looks' validator, sub_1E3CD0, as a child): one, made on
// first use (sub_1EF1E0, into dword_504374) and deleted (sub_1EF340, and
// through sub_1EF850); given as a validator (sub_1EF810) and its
// definition (sub_1EF830).
struct type_1EF260 : cScopeValidator
{
    type_1C9590 unk_118;

    type_1EF260();
    ~type_1EF260();
};
type_1EF260 *sub_1EF1E0();
void sub_1EF340();
const cScopeValidator *sub_1EF810();
type_1C9590 *sub_1EF830();
void sub_1EF850();
}

#endif
