/*
 * codfh-match: RenderWare Audio's object handles (the PS2 header's
 * rwaobject group): the handle list (0x506A60) and free list (0x506A68),
 * handle creation and release and the parameter accessors through an
 * object's interface.
 */
#include "rwa.h"
#include "rwaint.h"

#define rwaHandleFromLink(_link) ((RwaObjHandle *)((RwUInt8 *)(_link) - 8))

static rwaLink dword_506A60;        /* all handles */
static RwUInt8 unk_506A68[0x24];    /* handle free list */
static RwUInt32 dword_506A8C;

extern RwaObjHandle *Behavior_DispatchCallback(RwaObjHandle *handle, RwUInt32 index, RwInt32 type,
                                               void *data);
extern RwaObjHandle *sub_23F8E0(RwaObjHandle *handle, RwUInt32 index, RwInt32 type, void *data);
extern void DSPHandle_Stop(rwaInstance *obj, void *a, void *b);
extern RwInt32 sub_243B80(rwaObjInterface *objInterface);
extern rwaObjInterface *sub_243FF0(void *objInterface, rwaObjDef *def, RwUInt32 a, RwUInt32 b);
extern void *sub_243670(void *freeList, RwUInt32 hint);
extern void sub_2437A0(void *freeList, void *item);
extern void sub_2438E0(void *freeList);
extern RwBool sub_243950(RwUInt32 size, RwUInt32 count, RwUInt32 align, RwInt32 a,
                         void *freeList, RwUInt32 hint);

// match: _sub_23F770 @ 0x0023F770
// sp-match: _sub_23F770 @ 0x00152300
RwBool
sub_23F770(void)
{
    dword_506A60.next = &dword_506A60;
    dword_506A60.prev = &dword_506A60;

    if (!sub_243950(sizeof(RwaObjHandle), 0x40, 8, 0, unk_506A68,
                    rwaMEMHINTDUR_GLOBAL | rwaID_80B))
    {
        return FALSE;
    }

    dword_506A8C = TRUE;

    return TRUE;
}

// match: _sub_23F7B0 @ 0x0023F7B0
// sp-match: _sub_23F7B0 @ 0x00152340
static RwaObjHandle *
sub_23F7B0(rwaHandleParams *params)
{
    RwaObjHandle   *handle = params->handle;

    if (handle)
    {
        handle->flags = 1;

        return handle;
    }

    handle = (RwaObjHandle *)sub_243670(unk_506A68, rwaMEMHINTDUR_EVENT | rwaID_80B);
    handle->flags = 0;

    return handle;
}

// match: _sub_23F7E0 @ 0x0023F7E0
// sp-match: _sub_23F7E0 @ 0x00152370
static void
sub_23F7E0(RwaObjHandle *handle)
{
    if (!(handle->flags & 1))
    {
        sub_2437A0(unk_506A68, handle);
    }
}

// match: _DSPResource_Release @ 0x0023F800
// sp-match: _DSPResource_Release @ 0x00152390
void
DSPResource_Release(RwaObjHandle *handle, rwaReleaseParams *params)
{
    rwaReleaseParams    defaults;
    rwaInstance        *obj;

    defaults.a = NULL;
    defaults.b = NULL;
    defaults.handle = NULL;
    defaults.objInterface = NULL;

    if (!params)
    {
        params = &defaults;
    }

    if (handle->refCount > 0)
    {
        handle->refCount--;

        return;
    }

    if (handle->objInterface && sub_243B80(handle->objInterface) == 1)
    {
        params->objInterface = handle->objInterface;
    }

    obj = handle->obj;
    if (--*rwaInstGetExtra(obj) == 0 && !(handle->flags & 2))
    {
        DSPHandle_Stop(obj, params->a, params->b);
    }

    handle->link.prev->next = handle->link.next;
    handle->link.next->prev = handle->link.prev;

    sub_23F7E0(handle);
    params->handle = handle;
}

// match: _Behavior_DispatchCallback @ 0x0023F8B0
// sp-match: _Behavior_DispatchCallback @ 0x00152440
RwaObjHandle *
Behavior_DispatchCallback(RwaObjHandle *handle, RwUInt32 index, RwInt32 type, void *data)
{
    rwaInstance *obj = handle->obj;
    rwaParamFunc *setter = &handle->objInterface->setters[index];
    void *value = data;
    RwUInt32 param = setter->param;
    return setter->func(obj, param, value) ? handle : NULL;
}

// match: _sub_23F8E0 @ 0x0023F8E0
// sp-match: _sub_23F8E0 @ 0x00152470
RwaObjHandle *
sub_23F8E0(RwaObjHandle *handle, RwUInt32 index, RwInt32 type, void *data)
{
    rwaParamFunc   *getter = &handle->objInterface->getters[index];

    RwUInt32 param = getter->param;
    return getter->func(handle->obj, param, data) ? handle : NULL;
}

// match: _RwaObjHandleSetParamUInt8 @ 0x0023F910
// sp-match: _RwaObjHandleSetParamUInt8 @ 0x001524A0
RwaObjHandle *
RwaObjHandleSetParamUInt8(RwaObjHandle *handle, RwUInt32 index, RwInt32 type, ...)
{
    if (!handle)
    {
        return handle;
    }

    return Behavior_DispatchCallback(handle, index, type, &type + 1);
}

// match: _sub_23F940 @ 0x0023F940
// sp-match: _sub_23F940 @ 0x001524D0
RwaObjHandle *
sub_23F940(RwaObjHandle *handle, RwUInt32 index, RwInt32 type, void *data)
{
    if (!handle)
    {
        return handle;
    }

    return Behavior_DispatchCallback(handle, index, type, data);
}

// match: _sub_23F960 @ 0x0023F960
// sp-match: _sub_23F960 @ 0x001524F0
RwUInt32
sub_23F960(RwaObjHandle *handle, RwUInt32 index, RwInt32 type, RwBool *success)
{
    RwaObjHandle   *result = sub_23F8E0(handle, index, type, &index);

    if (success)
    {
        *success = result != NULL;
    }

    return index;
}

// match: _sub_23F9A0 @ 0x0023F9A0
// sp-match: _sub_23F9A0 @ 0x00152530
void
sub_23F9A0(void)
{
    while (dword_506A60.next != &dword_506A60)
    {
        DSPResource_Release(rwaHandleFromLink(dword_506A60.next), NULL);
    }

    sub_2438E0(unk_506A68);
    dword_506A8C = 0;
}

// match: _sub_23F9F0 @ 0x0023F9F0
// sp-match: _sub_23F9F0 @ 0x00152580
RwaObjHandle *
sub_23F9F0(rwaInstance *obj, void *objInterface, rwaHandleParams *params)
{
    rwaHandleParams defaults;
    RwaObjHandle   *handle;

    if (!params)
    {
        defaults.unk10 = 0;
        defaults.unk0C = 0;
        defaults.unk08 = 0;
        defaults.unk04 = 0;
        defaults.flags = 2;
        defaults.handle = NULL;
        params = &defaults;
    }

    handle = sub_23F7B0(params);
    if (!handle)
    {
        return NULL;
    }

    handle->flags |= 2;
    handle->obj = obj;
    handle->objInterface = NULL;
    handle->refCount = 0;

    if (objInterface || (objInterface = obj->def->interfaces[0]) != NULL)
    {
        handle->objInterface = sub_243FF0(objInterface, obj->def, params->unk0C, params->unk10);
        if (!handle->objInterface)
        {
            sub_23F7E0(handle);

            return NULL;
        }
    }

    ++*rwaInstGetExtra(handle->obj);

    handle->link.prev = NULL;
    handle->link.next = NULL;
    handle->link.next = dword_506A60.next;
    handle->link.prev = &dword_506A60;
    dword_506A60.next->prev = &handle->link;
    dword_506A60.next = &handle->link;

    return handle;
}
