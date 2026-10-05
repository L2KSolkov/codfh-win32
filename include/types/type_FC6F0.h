/*
 * type_FC6F0: the line test's atomic-pass hit, anchored at the triangle
 * callback sub_FC6F0 that fills it (src/recovered/unit_0FD730.cpp).
 */
#ifndef TYPE_FC6F0_H
#define TYPE_FC6F0_H

#include "rw/ostypes.h"
#include "rw/bamatrix.h"

// The atomic pass's hit (sub_FC8F0 builds it for sub_FC6F0 on its stack
// with the atomic's matrices, and hands the hit out as a type_91F40, point
// and normal swapped back).
struct type_FC6F0
{
    RwInt32 unk_00;             // whether it hit
    RwReal unk_04;              // how far along the line
    RwV3d unk_08;               // the normal, in the world
    RwV3d unk_14;               // the point
    RwMatrix *unk_20;           // the atomic's frame matrix
    RwMatrix *unk_24;           // the same, orthonormalised (for normals)
};

// The aim pass's triangle hit (sub_FCD90 hands it to the triangle callback
// sub_FD700, which keeps the nearest distance): only a flag and a distance.
struct type_FD700
{
    bool unk_00;                // whether it hit
    // Padding as single bytes: a byte array would make /GS treat sub_FCD90's
    // local as a string buffer and add a cookie the image does not have.
    RwUInt8 unk_01;
    RwUInt8 unk_02;
    RwUInt8 unk_03;
    RwReal unk_04;              // how far along
};

// Keeps the nearer of the line from *arg_0's hits in arg_4 (setting *arg_8
// and the distance *arg_C; the point and normal into arg_10 and arg_14);
// only the widths are known otherwise.
void sub_FC9F0(RwV3d *arg_0, struct type_91F40 *arg_4, RwInt32 *arg_8, RwReal *arg_C, RwV3d *arg_10,
               RwV3d *arg_14, RwInt32 arg_18);
// The atomic pass's callback (sub_FC8F0): the atomic's triangles against the
// line, for an entity with bit 2 of unk_28, into the type_91F40 arg_10.
struct RpAtomic *sub_FC8F0(struct RpIntersection *arg_0, struct RpWorldSector *arg_4, struct RpAtomic *arg_8,
                           RwReal arg_C, void *arg_10);
// The player's aim pass (sub_FCD90, an atomic callback; its data is the
// aim, a type_4C194C) and its triangle callback (sub_FD700, into a
// type_FD700).
struct RpAtomic *sub_FCD90(struct RpIntersection *arg_0, struct RpWorldSector *arg_4, struct RpAtomic *arg_8,
                           RwReal arg_C, void *arg_10);
struct RpCollisionTriangle *sub_FD700(struct RpIntersection *arg_0, struct RpCollisionTriangle *arg_4,
                                      RwReal arg_8, void *arg_C);

#endif
