/*
 * A row of the kick list (game/ingamepages.h): a player's index and name,
 * and its texts (slot 1).
 */
#include "game/ingamepages.h"

using namespace kujuUI;

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_7type_21CE60@@6B@ @ 0x003EA3A8
// match: __ehhandler$??0type_21CE60@@QAE@HUtype_1A5EA0@@@Z>1>8 @ 0x00424FB8
// match: __ehhandler$??0type_21CE60@@QAE@HUtype_1A5EA0@@@Z>1 @ 0x00424FC8
// match: __ehhandler$??1type_21CE60@@UAE@XZ>1>8 @ 0x00424FE4
// match: __ehhandler$??1type_21CE60@@UAE@XZ>1 @ 0x00424FEC
// match: __ehhandler$?vf_004@type_21CE60@@UAEXXZ>1>8 @ 0x00425008
// match: __ehhandler$?vf_004@type_21CE60@@UAEXXZ>1 @ 0x00425010

// match: ??0type_21CE60@@QAE@HUtype_1A5EA0@@@Z @ 0x0021CE60
// match: __ehhandler$??0type_21CE60@@QAE@HUtype_1A5EA0@@@Z-0x10 @ 0x00307EC0
// match: __ehhandler$??0type_21CE60@@QAE@HUtype_1A5EA0@@@Z @ 0x00307ED0

type_21CE60::type_21CE60(RwInt32 arg_0, type_1A5EA0 arg_4) : unk_40(arg_0), unk_44(arg_4)
{
}

// match: ??_Gtype_21CE60@@UAEPAXI@Z @ 0x0021CF00
// match: ??1type_21CE60@@UAE@XZ @ 0x0021CF30
// match: __ehhandler$??1type_21CE60@@UAE@XZ-0x8 @ 0x00307EE0
// match: __ehhandler$??1type_21CE60@@UAE@XZ @ 0x00307EE8
type_21CE60::~type_21CE60()
{
}

// Its texts: the name.
// match: ?vf_004@type_21CE60@@UAEXXZ @ 0x0021CF90
// match: __ehhandler$?vf_004@type_21CE60@@UAEXXZ-0x8 @ 0x00307F00
// match: __ehhandler$?vf_004@type_21CE60@@UAEXXZ @ 0x00307F08
void type_21CE60::vf_004()
{
    sub_1EC2C0(sub_1CB720(unk_44.c_str()), 0);
}


// match: ?sub_21D030@type_21CE60@@QAEHXZ @ 0x0021D030
RwInt32 type_21CE60::sub_21D030()
{
    return unk_40;
}

// match: ?sub_21D050@type_21CE60@@QAE?AUtype_1A5EA0@@XZ @ 0x0021D050
type_1A5EA0 type_21CE60::sub_21D050()
{
    return unk_44;
}

// match: ?sub_21D0A0@type_21CE60@@QAE_NABU1@@Z @ 0x0021D0A0
bool type_21CE60::sub_21D0A0(const type_21CE60 &arg_0)
{
    return unk_44.compare(arg_0.unk_44) < 0;
}
