/*
 * The Xbox kernel (xboxkrnl.exe) imports the recovered code calls, declared
 * as the XDK's xboxkrnl.h declares them: __stdcall and imported, so each call
 * goes through its import slot (config/aliases.txt names the slots).
 */
#ifndef XBOX_XBOXKRNL_H
#define XBOX_XBOXKRNL_H

#include "rw/ostypes.h"

// A unit that includes the XDK's own headers (xtl.h) first has all of this.
#ifndef _WINNT_

#ifdef __cplusplus
extern "C"
{
#endif

// A kernel critical section (0x1C bytes on the Xbox).
typedef struct _RTL_CRITICAL_SECTION
{
    RwUInt8 unk_00[0x1C];
} RTL_CRITICAL_SECTION;

__declspec(dllimport) void __stdcall RtlEnterCriticalSection(RTL_CRITICAL_SECTION *arg_0);
__declspec(dllimport) void __stdcall RtlLeaveCriticalSection(RTL_CRITICAL_SECTION *arg_0);
__declspec(dllimport) void __stdcall RtlInitializeCriticalSection(RTL_CRITICAL_SECTION *arg_0);

#ifdef __cplusplus
}
#endif

#endif

#endif
