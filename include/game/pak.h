/*
 * The pack file (unit_16C800): d:\COD.PAK, a 0x80-byte header whose last
 * word counts the directory's 16-byte entries (each a file's size, its
 * offset and the 64-bit FNV-1 hash of its upper-cased path), which
 * sub_16C940 reads before it points RenderWare's file interface at its own
 * functions. Files found in the pack open as the handles 0 to 4 (slot 0 is
 * never handed out), others fall through to the saved interface; a mode
 * with 'w' or a path starting "d:" always does.
 */
#ifndef GAME_PAK_H
#define GAME_PAK_H

#include <stddef.h>

#include "rw/ostypes.h"
#include "rw/osintf.h"

// A directory entry.
struct type_16CC10
{
    RwInt32 unk_00;             // its size
    RwInt32 unk_04;             // its offset in the pack
    RwUInt64 unk_08;            // its path's hash (sub_16C880)
};

// An open file in the pack.
struct type_4E22A8_80
{
    RwUInt8 unk_00;             // in use
    RwUInt8 unk_01;             // at its end
    RwUInt8 unk_02[0x2];
    type_16CC10 *unk_04;        // its entry
    RwInt32 unk_08;             // the position in it
};

// The pack's state (dword_4E22A8).
struct type_4E22A8
{
    RwUInt8 unk_00[0x7C];       // the header, read whole
    RwInt32 unk_7C;             // its directory's entries
    type_4E22A8_80 unk_80[5];   // the open files
    void *unk_BC;               // the pack, opened through unk_CC
    RwUInt8 unk_C0[0x4];
    type_16CC10 *unk_C4;        // the directory
    RwInt32 unk_C8;             // the pack's file position
    RwFileFunctions unk_CC;     // RenderWare's own file interface
    RwInt32 unk_F8;             // set up
};
typedef RwChar type_4E22A8_size_check[sizeof(type_4E22A8) == 0xFC ? 1 : -1];

// The start of the C library's file record, as sub_16D070 retries a seek
// while its unk_20 is 3; only that field is known.
struct type_16D070
{
    RwUInt8 unk_00[0x20];
    RwInt32 unk_20;
};

extern type_4E22A8 dword_4E22A8;
extern RwInt32 dword_4E23A8;    // text reads turn "\r\n" into "\n"

// The FNV-1 hash of the string arg_0 (upper-cased) from the basis arg_4.
RwUInt32 sub_16C800(const RwChar *arg_0, RwUInt32 arg_4);
// Likewise, 64-bit, with '/' read as '\\' and stopping at ';'.
RwUInt64 sub_16C880(const RwChar *arg_0, RwUInt64 arg_4);
// Opens the pack and hooks the file interface; false when it was already
// set up or the pack is missing.
bool sub_16C940();
// The pack's replacements for RenderWare's fopen, the entry lookup, and
// fclose, fread, fgets, fseek, feof and fexist.
void *sub_16CB00(const RwChar *arg_0, const RwChar *arg_4);
type_16CC10 *sub_16CC10(const RwChar *arg_0);
RwInt32 sub_16CCC0(void *arg_0);
size_t sub_16CD00(void *arg_0, size_t arg_4, size_t arg_8, void *arg_C);
RwChar *sub_16CE70(RwChar *arg_0, RwInt32 arg_4, void *arg_8);
RwInt32 sub_16D070(void *arg_0, RwFileSeekOffset arg_4, RwInt32 arg_8);
RwInt32 sub_16D1B0(void *arg_0);
RwBool sub_16D1E0(const RwChar *arg_0);
// The size of the pack file open as arg_0 (also in game/gameloop.h).
RwUInt32 sub_16D200(void *arg_0);

// Called by sub_16C940 before it opens the pack and after it hooks the
// file interface; only the widths are known.
RwInt32 sub_19CDE0(const RwChar *arg_0);
void sub_1A26F0();

#endif
