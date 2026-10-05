/*
 * A sign-in page with no layout of its own (game/ingamepages.h): the
 * service started last asked for step 6, and back while its state is not
 * 6.
 */
#include "game/liveservice.h"
#include "game/ingamepages.h"
#include "game/startup.h"

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_7type_218F40@@6B@ @ 0x003E9D40

// match: ??0type_218F40@@QAE@PAUtype_21A5E0@@@Z @ 0x00218F40

type_218F40::type_218F40(type_21A5E0 *arg_0) : type_21CB10("", arg_0, 0)
{
}

// match: ??_Gtype_218F40@@UAEPAXI@Z @ 0x00218F70
// match: ??1type_218F40@@UAE@XZ @ 0x00218FA0
type_218F40::~type_218F40()
{
}

// match: ?vf_008@type_218F40@@UAEXXZ @ 0x00218FC0
void type_218F40::vf_008()
{
    sub_227560()->sub_2270E0(6);
}

// match: ?vf_014@type_218F40@@UAEXM@Z @ 0x00218FE0
void type_218F40::vf_014(RwReal arg_0)
{
    if (sub_227560()->sub_2275D0() != 6)
        vf_040();
}

// type_218F40's vf_00C: type_219C20's code (ICF folded them, at 0x219CC0).
void type_218F40::vf_00C()
{
    sub_227560()->sub_227530();
}
