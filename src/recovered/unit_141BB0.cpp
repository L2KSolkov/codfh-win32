// The level sections' streaming: the chunk 0x719 and its records (opaque,
// alpha and collision BSPs, texture dictionaries, map data and banks).

#include "rw/ostypes.h"
#include "rw/bastream.h"
#include "rws/streamhandler.h"
#include "game/functions.h"
#include "rws/memoryhandler.h"
#include "types/type_4B8EF0.h"
#include "types/type_141C10.h"
#include "types/asynchload.h"
#include "game/gameloop.h"
#include "rw/babintex.h"
#include "rw/batextur.h"
#include "types/SectionInfo.h"
#include "game/particles.h"
#include "game/pathnodes.h"
#include "types/vec4.h"
#include "types/animbank.h"
#include <stdio.h>
#include <ctype.h>
#include "types/musicplayer.h"
#include "types/soundbank.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003DB3C4
extern const RwReal flt_3DB3C4 = 16.666666f;
// 0x004CFA04
RwTextureCallBackFind dword_4CFA04;
// 0x004CFA08
RwTexDictionary *dword_4CFA08[2];
// 0x004CFA10
RwTexDictionary *dword_4CFA10;
// End of its data definitions.


// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3DB3C4@@3MB @ 0x003DB3C4
// match: ??_C@_0EP@PBPKJMIA@Warning?3?5not?5able?5to?5find?5world?5@ @ 0x003DB3C8
// match: ??_C@_0EG@IONGLNBF@Warning?3?5Loading?5opaque?5BSP?5for?5@ @ 0x003DB418
// match: ??_C@_0EH@PMNAAEAD@?$CK?$CK?$CKERROR?3?5no?5section?5bank?5availa@ @ 0x003DB460
// match: ??_C@_0EO@MAAOAOCK@Warning?3?5not?5able?5to?5find?5world?5@ @ 0x003DB4A8
// match: ??_C@_0EF@FBBDDMEE@Warning?3?5Loading?5Alpha?5BSP?5for?5s@ @ 0x003DB4F8
// match: ??_C@_0EG@EFCGHKNP@?$CK?$CK?$CKERROR?3?5no?5section?5bank?5availa@ @ 0x003DB540
// match: ??_C@_0EO@MKINJCPH@Warning?3?5not?5able?5to?5find?5TXD?5ch@ @ 0x003DB588
// match: ??_C@_0DP@FMKHJFJB@Warning?3?5Loading?5TXD?5for?5section@ @ 0x003DB5D8
// match: ??_C@_0EJ@BADPOJHP@Warning?3?5not?5able?5to?5find?5world?5@ @ 0x003DB618
// match: ??_C@_0EA@PFBHKCMN@Warning?3?5Loading?5XBSP?5for?5sectio@ @ 0x003DB668
// match: ??_C@_0EB@CGMMLFGH@?$CK?$CK?$CKERROR?3?5no?5section?5bank?5availa@ @ 0x003DB6A8
// match: ??_C@_0FC@KIOIBLJB@Warning?3?5not?5able?5to?5find?5world?5@ @ 0x003DB6F0
// match: ??_C@_0EI@KAKFOMKO@Warning?3?5Loading?5Collsion?5BSP?5fo@ @ 0x003DB748
// match: ??_C@_0EK@JCPKCBLC@?$CK?$CK?$CKERROR?3?5no?5section?5bank?5availa@ @ 0x003DB790
// match: ??_C@_0CD@NFADJGLM@Received?5abort?5of?5section?5load?4?4@ @ 0x003DB7DC
// match: ??_C@_0CP@LBAKOPMN@NO?5level?5directory?5name?5received@ @ 0x003DB800
// match: ??_C@_0BP@HPDJHHMF@COD_MapData?$CLSceneData?$CLFilename?$AA@ @ 0x003DB830
// match: ??_C@_0CG@MANNFAMF@COD_MapData?$CLSceneDataL_?$CFd_?$CFd?$CLFil@ @ 0x003DB850
// match: ??_C@_0CG@ECGMMBOO@COD_MapData?$CLSceneData_shared?$CLFil@ @ 0x003DB878
// match: ??_C@_0CC@LJGBIKLK@COD_MapData?$CLHitDeathData?$CLFilenam@ @ 0x003DB8A0
// match: ??_C@_0CE@OFDNBCOL@COD_MapData?$CLHitDeathData?$CFs?$CLFilen@ @ 0x003DB8C4
// match: ??_C@_0BE@DJBDBCPF@AnimDataSet?5Request?$AA@ @ 0x003DB8E8
// match: __ehhandler$?sub_142D70@@YAXPAURwStream@@PAUtype_141C10@@@Z>1>8 @ 0x0041DBC4
// match: __ehhandler$?sub_142D70@@YAXPAURwStream@@PAUtype_141C10@@@Z>1 @ 0x0041DBCC

// match: sub_141BB0 @ 0x00141BB0
// sp-match: sub_141BB0 @ 0x000EE180

void sub_141BB0()
{
    RWS::CStreamHandler::RegisterChunkHandler(0x719, ChunkHandler); // not an address: a chunk id
}

// match: sub_141BD0 @ 0x00141BD0
// sp-match: sub_141BD0 @ 0x000EDDD0
void sub_141BD0()
{
    RWS::CStreamHandler::UnRegisterChunkHandler(0x719); // not an address: a chunk id
}

// match: ?ChunkHandler@@YAXAAURwChunkHeaderInfo@@PAURwStream@@@Z @ 0x00141BF0
// sp-match: ?ChunkHandler@@YAXAAURwChunkHeaderInfo@@PAURwStream@@@Z @ 0x000EE160
void ChunkHandler(RwChunkHeaderInfo &rChunkHeader, RwStream *pStream)
{
    sub_141C10(pStream, &rChunkHeader);
}

// match: sub_141C10 @ 0x00141C10
// sp-match: sub_141C10 @ 0x000EDDE0
// Reads the chunk's record and hands it to the handler for its kind (the
// loading bar advanced to a stage for some), then skips what the handler
// left of the chunk.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
#ifdef CODFH_SP
// Single player's empty handlers for kinds 15 and 30: separate functions (sub_141C10 calls each
// on its own), all folded with kind 14's into the empty function by /OPT:ICF.
void sub_141C10_kind15(RwStream *arg_0, type_141C10 *arg_4);
void sub_141C10_kind30(RwStream *arg_0, type_141C10 *arg_4);
#endif
void sub_141C10(RwStream *arg_0, RwChunkHeaderInfo *arg_4)
{
    RwInt32 var_4;
    type_141C10 local_20;

    RwStreamRead(arg_0, &local_20, sizeof(local_20));
    switch (local_20.unk_00)
    {
    case 19:
        if (local_20.unk_08 - sizeof(local_20))
            sub_142F70(arg_0, &local_20);
        break;
    case 18:
        sub_142490(arg_0, &local_20);
        break;
    case 1:
        sub_142030(arg_0, &local_20);
        break;
    case 2:
        sub_1421B0(arg_0, &local_20);
        break;
    case 3:
        sub_142890(arg_0, &local_20);
        break;
    case 4:
        sub_142330(arg_0, &local_20);
        break;
    case 5:
        sub_142620(arg_0, &local_20);
        break;
    case 17:
        sub_12F0A0();
        sub_1427A0(arg_0, &local_20);
        break;
    case 6:
        sub_12F0A0();
        sub_142A30(arg_0, &local_20);
        break;
    case 16:
        sub_12F0A0();
        sub_142A90(arg_0, &local_20);
        break;
    case 7:
        sub_12F0A0();
        sub_142B70(arg_0, &local_20);
        break;
    case 8:
        sub_12F0A0();
        sub_142BC0(arg_0, &local_20);
        break;
    case 9:
        sub_12F0A0();
        sub_142BC0(arg_0, &local_20);
        break;
    case 11:
        sub_12F0A0();
        sub_142BE0(arg_0, &local_20);
        dword_4B8EF0.sub_E9FB0(11);
        break;
    case 26:
        sub_12F0A0();
        sub_142C30(arg_0, &local_20);
        dword_4B8EF0.sub_E9FB0(12);
        break;
    case 12:
        sub_12F0A0();
        sub_142C60(arg_0, &local_20);
        dword_4B8EF0.sub_E9FB0(13);
        break;
    case 13:
        sub_12F0A0();
        sub_142CA0(arg_0, &local_20);
        dword_4B8EF0.sub_E9FB0(14);
        break;
    case 10:
        sub_12F0A0();
        sub_142CE0(arg_0, &local_20);
        break;
    case 14:
        sub_19A750(arg_0, &local_20);
        break;
    case 15:
        sub_12F0A0();
#ifdef CODFH_SP // single player's kind-15 handler is its own empty function (not tail-merged with kind 14's call, SP 0xEDDE0)
        sub_141C10_kind15(arg_0, &local_20);
#else
        sub_19A750(arg_0, &local_20);
#endif
        break;
    case 20:
        sub_143230(arg_0, &local_20);
        dword_4B8EF0.sub_E9FB0(15);
        break;
    case 21:
        sub_143360(arg_0, &local_20);
        dword_4B8EF0.sub_E9FB0(16);
        break;
    case 22:
        sub_143480(arg_0, &local_20);
        dword_4B8EF0.sub_E9FB0(17);
        break;
    case 23:
        sub_1435A0(arg_0, &local_20);
        dword_4B8EF0.sub_E9FB0(18);
        break;
    case 24:
        sub_1436C0(arg_0, &local_20);
        dword_4B8EF0.sub_E9FB0(19);
        break;
    case 25:
        sub_1437E0(arg_0, &local_20);
        dword_4B8EF0.sub_E9FB0(20);
        break;
    case 27:
        sub_143900(arg_0, &local_20);
        break;
    case 28:
        sub_143AF0(arg_0, &local_20);
        break;
    case 29:
        sub_143B90(arg_0, &local_20);
        break;
    case 30:
#ifdef CODFH_SP // likewise kind 30's (SP 0xEDDE0)
        sub_141C10_kind30(arg_0, &local_20);
#else
        sub_19A750(arg_0, &local_20);
#endif
        break;
    }
    var_4 = arg_4->length - local_20.unk_08;
    if (var_4 > 0)
        RwStreamSkip(arg_0, var_4);
}

// match: sub_142030 @ 0x00142030
// sp-match: sub_142030 @ 0x000EEF60
// Kind 1: the opaque BSP of the section arg_4->unk_04, read into its record
// when it is the section being loaded (or any is); the world is handed on
// (sub_173CE0), or the record dropped when it cannot be read. Returns what
// sub_173CE0 gave, or -1.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_142030(RwStream *arg_0, type_141C10 *arg_4)
{
    RwUInt32 var_4;
    RwInt32 v8;
    type_173F50 *stk_C;
    RpWorld *var_10;

    v8 = -1;
    if (RwStreamFindChunk(arg_0, rwID_WORLD, &var_4, 0))
    {
        if (arg_4->unk_04 == (RwUInt16)word_429EAC || (RwUInt16)word_429EAC == 0xFFFF)
        {
            stk_C = (type_173F50 *)sub_173F50((RwUInt16)arg_4->unk_04);
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS) // single player compiles the debug print out (SP 0xEEF60)
            if (!stk_C)
                sub_19A750("***ERROR: no section bank available to load Opaque BSP for section %d\n",
                           arg_4->unk_04);
#endif
            RwTexDictionarySetCurrent(0);
            stk_C->set_unk_08((RwInt16)arg_4->unk_04);
            sub_19A750(stk_C, 0);
            sub_143C30(sub_1743E0(arg_4->unk_04));
            var_10 = RpWorldStreamRead(arg_0, stk_C->unk_10);
            sub_143C60();
            sub_142A10();
            if (var_10)
            {
                v8 = sub_173CE0(var_10, 0, (RwUInt16)arg_4->unk_04);
                sub_19A750(stk_C, 0);
            }
            else
            {
                sub_19A750(stk_C, 0);
                sub_174060((type_4E5D30 *)stk_C, 1);
            }
        }
        else
        {
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS) // single player compiles the debug print out (SP 0xEEF60)
            sub_19A750("Warning: Loading opaque BSP for section %d but section to load is %d\n", arg_4->unk_04,
                       (RwUInt16)word_429EAC);
#endif
            RwStreamSkip(arg_0, arg_4->unk_08);
        }
    }
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS) // single player compiles the debug print out (SP 0xEEF60)
    else
    {
        sub_19A750("Warning: not able to find world chunk for Opaque BSP while loading section %d\n",
                   arg_4->unk_04);
    }
#endif
    return v8;
}

// match: sub_1421B0 @ 0x001421B0
// sp-match: sub_1421B0 @ 0x000EF030
// Kind 2: the alpha BSP (as sub_142030, with 1 for 0: the second world) of the section arg_4->unk_04, read into its record
// when it is the section being loaded (or any is); the world is handed on
// (sub_173CE0), or the record dropped when it cannot be read. Returns what
// sub_173CE0 gave, or -1.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_1421B0(RwStream *arg_0, type_141C10 *arg_4)
{
    RwUInt32 var_4;
    RwInt32 v8;
    type_173F50 *stk_C;
    RpWorld *var_10;

    v8 = -1;
    if (RwStreamFindChunk(arg_0, rwID_WORLD, &var_4, 0))
    {
        if (arg_4->unk_04 == (RwUInt16)word_429EAC || (RwUInt16)word_429EAC == 0xFFFF)
        {
            stk_C = (type_173F50 *)sub_173F50((RwUInt16)arg_4->unk_04);
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS) // single player compiles the debug print out (SP 0xEF030)
            if (!stk_C)
                sub_19A750("***ERROR: no section bank available to load Alpha BSP for section %d\n",
                           arg_4->unk_04);
#endif
            RwTexDictionarySetCurrent(0);
            stk_C->set_unk_08((RwInt16)arg_4->unk_04);
            sub_19A750(stk_C, 1);
            sub_143C30(sub_1743E0(arg_4->unk_04));
            var_10 = RpWorldStreamRead(arg_0, stk_C->unk_10);
            sub_143C60();
            sub_142A10();
            if (var_10)
            {
                v8 = sub_173CE0(var_10, 1, (RwUInt16)arg_4->unk_04);
                sub_19A750(stk_C, 1);
            }
            else
            {
                sub_19A750(stk_C, 1);
                sub_174060((type_4E5D30 *)stk_C, 1);
            }
        }
        else
        {
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS) // single player compiles the debug print out (SP 0xEF030)
            sub_19A750("Warning: Loading Alpha BSP for section %d but section to load is %d\n", arg_4->unk_04,
                       (RwUInt16)word_429EAC);
#endif
            RwStreamSkip(arg_0, arg_4->unk_08);
        }
    }
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS) // single player compiles the debug print out (SP 0xEF030)
    else
    {
        sub_19A750("Warning: not able to find world chunk for Alpha BSP while loading section %d\n",
                   arg_4->unk_04);
    }
#endif
    return v8;
}

// match: sub_142330 @ 0x00142330
// sp-match: sub_142330 @ 0x000EE8B0
// Kind 4: the section's texture dictionary (its error message is the alpha
// BSP's). Returns 1 when it was read, else -1.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_142330(RwStream *arg_0, type_141C10 *arg_4)
{
    RwUInt32 var_4;
    RwInt32 v8;
    RwTexDictionary *stk_C;
    type_173F50 *var_10;

    v8 = -1;
    if (RwStreamFindChunk(arg_0, rwID_TEXDICTIONARY, &var_4, 0))
    {
        if (arg_4->unk_04 == (RwUInt16)word_429EAC || (RwUInt16)word_429EAC == 0xFFFF)
        {
            var_10 = (type_173F50 *)sub_173F50((RwUInt16)arg_4->unk_04);
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS) // single player compiles the debug print out (SP 0xEE8B0)
            if (!var_10)
                sub_19A750("***ERROR: no section bank available to load Alpha BSP for section %d\n",
                           arg_4->unk_04);
#endif
            var_10->set_unk_08((RwInt16)arg_4->unk_04);
            sub_19A750(var_10, 3);
            stk_C = RwTexDictionaryStreamRead(arg_0, var_10->unk_10);
            sub_142A10();
            if (stk_C)
            {
                v8 = 1;
                sub_1742D0(stk_C, (RwUInt16)arg_4->unk_04);
                sub_19A750(var_10, 3);
            }
            else
            {
                sub_19A750(var_10, 3);
                sub_174060((type_4E5D30 *)var_10, 1);
            }
        }
        else
        {
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS) // single player compiles the debug print out (SP 0xEE8B0)
            sub_19A750("Warning: Loading TXD for section %d but section to load is %d\n", arg_4->unk_04,
                       (RwUInt16)word_429EAC);
#endif
            RwStreamSkip(arg_0, arg_4->unk_08);
        }
    }
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS) // single player compiles the debug print out (SP 0xEE8B0)
    else
    {
        sub_19A750("Warning: not able to find TXD chunk for section TXD while loading section %d\n",
                   arg_4->unk_04);
    }
#endif
    return v8;
}

// match: sub_142490 @ 0x00142490
// sp-match: sub_142490 @ 0x000EF100
// Kind 18: the XBSP (the world with animated UVs, stage 4), as sub_142030
// with the UV animation dictionary made current first. Its last warning
// has no `else` before it: it is logged after every load.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_142490(RwStream *arg_0, type_141C10 *arg_4)
{
    RwUInt32 var_4;
    RwInt32 v8;
    type_173F50 *stk_C;
    RpWorld *var_10;

    v8 = -1;
    if (RwStreamFindChunk(arg_0, rwID_WORLD, &var_4, 0))
    {
        if (arg_4->unk_04 == (RwUInt16)word_429EAC || (RwUInt16)word_429EAC == 0xFFFF)
        {
            stk_C = (type_173F50 *)sub_173F50((RwUInt16)arg_4->unk_04);
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS) // single player compiles the debug print out (SP 0xEF100)
            if (!stk_C)
                sub_19A750("***ERROR: no section bank available to load XBSP for section %d\n",
                           arg_4->unk_04);
#endif
            RwTexDictionarySetCurrent(0);
            RtDictSchemaSetCurrentDict(&_rpUVAnimDictSchema, schema);
            stk_C->set_unk_08((RwInt16)arg_4->unk_04);
            sub_19A750(stk_C, 4);
            sub_143C30(sub_1743E0(arg_4->unk_04));
            var_10 = RpWorldStreamRead(arg_0, stk_C->unk_10);
            sub_143C60();
            sub_142A10();
            if (var_10)
            {
                v8 = sub_173CE0(var_10, 4, (RwUInt16)arg_4->unk_04);
                sub_19A750(stk_C, 4);
            }
            else
            {
                sub_19A750(stk_C, 4);
                sub_174060((type_4E5D30 *)stk_C, 1);
            }
        }
        else
        {
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS) // single player compiles the debug print out (SP 0xEF100)
            sub_19A750("Warning: Loading XBSP for section %d but section to load is %d\n", arg_4->unk_04,
                       (RwUInt16)word_429EAC);
#endif
            RwStreamSkip(arg_0, arg_4->unk_08);
        }
    }
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS) // single player compiles the debug print out (SP 0xEF100)
    sub_19A750("Warning: not able to find world chunk for XBSP while loading section %d\n", arg_4->unk_04);
#endif
    return v8;
}

// match: sub_142620 @ 0x00142620
// sp-match: sub_142620 @ 0x000EE970
// Kind 5: the level's global texture dictionary (dword_4CFA10), read into
// the arena dword_4E5BD0 unless sections are set up; its size is kept
// rounded up to 128 bytes. What a failed read leaves is skipped.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_142620(RwStream *arg_0, type_141C10 *arg_4)
{
    type_4E5BD0 *var_4;
    RwInt32 v8;
    RwInt32 stk_C;
    RwInt32 var_10;

    if (arg_4->unk_08 == sizeof(type_141C10))
        return;
    var_4 = &dword_4E5BD0;
    var_4->unk_00 = 0;
    var_4->unk_04 = 0;
    var_4->unk_08 = 0;
    if (RwStreamFindChunk(arg_0, rwID_TEXDICTIONARY, 0, 0))
    {
        v8 = arg_0->position;
        if (!SectionInfo::sub_B0140())
        {
            var_4->unk_00 = dword_4E5CAC;
            var_4->unk_08 = dword_4E5CB4;
            dword_4CFA10 = RwTexDictionaryStreamRead(arg_0, var_4);
            sub_142A10();
        }
        else
        {
            dword_4CFA10 = RwTexDictionaryStreamRead(arg_0, 0);
        }
        if (dword_4CFA10)
        {
            sub_174510(dword_4CFA10);
            if (!SectionInfo::sub_B0140())
            {
                stk_C = 0x80;
                if ((stk_C - 1) & var_4->unk_04)
                    var_4->unk_04 = stk_C - ((stk_C - 1) & var_4->unk_04) + var_4->unk_04;
                var_4->unk_08 = var_4->unk_04;
            }
        }
        else
        {
            var_4->unk_00 = 0;
            var_4->unk_04 = 0;
            var_4->unk_08 = 0;
            var_10 = arg_4->unk_08 - 0x28 - (arg_0->position - v8);
            if (var_10 > 0)
                RwStreamSkip(arg_0, var_10);
        }
        SectionInfo::sub_B0140();
    }
    else
    {
        RwStreamSkip(arg_0, arg_4->unk_08);
    }
}

// match: sub_1427A0 @ 0x001427A0
// sp-match: sub_1427A0 @ 0x000EEA90
// Kind 17: a UV animation dictionary, whose entries are added to the
// current one (schema) before it is destroyed.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_1427A0(RwStream *arg_0, type_141C10 *arg_4)
{
    RtDict *var_4;
    RtDict *v8;
    RwInt32 varC;

    if (arg_4->unk_08 != sizeof(type_141C10) && arg_0)
    {
        if (RwStreamFindChunk(arg_0, rwID_UVANIMDICT, 0, 0))
        {
            var_4 = RtDictSchemaStreamReadDict(&_rpUVAnimDictSchema, arg_0);
            if (var_4)
            {
                v8 = schema;
                if (v8)
                    RtDictForAllEntries(var_4, callBack, v8);
                RtDictDestroy(var_4);
            }
            else
            {
                varC = arg_4->unk_08 - sizeof(type_141C10);
                if (varC > 0)
                    RwStreamSkip(arg_0, varC);
            }
        }
        else
        {
            RwStreamSkip(arg_0, arg_4->unk_08);
        }
    }
}

// match: ?callBack@@YAPAXPAX0@Z @ 0x00142860
// sp-match: ?callBack@@YAPAXPAX0@Z @ 0x000EE1A0
RtDictEntryType callBack(RtDictEntryType entry, void *data)
{
    RtDict *var_4;

    var_4 = (RtDict *)data;
    RtDictAddEntry(var_4, entry);
    return entry;
}

// match: sub_142890 @ 0x00142890
// sp-match: sub_142890 @ 0x000EF1E0
// Kind 3: the collision BSP, as sub_142030 with 2 (the collision world).
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_142890(RwStream *arg_0, type_141C10 *arg_4)
{
    RwUInt32 var_4;
    RwInt32 v8;
    type_173F50 *stk_C;
    RpWorld *var_10;

    v8 = -1;
    if (RwStreamFindChunk(arg_0, rwID_WORLD, &var_4, 0))
    {
        if (arg_4->unk_04 == (RwUInt16)word_429EAC || (RwUInt16)word_429EAC == 0xFFFF)
        {
            stk_C = (type_173F50 *)sub_173F50((RwUInt16)arg_4->unk_04);
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS) // single player compiles the debug print out (SP 0xEF1E0)
            if (!stk_C)
                sub_19A750("***ERROR: no section bank available to load Collision BSP for section %d\n",
                           arg_4->unk_04);
#endif
            RwTexDictionarySetCurrent(0);
            stk_C->set_unk_08((RwInt16)arg_4->unk_04);
            sub_19A750(stk_C, 2);
            sub_143C30(sub_1743E0(arg_4->unk_04));
            var_10 = RpWorldStreamRead(arg_0, stk_C->unk_10);
            sub_143C60();
            sub_142A10();
            if (var_10)
            {
                v8 = sub_173CE0(var_10, 2, (RwUInt16)arg_4->unk_04);
                sub_19A750(stk_C, 2);
            }
            else
            {
                sub_19A750(stk_C, 2);
                sub_174060((type_4E5D30 *)stk_C, 1);
            }
        }
        else
        {
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS) // single player compiles the debug print out (SP 0xEF1E0)
            sub_19A750("Warning: Loading Collsion BSP for section %d but section to load is %d\n", arg_4->unk_04,
                       (RwUInt16)word_429EAC);
#endif
            RwStreamSkip(arg_0, arg_4->unk_08);
        }
    }
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS) // single player compiles the debug print out (SP 0xEF1E0)
    else
    {
        sub_19A750("Warning: not able to find world chunk for collision BSP while loading section %d\n",
                   arg_4->unk_04);
    }
#endif
    return v8;
}

// match: sub_142A10 @ 0x00142A10
// sp-match: sub_142A10 @ 0x000EE1C0
void sub_142A10()
{
    type_2A9830 *var_4;

    var_4 = (type_2A9830 *)RwOsGetMemoryInterface();
    if (var_4->unk_00 == sub_2DA220)
        sub_2DA340();
}

// match: sub_142A30 @ 0x00142A30
// sp-match: sub_142A30 @ 0x000EE1E0
// Kind 6: a world read with the shared texture dictionary (sub_174460 takes
// it).
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_142A30(RwStream *arg_0, type_141C10 *arg_4)
{
    RwTexDictionary *var_4;
    RpWorld *local_8;

    if (RwStreamFindChunk(arg_0, rwID_WORLD, 0, 0))
    {
        var_4 = dword_4E5C8C;
        if (var_4)
            RwTexDictionarySetCurrent(var_4);
        local_8 = RpWorldStreamRead(arg_0, 0);
        if (local_8)
            sub_174460(local_8);
    }
}

// match: sub_142A90 @ 0x00142A90
// sp-match: sub_142A90 @ 0x000EE230
// Kind 16: likewise for sub_174470.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_142A90(RwStream *arg_0, type_141C10 *arg_4)
{
    RwTexDictionary *var_4;
    RpWorld *local_8;

    if (RwStreamFindChunk(arg_0, rwID_WORLD, 0, 0))
    {
        var_4 = dword_4E5C8C;
        if (var_4)
            RwTexDictionarySetCurrent(var_4);
        local_8 = RpWorldStreamRead(arg_0, 0);
        if (local_8)
            sub_174470(local_8);
    }
}

// match: sub_142AF0 @ 0x00142AF0
// sp-match: sub_142AF0 @ 0x000EE280
// Likewise for sub_174480, with the UV animation dictionary made current
// (no kind reaches it).
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_142AF0(RwStream *arg_0, type_141C10 *arg_4)
{
    RwTexDictionary *var_4;
    RpWorld *local_8;

    if (RwStreamFindChunk(arg_0, rwID_WORLD, 0, 0))
    {
        var_4 = dword_4E5C8C;
        if (var_4)
            RwTexDictionarySetCurrent(var_4);
        RtDictSchemaSetCurrentDict(&_rpUVAnimDictSchema, schema);
        local_8 = RpWorldStreamRead(arg_0, 0);
        if (local_8)
            sub_174480(local_8);
    }
}

// match: sub_142B70 @ 0x00142B70
// sp-match: sub_142B70 @ 0x000EE2E0
// Kind 7: a texture dictionary read by sub_144740 and handed to sub_174490.
void sub_142B70(RwStream *arg_0, type_141C10 *arg_4)
{
    RwTexDictionary *var_4;

    if (RwStreamFindChunk(arg_0, rwID_TEXDICTIONARY, 0, 0))
    {
        var_4 = sub_144740(arg_0, 1);
        if (var_4)
            sub_174490(var_4);
    }
}

// match: sub_142BC0 @ 0x00142BC0
// sp-match: sub_142BC0 @ 0x000EE320
// Kinds 8 and 9.
void sub_142BC0(RwStream *arg_0, type_141C10 *arg_4)
{
    sub_198C70(arg_0, (type_3DF8D8_ev *)arg_4);
}

// match: sub_142BE0 @ 0x00142BE0
// sp-match: sub_142BE0 @ 0x000EE330
// Kind 11: the particle definitions file (the rest of the chunk), read into
// a buffer of its own and handed to sub_F2B00.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_142BE0(RwStream *arg_0, type_141C10 *arg_4)
{
    RwInt32 var_4;
    type_4BFD28 *local_8;

    var_4 = arg_4->unk_08 - sizeof(type_141C10);
    if (var_4 > 0)
    {
        local_8 = (type_4BFD28 *)RWSMalloc(var_4, 0x34250); // not an address: a memory hint
        RwStreamRead(arg_0, local_8, var_4);
        sub_F2B00(local_8);
    }
}

// match: sub_142C30 @ 0x00142C30
// sp-match: sub_142C30 @ 0x000EE370
// Kind 26: the particle meshes.
void sub_142C30(RwStream *arg_0, type_141C10 *arg_4)
{
    RwInt32 var_4;

    var_4 = arg_4->unk_08 - sizeof(type_141C10);
    if (var_4 > 0)
        sub_F2C30(arg_0);
}

// match: sub_142C60 @ 0x00142C60
// sp-match: sub_142C60 @ 0x000EE390
// Kind 12: the particles' texture dictionary.
void sub_142C60(RwStream *arg_0, type_141C10 *arg_4)
{
    RwTexDictionary *var_4;

    if (RwStreamFindChunk(arg_0, rwID_TEXDICTIONARY, 0, 0))
    {
        var_4 = RwTexDictionaryStreamRead(arg_0, 0);
        sub_F2EE0(var_4);
    }
}

// match: sub_142CA0 @ 0x00142CA0
// sp-match: sub_142CA0 @ 0x000EE3C0
// Kind 13: the path nodes; one stage fewer of the loading screen left
// (dword_4B86FC).
void sub_142CA0(RwStream *arg_0, type_141C10 *arg_4)
{
    RwInt32 var_4;

    var_4 = arg_4->unk_08 - sizeof(type_141C10);
    if (var_4 > 0)
        sub_F8350(arg_0);
    dword_4B86FC--;
}

// match: sub_142CE0 @ 0x00142CE0
// sp-match: sub_142CE0 @ 0x000EE3F0
// Kind 10: the rest of the chunk read into a buffer that nothing keeps.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_142CE0(RwStream *arg_0, type_141C10 *arg_4)
{
    RwInt32 var_4;
    void *local_8;

    if (var_4 = arg_4->unk_08 - sizeof(type_141C10))
    {
        local_8 = RWSMalloc(var_4, 0x34250); // not an address: a memory hint
        RwStreamRead(arg_0, local_8, var_4);
    }
}

// match: sub_142D20 @ 0x00142D20
// sp-match: sub_142D20 @ 0x000EE420
// A texture dictionary handed to unk_4E5CC8 (no kind reaches it).
void sub_142D20(RwStream *arg_0, type_141C10 *arg_4)
{
    RwTexDictionary *var_4;

    if (RwStreamFindChunk(arg_0, rwID_TEXDICTIONARY, 0, 0))
    {
        var_4 = RwTexDictionaryStreamRead(arg_0, 0);
        if (var_4)
            unk_4E5CC8.sub_144690(var_4);
    }
}

// match: sub_142D70 @ 0x00142D70
// sp-match: sub_142D70 @ 0x000EE460
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Kind 18 within a section load: a list of type_143DC0 objects, each with
// its name, a value (none for -1) and its values, then the names of what it
// links to; each goes to unk_4E5CC8.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The names and their lengths are block-scoped: the image puts them below
// the /GS cookie, after the function-scope locals.
void sub_142D70(RwStream *arg_0, type_141C10 *arg_4)
{
    type_143DC0 *var_24;
    RwInt32 var_20;
    RwInt32 l1C;
    RwInt32 m_18;
    RwInt32 ebp_14;
    RwInt32 lv_10;

    RwStreamRead(arg_0, &var_20, sizeof(var_20));
    RwStreamRead(arg_0, &lv_10, sizeof(lv_10));
    while (lv_10--)
    {
        var_24 = new type_143DC0;
        if (var_24)
        {
            RwChar var_48[0x20];
            RwUInt8 v49;
            RwInt32 var_50;
            RwTexture *var_54;

            RwStreamRead(arg_0, &v49, sizeof(v49));
            RwStreamRead(arg_0, var_48, v49);
            var_48[v49] = 0;
            var_24->sub_144260(var_48);
            RwStreamRead(arg_0, &m_18, sizeof(m_18));
            if (m_18 == -1)
            {
            }
            else
            {
                var_24->set_unk_2C(m_18);
                RwStreamRead(arg_0, &l1C, sizeof(l1C));
                while (l1C--)
                {
                    RwStreamRead(arg_0, &var_50, sizeof(var_50));
                    var_24->sub_1440C0(var_50);
                }
            }
            RwStreamRead(arg_0, &ebp_14, sizeof(ebp_14));
            while (ebp_14--)
            {
                RwChar var_74[0x20];
                RwUInt8 var_75;

                RwStreamRead(arg_0, &var_75, sizeof(var_75));
                RwStreamRead(arg_0, var_74, var_75);
                var_74[var_75] = 0;
                var_54 = unk_4E5CC8.sub_144650(var_74);
                if (var_54)
                    var_24->sub_144070(var_54);
            }
            unk_4E5CC8.sub_144400(var_24);
        }
    }
}

// match: sub_142F70 @ 0x00142F70
// sp-match: sub_142F70 @ 0x000EF2B0
// Kind 19: a whole section load, as a run of (kind, size) sub-chunks up to
// kind 11, each read by its loader; a BSP or dictionary that cannot be read
// aborts the rest. The section's streaming record is marked done. Returns
// the section's slot (what the last BSP loader gave), or -1.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_142F70(RwStream *arg_0, type_141C10 *arg_4)
{
    RwInt32 var_4;
    RwInt32 v8;
    RwInt32 stk_C;
    RwInt32 var_10;

    var_10 = -1;
    stk_C = 0;
    while (!stk_C && RwStreamReadInt32(arg_0, &var_4, sizeof(var_4)))
    {
        if (var_4 == 11)
            break;
        RwStreamReadInt32(arg_0, &v8, sizeof(v8));
        switch (var_4)
        {
        case 0:
            var_10 = sub_142030(arg_0, arg_4);
            if (var_10 == -1)
                stk_C = 1;
            break;
        case 1:
            var_10 = sub_1421B0(arg_0, arg_4);
            if (var_10 == -1)
                stk_C = 1;
            break;
        case 2:
            var_10 = sub_142890(arg_0, arg_4);
            if (var_10 == -1)
                stk_C = 1;
            break;
        case 3:
            var_10 = sub_142490(arg_0, arg_4);
            if (var_10 == -1)
                stk_C = 1;
            break;
        case 4:
            if (sub_142330(arg_0, arg_4) == -1)
                stk_C = 1;
            break;
        case 5:
            sub_1427A0(arg_0, arg_4);
            break;
        case 6:
            sub_172820();
            sub_142620(arg_0, arg_4);
            break;
        case 8:
            sub_142A30(arg_0, arg_4);
            break;
        case 9:
            sub_142A90(arg_0, arg_4);
            break;
        case 19:
            sub_142AF0(arg_0, arg_4);
            break;
        case 10:
            sub_142B70(arg_0, arg_4);
            break;
        case 7:
            sub_123280(arg_0, v8);
            break;
        case 14:
            sub_19A750(arg_0);
            break;
        case 15:
            sub_123440(arg_0);
            break;
        case 13:
            if (!SectionInfo::sub_B0140())
                sub_172BB0();
            break;
        case 16:
            dword_4B2550.sub_8F330(arg_0);
            break;
        case 17:
            sub_142D20(arg_0, arg_4);
            break;
        case 18:
            sub_142D70(arg_0, arg_4);
            break;
        default:
            RwStreamSkip(arg_0, v8);
            break;
        }
    }
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS) // single player compiles the debug print out (SP 0xEF2B0)
    if (stk_C)
        sub_19A750("Received abort of section load...\n");
#endif
    if (var_10 >= 0 && var_10 < SECTION_SLOTS)
        get_4E5D30(var_10)->unk_04 = 0;
    return var_10;
}

// match: sub_143230 @ 0x00143230
// sp-match: sub_143230 @ 0x000EF4A0
// Kind 20: a list of objects: a count, then a record and its data for each; an
// object whose key is not known yet is made (kind 0xD), registered and
// read through its vf_000, else its data is skipped. Ends early when the stream does.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_143230(RwStream *arg_0, type_141C10 *arg_4)
{
    RwInt32 l4;
    RwInt32 var_8;
    RwUInt32 fp_C;
    RwInt32 local_10;
    RwUInt32 stk_14;

    local_10 = 0;
    dword_4B86FC--;
    if (!RwStreamReadInt32(arg_0, (RwInt32 *)&fp_C, sizeof(fp_C)))
        return;
    l4 = 0;
    for (stk_14 = 0; stk_14 < fp_C; stk_14++)
    {
        l4++;
        type_141C10 v30;
        type_199010 *v34;
        RwInt32 l38;

        if (!RwStreamRead(arg_0, &v30, sizeof(v30)))
            return;
        v34 = sub_198710(&v30.unk_0C.unk_04);
        if (!v34 && !sub_198770(&v30.unk_0C.unk_04))
        {
            v34 = sub_199010(&v30.unk_0C.unk_04, 0xD);
            sub_198FE0((type_3DF8D8_base *)v34);
            ((type_143230 *)v34)->vf_000(arg_0, &v30);
        }
        else
        {
            l38 = v30.unk_08 - sizeof(type_141C10);
            if (!RwStreamSkip(arg_0, l38))
                return;
        }
    }
    var_8 = local_10;
}

// match: sub_143360 @ 0x00143360
// sp-match: sub_143360 @ 0x000EEB20
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Kind 21: a list of objects: a count, then a record and its data for each; an
// object whose key is not known yet is made (kind 0x1E), registered and
// read (sub_1947F0), else its data is skipped. Ends early when the stream does.
void sub_143360(RwStream *arg_0, type_141C10 *arg_4)
{
    RwUInt32 var_14;
    RwInt32 lv_10;
    RwInt32 var_C;
    RwUInt32 bp_8;
    RwInt32 bp_4;

    lv_10 = 0;
    dword_4B86FC--;
    if (!RwStreamReadInt32(arg_0, (RwInt32 *)&bp_8, sizeof(bp_8)))
        return;
    bp_4 = 0;
    for (var_14 = 0; var_14 < bp_8; var_14++)
    {
        bp_4++;
        type_141C10 var_34;
        type_199010 *l18;
        RwInt32 var_38;

        if (!RwStreamRead(arg_0, &var_34, sizeof(var_34)))
            return;
        l18 = sub_198710(&var_34.unk_0C.unk_04);
        if (!l18 && !sub_198770(&var_34.unk_0C.unk_04))
        {
            l18 = sub_199010(&var_34.unk_0C.unk_04, 0x1E);
            sub_198FE0((type_3DF8D8_base *)l18);
            ((type_3DFE50 *)((type_1947F0 *)l18))->sub_1947F0(arg_0, (RwInt32)(&var_34));
        }
        else
        {
            var_38 = var_34.unk_08 - sizeof(type_141C10);
            if (!RwStreamSkip(arg_0, var_38))
                return;
        }
    }
    var_C = lv_10;
}

// match: sub_143480 @ 0x00143480
// sp-match: sub_143480 @ 0x000EEBF0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Kind 22: a list of objects: a count, then a record and its data for each; an
// object whose key is not known yet is made (kind 0x1C), registered and
// read (sub_193A00), else its data is skipped. Ends early when the stream does.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_143480(RwStream *arg_0, type_141C10 *arg_4)
{
    RwUInt32 var_14;
    RwInt32 lv_10;
    RwInt32 var_C;
    RwInt32 bp_8;
    RwUInt32 bp_4;

    lv_10 = 0;
    dword_4B86FC--;
    if (!RwStreamReadInt32(arg_0, (RwInt32 *)&bp_4, sizeof(bp_4)))
        return;
    bp_8 = 0;
    for (var_14 = 0; var_14 < bp_4; var_14++)
    {
        bp_8++;
        type_141C10 var_34;
        type_199010 *l18;
        RwInt32 var_38;

        if (!RwStreamRead(arg_0, &var_34, sizeof(var_34)))
            return;
        l18 = sub_198710(&var_34.unk_0C.unk_04);
        if (!l18 && !sub_198770(&var_34.unk_0C.unk_04))
        {
            l18 = sub_199010(&var_34.unk_0C.unk_04, 0x1C);
            sub_198FE0((type_3DF8D8_base *)l18);
            ((type_3DFCA0 *)((type_193A00 *)l18))->sub_193A00(arg_0, (RwInt32)(&var_34));
        }
        else
        {
            var_38 = var_34.unk_08 - sizeof(type_141C10);
            if (!RwStreamSkip(arg_0, var_38))
                return;
        }
    }
    var_C = lv_10;
}

// match: sub_1435A0 @ 0x001435A0
// sp-match: sub_1435A0 @ 0x000EECC0
// Kind 23: a list of objects: a count, then a record and its data for each; an
// object whose key is not known yet is made (kind 0x1B), registered and
// read (sub_193A00), else its data is skipped. Ends early when the stream does.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_1435A0(RwStream *arg_0, type_141C10 *arg_4)
{
    RwUInt32 var_14;
    RwInt32 lv_10;
    RwInt32 var_C;
    RwInt32 bp_8;
    RwUInt32 bp_4;

    lv_10 = 0;
    dword_4B86FC--;
    if (!RwStreamReadInt32(arg_0, (RwInt32 *)&bp_4, sizeof(bp_4)))
        return;
    bp_8 = 0;
    for (var_14 = 0; var_14 < bp_4; var_14++)
    {
        bp_8++;
        type_141C10 var_34;
        type_199010 *l18;
        RwInt32 var_38;

        if (!RwStreamRead(arg_0, &var_34, sizeof(var_34)))
            return;
        l18 = sub_198710(&var_34.unk_0C.unk_04);
        if (!l18 && !sub_198770(&var_34.unk_0C.unk_04))
        {
            l18 = sub_199010(&var_34.unk_0C.unk_04, 0x1B);
            sub_198FE0((type_3DF8D8_base *)l18);
            ((type_3DFCA0 *)((type_193A00 *)l18))->sub_193A00(arg_0, (RwInt32)(&var_34));
        }
        else
        {
            var_38 = var_34.unk_08 - sizeof(type_141C10);
            if (!RwStreamSkip(arg_0, var_38))
                return;
        }
    }
    var_C = lv_10;
}

// match: sub_1436C0 @ 0x001436C0
// sp-match: sub_1436C0 @ 0x000EED90
// Kind 24: a list of objects: a count, then a record and its data for each; an
// object whose key is not known yet is made (kind 0x1D), registered and
// read (sub_193A00), else its data is skipped. Ends early when the stream does.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_1436C0(RwStream *arg_0, type_141C10 *arg_4)
{
    RwUInt32 var_14;
    RwInt32 lv_10;
    RwInt32 var_C;
    RwInt32 bp_8;
    RwUInt32 bp_4;

    lv_10 = 0;
    dword_4B86FC--;
    if (!RwStreamReadInt32(arg_0, (RwInt32 *)&bp_4, sizeof(bp_4)))
        return;
    bp_8 = 0;
    for (var_14 = 0; var_14 < bp_4; var_14++)
    {
        bp_8++;
        type_141C10 var_34;
        type_199010 *l18;
        RwInt32 var_38;

        if (!RwStreamRead(arg_0, &var_34, sizeof(var_34)))
            return;
        l18 = sub_198710(&var_34.unk_0C.unk_04);
        if (!l18 && !sub_198770(&var_34.unk_0C.unk_04))
        {
            l18 = sub_199010(&var_34.unk_0C.unk_04, 0x1D);
            sub_198FE0((type_3DF8D8_base *)l18);
            ((type_3DFCA0 *)((type_193A00 *)l18))->sub_193A00(arg_0, (RwInt32)(&var_34));
        }
        else
        {
            var_38 = var_34.unk_08 - sizeof(type_141C10);
            if (!RwStreamSkip(arg_0, var_38))
                return;
        }
    }
    var_C = lv_10;
}

// match: sub_1437E0 @ 0x001437E0
// sp-match: sub_1437E0 @ 0x000EEE60
// Kind 25: a list of objects: a count, then a record and its data for each; an
// object whose key is not known yet is made (kind 0x2A), registered and
// read (sub_192870), else its data is skipped. Ends early when the stream does.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_1437E0(RwStream *arg_0, type_141C10 *arg_4)
{
    RwUInt32 var_14;
    RwInt32 lv_10;
    RwInt32 var_C;
    RwInt32 bp_8;
    RwUInt32 bp_4;

    lv_10 = 0;
    dword_4B86FC--;
    if (!RwStreamReadInt32(arg_0, (RwInt32 *)&bp_4, sizeof(bp_4)))
        return;
    bp_8 = 0;
    for (var_14 = 0; var_14 < bp_4; var_14++)
    {
        bp_8++;
        type_141C10 var_34;
        type_199010 *l18;
        RwInt32 var_38;

        if (!RwStreamRead(arg_0, &var_34, sizeof(var_34)))
            return;
        l18 = sub_198710(&var_34.unk_0C.unk_04);
        if (!l18 && !sub_198770(&var_34.unk_0C.unk_04))
        {
            l18 = sub_199010(&var_34.unk_0C.unk_04, 0x2A);
            sub_198FE0((type_3DF8D8_base *)l18);
            ((type_44E8D8_248 *)((type_192870 *)l18))->sub_192870(arg_0, (RwInt32)(&var_34));
        }
        else
        {
            var_38 = var_34.unk_08 - sizeof(type_141C10);
            if (!RwStreamSkip(arg_0, var_38))
                return;
        }
    }
    var_C = lv_10;
}

// match: sub_143900 @ 0x00143900
// sp-match: sub_143900 @ 0x000EE640
// Kind 27: the level's directory name (kept in dword_4E5CC4); a name of the
// form L_d_d asks for that level's hit-death data, else the shared one, and
// the scene data (the per-level branch is compiled out). Two stages of the
// loading screen pass.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_143900(RwStream *arg_0, type_141C10 *arg_4)
{
    RwInt32 var_4;
    RwChar slot_88[0x80];
    RwChar *loc8C;
    RwInt32 stk_90;
    RwChar *bp_94;

    var_4 = arg_4->unk_08 - sizeof(type_141C10);
    dword_4B86FC--;
    if (var_4 > 0)
    {
        bp_94 = (RwChar *)RWSMalloc(var_4, 0x34250); // not an address: a memory hint
        RwStreamRead(arg_0, bp_94, var_4);
        dword_4E5CC4 = (RwInt32)bp_94;
        stk_90 = 0;
        loc8C = bp_94;
        if (loc8C[0] == 'L' && loc8C[1] == '_' && isdigit(loc8C[2]) && loc8C[3] == '_' && isdigit(loc8C[4]))
            stk_90 = 1;
        dword_4B86FC++;
        if (stk_90)
        {
            sprintf(slot_88, "COD_MapData+HitDeathData%s+Filename", loc8C);
            sub_1989D0(slot_88, 0x12, 0, 0, 0);
        }
        else
        {
            sub_1989D0("COD_MapData+HitDeathData+Filename", 0x12, 0, 0, 0);
        }
        dword_4B86FC++;
        if (0)
        {
            sub_1989D0("COD_MapData+SceneData_shared+Filename", 0x18, 0, 0, 0);
            sprintf(slot_88, "COD_MapData+SceneDataL_%d_%d+Filename", loc8C[2] - '0', loc8C[4] - '0');
            sub_1989D0(slot_88, 0x18, 0, 0, 0);
        }
        else
        {
            sub_1989D0("COD_MapData+SceneData+Filename", 0x18, 0, 0, 0);
        }
    }
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS) // single player compiles the debug print out (SP 0xEE640)
    else
    {
        sub_19A750("NO level directory name received! This is bad!");
    }
#endif
}

// match: sub_143AF0 @ 0x00143AF0
// sp-match: sub_143AF0 @ 0x000EE760
// Kind 28: a clump bank, a weapon's (the top bit of unk_18 set; its bank
// and weapon in the next bytes) or a plain one, which is announced.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_143AF0(RwStream *arg_0, type_141C10 *arg_4)
{
    RwInt32 var_4;
    RwInt32 v8;
    RwInt32 stk_C;
    RwInt32 var_10;

    var_4 = arg_4->unk_08 - sizeof(type_141C10);
    if (var_4 > 0)
    {
        v8 = arg_4->unk_18;
        if ((v8 & 0x80000000) ? 1 : 0)
        {
            var_10 = (v8 & 0xFF00) >> 8;
            stk_C = v8 & 0xFF;
            sub_16F460(arg_0, var_10, stk_C);
        }
        else
        {
            sub_16EAE0(arg_0, v8);
            sub_6B5F0("ClumpBankLoaded", 0, 0, 0, 0, 0, 1, 0);
        }
    }
}

// match: sub_143B90 @ 0x00143B90
// sp-match: sub_143B90 @ 0x000EE7C0
// Kind 29: an animation data set, requested by the record's values; its
// arrival is announced when dword_4B8710 is set.
void sub_143B90(RwStream *arg_0, type_141C10 *arg_4)
{
    RwInt32 var_4;
    type_776F0 var_118;

    var_4 = arg_4->unk_08 - sizeof(type_141C10);
    if (var_4 > 0)
    {
        sprintf(var_118.unk_0C, "AnimDataSet Request");
        var_118.unk_00 = arg_4->unk_18;
        var_118.unk_04 = arg_4->unk_0C.unk_04.unk_00;
        var_118.unk_08 = arg_4->unk_0C.unk_04.unk_04;
        sub_776F0(arg_0, &var_118, 1);
        if (dword_4B8710)
            sub_6B5F0("AnimBankLoaded", 0, 0, 0, 0, 0, 1, 0);
    }
}

// match: sub_143C30 @ 0x00143C30
// sp-match: sub_143C30 @ 0x000EEF30
// While a section's BSP is read, textures are found in the global
// dictionary (sub_174520) and the section's arg_0 (sub_143C80); the
// previous find callback is kept for sub_143C60 to put back.
RwBool sub_143C30(RwTexDictionary *arg_0)
{
    dword_4CFA04 = RwTextureGetFindCallBack();
    dword_4CFA08[0] = sub_174520();
    dword_4CFA08[1] = arg_0;
    return RwTextureSetFindCallBack(sub_143C80);
}

// match: sub_143C60 @ 0x00143C60
// sp-match: sub_143C60 @ 0x000EE860
#ifdef CODFH_SP // returns nothing (SP 0xEE86B: pop ecx, the result unused)
void sub_143C60()
{
    RwTextureSetFindCallBack(dword_4CFA04);
}
#else
RwBool sub_143C60()
{
    return RwTextureSetFindCallBack(dword_4CFA04);
}
#endif

// match: sub_143C80 @ 0x00143C80
// sp-match: sub_143C80 @ 0x000EE870
// The texture arg_0 from the first of the two dictionaries that has it.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwTexture *sub_143C80(const RwChar *arg_0)
{
    RwInt32 var_4;
    RwTexture *local_8;

    for (var_4 = 0; var_4 < 2; var_4++)
    {
        if (dword_4CFA08[var_4])
        {
            local_8 = RwTexDictionaryFindNamedTexture(dword_4CFA08[var_4], arg_0);
            if (local_8)
                return local_8;
        }
    }
    return 0;
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?sub_19A750@@YAXPAURwStream@@@Z (folded into 0x19A750)
#ifndef CODFH_SP
// Single player keeps sub_142F70's call (SP 0xEF3CF), so the empty body is not in this file there.
void sub_19A750(struct RwStream * arg_0)
{
}
#endif

// ?sub_19A750@@YAXPAURwStream@@PAUtype_141C10@@@Z (folded into 0x19A750)
#ifndef CODFH_SP
// Single player keeps sub_141C10's calls for kinds 14, 15 and 30 (SP 0xEDDE0), so the empty
// body is not in this file there.
void sub_19A750(struct RwStream * arg_0, struct type_141C10 * arg_4)
{
}
#endif

// ?sub_19A750@@YAXPAUtype_173F50@@H@Z (folded into 0x19A750)
void sub_19A750(struct type_173F50 * arg_0, RwInt32 arg_4)
{
}
