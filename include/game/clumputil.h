/*
 * The clump utilities (unit_16D8C0): render parts shown or hidden by name,
 * atomics found by name, hierarchy frames found by id, a clump's frames
 * pruned to its hierarchy, bounding spheres and the rest, mostly through
 * RenderWare's iterators with a context on the caller's stack. The
 * callbacks are named for their addresses unless the database names them.
 */
#ifndef GAME_CLUMPUTIL_H
#define GAME_CLUMPUTIL_H

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "rw/baframe.h"
#include "rw/rpatomic.h"
#include "rw/rphanim.h"

// sub_16D8C0's context for sub_16E450.
struct type_16E450
{
    const RwChar *unk_00;       // the part's name
    bool *unk_04;               // shown
    bool *unk_08;               // set when a part matched
};

// sub_16D900's context for sub_16E500.
struct type_16E500
{
    const RwChar *unk_00;       // the atomic's name
    RwInt32 *unk_04;            // the atomic found
};

// sub_16D940's context for sub_16DAB0.
struct type_16DAB0
{
    RwInt32 *unk_00;            // the id sought
    RwFrame *unk_04;            // the frame found
};

// sub_16D9A0's context for sub_16DB20.
struct type_16DB20
{
    RwFrame *unk_00;            // the clump's frame
    RwInt32 *unk_04;            // the ids kept, and how many
    RwInt32 *unk_08;
    RwInt8 *unk_0C;             // the depth now
    RwInt8 *unk_10;             // the depth a kept frame was met at
};

// Shows or hides the render part arg_4 of the clump arg_0; whether it has
// one of that name.
struct RpClump;
bool sub_16D8C0(RpClump *arg_0, const RwChar *arg_4, bool arg_8);
RwInt32 sub_16D900(RpClump *arg_0, const RwChar *arg_4);
// The frame below arg_0 whose hierarchy id is arg_4, or 0.
RwFrame *sub_16D940(RwFrame *arg_0, RwInt32 arg_4);
RpHAnimHierarchy *sub_16D970(RpClump *arg_0);
// Detaches the clump arg_0's hierarchy frames from its frame, keeping only
// its own frame's atomics.
void sub_16D9A0(RpClump *arg_0);
RwFrame *sub_16DAB0(RwFrame *arg_0, void *arg_4);
RwFrame *sub_16DB20(RwFrame *arg_0, void *arg_4);
RwFrame *sub_16DC20(RwFrame *arg_0, void *arg_4);
RwObject *sub_16DC70(RwObject *arg_0, void *arg_4);
RpAtomic *Clump_FindFirstAtomic(RpClump *arg_0);
// The clump arg_0's bounding sphere into *arg_4, in its first atomic's
// frame (radius -1 with no atomic); sub_16DD80 grows the sphere *arg_4 over
// each atomic's world sphere.
void sub_16DCD0(RpClump *arg_0, RwSphere *arg_4);
RpAtomic *sub_16DD80(RpAtomic *arg_0, void *arg_4);
// Sets the bounding sphere of each atomic of the clump arg_0 (centre
// *arg_4, radius arg_8; sub_16E210 per atomic).
void sub_16DFA0(RpClump *arg_0, RwV3d *arg_4, RwReal arg_8);
RpAtomic *sub_16E210(RpAtomic *arg_0, void *arg_4);
// Sets the collision kind arg_4 of the clump arg_0 and of each of its
// atomics (sub_16E010).
void sub_16DFE0(RpClump *arg_0, RwInt32 arg_4);
RpAtomic *sub_16E010(RpAtomic *arg_0, void *arg_4);
// Detaches the clump arg_0's frame and runs sub_7C830 on its atomics.
void sub_16E040(RpClump *arg_0);
// Moves the atomics of the clump arg_4 onto the frames of the same
// hierarchy ids in the clump arg_0 (sub_16E140), destroying arg_4's frames.
void sub_16E100(RpClump *arg_0, RpClump *arg_4);
RpAtomic *sub_16E140(RpAtomic *arg_0, void *arg_4);
// The render parts' callbacks (sub_16E080 and sub_16E0C0).
struct type_16E250
{
    RwInt32 unk_00;             // the part's index
    RwUInt32 unk_04;            // the mask of those shown
};
RpAtomic *sub_16E250(RpAtomic *arg_0, void *arg_4);
RpAtomic *sub_16E370(RpAtomic *arg_0, void *arg_4);
// The atomic arg_0's string user data named arg_4, or 0.
struct RpUserDataArray *sub_16E3C0(RpAtomic *arg_0, const RwChar *arg_4);
RpAtomic *sub_16E450(RpAtomic *arg_0, void *arg_4);
RpAtomic *sub_16E500(RpAtomic *arg_0, void *arg_4);
RwFrame *GetHierarchyFrameRecurse(RwFrame *arg_0, void *arg_4);
RpAtomic *Clump_CaptureFirstAtomic(RpAtomic *arg_0, void *arg_4);

// sub_16E5C0's counts (its callbacks count a world's atomics, clumps and
// lights).
struct type_16E5C0
{
    RwInt32 unk_00;
    RwInt32 unk_04;
    RwInt32 unk_08;
};
struct RpLight *sub_16E540(struct RpLight *arg_0, void *arg_4);
RpClump *sub_16E560(RpClump *arg_0, void *arg_4);
RpAtomic *sub_16E580(RpAtomic *arg_0, void *arg_4);
struct RpWorldSector *sub_16E5A0(struct RpWorldSector *arg_0, void *arg_4);
bool sub_16E5C0(struct RpWorld *arg_0, RwInt32 arg_4, RwInt32 arg_8);
struct RwTexture *sub_16E6B0(struct RwTexture *arg_0, void *arg_4);
bool sub_16E6F0(struct RwTexDictionary *arg_0);
void sub_16E740(void *arg_0, void *arg_4, RwV3d *arg_8);
void sub_16E860(RwV3d *arg_0, RwV3d *arg_4, RwV3d *arg_8, RwV3d *arg_C);
void sub_16E950(RwChar *arg_0, const RwChar *arg_4);

// Defined elsewhere: the collision kind of a clump and of an atomic, an
// atomic's render mask (unit_0FB7A0), and sub_12DD40 (the atomic arg_0
// shown or not; only the widths are known).
// The collision-kind setters take a byte (unit_0FB7A0), but these calls pass
// the whole dword unconverted: the prototype they saw took an int (resolved
// to the same functions by name).
void sub_FBBE0(RpClump *arg_0, RwInt32 arg_4);
void sub_FB990(RpAtomic *arg_0, RwInt32 arg_4);
void sub_FB9F0(RpAtomic *arg_0, RwInt32 arg_4);

// From the clump data plugin (game/clumpdata.h): the hierarchy's ids kept
// (the count, and the ids).
RwInt32 sub_EC290(RpClump *arg_0);
RwInt32 *sub_EC2B0(RpClump *arg_0);

#endif
