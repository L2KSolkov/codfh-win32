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

/* Qualified pointer reads preserve the loads before each count test.
 * Original qualifiers are unknown. This helper and 23DB30 match only
 * with the still-unmatched 23DB90 caller supplying their register ABI. */
// match: _sub_23DAA0 @ 0x0023DAA0
static rwaObjDef *
sub_23DAA0(rwaObjDef *def)
{
    if (def->flags0C & 4)
    {
        { rwaParamTables *tables = (rwaParamTables *)def->interfaces;
          rwaParamDef *param = *(rwaParamDef *volatile *)&tables->inputs;
          RwUInt16 count = tables->noInputs;
          if (count > 0) {
            RwUInt32 i;
            param += count;
            i = count;
            do { --param; sub_240C30(param); } while (--i > 0);
          }
        }
        { rwaParamTables *tables = (rwaParamTables *)def->interfaces;
          rwaParamDef *param = *(rwaParamDef *volatile *)&tables->outputs;
          RwUInt16 count = tables->noOutputs;
          if (count > 0) {
            RwUInt32 i;
            param += count;
            i = count;
            do { --param; sub_240C30(param); } while (--i > 0);
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

