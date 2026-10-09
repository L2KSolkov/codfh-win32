/*
 * Single player's profile name editor (SP 0xB2110-0xB2973; include/sp/sp_fend.h): a front end
 * screen (type_sp_AD970, src/sp/units/sp_fend.cpp) with an on-screen keyboard, played from its
 * own maestro ("shell\fend\profile.csv" holds its texts). Accepting a name starts a new profile:
 * the save state's defaults, then the memory unit save (sub_186140). Not in the multiplayer
 * image: single player only, never compiled for multiplayer.
 *
 * Evidence: the code sits between the movie player (unit_0E8800, its last function SP 0xB20B0)
 * and the loading screen (unit_0E8F40, SP 0xB2980), apart from the rest of the front end; its
 * strings ("kbHit", "playBGStream", "$playernameedit", "/imcEditor/imcKeyboard/",
 * "shell\fend\profile.csv") exist only in default.xbe; the shell (SP 0xA5677, 0xA568B, 0xA56E7)
 * sets it up and steps it, and its vtable is SP 0x2E37E8.
 */
#include <string.h>

#include "rw/ostypes.h"
#include "rw/baengine.h"
#include "rw/rt2d.h"
#include "game/data.h"
#include "game/gameloop.h"
#include "game/movie.h"
#include "game/waitscreen.h"
#include "types/type_DA0A0.h"
#include "types/type_8A980.h"
#include "types/type_3DF8D8.h"
#include "sp/sp_fend.h"

// Its data definitions (PLAN SP5), in the image's address order.
// SP 0x002E5258
extern const RwReal sp_flt_2E5258 = 16.666666f; // unreferenced, just before its first string
// SP 0x003B5830
RwReal sp_flt_3B5830;                   // the B button last step
// End of its data definitions.

// The editor's sounds: the six keys unit_0E8800 defines (SP .data 0x32191C-0x32194B, in this
// order), which multiplayer never reads.
extern type_3DF8D8_04 unk_4B8EB8;
extern type_3DF8D8_04 unk_4B8EC0;
extern type_3DF8D8_04 unk_4B8ED8;
extern type_3DF8D8_04 unk_4B8EE0;
extern type_3DF8D8_04 unk_4B8EC8;
extern type_3DF8D8_04 unk_4B8ED0;

void sub_19B000(RwInt32 arg_0);
void sp_sub_1291D0(RwInt32 arg_0);

// sp-match: ?sp_sub_B2110@type_sp_B2110@@QAEXM@Z @ 0x000B2110
// Steps it: B leaves it.
void type_sp_B2110::sp_sub_B2110(RwReal arg_0)
{
    RwReal v;

    sp_sub_AE0D0(arg_0);
    v = unk_4B9308.sub_EE9A0(0, 0x18);
    if (v != 0.0f && sp_flt_3B5830 == 0.0f)
    {
        unk_1DC = 1;
        unk_04 = true;
        return;
    }
    sp_flt_3B5830 = v;
    unk_248 += arg_0;
}

// sp-match: ?sp_sub_B2180@type_sp_B2110@@QAEXP6A_NPAUtype_sp_B21B0@@PAX@Z1@Z @ 0x000B2180
void type_sp_B2110::sp_sub_B2180(bool (*arg_0)(type_sp_B21B0 *, void *), void *arg_4)
{
    unk_234 = arg_0;
    unk_238 = arg_4;
}

// sp-match: ?sp_sub_B21A0@@YAXPAURwCamera@@PAX@Z @ 0x000B21A0
// The memory unit save's draw callback: the editor arg_4.
void sp_sub_B21A0(RwCamera *arg_0, void *arg_4)
{
    ((type_sp_B2110 *)arg_4)->sp_sub_AD750(0);
}

// sp-match: ?sp_sub_B21B0@@YA_NPAUtype_sp_B21B0@@PAX@Z @ 0x000B21B0
// Starts a new profile named arg_0->unk_00 (its trailing spaces cut) and saves it.
bool sp_sub_B21B0(type_sp_B21B0 *arg_0, void *arg_4)
{
    RwInt32 n;
    type_D90B0 state;
    type_DA0A0 save;

    n = strlen(arg_0->unk_00) - 1;
    while (arg_0->unk_00[n] == ' ')
    {
        arg_0->unk_00[n] = 0;
        n--;
    }
    strcpy(dword_4F28F0->unk_48, arg_0->unk_00);
    sub_19B000(1);
    dword_4F28F0->unk_54 = 1;
    sp_sub_1291D0(1);
    dword_4F28F0->unk_1C = 0;
    dword_4F28F0->unk_20 = 1;
    dword_4F28F0->unk_22 = 0;
    dword_4F28F0->unk_18 = 1;
    dword_4F28F0->unk_14 = 1;
    dword_4F28F0->unk_21 = 1;
    dword_4F28F0->unk_28 = 1;
    dword_4F28F0->unk_180 = 1;
    dword_4F28F0->unk_181 = 1;
    sp_sub_1291D0(1);
    state.sub_D90B0();
    dword_4F28F0->unk_5C = state;
    dword_4F28F0->unk_58 = 0;
    sub_E8860(true);
    sub_186140(arg_0->unk_14, arg_0->unk_0C, arg_0->unk_04, true, 0, (void *)(arg_0->unk_10 != 0),
               sp_sub_B21A0, arg_0->unk_08);
    sub_D9EC0(&save);
    dword_4F28F0->unk_B8 = save;
    sub_E88B0(true);
    return true;
}

// sp-match: ?sp_sub_B23A0@@YAPAURt2dObject@@PAU1@0PAX@Z @ 0x000B23A0
// Finds the name's string object ("$playernameedit") under arg_0 into *arg_8.
Rt2dObject *sp_sub_B23A0(Rt2dObject *arg_0, Rt2dObject *arg_4, void *arg_8)
{
    if (*(Rt2dObject **)arg_8)
    {
        return arg_0;
    }
    if (Rt2dObjectIsScene(arg_0))
    {
        Rt2dSceneForAllChildren(arg_0, sp_sub_B23A0, arg_8);
        return arg_0;
    }
    if (Rt2dObjectIsObjectString(arg_0))
    {
        RwInt32 r = strcmp(Rt2dObjectStringGetText(arg_0), "$playernameedit");
        if (!r)
        {
            *(Rt2dObject **)arg_8 = arg_0;
        }
    }
    return arg_0;
}

// sp-match: ?sp_sub_B2420@type_sp_B2110@@QAEXXZ @ 0x000B2420
void type_sp_B2110::sp_sub_B2420()
{
    sp_sub_ADE30("kbHit", &unk_1E0, 6);
    sp_sub_ADE30("soundScroll", &unk_1E4, 6);
    sp_sub_ADE30("playBGStream", &unk_1E8, 6);
}

// sp-match: ?vf_000@type_sp_B2110@@UAEXH@Z @ 0x000B2470
// The keyboard: letters, space, delete, capitals and done.
// shape: share the append block at the first letter row (SP 0xB24FF), so the second
// row jumps back to it and the delete key keeps the common text update (SP 0xB2592).
void type_sp_B2110::vf_000(RwInt32 arg_0)
{
    RwInt32 key;
    RwInt32 ch;
    RwInt32 c;

    if (arg_0 == unk_1E0)
    {
        key = Rt2dAnimGetPrevFrameIndex(unk_1F0.unk_00);
        if (key == 2 || key == 3)
        {
            ch = Rt2dAnimGetPrevFrameIndex(unk_208.unk_00);
        }
        else
        {
            ch = Rt2dAnimGetPrevFrameIndex(unk_1FC.unk_00);
        }
        c = 0;
        switch (key)
        {
        case 0:
            c = ch + unk_224 + 'a';
            unk_224 = 0;
            Rt2dAnimGotoKeyFrameListByIndex(unk_214.unk_00, unk_214.unk_04, 0);
        append_character:
            if (c && unk_220 < 0xB)
            {
                unk_228[unk_220] = (RwChar)c;
                unk_220++;
                dword_4B1E98.sub_8A980(&unk_4B8EC0, 0, 0, (RwV3d *)&unk_4292B4, 1, 0);
            }
            goto update_text;
        case 1:
            c = ch + unk_224 + 'n';
            unk_224 = 0;
            Rt2dAnimGotoKeyFrameListByIndex(unk_214.unk_00, unk_214.unk_04, 0);
            goto append_character;
        case 2:
            switch (ch)
            {
            case 0:
                if (!unk_220)
                {
                    return;
                }
                c = ' ';
                dword_4B1E98.sub_8A980(&unk_4B8ED8, 0, 0, (RwV3d *)&unk_4292B4, 1, 0);
                break;
            case 1:
                if (!unk_220)
                {
                    return;
                }
                dword_4B1E98.sub_8A980(&unk_4B8EE0, 0, 0, (RwV3d *)&unk_4292B4, 1, 0);
                unk_228[unk_220 - 1] = 0;
                unk_220--;
                Rt2dObjectStringSetText(unk_1EC, unk_228);
                return;
            }
            break;
        case 3:
            switch (ch)
            {
            case 0:
                if (strlen(unk_228))
                {
                    dword_4B1E98.sub_8A980(&unk_4B8ED0, 0, 0, (RwV3d *)&unk_4292B4, 1, 0);
                    if (unk_234)
                    {
                        type_sp_B21B0 s;

                        s.unk_00 = unk_228;
                        s.unk_04 = unk_244;
                        s.unk_08 = this;
                        s.unk_0C = unk_23C;
                        s.unk_10 = unk_240;
                        s.unk_14 = unk_178;
                        if (unk_234(&s, unk_238))
                        {
                            unk_04 = true;
                            return;
                        }
                    }
                }
                break;
            case 1:
                dword_4B1E98.sub_8A980(&unk_4B8EC8, 0, 0, (RwV3d *)&unk_4292B4, 1, 0);
                if (unk_224)
                {
                    unk_224 = 0;
                    Rt2dAnimGotoKeyFrameListByIndex(unk_214.unk_00, unk_214.unk_04, 0);
                }
                else
                {
                    unk_224 = -0x20;
                    Rt2dAnimGotoKeyFrameListByIndex(unk_214.unk_00, unk_214.unk_04, 1);
                }
                return;
            }
            break;
        }
        goto append_character;
    update_text:
        Rt2dObjectStringSetText(unk_1EC, unk_228);
    }
    else if (arg_0 == unk_1E4)
    {
        dword_4B1E98.sub_8A980(&unk_4B8EB8, 0, 0, (RwV3d *)&unk_4292B4, 1, 0);
    }
}

// Sets it up for the profile slot arg_0 of the memory unit arg_4 (the name is cleared a
// character at a time: its own zero register, three dword stores, SP 0xB27E4).
// sp-match: ?sp_sub_B2750@type_sp_B2110@@QAEXHPAUtype_D9CF0@@PAURwCamera@@H@Z @ 0x000B2750
void type_sp_B2110::sp_sub_B2750(RwInt32 arg_0, type_D9CF0 *arg_4, RwCamera *arg_8, RwInt32 arg_C)
{
    RwInt32 i;

    sp_sub_AD990(arg_8);
    unk_244 = arg_0;
    unk_23C = arg_4;
    unk_240 = arg_C;
    sp_sub_B2180(sp_sub_B21B0, this);
    unk_1EC = 0;
    unk_224 = 0;
    unk_220 = 0;
    unk_1F0.unk_00 = 0;
    unk_1F0.unk_04 = 0;
    unk_1F0.unk_08 = 0;
    unk_1FC.unk_00 = 0;
    unk_1FC.unk_04 = 0;
    unk_1FC.unk_08 = 0;
    unk_208.unk_00 = 0;
    unk_208.unk_04 = 0;
    unk_208.unk_08 = 0;
    unk_214.unk_00 = 0;
    unk_214.unk_04 = 0;
    unk_214.unk_08 = 0;
    for (i = 0; i < 0xC; i++)
    {
        unk_228[i] = 0;
    }
    unk_1DC = 0;
}

// sp-match: ?sp_sub_B2810@type_sp_B2110@@QAE_NPBD00@Z @ 0x000B2810
bool type_sp_B2110::sp_sub_B2810(const RwChar *arg_0, const RwChar *arg_4, const RwChar *arg_8)
{
    type_sp_ADD00 l;
    Rt2dObject *objects[0x80];

    if (sp_sub_AE3C0(arg_0, arg_4, arg_8))
    {
        l.unk_00 = 0;
        l.unk_04 = 0x80;
        l.unk_08 = objects;
        Rt2dSceneForAllChildren(Rt2dMaestroGetScene(unk_17C), sp_sub_ADD00, &l);
        sp_sub_B2420();
        sp_sub_B23A0(Rt2dMaestroGetScene(unk_17C), 0, &unk_1EC);
        unk_1F0 = sp_sub_ADF20("/imcEditor/");
        unk_1FC = sp_sub_ADF20("/imcEditor/imcHorizontalEdit/");
        unk_208 = sp_sub_ADF20("/imcEditor/imcHorizontalEditLarge/");
        unk_214 = sp_sub_ADF20("/imcEditor/imcKeyboard/");
        Rt2dObjectStringSetText(unk_1EC, " ");
        sp_sub_B39F0(objects, l.unk_00, "shell\\fend\\profile.csv");
        return true;
    }
    return false;
}

// Folded by /OPT:ICF into type_sp_AD730::sp_sub_AD750 (SP 0xAD750): defined for the link.
void type_sp_B2110::sp_sub_AD750(RwCamera *arg_0)
{
    sp_sub_ADB50(arg_0);
}
