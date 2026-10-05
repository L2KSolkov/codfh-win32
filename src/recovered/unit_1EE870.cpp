/*
 * kujuUI's root widget (game/kujuui.h), the pad's buttons held and the
 * events their changes make, and the selectable widget's interface's move.
 */
#include "game/kujuui.h"

using namespace kujuUI;

// Vtables (.rdata, PLAN M5): each in its own placement range (config/splits.txt).
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_7type_3E75B8@kujuUI@@6B@ @ 0x003E75B8
// match: ??_7type_3E75E8@kujuUI@@6B@ @ 0x003E75E8

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
    RwUInt32 bp_4 = 1;
    for (RwInt32 var_C = 0; var_C < 13; ++var_C)
    {
        RwUInt32 lv_10 = unk_00 & bp_4;
        RwUInt32 var_14 = var_8 & bp_4;
        if (lv_10 != var_14)
        {
            RwInt32 var_18 = lv_10 == 0;
            cStateChange bp_20(var_C, var_18);
            arg_4->sub_1E75B0(bp_20);
        }
        bp_4 <<= 1;
    }
}

// match: ?sub_1EE9D0@type_1EE900@kujuUI@@QBEIXZ @ 0x001EE9D0
RwUInt32 type_1EE900::sub_1EE9D0() const
{
    return unk_00;
}

// match: ??0type_1EE900@kujuUI@@QAE@XZ @ 0x001EE9E0
type_1EE900::type_1EE900()
{
    unk_00 = 0;
    unk_04 = 0;
    unk_08 = 0;
}

// match: ??1type_3E75E8@kujuUI@@UAE@XZ @ 0x001EEA10
type_3E75E8::~type_3E75E8()
{
}

// match: ?sub_1EEA30@type_3E75E8@kujuUI@@QAEXII@Z @ 0x001EEA30
void type_3E75E8::sub_1EEA30(RwUInt32 arg_0, RwUInt32 arg_4)
{
    const type_1E0330_rect *bp_4 = pvf_004();
    RwReal lv_C = bp_4->unk_08 - bp_4->unk_00;
    RwReal var_8 = bp_4->unk_0C - bp_4->unk_04;
    type_1E0330_rect var_1C((RwReal)arg_0, (RwReal)arg_4, arg_0 + lv_C, arg_4 + var_8);
    pvf_008(&var_1C);
}
