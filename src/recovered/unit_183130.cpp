// The debug menu (game/debugmenu.h).

#include "rw/ostypes.h"
#include "rw/bamemory.h"
#include "types/animkey.h"
#include "game/functions.h"
#include "game/data.h"
#include "game/gameloop.h"
#include "game/debugmenu.h"
#include <string.h>
#include <math.h>
#include <stdio.h>
#include "rw/rt2d.h"
#include "rw/badevice.h"
#include "types/type_DA580.h"
#include "game/profiler.h"
#include "rws/gftime.h"
#include "rw/baengine.h"
#include "types/type_DC400.h"
#include "game/lightscales.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003DE5C4
extern const RwReal flt_3DE5C4 = 16.666666f;
// 0x0042A4D4
type_4E73A8_14 off_42A4D4 = { "MAIN DEBUG MENU", 0, 0, 0, 0 };
// 0x0042A4E8
RwInt32 unk_42A4E8 = 1;
// 0x0042A4EC
RwReal unk_42A4EC = 3.0f;
// 0x004E739C
RwInt32 unk_4E739C;
// 0x004E73A0
RwInt32 unk_4E73A0;
// End of its data definitions.


// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).
type_4E73A8 unk_4E73A8;
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0BA@DDAEONIJ@MAIN?5DEBUG?5MENU?$AA@ @ 0x003DE5B4
// match: ?flt_3DE5C4@@3MB @ 0x003DE5C4
// match: ??_C@_0BA@EDCKMLNE@int?5g_debugInt1?$AA@ @ 0x003DE5C8
// match: ??_C@_0BA@FKDBPKJF@int?5g_debugInt0?$AA@ @ 0x003DE5D8
// match: ??_C@_0BB@KKJMJPGP@int?5g_debugFloat?$AA@ @ 0x003DE5E8
// match: ??_C@_0BC@NNJKKHDA@int?5g_debugSwitch?$AA@ @ 0x003DE5FC
// match: ??_C@_0P@INPIEIIM@Debug?5Switches?$AA@ @ 0x003DE610
// match: ??_C@_0P@GNAJNEL@Unlimited?5Ammo?$AA@ @ 0x003DE620
// match: ??_C@_06HGHFEALA@Cheats?$AA@ @ 0x003DE630
// match: ??_C@_0L@JPAJOGEO@Game?5Speed?$AA@ @ 0x003DE638
// match: ??_C@_0O@FMGHIGIB@Game?5Settings?$AA@ @ 0x003DE644
// match: ??_C@_0BE@LMBJBIMK@Disable?3?5ADL?5Clones?$AA@ @ 0x003DE654
// match: ??_C@_0BH@HNPLNFPC@Disable?3?5Prelit?5Clones?$AA@ @ 0x003DE668
// match: ??_C@_0BH@NDALMDAC@Disable?3?5RAM?5Particles?$AA@ @ 0x003DE680
// match: ??_C@_0BE@CDBKNKON@Disable?3?5New?5Clones?$AA@ @ 0x003DE698
// match: ??_C@_0BK@EIHDGJOP@Lights?3?5Scale?5Directional?$AA@ @ 0x003DE6AC
// match: ??_C@_0BG@BKGJMEMN@Lights?3?5Scale?5Ambient?$AA@ @ 0x003DE6C8
// match: ??_C@_0BB@EPEHIFHM@Disable?3?5Sky?5Box?$AA@ @ 0x003DE6E0
// match: ??_C@_0BH@KLJMOHLD@Disable?3?5Texture?5Anims?$AA@ @ 0x003DE6F4
// match: ??_C@_0BF@NPAHAALK@Disable?3?5World?5Extra?$AA@ @ 0x003DE70C
// match: ??_C@_0BF@EPCFMCBP@Disable?3?5World?5Alpha?$AA@ @ 0x003DE724
// match: ??_C@_0BG@NKFIKDOD@Disable?3?5World?5Opaque?$AA@ @ 0x003DE73C
// match: ??_C@_0BD@NHFPBFLP@Disable?3?5Particles?$AA@ @ 0x003DE754
// match: ??_C@_0BA@PDGMDLMP@Disable?3?5Clones?$AA@ @ 0x003DE768
// match: ??_C@_0BB@ENFENHPE@Disable?3?5Shrimps?$AA@ @ 0x003DE778
// match: ??_C@_0P@OPBOJJNE@Disable?3?5Gimps?$AA@ @ 0x003DE78C
// match: ??_C@_0BO@DEIPNFAA@Disable?3?5DefaultClumpRenderer?$AA@ @ 0x003DE79C
// match: ??_C@_0BD@OMJLGLFJ@Renderer?5Switching?$AA@ @ 0x003DE7BC
// match: __real@3ba3d70a @ 0x003DE7D0
// match: __real@437b53d1 @ 0x003DE7D4
// match: __real@401921fa00000000 @ 0x003DE7D8
// match: ??_C@_05NAHKBEAK@?$CF1?43f?$AA@ @ 0x003DE7E0
// match: ??_C@_02NJPGOMH@?$CFf?$AA@ @ 0x003DE7E8
// match: ??_C@_05BJFIPBEN@?$CF4?42f?$AA@ @ 0x003DE7EC
// match: ??_C@_01JOAMLHOP@?9?$AA@ @ 0x003DE7F4
// match: ??_C@_08FGBCKBPP@SELECTED?$AA@ @ 0x003DE7F8
// match: ??_C@_03MPPIHBHJ@OFF?$AA@ @ 0x003DE804
// match: ??_C@_02BFICIOJL@ON?$AA@ @ 0x003DE808
// match: ??_C@_02HBOOOICD@?9?$DO?$AA@ @ 0x003DE80C
// match: ??_C@_05DNIIFBMG@?$CFs?5?$CFs?$AA@ @ 0x003DE810
// match: ??_C@_01PPODPGHN@?$DO?$AA@ @ 0x003DE818
// match: ??_C@_0N@OHBBDAEL@?9?9?9?9?5?$CFs?5?9?9?9?9?$AA@ @ 0x003DE81C
// match: ??_C@_0L@NABEIFP@Empty?5Menu?$AA@ @ 0x003DE82C
// match: .CRT$XCU+0 @ 0x00427170
// match: ?off_42A4D4@@3Utype_4E73A8_14@@A @ 0x0042A4D4
// match: ?unk_42A4E8@@3HA @ 0x0042A4E8
// match: ?unk_42A4EC@@3MA @ 0x0042A4EC

// match: _$E2 @ 0x0030BF80

// The variables the menu shows (defined elsewhere).
extern RwInt32 dword_4B69EC;
extern RwInt32 dword_4E6F24;
extern RwInt32 dword_4E7240;
extern RwInt32 dword_4CF31C;
extern RwInt32 dword_4BFD40;
extern RwInt32 dword_4CF434;
extern RwInt32 dword_4CF438;
extern RwInt32 dword_4CF43C;
extern RwInt32 dword_4CFE24;
extern RwInt32 dword_4CF440;
extern RwInt32 dword_4CF330;
extern RwInt32 unk_42C7B0;
extern RwInt32 dword_4CF324;
extern RwInt32 dword_4CF328;
extern RwReal flt_429298;
extern RwInt32 dword_4C19AC;
extern RwInt32 unk_42A4E8;
extern RwReal unk_42A4EC;
extern RwInt32 unk_4E739C;
extern RwInt32 unk_4E73A0;

// match: ?sub_183130@type_4E73A8@@QAEXXZ @ 0x00183130
// sp-match: ?sub_183130@type_4E73A8@@QAEXXZ @ 0x0011A700
// Builds the menu: its root, the second menu (dword_4E73F0), and the
// renderer switches, the game speed, unlimited ammunition and the debug
// switches.
void type_4E73A8::sub_183130()
{
    type_4E73A8_14 *var_4;

    unk_14 = 0;
    unk_08 = &off_42A4D4;
    unk_0C = &off_42A4D4;
    unk_10 = 0;
    dword_4E73F0.sub_184CF0();
    var_4 = sub_183440(0, "Renderer Switching");
    sub_183610(var_4, "Disable: DefaultClumpRenderer", &dword_4B69EC, 2);
    sub_183610(var_4, "Disable: Gimps", &dword_4E6F24, 2);
    sub_183610(var_4, "Disable: Shrimps", &dword_4E7240, 2);
    sub_183610(var_4, "Disable: Clones", &dword_4CF31C, 2);
    sub_183610(var_4, "Disable: Particles", &dword_4BFD40, 2);
    sub_183610(var_4, "Disable: World Opaque", &dword_4CF434, 2);
    sub_183610(var_4, "Disable: World Alpha", &dword_4CF438, 2);
    sub_183610(var_4, "Disable: World Extra", &dword_4CF43C, 2);
    sub_183610(var_4, "Disable: Texture Anims", &dword_4CFE24, 2);
    sub_183610(var_4, "Disable: Sky Box", &dword_4CF440, 2);
    sub_183610(var_4, "Lights: Scale Ambient", &dword_4F30A8.unk_00, 7);
    sub_183610(var_4, "Lights: Scale Directional", &dword_4F30A8.unk_04, 7);
    sub_183610(var_4, "Disable: New Clones", &dword_4CF330, 2);
    sub_183610(var_4, "Disable: RAM Particles", &unk_42C7B0, 2);
    sub_183610(var_4, "Disable: Prelit Clones", &dword_4CF324, 2);
    sub_183610(var_4, "Disable: ADL Clones", &dword_4CF328, 2);
    var_4 = sub_183440(0, "Game Settings");
    sub_183610(var_4, "Game Speed", &flt_429298, 7);
    var_4 = sub_183440(0, "Cheats");
    sub_183610(var_4, "Unlimited Ammo", &dword_4C19AC, 2);
    var_4 = sub_183440(0, "Debug Switches");
    sub_183610(var_4, "int g_debugSwitch", &unk_42A4E8, 2);
    sub_183610(var_4, "int g_debugFloat", &unk_42A4EC, 7);
    sub_183610(var_4, "int g_debugInt0", &unk_4E739C, 1);
    sub_183610(var_4, "int g_debugInt1", &unk_4E73A0, 1);
}

// match: ?sub_1833D0@type_4E73A8@@QAEXXZ @ 0x001833D0
// sp-match: ?sub_1833D0@type_4E73A8@@QAEXXZ @ 0x0011A480
// Frees the menu (the second menu first), leaving its root empty.
void type_4E73A8::sub_1833D0()
{
    dword_4E73F0.sub_184E40();
    if (!unk_08)
        return;
    sub_183640(unk_08);
    unk_08->unk_08 = 0;
    unk_08->unk_0C = 0;
    unk_08->unk_04 = 0;
    unk_08->unk_10 = 0;
    unk_18 = 0;
}

// match: ?sub_183440@type_4E73A8@@QAEPAUtype_4E73A8_14@@PAU2@PBD@Z @ 0x00183440
// sp-match: ?sub_183440@type_4E73A8@@QAEPAUtype_4E73A8_14@@PAU2@PBD@Z @ 0x00119BB0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
type_4E73A8_14 *type_4E73A8::sub_183440(type_4E73A8_14 *arg_0, const RwChar *arg_4)
{
    type_4E73A8_18 *var_C;
    type_4E73A8_14 *bp_8;
    type_4E73A8_18 *bp_4;

    if (!arg_0)
        arg_0 = unk_08;
    var_C = (type_4E73A8_18 *)RwMalloc(0x18, 0x3425C); // not an address: a memory hint
    unk_18 += 0x18;
    bp_8 = (type_4E73A8_14 *)RwMalloc(0x14, 0x3425C); // not an address: a memory hint
    unk_18 += 0x14;
    var_C->unk_00_b = 0;
    var_C->unk_04 = (RwChar *)RwMalloc(strlen(arg_4) + 1, 0x3425C); // not an address: a memory hint
    unk_18 += strlen(arg_4) + 1;
    strcpy(var_C->unk_04, arg_4);
    var_C->unk_0C = bp_8;
    var_C->unk_10 = 0;
    var_C->unk_14 = 0;
    var_C->unk_08 = 0;
    bp_8->unk_00 = (RwChar *)RwMalloc(strlen(arg_4) + 1, 0x3425C); // not an address: a memory hint
    unk_18 += strlen(arg_4) + 1;
    strcpy(bp_8->unk_00, arg_4);
    bp_8->unk_04 = 0;
    bp_8->unk_08 = 0;
    bp_8->unk_10 = arg_0;
    arg_0->unk_04++;
    if (arg_0->unk_08)
    {
        bp_4 = arg_0->unk_08;
        while (bp_4->unk_10)
            bp_4 = bp_4->unk_10;
        bp_4->unk_10 = var_C;
        var_C->unk_14 = bp_4;
    }
    else
    {
        arg_0->unk_08 = var_C;
        var_C->unk_14 = 0;
    }
    arg_0->unk_0C = var_C;
    unk_10 = unk_0C->unk_08;
    return bp_8;
}

// match: ?sub_183610@type_4E73A8@@QAEPAUtype_4E73A8_18@@PAUtype_4E73A8_14@@PBDPAXH@Z @ 0x00183610
// sp-match: ?sub_183610@type_4E73A8@@QAEPAUtype_4E73A8_18@@PAUtype_4E73A8_14@@PBDPAXH@Z @ 0x0011A4C0
type_4E73A8_18 *type_4E73A8::sub_183610(type_4E73A8_14 *arg_0, const RwChar *arg_4, void *arg_8, RwInt32 arg_C)
{
    return sub_183700(arg_0, arg_4, arg_8, arg_C, 0);
}

// match: ?sub_183640@type_4E73A8@@QAEXPAUtype_4E73A8_14@@@Z @ 0x00183640
// sp-match: ?sub_183640@type_4E73A8@@QAEXPAUtype_4E73A8_14@@@Z @ 0x00119CF0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_4E73A8::sub_183640(type_4E73A8_14 *arg_0)
{
    type_4E73A8_18 *var_C;
    type_4E73A8_18 *bp_8;
    RwInt32 bp_4;

    for (bp_4 = 0, var_C = arg_0->unk_08; bp_4 < arg_0->unk_04; bp_4++, var_C = bp_8)
    {
        if (!var_C->unk_00_b)
            sub_183640((type_4E73A8_14 *)var_C->unk_0C);
        if (var_C->unk_04)
            RwFree(var_C->unk_04);
        bp_8 = var_C->unk_10;
        RwFree(var_C);
    }
    if (arg_0 != unk_08)
    {
        if (arg_0->unk_00)
            RwFree(arg_0->unk_00);
        RwFree(arg_0);
    }
}

// match: ?sub_183700@type_4E73A8@@QAEPAUtype_4E73A8_18@@PAUtype_4E73A8_14@@PBDPAXHH@Z @ 0x00183700
// sp-match: ?sub_183700@type_4E73A8@@QAEPAUtype_4E73A8_18@@PAUtype_4E73A8_14@@PBDPAXHH@Z @ 0x00119D80
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
type_4E73A8_18 *type_4E73A8::sub_183700(type_4E73A8_14 *arg_0, const RwChar *arg_4, void *arg_8, RwInt32 arg_C,
                                        RwInt32 arg_10)
{
    type_4E73A8_18 *var_8;
    type_4E73A8_18 *l4;

    if (!arg_0)
        arg_0 = unk_08;
    var_8 = (type_4E73A8_18 *)RwMalloc(0x18, 0x3425C); // not an address: a memory hint
    unk_18 += 0x18;
    var_8->unk_00_b = arg_C;
    var_8->unk_04 = (RwChar *)RwMalloc(strlen(arg_4) + 1, 0x3425C); // not an address: a memory hint
    unk_18 += strlen(arg_4) + 1;
    strcpy(var_8->unk_04, arg_4);
    var_8->unk_0C = arg_8;
    var_8->unk_10 = 0;
    var_8->unk_08 = arg_10;
    arg_0->unk_04++;
    if (arg_0->unk_08)
    {
        l4 = arg_0->unk_08;
        while (l4->unk_10)
            l4 = l4->unk_10;
        l4->unk_10 = var_8;
        var_8->unk_14 = l4;
    }
    else
    {
        arg_0->unk_08 = var_8;
        var_8->unk_14 = 0;
    }
    arg_0->unk_0C = var_8;
    unk_10 = unk_0C->unk_08;
    return var_8;
}

// x modulo two pi as the draw takes it: an inline with no address, named
// for what it gives. Evidence: sub_184100 keeps its result in a temporary of
// its own before storing it, with the divisor as a double.
inline RwReal fmod2pi_(RwReal x)
{
    return ((RwReal)fmod((RwDouble)x, (RwDouble)6.28318f));
}

// An angle in radians wrapped into [-pi, pi) (80 pi added first); a macro
// with no address: sub_183840 calls fmod for the test and again for the
// value, keeping each result in a temporary of its own.
#define WRAP_ANGLE(x)                                                                          \
    (((RwReal)fmod((RwDouble)((x) + 251.32741f), (RwDouble)6.28318f) < 3.14159f)               \
         ? ((RwReal)fmod((RwDouble)((x) + 251.32741f), (RwDouble)6.28318f))                     \
         : ((RwReal)fmod((RwDouble)((x) + 251.32741f), (RwDouble)6.28318f) - 6.28318f))

// match: ?sub_183840@type_4E73A8@@QAEXXZ @ 0x00183840
// sp-match: ?sub_183840@type_4E73A8@@QAEXXZ @ 0x00119E70
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Its step while open (unk_14), from the pad once past frame 60: up and
// down move through the group (wrapping), left and right change the item
// (by its kind: an integer or byte by one, a float by its kind's step, an
// angle in radians or degrees wrapped, a colour channel or fraction
// clamped; a switch, a flag or a group taken on the press, which also zeroes
// most values; kind 15 calls its function), and back leaves the group or
// closes the menu. Items flagged 0x4000 cannot be changed.
void type_4E73A8::sub_183840()
{
    void (*bp_8)();
    RwReal ebp_34;
    RwReal var_30;
    RwReal var_2C;
    RwReal loc28;
    RwReal slot_24;
    RwInt32 v20;
    RwReal loc1C;
    RwReal bp_18;
    RwInt32 var14;
    RwInt32 r10;
    RwReal locC;
    RwInt32 bp_4;

    if (dword_4B87D8 < 60)
        return;
    locC = 0;
    bp_4 = (RwInt32)unk_4B9308.sub_EE8F0(0, 0xF);
#ifdef CODFH_SP
    // single player numbers this input 0x27 (SP 0x119E95)
    r10 = (RwInt32)unk_4B9308.sub_EE8F0(0, 0x27);
#else
    r10 = (RwInt32)unk_4B9308.sub_EE8F0(0, 0x2B);
#endif
    if (unk_14)
    {
        bp_18 = 0.9f;
        loc1C = unk_4B9308.sub_EE8F0(0, 0x1F);
        var_2C = unk_4B9308.sub_EE8F0(0, 0x20);
        loc28 = unk_4B9308.sub_EE8F0(0, 0x13);
        slot_24 = unk_4B9308.sub_EE8F0(0, 0x14);
        v20 = (RwInt32)unk_4B9308.sub_EE8F0(0, 0x1B);
        if (loc28 < bp_18)
            loc28 = 0;
        if (slot_24 < bp_18)
            slot_24 = 0;
        if (unk_10)
        {
            if (loc28 != 0.0f)
                unk_10 = unk_10->unk_14 ? unk_10->unk_14 : unk_0C->unk_0C;
            if (slot_24 != 0.0f)
                unk_10 = unk_10->unk_10 ? unk_10->unk_10 : unk_0C->unk_08;
            if (unk_10->unk_00 & 0x8000)
            {
                if (loc1C != 0.0f)
                    locC = -1.0f;
                else if (var_2C != 0.0f)
                    locC = 1.0f;
                else
                    locC = 0;
            }
            else
            {
                if (loc1C != 0.0f)
                    locC = -1.0f;
                else if (var_2C != 0.0f)
                    locC = 1.0f;
                else
                    locC = 0;
            }
            var14 = (RwInt32)locC;
            if (!(unk_10->unk_00 & 0x4000))
            {
                switch (unk_10->unk_00 & ~0xC000)
                {
                case 0:
                    if (r10)
                    {
                        unk_0C = (type_4E73A8_14 *)unk_10->unk_0C;
                        unk_10 = unk_0C->unk_08;
                    }
                    break;
                case 2:
                    if (r10)
                        *(RwInt32 *)unk_10->unk_0C ^= 1;
                    break;
                case 13:
                    if (r10)
                        *(RwInt32 *)unk_10->unk_0C = 1;
                    break;
                case 11:
                    var_30 = *(RwReal *)unk_10->unk_0C;
                    var_30 += locC * 3.14159f * 2.0f / 360.0f;
                    var_30 = WRAP_ANGLE(var_30);
                    if (r10)
                        var_30 = 0;
                    *(RwReal *)unk_10->unk_0C = var_30;
                    break;
                case 12:
                    ebp_34 = *(RwReal *)unk_10->unk_0C;
#ifdef CODFH_SP
                    // shape: the degree conversions in two steps each, so /O2 keeps
                    // two multiplies (SP 0x11A099, 0x11A0E3)
                    ebp_34 = ebp_34 * 3.14159f * 2.0f;
                    ebp_34 /= 360.0f;
                    ebp_34 += locC * 3.14159f * 2.0f / 360.0f;
                    ebp_34 = WRAP_ANGLE(ebp_34);
                    if (r10)
                        ebp_34 = 0;
                    ebp_34 = 360.0f * ebp_34;
                    ebp_34 /= 6.28318f;
#else
                    ebp_34 = ebp_34 * 3.14159f * 2.0f / 360.0f;
                    ebp_34 += locC * 3.14159f * 2.0f / 360.0f;
                    ebp_34 = WRAP_ANGLE(ebp_34);
                    if (r10)
                        ebp_34 = 0;
                    ebp_34 = 360.0f * ebp_34 / 6.28318f;
#endif
                    *(RwReal *)unk_10->unk_0C = ebp_34;
                    break;
                case 10:
                    *(RwReal *)unk_10->unk_0C += locC;
                    if (*(RwReal *)unk_10->unk_0C < 0.0f)
                        *(RwReal *)unk_10->unk_0C = 0;
                    if (*(RwReal *)unk_10->unk_0C > 255.0f)
                        *(RwReal *)unk_10->unk_0C = 255.0f;
                    if (r10)
                        *(RwReal *)unk_10->unk_0C = 0;
                    break;
                case 3:
                    *(RwReal *)unk_10->unk_0C += locC;
                    if (r10)
                        *(RwReal *)unk_10->unk_0C = 0;
                    break;
                case 4:
                    *(RwReal *)unk_10->unk_0C += locC * 5.0f;
                    break;
                case 5:
                    *(RwReal *)unk_10->unk_0C += locC * 1000.0f;
                    break;
                case 14:
                    *unk_10->unk_0C_b += var14;
                    break;
                case 6:
                    *(RwReal *)unk_10->unk_0C += locC * 0.05f;
                    if (r10)
                        *(RwReal *)unk_10->unk_0C = 0;
                    break;
                case 7:
                    *(RwReal *)unk_10->unk_0C += locC * 0.005f;
                    if (r10)
                        *(RwReal *)unk_10->unk_0C = 0;
                    break;
                case 8:
                    *(RwReal *)unk_10->unk_0C += locC * 0.0001f;
                    if (r10)
                        *(RwReal *)unk_10->unk_0C = 0;
                    break;
                case 9:
                    *(RwReal *)unk_10->unk_0C += locC * 0.005f;
                    if (*(RwReal *)unk_10->unk_0C < 0.0f)
                        *(RwReal *)unk_10->unk_0C = 0;
                    if (*(RwReal *)unk_10->unk_0C > 1.0f)
                        *(RwReal *)unk_10->unk_0C = 1.0f;
                    if (r10)
                        *(RwReal *)unk_10->unk_0C = 0;
                    break;
                case 1:
                    *(RwInt32 *)unk_10->unk_0C += var14;
                    if (r10)
                        *(RwInt32 *)unk_10->unk_0C = 0;
                    break;
                case 15:
                    bp_8 = (void (*)())unk_10->unk_0C;
                    if (r10)
                        bp_8();
                    break;
                }
            }
        }
        if (v20)
        {
            if (unk_0C->unk_10)
            {
                unk_0C = unk_0C->unk_10;
                unk_10 = unk_0C->unk_08;
            }
            else
                unk_14 = 0;
        }
    }
}

// match: ?sub_183FD0@type_4E73A8@@QAEHXZ @ 0x00183FD0
// sp-match: ?sub_183FD0@type_4E73A8@@QAEHXZ @ 0x0011A4E0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_4E73A8::sub_183FD0()
{
    type_DA580 *var_8;
    RwRGBA l4;

    unk_20 = (RwCamera *)dword_4E5CBC;
    if (!unk_20)
        return 0;
    RwCameraBeginUpdate(unk_20);
    sub_184760();
    l4.alpha = l4.red = l4.green = l4.blue = 255;
    unk_1C = Rt2dBrushCreate();
    Rt2dBrushSetRGBA(unk_1C, &l4, &l4, &l4, &l4);
    var_8 = dword_4B9190->unk_1A028;
    unk_04 = var_8;
    Rt2dCTMPush();
    Rt2dCTMSetIdentity();
    Rt2dCTMScale(1.0f / (RwUInt32)Height, 1.0f / (RwUInt32)Height);
    return 1;
}

// match: ?sub_1840C0@type_4E73A8@@QAEXXZ @ 0x001840C0
// sp-match: ?sub_1840C0@type_4E73A8@@QAEXXZ @ 0x0011A590
void type_4E73A8::sub_1840C0()
{
    Rt2dCTMPop();
    Rt2dBrushDestroy(unk_1C);
    sub_184870();
    RwCameraEndUpdate(unk_20);
}

// match: ?sub_184100@type_4E73A8@@QAEXPAURwCamera@@@Z @ 0x00184100
// sp-match: ?sub_184100@type_4E73A8@@QAEXPAURwCamera@@@Z @ 0x0011A980
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Draws the second menu and, while open, this one: its group's name, then
// each item (">" marks the selected one) with its value by kind (a group
// "->", a switch ON or OFF, a flag SELECTED, an angle in degrees within
// +-180, floats and integers).
void type_4E73A8::sub_184100(RwCamera *arg_0)
{
    type_4E73A8_18 *var_1BC;
    RwChar var_1B8[0xD0];
    RwChar vE8[4];
    RwReal m_E4;
    RwChar m_E0[0xD0];
    RwInt32 x8;
    RwInt32 l4;

    if (!sub_183FD0())
        return;
    dword_4E73F0.sub_184F90();
    dword_4E73F0.sub_1851C0(arg_0);
    sub_19A750();
    if (unk_14)
    {
        x8 = 30;
        l4 = Height - 40;
        if (!unk_10)
        {
            sub_184C50("Empty Menu", x8, l4);
            return;
        }
        if (unk_10->unk_08)
            sub_184910(unk_10->unk_08_s);
        sprintf(m_E0, "---- %s ----", unk_0C->unk_00);
        sub_184C50(m_E0, x8, l4);
        l4 -= 15;
        var_1BC = unk_0C->unk_08;
        while (var_1BC)
        {
            if (var_1BC == unk_10)
                strcpy(vE8, ">");
            else
                strcpy(vE8, " ");
            switch (var_1BC->unk_00 & ~0xC000)
            {
            case 0:
                sprintf(m_E0, "%s %s", vE8, var_1BC->unk_04);
                sprintf(var_1B8, "->");
                break;
            case 2:
                sprintf(m_E0, "%s %s", vE8, var_1BC->unk_04);
                sprintf(var_1B8, "%s", *(RwInt32 *)var_1BC->unk_0C ? "ON" : "OFF");
                break;
            case 13:
                sprintf(m_E0, "%s %s", vE8, var_1BC->unk_04);
                sprintf(var_1B8, "%s", *(RwInt32 *)var_1BC->unk_0C ? "SELECTED" : "-");
                break;
            case 11:
                sprintf(m_E0, "%s %s", vE8, var_1BC->unk_04);
                m_E4 = *(RwReal *)var_1BC->unk_0C;
                m_E4 = fmod2pi_(m_E4 + 251.32741f);
#ifdef CODFH_SP
                // shape: the conversion to degrees in two steps (SP 0x11AB78)
                m_E4 = 360.0f * m_E4;
                m_E4 /= 6.28318f;
#else
                m_E4 = 360.0f * m_E4 / 6.28318f;
#endif
                if (m_E4 > 180.0f)
                    m_E4 -= 360.0f;
                sprintf(var_1B8, "%4.2f", m_E4);
                break;
            case 12:
                sprintf(m_E0, "%s %s", vE8, var_1BC->unk_04);
                m_E4 = *(RwReal *)var_1BC->unk_0C;
#ifdef CODFH_SP
                // shape: the degree conversions in two steps each (SP 0x11ABD4, 0x11ABF1)
                m_E4 = m_E4 * 3.14159f * 2.0f;
                m_E4 /= 360.0f;
                m_E4 = fmod2pi_(m_E4 + 251.32741f);
                m_E4 = 360.0f * m_E4;
                m_E4 /= 6.28318f;
#else
                m_E4 = m_E4 * 3.14159f * 2.0f / 360.0f;
                m_E4 = fmod2pi_(m_E4 + 251.32741f);
                m_E4 = 360.0f * m_E4 / 6.28318f;
#endif
                if (m_E4 > 180.0f)
                    m_E4 -= 360.0f;
                sprintf(var_1B8, "%4.2f", m_E4);
                break;
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 10:
                sprintf(m_E0, "%s %s", vE8, var_1BC->unk_04);
                sprintf(var_1B8, "%f", *(RwReal *)var_1BC->unk_0C);
                break;
            case 9:
                sprintf(m_E0, "%s %s", vE8, var_1BC->unk_04);
                sprintf(var_1B8, "%1.3f", *(RwReal *)var_1BC->unk_0C);
                break;
            case 1:
                sprintf(m_E0, "%s %s", vE8, var_1BC->unk_04);
                sprintf(var_1B8, "%d", *(RwInt32 *)var_1BC->unk_0C);
                break;
            case 14:
                sprintf(m_E0, "%s %s", vE8, var_1BC->unk_04);
                sprintf(var_1B8, "%d", *var_1BC->unk_0C_b);
                break;
            case 15:
                sprintf(m_E0, "%s %s", vE8, var_1BC->unk_04);
                var_1B8[0] = 0;
                break;
            }
            sub_184C50(m_E0, x8, l4);
            if (var_1B8[0])
                sub_184C50(var_1B8, x8 + 270, l4);
            l4 -= 15;
            var_1BC = var_1BC->unk_10;
        }
    }
    sub_1840C0();
}

// match: ?sub_184760@type_4E73A8@@QAEXXZ @ 0x00184760
// sp-match: ?sub_184760@type_4E73A8@@QAEXXZ @ 0x0011A2E0
// Keeps the render states it draws with, then sets them: no texture, no
// depth test or write, no culling, vertex alpha, fog or blending.
void type_4E73A8::sub_184760()
{
    RwRenderStateGet(rwRENDERSTATETEXTURERASTER, &unk_24);
    RwRenderStateGet(rwRENDERSTATEZWRITEENABLE, &unk_28);
    RwRenderStateGet(rwRENDERSTATEZTESTENABLE, &unk_2C);
    RwRenderStateGet(rwRENDERSTATECULLMODE, &unk_30);
    RwRenderStateGet(rwRENDERSTATEVERTEXALPHAENABLE, &unk_34);
    RwRenderStateGet(rwRENDERSTATEFOGENABLE, &unk_38);
    RwRenderStateGet(rwRENDERSTATESRCBLEND, &unk_3C);
    RwRenderStateGet(rwRENDERSTATEDESTBLEND, &unk_40);
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void *)0);
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void *)0);
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void *)0);
    RwRenderStateSet(rwRENDERSTATECULLMODE, (void *)rwCULLMODECULLNONE);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)0);
    RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void *)0);
    RwRenderStateSet(rwRENDERSTATESRCBLEND, (void *)rwBLENDONE);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void *)1); // rwBLENDZERO
}

// match: ?sub_184870@type_4E73A8@@QAEXXZ @ 0x00184870
// sp-match: ?sub_184870@type_4E73A8@@QAEXXZ @ 0x0011A3A0
// Puts the render states back.
void type_4E73A8::sub_184870()
{
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void *)unk_24);
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void *)unk_28);
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void *)unk_2C);
    RwRenderStateSet(rwRENDERSTATECULLMODE, (void *)unk_30);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)unk_34);
    RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void *)unk_38);
    RwRenderStateSet(rwRENDERSTATESRCBLEND, (void *)unk_3C);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void *)unk_40);
}

// match: ?sub_184910@type_4E73A8@@QAEXPBD@Z @ 0x00184910
// sp-match: ?sub_184910@type_4E73A8@@QAEXPBD@Z @ 0x0011A920
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Measures the help text arg_0, then draws it from (0x300, 0x600) within
// the screen's width less 96.
void type_4E73A8::sub_184910(const RwChar *arg_0)
{
    RwInt32 var_24;
    RwInt32 var_20;
    RwInt32 l1C;
    RwInt32 m_18;
    RwInt32 ebp_14;
    RwInt32 lv_10;
    RwInt32 var_C;
    RwInt32 bp_8;
    RwInt32 bp_4;

    m_18 = Width;
    lv_10 = 0x300;
    var_C = 0x600;
    var_24 = lv_10;
    ebp_14 = var_C;
    sub_1849C0(arg_0, 0, &var_20, &l1C, m_18 - 96);
    var_24 <<= 4;
    ebp_14 <<= 4;
    bp_8 = (var_20 << 4) + var_24;
    bp_4 = (l1C << 4) + ebp_14;
    var_20 = var_24 >> 4;
    l1C = ebp_14 >> 4;
    sub_1849C0(arg_0, 1, &var_20, &l1C, m_18 - 96);
}

// match: ?sub_1849C0@type_4E73A8@@QAEXPBDHPAH1H@Z @ 0x001849C0
// sp-match: ?sub_1849C0@type_4E73A8@@QAEXPBDHPAH1H@Z @ 0x0011A5C0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Wraps the text arg_0 at newlines and within arg_10 (15 units a
// character), each line 15 below the last: drawn from (*arg_8, *arg_C)
// when arg_4 is set, else its width and (negative) height into them.
void type_4E73A8::sub_1849C0(const RwChar *arg_0, RwInt32 arg_4, RwInt32 *arg_8, RwInt32 *arg_C, RwInt32 arg_10)
{
    RwChar var_219;
    RwChar *v218;
    RwInt32 v214;
    RwInt32 var_210;
    const RwChar *var_20C;
    RwChar loc208[0x200];
    RwInt32 l4;

    l4 = 0;
    v214 = 0;
    var_210 = 0;
    var_20C = arg_0;
    v218 = loc208;
    while (var_219 = *var_20C++)
    {
        if (var_219 == '\n')
        {
            *v218 = 0;
            var_210 -= 15;
            if (l4 > v214)
                v214 = l4;
            l4 = 0;
            if (arg_4 && v218 != loc208)
                sub_184C50(loc208, *arg_8 << 4, (*arg_C + var_210 + 15) << 4);
            v218 = loc208;
        }
        else
        {
            *v218 = var_219;
            v218++;
            l4 += 15;
            if (l4 > arg_10 && *var_20C != '\n' && *var_20C)
            {
                *v218 = 0;
                l4 -= 15;
                var_210 -= 15;
                if (l4 > v214)
                    v214 = l4;
                l4 = 0;
                if (arg_4 && v218 != loc208)
                    sub_184C50(loc208, *arg_8 << 4, (*arg_C + var_210 + 15) << 4);
                v218 = loc208;
            }
        }
    }
    if (v218 != loc208)
    {
        var_210 -= 15;
        if (l4 > v214)
            v214 = l4;
        if (arg_4)
        {
            *v218 = 0;
            sub_184C50(loc208, *arg_8 << 4, (*arg_C + var_210 + 15) << 4);
        }
    }
    if (!arg_4)
    {
        *arg_8 = v214;
        *arg_C = var_210;
    }
}

// match: ?sub_184C50@type_4E73A8@@QAEXPBDHH@Z @ 0x00184C50
// sp-match: ?sub_184C50@type_4E73A8@@QAEXPBDHH@Z @ 0x0011A410
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_4E73A8::sub_184C50(const RwChar *arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    RwV2d var_C;
    RwRGBA bp_4;

    if (!unk_04)
        return;
    var_C.x = (RwReal)arg_4;
    var_C.y = (RwReal)arg_8;
    bp_4.red = unk_02;
    bp_4.green = unk_01;
    bp_4.blue = unk_00;
    bp_4.alpha = unk_03;
    unk_04->sub_DAB00(arg_0, &var_C, &bp_4, 0, 0);
}

// match: ?sub_184CC0@type_4E73A8@@QAEXXZ @ 0x00184CC0
// sp-match: ?sub_184CC0@type_4E73A8@@QAEXXZ @ 0x0011A470
// Its text colour (yellow): the dynamic initializer (0x30BF80) calls it.
void type_4E73A8::sub_184CC0()
{
    unk_02 = 255;
    unk_01 = 255;
    unk_00 = 0;
    unk_03 = 255;
}
