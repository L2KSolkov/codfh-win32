/*
 * kujuUI's layout page (game/kujuui.h, \COD\SHARED\UI\cLayoutPage.cpp): a
 * container whose widgets the pad's buttons move the focus between, along
 * the links in a std::set (whose instances follow).
 */
#include "game/kujuui.h"
#include "game/assert.h"
#include "game/frontend.h"

namespace kujuUI {

// Vtables (.rdata, PLAN M5): each in its own placement range (config/splits.txt).
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_7cLayoutPage@kujuUI@@6B@ @ 0x003E73F8
// match: ??_C@_0BP@GNONCFML@?2COD?2SHARED?2UI?2cLayoutPage?4cpp?$AA@ @ 0x003E7430
// match: ??_C@_0EA@HMMKCHAP@void?5__thiscall?5kujuUI?3?3cLayoutP@ @ 0x003E7450
// match: __ehhandler$??0cLayoutPage@kujuUI@@QAE@PAUtype_3E7D08@1@@Z>1>8 @ 0x004202A4
// match: __ehhandler$??0cLayoutPage@kujuUI@@QAE@PAUtype_3E7D08@1@@Z>1 @ 0x004202AC
// match: __ehhandler$??1cLayoutPage@kujuUI@@UAE@XZ>1>8 @ 0x004202C8
// match: __ehhandler$??1cLayoutPage@kujuUI@@UAE@XZ>1 @ 0x004202D0
// match: __ehhandler$?sub_1E8550@cLayoutPage@kujuUI@@QAE?AW4eEventWasHandled@2@ABVcStateChange@2@@Z>1>8 @ 0x004202EC
// match: __ehhandler$?sub_1E8550@cLayoutPage@kujuUI@@QAE?AW4eEventWasHandled@2@ABVcStateChange@2@@Z>1 @ 0x004202FC
// match: __ehhandler$?focusAvailableWidget@cLayoutPage@kujuUI@@QAEXXZ>1>8 @ 0x00420318
// match: __ehhandler$?focusAvailableWidget@cLayoutPage@kujuUI@@QAEXXZ>1 @ 0x00420320
// match: __ehhandler$?sub_1E8980@cLayoutPage@kujuUI@@QAEXPAUtype_3E7D08@2@0H@Z>1>8 @ 0x0042033C
// match: __ehhandler$?sub_1E8980@cLayoutPage@kujuUI@@QAEXPAUtype_3E7D08@2@0H@Z>1 @ 0x00420344
// match: __ehhandler$?sub_1E8A40@cLayoutPage@kujuUI@@QAEXPAUtype_3E7D08@2@@Z>1>8 @ 0x00420360
// match: __ehhandler$?sub_1E8A40@cLayoutPage@kujuUI@@QAEXPAUtype_3E7D08@2@@Z>1 @ 0x00420368
// match: __ehhandler$?erase@?$_Tree@V?$_Tset_traits@Utype_1F8040@kujuUI@@U?$less@Utype_1F8040@kujuUI@@@std@@V?$allocator@Utype_1F8040@kujuUI@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z>1>8 @ 0x00420384
// match: __ehhandler$?erase@?$_Tree@V?$_Tset_traits@Utype_1F8040@kujuUI@@U?$less@Utype_1F8040@kujuUI@@@std@@V?$allocator@Utype_1F8040@kujuUI@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z>1 @ 0x0042038C
// match: __ehhandler$?_Insert@?$_Tree@V?$_Tset_traits@Utype_1F8040@kujuUI@@U?$less@Utype_1F8040@kujuUI@@@std@@V?$allocator@Utype_1F8040@kujuUI@@@4@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tset_traits@Utype_1F8040@kujuUI@@U?$less@Utype_1F8040@kujuUI@@@std@@V?$allocator@Utype_1F8040@kujuUI@@@4@$0A@@std@@@2@ABUtype_1F8040@kujuUI@@@Z>1>8 @ 0x004203A8
// match: __ehhandler$?_Insert@?$_Tree@V?$_Tset_traits@Utype_1F8040@kujuUI@@U?$less@Utype_1F8040@kujuUI@@@std@@V?$allocator@Utype_1F8040@kujuUI@@@4@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tset_traits@Utype_1F8040@kujuUI@@U?$less@Utype_1F8040@kujuUI@@@std@@V?$allocator@Utype_1F8040@kujuUI@@@4@$0A@@std@@@2@ABUtype_1F8040@kujuUI@@@Z>1 @ 0x004203B0
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tset_traits@Utype_1F8040@kujuUI@@U?$less@Utype_1F8040@kujuUI@@@std@@V?$allocator@Utype_1F8040@kujuUI@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tset_traits@Utype_1F8040@kujuUI@@U?$less@Utype_1F8040@kujuUI@@@std@@V?$allocator@Utype_1F8040@kujuUI@@@4@$0A@@std@@@2@PAU342@00ABUtype_1F8040@kujuUI@@D@Z>1>8 @ 0x004203CC
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tset_traits@Utype_1F8040@kujuUI@@U?$less@Utype_1F8040@kujuUI@@@std@@V?$allocator@Utype_1F8040@kujuUI@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tset_traits@Utype_1F8040@kujuUI@@U?$less@Utype_1F8040@kujuUI@@@std@@V?$allocator@Utype_1F8040@kujuUI@@@4@$0A@@std@@@2@PAU342@00ABUtype_1F8040@kujuUI@@D@Z>1>16>16 @ 0x004203DC
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tset_traits@Utype_1F8040@kujuUI@@U?$less@Utype_1F8040@kujuUI@@@std@@V?$allocator@Utype_1F8040@kujuUI@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tset_traits@Utype_1F8040@kujuUI@@U?$less@Utype_1F8040@kujuUI@@@std@@V?$allocator@Utype_1F8040@kujuUI@@@4@$0A@@std@@@2@PAU342@00ABUtype_1F8040@kujuUI@@D@Z>1>16 @ 0x004203EC
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tset_traits@Utype_1F8040@kujuUI@@U?$less@Utype_1F8040@kujuUI@@@std@@V?$allocator@Utype_1F8040@kujuUI@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tset_traits@Utype_1F8040@kujuUI@@U?$less@Utype_1F8040@kujuUI@@@std@@V?$allocator@Utype_1F8040@kujuUI@@@4@$0A@@std@@@2@PAU342@00ABUtype_1F8040@kujuUI@@D@Z>1 @ 0x00420400
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tset_traits@Utype_1F8040@kujuUI@@U?$less@Utype_1F8040@kujuUI@@@std@@V?$allocator@Utype_1F8040@kujuUI@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tset_traits@Utype_1F8040@kujuUI@@U?$less@Utype_1F8040@kujuUI@@@std@@V?$allocator@Utype_1F8040@kujuUI@@@4@$0A@@std@@@2@XZ>1>8 @ 0x0042041C
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tset_traits@Utype_1F8040@kujuUI@@U?$less@Utype_1F8040@kujuUI@@@std@@V?$allocator@Utype_1F8040@kujuUI@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tset_traits@Utype_1F8040@kujuUI@@U?$less@Utype_1F8040@kujuUI@@@std@@V?$allocator@Utype_1F8040@kujuUI@@@4@$0A@@std@@@2@XZ>1>16>16 @ 0x0042042C
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tset_traits@Utype_1F8040@kujuUI@@U?$less@Utype_1F8040@kujuUI@@@std@@V?$allocator@Utype_1F8040@kujuUI@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tset_traits@Utype_1F8040@kujuUI@@U?$less@Utype_1F8040@kujuUI@@@std@@V?$allocator@Utype_1F8040@kujuUI@@@4@$0A@@std@@@2@XZ>1>16 @ 0x0042043C
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tset_traits@Utype_1F8040@kujuUI@@U?$less@Utype_1F8040@kujuUI@@@std@@V?$allocator@Utype_1F8040@kujuUI@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tset_traits@Utype_1F8040@kujuUI@@U?$less@Utype_1F8040@kujuUI@@@std@@V?$allocator@Utype_1F8040@kujuUI@@@4@$0A@@std@@@2@XZ>1 @ 0x00420450

// match: ??0cLayoutPage@kujuUI@@QAE@PAUtype_3E7D08@1@@Z @ 0x001E8350
// match: __ehhandler$??0cLayoutPage@kujuUI@@QAE@PAUtype_3E7D08@1@@Z-0x8 @ 0x00303CD0
// match: __ehhandler$??0cLayoutPage@kujuUI@@QAE@PAUtype_3E7D08@1@@Z @ 0x00303CD8

cLayoutPage::cLayoutPage(type_3E7D08 *arg_0) : type_3E7584(arg_0)
{
    unk_28 = 0;
    unk_2C = 0;
    unk_30 = 14;
    unk_34 = false;
}

// match: ??_GcLayoutPage@kujuUI@@UAEPAXI@Z @ 0x001E83E0

// match: ??1cLayoutPage@kujuUI@@UAE@XZ @ 0x001E8410
// match: __ehhandler$??1cLayoutPage@kujuUI@@UAE@XZ-0x8 @ 0x00303CF0
// match: __ehhandler$??1cLayoutPage@kujuUI@@UAE@XZ @ 0x00303CF8
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
// match: __ehhandler$?sub_1E8550@cLayoutPage@kujuUI@@QAE?AW4eEventWasHandled@2@ABVcStateChange@2@@Z-0x10 @ 0x00303D10
// match: __ehhandler$?sub_1E8550@cLayoutPage@kujuUI@@QAE?AW4eEventWasHandled@2@ABVcStateChange@2@@Z @ 0x00303D20
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
eEventWasHandled cLayoutPage::sub_1E8550(const cStateChange &arg_0)
{
    type_3E7D08 *lv_10 = unk_28;
    RwUInt32 var_18 = 0;
    eEventWasHandled var_14 = (eEventWasHandled)1;

    if (arg_0.get_unk_04() == 0)
    {
        do
        {
            type_1F8040 frm_24(lv_10, arg_0.get_unk_00());
            std::set<type_1F8040>::iterator var_28 = unk_1C.find(frm_24);
            if (var_28 != unk_1C.end())
            {
                lv_10 = var_28->sub_1E3480();
                var_14 = (eEventWasHandled)0;
            }
            ++var_18;
            if (var_18 > 10)
                lv_10 = unk_28;
        } while (lv_10 && !lv_10->vf_010());
        if (lv_10 != unk_28)
        {
            unk_28->sub_1F77B0();
            unk_28 = lv_10;
            unk_28->sub_1F7790();
            if (dword_504378)
                dword_504378->vf_04(0);
        }
    }
    else
    {
        type_1F8040 var_34(lv_10, arg_0.get_unk_00());
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
// match: __ehhandler$?focusAvailableWidget@cLayoutPage@kujuUI@@QAEXXZ-0x8 @ 0x00303D30
// match: __ehhandler$?focusAvailableWidget@cLayoutPage@kujuUI@@QAEXXZ @ 0x00303D38
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
// match: __ehhandler$?sub_1E8980@cLayoutPage@kujuUI@@QAEXPAUtype_3E7D08@2@0H@Z-0x8 @ 0x00303D50
// match: __ehhandler$?sub_1E8980@cLayoutPage@kujuUI@@QAEXPAUtype_3E7D08@2@0H@Z @ 0x00303D58
void cLayoutPage::sub_1E8980(type_3E7D08 *arg_0, type_3E7D08 *arg_4, RwInt32 arg_8)
{
    std::pair<std::set<type_1F8040>::iterator, bool> var_14 = unk_1C.insert(type_1F8040(arg_0, arg_4, arg_8));
    if (!var_14.second)
    {
        type_1F8040 *var_18 = &*var_14.first;
        var_18->sub_1E7540(arg_4);
    }
}

// match: ?sub_1E8A20@cLayoutPage@kujuUI@@QAEXPAUtype_3E7D08@2@@Z @ 0x001E8A20
void cLayoutPage::sub_1E8A20(type_3E7D08 *arg_0)
{
    sub_1ED9D0(arg_0);
}

// match: ?sub_1E8A40@cLayoutPage@kujuUI@@QAEXPAUtype_3E7D08@2@@Z @ 0x001E8A40
// match: __ehhandler$?sub_1E8A40@cLayoutPage@kujuUI@@QAEXPAUtype_3E7D08@2@@Z-0x8 @ 0x00303D70
// match: __ehhandler$?sub_1E8A40@cLayoutPage@kujuUI@@QAEXPAUtype_3E7D08@2@@Z @ 0x00303D78
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void cLayoutPage::sub_1E8A40(type_3E7D08 *arg_0)
{
    while (arg_0 && !arg_0->vf_010())
    {
        type_1F8040 var_1C(arg_0, 14);
        std::set<type_1F8040>::iterator local_10 = unk_1C.find(var_1C);
        if (local_10 == unk_1C.end())
            arg_0 = 0;
        else
            arg_0 = local_10->sub_1E3480();
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
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void cLayoutPage::vf_014(RwReal arg_0)
{
    type_3E7584::vf_014(arg_0);
    if (unk_30 != 14 && unk_504210.sub_1EF090(arg_0))
    {
        RwInt32 var_C = unk_30;
        cStateChange bp_8(var_C, 0);
        sub_1E8550(bp_8);
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

// The links' set's instances.
// match: ?insert@?$_Tree@V?$_Tset_traits@Utype_1F8040@kujuUI@@U?$less@Utype_1F8040@kujuUI@@@std@@V?$allocator@Utype_1F8040@kujuUI@@@4@$0A@@std@@@std@@QAE?AU?$pair@Viterator@?$_Tree@V?$_Tset_traits@Utype_1F8040@kujuUI@@U?$less@Utype_1F8040@kujuUI@@@std@@V?$allocator@Utype_1F8040@kujuUI@@@4@$0A@@std@@@std@@_N@2@ABUtype_1F8040@kujuUI@@@Z @ 0x001E8C70
// match: ?erase@?$_Tree@V?$_Tset_traits@Utype_1F8040@kujuUI@@U?$less@Utype_1F8040@kujuUI@@@std@@V?$allocator@Utype_1F8040@kujuUI@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z @ 0x001E8E00
// match: __ehhandler$?erase@?$_Tree@V?$_Tset_traits@Utype_1F8040@kujuUI@@U?$less@Utype_1F8040@kujuUI@@@std@@V?$allocator@Utype_1F8040@kujuUI@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z-0x8 @ 0x00303D90
// match: __ehhandler$?erase@?$_Tree@V?$_Tset_traits@Utype_1F8040@kujuUI@@U?$less@Utype_1F8040@kujuUI@@@std@@V?$allocator@Utype_1F8040@kujuUI@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z @ 0x00303D98
// match: ?find@?$_Tree@V?$_Tset_traits@Utype_1F8040@kujuUI@@U?$less@Utype_1F8040@kujuUI@@@std@@V?$allocator@Utype_1F8040@kujuUI@@@4@$0A@@std@@@std@@QAE?AViterator@12@ABUtype_1F8040@kujuUI@@@Z @ 0x001E93A0
// match: ?_Insert@?$_Tree@V?$_Tset_traits@Utype_1F8040@kujuUI@@U?$less@Utype_1F8040@kujuUI@@@std@@V?$allocator@Utype_1F8040@kujuUI@@@4@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tset_traits@Utype_1F8040@kujuUI@@U?$less@Utype_1F8040@kujuUI@@@std@@V?$allocator@Utype_1F8040@kujuUI@@@4@$0A@@std@@@2@ABUtype_1F8040@kujuUI@@@Z @ 0x001E9440
// match: __ehhandler$?_Insert@?$_Tree@V?$_Tset_traits@Utype_1F8040@kujuUI@@U?$less@Utype_1F8040@kujuUI@@@std@@V?$allocator@Utype_1F8040@kujuUI@@@4@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tset_traits@Utype_1F8040@kujuUI@@U?$less@Utype_1F8040@kujuUI@@@std@@V?$allocator@Utype_1F8040@kujuUI@@@4@$0A@@std@@@2@ABUtype_1F8040@kujuUI@@@Z-0x8 @ 0x00303DB0
// match: __ehhandler$?_Insert@?$_Tree@V?$_Tset_traits@Utype_1F8040@kujuUI@@U?$less@Utype_1F8040@kujuUI@@@std@@V?$allocator@Utype_1F8040@kujuUI@@@4@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tset_traits@Utype_1F8040@kujuUI@@U?$less@Utype_1F8040@kujuUI@@@std@@V?$allocator@Utype_1F8040@kujuUI@@@4@$0A@@std@@@2@ABUtype_1F8040@kujuUI@@@Z @ 0x00303DB8
// match: ?_Lrotate@?$_Tree@V?$_Tset_traits@Utype_1F8040@kujuUI@@U?$less@Utype_1F8040@kujuUI@@@std@@V?$allocator@Utype_1F8040@kujuUI@@@4@$0A@@std@@@std@@IAEXPAU_Node@?$_Tree_nod@V?$_Tset_traits@Utype_1F8040@kujuUI@@U?$less@Utype_1F8040@kujuUI@@@std@@V?$allocator@Utype_1F8040@kujuUI@@@4@$0A@@std@@@2@@Z @ 0x001E9790
// match: ?_Rrotate@?$_Tree@V?$_Tset_traits@Utype_1F8040@kujuUI@@U?$less@Utype_1F8040@kujuUI@@@std@@V?$allocator@Utype_1F8040@kujuUI@@@4@$0A@@std@@@std@@IAEXPAU_Node@?$_Tree_nod@V?$_Tset_traits@Utype_1F8040@kujuUI@@U?$less@Utype_1F8040@kujuUI@@@std@@V?$allocator@Utype_1F8040@kujuUI@@@4@$0A@@std@@@2@@Z @ 0x001E9840
// match: ?_Tidy@?$_Tree@V?$_Tset_traits@Utype_1F8040@kujuUI@@U?$less@Utype_1F8040@kujuUI@@@std@@V?$allocator@Utype_1F8040@kujuUI@@@4@$0A@@std@@@std@@IAEXXZ @ 0x001E98F0
// match: ?erase@?$_Tree@V?$_Tset_traits@Utype_1F8040@kujuUI@@U?$less@Utype_1F8040@kujuUI@@@std@@V?$allocator@Utype_1F8040@kujuUI@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@0@Z @ 0x001E9970
// match: ?_Init@?$_Tree@V?$_Tset_traits@Utype_1F8040@kujuUI@@U?$less@Utype_1F8040@kujuUI@@@std@@V?$allocator@Utype_1F8040@kujuUI@@@4@$0A@@std@@@std@@IAEXXZ @ 0x001E9A40
// match: ?_Lbound@?$_Tree@V?$_Tset_traits@Utype_1F8040@kujuUI@@U?$less@Utype_1F8040@kujuUI@@@std@@V?$allocator@Utype_1F8040@kujuUI@@@4@$0A@@std@@@std@@IBEPAU_Node@?$_Tree_nod@V?$_Tset_traits@Utype_1F8040@kujuUI@@U?$less@Utype_1F8040@kujuUI@@@std@@V?$allocator@Utype_1F8040@kujuUI@@@4@$0A@@std@@@2@ABUtype_1F8040@kujuUI@@@Z @ 0x001E9AB0
// match: ?_Buynode@?$_Tree@V?$_Tset_traits@Utype_1F8040@kujuUI@@U?$less@Utype_1F8040@kujuUI@@@std@@V?$allocator@Utype_1F8040@kujuUI@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tset_traits@Utype_1F8040@kujuUI@@U?$less@Utype_1F8040@kujuUI@@@std@@V?$allocator@Utype_1F8040@kujuUI@@@4@$0A@@std@@@2@PAU342@00ABUtype_1F8040@kujuUI@@D@Z @ 0x001E9B20
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tset_traits@Utype_1F8040@kujuUI@@U?$less@Utype_1F8040@kujuUI@@@std@@V?$allocator@Utype_1F8040@kujuUI@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tset_traits@Utype_1F8040@kujuUI@@U?$less@Utype_1F8040@kujuUI@@@std@@V?$allocator@Utype_1F8040@kujuUI@@@4@$0A@@std@@@2@PAU342@00ABUtype_1F8040@kujuUI@@D@Z @ 0x00303DD0
// match: ?clear@?$_Tree@V?$_Tset_traits@Utype_1F8040@kujuUI@@U?$less@Utype_1F8040@kujuUI@@@std@@V?$allocator@Utype_1F8040@kujuUI@@@4@$0A@@std@@@std@@QAEXXZ @ 0x001E9C00
// match: ?_Buynode@?$_Tree@V?$_Tset_traits@Utype_1F8040@kujuUI@@U?$less@Utype_1F8040@kujuUI@@@std@@V?$allocator@Utype_1F8040@kujuUI@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tset_traits@Utype_1F8040@kujuUI@@U?$less@Utype_1F8040@kujuUI@@@std@@V?$allocator@Utype_1F8040@kujuUI@@@4@$0A@@std@@@2@XZ @ 0x001E9C60
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tset_traits@Utype_1F8040@kujuUI@@U?$less@Utype_1F8040@kujuUI@@@std@@V?$allocator@Utype_1F8040@kujuUI@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tset_traits@Utype_1F8040@kujuUI@@U?$less@Utype_1F8040@kujuUI@@@std@@V?$allocator@Utype_1F8040@kujuUI@@@4@$0A@@std@@@2@XZ @ 0x00303DE0
// match: ?_Dec@const_iterator@?$_Tree@V?$_Tset_traits@Utype_1F8040@kujuUI@@U?$less@Utype_1F8040@kujuUI@@@std@@V?$allocator@Utype_1F8040@kujuUI@@@4@$0A@@std@@@std@@QAEXXZ @ 0x001E9D80
// match: ?_Inc@const_iterator@?$_Tree@V?$_Tset_traits@Utype_1F8040@kujuUI@@U?$less@Utype_1F8040@kujuUI@@@std@@V?$allocator@Utype_1F8040@kujuUI@@@4@$0A@@std@@@std@@QAEXXZ @ 0x001E9E40
// match: ?_Erase@?$_Tree@V?$_Tset_traits@Utype_1F8040@kujuUI@@U?$less@Utype_1F8040@kujuUI@@@std@@V?$allocator@Utype_1F8040@kujuUI@@@4@$0A@@std@@@std@@IAEXPAU_Node@?$_Tree_nod@V?$_Tset_traits@Utype_1F8040@kujuUI@@U?$less@Utype_1F8040@kujuUI@@@std@@V?$allocator@Utype_1F8040@kujuUI@@@4@$0A@@std@@@2@@Z @ 0x001E9ED0
// match: ??1_Node@?$_Tree_nod@V?$_Tset_traits@Utype_1F8040@kujuUI@@U?$less@Utype_1F8040@kujuUI@@@std@@V?$allocator@Utype_1F8040@kujuUI@@@4@$0A@@std@@@std@@QAE@XZ @ 0x001E9F40
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?vf_018@cLayoutPage@kujuUI@@UAEXPAUtype_1E4130@2@@Z (folded into 0x1F6BA0)
void kujuUI::cLayoutPage::vf_018(struct kujuUI::type_1E4130 *arg_0)
{
    type_3E7584::vf_018(arg_0);
}
