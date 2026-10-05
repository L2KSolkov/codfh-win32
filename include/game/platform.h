/*
 * The Xbox platform's set-up (unit_19CB20): the file system on d:, a file
 * read ahead, the DDS texture read callback, the gamma ramp, and the frame's
 * end (the Live friends feature, the back buffer drawn over itself).
 */
#ifndef GAME_PLATFORM_H
#define GAME_PLATFORM_H

#include "rw/ostypes.h"
#include "rw/batextur.h"
#include "rw/baengine.h"

extern void *dword_4F39D4;                          // the file system
extern RwTextureCallBackRead dword_4F39E0;          // the read callback before
extern RwInt32 dword_4F39E4;                        // the friends feature's step
extern RwInt32 dword_4E5CBC;                        // a second camera (game/gameloop.h)
extern RwInt32 dword_4F3080;
extern bool byte_4CF88C;
extern RwInt32 dword_4F39DC;
// The screen's size (also in game/gameloop.h).
extern RwInt32 Width;
extern RwInt32 Height;
extern "C" RwInt32 RwFclose(void *fptr);

RwInt32 sub_19CD50();
RwInt32 sub_19CD80();
RwInt32 sub_19CDE0(const RwChar *arg_0);
RwTexture *sub_19CEC0(const RwChar *arg_0, const RwChar *arg_4);
RwInt32 sub_19CF10();
RwInt32 sub_19D020();
void sub_19D040();
void sub_19D060();
void sub_19D080(RwCamera *arg_0);
// RenderWare's file system manager and its Xbox file system (rtfsyst).
extern "C" RwBool RtFSManagerOpen(RwInt32 maxNbFS);
extern "C" void *RtXboxFSystemInit(RwInt32 maxNbOpenFiles, const RwChar *deviceName,
                                   const RwChar *fileSystemName);
extern "C" RwBool RtFSManagerRegister(void *fs);
extern "C" void RtFSManagerSetDefaultFileSystem(void *fs);

// RenderWare's Xbox device configuration as the start-up fills it
// (sub_19D470): the screen's size, its format, the flags (widescreen 0x10,
// 720p 0x20, 480p 0x40, 0x100) and the refresh rate.
struct type_4F4600
{
    RwInt32 unk_00;             // width
    RwInt32 unk_04;             // height
    RwUInt8 unk_08[0x8];
    RwInt32 unk_10;
    RwUInt8 unk_14[0x8];
    RwUInt32 unk_1C;            // flags
    RwInt32 unk_20;             // refresh rate
    RwUInt32 unk_24;
};
extern "C" void RwXboxDeviceConfigGetDefaultValues(type_4F4600 *config);
extern type_4F4600 unk_4F4600;
extern RwUInt8 unk_4F39F8[];                        // the launch data
extern RwUInt32 dword_4F45FC;                       // XGetLaunchInfo's result
extern RwUInt32 dword_4F4628;                       // the launch data's type
extern RwInt32 dword_42C5A0;
#ifdef CODFH_PLAIN
extern RwInt32 &dword_4F30B8;
#else
extern RwInt32 dword_4F30B8;
#endif
extern RwInt32 dword_4F5A30;
extern RwInt32 dword_4F2B70;
extern RwInt32 dword_4F307C;
extern RwInt32 dword_4B87F0;
extern RwInt32 dword_4B87F4;
extern RwInt32 ZDepth;
extern RwInt32 dword_4B8880;
extern void *dword_4B87FC;
extern RwUInt32 dword_4F30C0;                       // XGetAudioFlags
#ifdef CODFH_PLAIN
extern RwInt32 &dword_4F30BC;                        // widescreen
#else
extern RwInt32 dword_4F30BC;                        // widescreen
#endif
extern RwUInt16 word_4F39EC;                        // the FPU control word before
extern void *dword_4F39F0;                          // the default XFONT
void sub_19D470(type_4F4600 *arg_0);
RwInt32 sub_19D290();
void sub_19D2D0();
RwInt32 main();
void sub_1A2680(void *arg_0);
void sub_D9C00();
// The back buffer drawn over itself (unit_19B0F0), and the stopwatch.
void sub_19B670(RwReal arg_0);
RwReal sub_19B9E0(RwInt32 arg_0);

// The Xbox driver's current Direct3D device (0x2B3CC0).
extern "C" void *RwXboxGetCurrentD3DDevice(void);
// Sets the memory card and pad state up (sub_16C940).
bool sub_16C940();

#endif
