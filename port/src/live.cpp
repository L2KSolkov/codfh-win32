/*
 * The Live UI engine, the voice engine and the system font for the port (docs/WIN32_PORT.md W7,
 * W1). There is no Xbox Live: a feature the game starts ends at once, the sign-in with
 * UIX_EXIT_LOGON_FAILED, which the game handles as a failed connection. There is no voice
 * device: the engine exists (the game drives it without a check after creating it) but no
 * communicator ever comes in. The system font measures text; drawing it is the 2D layer's
 * (W2.1).
 */
#include <xtl.h>
#include <xonline.h>
#include <uix.h>
#include <xhv.h>
#include <xfont.h>
#include <string.h>
#include <wchar.h>

#include "port.h"

/*
 * Live UI
 */

extern "C" const UIX_FEATURE _uix_logon_feature = (UIX_FEATURE)"logon";
extern "C" const UIX_FEATURE _uix_friends_feature = (UIX_FEATURE)"friends";
extern "C" const UIX_FEATURE _uix_players_feature = (UIX_FEATURE)"players";
extern "C" const UIX_VOICE_MAIL_ENTRY_POINT _uix_voice_mail = (UIX_VOICE_MAIL_ENTRY_POINT)"voicemail";

static UIX_FEATURE active_feature;
static int feature_exit_pending;

struct NoPlayersList : ILivePlayersList
{
    STDMETHOD(RegisterPlayer)(const ITitlePlayersListItem *) { return S_OK; }
    STDMETHOD(UnregisterPlayer)(const ITitlePlayersListItem *) { return S_OK; }
    STDMETHOD(Refresh)() { return S_OK; }
    STDMETHOD(SetFilterFlags)(const DWORD) { return S_OK; }
    STDMETHOD(ClearDepartedPlayersList)() { return S_OK; }
};
static NoPlayersList players_list;

static char engine_storage[16];

extern "C" HRESULT WINAPI UIXCreateLiveEngine(LPCSTR, DWORD, ILiveEngine **ppEngine)
{
    *ppEngine = (ILiveEngine *)engine_storage;
    return S_OK;
}

ULONG WINAPI LiveEngine::AddRef() { return 1; }
ULONG WINAPI LiveEngine::Release() { return 0; }
HRESULT WINAPI LiveEngine::SetUIPlugin(ITitleUIPlugin *) { return S_OK; }
HRESULT WINAPI LiveEngine::SetAudioPlugin(ITitleAudioPlugin *) { return S_OK; }
HRESULT WINAPI LiveEngine::EnableFeature(UIX_FEATURE) { return S_OK; }
HRESULT WINAPI LiveEngine::Render(IDirect3DSurface8 *) { return S_OK; }
HRESULT WINAPI LiveEngine::SetInput(DWORD, const XINPUT_STATE *) { return S_OK; }
HRESULT WINAPI LiveEngine::NotificationSetState(DWORD, DWORD, XNKID, DWORD, const PVOID) { return S_OK; }
HRESULT WINAPI LiveEngine::SetProperty(UIX_PROPERTY_TYPE, DWORD) { return S_OK; }
HRESULT WINAPI LiveEngine::Reboot(DWORD) { return S_OK; }
HRESULT WINAPI LiveEngine::LogOff(VOID) { return S_OK; }
HRESULT WINAPI LiveEngine::ClearInput(VOID) { return S_OK; }
HRESULT WINAPI LiveEngine::UseVoiceMail(UIX_VOICE_MAIL_ENTRY_POINT) { return S_OK; }

HRESULT WINAPI LiveEngine::StartFeature(UIX_FEATURE FeatureID, const VOID *)
{
    plog("Live UI: feature %s started (no Live: it ends at once)", (const char *)FeatureID);
    active_feature = FeatureID;
    feature_exit_pending = 1;
    return S_OK;
}

HRESULT WINAPI LiveEngine::DoWork(DWORD *pDoWorkFlags)
{
    *pDoWorkFlags = feature_exit_pending ? UIX_DOWORK_FEATURE_EXIT : 0;
    return S_OK;
}

HRESULT WINAPI LiveEngine::GetNotifications(DWORD, UIX_NOTIFICATION_PURPOSE, DWORD *pNotifications)
{
    *pNotifications = 0;
    return S_OK;
}

HRESULT WINAPI LiveEngine::GetExitInfo(UIX_EXIT_INFO *pExitInfo)
{
    memset(pExitInfo, 0, sizeof(*pExitInfo));
    pExitInfo->FeatureID = active_feature;
    if (active_feature == UIX_LOGON_FEATURE)
    {
        pExitInfo->ExitCode = UIX_EXIT_LOGON_FAILED;
        pExitInfo->hr = E_FAIL;
    }
    else if (active_feature == UIX_FRIENDS_FEATURE)
        pExitInfo->ExitCode = 4;    /* the friends list closed */
    else
        pExitInfo->ExitCode = 8;    /* the players list closed */
    feature_exit_pending = 0;
    return S_OK;
}

HRESULT WINAPI LiveEngine::EndFeature(VOID)
{
    active_feature = NULL;
    feature_exit_pending = 0;
    return S_OK;
}

HRESULT WINAPI LiveEngine::GetFeatureInterface(UIX_FEATURE FeatureID, const VOID *, VOID **ppFeatureInterface)
{
    *ppFeatureInterface = FeatureID == UIX_PLAYERS_FEATURE ? (VOID *)&players_list : NULL;
    return *ppFeatureInterface ? S_OK : E_FAIL;
}

ULONG WINAPI PluginSupport::AddRef() { return 1; }
ULONG WINAPI PluginSupport::Release() { return 0; }
HRESULT WINAPI PluginSupport::GetString(DWORD, LPCWSTR *ppString) { *ppString = L""; return E_FAIL; }
HRESULT WINAPI PluginSupport::GetLayout(DWORD, DWORD, UIX_SKIN_LAYOUT_INFO **pp) { *pp = NULL; return E_FAIL; }
HRESULT WINAPI PluginSupport::GetImage(DWORD, IDirect3DTexture8 **pp) { *pp = NULL; return E_FAIL; }
HRESULT WINAPI PluginSupport::GetScreenImage(DWORD, DWORD, IDirect3DTexture8 **pp) { *pp = NULL; return E_FAIL; }

HRESULT WINAPI PluginSupport::GetWordLength(LPCWSTR pString, DWORD *pWordLength)
{
    DWORD n = 0;
    while (pString[n] && pString[n] != L' ' && pString[n] != L'\n')
        n++;
    *pWordLength = n;
    return S_OK;
}

/*
 * Voice: an engine with no communicator.
 */

extern "C" const XHV_PROCESSING_MODE _xhv_loopback_mode = (XHV_PROCESSING_MODE)"loopback";
extern "C" const XHV_PROCESSING_MODE _xhv_voicechat_mode = (XHV_PROCESSING_MODE)"voicechat";
extern "C" const XHV_PROCESSING_MODE _xhv_voicemail_mode = (XHV_PROCESSING_MODE)"voicemail";

static char voice_engine_storage[16];

extern "C" HRESULT WINAPI XHVEngineCreate(PXHV_RUNTIME_PARAMS, PXHVENGINE *ppEngine)
{
    *ppEngine = (XHVEngine *)voice_engine_storage;
    return S_OK;
}

ULONG WINAPI XHVEngine::Release() { return 0; }
HRESULT WINAPI XHVEngine::EnableProcessingMode(XHV_PROCESSING_MODE) { return S_OK; }
HRESULT WINAPI XHVEngine::SetCallbackInterface(ITitleXHV *) { return S_OK; }
HRESULT WINAPI XHVEngine::DoWork() { return S_OK; }
HRESULT WINAPI XHVEngine::RegisterLocalTalker(DWORD) { return S_OK; }
HRESULT WINAPI XHVEngine::UnregisterLocalTalker(DWORD) { return S_OK; }
HRESULT WINAPI XHVEngine::SetProcessingMode(DWORD, XHV_PROCESSING_MODE) { return S_OK; }
HRESULT WINAPI XHVEngine::RegisterRemoteTalker(XUID) { return S_OK; }
HRESULT WINAPI XHVEngine::UnregisterRemoteTalker(XUID) { return S_OK; }
HRESULT WINAPI XHVEngine::SubmitIncomingVoicePacket(XUID, VOID *, DWORD) { return S_OK; }
BOOL WINAPI XHVEngine::IsTalking(XUID) { return FALSE; }
HRESULT WINAPI XHVEngine::SetPlaybackPriority(XUID, DWORD, XHV_PLAYBACK_PRIORITY) { return S_OK; }

/*
 * The system font: an 8x16 cell scaled to the set height.
 */

struct XFONTState
{
    unsigned height;
    D3DCOLOR color;
};
static XFONTState default_font = {16, 0xFFFFFFFF};

extern "C" HRESULT __stdcall XFONT_OpenDefaultFont(XFONT **ppFont)
{
    *ppFont = (XFONT *)&default_font;
    return S_OK;
}

extern "C" void __stdcall XFONT_Release(XFONT *)
{
}

extern "C" unsigned __stdcall XFONT_GetTextHeight(XFONT *pFont)
{
    return ((XFONTState *)pFont)->height;
}

extern "C" HRESULT __stdcall XFONT_SetTextHeight(XFONT *pFont, unsigned uHeight)
{
    ((XFONTState *)pFont)->height = uHeight ? uHeight : 16;
    return S_OK;
}

extern "C" void __stdcall XFONT_SetTextColor(XFONT *pFont, D3DCOLOR color)
{
    ((XFONTState *)pFont)->color = color;
}

extern "C" HRESULT __stdcall XFONT_GetTextExtent(XFONT *pFont, LPCWSTR wstr, unsigned cch, unsigned *puWidth)
{
    unsigned n = cch == (unsigned)-1 ? (unsigned)wcslen(wstr) : cch;
    *puWidth = n * ((XFONTState *)pFont)->height / 2;
    return S_OK;
}

extern "C" HRESULT __stdcall XFONT_TextOut(XFONT *, IDirect3DSurface8 *, LPCWSTR, unsigned, long, long)
{
    PORT_STUB();    /* W2.1: drawn with the 2D layer */
    return S_OK;
}
