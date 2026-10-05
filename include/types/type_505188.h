/*
 * type_505188: an id (-1 when unset) with two strings, ordered and compared
 * by the first; the object at 0x505188 is one (its dynamic initializer is
 * at 0x30DB08) and the shell's lists keep others. Named after that object.
 */
#ifndef TYPE_505188_H
#define TYPE_505188_H

#include <string>

#include "rw/ostypes.h"

// A string that takes a null pointer as "" (its constructor, sub_1A5EA0, is
// defined here but not inlined: type_505188's constructor, sub_1A5E10,
// reserves its expansions' slots; docs/toolchain.md); named after that
// constructor.
struct type_1A5EA0 : std::string
{
    // Empty, inline (the string message's instance, sub_1A34A0).
    type_1A5EA0()
    {
    }
    type_1A5EA0(const RwChar *arg_0) : std::string(arg_0 ? arg_0 : "")
    {
    }
    // A copy of the string arg_0 (unit_1C8110); its std::string copy is out
    // of line at sub_1C85F0 in one call, inlined in the others.
    type_1A5EA0(const std::string &arg_0) : std::string(arg_0)
    {
    }
    // Existing localized temporaries use the constructor entry at
    // sub_1CB6B0 (config/aliases.txt). Its compiled owner is type_1CB670:
    // sub_E3970 constructs this same string storage through its return
    // buffer; the derived type adds no data.
    type_1A5EA0(const RwChar *arg_0, RwInt32 arg_4);
    // Inserts the string arg_4 (or the character arg_4) at arg_0 (at most
    // at its end), and erases arg_4 characters from arg_0.
    type_1A5EA0 &sub_1C8110(RwUInt32 arg_0, const RwChar *arg_4);
    type_1A5EA0 &sub_1C8300(RwUInt32 arg_0, RwChar arg_4);
    type_1A5EA0 &sub_1C8330(RwUInt32 arg_0, RwUInt32 arg_4);
    // Empties it.
    void sub_1C84D0();
    // Appends the string arg_0 (a type_1A5EA0: its callers convert C strings
    // and substrings into temporaries of it first), or the number arg_0 in
    // decimal.
    type_1A5EA0 &sub_1C84F0(const type_1A5EA0 &arg_0);
    // The C string arg_0 appended (through a temporary of it).
    type_1A5EA0 &sub_1CA470(const RwChar *arg_0);
    type_1A5EA0 &sub_1C8540(RwInt32 arg_0);
    type_1A5EA0 &sub_1C85D0(RwInt32 arg_0);
    // Likewise, returning itself after the append (sub_21E3E0 appends a
    // rounded value clamped at 0).
    type_1A5EA0 &sub_214A70(RwInt32 arg_0);
    // The same over sub_1C85D0 (the host options' constructor and the weapon
    // page's texts, sub_223D00, call it).
    type_1A5EA0 &sub_202430(RwInt32 arg_0);
    // The same, returning sub_1C85D0's result (the pause menu's loading,
    // sub_21BD60, appends the map's number with it).
    type_1A5EA0 &sub_21CA90(RwInt32 arg_0);
    // The number arg_0 and the text arg_0 (a copy) appended, returning it:
    // out of line and shared (the game browser's rows, sub_205070 and
    // sub_223D00 call them).
    type_1A5EA0 &sub_1FBB70(RwUInt8 arg_0);
    type_1A5EA0 &sub_1FBB90(struct type_1CB670 arg_0);
};

// Appends arg_4 to arg_0: an inline with no address, named for what it
// does. Evidence: the searching dots (sub_20EB30) and the scoreboard's
// countdown (sub_21E3E0) keep the appended text's address in a temporary,
// as an inline's reference parameter does, before the append (sub_1C84F0).
inline void add_text(type_1A5EA0 &arg_0, const type_1A5EA0 &arg_4)
{
    arg_0.sub_1C84F0(arg_4);
}
// The number arg_4 appended to arg_0, likewise. Evidence: a scoreboard
// row's texts (sub_21D5A0) keep each count in a slot of their own before
// the append (sub_1C8540).
inline void add_number(type_1A5EA0 &arg_0, RwInt32 arg_4)
{
    arg_0.sub_1C8540(arg_4);
}
// A debug print of a text, compiled out: inlines with no code and no
// address. Evidence: the frames of a vote's question (sub_221A80, after its
// formatting) and of the create session page's fill (sub_205880, after its
// name is set) hold one more inline expansion than their statements give;
// a check or a discarded read there changes the registers instead.
inline void debug_text(const RwChar *arg_0)
{
}
inline void debug_text(const type_1A5EA0 &arg_0)
{
}

struct type_505188
{
    RwInt32 unk_00;
    type_1A5EA0 unk_04;
    type_1A5EA0 unk_20;
    RwInt32 unk_3C;

    type_505188();
    ~type_505188();
    // Inline setters, with no addresses and so no database names; named for
    // their fields. Evidence: the front end's list set-up (sub_1C3D90) sets
    // each through a `this` slot of its own.
    void set_unk_00(RwInt32 arg_0)
    {
        unk_00 = arg_0;
    }
    void set_unk_04(const type_1A5EA0 &arg_0)
    {
        unk_04 = arg_0;
    }
    void set_unk_20(const type_1A5EA0 &arg_0)
    {
        unk_20 = arg_0;
    }
    void set_unk_3C(RwInt32 arg_0)
    {
        unk_3C = arg_0;
    }
    // Its first string (what it is ordered by).
    const type_1A5EA0 &sub_1A5F60() const;
    // Whether it sorts before arg_0, and whether their first strings are
    // equal.
    bool sub_1A5F80(const type_505188 &arg_0) const;
    bool sub_1A5FC0(const type_505188 &arg_0) const;
    // Whether its first string is empty.
    bool sub_1A5FF0() const;
    // Its first word (its number): an out-of-line getter shared through
    // /OPT:ICF (0x1EE9D0).
    RwInt32 sub_1EE9D0() const;
};

// The level standing for any level (the level selector's "Any", sub_211680).
extern type_505188 unk_505188;

#endif
