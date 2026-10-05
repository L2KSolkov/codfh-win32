/*
 * The system link's session list (in-game menu 9, game/livemenu.h): the
 * session list page over "XboxSysLinkSessionList.layout".
 */
#include "game/livemenu.h"
#include "game/ingamemenu.h"

// The this-adjusting thunk the columns' vtable (off_3E8BBC) holds for the
// deleting destructor.
// match: ??_Etype_209BF0@@WBII@AEPAXI@Z @ 0x00209CF0

// match: ??0type_209BF0@@QAE@XZ @ 0x00209BF0
type_209BF0::type_209BF0() : type_20C470("XboxSysLinkSessionList.layout", true)
{
}

// match: ??_Gtype_209BF0@@UAEPAXI@Z @ 0x00209C30
// match: ??1type_209BF0@@UAE@XZ @ 0x00209C60
type_209BF0::~type_209BF0()
{
}

// match: ?vf_04C@type_209BF0@@UAEXXZ @ 0x00209C90
void type_209BF0::vf_04C()
{
    type_2053C0::sub_205BF0(2);
    sub_1FC310()->sub_1FBDA0(sub_2046C0(8));
}

// match: ?vf_048@type_209BF0@@UAEXXZ @ 0x00209CC0
void type_209BF0::vf_048()
{
    sub_1FC310()->sub_1FBDA0(sub_2046C0(10));
}
