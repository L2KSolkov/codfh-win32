// kujuUI's text button creator (type_3E79E4): split from unit_1F07C0.cpp at 0x1F0AE0, where the
// image ends that object (its deferred functions come before the next out-of-line one; PLAN M7).

#include "game/kujuui.h"
#include "game/parsedfile.h"
#include "types/type_4D1DB8.h"

// match: __ehhandler$?vf_008@type_3E79E4@kujuUI@@UAEXPAUtype_1C8DF0@2@HHPAUtype_1ED670@2@PAUtype_3E7D08@2@PAPAU52@@Z>1>8 @ 0x00420C6C
// match: __ehhandler$?vf_008@type_3E79E4@kujuUI@@UAEXPAUtype_1C8DF0@2@HHPAUtype_1ED670@2@PAUtype_3E7D08@2@PAPAU52@@Z>1 @ 0x00420C84
// match: ??_Gtype_3E79E4@kujuUI@@UAEPAXI@Z @ 0x001F0B00
// match: ??_7type_3E79E4@kujuUI@@6B@ @ 0x003E79E4
// match: ??_C@_0L@JJBACELP@textbutton?$AA@ @ 0x003E79F4

namespace kujuUI
{
// match: ??0type_3E79E4@kujuUI@@QAE@XZ @ 0x001F0AE0
type_3E79E4::type_3E79E4()
{
}
// match: ??1type_3E79E4@kujuUI@@UAE@XZ @ 0x001F0B30
type_3E79E4::~type_3E79E4()
{
}
// match: ?vf_004@type_3E79E4@kujuUI@@UAEPBDXZ @ 0x001F0B50
const RwChar *type_3E79E4::vf_004()
{
    return "textbutton";
}
// match: ?vf_008@type_3E79E4@kujuUI@@UAEXPAUtype_1C8DF0@2@HHPAUtype_1ED670@2@PAUtype_3E7D08@2@PAPAU52@@Z @ 0x001F0B60
// match: __ehhandler$?vf_008@type_3E79E4@kujuUI@@UAEXPAUtype_1C8DF0@2@HHPAUtype_1ED670@2@PAUtype_3E7D08@2@PAPAU52@@Z-0x24 @ 0x00304330
// match: __ehhandler$?vf_008@type_3E79E4@kujuUI@@UAEXPAUtype_1C8DF0@2@HHPAUtype_1ED670@2@PAUtype_3E7D08@2@PAPAU52@@Z @ 0x00304354
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3E79E4::vf_008(type_1C8DF0 *arg_0, RwInt32 arg_4, RwInt32 arg_8, type_1ED670 *arg_C, type_3E7D08 *arg_10,
                         type_3E7D08 **arg_14)
{
    type_1E0330_rect var_24(0, 0, 0, 0);
    const RwChar *lv_10;
    RwInt32 var_14;

    if (sub_1F7D80(arg_0, arg_4, &lv_10) == 1 && sub_1F7B10(arg_0, lv_10, &var_24) == 1 &&
        sub_1F7E70(arg_0, arg_8, &var_14) == 1)
    {
        const RwChar *slot_28;
        type_1ED670_object *fp_2c;
        type_1C8DF0_104 *o30;
        RwInt32 var_38;
        type_1ED670_object *l34;
        type_1C8DF0_104 *o3c;
        type_1F28C0 *lcl_44;
        type_1ED670_object *m_40;

        m_40 = 0;
        l34 = 0;
        fp_2c = 0;
        sub_1E0CB0(arg_0, sub_1E3520(), 0, arg_C, &m_40);
        sub_1E0CB0(arg_0, sub_1E3530(), 0, arg_C, &l34);
        sub_1E0CB0(arg_0, sub_1E3540(), 0, arg_C, &fp_2c);
        o3c = arg_0->sub_1C90B0(sub_1E3550());
        o30 = arg_0->sub_1C90B0(sub_1E35A0());
        slot_28 = "";
        lcl_44 = 0;

        if (o30)
        {
            arg_C->sub_1E0D50(o30->sub_1C9890(0)->sub_1E3480(), 3, &lcl_44);
            sub_1F7A60(arg_0, "a source");
            if (!lcl_44)
            {
                if (CODFH_DEBUG_LOGS)
                    sub_1C8A30("Widget factory - source missing! Widget \"%s\" type \"%s\"\n",
                               arg_0->sub_1C8FC0() ? arg_0->sub_1C8FC0() : "(none)",
                               arg_0->sub_1C8FE0()->sub_1CA280());
            }
            sub_1F7A60(lcl_44 != 0, "");
        }
        else if (o3c)
            slot_28 = (const RwChar *)o3c->sub_1C9890(0)->sub_1E3480();
        else
        {
            sub_1F7A60(arg_0, "a source");
            if (1)
            {
                if (CODFH_DEBUG_LOGS)
                    sub_1C8A30("Widget factory - source missing! Widget \"%s\" type \"%s\"\n",
                               arg_0->sub_1C8FC0() ? arg_0->sub_1C8FC0() : "(none)",
                               arg_0->sub_1C8FE0()->sub_1CA280());
            }
            sub_1F7A60(false, "");
        }
        var_38 = arg_0->sub_1C90B0(sub_1E3570()) ? 0 : (arg_0->sub_1C90B0(sub_1E3590()) ? 2 : 1);
        if (var_14 && (slot_28 || lcl_44))
        {
            type_3E79B4 *var_48 = new type_3E79B4(lv_10, &var_24, sub_1F7FE0(arg_0), m_40, l34, fp_2c,
                                                  type_1CB670(slot_28, 0), lcl_44, var_14, var_38, arg_10);
            sub_1F7CC0(arg_0, arg_C, static_cast<type_3E76B4 *>(*arg_14));
            sub_1F7DB0(arg_0, arg_C, static_cast<type_3E76B4 *>(*arg_14));
            *arg_14 = var_48;
        }
    }
}
// match: ?vf_00C@type_3E79E4@kujuUI@@UAEXPAVcScopeValidator@2@@Z @ 0x001F0F90
void type_3E79E4::vf_00C(cScopeValidator *arg_0)
{
    arg_0->sub_1CA1A0(sub_1E3700());
    arg_0->sub_1CA1A0(sub_1E3720());
    arg_0->sub_1C9F50(sub_1E3520());
    arg_0->sub_1C9F50(sub_1E3530());
    arg_0->sub_1C9F50(sub_1E3540());
    arg_0->sub_1C9F50(sub_1E3550());
    arg_0->sub_1C9F50(sub_1E3560());
    arg_0->sub_1C9F50(sub_1E35A0());
    arg_0->sub_1C9F50(sub_1E3570());
    arg_0->sub_1C9F50(sub_1E3580());
    arg_0->sub_1C9F50(sub_1E3590());
}
}
