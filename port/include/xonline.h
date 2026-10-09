/*
 * Win32 port bridge (docs/WIN32_PORT.md W7): stands in for the XDK's xonline.h. The port shims the
 * minimum of Xbox Live that System Link needs (signed-in users, the task pump) and stubs the
 * Live-only services (matchmaking, friends, mute lists, logon state) in port/xonline.
 *
 * Declared from what the game's Live code (cXboxLive, liveservice.h, systemlink.h, unit_1D8370,
 * unit_1DC6C0, unit_2261C0, unit_2049D0, unit_20AA10) uses. The structures keep the Xbox sizes and
 * packing: the game embeds them in its own layouts (players' user ids, the mute list, the logon
 * state saved across a reboot).
 */
#ifndef PORT_XONLINE_H
#define PORT_XONLINE_H

#include <xtl.h>

#ifdef __cplusplus
extern "C" {
#endif

/* A task handle that XOnlineTaskContinue pumps until it stops returning XONLINETASK_S_RUNNING. */
DECLARE_HANDLE(XONLINETASK_HANDLE);
typedef XONLINETASK_HANDLE *PXONLINETASK_HANDLE;

#define XONLINETASK_S_RUNNING S_OK
#define XONLINETASK_S_SUCCESS ((HRESULT)0x001500F0L)
#define XONLINETASK_S_RESULTS_AVAIL ((HRESULT)0x001500F1L)
#define XONLINETASK_S_RUNNING_IDLE ((HRESULT)0x001500F2L)

#define XONLINE_S_LOGON_CONNECTION_ESTABLISHED ((HRESULT)0x001510F0L)
#define XONLINE_E_NO_SESSION ((HRESULT)0x80150002L)

#define XONLINE_GAMERTAG_SIZE 16
#define XONLINE_MAX_LOGON_USERS 4
/* SP's Live manager reserves 16 saved-user records before unk_748 at 0x748. */
#define XONLINE_MAX_STORED_ONLINE_USERS 16

#pragma pack(push, 4)

/* A user's id (12 bytes: the 64-bit id is only 4-aligned). */
typedef struct _XUID
{
    ULONGLONG qwUserID;
    DWORD dwUserFlags;
} XUID;

/* A signed-in user, one per controller port (0x70 bytes). */
typedef struct _XONLINE_USER
{
    XUID xuid;
    CHAR szGamertag[XONLINE_GAMERTAG_SIZE];
    DWORD dwUserOptions;
    BYTE passcode[4];
    BYTE reserved[72];
    HRESULT hr;
} XONLINE_USER, *PXONLINE_USER;

#pragma pack(pop)

/* The logon, saved across XLaunchNewImage and restored after it. */
#define XONLINE_LOGON_STATE_SIZE (XONLINE_MAX_LOGON_USERS * sizeof(XONLINE_USER) + 16 * sizeof(DWORD))

typedef struct _XONLINE_LOGON_STATE
{
    BYTE bType;
    BYTE bVersion;
    WORD cbSize;
    BYTE Data[XONLINE_LOGON_STATE_SIZE];
} XONLINE_LOGON_STATE, *PXONLINE_LOGON_STATE;

/* Matchmaking: a session attribute and the type/length of one in a search result. */
typedef struct _XONLINE_ATTRIBUTE
{
    DWORD dwAttributeID;    /* the attribute's id and X_ATTRIBUTE_DATATYPE_* */
    BOOL fChanged;
    union
    {
        struct
        {
            ULONGLONG qwValue;
        } integer;
        struct
        {
            LPWSTR lpValue;
        } string;
        struct
        {
            PVOID pvValue;
            DWORD dwLength;
        } blob;
    } info;
} XONLINE_ATTRIBUTE, *PXONLINE_ATTRIBUTE;

typedef struct _XONLINE_ATTRIBUTE_SPEC
{
    DWORD dwType;
    DWORD dwLength;
} XONLINE_ATTRIBUTE_SPEC, *PXONLINE_ATTRIBUTE_SPEC;

#define X_ATTRIBUTE_DATATYPE_INTEGER 0x00000000
#define X_ATTRIBUTE_DATATYPE_STRING 0x00100000
#define X_ATTRIBUTE_DATATYPE_NULL 0x00F00000

#pragma pack(push, 1)

/* A session a search found; its attributes follow it. */
typedef struct _XONLINE_MATCH_SEARCHRESULT
{
    DWORD dwReserved;
    XNKID SessionID;
    XNADDR HostAddress;
    XNKEY KeyExchangeKey;
    DWORD dwPublicOpen;
    DWORD dwPrivateOpen;
    DWORD dwPublicFilled;
    DWORD dwPrivateFilled;
    DWORD dwNumAttributes;
} XONLINE_MATCH_SEARCHRESULT, *PXONLINE_MATCH_SEARCHRESULT;

/* A friend, as a game invite names the one who sent it. */
typedef struct _XONLINE_FRIEND
{
    XUID xuid;
    CHAR szGamertag[XONLINE_GAMERTAG_SIZE];
    DWORD dwFriendState;
    FILETIME gameinviteTime;
    XNKID sessionID;
    DWORD dwTitleID;
    BYTE StateDataSize;
    BYTE StateData[32];
    BYTE bReserved;
} XONLINE_FRIEND, *PXONLINE_FRIEND;

#pragma pack(pop)

typedef struct _XONLINE_ACCEPTED_GAMEINVITE
{
    XONLINE_FRIEND InvitingFriend;
    XUID xuidAcceptedFriend;
    FILETIME InviteAcceptTime;
    XUID xuidLogonUsers[XONLINE_MAX_LOGON_USERS];
} XONLINE_ACCEPTED_GAMEINVITE, *PXONLINE_ACCEPTED_GAMEINVITE;

/* One entry of a user's mute list. */
typedef struct _XONLINE_MUTELISTUSER
{
    XUID xuid;
    DWORD dwReserved;
} XONLINE_MUTELISTUSER, *PXONLINE_MUTELISTUSER;

/* The game starts Live with no parameters (NULL). */
typedef struct _XONLINE_STARTUP_PARAMS XONLINE_STARTUP_PARAMS;

HRESULT WINAPI XOnlineStartup(const XONLINE_STARTUP_PARAMS *pxosp);
HRESULT WINAPI XOnlineTaskContinue(XONLINETASK_HANDLE hTask);
HRESULT WINAPI XOnlineTaskClose(XONLINETASK_HANDLE hTask);
PXONLINE_USER WINAPI XOnlineGetLogonUsers(void);
HRESULT WINAPI XOnlineLogonTaskGetResults(XONLINETASK_HANDLE hLogonTask);
HRESULT WINAPI XOnlineSaveLogonState(PXONLINE_LOGON_STATE pLogonState);
HRESULT WINAPI XOnlineRetrieveLogonState(const XONLINE_LOGON_STATE *pLogonState,
                                         PXONLINE_USER pUsers, DWORD *pdwServiceIDs,
                                         DWORD *pdwServices);
HRESULT WINAPI XOnlineGetUsers(PXONLINE_USER pUsers, DWORD *pdwUsers);
BOOL WINAPI XOnlineIsUserVoiceAllowed(DWORD dwUserFlags);

HRESULT WINAPI XOnlineMatchSessionCreate(DWORD dwPublicFilled, DWORD dwPublicOpen,
                                         DWORD dwPrivateFilled, DWORD dwPrivateOpen,
                                         DWORD dwNumAttributes, PXONLINE_ATTRIBUTE pAttributes,
                                         HANDLE hWorkEvent, PXONLINETASK_HANDLE phTask);
HRESULT WINAPI XOnlineMatchSessionUpdate(XNKID SessionID, DWORD dwPublicFilled,
                                         DWORD dwPublicOpen, DWORD dwPrivateFilled,
                                         DWORD dwPrivateOpen, DWORD dwNumAttributes,
                                         PXONLINE_ATTRIBUTE pAttributes, HANDLE hWorkEvent,
                                         PXONLINETASK_HANDLE phTask);
HRESULT WINAPI XOnlineMatchSessionGetInfo(XONLINETASK_HANDLE hTask, XNKID *pSessionID,
                                          XNKEY *pKeyExchangeKey);
HRESULT WINAPI XOnlineMatchSessionDelete(XNKID SessionID, HANDLE hWorkEvent,
                                         PXONLINETASK_HANDLE phTask);
HRESULT WINAPI XOnlineMatchSessionFindFromID(XNKID SessionID, HANDLE hWorkEvent,
                                             PXONLINETASK_HANDLE phTask);
HRESULT WINAPI XOnlineMatchSearch(DWORD dwProcedureIndex, DWORD dwNumResults,
                                  DWORD dwNumAttributes, const XONLINE_ATTRIBUTE *pAttributes,
                                  DWORD dwResultsLen, HANDLE hWorkEvent,
                                  PXONLINETASK_HANDLE phTask);
DWORD WINAPI XOnlineMatchSearchResultsLen(DWORD dwNumResults, DWORD dwNumSessionAttributes,
                                          const XONLINE_ATTRIBUTE_SPEC *pSessionAttributeSpec);
HRESULT WINAPI XOnlineMatchSearchGetResults(XONLINETASK_HANDLE hTask,
                                            PXONLINE_MATCH_SEARCHRESULT **prgpSearchResults,
                                            DWORD *pdwReturnedResults);
HRESULT WINAPI XOnlineMatchSearchParse(const XONLINE_MATCH_SEARCHRESULT *pSearchResult,
                                       DWORD dwNumSessionAttributes,
                                       const XONLINE_ATTRIBUTE_SPEC *pSessionAttributeSpec,
                                       PVOID pQuerySession);

HRESULT WINAPI XOnlineFriendsGetAcceptedGameInvite(PXONLINE_ACCEPTED_GAMEINVITE pAcceptedGameInvite);
HRESULT WINAPI XOnlineMutelistStartup(HANDLE hWorkEvent, PXONLINETASK_HANDLE phTask);
HRESULT WINAPI XOnlineMutelistGet(DWORD dwUserIndex, DWORD dwMutelistUserBufferCount,
                                  HANDLE hWorkEvent, PXONLINETASK_HANDLE phTask,
                                  PXONLINE_MUTELISTUSER pMutelistUsersBuffer,
                                  DWORD *pdwNumMutelistUsers);

/* Layout checks: the sizes the Xbox build has (the game embeds these). */
typedef char port_check_XUID[sizeof(XUID) == 0x0C ? 1 : -1];
typedef char port_check_XONLINE_USER[sizeof(XONLINE_USER) == 0x70 ? 1 : -1];
typedef char port_check_XONLINE_LOGON_STATE[sizeof(XONLINE_LOGON_STATE) == 0x204 ? 1 : -1];
typedef char port_check_XONLINE_ATTRIBUTE[sizeof(XONLINE_ATTRIBUTE) == 0x10 ? 1 : -1];
typedef char port_check_XONLINE_MATCH_SEARCHRESULT[sizeof(XONLINE_MATCH_SEARCHRESULT) == 0x54 ? 1 : -1];
typedef char port_check_XONLINE_FRIEND[sizeof(XONLINE_FRIEND) == 0x56 ? 1 : -1];
typedef char port_check_XONLINE_ACCEPTED_GAMEINVITE[sizeof(XONLINE_ACCEPTED_GAMEINVITE) == 0x9C ? 1 : -1];
typedef char port_check_XONLINE_MUTELISTUSER[sizeof(XONLINE_MUTELISTUSER) == 0x10 ? 1 : -1];

#ifdef __cplusplus
}
#endif

#endif
