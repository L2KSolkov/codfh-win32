// The Win32 port's live link for the web suite's level viewer (C:\cfh-web-suite, web/live-view.js;
// CODFH_DRAW_TRIGGERS): a WebSocket server, on every interface, that the page connects to directly.
// Off until asked for: the debug tools' Engine, Links tab, or CODFH_LIVE=1 (the port 8771) or
// CODFH_LIVE=<port>.
//
// Two channels on the one socket:
//   binary  the state, once a game frame (the newest only: a slow viewer skips frames, the game
//           never waits for it), laid out as LiveHeader, then nEntities LiveEntity records, then
//           nTriggers LiveTrigger records (all little-endian, packed);
//   text    JSON events: "hello" and "level" (the level changed: what the viewer knew is void),
//           "trigger" (a handle's trigger, with its instance ID as the viewer's objects list
//           formats it), "entity" (a slot's entity appeared), "gone" (left), "log" (a line of the
//           Script log), "result" (the answer to a command); for a page that sent {"cmd":"scripts",
//           "on":1} (the web suite's Blueprint page), "scripts" ten times a second (the live state
//           machines, trigtools.cpp's TrigWebScriptsJson) and "image" (a state machine script's
//           header, name, id and states, each state's code start and first words, once each, for
//           the page to match with its decompiled units), "functions" (the loaded functions' ids
//           and code, once a level, for following a script into the functions it calls), "vm" and
//           "settings" (the VM and Script log tabs'), and the debugger's (scriptdbg.cpp); for a
//           page that sent {"cmd":"debug","on":1} (the level viewer's debug labels), "ai" and "pg"
//           ten times a second (every AI's and projectile generator's state, with their notes,
//           trigdraw.cpp's), "gimps" and "shrimps" as often (the gimps, the shrimps and their
//           spawners) and "nodes" (the path node graph once a level, then its changes); for
//           a page that sent {"cmd":"aifull","slot":n} (the full AI view), "aifields" once (the
//           field tables) and "aifull" five times a second (that AI's memory, by class).
// Commands come back as text JSON ({"cmd":"teleport","x":..,"y":..,"z":..}, "freecam" with
// x y z yaw pitch, "freecamoff", "lookat" x y z, "edit" handle, "setting" name index value text:
// the Script log tab's settings and the debug switches; and the script debugger's, carried out
// even while it holds the game paused: "bp" addr obj on, "bpclear", "watch" obj, "callsall" on,
// "pause" obj, "continue", "step" obj, "setvar" obj index value); the server listens on every
// interface and takes commands from any viewer.
//
// The game thread (TrigLiveTick, from TrigWebTick in sub_D7880) writes each frame into the back
// buffer and swaps; one thread per viewer copies the newest under the lock and sends it.

#ifdef CODFH_DRAW_TRIGGERS

#include <xtl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "rw/bamatrix.h"
#include "rw/baframe.h"
#include "rw/baengine.h"
#include "types/type_44350.h"
#include "types/type_10F710.h"
#include "types/type_4E5D30.h"
#include "types/type_4D1DB8.h"
#include "types/AIData.h"
#include "types/type_D48D0.h"
#include "types/alfaobject.h"
#include "types/type_72810.h"
#include "game/functions.h"
#include "game/worldmgr.h"
#include "game/data.h"
#include "game/savestate.h"

#undef socket
#undef bind
#undef sendto

extern type_4E5D30 dword_4E5D30[4];
extern "C" volatile unsigned port_frame;

// (trigdraw.cpp and trigtools.cpp)
const RwChar *TrigDrawKindName(RwInt32 nKind);
RwBool TrigDrawFreeCamGet(RwV3d *pv, RwReal *pfYaw, RwReal *pfPitch);
void TrigDrawFreeCamSet(const RwV3d *pv, RwReal fYaw, RwReal fPitch);
void TrigDrawFreeCamLookAt(const RwV3d *pv);
extern RwBool g_bTrigDrawFreeCam;
void TrigWebRequestTeleport(const RwV3d *pv);
void TrigWebEditTrigger(RwInt32 nHandle);
const RwChar *TrigWebResult();
RwBool TrigWebScriptsJson(RwChar *psz, RwInt32 nMax, void (*pfnImage)(RwUInt32 dwImage));
RwBool TrigWebSettingsJson(RwChar *psz, RwInt32 nMax);
void TrigWebSetSetting(const RwChar *pszName, RwInt32 nIndex, RwInt32 nValue, const RwChar *pszText);
RwBool TrigWebVmJson(RwChar *psz, RwInt32 nMax);
RwBool TrigDrawLiveAiJson(RwChar *psz, RwInt32 nMax);
RwBool TrigDrawLivePgJson(RwChar *psz, RwInt32 nMax);
RwBool TrigDrawLiveGimpsJson(RwChar *psz, RwInt32 nMax);
RwBool TrigDrawLiveShrimpsJson(RwChar *psz, RwInt32 nMax);
RwBool TrigDrawLiveNodesJson(RwChar *psz, RwInt32 nMax, RwBool bFull);
RwBool TrigDrawLiveAiFieldsJson(RwChar *psz, RwInt32 nMax);
RwBool TrigDrawLiveAiFullJson(RwChar *psz, RwInt32 nMax, RwInt32 nSlot);
extern RwBool g_bTrigLiveDebug;
// (scriptdbg.cpp)
void TrigScriptDbgCommand(const RwChar *pszCmd, RwUInt32 dwObj, RwUInt32 dwAddr, RwInt32 nIndex, RwInt32 nValue, RwInt32 nOn);
void TrigScriptDbgTick(RwBool bWatched);

// The overlay's switch and port (trigtools.cpp's Engine, Links tab).
RwBool g_bTrigLive = FALSE;
RwInt32 g_nTrigLivePort = 8771;
RwInt32 g_nTrigLiveClients = 0;

#define LIVE_CLIENTS    4
#define LIVE_ENTITIES   768
#define LIVE_TRIGGERS   2000
#define LIVE_EVENTS     (2048 * 1024)
#define LIVE_COMMANDS   32
#define LIVE_SCRIPTS    (768 * 1024)
#define LIVE_BASES      1024

#pragma pack(push, 1)
struct LiveHeader
{
    RwUInt32 dwMagic;           // 'CFHL'
    RwUInt16 wVersion;          // 1
    RwUInt16 wFlags;            // 1 the free camera is on, 2 in a level
    RwUInt32 dwFrame;           // port_frame
    RwReal fTime;               // seconds
    RwInt32 nLevel;             // sub_19B050
    RwInt16 nPlayerSlot;        // the local player's entity slot, or -1
    RwUInt16 nEntities;
    RwUInt16 nTriggers;
    RwUInt16 wReserved;
    RwReal afCamera[14];        // the game camera: pos, right, up, at, view window x and y
    RwReal afFreeCam[5];        // the free camera: pos, yaw, pitch
    RwUInt16 awSections[4];     // the live sections (0xFFFF a free slot)
    RwInt32 nPlayerHp;
    RwInt32 nPlayerWeapon;
};
struct LiveEntity
{
    RwUInt16 wSlot;
    RwUInt8 nCategory;          // 1 player, 2 soldier, 3 vehicle, 4 pick-up, 5 animated background, 0 other
    RwUInt8 nAiState;           // AIData::unk_578, 0xFF without AI
    RwUInt32 dwFlags;           // type_3D3548::unk_2C
    RwReal afPos[3];
    RwReal afAt[3];
    RwInt16 nHp;
    RwInt8 nAlert;              // AIData::unk_520
    RwUInt8 bPad;
    RwInt16 nTarget;            // the tracked entity's slot, or -1
    RwUInt16 wPad;
};
struct LiveTrigger
{
    RwUInt16 wHandle;
    RwUInt8 nKind;
    RwUInt8 nFlags;             // 1 on, 2 proximity off, 4 moved
    RwReal afPos[3];
};
#pragma pack(pop)

typedef RwChar LiveHeader_check[sizeof(LiveHeader) == 120 ? 1 : -1];
typedef RwChar LiveEntity_check[sizeof(LiveEntity) == 40 ? 1 : -1];
typedef RwChar LiveTrigger_check[sizeof(LiveTrigger) == 16 ? 1 : -1];

#define LIVE_FRAME_MAX  (sizeof(LiveHeader) + LIVE_ENTITIES * sizeof(LiveEntity) + LIVE_TRIGGERS * sizeof(LiveTrigger))

struct LiveCommand
{
    RwChar szCmd[16];
    RwReal af[5];
    RwInt32 n;
    RwUInt32 dwObj;
    RwInt32 nIndex, nValue;
    RwChar szName[24];
    RwChar szText[40];
};

struct LiveClient
{
    SOCKET s;
    volatile LONG bUsed;        // a thread owns the slot
    volatile LONG bOpen;        // handshake done
    RwBool bMayCommand;
    volatile LONG bNeedsAll;    // the game thread announces everything to it
    volatile LONG bScripts;     // it asked for the scripts
    volatile LONG bDebug;       // it takes the debug feed (AI, generators, path nodes)
    volatile LONG nAiFull;      // the AI slot its full view shows (-1 none)
    volatile LONG bAiFields;    // ... whose tables it still needs
    volatile LONG bNewDebug;    // ... just now (the whole graph again)
    volatile LONG bWorld;       // it gets the world: the state frames, triggers and entities (a
                                // page watching the scripts does not, unless it asks: "world" 1)
    volatile LONG bNewScripts;  // ... just now (the code starts again)
    RwChar *pEvents;            // its pending text events, each NUL-ended
    RwInt32 nEvents;
    RwUInt8 *pFrame;            // its copy of the newest frame
};

static CRITICAL_SECTION s_cs;
static RwBool s_bInit, s_bRunning;
static SOCKET s_sListen = INVALID_SOCKET;
static HANDLE s_hAccept;
static LiveClient s_aClients[LIVE_CLIENTS];
static RwUInt8 *s_apFrame[2];
static RwInt32 s_anFrameLen[2];
static RwInt32 s_nFrameFront;
static volatile LONG s_dwFrameSeq;
static LiveCommand s_aCommands[LIVE_COMMANDS];
static RwInt32 s_nCommands;

// What the viewers were told about (the game thread's).
static void *s_apKnownTrigger[LIVE_TRIGGERS];
static void *s_apKnownEntity[LIVE_ENTITIES];
static RwInt32 s_nKnownLevel = -2;
static RwChar s_szLastResult[256];
static RwUInt32 s_adwKnownBase[LIVE_BASES];
static RwInt32 s_nKnownBases;
static RwChar *s_pszScripts;
static RwBool s_bFunctionsSent;
static RwBool s_bNodesSent;
static RwChar *s_pszDebug;
#define LIVE_DEBUG      (1536 * 1024)
static LARGE_INTEGER s_liStart;

// ---------------------------------------------------------------------------
// SHA-1 and Base64, for the handshake's Sec-WebSocket-Accept.

static RwUInt32 LiveRol(RwUInt32 x, RwInt32 n)
{
    return (x << n) | (x >> (32 - n));
}

// (for the handshake's short key: nLen under 240 bytes)
static void LiveSha1(const RwUInt8 *p, RwUInt32 nLen, RwUInt8 abOut[20])
{
    RwUInt32 h[5] = { 0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476, 0xC3D2E1F0 };
    RwUInt8 abMsg[256];
    RwUInt64 qwBits = (RwUInt64)nLen * 8;
    RwUInt32 nTotal = (nLen + 8) / 64 * 64 + 64, nBlock, i;

    memset(abMsg, 0, sizeof(abMsg));
    memcpy(abMsg, p, nLen);
    abMsg[nLen] = 0x80;
    for (i = 0; i < 8; i++)
        abMsg[nTotal - 1 - i] = (RwUInt8)(qwBits >> (8 * i));
    for (nBlock = 0; nBlock < nTotal; nBlock += 64)
    {
        const RwUInt8 *abBlock = abMsg + nBlock;
        RwUInt32 w[80], a, b, c, d, e;

        for (i = 0; i < 16; i++)
            w[i] = (RwUInt32)abBlock[i * 4] << 24 | (RwUInt32)abBlock[i * 4 + 1] << 16
                 | (RwUInt32)abBlock[i * 4 + 2] << 8 | abBlock[i * 4 + 3];
        for (i = 16; i < 80; i++)
            w[i] = LiveRol(w[i - 3] ^ w[i - 8] ^ w[i - 14] ^ w[i - 16], 1);
        a = h[0], b = h[1], c = h[2], d = h[3], e = h[4];
        for (i = 0; i < 80; i++)
        {
            RwUInt32 f, k, t;

            if (i < 20)
                f = (b & c) | (~b & d), k = 0x5A827999;
            else if (i < 40)
                f = b ^ c ^ d, k = 0x6ED9EBA1;
            else if (i < 60)
                f = (b & c) | (b & d) | (c & d), k = 0x8F1BBCDC;
            else
                f = b ^ c ^ d, k = 0xCA62C1D6;
            t = LiveRol(a, 5) + f + e + k + w[i];
            e = d, d = c, c = LiveRol(b, 30), b = a, a = t;
        }
        h[0] += a, h[1] += b, h[2] += c, h[3] += d, h[4] += e;
    }
    for (i = 0; i < 20; i++)
        abOut[i] = (RwUInt8)(h[i / 4] >> (24 - 8 * (i % 4)));
}

static void LiveBase64(const RwUInt8 *p, RwInt32 n, RwChar *psz)
{
    static const RwChar s_szAlphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    RwInt32 i;

    for (i = 0; i < n; i += 3)
    {
        RwUInt32 v = (RwUInt32)p[i] << 16 | (i + 1 < n ? (RwUInt32)p[i + 1] << 8 : 0) | (i + 2 < n ? p[i + 2] : 0);

        *psz++ = s_szAlphabet[(v >> 18) & 63];
        *psz++ = s_szAlphabet[(v >> 12) & 63];
        *psz++ = i + 1 < n ? s_szAlphabet[(v >> 6) & 63] : '=';
        *psz++ = i + 2 < n ? s_szAlphabet[v & 63] : '=';
    }
    *psz = 0;
}

// ---------------------------------------------------------------------------
// The socket side.

static RwBool LiveSendAll(SOCKET s, const void *p, RwInt32 n)
{
    const char *pc = (const char *)p;

    while (n > 0)
    {
        int nSent = send(s, pc, n, 0);

        if (nSent <= 0)
            return FALSE;
        pc += nSent;
        n -= nSent;
    }
    return TRUE;
}

// A WebSocket frame from the server: unmasked, opcode nOp (1 text, 2 binary, 8 close, 10 pong).
static RwBool LiveSendFrame(SOCKET s, RwInt32 nOp, const void *p, RwInt32 n)
{
    RwUInt8 ab[10];
    RwInt32 nHead;

    ab[0] = (RwUInt8)(0x80 | nOp);
    if (n < 126)
    {
        ab[1] = (RwUInt8)n;
        nHead = 2;
    }
    else if (n < 65536)
    {
        ab[1] = 126;
        ab[2] = (RwUInt8)(n >> 8);
        ab[3] = (RwUInt8)n;
        nHead = 4;
    }
    else
    {
        RwInt32 i;

        ab[1] = 127;
        for (i = 0; i < 8; i++)
            ab[2 + i] = (RwUInt8)(i < 4 ? 0 : (RwUInt32)n >> (8 * (7 - i)));
        nHead = 10;
    }
    return LiveSendAll(s, ab, nHead) && LiveSendAll(s, p, n);
}

// The number after "key": in a command's JSON (0 without it).
static RwReal LiveJsonNumber(const RwChar *psz, const RwChar *pszKey)
{
    RwChar szFind[24];
    const RwChar *p;

    _snprintf(szFind, sizeof(szFind), "\"%s\"", pszKey);
    szFind[sizeof(szFind) - 1] = 0;
    p = strstr(psz, szFind);
    if (p == NULL)
        return 0.0f;
    p = strchr(p + strlen(szFind), ':');
    return p ? (RwReal)atof(p + 1) : 0.0f;
}

// The hex string after "key": (0 without it).
static RwUInt32 LiveJsonHex(const RwChar *psz, const RwChar *pszKey)
{
    RwChar szFind[24];
    const RwChar *p;

    _snprintf(szFind, sizeof(szFind), "\"%s\"", pszKey);
    szFind[sizeof(szFind) - 1] = 0;
    p = strstr(psz, szFind);
    if (p == NULL || (p = strchr(p + strlen(szFind), '"')) == NULL)
        return 0;
    return (RwUInt32)strtoul(p + 1, NULL, 16);
}

// The string after "key": into psz (nMax bytes; empty without it).
static void LiveJsonString(const RwChar *pszJson, const RwChar *pszKey, RwChar *psz, RwInt32 nMax)
{
    RwChar szFind[24];
    const RwChar *p;
    RwInt32 i;

    psz[0] = 0;
    _snprintf(szFind, sizeof(szFind), "\"%s\"", pszKey);
    szFind[sizeof(szFind) - 1] = 0;
    p = strstr(pszJson, szFind);
    if (p == NULL || (p = strchr(p + strlen(szFind), ':')) == NULL || (p = strchr(p, '"')) == NULL)
        return;
    for (p++, i = 0; i < nMax - 1 && p[i] && p[i] != '"'; i++)
        psz[i] = p[i];
    psz[i] = 0;
}

// The script debugger's commands (scriptdbg.cpp queues them for the game thread, which runs
// them each frame or from a pause's wait).
static const RwChar *const s_apszDbgCommands[] = { "bp", "bpclear", "watch", "callsall", "pause", "continue", "step", "setvar" };

// A command from a viewer, queued for the game thread.
static void LiveCommandText(LiveClient *pClient, RwChar *psz)
{
    const RwChar *p = strstr(psz, "\"cmd\"");
    LiveCommand c;
    RwInt32 i;

    if (p == NULL)
        return;
    p = strchr(p + 5, '"');
    if (p == NULL)
        return;
    p++;
    for (i = 0; i < (RwInt32)sizeof(c.szCmd) - 1 && p[i] && p[i] != '"'; i++)
        c.szCmd[i] = p[i];
    c.szCmd[i] = 0;
    // (nor is the full AI view: it only reads)
    if (!strcmp(c.szCmd, "aifull"))
    {
        LONG nSlot = (LONG)LiveJsonNumber(psz, "slot");

        if (nSlot >= 0 && pClient->nAiFull < 0)
            InterlockedExchange(&pClient->bAiFields, 1);
        InterlockedExchange(&pClient->nAiFull, nSlot >= 0 && nSlot < 768 ? nSlot : -1);
        return;
    }
    // (nor is the debug feed)
    if (!strcmp(c.szCmd, "debug"))
    {
        LONG bOn = LiveJsonNumber(psz, "on") != 0.0f;

        if (bOn && !pClient->bDebug)
            InterlockedExchange(&pClient->bNewDebug, 1);
        InterlockedExchange(&pClient->bDebug, bOn);
        return;
    }
    // (watching the scripts is not a command: any page may)
    if (!strcmp(c.szCmd, "scripts"))
    {
        LONG bOn = LiveJsonNumber(psz, "on") != 0.0f;

        if (bOn && !pClient->bScripts)
            InterlockedExchange(&pClient->bNewScripts, 1);
        InterlockedExchange(&pClient->bScripts, bOn);
        InterlockedExchange(&pClient->bWorld, bOn ? LiveJsonNumber(psz, "world") != 0.0f : 1);
        return;
    }
    if (!pClient->bMayCommand)
        return;
    c.af[0] = LiveJsonNumber(psz, "x");
    c.af[1] = LiveJsonNumber(psz, "y");
    c.af[2] = LiveJsonNumber(psz, "z");
    c.af[3] = LiveJsonNumber(psz, "yaw");
    c.af[4] = LiveJsonNumber(psz, "pitch");
    c.n = (RwInt32)LiveJsonNumber(psz, "handle");
    c.dwObj = LiveJsonHex(psz, "obj");
    c.nIndex = (RwInt32)LiveJsonNumber(psz, "index");
    c.nValue = (RwInt32)LiveJsonNumber(psz, "value");
    for (i = 0; i < (RwInt32)(sizeof(s_apszDbgCommands) / sizeof(s_apszDbgCommands[0])); i++)
        if (!strcmp(c.szCmd, s_apszDbgCommands[i]))
        {
            TrigScriptDbgCommand(c.szCmd, c.dwObj, LiveJsonHex(psz, "addr"), c.nIndex, c.nValue, LiveJsonNumber(psz, "on") != 0.0f);
            return;
        }
    LiveJsonString(psz, "name", c.szName, sizeof(c.szName));
    LiveJsonString(psz, "text", c.szText, sizeof(c.szText));
    EnterCriticalSection(&s_cs);
    if (s_nCommands < LIVE_COMMANDS)
        s_aCommands[s_nCommands++] = c;
    LeaveCriticalSection(&s_cs);
}

// Reads what the viewer sent; FALSE when it closed. pBuf/pnBuf keep a partial frame.
static RwBool LiveReceive(LiveClient *pClient, RwUInt8 *pBuf, RwInt32 *pnBuf, RwInt32 nMax)
{
    int n = recv(pClient->s, (char *)pBuf + *pnBuf, nMax - *pnBuf, 0);

    if (n <= 0)
        return FALSE;
    *pnBuf += n;
    for (;;)
    {
        RwInt32 nOp, nHead = 2, i;
        RwUInt32 nLen;
        RwUInt8 *pMask, *pData;

        if (*pnBuf < 2)
            return TRUE;
        nOp = pBuf[0] & 15;
        nLen = pBuf[1] & 127;
        if (nLen == 126)
        {
            if (*pnBuf < 4)
                return TRUE;
            nLen = (RwUInt32)pBuf[2] << 8 | pBuf[3];
            nHead = 4;
        }
        else if (nLen == 127)
            return FALSE;           // (a viewer sends nothing that long)
        if (!(pBuf[1] & 0x80) || nLen > (RwUInt32)(nMax - nHead - 5))
            return FALSE;           // (a client's frames are masked)
        if ((RwUInt32)*pnBuf < nHead + 4 + nLen)
            return TRUE;
        pMask = pBuf + nHead;
        pData = pMask + 4;
        for (i = 0; i < (RwInt32)nLen; i++)
            pData[i] ^= pMask[i & 3];
        if (nOp == 8)
            return FALSE;
        if (nOp == 9)
            LiveSendFrame(pClient->s, 10, pData, nLen);
        else if (nOp == 1)
        {
            RwUInt8 bSaved = pData[nLen];

            pData[nLen] = 0;
            LiveCommandText(pClient, (RwChar *)pData);
            pData[nLen] = bSaved;
        }
        i = nHead + 4 + nLen;
        memmove(pBuf, pBuf + i, *pnBuf - i);
        *pnBuf -= i;
    }
}

// The handshake: reads the request, answers 101. FALSE for anything but a WebSocket upgrade.
static RwBool LiveHandshake(LiveClient *pClient)
{
    static const RwChar s_szMagic[] = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
    RwChar szReq[4096], szKey[128], szAccept[64], szReply[256];
    RwUInt8 abHash[20];
    RwInt32 n = 0, i;
    RwChar *p;

    for (;;)
    {
        int nGot = recv(pClient->s, szReq + n, (int)sizeof(szReq) - 1 - n, 0);

        if (nGot <= 0)
            return FALSE;
        n += nGot;
        szReq[n] = 0;
        if (strstr(szReq, "\r\n\r\n"))
            break;
        if (n >= (RwInt32)sizeof(szReq) - 1)
            return FALSE;
    }
    for (p = szReq; *p; p++)
        if (*p == '\n' && !_strnicmp(p + 1, "Sec-WebSocket-Key:", 18))
            break;
    if (*p == 0)
        return FALSE;
    p += 19;
    while (*p == ' ')
        p++;
    for (i = 0; i < 64 && p[i] && p[i] != '\r'; i++)
        szKey[i] = p[i];
    szKey[i] = 0;
    strcat(szKey, s_szMagic);
    LiveSha1((const RwUInt8 *)szKey, (RwUInt32)strlen(szKey), abHash);
    LiveBase64(abHash, 20, szAccept);
    // (every viewer, from any machine or page, may command)
    pClient->bMayCommand = TRUE;
    _snprintf(szReply, sizeof(szReply),
              "HTTP/1.1 101 Switching Protocols\r\nUpgrade: websocket\r\nConnection: Upgrade\r\n"
              "Sec-WebSocket-Accept: %s\r\n\r\n", szAccept);
    szReply[sizeof(szReply) - 1] = 0;
    return LiveSendAll(pClient->s, szReply, (RwInt32)strlen(szReply));
}

static DWORD WINAPI LiveClientThread(void *pArg)
{
    LiveClient *pClient = (LiveClient *)pArg;
    static const RwInt32 nMax = 16384;
    RwUInt8 *pIn = (RwUInt8 *)malloc(nMax);
    RwChar *pEvents = (RwChar *)malloc(LIVE_EVENTS);
    RwInt32 nIn = 0;
    LONG dwSent = -1;

    if (pIn && pEvents && LiveHandshake(pClient))
    {
        InterlockedExchange(&pClient->bNeedsAll, 1);
        InterlockedExchange(&pClient->bOpen, 1);
        while (s_bRunning)
        {
            fd_set fds;
            timeval tv = { 0, 4000 };
            RwInt32 nEvents, nLen = 0, i;

            FD_ZERO(&fds);
            FD_SET(pClient->s, &fds);
            if (select(0, &fds, NULL, NULL, &tv) > 0 && !LiveReceive(pClient, pIn, &nIn, nMax))
                break;
            // the events first (a frame may name what they announce), then the newest frame
            EnterCriticalSection(&s_cs);
            nEvents = pClient->nEvents;
            memcpy(pEvents, pClient->pEvents, nEvents);
            pClient->nEvents = 0;
            if (dwSent != s_dwFrameSeq && pClient->bWorld)
            {
                nLen = s_anFrameLen[s_nFrameFront];
                memcpy(pClient->pFrame, s_apFrame[s_nFrameFront], nLen);
                dwSent = s_dwFrameSeq;
            }
            LeaveCriticalSection(&s_cs);
            for (i = 0; i < nEvents; i += (RwInt32)strlen(pEvents + i) + 1)
                if (!LiveSendFrame(pClient->s, 1, pEvents + i, (RwInt32)strlen(pEvents + i)))
                    goto done;
            if (nLen && !LiveSendFrame(pClient->s, 2, pClient->pFrame, nLen))
                break;
        }
    }
done:
    InterlockedExchange(&pClient->bOpen, 0);
    closesocket(pClient->s);
    free(pIn);
    free(pEvents);
    InterlockedDecrement((LONG *)&g_nTrigLiveClients);
    InterlockedExchange(&pClient->bUsed, 0);
    return 0;
}

static DWORD WINAPI LiveAcceptThread(void *)
{
    while (s_bRunning)
    {
        SOCKET s = accept(s_sListen, NULL, NULL);
        RwInt32 i;

        if (s == INVALID_SOCKET)
            break;
        for (i = 0; i < LIVE_CLIENTS; i++)
            if (InterlockedCompareExchange(&s_aClients[i].bUsed, 1, 0) == 0)
                break;
        if (i == LIVE_CLIENTS)
        {
            closesocket(s);
            continue;
        }
        {
            BOOL bNoDelay = TRUE;

            setsockopt(s, IPPROTO_TCP, TCP_NODELAY, (const char *)&bNoDelay, sizeof(bNoDelay));
        }
        EnterCriticalSection(&s_cs);
        s_aClients[i].s = s;
        s_aClients[i].nEvents = 0;
        s_aClients[i].bScripts = 0;
        s_aClients[i].bNewScripts = 0;
        s_aClients[i].bWorld = 1;
        s_aClients[i].bDebug = 0;
        s_aClients[i].nAiFull = -1;
        s_aClients[i].bAiFields = 0;
        s_aClients[i].bNewDebug = 0;
        LeaveCriticalSection(&s_cs);
        InterlockedIncrement((LONG *)&g_nTrigLiveClients);
        CloseHandle(CreateThread(NULL, 0, LiveClientThread, &s_aClients[i], 0, NULL));
    }
    return 0;
}

static void LiveStart()
{
    WSADATA wd;
    sockaddr_in addr;
    RwInt32 i;

    if (!s_bInit)
    {
        InitializeCriticalSection(&s_cs);
        for (i = 0; i < 2; i++)
            s_apFrame[i] = (RwUInt8 *)malloc(LIVE_FRAME_MAX);
        for (i = 0; i < LIVE_CLIENTS; i++)
        {
            s_aClients[i].pEvents = (RwChar *)malloc(LIVE_EVENTS);
            s_aClients[i].pFrame = (RwUInt8 *)malloc(LIVE_FRAME_MAX);
        }
        WSAStartup(MAKEWORD(2, 2), &wd);
        s_bInit = TRUE;
    }
    s_sListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (s_sListen == INVALID_SOCKET)
    {
        g_bTrigLive = FALSE;
        return;
    }
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons((u_short)g_nTrigLivePort);
    // (every interface, so the web suite on another machine can connect)
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(s_sListen, (sockaddr *)&addr, sizeof(addr)) != 0 || listen(s_sListen, 4) != 0)
    {
        closesocket(s_sListen);
        s_sListen = INVALID_SOCKET;
        g_bTrigLive = FALSE;
        return;
    }
    s_bRunning = TRUE;
    s_hAccept = CreateThread(NULL, 0, LiveAcceptThread, NULL, 0, NULL);
}

static void LiveStop()
{
    RwInt32 i;

    s_bRunning = FALSE;
    if (s_sListen != INVALID_SOCKET)
    {
        closesocket(s_sListen);
        s_sListen = INVALID_SOCKET;
    }
    if (s_hAccept)
    {
        WaitForSingleObject(s_hAccept, 2000);
        CloseHandle(s_hAccept);
        s_hAccept = NULL;
    }
    // (each viewer's thread sees s_bRunning within a few milliseconds and closes its socket)
    for (i = 0; i < 200 && g_nTrigLiveClients > 0; i++)
        Sleep(10);
}

// ---------------------------------------------------------------------------
// The game side (the game thread).

// Appends a text event for one viewer, or (pOnly NULL) every open one; bWorldOnly: only for
// the viewers getting the world (a trigger, an entity).
static void LiveEventTo(LiveClient *pOnly, const RwChar *psz, RwBool bWorldOnly)
{
    RwInt32 n = (RwInt32)strlen(psz) + 1, i;

    if (!s_bRunning)
        return;
    EnterCriticalSection(&s_cs);
    for (i = 0; i < LIVE_CLIENTS; i++)
    {
        LiveClient *p = &s_aClients[i];

        if (!p->bOpen || (pOnly && p != pOnly) || (bWorldOnly && !p->bWorld))
            continue;
        if (p->nEvents + n <= LIVE_EVENTS)
        {
            memcpy(p->pEvents + p->nEvents, psz, n);
            p->nEvents += n;
        }
        else
            InterlockedExchange(&p->bNeedsAll, 1);  // (it fell behind: everything again)
    }
    LeaveCriticalSection(&s_cs);
}

static void LiveEvent(LiveClient *pOnly, const RwChar *psz)
{
    LiveEventTo(pOnly, psz, FALSE);
}

static void LiveEventWorld(LiveClient *pOnly, const RwChar *psz)
{
    LiveEventTo(pOnly, psz, TRUE);
}

// Appends a text event for every viewer taking the debug feed.
static void LiveEventDebug(const RwChar *psz)
{
    RwInt32 n = (RwInt32)strlen(psz) + 1, i;

    EnterCriticalSection(&s_cs);
    for (i = 0; i < LIVE_CLIENTS; i++)
    {
        LiveClient *p = &s_aClients[i];

        if (p->bOpen && p->bDebug && p->nEvents + n <= LIVE_EVENTS)
        {
            memcpy(p->pEvents + p->nEvents, psz, n);
            p->nEvents += n;
        }
    }
    LeaveCriticalSection(&s_cs);
}

// Appends a text event for every viewer watching the scripts (scriptdbg.cpp's too: any thread).
void TrigLiveScriptsEvent(const RwChar *psz);
static void LiveEventScripts(const RwChar *psz)
{
    TrigLiveScriptsEvent(psz);
}

void TrigLiveScriptsEvent(const RwChar *psz)
{
    RwInt32 n = (RwInt32)strlen(psz) + 1, i;

    EnterCriticalSection(&s_cs);
    for (i = 0; i < LIVE_CLIENTS; i++)
    {
        LiveClient *p = &s_aClients[i];

        if (p->bOpen && p->bScripts && p->nEvents + n <= LIVE_EVENTS)
        {
            memcpy(p->pEvents + p->nEvents, psz, n);
            p->nEvents += n;
        }
    }
    LeaveCriticalSection(&s_cs);
}

// Reads the word at pdw; FALSE when the memory faults.
static RwBool LiveReadWord(const RwUInt32 *pdw, RwUInt32 *pdwOut)
{
    __try
    {
        *pdwOut = *pdw;
        return TRUE;
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        return FALSE;
    }
}

// The loaded functions (kind 4 files, dword_449AA4's type_72A30 entries: unk_04 the id, unk_08
// the code), as {"t":"functions","list":[{"id":n,"code":"hex"},...]}.
static void LiveFunctions()
{
    static RwChar s_szEvent[64 * 1024];
    RwInt32 n, i, nShown = 0;

    n = sprintf(s_szEvent, "{\"t\":\"functions\",\"list\":[");
    __try
    {
        for (i = 0; dword_449AA4.unk_30 && i < dword_449AA4.unk_04; i++)
        {
            alfahash_node *pNode;

            for (pNode = dword_449AA4.unk_30[i]; pNode && n < (RwInt32)sizeof(s_szEvent) - 64; pNode = pNode->unk_04)
            {
                type_72A30 *pFunction = (type_72A30 *)pNode->unk_00;

                if (pFunction)
                    n += sprintf(s_szEvent + n, "%s{\"id\":%u,\"code\":\"%08X\"}", nShown++ ? "," : "", (RwUInt32)pFunction->unk_04,
                                 (RwUInt32)pFunction->unk_08);
            }
        }
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
    }
    strcpy(s_szEvent + n, "]}");
    LiveEventScripts(s_szEvent);
}

static void LiveImage(RwUInt32 dwImage);

// Every loaded state machine script (dword_449B0C's type_72990 entries): a machine's current
// state can be another image's than its object's (a child machine's), so the page needs them all.
static void LiveImages()
{
    RwInt32 i;

    __try
    {
        for (i = 0; dword_449B0C.unk_30 && i < dword_449B0C.unk_04; i++)
        {
            alfahash_node *pNode;

            for (pNode = dword_449B0C.unk_30[i]; pNode; pNode = pNode->unk_04)
                if (pNode->unk_00)
                    LiveImage((RwUInt32)pNode->unk_00);
        }
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
    }
}

// A state machine script (its type_72990, the image's header from its +4: unk_00 its name,
// unk_04 its id, unk_08 its 32-byte state records, unk_0C their count), the first time it is
// seen: its name, id and, for each state, its index, code start and first 4 words.
static void LiveImage(RwUInt32 dwImage)
{
    static RwChar s_szEvent[160 * 1024];
    RwInt32 i, k, n, nStates = 0;
    RwUInt32 dwName = 0, dwId = 0, dwStates = 0, dw;
    RwChar szName[64];

    for (i = 0; i < s_nKnownBases; i++)
        if (s_adwKnownBase[i] == dwImage)
            return;
    if (s_nKnownBases < LIVE_BASES)
        s_adwKnownBase[s_nKnownBases++] = dwImage;
    szName[0] = 0;
    if (LiveReadWord((const RwUInt32 *)dwImage, &dwName) && dwName)
        for (i = 0; i < (RwInt32)sizeof(szName) - 1; i++)
        {
            if (!LiveReadWord((const RwUInt32 *)((dwName + i) & ~3u), &dw))
                break;
            szName[i] = (RwChar)(dw >> (8 * ((dwName + i) & 3)));
            if (szName[i] == 0)
                break;
            if (szName[i] == '"' || szName[i] == '\\' || (RwUInt8)szName[i] < 0x20)
                szName[i] = '_';
        }
    szName[sizeof(szName) - 1] = 0;
    szName[i < (RwInt32)sizeof(szName) ? i : (RwInt32)sizeof(szName) - 1] = 0;
    LiveReadWord((const RwUInt32 *)dwImage + 1, &dwId);
    LiveReadWord((const RwUInt32 *)dwImage + 2, &dwStates);
    if (LiveReadWord((const RwUInt32 *)dwImage + 3, &dw))
        nStates = (RwInt32)(dw & 0xFFFF);
    if (nStates > 1024)
        nStates = 1024;
    n = sprintf(s_szEvent, "{\"t\":\"image\",\"addr\":\"%08X\",\"id\":%u,\"name\":\"%s\",\"states\":[", dwImage, dwId, szName);
    for (i = 0; dwStates && i < nStates && n < (RwInt32)sizeof(s_szEvent) - 400; i++)
    {
        RwUInt32 dwRec = dwStates + i * 32, dwCode = 0, dwIndex = 0;

        if (!LiveReadWord((const RwUInt32 *)dwRec + 1, &dwCode) || !LiveReadWord((const RwUInt32 *)dwRec + 4, &dwIndex))
            break;
        n += sprintf(s_szEvent + n, "%s{\"index\":%d,\"code\":\"%08X\",\"words\":[", i ? "," : "", (RwInt16)(dwIndex & 0xFFFF), dwCode);
        for (k = 0; dwCode && k < 4 && LiveReadWord((const RwUInt32 *)dwCode + k, &dw); k++)
            n += sprintf(s_szEvent + n, "%s%u", k ? "," : "", dw);
        n += sprintf(s_szEvent + n, "]}");
    }
    strcpy(s_szEvent + n, "]}");
    LiveEventScripts(s_szEvent);
}

// A string as JSON's quoted text, into psz (nMax bytes).
static void LiveQuote(const RwChar *pszIn, RwChar *psz, RwInt32 nMax)
{
    RwInt32 n = 0;

    psz[n++] = '"';
    for (; *pszIn && n < nMax - 8; pszIn++)
    {
        RwUInt8 c = (RwUInt8)*pszIn;

        if (c == '"' || c == '\\')
            psz[n++] = '\\', psz[n++] = (RwChar)c;
        else if (c < 0x20)
            n += sprintf(psz + n, "\\u%04x", c);
        else
            psz[n++] = (RwChar)c;
    }
    psz[n++] = '"';
    psz[n] = 0;
}

// A line of the Script log for the viewers (any thread; trigtools.cpp's TrigWebScriptReport).
void TrigLiveLog(const RwChar *pszLine)
{
    RwChar szText[600], szEvent[700];

    if (!s_bRunning || g_nTrigLiveClients <= 0)
        return;
    LiveQuote(pszLine, szText, sizeof(szText));
    _snprintf(szEvent, sizeof(szEvent), "{\"t\":\"log\",\"frame\":%u,\"text\":%s}", port_frame, szText);
    szEvent[sizeof(szEvent) - 1] = 0;
    LiveEvent(NULL, szEvent);
}

// The entity's category, its AI's state and alertness, its tracked entity, its place.
static RwBool LiveReadEntity(type_3D3548 *pEntity, LiveEntity *pOut, type_3D3548 **ppTarget)
{
    __try
    {
        RwFrame *pFrame = pEntity->unk_338.unk_08;
        RwMatrix *pM;
        AIData *pAi;
        RwUInt32 dwBits = pEntity->unk_2C;

        if (pFrame == NULL)
            return FALSE;
        pM = RwFrameGetMatrix(pFrame);
        pOut->afPos[0] = pM->pos.x, pOut->afPos[1] = pM->pos.y, pOut->afPos[2] = pM->pos.z;
        pOut->afAt[0] = pM->at.x, pOut->afAt[1] = pM->at.y, pOut->afAt[2] = pM->at.z;
        pOut->dwFlags = dwBits;
        pOut->nCategory = (dwBits & 0x10) ? 1 : (dwBits & 0x20) ? 2 : pEntity->vf_014() ? 3
                        : (dwBits & 0x4000) ? 4 : (dwBits & 0x100) ? 5 : 0;
        pOut->nHp = (RwInt16)pEntity->vf_174();
        pOut->nAiState = 0xFF;
        pOut->nAlert = -1;
        *ppTarget = NULL;
        pAi = (dwBits & 0x10) ? NULL : pEntity->vf_120();
        if (pAi)
        {
            pOut->nAiState = (RwUInt8)pAi->get_unk_578();
            pOut->nAlert = (RwInt8)pAi->get_unk_520();
            *ppTarget = pAi->unk_1374.sub_D4910();
        }
        return TRUE;
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        return FALSE;
    }
}

static RwBool LiveReadTrigger(Trigger *pTrigger, LiveTrigger *pOut)
{
    __try
    {
        pOut->nKind = (RwUInt8)pTrigger->vf_008();
        pOut->nFlags = (RwUInt8)((pTrigger->unk_24_0 ? 1 : 0) | (pTrigger->unk_24_3 ? 2 : 0) | (pTrigger->unk_24_15 ? 4 : 0));
        pOut->afPos[0] = pTrigger->unk_90, pOut->afPos[1] = pTrigger->unk_94, pOut->afPos[2] = pTrigger->unk_98;
        return TRUE;
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        return FALSE;
    }
}

// The trigger's announcement: its handle, kind, class and instance ID (CAttributeHandler's
// m_InstanceId at +8, four little-endian words as the viewer prints them).
static void LiveAnnounceTrigger(LiveClient *pOnly, RwInt32 nHandle, Trigger *pTrigger, RwInt32 nKind)
{
    RwChar szEvent[256];
    const RwUInt32 *pdw = (const RwUInt32 *)((const RwUInt8 *)pTrigger + 8);
    const RwChar *pszClass = TrigDrawKindName(nKind);

    _snprintf(szEvent, sizeof(szEvent),
              "{\"t\":\"trigger\",\"handle\":%d,\"kind\":%d,\"class\":\"%s\",\"guid\":\"%08X-%08X-%08X-%08X\"}",
              nHandle, nKind, pszClass ? pszClass : "?", pdw[0], pdw[1], pdw[2], pdw[3]);
    szEvent[sizeof(szEvent) - 1] = 0;
    LiveEventWorld(pOnly, szEvent);
}

static void LiveAnnounceEntity(LiveClient *pOnly, RwInt32 nSlot, const LiveEntity *p)
{
    static const RwChar *const s_apszCategory[6] = { "other", "player", "soldier", "vehicle", "pickup", "background" };
    RwChar szEvent[160];

    _snprintf(szEvent, sizeof(szEvent), "{\"t\":\"entity\",\"slot\":%d,\"category\":\"%s\",\"flags\":%u}", nSlot,
              s_apszCategory[p->nCategory < 6 ? p->nCategory : 0], p->dwFlags);
    szEvent[sizeof(szEvent) - 1] = 0;
    LiveEventWorld(pOnly, szEvent);
}

static void LiveHello(LiveClient *pOnly, RwInt32 nLevel, const RwChar *pszType)
{
    RwChar szEvent[200];
    const RwChar *pszName = nLevel >= 0 ? sub_19B060(nLevel) : NULL;

#ifdef CODFH_SP
    const RwChar *pszBuild = "sp";
#else
    const RwChar *pszBuild = "mp";
#endif
    _snprintf(szEvent, sizeof(szEvent), "{\"t\":\"%s\",\"version\":1,\"build\":\"%s\",\"level\":%d,\"name\":\"%s\"}",
              pszType, pszBuild, nLevel, pszName ? pszName : "");
    szEvent[sizeof(szEvent) - 1] = 0;
    LiveEvent(pOnly, szEvent);
}

// The queued commands, on the game thread.
static void LiveRunCommands()
{
    LiveCommand aCmd[LIVE_COMMANDS];
    RwInt32 n, i;

    EnterCriticalSection(&s_cs);
    n = s_nCommands;
    memcpy(aCmd, s_aCommands, n * sizeof(LiveCommand));
    s_nCommands = 0;
    LeaveCriticalSection(&s_cs);
    for (i = 0; i < n; i++)
    {
        LiveCommand *c = &aCmd[i];
        RwV3d v;

        v.x = c->af[0], v.y = c->af[1], v.z = c->af[2];
        if (!strcmp(c->szCmd, "teleport"))
            TrigWebRequestTeleport(&v);
        else if (!strcmp(c->szCmd, "freecam"))
            TrigDrawFreeCamSet(&v, c->af[3], c->af[4]);
        else if (!strcmp(c->szCmd, "freecamoff"))
            g_bTrigDrawFreeCam = FALSE;
        else if (!strcmp(c->szCmd, "lookat"))
            TrigDrawFreeCamLookAt(&v);
        else if (!strcmp(c->szCmd, "edit"))
            TrigWebEditTrigger(c->n);
        else if (!strcmp(c->szCmd, "setting"))
            TrigWebSetSetting(c->szName, c->nIndex, c->nValue, c->szText);
    }
}

// Once a game frame (TrigWebTick): starts or stops the server as the switch says, runs the
// viewers' commands, announces what changed and builds the frame.
void TrigLiveTick()
{
    static RwInt32 s_nEnv = -1;
    RwUInt8 *pFrame;
    LiveHeader *pHead;
    LiveEntity *pEntities;
    LiveTrigger *pTriggers;
    type_3D3548 *apTarget[LIVE_ENTITIES];
    type_3D3548 *pPlayer;
    RwInt32 i, j, nLevel, nBack, nLast;
    RwBool bAll = FALSE;
    LARGE_INTEGER liNow, liFreq;
    RwV3d vFree;
    RwReal fYaw, fPitch;
    const RwChar *pszResult;

    if (s_nEnv < 0)
    {
        RwChar szValue[16];

        s_nEnv = GetEnvironmentVariableA("CODFH_LIVE", szValue, sizeof(szValue)) ? atoi(szValue) : 0;
        if (s_nEnv > 0)
        {
            g_bTrigLive = TRUE;
            if (s_nEnv > 1)
                g_nTrigLivePort = s_nEnv;
        }
    }
    if (g_bTrigLive && !s_bRunning)
        LiveStart();
    else if (!g_bTrigLive && s_bRunning)
        LiveStop();
    if (!s_bRunning)
        return;
    LiveRunCommands();
    pszResult = TrigWebResult();
    if (pszResult && strcmp(pszResult, s_szLastResult))
    {
        RwChar szText[300], szEvent[360];

        strncpy(s_szLastResult, pszResult, sizeof(s_szLastResult) - 1);
        LiveQuote(pszResult, szText, sizeof(szText));
        _snprintf(szEvent, sizeof(szEvent), "{\"t\":\"result\",\"text\":%s}", szText);
        szEvent[sizeof(szEvent) - 1] = 0;
        LiveEvent(NULL, szEvent);
    }
    if (g_nTrigLiveClients <= 0)
        return;

    // the level: a change voids what the viewers were told
    nLevel = dword_4E5C74 ? sub_19B050() : -1;
    if (nLevel != s_nKnownLevel)
    {
        memset(s_apKnownTrigger, 0, sizeof(s_apKnownTrigger));
        memset(s_apKnownEntity, 0, sizeof(s_apKnownEntity));
        s_nKnownBases = 0;
        s_bFunctionsSent = FALSE;
        s_bNodesSent = FALSE;
        s_nKnownLevel = nLevel;
        LiveHello(NULL, nLevel, "level");
    }
    // a new viewer: everything, to it
    for (i = 0; i < LIVE_CLIENTS; i++)
        if (s_aClients[i].bOpen && InterlockedExchange(&s_aClients[i].bNeedsAll, 0))
        {
            LiveHello(&s_aClients[i], nLevel, "hello");
            bAll = TRUE;
        }

    // the scripts, ten times a second, for the pages watching them (a new one: the code starts again)
    {
        RwBool bWatched = FALSE;

        for (i = 0; i < LIVE_CLIENTS; i++)
            if (s_aClients[i].bOpen && s_aClients[i].bScripts)
            {
                bWatched = TRUE;
                if (InterlockedExchange(&s_aClients[i].bNewScripts, 0))
                {
                    s_nKnownBases = 0;
                    s_bFunctionsSent = FALSE;
                }
            }
        if (s_pszScripts == NULL)
            s_pszScripts = (RwChar *)malloc(LIVE_SCRIPTS);
        if (bWatched && nLevel >= 0 && !s_bFunctionsSent)
        {
            s_bFunctionsSent = TRUE;
            LiveFunctions();
            LiveImages();
        }
        if (bWatched && nLevel >= 0 && port_frame % 6 == 0 && s_pszScripts)
        {
            if (TrigWebScriptsJson(s_pszScripts, LIVE_SCRIPTS, LiveImage))
                LiveEventScripts(s_pszScripts);
            if (TrigWebVmJson(s_pszScripts, LIVE_SCRIPTS))
                LiveEventScripts(s_pszScripts);
        }
        if (bWatched && port_frame % 30 == 0 && s_pszScripts && TrigWebSettingsJson(s_pszScripts, LIVE_SCRIPTS))
            LiveEventScripts(s_pszScripts);
        TrigScriptDbgTick(bWatched);
    }

    // the debug feed, for the viewers taking it (a new one: the whole graph again)
    {
        RwBool bDebug = FALSE;

        for (i = 0; i < LIVE_CLIENTS; i++)
            if (s_aClients[i].bOpen && s_aClients[i].bDebug)
            {
                bDebug = TRUE;
                if (InterlockedExchange(&s_aClients[i].bNewDebug, 0))
                    s_bNodesSent = FALSE;
            }
        g_bTrigLiveDebug = bDebug;
        if (bDebug && nLevel >= 0)
        {
            if (s_pszDebug == NULL)
                s_pszDebug = (RwChar *)malloc(LIVE_DEBUG);
            if (s_pszDebug && (!s_bNodesSent || port_frame % 30 == 0))
            {
                TrigDrawLiveNodesJson(s_pszDebug, LIVE_DEBUG, !s_bNodesSent);
                s_bNodesSent = TRUE;
                LiveEventDebug(s_pszDebug);
            }
            // the full AI views, each viewer its own AI
            for (i = 0; s_pszDebug && i < LIVE_CLIENTS; i++)
            {
                LiveClient *pc = &s_aClients[i];

                if (!pc->bOpen || pc->nAiFull < 0)
                    continue;
                if (InterlockedExchange(&pc->bAiFields, 0))
                {
                    TrigDrawLiveAiFieldsJson(s_pszDebug, LIVE_DEBUG);
                    LiveEventTo(pc, s_pszDebug, FALSE);
                }
                if (port_frame % 12 == 5)
                {
                    TrigDrawLiveAiFullJson(s_pszDebug, LIVE_DEBUG, pc->nAiFull);
                    LiveEventTo(pc, s_pszDebug, FALSE);
                }
            }
            if (s_pszDebug && port_frame % 6 == 3)
            {
                TrigDrawLiveAiJson(s_pszDebug, LIVE_DEBUG);
                LiveEventDebug(s_pszDebug);
                TrigDrawLivePgJson(s_pszDebug, LIVE_DEBUG);
                LiveEventDebug(s_pszDebug);
            }
            // the gimps and shrimps, between the AI's frames
            if (s_pszDebug && port_frame % 6 == 0)
            {
                TrigDrawLiveGimpsJson(s_pszDebug, LIVE_DEBUG);
                LiveEventDebug(s_pszDebug);
                TrigDrawLiveShrimpsJson(s_pszDebug, LIVE_DEBUG);
                LiveEventDebug(s_pszDebug);
            }
        }
    }

    nBack = 1 - s_nFrameFront;
    pFrame = s_apFrame[nBack];
    pHead = (LiveHeader *)pFrame;
    memset(pHead, 0, sizeof(*pHead));
    pHead->dwMagic = 0x4C484643;
    pHead->wVersion = 1;
    pHead->dwFrame = port_frame;
    // (seconds since the link started: a float of the raw counter would lose the milliseconds)
    QueryPerformanceCounter(&liNow);
    QueryPerformanceFrequency(&liFreq);
    if (s_liStart.QuadPart == 0)
        s_liStart = liNow;
    pHead->fTime = (RwReal)((double)(liNow.QuadPart - s_liStart.QuadPart) / (double)liFreq.QuadPart);
    pHead->nLevel = nLevel;
    pHead->nPlayerSlot = -1;
    if (dword_4E5C74)
    {
        RwCamera *pCamera = (RwCamera *)dword_4E5C74;
        RwMatrix *pM = RwFrameGetLTM(RwCameraGetFrame(pCamera));

        pHead->wFlags |= 2;
        memcpy(&pHead->afCamera[0], &pM->pos, 12);
        memcpy(&pHead->afCamera[3], &pM->right, 12);
        memcpy(&pHead->afCamera[6], &pM->up, 12);
        memcpy(&pHead->afCamera[9], &pM->at, 12);
        pHead->afCamera[12] = pCamera->viewWindow.x;
        pHead->afCamera[13] = pCamera->viewWindow.y;
    }
    if (TrigDrawFreeCamGet(&vFree, &fYaw, &fPitch))
    {
        pHead->wFlags |= 1;
        pHead->afFreeCam[0] = vFree.x, pHead->afFreeCam[1] = vFree.y, pHead->afFreeCam[2] = vFree.z;
        pHead->afFreeCam[3] = fYaw, pHead->afFreeCam[4] = fPitch;
    }
    for (i = 0; i < 4; i++)
        pHead->awSections[i] = dword_4E5D30[i].unk_00 ? dword_4E5D30[i].unk_08 : 0xFFFF;

    // the entities
    pPlayer = dword_4E5C74 ? sub_1745A0(0) : NULL;
    pEntities = (LiveEntity *)(pFrame + sizeof(LiveHeader));
    for (i = 0; i < LIVE_ENTITIES; i++)
    {
        type_3D3548 *pEntity = dword_4E5C74 ? dword_4B6A00[i].unk_04 : NULL;
        LiveEntity *p = &pEntities[pHead->nEntities];

        if (pEntity != NULL && LiveReadEntity(pEntity, p, &apTarget[pHead->nEntities]))
        {
            p->wSlot = (RwUInt16)i;
            p->nTarget = -1;
            p->bPad = 0;
            p->wPad = 0;
            if (bAll || s_apKnownEntity[i] != pEntity)
                LiveAnnounceEntity(NULL, i, p);
            if (pEntity == pPlayer)
            {
                pHead->nPlayerSlot = (RwInt16)i;
                pHead->nPlayerHp = p->nHp;
                __try
                {
                    pHead->nPlayerWeapon = ((type_10F710 *)pPlayer)->unk_1AE4;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                }
            }
            pHead->nEntities++;
        }
        else if (s_apKnownEntity[i] != NULL)
        {
            RwChar szEvent[48];

            sprintf(szEvent, "{\"t\":\"gone\",\"slot\":%d}", i);
            LiveEventWorld(NULL, szEvent);
            pEntity = NULL;
        }
        else
            pEntity = NULL;
        s_apKnownEntity[i] = pEntity;
    }
    // (each tracked entity as its slot)
    for (i = 0; i < pHead->nEntities; i++)
        if (apTarget[i])
            for (j = 0; j < pHead->nEntities; j++)
                if (dword_4B6A00[pEntities[j].wSlot].unk_04 == apTarget[i])
                {
                    pEntities[i].nTarget = (RwInt16)pEntities[j].wSlot;
                    break;
                }

    // the triggers
    pTriggers = (LiveTrigger *)(pEntities + pHead->nEntities);
    nLast = dword_4E5C74 ? dword_429D00 : -1;
    for (i = 0; i < LIVE_TRIGGERS; i++)
    {
        Trigger *pTrigger = i <= nLast ? (Trigger *)dword_4CFE30[i] : NULL;
        LiveTrigger *p = &pTriggers[pHead->nTriggers];

        if (pTrigger != NULL && LiveReadTrigger(pTrigger, p))
        {
            p->wHandle = (RwUInt16)i;
            if (bAll || s_apKnownTrigger[i] != pTrigger)
                LiveAnnounceTrigger(NULL, i, pTrigger, p->nKind);
            pHead->nTriggers++;
        }
        else
            pTrigger = NULL;
        s_apKnownTrigger[i] = pTrigger;
    }

    EnterCriticalSection(&s_cs);
    s_anFrameLen[nBack] = (RwInt32)((RwUInt8 *)(pTriggers + pHead->nTriggers) - pFrame);
    s_nFrameFront = nBack;
    s_dwFrameSeq++;
    LeaveCriticalSection(&s_cs);
}

#endif // CODFH_DRAW_TRIGGERS
