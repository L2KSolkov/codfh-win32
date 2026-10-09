/*
 * Single player's language screen (SP 0xAD730-0xAD96F; include/sp/sp_fend.h): the first front
 * end screen (type_sp_AD730), played from the fend maestro ("shell\fend\fend.csv" holds its
 * texts). Not in the multiplayer image: single player only, never compiled for multiplayer.
 *
 * Evidence: a file of its own in default.xbe: its unreferenced 16.666666f (SP 0x2E40F8) heads
 * its .rdata just before its strings ("soundSelect" ... "languageSelected", "shell\fend\fend.csv",
 * SP 0x2E40FC-0x2E414B), and the screens' base (sp_fendbase.cpp) has its own one after them
 * (SP 0x2E414C).
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

// Its data definitions (PLAN SP5), in the image's address order (its .data is defined
// further down, where the image's order puts it).
// SP 0x002E40F8
extern const RwReal sp_flt_2E40F8 = 16.666666f; // unreferenced, just before its first string
// End of its data definitions.

// single player's own front-end .bss (sp_fend.cpp)
extern RwInt32 sp_dword_3B4718;
extern type_DA580 *sp_dword_3B481C;
extern bool sp_byte_3B4822;
extern RwReal sp_flt_3B4828[0x28];
extern type_4F45F8 sp_unk_3B48C8;
extern RwInt32 sp_dword_3B54C8;
extern type_44C4E8 *sp_dword_3EC3E4;

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

// The language screen.

// sp-match: ?sp_sub_AD730@type_sp_AD730@@QAE_NXZ @ 0x000AD730
bool type_sp_AD730::sp_sub_AD730()
{
    return sp_sub_AD990(0);
}

// sp-match: ?sp_sub_AD740@type_sp_AD730@@QAEXM@Z @ 0x000AD740
void type_sp_AD730::sp_sub_AD740(RwReal arg_0)
{
    sp_sub_AE0D0(arg_0);
}

// sp-match: ?sp_sub_AD750@type_sp_AD730@@QAEXPAURwCamera@@@Z @ 0x000AD750
void type_sp_AD730::sp_sub_AD750(RwCamera *arg_0)
{
    sp_sub_ADB50(arg_0);
}

// sp-match: ?sp_sub_AD760@type_sp_AD730@@QAEXXZ @ 0x000AD760
void type_sp_AD730::sp_sub_AD760()
{
    sp_sub_ADE30("languageSelected", &unk_1DC, 6);
    sp_sub_ADE30("streamBG", &unk_1E0, 6);
    sp_sub_ADE30("soundScroll", &unk_1E4, 6);
    sp_sub_ADE30("soundSelect", &unk_1E8, 6);
}

// sp-match: ?vf_000@type_sp_AD730@@UAEXH@Z @ 0x000AD7C0
void type_sp_AD730::vf_000(RwInt32 arg_0)
{
    RwInt32 l;

    if (arg_0 == unk_1DC)
    {
        type_sp_ADF20 a = sp_sub_ADF20("/");

        switch (Rt2dAnimGetPrevFrameIndex(a.unk_00) - 1)
        {
        case 0:
            l = 2;
            break;
        case 1:
            l = 5;
            break;
        case 2:
            l = 6;
            break;
        default:
            l = 0;
            break;
        }
        sub_19B0C0(l);
        unk_04 = true;
    }
    else if (arg_0 != unk_1E0)
    {
        if (arg_0 == unk_1E4)
        {
            dword_4B1E98.sub_8A980(&unk_4B8B48, 0, 0, (RwV3d *)&unk_4292B4, 1, 0);
        }
        else if (arg_0 == unk_1E8)
        {
            dword_4B1E98.sub_8A980(&unk_4B8B40, 0, 0, (RwV3d *)&unk_4292B4, 1, 0);
        }
    }
}

// sp-match: ?sp_sub_AD8C0@type_sp_AD730@@QAE_NPBD0PAURwTexDictionary@@@Z @ 0x000AD8C0
bool type_sp_AD730::sp_sub_AD8C0(const RwChar *arg_0, const RwChar *arg_4, RwTexDictionary *arg_8)
{
    type_sp_ADD00 l;
    Rt2dObject *objects[0x400];

    if (sp_sub_AE3C0(arg_0, arg_4, 0))
    {
        unk_184 = arg_8;
        unk_10 = true;
        l.unk_00 = 0;
        l.unk_04 = 0x400;
        l.unk_08 = objects;
        Rt2dSceneForAllChildren(Rt2dMaestroGetScene(unk_17C), sp_sub_ADD00, &l);
        sp_sub_AD760();
        sp_sub_B39F0(objects, l.unk_00, "shell\\fend\\fend.csv");
        return true;
    }
    return false;
}
