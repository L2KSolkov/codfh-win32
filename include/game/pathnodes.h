/*
 * The path-node manager (src/recovered/unit_0F7BA0.cpp): the graph
 * (unk_4C00E8, types/type_4C00E8.h), which sub_F8350 reads from a stream,
 * its set-up, restart and shutdown, the grid lookups, and the table of
 * occupied alarm nodes (dword_4C01A0, hashed by node index in dword_4C0164).
 */
#ifndef GAME_PATHNODES_H
#define GAME_PATHNODES_H

#include "rw/ostypes.h"
#include "rw/bastream.h"
#include "types/alfahash.h"
#include "types/type_4C00E8.h"
#include "types/type_D48D0.h"
#include "types/type_F8350.h"
#include "types/type_154C0_1048.h"

struct AIData;

// An occupied alarm node: its index, who holds it, whether the slot is in
// use and the slot's own index.
struct type_4C01A0
{
    RwInt32 unk_00;
    type_D48D0 unk_04;
    RwInt32 unk_08;
    RwInt32 unk_0C;

    // Defined in the class: sub_F7BA0 expands it; the table's dynamic
    // initializer takes its out-of-line copy (sub_FA9B0).
    type_4C01A0()
    {
    }
};

extern type_4C00E8 unk_4C00E8;
extern alfahash dword_4C0164;
// The occupied nodes' table's size: the image's, or with the port's debug tools room for their
// bots (port/src/debug/trigtools.cpp) on generated graphs with cover.
#if defined(CODFH_DRAW_TRIGGERS) && !defined(CODFH_SP)
#define OCCUPIED_NODES 0x200
#else
#define OCCUPIED_NODES 0x80
#endif
extern type_4C01A0 dword_4C01A0[OCCUPIED_NODES];

// Takes (arg_8) or releases the alarm node arg_4 for the AI object arg_0
// (0: for no one); 0 when another holds it.
RwInt32 sub_F7BA0(AIData *arg_0, type_F8350 *arg_4, bool arg_8);
// Clears the occupied nodes.
void sub_F7DC0();
// The occupancy hash's key and equality.
RwUInt32 sub_F7E50(void *arg_0);
bool sub_F7E60(void *arg_0, void *arg_4);
// Set-up, restart and shutdown, the graph's clear, release and read.
void sub_F7F60();
void sub_F8010();
void sub_F8120();
void sub_F8160();
void sub_F8180();
void sub_F8270();
void sub_F8350(RwStream *arg_0);
// The grid cell of the point arg_0 (its column and row into *arg_4 and
// *arg_8), or -1 off the grid.
RwInt32 sub_F8770(RwV3d *arg_0, RwInt32 *arg_4, RwInt32 *arg_8);
// The grid cells a square of half-width arg_4 around arg_0 covers
// (types/type_4C00E8.h).
// Runs the node search arg_0: the rings of cells around its point, nearest
// first, each cell's nodes through its filter (sub_F8D30); the best node,
// or 0. arg_4 is passed on (whether a full result list still counts);
// arg_8 only by width.
type_F8350 *sub_F8970(type_154C0_1048 *arg_0, RwInt32 arg_4, RwInt32 arg_8);
RwInt32 sub_F8D30(RwInt32 arg_0, RwInt32 arg_4, type_154C0_1048 *arg_8, RwInt32 arg_C, RwInt32 arg_10);
// The searches run and their peak, and the time they took in all, last and
// at the last start.
#ifdef CODFH_PLAIN
extern RwUInt32 &dword_4C0154;
#else
extern RwUInt32 dword_4C0154;
#endif
#ifdef CODFH_PLAIN
extern RwUInt32 &dword_4C0158;
#else
extern RwUInt32 dword_4C0158;
#endif
#ifdef CODFH_PLAIN
extern RwUInt32 &dword_4C015C;
#else
extern RwUInt32 dword_4C015C;
#endif
extern RwUInt32 dword_4C09A0;
extern RwUInt32 dword_4C09A4;
// A door node's offsets for the one passing it: the position into *arg_4
// and the turn into *arg_8 (when given), by its kind and flags.
void sub_F8FE0(type_F8350 *arg_0, RwV3d *arg_4, RwV3d *arg_8);
// Whether a height difference arg_0 is within a node's reach (150); an
// inline with no address, named for what it does. Evidence: the node
// filters (sub_F93D0 and its kin) test a 1-or-0 result held in a temporary
// allocated before the one of its argument's cast, as an inline with a
// return on each branch gets.
inline RwInt32 within_height(RwReal arg_0)
{
    if (arg_0 < 150.0f)
    {
        return 1;
    }
    return 0;
}

// The node filters, by the kind sub_F7E80 picks them for.
RwInt32 sub_F93D0(type_F8350 *arg_0, RwInt32 arg_4, type_154C0_1048 *arg_8, RwReal arg_C);
RwInt32 sub_F9440(type_F8350 *arg_0, RwInt32 arg_4, type_154C0_1048 *arg_8, RwReal arg_C);
RwInt32 sub_F9710(type_F8350 *arg_0, RwInt32 arg_4, type_154C0_1048 *arg_8, RwReal arg_C);
RwInt32 sub_F9750(type_F8350 *arg_0, RwInt32 arg_4, type_154C0_1048 *arg_8, RwReal arg_C);
RwInt32 sub_F9780(type_F8350 *arg_0, RwInt32 arg_4, type_154C0_1048 *arg_8, RwReal arg_C);
RwInt32 sub_F97F0(type_F8350 *arg_0, RwInt32 arg_4, type_154C0_1048 *arg_8, RwReal arg_C);
RwInt32 sub_F9820(type_F8350 *arg_0, RwInt32 arg_4, type_154C0_1048 *arg_8, RwReal arg_C);
RwInt32 sub_F9A70(type_F8350 *arg_0, RwInt32 arg_4, type_154C0_1048 *arg_8, RwReal arg_C);
RwInt32 sub_F9AA0(type_F8350 *arg_0, RwInt32 arg_4, type_154C0_1048 *arg_8, RwReal arg_C);
RwInt32 sub_F9C80(type_F8350 *arg_0, RwInt32 arg_4, type_154C0_1048 *arg_8, RwReal arg_C);
RwInt32 sub_F9DA0(type_F8350 *arg_0, RwInt32 arg_4, type_154C0_1048 *arg_8, RwReal arg_C);
RwInt32 sub_FA260(type_F8350 *arg_0, RwInt32 arg_4, type_154C0_1048 *arg_8, RwReal arg_C);
RwInt32 sub_FA330(type_F8350 *arg_0, RwInt32 arg_4, type_154C0_1048 *arg_8, RwReal arg_C);
RwInt32 sub_FA440(type_F8350 *arg_0, RwInt32 arg_4, type_154C0_1048 *arg_8, RwReal arg_C);
RwInt32 sub_FA470(type_F8350 *arg_0, RwInt32 arg_4, type_154C0_1048 *arg_8, RwReal arg_C);
RwInt32 sub_FA570(type_F8350 *arg_0, RwInt32 arg_4, type_154C0_1048 *arg_8, RwReal arg_C);
RwInt32 sub_FA5D0(type_F8350 *arg_0, RwInt32 arg_4, type_154C0_1048 *arg_8, RwReal arg_C);
// A named variable as sub_198900 hands it to its callback: only its kind
// (unk_10) and value (unk_24) are known.
struct type_FA620
{
    RwInt32 unk_00[4];
    RwInt32 unk_10;
    RwInt32 unk_14[4];
    RwInt32 unk_24;
};

// The named nodes' registration callback (sub_198900): makes the variable
// arg_0 a node (kind 0x10) holding arg_8.
RwInt32 sub_FA620(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8);
// The range of sub_FA330's filter (1000; .rdata, loaded twice rather than
// folded).
extern const RwReal flt_3D9484;

#endif
