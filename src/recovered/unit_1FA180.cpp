// The pooled list (game/poollist.h): its nodes, its free list and its
// operations.

#include <new>

#include "game/poollist.h"


// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: __ehhandler$?sub_1FA180@@YAPAUtype_1FA180_node@@PAUtype_1F8BF0@@PAU1@1H@Z>1>8 @ 0x004214B0
// match: __ehhandler$?sub_1FA180@@YAPAUtype_1FA180_node@@PAUtype_1F8BF0@@PAU1@1H@Z>1 @ 0x004214B8

// match: ?sub_1FA180@@YAPAUtype_1FA180_node@@PAUtype_1F8BF0@@PAU1@1H@Z @ 0x001FA180
// match: __ehhandler$?sub_1FA180@@YAPAUtype_1FA180_node@@PAUtype_1F8BF0@@PAU1@1H@Z-0x11 @ 0x00304B50
// match: __ehhandler$?sub_1FA180@@YAPAUtype_1FA180_node@@PAUtype_1F8BF0@@PAU1@1H@Z @ 0x00304B61

type_1FA180_node *sub_1FA180(type_1F8BF0 *arg_0, type_1FA180_node *arg_4, type_1FA180_node *arg_8,
                             RwInt32 arg_C)
{
    void *p = 0;

    p = arg_0->sub_1F8BF0(arg_C + sizeof(type_1FA180_node));
    if (!p)
        return 0;
    return new (p) type_1FA180_node(arg_4, arg_8);
}

// match: ?sub_1FA210@@YAXPAUtype_1F8BF0@@PAUtype_1FA180_node@@@Z @ 0x001FA210
void sub_1FA210(type_1F8BF0 *arg_0, type_1FA180_node *arg_4)
{
    arg_0->sub_1F8C30(arg_4);
}

// match: ??0type_1FA230@@QAE@PAUtype_1F8BF0@@@Z @ 0x001FA230
type_1FA230::type_1FA230(type_1F8BF0 *arg_0)
{
    unk_00 = 0;
    unk_04 = 0;
    unk_08 = 0;
    unk_0C = 0;
    unk_10 = 0;
    unk_14 = arg_0;
}

// match: ??1type_1FA230@@QAE@XZ @ 0x001FA280
type_1FA230::~type_1FA230()
{
    sub_1FA2A0();
    sub_1FA640();
}

// match: ?sub_1FA2A0@type_1FA230@@QAEXXZ @ 0x001FA2A0
void type_1FA230::sub_1FA2A0()
{
    type_1FA180_node *n;

    unk_08 = unk_00;
    while (unk_08)
    {
        n = unk_08;
        unk_08 = unk_08->unk_04;
        sub_1FA5D0(n);
    }
    unk_10 = 0;
    unk_04 = 0;
    unk_00 = 0;
    unk_08 = 0;
}

// match: ?sub_1FA310@type_1FA230@@QAEPAXH@Z @ 0x001FA310
void *type_1FA230::sub_1FA310(RwInt32 arg_0)
{
    type_1FA180_node *n;

    n = sub_1FA690(unk_04, 0, arg_0);
    if (!n)
        return 0;
    unk_04 = n;
    if (unk_04->unk_00)
        unk_04->unk_00->unk_04 = unk_04;
    if (!unk_10++)
        unk_00 = unk_04;
    return unk_04 + 1;
}

// match: ?sub_1FA3A0@type_1FA230@@QAEXXZ @ 0x001FA3A0
void type_1FA230::sub_1FA3A0()
{
    type_1FA180_node *n;

    if (unk_08 == unk_00)
        unk_08 = 0;
    n = unk_00->unk_04;
    sub_1FA5D0(unk_00);
    unk_00 = n;
    if (unk_00)
        unk_00->unk_00 = 0;
    // A compiled-out check (docs/toolchain.md): the registers after it are
    // one load on.
    if (!unk_10)
    {
    }
    unk_10 = unk_10 - 1;
    if (!unk_10)
        unk_04 = 0;
}

// match: ?sub_1FA420@type_1FA230@@QAEXXZ @ 0x001FA420
void type_1FA230::sub_1FA420()
{
    type_1FA180_node *n;

    if (unk_08 == unk_04)
        unk_08 = 0;
    n = unk_04->unk_00;
    sub_1FA5D0(unk_04);
    unk_04 = n;
    if (unk_04)
        unk_04->unk_04 = 0;
    // A compiled-out check (docs/toolchain.md): the registers after it are
    // one load on.
    if (!unk_10)
    {
    }
    unk_10 = unk_10 - 1;
    if (!unk_10)
        unk_00 = 0;
}

// match: ?sub_1FA4A0@type_1FA230@@QAEPAXXZ @ 0x001FA4A0
void *type_1FA230::sub_1FA4A0()
{
    type_1FA180_node *prev;
    type_1FA180_node *next;

    // Two compiled-out checks (docs/toolchain.md): the registers after them
    // are two loads on.
    if (!unk_10)
    {
    }
    if (!unk_10)
    {
    }
    if (unk_08)
    {
        next = unk_08->unk_04;
        if (unk_08 == unk_00)
        {
            sub_1FA3A0();
            if (next)
            {
                unk_08 = next;
                return unk_08 + 1;
            }
            return 0;
        }
        if (unk_08 == unk_04)
        {
            sub_1FA420();
            return 0;
        }
        prev = unk_08->unk_00;
        sub_1FA5D0(unk_08);
        if (next)
            next->unk_00 = prev;
        if (prev)
            prev->unk_04 = next;
        unk_10 = unk_10 - 1;
        unk_08 = next;
        return unk_08 ? unk_08 + 1 : 0;
    }
    return 0;
}

// match: ?sub_1FA590@type_1FA230@@QAEHXZ @ 0x001FA590
RwInt32 type_1FA230::sub_1FA590()
{
    return unk_08 != 0;
}

// match: ?sub_1FA5B0@type_1FA230@@QAEXXZ @ 0x001FA5B0
void type_1FA230::sub_1FA5B0()
{
    sub_1FA640();
}

// match: ?sub_1FA5D0@type_1FA230@@QAEXPAUtype_1FA180_node@@@Z @ 0x001FA5D0
void type_1FA230::sub_1FA5D0(type_1FA180_node *arg_0)
{
    arg_0->unk_04 = unk_0C;
    arg_0->unk_00 = 0;
    unk_0C = arg_0;
}

// match: ?sub_1FA600@type_1FA230@@QAEPAUtype_1FA180_node@@PAU2@0@Z @ 0x001FA600
type_1FA180_node *type_1FA230::sub_1FA600(type_1FA180_node *arg_0, type_1FA180_node *arg_4)
{
    type_1FA180_node *n;

    n = unk_0C;
    unk_0C = unk_0C->unk_04;
    n->unk_04 = arg_4;
    n->unk_00 = arg_0;
    return n;
}

// match: ?sub_1FA640@type_1FA230@@QAEXXZ @ 0x001FA640
void type_1FA230::sub_1FA640()
{
    type_1FA180_node *n;
    type_1FA180_node *d;

    n = unk_0C;
    while (n)
    {
        d = n;
        n = n->unk_04;
        sub_1FA210(unk_14, d);
    }
    unk_0C = 0;
}

// match: ?sub_1FA690@type_1FA230@@QAEPAUtype_1FA180_node@@PAU2@0H@Z @ 0x001FA690
type_1FA180_node *type_1FA230::sub_1FA690(type_1FA180_node *arg_0, type_1FA180_node *arg_4, RwInt32 arg_8)
{
    if (unk_0C)
        return sub_1FA600(arg_0, arg_4);
    return sub_1FA180(unk_14, arg_0, arg_4, arg_8);
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?sub_191D80@type_1FA230@@QAEHXZ (folded into 0x191D80)
RwInt32 type_1FA230::sub_191D80()
{
    return unk_10;
}

// The node's constructor (its two links): the body /OPT:ICF shares with the
// arrays' iterators' constructors (0x1EFD70); defined here for the authentic
// link (PLAN M7).
// ??0type_1FA180_node@@QAE@PAU0@0@Z (folded into 0x1EFD70)
type_1FA180_node::type_1FA180_node(type_1FA180_node *arg_0, type_1FA180_node *arg_4)
{
    unk_00 = arg_0;
    unk_04 = arg_4;
}
