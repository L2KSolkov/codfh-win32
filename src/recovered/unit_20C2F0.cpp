/*
 * The Xbox Live session list (in-game menu 7, game/livemenu.h): the session
 * list page over "SessionList.layout".
 */
#include "types/cXboxLive.h"
#include "game/livemenu.h"
#include "game/ingamemenu.h"
#include "types/type_DC400.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003E90CC
extern const RwReal flt_3E90CC = 0.01f;
// 0x003E90D0
extern const RwReal flt_3E90D0 = 0.01f;
// 0x003E90D4
extern const RwReal flt_3E90D4 = 16.666666f;
// 0x003E90D8
extern const RwReal flt_3E90D8 = 0.01f;
// 0x003E90DC
extern const RwReal flt_3E90DC = 0.01f;
// 0x003E90E0
extern const RwReal flt_3E90E0 = 16.666666f;
// End of its data definitions.


// The this-adjusting thunk the columns' vtable (off_3E90E4) holds for the
// deleting destructor.
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3E90CC@@3MB @ 0x003E90CC
// match: ?flt_3E90D0@@3MB @ 0x003E90D0
// match: ?flt_3E90D4@@3MB @ 0x003E90D4
// match: ?flt_3E90D8@@3MB @ 0x003E90D8
// match: ?flt_3E90DC@@3MB @ 0x003E90DC
// match: ?flt_3E90E0@@3MB @ 0x003E90E0
// match: ??_7type_20C2F0@@6Btype_20E4F0@@@ @ 0x003E90E4
// match: ??_7type_20C2F0@@6Btype_2049D0@@@ @ 0x003E9100
// match: ??_C@_0BD@EDCHOECL@SessionList?4layout?$AA@ @ 0x003E915C

// match: ??_Etype_20C2F0@@WBII@AEPAXI@Z @ 0x0020C460
// match: ??0type_20C2F0@@QAE@XZ @ 0x0020C2F0

type_20C2F0::type_20C2F0() : type_20C470("SessionList.layout", true)
{
}

// match: ??_Gtype_20C2F0@@UAEPAXI@Z @ 0x0020C330
// match: ??1type_20C2F0@@UAE@XZ @ 0x0020C360
type_20C2F0::~type_20C2F0()
{
}

// match: ?vf_048@type_20C2F0@@UAEXXZ @ 0x0020C390
void type_20C2F0::vf_048()
{
    sub_1FC310()->sub_1FBDA0(sub_2046C0(1));
}

// match: ?vf_04C@type_20C2F0@@UAEXXZ @ 0x0020C3C0
void type_20C2F0::vf_04C()
{
    type_2053C0::sub_205BF0(2);
    sub_1FC310()->sub_1FBDA0(sub_2046C0(0));
}

// match: ?vf_054@type_20C2F0@@UAEXXZ @ 0x0020C3F0
void type_20C2F0::vf_054()
{
    sub_20CB20();
}

// match: ?vf_058@type_20C2F0@@UAEXXZ @ 0x0020C410
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_20C2F0::vf_058()
{
    type_4F8054 *var_8;
    type_4F8054_B0 *l4;

    var_8 = dword_4F8054;
    l4 = var_8->unk_B0;
    if (!var_8 || !l4)
        return;
    l4->sub_1CD370();
    var_8->setError(7, 10);
}

// Members /OPT:ICF folded into shared trivial bodies (config/aliases.txt): defined here for
// the authentic link (PLAN M7); the placement link takes the shared bodies.

// ?vf_050@type_20C2F0@@UAEXXZ (folded into the empty body at 0x1E41C0)
void type_20C2F0::vf_050()
{
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?vf_044@type_20C2F0@@UAE_NXZ (folded into 0x2015D0)
bool type_20C2F0::vf_044()
{
    return true;
}
