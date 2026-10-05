/*
 * CAnimObjectPool (unit_078AF0; the class name is in its own warning
 * "CAnimObjectPool:: Somebody forgot to de..."): a pool of animation players
 * (type_7C8D0) with a given number of tracks each, three of them at
 * byte_44A508. Its m_pool member is named by the label "animobjpool::m_pool"
 * it is set up with.
 */
#ifndef ANIMOBJPOOL_H
#define ANIMOBJPOOL_H

#include "rw/ostypes.h"
#include "types/alfasched.h"
#include "rw/rphanim.h"
#include "rw/rtquat.h"
#include "rw/rpatomic.h"
#include "rw/rtanim.h"

struct type_7C8D0;

struct CAnimObjectPool
{
    type_16C2A0 m_pool;
    RwInt32 unk_20;             // its index (stored in its players)
    RwInt32 unk_24;             // its players' tracks

    CAnimObjectPool();
    ~CAnimObjectPool();
    // Clears the pool's settings.
    void sub_78B90();
    // Sets the pool up as pool arg_0 of arg_8 players of arg_4 tracks.
    RwInt32 sub_78BB0(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8);
    // Warns of players not given back; shuts the pool down.
    void sub_78C00();
    void sub_78C30();
    // A new player, and giving one back.
    type_7C8D0 *sub_78C50();
    void sub_78CC0(type_7C8D0 *arg_0);
    // An inline accessor for unk_20, with no address and so no database
    // name; named for its field. Evidence: sub_78C50 copies it into a local
    // of its own before storing its low half.
    RwInt32 get_unk_20()
    {
        RwInt32 r = unk_20;
        return r;
    }
};
typedef RwChar CAnimObjectPool_size_check[sizeof(CAnimObjectPool) == 0x28 ? 1 : -1];

// sub_806E0: releases a track's or player's data; sub_7A4A0 and sub_7A540:
// the animation system's resets (sub_79260 runs both).
void sub_806E0(struct type_80300 *arg_0);
// dword_44A5C0: the next track serial (sub_796A0); sub_807C0 hands the
// animation's custom data to the interpolator arg_0.
extern RwInt32 dword_44A5C0;
RwInt32 sub_807C0(RtAnimInterpolator *arg_0, void *arg_4);
// sub_80300: a track's interpolator for arg_0 bytes of keyframes and arg_8
// of custom data, from the pool or (arg_4) the heap.
struct type_80300 *sub_80300(RwInt32 arg_0, bool arg_4, RwInt32 arg_8);
// sub_7F3C0: settles the hierarchy arg_0 in the mode arg_4 at the scale
// arg_8; sub_13FBC0: the rotation arg_4 slerped towards arg_8 by arg_C, into
// arg_0.
RwBool sub_7F3C0(RpHAnimHierarchy *arg_0, RwInt32 arg_4, RwReal arg_8);
void sub_13FBC0(RtQuat *arg_0, RtQuat *arg_4, RtQuat *arg_8, RwReal arg_C);
// RpSkinAtomicSetHAnimHierarchy: attaches the atomic arg_0 to the hierarchy arg_4 (the skin's).
extern "C" void RpSkinAtomicSetHAnimHierarchy(RpAtomic *arg_0, void *arg_4);
// The clump's atomics' callback sub_79270 passes (sub_7C830), and the
// interpolators' root-motion callback (sub_7C740, with its player).
RpAtomic *sub_7C830(RpAtomic *atomic, void *data);
// Sets up the clump's hierarchy (a new interpolator and the skin's bone
// matrices, unless one is given) and hands it to its atomics; true.
bool sub_79270(RpClump *arg_0, RpHAnimHierarchy *arg_4);
struct type_80300 *sub_7C740(struct type_80300 *arg_0, void *arg_4);
// The interpolators' event callback (sub_7C4E0, with its player), and
// sub_808A0, which sets the interpolator arg_0's callback arg_4 for the time
// arg_8 with the data arg_C.
struct type_80300 *sub_7C4E0(struct type_80300 *arg_0, void *arg_4);
void sub_808A0(struct type_80300 *arg_0, struct type_80300 *(*arg_4)(struct type_80300 *, void *),
               RwReal arg_8, void *arg_C);
// sub_80550: an interpolator from the header pool with arg_0 bytes of
// keyframes in the scratch block arg_4; sub_80740 gives it the callbacks
// of the scheme arg_4 (false when there is none); sub_807C0 and sub_807E0 set its
// frames, the latter with the animation; sub_80880 sets its other callback;
// sub_808D0 combines arg_4's keyframes into arg_0's.
struct type_80300 *sub_80550(RwInt32 arg_0, RwInt32 arg_4);
RwInt32 sub_80740(struct type_80300 *arg_0, RwInt32 arg_4);
RwInt32 sub_807E0(struct type_80300 *arg_0, RtAnimAnimation *arg_4);
void sub_80880(struct type_80300 *arg_0, struct type_80300 *(*arg_4)(struct type_80300 *, void *),
               void *arg_8);
RwInt32 sub_808D0(struct type_80300 *arg_0, struct type_80300 *arg_4);
// sub_80910 advances the interpolator arg_0 by arg_4 (decoding its keys
// when arg_8 is set); sub_81110 moves it to the time arg_4 (backwards
// through sub_31DB0, which in this image is an empty function /OPT:ICF
// shares); sub_81170 blends arg_4 and arg_8 by arg_C into arg_0.
RwInt32 sub_80910(struct type_80300 *arg_0, RwReal arg_4, RwUInt8 arg_8);
RwInt32 sub_31DB0(struct type_80300 *arg_0, RwReal arg_4, RwUInt8 arg_8);
RwInt32 sub_81110(struct type_80300 *arg_0, RwReal arg_4, RwUInt8 arg_8);
RwInt32 sub_81170(struct type_80300 *arg_0, struct type_80300 *arg_4, struct type_80300 *arg_8, RwReal arg_C);
bool sub_7A4A0();
bool sub_7A540();

// The animation event callbacks (sub_7A410 registers one for an event id,
// -1 for any, in dword_44A5A0's four slots) and the player update hooks
// (sub_7A4E0 adds one to dword_44A580's eight).
// An event callback: the event's id and data, the player's entity, the
// track and the player.
typedef void (*type_7A410_cb)(RwInt32 arg_0, void *arg_4, struct type_3D3548 *arg_8,
                              struct type_7C8D0_30 *arg_C, struct type_7C8D0 *arg_10);
struct type_44A5A0
{
    RwInt32 unk_00;             // the event id (-1: any)
    type_7A410_cb unk_04;
};
extern type_44A5A0 dword_44A5A0[4];
extern void (*dword_44A580[8])(type_7C8D0 *, type_80300 *, RwInt32, bool);

/* The player's own quaternion product (type_7C8D0's sub_7A100): the terms of
 * RtQuatMultiplyMacro (rw/rtquat.h), but its cross product the other way
 * round, each product with qp's component first, and qp's increment first.
 * No database name; named for what it does. */
#define quatMultiplyMacro(qpq, qp, qq)                                \
MACRO_START                                                           \
{                                                                     \
    (qpq)->real =                                                     \
        (qp)->real * (qq)->real -                                     \
        RwV3dDotProductMacro(&(qp)->imag, &(qq)->imag);               \
    MACRO_START                                                       \
    {                                                                 \
        (qpq)->imag.x = (((qp)->imag.z) * ((qq)->imag.y)) -           \
                        (((qp)->imag.y) * ((qq)->imag.z));            \
        (qpq)->imag.y = (((qp)->imag.x) * ((qq)->imag.z)) -           \
                        (((qp)->imag.z) * ((qq)->imag.x));            \
        (qpq)->imag.z = (((qp)->imag.y) * ((qq)->imag.x)) -           \
                        (((qp)->imag.x) * ((qq)->imag.y));            \
    }                                                                 \
    MACRO_STOP;                                                       \
    RwV3dIncrementScaledMacro(&(qpq)->imag, &(qp)->imag, (qq)->real); \
    RwV3dIncrementScaledMacro(&(qpq)->imag, &(qq)->imag, (qp)->real); \
}                                                                     \
MACRO_STOP

#endif
