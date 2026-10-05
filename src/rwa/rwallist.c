/*
 * codfh-match: RenderWare Audio's linked lists (0x243490-0x243670, after
 * the database's _rwaLListModuleOpen): RwaLLNode lists whose head is a
 * node, with nodes allocated per entry.
 */
#include "rwa.h"
#include "rwaint.h"

static RwUInt8 unk_516C20[0x24];    /* nodes */
static RwUInt32 dword_50702C;

extern void *sub_242170(RwUInt32 size, RwUInt32 hint);
extern void sub_2421B0(void *mem);
extern void sub_2438E0(void *freeList);
extern void *sub_243950(RwUInt32 size, RwUInt32 count, RwUInt32 align, RwInt32 a,
                        void *freeList, RwUInt32 hint);

// match: __rwaLListModuleOpen @ 0x00243490
RwBool
_rwaLListModuleOpen(void)
{
    if (sub_243950(sizeof(RwaLLNode), 0x20, 0, 0, unk_516C20, rwaMEMHINTDUR_GLOBAL | rwaID_804))
    {
        dword_50702C = TRUE;

        return TRUE;
    }

    return FALSE;
}

// match: _sub_2434C0 @ 0x002434C0
void
sub_2434C0(void)
{
    sub_2438E0(unk_516C20);
    dword_50702C = 0;
}

// match: _sub_2434E0 @ 0x002434E0
RwaLLNode *
sub_2434E0(RwaLLNode *list, void *data)
{
    RwaLLNode  *node = (RwaLLNode *)sub_242170(sizeof(RwaLLNode), rwaMEMHINTDUR_EVENT | rwaID_804);

    if (!node)
    {
        return NULL;
    }

    node->data = data;
    node->prev = list->prev;
    node->next = list;
    list->prev->next = node;
    list->prev = node;

    return node;
}

// match: _sub_243510 @ 0x00243510
RwaLLNode *
sub_243510(RwaLLNode *list, RwUInt32 index)
{
    RwaLLNode  *node = list->next;
    RwUInt32    i;

    for (i = 0; i != index; )
    {
        node = node->next;
        i++;
        if (node == list)
        {
            return NULL;
        }
    }

    return node;
}

// match: _sub_243540 @ 0x00243540
RwInt32
sub_243540(RwaLLNode *list, void *data)
{
    RwaLLNode  *node;
    RwInt32     index = 0;

    for (node = list->next; node != list; node = node->next)
    {
        if (node->data == data)
        {
            return index;
        }

        index++;
    }

    return -1;
}

// match: _sub_243570 @ 0x00243570
void *
sub_243570(RwaLLNode *list, RwUInt32 index)
{
    RwaLLNode  *node = sub_243510(list, index);

    return node ? node->data : NULL;
}

// match: _sub_243590 @ 0x00243590
void
sub_243590(RwaLLNode *list, RwaLLNode *node)
{
    RwaLLNode  *cur;

    for (cur = list->next; cur != node && cur != list; cur = cur->next)
    {
    }

    node->prev->next = node->next;
    node->next->prev = node->prev;
    sub_2421B0(node);
}

// match: _sub_2435D0 @ 0x002435D0
void
sub_2435D0(RwaLLNode *list)
{
    while (list->next != list)
    {
        sub_243590(list, list->next);
    }
}

// match: _sub_243600 @ 0x00243600
RwUInt32
sub_243600(RwaLLNode *list, void *(*callback)(RwaLLNode *node, void *data), void *data)
{
    RwaLLNode  *node;
    RwUInt32    count = 0;

    for (node = list->prev; node != list; node = node->prev)
    {
        if (callback)
        {
            if (callback(node, data))
            {
                count++;
            }
        }
        else
        {
            count++;
        }
    }

    return count;
}

// match: _sub_243640 @ 0x00243640
RwaLLNode *
sub_243640(RwaLLNode *list, void *data)
{
    RwaLLNode  *node = list->next;

    while (data != node->data)
    {
        if (node == list)
        {
            return NULL;
        }

        node = node->next;
    }

    sub_243590(list, node);

    return list;
}
