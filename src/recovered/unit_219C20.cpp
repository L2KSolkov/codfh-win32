/*
 * A sign-in page with no layout of its own (game/ingamepages.h): the
 * service started last asked for step 7, its Live feature ended when left,
 * and back while its state is not 7.
 */
#include "game/liveservice.h"
#include "game/ingamepages.h"
#include "game/startup.h"

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_7type_219C20@@6B@ @ 0x003E9E68

// match: ??0type_219C20@@QAE@PAUtype_21A5E0@@@Z @ 0x00219C20

type_219C20::type_219C20(type_21A5E0 *arg_0) : type_21CB10("", arg_0, 0)
{
}

// match: ??_Gtype_219C20@@UAEPAXI@Z @ 0x00219C50
// match: ??1type_219C20@@UAE@XZ @ 0x00219C80
type_219C20::~type_219C20()
{
}

// match: ?vf_008@type_219C20@@UAEXXZ @ 0x00219CA0
void type_219C20::vf_008()
{
    sub_227560()->sub_2270E0(7);
}

// match: ?vf_00C@type_219C20@@UAEXXZ @ 0x00219CC0
void type_219C20::vf_00C()
{
    sub_227560()->sub_227530();
}

// match: ?vf_014@type_219C20@@UAEXM@Z @ 0x00219CE0
void type_219C20::vf_014(RwReal arg_0)
{
    if (sub_227560()->sub_2275D0() != 7)
        vf_040();
}
