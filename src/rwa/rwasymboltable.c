/*
 * codfh-match: RenderWare Audio's symbol tables (rwasymboltable.h in the
 * library's PS2 header, docs/reference/rwacore_ps2.h): parameter types
 * listed by their link (+0x20). In the header's order: init (0x244630),
 * add (0x244650), remove (0x244690), find by UUID (0x2446D0), first
 * dependant (0x244720) and by index (0x244750).
 */
#include "rwa.h"
#include "rwaint.h"

#define rwaParamTypeFromLink(_link) ((RwaParamType *)((RwUInt8 *)(_link) - 0x20))

extern void sub_2421B0(void *mem);
extern RwaUniqueID *sub_240C30(RwaUniqueID *uniqueID);
extern RwInt32 RwaUUIDCompare(const RwaUUID *uuid1, const RwaUUID *uuid2);

// match: _sub_244600 @ 0x00244600
// sp-match: _sub_244600 @ 0x0015D380
void
sub_244600(RwaParamType *paramType)
{
    paramType->link.prev->next = paramType->link.next;
    paramType->link.next->prev = paramType->link.prev;
    sub_240C30(&paramType->uniqueID);
    sub_2421B0(paramType);
}

// match: _sub_244630 @ 0x00244630
// sp-match: _sub_244630 @ 0x0015D3B0
void
sub_244630(RwaSymbolTable *table)
{
    table->noParamTypes = 0;
    table->list.next = &table->list;
    table->list.prev = &table->list;
}

/* Return types: rwacore_ps2.h declares both symbol-table mutations as
 * RwaSymbolTable*. The image leaves table in EAX at 0x244682/0x2446C6. */
// match: _sub_244650 @ 0x00244650
// sp-match: _sub_244650 @ 0x0015D3D0
RwaSymbolTable *
sub_244650(RwaSymbolTable *table, RwaParamType *paramType)
{
    paramType->link.prev = NULL;
    paramType->link.next = NULL;
    paramType->link.next = table->list.next;
    paramType->link.prev = &table->list;
    table->list.next->prev = &paramType->link;
    table->list.next = &paramType->link;
    table->noParamTypes++;
    return table;
}

// match: _sub_244690 @ 0x00244690
// sp-match: _sub_244690 @ 0x0015D410
RwaSymbolTable *
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
    return table;
}

// match: _sub_2446D0 @ 0x002446D0
// sp-match: _sub_2446D0 @ 0x0015D450
RwaParamType *
sub_2446D0(RwaSymbolTable *table, const RwaUUID *uuid)
{
    rwaLink        *cur = table->list.next;
    RwaParamType   *paramType = rwaParamTypeFromLink(cur);

    while (RwaUUIDCompare(paramType->uniqueID.uuid, uuid))
    {
        cur = cur->next;
        if (cur == &table->list)
        {
            return NULL;
        }

        paramType = rwaParamTypeFromLink(cur);
    }

    return paramType;
}

// match: _sub_244720 @ 0x00244720
// sp-match: _sub_244720 @ 0x0015D4A0
RwaParamType *
sub_244720(RwaSymbolTable *table, RwaParamType *parent)
{
    rwaLink        *cur = table->list.next;
    RwaParamType   *paramType = rwaParamTypeFromLink(cur);

    while (paramType->paramType != parent)
    {
        cur = cur->next;
        if (cur == &table->list)
        {
            return NULL;
        }

        paramType = rwaParamTypeFromLink(cur);
    }

    return paramType;
}

// match: _sub_244750 @ 0x00244750
// sp-match: _sub_244750 @ 0x0015D4D0
RwaParamType *
sub_244750(RwaSymbolTable *table, RwInt32 index)
{
    rwaLink        *cur;
    RwaParamType   *paramType;
    RwInt32         i;

    if (index > table->noParamTypes || !table->noParamTypes)
    {
        return NULL;
    }

    cur = table->list.next;
    paramType = rwaParamTypeFromLink(cur);
    for (i = 0; i < index; i++)
    {
        cur = cur->next;
        if (cur == &table->list)
        {
            return NULL;
        }

        paramType = rwaParamTypeFromLink(cur);
    }

    return paramType;
}
