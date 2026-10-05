/*
 * The animation keyframes (unit_07CA20): the game's own compressed key
 * format (quaternions as three shorts in 32768ths with the real part
 * recovered, positions as half floats) and their interpolation.
 */
#ifndef ANIMKEY_H
#define ANIMKEY_H

#include <math.h>

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "rw/rtquat.h"
#include "rw/rtanim.h"
#include "rw/bastream.h"
#include "rw/bamatrix.h"
#include "types/alfasched.h"

// A keyframe as the interpolation callbacks read it: its time first.
struct type_7CB80
{
    RwReal unk_00;              // its time
};

// A pose key: its time, its header, then a rotation per node and after them
// a translation for each node the header marks.
struct type_7CBD0_hdr
{
    RwUInt8 unk_00;             // the nodes' count
    RwUInt8 unk_01;
    RwUInt8 unk_02;             // the translations' count
    RwUInt8 unk_03;
    RwUInt8 unk_04;
    RwUInt8 unk_05;             // the root node
    RwUInt8 unk_06;             // (scalars: a byte array would give sub_7A580's
    RwUInt8 unk_07;             // header local a /GS cookie)
    RwUInt64 unk_08;            // the nodes the key has (rotations)
    RwUInt64 unk_10;            // the nodes with a translation
};
struct type_7CBD0_t
{
    RwV3d unk_00;
    RwReal unk_0C;
};
struct type_7CBD0
{
    RwReal unk_00;              // its time
    type_7CBD0_hdr *unk_04;
    RwV3d *unk_08;              // the nodes' positions, when set (sub_7DEB0)
    RwUInt8 unk_0C[0x4];
    RtQuat unk_10[1];           // the rotations, then the translations
};

// A compressed pose key (sub_7CF40 builds one): the rotations it keeps (and
// in the top byte their count), the translations it keeps, the root's
// heading (in 64ths of a degree) and its time (in frames), then the
// rotations (three shorts each) and, aligned after them, the translations
// (three half floats each).
struct type_7CF40
{
    union
    {
        RwUInt64 unk_00;
        struct
        {
            RwInt64 unk_00_0 : 56;
            RwInt64 unk_00_56 : 8;  // the rotations' count
        };
    };
    union
    {
        RwUInt64 unk_08;
        struct
        {
            RwInt64 unk_08_0 : 56;
            RwInt64 unk_08_56 : 8;  // the translations' count
        };
    };
    RwInt16 unk_10;
    RwInt16 unk_12;
    RwInt16 unk_14[1][3];
};

// Floats through the C library: inlines with no address and so no database
// names, named for what they give. Evidence: sub_7CF40 passes atan2's
// arguments through temporaries and keeps its result in another.
inline RwReal atan2f_(RwReal y, RwReal x)
{
    return (RwReal)atan2(y, x);
}
// Radians to degrees: likewise (sub_7CF40 passes its argument through a
// temporary); the constant is 180 over pi as 3.1415926, divided at compile
// time (0x42652EE2, one ulp above 180/pi).
inline RwReal rad2deg_(RwReal x)
{
    return x * (180.0f / 3.1415926f);
}

// A float's square root through the C library: an inline with no address
// and so no database name, named for what it gives. Evidence: sub_7CA20
// keeps its argument in a temporary (fst) and its result in another.
inline RwReal sqrtf_(RwReal x)
{
    return (RwReal)sqrt(x);
}

// sub_7CA20: three shorts into a rotation (arg_8 unused; its callers pass
// 0, as sub_7FB40's pass 0 the other way).
void sub_7CA20(RtQuat *arg_0, RwInt16 *arg_4, RwInt32 arg_8);
void sub_7CAC0(RwUInt16 *arg_0, RwV3d *arg_4);
RwReal sub_7CB10(RwUInt16 arg_0);
// The inverse: a vector into three half floats, and a float as a half.
void sub_7D220(RwV3d *arg_0, RwUInt16 *arg_4);
RwUInt16 sub_7D270(RwReal arg_0);
// Compresses the pose key arg_4 into arg_0 (whose masks say what to keep).
void sub_7CF40(type_7CF40 *arg_0, type_7CBD0 *arg_4);
// sub_7FB40: a rotation into three shorts (arg_8 only known by width);
// sub_13FB00: a quaternion normalised.
void sub_7FB40(RwInt16 *arg_0, RtQuat *arg_4, RwInt32 arg_8);
void sub_13FB00(RtQuat *arg_0, RtQuat *arg_4);
// sub_13FDA0: the rotation by the vector *arg_0 (its length the angle about
// its direction) as a unit quaternion into *arg_4.
void sub_13FDA0(RwV3d *arg_0, RtQuat *arg_4);
// sub_13FE90: the product of the quaternions arg_8 and arg_4 into *arg_0.
void sub_13FE90(RtQuat *arg_0, RtQuat *arg_4, RtQuat *arg_8);
void sub_7CB80(void *arg_0, type_7CB80 *arg_4, type_7CB80 *arg_8, RwReal arg_C);
void sub_7CBD0(void *arg_0, type_7CB80 *arg_4, type_7CB80 *arg_8, RwReal arg_C);
// sub_13FBC0 (as unit_078AF0 declares it): a slerp.
void sub_13FBC0(RtQuat *arg_0, RtQuat *arg_4, RtQuat *arg_8, RwReal arg_C);

// The memory functions the game allocates through (RwMalloc and RwFree
// with a hint; the image holds them at fixed addresses in .data).

// The interpolation schemes: sub_7FD90 registers up to 16 in dword_44B638,
// sub_7FE10 finds one by its type.
extern RtAnimInterpolatorInfo dword_44B638[16];
extern RwInt32 dword_44BA38;        // the schemes registered

// The interpolators' pools and scratch memory (sub_7FC90 sets them up,
// sub_7FD10 frees them).
extern type_16C2A0 dword_44BA54;    // "_animInterpolatorPool"
extern type_16C2A0 dword_44BA74;    // "_animInterpolatorHeaderPool"
extern void *dword_44BA3C;
extern void *dword_44BA40;

RwInt32 sub_7FC90();
RwInt32 sub_7FD10();
RwInt32 sub_7FD70();
RwInt32 sub_7FD90(RtAnimInterpolatorInfo *arg_0);
RtAnimInterpolatorInfo *sub_7FE10(RwInt32 arg_0);
// An animation of arg_4 frames of the scheme arg_0 (flags arg_8, duration
// arg_C) with arg_10 bytes of frames after its arg_14 (on the heap, or in the
// memory arg_0 for sub_7FF20); the size such an animation takes.
RtAnimAnimation *sub_7FE60(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwReal arg_C, RwInt32 arg_10,
                           RwInt32 arg_14);
RwUInt32 sub_7FEF0(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8);
RtAnimAnimation *sub_7FF20(void *arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C, RwReal arg_10,
                           RwInt32 arg_14, RwInt32 arg_18);
RtAnimAnimation *sub_7FFB0(RtAnimAnimation *arg_0);

// An animation's stream header after its version (0x101), in the order
// sub_77E40 hands it on to sub_7FF20: the scheme's type, the frames, the
// frame and custom sizes, the flags and the duration. sub_7FFD0 reads it,
// false when the version or scheme is unknown or the stream runs out.
struct type_7FFD0
{
    RwInt32 unk_00;
    RwInt32 unk_04;
    RwInt32 unk_08;
    RwInt32 unk_0C;
    RwInt32 unk_10;
    RwReal unk_14;
};
bool sub_7FFD0(RwStream *arg_0, type_7FFD0 *arg_4);

// sub_800F0: the keys of the track arg_4 in the frames arg_0 (a warning when
// they are not arg_8); sub_801C0: resolves the frames' shared tracks (their
// word's top bits set) against the frames arg_4 (the set reader, sub_77E40,
// passes the animation's index as arg_8, unread); sub_802D0: reads the
// animation arg_4's arg_8 bytes of frames through its scheme (arg_C, the
// custom size, unread).
void *sub_800F0(type_7CBD0_hdr *arg_0, RwInt32 arg_4, RwInt32 arg_8);
void sub_801C0(RtAnimAnimation *arg_0, type_7CBD0_hdr **arg_4, RwInt32 arg_8);
RtAnimAnimation *sub_802D0(RwStream *arg_0, RtAnimAnimation *arg_4, RwInt32 arg_8, RwInt32 arg_C);

// A track's compressed key in the frames (8 bytes): its value (three shorts,
// copied whole: a rotation for sub_7CA20 or three half floats for
// sub_7CAC0), then its time in 59.999ths of a second.
struct type_7DCA0_q
{
    RwInt16 unk_00[3];
};
struct type_7DCA0
{
    type_7DCA0_q unk_00;
    RwInt16 unk_06;
};

// The scheme 0x1142 (sub_7DE10 registers it) and its callbacks: sub_7DEB0
// turns the pose key arg_4 into the matrices arg_0 (remapping the nodes
// through dword_428C10 in the mode 1), sub_7E230 a rotation into a matrix
// (mirrored when arg_8 is set), sub_7E3A0 copies the pose key arg_4 into
// arg_0, sub_7E870 reads an animation's frames (sub_7DCA0 their tracks).
// The rest are only known by width.
extern RwInt32 dword_428C10[];
RwInt32 sub_7DE10();
void sub_7DEB0(RwMatrixTag *arg_0, type_7CBD0 *arg_4, RwInt32 arg_8);
void sub_7E230(RtQuat *arg_0, RwMatrixTag *arg_4, RwUInt8 arg_8);
void sub_7E3A0(type_7CBD0 *arg_0, type_7CBD0 *arg_4);
RtAnimAnimation *sub_7DCA0(RtAnimAnimation *arg_0, RwStream *arg_4, type_7CBD0_hdr *arg_8);
RtAnimAnimation *sub_7E870(RwStream *arg_0, RtAnimAnimation *arg_4, RwInt32 arg_8);
// sub_7D2F0 decodes the interpolator arg_4's keys at its time into the pose
// key arg_0 (the scheme's +0x14 callback).
void sub_7D2F0(type_7CBD0 *arg_0, struct type_80300 *arg_4);
void sub_7E420(type_7CBD0 *arg_0, type_7CBD0 *arg_4);
// sub_7E990 writes an animation's frames (sub_7EAB0 their tracks).
RwInt32 sub_7E990(RtAnimAnimation *arg_0, RwStream *arg_4);
bool sub_7EAB0(RtAnimAnimation *arg_0, RwStream *arg_4, type_7CBD0_hdr *arg_8);
RwInt32 sub_7ECB0(RtAnimAnimation *arg_0);
// sub_7EE30 reads an animation's arg_4 compressed pose keys into the memory
// arg_8, filling its table of them (customData).
RtAnimAnimation *sub_7EE30(RwStream *arg_0, RtAnimAnimation *arg_4, void *arg_8);
// sub_7F0E0 would write the compressed pose keys (it returns 1 before its
// loop); sub_7F2A0 is the size of the key arg_4, sub_7F370 of them all.
RwInt32 sub_7F0E0(RtAnimAnimation *arg_0, RwStream *arg_4);
RwUInt32 sub_7F2A0(RtAnimAnimation *arg_0, RwInt32 arg_4);
RwUInt32 sub_7F370(RtAnimAnimation *arg_0);
// The empty callback at +0x1C: the debug print, which /OPT:ICF shares.
void sub_19A750(type_7CBD0 *arg_0, type_7CBD0 *arg_4);

#endif
