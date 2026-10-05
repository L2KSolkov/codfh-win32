/*
 * Small math inlines of the game's own, with no addresses and so no
 * database names; each is named for what it computes.
 */
#ifndef GAME_MATHUTIL_H
#define GAME_MATHUTIL_H

#include <math.h>

#include "rw/ostypes.h"

// The tangent of x, taken by reference. Evidence: CMountedWeaponBehavior's
// HandleAttributes (sub_A4B00) copies its local angle into a temporary
// before loading it for tan, as the compiler does for a const reference
// argument (docs/toolchain.md); by value it is substituted.
inline RwReal tan_ref(const RwReal &x)
{
    return tanf(x);
}
// Likewise the cosine. Evidence: PlayerTrigger's HandleAttributes (sub_AA400,
// command 18) copies its angle into a temporary before loading it for cos.
inline RwReal cos_ref(const RwReal &x)
{
    return cosf(x);
}
// Likewise the sine. Evidence: the player's lean (sub_1116A0) copies the
// sway's angle into a temporary before loading it for sin.
inline RwReal sin_ref(const RwReal &x)
{
    return sinf(x);
}
// Likewise the magnitude, as a float. Evidence: the weapon copy's fire
// (type_10F710_1A48::vf_018) copies the recoil line's end into a temporary
// before loading it for fabs, and keeps the result in one of its own.
inline RwReal fabs_ref(const RwReal &x)
{
    return (RwReal)fabs(x);
}
// The quotient y / x, taken by value. Evidence: the player's lean
// (sub_1116A0) loads the divisor before the dividend and divides reversed,
// as an inline's arguments (right to left) give.
inline RwReal ratio(RwReal y, RwReal x)
{
    return y / x;
}

#endif
