/*
 * The clones (unit_122FB0): many copies of a few atomics, drawn at the
 * matrices a level's clone file lists. The clump ("CloneID" user data on
 * each atomic's geometry names its slot in dword_4CEAE0) comes from the
 * level stream (sub_123440); the file (sub_123280) is kept whole in
 * dword_4CEAB0 and read through offsets from its start. Files from version
 * 0x10001 on can carry their own vertex and index data, drawn with the
 * vertex shaders "d:\clones.xvu" (lit) and "d:\clonesPL.xvu" (prelit).
 */
#ifndef GAME_CLONES_H
#define GAME_CLONES_H

#include <xtl.h>
#include <d3dx8.h>
#include <xgmath.h>

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "rw/bamatrix.h"
#include "rw/rpatomic.h"
#include "rw/rplight.h"
#include "rw/bastream.h"
#include "rw/batextur.h"
#include "rw/rpmesh.h"

// The part of the Xbox driver's raster extension the clones read: a flag
// byte at +0x12 (sub_123A80 counts the meshes whose textures' top-level
// rasters have it set; any puts the group in the second pass).
struct type_123A80
{
    RwUInt8 unk_00[0x12];
    RwUInt8 unk_12;
};

// A clone's mesh in a file's own data (at a record's unk_48, after its
// vertices): the material (filled in on first use, sub_124250), and the
// indices of a triangle strip, padded to an even count.
struct type_124250
{
    RpMaterial *unk_00;
    RwInt32 unk_04;             // how many indices
    RwUInt16 unk_08[1];
};

// A copy's place: its matrix, then (from the files with their own data) a
// value handed to the lit shader and its bounding radius (sub_1243F0).
struct type_1243F0
{
    RwMatrix unk_00;
    RwV3d unk_40;
    RwReal unk_4C;
};

// A group of copies of one clone (sub_1231F0 finds the first of a level
// section's): the clone, how many copies, the lighting to draw them with,
// where the copies are, and how it is drawn. Groups follow one another
// until a clone of 0.
struct type_1231F0
{
    RwInt32 unk_00;             // the clone (its slot in dword_4CEAE0)
    RwInt32 unk_04;             // how many copies
    RwRGBAReal unk_08;          // the ambient colour
    RwRGBAReal unk_18;          // the directional light's colour
    RwV3d unk_28;               // its direction
    RwInt32 unk_34;             // the copies (an offset in the file)
    RwInt16 unk_38;             // lit (with the ambient and directional)
    RwInt16 unk_3A;             // the pass it is drawn in (-1 until chosen)
    RwInt32 unk_3C;             // the next group (an offset)
    RwInt32 unk_40;             // how many vertices (0x30 bytes each)
    RwInt32 unk_44;             // how many meshes
    RwInt32 unk_48;             // the vertices and meshes (an offset)
    RwInt32 unk_4C;             // how many times to draw each copy (0: once)
    RwUInt8 unk_50[0xC];
    RwInt32 unk_5C;             // the radius scale
    D3DVertexBuffer *unk_60;    // its vertex buffer (sub_124290)
    RwInt32 unk_64;             // the next group (an offset; with own data)
    RwUInt8 unk_68[0x8];
    type_1243F0 unk_70[1];      // the copies (before version 0x10001)
};

// The file: its version (0x10001 on; older files start with the count),
// how many level sections it covers (the top bit set when it carries its
// own data), and each section's first group (offsets).
extern RwUInt8 *dword_4CEAB0;
extern RwInt32 dword_4CEA90;        // its version (0 for the older files)
extern RwInt32 dword_4CEAAC;        // whether it carries its own data
extern RpClump *dword_4CEAB4;       // the clump
extern RpAtomic *dword_4CEAE0[500]; // the clones by their "CloneID"
extern RwInt32 dword_4CF300;        // how many there are

// The two lights the file's groups are lit with (an ambient and a
// directional) and the frame the copies are drawn at.
extern RpLight *dword_4CEAA8;
extern RpLight *dword_4CF308;
extern RwFrame *frame;

// The vertex shaders (lit and prelit), and the view and projection the
// first shaded copy of a pass sets up.
extern DWORD vertexShader;
extern DWORD dword_4CEA84;
extern D3DMATRIX pM2;
extern D3DMATRIX stru_4CF340;

// The draw's state: whether the clones pass is running, the atomic being
// drawn and whether it is lit, the lights' colours and direction it set
// (and those of the view light and ambient it saved), and the counts it
// hands on (dword_4F309C, dword_4F30A0).
extern RwInt32 dword_4CEA80;
extern RpAtomic *dword_4CEA8C;
extern RwInt32 dword_4CF30C;
extern RwRGBAReal dword_4CEAC8;
extern RwV3d dword_4CEAB8;
extern RwRGBAReal stru_4CEA70;
extern RwRGBAReal stru_4CEA94;
extern RwMatrix stru_4CF2C0;
extern RwInt32 dword_4CEAC4;        // copies drawn
extern RwInt32 dword_4CF310;        // copies tested
extern RwInt32 dword_4CEAA4;
extern RwInt32 dword_4CF2B0;
extern RwInt32 dword_4CEAD8;
extern RwInt32 dword_4CF2BC;
extern RwInt32 dword_4CF32C;        // set while the clump is replaced
extern RwInt32 dword_4CF31C;        // no clones at all
extern RwInt32 dword_4CF324;        // no prelit clones
extern RwInt32 dword_4CF328;        // no lit clones
extern RwInt32 dword_4CF330;        // draw through RenderWare, not the shaders
extern RwInt32 dword_4CF334;        // every group in the second pass
extern RwInt32 dword_4CF338;        // every group in the first pass
extern RwInt32 dword_4CEA88;        // the mesh sub_124250 looks for
extern RwInt32 dword_4CF304;        // and its count so far

// Handed on after the pass: the copies drawn and tested.
extern RwInt32 dword_4F309C;
extern RwInt32 dword_4F30A0;
// The alpha reference the clones are drawn with (the directional light's
// colour scale is dword_4F30A8's unk_04, game/lightscales.h).
extern RwInt32 dword_4F3080;

#include "game/lightscales.h"
// A pre-transformed textured vertex of the full-screen quad (sub_19B6D0):
// position, rhw, colour and texture coordinates (D3DFVF_XYZRHW, _DIFFUSE,
// _TEX1).
struct type_19B6D0_v
{
    RwReal unk_00;
    RwReal unk_04;
    RwReal unk_08;
    RwReal unk_0C;
    RwUInt32 unk_10;
    RwReal unk_14;
    RwReal unk_18;
};

// The vertex declarations of the two shaders (.data).
extern DWORD dword_429B7C[];
extern DWORD dword_429B94[];

// Loads the vertex shader arg_0 with the declaration arg_4 into arg_8.
void sub_19F790(const RwChar *arg_0, DWORD *arg_4, DWORD *arg_8);
// The level's texture dictionary.
RwTexDictionary *sub_174520();

// The view light's default up (0, 1, 0) and the one for a light straight
// up or down (.rdata; sub_123AF0).
extern const RwV3d stru_3DA784;
extern const RwV3d stru_3DA790;

void sub_122FB0();
void sub_1230F0();
type_1231F0 *sub_1231F0(RwInt32 arg_0);
void sub_123280(RwStream *arg_0, RwUInt32 arg_4);
void sub_123440(RwStream *arg_0);
void sub_1234D0(RwInt32 arg_0);
void sub_123980();
void sub_1239B0(type_1231F0 *arg_0, RwInt32 arg_4);
RpMesh *sub_123A80(RpMesh *arg_0, RpMeshHeader *arg_4, void *arg_8);
void sub_123AF0(RpAtomic *arg_0, RwInt32 arg_4, RwRGBAReal *arg_8, RwRGBAReal *arg_C,
                RwRGBAReal *arg_10, RwV3d *arg_14);
void sub_123FE0(type_1243F0 *arg_0, RwInt32 arg_4, type_1231F0 *arg_8);
type_1231F0 *sub_1241D0(type_1231F0 *arg_0);
RpMesh *sub_124210(RpMesh *arg_0, RpMeshHeader *arg_4, void *arg_8);
void sub_124250(type_124250 *arg_0, RwInt32 arg_4);
void sub_124290();
void sub_1243F0(type_1231F0 *arg_0);
void sub_1245D0(type_1231F0 *arg_0, type_1243F0 *arg_4);
void sub_124D70();

#endif
