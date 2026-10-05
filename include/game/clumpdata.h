/*
 * The game's clump data plugin (0x4210, registered by sub_EBF10): per clump,
 * whether it was read with its data, its tagged matrices (chunk 0x4211), a
 * vector per hierarchy node (0x4212) and a list of ints (0x4213), read by
 * sub_EBF40 after the clump itself.
 */
#ifndef GAME_CLUMPDATA_H
#define GAME_CLUMPDATA_H

#include "rws/skinhelper.h"
#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "rw/bamatrix.h"
#include "rw/bastream.h"
#include "rw/rpatomic.h"
#include "rw/rphanim.h"

// A tagged matrix: its tag, a value read with it, and the matrix (0x50
// bytes; the list holds its count, padded to 0x10, then the entries).
struct type_EC1F0
{
    RwInt32 unk_00;
    RwInt32 unk_04;
    RwUInt8 unk_08[0x8];
    RwMatrixTag unk_10;
};
struct type_EBF40_04
{
    RwUInt32 unk_00;
    RwUInt8 unk_04[0xC];
    type_EC1F0 unk_10[1];
};

// The plugin's data in a clump (0x14 bytes at dword_4B92D0). Named for its
// accessor.
struct type_EC6C0
{
    bool unk_00;                // read with its data
    type_EBF40_04 *unk_04;      // the tagged matrices
    RwV3d *unk_08;              // a vector per hierarchy node
    RwInt32 unk_0C;             // the ints' count
    RwInt32 *unk_10;            // and the ints
};
extern RwInt32 dword_4B92D0;

// The plugin's registration (1) and its data in the clump arg_0.
RwInt32 sub_EBF10();
type_EC6C0 *sub_EC6C0(RpClump *arg_0);
// Reads a clump and its data from arg_0; *arg_4 (when given) says whether
// all four parts were there.
RpClump *sub_EBF40(RwStream *arg_0, RwInt32 *arg_4);
// The tagged matrix arg_4 of the clump arg_0, or 0.
type_EC1F0 *sub_EC1F0(RpClump *arg_0, RwInt32 arg_4);
// The clump's node vectors, ints' count and ints.
RwV3d *sub_EC270(RpClump *arg_0);
RwInt32 sub_EC290(RpClump *arg_0);
RwInt32 *sub_EC2B0(RpClump *arg_0);
// Sets the matrix arg_4 to the clump arg_0's tagged matrix arg_8 through its
// hierarchy (sub_EC310): with arg_C, a local-space hierarchy's node goes
// through the clump frame's modelling matrix rather than its LTM; arg_10 is
// unused.
struct RpClump;
RwInt32 sub_EC2D0(RpClump *arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C, RwInt32 arg_10);
RwInt32 sub_EC310(RpClump *arg_0, RpHAnimHierarchy *arg_4, RwMatrix *arg_8, RwInt32 arg_C, RwInt32 arg_10,
                  RwInt32 arg_14);
// The database's name for 0x2C37C0, a jump through the memory interface's
// free slot (dword_520218) that /OPT:ICF made several frees share;
// sub_79270 frees a hierarchy's interpolator through it.
extern "C" void _rpCollTreeDestroy(void *arg_0);
// The plugin's constructor, destructor and copy.
void *sub_EC570(void *arg_0, RwInt32 arg_4, RwInt32 arg_8);
void *sub_EC620(void *arg_0, RwInt32 arg_4, RwInt32 arg_8);
void *sub_EC5C0(void *arg_0, const void *arg_4, RwInt32 arg_8, RwInt32 arg_C);
// The clump arg_0's animation hierarchy; only the width is known.
RpHAnimHierarchy *sub_16D970(RpClump *arg_0);

#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

extern RwMatrix *RwMatrixStreamRead(RwStream * stream, RwMatrix * matrix);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

#endif
