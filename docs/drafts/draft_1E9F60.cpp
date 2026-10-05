/*
 * kujuUI's list box (game/kujuui.h): rows in a std::vector, shown a page at
 * a time under a look, with a selection the pad moves and columns the pad's
 * other buttons move; the vector's instances follow.
 */
#include <algorithm>
#include "game/kujuui.h"
#include "game/frontend.h"

namespace kujuUI {

// match: ??0type_3E7490@kujuUI@@QAE@HPAUtype_1E3BA0@1@HPBUtype_1E0330_rect@1@MH_NPAUtype_1ECA30@1@PAUtype_3E7D08@1@@Z @ 0x001E9F60
type_3E7490::type_3E7490(RwInt32 arg_0, type_1E3BA0 *arg_4, RwInt32 arg_8, const type_1E0330_rect *arg_C, RwReal arg_10,
                         RwInt32 arg_14, bool arg_18, type_1ECA30 *arg_1C, type_3E7D08 *arg_20)
    : type_3E7D08(arg_20), unk_1C(arg_0), unk_20(arg_4), unk_EC(arg_8), unk_F0(arg_10), unk_F4(arg_14), unk_F8(0),
      unk_FC(-1), unk_100(arg_1C), unk_104(*arg_C), unk_114(arg_18), unk_115(true)
{
    if (unk_100)
        unk_100->sub_1ECA30(this);
    unk_20.sub_1E3A30(arg_C);
}

// match: ??_Gtype_3E7490@kujuUI@@UAEPAXI@Z @ 0x001EA0A0

// match: ??1type_3E7490@kujuUI@@UAE@XZ @ 0x001EA0D0
type_3E7490::~type_3E7490()
{
}

// match: ?vf_008@type_3E7490@kujuUI@@UAEXXZ @ 0x001EA140
void type_3E7490::vf_008()
{
    for (RwUInt32 var_4 = 0; var_4 != unk_0C.size(); ++var_4)
        unk_0C[var_4]->sub_1EBF00();
    type_3E7D08::vf_008();
}

// match: ?vf_00C@type_3E7490@kujuUI@@UAEXXZ @ 0x001EA1D0
void type_3E7490::vf_00C()
{
    for (RwUInt32 var_4 = 0; var_4 != unk_0C.size(); ++var_4)
        unk_0C[var_4]->sub_1EBF50();
    type_3E7D08::vf_00C();
}

// match: ?sub_1EA260@type_3E7490@kujuUI@@QAEXXZ @ 0x001EA260
void type_3E7490::sub_1EA260()
{
    RwUInt32 var_10 = sub_1EB090();
    type_1E0330_rect var_20(0, unk_104.unk_04, 0, unk_104.unk_04 + unk_F0);
    std::vector<type_3E74C0 *>::iterator var_8 = unk_0C.begin() + unk_F8;
    std::vector<type_3E74C0 *>::iterator var_C = unk_0C.end();
    RwInt32 var_4 = 0;

    while (var_8 != var_C && var_4 != unk_F4)
    {
        type_3E74C0 *var_24 = *var_8;
        var_20.unk_00 = unk_104.unk_00;
        var_20.unk_08 = unk_104.unk_00;
        for (RwUInt32 var_28 = 0; var_28 < var_10; ++var_28)
        {
            RwUInt32 var_2C = unk_100->unk_0C[var_28].unk_00;
            var_20.unk_08 += (RwReal)var_2C;
            var_24->sub_1EC370(&var_20, var_28);
            var_20.unk_00 += (RwReal)var_2C;
        }
        var_20.unk_04 += unk_F0;
        var_20.unk_0C += unk_F0;
        ++var_8;
        ++var_4;
    }
    unk_115 = false;
}

// match: ?sub_1EA410@type_3E7490@kujuUI@@QAE_NXZ @ 0x001EA410
bool type_3E7490::sub_1EA410()
{
    return unk_FC != -1;
}

// match: ?sub_1EA430@type_3E7490@kujuUI@@QAEXH@Z @ 0x001EA430
void type_3E7490::sub_1EA430(RwInt32 arg_0)
{
    switch (arg_0)
    {
    case 2:
        sub_1EA540();
        unk_504210.sub_1EF120();
        unk_504210.unk_08 = false;
        break;
    case 3:
        sub_1EA5E0();
        unk_504210.sub_1EF120();
        unk_504210.unk_08 = true;
        break;
    case 8:
        sub_1EA6C0();
        break;
    case 9:
        sub_1EA7B0();
        break;
    case 4:
        unk_100->vf_010();
        if (dword_504378)
            dword_504378->vf_04(2);
        break;
    case 7:
        unk_100->vf_014();
        if (dword_504378)
            dword_504378->vf_04(3);
        break;
    }
}

// match: ?sub_1EA540@type_3E7490@kujuUI@@QAEXXZ @ 0x001EA540
void type_3E7490::sub_1EA540()
{
    if (unk_FC)
    {
        if (unk_FC == unk_F8)
        {
            --unk_F8;
            unk_115 = true;
        }
        sub_1EA910(unk_FC - 1);
        unk_100->vf_008();
        if (dword_504378)
            dword_504378->vf_04(1);
    }
}

// match: ?sub_1EA5E0@type_3E7490@kujuUI@@QAEXXZ @ 0x001EA5E0
void type_3E7490::sub_1EA5E0()
{
    if (unk_FC != unk_0C.size() - 1)
    {
        if (unk_FC == unk_F8 + unk_F4 - 1)
        {
            ++unk_F8;
            unk_115 = true;
        }
        sub_1EA910(unk_FC + 1);
        unk_100->vf_008();
        if (dword_504378)
            dword_504378->vf_04(1);
    }
}

// match: ?sub_1EA6C0@type_3E7490@kujuUI@@QAEXXZ @ 0x001EA6C0
void type_3E7490::sub_1EA6C0()
{
    RwInt32 var_4 = std::max(unk_FC - unk_F4, 0);
    sub_1EA910(var_4);
    if (unk_0C.size() > unk_F4)
    {
        RwInt32 var_8 = std::max(unk_F8 - unk_F4, 0);
        unk_F8 = var_8;
        unk_115 = true;
    }
}

// match: ?sub_1EA7B0@type_3E7490@kujuUI@@QAEXXZ @ 0x001EA7B0
void type_3E7490::sub_1EA7B0()
{
    RwUInt32 var_4 = std::min((RwUInt32)(unk_FC + unk_F4), unk_0C.size() - 1);
    sub_1EA910(var_4);
    if (unk_0C.size() > unk_F4)
    {
        RwUInt32 var_8 = std::min((RwUInt32)(unk_F8 + unk_F4), unk_0C.size() - unk_F4);
        unk_F8 = var_8;
        unk_115 = true;
    }
}

// match: ?sub_1EA910@type_3E7490@kujuUI@@QAEXH@Z @ 0x001EA910
void type_3E7490::sub_1EA910(RwInt32 arg_0)
{
    if (sub_1EA410())
        sub_1EB020()->sub_1EC250(0);
    unk_FC = arg_0;
    if (arg_0 != -1)
        sub_1EB020()->sub_1EC250(sub_1F7720() ? 1 : 2);
}

// match: ?sub_1EA980@type_3E7490@kujuUI@@QAEXPAUtype_3E74C0@2@H@Z @ 0x001EA980
void type_3E7490::sub_1EA980(type_3E74C0 *arg_0, RwInt32 arg_4)
{
    std::vector<type_3E74C0 *>::iterator var_4 = arg_4 == 0 ? unk_0C.begin() : unk_0C.begin() + arg_4;
    unk_0C.insert(var_4, arg_0);
    arg_0->sub_1EBFA0(this);
    if (sub_1EA410() && arg_4 <= unk_FC)
        ++unk_FC;
    unk_115 = true;
}

// match: ?sub_1EAA50@type_3E7490@kujuUI@@QAEXH@Z @ 0x001EAA50
void type_3E7490::sub_1EAA50(RwInt32 arg_0)
{
    std::vector<type_3E74C0 *>::iterator var_4 = unk_0C.begin() + arg_0;
    (*var_4)->sub_1EC110();
    unk_0C.erase(var_4);
    if (unk_FC > arg_0)
        --unk_FC;
    if (arg_0 < unk_F8)
        --unk_F8;
    unk_115 = true;
}

// match: ?sub_1EAB50@type_3E7490@kujuUI@@QAEXPAUtype_3E74C0@2@@Z @ 0x001EAB50
void type_3E7490::sub_1EAB50(type_3E74C0 *arg_0)
{
    for (RwUInt32 var_4 = 0; unk_0C.size(); ++var_4)
    {
        if (unk_0C[var_4] == arg_0)
        {
            sub_1EAA50(var_4);
            break;
        }
    }
}

// match: ?sub_1EABF0@type_3E7490@kujuUI@@QAEXI@Z @ 0x001EABF0
void type_3E7490::sub_1EABF0(RwUInt32 arg_0)
{
    unk_0C.reserve(arg_0);
}

// match: ?sub_1EAC10@type_3E7490@kujuUI@@QAEHXZ @ 0x001EAC10
RwInt32 type_3E7490::sub_1EAC10()
{
    return unk_EC;
}

// match: ?givenFocus@type_3E7490@kujuUI@@UAEXXZ @ 0x001EAC30
void type_3E7490::givenFocus()
{
    unk_20.sub_1E3B20(1);
    if (sub_1EA410())
        sub_1EB020()->sub_1EC250(1);
    else if (!(unk_0C.size() == 0))
    {
        unk_FC = 0;
        if (unk_F8)
        {
            unk_F8 = 0;
            unk_115 = true;
        }
        sub_1EB020()->sub_1EC250(1);
    }
}

// match: ?lostFocus@type_3E7490@kujuUI@@UAEXXZ @ 0x001EACF0
void type_3E7490::lostFocus()
{
    unk_20.sub_1E3B20(unk_100->vf_00C() ? 0 : 3);
    if (sub_1EA410())
        sub_1EB020()->sub_1EC250(unk_100->vf_00C() ? 2 : 4);
    if (unk_504210.sub_1EF160())
        unk_504210.sub_1EF140();
}

// match: ?vf_010@type_3E7490@kujuUI@@UAE_NXZ @ 0x001EAD90
bool type_3E7490::vf_010()
{
    if (unk_100)
        return unk_114 || unk_100->vf_00C();
    return unk_114;
}

// match: ?vf_014@type_3E7490@kujuUI@@UAEXM@Z @ 0x001EAE00
void type_3E7490::vf_014(RwReal arg_0)
{
    if (unk_504210.sub_1EF160() && sub_1F7720() && unk_504210.sub_1EF090(arg_0))
    {
        if (unk_504210.unk_08)
            sub_1EA5E0();
        else
            sub_1EA540();
    }
}

// match: ?vf_018@type_3E7490@kujuUI@@UAEXPAUtype_1E4130@2@@Z @ 0x001EAE60
void type_3E7490::vf_018(type_1E4130 *arg_0)
{
    if (unk_115)
        sub_1EA260();
    unk_20.sub_1E3950(arg_0);
    RwUInt32 var_4 = std::min(unk_0C.size(), (RwUInt32)(unk_F8 + unk_F4));
    for (RwUInt32 var_8 = unk_F8; var_8 != var_4; ++var_8)
        unk_0C[var_8]->sub_1EC2F0(arg_0);
}

// match: ?processEvent@type_3E7490@kujuUI@@UAE?AW4eEventWasHandled@2@ABVcStateChange@2@@Z @ 0x001EAF60
eEventWasHandled type_3E7490::processEvent(const cStateChange &arg_0)
{
    eEventWasHandled var_4 = (eEventWasHandled)1;

    switch (arg_0.get_unk_00())
    {
    case 2:
    case 3:
    case 4:
    case 7:
    case 8:
    case 9:
        var_4 = (eEventWasHandled)0;
    case 5:
    case 6:
        if (sub_1EA410() && var_4 == 0)
        {
            if (unk_504210.sub_1EF160())
                unk_504210.sub_1EF140();
            if (arg_0.get_unk_04() == 0)
                sub_1EA430(arg_0.get_unk_00());
        }
        break;
    }
    return var_4;
}

// match: ?sub_1EB020@type_3E7490@kujuUI@@QAEPAUtype_3E74C0@2@XZ @ 0x001EB020
type_3E74C0 *type_3E7490::sub_1EB020()
{
    return unk_0C[unk_FC];
}

// match: ?sub_1EB070@type_3E7490@kujuUI@@QAEPAV?$vector@PAUtype_3E74C0@kujuUI@@V?$allocator@PAUtype_3E74C0@kujuUI@@@std@@@std@@XZ @ 0x001EB070
std::vector<type_3E74C0 *> *type_3E7490::sub_1EB070()
{
    return &unk_0C;
}

// match: ?sub_1EB090@type_3E7490@kujuUI@@QAEIXZ @ 0x001EB090
RwUInt32 type_3E7490::sub_1EB090()
{
    return unk_100->sub_FB710();
}

// match: ?sub_1EB0B0@type_3E7490@kujuUI@@QAEXH@Z @ 0x001EB0B0
void type_3E7490::sub_1EB0B0(RwInt32 arg_0)
{
    sub_1EA910(arg_0);
}

// match: ?sub_1EB0D0@type_3E7490@kujuUI@@QAEXXZ @ 0x001EB0D0
void type_3E7490::sub_1EB0D0()
{
    if (sub_1EA410())
        sub_1EB020()->sub_1EC250(0);
    unk_FC = -1;
}

// match: ?sub_1EB110@type_3E7490@kujuUI@@QAEHI@Z @ 0x001EB110
RwInt32 type_3E7490::sub_1EB110(RwUInt32 arg_0)
{
    RwInt32 var_4 = unk_100->unk_0C[arg_0].unk_04;
    return var_4;
}

// match: ?sub_1EB140@type_3E7490@kujuUI@@QAEXXZ @ 0x001EB140
void type_3E7490::sub_1EB140()
{
    unk_115 = true;
}

// match: ?sub_1EB160@type_3E7490@kujuUI@@QAEXXZ @ 0x001EB160
void type_3E7490::sub_1EB160()
{
    for (std::vector<type_3E74C0 *>::iterator var_4 = unk_0C.begin(); var_4 != unk_0C.end(); ++var_4)
        (*var_4)->sub_1EC110();
    unk_0C.clear();
    unk_F8 = 0;
    unk_FC = -1;
    unk_115 = true;
}

// match: ?sub_1EB1F0@type_3E7490@kujuUI@@QAEHXZ @ 0x001EB1F0
RwInt32 type_3E7490::sub_1EB1F0()
{
    return unk_FC;
}

// match: ?sub_1EB210@type_3E7490@kujuUI@@QAEXH@Z @ 0x001EB210
void type_3E7490::sub_1EB210(RwInt32 arg_0)
{
    if (unk_F4 > unk_0C.size())
        unk_F8 = 0;
    else
        unk_F8 = arg_0;
    unk_115 = true;
}

// match: ?sub_1EB280@type_3E7490@kujuUI@@QAEHXZ @ 0x001EB280
RwInt32 type_3E7490::sub_1EB280()
{
    return unk_F8;
}

// match: ?vf_020@type_3E7490@kujuUI@@UAE?AUtype_1E0330_rect@2@XZ @ 0x001EB2A0
type_1E0330_rect type_3E7490::vf_020()
{
    return unk_104;
}
}
