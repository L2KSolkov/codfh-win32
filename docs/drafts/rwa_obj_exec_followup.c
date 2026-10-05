// match: _sub_23F0D0 @ 0x0023F0D0
rwaInstance *
sub_23F0D0(rwaInstance *obj, RwBool ok)
{
    rwaInstance    *result = obj;
    rwaLink        *cur;
    RwBool          status;

    if (!ok)
    {
        if (obj->def->unk2C) status = obj->def->unk2C(obj);
        else status = (RwBool)obj;
        if (!status) result = NULL;
    }
    else status = (RwBool)obj;

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
sub_23F140(rwaInstance *obj, RwBool ok)
{
    rwaInstance    *result = obj;
    rwaLink        *cur;
    RwBool          status;

    if (!ok)
    {
        if (obj->def->unk30) status = obj->def->unk30(obj);
        else status = (RwBool)obj;
        if (!status) result = NULL;
    }
    else status = (RwBool)obj;

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

