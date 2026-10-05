/*
 * codfh-match: RenderWare Audio's object interface definitions (0x243B40-0x244050): their pool
 * and list, creation, registration, ID assignment and lookup. Split from unit_243AE0.c, the
 * listener's interface registration, at an original object boundary: in one unit VC7.0 emits
 * the listener functions, which call these defined later, at the unit's end (docs/units.md;
 * PLAN M7).
 */

#include "rwa.h"
#include "rwaint.h"

#define rwaInterfaceDefFromLink(_link) ((RwaObjInterfaceDef *)((RwUInt8 *)(_link) - 0x20))
#define rwaInterfaceFromLink(_link) ((rwaObjInterface *)((RwUInt8 *)(_link) - 0x14))

static RwUInt8 unk_50708C[0x24];        /* interface definitions */
static rwaLink dword_5070B0;            /* all interface definitions */
static RwUInt32 dword_5070B8;

/* prepareInterfaceDefinition: an inline with no address, named for its role.
 * Evidence: sub_243E20 has a shared initialization block after allocation and
 * flag selection; a pointer-returning inline preserves its branch placement. */
static __forceinline RwaObjInterfaceDef *prepareInterfaceDefinition(RwaObjInterfaceDef *def)
{
    if (!def)
    {
        def = (RwaObjInterfaceDef *)sub_243670(unk_50708C, rwaMEMHINTDUR_EVENT | rwaID_80A);
        if (!def)
        {
            return NULL;
        }

        def->flags = 0;
    }
    else
    {
        def->flags = 2;
    }

    return def;
}

/* allocateInterfaceInstance: an inline with no address, named for its role.
 * Evidence: sub_243FF0 joins the custom/default allocator paths at the
 * instance initializer; returning their pointer reproduces the late fallback. */
static __forceinline rwaObjInterface *allocateInterfaceInstance(RwUInt32 size, void *(*allocFunc)(RwUInt32 size, void *data), void *data)
{
    rwaObjInterface *objInterface;
    if (allocFunc)
    {
        objInterface = (rwaObjInterface *)allocFunc(size, data);
        if (!objInterface)
        {
            return NULL;
        }

        objInterface->flags = 1;
    }
    else
    {
        objInterface = (rwaObjInterface *)sub_242170(size, rwaMEMHINTDUR_EVENT | rwaID_80A);
        if (!objInterface)
        {
            return NULL;
        }

        objInterface->flags = 0;
    }

    return objInterface;
}
// match: _sub_243B40 @ 0x00243B40
RwBool
sub_243B40(void)
{
    dword_5070B0.next = &dword_5070B0;
    dword_5070B0.prev = &dword_5070B0;

    if (sub_243950(sizeof(RwaObjInterfaceDef), 0x10, 8, 0, unk_50708C,
                   rwaMEMHINTDUR_GLOBAL | rwaID_80A))
    {
        dword_5070B8 = TRUE;

        return TRUE;
    }

    return FALSE;
}
// match: _sub_243B80 @ 0x00243B80
RwBool
sub_243B80(rwaObjInterface *objInterface)
{
    if (objInterface->refCount > 0)
    {
        objInterface->refCount--;

        return FALSE;
    }

    objInterface->link.prev->next = objInterface->link.next;
    objInterface->link.next->prev = objInterface->link.prev;

    if (!(objInterface->flags & 1))
    {
        sub_2421B0(objInterface);
    }

    return TRUE;
}
// match: _sub_243BC0 @ 0x00243BC0
RwaObjInterfaceDef *
sub_243BC0(RwaObjInterfaceDef *def, rwaObjDef *objDef, RwBool a)
{
    rwaParamTables *tables = (rwaParamTables *)objDef->interfaces;
    RwUInt32        count = def->noInputs;
    RwUInt32        noParams = tables->noInputs;
    RwBool          compatible = TRUE;
    RwUInt32        i;
    RwUInt32        j;

    {
        RwUInt32 k;
        /* The separate counter and qualified table-pointer read reproduce
         * the address operands at 243C12. Original qualification is unknown. */
        for (k = 0; k < count; k++)
        {
            for (j = 0; j < noParams; j++)
            {
                if (!RwaUUIDCompare(tables->inputs[j].uuid,
                                (*(_rwaParamID *volatile *)&def->inputs)[k].uniqueID.uuid))
                {
                    goto foundInput;
                }
            }

            compatible = FALSE;
          foundInput:;
        }
    }
    count = def->noOutputs;
    noParams = ((rwaParamTables *)objDef->interfaces)->noOutputs;
    for (i = 0; i < count; i++)
    {
        for (j = 0; j < noParams; j++)
        {
            if (!RwaUUIDCompare(tables->outputs[j].uuid, def->outputs[i].uniqueID.uuid))
            {
                goto foundOutput;
            }
        }

        compatible = FALSE;
      foundOutput:;
    }

    return compatible ? def : NULL;
}
// match: _sub_243CD0 @ 0x00243CD0
RwaObjInterfaceDef *
sub_243CD0(RwaObjInterfaceDef *def, _rwaParamID *inputs, RwUInt32 noInputs,
           _rwaParamID *outputs, RwUInt32 noOutputs)
{
    if (def->inputs && def->outputs)
    {
        if (!(def->flags & 1))
        {
            sub_2421B0(def->inputs);
        }

        def->inputs = NULL;
        def->outputs = NULL;
    }

    if (inputs && outputs)
    {
        RwUInt32    i;

        for (i = 0; i < noInputs; i++)
        {
            inputs[i].uniqueID.flags = 0;
            if (!_rwaParamTypeHandleRefreshType(&inputs[i].type))
            {
                return NULL;
            }
        }

        for (i = 0; i < noOutputs; i++)
        {
            outputs[i].uniqueID.flags = 0;
            if (!_rwaParamTypeHandleRefreshType(&outputs[i].type))
            {
                return NULL;
            }
        }

        def->inputs = inputs;
        def->flags |= 1;
        def->noOutputs = (RwUInt16)noOutputs;
        def->outputs = outputs;
        def->noInputs = (RwUInt16)noInputs;

        return def;
    }
    else
    {
        RwUInt32    size = (noInputs + noOutputs) * sizeof(_rwaParamID);
        _rwaParamID *ids = (_rwaParamID *)sub_242170(size, rwaMEMHINTDUR_EVENT | rwaID_80A);

        def->inputs = ids;
        if (!ids)
        {
            return NULL;
        }

        def->outputs = &ids[noInputs];
        memset(ids, 0, size);
        def->flags &= ~1;

        return def;
    }
}
// match: _RwaWaveDictAssignID @ 0x00243DF0
RwaObjInterfaceDef *
RwaWaveDictAssignID(RwaObjInterfaceDef *def, const RwaUUID *uuid, const RwChar *name)
{
    sub_240C10(&def->uniqueID, uuid);
    sub_240BF0(&def->uniqueID, name);

    return def;
}
// match: _sub_243E20 @ 0x00243E20
RwaObjInterfaceDef *
sub_243E20(RwaObjInterfaceDef *def)
{
    def = prepareInterfaceDefinition(def);
    if (!def)
    {
        return NULL;
    }

    def->noInputs = 0;
    def->noOutputs = 0;
    def->inputs = NULL;
    def->outputs = NULL;
    def->unregister = NULL;
    sub_240B40(&def->uniqueID);

    def->link.prev = NULL;
    def->link.next = NULL;
    def->link.next = dword_5070B0.next;
    def->link.prev = &dword_5070B0;
    dword_5070B0.next->prev = &def->link;
    dword_5070B0.next = &def->link;

    return def;
}
// match: _sub_243EA0 @ 0x00243EA0
RwBool
sub_243EA0(RwaObjInterfaceDef *def)
{
    RwUInt32    count;
    RwUInt32    i;

    if (def->unregister)
    {
        def->unregister(def);
    }

    sub_240C30(&def->uniqueID);

    count = def->noInputs;
    for (i = 0; i < count; i++)
    {
        sub_240C30(&def->inputs[i].uniqueID);
    }

    count = def->noOutputs;
    for (i = 0; i < count; i++)
    {
        sub_240C30(&def->outputs[i].uniqueID);
    }

    if (!(def->flags & 1))
    {
        sub_2421B0(def->inputs);
    }

    def->link.prev->next = def->link.next;
    def->link.next->prev = def->link.prev;

    if (!(def->flags & 2))
    {
        sub_2437A0(unk_50708C, def);
    }

    return TRUE;
}
// match: _sub_243F40 @ 0x00243F40
RwaObjInterfaceDef *
sub_243F40(const RwaUUID *uuid)
{
    rwaLink    *cur;

    if (!uuid)
    {
        return NULL;
    }

    for (cur = dword_5070B0.next; cur != &dword_5070B0; cur = cur->next)
    {
        RwaObjInterfaceDef *def = rwaInterfaceDefFromLink(cur);

        if (!RwaUUIDCompare(def->uniqueID.uuid, uuid))
        {
            return def;
        }
    }

    return NULL;
}
// match: _sub_243F90 @ 0x00243F90
void
sub_243F90(void)
{
    while (dword_5070B0.next != &dword_5070B0)
    {
        sub_243EA0(rwaInterfaceDefFromLink(dword_5070B0.next));
    }

    dword_5070B0.next = &dword_5070B0;
    dword_5070B0.prev = &dword_5070B0;
    sub_2438E0(unk_50708C);
    dword_5070B8 = 0;
}
// match: _sub_243FF0 @ 0x00243FF0
rwaObjInterface *
sub_243FF0(RwaObjInterfaceDef *def, rwaObjDef *objDef,
           void *(*allocFunc)(RwUInt32 size, void *data), void *data)
{
    rwaParamTables     *tables = (rwaParamTables *)objDef->interfaces;
    rwaLink            *head = &tables->interfaces;
    rwaLink            *cur;
    rwaObjInterface    *objInterface;
    RwUInt32            size;
    RwUInt16            n;
    RwUInt16            count;
    RwUInt16            i;

    for (cur = head->next; cur != head; cur = cur->next)
    {
        objInterface = rwaInterfaceFromLink(cur);
        if (objInterface->def == def)
        {
            objInterface->refCount++;

            return objInterface;
        }
    }

    if (!sub_243BC0(def, objDef, TRUE))
    {
        return NULL;
    }

    size = (def->noInputs + def->noOutputs) * sizeof(rwaParamFunc) + sizeof(rwaObjInterface);

    objInterface = allocateInterfaceInstance(size, allocFunc, data);
    if (!objInterface)
    {
        goto fail;
    }

    objInterface->setters = (rwaParamFunc *)(objInterface + 1);
    objInterface->getters = objInterface->setters + def->noInputs;
    objInterface->def = def;
    objInterface->refCount = 0;

    count = def->noInputs;
    n = ((rwaParamTables *)objDef->interfaces)->noInputs;
    for (i = 0; i < count; i++)
    {
        RwUInt16    j;

        for (j = 0; j < n; j++)
        {
            if (!RwaUUIDCompare(tables->inputs[j].uuid, def->inputs[i].uniqueID.uuid))
            {
                objInterface->setters[i].param = j;
                objInterface->setters[i].func =
                    (RwBool (*)(rwaInstance *, RwUInt32, void *))tables->inputs[j].handler;
            }
        }
    }

    {
        RwUInt16 k;
        /* The separate output counter and qualified table-pointer access
         * preserve the address operands at 24417C. Original qualification
         * is unknown; the shared definition type remains unqualified. */
        n = ((rwaParamTables *)objDef->interfaces)->noOutputs;
        count = def->noOutputs;
        for (k = 0; k < count; k++)
        {
            RwUInt16    j;

            for (j = 0; j < n; j++)
            {
                if (!RwaUUIDCompare(tables->outputs[j].uuid,
                                (*(_rwaParamID *volatile *)&def->outputs)[k].uniqueID.uuid))
                {
                    objInterface->getters[k].param = j;
                    objInterface->getters[k].func =
                        (RwBool (*)(rwaInstance *, RwUInt32, void *))tables->outputs[j].handler;
                }
            }
        }
    }

    objInterface->link.next = head->next;
    objInterface->link.prev = head;
    head->next->prev = &objInterface->link;
    head->next = &objInterface->link;

    return objInterface;

  fail:
    return NULL;
}
