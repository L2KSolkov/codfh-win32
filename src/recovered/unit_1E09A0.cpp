// kujuUI's button creator (type_3E6DA0): split from unit_1E0670.cpp at 0x1E09A0, where the image
// ends that object (its deferred functions come before the next out-of-line one; PLAN M7).

#include "game/kujuui.h"
#include "game/fileio.h"
#include "game/frontend.h"
#include "game/parsedfile.h"
#include "types/type_4D1DB8.h"

// match: __ehhandler$?vf_008@type_3E6DA0@kujuUI@@UAEXPAUtype_1C8DF0@2@HHPAUtype_1ED670@2@PAUtype_3E7D08@2@PAPAU52@@Z>1>8 @ 0x0041FD04
// match: __ehhandler$?vf_008@type_3E6DA0@kujuUI@@UAEXPAUtype_1C8DF0@2@HHPAUtype_1ED670@2@PAUtype_3E7D08@2@PAPAU52@@Z>1 @ 0x0041FD0C
// match: ??_Gtype_3E6DA0@kujuUI@@UAEPAXI@Z @ 0x001E09C0
// match: ??$sub_1E0D50@Utype_1ED670_object@kujuUI@@@type_1ED670@kujuUI@@QAEXHHPAPAUtype_1ED670_object@1@@Z @ 0x001E0D50
// match: ??_7type_3E6DA0@kujuUI@@6B@ @ 0x003E6DA0
// match: ??_C@_06HFKPFKMP@button?$AA@ @ 0x003E6DB0
// match: ??_C@_0DI@BNKJEENP@Widget?5factory?5?9?5source?5missing?$CB@ @ 0x003E6DB8
// match: ??_C@_06GGPOMPNM@?$CInone?$CJ?$AA@ @ 0x003E6DF0
// match: ??_C@_08CNKFIGOK@a?5source?$AA@ @ 0x003E6DF8

namespace kujuUI
{
// match: ??0type_3E6DA0@kujuUI@@QAE@XZ @ 0x001E09A0
type_3E6DA0::type_3E6DA0()
{
}
// match: ??1type_3E6DA0@kujuUI@@UAE@XZ @ 0x001E09F0
type_3E6DA0::~type_3E6DA0()
{
}
// match: ?vf_004@type_3E6DA0@kujuUI@@UAEPBDXZ @ 0x001E0A10
const RwChar *type_3E6DA0::vf_004()
{
    return "button";
}
// match: ?vf_008@type_3E6DA0@kujuUI@@UAEXPAUtype_1C8DF0@2@HHPAUtype_1ED670@2@PAUtype_3E7D08@2@PAPAU52@@Z @ 0x001E0A20
// match: __ehhandler$?vf_008@type_3E6DA0@kujuUI@@UAEXPAUtype_1C8DF0@2@HHPAUtype_1ED670@2@PAUtype_3E7D08@2@PAPAU52@@Z-0xB @ 0x003037C0
// match: __ehhandler$?vf_008@type_3E6DA0@kujuUI@@UAEXPAUtype_1C8DF0@2@HHPAUtype_1ED670@2@PAUtype_3E7D08@2@PAPAU52@@Z @ 0x003037CB
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3E6DA0::vf_008(type_1C8DF0 *arg_0, RwInt32 arg_4, RwInt32 arg_8, type_1ED670 *arg_C, type_3E7D08 *arg_10,
                         type_3E7D08 **arg_14)
{
    type_1E0330_rect var_20(0, 0, 0, 0);
    const RwChar *lv_10;

    if (sub_1F7D80(arg_0, arg_4, &lv_10) == 1 && sub_1F7B10(arg_0, lv_10, &var_20) == 1)
    {
        type_1ED670_object *var_2C = 0;
        type_1ED670_object *var_28 = 0;
        type_1ED670_object *ebp_24 = 0;

        sub_1E0CB0(arg_0, sub_1E3520(), 0, arg_C, &var_2C);
        sub_1E0CB0(arg_0, sub_1E3530(), 0, arg_C, &var_28);
        sub_1E0CB0(arg_0, sub_1E3540(), 0, arg_C, &ebp_24);
        sub_1F7A60(arg_0, "a source");
        if (!var_2C)
        {
            if (0)
                sub_1C8A30("Widget factory - source missing! Widget \"%s\" type \"%s\"\n",
                           arg_0->sub_1C8FC0() ? arg_0->sub_1C8FC0() : "(none)", arg_0->sub_1C8FE0()->sub_1CA280());
        }
        sub_1F7A60(var_2C != 0, "");
        *arg_14 = new type_3E6D70(lv_10, &var_20, sub_1F7FE0(arg_0), var_2C, var_28, ebp_24, arg_10);
        sub_1F7CC0(arg_0, arg_C, static_cast<type_3E76B4 *>(*arg_14));
        sub_1F7DB0(arg_0, arg_C, static_cast<type_3E76B4 *>(*arg_14));
    }
}
// match: ?vf_00C@type_3E6DA0@kujuUI@@UAEXPAVcScopeValidator@2@@Z @ 0x001E0C50
void type_3E6DA0::vf_00C(cScopeValidator *arg_0)
{
    arg_0->sub_1CA1A0(sub_1E3700());
    arg_0->sub_1CA1A0(sub_1E3720());
    arg_0->sub_1C9F50(sub_1E3520());
    arg_0->sub_1C9F50(sub_1E3530());
    arg_0->sub_1C9F50(sub_1E3540());
}
// match: ??$sub_1E0CB0@Utype_1ED670_object@kujuUI@@@kujuUI@@YAHPAUtype_1C8DF0@0@PAUtype_1C9590@0@HPAUtype_1ED670@0@PAPAUtype_1ED670_object@0@@Z @ 0x001E0CB0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
template <class T> RwInt32 sub_1E0CB0(type_1C8DF0 *arg_0, type_1C9590 *arg_4, RwInt32 arg_8, type_1ED670 *arg_C,
                                      T **arg_10)
{
    RwInt32 l4 = 0;
    type_1C8DF0_104 *var_8 = arg_0->sub_1C90B0(arg_4);

    if (var_8)
    {
        sub_1F7A60(arg_0, arg_4->get_unk_00());
        RwInt32 var_C = var_8->sub_1C9890(0)->sub_1E3480();

        arg_C->sub_1E0D50(var_C, arg_8, arg_10);
        if (*arg_10)
            l4 = 1;
        else
            l4 = 2;
        sub_1F7A60(l4, var_C);
    }
    return l4;
}
}
