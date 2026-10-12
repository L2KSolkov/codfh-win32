// CAnimObjectPool: the pools of animation players (the class name is in its
// own warning). The file's original name is not recovered (M1), so it is
// named for its start address.

#include "rw/ostypes.h"
#include "game/functions.h"
#include "types/animobjpool.h"
#include "types/animbank.h"
#include "types/type_3D3548.h"
#include "rw/rtquat.h"
#include "rw/rpskin.h"
#include "game/clumpdata.h"
#include "rw/bavector.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003D3C58
extern const RwReal flt_3D3C58 = 16.666666f;
// 0x0044A580
void (*dword_44A580[8])(type_7C8D0 *, type_80300 *, RwInt32, bool);
// 0x0044A5A0
type_44A5A0 dword_44A5A0[4];
// 0x0044A5C0
RwInt32 dword_44A5C0;
// End of its data definitions.


// Vtables (.rdata, PLAN M5): each in its own placement range (config/splits.txt).
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3D3C58@@3MB @ 0x003D3C58
// match: ??_C@_0BE@HIOIHIHA@animobjpool?3?3m_pool?$AA@ @ 0x003D3C5C
// match: ??_C@_0EA@IJEMBDKK@CAnimObjectPool?3?3?5Somebody?5forgo@ @ 0x003D3C70
// match: __ehhandler$??1CAnimObjectPool@@QAE@XZ>1>8 @ 0x0041B6B8
// match: __ehhandler$??1CAnimObjectPool@@QAE@XZ>1 @ 0x0041B6C0
// match: __ehhandler$??0CAnimObjectPool@@QAE@XZ>1>8 @ 0x0041B6DC
// match: __ehhandler$??0CAnimObjectPool@@QAE@XZ>1 @ 0x0041B6E4

// match: ??0CAnimObjectPool@@QAE@XZ @ 0x00078AF0
// match: __ehhandler$??0CAnimObjectPool@@QAE@XZ-8 @ 0x002FF9F0
// match: __ehhandler$??0CAnimObjectPool@@QAE@XZ @ 0x002FF9F8
// sp-match: ??0CAnimObjectPool@@QAE@XZ @ 0x00063360

CAnimObjectPool::CAnimObjectPool()
{
    sub_78B90();
}

// match: ??1CAnimObjectPool@@QAE@XZ @ 0x00078B40
// sp-match: ??1CAnimObjectPool@@QAE@XZ @ 0x00063380
CAnimObjectPool::~CAnimObjectPool()
{
    sub_78B90();
}

// match: ?sub_78B90@CAnimObjectPool@@QAEXXZ @ 0x00078B90
// sp-match: ?sub_78B90@CAnimObjectPool@@QAEXXZ @ 0x00063060
void CAnimObjectPool::sub_78B90()
{
    unk_20 = 0;
    unk_24 = 0;
}

// match: ?sub_78BB0@CAnimObjectPool@@QAEHHHH@Z @ 0x00078BB0
// sp-match: ?sub_78BB0@CAnimObjectPool@@QAEHHHH@Z @ 0x00063070
RwInt32 CAnimObjectPool::sub_78BB0(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    sub_78B90();
    unk_20 = arg_0;
    unk_24 = arg_4;
#ifdef CODFH_SP
    // Single player's anim objects are 0x80 bytes smaller (SP 0x63093: 0x140).
    m_pool.sub_16C2C0(arg_8, arg_4 * 0x2C + 0x140, "animobjpool::m_pool", 16, 0);
#else
    m_pool.sub_16C2C0(arg_8, arg_4 * 0x2C + 0x1C0, "animobjpool::m_pool", 16, 0);
#endif
    return 1;
}

// match: ?sub_78C00@CAnimObjectPool@@QAEXXZ @ 0x00078C00
void CAnimObjectPool::sub_78C00()
{
    if (m_pool.in_use()) {
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
        // Single player compiles the warning out (its text is not in default.xbe; sub_78790's
        // call goes to an empty function, SP 0x63215).
        sub_19A750("CAnimObjectPool:: Somebody forgot to deallocate an anim object!");
#endif
    }
}

// match: ?sub_78C30@CAnimObjectPool@@QAEXXZ @ 0x00078C30
// sp-match: ?sub_78C30@CAnimObjectPool@@QAEXXZ @ 0x000630B0
void CAnimObjectPool::sub_78C30()
{
    sub_78B90();
    m_pool.sub_16C4D0(1);
}

// match: ?sub_78C50@CAnimObjectPool@@QAEPAUtype_7C8D0@@XZ @ 0x00078C50
// sp-match: ?sub_78C50@CAnimObjectPool@@QAEPAUtype_7C8D0@@XZ @ 0x000630C0
type_7C8D0 *CAnimObjectPool::sub_78C50()
{
    type_7C8D0 *var_4;

    var_4 = (type_7C8D0 *)m_pool.sub_16C5A0(0);
    if (var_4 != 0) {
        new (var_4) type_7C8D0(unk_24);
        var_4->unk_10 = (RwInt16)get_unk_20();
    }
    return var_4;
}

// match: ?sub_78CC0@CAnimObjectPool@@QAEXPAUtype_7C8D0@@@Z @ 0x00078CC0
// sp-match: ?sub_78CC0@CAnimObjectPool@@QAEXPAUtype_7C8D0@@@Z @ 0x00063100
void CAnimObjectPool::sub_78CC0(type_7C8D0 *arg_0)
{
    delete arg_0;
    m_pool.sub_16C710(arg_0);
}

// match: ?sub_78D10@@YAXHPAXPAUtype_3D3548@@PAUtype_7C8D0_30@@PAUtype_7C8D0@@@Z @ 0x00078D10
// sp-match: ?sub_78D10@@YAXHPAXPAUtype_3D3548@@PAUtype_7C8D0_30@@PAUtype_7C8D0@@@Z @ 0x00063130
void sub_78D10(RwInt32 arg_0, void *arg_4, type_3D3548 *arg_8, type_7C8D0_30 *arg_C,
               type_7C8D0 *arg_10)
{
    RwInt32 local_8;
    type_3D3548 *var_4;

    local_8 = 0;
    if (arg_C != 0)
        local_8 = arg_C->unk_08;
    var_4 = arg_8;
    var_4->vf_170(arg_0, (RwInt32)arg_4, local_8, (RwInt32)arg_10);
}












// Called with the heading sub_79D50 turns to; the call's float argument is
// all that is known: its body, returning 0, is shared by /OPT:ICF with
// sub_170ED0 (defined beside it in unit_16FF90; the result is unused here).
RwInt32 sub_170ED0(RwReal arg_0);






















// Members /OPT:ICF folded into shared trivial bodies (config/aliases.txt): defined here for
// the authentic link (PLAN M7); the placement link takes the shared bodies.

// ??3type_7C8D0@@SAXPAX@Z (folded into the empty debug print at 0x19A750)
// Single player defines it in unit_078D60, whose deleting destructor drops the call.
#ifndef CODFH_SP
void type_7C8D0::operator delete(void *arg_0)
{
}
#endif

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??2type_7C8D0@@SAPAXIPAX@Z (folded into 0x6CCF0)
void *type_7C8D0::operator new(RwUInt32 arg_0, void *arg_4)
{
    return arg_4;
}
