/*
 * The next map vote (game/ingamepages.h): a vote page and its question (slot 22),
 * built in two texts (type_1CB670, default-constructed out of line).
 */
#include "game/ingamepages.h"
#include "game/uiglue.h"
#include "game/mpgame.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003E95F4
extern const RwReal flt_3E95F4 = 0.01f;
// 0x003E95F8
extern const RwReal flt_3E95F8 = 0.01f;
// 0x003E95FC
extern const RwReal flt_3E95FC = 16.666666f;
// End of its data definitions.


// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3E95F4@@3MB @ 0x003E95F4
// match: ?flt_3E95F8@@3MB @ 0x003E95F8
// match: ?flt_3E95FC@@3MB @ 0x003E95FC
// match: ??_7type_215D40@@6B@ @ 0x003E9600
// match: ??_C@_0O@LMKFHHBA@Vote?5next?5map?$AA@ @ 0x003E965C
// match: __ehhandler$?vf_058@type_215D40@@UAE?AUtype_1CB670@@XZ>1>8 @ 0x0042424C
// match: __ehhandler$?vf_058@type_215D40@@UAE?AUtype_1CB670@@XZ>1 @ 0x00424274

// match: ??0type_215D40@@QAE@PBDPAUtype_21A5E0@@@Z @ 0x00215D40

type_215D40::type_215D40(const RwChar *arg_0, type_21A5E0 *arg_4) : type_216130(arg_0, arg_4)
{
}

// match: ??_Gtype_215D40@@UAEPAXI@Z @ 0x00215D70
// match: ??1type_215D40@@UAE@XZ @ 0x00215DA0
type_215D40::~type_215D40()
{
}

// The question: Vote next map, then the next map voted on.
// match: ?vf_058@type_215D40@@UAE?AUtype_1CB670@@XZ @ 0x00215DC0
// match: __ehhandler$?vf_058@type_215D40@@UAE?AUtype_1CB670@@XZ-0x3F @ 0x00307020
// match: __ehhandler$?vf_058@type_215D40@@UAE?AUtype_1CB670@@XZ @ 0x0030705F
type_1CB670 type_215D40::vf_058()
{
    type_1CB670 lv_2C;
    type_1CB670 lv_48;

    if (sub_1C4D00() == 0)
    {
        lv_2C = type_1CB670("Vote next map", 0);
        lv_48 = type_1CB670(sub_1C4590(sub_1C4D20()), 0);
        add_text(lv_2C, lv_48);
    }
    return lv_2C;
}
