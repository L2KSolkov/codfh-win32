/*
 * The create session menu (in-game menu 0, game/livemenu.h): the create
 * session page over "CreateSession.layout", starting the game as the host
 * and going back to the menu it came from.
 */
#include "game/livemenu.h"
#include "game/ingamemenu.h"

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
