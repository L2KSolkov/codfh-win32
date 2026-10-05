/*
 * A point the network messages carry (game/netmsg.h), also two of the
 * multiplayer manager's members (game/gameloop.h): its own header so both
 * can hold it.
 */
#ifndef GAME_NETVEC_H
#define GAME_NETVEC_H

#include "rw/ostypes.h"
#include <math.h>

// A point some messages carry, zeroed by its inline constructor (the
// decoders, as sub_1A38D0, clear it through a `this` temporary).
struct type_1F8560_v
{
    RwReal unk_00;
    RwReal unk_04;
    RwReal unk_08;

    type_1F8560_v()
    {
        unk_00 = 0;
        unk_04 = 0;
        unk_08 = 0;
    }
    // Its arithmetic: inlines with no addresses. Evidence: the network
    // player's motion curves (unit_1FA6E0) build each result through the
    // three components' temporaries, z first, and copy it on.
    type_1F8560_v(RwReal arg_0, RwReal arg_4, RwReal arg_8)
    {
        unk_00 = arg_0;
        unk_04 = arg_4;
        unk_08 = arg_8;
    }
    type_1F8560_v operator+(const type_1F8560_v &arg_0) const
    {
        return type_1F8560_v(unk_00 + arg_0.unk_00, unk_04 + arg_0.unk_04, unk_08 + arg_0.unk_08);
    }
    type_1F8560_v operator-(const type_1F8560_v &arg_0) const
    {
        return type_1F8560_v(unk_00 - arg_0.unk_00, unk_04 - arg_0.unk_04, unk_08 - arg_0.unk_08);
    }
    type_1F8560_v operator-() const
    {
        return type_1F8560_v(-unk_00, -unk_04, -unk_08);
    }
    type_1F8560_v operator/(RwReal arg_0) const
    {
        return type_1F8560_v(unk_00 / arg_0, unk_04 / arg_0, unk_08 / arg_0);
    }
    // In-place sum and division: inlines with no addresses. Evidence: the
    // spawn lists' centre pick (sub_1C1820) sums the players' positions and
    // divides by their count in place.
    void operator+=(const type_1F8560_v &arg_0)
    {
        unk_00 += arg_0.unk_00;
        unk_04 += arg_0.unk_04;
        unk_08 += arg_0.unk_08;
    }
    void operator/=(RwReal arg_0)
    {
        unk_00 /= arg_0;
        unk_04 /= arg_0;
        unk_08 /= arg_0;
    }
    RwReal dot(const type_1F8560_v &arg_0) const
    {
        return unk_00 * arg_0.unk_00 + unk_04 * arg_0.unk_04 + unk_08 * arg_0.unk_08;
    }
    // Whether every component is within flt_3E134C (0.01) of zero.
    RwInt32 sub_1A6D70();
    // Its length (the remote player's state, sub_1BF0C0).
    RwReal sub_1BF590();
    // Its length again, as an inline: VC7.1 declines to expand it, so its
    // callers keep a slot for its local and call its out-of-line copy,
    // which /OPT:ICF folds into sub_1BF590 (aliased). Evidence: the spawn
    // lists' distance picks (sub_1C16B0, sub_1C1820, sub_1C1A40) hold that
    // never-written slot after the difference's temporaries.
    RwReal len()
    {
        return (RwReal)sqrt((RwReal)(unk_00 * unk_00 + unk_04 * unk_04 + unk_08 * unk_08));
    }
    // It scaled to unit length: an inline with no address and so no
    // database name, named for what it gives. Evidence: the remote player's
    // state (sub_1BF0C0) keeps the scale, the copy and the result in slots
    // after its own.
    type_1F8560_v normal()
    {
        RwReal f = 1.0f / sub_1BF590();
        type_1F8560_v r = *this;

        r.unk_00 *= f;
        r.unk_04 *= f;
        r.unk_08 *= f;
        return r;
    }
};
inline type_1F8560_v operator*(RwReal arg_0, const type_1F8560_v &arg_4)
{
    return type_1F8560_v(arg_0 * arg_4.unk_00, arg_0 * arg_4.unk_04, arg_0 * arg_4.unk_08);
}
extern const RwReal flt_3E134C;

#endif
