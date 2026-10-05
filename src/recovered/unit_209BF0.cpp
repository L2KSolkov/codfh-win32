/*
 * The system link's session list (in-game menu 9, game/livemenu.h): the
 * session list page over "XboxSysLinkSessionList.layout".
 */
#include "game/livemenu.h"
#include "game/ingamemenu.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003E8BB0
extern const RwReal flt_3E8BB0 = 0.01f;
// 0x003E8BB4
extern const RwReal flt_3E8BB4 = 0.01f;
// 0x003E8BB8
extern const RwReal flt_3E8BB8 = 16.666666f;
// End of its data definitions.


// The this-adjusting thunk the columns' vtable (off_3E8BBC) holds for the
// deleting destructor.
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3E8BB0@@3MB @ 0x003E8BB0
// match: ?flt_3E8BB4@@3MB @ 0x003E8BB4
// match: ?flt_3E8BB8@@3MB @ 0x003E8BB8
// match: ??_7type_209BF0@@6Btype_20E4F0@@@ @ 0x003E8BBC
// match: ??_7type_209BF0@@6Btype_2049D0@@@ @ 0x003E8BD8
// match: ??_C@_0BO@ICMFNNGC@XboxSysLinkSessionList?4layout?$AA@ @ 0x003E8C34

// match: ??_Etype_209BF0@@WBII@AEPAXI@Z @ 0x00209CF0
// match: ??0type_209BF0@@QAE@XZ @ 0x00209BF0

type_209BF0::type_209BF0() : type_20C470("XboxSysLinkSessionList.layout", true)
{
}

// match: ??_Gtype_209BF0@@UAEPAXI@Z @ 0x00209C30
// match: ??1type_209BF0@@UAE@XZ @ 0x00209C60
type_209BF0::~type_209BF0()
{
}

// match: ?vf_04C@type_209BF0@@UAEXXZ @ 0x00209C90
void type_209BF0::vf_04C()
{
    type_2053C0::sub_205BF0(2);
    sub_1FC310()->sub_1FBDA0(sub_2046C0(8));
}

// match: ?vf_048@type_209BF0@@UAEXXZ @ 0x00209CC0
void type_209BF0::vf_048()
{
    sub_1FC310()->sub_1FBDA0(sub_2046C0(10));
}

// Members /OPT:ICF folded into shared trivial bodies (config/aliases.txt): defined here for
// the authentic link (PLAN M7); the placement link takes the shared bodies.

// ?vf_044@type_209BF0@@UAE_NXZ (folded into `return false` at 0x1E4AA0)
bool type_209BF0::vf_044()
{
    return 0;
}

// ?vf_050@type_209BF0@@UAEXXZ (folded into the empty body at 0x1E41C0)
void type_209BF0::vf_050()
{
}

// ?vf_058@type_209BF0@@UAEXXZ (folded into the empty body at 0x1E41C0)
void type_209BF0::vf_058()
{
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?vf_054@type_209BF0@@UAEXXZ (folded into 0x20C3F0)
void type_209BF0::vf_054()
{
    sub_20CB20();
}
