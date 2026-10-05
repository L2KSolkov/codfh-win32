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

    for (i = 0; i < count; i++)
    {
        for (j = 0; j < noParams; j++)
        {
            if (!RwaUUIDCompare(tables->inputs[j].uuid, def->inputs[i].uniqueID.uuid))
            {
                goto foundInput;
            }
        }

        compatible = FALSE;
      foundInput:;
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

// match: _sub_243E20 @ 0x00243E20
RwaObjInterfaceDef *
sub_243E20(RwaObjInterfaceDef *def)
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
    RwUInt32            count;
    RwUInt32            i;

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

    if (allocFunc)
    {
        objInterface = (rwaObjInterface *)allocFunc(size, data);
        if (!objInterface)
        {
            goto fail;
        }

        objInterface->flags = 1;
    }
    else
    {
        objInterface = (rwaObjInterface *)sub_242170(size, rwaMEMHINTDUR_EVENT | rwaID_80A);
        if (!objInterface)
        {
            goto fail;
        }

        objInterface->flags = 0;
    }

    objInterface->setters = (rwaParamFunc *)(objInterface + 1);
    objInterface->getters = objInterface->setters + def->noInputs;
    objInterface->def = def;
    objInterface->refCount = 0;

    n = ((rwaParamTables *)objDef->interfaces)->noInputs;
    count = def->noInputs;
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

    n = ((rwaParamTables *)objDef->interfaces)->noOutputs;
    count = def->noOutputs;
    for (i = 0; i < count; i++)
    {
        RwUInt16    j;

        for (j = 0; j < n; j++)
        {
            if (!RwaUUIDCompare(tables->outputs[j].uuid, def->outputs[i].uniqueID.uuid))
            {
                objInterface->getters[i].param = j;
                objInterface->getters[i].func =
                    (RwBool (*)(rwaInstance *, RwUInt32, void *))tables->outputs[j].handler;
            }
        }
    }

    objInterface->link.prev = head;
    objInterface->link.next = head->next;
    head->next->prev = &objInterface->link;
    head->next = &objInterface->link;

    return objInterface;

  fail:
    return NULL;
}
