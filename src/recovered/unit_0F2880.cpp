// The particle systems (include/game/particles.h, types/type_F2FF0.h). The
// original file name is not in the image, so it is named for its start
// address.

#include <string.h>
#include <stdio.h>

#include "rw/ostypes.h"
#include "game/frand.h"
#include "rw/bamatrix.h"
#include "rw/baframe.h"
#include "rw/bastream.h"
#include "rw/babintex.h"
#include "rw/batextur.h"
#include "rw/badevice.h"
#include "rw/baengine.h"
#include "rw/rpatomic.h"
#include "rw/rprandom.h"
#include "rw/rt2d.h"
#include "game/data.h"
#include "game/functions.h"
#include "game/gameloop.h"
#include "game/decals.h"
#include "game/particles.h"
#include "types/asynchload.h"
#include "types/type_3D3548.h"
#include "types/type_F2880.h"
#include "rws/skinhelper.h"
#include "game/pooledconsts.h"
#include "rw/bavector.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003D92B8
extern const RwReal flt_3D92B8 = 16.666666f;
// 0x004BC8B8
type_4BC8B8 dword_4BC8B8[50];
// 0x004BCE30
RwInt32 dword_4BCE30;
// 0x004BCE34
type_F3830 *dword_4BCE34;
// 0x004BCE38
RwInt32 dword_4BCE38;
// 0x004BCE3C
RwInt32 dword_4BCE3C;
// 0x004BCE40
RwInt32 dword_4BCE40;
// 0x004BCE44
type_F3830 *dword_4BCE44;
// 0x004BCE48
type_F3830 dword_4BCE48[0x2BC];
// 0x004BFD28
type_4BFD28 *dword_4BFD28;
// 0x004BFD2C
RwTexDictionary *dict;
// 0x004BFD30
RwInt32 dword_4BFD30;
// 0x004BFD34
type_F2FF0 *dword_4BFD34;
// 0x004BFD38
RwInt32 dword_4BFD38;
// 0x004BFD3C
RwInt32 dword_4BFD3C;
// 0x004BFD40
RwInt32 dword_4BFD40;
// 0x004BFDB8
RwInt32 dword_4BFDB8;
// 0x004BFDBC
RwCamera *dword_4BFDBC;
// 0x004BFDC0
RwInt32 dword_4BFDC0;
// 0x004BFDC4
RwInt32 dword_4BFDC4;
// End of its data definitions.


// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).
type_16C2A0 dword_4BFD44;
type_16C2A0 dword_4BFD98;
alfahash dword_4BFD64;
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3D92B8@@3MB @ 0x003D92B8
// match: ??_C@_0BM@EDLIOJGK@m_sppSystemFreeListPriority?$AA@ @ 0x003D92BC
// match: ??_C@_0BE@BGCAEMKK@m_sppSystemFreeList?$AA@ @ 0x003D92D8
// match: ??_C@_04BKKFMPMK@?4rx1?$AA@ @ 0x003D92EC
// match: ??_C@_06OBFMGGE@?$CFs?4spp?$AA@ @ 0x003D92F4
// match: __real@c4fa0000 @ 0x003D92FC
// match: __real@410547ae @ 0x003D9300
// match: __ehhandler$?sub_F3130@@YAPAUtype_F2FF0@@PAUtype_F3130@@PAURwMatrixTag@@HH_N2@Z>1>8 @ 0x0041D028
// match: __ehhandler$?sub_F3130@@YAPAUtype_F2FF0@@PAUtype_F3130@@PAURwMatrixTag@@HH_N2@Z>1 @ 0x0041D030
// match: .CRT$XCU+0 @ 0x00427060
// match: .CRT$XCU+4 @ 0x00427064
// match: .CRT$XCU+8 @ 0x00427068

// match: _$E1 @ 0x0030B5C0
// match: _$E2 @ 0x0030E500
// match: _$E4 @ 0x0030B5E0
// match: _$E5 @ 0x0030E510
// match: _$E7 @ 0x0030B600
// match: _$E8 @ 0x0030E520
// sp-match: _$E8 @ 0x0021E8B0
// sp-match: _$E1 @ 0x0021D640
// sp-match: _$E4 @ 0x0021D660
// sp-match: _$E7 @ 0x0021D680
// sp-match: _$E2 @ 0x0021E890
// sp-match: _$E5 @ 0x0021E8A0

// The engine's memory functions' first two slots (include/rw/bamemory.h).

// match: ?sub_F2880@type_F2880@@QAEXPAUtype_F2FF0@@@Z @ 0x000F2880
// sp-match: ?sub_F2880@type_F2880@@QAEXPAUtype_F2FF0@@@Z @ 0x000B9190
void type_F2880::sub_F2880(type_F2FF0 *arg_0)
{
    type_F2FF0 *var_4 = unk_08;

    if (var_4)
    {
        if (var_4 == arg_0)
        {
            return;
        }
        var_4->sub_F44E0(this);
    }
    if (arg_0)
    {
        arg_0->sub_F4480(this);
    }
    unk_08 = arg_0;
}

// The hash of the definitions' records: a record's id, and whether two
// records' ids are equal.
// match: ?sub_F28D0@@YAIPAX@Z @ 0x000F28D0
// sp-match: ?sub_F28D0@@YAIPAX@Z @ 0x000B91C0
RwUInt32 sub_F28D0(void *arg_0)
{
    type_4BFD28_rec *var_4 = (type_4BFD28_rec *)arg_0;

    return var_4->unk_28;
}

// match: ?sub_F28F0@@YA_NPAX0@Z @ 0x000F28F0
// sp-match: ?sub_F28F0@@YA_NPAX0@Z @ 0x000B91D0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
bool sub_F28F0(void *arg_0, void *arg_4)
{
    type_4BFD28_rec *bp_8 = (type_4BFD28_rec *)arg_0;
    type_4BFD28_rec *bp_4 = (type_4BFD28_rec *)arg_4;

    return bp_8->unk_28 == bp_4->unk_28;
}

// match: ?sub_F2920@@YAXXZ @ 0x000F2920
// sp-match: ?sub_F2920@@YAXXZ @ 0x000B9710
void sub_F2920()
{
    dword_4BFD44.sub_16C2C0(0x2BC, 0x160, "m_sppSystemFreeList", 0x20, 0);
    dword_4BFD64.sub_67730(0x140, 0x40, sub_F28D0, sub_F28F0);
    dword_4BFD98.sub_16C2C0(0x32, 0x160, "m_sppSystemFreeListPriority", 0x20, 0);
    dword_4BFD28 = 0;
    dict = 0;
    dword_4BFD30 = 0;
    dword_4BFD34 = 0;
    dword_4BFD38 = 0;
    dword_4BFD3C = 0;
    dword_4BCE3C = 0;
    dword_4BCE40 = 0;
    sub_19E500();
    sub_F37B0();
    dword_4BFDC0 = 0;
    dword_4BFDC4 = 0;
}

// match: ?sub_F29F0@@YAXXZ @ 0x000F29F0
// sp-match: ?sub_F29F0@@YAXXZ @ 0x000B9E70
void sub_F29F0()
{
    sub_F2A00(0);
}

// match: ?sub_F2A00@@YAXH@Z @ 0x000F2A00
// sp-match: ?sub_F2A00@@YAXH@Z @ 0x000B9C80
void sub_F2A00(RwInt32 arg_0)
{
    sub_F37B0();
    sub_F33C0();
    if (arg_0)
    {
        sub_EFF70();
        sub_F2E10();
        sub_F2E90();
    }
}

// match: ?sub_F2A30@@YAXXZ @ 0x000F2A30
// sp-match: ?sub_F2A30@@YAXXZ @ 0x000B9CB0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_F2A30()
{
    RwFrame *bp_8;
    RwInt32 bp_4;

    sub_F33C0();
    dword_4BFD44.sub_16C4D0(1);
    dword_4BFD98.sub_16C4D0(1);
    for (bp_4 = 0; bp_4 < dword_4BFD3C; bp_4++)
    {
        if (dword_4BC8B8[bp_4].unk_14)
        {
            bp_8 = RpAtomicGetFrameMacro(dword_4BC8B8[bp_4].unk_18);
            if (bp_8)
            {
                RpAtomicSetFrame(dword_4BC8B8[bp_4].unk_18, 0);
                RwFrameDestroy(bp_8);
            }
            RpClumpDestroy(dword_4BC8B8[bp_4].unk_14);
        }
    }
    dword_4BFD3C = 0;
    sub_F2E10();
    sub_F2E90();
    sub_19E930();
    dword_4BFD64.sub_67780();
}

// match: ?sub_F2B00@@YAXPAUtype_4BFD28@@@Z @ 0x000F2B00
// sp-match: ?sub_F2B00@@YAXPAUtype_4BFD28@@@Z @ 0x000B91F0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_F2B00(type_4BFD28 *arg_0)
{
    RwInt32 bp_8;
    type_4BFD28_rec *bp_4;
    RwChar fp_2C[0x20];
    RwInt32 o30;
    type_F3130 *l34;
    RwTexture *fp_38;

    dword_4BFD28 = arg_0;
    bp_8 = dword_4BFD28->unk_00;
    bp_4 = dword_4BFD28->unk_04;
    for (o30 = 0; o30 < bp_8; o30++, bp_4++)
    {
        l34 = RWPLUGINOFFSET(type_F3130, dword_4BFD28, bp_4->unk_24);
        l34->unk_04 = 0;
        if (dict && l34->unk_84[0])
        {
            sub_16E950(fp_2C, l34->unk_84);
            fp_38 = RwTexDictionaryFindNamedTexture(dict, fp_2C);
            if (fp_38)
            {
                RwTextureSetFilterMode(fp_38, rwFILTERLINEAR);
                l34->unk_04 = fp_38;
            }
        }
        dword_4BFD64.sub_67850(bp_4);
    }
    if (dword_4BFD28 && dict && !dword_4BFD38)
    {
        dword_4BFD38 = 1;
        dword_4B86FC--;
    }
}

// match: ?sub_F2C30@@YAXPAURwStream@@@Z @ 0x000F2C30
// sp-match: ?sub_F2C30@@YAXPAURwStream@@@Z @ 0x000B92D0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_F2C30(RwStream *arg_0)
{
    RwFrame *lv_10;
    RwInt32 slot_C;
    RwChar (*bp_8)[0x2C];
    RwInt32 bp_4;

    RwStreamRead(arg_0, &dword_4BFD3C, 4);
    bp_8 = (RwChar (*)[0x2C])RwMalloc(dword_4BFD3C * 0x2C, 0x34250); // not an address: an allocation tag
    RwStreamRead(arg_0, bp_8, dword_4BFD3C * 0x2C);
    RwTexDictionarySetCurrent(dict);
    bp_4 = 0;
    for (slot_C = 0; slot_C < dword_4BFD3C; slot_C++)
    {
        if (RwStreamFindChunk(arg_0, 0x10, 0, 0))
        {
            strcpy(dword_4BC8B8[bp_4].unk_00, bp_8[bp_4]);
            dword_4BC8B8[bp_4].unk_14 = RpClumpStreamRead(arg_0);
            RpClumpForAllAtomics(dword_4BC8B8[bp_4].unk_14, (RpAtomic *(*)(RpAtomic *, void *))RWS::SkinHelper::FindFirstSkinCallback, &dword_4BC8B8[bp_4].unk_18);
            lv_10 = RwFrameCreate();
            RwFrameSetIdentity(lv_10);
            RpAtomicSetFrame(dword_4BC8B8[bp_4].unk_18, lv_10);
            bp_4++;
        }
    }
    RwFree(bp_8);
}

// match: ?sub_F2D80@@YAPAURpAtomic@@PBD@Z @ 0x000F2D80
// sp-match: ?sub_F2D80@@YAPAURpAtomic@@PBD@Z @ 0x000B93D0
RpAtomic *sub_F2D80(const RwChar *arg_0)
{
    RwChar var_48[0x40];
    RwInt32 var_4C;

    strcpy(var_48, arg_0);
    strcat(var_48, ".rx1");
    for (var_4C = 0; var_4C < dword_4BFD3C; var_4C++)
    {
        if (!_strcmpi(dword_4BC8B8[var_4C].unk_00, var_48))
        {
            return dword_4BC8B8[var_4C].unk_18;
        }
    }
    return 0;
}

// match: ?sub_F2E10@@YAXXZ @ 0x000F2E10
// sp-match: ?sub_F2E10@@YAXXZ @ 0x000B9470
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_F2E10()
{
    RwInt32 slot_C;
    RwInt32 bp_8;
    type_4BFD28_rec *bp_4;

    if (dword_4BFD28)
    {
        bp_8 = dword_4BFD28->unk_00;
        bp_4 = dword_4BFD28->unk_04;
        for (slot_C = 0; slot_C < bp_8; slot_C++, bp_4++)
        {
            dword_4BFD64.sub_678C0(bp_4);
        }
        operator delete(dword_4BFD28);
        dword_4BFD28 = 0;
    }
}

// match: ?sub_F2E90@@YAXXZ @ 0x000F2E90
// sp-match: ?sub_F2E90@@YAXXZ @ 0x000B94C0
void sub_F2E90()
{
    if (dict)
    {
        RwTexDictionaryDestroy(dict);
        dict = 0;
    }
}

// match: ?sub_F2EC0@@YAPAURwTexture@@PAU1@PAX@Z @ 0x000F2EC0
// sp-match: ?sub_F2EC0@@YAPAURwTexture@@PAU1@PAX@Z @ 0x000B94E0
RwTexture *sub_F2EC0(RwTexture *arg_0, void *arg_4)
{
    return RwTextureSetFilterMode(arg_0, rwFILTERLINEAR);
}

// match: ?sub_F2EE0@@YAXPAURwTexDictionary@@@Z @ 0x000F2EE0
// sp-match: ?sub_F2EE0@@YAXPAURwTexDictionary@@@Z @ 0x000B94F0
void sub_F2EE0(RwTexDictionary *arg_0)
{
    dict = arg_0;
    if (dict)
    {
        RwTexDictionaryForAllTextures(arg_0, sub_F2EC0, 0);
    }
    if (dword_4BFD28 && dict && !dword_4BFD38)
    {
        dword_4BFD38 = 1;
        dword_4B86FC--;
    }
}

// match: ?sub_F2F40@@YAXPAUtype_F2FF0@@@Z @ 0x000F2F40
// sp-match: ?sub_F2F40@@YAXPAUtype_F2FF0@@@Z @ 0x000B9540
void sub_F2F40(type_F2FF0 *arg_0)
{
    arg_0->unk_4C = dword_4BFD34;
    arg_0->unk_48 = 0;
    if (dword_4BFD34)
    {
        dword_4BFD34->unk_48 = arg_0;
    }
    dword_4BFD34 = arg_0;
}

// match: ?sub_F2F80@@YAXPAUtype_F2FF0@@@Z @ 0x000F2F80
// sp-match: ?sub_F2F80@@YAXPAUtype_F2FF0@@@Z @ 0x000B9570
void sub_F2F80(type_F2FF0 *arg_0)
{
    type_F2FF0 *var_4;

    var_4 = arg_0->unk_48;
    if (var_4)
    {
        var_4->unk_4C = arg_0->unk_4C;
    }
    var_4 = arg_0->unk_4C;
    if (var_4)
    {
        var_4->unk_48 = arg_0->unk_48;
    }
    if (arg_0 == dword_4BFD34)
    {
        dword_4BFD34 = arg_0->unk_4C;
    }
    arg_0->unk_4C = 0;
    arg_0->unk_48 = 0;
}

// match: ?sub_F2FF0@@YAHHPAURwMatrixTag@@HH_N1@Z @ 0x000F2FF0
// sp-match: ?sub_F2FF0@@YAHHPAURwMatrixTag@@HH_N1@Z @ 0x000B9D40
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_F2FF0(RwInt32 arg_0, RwMatrix *arg_4, RwInt32 arg_8, RwInt32 arg_C, bool arg_10, bool arg_14)
{
    type_4BFD28_rec *bp_4;
    type_4BFD28_rec r34;
    type_F3130 *ebp_38;

    if (dword_4BFD28)
    {
        r34.unk_28 = arg_0;
        bp_4 = (type_4BFD28_rec *)dword_4BFD64.sub_67970(&r34);
        if (bp_4)
        {
            ebp_38 = RWPLUGINOFFSET(type_F3130, dword_4BFD28, bp_4->unk_24);
            return (RwInt32)sub_F3130(ebp_38, arg_4, arg_8, arg_C, arg_10, arg_14);
        }
    }
    return 0;
}

// match: ?sub_F3070@@YAPAUtype_F2FF0@@PBDPAURwMatrixTag@@HH_N2@Z @ 0x000F3070
// sp-match: ?sub_F3070@@YAPAUtype_F2FF0@@PBDPAURwMatrixTag@@HH_N2@Z @ 0x000B9DC0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
type_F2FF0 *sub_F3070(const RwChar *arg_0, RwMatrix *arg_4, RwInt32 arg_8, RwInt32 arg_C, bool arg_10,
                      bool arg_14)
{
    RwChar frm_24[0x20];
    type_4BFD28_rec *lcl_28;
    RwInt32 o30;
    RwInt32 ebp_2C;
    type_F3130 *l34;

    sprintf(frm_24, "%s.spp", arg_0);
    if (dword_4BFD28)
    {
        ebp_2C = dword_4BFD28->unk_00;
        lcl_28 = dword_4BFD28->unk_04;
        for (o30 = 0; o30 < ebp_2C; o30++, lcl_28++)
        {
            if (!_strcmpi(lcl_28->unk_00, frm_24))
            {
                l34 = RWPLUGINOFFSET(type_F3130, dword_4BFD28, lcl_28->unk_24);
                return sub_F3130(l34, arg_4, arg_8, arg_C, arg_10, arg_14);
            }
        }
    }
    return 0;
}

// match: ?sub_F3130@@YAPAUtype_F2FF0@@PAUtype_F3130@@PAURwMatrixTag@@HH_N2@Z @ 0x000F3130
// match: __ehhandler$?sub_F3130@@YAPAUtype_F2FF0@@PAUtype_F3130@@PAURwMatrixTag@@HH_N2@Z-0x11 @ 0x00301070
// match: __ehhandler$?sub_F3130@@YAPAUtype_F2FF0@@PAUtype_F3130@@PAURwMatrixTag@@HH_N2@Z @ 0x00301081
// sp-match: ?sub_F3130@@YAPAUtype_F2FF0@@PAUtype_F3130@@PAURwMatrixTag@@HH_N2@Z @ 0x000B97B0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
type_F2FF0 *sub_F3130(type_F3130 *arg_0, RwMatrix *arg_4, RwInt32 arg_8, RwInt32 arg_C, bool arg_10,
                      bool arg_14)
{
    RwInt32 ebp_14;
    type_F2FF0 *lv_10;

    if (arg_8 == 1 && dword_4BFD30 > 0x28)
    {
        return 0;
    }
    if (arg_0->unk_00 >= 3 && arg_0->unk_A8 && arg_8 == 1)
    {
        return 0;
    }
    lv_10 = (type_F2FF0 *)dword_4BFD44.sub_16C5A0(1);
    if (!lv_10)
    {
        if (arg_14)
        {
            lv_10 = (type_F2FF0 *)dword_4BFD98.sub_16C5A0(1);
            if (!lv_10)
            {
                return 0;
            }
            dword_4BCE3C++;
            if (dword_4BCE3C > dword_4BCE40)
            {
                dword_4BCE40 = dword_4BCE3C;
            }
        }
        else
        {
            return 0;
        }
    }
    lv_10 = new (lv_10) type_F2FF0();
    ebp_14 = lv_10->sub_F3C00(arg_0, arg_4, (RwReal)sub_F39D0(), arg_8, arg_C, arg_10);
    if (ebp_14)
    {
        if (arg_8 == 1)
        {
            dword_4BFD30++;
        }
    }
    else
    {
        if (dword_4BFD44.sub_16C770(lv_10))
        {
            dword_4BFD44.sub_16C710(lv_10);
        }
        else if (dword_4BFD98.sub_16C770(lv_10))
        {
            dword_4BFD98.sub_16C710(lv_10);
            dword_4BCE3C--;
        }
        lv_10 = 0;
    }
    return lv_10;
}

// match: ?sub_F3300@@YAXPAUtype_F2FF0@@@Z @ 0x000F3300
// sp-match: ?sub_F3300@@YAXPAUtype_F2FF0@@@Z @ 0x000B9940
void sub_F3300(type_F2FF0 *arg_0)
{
    if (arg_0->unk_40 & 0x20)
    {
        dword_4BFD30--;
    }
    delete arg_0;
}

// match: ?sub_F3370@@YAXPAUtype_F3130@@@Z @ 0x000F3370
// sp-match: ?sub_F3370@@YAXPAUtype_F3130@@@Z @ 0x000B9970
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_F3370(type_F3130 *arg_0)
{
    type_F2FF0 *bp_8 = 0;
    type_F2FF0 *bp_4;

    bp_4 = dword_4BFD34;
    while (bp_4)
    {
        bp_8 = bp_4->unk_4C;
        if (bp_4->unk_44 == arg_0)
        {
            sub_F3300(bp_4);
        }
        bp_4 = bp_8;
    }
}

// match: ?sub_F33C0@@YAXXZ @ 0x000F33C0
// sp-match: ?sub_F33C0@@YAXXZ @ 0x000B99A0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_F33C0()
{
    type_F2FF0 *bp_8 = 0;
    type_F2FF0 *bp_4;

    bp_4 = dword_4BFD34;
    while (bp_4)
    {
        bp_8 = bp_4->unk_4C;
        sub_F3300(bp_4);
        bp_4 = bp_8;
    }
    dword_4BFD30 = 0;
}

// match: ?sub_F3410@@YAXXZ @ 0x000F3410
// sp-match: ?sub_F3410@@YAXXZ @ 0x000B99D0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_F3410()
{
    RwReal m_18;
    RwCamera *ebp_14;
    RwReal lv_10;
    RwInt32 slot_C;
    type_F2FF0 *bp_8;
    type_F2FF0 *bp_4;

    m_18 = (RwReal)sub_F39D0();
#ifdef CODFH_SP
    // shape: the rate scaled in a second step (SP 0xB99D0 multiplies twice)
    lv_10 = deltaTime * flt_3D92B8;
    lv_10 /= 1000.0f;
#else
    lv_10 = deltaTime * flt_3D92B8 / 1000.0f;
#endif
    ebp_14 = (RwCamera *)dword_4E5C74;
    sub_19EA10();
    slot_C = 0;
    bp_8 = 0;
    bp_4 = dword_4BFD34;
    while (bp_4)
    {
        bp_8 = bp_4->unk_4C;
        if (!bp_4->sub_F4190(ebp_14, m_18, lv_10))
        {
            sub_F3300(bp_4);
        }
        slot_C++;
        bp_4 = bp_8;
    }
    if (slot_C > dword_4BFDB8)
    {
        dword_4BFDB8 = slot_C;
    }
}

// match: ?sub_F34C0@@YAXHI@Z @ 0x000F34C0
// sp-match: ?sub_F34C0@@YAXHI@Z @ 0x000B9A60
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_F34C0(RwInt32 arg_0, RwUInt32 arg_4)
{
    RpLight *ebp_14;
    RwCamera *lv_10;
    RpLight *slot_C;
    type_F2FF0 *bp_8;
    type_F2FF0 *bp_4;
#ifndef CODFH_SP
    RwV3d loc20;
#endif
    type_F3830 *lcl_28;
    RwReal w24;

    if (dword_4BFD40)
    {
        return;
    }
    RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void *)TRUE);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)FALSE);
    RwRenderStateSet(rwRENDERSTATECULLMODE, (void *)rwCULLMODECULLBACK);
    RwRenderStateSet(rwRENDERSTATESRCBLEND, (void *)rwBLENDSRCALPHA);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void *)rwBLENDINVSRCALPHA);
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void *)TRUE);
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void *)TRUE);
    RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, (void *)rwFILTERLINEAR);
    ebp_14 = get_light(0);
    slot_C = clump;
    bp_8 = 0;
    bp_4 = dword_4BFD34;
    while (bp_4)
    {
        bp_8 = bp_4->unk_4C;
        if ((bp_4->unk_40 & 0x10) && (bp_4->unk_40 & 0x40) == arg_4)
        {
            bp_4->sub_F43B0();
        }
        bp_4 = bp_8;
    }
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)TRUE);
    RwRenderStateSet(rwRENDERSTATECULLMODE, (void *)rwCULLMODECULLNONE);
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void *)FALSE);
    lv_10 = (RwCamera *)dword_4E5C74;
    if (!lv_10)
    {
        return;
    }
    sub_19EB20(lv_10);
    bp_4 = dword_4BFD34;
    while (bp_4)
    {
        bp_8 = bp_4->unk_4C;
        if (!(bp_4->unk_40 & 0x10) && (bp_4->unk_40 & 0x40) == arg_4)
        {
            if (arg_0)
            {
#ifdef CODFH_SP
                // shape: the position local to this block (its x and y stores after the
                // flag test, SP 0xB9B74), the definition read once (SP 0xB9B82) and the
                // drop term kept whole in w24 so 8.33 is not factored out (SP 0xB9BAF)
                RwV3d loc20;
                loc20 = bp_4->unk_00.pos;
                if (bp_4->unk_60.unk_14 & 8)
                {
                    type_F3130 *def = bp_4->unk_44;
                    loc20.x += def->unk_F8 * 8.33f * bp_4->unk_58;
                    w24 = bp_4->unk_58 * bp_4->unk_58 * 0.5f;
                    w24 = def->unk_104 * 8.33f * w24;
                    loc20.y += def->unk_FC * 8.33f * bp_4->unk_58 + w24;
                    loc20.z += def->unk_100 * 8.33f * bp_4->unk_58;
                }
#else
                loc20 = bp_4->unk_00.pos;
                if (bp_4->unk_60.unk_14 & 8)
                {
                    w24 = bp_4->unk_58 * bp_4->unk_58 * 0.5f;
                    loc20.x += bp_4->unk_44->unk_F8 * 8.33f * bp_4->unk_58;
                    loc20.y = bp_4->unk_44->unk_FC * 8.33f * bp_4->unk_58 + loc20.y +
                               bp_4->unk_44->unk_104 * 8.33f * w24;
                    loc20.z += bp_4->unk_44->unk_100 * 8.33f * bp_4->unk_58;
                }
#endif
                sub_1414C0(&loc20, &loc20, &lv_10->viewMatrix);
                if (loc20.z > -2000.0f)
                {
                    lcl_28 = sub_F3830();
                    if (lcl_28)
                    {
                        lcl_28->unk_04 = 0;
                        lcl_28->unk_00 = 0;
                        lcl_28->unk_0C = bp_4;
                        lcl_28->unk_08 = loc20.z;
                        sub_F38B0(lcl_28);
                    }
                }
            }
            else
            {
                bp_4->sub_F43B0();
            }
        }
        bp_4 = bp_8;
    }
    if (arg_0)
    {
        if (dword_4BCE34)
        {
            sub_F3930(dword_4BCE34, true);
        }
        dword_4BCE34 = 0;
    }
    sub_19EB90();
}

// match: ?sub_F37B0@@YAXXZ @ 0x000F37B0
// sp-match: ?sub_F37B0@@YAXXZ @ 0x000B95B0
void sub_F37B0()
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 0x2BB; var_4++)
    {
        dword_4BCE48[var_4].unk_00 = &dword_4BCE48[var_4 + 1];
    }
    dword_4BCE48[var_4].unk_00 = 0;
    dword_4BCE34 = 0;
    dword_4BCE44 = dword_4BCE48;
    dword_4BCE30 = 0;
    dword_4BCE38 = 0;
}

// match: ?sub_F3830@@YAPAUtype_F3830@@XZ @ 0x000F3830
// sp-match: ?sub_F3830@@YAPAUtype_F3830@@XZ @ 0x000B95F0
type_F3830 *sub_F3830()
{
    type_F3830 *var_4 = dword_4BCE44;

    if (var_4)
    {
        dword_4BCE44 = var_4->unk_00;
        dword_4BCE38++;
        if (dword_4BCE38 > dword_4BCE30)
        {
            dword_4BCE30 = dword_4BCE38;
        }
    }
    return var_4;
}

// match: ?sub_F3880@@YAXPAUtype_F3830@@@Z @ 0x000F3880
// sp-match: ?sub_F3880@@YAXPAUtype_F3830@@@Z @ 0x000B9620
void sub_F3880(type_F3830 *arg_0)
{
    arg_0->unk_00 = dword_4BCE44;
    dword_4BCE44 = arg_0;
    dword_4BCE38--;
}

// match: ?sub_F38B0@@YAXPAUtype_F3830@@@Z @ 0x000F38B0
// sp-match: ?sub_F38B0@@YAXPAUtype_F3830@@@Z @ 0x000B9640
void sub_F38B0(type_F3830 *arg_0)
{
    type_F3830 *var_4 = dword_4BCE34;

    if (var_4)
    {
        for (;;)
        {
            if (arg_0->unk_08 >= var_4->unk_08)
            {
                if (var_4->unk_00)
                {
                    var_4 = var_4->unk_00;
                }
                else
                {
                    var_4->unk_00 = arg_0;
                    break;
                }
            }
            else
            {
                if (var_4->unk_04)
                {
                    var_4 = var_4->unk_04;
                }
                else
                {
                    var_4->unk_04 = arg_0;
                    break;
                }
            }
        }
    }
    else
    {
        dword_4BCE34 = arg_0;
    }
}

// match: ?sub_F3930@@YAXPAUtype_F3830@@_N@Z @ 0x000F3930
// sp-match: ?sub_F3930@@YAXPAUtype_F3830@@_N@Z @ 0x000B9690
void sub_F3930(type_F3830 *arg_0, bool arg_4)
{
    if (arg_4)
    {
        if (arg_0->unk_00)
        {
            sub_F3930(arg_0->unk_00, arg_4);
        }
        arg_0->unk_0C->sub_F43B0();
        if (arg_0->unk_04)
        {
            sub_F3930(arg_0->unk_04, arg_4);
        }
    }
    else
    {
        if (arg_0->unk_04)
        {
            sub_F3930(arg_0->unk_04, arg_4);
        }
        arg_0->unk_0C->sub_F43B0();
        if (arg_0->unk_00)
        {
            sub_F3930(arg_0->unk_00, arg_4);
        }
    }
    sub_F3880(arg_0);
}

// match: ?sub_F39D0@@YAIXZ @ 0x000F39D0
// sp-match: ?sub_F39D0@@YAIXZ @ 0x000B9700
RwUInt32 sub_F39D0()
{
    RwUInt32 var_4 = RWS::Time::GetTime();

    return var_4;
}














// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??2type_F2FF0@@SAPAXIPAX@Z (folded into 0x6CCF0)
void *type_F2FF0::operator new(RwUInt32 arg_0, void *arg_4)
{
    return arg_4;
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??3type_F2FF0@@SAXPAX0@Z (folded into 0x19A750)
void type_F2FF0::operator delete(void * arg_0, void * arg_4)
{
}
