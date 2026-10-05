/*
 * kujuUI's static text's creator ("text", game/kujuui.h): a text over a
 * rectangle in a font, bound to a text object or showing a localised text.
 */
#include "game/kujuui.h"
#include "game/parsedfile.h"
#include "types/type_4D1DB8.h"

namespace kujuUI {

// match: ??0type_3E7A00@kujuUI@@QAE@XZ @ 0x001F1040
type_3E7A00::type_3E7A00()
{
}

// match: ??_Gtype_3E7A00@kujuUI@@UAEPAXI@Z @ 0x001F1060

// match: ??1type_3E7A00@kujuUI@@UAE@XZ @ 0x001F1090
type_3E7A00::~type_3E7A00()
{
}

// match: ?vf_004@type_3E7A00@kujuUI@@UAEPBDXZ @ 0x001F10B0
const RwChar *type_3E7A00::vf_004()
{
    return "text";
}

// match: ?vf_008@type_3E7A00@kujuUI@@UAEXPAUtype_1C8DF0@2@HHPAUtype_1ED670@2@PAUtype_3E7D08@2@PAPAU52@@Z @ 0x001F10C0
void type_3E7A00::vf_008(type_1C8DF0 *arg_0, RwInt32 arg_4, RwInt32 arg_8, type_1ED670 *arg_C, type_3E7D08 *arg_10,
                         type_3E7D08 **arg_14)
{
    type_1E0330_rect var_20(0, 0, 0, 0);
    RwInt32 var_10;

    *arg_14 = 0;
    if (sub_1F7B10(arg_0, 0, &var_20) == 1 && sub_1F7E70(arg_0, arg_8, &var_10) == 1)
    {
        type_1C8DF0_104 *var_2C = arg_0->sub_1C90B0(sub_1E3550());
        type_1C8DF0_104 *var_24 = arg_0->sub_1C90B0(sub_1E35A0());
        RwInt32 var_28 = arg_0->sub_1C90B0(sub_1E3580()) ? 1 : (arg_0->sub_1C90B0(sub_1E3590()) ? 2 : 0);

        if (var_24)
        {
            type_1F28C0 *var_30;

            arg_C->sub_1E0D50(var_24->sub_1C9890(0)->sub_1E3480(), 3, &var_30);
            sub_1F7A60(arg_0, "a source");
            if (!var_30)
            {
                if (0)
                    sub_1C8A30("Widget factory - source missing! Widget \"%s\" type \"%s\"\n",
                               arg_0->sub_1C8FC0() ? arg_0->sub_1C8FC0() : "(none)",
                               arg_0->sub_1C8FE0()->sub_1CA280());
            }
            sub_1F7A60(var_30 != 0, pResourcePath);
            if (var_30)
            {
                cStaticText *var_34 = new cStaticText(var_10, &var_20, var_28, var_30, arg_10);
                *arg_14 = var_34;
            }
        }
        else if (var_2C)
        {
            type_1A5EA0 var_54((const RwChar *)var_2C->sub_1C9890(0)->sub_1E3480(), 0);

            if (var_54.c_str())
            {
                cStaticText *var_58 = new cStaticText(var_10, &var_20, var_28, 0, arg_10);
                var_58->pvf_008(var_54);
                *arg_14 = var_58;
            }
        }
    }
}

// match: ?vf_00C@type_3E7A00@kujuUI@@UAEXPAVcScopeValidator@2@@Z @ 0x001F13B0
void type_3E7A00::vf_00C(cScopeValidator *arg_0)
{
    arg_0->sub_1CA1A0(sub_1E3700());
    arg_0->sub_1C9F50(sub_1E3560());
    arg_0->sub_1C9F50(sub_1E3570());
    arg_0->sub_1C9F50(sub_1E3580());
    arg_0->sub_1C9F50(sub_1E3590());
    arg_0->sub_1C9F50(sub_1E3550());
    arg_0->sub_1C9F50(sub_1E35A0());
}
}
