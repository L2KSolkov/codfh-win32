/*
 * kujuUI's look given to a widget by name, and the pad's event queue
 * (game/kujuui.h).
 */
#include "game/kujuui.h"

namespace kujuUI {

// Vtables (.rdata, PLAN M5): each in its own placement range (config/splits.txt).
// match: ??_7type_1E7490@kujuUI@@6B@ @ 0x003E73A8

// match: ??0type_1E7490@kujuUI@@QAE@XZ @ 0x001E7490
type_1E7490::type_1E7490()
{
    unk_04 = 0;
}

// match: ??_Gtype_1E7490@kujuUI@@UAEPAXI@Z @ 0x001E74C0
// match: ??1type_1E7490@kujuUI@@UAE@XZ @ 0x001E74F0
type_1E7490::~type_1E7490()
{
}

// match: ?sub_1E7510@type_1E7490@kujuUI@@QAEXPAUtype_1E3BA0@2@@Z @ 0x001E7510
void type_1E7490::sub_1E7510(type_1E3BA0 *arg_0)
{
    unk_04->vf_000(arg_0);
}

// match: ?sub_1E7540@type_1E7490@kujuUI@@QAEXPAUtype_1E7490_target@12@@Z @ 0x001E7540
void type_1E7490::sub_1E7540(type_1E7490_target *arg_0)
{
    unk_04 = arg_0;
}

// match: ??0type_1E7560@kujuUI@@QAE@XZ @ 0x001E7560
type_1E7560::type_1E7560()
{
    unk_100 = 0;
}

// match: ?sub_1E75B0@type_1E7560@kujuUI@@QAEXABVcStateChange@2@@Z @ 0x001E75B0
void type_1E7560::sub_1E75B0(const cStateChange &arg_0)
{
    unk_00[unk_100] = arg_0;
    unk_100++;
}

// match: ?sub_1E75F0@type_1E7560@kujuUI@@QAE_NXZ @ 0x001E75F0
bool type_1E7560::sub_1E75F0()
{
    return unk_100 != 0;
}

// match: ?sub_1E7610@type_1E7560@kujuUI@@QAE?AVcStateChange@2@XZ @ 0x001E7610
cStateChange type_1E7560::sub_1E7610()
{
    cStateChange var_8 = unk_00[0];

    unk_100--;
    for (RwUInt32 var_C = 0; var_C < unk_100; var_C++)
        unk_00[var_C] = unk_00[var_C + 1];
    return var_8;
}

}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??1type_1E7560@kujuUI@@QAE@XZ (folded into 0x1E41C0)
kujuUI::type_1E7560::~type_1E7560()
{
}

// ?vf_000@type_1E7490@kujuUI@@UAEHXZ (folded into 0xA17A0)
RwInt32 kujuUI::type_1E7490::vf_000()
{
    return 5;
}
