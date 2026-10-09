/*
 * type_141C10: the record the section streaming chunk (0x719) carries, named
 * after its reader sub_141C10 (unit_141BB0): 0x1C bytes read at the start of
 * each chunk, a kind (1 to 30) that picks the handler, and the size of what
 * the chunk holds with it (the rest is skipped). Only what the reader uses
 * is known; the handlers read the rest.
 */
#ifndef TYPE_141C10_H
#define TYPE_141C10_H

#include "rw/ostypes.h"
#include "rw/bamemory.h"
#include "rw/bastream.h"
#include "types/type_3DF8D8.h"
#include "rw/babintex.h"
#include "rw/rtdict.h"
#include "types/type_143DC0.h"

// A key with a word before it, at +0x0C: the reader's frame builds it (the
// key's inline constructor, through `this` temporaries) before the read.
struct type_141C10_0C
{
    RwInt32 unk_00;
    type_3DF8D8_04 unk_04;
};

struct type_141C10
{
    RwInt32 unk_00;             // the kind
    RwInt32 unk_04;
    RwInt32 unk_08;             // the size read with the record (0x1C for
                                // the record alone)
    type_141C10_0C unk_0C;
    RwInt32 unk_18;
};

// The chunk's handler (ChunkHandler) and its registration.
void sub_141BB0();
void sub_141BD0();
void ChunkHandler(RwChunkHeaderInfo &rChunkHeader, RwStream *pStream);
void sub_141C10(RwStream *arg_0, RwChunkHeaderInfo *arg_4);

// The handlers, by the record's kind; only the widths are known.
RwInt32 sub_142030(RwStream *arg_0, type_141C10 *arg_4);
RwInt32 sub_1421B0(RwStream *arg_0, type_141C10 *arg_4);
RwInt32 sub_142330(RwStream *arg_0, type_141C10 *arg_4);
RwInt32 sub_142490(RwStream *arg_0, type_141C10 *arg_4);
void sub_142620(RwStream *arg_0, type_141C10 *arg_4);
void sub_1427A0(RwStream *arg_0, type_141C10 *arg_4);
RwInt32 sub_142890(RwStream *arg_0, type_141C10 *arg_4);
void sub_142A30(RwStream *arg_0, type_141C10 *arg_4);
void sub_142A90(RwStream *arg_0, type_141C10 *arg_4);
void sub_142AF0(RwStream *arg_0, type_141C10 *arg_4);
void sub_142B70(RwStream *arg_0, type_141C10 *arg_4);
void sub_142BC0(RwStream *arg_0, type_141C10 *arg_4);
void sub_142BE0(RwStream *arg_0, type_141C10 *arg_4);
void sub_142C30(RwStream *arg_0, type_141C10 *arg_4);
void sub_142C60(RwStream *arg_0, type_141C10 *arg_4);
void sub_142CA0(RwStream *arg_0, type_141C10 *arg_4);
void sub_142CE0(RwStream *arg_0, type_141C10 *arg_4);
void sub_142D20(RwStream *arg_0, type_141C10 *arg_4);
void sub_142D70(RwStream *arg_0, type_141C10 *arg_4);
RwInt32 sub_142F70(RwStream *arg_0, type_141C10 *arg_4);
void sub_143230(RwStream *arg_0, type_141C10 *arg_4);
void sub_143360(RwStream *arg_0, type_141C10 *arg_4);
void sub_143480(RwStream *arg_0, type_141C10 *arg_4);
void sub_1435A0(RwStream *arg_0, type_141C10 *arg_4);
void sub_1436C0(RwStream *arg_0, type_141C10 *arg_4);
void sub_1437E0(RwStream *arg_0, type_141C10 *arg_4);
void sub_143900(RwStream *arg_0, type_141C10 *arg_4);
void sub_143AF0(RwStream *arg_0, type_141C10 *arg_4);
void sub_143B90(RwStream *arg_0, type_141C10 *arg_4);
// The section loaders' helpers: the section's record, its streaming state
// and the world it gets; only the widths are known.
struct type_173F50;
struct RpWorld;
RwTexDictionary *sub_1743E0(RwInt32 arg_0);
RwBool sub_143C30(RwTexDictionary *arg_0);
#ifdef CODFH_SP
// Returns nothing in single player (SP 0xEE86B pops the argument into ecx).
void sub_143C60();
#else
RwBool sub_143C60();
#endif
void sub_142A10();
// RenderWare's memory interface (its first function, the allocator) as
// sub_142A10 checks it: when it is sub_2DA220, sub_2DA340 runs. Only the
// widths are known.
struct type_2A9830
{
    RwInt32 (*unk_00)(RwInt32 arg_0);
};
// (RwOsGetMemoryInterface returns RenderWare's RwMemoryFunctions, rw/bamemory.h.)
// The same through a result local: an inline with no address and so no
// database name. Evidence: the model object's handler (sub_190640) stores
// the interface into a temporary allocated after its block's locals and
// never reads it.
inline type_2A9830 *get_2A9830()
{
    type_2A9830 *r = (type_2A9830 *)RwOsGetMemoryInterface();
    return r;
}
extern "C" RwInt32 sub_2DA220(RwInt32 arg_0);
extern "C" void sub_2DA340();
// Reads RenderWare's allocations into the arena arg_0 from now on (0 for
// the engine's own functions again).
extern "C" void sub_2DAAF0(RwInt32 arg_0);
// The shared texture dictionary kinds 6, 16 and sub_142AF0 read their worlds
// with, and what takes each world.
#ifdef CODFH_PLAIN
extern RwTexDictionary *&dword_4E5C8C;
#else
extern RwTexDictionary *dword_4E5C8C;
#endif
void sub_174460(RpWorld *arg_0);
void sub_174470(RpWorld *arg_0);
void sub_174480(RpWorld *arg_0);
RwInt32 sub_173CE0(RpWorld *arg_0, RwInt32 arg_4, RwUInt16 arg_8);
// RenderWare's RpWorldStreamRead, which the section loaders call with a
// second argument (the section record's +0x10).
extern "C" RpWorld *RpWorldStreamRead(RwStream *stream, void *arg_4);
// What takes the section's texture dictionary (RwTexDictionaryStreamRead,
// with its second argument, is in rw/babintex.h).
RwInt32 sub_1742D0(RwTexDictionary *arg_0, RwUInt16 arg_4);
// The UV animation dictionary the XBSP loader makes current (the
// database's name).
extern RtDict *schema;
// The global texture dictionary's arena (kind 5): where it goes (dword_4E5CAC)
// and how much of it (dword_4E5CB4) when sections are not set up
// (SectionInfo::sub_B0140), and what it took, rounded up to 128 bytes.
struct type_4E5BD0
{
    RwInt32 unk_00;
    RwInt32 unk_04;
    RwInt32 unk_08;
};
extern type_4E5BD0 dword_4E5BD0;
#ifdef CODFH_PLAIN
extern RwInt32 &dword_4E5CAC;
#else
extern RwInt32 dword_4E5CAC;
#endif
extern RwInt32 dword_4E5CB4;
// The global texture dictionary and what takes it.
extern RwTexDictionary *dword_4CFA10;
void sub_174510(RwTexDictionary *arg_0);
// Adds the entry to the dictionary data (kind 17's walk).
RtDictEntryType callBack(RtDictEntryType entry, void *data);

// Kind 7's dictionary reader and what takes the dictionary; kinds 8 and 9's
// reader. Only the widths are known.
RwTexDictionary *sub_144740(RwStream *arg_0, RwInt32 arg_4);
void sub_174490(RwTexDictionary *arg_0);
struct type_3DF8D8_ev;
void sub_198C70(RwStream *arg_0, type_3DF8D8_ev *arg_4);

// The kind-18 sub-chunk's objects: the animated textures (types/type_143DC0.h).

// The empty debug print again, with a section record and a flag.
void sub_19A750(type_173F50 *arg_0, RwInt32 arg_4);

// Kind 19's other loaders (its sub-chunks 6 and 13); only the widths are
// known. Its sub-chunk 14 goes to another empty function folded into the
// debug print.
RwInt32 sub_172820();
// Sub-chunks 7 and 15 (game/clones.h declares them too, but brings in
// xtl.h, which asynchload.h's critical sections clash with).
void sub_123280(RwStream *arg_0, RwUInt32 arg_4);
void sub_123440(RwStream *arg_0);
void sub_172BB0();
void sub_19A750(RwStream *arg_0);

// Kinds 20 to 25 make objects by key through the sound bank's object
// functions (types/soundbank.h), here with the record's key; and read each
// through a method of its class, known only as these views.
struct type_199010;
struct type_3DF8D8_04;
type_199010 *sub_198710(type_3DF8D8_04 *arg_0);
RwInt32 sub_198770(type_3DF8D8_04 *arg_0);
type_199010 *sub_199010(type_3DF8D8_04 *arg_0, RwInt32 arg_4);
struct type_3DF8D8_base;
RwInt32 sub_198FE0(type_3DF8D8_base *arg_0);
struct type_143230
{
    virtual void vf_000(RwStream *arg_0, type_141C10 *arg_4);
};
struct type_1947F0
{
    void sub_1947F0(RwStream *arg_0, type_141C10 *arg_4);
};
struct type_193A00
{
    void sub_193A00(RwStream *arg_0, type_141C10 *arg_4);
};
struct type_192870
{
    void sub_192870(RwStream *arg_0, type_141C10 *arg_4);
};

// The texture find callback while a BSP is read: the one it replaced, and
// the dictionaries it looks in (the global one from sub_174520, and the
// section's).
extern RwTextureCallBackFind dword_4CFA04;
extern RwTexDictionary *dword_4CFA08[2];
RwTexDictionary *sub_174520();
RwTexture *sub_143C80(const RwChar *arg_0);
// The level's directory name (kind 27): kept in dword_4E5CC4 (types/
// asynchload.h).

// Kinds 14, 15 and 30 go to empty handlers, which /OPT:ICF folded into the
// empty debug print (sub_19A750).
void sub_19A750(RwStream *arg_0, type_141C10 *arg_4);

#endif
