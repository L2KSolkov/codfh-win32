/*
 * The surfaces' particle events: four tables (bullet, tank shell, artillery
 * shell and anti-tank impacts), each of records pairing a surface id with
 * the name of its list of particle systems. The global data loader fills
 * them from "Surfaces+Particles+ParticleEvents+..." (sub_F2680); sub_F2750
 * spawns a surface's list.
 */
#ifndef GAME_SURFACEPARTICLES_H
#define GAME_SURFACEPARTICLES_H

#include "rw/ostypes.h"
#include "rw/bamatrix.h"
#include "types/type_72810.h"

// A table's record: the surface id and its list's name.
struct type_4BC894
{
    RwInt32 unk_00;
    type_73050 unk_04;
};

// A particle system list, as sub_198900 returns it by name: only its count
// and its systems (the ids sub_F2FF0 takes) are known.
struct type_F2750
{
    RwInt32 unk_00[4];
    RwInt32 unk_10;
    RwInt32 *unk_14;
};

// The four tables and their records' counts.
extern type_4BC894 *dword_4BC894[4];
extern RwInt32 dword_4BC8A4[4];

// What the global data loader's sub_1989D0 returns: only where it stores
// the list's count and records is known.
struct type_1989D0
{
    RwInt32 unk_00[4];
    RwInt32 *unk_10;
    type_4BC894 **unk_14;
};

// Clears, frees and registers the tables (sub_F25F0, sub_F2630, sub_F2680).
void sub_F25F0();
void sub_F2630();
void sub_F2680();
// Spawns the list of the table arg_0 (0 to 3) for the surface arg_4 at the
// matrix arg_8 (arg_C: the systems' last flag); 0 when there is none.
RwInt32 sub_F2750(RwInt32 arg_0, RwInt32 arg_4, RwMatrix *arg_8, RwInt32 arg_C);

#endif
