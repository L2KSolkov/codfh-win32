/*
 * codfh-match: RenderWare Audio's object definitions (rwaobjdef.c in the
 * library's PS2 header, docs/reference/rwacore_ps2.h, which names the public
 * functions; the Xbox RwaObjDef layout differs from the header's).
 */
#include "rwa.h"
#include "rwaint.h"
#include <string.h>
#include <stddef.h>



extern RwaParamTypeHandle *_rwaParamTypeHandleRefreshType(RwaParamTypeHandle *handle);
extern RwBool sub_243B80(rwaObjInterface *objInterface);
extern void sub_244600(RwaParamType *paramType);
extern void sub_2438E0(void *freeList);
extern void sub_2443F0(void *pool);
extern void *TkFSManagerGetValue(void *obj, RwUInt32 index, void *data);
extern void sub_240C30(void *uniqueID);
extern void sub_240B40(void *uniqueID);
extern RwUInt8 unk_516C50[];
extern void *sub_244750(void *types, RwInt32 index);

rwaObjDef *dword_516C60;
static RwUInt8 unk_5068F8[0x5C];
static RwUInt8 unk_506954[0x24];
static RwUInt8 unk_506978[0x24];
static RwUInt8 unk_5068D0[0x24];
static RwUInt32 dword_50699C;
static RwUInt32 dword_5069A0;
static RwUInt32 dword_5069A4;


typedef RwBool (*rwaVoidFunc)(void);

// Its data (PLAN M5): literals, constants and tables where the image has them.

typedef RwInt32 (*rwaObjDefSearchFunc)(rwaObjDef *parent, rwaObjDef *child, void *data);
// Its data definitions (PLAN M5), in the image's address order.
// 0x0042E6F8
void *unk_42E6F8[4] =
{
    (void *)0x55AD338C,
    (void *)0x457E145E,
    (void *)0x551F5BA7,
    (void *)0xEFB797DD,
};
// 0x00516C50
RwUInt8 unk_516C50[12];
// End of its data definitions.

// match: _unk_42E6F8 @ 0x0042E6F8

// match: __rwaWaveDefUnregister @ 0x0023D710

RwBool
_rwaWaveDefUnregister(rwaVoidFunc *funcs, RwUInt32 count)
{
    RwUInt32    i;

    for (i = 0; i < count; i++)
    {
        if (!funcs[i]())
        {
            return FALSE;
        }
    }

    return TRUE;
}

extern RwBool sub_243BC0(void *iface, rwaObjDef *def, RwInt32 index);

// match: _sub_23D740 @ 0x0023D740
rwaObjDef *
sub_23D740(rwaObjDef *def, void *iface)
{
    if (!sub_243BC0(iface, def, 1))
    {
        return NULL;
    }

    def->interfaces[0] = iface;

    return def;
}

extern void sub_240BF0(rwaObjDef *def, const void *textID);
extern void sub_240C10(rwaObjDef *def, const void *uuid);

// match: _RwaObjDefAssignID @ 0x0023D770
rwaObjDef *
RwaObjDefAssignID(rwaObjDef *def, const void *uuid, const void *textID)
{
    sub_240BF0(def, textID);
    sub_240C10(def, uuid);

    return def;
}

// match: _RwaObjDefGetDefaultCreationParams @ 0x0023D7A0
rwaObjDef *
RwaObjDefGetDefaultCreationParams(rwaObjDef *def, void *params)
{
    if (def->query)
    {
        def->query(NULL, params);

        return def;
    }

    return NULL;
}

extern void *sub_243950(RwUInt32 size, RwUInt32 count, RwUInt32 align, RwInt32 a, void *freeList, RwUInt32 hint);
extern void *sub_244550(RwUInt32 size, RwUInt32 count, RwUInt32 align, RwInt32 a, RwInt32 b);

// match: _sub_23D7C0 @ 0x0023D7C0
rwaObjDef *
sub_23D7C0(rwaObjDef *def, RwUInt32 size, RwBool freeList)
{
    if (def->instances)
    {
        return NULL;
    }

    if (def->maxInstances > 1)
    {
        if (freeList)
        {
            def->instances = sub_243950(size, def->maxInstances, 1 << (def->flags >> 28), 1, NULL,
                                        rwaMEMHINTDUR_EVENT | rwaID_809);
            def->flags0C |= 0x40;
        }
        else
        {
            def->instances = sub_244550(size, def->maxInstances, 1 << (def->flags >> 28), 1, 0);
            def->flags0C |= 0x80;
        }
    }
    else
    {
        def->instances = (void *)1;
    }

    return def->instances ? def : NULL;
}

extern void *sub_243670(void *freeList, RwUInt32 hint);
extern void *sub_244440(void *pool, RwUInt32 size);
extern void *sub_242170(RwUInt32 size, RwUInt32 hint);

// match: _sub_23D860 @ 0x0023D860
void *
sub_23D860(rwaObjDef *def, RwUInt32 size)
{
    if (def->flags0C & 0x40)
    {
        return sub_243670(def->instances, def->hint);
    }

    if (def->flags0C & 0x80)
    {
        return sub_244440(def->instances, size);
    }

    return sub_242170(size, def->hint);
}

extern RwUInt32 sub_23F300(rwaObjDef *def, RwUInt32 flags, RwUInt32 *stateOffset);
extern void sub_2437A0(void *freeList, void *entry);
extern void sub_2444A0(void *pool, void *entry);
extern void sub_2421B0(void *entry);

// match: _sub_23D8B0 @ 0x0023D8B0
void
sub_23D8B0(rwaInstance *input, void *callback, void *data)
{
    void (*release)(void *, void *) = (void (*)(void *, void *))callback;
    rwaInstance *obj = input;
    RwUInt32 offset;  /* unused state offset; compiler reuses the input argument home */
    rwaObjDef *def = obj->def;
    void *memory = obj;

    if (obj->flags & 8)
    {
        memory = ((void **)obj)[-1];
    }
    else if (obj->flags & 0x10)
    {
        RwUInt8 *storage = (RwUInt8 *)obj;
        RwUInt32 size = sub_23F300(def, obj->flags & 7, &offset);
        /* Allocation pointer follows the variable-sized instance payload. */
        storage += size;
        memory = *(void **)storage;
    }

    if (def->instances && (!release || !(obj->flags & 0x20)))
    {
        if (def->flags0C & 0x40)
        {
            sub_2437A0(def->instances, memory);
        }
        else if (def->flags0C & 0x80)
        {
            sub_2444A0(def->instances, memory);
        }
        else
        {
            sub_2421B0(memory);
        }
    }
    else if (release)
    {
        release(memory, data);
    }
}

// match: _sub_23D940 @ 0x0023D940
rwaObjDef *
sub_23D940(rwaObjDef *def, void *obj)
{
    rwaLink    *head = &def->children;
    rwaLink    *cur = head->next;

    if (cur != head)
    {
        do
        {
            void   *inst = (RwUInt8 *)cur - 0x18;

            cur = cur->next;
            if (inst == obj)
            {
                return def;
            }
        }
        while (cur != head);
    }

    return NULL;
}



rwaObjDef *sub_23D970(rwaObjDef *def, rwaObjDef **parent, rwaObjDefSearchFunc callback,
                       void *data, RwInt32 self);

extern RwBool sub_2434E0(void *list, void *item);
extern void sub_2435D0(void *list);

/* The two qualified argument-home reads preserve the parent reloads
 * after the callback and on its successful child path. Original
 * declaration qualifiers are unknown. */
// match: _sub_23D970 @ 0x0023D970
rwaObjDef *
sub_23D970(rwaObjDef *def, rwaObjDef **parent, rwaObjDefSearchFunc callback, void *data,
           RwInt32 self)
{
    rwaLink    *cur;
    rwaObjDef *root = def;
    rwaLink *head;

    if (!root)
    {
        root = dword_516C60;
    }
    def = root;

    if (self == 1 && callback(root, root, data) == 1)
    {
        if (parent)
        {
            *parent = root;
        }

        return root;
    }

    head = &root->children;
    for (cur = head->next; cur != head; cur = cur->next)
    {
        rwaObjDef  *child = (rwaObjDef *)((RwUInt8 *)cur - offsetof(rwaObjDef, sibling));
        rwaObjDef  *found;

        if (callback(*(rwaObjDef *volatile *)&def, child, data) == 1)
        {
            if (parent)
            {
                *parent = *(rwaObjDef *volatile *)&def;
            }

            return child;
        }

        found = sub_23D970(child, parent, callback, data, 0);
        if (found)
        {
            return found;
        }
    }

    if (parent)
    {
        *parent = NULL;
    }

    return NULL;
}


// match: _sub_23DA20 @ 0x0023DA20
RwInt32
sub_23DA20(rwaObjDef *parent, rwaObjDef *child, rwaIfaceSearch *search)
{
    if ((child->flags0C & 4) && search->list &&
        sub_243BC0(search->iface, child, 0) && !sub_2434E0(search->list, child))
    {
        sub_2435D0(search->list);
        search->list = NULL;
    }

    return 0;
}

extern RwInt32 RwaUUIDCompare(const RwaUUID *a, const RwaUUID *b);

// match: _sub_23DA80 @ 0x0023DA80
RwInt32
sub_23DA80(rwaObjDef *parent, rwaObjDef *child, const RwaUUID *uuid)
{
    return !RwaUUIDCompare(*(const RwaUUID **)child, uuid);
}

/* Qualified parameter-table pointer reads preserve their loads before
 * the count tests. Original qualifiers are unknown. */
// match: _sub_23DAA0 @ 0x0023DAA0
static rwaObjDef *
sub_23DAA0(rwaObjDef *def)
{
    if (def->flags0C & 4)
    {
        {
            rwaParamTables *tables = (rwaParamTables *)def->interfaces;
            rwaParamDef *param = *(rwaParamDef *volatile *)&tables->inputs;
            RwUInt16 count = tables->noInputs;

            if (count > 0)
            {
                RwUInt32 i;

                param += count;
                i = count;
                do
                {
                    --param;
                    sub_240C30(param);
                }
                while (--i > 0);
            }
        }
        {
            rwaParamTables *tables = (rwaParamTables *)def->interfaces;
            rwaParamDef *param = *(rwaParamDef *volatile *)&tables->outputs;
            RwUInt16 count = tables->noOutputs;

            if (count > 0)
            {
                RwUInt32 i;

                param += count;
                i = count;
                do
                {
                    --param;
                    sub_240C30(param);
                }
                while (--i > 0);
            }
        }
        if (!(def->flags0C & 1))
        {
            sub_2421B0(((rwaParamTables *)def->interfaces)->inputs);
        }

        ((rwaParamTables *)def->interfaces)->inputs = NULL;
        ((rwaParamTables *)def->interfaces)->outputs = NULL;
    }

    return def;
}

// match: _sub_23DB30 @ 0x0023DB30
static void
sub_23DB30(rwaObjDef *def)
{
    sub_23DAA0(def);
    sub_240C30(def);

    if ((def->flags0C & 8) && !(def->flags0C & 0x20))
    {
        sub_2437A0(unk_506954, def->unk50);
    }

    if ((def->flags0C & 4) && !(def->flags0C & 0x10))
    {
        sub_2437A0(unk_506978, def->interfaces);
    }

    if (def->flags0C & 2)
    {
        sub_2437A0(unk_5068D0, def);
    }
}

// match: _sub_23DB90 @ 0x0023DB90
RwBool
sub_23DB90(rwaObjDef *def)
{
    rwaLink *list;
    rwaLink *child;

    while ((child = def->children.next) != &def->children)
    {
        if (!sub_23DB90((rwaObjDef *)((RwUInt8 *)child - offsetof(rwaObjDef, sibling))))
        {
            return FALSE;
        }
    }

    if (def->unregister)
    {
        def->unregister(def);
    }

    if (def->flags0C & 4)
    {
        rwaParamTables *tables = (rwaParamTables *)def->interfaces;
        child = tables->interfaces.next;
        list = &tables->interfaces;
        if (child != list)
        do
        {
            sub_243B80((rwaObjInterface *)((RwUInt8 *)child - offsetof(rwaObjInterface, link)));
            child = list->next;
        }
        while (child != list);
    }

    if (def->flags0C & 8)
    {
        list = (rwaLink *)def->unk50;
        while (list->next != list)
        {
            sub_244600((RwaParamType *)((RwUInt8 *)list->next - offsetof(RwaParamType, link)));
        }
    }

    if (def->instances)
    {
        if (def->flags0C & 0x40)
        {
            sub_2438E0(def->instances);
            def->instances = NULL;
        }
        else if (def->flags0C & 0x80)
        {
            sub_2443F0(def->instances);
            def->instances = NULL;
        }
        else
        {
            def->instances = NULL;
        }
    }

    if (def != (rwaObjDef *)unk_5068F8)
    {
        def->sibling.prev->next = def->sibling.next;
        def->sibling.next->prev = def->sibling.prev;
    }

    sub_23DB30(def);

    return TRUE;
}


// match: _sub_23DC60 @ 0x0023DC60
RwBool
sub_23DC60(rwaObjDef *root, void *iface, void *list)
{
    rwaIfaceSearch  search;

    search.iface = iface;
    search.list = list;
    sub_23D970(root, NULL, (rwaObjDefSearchFunc)sub_23DA20, &search, 1);

    return search.list != NULL;
}

// match: _sub_23DCA0 @ 0x0023DCA0
rwaObjDef *
sub_23DCA0(rwaObjDef *root, const RwaUUID *uuid, rwaObjDef **parentOut)
{
    RwaUUID     id = *uuid;
    rwaObjDef  *parent;
    rwaObjDef  *found;

    found = sub_23D970(root, &parent, (rwaObjDefSearchFunc)sub_23DA80, &id, 1);

    if (parentOut)
    {
        *parentOut = parent;
    }

    return found;
}
extern void sub_2438E0(void *freeList);
extern RwBool sub_23DB90(rwaObjDef *def);

/* The allocation and existing-table paths share the success return. */
// match: __rwaObjDefSetupParams @ 0x0023DD00
rwaObjDef *
_rwaObjDefSetupParams(rwaObjDef *def, rwaParamDef *inputs, RwUInt16 noInputs,
                      rwaParamDef *outputs, RwUInt16 noOutputs)
{
    RwUInt16    i;

    if (!inputs && !outputs)
    {
        def->flags0C &= ~1;
        ((rwaParamTables *)def->interfaces)->inputs =
            sub_242170((noInputs + noOutputs) * sizeof(rwaParamDef), rwaMEMHINTDUR_EVENT | rwaID_809);
        if (!((rwaParamTables *)def->interfaces)->inputs)
        {
            return NULL;
        }

        ((rwaParamTables *)def->interfaces)->outputs =
            ((rwaParamTables *)def->interfaces)->inputs + noInputs;
    }
    else
    {
        for (i = 0; i < noInputs; i++)
        {
            rwaParamDef    *param = &inputs[i];

            if (!_rwaParamTypeHandleRefreshType((RwaParamTypeHandle *)&param->type))
            {
                return NULL;
            }

            if (!param->handler)
            {
                param->handler = TkFSManagerGetValue;
            }
        }

        ((rwaParamTables *)def->interfaces)->inputs = inputs;
        ((rwaParamTables *)def->interfaces)->noInputs = noInputs;

        for (i = 0; i < noOutputs; i++)
        {
            rwaParamDef    *param = &outputs[i];

            if (!_rwaParamTypeHandleRefreshType((RwaParamTypeHandle *)&param->type))
            {
                return NULL;
            }

            if (!param->handler)
            {
                param->handler = TkFSManagerGetValue;
            }
        }

        def->flags0C |= 1;
        ((rwaParamTables *)def->interfaces)->outputs = outputs;
        ((rwaParamTables *)def->interfaces)->noOutputs = noOutputs;

    }
    return def;
}

// match: _sub_23DE20 @ 0x0023DE20
static void
sub_23DE20(rwaObjDef *input, RwInt32 io)
{
    rwaObjDef *def = input;
    void           *type = sub_244750(unk_516C50, 0);
    rwaParamDef    *param;
    RwUInt16        i;

    if (io == 1)
    {
        {
            rwaParamTables *tables = (rwaParamTables *)def->interfaces;
            rwaParamDef *params = tables->inputs;
            RwUInt16 count = tables->noInputs;

            for (i = 0; i < count; ++i)
            {
                param = &params[i];
                param->type = type;
                param->typeIndex = 0;
                param->handler = TkFSManagerGetValue;
                sub_240B40(param);
            }
        }
    }
    else
    {
        {
            rwaParamTables *tables = (rwaParamTables *)def->interfaces;
            rwaParamDef *params = tables->outputs;
            RwUInt16 count = tables->noOutputs;

            for (i = 0; i < count; ++i)
            {
                param = &params[i];
                param->type = type;
                param->typeIndex = 0;
                param->handler = TkFSManagerGetValue;
                sub_240B40(param);
            }
        }
    }
}

// match: __rwaObjDefCloseModule @ 0x0023DEC0
void
_rwaObjDefCloseModule(void)
{
    dword_50699C = 1;
    sub_23DB90((rwaObjDef *)unk_5068F8);
    sub_2438E0(unk_506954);
    sub_2438E0(unk_506978);
    sub_2438E0(unk_5068D0);
    dword_5069A0 = 0;
}

extern rwaObjDef *sub_23DFB0(rwaObjDef *parent, RwUInt32 flags, rwaObjDef *def, void *tables,
                             void *list, RwUInt32 hint);

/* Clear the packed size and alignment separately. These stores and the
 * alignment macro retain the original OR with the zeroed flag word. */
// match: _sub_23DF00 @ 0x0023DF00
static void
sub_23DF00(rwaObjDef *def)
{
    if (def->flags0C & 4)
    {
        sub_23DE20(def, 1);
        sub_23DE20(def, 2);
    }

    sub_240B40(def);

    if (def->flags0C & 4)
    {
        rwaParamTables *tables = (rwaParamTables *)def->interfaces;
        rwaLink        *list = &tables->interfaces;

        list->next = list;
        tables->interfaces.prev = list;
        tables->unk00 = NULL;
        tables->inputs = NULL;
        tables->outputs = NULL;
        tables->noInputs = 0;
        tables->noOutputs = 0;
    }

    if (def->flags0C & 8)
    {
        rwaLink    *list = (rwaLink *)def->unk50;

        list->next = list;
        list->prev = list;
    }

    /* Packed state-size/alignment word at +0x40. */
    def->unk40.stateSize = 0;
    def->unk40.stateAlign = 0;
    def->instances = NULL;
    rwaObjDefSetStateAlignment(def, 1);
    def->children.next = &def->children;
    def->children.prev = &def->children;
    def->maxInstances = 8;
    def->paramsSize = 0;
    def->unk54 = NULL;
    def->sibling.prev = NULL;
    def->sibling.next = NULL;
    def->waveDefs.next = &def->waveDefs;
    def->waveDefs.prev = &def->waveDefs;
    def->create = NULL;
    def->unk2C = NULL;
    def->unk30 = NULL;
    def->unlink = NULL;
    def->unregister = NULL;
    def->query = NULL;
}

// match: _sub_23DFB0 @ 0x0023DFB0
rwaObjDef *
sub_23DFB0(rwaObjDef *parent, RwUInt32 flags, rwaObjDef *def, void *tables, void *list,
           RwUInt32 hint)
{
    if (!parent && !dword_5069A4)
    {
        parent = dword_516C60;
    }

    if (!def)
    {
        def = (rwaObjDef *)sub_243670(unk_5068D0, rwaMEMHINTDUR_EVENT | rwaID_809);
        if (!def)
        {
            return NULL;
        }

        def->flags0C = 2;
    }
    else
    {
        def->flags0C = 0;
    }

    def->hint = hint;

    if ((RwUInt8)flags & 4)
    {
        if (!tables)
        {
            def->interfaces = sub_243670(unk_506978, rwaMEMHINTDUR_EVENT | rwaID_809);
            if (!def->interfaces)
            {
                sub_23DB30(def);

                return NULL;
            }
        }
        else
        {
            def->interfaces = tables;
            def->flags0C |= 0x10;
        }

        memset(def->interfaces, 0, sizeof(rwaParamTables));
        def->flags0C |= 4;
    }

    if ((RwUInt8)flags & 8)
    {
        if (!list)
        {
            def->unk50 = sub_243670(unk_506954, rwaMEMHINTDUR_EVENT | rwaID_809);
            if (!def->unk50)
            {
                sub_23DB30(def);

                return NULL;
            }
        }
        else
        {
            def->unk50 = list;
            def->flags0C |= 0x20;
        }

        memset(def->unk50, 0, sizeof(rwaLink));
        def->flags0C |= 8;
    }

    sub_23DF00(def);

    if (parent)
    {
        def->sibling.next = parent->children.next;
        def->sibling.prev = &parent->children;
        parent->children.next->prev = &def->sibling;
        parent->children.next = &def->sibling;
    }

    return def;
}

// match: _sub_23E0C0 @ 0x0023E0C0
RwBool
sub_23E0C0(void)
{
    dword_50699C = 0;
    dword_5069A4 = 1;

    if (sub_243950(0x5C, 8, 8, 0, unk_5068D0, rwaMEMHINTDUR_GLOBAL | rwaID_809))
    {
        if (sub_243950(0x18, 8, 8, 0, unk_506978, rwaMEMHINTDUR_GLOBAL | rwaID_809))
        {
            if (sub_243950(8, 8, 8, 0, unk_506954, rwaMEMHINTDUR_GLOBAL | rwaID_809))
            {
                dword_5069A0 = 1;
                dword_516C60 = sub_23DFB0(NULL, 0, (rwaObjDef *)unk_5068F8, NULL, NULL,
                                          rwaMEMHINTDUR_GLOBAL | rwaID_809);
                if (dword_516C60)
                {
                    RwaObjDefAssignID(dword_516C60, unk_42E6F8, NULL);
                    dword_516C60->maxInstances = 1;
                    dword_5069A4 = 0;

                    return TRUE;
                }

                sub_2438E0(unk_506954);
            }

            sub_2438E0(unk_506978);
        }

        sub_2438E0(unk_5068D0);
    }

    dword_5069A0 = 0;
    dword_5069A4 = 0;

    return FALSE;
}
