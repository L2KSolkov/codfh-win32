/*
 * The crash report's game and RenderWare pages (crash.cpp shows them): what the game was doing,
 * read from its globals, and RenderWare's free lists and textures. Every read is guarded (a
 * crash can leave anything broken) and written into the caller's buffer only, nothing allocated.
 *
 * The game: the level (sub_19B050's index, sub_19B060's name; while a level change runs the
 * index already holds the next one), whether a level is up (dword_4E5C74, the world manager's
 * camera) and running (dword_4B8710), the game loop's flags (dword_4B86F8: unit_0D6640's
 * sub_D7410 and unit_0D7F20's sub_D8xxx set them), the checkpoint register (dword_4B8780,
 * SetCheckPointRegister) and the restarts (dword_4B8720, GetNumberOfRestarts), the section slots
 * (dword_4E5D30), the loading queue (types/asynchload.h's, declared here as the debug tools do:
 * that header brings the kernel's in against xtl.h) and the local player (sub_1745A0(0)): its
 * frame's position and its health.
 *
 * RenderWare: src/rw/src/plcore/bamemory.c's _rwFreeListStats and src/rw/src/batextur.c's
 * _rwTexDictionaryStats (the port's, CODFH_WIN32), read without RenderWare's locks.
 */
#include <xtl.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "rw/bamatrix.h"
#include "rw/baframe.h"
#include "types/type_10F710.h"
#include "types/type_4E5D30.h"
#include "game/functions.h"
#include "game/worldmgr.h"
#include "game/data.h"
#include "game/savestate.h"
#include "game/sectionslots.h"

struct type_44BAD8
{
    RwChar unk_00[0x40];
    RwInt32 unk_40;
    RwInt32 unk_44;
    RwInt32 unk_48;
};
extern type_44BAD8 dword_44BAD8[16];
extern type_44BAD8 *dword_44BFF8;
extern type_44BAD8 *dword_44BFFC;
extern RwInt32 dword_44C004;
extern RwInt16 word_429EAC;
extern type_4E5D30 dword_4E5D30[SECTION_SLOTS];

extern "C" RwInt32 _rwFreeListStats(RwUInt32 *out, RwInt32 max);
extern "C" RwInt32 _rwTexDictionaryStats(RwInt32 *pnTextures, RwUInt32 *pnBytes);

static char *s_pOut;
static size_t s_nOut, s_nAt;

static void out(const char *fmt, ...)
{
    va_list a;
    int n;

    if (s_nAt + 1 >= s_nOut)
        return;
    va_start(a, fmt);
    n = _vsnprintf(s_pOut + s_nAt, s_nOut - 1 - s_nAt, fmt, a);
    va_end(a);
    s_nAt = n < 0 ? s_nOut - 1 : s_nAt + n;
    s_pOut[s_nAt] = 0;
}

static void begin(char *buf, size_t n)
{
    s_pOut = buf;
    s_nOut = n;
    s_nAt = 0;
    buf[0] = 0;
}

// ---- the game ----

static void level_part()
{
    __try
    {
        RwInt32 nLevel = sub_19B050();
#ifdef CODFH_SP
        const RwInt32 nNames = 40;
#else
        const RwInt32 nNames = 10;
#endif
        const RwChar *pszName = nLevel >= 0 && nLevel < nNames ? sub_19B060(nLevel) : NULL;

        out("Level %d %s%s\r\n", nLevel, pszName ? pszName : "(none)",
            (dword_4B86F8 & 0x80) ? " (the next: a level change is running)" : "");
        out("  world up (a level loaded): %s; level running: %s\r\n", dword_4E5C74 ? "yes" : "no",
            dword_4B8710 ? "yes" : "no");
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        out("Level: not readable\r\n");
    }
}

static void loop_part()
{
    static const char *const bits[8] = {
        "game loop running", "full reload asked", "leaving the game loop (quit, end of game)",
        "restart (death or RestartLevel)", "paused", "next level's load pending (shutdown and init next)",
        "quit fade-out", "level change started (fading out)",
    };

    __try
    {
        RwUInt32 f = dword_4B86F8;
        int i, any = 0;

        out("Game loop flags %08lX:", (unsigned long)f);
        for (i = 0; i < 8; i++)
            if (f & (1u << i))
                out("%s %s", any++ ? "," : "", bits[i]);
        out("%s\r\n", any ? "" : " none");
        out("Checkpoint register %d, restarts %d\r\n", dword_4B8780, dword_4B8720);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        out("Game loop: not readable\r\n");
    }
}

static void section_part()
{
    int i, used = 0;

    out("\r\nSection slots (%d)\r\n", SECTION_SLOTS);
    for (i = 0; i < SECTION_SLOTS; i++)
    {
        __try
        {
            RwInt32 live = dword_4E5D30[i].get_unk_00(), loading = dword_4E5D30[i].unk_04;
            RwUInt32 section = dword_4E5D30[i].unk_08;

            if (live || loading)
            {
                out("  slot %2d: section %u, %s\r\n", i, (unsigned)(section & 0xFFFF), live ? "loaded" : "loading");
                used++;
            }
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            out("  slot %2d: not readable\r\n", i);
        }
    }
    if (!used)
        out("  none in use\r\n");
}

static void queue_part()
{
    static const char *const kinds[4] = {"section", "sound bank", "anim group", "clump bank"};

    __try
    {
        type_44BAD8 *head = dword_44BFF8, *tail = dword_44BFFC;
        int pending = 0;

        out("\r\nLoading queue: %s", dword_44C004 ? "running" : "stopped");
        out(", section loading: %d\r\n", (int)word_429EAC);
        if (head && tail)
        {
            for (type_44BAD8 *p = head; p != tail && pending < 16;)
            {
                RwInt32 k = p->unk_40;

                out("  %s %s (id %d)%s\r\n", k >= 0 && k < 4 ? kinds[k] : "?", p->unk_00, p->unk_44,
                    p == head ? " (the loader's)" : "");
                pending++;
                p++;
                if (p >= dword_44BAD8 + 16)
                    p = dword_44BAD8;
            }
        }
        if (!pending)
            out("  nothing queued\r\n");
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        out("  not readable\r\n");
    }
}

static void player_part()
{
    out("\r\nPlayer\r\n");
    __try
    {
        type_10F710 *pPlayer = (type_10F710 *)sub_1745A0(0);
        RwFrame *pFrame;

        if (!pPlayer)
        {
            out("  none (between levels)\r\n");
            return;
        }
        pFrame = pPlayer->unk_338.unk_08;
        if (pFrame)
        {
            RwV3d *p = &RwFrameGetMatrix(pFrame)->pos;
            out("  position %.1f, %.1f, %.1f\r\n", p->x, p->y, p->z);
        }
        out("  health %.0f%% (%.0f of %d)\r\n", pPlayer->unk_19DC * 100.0f, pPlayer->unk_19DC * pPlayer->unk_19E0,
            pPlayer->unk_19E0);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        out("  not readable\r\n");
    }
}

extern "C" void port_crash_game_state(char *buf, size_t n)
{
    begin(buf, n);
    level_part();
    loop_part();
    section_part();
    queue_part();
    player_part();
}

// ---- RenderWare ----

static RwUInt32 s_aFreeLists[512 * 4];

extern "C" void port_crash_rw_stats(char *buf, size_t n)
{
    RwInt32 nLists = 0, nDicts = 0, nTextures = 0, i, j;
    RwUInt32 nTexBytes = 0;
    double total = 0;

    begin(buf, n);
    __try
    {
        nLists = _rwFreeListStats(s_aFreeLists, 512);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        out("RenderWare free lists: not readable\r\n");
        nLists = -1;
    }
    if (nLists >= 0)
    {
        // (largest first, by their blocks' entries)
        for (i = 0; i < nLists; i++)
            for (j = i + 1; j < nLists; j++)
            {
                double a = (double)s_aFreeLists[i * 4] * s_aFreeLists[i * 4 + 1] * s_aFreeLists[i * 4 + 2];
                double b = (double)s_aFreeLists[j * 4] * s_aFreeLists[j * 4 + 1] * s_aFreeLists[j * 4 + 2];

                if (b > a)
                    for (int k = 0; k < 4; k++)
                    {
                        RwUInt32 t = s_aFreeLists[i * 4 + k];
                        s_aFreeLists[i * 4 + k] = s_aFreeLists[j * 4 + k];
                        s_aFreeLists[j * 4 + k] = t;
                    }
            }
        for (i = 0; i < nLists; i++)
            total += (double)s_aFreeLists[i * 4] * s_aFreeLists[i * 4 + 1] * s_aFreeLists[i * 4 + 2];
        out("RenderWare free lists: %d, %.1f MB in their blocks\r\n", nLists, total / (1024.0 * 1024.0));
        out("  entry size  per block  blocks    in use / room     KB\r\n");
        for (i = 0; i < nLists && i < 10; i++)
        {
            RwUInt32 *f = &s_aFreeLists[i * 4];

            out("  %10lu %10lu %7lu %8lu / %-8lu %7.0f\r\n", (unsigned long)f[0], (unsigned long)f[1],
                (unsigned long)f[2], (unsigned long)f[3], (unsigned long)(f[1] * f[2]),
                (double)f[0] * f[1] * f[2] / 1024.0);
        }
        if (nLists > 10)
            out("  (%d smaller ones)\r\n", nLists - 10);
    }
    __try
    {
        nDicts = _rwTexDictionaryStats(&nTextures, &nTexBytes);
        out("RenderWare textures: %d dictionaries, %d textures, %.1f MB of rasters\r\n", nDicts, nTextures,
            nTexBytes / (1024.0 * 1024.0));
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        out("RenderWare textures: not readable (the dictionary list is broken)\r\n");
    }
}
