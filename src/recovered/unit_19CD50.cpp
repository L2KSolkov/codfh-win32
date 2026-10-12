// Split from unit_19CB20.cpp at 0x19CD50, where the image starts another object: its .rdata
// begins at 0x3E05DC with its own 16.666666, the unreferenced constant every game object
// starts its constants with, after the Bink player's object's (PLAN M7).

#include <xtl.h>
#include <stdio.h>
#include <stdlib.h>
#include "game/xboxlive.h"
#include "game/platform.h"
#include "game/gameloop.h"
#include "game/movie.h"
#include "game/savestate.h"
#include "game/functions.h"
#include "game/clones.h"
#ifdef CODFH_WIN32
#include <intrin.h>
extern "C" void plog(const RwChar *fmt, ...);
#endif
#include "rw/rwxbox.h"
#ifdef CODFH_SP
#include <xfont.h>
#include <string.h>
#endif

// Its data definitions (PLAN M5), in the image's address order.
// 0x003E05DC
extern const RwReal flt_3E05DC = 16.666666f;
#ifdef CODFH_SP // single player's own (.bss): sp_sub_12C410's count
// SP 0x003EB790
RwInt32 sp_dword_3EB790;                // the times the disc error came up
#endif

// match: ?flt_3E05DC@@3MB @ 0x003E05DC


// match: ?sub_19CD50@@YAHXZ @ 0x0019CD50
// match: ??_C@_02GKMJJLGI@d?3?$AA@ @ 0x003E05E0
// match: ??_C@_04MFDNODIH@xbox?$AA@ @ 0x003E05E4
// match: __real@41a570a4 @ 0x003E05EC
// match: __real@3f8a617c @ 0x003E05F0
// match: ??_C@_0BP@IPOJNPLF@Cant?5load?5Bink?5Movie?3?5?$CFs?5?9?9?5?$CFs?$AA@ @ 0x003E05F4
// sp-match: ?sub_19CD50@@YAHXZ @ 0x0012C6C0
RwInt32 sub_19CD50()
{
    RwInt32 var_4;

    var_4 = 0;
    if (sub_19CD80())
        var_4 = 1;
    return var_4;
}
// match: ?sub_19CD80@@YAHXZ @ 0x0019CD80
// sp-match: ?sub_19CD80@@YAHXZ @ 0x0012C3D0
// Mounts d: as RenderWare's default file system.
RwInt32 sub_19CD80()
{
    RwInt32 var_4;

    var_4 = RtFSManagerOpen(-1);
    dword_4F39D4 = RtXboxFSystemInit(5, "d:", "xbox");
    var_4 = RtFSManagerRegister(dword_4F39D4);
    RtFSManagerSetDefaultFileSystem(dword_4F39D4);
#ifndef CODFH_SP
    // Single player installs the pack file elsewhere (its call at SP 0xA5CFB), not here (SP 0x12C3D0).
    sub_16C940();
#endif
    return var_4;
}
#ifdef CODFH_SP
// The disc error's message in each language: off_42C5A4[6] on (unit_19CB20, SP .data 0x3294AC).
extern const RwChar *off_42C5A4[13];
extern RwRGBA dword_42B470[2];
extern RwInt32 dword_428E14;
void sub_1A20C0(const RwChar *arg_0, WCHAR *arg_4);

// The disc error ("There is a problem with the disc you are using."): with
// arg_0 0 and the loader running (dword_428E14), draws its lines in the
// default font in the middle of the screen for ever; otherwise only notes it
// (dword_4F39DC). Multiplayer's one-argument sub_19A750(void *) calls stand
// where single player calls it (sub_19CDE0, SP 0x12C67B and 0x12C69F).
// sp-match: ?sp_sub_12C410@@YAXPAX@Z @ 0x0012C410
void sp_sub_12C410(void *arg_0)
{
    XFONT *var_C18;
    RwCamera *var_C14;
    D3DSurface *var_C10;
    UINT var_C0C;
    UINT var_C08;
    RwChar var_C04[0x400];
    RwChar var_804[0x400];
    WCHAR var_404[0x200];
    RwInt32 lang;
    RwUInt32 y;
    RwInt32 n;
    RwInt32 i;
    RwChar c;
    RwUInt32 dy;
    RwChar *p;

    var_C18 = (XFONT *)dword_4F39F0;
    lang = sub_19B0A0();
    if (arg_0)
        return;
#ifdef CODFH_WIN32
    // (the port logs which check failed: the caller's address, for the map file)
    plog("disc error: a disc check failed (called from %p, the map's %08X)%s", _ReturnAddress(),
         (RwUInt32)((RwChar *)_ReturnAddress() - (RwChar *)GetModuleHandleA(NULL)) + 0x400000, // not an address: the image base
         dword_428E14 ? "; showing the disc-error screen" : "; noted");
#endif
    if (dword_428E14)
    {
        sp_dword_3EB790++;
        var_C14 = dword_4B88B0;
        if (!var_C14)
            var_C14 = (RwCamera *)dword_4E5C74;
        strcpy(var_C04, off_42C5A4[6 + lang]);
        if (var_C14)
        {
            var_C10 = D3DDevice_GetRenderTarget2();
            for (;;)
            {
                do
                    RwCameraClear(var_C14, dword_42B470, 3);
                while (!RwCameraBeginUpdate(var_C14));
                i = 0;
                n = 0;
                y = (RwUInt32)Height / 2 - 50;
                var_C08 = var_C18->GetTextHeight();
                p = var_C04;
                for (;; i++)
                {
                    c = var_C04[i];
                    if (c != '\n' && c != 0)
                    {
                        n++;
                        continue;
                    }
                    strcpy(var_804, p);
                    var_804[n] = 0;
                    sub_1A20C0(var_804, var_404);
                    var_C18->GetTextExtent(var_404, n, &var_C0C);
                    var_C18->TextOut(var_C10, var_404, n, ((RwUInt32)Width - var_C0C) / 2, y);
                    if (!c)
                        break;
                    dy = var_C08 * 4 / 3;
                    y += dy;
                    p = &var_C04[i + 1];
                    while (*p == '\n')
                    {
                        i++;
                        p++;
                        y += dy;
                    }
                    n = 0;
                }
                RwCameraEndUpdate(var_C14);
                RwRasterShowRaster(RwCameraGetRaster(var_C14), 0, 1);
            }
        }
    }
    dword_4F39DC = 1;
}
#endif

// match: ?sub_19CDE0@@YAHPBD@Z @ 0x0019CDE0
// sp-match: ?sub_19CDE0@@YAHPBD@Z @ 0x0012C5F0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Reads up to a million bytes of the file arg_0 ahead (none with the
// shell's unk_10 set): whether it could.
RwInt32 sub_19CDE0(const RwChar *arg_0)
{
    DWORD var_18;
    RwInt32 var_14;
    HANDLE lv_10;
    DWORD var_C;
    BOOL bp_8;
    void *bp_4;

    var_14 = 1;
    if (dword_4F45F8->unk_10)
        return 1;
    lv_10 = CreateFileA(arg_0, GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0);
    if (lv_10 != INVALID_HANDLE_VALUE)
    {
        var_C = GetFileSize(lv_10, &var_C);
        if (var_C >= 1000000)
            var_C = 1000000;
        bp_4 = malloc(var_C);
        bp_8 = ReadFile(lv_10, bp_4, var_C, &var_18, 0);
        if (!bp_8 || var_C != var_18)
        {
#ifdef CODFH_SP
            sp_sub_12C410(0);
#else
            sub_19A750(0);
#endif
            var_14 = 0;
        }
        CloseHandle(lv_10);
        free(bp_4);
    }
    else
    {
#ifdef CODFH_SP
        sp_sub_12C410(0);
#else
        sub_19A750(0);
#endif
        var_14 = 0;
    }
    return var_14;
}
// match: ?sub_19CEC0@@YAPAURwTexture@@PBD0@Z @ 0x0019CEC0
// sp-match: ?sub_19CEC0@@YAPAURwTexture@@PBD0@Z @ 0x0012C6E0
// The texture read callback: the DDS file first, else the callback before.
RwTexture *sub_19CEC0(const RwChar *arg_0, const RwChar *arg_4)
{
    RwTexture *var_4;

    var_4 = RwXboxDDSTextureRead(arg_0, arg_4);
    return var_4 ? var_4 : dword_4F39E0(arg_0, arg_4);
}
// match: ?sub_19CF10@@YAHXZ @ 0x0019CF10
// sp-match: ?sub_19CF10@@YAHXZ @ 0x0012C710
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Sets the gamma ramp from dword_4F30A8's gamma, the soft display filter
// and the DDS read callback.
RwInt32 sub_19CF10()
{
    RwInt32 var_314;
    RwInt32 l310;
    RwUInt32 bp_30C;
    D3DGAMMARAMP var_308;

    bp_30C = (RwUInt32)RwXboxGetCurrentD3DDevice();
    for (l310 = 0; l310 < 0x100; l310++)
    {
        var_314 = (RwInt32)(l310 * 1.0811f - 20.68f * dword_4F30A8.unk_08);
        if (var_314 < 0)
            var_314 = 0;
        if (var_314 > 0xFF)
            var_314 = 0xFF;
        var_308.blue[l310] = (BYTE)var_314;
        var_308.green[l310] = (BYTE)var_314;
        var_308.red[l310] = (BYTE)var_314;
    }
    D3DDevice_SetGammaRamp(0, &var_308);
    D3DDevice_SetSoftDisplayFilter(TRUE);
    dword_4F39E0 = RwTextureGetReadCallBack();
    RwTextureSetReadCallBack(sub_19CEC0);
    return 1;
}
// match: ?sub_19D020@@YAHXZ @ 0x0019D020
// sp-match: ?sub_19D020@@YAHXZ @ 0x0012C7D0
RwInt32 sub_19D020()
{
    byte_4CF88C = 1;
#ifdef CODFH_SP
    // Single player sets the count by level (SP 0x12C7D7): 120 on levels 14 and 17,
    // 110 on 30, 141 on 36, 170 on 37, else 10.
    switch (sub_19B050())
    {
    case 14:
    case 17:
        dword_4F3080 = 120;
        break;
    case 30:
        dword_4F3080 = 110;
        break;
    case 36:
        dword_4F3080 = 141;
        break;
    case 37:
        dword_4F3080 = 170;
        break;
    default:
        dword_4F3080 = 10;
    }
#else
    dword_4F3080 = 10;
#endif
    return 1;
}
// match: ?sub_19D040@@YAXXZ @ 0x0019D040
// sp-match: ?sub_19D040@@YAXXZ @ 0x0012C870
void sub_19D040()
{
    if (dword_4F39DC)
#ifdef CODFH_SP
        sp_sub_12C410(0);
#else
        sub_19A750(0);
#endif
}
// match: ?sub_19D060@@YAXXZ @ 0x0019D060
// sp-match: ?sub_19D060@@YAXXZ @ 0x0012C890
// Puts the read callback before back.
void sub_19D060()
{
    RwTextureSetReadCallBack(dword_4F39E0);
}
extern RwReal dword_4F2B64;
// match: ?sub_19D080@@YAXPAURwCamera@@@Z @ 0x0019D080
// sp-match: ?sub_19D080@@YAXPAURwCamera@@@Z @ 0x0012C8A0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The frame's end on the camera arg_0: the friends feature started or
// ended when asked, the back buffer drawn over itself once at
// dword_4F2B64's alpha (the render states kept around it), and the second
// camera updated.
void sub_19D080(RwCamera *arg_0)
{
    void *var_2C;
    void *var_28;
    void *ebp_24;
    void *var_20;
    void *l1C;
    void *m_18;
    void *ebp_14;
    void *lv_10;
    void *var_C;
    void *bp_8;
    void *bp_4;

    if (!arg_0)
        return;
    if (dword_4F39E4 == 1)
    {
        dword_4F3130.sub_19C200();
        dword_4F39E4 = 2;
    }
    if (dword_4F39E4 == 3)
        dword_4F3130.sub_19C280();
    RwCameraBeginUpdate(arg_0);
    RwRenderStateGet(rwRENDERSTATEZWRITEENABLE, &var_2C);
    RwRenderStateGet(rwRENDERSTATEZTESTENABLE, &l1C);
    RwRenderStateGet(rwRENDERSTATESHADEMODE, &lv_10);
    RwRenderStateGet(rwRENDERSTATETEXTUREFILTER, &ebp_14);
    RwRenderStateGet(rwRENDERSTATEVERTEXALPHAENABLE, &var_C);
    RwRenderStateGet(rwRENDERSTATECULLMODE, &var_20);
    RwRenderStateGet(rwRENDERSTATESRCBLEND, &var_28);
    RwRenderStateGet(rwRENDERSTATEDESTBLEND, &ebp_24);
    RwRenderStateGet(rwRENDERSTATEFOGENABLE, &m_18);
    RwRenderStateGet(rwRENDERSTATETEXTURERASTER, &bp_8);
    RwRenderStateGet(rwRENDERSTATETEXTUREADDRESS, &bp_4);
    RwRenderStateSet(rwRENDERSTATEFOGCOLOR, (void *)0x80);
    if (dword_4F2B64 != 0.0f)
    {
        sub_19B670(dword_4F2B64);
        dword_4F2B64 = 0;
    }
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, var_2C);
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, l1C);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, var_C);
    RwRenderStateSet(rwRENDERSTATESRCBLEND, var_28);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, ebp_24);
    RwRenderStateSet(rwRENDERSTATEFOGENABLE, m_18);
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, bp_8);
    RwRenderStateSet(rwRENDERSTATETEXTUREADDRESS, bp_4);
    RwRenderStateSet(rwRENDERSTATESHADEMODE, lv_10);
    RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, ebp_14);
    RwRenderStateSet(rwRENDERSTATECULLMODE, var_20);
    RwCameraEndUpdate(arg_0);
    arg_0 = (RwCamera *)dword_4E5CBC;
    if (!arg_0)
        return;
    RwCameraBeginUpdate(arg_0);
    RwCameraEndUpdate(arg_0);
}
// match: ?sub_19D290@@YAHXZ @ 0x0019D290
// sp-match: ?sub_19D290@@YAHXZ @ 0x0012CA70
// Sets the FPU to truncate (keeping its control word) and opens the default
// font.
RwInt32 sub_19D290()
{
    RwUInt16 l4;
    HRESULT var_8;

    // begin original __asm (the original sets the control word in inline
    // assembly: fstcw into word_4F39EC, the rounding bits set in ax, fldcw)
    __asm
    {
        fstcw word_4F39EC
        mov ax, word_4F39EC
        and ax, 0xF0FF
        or ax, 0xC00
        mov l4, ax
        fldcw l4
    }
    // end original __asm
    var_8 = XFONT_OpenDefaultFont((XFONT **)&dword_4F39F0);
    return 1;
}
#ifndef CODFH_SP // MP only: multiplayer's game-loop exit (single player's loop, SP 0xA4930, never leaves); no twin in config/sp/shared.txt
// match: ?sub_19D2D0@@YAXXZ @ 0x0019D2D0
// Puts the FPU's control word back.
void sub_19D2D0()
{
    sub_19A750();
    // begin original __asm (the original restores the word in inline assembly)
    __asm fldcw word_4F39EC
    // end original __asm
}
#endif
// match: _main @ 0x0019D2E0
// sp-match: _main @ 0x0012CB50
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The game's entry (mainXapiStartup calls it): the launch data (a title's
// settings, a start from the debugger, or none), the save state, the
// video mode and devices, then the outer loop.
RwInt32 main()
{
    type_4F45F8 *var_C;
    DWORD bp_8;
    RwInt32 bp_4;

    bp_4 = 0;
    dword_4F2B70 = 0;
    dword_4F307C = 0;
    dword_42C5A0 = 1;
    dword_4F45F8 = (type_4F45F8 *)unk_4F39F8;
    bp_8 = XGetLaunchInfo((PDWORD)&dword_4F4628, (PLAUNCH_DATA)unk_4F39F8);
    dword_4F45FC = bp_8;
    if (!bp_8)
    {
        switch (dword_4F4628)
        {
        case LDT_TITLE:
            var_C = (type_4F45F8 *)unk_4F39F8;
            dword_42C5A0 = *(RwInt32 *)var_C;
            dword_4F30B8 = 1;
            unk_4B9308.sub_EEAA0(var_C->unk_24);
            dword_4F5A30 = dword_4F45F8->unk_394;
#ifndef CODFH_SP
            // Single player calls this elsewhere (SP 0xA5935), not from main (SP 0x12CB50).
            sub_1A2680(var_C);
#endif
            break;
        case LDT_FROM_DEBUGGER_CMDLINE:
            memset(dword_4F45F8, 0, sizeof(type_4F45F8));
            dword_4F45F8->unk_20 = 1;
            break;
        default:
            memset(dword_4F45F8, 0, sizeof(type_4F45F8));
        }
    }
    else
        memset(dword_4F45F8, 0, sizeof(type_4F45F8));
#ifndef CODFH_SP
    // Single player calls this elsewhere (SP 0x12912F), not from main (SP 0x12CB50).
    sub_19AD20();
#endif
    Width = 640;
    Height = 480;
    dword_4B87F0 = 32;
    dword_4B87F4 = 0x803;
    ZDepth = 32;
    dword_4B8880 = 0;
    sub_19D470(&unk_4F4600);
    dword_4B87FC = &unk_4F4600;
    dword_4F30C0 = XGetAudioFlags();
    XInitDevices(0, 0);
    sub_19B9E0(1);
    sub_D9C00();
    return bp_4;
}
// match: ?sub_19D470@@YAXPAUtype_4F4600@@@Z @ 0x0019D470
// sp-match: ?sub_19D470@@YAXPAUtype_4F4600@@@Z @ 0x0012CAA0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// RenderWare's device configuration for the television: 640 by 480, 60 Hz
// (50 for PAL without its 60 Hz mode), and the widescreen, 480p and 720p
// flags.
void sub_19D470(type_4F4600 *arg_0)
{
    DWORD var_8;
    DWORD l4;

    var_8 = XGetVideoFlags();
    l4 = XGetVideoStandard();
    RwXboxDeviceConfigGetDefaultValues(arg_0);
    switch (l4)
    {
    case XC_VIDEO_STANDARD_PAL_I:
        if (var_8 & XC_VIDEO_FLAGS_PAL_60Hz)
            arg_0->unk_20 = 60;
        else
            arg_0->unk_20 = 50;
        break;
    case XC_VIDEO_STANDARD_NTSC_J:
        arg_0->unk_20 = 60;
        break;
    default:
        arg_0->unk_20 = 60;
    }
    arg_0->unk_24 = 0x80000001;
    arg_0->unk_10 = 0x11;
    arg_0->unk_00 = 640;
    arg_0->unk_04 = 480;
    if (var_8 & XC_VIDEO_FLAGS_WIDESCREEN)
    {
        arg_0->unk_1C |= 0x10;
        dword_4F30BC = 1;
    }
    if (var_8 & XC_VIDEO_FLAGS_HDTV_480p)
        arg_0->unk_1C |= 0x40;
    else if (var_8 & XC_VIDEO_FLAGS_HDTV_720p)
    {
        arg_0->unk_1C &= ~0x40;
        arg_0->unk_1C |= 0x20;
    }
    arg_0->unk_1C |= 0x100;
}
// match: ?sub_19D580@type_19D580@@QAE_NXZ @ 0x0019D580
// sp-match: ?sub_19D580@type_19D580@@QAE_NXZ @ 0x0012CC80
bool type_19D580::sub_19D580()
{
    unk_00 = 0;
    unk_01 = 1;
    unk_8C[0] = 0;
    unk_02[0] = 0;
    unk_84 = 0;
    unk_10C = 0;
    unk_110 = 0;
    dword_4F39A8.sub_19CB20(0);
    return unk_01;
}
// match: ?sub_19D5E0@type_19D580@@QAE_NXZ @ 0x0019D5E0
// sp-match: ?sub_19D5E0@type_19D580@@QAE_NXZ @ 0x0012CCC0
bool type_19D580::sub_19D5E0()
{
    if (unk_84)
    {
        dword_4F39A8.sub_19CD10(unk_84, unk_110);
        unk_84 = 0;
    }
    unk_110 = 0;
    unk_00 = 0;
    unk_01 = 0;
    return true;
}
// match: ?sub_19D640@type_19D580@@QAE_NPBDH@Z @ 0x0019D640
// sp-match: ?sub_19D640@type_19D580@@QAE_NPBDH@Z @ 0x0012CD00
bool type_19D580::sub_19D640(const RwChar *arg_0, RwInt32 arg_4)
{
    RwChar var_108[0x100];

    if (unk_84)
        return false;
    unk_84 = dword_4F39A8.sub_19CB80(arg_0, (RwInt32 *)&unk_110);
    if (!unk_84)
    {
        sprintf(var_108, "Cant load Bink Movie: %s -- %s", arg_0, BinkGetError());
        unk_10C = 0;
        return false;
    }
    unk_88 = 0;
    unk_10C = 1;
    dword_4F39A8.sub_32260(unk_84);
    return true;
}
// match: ?sub_19D720@type_19D580@@QAEH_N@Z @ 0x0019D720
// sp-match: ?sub_19D720@type_19D580@@QAEH_N@Z @ 0x0012CDD0
RwInt32 type_19D580::sub_19D720(bool arg_0)
{
    if (unk_84)
    {
        if (BinkWait(unk_84))
            return 2;
        BinkDoFrame(unk_84);
        if (unk_88 == unk_84->Frames)
        {
            if (arg_0)
                unk_88 = 0;
            else
            {
                unk_00 = 0;
                return 1;
            }
        }
        if (!arg_0 && unk_84->FrameNum >= unk_84->Frames - 1)
        {
            unk_00 = 0;
            return 1;
        }
        BinkNextFrame(unk_84);
        unk_88++;
        return 0;
    }
    else
    {
        return -1;
    }
}
// match: ?sub_19D810@type_19D580@@QAEXPAURwCamera@@H@Z @ 0x0019D810
// sp-match: ?sub_19D810@type_19D580@@QAEXPAURwCamera@@H@Z @ 0x0012CE60
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Copies the frame into the back buffer (all of it, 32 bits a pixel).
void type_19D580::sub_19D810(RwCamera *arg_0, RwInt32 arg_4)
{
    D3DSurface *var_10;
    D3DLOCKED_RECT var_C;
    RwInt32 bp_4;

    D3DDevice_GetBackBuffer(0, D3DBACKBUFFER_TYPE_MONO, &var_10);
    var_10->LockRect(&var_C, 0, D3DLOCK_TILED);
    bp_4 = BinkCopyToBuffer(unk_84, var_C.pBits, var_C.Pitch, unk_84->Height, 0, 0, 0x80000003);
    var_10->UnlockRect();
    var_10->Release();
}
// match: ?sub_19D890@type_19D580@@QAEX_N@Z @ 0x0019D890
// sp-match: ?sub_19D890@type_19D580@@QAEX_N@Z @ 0x0012CEB0
void type_19D580::sub_19D890(bool arg_0)
{
    if (unk_84)
        BinkPause(unk_84, arg_0);
}
// match: ?sub_19D8C0@type_19D580@@QAEHXZ @ 0x0019D8C0
// sp-match: ?sub_19D8C0@type_19D580@@QAEHXZ @ 0x0012CED0
RwInt32 type_19D580::sub_19D8C0()
{
    return BinkWait(unk_84);
}
// match: ?sub_19D8E0@type_19D580@@QAEXHH@Z @ 0x0019D8E0
// sp-match: ?sub_19D8E0@type_19D580@@QAEXHH@Z @ 0x0012CEE0
// Sets track arg_0's volume full (arg_4) or off.
void type_19D580::sub_19D8E0(RwInt32 arg_0, RwInt32 arg_4)
{
    if (unk_84)
        BinkSetVolume(unk_84, arg_0, arg_4 ? 0x10000 : 0);
}
