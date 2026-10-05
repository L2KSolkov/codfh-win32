/*
 * The float constants the game reads by name at the addresses of __real@ literals: the
 * readers load them at run time (a multiply in a double expression, a compare), so they
 * are variables, not literals, yet the image has no copy of their own: each reads the
 * literal another unit's code made first (0.0 and 1.0 unit_012000's, 4.0 unit_03D410's,
 * 3.0 unit_0D48D0's). A definition here (a selectany COMDAT or a const per unit) would be
 * data of its own, which link 7.10 without /OPT:ICF keeps apart, so the names stay
 * declarations and the link resolves each to its literal (/alternatename). Address-named
 * after the literal they share.
 */
#ifndef GAME_POOLEDCONSTS_H
#define GAME_POOLEDCONSTS_H

#include "rw/ostypes.h"

extern const RwReal flt_3CD84C;
extern const RwReal flt_3CD8E0;
extern const RwReal flt_3CE7F4;
extern const RwReal flt_3D7118;

#pragma comment(linker, "/alternatename:?flt_3CD84C@@3MB=__real@00000000")
#pragma comment(linker, "/alternatename:?flt_3CD8E0@@3MB=__real@3f800000")
#pragma comment(linker, "/alternatename:?flt_3CE7F4@@3MB=__real@40800000")
#pragma comment(linker, "/alternatename:?flt_3D7118@@3MB=__real@40400000")

#endif
