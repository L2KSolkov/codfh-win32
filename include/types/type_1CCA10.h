/*
 * type_1CCA10: the game's time in milliseconds (sub_1CCA10 returns it).
 */
#ifndef TYPE_1CCA10_H
#define TYPE_1CCA10_H

#include "rw/ostypes.h"

// A time sub_1CCA10 returns (through a hidden pointer, so it has a
// constructor) and the object at 0x4F7EB8 takes after each step of the
// module shutdown (sub_1AF750, with 1 and 0); only the widths are known.
struct type_1CCA10
{
    RwInt32 unk_00;

    // Inline: the network players' constructor (sub_1A6140) clears their
    // times through a `this` temporary.
    type_1CCA10()
    {
        unk_00 = 0;
    }
    // Inline too: the network players' debug hook (sub_1A64A0) gets its
    // copy built in place on the stack through a `this` temporary.
    type_1CCA10(const type_1CCA10 &arg_0)
    {
        unk_00 = arg_0.unk_00;
    }
    // An inline accessor for unk_00, with no address and so no database
    // name; named for its field. Evidence: the game event print
    // (sub_1A8A70) reads the returned time through a `this` copy.
    RwInt32 get_unk_00() const
    {
        return unk_00;
    }
    // The same through a result local: an inline with no address, named
    // for what it gives. Evidence: the ping's send (sNetGameEP.cpp,
    // sub_1D7560) copies each time into a slot of its own before its named
    // local.
    RwInt32 ms() const
    {
        RwInt32 r = unk_00;
        return r;
    }
    // The same by reference: an inline with no address, named for its
    // field. Evidence: the game data's level start (sub_1B59F0) converts the
    // returned time from memory through a `this` temporary.
    const RwInt32 &ref_unk_00() const
    {
        return unk_00;
    }
    // The milliseconds from arg_0 to it; inline, with a local of its own
    // (the network player's sub_1A71E0 keeps both).
    RwInt32 operator-(const type_1CCA10 &arg_0) const
    {
        RwInt32 r = unk_00 - arg_0.unk_00;
        return r;
    }
    // The time from arg_0 to it, as a time: an inline with no address,
    // named for what it gives. Evidence: the voice channel's state
    // (sub_1DF990) copies the difference into a time from a result slot of
    // its own.
    type_1CCA10 since(const type_1CCA10 &arg_0) const
    {
        return type_1CCA10(*this - arg_0);
    }
    // The time 0: an inline with no address, named for what it gives.
    // Evidence: the voice channel's start (sub_1DE450) copies a returned
    // zero into its times from a slot of its own.
    static type_1CCA10 zero()
    {
        return type_1CCA10(0);
    }
    // Inline too, with no addresses and so no database names: a time from
    // milliseconds, it arg_0 milliseconds on (with a local of its own),
    // whether it is later than arg_0 milliseconds and whether it equals
    // arg_0. Evidence: the voice chat (sub_1C6700, sub_1C6EC0) keeps the
    // literal each takes in a slot of its own, as a reference parameter
    // gives, and the sum and the difference in locals.
    type_1CCA10(RwInt32 arg_0)
    {
        unk_00 = arg_0;
    }
    type_1CCA10 operator+(const RwInt32 &arg_0) const
    {
        RwInt32 r = unk_00 + arg_0;
        return r;
    }
    // The sum of two times, built straight into the result: the packet
    // engine's receive (sub_1D2CC0) adds a time made from a literal.
    type_1CCA10 operator+(const type_1CCA10 &arg_0) const
    {
        return type_1CCA10(unk_00 + arg_0.unk_00);
    }
    // A time arg_0 milliseconds earlier, and whether it is earlier than
    // arg_0: the players' handlePossibleDisconnections builds the first
    // straight into its local and tests the second through a bool.
    type_1CCA10 operator-(const RwInt32 &arg_0) const
    {
        return type_1CCA10(unk_00 - arg_0);
    }
    bool operator<(const type_1CCA10 &arg_0) const
    {
        return unk_00 < arg_0.unk_00;
    }
    bool operator<(const RwInt32 &arg_0) const
    {
        return unk_00 < arg_0;
    }
    bool operator>(const RwInt32 &arg_0) const
    {
        return unk_00 > arg_0;
    }
    // Whether it is later than arg_0: the players' join step tests its
    // deadlines through a bool.
    bool operator>(const type_1CCA10 &arg_0) const
    {
        return unk_00 > arg_0.unk_00;
    }
    // Whether it is at or after arg_0: the packet engine's step tests its
    // one-second window through a bool.
    bool operator>=(const type_1CCA10 &arg_0) const
    {
        return unk_00 >= arg_0.unk_00;
    }
    bool operator==(const type_1CCA10 &arg_0) const
    {
        return !(unk_00 - arg_0.unk_00);
    }
};

#endif
