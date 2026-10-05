// The intrusive lists (type_16B810: a head, a sentinel's link and a tail)
// and their iterator (type_16B900), whose nodes (type_6FCD0) link through
// their first two words; the animated textures (unit_143CE0) use them.

#include "rw/ostypes.h"
#include "types/type_143DC0.h"

// match: ??0type_16B810@@QAE@XZ @ 0x0016B810
type_16B810::type_16B810()
{
    sub_16B830();
}

// match: ?sub_16B830@type_16B810@@QAEXXZ @ 0x0016B830
// Empties it: the head points at the sentinel's link (0), the tail at the
// list itself.
void type_16B810::sub_16B830()
{
    unk_00 = &unk_04;
    unk_04 = 0;
    unk_08 = this;
}

// match: ?sub_16B860@type_16B810@@QAEXPAUtype_6FCD0@@@Z @ 0x0016B860
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Links arg_0 in at the head.
void type_16B810::sub_16B860(type_6FCD0 *arg_0)
{
    type_6FCD0 *var_8;
    void *l4;

    l4 = unk_00;
    arg_0->unk_00 = l4;
    unk_00 = arg_0;
    arg_0->unk_04 = this;
    var_8 = (type_6FCD0 *)arg_0->unk_00;
    var_8->unk_04 = arg_0;
}

// match: ?sub_16B8B0@type_16B810@@QAEXPAUtype_6FCD0@@@Z @ 0x0016B8B0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Links arg_0 in at the tail.
void type_16B810::sub_16B8B0(type_6FCD0 *arg_0)
{
    type_6FCD0 *var_8;
    void *l4;

    arg_0->unk_00 = &unk_04;
    l4 = unk_08;
    arg_0->unk_04 = l4;
    unk_08 = arg_0;
    var_8 = (type_6FCD0 *)arg_0->unk_04;
    var_8->unk_00 = arg_0;
}

// match: ??0type_16B900@@QAE@PAUtype_16B810@@@Z @ 0x0016B900
type_16B900::type_16B900(type_16B810 *arg_0)
{
    type_6FCD0 *var_4;

    unk_00 = arg_0;
    var_4 = (type_6FCD0 *)unk_00->unk_00;
    unk_04 = var_4;
}

// match: ?sub_16B930@type_16B900@@QAEPAUtype_6FCD0@@XZ @ 0x0016B930
type_6FCD0 *type_16B900::sub_16B930()
{
    type_6FCD0 *var_4;

    var_4 = (type_6FCD0 *)unk_04->unk_00;
    unk_04 = var_4;
    return unk_04;
}

// match: ?sub_16B960@type_16B900@@QAEPAUtype_6FCD0@@XZ @ 0x0016B960
type_6FCD0 *type_16B900::sub_16B960()
{
    type_6FCD0 *var_4;

    var_4 = (type_6FCD0 *)unk_04->unk_04;
    unk_04 = var_4;
    return unk_04;
}

// match: ?sub_16B990@type_16B900@@QAEPAUtype_6FCD0@@XZ @ 0x0016B990
// Unlinks the current node (stepping back first) and returns it; 0 at an
// end.
type_6FCD0 *type_16B900::sub_16B990()
{
    type_6FCD0 *var_4 = 0;

    if (sub_16B9D0())
    {
        var_4 = unk_04;
        sub_16B960();
        var_4->sub_16BA30();
    }
    return var_4;
}

// match: ?sub_16B9D0@type_16B900@@QAE_NXZ @ 0x0016B9D0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Whether it is on a node (not the head's or the sentinel's link).
bool type_16B900::sub_16B9D0()
{
    void *var_8;
    void *l4;

    l4 = unk_04->unk_00;
    if (!l4)
        return false;
    var_8 = unk_04->unk_04;
    if (!var_8)
        return false;
    return true;
}

// match: ?sub_16BA10@type_16B900@@QAEXH@Z @ 0x0016BA10
// Its postfix step (the argument is operator++'s dummy).
void type_16B900::sub_16BA10(RwInt32 arg_0)
{
    sub_16B930();
}

// match: ?sub_16BA30@type_6FCD0@@QAEXXZ @ 0x0016BA30
void type_6FCD0::sub_16BA30()
{
    ((type_6FCD0 *)unk_00)->unk_04 = unk_04;
    ((type_6FCD0 *)unk_04)->unk_00 = unk_00;
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??0type_6FCD0@@QAE@XZ (folded into 0x6FCD0)
type_6FCD0::type_6FCD0()
{
    
}

// ??1type_16B810@@QAE@XZ (folded into 0x1E41C0)
type_16B810::~type_16B810()
{
}

// ??1type_16B900@@QAE@XZ (folded into 0x1E41C0)
type_16B900::~type_16B900()
{
}

// ??1type_6FCD0@@QAE@XZ (folded into 0x1E41C0)
type_6FCD0::~type_6FCD0()
{
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?sub_1E3480@type_16B900@@QAEPAUtype_6FCD0@@XZ (folded into 0x1E3480)
struct type_6FCD0 * type_16B900::sub_1E3480()
{
    return unk_04;
}
