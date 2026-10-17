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
#include "rw/baraster.h"
#include "rw/batextur.h"
#include "rw/baengine.h"
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

extern "C" RwInt32 _rwFreeListStats(RwUInt32 *out, RwInt32 max);
extern "C" void _rwResourcesStats(RwInt32 *maxSize, RwInt32 *currentSize, RwInt32 *reusageSize);
typedef void (*_rwTextureVisit)(const RwChar *name, const RwRaster *raster, RwUInt32 bytes, RwInt32 dxt,
                                RwInt32 dict, void *data);
extern "C" RwInt32 _rwTexDictionaryWalk(_rwTextureVisit cb, void *data, RwTexDictionary **current);
extern "C" void _rwWorldStats(const RpWorld *world, RwInt32 *out);
extern "C" RwInt32 _rt2dFontNames(const RwChar **names, RwInt32 max);
extern "C" void _rwXbMemoryStats(RwUInt32 *out);
extern "C" RwUInt32 RwEngineGetVersion(void);
// (crash.cpp: a code address's function, from the symbols)
extern "C" void port_crash_symbol(const void *addr, char *out, size_t n);

static double kb(double n)
{
    return n / 1024.0;
}

static void engine_part()
{
    __try
    {
        RwUInt32 v = RwEngineGetVersion();
        RwVideoMode vm;
        RwInt32 mode = RwEngineGetCurrentVideoMode();

        out("RenderWare %lu.%lu.%lu.%lu", (unsigned long)((v >> 16) & 0xF), (unsigned long)((v >> 12) & 0xF),
            (unsigned long)((v >> 8) & 0xF), (unsigned long)(v & 0xFF));
        if (mode >= 0 && RwEngineGetVideoModeInfo(&vm, mode))
            out(", video mode %d: %dx%d, %d bits, %d Hz", mode, vm.width, vm.height, vm.depth, vm.refRate);
        out("\r\n");
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        out("RenderWare: the engine not readable\r\n");
    }
    __try
    {
        RwInt32 maxSize = 0, cur = 0, reuse = 0;

        _rwResourcesStats(&maxSize, &cur, &reuse);
        out("Resources arena: %.0f KB of %.0f KB in use, %.0f KB kept for reuse\r\n", kb(cur), kb(maxSize), kb(reuse));
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        out("Resources arena: not readable\r\n");
    }
}

static RwUInt32 s_aFreeLists[512 * 5];

static void freelist_part()
{
    RwInt32 nLists = -1, i, j;
    double total = 0;

    __try
    {
        nLists = _rwFreeListStats(s_aFreeLists, 512);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        out("\r\nFree lists: not readable\r\n");
        return;
    }
    // (largest first, by their blocks' entries)
    for (i = 0; i < nLists; i++)
        for (j = i + 1; j < nLists; j++)
        {
            double x = (double)s_aFreeLists[i * 5] * s_aFreeLists[i * 5 + 1] * s_aFreeLists[i * 5 + 2];
            double y = (double)s_aFreeLists[j * 5] * s_aFreeLists[j * 5 + 1] * s_aFreeLists[j * 5 + 2];

            if (y > x)
                for (int k = 0; k < 5; k++)
                {
                    RwUInt32 t = s_aFreeLists[i * 5 + k];
                    s_aFreeLists[i * 5 + k] = s_aFreeLists[j * 5 + k];
                    s_aFreeLists[j * 5 + k] = t;
                }
        }
    for (i = 0; i < nLists; i++)
        total += (double)s_aFreeLists[i * 5] * s_aFreeLists[i * 5 + 1] * s_aFreeLists[i * 5 + 2];
    out("\r\nFree lists: %d, %.1f MB in their blocks\r\n", nLists, total / (1024.0 * 1024.0));
    out("  %-34s %6s %13s %8s\r\n", "made by", "entry", "in use / room", "KB");
    for (i = 0; i < nLists; i++)
    {
        RwUInt32 *f = &s_aFreeLists[i * 5];
        char who[96] = "(not recorded)";

        if (!f[2])
            continue;   // (no block: nothing in it)
        if (f[4])
            port_crash_symbol((const void *)(ULONG_PTR)f[4], who, sizeof(who));
        out("  %-34.34s %6lu %6lu / %-6lu %8.0f\r\n", who, (unsigned long)f[0], (unsigned long)f[3],
            (unsigned long)(f[1] * f[2]), (double)f[0] * f[1] * f[2] / 1024.0);
    }
}

// The textures: by format, and the largest.
struct TexStats
{
    RwInt32 count, rasters;
    double byFormat[12];
    RwInt32 countByFormat[12];
    struct { char name[32]; RwInt32 w, h, fmt, dict; RwUInt32 bytes; } top[12];
    RwInt32 ntop;
};
static TexStats s_tex;
static const char *const s_apszFormat[12] = {"DXT1", "DXT2/3", "DXT4/5", "8888", "888", "565", "1555", "4444",
                                             "555", "LUM8", "palettised", "other"};

static int format_of(const RwRaster *r, RwInt32 dxt)
{
    if (dxt == 0x0C)
        return 0;
    if (dxt == 0x0E)
        return 1;
    if (dxt == 0x0F)
        return 2;
    if (r->cFormat & 0x60)
        return 10;
    switch (r->cFormat & 0x0F)
    {
    case 5: return 3;
    case 6: return 4;
    case 2: return 5;
    case 1: return 6;
    case 3: return 7;
    case 0xA: return 8;
    case 4: return 9;
    }
    return 11;
}

static void tex_visit(const RwChar *name, const RwRaster *raster, RwUInt32 bytes, RwInt32 dxt, RwInt32 dict, void *)
{
    int fmt, i;

    s_tex.count++;
    if (!raster)
        return;
    s_tex.rasters++;
    fmt = format_of(raster, dxt);
    s_tex.byFormat[fmt] += bytes;
    s_tex.countByFormat[fmt]++;
    // (the twelve largest, kept in order)
    for (i = s_tex.ntop; i > 0 && s_tex.top[i - 1].bytes < bytes; i--)
        if (i < 12)
            s_tex.top[i] = s_tex.top[i - 1];
    if (i < 12)
    {
        strncpy(s_tex.top[i].name, name, 31);
        s_tex.top[i].name[31] = 0;
        s_tex.top[i].w = raster->width;
        s_tex.top[i].h = raster->height;
        s_tex.top[i].fmt = fmt;
        s_tex.top[i].dict = dict;
        s_tex.top[i].bytes = bytes;
        if (s_tex.ntop < 12)
            s_tex.ntop++;
    }
}

static void texture_part()
{
    RwInt32 nDicts = -1, i;
    RwTexDictionary *current = NULL;
    double total = 0;

    memset(&s_tex, 0, sizeof(s_tex));
    __try
    {
        nDicts = _rwTexDictionaryWalk(tex_visit, NULL, &current);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        out("\r\nTextures: the dictionary list is broken (read as far as it went)\r\n");
    }
    for (i = 0; i < 12; i++)
        total += s_tex.byFormat[i];
    out("\r\nTextures: %d in %d dictionaries (the current %p), %.1f MB of rasters\r\n", s_tex.count, nDicts < 0 ? 0 : nDicts,
        current, total / (1024.0 * 1024.0));
    for (i = 0; i < 12; i++)
        if (s_tex.countByFormat[i])
            out("  %-10s %5d textures %8.0f KB\r\n", s_apszFormat[i], s_tex.countByFormat[i], kb(s_tex.byFormat[i]));
    out("  the largest:\r\n");
    for (i = 0; i < s_tex.ntop; i++)
        out("    %-31s %4dx%-4d %-10s %6.0f KB  (dictionary %d)\r\n", s_tex.top[i].name, s_tex.top[i].w, s_tex.top[i].h,
            s_apszFormat[s_tex.top[i].fmt], kb(s_tex.top[i].bytes), s_tex.top[i].dict);
}

static void world_part()
{
    int i, any = 0;

    out("\r\nWorlds (the section slots')\r\n");
    for (i = 0; i < SECTION_SLOTS; i++)
    {
        __try
        {
            RpWorld *world = dword_4E5D30[i].unk_20;
            RwInt32 c[7];

            if (!dword_4E5D30[i].get_unk_00() || !world)
                continue;
            _rwWorldStats(world, c);
            out("  slot %2d, section %u: %d sectors, %d clumps (%d atomics), %d+%d lights, %d triangles\r\n", i,
                (unsigned)(dword_4E5D30[i].unk_08 & 0xFFFF), c[0], c[1], c[2], c[3], c[4], c[5]);
            any++;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            out("  slot %2d: not readable\r\n", i);
        }
    }
    if (!any)
        out("  none loaded\r\n");
}

static void font_part()
{
    const RwChar *names[24];
    RwInt32 n = 0, i;

    __try
    {
        n = _rt2dFontNames(names, 24);
        out("\r\nFonts (Rt2d): %d", n);
        for (i = 0; i < n && i < 24; i++)
            out("%s %s", i ? "," : "", names[i] ? names[i] : "?");
        out("\r\n");
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        out("\r\nFonts: not readable\r\n");
    }
}

static void driver_part()
{
    __try
    {
        RwUInt32 m[6];

        _rwXbMemoryStats(m);
        out("\r\nXbox driver memory: %lu blocks, %.1f MB; free %lu entries, %.1f MB; %lu dynamic vertex buffers, %.0f KB\r\n",
            (unsigned long)m[0], m[1] / (1024.0 * 1024.0), (unsigned long)m[2], m[3] / (1024.0 * 1024.0),
            (unsigned long)m[4], kb(m[5]));
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        out("\r\nXbox driver memory: not readable\r\n");
    }
}

extern "C" void port_crash_rw_stats(char *buf, size_t n)
{
    begin(buf, n);
    engine_part();
    freelist_part();
    texture_part();
    world_part();
    font_part();
    driver_part();
}
