/*
 * The XAPI thread functions the recovered code calls, declared as the XDK's
 * winbase.h declares them: __stdcall, linked from xapilib (config/aliases.txt
 * places them).
 */
#ifndef XBOX_XAPI_H
#define XBOX_XAPI_H

// A unit that includes the XDK's own headers (xtl.h) first has all of this.
#ifndef _WINBASE_

#include "rw/ostypes.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef RwUInt32 (__stdcall *PTHREAD_START_ROUTINE)(void *lpThreadParameter);

void *__stdcall CreateThread(void *lpThreadAttributes, RwUInt32 dwStackSize,
                             PTHREAD_START_ROUTINE lpStartAddress, void *lpParameter,
                             RwUInt32 dwCreationFlags, RwUInt32 *lpThreadId);
RwInt32 __stdcall SetThreadPriority(void *hThread, RwInt32 nPriority);
RwUInt32 __stdcall ResumeThread(void *hThread);
// The time in milliseconds (RenderWare Studio's Time::GetTime reads it).
RwUInt32 __stdcall GetTickCount(void);
#ifdef CODFH_WIN32
// The port's: a millisecond count as the Xbox's (Windows' moves in 15.6 ms steps, which made the
// game's frame times 15, 16 or 31 ms at a steady 60 frames a second; port/src/xpal_core.cpp).
RwUInt32 __stdcall xpal_GetTickCount(void);
#define GetTickCount xpal_GetTickCount
#endif
__declspec(noreturn) void __stdcall ExitThread(RwUInt32 dwExitCode);

// Launching the dashboard, as the XDK's xbox.h declares it (the not enough
// free blocks screen, sub_18D7C0, opens its memory page).
#define MAX_LAUNCH_DATA_SIZE (1024 * 3)
typedef struct _LAUNCH_DATA
{
    RwUInt8 Data[MAX_LAUNCH_DATA_SIZE];
} LAUNCH_DATA, *PLAUNCH_DATA;
#define XLD_LAUNCH_DASHBOARD_MEMORY 2
typedef struct _LD_LAUNCH_DASHBOARD
{
    RwUInt32 dwReason;
    RwUInt32 dwContext;
    RwUInt32 dwParameter1;
    RwUInt32 dwParameter2;
    RwUInt8 Reserved[MAX_LAUNCH_DATA_SIZE - 16];
} LD_LAUNCH_DASHBOARD, *PLD_LAUNCH_DASHBOARD;
RwUInt32 __stdcall XLaunchNewImageA(const RwChar *lpTitlePath, PLAUNCH_DATA pLaunchData);
#define XLaunchNewImage XLaunchNewImageA

#ifdef __cplusplus
}
#endif

#endif

#endif
