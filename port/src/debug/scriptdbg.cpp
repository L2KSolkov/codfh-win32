// The Win32 port's script debugger (CODFH_DRAW_TRIGGERS), for the web suite's Blueprint page over
// the live link (trigweb.cpp): the script VM's loop (sub_68310, unit_067B10) calls TrigScriptStep
// before each instruction while g_bTrigScriptStep is set, which is while something needs it:
//   a watched script  each instruction it runs goes into the trace, sent as {"t":"trace"} once a
//                     game frame, so the page can follow it exactly (between runs it only ever
//                     sees the yield points);
//   calls             each command call (opcode 21, sub_69330) of the watched script, or of every
//                     script, with its arguments (the top unk_0C stack words before the call, the
//                     first popped last) and its results (the top unk_14 after), sent as
//                     {"t":"calls"};
//   breakpoints       code addresses, each for any script or for one object; reaching one pauses;
//   step / pause      pauses at the next instruction of a script (the stepped one, or any).
// Pausing stops the game thread inside the VM, before the instruction runs: the page gets
// {"t":"paused"} with the VM's registers, the stack's top, the script's variables and, at a
// call, the command and its arguments; the viewer threads keep serving, and the queued debugger
// commands (continue, step, breakpoints, a variable or stack word set) are carried out from the
// wait. With no viewer left the game goes on by itself.

#ifdef CODFH_DRAW_TRIGGERS

#include <xtl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rw/ostypes.h"
#include "types/type_44350.h"
#include "types/scriptvm.h"
#include "types/alfaobject.h"
#include "types/alfaobjman.h"

extern "C" volatile unsigned port_frame;

// (trigweb.cpp and trigtools.cpp)
void TrigLiveScriptsEvent(const RwChar *psz);
extern RwInt32 g_nTrigLiveClients;
void TrigWebCommandName(RwInt32 nIndex, RwChar *pszOut);
void TrigWebScriptName(void *pScript, RwChar *pszOut, RwInt32 nMax);

RwBool g_bTrigScriptStep = FALSE;

#define DBG_BREAKPOINTS 64
#define DBG_TRACE       8192
#define DBG_CALLS       512
#define DBG_COMMANDS    64
#define DBG_ARGS        12

struct DbgBreakpoint
{
    RwUInt32 dwAddr;
    RwUInt32 dwObj;             // 0: any script
};

struct DbgCall
{
    RwUInt32 dwObj, dwCode;
    RwInt32 nIndex;
    RwInt32 nArgs, nResults;
    RwInt32 anArgs[DBG_ARGS];
    RwInt32 anResults[4];
    RwBool bResults;
};

struct DbgCommand
{
    RwChar szCmd[16];
    RwUInt32 dwObj, dwAddr;
    RwInt32 nIndex, nValue, nOn;
};

static CRITICAL_SECTION s_cs;
static RwBool s_bInit;
static DbgBreakpoint s_aBreak[DBG_BREAKPOINTS];
static RwInt32 s_nBreak;
static RwUInt32 s_dwWatch;              // the traced script (0 none)
static RwBool s_bCallsAll;              // calls of every script, not only the watched one
static RwUInt32 s_adwTrace[DBG_TRACE];
static RwInt32 s_nTrace;
static RwBool s_bTraceFull;
static DbgCall s_aCalls[DBG_CALLS];
static RwInt32 s_nCalls;
static RwInt32 s_nCallsDropped;
static DbgCall *s_pPendingResult;       // the last call, until the next instruction of its script
static volatile LONG s_bPaused;
static RwUInt32 s_dwStepObj;            // step: pause at its next instruction (1: any script's)
static RwBool s_bStepPending;
static DbgCommand s_aCommands[DBG_COMMANDS];
static RwInt32 s_nCommands;
static RwBool s_bReportedState;

static void DbgInit()
{
    if (!s_bInit)
    {
        InitializeCriticalSection(&s_cs);
        s_bInit = TRUE;
    }
}

// Whether the hook is needed at all.
static void DbgUpdateHook()
{
    g_bTrigScriptStep = s_nBreak > 0 || s_dwWatch != 0 || s_bCallsAll || s_bStepPending;
}

static RwBool DbgRead(const void *p, RwUInt32 *pdw)
{
    __try
    {
        *pdw = *(const RwUInt32 *)p;
        return TRUE;
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        return FALSE;
    }
}

static void DbgWrite(void *p, RwUInt32 dw)
{
    __try
    {
        *(RwUInt32 *)p = dw;
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
    }
}

// The debugger's state, so the page can show it (breakpoints, the watched script, pausing).
static void DbgSendState()
{
    RwChar sz[4096];
    RwInt32 n, i;

    n = sprintf(sz, "{\"t\":\"debugger\",\"paused\":%d,\"watch\":\"%08X\",\"callsAll\":%d,\"breakpoints\":[", (RwInt32)s_bPaused,
                s_dwWatch, (RwInt32)s_bCallsAll);
    for (i = 0; i < s_nBreak; i++)
        n += sprintf(sz + n, "%s{\"addr\":\"%08X\",\"obj\":\"%08X\"}", i ? "," : "", s_aBreak[i].dwAddr, s_aBreak[i].dwObj);
    strcpy(sz + n, "]}");
    TrigLiveScriptsEvent(sz);
}

static void DbgSetBreak(RwUInt32 dwAddr, RwUInt32 dwObj, RwBool bOn)
{
    RwInt32 i;

    for (i = 0; i < s_nBreak; i++)
        if (s_aBreak[i].dwAddr == dwAddr && s_aBreak[i].dwObj == dwObj)
            break;
    if (bOn && i == s_nBreak && s_nBreak < DBG_BREAKPOINTS)
    {
        s_aBreak[s_nBreak].dwAddr = dwAddr;
        s_aBreak[s_nBreak].dwObj = dwObj;
        s_nBreak++;
    }
    else if (!bOn && i < s_nBreak)
        s_aBreak[i] = s_aBreak[--s_nBreak];
}

// A machine's variable, or (index -1 - n) the paused VM's stack word n down from the top.
static void DbgSetValue(RwUInt32 dwObj, RwInt32 nIndex, RwInt32 nValue)
{
    if (nIndex < 0)
    {
        RwInt32 nDown = -1 - nIndex;

        if (s_bPaused && dword_449318 && nDown < 64)
            DbgWrite(dword_449318 - 1 - nDown, (RwUInt32)nValue);
        return;
    }
    __try
    {
        type_3D2DB8 *pMachine = (type_3D2DB8 *)dwObj;

        if (dwObj && pMachine->unk_74 && nIndex < (RwInt32)(pMachine->unk_78 / 4))
            pMachine->unk_74[nIndex] = nValue;
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
    }
}

// The queued commands (the game thread: each frame, and from a pause's wait).
static void DbgRunCommands()
{
    DbgCommand aCmd[DBG_COMMANDS];
    RwInt32 n, i;
    RwBool bChanged = FALSE;

    DbgInit();
    EnterCriticalSection(&s_cs);
    n = s_nCommands;
    memcpy(aCmd, s_aCommands, n * sizeof(DbgCommand));
    s_nCommands = 0;
    LeaveCriticalSection(&s_cs);
    for (i = 0; i < n; i++)
    {
        DbgCommand *c = &aCmd[i];

        bChanged = TRUE;
        if (!strcmp(c->szCmd, "bp"))
            DbgSetBreak(c->dwAddr, c->dwObj, c->nOn);
        else if (!strcmp(c->szCmd, "bpclear"))
            s_nBreak = 0;
        else if (!strcmp(c->szCmd, "watch"))
        {
            s_dwWatch = c->dwObj;
            s_nTrace = 0;
        }
        else if (!strcmp(c->szCmd, "callsall"))
            s_bCallsAll = c->nOn;
        else if (!strcmp(c->szCmd, "pause"))
        {
            s_dwStepObj = c->dwObj ? c->dwObj : 1;
            s_bStepPending = TRUE;
        }
        else if (!strcmp(c->szCmd, "continue"))
        {
            s_bStepPending = FALSE;
            InterlockedExchange(&s_bPaused, 0);
        }
        else if (!strcmp(c->szCmd, "step"))
        {
            // (the paused script's next instruction, or any script's when none is named)
            s_dwStepObj = c->dwObj ? c->dwObj : (RwUInt32)dword_449328;
            if (s_dwStepObj == 0)
                s_dwStepObj = 1;
            s_bStepPending = TRUE;
            InterlockedExchange(&s_bPaused, 0);
        }
        else if (!strcmp(c->szCmd, "setvar"))
        {
            DbgSetValue(c->dwObj, c->nIndex, c->nValue);
            bChanged = FALSE;
        }
    }
    DbgUpdateHook();
    if (bChanged || !s_bReportedState)
    {
        s_bReportedState = TRUE;
        DbgSendState();
    }
}

// A command from a viewer (any thread: a viewer's, while the game is paused too).
void TrigScriptDbgCommand(const RwChar *pszCmd, RwUInt32 dwObj, RwUInt32 dwAddr, RwInt32 nIndex, RwInt32 nValue, RwInt32 nOn)
{
    DbgInit();
    EnterCriticalSection(&s_cs);
    if (s_nCommands < DBG_COMMANDS)
    {
        DbgCommand *c = &s_aCommands[s_nCommands++];

        strncpy(c->szCmd, pszCmd, sizeof(c->szCmd) - 1);
        c->szCmd[sizeof(c->szCmd) - 1] = 0;
        c->dwObj = dwObj;
        c->dwAddr = dwAddr;
        c->nIndex = nIndex;
        c->nValue = nValue;
        c->nOn = nOn;
    }
    LeaveCriticalSection(&s_cs);
}

// The call at the code pointer: its command's record (Base), or NULL.
static type_44350 *DbgCallRecord(const RwInt32 *pCode, RwInt32 *pnIndex)
{
    RwUInt32 dwWord, dwBase, dwCount;

    if (!DbgRead(pCode, &dwWord) || (dwWord & 0xFF) != 21)
        return NULL;
    *pnIndex = (RwInt16)(dwWord >> 16);
    if (!DbgRead(&Base, &dwBase) || !DbgRead(&NumOfElements, &dwCount) || dwBase == 0 || *pnIndex < 0
        || *pnIndex >= (RwInt32)dwCount)
        return NULL;
    return (type_44350 *)dwBase + *pnIndex;
}

// The top n stack words, the deepest first.
static RwInt32 DbgStackTop(RwInt32 *pn, RwInt32 nMax, RwInt32 nWant)
{
    RwInt32 i, n = nWant < nMax ? nWant : nMax;
    RwUInt32 dw;

    if (dword_449318 == NULL)
        return 0;
    for (i = 0; i < n; i++)
    {
        if (!DbgRead(dword_449318 - n + i, &dw))
            return i;
        pn[i] = (RwInt32)dw;
    }
    return n;
}

static void DbgJsonInts(RwChar *psz, RwInt32 *pn, const RwInt32 *pnValues, RwInt32 nCount)
{
    RwInt32 i;

    *pn += sprintf(psz + *pn, "[");
    for (i = 0; i < nCount; i++)
        *pn += sprintf(psz + *pn, "%s%d", i ? "," : "", pnValues[i]);
    *pn += sprintf(psz + *pn, "]");
}

// Waits, paused before the instruction at the code pointer of the running script.
static void DbgPause(const RwChar *pszReason)
{
    static RwChar s_sz[8192];
    RwChar szName[96], szCommand[64];
    RwInt32 n, anStack[32], nStack, anVars[64], nVars = 0, nIndex = -1, i;
    RwUInt32 dwObj = (RwUInt32)dword_449328, dwVars = 0, dwSize = 0, dwWord = 0;
    type_44350 *pRecord;

    if (g_nTrigLiveClients <= 0)
        return;
    TrigWebScriptName(dword_449328, szName, sizeof(szName));
    for (i = 0; szName[i]; i++)
        if (szName[i] == '"' || szName[i] == '\\')
            szName[i] = '_';
    nStack = DbgStackTop(anStack, 32, 32);
    // (a state machine's: one of m_stateMachineObjectPool's elements, as the overlay's tables tell)
    if (dwObj >= (RwUInt32)dword_449A30.unk_04
        && dwObj < (RwUInt32)dword_449A30.unk_04 + (RwUInt32)(dword_449A30.unk_0C * dword_449A30.unk_10))
    {
        DbgRead(&((type_3D2DB8 *)dwObj)->unk_74, &dwVars);
        DbgRead(&((type_3D2DB8 *)dwObj)->unk_78, &dwSize);
    }
    for (i = 0; dwVars && i < (RwInt32)(dwSize / 4) && i < 64; i++)
    {
        RwUInt32 dw;

        if (!DbgRead((RwInt32 *)dwVars + i, &dw))
            break;
        anVars[nVars++] = (RwInt32)dw;
    }
    DbgRead(dword_449320, &dwWord);
    InterlockedExchange(&s_bPaused, 1);
    n = sprintf(s_sz, "{\"t\":\"paused\",\"reason\":\"%s\",\"frame\":%u,\"obj\":\"%08X\",\"name\":\"%s\",\"code\":\"%08X\","
                "\"word\":%u,\"sp\":\"%08X\",\"fp\":\"%08X\",\"fourth\":%d,\"stack\":",
                pszReason, port_frame, dwObj, szName, (RwUInt32)dword_449320, dwWord, (RwUInt32)dword_449318,
                (RwUInt32)dword_44931C, dword_4492E0);
    DbgJsonInts(s_sz, &n, anStack, nStack);
    n += sprintf(s_sz + n, ",\"vars\":");
    DbgJsonInts(s_sz, &n, anVars, nVars);
    pRecord = DbgCallRecord(dword_449320, &nIndex);
    if (pRecord)
    {
        RwInt32 anArgs[DBG_ARGS], nArgs = 0;
        RwUInt32 dwArgs = 0, dwResults = 0;

        DbgRead(&pRecord->unk_0C, &dwArgs);
        DbgRead(&pRecord->unk_14, &dwResults);
        nArgs = DbgStackTop(anArgs, DBG_ARGS, (RwInt32)dwArgs);
        TrigWebCommandName(nIndex, szCommand);
        n += sprintf(s_sz + n, ",\"call\":{\"index\":%d,\"name\":\"%s\",\"results\":%u,\"args\":", nIndex, szCommand, dwResults);
        DbgJsonInts(s_sz, &n, anArgs, nArgs);
        n += sprintf(s_sz + n, "}");
    }
    strcpy(s_sz + n, "}");
    TrigLiveScriptsEvent(s_sz);
    DbgSendState();
    while (s_bPaused && g_nTrigLiveClients > 0)
    {
        DbgRunCommands();
        if (s_bPaused)
            Sleep(5);
    }
    InterlockedExchange(&s_bPaused, 0);
    TrigLiveScriptsEvent("{\"t\":\"resumed\"}");
    DbgSendState();
}

// Before each instruction while the hook is on (sub_68310's loop): the code pointer is
// dword_449320, the script dword_449328.
void TrigScriptStep()
{
    RwUInt32 dwObj = (RwUInt32)dword_449328, dwCode = (RwUInt32)dword_449320;
    RwInt32 i, nIndex;
    type_44350 *pRecord;

    // the last call's results, now that it has returned
    if (s_pPendingResult && s_pPendingResult->dwObj == dwObj)
    {
        s_pPendingResult->nResults = DbgStackTop(s_pPendingResult->anResults, 4, s_pPendingResult->nResults);
        s_pPendingResult->bResults = TRUE;
        s_pPendingResult = NULL;
    }
    if (dwObj == s_dwWatch && s_dwWatch)
    {
        if (s_nTrace < DBG_TRACE)
            s_adwTrace[s_nTrace++] = dwCode;
        else
            s_bTraceFull = TRUE;
    }
    if ((s_bCallsAll || (dwObj == s_dwWatch && s_dwWatch)) && (pRecord = DbgCallRecord(dword_449320, &nIndex)) != NULL)
    {
        if (s_nCalls < DBG_CALLS)
        {
            DbgCall *c = &s_aCalls[s_nCalls++];
            RwUInt32 dwArgs = 0, dwResults = 0;

            DbgRead(&pRecord->unk_0C, &dwArgs);
            DbgRead(&pRecord->unk_14, &dwResults);
            c->dwObj = dwObj;
            c->dwCode = dwCode;
            c->nIndex = nIndex;
            c->nArgs = DbgStackTop(c->anArgs, DBG_ARGS, (RwInt32)dwArgs);
            c->nResults = dwResults > 4 ? 4 : (RwInt32)dwResults;
            c->bResults = FALSE;
            s_pPendingResult = c->nResults ? c : NULL;
        }
        else
            s_nCallsDropped++;
    }
    if (s_bStepPending && (s_dwStepObj == 1 || s_dwStepObj == dwObj))
    {
        s_bStepPending = FALSE;
        DbgUpdateHook();
        DbgPause("step");
        return;
    }
    for (i = 0; i < s_nBreak; i++)
        if (s_aBreak[i].dwAddr == dwCode && (s_aBreak[i].dwObj == 0 || s_aBreak[i].dwObj == dwObj))
        {
            DbgPause("breakpoint");
            return;
        }
}

// The watched script, 0 for none (the scripts snapshot sends its variables in full).
RwUInt32 TrigScriptWatched()
{
    return s_dwWatch;
}

// The end of a script's run (TrigWebVmSnapshot): a call's results still pending are taken now.
void TrigScriptRunEnd()
{
    if (s_pPendingResult && s_pPendingResult->dwObj == (RwUInt32)dword_449328)
    {
        s_pPendingResult->nResults = DbgStackTop(s_pPendingResult->anResults, 4, s_pPendingResult->nResults);
        s_pPendingResult->bResults = TRUE;
        s_pPendingResult = NULL;
    }
}

// Once a game frame (TrigLiveTick): the queued commands, then the frame's trace and calls.
void TrigScriptDbgTick(RwBool bWatched)
{
    static RwChar s_sz[96 * 1024];
    RwInt32 n, i;

    DbgRunCommands();
    if (!bWatched)
    {
        // (no page watching the scripts: nothing kept)
        if (s_dwWatch || s_bCallsAll || s_nBreak)
        {
            s_dwWatch = 0;
            s_bCallsAll = FALSE;
            s_nBreak = 0;
            DbgUpdateHook();
        }
        s_nTrace = s_nCalls = 0;
        return;
    }
    if (s_nTrace)
    {
        n = sprintf(s_sz, "{\"t\":\"trace\",\"frame\":%u,\"obj\":\"%08X\",\"full\":%d,\"code\":[", port_frame, s_dwWatch,
                    (RwInt32)s_bTraceFull);
        for (i = 0; i < s_nTrace && n < (RwInt32)sizeof(s_sz) - 32; i++)
            n += sprintf(s_sz + n, "%s%u", i ? "," : "", s_adwTrace[i]);
        strcpy(s_sz + n, "]}");
        TrigLiveScriptsEvent(s_sz);
        s_nTrace = 0;
        s_bTraceFull = FALSE;
    }
    if (s_nCalls)
    {
        RwChar szName[64];

        s_pPendingResult = NULL;
        n = sprintf(s_sz, "{\"t\":\"calls\",\"frame\":%u,\"dropped\":%d,\"list\":[", port_frame, s_nCallsDropped);
        for (i = 0; i < s_nCalls && n < (RwInt32)sizeof(s_sz) - 600; i++)
        {
            DbgCall *c = &s_aCalls[i];

            TrigWebCommandName(c->nIndex, szName);
            n += sprintf(s_sz + n, "%s{\"obj\":\"%08X\",\"code\":\"%08X\",\"index\":%d,\"name\":\"%s\",\"args\":", i ? "," : "",
                         c->dwObj, c->dwCode, c->nIndex, szName);
            DbgJsonInts(s_sz, &n, c->anArgs, c->nArgs);
            if (c->bResults)
            {
                n += sprintf(s_sz + n, ",\"results\":");
                DbgJsonInts(s_sz, &n, c->anResults, c->nResults);
            }
            n += sprintf(s_sz + n, "}");
        }
        strcpy(s_sz + n, "]}");
        TrigLiveScriptsEvent(s_sz);
        s_nCalls = 0;
        s_nCallsDropped = 0;
    }
}

#endif // CODFH_DRAW_TRIGGERS
