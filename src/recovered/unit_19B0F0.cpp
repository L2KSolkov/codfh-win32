// Level tables, the assert trap, the light scales, and full-screen drawing
// helpers.

#include <xtl.h>
#include <stdio.h>
#include <string.h>

#include "rw/ostypes.h"
#include "types/vec4.h"
#include "game/levels.h"
#include "game/clones.h"
#include "rw/rwxbox.h"
#include "rw/badevice.h"
#include "rw/baengine.h"
#include "game/functions.h"
#include "game/render.h"
#include "game/gameloop.h"
#include "game/savestate.h"
#include "game/padlib.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003E017C
extern const RwReal flt_3E017C = 16.666666f;
// 0x0042B740
type_42B740 dword_42B740[23] = {
    { 4, 1, 11, -1, -1, -1, -1, 0 },
    { 12, 2, 16, 25, -1, -1, -1, 0 },
    { 13, 3, 9, 4, 39, -1, -1, 0 },
    { 11, 2, 24, 10, -1, -1, -1, 0 },
    { 0, 3, 40, 19, 33, -1, -1, 0 },
    { 1, 2, 20, 34, -1, -1, -1, 0 },
    { 2, 4, 13, 21, 31, 29, -1, 0 },
    { 3, 4, 14, 22, 32, 30, -1, 0 },
    { 16, 1, 6, -1, -1, -1, -1, 0 },
    { 15, 2, 7, 27, -1, -1, -1, 0 },
    { 7, 1, 18, -1, -1, -1, -1, 0 },
    { 17, 1, 3, -1, -1, -1, -1, 0 },
    { 14, 1, 15, -1, -1, -1, -1, 0 },
    { 6, 1, 42, -1, -1, -1, -1, 0 },
    { 22, 1, 2, -1, -1, -1, -1, 0 },
    { 23, 1, 0, -1, -1, -1, -1, 0 },
    { 24, 1, 1, -1, -1, -1, -1, 0 },
    { 25, 1, 5, -1, -1, -1, -1, 0 },
    { 5, 2, 17, 38, -1, -1, -1, 0 },
    { 10, 4, 12, 23, 37, 43, -1, 0 },
    { 20, 1, 35, -1, -1, -1, -1, 0 },
    { 21, 1, 36, -1, -1, -1, -1, 0 },
    { -1, 1, -1, -1, -1, -1, -1, 0 },
};
// 0x0042BA20
type_42B740 dword_42BA20[23] = {
    { 4, 1, 11, -1, -1, -1, -1, 0 },
    { 12, 3, 14, 25, 29, -1, -1, 0 },
    { 13, 2, 40, 39, -1, -1, -1, 0 },
    { 11, 3, 13, 24, 30, -1, -1, 0 },
    { 0, 4, 9, 4, 19, 33, -1, 0 },
    { 1, 3, 10, 20, 34, -1, -1, 0 },
    { 2, 3, 7, 21, 31, -1, -1, 0 },
    { 3, 2, 22, 32, -1, -1, -1, 0 },
    { 16, 1, 3, -1, -1, -1, -1, 0 },
    { 15, 2, 16, 27, -1, -1, -1, 0 },
    { 7, 2, 12, 42, -1, -1, -1, 0 },
    { 17, 1, 6, -1, -1, -1, -1, 0 },
    { 14, 1, -1, -1, -1, -1, -1, 0 },
    { 6, 1, 18, -1, -1, -1, -1, 0 },
    { 24, 1, 2, -1, -1, -1, -1, 0 },
    { 25, 1, 0, -1, -1, -1, -1, 0 },
    { 22, 1, 1, -1, -1, -1, -1, 0 },
    { 23, 1, 5, -1, -1, -1, -1, 0 },
    { 5, 2, 17, 38, -1, -1, -1, 0 },
    { 10, 4, 15, 23, 37, 43, -1, 0 },
    { 20, 1, 35, -1, -1, -1, -1, 0 },
    { 21, 1, 36, -1, -1, -1, -1, 0 },
    { -1, 1, -1, -1, -1, -1, -1, 0 },
};
// 0x0042BD00
type_42B740 dword_42BD00[23] = {
    { 4, 1, 11, -1, -1, -1, -1, 0 },
    { 12, 2, 7, 25, -1, -1, -1, 0 },
    { 13, 3, 9, 4, 39, -1, -1, 0 },
    { 11, 2, 10, 24, -1, -1, -1, 0 },
    { 0, 2, 19, 33, -1, -1, -1, 0 },
    { 1, 2, 20, 34, -1, -1, -1, 0 },
    { 2, 4, 14, 21, 31, 29, -1, 0 },
    { 3, 4, 13, 22, 32, 30, -1, 0 },
    { 16, 1, 3, -1, -1, -1, -1, 0 },
    { 15, 2, 40, 27, -1, -1, -1, 0 },
    { 7, 1, 18, -1, -1, -1, -1, 0 },
    { 17, 1, 6, -1, -1, -1, -1, 0 },
    { 14, 1, 16, -1, -1, -1, -1, 0 },
    { 6, 2, 12, 42, -1, -1, -1, 0 },
    { 24, 1, 2, -1, -1, -1, -1, 0 },
    { 23, 1, 0, -1, -1, -1, -1, 0 },
    { 22, 1, 1, -1, -1, -1, -1, 0 },
    { 25, 1, 5, -1, -1, -1, -1, 0 },
    { 5, 2, 17, 38, -1, -1, -1, 0 },
    { 10, 4, 15, 23, 37, 43, -1, 0 },
    { 20, 1, 35, -1, -1, -1, -1, 0 },
    { 21, 1, 36, -1, -1, -1, -1, 0 },
    { -1, 1, -1, -1, -1, -1, -1, 0 },
};
// 0x0042BFE0
type_42B740 dword_42BFE0[23] = {
    { 4, 1, 11, -1, -1, -1, -1, 0 },
    { 12, 2, 13, 25, -1, -1, -1, 0 },
    { 13, 3, 9, 4, 39, -1, -1, 0 },
    { 11, 2, 10, 24, -1, -1, -1, 0 },
    { 0, 3, 40, 19, 33, -1, -1, 0 },
    { 1, 3, 18, 20, 34, -1, -1, 0 },
    { 2, 3, 21, 31, 29, -1, -1, 0 },
    { 3, 3, 22, 32, 30, -1, -1, 0 },
    { 16, 1, 6, -1, -1, -1, -1, 0 },
    { 15, 2, 15, 27, -1, -1, -1, 0 },
    { 7, 1, 16, -1, -1, -1, -1, 0 },
    { 17, 1, 3, -1, -1, -1, -1, 0 },
    { 14, 1, 14, -1, -1, -1, -1, 0 },
    { 6, 2, 12, 42, -1, -1, -1, 0 },
    { 22, 1, 2, -1, -1, -1, -1, 0 },
    { 23, 1, 0, -1, -1, -1, -1, 0 },
    { 24, 1, 1, -1, -1, -1, -1, 0 },
    { 25, 1, 5, -1, -1, -1, -1, 0 },
    { 5, 2, 17, 38, -1, -1, -1, 0 },
    { 10, 4, 7, 23, 37, 43, -1, 0 },
    { 20, 1, 35, -1, -1, -1, -1, 0 },
    { 21, 1, 36, -1, -1, -1, -1, 0 },
    { -1, 1, -1, -1, -1, -1, -1, 0 },
};
// 0x0042C2C0
type_42B740 dword_42C2C0[23] = {
    { 4, 1, 11, -1, -1, -1, -1, 0 },
    { 12, 2, 7, 25, -1, -1, -1, 0 },
    { 13, 3, 9, 4, 39, -1, -1, 0 },
    { 11, 3, 12, 42, 24, -1, -1, 0 },
    { 0, 2, 19, 33, -1, -1, -1, 0 },
    { 1, 2, 20, 34, -1, -1, -1, 0 },
    { 2, 4, 14, 21, 31, 29, -1, 0 },
    { 3, 4, 13, 22, 32, 30, -1, 0 },
    { 16, 1, 6, -1, -1, -1, -1, 0 },
    { 15, 2, 15, 27, -1, -1, -1, 0 },
    { 7, 1, 16, -1, -1, -1, -1, 0 },
    { 17, 1, 3, -1, -1, -1, -1, 0 },
    { 14, 1, 40, -1, -1, -1, -1, 0 },
    { 6, 1, 18, -1, -1, -1, -1, 0 },
    { 24, 1, 2, -1, -1, -1, -1, 0 },
    { 25, 1, 0, -1, -1, -1, -1, 0 },
    { 22, 1, 1, -1, -1, -1, -1, 0 },
    { 23, 1, 5, -1, -1, -1, -1, 0 },
    { 5, 2, 17, 38, -1, -1, -1, 0 },
    { 10, 4, 10, 23, 37, 43, -1, 0 },
    { 20, 1, 35, -1, -1, -1, -1, 0 },
    { 21, 1, 36, -1, -1, -1, -1, 0 },
    { -1, 1, -1, -1, -1, -1, -1, 0 },
};
// 0x004F2AAC
type_42B740 *dword_4F2AAC[5];
// 0x004F30C4
RwReal flt_4F30C4;
// 0x004F30C8
RwReal flt_4F30C8;
// 0x004F30CC
RwReal flt_4F30CC;
// 0x004F30D0
RwInt32 dword_4F30D0;
// End of its data definitions.


// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).
type_4F30A8 dword_4F30A8;
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_06EDDDIONA@German?$AA@ @ 0x003D4330
// match: ?flt_3E017C@@3MB @ 0x003E017C
// match: ??_C@_0O@LACFKLDA@RWASSERT?5TRAP?$AA@ @ 0x003E0180
// match: ??_C@_09IGPPBBJE@Deutsches?$AA@ @ 0x003E0190
// match: ??_C@_0EO@CMMCDAMO@Com?5Sergei?5Konstantinov?3?5Il?5faut@ @ 0x003E01A0
// match: ??_C@_0EL@DMFLJBNI@Com?5Sergei?5Konstantinov?3?5Dobbiam@ @ 0x003E01F0
// match: ??_C@_0FE@PMPBLGBK@Com?5Sergei?5Konstantinov?3?5Les?5All@ @ 0x003E0240
// match: ??_C@_0EH@OMJFJOFL@Com?5Sergei?5Konstantinov?3?5I?5tedes@ @ 0x003E0298
// match: ??_C@_0EH@GHEKJBOK@Com?5Sergei?5Konstantinov?3?5Bien?0?5t@ @ 0x003E02E0
// match: ??_C@_0CP@BPDMEHNJ@Com?5Sergei?5Konstantinov?3?5Bene?0?5c@ @ 0x003E0328
// match: ??_C@_0FJ@ENIHDMFA@Lt?5Tanya?5Pavelovna?3?5Une?5explosio@ @ 0x003E0358
// match: ??_C@_0CC@OHAENDDL@Lt?5Tanya?5Pavelovna?3?5Un?8esplosion@ @ 0x003E03B4
// match: ??_C@_0BH@KPNLAKCN@d?3?2Media?2codlayout?4uix?$AA@ @ 0x003E03D8
// match: .CRT$XCU+0 @ 0x00427198
// match: ?dword_42B740@@3PAUtype_42B740@@A @ 0x0042B740
// match: ?dword_42BA20@@3PAUtype_42B740@@A @ 0x0042BA20
// match: ?dword_42BD00@@3PAUtype_42B740@@A @ 0x0042BD00
// match: ?dword_42BFE0@@3PAUtype_42B740@@A @ 0x0042BFE0
// match: ?dword_42C2C0@@3PAUtype_42B740@@A @ 0x0042C2C0

// match: _$E1 @ 0x0030C0E0

void sub_19B6D0(D3DSurface *arg_0, RwReal arg_4, RwReal arg_8, RwReal arg_C, RwReal arg_10, RwReal arg_14,
                RwReal arg_18);

// match: ?sub_19B0F0@@YAXXZ @ 0x0019B0F0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Points dword_4F2AAC at the five tables and flags each row that has a
// kind 5.
void sub_19B0F0()
{
    RwInt32 var_C;
    RwInt32 bp_8;
    RwInt32 bp_4;

    dword_4F2AAC[0] = dword_42B740;
    dword_4F2AAC[1] = dword_42BA20;
    dword_4F2AAC[2] = dword_42BD00;
    dword_4F2AAC[3] = dword_42BFE0;
    dword_4F2AAC[4] = dword_42C2C0;
    for (bp_4 = 0; bp_4 < 5; bp_4++)
    {
        bp_8 = 0;
        while (dword_4F2AAC[bp_4][bp_8].unk_00 != -1)
        {
            for (var_C = 0; var_C < dword_4F2AAC[bp_4][bp_8].unk_04; var_C++)
            {
                if (dword_4F2AAC[bp_4][bp_8].unk_08[var_C] == 5)
                    dword_4F2AAC[bp_4][bp_8].unk_1C = 1;
            }
            bp_8++;
        }
    }
}

// match: ?sub_19B1E0@@YAPAUtype_42B740@@H@Z @ 0x0019B1E0
type_42B740 *sub_19B1E0(RwInt32 arg_0)
{
    return dword_4F2AAC[arg_0];
}

// match: ?sub_19B1F0@@YAXH@Z @ 0x0019B1F0
// Stops for good, after a message, when arg_0 is 0.
void sub_19B1F0(RwInt32 arg_0)
{
    if (!arg_0)
    {
        printf("RWASSERT TRAP");
        while (1)
            ;
    }
}

// match: ??0type_4F30A8@@QAE@XZ @ 0x0019B220
type_4F30A8::type_4F30A8()
{
    unk_00 = 1.0f;
    unk_04 = 1.0f;
    unk_08 = 0.45f;
    unk_0C = 0;
    unk_10 = 0;
    unk_14 = 0;
}

// match: ?sub_19B270@@YAXPAUtype_8F210@@@Z @ 0x0019B270
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Scales the ambient's colour by dword_4F30A8's unk_00 and the lights' by
// its unk_04, each channel kept below 1 (a dead reset first). The kept
// value goes through the FPU (fld, fstp) where a plain float copy moves it
// as an integer: the original converts it, as from a double.
void sub_19B270(type_8F210 *arg_0)
{
    RwInt32 var_8;
    RwInt32 l4;

    var_8 = 0;
    if (var_8)
    {
        for (l4 = 0; l4 < 5; l4++)
        {
            arg_0->unk_10[l4].unk_10.unk_00 = 0;
            arg_0->unk_10[l4].unk_10.unk_04 = 0;
            arg_0->unk_10[l4].unk_10.unk_08 = 0;
            arg_0->unk_10[l4].unk_10.unk_0C = 0;
            arg_0->unk_10[l4].unk_00.unk_00 = 1.0f;
            arg_0->unk_10[l4].unk_00.unk_04 = 0;
            arg_0->unk_10[l4].unk_00.unk_08 = 0;
            arg_0->unk_10[l4].unk_00.unk_0C = 0;
        }
    }
    else
    {
        if (dword_4F30A8.unk_00 != 1.0f)
        {
            arg_0->unk_10[0].unk_10.unk_00 = dword_4F30A8.unk_00 * arg_0->unk_10[0].unk_10.unk_00;
            arg_0->unk_10[0].unk_10.unk_04 = dword_4F30A8.unk_00 * arg_0->unk_10[0].unk_10.unk_04;
            arg_0->unk_10[0].unk_10.unk_08 = dword_4F30A8.unk_00 * arg_0->unk_10[0].unk_10.unk_08;
            arg_0->unk_10[0].unk_10.unk_0C = dword_4F30A8.unk_00 * arg_0->unk_10[0].unk_10.unk_0C;
            arg_0->unk_10[0].unk_10.unk_00 = arg_0->unk_10[0].unk_10.unk_00 < 1.0f ? (RwReal)(RwDouble)arg_0->unk_10[0].unk_10.unk_00 : 1.0f;
            arg_0->unk_10[0].unk_10.unk_04 = arg_0->unk_10[0].unk_10.unk_04 < 1.0f ? (RwReal)(RwDouble)arg_0->unk_10[0].unk_10.unk_04 : 1.0f;
            arg_0->unk_10[0].unk_10.unk_08 = arg_0->unk_10[0].unk_10.unk_08 < 1.0f ? (RwReal)(RwDouble)arg_0->unk_10[0].unk_10.unk_08 : 1.0f;
            arg_0->unk_10[0].unk_10.unk_0C = arg_0->unk_10[0].unk_10.unk_0C < 1.0f ? (RwReal)(RwDouble)arg_0->unk_10[0].unk_10.unk_0C : 1.0f;
        }
        if (dword_4F30A8.unk_04 != 1.0f)
        {
            for (l4 = 0; l4 < arg_0->unk_00; l4++)
            {
                arg_0->unk_10[l4 + 1].unk_10.unk_00 = dword_4F30A8.unk_04 * arg_0->unk_10[l4 + 1].unk_10.unk_00;
                arg_0->unk_10[l4 + 1].unk_10.unk_04 = dword_4F30A8.unk_04 * arg_0->unk_10[l4 + 1].unk_10.unk_04;
                arg_0->unk_10[l4 + 1].unk_10.unk_08 = dword_4F30A8.unk_04 * arg_0->unk_10[l4 + 1].unk_10.unk_08;
                arg_0->unk_10[l4 + 1].unk_10.unk_0C = dword_4F30A8.unk_04 * arg_0->unk_10[l4 + 1].unk_10.unk_0C;
                arg_0->unk_10[l4 + 1].unk_10.unk_00 =
                    arg_0->unk_10[l4 + 1].unk_10.unk_00 < 1.0f ? (RwReal)(RwDouble)arg_0->unk_10[l4 + 1].unk_10.unk_00 : 1.0f;
                arg_0->unk_10[l4 + 1].unk_10.unk_04 =
                    arg_0->unk_10[l4 + 1].unk_10.unk_04 < 1.0f ? (RwReal)(RwDouble)arg_0->unk_10[l4 + 1].unk_10.unk_04 : 1.0f;
                arg_0->unk_10[l4 + 1].unk_10.unk_08 =
                    arg_0->unk_10[l4 + 1].unk_10.unk_08 < 1.0f ? (RwReal)(RwDouble)arg_0->unk_10[l4 + 1].unk_10.unk_08 : 1.0f;
                arg_0->unk_10[l4 + 1].unk_10.unk_0C =
                    arg_0->unk_10[l4 + 1].unk_10.unk_0C < 1.0f ? (RwReal)(RwDouble)arg_0->unk_10[l4 + 1].unk_10.unk_0C : 1.0f;
            }
        }
    }
}

// match: ?sub_19B650@@YAHPAX@Z @ 0x0019B650
// Empty in this build: 0.
RwInt32 sub_19B650(void *arg_0)
{
    RwInt32 var_4;

    var_4 = 0;
    return var_4;
}

// match: ?sub_19B670@@YAXM@Z @ 0x0019B670
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Draws the back buffer over the screen again at 0.15 with alpha arg_0.
void sub_19B670(RwReal arg_0)
{
    D3DSurface *var_C;
    RwReal bp_8;
    D3DSurface *bp_4;

    D3DDevice_GetBackBuffer(-1, D3DBACKBUFFER_TYPE_MONO, &bp_4);
    var_C = bp_4;
    bp_8 = 0.15f;
    sub_19B6D0(var_C, 640.0f, 480.0f, 640.0f, 480.0f, bp_8, arg_0);
    bp_4->Release();
}

// match: ?sub_19B6D0@@YAXPAUD3DSurface@@MMMMMM@Z @ 0x0019B6D0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Draws arg_0 over the screen (arg_4 by arg_8, its texture coordinates to
// arg_C and arg_10) at the depth arg_14 with the alpha arg_18, blended, the
// render states it changes put back.
void sub_19B6D0(D3DSurface *arg_0, RwReal arg_4, RwReal arg_8, RwReal arg_C, RwReal arg_10, RwReal arg_14,
                RwReal arg_18)
{
    RwInt32 var_90;
    RwUInt32 l8C;
    void *var_88;
    RwUInt32 lcl_84;
    void *var_80;
    void *var_7C;
    type_19B6D0_v m_78[4];
    void *bp_4;

    if (!arg_0)
        return;
    RwRenderStateGet(rwRENDERSTATECULLMODE, &var_7C);
    RwRenderStateGet(rwRENDERSTATEVERTEXALPHAENABLE, &bp_4);
    RwRenderStateGet(rwRENDERSTATESRCBLEND, &var_88);
    RwRenderStateGet(rwRENDERSTATEDESTBLEND, &var_80);
    RwRenderStateSet(rwRENDERSTATECULLMODE, (void *)rwCULLMODECULLNONE);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)TRUE);
    RwRenderStateSet(rwRENDERSTATESRCBLEND, (void *)rwBLENDSRCALPHA);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void *)rwBLENDINVSRCALPHA);
    for (var_90 = 0; var_90 < 3; var_90++)
    {
        RwXbSetCachedTextureStageState(var_90, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
        RwXbSetCachedTextureStageState(var_90, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);
    }
    lcl_84 = 0xFF;
    l8C = ((RwInt32)(arg_18 * 255.0f) << 24) | (lcl_84 << 16) | (lcl_84 << 8) | lcl_84;
    D3DDevice_SetTexture(0, (D3DBaseTexture *)arg_0);
    m_78[0].unk_00 = 0;
    m_78[0].unk_04 = 0;
    m_78[0].unk_08 = arg_14;
    m_78[0].unk_0C = 1.0f - arg_14;
    m_78[0].unk_14 = 0;
    m_78[0].unk_18 = 0;
    m_78[0].unk_10 = l8C;
    m_78[1].unk_00 = arg_4;
    m_78[1].unk_04 = 0;
    m_78[1].unk_08 = arg_14;
    m_78[1].unk_0C = 1.0f - arg_14;
    m_78[1].unk_14 = arg_C;
    m_78[1].unk_18 = 0;
    m_78[1].unk_10 = l8C;
    m_78[2].unk_00 = arg_4;
    m_78[2].unk_04 = arg_8;
    m_78[2].unk_08 = arg_14;
    m_78[2].unk_0C = 1.0f - arg_14;
    m_78[2].unk_14 = arg_C;
    m_78[2].unk_18 = arg_10;
    m_78[2].unk_10 = l8C;
    m_78[3].unk_00 = 0;
    m_78[3].unk_04 = arg_8;
    m_78[3].unk_08 = arg_14;
    m_78[3].unk_0C = 1.0f - arg_14;
    m_78[3].unk_14 = 0;
    m_78[3].unk_18 = arg_10;
    m_78[3].unk_10 = l8C;
    D3DDevice_SetVertexShader(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
    RwXboxDrawVerticesUP(D3DPT_QUADLIST, 4, m_78, 0x1C);
    RwRenderStateSet(rwRENDERSTATECULLMODE, var_7C);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, bp_4);
    RwRenderStateSet(rwRENDERSTATESRCBLEND, var_88);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, var_80);
}

// match: ?sub_19B9E0@@YAMH@Z @ 0x0019B9E0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The performance counter in seconds, and a stopwatch on it: arg_0 0
// starts it (0), 6 reads it, 1 resumes it after a pause that 2 began, 3 and
// 4 do so less or more a tenth of a second; others return the time.
RwReal sub_19B9E0(RwInt32 arg_0)
{
    LARGE_INTEGER var_18;
    RwReal var_C;
    LARGE_INTEGER bp_8;

    if (!dword_4F30D0)
    {
        dword_4F30D0 = 1;
        QueryPerformanceFrequency(&var_18);
        flt_4F30CC = 1.0f / var_18.QuadPart;
    }
    QueryPerformanceCounter(&bp_8);
    var_C = bp_8.QuadPart * flt_4F30CC;
    if (arg_0 == 0)
    {
        flt_4F30C8 = var_C;
        return 0.0f;
    }
    if (arg_0 == 6)
        return var_C - flt_4F30C8;
    if (arg_0 == 1)
        flt_4F30C8 = var_C - flt_4F30C4 + flt_4F30C8;
    if (arg_0 == 2)
        flt_4F30C4 = var_C;
    if (arg_0 == 3)
        flt_4F30C8 = var_C - (flt_4F30C4 + 0.1f) + flt_4F30C8;
    if (arg_0 == 4)
        flt_4F30C8 = var_C - (flt_4F30C4 - 0.1f) + flt_4F30C8;
    return var_C;
}

// match: ?sub_19BAC0@@YAXPAURwCamera@@@Z @ 0x0019BAC0
// Clears the camera's image and depth to black, twice.
void sub_19BAC0(RwCamera *arg_0)
{
    RwRGBA var_4;

    var_4.red = 0;
    var_4.green = 0;
    var_4.blue = 0;
    var_4.alpha = 0;
    if (arg_0)
    {
        RwCameraClear(arg_0, &var_4, rwCAMERACLEARIMAGE | rwCAMERACLEARZ);
        sub_19A750((const RwChar *)arg_0);
        sub_126750(arg_0);
        RwCameraClear(arg_0, &var_4, rwCAMERACLEARIMAGE | rwCAMERACLEARZ);
        sub_19A750((const RwChar *)arg_0);
        sub_126750(arg_0);
    }
}

// match: ?sub_19BB40@@YAXPBDH@Z @ 0x0019BB40
void sub_19BB40(const RwChar *arg_0, RwInt32 arg_4)
{
    sub_19A750(arg_0, arg_4);
}

// match: ?sub_19BB60@@YAHPAD0PBD1H@Z @ 0x0019BB60
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Writes arg_0 into arg_4 with its first arg_8 replaced by arg_C (arg_10:
// arg_4 is also the text, copied first); whether arg_8 was found.
RwInt32 sub_19BB60(RwChar *arg_0, RwChar *arg_4, const RwChar *arg_8, const RwChar *arg_C, RwInt32 arg_10)
{
    RwInt32 var_420;
    RwInt32 var_41C;
    RwChar var_418[0x400];
    RwInt32 lv_10;
    RwInt32 var_C;
    RwInt32 bp_8;
    RwChar *bp_4;

    var_C = 0;
    bp_4 = 0;
    if (arg_10)
    {
        arg_0 = var_418;
        strcpy(arg_0, arg_4);
    }
    bp_4 = strstr(arg_0, arg_8);
    if (bp_4)
    {
        var_420 = bp_4 - arg_0;
        if (var_420)
        {
            strncpy(arg_4, arg_0, var_420);
            arg_4[var_420] = 0;
        }
        else
            *arg_4 = 0;
        strcat(arg_4, arg_C);
        bp_8 = strlen(arg_0);
        var_41C = strlen(arg_8);
        lv_10 = bp_8 - var_41C - var_420;
        if (lv_10 > 0)
            strcat(arg_4, bp_4 + var_41C);
        var_C = 1;
    }
    return var_C;
}

// match: ?sub_19BC70@@YAHPAD0@Z @ 0x0019BC70
// "German" in arg_0 as "Deutsches", into arg_4.
RwInt32 sub_19BC70(RwChar *arg_0, RwChar *arg_4)
{
    RwInt32 var_4;

    var_4 = 0;
    var_4 = sub_19BB60(arg_0, arg_4, "German", "Deutsches", var_4);
    return var_4;
}

// match: ?sub_19BCB0@@YAHPBDPAD@Z @ 0x0019BCB0
// Four Italian subtitles given in French instead, into arg_4; whether
// arg_0 was one.
RwInt32 sub_19BCB0(const RwChar *arg_0, RwChar *arg_4)
{
    RwInt32 var_4;

    var_4 = 0;
    if (!strncmp(arg_0, "Lt Tanya Pavelovna: Un'esplosione", 0x20))
    {
        strcpy(arg_4, "Lt Tanya Pavelovna: Une explosion. Il faut quelque chose pour couvrir le bruit du fusil.");
        var_4 = 1;
    }
    if (!strncmp(arg_0, "Com Sergei Konstantinov: Bene, ce l'hai fatta.", 0x2C))
    {
        strcpy(arg_4, "Com Sergei Konstantinov: Bien, tu as r\xe9ussi. On a besoin d'un tireur !");
        var_4 = 1;
    }
    if (!strncmp(arg_0, "Com Sergei Konstantinov: I tedeschi stanno preparando un altro assalto", 0x44))
    {
        strcpy(arg_4, "Com Sergei Konstantinov: Les Allemands se pr\xe9parent \xe0 un nouvel assaut sur l'usine.");
        var_4 = 1;
    }
    if (!strncmp(arg_0, "Com Sergei Konstantinov: Dobbiamo trattenerli fino all'arrivo dei carristi", 0x44))
    {
        strcpy(arg_4, "Com Sergei Konstantinov: Il faut les retenir jusqu'\xe0 l'arriv\xe9" "e de l'\xe9quipage.");
        var_4 = 1;
    }
    return var_4;
}

// match: ?sub_19BD80@@YAHPBD@Z @ 0x0019BD80
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Whether arg_0 holds a "$ud$" token, outside the English game (none while
// dword_4B88B0 is set).
RwInt32 sub_19BD80(const RwChar *arg_0)
{
    RwInt32 var_10;
    RwInt32 var_C;
    RwInt32 bp_8;
    RwInt32 bp_4;

    var_C = 0;
    if (dword_4B88B0)
        return 0;
    bp_4 = sub_19B0A0();
    if (bp_4)
    {
        bp_8 = strlen(arg_0);
        for (var_10 = 0; var_10 < bp_8; var_10++)
        {
            if ((arg_0 + var_10)[0] == '$' && (arg_0 + var_10)[3] == '$' && (arg_0 + var_10)[1] == 'u'
                && (arg_0 + var_10)[2] == 'd')
            {
                var_C = 1;
                break;
            }
        }
    }
    return var_C;
}

// match: ?sub_19BE30@@YAHPAUtype_19BE30@@@Z @ 0x0019BE30
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Marks in arg_0 which of the four controllers are in: how many are.
RwInt32 sub_19BE30(type_19BE30 *arg_0)
{
    RwInt32 var_8;
    RwInt32 l4;

    l4 = 0;
    for (var_8 = 0; var_8 < 4; var_8++)
    {
        if (dword_4F4638[var_8].unk_48)
        {
            arg_0->unk_690[var_8] = 1;
            l4++;
        }
        else
            arg_0->unk_690[var_8] = 0;
    }
    return l4;
}

// match: ?sub_19BEA0@@YAHXZ @ 0x0019BEA0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The language's index in another order (1 for English and the rest).
RwInt32 sub_19BEA0()
{
    RwInt32 var_8;
    RwInt32 l4;

    l4 = sub_19B0A0();
    var_8 = 0;
    switch (l4)
    {
    case 2:
        var_8 = 4;
        break;
    case 1:
        var_8 = 3;
        break;
    case 6:
        var_8 = 5;
        break;
    case 5:
        var_8 = 6;
        break;
    default:
        var_8 = 1;
        break;
    }
    return var_8;
}

// Not in the image: a stand-in for a function the original object held last, which
// the link dropped (/OPT:REF) but whose literal stayed: the UI layout's path sits
// after this object's literals (0x3E03D8), before unit_19CB20's table, which also
// names it (a same-named literal is the first object's). Unreferenced.
const RwChar *dropped_3E03D8()
{
    return "d:\\Media\\codlayout.uix";
}


#ifdef CODFH_PLAIN
// Plain builds (tools/plainbuild.py): the variables below are a second name for this unit's
// variables' bytes in the image (tools/session/overlapvars.py --aliases); only the placement
// link gives them one storage, so any other link binds them here at the image offset.
// (bound at start-up: the library initialization area runs before every game constructor)
#pragma warning(disable: 4073)
#pragma init_seg(lib)
// 0x004F30B8: dword_4F30A8 + 0x10
RwInt32 &dword_4F30B8 = *(RwInt32 *)((RwUInt8 *)&dword_4F30A8 + 0x10);
// 0x004F30BC: dword_4F30A8 + 0x14
RwInt32 &dword_4F30BC = *(RwInt32 *)((RwUInt8 *)&dword_4F30A8 + 0x14);
#endif
