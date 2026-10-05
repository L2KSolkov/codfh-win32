/*
 * kujuUI's layout page (game/kujuui.h, \COD\SHARED\UI\cLayoutPage.cpp): a
 * container whose widgets the pad's buttons move the focus between, along
 * the links in a std::set (whose instances follow).
 */
#include "game/kujuui.h"
#include "game/assert.h"
#include "game/frontend.h"

namespace kujuUI {

// match: ??0cLayoutPage@kujuUI@@QAE@PAUtype_3E7D08@1@@Z @ 0x001E8350
cLayoutPage::cLayoutPage(type_3E7D08 *arg_0) : type_3E7584(arg_0)
{
    unk_28 = 0;
    unk_2C = 0;
    unk_30 = 14;
    unk_34 = false;
}

// match: ??_GcLayoutPage@kujuUI@@UAEPAXI@Z @ 0x001E83E0

// match: ??1cLayoutPage@kujuUI@@UAE@XZ @ 0x001E8410
cLayoutPage::~cLayoutPage()
{
}

// match: ?processEvent@cLayoutPage@kujuUI@@UAE?AW4eEventWasHandled@2@ABVcStateChange@2@@Z @ 0x001E8470
eEventWasHandled cLayoutPage::processEvent(const cStateChange &arg_0)
{
    eEventWasHandled var_4 = (eEventWasHandled)1;

    if (unk_28 && (held() || unk_28->processEvent(arg_0)) && unk_28)
    {
        var_4 = sub_1E8550(arg_0);
        if (arg_0.get_unk_04() == 0)
        {
            unk_30 = arg_0.get_unk_00();
            if (unk_504210.sub_1EF160())
                unk_504210.sub_1EF140();
            unk_504210.sub_1EF120();
        }
        else
        {
            unk_30 = 14;
            if (unk_504210.sub_1EF160())
                unk_504210.sub_1EF140();
        }
    }
    return var_4;
}

// match: ?sub_1E8550@cLayoutPage@kujuUI@@QAE?AW4eEventWasHandled@2@ABVcStateChange@2@@Z @ 0x001E8550
eEventWasHandled cLayoutPage::sub_1E8550(const cStateChange &arg_0)
{
    type_3E7D08 *var_10 = unk_28;
    RwUInt32 var_18 = 0;
    eEventWasHandled var_14 = (eEventWasHandled)1;

    if (arg_0.get_unk_04() == 0)
    {
        do
        {
            type_1F8040 var_24(var_10, arg_0.get_unk_00());
            std::set<type_1F8040>::iterator var_28 = unk_1C.find(var_24);
            if (var_28 != unk_1C.end())
            {
                var_10 = var_28->sub_1E3480();
                var_14 = (eEventWasHandled)0;
            }
            ++var_18;
            if (var_18 > 10)
                var_10 = unk_28;
        } while (var_10 && !var_10->vf_010());
        if (var_10 != unk_28)
        {
            unk_28->sub_1F77B0();
            unk_28 = var_10;
            unk_28->sub_1F7790();
            if (dword_504378)
                dword_504378->vf_04(0);
        }
    }
    else
    {
        type_1F8040 var_34(var_10, arg_0.get_unk_00());
        std::set<type_1F8040>::iterator var_38 = unk_1C.find(var_34);
        if (var_38 != unk_1C.end())
            var_14 = (eEventWasHandled)0;
    }
    return var_14;
}

// match: ?givenFocus@cLayoutPage@kujuUI@@UAEXXZ @ 0x001E8750
void cLayoutPage::givenFocus()
{
    if (!unk_28)
    {
        unk_28 = unk_2C;
        focusAvailableWidget();
        if (unk_28)
            unk_28->sub_1F7790();
    }
}

// match: ?lostFocus@cLayoutPage@kujuUI@@UAEXXZ @ 0x001E8790
void cLayoutPage::lostFocus()
{
    if (unk_28)
    {
        if (unk_34)
            unk_2C = unk_28;
        unk_28->sub_1F77B0();
        unk_28 = 0;
        if (unk_504210.sub_1EF160())
        {
            unk_504210.sub_1EF140();
            unk_30 = 14;
        }
    }
}

// match: ?vf_034@cLayoutPage@kujuUI@@UAE_NPAUtype_3E7D08@2@@Z @ 0x001E8800
bool cLayoutPage::vf_034(type_3E7D08 *arg_0)
{
    return unk_28 == arg_0;
}

// match: ?vf_030@cLayoutPage@kujuUI@@UAEXXZ @ 0x001E8820
void cLayoutPage::vf_030()
{
    type_3E7D08 *var_4 = unk_28;
    if (var_4)
    {
        focusAvailableWidget();
        if (var_4 != unk_28)
        {
            var_4->sub_1F77B0();
            unk_28->sub_1F7790();
        }
    }
}

// match: ?focusAvailableWidget@cLayoutPage@kujuUI@@QAEXXZ @ 0x001E8870
void cLayoutPage::focusAvailableWidget()
{
    while (unk_28 && !unk_28->vf_010())
    {
        type_1F8040 var_18(unk_28, 14);
        std::set<type_1F8040>::iterator var_1C = unk_1C.find(var_18);
#line 207 "\\COD\\SHARED\\UI\\cLayoutPage.cpp"
        sub_1C7F20(var_1C != unk_1C.end(), __FILE__, __LINE__, __FUNCSIG__, 0);
        unk_28 = var_1C->sub_1E3480();
#line 209 "\\COD\\SHARED\\UI\\cLayoutPage.cpp"
        sub_1C7F20(unk_28 != 0, __FILE__, __LINE__, __FUNCSIG__, 0);
    }
}

// match: ?sub_1E8980@cLayoutPage@kujuUI@@QAEXPAUtype_3E7D08@2@0H@Z @ 0x001E8980
void cLayoutPage::sub_1E8980(type_3E7D08 *arg_0, type_3E7D08 *arg_4, RwInt32 arg_8)
{
    std::pair<std::set<type_1F8040>::iterator, bool> var_14 = unk_1C.insert(type_1F8040(arg_0, arg_4, arg_8));
    if (!var_14.second)
        var_14.first->sub_1E7540(arg_4);
}

// match: ?sub_1E8A20@cLayoutPage@kujuUI@@QAEXPAUtype_3E7D08@2@@Z @ 0x001E8A20
void cLayoutPage::sub_1E8A20(type_3E7D08 *arg_0)
{
    sub_1ED9D0(arg_0);
}

// match: ?sub_1E8A40@cLayoutPage@kujuUI@@QAEXPAUtype_3E7D08@2@@Z @ 0x001E8A40
void cLayoutPage::sub_1E8A40(type_3E7D08 *arg_0)
{
    while (arg_0 && !arg_0->vf_010())
    {
        type_1F8040 var_1C(arg_0, 14);
        std::set<type_1F8040>::iterator var_10 = unk_1C.find(var_1C);
        if (var_10 == unk_1C.end())
            arg_0 = 0;
        else
            arg_0 = var_10->sub_1E3480();
    }
    unk_2C = arg_0;
    if (sub_1F7720() && !unk_28 && arg_0->vf_010())
    {
        unk_28 = unk_2C;
        unk_28->sub_1F7790();
    }
}

// match: ?sub_1E8B50@cLayoutPage@kujuUI@@QAEXPAUtype_3E7D08@2@@Z @ 0x001E8B50
void cLayoutPage::sub_1E8B50(type_3E7D08 *arg_0)
{
    if (arg_0 != unk_28)
    {
        if (unk_28)
            unk_28->sub_1F77B0();
        unk_28 = arg_0;
        if (arg_0)
        {
            focusAvailableWidget();
            if (unk_28)
                unk_28->sub_1F7790();
        }
    }
}

// match: ?sub_1E8BB0@cLayoutPage@kujuUI@@QAE_NXZ @ 0x001E8BB0
bool cLayoutPage::sub_1E8BB0()
{
    return unk_2C != 0;
}

// match: ?vf_014@cLayoutPage@kujuUI@@UAEXM@Z @ 0x001E8BD0
void cLayoutPage::vf_014(RwReal arg_0)
{
    type_3E7584::vf_014(arg_0);
    if (unk_30 != 14 && unk_504210.sub_1EF090(arg_0))
    {
        cStateChange var_8 = {unk_30, 0};
        sub_1E8550(var_8);
    }
}

// match: ?sub_1E8C30@cLayoutPage@kujuUI@@QAEX_N@Z @ 0x001E8C30
void cLayoutPage::sub_1E8C30(bool arg_0)
{
    unk_34 = arg_0;
}

// match: ?sub_1E8C50@cLayoutPage@kujuUI@@QAEPAUtype_3E7D08@2@XZ @ 0x001E8C50
type_3E7D08 *cLayoutPage::sub_1E8C50()
{
    return unk_28;
}
}
