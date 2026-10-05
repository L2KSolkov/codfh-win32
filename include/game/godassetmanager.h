/*
 * The GodAsset manager (unit_198390), named from its own strings
 * ("GodAssetManager:: m_requestPool alloc %d", "m_freeGodAssetPools[%d]",
 * "m_fileInfoPool", "GodAssetStringPool"). Its state is file statics, each
 * with its own dynamic initializer and atexit destructor:
 *
 *   dword_4F26D0  the objects waiting to be read, a list of requests
 *   dword_4F26D4  a second table (0x12C nodes, 100 buckets)
 *   dword_4F2708  m_requestPool (9000 requests of 0x18 bytes; 50 in game)
 *   dword_4F2728  every object by key (types/type_3DF8D8.h)
 *   dword_4F275C  GodAssetStringPool (40 strings of 0x100 bytes)
 *   dword_4F277C  m_fileInfoPool (300 of 0xC bytes)
 *   dword_4F27A0  m_freeGodAssetPools[6], the objects' memory by size
 *                 (dword_42B6E4's counts and sizes)
 */
#ifndef GAME_GODASSETMANAGER_H
#define GAME_GODASSETMANAGER_H

#include "rw/ostypes.h"
#include "types/alfahash.h"
#include "types/alfasched.h"
#include "types/type_3DF8D8.h"

// A request (m_requestPool's 0x18 bytes): the object to read, the callback
// told once it is read (with unk_10 and unk_14; nonzero marks it wanted),
// and its links in the list at dword_4F26D0 (newest first).
struct type_4F26D0
{
    type_3DF8D8_base *unk_00;
    RwInt32 (*unk_04)(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8);
    type_4F26D0 *unk_08;        // the next
    type_4F26D0 *unk_0C;        // the previous
    RwInt32 unk_10;
    RwInt32 unk_14;

    // An accessor with no address and so no database name, named for its
    // field. Evidence: the stream reader (sub_198D30) marks the object
    // wanted through a temporary of its own each time.
    type_3DF8D8_base *get_unk_00()
    {
        type_3DF8D8_base *r = unk_00;
        return r;
    }
};
// A file-info record (m_fileInfoPool's 0xC bytes, in the table dword_4F26D4):
// a read object's file id (its header's unk_18), a value and a clump.
struct type_4F277C
{
    RwInt32 unk_00;
    RwInt32 unk_04;
    RwInt32 unk_08;
};
// m_freeGodAssetPools' element counts and sizes (the last pool's size is
// -1: the largest asset's, measured as the pools are set up).
struct type_42B6E4
{
    RwInt32 unk_00;
    RwInt32 unk_04;
};

extern alfahash dword_4F26D4;
extern type_16C2A0 dword_4F2708;
extern alfahash dword_4F2728;
extern type_16C2A0 dword_4F275C;
extern type_16C2A0 dword_4F277C;
extern type_16C2A0 dword_4F27A0[6];
extern type_42B6E4 dword_42B6E4[6];
extern RwUInt32 dword_4F25D8;       // when the manager was set up
extern RwUInt32 dword_4F25E0[0x3C];   // live objects by kind
extern RwUInt32 dword_4F24E8[0x3C];   // the most of each kind at once

// Frees every object's registration (sub_198580 walks the table with it).
bool sub_1986F0(void *arg_0);

#endif
