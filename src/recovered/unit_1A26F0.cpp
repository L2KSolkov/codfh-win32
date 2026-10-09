// The Xbox strings and the sound's start-up (game/pak.h, game/gameloop.h):
// the in-game messages' texts, the sound library's set-up and update, and
// the shell's world.

#include "game/liveservice.h"
#include <stdio.h>

#include "game/pak.h"
#include "game/waitscreen.h"
#include "game/startup.h"
#include "game/debugtext.h"
#include "game/savestate.h"
#include "types/type_DC400.h"
#include "game/gameloop.h"
#include "game/data.h"
#include "game/frontend.h"
#include "game/netmsg.h"
#include "game/netplayer.h"
#include "rw/bastream.h"
#include "rw/batextur.h"
#include "rw/babintex.h"
#include "game/ingamepages.h"
#include "game/fade.h"
#include "game/uiglue.h"
#include "types/cXboxLive.h"

// The message handlers in the table below (defined below and in unit_1A8B20).
type_3DA44C *sub_1A3020(type_1F8560 *arg_0);
type_3DA44C *sub_1A30A0(type_1F8560 *arg_0);
type_3DA44C *sub_1A30F0(type_1F8560 *arg_0);
type_3DA44C *sub_1A3140(type_1F8560 *arg_0);
type_3DA44C *sub_1A31A0(type_1F8560 *arg_0);
type_3DA44C *sub_1A31F0(type_1F8560 *arg_0);
type_3DA44C *sub_1A3250(type_1F8560 *arg_0);
type_3DA44C *sub_1A32B0(type_1F8560 *arg_0);
type_3DA44C *sub_1A3330(type_1F8560 *arg_0);
type_3DA44C *sub_1A33B0(type_1F8560 *arg_0);
type_3DA44C *sub_1A3400(type_1F8560 *arg_0);
type_3DA44C *sub_1A3450(type_1F8560 *arg_0);
type_3DA44C *sub_1A34A0(type_1F8560 *arg_0);
void sub_1A3550(RwUInt32 arg_0, RwInt32 arg_4, type_1F8560 *arg_8);
type_3DA44C *sub_1A35B0(type_1F8560 *arg_0);
type_3DA44C *sub_1A3600(type_1F8560 *arg_0);
type_3DA44C *sub_1A3650(type_1F8560 *arg_0);
type_3DA44C *sub_1A36A0(type_1F8560 *arg_0);
type_3DA44C *sub_1A36F0(type_1F8560 *arg_0);
type_3DA44C *sub_1A3740(type_1F8560 *arg_0);
type_3DA44C *sub_1A3790(type_1F8560 *arg_0);
type_3DA44C *sub_1A37E0(type_1F8560 *arg_0);
type_3DA44C *sub_1A3830(type_1F8560 *arg_0);
type_3DA44C *sub_1A3880(type_1F8560 *arg_0);
type_3DA44C *sub_1A38D0(type_1F8560 *arg_0);
type_3DA44C *sub_1A3950(type_1F8560 *arg_0);
type_3DA44C *sub_1A39A0(type_1F8560 *arg_0);
type_3DA44C *sub_1A39F0(type_1F8560 *arg_0);
type_3DA44C *sub_1A3A70(type_1F8560 *arg_0);
type_3DA44C *sub_1A3AC0(type_1F8560 *arg_0);
type_3DA44C *sub_1A3B40(type_1F8560 *arg_0);
void sub_1ACAB0(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8);
void sub_1ACEB0(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8);
void sub_1ACFD0(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8);
void sub_1AD0F0(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8);
void sub_1AD260(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8);
void sub_1AD6B0(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8);
void sub_1AD750(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8);
void sub_1ADD90(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8);
void sub_1AE250(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8);
void sub_1AE300(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8);
void sub_1AE420(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8);
void sub_1AE460(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8);
void sub_1AE4D0(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8);
void sub_1AE5C0(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8);
void sub_1AE650(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8);
void sub_1AE810(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8);
void sub_1AE8F0(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8);
void sub_1AEB90(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8);
void sub_1AEBE0(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8);
void sub_1AEC30(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8);
void sub_1AF320(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8);
void sub_1AF370(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8);
void sub_1AF400(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8);
void sub_1AF420(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8);
void sub_1AF470(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8);
void sub_1AF4C0(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8);
void sub_1AF570(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8);
void sub_1AF5D0(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8);

// Its data definitions (PLAN M5), in the image's address order.
#ifndef CODFH_SP // MP only: the network messages' handler table (read by sub_1DDF00) and the multiplayer start-up and log callback; single player has no twin of sub_1A2910/sub_1A2A60 (config/sp/shared.txt), only sub_1A26F0 (SP 0x12FC40)
// 0x0042C848
// The message handlers by message id (sub_1DDF00): kind 0 reads the
// message (unk_08) and takes it (unk_0C), kind 1 takes the stream (unk_10).
// Two take nothing: their empty handlers folded into sub_19A750.
type_42C848 unk_42C848[31] = {
    { 1, 0, 0, 0, sub_1A3550 },
    { 0, 1, sub_1A30A0, sub_1ACAB0, 0 },
    { 0, 2, sub_1A30F0, sub_1ACEB0, 0 },
    { 0, 3, sub_1A3AC0, sub_1AD0F0, 0 },
    { 0, 8, sub_1A37E0, sub_1AD260, 0 },
    { 0, 9, sub_1A3830, sub_1AD6B0, 0 },
    { 0, 10, sub_1A39A0, sub_1AD750, 0 },
    { 0, 11, sub_1A39F0, sub_1ADD90, 0 },
    { 0, 12, sub_1A3A70, sub_1AE250, 0 },
    { 0, 13, sub_1A32B0, sub_1AE300, 0 },
    { 0, 27, sub_1A3330, sub_1AE420, 0 },
    { 0, 14, sub_1A3B40, sub_1AE8F0, 0 },
#ifdef CODFH_WIN32
    // (the empty function without the print: the port's sub_19A750 prints its first argument)
    { 0, 15, sub_1A3650, (void (*)(RwInt32, RwInt32, struct type_3DA44C *))(void (*)())sub_19A750, 0 },
#else
    { 0, 15, sub_1A3650, (void (*)(RwInt32, RwInt32, struct type_3DA44C *))(void (*)(const RwChar *, ...))sub_19A750, 0 },
#endif
    { 0, 16, sub_1A3880, sub_1AE5C0, 0 },
    { 0, 17, sub_1A38D0, sub_1AE650, 0 },
    { 0, 18, sub_1A3950, sub_1AE810, 0 },
    { 0, 19, sub_1A3140, sub_1ACFD0, 0 },
    { 0, 20, sub_1A3250, sub_1AEB90, 0 },
    { 0, 21, sub_1A31F0, sub_1AEBE0, 0 },
    { 0, 22, sub_1A36A0, sub_1AF320, 0 },
    { 0, 23, sub_1A36F0, sub_1AF370, 0 },
    { 0, 24, sub_1A3740, sub_1AF400, 0 },
    { 0, 25, sub_1A35B0, sub_1AF420, 0 },
    { 0, 26, sub_1A3600, sub_1AF470, 0 },
    { 0, 28, sub_1A33B0, sub_1AF4C0, 0 },
    { 0, 29, sub_1A3400, sub_1AF570, 0 },
    { 0, 30, sub_1A3450, sub_1AF5D0, 0 },
    { 0, 31, sub_1A34A0, sub_1AE460, 0 },
    { 0, 32, sub_1A3020, sub_1AE4D0, 0 },
    { 0, 33, sub_1A31A0, sub_1AEC30, 0 },
#ifdef CODFH_WIN32
    // (the empty function without the print: the port's sub_19A750 prints its first argument)
    { 0, 34, sub_1A3790, (void (*)(RwInt32, RwInt32, struct type_3DA44C *))(void (*)())sub_19A750, 0 },
#else
    { 0, 34, sub_1A3790, (void (*)(RwInt32, RwInt32, struct type_3DA44C *))(void (*)(const RwChar *, ...))sub_19A750, 0 },
#endif
};
// 0x0042CAB4
RwUInt32 dword_42CAB4 = 31;
#endif
// 0x004F6178
RwChar *dword_4F6178[29];
// 0x004F62FC
#ifndef CODFH_PLAIN
RwInt32 dword_4F62FC;
#endif
// 0x004F6AB8
RwUInt32 dword_4F6AB8[5138];
// End of its data definitions.



// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0BK@KJGADLFK@shell?2hud?2XboxStrings?4csv?$AA@ @ 0x003E0C88
// match: ??_C@_07ENNCKBDI@_Yes_No?$AA@ @ 0x003E0CA4
// match: ??_C@_03NFLEOILF@_No?$AA@ @ 0x003E0CAC
// match: ??_C@_04HPJFDDCO@_Yes?$AA@ @ 0x003E0CB0
// match: ??_C@_09MMKDJGBG@_Sign_Out?$AA@ @ 0x003E0CB8
// match: ??_C@_08FFDCIBLJ@_Sign_In?$AA@ @ 0x003E0CC4
// match: ??_C@_0BK@LGPLJEOG@_Xbox_Multiple_Accounts_3?$AA@ @ 0x003E0CD0
// match: ??_C@_0BK@KPOAKFKH@_Xbox_Multiple_Accounts_2?$AA@ @ 0x003E0CEC
// match: ??_C@_0BK@IEMNPGGE@_Xbox_Multiple_Accounts_1?$AA@ @ 0x003E0D08
// match: ??_C@_0BK@IFFCOMIA@_Important_Xbox_Message_2?$AA@ @ 0x003E0D24
// match: ??_C@_0BK@KOHPLPED@_Important_Xbox_Message_1?$AA@ @ 0x003E0D40
// match: ??_C@_0M@OLJBBFEF@_Signing_In?$AA@ @ 0x003E0D5C
// match: ??_C@_0P@DNFCFPPK@_Appear_Online?$AA@ @ 0x003E0D68
// match: ??_C@_0BA@IOMJODJG@_Appear_Offline?$AA@ @ 0x003E0D78
// match: ??_C@_0O@LAAECMBO@_Friends_List?$AA@ @ 0x003E0D88
// match: ??_C@_09PEOPBPKD@_Continue?$AA@ @ 0x003E0D98
// match: ??_C@_0P@BNACNBJM@_Not_Signed_In?$AA@ @ 0x003E0DA4
// match: ??_C@_0BC@KIGHLFIL@_Pass_Code_Needed?$AA@ @ 0x003E0DB4
// match: ??_C@_0BA@IFBJFOEB@_Sign_In_Failed?$AA@ @ 0x003E0DC8
// match: ??_C@_0L@PPKKFDKJ@_Signed_In?$AA@ @ 0x003E0DD8
// match: ??_C@_0BK@KFEHNMP@_Xbox_Live_Cant_Connect_2?$AA@ @ 0x003E0DE4
// match: ??_C@_0BK@CBHJCOAM@_Xbox_Live_Cant_Connect_1?$AA@ @ 0x003E0E00
// match: ??_C@_0M@FGKGPHBG@_Invert_Aim?$AA@ @ 0x003E0E1C
// match: ??_C@_0BD@DAEBGHBN@_Xbox_Live_Options?$AA@ @ 0x003E0E28
// match: ??_C@_08DGBACAOJ@_Loading?$AA@ @ 0x003E0E3C
// match: ??_C@_0O@KJMJGHCJ@_Unsaved_Lost?$AA@ @ 0x003E0E48
// match: ??_C@_0BC@PJLMAKKM@_Restart_Question?$AA@ @ 0x003E0E58
// match: ??_C@_0P@HLNFHGLI@_Quit_Question?$AA@ @ 0x003E0E6C
// match: ??_C@_0BF@CHMJAEJL@_Insert_Controller_2?$AA@ @ 0x003E0E7C
// match: ??_C@_0BF@MOEFHFI@_Insert_Controller_1?$AA@ @ 0x003E0E94
// match: ?unk_42C848@@3PAUtype_42C848@@A @ 0x0042C848
// match: ?dword_42CAB4@@3IA @ 0x0042CAB4

// match: ?sub_1A26F0@@YAXXZ @ 0x001A26F0
// sp-match: ?sub_1A26F0@@YAXXZ @ 0x0012FC40

// Reads the in-game messages' texts (dword_4F6178) from
// "shell\hud\XboxStrings.csv".
void sub_1A26F0()
{
    type_18A470 var_F0[] = {
        {"_Insert_Controller_1", &dword_4F6178[0]},
        {"_Insert_Controller_2", &dword_4F6178[1]},
        {"_Quit_Question", &dword_4F6178[2]},
        {"_Restart_Question", &dword_4F6178[3]},
        {"_Unsaved_Lost", &dword_4F6178[4]},
        {"_Loading", &dword_4F6178[5]},
        {"_Xbox_Live_Options", &dword_4F6178[6]},
        {"_Invert_Aim", &dword_4F6178[7]},
        {"_Xbox_Live_Cant_Connect_1", &dword_4F6178[8]},
        {"_Xbox_Live_Cant_Connect_2", &dword_4F6178[9]},
        {"_Signed_In", &dword_4F6178[10]},
        {"_Sign_In_Failed", &dword_4F6178[11]},
        {"_Pass_Code_Needed", &dword_4F6178[12]},
        {"_Not_Signed_In", &dword_4F6178[13]},
        {"_Continue", &dword_4F6178[14]},
        {"_Friends_List", &dword_4F6178[15]},
        {"_Appear_Offline", &dword_4F6178[16]},
        {"_Appear_Online", &dword_4F6178[17]},
        {"_Signing_In", &dword_4F6178[18]},
        {"_Important_Xbox_Message_1", &dword_4F6178[19]},
        {"_Important_Xbox_Message_2", &dword_4F6178[20]},
        {"_Xbox_Multiple_Accounts_1", &dword_4F6178[21]},
        {"_Xbox_Multiple_Accounts_2", &dword_4F6178[22]},
        {"_Xbox_Multiple_Accounts_3", &dword_4F6178[23]},
        {"_Sign_In", &dword_4F6178[24]},
        {"_Sign_Out", &dword_4F6178[25]},
        {"_Yes", &dword_4F6178[26]},
        {"_No", &dword_4F6178[27]},
        {"_Yes_No", &dword_4F6178[28]},
        {0, 0},
    };

    sub_18A890("shell\\hud\\XboxStrings.csv", var_F0, 0);
}

#ifndef CODFH_SP // MP only: the network messages' handler table (read by sub_1DDF00) and the multiplayer start-up and log callback; single player has no twin of sub_1A2910/sub_1A2A60 (config/sp/shared.txt), only sub_1A26F0 (SP 0x12FC40)
// match: ?sub_1A2910@@YAXXZ @ 0x001A2910
// Starts the systems after RenderWare: the log callback, the debug text's
// buffer, the text's language (from the game's), then unk_4F7EB8 and the
// service at dword_5051E8.
void sub_1A2910()
{
    sub_1D5DB0((void (__cdecl *)(const RwChar *))sub_1A2A60);
    sub_16BA60(0x2000);
    switch (sub_19B0A0())
    {
    case 0:
        unk_4FEB0C.sub_1CAD40(1);
        break;
    case 1:
        unk_4FEB0C.sub_1CAD40(4);
        break;
    case 2:
        unk_4FEB0C.sub_1CAD40(2);
        break;
    case 3:
        unk_4FEB0C.sub_1CAD40(4);
        break;
    case 4:
        unk_4FEB0C.sub_1CAD40(2);
        break;
    case 5:
        unk_4FEB0C.sub_1CAD40(5);
        break;
    case 6:
        unk_4FEB0C.sub_1CAD40(3);
        break;
    case 7:
        unk_4FEB0C.sub_1CAD40(8);
        break;
    case 10:
        unk_4FEB0C.sub_1CAD40(6);
        break;
    case 12:
        unk_4FEB0C.sub_1CAD40(7);
        break;
    case 13:
        unk_4FEB0C.sub_1CAD40(0);
        break;
    default:
        unk_4FEB0C.sub_1CAD40(1);
        break;
    }
    unk_4F7EB8.sub_1A9580();
    unk_4FEB0C.sub_1CADA0(0, 0);
    sub_227560()->sub_226360();
    unk_4F7EB8.sub_1AA320();
}

// match: ?sub_1A2A60@@YAXPAD@Z @ 0x001A2A60
// The library's log callback: the line arg_0 into channel 2.
void sub_1A2A60(RwChar *arg_0)
{
    sub_1B18D0()->sub_1B1780(arg_0, 2);
}

#endif











// (The compiler's exit thunk for sub_1A3020's instance: it runs the
// message's destructor, sub_1C5760.)











// (The compiler's exit thunk for the instance: the message's destructor,
// sub_1B2AD0.)


// (The compiler's exit thunk for the instance: the message's destructor,
// sub_1B3800.)





// (The compiler's exit thunk for the instance: the message's destructor,
// sub_1A88E0.)



















// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?vf_000@type_3E0EB8@@UAEXPAUtype_1F8560@@@Z (folded into 0x15FB30)
void type_3E0EB8::vf_000(struct type_1F8560 *arg_0)
{
}

// ?vf_000@type_3E1044@@UAEXPAUtype_1F8560@@@Z (folded into 0x15FB30)
void type_3E1044::vf_000(struct type_1F8560 *arg_0)
{
}

// ?vf_000@type_3E108C@@UAEXPAUtype_1F8560@@@Z (folded into 0x15FB30)
void type_3E108C::vf_000(struct type_1F8560 *arg_0)
{
}

// ?vf_000@type_3E10A4@@UAEXPAUtype_1F8560@@@Z (folded into 0x15FB30)
void type_3E10A4::vf_000(struct type_1F8560 *arg_0)
{
}

// ?vf_004@type_3E0EB8@@UAEXPAUtype_1F8560@@@Z (folded into 0x15FB30)
void type_3E0EB8::vf_004(struct type_1F8560 *arg_0)
{
}

// ?vf_008@type_3E0F60@@UAEHXZ (folded into 0x6FCA0)
RwInt32 type_3E0F60::vf_008()
{
    return 0x20;
}

// ?vf_008@type_3E0F78@@UAEHXZ (folded into 0x195D00)
RwInt32 type_3E0F78::vf_008()
{
    return 2;
}

// ?vf_008@type_3E0FA8@@UAEHXZ (folded into 0x1940D0)
RwInt32 type_3E0FA8::vf_008()
{
    return 0x21;
}

// ?vf_008@type_3E0FF0@@UAEHXZ (folded into 0x1936A0)
RwInt32 type_3E0FF0::vf_008()
{
    return 0x1C;
}

// ?vf_008@type_3E1008@@UAEHXZ (folded into 0x193B10)
RwInt32 type_3E1008::vf_008()
{
    return 0x1D;
}

// ?vf_008@type_3E1020@@UAEHXZ (folded into 0x1945A0)
RwInt32 type_3E1020::vf_008()
{
    return 0x1E;
}

// ?vf_008@type_3E1038@@UAEHXZ (folded into 0x1948F0)
RwInt32 type_3E1038::vf_008()
{
    return 0x1F;
}

// ?vf_008@type_3E1050@@UAEHXZ (folded into 0xA2530)
RwInt32 type_3E1050::vf_008()
{
    return 0x19;
}

// ?vf_008@type_3E1068@@UAEHXZ (folded into 0xBAA90)
RwInt32 type_3E1068::vf_008()
{
    return 0xF;
}

// ?vf_008@type_3E1080@@UAEHXZ (folded into 0xA3B80)
RwInt32 type_3E1080::vf_008()
{
    return 0x16;
}

// ?vf_008@type_3E1098@@UAEHXZ (folded into 0x9E040)
RwInt32 type_3E1098::vf_008()
{
    return 0x17;
}

// ?vf_008@type_3E10B0@@UAEHXZ (folded into 0xA9500)
RwInt32 type_3E10B0::vf_008()
{
    return 0x18;
}

// ?vf_008@type_3E10C8@@UAEHXZ (folded into 0x193FA0)
RwInt32 type_3E10C8::vf_008()
{
    return 0x22;
}

// ?vf_008@type_3E10E0@@UAEHXZ (folded into 0x9F4C0)
RwInt32 type_3E10E0::vf_008()
{
    return 8;
}

// ?vf_008@type_3E10F8@@UAEHXZ (folded into 0xA2CD0)
RwInt32 type_3E10F8::vf_008()
{
    return 9;
}

// ?vf_008@type_3E1110@@UAEHXZ (folded into 0xA1330)
RwInt32 type_3E1110::vf_008()
{
    return 0x10;
}

// ?vf_008@type_3E1128@@UAEHXZ (folded into 0xB7520)
RwInt32 type_3E1128::vf_008()
{
    return 0x11;
}

// ?vf_008@type_3E1140@@UAEHXZ (folded into 0xA6EF0)
RwInt32 type_3E1140::vf_008()
{
    return 0x12;
}

// ?vf_008@type_3E1158@@UAEHXZ (folded into 0x36780)
RwInt32 type_3E1158::vf_008()
{
    return 10;
}

// ?vf_008@type_3E1188@@UAEHXZ (folded into 0xBAD20)
RwInt32 type_3E1188::vf_008()
{
    return 0xC;
}

// ?vf_008@type_3E11B8@@UAEHXZ (folded into 0xBB430)
RwInt32 type_3E11B8::vf_008()
{
    return 0xE;
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?vf_008@type_3E0EC4@@UAEHXZ (folded into 0x215B70)
RwInt32 type_3E0EC4::vf_008()
{
        return 0x1A;
    }


#ifdef CODFH_PLAIN
// Plain builds (tools/plainbuild.py): the variables below are a second name for this unit's
// variables' bytes in the image (tools/session/overlapvars.py --aliases); only the placement
// link gives them one storage, so any other link binds them here at the image offset.
// (bound at start-up: the library initialization area runs before every game constructor)
#pragma warning(disable: 4073)
#pragma init_seg(lib)
// 0x004F6AF8: dword_4F6AB8 + 0x40
RwReal &flt_4F6AF8 = *(RwReal *)((RwUInt8 *)&dword_4F6AB8 + 0x40);
// 0x004F7E98: dword_4F6AB8 + 0x13E0
RwCamera *&dword_4F7E98 = *(RwCamera * *)((RwUInt8 *)&dword_4F6AB8 + 0x13E0);
#endif
