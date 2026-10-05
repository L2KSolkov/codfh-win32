// PlayerTrigger: its MakeNew, constructor, destructor, handlers and its
// settings' helpers. Its original file name is not in the image, so it is
// named for its start address.

#include <math.h>
#include <string.h>

#include "rw/ostypes.h"
#include "rw/baframe.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "rws/ceventhandler.h"
#include "game/data.h"
#include "game/functions.h"
#include "game/gameloop.h"
#include "game/weaponbank.h"
#include "types/PlayerTrigger.h"
#include "types/SoldierTrigger.h"
#include "types/type_10F710.h"
#include "types/type_4C19C0.h"
#include "types/type_72810.h"
#include "types/type_DA0A0.h"
#include "rws/csystemcommands.h"
#include "rw/baengine.h"
#include "game/worldmgr.h"
#include "game/mathutil.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003D5F84
extern const RwReal flt_3D5F84 = -5.0f;
// 0x003D5F88
extern const RwReal flt_3D5F88 = 16.666666f;
// 0x004B67E4
RwInt32 dword_4B67E4;
// End of its data definitions.


// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0O@BJJDFCIC@PlayerTrigger?$AA@ @ 0x003D5F74
// match: ?flt_3D5F84@@3MB @ 0x003D5F84
// match: ?flt_3D5F88@@3MB @ 0x003D5F88
// match: __real@3f1c61aa @ 0x003D5F8C
// match: ??_7PlayerTrigger@@6BCEventHandler@RWS@@@ @ 0x003D5F90
// match: ??_7PlayerTrigger@@6BCAttributeHandler@RWS@@@ @ 0x003D5F98
// match: ??_C@_0FH@EDEBPDOH@NOTE?3?5?$CB?$CB?$CB?5PlayerTrigger?3?5using?5p@ @ 0x003D5FC8
// match: ??_C@_0DO@ECHKBDID@Restoring?5Original?5Weapons?0?5Unlo@ @ 0x003D6020
// match: ??_C@_0DO@HMHGIFIJ@Flagging?5weapon?5?$CFd?8s?5def?5to?5init@ @ 0x003D6060
// match: ??_C@_0CM@MDBMBPEG@Assigning?5weapon?5?$CFd?8s?5def?5to?5wba@ @ 0x003D60A0
// match: ??_C@_0CE@JDEKFELG@GameWeapons?$CLDeathAnims?$CLBipod_Fre@ @ 0x003D60CC
// match: ??_C@_0CE@PPCMEBKF@GameWeapons?$CLDeathAnims?$CLProne_Fre@ @ 0x003D60F0
// match: ??_C@_0CF@FAIIFJEG@GameWeapons?$CLDeathAnims?$CLCrouch_Fr@ @ 0x003D6114
// match: ??_C@_0CG@KFNDHADD@GameWeapons?$CLDeathAnims?$CLStand_Fre@ @ 0x003D613C
// match: ??_C@_0CG@IOPOCDPA@GameWeapons?$CLDeathAnims?$CLStand_Fre@ @ 0x003D6164
// match: ??_C@_0CD@LAJHKAA@GameWeapons?$CLDeathAnims?$CLBipod_Dea@ @ 0x003D618C
// match: ??_C@_0CD@GLIJIEFE@GameWeapons?$CLDeathAnims?$CLProne_Dea@ @ 0x003D61B0
// match: ??_C@_0CE@MFIKCLPN@GameWeapons?$CLDeathAnims?$CLCrouch_De@ @ 0x003D61D4
// match: ??_C@_0CF@ELNKLCMM@GameWeapons?$CLDeathAnims?$CLStand_Dea@ @ 0x003D61F8
// match: ??_C@_0CF@GAPHOBAP@GameWeapons?$CLDeathAnims?$CLStand_Dea@ @ 0x003D6220
// match: ??_C@_0CA@HNGDGOCL@GameWeapons?$CLDeathAnims?$CLPPSH_Hit?$AA@ @ 0x003D6248
// match: __ehhandler$?MakeNew@PlayerTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041BEA8
// match: __ehhandler$?MakeNew@PlayerTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041BEB0
// match: __ehhandler$??0PlayerTrigger@@QAE@ABVCAttributePacket@RWS@@@Z>1>8 @ 0x0041BECC
// match: __ehhandler$??0PlayerTrigger@@QAE@ABVCAttributePacket@RWS@@@Z>1 @ 0x0041BEDC
// match: __ehhandler$??1PlayerTrigger@@UAE@XZ>1>8 @ 0x0041BEF8
// match: __ehhandler$??1PlayerTrigger@@UAE@XZ>1 @ 0x0041BF08
// match: .CRT$XCU+0 @ 0x00426F38
// match: ?pPlayerTriggerClassID@PlayerTrigger@@2PBDB @ 0x0042917C

// match: _$E2 @ 0x0030A8D0
// match: _$E3 @ 0x0030E0C0

// PlayerTrigger's registration initializer passes this exit to atexit.

RWS_IMPLEMENT_CLASSID(PlayerTrigger);
RWS_REGISTERCLASS(PlayerTrigger);
// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@PlayerTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000A9980
// match: __ehhandler$?MakeNew@PlayerTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x003000F0
// match: __ehhandler$?MakeNew@PlayerTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x003000FF
RWS_DEFINE_MAKENEW(PlayerTrigger)

// match: ??0PlayerTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000A9A00
// match: __ehhandler$??0PlayerTrigger@@QAE@ABVCAttributePacket@RWS@@@Z-0x16 @ 0x00300110
// match: __ehhandler$??0PlayerTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x00300126
PlayerTrigger::PlayerTrigger(const RWS::CAttributePacket &attr) : Trigger(attr)
{
    RwInt32 var_10;

    unk_C4 = 0;
    unk_C8 = 0;
    unk_C0 = -1;
    unk_D4 = 100.5f;
    unk_D8 = 52.6f;
    unk_DC = 90.0f;
    unk_F0 = ((RwReal)tan(0.61086524f));
    unk_F4 = 0;
    unk_F8 = 0;
    unk_E4.set(0.0f, 0.0f, 0.0f);
    unk_E0 = flt_3D5F84;
    unk_FC = 100;
    unk_100 = 0;
    unk_104 = 0;
    unk_254 = 0;
    unk_300 = 0;
    unk_28.unk_00 = 0;
    unk_28.unk_04 = 0;
    unk_140 = 0;
    unk_144 = 120.0f;
    unk_148 = 55.0f;
    unk_14C = 0;
    unk_150 = 24.0f;
    unk_154 = 1.0f;
    unk_15C = 0;
    unk_160 = 0.1f;
    unk_164 = 2.0f;
    unk_170 = 2.0f;
    unk_168 = 2.0f;
    unk_174 = 2.0f;
    unk_16C = 2.0f;
    unk_178 = 2.0f;
    unk_17C = 2.0f;
    unk_180 = 2.0f;
    unk_1B4 = 2.0f;
    unk_1B8 = 2.0f;
    unk_1BC = 1.0f;
    unk_1C0 = 2.0f;
    unk_1C4 = 1.0f;
    unk_1C8 = 1.0f;
    unk_1D4 = 7;
    unk_1D8 = 0.75f;
    unk_1E0 = 0.6f;
    unk_1DC = 0.5f;
    unk_1EC = 2.0f;
    unk_1E8 = 2.0f;
    unk_1E4 = 2.0f;
    unk_1F0 = 2.0f;
    unk_204 = 0.5f;
    unk_210 = 3.0f;
    unk_214 = 0.5f;
    unk_218 = 3.0f;
    unk_21C = 0.1f;
    unk_220 = 0.4f;
    unk_224 = 0.1f;
    unk_228 = 0.4f;
    unk_22C = 0.155f;
    unk_230 = 0.43f;
    unk_234 = 0.155f;
    unk_238 = 0.43f;
    unk_23C = 300.0f;
    unk_240 = 1000.0f;
    unk_304 = 1;
    unk_308 = 1.0f;
    unk_30C = 0;
    unk_310 = 0.8f;
    unk_314 = 1.3f;
    unk_318 = 0.8f;
    unk_31C = 0.2f;
    unk_320 = 400.0f;
    unk_324 = 0.4f;
    unk_328 = 30.0f;
    unk_32C = 70.0f;
    unk_330 = 90.0f;
    unk_334 = 2000.0f;
    unk_338 = 1;
    unk_33C = 1.0f;
    unk_340 = 5;
    unk_344 = 0.1f;
    unk_348 = 1;
    unk_34C = 1.4f;
    unk_350 = 100.0f;
    unk_354 = 0.03f;
    unk_358 = 0.05f;
    unk_35C = 0.1f;
    unk_360 = 1.0f;
    unk_364 = 12.0f;
    unk_370 = 15.0f;
    unk_368 = 4.0f;
    unk_374 = 6.0f;
    unk_36C = 2.0f;
    unk_378 = 3.0f;
    unk_37C = 12.0f;
    unk_380 = 0;
    unk_430 = 0;
    unk_434 = 0;
    unk_428 = 0;
    unk_42C = 0;
    unk_420 = 0;
    unk_424 = 0;
    unk_438 = 0;
    unk_468 = 0;
    unk_184.set(-0.5f, 0.0f, -0.5f);
    unk_190.set(-0.5f, 0.0f, -0.5f);
    unk_19C.set(-0.5f, -0.5f, -0.5f);
    unk_1A8.set(-0.5f, -0.5f, -0.5f);
    for (var_10 = 0; var_10 < 2; var_10++)
    {
        unk_108[var_10] = -1;
    }
    unk_450.unk_00 = 0;
    unk_450.unk_04 = 0;
    unk_458.unk_00 = 0;
    unk_458.unk_04 = 0;
    unk_460.unk_00 = 0;
    unk_460.unk_04 = 0;
    unk_24C.unk_00 = 0x66970600;
    unk_24C.unk_04 = 0x5621B158;
    unk_43C.unk_00 = 0;
    unk_43C.unk_04 = 0;
    unk_444.set(0.0f, 0.0f, 0.0f);
    LinkMsg(iMsgSparkStartSystem, 0, 0x8000);
    LinkMsg(dword_4B8750, 0, 0x8000);
    LinkMsg(RWS::iMsgStartSystem, 0, 0x8000);
    LinkMsg(dword_4B67B8, 0, 0x8000);
    LinkMsg(dword_4B67C0, 0, 0x8000);
    LinkMsg(dword_4B67B0, 0, 0x8000);
}

// match: ?vf_01C@PlayerTrigger@@UAEPAUtype_3DF8D8_04@@XZ @ 0x000AA2B0

// match: ??_GPlayerTrigger@@UAEPAXI@Z @ 0x000AA2D0

// match: ??1PlayerTrigger@@UAE@XZ @ 0x000AA2F0
// match: __ehhandler$??1PlayerTrigger@@UAE@XZ-0x16 @ 0x00300130
// match: __ehhandler$??1PlayerTrigger@@UAE@XZ @ 0x00300146
PlayerTrigger::~PlayerTrigger()
{
    type_3D3548 *var_10 = unk_46C.sub_D4910();

    if (var_10)
        delete var_10;
    UnLinkMsg(iMsgSparkStartSystem);
    UnLinkMsg(dword_4B8750);
    UnLinkMsg(RWS::iMsgStartSystem);
    UnLinkMsg(dword_4B67B8);
    UnLinkMsg(dword_4B67C0);
    UnLinkMsg(dword_4B67B0);
}

// match: ?sub_AA3F0@@YAXXZ @ 0x000AA3F0
void sub_AA3F0()
{
    dword_4B67E4 = 0;
}

// match: ?HandleAttributes@PlayerTrigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000AA400
void PlayerTrigger::HandleAttributes(const RWS::CAttributePacket &attr)
{
    RwInt32 slot_C;
    RwInt32 bp_8;
    const RwInt32 *bp_4;
    type_10F710 *d20;

    Trigger::HandleAttributes(attr);
    RWS::CAttributeCommandIterator l28(attr, RWS::CSystemCommands::pCSystemCommandsClassID);

    while (!l28.IsFinished())
    {
        switch (l28->GetCommandId())
        {
        case RWS::CSystemCommands::CMD_LoadMatrix:
            sub_ACEA0();
            break;
        }
        ++l28;
    }
    d20 = (type_10F710 *)unk_46C.sub_D4910();
    RWS::CAttributeCommandIterator ebp_1C(attr, RWS_CLASSID_OF(PlayerTrigger));

    while (!ebp_1C.IsFinished())
    {
        switch (ebp_1C->GetCommandId())
        {
        case 2:
            unk_C0 = ebp_1C->GetAs_RwInt32();
            if (d20)
            {
                sub_1745C0(d20, d20->unk_3D4);
                sub_ACF10(d20);
                sub_174580(d20, unk_C0);
            }
            break;
        }
        ++ebp_1C;
    }
    RWS::CAttributeCommandIterator b14(attr, RWS_CLASSID_OF(PlayerTrigger));

    while (!b14.IsFinished())
    {
        switch (b14->GetCommandId())
        {
        case 20:
            b14->GetCommandData(unk_450);
            if (unk_450.unk_00 || unk_450.unk_04)
            {
                sub_198900((type_3DF8D8_04 *)&unk_450, 10, 0, 0, 0, 0);
            }
            break;
        case 21:
            b14->GetCommandData(unk_458);
            if (unk_458.unk_00 || unk_458.unk_04)
            {
                sub_198900((type_3DF8D8_04 *)&unk_458, 12, 0, 0, 0, 0);
            }
            break;
        case 22:
            b14->GetCommandData(unk_204);
            break;
        case 23:
            b14->GetCommandData(unk_210);
            break;
        case 26:
            b14->GetCommandData(unk_214);
            break;
        case 27:
            b14->GetCommandData(unk_218);
            break;
        case 24:
            b14->GetCommandData(unk_21C);
            break;
        case 25:
            b14->GetCommandData(unk_220);
            break;
        case 28:
            b14->GetCommandData(unk_224);
            break;
        case 29:
            b14->GetCommandData(unk_228);
            break;
        case 19:
            b14->GetCommandData(unk_460);
            if (unk_460.unk_00)
            {
                sub_198900((type_3DF8D8_04 *)&unk_460, 46, 0, 0, 0, 0);
            }
            break;
        case 1:
            b14->GetCommandData(unk_CC);
            if (unk_CC.unk_00 || unk_CC.unk_04)
            {
                sub_198900((type_3DF8D8_04 *)&unk_CC, 3, 0, 0, 0, 0);
            }
            break;
        case 3:
            unk_C4 = b14->GetAs_RwInt32();
            sub_ACF10(d20);
            break;
        case 0:
            b14->GetCommandData(unk_244);
            if (unk_244.unk_00)
            {
                sub_198900((type_3DF8D8_04 *)&unk_244, 46, 0, 0, 0, 0);
            }
            break;
        case 4:
            unk_C8 = b14->GetAs_RwInt32();
            sub_ACF10(d20);
            break;
        case 6:
            unk_FC = b14->GetAs_RwInt32();
            sub_ACF10(d20);
            break;
        case 7:
            unk_100 = b14->GetAs_RwInt32();
            sub_ACF10(d20);
        case 8:
            unk_104 = b14->GetAs_RwInt32();
            sub_ACF10(d20);
            break;
        case 30:
            b14->GetCommandData(unk_D4);
            sub_ACF10(d20);
            break;
        case 31:
            b14->GetCommandData(unk_D8);
            sub_ACF10(d20);
            break;
        case 32:
            b14->GetCommandData(unk_DC);
            sub_ACF10(d20);
            break;
        case 65:
            b14->GetCommandData(unk_E0);
            sub_ACF10(d20);
            break;
        case 33:
            b14->GetCommandData(unk_E4);
            sub_ACF10(d20);
            break;
        case 18:
        {
            RwInt32 ebp_50;
            RwInt32 o4C;
            RwReal q48;
            RwVideoMode v44;
            RwReal stk_2C;

            b14->GetCommandData(q48);
            q48 = q48 * 0.5f * 0.017453292f;
            unk_F0 = tan_ref(q48);
            ebp_50 = ((RwCamera *)dword_4E5C74)->frameBuffer->width;
            o4C = ((RwCamera *)dword_4E5C74)->frameBuffer->height;
            RwEngineGetVideoModeInfo(&v44, RwEngineGetCurrentVideoMode());
            if (v44.flags & 4)
                o4C *= 2;
            unk_F8 = ((RwReal)cos(stk_2C = o4C * q48 / ebp_50));
            q48 = q48 * 0.8f;
            unk_F4 = cos_ref(q48);
            sub_ACF10(d20);
            break;
        }
        case 5:
        {
            RwInt32 q68;
            RwInt32 var_64;
            RwInt32 stk_60;
            type_4C19C0 *y5C;
            type_3DF8D8 *slot_58;
            RwInt32 lv_54;

            unk_254 = 0;
            unk_300 = 0;
            memset(unk_384, -1, 0x9C);
            lv_54 = 0;
            bp_4 = (const RwInt32 *)b14->GetAs_RwChar_ptr();
            bp_8 = *bp_4++;
            if (bp_8 != 999)
            {
                memset(unk_114, 0, 0x27);
                if (bp_8)
                {
                    for (var_64 = 0; var_64 < bp_8; var_64++)
                    {
                        q68 = *bp_4;
                        if (q68 == 0x15 || q68 == 0x1F || q68 == 0x21 || q68 == 0x14 ||
                            q68 == 0x16 || q68 == 0x13 || q68 == 0x22 || q68 == 0x26)
                            unk_114[q68] = 1;
                        bp_4++;
                    }
                }
                stk_60 = *bp_4++;
                for (slot_C = 0; slot_C < 2; slot_C++)
                {
                    unk_108[slot_C] = -1;
                }
                for (slot_C = 0; slot_C < stk_60; slot_C++)
                {
                    unk_108[slot_C] = *bp_4;
                    if (unk_108[slot_C] == 0x1E || unk_108[slot_C] == 0x24)
                        unk_108[slot_C] = -1;
                    bp_4++;
                }
                unk_13C = *bp_4;
                if (unk_13C == 0x1E || unk_13C == 0x24)
                    unk_13C = -1;
                lv_54 = 0x1D;
            }
            else
            {
                memset(unk_114, 0, 0x27);
                unk_108[1] = -1;
                unk_108[0] = -1;
                unk_13C = -1;
                lv_54 = 0x1D;
                if (unk_254)
                {
                    RwUInt32 frm_9C;
                    RwInt32 local_98;
                    RwUInt32 local_94;
                    RwUInt32 ebp_90;
                    RwUInt32 stk_8C;
                    RwUInt32 stk_88;
                    RwInt32 lcl_84;
                    RwUInt32 lv_80;
                    RwInt32 r7C;
                    RwInt32 m_78;
                    type_D90B0 *m_74;
                    RwInt32 frm_70;
                    RwInt32 q6C;

                    sub_19A750("NOTE: !!! PlayerTrigger: using player attribs from previous level or from memCard !!!\n");
                    memset(unk_258, -1, 8);
                    memset(unk_264, -1, 0x9C);
                    unk_260 = -1;
                    unk_300 = 1;
                    frm_70 = *bp_4++;
                    unk_258[0] = frm_70;
                    unk_264[frm_70] = *bp_4++;
                    frm_70 = *bp_4++;
                    if (frm_70 != 999)
                    {
                        unk_258[1] = frm_70;
                        unk_264[frm_70] = *bp_4++;
                    }
                    else
                        bp_4++;
                    m_74 = &dword_4F28F0->unk_5C;
                    r7C = -1;
                    for (lv_80 = 0; lv_80 < 2; lv_80++)
                    {
                        if (m_74->unk_08[lv_80] != 999)
                        {
                            if (m_74->unk_08[lv_80] == 0x1D)
                                r7C = lv_80;
                            else
                            {
                                unk_114[m_74->unk_08[lv_80]] = 1;
                                unk_108[lv_80] = m_74->unk_08[lv_80];
                                unk_384[m_74->unk_08[lv_80]] = m_74->unk_10[lv_80];
                            }
                        }
                    }
                    if (r7C != -1)
                    {
                        lcl_84 = -1;

                        for (stk_88 = 0; stk_88 < 2; stk_88++)
                        {
                            if (unk_258[stk_88] != -1)
                            {
                                stk_8C = 0;

                                for (stk_8C = 0; stk_8C < 2; stk_8C++)
                                {
                                    if (unk_108[stk_8C] == unk_258[stk_88])
                                        break;
                                }
                                if (stk_8C == 2)
                                {
                                    lcl_84 = stk_88;
                                    break;
                                }
                            }
                        }
                        if (lcl_84 != -1)
                        {
                            unk_114[unk_258[lcl_84]] = 1;
                            unk_108[r7C] = unk_258[lcl_84];
                            unk_384[unk_258[lcl_84]] = unk_264[unk_258[lcl_84]];
                        }
                    }
                    if (m_74->unk_00 != 0x1D)
                        unk_13C = m_74->unk_00;
                    else
                    {
                        unk_13C = unk_108[r7C];
                        if (unk_13C == -1)
                        {
                            for (ebp_90 = 0; ebp_90 < 2; ebp_90++)
                            {
                                if (unk_108[ebp_90] != -1)
                                {
                                    unk_13C = unk_108[ebp_90];
                                    break;
                                }
                            }
                        }
                    }
                    if (*bp_4++ != 999)
                    {
                        unk_260 = bp_4[-1];
                        for (local_94 = 0; local_94 < 2; local_94++)
                        {
                            if (unk_260 == unk_108[local_94])
                                break;
                        }
                        if (local_94 == 2)
                            lv_54 = unk_260;
                    }
                    q6C = *bp_4++;
                    if (q6C)
                    {
                        for (local_98 = 0; local_98 < q6C; local_98++)
                        {
                            frm_70 = *bp_4++;
                            unk_114[frm_70] = 1;
                            unk_384[frm_70] = *bp_4;
                            unk_264[frm_70] = *bp_4;
                            bp_4++;
                        }
                    }
                    for (frm_9C = 0; frm_9C < 13; frm_9C++)
                    {
                        if (m_74->unk_18.unk_04[frm_9C])
                        {
                            switch (frm_9C)
                            {
                            case 2:
                                m_78 = 0x15;
                                break;
                            case 7:
                                m_78 = 0x21;
                                break;
                            case 5:
                                m_78 = 0x1F;
                                break;
                            case 8:
                                m_78 = 0x14;
                                break;
                            case 9:
                                m_78 = 0x16;
                                break;
                            case 10:
                                m_78 = 0x13;
                                break;
                            case 11:
                                m_78 = 0x22;
                                break;
                            case 12:
                                m_78 = 0x26;
                                break;
                            default:
                                m_78 = -1;
                            }
                            if (m_78 != -1)
                            {
                                if (!unk_114[m_78])
                                {
                                    unk_114[m_78] = 1;
                                    unk_384[m_78] = m_74->unk_18.unk_04[frm_9C];
                                }
                                else if (m_74->unk_18.unk_04[frm_9C] > unk_384[m_78])
                                    unk_384[m_78] = m_74->unk_18.unk_04[frm_9C];
                            }
                        }
                    }
                    unk_FC = m_74->unk_50;
                }
                else
                {
                    RwInt32 m_BC;
                    RwInt32 local_B8;
                    RwInt32 local_B4;
                    RwInt32 ebp_B0;
                    RwInt32 local_AC;
                    RwInt32 pA8;
                    RwInt32 varA4;
                    RwInt32 locA0;

                    varA4 = *bp_4++;
                    unk_114[varA4] = 1;
                    unk_13C = varA4;
                    unk_108[0] = varA4;
                    pA8 = *bp_4++;
                    unk_384[varA4] = pA8;
                    local_B8 = *bp_4++;
                    if (local_B8 != 999)
                    {
                        unk_114[local_B8] = 1;
                        unk_108[1] = local_B8;
                    }
                    local_AC = *bp_4++;
                    if (local_B8 != 999)
                        unk_384[local_B8] = local_AC;
                    lv_54 = *bp_4++;
                    if (lv_54 == 999)
                        lv_54 = 0x1D;
                    locA0 = *bp_4++;
                    if (locA0)
                    {
                        for (m_BC = 0; m_BC < locA0; m_BC++)
                        {
                            local_B4 = *bp_4++;
                            ebp_B0 = *bp_4++;
                            unk_114[local_B4] = 1;
                            unk_384[local_B4] = ebp_B0;
                        }
                    }
                }
            }
            y5C = 0;
            for (slot_C = 0; slot_C < 0x27; slot_C++)
            {
                y5C = sub_119B70(slot_C);
                if (y5C)
                {
                    slot_58 = (type_3DF8D8 *)sub_198900((type_3DF8D8_04 *)y5C, 5, 0, 0, 0, 0);
                    slot_58->unk_0C = 1;
                    if (unk_114[slot_C])
                        slot_58->unk_0C = 0;
                    for (RwInt32 var_C0 = 0; var_C0 < 2; var_C0++)
                    {
                        if (unk_108[var_C0] != -1 && unk_108[var_C0] == slot_C)
                        {
                            sub_ACDB0(slot_C, var_C0);
                            slot_58->unk_18 = var_C0;
                            break;
                        }
                    }
                }
            }
            break;
        }
        case 107:
            b14->GetCommandData(unk_140);
            break;
        case 111:
            skip_value(b14->GetAs_RwInt32());
            break;
        case 13:
            b14->GetCommandData(unk_144);
            break;
        case 14:
            b14->GetCommandData(unk_148);
            break;
        case 15:
            b14->GetCommandData(unk_14C);
            break;
        case 16:
            b14->GetCommandData(unk_150);
            break;
        case 54:
            b14->GetCommandData(unk_158);
            sub_ACA70();
            break;
        case 53:
            b14->GetCommandData(unk_15C);
            break;
        case 17:
            b14->GetCommandData(unk_160);
            break;
        case 38:
            b14->GetCommandData(unk_164);
            break;
        case 42:
            b14->GetCommandData(unk_170);
            break;
        case 39:
            b14->GetCommandData(unk_168);
            break;
        case 43:
            b14->GetCommandData(unk_174);
            break;
        case 40:
            b14->GetCommandData(unk_16C);
            break;
        case 44:
            b14->GetCommandData(unk_178);
            break;
        case 41:
            b14->GetCommandData(unk_17C);
            break;
        case 45:
            b14->GetCommandData(unk_180);
            break;
        case 46:
            b14->GetCommandData(unk_184);
            break;
        case 47:
            b14->GetCommandData(unk_190);
            break;
        case 59:
            b14->GetCommandData(unk_19C);
            break;
        case 60:
            b14->GetCommandData(unk_1A8);
            break;
        case 9:
            b14->GetCommandData(unk_1FC);
            break;
        case 11:
            b14->GetCommandData(unk_20C);
            break;
        case 10:
            b14->GetCommandData(unk_200);
            break;
        case 72:
            b14->GetCommandData(unk_314);
            break;
        case 73:
            b14->GetCommandData(unk_318);
            break;
        case 48:
            b14->GetCommandData(unk_1C0);
            sub_ACA70();
            break;
        case 49:
            b14->GetCommandData(unk_1B8);
            break;
        case 50:
            b14->GetCommandData(unk_1D0);
            sub_ACA70();
            break;
        case 51:
            b14->GetCommandData(unk_1C4);
            sub_ACA70();
            break;
        case 52:
            b14->GetCommandData(unk_1C8);
            sub_ACA70();
            break;
        case 55:
            b14->GetCommandData(unk_22C);
            break;
        case 90:
            b14->GetCommandData(unk_35C);
            break;
        case 56:
            b14->GetCommandData(unk_230);
            break;
        case 57:
            b14->GetCommandData(unk_234);
            break;
        case 58:
            b14->GetCommandData(unk_238);
            break;
        case 61:
            b14->GetCommandData(unk_1D4);
            break;
        case 62:
            b14->GetCommandData(unk_1D8);
            break;
        case 63:
            b14->GetCommandData(unk_1E0);
            break;
        case 64:
            b14->GetCommandData(unk_1DC);
            break;
        case 34:
            b14->GetCommandData(unk_1E4);
            break;
        case 35:
            b14->GetCommandData(unk_1E8);
            break;
        case 36:
            b14->GetCommandData(unk_1EC);
            break;
        case 66:
            b14->GetCommandData(unk_23C);
            unk_23C = unk_23C * 100.0f;
            break;
        case 67:
            b14->GetCommandData(unk_240);
            unk_240 = unk_240 * 100.0f;
            break;
        case 37:
            b14->GetCommandData(unk_1F0);
            break;
        case 100:
            unk_420 = b14->GetAs_RwReal();
            break;
        case 101:
            unk_424 = b14->GetAs_RwReal();
            break;
        case 102:
            unk_428 = (RwReal)(RwUInt32)b14->GetAs_RwReal();
            break;
        case 103:
            unk_42C = (RwReal)(RwUInt32)b14->GetAs_RwReal();
            break;
        case 104:
            unk_430 = (RwReal)(RwUInt32)b14->GetAs_RwReal();
            break;
        case 105:
            unk_434 = (RwReal)(RwUInt32)b14->GetAs_RwReal();
            break;
        case 106:
            unk_438 = (RwReal)(RwUInt32)b14->GetAs_RwReal();
            break;
        case 113:
            b14->GetCommandData(unk_43C);
            break;
        case 114:
            b14->GetCommandData(unk_444);
            break;
        case 115:
        {
            RwInt32 var_C4 = 0;

            b14->GetCommandData(var_C4);
            if (var_C4)
            {
                type_3DFEEC *var_CC;
                type_3DF8D8 *var_C8 = sub_198800(&unk_43C);

                var_CC = (type_3DFEEC *)var_C8;

                if (sub_1745A0(0))
                    ((type_10F710 *)sub_1745A0(0))->vf_234(var_CC->unk_24, &unk_444);
            }
            break;
        }
        case 68:
            b14->GetCommandData(unk_304);
            break;
        case 69:
            b14->GetCommandData(unk_308);
            break;
        case 70:
            b14->GetCommandData(unk_30C);
            break;
        case 71:
            b14->GetCommandData(unk_310);
            break;
        case 74:
            b14->GetCommandData(unk_31C);
            break;
        case 75:
            b14->GetCommandData(unk_320);
            break;
        case 76:
            b14->GetCommandData(unk_324);
            break;
        case 77:
            b14->GetCommandData(unk_328);
            break;
        case 78:
            b14->GetCommandData(unk_32C);
            break;
        case 79:
            b14->GetCommandData(unk_330);
            break;
        case 80:
            b14->GetCommandData(unk_334);
            break;
        case 81:
            b14->GetCommandData(unk_338);
            break;
        case 82:
            b14->GetCommandData(unk_33C);
            break;
        case 83:
            b14->GetCommandData(unk_340);
            break;
        case 84:
            b14->GetCommandData(unk_344);
            break;
        case 85:
            b14->GetCommandData(unk_348);
            break;
        case 86:
            b14->GetCommandData(unk_34C);
            break;
        case 87:
            b14->GetCommandData(unk_350);
            break;
        case 88:
            b14->GetCommandData(unk_354);
            break;
        case 89:
            b14->GetCommandData(unk_358);
            break;
        case 91:
            b14->GetCommandData(unk_360);
            break;
        case 92:
            b14->GetCommandData(unk_364);
            break;
        case 93:
            b14->GetCommandData(unk_370);
            break;
        case 94:
            b14->GetCommandData(unk_368);
            break;
        case 95:
            b14->GetCommandData(unk_374);
            break;
        case 96:
            b14->GetCommandData(unk_36C);
            break;
        case 97:
            b14->GetCommandData(unk_378);
            break;
        case 99:
            b14->GetCommandData(unk_380);
            break;
        case 98:
            b14->GetCommandData(unk_37C);
        }
        ++b14;
    }
}

// match: ?sub_AC900@PlayerTrigger@@QAEXXZ @ 0x000AC900
void PlayerTrigger::sub_AC900()
{
    RwInt32 lv_10;
    type_4C19C0 *slot_C;
    RwInt32 bp_8;
    RwInt32 bp_4;

    memset(unk_114, 0, 0x27);
    memset(unk_384, -1, 0x9C);
    for (bp_4 = 0; bp_4 < 0x27; bp_4++)
    {
        if (unk_264[bp_4] != -1)
        {
            unk_114[bp_4] = 1;
            unk_384[bp_4] = unk_264[bp_4];
        }
        else
            unk_384[bp_4] = -1;
    }
    sub_19A750("Restoring Original Weapons, Unloading current banks -=]MF[=-\n");
    sub_16FD10();
    for (bp_8 = 0; bp_8 < 2; bp_8++)
    {
        unk_108[bp_8] = unk_258[bp_8];
        if (unk_108[bp_8] != -1)
        {
            unk_114[unk_108[bp_8]] = 1;
            slot_C = sub_119B70(unk_108[bp_8]);
            lv_10 = slot_C->unk_24;
            dword_4E54E8[bp_8] = lv_10;
            sub_16F2C0(bp_8, slot_C->unk_24);
        }
    }
    unk_13C = unk_108[0];
}

// match: ?sub_ACA70@PlayerTrigger@@QAEXXZ @ 0x000ACA70
void PlayerTrigger::sub_ACA70()
{
    switch (dword_4F28F0->get_unk_18_direct())
    {
    case 0:
        unk_1B4 = unk_1C0 * unk_1C4;
        unk_1CC = unk_1D0 * unk_1C4;
        unk_154 = unk_158 * unk_1C4;
        unk_1F8 = unk_200 * unk_318;
        unk_1F4 = unk_1FC * unk_318;
        unk_208 = unk_20C * unk_318;
        break;
    case 2:
        unk_1B4 = unk_1C0 * unk_1C8;
        unk_1CC = unk_1D0 * unk_1C8;
        unk_154 = unk_158 * unk_1C8;
        unk_1F8 = unk_200 * unk_314;
        unk_1F4 = unk_1FC * unk_314;
        unk_208 = unk_20C * unk_314;
        break;
    default:
        unk_1B4 = unk_1C0;
        unk_1CC = unk_1D0;
        unk_154 = unk_158;
        unk_1F8 = unk_200;
        unk_1F4 = unk_1FC;
        unk_208 = unk_20C;
    }
}

// match: ?HandleEvents@PlayerTrigger@@UAEXAAVCMsg@RWS@@@Z @ 0x000ACC60
void PlayerTrigger::HandleEvents(RWS::CMsg &pMsg)
{
    Trigger::HandleEvents(pMsg);
    if (pMsg.Id.p_msgrec == RWS::iMsgStartSystem.p_msgrec)
    {
        sub_AD030();
        UnLinkMsg(RWS::iMsgStartSystem);
    }
    else if (pMsg.Id.p_msgrec == iMsgSparkStartSystem.p_msgrec)
    {
        UnLinkMsg(iMsgSparkStartSystem);
    }
    else if (pMsg.Id.p_msgrec == dword_4B8750.p_msgrec)
    {
        sub_ACE00();
        unk_468 = 1;
        UnLinkMsg(dword_4B8750);
    }
    else if (pMsg.Id.p_msgrec == dword_4B67B0.p_msgrec)
    {
        if (unk_300)
        {
            unk_300 = 0;
            sub_AC900();
        }
        sub_ACE00();
        type_10F710 *var_4 = (type_10F710 *)unk_46C.sub_D4910();

        var_4->sub_FF210();
        sub_ACEA0();
    }
    else if (pMsg.Id.p_msgrec == dword_4B67B8.p_msgrec)
    {
        type_3D3548 *var_8 = unk_46C.sub_D4910();

        if (var_8)
            delete var_8;
    }
}

// match: ?sub_ACDB0@PlayerTrigger@@QAEXHH@Z @ 0x000ACDB0
void PlayerTrigger::sub_ACDB0(RwInt32 arg_0, RwInt32 arg_4)
{
    type_4C19C0 *bp_8;
    type_3DF8D8 *bp_4;

    bp_8 = sub_119B70(arg_0);
    bp_4 = (type_3DF8D8 *)sub_198900((type_3DF8D8_04 *)bp_8, 5, 0, 0, 0, 0);

    bp_4->unk_0C = 2;
    unk_114[arg_0] = 1;
}

// match: ?sub_ACE00@PlayerTrigger@@QAEXXZ @ 0x000ACE00
void PlayerTrigger::sub_ACE00()
{
    RwInt32 lv_10;
    type_4C19C0 *slot_C;
    type_1917A0 *bp_8;
    RwInt32 bp_4;

    for (bp_4 = 0; bp_4 < 0x27; bp_4++)
    {
        slot_C = sub_119B70(bp_4);
        bp_8 = (type_1917A0 *)sub_198800((type_3DF8D8_04 *)slot_C);
        lv_10 = bp_8->unk_44;
        slot_C->unk_24 = lv_10;
        sub_19A750("Assigning weapon %d's def to wbank_%02d.bin", bp_4, slot_C->unk_24);
        if (unk_114[bp_4])
            sub_19A750("Flagging weapon %d's def to initialize geometry on game start", bp_4);
    }
}

// match: ?sub_ACEA0@PlayerTrigger@@QAEXXZ @ 0x000ACEA0
void PlayerTrigger::sub_ACEA0()
{
    type_3D3548 *var_4 = unk_46C.sub_D4910();

    if (var_4)
    {
        RwFrame *var_8 = var_4->get_unk_340();

        if (var_8)
        {
            RwMatrix *var_C;

            if (var_C = RwFrameGetMatrix(var_8))
            {
                *var_C = unk_60_m;
                RwFrameUpdateObjects(var_8);
            }
        }
    }
}

// match: ?sub_ACF10@PlayerTrigger@@QAEXPAUtype_10F710@@@Z @ 0x000ACF10
void PlayerTrigger::sub_ACF10(type_10F710 *arg_0)
{
    if (arg_0)
    {
        arg_0->unk_3D4 = unk_C0;
        arg_0->unk_3D8 = unk_C4;
        arg_0->unk_3DC = unk_C8;
        arg_0->unk_48 = unk_D4;
        arg_0->unk_50_r = unk_D8;
        arg_0->unk_4C = unk_DC;
        arg_0->unk_108 = unk_E0;
        arg_0->unk_3C_v = unk_E4;
        arg_0->unk_534 = unk_F0;
        arg_0->unk_53C = unk_F4;
        arg_0->unk_540 = unk_F8;
        arg_0->unk_19E0 = unk_FC;
        arg_0->unk_19E4 = (RwReal)unk_100;
        arg_0->unk_19E8 = (RwReal)unk_104;
    }
}

// match: ?sub_AD030@PlayerTrigger@@QAEXXZ @ 0x000AD030
void PlayerTrigger::sub_AD030()
{
    if (dword_4B67E4)
        return;
    sub_198900((type_3DF8D8_04 *)&unk_24C, 3, 0, 0, 0, 0);
    sub_1989D0("GameWeapons+DeathAnims+PPSH_Hit", 2, (RwInt32)sub_195C10, 0, (RwInt32)dword_4C1970);
    sub_1989D0("GameWeapons+DeathAnims+Stand_Death_A", 2, (RwInt32)sub_195C10, 0, (RwInt32)&dword_4C1980[0]);
    sub_1989D0("GameWeapons+DeathAnims+Stand_Death_B", 2, (RwInt32)sub_195C10, 0, (RwInt32)&dword_4C1980[1]);
    sub_1989D0("GameWeapons+DeathAnims+Crouch_Death", 2, (RwInt32)sub_195C10, 0, (RwInt32)&dword_4C1980[2]);
    sub_1989D0("GameWeapons+DeathAnims+Prone_Death", 2, (RwInt32)sub_195C10, 0, (RwInt32)&dword_4C1980[3]);
    sub_1989D0("GameWeapons+DeathAnims+Bipod_Death", 2, (RwInt32)sub_195C10, 0, (RwInt32)&dword_4C1980[4]);
    sub_1989D0("GameWeapons+DeathAnims+Stand_Freeze_A", 2, (RwInt32)sub_195C10, 0, (RwInt32)&dword_4C1980[5]);
    sub_1989D0("GameWeapons+DeathAnims+Stand_Freeze_B", 2, (RwInt32)sub_195C10, 0, (RwInt32)&dword_4C1980[6]);
    sub_1989D0("GameWeapons+DeathAnims+Crouch_Freeze", 2, (RwInt32)sub_195C10, 0, (RwInt32)&dword_4C1980[7]);
    sub_1989D0("GameWeapons+DeathAnims+Prone_Freeze", 2, (RwInt32)sub_195C10, 0, (RwInt32)&dword_4C1980[8]);
    sub_1989D0("GameWeapons+DeathAnims+Bipod_Freeze", 2, (RwInt32)sub_195C10, 0, (RwInt32)&dword_4C1980[9]);
    dword_4B67E4 = 1;
}

// match: ??_EPlayerTrigger@@WBI@AEPAXI@Z @ 0x000AD1A0
