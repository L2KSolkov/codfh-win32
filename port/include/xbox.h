/*
 * Win32 port bridge (docs/WIN32_PORT.md W1, W4): the Xbox-only part of XAPI that the XDK's xtl.h
 * brings in (its xbox.h): controllers, device tables, saves, signatures, launch data, video and
 * audio flags, physical memory. The Win32 part of XAPI (files, threads, events, timers) is the
 * Windows SDK's own. port/xpal_* implement these names.
 *
 * Declared from what the game, RenderWare and RenderWare Audio use. The controller structures are
 * byte-packed, as the Xbox's: the game's controller record (type_4F4638, game/padlib.h) embeds
 * two states back to back at +0x00 and +0x16.
 */
#ifndef PORT_XBOX_H
#define PORT_XBOX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Peripheral device types: the XAPI's descriptor tables, passed by address. */
typedef struct _XPP_DEVICE_TYPE
{
    ULONG Reserved[3];
} XPP_DEVICE_TYPE, *PXPP_DEVICE_TYPE;

extern XPP_DEVICE_TYPE XDEVICE_TYPE_GAMEPAD_TABLE;
extern XPP_DEVICE_TYPE XDEVICE_TYPE_VOICE_MICROPHONE_TABLE;
extern XPP_DEVICE_TYPE XDEVICE_TYPE_VOICE_HEADPHONE_TABLE;
#define XDEVICE_TYPE_GAMEPAD (&XDEVICE_TYPE_GAMEPAD_TABLE)
#define XDEVICE_TYPE_VOICE_MICROPHONE (&XDEVICE_TYPE_VOICE_MICROPHONE_TABLE)
#define XDEVICE_TYPE_VOICE_HEADPHONE (&XDEVICE_TYPE_VOICE_HEADPHONE_TABLE)

typedef struct _XDEVICE_PREALLOC_TYPE
{
    PXPP_DEVICE_TYPE DeviceType;
    DWORD dwPreallocCount;
} XDEVICE_PREALLOC_TYPE, *PXDEVICE_PREALLOC_TYPE;

VOID WINAPI XInitDevices(DWORD dwPreallocTypeCount, PXDEVICE_PREALLOC_TYPE PreallocTypes);
DWORD WINAPI XGetDevices(PXPP_DEVICE_TYPE DeviceType);
BOOL WINAPI XGetDeviceChanges(PXPP_DEVICE_TYPE DeviceType, PDWORD pdwInsertions,
                              PDWORD pdwRemovals);

/* Controllers */
#pragma pack(push, 1)

typedef struct _XINPUT_GAMEPAD
{
    WORD wButtons;
    BYTE bAnalogButtons[8];
    SHORT sThumbLX;
    SHORT sThumbLY;
    SHORT sThumbRX;
    SHORT sThumbRY;
} XINPUT_GAMEPAD, *PXINPUT_GAMEPAD;

typedef struct _XINPUT_STATE
{
    DWORD dwPacketNumber;
    XINPUT_GAMEPAD Gamepad;
} XINPUT_STATE, *PXINPUT_STATE;

typedef struct _XINPUT_RUMBLE
{
    WORD wLeftMotorSpeed;
    WORD wRightMotorSpeed;
} XINPUT_RUMBLE, *PXINPUT_RUMBLE;

typedef struct _XINPUT_CAPABILITIES
{
    BYTE SubType;
    WORD Reserved;
    union
    {
        XINPUT_GAMEPAD Gamepad;
    } In;
    union
    {
        XINPUT_RUMBLE Rumble;
    } Out;
} XINPUT_CAPABILITIES, *PXINPUT_CAPABILITIES;

/* Rumble: the header tracks the asynchronous send (the game polls dwStatus). */
typedef struct _XINPUT_FEEDBACK_HEADER
{
    DWORD dwStatus;
    HANDLE hEvent;
    BYTE Reserved[58];
} XINPUT_FEEDBACK_HEADER, *PXINPUT_FEEDBACK_HEADER;

typedef struct _XINPUT_FEEDBACK
{
    XINPUT_FEEDBACK_HEADER Header;
    XINPUT_RUMBLE Rumble;
} XINPUT_FEEDBACK, *PXINPUT_FEEDBACK;

typedef struct _XINPUT_POLLING_PARAMETERS
{
    BYTE fAutoPoll : 1;
    BYTE fInterruptOut : 1;
    BYTE ReservedMBZ1 : 6;
    BYTE bInputInterval;
    BYTE bOutputInterval;
    BYTE ReservedMBZ2;
} XINPUT_POLLING_PARAMETERS, *PXINPUT_POLLING_PARAMETERS;

#pragma pack(pop)

HANDLE WINAPI XInputOpen(PXPP_DEVICE_TYPE DeviceType, DWORD dwPort, DWORD dwSlot,
                         PXINPUT_POLLING_PARAMETERS pPollingParameters);
VOID WINAPI XInputClose(HANDLE hDevice);
DWORD WINAPI XInputGetState(HANDLE hDevice, PXINPUT_STATE pState);
DWORD WINAPI XInputSetState(HANDLE hDevice, PXINPUT_FEEDBACK pFeedback);
DWORD WINAPI XInputGetCapabilities(HANDLE hDevice, PXINPUT_CAPABILITIES pCapabilities);

/* Saves: one directory per save game under the save drive (port: a folder per save). */
#define MAX_GAMENAME 128

typedef struct _XGAME_FIND_DATA
{
    WIN32_FIND_DATAA wfd;
    CHAR szSaveGameDirectory[MAX_PATH];
    WCHAR szSaveGameName[MAX_GAMENAME];
} XGAME_FIND_DATA, *PXGAME_FIND_DATA;

DWORD WINAPI XCreateSaveGame(LPCSTR lpRootPathName, LPCWSTR lpSaveGameName,
                             DWORD dwCreationDisposition, DWORD dwCreateFlags, LPSTR lpPathBuffer,
                             UINT uSize);
DWORD WINAPI XDeleteSaveGame(LPCSTR lpRootPathName, LPCWSTR lpSaveGameName);
HANDLE WINAPI XFindFirstSaveGame(LPCSTR lpRootPathName, PXGAME_FIND_DATA pFindGameData);
BOOL WINAPI XFindNextSaveGame(HANDLE hFindGame, PXGAME_FIND_DATA pFindGameData);
BOOL WINAPI XFindClose(HANDLE hFind);

/* Save signatures (port: HMAC-SHA1 with a fixed local key). */
#define XCALCSIG_SIGNATURE_SIZE 20

typedef struct
{
    BYTE Signature[XCALCSIG_SIGNATURE_SIZE];
} XCALCSIG_SIGNATURE, *PXCALCSIG_SIGNATURE;

HANDLE WINAPI XCalculateSignatureBegin(DWORD dwFlags);
DWORD WINAPI XCalculateSignatureUpdate(HANDLE hCalcSig, const BYTE *pbData, ULONG cbData);
DWORD WINAPI XCalculateSignatureEnd(HANDLE hCalcSig, PVOID pSignature);

/* Launch data: what the title was started with, and starting another (the dashboard). */
#define MAX_LAUNCH_DATA_SIZE (1024 * 3)
#define LDT_TITLE 0
#define LDT_FROM_DEBUGGER_CMDLINE 3

typedef struct _LAUNCH_DATA
{
    BYTE Data[MAX_LAUNCH_DATA_SIZE];
} LAUNCH_DATA, *PLAUNCH_DATA;

#define XLD_LAUNCH_DASHBOARD_MEMORY 2

typedef struct _LD_LAUNCH_DASHBOARD
{
    DWORD dwReason;
    DWORD dwContext;
    DWORD dwParameter1;
    DWORD dwParameter2;
    BYTE Reserved[MAX_LAUNCH_DATA_SIZE - 16];
} LD_LAUNCH_DASHBOARD, *PLD_LAUNCH_DASHBOARD;

DWORD WINAPI XGetLaunchInfo(PDWORD pdwLaunchDataType, PLAUNCH_DATA pLaunchData);
DWORD WINAPI XLaunchNewImageA(LPCSTR lpImagePath, PLAUNCH_DATA pLaunchData);
#define XLaunchNewImage XLaunchNewImageA

/* The console's settings (port: the configuration file). */
#define XC_VIDEO_STANDARD_NTSC_J 2
#define XC_VIDEO_STANDARD_PAL_I 3
#define XC_VIDEO_FLAGS_WIDESCREEN 0x00000001
#define XC_VIDEO_FLAGS_HDTV_720p 0x00000002
#define XC_VIDEO_FLAGS_HDTV_480p 0x00000008
#define XC_VIDEO_FLAGS_PAL_60Hz 0x00000040

DWORD WINAPI XGetVideoFlags(VOID);
DWORD WINAPI XGetVideoStandard(VOID);
DWORD WINAPI XGetAudioFlags(VOID);

/* Memory and disks */
LPVOID WINAPI XPhysicalAlloc(SIZE_T dwSize, ULONG_PTR ulPhysicalAddress, ULONG_PTR ulAlignment,
                             DWORD flProtect);
VOID WINAPI XPhysicalFree(LPVOID lpAddress);
DWORD WINAPI XGetDiskSectorSizeA(LPCSTR lpRootPathName);

/* The kernel's critical sections, which the Xbox's XAPI exposes by these names. Windows' ntdll
   exports the same two; declared as RenderWare's texture module declares them itself
   (batextur.c), so the declarations agree. */
__declspec(dllimport) void __stdcall RtlEnterCriticalSection(void *CriticalSection);
__declspec(dllimport) void __stdcall RtlLeaveCriticalSection(void *CriticalSection);

/* Layout checks: the game's own structures embed these. */
typedef char port_check_XINPUT_STATE[sizeof(XINPUT_STATE) == 0x16 ? 1 : -1];
typedef char port_check_XINPUT_CAPABILITIES[sizeof(XINPUT_CAPABILITIES) == 0x19 ? 1 : -1];
typedef char port_check_XINPUT_FEEDBACK[sizeof(XINPUT_FEEDBACK) == 0x46 ? 1 : -1];
typedef char port_check_XGAME_FIND_DATA[sizeof(XGAME_FIND_DATA) == 0x344 ? 1 : -1];

#ifdef __cplusplus
}
#endif

#endif
