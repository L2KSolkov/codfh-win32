/*
 * type_92430: the result of the downward collision query sub_92430, named
 * after that function, which fills it at run time (its callback sub_92540
 * keeps the highest hit). 0x2C bytes: AIData::sub_1BEF0 keeps one on the
 * stack, and its frame fixes the size.
 *
 *   +0x00 unk_00  the hit triangle (from the world sector's triangles)
 *   +0x04 unk_04  the hit's height above the query point (-100000 for none)
 *   +0x08 unk_08  the hit point
 *   +0x14 unk_14  room for the hit triangle's normal ("GetTerrainAngle")
 *   +0x20 unk_20  the sector's vertices; zeroed first, so nonzero means a hit
 */
#ifndef TYPE_92430_H
#define TYPE_92430_H

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "rw/rpcollis.h"
#include "rw/rpatomic.h"
#include "types/type_3D96F0.h"

struct type_92430
{
    void *unk_00;
    RwReal unk_04;
    RwV3d unk_08;
    RwV3d unk_14;               // the hit triangle's normal, when sub_16E740
                                // computes it ("GetTerrainAngle")
    void *unk_20;
    RwUInt32 unk_24[0x2];
};
typedef RwChar type_92430_size_check[sizeof(type_92430) == 0x2C ? 1 : -1];

// A world sector as sub_92540 reads it: its triangles (8 bytes each) and
// its vertices.
struct type_92540_tri
{
    RwUInt16 unk_00[3];         // its vertices
    RwUInt16 unk_06;            // its material, in the sector's window
};
struct type_92540
{
    RwInt32 unk_00;
    type_92540_tri *unk_04;
    RwV3d *unk_08;
    RwUInt8 unk_0C[0x74];
    RwUInt16 unk_80;            // the sector's first material in the world's list
};
// A world as sub_96E30 reads it: its materials.
struct type_96E30
{
    RwUInt8 unk_00[0x10];
    void **unk_10;
};
// A material's game data (the plugin sub_FC020 registers, found by
// sub_FC000): its surface id in the low 16 bits of unk_04 (0xFFFF none)
// and its flags in the high 16.
// It is the material extension type_3D970C (types/type_3D96F0.h).
typedef type_3D970C type_FC000;
type_FC000 *sub_FC000(void *arg_0);
// RenderWare's line-triangle test (unit_08AB60): whether the line from arg_0
// along arg_4 crosses the triangle arg_8, arg_C, arg_10, how far along in
// *arg_14.
RwInt32 sub_92620(RwV3d *arg_0, RwV3d *arg_4, RwV3d *arg_8, RwV3d *arg_C, RwV3d *arg_10, RwReal *arg_14);
// The query's point and how far above it a hit may be (sub_92430 sets them
// for its callback).
extern RwV3d dword_4B25A0;
extern RwReal flt_4B25AC;
// A collision search's context (0xB4 bytes on the stack of sub_948A0,
// sub_950C0, sub_96EF0 and others; sub_95030 sets it up): the world, what
// sub_96680 flushes the gathered triangles to, the materials it skips and
// the last surface seen.
struct type_93DF0
{
    RpWorld *unk_00;            // the world being searched
    struct type_3D3548 *unk_04; // the entity moving
    struct type_3D3548 *unk_08; // the entity hit
    struct type_758F0 *unk_0C;  // the explosion (sub_9A860)
    RpAtomic *unk_10;           // the atomic hit
    RwFrame *unk_14;            // the moving entity's frame (sub_D42D0)
    RwMatrix *unk_18;           // its matrix
    RwMatrix *unk_1C;           // the atomic's matrix, orthonormalised,
    RwMatrix *unk_20;           // and its inverse (sub_946B0)
    RwReal unk_24;              // the squared search radius (sub_D42D0)
    RwReal unk_28;              // the nearest hit's squared distance (0: none)
    union
    {
        RwInt32 unk_2C[7];
        struct
        {
            RwV3d unk_2C_v;     // the nearest point (type_10F710's world
                                // triangle callback, sub_104B30)
            RwReal unk_38[3];   // a blast's inverse squared radii (sub_9A960)
            RwReal unk_44;      // the hit's ellipsoid distance (sub_929A0)
        };
    };
    RwReal unk_48;              // the height a floor must be above (sub_929A0)
    RwReal unk_4C;              // the mover's radius (sub_974A0, sub_98200)
    RwInt32 *unk_50;
    struct type_3D3548 *unk_54; // the entity stood on (sub_93700)
    RpAtomic *unk_58;           // an atomic to stand on (sub_950C0)
    RwInt32 unk_5C;             // something was hit
    RwInt32 unk_60;
    RwInt32 unk_64;
    RwInt32 unk_68;
    RwV3d *unk_6C;              // an offset the sphere follows (sub_929A0)
    RwInt32 unk_70;             // the search's id (sub_8F940)
    RwUInt32 unk_74;            // material flags to skip
    RwInt32 unk_78;             // the last triangle's surface (-1 none)
    struct type_3DAFC8_1DDC *unk_7C; // the contact records (sub_948A0's arg_2C)
    RwReal *unk_80;             // where the ground height goes (sub_96680)
    RwReal unk_84;              // the side radius (sub_96EF0)
    RwInt32 unk_88;
    RwReal unk_8C;              // the step height (sub_96680)
    RwInt32 unk_90;
    RwReal unk_94;
    union
    {
        struct
        {
            RwInt32 unk_98;
            RwInt32 unk_9C;
            RwInt32 unk_A0;
        };
        RwV3d unk_98_v;         // the nearest hit's normal (sub_93700)
    };
    union
    {
        struct
        {
            RwInt32 unk_A4;
            RwInt32 unk_A8;
            RwInt32 unk_AC;
        };
        RwV3d unk_A4_v;         // and its point
    };
    RwInt32 unk_B0;

    type_93DF0();
};
// Gathers each triangle not of a skipped material (sub_96EF0's world
// query callback).
RpCollisionTriangle *sub_96E30(RpIntersection *arg_0, RpWorldSector *arg_4, RpCollisionTriangle *arg_8,
                               RwReal arg_C, void *arg_10);
// Gathers the triangle arg_0 (its vertices) with the normal arg_4 into
// dword_4B25C0 and dword_4B56F8, flushing them through sub_96680 at 350.
void sub_93DF0(RwV3d **arg_0, RwV3d *arg_4, type_93DF0 *arg_8, RpIntersection *arg_C);
void sub_96680(type_93DF0 *arg_0, RpIntersection *arg_4, RwReal arg_8, RwReal *arg_C, RwReal arg_10);
// The entity arg_0's collision (unit_08AB60); arg_30 is unused (the
// player's collision step passes 0).
void sub_96EF0(struct type_3D3548 *arg_0, RwFrame *arg_4, RwV3d *arg_8, RwReal arg_C, RwInt32 *arg_10,
               RwV3d *arg_14, RwReal *arg_18, RwInt32 *arg_1C, RwInt32 *arg_20, RwInt32 *arg_24,
               RwReal arg_28, RwReal arg_2C, RwInt32 arg_30);
extern RwInt32 dword_4B25BC;
// The entity collision searches around the entity arg_0's frame arg_4 (the
// sphere arg_8 of radius arg_C, the radii arg_14): whether it stands, the
// ground height, the ceiling, a hit, an entity and a wall into arg_10, arg_18
// and arg_1C to arg_28, the contacts into arg_2C; sub_985B0 is the soldier's
// (arg_30: the full search). type_3D3548::vf_044 runs them.
void sub_948A0(struct type_3D3548 *arg_0, RwFrame *arg_4, RwV3d *arg_8, RwReal arg_C, RwInt32 *arg_10,
               RwV3d *arg_14, RwReal *arg_18, RwInt32 *arg_1C, RwInt32 *arg_20, RwInt32 *arg_24,
               RwInt32 *arg_28, struct type_3DAFC8_1DDC *arg_2C);
void sub_985B0(struct type_3D3548 *arg_0, RwFrame *arg_4, RwV3d *arg_8, RwReal arg_C, RwInt32 *arg_10,
               RwV3d *arg_14, RwReal *arg_18, RwInt32 *arg_1C, RwInt32 *arg_20, RwInt32 *arg_24,
               RwInt32 *arg_28, struct type_3DAFC8_1DDC *arg_2C, RwInt32 arg_30);
// sub_948A0's atomic and collision world callbacks.
RpAtomic *sub_943E0(RpIntersection *arg_0, RpWorldSector *arg_4, RpAtomic *arg_8, RwReal arg_C, void *arg_10);
RpCollisionTriangle *sub_929A0(RpIntersection *arg_0, RpWorldSector *arg_4, RpCollisionTriangle *arg_8,
                               RwReal arg_C, void *arg_10);
// sub_985B0's triangle callback.
RpCollisionTriangle *sub_98200(RpIntersection *arg_0, RpWorldSector *arg_4, RpCollisionTriangle *arg_8,
                               RwReal arg_C, void *arg_10);
// sub_950C0's.
RpAtomic *sub_946B0(RpIntersection *arg_0, RpWorldSector *arg_4, RpAtomic *arg_8, RwReal arg_C, void *arg_10);
RpCollisionTriangle *sub_930F0(RpIntersection *arg_0, RpWorldSector *arg_4, RpCollisionTriangle *arg_8,
                               RwReal arg_C, void *arg_10);
// Set to 150 by each sphere search (sub_948A0).
extern RwInt32 dword_4B25B8;
extern RwV3d dword_4B25C0[350 * 3];
extern RwV3d dword_4B56F8[350];
// An atomic's triangle taken into the world (sub_93700), and the pointers
// to its three points (.data, pointing into it).
extern RwV3d dword_4B6768[3];
extern RwV3d *dword_4290F4[3];
// The same for a soldier's query (sub_97790).
extern RwV3d dword_4B678C[3];
extern RwV3d *dword_429100[3];
// Whether the sphere at arg_4 of radius arg_8 touches the triangle arg_C
// (three vertices) of normal arg_10; its nearest point into *arg_0.
RwInt32 sub_95C70(RwV3d *arg_0, RwV3d *arg_4, RwReal arg_8, RwV3d *arg_C, RwV3d *arg_10);
// The point of the triangle arg_0 (normal arg_4) nearest *arg_8, into
// *arg_8; returns its squared distance.
RwReal sub_8F960(RwV3d **arg_0, RwV3d *arg_4, RwV3d *arg_8);
// Whether the heights of the three points span 50 or more (sub_98200).
RwInt32 sub_92FB0(RwV3d *arg_0, RwV3d *arg_4, RwV3d *arg_8);
// Pushes a sphere out of the gathered triangles (sub_98200, sub_985B0).
void sub_974A0(type_93DF0 *arg_0, RwV3d *arg_4, RwReal arg_8);
extern RwInt32 dword_4B6760;
// A vertical probe's result (sub_99280's data): whether a hit was found
// above and below the reference height unk_10, the nearest of each and
// their surfaces, and the world searched.
struct type_99130
{
    RwInt32 unk_00;             // a hit above
    RwInt32 unk_04;             // a hit below
    RwReal unk_08;              // the lowest hit above
    RwReal unk_0C;              // the highest hit below
    RwReal unk_10;              // the reference height
    struct type_3D3548 *unk_14; // the entity asking (sub_948A0)
    RwInt32 unk_18;             // the surface above
    RwInt32 unk_1C;             // the surface below
    RpWorld *unk_20;
};
// Files the hit at arg_0 along the line arg_4 above or below.
void sub_99130(RwReal arg_0, RpIntersection *arg_4, type_99130 *arg_8, RpWorldSector *arg_C,
               RpCollisionTriangle *arg_10);
// The surface of the triangle arg_8 of the sector arg_4 (-1 for none). An
// inline function the compiler does not expand (sub_99130 keeps 8 bytes for
// each of its two calls; docs/toolchain.md).
inline RwInt32 sub_991F0(type_99130 *arg_0, RpWorldSector *arg_4, RpCollisionTriangle *arg_8);
RpCollisionTriangle *sub_99280(RpIntersection *arg_0, RpWorldSector *arg_4, RpCollisionTriangle *arg_8,
                               RwReal arg_C, void *arg_10);
// The flags of the materials the entity arg_0 passes through (by its kind).
RwUInt32 sub_9A800(struct type_3D3548 *arg_0);
// An explosion search's atomic callback: tells each entity it reaches once.
RpAtomic *sub_9A860(RpIntersection *arg_0, RpWorldSector *arg_4, RpAtomic *arg_8, RwReal arg_C,
                    void *arg_10);
// Whether arg_0 is less than arg_8 from arg_4.
RwInt32 sub_9ACE0(RwV3d *arg_0, RwV3d *arg_4, RwReal arg_8);
// The callback: keeps the highest hit up to flt_4B25AC above dword_4B25A0.
RpCollisionTriangle *sub_92540(RpIntersection *arg_0, RpWorldSector *arg_4, RpCollisionTriangle *arg_8,
                               RwReal arg_C, void *arg_10);

#endif
