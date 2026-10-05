// The GodAsset manager (game/godassetmanager.h): the objects by key, the
// requests to read them, and the pools their memory comes from.

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "game/godassetmanager.h"
#include "game/functions.h"
#include "game/gameloop.h"
#include "rws/gftime.h"
#include "types/type_141C10.h"
#include "types/type_72810.h"
#include "types/soundbank.h"
#include "types/musicplayer.h"
#include "rw/bastream.h"
#include <stdio.h>
#include <string.h>

// Its data definitions (PLAN M5), in the image's address order.
// 0x003DFFB0
extern const RwReal flt_3DFFB0 = 16.666666f;
// 0x0042B6E4
type_42B6E4 dword_42B6E4[6] = {
    { 2000, 20 },
    { 2600, 28 },
    { 850, 36 },
    { 2050, 52 },
    { 850, 72 },
    { 175, -1 },
};
// 0x004F24E8
RwUInt32 dword_4F24E8[0x3C];
// 0x004F25D8
RwUInt32 dword_4F25D8;
// 0x004F25E0
RwUInt32 dword_4F25E0[0x3C];
// 0x004F26D0
RwInt32 dword_4F26D0;
// End of its data definitions.


// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).
type_16C2A0 dword_4F2708;
type_16C2A0 dword_4F27A0[6];
type_16C2A0 dword_4F277C;
type_16C2A0 dword_4F275C;
alfahash dword_4F2728;
alfahash dword_4F26D4;
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3DFFB0@@3MB @ 0x003DFFB0
// match: ??_C@_0BD@BGNDJJJK@GodAssetStringPool?$AA@ @ 0x003DFFB4
// match: ??_C@_0CM@DLFJIPEN@?5?5GodAssetManager?3?3?5m_requestPoo@ @ 0x003DFFC8
// match: ??_C@_0O@HFHJHNLF@m_requestPool?$AA@ @ 0x003DFFF4
// match: ??_C@_0P@OGGPGPOA@m_fileInfoPool?$AA@ @ 0x003E0004
// match: ??_C@_0DG@KAIGKLGA@?5?5GodAssetManager?3?3?5m_freeGodAss@ @ 0x003E0014
// match: ??_C@_0BI@BEMMBEIK@m_freeGodAssetPools?$FL?$CFd?$FN?$AA@ @ 0x003E004C
// match: ??_C@_0CM@JHBNBOEO@?5?5GodAssetManager?3?3?5Largest?5Asse@ @ 0x003E0064
// match: ??_C@_0DH@LMLJPNFA@GodAssetManager?3?3?5m_requestPool?5@ @ 0x003E0090
// match: ??_C@_06GFAEKDNI@?$CFx?0?5?$CFx?$AA@ @ 0x003E00C8
// match: __ehhandler$?sub_198710@@YAPAUtype_199010@@PAUtype_3DF8D8_04@@@Z>1>8 @ 0x0041E740
// match: __ehhandler$?sub_198710@@YAPAUtype_199010@@PAUtype_3DF8D8_04@@@Z>1 @ 0x0041E748
// match: __ehhandler$?sub_198800@@YAPAUtype_3DF8D8@@PAUtype_3DF8D8_04@@@Z>1>8 @ 0x0041E764
// match: __ehhandler$?sub_198800@@YAPAUtype_3DF8D8@@PAUtype_3DF8D8_04@@@Z>1 @ 0x0041E76C
// match: __ehhandler$?sub_198880@@YAPAUtype_3DF8D8@@PBD@Z>1>8 @ 0x0041E788
// match: __ehhandler$?sub_198880@@YAPAUtype_3DF8D8@@PBD@Z>1 @ 0x0041E790
// match: __ehhandler$?sub_199010@@YAPAUtype_199010@@PAUtype_3DF8D8_04@@H@Z>1>8 @ 0x0041E7AC
// match: __ehhandler$?sub_199010@@YAPAUtype_199010@@PAUtype_3DF8D8_04@@H@Z>1 @ 0x0041E964
// match: .CRT$XCU+0 @ 0x0042717C
// match: .CRT$XCU+4 @ 0x00427180
// match: .CRT$XCU+8 @ 0x00427184
// match: .CRT$XCU+12 @ 0x00427188
// match: .CRT$XCU+16 @ 0x0042718C
// match: .CRT$XCU+20 @ 0x00427190
// match: ?dword_42B6E4@@3PAUtype_42B6E4@@A @ 0x0042B6E4

// match: _$E1 @ 0x0030BFE0
// match: _$E2 @ 0x0030E9A0
// match: _$E4 @ 0x0030C000
// match: _$E5 @ 0x0030E9B0
// match: _$E7 @ 0x0030C030
// match: _$E8 @ 0x0030E9D0
// match: _$E10 @ 0x0030C050
// match: _$E11 @ 0x0030E9E0
// match: _$E13 @ 0x0030C070
// match: _$E14 @ 0x0030E9F0
// match: _$E16 @ 0x0030C090
// match: _$E17 @ 0x0030EA00

void sub_198F00(type_3DF8D8_04 *arg_0);
RwInt32 sub_18F750();
RwInt32 sub_18F710(RwInt32 arg_0);
RwUInt32 sub_16C800(const RwChar *arg_0, RwUInt32 arg_4);
struct RwStream;
struct type_3DF8D8_ev;
void sub_198C70(RwStream *arg_0, type_3DF8D8_ev *arg_4);
void sub_198D30(RwStream *arg_0, type_3DF8D8_ev *arg_4);
void sub_198F40(type_3DF8D8_base *arg_0);
RwInt32 sub_198FC0(type_4F26D0 *arg_0);
struct type_3DF8D8_base;
RwInt32 sub_198FE0(type_3DF8D8_base *arg_0);
void sub_19A7D0(type_4F26D0 *arg_0);
RwUInt32 sub_19A980(void *arg_0);
bool sub_19A9A0(void *arg_0, void *arg_4);
RwUInt32 sub_19AA00(void *arg_0);
bool sub_19AA20(void *arg_0, void *arg_4);
struct type_3DF8D8_04;
RwInt32 sub_198770(type_3DF8D8_04 *arg_0);
type_4F26D0 *sub_1987A0(type_3DF8D8_04 *arg_0);
type_3DF8D8_base *sub_198900(type_3DF8D8_04 *arg_0, RwInt32 arg_4, void (*arg_8)(RwInt32, RwInt32, RwInt32),
                             RwInt32 arg_C, RwInt32 arg_10, RwInt32 arg_14);
void sub_19A760(type_3DF8D8_base *arg_0, void (*arg_4)(RwInt32, RwInt32, RwInt32), RwInt32 arg_8, RwInt32 arg_C);

// match: ?sub_198390@@YAXXZ @ 0x00198390
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Sets the manager up: m_freeGodAssetPools (the last sized for the largest
// asset), m_fileInfoPool, m_requestPool, the two tables and the string pool.
void sub_198390()
{
    RwChar var_30[0x20];
    RwInt32 var_C;
    RwInt32 bp_8;
    RwInt32 bp_4;

    dword_4F26D0 = 0;
    bp_8 = sub_18F750();
    sub_19A750("  GodAssetManager:: Largest Asset size: %d\n", bp_8);
    bp_4 = 0;
    for (var_C = 0; var_C < 6; var_C++)
    {
        if (dword_42B6E4[var_C].unk_04 < 0)
            dword_42B6E4[var_C].unk_04 = bp_8;
        sprintf(var_30, "m_freeGodAssetPools[%d]", var_C);
        dword_4F27A0[var_C].sub_16C2C0(dword_42B6E4[var_C].unk_00, dword_42B6E4[var_C].unk_04, var_30, 4, 0);
        sub_19A750("  GodAssetManager:: m_freeGodAssetPools[%d] alloc %d\n", var_C,
                   dword_42B6E4[var_C].unk_00 * dword_42B6E4[var_C].unk_04);
        bp_4 += dword_42B6E4[var_C].unk_00;
    }
    dword_4F277C.sub_16C2C0(0x12C, 0xC, "m_fileInfoPool", 4, 0);
    dword_4F2708.sub_16C2C0(0x2328, 0x18, "m_requestPool", 4, 0);
    sub_19A750("  GodAssetManager:: m_requestPool alloc %d\n", 0x2328 * 0x18);
    dword_4F2728.sub_67730(bp_4, bp_4 / 4, sub_19A980, sub_19A9A0);
    dword_4F26D4.sub_67730(0x12C, 0x64, sub_19AA00, sub_19AA20);
    dword_4F275C.sub_16C2C0(0x28, 0x100, "GodAssetStringPool", 4, 0);
    dword_4F25D8 = RWS::Time::GetTime();
    {
        RwInt32 var_34;

        for (var_34 = 0; var_34 < 0x3C; var_34++)
        {
            dword_4F25E0[var_34] = 0;
            dword_4F24E8[var_34] = 0;
        }
    }
}

// match: ?sub_198570@@YAXXZ @ 0x00198570
// Notes when the manager was set up.
void sub_198570()
{
    dword_4F25D8 = RWS::Time::GetTime();
}

// match: ?sub_198580@@YAXXZ @ 0x00198580
// Shuts the manager down: every object's registration freed, the requests,
// tables and pools.
void sub_198580()
{
    RwInt32 var_4;

    dword_4F2728.sub_67AA0(sub_1986F0);
    dword_4F26D0 = 0;
    dword_4F2708.sub_16C4D0(0);
    for (var_4 = 0; var_4 < 6; var_4++)
        dword_4F27A0[var_4].sub_16C4D0(1);
    dword_4F277C.sub_16C4D0(0);
    dword_4F2728.sub_67780();
    dword_4F26D4.sub_67780();
    dword_4F275C.sub_16C4D0(1);
}

// match: ?sub_198610@@YAXXZ @ 0x00198610
// At the game's start: m_requestPool again, for 50 requests.
void sub_198610()
{
    dword_4F2708.sub_16C4D0(1);
    dword_4F2708.sub_16C2C0(0x32, 0x18, "m_requestPool", 4, 0);
    sub_19A750("GodAssetManager:: m_requestPool alloc at GameStart %d\n", 0x2328 * 0x18);
}

// match: ?sub_198650@@YAMXZ @ 0x00198650
RwReal sub_198650()
{
    return 0.0f;
}

// match: ?sub_198660@@YAXPAUtype_198660@@@Z @ 0x00198660
// The key of the first object waiting to be read into *arg_0 (0 for none).
void sub_198660(type_198660 *arg_0)
{
    if (arg_0)
    {
        if (dword_4F26D0)
        {
            arg_0->unk_00 = ((type_4F26D0 *)dword_4F26D0)->unk_00->unk_04.unk_00;
            arg_0->unk_04 = ((type_4F26D0 *)dword_4F26D0)->unk_00->unk_04.unk_04;
        }
        else
        {
            arg_0->unk_00 = 0;
            arg_0->unk_04 = 0;
        }
    }
}

// match: ?sub_1986B0@@YAPADXZ @ 0x001986B0
// A string buffer from GodAssetStringPool.
RwChar *sub_1986B0()
{
    return (RwChar *)dword_4F275C.sub_16C5A0(0);
}

// match: ?sub_1986D0@@YAXPAD@Z @ 0x001986D0
void sub_1986D0(RwChar *arg_0)
{
    dword_4F275C.sub_16C710(arg_0);
}

// match: ?sub_1986F0@@YA_NPAX@Z @ 0x001986F0
bool sub_1986F0(void *arg_0)
{
    type_3DF8D8_base *var_4;

    var_4 = (type_3DF8D8_base *)arg_0;
    sub_198F00(&var_4->unk_04);
    return true;
}

// match: ?sub_198710@@YAPAUtype_199010@@PAUtype_3DF8D8_04@@@Z @ 0x00198710
// match: __ehhandler$?sub_198710@@YAPAUtype_199010@@PAUtype_3DF8D8_04@@@Z-8 @ 0x00302360
// match: __ehhandler$?sub_198710@@YAPAUtype_199010@@PAUtype_3DF8D8_04@@@Z @ 0x00302368
// The object with the key *arg_0 (through a key object of its own), or 0.
type_199010 *sub_198710(type_3DF8D8_04 *arg_0)
{
    type_3DF8D8_base var_1C(*arg_0);

    return (type_199010 *)dword_4F2728.sub_67970(&var_1C);
}

// match: ?sub_198770@@YAHPAUtype_3DF8D8_04@@@Z @ 0x00198770
// The object a request for *arg_0 is waiting to read, or 0.
RwInt32 sub_198770(type_3DF8D8_04 *arg_0)
{
    type_4F26D0 *var_4;

    var_4 = sub_1987A0(arg_0);
    if (var_4)
        return (RwInt32)var_4->unk_00;
    return 0;
}

// match: ?sub_1987A0@@YAPAUtype_4F26D0@@PAUtype_3DF8D8_04@@@Z @ 0x001987A0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The request for the key *arg_0, or 0.
type_4F26D0 *sub_1987A0(type_3DF8D8_04 *arg_0)
{
    type_3DF8D8_04 *var_8;
    type_4F26D0 *l4;

    for (l4 = (type_4F26D0 *)dword_4F26D0; l4; l4 = l4->unk_08)
    {
        var_8 = &l4->unk_00->unk_04;
        if (arg_0->unk_00 == var_8->unk_00 && arg_0->unk_04 == var_8->unk_04)
            return l4;
    }
    return 0;
}

// match: ?sub_198800@@YAPAUtype_3DF8D8@@PAUtype_3DF8D8_04@@@Z @ 0x00198800
type_3DF8D8 *sub_198800(type_3DF8D8_04 *arg_0)
{
    if (arg_0->unk_00 == 0 && arg_0->unk_04 == 0)
        return 0;
    type_3DF8D8_base var_1C(*arg_0);

    return (type_3DF8D8 *)dword_4F2728.sub_67970(&var_1C);
}

// match: ?sub_198880@@YAPAUtype_3DF8D8@@PBD@Z @ 0x00198880
// match: __ehhandler$?sub_198880@@YAPAUtype_3DF8D8@@PBD@Z-8 @ 0x00302380
// match: __ehhandler$?sub_198880@@YAPAUtype_3DF8D8@@PBD@Z @ 0x00302388
// The object named arg_0 (its key hashed from the name, sub_198A20).
type_3DF8D8 *sub_198880(const RwChar *arg_0)
{
    type_3DF8D8_04 var_14;

    sub_198A20(arg_0, &var_14);
    type_3DF8D8_base var_24(var_14);

    return (type_3DF8D8 *)dword_4F2728.sub_67970(&var_24);
}

// match: ?sub_198900@@YAPAUtype_3DF8D8_base@@PAUtype_3DF8D8_04@@HP6AXHHH@ZHHH@Z @ 0x00198900
// Asks for the object with the key *arg_0 (of the kind arg_4): an object
// already read is handed to the callback arg_8 (with arg_C and arg_10) or
// marked wanted; one waiting to be read is marked wanted; else it is made
// (sub_199010) and the request queued (sub_19A760). 0 for a zero key.
type_3DF8D8_base *sub_198900(type_3DF8D8_04 *arg_0, RwInt32 arg_4, void (*arg_8)(RwInt32, RwInt32, RwInt32),
                             RwInt32 arg_C, RwInt32 arg_10, RwInt32 arg_14)
{
    bool var_1;
    type_3DF8D8_base *var_8;

    if (arg_0->unk_00 == 0 && arg_0->unk_04 == 0)
        return 0;
    var_8 = (type_3DF8D8_base *)sub_198710(arg_0);
    if (var_8)
    {
        if (arg_8)
            arg_8((RwInt32)var_8, arg_C, arg_10);
        else
            var_8->unk_0E = 1;
        return var_8;
    }
    var_8 = (type_3DF8D8_base *)sub_198770(arg_0);
    var_1 = var_8 != 0;
    if (var_1 && !arg_8)
    {
        var_8->unk_0E = 1;
        return var_8;
    }
    if (!var_8)
        var_8 = (type_3DF8D8_base *)sub_199010(arg_0, arg_4);
    sub_19A760(var_8, arg_8, arg_C, arg_10);
    return var_8;
}

// match: ?sub_1989D0@@YAPAUtype_1989D0@@PBDHHHH@Z @ 0x001989D0
// The same for the object named arg_0.
type_1989D0 *sub_1989D0(const RwChar *arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C, RwInt32 arg_10)
{
    type_3DF8D8_04 var_8;

    sub_198A20(arg_0, &var_8);
    return (type_1989D0 *)sub_198900(&var_8, arg_4, (void (*)(RwInt32, RwInt32, RwInt32))arg_8, arg_C, arg_10, 0);
}

// match: ?sub_198A20@@YAXPBDPAUtype_3DF8D8_04@@@Z @ 0x00198A20
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The key of the name arg_0: the name quoted (and each '+' in it), upper-
// cased, and its odd and even characters hashed apart (FNV-1).
void sub_198A20(const RwChar *arg_0, type_3DF8D8_04 *arg_4)
{
    RwChar var_818[0x400];
    RwChar *var_414;
    const RwChar *l410;
    RwChar *local_40C;
    RwChar var408[0x400];
    RwChar *l4;

    l410 = arg_0;
    local_40C = var_818;
    *local_40C = '"';
    local_40C++;
    while (l410 && *l410)
    {
        if (*l410 == '+')
        {
            *local_40C = '"';
            local_40C++;
            *local_40C = *l410;
            local_40C++;
            *local_40C = '"';
            local_40C++;
        }
        else
        {
            *local_40C = *l410;
            local_40C++;
        }
        l410++;
    }
    *local_40C = '"';
    local_40C[1] = 0;
    var_414 = &var_818[1];
    l4 = var408;
    _strupr(var_818);
    while (*var_414 && var_414[1])
    {
        *l4 = *var_414;
        l4++;
        var_414 += 2;
    }
    if (*var_414)
    {
        *l4 = *var_414;
        l4++;
    }
    *l4 = 0;
    var_414 = var_818;
    l4 = var_818;
    while (*var_414 && var_414[1])
    {
        *l4 = *var_414;
        l4++;
        var_414 += 2;
    }
    if (*var_414)
    {
        *l4 = *var_414;
        l4++;
    }
    *l4 = 0;
    arg_4->unk_00 = sub_16C800(var_818, 0x811C9DC5);
    arg_4->unk_04 = sub_16C800(var408, 0x811C9DC5);
}

// match: ?sub_198C70@@YAXPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00198C70
// Reads an object from the stream, then the others its header counts
// (each with a header of its own).
void sub_198C70(RwStream *arg_0, type_3DF8D8_ev *arg_4)
{
    RwInt32 var_4;

    var_4 = get_ref_low(arg_4->unk_0C.unk_00, 0x1FF, 0xC, 0xC);
    if (var_4 > 1)
    {
        sub_198D30(arg_0, arg_4);
        var_4--;
        while (var_4)
        {
            type_3DF8D8_ev var_20;

            RwStreamRead(arg_0, &var_20, 0x1C);
            sub_198C70(arg_0, &var_20);
            var_4--;
        }
    }
    else
        sub_198D30(arg_0, arg_4);
}

// match: ?sub_198D30@@YAXPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00198D30
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Reads one object: skipped unless requested; else read by its handler,
// every request for it answered (the object marked wanted unless a callback
// says otherwise) and freed, and the object freed again if the read failed
// or nothing wants it.
void sub_198D30(RwStream *arg_0, type_3DF8D8_ev *arg_4)
{
    RwInt32 bp_A8;
    RwInt32 vA4;
    RwInt32 locA0;
    RwInt32 t9C;
    RwChar fp_98[0x80];
    type_4F26D0 *ebp_14;
    type_3DF8D8_base *lv_10;
    bool w9;
    type_73050 bp_8;

    bp_A8 = 0;
    t9C = get_ref_low(arg_4->unk_0C.unk_00, 0xFF, 4, 4);
    bp_8 = *(type_73050 *)&arg_4->unk_0C.unk_04;
    sprintf(fp_98, "%x, %x", bp_8.unk_00, bp_8.unk_04);
    if (!sub_198770((type_3DF8D8_04 *)&bp_8))
    {
        RwStreamSkip(arg_0, arg_4->unk_08 - 0x1C);
        return;
    }
    ebp_14 = sub_1987A0((type_3DF8D8_04 *)&bp_8);
    locA0 = ebp_14->unk_00->vf_000(arg_0, arg_4);
    lv_10 = ebp_14->unk_00;
    w9 = 0;
    do
    {
        if (sub_198FC0(ebp_14))
            w9 = 1;
        if (ebp_14->unk_04)
        {
            if (ebp_14->unk_04((RwInt32)ebp_14->unk_00, ebp_14->unk_10, ebp_14->unk_14))
                ebp_14->get_unk_00()->unk_0E = 1;
        }
        else
            ebp_14->get_unk_00()->unk_0E = 1;
        memset(ebp_14, 0, 0x18);
        dword_4F2708.sub_16C710(ebp_14);
        ebp_14 = sub_1987A0((type_3DF8D8_04 *)&bp_8);
    } while (ebp_14);
    if (!locA0 || !lv_10->unk_0E)
        sub_198F00((type_3DF8D8_04 *)&bp_8);
    vA4 = bp_A8;
}

// match: ?sub_198F00@@YAXPAUtype_3DF8D8_04@@@Z @ 0x00198F00
// Frees the object with the key *arg_0: out of the table, released
// (vf_004) and its memory back to its pool.
void sub_198F00(type_3DF8D8_04 *arg_0)
{
    type_3DF8D8 *var_4;

    var_4 = sub_198800(arg_0);
    dword_4F2728.sub_678C0(var_4);
    var_4->vf_004();
    sub_198F40(var_4);
}

// match: ?sub_198F40@@YAXPAUtype_3DF8D8_base@@@Z @ 0x00198F40
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Returns arg_0's memory to the pool it came from and counts one of its
// kind fewer.
void sub_198F40(type_3DF8D8_base *arg_0)
{
    RwUInt32 *var_8;
    RwInt32 l4;

    for (l4 = 0; l4 < 6; l4++)
    {
        if (dword_4F27A0[l4].sub_16C770(arg_0))
        {
            dword_4F27A0[l4].sub_16C710(arg_0);
            break;
        }
    }
    var_8 = &dword_4F25E0[arg_0->vf_008()];
    (*var_8)--;
}

// match: ?sub_198FC0@@YAHPAUtype_4F26D0@@@Z @ 0x00198FC0
// Takes the request out of the list and registers its object.
RwInt32 sub_198FC0(type_4F26D0 *arg_0)
{
    sub_19A7D0(arg_0);
    return sub_198FE0(arg_0->unk_00);
}

// match: ?sub_198FE0@@YAHPAUtype_3DF8D8_base@@@Z @ 0x00198FE0
// Registers arg_0 under its key unless an object has it: whether it did.
RwInt32 sub_198FE0(type_3DF8D8_base *arg_0)
{
    if (!sub_198710(&arg_0->unk_04))
    {
        dword_4F2728.sub_67850(arg_0);
        return 1;
    }
    return 0;
}

// match: ?sub_199010@@YAPAUtype_199010@@PAUtype_3DF8D8_04@@H@Z @ 0x00199010
// match: __ehhandler$?sub_199010@@YAPAUtype_199010@@PAUtype_3DF8D8_04@@H@Z-0x428 @ 0x003023A0
// match: __ehhandler$?sub_199010@@YAPAUtype_199010@@PAUtype_3DF8D8_04@@H@Z @ 0x003027C8
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Makes the object of the kind arg_4 with the key *arg_0: built in the first
// of m_freeGodAssetPools with room for the kind's size (sub_18F710) and a
// free element, and counted (dword_4F25E0, its peak in dword_4F24E8).
type_199010 *sub_199010(type_3DF8D8_04 *arg_0, RwInt32 arg_4)
{
    RwInt32 var_1C;
    type_3DF8D8_base *var_18;
    RwInt32 var_14;
    void *lv_10;

    lv_10 = 0;
    var_18 = 0;
    var_14 = sub_18F710(arg_4);
    for (var_1C = 0; var_1C < 6; var_1C++)
    {
        if (var_14 <= dword_42B6E4[var_1C].unk_04 && !dword_4F27A0[var_1C].sub_16C7E0())
        {
            lv_10 = dword_4F27A0[var_1C].sub_16C5A0(0);
            break;
        }
    }
    switch (arg_4)
    {
    case 1:
        var_18 = new (lv_10) type_3DF8E4(*arg_0);
        break;
    case 3:
        var_18 = new (lv_10) type_3DF9C4(*arg_0);
        break;
    case 4:
        var_18 = new (lv_10) type_3DFA64(*arg_0);
        break;
    case 5:
        var_18 = new (lv_10) type_3DFABC(*arg_0);
        break;
    case 26:
        var_18 = new (lv_10) type_3DFAC8(*arg_0);
        break;
    case 25:
        var_18 = new (lv_10) type_3DFC34(*arg_0);
        break;
    case 38:
        var_18 = new (lv_10) type_3DFE44(*arg_0);
        break;
    case 35:
        var_18 = new (lv_10) type_3DFE20(*arg_0);
        break;
    case 36:
        var_18 = new (lv_10) type_3DFE2C(*arg_0);
        break;
    case 37:
        var_18 = new (lv_10) type_3DFE38(*arg_0);
        break;
    case 27:
        var_18 = new (lv_10) type_3DFCA0(*arg_0);
        break;
    case 28:
        var_18 = new (lv_10) type_3DFD40(*arg_0);
        break;
    case 29:
        var_18 = new (lv_10) type_3DFDE4(*arg_0);
        break;
    case 30:
        var_18 = new (lv_10) type_3DFE50(*arg_0);
        break;
    case 31:
        var_18 = new (lv_10) type_3DFE64(*arg_0);
        break;
    case 32:
        var_18 = new (lv_10) type_3DFDFC(*arg_0);
        break;
    case 33:
        var_18 = new (lv_10) type_3DFE14(*arg_0);
        break;
    case 34:
        var_18 = new (lv_10) type_3DFE08(*arg_0);
        break;
    case 42:
        var_18 = new (lv_10) type_44E8D8_248(*arg_0);
        break;
    case 6:
        var_18 = new (lv_10) type_3DF8FC(*arg_0);
        break;
    case 7:
        var_18 = new (lv_10) type_3DF8F0(*arg_0);
        break;
    case 58:
        var_18 = new (lv_10) type_3DF9A0(*arg_0);
        break;
    case 8:
        var_18 = new (lv_10) type_3DF9AC(*arg_0, arg_4);
        break;
    case 9:
        var_18 = new (lv_10) type_3DF9B8(*arg_0);
        break;
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
        var_18 = new (lv_10) type_3DFAD4(*arg_0, arg_4);
        break;
    case 15:
        var_18 = new (lv_10) type_3DFAE0(*arg_0);
        break;
    case 16:
        var_18 = new (lv_10) type_3DFAEC(*arg_0);
        break;
    case 17:
        var_18 = new (lv_10) type_3DFAF8(*arg_0);
        break;
    case 18:
        var_18 = new (lv_10) type_3DFB04(*arg_0);
        break;
    case 20:
        var_18 = new (lv_10) type_3DFB10(*arg_0);
        break;
    case 19:
        var_18 = new (lv_10) type_3DFB1C(*arg_0);
        break;
    case 21:
        var_18 = new (lv_10) type_3DFB28(*arg_0);
        break;
    case 22:
        var_18 = new (lv_10) type_3DFB34(*arg_0);
        break;
    case 23:
        var_18 = new (lv_10) type_3DFB40(*arg_0);
        break;
    case 24:
        var_18 = new (lv_10) type_3DFB4C(*arg_0);
        break;
    case 39:
        var_18 = new (lv_10) type_3DFE70(*arg_0);
        break;
    case 40:
        var_18 = new (lv_10) type_3DFE7C(*arg_0);
        break;
    case 41:
        var_18 = new (lv_10) type_3DFE88(*arg_0);
        break;
    case 2:
        var_18 = new (lv_10) type_3DFE94(*arg_0);
        break;
    case 43:
        var_18 = new (lv_10) type_3DFEA4(*arg_0);
        break;
    case 46:
        var_18 = new (lv_10) type_3DFEB0_obj(*arg_0);
        break;
    case 44:
        var_18 = new (lv_10) type_3DFEEC_obj(*arg_0);
        break;
    case 45:
        var_18 = new (lv_10) type_3DFEC4_obj(*arg_0);
        break;
    case 47:
        var_18 = new (lv_10) type_3DFF00(*arg_0);
        break;
    case 48:
        var_18 = new (lv_10) type_3DFA58(*arg_0);
        break;
    case 49:
        var_18 = new (lv_10) type_3DFF0C(*arg_0);
        break;
    case 50:
        var_18 = new (lv_10) type_3DFF18(*arg_0);
        break;
    case 51:
        var_18 = new (lv_10) type_3DFF3C(*arg_0);
        break;
    case 52:
        var_18 = new (lv_10) type_3DFF5C(*arg_0);
        break;
    case 53:
        var_18 = new (lv_10) type_3DFF68(*arg_0);
        break;
    case 54:
        var_18 = new (lv_10) type_3DFF74(*arg_0);
        break;
    case 55:
        var_18 = new (lv_10) type_3DFF80(*arg_0);
        break;
    case 56:
        var_18 = new (lv_10) type_3DFF8C(*arg_0);
        break;
    case 57:
        var_18 = new (lv_10) type_3DFF98(*arg_0);
        break;
    case 59:
        var_18 = new (lv_10) type_3DFFA4(*arg_0);
        break;
    }
    dword_4F25E0[arg_4]++;
    if (dword_4F25E0[arg_4] > dword_4F24E8[arg_4])
        dword_4F24E8[arg_4] = dword_4F25E0[arg_4];
    return (type_199010 *)var_18;
}

// match: ?sub_19A750@@YAXPBDZZ @ 0x0019A750
// The debug print: empty in this build.
void sub_19A750(const RwChar *arg_0, ...)
{
}

// match: ?sub_19A760@@YAXPAUtype_3DF8D8_base@@P6AXHHH@ZHH@Z @ 0x0019A760
// Queues a request for arg_0 (the callback arg_4 with arg_8 and arg_C).
void sub_19A760(type_3DF8D8_base *arg_0, void (*arg_4)(RwInt32, RwInt32, RwInt32), RwInt32 arg_8, RwInt32 arg_C)
{
    type_4F26D0 *var_4;

    var_4 = (type_4F26D0 *)dword_4F2708.sub_16C5A0(0);
    var_4->unk_00 = arg_0;
    var_4->unk_0C = 0;
    var_4->unk_04 = (RwInt32 (*)(RwInt32, RwInt32, RwInt32))arg_4;
    var_4->unk_10 = arg_8;
    var_4->unk_14 = arg_C;
    if (dword_4F26D0)
        ((type_4F26D0 *)dword_4F26D0)->unk_0C = var_4;
    var_4->unk_08 = (type_4F26D0 *)dword_4F26D0;
    dword_4F26D0 = (RwInt32)var_4;
}

// match: ?sub_19A7D0@@YAXPAUtype_4F26D0@@@Z @ 0x0019A7D0
// Takes the request arg_0 out of the list.
void sub_19A7D0(type_4F26D0 *arg_0)
{
    if (arg_0->unk_0C)
        arg_0->unk_0C->unk_08 = arg_0->unk_08;
    else
        dword_4F26D0 = (RwInt32)arg_0->unk_08;
    if (arg_0->unk_08)
        arg_0->unk_08->unk_0C = arg_0->unk_0C;
    arg_0->unk_08 = 0;
    arg_0->unk_0C = 0;
}

// match: ?sub_19A830@@YAPAURpClump@@PAUtype_3DF8D8_ev@@PAU1@H@Z @ 0x0019A830
// Notes the clump arg_4 read for the header arg_0's file (with arg_8), when
// it has one; returns arg_4.
RpClump *sub_19A830(type_3DF8D8_ev *arg_0, RpClump *arg_4, RwInt32 arg_8)
{
    type_4F277C *var_4;

    if (arg_0->unk_18)
    {
        var_4 = (type_4F277C *)dword_4F277C.sub_16C5A0(0);
        var_4->unk_08 = (RwInt32)arg_4;
        var_4->unk_00 = (RwInt32)arg_0->unk_18;
        var_4->unk_04 = arg_8;
        if (!dword_4F26D4.sub_67850(var_4))
            dword_4F277C.sub_16C710(var_4);
    }
    return arg_4;
}

// match: ?sub_19A8A0@@YAXHHH@Z @ 0x0019A8A0
// Forgets the record arg_0, arg_4, arg_8.
void sub_19A8A0(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    type_4F277C var_C;

    if (arg_0)
    {
        var_C.unk_00 = arg_0;
        var_C.unk_04 = arg_4;
        var_C.unk_08 = arg_8;
        dword_4F26D4.sub_678C0(&var_C);
    }
}

// match: ?sub_19A8D0@@YAPAXPAUtype_3DF8D8_ev@@H@Z @ 0x0019A8D0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The clump noted for the header arg_0's file and arg_4, or 0.
void *sub_19A8D0(type_3DF8D8_ev *arg_0, RwInt32 arg_4)
{
    type_4F277C *var_14;
    type_4F277C ebp_10;
    void *l4;

    l4 = 0;
    if (arg_0->unk_18)
    {
        ebp_10.unk_00 = (RwInt32)arg_0->unk_18;
        ebp_10.unk_04 = arg_4;
        ebp_10.unk_08 = 0;
        var_14 = (type_4F277C *)dword_4F26D4.sub_67970(&ebp_10);
        if (var_14)
            l4 = (void *)var_14->unk_08;
    }
    return l4;
}

// match: ?sub_19A930@@YAHHH@Z @ 0x0019A930
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The value noted for the file arg_0 and the clump arg_4, or -1.
RwInt32 sub_19A930(RwInt32 arg_0, RwInt32 arg_4)
{
    type_4F277C *var_14;
    type_4F277C ebp_10;
    RwInt32 l4;

    l4 = -1;
    if (arg_0)
    {
        ebp_10.unk_00 = arg_0;
        ebp_10.unk_04 = -1;
        ebp_10.unk_08 = arg_4;
        var_14 = (type_4F277C *)dword_4F26D4.sub_67970(&ebp_10);
        if (var_14)
            l4 = var_14->unk_04;
    }
    return l4;
}

// match: ?sub_19A980@@YAIPAX@Z @ 0x0019A980
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The object table's hash: the key's first word.
RwUInt32 sub_19A980(void *arg_0)
{
    type_3DF8D8_base *var_8;
    type_3DF8D8_04 *l4;

    var_8 = (type_3DF8D8_base *)arg_0;
    l4 = &var_8->unk_04;
    return l4->unk_00;
}

// match: ?sub_19A9A0@@YA_NPAX0@Z @ 0x0019A9A0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The object table's test: equal keys.
bool sub_19A9A0(void *arg_0, void *arg_4)
{
    type_3DF8D8_base *var_C;
    type_3DF8D8_04 *bp_8;
    type_3DF8D8_04 *bp_4;

    var_C = (type_3DF8D8_base *)arg_0;
    bp_8 = &var_C->unk_04;
    var_C = (type_3DF8D8_base *)arg_4;
    bp_4 = &var_C->unk_04;
    return bp_8->unk_00 == bp_4->unk_00 && bp_8->unk_04 == bp_4->unk_04;
}

// match: ?sub_19AA00@@YAIPAX@Z @ 0x0019AA00
// The file-info table's hash: the file id.
RwUInt32 sub_19AA00(void *arg_0)
{
    type_4F277C *var_4;

    var_4 = (type_4F277C *)arg_0;
    return var_4->unk_00;
}

// match: ?sub_19AA20@@YA_NPAX0@Z @ 0x0019AA20
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The file-info table's test: the same file and value, or with either value
// -1, the same file and clump.
bool sub_19AA20(void *arg_0, void *arg_4)
{
    type_4F277C *var_8;
    type_4F277C *l4;

    var_8 = (type_4F277C *)arg_0;
    l4 = (type_4F277C *)arg_4;
    if (var_8->unk_04 == -1 || l4->unk_04 == -1)
        return var_8->unk_00 == l4->unk_00 && var_8->unk_08 == l4->unk_08;
    return var_8->unk_00 == l4->unk_00 && var_8->unk_04 == l4->unk_04;
}
