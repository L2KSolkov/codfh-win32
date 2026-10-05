/*
 * kujuUI's root widget (game/kujuui.h), the pad's buttons held and the
 * events their changes make, and the selectable widget's interface's move.
 */
#include "game/kujuui.h"

using namespace kujuUI;

// match: ??0type_3E75B8@kujuUI@@QAE@PAUtype_3E7D08@1@@Z @ 0x001EE870
type_3E75B8::type_3E75B8(type_3E7D08 *arg_0) : type_3E7D08(arg_0)
{
}

// match: ??_Gtype_3E75B8@kujuUI@@UAEPAXI@Z @ 0x001EE8A0

// match: ??1type_3E75B8@kujuUI@@UAE@XZ @ 0x001EE8D0
type_3E75B8::~type_3E75B8()
{
}

// match: ?vf_020@type_3E75B8@kujuUI@@UAE?AUtype_1E0330_rect@2@XZ @ 0x001EE8F0
type_1E0330_rect type_3E75B8::vf_020()
{
    return type_1E0330_rect();
}

// match: ??0type_1EE900@kujuUI@@QAE@I@Z @ 0x001EE900
type_1EE900::type_1EE900(RwUInt32 arg_0)
{
    unk_00 = arg_0;
    unk_04 = 0;
    unk_08 = 0;
}

// match: ?sub_1EE930@kujuUI@@YAIH@Z @ 0x001EE930
RwUInt32 kujuUI::sub_1EE930(RwInt32 arg_0)
{
    return 1 << arg_0;
}

// match: ?sub_1EE940@type_1EE900@kujuUI@@QAEXPBU12@PAUtype_1E7560@2@@Z @ 0x001EE940
void type_1EE900::sub_1EE940(const type_1EE900 *arg_0, type_1E7560 *arg_4)
{
    RwUInt32 var_8 = arg_0->sub_1EE9D0();
    RwUInt32 var_4 = 1;
    for (RwInt32 var_C = 0; var_C < 13; ++var_C)
    {
        RwUInt32 var_10 = unk_00 & var_4;
        RwUInt32 var_14 = var_8 & var_4;
        if (var_10 != var_14)
            arg_4->sub_1E75B0(cStateChange(var_C, var_10 == 0));
        var_4 <<= 1;
    }
}

// match: ??1type_3E75E8@kujuUI@@UAE@XZ @ 0x001EEA10
type_3E75E8::~type_3E75E8()
{
}

// match: ?sub_1EEA30@type_3E75E8@kujuUI@@QAEXII@Z @ 0x001EEA30
void type_3E75E8::sub_1EEA30(RwUInt32 arg_0, RwUInt32 arg_4)
{
    const type_1E0330_rect *var_4 = pvf_004();
    RwReal var_C = var_4->unk_08 - var_4->unk_00;
    RwReal var_8 = var_4->unk_0C - var_4->unk_04;
    type_1E0330_rect var_1C((RwReal)arg_0, (RwReal)arg_4, arg_0 + var_C, arg_4 + var_8);
    pvf_008(&var_1C);
}
