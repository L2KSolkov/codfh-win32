/*
 * The system link's create session menu (in-game menu 8, game/livemenu.h):
 * the create session page over "XboxSysLinkCreateSession.layout", starting
 * the game as the host over the system link and going back to the menu it
 * came from.
 */
#include "game/livemenu.h"
#include "game/ingamemenu.h"

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
