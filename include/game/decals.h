/*
 * The decal system: up to 64 decals (a ring, dword_4B9E7C the next slot and
 * dword_4B9E80 the count), drawn as one PTank atomic of camera-facing
 * matrices with texture coordinates into the 32-pixel cells of the texture
 * "decals" from the level's dictionary.
 */
#ifndef GAME_DECALS_H
#define GAME_DECALS_H

#include "rw/ostypes.h"
#include "rw/bamatrix.h"
#include "rw/batextur.h"
#include "rw/rpptank.h"

// The PTank atomic and the level's texture dictionary (the database's
// names).
extern RpAtomic *atomic;
extern RwTexDictionary *dict;
// The decals' texture coordinates, matrices and ages (2: gone).
extern RwTexCoords *dword_4B9E70;
extern RwMatrix *dword_4B9E74;
extern RwUInt8 *dword_4B9E78;
extern RwUInt32 dword_4B9E7C;
extern RwUInt32 dword_4B9E80;
// The texture's width and height, once found.
extern RwUInt32 dword_4B9E84;
extern RwUInt32 dword_4B9E88;
// The decals' scale across and up (.data).
// unk_4296C0 (one .data object: a lone zero global would be in .bss).
struct type_4296C0
{
    RwReal unk_00;
    RwReal unk_04;
    RwInt32 unk_08;
    RwInt32 unk_0C;
};
extern type_4296C0 unk_4296C0;

// The database's name for its set-up (game code, 0xEFBC0).
extern "C" void RpPrtStdEmitterCreatePTank();
// Its reset (the restart), shutdown, update (the texture, then the active
// decals' coordinates and matrices) and render.
void sub_EFF70();
void sub_F0000();
void sub_F00C0();
void sub_F03F0();
// Adds a decal at the matrix arg_0 in the texture's cell arg_4; arg_8 is
// ignored (the projectiles pass 0: type_3DC7F8::vf_02C).
void sub_F04E0(RwMatrix *arg_0, RwInt32 arg_4, RwInt32 arg_8);
// Turns the matrix arg_0 about the axis *arg_4 by arg_8 degrees; only the
// widths are known.
void sub_140440(RwMatrix *arg_0, RwV3d *arg_4, RwReal arg_8);

#endif
