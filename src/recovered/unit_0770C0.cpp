// The animation banks: their heap, the data sets loaded into them from
// "ANIMGRPS\..." files, and their loading and unloading. The file's
// original name is not recovered (M1), so it is named for its start
// address.

#include <stdio.h>
#include <string.h>

#include "rw/ostypes.h"
#include "rw/bastream.h"
#include "rw/batypes.h"
#include "game/functions.h"
#include "types/animbank.h"
#include "types/type_3D3548.h"
#include "rw/badevice.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x00428BEC
type_428BEC dword_428BEC[3] = {
    { 4, 128, 1 },
    { 8, 16, 2 },
#ifdef CODFH_SP // single player's third bank is { 24, 16, 1 } (SP 0x320D1C)
    { 24, 16, 1 },
#else
    { 96, 34, 1 },
#endif
};
// 0x00449B90
RwChar byte_449B90[256];
// 0x00449C90
RwUInt32 dword_449C90;
// 0x00449C94
type_449C94 *dword_449C94;
// 0x00449C98
RwUInt8 *dword_449C98;
// 0x00449C9C
RwInt32 dword_449C9C;
// 0x00449CA0
type_449CA0 dword_449CA0[dword_449CA0_count];
// 0x0044A504
RwInt32 dword_44A504;
// End of its data definitions.



// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).
CAnimObjectPool byte_44A508[3];
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0CP@HKDNHEPE@?$CK?$CK?$CKTotal?5size?5allocated?5for?5all?5@ @ 0x003D38AC
// match: ??_C@_0BB@JIEGAGOC@Size?5per?5bank?5?$CFd?$AA@ @ 0x003D38DC
// match: ??_C@_0BG@EOPEIBBM@Anim?5bank?5?$CFd?5size?3?5?$CFd?$AA@ @ 0x003D38F0
// match: ??_C@_0BJ@GEDDPEHH@Number?5of?5anim?5banks?3?5?$CFd?$AA@ @ 0x003D3908
// match: ??_C@_0CH@ELIHOGPE@Size?5Allocated?5for?5DataSet?5Entri@ @ 0x003D3924
// match: ??_C@_0CO@KEPHMBHK@?$CK?$CK?$CK?$CK?$CK?$CKANIMATION?5HEAP?5SIZE?5ALLOCA@ @ 0x003D394C
// match: ??_C@_0CO@LIFFEDLL@?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK@ @ 0x003D397C
// match: ??_C@_0CE@NIAMAHDD@Unabled?5to?5open?5anim?5bank?5file?3?5@ @ 0x003D39AC
// match: ??_C@_0O@FDCFGIFM@ANIMGRPS?2?$CFs?$CFs?$AA@ @ 0x003D39D0
// match: ??_C@_0GC@LHLOMAHN@?6BAD?5DATA?$CB?5BAD?5DATA?$CB?5BAD?5DATA?$CB?6?6@ @ 0x003D39E0
// match: ??_C@_0DG@NGMFIKNE@Adding?5load?5of?5Anim?5bank?5?$CFs?5slot@ @ 0x003D3A44
// match: ??_C@_0BO@NENNIJOD@Unloading?5anim?5bank?5slot?5?$CFd?5?6?$AA@ @ 0x003D3A7C
// match: ??_C@_0DO@LMPEIHEL@ERROR?3?5Can?8t?5unload?5a?5bank?5with?5@ @ 0x003D3A9C
// match: ??_C@_0GE@KEJOAHOM@ERROR?3?5Can?8t?5unload?5a?5bank?5with?5@ @ 0x003D3AE0
// match: ??_C@_0FA@MOLGDBHP@?6?$CK?6ERROR?3?5Attempting?5to?5unload?5a@ @ 0x003D3B48
// match: ??_C@_0FA@DEMBHBIN@ERROR?$CB?5Cannot?5load?5anim?5bank?5?$CFx?3@ @ 0x003D3B98
// match: ??_C@_0EN@JACCPJPM@Requested?5Animation?5bank?5?$CFx?3?$CFx?5i@ @ 0x003D3BE8
// match: ??_C@_0BO@GJCNCNLJ@Out?5of?5animation?5bank?5memory?$CB?$AA@ @ 0x003D3C38
// match: .CRT$XCU+0 @ 0x00426DEC
// match: ?dword_428BEC@@3PAUtype_428BEC@@A @ 0x00428BEC

// match: _$E1 @ 0x00309BD0
// match: _$E2 @ 0x0030DE50
// match: ?sub_770C0@@YAXXZ @ 0x000770C0
// sp-match: ?sub_770C0@@YAXXZ @ 0x00062180
// sp-match: _$E1 @ 0x0021C660
// sp-match: _$E2 @ 0x0021E280

void sub_770C0()
{
    dword_449C90 = 0;
    dword_449C94 = 0;
    dword_449C98 = 0;
}

// match: ?sub_770F0@@YAXIIPAI@Z @ 0x000770F0
// sp-match: ?sub_770F0@@YAXIIPAI@Z @ 0x000621A0
// Sets up arg_0 banks of arg_4 bytes each, or of the sizes arg_8 (at least
// 0x800 counted, 300 given, each).
void sub_770F0(RwUInt32 arg_0, RwUInt32 arg_4, RwUInt32 *arg_8)
{
    RwUInt32 var_4;
    RwUInt32 v8;
    RwUInt8 *stk_C;
    RwUInt32 var_10;

    var_4 = 0;
#ifndef CODFH_SP
    // single player compiles the debug prints out (SP 0x621A0)
    sub_19A750("*********************************************");
    sub_19A750("******ANIMATION HEAP SIZE ALLOCATION*********");
#endif
    dword_449C90 = arg_0;
    var_4 = arg_0 * 0x44;
    dword_449C94 = (type_449C94 *)RwMalloc(var_4, 0x34251); // not an address: an allocation tag
#ifndef CODFH_SP
    sub_19A750("Size Allocated for DataSet Entries: %d", var_4);
    sub_19A750("Number of anim banks: %d", arg_0);
#endif
    var_4 = 0;
    for (v8 = 0; v8 < arg_0; v8++) {
        if (arg_8 != 0) {
            var_4 += arg_8[v8] < 0x800 ? 0x800 : arg_8[v8];
#ifndef CODFH_SP
            sub_19A750("Anim bank %d size: %d", v8 + 1, arg_8[v8]);
#endif
        }
        dword_449C94[v8].unk_00 = v8;
        dword_449C94[v8].unk_04 = 0;
        dword_449C94[v8].unk_10 = 0;
        dword_449C94[v8].unk_14 = 0;
        dword_449C94[v8].unk_18 = 0;
        dword_449C94[v8].unk_08 = 0;
        dword_449C94[v8].unk_0C = 0;
        dword_449C94[v8].unk_1C = 0;
        dword_449C94[v8].unk_20 = 0;
    }
    if (var_4 == 0) {
        var_4 = arg_0 * arg_4;
#ifndef CODFH_SP
        sub_19A750("Size per bank %d", arg_4);
#endif
    }
    dword_449C98 = (RwUInt8 *)RwMalloc(var_4, 0x34251); // not an address: an allocation tag
    stk_C = dword_449C98;
#ifndef CODFH_SP
    sub_19A750("***Total size allocated for all anim banks: %d", var_4);
#endif
    for (v8 = 0; v8 < arg_0; v8++) {
        dword_449C94[v8].unk_18 = 0;
        dword_449C94[v8].unk_10 = (type_77D30 *)stk_C;
        if (arg_8 != 0) {
            var_10 = 300;
            if (var_10 < arg_8[v8])
                var_10 = arg_8[v8];
            dword_449C94[v8].unk_14 = var_10;
            stk_C += var_10;
        } else {
            dword_449C94[v8].unk_14 = arg_4;
            stk_C += arg_4;
        }
    }
#ifndef CODFH_SP
    sub_19A750("*********************************************");
#endif
}

// match: ?sub_773A0@@YAXXZ @ 0x000773A0
// sp-match: ?sub_773A0@@YAXXZ @ 0x00062690
// Destroys the heap-built sets and frees the banks and their heap.
void sub_773A0()
{
    RwUInt32 var_4;

    if (dword_449C94 != 0) {
        for (var_4 = 0; var_4 < dword_449C90; var_4++) {
            if (dword_449C94[var_4].unk_10 != 0 && dword_449C94[var_4].unk_1C != 0
                && dword_449C94[var_4].unk_10->is_heap()) {
                delete dword_449C94[var_4].unk_10;
                dword_449C94[var_4].unk_10 = 0;
            }
        }
        RwFree(dword_449C94);
        dword_449C94 = 0;
    }
    if (dword_449C98 != 0) {
        RwFree(dword_449C98);
        dword_449C98 = 0;
    }
}

// match: ?sub_774F0@@YAHUtype_449C94_08@@H@Z @ 0x000774F0
// sp-match: ?sub_774F0@@YAHUtype_449C94_08@@H@Z @ 0x000622D0
// Whether bank arg_8 holds the loaded set arg_0, arg_4.
RwInt32 sub_774F0(type_449C94_08 arg_0, RwInt32 arg_8)
{
    if (dword_449C94[arg_8].unk_08 == arg_0.unk_00 && dword_449C94[arg_8].unk_0C == arg_0.unk_04
        && dword_449C94[arg_8].unk_1C != 0)
        return 1;
    return 0;
}

// match: ?sub_77540@@YAHPBDUtype_449C94_08@@IHH@Z @ 0x00077540
// sp-match: ?sub_77540@@YAHPBDUtype_449C94_08@@IHH@Z @ 0x00062730
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Loads the set arg_4 named Source into bank arg_C from its
// "ANIMGRPS\..." file.
RwInt32 sub_77540(const RwChar *Source, type_449C94_08 arg_4, RwUInt32 arg_C, RwInt32 arg_10, RwInt32 arg_14)
{
    RwChar var_360[0x100];
    RwChar var_260[0x100];
    type_776F0 var_160;
    RwChar l50[0x40];
    RwChar *var_8;
    RwStream *l4;

    dword_449C94[arg_C].unk_08 = arg_4.unk_00;
    dword_449C94[arg_C].unk_0C = arg_4.unk_04;
    dword_449C94[arg_C].unk_04 |= 0x80000000;
    strncpy(dword_449C94[arg_C].unk_24, Source, 31);
    memset(&var_160, 0, 0x44);
    var_160.unk_00 = arg_C;
    var_160.unk_04 = arg_4.unk_00;
    var_160.unk_08 = arg_4.unk_04;
    strcpy(l50, Source);
    var_8 = strchr(l50, '_');
    if (var_8 != 0) {
        var_8[3] = '\\';
        var_8[4] = 0;
    } else
        l50[0] = 0;
    sprintf(var_260, "ANIMGRPS\\%s%s", l50, Source);
    sub_D7F20(var_360, var_260);
    strncpy(var_160.unk_0C, var_360, 255);
    l4 = RwStreamOpen(rwSTREAMFILENAME, rwSTREAMREAD, var_360);
    if (l4 != 0) {
        sub_776F0(l4, &var_160, 1);
        RwStreamClose(l4, var_360);
    } else
        sprintf(byte_449B90, "Unabled to open anim bank file: %s!", var_160.unk_0C);
    return 1;
}

// match: ?sub_776F0@@YAHPAURwStream@@PAUtype_776F0@@H@Z @ 0x000776F0
// sp-match: ?sub_776F0@@YAHPAURwStream@@PAUtype_776F0@@H@Z @ 0x00062310
RwInt32 sub_776F0(RwStream *arg_0, type_776F0 *arg_4, RwInt32 arg_8)
{
    type_77D30 *var_4;

    if (arg_0 != 0) {
        var_4 = sub_77E40(arg_0, dword_449C94[arg_4->unk_00].unk_10,
                          dword_449C94[arg_4->unk_00].unk_14);
        if (var_4 != 0) {
            if (var_4->get_unk_14() > dword_449C94[arg_4->unk_00].unk_20)
                dword_449C94[arg_4->unk_00].unk_20 = var_4->get_unk_14();
            dword_449C94[arg_4->unk_00].unk_1C = 1;
            return 1;
        }
        dword_449C94[arg_4->unk_00].unk_1C = 0;
        sprintf(byte_449B90, "\nBAD DATA! BAD DATA! BAD DATA!\n\nNot enough memory to load anim bank "
                             "file\n into anim bank slot %d\n",
                arg_4->unk_00);
        return 0;
    }
    sprintf(byte_449B90, "Unabled to open anim bank file: %s!", arg_4->unk_0C);
    return 0;
}

// match: ?sub_777F0@@YAHPBDUtype_449C94_08@@HPAURwV3d@@@Z @ 0x000777F0
// sp-match: ?sub_777F0@@YAHPBDUtype_449C94_08@@HPAURwV3d@@@Z @ 0x000623C0
// Queues the load of the set arg_4, arg_8 (the file arg_0) into bank arg_C,
// unloading what it holds; arg_10 is the trigger asking, or 0 for a script.
RwInt32 sub_777F0(const RwChar *arg_0, type_449C94_08 arg_4, RwInt32 arg_C, RwV3d *arg_10)
{
    RwUInt32 var_4;
    RwUInt32 v8;
    bool l9;

    if (dword_449C94[arg_C].unk_08 == arg_4.unk_00 && dword_449C94[arg_C].unk_0C == arg_4.unk_04) {
#ifndef CODFH_SP
        // single player compiles the debug prints out (SP 0x623C0)
        sub_19A750("Requested Animation bank %x:%x is already loaded in slot %d. Ignoring load.\n",
                   arg_4.unk_00, arg_4.unk_04, arg_C);
#endif
        return 0;
    }
    for (var_4 = 0; var_4 < dword_449C90; var_4++) {
        if (dword_449C94[var_4].unk_08 == arg_4.unk_00 && dword_449C94[var_4].unk_0C == arg_4.unk_04) {
            RwChar var_110[0x100];

            sprintf(var_110,
                    "ERROR! Cannot load anim bank %x:%x into slot %d.  It is already loaded in %d!!\n",
                    arg_4.unk_00, arg_4.unk_04, arg_C + 1, var_4 + 1);
#ifndef CODFH_SP
            sub_19A750(var_110);
#endif
        }
    }
    l9 = false;
    v8 = dword_449C94[arg_C].unk_10->unk_18;
    for (var_4 = 0; var_4 < v8; var_4++) {
        type_77D30_28 *var_118;
        type_77D30_28 *var_114;

        var_118 = dword_449C94[arg_C].unk_10->unk_28[var_4];
        while (var_118 != 0) {
            var_114 = var_118->unk_24;
            if (sub_788C0(var_118->unk_00, 1)) {
#ifndef CODFH_SP
                sub_19A750("\n*\nERROR: Attempting to unload animation %s (in bank %d) while still "
                           "active.\n*\n",
                           var_118->unk_04, arg_C + 1);
#endif
                l9 = true;
            }
            var_118 = var_114;
        }
    }
    if (l9) {
        RwChar var_218[0x100];

        if (arg_10 != 0)
            sprintf(var_218,
                    "ERROR: Can't unload a bank with active animations.  AnimPackTrigger @ position "
                    "%9.4f, %9.4f, %9.4f\n",
                    arg_10->x, arg_10->y, arg_10->z);
        else
            sprintf(var_218, "ERROR: Can't unload a bank with active animations from SCRIPT");
    }
    if (dword_449C94[arg_C].unk_04 & 0x80000000) {
#ifndef CODFH_SP
        sub_19A750("Unloading anim bank slot %d \n", arg_C);
#endif
        dword_449C94[arg_C].unk_04 &= 0x7FFFFFFF;
        dword_449C94[arg_C].unk_18 = 0;
    }
    dword_449C94[arg_C].unk_08 = arg_4.unk_00;
    dword_449C94[arg_C].unk_0C = arg_4.unk_04;
    dword_449C94[arg_C].unk_1C = 0;
#ifndef CODFH_SP
    sub_19A750("Adding load of Anim bank %s slot %d to AsyncQueue...\n", arg_0, arg_C);
#endif
    sub_81EB0(2, arg_0, (RwInt32)&dword_449C94[arg_C]);
    return 1;
}

// match: ?sub_77AC0@@YAHPAUtype_77D30@@@Z @ 0x00077AC0
// sp-match: ?sub_77AC0@@YAHPAUtype_77D30@@@Z @ 0x000625B0
// Puts the set arg_0 (built elsewhere) into the first free bank.
RwInt32 sub_77AC0(type_77D30 *arg_0)
{
    RwUInt32 var_4;

    for (var_4 = 0; var_4 < dword_449C90; var_4++) {
        if (dword_449C94[var_4].unk_10 == 0)
            break;
    }
    if (var_4 == dword_449C90)
        return 0;
    dword_449C94[var_4].unk_04 = 0x80000000;
    dword_449C94[var_4].unk_10 = arg_0;
    dword_449C94[var_4].unk_14 = arg_0->get_unk_14();
    dword_449C94[var_4].unk_18 = 0;
    return 1;
}

// match: ?sub_77B70@@YAHHPAPAX0@Z @ 0x00077B70
// sp-match: ?sub_77B70@@YAHHPAPAX0@Z @ 0x00062620
// Finds the animation arg_0 in the loading banks (sub_77DC0).
RwInt32 sub_77B70(RwInt32 arg_0, void **arg_4, void **arg_8)
{
    RwUInt32 var_4;
    RwInt32 local_8;

    local_8 = 0;
    for (var_4 = 0; var_4 < dword_449C90; var_4++) {
        if (dword_449C94[var_4].unk_10 == 0 || !(dword_449C94[var_4].unk_04 & 0x80000000))
            continue;
        type_77D30 *var_C = dword_449C94[var_4].unk_10;

        if (var_C->sub_77DC0(arg_0, arg_4, arg_8)) {
            local_8 = 1;
            break;
        }
    }
    return local_8;
}

// match: ??2type_77D30@@SAPAXIPAEI@Z @ 0x00077C10
// sp-match: ??2type_77D30@@SAPAXIPAEI@Z @ 0x000628B0
void *type_77D30::operator new(RwUInt32 arg_0, RwUInt8 *arg_4, RwUInt32 arg_8)
{
    type_77D30 *var_4;

    if (arg_4 == 0) {
        var_4 = (type_77D30 *)RwMalloc(arg_0 + 0x100, 0x34251); // not an address: an allocation tag
        arg_4 = (RwUInt8 *)var_4;
        var_4->unk_24 = 0;
        var_4->unk_20 = 0;
    } else {
        var_4 = (type_77D30 *)arg_4;
        var_4->unk_24 = arg_8;
        var_4->unk_20 = arg_4 + arg_0 + 0x100;
    }
    var_4->unk_18 = 0x40;
    var_4->unk_00 = 1;
    var_4->unk_14 = 0;
    return arg_4;
}

// match: ??0type_77D30@@QAE@XZ @ 0x00077CA0
// sp-match: ??0type_77D30@@QAE@XZ @ 0x00062920
type_77D30::type_77D30()
{
    RwInt32 var_4;

    if (unk_00) {
        unk_04 = 0x41445354;
        unk_08 = 0x1000;
        unk_14 = 0;
        unk_1C = unk_18 - 1;
        unk_0C = 0;
        unk_10 = 0;
        for (var_4 = 0; var_4 < unk_18; var_4++)
            unk_28[var_4] = 0;
    }
}

// match: ??1type_77D30@@QAE@XZ @ 0x00077D30
// sp-match: ??1type_77D30@@QAE@XZ @ 0x00062980
type_77D30::~type_77D30()
{
    RwInt32 var_4;
    type_77D30_28 *v8;
    type_77D30_28 *varC;

    if (unk_00) {
        for (var_4 = 0; var_4 < unk_18; var_4++) {
            varC = unk_28[var_4];
            while (varC != 0) {
                v8 = varC->unk_24;
                sub_7FFB0((RtAnimAnimation *)varC->unk_28);
                delete varC->unk_2C;
                delete varC;
                varC = v8;
            }
        }
    }
}

// match: ?sub_77DC0@type_77D30@@QAE_NHPAPAX0@Z @ 0x00077DC0
// sp-match: ?sub_77DC0@type_77D30@@QAE_NHPAPAX0@Z @ 0x000629E0
bool type_77D30::sub_77DC0(RwInt32 arg_0, void **arg_4, void **arg_8)
{
    type_77D30_28 *var_4;
    RwInt32 v8;
    type_77D30_28 *varC;

    var_4 = 0;
    v8 = arg_0 & unk_1C;
    varC = unk_28[v8];
    while (varC != 0) {
        if (varC->unk_00 == arg_0) {
            var_4 = varC;
            break;
        }
        varC = varC->unk_24;
    }
    if (var_4 != 0) {
        if (arg_4 != 0)
            *arg_4 = var_4->unk_28;
        if (arg_8 != 0)
            *arg_8 = var_4->unk_2C;
        return true;
    }
    return false;
}

// The frames of every animation read so far (sub_77E40 adds each one's).
extern RwInt32 dword_449C9C;

// match: ?sub_77E40@@YAPAUtype_77D30@@PAURwStream@@PAXI@Z @ 0x00077E40
// sp-match: ?sub_77E40@@YAPAUtype_77D30@@PAURwStream@@PAXI@Z @ 0x00062B40
// Reads a set ('ADST' chunk 0x42A1) from the stream arg_0 into the bank
// memory arg_4 of arg_8 bytes (the heap when arg_4 is 0): two words for
// unk_0C and unk_10 around the animations' count, then each animation
// (chunk 1): its name, its header and frames (built in the bank's memory or
// on the heap, their shared tracks resolved against the earlier ones) and
// its events; 0 when the chunk is not a set or the memory runs out.
type_77D30 *sub_77E40(RwStream *arg_0, void *arg_4, RwUInt32 arg_8)
{
    void *local_1080;
    type_7FFD0 o107c;
    RwInt32 frm_1064[2];
    RwInt32 fp_105c;
    RwChar local_1058[0x20];
    RwInt16 l1034;
    RtAnimAnimation *q1030;
    type_783F0 *l102c;
    RwInt32 y1028;
    RwInt32 o1024;
    RwInt32 fp_1020;
    RwChunkHeaderInfo ebp_101c;
    RwInt32 ebp_1008;
    type_77D30 *ebp_1004;
    type_7CBD0_hdr *ebp_1000[0x400];

    ebp_1004 = new ((RwUInt8 *)arg_4, arg_8) type_77D30;
    RwStreamReadChunkHeaderInfo(arg_0, &ebp_101c);
    if (ebp_101c.type != 0x42A1) {
        if (arg_4 == 0)
            delete ebp_1004;
        return 0;
    }
    RwStreamReadInt32(arg_0, &fp_1020, 4);
    RwStreamReadInt32(arg_0, &o1024, 4);
    RwStreamReadInt32(arg_0, &y1028, 4);
    for (ebp_1008 = 0; ebp_1008 < o1024; ebp_1008++) {
        RwStreamReadChunkHeaderInfo(arg_0, &ebp_101c);
        if (ebp_101c.type == 1) {
            l102c = 0;
            RwStreamRead(arg_0, local_1058, 0x20);
            RwStreamReadInt32(arg_0, frm_1064, 8);
            RwStreamReadChunkHeaderInfo(arg_0, &ebp_101c);
            sub_7FFD0(arg_0, &o107c);
            dword_449C9C += o107c.unk_04;
            if (ebp_1004->unk_24 != 0) {
                local_1080 = ebp_1004->sub_78370(sub_7FEF0(0, o107c.unk_08, 0));
                if (local_1080 == 0)
                    return 0;
                q1030 = sub_7FF20(local_1080, o107c.unk_00, o107c.unk_04, o107c.unk_10, o107c.unk_14,
                                    o107c.unk_08, o107c.unk_0C);
            } else
                q1030 = sub_7FE60(o107c.unk_00, o107c.unk_04, o107c.unk_10, o107c.unk_14, o107c.unk_08,
                                    o107c.unk_0C);
            sub_802D0(arg_0, q1030, o107c.unk_08, o107c.unk_0C);
            ebp_1000[ebp_1008] = (type_7CBD0_hdr *)q1030->pFrames;
            sub_801C0(q1030, ebp_1000, ebp_1008);
            RwStreamReadInt32(arg_0, &fp_105c, 4);
#ifdef CODFH_SP // shape: SP 0x62B40 retains the signed count across the bank-size test.
            const RwInt32 &count = (RwInt16)fp_105c;
            RwUInt32 has = ebp_1004->unk_24;
            fp_105c = count;
            if (has) {
#else // MP 0x77E40
            l1034 = (RwInt16)fp_105c;
            fp_105c = l1034;
            if (ebp_1004->unk_24 != 0) {
#endif
                if (fp_105c != 0) {
                    l102c = (type_783F0 *)ebp_1004->sub_78370(sub_78670(fp_105c));
                    if (l102c == 0)
                        return 0;
                    sub_783F0(arg_0, l102c, fp_105c);
                }
            } else
                l102c = sub_784D0(arg_0, fp_105c);
            if (!ebp_1004->sub_78260(local_1058, q1030, (RwUInt8 *)l102c))
                return 0;
        }
    }
    ebp_1004->set_unk_0C(fp_1020);
    ebp_1004->set_unk_10(y1028);
    return ebp_1004;
}

// match: ?sub_78260@type_77D30@@QAE_NPBDPAXPAE@Z @ 0x00078260
// sp-match: ?sub_78260@type_77D30@@QAE_NPBDPAXPAE@Z @ 0x00062A60
bool type_77D30::sub_78260(const RwChar *Source, void *arg_4, RwUInt8 *arg_8)
{
    RwChar *var_4;
    RwInt32 v8;
    type_77D30_28 *stk_C;
    RwUInt32 var_10;
    RwChar ebp_34[0x20];

    strncpy(ebp_34, Source, 31);
    ebp_34[31] = 0;
    var_4 = strchr(ebp_34, '.');
    if (var_4 != 0)
        *var_4 = 0;
    _strupr(ebp_34);
    var_10 = sub_16C800(ebp_34, 0x811C9DC5);
    v8 = var_10 & unk_1C;
    if (unk_24 != 0)
        stk_C = (type_77D30_28 *)sub_78370(0x30);
    else
        stk_C = new type_77D30_28;
    if (stk_C == 0) {
        unk_28[v8] = 0;
        return false;
    }
    strncpy(stk_C->unk_04, ebp_34, 32);
    stk_C->unk_00 = var_10;
    stk_C->unk_28 = arg_4;
    stk_C->unk_2C = arg_8;
    stk_C->unk_24 = unk_28[v8];
    unk_28[v8] = stk_C;
    return true;
}

// match: ?sub_78370@type_77D30@@QAEPAXI@Z @ 0x00078370
// sp-match: ?sub_78370@type_77D30@@QAEPAXI@Z @ 0x00062A20
void *type_77D30::sub_78370(RwUInt32 arg_0)
{
    RwUInt32 var_4;
    RwUInt8 *local_8;

    var_4 = (((RwUInt32)unk_20 + arg_0 + 3) & ~3) - (RwUInt32)unk_20;
    if (unk_20 - &unk_00 + var_4 < unk_24) {
        local_8 = unk_20;
        unk_20 += var_4;
        unk_14 = unk_20 - &unk_00;
    } else {
#ifndef CODFH_SP
        // single player compiles the debug print out (SP 0x62A20)
        sub_19A750("Out of animation bank memory!");
#endif
        local_8 = 0;
    }
    return local_8;
}

// match: ?sub_783F0@@YAPAUtype_783F0@@PAURwStream@@PAU1@I@Z @ 0x000783F0
// sp-match: ?sub_783F0@@YAPAUtype_783F0@@PAURwStream@@PAU1@I@Z @ 0x00062DE0
// Reads arg_8 events from the stream arg_0 into arg_4.
type_783F0 *sub_783F0(RwStream *arg_0, type_783F0 *arg_4, RwUInt32 arg_8)
{
    RwUInt32 var_4;
    type_783F0 *v8;
    RwInt16 varC;

    v8 = arg_4;
    if (arg_8 == 0)
        return 0;
    v8->unk_00 = arg_8;
    for (var_4 = 0; var_4 < (RwUInt32)v8->unk_00; var_4++) {
        v8->unk_04[var_4].unk_00 = 0;
        if (!RwStreamReadInt16(arg_0, (RwInt16 *)&v8->unk_04[var_4].unk_00, 2))
            return 0;
        if (!RwStreamReadInt16(arg_0, &varC, 2))
            return 0;
        v8->unk_04[var_4].unk_04 = varC / 120.0f;
        if (!RwStreamReadInt16(arg_0, (RwInt16 *)&v8->unk_04[var_4].unk_08, 16))
            return 0;
    }
    return v8;
}

// match: ?sub_784D0@@YAPAUtype_783F0@@PAURwStream@@I@Z @ 0x000784D0
// sp-match: ?sub_784D0@@YAPAUtype_783F0@@PAURwStream@@I@Z @ 0x00062E70
type_783F0 *sub_784D0(RwStream *arg_0, RwUInt32 arg_4)
{
    RwUInt32 var_4;
    type_783F0 *local_8;

    if (arg_4 == 0)
        return 0;
    var_4 = arg_4 != 0 ? arg_4 - 1 : 0;
    local_8 = (type_783F0 *)RwMalloc(var_4 * sizeof(type_783F0_04) + sizeof(type_783F0),
                                       0x34251); // not an address: an allocation tag
    if (!sub_783F0(arg_0, local_8, arg_4)) {
        RwFree(local_8);
        return 0;
    }
    return local_8;
}

// match: ?sub_78550@type_783F0@@QAEPAUtype_783F0_04@@MH@Z @ 0x00078550
// sp-match: ?sub_78550@type_783F0@@QAEPAUtype_783F0_04@@MH@Z @ 0x00062EC0
type_783F0_04 *type_783F0::sub_78550(RwReal arg_0, RwInt32 arg_4)
{
    RwUInt32 var_4;

    for (var_4 = 0; var_4 < (RwUInt32)unk_00; var_4++) {
        if (unk_04[var_4].unk_04 >= arg_0 && (arg_4 == -1 || arg_4 == unk_04[var_4].unk_00))
            return &unk_04[var_4];
    }
    return 0;
}

// match: ?sub_785C0@type_783F0@@QAEPAUtype_783F0_04@@PAU2@H@Z @ 0x000785C0
// sp-match: ?sub_785C0@type_783F0@@QAEPAUtype_783F0_04@@PAU2@H@Z @ 0x00062F10
type_783F0_04 *type_783F0::sub_785C0(type_783F0_04 *arg_0, RwInt32 arg_4)
{
    RwUInt32 var_4;
    type_783F0_04 *v8;
    RwInt32 stk_C;
    RwUInt32 var_10;

    v8 = 0;
    var_10 = (RwUInt8 *)arg_0 - (RwUInt8 *)unk_04;
    stk_C = var_10 / sizeof(type_783F0_04);
    if (arg_4 == -1) {
        stk_C++;
        if (stk_C < unk_00)
            v8 = &unk_04[stk_C];
    } else {
        for (var_4 = stk_C + 1; var_4 < (RwUInt32)unk_00; var_4++) {
            if (unk_04[var_4].unk_00 == arg_4)
                v8 = &unk_04[var_4];
        }
    }
    return v8;
}

// match: ?sub_78670@@YAIH@Z @ 0x00078670
// sp-match: ?sub_78670@@YAIH@Z @ 0x00062F70
// The size of an event list of arg_0 events.
RwUInt32 sub_78670(RwInt32 arg_0)
{
    RwInt32 var_4;

    if ((var_4 = arg_0 - 1) < 0)
        var_4 = 0;
    return var_4 * sizeof(type_783F0_04) + sizeof(type_783F0);
}

// match: ?sub_786A0@@YAXXZ @ 0x000786A0
// sp-match: ?sub_786A0@@YAXXZ @ 0x00063160
// Sets the animation system up: its parts, the three player pools and the
// players' handle table.
void sub_786A0()
{
    RwInt32 var_4;

    sub_7DE10();
    sub_7FC90();
    for (var_4 = 0; var_4 < 3; var_4++)
        byte_44A508[var_4].sub_78BB0(var_4, dword_428BEC[var_4].unk_00, dword_428BEC[var_4].unk_04);
    sub_79260();
    sub_7A410(-1, sub_78D10);
    sub_7A4E0(sub_134320);
    sub_7A4E0(sub_150350);
    sub_7A4E0(sub_155D30);
    sub_7A4E0(sub_17F620);
    sub_7A4E0(sub_181140);
    sub_7A4E0(sub_16B0C0);
    dword_428C0C = 1;
    memset(dword_449CA0, 0, sizeof(dword_449CA0));
    dword_44A504 = 0;
}

// match: ?sub_78790@@YAXXZ @ 0x00078790
// sp-match: ?sub_78790@@YAXXZ @ 0x00063210
void sub_78790()
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 3; var_4++)
        byte_44A508[var_4].sub_78C00();
    dword_428C0C = 1;
    memset(dword_449CA0, 0, sizeof(dword_449CA0));
    dword_44A504 = 0;
    sub_31DB0();
}

// match: ?sub_787F0@@YAXXZ @ 0x000787F0
// sp-match: ?sub_787F0@@YAXXZ @ 0x00063250
void sub_787F0()
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 3; var_4++)
        byte_44A508[var_4].sub_78C30();
    sub_79260();
    sub_7FD10();
}

// match: ?sub_78830@@YAIH@Z @ 0x00078830
// sp-match: ?sub_78830@@YAIH@Z @ 0x00063280
RwUInt32 sub_78830(RwInt32 arg_0)
{
    void *var_4;
    RwUInt32 local_8;

    var_4 = byte_44A508[arg_0].sub_78C50();
    local_8 = sub_789A0(var_4, arg_0);
    return local_8;
}

// match: ?sub_78870@@YAXH@Z @ 0x00078870
// sp-match: ?sub_78870@@YAXH@Z @ 0x000632A0
void sub_78870(RwInt32 arg_0)
{
    type_788C0 *var_4;

    var_4 = (type_788C0 *)sub_78AC0(arg_0);
    if (var_4 != 0) {
        byte_44A508[var_4->unk_10].sub_78CC0((type_7C8D0 *)var_4);
        sub_78A80(arg_0);
    }
}

// match: ?sub_788C0@@YA_NH_N@Z @ 0x000788C0
// sp-match: ?sub_788C0@@YA_NH_N@Z @ 0x000632E0
// Whether a player plays the animation arg_0 (holding it on unload when
// arg_4 is set).
bool sub_788C0(RwInt32 arg_0, bool arg_4)
{
    RwUInt32 var_4;
    RwInt32 v8;
    type_788C0 *varC;

    for (v8 = 1; v8 < dword_449CA0_count; v8++) {
        if (dword_449CA0[v8].unk_08 != 0) {
            varC = (type_788C0 *)sub_78AC0(dword_449CA0[v8].unk_04);
            if (varC != 0) {
                for (var_4 = 0; var_4 < varC->unk_2C; var_4++) {
                    if (varC->unk_30[var_4].unk_1C != 0 && varC->unk_30[var_4].unk_08 == arg_0) {
                        if (arg_4)
                            varC->unk_30[var_4].unk_0C |= 0x20;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

// match: ?sub_789A0@@YAIPAXH@Z @ 0x000789A0
// sp-match: ?sub_789A0@@YAIPAXH@Z @ 0x00062F90
// Registers the player arg_0 of the pool arg_4 under a new handle.
RwUInt32 sub_789A0(void *arg_0, RwInt32 arg_4)
{
    RwInt32 var_4;
    type_439E78_00 v8;
    RwInt32 varC;

    var_4 = 0;
    if (dword_428C0C == 0)
        dword_428C0C = 1;
    for (varC = 1; varC < dword_449CA0_count; varC++) {
        if (dword_449CA0[varC].unk_04 == 0 && dword_449CA0[varC].unk_08 == 0) {
            v8.unk_00 = (RwUInt16)varC;
            v8.unk_02 = (RwUInt16)dword_428C0C;
            dword_449CA0[v8.unk_00].unk_04_h.unk_00 = v8.unk_00;
            dword_449CA0[v8.unk_00].unk_04_h.unk_02 = v8.unk_02;
            dword_449CA0[v8.unk_00].unk_08 = arg_0;
            dword_449CA0[v8.unk_00].unk_00 = arg_4;
            var_4 = 1;
            dword_428C0C++;
            break;
        }
    }
    return *(RwUInt32 *)&v8;
}

// match: ?sub_78A80@@YAXI@Z @ 0x00078A80
// sp-match: ?sub_78A80@@YAXI@Z @ 0x00063020
void sub_78A80(RwUInt32 arg_0)
{
    dword_449CA0[(RwUInt16)arg_0].unk_04 = 0;
    dword_449CA0[(RwUInt16)arg_0].unk_08 = 0;
    dword_449CA0[(RwUInt16)arg_0].unk_00 = 0;
}

// match: ?sub_78AC0@@YAPAUtype_78AC0@@H@Z @ 0x00078AC0
// sp-match: ?sub_78AC0@@YAPAUtype_78AC0@@H@Z @ 0x00063040
type_78AC0 *sub_78AC0(RwInt32 arg_0)
{
    if (dword_449CA0[(RwUInt16)arg_0].unk_04 == (RwUInt32)arg_0)
        return (type_78AC0 *)dword_449CA0[(RwUInt16)arg_0].unk_08;
    return 0;
}
