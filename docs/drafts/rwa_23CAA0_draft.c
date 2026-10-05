extern void sub_242510(void *item);
extern void sub_2435D0(rwaLink *list);

// match: _sub_23CAA0 @ 0x0023CAA0
void
sub_23CAA0(rwaWaveDict *dict)
{
    dict->link.prev->next = dict->link.next;
    dict->link.next->prev = dict->link.prev;

    if (dict == dword_506844)
    {
        dword_506844 = dword_506840;
    }

    if ((dict->type & 0x40) && (dict->unk28 || (dict->flags & 1)))
    {
        sub_23C700(dict);
    }

    if (dict->type & 0x20)
    {
        return;
    }

    if (dict->type & 0x10)
    {
        sub_2422A0(dict->data);

        return;
    }

    {
        rwaWaveNode    *node;

        for (node = (rwaWaveNode *)dict->waves.prev;
             node != (rwaWaveNode *)&dict->waves;
             node = node->next)
        {
            void       *item = node->item;
            rwaLink    *cur;

            for (cur = dword_516CA8.next; cur != &dword_516CA8; cur = cur->next)
            {
                if (sub_23C880(rwaDictFromLink(cur), item))
                {
                    break;
                }
            }

            if (cur == &dword_516CA8)
            {
                sub_242510(item);
            }
        }
    }

    sub_2435D0(&dict->waves);
    sub_23C970(dict);
}


extern void sub_240C30(rwaWaveDict *dict);
extern void sub_2437A0(void *freeList, rwaWaveDict *dict);

// match: _sub_23C970 @ 0x0023C970
static void
sub_23C970(rwaWaveDict *dict)
{
    sub_240C30(dict);

    if (dict->type & 1)
    {
        sub_2437A0(unk_516C80, dict);
    }
    else if (!(dict->type & 4))
    {
        sub_2421B0((rwaVoiceState *)dict);
    }
}

