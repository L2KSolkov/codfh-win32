/*
 * The create session menu (in-game menu 0, game/livemenu.h): the create
 * session page over "CreateSession.layout", starting the game as the host
 * and going back to the menu it came from.
 */
#include "game/livemenu.h"
#include "game/ingamemenu.h"

// Its data definitions (PLAN M5), in the image's address order.
#ifndef CODFH_SP // MP only: unreferenced constants single player does not emit (not in default.xbe; /O2 keeps them only while they are external)
// 0x003E86F4
extern const RwReal flt_3E86F4 = 0.01f;
// 0x003E86F8
extern const RwReal flt_3E86F8 = 0.01f;
// 0x003E86FC
extern const RwReal flt_3E86FC = 16.666666f;
#endif
// End of its data definitions.


// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3E86F4@@3MB @ 0x003E86F4
// match: ?flt_3E86F8@@3MB @ 0x003E86F8
// match: ?flt_3E86FC@@3MB @ 0x003E86FC
// match: ??_7type_206190@@6Btype_200B90@@@ @ 0x003E8700
// match: ??_7type_206190@@6Btype_2049D0@@@ @ 0x003E8708
// match: ??_C@_0BF@IMDLHAFH@CreateSession?4layout?$AA@ @ 0x003E8754

// match: ??0type_206190@@QAE@XZ @ 0x00206190

type_206190::type_206190() : type_2053C0("CreateSession.layout", true)
{
}

// match: ??_Gtype_206190@@UAEPAXI@Z @ 0x002061D0
// match: ??1type_206190@@UAE@XZ @ 0x00206200
type_206190::~type_206190()
{
}

// match: ?vf_044@type_206190@@UAEXXZ @ 0x00206230
void type_206190::vf_044()
{
    startServer(true);
}

// match: ?vf_048@type_206190@@UAEPAUtype_1FBDA0_menu@@XZ @ 0x00206250
type_1FBDA0_menu *type_206190::vf_048()
{
    type_1FBDA0_menu *var_4 = 0;

    switch (sub_205C00())
    {
    case 0:
        var_4 = sub_2046C0(6);
        break;
    case 1:
        var_4 = sub_2046C0(1);
        break;
    case 2:
        var_4 = sub_2046C0(7);
        break;
    }
    return var_4;
}
