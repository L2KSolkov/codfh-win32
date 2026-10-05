// The message screens drawn while the game waits (saving, loading, the
// memory unit): a frame of their own around the front end's draw.

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "rw/baengine.h"
#include "rw/baraster.h"
#include "game/functions.h"
#include "game/data.h"
#include "game/gameloop.h"
#include "game/render.h"
#include "game/textmanager.h"
#include "types/musicplayer.h"
#include "rws/gftime.h"
#include "types/type_DA0A0.h"
#include "game/waitscreen.h"
#include "types/type_3D3548.h"
#include "types/CGlobalSounds.h"
#include "types/type_8A980.h"
#include "rw/badevice.h"
#include "rw/rt2d.h"
#include "types/type_DA580.h"
#include "types/type_3DF8D8.h"
#include <string.h>
#include <stdlib.h>

// Its data definitions (PLAN M5), in the image's address order.
// 0x003DE8E4
extern const RwReal flt_3DE8E4 = 16.666666f;
// 0x003DE8E8
extern const RwReal flt_3DE8E8 = 16.666666f;
// 0x0042B470
// The cameras' clear colour (black); its second colour is unused.
RwRGBA dword_42B470[2] = { { 0, 0, 0, 255 } };
// 0x0042B478
RwReal flt_42B478 = 1.25f;
// 0x0042B47C
RwReal flt_42B47C = 0.15f;
// 0x0042B480
RwReal flt_42B480 = 0.954f;
// 0x0042B484
RwReal flt_42B484 = 0.58f;
// 0x0042B488
RwReal flt_42B488 = 0.954f;
// 0x0042B490
type_42B490 dword_42B490[3][3] = {
    { { 0.42f, 0.945f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { { 0.18f, 0.945f, 0.0f }, { 0.63f, 0.945f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { { 0.1f, 0.945f, 0.0f }, { 0.35f, 0.945f, 0.0f }, { 0.75f, 0.945f, 0.0f } },
};
// 0x0042B4FC
// What a missing text reads (unit_188380); 8-alignment puts the next
// object's message table at 0x42B518, so this is the waiting screens'.
RwChar byte_42B4FC[20] = "No Translation";
// 0x0042B510
RwReal flt_42B510 = -17.0f;
// 0x004B8894
RwUInt8 byte_4B8894;
// 0x004EBCC8
RwUInt8 byte_4EBCC8;
// 0x004EBCC9
RwUInt8 byte_4EBCC9;
// 0x004EBCCC
RwInt32 dword_4EBCCC;
// 0x004EBCD8
RwInt32 dword_4EBCD8;
// 0x004EBCDC
RwInt32 dword_4EBCDC;
// 0x004EBCE0
const RwChar *dword_4EBCE0[5];
// 0x004EBCF4
void *pBlock;
// 0x004EBCF8
RwV2d dword_4EBCF8;
// 0x004EBD00
RwInt32 dword_4EBD00;
// 0x004EBD04
void *dword_4EBD04;
// 0x004EBD08
RwV2d dword_4EBD08;
// 0x004EBD10
RwRGBA dword_4EBD10;
// 0x004EBD14
RwRGBA dword_4EBD14;
// 0x004EBD18
RwInt32 dword_4EBD18;
// 0x004EBD1C
RwInt32 dword_4EBD1C;
// 0x004EBD20
RwRGBA dword_4EBD20;
// 0x004EBD24
RwRGBA dword_4EBD24;
// 0x004EBD28
RwInt32 dword_4EBD28;
// 0x004EBD2C
struct type_DA580 *dword_4EBD2C;
// 0x004EBD30
RwInt32 dword_4EBD30;
// 0x004EBD34
RwInt32 dword_4EBD34;
// 0x004EBD38
RwInt32 dword_4EBD38[0x2C];
// 0x004EBDE8
RwRGBA dword_4EBDE8;
// 0x004EBDEC
RwInt32 dword_4EBDEC;
// 0x004EBDF0
RwInt32 dword_4EBDF0;
// 0x004EBDF4
RwUInt8 byte_4EBDF4;
// 0x004F3168
#ifndef CODFH_PLAIN
RwInt32 dword_4F3168;
#endif
// End of its data definitions.


// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).
type_4EBE00 dword_4EBE00[2];
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3DE8E4@@3MB @ 0x003DE8E4
// match: ?flt_3DE8E8@@3MB @ 0x003DE8E8
// match: ??_C@_0CH@EIFECLFC@COD_InGameText?$CLEvent_NoControlle@ @ 0x003DE8EC
// match: ??_C@_0CH@HBFLNJF@COD_InGameText?$CLEvent_NoControlle@ @ 0x003DE914
// match: ??_C@_0CH@BOAOIMNE@COD_InGameText?$CLEvent_NoControlle@ @ 0x003DE93C
// match: ??_C@_0CH@DFCDNPBH@COD_InGameText?$CLEvent_NoControlle@ @ 0x003DE964
// match: ??_C@_0CI@DACDFDMF@COD_InGameText?$CLEvent_OptMenuSetD@ @ 0x003DE98C
// match: ??_C@_0CH@KHEJFOCG@COD_InGameText?$CLEvent_OptMenuFFir@ @ 0x003DE9B4
// match: ??_C@_0CG@DIOCEGAK@COD_InGameText?$CLEvent_OptMenuAimA@ @ 0x003DE9DC
// match: ??_C@_0CJ@MHCKIMJC@COD_InGameText?$CLEvent_OptMenuItem@ @ 0x003DEA04
// match: ??_C@_0CM@HOHOPIMC@COD_InGameText?$CLEvent_OptMenuCont@ @ 0x003DEA30
// match: ??_C@_0CI@JFGAEJHJ@COD_InGameText?$CLEvent_OptMenuInve@ @ 0x003DEA5C
// match: ??_C@_0CK@DJHGOPBH@COD_InGameText?$CLEvent_OptMenuItem@ @ 0x003DEA84
// match: ??_C@_0CK@BIPECEFO@COD_InGameText?$CLEvent_OptMenuItem@ @ 0x003DEAB0
// match: ??_C@_0CK@BOPBFBP@COD_InGameText?$CLEvent_OptMenuItem@ @ 0x003DEADC
// match: ??_C@_0CK@EOKOIDNI@COD_InGameText?$CLEvent_OptMenuItem@ @ 0x003DEB08
// match: ??_C@_0CK@FHLFLCJJ@COD_InGameText?$CLEvent_OptMenuItem@ @ 0x003DEB34
// match: ??_C@_0CK@HMJIOBFK@COD_InGameText?$CLEvent_OptMenuItem@ @ 0x003DEB60
// match: ??_C@_0CO@NIKHBLBL@COD_InGameText?$CLEvent_OptMenuItem@ @ 0x003DEB8C
// match: ??_C@_0CN@MEAELOCF@COD_InGameText?$CLEvent_OptMenuItem@ @ 0x003DEBBC
// match: ??_C@_0CN@IOGJEBPI@COD_InGameText?$CLEvent_OptMenuItem@ @ 0x003DEBEC
// match: ??_C@_0CN@KAHPHHNN@COD_InGameText?$CLEvent_OptMenuItem@ @ 0x003DEC1C
// match: ??_C@_0CK@EMFFEPNC@COD_InGameText?$CLEvent_OptMenuItem@ @ 0x003DEC4C
// match: ??_C@_0CM@MPNHPBEN@COD_InGameText?$CLEvent_OptMenuItem@ @ 0x003DEC78
// match: ??_C@_0CN@GJJKKCFG@COD_InGameText?$CLEvent_OptMenuItem@ @ 0x003DECA4
// match: ??_C@_0CL@PPIHNFPM@COD_InGameText?$CLEvent_OptMenuItem@ @ 0x003DECD4
// match: ??_C@_0CG@ELANFOGF@COD_InGameText?$CLEvent_OptMenuItem@ @ 0x003DED00
// match: ??_C@_0CI@NOPCOPEP@COD_InGameText?$CLEvent_OptionsMenu@ @ 0x003DED28
// match: ??_C@_0CI@CDHKMKGF@COD_InGameText?$CLEvent_RestartMenu@ @ 0x003DED50
// match: ??_C@_0CF@JPPPHDGK@COD_InGameText?$CLEvent_QuitMenuHea@ @ 0x003DED78
// match: ??_C@_0CK@PBLIKPCG@COD_InGameText?$CLEvent_PauseMenuIt@ @ 0x003DEDA0
// match: ??_C@_0CH@MJFFDNHA@COD_InGameText?$CLEvent_PauseMenuIt@ @ 0x003DEDCC
// match: ??_C@_0CK@BMDHOANO@COD_InGameText?$CLEvent_PauseMenuIt@ @ 0x003DEDF4
// match: ??_C@_0CG@COJIEFIE@COD_InGameText?$CLEvent_PauseMenuHe@ @ 0x003DEE20
// match: ??_C@_0CG@ENCAOGEJ@COD_InGameText?$CLEvent_MenuChangeO@ @ 0x003DEE48
// match: ??_C@_0CB@KKNEIEKF@COD_InGameText?$CLEvent_MenuUnPause@ @ 0x003DEE70
// match: ??_C@_0CC@PEMDMOHL@COD_InGameText?$CLEvent_MenuNavigat@ @ 0x003DEE94
// match: ??_C@_0CA@HDCMBHBK@COD_InGameText?$CLEvent_MenuCancel?$AA@ @ 0x003DEEB8
// match: ??_C@_0CA@NDDHCPCL@COD_InGameText?$CLEvent_MenuAction?$AA@ @ 0x003DEED8
// match: ??_C@_0CK@BNBOPONP@COD_InGameText?$CLEvent_MenuGeneric@ @ 0x003DEEF8
// match: ??_C@_0CJ@PJNMDJNN@COD_InGameText?$CLEvent_MenuGeneric@ @ 0x003DEF24
// match: ??_C@_0CI@JOOPMPJ@COD_InGameText?$CLEvent_MenuGeneric@ @ 0x003DEF50
// match: ??_C@_0CI@BBDHKHIP@COD_InGameText?$CLEvent_MenuGeneric@ @ 0x003DEF78
// match: ??_C@_0CJ@LJFNGJND@COD_InGameText?$CLEvent_MenuGeneric@ @ 0x003DEFA0
// match: __real@3fe66666 @ 0x003DEFCC
// match: __real@4107b6db @ 0x003DEFD0
// match: __real@41510000 @ 0x003DEFD4
// match: __real@418e8000 @ 0x003DEFD8
// match: __real@41b00000 @ 0x003DEFDC
// match: .CRT$XCU+0 @ 0x00427178
// match: ?dword_42B470@@3PAURwRGBA@@A @ 0x0042B470
// match: ?flt_42B478@@3MA @ 0x0042B478
// match: ?flt_42B47C@@3MA @ 0x0042B47C
// match: ?flt_42B480@@3MA @ 0x0042B480
// match: ?flt_42B484@@3MA @ 0x0042B484
// match: ?flt_42B488@@3MA @ 0x0042B488
// match: ?dword_42B490@@3PAY02Utype_42B490@@A @ 0x0042B490
// match: ?byte_42B4FC@@3PADA @ 0x0042B4FC
// match: ?flt_42B510@@3MA @ 0x0042B510

// match: _$E2 @ 0x0030BFA0

// The screen's backdrop colour (in .data).
extern RwRGBA dword_42B470[2];

// match: ?sub_185C30@@YAXPAURwCamera@@_NP6AX0PAX@Z2@Z @ 0x00185C30
// One frame of a waiting screen for the camera arg_0: the pads read, the
// front end's music kept (track 0x2C started while no pad is in, faded when
// one is, when arg_4), the front end's step, the screen cleared, arg_8's
// draw with arg_C, the HUD's, shown; then the sounds and the files.
void sub_185C30(RwCamera *arg_0, bool arg_4, void (*arg_8)(RwCamera *, void *), void *arg_C)
{
    unk_4B9308.sub_EE6D0();
    if (arg_4)
    {
        if (!dword_42926C && sub_188350() != 0x2C)
            sub_186E70(0x2C, 0, 0);
        else if (dword_42926C && sub_188350() == 0x2C)
            sub_186F80(0x2C, 1);
    }
    sub_187B30();
    RwCameraClear(arg_0, dword_42B470, 3);
    if (arg_8)
        arg_8(arg_0, arg_C);
    sub_187150((RwInt32)arg_0);
    RwRasterShowRaster(arg_0->frameBuffer, 0, 1);
    sub_D9620();
    RwaCoreUpdate();
    RwaCoreUpdate();
    RtFSManagerSyncAllFiles();
    sub_19A750();
}

// match: ?sub_185CF0@@YAXPAHPAURwCamera@@P6AX1PAX@Z2@Z @ 0x00185CF0
// Runs waiting frames (the music kept after half a second) until *arg_0 is
// set or the memory unit operation ends, which sets it to 3.
void sub_185CF0(RwInt32 *arg_0, RwCamera *arg_4, void (*arg_8)(RwCamera *, void *), void *arg_C)
{
    RwUInt32 var_4;

    var_4 = RWS::Time::GetTime() + 500;
    while (!*arg_0 && sub_186D00())
        sub_185C30(arg_4, RWS::Time::GetTime() >= var_4, arg_8, arg_C);
    if (!sub_186D00())
        *arg_0 = 3;
}

// match: ?sub_185D50@@YAHPAURwCamera@@PAUtype_D9CF0@@P6AX0PAX@Z2_N@Z @ 0x00185D50
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Looks for the memory card: 1 at once on this build. The retry loop after
// the return (message 5, a second's wait, the card's search and, when asked
// and found, its format after message 0x1A and the save's check) is still
// compiled.
RwInt32 sub_185D50(RwCamera *arg_0, type_D9CF0 *arg_4, void (*arg_8)(RwCamera *, void *), void *arg_C,
                   bool arg_10)
{
    type_186E70 l1C;
    RwInt32 ebp_14;
    RwUInt32 lv_10;
    RwInt32 var_C;

    return 1;
    // A check compiled out of this build (it moves the registers one step).
    if (byte_4B8894)
    {
    }
    const RwInt32 bp_8 = 1;
    RwInt32 bp_4;

    while (bp_8)
    {
        byte_4B8894 = 0;
        sub_186E70(5, 0, 0);
        sub_187B30();
        for (ebp_14 = 0; ebp_14 < 2; ebp_14++)
        {
            RwCameraClear(arg_0, dword_42B470, 3);
            if (arg_8)
                arg_8(arg_0, arg_C);
            sub_187150((RwInt32)arg_0);
            RwRasterShowRaster(arg_0->frameBuffer, 0, 1);
        }
        lv_10 = RWS::Time::GetTime() + 1000;
        while (RWS::Time::GetTime() < lv_10)
            ;
        if (bp_4 != -2)
            bp_4 = arg_4->sub_D9D30();
        byte_4EBCC8 = 1;
        byte_4EBCC9 = 0;
        var_C = 0;
        if ((bp_4 == 0 || bp_4 == -2) && arg_10)
            var_C = arg_4->sub_DA200();
        else
        {
            lv_10 = RWS::Time::GetTime() + 1000;
            while (RWS::Time::GetTime() < lv_10)
                ;
        }
        sub_187040();
        sub_187B30();
        if (var_C == 3 || var_C == 2)
        {
            l1C.unk_00 = 0;
            l1C.unk_04 = 0;
            sub_186E70(0x1A, &l1C, 0);
            sub_185CF0(&l1C.unk_00, arg_0, arg_8, arg_C);
            sub_187040();
            sub_187B30();
            if (sub_186020(arg_0, arg_4, 0, arg_8, arg_C) == 0)
            {
                byte_4EBCC9 = 1;
                byte_4B8894 = 1;
                dword_4EBCCC = -6;
                return -6;
            }
            bp_4 = 0;
        }
        else
        {
            return bp_4;
        }
    }
    return bp_4;
}

// match: ?sub_185F30@@YAXPAURwCamera@@P6AX0PAX@Z1@Z @ 0x00185F30
// Shows message 0x1C until answered.
void sub_185F30(RwCamera *arg_0, void (*arg_4)(RwCamera *, void *), void *arg_8)
{
    type_186E70 var_8;

    var_8.unk_00 = 0;
    var_8.unk_04 = 0;
    sub_186E70(0x1C, &var_8, 0);
    sub_185CF0(&var_8.unk_00, arg_0, arg_4, arg_8);
    sub_187040();
    sub_187B30();
}

// match: ?sub_185F80@@YAXPAURwCamera@@P6AX0PAX@Z1@Z @ 0x00185F80
// Shows message 8 until answered.
void sub_185F80(RwCamera *arg_0, void (*arg_4)(RwCamera *, void *), void *arg_8)
{
    type_186E70 var_8;

    var_8.unk_00 = 0;
    var_8.unk_04 = 0;
    sub_186E70(8, &var_8, 0);
    sub_185CF0(&var_8.unk_00, arg_0, arg_4, arg_8);
    sub_187040();
    sub_187B30();
}

// match: ?sub_185FD0@@YAXPAURwCamera@@P6AX0PAX@Z1@Z @ 0x00185FD0
// Shows message 0x20 until answered.
void sub_185FD0(RwCamera *arg_0, void (*arg_4)(RwCamera *, void *), void *arg_8)
{
    type_186E70 var_8;

    var_8.unk_00 = 0;
    var_8.unk_04 = 0;
    sub_186E70(0x20, &var_8, 0);
    sub_185CF0(&var_8.unk_00, arg_0, arg_4, arg_8);
    sub_187040();
    sub_187B30();
}

// match: ?sub_186020@@YA?AUtype_186020@@PAURwCamera@@PAUtype_D9CF0@@_NP6AX0PAX@Z3@Z @ 0x00186020
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Whether to save: unless already declined, message 0x1F; with arg_8 the
// card is looked for (-2: message 0x1C, and 4 with the result); a yes is
// 1, a no remembered in byte_4EBCC9.
type_186020 sub_186020(RwCamera *arg_0, type_D9CF0 *arg_4, bool arg_8, void (*arg_C)(RwCamera *, void *),
                       void *arg_10)
{
    RwInt32 var_C;
    type_186E70 bp_8;

    if (byte_4EBCC9)
    {
        sub_185F80(arg_0, arg_C, arg_10);
        return type_186020(0, 0);
    }
    bp_8.unk_00 = 0;
    bp_8.unk_04 = 0;
    sub_186E70(0x1F, &bp_8, 0);
    sub_185CF0(&bp_8.unk_00, arg_0, arg_C, arg_10);
    sub_187040();
    sub_187B30();
    if (arg_8)
    {
        var_C = sub_185D50(0, arg_4, 0, 0, 0);
        if (var_C == -2)
        {
            sub_185F30(arg_0, arg_C, arg_10);
            return type_186020(4, var_C);
        }
    }
    if (bp_8.unk_00 == 1)
    {
        byte_4EBCC9 = 1;
        return type_186020(0, 0);
    }
    byte_4EBCC9 = 0;
    return type_186020(1, 0);
}

// match: ?sub_186140@@YA?AUtype_186020@@PAURwCamera@@PAUtype_D9CF0@@H_NHPAXP6AX03@Z3@Z @ 0x00186140
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Saves into slot arg_8 of the card arg_4 (message 0xE with arg_14 shown
// for two frames unless saving is off, then a second's wait): 0 on this
// build. The retry loop after the return (the card's search, a full card's
// prompt, a name already used in another slot, the save and its failure or
// success messages) is still compiled.
type_186020 sub_186140(RwCamera *arg_0, type_D9CF0 *arg_4, RwInt32 arg_8, bool arg_C, RwInt32 arg_10,
                       void *arg_14, void (*arg_18)(RwCamera *, void *), void *arg_1C)
{
    RwInt32 y14;
    RwUInt32 var_C;
    RwInt32 bp_8;
    RwInt32 bp_4;

    if (!dword_4F5A30)
    {
        sub_186E70(0xE, arg_14, 0);
        sub_187B30();
        for (bp_8 = 0; bp_8 < 2; bp_8++)
        {
            RwCameraClear(arg_0, dword_42B470, 3);
            if (arg_18)
                arg_18(arg_0, arg_1C);
            sub_187150((RwInt32)arg_0);
            RwRasterShowRaster(arg_0->frameBuffer, 0, 1);
        }
    }
    bp_4 = arg_4->sub_D9E50(arg_8);
    if (!dword_4F5A30)
    {
        var_C = RWS::Time::GetTime() + 1000;
        while (RWS::Time::GetTime() < var_C)
            ;
        sub_187040();
        sub_187B30();
    }
    return type_186020(0, 0);
    // A check compiled out of this build (it moves the registers one step).
    if (byte_4B8894)
    {
    }
    const RwInt32 r10 = 1;
    while (r10)
    {
        y14 = sub_185D50(arg_0, arg_4, arg_18, arg_1C, 0);
        if (y14 == -2)
        {
            sub_185F30(arg_0, arg_18, arg_1C);
            return type_186020(4, y14);
        }
        if (y14 == 0 && !arg_4->sub_DA230())
        {
            type_186020 var_1C = sub_186630(arg_0, arg_4, arg_C, 1, arg_18, arg_1C);

            if (var_1C == 3)
                return var_1C;
            if (var_1C == 1)
            {
                type_186020 var_24 = sub_186020(arg_0, arg_4, 0, arg_18, arg_1C);

                if (var_24 == 0)
                    return type_186020(1, 0);
                if (var_24 == 4)
                    return var_24;
            }
        }
        else if (y14 == 0)
        {
            RwChar var6C[4][12];
            type_186E70_08 l80;
            RwInt32 var_74;
            RwInt32 var70;
            RwInt32 local_38;
            RwInt32 local_34[4];

            memset(var6C, 0, 0x30);
            arg_4->sub_D9D60(local_34, var6C);
            for (var70 = 0; var70 < 4; var70++)
            {
                if (!strcmp(var6C[var70], dword_4F28F0->unk_48) && var70 != arg_8)
                {
                    sub_185FD0(arg_0, arg_18, arg_1C);
                    return type_186020(3, 0);
                }
            }
            sub_186E70(0xE, arg_14, 0);
            sub_187B30();
            for (var_74 = 0; var_74 < 2; var_74++)
            {
                RwCameraClear(arg_0, dword_42B470, 3);
                if (arg_18)
                    arg_18(arg_0, arg_1C);
                sub_187150((RwInt32)arg_0);
                RwRasterShowRaster(arg_0->frameBuffer, 0, 1);
            }
            local_38 = arg_4->sub_D9E50(arg_8);
            sub_187040();
            sub_187B30();
            if (local_38)
            {
                l80.unk_00 = 0;
                l80.unk_04 = 0;
                l80.unk_08 = arg_14;
                l80.unk_04 = arg_C;
                sub_186E70(0x10, &l80, 0);
                sub_185CF0(&l80.unk_00, arg_0, arg_18, arg_1C);
                sub_187040();
                sub_187B30();
                if (l80.unk_00 == 3)
                    return type_186020(3, 0);
                if (l80.unk_00 == 1)
                {
                    type_186020 var_88 = sub_186020(arg_0, arg_4, 0, arg_18, arg_1C);

                    if (var_88 == 0)
                        return type_186020(1, 0);
                    if (var_88 == 4)
                        return var_88;
                }
            }
            else
            {
                type_186E70_08 var_94;

                var_94.unk_00 = 0;
                var_94.unk_04 = 0;
                var_94.unk_08 = arg_14;
                sub_186E70(0xF, &var_94, 0);
                sub_185CF0(&var_94.unk_00, arg_0, arg_18, arg_1C);
                sub_187040();
                sub_187B30();
                return type_186020(0, 0);
            }
        }
    }
    return type_186020(1, 0);
}

// match: ?sub_186630@@YA?AUtype_186020@@PAURwCamera@@PAUtype_D9CF0@@_N2P6AX0PAX@Z3@Z @ 0x00186630
// The full card's prompt (message 0x18, or 0x19 with arg_C): 1 to go on, 2
// on its fourth choice, else 3.
type_186020 sub_186630(RwCamera *arg_0, type_D9CF0 *arg_4, bool arg_8, bool arg_C,
                       void (*arg_10)(RwCamera *, void *), void *arg_14)
{
    type_186E70 var_8;

    var_8.unk_00 = 0;
    var_8.unk_04 = 0;
    var_8.unk_04 = arg_8;
    sub_186E70(0x18 + (arg_C ? 1 : 0), &var_8, 0);
    sub_185CF0(&var_8.unk_00, arg_0, arg_10, arg_14);
    sub_187040();
    sub_187B30();
    if (var_8.unk_00 == 1)
        return type_186020(1, 0);
    if (var_8.unk_00 == 4)
        return type_186020(2, 0);
    return type_186020(3, 0);
}

// match: ?sub_1866E0@@YA?AUtype_186020@@PAURwCamera@@PAUtype_D9CF0@@HP6AX0PAX@Z2@Z @ 0x001866E0
// The checkpoint's save into the save state's slot (arg_8 unused).
type_186020 sub_1866E0(RwCamera *arg_0, type_D9CF0 *arg_4, RwInt32 arg_8, void (*arg_C)(RwCamera *, void *),
                       void *arg_10)
{
    RwInt32 var_4;

    var_4 = dword_4F28F0->unk_44;
    return sub_186140(arg_0, arg_4, var_4, 0, 0, 0, arg_C, arg_10);
}

// match: ?sub_186720@@YAXXZ @ 0x00186720
// Sets the message boxes up: none open, their colours and layout, no text.
void sub_186720()
{
    RwInt32 var_4;

    dword_4EBD34 = -1;
    dword_4EBD2C = 0;
    dword_4EBCD8 = 0;
    dword_4EBD14.red = dword_4EBD14.green = dword_4EBD14.blue = dword_4EBD14.alpha = 200;
    dword_4EBD10.red = dword_4EBD10.green = dword_4EBD10.blue = dword_4EBD10.alpha = 255;
    dword_4EBD20.red = dword_4EBD20.green = dword_4EBD20.blue = 0;
    dword_4EBD20.alpha = 232;
    dword_4EBDE8.red = dword_4EBDE8.green = dword_4EBDE8.blue = 75;
    dword_4EBDE8.alpha = 200;
    dword_4EBD24.red = dword_4EBD24.green = dword_4EBD24.blue = dword_4EBD24.alpha = 255;
    dword_4EBCF8.x = 0;
    dword_4EBCF8.y = 0;
    dword_4EBD08.x = 0;
    dword_4EBD08.y = 60.0f;
    dword_4EBCDC = 0;
    for (var_4 = 0; var_4 < 5; var_4++)
        dword_4EBCE0[var_4] = 0;
    pBlock = 0;
    dword_4EBD30 = 1;
}

// match: ?sub_186880@@YA_NH@Z @ 0x00186880
bool sub_186880(RwInt32 arg_0)
{
    if (pBlock && !arg_0)
    {
        free(pBlock);
        pBlock = 0;
    }
    if (arg_0)
        byte_4EBDF4 = 1;
    pBlock = sub_18AF40((RwChar *)arg_0);
    return pBlock != 0;
}

// match: ?sub_1868E0@@YAXXZ @ 0x001868E0
// Shuts the message boxes down (the text freed unless kept).
void sub_1868E0()
{
    dword_4EBD34 = -1;
    dword_4EBD2C = 0;
    dword_4EBCD8 = 0;
    sub_186E10();
    if (pBlock && !byte_4EBDF4)
    {
        free(pBlock);
        pBlock = 0;
    }
    byte_4EBDF4 = 0;
    dword_4EBD30 = 0;
}

// match: ?sub_186950@@YAXXZ @ 0x00186950
// Closes the message box and shows them.
void sub_186950()
{
    dword_4EBD34 = -1;
    dword_4EBCD8 = 1;
}

// match: ?sub_186970@@YAXPAUtype_DA580@@@Z @ 0x00186970
void sub_186970(type_DA580 *arg_0)
{
    dword_4EBD2C = arg_0;
}

// match: ?sub_186980@@YAXXZ @ 0x00186980
// Registers the in-game menus' text events (their Yes, No and so on, the
// pause, quit, restart and options menus, and the no-controller lines).
void sub_186980()
{
    sub_1989D0("COD_InGameText+Event_MenuGenericText_Yes", 0x32, 0, 0, 0);
    sub_1989D0("COD_InGameText+Event_MenuGenericText_No", 0x32, 0, 0, 0);
    sub_1989D0("COD_InGameText+Event_MenuGenericText_On", 0x32, 0, 0, 0);
    sub_1989D0("COD_InGameText+Event_MenuGenericText_Off", 0x32, 0, 0, 0);
    sub_1989D0("COD_InGameText+Event_MenuGenericText_Back", 0x32, 0, 0, 0);
    sub_1989D0("COD_InGameText+Event_MenuAction", 0x32, 0, 0, 0);
    sub_1989D0("COD_InGameText+Event_MenuCancel", 0x32, 0, 0, 0);
    sub_1989D0("COD_InGameText+Event_MenuNavigate", 0x32, 0, 0, 0);
    sub_1989D0("COD_InGameText+Event_MenuUnPause", 0x32, 0, 0, 0);
    sub_1989D0("COD_InGameText+Event_MenuChangeOption", 0x32, 0, 0, 0);
    sub_1989D0("COD_InGameText+Event_PauseMenuHeading", 0x32, 0, 0, 0);
    sub_1989D0("COD_InGameText+Event_PauseMenuItemOptions", 0x32, 0, 0, 0);
    sub_1989D0("COD_InGameText+Event_PauseMenuItemQuit", 0x32, 0, 0, 0);
    sub_1989D0("COD_InGameText+Event_PauseMenuItemRestart", 0x32, 0, 0, 0);
    sub_1989D0("COD_InGameText+Event_QuitMenuHeading", 0x32, 0, 0, 0);
    sub_1989D0("COD_InGameText+Event_RestartMenuHeading", 0x32, 0, 0, 0);
    sub_1989D0("COD_InGameText+Event_OptionsMenuHeading", 0x32, 0, 0, 0);
    sub_1989D0("COD_InGameText+Event_OptMenuItemSound", 0x32, 0, 0, 0);
    sub_1989D0("COD_InGameText+Event_OptMenuItemSound_Mono", 0x32, 0, 0, 0);
    sub_1989D0("COD_InGameText+Event_OptMenuItemSound_Stereo", 0x32, 0, 0, 0);
    sub_1989D0("COD_InGameText+Event_OptMenuItemSound_Dolby", 0x32, 0, 0, 0);
    sub_1989D0("COD_InGameText+Event_OptMenuItemTurnSpeed", 0x32, 0, 0, 0);
    sub_1989D0("COD_InGameText+Event_OptMenuItemTurnSpd_Slow", 0x32, 0, 0, 0);
    sub_1989D0("COD_InGameText+Event_OptMenuItemTurnSpd_Norm", 0x32, 0, 0, 0);
    sub_1989D0("COD_InGameText+Event_OptMenuItemTurnSpd_Fast", 0x32, 0, 0, 0);
    sub_1989D0("COD_InGameText+Event_OptMenuItemControlConfig", 0x32, 0, 0, 0);
    sub_1989D0("COD_InGameText+Event_OptMenuItemCtlr_Set1", 0x32, 0, 0, 0);
    sub_1989D0("COD_InGameText+Event_OptMenuItemCtlr_Set2", 0x32, 0, 0, 0);
    sub_1989D0("COD_InGameText+Event_OptMenuItemCtlr_Set3", 0x32, 0, 0, 0);
    sub_1989D0("COD_InGameText+Event_OptMenuItemCtlr_Set4", 0x32, 0, 0, 0);
    sub_1989D0("COD_InGameText+Event_OptMenuItemCtlr_Set5", 0x32, 0, 0, 0);
    sub_1989D0("COD_InGameText+Event_OptMenuItemSubtitles", 0x32, 0, 0, 0);
    sub_1989D0("COD_InGameText+Event_OptMenuInvertYAxis", 0x32, 0, 0, 0);
    sub_1989D0("COD_InGameText+Event_OptMenuControllerShake", 0x32, 0, 0, 0);
    sub_1989D0("COD_InGameText+Event_OptMenuItemHintMsgs", 0x32, 0, 0, 0);
    sub_1989D0("COD_InGameText+Event_OptMenuAimAssist", 0x32, 0, 0, 0);
    sub_1989D0("COD_InGameText+Event_OptMenuFFireBlock", 0x32, 0, 0, 0);
    sub_1989D0("COD_InGameText+Event_OptMenuSetDefaults", 0x32, 0, 0, 0);
    sub_1989D0("COD_InGameText+Event_NoControllerLine1", 0x32, 0, 0, 0);
    sub_1989D0("COD_InGameText+Event_NoControllerLine2", 0x32, 0, 0, 0);
    sub_1989D0("COD_InGameText+Event_NoControllerLine3", 0x32, 0, 0, 0);
    sub_1989D0("COD_InGameText+Event_NoControllerLine4", 0x32, 0, 0, 0);
}

// match: ?sub_186D00@@YAHXZ @ 0x00186D00
// How many message boxes are open.
RwInt32 sub_186D00()
{
    return dword_4EBD34 + 1;
}

// match: ?sub_186D10@@YAPAUtype_4EBE00@@XZ @ 0x00186D10
// Opens the next message box (reset, with the font).
type_4EBE00 *sub_186D10()
{
    dword_4EBD34 = dword_4EBD34 + 1;
    dword_4EBE00[dword_4EBD34].sub_1883B0();
    dword_4EBE00[dword_4EBD34].sub_1888F0((RwCamera *)dword_4EBD04, 0);
    dword_4EBE00[dword_4EBD34].unk_00 = 1;
    dword_4EBE00[dword_4EBD34].unk_18 = 0;
    return &dword_4EBE00[dword_4EBD34];
}

// match: ?sub_186DA0@@YAXXZ @ 0x00186DA0
// With the first box open, holds the pad bindings (clearing them).
void sub_186DA0()
{
    RwInt32 var_4;

    if (dword_4EBD34 == 0 && !dword_4EBCDC)
    {
        dword_4EBCDC = 1;
        for (var_4 = 0; var_4 < 0x2C; var_4++)
        {
            dword_4EBD38[var_4] = dword_429498[var_4].unk_04;
            dword_429498[var_4].unk_04 = 0;
        }
    }
}

// match: ?sub_186E10@@YAXXZ @ 0x00186E10
// With none open, puts the pad bindings back.
void sub_186E10()
{
    RwInt32 var_4;

    if (dword_4EBD34 == -1 && dword_4EBCDC)
    {
        for (var_4 = 0; var_4 < 0x2C; var_4++)
            dword_429498[var_4].unk_04 = dword_4EBD38[var_4];
        dword_4EBCDC = 0;
    }
}

// match: ?sub_186E70@@YAHHPAX0@Z @ 0x00186E70
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Opens message arg_0 with arg_4 (its opener from off_42B518), in the font
// arg_8 (kept) or the last; 0 without a font or an opener.
RwInt32 sub_186E70(RwInt32 arg_0, void *arg_4, void *arg_8)
{
    type_42B518 *var_8;
    type_4EBE00 *l4;

    if (arg_8)
        dword_4EBD04 = arg_8;
    if (!dword_4EBD04)
        return 0;
    sub_1882C0();
    sub_1882C0();
    l4 = sub_186D10();
    for (var_8 = off_42B518; var_8->unk_00 != -1; var_8++)
    {
        if (var_8->unk_00 == arg_0)
        {
            if (var_8->unk_04)
            {
                l4->unk_2CDC = arg_0;
                var_8->unk_04(l4, (RwInt32)arg_4);
            }
            break;
        }
    }
    if (var_8->unk_00 == -1)
    {
        dword_4EBD34 = dword_4EBD34 - 1;
        return 0;
    }
    sub_186DA0();
    return 1;
}

// match: ?sub_186F20@@YAHH@Z @ 0x00186F20
// Whether message arg_0 is open.
RwInt32 sub_186F20(RwInt32 arg_0)
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 2; var_4++)
    {
        if (dword_4EBE00[var_4].unk_00 && arg_0 == dword_4EBE00[var_4].unk_2CDC)
            return 1;
    }
    return 0;
}

// match: ?sub_186F80@@YAXHH@Z @ 0x00186F80
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Closes message arg_0 (the top one popped, with the player's close sound
// when arg_4).
void sub_186F80(RwInt32 arg_0, RwInt32 arg_4)
{
    type_3D3548 *var_8;
    RwInt32 l4;

    for (l4 = 0; l4 <= dword_4EBD34; l4++)
    {
        if (dword_4EBE00[l4].unk_2CDC == arg_0)
        {
            dword_4EBE00[l4].sub_188490();
            if (l4 == dword_4EBD34)
            {
                dword_4EBD34 = dword_4EBD34 - 1;
                if (arg_4)
                {
                    var_8 = sub_1745A0(0);
                    if (var_8)
                        var_8->unk_1C0.sub_8A980(&dword_4B1B48, var_8, 1, var_8->sub_CD550(), 0, 0);
                }
            }
        }
    }
    sub_186E10();
}

// match: ?sub_187040@@YAXXZ @ 0x00187040
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Closes every message box, with the close sound.
void sub_187040()
{
    type_3D3548 *var_8;
    RwInt32 l4;

    if (dword_4EBD34 == -1)
        return;
    for (l4 = dword_4EBD34; l4 > -1; l4--)
        dword_4EBE00[l4].sub_188490();
    var_8 = sub_1745A0(0);
    if (var_8)
        var_8->unk_1C0.sub_8A980(&dword_4B1B48, var_8, 1, var_8->sub_CD550(), 0, 0);
    dword_4EBD34 = -1;
    sub_186E10();
}

// match: ?sub_1870D0@@YAXXZ @ 0x001870D0
// Closes the top message box, with the close sound.
void sub_1870D0()
{
    type_3D3548 *var_4;

    if (dword_4EBD34 == -1)
        return;
    dword_4EBE00[dword_4EBD34].sub_188490();
    dword_4EBD34 = dword_4EBD34 - 1;
    var_4 = sub_1745A0(0);
    if (var_4)
        var_4->unk_1C0.sub_8A980(&dword_4B1B48, var_4, 1, var_4->sub_CD550(), 0, 0);
    sub_186E10();
}

// match: ?sub_187150@@YAXH@Z @ 0x00187150
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Draws the top message box on the camera arg_0 (kept for the boxes) while
// they are shown with a font: a 384 by 448 screen, the text scaled to at
// least 1.8, alpha blending and no depth, then the states put back.
void sub_187150(RwInt32 arg_0)
{
    RwReal var_30;
    RwInt32 var_2C;
    RwInt32 var_28;
    RwInt32 ebp_24;
    RwInt32 var_20;
    RwInt32 l1C;
    RwInt32 m_18;
    RwInt32 ebp_14;
    RwInt32 lv_10;
    RwInt32 var_C;
    RwInt32 bp_8;
    RwInt32 bp_4;

    dword_4EBD04 = (void *)arg_0;
    if (!dword_4EBD30 || !dword_4EBD2C || dword_4EBD34 == -1)
        return;
    RwCameraBeginUpdate((RwCamera *)arg_0);
    Rt2dCTMPush();
    Rt2dCTMSetIdentity();
    Rt2dCTMScale(1.0f / 384.0f, 1.0f / 448.0f);
    var_30 = flt_4292C8;
    if (var_30 < 1.8f)
        flt_4292C8 = 1.8f;
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
    RwRenderStateSet(rwRENDERSTATESRCBLEND, (void *)5);  // rwBLENDSRCALPHA
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void *)6); // rwBLENDINVSRCALPHA
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)1);
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void *)0);
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void *)0);
    RwRenderStateSet(rwRENDERSTATESHADEMODE, (void *)2);       // rwSHADEMODEGOURAUD
    RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, (void *)2);   // rwFILTERLINEAR
    RwRenderStateSet(rwRENDERSTATECULLMODE, (void *)rwCULLMODECULLNONE);
    RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void *)0);
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void *)0);
    RwRenderStateSet(rwRENDERSTATETEXTUREADDRESS, (void *)3);  // rwTEXTUREADDRESSCLAMP
    if (dword_4EBE00[dword_4EBD34].unk_00)
    {
        sub_187400(&dword_4EBE00[dword_4EBD34]);
        if (dword_4EBE00[dword_4EBD34].unk_2CE4)
            sub_187800();
    }
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void *)var_2C);
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void *)l1C);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)var_C);
    RwRenderStateSet(rwRENDERSTATESRCBLEND, (void *)var_28);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void *)ebp_24);
    RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void *)m_18);
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void *)bp_8);
    RwRenderStateSet(rwRENDERSTATETEXTUREADDRESS, (void *)bp_4);
    RwRenderStateSet(rwRENDERSTATESHADEMODE, (void *)lv_10);
    RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, (void *)ebp_14);
    RwRenderStateSet(rwRENDERSTATECULLMODE, (void *)var_20);
    Rt2dCTMPop();
    flt_4292C8 = var_30;
}

// match: ?sub_187400@@YAXPAUtype_4EBE00@@@Z @ 0x00187400
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Draws the message box arg_0: its backdrop, its heading's backdrop when it
// has one and its frame, the heading lines (centred when set), then its
// lines each 20 below the last (a gap before the flagged one), the selected
// one highlighted when its choice is set.
void sub_187400(type_4EBE00 *arg_0)
{
    RwInt32 var_30;
    RwInt32 var_2C;
    RwV2d var_28;
    RwReal var_20;
    RwReal l1C;
    RwInt32 m_18;
    RwInt32 ebp_14;
    RwV2d lv_10;
    RwInt32 bp_8;
    RwInt32 bp_4;

    if (!arg_0->unk_00)
        return;
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void *)0);
    RwIm2DRenderPrimitive(rwPRIMTYPETRISTRIP, arg_0->unk_3C, 4);
    bp_8 = 0;
    for (bp_8 = 0; bp_8 < 5 && !arg_0->unk_27DC[bp_8][0]; bp_8++)
        ;
    if (bp_8 != 5)
        RwIm2DRenderPrimitive(rwPRIMTYPETRISTRIP, arg_0->unk_2CF4, 4);
    RwIm2DRenderPrimitive(rwPRIMTYPETRISTRIP, arg_0->unk_2F24, 4);
    RwIm2DRenderPrimitive(rwPRIMTYPETRISTRIP, arg_0->unk_2F94, 4);
    RwIm2DRenderPrimitive(rwPRIMTYPETRISTRIP, arg_0->unk_3004, 4);
    RwIm2DRenderPrimitive(rwPRIMTYPETRISTRIP, arg_0->unk_3074, 4);
    RwIm2DRenderPrimitive(rwPRIMTYPETRISTRIP, arg_0->unk_2D64, 4);
    RwIm2DRenderPrimitive(rwPRIMTYPETRISTRIP, arg_0->unk_2DD4, 4);
    RwIm2DRenderPrimitive(rwPRIMTYPETRISTRIP, arg_0->unk_2E44, 4);
    RwIm2DRenderPrimitive(rwPRIMTYPETRISTRIP, arg_0->unk_2EB4, 4);
    RwIm2DRenderPrimitive(rwPRIMTYPETRISTRIP, arg_0->unk_30E4, 4);
    RwIm2DRenderPrimitive(rwPRIMTYPETRISTRIP, arg_0->unk_3154, 4);
    RwIm2DRenderPrimitive(rwPRIMTYPETRISTRIP, arg_0->unk_31C4, 4);
    RwIm2DRenderPrimitive(rwPRIMTYPETRISTRIP, arg_0->unk_3234, 4);
    l1C = arg_0->unk_AC[1].y + 17.8125f;
    lv_10.x = arg_0->unk_AC[1].x + 10.0f;
    lv_10.y = l1C;
    for (bp_8 = 0; bp_8 < 5; bp_8++)
    {
        if (arg_0->unk_27DC[bp_8][0])
        {
            if (arg_0->unk_2CE0)
            {
                var_20 = dword_4EBD2C->sub_DA7B0(arg_0->unk_27DC[bp_8], 19.0f) * 0.5f;
                lv_10.x = (arg_0->unk_AC[1].x + arg_0->unk_AC[3].x) / 2.0f - var_20;
            }
            sub_1879F0(2, &lv_10, arg_0->unk_27DC[bp_8], 0);
            lv_10.y += 20.0f;
        }
    }
    lv_10.y = l1C;
    for (bp_8 = 0; bp_8 < 5; bp_8++)
    {
        if (arg_0->unk_27DC[bp_8][0])
            lv_10.y += 20.0f;
    }
    if (lv_10.y != l1C)
        lv_10.y += 13.0625f;
    ebp_14 = arg_0->unk_38;
    bp_4 = arg_0->unk_DC[ebp_14].unk_264;
    m_18 = 0;
    for (bp_8 = 0; bp_8 < arg_0->unk_2C; bp_8++)
    {
        var_30 = arg_0->unk_DC[bp_8].unk_26C;
        if (var_30 && !m_18)
        {
            lv_10.y += 8.4821424f;
            m_18 = 1;
        }
        var_28 = lv_10;
        var_2C = 0;
        if (bp_8 == ebp_14 && bp_4 != -1
            && (arg_0->unk_DC[ebp_14].unk_100[bp_4].unk_24 || arg_0->unk_DC[ebp_14].unk_100[bp_4].unk_1C))
            var_2C = 1;
        arg_0->unk_DC[bp_8].sub_18A1F0(var_2C, &lv_10, arg_0);
        lv_10.y += 20.0f;
    }
}

// match: ?sub_187800@@YAXXZ @ 0x00187800
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The top box's button bar: its labels looked up once ("Action",
// "Back", "Navigate", "UnPause", "ChangeOption"), then up to three of its
// buttons placed by their count, in slightly smaller text.
void sub_187800()
{
    RwV2d var_1C;
    RwInt32 var_14;
    RwInt32 lv_10;
    type_3DF8D8 *var_C;
    RwInt32 bp_8;
    RwInt32 bp_4;

    flt_4292C8 = 1.7f;
    if (!dword_4EBCE0[0])
    {
        var_C = 0;
        var_C = sub_198880("COD_InGameText+Event_MenuAction");
        if (var_C)
            dword_4EBCE0[3] = var_C->sub_197550(0, 0);
        var_C = sub_198880("COD_InGameText+Event_MenuGenericText_Back");
        if (var_C)
            dword_4EBCE0[4] = var_C->sub_197550(0, 0);
        var_C = sub_198880("COD_InGameText+Event_MenuNavigate");
        if (var_C)
            dword_4EBCE0[1] = var_C->sub_197550(0, 0);
        var_C = sub_198880("COD_InGameText+Event_MenuUnPause");
        if (var_C)
            dword_4EBCE0[0] = var_C->sub_197550(0, 0);
        var_C = sub_198880("COD_InGameText+Event_MenuChangeOption");
        if (var_C)
            dword_4EBCE0[2] = var_C->sub_197550(0, 0);
    }
    bp_4 = 0;
    for (lv_10 = 0; lv_10 < 5; lv_10++)
    {
        if (dword_4EBE00[dword_4EBD34].unk_04.unk_00[lv_10])
            bp_4++;
    }
    if (bp_4 > 3)
        bp_4 = 3;
    bp_8 = 0;
    for (var_14 = 0; bp_8 < bp_4 && var_14 < 5; var_14++)
    {
        if (dword_4EBE00[dword_4EBD34].unk_04.unk_00[var_14])
        {
            var_1C.x = dword_42B490[bp_4 - 1][bp_8].unk_00 * 512.0f;
            var_1C.y = dword_42B490[bp_4 - 1][bp_8].unk_04 * 448.0f;
            sub_1879F0(0, &var_1C, dword_4EBCE0[var_14], 0);
            bp_8++;
        }
    }
    flt_4292C8 = 1.0f;
}

// match: ?sub_1879F0@@YAXHPAURwV2d@@PBDPAURwRGBA@@@Z @ 0x001879F0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Draws the text arg_8 at *arg_4 (y from the top of a 448-high screen)
// in the colour arg_C or the style arg_0's (0 grey, else white; 1 a
// quarter larger), a pad button symbol ("$" or "Ba...") moved down (and
// "?p" along); without depth.
void sub_1879F0(RwInt32 arg_0, RwV2d *arg_4, const RwChar *arg_8, RwRGBA *arg_C)
{
    RwInt32 var_1C;
    RwRGBA var_18;
    type_DA580 *var_14;
    RwV2d ebp_10;
    RwReal var8;
    RwInt32 l4;

    RwRenderStateGet(rwRENDERSTATEZWRITEENABLE, &var_1C);
    RwRenderStateGet(rwRENDERSTATEZTESTENABLE, &l4);
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void *)0);
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void *)0);
    var_14 = dword_4EBD2C;
    if (!var_14)
        return;
    if (arg_C)
        var_18 = *arg_C;
    else if (!arg_0)
        var_18 = dword_4EBD14;
    else
        var_18 = dword_4EBD10;
    ebp_10.x = arg_4->x;
    ebp_10.y = 448.0f - arg_4->y;
    var8 = 19.0f;
    if (arg_0 == 1)
        var8 *= flt_42B478;
    if (!arg_8)
        return;
    if (arg_8[0] == '$' || (arg_8[0] == 'B' && arg_8[1] == 'a'))
    {
        if (arg_8[1] == 'p')
            ebp_10.x += 25.0f;
        ebp_10.y += 22.0f;
    }
    var_14->sub_DAB00(arg_8, &ebp_10, &var_18, var8, 0);
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void *)var_1C);
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void *)l4);
}

// match: ?sub_187B30@@YAXXZ @ 0x00187B30
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The top message box's step (unless it waits): its own update, then the
// pad: up and down move the selection, left and right change the line's
// choice (calling its change), accept calls the choice's select, back (in
// the front end's menus only) closes it unless it forbids that, each with
// its sound.
void sub_187B30()
{
    RwInt32 var_6C;
    RwInt32 v68;
    RwInt32 frm_64;
    RwInt32 t60;
    RwInt32 lcl_5C;
    RwV3d bp_58;
    type_3D3548 *m_4C;
    RwInt32 local_48;
    RwInt32 local_44;
    RwInt32 local_40;
    type_3D3548 *p3C;
    RwInt32 var_38;
    RwInt32 l34;
    type_3D3548 *var30;
    type_3D3548 *ebp_2C;
    type_3D3548 *lcl_28;
    RwInt32 frm_24;
    RwInt32 var_20;
    RwInt32 l1C;
    RwInt32 m_18;
    RwReal ebp_14;
    RwInt32 lv_10;
    type_4EBE00 *var_C;
    RwInt32 bp_8;
    RwInt32 bp_4;

    if (dword_4EBD34 == -1)
        return;
    var_C = &dword_4EBE00[dword_4EBD34];
    if (var_C->unk_18)
        return;
    if (var_C->unk_2CE8)
        var_C->unk_2CE8(var_C, var_C->unk_2CEC);
    frm_24 = dword_4EBD28;
    m_18 = dword_4EBD1C;
    bp_8 = dword_4EBD00;
    l1C = dword_4EBDF0;
    bp_4 = dword_4EBD18;
    var_20 = dword_4EBDEC;
    ebp_14 = unk_4B9308.sub_EE8F0(0, frm_24);
    if (dword_4F3168 == 6)
        ebp_14 = 0;
    if (ebp_14 != 0.0f)
    {
        var_C->unk_38 = var_C->sub_18A060(var_C->unk_38);
        lcl_28 = sub_1745A0(0);
        if (lcl_28)
            lcl_28->unk_1C0.sub_8A980(&dword_4B1C88, lcl_28, 1, lcl_28->sub_CD550(), 0, 0);
    }
    ebp_14 = unk_4B9308.sub_EE8F0(0, m_18);
    if (dword_4F3168 == 6)
        ebp_14 = 0;
    if (ebp_14 != 0.0f)
    {
        var_C->unk_38 = var_C->sub_189FB0(var_C->unk_38);
        ebp_2C = sub_1745A0(0);
        if (ebp_2C)
            ebp_2C->unk_1C0.sub_8A980(&dword_4B1C88, ebp_2C, 1, ebp_2C->sub_CD550(), 0, 0);
    }
    if (dword_4EBE00[dword_4EBD34].unk_2CDC == 1)
    {
        if (dword_4EBE00[dword_4EBD34].unk_38 == dword_4EBE00[dword_4EBD34].unk_2C - 1)
        {
            dword_4EBE00[dword_4EBD34].unk_04.unk_00[4] = 0;
            dword_4EBE00[dword_4EBD34].unk_04.unk_00[3] = 1;
            var_C->unk_04.unk_00[2] = 0;
            var_C->unk_04.unk_00[1] = 1;
        }
        else
        {
            dword_4EBE00[dword_4EBD34].unk_04.unk_00[4] = 1;
            dword_4EBE00[dword_4EBD34].unk_04.unk_00[3] = 0;
            var_C->unk_04.unk_00[2] = 1;
            var_C->unk_04.unk_00[1] = 1;
        }
    }
    lv_10 = var_C->unk_38;
    if (lv_10 != -1)
    {
        ebp_14 = unk_4B9308.sub_EE8F0(0, bp_8);
        if (dword_4F3168 == 6)
            ebp_14 = 0;
        if (ebp_14 != 0.0f)
        {
            lcl_5C = var_C->unk_DC[lv_10].unk_260;
            if (lcl_5C > 1)
            {
                l34 = var_C->unk_DC[lv_10].unk_264;
                if ((var_38 = l34 - 1) < 0)
                {
                    t60 = var_C->unk_DC[lv_10].unk_260;
                    var_38 = t60 - 1;
                }
                var_C->unk_DC[lv_10].unk_264 = var_38;
                if (var_C->unk_DC[lv_10].unk_100[l34].unk_1C)
                    var_C->unk_DC[lv_10].unk_100[l34].unk_1C(var_C, &var_C->unk_DC[lv_10],
                                                               var_C->unk_DC[lv_10].unk_100[l34].unk_00,
                                                               var_C->unk_DC[lv_10].unk_100[l34].unk_20);
                var30 = sub_1745A0(0);
                if (var30)
                    var30->unk_1C0.sub_8A980(&dword_4B1C00, var30, 1, var30->sub_CD550(), 0, 0);
            }
        }
        ebp_14 = unk_4B9308.sub_EE8F0(0, l1C);
        if (dword_4F3168 == 6)
            ebp_14 = 0;
        if (ebp_14 != 0.0f)
        {
            frm_64 = var_C->unk_DC[lv_10].unk_260;
            if (frm_64 > 1)
            {
                local_40 = var_C->unk_DC[lv_10].unk_264;
                local_44 = local_40 + 1;
                v68 = var_C->unk_DC[lv_10].unk_260;
                if (local_44 >= v68)
                    local_44 = 0;
                var_C->unk_DC[lv_10].unk_264 = local_44;
                if (var_C->unk_DC[lv_10].unk_100[local_40].unk_1C)
                    var_C->unk_DC[lv_10].unk_100[local_40].unk_1C(var_C, &var_C->unk_DC[lv_10],
                                                               var_C->unk_DC[lv_10].unk_100[local_40].unk_00,
                                                               var_C->unk_DC[lv_10].unk_100[local_40].unk_20);
                p3C = sub_1745A0(0);
                if (p3C)
                    p3C->unk_1C0.sub_8A980(&dword_4B1C00, p3C, 1, p3C->sub_CD550(), 0, 0);
            }
        }
        ebp_14 = unk_4B9308.sub_EE8F0(0, bp_4);
        if (ebp_14 != 0.0f && dword_4F3168 != 6)
        {
            local_48 = var_C->unk_DC[lv_10].unk_264;
            if (local_48 != -1 && var_C->unk_DC[lv_10].unk_100[local_48].unk_24)
                var_C->unk_DC[lv_10].unk_100[local_48].unk_24(var_C, &var_C->unk_DC[lv_10],
                                                           var_C->unk_DC[lv_10].unk_100[local_48].unk_00,
                                                           var_C->unk_DC[lv_10].unk_100[local_48].unk_28);
        }
    }
    ebp_14 = unk_4B9308.sub_EE8F0(0, var_20);
    if (dword_4F3168 != 6)
        ebp_14 = 0;
    if (ebp_14 != 0.0f && !dword_4B88AC)
    {
        var_6C = var_C->unk_2CF0;
        if (var_6C != 1 && dword_4EBE00[dword_4EBD34].unk_2CDC)
        {
            if (dword_4EBE00[dword_4EBD34].unk_2CDC == 1)
                sub_18E380(0, 0, 0, 0);
            dword_4EBD34 = dword_4EBD34 - 1;
            bp_58.x = 1.0f;
            bp_58.y = bp_58.z = 0;
            m_4C = sub_1745A0(0);
            if (m_4C)
                m_4C->unk_1C0.sub_8A980(&dword_4B1B48, m_4C, 1, m_4C->sub_CD550(), 0, 0);
            else
                dword_4B1E98.sub_8A980(&dword_4B1B48, 0, 0, &bp_58, 0, 0);
        }
    }
}

// match: ?sub_1882C0@@YAXXZ @ 0x001882C0
// While a pad is in, the buttons the boxes answer to from its bindings
// (actions 0 to 3, 10 and 11).
void sub_1882C0()
{
    if (!dword_42926C)
        return;
    dword_4EBD28 = unk_4B9308.sub_EE790(0, 0);
    dword_4EBD1C = unk_4B9308.sub_EE790(1, 0);
    dword_4EBD00 = unk_4B9308.sub_EE790(2, 0);
    dword_4EBDF0 = unk_4B9308.sub_EE790(3, 0);
    dword_4EBD18 = unk_4B9308.sub_EE790(0xA, 0);
    dword_4EBDEC = unk_4B9308.sub_EE790(0xB, 0);
}

// match: ?sub_188350@@YAHXZ @ 0x00188350
// The top box's message, or -1.
RwInt32 sub_188350()
{
    RwInt32 var_4;

    var_4 = -1;
    if (dword_4EBD34 != -1)
        var_4 = dword_4EBE00[dword_4EBD34].unk_2CDC;
    return var_4;
}
