/*
 * A scoreboard's players (game/ingamepages.h): their rows, ordered by their
 * two counts, and the columns holding them.
 */
#include "game/ingamepages.h"
#include "game/uiglue.h"

// Its data definitions (PLAN M5), in the image's address order.
// End of its data definitions.


using namespace kujuUI;

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_7type_21D470@@6B@ @ 0x003EA420
// match: __ehhandler$??0type_21D470@@QAE@HABUtype_1A5EA0@@HHH@Z>1>8 @ 0x004250C8
// match: __ehhandler$??0type_21D470@@QAE@HABUtype_1A5EA0@@HHH@Z>1 @ 0x004250D0
// match: __ehhandler$??1type_21D470@@UAE@XZ>1>8 @ 0x004250EC
// match: __ehhandler$??1type_21D470@@UAE@XZ>1 @ 0x004250F4
// match: __ehhandler$?vf_004@type_21D470@@UAEXXZ>1>8 @ 0x00425110
// match: __ehhandler$?vf_004@type_21D470@@UAEXXZ>1 @ 0x00425128

// match: ??0type_21D470@@QAE@HABUtype_1A5EA0@@HHH@Z @ 0x0021D470
// match: __ehhandler$??0type_21D470@@QAE@HABUtype_1A5EA0@@HHH@Z-0x8 @ 0x00307FB0
// match: __ehhandler$??0type_21D470@@QAE@HABUtype_1A5EA0@@HHH@Z @ 0x00307FB8

type_21D470::type_21D470(RwInt32 arg_0, const type_1A5EA0 &arg_4, RwInt32 arg_8, RwInt32 arg_C, RwInt32 arg_10)
    : unk_40(arg_0), unk_44(arg_4), unk_60(arg_8), unk_64(arg_C), unk_68(arg_10)
{
}


// match: ??_Gtype_21D470@@UAEPAXI@Z @ 0x0021D510
// match: ??1type_21D470@@UAE@XZ @ 0x0021D540
// match: __ehhandler$??1type_21D470@@UAE@XZ-0x8 @ 0x00307FD0
// match: __ehhandler$??1type_21D470@@UAE@XZ @ 0x00307FD8
type_21D470::~type_21D470()
{
}

// Its texts: the name and the two counts.
// match: ?vf_004@type_21D470@@UAEXXZ @ 0x0021D5A0
// match: __ehhandler$?vf_004@type_21D470@@UAEXXZ-0x18 @ 0x00307FF0
// match: __ehhandler$?vf_004@type_21D470@@UAEXXZ @ 0x00308008
void type_21D470::vf_004()
{
    type_1CB670 lv_2C;
    type_1CB670 lv_48;

    add_number(lv_2C, sub_21D740());
    add_number(lv_48, sub_21D720());
    sub_1EC2C0(sub_1CB720(sub_21D700()->c_str()), 0);
    sub_1EC2C0(lv_2C, 1);
    sub_1EC2C0(lv_48, 2);
}

// match: ?sub_21D700@type_21D470@@QBEPBUtype_1A5EA0@@XZ @ 0x0021D700
const type_1A5EA0 *type_21D470::sub_21D700() const
{
    return &unk_44;
}

// match: ?sub_21D720@type_21D470@@QBEHXZ @ 0x0021D720
RwInt32 type_21D470::sub_21D720() const
{
    return unk_64;
}

// match: ?sub_21D740@type_21D470@@QBEHXZ @ 0x0021D740
RwInt32 type_21D470::sub_21D740() const
{
    return unk_60;
}

// match: ?sub_21D760@type_21D470@@QAE_NABU1@@Z @ 0x0021D760
bool type_21D470::sub_21D760(const type_21D470 &arg_0)
{
    return unk_60 > arg_0.sub_21D740() || unk_60 == arg_0.sub_21D740() && unk_64 > arg_0.sub_21D720();
}





// The rows' list's members (std::list<type_21D470 *>).



// The compiler's destructor, out of line with the deleting one.




