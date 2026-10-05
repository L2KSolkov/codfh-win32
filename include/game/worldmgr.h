/*
 * The world manager (unit_171DC0): the section worlds (dword_4E5D30, four
 * slots, and the global section unk_4E5CD8), the default world
 * (dword_4E5C78), the skybox worlds (world, dword_4E5C84, dword_4E5C88),
 * the lights (camera and dword_4E5C98, game/particles.h), the default
 * zone's view (type_4E5BE0 over dword_4E5BE0) and the sections' memory arena (dword_4E5CB0,
 * with the clump and weapon banks' heaps at its start). The database's
 * names world, camera, clump and schema are kept.
 */
#ifndef GAME_WORLDMGR_H
#define GAME_WORLDMGR_H

#include <stddef.h>

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "rw/batextur.h"
#include "rw/rpworld.h"
#include "types/type_4E5D30.h"
#include "types/type_D48D0.h"
#include "types/vec4.h"
#include "game/render.h"

// The default zone as the world manager sees it (sub_171DC0 sets its box
// to +-500000 and clears its three point and value pairs): a view of
// dword_4E5BE0 (types/vec4.h's type_8F3E0), which sub_171DC0 casts to it.
struct type_4E5BE0_20
{
    type_8BEC0 unk_00;
    type_8BEC0 unk_10;
};
struct type_4E5BE0
{
    type_8BEC0 unk_00;          // its box: the least corner
    type_8BEC0 unk_10;          // and the greatest
    type_4E5BE0_20 unk_20[3];
};

// The global section (the database's dword_4E5CD8 is its first field,
// dword_4E5CF8 its world and dword_4E5D00 its collision world).
extern type_4E5D30 unk_4E5CD8;
extern type_D48D0 dword_4E5D1C[4];

#ifdef CODFH_PLAIN
extern RwInt32 &dword_4E5C70;            // set up
#else
extern RwInt32 dword_4E5C70;            // set up
#endif
#ifdef CODFH_PLAIN
extern RwInt32 &dword_4E5C74;            // the main camera (as in
#else
extern RwInt32 dword_4E5C74;            // the main camera (as in
#endif
                                        // types/type_3D3548.h)
extern RwInt32 dword_4E5CC4;            // a block it frees at shutdown
extern RwInt16 word_429EAC;             // the section being loaded
// Starts the UV animations' "VTrack" (as in types/type_3DBC78.h).
struct RtAnimAnimation *sub_159AC0();
#ifdef CODFH_PLAIN
extern RpWorld *&world;                  // the skybox world
#else
extern RpWorld *world;                  // the skybox world
#endif
#ifdef CODFH_PLAIN
extern RwTexDictionary *&dword_4E5C90;   // shared.txd
#else
extern RwTexDictionary *dword_4E5C90;   // shared.txd
#endif
extern RwUInt32 dword_4E5CB0;           // the arena
extern RwInt32 dword_4E5CB8;            // and its size

// RenderWare's free as the arena's hook replaced it (sub_2DA2F0): the arena
// (dword_50F250 to dword_50F254) and the memory functions it saved.
extern "C" RwUInt32 dword_50F250;
extern "C" RwUInt32 dword_50F254;
extern "C" void *(*dword_50F258)(size_t size, RwUInt32 hint);
extern "C" void *(*dword_50F25C)(void *mem, size_t newSize, RwUInt32 hint);
extern "C" void *(*dword_50F260)(size_t numObj, size_t sizeObj, RwUInt32 hint);
extern "C" void (*dword_524488)(void *mem);
extern "C" void sub_2DA2F0(RwUInt32 arg_0, RwUInt32 arg_4);

void sub_171DC0();
void sub_172210();
void sub_172230();
void sub_172430();
void sub_172480();
void sub_1724C0();
void sub_1727E0(RwInt32 *arg_0);
RwInt32 sub_172820();
void sub_172A80();
void sub_172BB0();
struct type_3D96F0;
RwUInt16 sub_172C60(RwFrame *arg_0, type_3D96F0 *arg_4);
RpWorld *sub_172EB0(RwUInt16 arg_0, type_3D96F0 *arg_4);
RwInt32 sub_172F60(RpWorld *arg_0, RpWorld *arg_4);
RpWorld *sub_172FF0(RwInt32 *arg_0, RwFrame *arg_4, type_3D96F0 *arg_8, RpWorld *arg_C);
void sub_173080(RwUInt16 arg_0, type_3D96F0 *arg_4);
RpAtomic *sub_173100(RpAtomic *arg_0, void *arg_4);
RpLight *sub_173140(RpLight *arg_0, void *arg_4);
// The level's light list's head (render.h's dword_4E5C7C) through a local
// of its own: an inline with no address, named for its field. Evidence:
// sub_173800 links the new light to it through a temporary.
inline RpLight *get_4E5C7C()
{
    RpLight *r = dword_4E5C7C;
    return r;
}
// The entity of the clump arg_0 (its extension's, unit_0FB7A0).
struct type_3D3548 *sub_FBBB0(RpClump *arg_0);
RpWorld *sub_173180(RpClump *arg_0);
RpWorld *sub_173320(RpAtomic *arg_0);
RpWorld *sub_173450(RpLight *arg_0);
RpAtomic *sub_1734E0(RpAtomic *arg_0, void *arg_4);
RpLight *sub_173540(RpLight *arg_0, void *arg_4);
RpWorld *sub_1735A0(RpClump *arg_0);
RpWorld *sub_173620(RpAtomic *arg_0);
RpClump *sub_173680(RpClump *arg_0, void *arg_4);
RpLight *sub_1736A0(RpLight *arg_0, void *arg_4);
RpAtomic *sub_1736C0(RpAtomic *arg_0, void *arg_4);
RpWorldSector *sub_1736E0(RpWorldSector *arg_0, void *arg_4);
void sub_173700(RpWorld *arg_0);
void sub_173750();
struct RpLight;
RwInt32 sub_1738D0(RpLight *arg_0);
void sub_1739C0();
// The definitions' own prototypes (their callers declare the section as
// signed: types/type_141C10.h, types/asynchload.h).
void sub_173BE0(RpWorld *arg_0, RwInt32 arg_4, RwUInt16 arg_8, RwUInt16 arg_C);
RwInt32 sub_173CE0(RpWorld *arg_0, RwInt32 arg_4, RwUInt16 arg_8);
RpMaterial *sub_173F30(RpMaterial *arg_0, void *arg_4);
type_4E5D30 *sub_173F50(RwUInt16 arg_0);
void sub_174030(RwUInt16 arg_0, RwInt32 arg_4);
RpMaterial *sub_1742B0(RpMaterial *arg_0, void *arg_4);
RwInt32 sub_1742D0(RwTexDictionary *arg_0, RwUInt16 arg_4);
void sub_174580(struct type_3D3548 *arg_0, RwInt32 arg_4);
void sub_1745C0(struct type_3D3548 *arg_0, RwInt32 arg_4);
RwInt32 sub_1745F0(RwInt32 arg_0);
// The section lock (types/asynchload.h, which clashes with <xtl.h>).
extern RTL_CRITICAL_SECTION dword_44BFB8;
void sub_1744A0();
void sub_174530();
void sub_1746B0();

#endif
