// kujuUI's static image creator (type_3E7830): split from unit_1F00E0.cpp at 0x1F0230, where the
// image ends that object (its deferred functions come before the next out-of-line one; PLAN M7).

#include "game/kujuui.h"
#include "game/assert.h"
#include "game/parsedfile.h"

// match: __ehhandler$?vf_008@type_3E7830@kujuUI@@UAEXPAUtype_1C8DF0@2@HHPAUtype_1ED670@2@PAUtype_3E7D08@2@PAPAU52@@Z>1>8 @ 0x00420B88
// match: __ehhandler$?vf_008@type_3E7830@kujuUI@@UAEXPAUtype_1C8DF0@2@HHPAUtype_1ED670@2@PAUtype_3E7D08@2@PAPAU52@@Z>1 @ 0x00420B90
// match: ??_Gtype_3E7830@kujuUI@@UAEPAXI@Z @ 0x001F0250
// match: ??_7type_3E7830@kujuUI@@6B@ @ 0x003E7830

namespace kujuUI
{
// match: ??0type_3E7830@kujuUI@@QAE@XZ @ 0x001F0230
type_3E7830::type_3E7830()
{
}
// match: ??1type_3E7830@kujuUI@@UAE@XZ @ 0x001F0280
type_3E7830::~type_3E7830()
{
}
// match: ?vf_004@type_3E7830@kujuUI@@UAEPBDXZ @ 0x001F02A0
const RwChar *type_3E7830::vf_004()
{
    return "image";
}
// match: ?vf_008@type_3E7830@kujuUI@@UAEXPAUtype_1C8DF0@2@HHPAUtype_1ED670@2@PAUtype_3E7D08@2@PAPAU52@@Z @ 0x001F02B0
// match: __ehhandler$?vf_008@type_3E7830@kujuUI@@UAEXPAUtype_1C8DF0@2@HHPAUtype_1ED670@2@PAUtype_3E7D08@2@PAPAU52@@Z-0xB @ 0x00304230
// match: __ehhandler$?vf_008@type_3E7830@kujuUI@@UAEXPAUtype_1C8DF0@2@HHPAUtype_1ED670@2@PAUtype_3E7D08@2@PAPAU52@@Z @ 0x0030423B
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3E7830::vf_008(type_1C8DF0 *arg_0, RwInt32 arg_4, RwInt32 arg_8, type_1ED670 *arg_C, type_3E7D08 *arg_10,
                         type_3E7D08 **arg_14)
{
    type_1E0330_rect var_20(0, 0, 0, 0);
    const RwChar *lv_10;

    if (sub_1F7D80(arg_0, arg_4, &lv_10) == 1 && sub_1F7B10(arg_0, lv_10, &var_20) == 1)
    {
        *arg_14 = new cStaticImage(lv_10, &var_20, arg_10);
        sub_1F7CC0(arg_0, arg_C, static_cast<type_3E76B4 *>(*arg_14));
        sub_1F7DB0(arg_0, arg_C, static_cast<type_3E76B4 *>(*arg_14));
    }
}
// match: ?vf_00C@type_3E7830@kujuUI@@UAEXPAVcScopeValidator@2@@Z @ 0x001F03F0
void type_3E7830::vf_00C(cScopeValidator *arg_0)
{
    arg_0->sub_1CA1A0(sub_1E3700());
}
}
