// Split from unit_1340D0.cpp at 0x134B40, where the image starts another object (the
// soldier, type_3DAFC8): its factory first, then the constructor's out-of-line copy it
// needs (sub_134C50) with the vtable's inline functions; its .rdata begins at 0x3DAEC0 with
// its own constants (the frame time, three axes, two offset tables, 0.0) before its
// vtable (PLAN M7).

#ifdef CODFH_SP // shape: AIData declared first (before the RenderWare headers): only then does
                // type_3DAFC8::vf_1CC (SP 0xE6A40) load [esp+0x48] before [esp+0x38] after
                // RwFrameUpdateObjects as the image does
#include "types/AIData.h"
#endif
#include <math.h>
#include "rw/ostypes.h"
#include "rw/bavector.h"
#include "rw/bamatrix.h"
#include "rw/rtquat.h"
#include "game/frand.h"
#include "types/type_3DA6C0.h"
#include "types/type_3D94B8.h"
#include "types/type_8A980.h"
#include "types/CGlobalSounds.h"
#include "types/type_1227C0.h"
#include "types/type_92430.h"
#include "game/decals.h"
#include "types/animkey.h"
#include "types/type_FC6F0.h"
#include "rw/rphanim.h"
#include "game/functions.h"
#include "game/data.h"
#include "types/type_3D3548.h"
#include "types/type_3DAFC8.h"
#include "types/animkey.h"
#include "types/animobjpool.h"
#include "types/type_4B85F8.h"
#include "types/type_3D32F8.h"
#include "types/type_44350.h"
#include "types/SoldierTrigger.h"
#include "types/type_3DF8D8.h"
#include "types/type_3D2E7C.h"
#include "types/type_3C540.h"
#include "types/alfaobject.h"
#include "types/ccess.h"
#include "types/animbank.h"
#include "types/soundbank.h"
#include "types/type_154C0_80.h"
#include "types/type_10F710.h"
#include "rw/baframe.h"
#include "rw/rpworld.h"
#include "rw/rphanim.h"
#include "rw/rprandom.h"
#include "rw/rpatomic.h"
#include "game/clumpdata.h"
#include <string.h>
#include <stdio.h>
#include "game/vecutil.h"
#include "rws/skinhelper.h"
#include "types/type_3D51C0.h"
#include <xmmintrin.h>
#include "types/type_3D5658.h"
#include "types/vec4.h"
#include "game/pathnodes.h"
#include "game/startup.h"
#include "rw/rtquat.h"
#include "types/type_3DC048.h"
#include "types/type_3DBC78.h"
#ifdef CODFH_DRAW_TRIGGERS
// (port/src/debug/trigdraw.cpp: the debug tools' hit view)
void TrigDrawDamageTaken(void *pEntity, RwReal fAmount);
#endif

// match: __ehhandler$?sub_134B40@@YAPAUtype_3D3548@@PAU1@@Z>1>8 @ 0x0041DAC8
// match: __ehhandler$?sub_134B40@@YAPAUtype_3D3548@@PAU1@@Z>1 @ 0x0041DAD0
// match: __ehhandler$??0type_3DAFC8@@QAE@PAVSoldierTrigger@@@Z>1>8 @ 0x0041DAEC
// match: __ehhandler$??0type_3DAFC8@@QAE@PAVSoldierTrigger@@@Z>1 @ 0x0041DB34
// match: __ehhandler$??1type_3DAFC8@@UAE@XZ>1>8 @ 0x0041DB50
// match: __ehhandler$??1type_3DAFC8@@UAE@XZ>1 @ 0x0041DBA8
// match: __ehhandler$??0type_3DAFC8@@QAE@PAVSoldierTrigger@@@Z-0x78 @ 0x00301880
// match: __ehhandler$??0type_3DAFC8@@QAE@PAVSoldierTrigger@@@Z @ 0x003018F8
// match: __ehhandler$??1type_3DAFC8@@UAE@XZ-0x88 @ 0x00301910
// match: __ehhandler$??1type_3DAFC8@@UAE@XZ @ 0x00301998
// match: ??0type_3DAFC8@@QAE@PAVSoldierTrigger@@@Z @ 0x00134C50
// match: ?vf_094@type_3DAFC8@@UAEXI@Z @ 0x00134D90
// match: ?vf_0A4@type_3DAFC8@@UAEXH@Z @ 0x00134DB0
// match: ?vf_0A8@type_3DAFC8@@UAEHXZ @ 0x00134DD0
// match: ?vf_088@type_3DAFC8@@UAEXH@Z @ 0x00134DF0
// match: ?vf_09C@type_3DAFC8@@UAEHXZ @ 0x00134E10
// match: ?vf_0A0@type_3DAFC8@@UAEXI@Z @ 0x00134E30
// match: ?vf_0AC@type_3DAFC8@@UAEHXZ @ 0x00134E50
// match: ?vf_0B4@type_3DAFC8@@UAEXXZ @ 0x00134E70
// match: ?vf_0B8@type_3DAFC8@@UAEXH@Z @ 0x00134E90
// match: ?vf_0E0@type_3DAFC8@@UAEPAEXZ @ 0x00134EB0
// match: ?vf_0F0@type_3DAFC8@@UAEPACXZ @ 0x00134ED0
// match: ?vf_1AC@type_3DAFC8@@UAEXH@Z @ 0x00134EF0
// match: ?vf_234@type_3DAFC8@@UAEMXZ @ 0x00134F20
// match: ?vf_238@type_3DAFC8@@UAEXM@Z @ 0x00134F40
// match: ?vf_23C@type_3DAFC8@@UAEHXZ @ 0x00134F60
// match: ?vf_240@type_3DAFC8@@UAEXH@Z @ 0x00134F80
// match: ?vf_138@type_3DAFC8@@UAEHXZ @ 0x00134FA0
// match: ?vf_174@type_3DAFC8@@UAEHXZ @ 0x00134FC0
// match: ?vf_178@type_3DAFC8@@UAEXH@Z @ 0x00134FE0
// match: ?vf_180@type_3DAFC8@@UAEXH@Z @ 0x00135000
// match: ?vf_254@type_3DAFC8@@UAEHXZ @ 0x00135050
// match: ?vf_258@type_3DAFC8@@UAEHXZ @ 0x00135090
// match: ?vf_25C@type_3DAFC8@@UAEXH@Z @ 0x001350B0
// match: ?vf_118@type_3DAFC8@@UAEPAUtype_3D3548@@XZ @ 0x001350D0
// match: ?vf_11C@type_3DAFC8@@UAEXPAUtype_3D3548@@@Z @ 0x001350F0
// match: ?vf_120@type_3DAFC8@@UAEPAUAIData@@XZ @ 0x00135110
// match: ?vf_17C@type_3DAFC8@@UAEMXZ @ 0x00135130
// match: ?vf_260@type_3DAFC8@@UAEXM@Z @ 0x00135150
// match: ?vf_144@type_3DAFC8@@UAEMXZ @ 0x00135180
// match: ?vf_148@type_3DAFC8@@UAEMXZ @ 0x001351A0
// match: ?vf_14C@type_3DAFC8@@UAEMXZ @ 0x001351C0
// match: ?vf_150@type_3DAFC8@@UAEMXZ @ 0x001351E0
// match: ?vf_154@type_3DAFC8@@UAEMXZ @ 0x00135200
// match: ?vf_158@type_3DAFC8@@UAEMXZ @ 0x00135220
// match: ?vf_15C@type_3DAFC8@@UAEHXZ @ 0x00135240
// match: ?vf_13C@type_3DAFC8@@UAEHXZ @ 0x00135260
// match: ?vf_140@type_3DAFC8@@UAEXXZ @ 0x00135280
// match: ?vf_1F4@type_3DAFC8@@UAEMXZ @ 0x001352A0
// match: ?vf_1C8@type_3DAFC8@@UAEPAUtype_3DAFC8_1DDC@@XZ @ 0x001352C0
// match: ??_Gtype_3DAFC8@@UAEPAXI@Z @ 0x001352E0
// match: ??1type_3DAFC8@@UAE@XZ @ 0x00135310
// match: _v3d_3DAEC4 @ 0x003DAEC4
// match: _v3d_3DAED0 @ 0x003DAED0
// match: _v3d_3DAEDC @ 0x003DAEDC
// match: ??_7type_3DAFC8@@6B@ @ 0x003DAFC8
// match: ??_C@_0BB@HJJEEAKD@SetDeletionDelay?$AA@ @ 0x003DB22C
// match: ??_C@_0HC@LCBEGBKL@?$CK?$CK?$CKERROR?3?5Cannot?5create?5soldier?5@ @ 0x003DB240
// match: ??_C@_0CO@IPCLHAFO@WARNING?3?5No?5idle?5face?5anim?5loade@ @ 0x003DB2B4
// match: ??_C@_0BD@GHFPEOE@FA_QO1A2K_IdleMask?$AA@ @ 0x003DB2E4
// match: ??_C@_0CD@FHBOBJAN@?$CF2d?5?$CF4d?5?$HL?5?$CF9?46f?0?5?$CF9?46f?0?5?$CF9?46f?5?$HN?0@ @ 0x003DB2F8
// match: __real@3f866666 @ 0x003DB31C
// match: ??_C@_0BI@MIIOHCDD@SoldierEntity?3?3HeadMesh?$AA@ @ 0x003DB320
// match: ??_C@_0BI@CBBANKIH@SoldierEntity?3?3BodyMesh?$AA@ @ 0x003DB338
// match: ??_C@_0BM@OHMOLHJL@SoldierEntity?3?3CharacterDef?$AA@ @ 0x003DB350
// match: __real@c2f00000 @ 0x003DB36C
// match: __real@3fe6666666666666 @ 0x003DB370
// match: __real@bf7ffffa @ 0x003DB378
// match: ??_C@_0BF@JPEPHFII@ContinuedSuppression?$AA@ @ 0x003DB37C
// match: ??_C@_0BB@JGNNPLEC@StartSuppression?$AA@ @ 0x003DB394
// match: __real@3ea8f5c3 @ 0x003DB3A8
// match: __real@3f2b851f @ 0x003DB3AC
// match: __real@41300000 @ 0x003DB3B0
// sp-match: ?vf_0A4@type_3DAFC8@@UAEXH@Z @ 0x000EBE10
// sp-match: ?vf_0A8@type_3DAFC8@@UAEHXZ @ 0x000EBE20
// sp-match: ?vf_0F0@type_3DAFC8@@UAEPACXZ @ 0x000EBEA0
// sp-match: ?vf_1AC@type_3DAFC8@@UAEXH@Z @ 0x000EBEB0
// sp-match: ?vf_138@type_3DAFC8@@UAEHXZ @ 0x000EBF10
// sp-match: ?vf_174@type_3DAFC8@@UAEHXZ @ 0x000EBF20
// sp-match: ?vf_178@type_3DAFC8@@UAEXH@Z @ 0x000EBF30
// sp-match: ?vf_180@type_3DAFC8@@UAEXH@Z @ 0x000EBF40
// sp-match: ?vf_254@type_3DAFC8@@UAEHXZ @ 0x000EBF70
// sp-match: ?vf_258@type_3DAFC8@@UAEHXZ @ 0x000EBF90
// sp-match: ?vf_25C@type_3DAFC8@@UAEXH@Z @ 0x000EBFA0
// sp-match: ?vf_118@type_3DAFC8@@UAEPAUtype_3D3548@@XZ @ 0x000EBFB0
// sp-match: ?vf_11C@type_3DAFC8@@UAEXPAUtype_3D3548@@@Z @ 0x000EBFC0
// sp-match: ?vf_120@type_3DAFC8@@UAEPAUAIData@@XZ @ 0x000EBFD0
// sp-match: ?vf_17C@type_3DAFC8@@UAEMXZ @ 0x000EBFE0
// sp-match: ?vf_260@type_3DAFC8@@UAEXM@Z @ 0x000EBFF0
// sp-match: ?vf_13C@type_3DAFC8@@UAEHXZ @ 0x000EC090
// sp-match: ?vf_140@type_3DAFC8@@UAEXXZ @ 0x000EC0A0
// sp-match: ?vf_1C8@type_3DAFC8@@UAEPAUtype_3DAFC8_1DDC@@XZ @ 0x000EC110
// sp-match: ??_Gtype_3DAFC8@@UAEPAXI@Z @ 0x000EC120
// sp-match: ??0type_3DAFC8@@QAE@PAVSoldierTrigger@@@Z @ 0x000EBD40
// sp-match: ?vf_094@type_3DAFC8@@UAEXI@Z @ 0x000EBE00
// sp-match: ?vf_088@type_3DAFC8@@UAEXH@Z @ 0x000EBE30
// sp-match: ?vf_09C@type_3DAFC8@@UAEHXZ @ 0x000EBE40
// sp-match: ?vf_0A0@type_3DAFC8@@UAEXI@Z @ 0x000EBE50
// sp-match: ?vf_0AC@type_3DAFC8@@UAEHXZ @ 0x000EBE60
// sp-match: ?vf_0B4@type_3DAFC8@@UAEXXZ @ 0x000EBE70
// sp-match: ?vf_0B8@type_3DAFC8@@UAEXH@Z @ 0x000EBE80
// sp-match: ?vf_0E0@type_3DAFC8@@UAEPAEXZ @ 0x000EBE90
// sp-match: ?vf_234@type_3DAFC8@@UAEMXZ @ 0x000EBED0
// sp-match: ?vf_23C@type_3DAFC8@@UAEHXZ @ 0x000EBEF0
// sp-match: ??1type_3DAFC8@@UAE@XZ @ 0x000EC140
// sp-match: ?vf_238@type_3DAFC8@@UAEXM@Z @ 0x000EBEE0
// sp-match: ?vf_240@type_3DAFC8@@UAEXH@Z @ 0x000EBF00
// sp-match: ?vf_1F4@type_3DAFC8@@UAEMXZ @ 0x000EC100
// sp-match: ?vf_144@type_3DAFC8@@UAEMXZ @ 0x000EC010
// sp-match: ?vf_148@type_3DAFC8@@UAEMXZ @ 0x000EC020
// sp-match: ?vf_14C@type_3DAFC8@@UAEMXZ @ 0x000EC030
// sp-match: ?vf_150@type_3DAFC8@@UAEMXZ @ 0x000EC040
// sp-match: ?vf_154@type_3DAFC8@@UAEMXZ @ 0x000EC050
// sp-match: ?vf_158@type_3DAFC8@@UAEMXZ @ 0x000EC060
// sp-match: ?vf_15C@type_3DAFC8@@UAEHXZ @ 0x000EC070


// match: ?sub_134B40@@YAPAUtype_3D3548@@PAU1@@Z @ 0x00134B40
// match: __ehhandler$?sub_134B40@@YAPAUtype_3D3548@@PAU1@@Z-0x11 @ 0x00301860
// match: __ehhandler$?sub_134B40@@YAPAUtype_3D3548@@PAU1@@Z @ 0x00301871
// sp-match: ?sub_134B40@@YAPAUtype_3D3548@@PAU1@@Z @ 0x000EC200
// Spawns the soldier of the trigger arg_0 in entity memory, or warns that
// there is none for it.
type_3D3548 *sub_134B40(type_3D3548 *arg_0)
{
    type_3DAFC8 *var_10;

    var_10 = (type_3DAFC8 *)sub_D56D0(0x2170, ((SoldierTrigger *)arg_0)->unk_24_18,
                                      ((SoldierTrigger *)arg_0)->vf_008());
    if (var_10 != 0)
    {
        var_10 = new (var_10) type_3DAFC8((SoldierTrigger *)arg_0);
        if (var_10->unk_28 & 0x400000) // not an address: entity flag
        {
            sub_D5A60(var_10, 0);
            var_10 = 0;
        }
    }
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS) // MP only: single player has no warning (SP 0xEC200)
    else
    {
        sub_19A750("WARNING: A spawn could not be created due to lack of entity memory. Trigger "
                   "location(%6.2f,%6.2f,%6.2f)",
                   ((SoldierTrigger *)arg_0)->unk_90, ((SoldierTrigger *)arg_0)->unk_94,
                   ((SoldierTrigger *)arg_0)->unk_98);
    }
#endif
    return var_10;
}
extern type_7CBD0_t flt_428A50[];
extern RwInt32 dword_42A050[];
extern type_42A1C8 dword_42A1C8[];
extern RwUInt32 dword_42A36C;
extern type_42A0B8 dword_42A0B8[];
extern RwUInt32 dword_42A1C0;
extern RwReal dword_429C3C;
// match: ?sub_135430@type_3DAFC8@@QAEHPAVSoldierTrigger@@@Z @ 0x00135430
// sp-match: ?sub_135430@type_3DAFC8@@QAEHPAVSoldierTrigger@@@Z @ 0x000E9B00
// Its set-up from its trigger arg_0: its trigger's object points at it, its
// name, the base's set-up, its flags, fields and timers; its definition's
// body and head (without all three it is left inert, flagged 0x400000, and
// 0 returned), side by weapon class, render parts, its two animations and
// their scales (fixed per definition, or random, or smaller with cheat bit
// 6), its hat tag, its second animation's rest translations from the
// skin, its idle face animation, its AI object and script; with the
// trigger's mode 5 it starts at cover (else, unless the trigger allows it,
// it is left inert with a warning, and 0 returned); its search, its weapon
// and grenade, its sounds, its spline, and its deletion delay. Returns 1.
RwInt32 type_3DAFC8::sub_135430(SoldierTrigger *arg_0)
{
    SoldierTrigger *var_C;
    type_3DFEEC *var_10;
    RwUInt32 var_24;
    type_1917A0 *var_28;
    type_1908A0 *var_2C;
    type_1908A0 *var_30;
    type_3DF8D8 *var_34;
    RwInt32 var_38;
    RwUInt32 var_68;
    type_7C8D0 *var_6C;
    RpHAnimHierarchy *var_74;
    RwUInt32 var_78;
    type_7C8D0 *var_7C;
    RwInt32 var_88;
    type_3DF8D8_04 *var_8C;
    bool var_BD;
    type_3DF8D8_04 *var_C4;
    type_3DF8D8 *var_C8;
    type_EC1F0 *var_D0;
    RpSkin *var_D8;
    const RwMatrix *var_DC;
    RwInt32 var_E0;
    type_140490 var_100;
    RwInt32 var_104;
    RwInt32 var_108;
    RwChar var_150[0x40];
    RwUInt32 var_154;
    RwInt32 var_158;
    RwInt32 var_15C;
    RwInt32 var_160;
    type_3DF8D8 *var_164;
    RwUInt32 var_168;
    type_3D2E7C *var_16C;
    type_3DF8D8 *var_174;
    type_3D2CD0 *var_17C;
    type_3D2E7C *var_184;
    RwV3d *var_18C;
    RwChar var_390[0x200];
    RwInt32 var_394;
    type_3DF8D8 *var_39C;
    type_3DFEEC *var_3A0;
    SplinePath *var_3A4;
    RwInt32 var_3A8;

    var_C = arg_0;
    if (var_C->unk_D0.unk_00)
    {
        var_10 = (type_3DFEEC *)sub_198800(&var_C->unk_D0);
        ((type_D48D0 *)&var_10->unk_24_id)->sub_D48D0(this);
        var_10->unk_10 = 6;
    }
    strcpy(unk_62C, var_C->unk_174);
    unk_64C = 1;
    unk_2164 = 1;
    unk_88 &= ~0x2000;
    unk_600 = 0;
    sub_CCCD0((type_712B0 *)arg_0);
    unk_88_10 = arg_0->unk_24_20;
    unk_28 = 0x183C;
    if (var_C->unk_160)
        unk_28 |= 0x80000; // not an address: a flag
    unk_1D44 = 0;
    unk_848 = 0;
    set_xyz(&unk_10C, -1.0f, 0.0f, -1.0f);
    set_xyz(&unk_134, -1.0f, -1.0f, -1.0f);
    zero_v3d(&unk_118);
    set_xyz(&unk_124, 1000.0f, 1000.0f, 1000.0f);
#ifdef CODFH_SP // shape: single player stores unk_108 first (SP 0xE9B00)
    unk_108 = dword_429C3C;
    unk_130 = 0;
    unk_1D28 = 0;
#else
    unk_130 = 0;
    unk_1D28 = 0;
    unk_108 = dword_429C3C;
#endif
    for (var_24 = 0; var_24 < 4; var_24++)
    {
        unk_2144[var_24].unk_00 = 1.0f;
        unk_2144[var_24].unk_04 = 0.0f;
    }
    unk_1D20 = var_C->unk_140;
    unk_1D24 = unk_1D20;
    unk_1D48 = 0;
    unk_86C = var_C->unk_104;
    unk_870 = var_C->unk_108;
    unk_874 = 0;
    unk_878 = var_C->unk_10C;
    unk_87C = var_C->unk_110;
    unk_880 = 1.0f;
    unk_884 = var_C->unk_114;
    unk_888 = var_C->unk_118;
    unk_88C = var_C->unk_144;
    unk_890 = var_C->unk_148;
    unk_1D34 = 0;
    unk_1D2C = 0.0f;
    unk_1D30 = 0.0f;
    unk_824 = 0;
    unk_1D4C = 0;
    unk_1D4E = 0;
    unk_1D64.z = 0.0f;
    unk_1D64.y = 0.0f;
    unk_1D64.x = 0.0f;
    unk_1DC4 = 0;
    unk_1DD4 = 0.0f;
    unk_1DD8 = 0.0f;
    unk_1DC8.z = 0.0f;
    unk_1DC8.y = 0.0f;
    unk_1DC8.x = 0.0f;
    unk_1DC0 = 0.0f;
    for (var_24 = 0; var_24 < 5; var_24++)
    {
        unk_1D50[var_24] = 0.0f;
        unk_1D70[var_24].z = 0.0f;
        unk_1D70[var_24].y = 0.0f;
        unk_1D70[var_24].x = 0.0f;
        unk_1DAC[var_24] = 0.0f;
    }
    unk_2140 = 0;
    unk_58 = 1;
    unk_620 = 0;
    unk_624.sub_D48D0(0);
    unk_628 = 0;
    unk_61C = 0;
    unk_5E0 = 0;
    unk_5F8 = 0;
    unk_5FC = -1.0f;
    unk_5E4 = 0.0f;
    unk_5E8 = 0xFF;
    unk_614.sub_D48D0(0);
    unk_810 = -1;
    unk_814 = 0;
    memset(&unk_1DDC, 0, sizeof(unk_1DDC));
    unk_28 |= 0x100000; // not an address: a flag
    unk_804 = 0;
    unk_894 = 0.0f;
    var_28 = 0;
    var_2C = 0;
    var_30 = 0;
    var_34 = sub_198800(&var_C->unk_D8);
    if (var_34 && var_34->vf_008() == 4)
    {
        var_28 = (type_1917A0 *)var_34;
        var_2C = var_28->sub_1917A0();
        var_30 = var_28->sub_1917F0();
    }
    if (!var_28 || !var_2C || !var_30)
    {
        if (!var_28)
            sub_D3FB0("SoldierEntity::CharacterDef", arg_0, &var_C->unk_D8);
        if (!var_2C)
            sub_D3FB0("SoldierEntity::BodyMesh", arg_0, &var_C->unk_D8);
        if (!var_30)
            sub_D3FB0("SoldierEntity::HeadMesh", arg_0, &var_C->unk_D8);
        unk_808 = 0;
        unk_800 = 1.0f;
        unk_7FC = 1.0f;
        unk_840 = 0;
        unk_844 = 0;
        unk_28 |= 0x400000; // not an address: a flag
        return 0;
    }
    var_38 = var_28->unk_44;
    switch (var_38)
    {
    case 1:
        unk_2C = 0x21;
        unk_30 = 0x27BFF7; // not an address: collision flags
        break;
    case 0:
        unk_2C = 0x22;
        unk_30 = 0x27BFF7; // not an address: collision flags
        break;
    case 3:
        unk_2C = 0x29;
        unk_30 = 0x27BFF7; // not an address: collision flags
        break;
    case 2:
        unk_2C = 0x2A;
        unk_30 = 0x27BFF7; // not an address: collision flags
        break;
    case 4:
        unk_2C = 0x22;
        unk_30 = 0x27BFF7; // not an address: collision flags
        break;
    }
    unk_34 = 0x600B0; // not an address: entity kind bits
    vf_224(var_2C, 0, 0);
    sub_16E080(get_unk_264(), var_28->get_unk_34());
    sub_13ACE0(var_28->sub_18F830((type_1917A0_10 *)&var_28->unk_10));
    sub_16E080(unk_828.get_unk_08(), var_28->sub_1917F0()->get_unk_54());
    sub_13ADA0(var_28->sub_18F830(&var_28->unk_28));
    if (var_28->sub_191840())
        sub_16E080(unk_834.get_unk_08(), var_28->sub_191840()->get_unk_54());
    sub_16D9A0(get_unk_264());
    unk_48 = 90.0f;
    unk_4C = 50.0f;
    unk_50_r = 33.0f;
    zero_v3d(&unk_3C_v);
    unk_40 = 90.0f;
    var_68 = sub_78830(2);
    unk_280 = var_68;
    var_6C = (type_7C8D0 *)sub_78AC0(unk_280);
    unk_284 = var_6C;
    var_74 = sub_16D970(get_unk_264());
    var_6C->sub_79470(var_74);
    var_6C->unk_1C = (RwInt32)this;
    var_78 = sub_78830(0);
    unk_288 = var_78;
    var_7C = (type_7C8D0 *)sub_78AC0(unk_288);
    unk_28C = var_7C;
    var_74 = sub_16D970(unk_828.get_unk_08());
    var_7C->sub_79470(var_74);
    var_7C->unk_1C = (RwInt32)this;
    var_7C->set_unk_12(var_7C->unk_12 | 2);
    var_88 = -1;
    for (var_24 = 0; var_24 < dword_42A1C0; var_24++)
    {
        var_8C = &var_34->unk_04;
        if (var_8C->unk_00 == dword_42A0B8[var_24].unk_00.unk_00
            && var_8C->unk_04 == dword_42A0B8[var_24].unk_00.unk_04)
        {
            var_88 = var_24;
            break;
        }
    }
    if (var_88 >= 0)
    {
        unk_808 = 1;
        unk_800 = dword_42A0B8[var_88].unk_08;
        unk_7FC = 1.0f;
    }
    else
    {
        unk_808 = 0;
        unk_800 = frand_range(0.95f, 1.05f);
        unk_7FC = 1.0f;
    }
    if (((type_4B8888 *)dword_4B8888)->unk_00_6)
        unk_800 = frand_range(0.3f, 1.2f);
    unk_284->set_unk_28(unk_800);
    unk_28C->set_unk_28(unk_7FC);
    var_BD = false;
    for (var_24 = 0; var_24 < dword_42A36C; var_24++)
    {
        var_C4 = &var_28->unk_28.unk_04;
        var_C8 = sub_198800(var_C4);
        if (var_C8->unk_14 == dword_42A1C8[var_24].unk_00.unk_00
            && var_C8->unk_18 == dword_42A1C8[var_24].unk_00.unk_04)
        {
            var_BD = true;
            break;
        }
    }
    if (var_BD)
    {
        var_D0 = sub_EC1F0(unk_828.get_unk_08(), dword_42A1C8[var_24].unk_08);
        if (var_D0)
            unk_80C = dword_42A1C8[var_24].unk_08;
        else
            unk_80C = 0x48415400; // not an address: the tag "HAT"
    }
    else
    {
        unk_80C = 0x48415400; // not an address: the tag "HAT"
    }
    var_D8 = RWS::SkinHelper::FindFirstSkin(*unk_828.get_unk_08());
    if (var_D8)
    {
        var_DC = RpSkinGetSkinToBoneMatrices(var_D8);
        for (var_E0 = 0; var_E0 < unk_28C->get_unk_18()->numNodes; var_E0++)
        {
            unk_650[var_E0] = *(type_7CBD0_t *)&var_DC[var_E0].pos;
            var_100.x = 0.0f;
            var_100.y = 0.0f;
            var_100.z = 0.0f;
            var_100.w = 0.0f;
            var_104 = dword_42A050[var_E0];
            while (var_104 != -1)
            {
                var_100.x += unk_650[var_104].unk_00.x;
                var_100.y += unk_650[var_104].unk_00.y;
                var_100.z += unk_650[var_104].unk_00.z;
                var_104 = dword_42A050[var_104];
            }
#ifdef CODFH_SP // shape: plain assignments schedule the loop's stores as SP 0xE9B00 does
            unk_650[var_E0].unk_00.x = unk_650[var_E0].unk_00.x - (var_100.x + flt_428A50[var_E0].unk_00.x);
            unk_650[var_E0].unk_00.y = unk_650[var_E0].unk_00.y - (var_100.y + flt_428A50[var_E0].unk_00.y);
            unk_650[var_E0].unk_00.z = unk_650[var_E0].unk_00.z - (var_100.z + flt_428A50[var_E0].unk_00.z);
#else
            unk_650[var_E0].unk_00.x -= var_100.x + flt_428A50[var_E0].unk_00.x;
            unk_650[var_E0].unk_00.y -= var_100.y + flt_428A50[var_E0].unk_00.y;
            unk_650[var_E0].unk_00.z -= var_100.z + flt_428A50[var_E0].unk_00.z;
#endif
        }
    }
    else
    {
        var_DC = RpSkinGetSkinToBoneMatrices(var_D8);
        for (var_108 = 0; var_108 < unk_28C->get_unk_18()->numNodes; var_108++)
        {
            unk_650[var_108].unk_00.x = 0.0f;
            unk_650[var_108].unk_00.y = 0.0f;
            unk_650[var_108].unk_00.z = 0.0f;
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS) // MP only: single player has no debug print (SP 0xE9B00)
            sub_19A750("%2d %4d { %9.6f, %9.6f, %9.6f }, \n", var_108,
                       unk_28C->get_unk_18()->pNodeInfo[var_108].nodeID, var_DC[var_108].pos.x,
                       var_DC[var_108].pos.y, var_DC[var_108].pos.z);
#endif
        }
    }
    strncpy(var_150, "FA_QO1A2K_IdleMask", 0x1F);
    var_154 = sub_16C800(var_150, 0x811C9DC5); // not an address: the FNV basis
    unk_805 = 0;
    if (sub_77B70(var_154, (void **)(&var_15C), (void **)(&var_158)))
    {
        var_7C->sub_794C0(0.0f);
        var_7C->sub_796A0((RtAnimAnimation *)var_15C, var_154, 0, (type_783F0 *)var_158, 0, 1.0f, 1.0f);
        unk_298 = var_154;
    }
    else
    {
        unk_298 = 0;
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS) // MP only: single player has no debug print (SP 0xE9B00)
        sub_19A750("WARNING: No idle face anim loaded for level!\n");
#endif
    }
    memset(unk_84C, 0, 0xC);
    memset(unk_858, 0, 0xC);
    for (var_160 = 0; var_160 < 6; var_160++)
    {
        unk_84C[var_160 + 6] = 1;
        unk_858[var_160 + 6] = 1;
    }
    vf_0B0(0, 0);
    vf_25C(0);
    var_164 = sub_198800(&var_C->unk_E0);
    var_168 = sub_71870();
    unk_840 = var_168;
    var_16C = vf_098();
    var_16C->sub_70DF0(this, 2);
    var_16C->sub_70E10(var_164->get_unk_18(), 1);
    var_174 = sub_198800(&var_C->unk_E8);
    if (var_174)
        var_16C->sub_70F40(var_174->get_unk_18(), 1);
    var_17C = (type_3D2CD0 *)sub_71770(1);
    // Its handle as the object's handle struct (a struct copy: the value is
    // loaded before the destination).
    *(type_439E78_00 *)&unk_844 = var_17C->get_unk_04_h();
    var_17C->sub_6CDA0(this, 1);
    memcpy(unk_898, var_C->unk_C0, 6);
    var_184 = vf_098();
    var_C->sub_B8F80(var_184);
    if ((unk_2C & 7) == 2)
        sub_D5B80(this, 9);
    else
        sub_D5B80(this, 10);
    unk_8A0.sub_16BC0(this);
    switch (var_C->unk_168)
    {
    case 5:
        unk_8A0.sub_17AB0(1);
        unk_8A0.unk_530 = 1;
        if (unk_8A0.sub_27E30())
        {
            sub_6B5F0("AIAction_AttackFromCover", (type_67620 *)(vf_098()), 0, 0, 0, 0, 1, 0);
        }
        else if (arg_0->unk_24_18)
        {
            unk_8A0.sub_17AB0(0);
            unk_8A0.unk_530 = 0;
        }
        else
        {
            var_18C = RwMatrixGetPos(&arg_0->unk_60_m);
            sprintf(var_390,
                    "***ERROR: Cannot create soldier entity from trigger loc: %f,%f,%f because it could not "
                    "find a starting coverpoint",
                    var_18C->x, var_18C->y, var_18C->z);
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS) // MP only: single player has no debug print (SP 0xE9B00)
            sub_19A750(var_390);
#endif
            unk_8A0.unk_51C = 0;
            unk_28 |= 0x200;
            unk_28 |= 0x400000; // not an address: a flag
            return 0;
        }
        break;
    }
    sub_3EE10(this);
    sub_40A60(var_16C->sub_71340(), 2, 0, 1, 0);
    sub_35200(var_16C->sub_71340(), 0.0f, 1e37f, 6, 0, 0, 0, -1, -1);
    sub_34E20(var_16C->sub_71340());
    sub_32F70(var_16C->sub_71340(), 0, 100.0f, 0);
    sub_3C720(this);
    var_394 = var_C->unk_130;
    if (valid_weapon_type(var_394))
    {
        unk_3E0.sub_15D010(this, var_394);
        unk_3E0.sub_15D3E0();
    }
    RwMatrixSetIdentityMacro(&unk_3E0.unk_30);
    unk_5E0 = sub_15EFA0(var_C->unk_134) == 8;
    if (unk_5E0)
        unk_4E0.sub_15D010(this, var_C->unk_134);
    if ((unk_2C & 7) == 2)
        sub_83850(0, &unk_1C0, &unk_3B0);
    else
        sub_83850(1, &unk_1C0, &unk_3B0);
    if (!unk_88_1)
    {
        vf_078();
        unk_88 |= 2;
    }
    if (var_C->unk_F8.unk_00 || var_C->unk_F8.unk_04)
    {
        var_39C = sub_198800(&var_C->unk_F8);
        var_3A0 = (type_3DFEEC *)var_39C;
        var_3A4 = var_3A0->unk_24;
        unk_8A0.unk_D14 = var_3A4;
        unk_8A0.unk_49C |= 0x1000;
    }
    var_3A8 = var_C->unk_11C;
    sub_6B5F0("SetDeletionDelay", (type_67620 *)(vf_098()), 0, 0, &var_3A8, 1, 1, 0);
#ifndef CODFH_SP // MP 0x135430 only: single player's soldier (SP 0xE9B00) has no unk_818
    unk_820 = 0;
    unk_81C = 0;
    unk_818 = 0;
#endif
    return 1;
}
// match: ?vf_230@type_3DAFC8@@UAEXXZ @ 0x00136B10
// sp-match: ?vf_230@type_3DAFC8@@UAEXXZ @ 0x000EA840
// Takes it down: its weapon and mounted weapon, its AI's registrations and
// its listener, its AI, its clumps, its render parts, its animations, its
// performance player and AI object, and the trigger's AI script's entity.
void type_3DAFC8::vf_230()
{
    SoldierTrigger *var_4;
    type_3D2E7C *v8;
    type_3DFEEC *varC;

    if (unk_2164)
    {
        unk_2164 = 0;
#ifndef CODFH_SP // MP only: single player does not put its weapon away here (SP 0xEA840)
        sub_136D40();
#endif
        sub_13F590(0);
        v8 = vf_098();
        if (v8)
        {
            sub_330E0(v8->sub_71340(), 0);
            sub_34E40(v8->sub_71340());
            sub_35330(v8->sub_71340());
            sub_40AE0(v8->sub_71340());
            sub_3C760(this);
        }
        unk_8A0.sub_16C50();
        unk_828.sub_129940(0);
        unk_834.sub_129940(0);
        vf_228();
#ifdef CODFH_SP // shape: single player releases them through release_anim (SP 0xEA840)
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
        if (vf_090())
        {
            sub_717B0((type_3D2C88 *)vf_090());
            unk_844 = 0;
        }
        if (v8)
        {
            sub_71970((type_3D2C88 *)v8);
            unk_840 = 0;
        }
        var_4 = (SoldierTrigger *)get_unk_34C();
        if (var_4->unk_D0.unk_00)
        {
            varC = (type_3DFEEC *)sub_198800(&var_4->unk_D0);
            ((type_D48D0 *)&varC->unk_24_id)->sub_D48D0(0);
        }
    }
}
// match: ?vf_038@type_3DAFC8@@UAEXM@Z @ 0x00136CF0
// sp-match: ?vf_038@type_3DAFC8@@UAEXM@Z @ 0x000E4B10
// Its update: the base's, its AI's (timed as profile section 0x18) and its
// head tracking.
void type_3DAFC8::vf_038(RwReal arg_0)
{
    type_3D3548::vf_038(arg_0);
    sub_16D7F0(0x18);
    unk_8A0.sub_17190(arg_0);
    sub_16D850(0x18);
    sub_134160();
}
// match: ?sub_136D40@type_3DAFC8@@QAEXXZ @ 0x00136D40
// Puts its weapon away, when it has a valid one.
void type_3DAFC8::sub_136D40()
{
    if (valid_weapon_type(unk_3E0.unk_04))
    {
        unk_3E0.sub_15D420();
        unk_3E0.sub_15D360();
    }
}
// match: ?sub_136DA0@type_3DAFC8@@QAEXH@Z @ 0x00136DA0
// Changes its weapon to the type arg_0 (nothing when it has it already).
void type_3DAFC8::sub_136DA0(RwInt32 arg_0)
{
    RwInt32 var_4;

    var_4 = unk_3E0.unk_04;
    if (arg_0 == var_4)
        return;
    sub_136D40();
    unk_3E0.sub_15D010(this, arg_0);
    unk_3E0.sub_15D3E0();
}
#if defined(CODFH_SP) || defined(CODFH_DRAW_TRIGGERS) // single player; and multiplayer's debug tools' bots (their grenades)
// Single player's grenade throw (message 0x76C of vf_170, SP 0xEB880): multiplayer has
// none (its tunables flt_429C40..flt_429C84 stay unreferenced there).
extern RwReal flt_429C40;
extern RwReal flt_429C44;
extern RwReal flt_429C48;
extern RwReal flt_429C4C;
extern RwReal flt_429C50;
extern RwReal flt_429C54;
extern RwReal flt_429C58;
extern RwReal flt_429C5C;
extern RwReal flt_429C68;
extern RwReal flt_429C6C;
extern RwReal flt_429C70;
extern RwReal flt_429C74;
extern RwReal flt_429C78;
extern RwReal flt_429C7C;
extern RwReal flt_429C80;
extern RwReal flt_429C84;

// sp-match: ?sp_sub_E4B50@type_3DAFC8@@QAEXXZ @ 0x000E4B50
// Single player only (SP 0xE4B50): readies the grenade (unk_4E0's sub_15D3E0).
void type_3DAFC8::sp_sub_E4B50()
{
    unk_4E0.sub_15D3E0();
}
#endif

#if defined(CODFH_SP) || defined(CODFH_DRAW_TRIGGERS) // single player; and multiplayer's debug tools' bots (their grenades)
// sp-match: ?sp_sub_E4B60@type_3DAFC8@@QAEXPAURwV3d@@MMMM@Z @ 0x000E4B60
// Single player only (SP 0xE4B60): throws the grenade in hand at *arg_0 (arg_4 and arg_8
// whole, then arg_C and arg_10, with the timer override unk_5FC) and restarts the
// throw timer unk_5E4.
void type_3DAFC8::sp_sub_E4B60(RwV3d *arg_0, RwReal arg_4, RwReal arg_8, RwReal arg_C, RwReal arg_10)
{
    unk_5E4 = 0.0f;
    unk_4E0.sub_15D8A0(arg_0, (RwInt32)arg_4, (RwInt32)arg_8, arg_C, arg_10, unk_5FC);
    unk_4E0.sub_15D420();
}
#endif

#if defined(CODFH_SP) || defined(CODFH_DRAW_TRIGGERS) // single player; and multiplayer's debug tools' bots (their grenades)
// sp-match: ?sp_sub_E4BB0@type_3DAFC8@@QAEXXZ @ 0x000E4BB0
// Single player only (SP 0xE4BB0): throws a grenade at its target (or at the throw
// point unk_5EC when one is set, else 1100 ahead): at the target's record position
// (lowered by its height when vf_00C has one), its share of the way there (flt_429C40,
// more above, less below) varied by the trigger's grenade mode unless the target's AI
// (sp_sub_16540) takes the point as it is; then two line tests from the hand (to the
// arc's top and on) pick the throw's arguments. A missing record goes straight to the
// point ahead (the image jumps there).
void type_3DAFC8::sp_sub_E4BB0()
{
    RwReal var_arc;
    RwReal var_spin;
    SoldierTrigger *var_trigger;
    RwInt32 var_seen;
    RwV3d var_at;
    RwV3d var_d;
    RwV3d var_hand;
    type_3D3548 *var_target;
    type_154C0_80 *var_rec;
    RwV3d *var_me;
    RwMatrix *var_m;
    RwInt32 var_clear1;
    RwInt32 var_clear2;
    RwReal var_4;
    RwReal var_8;

    if (!unk_4E0.get_unk_00())
    {
        sp_sub_E4B50();
    }
    var_trigger = (SoldierTrigger *)unk_344.unk_08;
    var_spin = 0.0f;
    var_seen = 0;
    var_target = unk_8A0.unk_1374.sub_D4910();
    if (var_target && !unk_5F8)
    {
        var_rec = unk_8A0.sub_16ED0(var_target, 0);
        if (!var_rec)
        {
            goto ahead;
        }
        var_me = sub_CD550();
        var_arc = flt_429C40;
        var_at = var_rec->unk_14;
        if (var_target->vf_120()->sp_sub_16540(this, &var_at))
        {
            var_seen = 1;
        }
        else
        {
            if (var_target->vf_00C())
            {
                var_at.y -= var_target->unk_48;
            }
            if (var_me->y + 200.0f < var_at.y)
            {
                var_arc = flt_429C44;
            }
            else if (var_me->y - 200.0f > var_at.y)
            {
                var_arc = flt_429C48;
            }
        }
        switch (var_trigger->unk_138)
        {
        case 0:
            var_arc += frand_range(-flt_429C7C, flt_429C7C);
            if (var_rec->unk_04_0)
            {
                var_spin = flt_429C70;
            }
            break;
        case 2:
            var_arc += frand_range(-flt_429C84, flt_429C84);
            if (var_rec->unk_04_0)
            {
                var_spin = flt_429C78;
            }
            break;
        default:
            var_arc += frand_range(-flt_429C80, flt_429C80);
            if (var_rec->unk_04_0)
            {
                var_spin = flt_429C74;
            }
            break;
        }
        if (!var_seen)
        {
            RwV3d var_lead;

            RwV3dSub(&var_lead, &var_at, sub_CD550());
            RwV3dScale(&var_lead, &var_lead, var_arc);
            RwV3dAdd(&var_at, &var_lead, sub_CD550());
        }
    }
    else if (unk_5F8)
    {
        var_at = unk_5EC;
    }
    else
    {
    ahead:
        var_m = RwFrameGetMatrix(get_unk_340());
        var_at = *RwMatrixGetPos(var_m);
        RwV3dIncrementScaledMacro(&var_at, RwMatrixGetAt(var_m), 1100.0f);
    }
    var_hand = *RwMatrixGetPos(RwFrameGetMatrix(RpClumpGetFrame(unk_4E0.get_unk_18())));
    RwV3dSub(&var_d, &var_at, sub_CD550());
    var_d.x *= flt_429C5C;
    var_d.y = 0.0f;
    var_d.z *= flt_429C5C;
    var_d.y = RwV3dLength(&var_d) * flt_429C68;
    RwV3dAdd(&var_d, &var_hand, &var_d);
    var_clear1 = 0;
    var_clear2 = 0;
    if (sub_D2FC0(&var_hand, &var_d, 0, 0, 0, 0, 1, 1, 0x180000 /* not an address: line-test flags */, 1, 0))
    {
        var_clear1 = 1;
    }
    var_d.y *= flt_429C6C / flt_429C68;
    RwV3dScale(&var_d, &var_d, 1.5f);
    if (sub_D2FC0(&var_hand, &var_d, 0, 0, 0, 0, 1, 1, 0x180000 /* not an address: line-test flags */, 1, 0))
    {
        var_clear2 = 1;
    }
    var_8 = var_clear1 ? flt_429C54 : flt_429C58;
    var_4 = var_clear2 ? flt_429C50 : flt_429C4C;
    if (unk_5F8)
    {
        var_spin = 0.0f;
        var_4 = flt_429C4C;
        var_8 = flt_429C54;
    }
    else if (var_clear1 && var_clear2)
    {
        var_8 = flt_429C58;
        var_4 = flt_429C58 - 5.0f;
    }
    else if (var_seen && !var_clear1 && !var_clear2)
    {
        var_4 = flt_429C4C;
        var_8 = flt_429C54;
    }
    sp_sub_E4B60(&var_at, var_4, var_8, 3000.0f, var_spin);
}
#endif

#if defined(CODFH_DRAW_TRIGGERS) && !defined(CODFH_SP)
// (port/src/debug/trigtools.cpp: the debug tools' bots' aim spread scaled, CODFH_BOTS_ACCURACY)
RwReal TrigBotSpread(const void *pEntity, RwReal fSpread);
// (whether the entity is one of the debug tools' AI soldiers)
bool TrigIsAiSoldier(const void *pEntity);
// (the bots' grenade events counted: 0 a throw, 1 a grenade taken in hand)
extern RwInt32 g_anTrigGrenadeEvents[2];
void TrigBotAnimEvent(RwInt32 nEvent, RwInt32 bIgnored);
// (and their grenades' odds, in 10000, scaled: CODFH_BOTS_GRENADE_ODDS)
RwInt32 TrigBotGrenadeOdds(const void *pEntity, RwInt32 nBase, RwInt32 nOdds);
#endif
// match: ?sub_136E00@type_3DAFC8@@QAEXXZ @ 0x00136E00
// sp-match: ?sub_136E00@type_3DAFC8@@QAEXXZ @ 0x000E5070
// "DropGrenade": drops the grenade in hand 20 units above its clump's
// origin, and clears the timer override.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3DAFC8::sub_136E00()
{
    RwFrame *var_4;
    RwV3d local_10;
    RwMatrix *stk_14;
    RpClump *loc18;

    if (!unk_5E0 || !unk_4E0.get_unk_00())
        return;
    loc18 = unk_25C.unk_08;
    var_4 = RpClumpGetFrame(loc18);
    stk_14 = RwFrameGetLTM(var_4);
    local_10 = *RwMatrixGetPos(stk_14);
    local_10.y += 20.0f;
    unk_4E0.sub_15D8A0(&local_10, 0, 0x5A, 3000.0f, 0, -1.0f);
    unk_5FC = -1.0f;
    unk_4E0.sub_15D420();
}
extern RwReal flt_4F28D8[3];
// sp-match: ?get_grenade_multiplier@@YAMXZ @ 0x000E4AD0
inline RwReal get_grenade_multiplier()
{
    if (dword_42B714 > -1 && dword_42B714 < 3)
    {
        return flt_4F28D8[dword_42B714];
    }
    return 1.0f;
}
// match: ?sub_136EC0@type_3DAFC8@@QAEHH@Z @ 0x00136EC0
// sp-match: ?sub_136EC0@type_3DAFC8@@QAEHH@Z @ 0x000E5100
// "ShouldIThrowAGrenade": never without a grenade, before unk_5E4 reaches
// 120, or unless its target is 700 to 3000 away; otherwise by a chance (in
// 10000) by the trigger's grenade mode and arg_0, scaled by the difficulty
// and by the entities near the target (more when one or several are its
// enemies, less when some are not).
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_3DAFC8::sub_136EC0(RwInt32 arg_0)
{
    RwInt32 l4;
    SoldierTrigger *var_8;
    AIData *fp_C;
    type_154C0_80 *v10;
    type_3D3548 *local_14;
    RwInt32 var18;
    RwInt32 var_1C;
    RwReal l20;
    RwInt32 fp_24;
    type_3D3548 *fp_28;

    if (!get_unk_5E0())
        return 0;
    var_8 = (SoldierTrigger *)unk_344.unk_08;
    var18 = 0;
    if (unk_5E4 < 120.0f)
        return 0;
    local_14 = unk_8A0.unk_1374.sub_D4910();
    if (!local_14)
        return 0;
    v10 = unk_8A0.sub_16ED0(local_14, 0);
    if (!v10)
        return 0;
    if (v10->unk_0C < 700.0f || v10->unk_0C > 3000.0f)
        return 0;
    var_1C = 0;
    l4 = 0;
    fp_C = local_14->vf_120();
    if (fp_C)
    {
        for (fp_24 = 0; fp_24 < 0x20; fp_24++)
        {
            fp_28 = fp_C->unk_80[fp_24].unk_00.sub_D4910();
            if (fp_28 && fp_28 != local_14 && fp_C->unk_80[fp_24].unk_0C < 700.0f)
            {
                if (cmp_unk_2C(this, fp_28))
                    l4++;
                else
                    var_1C++;
            }
        }
    }
    l20 = 1.0f;
    if (l4 == 1)
        l20 = 1.3f;
    else if (l4 > 1)
        l20 = 2.0f;
    if (var_1C > 0)
        l20 -= 0.6f;
    if (l20 < 0.0f)
        l20 = 0.0f;
    switch (var_8->unk_13C)
    {
    case 0:
        switch (arg_0)
        {
        default:
            var18 = 1000;
            break;
        case 1:
            var18 = 10;
            break;
        case 2:
            var18 = 10;
            break;
        }
        break;
    default:
        switch (arg_0)
        {
        default:
            var18 = 2500;
            break;
        case 1:
            var18 = 40;
            break;
        case 2:
            var18 = 20;
            break;
        }
        break;
    case 2:
        switch (arg_0)
        {
        default:
            var18 = 5000;
            break;
        case 1:
            var18 = 120;
            break;
        case 2:
            var18 = 50;
            break;
        }
        break;
    }
#if defined(CODFH_DRAW_TRIGGERS) && !defined(CODFH_SP)
    // (the debug tools' bots: their own odds, not the difficulty's multiplier, which is 0 in
    // multiplayer)
    {
        RwInt32 nBase = var18;

        var18 = var18 * get_grenade_multiplier();
        var18 = TrigBotGrenadeOdds(this, nBase, var18);
    }
#else
    var18 = var18 * get_grenade_multiplier();
#endif
    if ((RwReal)(RpRandom() % 10000 + 1) > var18 * l20)
        return 0;
    return 1;
}
// match: ?sub_137200@type_3DAFC8@@QAEHH@Z @ 0x00137200
// sp-match: ?sub_137200@type_3DAFC8@@QAEHH@Z @ 0x000E5320
// "ShouldIMeleeAttack": whether its target is within 120 above or below it
// (a player's by its eye height), unless the target is flagged out (bits 7
// and 18 of unk_2C) or has a vf_200 entity.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_3DAFC8::sub_137200(RwInt32 arg_0)
{
    RwInt32 var_4;
    type_3D3548 *v8;
    RwV3d l14;

    var_4 = 0;
    v8 = unk_8A0.unk_1374.sub_D4910();
    if (v8)
    {
        if (v8->unk_2C_18 || v8->unk_2C_7)
            var_4 = 0;
        else if (v8->vf_200())
            var_4 = 0;
        else
        {
            RwV3dSubMacro(&l14, sub_CD550(), v8->sub_CD550());
            if (v8->vf_00C())
                l14.y += v8->vf_00C()->unk_1A00;
            var_4 = l14.y < 120.0f && l14.y > -120.0f;
        }
    }
    return var_4;
}
// match: ?sub_137340@@YAHPAURwV3d@@0@Z @ 0x00137340
// sp-match: ?sub_137340@@YAHPAURwV3d@@0@Z @ 0x000E5400
// Whether *arg_0 and *arg_4 are equal.
RwInt32 sub_137340(RwV3d *arg_0, RwV3d *arg_4)
{
    if (arg_0->x == arg_4->x && arg_0->y == arg_4->y && arg_0->z == arg_4->z)
        return 1;
    return 0;
}
// match: ?sub_137390@@YAHPAURwMatrixTag@@0@Z @ 0x00137390
// sp-match: ?sub_137390@@YAHPAURwMatrixTag@@0@Z @ 0x000E5440
// Whether the matrices *arg_0 and *arg_4 are equal (position first).
RwInt32 sub_137390(RwMatrix *arg_0, RwMatrix *arg_4)
{
    if (sub_137340(&arg_0->pos, &arg_4->pos) && sub_137340(&arg_0->up, &arg_4->up)
        && sub_137340(&arg_0->at, &arg_4->at) && sub_137340(&arg_0->right, &arg_4->right))
        return 1;
    return 0;
}
// match: ?vf_03C@type_3DAFC8@@UAEXM@Z @ 0x00137400
// sp-match: ?vf_03C@type_3DAFC8@@UAEXM@Z @ 0x000E54B0
// Its logic for the time arg_0: its timers; a hit by the entity it rides
// when that one breaks (flag 0 or 9); the base's; its second animation's
// translations offset by unk_650 and two of its bones copied from the
// primary's; riding at the ride's tag; while flag 9 is set and its pickup
// not dropped, its weapon's model watched for a collision on the way (a
// world or an atomic) or for staying put: after 8 (unk_3E0.unk_70)
// or on a collision it drops its pickup; then its AI.
void type_3DAFC8::vf_03C(RwReal arg_0)
{
    RwInt32 var_8;
    type_3D3548 *var_C;
#ifndef CODFH_SP // single player declares these in the blocks that use them (SP 0xE54B0)
    type_75600 var_3C;
#endif
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
#ifndef CODFH_SP
    type_129940 *var_A0;
    RpClump *var_A4;
    RwMatrix var_F0;
#endif
    RwFrame *var_F4;
    RwFrame *var_F8;
    SoldierTrigger *var_FC;
#ifndef CODFH_SP
    RwFrame *var_100;
    RpClump *var_104;
    RwFrame *var_108;
    RwMatrix *var_10C;
    RwInt32 var_110;
    RwLine var_128;
    RwV3d var_134;
    RwReal var_138;
#endif
    RwInt32 var_13C;
    type_4E5D30 *var_140;
#ifndef CODFH_SP
    RwReal var_150;
    RpIntersection var_16C;
    type_91F40 var_198;
    RwInt32 var_19C;
    type_4E5D30 *var_1A0;
#endif

    if (unk_1D2C > 0.0f)
        unk_1D2C -= arg_0;
    if (unk_1D30 > 0.0f)
        unk_1D30 -= arg_0;
    unk_5E4 += arg_0;
    if (unk_894 > 0.0f)
        unk_894 -= arg_0;
    for (var_8 = 0; var_8 < 4; var_8++)
    {
        if (unk_2144[var_8].unk_04 > 0.0f)
            unk_2144[var_8].unk_04 -= arg_0;
    }
    unk_84C[5] = 0;
    unk_858[5] = 0;
    if (unk_624.sub_D4910())
    {
        var_C = unk_624.sub_D4910();
        if (var_C->unk_28_0 || var_C->unk_28_9)
        {
#ifdef CODFH_SP // shape: block-scoped
            type_75600 var_3C;
#endif
            var_3C.unk_00_w = 0;
            if ((unk_2C & 7) == 2)
                var_3C.unk_08 = 0x202;
            else
                var_3C.unk_08 = 0x201;
            var_3C.unk_04 = 0;
            var_3C.unk_14 = 0;
            var_3C.unk_18 = 0;
            var_3C.unk_28 = (RwReal)unk_1D20;
            var_3C.unk_2C = (RwReal)unk_1D20;
            var_3C.unk_0C = var_C;
            var_3C.unk_24 = 1;
            var_3C.unk_10 = var_C->unk_2C;
            unk_894 = 0.0f;
            vf_064(&var_3C);
        }
    }
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
            var_74[var_78].unk_00.x -= unk_650[var_7C].unk_00.x;
            var_74[var_78].unk_00.y -= unk_650[var_7C].unk_00.y;
            var_74[var_78].unk_00.z -= unk_650[var_7C].unk_00.z;
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
    if (unk_620 && unk_624.sub_D4910())
    {
#ifdef CODFH_SP // shape: block-scoped
        type_129940 *var_A0;
        RpClump *var_A4;
        RwMatrix var_F0;
#endif
        var_A0 = &unk_624.sub_D4910()->unk_25C;
        var_A4 = var_A0->unk_08;
        if (sub_EC2D0(var_A4, (RwInt32)&var_F0, unk_628, 0, 1))
        {
            var_F4 = unk_338.unk_08;
            var_F8 = var_F4;
            RwFrameTransform(var_F8, &var_F0, rwCOMBINEREPLACE);
            RwFrameUpdateObjects(var_F8);
        }
    }
    if (unk_620 && !unk_624.sub_D4910())
        unk_620 = 0;
    if (unk_28_9 && !unk_1D48)
    {
        var_FC = (SoldierTrigger *)unk_344.unk_08;
        if ((var_FC && var_FC->unk_150 && var_FC->unk_14C != -1)
            || (unk_810 != -1 && unk_814))
        {
#ifdef CODFH_SP // shape: block-scoped
            RwFrame *var_100;
            RpClump *var_104;
            RwFrame *var_108;
            RwMatrix *var_10C;
            RwInt32 var_110;
            RwLine var_128;
            RwV3d var_134;
            RwReal var_138;
#endif
            var_100 = 0;
            var_104 = unk_3E0.unk_10.unk_08;
            if (var_104)
            {
                var_100 = RpClumpGetFrame(var_104);
            }
            else
            {
                var_108 = unk_338.unk_08;
                var_100 = var_108;
            }
            var_10C = RwFrameGetMatrix(var_100);
            var_110 = 0;
            if (unk_3E0.unk_30.flags & rwMATRIXINTERNALIDENTITY)
                var_128.start = var_10C->pos;
            else
                var_128.start = unk_3E0.unk_30.pos;
            var_128.end = var_10C->pos;
            RwV3dSubMacro(&var_134, &var_128.end, &var_128.start);
            var_138 = RwV3dLength((RwV3d *)&var_134);
            if (var_138 > 0.01f)
            {
                RwV3dNormalize(&var_134, &var_134);
                RwV3dScaleMacro(&var_134, &var_134, 50.0f);
                RwV3dSubMacro(&var_128.start, &var_128.start, &var_134);
                RwV3dAddMacro(&var_128.end, &var_128.end, &var_134);
                for (var_13C = 0; var_13C < 4; var_13C++)
                {
                    var_140 = &dword_4E5D30[var_13C];
                    if (var_140->get_unk_00() && var_140->get_unk_28()
                        && sub_91F40(var_140->get_unk_28(), &var_128, 0, 0,
                                     0x20000, 1)) // not an address: collision flags
                    {
                        var_110 = 1;
                        break;
                    }
                }
                if (!var_110)
                {
#ifdef CODFH_SP // shape: block-scoped
                    RwReal var_150;
                    RpIntersection var_16C;
                    type_91F40 var_198;
                    RwInt32 var_19C;
                    type_4E5D30 *var_1A0;
#endif
                    var_150 = 1e37f;
                    var_16C.type = rpINTERSECTLINE;
                    var_16C.t.line.start = var_128.start;
                    var_16C.t.line.end = var_128.end;
                    var_198.unk_00 = 0;
                    var_198.unk_04 = var_150;
                    for (var_19C = 0; var_19C < 4; var_19C++)
                    {
                        var_1A0 = &dword_4E5D30[var_19C];
                        if (var_1A0->get_unk_00() && var_1A0->get_unk_28())
                        {
                            RpWorldForAllAtomicIntersections(var_1A0->get_unk_28(), &var_16C, sub_FC8F0,
                                                             &var_198);
                            sub_FC9F0(&var_16C.t.line.start, &var_198, &var_110, &var_150, 0, 0, 0);
                        }
                        if (var_110)
                            break;
                    }
                }
            }
            if (var_110 || sub_137390(var_10C, &unk_3E0.unk_30))
            {
                unk_3E0.unk_70 += arg_0;
                if (unk_3E0.unk_70 > 8.0f)
                {
                    vf_1CC(1);
                }
                else if (var_110)
                {
                    if (unk_3E0.unk_30.flags & rwMATRIXINTERNALIDENTITY)
                    {
                        unk_1D48 = 1;
                    }
                    else
                    {
                        *var_10C = unk_3E0.unk_30;
                        vf_1CC(1);
                    }
                }
            }
            unk_3E0.unk_30 = *var_10C;
        }
    }
    sub_16D7F0(0x18);
    unk_8A0.sub_172F0(arg_0);
    sub_16D850(0x18);
}
const RwReal flt_3DAEC0 = 16.666666f;
// match: _flt_3DAEC0 @ 0x003DAEC0
const RwV3d v3d_3DAEC4 = {1.0f, 0.0f, 0.0f};
const RwV3d v3d_3DAED0 = {0.0f, 1.0f, 0.0f};
const RwV3d v3d_3DAEDC = {0.0f, 0.0f, 1.0f};
// match: ?vf_04C@type_3DAFC8@@UAEXM@Z @ 0x00137EF0
// sp-match: ?vf_04C@type_3DAFC8@@UAEXM@Z @ 0x000EA990
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// After the base's update for the time arg_0: its props (unk_35C) and its
// held clump (unk_828, bone 0x1C4) follow its frame or bones; its second
// animation's speed (2 with cheat flag 0) and time; a knocked-off unk_834
// flies (unk_804 2) until it lands, else follows its frame or (bone 0x1A9,
// or its hierarchy's unk_80C node) its head; its weapon and grenade in
// hand, its mounted weapon, its atomic's centre height, its AI and the base
// vf_1D0.
void type_3DAFC8::vf_04C(RwReal arg_0)
{
    RpClump *var_D8;
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
    bool var_5D;
    RpClump *var_64;
    RpClump *var_68;
    RwFrame *var_6C;
    RwMatrix *var_70;
    RwV3d var_7C;
    RwV3d var_88;
    bool var_89;
    RwV3d var_98;
    RwV3d var_A4;
    RwReal var_B0;
    RpClump *var_B4;
    RpClump *var_B8;
    RwFrame *var_BC;
    RwMatrix *var_C0;
    RpClump *var_C4;
    RwFrame *var_C8;
    RwMatrix *var_CC;
    RpClump *var_D0;
    RpClump *var_D4;
    RwMatrix var_120;
    RwMatrix *var_124;
    RpHAnimHierarchy *var_128;
    RwInt32 var_12C;
    RpClump *var_130;
    RwFrame *var_134;
    RwMatrix *var_138;
    RpAtomic *var_144;
    RwMatrix *var_148;
    RpHAnimHierarchy *var_14C;
    RwReal var_150;

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
        var_2C = unk_828.unk_08;
        if (var_2C)
        {
            var_30 = unk_828.unk_08;
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
    }
    if (((type_4B8888 *)dword_4B8888)->unk_00_0)
        unk_28C->set_unk_28(2.0f);
    else
        unk_28C->set_unk_28(unk_7FC);
    if (unk_28C)
    {
        var_5D = false;
        if (unk_284->unk_12 & 4)
            var_5D = true;
        unk_28C->sub_7C090(arg_0 * flt_3DAEC0 * 0.001f, var_5D);
    }
    if (unk_804 > 1)
    {
        if (unk_804 > 2)
        {
        }
        else
        {
            var_64 = unk_834.unk_08;
            if (var_64)
            {
                var_68 = unk_834.unk_08;
                var_6C = RpClumpGetFrame(var_68);
                var_70 = RwFrameGetMatrix(var_6C);
                var_7C = var_70->pos;
                var_88 = var_70->pos;
                var_88.x += arg_0 * unk_7E4.x;
                var_88.y += arg_0 * unk_7E4.y;
                var_88.z += arg_0 * unk_7E4.z;
                var_89 = true;
                if (sub_FCAE0(&var_7C, &var_88, &var_A4, &var_98, sub_9A800(this), 1, 1))
                {
                    if (var_98.y > 0.7f)
                    {
                        unk_804++;
                        var_70->pos.x = var_A4.x;
                        var_70->pos.y = var_A4.y;
                        var_70->pos.z = var_A4.z;
                        var_89 = false;
                    }
                    else
                    {
                        var_B0 = sqrt(unk_7E4.x * unk_7E4.x + unk_7E4.z * unk_7E4.z);
                        unk_7E4.x = var_B0 * var_98.x;
                        unk_7E4.z = var_B0 * var_98.z;
                    }
                }
                if (var_89)
                {
                    var_70->pos.x += arg_0 * unk_7E4.x;
                    var_70->pos.y += arg_0 * unk_7E4.y;
                    var_70->pos.z += arg_0 * unk_7E4.z;
                    unk_7E4.y -= 0.5f * arg_0;
                    sub_140440(var_70, &unk_7F0, 0.5f);
                }
                RwFrameUpdateObjects(var_6C);
            }
        }
    }
    else if (!unk_28_13)
    {
        var_B4 = unk_834.unk_08;
        if (var_B4)
        {
            var_B8 = unk_25C.unk_08;
            var_BC = RpClumpGetFrame(var_B8);
            var_C0 = RwFrameGetLTM(var_BC);
            var_C4 = unk_834.unk_08;
            var_C8 = RpClumpGetFrame(var_C4);
            var_CC = RwFrameGetMatrix(var_C8);
            *var_CC = *var_C0;
            RwFrameUpdateObjects(var_C8);
        }
    }
    else
    {
        var_D0 = unk_834.unk_08;
        if (var_D0)
        {
            var_D4 = unk_828.unk_08;
            var_D8 = unk_828.unk_08;
            if (sub_EC310(var_D8, sub_16D970(var_D4), &var_120, unk_80C, 0, 1))
            {
                var_124 = &var_120;
            }
            else
            {
                var_128 = unk_284->unk_18;
                var_12C = RpHAnimIDGetIndex(var_128, 0x1A9);
                var_124 = &var_10[var_12C];
            }
            var_130 = unk_834.unk_08;
            var_134 = RpClumpGetFrame(var_130);
            var_138 = RwFrameGetMatrix(var_134);
            RwMatrixTransform(var_138, var_124, rwCOMBINEREPLACE);
            RwFrameUpdateObjects(var_134);
        }
    }
    if (unk_3E0.get_unk_00())
        sub_138760(&unk_3E0, 0x1C2, (RwInt32)arg_0);
    if (unk_4E0.get_unk_00())
        sub_138760(&unk_4E0, unk_5E8, (RwInt32)arg_0);
    if (unk_61C)
        sub_13F350(arg_0);
    var_144 = unk_250.unk_08;
    if (var_144)
    {
        var_148 = RwFrameGetLTM(RpAtomicGetFrame(var_144));
        var_14C = unk_284->unk_18;
        var_150 = var_10[RpHAnimIDGetIndex(var_14C, 1)].pos.y - var_148->pos.y;
        var_144->boundingSphere.center.y = var_150;
    }
    sub_16D7F0(0x18);
    unk_8A0.sub_17A20(arg_0);
    sub_16D850(0x18);
    type_3D3548::vf_1D0();
}
// match: ?vf_21C@type_3DAFC8@@UAEXM@Z @ 0x00138710
// sp-match: ?vf_21C@type_3DAFC8@@UAEXM@Z @ 0x000EC2A0
// Its five-way blends (while their flags are set), then the base's.
void type_3DAFC8::vf_21C(RwReal arg_0)
{
    if (unk_824 & 1)
        sub_139620();
    if (unk_824 & 2)
        sub_13A410();
    type_3D3548::vf_21C(arg_0);
}
// Where a weapon sits off the soldier's frame when no animation drives it,
// by weapon class (rows, 0 for none or kinds 6, 8 and 15) and posture class
// (columns): the height (-1: at twice the soldier's height instead) and the
// sideways offset (this unit's constants, 0x3DAEE8 and 0x3DAF58).
const RwReal flt_3DAEE8[9][3] = {
    {109.382202f, 80.8946991f, 33.7338982f},
    {135.663803f, 86.2866974f, 27.3132f},
    {142.067505f, 80.8946991f, 33.7338982f},
    {149.804398f, 103.199402f, -1.0f},
    {147.067505f, 80.8946991f, 33.7338982f},
    {106.421799f, -1.0f, 28.8885994f},
    {87.6591034f, -1.0f, -1.0f},
    {-1.0f, -1.0f, -1.0f},
    {-1.0f, -1.0f, -1.0f},
};
const RwReal flt_3DAF58[9][3] = {
    {-25.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f},
    {-25.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f},
};
// 0x003DAFC4
extern const RwReal flt_3DAFC4 = 0.0f;
// match: ?flt_3DAFC4@@3MB @ 0x003DAFC4

// match: _flt_3DAF58 @ 0x003DAF58
// match: _flt_3DAEE8 @ 0x003DAEE8
// match: ?sub_138760@type_3DAFC8@@QAEXPAUtype_15CCE0@@HH@Z @ 0x00138760
// sp-match: ?sub_138760@type_3DAFC8@@QAEXPAUtype_15CCE0@@HH@Z @ 0x000E5BF0
// Puts the weapon arg_0's model in its hand: at the bone arg_4 while its
// animation drives it, else at its cover node (its AI object in state 6,
// 0x26 or 0x2A with a node that is not of kind 0xE) or at its frame raised
// by the tables above; then the weapon's state arg_8 (sub_15D600).
void type_3DAFC8::sub_138760(type_15CCE0 *arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    RpClump *var_8;
    RwFrame *var_C;
    RwMatrix *var_10;
    RpHAnimHierarchy *var_14;
    RwMatrix *var_18;
    RpHAnimHierarchy *var_1C;
    RwInt32 var_20;
    RwMatrix *var_24;
    type_F8350 *var_28;
    RwInt32 var_2C;
#ifndef CODFH_SP // single player declares these in the blocks that use them (SP 0xE5BF0)
    RwV3d var_38;
    RwMatrix var_80;
    RwV3d var_C0;
#endif
    RpClump *var_C4;
    RwFrame *var_C8;
    RwMatrix *var_CC;
    RwInt32 var_D0;
    RwInt32 var_D4;
    RwInt32 var_D8;
#ifndef CODFH_SP
    RwV3d var_EC;
#endif

    var_8 = arg_0->unk_10.unk_08;
    var_C = RpClumpGetFrame(var_8);
    var_10 = RwFrameGetMatrix(var_C);
    if (unk_28_13)
    {
        var_14 = unk_284->unk_18;
        var_18 = RpHAnimHierarchyGetMatrixArray(var_14);
        var_1C = unk_284->unk_18;
        var_20 = RpHAnimIDGetIndex(var_1C, arg_4);
        var_24 = &var_18[var_20];
        RwMatrixTransform(var_10, var_24, rwCOMBINEREPLACE);
    }
    else
    {
        var_28 = unk_8A0.unk_F60;
        var_2C = -1;
        if (var_28)
            var_2C = sub_F8FC0(var_28);
        if (var_28 && var_2C != 0xE && unk_8A0.sub_238E0(0))
        {
#ifdef CODFH_SP // shape: block-scoped
            RwV3d var_38;
            RwMatrix var_80;
            RwV3d var_C0;
#endif
            var_38.x = 0.0f;
            var_38.y = 0.0f;
            var_38.z = 0.0f;
            sub_F8FE0(var_28, &var_38, 0);
            RwMatrixSetIdentityMacro(&var_80);
            RtQuatConvertToMatrix(&var_28->unk_1C, &var_80);
            var_80.pos = var_28->unk_10;
            sub_1414C0(&var_C0, &var_38, &var_80);
            var_80.pos = var_C0;
            RwMatrixTransform(var_10, &var_80, rwCOMBINEREPLACE);
        }
        else
        {
            var_C4 = unk_25C.unk_08;
            var_C8 = RpClumpGetFrame(var_C4);
            var_CC = RwFrameGetLTM(var_C8);
            RwMatrixTransform(var_10, var_CC, rwCOMBINEREPLACE);
            var_D0 = vf_0BC();
            var_D4 = 0;
            var_D8 = unk_3E0.unk_00;
            if (var_D8)
            {
                switch (unk_3E0.get_unk_04())
                {
                case 6:
                case 8:
                case 15:
                    var_D4 = 0;
                    break;
                default:
                    var_D4 = unk_3E0.sub_15EF80();
                    break;
                }
            }
            if (flt_3DAEE8[var_D4][var_D0] != -1.0f)
            {
#ifdef CODFH_SP // shape: block-scoped
                RwV3d var_EC;
#endif
                var_EC.x = 0.0f;
                var_EC.y = 0.0f;
                var_EC.z = 0.0f;
                var_EC.y += flt_3DAEE8[var_D4][var_D0];
                if (flt_3DAF58[var_D4][var_D0] != 0.0f)
                    var_EC.x += flt_3DAF58[var_D4][var_D0];
                sub_1414C0(&var_10->pos, &var_EC, var_CC);
            }
            else
            {
                var_10->pos.y += unk_48 * 2.0f;
            }
        }
    }
    RwFrameUpdateObjects(var_C);
    arg_0->sub_15D600((RwReal)arg_8);
}
// The soldiers' aim spread multiplier by difficulty (0x4F2878).
extern RwReal flt_4F2878[3];

// That multiplier for the difficulty dword_42B714, 1 outside 0 to 2: an
// inline with no address and so no database name, named for what it
// returns. Evidence: sub_138D00 reads it through a temporary of its own at
// each use, with the range check of get_spread_multiplier (unit_11EE20).
inline RwReal get_aim_spread_multiplier()
{
    if (dword_42B714 > -1 && dword_42B714 < 3)
    {
        return flt_4F2878[dword_42B714];
    }
    return 1.0f;
}
// match: ?sub_138D00@type_3DAFC8@@QAEHH@Z @ 0x00138D00
// sp-match: ?sub_138D00@type_3DAFC8@@QAEHH@Z @ 0x000E5F20
// "SetAdvancedShotLocation": with arg_0 and a target, picks where to shoot:
// from its muzzle (or its cover node's point), towards the target's centre
// at up to 0.7 of the distance (at least its weapon's range), spread at
// random by its AI parameters (vf_164, vf_168) and the difficulty, until a
// line test passes (the point becomes its weapon's aim) or fails twice
// (returning 0). Without, its weapon stops aiming at a point.
RwInt32 type_3DAFC8::sub_138D00(RwInt32 arg_0)
{
    RwInt32 var_8;
    type_3D3548 *var_C;
    RwV3d var_18;
    AIData *var_1C;
    type_F8350 *var_20;
#ifndef CODFH_SP // single player declares these in the blocks that use them (SP 0xE5F20)
    RwMatrix var_A0;
#endif
    RwV3d var_AC;
    RwV3d var_B8;
    RwReal var_BC;
    RwMatrix var_100;
    RwInt32 var_104;
    RwReal var_114;
    RwInt32 var_118;
    RwInt32 var_11C;
#ifndef CODFH_SP
    RwMatrix var_160;
    RwReal var_180;
    RwV3d var_1A8;
#endif

    var_8 = 1;
    var_C = unk_8A0.unk_1374.sub_D4910();
    if (arg_0 && var_C)
    {
        var_C->vf_110(&var_18, this, 0);
        var_1C = vf_120();
        var_20 = var_1C->unk_F60;
        if (var_1C->sub_238E0(0) && var_20)
        {
#ifdef CODFH_SP // shape: block-scoped
            RwMatrix var_A0;
#endif
            RtQuatConvertToMatrix(&var_20->unk_1C, &var_A0);
            var_A0.pos = var_20->unk_10;
            sub_F8FE0(var_20, &var_AC, 0);
            sub_1414C0(&var_AC, &var_AC, &var_A0);
        }
        else
        {
            unk_3E0.sub_15E890(&var_AC);
        }
        RwV3dSubMacro(&var_B8, &var_18, &var_AC);
        var_BC = RwV3dLength((RwV3d *)&var_B8);
        RwV3dScaleMacro(&var_B8, &var_B8, 1.0f / var_BC);
        sub_1213D0(&var_B8, &var_100);
        if (unk_2C_1)
            var_104 = 0x9A142; // not an address: line test flags
        else
            var_104 = 0x9A141; // not an address: line test flags
        var_114 = vf_14C() > var_BC * 0.7 ? vf_14C() : var_BC * 0.7;
        var_118 = 0;
        var_11C = 0;
        while (!var_118)
        {
#ifdef CODFH_SP // shape: block-scoped
            RwMatrix var_160;
            RwReal var_180;
            RwV3d var_1A8;
#endif
            var_160 = var_100;
            var_180 = frand_range(-vf_164() * get_aim_spread_multiplier(),
                                  vf_164() * get_aim_spread_multiplier());
            RwMatrixRotate(&var_160, &var_160.up, var_180, rwCOMBINEPOSTCONCAT);
            var_180 = frand_range(-vf_168() * get_aim_spread_multiplier(),
                                  vf_168() * get_aim_spread_multiplier());
            RwMatrixRotate(&var_160, &var_160.right, var_180, rwCOMBINEPOSTCONCAT);
            var_1A8 = var_AC;
            RwV3dIncrementScaledMacro(&var_1A8, &var_160.at, var_114);
            if (sub_D2FC0(&var_AC, &var_1A8, var_C, 0, 0, var_104, 1, 1,
                          0x180000, 1, 0)) // not an address: line test flags
            {
                var_11C++;
                if (var_11C >= 2)
                {
                    var_118 = 1;
                    var_8 = 0;
                }
            }
            else
            {
                unk_3E0.aim_at(&var_1A8);
                var_118 = 1;
            }
        }
    }
    else
    {
        unk_3E0.stop_aiming(0);
    }
    return var_8;
}
// match: ?vf_190@type_3DAFC8@@UAEXH@Z @ 0x00139450
// sp-match: ?vf_190@type_3DAFC8@@UAEXH@Z @ 0x000E6430
// The base's, then its search records cleared unless unk_28_5 is set.
void type_3DAFC8::vf_190(RwInt32 arg_0)
{
    type_3D3548::vf_190(arg_0);
    if (!unk_28_5)
        memset(&unk_1DDC, 0, sizeof(unk_1DDC));
}
// match: ?vf_1A0@type_3DAFC8@@UAEXH@Z @ 0x00139490
// sp-match: ?vf_1A0@type_3DAFC8@@UAEXH@Z @ 0x000E6460
// Likewise.
void type_3DAFC8::vf_1A0(RwInt32 arg_0)
{
    type_3D3548::vf_1A0(arg_0);
    if (!unk_28_5)
        memset(&unk_1DDC, 0, sizeof(unk_1DDC));
}
extern RwReal flt_429C88;
// match: ?vf_210@type_3DAFC8@@UAEXPAUtype_D05C0@@@Z @ 0x001394D0
// sp-match: ?vf_210@type_3DAFC8@@UAEXPAUtype_D05C0@@@Z @ 0x000E6490
// Raises the step (a quarter of it in mode 1 of unk_1D28) with flags 3 and
// 5 set and 1 and 7 clear.
void type_3DAFC8::vf_210(type_D05C0 *arg_0)
{
    if (unk_28_3 && unk_28_5)
    {
        if (unk_28_1)
            return;
        if (!unk_28_7)
        {
            if (unk_1D28 == 1)
                arg_0->unk_00.y += flt_429C88 * arg_0->unk_48;
            else
                arg_0->unk_00.y += arg_0->unk_48;
        }
    }
}
// match: ?sub_139550@type_3DAFC8@@QAEX_N@Z @ 0x00139550
// sp-match: ?sub_139550@type_3DAFC8@@QAEX_N@Z @ 0x000E64D0
// "SetFiveWayBlend" mode 0: its flag, cleared blend weights, and the
// animation queued before the newest when turned on.
void type_3DAFC8::sub_139550(bool arg_0)
{
    RwInt32 var_4;
    RwInt32 local_8;           // unused; the image reserves its slot, as
                               // type_3D32F8::sub_76860's

    unk_824 = (unk_824 & ~1) | (arg_0 ? 1 : 0);
    unk_1D4C = -1;
    for (var_4 = 0; var_4 < 5; var_4++)
        unk_1D50[var_4] = 0;
    if (arg_0 && unk_284->sub_76920())
        unk_1D4C = unk_284->get_unk_34_id(0);
}
// match: ?sub_139620@type_3DAFC8@@QAEXXZ @ 0x00139620
// sp-match: ?sub_139620@type_3DAFC8@@QAEXXZ @ 0x000EAE80
// Five-way blend mode 0 (flag 1 of unk_824): ends when its first animation
// has ended; starts its five animations after unk_1D4C when none run,
// taking the origin (event 5) and the directions (event 6) from their
// events and bringing the directions into the first one's frame (at z 1);
// then weights the two directions either side of where it aims (vf_244,
// sub_13A1F0) by their angles (sub_140490) and blends them (sub_13A070).
void type_3DAFC8::sub_139620()
{
    RwInt32 var_8;
    RwInt32 var_C;
    RwInt32 var_10;
    type_783F0_04 *var_14;
    RwV3d var_20;
    RwMatrix var_60;
    RwMatrix var_A0;
    RwInt32 var_A4;
    RwV3d var_C0;
    type_140490 var_D0;
    RwInt32 var_D4;
    RwInt32 var_D8;
    RwInt32 var_DC;
    RwReal var_F0[5];
    type_140490 var_100;
    type_140490 var_120;
    type_140490 var_130;
    type_140490 var_170;
#ifdef CODFH_SP // the aim's locals (vf_244's in multiplayer), at the top for single player's frame
    RwMatrix aim_frame;
    RwMatrix ltm;
    RwV3d line[2];              // the frame's origin and the aim point, one array (slot order)
    RwReal scale;
    type_3DC9B0 *mounted;
    RwFrame *frame;             // read first, as vf_244 does (the LTM copy's schedule)
#endif

    if (!(unk_824 & 1))
        return;
    if (unk_1D50[0] && !unk_284->sub_76E00(unk_1D50[0]))
    {
        unk_824 &= ~1;
        for (var_8 = 0; var_8 < 5; var_8++)
            unk_1D50[var_8] = 0;
        return;
    }
#ifdef CODFH_SP // single player also ends unless the newest queued animation is 5 (SP 0xEAEF6)
    if (unk_284->unk_34[(unk_284->unk_20 + unk_284->unk_24 - 1) % type_7C8D0_ring_size].unk_08_0 != 5)
    {
        unk_824 &= ~1;
        return;
    }
#endif
    if (!unk_1D50[0])
    {
        var_C = 0;
        var_10 = 0;
        while (var_C < unk_1D4C + 5)
        {
            var_10 = unk_284->sub_7C3E0(0, var_10);
            if (var_C >= unk_1D4C)
            {
                unk_1D50[var_C - unk_1D4C] = var_10;
                if (var_C == unk_1D4C)
                {
                    var_14 = unk_284->sub_7C480(var_10, 0, 5);
#ifdef CODFH_SP // single player stops the blend (sub_139550) when an event is missing (SP 0xEAFA7)
                    if (!var_14)
                    {
                        sub_139550(false);
                        return;
                    }
                    var_20 = var_14->unk_08_v;
                    unk_1D64 = var_20;
                    if (unk_284->unk_12 & 4)
                        unk_1D64.x *= -1.0f;
#else
                    if (var_14)
                    {
                        var_20 = var_14->unk_08_v;
                        unk_1D64 = var_20;
                        if (unk_284->unk_12 & 4)
                            unk_1D64.x *= -1.0f;
                    }
#endif
                }
                var_14 = unk_284->sub_7C480(var_10, 0, 6);
#ifdef CODFH_SP // and stores the direction at var_C itself (SP 0xEAFFC, 0xEB00B)
                if (!var_14)
                {
                    sub_139550(false);
                    return;
                }
                unk_1D70[var_C] = var_14->unk_08_v;
                if (unk_284->unk_12 & 4)
                    unk_1D70[var_C].x *= -1.0f;
#else
                if (var_14)
                {
                    unk_1D70[var_C - unk_1D4C] = var_14->unk_08_v;
                    if (unk_284->unk_12 & 4)
                        unk_1D70[var_C].x *= -1.0f;
                }
#endif
            }
            var_C++;
        }
        var_60.at = unk_1D70[0];
        var_60.up = v3d_3DAED0;
        RwV3dCrossProductMacro(&var_60.right, &var_60.up, &var_60.at);
        var_60.pos.x = 0.0f;
        var_60.pos.y = 0.0f;
        var_60.pos.z = 0.0f;
        RwMatrixOptimize(&var_60, 0);
        RwMatrixInvert(&var_A0, &var_60);
        for (var_A4 = 1; var_A4 < 5; var_A4++)
        {
            RwV3d var_B0;
            RwReal var_B4;

            RwV3dTransformVector(&var_B0, &unk_1D70[var_A4], &var_A0);
            var_B4 = 1.0f / var_B0.z;
            var_B0.x *= var_B4;
            var_B0.y *= var_B4;
            var_B0.z = 1.0f;
            unk_1D70[var_A4] = var_B0;
        }
    }
#ifdef CODFH_SP // single player has no vf_244: it aims here, in the first direction's frame
                // moved by unk_1D64, and carries the line to z 1 (SP 0xEB1BA)
    {
        aim_frame.at = unk_1D70[0];
        aim_frame.up = v3d_3DAED0;
        RwV3dCrossProductMacro(&aim_frame.right, &aim_frame.up, &aim_frame.at);
        aim_frame.pos.x = 0.0f;
        aim_frame.pos.y = 0.0f;
        aim_frame.pos.z = 0.0f;
        RwMatrixOptimize(&aim_frame, 0);
        frame = unk_338.unk_08;
        ltm = *RwFrameGetLTM(frame);
        RwMatrixTranslate(&ltm, &unk_1D64, rwCOMBINEPRECONCAT);
        RwMatrixTransform(&ltm, &aim_frame, rwCOMBINEPRECONCAT);
        RwMatrixInvert(&aim_frame, &ltm);
        if (get_unk_61C())
        {
            mounted = (type_3DC9B0 *)unk_618.sub_D4910();
            if (mounted)
                mounted->sub_16A580(&line[1]);
        }
        else if (unk_3E0.unk_00)
            unk_3E0.sub_15E9E0(&line[1]);
        else
            return;
        var_D0 = *(type_140490 *)&unk_1D70[0];
        line[0] = ltm.pos;
        unk_1DC8 = line[1];
        sub_1414C0(&line[0], &line[0], &aim_frame);
        sub_1414C0(&line[1], &line[1], &aim_frame);
        if (line[1].z > 0.0f)
        {
            scale = 1.0f / line[1].z;
            var_D0.z = 1.0f;
            var_D0.x = (line[1].x - line[0].x) * scale + line[0].x;
            var_D0.y = (line[1].y - line[0].y) * scale + line[0].y;
        }
    }
#else
    vf_244(&var_C0);
    var_D0.x = var_C0.x;
    var_D0.y = var_C0.y;
    var_D0.z = var_C0.z;
    var_D0.w = 1.0f;
#endif
    var_D4 = 0;
    var_D8 = 0;
    for (var_DC = 0; var_DC < 5; var_DC++)
        var_F0[var_DC] = 0.0f;
    var_100 = *(type_140490 *)&v3d_3DAEDC;
    switch (sub_13A1F0((RwV3d *)&var_D0, unk_1D70))
    {
    case 0:
        var_120 = *(type_140490 *)&unk_1D70[4];
        var_130 = *(type_140490 *)&unk_1D70[1];
        var_D4 = 4;
        var_D8 = 1;
        break;
    case 1:
        var_120 = *(type_140490 *)&unk_1D70[1];
        var_130 = *(type_140490 *)&unk_1D70[2];
        var_D4 = 1;
        var_D8 = 2;
        break;
    case 2:
        var_120 = *(type_140490 *)&unk_1D70[2];
        var_130 = *(type_140490 *)&unk_1D70[3];
        var_D4 = 2;
        var_D8 = 3;
        break;
    case 3:
        var_120 = *(type_140490 *)&unk_1D70[3];
        var_130 = *(type_140490 *)&unk_1D70[4];
        var_D4 = 3;
        var_D8 = 4;
        break;
    }
    var_100.x = var_100.y = var_100.z = 0.0f;
    var_120.x = atan(var_120.x / var_120.z);
    var_120.y = atan(var_120.y / var_120.z);
    var_120.z = 0.0f;
    var_130.x = atan(var_130.x / var_130.z);
    var_130.y = atan(var_130.y / var_130.z);
    var_130.z = 0.0f;
    var_D0.x = atan(var_D0.x / var_D0.z);
    var_D0.y = atan(var_D0.y / var_D0.z);
    var_D0.z = 0.0f;
    sub_140490(&var_100, &var_120, &var_130, &var_D0, &var_170);
    var_F0[0] = var_170.x;
    var_F0[var_D4] = var_170.y;
    var_F0[var_D8] = var_170.z;
#ifdef CODFH_SP // single player's sub_13A070 takes no blend (SP 0xE6580 ends ret 8)
    sub_13A070(unk_1D50, var_F0);
#else
    sub_13A070(unk_1D50, var_F0, 1.0f);
#endif
}
// match: ?vf_244@type_3DAFC8@@UAEPAURwV3d@@PAU2@@Z @ 0x00139E50
// Where its weapon (or mounted weapon) aims, for the five-way blend: the
// aim point becomes the head's target (unk_1DC8); in its frame moved by
// unk_1D64, the line from the frame's origin to it is carried to 100
// forward, else the first blend direction. Returns arg_0.
RwV3d *type_3DAFC8::vf_244(RwV3d *arg_0)
{
    RwReal var_C4;
    RwReal var_C0;
    RwV3d var_BC[2];
    RwV3d var_A4;
    type_3DC9B0 *var_98;
    RwMatrix var_90;
    RwMatrix var_50;
    RwFrame *var_8;

    var_8 = unk_338.unk_08;
    var_50 = *RwFrameGetLTM(var_8);
    RwMatrixTranslate(&var_50, &unk_1D64, rwCOMBINEPRECONCAT);
    RwMatrixInvert(&var_90, &var_50);
    if (get_unk_61C())
    {
        var_98 = (type_3DC9B0 *)unk_618.sub_D4910();
        if (var_98)
            var_98->sub_16A580(&var_A4);
    }
    else
    {
        unk_3E0.sub_15E9E0(&var_A4);
    }
    var_BC[0] = unk_1D70[0];
    var_BC[1] = var_50.pos;
    unk_1DC8 = var_A4;
    RwV3dTransformPoints(&var_BC[1], &var_BC[1], 1, &var_90);
    RwV3dTransformPoints(&var_A4, &var_A4, 1, &var_90);
    if (var_A4.z - var_BC[1].z > 0.0f)
    {
        var_C0 = var_A4.z - var_BC[1].z;
        var_C4 = (100.0f - var_BC[1].z) / var_C0;
        var_BC[0].z = 100.0f;
        var_BC[0].x = (var_A4.x - var_BC[1].x) * var_C4 + var_BC[1].x;
        var_BC[0].y = (var_A4.y - var_BC[1].y) * var_C4 + var_BC[1].y;
    }
    *arg_0 = var_BC[0];
    return arg_0;
}
// match: ?sub_13A070@type_3DAFC8@@QAEXPAHPAMM@Z @ 0x0013A070
// sp-match: ?sub_13A070@type_3DAFC8@@QAEXPAHPAMM@Z @ 0x000E6580
// Blends the five animations arg_0 towards the layered weights arg_4 (the
// last on top) by arg_8, as type_3D32F8::sub_76E70 does but without its
// cut-off for small weights.
#ifdef CODFH_SP // single player's sub_13A070 takes no blend (SP 0xE6580 ends ret 8)
void type_3DAFC8::sub_13A070(RwInt32 *arg_0, RwReal *arg_4)
#else
void type_3DAFC8::sub_13A070(RwInt32 *arg_0, RwReal *arg_4, RwReal arg_8)
#endif
{
    RwReal var_4;
    RwInt32 v8;
    RwReal fp_1C[5];
    bool var1D;

    var1D = false;
    fp_1C[0] = 1.0f;
    fp_1C[4] = arg_4[4];
    for (v8 = 3; v8 > 0; v8--) {
        if (var1D || arg_4[v8] == 0)
            fp_1C[v8] = 0;
        else {
            RwInt32 var_24;

            var_4 = 1.0f;
            for (var_24 = v8 + 1; var_24 < 5; var_24++)
                var_4 *= 1.0f - fp_1C[var_24];
            if (var_4 == 0)
                fp_1C[v8] = 0;
            else
                fp_1C[v8] = arg_4[v8] / var_4;
            if (fp_1C[v8] >= 1.0f) {
                fp_1C[v8] = 1.0f;
                var1D = true;
            }
        }
    }
#ifdef CODFH_SP // single player's sub_13A070 takes no blend (SP 0xE6580 ends ret 8)
    for (v8 = 0; v8 < 5; v8++)
        unk_284->sub_79C90(arg_0[v8], fp_1C[v8]);
#else
    for (v8 = 0; v8 < 5; v8++) {
        fp_1C[v8] = arg_8 * fp_1C[v8] + unk_284->sub_7C9A0(arg_0[v8]) * (1.0f - arg_8);
        unk_284->sub_79C90(arg_0[v8], fp_1C[v8]);
    }
#endif
}
// match: ?sub_13A1F0@type_3DAFC8@@QAEHPAURwV3d@@0@Z @ 0x0013A1F0
// sp-match: ?sub_13A1F0@type_3DAFC8@@QAEHPAURwV3d@@0@Z @ 0x000E66B0
// The last of the four directions arg_4[1] to arg_4[4] at which the turn
// towards *arg_0 changes sides (by the z of their cross products), from 0.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_3DAFC8::sub_13A1F0(RwV3d *arg_0, RwV3d *arg_4)
{
    RwV3d var_C = v3d_3DAEDC;
    RwInt32 v10;
    RwInt32 local_14;
    RwReal var18;
    RwV3d var24;
    RwV3d var_54[4];
    RwV3d var_60;

    local_14 = 0;
    var18 = 0.0f;
    for (v10 = 0; v10 < 4; v10++)
        var_54[v10] = arg_4[v10 + 1];
    var_60 = *arg_0;
    var18 = 1.0f;
    for (v10 = 0; v10 < 4; v10++)
    {
        RwV3dCrossProductMacro(&var24, &var_54[v10], &var_60);
        if (var18 >= 0.0f && var24.z < 0.0f)
            local_14 = v10;
        var18 = var24.z;
    }
    return local_14;
}
// match: ?sub_13A340@type_3DAFC8@@QAEX_N@Z @ 0x0013A340
// sp-match: ?sub_13A340@type_3DAFC8@@QAEX_N@Z @ 0x000E6800
// "SetFiveWayBlend" mode 1: likewise with flag 2, unk_1D4E and unk_1DAC.
void type_3DAFC8::sub_13A340(bool arg_0)
{
    RwInt32 var_4;
    RwInt32 local_8;           // unused; the image reserves its slot, as
                               // sub_139550's

    unk_824 = (unk_824 & ~2) | (arg_0 ? 2 : 0);
    unk_1D4E = -1;
    for (var_4 = 0; var_4 < 5; var_4++)
        unk_1DAC[var_4] = 0;
    if (arg_0 && unk_284->sub_76920())
        unk_1D4E = unk_284->get_unk_34_id(0);
}
// match: ?sub_13A410@type_3DAFC8@@QAEXXZ @ 0x0013A410
// sp-match: ?sub_13A410@type_3DAFC8@@QAEXXZ @ 0x000E68B0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Five-way blend mode 1 (flag 2 of unk_824): ends when its first animation
// has ended; starts its five animations after unk_1D4E when none run (then
// blending at once); weights them by the angle unk_1DC0 (its cosine and
// sine split between the side animations, scaled by 1/sqrt 2) and blends
// them (sub_13A070).
void type_3DAFC8::sub_13A410()
{
    RwInt32 lcl_38;
    RwInt32 r34;
    RwInt32 lv_30;
    RwReal fp_2C[5];
    RwInt32 m_18;
    RwReal ebp_14;
    RwInt32 lv_10;
    RwReal slot_C;
    RwReal bp_8;
    RwInt32 bp_4;

    {
        // Unused; the image reserves two slots after the others.
        RwInt32 ebp_3C;
        RwInt32 fp_40;
    }
    ebp_14 = 0.5f;
    if (!(unk_824 & 2))
        return;
    if (unk_1DAC[0] && !unk_284->sub_76E00(unk_1DAC[0]))
    {
        unk_824 &= ~2;
        for (lv_30 = 0; lv_30 < 5; lv_30++)
            unk_1DAC[lv_30] = 0;
        return;
    }
    if (!unk_1DAC[0])
    {
        r34 = 0;
        lcl_38 = 0;
        while (r34 < unk_1D4E + 5)
        {
            lcl_38 = unk_284->sub_7C3E0(0, lcl_38);
            if (r34 >= unk_1D4E)
            {
                unk_284->sub_79CE0(lcl_38, true);
                unk_1DAC[r34 - unk_1D4E] = lcl_38;
            }
            r34++;
        }
        ebp_14 = 1.0f;
    }
    bp_4 = 0;
    m_18 = 0;
    for (lv_10 = 0; lv_10 < 5; lv_10++)
        fp_2C[lv_10] = 0.0f;
    slot_C = cos(unk_1DC0);
    bp_8 = sin(unk_1DC0);
    if (slot_C > 0.0f)
    {
        bp_4 = 1;
    }
    else if (slot_C < 0.0f)
    {
        bp_4 = 2;
        slot_C = -slot_C;
    }
    if (bp_8 > 0.0f)
    {
        m_18 = 3;
    }
    else if (bp_8 < 0.0f)
    {
        m_18 = 4;
        bp_8 = -bp_8;
    }
    fp_2C[bp_4] = slot_C * 0.70710677f;
    fp_2C[m_18] = bp_8 * 0.70710677f;
    fp_2C[0] = 1.0f - fp_2C[bp_4] - fp_2C[m_18];
#ifdef CODFH_SP // single player's sub_13A070 takes no blend (SP 0xE6580 ends ret 8)
    sub_13A070(unk_1DAC, fp_2C);
#else
    sub_13A070(unk_1DAC, fp_2C, ebp_14);
#endif
}
// match: ?vf_1CC@type_3DAFC8@@UAEXH@Z @ 0x0013A680
// sp-match: ?vf_1CC@type_3DAFC8@@UAEXH@Z @ 0x000E6A40
// Drops its pickup once (unk_1D48): its trigger's (unk_14C, unk_150), or
// its own when set (unk_810, unk_814), at its weapon's model levelled to the
// ground ahead (its heading and the slope 100 ahead), or at its frame; kinds
// 0x4B to 0x4D, 0x5A and 0x5B upright; it floats up 20 with arg_0. Its
// weapon is put away and the drop sound played.
void type_3DAFC8::vf_1CC(RwInt32 arg_0)
{
    RwFrame *l90;
    RwMatrix *var_8C;
    RwV3d local_88;
    RwMatrix *loc7C;
    RwV3d local_78;
    RwReal var_6C;
    RwMatrix *v68;
    RwReal bp_64;
    RwReal v60;
    RwReal bp_5C;
#ifndef CODFH_SP // single player declares these in the blocks that use them (SP 0xE6A40)
    RwV3d frm_58;
#endif
    RwReal lv_4C;
    RwV3d stk_48;
    RwV3d var3C;
    RwV3d lcl_30;
    RwV3d slot_24;
    RwFrame *var18;
    RwInt32 stk_14;
    RwReal l10;
    RpClump *local_C;
    RwInt32 lv_8;
    SoldierTrigger *var_4;

    if (!unk_1D48)
    {
        var_4 = (SoldierTrigger *)unk_344.unk_08;
        if (var_4 && var_4->unk_150 && var_4->unk_14C != -1)
        {
            var18 = 0;
            local_C = unk_3E0.unk_10.unk_08;
            if (local_C)
            {
#ifdef CODFH_SP // shape: block-scoped
                RwV3d frm_58;
#endif
                v60 = 0.0f;
                lv_4C = 0.0f;
                frm_58.x = 0.0f;
                frm_58.y = 0.0f;
                frm_58.z = 100.0f;
                var18 = RpClumpGetFrame(local_C);
                v68 = RwFrameGetMatrix(var18);
                RwV3dScaleMacro(&lcl_30, &v68->at, 100.0f);
                slot_24 = *RwMatrixGetPos(v68);
                RwV3dAddMacro(&stk_48, &lcl_30, &slot_24);
                bp_64 = atan2(lcl_30.x, lcl_30.z);
                v60 = bp_64 * 57.295776f;
                v60 = sub_13F9E0(v60);
                var_6C = sub_CC8E0(&slot_24);
                sub_13FFA0(&frm_58, (RwV3d *)&v3d_3DAED0, bp_64);
                RwV3dAddMacro(&stk_48, &frm_58, &slot_24);
                bp_5C = sub_CC8E0(&stk_48);
                lv_4C = atan2(var_6C - bp_5C, 100.0f) * 57.295776f;
                lv_4C = sub_13F9E0(lv_4C);
                var3C = *RwMatrixGetPos(v68);
                RwMatrixSetIdentityMacro(v68);
                RwMatrixRotate(v68, &v3d_3DAED0, v60, rwCOMBINEPRECONCAT);
                RwMatrixRotate(v68, &v3d_3DAEC4, lv_4C, rwCOMBINEPRECONCAT);
                *RwMatrixGetPos(v68) = var3C;
                RwFrameUpdateObjects(var18);
            }
            else
            {
                l90 = unk_338.unk_08;
                var18 = l90;
            }
            stk_14 = var_4->unk_14C;
            lv_8 = var_4->unk_150;
            if (unk_810 != -1 && unk_814)
            {
                stk_14 = unk_810;
                lv_8 = unk_814;
            }
            if (stk_14 == 0x4B || stk_14 == 0x4C || stk_14 == 0x4D || stk_14 == 0x5A
                || stk_14 == 0x5B)
            {
                loc7C = RwFrameGetMatrix(var18);
                local_78 = *RwMatrixGetPos(loc7C);
                RwMatrixSetIdentityMacro(loc7C);
                *RwMatrixGetPos(loc7C) = local_78;
            }
            if (stk_14 == 0x4B || stk_14 == 0x4C || stk_14 == 0x4D || stk_14 == 0x5A
                || stk_14 == 0x5B)
            {
                var_8C = RwFrameGetMatrix(var18);
                local_88 = *RwMatrixGetPos(var_8C);
                RwMatrixSetIdentityMacro(var_8C);
                *RwMatrixGetPos(var_8C) = local_88;
            }
            l10 = -1.0f;
            if (arg_0)
                l10 = 20.0f;
            sub_FABC0(stk_14, lv_8, RwFrameGetMatrix(var18), l10, 0, 0);
            unk_3E0.sub_15D360();
            dword_4B1E98.sub_8A980(&dword_4B1C90, 0, 0, sub_CD550(), 0, 0);
        }
        unk_1D48 = 1;
    }
}
// match: ?vf_224@type_3DAFC8@@UAE_NPAUtype_3DF8D8@@HPAH@Z @ 0x0013AC60
// sp-match: ?vf_224@type_3DAFC8@@UAE_NPAUtype_3DF8D8@@HPAH@Z @ 0x000E6DA0
// The base's set-up of its model from the definition arg_0, then its
// atomic's bounding radius (150) and flags, and its weapon class.
bool type_3DAFC8::vf_224(type_3DF8D8 *arg_0, RwInt32 arg_4, RwInt32 *arg_8)
{
    RpAtomic *var_4;
    RwInt32 local_8;

    type_3D3548::vf_224(arg_0, 0, 0);
    var_4 = unk_274.unk_08;
    var_4->boundingSphere.radius = 150.0f;
    ((RwObject *)var_4)->flags = 1;
    local_8 = ((type_1917A0 *)arg_0)->unk_44;
    unk_290 = local_8;
    return true;
}
// match: ?vf_228@type_3DAFC8@@UAE_NXZ @ 0x0013ACC0
// sp-match: ?vf_228@type_3DAFC8@@UAE_NXZ @ 0x0007B5D0
bool type_3DAFC8::vf_228()
{
    type_3D3548::vf_228();
    return true;
}
// match: ?sub_13ACE0@type_3DAFC8@@QAEXPAURpClump@@@Z @ 0x0013ACE0
// sp-match: ?sub_13ACE0@type_3DAFC8@@QAEXPAURpClump@@@Z @ 0x000E6DE0
// Holds a copy of the clump arg_0 in unk_828 (none for 0), its hierarchy
// updating its modelling matrices.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3DAFC8::sub_13ACE0(RpClump *arg_0)
{
    RpClump *var_4;
    RwUInt32 v8;
    RpHAnimHierarchy *varC;

    unk_828.sub_129940(0);
    if (arg_0)
    {
        var_4 = RpClumpClone(arg_0);
        if (var_4)
        {
            unk_828.sub_129620(var_4);
            unk_828.sub_129690(this);
            varC = sub_16D970(unk_828.get_unk_08());
            sub_79270(unk_828.get_unk_08(), 0);
            v8 = varC->flags;
            v8 |= rpHANIMHIERARCHYUPDATEMODELLINGMATRICES;
            varC->flags = v8;
        }
    }
}
// match: ?sub_13ADA0@type_3DAFC8@@QAEXPAURpClump@@@Z @ 0x0013ADA0
// sp-match: ?sub_13ADA0@type_3DAFC8@@QAEXPAURpClump@@@Z @ 0x000E6E50
// Holds a copy of the clump arg_0 in unk_834 at the identity (none for 0).
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3DAFC8::sub_13ADA0(RpClump *arg_0)
{
    RpClump *var_4;
    RwFrame *local_8;

    unk_834.sub_129940(0);
    if (arg_0)
    {
        var_4 = RpClumpClone(arg_0);
        if (var_4)
        {
            local_8 = RpClumpGetFrame(var_4);
            if (!local_8)
                local_8 = RwFrameCreate();
            RwFrameSetIdentity(local_8);
            unk_834.sub_129620(var_4);
            unk_834.sub_129690(this);
        }
    }
    else
    {
        unk_834.sub_129620(0);
    }
}
// match: ?vf_170@type_3DAFC8@@UAEXHHHH@Z @ 0x0013AE40
// sp-match: ?vf_170@type_3DAFC8@@UAEXHHHH@Z @ 0x000EB680
// Its handler for the message arg_0 with the data arg_4 (unless its
// flag 13 of unk_88 is set): 1 (arg_8 the animation that ended, arg_C its
// player) replays its own animation unk_298 when the player loops; 0xB54
// plays the animation of *arg_4; 0x516 spawns the particle system at a
// bone of its clump, its held clump, its mounted weapon or its prop;
// 0x7D0 fires or stops its weapon; 0x960 shows or hides its weapons'
// parts and sets vf_18C; 0x9C4 sets a hatch of the vehicle it rides;
// 0xA8C mounts or dismounts its mounted weapon or sets unk_620; 0xA28 its
// vision; the rest go to the base with no player.
void type_3DAFC8::vf_170(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C)
{
    type_13AE40_msg *var_14;
    type_13AE40_msg *var_20;
    RpHAnimHierarchy *var_24;
    RpClump *var_28;
    RwMatrix var_70;
    RpHAnimHierarchy *var_74;
    RpClump *var_78;
    type_129940 *var_7C;
    RpClump *var_80;
    type_13AE40_msg *var_84;
    type_13AE40_msg *var_8C;
    RwInt32 var_90;
    type_13AE40_msg *var_94;
    type_13AE40_msg *var_98;
    type_3D3548 *var_B0;
    type_3DC048 *var_B4;
    bool var_B5;
    type_13AE40_hatch *var_BC;
    type_13AE40_msg *var_C0;
    type_13AE40_msg *var_C8;
    type_3D3548 *var_D0;
    AIData *var_D4;
    type_F8350 *var_D8;
    type_3D3548 *var_DC;
    type_3D3548 *var_E0;
    AIData *var_E4;
    type_F8350 *var_E8;
    type_3D3548 *var_EC;
    type_13AE40_msg *var_F0;
    type_13AE40_vision *var_F4;
    type_3D3548 *var_100;
    type_3DBC78 *var_104;

#if defined(CODFH_DRAW_TRIGGERS) && !defined(CODFH_SP)
    // (the debug tools: the bots' animation events counted by id, port/src/debug/trigtools.cpp)
    if (TrigIsAiSoldier(this))
        TrigBotAnimEvent(arg_0, unk_88_13);
#endif
    if (unk_88_13)
        return;
    switch ((RwUInt32)arg_0)
    {
    case 1:
        if (((type_7C8D0 *)arg_C)->unk_12 & 2)
        {
            RwInt32 var_C;
            RwInt32 var_10;

            if (unk_298 && unk_298 != arg_8 && sub_77B70(unk_298, (void **)(&var_10), (void **)(&var_C)))
            {
                unk_28C->sub_794C0(0.1f);
                unk_28C->sub_796A0((RtAnimAnimation *)var_10, unk_298, 0, (type_783F0 *)var_C, 0, 1.0f,
                                   1.0f);
                unk_805 = 0;
            }
        }
        else
        {
            type_3D3548::vf_170(arg_0, arg_4, arg_8, 0);
        }
        break;
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
            unk_805 = 8;
        }
        break;
    }
    case 0x516:
        var_20 = (type_13AE40_msg *)arg_4;
        if (unk_28_13)
        {
            var_24 = unk_284->unk_18;
            var_28 = unk_25C.unk_08;
            if (sub_EC310(var_28, var_24, &var_70, var_20->unk_00, 0, 0))
            {
                sub_F2FF0(var_20->unk_0C, &var_70, 0, 0, 0, 0);
            }
            else
            {
                var_74 = unk_284->unk_18;
                var_78 = unk_828.unk_08;
                if (sub_EC310(var_78, var_74, &var_70, var_20->unk_00, 0, 0))
                {
                    sub_F2FF0(var_20->unk_0C, &var_70, 0, 0, 0, 0);
                }
                else if (unk_618.sub_D4910())
                {
                    ((type_3DC9B0 *)unk_618.sub_D4910())->sub_169F30(&var_70, -1);
                    sub_F2FF0(var_20->unk_0C, &var_70, 0, 0, 0, 0);
                }
                else if (unk_35C[0].sub_D4910())
                {
                    var_7C = &unk_35C[0].sub_D4910()->unk_25C;
                    var_80 = var_7C->unk_08;
                    sub_EC2D0(var_80, (RwInt32)&var_70, var_20->unk_00, 0, 0);
                    sub_F2FF0(var_20->unk_0C, &var_70, 0, 0, 0, 0);
                }
            }
        }
        break;
    case 0x7D0:
        var_84 = (type_13AE40_msg *)arg_4;
        switch (var_84->unk_00)
        {
        case 0:
            vf_1B0(0);
            break;
        case 1:
        case 2:
        case 3:
            if (unk_8A0.unk_524)
            {
                if (var_84->unk_04)
                    unk_3E0.sub_15D510(1, (RwInt32)&var_84->unk_04);
                else
                    unk_3E0.sub_15D510(1, 0);
            }
            break;
        }
        break;
    case 0x76C:
#ifdef CODFH_SP
        // Single player handles it (SP 0xEB87D): 0 calls sp_sub_E4BB0; 1
        // calls sp_sub_E4B50 and sets the grenade bone unk_5E8 from unk_04.
        var_8C = (type_13AE40_msg *)arg_4;
        switch (var_8C->unk_00)
        {
        case 0:
            sp_sub_E4BB0();
            break;
        case 1:
            sp_sub_E4B50();
            switch (var_8C->unk_04)
            {
            case 1:
                unk_5E8 = 0x9B;
                break;
            default:
                unk_5E8 = 0xFF;
                break;
            }
            break;
        }
        break;
#else
#if defined(CODFH_DRAW_TRIGGERS)
        // (the port's debug tools: an AI soldier's grenade events taken as single player takes
        // them, port/src/debug/trigtools.cpp's bots)
        if (TrigIsAiSoldier(this))
        {
            var_8C = (type_13AE40_msg *)arg_4;
            if (var_8C->unk_00 >= 0 && var_8C->unk_00 < 2)
                g_anTrigGrenadeEvents[var_8C->unk_00]++;
            if (var_8C->unk_00 == 0)
                sp_sub_E4BB0();
            else if (var_8C->unk_00 == 1)
            {
                sp_sub_E4B50();
                unk_5E8 = var_8C->unk_04 == 1 ? 0x9B : 0xFF;
            }
        }
#endif
        break;
        // Unreachable: the image has no code here, but its three slots
        // (-0x8C..-0x94) and the registers the next case uses need four
        // register loads into three locals; what it did is unknown.
        var_8C = (type_13AE40_msg *)arg_4;
        var_90 = var_8C->unk_00;
        var_94 = (type_13AE40_msg *)arg_4;
        break;
#endif
    case 0x960:
        var_98 = (type_13AE40_msg *)arg_4;
        switch (var_98->unk_00)
        {
        case 0:
            sub_16E080(unk_3E0.get_unk_18(), -1);
            break;
        case 1:
            sub_16E080(unk_3E0.get_unk_18(), 0);
            break;
        case 2:
            sub_16E080(unk_4E0.get_unk_18(), -1);
            break;
        case 3:
            sub_16E080(unk_4E0.get_unk_18(), 0);
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
        if (!unk_624.sub_D4910())
            break;
        var_B0 = unk_624.sub_D4910();
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
    case 0xA8C:
        var_C8 = (type_13AE40_msg *)arg_4;
        switch (var_C8->unk_00)
        {
        case 0:
            var_D0 = unk_618.sub_D4910();
            if (var_D0 && var_D0->vf_028())
            {
                var_D4 = vf_120();
                var_D8 = var_D4->unk_F60;
                if (var_D8 || (unk_624.sub_D4910() && (var_DC = unk_624.sub_D4910())->vf_010()))
                {
                    if (!sub_13F590(1))
                        sub_13F590(0);
                }
            }
            break;
        case 1:
            var_E0 = unk_618.sub_D4910();
            if (var_E0 && var_E0->vf_028())
            {
                var_E4 = vf_120();
                var_E8 = var_E4->unk_F60;
                if (var_E8 || (unk_624.sub_D4910() && (var_EC = unk_624.sub_D4910())->vf_010()))
                    sub_13F590(0);
            }
            break;
        case 2:
            unk_620 = 1;
            break;
        case 3:
            unk_620 = 0;
            break;
        }
        break;
    case 0xA28:
        var_F0 = (type_13AE40_msg *)arg_4;
        var_F4 = (type_13AE40_vision *)arg_4;
        switch (var_F0->unk_08)
        {
        case 0:
            vf_238(var_F4->unk_00);
            switch (var_F0->unk_04)
            {
            case 0:
                vf_240(0);
                break;
            case 1:
                vf_240(1);
                break;
            }
            break;
        case 1:
            if (!unk_624.sub_D4910())
                break;
            var_100 = unk_624.sub_D4910();
            var_104 = var_100->vf_010();
            if (var_104)
            {
                var_104->vf_23C(var_F4->unk_00);
                switch (var_F0->unk_04)
                {
                case 0:
                    var_104->vf_244(0);
                    break;
                case 1:
                    var_104->vf_244(1);
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
// match: ?vf_0EC@type_3DAFC8@@UAEXHH@Z @ 0x0013B7A0
// sp-match: ?vf_0EC@type_3DAFC8@@UAEXHH@Z @ 0x000E6EC0
// Sets its scene value arg_0 to arg_4 ("SetSceneValue").
void type_3DAFC8::vf_0EC(RwInt32 arg_0, RwInt32 arg_4)
{
    unk_898[arg_0] = (RwInt16)arg_4;
}
// match: ?vf_208@type_3DAFC8@@UAEHHHHMMMH@Z @ 0x0013B7C0
// sp-match: ?vf_208@type_3DAFC8@@UAEHHHHMMMH@Z @ 0x000E6EE0
// Before the base plays an animation (unless arg_8 is clear while one is
// queued): each five-way blend that is on takes the new animation (0) or,
// already holding one, turns off.
RwInt32 type_3DAFC8::vf_208(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwReal arg_C,
                            RwReal arg_10, RwReal arg_14, RwInt32 arg_18)
{
    RwInt32 var_4;             // unused; the image reserves its slot

    if (arg_8 || !unk_284->sub_76920())
    {
        if (unk_824 & 1)
        {
            if (unk_1D4C == -1)
                unk_1D4C = 0;
            else
                unk_824 &= ~1;
        }
        if (unk_824 & 2)
        {
            if (unk_1D4E == -1)
                unk_1D4E = 0;
            else
                unk_824 &= ~2;
        }
    }
    return type_3D3548::vf_208(arg_0, arg_4, arg_8, arg_C, arg_10, arg_14, arg_18);
}
// match: ?vf_0FC@type_3DAFC8@@UAEMXZ @ 0x0013B8A0
// sp-match: ?vf_0FC@type_3DAFC8@@UAEMXZ @ 0x000E6F90
RwReal type_3DAFC8::vf_0FC()
{
    if (unk_874)
        return -0.99999964f;
    return unk_86C;
}
// match: ?vf_100@type_3DAFC8@@UAEMXZ @ 0x0013B8D0
// sp-match: ?vf_100@type_3DAFC8@@UAEMXZ @ 0x000E6FB0
RwReal type_3DAFC8::vf_100()
{
    if (unk_874)
        return -0.99999964f;
    return unk_870;
}
// match: ?vf_10C@type_3DAFC8@@UAEMXZ @ 0x0013B900
// sp-match: ?vf_10C@type_3DAFC8@@UAEMXZ @ 0x000E6FD0
// Its view range (the alerted one while its AI object is alerted) times its
// vision multiplier.
RwReal type_3DAFC8::vf_10C()
{
    if (unk_8A0.unk_520)
        return unk_87C * unk_880;
    return unk_878 * unk_880;
}
// match: ?vf_130@type_3DAFC8@@UAEMXZ @ 0x0013B940
// sp-match: ?vf_130@type_3DAFC8@@UAEMXZ @ 0x000E6FF0
RwReal type_3DAFC8::vf_130()
{
    return unk_888;
}
// match: ?vf_114@type_3DAFC8@@UAEMXZ @ 0x0013B960
// sp-match: ?vf_114@type_3DAFC8@@UAEMXZ @ 0x000E7000
// Its preferred attack range: its alerted view range times its vision
// multiplier, and times unk_884 unless bit 13 of its AI object's unk_49C is
// set.
RwReal type_3DAFC8::vf_114()
{
    if (unk_8A0.unk_49C & 0x2000)
        return unk_87C * unk_880;
    return unk_87C * unk_880 * unk_884;
}
extern RwReal flt_429C8C;
// match: ?vf_250@type_3DAFC8@@UAEMXZ @ 0x0013B9B0
// sp-match: ?vf_250@type_3DAFC8@@UAEMXZ @ 0x000E7030
// Suppresses it: when its suppression time has run out, 60 frames of
// suppression (unk_1D2C) and a new time (unk_1D30), telling its scripts it
// starts; then that it continues. Returns the suppression.
RwReal type_3DAFC8::vf_250()
{
    if (unk_1D30 <= 0.0f)
    {
        unk_1D2C = 60.0f;
        unk_1D30 = 60.0f * flt_429C8C;
        sub_6B5F0("StartSuppression", (type_67620 *)(vf_098()), 0, 0, 0, 0, 1, 0);
    }
    sub_6B5F0("ContinuedSuppression", (type_67620 *)(vf_098()), 0, 0, 0, 0, 1, 0);
    return unk_1D2C;
}
// match: ?vf_104@type_3DAFC8@@UAEXPAURwMatrixTag@@@Z @ 0x0013BA50
// sp-match: ?vf_104@type_3DAFC8@@UAEXPAURwMatrixTag@@@Z @ 0x000E70B0
// Its head's matrix (bone 0xCA) while its animation drives it, else its
// frame's raised by its height by its posture's class (vf_0BC): twice it,
// or once for class 1, or half for class 2.
void type_3DAFC8::vf_104(RwMatrix *arg_0)
{
    RpHAnimHierarchy *var_4;
    RwInt32 loc8;
    RwMatrix *local_C;
    RwFrame *var10;
    RwV3d fp_1C;
    RpClump *ebp_20;

    if (unk_284 && unk_28_13)
    {
        var_4 = unk_284->unk_18;
        local_C = RpHAnimHierarchyGetMatrixArray(var_4);
        loc8 = RpHAnimIDGetIndex(var_4, 0xCA);
        *arg_0 = local_C[loc8];
    }
    else
    {
        ebp_20 = unk_25C.unk_08;
        var10 = RpClumpGetFrame(ebp_20);
        fp_1C.x = fp_1C.z = 0.0f;
        if (vf_0BC() == 0)
            fp_1C.y = unk_48 * 2.0f;
        else if (vf_0BC() == 1)
            fp_1C.y = unk_48;
        else if (vf_0BC() == 2)
            fp_1C.y = unk_48 / 2.0f;
        else
            fp_1C.y = unk_48 * 2.0f;
        *arg_0 = *RwFrameGetLTM(var10);
        RwMatrixTranslate(arg_0, &fp_1C, rwCOMBINEPOSTCONCAT);
    }
}
// match: ?vf_108@type_3DAFC8@@UAEXPAURwV3d@@@Z @ 0x0013BB80
// sp-match: ?vf_108@type_3DAFC8@@UAEXPAURwV3d@@@Z @ 0x000E7190
// Its eye point: its head (bone 0xCA) while its animation drives it, else
// its frame's position raised as vf_104 raises it.
void type_3DAFC8::vf_108(RwV3d *arg_0)
{
    RpHAnimHierarchy *l4;
    RwInt32 var_8;
    RwMatrix *fp_C;
    RwFrame *local_10;
    RwMatrix *stk_14;
    RpClump *loc18;

    if (unk_284 && unk_28_13)
    {
        l4 = unk_284->unk_18;
        fp_C = RpHAnimHierarchyGetMatrixArray(l4);
        var_8 = RpHAnimIDGetIndex(l4, 0xCA);
        *arg_0 = fp_C[var_8].pos;
    }
    else
    {
        loc18 = unk_25C.unk_08;
        local_10 = RpClumpGetFrame(loc18);
        stk_14 = RwFrameGetLTM(local_10);
        *arg_0 = stk_14->pos;
        if (vf_0BC() == 0)
            arg_0->y += unk_48 * 2.0f;
        else if (vf_0BC() == 1)
            arg_0->y += unk_48;
        else if (vf_0BC() == 2)
            arg_0->y += unk_48 / 2.0f;
        else
            arg_0->y += unk_48 * 2.0f;
    }
}
// match: ?vf_110@type_3DAFC8@@UAEXPAURwV3d@@PAUtype_3D3548@@H@Z @ 0x0013BCD0
// sp-match: ?vf_110@type_3DAFC8@@UAEXPAURwV3d@@PAUtype_3D3548@@H@Z @ 0x000E7270
// Its aim point: at a cover node (its AI object in state 6, 0x26 or 0x2A
// with a current node, and arg_8 set), the node's point in the node's frame
// unless arg_4 is behind the node; else bone 0x1C5 at such a node or 0x71
// while its animation drives it; else its frame's position raised by its
// height by its posture's class (a half for 1, a quarter for 2).
void type_3DAFC8::vf_110(RwV3d *arg_0, type_3D3548 *arg_4, RwInt32 arg_8)
{
    AIData *var_8;
    type_F8350 *var_C;
    RwInt32 var_10;
#ifndef CODFH_SP // single player scopes it to a block below (SP 0xE7270)
    RwMatrix var_90;
#endif
    RwV3d var_9C;
    RpHAnimHierarchy *var_A0;
    RwMatrix *var_A4;
    RwInt32 var_AC;
    RpClump *var_B0;
    RwFrame *var_B4;
    RwMatrix *var_B8;

    var_8 = vf_120();
    var_C = var_8->unk_F60;
    if (var_8->sub_238E0(0) && var_C && arg_8)
    {
#ifdef CODFH_SP // shape: block-scoped
        RwMatrix var_90;
#endif
        var_10 = 1;
        RtQuatConvertToMatrix(&var_C->unk_1C, &var_90);
        var_90.pos = var_C->unk_10;
        if (arg_4)
        {
            RwV3dSubMacro(&var_9C, arg_4->sub_CD550(), &var_C->unk_10);
            if (RwV3dDotProductMacro(&var_9C, &var_90.at) <= 0.0)
                var_10 = 0;
        }
        if (var_10)
        {
            sub_F8FE0(var_C, arg_0, 0);
            sub_1414C0(arg_0, arg_0, &var_90);
            return;
        }
    }
    if (unk_284 && unk_28_13)
    {
        var_A0 = unk_284->unk_18;
        var_A4 = RpHAnimHierarchyGetMatrixArray(var_A0);
        var_AC = RpHAnimIDGetIndex(var_A0, var_8->sub_238E0(0) && var_C ? 0x1C5 : 0x71);
        *arg_0 = var_A4[var_AC].pos;
    }
    else
    {
        var_B0 = unk_25C.unk_08;
        var_B4 = RpClumpGetFrame(var_B0);
        var_B8 = RwFrameGetLTM(var_B4);
        *arg_0 = var_B8->pos;
        if (vf_0BC() == 0)
            arg_0->y += unk_48;
        else if (vf_0BC() == 1)
            arg_0->y += unk_48 / 2.0f;
        else if (vf_0BC() == 2)
            arg_0->y += unk_48 / 4.0f;
        else
            arg_0->y += unk_48;
    }
}
// match: ?vf_0BC@type_3DAFC8@@UAEHXZ @ 0x0013C120
// sp-match: ?vf_0BC@type_3DAFC8@@UAEHXZ @ 0x00112CA0
// The class (1, 2 or 0) of its posture (vf_0AC).
RwInt32 type_3DAFC8::vf_0BC()
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
// match: ?vf_07C@type_3DAFC8@@UAEHCPAURpIntersection@@PAMH@Z @ 0x0013C1C0
// sp-match: ?vf_07C@type_3DAFC8@@UAEHCPAURpIntersection@@PAMH@Z @ 0x000E7560
// The line (arg_0 1) or sphere of arg_4 against its bone boxes (13 of
// them while its animation drives it, else one box around it, its radius
// across and as high as vf_104 raises its head); -1 for a miss or while
// unk_88_1 is clear.
RwInt32 type_3DAFC8::vf_07C(RwInt8 arg_0, RpIntersection *arg_4, RwReal *arg_8, RwInt32 arg_C)
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

            var_30.unk_00 = -unk_4C / 2.0f;
            var_30.unk_04 = 0.0f;
            var_30.unk_08 = -unk_4C / 2.0f;
            var_30.unk_0C = 0.0f;
            var_30.unk_10 = unk_4C / 2.0f;
            if (vf_0BC() == 0)
                var_30.unk_14 = unk_48 * 2.0f;
            else if (vf_0BC() == 1)
                var_30.unk_14 = unk_48;
            else if (vf_0BC() == 2)
                var_30.unk_14 = unk_48 / 2.0f;
            else
                var_30.unk_14 = unk_48 * 2.0f;
            var_30.unk_18 = unk_4C / 2.0f;
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

            var_60.unk_00 = -unk_4C / 2.0f;
            var_60.unk_04 = 0.0f;
            var_60.unk_08 = -unk_4C / 2.0f;
            var_60.unk_0C = 0.0f;
            var_60.unk_10 = unk_4C / 2.0f;
            if (vf_0BC() == 0)
                var_60.unk_14 = unk_48 * 2.0f;
            else if (vf_0BC() == 1)
                var_60.unk_14 = unk_48;
            else if (vf_0BC() == 2)
                var_60.unk_14 = unk_48 / 2.0f;
            else
                var_60.unk_14 = unk_48 * 2.0f;
            var_60.unk_18 = unk_4C / 2.0f;
            var_60.unk_1C = 0.0f;
            var_64 = unk_284->unk_18;
            var_8 = sub_8E330(1, var_64, arg_4, arg_C == 0, &var_60);
        }
    }
    return var_8;
}
// match: ?sub_13C490@type_3DAFC8@@QAEXH@Z @ 0x0013C490
// sp-match: ?sub_13C490@type_3DAFC8@@QAEXH@Z @ 0x000E7770
// Takes arg_0 damage: unless already hurt (1) or dying (2), it dies (unless
// bit 14 of its AI object's unk_49C holds it) or is hurt, through its
// second animation; with cheat flag 4 it shrinks with its hit points (to a
// third).
void type_3DAFC8::sub_13C490(RwInt32 arg_0)
{
#ifdef CODFH_DRAW_TRIGGERS
    TrigDrawDamageTaken(this, arg_0);
#endif
    unk_1D20 -= arg_0;
    if (unk_805 == 2 || unk_805 == 1)
        return;
    if (unk_1D20 <= 0 && !unk_8A0.unk_49C_14)
    {
        sub_17AD60(unk_28C);
        unk_805 = 2;
    }
    else
    {
        sub_17ADF0(unk_28C);
        unk_805 = 1;
    }
    if (((type_4B8888 *)dword_4B8888)->unk_00_4)
    {
        unk_800 = (RwReal)unk_1D20 / unk_1D24 * 0.67f + 0.33f;
        if (unk_800 < 0.33f)
            unk_800 = 0.33f;
        unk_284->set_unk_28(unk_800);
    }
}
extern RwReal flt_429C90;
extern RwReal dword_4CF9D0;
// match: ?vf_064@type_3DAFC8@@UAEHPAUtype_75600@@@Z @ 0x0013C5B0
// sp-match: ?vf_064@type_3DAFC8@@UAEHPAUtype_75600@@@Z @ 0x000E7830
// A bullet: its hit-death values (with a performance value from the
// shooter's distance), the damage (unless from a friend, or while its AI
// object is not hurt by bullets; all or nothing with cheat flags 5 and 2),
// on a head shot a chance of unk_804 2 with unk_7E4 the bullet's direction
// (scaled by 11 and raised by 6), and its scripts told.
RwInt32 type_3DAFC8::vf_064(type_75600 *arg_0)
{
    RwInt32 l4;
    RwUInt8 var_5;
    type_EC880 *fp_C;
    RwV3d var_18;
    RwInt32 var_1C;
    RwReal l20;
    RwInt32 fp_24;
    RwV3d *fp_28;

    if (arg_0->unk_24 != -1)
    {
        l4 = 0;
        if (arg_0->unk_0C)
        {
            fp_C = (type_EC880 *)dword_4B92D4;
            RwV3dSubMacro(&var_18, sub_CD550(), arg_0->unk_0C->sub_CD550());
            l4 = fp_C->sub_EC880((type_EC880_00 *)arg_0,
                                     RwV3dLength((RwV3d *)&var_18));
            unk_8A0.sub_18DA0(arg_0->unk_0C);
        }
        if (unk_8A0.unk_49C_14 && unk_894 > 0.0f)
            return 0;
        unk_1D38[0] = unk_868;
        unk_1D38[1] = unk_864;
        unk_1D38[2] = arg_0->unk_24;
        unk_1D38[3] = unk_3E0.sub_15F0A0();
        unk_1D38[4] = l4;
        unk_1D38[5] = l4;
        for (var_1C = 0; var_1C < 6; var_1C++)
            unk_1D38[var_1C + 6] = 1;
        var_5 = 1;
        if (arg_0->unk_0C && !cmp_unk_2C(arg_0->unk_0C, this))
            var_5 = 0;
        if (unk_8A0.unk_49C_3 && var_5)
        {
            l20 = 0.0f;
            if (((type_4B8888 *)dword_4B8888)->unk_00_5)
            {
                l20 = 1000.0f;
            }
            else if (((type_4B8888 *)dword_4B8888)->unk_00_2)
            {
                if (arg_0->unk_24 == 0)
                    l20 = 1000.0f;
                else
                    l20 = 0.0f;
            }
            else
            {
                l20 = part_damage_multiplier(arg_0->unk_24) * arg_0->unk_28;
            }
            sub_13C490((RwInt32)l20);
        }
        else
        {
            sub_13C490(0);
        }
        if (!unk_804 && arg_0->unk_24 == 0 && RpRandom() % 101 > 70 && !unk_808)
        {
            fp_24 = 0;
            if (arg_0->unk_04_p)
            {
                fp_28 = &arg_0->unk_04_p->unk_10;
                if (RwV3dDotProductMacro(fp_28, fp_28) > 0.0001f)
                {
                    RwV3dNormalize(&unk_7E4, fp_28);
                    fp_24 = 1;
                }
            }
            if (!fp_24)
                set_v3d(&unk_7E4, 0.0f, 0.0f, 0.0f);
            unk_7F0 = unk_7E4;
            RwV3dScaleMacro(&unk_7E4, &unk_7E4, 11.0f);
            unk_7E4.y += 6.0f;
            unk_804 = 2;
        }
        if (unk_8A0.unk_49C_14)
        {
            if (unk_1D20 <= 0)
                unk_1D20 = 1;
            unk_894 = frand_range(dword_4CF9D0, flt_429C90) * 60.0f;
        }
        sub_6B5F0("HitByBullet", (type_67620 *)(vf_098()), 0, 0, 0, 0, 1, 0);
        sub_D2AD0(arg_0->unk_0C, arg_0->unk_04);
    }
    return 0;
}
// match: ?vf_068@type_3DAFC8@@UAEHPAUtype_758F0@@@Z @ 0x0013CAA0
// sp-match: ?vf_068@type_3DAFC8@@UAEHPAUtype_758F0@@@Z @ 0x000E7BA0
// An explosion that reaches it: while bit 3 of its AI object's unk_49C is
// set, the damage by its zones (as the player's vf_068 reckons it, but for
// its own posture class; 1 when out of range), then its hit-death values
// (with a performance value from the distance), and its scripts told where
// it came from and whether from behind.
RwInt32 type_3DAFC8::vf_068(type_758F0 *arg_0)
{
    RwInt32 stk_64;
    RwInt32 var_60;
    RwReal stk_5C;
    type_114F90_50 *local_58;
    RwReal local_54;
#ifndef CODFH_SP // single player scopes it to the block below (SP 0xE7BA0 reuses its slot)
    RwV3d local_50;
#endif
    RwReal slot_44;
    RwV3d *l40;
    RwFrame *var_3C;
    RwV3d l38;
    RwV3d lcl_2C;
    RwMatrix *local_20;
    type_EC880 *var_1C;
    type_758F0_14 var_18;
    RwInt32 var_4;

    if (arg_0->unk_2C != 0.0f && vf_070(arg_0, 0, 0))
    {
        if (unk_8A0.unk_49C_3)
        {
#ifdef CODFH_SP // shape: block-scoped, its slot shared with a later temporary
            RwV3d local_50;

#endif
            RwV3dSubMacro(&local_50, &arg_0->unk_0C->pos, sub_CD550());
            slot_44 = RwV3dLength((RwV3d *)&local_50);
            if (slot_44 > arg_0->unk_10)
                return 1;
            if (!arg_0->unk_30)
            {
                local_54 = slot_44 / (arg_0->unk_10);
                local_54 = (1.0f - local_54) * arg_0->unk_2C;
                sub_13C490((RwInt32)local_54);
            }
            else
            {
                local_58 = &arg_0->unk_30->unk_50;
                var_60 = vf_0BC();
                stk_5C = arg_0->unk_0C->pos.y - sub_CD550()->y;
                if (stk_5C > 145.0f)
                    var_60 = 2;
                else if (stk_5C > 90.0 && var_60 == 0)
                    var_60 = 1;
                if (slot_44 < local_58->unk_18)
                {
                    local_54 = (RwInt32)arg_0->unk_2C;
                    sub_13C490((RwInt32)local_54);
                }
                else if (var_60 == 0 || var_60 == -1)
                {
                    local_54 = (slot_44 - local_58->unk_18) / (arg_0->unk_10 - local_58->unk_18);
                    local_54 = (1.0f - local_54) * arg_0->unk_2C;
                    sub_13C490((RwInt32)local_54);
                }
                else if (var_60 == 1 && slot_44 < local_58->unk_08)
                {
                    local_54 = (slot_44 - local_58->unk_18) / (local_58->unk_08 - local_58->unk_18);
                    local_54 = (1.0f - local_54) * local_58->unk_10;
                    sub_13C490((RwInt32)local_54);
                }
                else if (var_60 == 2 && slot_44 < local_58->unk_0C)
                {
                    local_54 = (slot_44 - local_58->unk_18) / (local_58->unk_0C - local_58->unk_18);
                    local_54 = (1.0f - local_54) * local_58->unk_14;
                    sub_13C490((RwInt32)local_54);
                }
                else
                {
                    return 1;
                }
            }
        }
        l40 = RwMatrixGetPos(arg_0->unk_0C);
        RwV3dSubMacro(&lcl_2C, sub_CD550(), l40);
        var_1C = (type_EC880 *)dword_4B92D4;
        var_4 = var_1C->sub_EC970((type_EC880_00 *)arg_0,
                                  RwV3dLength((RwV3d *)&lcl_2C));
        unk_1D38[0] = unk_868;
        unk_1D38[1] = unk_864;
        unk_1D38[2] = (RwInt8)(RpRandom() % 9);
        unk_1D38[3] = unk_3E0.sub_15F0A0();
        unk_1D38[4] = var_4;
        unk_1D38[5] = var_4;
        for (stk_64 = 0; stk_64 < 6; stk_64++)
            unk_1D38[stk_64 + 6] = 1;
        var_3C = unk_338.unk_08;
        local_20 = RwFrameGetLTM(var_3C);
        l38 = *RwMatrixGetPos(local_20);
        RwV3dSubMacro(&l38, &l38, l40);
        if (unk_8A0.unk_49C_14 && unk_1D20 <= 0)
            unk_1D20 = 1;
        var_18.unk_00 = l40->x;
        var_18.unk_04 = l40->y;
        var_18.unk_08 = l40->z;
        var_18.unk_0C = arg_0->unk_14;
        var_18.unk_10 = RwV3dDotProductMacro(&local_20->at, &l38) <= 0 ? 1 : 0;
        sub_6B5F0("HitByExplosion", (type_67620 *)(vf_098()), 0, 0, (RwInt32 *)(&var_18), 5, 1, 0);
        sub_D2AD0(arg_0->unk_04.sub_D4910(), arg_0->unk_08);
    }
    return 0;
}
// The magnitude of arg_0: an inline with no address and so no database name,
// named for what it computes. Evidence: vf_060 stores an expression argument
// into a parameter slot, compares it with 0 and copies it or its negation
// into a result temporary, with no call to the C library's fabs.
// sp-match: ?real_abs@@YAMM@Z @ 0x000E4AF0
inline RwReal real_abs(RwReal arg_0)
{
    return arg_0 >= 0.0f ? arg_0 : -arg_0;
}
// match: ?vf_060@type_3DAFC8@@UAEHPAUtype_3D3548@@@Z @ 0x0013CF90
// sp-match: ?vf_060@type_3DAFC8@@UAEHPAUtype_3D3548@@@Z @ 0x000E7F10
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// A touch by the entity arg_0 (none while it rides or is dead: flags 9 and
// 0). A vehicle (kind bits 0x40080) of another side, or one a player rides,
// run it over unless its AI blocks that (bits 21, 14): moving at 1 or more
// (without a player at the wheel, unk_113C), within 180 up or down, heading
// at it (without a player) and passing within its radius plus 100 sideways;
// then its hit-death values and its scripts told as for a bullet. A
// soldier, a player or kinds 17 and 21 push it (or, with flag 19 of unk_28,
// it pushes them) out of their overlap. A type_3DA6C0 whose vf_244 is 1
// (not blocked by bit 14) knocks it down the same way.
RwInt32 type_3DAFC8::vf_060(type_3D3548 *arg_0)
{
#ifndef CODFH_SP // single player declares these in the blocks that use them (SP 0xE7F10)
    RwInt32 varB8;
    RwV3d *var_B4;
    RwV3d *vB0;
    RwV3d qAC;
    RwReal frm_A0;
#endif
    type_3DA6C0 *local_9C;
#ifndef CODFH_SP
    RwV3d var98;
    RwV3d l8C;
    RwReal *ebp_80;
    RwReal v7C;
    RwReal var78;
    RwReal *lv_74;
    RwInt32 z70;
    RwV3d lv_6C;
    RwV3d l60;
    RwReal l54;
    RwV3d var50;
    RwReal loc44;
    RwV3d *var_40;
    RwV3d l3C;
    RwV3d *local_30;
    RwV3d stk_2C;
    RwV3d var_20;
#endif
    RwReal ebp_14;
    type_3DBC78 *lv_10;
    RwInt32 var_C;
    RwInt32 bp_8;
    type_3D3548 *bp_4;

    if (unk_28_9 || unk_28_0)
        return 0;
    if (arg_0)
    {
        if ((arg_0->unk_2C & 0x3FFFFF0) & 0x40080 && !unk_8A0.unk_49C_21 && !unk_8A0.unk_49C_14) // not an address: entity kind bits
        {
            lv_10 = arg_0->vf_010();
            bp_8 = 0;
            var_C = cmp_unk_2C(this, arg_0);
            bp_4 = lv_10->unk_118C.sub_D4910();
            if (bp_4 && bp_4->unk_2C_4)
                bp_8 = 1;
            if (var_C || (!var_C && bp_8))
            {
#ifdef CODFH_SP // shape: block-scoped
                RwV3d var50;
                RwReal l54;
                RwV3d *var_40;
                RwV3d l3C;
                RwV3d *local_30;
                RwV3d stk_2C;
                RwV3d var_20;
                RwReal loc44;
                RwInt32 z70;
#endif
                var50 = lv_10->unk_450.unk_124;
                var50.y = 0.0f;
                l54 = RwV3dLength((RwV3d *)&var50);
                if (!bp_8)
                {
                    if (l54 < 1.0f)
                        return 0;
                }
                else
                {
                    if (!lv_10->get_unk_113C() && l54 < 1.0f)
                        return 0;
                }
                local_30 = sub_CD550();
                var_40 = lv_10->sub_CD550();
                if (real_abs(local_30->y - var_40->y) > 180.0f)
                    return 0;
                if (!bp_8)
                {
#ifdef CODFH_SP // shape: block-scoped
                    RwV3d lv_6C;
                    RwV3d l60;
#endif
                    l60 = lv_10->unk_450.unk_124;
                    RwV3dNormalize(&l60, &l60);
                    RwV3dSubMacro(&lv_6C, local_30, var_40);
                    RwV3dNormalize(&lv_6C, &lv_6C);
                    ebp_14 = RwV3dDotProductMacro(&lv_6C, &l60);
                    if (ebp_14 < 0.25f)
                        return 0;
                }
                l3C = *lv_10->sub_CDBE0();
                l3C.y = 0.0f;
                RwV3dNormalize(&l3C, &l3C);
                RwV3dSubMacro(&var_20, local_30, var_40);
                loc44 = RwV3dDotProductMacro(&l3C, &var_20);
#ifdef CODFH_SP // shape: single player evaluates the call first (SP 0xE7F10)
                if (real_abs(loc44) > lv_10->unk_4C + 100.0f)
#else
                if (lv_10->unk_4C + 100.0f < real_abs(loc44))
#endif
                    return 0;
                RwV3dSubMacro(&stk_2C, var_40, local_30);
                RwV3dNormalize(&stk_2C, &stk_2C);
                ebp_14 = RwV3dDotProductMacro(sub_CD5A0(), &stk_2C);
                unk_1D38[0] = vf_08C(1, 0)[3];
                unk_1D38[2] = (RwInt8)(RpRandom() % 9);
                unk_1D38[3] = unk_3E0.sub_15F0A0();
                if (ebp_14 > 0.0f)
                    unk_1D38[1] = 0x49;
                else
                    unk_1D38[1] = 0x4A;
                if (l54 < 5.0f)
                {
                    unk_1D38[4] = 0;
                    unk_1D38[5] = 0;
                }
                else
                {
                    unk_1D38[4] = 1;
                    unk_1D38[5] = 1;
                }
                for (z70 = 0; z70 < 6; z70++)
                    unk_1D38[z70 + 6] = 1;
                if (unk_8A0.unk_49C_3)
                    sub_13C490(unk_1D20);
                vf_190(0);
                unk_108 = 0.0f;
                sub_6B5F0("HitByBullet", (type_67620 *)(vf_098()), 0, 0, 0, 0, 1, 0);
            }
        }
        else if (arg_0->unk_2C_5 || arg_0->unk_2C_17 || arg_0->unk_2C_21 || arg_0->unk_2C_4)
        {
#ifdef CODFH_SP // shape: block-scoped
            RwReal *ebp_80;
            RwReal v7C;
            RwReal var78;
            RwReal *lv_74;
            RwV3d var98;
            RwV3d l8C;
#endif
            ebp_80 = arg_0->vf_0C4();
            lv_74 = vf_0C4();
            RwV3dSubMacro(&var98, (RwV3d *)ebp_80, (RwV3d *)lv_74);
            var98.y = 0.0f;
            v7C = RwV3dLength((RwV3d *)&var98);
            var78 = v7C - (unk_4C + arg_0->unk_4C) / 1.25f;
            if (var78 < 0.0f)
            {
                if (RwV3dDotProductMacro(&var98, &var98) > 0.001f)
                    RwV3dNormalize(&var98, &var98);
                if (!unk_28_19)
                {
                    RwV3dScaleMacro(&var98, &var98, var78);
                    RwV3dAddMacro(&l8C, &var98, (RwV3d *)lv_74);
                    vf_0C0(&l8C);
                }
                else
                {
                    RwV3dScaleMacro(&var98, &var98, -var78);
                    RwV3dAddMacro(&l8C, &var98, (RwV3d *)ebp_80);
                    arg_0->vf_0C0(&l8C);
                }
            }
        }
        else if (arg_0->vf_01C())
        {
            local_9C = (type_3DA6C0 *)arg_0;
            if (local_9C->vf_244() == 1 && !unk_8A0.unk_49C_14)
            {
#ifdef CODFH_SP // shape: block-scoped
                RwV3d *var_B4;
                RwV3d *vB0;
                RwV3d qAC;
                RwReal frm_A0;
                RwInt32 varB8;
#endif
                vB0 = sub_CD550();
                var_B4 = arg_0->sub_CD550();
                RwV3dSubMacro(&qAC, var_B4, vB0);
                RwV3dNormalize(&qAC, &qAC);
                frm_A0 = RwV3dDotProductMacro(sub_CD5A0(), &qAC);
                unk_1D38[0] = vf_08C(1, 0)[3];
                unk_1D38[2] = (RwInt8)(RpRandom() % 9);
                unk_1D38[3] = unk_3E0.sub_15F0A0();
                if (frm_A0 > 0.0f)
                    unk_1D38[1] = 0x49;
                else
                    unk_1D38[1] = 0x4A;
                unk_1D38[4] = 1;
                unk_1D38[5] = 1;
                for (varB8 = 0; varB8 < 6; varB8++)
                    unk_1D38[varB8 + 6] = 1;
                if (unk_8A0.unk_49C_3)
                    sub_13C490(unk_1D20);
                vf_190(0);
                unk_108 = 0.0f;
                sub_6B5F0("HitByBullet", (type_67620 *)(vf_098()), 0, 0, 0, 0, 1, 0);
            }
        }
    }
    return 0;
}
// match: ?vf_06C@type_3DAFC8@@UAEHPAUtype_3D3548@@@Z @ 0x0013DA50
// sp-match: ?vf_06C@type_3DAFC8@@UAEHPAUtype_3D3548@@@Z @ 0x000E8540
// A collision with the entity arg_0: from a type_3DA6C0 whose vf_244 is 1,
// its hit-death values (0x49 or 0x4A by whether it faces the entity), 1000
// damage while its AI object is hurt by hits, its collision off, and its
// scripts told as for a bullet.
RwInt32 type_3DAFC8::vf_06C(type_3D3548 *arg_0)
{
    type_3DA6C0 *var_4;
    RwReal loc8;
    RwV3d local_14;
    RwV3d *var18;
    RwV3d *var_1C;
    RwInt32 l20;

    if (arg_0->vf_01C())
    {
        var_4 = (type_3DA6C0 *)arg_0;
        if (var_4->vf_244() == 1)
        {
            var18 = sub_CD550();
            var_1C = arg_0->sub_CD550();
            RwV3dSubMacro(&local_14, var_1C, var18);
            RwV3dNormalize(&local_14, &local_14);
            loc8 = RwV3dDotProductMacro(sub_CD5A0(), &local_14);
            unk_1D38[0] = vf_08C(1, 0)[3];
            unk_1D38[2] = (RwInt8)(RpRandom() % 9);
            unk_1D38[3] = unk_3E0.sub_15F0A0();
            if (loc8 > 0.0f)
                unk_1D38[1] = 0x49;
            else
                unk_1D38[1] = 0x4A;
            unk_1D38[4] = 1;
            unk_1D38[5] = 1;
            for (l20 = 0; l20 < 6; l20++)
                unk_1D38[l20 + 6] = 1;
            if (unk_8A0.unk_49C_3)
                sub_13C490(1000);
            if (unk_8A0.unk_49C_14 && unk_1D20 <= 0)
                unk_1D20 = 1;
            vf_190(0);
            unk_108 = 0.0f;
            sub_6B5F0("HitByBullet", (type_67620 *)(vf_098()), 0, 0, 0, 0, 1, 0);
        }
    }
    return 0;
}
// match: ?vf_054@type_3DAFC8@@UAEXH@Z @ 0x0013DC60
// sp-match: ?vf_054@type_3DAFC8@@UAEXH@Z @ 0x000E86E0
// Its render (unless its trigger hides it by bit 11 of unk_24): its clump
// and its two held clumps as the base renders its clump (faded while
// unk_28_18 is set), with the cull mode flipped while its second animation
// runs with flag 4.
void type_3DAFC8::vf_054(RwInt32 arg_0)
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
    v8 = unk_828.unk_08;
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
    v8 = unk_834.unk_08;
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
extern RwReal flt_429CB8;
extern RwReal flt_429CB0;
extern RwReal flt_429CAC;
extern RwReal flt_429CB4;
extern RwReal flt_429C98;
extern RwReal flt_429CA0;
extern RwReal flt_429C9C;
extern RwReal flt_429CA8;
extern RwReal flt_429CA4;
// match: ?sub_13DF40@type_3DAFC8@@QAEXPAURwV3d@@M@Z @ 0x0013DF40
// sp-match: ?sub_13DF40@type_3DAFC8@@QAEXPAURwV3d@@M@Z @ 0x000E8900
// "SendFlying": unless it flies already, it flies (unk_1D28 1, gravity on)
// away from the point *arg_0, launched at an angle and a speed from the
// strength arg_4 (200 to 1000) and the distance, in its own frame.
void type_3DAFC8::sub_13DF40(RwV3d *arg_0, RwReal arg_4)
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

    if (unk_1D28 == 1)
        return;
    unk_30 |= 0x40;
    unk_1D28 = 1;
    vf_18C(1);
    unk_28_5 = 1;
    unk_28_4 = 1;
    if (arg_4 != 0.0f)
    {
        if (arg_4 < flt_429CA4)
            arg_4 = flt_429CA4;
        if (arg_4 > flt_429CA8)
            arg_4 = flt_429CA8;
        var_8 = sub_CD550();
        RwV3dSubMacro(&var_14, var_8, arg_0);
        var_18 = RwV3dLength((RwV3d *)&var_14);
        var_14.y = 0.0f;
        var_1C = RwV3dLength((RwV3d *)&var_14);
        if (var_1C > 0.001f)
        {
#ifdef CODFH_SP // shape: single player evaluates the left factor first (SP 0xE8900)
            var_20 = (flt_429CA0 / flt_429C9C) * ((arg_4 * flt_429C9C - var_1C) / arg_4);
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
// match: ?vf_1C4@type_3DAFC8@@UAEXH@Z @ 0x0013E200
// sp-match: ?vf_1C4@type_3DAFC8@@UAEXH@Z @ 0x000E8B00
// Landing from a flight (unk_1D28): on the ground (arg_0) it stops, or
// against a wall it drops; its scripts are told.
void type_3DAFC8::vf_1C4(RwInt32 arg_0)
{
    if (!unk_1D28)
    {
        return;
    }
    if (arg_0)
    {
        unk_130 = 0;
        set_v3d(&unk_10C, -1.0f, -1.0f, -1.0f);
        unk_1D28 = 0;
        sub_6B5F0("HitGround", (type_67620 *)(vf_098()), 0, 0, 0, 0, 1, 0);
    }
    else if (unk_1D28 == 1)
    {
        set_v3d(&unk_10C, -1.0f, 0.0f, -1.0f);
        unk_DC = 0.0f;
        unk_1D28 = 2;
        sub_6B5F0("HitWall", (type_67620 *)(vf_098()), 0, 0, 0, 0, 1, 0);
    }
}
// match: ?vf_164@type_3DAFC8@@UAEMXZ @ 0x0013E310
// sp-match: ?vf_164@type_3DAFC8@@UAEMXZ @ 0x000E8BB0
RwReal type_3DAFC8::vf_164()
{
#if defined(CODFH_DRAW_TRIGGERS) && !defined(CODFH_SP)
    return TrigBotSpread(this, unk_88C);
#else
    return unk_88C;
#endif
}
// match: ?vf_168@type_3DAFC8@@UAEMXZ @ 0x0013E330
// sp-match: ?vf_168@type_3DAFC8@@UAEMXZ @ 0x000E8BC0
RwReal type_3DAFC8::vf_168()
{
#if defined(CODFH_DRAW_TRIGGERS) && !defined(CODFH_SP)
    return TrigBotSpread(this, unk_890);
#else
    return unk_890;
#endif
}
// match: ?vf_16C@type_3DAFC8@@UAEHHH@Z @ 0x0013E350
// sp-match: ?vf_16C@type_3DAFC8@@UAEHHH@Z @ 0x000E8BD0
// Sets AI parameter arg_0 to arg_4, a float's bits as the script passes
// them ("SetAIParam"), as type_3D5658::vf_16C does for its own fields.
RwInt32 type_3DAFC8::vf_16C(RwInt32 arg_0, RwInt32 arg_4)
{
    RwInt32 var_4;

    var_4 = 1;
    switch (arg_0)
    {
    case 0:
        unk_88C = *(RwReal *)&arg_4 * 0.5f;
        break;
    case 1:
        unk_890 = *(RwReal *)&arg_4 * 0.5f;
        break;
    case 2:
        unk_86C = cos(*(RwReal *)&arg_4 *= 0.0087266462f);
        break;
    case 3:
        *(RwReal *)&arg_4 = 0.0087266462f;
        unk_870 = cos(*(RwReal *)&arg_4);
        break;
    case 4:
        unk_878 = *(RwReal *)&arg_4 * 100.0f;
        break;
    case 5:
        unk_87C = *(RwReal *)&arg_4 * 100.0f;
        break;
    case 6:
        unk_884 = *(RwReal *)&arg_4;
        break;
    case 7:
        unk_888 = *(RwReal *)&arg_4 * 100.0f;
        break;
    }
    return var_4;
}
// match: ?vf_1B0@type_3DAFC8@@UAEXH@Z @ 0x0013E470
// sp-match: ?vf_1B0@type_3DAFC8@@UAEXH@Z @ 0x000E8CC0
// Sets its AI object's unk_524 and hands it to its weapon.
void type_3DAFC8::vf_1B0(RwInt32 arg_0)
{
    unk_8A0.unk_524 = arg_0;
    unk_3E0.sub_15D510(arg_0, 0);
}
// match: ?vf_1B4@type_3DAFC8@@UAEXH@Z @ 0x0013E4A0
// sp-match: ?vf_1B4@type_3DAFC8@@UAEXH@Z @ 0x000E8CE0
// Fires (arg_0 1) or stops: its mounted weapon while it is mounted, else
// its own weapon (stopping it at 0).
void type_3DAFC8::vf_1B4(RwInt32 arg_0)
{
    type_3DC9B0 *var_4;

    if (get_unk_61C())
    {
        var_4 = get_unk_618();
        if (var_4)
            var_4->sub_169170(arg_0);
    }
    else
    {
        unk_8A0.unk_524 = arg_0;
        if (!arg_0)
            unk_3E0.sub_15D510(0, 0);
    }
}
// match: ?vf_248@type_3DAFC8@@UAEXH@Z @ 0x0013E510
// sp-match: ?vf_248@type_3DAFC8@@UAEXH@Z @ 0x000E8D20
void type_3DAFC8::vf_248(RwInt32 arg_0)
{
    unk_3E0.unk_20 = arg_0;
}
// match: ?vf_24C@type_3DAFC8@@UAEXH@Z @ 0x0013E530
// sp-match: ?vf_24C@type_3DAFC8@@UAEXH@Z @ 0x000E8D30
// "SetFireAtNoTarget": its weapon's flags, then it fires.
void type_3DAFC8::vf_24C(RwInt32 arg_0)
{
    unk_3E0.unk_A0 = arg_0 == 0;
    unk_3E0.unk_C4 = arg_0;
    vf_1B4(1);
    unk_600 = 1;
}
// match: ?sub_13E580@type_3DAFC8@@QAEHHHH@Z @ 0x0013E580
// sp-match: ?sub_13E580@type_3DAFC8@@QAEHHHH@Z @ 0x000E8D70
// "GetDodgeDirection": whether it can dodge in direction arg_0 (0 left, 1
// right, 2 forward, 3 back) from the posture arg_4 (distances by posture:
// kinds 8, 43, 64; 7, 18, 42, 59, 63; the others): never while flag 7 of
// unk_28 is set; a line test from its eye height to the dodge point, at most
// every 30 frames per direction (unk_2144), its AI object vetoing points it
// would not stand at; with arg_8, also a clear shot from there at its
// target.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_3DAFC8::sub_13E580(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    RpHAnimHierarchy *var_60;
    RpHAnimHierarchy *stk_5C;
    RwFrame *local_58;
    RwMatrix *local_54;
    RwMatrix *local_50;
    RwReal stk_4C;
    RwV3d loc48;
    RwV3d local_3C;
    AIData *v30;
    RwFrame *var_2C;
    RwV3d loc28;
    RwV3d slot_1C;
    RwReal local_10;
    RwReal fp_C;
    RwReal lv_8;
    RwReal var_4;

    if (unk_28_7)
        return 0;
    switch (arg_4)
    {
    case 8:
    case 43:
    case 64:
        var_4 = 103.7f;
        local_10 = 115.8f;
        lv_8 = 35.5f;
        fp_C = 0.0f;
        break;
    case 7:
    case 18:
    case 42:
    case 59:
    case 63:
        var_4 = 68.8f;
        local_10 = 68.8f;
        lv_8 = 0.0f;
        fp_C = 0.0f;
        break;
    default:
        var_4 = 56.0f;
        local_10 = 56.0f;
        lv_8 = 35.5f;
        fp_C = 35.5f;
        break;
    }
    loc28.x = 0.0f;
    loc28.y = 0.0f;
    loc28.z = 0.0f;
    slot_1C.x = 0.0f;
    slot_1C.y = 0.0f;
    slot_1C.z = 0.0f;
    switch (arg_0)
    {
    case 0:
        loc28.z = loc28.y = 0.0f;
        loc28.x = -local_10;
        slot_1C.z = slot_1C.y = 0.0f;
        slot_1C.x = -150.0f;
        break;
    case 1:
        loc28.z = loc28.y = 0.0f;
        loc28.x = var_4;
        slot_1C.z = slot_1C.y = 0.0f;
        slot_1C.x = 150.0f;
        break;
    case 2:
        loc28.y = loc28.x = 0.0f;
        loc28.z = lv_8;
        slot_1C.y = slot_1C.x = 0.0f;
        slot_1C.z = 200.0f;
        break;
    case 3:
        loc28.y = loc28.x = 0.0f;
        loc28.z = -fp_C;
        slot_1C.y = slot_1C.x = 0.0f;
        slot_1C.z = -150.0f;
    }
    if (unk_2144[arg_0].unk_04 <= 0.0f)
    {
        local_58 = unk_338.unk_08;
        var_2C = local_58;
        local_50 = RwFrameGetLTM(var_2C);
        loc48 = local_50->pos;
        sub_1414C0(&local_3C, &slot_1C, local_50);
        if (unk_28_13)
        {
            stk_5C = unk_284->unk_18;
            local_54 = RpHAnimHierarchyGetMatrixArray(stk_5C);
            var_60 = unk_284->unk_18;
            stk_4C = local_54[RpHAnimIDGetIndex(var_60, 1)].pos.y - local_50->pos.y;
        }
        else
        {
            if (vf_0BC() == 0)
                stk_4C = unk_48;
            else if (vf_0BC() == 1)
                stk_4C = unk_48 / 2.0f;
            else if (vf_0BC() == 2)
                stk_4C = unk_48 / 4.0f;
            else
                stk_4C = unk_48;
        }
        loc48.y += stk_4C;
        local_3C.y += stk_4C;
        unk_2144[arg_0].unk_04 = 30.0f;
        v30 = vf_120();
        if (v30 && (v30->unk_49C & 0x2000) && !v30->sub_205E0(&local_3C, 0))
            return 0;
        if (sub_D2FC0(&loc48, &local_3C, 0, &unk_2144[arg_0].unk_00, 0, unk_30, 1, 1,
                      0x20000, 0, 0)) // not an address: line test flags
            return 0;
    }
    else if (unk_2144[arg_0].unk_00 < 1.0f)
    {
        return 0;
    }
    if (!arg_8 || vf_134(&loc28, unk_8A0.unk_1374.sub_D4910(), 1, 1, 0, 0, -1))
        return 1;
    return 0;
}
// match: ?sub_13E9A0@type_3DAFC8@@QAEHPAURwV3d@@PAUtype_3D3548@@H@Z @ 0x0013E9A0
// sp-match: ?sub_13E9A0@type_3DAFC8@@QAEHPAURwV3d@@PAUtype_3D3548@@H@Z @ 0x000E9110
// Whether it can dive along *arg_0: a nonzero direction, with nothing (but
// arg_4) in the way from 100 above its position to that point plus the
// direction.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_3DAFC8::sub_13E9A0(RwV3d *arg_0, type_3D3548 *arg_4, RwInt32 arg_8)
{
    RwInt32 var_4;
    RwV3d local_10;
    RwV3d var_1C;
    RwV3d bp_28;

    var_4 = 0;
    if ((RwReal)fabs((RwDouble)(RwV3dDotProductMacro(arg_0, arg_0) > 0.0f)) != 0.0f)
    {
        bp_28.x = 0.0f;
        bp_28.y = 100.0f;
        bp_28.z = 0.0f;
        RwV3dAddMacro(&var_1C, sub_CD550(), &bp_28);
        RwV3dAddMacro(&local_10, &var_1C, arg_0);
        var_4 = !sub_D2FC0(&var_1C, &local_10, arg_4, 0, 0, arg_8, 1, 1, 0x20000, 0, 0); // not an address: line test flags
    }
    return var_4;
}
extern RwReal flt_429CBC;
extern RwReal flt_429CCC;
extern RwReal flt_429CC8;
extern RwReal flt_429CC4;
extern RwReal flt_429CC0;
// match: ?vf_134@type_3DAFC8@@UAEHPAURwV3d@@PAUtype_3D3548@@HHPAH2H@Z @ 0x0013EAD0
// sp-match: ?vf_134@type_3DAFC8@@UAEHPAURwV3d@@PAUtype_3D3548@@HHPAH2H@Z @ 0x000E9200
// Whether it can shoot arg_4 from the offset arg_0 in the posture arg_18
// (-1: its own, vf_0BC): not where its weapon has no place (the tables
// above); the muzzle point raised by the weapon's height and moved aside,
// in its clump's space, to the target's aim point (arg_4's vf_110), lowered
// for a close high target in postures 0 and 1; with arg_8, the line is
// moved 10 to the side and, when that is blocked, 20 to the other. The AI
// keeps the blocker's distance (set_unk_139C); *arg_14 gets the distance
// along to it (1e37 at first, 0 when very close), *arg_10 whether the
// target's AI has a cover node.
RwInt32 type_3DAFC8::vf_134(RwV3d *arg_0, type_3D3548 *arg_4, RwInt32 arg_8, RwInt32 arg_C,
                            RwInt32 *arg_10, RwInt32 *arg_14, RwInt32 arg_18)
{
    RwInt32 var_8;
    RwInt32 var_C;
    RwInt32 var_10;
    RwV3d var_24;
    RpClump *var_28;
    RwFrame *var_2C;
    RwV3d var_38;
    RwV3d var_44;
    AIData *var_48;
    type_F8350 *var_4C;
    RwV3d var_58;
    RwReal var_5C;
    RwReal var_60;
    RwReal var_64;
#ifndef CODFH_SP // single player declares these in the blocks that use them (SP 0xE9200)
    RwV3d var_70;
    RwV3d var_7C;
    RwV3d var_88;
    RwReal var_8C;
#endif
    RwInt32 var_90;
#ifndef CODFH_SP
    RwV3d var_B4;
    RwReal var_B8;
    RwReal var_114;
    RwV3d var_12C;
    RwReal var_130;
#endif

    if (!arg_4)
        return 0;
    var_8 = 0;
    if (arg_18 == -1)
        arg_18 = vf_0BC();
    var_C = 0;
    var_10 = unk_3E0.unk_00;
    if (var_10)
    {
        switch (unk_3E0.get_unk_04())
        {
        case 6:
        case 8:
        case 15:
            var_C = 0;
            break;
        default:
            var_C = unk_3E0.sub_15EF80();
            break;
        }
    }
    if (flt_3DAEE8[var_C][arg_18] == -1.0f)
        return 0;
    var_24 = *arg_0;
    var_24.y += flt_3DAEE8[var_C][arg_18];
    if (flt_3DAF58[var_C][arg_18] != 0.0f)
        var_24.x += flt_3DAF58[var_C][arg_18];
    var_28 = unk_25C.unk_08;
    var_2C = RpClumpGetFrame(var_28);
    sub_1414C0(&var_38, &var_24, RwFrameGetLTM(var_2C));
    arg_4->vf_110(&var_44, this, 1);
    if (arg_4->vf_120() && arg_4->vf_120()->sub_238E0(0))
    {
        var_48 = arg_4->vf_120();
        var_4C = var_48->unk_F60;
        if (var_4C)
            var_8 = 1;
    }
    if (arg_14)
        *(RwReal *)arg_14 = 1e37f;
    RwV3dSubMacro(&var_58, &var_44, &var_38);
    var_5C = var_58.y;
    var_58.y = 0.0f;
    if (var_5C > flt_429CC0 && arg_18 != 2)
    {
        var_60 = RwV3dDotProductMacro(&var_58, &var_58);
        var_64 = var_60 / (var_5C * var_5C);
        if (var_64 < flt_429CC4)
        {
            if (arg_18 == 0)
                var_24.y -= flt_429CC8;
            else if (arg_18 == 1)
                var_24.y -= flt_429CCC;
        }
    }
    if (arg_8)
    {
#ifdef CODFH_SP // shape: block-scoped
        RwV3d var_70;
        RwV3d var_7C;
        RwV3d var_88;
        RwReal var_8C;
#endif
        var_70.x = 0.0f;
        var_70.y = 1.0f;
        var_70.z = 0.0f;
        RwV3dSubMacro(&var_7C, &var_44, &var_38);
        RwV3dCrossProductMacro(&var_88, &var_70, &var_7C);
        RwV3dNormalize(&var_88, &var_88);
        RwV3dIncrementScaledMacro(&var_38, &var_88, flt_429CBC);
        RwV3dIncrementScaledMacro(&var_44, &var_88, flt_429CBC);
        var_90 = !sub_D2FC0(&var_38, &var_44, arg_4, &var_8C, 1, unk_30, 1, 1,
                            0x180000, 1, 0); // not an address: collision flags
        unk_8A0.set_unk_139C(var_8C);
        if (var_90)
        {
            RwV3dIncrementScaledMacro(&var_38, &var_88, -flt_429CBC * 2);
            RwV3dIncrementScaledMacro(&var_44, &var_88, -flt_429CBC * 2);
            var_90 = !sub_D2FC0(&var_38, &var_44, arg_4, &var_8C, 1, unk_30, 1, 1,
                                0x180000, 1, 0); // not an address: collision flags
            unk_8A0.set_unk_139C(var_8C);
        }
        else if (arg_14)
        {
#ifdef CODFH_SP // shape: block-scoped
            RwV3d var_B4;
            RwReal var_B8;
#endif
            RwV3dSubMacro(&var_B4, &var_38, &var_44);
            RwV3dScaleMacro(&var_B4, &var_B4, var_8C);
            var_B8 = RwV3dDotProductMacro(&var_B4, &var_B4);
            if (var_B8 > 0.0001f)
            {
                do
                {
                    __m128 var_D0 = _mm_set_ss(var_B8);
                    __m128 var_F0 = _mm_sqrt_ss(var_D0);
                    _mm_store_ss((RwReal *)arg_14, var_F0);
                } while (0);
            }
            else
            {
                *(RwReal *)arg_14 = 0.0f;
            }
        }
    }
    else
    {
#ifdef CODFH_SP // shape: block-scoped
        RwReal var_114;
#endif
        var_90 = !sub_D2FC0(&var_38, &var_44, arg_4, &var_114, 1, unk_30, 1, 1,
                            0x180000, 1, 0); // not an address: collision flags
        unk_8A0.set_unk_139C(var_114);
        if (!var_90 && arg_14)
        {
#ifdef CODFH_SP // shape: block-scoped
            RwV3d var_12C;
            RwReal var_130;
#endif
            RwV3dSubMacro(&var_12C, &var_38, &var_44);
            RwV3dScaleMacro(&var_12C, &var_12C, var_114);
            var_130 = RwV3dDotProductMacro(&var_12C, &var_12C);
            if (var_130 > 0.0001f)
            {
                do
                {
                    __m128 var_150 = _mm_set_ss(var_130);
                    __m128 var_170 = _mm_sqrt_ss(var_150);
                    _mm_store_ss((RwReal *)arg_14, var_170);
                } while (0);
            }
            else
            {
                *(RwReal *)arg_14 = 0.0f;
            }
        }
    }
    if (arg_10)
        *arg_10 = var_8;
    return var_90;
}
// match: ?sub_13F350@type_3DAFC8@@QAEXM@Z @ 0x0013F350
// sp-match: ?sub_13F350@type_3DAFC8@@QAEXM@Z @ 0x000E9700
// Aims its mounted weapon from bone 0x190 while its animation drives it,
// else from its frame raised by its height by its posture's class; the
// argument is unused.
void type_3DAFC8::sub_13F350(RwReal arg_0)
{
    type_3DC9B0 *var_8;
    RpHAnimHierarchy *var_C;
    RwMatrix *var_10;
    RpHAnimHierarchy *var_14;
    RwInt32 var_18;
    RwMatrix *var_1C;
    RpClump *var_20;
    RwFrame *var_24;
    RwMatrix *var_28;
    RwMatrix var_70;
    RwV3d *var_74;

    var_8 = (type_3DC9B0 *)unk_618.sub_D4910();
    if (var_8)
    {
        if (unk_28_13)
        {
            var_C = unk_284->unk_18;
            var_10 = RpHAnimHierarchyGetMatrixArray(var_C);
            var_14 = unk_284->unk_18;
            var_18 = RpHAnimIDGetIndex(var_14, 0x190);
            var_1C = &var_10[var_18];
        }
        else
        {
            var_20 = unk_25C.unk_08;
            var_24 = RpClumpGetFrame(var_20);
            var_28 = RwFrameGetLTM(var_24);
            var_70 = *var_28;
            var_74 = RwMatrixGetPos(&var_70);
            if (vf_0BC() == 0)
                var_74->y += unk_48;
            else if (vf_0BC() == 1)
                var_74->y += unk_48 / 2.0f;
            else if (vf_0BC() == 2)
                var_74->y += unk_48 / 4.0f;
            else
                var_74->y += unk_48;
            var_1C = &var_70;
        }
        var_8->sub_16A440(var_1C);
    }
}
// match: ?sub_13F4D0@type_3DAFC8@@QAEXPAUtype_3D3548@@@Z @ 0x0013F4D0
// sp-match: ?sub_13F4D0@type_3DAFC8@@QAEXPAUtype_3D3548@@@Z @ 0x000E9800
void type_3DAFC8::sub_13F4D0(type_3D3548 *arg_0)
{
    unk_618.sub_D48D0(arg_0);
}
// match: ?sub_13F4F0@type_3DAFC8@@QAEXXZ @ 0x0013F4F0
// sp-match: ?sub_13F4F0@type_3DAFC8@@QAEXXZ @ 0x000E9810
void type_3DAFC8::sub_13F4F0()
{
    if (unk_600)
    {
        vf_1B4(0);
        unk_3E0.unk_A0 = 1;
        unk_3E0.unk_C4 = 0;
        unk_600 = 0;
    }
}
// match: ?vf_08C@type_3DAFC8@@UAEPAEHH@Z @ 0x0013F540
// sp-match: ?vf_08C@type_3DAFC8@@UAEPAEHH@Z @ 0x000E9850
// Its performance values (arg_4 1: the special idle ones), or for arg_0 set
// those of its performance kind.
RwUInt8 *type_3DAFC8::vf_08C(RwInt32 arg_0, RwInt32 arg_4)
{
    RwInt32 var_4;

    var_4 = arg_0 ? unk_848 : arg_4;
    switch (var_4)
    {
    case 1:
        return unk_858;
    default:
        return unk_84C;
    }
}
// match: ?sub_13F590@type_3DAFC8@@QAEHH@Z @ 0x0013F590
// sp-match: ?sub_13F590@type_3DAFC8@@QAEHH@Z @ 0x000E9880
// Mounts (arg_0 1) or dismounts the weapon unk_618 holds; 0 when it may not
// be mounted.
RwInt32 type_3DAFC8::sub_13F590(RwInt32 arg_0)
{
    type_3DC9B0 *var_4;

    var_4 = (type_3DC9B0 *)unk_618.sub_D4910();
    if (var_4)
    {
        unk_61C = arg_0;
        if (arg_0)
        {
            if (!var_4->sub_168E10(this))
            {
                unk_61C = 0;
                return 0;
            }
        }
        else
        {
            var_4->sub_169000(this);
            unk_618.sub_D48D0(0);
        }
        unk_3E0.sub_15D510(0, 0);
    }
    return 1;
}
// match: ?vf_098@type_3DAFC8@@UAEPAUtype_3D2E7C@@XZ @ 0x0013F620
// sp-match: ?vf_098@type_3DAFC8@@UAEPAUtype_3D2E7C@@XZ @ 0x000E98F0
type_3D2E7C *type_3DAFC8::vf_098()
{
    return (type_3D2E7C *)sub_67620(unk_840);
}
// match: ?vf_090@type_3DAFC8@@UAEPAUtype_6D380@@XZ @ 0x0013F640
// sp-match: ?vf_090@type_3DAFC8@@UAEPAUtype_6D380@@XZ @ 0x000E9900
struct type_6D380 *type_3DAFC8::vf_090()
{
    return (type_6D380 *)sub_67620(unk_844);
}
// match: ?sub_13F660@type_3DAFC8@@QAEXHH@Z @ 0x0013F660
// sp-match: ?sub_13F660@type_3DAFC8@@QAEXHH@Z @ 0x000E9910
// "EnableWeaponRender": shows (arg_4 set) or hides the model of its weapon
// (arg_0 0) or of its grenade (1).
void type_3DAFC8::sub_13F660(RwInt32 arg_0, RwInt32 arg_4)
{
    if (arg_0 == 0 && unk_3E0.get_unk_18())
    {
        if (arg_4)
            sub_16E080(unk_3E0.get_unk_18(), -1);
        else
            sub_16E080(unk_3E0.get_unk_18(), 0);
    }
    if (arg_0 == 1 && unk_4E0.get_unk_18())
    {
        if (arg_4)
            sub_16E080(unk_4E0.get_unk_18(), -1);
        else
            sub_16E080(unk_4E0.get_unk_18(), 0);
    }
}
// match: ?vf_058@type_3DAFC8@@UAEHPAUtype_3DF8D8_04@@@Z @ 0x0013F720
// sp-match: ?vf_058@type_3DAFC8@@UAEHPAUtype_3DF8D8_04@@@Z @ 0x000E9960
// Whether arg_0 is one of the keys (0 to 2) of its definition's model
// objects (sub_1917A0, sub_1917F0 and, when it has one, sub_191840).
RwInt32 type_3DAFC8::vf_058(type_3DF8D8_04 *arg_0)
{
    type_1917A0 *var_4;
    type_3DF8D8_04 *v8;
    type_1908A0 *stk_C;
    type_3DF8D8 *var_10;
    SoldierTrigger *lv_14;

    lv_14 = (SoldierTrigger *)get_unk_34C();
    var_10 = sub_198800(&lv_14->unk_D8);
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
// match: ?sub_13F940@type_3DAFC8@@QAEXM@Z @ 0x0013F940
// sp-match: ?sub_13F940@type_3DAFC8@@QAEXM@Z @ 0x000E9A90
// Adds arg_0 of its full hit points to its hit points (0 to full).
void type_3DAFC8::sub_13F940(RwReal arg_0)
{
    unk_1D20 += (RwInt32)(unk_1D24 * arg_0);
    if (unk_1D20 < 0)
        unk_1D20 = 0;
    if (unk_1D20 > unk_1D24)
        unk_1D20 = unk_1D24;
}
// match: ?vf_0B0@type_3DAFC8@@UAEXHH@Z @ 0x0013F9B0
// sp-match: ?vf_0B0@type_3DAFC8@@UAEXHH@Z @ 0x000E9AE0
// Sets its posture ("SetPosture") and derives vf_0B4's value.
void type_3DAFC8::vf_0B0(RwInt32 arg_0, RwInt32 arg_4)
{
    unk_864 = arg_0;
    vf_0B4();
}
