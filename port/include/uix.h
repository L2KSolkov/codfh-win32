/*
 * Win32 port bridge (docs/WIN32_PORT.md W7): stands in for the XDK's uix.h (the Xbox Live UI
 * engine). The port has no Live UI: port/uix stubs the engine (features never start, DoWork
 * reports nothing), so the game's Live manager (unit_19BF20, unit_2261C0) and its plugins
 * (unit_228D70: the skinned UI, fonts and players list) compile and run unchanged.
 *
 * Declared from what those units use. The title interfaces are implemented by the game, so they
 * keep their method sets and order (the game's vtables follow them).
 */
#ifndef PORT_UIX_H
#define PORT_UIX_H

#include <xtl.h>
#include <xonline.h>

/* Features: the engine's descriptors, passed by address. */
typedef PVOID UIX_FEATURE;
extern "C" const UIX_FEATURE _uix_logon_feature;
extern "C" const UIX_FEATURE _uix_friends_feature;
extern "C" const UIX_FEATURE _uix_players_feature;
#define UIX_LOGON_FEATURE _uix_logon_feature
#define UIX_FRIENDS_FEATURE _uix_friends_feature
#define UIX_PLAYERS_FEATURE _uix_players_feature

typedef PVOID UIX_VOICE_MAIL_ENTRY_POINT;
extern "C" const UIX_VOICE_MAIL_ENTRY_POINT _uix_voice_mail;
#define UIX_VOICE_MAIL _uix_voice_mail

/* DoWork's result flags. */
#define UIX_DOWORK_NEED_TO_RENDER 0x00000001
#define UIX_DOWORK_NEED_TO_REBOOT 0x00000004
#define UIX_DOWORK_FEATURE_EXIT 0x00000008
#define UIX_DOWORK_PROCESSING_INPUT 0x00000010
#define UIX_DOWORK_NOTIFY_FRIEND_REQUEST 0x00010000
#define UIX_DOWORK_NOTIFY_GAME_INVITE 0x00020000

/* The players feature's display flags. */
#define UIX_PLAYERS_DISPLAY_CURRENT_PLAYERS 0x00000001
#define UIX_PLAYERS_DISPLAY_DEPARTED_PLAYERS 0x00000002

/* GetExitInfo's exit codes. */
typedef DWORD UIX_EXIT_CODE_TYPE;
#define UIX_EXIT_LOGON_SUCCESSFUL 1
#define UIX_EXIT_LOGON_FAILED 2
#define UIX_EXIT_LOGON_USER_EXIT 3
#define UIX_EXIT_FRIENDS_NORMAL_EXIT 4
#define UIX_EXIT_FRIENDS_JOIN_GAME 5
#define UIX_EXIT_FRIENDS_JOIN_GAME_CROSS_TITLE 6

typedef enum _UIX_NOTIFICATION_PURPOSE
{
    UIX_NOTIFICATION_MENU = 0,
    UIX_NOTIFICATION_IN_GAME_FLASH = 1,
    UIX_NOTIFICATION_FORCE_DWORD = 0x7fffffff
} UIX_NOTIFICATION_PURPOSE;

typedef enum _UIX_PROPERTY_TYPE
{
    UIX_PROPERTY_DISPLAY_NOTIFICATIONS = 0,
    UIX_PROPERTY_HOST_NO_MIGRATION = 1,
    UIX_PROPERTY_DISPLAY_CONNECTION_ERRORS = 2,
    UIX_PROPERTY_ALLOW_GAME_INVITES = 3,
    UIX_PROPERTY_VOICE_MAIL_ENGINE = 4,
    UIX_PROPERTY_VOICE_MAIL_TO_SPEAKERS = 5,
    UIX_PROPERTY_FORCE_DWORD = 0x7fffffff
} UIX_PROPERTY_TYPE;

/* The skinned UI's objects (the game's UI plugin draws them). */
typedef enum _UIX_OBJECT_TYPE
{
    UIX_OBJECT_NONE = 0,
    UIX_OBJECT_TEXTBOX = 1,
    UIX_OBJECT_LISTBOX = 2,
    UIX_OBJECT_BACKGROUND = 3,
    UIX_OBJECT_FORCE_DWORD = 0x7fffffff
} UIX_OBJECT_TYPE;

typedef enum _UIX_OBJSTATE_TYPE
{
    UIX_OBJSTATE_LIST_SELECTION_INDEX = 0,
    UIX_OBJSTATE_LIST_ITEM_GREYED = 1,
    UIX_OBJSTATE_LIST_ITEM_HIGHLIGHTED = 2,
    UIX_OBJSTATE_WORD_WRAP = 3,
    UIX_OBJSTATE_FORCE_DWORD = 0x7fffffff
} UIX_OBJSTATE_TYPE;

/* Input handed to a list: directional keys carry 0x1000. */
typedef enum _UIX_INPUT_TYPE
{
    UIX_INPUT_NONE = 0,
    UIX_INPUT_UP = 0x1005,
    UIX_INPUT_DOWN = 0x1006,
    UIX_INPUT_DPAD_UP = 0x1009,
    UIX_INPUT_DPAD_DOWN = 0x100A,
    UIX_INPUT_FORCE_DWORD = 0x7fffffff
} UIX_INPUT_TYPE;

typedef enum _UIX_LOGON_TYPE
{
    UIX_LOGON_TYPE_NORMAL = 0,
    UIX_LOGON_TYPE_SILENT = 1,
    UIX_LOGON_TYPE_RETRIEVED_STATE = 2,
    UIX_LOGON_TYPE_RETRIEVED_GAME_INVITE = 3,
    UIX_LOGON_FORCE_DWORD = 0x7fffffff
} UIX_LOGON_TYPE;

typedef enum _UIX_VOICE_STATUS_TYPE
{
    UIX_VOICE_STATUS_COMMUNICATOR = 0,
    UIX_VOICE_STATUS_SPEAKERS = 1,
    UIX_VOICE_STATUS_NONE = 2,
    UIX_VOICE_STATUS_FORCE_DWORD = 0x7fffffff
} UIX_VOICE_STATUS_TYPE;

#pragma pack(push, 1)

/* A skin object's placement and colours. */
typedef struct _UIX_SKIN_LAYOUT_INFO
{
    WORD X;
    WORD Y;
    WORD Width;
    WORD Height;
    DWORD ImageOffset;
    D3DCOLOR BackColor;
    D3DCOLOR TextColor;
    D3DCOLOR DisabledTextColor;
    D3DCOLOR SelectionBackColor;
    D3DCOLOR HighlightedTextColor;
    WORD FontHeight;
    WORD Flags;
    WORD XOffset;
    WORD YOffset;
    DWORD CustomParam;
} UIX_SKIN_LAYOUT_INFO;

/* An icon inside a list item's text. */
typedef struct _UIX_SKIN_ICON_INFO
{
    DWORD IconResID;
    DWORD InsertPosInText;
    DWORD Flags;
} UIX_SKIN_ICON_INFO;

#pragma pack(pop)

#pragma pack(push, 4)

typedef struct _UIX_LOGON_PARAMS
{
    SIZE_T StructSize;
    UIX_LOGON_TYPE LogonType;
    DWORD LogonUserCount;
    DWORD LogonServiceIDs[16];
    XONLINE_LOGON_STATE *pLogonState;
    XONLINE_ACCEPTED_GAMEINVITE *pGameInvite;
} UIX_LOGON_PARAMS;

typedef struct _UIX_FRIENDS_PARAMS
{
    SIZE_T StructSize;
    DWORD UserPort;
    XUID SelectedFriendXUID;
    BOOL SignOutEnabled;
} UIX_FRIENDS_PARAMS;

typedef struct _UIX_EXIT_INFO
{
    UIX_FEATURE FeatureID;
    UIX_EXIT_CODE_TYPE ExitCode;
    HRESULT hr;
    PVOID pExitData;
} UIX_EXIT_INFO;

#pragma pack(pop)

struct PluginSupport;
struct LiveEngine;
#define IPluginSupport PluginSupport
#define ILiveEngine LiveEngine

/* The game's font renderer over an XFONT (type_3E0404). */
struct __declspec(novtable) ITitleFontRenderer
{
    STDMETHOD_(ULONG, Release)() = 0;
    STDMETHOD(SetHeight)(DWORD Height) = 0;
    STDMETHOD(SetColor)(D3DCOLOR Color) = 0;
    STDMETHOD(DrawText)(LPCWSTR pText, DWORD X, DWORD Y, DWORD MaxWidth) = 0;
    STDMETHOD(GetTextSize)(LPCWSTR pText, DWORD *pWidth, DWORD *pHeight) = 0;
};

/* The game's skinned UI (unit_228D70). */
struct __declspec(novtable) ITitleUIPlugin
{
    STDMETHOD_(ULONG, Release)() = 0;
    STDMETHOD(DoWork)() = 0;
    STDMETHOD(SetPluginSupport)(IPluginSupport *pPluginSupport) = 0;
    STDMETHOD(CreateObject)(UIX_OBJECT_TYPE ObjectType, DWORD ScreenInstance, DWORD ScreenResID,
                            DWORD ObjectResID, DWORD *pObjectID) = 0;
    STDMETHOD(DestroyObject)(DWORD ObjectID) = 0;
    STDMETHOD(DestroyScreenObjects)(DWORD ScreenInstance) = 0;
    STDMETHOD(SetRenderTarget)(IDirect3DSurface8 *pSurface) = 0;
    STDMETHOD(RenderObject)(DWORD ObjectID) = 0;
    STDMETHOD(SetText)(DWORD ObjectID, DWORD ItemIndex, LPCWSTR pText, DWORD IconCount,
                       const UIX_SKIN_ICON_INFO *pIconInfo) = 0;
    STDMETHOD(InsertItem)(DWORD ObjectID, DWORD ItemIndex, DWORD *pReturnIndex) = 0;
    STDMETHOD(SetObjectState)(DWORD ObjectID, DWORD ItemIndex, UIX_OBJSTATE_TYPE State,
                              DWORD Value) = 0;
    STDMETHOD(GetObjectState)(DWORD ObjectID, DWORD ItemIndex, UIX_OBJSTATE_TYPE State,
                              DWORD *pValue) = 0;
    STDMETHOD(PassInputToObject)(DWORD ObjectID, UIX_INPUT_TYPE InputKey) = 0;
    STDMETHOD(Clear)(DWORD ObjectID, BOOL ResetSelectionIndex) = 0;
    STDMETHOD(GetFont)(ITitleFontRenderer **ppFont) = 0;
};

/* The game's UI sounds. */
struct __declspec(novtable) ITitleAudioPlugin
{
    STDMETHOD_(ULONG, Release)() = 0;
    STDMETHOD(PlaySound)(LPCSTR SoundName) = 0;
    STDMETHOD(DoWork)() = 0;
};

/* A player as the players feature lists them (the game's players). */
struct __declspec(novtable) ITitlePlayersListItem
{
    STDMETHOD_(const WCHAR *, GetName)() const = 0;
    STDMETHOD_(const XUID *, GetXUID)() const = 0;
    STDMETHOD_(UIX_VOICE_STATUS_TYPE, GetVoiceStatus)() const = 0;
    STDMETHOD_(BOOL, IsTalking)() const = 0;
    STDMETHOD_(DWORD, GetBitflags)() const = 0;
    STDMETHOD_(INT, Compare)(const ITitlePlayersListItem *) const
    {
        return 0;
    }
};

/* The players feature's list, from GetFeatureInterface. */
struct __declspec(novtable) ILivePlayersList
{
    STDMETHOD(RegisterPlayer)(const ITitlePlayersListItem *pPlayer) = 0;
    STDMETHOD(UnregisterPlayer)(const ITitlePlayersListItem *pPlayer) = 0;
    STDMETHOD(Refresh)() = 0;
    STDMETHOD(SetFilterFlags)(const DWORD Flags) = 0;
    STDMETHOD(ClearDepartedPlayersList)() = 0;
};

typedef struct _UIX_PLAYERS_PARAMS
{
    SIZE_T StructSize;
    DWORD UserPort;
    ITitlePlayersListItem *pPlayerControllingScreen;
    const XUID *pSelectedPlayerXUID;
    BOOL SortCurrentPlayersList;
    DWORD FilterFlags;
    DWORD DisplayType;
} UIX_PLAYERS_PARAMS;

/* The skin's resources, handed to the game's UI plugin. */
struct PluginSupport
{
    ULONG WINAPI AddRef();
    ULONG WINAPI Release();
    HRESULT WINAPI GetString(DWORD StringResID, LPCWSTR *ppString);
    HRESULT WINAPI GetLayout(DWORD ScreenResID, DWORD ObjectResID, UIX_SKIN_LAYOUT_INFO **ppLayout);
    HRESULT WINAPI GetImage(DWORD ImageResID, IDirect3DTexture8 **ppTexture);
    HRESULT WINAPI GetScreenImage(DWORD ScreenResID, DWORD ImageResID, IDirect3DTexture8 **ppTexture);
    HRESULT WINAPI GetWordLength(LPCWSTR pString, DWORD *pWordLength);
};

/* The engine. */
struct LiveEngine
{
    ULONG WINAPI AddRef();
    ULONG WINAPI Release();
    HRESULT WINAPI DoWork(DWORD *pDoWorkFlags);
    HRESULT WINAPI SetUIPlugin(ITitleUIPlugin *pUIPlugin);
    HRESULT WINAPI SetAudioPlugin(ITitleAudioPlugin *pAudioPlugin);
    HRESULT WINAPI EnableFeature(UIX_FEATURE FeatureID);
    HRESULT WINAPI StartFeature(UIX_FEATURE FeatureID, const VOID *pFeatureParams);
    HRESULT WINAPI Render(IDirect3DSurface8 *pSurface);
    HRESULT WINAPI SetInput(DWORD Port, const XINPUT_STATE *pInputState);
    HRESULT WINAPI NotificationSetState(DWORD Port, DWORD StateFlags, XNKID SessionID,
                                        DWORD StateDataSize, const PVOID pStateData);
    HRESULT WINAPI GetNotifications(DWORD Port, UIX_NOTIFICATION_PURPOSE Purpose,
                                    DWORD *pNotifications);
    HRESULT WINAPI SetProperty(UIX_PROPERTY_TYPE Property, DWORD Value);
    HRESULT WINAPI GetExitInfo(UIX_EXIT_INFO *pExitInfo);
    HRESULT WINAPI Reboot(DWORD Context);
    HRESULT WINAPI LogOff(VOID);
    HRESULT WINAPI GetFeatureInterface(UIX_FEATURE FeatureID, const VOID *pParam,
                                       VOID **ppFeatureInterface);
    HRESULT WINAPI EndFeature(VOID);
    HRESULT WINAPI ClearInput(VOID);
    HRESULT WINAPI UseVoiceMail(UIX_VOICE_MAIL_ENTRY_POINT VoiceMailEntryPoint);
};

extern "C" HRESULT WINAPI UIXCreateLiveEngine(LPCSTR pSkinFileName, DWORD LanguageID,
                                              ILiveEngine **ppEngine);
extern "C" HRESULT WINAPI UIXCreateUIPlugin(ITitleFontRenderer *pFontRenderer,
                                             ITitleUIPlugin **ppPlugin);

#endif
