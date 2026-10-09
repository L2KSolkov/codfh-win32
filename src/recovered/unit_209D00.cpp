/*
 * In-game menu 11's sign-in page and the Live options (game/livemenu.h):
 * the options' actions, their text of the appearing status, and the one
 * options page (sub_20A540).
 */
#include <stdio.h>
#include "game/liveservice.h"
#include "game/livemenu.h"
#include "game/ingamemenu.h"
#include "game/frontend.h"
#include "game/startup.h"

// Its data definitions (PLAN M5), in the image's address order.
#ifndef CODFH_SP // MP only: unreferenced constants single player does not emit (not in default.xbe; /O2 keeps them only while they are external)
// 0x003E8C54
extern const RwReal flt_3E8C54 = 0.01f;
// 0x003E8C58
extern const RwReal flt_3E8C58 = 0.01f;
// 0x003E8C5C
extern const RwReal flt_3E8C5C = 16.666666f;
#endif
// End of its data definitions.


using namespace kujuUI;

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3E8C54@@3MB @ 0x003E8C54
// match: ?flt_3E8C58@@3MB @ 0x003E8C58
// match: ?flt_3E8C5C@@3MB @ 0x003E8C5C
// match: ??_7type_209D00@@6B@ @ 0x003E8C60

// match: ??0type_209D00@@QAE@XZ @ 0x00209D00

type_209D00::type_209D00() : type_2049D0("", 0, true)
{
    unk_188 = 1;
}

// match: ??_Gtype_209D00@@UAEPAXI@Z @ 0x00209D40
// match: ??1type_209D00@@UAE@XZ @ 0x00209D70
type_209D00::~type_209D00()
{
}

// match: ?vf_014@type_209D00@@UAEXM@Z @ 0x00209D90
void type_209D00::vf_014(RwReal arg_0)
{
    if (unk_188)
    {
        sub_227560()->sub_2270E0(2);
        unk_188 = 0;
    }
    if (sub_227560()->sub_2275D0() != 2)
    {
        sub_1E7CF0()->sub_1E7D90(this);
        unk_188 = 1;
    }
}










type_209E00 *dword_504578;






// Members /OPT:ICF folded into shared trivial bodies (config/aliases.txt): defined here for
// the authentic link (PLAN M7); the placement link takes the shared bodies.

// ?sub_1E41C0@type_209E00@@QAEXXZ (folded into the empty body at 0x1E41C0)
void type_209E00::sub_1E41C0()
{
}
