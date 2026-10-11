// The pack file (game/pak.h): the path hashes, the set-up that reads
// d:\COD.PAK's directory and hooks RenderWare's file interface, and the
// replacement file functions.

#include "rw/ostypes.h"
#include "rw/osintf.h"
#include "game/pak.h"
#include "game/functions.h"
#include <string.h>
#include <stdio.h>
#include "rw/badevice.h"
#if defined(CODFH_WIN32)
extern "C" void plog(const RwChar *fmt, ...);
#endif

#ifdef CODFH_SP
// Single player uses the disc-error callback in these byte-count call slots;
// nonzero results return immediately from the callback.
void sp_sub_12C410(void *arg_0);
#endif

// Its data definitions (PLAN M5), in the image's address order.
// 0x004E22A8
type_4E22A8 dword_4E22A8;
// 0x004E23A8
RwInt32 dword_4E23A8;
// End of its data definitions.



// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0L@MJHDGMCA@d?3?2COD?4PAK?$AA@ @ 0x003DCCC0
// match: ??_C@_0EA@LPDNONCP@Unable?5to?5locate?5?$CFs?5in?5pack?5file@ @ 0x003DCCD0
// match: ??_C@_0M@KOCBOMJD@Read?5Error?6?$AA@ @ 0x003DCD10
// match: ??_C@_0CH@KNJNKPP@?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?5Seek?5retr@ @ 0x003DCD1C

// match: ?sub_16C800@@YAIPBDI@Z @ 0x0016C800
// sp-match: ?sub_16C800@@YAIPBDI@Z @ 0x0010A4A0

RwUInt32 sub_16C800(const RwChar *arg_0, RwUInt32 arg_4)
{
    RwChar var_408[0x400];
    RwUInt8 *var_4;

    strcpy(var_408, arg_0);
    var_4 = (RwUInt8 *)var_408;
    strupr((RwChar *)var_4);
    while (*var_4)
    {
        arg_4 *= 0x1000193;
        arg_4 ^= *var_4;
        var_4++;
    }
    return arg_4;
}

// match: ?sub_16C880@@YA_KPBD_K@Z @ 0x0016C880
// sp-match: ?sub_16C880@@YA_KPBD_K@Z @ 0x0010A520
RwUInt64 sub_16C880(const RwChar *arg_0, RwUInt64 arg_4)
{
    RwChar var_408[0x400];
    RwUInt8 *var_4;

    strcpy(var_408, arg_0);
    var_4 = (RwUInt8 *)var_408;
    strupr((RwChar *)var_4);
    while (*var_4)
    {
        RwUInt8 var_409 = *var_4;

        if (var_409 == '/')
            var_409 = '\\';
        if (var_409 == ';')
            break;
        arg_4 *= 0x100000001B3;
        arg_4 ^= var_409;
        var_4++;
    }
    return arg_4;
}

// match: ?sub_16C940@@YA_NXZ @ 0x0016C940
// sp-match: ?sub_16C940@@YA_NXZ @ 0x0010AA40
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
bool sub_16C940()
{
    RwInt32 var_10;
    RwFileFunctions *var_C;
    size_t bp_8;
    type_4E22A8 *bp_4;

    if (dword_4E22A8.unk_F8)
        return false;
    for (var_10 = 0; var_10 < 5; var_10++)
        dword_4E22A8.unk_80[var_10].unk_00 = 0;
    dword_4E22A8.unk_80[0].unk_00 = 1;
    bp_4 = &dword_4E22A8;
    dword_4E22A8.unk_CC = *RwOsGetFileInterface();
    sub_19CDE0("d:\\COD.PAK");
    bp_4->unk_BC = dword_4E22A8.unk_CC.rwfopen("d:\\COD.PAK", "rb");
#if defined(CODFH_WIN32)
    // (the Win32 port: without the pack nothing in it opens; say so)
    if (!bp_4->unk_BC)
        plog("pack: d:\\COD.PAK could not be opened: every file in it will be missing");
#endif
    if (!bp_4->unk_BC)
        return false;
    dword_4E22A8.unk_CC.rwfseek(bp_4->unk_BC, 0, 0);
    bp_8 = dword_4E22A8.unk_CC.rwfread(bp_4, 1, 0x80, bp_4->unk_BC);
#ifdef CODFH_SP
    sp_sub_12C410((void *)bp_8);
#else
    sub_19A750((const RwChar *)bp_8);
#endif
    bp_4->unk_C4 = (type_16CC10 *)RwMalloc(bp_4->unk_7C * sizeof(type_16CC10), 0x34250); // not an address: a memory hint
    bp_8 = dword_4E22A8.unk_CC.rwfread(bp_4->unk_C4, 1, bp_4->unk_7C * sizeof(type_16CC10), bp_4->unk_BC);
#ifdef CODFH_SP
    sp_sub_12C410((void *)bp_8);
#else
    sub_19A750((const RwChar *)bp_8);
#endif
    bp_4->unk_C8 = bp_4->unk_7C * sizeof(type_16CC10) + 0x80;
#if defined(CODFH_WIN32)
    {
        // (its directory, and the furthest end of a file in it against the pack's size: a
        // truncated or foreign pack shows here)
        RwInt32 i, nSize, nEnd = 0;

        for (i = 0; bp_4->unk_C4 && i < bp_4->unk_7C; i++)
            if (bp_4->unk_C4[i].unk_04 + bp_4->unk_C4[i].unk_00 > nEnd)
                nEnd = bp_4->unk_C4[i].unk_04 + bp_4->unk_C4[i].unk_00;
        dword_4E22A8.unk_CC.rwfseek(bp_4->unk_BC, 0, SEEK_END);
        nSize = dword_4E22A8.unk_CC.rwftell(bp_4->unk_BC);
        dword_4E22A8.unk_CC.rwfseek(bp_4->unk_BC, bp_4->unk_C8, SEEK_SET);
        plog("pack: d:\\COD.PAK opened: %d files, %d bytes, its files end at %d%s", bp_4->unk_7C, nSize, nEnd,
             nSize >= 0 && nEnd > nSize ? " (PAST ITS END: the pack is truncated or not this game's)" : "");
    }
#endif
    var_C = RwOsGetFileInterface();
    var_C->rwfopen = sub_16CB00;
    var_C->rwfclose = sub_16CCC0;
    var_C->rwfread = sub_16CD00;
    var_C->rwfgets = sub_16CE70;
    var_C->rwfeof = sub_16D1B0;
    var_C->rwfseek = sub_16D070;
    var_C->rwfexist = sub_16D1E0;
    dword_4E22A8.unk_F8 = 1;
    sub_1A26F0();
    return true;
}

// match: ?sub_16CB00@@YAPAXPBD0@Z @ 0x0016CB00
// sp-match: ?sub_16CB00@@YAPAXPBD0@Z @ 0x0010A780
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void *sub_16CB00(const RwChar *arg_0, const RwChar *arg_4)
{
    void *var_10;
    RwInt32 var_C;
    void *bp_8;
    type_16CC10 *bp_4;

    if (strchr(arg_4, 'w') || strchr(arg_4, 'W') || arg_0[0] == 'd' && arg_0[1] == ':')
    {
        bp_8 = dword_4E22A8.unk_CC.rwfopen(arg_0, arg_4);
#if defined(CODFH_WIN32)
        plog("pack: open %s (\"%s\", from disk): %s", arg_0, arg_4, bp_8 ? "opened" : "NOT FOUND");
#endif
        return bp_8;
    }
    bp_4 = sub_16CC10(arg_0);
    if (bp_4)
    {
        for (var_C = 0; var_C < 5; var_C++)
        {
            if (!dword_4E22A8.unk_80[var_C].unk_00)
            {
                dword_4E22A8.unk_80[var_C].unk_00 = 1;
                dword_4E22A8.unk_80[var_C].unk_01 = 0;
                dword_4E22A8.unk_80[var_C].unk_04 = bp_4;
                dword_4E22A8.unk_80[var_C].unk_08 = 0;
#if defined(CODFH_WIN32)
                plog("pack: open %s (in COD.PAK, %d bytes)", arg_0, bp_4->unk_00);
#endif
                return (void *)var_C;
            }
        }
    }
    else
    {
#ifndef CODFH_SP
        // Single player compiles the debug print out (SP 0x10A780).
        sub_19A750("Unable to locate %s in pack file - attempting to load off disk\n", arg_0);
#endif
        var_10 = dword_4E22A8.unk_CC.rwfopen(arg_0, arg_4);
#if defined(CODFH_WIN32)
        // (the Win32 port: a file the pack lacks, and whether the disk fallback, relative to
        // the working directory, found it; the image's print above is compiled out of SP)
        plog("pack: %s is not in COD.PAK (%d files); from disk: %s", arg_0, dword_4E22A8.unk_7C,
             var_10 ? "opened" : "NOT FOUND");
#endif
        return var_10;
    }
#if defined(CODFH_WIN32)
    plog("pack: %s found but all five pack handles are in use", arg_0);
#endif
    return 0;
}

// match: ?sub_16CC10@@YAPAUtype_16CC10@@PBD@Z @ 0x0016CC10
// sp-match: ?sub_16CC10@@YAPAUtype_16CC10@@PBD@Z @ 0x0010A5C0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The directory entry of the path arg_0 (after any drive), or 0.
type_16CC10 *sub_16CC10(const RwChar *arg_0)
{
    RwInt32 var_14;
    RwUInt64 ebp_10;
    const RwChar *l4;

    l4 = strchr(arg_0, ':');
    if (l4)
        l4++;
    else
        l4 = arg_0;
    ebp_10 = sub_16C880(l4, 0x84222325CBF29CE4); // not an address: FNV-1's 64-bit basis with its halves swapped
    for (var_14 = 0; var_14 < dword_4E22A8.unk_7C; var_14++)
    {
        if (dword_4E22A8.unk_C4[var_14].unk_08 == ebp_10)
            return &dword_4E22A8.unk_C4[var_14];
    }
    return 0;
}

// match: ?sub_16CCC0@@YAHPAX@Z @ 0x0016CCC0
// sp-match: ?sub_16CCC0@@YAHPAX@Z @ 0x0010A630
RwInt32 sub_16CCC0(void *arg_0)
{
    RwInt32 var_4 = (RwInt32)arg_0;

    if (var_4 > 5)
        return dword_4E22A8.unk_CC.rwfclose(arg_0);
    dword_4E22A8.unk_80[var_4].unk_00 = 0;
    return 0;
}

// match: ?sub_16CD00@@YAIPAXII0@Z @ 0x0016CD00
// sp-match: ?sub_16CD00@@YAIPAXII0@Z @ 0x0010A820
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
size_t sub_16CD00(void *arg_0, size_t arg_4, size_t arg_8, void *arg_C)
{
    RwInt32 var_10;
    RwInt32 var_C;
    RwInt32 bp_8;
    RwInt32 bp_4;

    bp_8 = (RwInt32)arg_C;
    if (bp_8 > 5)
    {
        size_t var_14 = dword_4E22A8.unk_CC.rwfread(arg_0, arg_4, arg_8, arg_C);

#ifdef CODFH_SP
        sp_sub_12C410((void *)var_14);
#else
        sub_19A750((const RwChar *)var_14);
#endif
        return var_14;
    }
    bp_4 = arg_4 * arg_8;
    if (!bp_4)
        return 0;
    if (dword_4E22A8.unk_80[bp_8].unk_01)
        return 0;
    var_10 = dword_4E22A8.unk_80[bp_8].unk_04->unk_04 + dword_4E22A8.unk_80[bp_8].unk_08;
    if (var_10 != dword_4E22A8.unk_C8)
        sub_16D070((void *)bp_8, dword_4E22A8.unk_80[bp_8].unk_08, 0);
    var_C = dword_4E22A8.unk_80[bp_8].unk_04->unk_00 - dword_4E22A8.unk_80[bp_8].unk_08;
    if (bp_4 >= var_C)
    {
        dword_4E22A8.unk_80[bp_8].unk_01 = 1;
        bp_4 = var_C;
    }
    else
    {
        dword_4E22A8.unk_80[bp_8].unk_01 = 0;
    }
    if (bp_4)
    {
        size_t var_18 = dword_4E22A8.unk_CC.rwfread(arg_0, 1, bp_4, dword_4E22A8.unk_BC);

#ifdef CODFH_SP
        sp_sub_12C410((void *)var_18);
#else
        sub_19A750((const RwChar *)var_18);
#endif
#ifndef CODFH_SP
        // Single player compiles the debug print out (SP 0x10A8DE goes straight on).
        if (var_18 != bp_4)
            sub_19A750("Read Error\n");
#endif
        dword_4E22A8.unk_80[bp_8].unk_08 += bp_4;
        dword_4E22A8.unk_C8 += bp_4;
    }
    return bp_4;
}

// match: ?sub_16CE70@@YAPADPADHPAX@Z @ 0x0016CE70
// sp-match: ?sub_16CE70@@YAPADPADHPAX@Z @ 0x0010A900
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwChar *sub_16CE70(RwChar *arg_0, RwInt32 arg_4, void *arg_8)
{
    RwInt32 var_14;
    RwInt32 lv_10;
    RwInt32 var_C;
    RwInt32 bp_8;
    RwInt32 bp_4;

    bp_4 = (RwInt32)arg_8;
    if (bp_4 > 5)
        return dword_4E22A8.unk_CC.rwfgets(arg_0, arg_4, arg_8);
    if (dword_4E22A8.unk_80[bp_4].unk_01)
        return 0;
    var_C = dword_4E22A8.unk_80[bp_4].unk_04->unk_04 + dword_4E22A8.unk_80[bp_4].unk_08;
    if (var_C != dword_4E22A8.unk_C8)
        sub_16D070((void *)bp_4, dword_4E22A8.unk_80[bp_4].unk_08, 0);
    if (!(bp_8 = dword_4E22A8.unk_80[bp_4].unk_04->unk_00 - dword_4E22A8.unk_80[bp_4].unk_08))
    {
        dword_4E22A8.unk_80[bp_4].unk_01 = 1;
        return 0;
    }
    if (arg_4 < 0)
        arg_4 = 0;
    if (arg_4 > bp_8 + 1)
        arg_4 = bp_8 + 1;
    lv_10 = dword_4E22A8.unk_CC.rwftell(dword_4E22A8.unk_BC);
    if (!dword_4E22A8.unk_CC.rwfgets(arg_0, arg_4, dword_4E22A8.unk_BC))
    {
        dword_4E22A8.unk_80[bp_4].unk_01 = 1;
        return 0;
    }
    lv_10 = dword_4E22A8.unk_CC.rwftell(dword_4E22A8.unk_BC) - lv_10;
    if (lv_10 > arg_4)
    {
        arg_0[arg_4] = 0;
        dword_4E22A8.unk_80[bp_4].unk_01 = 1;
    }
    if (dword_4E23A8)
    {
        var_14 = strlen(arg_0);
        if (arg_0[var_14 - 2] == '\r' && arg_0[var_14 - 1] == '\n')
        {
            arg_0[var_14 - 2] = '\n';
            arg_0[var_14 - 1] = 0;
        }
    }
    dword_4E22A8.unk_80[bp_4].unk_08 += lv_10;
    dword_4E22A8.unk_C8 += lv_10;
    if (dword_4E22A8.unk_80[bp_4].unk_08 >= dword_4E22A8.unk_80[bp_4].unk_04->unk_00)
        dword_4E22A8.unk_80[bp_4].unk_01 = 1;
    return arg_0;
}

// match: ?sub_16D070@@YAHPAXJH@Z @ 0x0016D070
// sp-match: ?sub_16D070@@YAHPAXJH@Z @ 0x0010A660
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_16D070(void *arg_0, RwFileSeekOffset arg_4, RwInt32 arg_8)
{
    RwInt32 var_14;
    type_16D070 *lv_10;
    RwInt32 var_C;
    RwInt32 bp_8;
    RwInt32 bp_4;

    bp_4 = (RwInt32)arg_0;
    if (bp_4 > 5)
        return dword_4E22A8.unk_CC.rwfseek(arg_0, arg_4, arg_8);
    bp_8 = dword_4E22A8.unk_80[bp_4].unk_08;
    switch (arg_8)
    {
    case 0:
        bp_8 = arg_4;
        break;
    case 1:
        bp_8 = dword_4E22A8.unk_80[bp_4].unk_08 + arg_4;
        break;
    case 2:
        bp_8 = dword_4E22A8.unk_80[bp_4].unk_04->unk_00 + arg_4;
        break;
    }
    if (bp_8 > dword_4E22A8.unk_80[bp_4].unk_04->unk_00)
        bp_8 = dword_4E22A8.unk_80[bp_4].unk_04->unk_00;
    if (bp_8 < 0)
        bp_8 = 0;
    var_14 = dword_4E22A8.unk_80[bp_4].unk_04->unk_04 + bp_8;
    lv_10 = (type_16D070 *)dword_4E22A8.unk_BC;
    var_C = 0;
    do
    {
        if (var_C)
            printf("********************** Seek retry #%d\n", var_C);
        dword_4E22A8.unk_CC.rwfseek(dword_4E22A8.unk_BC, var_14, 0);
        var_C++;
    } while (lv_10->unk_20 == 3);
    dword_4E22A8.unk_C8 = var_14;
    dword_4E22A8.unk_80[bp_4].unk_08 = bp_8;
    return 1;
}

// match: ?sub_16D1B0@@YAHPAX@Z @ 0x0016D1B0
// sp-match: ?sub_16D1B0@@YAHPAX@Z @ 0x0010A720
RwInt32 sub_16D1B0(void *arg_0)
{
    RwInt32 var_4 = (RwInt32)arg_0;

    if (var_4 > 5)
        return dword_4E22A8.unk_CC.rwfeof(arg_0);
    return dword_4E22A8.unk_80[var_4].unk_01;
}

// match: ?sub_16D1E0@@YAHPBD@Z @ 0x0016D1E0
// sp-match: ?sub_16D1E0@@YAHPBD@Z @ 0x0010A740
RwBool sub_16D1E0(const RwChar *arg_0)
{
    type_16CC10 *var_4 = sub_16CC10(arg_0);

    return var_4 != 0;
}

// match: ?sub_16D200@@YAIPAX@Z @ 0x0016D200
// sp-match: ?sub_16D200@@YAIPAX@Z @ 0x0010A760
// The size of the pack file open as arg_0.
RwUInt32 sub_16D200(void *arg_0)
{
    RwInt32 var_4 = (RwInt32)arg_0;

    return dword_4E22A8.unk_80[var_4].unk_04->unk_00;
}
