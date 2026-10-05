/*
 * The triggers' bookkeeping (unit_144940): the trigger table (dword_4CFE30,
 * 2000 by handle, game/data.h; dword_429D00 the last handle given), the
 * pools of proximity messages, message lists and moved triggers, and the
 * spatial table unk_4D1DB8 the triggers that test their surroundings are
 * kept in (sub_1458B0 says which). Only what the unit uses is known.
 */
#ifndef TYPE_4D1DB8_H
#define TYPE_4D1DB8_H

#include "rw/ostypes.h"
#include "types/alfasched.h"
#include "rw/batypes.h"

class Trigger;
struct type_4CFE30;

struct type_144E80;
// A cell's record (unk_13B0, by the index a cell holds): its list of
// trigger handles, whether it changed since sub_146F10, and whether it is
// in use (sub_147020).
struct type_1461F0
{
    type_144E80 *unk_00;
    RwInt8 unk_04;
    RwInt8 unk_05;
};
struct type_146B70
{
    RwReal unk_00;
    RwReal unk_04;
    RwReal unk_08;
    RwReal unk_0C;
};
struct type_4D1DB8
{
    RwInt32 unk_00;
    RwInt16 unk_04[50][50];     // the cells by x and z: their records
                                // (-1 for none; sub_145EB0), counts while
                                // it is sized (sub_146360)
    RwReal unk_138C;            // the triggers' extent: x from and to,
    RwReal unk_1390;
    RwReal unk_1394;            // z from and to
    RwReal unk_1398;
    RwReal unk_139C;            // and a fiftieth of each (the cells' size)
    RwReal unk_13A0;
    RwInt32 unk_13A4;
    RwInt32 unk_13A8;
    RwInt32 unk_13AC;           // its cells' count (the pool is set up)
    type_1461F0 *unk_13B0;      // the cells' records (sub_1461F0)
    type_16C2A0 unk_13B4;       // a pool

    // Its constructor and destructor build and take down the pool.
    type_4D1DB8();
    ~type_4D1DB8();
    // Sets itself up for the arg_0 triggers of arg_4, and the rest of the
    // build; only the widths are known.
    void sub_145FB0(RwInt32 arg_0, type_4CFE30 **arg_4);
    // The trigger arg_0's extent (x from and to, z from and to) into
    // *arg_4.
    void sub_146B70(type_4CFE30 *arg_0, struct type_146B70 *arg_4);
    void sub_146190();
    void sub_1461F0();
    void sub_146360(type_4CFE30 *arg_0);
    // Refreshes it; whether the cells arg_0 changed.
    void sub_146F10();
    RwInt32 sub_146F50(RwV3d *arg_0);
    // Builds the table from the arg_0 triggers of arg_4; empties it.
    void sub_145EB0(RwInt32 arg_0, type_4CFE30 **arg_4);
    void sub_145F50();
    // Adds and removes the trigger arg_0.
    void sub_1464E0(Trigger *arg_0);
    void sub_146640(Trigger *arg_0);
    // The cell list for the point arg_0.
    type_144E80 *sub_1466B0(RwV3d *arg_0);
    // Whether the trigger arg_0 is in it.
    RwInt32 sub_146E80(Trigger *arg_0);
    // Adds the trigger arg_8 to the cell (arg_0, arg_4), and takes it out.
    void sub_146770(RwInt32 arg_0, RwInt32 arg_4, Trigger *arg_8);
    void sub_146A00(RwInt32 arg_0, RwInt32 arg_4, Trigger *arg_8);
    // The extents of a sphere, a cylinder and a box around the matrix
    // arg_0.
    void sub_146C30(struct RwMatrixTag *arg_0, RwReal arg_4, type_146B70 *arg_8);
    void sub_146C90(struct RwMatrixTag *arg_0, RwReal arg_4, RwReal arg_8, type_146B70 *arg_C);
    void sub_146CD0(struct RwMatrixTag *arg_0, RwReal arg_4, RwReal arg_8, RwReal arg_C, type_146B70 *arg_10);
    // A free cell record's index.
    RwInt32 sub_147020();
};
extern type_4D1DB8 unk_4D1DB8;

// Set up (sub_144990), and the spatial table built (sub_144B80).
extern RwInt32 dword_4D1D70;
extern RwInt32 dword_4D1D74;
extern RwInt32 dword_429D00;
// The pools: proximity messages (400 of 0x1C), message lists (400 of 0x20)
// and moved triggers (dword_4D1D98, types/type_44350.h).
extern type_16C2A0 dword_4D318C;
extern type_16C2A0 dword_4D1D78;
// Whether the trigger arg_0 goes in the spatial table.
RwInt32 sub_1458B0(Trigger *arg_0);
// Warns of the triggers and pool elements shutdown finds left.
void sub_144AD0();

// A range of triggers (handles unk_00 to unk_02) in a cell's list, and the
// cells around a matrix (sub_145B40: a mask of which are near, and their
// list), which an entity's trigger volume keeps (sub_144C80).
struct type_144E80
{
    RwInt16 unk_00;
    RwInt16 unk_02;
    type_144E80 *unk_04;
};
struct type_145B40
{
    RwInt32 unk_00;
    type_144E80 *unk_04;
};
struct RwMatrixTag;
struct type_3D3548;
void sub_145B40(RwMatrixTag *arg_0, type_145B40 *arg_4, RwUInt8 arg_8);
RwInt16 sub_144E80(type_144E80 **arg_0, RwInt32 *arg_4, RwInt16 arg_8);
// The entity arg_0 enters and leaves the trigger arg_4.
void sub_145060(type_3D3548 *arg_0, Trigger *arg_4);
void sub_145640(type_3D3548 *arg_0, Trigger *arg_4);
struct RwV3d;
RwInt32 sub_144F20(RwV3d *arg_0, Trigger *arg_4);
// Updates the trigger arg_0 in the spatial table after it moved, and the
// trigger volumes of the entities that keep one.
void sub_145A40(Trigger *arg_0);
// Orders two trigger handles (a qsort comparator).
RwInt32 __cdecl sub_145E20(const void *arg_0, const void *arg_4);
RwInt32 sub_145000(RwMatrixTag *arg_0, Trigger *arg_4);
RwInt32 sub_145030(RwMatrixTag *arg_0, Trigger *arg_4);
// A trigger kind with a virtual of its own at +0x30 (the stream, sound and
// animation pack triggers' entry action), as sub_145060 calls it.
struct type_145060_30
{
    virtual void vf_000();
    virtual void vf_004();
    virtual void vf_008();
    virtual void vf_00C();
    virtual void vf_010();
    virtual void vf_014();
    virtual void vf_018();
    virtual void vf_01C();
    virtual void vf_020();
    virtual void vf_024();
    virtual void vf_028();
    virtual void vf_02C();
    virtual void vf_030();
};
// The section streaming's queue: whether the section is queued, and queueing
// it (callers pass "" for the resource path: the pooled empty literal, 1-byte
// aligned, at 0x3D292F; the database's pResourcePath).
void sub_81EB0(RwInt32 arg_0, const RwChar *arg_4, RwInt32 arg_8);
// Sends block 6 of the triggers in the cells arg_4 to the entity arg_0.
void sub_145970(type_3D3548 *arg_0, type_145B40 *arg_4);
// The shapes' point tests: sub_9ACE0 (types/type_92430.h) and these two.
RwInt32 sub_92900(RwV3d *arg_0, RwMatrixTag *arg_4, RwReal arg_8, RwReal arg_C);
RwInt32 sub_9ABE0(RwV3d *arg_0, RwMatrixTag *arg_4, RwReal arg_8, RwReal arg_C, RwReal arg_10);

#endif
