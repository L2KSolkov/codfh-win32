/*
 * RwMemoryFunctions, RwOsGetMemoryInterface and RwFreeListPurgeAllFreeLists,
 * copied from RenderWare 3.7.2 RWSDK/src/plcore/bamemory.h, osintf.h and
 * bafrlist.h (the struct and the prototypes).
 * The engine keeps the block in its globals (RWSRCGLOBAL(memoryFuncs), at
 * 0x520214); RwMalloc, RwFree, RwFreeListAlloc and RwFreeListFree are
 * rw/badevice.h's (included at the end).
 * RwFreeList (opaque), RwFreeListCreate and RwFreeListDestroy.
 */
#ifndef RW_BAMEMORY_H
#define RW_BAMEMORY_H

#include <stddef.h>

#include "rw/ostypes.h"

typedef struct RwMemoryFunctions RwMemoryFunctions;
struct RwMemoryFunctions
{
    void *(*rwmalloc)(size_t size, RwUInt32 hint);
    void (*rwfree)(void *mem);
    void *(*rwrealloc)(void *mem, size_t newSize, RwUInt32 hint);
    void *(*rwcalloc)(size_t numObj, size_t sizeObj, RwUInt32 hint);
};

#ifdef    __cplusplus
extern "C"
{
#endif

typedef struct RwFreeList RwFreeList;

extern RwMemoryFunctions *RwOsGetMemoryInterface(void);
extern RwFreeList *RwFreeListCreate(RwInt32 entrySize, RwInt32 entriesPerBlock,
                                    RwInt32 alignment, RwUInt32 hint);
extern RwBool RwFreeListDestroy(RwFreeList * freelist);
extern RwInt32 RwFreeListPurgeAllFreeLists(void);

#ifdef    __cplusplus
}
#endif

enum RwMemoryHintDuration
{
    rwMEMHINTDUR_NADURATION = 0x00000000,
    rwMEMHINTDUR_FUNCTION   = 0x00010000,
    rwMEMHINTDUR_FRAME      = 0x00020000,
    rwMEMHINTDUR_EVENT      = 0x00030000,
    rwMEMHINTDUR_GLOBAL     = 0x00040000,
    rwMEMHINTDUR_MASK       = 0x00FF0000
};

#include "rw/badevice.h"

#endif
