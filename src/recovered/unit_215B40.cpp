/*
 * The game type vote (game/ingamepages.h): a vote page and its question (slot 22),
 * built in two texts (type_1CB670, default-constructed out of line).
 */
#include "game/ingamepages.h"
#include "game/uiglue.h"
#include "game/mpgame.h"

// Its data definitions (PLAN M5), in the image's address order.
#ifndef CODFH_SP // MP only: unreferenced constants single player does not emit (not in default.xbe; /O2 keeps them only while they are external)
// 0x003E9578
extern const RwReal flt_3E9578 = 0.01f;
// 0x003E957C
extern const RwReal flt_3E957C = 0.01f;
// 0x003E9580
extern const RwReal flt_3E9580 = 16.666666f;
#endif
// End of its data definitions.


// The in-game pages' base's kind (game/ingamepages.h's inline; its copy
// sits here).
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3E9578@@3MB @ 0x003E9578
// match: ?flt_3E957C@@3MB @ 0x003E957C
// match: ?flt_3E9580@@3MB @ 0x003E9580
// match: ??_7type_215B40@@6B@ @ 0x003E9588
// match: ??_C@_0P@KJNHHCIB@Vote?5game?5type?$AA@ @ 0x003E95E4
// match: __ehhandler$?vf_058@type_215B40@@UAE?AUtype_1CB670@@XZ>1>8 @ 0x00424208
// match: __ehhandler$?vf_058@type_215B40@@UAE?AUtype_1CB670@@XZ>1 @ 0x00424230

// match: ?vf_024@type_21CB10@@UAEHXZ @ 0x00215B70
// match: ??0type_215B40@@QAE@PBDPAUtype_21A5E0@@@Z @ 0x00215B40

type_215B40::type_215B40(const RwChar *arg_0, type_21A5E0 *arg_4) : type_216130(arg_0, arg_4)
{
}

// match: ??_Gtype_215B40@@UAEPAXI@Z @ 0x00215B80
// match: ??1type_215B40@@UAE@XZ @ 0x00215BB0
type_215B40::~type_215B40()
{
}

// The question: Vote game type, then the game type voted on.
// match: ?vf_058@type_215B40@@UAE?AUtype_1CB670@@XZ @ 0x00215BD0
// match: __ehhandler$?vf_058@type_215B40@@UAE?AUtype_1CB670@@XZ-0x3F @ 0x00306FD0
// match: __ehhandler$?vf_058@type_215B40@@UAE?AUtype_1CB670@@XZ @ 0x0030700F
type_1CB670 type_215B40::vf_058()
{
    type_1CB670 lv_2C;
    type_1CB670 lv_48;

    if (sub_1C4D00() == 1)
    {
        lv_2C = type_1CB670("Vote game type", 0);
        lv_48 = type_1CB670(sub_1C4E60(sub_1C4D20()), 0);
        add_text(lv_2C, lv_48);
    }
    return lv_2C;
}
