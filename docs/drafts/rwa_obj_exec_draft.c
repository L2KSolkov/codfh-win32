// match: _sub_23F0D0 @ 0x0023F0D0
rwaInstance *
sub_23F0D0(rwaInstance *obj, RwBool ok)
{
    rwaInstance    *result = obj;
    rwaLink        *cur;
    RwBool          status;

    if (ok)
    {
        status = ok;
    }
    else
    {
        if (obj->def->unk2C)
        {
            status = obj->def->unk2C(obj);
        }
        else
        {
            status = ok;
        }

        if (!status)
        {
            result = NULL;
        }
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
sub_23F140(rwaInstance *obj, RwBool ok)
{
    rwaInstance    *result = obj;
    rwaLink        *cur;

    if (!ok)
    {
        if (obj->def->unk30)
        {
            ok = obj->def->unk30(obj);
        }

        if (!ok)
        {
            result = NULL;
        }
    }

    cur = obj->subObjs.next;
    while (cur != &obj->subObjs)
    {
        rwaInstance    *sub = rwaInstFromSubLink(cur);

        cur = cur->next;
        if (sub->def->unk30)
        {
            ok = sub->def->unk30(sub);
        }

        if (!ok)
        {
            result = NULL;
        }
    }

    return result;
}

