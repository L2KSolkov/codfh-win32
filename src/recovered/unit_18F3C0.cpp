// The GodAsset objects (type_3DF8D8, types/type_3DF8D8.h): the keyed
// objects the level's data defines, their kinds and their loading.

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include <string.h>
#include "types/type_3DF8D8.h"
#include "types/type_495F0.h"
#include "types/SoldierTrigger.h"
#include "game/functions.h"
#include "rw/bastream.h"
#include "rw/batextur.h"
#include "rw/babintex.h"
#include "rw/rtpitexd.h"
#include "xbox/xboxkrnl.h"
#include "types/asynchload.h"
#include "types/type_141C10.h"
#include "types/type_72810.h"
#include <stdio.h>
#include "rw/rpatomic.h"
#include "rw/rpmaterial.h"
#include "rw/rtdict.h"
#include "rw/babbox.h"
#include "game/clumpdata.h"
#include "game/gameloop.h"
#include "types/type_3D96F0.h"
#include "game/clumpbank.h"
#include "game/weaponbank.h"
#include "types/animbank.h"
#include "types/type_44350.h"
#include "game/data.h"
#include "types/musicplayer.h"
#include "types/soundbank.h"
#include "types/type_8A980.h"
#include "game/textmanager.h"
#include "types/type_DC400.h"
#include "rw/rprandom.h"
#include "types/alfaobject.h"
#include "game/pak.h"
#include "types/type_4C09B0.h"
#include "rw/bamatrix.h"
#include "rw/rtquat.h"
#include "types/type_4E1B70.h"
#include "types/type_F8350.h"
#include "types/type_3D3548.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003DF8D4
extern const RwReal flt_3DF8D4 = 16.666666f;

// match: ??0type_3DF8D8_base@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x0018F3C0
// match: ?vf_000@type_3DF8D8_base@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x0018F420
// match: ?flt_3DF8D4@@3MB @ 0x003DF8D4
// match: ??_7type_3DF8E4@@6B@ @ 0x003DF8E4
// match: ??_7type_3DF8F0@@6B@ @ 0x003DF8F0
// match: ??_7type_3DF8FC@@6B@ @ 0x003DF8FC
// match: ??_C@_0DB@HGGOFGAL@?6?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK@ @ 0x003DF908
// match: ??_C@_0CO@OGFFGHDG@?$CK?$CK?$CKGod?5ID?3?5?$CFx?0?$CFx?5is?5not?5a?5valid?5@ @ 0x003DF93C
// match: ??_C@_0DC@GNELFPFE@?6?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK@ @ 0x003DF96C
// match: ??_7type_3DF9A0@@6B@ @ 0x003DF9A0
// match: ??_7type_3DF9AC@@6B@ @ 0x003DF9AC
// match: ??_7type_3DF9B8@@6B@ @ 0x003DF9B8
// match: ??_7type_3DF9C4@@6B@ @ 0x003DF9C4
// match: ??_C@_0CJ@JHPMCDDO@?7?7Creating?5GodAsset?3?5DFF?5collide@ @ 0x003DF9D0
// match: ??_C@_0CK@HGNOMEJE@?7?7Creating?5GodAsset?3?5DFF?5geometr@ @ 0x003DF9FC
// match: ??_C@_0DA@NFJFHIND@?7?7Creating?5GodAsset?3?5texture?5dic@ @ 0x003DFA28
// match: ??_7type_3DFA58@@6B@ @ 0x003DFA58
// match: ??_7type_3DFA64@@6B@ @ 0x003DFA64
// match: ??_C@_0EL@GJCDIFDO@Clump?5could?5not?5be?5dereferenced?4@ @ 0x003DFA70
// match: ??_7type_3DFABC@@6B@ @ 0x003DFABC
// match: ??_7type_3DFAC8@@6B@ @ 0x003DFAC8
// match: ??_7type_3DFAD4@@6B@ @ 0x003DFAD4
// match: ??_7type_3DFAE0@@6B@ @ 0x003DFAE0
// match: ??_7type_3DFAEC@@6B@ @ 0x003DFAEC
// match: ??_7type_3DFAF8@@6B@ @ 0x003DFAF8
// match: ??_7type_3DFB04@@6B@ @ 0x003DFB04
// match: ??_7type_3DFB10@@6B@ @ 0x003DFB10
// match: ??_7type_3DFB1C@@6B@ @ 0x003DFB1C
// match: ??_7type_3DFB28@@6B@ @ 0x003DFB28
// match: ??_7type_3DFB34@@6B@ @ 0x003DFB34
// match: ??_7type_3DFB40@@6B@ @ 0x003DFB40
// match: ??_7type_3DF8D8_base@@6B@ @ 0x003DF8D8
// match: ??_7type_3DFB4C@@6B@ @ 0x003DFB4C
// match: ??_7type_44E8D8_248@@6B@ @ 0x003DFB58
// sp-match: ??0type_3DF8D8_base@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00122120
// sp-match: ?vf_000@type_3DF8D8_base@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00061DA0
type_3DF8D8_base::type_3DF8D8_base(const type_3DF8D8_04 &arg_0)
{
    unk_04 = arg_0;
    unk_0E = 0;
    unk_0C = 0;
}

RwInt32 type_3DF8D8_base::vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4)
{
    return 1;
}

// match: ??1type_3DF8D8_base@@QAE@XZ @ 0x0018F440
// sp-match: ??1type_3DF8D8_base@@QAE@XZ @ 0x00122150
type_3DF8D8_base::~type_3DF8D8_base()
{
}

// match: ?sub_18F460@@YAXPAH@Z @ 0x0018F460
// sp-match: ?sub_18F460@@YAXPAH@Z @ 0x00122160
// The size of each kind's object (arg_0, by kind; 60 kinds).
void sub_18F460(RwInt32 *arg_0)
{
    arg_0[0] = 0x10;
    arg_0[2] = 0x14;
    arg_0[1] = 0x14;
    arg_0[3] = 0x58;
    arg_0[4] = 0x48;
    arg_0[5] = 0x48;
    arg_0[25] = 0x44;
    arg_0[38] = 0x1C;
    arg_0[27] = 0x20;
    arg_0[28] = 0x20;
    arg_0[29] = 0x20;
    arg_0[30] = 0x1C;
    arg_0[42] = 0x30;
    arg_0[31] = 0x18;
    arg_0[32] = 0x18;
    arg_0[33] = 0x18;
    arg_0[34] = 0x18;
    arg_0[35] = 0x28;
    arg_0[36] = 0x28;
    arg_0[37] = 0x28;
    arg_0[6] = 0x40;
    arg_0[7] = 0x34;
    arg_0[8] = 0x20;
    arg_0[9] = 0x2C;
    arg_0[10] = 0x1C;
    arg_0[11] = 0x1C;
    arg_0[12] = 0x1C;
    arg_0[13] = 0x1C;
    arg_0[15] = 0x14;
    arg_0[14] = 0x1C;
    arg_0[16] = 0x14;
    arg_0[17] = 0x10;
    arg_0[18] = 0x14;
    arg_0[19] = 0x10;
    arg_0[20] = 0x10;
    arg_0[21] = 0x10;
    arg_0[22] = 0x10;
    arg_0[23] = 0x10;
    arg_0[24] = 0x14;
    arg_0[26] = 0x1C;
    arg_0[39] = 0x14;
    arg_0[40] = 0x14;
    arg_0[41] = 0x14;
    arg_0[43] = 0x20;
    arg_0[46] = 0x34;
    arg_0[44] = 0x34;
    arg_0[45] = 0x14;
    arg_0[47] = 0x38;
    arg_0[48] = 0x10;
    arg_0[49] = 0x10;
    arg_0[50] = 0x1C;
    arg_0[51] = 0x1C;
    arg_0[52] = 0x10;
    arg_0[53] = 0x10;
    arg_0[54] = 0x24;
    arg_0[55] = 0x18;
    arg_0[56] = 0x14;
    arg_0[57] = 0x18;
    arg_0[58] = 0x2C;
    arg_0[59] = 0x14;
}

// match: ?sub_18F710@@YAHH@Z @ 0x0018F710
// sp-match: ?sub_18F710@@YAHH@Z @ 0x001222C0
// The size of kind arg_0's object (-1 for none).
RwInt32 sub_18F710(RwInt32 arg_0)
{
    RwInt32 var_F0[60];

    memset(var_F0, -1, sizeof(var_F0));
    sub_18F460(var_F0);
    return var_F0[arg_0];
}

// match: ?sub_18F750@@YAHXZ @ 0x0018F750
// sp-match: ?sub_18F750@@YAHXZ @ 0x00122300
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The largest kind's size.
RwInt32 sub_18F750()
{
    RwInt32 var_FC;
    RwInt32 var_F8;
    RwInt32 local_F4;
    RwInt32 local_F0[60];

    memset(local_F0, -1, sizeof(local_F0));
    sub_18F460(local_F0);
    local_F4 = 0;
    var_F8 = 0;
    for (var_FC = 0; var_FC < 60; var_FC++)
    {
        if (local_F0[var_FC] > local_F4)
        {
            local_F4 = local_F0[var_FC];
            var_F8 = var_FC;
        }
    }
    return local_F4;
}

// match: ?sub_18F800@type_495F0@@QAEHPAUtype_18F800@@@Z @ 0x0018F800
// sp-match: ?sub_18F800@type_495F0@@QAEHPAUtype_18F800@@@Z @ 0x00125A60
RwInt32 type_495F0::sub_18F800(type_18F800 *arg_0)
{
    type_3DF8D8 *var_4;

    var_4 = sub_198800(&arg_0->unk_04);
    return ((RwInt32)((type_3DF9C4 *)var_4)->sub_190A10());
}

// match: ?sub_18F830@type_1917A0@@QAEPAURpClump@@PAUtype_1917A0_10@@@Z @ 0x0018F830
// sp-match: ?sub_18F830@type_1917A0@@QAEPAURpClump@@PAUtype_1917A0_10@@@Z @ 0x00125A80
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RpClump *type_1917A0::sub_18F830(type_1917A0_10 *arg_0)
{
    type_3DF8D8 *var_8;
    type_3DF8D8 *l4;

    l4 = sub_198800(&arg_0->unk_04);
    var_8 = sub_198800((type_3DF8D8_04 *)&l4->unk_14);
    if (!var_8)
        return 0;
    return ((type_3DF9C4 *)(RpClump *)var_8)->sub_190A10();
}

// match: ??0type_3DF8E4@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x0018F880
// sp-match: ??0type_3DF8E4@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00122380
type_3DF8E4::type_3DF8E4(const type_3DF8D8_04 &arg_0)
    : type_3DF8D8_base(arg_0)
{
    unk_10 = 0;
}

// match: ?sub_18F8B0@@YAHPAUtype_3DF8D8@@HPAX@Z @ 0x0018F8B0
// sp-match: ?sub_18F8B0@@YAHPAUtype_3DF8D8@@HPAX@Z @ 0x001223D0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// A variable's value as a dword into *arg_8 (a callback of sub_198900's).
RwInt32 sub_18F8B0(type_3DF8D8 *arg_0, RwInt32 arg_4, void *arg_8)
{
    RwInt32 var_8;
    RwInt32 *l4;

    l4 = (RwInt32 *)arg_8;
    var_8 = arg_0->unk_10;
    *l4 = var_8;
    return 0;
}

// match: ?sub_18F8E0@@YAHPAUtype_3DF8D8@@HPAX@Z @ 0x0018F8E0
// sp-match: ?sub_18F8E0@@YAHPAUtype_3DF8D8@@HPAX@Z @ 0x001223E0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The same as a word.
RwInt32 sub_18F8E0(type_3DF8D8 *arg_0, RwInt32 arg_4, void *arg_8)
{
    RwInt16 *l4;

    l4 = (RwInt16 *)arg_8;
    *l4 = arg_0->get_unk_10_w();
    return 0;
}

// match: ?sub_18F910@@YAHPAUtype_3DF8D8@@HPAX@Z @ 0x0018F910
// sp-match: ?sub_18F910@@YAHPAUtype_3DF8D8@@HPAX@Z @ 0x00122400
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The same as a byte.
RwInt32 sub_18F910(type_3DF8D8 *arg_0, RwInt32 arg_4, void *arg_8)
{
    RwUInt8 var_5;
    RwUInt8 *l4;

    l4 = (RwUInt8 *)arg_8;
    var_5 = arg_0->unk_10_b;
    *l4 = var_5;
    return 0;
}

// match: ??0type_3DF8F0@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x0018F940
// sp-match: ??0type_3DF8F0@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00125AB0
type_3DF8F0::type_3DF8F0(const type_3DF8D8_04 &arg_0)
    : type_3DF8D8_base(arg_0)
{
    unk_24 = 0;
    unk_20 = 0;
    unk_28.unk_00 = 0xFF;
}

// match: ?vf_000@type_3DF8F0@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x0018F9E0
// sp-match: ?vf_000@type_3DF8F0@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00122420
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Registers it (event 0x1C), or reads its dictionary: kept as it is read
// (unk_0C 2), or read as a texture dictionary or a platform-independent one
// and made current (unk_0C 0), then registered with its dictionary.
RwInt32 type_3DF8F0::vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4)
{
    RwInt32 var_3C;
    RwTexDictionary *w38;
    RwInt32 ebp_34;
    RwTexDictionary *var_30;
    type_3DF8D8 *v2C;
    RwChunkHeaderInfo lcl_28;
    RwChunkHeaderInfo v14;

    if (arg_4->unk_08 == 0x1C)
    {
        if (unk_0C)
            RtlEnterCriticalSection(&dword_44BFB8);
        sub_198900((type_3DF8D8_04 *)&unk_28.unk_04, 6, 0, 0, 0, 0);
        if (unk_0C)
            RtlLeaveCriticalSection(&dword_44BFB8);
        return 1;
    }
    if (unk_0C == 2)
    {
        unk_24 = 0;
        RwStreamReadChunkHeaderInfo(arg_0, &v14);
        if (v14.type == 0x16)
        {
            ebp_34 = unk_10;
            unk_24 = RwTexDictionaryStreamRead(arg_0, (void *)ebp_34);
            RtlEnterCriticalSection(&dword_44BFB8);
            sub_142A10();
            RtlLeaveCriticalSection(&dword_44BFB8);
        }
    }
    else if (unk_0C == 0)
    {
#ifdef CODFH_SP
        // shape: one chunk header for both kinds (SP 0x122420's frame is 0x14, not 0x28)
        RwStreamReadChunkHeaderInfo(arg_0, &v14);
        switch (v14.type)
#else
        RwStreamReadChunkHeaderInfo(arg_0, &lcl_28);
        switch (lcl_28.type)
#endif
        {
        case 0x16:
            unk_24 = sub_144740(arg_0, 1);
            break;
        case 0x23:
            var_30 = RtPITexDictionaryStreamRead(arg_0);
            unk_24 = var_30;
            RwTexDictionarySetCurrent(unk_24);
            break;
        }
        v2C = (type_3DF8D8 *)sub_198900((type_3DF8D8_04 *)&unk_28.unk_04, 6, 0, 0, 0, 0);
        w38 = unk_24;
        v2C->unk_10 = (RwUInt32)w38;
        var_3C = unk_20;
        v2C->unk_14 = var_3C;
    }
    return 1;
}

// match: ??0type_3DF8FC@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x0018FB70
// sp-match: ??0type_3DF8FC@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00125AF0
type_3DF8FC::type_3DF8FC(const type_3DF8D8_04 &arg_0)
    : type_3DF8D8_base(arg_0)
{
    unk_10 = 0;
    unk_14 = 0;
    unk_24.inf.z = 0;
    unk_24.inf.y = 0;
    unk_24.inf.x = 0;
    unk_24.sup.z = 0;
    unk_24.sup.y = 0;
    unk_24.sup.x = 0;
    unk_3C = 0;
}

// match: ?sub_18FC20@@YAPAURpMaterial@@PAU1@PAX@Z @ 0x0018FC20
// sp-match: ?sub_18FC20@@YAPAURpMaterial@@PAU1@PAX@Z @ 0x00122560
// A model material's hold (arg_4 set) or release on the animated textures.
RpMaterial *sub_18FC20(RpMaterial *arg_0, void *arg_4)
{
    if (arg_4)
        unk_4E5CC8.sub_144590(arg_0, -1);
    else
        unk_4E5CC8.sub_1444B0(arg_0, -1);
    return arg_0;
}

// match: ?sub_18FC50@@YAPAURpAtomic@@PAU1@PAX@Z @ 0x0018FC50
// sp-match: ?sub_18FC50@@YAPAURpAtomic@@PAU1@PAX@Z @ 0x00122590
// The same for each material of an atomic's geometry.
RpAtomic *sub_18FC50(RpAtomic *arg_0, void *arg_4)
{
    RpGeometry *var_4;

    var_4 = arg_0->geometry;
    if (var_4)
        RpGeometryForAllMaterials(var_4, sub_18FC20, arg_4);
    return arg_0;
}

// match: ?vf_000@type_3DF8FC@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x0018FC80
// sp-match: ?vf_000@type_3DF8FC@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x001225C0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Takes the clump kept from before (sub_19A8D0) and skips it, or reads the
// clump or clump data file (with its dictionaries current), keeping it
// (sub_19A830); then bounds its atomics' vertices.
RwInt32 type_3DF8FC::vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4)
{
    RpGeometry *var_1BC;
    RpAtomic *w1B8;
    RwLLLink *w1B4;
    RwLLLink *var_1B0;
    RwLLLink *local_1AC;
    RwChar var1A8[0x80];
    RwChar var_128[0x100];
    RwInt32 frm_24;
    RwChunkHeaderInfo var_20;
    RpClump *var_C;
    void *bp_8;
    RwUInt8 var_1;

    if (arg_4->unk_08 == 0x1C)
        return 1;
    var_C = 0;
    bp_8 = sub_19A8D0(arg_4, arg_4->unk_08);
    var_1 = 0;
    if (bp_8)
    {
        var_C = (RpClump *)bp_8;
        unk_18.sub_129620(var_C);
        RwStreamSkip(arg_0, arg_4->unk_08 - 0x1C);
        var_1 = 1;
    }
    else
    {
        while (!var_1 && RwStreamReadChunkHeaderInfo(arg_0, &var_20))
        {
            if (var_20.type == rwID_CLUMP)
            {
                if (unk_10)
                    RwTexDictionarySetCurrent(unk_10);
                if (unk_14)
                    RtDictSchemaSetCurrentDict(&_rpUVAnimDictSchema, unk_14);
                var_C = RpClumpStreamRead(arg_0);
                sub_19A830(arg_4, var_C, arg_4->unk_08);
                unk_18.sub_129620(var_C);
                sub_FBC10(var_C, arg_4->unk_18);
                var_1 = 1;
            }
            else if (var_20.type == 0x4210)
            {
                if (unk_10)
                    RwTexDictionarySetCurrent(unk_10);
                if (unk_14)
                    RtDictSchemaSetCurrentDict(&_rpUVAnimDictSchema, unk_14);
                frm_24 = 0;
                var_C = sub_EBF40(arg_0, &frm_24);
                if (!frm_24)
                {
                    sprintf(var_128, "\n***********************************************\n");
                    sprintf(var1A8, "***God ID: %x,%x is not a valid .sdf file!***", unk_04.unk_00, unk_04.unk_04);
                    strcat(var_128, var1A8);
                    sprintf(var1A8, "\n***********************************************");
                    strcat(var_128, var1A8);
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
                    // single player compiles the debug prints out (SP 0x1225C0)
                    sub_19A750(var_128);
#endif
                }
                RpClumpForAllAtomics(var_C, sub_18FC50, (void *)1);
                sub_19A830(arg_4, var_C, arg_4->unk_08);
                unk_18.sub_129620(var_C);
                sub_FBC10(var_C, arg_4->unk_18);
                var_1 = 1;
            }
            else
                RwStreamSkip(arg_0, var_20.length);
        }
    }
    if (var_C)
    {
        local_1AC = rwLinkListGetFirstLLLink(&var_C->atomicList);
        w1B4 = rwLinkListGetTerminator(&var_C->atomicList);
        while (local_1AC != w1B4)
        {
            w1B8 = rwLLLinkGetData(local_1AC, RpAtomic, inClumpLink);
            sub_19B1F0(w1B8->object[0] == 1);
            var_1B0 = local_1AC->next;
            var_1BC = w1B8->geometry;
            if (var_1BC && var_1BC->numVertices > 0 && var_1BC->morphTarget && var_1BC->morphTarget->verts)
            {
                RwBBoxCalculate(&unk_24, var_1BC->morphTarget->verts, var_1BC->numVertices);
                unk_3C = 1;
            }
            local_1AC = var_1B0;
        }
    }
    return 1;
}

// match: ?sub_190040@type_3DF8FC@@QAEPAURwBBox@@XZ @ 0x00190040
// sp-match: ?sub_190040@type_3DF8FC@@QAEPAURwBBox@@XZ @ 0x00122850
RwBBox *type_3DF8FC::sub_190040()
{
    RwBBox *var_4;

    var_4 = 0;
    if (unk_3C)
        var_4 = &unk_24;
    return var_4;
}

// match: ?vf_004@type_3DF8FC@@UAEXXZ @ 0x00190070
// sp-match: ?vf_004@type_3DF8FC@@UAEXXZ @ 0x00122860
void type_3DF8FC::vf_004()
{
    RpClump *var_4;

    var_4 = unk_18.unk_08;
    if (var_4)
        RpClumpForAllAtomics(var_4, sub_18FC50, 0);
    unk_18.sub_129940(0);
}

// match: ??0type_3DF9A0@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x001900B0
// sp-match: ??0type_3DF9A0@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00122890
type_3DF9A0::type_3DF9A0(const type_3DF8D8_04 &arg_0)
    : type_3DF8D8_base(arg_0)
{
    unk_10 = 0;
    unk_14.unk_00 = 0xFF;
    unk_20.unk_00 = 0xFF;
}

// match: ?vf_000@type_3DF9A0@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00190140
// sp-match: ?vf_000@type_3DF9A0@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x001228E0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Registering it hands its reference to the texture dictionary, or
// registers the model; reading it reads the dictionary (and makes it
// current) and hands it to either.
RwInt32 type_3DF9A0::vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4)
{
    struct RtDict *var_14;
    struct RtDict *lv_10;
    type_3DF8FC *var_C;
    type_3DF8F0 *bp_8;
    type_3DF8F0 *bp_4;

    if (arg_4->unk_08 == 0x1C)
    {
        bp_4 = (type_3DF8F0 *)sub_198900((type_3DF8D8_04 *)&unk_14.unk_04, 7, 0, 0, 0, 0);
        if (bp_4)
            bp_4->unk_28 = unk_20;
        else
        {
            if (unk_0C)
                RtlEnterCriticalSection(&dword_44BFB8);
            sub_198900((type_3DF8D8_04 *)&unk_20.unk_04, 6, 0, 0, 0, 0);
            if (unk_0C)
                RtlLeaveCriticalSection(&dword_44BFB8);
        }
        return 1;
    }
    if (RwStreamFindChunk(arg_0, 0x2B, 0, 0))
    {
        unk_10 = RtDictSchemaStreamReadDict(&_rpUVAnimDictSchema, arg_0);
        if (unk_10)
            RtDictSchemaSetCurrentDict(&_rpUVAnimDictSchema, unk_10);
    }
    if (!unk_0C)
    {
        bp_8 = (type_3DF8F0 *)sub_198900((type_3DF8D8_04 *)&unk_14.unk_04, 7, 0, 0, 0, 0);
        if (bp_8)
        {
            bp_8->unk_28 = unk_20;
            lv_10 = unk_10;
            bp_8->unk_20 = (RwInt32)lv_10;
        }
        else
        {
            var_C = (type_3DF8FC *)sub_198900((type_3DF8D8_04 *)&unk_20.unk_04, 6, 0, 0, 0, 0);
            var_14 = unk_10;
            var_C->unk_14 = var_14;
        }
    }
    return 1;
}

// match: ?vf_004@type_3DF9A0@@UAEXXZ @ 0x001902D0
// sp-match: ?vf_004@type_3DF9A0@@UAEXXZ @ 0x00122A20
void type_3DF9A0::vf_004()
{
    if (unk_10)
    {
        RtDictDestroy(unk_10);
        unk_10 = 0;
    }
}

// match: ??0type_3DF9AC@@QAE@ABUtype_3DF8D8_04@@H@Z @ 0x00190300
// sp-match: ??0type_3DF9AC@@QAE@ABUtype_3DF8D8_04@@H@Z @ 0x00122A40
type_3DF9AC::type_3DF9AC(const type_3DF8D8_04 &arg_0, RwInt32 arg_4)
    : type_3DF8D8_base(arg_0)
{
    unk_1C = arg_4;
}

// match: ?vf_008@type_3DF9AC@@UAEHXZ @ 0x00190360
// sp-match: ?vf_008@type_3DF9AC@@UAEHXZ @ 0x00122A70
RwInt32 type_3DF9AC::vf_008()
{
    return unk_1C;
}

// match: ?vf_000@type_3DF9AC@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00190380
// sp-match: ?vf_000@type_3DF9AC@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00122A80
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_3DF9AC::vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4)
{
    RwInt32 var_8;
    type_3DF8D8_base *l4;

    RwStreamRead(arg_0, &unk_10, arg_4->unk_08 - 0x1C);
    if (!unk_10.unk_04.unk_00 && !unk_10.unk_04.unk_04)
        return 1;
    switch (unk_1C)
    {
    case 8:
        if (unk_0C == 1)
            sub_198900((type_3DF8D8_04 *)&unk_10.unk_04, 0x30, 0, 0, 0, 0);
        else
        {
            l4 = (type_3DF8D8_base *)sub_198900((type_3DF8D8_04 *)&unk_10.unk_04, 3, 0, 0, 0, 0);
            var_8 = unk_0C;
            l4->unk_0C = var_8;
        }
        break;
    }
    return 1;
}

// match: ??0type_3DF9B8@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00190440
// sp-match: ??0type_3DF9B8@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00122B00
type_3DF9B8::type_3DF9B8(const type_3DF8D8_04 &arg_0)
    : type_3DF8D8_base(arg_0)
{
    unk_20 = 0;
    unk_24 = 0;
    unk_28 = 0;
}

// match: ?sub_1904B0@type_3DF9B8@@QAEXP6AXHHH@ZHH@Z @ 0x001904B0
// sp-match: ?sub_1904B0@type_3DF9B8@@QAEXP6AXHHH@ZHH@Z @ 0x00122B30
void type_3DF9B8::sub_1904B0(void (*arg_0)(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8), RwInt32 arg_4, RwInt32 arg_8)
{
    unk_20 = arg_0;
    unk_24 = arg_4;
    unk_28 = arg_8;
}

// match: ?vf_000@type_3DF9B8@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x001904E0
// sp-match: ?vf_000@type_3DF9B8@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00122B50
RwInt32 type_3DF9B8::vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4)
{
    RwStreamRead(arg_0, &unk_10, arg_4->unk_08 - 0x1C);
    sub_198900((type_3DF8D8_04 *)&unk_10.unk_04, unk_1C, unk_20, unk_24, unk_28, 0);
    return 1;
}

// match: ??0type_3DF9C4@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00190540
// sp-match: ??0type_3DF9C4@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00122BA0
type_3DF9C4::type_3DF9C4(const type_3DF8D8_04 &arg_0)
    : type_3DF8D8_base(arg_0)
{
    unk_44 = -1;
}

// match: ?vf_000@type_3DF9C4@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00190640
// sp-match: ?vf_000@type_3DF9C4@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x001270F0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Reads its six references and keeps its texture dictionary, UV animation
// dictionary, model and second model (registering what they need), a
// variable for unk_54 and a registration (kind 9) for unk_44; kept as it
// is (unk_0C 2), it is read by sub_190B20.
RwInt32 type_3DF9C4::vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4)
{
    type_3DF8D8_base *bp_4;
    type_3DF9B8 *var_64;
    type_3DF8D8_base *stk_60;
    type_3DF8D8_base *y5C;
    type_3DF8D8_ref *stk_58;
    type_3DF8D8_base *l54;
    RwInt32 x8;             // unused: the image keeps its slot

    if (unk_0C == 2)
    {
        sub_190B20(arg_0, arg_4);
        get_2A9830();
        return 1;
    }
    type_3DF8D8_ref var50[6];

    memset(var50, 0, sizeof(var50));
    RwStreamRead(arg_0, var50, arg_4->unk_08 - 0x1C);
    unk_38 = *sub_190900(2, var50, 6, 7, 0, &stk_60);
    unk_48 = *sub_190900(6, var50, 6, 0x3A, 1, &bp_4);
    unk_20 = *sub_190900(1, var50, 6, 6, 0, 0);
    unk_2C = *sub_190900(4, var50, 6, 6, 1, &y5C);
    sub_190900(5, var50, 6, 9, 1, &l54);
    stk_58 = sub_190900(3, var50, 6, 1, 0, 0);
    sub_198900((type_3DF8D8_04 *)&stk_58->unk_04, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_18F8B0, 0, (RwInt32)&unk_54, 0);
    ((type_3DF9A0 *)bp_4)->set_unk_14(unk_38);
    ((type_3DF9A0 *)bp_4)->set_unk_20(unk_20);
    var_64 = (type_3DF9B8 *)l54;
    var_64->unk_1C = 1;
    var_64->sub_1904B0((void (*)(RwInt32, RwInt32, RwInt32))sub_18F8B0, 0, (RwInt32)&unk_44);
    return 1;
}

// match: ?sub_1908A0@type_3DF9C4@@QAEPAUtype_3DF8D8_04@@H@Z @ 0x001908A0
// sp-match: ?sub_1908A0@type_3DF9C4@@QAEPAUtype_3DF8D8_04@@H@Z @ 0x00122BF0
// The key of its model, second model, texture dictionary or UV animation
// dictionary (arg_0 0 to 3), or 0.
type_3DF8D8_04 *type_3DF9C4::sub_1908A0(RwInt32 arg_0)
{
    switch (arg_0)
    {
    case 0:
        return &unk_20.unk_04;
    case 1:
        return &unk_2C.unk_04;
    case 2:
        return &unk_38.unk_04;
    case 3:
        return &unk_48.unk_04;
    }
    return 0;
}

// match: ?sub_190900@type_3DF9C4@@QAEPAUtype_3DF8D8_ref@@HPAU2@HHEPAPAUtype_3DF8D8_base@@@Z @ 0x00190900
// sp-match: ?sub_190900@type_3DF9C4@@QAEPAUtype_3DF8D8_ref@@HPAU2@HHEPAPAUtype_3DF8D8_base@@@Z @ 0x00122D20
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The reference of type arg_0 among the arg_8 at arg_4, or 0; with arg_10
// set, what it names is registered as kind arg_C into *arg_14 (else *arg_14
// is cleared).
type_3DF8D8_ref *type_3DF9C4::sub_190900(RwInt32 arg_0, type_3DF8D8_ref *arg_4, RwInt32 arg_8, RwInt32 arg_C,
                                         RwUInt8 arg_10, type_3DF8D8_base **arg_14)
{
    RwInt32 var_C;
    RwUInt32 bp_8;
    RwInt32 bp_4;

    bp_4 = arg_0;
    for (var_C = 0; var_C < arg_8; var_C++)
    {
        bp_8 = get_ref_kind(arg_4[var_C].unk_00, 0x1F);
        if (bp_8 == bp_4)
        {
            if (arg_10)
                *arg_14 = (type_3DF8D8_base *)sub_198900((type_3DF8D8_04 *)&arg_4[var_C].unk_04, arg_C, 0, 0, 0, 0);
            else if (arg_14)
                *arg_14 = 0;
            return &arg_4[var_C];
        }
    }
    return 0;
}

// match: ?sub_1909C0@type_3DF9C4@@QAEPAURtDict@@XZ @ 0x001909C0
// sp-match: ?sub_1909C0@type_3DF9C4@@QAEPAURtDict@@XZ @ 0x00122C30
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Its UV animation dictionary, or 0.
struct RtDict *type_3DF9C4::sub_1909C0()
{
    RwInt32 var_C;
    struct RtDict *bp_8;
    type_3DF9A0 *bp_4;

    bp_8 = 0;
    bp_4 = (type_3DF9A0 *)sub_198800(&unk_48.unk_04);
    if (bp_4)
    {
        var_C = bp_4->vf_008();
        bp_8 = bp_4->unk_10;
    }
    return bp_8;
}

// match: ?sub_190A10@type_3DF9C4@@QAEPAURpClump@@XZ @ 0x00190A10
// sp-match: ?sub_190A10@type_3DF9C4@@QAEPAURpClump@@XZ @ 0x00122C60
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Its model's clump.
RpClump *type_3DF9C4::sub_190A10()
{
    RpClump *var_C;
    RwInt32 bp_8;
    type_3DF8FC *bp_4;

    bp_4 = (type_3DF8FC *)sub_198800(&unk_20.unk_04);
    bp_8 = bp_4->vf_008();
    var_C = bp_4->unk_18.unk_08;
    return var_C;
}

// match: ?sub_190A50@type_3DF9C4@@QAEPAURpClump@@XZ @ 0x00190A50
// sp-match: ?sub_190A50@type_3DF9C4@@QAEPAURpClump@@XZ @ 0x00122C80
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Its second model's clump, or 0.
RpClump *type_3DF9C4::sub_190A50()
{
    RpClump *var_8;
    type_3DF8FC *l4;

    l4 = (type_3DF8FC *)sub_198800(&unk_2C.unk_04);
    if (!l4)
        return 0;
    var_8 = l4->unk_18.unk_08;
    return var_8;
}

// match: ?sub_190A90@type_3DF9C4@@QAEPAURwBBox@@XZ @ 0x00190A90
// sp-match: ?sub_190A90@type_3DF9C4@@QAEPAURwBBox@@XZ @ 0x00122CA0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Its second model's bounds, or 0.
RwBBox *type_3DF9C4::sub_190A90()
{
    RwBBox *var_8;
    type_3DF8FC *l4;

    var_8 = 0;
    l4 = (type_3DF8FC *)sub_198800(&unk_2C.unk_04);
    if (l4)
        var_8 = l4->sub_190040();
    return var_8;
}

// match: ?vf_004@type_3DF9C4@@UAEXXZ @ 0x00190AD0
// sp-match: ?vf_004@type_3DF9C4@@UAEXXZ @ 0x00122CC0
// Lets its UV animation dictionary go.
void type_3DF9C4::vf_004()
{
    type_3DF8D8 *var_4;

    var_4 = sub_198800(&unk_48.unk_04);
    if (var_4)
    {
        sub_198F00(&unk_48.unk_04);
        unk_48.unk_04.unk_00 = 0;
        unk_48.unk_04.unk_04 = 0;
    }
}

// match: ?sub_190B20@type_3DF9C4@@QAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00190B20
// sp-match: ?sub_190B20@type_3DF9C4@@QAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00125B40
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Kept as it is (unk_0C 2), the model object is followed in the stream by
// its UV animation dictionary, texture dictionary, model and collision
// model: each not yet made is made (sub_199010) and read into the arena
// unk_10, the texture dictionary made current, and the rest skipped.
RwInt32 type_3DF9C4::sub_190B20(RwStream *arg_0, type_3DF8D8_ev *arg_4)
{
    RwChar v160[0x100];
    type_3DF8D8_ref bp_58[6];
    type_3DF8FC *local_10;
    type_3DF8D8_base *var_C;
    type_3DF8F0 *bp_8;
    type_3DF8D8_base *bp_4;

    RwStreamRead(arg_0, bp_58, arg_4->unk_08 - 0x1C);
    type_3DF8D8_ev var_17C;

    local_10 = 0;
    var_C = 0;
    bp_8 = 0;
    bp_4 = 0;
    RtlEnterCriticalSection(&dword_44BFB8);
    unk_48 = *sub_190900(6, bp_58, 6, 0x3A, 0, 0);
    unk_38 = *sub_190900(2, bp_58, 6, 7, 0, 0);
    unk_20 = *sub_190900(1, bp_58, 6, 6, 0, 0);
    unk_2C = *sub_190900(4, bp_58, 6, 6, 0, 0);
    RtlLeaveCriticalSection(&dword_44BFB8);
    RwStreamRead(arg_0, &unk_44, 4);
    RwStreamRead(arg_0, &unk_54, 4);

    RwStreamRead(arg_0, &var_17C, 0x1C);
    if (!sub_198710(&var_17C.unk_0C.unk_04))
    {
        RtlEnterCriticalSection(&dword_44BFB8);
        bp_4 = (type_3DF8D8_base *)sub_199010(&var_17C.unk_0C.unk_04, 0x3A);
        bp_4->unk_0C = 2;
        sub_2DAAF0(get_unk_10());
        RtlLeaveCriticalSection(&dword_44BFB8);
        bp_4->vf_000(arg_0, &var_17C);
        RtlEnterCriticalSection(&dword_44BFB8);
        sub_2DA340();
        sub_198FE0((type_3DF8D8_base *)((type_199010 *)bp_4));
        RtlLeaveCriticalSection(&dword_44BFB8);
    }
    else
        RwStreamSkip(arg_0, var_17C.unk_08 - 0x1C);

    RwStreamRead(arg_0, &var_17C, 0x1C);
    if (!sub_198710(&var_17C.unk_0C.unk_04))
    {
        RtlEnterCriticalSection(&dword_44BFB8);
        call_unk_1C(&var_17C.unk_0C.unk_04, 7);
        sprintf(v160, "\t\tCreating GodAsset: texture dictionary (%x,%x)", var_17C.unk_0C.unk_04.unk_00,
                var_17C.unk_0C.unk_04.unk_04);
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
        // single player compiles the debug prints out (SP 0x125B40)
        sub_19A750(v160);
#endif
        bp_8 = (type_3DF8F0 *)sub_199010(&var_17C.unk_0C.unk_04, 7);
        bp_8->unk_0C = 2;
        bp_8->unk_10 = get_unk_10();
        RtlLeaveCriticalSection(&dword_44BFB8);
        bp_8->vf_000(arg_0, &var_17C);
        RtlEnterCriticalSection(&dword_44BFB8);
        sub_198FE0((type_3DF8D8_base *)((type_199010 *)bp_8));
        bp_8->unk_28 = unk_20;
        if (bp_8->get_unk_24())
            RwTexDictionarySetCurrent(bp_8->get_unk_24());
        RtlLeaveCriticalSection(&dword_44BFB8);
    }
    else
        RwStreamSkip(arg_0, var_17C.unk_08 - 0x1C);

    RwStreamRead(arg_0, &var_17C, 0x1C);
    if (!sub_198710(&var_17C.unk_0C.unk_04))
    {
        RtlEnterCriticalSection(&dword_44BFB8);
        sprintf(v160, "\t\tCreating GodAsset: DFF geometry (%x,%x)", var_17C.unk_0C.unk_04.unk_00,
                var_17C.unk_0C.unk_04.unk_04);
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
        sub_19A750(v160);
#endif
        call_unk_1C(&var_17C.unk_0C.unk_04, 6);
        local_10 = (type_3DF8FC *)sub_199010(&var_17C.unk_0C.unk_04, 6);
        if (!bp_8)
            bp_8 = (type_3DF8F0 *)sub_198710(&bp_58[0].unk_04);
        if (bp_8)
            local_10->unk_10 = bp_8->get_unk_24();
        sub_2DAAF0(get_unk_10());
        RtlLeaveCriticalSection(&dword_44BFB8);
        local_10->vf_000(arg_0, &var_17C);
        RtlEnterCriticalSection(&dword_44BFB8);
        sub_2DA340();
        sub_198FE0((type_3DF8D8_base *)((type_199010 *)local_10));
        RtlLeaveCriticalSection(&dword_44BFB8);
    }
    else
        RwStreamSkip(arg_0, var_17C.unk_08 - 0x1C);

    RwStreamRead(arg_0, &var_17C, 0x1C);
    if (!sub_198710(&var_17C.unk_0C.unk_04))
    {
        RtlEnterCriticalSection(&dword_44BFB8);
        sprintf(v160, "\t\tCreating GodAsset: DFF collide (%x,%x)", var_17C.unk_0C.unk_04.unk_00,
                var_17C.unk_0C.unk_04.unk_04);
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
        sub_19A750(v160);
#endif
        call_unk_1C(&var_17C.unk_0C.unk_04, 6);
        var_C = (type_3DF8D8_base *)sub_199010(&var_17C.unk_0C.unk_04, 6);
        sub_2DAAF0(get_unk_10());
        RtlLeaveCriticalSection(&dword_44BFB8);
        var_C->vf_000(arg_0, &var_17C);
        RtlEnterCriticalSection(&dword_44BFB8);
        sub_2DA340();
        sub_198FE0((type_3DF8D8_base *)((type_199010 *)var_C));
        RtlLeaveCriticalSection(&dword_44BFB8);
    }
    else
        RwStreamSkip(arg_0, var_17C.unk_08 - 0x1C);

    RwTexDictionarySetCurrent(0);
    return 1;
}

// match: ??0type_3DFA58@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00191230
// sp-match: ??0type_3DFA58@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00122CF0
type_3DFA58::type_3DFA58(const type_3DF8D8_04 &arg_0)
    : type_3DF8D8_base(arg_0)
{
}

// match: ?vf_008@type_3DFA58@@UAEHXZ @ 0x00191260
// sp-match: ?vf_008@type_3DFA58@@UAEHXZ @ 0x00122D10
RwInt32 type_3DFA58::vf_008()
{
    return 0x30;
}

// match: ?vf_000@type_3DFA58@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00191270
// sp-match: ?vf_000@type_3DFA58@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00126000
RwInt32 type_3DFA58::vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4)
{
    type_3DF8D8_ref var_48[6];
    type_3DF8D8_base *var_4C;

    RwStreamRead(arg_0, var_48, arg_4->unk_08 - 0x1C);
    sub_191300(4, var_48, 6, 6, 1, &var_4C);
    return 0;
}

// match: ?sub_191300@type_3DFA58@@QAEPAUtype_3DF8D8_ref@@HPAU2@HHEPAPAUtype_3DF8D8_base@@@Z @ 0x00191300
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// As type_3DF9C4's sub_190900.
type_3DF8D8_ref *type_3DFA58::sub_191300(RwInt32 arg_0, type_3DF8D8_ref *arg_4, RwInt32 arg_8, RwInt32 arg_C,
                                         RwUInt8 arg_10, type_3DF8D8_base **arg_14)
{
    RwUInt32 var_8;
    RwInt32 l4;

    for (l4 = 0; l4 < arg_8; l4++)
    {
        var_8 = get_ref_kind_direct(arg_4[l4].unk_00, 0x1F);
        if (var_8 == arg_0)
        {
            if (arg_10)
                *arg_14 = (type_3DF8D8_base *)sub_198900((type_3DF8D8_04 *)&arg_4[l4].unk_04, arg_C, 0, 0, 0, 0);
            else if (arg_14)
                *arg_14 = 0;
            return &arg_4[l4];
        }
    }
    return 0;
}

// match: ??0type_3DFA64@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x001913B0
// sp-match: ??0type_3DFA64@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00122DB0
type_3DFA64::type_3DFA64(const type_3DF8D8_04 &arg_0)
    : type_3DF8D8_base(arg_0)
{
    unk_44 = -1;
}

#ifdef CODFH_SP
// shape: single player's last two references (cases 7 and 8) name sub_18F8B0's twin (unit_192BE0,
// folded into SP 0x1223D0), so its compiler does not share case 7's call with cases 4-6 (SP 0x122DF0)
RwInt32 sp_sub_18F8B0_twin(type_3DF8D8 *arg_0, RwInt32 arg_4, void *arg_8);
#define sub_18F8B0_late sp_sub_18F8B0_twin
#else
#define sub_18F8B0_late sub_18F8B0
#endif
// match: ?vf_000@type_3DFA64@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00191450
// sp-match: ?vf_000@type_3DFA64@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00122DF0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_3DFA64::vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4)
{
    type_3DF9B8 *var_70;
    RwInt32 l6C;
    type_3DF8D8_base *local_68;
    RwUInt32 var_64;
    type_3DF8D8_ref l60[8];

    RwStreamRead(arg_0, l60, arg_4->unk_08 - 0x1C);
    for (l6C = 0; l6C < 8; l6C++)
    {
        var_64 = get_ref_kind(l60[l6C].unk_00, 0x1F);
        switch (var_64)
        {
        case 1:
            unk_1C = l60[l6C];
            local_68 = (type_3DF8D8_base *)sub_198900((type_3DF8D8_04 *)&l60[l6C].unk_04, 8, 0, 0, 0, 0);
            local_68->set_unk_0C(unk_0C);
            break;
        case 2:
            unk_10 = l60[l6C];
            local_68 = (type_3DF8D8_base *)sub_198900((type_3DF8D8_04 *)&l60[l6C].unk_04, 8, 0, 0, 0, 0);
            local_68->set_unk_0C(unk_0C);
            break;
        case 3:
            unk_28 = l60[l6C];
            local_68 = (type_3DF8D8_base *)sub_198900((type_3DF8D8_04 *)&l60[l6C].unk_04, 8, 0, 0, 0, 0);
            local_68->set_unk_0C(unk_0C);
            break;
        case 4:
            sub_198900((type_3DF8D8_04 *)&l60[l6C].unk_04, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_18F8B0, 0, (RwInt32)&unk_38, 0);
            break;
        case 5:
            sub_198900((type_3DF8D8_04 *)&l60[l6C].unk_04, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_18F8B0, 0, (RwInt32)&unk_3C, 0);
            break;
        case 6:
            sub_198900((type_3DF8D8_04 *)&l60[l6C].unk_04, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_18F8B0, 0, (RwInt32)&unk_40, 0);
            break;
        case 7:
            sub_198900((type_3DF8D8_04 *)&l60[l6C].unk_04, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_18F8B0_late, 0, (RwInt32)&unk_34, 0);
            break;
        case 8:
            var_70 = (type_3DF9B8 *)sub_198900((type_3DF8D8_04 *)&l60[l6C].unk_04, 9, 0, 0, 0, 0);
            var_70->unk_1C = 1;
            var_70->sub_1904B0((void (*)(RwInt32, RwInt32, RwInt32))sub_18F8B0_late, 0, (RwInt32)&unk_44);
            break;
        }
    }
    return 1;
}

// match: ?sub_1917A0@type_1917A0@@QAEPAUtype_1908A0@@XZ @ 0x001917A0
// sp-match: ?sub_1917A0@type_1917A0@@QAEPAUtype_1908A0@@XZ @ 0x00122F90
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
type_1908A0 *type_1917A0::sub_1917A0()
{
    type_1908A0 *var_8;
    type_3DF8D8 *l4;

    l4 = sub_198800(&unk_20);
    var_8 = (type_1908A0 *)sub_198800((type_3DF8D8_04 *)&l4->unk_14);
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
    // single player compiles the debug print out (SP 0x122F90)
    if (!var_8)
        sub_19A750("Clump could not be dereferenced. Did you forget to trigger a clump stream?");
#endif
    return var_8;
}

// match: ?sub_1917F0@type_1917A0@@QAEPAUtype_1908A0@@XZ @ 0x001917F0
// sp-match: ?sub_1917F0@type_1917A0@@QAEPAUtype_1908A0@@XZ @ 0x00122FB0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
type_1908A0 *type_1917A0::sub_1917F0()
{
    type_1908A0 *var_8;
    type_3DF8D8 *l4;

    l4 = sub_198800((type_3DF8D8_04 *)&unk_14);
    var_8 = (type_1908A0 *)sub_198800((type_3DF8D8_04 *)&l4->unk_14);
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
    // single player compiles the debug print out (SP 0x122FB0)
    if (!var_8)
        sub_19A750("Clump could not be dereferenced. Did you forget to trigger a clump stream?");
#endif
    return var_8;
}

// match: ?sub_191840@type_1917A0@@QAEPAUtype_1908A0@@XZ @ 0x00191840
// sp-match: ?sub_191840@type_1917A0@@QAEPAUtype_1908A0@@XZ @ 0x00122FD0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
type_1908A0 *type_1917A0::sub_191840()
{
    type_1908A0 *var_8;
    type_3DF8D8 *l4;

    l4 = sub_198800(&unk_28.unk_04);
    var_8 = (type_1908A0 *)sub_198800((type_3DF8D8_04 *)&l4->unk_14);
    if (!var_8)
        return 0;
    return var_8;
}

// match: ??0type_3DFABC@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00191880
// sp-match: ??0type_3DFABC@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00123000
type_3DFABC::type_3DFABC(const type_3DF8D8_04 &arg_0)
    : type_3DF8D8_base(arg_0)
{
}

// match: ?vf_000@type_3DFABC@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00191950
// sp-match: ?vf_000@type_3DFABC@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00126080
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_3DFABC::vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4)
{
    RwInt32 var_40;
    type_3DF8D8_ref l3C[5];

    RwStreamRead(arg_0, l3C, arg_4->unk_08 - 0x1C);
    for (var_40 = 0; var_40 < 5; var_40++)
    {
        switch (get_ref_kind(l3C[var_40].unk_00, 0x1F))
        {
        case 1:
            unk_20 = l3C[var_40];
            if (!unk_0C)
                sub_198900((type_3DF8D8_04 *)&l3C[var_40].unk_04, 3, 0, 0, 0, 0);
            else
                sub_198900((type_3DF8D8_04 *)&l3C[var_40].unk_04, 0x30, 0, 0, 0, 0);
            break;
        case 3:
            unk_38 = l3C[var_40];
            if (!unk_0C)
                sub_198900((type_3DF8D8_04 *)&l3C[var_40].unk_04, 3, 0, 0, 0, 0);
            else
                sub_198900((type_3DF8D8_04 *)&l3C[var_40].unk_04, 0x30, 0, 0, 0, 0);
            break;
        case 4:
            sub_198900((type_3DF8D8_04 *)&l3C[var_40].unk_04, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_191B30,
                       (RwInt32)this, (RwInt32)&unk_44, 0);
            break;
        }
    }
    return 1;
}

// match: ?sub_191B30@@YAHPAUtype_3DF8D8@@HPAX@Z @ 0x00191B30
// sp-match: ?sub_191B30@@YAHPAUtype_3DF8D8@@HPAX@Z @ 0x00123040
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The weapon's variable's callback (arg_4 the weapon): its value into unk_44,
// and for a kept weapon (unk_0C 2) into the level's clump bank slot unk_18
// (or the first free one).
RwInt32 sub_191B30(type_3DF8D8 *arg_0, RwInt32 arg_4, void *arg_8)
{
    RwInt32 var_18;
    RwInt32 var_14;
    RwInt32 lv_10;
    RwInt32 var_C;
    RwInt32 bp_8;
    type_3DFABC *bp_4;

    bp_4 = (type_3DFABC *)arg_4;
    sub_18F8B0(arg_0, arg_4, &bp_4->unk_44);
    if (bp_4->unk_0C == 2)
    {
        bp_8 = bp_4->unk_18;
        if (bp_8 == -1)
        {
            for (var_C = 0; var_C < 3; var_C++)
            {
                lv_10 = dword_4E54E8[var_C];
                if (lv_10 == -1)
                {
                    var_14 = bp_4->unk_44;
                    dword_4E54E8[var_C] = var_14;
                    break;
                }
            }
        }
        else
        {
            var_18 = bp_4->unk_44;
            dword_4E54E8[bp_8] = var_18;
        }
    }
    return 0;
}

// match: ??0type_3DFAC8@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00191BE0
// sp-match: ??0type_3DFAC8@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x001230A0
type_3DFAC8::type_3DFAC8(const type_3DF8D8_04 &arg_0)
    : type_3DF8D8_base(arg_0)
{
}

// match: ?vf_000@type_3DFAC8@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00191C30
// sp-match: ?vf_000@type_3DFAC8@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x001230E0
RwInt32 type_3DFAC8::vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4)
{
    type_3DF8D8_ref var_18[2];
    RwInt32 var_1C;

    RwStreamRead(arg_0, var_18, arg_4->unk_08 - 0x1C);
    for (var_1C = 0; var_1C < 2; var_1C++)
    {
        switch (get_ref_kind(var_18[var_1C].unk_00, 0x1F))
        {
        case 1:
            unk_10 = var_18[var_1C];
            sub_198900((type_3DF8D8_04 *)&var_18[var_1C].unk_04, 3, 0, 0, 0, 0);
            break;
        }
    }
    return 1;
}

// match: ??0type_3DFAD4@@QAE@ABUtype_3DF8D8_04@@H@Z @ 0x00191D30
// sp-match: ??0type_3DFAD4@@QAE@ABUtype_3DF8D8_04@@H@Z @ 0x00123170
type_3DFAD4::type_3DFAD4(const type_3DF8D8_04 &arg_0, RwInt32 arg_4)
    : type_3DF8D8_base(arg_0)
{
    unk_14 = 0;
    unk_18 = -1;
    unk_10 = arg_4;
}

// match: ?vf_008@type_3DFAD4@@UAEHXZ @ 0x00191D80
// sp-match: ?vf_008@type_3DFAD4@@UAEHXZ @ 0x00124C00
RwInt32 type_3DFAD4::vf_008()
{
    return unk_10;
}

// match: ?vf_000@type_3DFAD4@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00191DA0
// sp-match: ?vf_000@type_3DFAD4@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x001231A0
RwInt32 type_3DFAD4::vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4)
{
    type_72900 *var_4;

    unk_14 = RWSMalloc(arg_4->unk_08 - 0x1C, 0x34255); // not an address: a memory hint
    RwStreamRead(arg_0, unk_14, arg_4->unk_08 - 0x1C);
    var_4 = (type_72900 *)sub_72BA0((RwChar *)unk_14);
    switch (unk_10)
    {
    case 10:
        sub_728C0(var_4);
        unk_18 = var_4->unk_04;
        break;
    case 11:
        sub_72920((type_72990 *)var_4);
        unk_18 = var_4->unk_04;
        break;
    case 12:
        sub_729F0((type_72A30 *)var_4);
        unk_18 = var_4->unk_04;
        break;
    case 13:
        sub_72AA0((struct type_67620_74 *)var_4);
        unk_18 = *(RwUInt16 *)&var_4->unk_04;
        break;
    }
    return 1;
}

// match: ?vf_004@type_3DFAD4@@UAEXXZ @ 0x00191EA0
// sp-match: ?vf_004@type_3DFAD4@@UAEXXZ @ 0x00124E50
void type_3DFAD4::vf_004()
{
    void *var_4;

    if (unk_14)
    {
        var_4 = unk_14;
        ::operator delete(var_4);
        unk_14 = 0;
    }
}

// match: ?sub_191EE0@@YAHPAX0@Z @ 0x00191EE0
// sp-match: ?sub_191EE0@@YAHPAX0@Z @ 0x00123270
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Hands a script (kind 10) or task function (kind 12) arg_0 to the
// trigger arg_4.
RwInt32 sub_191EE0(void *arg_0, void *arg_4)
{
    RwInt32 var_10;
    RwInt32 var_C;
    type_3DFAD4 *bp_8;
    Trigger *bp_4;

    bp_4 = (Trigger *)arg_4;
    bp_8 = (type_3DFAD4 *)arg_0;
    if (bp_8->vf_008() == 10)
    {
        var_C = bp_8->unk_18;
        bp_4->sub_BDE70((RwUInt16)var_C);
    }
    else if (bp_8->vf_008() == 12)
    {
        var_10 = bp_8->unk_18;
        bp_4->sub_BDEE0((RwUInt16)var_10);
    }
    return 1;
}

// match: ??0type_3DFAE0@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00191F50
// sp-match: ??0type_3DFAE0@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x001232C0
type_3DFAE0::type_3DFAE0(const type_3DF8D8_04 &arg_0)
    : type_3DF8D8_base(arg_0)
{
    unk_10 = 0;
}

// match: ?vf_000@type_3DFAE0@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00191F80
// sp-match: ?vf_000@type_3DFAE0@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x001232F0
RwInt32 type_3DFAE0::vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4)
{
    unk_10 = sub_77E40(arg_0, 0, 0);
    sub_77AC0(unk_10);
    return 1;
}

// match: ??0type_3DFAEC@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00191FC0
// sp-match: ??0type_3DFAEC@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00123320
type_3DFAEC::type_3DFAEC(const type_3DF8D8_04 &arg_0)
    : type_3DF8D8_base(arg_0)
{
    unk_10 = 0;
}

// match: ?vf_000@type_3DFAEC@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00191FF0
// match: __ehhandler$?vf_000@type_3DFAEC@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z-0xB @ 0x00302320
// match: __ehhandler$?vf_000@type_3DFAEC@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x0030232B
// sp-match: ?vf_000@type_3DFAEC@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00123340
RwInt32 type_3DFAEC::vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4)
{
    unk_10 = new type_ED340;
    unk_10->sub_ED030(arg_0);
    unk_10->sub_ED2A0();
    set_dword_4B92FC(unk_10);
    dword_4B86FC--;
    return 1;
}

// match: ?vf_004@type_3DFAEC@@UAEXXZ @ 0x001920A0
// sp-match: ?vf_004@type_3DFAEC@@UAEXXZ @ 0x00126160
void type_3DFAEC::vf_004()
{
    if (unk_10)
    {
        delete unk_10;
        unk_10 = 0;
    }
    dword_4B92FC = 0;
}

// match: ??0type_3DFAF8@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00192110
// sp-match: ??0type_3DFAF8@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x001233D0
type_3DFAF8::type_3DFAF8(const type_3DF8D8_04 &arg_0)
    : type_3DF8D8_base(arg_0)
{
}

// match: ?vf_000@type_3DFAF8@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00192140
// sp-match: ?vf_000@type_3DFAF8@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x001233F0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_3DFAF8::vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4)
{
    RwInt32 var_8;
    RwInt32 l4;

    dword_4B86FC--;
    if (!RwStreamReadInt32(arg_0, &var_8, 4))
        return 1;
    for (l4 = 0; l4 < var_8; l4++)
    {
        type_3DF8D8_04 var_10;

        RwStreamReadInt32(arg_0, (RwInt32 *)&var_10.unk_00, 4);
        RwStreamReadInt32(arg_0, (RwInt32 *)&var_10.unk_04, 4);
        sub_198900((type_3DF8D8_04 *)&var_10, 0xD, 0, 0, 0, 0);
    }
    return 1;
}

// match: ??0type_3DFB04@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x001921F0
// sp-match: ??0type_3DFB04@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00123480
type_3DFB04::type_3DFB04(const type_3DF8D8_04 &arg_0)
    : type_3DF8D8_base(arg_0)
{
    unk_10 = 0;
}

// match: ?vf_000@type_3DFB04@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00192220
// sp-match: ?vf_000@type_3DFB04@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x001234A0
RwInt32 type_3DFB04::vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4)
{
    unk_10 = new type_ECDA0;
    unk_10->sub_EC750(arg_0);
    set_dword_4B92D4(unk_10);
    dword_4B86FC--;
    return 1;
}

// match: ?vf_004@type_3DFB04@@UAEXXZ @ 0x001922D0
// sp-match: ?vf_004@type_3DFB04@@UAEXXZ @ 0x00126190
void type_3DFB04::vf_004()
{
    if (unk_10)
    {
        delete unk_10;
        unk_10 = 0;
    }
    dword_4B92D4 = 0;
}

// match: ??0type_3DFB10@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00192340
// sp-match: ??0type_3DFB10@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00123520
type_3DFB10::type_3DFB10(const type_3DF8D8_04 &arg_0)
    : type_3DF8D8_base(arg_0)
{
}

// match: ??0type_3DFB1C@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00192370
// sp-match: ??0type_3DFB1C@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00123540
type_3DFB1C::type_3DFB1C(const type_3DF8D8_04 &arg_0)
    : type_3DF8D8_base(arg_0)
{
}

// match: ??0type_3DFB28@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x001923A0
// sp-match: ??0type_3DFB28@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00123570
type_3DFB28::type_3DFB28(const type_3DF8D8_04 &arg_0)
    : type_3DF8D8_base(arg_0)
{
}

// match: ??0type_3DFB34@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x001923D0
// sp-match: ??0type_3DFB34@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00123590
type_3DFB34::type_3DFB34(const type_3DF8D8_04 &arg_0)
    : type_3DF8D8_base(arg_0)
{
}

// match: ??0type_3DFB40@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00192400
// sp-match: ??0type_3DFB40@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x001235B0
type_3DFB40::type_3DFB40(const type_3DF8D8_04 &arg_0)
    : type_3DF8D8_base(arg_0)
{
}

// match: ??0type_3DFB4C@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00192430
// sp-match: ??0type_3DFB4C@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x001235D0
type_3DFB4C::type_3DFB4C(const type_3DF8D8_04 &arg_0)
    : type_3DF8D8_base(arg_0)
{
    unk_10 = 0;
}

// match: ?vf_000@type_3DFB4C@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00192460
// sp-match: ?vf_000@type_3DFB4C@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x001235F0
RwInt32 type_3DFB4C::vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4)
{
    unk_10 = new type_ED850;
    unk_10->sub_ED6B0(arg_0);
    unk_10->sub_ED7B0();
    set_dword_4B9300(unk_10);
    dword_4B86FC--;
    return 1;
}

// match: ?vf_004@type_3DFB4C@@UAEXXZ @ 0x00192510
// sp-match: ?vf_004@type_3DFB4C@@UAEXXZ @ 0x001261C0
void type_3DFB4C::vf_004()
{
    if (unk_10)
    {
        delete unk_10;
        unk_10 = 0;
    }
    dword_4B9300 = 0;
}

// match: ?vf_000@type_44E8D8_248@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00192580
// sp-match: ?vf_000@type_44E8D8_248@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00123680
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Registers its settings (its volume, duck depth, master flag and the
// rest) as variables from the references it reads.
RwInt32 type_44E8D8_248::vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4)
{
    RwInt32 var_120;
    RwUInt32 var_11C;
    type_3DF8D8_ref local_118[23];

    RwStreamRead(arg_0, local_118, arg_4->unk_08 - 0x1C);
    for (var_120 = 0; var_120 < 23; var_120++)
    {
        var_11C = get_ref_kind(local_118[var_120].unk_00, 0x1F);
        switch (var_11C)
        {
        case 2:
            sub_198900((type_3DF8D8_04 *)&local_118[var_120].unk_04, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_18F8B0, 0, (RwInt32)&unk_18, 0);
            break;
        case 3:
            sub_198900((type_3DF8D8_04 *)&local_118[var_120].unk_04, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_18F8B0, 0, (RwInt32)&unk_14, 0);
            break;
        case 4:
            sub_198900((type_3DF8D8_04 *)&local_118[var_120].unk_04, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_18F8B0, 0, (RwInt32)&unk_10, 0);
            break;
        case 5:
            sub_198900((type_3DF8D8_04 *)&local_118[var_120].unk_04, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_18F8B0, 0, (RwInt32)&unk_1C, 0);
            break;
        case 25:
            sub_198900((type_3DF8D8_04 *)&local_118[var_120].unk_04, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_18F8B0, 0, (RwInt32)&unk_20, 0);
            break;
        case 26:
            sub_198900((type_3DF8D8_04 *)&local_118[var_120].unk_04, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_18F8B0, 0, (RwInt32)&unk_28, 0);
            break;
        case 27:
            sub_198900((type_3DF8D8_04 *)&local_118[var_120].unk_04, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_18F8B0, 0, (RwInt32)&unk_2C, 0);
            break;
        }
    }
    return 1;
}

// match: ?sub_192870@type_44E8D8_248@@QAEXPAURwStream@@H@Z @ 0x00192870
// sp-match: ?sub_192870@type_44E8D8_248@@QAEXPAURwStream@@H@Z @ 0x001237A0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Reads its header into its settings, then its records, reading the
// language's ones (by the sound mode, dword_44E8A4) and skipping the rest.
void type_44E8D8_248::sub_192870(RwStream *arg_0, RwInt32 arg_4)
{
    RwChar var_460[0x200];
    RwInt32 var_260;
    RwInt32 local_25C;
    RwChar var_258[0x200];
    RwUInt32 lcl_50;
    RwUInt32 var_4C;
    RwUInt32 var_48;
    RwUInt32 loc44;
    type_44E8D8_248_hdr frm_24;

    RwStreamRead(arg_0, &frm_24, 0x24);
    unk_10 = frm_24.unk_08;
    unk_14 = frm_24.unk_00;
    unk_18 = frm_24.unk_10;
    unk_1C = frm_24.unk_04;
    unk_20 = frm_24.unk_0C;
    unk_24 = frm_24.unk_18;
    unk_28 = frm_24.unk_1C;
    unk_2C = frm_24.unk_20;
    type_44E8D8_248_rec var_40;

    RwStreamRead(arg_0, &var_40, 0x1C);
    var_48 = get_ref_kind(var_40.unk_0C.unk_00, 0x1F);
    lcl_50 = var_40.unk_08 - 0x1C;
    var_4C = 0;
    loc44 = 4;
    if (lcl_50)
    {
        var_4C = lcl_50 + 1;
        if ((loc44 - 1) & var_4C)
            var_4C = loc44 - ((loc44 - 1) & var_4C) + var_4C;
        RwStreamRead(arg_0, var_258, lcl_50);
    }
    for (local_25C = 0; local_25C < frm_24.unk_14; local_25C++)
    {
        RwStreamRead(arg_0, &var_40, 0x1C);
        var_260 = 0;
        var_48 = get_ref_kind(var_40.unk_0C.unk_00, 0x1F);
        switch (var_48)
        {
        case 0xB:
            if (dword_44E8A4 == 0)
                var_260 = 1;
            break;
        case 0xC:
            if (dword_44E8A4 == 1)
                var_260 = 1;
            break;
        case 0x14:
            if (dword_44E8A4 == 2)
                var_260 = 1;
            break;
        }
        lcl_50 = var_40.unk_08 - 0x1C;
        if (lcl_50)
        {
            if (var_260)
            {
                var_4C = lcl_50 + 1;
                if ((loc44 - 1) & var_4C)
                    var_4C = loc44 - ((loc44 - 1) & var_4C) + var_4C;
#ifdef CODFH_SP
                // shape: the record read into the header's buffer (SP 0x1237A0 has one 0x200 buffer)
                RwStreamRead(arg_0, var_258, lcl_50);
#else
                RwStreamRead(arg_0, var_460, lcl_50);
#endif
            }
            else
                RwStreamSkip(arg_0, lcl_50);
        }
    }
}

// match: ??0type_44E8D8_248@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00192B20
// sp-match: ??0type_44E8D8_248@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x001261F0
type_44E8D8_248::type_44E8D8_248(const type_3DF8D8_04 &arg_0)
    : type_3DFB6C(arg_0)
{
    unk_24 = -1;
    unk_10 = 0;
    unk_14 = 0;
    unk_18 = 0;
    unk_1C = 0;
    unk_20 = 0;
    unk_10 = 0;
    unk_14 = 0;
    unk_18 = 100;
    unk_20 = 0;
}

// match: ?vf_008@type_44E8D8_248@@UAEHXZ @ 0x00192BC0
// sp-match: ?vf_008@type_44E8D8_248@@UAEHXZ @ 0x001238D0
RwInt32 type_44E8D8_248::vf_008()
{
    return 0x2A;
}

// match: ?vf_010@type_44E8D8_248@@UAE_NH@Z @ 0x00192BD0
// match: __ehhandler$?vf_000@type_3DFB04@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z>1>8 @ 0x0041E668
// match: __ehhandler$?vf_000@type_3DFB04@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z>1 @ 0x0041E670
// match: __ehhandler$?vf_000@type_3DFB4C@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z>1>8 @ 0x0041E68C
// match: __ehhandler$?vf_000@type_3DFB4C@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z>1 @ 0x0041E694
// match: __ehhandler$?vf_000@type_3DFAEC@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z>1>8 @ 0x0041E6B0
// match: __ehhandler$?vf_000@type_3DFAEC@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z>1 @ 0x0041E6B8
// sp-match: ?vf_010@type_44E8D8_248@@UAE_NH@Z @ 0x001263E0
bool type_44E8D8_248::vf_010(RwInt32 arg_0)
{
    return true;
}


































































































































// Members /OPT:ICF folded into shared trivial bodies (config/aliases.txt): defined here for
// the authentic link (PLAN M7); the placement link takes the shared bodies.

// ?vf_004@type_3DF8D8_base@@UAEXXZ (folded into the empty body at 0x1E41C0)
void type_3DF8D8_base::vf_004()
{
}

// ?vf_008@type_3DF8D8_base@@UAEHXZ (folded into `return 0` at 0x1E4CB0)
RwInt32 type_3DF8D8_base::vf_008()
{
    return 0;
}

// ?vf_008@type_3DFA64@@UAEHXZ (folded into `return 4` at 0x9E000)
RwInt32 type_3DFA64::vf_008()
{
    return 4;
}

// ?vf_008@type_3DFAEC@@UAEHXZ (folded into `return 0` at 0x1E4CB0)
RwInt32 type_3DFAEC::vf_008()
{
    return 0;
}

// ?vf_008@type_3DFAF8@@UAEHXZ (folded into `return 0` at 0x1E4CB0)
RwInt32 type_3DFAF8::vf_008()
{
    return 0;
}

// ?vf_008@type_3DFB04@@UAEHXZ (folded into `return 0` at 0x1E4CB0)
RwInt32 type_3DFB04::vf_008()
{
    return 0;
}

// ?vf_008@type_3DFB28@@UAEHXZ (folded into `return 0` at 0x1E4CB0)
RwInt32 type_3DFB28::vf_008()
{
    return 0;
}

// ?vf_008@type_3DFB34@@UAEHXZ (folded into `return 0` at 0x1E4CB0)
RwInt32 type_3DFB34::vf_008()
{
    return 0;
}

// ?vf_008@type_3DFB40@@UAEHXZ (folded into `return 0` at 0x1E4CB0)
RwInt32 type_3DFB40::vf_008()
{
    return 0;
}

// ?vf_008@type_3DFB4C@@UAEHXZ (folded into `return 0` at 0x1E4CB0)
RwInt32 type_3DFB4C::vf_008()
{
    return 0;
}

// ?vf_008@type_3DFE88@@UAEHXZ (folded into `return 0` at 0x1E4CB0)
RwInt32 type_3DFE88::vf_008()
{
    return 0;
}

// Members /OPT:ICF folded into shared trivial bodies (config/aliases.txt): defined here for
// the authentic link (PLAN M7); the placement link takes the shared bodies.

// ??3type_3DF8D8_base@@SAXPAX0@Z (folded into the empty debug print at 0x19A750)
void type_3DF8D8_base::operator delete(void *arg_0, void *arg_4)
{
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??2type_3DF8D8_base@@SAPAXIPAX@Z (folded into 0x6CCF0)
void *type_3DF8D8_base::operator new(RwUInt32 arg_0, void *arg_4)
{
    return arg_4;
}

// ?vf_000@type_3DFE08@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z (folded into 0x193F00)
RwInt32 type_3DFE08::vf_000(struct RwStream *arg_0, struct type_3DF8D8_ev *arg_4)
{
    RwUInt32 var_4;

    var_4 = arg_4->unk_08 - 0x1C;
    unk_10 = var_4 / 0xC;
    unk_14 = (type_3DF8D8_ref *)RWSMalloc(var_4, 0x34253); // not an address: a memory hint
    RwStreamRead(arg_0, unk_14, var_4);
    return 1;
}

// ?vf_000@type_3DFE38@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z (folded into 0x194490)
RwInt32 type_3DFE38::vf_000(struct RwStream *arg_0, struct type_3DF8D8_ev *arg_4)
{
    RwStreamRead(arg_0, unk_10, arg_4->unk_08 - 0x1C);
    return 1;
}

// ?vf_000@type_3DFE64@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z (folded into 0x193F00)
RwInt32 type_3DFE64::vf_000(struct RwStream *arg_0, struct type_3DF8D8_ev *arg_4)
{
    RwUInt32 var_4;

    var_4 = arg_4->unk_08 - 0x1C;
    unk_10 = var_4 / 0xC;
    unk_14 = (type_3DF8D8_ref *)RWSMalloc(var_4, 0x34253); // not an address: a memory hint
    RwStreamRead(arg_0, unk_14, var_4);
    return 1;
}

// ?vf_004@type_3DFD40@@UAEXXZ (folded into 0x1935C0)
void type_3DFD40::vf_004()
{
    if (unk_14)
    {
        ::operator delete(unk_14);
        unk_14 = 0;
    }
    if (unk_10)
    {
        ::operator delete(unk_10);
        unk_10 = 0;
    }
    if (unk_1C)
    {
        ::operator delete((void *)unk_1C);
        unk_1C = 0;
    }
}

// ?vf_004@type_3DFDE4@@UAEXXZ (folded into 0x1935C0)
void type_3DFDE4::vf_004()
{
    if (unk_14)
    {
        ::operator delete(unk_14);
        unk_14 = 0;
    }
    if (unk_10)
    {
        ::operator delete(unk_10);
        unk_10 = 0;
    }
    if (unk_1C)
    {
        ::operator delete((void *)unk_1C);
        unk_1C = 0;
    }
}

// ?vf_004@type_3DFE08@@UAEXXZ (folded into 0x193DF0)
void type_3DFE08::vf_004()
{
    if (unk_14)
    {
        ::operator delete(unk_14);
        unk_14 = 0;
    }
}

// ?vf_004@type_3DFE14@@UAEXXZ (folded into 0x193DF0)
void type_3DFE14::vf_004()
{
    if (unk_14)
    {
        ::operator delete(unk_14);
        unk_14 = 0;
    }
}

// ?vf_004@type_3DFE64@@UAEXXZ (folded into 0x193DF0)
void type_3DFE64::vf_004()
{
    if (unk_14)
    {
        ::operator delete(unk_14);
        unk_14 = 0;
    }
}

// ?vf_004@type_3DFE7C@@UAEXXZ (folded into 0x197630)
void type_3DFE7C::vf_004()
{
    if (unk_10)
    {
        ::operator delete(unk_10);
        unk_10 = 0;
    }
}

// ?vf_00C@type_3DFE94@@UAEPADXZ (folded into 0x191D80)
RwChar *type_3DFE94::vf_00C()
{
    return unk_10;
}

// ?vf_004@type_3DFE94@@UAEXXZ (folded into 0x197630)
void type_3DFE94::vf_004()
{
    if (unk_10)
    {
        ::operator delete(unk_10);
        unk_10 = 0;
    }
}

// ?vf_008@type_3DF8E4@@UAEHXZ (folded into 0x115460)
RwInt32 type_3DF8E4::vf_008()
{
    return 1;
}

// ?vf_008@type_3DF8F0@@UAEHXZ (folded into 0xBFD70)
RwInt32 type_3DF8F0::vf_008()
{
    return 7;
}

// ?vf_008@type_3DF8FC@@UAEHXZ (folded into 0x15FD20)
RwInt32 type_3DF8FC::vf_008()
{
    return 6;
}

// ?vf_008@type_3DF9B8@@UAEHXZ (folded into 0xA2CD0)
RwInt32 type_3DF9B8::vf_008()
{
    return 9;
}

// ?vf_008@type_3DF9C4@@UAEHXZ (folded into 0xC5540)
RwInt32 type_3DF9C4::vf_008()
{
    return 3;
}

// ?vf_008@type_3DFABC@@UAEHXZ (folded into 0xA17A0)
RwInt32 type_3DFABC::vf_008()
{
    return 5;
}

// ?vf_008@type_3DFAE0@@UAEHXZ (folded into 0xBAA90)
RwInt32 type_3DFAE0::vf_008()
{
    return 0xF;
}

// ?vf_008@type_3DFB10@@UAEHXZ (folded into 0x1A32A0)
RwInt32 type_3DFB10::vf_008()
{
    return 0x14;
}

// ?vf_008@type_3DFB1C@@UAEHXZ (folded into 0x1A3190)
// sp-match: ?vf_008@type_3DFB1C@@UAEHXZ @ 0x00123560
RwInt32 type_3DFB1C::vf_008()
{
    return 0x13;
}

// ?vf_008@type_3DFC34@@UAEHXZ (folded into 0xA2530)
RwInt32 type_3DFC34::vf_008()
{
    return 0x19;
}

// ?vf_008@type_3DFCA0@@UAEHXZ (folded into 0x1B3C20)
// sp-match: ?vf_008@type_3DFCA0@@UAEHXZ @ 0x001262B0
RwInt32 type_3DFCA0::vf_008()
{
    return 27;
}

// ?vf_008@type_3DFDFC@@UAEHXZ (folded into 0x6FCA0)
RwInt32 type_3DFDFC::vf_008()
{
    return 0x20;
}

// ?vf_008@type_3DFE38@@UAEHXZ (folded into 0x1C0AD0)
RwInt32 type_3DFE38::vf_008()
{
    return 0x25;
}

// ?vf_008@type_3DFE44@@UAEHXZ (folded into 0xCC460)
// sp-match: ?vf_008@type_3DFE44@@UAEHXZ @ 0x001244A0
RwInt32 type_3DFE44::vf_008()
{
    return 0x26;
}

// ?vf_008@type_3DFE70@@UAEHXZ (folded into 0xCC720)
// sp-match: ?vf_008@type_3DFE70@@UAEHXZ @ 0x001247E0
RwInt32 type_3DFE70::vf_008()
{
    return 0x27;
}

// ?vf_010@type_3DFC34@@UAE_NH@Z (folded into 0x192BD0)
bool type_3DFC34::vf_010(RwInt32 arg_0)
{
    return true;
}

// ?vf_010@type_3DFCA0@@UAE_NH@Z (folded into 0x192BD0)
bool type_3DFCA0::vf_010(RwInt32 arg_0)
{
    return true;
}

// ?vf_010@type_3DFD40@@UAE_NH@Z (folded into 0x192BD0)
bool type_3DFD40::vf_010(RwInt32 arg_0)
{
    return true;
}

// ?vf_010@type_3DFDE4@@UAE_NH@Z (folded into 0x192BD0)
bool type_3DFDE4::vf_010(RwInt32 arg_0)
{
    return true;
}

// ?vf_010@type_3DFE50@@UAE_NH@Z (folded into 0x192BD0)
bool type_3DFE50::vf_010(RwInt32 arg_0)
{
    return true;
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?vf_008@type_3DF9A0@@UAEHXZ (folded into 0x222540)
// sp-match: ?vf_008@type_3DF9A0@@UAEHXZ @ 0x001228D0
RwInt32 type_3DF9A0::vf_008()
{
        return 0x3A;
    }

// ?vf_008@type_3DFAC8@@UAEHXZ (folded into 0x215B70)
// sp-match: ?vf_008@type_3DFAC8@@UAEHXZ @ 0x001230D0
RwInt32 type_3DFAC8::vf_008()
{
        return 0x1A;
    }

// ?vf_00C@type_3DFED8_obj@@UAEPAURwV3d@@XZ (folded into 0x1E4CB0)
struct RwV3d * type_3DFED8_obj::vf_00C()
{
        return 0;
    }

// ?vf_010@type_3DFED8_obj@@UAEPAURwV3d@@XZ (folded into 0x1E4CB0)
struct RwV3d * type_3DFED8_obj::vf_010()
{
        return 0;
    }

// The kind-1 variable's and the reference object's readers: their data after the
// header (/OPT:ICF folded both into type_3DFE20's, 0x194490).
RwInt32 type_3DF8E4::vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4)
{
    RwStreamRead(arg_0, &unk_10, arg_4->unk_08 - 0x1C);
    return 1;
}

RwInt32 type_3DFE44::vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4)
{
    RwStreamRead(arg_0, &unk_10, arg_4->unk_08 - 0x1C);
    return 1;
}

// The kind-0x2C object's release of its block (folded by /OPT:ICF into
// type_3DFDFC's, 0x193DF0).
void type_3DFEEC_obj::vf_004()
{
    if (unk_14)
    {
        ::operator delete((void *)unk_14);
        unk_14 = 0;
    }
}
