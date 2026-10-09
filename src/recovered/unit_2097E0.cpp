/*
 * The system link's create session menu (in-game menu 8, game/livemenu.h):
 * the create session page over "XboxSysLinkCreateSession.layout", starting
 * the game as the host over the system link and going back to the menu it
 * came from.
 */
#include "game/livemenu.h"
#include "game/ingamemenu.h"

// Its data definitions (PLAN M5), in the image's address order.
#ifndef CODFH_SP // MP only: unreferenced constants single player does not emit (not in default.xbe; /O2 keeps them only while they are external)
// 0x003E8A98
extern const RwReal flt_3E8A98 = 0.01f;
// 0x003E8A9C
extern const RwReal flt_3E8A9C = 0.01f;
// 0x003E8AA0
extern const RwReal flt_3E8AA0 = 16.666666f;
#endif
// End of its data definitions.


// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3E8A98@@3MB @ 0x003E8A98
// match: ?flt_3E8A9C@@3MB @ 0x003E8A9C
// match: ?flt_3E8AA0@@3MB @ 0x003E8AA0
// match: ??_7type_2097E0@@6Btype_200B90@@@ @ 0x003E8AA4
// match: ??_7type_2097E0@@6Btype_2049D0@@@ @ 0x003E8AA8
// match: ??_C@_0CA@PCIFMNPB@XboxSysLinkCreateSession?4layout?$AA@ @ 0x003E8AF4

// match: ??0type_2097E0@@QAE@XZ @ 0x002097E0

type_2097E0::type_2097E0() : type_2053C0("XboxSysLinkCreateSession.layout", true)
{
}

// match: ??_Gtype_2097E0@@UAEPAXI@Z @ 0x00209820
// match: ??1type_2097E0@@UAE@XZ @ 0x00209850
type_2097E0::~type_2097E0()
{
}

// match: ?vf_044@type_2097E0@@UAEXXZ @ 0x00209880
void type_2097E0::vf_044()
{
    startServer(false);
}

// match: ?vf_048@type_2097E0@@UAEPAUtype_1FBDA0_menu@@XZ @ 0x002098A0
type_1FBDA0_menu *type_2097E0::vf_048()
{
    type_1FBDA0_menu *var_4 = 0;

    switch (sub_205C00())
    {
    case 0:
        var_4 = sub_2046C0(10);
        break;
    case 2:
        var_4 = sub_2046C0(9);
        break;
    }
    return var_4;
}
