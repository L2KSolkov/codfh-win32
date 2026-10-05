/*
 * kujuUI's container widget (game/kujuui.h): its children in a std::vector,
 * which it updates, draws and bounds; the vector's instances follow.
 */
#include <algorithm>
#include "game/kujuui.h"

template class std::vector<kujuUI::type_3E7D08 *>;

using namespace kujuUI;

// match: ??0type_3E7584@kujuUI@@QAE@PAUtype_3E7D08@1@@Z @ 0x001ED730
type_3E7584::type_3E7584(type_3E7D08 *arg_0) : type_3E7D08(arg_0)
{
}

// match: ??1type_3E7584@kujuUI@@UAE@XZ @ 0x001ED7A0
type_3E7584::~type_3E7584()
{
}

// match: ?vf_008@type_3E7584@kujuUI@@UAEXXZ @ 0x001ED800
void type_3E7584::vf_008()
{
    for (std::vector<type_3E7D08 *>::iterator var_4 = unk_0C.begin(); var_4 != unk_0C.end(); ++var_4)
        (*var_4)->vf_008();
    type_3E7D08::vf_008();
}

// match: ?vf_00C@type_3E7584@kujuUI@@UAEXXZ @ 0x001ED870
void type_3E7584::vf_00C()
{
    for (std::vector<type_3E7D08 *>::iterator var_4 = unk_0C.begin(); var_4 != unk_0C.end(); ++var_4)
        (*var_4)->vf_00C();
    type_3E7D08::vf_00C();
}

// match: ?vf_014@type_3E7584@kujuUI@@UAEXM@Z @ 0x001ED8E0
void type_3E7584::vf_014(RwReal arg_0)
{
    vf_030();
    for (std::vector<type_3E7D08 *>::iterator var_4 = unk_0C.begin(); var_4 != unk_0C.end(); ++var_4)
        (*var_4)->vf_014(arg_0);
}

// match: ?vf_018@type_3E7584@kujuUI@@UAEXPAUtype_1E4130@2@@Z @ 0x001ED960
void type_3E7584::vf_018(type_1E4130 *arg_0)
{
    for (std::vector<type_3E7D08 *>::iterator var_4 = unk_0C.begin(); var_4 != unk_0C.end(); ++var_4)
        (*var_4)->vf_018(arg_0);
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
    RwReal var_8 = 0.0f;
    RwReal var_4 = 480.0f;
    RwReal var_10 = 0.0f;
    RwReal var_C = 320.0f;
    for (std::vector<type_3E7D08 *>::iterator var_14 = unk_0C.begin(); var_14 != unk_0C.end(); ++var_14)
    {
        type_3E7D08 *var_18 = *var_14;
        type_1E0330_rect var_28 = var_18->vf_020();
        var_4 = std::min(var_4, var_28.unk_04);
        var_10 = std::max(var_10, var_28.unk_0C);
        var_8 = std::max(var_8, var_28.unk_08 - var_C);
        var_8 = std::max(var_8, var_C - var_28.unk_00);
    }
    return type_1E0330_rect(var_C - var_8, var_4, var_C + var_8, var_10);
}

// match: ?sub_1EDBC0@type_3E7584@kujuUI@@QAEXI@Z @ 0x001EDBC0
void type_3E7584::sub_1EDBC0(RwUInt32 arg_0)
{
    unk_0C.reserve(arg_0);
}
