// The gimp (type_3DDB98), the entity a GimpTrigger spawns.

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "game/functions.h"
#include "game/data.h"
#include "types/type_3D3548.h"
#include "types/type_3DDB98.h"
#include "types/type_3D32F8.h"
#include "types/GimpTrigger.h"
#include "types/type_44350.h"
#include "types/SoldierTrigger.h"
#include "types/soundbank.h"
#include "game/cheats.h"
#include "types/vec4.h"
#include "types/SplinePath.h"
#include "types/type_3DAFC8.h"
#include "types/type_3DF8D8.h"
#include "types/type_3D2E7C.h"
#include "types/alfaobject.h"
#include "types/animbank.h"
#include "types/animkey.h"
#include "types/type_4B85F8.h"
#include "types/type_3D51C0.h"
#include "types/type_10F710.h"
#include "rw/rphanim.h"
#include "rw/rprandom.h"
#include "game/clumpdata.h"
#include "game/frand.h"
#include "game/vecutil.h"
#include "rws/skinhelper.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "rw/badevice.h"
#include "types/type_3D5658.h"
#include "types/type_3DA6C0.h"
#include "types/type_92430.h"
#include "game/decals.h"
#include "types/type_F2FF0.h"
#include "types/type_3DC048.h"
#include "types/type_3DBC78.h"
#include "rw/bavector.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003DDB90
extern const RwReal flt_3DDB90 = 16.666666f;
// 0x0042A048
#ifdef CODFH_SP
// Internal to this file in single player: SP 0x113F80 loads it ahead of
// stores through `this`, which /O2 does only for a static whose address is
// never taken.
static RwReal dword_42A048 = -2.0f;
#else
RwReal dword_42A048 = -2.0f;
#endif
// 0x0042A050
RwInt32 dword_42A050[26] = { -1, 0, 1, 2, 3, 3, 3, 6, 6, 6, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0 };
// 0x0042A0B8
type_42A0B8 dword_42A0B8[22] = {
    { 0xEEE7BCA3, 0x6473325F, 0.94f },
    { 0x114A6E88, 0x2F27012, 1.05f },
    { 0x71763C32, 0x870F1FC0, 1.0f },
    { 0x14B547A8, 0x6637F33E, 1.0f },
    { 0xCB0E8992, 0x96DA779C, 1.0f },
    { 0x14B547A8, 0x42BD052B, 1.0f },
    { 0xB343BD76, 0x7448AB61, 0.96f },
    { 0x114A6E88, 0x85DAD028, 1.05f },
    { 0x71763C32, 0xAA914F12, 1.0f },
    { 0x114A6E88, 0x9084CD87, 1.05f },
    { 0x14B547A8, 0xC6203F5D, 1.0f },
    { 0xB343BD76, 0xD734F1BB, 0.96f },
    { 0x2BADF11, 0xE7663874, 0.94f },
    { 0x2BADF11, 0xBCD9CFF2, 0.94f },
    { 0x5217055F, 0xEE38E719, 1.07f },
    { 0x5217055F, 0xC8FDBF72, 1.07f },
    { 0x5F2BD056, 0x1852B832, 1.04f },
    { 0x57B3E379, 0x8D5BD92A, 1.09f },
    { 0x57B3E379, 0xFF19D413, 1.09f },
    { 0xBEBBF00E, 0xBCDC72C1, 1.03f },
    { 0x57B3E379, 0x2B5492E6, 1.09f },
    { 0x5F2BD056, 0x28D9621E, 1.04f },
};
// 0x0042A1C0
RwUInt32 dword_42A1C0 = 33;
// 0x0042A1C8
type_42A1C8 dword_42A1C8[35] = {
    { 0x7793F2E9, 0x4A3B1814, 1213476913 },
    { 0x44F3DCB4, 0x702D682F, 1213476914 },
    { 0xE3CBC2ED, 0x3B335D08, 1213476915 },
    { 0x4DCAE0C0, 0x565CCE6D, 1213476916 },
    { 0xFFAD0FDD, 0x937810C1, 1213476917 },
    { 0x6836E260, 0x3D73AA86, 1213476918 },
    { 0x7F825E81, 0x9CDDA57A, 1213476919 },
    { 0x92A04B5B, 0xC92CBEC2, 1213476920 },
    { 0x2487396B, 0x8862A0DE, 1213476921 },
    { 0x5C9D2A04, 0x6E8F47FB, 1213477168 },
    { 0xA7998A34, 0x5E55B6F9, 1213477169 },
    { 0xC54340A7, 0x44076D04, 1213477170 },
    { 0xCF81A073, 0x739645B3, 1213477171 },
    { 0xE6F6833D, 0x9900843E, 1213477172 },
    { 0xEDD63EFA, 0xEFEEDF20, 1213477173 },
    { 0xE6F6833D, 0xAD233280, 1213477174 },
    { 0x4EFD28B1, 0xA9C6DAC8, 1213477175 },
    { 0xFBDF7C83, 0xDD6326FA, 1213477176 },
    { 0xFBDF7C83, 0xDD6326F9, 1213477177 },
    { 0xFBDF7C83, 0xDD6326F8, 1213477424 },
    { 0xB1245974, 0x295E3E9F, 1213477425 },
    { 0x30843315, 0xE3076A36, 1213477426 },
    { 0x997036B5, 0x6A374A47, 1213477427 },
    { 0x4F7F58BE, 0x6220D1D, 1213477428 },
    { 0x96003442, 0x1EC74765, 1213477429 },
    { 0x2FFD1878, 0x581AE84B, 1213477430 },
    { 0x4F7F58DE, 0xDF86C125, 1213477431 },
    { 0x3743F3CA, 0x2BB0B65E, 1213477432 },
    { 0x3743F3C9, 0x2BB0B65E, 1213477433 },
    { 0x3843F5BF, 0x2BB0B65E, 1213477680 },
    { 0x3843F5BC, 0x2BB0B65E, 1213477681 },
    { 0x3843F5BD, 0x2BB0B65E, 1213477682 },
    { 0x38CB89C9, 0xA7B89F35, 1213477683 },
    { 0x89405B39, 0x8CE5E77, 1213477684 },
    { 0xEB33664D, 0xFF17C6A2, 1213477685 },
};
// 0x0042A36C
RwUInt32 dword_42A36C = 35;
// 0x0042A370
type_42A370 byte_42A370[9] = {
    { "FA_QO1A1M_DeathA", 0.25f },
    { "FA_QO1A1N_DeathB", 0.25f },
    { "FA_QO1A1O_DeathC", 0.25f },
    { "FA_QO1A1P_DeathD", 0.25f },
    { "FA_QO1A1X_HitA", 0.25f },
    { "FA_QO1A1Y_HitB", 0.25f },
    { "FA_QO1A1Z_HitC", 0.25f },
    { "FA_QO1A2A_HitD", 0.15f },
    { "FA_QO1A2B_HitE", 0.1f },
};
// 0x004E6F24
RwInt32 dword_4E6F24;
// End of its data definitions.


// The soldier's flight and step tuning (unit_1340D0 declares them too).
extern RwReal flt_429C88;
extern RwReal flt_429C98;
extern RwReal flt_429C9C;
extern RwReal flt_429CA0;
extern RwReal flt_429CA4;
extern RwReal flt_429CAC;
extern RwReal flt_429CB0;
extern RwReal flt_429CB4;
extern RwReal flt_429CB8;
// Set while no gimp is drawn (vf_054).
extern RwInt32 dword_4E6F24;

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3DDB90@@3MB @ 0x003DDB90
// match: ??_7type_3DDB98@@6B@ @ 0x003DDB98
// match: ??_C@_0BF@BNFNEKCB@GimpEntity?3?3HeadMesh?$AA@ @ 0x003DDDDC
// match: ??_C@_0BF@PEMDOCJF@GimpEntity?3?3BodyMesh?$AA@ @ 0x003DDDF4
// match: ??_C@_0BJ@GLAKCMCA@GimpEntity?3?3CharacterDef?$AA@ @ 0x003DDE0C
// match: __real@4a189680 @ 0x003DDE28
// match: ??_C@_0CP@BANGGDBK@WARNING?3?5No?5Death?5face?5anim?5load@ @ 0x003DDE2C
// match: __ehhandler$?sub_176E50@@YAPAUtype_3D3548@@PAVGimpTrigger@@@Z>1>8 @ 0x0041E3D0
// match: __ehhandler$?sub_176E50@@YAPAUtype_3D3548@@PAVGimpTrigger@@@Z>1 @ 0x0041E3D8
// match: __ehhandler$??0type_3DDB98@@QAE@PAVGimpTrigger@@@Z>1>8 @ 0x0041E3F4
// match: __ehhandler$??0type_3DDB98@@QAE@PAVGimpTrigger@@@Z>1 @ 0x0041E41C
// match: __ehhandler$??1type_3DDB98@@UAE@XZ>1>8 @ 0x0041E438
// match: __ehhandler$??1type_3DDB98@@UAE@XZ>1 @ 0x0041E470
// match: __ehhandler$?sub_179C10@@YAHPAUtype_F2FF0@@@Z>1>8 @ 0x0041E48C
// match: __ehhandler$?sub_179C10@@YAHPAUtype_F2FF0@@@Z>1 @ 0x0041E494
// match: ?dword_42A048@@3MA @ 0x0042A048
// match: ?dword_42A050@@3PAHA @ 0x0042A050
// match: ?dword_42A0B8@@3PAUtype_42A0B8@@A @ 0x0042A0B8
// match: ?dword_42A1C0@@3IA @ 0x0042A1C0
// match: ?dword_42A1C8@@3PAUtype_42A1C8@@A @ 0x0042A1C8
// match: ?dword_42A36C@@3IA @ 0x0042A36C
// match: ?byte_42A370@@3PAUtype_42A370@@A @ 0x0042A370

// match: ?sub_176E50@@YAPAUtype_3D3548@@PAVGimpTrigger@@@Z @ 0x00176E50
// match: __ehhandler$?sub_176E50@@YAPAUtype_3D3548@@PAVGimpTrigger@@@Z-0x11 @ 0x00302090
// match: __ehhandler$?sub_176E50@@YAPAUtype_3D3548@@PAVGimpTrigger@@@Z @ 0x003020A1
// sp-match: ?sub_176E50@@YAPAUtype_3D3548@@PAVGimpTrigger@@@Z @ 0x001153A0

// Builds the gimp for the trigger arg_0, or warns that there is no entity
// memory for it.
type_3D3548 *sub_176E50(GimpTrigger *arg_0)
{
    type_3DDB98 *var_10;

    var_10 = (type_3DDB98 *)sub_D56D0(0x790, arg_0->unk_24_18, arg_0->vf_008());
    if (var_10 != 0) {
        var_10 = new (var_10) type_3DDB98(arg_0);
        if (var_10->unk_28 & 0x400000) { // not an address: entity flag
            sub_D5A60(var_10, 0);
            var_10 = 0;
        }
    }
#ifndef CODFH_SP
    else
        sub_19A750("WARNING: A spawn could not be created due to lack of entity memory. Trigger "
                   "location(%6.2f,%6.2f,%6.2f)",
                   arg_0->unk_90, arg_0->unk_94, arg_0->unk_98);
#endif
    return var_10;
}

// match: ??0type_3DDB98@@QAE@PAVGimpTrigger@@@Z @ 0x00176F60
// match: __ehhandler$??0type_3DDB98@@QAE@PAVGimpTrigger@@@Z-0x40 @ 0x003020B0
// match: __ehhandler$??0type_3DDB98@@QAE@PAVGimpTrigger@@@Z @ 0x003020F0
// sp-match: ??0type_3DDB98@@QAE@PAVGimpTrigger@@@Z @ 0x00115070
// (Defined in the class.)

// What the gimp's set-up matches its definition and head against (as the
// soldier's, unit_1340D0); each node's parent and bind pose offset.
extern type_42A0B8 dword_42A0B8[];
extern RwUInt32 dword_42A1C0;
extern type_42A1C8 dword_42A1C8[];
extern RwUInt32 dword_42A36C;
extern RwInt32 dword_42A050[];
extern type_7CBD0_t flt_428A50[];
// The gimp's unk_108 at first (-2).
#ifndef CODFH_SP
extern RwReal dword_42A048;
#endif

// match: ?vf_160@type_3DDB98@@UAEHXZ @ 0x00177040
// sp-match: ?vf_160@type_3DDB98@@UAEHXZ @ 0x000EC080
RwInt32 type_3DDB98::vf_160()
{
    return unk_3E0.sub_15EF80();
}

// match: ?vf_094@type_3DDB98@@UAEXI@Z @ 0x00177060
// sp-match: ?vf_094@type_3DDB98@@UAEXI@Z @ 0x00115100
void type_3DDB98::vf_094(RwUInt32 arg_0)
{
    unk_6A4 = arg_0;
}

// match: ?Collision_DispatchAtomicIntersectionsBySelectorFlag@type_3DDB98@@UAEXPAURpAtomic@@PAURpIntersection@@PAUtype_93700@@@Z @ 0x00177080
// sp-match: ?Collision_DispatchAtomicIntersectionsBySelectorFlag@type_3DDB98@@UAEXPAURpAtomic@@PAURpIntersection@@PAUtype_93700@@@Z @ 0x00115110
void type_3DDB98::Collision_DispatchAtomicIntersectionsBySelectorFlag(RpAtomic *arg_0, RpIntersection *arg_4,
                                                                    type_93700 *arg_8)
{
    if (arg_8)
        arg_8->unk_5C = 1;
}

// match: ?vf_0F0@type_3DDB98@@UAEPACXZ @ 0x001770A0
// sp-match: ?vf_0F0@type_3DDB98@@UAEPACXZ @ 0x00115130
RwInt8 *type_3DDB98::vf_0F0()
{
    return unk_748;
}

// match: ?vf_1AC@type_3DDB98@@UAEXH@Z @ 0x001770C0
// sp-match: ?vf_1AC@type_3DDB98@@UAEXH@Z @ 0x00115140
void type_3DDB98::vf_1AC(RwInt32 arg_0)
{
    ((GimpTrigger *)get_unk_34C())->unk_118 = arg_0;
}

// match: ?vf_09C@type_3DDB98@@UAEHXZ @ 0x001770F0
// sp-match: ?vf_09C@type_3DDB98@@UAEHXZ @ 0x00115160
RwInt32 type_3DDB98::vf_09C()
{
    return unk_6A0;
}

// match: ?vf_0A0@type_3DDB98@@UAEXI@Z @ 0x00177110
// sp-match: ?vf_0A0@type_3DDB98@@UAEXI@Z @ 0x00115170
void type_3DDB98::vf_0A0(RwUInt32 arg_0)
{
    unk_6A0 = arg_0;
}

// match: ?vf_088@type_3DDB98@@UAEXH@Z @ 0x00177130
// sp-match: ?vf_088@type_3DDB98@@UAEXH@Z @ 0x00115180
void type_3DDB98::vf_088(RwInt32 arg_0)
{
    unk_6B0 = arg_0;
}

// match: ?vf_0E0@type_3DDB98@@UAEPAEXZ @ 0x00177150
// sp-match: ?vf_0E0@type_3DDB98@@UAEPAEXZ @ 0x00115190
RwUInt8 *type_3DDB98::vf_0E0()
{
    return (RwUInt8 *)unk_6A8;
}

// match: ?vf_12C@type_3DDB98@@UAEXH@Z @ 0x00177170
// sp-match: ?vf_12C@type_3DDB98@@UAEXH@Z @ 0x001151B0
void type_3DDB98::vf_12C(RwInt32 arg_0)
{
    unk_760 = (unk_760 & ~1) | (arg_0 != 0);
}

// match: ?vf_234@type_3DDB98@@UAEXH@Z @ 0x001771A0
// sp-match: ?vf_234@type_3DDB98@@UAEXH@Z @ 0x001151D0
void type_3DDB98::vf_234(RwInt32 arg_0)
{
    unk_760 = (unk_760 & ~6) | (arg_0 ? 2 : 0);
}

// match: ?vf_238@type_3DDB98@@UAEXH@Z @ 0x001771D0
// sp-match: ?vf_238@type_3DDB98@@UAEXH@Z @ 0x001151F0
void type_3DDB98::vf_238(RwInt32 arg_0)
{
    unk_760 = (unk_760 & ~6) | (arg_0 ? 4 : 0);
}

// match: ?vf_0F4@type_3DDB98@@UAEPAUSplinePath@@XZ @ 0x00177200
// sp-match: ?vf_0F4@type_3DDB98@@UAEPAUSplinePath@@XZ @ 0x00115210
SplinePath *type_3DDB98::vf_0F4()
{
    return unk_734;
}

// match: ?vf_174@type_3DDB98@@UAEHXZ @ 0x00177220
// sp-match: ?vf_174@type_3DDB98@@UAEHXZ @ 0x00115220
RwInt32 type_3DDB98::vf_174()
{
    return unk_740;
}

// match: ?vf_178@type_3DDB98@@UAEXH@Z @ 0x00177240
// sp-match: ?vf_178@type_3DDB98@@UAEXH@Z @ 0x00115230
void type_3DDB98::vf_178(RwInt32 arg_0)
{
    unk_740 = arg_0;
}

// match: ?vf_180@type_3DDB98@@UAEXH@Z @ 0x00177260
// sp-match: ?vf_180@type_3DDB98@@UAEXH@Z @ 0x00115240
void type_3DDB98::vf_180(RwInt32 arg_0)
{
    unk_740 += arg_0;
    if (unk_740 > unk_744)
        unk_740 = unk_744;
}

// match: ?vf_17C@type_3DDB98@@UAEMXZ @ 0x001772B0
// sp-match: ?vf_17C@type_3DDB98@@UAEMXZ @ 0x00115270
RwReal type_3DDB98::vf_17C()
{
    return (RwReal)unk_740 / unk_744;
}

// match: ?vf_0AC@type_3DDB98@@UAEHXZ @ 0x001772D0
// sp-match: ?vf_0AC@type_3DDB98@@UAEHXZ @ 0x00115280
RwInt32 type_3DDB98::vf_0AC()
{
    return unk_754;
}

// match: ?vf_0B0@type_3DDB98@@UAEXHH@Z @ 0x001772F0
// sp-match: ?vf_0B0@type_3DDB98@@UAEXHH@Z @ 0x00115290
void type_3DDB98::vf_0B0(RwInt32 arg_0, RwInt32 arg_4)
{
    unk_754 = arg_0;
    vf_0B4();
}

// match: ?vf_0B4@type_3DDB98@@UAEXXZ @ 0x00177320
// sp-match: ?vf_0B4@type_3DDB98@@UAEXXZ @ 0x001152B0
void type_3DDB98::vf_0B4()
{
    unk_758 = unk_6B4[3];
}

// match: ?vf_1F0@type_3DDB98@@UAEMXZ @ 0x00177340
// sp-match: ?vf_1F0@type_3DDB98@@UAEMXZ @ 0x000EC0B0

RwReal type_3DDB98::vf_1F0()
{
#ifdef CODFH_SP
    return unk_3E0.sub_15EDE0() * get_4F28C0();
#else
    return unk_3E0.sub_15EDE0() * 1.0f;
#endif
}

// match: ?vf_23C@type_3DDB98@@UAEHXZ @ 0x00177360
// sp-match: ?vf_23C@type_3DDB98@@UAEHXZ @ 0x001152C0
RwInt32 type_3DDB98::vf_23C()
{
    return unk_75C;
}

// match: ?vf_240@type_3DDB98@@UAEXH@Z @ 0x00177380
// sp-match: ?vf_240@type_3DDB98@@UAEXH@Z @ 0x001152D0
void type_3DDB98::vf_240(RwInt32 arg_0)
{
    unk_75C = arg_0;
}

// match: ?sub_1774C0@type_3DDB98@@QAEHPAVGimpTrigger@@@Z @ 0x001774C0
// sp-match: ?sub_1774C0@type_3DDB98@@QAEHPAVGimpTrigger@@@Z @ 0x00113F80
// Its set-up from its trigger arg_0, as the soldier's (type_3DAFC8's
// sub_135430): the base's set-up, its health, flags and fields; its
// definition's body and head (without all three it is left inert, flagged
// 0x400000, and 0 returned); its script object and scripts, its
// performance player, render parts, its two animations and their scales,
// its hat tag, its second animation's rest translations from the skin, its
// idle face animation, its weapon, its side by the definition's kind, its
// deletion delay and its spline path. Returns 1.
RwInt32 type_3DDB98::sub_1774C0(GimpTrigger *arg_0)
{
    GimpTrigger *var_C;
    type_3DFEEC *var_10;
    type_1917A0 *var_28;
    type_1908A0 *var_2C;
    type_1908A0 *var_30;
    type_3DF8D8 *var_34;
    type_3DF8D8 *var_38;
    RwUInt32 var_3C;
    type_3D2E7C *var_40;
    type_3DF8D8 *var_48;
    type_3D2CD0 *var_50;
    RwUInt32 var_58;
    RwUInt32 var_78;
    type_7C8D0 *var_7C;
    RpHAnimHierarchy *var_84;
    RwUInt32 var_88;
    type_7C8D0 *var_8C;
    RwInt32 var_98;
    type_3DF8D8_04 *var_9C;
    bool var_CD;
    type_3DF8D8_04 *var_D4;
    type_3DF8D8 *var_D8;
    type_EC1F0 *var_E0;
    RpSkin *var_E8;
    const RwMatrix *var_EC;
    RwInt32 var_F0;
    type_140490 var_110;
    RwInt32 var_114;
    RwInt32 var_118;
    RwChar var_160[0x40];
    RwUInt32 var_164;
    RwInt32 var_168;
    RwInt32 var_16C;
    RwInt32 var_170;
    RwInt32 var_180;
    type_3DF8D8 *var_184;
    type_3DFEEC *var_188;

    var_C = arg_0;
    sub_CCCD0((type_712B0 *)arg_0);
    unk_784 = 1;
    unk_88 &= ~0x2000;
    unk_744 = (RwInt32)var_C->unk_120_r;
    unk_740 = unk_744;
    RwMatrixSetIdentityMacro(&unk_6F0);
    if (var_C->unk_D8.unk_00)
    {
        var_10 = (type_3DFEEC *)sub_198800(&var_C->unk_D8);
        ((type_D48D0 *)&var_10->unk_24_id)->sub_D48D0(this);
        var_10->unk_10 = 0x802;
    }
    unk_88_10 = arg_0->unk_24_20;
    unk_28 = 0x14;
    unk_2C = 0x200000; // not an address: entity kind bits
    unk_30 = 0x241EF7; // not an address: collision flags
    if (var_C->unk_118)
        unk_28 |= 0x80000; // not an address: a flag
    unk_760 = 0;
    unk_73C = 0;
    unk_764 = var_C->unk_144;
    unk_108 = dword_42A048;
    set_xyz(&unk_10C, -1.0f, -1.0f, -1.0f);
    set_xyz(&unk_134, -1.0f, -1.0f, -1.0f);
    zero_v3d(&unk_118);
    set_xyz(&unk_124, 1000.0f, 1000.0f, 1000.0f);
    unk_130 = 0;
    vf_240(var_C->unk_11C);
    unk_58 = 1;
    unk_3D4 = 0;
    unk_3D8.sub_D48D0(0);
    unk_3DC = 0;
    unk_734 = 0;
    unk_6E4 = 0;
    unk_738 = 1.0f;
    unk_730 = 1.0f;
    unk_760 = (unk_760 & ~1) | (var_C->unk_138 == 0);
    zero_v3d(&unk_778);
    unk_28 |= 0x100000; // not an address: a flag
    unk_695 = 0;
    var_28 = 0;
    var_2C = 0;
    var_30 = 0;
    var_34 = sub_198800(&var_C->unk_C0);
    if (var_34 && var_34->vf_008() == 4)
    {
        var_28 = (type_1917A0 *)var_34;
        var_2C = var_28->sub_1917A0();
        var_30 = var_28->sub_1917F0();
    }
    if (!var_28 || !var_2C || !var_30)
    {
        if (!var_28)
            sub_D3FB0("GimpEntity::CharacterDef", arg_0, &var_C->unk_C0);
        if (!var_2C)
            sub_D3FB0("GimpEntity::BodyMesh", arg_0, &var_C->unk_C0);
        if (!var_30)
            sub_D3FB0("GimpEntity::HeadMesh", arg_0, &var_C->unk_C0);
        unk_698 = 0;
        unk_690 = 1.0f;
        unk_68C = 1.0f;
        unk_6A0 = 0;
        unk_6A4 = 0;
        unk_28 |= 0x400000; // not an address: a flag
        return 0;
    }
    var_38 = sub_198800(&var_C->unk_C8);
    var_3C = sub_71870();
    unk_6A0 = var_3C;
    var_40 = vf_098();
    var_40->sub_70DF0(this, 2);
    var_40->sub_70E10(var_38->get_unk_18(), 1);
    var_48 = sub_198800(&var_C->unk_D0);
    if (var_48)
        var_40->sub_70F40(var_48->get_unk_18(), 1);
    var_50 = (type_3D2CD0 *)sub_71770(1);
    unk_6A4_h = var_50->get_unk_04_h();
    var_50->sub_6CDA0(this, 1);
    memcpy(unk_6A8, var_C->unk_100, 6);
    unk_6B0 = 0;
    memset(unk_6B4, 0, 0xC);
    memset(unk_6C0, 0, 0xC);
    for (var_58 = 0; var_58 < 6; var_58++)
    {
        unk_6B4[var_58 + 6] = 1;
        unk_6C0[var_58 + 6] = 1;
    }
    vf_0B0(0, 0);
    sub_83850(9, &unk_1C0, &unk_3B0);
    vf_224(var_2C, 0, 0);
    sub_179AB0(var_28->sub_18F830((type_1917A0_10 *)&var_28->unk_10));
    sub_179B70(var_28->sub_18F830(&var_28->unk_28));
    sub_16D9A0(get_unk_264());
    sub_16E080(get_unk_264(), var_28->get_unk_34());
    sub_16E080(unk_6CC.get_unk_08(), var_28->sub_1917F0()->get_unk_54());
    zero_v3d(&unk_3C_v);
    unk_48 = 90.0f;
    unk_4C = 60.0f;
    unk_50_r = 33.0f;
    unk_40 = 90.0f;
    var_78 = sub_78830(0);
    unk_280 = var_78;
    var_7C = (type_7C8D0 *)sub_78AC0(unk_280);
    unk_284 = var_7C;
    var_84 = sub_16D970(get_unk_264());
    var_7C->sub_79470(var_84);
    var_7C->unk_1C = (RwInt32)this;
    var_88 = sub_78830(0);
    unk_288 = var_88;
    var_8C = (type_7C8D0 *)sub_78AC0(unk_288);
    unk_28C = var_8C;
    var_84 = sub_16D970(unk_6CC.get_unk_08());
    var_8C->sub_79470(var_84);
    var_8C->unk_1C = (RwInt32)this;
    var_8C->unk_1C = (RwInt32)this;
    var_8C->set_unk_12(var_8C->unk_12 | 2);
    var_98 = -1;
    for (var_58 = 0; var_58 < dword_42A1C0; var_58++)
    {
        var_9C = &var_34->unk_04;
        if (var_9C->unk_00 == dword_42A0B8[var_58].unk_00.unk_00
            && var_9C->unk_04 == dword_42A0B8[var_58].unk_00.unk_04)
        {
            var_98 = var_58;
            break;
        }
    }
    if (var_98 >= 0)
    {
        unk_698 = 1;
        unk_690 = dword_42A0B8[var_98].unk_08;
        unk_68C = 1.0f;
    }
    else
    {
        unk_698 = 0;
        unk_690 = frand_range(0.95f, 1.05f);
        unk_68C = 1.0f;
    }
    if (((type_4B8888 *)dword_4B8888)->unk_00_6)
        unk_690 = frand_range(0.3f, 1.2f);
    unk_284->set_unk_28(unk_690);
    unk_28C->set_unk_28(unk_68C);
    var_CD = false;
    for (var_58 = 0; var_58 < dword_42A36C; var_58++)
    {
        var_D4 = &var_28->unk_28.unk_04;
        var_D8 = sub_198800(var_D4);
        if (var_D8->unk_14 == dword_42A1C8[var_58].unk_00.unk_00
            && var_D8->unk_18 == dword_42A1C8[var_58].unk_00.unk_04)
        {
            var_CD = true;
            break;
        }
    }
    if (var_CD)
    {
        var_E0 = sub_EC1F0(unk_6CC.get_unk_08(), dword_42A1C8[var_58].unk_08);
        if (var_E0)
            unk_69C = dword_42A1C8[var_58].unk_08;
        else
            unk_69C = 0x48415400; // not an address: the tag "HAT"
    }
    else
    {
        unk_69C = 0x48415400; // not an address: the tag "HAT"
    }
    var_E8 = RWS::SkinHelper::FindFirstSkin(*unk_6CC.get_unk_08());
    if (var_E8)
    {
        var_EC = RpSkinGetSkinToBoneMatrices(var_E8);
        for (var_F0 = 0; var_F0 < unk_28C->get_unk_18()->numNodes; var_F0++)
        {
            unk_4E0[var_F0] = *(type_7CBD0_t *)&var_EC[var_F0].pos;
            var_110.x = 0.0f;
            var_110.y = 0.0f;
            var_110.z = 0.0f;
            var_110.w = 0.0f;
            var_114 = dword_42A050[var_F0];
            while (var_114 != -1)
            {
                var_110.x += unk_4E0[var_114].unk_00.x;
                var_110.y += unk_4E0[var_114].unk_00.y;
                var_110.z += unk_4E0[var_114].unk_00.z;
                var_114 = dword_42A050[var_114];
            }
#ifdef CODFH_SP // shape: plain assignments schedule the loop's stores as SP 0x113F80 does
            unk_4E0[var_F0].unk_00.x = unk_4E0[var_F0].unk_00.x - (var_110.x + flt_428A50[var_F0].unk_00.x);
            unk_4E0[var_F0].unk_00.y = unk_4E0[var_F0].unk_00.y - (var_110.y + flt_428A50[var_F0].unk_00.y);
            unk_4E0[var_F0].unk_00.z = unk_4E0[var_F0].unk_00.z - (var_110.z + flt_428A50[var_F0].unk_00.z);
#else
            unk_4E0[var_F0].unk_00.x -= var_110.x + flt_428A50[var_F0].unk_00.x;
            unk_4E0[var_F0].unk_00.y -= var_110.y + flt_428A50[var_F0].unk_00.y;
            unk_4E0[var_F0].unk_00.z -= var_110.z + flt_428A50[var_F0].unk_00.z;
#endif
        }
    }
    else
    {
        var_EC = RpSkinGetSkinToBoneMatrices(var_E8);
        for (var_118 = 0; var_118 < unk_28C->get_unk_18()->numNodes; var_118++)
        {
            unk_4E0[var_118].unk_00.x = 0.0f;
            unk_4E0[var_118].unk_00.y = 0.0f;
            unk_4E0[var_118].unk_00.z = 0.0f;
#ifndef CODFH_SP
            sub_19A750("%2d %4d { %9.6f, %9.6f, %9.6f }, \n", var_118,
                       unk_28C->get_unk_18()->pNodeInfo[var_118].nodeID, var_EC[var_118].pos.x,
                       var_EC[var_118].pos.y, var_EC[var_118].pos.z);
#endif
        }
    }
    strncpy(var_160, "FA_QO1A2K_IdleMask", 0x1F);
    var_164 = sub_16C800(var_160, 0x811C9DC5); // not an address: the FNV basis
    unk_694 = 0;
    if (sub_77B70(var_164, (void **)(&var_16C), (void **)(&var_168)))
    {
        var_8C->sub_794C0(0.0f);
        var_8C->sub_796A0((RtAnimAnimation *)var_16C, var_164, 0, (type_783F0 *)var_168, 0, 1.0f, 1.0f);
        unk_298 = var_164;
    }
    else
    {
        unk_298 = 0;
#ifndef CODFH_SP
        sub_19A750("WARNING: No idle face anim loaded for level!\n");
#endif
    }
    if (!unk_88_1)
        unk_88 |= 2;
    var_170 = var_C->unk_F8;
    if (valid_weapon_type(var_170))
    {
        unk_3E0.sub_15D010((type_3DAFC8 *)this, var_170);
        unk_3E0.sub_15D3E0();
    }
    switch (var_28->get_unk_44())
    {
    case 1:
        unk_2C |= 1;
        break;
    case 0:
        unk_2C |= 2;
        break;
    case 3:
        unk_2C |= 1;
        break;
    case 2:
        unk_2C |= 2;
    }
    if (unk_2C & 1)
        sub_D5B80(this, 0xC);
    else
        sub_D5B80(this, 0xB);
    var_180 = var_C->unk_FC;
    sub_6B5F0("SetDeletionDelay", (type_67620 *)(vf_098()), 0, 0, &var_180, 1, 1, 0);
    unk_778 = *(RwV3d *)vf_0C4();
    if (var_C->unk_E0.unk_00 || var_C->unk_E0.unk_04)
    {
        var_184 = sub_198800(&var_C->unk_E0);
        var_188 = (type_3DFEEC *)var_184;
        unk_734 = var_188->unk_24;
        if (unk_734)
            sub_178640(unk_734);
    }
    return 1;
}

// match: ??_Gtype_3DDB98@@UAEPAXI@Z @ 0x001773A0
// match: ??1type_3DDB98@@UAE@XZ @ 0x001773D0
// match: __ehhandler$??1type_3DDB98@@UAE@XZ-0x50 @ 0x00302100
// match: __ehhandler$??1type_3DDB98@@UAE@XZ @ 0x00302150
// sp-match: ??1type_3DDB98@@UAE@XZ @ 0x00115300
// sp-match: ??_Gtype_3DDB98@@UAEPAXI@Z @ 0x001152E0
// (Defined in the class: vf_230, called directly as in any destructor,
// then the members' destructors and the base's.)

// match: ?sub_178640@type_3DDB98@@QAEXPAUSplinePath@@@Z @ 0x00178640
// sp-match: ?sub_178640@type_3DDB98@@QAEXPAUSplinePath@@@Z @ 0x00111C30
void type_3DDB98::sub_178640(SplinePath *arg_0)
{
    unk_734 = arg_0;
    unk_6E4 = 0;
    unk_768 = 0;
    unk_738 = 1.0f;
    if (unk_734 && unk_734->unk_28)
    {
        unk_734->sub_BA990(unk_6E4, &unk_778, &unk_6F0);
        if (unk_734->unk_24 > 2500000.0f)
            unk_768 = 0.033333335f;
        else
            unk_768 = 100.0f / unk_734->unk_24;
        unk_76C = unk_778;
        unk_76C.y = vf_0C4()[1];
        vf_0D0(&unk_76C);
    }
}

// match: ?vf_230@type_3DDB98@@UAEXXZ @ 0x00178770
// sp-match: ?vf_230@type_3DDB98@@UAEXXZ @ 0x00111CF0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Shuts it down once: its clumps, collision, weapon, animations, sounds,
// performance player and script object released, and its trigger's object
// let go.
void type_3DDB98::vf_230()
{
    type_3DFEEC *var_C;
    GimpTrigger *bp_8;
    type_3D2E7C *bp_4;

    if (unk_784)
    {
        unk_784 = 0;
        unk_6CC.sub_129940(0);
        unk_6D8.sub_129940(0);
        vf_228();
        if (unk_3E0.get_unk_00() && valid_weapon_type(unk_3E0.unk_04))
            unk_3E0.sub_15D360();
#ifdef CODFH_SP // shape: SP 0x111CF0 releases them through an inline
        if (unk_280)
        {
            release_anim(unk_280);
        }
        if (unk_288)
        {
            release_anim(unk_288);
        }
#else
        if (unk_280)
        {
            sub_78870(unk_280);
            unk_280 = 0;
        }
        if (unk_288)
        {
            sub_78870(unk_288);
            unk_288 = 0;
        }
#endif
        sub_8B840(this);
        bp_4 = vf_098();
        if (vf_090())
        {
            sub_717B0((type_3D2C88 *)vf_090());
            unk_6A4 = 0;
        }
        if (bp_4)
        {
            sub_71970((type_3D2C88 *)bp_4);
            unk_6A0 = 0;
        }
        bp_8 = (GimpTrigger *)get_unk_34C();
        if (bp_8->unk_D8.unk_00)
        {
            var_C = (type_3DFEEC *)sub_198800(&bp_8->unk_D8);
            ((type_D48D0 *)&var_C->unk_24_id)->sub_D48D0(0);
        }
    }
}

// match: ?vf_03C@type_3DDB98@@UAEXM@Z @ 0x00178930
// sp-match: ?vf_03C@type_3DDB98@@UAEXM@Z @ 0x00114950
// Its logic for the time arg_0: the base's; its second animation's
// translations offset by unk_4E0 and two of its bones copied from the
// primary's; along its spline or to its point (sub_179530) unless it
// rides; riding at the ride's tag; and its weapon changed to its
// trigger's (as the soldier's, without its timers and AI).
void type_3DDB98::vf_03C(RwReal arg_0)
{
    RpHAnimHierarchy *var_40;
    type_7CBD0 *var_44;
    RpHAnimHierarchy *var_48;
    type_7CBD0 *var_4C;
    RpHAnimHierarchy *var_50;
    RwInt32 var_54;
    RpHAnimHierarchy *var_58;
    RwInt32 var_5C;
    RpHAnimHierarchy *var_60;
    RwInt32 var_64;
    RpHAnimHierarchy *var_68;
    RwInt32 var_6C;
    type_7CBD0_hdr *var_70;
    type_7CBD0_t *var_74;
    RwInt32 var_78;
    RwInt32 var_7C;
    RwUInt64 var_88;
    RtQuat *var_94;
    RtQuat *var_98;
    RpHAnimHierarchy *var_9C;
    type_129940 *var_A0;
    RpClump *var_A4;
    RwMatrix var_F0;
    RwFrame *var_F4;
    RwFrame *var_F8;
    GimpTrigger *var_FC;

    type_3D3548::vf_03C(arg_0);
    var_40 = unk_284->unk_18;
    var_44 = (type_7CBD0 *)((type_80300 *)var_40->currentAnim)->unk_144;
    var_48 = unk_28C->unk_18;
    var_4C = (type_7CBD0 *)((type_80300 *)var_48->currentAnim)->unk_144;
    var_50 = unk_28C->unk_18;
    var_54 = RpHAnimIDGetIndex(var_50, 0x386);
    var_58 = unk_284->unk_18;
    var_5C = RpHAnimIDGetIndex(var_58, 0x1C5);
    var_60 = unk_28C->unk_18;
    var_64 = RpHAnimIDGetIndex(var_60, 0x384);
    var_68 = unk_284->unk_18;
    var_6C = RpHAnimIDGetIndex(var_68, 0xC8);
    var_70 = var_4C->unk_04;
    var_74 = (type_7CBD0_t *)&var_4C->unk_10[var_70->unk_00];
    var_78 = 0;
    for (var_7C = 0; var_7C < unk_28C->get_unk_18()->numNodes; var_7C++)
    {
        var_88 = (RwUInt64)1 << var_7C;
        if (var_70->unk_10 & var_88)
        {
            var_74[var_78].unk_00.x -= unk_4E0[var_7C].unk_00.x;
            var_74[var_78].unk_00.y -= unk_4E0[var_7C].unk_00.y;
            var_74[var_78].unk_00.z -= unk_4E0[var_7C].unk_00.z;
            var_78++;
        }
    }
    var_94 = var_44->unk_10;
    var_98 = var_4C->unk_10;
    var_9C = unk_284->unk_18;
    if (((type_7CBD0_hdr *)((type_80300 *)var_9C->currentAnim)->unk_128)->unk_00)
    {
        var_98[var_54] = var_94[var_5C];
        var_98[var_64] = var_94[var_6C];
    }
    if (!unk_28_9 && (unk_760 & 6))
        sub_179530();
    if (unk_3D4 && unk_3D8.sub_D4910())
    {
        var_A0 = &unk_3D8.sub_D4910()->unk_25C;
        var_A4 = var_A0->unk_08;
        if (sub_EC2D0(var_A4, (RwInt32)&var_F0, unk_3DC, 0, 1))
        {
            var_F4 = unk_338.unk_08;
            var_F8 = var_F4;
            RwFrameTransform(var_F8, &var_F0, rwCOMBINEREPLACE);
            RwFrameUpdateObjects(var_F8);
        }
    }
    if (unk_3D4 && !unk_3D8.sub_D4910())
        unk_3D4 = 0;
    var_FC = (GimpTrigger *)get_unk_34C();
    if (var_FC && unk_3E0.get_unk_04() != var_FC->unk_F8 && valid_weapon_type(var_FC->unk_F8))
    {
        unk_3E0.sub_15D420();
        unk_3E0.sub_15D360();
        unk_3E0.sub_15D010((type_3DAFC8 *)this, var_FC->unk_F8);
        unk_3E0.sub_15D3E0();
    }
}

// match: ?vf_04C@type_3DDB98@@UAEXM@Z @ 0x00178DA0
// sp-match: ?vf_04C@type_3DDB98@@UAEXM@Z @ 0x00114BF0
// After the base's update for the time arg_0: its props (unk_35C) and its
// body (unk_6CC, bone 0x1C4) follow its frame or bones, and its atomic's
// centre its root bone's height; its second animation's speed (2 with
// cheat flag 0) and time; a knocked-off head (unk_6D8) flies (unk_695 2)
// until it lands, else follows its frame or (bone 0x1A9, or its body's
// unk_69C node) its neck; its weapon in hand (as the soldier's).
void type_3DDB98::vf_04C(RwReal arg_0)
{
    type_3D3548 *var_8;
    RpHAnimHierarchy *var_C;
    RwMatrix *var_10;
    RpClump *var_14;
    RwFrame *var_18;
    RwMatrix *var_1C;
    RwInt32 var_20;
    RwFrame *var_24;
    RwFrame *var_28;
    RpClump *var_2C;
    RpClump *var_30;
    RwFrame *var_34;
    RwMatrix *var_38;
    RpHAnimHierarchy *var_3C;
    RwInt32 var_40;
    RpHAnimHierarchy *var_44;
    RwInt32 var_48;
    RwFrame *var_4C;
    RwFrame *var_50;
    RpAtomic *var_54;
    RwMatrix *var_58;
    RpHAnimHierarchy *var_5C;
    RwReal var_60;
    bool var_6D;
    RpClump *var_74;
    RpClump *var_78;
    RwFrame *var_7C;
    RwMatrix *var_80;
    RwV3d var_8C;
    RwV3d var_98;
    bool var_99;
    RwV3d var_A8;
    RwV3d var_B4;
    RwReal var_C0;
    RpClump *var_C4;
    RpClump *var_C8;
    RwFrame *var_CC;
    RwMatrix *var_D0;
    RpClump *var_D4;
    RwFrame *var_D8;
    RwMatrix *var_DC;
    RpClump *var_E0;
    RpClump *var_E4;
    RpClump *var_E8;
    RwMatrix var_130;
    RwMatrix *var_134;
    RpHAnimHierarchy *var_138;
    RwInt32 var_13C;
    RpClump *var_140;
    RwFrame *var_144;
    RwMatrix *var_148;

    var_8 = 0;
    type_3D3548::vf_04C(arg_0);
    var_C = unk_284->unk_18;
    var_10 = RpHAnimHierarchyGetMatrixArray(var_C);
    if (!unk_28_13)
    {
        var_14 = unk_25C.unk_08;
        var_18 = RpClumpGetFrame(var_14);
        var_1C = RwFrameGetLTM(var_18);
        for (var_20 = 0; var_20 < 2; var_20++)
        {
            var_8 = unk_35C[var_20].sub_D4910();
            if (var_8)
            {
                var_24 = var_8->unk_338.unk_08;
                var_28 = var_24;
                *RwFrameGetMatrix(var_28) = *var_1C;
                RwFrameUpdateObjects(var_28);
            }
        }
    }
    else
    {
        var_2C = unk_6CC.unk_08;
        if (var_2C)
        {
            var_30 = unk_6CC.unk_08;
            var_34 = RpClumpGetFrame(var_30);
            var_38 = RwFrameGetMatrix(var_34);
            var_3C = unk_284->unk_18;
            var_40 = RpHAnimIDGetIndex(var_3C, 0x1C4);
            *var_38 = var_10[var_40];
            RwFrameUpdateObjects(var_34);
        }
        for (var_20 = 0; var_20 < 2; var_20++)
        {
            var_8 = unk_35C[var_20].sub_D4910();
            if (var_8 && unk_364[var_20])
            {
                var_44 = unk_284->unk_18;
                var_48 = RpHAnimIDGetIndex(var_44, unk_364[var_20]);
                var_4C = var_8->unk_338.unk_08;
                var_50 = var_4C;
                *RwFrameGetMatrix(var_50) = var_10[var_48];
                RwFrameUpdateObjects(var_50);
            }
        }
        var_54 = unk_250.unk_08;
        if (var_54)
        {
            var_58 = RwFrameGetLTM(RpAtomicGetFrame(var_54));
            var_5C = unk_284->unk_18;
            var_60 = var_10[RpHAnimIDGetIndex(var_5C, 1)].pos.y - var_58->pos.y;
            var_54->boundingSphere.center.y = var_60;
        }
    }
    if (((type_4B8888 *)dword_4B8888)->unk_00_0)
        unk_28C->set_unk_28(2.0f);
    else
        unk_28C->set_unk_28(unk_68C);
    if (unk_28C)
    {
        var_6D = false;
        if (unk_284->unk_12 & 4)
            var_6D = true;
        unk_28C->sub_7C090(arg_0 * flt_3DDB90 * 0.001f, var_6D);
    }
    if (unk_695 > 1)
    {
        if (unk_695 > 2)
        {
        }
        else
        {
            var_74 = unk_6D8.unk_08;
            if (var_74)
            {
                var_78 = unk_6D8.unk_08;
                var_7C = RpClumpGetFrame(var_78);
                var_80 = RwFrameGetMatrix(var_7C);
                var_8C = var_80->pos;
                var_98 = var_80->pos;
                var_98.x += arg_0 * unk_674.x;
                var_98.y += arg_0 * unk_674.y;
                var_98.z += arg_0 * unk_674.z;
                var_99 = true;
                if (sub_FCAE0(&var_8C, &var_98, &var_B4, &var_A8, sub_9A800(this), 1, 1))
                {
                    if (var_A8.y > 0.7f)
                    {
                        unk_695++;
                        var_80->pos.x = var_B4.x;
                        var_80->pos.y = var_B4.y;
                        var_80->pos.z = var_B4.z;
                        var_99 = false;
                    }
                    else
                    {
                        var_C0 = sqrt(unk_674.x * unk_674.x + unk_674.z * unk_674.z);
                        unk_674.x = var_C0 * var_A8.x;
                        unk_674.z = var_C0 * var_A8.z;
                    }
                }
                if (var_99)
                {
                    var_80->pos.x += arg_0 * unk_674.x;
                    var_80->pos.y += arg_0 * unk_674.y;
                    var_80->pos.z += arg_0 * unk_674.z;
                    unk_674.y -= 0.5f * arg_0;
                    sub_140440(var_80, &unk_680, 0.5f);
                }
                RwFrameUpdateObjects(var_7C);
            }
        }
    }
    else if (!unk_28_13)
    {
        var_C4 = unk_6D8.unk_08;
        if (var_C4)
        {
            var_C8 = unk_25C.unk_08;
            var_CC = RpClumpGetFrame(var_C8);
            var_D0 = RwFrameGetLTM(var_CC);
            var_D4 = unk_6D8.unk_08;
            var_D8 = RpClumpGetFrame(var_D4);
            var_DC = RwFrameGetMatrix(var_D8);
            *var_DC = *var_D0;
            RwFrameUpdateObjects(var_D8);
        }
    }
    else
    {
        var_E0 = unk_6D8.unk_08;
        if (var_E0)
        {
            var_E4 = unk_6CC.unk_08;
            var_E8 = unk_6CC.unk_08;
            if (sub_EC310(var_E8, sub_16D970(var_E4), &var_130, unk_69C, 0, 1))
            {
                var_134 = &var_130;
            }
            else
            {
                var_138 = unk_284->unk_18;
                var_13C = RpHAnimIDGetIndex(var_138, 0x1A9);
                var_134 = &var_10[var_13C];
            }
            var_140 = unk_6D8.unk_08;
            var_144 = RpClumpGetFrame(var_140);
            var_148 = RwFrameGetMatrix(var_144);
            RwMatrixTransform(var_148, var_134, rwCOMBINEREPLACE);
            RwFrameUpdateObjects(var_144);
        }
    }
    if (unk_3E0.get_unk_00())
        sub_17BDD0(&unk_3E0, 0x1C2, (RwInt32)arg_0);
}

// match: ?sub_179530@type_3DDB98@@QAEXXZ @ 0x00179530
// sp-match: ?sub_179530@type_3DDB98@@QAEXXZ @ 0x00111E10
// Moves it along its spline path by its speed (at an end the path turns
// back, wraps or is done), facing its point ahead; or, with flag 1, steps
// it along the path towards its goto point until within 75 of it, set on
// the ground when it follows the terrain. Arriving tells its scripts
// ("IHaveArrived", "SplinePath_ArrivedATDestination"); a finished path is
// dropped.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3DDB98::sub_179530()
{
#ifndef CODFH_SP
    RwReal v6C;
#endif
    type_92430 var_68;
    RwV3d local_3C;
    RwV3d v30;
    RwReal slot_24;
    RwReal v20;
    RwReal slot_1C;
    RwInt32 local_18;
    RwInt32 local_14;
    RwReal local_10;
    RwV3d var_C;

    local_14 = 0;
    local_18 = 0;
    local_10 = unk_6E4;
    if (!(unk_760 & 1))
    {
        slot_1C = unk_154.z;
        v20 = slot_1C / vf_0F4()->unk_24;
#ifdef CODFH_SP // shape: SP 0x111E10 compares the floats
        unk_6E4 += v20 * unk_730;
        if (unk_6E4 > unk_738)
            unk_6E4 = unk_738;
#else
        unk_6E4 += v20 * unk_730;
        if ((RwDouble)unk_6E4 > (RwDouble)unk_738)
            unk_6E4 = (RwReal)(RwDouble)unk_738;
#endif
        else if (unk_6E4 < 0.0f)
            unk_6E4 = 0;
        if (unk_6E4 >= unk_738 || unk_6E4 <= 0.0f)
        {
            if (unk_734->unk_1C_0 == 2)
            {
                unk_730 = -unk_730;
            }
            else if (unk_734->unk_1C_0 == 1)
            {
                unk_6E4 = 0;
            }
            else
            {
                local_18 = 1;
                unk_760 &= ~6;
            }
            local_14 = 1;
        }
        unk_734->sub_BA990(unk_6E4, &var_C, &unk_6F0);
        vf_0C0(&var_C);
        local_10 = unk_768 * unk_730 + unk_6E4;
        if (local_10 > 1.0f)
            local_10 = 1.0f;
        else if (local_10 < 0.0f)
            local_10 = 0;
        unk_734->sub_BA990(local_10, &var_C, &unk_6F0);
        vf_0D0(&var_C);
    }
    else
    {
        local_3C = *(RwV3d *)vf_0C4();
        RwV3dSubMacro(&v30, &unk_778, &local_3C);
        v30.y = 0;
        slot_24 = RwV3dLength((RwV3d *)&v30);
        if (slot_24 < 75.0f)
        {
            if (unk_760 & 2)
            {
#ifdef CODFH_SP // shape: SP 0x111E10 compares the floats
                unk_6E4 += unk_768;
                if (unk_6E4 > unk_738)
                    unk_6E4 = unk_738;
#else
                unk_6E4 += unk_768;
                if ((RwDouble)unk_6E4 > (RwDouble)unk_738)
                    unk_6E4 = (RwReal)(RwDouble)unk_738;
#endif
                else if (unk_6E4 < 0.0f)
                    unk_6E4 = 0;
                if (unk_6E4 >= unk_738)
                {
                    local_14 = 1;
                    local_18 = 1;
                    unk_760 &= ~6;
                }
                else
                {
                    unk_734->sub_BA990(unk_6E4, &unk_778, &unk_6F0);
                    unk_76C = unk_778;
                }
            }
            else
            {
                local_14 = 1;
                unk_760 &= ~6;
            }
        }
        if (unk_764 == 1 || (unk_764 == 0 && unk_28_13))
        {
            local_3C.y += 150.0f;
            sub_92430(&local_3C, &var_68, 100.0f);
            if (var_68.unk_20)
                local_3C.y = var_68.unk_08.y;
            else
                local_3C.y = unk_778.y;
        }
        else
        {
            local_3C.y = unk_778.y;
        }
        if (!local_14 && !local_18)
        {
            vf_0C0(&local_3C);
            if (unk_760 & 4)
                unk_76C = unk_778;
            unk_76C.y = local_3C.y;
        }
        vf_0D0(&unk_76C);
    }
    if (local_14)
    {
#ifdef CODFH_SP // shape: block-scoped, SP 0x111E10 shares its slot with local_10
        RwReal v6C = deltaTime;
#else
        v6C = deltaTime;
#endif
        sub_6B5F0("IHaveArrived", (type_67620 *)(vf_098()), 0, 0, (RwInt32 *)(&v6C), 1, 1, 0);
        sub_6B5F0("SplinePath_ArrivedATDestination", (type_67620 *)(vf_098()), 0, 0, 0, 0, 1, 0);
    }
    if (local_18)
        sub_178640(0);
}

// match: ?vf_224@type_3DDB98@@UAE_NPAUtype_3DF8D8@@HPAH@Z @ 0x00179A50
// sp-match: ?vf_224@type_3DDB98@@UAE_NPAUtype_3DF8D8@@HPAH@Z @ 0x001121C0
// The base's set-up of its model from the definition arg_0, then its
// atomic's bounding radius (100) and flags, and its weapon class.
bool type_3DDB98::vf_224(type_3DF8D8 *arg_0, RwInt32 arg_4, RwInt32 *arg_8)
{
    RpAtomic *var_4;
    RwInt32 local_8;

    type_3D3548::vf_224(arg_0, 0, 0);
    var_4 = unk_274.unk_08;
    var_4->boundingSphere.radius = 100.0f;
    ((RwObject *)var_4)->flags = 1;
    local_8 = ((type_1917A0 *)arg_0)->unk_44;
    unk_290 = local_8;
    return true;
}

// match: ?sub_179AB0@type_3DDB98@@QAEXPAURpClump@@@Z @ 0x00179AB0
// sp-match: ?sub_179AB0@type_3DDB98@@QAEXPAURpClump@@@Z @ 0x00112200
// Holds a copy of the clump arg_0 (its body) in unk_6CC (none for 0), its
// hierarchy updating its modelling matrices (as the soldier's sub_13ACE0).
void type_3DDB98::sub_179AB0(RpClump *arg_0)
{
    RpClump *var_4;
    RwUInt32 v8;
    RpHAnimHierarchy *varC;

    unk_6CC.sub_129940(0);
    if (arg_0)
    {
        var_4 = RpClumpClone(arg_0);
        if (var_4)
        {
            unk_6CC.sub_129620(var_4);
            unk_6CC.sub_129690(this);
            varC = sub_16D970(unk_6CC.get_unk_08());
            sub_79270(unk_6CC.get_unk_08(), 0);
            v8 = varC->flags;
            v8 |= rpHANIMHIERARCHYUPDATEMODELLINGMATRICES;
            varC->flags = v8;
        }
    }
}

// match: ?sub_179B70@type_3DDB98@@QAEXPAURpClump@@@Z @ 0x00179B70
// sp-match: ?sub_179B70@type_3DDB98@@QAEXPAURpClump@@@Z @ 0x00112270
// Holds a copy of the clump arg_0 (its head) in unk_6D8 at the identity
// (none for 0; as the soldier's sub_13ADA0).
void type_3DDB98::sub_179B70(RpClump *arg_0)
{
    RpClump *var_4;
    RwFrame *local_8;

    unk_6D8.sub_129940(0);
    if (arg_0)
    {
        var_4 = RpClumpClone(arg_0);
        if (var_4)
        {
            local_8 = RpClumpGetFrame(var_4);
            if (!local_8)
                local_8 = RwFrameCreate();
            RwFrameSetIdentity(local_8);
            unk_6D8.sub_129620(var_4);
            unk_6D8.sub_129690(this);
        }
    }
    else
    {
        unk_6D8.sub_129620(0);
    }
}

// match: ?sub_179C10@@YAHPAUtype_F2FF0@@@Z @ 0x00179C10
// match: __ehhandler$?sub_179C10@@YAHPAUtype_F2FF0@@@Z-0x8 @ 0x00302160
// match: __ehhandler$?sub_179C10@@YAHPAUtype_F2FF0@@@Z @ 0x00302168
// sp-match: ?sub_179C10@@YAHPAUtype_F2FF0@@@Z @ 0x001122E0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// A particle system's callback while it follows a gimp (set by vf_170's
// 0x516): its matrix at the gimp's bone arg_0->unk_158 (in its clump, its
// body or its mounted weapon's), or at the gimp's frame; 0 once the gimp
// or the bone is gone (as the base's sub_CDFA0).
RwInt32 sub_179C10(type_F2FF0 *arg_0)
{
    RwInt32 v14 = 0;
    RpClump *var_2C;
    RwMatrix *loc28;
    RwFrame *slot_24;
    type_3D3548 *v20;
    RpHAnimHierarchy *loc1C;
    type_3DDB98 *bp_18;
    type_D48D0 lv_10;

    lv_10 = arg_0->unk_150;
    if (!lv_10.sub_D4910())
        return 0;
    bp_18 = lv_10.sub_D4910()->vf_024();
    if (bp_18)
    {
        if (bp_18->unk_28_13)
        {
            v14 = 1;
            loc1C = bp_18->get_unk_284()->unk_18;
            if (!sub_EC310(bp_18->get_unk_264(), loc1C, &arg_0->unk_00, arg_0->unk_158, 0, 0)
                && !sub_EC310(bp_18->unk_6CC.get_unk_08(), loc1C, &arg_0->unk_00, arg_0->unk_158, 0, 0))
            {
                v20 = bp_18->vf_1F8(0);
                if (!v20 || !sub_EC2D0(v20->get_unk_264(), (RwInt32)arg_0, arg_0->unk_158, 0, 0))
                    v14 = 0;
            }
        }
        else
        {
            var_2C = bp_18->unk_25C.unk_08;
            slot_24 = RpClumpGetFrame(var_2C);
            loc28 = RwFrameGetLTM(slot_24);
            arg_0->unk_00 = *loc28;
        }
    }
    return v14;
}

// match: ?vf_170@type_3DDB98@@UAEXHHHH@Z @ 0x00179DD0
// sp-match: ?vf_170@type_3DDB98@@UAEXHHHH@Z @ 0x001123E0
// Its handler for the message arg_0 with the data arg_4 (unless its flag
// 13 of unk_88 is set), as the soldier's: 1 replays its own animation when
// its face player loops; 0xB54 plays the animation of *arg_4; 0x516 spawns
// the particle system at a bone of its clump, its body or its prop (made
// to follow it with sub_179C10 when asked); 0x7D0 fires or stops its
// weapon; 0xA8C sets or clears unk_3D4; 0x960 shows or hides its weapon's
// parts and sets vf_18C; 0x9C4 sets a hatch of the vehicle it rides;
// 0xA28 that vehicle's vision; the rest go to the base with no player.
void type_3DDB98::vf_170(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C)
{
#ifndef CODFH_SP // SP declares these in their cases
    RwInt32 var_C;
    RwInt32 var_10;
#endif
    type_13AE40_msg *var_14;
#ifndef CODFH_SP
    RwInt32 var_18;
    RwInt32 var_1C;
#endif
    type_13AE40_msg *var_20;
    type_F2FF0 *var_24;
    RpHAnimHierarchy *var_28;
    RpClump *var_2C;
    RwMatrix var_70;
    RpHAnimHierarchy *var_74;
    RpClump *var_78;
    type_129940 *var_7C;
    RpClump *var_80;
    RpClump *var_84;
    RwFrame *var_88;
    RwMatrix *var_8C;
    type_13AE40_msg *var_90;
    type_13AE40_msg *var_98;
    type_13AE40_msg *var_A0;
    type_3D3548 *var_B0;
    type_3DC048 *var_B4;
    bool var_B5;
    type_13AE40_hatch *var_BC;
    type_13AE40_msg *var_C0;
    type_13AE40_msg *var_C8;
    type_13AE40_vision *var_CC;
    type_3D3548 *var_D4;
    type_3DBC78 *var_D8;

    if (unk_88_13)
        return;
    switch ((RwUInt32)arg_0)
    {
#ifdef CODFH_SP // shape: SP 0x1123E0 shares the two cases' slots
    case 1:
    {
        RwInt32 var_C;
        RwInt32 var_10;
        if (((type_7C8D0 *)arg_C)->unk_12 & 2)
        {
            if (unk_298 && unk_298 != arg_8 && sub_77B70(unk_298, (void **)(&var_10), (void **)(&var_C)))
            {
                unk_28C->sub_794C0(0.1f);
                unk_28C->sub_796A0((RtAnimAnimation *)var_10, unk_298, 0, (type_783F0 *)var_C, 0, 1.0f,
                                   1.0f);
                unk_694 = 0;
            }
        }
        else
        {
            type_3D3548::vf_170(arg_0, arg_4, arg_8, 0);
        }
        break;
    }
    case 0xB54:
    {
        RwInt32 var_18;
        RwInt32 var_1C;
        var_14 = (type_13AE40_msg *)arg_4;
        if (sub_77B70(var_14->unk_00, (void **)(&var_1C), (void **)(&var_18)))
        {
            unk_28C->sub_794C0(0.1f);
            unk_28C->sub_796A0((RtAnimAnimation *)var_1C, var_14->unk_00, 0, (type_783F0 *)var_18, 0, 1.0f,
                               1.0f);
            unk_694 = 8;
        }
        break;
    }
#else
    case 1:
        if (((type_7C8D0 *)arg_C)->unk_12 & 2)
        {
            if (unk_298 && unk_298 != arg_8 && sub_77B70(unk_298, (void **)(&var_10), (void **)(&var_C)))
            {
                unk_28C->sub_794C0(0.1f);
                unk_28C->sub_796A0((RtAnimAnimation *)var_10, unk_298, 0, (type_783F0 *)var_C, 0, 1.0f,
                                   1.0f);
                unk_694 = 0;
            }
        }
        else
        {
            type_3D3548::vf_170(arg_0, arg_4, arg_8, 0);
        }
        break;
    case 0xB54:
        var_14 = (type_13AE40_msg *)arg_4;
        if (sub_77B70(var_14->unk_00, (void **)(&var_1C), (void **)(&var_18)))
        {
            unk_28C->sub_794C0(0.1f);
            unk_28C->sub_796A0((RtAnimAnimation *)var_1C, var_14->unk_00, 0, (type_783F0 *)var_18, 0, 1.0f,
                               1.0f);
            unk_694 = 8;
        }
        break;
#endif
    case 0x516:
        var_20 = (type_13AE40_msg *)arg_4;
        var_24 = 0;
        if (unk_28_13)
        {
            var_28 = unk_284->unk_18;
            var_2C = unk_25C.unk_08;
            if (sub_EC310(var_2C, var_28, &var_70, var_20->unk_00, 0, 0))
            {
                var_24 = (type_F2FF0 *)sub_F2FF0(var_20->unk_0C, &var_70, 0, 0, 0, 0);
            }
            else
            {
                var_74 = unk_284->unk_18;
                var_78 = unk_6CC.unk_08;
                if (sub_EC310(var_78, var_74, &var_70, var_20->unk_00, 0, 0))
                {
                    var_24 = (type_F2FF0 *)sub_F2FF0(var_20->unk_0C, &var_70, 0, 0, 0, 0);
                }
                else if (unk_35C[0].sub_D4910())
                {
                    var_7C = &unk_35C[0].sub_D4910()->unk_25C;
                    var_80 = var_7C->unk_08;
                    if (sub_EC2D0(var_80, (RwInt32)&var_70, var_20->unk_00, 0, 0))
                        var_24 = (type_F2FF0 *)sub_F2FF0(var_20->unk_0C, &var_70, 0, 0, 0, 0);
                }
            }
        }
        else
        {
            var_84 = unk_25C.unk_08;
            var_88 = RpClumpGetFrame(var_84);
            var_8C = RwFrameGetLTM(var_88);
            var_24 = (type_F2FF0 *)sub_F2FF0(var_20->unk_0C, var_8C, 0, 0, 0, 0);
        }
        if (var_24 && var_20->unk_04)
        {
            var_24->unk_150_h = unk_384_h;
            var_24->unk_158 = var_20->unk_00;
            var_24->unk_154 = sub_179C10;
        }
        break;
    case 0x7D0:
        var_90 = (type_13AE40_msg *)arg_4;
        switch (var_90->unk_00)
        {
        case 0:
            unk_3E0.sub_15D510(0, 0);
            break;
        case 1:
        case 2:
        case 3:
            if (var_90->unk_04)
                unk_3E0.sub_15D510(1, (RwInt32)&var_90->unk_04);
            else
                unk_3E0.sub_15D510(1, 0);
            break;
        }
        break;
    case 0xA8C:
        var_98 = (type_13AE40_msg *)arg_4;
        switch (var_98->unk_00)
        {
        case 2:
            unk_3D4 = 1;
            break;
        case 3:
            unk_3D4 = 0;
            break;
        }
        break;
    case 0x960:
        var_A0 = (type_13AE40_msg *)arg_4;
        switch (var_A0->unk_00)
        {
        case 0:
            sub_16E080(unk_3E0.get_unk_18(), -1);
            break;
        case 1:
            sub_16E080(unk_3E0.get_unk_18(), 0);
            break;
        case 4:
            vf_18C(1);
            break;
        case 5:
            vf_18C(0);
            break;
        }
        break;
    case 0x9C4:
        if (!unk_3D8.sub_D4910())
            break;
        var_B0 = unk_3D8.sub_D4910();
        var_B4 = var_B0->vf_014();
        if (var_B4)
        {
            var_B5 = false;
            var_BC = (type_13AE40_hatch *)arg_4;
            var_C0 = (type_13AE40_msg *)arg_4;
            switch (var_BC->unk_00)
            {
            case 0:
                var_B5 = true;
                break;
            case 1:
                var_B5 = false;
                break;
            }
            if (var_B5 != (bool)var_B4->sub_15A480(var_BC->unk_01))
                var_B4->sub_15A4A0(var_BC->unk_01, var_BC->unk_02, var_BC->unk_03, var_C0->unk_04, var_B5);
        }
        break;
    case 0xA28:
        var_C8 = (type_13AE40_msg *)arg_4;
        var_CC = (type_13AE40_vision *)arg_4;
        switch (var_C8->unk_08)
        {
        case 1:
            if (!unk_3D8.sub_D4910())
                break;
            var_D4 = unk_3D8.sub_D4910();
            var_D8 = var_D4->vf_010();
            if (var_D8)
            {
                var_D8->vf_23C(var_CC->unk_00);
                switch (var_C8->unk_04)
                {
                case 0:
                    var_D8->vf_244(0);
                    break;
                case 1:
                    var_D8->vf_244(1);
                    break;
                }
            }
            break;
        }
        break;
    default:
        type_3D3548::vf_170(arg_0, arg_4, arg_8, 0);
        break;
    }
}

// match: ?vf_054@type_3DDB98@@UAEXH@Z @ 0x0017A520
// sp-match: ?vf_054@type_3DDB98@@UAEXH@Z @ 0x001128F0
// Its render (unless its trigger hides it by bit 11 of unk_24, or gimps
// are hidden): its clump and its body's and head's as the base renders its
// clump (faded while unk_28_18 is set), with the cull mode flipped while
// its second animation runs with flag 4 (as the soldier's).
void type_3DDB98::vf_054(RwInt32 arg_0)
{
    RwRGBA var_4;
    RpClump *v8;
    RwInt32 varC;

    var_4.red = 255;
    var_4.green = 255;
    var_4.blue = 255;
    var_4.alpha = 255;
    if (get_unk_34C() && get_unk_34C()->unk_24_11)
        return;
    if (dword_4E6F24)
        return;
    sub_16D7F0(0x11);
    v8 = unk_25C.unk_08;
    if (v8)
    {
        if (unk_28_18)
        {
            var_4.alpha = (RwUInt8)(255.0f * unk_2AC);
            dword_4B697C = 0;
            dword_4B69E0 = 0;
            RpClumpForAllAtomics(v8, sub_D3B30, &var_4);
        }
        sub_D2920(v8, 0);
        if (unk_28_18)
        {
            var_4.alpha = 255;
            dword_4B697C = 0;
            dword_4B69E0 = 0;
            RpClumpForAllAtomics(v8, sub_D3BE0, &var_4);
        }
    }
    varC = 0;
    if (unk_28C && (unk_284->unk_12 & 4))
    {
        RwRenderStateGet(rwRENDERSTATECULLMODE, &varC);
        if (varC > 1)
            RwRenderStateSet(rwRENDERSTATECULLMODE, (void *)((varC == 2) + 2));
    }
    v8 = unk_6CC.unk_08;
    if (v8)
    {
        if (unk_28_18)
        {
            var_4.alpha = (RwUInt8)(255.0f * unk_2AC);
            dword_4B697C = 0;
            dword_4B69E0 = 0;
            RpClumpForAllAtomics(v8, sub_D3B30, &var_4);
        }
        sub_D2920(v8, 0);
        if (unk_28_18)
        {
            var_4.alpha = 255;
            dword_4B697C = 0;
            dword_4B69E0 = 0;
            RpClumpForAllAtomics(v8, sub_D3BE0, &var_4);
        }
    }
    v8 = unk_6D8.unk_08;
    if (v8)
    {
        if (unk_28_18)
        {
            var_4.alpha = (RwUInt8)(255.0f * unk_2AC);
            dword_4B697C = 0;
            dword_4B69E0 = 0;
            RpClumpForAllAtomics(v8, sub_D3B30, &var_4);
        }
        sub_D2920(v8, 0);
        if (unk_28_18)
        {
            var_4.alpha = 255;
            dword_4B697C = 0;
            dword_4B69E0 = 0;
            RpClumpForAllAtomics(v8, sub_D3BE0, &var_4);
        }
    }
    if (varC)
        RwRenderStateSet(rwRENDERSTATECULLMODE, (void *)varC);
    sub_16D850(0x11);
}

// match: ?vf_098@type_3DDB98@@UAEPAUtype_3D2E7C@@XZ @ 0x0017A800
// sp-match: ?vf_098@type_3DDB98@@UAEPAUtype_3D2E7C@@XZ @ 0x00112B10
type_3D2E7C *type_3DDB98::vf_098()
{
    return (type_3D2E7C *)sub_67620(unk_6A0);
}

// match: ?vf_090@type_3DDB98@@UAEPAUtype_6D380@@XZ @ 0x0017A820
// sp-match: ?vf_090@type_3DDB98@@UAEPAUtype_6D380@@XZ @ 0x00112B20
struct type_6D380 *type_3DDB98::vf_090()
{
    return (type_6D380 *)sub_67620(unk_6A4);
}

// match: ?sub_17A840@type_3DDB98@@QAEXHH@Z @ 0x0017A840
// sp-match: ?sub_17A840@type_3DDB98@@QAEXHH@Z @ 0x00112B30
// "EnableWeaponRender": shows (arg_4 set) or hides its weapon's model
// (arg_0 0; it has no grenade).
void type_3DDB98::sub_17A840(RwInt32 arg_0, RwInt32 arg_4)
{
    if (arg_0 == 0 && unk_3E0.get_unk_18())
    {
        if (arg_4)
            sub_16E080(unk_3E0.get_unk_18(), -1);
        else
            sub_16E080(unk_3E0.get_unk_18(), 0);
    }
}

// match: ?vf_058@type_3DDB98@@UAEHPAUtype_3DF8D8_04@@@Z @ 0x0017A8B0
// sp-match: ?vf_058@type_3DDB98@@UAEHPAUtype_3DF8D8_04@@@Z @ 0x00112B70
// Whether arg_0 is one of the keys (0 to 2) of its definition's model
// objects (as the soldier's).
RwInt32 type_3DDB98::vf_058(type_3DF8D8_04 *arg_0)
{
    type_1917A0 *var_4;
    type_3DF8D8_04 *v8;
    type_1908A0 *stk_C;
    type_3DF8D8 *var_10;
    GimpTrigger *lv_14;

    lv_14 = (GimpTrigger *)get_unk_34C();
    var_10 = sub_198800(&lv_14->unk_C0);
    var_4 = (type_1917A0 *)var_10;
    stk_C = var_4->sub_1917A0();
    v8 = ((type_3DF9C4 *)stk_C)->sub_1908A0(0);
    if (arg_0->unk_00 == v8->unk_00 && arg_0->unk_04 == v8->unk_04)
        return 1;
    v8 = ((type_3DF9C4 *)stk_C)->sub_1908A0(1);
    if (arg_0->unk_00 == v8->unk_00 && arg_0->unk_04 == v8->unk_04)
        return 1;
    v8 = ((type_3DF9C4 *)stk_C)->sub_1908A0(2);
    if (arg_0->unk_00 == v8->unk_00 && arg_0->unk_04 == v8->unk_04)
        return 1;
    stk_C = var_4->sub_1917F0();
    v8 = ((type_3DF9C4 *)stk_C)->sub_1908A0(0);
    if (arg_0->unk_00 == v8->unk_00 && arg_0->unk_04 == v8->unk_04)
        return 1;
    v8 = ((type_3DF9C4 *)stk_C)->sub_1908A0(1);
    if (arg_0->unk_00 == v8->unk_00 && arg_0->unk_04 == v8->unk_04)
        return 1;
    v8 = ((type_3DF9C4 *)stk_C)->sub_1908A0(2);
    if (arg_0->unk_00 == v8->unk_00 && arg_0->unk_04 == v8->unk_04)
        return 1;
    stk_C = var_4->sub_191840();
    if (stk_C)
    {
        v8 = ((type_3DF9C4 *)stk_C)->sub_1908A0(0);
        if (arg_0->unk_00 == v8->unk_00 && arg_0->unk_04 == v8->unk_04)
            return 1;
        v8 = ((type_3DF9C4 *)stk_C)->sub_1908A0(1);
        if (arg_0->unk_00 == v8->unk_00 && arg_0->unk_04 == v8->unk_04)
            return 1;
        v8 = ((type_3DF9C4 *)stk_C)->sub_1908A0(2);
        if (arg_0->unk_00 == v8->unk_00 && arg_0->unk_04 == v8->unk_04)
            return 1;
    }
    return 0;
}

// match: ?vf_07C@type_3DDB98@@UAEHCPAURpIntersection@@PAMH@Z @ 0x0017AAD0
// sp-match: ?vf_07C@type_3DDB98@@UAEHCPAURpIntersection@@PAMH@Z @ 0x00112D20
// The line (arg_0 1) or sphere of arg_4 against its bone boxes (13 of
// them while its animation drives it, else one box 30 across, as high as
// its stance puts its head); -1 for a miss or while unk_88_1 is clear (as
// the soldier's).
RwInt32 type_3DDB98::vf_07C(RwInt8 arg_0, RpIntersection *arg_4, RwReal *arg_8, RwInt32 arg_C)
{
    RwInt32 var_8;

    if (!unk_88_1)
        return -1;
    var_8 = -1;
    if (arg_0 == 1)
    {
        if (unk_28_13)
        {
            RpHAnimHierarchy *var_C;

            var_C = unk_284->unk_18;
            var_8 = sub_8D660(0xD, var_C, arg_4, arg_C == 0, 0);
        }
        else
        {
            type_4B21D0_60 var_30;
            RpHAnimHierarchy *var_34;

            var_30.unk_00 = -15.0f;
            var_30.unk_04 = 0.0f;
            var_30.unk_08 = -15.0f;
            var_30.unk_0C = 0.0f;
            var_30.unk_10 = 15.0f;
            if (vf_0BC() == 0)
                var_30.unk_14 = unk_48;
            else if (vf_0BC() == 1)
                var_30.unk_14 = unk_48 / 2.0f;
            else if (vf_0BC() == 2)
                var_30.unk_14 = unk_48 / 6.0f;
            else
                var_30.unk_14 = unk_48;
            var_30.unk_18 = 15.0f;
            var_30.unk_1C = 0.0f;
            var_34 = unk_284->unk_18;
            var_8 = sub_8D660(1, var_34, arg_4, arg_C == 0, &var_30);
        }
    }
    else
    {
        if (unk_28_13)
        {
            RpHAnimHierarchy *var_38;

            var_38 = unk_284->unk_18;
            var_8 = sub_8E330(0xD, var_38, arg_4, arg_C == 0, 0);
        }
        else
        {
            type_4B21D0_60 var_60;
            RpHAnimHierarchy *var_64;

            var_60.unk_00 = -15.0f;
            var_60.unk_04 = 0.0f;
            var_60.unk_08 = -15.0f;
            var_60.unk_0C = 0.0f;
            var_60.unk_10 = 15.0f;
            if (vf_0BC() == 0)
                var_60.unk_14 = unk_48;
            else if (vf_0BC() == 1)
                var_60.unk_14 = unk_48 / 2.0f;
            else if (vf_0BC() == 2)
                var_60.unk_14 = unk_48 / 6.0f;
            else
                var_60.unk_14 = unk_48;
            var_60.unk_18 = 15.0f;
            var_60.unk_1C = 0.0f;
            var_64 = unk_284->unk_18;
            var_8 = sub_8E330(1, var_64, arg_4, arg_C == 0, &var_60);
        }
    }
    return var_8;
}

// match: ?sub_17AD60@@YAXPAUtype_7C8D0@@@Z @ 0x0017AD60
// sp-match: ?sub_17AD60@@YAXPAUtype_7C8D0@@@Z @ 0x00112F20
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The dying face: one of the four death animations at random on the
// animation arg_0 (the soldier's too, sub_13C490).
void sub_17AD60(type_7C8D0 *arg_0)
{
    RwInt32 var_10;
    RwUInt32 var_C;
    RwInt32 bp_8;
    RwUInt32 bp_4;

    var_C = RpRandom() % 4;
    bp_4 = sub_16C800(byte_42A370[var_C].unk_00, 0x811C9DC5); // not an address: the FNV basis
    if (sub_77B70(bp_4, (void **)(&var_10), (void **)(&bp_8)))
    {
        arg_0->sub_794C0(0.1f);
        arg_0->sub_796A0((RtAnimAnimation *)var_10, bp_4, 0, (type_783F0 *)bp_8, 0, 1.0f, 1.0f);
    }
#ifndef CODFH_SP
    else
    {
        sub_19A750("WARNING: No Death face anim loaded for level!\n");
    }
#endif
}

// match: ?sub_17ADF0@@YAXPAUtype_7C8D0@@@Z @ 0x0017ADF0
// sp-match: ?sub_17ADF0@@YAXPAUtype_7C8D0@@@Z @ 0x00112FA0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The hurt face: one of the five hit animations at random (with the same
// warning).
void sub_17ADF0(type_7C8D0 *arg_0)
{
    RwInt32 var_10;
    RwUInt32 var_C;
    RwInt32 bp_8;
    RwUInt32 bp_4;

    var_C = RpRandom() % 5;
    // the hits: the table's entries from 4 (0x42A400)
    bp_4 = sub_16C800((byte_42A370 + 4)[var_C].unk_00, 0x811C9DC5); // not an address: the FNV basis
    if (sub_77B70(bp_4, (void **)(&var_10), (void **)(&bp_8)))
    {
        arg_0->sub_794C0(0.1f);
        arg_0->sub_796A0((RtAnimAnimation *)var_10, bp_4, 0, (type_783F0 *)bp_8, 0, 1.0f, 1.0f);
    }
#ifndef CODFH_SP
    else
    {
        sub_19A750("WARNING: No Death face anim loaded for level!\n");
    }
#endif
}

// match: ?sub_17AE80@type_3DDB98@@QAEXH@Z @ 0x0017AE80
// sp-match: ?sub_17AE80@type_3DDB98@@QAEXH@Z @ 0x00113020
// Takes arg_0 damage: unless already hurt (1) or dying (2), it dies or is
// hurt, through its second animation; with cheat flag 4 it shrinks with
// its health (to a third; as the soldier's sub_13C490).
void type_3DDB98::sub_17AE80(RwInt32 arg_0)
{
    unk_740 -= arg_0;
    if (unk_694 == 2 || unk_694 == 1)
        return;
    if (unk_740 <= 0)
    {
        sub_17AD60(unk_28C);
        unk_694 = 2;
    }
    else
    {
        sub_17ADF0(unk_28C);
        unk_694 = 1;
    }
    if (((type_4B8888 *)dword_4B8888)->unk_00_4)
    {
        unk_690 = (RwReal)unk_740 / unk_744 * 0.67f + 0.33f;
        if (unk_690 < 0.33f)
            unk_690 = 0.33f;
        unk_284->set_unk_28(unk_690);
    }
}

// match: ?vf_064@type_3DDB98@@UAEHPAUtype_75600@@@Z @ 0x0017AF90
// sp-match: ?vf_064@type_3DDB98@@UAEHPAUtype_75600@@@Z @ 0x001130D0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// A bullet (only while its trigger lets bullets hurt it, and not from a
// side its trigger shields it from): its hit-death values (with a
// performance value from the shooter's distance), the damage (all or
// nothing with cheat flags 5 and 2), on a head shot a chance of unk_695 2
// with unk_674 the bullet's direction (scaled by 11 and raised by 6), and
// its scripts told (as the soldier's).
RwInt32 type_3DDB98::vf_064(type_75600 *arg_0)
{
    RwV3d *var_30;
    RwInt32 var_2C;
    RwInt32 lv_28;
    RwV3d var_24;
    type_3D3548 *bp_18;
    type_EC880 *var_14;
    RwReal ebp_10;
    GimpTrigger *qC;
    RwInt32 var8;
    RwInt32 l4;

    if (arg_0)
    {
        qC = (GimpTrigger *)unk_344.unk_08;
        if (!qC->unk_12C)
            return 0;
        l4 = 0;
        if (arg_0->unk_0C)
        {
            bp_18 = arg_0->unk_0C;
            var_14 = (type_EC880 *)dword_4B92D4;
            RwV3dSubMacro(&var_24, sub_CD550(), arg_0->unk_0C->sub_CD550());
            l4 = var_14->sub_EC880((type_EC880_00 *)arg_0, RwV3dLength((RwV3d *)&var_24));
            if (!qC->unk_124 && bp_18->unk_2C_0)
                return 0;
            if (!qC->unk_128 && bp_18->unk_2C_1)
                return 0;
        }
        unk_748[0] = vf_08C(1, 0)[3];
        unk_748[1] = (RwInt8)vf_0AC();
        unk_748[2] = (RwInt8)arg_0->unk_24 > 0 ? (RwInt8)arg_0->unk_24 : 1;
        unk_748[3] = unk_3E0.sub_15F0A0();
        unk_748[4] = l4;
        unk_748[5] = l4;
        for (lv_28 = 0; lv_28 < 6; lv_28++)
            unk_748[lv_28 + 6] = 1;
        ebp_10 = 0.0f;
        if (((type_4B8888 *)dword_4B8888)->unk_00_5)
        {
            ebp_10 = 1000.0f;
        }
        else if (((type_4B8888 *)dword_4B8888)->unk_00_2)
        {
            if (arg_0->unk_24 == 0)
                ebp_10 = 1000.0f;
            else
                ebp_10 = 0.0f;
        }
        else
        {
            ebp_10 = arg_0->unk_28;
        }
        sub_17AE80((RwInt32)ebp_10);
        if (!unk_695 && arg_0->unk_24 == 0 && RpRandom() % 101 > 70 && !unk_698)
        {
            var_2C = 0;
            if (arg_0->unk_04_p)
            {
                var_30 = &arg_0->unk_04_p->unk_10;
                if (RwV3dDotProductMacro(var_30, var_30) > 0.0001f)
                {
                    RwV3dNormalize(&unk_674, var_30);
                    var_2C = 1;
                }
            }
            if (!var_2C)
                set_v3d(&unk_674, 0.0f, 0.0f, 0.0f);
            unk_680 = unk_674;
            RwV3dScaleMacro(&unk_674, &unk_674, 11.0f);
            unk_674.y += 6.0f;
            unk_695 = 2;
        }
        sub_6B5F0("HitByBullet", (type_67620 *)(vf_098()), 0, 0, 0, 0, 1, 0);
        var8 = 0;
        sub_6B5F0("HitByBulletRWS", (type_67620 *)(vf_098()), 0, 0, &var8, 1, 1, 0);
        sub_D2AD0(arg_0->unk_0C, arg_0->unk_04);
    }
    return 0;
}

// match: ?vf_06C@type_3DDB98@@UAEHPAUtype_3D3548@@@Z @ 0x0017B3B0
// sp-match: ?vf_06C@type_3DDB98@@UAEHPAUtype_3D3548@@@Z @ 0x001133C0
// A collision with the entity arg_0: from a type_3DA6C0 whose vf_244 is 1,
// its hit-death values (0x49 or 0x4A by whether it faces the entity), 1000
// damage, and its scripts told as for a bullet (as the soldier's).
RwInt32 type_3DDB98::vf_06C(type_3D3548 *arg_0)
{
    RwReal loc8;
    RwV3d local_14;
    RwV3d *var18;
    RwV3d *var_1C;
    RwInt32 l20;

    if (arg_0->vf_01C() && ((type_3DA6C0 *)arg_0)->vf_244() == 1)
    {
        var18 = sub_CD550();
        var_1C = arg_0->sub_CD550();
        RwV3dSubMacro(&local_14, var_1C, var18);
        RwV3dNormalize(&local_14, &local_14);
        loc8 = RwV3dDotProductMacro(sub_CD5A0(), &local_14);
        unk_748[0] = vf_08C(1, 0)[3];
        unk_748[2] = (RwInt8)(RpRandom() % 9);
        unk_748[3] = unk_3E0.sub_15F0A0();
        if (loc8 > 0.0f)
            unk_748[1] = 0x49;
        else
            unk_748[1] = 0x4A;
        unk_748[4] = 1;
        unk_748[5] = 1;
        for (l20 = 0; l20 < 6; l20++)
            unk_748[l20 + 6] = 1;
        sub_17AE80(1000);
        vf_190(0);
        unk_108 = 0.0f;
        sub_6B5F0("HitByBullet", (type_67620 *)(vf_098()), 0, 0, 0, 0, 1, 0);
    }
    return 0;
}

// match: ?vf_060@type_3DDB98@@UAEHPAUtype_3D3548@@@Z @ 0x0017B580
// sp-match: ?vf_060@type_3DDB98@@UAEHPAUtype_3D3548@@@Z @ 0x00113540
// A touch by the entity arg_0 (none while it rides or is dead: flags 9 and
// 0). A vehicle (kind bits 0x40080) runs it over: its hit-death values,
// 1000 damage and its scripts told as for a bullet. Anything else pushes it
// (or, with flag 19 of unk_28, it pushes them) out of their overlap.
RwInt32 type_3DDB98::vf_060(type_3D3548 *arg_0)
{
#ifndef CODFH_SP // shape: SP 0x113540 declares these in the branches (they share slots)
    RwV3d var_44;
    RwV3d l38;
#endif
    RwReal *lcl_2C;
    RwReal local_28;
    RwReal local_24;
    RwReal *local_20;
    RwInt32 var_1C;
    RwV3d *local_18;
    RwV3d *local_14;
#ifndef CODFH_SP
    RwV3d local_10;
#endif
    RwReal var_4;

    if (unk_28_9 || unk_28_0)
        return 0;
    if ((arg_0->unk_2C & 0x3FFFFF0) & 0x40080) // not an address: entity kind bits
    {
#ifdef CODFH_SP
        RwV3d local_10;
#endif
        local_14 = sub_CD550();
        local_18 = arg_0->sub_CD550();
        RwV3dSubMacro(&local_10, local_18, local_14);
        RwV3dNormalize(&local_10, &local_10);
        var_4 = RwV3dDotProductMacro(sub_CD5A0(), &local_10);
        unk_748[0] = vf_08C(1, 0)[3];
        unk_748[2] = (RwInt8)(RpRandom() % 9);
        unk_748[3] = unk_3E0.sub_15F0A0();
        if (var_4 > 0.0f)
            unk_748[1] = 0x49;
        else
            unk_748[1] = 0x4A;
        unk_748[4] = 1;
        unk_748[5] = 1;
        for (var_1C = 0; var_1C < 6; var_1C++)
            unk_748[var_1C + 6] = 1;
        vf_190(0);
        unk_108 = 0.0f;
        sub_17AE80(1000);
        sub_6B5F0("HitByBullet", (type_67620 *)(vf_098()), 0, 0, 0, 0, 1, 0);
    }
    else
    {
#ifdef CODFH_SP
        RwV3d var_44;
        RwV3d l38;
#endif
        lcl_2C = arg_0->vf_0C4();
        local_20 = vf_0C4();
        RwV3dSubMacro(&var_44, (RwV3d *)lcl_2C, (RwV3d *)local_20);
        var_44.y = 0.0f;
        local_28 = RwV3dLength((RwV3d *)&var_44);
        RwV3dNormalize(&var_44, &var_44);
        local_24 = local_28 - (unk_4C + arg_0->unk_4C) / 1.25f;
        if (local_24 < 0.0f)
        {
            if (var_44.x != 0.0f || var_44.y != 0.0f || var_44.z != 0.0f)
                RwV3dNormalize(&var_44, &var_44);
            if (!unk_28_19)
            {
                RwV3dScaleMacro(&var_44, &var_44, local_24);
                RwV3dAddMacro(&l38, &var_44, (RwV3d *)local_20);
                vf_0C0(&l38);
            }
            else
            {
                RwV3dScaleMacro(&var_44, &var_44, -local_24);
                RwV3dAddMacro(&l38, &var_44, (RwV3d *)lcl_2C);
                arg_0->vf_0C0(&l38);
            }
        }
    }
    return 0;
}

// match: ?vf_068@type_3DDB98@@UAEHPAUtype_758F0@@@Z @ 0x0017B910
// sp-match: ?vf_068@type_3DDB98@@UAEHPAUtype_758F0@@@Z @ 0x00113830
// An explosion that reaches it (while its trigger lets explosions hurt it):
// the damage (falling off to its radius, or by its settings' inner radius;
// 1 returned when out of range), then its hit-death values (with a
// performance value from the distance), and its scripts told where it came
// from and whether from behind (as the soldier's).
RwInt32 type_3DDB98::vf_068(type_758F0 *arg_0)
{
    RwInt32 stk_64;
    type_114F90_50 *var_60;
    RwReal stk_5C;
    RwV3d *local_58;
    RwFrame *local_54;
    RwV3d local_50;
    GimpTrigger *slot_44;
    RwV3d l40;
    RwV3d v34;
    RwMatrix *local_28;
    RwInt32 local_24;
    type_EC880 *local_20;
    RwReal var_1C;
    type_758F0_14 var_18;
    RwInt32 var_4;

    if (arg_0 && arg_0->unk_2C > 0.0f && vf_070(arg_0, 0, 0))
    {
        slot_44 = (GimpTrigger *)unk_344.unk_08;
        if (!slot_44->unk_130)
            return 0;
        RwV3dSubMacro(&v34, &arg_0->unk_0C->pos, sub_CD550());
        var_1C = RwV3dLength((RwV3d *)&v34);
        if (var_1C > arg_0->unk_10)
            return 1;
        if (!arg_0->unk_30)
        {
            stk_5C = var_1C / (arg_0->unk_10);
            sub_17AE80((RwInt32)(stk_5C = (1.0f - stk_5C) * arg_0->unk_2C));
        }
        else
        {
            var_60 = &arg_0->unk_30->unk_50;
            if (var_1C < var_60->unk_18)
            {
                stk_5C = arg_0->unk_2C;
                sub_17AE80((RwInt32)stk_5C);
            }
            else
            {
                stk_5C = (var_1C - var_60->unk_18) / (arg_0->unk_10 - var_60->unk_18);
                sub_17AE80((RwInt32)(stk_5C = (1.0f - stk_5C) * arg_0->unk_2C));
            }
        }
        local_58 = RwMatrixGetPos(arg_0->unk_0C);
        RwV3dSubMacro(&l40, sub_CD550(), local_58);
        local_20 = (type_EC880 *)dword_4B92D4;
        var_4 = local_20->sub_EC970((type_EC880_00 *)arg_0, RwV3dLength((RwV3d *)&l40));
        unk_748[0] = vf_08C(1, 0)[3];
        unk_748[1] = (RwInt8)vf_0AC();
        unk_748[2] = (RwInt8)(RpRandom() % 9);
        unk_748[3] = unk_3E0.sub_15F0A0();
        unk_748[4] = var_4;
        unk_748[5] = var_4;
        for (stk_64 = 0; stk_64 < 6; stk_64++)
            unk_748[stk_64 + 6] = 1;
        local_54 = unk_338.unk_08;
        local_28 = RwFrameGetLTM(local_54);
        local_50 = *RwMatrixGetPos(local_28);
        RwV3dSubMacro(&local_50, &local_50, local_58);
        var_18.unk_00 = local_58->x;
        var_18.unk_04 = local_58->y;
        var_18.unk_08 = local_58->z;
        var_18.unk_0C = arg_0->unk_14;
        var_18.unk_10 = RwV3dDotProductMacro(&local_28->at, &local_50) <= 0 ? 1 : 0;
        sub_6B5F0("HitByExplosion", (type_67620 *)(vf_098()), 0, 0, (RwInt32 *)(&var_18), 5, 1, 0);
        local_24 = 0;
        sub_6B5F0("HitByExplosionRWS", (type_67620 *)(vf_098()), 0, 0, &local_24, 1, 1, 0);
        sub_D2AD0(arg_0->unk_04.sub_D4910(), arg_0->unk_08);
    }
    return 0;
}

// match: ?vf_0E4@type_3DDB98@@UAEHH@Z @ 0x0017BCF0
// sp-match: ?vf_0E4@type_3DDB98@@UAEHH@Z @ 0x00113B00
// Its trigger's scene value arg_0.
RwInt32 type_3DDB98::vf_0E4(RwInt32 arg_0)
{
    type_712B0 *var_4;

    var_4 = get_unk_34C();
    return ((GimpTrigger *)var_4)->unk_106[arg_0];
}

// match: ?vf_0EC@type_3DDB98@@UAEXHH@Z @ 0x0017BD20
// sp-match: ?vf_0EC@type_3DDB98@@UAEXHH@Z @ 0x00113B20
// Sets its scene value arg_0 to arg_4 ("SetSceneValue").
void type_3DDB98::vf_0EC(RwInt32 arg_0, RwInt32 arg_4)
{
    unk_6A8[arg_0] = (RwInt16)arg_4;
}

// match: ?vf_0E8@type_3DDB98@@UAEHXZ @ 0x0017BD40
// sp-match: ?vf_0E8@type_3DDB98@@UAEHXZ @ 0x00113B40
// How many scene values its trigger sets.
RwInt32 type_3DDB98::vf_0E8()
{
    type_712B0 *var_8;
    RwInt32 l4;

    var_8 = get_unk_34C();
    for (l4 = 0; l4 < 5; l4++)
    {
        if (((GimpTrigger *)var_8)->unk_106[l4] == -1)
        {
            break;
        }
    }
    return l4;
}

// match: ?vf_078@type_3DDB98@@UAEXXZ @ 0x0017BDA0
// sp-match: ?vf_078@type_3DDB98@@UAEXXZ @ 0x00113B60
void type_3DDB98::vf_078()
{
    sub_8D580(unk_284->get_unk_18(), 1);
}

// match: ?sub_17BDD0@type_3DDB98@@QAEXPAUtype_15CCE0@@HH@Z @ 0x0017BDD0
// sp-match: ?sub_17BDD0@type_3DDB98@@QAEXPAUtype_15CCE0@@HH@Z @ 0x00113B80
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Puts the weapon arg_0's model in its hand: at the bone arg_4 while its
// animation drives it, else at its frame; then the weapon's state arg_8
// (as the soldier's sub_138760).
void type_3DDB98::sub_17BDD0(type_15CCE0 *arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    RpClump *var_1C;
    RwFrame *var_18;
    RwInt32 var_14;
    RwMatrix *lv_10;
    RwFrame *var_C;
    RwMatrix *bp_8;
    RwMatrix *bp_4;

    if (unk_28_13)
    {
        lv_10 = RpHAnimHierarchyGetMatrixArray(unk_284->get_unk_18());
        var_14 = RpHAnimIDGetIndex(unk_284->get_unk_18(), arg_4);
        bp_4 = &lv_10[var_14];
    }
    else
    {
        var_1C = unk_25C.unk_08;
    var_18 = RpClumpGetFrame(var_1C);
        bp_4 = RwFrameGetLTM(var_18);
    }
    var_C = RpClumpGetFrame(arg_0->get_unk_18());
    bp_8 = RwFrameGetMatrix(var_C);
    RwMatrixTransform(bp_8, bp_4, rwCOMBINEREPLACE);
    RwFrameUpdateObjects(var_C);
    arg_0->sub_15D600((RwReal)arg_8);
}

// match: ?vf_0F8@type_3DDB98@@UAEXM@Z @ 0x0017BEB0
// sp-match: ?vf_0F8@type_3DDB98@@UAEXM@Z @ 0x00113C00
// Moves it to the point arg_0 of the way along its spline path.
void type_3DDB98::vf_0F8(RwReal arg_0)
{
    RwV3d var_C;

    unk_6E4 = arg_0;
    if (unk_734)
    {
        unk_734->sub_BA990(unk_6E4, &var_C, &unk_6F0);
        vf_0C0(&var_C);
    }
}

// match: ?sub_17BF10@type_3DDB98@@QAEXPAURwV3d@@@Z @ 0x0017BF10
// sp-match: ?sub_17BF10@type_3DDB98@@QAEXPAURwV3d@@@Z @ 0x00113C50
void type_3DDB98::sub_17BF10(RwV3d *arg_0)
{
    unk_778 = *arg_0;
}

// match: ?vf_08C@type_3DDB98@@UAEPAEHH@Z @ 0x0017BF40
// sp-match: ?vf_08C@type_3DDB98@@UAEPAEHH@Z @ 0x00113C70
// Its performance values (arg_4 1: the special idle ones), or for arg_0 set
// those of its performance kind.
RwUInt8 *type_3DDB98::vf_08C(RwInt32 arg_0, RwInt32 arg_4)
{
    RwInt32 var_4;

    var_4 = arg_0 ? unk_6B0 : arg_4;
    switch (var_4)
    {
    case 1:
        return unk_6C0;
    default:
        return unk_6B4;
    }
}

// match: ?sub_17BF90@type_3DDB98@@QAEXPAURwV3d@@M@Z @ 0x0017BF90
// sp-match: ?sub_17BF90@type_3DDB98@@QAEXPAURwV3d@@M@Z @ 0x00113CA0
// "SendFlying": unless it flies already, it flies (unk_73C 1, gravity on)
// away from the point *arg_0, launched at an angle and a speed from the
// strength arg_4 (at least 200) and the distance, in its own frame (as the
// soldier's sub_13DF40).
void type_3DDB98::sub_17BF90(RwV3d *arg_0, RwReal arg_4)
{
    RwV3d *var_8;
    RwV3d var_14;
    RwReal var_18;
    RwReal var_1C;
    RwReal var_20;
    RwReal var_24;
    RwReal var_2C;
    RwReal var_30;
    RwReal var_34;
    RwFrame *var_38;
    RwMatrix var_80;

    if (unk_73C == 1)
        return;
    if (unk_28_2)
        unk_30 |= 0x40;
    else
        unk_30 = 0x40;
    unk_73C = 1;
    vf_18C(1);
    unk_28_5 = 1;
    unk_28_4 = 1;
    unk_28_1 = 0;
    if (arg_4 != 0.0f)
    {
        if (arg_4 < flt_429CA4)
            arg_4 = flt_429CA4;
        var_8 = sub_CD550();
        RwV3dSubMacro(&var_14, var_8, arg_0);
        var_18 = RwV3dLength((RwV3d *)&var_14);
        var_14.y = 0.0f;
        var_1C = RwV3dLength((RwV3d *)&var_14);
        if (var_1C > 0.001f)
        {
#ifdef CODFH_SP // shape: SP 0x113CA0
            var_20 = (arg_4 * flt_429C9C - var_1C) / arg_4;
            var_20 = var_20 * (flt_429CA0 / flt_429C9C);
#else
            var_20 = (arg_4 * flt_429C9C - var_1C) / arg_4 * (flt_429CA0 / flt_429C9C);
#endif
            var_24 = flt_429C98 + var_20;
            var_2C = tan(var_24 * rwPI / 180.0f);
            var_30 = var_2C * var_1C;
            var_14.y = var_30;
            RwV3dNormalize(&var_14, &var_14);
        }
        else
        {
            var_14.x = var_14.z = 0.0f;
            var_14.y = 1.0f;
        }
        if (arg_4 <= 450.0f)
            var_34 = (arg_4 - flt_429CA4 * flt_429CB4) * flt_429CAC
                     + (arg_4 - var_18) * flt_429CB0;
        else
            var_34 = (arg_4 - flt_429CA4 * flt_429CB4) * flt_429CB8
                     + (arg_4 - var_18) * flt_429CB0;
        RwV3dScaleMacro(&var_14, &var_14, var_34);
        var_38 = unk_338.unk_08;
        RwMatrixInvert(&var_80, RwFrameGetLTM(var_38));
        sub_141320(&var_14, &var_14, &var_80);
        sub_D04D0(&var_14);
        set_v3d(&unk_10C, 0.0f, 0.0f, 0.0f);
    }
    unk_130 = 1;
}

// match: ?vf_1C4@type_3DDB98@@UAEXH@Z @ 0x0017C260
// sp-match: ?vf_1C4@type_3DDB98@@UAEXH@Z @ 0x00113E90
// Landing from a flight (unk_73C): on the ground (arg_0) it stops, or
// against a wall it drops; its scripts are told (as the soldier's).
void type_3DDB98::vf_1C4(RwInt32 arg_0)
{
    if (!unk_73C)
    {
        return;
    }
    if (arg_0)
    {
        unk_130 = 0;
        set_v3d(&unk_10C, -1.0f, -1.0f, -1.0f);
        unk_73C = 0;
        sub_6B5F0("HitGround", (type_67620 *)(vf_098()), 0, 0, 0, 0, 1, 0);
    }
    else if (unk_73C == 1)
    {
        set_v3d(&unk_10C, -1.0f, 0.0f, -1.0f);
        unk_DC = 0.0f;
        unk_73C = 2;
        sub_6B5F0("HitWall", (type_67620 *)(vf_098()), 0, 0, 0, 0, 1, 0);
    }
}

// match: ?vf_210@type_3DDB98@@UAEXPAUtype_D05C0@@@Z @ 0x0017C370
// sp-match: ?vf_210@type_3DDB98@@UAEXPAUtype_D05C0@@@Z @ 0x00113F40
// Raises the step (a quarter of it while flying) with flags 3 and 5 set
// and 7 clear.
void type_3DDB98::vf_210(type_D05C0 *arg_0)
{
    if (unk_28_3 && unk_28_5 && !unk_28_7)
    {
        if (unk_73C == 1)
            arg_0->unk_00.y += flt_429C88 * arg_0->unk_48;
        else
            arg_0->unk_00.y += arg_0->unk_48;
    }
}

// type_3DDB98's vf_0BC: type_3DAFC8's code (ICF folded them, at 0x13C120).
// sp-match: ?vf_0BC@type_3DDB98@@UAEHXZ @ 0x00112CA0
RwInt32 type_3DDB98::vf_0BC()
{
    switch (vf_0AC())
    {
    case 7:
    case 9:
    case 10:
    case 13:
    case 16:
    case 18:
    case 19:
    case 20:
    case 41:
    case 42:
    case 47:
    case 50:
    case 54:
    case 57:
    case 59:
    case 63:
    case 68:
        return 1;
    case 8:
    case 21:
    case 43:
    case 51:
    case 64:
    case 66:
    case 67:
    case 69:
    case 71:
    case 72:
        return 2;
    default:
        return 0;
    }
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??2type_3DDB98@@SAPAXIPAX@Z (folded into 0x6CCF0)
void *type_3DDB98::operator new(RwUInt32 arg_0, void *arg_4)
{
    return arg_4;
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??3type_3DDB98@@SAXPAX@Z (folded into 0x19A750)
// Single player's deleting destructor (SP 0x1152E0) calls it out of line: the
// empty body here would let /O2 drop that call, so SP only declares it.
#ifndef CODFH_SP
void type_3DDB98::operator delete(void * arg_0)
{
}
#endif

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??3type_3DDB98@@SAXPAX0@Z (folded into 0x19A750)
void type_3DDB98::operator delete(void * arg_0, void * arg_4)
{
}
