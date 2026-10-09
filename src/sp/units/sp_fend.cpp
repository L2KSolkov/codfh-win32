/*
 * Single player's front end (SP 0xAD730-0xB19AB; include/sp/sp_fend.h): the language screen
 * (sp_fendlang.cpp), the screens' base (type_sp_AD970, sp_fendbase.cpp) and here the main menu
 * (SP 0xAE5D0-0xB19AB), all played from Rt2d maestro files ("shell\fend\fend.csv" holds their
 * texts). Not in the multiplayer image (its front end is kujuUI's, game/kujuui.h): single
 * player only, never compiled for multiplayer.
 *
 * Three files: each heads its .rdata with an unreferenced 16.666666f (SP 0x2E40F8, 0x2E414C
 * and this one's 0x2E43B0, after the cheats' strings and before "$MCEmptySlot").
 *
 * Evidence: the code sits between unit_0DC400's single-player code and the movie player
 * (unit_0E8800, SP 0xB19B0); its strings (the maestros' labels "languageSelected",
 * "btnUp"..."btnSelect", "url..." and "sound..." names, "shell\fend\fend.csv", the
 * "/mcAct1/mc1_1a/" movie clips) exist only in default.xbe; the shell (SP 0xA55F0-0xA5CF6)
 * creates the screens (the base's constructor SP 0xAD970 and its vtable SP 0x2E4150, the
 * screens' vtables SP 0x2E37E8-0x2E37F0) and calls them.
 */
#include <string.h>
#include <stdio.h>

#include "rw/ostypes.h"
#include "rw/baengine.h"
#include "rw/bastream.h"
#include "rw/babintex.h"
#include "rw/batextur.h"
#include "rw/badevice.h"
#include "rw/rt2d.h"
#include "game/data.h"
#include "game/gameloop.h"
#include "game/xboxlive.h"
#include "game/lightscales.h"
#include "game/frontend.h"
#include "game/platform.h"
#include "types/type_DA580.h"
#include "types/type_8A980.h"
#include "types/type_3DF8D8.h"
#include "game/movie.h"
#include "game/savestate.h"
#include "game/waitscreen.h"
#include "game/levels.h"
#include "game/profiles.h"
#include "game/functions.h"
#include "types/type_4B8EF0.h"
#include "xbox/xapi.h"
#include "sp/sp_fend.h"

// Its data definitions (PLAN SP5): single player's own .bss, in the image's address order (its
// .data and .rdata are defined further down, where the image's order puts them).
// SP 0x003B4718
RwInt32 sp_dword_3B4718;                // the pad pressed a button this step
// SP 0x003B481C
type_DA580 *sp_dword_3B481C;            // the front end's font
// SP 0x003B4822
bool sp_byte_3B4822;
// SP 0x003B4828
RwReal sp_flt_3B4828[0x28];             // the first pad's buttons last step
// SP 0x003B48C8
type_4F45F8 sp_unk_3B48C8;              // the launch data for the multiplayer image
// SP 0x003B54C8
RwInt32 sp_dword_3B54C8;                // the profile slots are being watched
// SP 0x003EC3E4
type_44C4E8 *sp_dword_3EC3E4;           // the extras' music (also the front end's, unit_0DA290)
// SP 0x002E43B0
extern const RwReal sp_flt_2E43B0 = 16.666666f; // unreferenced, just before its first string
// End of its data definitions.

// The screens' base's .data the main menu reads (sp_fendbase.cpp).
extern RwChar sp_byte_321794[];
extern type_3DF8D8_04 sp_unk_3217C8;
extern type_3DF8D8_04 sp_unk_3217D0;
extern type_3DF8D8_04 sp_unk_3217D8;
extern type_3DF8D8_04 sp_unk_3217E0;
extern type_3DF8D8_04 sp_unk_3217E8;
extern type_3DF8D8_04 sp_unk_3217F0;
extern type_3DF8D8_04 sp_unk_3217F8;
extern type_3DF8D8_04 sp_unk_321800;
extern type_3DF8D8_04 sp_unk_321808;
extern type_3DF8D8_04 sp_unk_321810;
extern type_3DF8D8_04 sp_unk_321818;
extern type_3DF8D8_04 sp_unk_321820;
extern type_3DF8D8_04 sp_unk_321828;
extern type_3DF8D8_04 sp_unk_321830;
extern type_3DF8D8_04 sp_unk_321838;
extern type_3DF8D8_04 sp_unk_321840;
extern type_3DF8D8_04 sp_unk_321848;
extern type_3DF8D8_04 sp_unk_321850;
extern type_3DF8D8_04 sp_unk_321858;
extern type_3DF8D8_04 sp_unk_321860;
extern type_3DF8D8_04 sp_unk_321868;
extern type_3DF8D8_04 sp_unk_321870;
extern type_3DF8D8_04 sp_unk_321878;
extern type_3DF8D8_04 sp_unk_321880;
extern type_3DF8D8_04 sp_unk_321888;
extern type_3DF8D8_04 sp_unk_321890;
extern type_3DF8D8_04 sp_unk_321898;
extern type_3DF8D8_04 sp_unk_3218B0;
extern type_3DF8D8_04 sp_unk_3218B8;
extern type_3DF8D8_04 sp_unk_3218C0;
extern type_3DF8D8_04 sp_unk_3218C8;
extern type_3DF8D8_04 sp_unk_3218D0;
extern type_3DF8D8_04 sp_unk_3218D8;
extern type_3DF8D8_04 sp_unk_3218E0;
extern type_3DF8D8_04 sp_unk_3218E8;
extern type_3DF8D8_04 sp_unk_3218F0;

// The front end loop's (unit_0DA290).
extern bool sp_byte_3B4820;
extern bool sp_byte_3B4821;
extern bool sp_byte_3B4720;             // the menu is busy (a page is being shown)
extern RwInt32 sp_dword_3B4744;
extern RwTexDictionary *sp_dword_3B475C;
// The language screen's scroll and select sounds (unit_0DC400's .data, SP 0x3216A4, 0x3216AC).
extern type_3DF8D8_04 unk_4B8B48;
extern type_3DF8D8_04 unk_4B8B40;

void sub_19B0C0(RwInt32 arg_0);
void sub_D7F20(RwChar *arg_0, const RwChar *arg_4);
RwTexDictionary *sub_E8320(const RwChar *arg_0);
void sp_sub_129B50();
void sp_sub_1291D0(RwInt32 arg_0);
void sp_sub_129AC0(RwInt32 arg_0);
RwChar *sp_sub_121960();
void sp_sub_A4F60();
RwInt32 sp_sub_A55F0(RwCamera *arg_0, RwInt32 arg_4, type_D9CF0 *arg_8, RwInt32 arg_C);
void sp_sub_A5E60();
void sp_sub_A5EA0(RwTexDictionary *arg_0);
void sp_sub_A5EC0(RwCamera *arg_0);
void sp_sub_A5F50();
void sp_sub_A5F80();
void sp_sub_A5F90();
void sp_sub_A5FB0();
void sp_sub_A6000();
void sp_sub_A6050(RwReal arg_0);
void sp_sub_A6100();
void sp_sub_B1A10();
type_186020 sp_sub_11B890(RwCamera *arg_0, void (*arg_4)(RwCamera *, void *), void *arg_8);
type_186020 sp_sub_11B900(RwCamera *arg_0, type_D9CF0 *arg_4, RwInt32 arg_8,
                          void (*arg_C)(RwCamera *, void *), void *arg_10);
type_186020 sp_sub_11B930(RwCamera *arg_0, type_D9CF0 *arg_4, void (*arg_8)(RwCamera *, void *),
                          void *arg_C);
type_186020 sp_sub_11B9A0(RwCamera *arg_0, type_D9CF0 *arg_4, RwInt32 arg_8,
                          void (*arg_C)(RwCamera *, void *), void *arg_10);
type_186020 sp_sub_11BAE0(RwCamera *arg_0, type_D9CF0 *arg_4, RwInt32 arg_8,
                          void (*arg_C)(RwCamera *, void *), void *arg_10);

// The main menu.

// Sets it up. The labels (urlQuit on, up to the profile slots' texts) are -1'd in a loop
// the compiler makes a rep stosd of (edi before ecx, SP 0xAE5EC; memset sets ecx first).
// sp-match: ?sp_sub_AE5D0@type_sp_AE5D0@@QAEXPAURwCamera@@@Z @ 0x000AE5D0
void type_sp_AE5D0::sp_sub_AE5D0(RwCamera *arg_0)
{
    sp_sub_AD990(arg_0);
    unk_178 = arg_0;
    for (RwInt32 i = 0; i < 0x8E; i++)
    {
        (&unk_3D8)[i] = -1;
    }
    unk_3C4[0] = -1;
    unk_3C4[1] = -1;
    unk_3C4[2] = -1;
    unk_3C4[3] = -1;
    unk_3C4[4] = -1;
    unk_1DC = 0;
    unk_1E0 = 0;
    unk_1E4 = 1;
    unk_1E8 = false;
    unk_3C0 = 0;
    memset(unk_610, 0, sizeof(unk_610));
    memset(unk_1EC, 0, sizeof(unk_1EC));
    memset(unk_39C, 0, sizeof(unk_39C));
    memset(unk_720, 0, sizeof(unk_720));
    strcpy(unk_7C0, "$MCEmptySlot");
    unk_7CE = false;
    unk_7CF = true;
    unk_7D0 = false;
    unk_7D1 = false;
    unk_7DC = -1;
    sp_sub_A5E60();
}

// sp-match: ?sp_sub_AE6F0@type_sp_AE5D0@@QAE_NXZ @ 0x000AE6F0
// Shows the memory unit's profiles' names in the four slots; whether there is one.
bool type_sp_AE5D0::sp_sub_AE6F0()
{
    RwInt32 count[4];
    RwChar names[4][12];
    bool r;
    RwInt32 i;

    memset(names, 0, sizeof(names));
    unk_4B8744.sub_D9D60(count, names);
    r = false;
    for (i = 0; i < 4; i++)
    {
        if (names[i][0])
        {
            r = true;
            Rt2dObjectStringSetText(unk_610[i][0], names[i]);
            Rt2dObjectStringSetText(unk_610[i][1], names[i]);
        }
        else
        {
            Rt2dObjectStringSetText(unk_610[i][0], unk_7C0);
            Rt2dObjectStringSetText(unk_610[i][1], unk_7C0);
        }
    }
    return r;
}

// sp-match: ?sp_sub_AE7A0@type_sp_AE5D0@@QAEXPAURwCamera@@@Z @ 0x000AE7A0
void type_sp_AE5D0::sp_sub_AE7A0(RwCamera *arg_0)
{
    if (unk_7DC == 1)
    {
        sp_sub_A5EC0(arg_0);
    }
    sp_sub_ADB50(arg_0);
}

// sp-match: ?sp_sub_AE7D0@type_sp_AD970@@QAEXXZ @ 0x000AE7D0
void type_sp_AD970::sp_sub_AE7D0()
{
    sp_sub_ADA70();
}

// sp-match: ?sp_sub_AE7E0@type_sp_AE5D0@@QAE_NPBD00@Z @ 0x000AE7E0
bool type_sp_AE5D0::sp_sub_AE7E0(const RwChar *arg_0, const RwChar *arg_4, const RwChar *arg_8)
{
    if (sp_sub_AE3C0(arg_0, arg_4, arg_8))
    {
        return true;
    }
    return false;
}

// sp-match: ?sp_sub_AE800@type_sp_AE5D0@@QAE_NPBUtype_sp_AE5D0_cb@@@Z @ 0x000AE800
// Adds the step callback arg_0 (false when it is there already or there is no room).
bool type_sp_AE5D0::sp_sub_AE800(const type_sp_AE5D0_cb *arg_0)
{
    RwUInt32 i;

    for (i = 0; i < 10; i++)
    {
        if (unk_720[i].unk_00 == (type_sp_AE5D0_fn)arg_0)
        {
            return false;
        }
    }
    for (i = 0; i < 10; i++)
    {
        if (!unk_720[i].unk_00)
        {
            unk_720[i] = *arg_0;
            return true;
        }
    }
    return false;
}

// sp-match: ?sp_sub_AE860@type_sp_AE5D0@@QAEXXZ @ 0x000AE860
void type_sp_AE5D0::sp_sub_AE860()
{
    RwInt32 i;
    type_sp_AE5D0_cb *c;

    for (i = 0; i < 10; i++)
    {
        c = &unk_720[i];
        if (c->unk_00)
        {
            if (c->unk_08)
            {
                c->unk_08--;
            }
            else if (c->unk_0C && c->unk_00(this, c->unk_04))
            {
                if (c->unk_0C != -1)
                {
                    c->unk_0C--;
                }
            }
            else
            {
                c->unk_00 = 0;
            }
        }
    }
}

// sp-match: ?sp_sub_AE8C0@type_sp_AE5D0@@QAEXXZ @ 0x000AE8C0
// Selects the furthest level reached in the level select.
void type_sp_AE5D0::sp_sub_AE8C0()
{
    RwUInt32 act;
    RwUInt32 level;
    RwInt32 data[2];

    unk_1DC = 0;
    unk_1E0 = 0;
    for (act = 0; act < 3; act++)
    {
        for (level = 0; level < 8; level++)
        {
            if (!unk_1EC[act][level].unk_00.unk_00)
            {
                break;
            }
            if (unk_1EC[act][level].unk_0C == unk_1E4)
            {
                unk_1E0 = level;
                unk_1DC = act;
                data[1] = 0x40;
                data[0] = unk_3C4[unk_1DC + 1];
                Rt2dMaestroForAllVisibleAnimations(unk_17C, sp_sub_ADDF0, data);
                return;
            }
        }
    }
}

// sp-match: ?sp_sub_AE960@@YA_NPAUtype_sp_AE5D0@@PAX@Z @ 0x000AE960
bool sp_sub_AE960(type_sp_AE5D0 *arg_0, void *arg_4)
{
    sp_byte_3B4720 = false;
    return false;
}

// sp-match: ?sp_sub_AE970@@YAXPAURwCamera@@PAX@Z @ 0x000AE970
// The memory unit flows' draw callback: the main menu arg_4 on the camera arg_0.
void sp_sub_AE970(RwCamera *arg_0, void *arg_4)
{
    ((type_sp_AE5D0 *)arg_4)->sp_sub_AE7A0(arg_0);
}

// sp-match: ?sp_sub_AE980@type_sp_AE5D0@@QAEXXZ @ 0x000AE980
void type_sp_AE5D0::sp_sub_AE980()
{
    sp_dword_3B54C8 = 1;
    unk_7D1 = true;
}

// sp-match: ?sp_sub_AE9A0@type_sp_AE5D0@@QAEXXZ @ 0x000AE9A0
void type_sp_AE5D0::sp_sub_AE9A0()
{
    sp_dword_3B54C8 = 0;
    unk_7D1 = false;
}

// sp-match: ?sp_sub_AE9B0@@YAXXZ @ 0x000AE9B0
// Stops the extras' music.
void sp_sub_AE9B0()
{
    RwInt32 i;

    if (sp_dword_3EC3E4)
    {
        SoundEmitter_Stop(sp_dword_3EC3E4, 0);
        sp_dword_3EC3E4 = 0;
        for (i = 0; i < 4; i++)
        {
            RwaCoreUpdate();
        }
    }
}

// sp-match: ?sp_sub_AE9E0@@YAXPAURwCamera@@H@Z @ 0x000AE9E0
// Starts the multiplayer image ("urlMultiplayer"): hands it the settings, the profiles and the
// Xbox Live logon state (arg_4 1: join the friend, 2: leave quietly).
void sp_sub_AE9E0(RwCamera *arg_0, RwInt32 arg_4)
{
    sp_sub_A4F60();
    sub_19CDE0(sp_byte_321794);
    memset(&sp_unk_3B48C8, 0, sizeof(sp_unk_3B48C8));
    sp_unk_3B48C8.unk_00 = 0;
    if (arg_4 == 1)
    {
        sp_unk_3B48C8.unk_38 = 1;
    }
    else if (arg_4 == 2)
    {
        sp_unk_3B48C8.unk_3C = 1;
    }
    sp_unk_3B48C8.unk_24 = dword_4B9E50;
    *(RwInt32 *)&sp_unk_3B48C8.unk_04[4] = dword_4F30BC;
    sp_unk_3B48C8.unk_28 = sub_19B0A0();
    sp_unk_3B48C8.unk_2C = dword_4F28F0->unk_22;
    sp_unk_3B48C8.unk_30 = dword_4F28F0->unk_1C;
    sp_unk_3B48C8.unk_34 = dword_4F28F0->unk_18;
    memcpy(sp_unk_3B48C8.unk_434, dword_4F45F8->unk_434, sizeof(sp_unk_3B48C8.unk_434));
    memcpy(sp_unk_3B48C8.unk_398, dword_4F45F8->unk_398, sizeof(sp_unk_3B48C8.unk_398));
    if (dword_4F3130.sub_19C500() && !dword_4F3130.unk_24
        && XOnlineSaveLogonState((PXONLINE_LOGON_STATE)sp_unk_3B48C8.unk_48A) == 0)
    {
        sp_unk_3B48C8.unk_40 = 1;
    }
    else
    {
        sp_unk_3B48C8.unk_40 = 0;
    }
    sp_unk_3B48C8.unk_14 = dword_4F28F0->unk_44;
    sp_unk_3B48C8.unk_394 = dword_4F5A30;
    sub_19BAC0(arg_0);
    sub_EA560(arg_0);
    sub_19BE30((type_19BE30 *)&sp_unk_3B48C8);
    sub_1A2650(&sp_unk_3B48C8);
    D3DDevice_PersistDisplay();
    XLaunchNewImage(sp_byte_321794, (PLAUNCH_DATA)&sp_unk_3B48C8);
}

// sp-match: ?sp_sub_AEB20@type_sp_AE5D0@@QAE_NH@Z @ 0x000AEB20
// The galleries' slideshow buttons.
bool type_sp_AE5D0::sp_sub_AEB20(RwInt32 arg_0)
{
    bool r = true;

    if (arg_0 == unk_5DC)
    {
        sp_sub_A5F80();
    }
    else if (arg_0 == unk_5E0)
    {
        sp_sub_A5F90();
    }
    else if (arg_0 == unk_5E4)
    {
        sp_sub_A5FB0();
    }
    else if (arg_0 == unk_5E8)
    {
        sp_sub_A6000();
    }
    else
    {
        r = false;
    }
    return r;
}

// sp-match: ?sp_sub_AEB80@type_sp_AE5D0@@QAEXXZ @ 0x000AEB80
void type_sp_AE5D0::sp_sub_AEB80()
{
    sp_sub_ADE30("urlQuit", &unk_3D8, 6);
    sp_sub_ADE30("enteringProfileSelect", &unk_494, 6);
    sp_sub_ADE30("enableMemCardMonitoring", &unk_498, 6);
    sp_sub_ADE30("selectProfile", &unk_49C, 6);
    sp_sub_ADE30("createNewProfile", &unk_4A0, 6);
    sp_sub_ADE30("leavingSelectProfile", &unk_4A4, 6);
    sp_sub_ADE30("urlLevelMamaevKurgen", &unk_4A8, 6);
    sp_sub_ADE30("urlLevel1_1B", &unk_4AC, 6);
    sp_sub_ADE30("urlLevelTractorFactory", &unk_4B0, 6);
    sp_sub_ADE30("urlLevel1_2B", &unk_4B4, 6);
    sp_sub_ADE30("urlLevelTrainStation", &unk_4B8, 6);
    sp_sub_ADE30("urlLevel1_3B", &unk_4BC, 6);
    sp_sub_ADE30("urlLevelPitomnik", &unk_4C0, 6);
    sp_sub_ADE30("urlLevelTatsinskaya", &unk_4C4, 6);
    sp_sub_ADE30("urlLevel1_5B", &unk_4C8, 6);
    sp_sub_ADE30("urlLevelMatmata", &unk_4CC, 6);
    sp_sub_ADE30("urlLevel2_1B", &unk_4D0, 6);
    sp_sub_ADE30("urlLevelKsarTarsine", &unk_4D4, 6);
    sp_sub_ADE30("urlLevel2_2B", &unk_4D8, 6);
    sp_sub_ADE30("urlLevelAachen", &unk_4DC, 6);
    sp_sub_ADE30("urlLevel3_1B", &unk_4E0, 6);
    sp_sub_ADE30("urlLevel3_1C", &unk_4E4, 6);
    sp_sub_ADE30("urlLevelStavelot", &unk_4E8, 6);
    sp_sub_ADE30("urlLevel3_2B", &unk_4EC, 6);
    sp_sub_ADE30("urlLevelTillet1", &unk_4F0, 6);
    sp_sub_ADE30("urlLevel3_3B", &unk_4F4, 6);
    sp_sub_ADE30("urlLevelTillet2", &unk_4F8, 6);
    sp_sub_ADE30("urlLevel3_4B", &unk_4FC, 6);
    sp_sub_ADE30("urlLevelRemagen", &unk_500, 6);
    sp_sub_ADE30("urlLevel3_5B", &unk_504, 6);
    sp_sub_ADE30("urlLevel3_5C", &unk_508, 6);
    sp_sub_ADE30("playAct1Movie", &unk_50C, 6);
    sp_sub_ADE30("playAct2Movie", &unk_510, 6);
    sp_sub_ADE30("playAct3Movie", &unk_514, 6);
    sp_sub_ADE30("urlPlayMakingOf1", &unk_518, 6);
    sp_sub_ADE30("urlPlayMakingOf2", &unk_51C, 6);
    sp_sub_ADE30("urlPlayMakingOf3", &unk_520, 6);
    sp_sub_ADE30("movieCredits", &unk_524, 6);
    sp_sub_ADE30("movieAnimReel", &unk_528, 6);
    sp_sub_ADE30("movieTeaser", &unk_52C, 6);
    sp_sub_ADE30("urlResetOptions", &unk_554, 6);
    sp_sub_ADE30("urlSaveOptions", &unk_550, 6);
    sp_sub_ADE30("urlRefresh", &unk_54C, 6);
    sp_sub_ADE30("enteringControllerConfig", &unk_558, 6);
    sp_sub_ADE30("setControllerConfig", &unk_55C, 6);
    sp_sub_ADE30("setOutgoingCC", &unk_560, 6);
    sp_sub_ADE30("shakeIt", &unk_564, 6);
    sp_sub_ADE30("profileOptionsSave", &unk_568, 6);
    sp_sub_ADE30("profileOptionsLoad", &unk_56C, 6);
    sp_sub_ADE30("profileOptionsCreateNew", &unk_570, 6);
    sp_sub_ADE30("urlEnterCheatsScreen", &unk_574, 6);
    sp_sub_ADE30("urlExitCheatsScreen", &unk_578, 6);
    sp_sub_ADE30("urlCheckButtonSequence", &unk_57C, 6);
    sp_sub_ADE30("urlBigHeadsOn", &unk_584, 6);
    sp_sub_ADE30("urlBigHeadsOff", &unk_580, 6);
    sp_sub_ADE30("urlRicochetPlayerOn", &unk_58C, 6);
    sp_sub_ADE30("urlRicochetPlayerOff", &unk_588, 6);
    sp_sub_ADE30("urlHeadShotKillsOn", &unk_594, 6);
    sp_sub_ADE30("urlHeadShotKillsOff", &unk_590, 6);
    sp_sub_ADE30("urlRicochetAllOn", &unk_59C, 6);
    sp_sub_ADE30("urlRicochetAllOff", &unk_598, 6);
    sp_sub_ADE30("urlShrinkingSoldiersOn", &unk_5A4, 6);
    sp_sub_ADE30("urlShrinkingSoldiersOff", &unk_5A0, 6);
    sp_sub_ADE30("urlOneShotKillsOn", &unk_5AC, 6);
    sp_sub_ADE30("urlOneShotKillsOff", &unk_5A8, 6);
    sp_sub_ADE30("urlBigNSmallOn", &unk_5B4, 6);
    sp_sub_ADE30("urlBigNSmallOff", &unk_5B0, 6);
    sp_sub_ADE30("urlPersonalScreensEnter", &unk_5B8, 6);
    sp_sub_ADE30("urlGalleryEnter", &unk_5BC, 6);
    sp_sub_ADE30("urlSelectedAnimation", &unk_5C0, 6);
    sp_sub_ADE30("urlSelectedArtwork", &unk_5C4, 6);
    sp_sub_ADE30("urlSelectedMaking1", &unk_5C8, 6);
    sp_sub_ADE30("urlSelectedMaking2", &unk_5CC, 6);
    sp_sub_ADE30("urlSelectedMaking3", &unk_5D0, 6);
    sp_sub_ADE30("urlArtGalleryEnter", &unk_5D4, 6);
    sp_sub_ADE30("urlSlideshowLeave", &unk_5D8, 6);
    sp_sub_ADE30("urlSlideshowPlay", &unk_5DC, 6);
    sp_sub_ADE30("urlSlideshowPause", &unk_5E0, 6);
    sp_sub_ADE30("urlSlideshowPrev", &unk_5E4, 6);
    sp_sub_ADE30("urlSlideshowNext", &unk_5E8, 6);
    sp_sub_ADE30("urlDisableRender", &unk_5EC, 6);
    sp_sub_ADE30("enteringLevelSelect", &unk_5F0, 6);
    sp_sub_ADE30("updateLevelStates", &unk_5F4, 6);
    sp_sub_ADE30("selectNextAct", &unk_5FC, 6);
    sp_sub_ADE30("selectPreviousAct", &unk_5F8, 6);
    sp_sub_ADE30("selectNextLevel", &unk_604, 6);
    sp_sub_ADE30("selectPreviousLevel", &unk_600, 6);
    sp_sub_ADE30("checkUnlockSPLvlsMBS", &unk_608, 6);
    sp_sub_ADE30("btnDownAction", &unk_3C4[0], 3);
    sp_sub_ADE30("btnGotoAct1", &unk_3C4[1], 3);
    sp_sub_ADE30("btnGotoAct2", &unk_3C4[2], 3);
    sp_sub_ADE30("btnGotoAct3", &unk_3C4[3], 3);
    sp_sub_ADE30("vBtnJumpToMain", &unk_3C4[4], 3);
    sp_sub_ADE30("urlMultiplayer", &unk_60C, 6);
    sp_sub_ADE30("enableBG", &unk_3DC, 6);
    sp_sub_ADE30("disableBG", &unk_3E0, 6);
    sp_sub_ADE30("enableDemo", &unk_3E4, 6);
    sp_sub_ADE30("disableDemo", &unk_3E8, 6);
    sp_sub_ADE30("soundPressStart", &unk_408, 6);
    sp_sub_ADE30("soundPSScroll", &unk_40C, 6);
    sp_sub_ADE30("soundPSSelect", &unk_410, 6);
    sp_sub_ADE30("soundPSNew", &unk_414, 6);
    sp_sub_ADE30("soundMSScroll", &unk_418, 6);
    sp_sub_ADE30("soundMSSelect", &unk_41C, 6);
    sp_sub_ADE30("soundCGScroll", &unk_420, 6);
    sp_sub_ADE30("soundCGScrollAcross", &unk_424, 6);
    sp_sub_ADE30("soundCGSelect", &unk_428, 6);
    sp_sub_ADE30("soundCGBack", &unk_42C, 6);
    sp_sub_ADE30("soundOSScrollDown", &unk_430, 6);
    sp_sub_ADE30("soundOSScrollAcross", &unk_434, 6);
    sp_sub_ADE30("soundOSSelect", &unk_438, 6);
    sp_sub_ADE30("soundOSBack", &unk_43C, 6);
    sp_sub_ADE30("soundCCScroll", &unk_440, 6);
    sp_sub_ADE30("soundCCSelect", &unk_444, 6);
    sp_sub_ADE30("soundCCBack", &unk_448, 6);
    sp_sub_ADE30("soundCSBack", &unk_44C, 6);
    sp_sub_ADE30("soundEXScroll", &unk_450, 6);
    sp_sub_ADE30("soundEXSelect", &unk_454, 6);
    sp_sub_ADE30("soundEXBack", &unk_458, 6);
    sp_sub_ADE30("soundDOScroll", &unk_45C, 6);
    sp_sub_ADE30("soundDOSelect", &unk_460, 6);
    sp_sub_ADE30("soundDOBack", &unk_464, 6);
    sp_sub_ADE30("soundUNScroll", &unk_468, 6);
    sp_sub_ADE30("soundUNSelect", &unk_46C, 6);
    sp_sub_ADE30("soundUNBack", &unk_470, 6);
    sp_sub_ADE30("soundGAScroll", &unk_474, 6);
    sp_sub_ADE30("soundGABack", &unk_47C, 6);
    sp_sub_ADE30("soundGASelect", &unk_478, 6);
    sp_sub_ADE30("soundCHScroll", &unk_480, 6);
    sp_sub_ADE30("soundCHSelect", &unk_484, 6);
    sp_sub_ADE30("soundLPScroll", &unk_488, 6);
    sp_sub_ADE30("soundLPSelect", &unk_48C, 6);
    sp_sub_ADE30("soundLPBack", &unk_490, 6);
    sp_sub_ADE30("streamProfileSelect", &unk_3EC, 6);
    sp_sub_ADE30("streamContinueGame", &unk_3F0, 6);
    sp_sub_ADE30("streamOptions", &unk_3F4, 6);
    sp_sub_ADE30("streamExtras", &unk_3F8, 6);
    sp_sub_ADE30("streamUnlockables", &unk_3FC, 6);
    sp_sub_ADE30("streamCheats", &unk_400, 6);
    sp_sub_ADE30("streamMusic", &unk_404, 6);
}

// sp-match: ?sp_sub_AF700@type_sp_AE5D0@@QAEHPBD@Z @ 0x000AF700
// The frame the clip arg_0 shows.
RwInt32 type_sp_AE5D0::sp_sub_AF700(const RwChar *arg_0)
{
    type_sp_ADF20 a;

    a = sp_sub_ADF20(arg_0);
    return Rt2dAnimGetPrevFrameIndex(a.unk_00);
}

// sp-match: ?sp_sub_AF730@type_sp_AE5D0@@QAEXPBDH@Z @ 0x000AF730
// Shows the frame arg_4 of the clip arg_0.
void type_sp_AE5D0::sp_sub_AF730(const RwChar *arg_0, RwInt32 arg_4)
{
    type_sp_ADF20 a;

    a = sp_sub_ADF20(arg_0);
    Rt2dAnimGotoKeyFrameListByIndex(a.unk_00, a.unk_04, arg_4);
}

// sp-match: ?sp_sub_AF760@type_sp_AE5D0@@QAEXH@Z @ 0x000AF760
// Presses the button unk_3C4[arg_0].
void type_sp_AE5D0::sp_sub_AF760(RwInt32 arg_0)
{
    RwInt32 data[2];

    data[0] = unk_3C4[arg_0];
    data[1] = 0x40;
    Rt2dMaestroForAllVisibleAnimations(unk_17C, sp_sub_ADDF0, data);
}

// sp-match: ?sp_sub_AF7A0@type_sp_AE5D0@@QAEXM@Z @ 0x000AF7A0
void type_sp_AE5D0::sp_sub_AF7A0(RwReal arg_0)
{
    sp_sub_B1A10();
    unk_7D4 += arg_0;
    if (unk_610[0][0])
    {
        sp_sub_AE6F0();
    }
    sp_sub_A6050(arg_0);
    sp_sub_AE860();
    sp_sub_AE0D0(1.0f);
}

// sp-match: ?sp_sub_AF7F0@type_sp_AE5D0@@QAEXXZ @ 0x000AF7F0
// Finds the maestro's objects and clips the menu uses.
void type_sp_AE5D0::sp_sub_AF7F0()
{
    type_sp_ADD00 l;
    struct
    {
        const RwChar *unk_00;
        Rt2dObject **unk_04;
    } slots[4];
    struct
    {
        const RwChar *unk_00;
        type_sp_AE5D0_level *unk_04;
        RwInt32 unk_08;
    } levels[19];
    Rt2dObject *objects[0x400];
    RwChar name[0x10];
    RwUInt32 i;
    RwUInt32 j;
    RwUInt32 n;
    const RwChar *t;

    if (sp_sub_121960())
    {
        memset(unk_7C0, 0, sizeof(unk_7C0));
        strncpy(unk_7C0, sp_sub_121960(), 0xD);
        unk_7C0[0xD] = 0;
    }
    l.unk_00 = 0;
    l.unk_04 = 0x400;
    l.unk_08 = objects;
    Rt2dSceneForAllChildren(Rt2dMaestroGetScene(unk_17C), sp_sub_ADD00, &l);
    slots[0].unk_00 = "$slot1";
    slots[0].unk_04 = unk_610[0];
    slots[1].unk_00 = "$slot2";
    slots[1].unk_04 = unk_610[1];
    slots[2].unk_00 = "$slot3";
    slots[2].unk_04 = unk_610[2];
    slots[3].unk_00 = "$slot4";
    slots[3].unk_04 = unk_610[3];
    for (i = 0; i < 4; i++)
    {
        n = 0;
        for (j = 0; j < l.unk_00; j++)
        {
            t = Rt2dObjectStringGetText(objects[j]);
            if (t && !strcmp(t, slots[i].unk_00))
            {
                slots[i].unk_04[n] = objects[j];
                n++;
                if (n == 2)
                {
                    break;
                }
            }
        }
    }
    levels[0].unk_00 = "/mcAct1/mc1_1a/";
    levels[0].unk_04 = &unk_1EC[0][0];
    levels[0].unk_08 = 1;
    levels[1].unk_00 = "/mcAct1/mc1_1b/";
    levels[1].unk_04 = &unk_1EC[0][1];
    levels[1].unk_08 = 2;
    levels[2].unk_00 = "/mcAct1/mc1_2a/";
    levels[2].unk_04 = &unk_1EC[0][2];
    levels[2].unk_08 = 4;
    levels[3].unk_00 = "/mcAct1/mc1_2b/";
    levels[3].unk_04 = &unk_1EC[0][3];
    levels[3].unk_08 = 5;
    levels[4].unk_00 = "/mcAct1/mc1_3a/";
    levels[4].unk_04 = &unk_1EC[0][4];
    levels[4].unk_08 = 7;
    levels[5].unk_00 = "/mcAct1/mc1_3b/";
    levels[5].unk_04 = &unk_1EC[0][5];
    levels[5].unk_08 = 8;
    levels[6].unk_00 = "/mcAct1/mc1_5a/";
    levels[6].unk_04 = &unk_1EC[0][6];
    levels[6].unk_08 = 0xB;
    levels[7].unk_00 = "/mcAct1/mc1_5b/";
    levels[7].unk_04 = &unk_1EC[0][7];
    levels[7].unk_08 = 0xC;
    levels[8].unk_00 = "/mcAct2/mc2_1a/";
    levels[8].unk_04 = &unk_1EC[1][0];
    levels[8].unk_08 = 0xE;
    levels[9].unk_00 = "/mcAct2/mc2_1b/";
    levels[9].unk_04 = &unk_1EC[1][1];
    levels[9].unk_08 = 0xF;
    levels[10].unk_00 = "/mcAct2/mc2_2a/";
    levels[10].unk_04 = &unk_1EC[1][2];
    levels[10].unk_08 = 0x11;
    levels[11].unk_00 = "/mcAct2/mc2_2b/";
    levels[11].unk_04 = &unk_1EC[1][3];
    levels[11].unk_08 = 0x12;
    levels[12].unk_00 = "/mcAct3/mc3_1a/";
    levels[12].unk_04 = &unk_1EC[2][0];
    levels[12].unk_08 = 0x18;
    levels[13].unk_00 = "/mcAct3/mc3_1b/";
    levels[13].unk_04 = &unk_1EC[2][1];
    levels[13].unk_08 = 0x19;
    levels[14].unk_00 = "/mcAct3/mc3_1c/";
    levels[14].unk_04 = &unk_1EC[2][2];
    levels[14].unk_08 = 0x1A;
    levels[15].unk_00 = "/mcAct3/mc3_3a/";
    levels[15].unk_04 = &unk_1EC[2][3];
    levels[15].unk_08 = 0x1E;
    levels[16].unk_00 = "/mcAct3/mc3_5a/";
    levels[16].unk_04 = &unk_1EC[2][4];
    levels[16].unk_08 = 0x24;
    levels[17].unk_00 = "/mcAct3/mc3_5b/";
    levels[17].unk_04 = &unk_1EC[2][5];
    levels[17].unk_08 = 0x25;
    levels[18].unk_00 = "/mcAct3/mc3_5c/";
    levels[18].unk_04 = &unk_1EC[2][6];
    levels[18].unk_08 = 0x26;
    for (i = 0; i < 19; i++)
    {
        levels[i].unk_04->unk_00 = sp_sub_ADF20(levels[i].unk_00);
        levels[i].unk_04->unk_0C = levels[i].unk_08;
    }
    for (i = 0; i < 3; i++)
    {
        sprintf(name, "/mcAct%d/", i + 1);
        unk_39C[i] = sp_sub_ADF20(name);
    }
    sp_sub_AEB80();
    sp_sub_B39F0(objects, l.unk_00, "shell\\fend\\fend.csv");
}

// sp-match: ?sp_sub_AFCA0@type_sp_AE5D0@@QAEXXZ @ 0x000AFCA0
// Back to the main menu (vBtnJumpToMain).
void type_sp_AE5D0::sp_sub_AFCA0()
{
    sub_E88B0(false);
    sp_sub_AF760(4);
}

// sp-match: ?sp_sub_AFCC0@@YA_NPAUtype_sp_AE5D0@@PAX@Z @ 0x000AFCC0
// Shows the act's levels: locked, selected or open.
bool sp_sub_AFCC0(type_sp_AE5D0 *arg_0, void *arg_4)
{
    RwUInt32 i;
    RwUInt32 n;

    for (i = 0; i < 8; i++)
    {
        if (!arg_0->unk_1EC[arg_0->unk_1DC][i].unk_00.unk_00)
        {
            break;
        }
        if (arg_0->unk_1EC[arg_0->unk_1DC][i].unk_0C <= arg_0->unk_1E4)
        {
            if (i == arg_0->unk_1E0)
            {
                Rt2dAnimGotoKeyFrameListByIndex(arg_0->unk_1EC[arg_0->unk_1DC][i].unk_00.unk_00,
                                                arg_0->unk_1EC[arg_0->unk_1DC][i].unk_00.unk_04, 2);
            }
            else
            {
                Rt2dAnimGotoKeyFrameListByIndex(arg_0->unk_1EC[arg_0->unk_1DC][i].unk_00.unk_00,
                                                arg_0->unk_1EC[arg_0->unk_1DC][i].unk_00.unk_04, 0);
            }
        }
        else
        {
            Rt2dAnimGotoKeyFrameListByIndex(arg_0->unk_1EC[arg_0->unk_1DC][i].unk_00.unk_00,
                                            arg_0->unk_1EC[arg_0->unk_1DC][i].unk_00.unk_04, 1);
        }
    }
    arg_0->unk_1E8 = false;
    if (arg_0->unk_1EC[arg_0->unk_1DC][0].unk_0C > arg_0->unk_1E4)
    {
        for (i = 0; i < 8; i++)
        {
            if (!arg_0->unk_1EC[arg_0->unk_1DC][i].unk_00.unk_00)
            {
                break;
            }
        }
        n = i;
    }
    else
    {
        n = arg_0->unk_1E0;
    }
    Rt2dAnimGotoKeyFrameListByIndex(arg_0->unk_39C[arg_0->unk_1DC].unk_00,
                                    arg_0->unk_39C[arg_0->unk_1DC].unk_04, n);
    type_sp_AE5D0_cb c = {sp_sub_AE960, 0, 1, 1};
    arg_0->sp_sub_AE800(&c);
    return false;
}

// sp-match: ?sp_sub_AFDD0@@YA_NPAUtype_sp_AE5D0@@PAX@Z @ 0x000AFDD0
// Shows the options.
bool sp_sub_AFDD0(type_sp_AE5D0 *arg_0, void *arg_4)
{
    arg_0->sp_sub_AF730("/mcDifficulty/", sub_19B080());
    arg_0->sp_sub_AF730("/mcVibration/", dword_4F28F0->unk_20);
    arg_0->sp_sub_AF730("/mcSubtitles/", dword_4F28F0->unk_21);
    arg_0->sp_sub_AF730("/mcTurnLookSpeed/", dword_4F28F0->unk_18);
    arg_0->sp_sub_AF730("/mcInvertYAxis/", dword_4F28F0->unk_22);
    arg_0->sp_sub_AF730("/mcControls/", dword_4F28F0->unk_1C);
    arg_0->sp_sub_AF730("/mcFriendlyFire/", dword_4F28F0->unk_180);
    arg_0->sp_sub_AF730("/mcAimAssist/", dword_4F28F0->unk_181);
    arg_0->sp_sub_AF730("/mcHintMessages/", dword_4F28F0->unk_28);
    sp_byte_3B4720 = true;
    type_sp_AE5D0_cb c = {sp_sub_AE960, 0, 1, 1};
    arg_0->sp_sub_AE800(&c);
    return false;
}

extern "C" void _WriteBarrier();
#pragma intrinsic(_WriteBarrier)

static inline sp_movie_flag_word sp_read_movie_flags(const RwInt32 *p)
{
    sp_movie_flag_word r = {*p};
    return r;
}

// sp-match: ?sp_sub_AFEE0@@YA_NPAUtype_sp_AE5D0@@PAX@Z @ 0x000AFEE0
// Shows the making-of movies unlocked, the one selected (*arg_4) lit.
// shape: the copied selector and flag-word getters preserve the late screen loads.
bool sp_sub_AFEE0(type_sp_AE5D0 *arg_0, void *arg_4)
{
    RwInt32 *flags = &dword_4F28F0->unk_30;
    RwUInt32 selected = *(volatile RwUInt32 *)arg_4;
    sp_movie_selection_encoding context;
    context.words.low = selected;
    context.words.high = selected;
    RwInt32 f1 = *(volatile RwInt32 *)flags;
    switch (context.raw)
    {
    case 0x100000001ui64:
        if (f1 & 0x1000)
        {
            arg_0->sp_sub_AF730("/mcMakingOf1/", 2);
            goto unselected2;
        }
    default:
        if (f1 & 0x1000)
        {
            arg_0->sp_sub_AF730("/mcMakingOf1/", 1);
        }
    }
    if (context.words.high == 2)
    {
        if ((*flags) & 0x2000)
        {
            arg_0->sp_sub_AF730("/mcMakingOf2/", 2);
            goto unselected3;
        }
        goto selected3;
    }
unselected2:
    if ((sp_read_movie_flags(flags).bits) & 0x2000)
    {
        arg_0->sp_sub_AF730("/mcMakingOf2/", 1);
    }
selected3:
    _WriteBarrier();
    if (context.words.high == 3)
    {
        if ((sp_read_movie_flags(flags).bits) & 0x4000)
        {
            arg_0->sp_sub_AF730("/mcMakingOf3/", 2);
        }
        goto done;
    }
unselected3:
    if ((sp_read_movie_flags(flags).bits) & 0x4000)
    {
        arg_0->sp_sub_AF730("/mcMakingOf3/", 1);
    }
done:;
    type_sp_AE5D0_cb c = {sp_sub_AE960, 0, 1, 1};
    arg_0->sp_sub_AE800(&c);
    return false;
}

// sp-match: ?sp_sub_AFFC0@@YA_NPAUtype_sp_AE5D0@@PAX@Z @ 0x000AFFC0
// Shows the cheats unlocked and switched on.
bool sp_sub_AFFC0(type_sp_AE5D0 *arg_0, void *arg_4)
{
    RwUInt32 *f;

    f = (RwUInt32 *)&dword_4F28F0->unk_30;
    arg_0->sp_sub_AF730("/mcCheat1/", *f & 1);
    arg_0->sp_sub_AF730("/mcCheat2/", (*f >> 1) & 1);
    arg_0->sp_sub_AF730("/mcCheat3/", (*f >> 2) & 1);
    arg_0->sp_sub_AF730("/mcCheat4/", (*f >> 3) & 1);
    arg_0->sp_sub_AF730("/mcCheat5/", (*f >> 4) & 1);
    arg_0->sp_sub_AF730("/mcCheat6/", (*f >> 5) & 1);
    arg_0->sp_sub_AF730("/mcCheat7/", (*f >> 6) & 1);
    f = (RwUInt32 *)&dword_4F28F0->unk_2C;
    arg_0->sp_sub_AF730("/mcCheat1/mcCheat1Toggle/", *f & 1);
    arg_0->sp_sub_AF730("/mcCheat2/mcCheat2Toggle/", (*f >> 1) & 1);
    arg_0->sp_sub_AF730("/mcCheat3/mcCheat3Toggle/", (*f >> 2) & 1);
    arg_0->sp_sub_AF730("/mcCheat4/mcCheat4Toggle/", (*f >> 3) & 1);
    arg_0->sp_sub_AF730("/mcCheat5/mcCheat5Toggle/", (*f >> 4) & 1);
    arg_0->sp_sub_AF730("/mcCheat6/mcCheat6Toggle/", (*f >> 5) & 1);
    arg_0->sp_sub_AF730("/mcCheat7/mcCheat7Toggle/", (*f >> 6) & 1);
    type_sp_AE5D0_cb c = {sp_sub_AE960, 0, 1, 1};
    arg_0->sp_sub_AE800(&c);
    return false;
}

// sp-match: ?sp_sub_B0130@type_sp_AE5D0@@QAEXXZ @ 0x000B0130
// Takes the options from the maestro.
void type_sp_AE5D0::sp_sub_B0130()
{
    bool on;

    sp_sub_1291D0(sp_sub_AF700("/mcDifficulty/"));
    on = sp_sub_AF700("/mcVibration/") != 0;
    dword_4F28F0->unk_20 = on;
    on = sp_sub_AF700("/mcSubtitles/") != 0;
    dword_4F28F0->unk_21 = on;
    dword_4F28F0->unk_18 = sp_sub_AF700("/mcTurnLookSpeed/");
    on = sp_sub_AF700("/mcInvertYAxis/") != 0;
    dword_4F28F0->unk_22 = on;
    dword_4F28F0->unk_1C = sp_sub_AF700("/mcControls/");
    on = sp_sub_AF700("/mcFriendlyFire/") != 0;
    dword_4F28F0->unk_180 = on;
    on = sp_sub_AF700("/mcAimAssist/") != 0;
    dword_4F28F0->unk_181 = on;
    on = sp_sub_AF700("/mcHintMessages/") != 0;
    dword_4F28F0->unk_28 = on;
}

// sp-match: ?sp_sub_B0220@type_sp_AE5D0@@QAEXXZ @ 0x000B0220
void type_sp_AE5D0::sp_sub_B0220()
{
    type_sp_AE5D0_cb c = {sp_sub_AFDD0, 0, 2, 1};
    sp_sub_AE800(&c);
}

// sp-match: ?sp_sub_B0250@type_sp_AE5D0@@QAE_NH@Z @ 0x000B0250
// The options' buttons.
bool type_sp_AE5D0::sp_sub_B0250(RwInt32 arg_0)
{
    bool r = true;

    if (arg_0 == unk_550)
    {
        sp_sub_B0130();
    }
    else if (arg_0 == unk_554)
    {
        sp_sub_1291D0(1);
        dword_4F28F0->unk_20 = 1;
        dword_4F28F0->unk_21 = 1;
        dword_4F28F0->unk_14 = 1;
        dword_4F28F0->unk_18 = 1;
        dword_4F28F0->unk_22 = 0;
        dword_4F28F0->unk_1C = 0;
        dword_4F28F0->unk_180 = 1;
        dword_4F28F0->unk_181 = 1;
        dword_4F28F0->unk_28 = 1;
        sp_sub_B0220();
    }
    else if (arg_0 == unk_54C)
    {
        sp_sub_B0220();
    }
    else
    {
        r = false;
    }
    return r;
}

// The pad button 23 (btnAction) as a value the compiler does not fold into a static initializer:
// the art gallery's sequence below has its last element stored at run time, under its guard
// (SP 0xB03A4: or [0x3B54CC], 1; mov [0x321910], 0x17).
static inline RwInt32 sp_pad_button_23()
{
    return 23;
}

// sp-match: ?sp_sub_B0300@type_sp_AE5D0@@QAE_NH@Z @ 0x000B0300
// The extras' buttons: the galleries and the making-of movies.
bool type_sp_AE5D0::sp_sub_B0300(RwInt32 arg_0)
{
    RwInt32 *flags = &dword_4F28F0->unk_30;
    bool r = true;

    if (arg_0 == unk_5BC) // urlGalleryEnter
    {
        unk_3C0 = 0;
    }
    else if (arg_0 == unk_5C0) // urlSelectedAnimation
    {
        // The pad buttons (21 left, 31, 19 up, 33) entered in turn (SP .rdata 0x2E5110, 0x2E50D4).
        static const RwInt32 sp_dword_2E5110[16] = { 21, 31, 19, 33, 21, 31, 19, 33, 21, 31, 19, 33, 21, 31, 19, 33 };
        static const RwInt32 sp_dword_2E50D4[15] = { 21, 31, 19, 33, 21, 31, 19, 33, 21, 31, 19, 33, 21, 31, 19 };

        unk_3C0 = 0;
        if (sp_sub_ADAE0(sp_dword_2E5110, 16, false))
        {
            *flags |= 0x7000;
        }
        if (sp_sub_ADAE0(sp_dword_2E50D4, 15, false))
        {
            *flags |= 0x7000;
        }
    }
    else if (arg_0 == unk_5C4) // urlSelectedArtwork
    {
        unk_3C0 = 0;
    }
    else if (arg_0 == unk_5D4) // urlArtGalleryEnter
    {
        RwTexDictionary *d;

        sub_E8860(true);
        static RwInt32 seq[7] = {22, 22, 22, 21, 21, 21, sp_pad_button_23()};
        sp_sub_ADAE0(seq, 7, false);
        d = sub_E8320("shell\\fend\\instance\\xbox\\artwork.txd");
        if (d)
        {
            sp_sub_A5EA0(d);
            sp_sub_A5F50();
            unk_7DC = 1;
        }
        sub_E88B0(true);
        sub_DA550(false);
    }
    else if (arg_0 == unk_5C8) // urlSelectedMaking1
    {
        unk_3C0 = 1;
    }
    else if (arg_0 == unk_5CC) // urlSelectedMaking2
    {
        unk_3C0 = 2;
    }
    else if (arg_0 == unk_5D0) // urlSelectedMaking3
    {
        unk_3C0 = 3;
    }
    else if (arg_0 == unk_518) // urlPlayMakingOf1
    {
        if (*flags & 0x1000)
        {
            sp_sub_AE9B0();
            sub_E8AC0("Making1.bik", (RwInt32)unk_178, 0, 0);
            type_3DF8D8_04 key(0x6D62AE9, 0xC7F591);
            sp_dword_3EC3E4 = (type_44C4E8 *)dword_4B1E98.sub_8A980(&key, 0, 0, (RwV3d *)&unk_4292B4, 1, 0);
        }
    }
    else if (arg_0 == unk_51C) // urlPlayMakingOf2
    {
        if (*flags & 0x2000)
        {
            sp_sub_AE9B0();
            sub_E8AC0("Making2.bik", (RwInt32)unk_178, 0, 0);
            type_3DF8D8_04 key(0x6D62AE9, 0xC7F591);
            sp_dword_3EC3E4 = (type_44C4E8 *)dword_4B1E98.sub_8A980(&key, 0, 0, (RwV3d *)&unk_4292B4, 1, 0);
        }
    }
    else if (arg_0 == unk_520) // urlPlayMakingOf3
    {
        if (*flags & 0x4000)
        {
            sp_sub_AE9B0();
            sub_E8AC0("Making3.bik", (RwInt32)unk_178, 0, 0);
            type_3DF8D8_04 key(0x6D62AE9, 0xC7F591);
            sp_dword_3EC3E4 = (type_44C4E8 *)dword_4B1E98.sub_8A980(&key, 0, 0, (RwV3d *)&unk_4292B4, 1, 0);
        }
    }
    else
    {
        r = false;
    }
    if (r)
    {
        type_sp_AE5D0_cb c = {sp_sub_AFEE0, &unk_3C0, 2, 1};
        sp_sub_AE800(&c);
    }
    return r;
}

// sp-match: ?sp_sub_B0590@type_sp_AE5D0@@QAE_NH@Z @ 0x000B0590
// The cheats screen's buttons.
bool type_sp_AE5D0::sp_sub_B0590(RwInt32 arg_0)
{
    type_4F28F0 *s = dword_4F28F0;
    bool r = true;

    if (arg_0 == unk_574 || arg_0 == unk_578)
    {
    }
    else if (arg_0 == unk_57C)
    {
        // SP .rdata 0x2E5174, 0x2E5150.
        static const RwInt32 sp_dword_2E5174[9] = { 20, 20, 19, 19, 21, 22, 21, 22, 25 };
        static const RwInt32 sp_dword_2E5150[9] = { 21, 31, 20, 34, 22, 32, 19, 33, 25 };

        if (!sp_sub_ADAE0(sp_dword_2E5174, 9, false) && sp_sub_ADAE0(sp_dword_2E5150, 9, false))
        {
            dword_4F28F0->unk_30 |= 0x7F;
        }
    }
    else if (arg_0 == unk_580)
    {
        s->unk_2C &= ~0x7F;
    }
    else if (arg_0 == unk_584)
    {
        s->unk_2C = 1;
    }
    else if (arg_0 == unk_588)
    {
        s->unk_2C &= ~0x7F;
    }
    else if (arg_0 == unk_58C)
    {
        s->unk_2C = 2;
    }
    else if (arg_0 == unk_590)
    {
        s->unk_2C &= ~0x7F;
    }
    else if (arg_0 == unk_594)
    {
        s->unk_2C = 4;
    }
    else if (arg_0 == unk_598)
    {
        s->unk_2C &= ~0x7F;
    }
    else if (arg_0 == unk_59C)
    {
        s->unk_2C = 8;
    }
    else if (arg_0 == unk_5A0)
    {
        s->unk_2C &= ~0x7F;
    }
    else if (arg_0 == unk_5A4)
    {
        s->unk_2C = 0x10;
    }
    else if (arg_0 == unk_5A8)
    {
        s->unk_2C &= ~0x7F;
    }
    else if (arg_0 == unk_5AC)
    {
        s->unk_2C = 0x20;
    }
    else if (arg_0 == unk_5B0)
    {
        s->unk_2C &= ~0x7F;
    }
    else if (arg_0 == unk_5B4)
    {
        s->unk_2C = 0x40;
    }
    else
    {
        r = false;
    }
    if (r)
    {
        type_sp_AE5D0_cb c = {sp_sub_AFFC0, 0, 2, 1};
        sp_sub_AE800(&c);
    }
    return r;
}

// sp-match: ?sp_sub_B0700@@YA_NPAUtype_sp_AE5D0@@PAX@Z @ 0x000B0700
// Shows the act selected, then its levels (sp_sub_AFCC0).
bool sp_sub_B0700(type_sp_AE5D0 *arg_0, void *arg_4)
{
    Rt2dAnimGotoKeyFrameListByIndex(arg_0->unk_39C[arg_0->unk_1DC].unk_00,
                                    arg_0->unk_39C[arg_0->unk_1DC].unk_04, arg_0->unk_1E0);
    type_sp_AE5D0_cb c = {sp_sub_AFCC0, 0, 1, 1};
    arg_0->sp_sub_AE800(&c);
    return false;
}

// sp-match: ?sp_sub_B0770@type_sp_AE5D0@@QAE_NH@Z @ 0x000B0770
bool type_sp_AE5D0::sp_sub_B0770(RwInt32 arg_0)
{
    bool r = sp_sub_B0250(arg_0) || sp_sub_B0300(arg_0) || sp_sub_AEB20(arg_0);

    if (r)
        return true;
    if (sp_sub_B0590(arg_0))
        return true;
    return false;
}

// sp-match: ?vf_000@type_sp_AE5D0@@UAEXH@Z @ 0x000B07C0
// The main menu's GETURL messages.
void type_sp_AE5D0::vf_000(RwInt32 arg_0)
{
    // The controller set-up chosen and not yet shown (-1: none; SP .data 0x321914, after seq).
    static RwInt32 sp_dword_321914 = -1;
    RwInt32 level;
    bool busy = false;

    sp_dword_3B4744 = 5;
    if (sp_sub_B0770(arg_0))
    {
    }
    else if (arg_0 == unk_3D8) // urlQuit
    {
        unk_04 = true;
        busy = true;
    }
    else if (arg_0 == unk_3DC) // enableBG
    {
        sub_E88B0(false);
    }
    else if (arg_0 == unk_3E0) // disableBG
    {
        sub_E8860(false);
    }
    else if (arg_0 == unk_3E4) // enableDemo
    {
        sub_DA550(true);
    }
    else if (arg_0 == unk_3E8) // disableDemo
    {
        sub_DA550(false);
    }
    else if (arg_0 == unk_3EC || arg_0 == unk_3F0)
    {
    }
    else if (arg_0 == unk_3F4) // streamOptions
    {
        sp_sub_A6100();
    }
    else if (arg_0 == unk_3F8 || arg_0 == unk_3FC || arg_0 == unk_404)
    {
    }
    else if (arg_0 == unk_408) // soundPressStart
    {
        dword_4B1E98.sub_8A980(&sp_unk_3217C8, 0, 0, (RwV3d *)&unk_4292B4, 1, 0);
    }
    else if (arg_0 == unk_40C) // soundPSScroll
    {
        dword_4B1E98.sub_8A980(&sp_unk_3217D0, 0, 0, (RwV3d *)&unk_4292B4, 1, 0);
    }
    else if (arg_0 == unk_410 || arg_0 == unk_414)
    {
    }
    else if (arg_0 == unk_418) // soundMSScroll
    {
        dword_4B1E98.sub_8A980(&sp_unk_3217E8, 0, 0, (RwV3d *)&unk_4292B4, 1, 0);
    }
    else if (arg_0 == unk_41C) // soundMSSelect
    {
        dword_4B1E98.sub_8A980(&sp_unk_3217F0, 0, 0, (RwV3d *)&unk_4292B4, 1, 0);
    }
    else if (arg_0 == unk_420) // soundCGScroll
    {
        dword_4B1E98.sub_8A980(&sp_unk_3217F8, 0, 0, (RwV3d *)&unk_4292B4, 1, 0);
    }
    else if (arg_0 == unk_424) // soundCGScrollAcross
    {
        dword_4B1E98.sub_8A980(&sp_unk_321810, 0, 0, (RwV3d *)&unk_4292B4, 1, 0);
    }
    else if (arg_0 == unk_428) // soundCGSelect
    {
        dword_4B1E98.sub_8A980(&sp_unk_321800, 0, 0, (RwV3d *)&unk_4292B4, 1, 0);
    }
    else if (arg_0 == unk_42C) // soundCGBack
    {
        dword_4B1E98.sub_8A980(&sp_unk_321808, 0, 0, (RwV3d *)&unk_4292B4, 1, 0);
    }
    else if (arg_0 == unk_430) // soundOSScrollDown
    {
        dword_4B1E98.sub_8A980(&sp_unk_321818, 0, 0, (RwV3d *)&unk_4292B4, 1, 0);
    }
    else if (arg_0 == unk_434) // soundOSScrollAcross
    {
        dword_4B1E98.sub_8A980(&sp_unk_321820, 0, 0, (RwV3d *)&unk_4292B4, 1, 0);
    }
    else if (arg_0 == unk_438) // soundOSSelect
    {
        sp_sub_B0130();
        dword_4B1E98.sub_8A980(&sp_unk_321828, 0, 0, (RwV3d *)&unk_4292B4, 1, 0);
    }
    else if (arg_0 == unk_43C) // soundOSBack
    {
        dword_4B1E98.sub_8A980(&sp_unk_321830, 0, 0, (RwV3d *)&unk_4292B4, 1, 0);
    }
    else if (arg_0 == unk_440) // soundCCScroll
    {
        dword_4B1E98.sub_8A980(&sp_unk_321838, 0, 0, (RwV3d *)&unk_4292B4, 1, 0);
    }
    else if (arg_0 == unk_444) // soundCCSelect
    {
        dword_4B1E98.sub_8A980(&sp_unk_321840, 0, 0, (RwV3d *)&unk_4292B4, 1, 0);
    }
    else if (arg_0 == unk_448) // soundCCBack
    {
        dword_4B1E98.sub_8A980(&sp_unk_321848, 0, 0, (RwV3d *)&unk_4292B4, 1, 0);
    }
    else if (arg_0 == unk_44C) // soundCSBack
    {
        dword_4B1E98.sub_8A980(&sp_unk_321850, 0, 0, (RwV3d *)&unk_4292B4, 1, 0);
    }
    else if (arg_0 == unk_450) // soundEXScroll
    {
        dword_4B1E98.sub_8A980(&sp_unk_321858, 0, 0, (RwV3d *)&unk_4292B4, 1, 0);
    }
    else if (arg_0 == unk_454) // soundEXSelect
    {
        dword_4B1E98.sub_8A980(&sp_unk_321860, 0, 0, (RwV3d *)&unk_4292B4, 1, 0);
    }
    else if (arg_0 == unk_458) // soundEXBack
    {
        dword_4B1E98.sub_8A980(&sp_unk_321868, 0, 0, (RwV3d *)&unk_4292B4, 1, 0);
    }
    else if (arg_0 == unk_45C) // soundDOScroll
    {
        dword_4B1E98.sub_8A980(&sp_unk_321870, 0, 0, (RwV3d *)&unk_4292B4, 1, 0);
    }
    else if (arg_0 == unk_460) // soundDOSelect
    {
        dword_4B1E98.sub_8A980(&sp_unk_321878, 0, 0, (RwV3d *)&unk_4292B4, 1, 0);
    }
    else if (arg_0 == unk_464) // soundDOBack
    {
        dword_4B1E98.sub_8A980(&sp_unk_321880, 0, 0, (RwV3d *)&unk_4292B4, 1, 0);
    }
    else if (arg_0 == unk_468) // soundUNScroll
    {
        dword_4B1E98.sub_8A980(&sp_unk_321888, 0, 0, (RwV3d *)&unk_4292B4, 1, 0);
    }
    else if (arg_0 == unk_46C) // soundUNSelect
    {
        dword_4B1E98.sub_8A980(&sp_unk_321890, 0, 0, (RwV3d *)&unk_4292B4, 1, 0);
    }
    else if (arg_0 == unk_470) // soundUNBack
    {
        dword_4B1E98.sub_8A980(&sp_unk_321898, 0, 0, (RwV3d *)&unk_4292B4, 1, 0);
    }
    else if (arg_0 == unk_474) // soundGAScroll
    {
        dword_4B1E98.sub_8A980(&sp_unk_3218B0, 0, 0, (RwV3d *)&unk_4292B4, 1, 0);
    }
    else if (arg_0 == unk_478) // soundGASelect
    {
        type_4F28F0 *state = dword_4F28F0;
        if (unk_3C0 == 0 || (unk_3C0 == 1 && (state->unk_30 & 0x1000))
            || (unk_3C0 == 2 && (state->unk_30 & 0x2000))
            || (unk_3C0 == 3 && (state->unk_30 & 0x4000)))
        {
            dword_4B1E98.sub_8A980(&sp_unk_3218B8, 0, 0, (RwV3d *)&unk_4292B4, 1, 0);
        }
    }
    else if (arg_0 == unk_47C) // soundGABack
    {
        dword_4B1E98.sub_8A980(&sp_unk_3218C0, 0, 0, (RwV3d *)&unk_4292B4, 1, 0);
    }
    else if (arg_0 == unk_480) // soundCHScroll
    {
        dword_4B1E98.sub_8A980(&sp_unk_3218C8, 0, 0, (RwV3d *)&unk_4292B4, 1, 0);
    }
    else if (arg_0 == unk_484) // soundCHSelect
    {
        dword_4B1E98.sub_8A980(&sp_unk_3218D0, 0, 0, (RwV3d *)&unk_4292B4, 1, 0);
    }
    else if (arg_0 == unk_488) // soundLPScroll
    {
        dword_4B1E98.sub_8A980(&sp_unk_3218D8, 0, 0, (RwV3d *)&unk_4292B4, 1, 0);
    }
    else if (arg_0 == unk_48C) // soundLPSelect
    {
        dword_4B1E98.sub_8A980(&sp_unk_3218E0, 0, 0, (RwV3d *)&unk_4292B4, 1, 0);
    }
    else if (arg_0 == unk_490) // soundLPBack
    {
        dword_4B1E98.sub_8A980(&sp_unk_3218E8, 0, 0, (RwV3d *)&unk_4292B4, 1, 0);
    }
    else if (arg_0 == unk_49C) // selectProfile
    {
        type_sp_ADF20 a = sp_sub_ADF20("/imcProfileSelection/");
        RwInt32 slot = Rt2dAnimGetPrevFrameIndex(a.unk_00);

        const RwChar *text = Rt2dObjectStringGetText(unk_610[slot][0]);
        if (!strcmp(text, unk_7C0))
        {
            dword_4B1E98.sub_8A980(&sp_unk_3218F0, 0, 0, (RwV3d *)&unk_4292B4, 1, 0);
        }
        else
        {
            dword_4B1E98.sub_8A980(&sp_unk_3217D8, 0, 0, (RwV3d *)&unk_4292B4, 1, 0);
            dword_4F28F0->unk_44 = slot;
            sub_E8860(true);
            if (dword_4F6158[slot])
            {
                dword_4F6168 = slot;
                sp_sub_129AC0(0x2D);
            }
            else
            {
                type_186020 r = sp_sub_11B900(unk_178, &unk_4B8744, slot, sp_sub_AE970, this);
                sub_E88B0(true);
                // shape: retain the boolean comparison result before branching.
                const bool &ok = r == 0;
                if (ok)
                {
                    dword_4F28F0->unk_58 = 1;
                    sp_sub_AE9A0();
                    sp_sub_AFCA0();
                }
            }
        }
    }
    else if (arg_0 == unk_4A0) // createNewProfile
    {
        type_sp_ADF20 a = sp_sub_ADF20("/imcProfileSelection/");
        RwInt32 slot = Rt2dAnimGetPrevFrameIndex(a.unk_00);
        RwInt32 overwrite;
        RwInt32 res;

        dword_4F28F0->unk_44 = slot;
        dword_4B1E98.sub_8A980(&sp_unk_3217E0, 0, 0, (RwV3d *)&unk_4292B4, 1, 0);
        overwrite = 0;
        const RwChar *text = Rt2dObjectStringGetText(unk_610[slot][0]);
        if (strcmp(text, unk_7C0))
        {
            sub_E8860(true);
            type_186020 r = sp_sub_11B930(unk_178, &unk_4B8744, sp_sub_AE970, this);
            sub_E88B0(true);
            if (r.unk_00)
            {
                goto dispatch_level;
            }
            overwrite = 1;
        }
        dword_4F28F0->unk_44 = slot;
        sp_sub_AE9A0();
        res = sp_sub_A55F0(unk_178, slot, &unk_4B8744, overwrite);
        if (!res)
        {
            sp_sub_AFCA0();
        }
        else
        {
            sp_sub_AE980();
            unk_7CE = res == 2;
        }
    }
    else if (arg_0 == unk_494) // enteringProfileSelect
    {
        if (unk_7CF)
        {
            unk_7CF = false;
            sp_sub_AE6F0();
            sub_E88B0(true);
            unk_7D0 = false;
        }
    }
    else if (arg_0 == unk_498) // enableMemCardMonitoring
    {
        sp_sub_AE980();
    }
    else if (arg_0 == unk_4A4) // leavingSelectProfile
    {
        sp_sub_AE9A0();
    }
    else if (arg_0 == unk_5F0) // enteringLevelSelect
    {
        unk_1E4 = dword_4F28F0->unk_54;
        sp_sub_AE8C0();
        type_sp_AE5D0_cb c = {sp_sub_B0700, 0, 1, 1};
        sp_sub_AE800(&c);
        unk_1E8 = true;
        busy = true;
    }
    else if (arg_0 == unk_5F4) // updateLevelStates
    {
        if (!unk_1E8)
        {
            type_sp_AE5D0_cb c = {sp_sub_AFCC0, 0, 1, 1};
            sp_sub_AE800(&c);
        }
    }
    else if (arg_0 == unk_5F8) // selectPreviousAct
    {
        if (unk_1DC > 0)
        {
            unk_1DC--;
        }
        else
        {
            unk_1DC = 2;
        }
        unk_1E0 = 0;
        busy = true;
    }
    else if (arg_0 == unk_5FC) // selectNextAct
    {
        if (unk_1DC < 2)
        {
            unk_1DC++;
        }
        else
        {
            unk_1DC = 0;
        }
        unk_1E0 = 0;
        busy = true;
    }
    else if (arg_0 == unk_600) // selectPreviousLevel
    {
        if (unk_1E0 > 0)
        {
            unk_1E0--;
        }
    }
    else if (arg_0 == unk_604) // selectNextLevel
    {
        if (unk_1E0 + 1 < 8 && unk_1EC[unk_1DC][unk_1E0 + 1].unk_0C <= unk_1E4)
        {
            RwInt32 data[2];

            unk_1E0 = unk_1E0 + 1;
            data[1] = 0x40;
            data[0] = unk_3C4[0];
            Rt2dMaestroForAllVisibleAnimations(unk_17C, sp_sub_ADDF0, data);
        }
    }
    else if (arg_0 == unk_608) // checkUnlockSPLvlsMBS
    {
        static const RwInt32 sp_dword_2E5204[4] = { 11, 17, 17, 25 }; // SP .rdata 0x2E5204

        if (sp_sub_ADAE0(sp_dword_2E5204, 4, true) && unk_1E4 != 0x26)
        {
            unk_1E4 = 0x26;
            type_sp_AE5D0_cb c = {sp_sub_AFCC0, 0, 1, 1};
            sp_sub_AE800(&c);
            busy = true;
        }
    }
    if (busy)
    {
        sp_byte_3B4720 = true;
    }
dispatch_level:
    // shape: separate selection from launch so every level shares the launch block.
    bool selected = true;
    if (arg_0 == unk_4AC)
    {
        level = 0x2;
    }
    else if (arg_0 == unk_4C8)
    {
        level = 0xC;
    }
    else if (arg_0 == unk_4D4)
    {
        level = 0x11;
    }
    else if (arg_0 == unk_4DC)
    {
        level = 0x18;
    }
    else if (arg_0 == unk_4A8)
    {
        level = 0x1;
    }
    else if (arg_0 == unk_4B0)
    {
        level = 0x4;
    }
    else if (arg_0 == unk_4B4)
    {
        level = 0x5;
    }
    else if (arg_0 == unk_4B8)
    {
        level = 0x7;
    }
    else if (arg_0 == unk_4BC)
    {
        level = 0x8;
    }
    else if (arg_0 == unk_4C0)
    {
        level = 0xA;
    }
    else if (arg_0 == unk_4C4)
    {
        level = 0xB;
    }
    else if (arg_0 == unk_4CC)
    {
        level = 0xE;
    }
    else if (arg_0 == unk_4D0)
    {
        level = 0xF;
    }
    else if (arg_0 == unk_4D8)
    {
        level = 0x12;
    }
    else if (arg_0 == unk_4E0)
    {
        level = 0x19;
    }
    else if (arg_0 == unk_4E4)
    {
        level = 0x1A;
    }
    else if (arg_0 == unk_4E8)
    {
        level = 0x1B;
    }
    else if (arg_0 == unk_4EC)
    {
        level = 0x1C;
    }
    else if (arg_0 == unk_4F0)
    {
        level = 0x1E;
    }
    else if (arg_0 == unk_4F4)
    {
        level = 0x1F;
    }
    else if (arg_0 == unk_4F8)
    {
        level = 0x21;
    }
    else if (arg_0 == unk_4FC)
    {
        level = 0x22;
    }
    else if (arg_0 == unk_500)
    {
        level = 0x24;
    }
    else if (arg_0 == unk_504)
    {
        level = 0x25;
    }
    else if (arg_0 == unk_508)
    {
        level = 0x26;
    }
    else
    {
        selected = false;
    }
    if (!selected)
    {
        if (arg_0 == unk_50C)
        {
            sp_sub_AE9B0();
            sub_E8AC0("Act_1.bik", (RwInt32)unk_178, 0, 0);
        }
        else if (arg_0 == unk_510)
        {
            sp_sub_AE9B0();
            sub_E8AC0("Act_2.bik", (RwInt32)unk_178, 0, 0);
        }
        else if (arg_0 == unk_514)
        {
            sp_sub_AE9B0();
            sub_E8AC0("Act_3.bik", (RwInt32)unk_178, 0, 0);
        }
        else if (arg_0 == unk_524)
        {
            sp_sub_AE9B0();
            sub_E8AC0("Credits.bik", (RwInt32)unk_178, 0, 0);
            type_3DF8D8_04 key(0x6D62AE9, 0xC7F591);
            sp_dword_3EC3E4 = (type_44C4E8 *)dword_4B1E98.sub_8A980(&key, 0, 0, (RwV3d *)&unk_4292B4, 1, 0);
        }
        else if (arg_0 == unk_528)
        {
            sp_sub_AE9B0();
            sub_E8AC0("AnimReel.bik", (RwInt32)unk_178, 0, 0);
            type_3DF8D8_04 key(0x6D62AE9, 0xC7F591);
            sp_dword_3EC3E4 = (type_44C4E8 *)dword_4B1E98.sub_8A980(&key, 0, 0, (RwV3d *)&unk_4292B4, 1, 0);
        }
        else if (arg_0 == unk_52C)
        {
            sp_sub_AE9B0();
            sub_E8AC0("Intro.bik", (RwInt32)unk_178, 0, 0);
            type_3DF8D8_04 key(0x6D62AE9, 0xC7F591);
            sp_dword_3EC3E4 = (type_44C4E8 *)dword_4B1E98.sub_8A980(&key, 0, 0, (RwV3d *)&unk_4292B4, 1, 0);
        }
        else if (arg_0 == unk_558) // enteringControllerConfig
        {
            // shape: read the configured controller before choosing the override.
            const RwInt32 &c = dword_4F28F0->get_unk_1C();
            if (sp_dword_321914 >= 0)
            {
                sp_sub_AF730("/imcConfigXbox/", sp_dword_321914);
            }
            else
            {
                sp_sub_AF730("/imcConfigXbox/", c);
            }
            sp_dword_321914 = -1;
        }
        else if (arg_0 == unk_55C) // setControllerConfig
        {
            dword_4F28F0->unk_1C = sp_sub_AF700("/imcConfigXbox/");
        }
        else if (arg_0 == unk_560) // setOutgoingCC
        {
            sp_dword_321914 = sp_sub_AF700("/mcControls/");
        }
        else if (arg_0 == unk_564) // shakeIt
        {
            if (!sp_sub_AF700("/mcVibration/"))
            {
                unk_4B9308.sub_EED30(0, 1, 0xDC, 4);
            }
        }
        else if (arg_0 == unk_568) // profileOptionsSave
        {
            sub_E8860(true);
            sp_sub_11BAE0(unk_178, &unk_4B8744, dword_4F28F0->unk_44, sp_sub_AE970, this);
            unk_4B9308.sub_EE6D0();
            sub_E88B0(true);
        }
        else if (arg_0 == unk_56C) // profileOptionsLoad
        {
            sub_E8860(true);
            if (sp_sub_11B9A0(unk_178, &unk_4B8744, dword_4F28F0->get_unk_44(), sp_sub_AE970, this).unk_00 == 0)
            {
                sp_sub_B0220();
            }
            unk_4B9308.sub_EE6D0();
            sub_E88B0(true);
        }
        else if (arg_0 == unk_570) // profileOptionsCreateNew
        {
            sub_E8860(true);
            if (sp_sub_11B890(unk_178, sp_sub_AE970, this).unk_00)
            {
                sub_E88B0(true);
                return;
            }
            sub_E88B0(true);
            sub_E8860(true);
            for (;;)
            {
                type_186020 r = sp_sub_11B9A0(unk_178, &unk_4B8744, dword_4F28F0->unk_44, sp_sub_AE970, this);
                sub_E88B0(true);
                unk_4B9308.sub_EE6D0();
                if (r.unk_00)
                {
                    return;
                }
                if (!sp_sub_A55F0(unk_178, dword_4F28F0->get_unk_44(), &unk_4B8744, r.unk_04 != 0))
                {
                    sp_sub_B0220();
                    return;
                }
                sub_E8860(true);
            }
        }
        else if (arg_0 == unk_5B8) // urlPersonalScreensEnter
        {
            RwTexDictionary *d;

            sub_E8860(true);
            d = sub_E8320("shell\\fend\\instance\\xbox\\slideshw.txd");
            if (d)
            {
                sp_sub_A5EA0(d);
            }
            sub_E88B0(true);
            unk_7DC = 1;
        }
        else if (arg_0 == unk_5D8) // urlSlideshowLeave
        {
            RwTexDictionaryDestroy(sp_dword_3B475C);
            sp_sub_A5EA0(0);
            unk_7DC = -1;
        }
        else if (arg_0 == unk_60C) // urlMultiplayer
        {
            sp_sub_AE9E0(unk_178, 0);
        }
        else if (arg_0 == unk_5EC) // urlDisableRender
        {
            sp_byte_3B4720 = true;
        }
        return;
    }
    sub_19B000(level);
    if (dword_4F28F0->unk_58 && dword_4F28F0->unk_B8.unk_0C != level)
    {
        dword_4F28F0->unk_58 = 0;
    }
}
