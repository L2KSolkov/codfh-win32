/*
 * The host's game options (unit_200B90): the values the front end's host
 * pages show and change (the game type, the level, the time limit, the
 * scores and the rules), read from the front end's settings copy
 * (unk_4FDBB0, sub_201890) and written back (sub_201A70). The option
 * selectors are game/options.h's template, each a class of its own
 * (their units follow) over a value type of its own.
 */
#ifndef GAME_HOSTOPTIONS_H
#define GAME_HOSTOPTIONS_H

#include "game/options.h"
#include "game/uiglue.h"

// The selectors' values (distinct enumerations; names and values not
// known), named for their selectors' base constructors.
enum type_212C70_value
{
};
enum type_214C30_value
{
};
enum type_20EFD0_value
{
};
enum type_2138C0_value
{
};
enum type_210430_value
{
};
// The weapon selection's values (the weapon classes; the pause menu's
// weapon page's selector, unit_223280).
enum type_224010_value
{
};

// A compiled-out check of a level list index: no code, but its load moves
// the compiler's register rotation (the host options' write, sub_201A70,
// checks twice). The condition is a stand-in with one load.
#define LEVELS_CHECK(i) { if ((i) == (RwInt32)dword_4FD970) { } }

// The level picked (sub_1C4BC0) in the level list, checked twice: an inline
// with no address, named for what it gives. Evidence: a scoreboard's
// options (sub_21E630, sub_21E7A0) keep the index in a local placed after
// the temporaries, the checks moving the registers.
inline type_505188 *picked_level()
{
    RwInt32 r = sub_1C4BC0();

    LEVELS_CHECK(r);
    LEVELS_CHECK(r);
    return &dword_4FD974[r];
}

// The players picked in the front end's settings (the host options' and
// the find session page's players selector).
#ifdef CODFH_PLAIN
extern RwInt32 &dword_4F6300;
#else
extern RwInt32 dword_4F6300;
#endif
// Whether the time limit's "No limit" was picked when the game type took it
// away (the time limit's update, sub_2016A0).
extern RwUInt8 byte_5044E0;

// A level as the level selector's value (4 bytes): the level list's entry
// (unk_00), ordered by the entries' first strings (type_505188::sub_1A5F80).
// Its destructor is empty: the host options' read (sub_201890) keeps one in
// an unwind state of its own. The comparison and the copy read the other
// key through its getter: the map's insert (sub_211C00) and node
// (sub_2122B0) and the selector's add (sub_211950) copy the level through a
// slot, and the insert has no unwind frame for a by-value operand.
struct type_211860_key
{
    type_505188 *unk_00;

    // Over the level arg_0: an inline with no address. Evidence: the
    // scoreboard's options (sub_21E630) pick the level through one.
    type_211860_key(type_505188 *arg_0)
    {
        unk_00 = arg_0;
    }
    ~type_211860_key()
    {
    }
    bool operator<(const type_211860_key &arg_0) const
    {
        return unk_00->sub_1A5F80(*arg_0.get_unk_00());
    }
    type_211860_key(const type_211860_key &arg_0)
    {
        unk_00 = arg_0.get_unk_00();
    }
    // Its level: an inline accessor with no address, named for its field.
    // Evidence: the host options' write (sub_201A70) reads it through a
    // slot of its own.
    type_505188 *get_unk_00() const
    {
        return unk_00;
    }
};

// The option selectors (each 0x20 bytes over its template's instance; only
// their constructors, and the destructors not generated, are known): the
// respawn's (sub_20EE00, "Respawn"), the level's (sub_211680), the
// players' (sub_213680), the respawn order's (sub_212A80: none, forwards,
// backwards, random), the yes-or-no rules' (sub_214A90, "Yes") and the
// game type's (sub_210180).
struct type_20EE00 : type_1FCDC0<type_20EFD0_value>
{
    type_20EE00(RwInt32 arg_0, RwInt32 arg_4);
    virtual ~type_20EE00();
};
struct type_211680 : type_1FCDC0<type_211860_key>
{
    type_211680(RwInt32 arg_0, kujuUI::type_1ED670_object *arg_4);
    virtual ~type_211680();
};
struct type_213680 : type_1FCDC0<type_2138C0_value>
{
    type_213680(RwInt32 arg_0, kujuUI::type_1ED670_object *arg_4);
    virtual ~type_213680();
};
struct type_212A80 : type_1FCDC0<type_212C70_value>
{
    type_212A80(kujuUI::type_1ED670_object *arg_0);
};
struct type_214A90 : type_1FCDC0<type_214C30_value>
{
    // Picks arg_4 (the constructor, sub_214A90, passes its address).
    type_214A90(RwInt32 arg_0, type_214C30_value arg_4, kujuUI::type_1ED670_object *arg_8);
};
struct type_210180 : type_1FCDC0<type_210430_value>
{
    type_210180(RwInt32 arg_0, kujuUI::type_1ED670_object *arg_4);
    virtual ~type_210180();
};
// The server's name (0x28 bytes over a text; sub_213610).
struct type_213610 : kujuUI::type_1F28C0
{
    type_213610();
    virtual ~type_213610();
};
// The score limit (0x7C bytes over an integer value; "No limit" at the
// least when arg_1C is 1).
struct type_20EC00 : kujuUI::type_1E76A0
{
    type_20EC00(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C, RwInt32 arg_10, RwInt32 arg_14,
                RwInt32 arg_18, RwInt32 arg_1C, kujuUI::type_1ED670_object *arg_20);
};

// The host's options (off_3E8374, 0x3A0 bytes; sub_200B90 builds it with
// arg_0 kept in unk_39D): the actions and checks the pages' widgets call on
// it (unk_04 to unk_80, over its methods), the options, the name widgets
// found by name (unk_374 "name", unk_378 "nametext", through unk_37C), the
// values kept while a page is open (unk_388 to unk_398, sub_201CD0 and
// sub_201D60), and whether the options may change (unk_39C). Slot 0 is told
// of a change (empty here).
struct type_200B90
{
    kujuUI::type_3E7264<type_200B90> unk_04;
    kujuUI::type_3E7264<type_200B90> unk_14;
    kujuUI::type_3E7264<type_200B90> unk_24;
    kujuUI::type_3E7264<type_200B90> unk_34;
    kujuUI::type_3E7264<type_200B90> unk_44;
    kujuUI::type_3E7264<type_200B90> unk_54;
    kujuUI::type_3E7264<type_200B90> unk_64;
    kujuUI::type_3E7CE8<type_200B90> unk_74;
    kujuUI::type_3E7264<type_200B90> unk_80;
    type_213610 unk_90;
    type_20EE00 unk_B8;
    type_211680 unk_D8;
    kujuUI::type_1E76A0 unk_F8;
    type_213680 unk_174;
    type_1FCDC0<RwUInt32> unk_194;
    type_20EC00 unk_1B4;
    kujuUI::type_1E76A0 unk_230;
    type_212A80 unk_2AC;
    type_214A90 unk_2CC;
    type_214A90 unk_2EC;
    type_214A90 unk_30C;
    type_210180 unk_32C;
    kujuUI::type_1F28C0 unk_34C;
    kujuUI::type_3E7D08 *unk_374;
    kujuUI::type_3E7D08 *unk_378;
    kujuUI::type_1EFCF0<kujuUI::type_3E7D08 *> unk_37C;
    RwInt32 unk_388;
    RwInt32 unk_38C;
    RwInt32 unk_390;
    RwInt32 unk_394;
    RwInt32 unk_398;
    bool unk_39C;
    bool unk_39D;

    type_200B90(bool arg_0);
    ~type_200B90();
    virtual void vf_00();
    void sub_201590();
    bool sub_2015D0();
    bool sub_2015E0();
    bool sub_201610();
    bool sub_201640();
    bool sub_201680();
    void sub_2016A0();
    RwInt32 sub_2017E0();
    bool sub_201840();
    void sub_201890();
    void sub_201A70();
    void sub_201C70();
    void sub_201CD0();
    void sub_201D60();
    bool sub_201DF0();
    // Empty: shared through /OPT:ICF.
    void sub_1E41C0();
};

#endif
