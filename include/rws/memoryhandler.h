/*
 * RenderWare Studio's memory types and its typed global operator new,
 * copied from the game framework (framework/core/memoryhandler/
 * memoryhandler.h): the RWS_DISABLE_MEMORY_CHECKING build the image has,
 * where RWS_OP_NEW(size) is operator new(size, RWS_MEMORY_TYPE_RWS) (the
 * stream handlers, unit attributehandlerstrfuncs, pass 2).
 */
#ifndef RWS_MEMORYHANDLER_H
#define RWS_MEMORYHANDLER_H

#include <stddef.h>

#include "rw/ostypes.h"

namespace RWS
{
   const RwUInt32 RWS_MEMORY_TYPE_RW = 0;
   const RwUInt32 RWS_MEMORY_TYPE_STD = 1;
   const RwUInt32 RWS_MEMORY_TYPE_RWS = 2;
}

void *operator new(size_t size, RwUInt32 type);

// The memory handler's alignment of its (empty) header.
const RwUInt32 RWS_MEMORY_ALIGNMENT = 16;

// The base allocator (the game's: the CRT's functions inside a critical
// section).
void BaseMemInit(void);
void BaseMemClose(void);
void *BaseMemAlloc(size_t size, RwUInt32 userTypeNum);
void BaseMemFree(void *pMem);
void *BaseMemReAlloc(void *pMem, size_t size, RwUInt32 userTypeNum);
void *BaseMemCalloc(size_t num, size_t size, RwUInt32 userTypeNum);

// RenderWare's allocation functions (the engine's memory functions call
// them); hint is a RenderWare memory hint.
void *RWSMalloc(size_t size, RwUInt32 hint);
void *RWSReAlloc(void *pMem, size_t newSize, RwUInt32 hint);
void *RWSCalloc(size_t num, size_t size, RwUInt32 hint);
void RWSFree(void *pMem);

// The base allocator's critical section, its busy flag (set while inside
// the CRT's functions; the asynchronous loader, sub_81380, waits for it to
// clear) and whether it is set up.
extern struct _RTL_CRITICAL_SECTION unk_4CF86C;
extern RwInt32 dword_4CF888;
extern bool byte_4CF88D;
// The hook's flag (sub_12F0A0 sets it, sub_12F090 clears it; sub_19D020
// reads it).
extern bool byte_4CF88C;

// The game's leak checks by region, compiled out in this build (the game
// loop's shutdowns ask sub_12F080 and report with sub_12F060), and the hook
// in RenderWare Studio's entity messages.
bool sub_12F080(RwInt32 arg_0);
void sub_12F060(RwInt32 arg_0);
void sub_12F090();
void sub_12F0A0();

#define RWS_OP_NEW(size) operator new(size, RWS::RWS_MEMORY_TYPE_RWS)

#endif
