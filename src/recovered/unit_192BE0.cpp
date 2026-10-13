// the music streams and the GodAsset types after them: split from unit_18F3C0.cpp at 0x192BE0, an
// original object boundary (docs/units.md; PLAN M7).

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

// 0x0042B690
const RwChar *dword_42B690 = "XBX_";
// End of its data definitions.


// The GodAsset kinds' vtables (.rdata, PLAN M5): each sits in its own
// placement range (config/splits.txt); tools/session/datapieces.py checks them.
// Vtables (.rdata, PLAN M5): each in its own placement range (config/splits.txt).
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_7type_3DFB6C@@6B@ @ 0x003DFB6C
// match: ??_C@_04FPCPCCMN@XBX_?$AA@ @ 0x003DFB80
// match: ??_C@_07COFPGPDG@4s3?4rws?$AA@ @ 0x003DFB88
// match: ??_C@_07OFADLMJD@4s2?4rws?$AA@ @ 0x003DFB90
// match: ??_C@_07GDJHMODN@4s1?4rws?$AA@ @ 0x003DFB98
// match: ??_C@_07BJLOIIKF@4m3?4rws?$AA@ @ 0x003DFBA0
// match: ??_C@_07NCOCFLAA@4m2?4rws?$AA@ @ 0x003DFBA8
// match: ??_C@_07FEHGCJKO@4m1?4rws?$AA@ @ 0x003DFBB0
// match: ??_C@_07OIDAGGLB@2s3?4rws?$AA@ @ 0x003DFBB8
// match: ??_C@_07CDGMLFBE@2s2?4rws?$AA@ @ 0x003DFBC0
// match: ??_C@_07KFPIMHLK@2s1?4rws?$AA@ @ 0x003DFBC8
// match: ??_C@_07NPNBIBCC@2m3?4rws?$AA@ @ 0x003DFBD0
// match: ??_C@_07BEINFCIH@2m2?4rws?$AA@ @ 0x003DFBD8
// match: ??_C@_07JCBJCACJ@2m1?4rws?$AA@ @ 0x003DFBE0
// match: ??_C@_07GGLPGBFC@1s3?4rws?$AA@ @ 0x003DFBE8
// match: ??_C@_07KNODLCPH@1s2?4rws?$AA@ @ 0x003DFBF0
// match: ??_C@_07CLHHMAFJ@1s1?4rws?$AA@ @ 0x003DFBF8
// match: ??_C@_07FBFOIGMB@1m3?4rws?$AA@ @ 0x003DFC00
// match: ??_C@_07JKACFFGE@1m2?4rws?$AA@ @ 0x003DFC08
// match: ??_C@_07BMJGCHMK@1m1?4rws?$AA@ @ 0x003DFC10
// match: ??_C@_0BC@GGFEBLNF@InvalidStreamName?$AA@ @ 0x003DFC18
// match: ??_C@_06DIJPEION@?$CFs?$CFs?$CFs?$AA@ @ 0x003DFC2C
// match: ??_7type_3DFC34@@6B@ @ 0x003DFC34
// match: ??_C@_0EN@OPIJOMPK@More?5than?5two?5banks?5contain?5this@ @ 0x003DFC50
// match: ??_7type_3DFCA0@@6B@ @ 0x003DFCA0
// match: ??_C@_0IH@NIBBLLKE@Didn?8t?5play?5anything?5from?5a?5rand@ @ 0x003DFCB8
// match: ??_7type_3DFD40@@6B@ @ 0x003DFD40
// match: ??_C@_0DD@BIKKILPB@?$CK?$CK?$CK?$CK?$CK?$CK?$FO?$CG?$FO?$CG?$FO?$FO?5WARNING?3?5Subtitles?5@ @ 0x003DFD54
// match: ??_C@_0FK@MNNBDIMJ@?$CK?$CK?$CK?$CK?$CK?$CK?$FO?$CG?$FO?$CG?$FO?$FO?5WARNING?3?5Did?5not?5fi@ @ 0x003DFD88
// match: ??_7type_3DFDE4@@6B@ @ 0x003DFDE4
// match: ??_7type_3DFDFC@@6B@ @ 0x003DFDFC
// match: ??_7type_3DFE08@@6B@ @ 0x003DFE08
// match: ??_7type_3DFE14@@6B@ @ 0x003DFE14
// match: ??_7type_3DFE20@@6B@ @ 0x003DFE20
// match: ??_7type_3DFE2C@@6B@ @ 0x003DFE2C
// match: ??_7type_3DFE38@@6B@ @ 0x003DFE38
// match: ??_7type_3DFE44@@6B@ @ 0x003DFE44
// match: ??_7type_3DFE50@@6B@ @ 0x003DFE50
// match: ??_7type_3DFE64@@6B@ @ 0x003DFE64
// match: ??_7type_3DFE70@@6B@ @ 0x003DFE70
// match: ??_7type_3DFE7C@@6B@ @ 0x003DFE7C
// match: ??_7type_3DFE88@@6B@ @ 0x003DFE88
// match: ??_7type_3DFE94@@6B@ @ 0x003DFE94
// match: ??_7type_3DFEA4@@6B@ @ 0x003DFEA4
// match: ??_7type_3DFEB0_obj@@6B@ @ 0x003DFEB0
// match: ??_7type_3DFEC4_obj@@6B@ @ 0x003DFEC4
// match: ??_7type_3DFED8_obj@@6B@ @ 0x003DFED8
// match: ??_7type_3DFEEC_obj@@6B@ @ 0x003DFEEC
// match: ??_7type_3DFF00@@6B@ @ 0x003DFF00
// match: ??_7type_3DFF0C@@6B@ @ 0x003DFF0C
// match: ??_7type_3DFF18@@6B@ @ 0x003DFF18
// match: ??_C@_01IPJKGB@?$CD?$AA@ @ 0x003DFF24
// match: ??_C@_0BC@FIFENIFA@NULL?5?9?5REPLACE?5ME?$AA@ @ 0x003DFF28
// match: ??_7type_3DFF3C@@6B@ @ 0x003DFF3C
// match: ??_C@_0BD@EKIPKHO@Surfaces?$CLMaterials?$AA@ @ 0x003DFF48
// match: ??_7type_3DFF5C@@6B@ @ 0x003DFF5C
// match: ??_7type_3DFF68@@6B@ @ 0x003DFF68
// match: ??_7type_3DFF74@@6B@ @ 0x003DFF74
// match: ??_7type_3DFF80@@6B@ @ 0x003DFF80
// match: ??_7type_3DFF8C@@6B@ @ 0x003DFF8C
// match: ??_7type_3DFF98@@6B@ @ 0x003DFF98
// match: ??_7type_3DFFA4@@6B@ @ 0x003DFFA4
// match: __ehhandler$??0type_3DFE70@@QAE@ABUtype_3DF8D8_04@@@Z>1>8 @ 0x0041E6D4
// match: __ehhandler$??0type_3DFE70@@QAE@ABUtype_3DF8D8_04@@@Z>1 @ 0x0041E6DC
// match: __ehhandler$??0type_3DFE7C@@QAE@ABUtype_3DF8D8_04@@@Z>1>8 @ 0x0041E6F8
// match: __ehhandler$??0type_3DFE7C@@QAE@ABUtype_3DF8D8_04@@@Z>1 @ 0x0041E700
// match: __ehhandler$?vf_000@type_3DFE88@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z>1>8 @ 0x0041E71C
// match: __ehhandler$?vf_000@type_3DFE88@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z>1 @ 0x0041E724
// match: ?dword_42B690@@3PBDB @ 0x0042B690
// match: ?off_42B698@?1??vf_00C@type_44E8D8_248@@UAEHPAUtype_8A980@@PAUtype_3D3548@@HPAURwV3d@@HH@Z@4PAPBDA @ 0x0042B698


// match: ?vf_00C@type_44E8D8_248@@UAEHPAUtype_8A980@@PAUtype_3D3548@@HPAURwV3d@@HH@Z @ 0x00192BE0
// sp-match: ?vf_00C@type_44E8D8_248@@UAEHPAUtype_8A980@@PAUtype_3D3548@@HPAURwV3d@@HH@Z @ 0x001238E0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Plays it on its player: its file named from the language's folder and the
// sound table; a replay of the track now playing is left alone (or its
// fade cancelled); -1 once it is playing.
RwInt32 type_44E8D8_248::vf_00C(type_8A980 *arg_0, type_3D3548 *arg_4, RwInt32 arg_8, RwV3d *arg_C,
                                RwInt32 arg_10, RwInt32 arg_14)
{
    // The streams' file names by index (0x42B698, a static of this function: its
    // literals come out with the function, after the global prefix's).
    static const RwChar *off_42B698[19] = { "InvalidStreamName", "1m1.rws", "1m2.rws", "1m3.rws", "1s1.rws", "1s2.rws", "1s3.rws", "2m1.rws", "2m2.rws", "2m3.rws", "2s1.rws", "2s2.rws", "2s3.rws", "4m1.rws", "4m2.rws", "4m3.rws", "4s1.rws", "4s2.rws", "4s3.rws" };
    RwChar var_108[0x100];
    RwInt32 l4;

    l4 = -1;
    if (dword_44E8D8[unk_20].unk_248)
        l4 = dword_44E8D8[unk_20].unk_248->unk_24;
    sub_85840(0, var_108);
    sprintf(dword_44E8D8[unk_20].unk_01, "%s%s%s", var_108, dword_42B690, off_42B698[dword_44C0B0[unk_24]]);
    if (l4 == unk_24 && dword_44E8D8[unk_20].unk_244
        && (dword_44E8D8[unk_20].unk_180 == 0xE || dword_44E8D8[unk_20].unk_180 == 0xF))
    {
        dword_44E8D8[unk_20].unk_244 = 0;
        return 0;
    }
    if (l4 == unk_24 && !dword_44E8D8[unk_20].unk_244)
    {
        if (dword_44E8D8[unk_20].unk_180 == 0xE)
        {
            dword_44E8D8[unk_20].unk_180 = 0xC;
            return -1;
        }
        if (dword_44E8D8[unk_20].unk_180 == 0xF)
        {
            dword_44E8D8[unk_20].unk_180 = 0xC;
            return -1;
        }
        if (dword_44E8D8[unk_20].unk_180 != 1)
            return 0;
    }
    dword_44E8D8[unk_20].sub_86710();
    dword_44E8D8[unk_20].unk_248 = this;
    if (unk_10)
        sub_84610();
    dword_44E8D8[unk_20].unk_190[0] = (RwReal)unk_18 / 100.0f;
    dword_44E8D8[unk_20].unk_1B0[0] = (RwReal)unk_18 / 100.0f;
    return -1;
}
// match: ??0type_3DFC34@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00192E60
// sp-match: ??0type_3DFC34@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00126230
type_3DFC34::type_3DFC34(const type_3DF8D8_04 &arg_0)
    : type_3DFB6C(arg_0)
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 2; var_4++)
    {
        unk_2C[var_4].unk_00.unk_00 = 1;
        unk_2C[var_4].unk_00.unk_04 = 1;
        unk_2C[var_4].unk_08 = -1;
    }
    unk_1A = 0;
    unk_28 = 0;
}
// match: ?vf_014@type_3DFC34@@UAEXPAUtype_825E0@@H@Z @ 0x00192F30
// sp-match: ?vf_014@type_3DFC34@@UAEXPAUtype_825E0@@H@Z @ 0x00123A60
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Adds it to the bank arg_0 as its record arg_4 (unless that bank has it
// already): into a free slot, at 0.6 of its volume while a bank request
// holds that bank; a warning when both slots are taken.
void type_3DFC34::vf_014(type_825E0 *arg_0, RwInt32 arg_4)
{
    RwReal var_114;
    RwInt32 var_110;
    RwInt32 local_10C;
    RwChar var_108[0x100];

    for (local_10C = 0; local_10C < 2; local_10C++)
    {
        if (unk_2C[local_10C].unk_00.unk_00 == arg_0->unk_00.unk_00 && unk_2C[local_10C].unk_00.unk_04 == arg_0->unk_00.unk_04)
            return;
    }
    for (local_10C = 0; local_10C < 2; local_10C++)
    {
        if (unk_2C[local_10C].unk_08 < 0)
        {
            unk_2C[local_10C].unk_00.unk_00 = arg_0->unk_00.unk_00;
            unk_2C[local_10C].unk_00.unk_04 = arg_0->unk_00.unk_04;
            unk_2C[local_10C].unk_08 = arg_4;
            unk_1B = 0;
            for (var_110 = 0; var_110 < 10; var_110++)
            {
                if (unk_2C[local_10C].unk_00.unk_00 == dword_4B1B60[var_110].unk_00.unk_00
                    && unk_2C[local_10C].unk_00.unk_04 == dword_4B1B60[var_110].unk_00.unk_04)
                {
                    if (unk_15 != 100)
                        unk_15 = (RwUInt8)(var_114 = (var_114 = unk_15) * 0.6f);
                    unk_1B = 1;
                    break;
                }
            }
            return;
        }
    }
    sprintf(var_108, "More than two banks contain this basic sound alias:0x%X, 0x%X. That's bad!.\n", unk_04.unk_00,
            unk_04.unk_04);
}
// match: ?vf_004@type_3DFC34@@UAEXXZ @ 0x00193140
// sp-match: ?vf_004@type_3DFC34@@UAEXXZ @ 0x00123B60
void type_3DFC34::vf_004()
{
    if (unk_28)
        sub_1986D0(unk_28);
    unk_28 = 0;
}
// match: ?vf_00C@type_3DFC34@@UAEHPAUtype_8A980@@PAUtype_3D3548@@HPAURwV3d@@HH@Z @ 0x00193170
// sp-match: ?vf_00C@type_3DFC34@@UAEHPAUtype_8A980@@PAUtype_3D3548@@HPAURwV3d@@HH@Z @ 0x00123B80
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Plays it through the emitter arg_0 (its name shown as a subtitle), then
// lets the entity arg_4's listeners hear it; the voice, or 0.
RwInt32 type_3DFC34::vf_00C(type_8A980 *arg_0, type_3D3548 *arg_4, RwInt32 arg_8, RwV3d *arg_C,
                            RwInt32 arg_10, RwInt32 arg_14)
{
    RwInt32 var_8;
    RwInt32 l4;

    l4 = 0;
    l4 = arg_0->sub_8A440((type_199010 *)this, sub_840D0((type_199010 *)this), unk_16, arg_10, arg_14);
    if (l4 && unk_28)
    {
        strcpy((RwChar *)&byte_44E490, unk_28);
        sub_EAB80((RwChar *)&byte_44E490, 0, 0.1f);
        clear_hud_unk_1A160();
        arg_0->unk_00 = (struct type_44C4E8 *)l4;
    }
    if (unk_17 && !((dword_4B86F8 >> 4) & 1))
    {
        if (!unk_19)
            var_8 = 2;
        else
            var_8 = 1;
        if (unk_18)
            sub_3C4B0(arg_4, arg_8, arg_C, var_8, unk_1E * 100.0f, 0, 0);
        else if (l4)
            sub_3C540(arg_4, arg_8, l4, arg_C, var_8, unk_1E * 100.0f, 0, 0);
    }
    return l4;
}
// match: ??0type_3DFCA0@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x001932D0
// sp-match: ??0type_3DFCA0@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00126280
type_3DFCA0::type_3DFCA0(const type_3DF8D8_04 &arg_0)
    : type_3DFB6C(arg_0)
{
    unk_18 = 0;
    unk_14 = 0;
    unk_10 = 0;
    unk_1C = 0;
}
// match: ?vf_00C@type_3DFCA0@@UAEHPAUtype_8A980@@PAUtype_3D3548@@HPAURwV3d@@HH@Z @ 0x00193330
// sp-match: ?vf_00C@type_3DFCA0@@UAEHPAUtype_8A980@@PAUtype_3D3548@@HPAURwV3d@@HH@Z @ 0x00123CA0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Plays one of its loaded sounds, picked at random by weight.
RwInt32 type_3DFCA0::vf_00C(type_8A980 *arg_0, type_3D3548 *arg_4, RwInt32 arg_8, RwV3d *arg_C,
                            RwInt32 arg_10, RwInt32 arg_14)
{
    RwChar var_898[0x80];
    RwInt32 local_810;
    RwInt32 var_80C;
    RwInt32 v808;
    RwInt32 v804;
    type_3DFB6C *var_800[0x200];

    if (!unk_14 || !unk_10)
        return 0;
    v808 = 0;
    for (v804 = 0; v804 < unk_18; v804++)
    {
        var_800[v804] = (type_3DFB6C *)sub_198800(&unk_10[v804]);
        if (var_800[v804])
            v808 += unk_14[v804];
    }
    if (v808 > 0)
    {
        var_80C = rand() % v808;
        local_810 = RpRandom() % 100001;
        var_80C = local_810 % v808;
        for (v804 = 0; v804 < unk_18; v804++)
        {
            if (var_800[v804])
            {
                if ((var_80C -= unk_14[v804]) < 0)
                    return var_800[v804]->vf_00C(arg_0, arg_4, arg_8, arg_C, arg_10, arg_14);
            }
        }
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS) // single player compiles the debug print out (SP 0x123CA0)
        sub_19A750("Didn't play anything from a random even though at least one of it's sounds was actually loaded. What the hell?? That's not right! -RB\n");
#endif
    }
    else if (dword_44E870)
        sprintf(var_898, "0x%X, 0x%X", unk_04.unk_00, unk_04.unk_04);
    return 0;
}
// match: ?vf_000@type_3DFCA0@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00193530
// sp-match: ?vf_000@type_3DFCA0@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00127520
// Registers its list (kind 0x20), which sub_193E20 hands it.
RwInt32 type_3DFCA0::vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4)
{
    RwUInt32 var_4;
    type_3DF8D8_ref var_10;

    RwStreamRead(arg_0, &var_10, arg_4->unk_08 - 0x1C);
    var_4 = get_ref_kind(var_10.unk_00, 0x1F);
    sub_198900((type_3DF8D8_04 *)&var_10.unk_04, 0x20, (void (*)(RwInt32, RwInt32, RwInt32))sub_193E20, (RwInt32)this, 0, 0);
    return 1;
}
// match: ?vf_004@type_3DFCA0@@UAEXXZ @ 0x001935C0
// sp-match: ?vf_004@type_3DFCA0@@UAEXXZ @ 0x00123E10
// Frees its weights, keys and references.
void type_3DFCA0::vf_004()
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
// match: ??0type_3DFD40@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00193640
// sp-match: ??0type_3DFD40@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x001262C0
type_3DFD40::type_3DFD40(const type_3DF8D8_04 &arg_0)
    : type_3DFB6C(arg_0)
{
    unk_18 = 0;
    unk_14 = 0;
    unk_10 = 0;
    unk_1C = 0;
}
// match: ?vf_008@type_3DFD40@@UAEHXZ @ 0x001936A0
// sp-match: ?vf_008@type_3DFD40@@UAEHXZ @ 0x001262F0
RwInt32 type_3DFD40::vf_008()
{
    return 0x1C;
}
// match: ?vf_00C@type_3DFD40@@UAEHPAUtype_8A980@@PAUtype_3D3548@@HPAURwV3d@@HH@Z @ 0x001936B0
// sp-match: ?vf_00C@type_3DFD40@@UAEHPAUtype_8A980@@PAUtype_3D3548@@HPAURwV3d@@HH@Z @ 0x00123E60
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Plays the sequence through the emitter arg_0 at arg_C: nothing while a
// slot of dword_4B1CA0 is starting this one; else a free slot, or one with
// no subtitled sound in it (the first as a last resort), takes its sounds
// with their delays.
RwInt32 type_3DFD40::vf_00C(type_8A980 *arg_0, type_3D3548 *arg_4, RwInt32 arg_8, RwV3d *arg_C, RwInt32 arg_10,
                            RwInt32 arg_14)
{
    RwInt32 var_24;
    type_3DF8D8_19 *var_20;
    type_3DF8D8 *l1C;
    RwInt32 m_18;
    type_837D0 *ebp_14;
    type_3DF8D8 *lv_10;
    RwInt32 var_C;
    RwInt32 bp_8;
    type_3DF8D8 *bp_4;

    bp_8 = 0;
    var_C = -1;
    if (!arg_0)
        return 0;
    for (bp_8 = 0; bp_8 < 0x14; bp_8++)
    {
        if (dword_4B1CA0[bp_8].unk_04 && dword_4B1CA0[bp_8].unk_00 == 0.0f)
        {
            lv_10 = sub_198800(unk_10);
            if (lv_10 && dword_4B1CA0[bp_8].unk_04->unk_04.unk_00 == lv_10->unk_04.unk_00
                && dword_4B1CA0[bp_8].unk_04->unk_04.unk_04 == lv_10->unk_04.unk_04)
                return 0;
        }
    }
    for (bp_8 = 0; bp_8 < 0x14; bp_8++)
    {
        if (!dword_4B1CA0[bp_8].unk_04)
        {
            var_C = bp_8;
            break;
        }
    }
    if (var_C == -1)
    {
        for (bp_8 = 0; bp_8 < 0x14; bp_8++)
        {
            if (dword_4B1CA0[bp_8].unk_04)
            {
                m_18 = 0;
                ebp_14 = dword_4B1CA0[bp_8].unk_04;
                while (ebp_14)
                {
                    l1C = sub_198800((type_3DF8D8_04 *)&ebp_14->unk_04);
                    if (l1C && l1C->vf_008() == 0x19)
                    {
                        var_20 = (type_3DF8D8_19 *)l1C;
                        if (var_20->unk_28)
                        {
                            m_18 = 1;
                            break;
                        }
                    }
                    ebp_14 = ebp_14->unk_0C;
                }
                if (!m_18)
                {
                    var_C = bp_8;
                    break;
                }
            }
        }
        if (var_C == -1)
        {
            var_C = 0;
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS) // single player compiles the debug prints out (SP 0x123E60)
            sub_19A750("******^&^&^^ WARNING: Did not find a sequence alias slot that has no subtitle to remove!\n");
            sub_19A750("******^&^&^^ WARNING: Subtitles might not display\n");
#endif
        }
        delete dword_4B1CA0[var_C].unk_04;
        dword_4B1CA0[var_C].unk_04 = 0;
    }
    dword_4B1CA0[var_C].unk_00 = 0;
    dword_4B1CA0[var_C].unk_14 = arg_0;
    for (var_24 = 0; var_24 < unk_18; var_24++)
    {
        bp_4 = sub_198800(&unk_10[var_24]);
        if (bp_4)
            dword_4B1CA0[var_C].sub_85A00((type_825E0_id *)&bp_4->unk_04, (RwReal)unk_14[var_24]);
#ifdef CODFH_EXTRA_LOGS // (the GameCube build, main.dol 0x800C6260)
        else if (sub_198770(&unk_10[var_24]))
            sub_19A750("Asset still loading!\n");
#endif
    }
    dword_4B1CA0[var_C].unk_08 = *arg_C;
    return 0;
}
// match: ?vf_000@type_3DFD40@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00193980
// sp-match: ?vf_000@type_3DFD40@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00127580
// Registers its list (kind 0x21), which sub_1940E0 hands it.
RwInt32 type_3DFD40::vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4)
{
    RwUInt32 var_4;
    type_3DF8D8_ref var_10;

    RwStreamRead(arg_0, &var_10, 0xC);
    var_4 = get_ref_kind(var_10.unk_00, 0x1F);
    sub_198900((type_3DF8D8_04 *)&var_10.unk_04, 0x21, (void (*)(RwInt32, RwInt32, RwInt32))sub_1940E0, (RwInt32)this, 0, 0);
    return 1;
}
// match: ?sub_193A00@type_3DFCA0@@QAEXPAURwStream@@H@Z @ 0x00193A00
// sp-match: ?sub_193A00@type_3DFCA0@@QAEXPAURwStream@@H@Z @ 0x00124010
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3DFCA0::sub_193A00(RwStream *arg_0, RwInt32 arg_4)
{
    RwInt32 var_8;
    RwInt32 l4;

    RwStreamRead(arg_0, &l4, 4);
    unk_18 = l4;
    unk_10 = (type_3DF8D8_04 *)RWSMalloc(l4 * 8, 0x34253); // not an address: a memory hint
    unk_14 = (RwInt32 *)RWSMalloc(l4 * 4, 0x34253); // not an address: a memory hint
    for (var_8 = 0; var_8 < l4; var_8++)
    {
        RwStreamRead(arg_0, &unk_10[var_8], 8);
        RwStreamRead(arg_0, &unk_14[var_8], 4);
    }
}
// match: ??0type_3DFDE4@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00193AB0
// sp-match: ??0type_3DFDE4@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00126300
type_3DFDE4::type_3DFDE4(const type_3DF8D8_04 &arg_0)
    : type_3DFB6C(arg_0)
{
    unk_18 = 0;
    unk_14 = 0;
    unk_10 = 0;
    unk_1C = 0;
}
// match: ?vf_008@type_3DFDE4@@UAEHXZ @ 0x00193B10
// sp-match: ?vf_008@type_3DFDE4@@UAEHXZ @ 0x00126330
RwInt32 type_3DFDE4::vf_008()
{
    return 0x1D;
}
// match: ?vf_00C@type_3DFDE4@@UAEHPAUtype_8A980@@PAUtype_3D3548@@HPAURwV3d@@HH@Z @ 0x00193B20
// sp-match: ?vf_00C@type_3DFDE4@@UAEHPAUtype_8A980@@PAUtype_3D3548@@HPAURwV3d@@HH@Z @ 0x001240A0
RwInt32 type_3DFDE4::vf_00C(type_8A980 *arg_0, type_3D3548 *arg_4, RwInt32 arg_8, RwV3d *arg_C,
                            RwInt32 arg_10, RwInt32 arg_14)
{
    return 0;
}
// match: ?vf_014@type_3DFDE4@@UAEHPAUtype_8A980@@HPAUtype_3D3548@@HPAURwV3d@@HH@Z @ 0x00193B30
// sp-match: ?vf_014@type_3DFDE4@@UAEHPAUtype_8A980@@HPAUtype_3D3548@@HPAURwV3d@@HH@Z @ 0x001240B0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Plays its loaded sound of index arg_4; with none, a warning sound at the
// player when the debug switch is set.
RwInt32 type_3DFDE4::vf_014(type_8A980 *arg_0, RwInt32 arg_4, type_3D3548 *arg_8, RwInt32 arg_C,
                            RwV3d *arg_10, RwInt32 arg_14, RwInt32 arg_18)
{
    type_3D3548 *var_88C;
    RwChar stk_888[0x80];
    RwInt32 var804;
    type_3DFB6C *var_800[0x200];

    if (!arg_0)
        return 0;
    if (!unk_14 || !unk_10)
        return 0;
    for (var804 = 0; var804 < unk_18; var804++)
    {
        var_800[var804] = (type_3DFB6C *)sub_198800(&unk_10[var804]);
        if (var_800[var804])
        {
            if (unk_14[var804] == arg_4)
                return var_800[var804]->vf_00C(arg_0, arg_8, arg_C, arg_10, arg_14, arg_18);
        }
        else if (dword_44E860)
            sprintf(stk_888, "0x%X, 0x%X", unk_04.unk_00, unk_04.unk_04);
    }
    if (dword_44E860 && dword_44E874)
        sprintf(stk_888, "0x%X, 0x%X", unk_04.unk_00, unk_04.unk_04);
    if (dword_44E83C)
    {
        type_3DF8D8_04 var_894;

        var_894.unk_00 = 0x9FAFD39B;
        var_894.unk_04 = 0xAB43C2E3;
        var_88C = sub_1745A0(0);
        dword_4B1E98.sub_8A980(&var_894, 0, 0, var_88C->sub_CD550(), 1, 0);
    }
    return 0;
}
// match: ?vf_000@type_3DFDE4@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00193D20
// sp-match: ?vf_000@type_3DFDE4@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x001275D0
// Registers its list (kind 0x22), which sub_193FB0 hands it.
RwInt32 type_3DFDE4::vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4)
{
    RwUInt32 var_4;
    type_3DF8D8_ref var_10;

    RwStreamRead(arg_0, &var_10, arg_4->unk_08 - 0x1C);
    var_4 = get_ref_kind(var_10.unk_00, 0x1F);
    sub_198900((type_3DF8D8_04 *)&var_10.unk_04, 0x22, (void (*)(RwInt32, RwInt32, RwInt32))sub_193FB0, (RwInt32)this, 0, 0);
    return 1;
}
// match: ??0type_3DFDFC@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00193DB0
// sp-match: ??0type_3DFDFC@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00124230
type_3DFDFC::type_3DFDFC(const type_3DF8D8_04 &arg_0)
    : type_3DF8D8_base(arg_0)
{
    unk_10 = 0;
    unk_14 = 0;
}
// match: ?vf_004@type_3DFDFC@@UAEXXZ @ 0x00193DF0
// sp-match: ?vf_004@type_3DFDFC@@UAEXXZ @ 0x00124E50
void type_3DFDFC::vf_004()
{
    if (unk_14)
    {
        ::operator delete(unk_14);
        unk_14 = 0;
    }
}
// match: ?sub_193E20@@YAHPAUtype_3DFDFC@@PAUtype_3DFCA0@@PAX@Z @ 0x00193E20
// sp-match: ?sub_193E20@@YAHPAUtype_3DFDFC@@PAUtype_3DFCA0@@PAX@Z @ 0x001272A0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_193E20(type_3DFDFC *arg_0, type_3DFCA0 *arg_4, void *arg_8)
{
    RwInt32 var_C;
    type_3DFCA0 *bp_8;
    type_3DFDFC *bp_4;

    bp_8 = arg_4;
    bp_4 = arg_0;
    bp_8->unk_18 = bp_4->unk_10;
    bp_8->unk_1C = (RwInt32)bp_4->unk_14;
    bp_4->unk_10 = -1;
    bp_4->unk_14 = 0;
    bp_8->unk_10 = (type_3DF8D8_04 *)RWSMalloc(bp_8->unk_18 * 8, 0x34253); // not an address: a memory hint
    bp_8->unk_14 = (RwInt32 *)RWSMalloc(bp_8->unk_18 * 4, 0x34253); // not an address: a memory hint
    for (var_C = 0; var_C < bp_8->unk_18; var_C++)
        sub_198900((type_3DF8D8_04 *)&((type_3DF8D8_ref *)bp_8->unk_1C)[var_C].unk_04, 0x23,
                   (void (*)(RwInt32, RwInt32, RwInt32))sub_194320, (RwInt32)&bp_8->unk_10[var_C],
                   (RwInt32)&bp_8->unk_14[var_C], 0);
    return 0;
}
// match: ?vf_000@type_3DFDFC@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00193F00
// sp-match: ?vf_000@type_3DFDFC@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x001242A0
// Reads its references.
RwInt32 type_3DFDFC::vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4)
{
    RwUInt32 var_4;

    var_4 = arg_4->unk_08 - 0x1C;
    unk_10 = var_4 / 0xC;
    unk_14 = (type_3DF8D8_ref *)RWSMalloc(var_4, 0x34253); // not an address: a memory hint
    RwStreamRead(arg_0, unk_14, var_4);
    return 1;
}
// match: ??0type_3DFE08@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00193F60
// sp-match: ??0type_3DFE08@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00124260
type_3DFE08::type_3DFE08(const type_3DF8D8_04 &arg_0)
    : type_3DF8D8_base(arg_0)
{
    unk_10 = 0;
    unk_14 = 0;
}
// match: ?vf_008@type_3DFE08@@UAEHXZ @ 0x00193FA0
// sp-match: ?vf_008@type_3DFE08@@UAEHXZ @ 0x00124290
RwInt32 type_3DFE08::vf_008()
{
    return 0x22;
}
// match: ?sub_193FB0@@YAHPAUtype_3DFDFC@@PAUtype_3DFDE4@@PAX@Z @ 0x00193FB0
// sp-match: ?sub_193FB0@@YAHPAUtype_3DFDFC@@PAUtype_3DFDE4@@PAX@Z @ 0x00127340
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The index sound's list callback (as sub_193E20, kind 0x25).
RwInt32 sub_193FB0(type_3DFDFC *arg_0, type_3DFDE4 *arg_4, void *arg_8)
{
    RwInt32 var_C;
    type_3DFDE4 *bp_8;
    type_3DFDFC *bp_4;

    bp_8 = arg_4;
    bp_4 = arg_0;
    bp_8->unk_18 = bp_4->unk_10;
    bp_8->unk_1C = (RwInt32)bp_4->unk_14;
    bp_4->unk_10 = -1;
    bp_4->unk_14 = 0;
    bp_8->unk_10 = (type_3DF8D8_04 *)RWSMalloc(bp_8->unk_18 * 8, 0x34253); // not an address: a memory hint
    bp_8->unk_14 = (RwInt32 *)RWSMalloc(bp_8->unk_18 * 4, 0);
    for (var_C = 0; var_C < bp_8->unk_18; var_C++)
        sub_198900((type_3DF8D8_04 *)&((type_3DF8D8_ref *)bp_8->unk_1C)[var_C].unk_04, 0x25,
                   (void (*)(RwInt32, RwInt32, RwInt32))sub_194320, (RwInt32)&bp_8->unk_10[var_C],
                   (RwInt32)&bp_8->unk_14[var_C], 0);
    return 0;
}
// match: ??0type_3DFE14@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00194090
// sp-match: ??0type_3DFE14@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x001242F0
type_3DFE14::type_3DFE14(const type_3DF8D8_04 &arg_0)
    : type_3DF8D8_base(arg_0)
{
    unk_10 = 0;
    unk_14 = 0;
}
// match: ?vf_008@type_3DFE14@@UAEHXZ @ 0x001940D0
// sp-match: ?vf_008@type_3DFE14@@UAEHXZ @ 0x00124320
RwInt32 type_3DFE14::vf_008()
{
    return 0x21;
}
// match: ?sub_1940E0@@YAHPAUtype_3DFDFC@@PAUtype_3DFD40@@PAX@Z @ 0x001940E0
// sp-match: ?sub_1940E0@@YAHPAUtype_3DFDFC@@PAUtype_3DFD40@@PAX@Z @ 0x001273D0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The sequence sound's list callback (as sub_193E20, kind 0x24).
RwInt32 sub_1940E0(type_3DFDFC *arg_0, type_3DFD40 *arg_4, void *arg_8)
{
    RwInt32 var_C;
    type_3DFD40 *bp_8;
    type_3DFDFC *bp_4;

    bp_8 = arg_4;
    bp_4 = arg_0;
    bp_8->unk_18 = bp_4->unk_10;
    bp_8->unk_1C = (RwInt32)bp_4->unk_14;
    bp_4->unk_10 = -1;
    bp_4->unk_14 = 0;
    bp_8->unk_10 = (type_3DF8D8_04 *)RWSMalloc(bp_8->unk_18 * 8, 0x34253); // not an address: a memory hint
    bp_8->unk_14 = (RwInt32 *)RWSMalloc(bp_8->unk_18 * 4, 0);
    for (var_C = 0; var_C < bp_8->unk_18; var_C++)
        sub_198900((type_3DF8D8_04 *)&((type_3DF8D8_ref *)bp_8->unk_1C)[var_C].unk_04, 0x24,
                   (void (*)(RwInt32, RwInt32, RwInt32))sub_194320, (RwInt32)&bp_8->unk_10[var_C],
                   (RwInt32)&bp_8->unk_14[var_C], 0);
    return 0;
}
// match: ?vf_000@type_3DFE14@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x001941C0
// sp-match: ?vf_000@type_3DFE14@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00124330
RwInt32 type_3DFE14::vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4)
{
    RwUInt32 var_4;

    var_4 = arg_4->unk_04 - 0x1C;
    unk_10 = var_4 / 0xC;
    unk_14 = (type_3DF8D8_ref *)RWSMalloc(var_4, 0x34253); // not an address: a memory hint
    RwStreamRead(arg_0, unk_14, var_4);
    return 1;
}
// match: ??0type_3DFE20@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00194220
// sp-match: ??0type_3DFE20@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00124380
type_3DFE20::type_3DFE20(const type_3DF8D8_04 &arg_0)
    : type_3DF8D8_base(arg_0)
{
}
// match: ?vf_008@type_3DFE20@@UAEHXZ @ 0x00194290
// sp-match: ?vf_008@type_3DFE20@@UAEHXZ @ 0x001243B0
RwInt32 type_3DFE20::vf_008()
{
    return 0x23;
}
// match: ??0type_3DFE2C@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x001942A0
// sp-match: ??0type_3DFE2C@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x001243C0
type_3DFE2C::type_3DFE2C(const type_3DF8D8_04 &arg_0)
    : type_3DF8D8_base(arg_0)
{
}
// match: ?vf_008@type_3DFE2C@@UAEHXZ @ 0x00194310
// sp-match: ?vf_008@type_3DFE2C@@UAEHXZ @ 0x001243F0
RwInt32 type_3DFE2C::vf_008()
{
    return 0x24;
}
// match: ?sub_194320@@YAHPAUtype_3DFE20@@PAUtype_3DF8D8_04@@PAH@Z @ 0x00194320
// sp-match: ?sub_194320@@YAHPAUtype_3DFE20@@PAUtype_3DF8D8_04@@PAH@Z @ 0x00126340
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// A sound reference's callback: registers its sound (kind 0x26, its key
// into *arg_4 through sub_194510) and its weight (a variable into *arg_8).
RwInt32 sub_194320(type_3DFE20 *arg_0, type_3DF8D8_04 *arg_4, RwInt32 *arg_8)
{
    RwInt32 var_10;
    type_3DFE20 *var_C;
    type_3DF8D8_04 *bp_8;
    RwInt32 *bp_4;

    var_C = arg_0;
    bp_8 = arg_4;
    bp_4 = arg_8;
    for (var_10 = 0; var_10 < 2; var_10++)
    {
        switch (get_ref_kind(var_C->unk_10[var_10].unk_00, 0x1F))
        {
        case 1:
            sub_198900((type_3DF8D8_04 *)&var_C->unk_10[var_10].unk_04, 0x26, (void (*)(RwInt32, RwInt32, RwInt32))sub_194510,
                       0, (RwInt32)bp_8, 0);
            break;
        case 2:
            sub_198900((type_3DF8D8_04 *)&var_C->unk_10[var_10].unk_04, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_18F8B0,
                       0, (RwInt32)bp_4, 0);
            break;
        }
    }
    return 0;
}
// match: ?vf_000@type_3DFE2C@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x001943F0
// sp-match: ?vf_000@type_3DFE2C@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00124400
RwInt32 type_3DFE2C::vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4)
{
    RwStreamRead(arg_0, unk_10, arg_4->unk_04 - 0x1C);
    return 1;
}
// match: ??0type_3DFE38@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00194420
// sp-match: ??0type_3DFE38@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00124430
type_3DFE38::type_3DFE38(const type_3DF8D8_04 &arg_0)
    : type_3DF8D8_base(arg_0)
{
}
// match: ?vf_000@type_3DFE20@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00194490
// sp-match: ?vf_000@type_3DFE20@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x001223A0
RwInt32 type_3DFE20::vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4)
{
    RwStreamRead(arg_0, unk_10, arg_4->unk_08 - 0x1C);
    return 1;
}
// match: ??0type_3DFE44@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x001944C0
// sp-match: ??0type_3DFE44@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00124470
type_3DFE44::type_3DFE44(const type_3DF8D8_04 &arg_0)
    : type_3DF8D8_base(arg_0)
{
}
// match: ?sub_194510@@YAHPAUtype_3DFE44@@HPAUtype_3DF8D8_04@@@Z @ 0x00194510
// sp-match: ?sub_194510@@YAHPAUtype_3DFE44@@HPAUtype_3DF8D8_04@@@Z @ 0x001244B0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// A sound reference's key into *arg_8.
RwInt32 sub_194510(type_3DFE44 *arg_0, RwInt32 arg_4, type_3DF8D8_04 *arg_8)
{
    type_3DF8D8_04 *var_8;
    type_3DF8D8_04 *l4;

    var_8 = arg_8;
    l4 = &arg_0->unk_10.unk_04;
    var_8->unk_00 = l4->unk_00;
    var_8->unk_04 = l4->unk_04;
    return 0;
}
// match: ??0type_3DFE50@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00194550
// sp-match: ??0type_3DFE50@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x001263A0
type_3DFE50::type_3DFE50(const type_3DF8D8_04 &arg_0)
    : type_3DFB6C(arg_0)
{
    unk_14 = 0;
    unk_10 = 0;
    unk_18 = 0;
}
// match: ?vf_008@type_3DFE50@@UAEHXZ @ 0x001945A0
// sp-match: ?vf_008@type_3DFE50@@UAEHXZ @ 0x001263D0
RwInt32 type_3DFE50::vf_008()
{
    return 0x1E;
}
// match: ?vf_00C@type_3DFE50@@UAEHPAUtype_8A980@@PAUtype_3D3548@@HPAURwV3d@@HH@Z @ 0x001945B0
// sp-match: ?vf_00C@type_3DFE50@@UAEHPAUtype_8A980@@PAUtype_3D3548@@HPAURwV3d@@HH@Z @ 0x001244D0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Plays one of its loaded sounds, picked at random.
RwInt32 type_3DFE50::vf_00C(type_8A980 *arg_0, type_3D3548 *arg_4, RwInt32 arg_8, RwV3d *arg_C,
                            RwInt32 arg_10, RwInt32 arg_14)
{
    RwChar var_898[0x80];
    RwInt32 local_810;
    RwInt32 var_80C;
    RwInt32 v808;
    RwInt32 v804;
    type_3DFB6C *var_800[0x200];

    if (!unk_10)
        return 0;
    v808 = 0;
    for (v804 = 0; v804 < unk_14; v804++)
    {
        var_800[v804] = (type_3DFB6C *)sub_198800(&unk_10[v804]);
        if (var_800[v804])
            v808++;
    }
    if (v808 > 0)
    {
        local_810 = RpRandom() % 100001;
        var_80C = local_810 % v808;
        for (v804 = 0; v804 < unk_14; v804++)
        {
            if (var_800[v804])
            {
                if (--var_80C < 0)
                    return var_800[v804]->vf_00C(arg_0, arg_4, arg_8, arg_C, arg_10, arg_14);
            }
        }
    }
    else if (dword_44E870)
        sprintf(var_898, "0x%X, 0x%X", unk_04.unk_00, unk_04.unk_04);
    return 0;
}
// match: ?vf_000@type_3DFE50@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00194760
// sp-match: ?vf_000@type_3DFE50@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x001263F0
// Registers its list (kind 0x1F), which sub_194900 hands it.
RwInt32 type_3DFE50::vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4)
{
    RwUInt32 var_4;
    type_3DF8D8_ref var_10;

    RwStreamRead(arg_0, &var_10, arg_4->unk_08 - 0x1C);
    var_4 = get_ref_kind(var_10.unk_00, 0x1F);
    sub_198900((type_3DF8D8_04 *)&var_10.unk_04, 0x1F, (void (*)(RwInt32, RwInt32, RwInt32))sub_194900, (RwInt32)this, 0, 0);
    return 1;
}
// match: ?sub_1947F0@type_3DFE50@@QAEXPAURwStream@@H@Z @ 0x001947F0
// sp-match: ?sub_1947F0@type_3DFE50@@QAEXPAURwStream@@H@Z @ 0x00124610
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3DFE50::sub_1947F0(RwStream *arg_0, RwInt32 arg_4)
{
    RwInt32 var_8;
    RwInt32 l4;

    RwStreamRead(arg_0, &l4, 4);
    unk_14 = l4;
    unk_10 = (type_3DF8D8_04 *)RWSMalloc(l4 * 8, 0x34253); // not an address: a memory hint
    for (var_8 = 0; var_8 < l4; var_8++)
        RwStreamRead(arg_0, &unk_10[var_8], 8);
}
// match: ?vf_004@type_3DFE50@@UAEXXZ @ 0x00194870
// sp-match: ?vf_004@type_3DFE50@@UAEXXZ @ 0x00124680
void type_3DFE50::vf_004()
{
    if (unk_10)
    {
        ::operator delete(unk_10);
        unk_10 = 0;
    }
    if (unk_18)
    {
        ::operator delete(unk_18);
        unk_18 = 0;
    }
}
// match: ??0type_3DFE64@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x001948C0
// sp-match: ??0type_3DFE64@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x001246C0
type_3DFE64::type_3DFE64(const type_3DF8D8_04 &arg_0)
    : type_3DF8D8_base(arg_0)
{
    unk_14 = 0;
}
// match: ?vf_008@type_3DFE64@@UAEHXZ @ 0x001948F0
// sp-match: ?vf_008@type_3DFE64@@UAEHXZ @ 0x001246E0
RwInt32 type_3DFE64::vf_008()
{
    return 0x1F;
}
// match: ?sub_194900@@YAHPAUtype_3DFE64@@PAUtype_3DFE50@@PAX@Z @ 0x00194900
// sp-match: ?sub_194900@@YAHPAUtype_3DFE64@@PAUtype_3DFE50@@PAX@Z @ 0x001246F0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The uniform random sound's list callback: its references registered
// (kind 0x26) with sub_194510 filling their keys.
RwInt32 sub_194900(type_3DFE64 *arg_0, type_3DFE50 *arg_4, void *arg_8)
{
    RwInt32 var_C;
    type_3DFE50 *bp_8;
    type_3DFE64 *bp_4;

    bp_8 = arg_4;
    bp_4 = arg_0;
    bp_8->unk_14 = bp_4->unk_10;
    bp_8->unk_18 = bp_4->unk_14;
    bp_4->unk_10 = -1;
    bp_4->unk_14 = 0;
    bp_8->unk_10 = (type_3DF8D8_04 *)RWSMalloc(bp_8->unk_14 * 8, 0x34253); // not an address: a memory hint
    for (var_C = 0; var_C < bp_8->unk_14; var_C++)
        sub_198900((type_3DF8D8_04 *)&bp_8->unk_18[var_C].unk_04, 0x26, (void (*)(RwInt32, RwInt32, RwInt32))sub_194510, 0,
                   (RwInt32)&bp_8->unk_10[var_C], 0);
    return 0;
}
// match: ??0type_3DFE70@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x001949C0
// match: __ehhandler$??0type_3DFE70@@QAE@ABUtype_3DF8D8_04@@@Z-0x8 @ 0x00302340
// match: __ehhandler$??0type_3DFE70@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00302348
// sp-match: ??0type_3DFE70@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00124770
type_3DFE70::type_3DFE70(const type_3DF8D8_04 &arg_0)
    : type_3DF8D8_base(arg_0)
{
    unk_10 = (type_3DFE70_10 *)RWSMalloc(0x9C, 0x34257); // not an address: a memory hint
    memset(unk_10, 0, 0x9C);
}
// match: ?vf_004@type_3DFE70@@UAEXXZ @ 0x00194A40
// sp-match: ?vf_004@type_3DFE70@@UAEXXZ @ 0x001247F0
void type_3DFE70::vf_004()
{
    if (unk_10)
    {
        if (unk_10->unk_98)
        {
            ::operator delete(unk_10->unk_98);
            unk_10->unk_98 = 0;
        }
        ::operator delete(unk_10);
        unk_10 = 0;
    }
}
#ifdef CODFH_SP
// shape: sp_sub_18F8B0_twin (folded into sub_18F8B0, SP 0x1223D0): sub_18F8B0's body again, the
// callback of vf_000's last six dword references. Single player's compiler shares the
// `push 0; push sub_1223D0` tail among those six cases only (vf_000, SP 0x126450), which it does when
// they name another symbol than the first eight; the linker folds the two bodies.
RwInt32 sp_sub_18F8B0_twin(type_3DF8D8 *arg_0, RwInt32 arg_4, void *arg_8)
{
    RwInt32 var_8;
    RwInt32 *l4;

    l4 = (RwInt32 *)arg_8;
    var_8 = arg_0->unk_10;
    *l4 = var_8;
    return 0;
}
#define sub_18F8B0_late sp_sub_18F8B0_twin
#else
#define sub_18F8B0_late sub_18F8B0
#endif
// match: ?vf_000@type_3DFE70@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00194AB0
// sp-match: ?vf_000@type_3DFE70@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00126450
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Fills its block from its 31 references.
RwInt32 type_3DFE70::vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4)
{
    RwInt32 var_180;
    type_3DF9B8 *local_17C;
    type_3DF8D8_ref var_178[31];

    RwStreamRead(arg_0, var_178, arg_4->unk_08 - 0x1C);
    for (var_180 = 0; var_180 < 31; var_180++)
    {
        switch (get_ref_kind(var_178[var_180].unk_00, 0x1F))
        {
        case 1:
            unk_10->unk_04 = var_178[var_180].unk_04;
            if (unk_0C == 0)
                sub_198900((type_3DF8D8_04 *)&unk_10->unk_04, 3, 0, 0, 0, 0);
            else
                sub_198900((type_3DF8D8_04 *)&unk_10->unk_04, 0x30, 0, 0, 0, 0);
            break;
        case 6:
            unk_10->unk_00 = sub_198900((type_3DF8D8_04 *)&var_178[var_180].unk_04, 0x28, 0, 0, 0, 0);
            break;
        case 7:
            unk_10->unk_0C = var_178[var_180];
            sub_198900((type_3DF8D8_04 *)&var_178[var_180].unk_04, 8, 0, 0, 0, 0);
            break;
        case 11:
            unk_10->unk_18 = var_178[var_180];
            sub_198900((type_3DF8D8_04 *)&var_178[var_180].unk_04, 8, 0, 0, 0, 0);
            break;
        case 12:
            unk_10->unk_24 = var_178[var_180];
            sub_198900((type_3DF8D8_04 *)&var_178[var_180].unk_04, 8, 0, 0, 0, 0);
            break;
        case 30:
            unk_10->unk_30 = var_178[var_180];
            sub_198900((type_3DF8D8_04 *)&var_178[var_180].unk_04, 8, 0, 0, 0, 0);
            break;
        case 2:
            sub_198900((type_3DF8D8_04 *)&var_178[var_180].unk_04, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_18F8B0, 0,
                       (RwInt32)&unk_10->unk_3C, 0);
            break;
        case 8:
            sub_198900((type_3DF8D8_04 *)&var_178[var_180].unk_04, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_18F8B0, 0,
                       (RwInt32)&unk_10->unk_40, 0);
            break;
        case 13:
            sub_198900((type_3DF8D8_04 *)&var_178[var_180].unk_04, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_18F8B0, 0,
                       (RwInt32)&unk_10->unk_44, 0);
            break;
        case 23:
            sub_198900((type_3DF8D8_04 *)&var_178[var_180].unk_04, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_18F8B0, 0,
                       (RwInt32)&unk_10->unk_48, 0);
            break;
        case 19:
            local_17C = (type_3DF9B8 *)sub_198900((type_3DF8D8_04 *)&var_178[var_180].unk_04, 9, 0, 0, 0, 0);
            local_17C->unk_1C = 1;
            local_17C->sub_1904B0((void (*)(RwInt32, RwInt32, RwInt32))sub_18F8B0, 0, (RwInt32)&unk_10->unk_4C);
            break;
        case 24:
            local_17C = (type_3DF9B8 *)sub_198900((type_3DF8D8_04 *)&var_178[var_180].unk_04, 9, 0, 0, 0, 0);
            local_17C->unk_1C = 1;
            local_17C->sub_1904B0((void (*)(RwInt32, RwInt32, RwInt32))sub_18F8B0, 0, (RwInt32)&unk_10->unk_50);
            break;
        case 28:
            local_17C = (type_3DF9B8 *)sub_198900((type_3DF8D8_04 *)&var_178[var_180].unk_04, 9, 0, 0, 0, 0);
            local_17C->unk_1C = 1;
            local_17C->sub_1904B0((void (*)(RwInt32, RwInt32, RwInt32))sub_18F8B0, 0, (RwInt32)&unk_10->unk_54);
            break;
        case 25:
            local_17C = (type_3DF9B8 *)sub_198900((type_3DF8D8_04 *)&var_178[var_180].unk_04, 9, 0, 0, 0, 0);
            local_17C->unk_1C = 1;
            local_17C->sub_1904B0((void (*)(RwInt32, RwInt32, RwInt32))sub_18F8B0, 0, (RwInt32)&unk_10->unk_58);
            break;
        case 29:
            local_17C = (type_3DF9B8 *)sub_198900((type_3DF8D8_04 *)&var_178[var_180].unk_04, 9, 0, 0, 0, 0);
            local_17C->unk_1C = 1;
            local_17C->sub_1904B0((void (*)(RwInt32, RwInt32, RwInt32))sub_18F8B0, 0, (RwInt32)&unk_10->unk_5C);
            break;
        case 26:
            local_17C = (type_3DF9B8 *)sub_198900((type_3DF8D8_04 *)&var_178[var_180].unk_04, 9, 0, 0, 0, 0);
            local_17C->unk_1C = 1;
            local_17C->sub_1904B0((void (*)(RwInt32, RwInt32, RwInt32))sub_18F8B0, 0, (RwInt32)&unk_10->unk_60);
            break;
        case 14:
            local_17C = (type_3DF9B8 *)sub_198900((type_3DF8D8_04 *)&var_178[var_180].unk_04, 9, 0, 0, 0, 0);
            local_17C->unk_1C = 1;
            local_17C->sub_1904B0((void (*)(RwInt32, RwInt32, RwInt32))sub_18F8B0, 0, (RwInt32)&unk_10->unk_64);
            break;
        case 17:
            local_17C = (type_3DF9B8 *)sub_198900((type_3DF8D8_04 *)&var_178[var_180].unk_04, 9, 0, 0, 0, 0);
            local_17C->unk_1C = 1;
            local_17C->sub_1904B0((void (*)(RwInt32, RwInt32, RwInt32))sub_18F8B0, 0, (RwInt32)&unk_10->unk_68);
            break;
        case 20:
            sub_198900((type_3DF8D8_04 *)&var_178[var_180].unk_04, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_18F8B0, 0,
                       (RwInt32)&unk_10->unk_6C, 0);
            break;
        case 22:
            sub_198900((type_3DF8D8_04 *)&var_178[var_180].unk_04, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_18F8B0, 0,
                       (RwInt32)&unk_10->unk_70, 0);
            break;
        case 3:
            sub_198900((type_3DF8D8_04 *)&var_178[var_180].unk_04, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_18F8B0, 0,
                       (RwInt32)&unk_10->unk_74, 0);
            break;
        case 15:
            sub_198900((type_3DF8D8_04 *)&var_178[var_180].unk_04, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_18F8B0, 0,
                       (RwInt32)&unk_10->unk_78, 0);
            break;
        case 9:
            sub_198900((type_3DF8D8_04 *)&var_178[var_180].unk_04, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_18F8B0_late, 0,
                       (RwInt32)&unk_10->unk_7C, 0);
            break;
        case 10:
            sub_198900((type_3DF8D8_04 *)&var_178[var_180].unk_04, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_18F8B0_late, 0,
                       (RwInt32)&unk_10->unk_80, 0);
            break;
        case 18:
            sub_198900((type_3DF8D8_04 *)&var_178[var_180].unk_04, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_18F8B0_late, 0,
                       (RwInt32)&unk_10->unk_84, 0);
            break;
        case 27:
            sub_198900((type_3DF8D8_04 *)&var_178[var_180].unk_04, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_18F8B0_late, 0,
                       (RwInt32)&unk_10->unk_88, 0);
            break;
        case 21:
            local_17C = (type_3DF9B8 *)sub_198900((type_3DF8D8_04 *)&var_178[var_180].unk_04, 9, 0, 0, 0, 0);
            local_17C->unk_1C = 1;
            local_17C->sub_1904B0((void (*)(RwInt32, RwInt32, RwInt32))sub_18F8B0, 0, (RwInt32)&unk_10->unk_8C);
            break;
        case 4:
            sub_198900((type_3DF8D8_04 *)&var_178[var_180].unk_04, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_18F8B0_late, 0,
                       (RwInt32)&unk_10->unk_90, 0);
            break;
        case 5:
            sub_198900((type_3DF8D8_04 *)&var_178[var_180].unk_04, 2, (void (*)(RwInt32, RwInt32, RwInt32))sub_195BA0,
                       (RwInt32)this, (RwInt32)&unk_10->unk_98, 0);
            break;
        case 16:
            sub_198900((type_3DF8D8_04 *)&var_178[var_180].unk_04, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_18F8B0_late, 0,
                       (RwInt32)&unk_10->unk_94, 0);
            break;
        }
    }
    return 1;
}
// match: ?sub_1954D0@type_3DFE7C@@QAEPAUtype_3DF8D8@@XZ @ 0x001954D0
// sp-match: ?sub_1954D0@type_3DFE7C@@QAEPAUtype_3DF8D8@@XZ @ 0x00124830
type_3DF8D8 *type_3DFE7C::sub_1954D0()
{
    return (type_3DF8D8 *)sub_198710((type_3DF8D8_04 *)((type_825E0_id *)&unk_10->unk_04));
}
// match: ??0type_3DFE7C@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x001954F0
// sp-match: ??0type_3DFE7C@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00124840
type_3DFE7C::type_3DFE7C(const type_3DF8D8_04 &arg_0)
    : type_3DF8D8_base(arg_0)
{
    unk_10 = (type_3DFE7C_10 *)RWSMalloc(0x78, 0x34257); // not an address: a memory hint
}
// match: ?vf_008@type_3DFE7C@@UAEHXZ @ 0x00195560
// sp-match: ?vf_008@type_3DFE7C@@UAEHXZ @ 0x001248A0
RwInt32 type_3DFE7C::vf_008()
{
    return 0x28;
}
// match: ?vf_000@type_3DFE7C@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00195570
// sp-match: ?vf_000@type_3DFE7C@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x001248B0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Its fifteen references: each names a sound list (kind 0x26) whose key
// goes into its slot of the block (sub_194510).
RwInt32 type_3DFE7C::vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4)
{
    RwUInt32 var_C0;
    RwInt32 lv_BC;
    type_3DF8D8_ref var_B8[15];

    RwStreamRead(arg_0, var_B8, arg_4->unk_08 - 0x1C);
    for (lv_BC = 0; lv_BC < 15; lv_BC++)
    {
        var_C0 = get_ref_kind(var_B8[lv_BC].unk_00, 0x1F);
        switch (var_C0)
        {
        case 7:
            sub_198900((type_3DF8D8_04 *)&var_B8[lv_BC].unk_04, 0x26, (void (*)(RwInt32, RwInt32, RwInt32))sub_194510, 0,
                       (RwInt32)&((type_3DF8D8_04 *)unk_10)[0], 0);
            break;
        case 6:
            sub_198900((type_3DF8D8_04 *)&var_B8[lv_BC].unk_04, 0x26, (void (*)(RwInt32, RwInt32, RwInt32))sub_194510, 0,
                       (RwInt32)&((type_3DF8D8_04 *)unk_10)[1], 0);
            break;
        case 1:
            sub_198900((type_3DF8D8_04 *)&var_B8[lv_BC].unk_04, 0x26, (void (*)(RwInt32, RwInt32, RwInt32))sub_194510, 0,
                       (RwInt32)&((type_3DF8D8_04 *)unk_10)[2], 0);
            break;
        case 8:
            sub_198900((type_3DF8D8_04 *)&var_B8[lv_BC].unk_04, 0x26, (void (*)(RwInt32, RwInt32, RwInt32))sub_194510, 0,
                       (RwInt32)&((type_3DF8D8_04 *)unk_10)[3], 0);
            break;
        case 2:
            sub_198900((type_3DF8D8_04 *)&var_B8[lv_BC].unk_04, 0x26, (void (*)(RwInt32, RwInt32, RwInt32))sub_194510, 0,
                       (RwInt32)&((type_3DF8D8_04 *)unk_10)[4], 0);
            break;
        case 9:
            sub_198900((type_3DF8D8_04 *)&var_B8[lv_BC].unk_04, 0x26, (void (*)(RwInt32, RwInt32, RwInt32))sub_194510, 0,
                       (RwInt32)&((type_3DF8D8_04 *)unk_10)[5], 0);
            break;
        case 13:
            sub_198900((type_3DF8D8_04 *)&var_B8[lv_BC].unk_04, 0x26, (void (*)(RwInt32, RwInt32, RwInt32))sub_194510, 0,
                       (RwInt32)&((type_3DF8D8_04 *)unk_10)[6], 0);
            break;
        case 14:
            sub_198900((type_3DF8D8_04 *)&var_B8[lv_BC].unk_04, 0x26, (void (*)(RwInt32, RwInt32, RwInt32))sub_194510, 0,
                       (RwInt32)&((type_3DF8D8_04 *)unk_10)[7], 0);
            break;
        case 3:
            sub_198900((type_3DF8D8_04 *)&var_B8[lv_BC].unk_04, 0x26, (void (*)(RwInt32, RwInt32, RwInt32))sub_194510, 0,
                       (RwInt32)&((type_3DF8D8_04 *)unk_10)[8], 0);
            break;
        case 4:
            sub_198900((type_3DF8D8_04 *)&var_B8[lv_BC].unk_04, 0x26, (void (*)(RwInt32, RwInt32, RwInt32))sub_194510, 0,
                       (RwInt32)&((type_3DF8D8_04 *)unk_10)[9], 0);
            break;
        case 15:
            sub_198900((type_3DF8D8_04 *)&var_B8[lv_BC].unk_04, 0x26, (void (*)(RwInt32, RwInt32, RwInt32))sub_194510, 0,
                       (RwInt32)&((type_3DF8D8_04 *)unk_10)[10], 0);
            break;
        case 10:
            sub_198900((type_3DF8D8_04 *)&var_B8[lv_BC].unk_04, 0x26, (void (*)(RwInt32, RwInt32, RwInt32))sub_194510, 0,
                       (RwInt32)&((type_3DF8D8_04 *)unk_10)[11], 0);
            break;
        case 11:
            sub_198900((type_3DF8D8_04 *)&var_B8[lv_BC].unk_04, 0x26, (void (*)(RwInt32, RwInt32, RwInt32))sub_194510, 0,
                       (RwInt32)&((type_3DF8D8_04 *)unk_10)[12], 0);
            break;
        case 12:
            sub_198900((type_3DF8D8_04 *)&var_B8[lv_BC].unk_04, 0x26, (void (*)(RwInt32, RwInt32, RwInt32))sub_194510, 0,
                       (RwInt32)&((type_3DF8D8_04 *)unk_10)[13], 0);
            break;
        case 5:
            sub_198900((type_3DF8D8_04 *)&var_B8[lv_BC].unk_04, 0x26, (void (*)(RwInt32, RwInt32, RwInt32))sub_194510, 0,
                       (RwInt32)&((type_3DF8D8_04 *)unk_10)[14], 0);
            break;
        }
    }
    return 1;
}
// match: ??0type_3DFE88@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00195A20
// sp-match: ??0type_3DFE88@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00124A30
type_3DFE88::type_3DFE88(const type_3DF8D8_04 &arg_0)
    : type_3DF8D8_base(arg_0)
{
    unk_10 = 0;
}
// match: ?vf_000@type_3DFE88@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00195A50
// sp-match: ?vf_000@type_3DFE88@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00124A50
RwInt32 type_3DFE88::vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4)
{
    unk_10 = new type_4B9304;
    unk_10->sub_EDA50(arg_0);
    set_dword_4B9304(unk_10);
    dword_4B86FC--;
    return 1;
}
// match: ?vf_004@type_3DFE88@@UAEXXZ @ 0x00195B00
// sp-match: ?vf_004@type_3DFE88@@UAEXXZ @ 0x00126920
void type_3DFE88::vf_004()
{
    if (unk_10)
    {
        delete unk_10;
        unk_10 = 0;
    }
    dword_4B9304 = 0;
}
// match: ?sub_195B70@@YAHPAUtype_3DFE94@@HPAX@Z @ 0x00195B70
// sp-match: ?sub_195B70@@YAHPAUtype_3DFE94@@HPAX@Z @ 0x00124AD0
// A string variable's callback: the string copied to arg_8.
RwInt32 sub_195B70(type_3DFE94 *arg_0, RwInt32 arg_4, void *arg_8)
{
    RwChar *var_4;

    var_4 = (RwChar *)arg_8;
    if (arg_0->unk_10)
        strcpy(var_4, arg_0->unk_10);
    return 0;
}
// match: ?sub_195BA0@@YAHPAUtype_3DFE94@@HPAX@Z @ 0x00195BA0
// sp-match: ?sub_195BA0@@YAHPAUtype_3DFE94@@HPAX@Z @ 0x00124AF0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// A string variable's callback: a copy of the string (0 for an empty one)
// into *arg_8.
RwInt32 sub_195BA0(type_3DFE94 *arg_0, RwInt32 arg_4, void *arg_8)
{
    RwInt32 var_C;
    RwChar **bp_8;
    type_3DFE94 *bp_4;

    bp_4 = arg_0;
    var_C = strlen(bp_4->unk_10);
    bp_8 = (RwChar **)arg_8;
    if (var_C > 0)
    {
        *bp_8 = (RwChar *)RWSMalloc(var_C + 1, 0x34257); // not an address: a memory hint
        strcpy(*bp_8, bp_4->unk_10);
    }
    else
        *bp_8 = 0;
    return 0;
}
// match: ?sub_195C10@@YAHPAUtype_3DFE94@@HPAX@Z @ 0x00195C10
// sp-match: ?sub_195C10@@YAHPAUtype_3DFE94@@HPAX@Z @ 0x00124B50
// A string variable's callback: the FNV hash of the upper-cased string into
// *arg_8 (CWeaponBehavior's names).
RwInt32 sub_195C10(type_3DFE94 *arg_0, RwInt32 arg_4, void *arg_8)
{
    RwUInt32 *var_4;

    var_4 = (RwUInt32 *)arg_8;
    _strupr(arg_0->unk_10);
    *var_4 = sub_16C800(arg_0->unk_10, 0x811C9DC5);
    return 0;
}
// match: ?vf_000@type_3DFE94@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00195C50
// sp-match: ?vf_000@type_3DFE94@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00124B80
RwInt32 type_3DFE94::vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4)
{
    RwInt32 var_4;

    var_4 = arg_4->unk_08 - 0x1C;
    unk_10 = (RwChar *)RWSMalloc(var_4 + 1, 0x34257); // not an address: a memory hint
    if (var_4 > 0)
    {
        RwStreamRead(arg_0, unk_10, var_4);
        unk_10[var_4] = 0;
    }
    unk_10[var_4] = 0;
    return 1;
}
// match: ??0type_3DFE94@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00195CD0
// sp-match: ??0type_3DFE94@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00124BD0
type_3DFE94::type_3DFE94(const type_3DF8D8_04 &arg_0)
    : type_3DF8D8_base(arg_0)
{
    unk_10 = 0;
}
// match: ?vf_008@type_3DFE94@@UAEHXZ @ 0x00195D00
// sp-match: ?vf_008@type_3DFE94@@UAEHXZ @ 0x00124BF0
RwInt32 type_3DFE94::vf_008()
{
    return 2;
}
// match: ??0type_3DFEA4@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00195D10
// sp-match: ??0type_3DFEA4@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00124C10
type_3DFEA4::type_3DFEA4(const type_3DF8D8_04 &arg_0)
    : type_3DF8D8_base(arg_0)
{
}
// match: ?vf_008@type_3DFEA4@@UAEHXZ @ 0x00195D60
// sp-match: ?vf_008@type_3DFEA4@@UAEHXZ @ 0x00124C40
RwInt32 type_3DFEA4::vf_008()
{
    return 0x2B;
}
// match: ?vf_000@type_3DFEA4@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00195D70
// sp-match: ?vf_000@type_3DFEA4@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00126950
// Keeps its model object's reference (registering it, kind 3) and a
// variable whose value names a pickup (sub_195EB0).
RwInt32 type_3DFEA4::vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4)
{
    type_3DF8D8_ref var_18[2];
    RwInt32 var_1C;

    RwStreamRead(arg_0, var_18, arg_4->unk_08 - 0x1C);
    for (var_1C = 0; var_1C < 2; var_1C++)
    {
        switch (get_ref_kind(var_18[var_1C].unk_00, 0x1F))
        {
        case 1:
            unk_14 = var_18[var_1C];
            sub_198900((type_3DF8D8_04 *)&var_18[var_1C].unk_04, 3, 0, 0, 0, 0);
            break;
        case 2:
            sub_198900((type_3DF8D8_04 *)&var_18[var_1C].unk_04, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_195EB0, 0,
                       (RwInt32)&unk_14.unk_04, 0);
            break;
        }
    }
    return 1;
}
// match: ?sub_195EB0@@YAHPAUtype_3DF8D8@@HPAUtype_3DF8D8_04@@@Z @ 0x00195EB0
// sp-match: ?sub_195EB0@@YAHPAUtype_3DF8D8@@HPAUtype_3DF8D8_04@@@Z @ 0x00124C50
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The pickup settings the variable's value names take the key arg_8.
RwInt32 sub_195EB0(type_3DF8D8 *arg_0, RwInt32 arg_4, type_3DF8D8_04 *arg_8)
{
    type_3DF8D8_04 *var_C;
    type_4C09B0 *bp_8;
    RwInt32 bp_4;

    var_C = arg_8;
    sub_18F8B0(arg_0, arg_4, &bp_4);
    bp_8 = sub_FB6C0(bp_4);
    bp_8->unk_04.unk_00 = var_C->unk_00;
    bp_8->unk_04.unk_04 = var_C->unk_04;
    return 0;
}
// match: ??0type_3DFEB0_obj@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00195F00
// sp-match: ??0type_3DFEB0_obj@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00127460
type_3DFEB0_obj::type_3DFEB0_obj(const type_3DF8D8_04 &arg_0)
    : type_3DFEEC_obj(arg_0)
{
}
// match: ?vf_008@type_3DFEB0_obj@@UAEHXZ @ 0x00195F30
// sp-match: ?vf_008@type_3DFEB0_obj@@UAEHXZ @ 0x00127480
RwInt32 type_3DFEB0_obj::vf_008()
{
    return 0x2E;
}
// match: ?vf_000@type_3DFEB0_obj@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00195F40
// sp-match: ?vf_000@type_3DFEB0_obj@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00127490
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Registers the kind-0x2C objects among its references (sub_196020 names
// it after the first).
RwInt32 type_3DFEB0_obj::vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4)
{
    RwInt32 var_C;
    type_3DF8D8_ref *bp_8;
    RwInt32 bp_4;

    bp_8 = (type_3DF8D8_ref *)RWSMalloc(arg_4->unk_04 - 0x1C, 0x34257); // not an address: a memory hint
    RwStreamRead(arg_0, bp_8, arg_4->unk_04 - 0x1C);
    bp_4 = (RwUInt32)(arg_4->unk_04 - 0x1C) / 0xC;
    for (var_C = 0; var_C < bp_4; var_C++)
    {
        if (get_ref_low(bp_8[var_C].unk_00, 0xF, 0, 0) == 8)
            sub_198900((type_3DF8D8_04 *)&bp_8[var_C].unk_04, 0x2C, (void (*)(RwInt32, RwInt32, RwInt32))sub_196020, 0,
                       (RwInt32)this, 0);
    }
    ::operator delete(bp_8);
    return 1;
}
// match: ?sub_196020@@YAHPAUtype_3DFEEC_obj@@HPAUtype_3DFEB0_obj@@@Z @ 0x00196020
// sp-match: ?sub_196020@@YAHPAUtype_3DFEEC_obj@@HPAUtype_3DFEB0_obj@@@Z @ 0x001269F0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_196020(type_3DFEEC_obj *arg_0, RwInt32 arg_4, type_3DFEB0_obj *arg_8)
{
    type_3DFEEC_obj *var_8;
    type_3DFEB0_obj *l4;

    var_8 = arg_0;
    l4 = arg_8;
    if (!l4->unk_14)
        sub_198900((type_3DF8D8_04 *)&var_8->unk_18.unk_04, 2, (void (*)(RwInt32, RwInt32, RwInt32))sub_196480, 0,
                   (RwInt32)&l4->unk_14, 0);
    return 0;
}
// match: ?vf_004@type_3DFEB0_obj@@UAEXXZ @ 0x00196070
// sp-match: ?vf_004@type_3DFEB0_obj@@UAEXXZ @ 0x00126A20
void type_3DFEB0_obj::vf_004()
{
    type_3DFEEC_obj::vf_004();
}
// match: ??0type_3DFEC4_obj@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00196090
// sp-match: ??0type_3DFEC4_obj@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00126A30
type_3DFEC4_obj::type_3DFEC4_obj(const type_3DF8D8_04 &arg_0)
    : type_3DFED8_obj(arg_0)
{
    unk_10 = RwMatrixCreate();
    RwMatrixSetIdentity(unk_10);
}
// match: ?vf_008@type_3DFEC4_obj@@UAEHXZ @ 0x00196190
// sp-match: ?vf_008@type_3DFEC4_obj@@UAEHXZ @ 0x00126AB0
RwInt32 type_3DFEC4_obj::vf_008()
{
    return 0x2D;
}
// match: ?vf_00C@type_3DFEC4_obj@@UAEPAURwV3d@@XZ @ 0x001961A0
// sp-match: ?vf_00C@type_3DFEC4_obj@@UAEPAURwV3d@@XZ @ 0x00126AC0
RwV3d *type_3DFEC4_obj::vf_00C()
{
    return &unk_10->pos;
}
// match: ?vf_010@type_3DFEC4_obj@@UAEPAURwV3d@@XZ @ 0x001961C0
// sp-match: ?vf_010@type_3DFEC4_obj@@UAEPAURwV3d@@XZ @ 0x00126AD0
RwV3d *type_3DFEC4_obj::vf_010()
{
    return &unk_10->at;
}
// match: ?vf_000@type_3DFEC4_obj@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x001961E0
// sp-match: ?vf_000@type_3DFEC4_obj@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00124C90
RwInt32 type_3DFEC4_obj::vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4)
{
    RwReal var_40[16];

    RwStreamRead(arg_0, var_40, arg_4->unk_04 - 0x1C);
    unk_10->right.x = var_40[0];
    unk_10->right.y = var_40[1];
    unk_10->right.z = var_40[2];
    unk_10->up.x = var_40[4];
    unk_10->up.y = var_40[5];
    unk_10->up.z = var_40[6];
    unk_10->at.x = var_40[8];
    unk_10->at.y = var_40[9];
    unk_10->at.z = var_40[10];
    unk_10->pos.x = var_40[12];
    unk_10->pos.y = var_40[13];
    unk_10->pos.z = var_40[14];
    return 1;
}
// match: ?vf_004@type_3DFEC4_obj@@UAEXXZ @ 0x001962A0
// sp-match: ?vf_004@type_3DFEC4_obj@@UAEXXZ @ 0x00124D40
void type_3DFEC4_obj::vf_004()
{
    if (unk_10)
    {
        RwMatrixDestroy(unk_10);
        unk_10 = 0;
    }
}
// match: ??0type_3DFEEC_obj@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x001962D0
// sp-match: ??0type_3DFEEC_obj@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00126AE0
type_3DFEEC_obj::type_3DFEEC_obj(const type_3DF8D8_04 &arg_0)
    : type_3DFED8_obj(arg_0)
{
    unk_10 = 0;
    unk_14 = 0;
    unk_24.unk_00 = 0;
    unk_24.unk_04 = 0;
    unk_24.unk_08 = 0;
    unk_30 = 0;
}
// match: ?vf_008@type_3DFEEC_obj@@UAEHXZ @ 0x00196370
// sp-match: ?vf_008@type_3DFEEC_obj@@UAEHXZ @ 0x00126B20
RwInt32 type_3DFEEC_obj::vf_008()
{
    return 0x2C;
}
// match: ?vf_000@type_3DFEEC_obj@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00196380
// sp-match: ?vf_000@type_3DFEEC_obj@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00124D60
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Keeps its reference.
RwInt32 type_3DFEEC_obj::vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4)
{
    RwInt32 var_14;
    RwUInt32 lv_10;
    type_3DF8D8_ref var_C[1];

    RwStreamRead(arg_0, var_C, arg_4->unk_04 - 0x1C);
    for (var_14 = 0; var_14 < 1; var_14++)
    {
        lv_10 = get_ref_kind(var_C[var_14].unk_00, 0x1F);
        switch (lv_10)
        {
        case 1:
            unk_18.unk_00 = var_C[var_14].unk_00;
            unk_18.unk_04.unk_00 = var_C[var_14].unk_04.unk_00;
            unk_18.unk_04.unk_04 = var_C[var_14].unk_04.unk_04;
            break;
        }
    }
    return 1;
}
// match: ?sub_196480@@YAHPAUtype_3DFE94@@HPAX@Z @ 0x00196480
// sp-match: ?sub_196480@@YAHPAUtype_3DFE94@@HPAX@Z @ 0x00124DC0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// A string variable's callback: a copy of the string, cut to 31 characters,
// into *arg_8 (0 for an empty one).
RwInt32 sub_196480(type_3DFE94 *arg_0, RwInt32 arg_4, void *arg_8)
{
    RwChar *var_10;
    RwInt32 var_C;
    RwChar **bp_8;
    type_3DFE94 *bp_4;

    bp_4 = arg_0;
    var_C = strlen(bp_4->unk_10);
    bp_8 = (RwChar **)arg_8;
    if (var_C > 0)
    {
        if (var_C < 0x20)
        {
            *bp_8 = (RwChar *)RWSMalloc(var_C + 1, 0x34257); // not an address: a memory hint
            strcpy(*bp_8, bp_4->unk_10);
        }
        else
        {
            *bp_8 = (RwChar *)RWSMalloc(0x20, 0x34257); // not an address: a memory hint
            strncpy(*bp_8, bp_4->unk_10, 0x20);
            var_10 = *bp_8;
            var_10[0x1F] = 0;
        }
    }
    else
        *bp_8 = 0;
    return 0;
}
// match: ?vf_00C@type_3DFEEC_obj@@UAEPAURwV3d@@XZ @ 0x00196530
// sp-match: ?vf_00C@type_3DFEEC_obj@@UAEPAURwV3d@@XZ @ 0x00124E70
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Its point: its entity's position, its trigger's, or its path node's.
RwV3d *type_3DFEEC_obj::vf_00C()
{
    type_3DFEEC_trig *var_14;
    type_3DFEEC_24 *lv_10;
    type_3DFEEC_24 *var_C;
    type_3D3548 *bp_8;
    RwV3d *bp_4;

    bp_4 = 0;
    if (unk_10 & 2)
    {
        var_C = &unk_24;
        bp_8 = ((type_D48D0 *)&var_C->unk_00)->sub_D4910();
        if (bp_8)
            bp_4 = bp_8->sub_CD550();
    }
    else if (unk_10 & 1)
    {
        lv_10 = &unk_24;
        var_14 = lv_10->unk_08;
        if (var_14)
            bp_4 = &var_14->unk_90;
    }
    else if ((unk_10 & 0x10) && unk_24.unk_00)
        bp_4 = &((type_F8350 *)unk_24.unk_00)->unk_10;
    return bp_4;
}
// match: ?vf_010@type_3DFEEC_obj@@UAEPAURwV3d@@XZ @ 0x001965D0
// sp-match: ?vf_010@type_3DFEEC_obj@@UAEPAURwV3d@@XZ @ 0x00124EC0
// Its direction: its entity's frame's (the world matrix's at), its
// trigger's, or its path node's orientation's at (kept at +0x28).
RwV3d *type_3DFEEC_obj::vf_010()
{
    RwV3d *var_8;
    type_3DFEEC_24 *var_C;
    type_3D3548 *var_10;
    RwFrame *var_14;
    type_3DFEEC_24 *var_18;
    type_3DFEEC_trig *var_1C;
    RwMatrix var_60;
    RtQuat *var_64;

    var_8 = 0;
    if (unk_10 & 2)
    {
        var_C = &unk_24;
        var_10 = ((type_D48D0 *)&var_C->unk_00)->sub_D4910();
        if (var_10)
        {
            var_14 = var_10->unk_338.unk_08;
            var_8 = &var_14->ltm.at;
        }
    }
    else if (unk_10 & 1)
    {
        var_18 = &unk_24;
        var_1C = var_18->unk_08;
        if (var_1C)
            var_8 = &var_1C->unk_80;
    }
    else if ((unk_10 & 0x10) && unk_24.unk_00 && (((type_F8350 *)unk_24.unk_00)->unk_00 & 1))
    {
        RwMatrixSetIdentity(&var_60);
        var_64 = &((type_F8350 *)unk_24.unk_00)->unk_1C;
        RtQuatConvertToMatrix(var_64, &var_60);
        *(RwV3d *)&unk_24.unk_04 = var_60.at;
        var_8 = (RwV3d *)&unk_24.unk_04;
    }
    return var_8;
}
// match: ??0type_3DFF00@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x001968C0
// sp-match: ??0type_3DFF00@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00124FF0
type_3DFF00::type_3DFF00(const type_3DF8D8_04 &arg_0)
    : type_3DF8D8_base(arg_0)
{
}
// match: ?vf_008@type_3DFF00@@UAEHXZ @ 0x00196940
// sp-match: ?vf_008@type_3DFF00@@UAEHXZ @ 0x00125020
RwInt32 type_3DFF00::vf_008()
{
    return 0x2F;
}
// match: ?vf_000@type_3DFF00@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00196950
// sp-match: ?vf_000@type_3DFF00@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00126B30
RwInt32 type_3DFF00::vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4)
{
    type_3DF8D8_ref var_48[6];
    RwInt32 var_4C;
    RwUInt32 var_50;

    RwStreamRead(arg_0, var_48, arg_4->unk_08 - 0x1C);
    for (var_4C = 0; var_4C < 6; var_4C++)
    {
        var_50 = get_ref_kind(var_48[var_4C].unk_00, 0x1F);
        switch (var_50)
        {
        case 1:
            unk_14 = var_48[var_4C];
            sub_198900((type_3DF8D8_04 *)&var_48[var_4C].unk_04, 3, 0, 0, 0, 0);
            break;
        case 2:
            unk_20 = var_48[var_4C];
            sub_198900((type_3DF8D8_04 *)&var_48[var_4C].unk_04, 3, 0, 0, 0, 0);
            break;
        case 3:
            sub_198900((type_3DF8D8_04 *)&var_48[var_4C].unk_04, 2, (void (*)(RwInt32, RwInt32, RwInt32))sub_195C10, 0,
                       (RwInt32)&unk_2C, 0);
            break;
        case 5:
            sub_198900((type_3DF8D8_04 *)&var_48[var_4C].unk_04, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_196B70, 0,
                       (RwInt32)this, 0);
            break;
        case 4:
            sub_198900((type_3DF8D8_04 *)&var_48[var_4C].unk_04, 2, (void (*)(RwInt32, RwInt32, RwInt32))sub_195C10, 0,
                       (RwInt32)&unk_30, 0);
            break;
        case 6:
            sub_198900((type_3DF8D8_04 *)&var_48[var_4C].unk_04, 2, (void (*)(RwInt32, RwInt32, RwInt32))sub_195C10, 0,
                       (RwInt32)&unk_34, 0);
            break;
        }
    }
    return 1;
}
// match: ?sub_196B70@@YAHPAUtype_3DF8D8@@HPAUtype_3DFF00@@@Z @ 0x00196B70
// sp-match: ?sub_196B70@@YAHPAUtype_3DF8D8@@HPAUtype_3DFF00@@@Z @ 0x00125030
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The mounted weapon settings the variable's value names take the record's
// two model keys, with the record as their animation.
RwInt32 sub_196B70(type_3DF8D8 *arg_0, RwInt32 arg_4, type_3DFF00 *arg_8)
{
    type_4E1B70 *var_C;
    type_3DFF00 *bp_8;
    RwInt32 bp_4;

    bp_8 = arg_8;
    sub_18F8B0(arg_0, arg_4, &bp_4);
    var_C = sub_166990(bp_4);
    var_C->unk_00.unk_00 = bp_8->unk_14.unk_04.unk_00;
    var_C->unk_00.unk_04 = bp_8->unk_14.unk_04.unk_04;
    var_C->unk_08.unk_00 = bp_8->unk_20.unk_04.unk_00;
    var_C->unk_08.unk_04 = bp_8->unk_20.unk_04.unk_04;
    bp_8->unk_10 = bp_4;
    var_C->unk_C8 = (type_4E1B70_C8 *)bp_8;
    var_C->unk_F8 = 1;
    return 0;
}
// match: ??0type_3DFF0C@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00196C00
// sp-match: ??0type_3DFF0C@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00125090
type_3DFF0C::type_3DFF0C(const type_3DF8D8_04 &arg_0)
    : type_3DF8D8_base(arg_0)
{
}
// match: ?vf_008@type_3DFF0C@@UAEHXZ @ 0x00196C30
// sp-match: ?vf_008@type_3DFF0C@@UAEHXZ @ 0x001250B0
RwInt32 type_3DFF0C::vf_008()
{
    return 0x31;
}
// match: ?vf_000@type_3DFF0C@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00196C40
// sp-match: ?vf_000@type_3DFF0C@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x001250C0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_3DFF0C::vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4)
{
    RwInt32 var_18;
    RwUInt32 var_14;
    type_3DF8D8_ref ebp_10;
    RwInt32 l4;

    var_14 = arg_4->unk_08 - 0x1C;
    l4 = var_14 / 0xC;
    for (var_18 = 0; var_18 < l4; var_18++)
    {
        RwStreamRead(arg_0, &ebp_10, 0xC);
        sub_198900((type_3DF8D8_04 *)&ebp_10.unk_04, 0x32, 0, 0, 0, 0);
    }
    return 1;
}
// match: ??0type_3DFF18@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00196CD0
// sp-match: ??0type_3DFF18@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00125130
type_3DFF18::type_3DFF18(const type_3DF8D8_04 &arg_0)
    : type_3DF8D8_base(arg_0)
{
    unk_10 = 0;
    unk_14 = 0;
    unk_18 = 0;
}
// match: ?vf_008@type_3DFF18@@UAEHXZ @ 0x00196D20
// sp-match: ?vf_008@type_3DFF18@@UAEHXZ @ 0x00125160
RwInt32 type_3DFF18::vf_008()
{
    return 0x32;
}
// match: ?vf_000@type_3DFF18@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00196D30
// sp-match: ?vf_000@type_3DFF18@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00126C40
// Its fifteen references, one per language: it keeps the string of the one
// for the game's language (sub_197520) and only registers the others.
RwInt32 type_3DFF18::vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4)
{
    type_3DF8D8_ref var_B8[15];
    RwInt32 var_BC;

    RwStreamRead(arg_0, var_B8, arg_4->unk_08 - 0x1C);
    for (var_BC = 0; var_BC < 15; var_BC++)
    {
        switch (get_ref_kind(var_B8[var_BC].unk_00, 0x1F))
        {
        case 1:
            if (sub_19B0A0() == 0xE)
                sub_198900((type_3DF8D8_04 *)&var_B8[var_BC].unk_04, 2, (void (*)(RwInt32, RwInt32, RwInt32))sub_197520,
                           (RwInt32)this, (RwInt32)&unk_10, 0);
            else
                sub_198900((type_3DF8D8_04 *)&var_B8[var_BC].unk_04, 2, 0, 0, 0, 0);
            break;
        case 2:
            if (sub_19B0A0() == 0xA)
                sub_198900((type_3DF8D8_04 *)&var_B8[var_BC].unk_04, 2, (void (*)(RwInt32, RwInt32, RwInt32))sub_197520,
                           (RwInt32)this, (RwInt32)&unk_10, 0);
            else
                sub_198900((type_3DF8D8_04 *)&var_B8[var_BC].unk_04, 2, 0, 0, 0, 0);
            break;
        case 11:
            if (sub_19B0A0() == 0)
                sub_198900((type_3DF8D8_04 *)&var_B8[var_BC].unk_04, 2, (void (*)(RwInt32, RwInt32, RwInt32))sub_197520,
                           (RwInt32)this, (RwInt32)&unk_10, 0);
            else
                sub_198900((type_3DF8D8_04 *)&var_B8[var_BC].unk_04, 2, 0, 0, 0, 0);
            break;
        case 3:
            if (sub_19B0A0() == 0xB)
                sub_198900((type_3DF8D8_04 *)&var_B8[var_BC].unk_04, 2, (void (*)(RwInt32, RwInt32, RwInt32))sub_197520,
                           (RwInt32)this, (RwInt32)&unk_10, 0);
            else
                sub_198900((type_3DF8D8_04 *)&var_B8[var_BC].unk_04, 2, 0, 0, 0, 0);
            break;
        case 12:
            if (sub_19B0A0() == 2)
                sub_198900((type_3DF8D8_04 *)&var_B8[var_BC].unk_04, 2, (void (*)(RwInt32, RwInt32, RwInt32))sub_197520,
                           (RwInt32)this, (RwInt32)&unk_10, 0);
            else
                sub_198900((type_3DF8D8_04 *)&var_B8[var_BC].unk_04, 2, 0, 0, 0, 0);
            break;
        case 4:
            if (sub_19B0A0() == 1)
                sub_198900((type_3DF8D8_04 *)&var_B8[var_BC].unk_04, 2, (void (*)(RwInt32, RwInt32, RwInt32))sub_197520,
                           (RwInt32)this, (RwInt32)&unk_10, 0);
            else
                sub_198900((type_3DF8D8_04 *)&var_B8[var_BC].unk_04, 2, 0, 0, 0, 0);
            break;
        case 13:
            if (sub_19B0A0() == 5)
                sub_198900((type_3DF8D8_04 *)&var_B8[var_BC].unk_04, 2, (void (*)(RwInt32, RwInt32, RwInt32))sub_197520,
                           (RwInt32)this, (RwInt32)&unk_10, 0);
            else
                sub_198900((type_3DF8D8_04 *)&var_B8[var_BC].unk_04, 2, 0, 0, 0, 0);
            break;
        case 5:
            if (sub_19B0A0() == 0xD)
                sub_198900((type_3DF8D8_04 *)&var_B8[var_BC].unk_04, 2, (void (*)(RwInt32, RwInt32, RwInt32))sub_197520,
                           (RwInt32)this, (RwInt32)&unk_10, 0);
            else
                sub_198900((type_3DF8D8_04 *)&var_B8[var_BC].unk_04, 2, 0, 0, 0, 0);
            break;
        case 14:
            if (sub_19B0A0() == 7)
                sub_198900((type_3DF8D8_04 *)&var_B8[var_BC].unk_04, 2, (void (*)(RwInt32, RwInt32, RwInt32))sub_197520,
                           (RwInt32)this, (RwInt32)&unk_10, 0);
            else
                sub_198900((type_3DF8D8_04 *)&var_B8[var_BC].unk_04, 2, 0, 0, 0, 0);
            break;
        case 15:
            if (sub_19B0A0() == 9)
                sub_198900((type_3DF8D8_04 *)&var_B8[var_BC].unk_04, 2, (void (*)(RwInt32, RwInt32, RwInt32))sub_197520,
                           (RwInt32)this, (RwInt32)&unk_10, 0);
            else
                sub_198900((type_3DF8D8_04 *)&var_B8[var_BC].unk_04, 2, 0, 0, 0, 0);
            break;
        case 6:
            if (sub_19B0A0() == 0xC)
                sub_198900((type_3DF8D8_04 *)&var_B8[var_BC].unk_04, 2, (void (*)(RwInt32, RwInt32, RwInt32))sub_197520,
                           (RwInt32)this, (RwInt32)&unk_10, 0);
            else
                sub_198900((type_3DF8D8_04 *)&var_B8[var_BC].unk_04, 2, 0, 0, 0, 0);
            break;
        case 7:
            if (sub_19B0A0() == 4)
                sub_198900((type_3DF8D8_04 *)&var_B8[var_BC].unk_04, 2, (void (*)(RwInt32, RwInt32, RwInt32))sub_197520,
                           (RwInt32)this, (RwInt32)&unk_10, 0);
            else
                sub_198900((type_3DF8D8_04 *)&var_B8[var_BC].unk_04, 2, 0, 0, 0, 0);
            break;
        case 8:
            if (sub_19B0A0() == 3)
                sub_198900((type_3DF8D8_04 *)&var_B8[var_BC].unk_04, 2, (void (*)(RwInt32, RwInt32, RwInt32))sub_197520,
                           (RwInt32)this, (RwInt32)&unk_10, 0);
            else
                sub_198900((type_3DF8D8_04 *)&var_B8[var_BC].unk_04, 2, 0, 0, 0, 0);
            break;
        case 9:
            if (sub_19B0A0() == 6)
                sub_198900((type_3DF8D8_04 *)&var_B8[var_BC].unk_04, 2, (void (*)(RwInt32, RwInt32, RwInt32))sub_197520,
                           (RwInt32)this, (RwInt32)&unk_10, 0);
            else
                sub_198900((type_3DF8D8_04 *)&var_B8[var_BC].unk_04, 2, 0, 0, 0, 0);
            break;
        case 10:
            if (sub_19B0A0() == 8)
                sub_198900((type_3DF8D8_04 *)&var_B8[var_BC].unk_04, 2, (void (*)(RwInt32, RwInt32, RwInt32))sub_197520,
                           (RwInt32)this, (RwInt32)&unk_10, 0);
            else
                sub_198900((type_3DF8D8_04 *)&var_B8[var_BC].unk_04, 2, 0, 0, 0, 0);
            break;
        }
    }
    return 1;
}
// match: ?sub_1974B0@type_3DFF18@@QAEXXZ @ 0x001974B0
// sp-match: ?sub_1974B0@type_3DFF18@@QAEXXZ @ 0x00125170
// Cuts the string at its '}' (unk_18 the rest) and then its '{' (unk_14).
void type_3DFF18::sub_1974B0()
{
    RwChar *var_4;

    if (!unk_10)
        return;
    var_4 = strchr(unk_10, '}');
    if (var_4)
    {
        *var_4 = 0;
        unk_18 = var_4 + 1;
    }
    var_4 = strchr(unk_10, '{');
    if (var_4)
    {
        *var_4 = 0;
        unk_14 = var_4 + 1;
    }
}
// match: ?sub_197520@@YAHPAUtype_3DFE94@@PAUtype_3DFF18@@PAX@Z @ 0x00197520
// sp-match: ?sub_197520@@YAHPAUtype_3DFE94@@PAUtype_3DFF18@@PAX@Z @ 0x001251B0
// The localised string's callback: a copy of the string variable's value
// into its unk_10, then cut.
RwInt32 sub_197520(type_3DFE94 *arg_0, type_3DFF18 *arg_4, void *arg_8)
{
    sub_195BA0(arg_0, (RwInt32)arg_4, arg_8);
    arg_4->sub_1974B0();
    return 0;
}
// match: ?sub_197550@type_3DF8D8@@QAEPBDPADH@Z @ 0x00197550
// sp-match: ?sub_197550@type_3DF8D8@@QAEPBDPADH@Z @ 0x001251E0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
const RwChar *type_3DF8D8::sub_197550(RwChar *arg_0, RwInt32 arg_4)
{
    RwChar var_C[4];
    RwChar *bp_8;
    RwChar *bp_4;

    if (!unk_10_name || !arg_0)
    {
        if (!unk_10_name)
            return "NULL - REPLACE ME";
        return unk_10_name;
    }
    strcpy(arg_0, unk_10_name);
    bp_8 = strstr(arg_0, "#");
    if (bp_8)
    {
        bp_4 = strstr(unk_10_name, "#") + 1;
        sprintf(var_C, "%d", arg_4);
        memcpy(bp_8, var_C, strlen(var_C));
        sprintf(bp_8 + strlen(var_C), "%s", bp_4);
    }
    return arg_0;
}
#ifdef CODFH_SP
// sp-match: ?sp_sub_1252B0@type_3DF8D8@@QAEPBDPADH@Z @ 0x001252B0
// Single player's copy of sub_197550 for the text at +0x14 (no "NULL - REPLACE ME":
// a null text or buffer returns the text; SP 0x1252B0).
const RwChar *type_3DF8D8::sp_sub_1252B0(RwChar *arg_0, RwInt32 arg_4)
{
    RwChar var_C[4];
    RwChar *bp_8;
    RwChar *bp_4;

    if (!unk_14 || !arg_0)
        return (const RwChar *)unk_14;
    strcpy(arg_0, (const RwChar *)unk_14);
    bp_8 = strstr(arg_0, "#");
    if (bp_8)
    {
        bp_4 = strstr((RwChar *)unk_14, "#") + 1;
        sprintf(var_C, "%d", arg_4);
        memcpy(bp_8, var_C, strlen(var_C));
        sprintf(bp_8 + strlen(var_C), "%s", bp_4);
    }
    return arg_0;
}
#endif
#ifdef CODFH_SP
// sp-match: ?sp_sub_125370@type_3DF8D8@@QAEPBDPADH@Z @ 0x00125370
// Single player's copy of sub_197550 for the text at +0x18 (SP 0x125370).
const RwChar *type_3DF8D8::sp_sub_125370(RwChar *arg_0, RwInt32 arg_4)
{
    RwChar var_C[4];
    RwChar *bp_8;
    RwChar *bp_4;

    if (!unk_18 || !arg_0)
        return (const RwChar *)unk_18;
    strcpy(arg_0, (const RwChar *)unk_18);
    bp_8 = strstr(arg_0, "#");
    if (bp_8)
    {
        bp_4 = strstr((RwChar *)unk_18, "#") + 1;
        sprintf(var_C, "%d", arg_4);
        memcpy(bp_8, var_C, strlen(var_C));
        sprintf(bp_8 + strlen(var_C), "%s", bp_4);
    }
    return arg_0;
}
#endif
// match: ?vf_004@type_3DFF18@@UAEXXZ @ 0x00197630
// sp-match: ?vf_004@type_3DFF18@@UAEXXZ @ 0x00125430
void type_3DFF18::vf_004()
{
    if (unk_10)
    {
        ::operator delete(unk_10);
        unk_10 = 0;
    }
}
// match: ??0type_3DFF3C@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00197660
// sp-match: ??0type_3DFF3C@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00125450
type_3DFF3C::type_3DFF3C(const type_3DF8D8_04 &arg_0)
    : type_3DF8D8_base(arg_0)
{
    unk_10 = 0;
    unk_14 = 0;
    unk_18 = 0;
}
// match: ?vf_008@type_3DFF3C@@UAEHXZ @ 0x001976B0
// sp-match: ?vf_008@type_3DFF3C@@UAEHXZ @ 0x00125480
RwInt32 type_3DFF3C::vf_008()
{
    return 0x33;
}
// match: ?vf_000@type_3DFF3C@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x001976C0
// sp-match: ?vf_000@type_3DFF3C@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00126E80
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_3DFF3C::vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4)
{
    RwInt32 var_18;
    RwUInt32 var_14;
    type_3DF8D8_ref ebp_10;
    RwInt32 l4;

    var_14 = arg_4->unk_08 - 0x1C;
    l4 = var_14 / 0xC;
    unk_10 = l4;
    for (var_18 = 0; var_18 < l4; var_18++)
    {
        RwStreamRead(arg_0, &ebp_10, 0xC);
        sub_198900((type_3DF8D8_04 *)&ebp_10.unk_04, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_197760, (RwInt32)this,
                   0, 0);
    }
    return 1;
}
// match: ?sub_197760@@YAHPAUtype_3DF8D8@@PAUtype_3DFF3C@@H@Z @ 0x00197760
// sp-match: ?sub_197760@@YAHPAUtype_3DF8D8@@PAUtype_3DFF3C@@H@Z @ 0x00125490
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Each index sound's callback: once the last is in, the table (every entry
// -1) goes into dword_4E5E40 and the surface materials are asked for.
RwInt32 sub_197760(type_3DF8D8 *arg_0, type_3DFF3C *arg_4, RwInt32 arg_8)
{
    RwInt32 var_14;
    type_4E5E40 *lv_10;
    type_4E5E40_08 *var_C;
    type_3DFF3C *bp_8;
    RwInt32 bp_4;

    bp_4 = 0;
    bp_8 = arg_4;
    bp_4 = arg_0->unk_10;
    if (bp_4 > bp_8->unk_14)
        bp_8->unk_14 = bp_4;
    bp_8->unk_18++;
    if (bp_8->unk_18 == bp_8->unk_10)
    {
        bp_8->unk_14++;
        var_C = new type_4E5E40_08[bp_8->unk_14];
        for (var_14 = 0; var_14 < bp_8->unk_14; var_14++)
        {
            var_C[var_14].unk_04[0] = -1;
            var_C[var_14].unk_00 = -1;
            var_C[var_14].unk_04[1] = -1;
        }
        lv_10 = &dword_4E5E40;
        lv_10->unk_08 = var_C;
        lv_10->unk_00[1] = bp_8->unk_10;
        lv_10->unk_00[0] = bp_8->unk_14;
        dword_4B86FC--;
        sub_1989D0("Surfaces+Materials", 0x34, 0, 0, 0);
    }
    return 0;
}
// match: ??0type_3DFF5C@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00197880
// sp-match: ??0type_3DFF5C@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00125530
type_3DFF5C::type_3DFF5C(const type_3DF8D8_04 &arg_0)
    : type_3DF8D8_base(arg_0)
{
}
// match: ?vf_008@type_3DFF5C@@UAEHXZ @ 0x001978B0
// sp-match: ?vf_008@type_3DFF5C@@UAEHXZ @ 0x00125550
RwInt32 type_3DFF5C::vf_008()
{
    return 0x34;
}
// match: ?vf_000@type_3DFF5C@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x001978C0
// sp-match: ?vf_000@type_3DFF5C@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00125560
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_3DFF5C::vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4)
{
    RwInt32 var_18;
    RwUInt32 var_14;
    type_3DF8D8_ref ebp_10;
    RwInt32 l4;

    var_14 = arg_4->unk_08 - 0x1C;
    l4 = var_14 / 0xC;
    for (var_18 = 0; var_18 < l4; var_18++)
    {
        RwStreamRead(arg_0, &ebp_10, 0xC);
        sub_198900((type_3DF8D8_04 *)&ebp_10.unk_04, 0x35, 0, 0, 0, 0);
    }
    return 1;
}
// match: ??0type_3DFF68@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00197950
// sp-match: ??0type_3DFF68@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x001255D0
type_3DFF68::type_3DFF68(const type_3DF8D8_04 &arg_0)
    : type_3DF8D8_base(arg_0)
{
}
// match: ?vf_008@type_3DFF68@@UAEHXZ @ 0x00197980
// sp-match: ?vf_008@type_3DFF68@@UAEHXZ @ 0x001255F0
RwInt32 type_3DFF68::vf_008()
{
    return 0x35;
}
// match: ?vf_000@type_3DFF68@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00197990
// sp-match: ?vf_000@type_3DFF68@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00125600
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_3DFF68::vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4)
{
    RwInt32 var_18;
    RwUInt32 var_14;
    type_3DF8D8_ref ebp_10;
    RwInt32 l4;

    var_14 = arg_4->unk_08 - 0x1C;
    l4 = var_14 / 0xC;
    for (var_18 = 0; var_18 < l4; var_18++)
    {
        RwStreamRead(arg_0, &ebp_10, 0xC);
        sub_198900((type_3DF8D8_04 *)&ebp_10.unk_04, 0x36, 0, 0, 0, 0);
    }
    return 1;
}
// match: ??0type_3DFF74@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00197A20
// sp-match: ??0type_3DFF74@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00125670
type_3DFF74::type_3DFF74(const type_3DF8D8_04 &arg_0)
    : type_3DF8D8_base(arg_0)
{
    unk_20 = 0;
    unk_10 = -1;
    unk_14 = -1;
    unk_18 = -1;
    unk_1C = -1;
}
// match: ?vf_008@type_3DFF74@@UAEHXZ @ 0x00197A80
// sp-match: ?vf_008@type_3DFF74@@UAEHXZ @ 0x001256A0
RwInt32 type_3DFF74::vf_008()
{
    return 0x36;
}
// match: ?vf_000@type_3DFF74@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00197A90
// sp-match: ?vf_000@type_3DFF74@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00126F00
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_3DFF74::vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4)
{
    type_3DF9B8 *var_40;
    type_3DF9B8 *stk_3C;
    type_3DF9B8 *ebp_38;
    RwInt32 var_34;
    type_3DF8D8_ref local_30[4];

    RwStreamRead(arg_0, local_30, arg_4->unk_08 - 0x1C);
    for (var_34 = 0; var_34 < 4; var_34++)
    {
        switch (get_ref_kind(local_30[var_34].unk_00, 0x1F))
        {
        case 1:
            ebp_38 = (type_3DF9B8 *)sub_198900((type_3DF8D8_04 *)&local_30[var_34].unk_04, 9, 0, 0, 0, 0);
            ebp_38->unk_1C = 1;
            ebp_38->sub_1904B0((void (*)(RwInt32, RwInt32, RwInt32))sub_197C80, (RwInt32)this, (RwInt32)&unk_10);
            break;
        case 2:
            stk_3C = (type_3DF9B8 *)sub_198900((type_3DF8D8_04 *)&local_30[var_34].unk_04, 9, 0, 0, 0, 0);
            stk_3C->unk_1C = 1;
            stk_3C->sub_1904B0((void (*)(RwInt32, RwInt32, RwInt32))sub_197C80, (RwInt32)this, (RwInt32)&unk_14);
            break;
        case 3:
            var_40 = (type_3DF9B8 *)sub_198900((type_3DF8D8_04 *)&local_30[var_34].unk_04, 9, 0, 0, 0, 0);
            var_40->unk_1C = 1;
            var_40->sub_1904B0((void (*)(RwInt32, RwInt32, RwInt32))sub_197C80, (RwInt32)this, (RwInt32)&unk_18);
            break;
        case 4:
            sub_198900((type_3DF8D8_04 *)&local_30[var_34].unk_04, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_197C80,
                       (RwInt32)this, (RwInt32)&unk_1C, 0);
            break;
        }
    }
    return 1;
}
// match: ?sub_197C80@@YAHPAUtype_3DF8E4@@PAUtype_3DFF74@@PAH@Z @ 0x00197C80
// sp-match: ?sub_197C80@@YAHPAUtype_3DF8E4@@PAUtype_3DFF74@@PAH@Z @ 0x001256B0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Each variable's callback: its value into the field arg_8 (the fourth's
// truncated from a real), then the entry into the table.
RwInt32 sub_197C80(type_3DF8E4 *arg_0, type_3DFF74 *arg_4, RwInt32 *arg_8)
{
    RwInt32 var_18;
    type_4E5E40 *var_14;
    type_4E5E40_08 *lv_10;
    RwReal var_C;
    type_3DFF74 *bp_8;
    RwInt32 *bp_4;

    bp_4 = arg_8;
    bp_8 = arg_4;
    if (bp_4 == &bp_8->unk_1C)
    {
        var_C = *(RwReal *)&arg_0->unk_10;
        bp_8->unk_1C = (RwInt32)var_C;
    }
    else
    {
        var_18 = arg_0->unk_10;
        *bp_4 = var_18;
    }
    bp_8->unk_20++;
    var_14 = &dword_4E5E40;
    lv_10 = var_14->unk_08;
    if (bp_8->unk_10 != -1)
    {
        lv_10[bp_8->unk_10].unk_00 = bp_8->unk_14;
        lv_10[bp_8->unk_10].unk_04[0] = bp_8->unk_18;
        lv_10[bp_8->unk_10].unk_04[1] = bp_8->unk_1C;
    }
    return 0;
}
// match: ??0type_3DFF80@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00197D40
// sp-match: ??0type_3DFF80@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00125720
type_3DFF80::type_3DFF80(const type_3DF8D8_04 &arg_0)
    : type_3DF8D8_base(arg_0)
{
    unk_10 = 0;
    unk_14 = 0;
}
// match: ?vf_008@type_3DFF80@@UAEHXZ @ 0x00197D80
// sp-match: ?vf_008@type_3DFF80@@UAEHXZ @ 0x00125750
RwInt32 type_3DFF80::vf_008()
{
    return 0x37;
}
// match: ?vf_000@type_3DFF80@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00197D90
// sp-match: ?vf_000@type_3DFF80@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00125760
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_3DFF80::vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4)
{
    type_3DFF8C *var_1C;
    RwInt32 var_18;
    RwUInt32 var_14;
    type_3DF8D8_ref ebp_10;
    RwInt32 l4;

    var_14 = arg_4->unk_08 - 0x1C;
    l4 = var_14 / 0xC;
    *unk_10 = l4;
    *unk_14 = new type_3DFF80_e[l4];
    for (var_18 = 0; var_18 < l4; var_18++)
    {
        RwStreamRead(arg_0, &ebp_10, 0xC);
        var_1C = (type_3DFF8C *)sub_198900((type_3DF8D8_04 *)&ebp_10.unk_04, 0x38, 0, 0, 0, 0);
        var_1C->unk_10 = &(*unk_14)[var_18];
    }
    return 1;
}
// match: ??0type_3DFF8C@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00197ED0
// sp-match: ??0type_3DFF8C@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00125820
type_3DFF8C::type_3DFF8C(const type_3DF8D8_04 &arg_0)
    : type_3DF8D8_base(arg_0)
{
    unk_10 = 0;
}
// match: ?vf_008@type_3DFF8C@@UAEHXZ @ 0x00197F00
// sp-match: ?vf_008@type_3DFF8C@@UAEHXZ @ 0x00125840
RwInt32 type_3DFF8C::vf_008()
{
    return 0x38;
}
// match: ?vf_000@type_3DFF8C@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00197F10
// sp-match: ?vf_000@type_3DFF8C@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00127030
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_3DFF8C::vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4)
{
    type_3DF9B8 *var_24;
    type_3DF9B8 *var_20;
    RwInt32 l1C;
    type_3DF8D8_ref m_18[2];

    RwStreamRead(arg_0, m_18, arg_4->unk_08 - 0x1C);
    for (l1C = 0; l1C < 2; l1C++)
    {
        switch (get_ref_kind(m_18[l1C].unk_00, 0x1F))
        {
        case 1:
            var_20 = (type_3DF9B8 *)sub_198900((type_3DF8D8_04 *)&m_18[l1C].unk_04, 9, 0, 0, 0, 0);
            var_20->unk_1C = 1;
            var_20->sub_1904B0((void (*)(RwInt32, RwInt32, RwInt32))sub_18F8B0, 0, (RwInt32)unk_10);
            break;
        case 2:
            var_24 = (type_3DF9B8 *)sub_198900((type_3DF8D8_04 *)&m_18[l1C].unk_04, 9, 0, 0, 0, 0);
            var_24->unk_1C = 0x39;
            var_24->sub_1904B0((void (*)(RwInt32, RwInt32, RwInt32))sub_198070, (RwInt32)this,
                               (RwInt32)&unk_10->unk_04);
            break;
        }
    }
    return 1;
}
// match: ?sub_198070@@YAHPAUtype_3DF8D8_base@@PAUtype_3DFF8C@@H@Z @ 0x00198070
// sp-match: ?sub_198070@@YAHPAUtype_3DF8D8_base@@PAUtype_3DFF8C@@H@Z @ 0x00125850
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The kind-0x39 object's callback: its key into the entry.
RwInt32 sub_198070(type_3DF8D8_base *arg_0, type_3DFF8C *arg_4, RwInt32 arg_8)
{
    type_3DFF8C *var_8;
    type_3DF8D8_base *l4;

    var_8 = arg_4;
    l4 = arg_0;
    var_8->unk_10->unk_04 = l4->unk_04;
    return 1;
}
// match: ??0type_3DFF98@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x001980A0
// sp-match: ??0type_3DFF98@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00125870
type_3DFF98::type_3DFF98(const type_3DF8D8_04 &arg_0)
    : type_3DF8D8_base(arg_0)
{
    unk_10 = 0;
    unk_14 = 0;
}
// match: ?vf_008@type_3DFF98@@UAEHXZ @ 0x001980E0
// sp-match: ?vf_008@type_3DFF98@@UAEHXZ @ 0x001258A0
RwInt32 type_3DFF98::vf_008()
{
    return 0x39;
}
// match: ?vf_000@type_3DFF98@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x001980F0
// sp-match: ?vf_000@type_3DFF98@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x001258B0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_3DFF98::vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4)
{
    type_3DF9B8 *var_1C;
    RwInt32 var_18;
    RwUInt32 var_14;
    type_3DF8D8_ref ebp_10;
    RwInt32 l4;

    var_14 = arg_4->unk_08 - 0x1C;
    l4 = var_14 / 0xC;
    unk_10 = l4;
    if (unk_10)
        unk_14 = new RwInt32[l4];
    for (var_18 = 0; var_18 < l4; var_18++)
    {
        RwStreamRead(arg_0, &ebp_10, 0xC);
        var_1C = (type_3DF9B8 *)sub_198900((type_3DF8D8_04 *)&ebp_10.unk_04, 9, 0, 0, 0, 0);
        var_1C->unk_1C = 1;
        var_1C->sub_1904B0((void (*)(RwInt32, RwInt32, RwInt32))sub_18F8B0, 0, (RwInt32)&unk_14[var_18]);
    }
    return 1;
}
// match: ?vf_004@type_3DFF98@@UAEXXZ @ 0x001981E0
// sp-match: ?vf_004@type_3DFF98@@UAEXXZ @ 0x00125960
void type_3DFF98::vf_004()
{
    if (unk_14)
        delete[] unk_14;
}
// match: ??0type_3DFFA4@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00198210
// sp-match: ??0type_3DFFA4@@QAE@ABUtype_3DF8D8_04@@@Z @ 0x00125970
type_3DFFA4::type_3DFFA4(const type_3DF8D8_04 &arg_0)
    : type_3DF8D8_base(arg_0)
{
    unk_10 = 0;
}
// match: ?vf_008@type_3DFFA4@@UAEHXZ @ 0x00198240
// sp-match: ?vf_008@type_3DFFA4@@UAEHXZ @ 0x00125990
RwInt32 type_3DFFA4::vf_008()
{
    return 0x3B;
}
// match: ?vf_000@type_3DFFA4@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x00198250
// sp-match: ?vf_000@type_3DFFA4@@UAEHPAURwStream@@PAUtype_3DF8D8_ev@@@Z @ 0x001259A0
RwInt32 type_3DFFA4::vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4)
{
    RwInt32 l4;
    RwUInt32 var_2C;
    RwInt32 var_30;

    unk_10 = sub_1986B0();
    type_3DF8D8_ref var_28[3];

    var_2C = arg_4->unk_08 - 0x1C;
    l4 = var_2C / 0xC;
    RwStreamRead(arg_0, var_28, arg_4->unk_08 - 0x1C);
    for (var_30 = 0; var_30 < l4; var_30++)
    {
        switch (get_ref_kind(var_28[var_30].unk_00, 0x1F))
        {
        case 2:
            sub_198900((type_3DF8D8_04 *)&var_28[var_30].unk_04, 2, (void (*)(RwInt32, RwInt32, RwInt32))sub_195B70,
                       (RwInt32)this, (RwInt32)unk_10, 0);
            break;
        }
    }
    return 1;
}
// match: ?vf_004@type_3DFFA4@@UAEXXZ @ 0x00198360
// sp-match: ?vf_004@type_3DFFA4@@UAEXXZ @ 0x00125A40
void type_3DFFA4::vf_004()
{
    if (unk_10)
    {
        sub_1986D0(unk_10);
        unk_10 = 0;
    }
}
