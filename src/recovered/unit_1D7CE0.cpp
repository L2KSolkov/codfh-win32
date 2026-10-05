/*
 * cXboxLive's file (its traces name cXboxLive:: functions): the system link
 * host search, CSystemLinkQuery, first.
 */
#include <string.h>

#include "game/systemlink.h"
#include "types/cXboxLive.h"
#include "game/gameloop.h"
#include "types/cXboxLiveNetGame.h"

extern void (*off_42CD14)(const RwChar *arg_0, ...);

// Its data definitions (PLAN M5), in the image's address order.

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0DP@BKCPBNFA@CSystemLinkQuery?3?3Query?$CI?$CJ?5?3?5fail@ @ 0x003E52A4

// match: ??0CSystemLinkQuery@@QAE@XZ @ 0x001D7CE0

CSystemLinkQuery::CSystemLinkQuery() : unk_F0C(0)
{
    unk_103C = 0;
    unk_104C = 0;
    unk_1050 = S_FALSE;
}

// match: ??1CSystemLinkQuery@@QAE@XZ @ 0x001D7D40
CSystemLinkQuery::~CSystemLinkQuery()
{
    sub_1D7D60();
}

// match: ?sub_1D7D60@CSystemLinkQuery@@QAEXXZ @ 0x001D7D60
void CSystemLinkQuery::sub_1D7D60()
{
    switch (unk_104C)
    {
    case 1:
    case 2:
        sub_1D7DB0();
        unk_104C = 0;
        unk_1050 = S_FALSE;
        break;
    }
}

// match: ?sub_1D7DB0@CSystemLinkQuery@@QAEXXZ @ 0x001D7DB0
void CSystemLinkQuery::sub_1D7DB0()
{
    unk_F0C = 0;
}

// match: ?Query@CSystemLinkQuery@@QAEJPAUcXboxSocket@@_J1111@Z @ 0x001D7DD0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
HRESULT CSystemLinkQuery::Query(cXboxSocket *arg_0, LONGLONG arg_4, LONGLONG arg_C, LONGLONG arg_14,
                                LONGLONG arg_1C, LONGLONG arg_24)
{
    INT var_74;
    type_1D7DD0_probe var70;
    RwInt32 var_8;
    RwInt32 l4;

    // A compiled-out check (docs/toolchain.md).
    if (!unk_104C)
    {
    }
    unk_103C = arg_0;
    if (unk_104C == 2)
    {
        sub_1D7DB0();
        unk_104C = 0;
    }
    if (unk_104C != 0)
        return E_UNEXPECTED;
    unk_1040 = sub_1CCA10();
    if (!unk_103C->is_open() && !unk_103C->create(2))
    {
        if (0)
            off_42CD14("CSystemLinkQuery::Query() : failed to create broadcast socket\n");
        return S_OK;
    }
    var70.unk_00[0] = 0xFF;
    var70.unk_00[1] = 0xFF;
    var_74 = XNetRandom(var70.unk_02, 8);
    for (l4 = 0; l4 < 8; l4++)
        unk_1044[l4] = var70.unk_02[l4];
    arg_4 = 0xFFFFFFFF;
    arg_C = 0xFFFFFFFF;
    arg_14 = 0xFFFFFFFF;
    arg_1C = 0xFFFFFFFF;
    var70.unk_10[0].dwAttributeID = arg_4 == MAXLONGLONG ? X_ATTRIBUTE_DATATYPE_NULL : 0;
    var70.unk_10[0].info.integer.qwValue = arg_4;
    var70.unk_10[1].dwAttributeID = arg_C == MAXLONGLONG ? X_ATTRIBUTE_DATATYPE_NULL : 0;
    var70.unk_10[1].info.integer.qwValue = arg_C;
    var70.unk_10[2].dwAttributeID = arg_14 == MAXLONGLONG ? X_ATTRIBUTE_DATATYPE_NULL : 0;
    var70.unk_10[2].info.integer.qwValue = arg_14;
    var70.unk_10[3].dwAttributeID = arg_1C == MAXLONGLONG ? X_ATTRIBUTE_DATATYPE_NULL : 0;
    var70.unk_10[3].info.integer.qwValue = arg_1C;
    var70.unk_10[4].dwAttributeID = arg_24 == MAXLONGLONG ? X_ATTRIBUTE_DATATYPE_NULL : 0;
    var70.unk_10[4].info.integer.qwValue = arg_24;
    var_8 = unk_103C->broadcast((const RwChar *)&var70, 0x60);
    if (var_8)
    {
        unk_104C = 1;
        return S_OK;
    }
    return S_FALSE;
}

// match: ?sub_1D8060@CSystemLinkQuery@@QAEJXZ @ 0x001D8060
HRESULT CSystemLinkQuery::sub_1D8060()
{
    if (!unk_104C)
        return S_OK;
    if (unk_104C == 1)
    {
        type_1CCA10 local_8 = sub_1CCA10();
        RwInt32 var_4 = local_8 - unk_1040;

        if ((RwReal)var_4 * 0.001f > 0.5f)
            unk_104C = 2;
    }
    if (unk_104C == 2)
        return XONLINETASK_S_SUCCESS;
    return S_OK;
}

// match: ?sub_1D80F0@CSystemLinkQuery@@QAEJPBEHH@Z @ 0x001D80F0
HRESULT CSystemLinkQuery::sub_1D80F0(const RwUInt8 *arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    if (!unk_104C)
        return S_OK;
    if (unk_104C == 2)
        return unk_1050;
    sub_1D8140(arg_0, arg_4, arg_8);
    return S_OK;
}

// match: ?sub_1D8140@CSystemLinkQuery@@QAEXPBEHH@Z @ 0x001D8140
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void CSystemLinkQuery::sub_1D8140(const RwUInt8 *arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    const type_1D8140_reply *x8;
    bool var_9;
    RwInt32 var_10;
    RwInt32 l4;

    // Two compiled-out checks (docs/toolchain.md).
    if (!unk_104C)
    {
    }
    if (!unk_104C)
    {
    }
    x8 = (const type_1D8140_reply *)arg_0;
    var_9 = true;
    for (l4 = 0; l4 < 8; l4++)
    {
        if (unk_1044[l4] != x8->unk_02[l4])
            var_9 = false;
    }
    if (var_9)
    {
        var_10 = unk_F0C;
        unk_F0C = var_10 + 1;
        unk_000[var_10].unk_4A = x8->unk_0A;
        unk_000[var_10].unk_52 = x8->unk_12;
        unk_000[var_10].unk_62 = x8->unk_22;
        unk_000[var_10].unk_8A = 0;
        unk_000[var_10].unk_8E = x8->unk_B8;
        unk_000[var_10].unk_92 = 0;
        unk_000[var_10].unk_00 = x8->unk_48[0].info.integer.qwValue;
        unk_000[var_10].unk_08 = x8->unk_48[1].info.integer.qwValue;
        unk_000[var_10].unk_86 = (RwInt32)x8->unk_48[2].info.integer.qwValue - x8->unk_B8;
        unk_000[var_10].unk_10 = x8->unk_48[3].info.integer.qwValue;
        wcscpy(unk_000[var_10].unk_28, x8->unk_98);
        unk_F10[var_10] = &unk_000[var_10].unk_62;
        unk_F74[var_10] = &unk_000[var_10].unk_4A;
        unk_FD8[var_10] = &unk_000[var_10].unk_52;
    }
}





// (The compiler's exit thunk for sub_1D8810's instance: it runs cXboxLive's
// destructor.)














































































































// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??1cXboxSocket@@QAE@XZ (folded into 0x1E41C0)
cXboxSocket::~cXboxSocket()
{
}
