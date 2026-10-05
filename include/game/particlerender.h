/*
 * The particle renderer (unit_19E500; game/particles.h has the systems): its shader ("d:\particle.xvu"), four
 * sets of eight spinning matrices, a table of random offsets, the camera's
 * matrix it draws with, and the render states it keeps and puts back.
 */
#ifndef GAME_PARTICLERENDER_H
#define GAME_PARTICLERENDER_H

#include <xtl.h>
#include <d3dx8.h>

#include "rw/ostypes.h"
#include "rw/bamatrix.h"
#include "rw/baengine.h"
#include "rw/baframe.h"
#include "game/particles.h"
#include "types/type_F3130.h"

// What the two point setters (sub_19E9B0, sub_19E9E0) write: two points at
// +0x10 and +0x20; only those are known.
struct type_19E9B0
{
    RwUInt8 unk_00[0x10];
    RwV3d unk_10;
    RwUInt8 unk_1C[0x4];
    RwV3d unk_20;
};

// A sprite system's shader state (the systems' type_F2FF0_60 as sub_19EC70
// fills it, 0xF0 bytes): the count, which terms are set (flags 1, 2, 8,
// 0x10), then vectors of four: a spin and its other axis, the start speed
// and the gravity, the direction in the camera's frame, a second speed, the
// position, the times, sizes and three colours (0 to 1).
struct type_19EC70
{
    RwInt32 unk_00;             // the particle count
    RwUInt32 unk_04;            // the terms set
    RwUInt8 unk_08[0x8];
    RwReal unk_10[4];
    RwReal unk_20[4];
    RwReal unk_30[4];
    RwReal unk_40[4];
    RwReal unk_50[4];
    RwReal unk_60[4];
    RwReal unk_70;
    RwReal unk_74;              // one over the life in frames
    RwReal unk_78;
    RwUInt32 unk_7C;            // a random phase (0 to 128)
    RwReal unk_80[4];
    RwReal unk_90[4];
    RwReal unk_A0[4];           // the start colour
    RwReal unk_B0[4];           // the middle colour
    RwReal unk_C0[4];           // the end colour
    RwInt32 unk_D0;
    D3DVertexBuffer *unk_D4;    // four vertices a particle (sub_19F840)
    RwInt32 unk_D8;
    RwInt32 unk_DC;
    struct type_F3130 *unk_E0; // its definition
    RwUInt32 unk_E4;            // 1: the standard rate; 2: and dword_4C19A8
    RwUInt8 unk_E8[0x8];
};
extern RwInt32 dword_4C19A8;
void sub_19F5B0(type_F2FF0_60 *arg_0);
void sub_19F540(RwReal *arg_0);
void sub_19F600(RwReal *arg_0);
// A particle's vertex (0x18 bytes): its age, its corner, its index (0 to 7)
// and a random offset.
struct type_19F840_v
{
    RwReal unk_00;
    RwReal unk_04;
    RwReal unk_08;
    RwReal unk_0C;
    RwReal unk_10;
    RwReal unk_14;
};
// The ambient colour the particles are lit by (sub_19F540).
extern RwRGBA stru_4CF768;
// Whether a system draws in its own frame (its unk_E4 flag 1, or the draw
// flag 0x40); arg_8 is not read.
RwInt32 sub_1A0830(type_19EC70 *arg_0, RwUInt32 arg_4, struct type_F2FF0 *arg_8);
// Draws the particles with the spin set arg_8 (off_42C790's).
void sub_1A0860(type_19EC70 *arg_0, struct type_F2FF0 *arg_4, RwInt32 arg_8, RwUInt32 arg_C);
// The live particles' first quad and count (arg_8 and arg_4).
void sub_1A15C0(type_19EC70 *arg_0, RwInt32 *arg_4, RwInt32 *arg_8);
void sub_19F840(type_19EC70 *arg_0);

// The spinning matrices: each set's eight turn about z at the rates
// flt_42C7D4 (the first two sets) and flt_42C7B4 (the third) give them.
extern RwMatrix dword_4F48B0[8];
extern RwMatrix dword_4F4AB0[8];
extern RwMatrix dword_4F4D80[8];
extern RwMatrix dword_4F4F80[8];
extern RwReal flt_42C7B4[8];
extern RwReal flt_42C7D4[8];
// The four spin sets, as sub_1A0860 picks them.
extern RwMatrix *off_42C790[4];
extern RwReal flt_4F5180[0x200];    // random offsets from -0.5 to 0.5
extern DWORD dword_4F4CF0;          // the particles' vertex shader
extern DWORD dword_42C7A0[];        // and its declaration
extern RwMatrix dword_4F4D00;       // the camera's matrix, flags cleared
extern void *dword_4F5A00;          // the camera
extern void *dword_4F5A04[11];      // the render states put back

void sub_19E9B0(type_19E9B0 *arg_0, RwV3d *arg_4);
void sub_19E9E0(type_19E9B0 *arg_0, RwV3d *arg_4);
// The frame's clip planes (the near one at least 20), field of view and
// aspect, the view matrix and the three projections sub_19FB20 builds (near
// planes nearClip, 160 and 1).
extern RwReal nearClip;
extern RwReal flt_42C784;
extern RwReal flt_42C788;
extern RwReal flt_42C78C;
extern D3DMATRIX stru_4F59C0;
extern D3DMATRIX stru_4F5980;
extern D3DMATRIX stru_4F4D40;
extern D3DMATRIX stru_4F4CB0;
void sub_19FB20();

#endif
