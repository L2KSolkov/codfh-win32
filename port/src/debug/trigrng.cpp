// The debug tools' random numbers and frame timing (for speedrunning: what makes a run repeat
// and what depends on the frame rate). trigtools.cpp's Speedrun views show and set them.
//
// The game has two generators, neither ever seeded by the game itself:
//  - RenderWare's RpRandom (src/rw/plugin/random/rprandom.c, the 31-word additive generator),
//    seeded once with 0x9A319039 when the engine opens: particles, decals, AI choices, most of
//    the game's randomness (frand, frand_range, game/frand.h);
//  - the C library's rand() (crand, and a few direct calls: mounted weapons' spread, gibs),
//    from its default seed of 1.
// So a run's random numbers depend only on how many were drawn before: anything drawn per
// frame makes the frame rate change what comes out.
//
// rand() and srand() are defined here (the debug tools' build only), the C library's own
// algorithm and per-thread state, so its calls can be counted; RpRandom tells us of each call
// (PortRngNote). Nothing is recorded until the view turns recording on.

#ifdef CODFH_DRAW_TRIGGERS

#include <xtl.h>
#include <intrin.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <dbghelp.h>
#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "rw/bamatrix.h"
#include "rw/baframe.h"
#include "rw/rprandom.h"
#include "game/data.h"
#include "game/functions.h"
#include "game/gameloop.h"
#include "types/type_3D3548.h"
#include "trigsndproj.h"

extern "C" volatile unsigned port_frame;
extern "C" void plog(const char *fmt, ...);
extern "C" int port_get_max_fps(void);
extern "C" RwUInt32 _rpRandomStateHash(void);
// (types/soundbank.h's: the frame's time before the cap)
extern RwReal flt_429288;

RwBool g_bTrigRngRecord = FALSE;
RwBool g_bTrigFrameSample = FALSE;
RwBool g_bTrigRngSeedOnRestart = FALSE;
RwUInt32 g_dwTrigRngSeed = 12345;
RwUInt32 g_anTrigRngTotal[2];
RwUInt32 g_anTrigRngLastFrame[2];
RwReal g_afTrigRngPerSecond[2];
RwUInt32 g_anTrigRngSinceRestart[2];
RwInt32 g_nTrigRngRestarts;
TrigRngCaller g_aTrigRngCallers[TRIGRNG_CALLERS];
RwInt32 g_nTrigRngCallers;
TrigRngCall g_aTrigRngLog[TRIGRNG_LOG];
RwInt32 g_nTrigRngLogNext;
RwUInt32 g_nTrigRngLogTotal;

TrigFrameSample g_aTrigFrameSamples[TRIGFRAME_SAMPLES];
RwInt32 g_nTrigFrameNext;
RwInt32 g_nTrigFrameCount;
RwReal g_fTrigFrameGameOverReal = 1.0f;
RwReal g_fTrigFrameFps;
RwInt32 g_nTrigFrameCapped;
TrigFrameNote g_aTrigFrameNotes[TRIGFRAME_NOTES];
RwInt32 g_nTrigFrameNotes;

// ---- rand() and srand(): the C library's (ucrt's rand.cpp), counted ----

static __declspec(thread) RwUInt32 t_dwRandState = 1;

extern "C" void __cdecl srand(unsigned int seed)
{
    t_dwRandState = seed;
}

extern "C" int __cdecl rand(void)
{
    RwInt32 n;

    t_dwRandState = t_dwRandState * 214013 + 2531011;
    n = (RwInt32)((t_dwRandState >> 16) & 0x7FFF);
    if (g_bTrigRngRecord)
        PortRngNote(1, _ReturnAddress(), (RwUInt32)n);
    return n;
}

// The calling thread's rand() state (the game thread's, from the view).
RwUInt32 TrigRngRandState()
{
    return t_dwRandState;
}

// ---- the record ----

// One call of generator nGen (0 RpRandom, 1 rand) from pCaller, returning dwValue.
extern "C" void PortRngNote(RwInt32 nGen, const void *pCaller, RwUInt32 dwValue)
{
    TrigRngCall *c;
    RwInt32 i;

    if (!g_bTrigRngRecord)
        return;
    nGen &= 1;
    g_anTrigRngTotal[nGen]++;
    g_anTrigRngSinceRestart[nGen]++;
    c = &g_aTrigRngLog[g_nTrigRngLogNext];
    g_nTrigRngLogNext = (g_nTrigRngLogNext + 1) % TRIGRNG_LOG;
    g_nTrigRngLogTotal++;
    c->nGen = nGen;
    c->pAddr = pCaller;
    c->dwValue = dwValue;
    c->dwFrame = port_frame;
    for (i = 0; i < g_nTrigRngCallers; i++)
        if (g_aTrigRngCallers[i].pAddr == pCaller && g_aTrigRngCallers[i].nGen == nGen)
        {
            g_aTrigRngCallers[i].nCount++;
            g_aTrigRngCallers[i].nThisFrame++;
            return;
        }
    if (g_nTrigRngCallers < TRIGRNG_CALLERS)
    {
        TrigRngCaller *p = &g_aTrigRngCallers[g_nTrigRngCallers++];

        memset(p, 0, sizeof(*p));
        p->pAddr = pCaller;
        p->nGen = nGen;
        p->nCount = 1;
        p->nThisFrame = 1;
    }
}

void TrigRngReset()
{
    memset(g_anTrigRngTotal, 0, sizeof(g_anTrigRngTotal));
    memset(g_anTrigRngSinceRestart, 0, sizeof(g_anTrigRngSinceRestart));
    memset(g_aTrigRngLog, 0, sizeof(g_aTrigRngLog));
    g_nTrigRngLogNext = 0;
    g_nTrigRngLogTotal = 0;
    g_nTrigRngCallers = 0;
}

// Both generators from dwSeed: RpRandom as RenderWare seeds it, rand() for the calling thread
// (the game's).
void TrigRngSeedNow(RwUInt32 dwSeed)
{
    RwBool bRecord = g_bTrigRngRecord;

    // (RpRandomSeed draws 310 numbers to stir its table: not the game's)
    g_bTrigRngRecord = FALSE;
    RpRandomSeed(dwSeed);
    srand(dwSeed);
    g_bTrigRngRecord = bRecord;
    memset(g_anTrigRngSinceRestart, 0, sizeof(g_anTrigRngSinceRestart));
}

// From the restart's tick reset (sub_D9610: a level's start, a checkpoint's, a death's).
void TrigRngOnRestart()
{
    g_nTrigRngRestarts++;
    memset(g_anTrigRngSinceRestart, 0, sizeof(g_anTrigRngSinceRestart));
    if (g_bTrigRngSeedOnRestart)
        TrigRngSeedNow(g_dwTrigRngSeed);
}

// A fingerprint of a generator's state: equal fingerprints, equal numbers to come.
RwUInt32 TrigRngStateHash(RwInt32 nGen)
{
    return nGen == 0 ? _rpRandomStateHash() : TrigRngRandState();
}

// A caller's function and offset (the port's symbols: sub_XXXXX names give the image's
// address), looked up once.
const RwChar *TrigRngCallerName(TrigRngCaller *p)
{
    static RwBool s_bSym;

    if (!p->bNamed)
    {
        RwChar buf[sizeof(SYMBOL_INFO) + 128];
        SYMBOL_INFO *sym = (SYMBOL_INFO *)buf;
        DWORD64 disp = 0;

        if (!s_bSym)
        {
            // (the profiler and the crash handler may have set DbgHelp up already: then
            // this fails, and the lookups work all the same)
            SymSetOptions(SYMOPT_DEFERRED_LOADS | SYMOPT_UNDNAME);
            SymInitialize(GetCurrentProcess(), NULL, TRUE);
            s_bSym = TRUE;
        }
        memset(buf, 0, sizeof(buf));
        sym->SizeOfStruct = sizeof(SYMBOL_INFO);
        sym->MaxNameLen = 127;
        if (SymFromAddr(GetCurrentProcess(), (DWORD64)(size_t)p->pAddr, &disp, sym))
            _snprintf(p->szName, sizeof(p->szName), "%s+0x%X", sym->Name, (RwUInt32)disp);
        else
            _snprintf(p->szName, sizeof(p->szName), "%p", p->pAddr);
        p->szName[sizeof(p->szName) - 1] = 0;
        p->bNamed = TRUE;
    }
    return p->szName;
}

// ---- the frame timing ----

static RwBool PlayerPos(RwV3d *pv)
{
    __try
    {
        type_3D3548 *pPlayer = sub_1745A0(0);
        RwFrame *pFrame;

        if (pPlayer == NULL)
            return FALSE;
        pFrame = pPlayer->unk_338.unk_08;
        if (pFrame == NULL)
            return FALSE;
        *pv = RwFrameGetMatrix(pFrame)->pos;
        return TRUE;
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        return FALSE;
    }
}

// Each main-loop pass (TrigWebTick): the frame's game time (deltaTime, 60ths of a second,
// capped at 5; flt_429288 before the cap), its real time, the player's speed by each, and the
// random numbers drawn in it.
void TrigRngFrame()
{
    static LARGE_INTEGER s_freq, s_last;
    static RwUInt32 s_anPrev[2];
    static RwV3d s_vPrev;
    static RwBool s_bPrev;
    static RwReal s_fSecs, s_fGameSecs;
    static RwUInt32 s_anSecond[2];
    LARGE_INTEGER now;
    TrigFrameSample *f;
    RwReal fReal, fGame;
    RwV3d v;
    RwInt32 i, k;

    RwUInt32 anFrame[2];
    static RwInt32 s_nStart = -1;
    static RwUInt32 s_dwSummaryFrame;

    // (CODFH_RNG=1: record from the start, and log a summary of the callers once, 20 seconds
    // in; CODFH_FRAMES=1: sample the frames from the start)
    if (s_nStart < 0)
    {
        s_nStart = 0;
        if (GetEnvironmentVariableA("CODFH_RNG", NULL, 0))
        {
            g_bTrigRngRecord = TRUE;
            s_dwSummaryFrame = port_frame + 1200;
        }
        if (GetEnvironmentVariableA("CODFH_FRAMES", NULL, 0))
            g_bTrigFrameSample = TRUE;
    }
    if (s_dwSummaryFrame && port_frame >= s_dwSummaryFrame)
    {
        RwInt32 nTop;

        s_dwSummaryFrame = 0;
        plog("rng: %u RpRandom and %u rand() calls so far (%.0f and %.0f a second); %d callers; the most:",
             g_anTrigRngTotal[0], g_anTrigRngTotal[1], g_afTrigRngPerSecond[0], g_afTrigRngPerSecond[1],
             g_nTrigRngCallers);
        for (nTop = 0; nTop < 12; nTop++)
        {
            TrigRngCaller *pBest = NULL;

            for (i = 0; i < g_nTrigRngCallers; i++)
                if (!g_aTrigRngCallers[i].bLogged && (pBest == NULL || g_aTrigRngCallers[i].nCount > pBest->nCount))
                    pBest = &g_aTrigRngCallers[i];
            if (pBest == NULL)
                break;
            pBest->bLogged = TRUE;
            plog("rng:   %8u %s %s (last frame %u)", pBest->nCount, pBest->nGen ? "rand()  " : "RpRandom",
                 TrigRngCallerName(pBest), pBest->nLastFrame);
        }
    }
    for (k = 0; k < 2; k++)
    {
        anFrame[k] = g_anTrigRngTotal[k] - s_anPrev[k];
        s_anPrev[k] = g_anTrigRngTotal[k];
        g_anTrigRngLastFrame[k] = anFrame[k];
        s_anSecond[k] += anFrame[k];
    }
    for (i = 0; i < g_nTrigRngCallers; i++)
    {
        g_aTrigRngCallers[i].nLastFrame = g_aTrigRngCallers[i].nThisFrame;
        g_aTrigRngCallers[i].nThisFrame = 0;
    }
    if (!s_freq.QuadPart)
    {
        QueryPerformanceFrequency(&s_freq);
        QueryPerformanceCounter(&s_last);
        return;
    }
    QueryPerformanceCounter(&now);
    fReal = (RwReal)((RwDouble)(now.QuadPart - s_last.QuadPart) / (RwDouble)s_freq.QuadPart);
    s_last = now;
    if (!g_bTrigFrameSample)
    {
        s_bPrev = FALSE;
        g_nTrigFrameCount = 0;
        return;
    }
    if (fReal <= 0.0f || fReal > 1.0f)
    {
        s_bPrev = FALSE;
        return;
    }
    fGame = deltaTime / 60.0f;
    f = &g_aTrigFrameSamples[g_nTrigFrameNext];
    g_nTrigFrameNext = (g_nTrigFrameNext + 1) % TRIGFRAME_SAMPLES;
    if (g_nTrigFrameCount < TRIGFRAME_SAMPLES)
        g_nTrigFrameCount++;
    memset(f, 0, sizeof(*f));
    f->fDelta = deltaTime;
    f->fRaw = flt_429288;
    f->fRealMs = fReal * 1000.0f;
    if (PlayerPos(&v))
    {
        if (s_bPrev)
        {
            RwReal dx = v.x - s_vPrev.x, dz = v.z - s_vPrev.z;
            RwReal d = (RwReal)sqrt(dx * dx + dz * dz);

            // (a teleport, a restart: not movement)
            if (d < 2000.0f)
            {
                f->fSpeedReal = d / fReal;
                f->fSpeedGame = fGame > 0.0f ? d / fGame : 0.0f;
            }
        }
        s_vPrev = v;
        s_bPrev = TRUE;
    }
    else
        s_bPrev = FALSE;
    f->anRng[0] = anFrame[0];
    f->anRng[1] = anFrame[1];
    // (once a second: the rates, the game time against the real, the fps, the capped frames)
    s_fSecs += fReal;
    s_fGameSecs += fGame;
    if (s_fSecs >= 1.0f)
    {
        g_fTrigFrameGameOverReal = s_fGameSecs / s_fSecs;
        for (k = 0; k < 2; k++)
        {
            g_afTrigRngPerSecond[k] = s_anSecond[k] / s_fSecs;
            s_anSecond[k] = 0;
        }
        s_fSecs = 0.0f;
        s_fGameSecs = 0.0f;
    }
    {
        RwReal fMs = 0.0f;
        RwInt32 nCapped = 0;

        for (i = 0; i < g_nTrigFrameCount; i++)
        {
            fMs += g_aTrigFrameSamples[i].fRealMs;
            if (g_aTrigFrameSamples[i].fRaw > 5.0f)
                nCapped++;
        }
        g_fTrigFrameFps = fMs > 0.0f ? g_nTrigFrameCount * 1000.0f / fMs : 0.0f;
        g_nTrigFrameCapped = nCapped;
    }
}

// Notes the last samples' averages under the current frame cap, for the comparison table.
void TrigFrameNoteNow()
{
    TrigFrameNote *n;
    RwReal fReal = 0.0f, fGame = 0.0f, fSpeedG = 0.0f, fSpeedR = 0.0f;
    RwUInt32 anRng[2] = { 0, 0 };
    RwInt32 i, nMoving = 0;

    if (g_nTrigFrameCount == 0)
        return;
    if (g_nTrigFrameNotes >= TRIGFRAME_NOTES)
    {
        memmove(&g_aTrigFrameNotes[0], &g_aTrigFrameNotes[1], sizeof(g_aTrigFrameNotes[0]) * (TRIGFRAME_NOTES - 1));
        g_nTrigFrameNotes--;
    }
    for (i = 0; i < g_nTrigFrameCount; i++)
    {
        const TrigFrameSample *f = &g_aTrigFrameSamples[i];

        fReal += f->fRealMs / 1000.0f;
        fGame += f->fDelta / 60.0f;
        anRng[0] += f->anRng[0];
        anRng[1] += f->anRng[1];
        if (f->fSpeedGame > 1.0f)
        {
            fSpeedG += f->fSpeedGame;
            fSpeedR += f->fSpeedReal;
            nMoving++;
        }
    }
    n = &g_aTrigFrameNotes[g_nTrigFrameNotes++];
    memset(n, 0, sizeof(*n));
    n->nMaxFps = port_get_max_fps();
    n->fFps = fReal > 0.0f ? g_nTrigFrameCount / fReal : 0.0f;
    n->fGameOverReal = fReal > 0.0f ? fGame / fReal : 0.0f;
    n->fSpeedGame = nMoving ? fSpeedG / nMoving : 0.0f;
    n->fSpeedReal = nMoving ? fSpeedR / nMoving : 0.0f;
    n->afRngPerGameSecond[0] = fGame > 0.0f ? anRng[0] / fGame : 0.0f;
    n->afRngPerGameSecond[1] = fGame > 0.0f ? anRng[1] / fGame : 0.0f;
    n->nCapped = g_nTrigFrameCapped;
}

#endif
