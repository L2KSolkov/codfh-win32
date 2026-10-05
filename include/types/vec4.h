/*
 * Four-float points (unit_08AB60): what the helpers at 0x8B920 to 0x8BFA0
 * return by value (vectors and 4x4 matrices), and sub_8C230 the corners of
 * a box through an RwMatrix.
 */
#ifndef TYPES_VEC4_H
#define TYPES_VEC4_H

#include "rw/ostypes.h"
#include "rw/bamatrix.h"
#include "rw/rphanim.h"
#include "rw/bastream.h"
#include "rw/rpworld.h"
#include "types/type_8E670.h"

struct type_8BEC0
{
    RwReal unk_00;
    RwReal unk_04;
    RwReal unk_08;
    RwReal unk_0C;              // 1 for a point
};

// Four of them: a 4x4 matrix by rows (sub_8BFA0's inverse), 16-aligned:
// its return temporaries sit on 16-byte boundaries.
// A four-float vector aligned to 16, named after sub_140490, which takes
// them (the soldier's five-way blend, type_3DAFC8::sub_139620, keeps them at
// 16-aligned slots).
struct __declspec(align(16)) type_140490
{
    RwReal x;                   // x, y and z: sub_140490 applies
    RwReal y;                   // RwV3dSubMacro and RwV3dCrossProductMacro
    RwReal z;                   // to them
    RwReal w;
};

struct __declspec(align(16)) type_8BFA0
{
    type_8BEC0 unk_00[4];
};

// A box as two corners (sub_8C410's result), 16-aligned: sub_8C690 keeps
// its return temporaries on 16-byte boundaries.
struct __declspec(align(16)) type_8C410
{
    type_8BEC0 unk_00;          // the least corner
    type_8BEC0 unk_10;          // the greatest
};
// The box around arg_4 (its two corners) through the matrix arg_0: the
// least and greatest of its eight corners so transformed (from +-1e9).
type_8C410 sub_8C410(RwMatrix *arg_0, type_8BEC0 *arg_4);

// The helpers (each builds its result in a 16-aligned local, hence the
// realigned frames): the cross product, arg_0 scaled by *arg_4 and *arg_0
// scaling arg_4, the difference and sum as points (w 1), a point from
// arg_0, one from four floats, the dot product, the matrix arg_4's rows
// scaled by *arg_0 (the last row scales itself), the normalised vector,
// the vector arg_4 through the matrix arg_0 (w 0) and the inverse of the
// matrix arg_0.
type_8BEC0 sub_8B920(type_8BEC0 *arg_0, type_8BEC0 *arg_4);
type_8BEC0 sub_8B9C0(type_8BEC0 *arg_0, RwReal *arg_4);
type_8BEC0 sub_8BA30(RwReal *arg_0, type_8BEC0 *arg_4);
type_8BEC0 sub_8BAA0(type_8BEC0 *arg_0, type_8BEC0 *arg_4);
type_8BEC0 sub_8BB10(type_8BEC0 *arg_0, type_8BEC0 *arg_4);
type_8BEC0 sub_8BB80(RwV3d *arg_0);
type_8BEC0 sub_8BBE0(RwReal arg_0, RwReal arg_4, RwReal arg_8, RwReal arg_C);
RwReal sub_8BC40(type_8BEC0 *arg_0, type_8BEC0 *arg_4);
type_8BFA0 sub_8BC90(RwReal *arg_0, type_8BFA0 *arg_4);
type_8BEC0 sub_8BE10(type_8BEC0 *arg_0);
type_8BEC0 sub_8BEC0(RwMatrix *arg_0, type_8BEC0 *arg_4);
type_8BFA0 sub_8BFA0(RwMatrix *arg_0);
// sub_140130: the point *arg_4 through the 4x4 matrix arg_8, divided by its
// w, into *arg_0; sub_1401B0: the vector *arg_4 through the matrix arg_8
// into *arg_0 (unit_13F9E0).
void sub_140130(RwV3d *arg_0, RwV3d *arg_4, type_8BFA0 *arg_8);
void sub_1401B0(type_140490 *arg_0, type_140490 *arg_4, type_8BFA0 *arg_8);
// The eight corners of the box arg_0 (its two opposite corners) through
// the matrix arg_4, into arg_8.
void sub_8C230(type_8BEC0 *arg_0, RwMatrix *arg_4, type_8BEC0 *arg_8);
// A bone's box in the table dword_4B21D0: its least corner (whose w holds
// its bone's index as a float; the tests truncate it) and its greatest; the
// sphere test (sub_8E330) takes the least corner as half extents. Aligned
// to 16: type_3DAFC8::vf_07C builds one on its aligned frame.
struct __declspec(align(16)) type_4B21D0_60
{
    RwReal unk_00;
    RwReal unk_04;
    RwReal unk_08;
    RwReal unk_0C;
    RwReal unk_10;
    RwReal unk_14;
    RwReal unk_18;
    RwReal unk_1C;
};
// The bone boxes (.bss): the six axis planes (x, y, z, d; the line and
// sphere tests set each d from a box's half extents), then the kind-0 and
// kind-1 boxes (+0x60) and the other kinds' (+0x1E0); how many each holds
// is not established.
struct type_4B21D0
{
    type_8BEC0 unk_00[6];
    type_4B21D0_60 unk_60[12];
    type_4B21D0_60 unk_1E0[12];
    type_8C410 unk_360;         // the line test's current box, in the bone's
                                // space (sub_8C410)
};
extern type_4B21D0 dword_4B21D0;
// What a hit on each bone box is (.data, 0x18 bytes each): 13 for kinds 0
// and 1 (dword_428E80) and the rest for the others (dword_428FB8, which
// follows it); unk_10 is what the line test returns for the box.
struct type_428E80
{
    RwInt32 unk_00;             // two bone ids
    RwInt32 unk_04;
    RwReal unk_08;
    RwReal unk_0C;
    RwInt32 unk_10;             // the part hit
    RwUInt8 unk_14;             // set: the box faces along the bone (sub_8C690)
    RwUInt8 unk_15[0x3];
};
extern type_428E80 dword_428E80[13];
extern type_428E80 dword_428FB8[];
// Sets up the boxes between the bones of the hierarchy arg_4 from the
// table for the kind arg_0 (0 and 1: 13 bones, else 11), and the six axis
// directions (dword_4B21D0 on).
void sub_8C690(RwInt32 arg_0, RpHAnimHierarchy *arg_4);
void sub_8D580(RpHAnimHierarchy *arg_0, RwInt32 arg_4);
// The line of arg_8 against the bone boxes of the hierarchy arg_4, and its
// sphere (sub_8E330: arg_8 read as an RwSphere, the first arg_0 boxes of
// the kind arg_C's table or of arg_10); -1 for a miss.
RwInt32 sub_8D660(RwInt32 arg_0, RpHAnimHierarchy *arg_4, RpIntersection *arg_8, RwInt32 arg_C,
                  type_4B21D0_60 *arg_10);
RwInt32 sub_8E330(RwInt32 arg_0, RpHAnimHierarchy *arg_4, RpIntersection *arg_8, RwInt32 arg_C,
                  type_4B21D0_60 *arg_10);
// Which faces of the box arg_4 the point arg_0 lies outside: 1 and 2 below
// and above in x, 4 and 8 in y, 0x10 and 0x20 in z.
RwInt32 sub_8D5A0(type_8BEC0 *arg_0, type_8BEC0 *arg_4);

// A zone (sub_8F3E0 tests a point against it): its box, then its planes
// in groups of four (x[4], y[4], z[4], d[4]), as many as byte 2 of unk_8C
// says; a plane of 0, 0, 0, -1 ends them early.
struct type_8F3E0
{
    type_8BEC0 unk_00[2];
    RwUInt8 unk_20[0x10];
    type_8BEC0 unk_30;          // its ambient light (sub_8E870)
    type_8BEC0 unk_40;          // its first light's point (none when zero)
    type_8BEC0 unk_50;          // and value
    type_8BEC0 unk_60;          // its second light's
    type_8BEC0 unk_70;
    RwUInt8 unk_80[0xC];
    RwInt32 unk_8C;
    RwReal unk_90[4];
    RwReal unk_A0[4];
    RwReal unk_B0[4];
    RwReal unk_C0[4];
};
// The zones' shared effect (dword_4B2560): sub_8F140 starts it with one or
// two points and their four-float values, sub_8E750 runs its time down,
// sub_8F210 hands it out.
struct type_4B2560
{
    RwReal unk_00;              // its time, in seconds
    RwInt32 unk_04;             // how many points (1 or 2)
    RwV3d unk_08[2];
    type_8BEC0 unk_20[2];

    // Inline: its initializer (0x30A440) clears only the time.
    type_4B2560()
    {
        unk_00 = 0;
    }
};
extern type_4B2560 dword_4B2560;
struct type_8F210_e
{
    type_8BEC0 unk_00;          // the point, w 0
    type_8BEC0 unk_10;
};
// 16-aligned: sub_122820 keeps one on a realigned frame.
struct __declspec(align(16)) type_8F210
{
    RwInt32 unk_00;             // how many
    RwInt32 unk_04;             // (no byte array: sub_122820 keeps one
    RwInt32 unk_08;             // without a /GS cookie)
    RwInt32 unk_0C;
    type_8F210_e unk_10[5];     // the ambient first, then the lights
};
// Hands the light list arg_0 on (sub_8E870).
void sub_19B270(type_8F210 *arg_0);

// The zone table (unit_08AB60, read by sub_8F330 from a stream): its
// count, each zone's offset into the data (low 24 bits; sub_94060 reads
// dword_4B2554 and dword_4B2558), and the data.
struct type_8F300
{
    RwInt32 unk_00;             // the count (read as a packed header)
    RwUInt32 *unk_04;
    RwUInt8 *unk_08;

    type_8F300();
    // Inline: its exit function (0x30DF00) clears the three fields without
    // freeing (sub_D7350 frees them at shutdown).
    ~type_8F300()
    {
        unk_00 = 0;
        unk_04 = 0;
        unk_08 = 0;
    }
    void sub_8F330(RwStream *arg_0);
    // Frees the table (the game loop's module shutdown, sub_D7040).
    void sub_D7350();
    // An inline accessor for zone arg_0 (0 before the table is read), with
    // no address and so no database name. Evidence: sub_93F00 loads the
    // offsets' base before the index, which the expanded accessor does and
    // the same expression written in place does not.
    type_8F3E0 *get_zone(RwInt32 arg_0)
    {
        if (unk_08)
        {
            return (type_8F3E0 *)(unk_08 + (unk_04[arg_0] & 0xFFFFFF));
        }
        return 0;
    }
    // Whether the point arg_4 is inside the zone arg_0 (its box, and behind
    // all its planes).
    bool sub_8F3E0(type_8F3E0 *arg_0, type_8BEC0 *arg_4);
    // Runs sub_8F5C0 over the world sectors of arg_0 once for each zone.
    void sub_8F570(RpWorld *arg_0);
    // Runs sub_8F8C0 over them as often.
    void sub_8F870(RpWorld *arg_0);
};
RpWorldSector *sub_8F5C0(RpWorldSector *arg_0, void *arg_4);
extern type_8F300 dword_4B2550;
// sub_94060's search for the smallest zone around a point: the smallest
// volume so far, its zone, and the entity asking.
struct type_93F00
{
    RwReal unk_00;
    type_8F3E0 *unk_04;
    struct type_3D3548 *unk_08;
};
// The sector callback of that search: each zone listed in the sector that
// holds the point, if smaller than the best so far.
RpWorldSector *sub_93F00(RpIntersection *arg_0, RpWorldSector *arg_4, void *arg_8);
// The zone outside every zone.
extern type_8F3E0 dword_4E5BE0;
// Whether zones are found with a sphere through the collision worlds
// (else through the world sectors the entity's atomic is in).
extern RwInt32 dword_4B6764;
// A world sector link of an atomic (RenderWare's RpTie: the sector link at
// +0xC, the sector at +0x14), as sub_94060 walks them.
struct type_94060_link
{
    type_94060_link *unk_00;    // the next
    type_94060_link *unk_04;
};
struct type_94060_tie
{
    RwUInt8 unk_00[0xC];
    type_94060_link unk_0C;
    RpWorldSector *unk_14;
};
// An atomic as sub_94060 reads it: a vector it requires nonzero, and its
// world sectors' ties.
struct type_94060_atomic
{
    RwUInt8 unk_00[0x2C];
    RwV3d unk_2C;
    RwUInt8 unk_38[0x2C];
    type_94060_link unk_64;
};
// Finds the smallest zone around the entity arg_0 and fades to it.
void sub_94060(struct type_3D3548 *arg_0);
// Whether the boxes arg_0 and arg_4 overlap.
bool sub_8F770(type_8BEC0 *arg_0, type_8BEC0 *arg_4);
// A world sector's zone list as sub_8F5C0 leaves it: tagged 0xFFFFFF in
// the top of unk_10 with the count in its low bits, the zones' indices
// packed four to a word from unk_14.
struct type_8F8C0
{
    RwUInt8 unk_00[0x10];
    RwUInt32 unk_10;
    RwUInt32 unk_14[6];         // up to 24 zones (sub_8F5C0)
    RwUInt8 unk_2C[0x1C];
    RwBBox unk_48;              // its box (RenderWare's boundingBox)
};
// Clears a sector's zone list (and its tag).
RpWorldSector *sub_8F8C0(RpWorldSector *arg_0, void *arg_4);
// A new id (dword_4B25B0 counts them).
RwInt32 sub_8F940();
extern RwInt32 dword_4B25B0;

#endif
