/*
 * Win32 port bridge (docs/WIN32_PORT.md W7): stands in for the XDK's xhv.h (the Xbox voice
 * engine). The port has no voice device: port/xhv's engine never sees a communicator, so the
 * game's voice owner (type_3E3884 in game/voice.h, unit_1C6AC0) runs with no talkers.
 *
 * Declared from what that code uses. ITitleXHV is implemented by the game, so it keeps its
 * method order and the default bodies the game relies on for the slot it does not override.
 */
#ifndef PORT_XHV_H
#define PORT_XHV_H

#include <xtl.h>
#include <dsound.h>
#include <xonline.h>

/* Playback targets: a local talker's port, or the speakers. */
#define XHV_PLAYBACK_TO_SPEAKERS 4
#define XHV_PLAYBACK_PRIORITY_MAX 0
#define XHV_PLAYBACK_PRIORITY_NEVER 0xFFFFFFFF
typedef DWORD XHV_PLAYBACK_PRIORITY;

/* Processing modes: the engine's descriptors, passed by address. */
typedef PVOID XHV_PROCESSING_MODE;
extern "C" const XHV_PROCESSING_MODE _xhv_loopback_mode;
extern "C" const XHV_PROCESSING_MODE _xhv_voicechat_mode;
extern "C" const XHV_PROCESSING_MODE _xhv_voicemail_mode;
extern "C" const XHV_PROCESSING_MODE _xhv_inactive_mode;
#define XHV_LOOPBACK_MODE _xhv_loopback_mode
#define XHV_VOICECHAT_MODE _xhv_voicechat_mode
#define XHV_VOICEMAIL_MODE _xhv_voicemail_mode
#define XHV_INACTIVE_MODE _xhv_inactive_mode

typedef enum _XHV_VOICE_COMMUNICATOR_STATUS
{
    XHV_VOICE_COMMUNICATOR_STATUS_INSERTED = 0,
    XHV_VOICE_COMMUNICATOR_STATUS_REMOVED
} XHV_VOICE_COMMUNICATOR_STATUS;

#pragma pack(push, 4)

typedef struct _XHV_SR_ITEM
{
    DWORD dwWordID;
    FLOAT fConfidence;
} XHV_SR_ITEM;

typedef struct _XHV_RUNTIME_PARAMS
{
    DWORD dwMaxRemoteTalkers;
    DWORD dwMaxLocalTalkers;
    DWORD dwMaxCompressedBuffers;
    DWORD dwFlags;
    DSEFFECTIMAGEDESC *pEffectImageDesc;
    DWORD dwEffectsStartIndex;
    DWORD dwOutOfSyncThreshold;
    BOOL bCustomVADProvided;
    BOOL bHeadphoneAlwaysOn;
} XHV_RUNTIME_PARAMS, *PXHV_RUNTIME_PARAMS;

#pragma pack(pop)

/* The engine's callbacks into the game. */
struct __declspec(novtable) ITitleXHV
{
    STDMETHOD(LocalChatDataReady)(DWORD dwLocalPort, DWORD dwSize, VOID *pData)
    {
        return E_NOTIMPL;
    }
    STDMETHOD(CommunicatorStatusUpdate)(DWORD dwLocalPort,
                                        XHV_VOICE_COMMUNICATOR_STATUS communicatorStatus)
    {
        return E_NOTIMPL;
    }
    STDMETHOD(SpeechRecognized)(DWORD dwLocalPort, XHV_SR_ITEM *pSRArray, DWORD dwSRItemsCount)
    {
        return E_NOTIMPL;
    }
    STDMETHOD(MicrophoneRawDataReady)(DWORD dwLocalPort, DWORD dwSize, VOID *pData,
                                      BOOL *pVoiceDetected)
    {
        return E_NOTIMPL;
    }
    STDMETHOD(VoiceMailDataReady)(DWORD dwLocalPort, DWORD dwDuration, DWORD dwSize)
    {
        return E_NOTIMPL;
    }
    STDMETHOD(VoiceMailStopped)(DWORD dwLocalPort)
    {
        return E_NOTIMPL;
    }
};

/* The engine. */
struct XHVEngine
{
    ULONG WINAPI Release();
    HRESULT WINAPI EnableProcessingMode(XHV_PROCESSING_MODE processingMode);
    HRESULT WINAPI SetCallbackInterface(ITitleXHV *pITitleXHV);
    HRESULT WINAPI DoWork();
    HRESULT WINAPI RegisterLocalTalker(DWORD dwLocalPort);
    HRESULT WINAPI UnregisterLocalTalker(DWORD dwLocalPort);
    HRESULT WINAPI SetProcessingMode(DWORD dwLocalPort, XHV_PROCESSING_MODE processingMode);
    HRESULT WINAPI RegisterRemoteTalker(XUID xuidRemoteTalker);
    HRESULT WINAPI UnregisterRemoteTalker(XUID xuidRemoteTalker);
    HRESULT WINAPI SubmitIncomingVoicePacket(XUID xuidRemoteTalker, VOID *pvData, DWORD dwSize);
    BOOL WINAPI IsTalking(XUID xuidRemoteTalker);
    HRESULT WINAPI SetPlaybackPriority(XUID xuidRemoteTalker, DWORD dwLocalPort,
                                       XHV_PLAYBACK_PRIORITY playbackPriority);
    HRESULT WINAPI SetMaxPlaybackStreamsCount(DWORD dwMaxPlaybackStreams);
};
typedef XHVEngine *PXHVENGINE;

extern "C" HRESULT WINAPI XHVEngineCreate(PXHV_RUNTIME_PARAMS pParams, PXHVENGINE *ppEngine);

#endif
