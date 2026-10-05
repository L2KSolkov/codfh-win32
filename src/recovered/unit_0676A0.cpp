// alfahash, a chained hash table of pointers (types/alfahash.h), named from
// the image's own string "alfahash::m_pool". The file's original name is
// not recovered (M1), so it is named for its start address.

#include "rw/ostypes.h"
#include "game/functions.h"
#include "types/alfahash.h"

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0BB@MHCOFHPO@alfahash?3?3m_pool?$AA@ @ 0x003D2774
// match: __ehhandler$??1alfahash@@QAE@XZ>1>8 @ 0x0041B4B4
// match: __ehhandler$??1alfahash@@QAE@XZ>1 @ 0x0041B4BC

// match: ??0alfahash@@QAE@XZ @ 0x000676A0

alfahash::alfahash()
{
    unk_30 = 0;
    unk_08 = 0;
    unk_0C = 0;
}

// match: ??1alfahash@@QAE@XZ @ 0x000676E0
// match: __ehhandler$??1alfahash@@QAE@XZ-0xB @ 0x002FF880
// match: __ehhandler$??1alfahash@@QAE@XZ @ 0x002FF88B
alfahash::~alfahash()
{
    sub_67780();
}

// match: ?sub_67730@alfahash@@QAEXHHP6AIPAX@ZP6A_N00@Z@Z @ 0x00067730
void alfahash::sub_67730(RwInt32 arg_0, RwInt32 arg_4, RwUInt32 (*arg_8)(void *),
                         bool (*arg_C)(void *, void *))
{
    unk_00 = arg_0;
    unk_04 = arg_4;
    unk_08 = arg_8;
    unk_0C = arg_C;
    sub_677C0(arg_0);
    sub_677F0(arg_4);
}

// match: ?sub_67780@alfahash@@QAEXXZ @ 0x00067780
void alfahash::sub_67780()
{
    if (unk_30 != 0)
        operator delete(unk_30);
    unk_30 = 0;
    m_pool.sub_16C4D0(0);
}

// match: ?sub_677C0@alfahash@@QAEXH@Z @ 0x000677C0
void alfahash::sub_677C0(RwInt32 arg_0)
{
    m_pool.sub_16C2C0(arg_0, 8, "alfahash::m_pool", 4, 0);
}

// match: ?sub_677F0@alfahash@@QAEXH@Z @ 0x000677F0
void alfahash::sub_677F0(RwInt32 arg_0)
{
    RwInt32 var_4;

    unk_30 = (alfahash_node **)RWSMalloc(arg_0 * 4, 0x34254);  // not an address: an allocation tag
    for (var_4 = 0; var_4 < arg_0; var_4++)
        unk_30[var_4] = 0;
}

// match: ?sub_67850@alfahash@@QAE_NPAX@Z @ 0x00067850
bool alfahash::sub_67850(void *arg_0)
{
    alfahash_node *local_8;
    RwUInt32 var_4;

    if (sub_67970(arg_0) == 0) {
        local_8 = sub_67A40(arg_0);
        var_4 = sub_67A10(arg_0);
        local_8->unk_04 = unk_30[var_4];
        unk_30[var_4] = local_8;
        return true;
    }
    return false;
}

// match: ?sub_678C0@alfahash@@QAEXPAX@Z @ 0x000678C0
void alfahash::sub_678C0(void *arg_0)
{
    alfahash_node *var_10;
    alfahash_node *ebp_C;
    alfahash_node *v8;
    RwUInt32 var_4;

    var_4 = sub_67A10(arg_0);
    v8 = sub_679C0(unk_30[var_4], arg_0);
    if (v8 != 0) {
        var_10 = unk_30[var_4];
        ebp_C = 0;
        while (var_10 != v8) {
            ebp_C = var_10;
            var_10 = var_10->unk_04;
        }
        if (ebp_C != 0)
            ebp_C->unk_04 = v8->unk_04;
        else
            unk_30[var_4] = v8->unk_04;
        sub_67A80(v8);
    }
}

// match: ?sub_67970@alfahash@@QAEPAXPAX@Z @ 0x00067970
void *alfahash::sub_67970(void *arg_0)
{
    alfahash_node *local_8;
    RwUInt32 var_4;

    var_4 = sub_67A10(arg_0);
    local_8 = sub_679C0(unk_30[var_4], arg_0);
    if (local_8 != 0)
        return local_8->unk_00;
    return 0;
}

// match: ?sub_679C0@alfahash@@QAEPAUalfahash_node@@PAU2@PAX@Z @ 0x000679C0
alfahash_node *alfahash::sub_679C0(alfahash_node *arg_0, void *arg_4)
{
    alfahash_node *var_4;

    for (var_4 = arg_0; var_4 != 0 && !unk_0C(var_4->unk_00, arg_4); var_4 = var_4->unk_04)
        ;
    return var_4;
}

// match: ?sub_67A10@alfahash@@QAEIPAX@Z @ 0x00067A10
RwUInt32 alfahash::sub_67A10(void *arg_0)
{
    RwUInt32 var_4;

    var_4 = unk_08(arg_0);
    var_4 = var_4 % unk_04;
    return var_4;
}

// match: ?sub_67A40@alfahash@@QAEPAUalfahash_node@@PAX@Z @ 0x00067A40
alfahash_node *alfahash::sub_67A40(void *arg_0)
{
    alfahash_node *var_4;

    var_4 = (alfahash_node *)m_pool.sub_16C5A0(0);
    var_4->unk_00 = arg_0;
    var_4->unk_04 = 0;
    return var_4;
}

// match: ?sub_67A80@alfahash@@QAEXPAUalfahash_node@@@Z @ 0x00067A80
void alfahash::sub_67A80(alfahash_node *arg_0)
{
    m_pool.sub_16C710(arg_0);
}

// match: ?sub_67AA0@alfahash@@QAEXP6A_NPAX@Z@Z @ 0x00067AA0
void alfahash::sub_67AA0(bool (*arg_0)(void *))
{
    alfahash_node *varC;
    alfahash_node *local_8;
    RwInt32 var_4;

    for (var_4 = 0; var_4 < unk_04; var_4++) {
        varC = unk_30[var_4];
        while (varC != 0) {
            local_8 = varC->unk_04;
            if (!arg_0(varC->unk_00))
                return;
            varC = local_8;
        }
    }
}
