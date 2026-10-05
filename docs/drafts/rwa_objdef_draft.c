// match: _sub_23D970 @ 0x0023D970
rwaObjDef *
sub_23D970(rwaObjDef *def, rwaObjDef **parent, rwaObjDefSearchFunc callback, void *data,
           RwInt32 self)
{
    rwaLink    *cur;

    if (!def)
    {
        def = dword_516C60;
    }

    if (self == 1 && callback(def, def, data) == 1)
    {
        if (parent)
        {
            *parent = def;
        }

        return def;
    }

    for (cur = def->children.next; cur != &def->children; cur = cur->next)
    {
        rwaObjDef  *child = (rwaObjDef *)((RwUInt8 *)cur - 0x18);
        rwaObjDef  *found;

        if (callback(def, child, data) == 1)
        {
            if (parent)
            {
                *parent = def;
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

extern void sub_240C30(void *uniqueID);
extern void sub_2421B0(void *data);

// match: _sub_23DAA0 @ 0x0023DAA0
static rwaObjDef *
sub_23DAA0(rwaObjDef *def)
{
    if (def->flags0C & 4)
    {
        rwaParamTables *tables = (rwaParamTables *)def->interfaces;
        RwUInt8        *param;
        RwUInt32        i;

        param = tables->inputs + tables->noInputs * 0x18;
        for (i = tables->noInputs; i; i--)
        {
            param -= 0x18;
            sub_240C30(param);
        }

        tables = (rwaParamTables *)def->interfaces;
        param = tables->outputs + tables->noOutputs * 0x18;
        for (i = tables->noOutputs; i; i--)
        {
            param -= 0x18;
            sub_240C30(param);
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

extern RwUInt8 unk_506954[];
extern RwUInt8 unk_506978[];
extern RwUInt8 unk_5068D0[];
extern void sub_2437A0(void *freeList, void *entry);

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

extern RwUInt8 unk_5068F8[];
extern void sub_243B80(void *entry);
extern void sub_244600(void *entry);
extern void sub_2438E0(void *freeList);
extern void sub_2443F0(void *pool);

// match: _sub_23DB90 @ 0x0023DB90
RwBool
sub_23DB90(rwaObjDef *def)
{
    rwaLink    *list;

    while (def->children.next != &def->children)
    {
        if (!sub_23DB90((rwaObjDef *)((RwUInt8 *)def->children.next - 0x18)))
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
        list = (rwaLink *)((RwUInt8 *)def->interfaces + 4);
        while (list->next != list)
        {
            sub_243B80((RwUInt8 *)list->next - 0x14);
        }
    }

    if (def->flags0C & 8)
    {
        list = (rwaLink *)def->unk50;
        while (list->next != list)
        {
            sub_244600((RwUInt8 *)list->next - 0x20);
        }
    }

    if (def->instances)
    {
        if (def->flags0C & 0x40)
        {
            sub_2438E0(def->instances);
        }
        else if (def->flags0C & 0x80)
        {
            sub_2443F0(def->instances);
        }

        def->instances = NULL;
    }

    if (def != (rwaObjDef *)unk_5068F8)
    {
        def->sibling.prev->next = def->sibling.next;
        def->sibling.next->prev = def->sibling.prev;
    }

    sub_23DB30(def);

    return TRUE;
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
extern RwUInt8 unk_516C50[];
extern void *sub_244750(void *types, RwInt32 index);
extern void sub_240B40(void *uniqueID);

// match: _sub_23DE20 @ 0x0023DE20
static void
sub_23DE20(rwaObjDef *def, RwInt32 io)
{
    void           *type = sub_244750(unk_516C50, 0);
    rwaParamTables *tables = (rwaParamTables *)def->interfaces;
    rwaParamDef    *param;
    RwUInt32        i;

    if (io == 1)
    {
        param = (rwaParamDef *)tables->inputs;
        for (i = tables->noInputs; i; i--)
        {
            param->type = type;
            param->typeIndex = 0;
            param->handler = sub_257AF0;
            sub_240B40(param);
            param++;
        }
    }
    else
    {
        param = (rwaParamDef *)tables->outputs;
        for (i = tables->noOutputs; i; i--)
        {
            param->type = type;
            param->typeIndex = 0;
            param->handler = sub_257AF0;
            sub_240B40(param);
            param++;
        }
    }
}

extern RwBool _rwaParamTypeHandleRefreshType(void *handle);
extern void *sub_257AF0(void *obj, RwUInt32 index, void *data);

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
            ((rwaParamTables *)def->interfaces)->inputs + noInputs * sizeof(rwaParamDef);

        return def;
    }

    for (i = 0; i < noInputs; i++)
    {
        rwaParamDef    *param = &inputs[i];

        if (!_rwaParamTypeHandleRefreshType(&param->type))
        {
            return NULL;
        }

        if (!param->handler)
        {
            param->handler = sub_257AF0;
        }
    }

    ((rwaParamTables *)def->interfaces)->inputs = (RwUInt8 *)inputs;
    ((rwaParamTables *)def->interfaces)->noInputs = noInputs;

    for (i = 0; i < noOutputs; i++)
    {
        rwaParamDef    *param = &outputs[i];

        if (!_rwaParamTypeHandleRefreshType(&param->type))
        {
            return NULL;
        }

        if (!param->handler)
        {
            param->handler = sub_257AF0;
        }
    }

    def->flags0C |= 1;
    ((rwaParamTables *)def->interfaces)->outputs = (RwUInt8 *)outputs;
    ((rwaParamTables *)def->interfaces)->noOutputs = noOutputs;

    return def;
}

extern RwUInt32 dword_5069A4;
extern RwUInt8 unk_42E6F8[];
extern rwaObjDef *dword_516C60;
extern rwaObjDef *sub_23DFB0(rwaObjDef *parent, RwUInt32 flags, rwaObjDef *def, void *tables,
                             void *list, RwUInt32 hint);

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
