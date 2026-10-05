/*
 * kujuUI's container widget (game/kujuui.h): its children in a std::vector,
 * which it updates, draws and bounds; the vector's instances follow.
 */
#include <algorithm>
#include "game/kujuui.h"

// (the vector is not instantiated explicitly: the image has no const_iterator
// _Uninit_copy, whose EH table the M7 link would keep beside the iterator one's)

using namespace kujuUI;

// Vtables (.rdata, PLAN M5): each in its own placement range (config/splits.txt).
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_7type_3E7584@kujuUI@@6B@ @ 0x003E7584
// match: __ehhandler$??0type_3E7584@kujuUI@@QAE@PAUtype_3E7D08@1@@Z>1>8 @ 0x0042078C
// match: __ehhandler$??0type_3E7584@kujuUI@@QAE@PAUtype_3E7D08@1@@Z>1 @ 0x00420794
// match: __ehhandler$??1type_3E7584@kujuUI@@UAE@XZ>1>8 @ 0x004207B0
// match: __ehhandler$??1type_3E7584@kujuUI@@UAE@XZ>1 @ 0x004207B8
// match: __ehhandler$?reserve@?$vector@PAUtype_3E7D08@kujuUI@@V?$allocator@PAUtype_3E7D08@kujuUI@@@std@@@std@@QAEXI@Z>1>8 @ 0x004207D4
// match: __ehhandler$?reserve@?$vector@PAUtype_3E7D08@kujuUI@@V?$allocator@PAUtype_3E7D08@kujuUI@@@std@@@std@@QAEXI@Z>1>16>16 @ 0x004207E4
// match: __ehhandler$?reserve@?$vector@PAUtype_3E7D08@kujuUI@@V?$allocator@PAUtype_3E7D08@kujuUI@@@std@@@std@@QAEXI@Z>1>16 @ 0x004207F4
// match: __ehhandler$?reserve@?$vector@PAUtype_3E7D08@kujuUI@@V?$allocator@PAUtype_3E7D08@kujuUI@@@std@@@std@@QAEXI@Z>1 @ 0x00420808
// match: __ehhandler$?_Insert_n@?$vector@PAUtype_3E7D08@kujuUI@@V?$allocator@PAUtype_3E7D08@kujuUI@@@std@@@std@@IAEXViterator@12@IABQAUtype_3E7D08@kujuUI@@@Z>1>8 @ 0x00420824
// match: __ehhandler$?_Insert_n@?$vector@PAUtype_3E7D08@kujuUI@@V?$allocator@PAUtype_3E7D08@kujuUI@@@std@@@std@@IAEXViterator@12@IABQAUtype_3E7D08@kujuUI@@@Z>1>16>16 @ 0x00420844
// match: __ehhandler$?_Insert_n@?$vector@PAUtype_3E7D08@kujuUI@@V?$allocator@PAUtype_3E7D08@kujuUI@@@std@@@std@@IAEXViterator@12@IABQAUtype_3E7D08@kujuUI@@@Z>1>16>36 @ 0x00420854
// match: __ehhandler$?_Insert_n@?$vector@PAUtype_3E7D08@kujuUI@@V?$allocator@PAUtype_3E7D08@kujuUI@@@std@@@std@@IAEXViterator@12@IABQAUtype_3E7D08@kujuUI@@@Z>1>16 @ 0x00420864
// match: __ehhandler$?_Insert_n@?$vector@PAUtype_3E7D08@kujuUI@@V?$allocator@PAUtype_3E7D08@kujuUI@@@std@@@std@@IAEXViterator@12@IABQAUtype_3E7D08@kujuUI@@@Z>1 @ 0x0042088C
// match: __ehhandler$?_Xlen@?$vector@PAUtype_3E7D08@kujuUI@@V?$allocator@PAUtype_3E7D08@kujuUI@@@std@@@std@@IBEXXZ>1>8 @ 0x004208A8
// match: __ehhandler$?_Xlen@?$vector@PAUtype_3E7D08@kujuUI@@V?$allocator@PAUtype_3E7D08@kujuUI@@@std@@@std@@IBEXXZ>1 @ 0x004208B0
// match: __ehhandler$??$_Uninit_copy@Viterator@?$vector@PAUtype_3E7D08@kujuUI@@V?$allocator@PAUtype_3E7D08@kujuUI@@@std@@@std@@PAPAUtype_3E7D08@kujuUI@@V?$allocator@PAUtype_3E7D08@kujuUI@@@3@@std@@YAPAPAUtype_3E7D08@kujuUI@@Viterator@?$vector@PAUtype_3E7D08@kujuUI@@V?$allocator@PAUtype_3E7D08@kujuUI@@@std@@@0@0PAPAU12@AAV?$allocator@PAUtype_3E7D08@kujuUI@@@0@U_Nonscalar_ptr_iterator_tag@0@@Z>1>8 @ 0x004208CC
// match: __ehhandler$??$_Uninit_copy@Viterator@?$vector@PAUtype_3E7D08@kujuUI@@V?$allocator@PAUtype_3E7D08@kujuUI@@@std@@@std@@PAPAUtype_3E7D08@kujuUI@@V?$allocator@PAUtype_3E7D08@kujuUI@@@3@@std@@YAPAPAUtype_3E7D08@kujuUI@@Viterator@?$vector@PAUtype_3E7D08@kujuUI@@V?$allocator@PAUtype_3E7D08@kujuUI@@@std@@@0@0PAPAU12@AAV?$allocator@PAUtype_3E7D08@kujuUI@@@0@U_Nonscalar_ptr_iterator_tag@0@@Z>1>16>16 @ 0x004208DC
// match: __ehhandler$??$_Uninit_copy@Viterator@?$vector@PAUtype_3E7D08@kujuUI@@V?$allocator@PAUtype_3E7D08@kujuUI@@@std@@@std@@PAPAUtype_3E7D08@kujuUI@@V?$allocator@PAUtype_3E7D08@kujuUI@@@3@@std@@YAPAPAUtype_3E7D08@kujuUI@@Viterator@?$vector@PAUtype_3E7D08@kujuUI@@V?$allocator@PAUtype_3E7D08@kujuUI@@@std@@@0@0PAPAU12@AAV?$allocator@PAUtype_3E7D08@kujuUI@@@0@U_Nonscalar_ptr_iterator_tag@0@@Z>1>16 @ 0x004208EC
// match: __ehhandler$??$_Uninit_copy@Viterator@?$vector@PAUtype_3E7D08@kujuUI@@V?$allocator@PAUtype_3E7D08@kujuUI@@@std@@@std@@PAPAUtype_3E7D08@kujuUI@@V?$allocator@PAUtype_3E7D08@kujuUI@@@3@@std@@YAPAPAUtype_3E7D08@kujuUI@@Viterator@?$vector@PAUtype_3E7D08@kujuUI@@V?$allocator@PAUtype_3E7D08@kujuUI@@@std@@@0@0PAPAU12@AAV?$allocator@PAUtype_3E7D08@kujuUI@@@0@U_Nonscalar_ptr_iterator_tag@0@@Z>1 @ 0x00420900

// match: ??0type_3E7584@kujuUI@@QAE@PAUtype_3E7D08@1@@Z @ 0x001ED730
// match: __ehhandler$??0type_3E7584@kujuUI@@QAE@PAUtype_3E7D08@1@@Z-0x8 @ 0x00303FE0
// match: __ehhandler$??0type_3E7584@kujuUI@@QAE@PAUtype_3E7D08@1@@Z @ 0x00303FE8

type_3E7584::type_3E7584(type_3E7D08 *arg_0) : type_3E7D08(arg_0)
{
}

// match: ??1type_3E7584@kujuUI@@UAE@XZ @ 0x001ED7A0
// match: __ehhandler$??1type_3E7584@kujuUI@@UAE@XZ-0x8 @ 0x00304000
// match: __ehhandler$??1type_3E7584@kujuUI@@UAE@XZ @ 0x00304008
type_3E7584::~type_3E7584()
{
}

// match: ?vf_008@type_3E7584@kujuUI@@UAEXXZ @ 0x001ED800
void type_3E7584::vf_008()
{
    for (std::vector<type_3E7D08 *>::iterator var_4 = unk_0C.begin(); var_4 != unk_0C.end(); ++var_4)
    {
        type_3E7D08 *var_8 = *var_4;
        var_8->vf_008();
    }
    type_3E7D08::vf_008();
}

// match: ?vf_00C@type_3E7584@kujuUI@@UAEXXZ @ 0x001ED870
void type_3E7584::vf_00C()
{
    for (std::vector<type_3E7D08 *>::iterator var_4 = unk_0C.begin(); var_4 != unk_0C.end(); ++var_4)
    {
        type_3E7D08 *var_8 = *var_4;
        var_8->vf_00C();
    }
    type_3E7D08::vf_00C();
}

// match: ?vf_014@type_3E7584@kujuUI@@UAEXM@Z @ 0x001ED8E0
void type_3E7584::vf_014(RwReal arg_0)
{
    vf_030();
    for (std::vector<type_3E7D08 *>::iterator var_4 = unk_0C.begin(); var_4 != unk_0C.end(); ++var_4)
    {
        type_3E7D08 *var_8 = *var_4;
        var_8->vf_014(arg_0);
    }
}

// match: ?vf_018@type_3E7584@kujuUI@@UAEXPAUtype_1E4130@2@@Z @ 0x001ED960
void type_3E7584::vf_018(type_1E4130 *arg_0)
{
    for (std::vector<type_3E7D08 *>::iterator var_4 = unk_0C.begin(); var_4 != unk_0C.end(); ++var_4)
    {
        type_3E7D08 *var_8 = *var_4;
        var_8->vf_018(arg_0);
    }
}

// match: ?sub_1ED9D0@type_3E7584@kujuUI@@QAEXPAUtype_3E7D08@2@@Z @ 0x001ED9D0
void type_3E7584::sub_1ED9D0(type_3E7D08 *arg_0)
{
    unk_0C.push_back(arg_0);
}

// match: ?sub_1ED9F0@type_3E7584@kujuUI@@QAEXPAUtype_3E7D08@2@@Z @ 0x001ED9F0
void type_3E7584::sub_1ED9F0(type_3E7D08 *arg_0)
{
    unk_0C.insert(unk_0C.begin(), arg_0);
}

// match: ?vf_020@type_3E7584@kujuUI@@UAE?AUtype_1E0330_rect@2@XZ @ 0x001EDA30
type_1E0330_rect type_3E7584::vf_020()
{
    RwReal bp_4;
    RwReal var_8;
    RwReal lv_C;
    RwReal var_10;
    var_8 = 0.0f;
    bp_4 = 480.0f;
    var_10 = 0.0f;
    lv_C = 320.0f;
    for (std::vector<type_3E7D08 *>::iterator var_14 = unk_0C.begin(); var_14 != unk_0C.end(); ++var_14)
    {
        type_3E7D08 *lv_18 = *var_14;
        type_1E0330_rect var_28 = lv_18->vf_020();
        bp_4 = std::min(bp_4, var_28.unk_04);
        var_10 = std::max(var_10, var_28.unk_0C);
        var_8 = std::max(var_8, var_28.unk_08 - lv_C);
        var_8 = std::max(var_8, lv_C - var_28.unk_00);
    }
    return type_1E0330_rect(lv_C - var_8, bp_4, lv_C + var_8, var_10);
}

// match: ?sub_1EDBC0@type_3E7584@kujuUI@@QAEXI@Z @ 0x001EDBC0
void type_3E7584::sub_1EDBC0(RwUInt32 arg_0)
{
    unk_0C.reserve(arg_0);
}

// std::vector<type_3E7D08 *>'s instances (the explicit instantiation above).
// match: ?reserve@?$vector@PAUtype_3E7D08@kujuUI@@V?$allocator@PAUtype_3E7D08@kujuUI@@@std@@@std@@QAEXI@Z @ 0x001EDC40
// match: __ehhandler$?reserve@?$vector@PAUtype_3E7D08@kujuUI@@V?$allocator@PAUtype_3E7D08@kujuUI@@@std@@@std@@QAEXI@Z @ 0x00304020
// match: ?push_back@?$vector@PAUtype_3E7D08@kujuUI@@V?$allocator@PAUtype_3E7D08@kujuUI@@@std@@@std@@QAEXABQAUtype_3E7D08@kujuUI@@@Z @ 0x001EDE70
// match: ?insert@?$vector@PAUtype_3E7D08@kujuUI@@V?$allocator@PAUtype_3E7D08@kujuUI@@@std@@@std@@QAE?AViterator@12@V312@ABQAUtype_3E7D08@kujuUI@@@Z @ 0x001EDF50
// match: ?_Buy@?$vector@PAUtype_3E7D08@kujuUI@@V?$allocator@PAUtype_3E7D08@kujuUI@@@std@@@std@@IAE_NI@Z @ 0x001EE000
// match: ?_Insert_n@?$vector@PAUtype_3E7D08@kujuUI@@V?$allocator@PAUtype_3E7D08@kujuUI@@@std@@@std@@IAEXViterator@12@IABQAUtype_3E7D08@kujuUI@@@Z @ 0x001EE0A0
// match: __ehhandler$?_Insert_n@?$vector@PAUtype_3E7D08@kujuUI@@V?$allocator@PAUtype_3E7D08@kujuUI@@@std@@@std@@IAEXViterator@12@IABQAUtype_3E7D08@kujuUI@@@Z @ 0x00304030
// match: ?_Xlen@?$vector@PAUtype_3E7D08@kujuUI@@V?$allocator@PAUtype_3E7D08@kujuUI@@@std@@@std@@IBEXXZ @ 0x001EE710
// match: __ehhandler$?_Xlen@?$vector@PAUtype_3E7D08@kujuUI@@V?$allocator@PAUtype_3E7D08@kujuUI@@@std@@@std@@IBEXXZ-0x8 @ 0x00304040
// match: __ehhandler$?_Xlen@?$vector@PAUtype_3E7D08@kujuUI@@V?$allocator@PAUtype_3E7D08@kujuUI@@@std@@@std@@IBEXXZ @ 0x00304048
// match: ??$_Uninit_copy@Viterator@?$vector@PAUtype_3E7D08@kujuUI@@V?$allocator@PAUtype_3E7D08@kujuUI@@@std@@@std@@PAPAUtype_3E7D08@kujuUI@@V?$allocator@PAUtype_3E7D08@kujuUI@@@3@@std@@YAPAPAUtype_3E7D08@kujuUI@@Viterator@?$vector@PAUtype_3E7D08@kujuUI@@V?$allocator@PAUtype_3E7D08@kujuUI@@@std@@@0@0PAPAU12@AAV?$allocator@PAUtype_3E7D08@kujuUI@@@0@U_Nonscalar_ptr_iterator_tag@0@@Z @ 0x001EE7A0
// match: __ehhandler$??$_Uninit_copy@Viterator@?$vector@PAUtype_3E7D08@kujuUI@@V?$allocator@PAUtype_3E7D08@kujuUI@@@std@@@std@@PAPAUtype_3E7D08@kujuUI@@V?$allocator@PAUtype_3E7D08@kujuUI@@@3@@std@@YAPAPAUtype_3E7D08@kujuUI@@Viterator@?$vector@PAUtype_3E7D08@kujuUI@@V?$allocator@PAUtype_3E7D08@kujuUI@@@std@@@0@0PAPAU12@AAV?$allocator@PAUtype_3E7D08@kujuUI@@@0@U_Nonscalar_ptr_iterator_tag@0@@Z @ 0x00304060

// match: ?sub_1EDBE0@type_3E7584@kujuUI@@QAE?AViterator@?$vector@PAUtype_3E7D08@kujuUI@@V?$allocator@PAUtype_3E7D08@kujuUI@@@std@@@std@@XZ @ 0x001EDBE0
std::vector<type_3E7D08 *>::iterator type_3E7584::sub_1EDBE0()
{
    return unk_0C.begin();
}

// match: ?sub_1EDC10@type_3E7584@kujuUI@@QAE?AViterator@?$vector@PAUtype_3E7D08@kujuUI@@V?$allocator@PAUtype_3E7D08@kujuUI@@@std@@@std@@XZ @ 0x001EDC10
std::vector<type_3E7D08 *>::iterator type_3E7584::sub_1EDC10()
{
    return unk_0C.end();
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?vf_030@type_3E7584@kujuUI@@UAEXXZ (folded into 0x1E41C0)
void kujuUI::type_3E7584::vf_030()
{
}
