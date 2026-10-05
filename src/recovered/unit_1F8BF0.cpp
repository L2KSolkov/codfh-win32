/*
 * The memory pools (game/pool.h): the counting pool, the heap pool made on
 * first use, and the block pools that run a heap in a block of their parent.
 */
#include "game/pool.h"

// Vtables (.rdata, PLAN M5): each in its own placement range (config/splits.txt).
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_7type_1F8BF0@@6B@ @ 0x003E7DFC
// match: ??_7type_3E7E0C@@6B@ @ 0x003E7E0C
// match: ??_7type_1F8E00@@6Btype_3E7E30@@@ @ 0x003E7E1C
// match: ??_7type_1F8E00@@6Btype_1F8BF0@@@ @ 0x003E7E20
// match: ??_7type_3E7E30@@6B@ @ 0x003E7E30
// match: __ehhandler$?sub_1F8CF0@@YAPAUtype_1F8BF0@@XZ>1>8 @ 0x0042143C
// match: __ehhandler$?sub_1F8CF0@@YAPAUtype_1F8BF0@@XZ>1 @ 0x00421444
// match: __ehhandler$??0type_1F8E00@@QAE@PAUtype_1F8BF0@@I@Z>1>8 @ 0x00421460
// match: __ehhandler$??0type_1F8E00@@QAE@PAUtype_1F8BF0@@I@Z>1 @ 0x00421468
// match: __ehhandler$??1type_1F8E00@@UAE@XZ>1>8 @ 0x00421484
// match: __ehhandler$??1type_1F8E00@@UAE@XZ>1 @ 0x00421494

// match: ?sub_1F8BF0@type_1F8BF0@@QAEPAXI@Z @ 0x001F8BF0

void *type_1F8BF0::sub_1F8BF0(RwUInt32 arg_0)
{
    POOL_CHECK(unk_04 >= 0);
    void *var_4 = vf_004(arg_0);
    if (var_4)
        ++unk_04;
    return var_4;
}

// match: ?sub_1F8C30@type_1F8BF0@@QAEXPAX@Z @ 0x001F8C30
void type_1F8BF0::sub_1F8C30(void *arg_0)
{
    if (arg_0)
    {
        POOL_CHECK(unk_04 > 0);
        --unk_04;
    }
    else
        return;
    vf_008(arg_0);
}

// match: ??0type_1F8BF0@@QAE@XZ @ 0x001F8C70
type_1F8BF0::type_1F8BF0()
{
    unk_04 = 0;
}

// match: ??_Gtype_1F8BF0@@UAEPAXI@Z @ 0x001F8CA0

// match: ??1type_1F8BF0@@UAE@XZ @ 0x001F8CD0
type_1F8BF0::~type_1F8BF0()
{
}

// match: ?sub_1F8CF0@@YAPAUtype_1F8BF0@@XZ @ 0x001F8CF0
// match: __ehhandler$?sub_1F8CF0@@YAPAUtype_1F8BF0@@XZ-0xE @ 0x00304AD0
// match: __ehhandler$?sub_1F8CF0@@YAPAUtype_1F8BF0@@XZ @ 0x00304ADE
type_1F8BF0 *sub_1F8CF0()
{
    static type_3E7E0C unk_50439C;

    return &unk_50439C;
}

// match: _$E2 @ 0x0030F040
// (The compiler's exit thunk for sub_1F8CF0's heap pool: it runs the pool's
// destructor.)

// match: ??_Gtype_3E7E0C@@UAEPAXI@Z @ 0x001F8D70
// match: ??1type_3E7E0C@@UAE@XZ @ 0x001F8DA0

// match: ?vf_004@type_3E7E0C@@UAEPAXI@Z @ 0x001F8DC0
void *type_3E7E0C::vf_004(RwUInt32 arg_0)
{
    return operator new(arg_0);
}

// match: ?vf_008@type_3E7E0C@@UAEXPAX@Z @ 0x001F8DE0
void type_3E7E0C::vf_008(void *arg_0)
{
    operator delete(arg_0);
}

// ?vf_00C@type_3E7E0C@@UAEXXZ (folded into 0x1E41C0)
void type_3E7E0C::vf_00C()
{
}

// match: ??0type_1F8E00@@QAE@PAUtype_1F8BF0@@I@Z @ 0x001F8E00
// match: __ehhandler$??0type_1F8E00@@QAE@PAUtype_1F8BF0@@I@Z-0x8 @ 0x00304AF0
// match: __ehhandler$??0type_1F8E00@@QAE@PAUtype_1F8BF0@@I@Z @ 0x00304AF8
type_1F8E00::type_1F8E00(type_1F8BF0 *arg_0, RwUInt32 arg_4)
    : type_3E7E30(arg_0->sub_1F8BF0(arg_4), arg_4), unk_1C(arg_0)
{
}

// match: ??_Gtype_3E7E30@@UAEPAXI@Z @ 0x001F8ED0

// match: ??_Gtype_1F8E00@@UAEPAXI@Z @ 0x001F8F00

// match: ??1type_1F8E00@@UAE@XZ @ 0x001F8F30
// match: __ehhandler$??1type_1F8E00@@UAE@XZ-0x2F @ 0x00304B10
// match: __ehhandler$??1type_1F8E00@@UAE@XZ @ 0x00304B3F
type_1F8E00::~type_1F8E00()
{
    if (unk_1C)
        unk_1C->sub_1F8C30(type_3E7E30::unk_04);
}

// match: ??1type_3E7E30@@UAE@XZ @ 0x001F8FD0

// match: ?vf_004@type_1F8E00@@UAEPAXI@Z @ 0x001F8FF0
void *type_1F8E00::vf_004(RwUInt32 arg_0)
{
    return heap_alloc(arg_0);
}

// match: ?vf_008@type_1F8E00@@UAEXPAX@Z @ 0x001F9040
void type_1F8E00::vf_008(void *arg_0)
{
    heap_free(arg_0);
}

// match: ??_Etype_1F8E00@@W7AEPAXI@Z @ 0x001F90D0

// match: ?vf_00C@type_1F8E00@@UAEXXZ @ 0x001F9090
void type_1F8E00::vf_00C()
{
    heap_reset();
}
