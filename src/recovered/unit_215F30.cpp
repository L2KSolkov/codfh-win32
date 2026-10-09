/*
 * The kick vote (game/ingamepages.h): a vote page and its question (slot 22),
 * built in two texts (type_1CB670, default-constructed out of line).
 */
#include "game/ingamepages.h"
#include "game/uiglue.h"

// Its data definitions (PLAN M5), in the image's address order.
#ifndef CODFH_SP // MP only: unreferenced constants single player does not emit (not in default.xbe; /O2 keeps them only while they are external)
// 0x003E966C
extern const RwReal flt_3E966C = 0.01f;
// 0x003E9670
extern const RwReal flt_3E9670 = 0.01f;
// 0x003E9674
extern const RwReal flt_3E9674 = 16.666666f;
#endif
// End of its data definitions.


// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3E966C@@3MB @ 0x003E966C
// match: ?flt_3E9670@@3MB @ 0x003E9670
// match: ?flt_3E9674@@3MB @ 0x003E9674
// match: ??_7type_215F30@@6B@ @ 0x003E9678
// match: ??_C@_0BD@BPPJLKBC@VOTE_KICK_PLAYER?$CF1?$AA@ @ 0x003E96D4
// match: __ehhandler$?vf_058@type_215F30@@UAE?AUtype_1CB670@@XZ>1>8 @ 0x00424290
// match: __ehhandler$?vf_058@type_215F30@@UAE?AUtype_1CB670@@XZ>1 @ 0x004242B8

// match: ??0type_215F30@@QAE@PBDPAUtype_21A5E0@@@Z @ 0x00215F30

type_215F30::type_215F30(const RwChar *arg_0, type_21A5E0 *arg_4) : type_216130(arg_0, arg_4)
{
}

// match: ??_Gtype_215F30@@UAEPAXI@Z @ 0x00215F60
// match: ??1type_215F30@@UAE@XZ @ 0x00215F90
type_215F30::~type_215F30()
{
}

// The question: the player voted on kicked ("VOTE_KICK_PLAYER%1").
// match: ?vf_058@type_215F30@@UAE?AUtype_1CB670@@XZ @ 0x00215FB0
// match: __ehhandler$?vf_058@type_215F30@@UAE?AUtype_1CB670@@XZ-0x3F @ 0x00307070
// match: __ehhandler$?vf_058@type_215F30@@UAE?AUtype_1CB670@@XZ @ 0x003070AF
type_1CB670 type_215F30::vf_058()
{
    type_1CB670 lv_2C;
    type_1CB670 lv_48;

    if (sub_1C4D00() == 2)
        lv_2C = sub_1CB7B0("VOTE_KICK_PLAYER%1", sub_1CB720(sub_1C4630(sub_1C4D20())).c_str(), 0);
    return lv_2C;
}
