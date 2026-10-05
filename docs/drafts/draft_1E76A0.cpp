/*
 * kujuUI's integer value (game/kujuui.h): a value a combobox steps between
 * a least and a greatest, by small and large steps, wrapping unless told
 * not to, shown between a prefix and suffix (or as a text of its own at the
 * least), telling a hook when it changes.
 */
#include <stdlib.h>
#include "game/kujuui.h"

namespace kujuUI {

// match: ??0type_1E76A0@kujuUI@@QAE@HHHHHHHABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@00PAUtype_1ED670_object@1@@Z @ 0x001E76A0
type_1E76A0::type_1E76A0(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C, RwInt32 arg_10, RwInt32 arg_14,
                         RwInt32 arg_18, const std::string &arg_1C, const std::string &arg_20,
                         const std::string &arg_24, type_1ED670_object *arg_28)
    : unk_08(arg_0), unk_0C(arg_4), unk_10(arg_8), unk_14(arg_C), unk_18(arg_10), unk_1C(arg_14), unk_20(arg_18),
      unk_24(arg_1C), unk_40(arg_20), unk_5C(arg_24), unk_78(arg_28)
{
}

// match: ??_Gtype_1E76A0@kujuUI@@UAEPAXI@Z @ 0x001E7770

// match: ??1type_1E76A0@kujuUI@@UAE@XZ @ 0x001E77A0
type_1E76A0::~type_1E76A0()
{
}

// match: ?vf_014@type_1E76A0@kujuUI@@UAEXXZ @ 0x001E7840
void type_1E76A0::vf_014()
{
    if (has_unk_04())
    {
        sub_1E7A80();
        if (unk_78)
            unk_78->vf_008();
    }
}

// match: ?vf_008@type_1E76A0@kujuUI@@UAEXI@Z @ 0x001E7880
void type_1E76A0::vf_008(RwUInt32 arg_0)
{
    if (unk_08 == unk_10)
    {
        if (!unk_20)
            unk_08 = unk_0C;
    }
    else if (arg_0 > 10)
        unk_08 += unk_1C;
    else if (arg_0 > 5)
        unk_08 += unk_1C;
    else
        unk_08 += unk_14;
    unk_08 = std::min(unk_08, unk_10);
    vf_014();
}

// match: ?vf_00C@type_1E76A0@kujuUI@@UAEXI@Z @ 0x001E7950
void type_1E76A0::vf_00C(RwUInt32 arg_0)
{
    if (unk_08 == unk_0C)
    {
        if (!unk_20)
            unk_08 = unk_10;
    }
    else if (arg_0 > 10)
        unk_08 -= unk_1C;
    else if (arg_0 > 5)
        unk_08 -= unk_1C;
    else
        unk_08 -= unk_14;
    unk_08 = std::max(unk_08, unk_0C);
    vf_014();
}

// match: ?vf_010@type_1E76A0@kujuUI@@UAE_NXZ @ 0x001E7A20
bool type_1E76A0::vf_010()
{
    return has_unk_04() && (unk_78 ? unk_78->vf_00C() : true);
}

// match: ?sub_1E7A80@type_1E76A0@kujuUI@@QAEXXZ @ 0x001E7A80
void type_1E76A0::sub_1E7A80()
{
    if (has_unk_04())
    {
        if (unk_08 == unk_0C && !unk_24.empty())
            sub_1E3480()->sub_1E2A50(unk_24);
        else
        {
            type_1CB670 var_3C(unk_40);
            RwChar var_20[16];
            _itoa(unk_08, var_20, 10);
            var_3C.sub_1C84F0(sub_1CB720(var_20));
            var_3C.sub_1C84F0(unk_5C);
            sub_1E3480()->sub_1E2A50(var_3C);
        }
    }
}

// match: ?sub_1E7BB0@type_1E76A0@kujuUI@@QAEXH@Z @ 0x001E7BB0
void type_1E76A0::sub_1E7BB0(RwInt32 arg_0)
{
    unk_08 = arg_0;
    sub_1E7A80();
}

// match: ?sub_1E7BD0@type_1E76A0@kujuUI@@QAEXH@Z @ 0x001E7BD0
void type_1E76A0::sub_1E7BD0(RwInt32 arg_0)
{
    if (arg_0 >= unk_0C)
    {
        unk_10 = arg_0;
        unk_08 = std::min(unk_08, unk_10);
        vf_014();
    }
}
}
