/*
 * codfh-match: RenderWare Audio's object instances (rwaobj.c, after
 * _rwaObjFindFixed and _rwaObjCloseModule): the instance list (0x506A28),
 * the connection free list (0x506A34), the top-level object (0x506A58),
 * instance creation and destruction and the module open and close.
 */
#include "rwa.h"
#include "rwaint.h"

#define rwaInstFromLink(_link) ((rwaInstance *)((RwUInt8 *)(_link) - 4))
#define rwaInstFromSubLink(_link) ((rwaInstance *)((RwUInt8 *)(_link) - 0x14))
#define rwaObjDefGetTables(_def) ((rwaParamTables *)(_def)->interfaces)

static RwUInt8 unk_506A00[0x28];    /* the top-level object */
static rwaLink dword_506A28;        /* all instances */
static RwUInt32 dword_506A30;
static RwUInt8 unk_506A34[0x24];    /* connection free list */
static rwaInstance *dword_506A58;   /* the top-level object */
static RwUInt32 dword_506A5C;

extern rwaObjDef *dword_516C60;

extern rwaObjDef *sub_23D7C0(rwaObjDef *def, RwUInt32 size, RwBool freeList);
extern void *sub_23D860(rwaObjDef *def, RwUInt32 size);
extern void sub_23D8B0(rwaInstance *obj, void *a, void *b);
extern rwaObjDef *sub_23D940(rwaObjDef *def, void *obj);
extern void *sub_242170(RwUInt32 size, RwUInt32 hint);
extern void sub_2421B0(void *data);
extern void *sub_243600(rwaLink *list, rwaLink *(*callback)(rwaLink *, void *), void *data);
extern void sub_2437A0(void *freeList, void *item);
extern void sub_2438E0(void *freeList);
extern RwBool sub_243950(RwUInt32 size, RwUInt32 count, RwUInt32 align, RwInt32 a,
                         void *freeList, RwUInt32 hint);

// match: _sub_23EF00 @ 0x0023EF00
static void *
sub_23EF00(rwaObjDef *def, void *b, void *params, RwUInt32 size)
{
    return unk_506A00;
}

// match: _sub_23EF10 @ 0x0023EF10
rwaInstance *
sub_23EF10(rwaObjDef *def, RwUInt32 *flags, void *params, RwUInt32 size)
{
    RwUInt32    objFlags = *flags;

    if (!def->instances && !sub_23D7C0(def, size, (objFlags >> 2) & 1))
    {
        return NULL;
    }

    return (rwaInstance *)sub_23D860(def, size);
}

// match: _sub_23EF50 @ 0x0023EF50
static RwBool
sub_23EF50(rwaInstance *obj, rwaInstSearch *search)
{
    if (obj->def == search->def && (obj->flags & 4))
    {
        search->found = obj->flags;

        return FALSE;
    }

    return TRUE;
}

// match: _sub_23EF80 @ 0x0023EF80
static rwaInstParams *
sub_23EF80(rwaInstance *obj)
{
    if (obj->state)
    {
        if (obj->flags & 2)
        {
            return (rwaInstParams *)(obj->state + rwaObjDefGetStateSize(obj->def) + 4);
        }

        return (rwaInstParams *)(obj->state + rwaObjDefGetStateSize(obj->def));
    }

    if (obj->flags & 2)
    {
        return (rwaInstParams *)((RwUInt32 *)(obj + 1) + 1);
    }

    return (rwaInstParams *)(obj + 1);
}

// match: _sub_23EFC0 @ 0x0023EFC0
static void
sub_23EFC0(rwaInstance *obj, rwaObjDef *def, RwUInt32 flags, RwUInt32 stateOffset)
{
    obj->def = def;
    obj->flags = flags;
    obj->state = (RwUInt8 *)obj;
    obj->state += stateOffset;

    if (flags & 1)
    {
        rwaInstParams  *params = sub_23EF80(obj);
        rwaInput       *input;
        rwaLink        *output;
        RwUInt16        count;
        RwUInt16        i;

        params->inputs = (rwaInput *)(params + 1);
        params->outputs = (rwaLink *)(params->inputs + rwaObjDefGetTables(def)->noInputs);

        input = params->inputs;
        count = rwaObjDefGetTables(def)->noInputs;
        for (i = 0; i < count; i++)
        {
            input->conns.next = &input->conns;
            input->conns.prev = &input->conns;
            input->unk08 = input;
            input++;
        }

        output = params->outputs;
        count = rwaObjDefGetTables(def)->noOutputs;
        for (i = 0; i < count; i++)
        {
            output->next = output;
            output->prev = output;
            output++;
        }
    }

    if (obj->flags & 2)
    {
        RwUInt32   *extra;

        if (obj->state)
        {
            extra = (RwUInt32 *)(obj->state + rwaObjDefGetStateSize(obj->def));
        }
        else
        {
            extra = (RwUInt32 *)(obj + 1);
        }

        *extra = 0;
    }

    obj->subObjs.next = &obj->subObjs;
    obj->subObjs.prev = &obj->subObjs;
    obj->subObjLink.prev = NULL;
    obj->subObjLink.next = NULL;
}

// match: _sub_23F070 @ 0x0023F070
RwBool
sub_23F070(rwaInstance *obj, rwaInstFind *find)
{
    if (obj->def == find->def)
    {
        find->found = obj;

        return FALSE;
    }

    return TRUE;
}

// match: _sub_23F090 @ 0x0023F090
void
sub_23F090(RwBool (*callback)(rwaInstance *obj, void *data), void *data)
{
    rwaLink    *cur;

    for (cur = dword_506A28.next; cur != &dword_506A28; cur = cur->next)
    {
        if (!callback(rwaInstFromLink(cur), data))
        {
            break;
        }
    }
}

// match: _sub_23F0D0 @ 0x0023F0D0
rwaInstance *
sub_23F0D0(rwaInstance *volatile input, RwBool ok)
{
    /* Preserve the parameter-home reloads at the two fallback paths.
     * Their source qualifier is unknown; this local qualification reproduces
     * the observed reads without qualifying the shared instance type. */
    rwaInstance    *obj = input;
    rwaInstance    *result = obj;
    rwaLink        *cur;
    rwaInstance    *status;

    if (!ok)
    {
        if (obj->def->unk2C)
        {
            status = obj->def->unk2C(obj);
        }
        else
        {
            status = input;
        }
        if (!status)
        {
            result = NULL;
        }
    }
    else
    {
        status = input;
    }

    cur = obj->subObjs.next;
    while (cur != &obj->subObjs)
    {
        rwaInstance    *sub = rwaInstFromSubLink(cur);

        cur = cur->next;
        if (sub->def->unk2C)
        {
            status = sub->def->unk2C(sub);
        }

        if (!status)
        {
            result = NULL;
        }
    }

    return result;
}


// match: _sub_23F140 @ 0x0023F140
rwaInstance *
sub_23F140(rwaInstance *volatile input, RwBool ok)
{
    /* Preserve the parameter-home reloads at the two fallback paths.
     * Their source qualifier is unknown; this local qualification reproduces
     * the observed reads without qualifying the shared instance type. */
    rwaInstance    *obj = input;
    rwaInstance    *result = obj;
    rwaLink        *cur;
    rwaInstance    *status;

    if (!ok)
    {
        if (obj->def->unk30)
        {
            status = obj->def->unk30(obj);
        }
        else
        {
            status = input;
        }
        if (!status)
        {
            result = NULL;
        }
    }
    else
    {
        status = input;
    }

    cur = obj->subObjs.next;
    while (cur != &obj->subObjs)
    {
        rwaInstance    *sub = rwaInstFromSubLink(cur);

        cur = cur->next;
        if (sub->def->unk30)
        {
            status = sub->def->unk30(sub);
        }

        if (!status)
        {
            result = NULL;
        }
    }

    return result;
}

// match: _sub_23F1B0 @ 0x0023F1B0
static rwaLink *
sub_23F1B0(rwaLink *link, void *def)
{
    return rwaInstFromLink(link)->def == def ? link : NULL;
}

// match: _sub_23F1D0 @ 0x0023F1D0
void *
sub_23F1D0(rwaObjDef *def)
{
    return sub_243600(&dword_506A28, sub_23F1B0, def);
}

// match: _sub_23F1F0 @ 0x0023F1F0
rwaInstance *
sub_23F1F0(rwaInstance *obj, RwUInt32 index, RwInt32 inputOutput)
{
    rwaInstParams  *params = sub_23EF80(obj);

    if (inputOutput == 1)
    {
        rwaInput   *input = &params->inputs[index];
        rwaLink    *cur = input->conns.next;
        rwaLink    *end = input->conns.prev;

        while (cur != end)
        {
            rwaConnection  *conn = (rwaConnection *)((RwUInt8 *)cur - 0x14);

            cur = cur->next;
            conn->outLink.prev->next = conn->outLink.next;
            conn->outLink.next->prev = conn->outLink.prev;
            conn->inLink.prev->next = conn->inLink.next;
            conn->inLink.next->prev = conn->inLink.prev;
            sub_2437A0(unk_506A34, conn);
        }
    }
    else
    {
        rwaLink    *output = &params->outputs[index];
        rwaLink    *cur = output->next;
        rwaLink    *end = output->prev;

        while (cur != end)
        {
            rwaConnection  *conn = (rwaConnection *)((RwUInt8 *)cur - 0x0C);

            cur = cur->next;
            conn->outLink.prev->next = conn->outLink.next;
            conn->outLink.next->prev = conn->outLink.prev;
            conn->inLink.prev->next = conn->inLink.next;
            conn->inLink.next->prev = conn->inLink.prev;
            sub_2437A0(unk_506A34, conn);
        }
    }

    return obj;
}

// match: _sub_23F2B0 @ 0x0023F2B0
static void
sub_23F2B0(rwaInstance *obj, RwInt32 inputOutput)
{
    RwUInt32    count;
    RwUInt32    i;

    if (inputOutput == 1)
    {
        count = rwaObjDefGetTables(obj->def)->noInputs;
    }
    else
    {
        count = rwaObjDefGetTables(obj->def)->noOutputs;
    }

    for (i = 0; i < count; i++)
    {
        sub_23F1F0(obj, i, inputOutput);
    }
}

// match: _sub_23F2F0 @ 0x0023F2F0
rwaInstance *
sub_23F2F0(void)
{
    return dword_506A58;
}

// match: _sub_23F300 @ 0x0023F300
RwUInt32
sub_23F300(rwaObjDef *def, RwUInt32 flags, RwUInt32 *stateOffset)
{
    RwUInt32    size;
    RwUInt32    unused;

    if (!stateOffset)
    {
        stateOffset = &unused;
    }

    size = sizeof(rwaInstance);

    if (rwaObjDefGetStateSize(def) > 0)
    {
        RwUInt32    align;

        if (!sub_23F1D0(def) && (1 << (def->flags >> 28)) == 1)
        {
            def->flags &= 0x0FFFFFFF;
            rwaObjDefSetStateAlignment(def, 4);
        }

        align = 1 << (def->flags >> 28);
        *stateOffset = (sizeof(rwaInstance) + align - 1) & ~(align - 1);
        size = rwaObjDefGetStateSize(def) + *stateOffset;
    }
    else
    {
        *stateOffset = 0;
    }

    if (flags & 2)
    {
        size += 4;
    }

    if (flags & 1)
    {
        size += sizeof(rwaInstParams) +
                rwaObjDefGetTables(def)->noInputs * sizeof(rwaInput) +
                rwaObjDefGetTables(def)->noOutputs * sizeof(rwaLink);
    }

    return size;
}

// match: __rwaObjFindFixed @ 0x0023F3B0
RwUInt32
_rwaObjFindFixed(rwaObjDef *def)
{
    rwaInstSearch   search;

    search.def = def;
    search.found = 0;
    sub_23F090((RwBool (*)(rwaInstance *, void *))sub_23EF50, &search);

    return search.found;
}

// match: _DSPHandle_Stop @ 0x0023F3E0
void
DSPHandle_Stop(rwaInstance *obj, void *a, void *b)
{
    rwaLink    *cur;

    if (obj->def->unlink)
    {
        obj->def->unlink(obj, a, b);
    }

    if (obj->subObjLink.next)
    {
        obj->subObjLink.prev->next = obj->subObjLink.next;
        obj->subObjLink.next->prev = obj->subObjLink.prev;
        obj->subObjLink.prev = NULL;
        obj->subObjLink.next = NULL;
    }

    cur = obj->subObjs.next;
    while (cur != &obj->subObjs)
    {
        rwaLink    *next = cur->next;

        cur->prev->next = cur->next;
        cur->next->prev = cur->prev;
        cur = next;
    }

    if (obj->flags & 1)
    {
        sub_23F2B0(obj, 1);
        sub_23F2B0(obj, 2);
    }

    obj->link.prev->next = obj->link.next;
    obj->link.next->prev = obj->link.prev;

    sub_23D8B0(obj, a, b);
}

// match: __rwaObjCloseModule @ 0x0023F480
void
_rwaObjCloseModule(void)
{
    dword_506A30 = 1;
    DSPHandle_Stop(dword_506A58, NULL, NULL);
    dword_506A58 = NULL;
    sub_2438E0(unk_506A34);
    dword_506A5C = 0;
}

// match: _sub_23F4C0 @ 0x0023F4C0
rwaInstance *
sub_23F4C0(rwaObjDef *def, rwaInstance *parent, RwUInt32 flags, void *params,
           void *(*allocFunc)(rwaObjDef *def, void *data, void *params, RwUInt32 size),
           void *data)
{
    RwUInt8         buffer[0x200];
    void           *allocated;
    RwUInt32        stateOffset;
    RwUInt32        size;
    rwaInstance    *obj;

    flags &= 7;

    if (dword_506A58)
    {
        if (!parent)
        {
            parent = sub_23F2F0();
        }

        if (!sub_23D940(parent->def, def))
        {
            return NULL;
        }
    }

    allocated = NULL;
    if (!params)
    {
        params = buffer;
        if (def->paramsSize > sizeof(buffer))
        {
            allocated = sub_242170(def->paramsSize, rwaMEMHINTDUR_FUNCTION | rwaID_80B);
            if (!allocated)
            {
                return NULL;
            }

            params = allocated;
        }

        if (def->query)
        {
            def->query(NULL, params);
        }
        else
        {
            params = NULL;
        }
    }

    size = sub_23F300(def, flags, &stateOffset);

    if (allocFunc && (obj = (rwaInstance *)allocFunc(def, data, params, size)) != NULL)
    {
        flags |= 0x20;
    }
    else
    {
        obj = sub_23EF10(def, &flags, params, size);
        if (!obj)
        {
            if (allocated)
            {
                sub_2421B0(allocated);
            }

            return NULL;
        }
    }

    obj->parent = parent;
    sub_23EFC0(obj, def, flags, stateOffset);

    if (dword_506A58)
    {
        obj->subObjLink.next = parent->subObjs.next;
        obj->subObjLink.prev = &parent->subObjs;
        parent->subObjs.next->prev = &obj->subObjLink;
        parent->subObjs.next = &obj->subObjLink;
    }

    if (obj->def->create && !obj->def->create(obj, parent, params, allocFunc, data))
    {
        if (allocated)
        {
            sub_2421B0(allocated);
        }

        if (dword_506A58)
        {
            obj->subObjLink.prev->next = obj->subObjLink.next;
            obj->subObjLink.next->prev = obj->subObjLink.prev;
        }

        sub_23D8B0(obj, NULL, NULL);

        return NULL;
    }

    if (allocated)
    {
        sub_2421B0(allocated);
    }

    obj->link.next = dword_506A28.next;
    obj->link.prev = &dword_506A28;
    dword_506A28.next->prev = &obj->link;
    dword_506A28.next = &obj->link;

    return obj;
}

// match: _sub_23F6E0 @ 0x0023F6E0
RwBool
sub_23F6E0(void)
{
    dword_506A28.next = &dword_506A28;
    dword_506A28.prev = &dword_506A28;
    dword_506A30 = 0;

    if (sub_243950(sizeof(rwaConnection), 0x10, 8, 0, unk_506A34,
                   rwaMEMHINTDUR_GLOBAL | rwaID_80B))
    {
        dword_506A5C = 1;
        dword_506A58 = sub_23F4C0(dword_516C60, NULL, 0, NULL,
                                  sub_23EF00, NULL);
        if (dword_506A58)
        {
            return TRUE;
        }

        sub_2438E0(unk_506A34);
    }

    dword_506A5C = 0;

    return FALSE;
}
