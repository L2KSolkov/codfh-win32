/*
 * type_4C00E8: the path-node graph, a single global (unk_4C00E8) that
 * sub_F8350 fills from a RenderWare stream; named after that first (and
 * only) instance. The database also names two of its fields as globals
 * (dword_4C00F0 and dword_4C0114).
 *
 *   +0x04 unk_04  a grid cell's size (dword_4C00EC)
 *   +0x08 unk_08  the node count (dword_4C00F0)
 *   +0x18 unk_18  the grid's origin (dword_4C0100)
 *   +0x24 unk_24  the grid's width and height in cells (dword_4C010C,
 *   +0x28 unk_28  dword_4C0110; sub_F8820 clips a square to them)
 *   +0x2C unk_2C  the node table: node pointers by index (dword_4C0114);
 *                 AIData::sub_28470 and sub_28640 index it by search results
 *   +0x3C unk_3C  each cell's link list index, 0xFFFF for none (dword_4C0124,
 *                 indexed row by row: y * unk_24 + x)
 *   +0x48 unk_48  the link lists: link word arrays by index (dword_4C0130),
 *                 walked with type_3CE1FC
 */
#ifndef TYPE_4C00E8_H
#define TYPE_4C00E8_H

#include "rw/ostypes.h"
#include "types/type_F8350.h"

struct type_4C00E8
{
    RwInt32 unk_00;
    RwInt32 unk_04;             // a grid cell's size
    RwInt32 unk_08;
    RwInt32 unk_0C;
    RwInt32 unk_10;
    RwInt32 unk_14;
    RwV3d unk_18;               // the grid's origin
    RwInt32 unk_24;
    RwInt32 unk_28;
    type_F8350 **unk_2C;
    RwInt32 unk_30;
    RwUInt8 *unk_34;            // the nodes' buffer (the table holds offsets
                                // into it until sub_F8350 fixes them up)
    RwInt32 unk_38;
    RwUInt16 *unk_3C;
    RwInt32 unk_40;
    RwUInt32 unk_44;            // the link lists' count
    RwUInt32 **unk_48;
    RwInt32 unk_4C;
    RwUInt8 *unk_50;            // the link lists' buffer
    RwInt32 unk_54;
    RwUInt8 *unk_58;            // the named nodes (12 bytes each: a key and
    RwUInt32 unk_5C;            // a node index) and their size in bytes
    RwInt32 unk_60;             // set up (sub_F7F60)
    RwInt32 unk_64;             // set once the graph is loaded (the A*
                                // search refuses to start without it)

    // A cell's link list index: an inline accessor with no address and so
    // no database name; named for its field. Evidence: type_3D3548's vf_1D0
    // loads the table before the index, which a plain subscript does not.
    RwUInt16 get_unk_3C(RwInt32 arg_0)
    {
        return unk_3C[arg_0];
    }
};

// The grid cells a square of half-width arg_4 around arg_0 covers, into
// arg_8 (the lowest x and y, then the highest); 0 when it misses the grid.
// Unless arg_C is set, the range is clipped to the grid.
RwInt32 sub_F8820(RwV3d *arg_0, RwReal arg_4, RwInt32 *arg_8, RwInt32 arg_C);

#endif
