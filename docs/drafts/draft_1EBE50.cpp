/*
 * kujuUI's list box's rows, its creator ("listbox") and its columns
 * (game/kujuui.h).
 */
#include "game/kujuui.h"
#include "game/parsedfile.h"
#include "types/type_4D1DB8.h"

namespace kujuUI {

// match: ??0type_3E74C0@kujuUI@@QAE@XZ @ 0x001EBE50
type_3E74C0::type_3E74C0()
{
    unk_3C = 0;
}

// match: ??_Gtype_3E74C0@kujuUI@@UAEPAXI@Z @ 0x001EBE90

// match: ??1type_3E74C0@kujuUI@@UAE@XZ @ 0x001EBEC0
type_3E74C0::~type_3E74C0()
{
    if (sub_1EC230())
        unk_3C->sub_1EAB50(this);
}

// match: ?sub_1EBF00@type_3E74C0@kujuUI@@QAEXXZ @ 0x001EBF00
void type_3E74C0::sub_1EBF00()
{
    for (RwUInt32 var_4 = 0; var_4 < unk_3C->sub_1EB090(); ++var_4)
        (*unk_28.at(var_4))->sub_1F1AA0();
}

// match: ?sub_1EBF50@type_3E74C0@kujuUI@@QAEXXZ @ 0x001EBF50
void type_3E74C0::sub_1EBF50()
{
    for (RwUInt32 var_4 = 0; var_4 < unk_3C->sub_1EB090(); ++var_4)
        (*unk_28.at(var_4))->sub_1F1AD0();
}

// match: ?sub_1EBFA0@type_3E74C0@kujuUI@@QAEXPAUtype_3E7490@2@@Z @ 0x001EBFA0
void type_3E74C0::sub_1EBFA0(type_3E7490 *arg_0)
{
    unk_3C = arg_0;
    type_1E0330_rect var_1C(0, 0, 10.0f, 10.0f);
    for (RwUInt32 var_20 = 0; var_20 < unk_3C->sub_1EB090(); ++var_20)
    {
        type_1E37A0 *var_24 = new type_1E37A0(unk_3C->sub_190360());
        *unk_14.next() = var_24;
        type_1F1420 *var_2C = new type_1F1420(unk_3C->sub_1EAC10(), &var_1C, unk_3C->sub_1EB110(var_20), true);
        *unk_28.next() = var_2C;
        (*unk_28.back())->sub_1F2410(0);
    }
    vf_004();
}

// match: ?sub_1EC110@type_3E74C0@kujuUI@@QAEXXZ @ 0x001EC110
void type_3E74C0::sub_1EC110()
{
    for (::type_1E61A0_it<type_1E37A0 *, 4> var_8 = unk_14.begin(); var_8.ne(unk_14.end()); var_8.inc())
        delete *var_8.get();
    unk_14.clear();
    for (::type_1E61A0_it<type_1F1420 *, 4> var_10 = unk_28.begin(); var_10.ne(unk_28.end()); var_10.inc())
        delete *var_10.get();
    unk_28.clear();
    unk_3C = 0;
}

// match: ?sub_1EC230@type_3E74C0@kujuUI@@QAE_NXZ @ 0x001EC230
bool type_3E74C0::sub_1EC230()
{
    return unk_3C != 0;
}

// match: ?sub_1EC250@type_3E74C0@kujuUI@@QAEXH@Z @ 0x001EC250
void type_3E74C0::sub_1EC250(RwInt32 arg_0)
{
    for (RwUInt32 var_4 = 0; var_4 < unk_3C->sub_1EB090(); ++var_4)
    {
        (*unk_28.at(var_4))->sub_1F1E00(arg_0);
        (*unk_14.at(var_4))->sub_1E3B20(arg_0);
    }
}

// match: ?sub_1EC2C0@type_3E74C0@kujuUI@@QAEXABUtype_1A5EA0@@I@Z @ 0x001EC2C0
void type_3E74C0::sub_1EC2C0(const type_1A5EA0 &arg_0, RwUInt32 arg_4)
{
    type_1F1420 *var_4 = *unk_28.at(arg_4);
    var_4->sub_1F1D10(arg_0);
}

// match: ?sub_1EC2F0@type_3E74C0@kujuUI@@QAEXPAUtype_1E4130@2@@Z @ 0x001EC2F0
void type_3E74C0::sub_1EC2F0(type_1E4130 *arg_0)
{
    for (RwUInt32 var_4 = 0; var_4 < unk_3C->sub_1EB090(); ++var_4)
    {
        type_1F1420 *var_8 = *unk_28.at(var_4);
        type_1E37A0 *var_C = *unk_14.at(var_4);
        var_C->sub_1E3950(arg_0);
        var_8->sub_1F1B10(arg_0);
    }
}

// match: ?sub_1EC370@type_3E74C0@kujuUI@@QAEXPBUtype_1E0330_rect@2@I@Z @ 0x001EC370
void type_3E74C0::sub_1EC370(const type_1E0330_rect *arg_0, RwUInt32 arg_4)
{
    type_1F1420 *var_4 = *unk_28.at(arg_4);
    var_4->sub_1F20E0(unk_3C->sub_1EB110(arg_4));
    var_4->pvf_008(arg_0);
    (*unk_14.at(arg_4))->sub_1E3A30(arg_0);
}

// match: ??0type_3E74C8@kujuUI@@QAE@XZ @ 0x001EC490
type_3E74C8::type_3E74C8()
{
}

// match: ??_Gtype_3E74C8@kujuUI@@UAEPAXI@Z @ 0x001EC4B0

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
void type_3E74C8::vf_008(type_1C8DF0 *arg_0, RwInt32 arg_4, RwInt32 arg_8, type_1ED670 *arg_C, type_3E7D08 *arg_10,
                         type_3E7D08 **arg_14)
{
    type_1E0330_rect var_2C(0, 0, 0, 0);
    type_1C8DF0_104 *var_10 = arg_0->sub_1C90B0(sub_1E3790());
    const RwChar *var_14;
    const RwChar *var_18;
    RwInt32 var_1C;

    if (sub_1F7B10(arg_0, 0, &var_2C) == 1 && sub_1F7D80(arg_0, arg_4, &var_14) == 1 &&
        sub_1F7EA0(arg_0, sub_1E3780(), arg_4, &var_18) == 1 && sub_1F7E70(arg_0, arg_8, &var_1C) == 1)
    {
        type_1ECA30 *var_3C = 0;
        type_1C8DF0_104 *var_30 = arg_0->sub_1C90B0(sub_1E35A0());

        if (var_30)
        {
            RwInt32 var_40 = var_30->sub_1C9890(0)->sub_1E3480();
            arg_C->sub_1E0D50(var_40, 2, &var_3C);
        }
        sub_1F7A60(arg_0, "a source");
        if (!var_30)
        {
            if (0)
                sub_1C8A30("Widget factory - source missing! Widget \"%s\" type \"%s\"\n",
                           arg_0->sub_1C8FC0() ? arg_0->sub_1C8FC0() : "(none)", arg_0->sub_1C8FE0()->sub_1CA280());
        }
        sub_1F7A60(var_30 != 0, pResourcePath);
        RwUInt32 var_38;
        if (var_10)
            var_38 = var_10->sub_1C9890(0)->sub_1E3480();
        else
        {
            type_1E5A60 *var_44 = ((type_1E6350 *)var_1C)->sub_1E6610(0).operator->();
            var_38 = var_44->sub_1E60E0();
        }
        RwInt32 var_34 = (RwInt32)((var_2C.unk_0C - var_2C.unk_04) / (RwReal)var_38);
        *arg_14 = new type_3E7490((RwInt32)var_14, (type_1E3BA0 *)var_18, var_1C, &var_2C, (RwReal)var_38, var_34,
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
type_1ECA30::type_1ECA30(RwUInt32 arg_0)
{
    unk_04 = 0;
    unk_08 = arg_0;
    unk_0C = new type_1ECA30_column[arg_0];
}

// match: ?sub_1EC930@type_1ECA30@kujuUI@@QAEXXZ @ 0x001EC930
void type_1ECA30::sub_1EC930()
{
    if (unk_04)
    {
        RwReal var_4 = unk_04->unk_104.width();
        RwReal var_8 = 0;
        for (RwUInt32 var_C = 0; var_C != sub_FB710(); ++var_C)
            var_8 += (RwReal)unk_0C[var_C].unk_00;
        if (var_8 > 0.0f)
        {
            RwReal var_10 = var_4 / var_8;
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
void type_1ECA30::sub_1ECA30(type_3E7490 *arg_0)
{
    unk_04 = arg_0;
    if (unk_04)
    {
        vf_018();
        if (unk_0C[0].unk_00 == 0)
        {
            RwInt32 var_8 = (RwInt32)arg_0->unk_104.width();
            RwReal var_4 = (RwReal)(var_8 / sub_FB710());
            for (RwUInt32 var_C = 0; var_C != sub_FB710(); ++var_C)
                unk_0C[var_C].unk_00 = (RwInt32)var_4;
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

// The array template's members this unit instantiates first.
// match: ?next@?$type_1E61A0@PAUtype_1E37A0@kujuUI@@$03@@QAEPAPAUtype_1E37A0@kujuUI@@XZ @ 0x001EC3E0
// match: ?clear@?$type_1E61A0@PAUtype_1E37A0@kujuUI@@$03@@QAEXXZ @ 0x001EC420
// match: ?back@?$type_1E61A0@PAUtype_1F1420@kujuUI@@$03@@QAEPAPAUtype_1F1420@kujuUI@@XZ @ 0x001EC470
}
