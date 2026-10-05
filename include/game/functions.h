/*
 * Free functions in units not yet recovered, declared once with the types
 * their bodies establish.
 */
#ifndef GAME_FUNCTIONS_H
#define GAME_FUNCTIONS_H

#include "rw/ostypes.h"
#include "rws/debugswitches.h"
#include "rws/maths.h"
#include "rw/bamatrix.h"
#include "rw/rpcollis.h"
#include "types/type_154C0_1048.h"

struct type_3D3548;
struct type_3DBC78;
struct AIData;
struct type_F8350;
typedef struct RpClump RpClump;
struct type_3DC048;
struct type_3CE6D0;
struct type_3D2E7C;
struct type_3DF8D8;
struct type_3DC9B0;
struct type_92430;
struct type_67620;
struct type_3DF8D8_04;
struct type_3D410;

// Defined in src/recovered/unit_012000.cpp: the handler table unk_427408's
// dispatchers (arg_8/arg_4 carry the caller's context, a type_3D410 *, as a
// dword) and the check sub_15370.
RwInt32 sub_12030(RwInt32 arg_0, type_3DBC78 *arg_4, RwInt32 arg_8, void *arg_C);
RwInt32 sub_12070(type_3DBC78 *arg_0, RwInt32 arg_4);
RwBool sub_15370(type_3DBC78 *arg_0, RwInt32 arg_4, RwInt32 arg_8);

// sub_3DE00: whether the entity arg_0 may take the entity arg_4 as its
// target (type_3D410::sub_3DCD0 and type_3CE4F0::sub_34C60 ask).
RwInt32 sub_3DE00(type_3D3548 *arg_0, type_3D3548 *arg_4);

// sub_6B680: sub_6B5F0's counterpart taking a message id (arg_0) for the
// name; the other arguments are as there.
struct type_42E00_10;
void sub_6B680(RwInt32 arg_0, type_67620 *arg_4, type_42E00_10 *arg_8, type_3D2E7C *arg_C, RwInt32 *arg_10, RwInt32 arg_14, bool arg_18, bool arg_1C);

// sub_8A950: whether the untimed sound arg_0 still lasts (AIHearing's
// sub_3C2B0 drops one that has been seen once when it returns 0).

// sub_3D700: runs the periodic update arg_0 (dword_427660) on arg_4.
void sub_3D700(RwInt32 arg_0, type_3D410 *arg_4);

// sub_6B5F0: takes a name string and an entity's type_3D2E7C (its vf_098),
// which it tests against zero; reads arg_18 and arg_1C as single bytes (only
// 0 and 1 are passed). arg_10 is an untyped pointer: callers pass the address
// of an RwInt32 (sub_13900) or of a copy of their own pointer argument
// (sub_12EF0). arg_8, arg_C and arg_14 are passed through as dwords.
void sub_6B5F0(const RwChar *arg_0, type_67620 *arg_4, type_42E00_10 *arg_8, type_3D2E7C *arg_C, RwInt32 *arg_10, RwInt32 arg_14, bool arg_18, bool arg_1C);

// sub_150F0: in this unit (src/recovered/unit_012000.cpp); called before its
// definition by sub_14570 and sub_14650.
RwInt32 sub_150F0(type_3D3548 *arg_0, RwInt32 arg_4);

// sub_14CC0: in this unit; called before its definition by sub_140D0 and
// sub_14340.
RwInt32 sub_14CC0(type_3DBC78 *arg_0, RwInt32 arg_4);

// sub_14EA0: in this unit; called before its definition by sub_14480.
RwInt32 sub_14EA0(type_3DBC78 *arg_0, RwInt32 arg_4);

// sub_14DF0: in this unit; called before its definition by sub_143E0.
RwInt32 sub_14DF0(type_3DBC78 *arg_0, RwInt32 arg_4);

// sub_15190: in this unit; called before its definition by sub_146E0.
RwInt32 sub_15190(type_3DC048 *arg_0, RwInt32 arg_4);

// sub_152A0: in this unit; called before its definition by sub_14770.
RwInt32 sub_152A0(type_3DC048 *arg_0, RwInt32 arg_4);

// sub_F7BA0: takes an AI object, a path node and a flag it reads as a byte;
// its result is only known by width.
RwInt32 sub_F7BA0(AIData *arg_0, type_F8350 *arg_4, bool arg_8);

// sub_16D10, sub_16E80: in this unit; they manage the handle table
// unk_438CA8.
void sub_16D10();
RwInt32 sub_16E80(type_3D3548 *arg_0);

// sub_19A750: the game's debug print, an empty function in the retail image
// (docs/image.md). Callers pass a format and up to six more arguments.
void sub_19A750(const RwChar *arg_0, ...);
// The game loop's set-up (sub_D6640) also calls it with no arguments.
void sub_19A750();
// The same empty body serves the object-tagged debug log too: the A*
// scheduler (sub_32F70, sub_330E0) passes the entity, a level, the message,
// __FILE__ and __LINE__. /OPT:ICF folded both empty functions into one.
void sub_19A750(type_3D3548 *arg_0, RwInt32 arg_4, const RwChar *arg_8, const RwChar *arg_C,
                RwInt32 arg_10);
// And a third, taking a time step: the AI update sub_3ED10 passes its own
// between the schedulers' updates.
void sub_19A750(RwReal arg_0);
// And a fifth, taking a flag: the frame timer (sub_124DC0) passes 1 while
// the frames are quick or a fade runs and 0 while they are slow, and the
// fade's start (sub_124EE0) passes 1.
void sub_19A750(RwInt32 arg_0);
// And a fourth: "EfuncPlaySound" passes no entity, level 1, the sound's key
// by value and 2.
void sub_19A750(type_3D3548 *arg_0, RwInt32 arg_4, type_3DF8D8_04 arg_8, RwInt32 arg_10);
// And a fifth: "SetObjectiveCounter" (also "ModifyObjectiveCounter") passes
// the objective's key and the count to an empty function.
void sub_19A750(type_3DF8D8_04 *arg_0, RwInt32 arg_4);
// And a sixth: "PrintObjective" passes only the objective's key.
void sub_19A750(type_3DF8D8_04 *arg_0);
// The objectives, by key: add one (sub_1703B0, with arg_4 and arg_8),
// remove one, and get, set and clear its flags and get its counter;
// only the widths are known.
void sub_1703B0(type_3DF8D8_04 *arg_0, RwInt32 arg_4, RwInt32 arg_8);
RwInt32 sub_170500(type_3DF8D8_04 *arg_0);
RwInt32 sub_1706A0(type_3DF8D8_04 *arg_0);
void sub_170710(type_3DF8D8_04 *arg_0, RwInt32 arg_4);
void sub_170790(type_3DF8D8_04 *arg_0, RwInt32 arg_4);
RwInt32 sub_170810(type_3DF8D8_04 *arg_0);
// Set the objective's activate, complete, fail, increment-counter and
// decrement-counter messages and its nag timer to arg_4, and its target to
// the entity or trigger arg_4 (sub_171110, sub_171070); only the widths are
// known.
RwInt32 sub_170940(type_3DF8D8_04 *arg_0, RwInt32 arg_4);
RwInt32 sub_170A30(type_3DF8D8_04 *arg_0, RwInt32 arg_4);
RwInt32 sub_170B20(type_3DF8D8_04 *arg_0, RwInt32 arg_4);
RwInt32 sub_170C10(type_3DF8D8_04 *arg_0, RwInt32 arg_4);
RwInt32 sub_170D00(type_3DF8D8_04 *arg_0, RwInt32 arg_4);
// (sub_170FD0 is defined with a float timer, game/objectives.h; the
// script command passes an int, which this prototype keeps.)
RwInt32 sub_170FD0(type_3DF8D8_04 *arg_0, RwReal arg_4);
void sub_171110(type_3DF8D8_04 *arg_0, type_3D3548 *arg_4);
void sub_171070(type_3DF8D8_04 *arg_0, class type_712B0 *arg_4);
// The objective's spline path arg_4 (0 for none; sub_1711B0) and lookahead
// distance (sub_171230); add and clear a sub-objective target and clear them
// all (sub_171380, sub_1713F0, sub_171440); only the widths are known.
void sub_1711B0(type_3DF8D8_04 *arg_0, struct SplinePath *arg_4);
void sub_171230(type_3DF8D8_04 *arg_0, RwReal arg_4);
RwInt32 sub_171380(type_3D3548 *arg_0);
RwInt32 sub_1713F0(type_3D3548 *arg_0);
void sub_171440();
// Help messages (game/helpmessages.h): show the one under the key arg_0
// (arg_4 its killed flag, arg_8 first), kill one, and clear all (arg_0: the
// one shown fades out) (sub_17C500, sub_17C640, sub_17C6C0).
RwInt32 sub_17C500(type_3DF8D8_04 *arg_0, RwInt32 arg_4, RwInt32 arg_8);
void sub_17C640(type_3DF8D8_04 *arg_0);
void sub_17C6C0(RwInt32 arg_0);

// sub_40B10: takes an AI object's owner and its new target (AIData::sub_18BB0
// calls it on acquiring a target); its result, if any, is not used there.
void sub_40B10(type_3D3548 *arg_0, type_3D3548 *arg_4);

// sub_16D50, sub_16E30: in this unit; sub_16D50 resets the handle table count
// and reports uncleared slots through sub_16E30.
void sub_16D50();
void sub_16E30();

// sub_31BE0, sub_31C30: AIData::sub_19010 passes either one its owner's
// vf_098; their results, if any, are not used there.
void sub_31BE0(type_3D2E7C *arg_0);
void sub_31C30(type_3D2E7C *arg_0);

// The CanShoot scheduler (two alfasched, flt_438D38 and flt_438D88):
// sub_31AD0 sets both up, sub_31B10 and sub_31B50 flush them (complaining
// through sub_31B90 about entries left), sub_31BB0 runs them. sub_31C50 is
// the first one's callback (and its test, sub_31DB0, always passes); the
// second one's is sub_31E20.
struct type_67620;
void sub_31AD0();
void sub_31B10();
void sub_31B50();
void sub_31B90();
void sub_31BB0(RwReal arg_0);
RwInt32 sub_31C50(type_67620 *arg_0, RwInt32 arg_4, RwReal arg_8, RwInt32 arg_C);
RwInt32 sub_31DB0(type_67620 *arg_0, RwInt32 arg_4, RwReal arg_8, RwInt32 arg_C);
RwInt32 sub_31E20(type_67620 *arg_0, RwInt32 arg_4, RwReal arg_8, RwInt32 arg_C);

// sub_31DC0, sub_31E00: AIData::sub_1FC40 and sub_1FC70 pass their owner's
// vf_098; sub_31E00 calls sub_71340 on it when it is not 0.
void sub_31DC0(type_3D2E7C *arg_0);
void sub_31E00(type_3D2E7C *arg_0);

// sub_3D3E0: the object registered under handle arg_0 in dword_4392A8, or 0
// when the handle's slot holds another handle.
type_3CE6D0 *sub_3D3E0(RwUInt32 arg_0);

// sub_1745A0: the entity whose handle is entry arg_0 of the table at
// unk_4E5D1C (resolved with sub_D4910).
type_3D3548 *sub_1745A0(RwInt32 arg_0);

// sub_D5CF0: the entity registered under handle arg_0 in the (handle,
// entity) pairs at dword_4B6A00, or 0 when the handle's slot holds another
// handle.
type_3D3548 *sub_D5CF0(RwInt32 arg_0);

// sub_22C20: a clamp: arg_8 when arg_0 is above it, arg_4 when arg_0 is below
// that, else arg_0. It takes and returns addresses, used as references.
const RwReal &sub_22C20(const RwReal &arg_0, const RwReal &arg_4, const RwReal &arg_8);

// sub_141320: *arg_0 = arg_4 transformed by the rotation rows of arg_8 (it
// also counts its calls in dword_4CFA00).
RwV3d *sub_141320(RwV3d *arg_0, RwV3d *arg_4, RwMatrix *arg_8);

// sub_141080: *arg_0 = the rotation by the angles *arg_4 (about x, then y,
// then z) at the position *arg_8 (none for 0), written as a 4x4 matrix.
void sub_141080(RwMatrix *arg_0, RwV3d *arg_4, RwV3d *arg_8);
// sub_141590: arg_8 points arg_4 transformed by arg_C into arg_0 (the line
// test's atomic triangle callback, sub_FC6F0, passes a triangle's corners).
RwV3d *sub_141590(RwV3d *arg_0, RwV3d *arg_4, RwInt32 arg_8, RwMatrix *arg_C);
// sub_132FC0: passes arg_4 to each atomic of the clump arg_0 (a callback of
// RpClumpForAllAtomics); sub_16DCD0: the clump arg_0's bounding sphere into
// *arg_4; sub_FB990: the atomic arg_0's collision kind (its plugin data's
// +4, from sub_FB7A0); sub_173320: adds the atomic arg_0 to the collision
// world. Only the widths are known.
// sub_133010 and sub_173180: more of a model's set-up (the player's
// sub_10C650, the pickup's sub_FADB0); only the widths are known.
RpWorld *sub_173180(RpClump *arg_0);
void sub_16DCD0(RpClump *arg_0, RwSphere *arg_4);
void sub_FB990(RpAtomic *arg_0, RwInt32 arg_4);
RpWorld *sub_173320(RpAtomic *arg_0);
// sub_166D40: spawns a mounted weapon (a 0x5E0-byte entity) with the
// settings arg_0 and arg_4 at the matrix arg_8 for the trigger arg_10
// (a type_3D32F8's set-up passes its trigger's unk_140 to unk_17C); only
// the widths are known.
struct type_3D3548 *sub_166D40(RwInt32 arg_0, RwInt32 arg_4, RwMatrix *arg_8, RwInt32 arg_C,
                               struct type_712B0 *arg_10, RwInt32 arg_14, RwInt32 arg_18, RwInt32 arg_1C,
                               RwInt32 arg_20, RwInt32 arg_24, RwInt32 arg_28);
// sub_1413E0: likewise for arg_8 vectors (the matrix's rotation only).
RwV3d *sub_1413E0(RwV3d *arg_0, RwV3d *arg_4, RwInt32 arg_8, RwMatrix *arg_C);

// sub_1279C0 (game/render.h): the debug line from arg_0 along arg_4 (arg_8
// its side), as type_3D3548::vf_044 draws it; declared here too, since
// render.h brings in DSound.
void sub_1279C0(RwV3d *arg_0, RwV3d *arg_4, RwV3d *arg_8, RwReal arg_C, RwReal arg_10,
                RwInt32 arg_14, RwInt32 arg_18);

// sub_1414C0: *arg_0 = the point arg_4 transformed by arg_8 (AIData::sub_21A90
// passes an offset and its owner's frame matrix).
RwV3d *sub_1414C0(RwV3d *arg_0, RwV3d *arg_4, RwMatrix *arg_8);

// RenderWare's RtLineSphereIntersectionTest (rtray; the database calls it
// RaySphereIntersect): whether the segment arg_0 meets the sphere arg_4, with
// the distance along it in *arg_8.
extern "C" RwBool RtLineSphereIntersectionTest(RwLine *arg_0, RwSphere *arg_4, RwReal *arg_8);

// sub_91F40: a line test in the collision world arg_0; AIData::sub_29FC0
// passes the segment arg_4, 0, then 0x20000 and 0x10000 in either order,
// then 1, and treats a nonzero result as blocked. arg_8, when given, takes
// the hit (type_3D3548's sub_D2FC0 reads whether and how far along).
struct type_91F40
{
    RwInt32 unk_00;         // whether it hit: the hit triangle (sub_91F40)
    RwReal unk_04;          // how far along the line
    RwV3d unk_08;           // the hit point (sub_FC9F0 hands it out)
    RwV3d unk_14;           // the hit surface's normal
    RwV3d *unk_20;          // the hit sector's vertices
    RwInt32 unk_24;         // the hit surface (its material's game data)
    struct RpWorldSector *unk_28;   // the hit sector
};
RwInt32 sub_91F40(RpWorld *arg_0, RwLine *arg_4, type_91F40 *arg_8, RwInt32 arg_C,
                  RwInt32 arg_10, RwInt32 arg_14);

// sub_992B0 and sub_9A2D0: collision queries AIData::sub_30B90 runs for the
// records of a type_3DAFC8_1DDC it copies (arg_8 of the first and arg_C of
// the second is that copy); sub_992B0's arg_0 is 0 for records 0-3 and 1
// for 4-7. Otherwise only the widths are known.
struct type_3DAFC8_1DDC;
struct type_30B90_48;
void sub_992B0(RwInt32 arg_0, RwV3d *arg_4, type_3DAFC8_1DDC *arg_8, RwV3d *arg_C,
               type_30B90_48 *arg_10);
void sub_9A2D0(type_3D3548 *arg_0, RwV3d *arg_4, RwV3d *arg_8, type_3DAFC8_1DDC *arg_C);

// sub_19B1F0: AIData::sub_29FC0 passes whether it found a node to head for.
void sub_19B1F0(RwInt32 arg_0);

// sub_42210: takes two points, the owner and the entity whose vf_110 filled
// the second; tested against zero by AIData::sub_228A0.
RwInt32 sub_42210(RwV3d *arg_0, RwV3d *arg_4, type_3D3548 *arg_8, type_3D3548 *arg_C);

// sub_198800: the object registered under the key *arg_0 (0 for a zero
// key), looked up in the map dword_4F2728.
type_3DF8D8 *sub_198800(type_3DF8D8_04 *arg_0);
// Rotates *arg_0 about the axis *arg_4 by arg_8 radians (Rodrigues'
// formula), returning arg_0.
RwV3d *sub_13FFA0(RwV3d *arg_0, RwV3d *arg_4, RwReal arg_8);
// sub_1402B0: turns the line *arg_0 about the vertical through its start by
// arg_4 degrees; sub_1403D0: sets its end arg_4 from its start along its
// direction in x and y.
void sub_1402B0(RwLine *arg_0, RwReal arg_4);
void sub_1403D0(RwLine *arg_0, RwReal arg_4);
// sub_140910: *arg_4 copied into *arg_0 with its rotation transposed and
// its position negated.
void sub_140910(RwMatrix *arg_0, RwMatrix *arg_4);
// sub_141240: the signed angle in degrees from *arg_4 to *arg_0 in the
// ground plane.
RwReal sub_141240(RwV3d *arg_0, RwV3d *arg_4);
// sub_141690: *arg_0 = the identity as a 4x4 matrix at the position *arg_4
// (none for 0).
void sub_141690(RwMatrix *arg_0, RwV3d *arg_4);
// sub_141700: moves along a trapezoidal speed profile for the time arg_18
// (the speed *arg_0 updated, arg_C the top speed, arg_10 and arg_14 the
// acceleration and deceleration, arg_4 the distance to stop at); returns
// the distance covered, *arg_1C the profile's time; sub_141B10: one stage.
RwReal sub_141700(RwReal *arg_0, RwReal arg_4, RwReal arg_8, RwReal arg_C, RwReal arg_10, RwReal arg_14,
                  RwReal arg_18, RwReal *arg_1C);
RwReal sub_141B10(RwReal *arg_0, RwReal arg_4, RwReal arg_8, RwReal arg_C, RwReal *arg_10);
// Whether the point *arg_0 lies within the firing arcs of the matrix
// *arg_4: the cosine of its bearing off the at row, across the right row, at
// least arg_8, and across the up row at least arg_C in size.
RwInt32 sub_1409C0(RwV3d *arg_0, RwMatrix *arg_4, RwReal arg_8, RwReal arg_C);
// The same through a local of its own: an inline with no address, named for
// what it does. Evidence: the projectile generators (sub_11F500,
// sub_121C10, the kinds' vf_00C) keep sub_198800's result in a temporary
// and copy it into a second before they use it.
inline type_3DF8D8 *find_object(type_3DF8D8_04 *arg_0)
{
    type_3DF8D8 *r = sub_198800(arg_0);
    return r;
}

// sub_92430: casts a line down through arg_0 (from 60 above to 1000 below)
// against the collision worlds and keeps the highest hit up to arg_8 above
// arg_0 in *arg_4; returns that height.
RwReal sub_92430(RwV3d *arg_0, type_92430 *arg_4, RwReal arg_8);
// sub_16E740: the normal of the triangle arg_0 (vertex indices into the
// vertices arg_4, as a type_92430 holds them) into *arg_8.
void sub_16E740(void *arg_0, void *arg_4, RwV3d *arg_8);

// sub_32F70: registers an A* search of type arg_4 for the object arg_0 with
// the data arg_8 (a float: the callbacks take it as one; sub_34E20 passes
// 100) and id arg_C (a new id when 0) and returns the id; logs
// "AStar search registered..." through sub_19A750.
RwInt32 sub_32F70(type_67620 *arg_0, RwInt32 arg_4, RwReal arg_8, RwInt32 arg_C);
// sub_34E20: registers arg_0's A* search of type 10 (sub_32F70 with 100).
void sub_34E20(type_67620 *arg_0);
// sub_330E0: unregisters arg_0's A* search of type arg_4, logging it.
void sub_330E0(type_67620 *arg_0, RwInt32 arg_4);

// sub_F61A0, sub_F6200, sub_F6270: the A* search slots (arg_0 is 1 or 2 for
// sub_F61A0, a search id for the others): whether one is free, whether the
// search is still pending, and release it.
RwInt32 sub_F61A0(RwInt32 arg_0);
RwInt32 sub_F6200(RwInt32 arg_0);
void sub_F6270(RwInt32 arg_0);
// sub_34E60: runs the cover-point search (type 10) for arg_0 with id arg_4.
RwInt32 sub_34E60(type_67620 *arg_0, RwInt32 arg_4);

// sub_FA920: the index of the node arg_0.
RwInt32 sub_FA920(type_F8350 *arg_0);

// RenderWare Studio's RWSMalloc (the database's AllocBuffer): allocates
// size bytes; hint is a RenderWare memory hint (rws/memoryhandler.h).
void *RWSMalloc(RwUInt32 size, RwUInt32 hint);

// sub_67620: the object registered under handle arg_0 in dword_439E78.
type_67620 *sub_67620(RwInt32 arg_0);
// sub_71DB0, sub_71E40: read and write the global script register arg_0 (0
// to 100) as the type arg_4: 0 other, 1 int, 2 float, 3 a god name (an
// 8-byte key); the value is at arg_8 ("GetGlobalRegister_As...",
// "SetGlobalRegister_As...").
void sub_71DB0(RwInt32 arg_0, RwInt32 arg_4, void *arg_8);
void sub_71E40(RwInt32 arg_0, RwInt32 arg_4, void *arg_8);

// sub_6D0A0: looks up a set for arg_0, arg_4 and arg_8 (sub_EE360;
// AIData::sub_29630 passes a class, 5 and 2), composes its entries' rotations
// and offsets, and puts the resulting extent plus 33 (or 0) in *arg_C when
// given; returns whether the set was found and complete.
// Callers push the three selectors as dwords though it reads them as bytes.
bool sub_6D0A0(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwReal *arg_C);

// sub_6B060: reports the message arg_4 for the object arg_0 (AIData::sub_233B0
// passes 0 for arg_8).
bool sub_6B060(type_67620 *arg_0, const RwChar *arg_4, bool arg_8);

// sub_13F9E0: an angle in degrees brought into range; AIData::sub_2D3A0
// passes a heading in degrees and keeps the result.
RwReal sub_13F9E0(RwReal arg_0);
// sub_13FA50: normalises *arg_0 in place and returns its length (0 for a
// zero vector, left as it is).
RwReal sub_13FA50(RwV3d *arg_0);


// sub_1326C0: the signed difference of the headings arg_0 and arg_4 in
// degrees (the gimp vehicle's sub_1808D0 turns by it); only the widths are
// known.
// sub_19B650: empty in this build; returns 0.
RwInt32 sub_19B650(void *arg_0);

// sub_12DD80, sub_FB9C0, sub_FB960: about a collision atomic: whether it
// takes part, its flags (bit 3 excludes it) and its entity.
RwInt32 sub_FB9C0(RpAtomic *arg_0);
type_3D3548 *sub_FB960(RpAtomic *arg_0);

// sub_2C9B0: in this unit (src/recovered/unit_012000.cpp); AIData::sub_2CE90's
// atomic intersection callback.
RpAtomic *sub_2C9B0(RpIntersection *arg_0, RpWorldSector *arg_4, RpAtomic *arg_8, RwReal arg_C,
                    void *arg_10);

// sub_FA980: the node with index arg_0 (AIData::sub_28F30 passes a search
// result's unk_00).
type_F8350 *sub_FA980(RwInt32 arg_0);

// sub_13FB00: the quaternion arg_4 normalised into arg_0.
void sub_13FB00(struct RtQuat *arg_0, struct RtQuat *arg_4);
// sub_140C90: the squared distance between arg_0 and arg_4.
RwReal sub_140C90(RwV3d *arg_0, RwV3d *arg_4);

// sub_16A340: the mounted weapon (entity list 13) whose key (unk_4EC) is
// arg_0, or 0.
type_3DC9B0 *sub_16A340(RwInt32 arg_0);
// sub_16A380: the entity a path node refers to (through sub_FA920 and
// sub_16A340), or 0.
type_3DC9B0 *sub_16A380(type_F8350 *arg_0);

// sub_27500: in this unit (src/recovered/unit_012000.cpp); for a kind-0x11
// node, its entity's unk_4C0 (1.0 without one), else 0.8.
RwReal sub_27500(type_F8350 *arg_0);

// sub_16E950: copies the file name arg_4 up to its extension into arg_0.
void sub_16E950(RwChar *arg_0, const RwChar *arg_4);
// sub_140CE0: builds the matrix arg_0 at the position arg_4 looking along
// arg_8.
void sub_140CE0(RwMatrix *arg_0, RwV3d *arg_4, RwV3d *arg_8);
// sub_140F00: likewise, the matrix arg_0 at the position arg_4 with arg_8
// as its up vector.
void sub_140F00(RwMatrix *arg_0, RwV3d *arg_4, RwV3d *arg_8);

// sub_F8970: runs the node search arg_0 (filling its results) and returns
// its best node (game/pathnodes.h); callers pass (0, 0) or (1, 0) for the
// rest.
type_F8350 *sub_F8970(type_154C0_1048 *arg_0, RwInt32 arg_4, RwInt32 arg_8);

// sub_F7E80: the node filter for kind arg_0 (sub_F93D0 and 16 others).
type_F93D0 sub_F7E80(RwInt32 arg_0);

// sub_2C1E0: the heading of the direction arg_0, atan2(z, x).
RwReal sub_2C1E0(RwV3d *arg_0);

// Called by the script commands, only their widths known: sub_134B40 and
// sub_155470 create a soldier and a tank for an entity, sub_124EE0 fades the
// screen out (arg_4 1) or in, sub_128C20 sets the motion blur, sub_128C80
// the fog distances and sub_128CD0 the clip distances.
type_3D3548 *sub_134B40(type_3D3548 *arg_0);
type_3DC048 *sub_155470(type_712B0 *arg_0);
// sub_14C820 and sub_15A7B0: create a jeep and a flak gun for a trigger (a
// VehicleTrigger of type 0, a FlakTrigger); only the widths are known.
type_3DBC78 *sub_14C820(type_712B0 *arg_0);
struct type_3DC378;
type_3DC378 *sub_15A7B0(type_712B0 *arg_0);
void sub_124EE0(RwReal arg_0, RwInt32 arg_4);
void sub_128C20(RwInt32 arg_0, RwReal arg_4, RwReal arg_8);
void sub_128C80(RwReal arg_0, RwReal arg_4);
void sub_128CD0(RwReal arg_0, RwReal arg_4);
// sub_47F90: plays the object arg_0's entity arg_4's current performance, at
// the point *arg_8 facing *arg_C when given ("PlayCurrentPerformance" and
// the like); the flags are only known by width.
struct type_67620;
void sub_47F90(type_67620 *arg_0, type_3D3548 *arg_4, RwV3d *arg_8, RwV3d *arg_C,
               RwInt32 arg_10, RwInt32 arg_14, RwInt32 arg_18);
// The Distance Scheduler's registration calls (src/recovered/unit_034FA0.cpp):
// sub_35200 registers arg_0 for a test and returns the registration, whose
// first field is its handle ("RegisterDistanceCheck"); sub_35330 unregisters
// all of arg_0's, sub_35360 one registration.
struct alfasched_entry;
type_67620 *sub_35200(type_67620 *arg_0, RwReal arg_4, RwReal arg_8, RwInt32 arg_C,
                      RwInt32 arg_10, RwInt32 arg_14, type_3D2E7C *arg_18, RwInt32 arg_1C,
                      RwInt32 arg_20);
void sub_35330(type_67620 *arg_0);
// sub_34E40 unregisters arg_0's A* search of type 10 (unit_033520);
// sub_40AE0 takes arg_0 off the two lists at dword_439840 and dword_4398B0
// (unit_040720).
void sub_34E40(type_67620 *arg_0);
void sub_40AE0(type_67620 *arg_0);
void sub_35360(alfasched_entry *arg_0);
// The render parts of the clump arg_0: sub_16E0C0 returns the mask of those
// shown, sub_16E080 sets it, sub_16D8C0 shows or hides the part arg_4
// ("SetRenderPartState", "GetRenderPartState", "SetRenderPartStateByName").
RwUInt32 sub_16E0C0(RpClump *arg_0);
void sub_16E080(RpClump *arg_0, RwUInt32 arg_4);

// sub_17AD60 and sub_17ADF0: a soldier's dying and hurt reactions on its
// second animation (type_3DAFC8::sub_13C490); only the widths are known.
void sub_17AD60(struct type_7C8D0 *arg_0);
void sub_17ADF0(struct type_7C8D0 *arg_0);
bool sub_16D8C0(RpClump *arg_0, const RwChar *arg_4, bool arg_8);
// The same, by the part's name (the vehicles' "destroyed" part, sub_153CB0),
// and whether the clump has a part of that name.
bool sub_16D8C0(RpClump *arg_0, const RwChar *arg_4, bool arg_8);
RwInt32 sub_16D900(RpClump *arg_0, const RwChar *arg_4);
// The clump banks: sub_16EEC0 requests bank arg_0's load
// ("RequestClumpBankLoad"), sub_16EE80 tells whether it is loaded.
void sub_16EEC0(RwInt32 arg_0);
RwInt32 sub_16EE80(RwInt32 arg_0);
// sub_EACA0: queues the console message arg_0 (split at a word under 47
// characters) of the kind arg_4, typed out with a sound when arg_8 is set
// (the text manager, game/textmanager.h; "SetCheckPointRegister" passes 2
// and 1).
void sub_EACA0(const RwChar *arg_0, RwInt32 arg_4, RwInt32 arg_8);
// sub_EACA0 for a plain message, as an inline with no address and so no
// database name, named for what it does. Evidence: the kill messages
// (sub_1ACBA0, sub_1AD750) keep a no-code inline expansion's frame
// after their message texts (docs/toolchain.md).
inline void show_message(const RwChar *arg_0)
{
    sub_EACA0(arg_0, 0, 0);
}
// sub_1727E0: the four starting sections *arg_0 ("SetStartingSections").
void sub_1727E0(RwInt32 *arg_0);
// sub_D9320: takes the checkpoint snapshot ("TakeCheckpointSnapshot").
void sub_D9320();
// sub_F2FF0: spawns the particle system arg_0 at the matrix arg_4
// ("SpawnParticle" passes 0, 1, 0 and 0 for the rest), returning what
// "PZ_Manipulate" hands to sub_17DB90; only the widths are known.
RwInt32 sub_F2FF0(RwInt32 arg_0, RwMatrix *arg_4, RwInt32 arg_8, RwInt32 arg_C, bool arg_10,
               bool arg_14);
// The CCESS pool's script commands ("SpecialCCESSPoolCreation" and the
// rest) are declared in types/ccess.h.
// sub_144F20: whether the object whose kind bits are arg_4 lies in the
// trigger volume arg_0 ("IsNamedEntityInTrigger"); only the widths are known.
struct RwV3d;
class Trigger;
RwInt32 sub_144F20(RwV3d *arg_0, Trigger *arg_4);
// The cover point arg_0's peek flags (sub_F8FA0, "GetCoverPointPeekFlags")
// and type (sub_F8FC0, "GetCoverPointType").
RwInt32 sub_F8FA0(type_F8350 *arg_0);
RwInt32 sub_F8FC0(type_F8350 *arg_0);
// sub_140490: three weights for the point arg_0 against the points arg_4,
// arg_8 and arg_C into *arg_10 (the soldier's five-way blend,
// type_3DAFC8::sub_139620): the triangle weights, false when the point lies
// outside.
struct type_140490;
bool sub_140490(type_140490 *arg_0, type_140490 *arg_4, type_140490 *arg_8, type_140490 *arg_C,
                type_140490 *arg_10);
// sub_FA650: the corner connected to the cover point arg_0, or 0
// ("IsConnectedCorner" and the like).
type_F8350 *sub_FA650(type_F8350 *arg_0);
// The script timers: sub_733D0 registers the timer arg_4 for the object
// arg_0 to post the message arg_8 after arg_C frames ("RegisterTimer");
// sub_734E0 unregisters the object's timers with the message arg_4
// ("UnregisterTimerByMessage"). Only the widths are known otherwise.
RwInt32 sub_733D0(type_67620 *arg_0, RwInt32 arg_4, RwInt32 arg_8, RwReal arg_C);
void sub_734E0(type_67620 *arg_0, RwInt32 arg_4);
// sub_33190: unregisters the A* check arg_0 (the handle sub_28A60 returns;
// Source/GameCore/ai/astarscheduler.cpp).
void sub_33190(RwInt32 arg_0);
// sub_3F0D0: the group with the id arg_0 ("ForceManeuver";
// src/recovered/unit_03DF30.cpp).
struct type_3DF30;
type_3DF30 *sub_3F0D0(RwInt32 arg_0);
// sub_48EE0: plays the object arg_0's entity arg_4's current scene
// performance ("PlayCurrentScene" and the like), at the point *arg_8 facing
// *arg_C when given; the flag arg_10 is only known by width.
void sub_48EE0(type_67620 *arg_0, type_3D3548 *arg_4, RwV3d *arg_8, RwV3d *arg_C,
               RwInt32 arg_10);
// sub_F12A0: fires the particle spawners on the entity arg_0 once more and
// frees them ("DestroySelf", sub_454A0, passes 0 for the position arg_4;
// types/type_4B9E90.h).
void sub_F12A0(type_3D3548 *arg_0, RwV3d *arg_4);
// SoundEmitter_Stop (the database's name, 0x23B8B0): stops the sound
// emitter arg_0 (arg_4 0: stop and restart, 1: start only, 2: restart);
// sub_3C6C0 then ends the lasting sound with that id
// ("PG_ManipulateProjectileGenerator").
struct type_44C4E8;
extern "C" void SoundEmitter_Stop(type_44C4E8 *arg_0, RwInt32 arg_4);
// sub_84300: loads the sound bank under the key *arg_0 ("LoadSoundBank");
// sub_777F0: loads the animation group arg_C of the object named arg_0 under
// the key arg_4 ("LoadAnimGroup", which passes 0 for arg_10); sub_77B70:
// finds the facial animation arg_0, giving its group and index in *arg_4 and
// *arg_8 (0 if there is none; sub_5AC50). Only the widths are known.
struct type_825E0;
void sub_84300(type_825E0 *arg_0);
// RenderWare's RwV3dLength (0x2A3C70; the database calls it
// PVSFindDiagonalSizeOfBBox): callers pass their vectors to it (rw/bavector.h).
// sub_61700: whether the line from *arg_4 (raised by arg_0's unk_40 plus 33)
// to *arg_8 (raised by 100) is clear for arg_0 (sub_D2FC0, with the flag
// arg_10), scaling *arg_C, the fraction along it, by its length.
RwInt32 sub_61700(type_3D3548 *arg_0, RwV3d *arg_4, RwV3d *arg_8, RwReal *arg_C, RwInt32 arg_10);
// sub_61BA0: whether the horizontal direction from arg_0 to *arg_4 lies
// within about 30 degrees of arg_0's facing (cosine at most 0.866 counts,
// as written).
RwInt32 sub_61BA0(type_3D3548 *arg_0, RwV3d *arg_4);
// The Vision Scheduler's tests of whether arg_0 sees arg_4 (unit_040720,
// which declares them too): within the range arg_8 (sub_414F0, giving the
// distance in *arg_C), by angle (sub_413E0), and the line checks sub_41AD0,
// sub_415E0 and sub_421C0 ("CanSee").
RwInt32 sub_413E0(type_3D3548 *arg_0, type_3D3548 *arg_4);
RwInt32 sub_414F0(type_3D3548 *arg_0, type_3D3548 *arg_4, RwReal arg_8, RwReal *arg_C);
RwInt32 sub_415E0(type_3D3548 *arg_0, type_3D3548 *arg_4);
RwInt32 sub_41AD0(type_3D3548 *arg_0, type_3D3548 *arg_4);
RwInt32 sub_421C0(type_3D3548 *arg_0, type_3D3548 *arg_4);
// sub_35D90: whether arg_0 and arg_4 lie within the squared distances arg_8
// and arg_C, storing the distance in *arg_10 (unit_034FA0, which declares it
// too; "IsWithinRangeOfObject").
RwInt32 sub_35D90(type_3D3548 *arg_0, type_3D3548 *arg_4, RwReal arg_8, RwReal arg_C,
                  RwReal *arg_10);
// sub_D8C20: quits the level ("QuitLevel"); sub_D8CC0: quits and loads
// level arg_0 (1 to 8, "QuitAndLoadNextLevel").
void sub_D8C20();
void sub_D8CC0(RwInt32 arg_0);
struct type_449C94_08;
RwInt32 sub_777F0(const RwChar *arg_0, type_449C94_08 arg_4, RwInt32 arg_C, RwV3d *arg_10);
RwInt32 sub_77B70(RwInt32 arg_0, void **arg_4, void **arg_8);
void sub_3C6C0(RwInt32 arg_0);

// sub_12F0A0: the game's hook in RenderWare Studio's entity messages (the
// stream handlers of attributehandlerstrfuncs call it first): sets
// byte_4CF88C while dword_4B8710 is set.
void sub_12F0A0();
// sub_16D7F0 and sub_16D850: open and close the timing section arg_0
// around a piece of work (also declared in types/soundbank.h).
void sub_16D7F0(RwInt32 arg_0);
void sub_16D850(RwInt32 arg_0);

#endif
