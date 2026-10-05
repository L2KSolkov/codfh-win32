// match: _sub_244650 @ 0x00244650
void
sub_244650(RwaSymbolTable *table, RwaParamType *paramType)
{
    paramType->link.prev = NULL;
    paramType->link.next = NULL;
    paramType->link.next = table->list.next;
    paramType->link.prev = &table->list;
    table->list.next->prev = &paramType->link;
    table->list.next = &paramType->link;
    table->noParamTypes++;
}

// match: _sub_244690 @ 0x00244690
void
sub_244690(RwaSymbolTable *table, RwaParamType *paramType)
{
    rwaLink    *cur;

    for (cur = table->list.next; cur != &table->list; cur = cur->next)
    {
        if (rwaParamTypeFromLink(cur) == paramType)
        {
            break;
        }
    }

    table->noParamTypes--;
    paramType->link.prev->next = paramType->link.next;
    paramType->link.next->prev = paramType->link.prev;
}

