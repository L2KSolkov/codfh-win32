/*
 * codfh-match: RenderWare Audio's memory functions (rwamemory.h in the
 * library's PS2 header, docs/reference/rwacore_ps2.h): allocation through
 * the RenderWare engine's memory interface (ourGlobals.memoryFuncs: malloc, free,
 * realloc and calloc slots, each taking a memory hint), aligned blocks,
 * the C library defaults and the interface's set-up.
 */
#include "rwa.h"
#include "rwaint.h"


extern void *malloc(RwUInt32 size);
extern void free(void *mem);
extern void *realloc(void *mem, RwUInt32 size);
extern void *memset(void *dst, RwInt32 value, RwUInt32 size);

// match: _sub_242170 @ 0x00242170
// sp-match: _sub_242170 @ 0x00159050
void *
sub_242170(RwUInt32 size, RwUInt32 hint)
{
    return ourGlobals.memoryFuncs.rwmalloc(size, hint);
}

// match: _sub_242180 @ 0x00242180
// sp-match: _sub_242180 @ 0x00159060
void *
sub_242180(RwUInt32 size, RwUInt32 hint)
{
    RwUInt32    block = (RwUInt32)sub_242170(size + 8, hint);

    if (block > 0)
    {
        RwUInt32   *aligned = (RwUInt32 *)((block + 8) / 8 * 8);

        aligned[-1] = block;

        return aligned;
    }

    return NULL;
}

// match: _sub_2421B0 @ 0x002421B0
// sp-match: _sub_2421B0 @ 0x00159090
void
sub_2421B0(void *mem)
{
    ourGlobals.memoryFuncs.rwfree(mem);
}

// match: _sub_2421C0 @ 0x002421C0
// sp-match: _sub_2421C0 @ 0x001590A0
void *
sub_2421C0(RwUInt32 count, RwUInt32 size, RwUInt32 hint)
{
    return ourGlobals.memoryFuncs.rwcalloc(count, size, hint);
}

// match: _sub_2421D0 @ 0x002421D0
// sp-match: _sub_2421D0 @ 0x001590B0
void *
sub_2421D0(RwUInt32 size, RwUInt32 hint)
{
    return malloc(size);
}

// match: _sub_2421E0 @ 0x002421E0
// sp-match: _sub_2421E0 @ 0x001590C0
void *
sub_2421E0(void *mem, RwUInt32 size, RwUInt32 hint)
{
    return realloc(mem, size);
}

// match: __fnxCalloc @ 0x00242200
// sp-match: __fnxCalloc @ 0x001590E0
void *
_fnxCalloc(RwUInt32 count, RwUInt32 size, RwUInt32 hint)
{
    RwUInt32    total = count * size;
    void       *mem = malloc(total);

    if (mem)
    {
        memset(mem, 0, total);
    }

    return mem;
}

// match: _sub_242240 @ 0x00242240
// sp-match: _sub_242240 @ 0x00159120
RwBool
sub_242240(void **funcs)
{
    if (funcs)
    {
        ourGlobals.memoryFuncs.rwmalloc = (void *(*)(RwUInt32, RwUInt32))funcs[0];
        ourGlobals.memoryFuncs.rwfree = (void (*)(void *))funcs[1];
        ourGlobals.memoryFuncs.rwrealloc = (void *(*)(void *, RwUInt32, RwUInt32))funcs[2];
        ourGlobals.memoryFuncs.rwcalloc = (void *(*)(RwUInt32, RwUInt32, RwUInt32))funcs[3];

        return TRUE;
    }

    ourGlobals.memoryFuncs.rwmalloc = sub_2421D0;
    ourGlobals.memoryFuncs.rwfree = free;
    ourGlobals.memoryFuncs.rwrealloc = sub_2421E0;
    ourGlobals.memoryFuncs.rwcalloc = _fnxCalloc;

    return TRUE;
}

// match: _sub_2422A0 @ 0x002422A0
// sp-match: _sub_2422A0 @ 0x00159180
void
sub_2422A0(void *mem)
{
    sub_2421B0(((void **)mem)[-1]);
}
