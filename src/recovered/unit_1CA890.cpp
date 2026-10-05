// The localised text (game/loc.h): the dictionary, the tables and their
// manager.

#include <stdio.h>
#include <string.h>

#include "game/loc.h"
#include "game/assert.h"
#include "types/type_DC400.h"
#include "game/pool.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x0042CC64
RwInt32 unk_42CC64[10] = { 1, 0, 4, 2, 3, 5, 8, 10, 7, -1 };
// 0x0042CC8C
const RwChar *unk_42CC8C[9] = { "JAPANESE", "ENGLISH", "FRENCH", "SPANISH", "GERMAN", "ITALIAN", "DUTCH",
                                "PORTUGUESE", "KOREAN" };
// 0x0042CCB0
const RwChar *unk_42CCB0[9] = { "JAP", "ENG", "FRE", "SPA", "GER", "ITA", "DUT", "POR", "KOR" };
// 0x0042CCD4
const RwChar *dword_42CCD4[9] = { "JA", "US", "FR", "SP", "DE", "IT", "NL", "PT", "KO" };
// 0x004FEAEC
bool byte_4FEAEC;
// End of its data definitions.


// Conditions retain the loads of the image's compiled-out checks.
#define LOCTEXT_CHECK(condition) { if (!(condition)) { } }

// Globals with constructors defined here (their initializers and exit
// functions at the end of .text): the block pools, each a heap from the
// default pool (sub_1F8CF0).
type_1CAC10 unk_4FEB0C;
type_1F8E00 unk_4FEBDC(sub_1F8CF0(), 0x10000);
type_1F8E00 unk_4FEBFC(sub_1F8CF0(), 0xC000);
type_1F8E00 unk_4FEC1C(sub_1F8CF0(), 0x10000);
type_1F8E00 unk_4FEBBC(sub_1F8CF0(), 102400);
type_1F8E00 unk_4FEC3C(sub_1F8CF0(), 0x8000);
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_02LJABHAG@KO?$AA@ @ 0x003E3C8C
// match: ??_C@_02LCNFJAAN@PT?$AA@ @ 0x003E3C90
// match: ??_C@_02CGHGIGCO@NL?$AA@ @ 0x003E3C94
// match: ??_C@_02KBCCAIPC@IT?$AA@ @ 0x003E3C98
// match: ??_C@_02PKCDLILB@DE?$AA@ @ 0x003E3C9C
// match: ??_C@_02NEPPOLFA@SP?$AA@ @ 0x003E3CA0
// match: ??_C@_02PMCEOIEJ@FR?$AA@ @ 0x003E3CA4
// match: ??_C@_02PLFPMECB@US?$AA@ @ 0x003E3CA8
// match: ??_C@_02JENBFALP@JA?$AA@ @ 0x003E3CAC
// match: ??_C@_03GBOFAKPE@KOR?$AA@ @ 0x003E3CB0
// match: ??_C@_03OGPNNKGK@POR?$AA@ @ 0x003E3CB4
// match: ??_C@_03HOGNJLIC@DUT?$AA@ @ 0x003E3CB8
// match: ??_C@_03LKHAMPHM@ITA?$AA@ @ 0x003E3CBC
// match: ??_C@_03CGKEDAJK@GER?$AA@ @ 0x003E3CC0
// match: ??_C@_03ICNNNAFL@SPA?$AA@ @ 0x003E3CC4
// match: ??_C@_03ICPCGGJM@FRE?$AA@ @ 0x003E3CC8
// match: ??_C@_03LHENPBOE@ENG?$AA@ @ 0x003E3CCC
// match: ??_C@_03OBPBCCBJ@JAP?$AA@ @ 0x003E3CD0
// match: ??_C@_06CLCKAIGD@KOREAN?$AA@ @ 0x003E3CD4
// match: ??_C@_0L@NCMCGEAP@PORTUGUESE?$AA@ @ 0x003E3CDC
// match: ??_C@_05CEBEDIPM@DUTCH?$AA@ @ 0x003E3CE8
// match: ??_C@_07NLCMMKLO@ITALIAN?$AA@ @ 0x003E3CF0
// match: ??_C@_06IIKFGJJO@GERMAN?$AA@ @ 0x003E3CF8
// match: ??_C@_07PBCAEALG@SPANISH?$AA@ @ 0x003E3D00
// match: ??_C@_06KFKKMHJN@FRENCH?$AA@ @ 0x003E3D08
// match: ??_C@_07NAIMCPPE@ENGLISH?$AA@ @ 0x003E3D10
// match: ??_C@_08PIFBPFEL@JAPANESE?$AA@ @ 0x003E3D18
// match: .CRT$XCU+0 @ 0x00427218
// match: .CRT$XCU+4 @ 0x0042721C
// match: .CRT$XCU+8 @ 0x00427220
// match: .CRT$XCU+12 @ 0x00427224
// match: .CRT$XCU+16 @ 0x00427228
// match: .CRT$XCU+20 @ 0x0042722C
// match: ?unk_42CC64@@3PAHA @ 0x0042CC64
// match: ?unk_42CC8C@@3PAPBDA @ 0x0042CC8C
// match: ?unk_42CCB0@@3PAPBDA @ 0x0042CCB0
// match: ?dword_42CCD4@@3PAPBDA @ 0x0042CCD4

// match: _$E2 @ 0x0030C890
// match: _$E3 @ 0x0030EB50
// match: _$E5 @ 0x0030C8B0
// match: _$E8 @ 0x0030C8E0
// match: _$E11 @ 0x0030C910
// match: _$E14 @ 0x0030C940
// match: _$E17 @ 0x0030C970
// match: _$E6 @ 0x0030EBB0
// match: _$E9 @ 0x0030EBC0
// match: _$E12 @ 0x0030EBD0
// match: _$E15 @ 0x0030EBE0
// match: _$E18 @ 0x0030EBF0
// match: ?sub_1CA890@@YAPBDH@Z @ 0x001CA890

const RwChar *sub_1CA890(RwInt32 arg_0)
{
    return dword_42CCD4[arg_0];
}

// match: ??0type_1CA8A0@@QAE@HH@Z @ 0x001CA8A0
type_1CA8A0::type_1CA8A0(RwInt32 arg_0, RwInt32 arg_4)
{
    unk_04 = arg_0;
    unk_00 = new type_1CA8A0_00[arg_0 * 8];
    unk_08 = 0;
    unk_0C = arg_4;
    unk_10 = 0;
    unk_14 = 0;
    unk_18 = 0;
}

// match: ??1type_1CA8A0@@QAE@XZ @ 0x001CA910
type_1CA8A0::~type_1CA8A0()
{
    delete[] unk_00;
}

// match: ?sub_1CA940@type_1CA8A0@@QAEHPBD0@Z @ 0x001CA940
RwInt32 type_1CA8A0::sub_1CA940(const RwChar *arg_0, const RwChar *arg_4)
{
    unk_18++;
    if (arg_0 == arg_4)
        return 0;
    if (!unk_0C)
        return _strcmpi(arg_0, arg_4);
    return strcmp(arg_0, arg_4);
}

// match: ?sub_1CA9A0@type_1CA8A0@@QAEXH@Z @ 0x001CA9A0
void type_1CA8A0::sub_1CA9A0(RwInt32 arg_0)
{
    RwInt32 var_4;
    RwInt32 lv_C;
    RwInt32 loc8;
    type_1CA8A0_00 lv_14;

    for (var_4 = arg_0; var_4 < unk_08 - 1; var_4++)
    {
        lv_C = var_4;
        while ((loc8 = sub_1CA940(unk_00[lv_C].unk_00, unk_00[lv_C + 1].unk_00)) > 0)
        {
            lv_14 = unk_00[lv_C];
            unk_00[lv_C] = unk_00[lv_C + 1];
            unk_00[lv_C + 1] = lv_14;
            if (--lv_C < 0)
                break;
        }
    }
    unk_14 = 0;
    unk_18 = 0;
}

// match: ?sub_1CAA80@type_1CA8A0@@QAEPAUtype_1CA8A0_00@@PBD@Z @ 0x001CAA80
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
type_1CA8A0_00 *type_1CA8A0::sub_1CAA80(const RwChar *arg_0)
{
    RwInt32 var_14;
    RwInt32 lv_10;
    RwInt32 var_C;
    RwInt32 bp_8;
    RwInt32 bp_4;

    lv_10 = 0;
    var_C = unk_08 - 1;
    unk_14++;
    while (1)
    {
        var_14 = var_C - lv_10;
        if (var_14 <= 1)
        {
            var_C++;
            for (; lv_10 != var_C; lv_10++)
            {
                if (!sub_1CA940(arg_0, unk_00[lv_10].unk_00))
                    return &unk_00[lv_10];
            }
            return 0;
        }
        bp_4 = (var_14 >> 1) + lv_10;
        bp_8 = sub_1CA940(arg_0, unk_00[bp_4].unk_00);
        if (!bp_8)
            return &unk_00[bp_4];
        if (bp_8 < 0)
            var_C = bp_4;
        else
            lv_10 = bp_4;
    }
    return 0;
}

// match: ?sub_1CAB70@type_1CA8A0@@QAEPBGPBD@Z @ 0x001CAB70
const RwUInt16 *type_1CA8A0::sub_1CAB70(const RwChar *arg_0)
{
    type_1CA8A0_00 *var_4;

    var_4 = sub_1CAA80(arg_0);
    if (var_4)
        return var_4->unk_04;
    return 0;
}

// match: ?sub_1CABA0@type_1CA8A0@@QAEXPBDPBG@Z @ 0x001CABA0
void type_1CA8A0::sub_1CABA0(const RwChar *arg_0, const RwUInt16 *arg_4)
{
    if (!sub_1CAA80(arg_0))
    {
        unk_00[unk_08].unk_00 = arg_0;
        unk_00[unk_08].unk_04 = arg_4;
        unk_08++;
        if (unk_08 > 1)
            sub_1CA9A0(unk_08 - 2);
    }
}

// match: ??0type_1CAC10@@QAE@XZ @ 0x001CAC10
type_1CAC10::type_1CAC10()
{
    memset(this, 0, sizeof(unk_00));
    unk_0C = 10;
    byte_4FEAEC = false;
}

// match: ??1type_1CAC10@@QAE@XZ @ 0x001CAC40
type_1CAC10::~type_1CAC10()
{
    sub_1CAC60(false);
}

// match: ?sub_1CAC60@type_1CAC10@@QAEX_N@Z @ 0x001CAC60
void type_1CAC10::sub_1CAC60(bool arg_0)
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 3; var_4++)
    {
        if (unk_00[var_4] && (var_4 || arg_0))
            sub_1CACC0(var_4);
    }
    byte_4FEAEC = false;
}

// match: ?sub_1CACC0@type_1CAC10@@QAE_NH@Z @ 0x001CACC0
bool type_1CAC10::sub_1CACC0(RwInt32 arg_0)
{
    if (unk_00[arg_0])
    {
        unk_00[arg_0]->sub_1CB310();
        delete unk_00[arg_0];
        unk_00[arg_0] = 0;
    }
    return false;
}

// match: ?sub_1CAD40@type_1CAC10@@QAE_NH@Z @ 0x001CAD40
bool type_1CAC10::sub_1CAD40(RwInt32 arg_0)
{
    RwInt32 var_4;

    if (arg_0 != unk_0C)
    {
        unk_0C = arg_0;
        for (var_4 = 0; var_4 < 3; var_4++)
        {
            if (unk_00[var_4])
                sub_1CADA0(var_4, &byte_4FEAEC);
        }
        return true;
    }
    return false;
}













// type_1A5EA0's constructor from a key and a table is this one's code (0x1CB6B0): the base
// has no data of its own, so the link takes this for it (PLAN M7).
#pragma comment(linker, "/alternatename:??0type_1A5EA0@@QAE@PBDH@Z=??0type_1CB670@@QAE@PBDH@Z")
















// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??0type_1CB670@@QAE@ABU0@@Z (folded into 0x1CB670)
type_1CB670::type_1CB670(struct type_1CB670 const & arg_0) : type_1A5EA0(arg_0.c_str())
{
}
