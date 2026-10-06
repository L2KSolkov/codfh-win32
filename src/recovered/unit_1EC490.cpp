// kujuUI's list box creator (type_3E74C8): split from unit_1EBE50.cpp at 0x1EC490, where the image
// ends that object (its deferred functions come before the next out-of-line one; PLAN M7).

#include "game/kujuui.h"
#include "game/parsedfile.h"
#include "types/type_4D1DB8.h"

// match: __ehhandler$?vf_008@type_3E74C8@kujuUI@@UAEXPAUtype_1C8DF0@2@HHPAUtype_1ED670@2@PAUtype_3E7D08@2@PAPAU52@@Z>1>8 @ 0x00420640
// match: __ehhandler$?vf_008@type_3E74C8@kujuUI@@UAEXPAUtype_1C8DF0@2@HHPAUtype_1ED670@2@PAUtype_3E7D08@2@PAPAU52@@Z>1 @ 0x00420650
// match: __ehhandler$??0type_1ECA30@kujuUI@@QAE@I@Z>1>8 @ 0x0042066C
// match: __ehhandler$??0type_1ECA30@kujuUI@@QAE@I@Z>1 @ 0x00420674
// match: ??_Gtype_3E74C8@kujuUI@@UAEPAXI@Z @ 0x001EC4B0
// match: ??_7type_3E74C8@kujuUI@@6B@ @ 0x003E74C8
// match: ??_C@_07LHBBOFFP@listbox?$AA@ @ 0x003E74D8
// match: ??_7type_1ECA30@kujuUI@@6B@ @ 0x003E74E0

namespace kujuUI
{
// match: ??0type_3E74C8@kujuUI@@QAE@XZ @ 0x001EC490
type_3E74C8::type_3E74C8()
{
}
// match: ??1type_3E74C8@kujuUI@@UAE@XZ @ 0x001EC4E0
type_3E74C8::~type_3E74C8()
{
}
// match: ?vf_004@type_3E74C8@kujuUI@@UAEPBDXZ @ 0x001EC500
const RwChar *type_3E74C8::vf_004()
{
    return "listbox";
}
// match: ?vf_008@type_3E74C8@kujuUI@@UAEXPAUtype_1C8DF0@2@HHPAUtype_1ED670@2@PAUtype_3E7D08@2@PAPAU52@@Z @ 0x001EC510
// match: __ehhandler$?vf_008@type_3E74C8@kujuUI@@UAEXPAUtype_1C8DF0@2@HHPAUtype_1ED670@2@PAUtype_3E7D08@2@PAPAU52@@Z-0x13 @ 0x00303EB0
// match: __ehhandler$?vf_008@type_3E74C8@kujuUI@@UAEXPAUtype_1C8DF0@2@HHPAUtype_1ED670@2@PAUtype_3E7D08@2@PAPAU52@@Z @ 0x00303EC3
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3E74C8::vf_008(type_1C8DF0 *arg_0, RwInt32 arg_4, RwInt32 arg_8, type_1ED670 *arg_C, type_3E7D08 *arg_10,
                         type_3E7D08 **arg_14)
{
    type_1E0330_rect var_2C(0, 0, 0, 0);
    type_1C8DF0_104 *lv_10 = arg_0->sub_1C90B0(sub_1E3790());
    const RwChar *var_14;
    const RwChar *var_18;
    RwInt32 slot_1C;

    if (sub_1F7B10(arg_0, 0, &var_2C) == 1 && sub_1F7D80(arg_0, arg_4, &var_14) == 1 &&
        sub_1F7EA0(arg_0, sub_1E3780(), arg_4, &var_18) == 1 && sub_1F7E70(arg_0, arg_8, &slot_1C) == 1)
    {
        type_1ECA30 *var_3C = 0;
        type_1C8DF0_104 *local_30 = arg_0->sub_1C90B0(sub_1E35A0());

        if (local_30)
        {
            RwInt32 var_40 = local_30->sub_1C9890(0)->sub_1E3480();
            arg_C->sub_1E0D50(var_40, 2, &var_3C);
        }
        sub_1F7A60(arg_0, "a source");
        if (!local_30)
        {
            if (CODFH_DEBUG_LOGS)
                sub_1C8A30("Widget factory - source missing! Widget \"%s\" type \"%s\"\n",
                           arg_0->sub_1C8FC0() ? arg_0->sub_1C8FC0() : "(none)", arg_0->sub_1C8FE0()->sub_1CA280());
        }
        sub_1F7A60(local_30 != 0, "");
        RwUInt32 var_38;
        if (lv_10)
            var_38 = lv_10->sub_1C9890(0)->sub_1E3480();
        else
        {
            type_1E5A60 *var_44 = ((type_1E6350 *)slot_1C)->sub_1E6610(0).operator->();
            var_38 = var_44->sub_1E60E0();
        }
        RwInt32 var_34 = (RwInt32)(var_2C.height() / (RwReal)var_38);
        *arg_14 = new type_3E7490((RwInt32)var_14, (type_1E3BA0 *)var_18, slot_1C, &var_2C, (RwReal)var_38, var_34,
                                  sub_1F7FE0(arg_0), var_3C, arg_10);
    }
}
// match: ?vf_00C@type_3E74C8@kujuUI@@UAEXPAVcScopeValidator@2@@Z @ 0x001EC7A0
void type_3E74C8::vf_00C(cScopeValidator *arg_0)
{
    arg_0->sub_1CA1A0(sub_1E3720());
    arg_0->sub_1C9F50(sub_1E34E0());
    arg_0->sub_1C9F50(sub_1E3500());
    arg_0->sub_1C9F50(sub_1E3780());
    arg_0->sub_1C9F50(sub_1E35A0());
    arg_0->sub_1C9F50(sub_1E3560());
    arg_0->sub_1C9F50(sub_1E3790());
}
// match: ??1type_1ECA30@kujuUI@@UAE@XZ @ 0x001EC810
type_1ECA30::~type_1ECA30()
{
    delete[] unk_0C;
}
// match: ??0type_1ECA30@kujuUI@@QAE@I@Z @ 0x001EC850
// match: __ehhandler$??0type_1ECA30@kujuUI@@QAE@I@Z-0x8 @ 0x00303ED0
// match: __ehhandler$??0type_1ECA30@kujuUI@@QAE@I@Z @ 0x00303ED8
type_1ECA30::type_1ECA30(RwUInt32 arg_0)
{
    unk_04 = 0;
    unk_08 = arg_0;
    unk_0C = new type_1ECA30_column[arg_0];
}
// match: ?sub_1EC930@type_1ECA30@kujuUI@@QAEXXZ @ 0x001EC930
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_1ECA30::sub_1EC930()
{
    if (unk_04)
    {
        RwReal l4 = unk_04->unk_104.width();
        RwReal var_8 = 0;
        for (RwUInt32 var_C = 0; var_C != sub_FB710(); ++var_C)
            var_8 += (RwReal)unk_0C[var_C].unk_00;
        if (var_8 > 0.0f)
        {
            RwReal var_10 = l4 / var_8;
            for (RwUInt32 var_14 = 0; var_14 != sub_FB710(); ++var_14)
            {
                RwReal var_18;
                unk_0C[var_14].unk_00 = (RwInt32)(var_18 = (var_18 = (RwReal)unk_0C[var_14].unk_00) * var_10);
            }
        }
        unk_04->sub_1EB140();
    }
}
// match: ?sub_1ECA30@type_1ECA30@kujuUI@@QAEXPAUtype_3E7490@2@@Z @ 0x001ECA30
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_1ECA30::sub_1ECA30(type_3E7490 *arg_0)
{
    unk_04 = arg_0;
    if (unk_04)
    {
        pvf_018();
        if (unk_0C[0].unk_00 == 0)
        {
            RwInt32 var_8 = (RwInt32)arg_0->unk_104.width();
            RwReal l4 = (RwReal)(var_8 / sub_FB710());
            for (RwUInt32 var_C = 0; var_C != sub_FB710(); ++var_C)
                unk_0C[var_C].unk_00 = (RwInt32)l4;
        }
        else
            sub_1EC930();
    }
}
// match: ?sub_1ECAF0@type_1ECA30@kujuUI@@QAEIXZ @ 0x001ECAF0
RwUInt32 type_1ECA30::sub_1ECAF0()
{
    return sub_1E3480()->sub_1EB070()->size();
}
// match: ?sub_1ECB40@type_1ECA30@kujuUI@@QAE_NXZ @ 0x001ECB40
bool type_1ECA30::sub_1ECB40()
{
    return sub_1E3480()->sub_1EA410();
}
// match: ?sub_1ECB60@type_1ECA30@kujuUI@@QAEXII@Z @ 0x001ECB60
void type_1ECA30::sub_1ECB60(RwUInt32 arg_0, RwUInt32 arg_4)
{
    unk_0C[arg_0].unk_00 = arg_4;
    if (unk_04)
        unk_04->sub_1EB140();
}
// match: ?sub_1ECB90@type_1ECA30@kujuUI@@QAEXIH@Z @ 0x001ECB90
void type_1ECA30::sub_1ECB90(RwUInt32 arg_0, RwInt32 arg_4)
{
    unk_0C[arg_0].unk_04 = arg_4;
    if (unk_04)
        unk_04->sub_1EB140();
}
}
