/* Matched definition-creation group, 2026-10-02.
 * Uses rwaObjDef's packed state-size/alignment fields at +0x40.
 * 23DAA0's qualified pointer reads retain the original load order;
 * its original declaration qualifiers are unknown.
 * Keep this group together when probing the static register calling ABI.
 */
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
                param->handler = sub_257AF0;
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
                param->handler = sub_257AF0;
                sub_240B40(param);
            }
        }
    }
}

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
