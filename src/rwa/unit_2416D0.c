/*
 * codfh-match: RenderWare Audio's Xbox OS layer (0x2416D0-0x2417C0):
 * semaphores, the library's threads (the database's _RwaThreadCreate) and
 * an interlocked store.
 */
#include "rwa.h"
#include "rwaint.h"

#define rwaINFINITE 0xFFFFFFFF
#define rwaWAIT_TIMEOUT 0x102

extern void *__stdcall CreateSemaphoreA(void *attributes, RwInt32 initial, RwInt32 maximum,
                                        const RwChar *name);
extern RwUInt32 __stdcall WaitForSingleObject(void *handle, RwUInt32 milliseconds);
extern RwBool __stdcall ReleaseSemaphore(void *semaphore, RwInt32 count, RwInt32 *previous);
extern void __stdcall Sleep(RwUInt32 milliseconds);
extern void *__stdcall CreateThread(void *attributes, RwUInt32 stackSize, void *start,
                                    void *parameter, RwUInt32 flags, RwUInt32 *threadId);
extern RwBool __stdcall SetThreadPriority(void *thread, RwInt32 priority);
extern RwInt32 _InterlockedExchange(RwInt32 volatile *target, RwInt32 value);
#pragma intrinsic(_InterlockedExchange)

// match: _sub_2416D0 @ 0x002416D0
// sp-match: _sub_2416D0 @ 0x00155810
void **
sub_2416D0(void **semaphore, RwInt32 initial, RwInt32 maximum)
{
    *semaphore = CreateSemaphoreA(NULL, initial, maximum, NULL);

    return *semaphore ? semaphore : NULL;
}

// match: _sub_2416F0 @ 0x002416F0
// sp-match: _sub_2416F0 @ 0x00155830
RwBool
sub_2416F0(void **semaphore)
{
    RwBool      result = FALSE;

    if (WaitForSingleObject(*semaphore, 0) != rwaWAIT_TIMEOUT)
    {
        result = TRUE;
    }

    return result;
}

// match: __RwaThreadCreate @ 0x00241710
// sp-match: __RwaThreadCreate @ 0x00155850
rwaThread *
_RwaThreadCreate(rwaThread *thread, void **(*func)(void *data), RwInt32 priority,
                 RwUInt32 stackSize)
{
    thread->func = func;
    thread->handle = NULL;
    thread->data = NULL;
    thread->priority = priority;
    thread->stackSize = stackSize;

    return thread;
}

// match: _sub_241740 @ 0x00241740
// sp-match: _sub_241740 @ 0x00155880
void
sub_241740(rwaThread *thread)
{
    void      **semaphore = thread->func(thread->data);

    if (semaphore)
    {
        ReleaseSemaphore(*semaphore, 1, NULL);
        Sleep(rwaINFINITE);
    }
}

// match: _sub_241770 @ 0x00241770
// sp-match: _sub_241770 @ 0x001558B0
rwaThread *
sub_241770(rwaThread *thread, void *data)
{
    RwUInt32    threadId;
    void       *handle;

    thread->data = data;

    handle = CreateThread(NULL, thread->stackSize, sub_241740, thread, 0, &threadId);
    if (!handle)
    {
        return NULL;
    }

    thread->handle = handle;
    SetThreadPriority(handle, thread->priority);

    return thread;
}

// match: _sub_2417B0 @ 0x002417B0
// sp-match: _sub_2417B0 @ 0x001558F0
RwUInt32 *
sub_2417B0(RwUInt32 *target, RwUInt32 value)
{
    _InterlockedExchange((RwInt32 volatile *)target, (RwInt32)value);

    return target;
}
