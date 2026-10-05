/*
 * kujuUI's text button (game/kujuui.h): a button showing a text it is the
 * source of, and its creator ("textbutton").
 */
#include "game/kujuui.h"
#include "game/parsedfile.h"
#include "types/type_4D1DB8.h"

namespace kujuUI {

// match: ??0type_3E79B4@kujuUI@@QAE@PBDPBUtype_1E0330_rect@1@_NPAUtype_1ED670_object@1@33ABUtype_1A5EA0@@PAUtype_1F28C0@1@HIPAUtype_3E7D08@1@@Z @ 0x001F07C0
type_3E79B4::type_3E79B4(const RwChar *arg_0, const type_1E0330_rect *arg_4, bool arg_8, type_1ED670_object *arg_C,
                         type_1ED670_object *arg_10, type_1ED670_object *arg_14, const type_1A5EA0 &arg_18,
                         type_1F28C0 *arg_1C, RwInt32 arg_20, RwUInt32 arg_24, type_3E7D08 *arg_28)
    : type_3E6D70(arg_0, arg_4, arg_8, arg_C, arg_10, arg_14, arg_28), unk_30(arg_20, arg_4, arg_24, true)
{
    if (arg_1C)
    {
        arg_1C->sub_1E7540(this);
        pvf_008(arg_1C->unk_08);
    }
    else
        pvf_008(arg_18);
}

// match: ??_Gtype_3E79B4@kujuUI@@UAEPAXI@Z @ 0x001F08D0

// match: ??1type_3E79B4@kujuUI@@UAE@XZ @ 0x001F0900
type_3E79B4::~type_3E79B4()
{
}

// match: ?vf_008@type_3E79B4@kujuUI@@UAEXXZ @ 0x001F09A0
void type_3E79B4::vf_008()
{
    unk_30.sub_1F1AA0();
    type_3E6D70::vf_008();
}

// match: ?vf_00C@type_3E79B4@kujuUI@@UAEXXZ @ 0x001F09C0
void type_3E79B4::vf_00C()
{
    unk_30.sub_1F1AD0();
    type_3E6D70::vf_00C();
}

// match: ?vf_018@type_3E79B4@kujuUI@@UAEXPAUtype_1E4130@2@@Z @ 0x001F09E0
void type_3E79B4::vf_018(type_1E4130 *arg_0)
{
    if (!static_cast<type_3E75E8 *>(this)->pvf_00C())
    {
        type_3E76B4::vf_018(arg_0);
        unk_30.sub_1F1B10(arg_0);
    }
}

// match: ?vf_014@type_3E79B4@kujuUI@@UAEXM@Z @ 0x001F0A20
void type_3E79B4::vf_014(RwReal arg_0)
{
    type_3E6D70::vf_014(arg_0);
    unk_30.sub_1F1E00(sub_1EFFC0());
}

// match: ?pvf_008@type_3E79B4@kujuUI@@UAEXPBUtype_1E0330_rect@2@@Z @ 0x001F0A50
void type_3E79B4::pvf_008(const type_1E0330_rect *arg_0)
{
    type_3E76B4::pvf_008(arg_0);
    static_cast<type_3E75E8 &>(unk_30).pvf_008(arg_0);
}

// match: ?pvf_008@type_3E79B4@kujuUI@@UAEXABUtype_1A5EA0@@@Z @ 0x001F0A80
void type_3E79B4::pvf_008(const type_1A5EA0 &arg_0)
{
    unk_30.sub_1F1D10(arg_0);
    static_cast<type_3E75E8 &>(unk_30).pvf_008(static_cast<type_3E75E8 *>(this)->pvf_004());
}

// match: ??_Etype_3E79B4@kujuUI@@WM@AEPAXI@Z @ 0x001F0AC0

// match: ??_Etype_3E79B4@kujuUI@@WCM@AEPAXI@Z @ 0x001F0AD0

// match: ??0type_3E79E4@kujuUI@@QAE@XZ @ 0x001F0AE0
type_3E79E4::type_3E79E4()
{
}

// match: ??_Gtype_3E79E4@kujuUI@@UAEPAXI@Z @ 0x001F0B00

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
void type_3E79E4::vf_008(type_1C8DF0 *arg_0, RwInt32 arg_4, RwInt32 arg_8, type_1ED670 *arg_C, type_3E7D08 *arg_10,
                         type_3E7D08 **arg_14)
{
    type_1E0330_rect var_24(0, 0, 0, 0);
    const RwChar *lv_10;
    RwInt32 var_14;

    if (sub_1F7D80(arg_0, arg_4, &lv_10) == 1 && sub_1F7B10(arg_0, lv_10, &var_24) == 1 &&
        sub_1F7E70(arg_0, arg_8, &var_14) == 1)
    {
        type_1ED670_object *var_40 = 0;
        type_1ED670_object *var_34 = 0;
        type_1ED670_object *var_2C = 0;

        sub_1E0CB0(arg_0, sub_1E3520(), 0, arg_C, &var_40);
        sub_1E0CB0(arg_0, sub_1E3530(), 0, arg_C, &var_34);
        sub_1E0CB0(arg_0, sub_1E3540(), 0, arg_C, &var_2C);
        type_1C8DF0_104 *var_3C = arg_0->sub_1C90B0(sub_1E3550());
        type_1C8DF0_104 *var_30 = arg_0->sub_1C90B0(sub_1E35A0());
        const RwChar *var_28 = pResourcePath;
        type_1F28C0 *var_44 = 0;

        if (var_30)
        {
            arg_C->sub_1E0D50(var_30->sub_1C9890(0)->sub_1E3480(), 3, &var_44);
            sub_1F7A60(arg_0, "a source");
            if (!var_44)
            {
                if (0)
                    sub_1C8A30("Widget factory - source missing! Widget \"%s\" type \"%s\"\n",
                               arg_0->sub_1C8FC0() ? arg_0->sub_1C8FC0() : "(none)",
                               arg_0->sub_1C8FE0()->sub_1CA280());
            }
            sub_1F7A60(var_44 != 0, pResourcePath);
        }
        else if (var_3C)
            var_28 = (const RwChar *)var_3C->sub_1C9890(0)->sub_1E3480();
        else
        {
            sub_1F7A60(arg_0, "a source");
            if (1)
            {
                if (0)
                    sub_1C8A30("Widget factory - source missing! Widget \"%s\" type \"%s\"\n",
                               arg_0->sub_1C8FC0() ? arg_0->sub_1C8FC0() : "(none)",
                               arg_0->sub_1C8FE0()->sub_1CA280());
            }
            sub_1F7A60(false, pResourcePath);
        }
        RwInt32 var_38 = arg_0->sub_1C90B0(sub_1E3570()) ? 0 : (arg_0->sub_1C90B0(sub_1E3590()) != 0) + 1;
        if (var_14 && (var_28 || var_44))
        {
            type_3E79B4 *var_48 = new type_3E79B4(lv_10, &var_24, sub_1F7FE0(arg_0), var_40, var_34, var_2C,
                                                  type_1A5EA0(var_28, 0), var_44, var_14, var_38, arg_10);
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
