/*
 * The Xbox Live session list (in-game menu 7, game/livemenu.h): the session
 * list page over "SessionList.layout".
 */
#include "types/cXboxLive.h"
#include "game/livemenu.h"
#include "game/ingamemenu.h"
#include "types/type_DC400.h"

// The this-adjusting thunk the columns' vtable (off_3E90E4) holds for the
// deleting destructor.
// match: ??_Etype_20C2F0@@WBII@AEPAXI@Z @ 0x0020C460

// match: ??0type_20C2F0@@QAE@XZ @ 0x0020C2F0
type_20C2F0::type_20C2F0() : type_20C470("SessionList.layout", true)
{
}

// match: ??_Gtype_20C2F0@@UAEPAXI@Z @ 0x0020C330
// match: ??1type_20C2F0@@UAE@XZ @ 0x0020C360
type_20C2F0::~type_20C2F0()
{
}

// match: ?vf_048@type_20C2F0@@UAEXXZ @ 0x0020C390
void type_20C2F0::vf_048()
{
    sub_1FC310()->sub_1FBDA0(sub_2046C0(1));
}

// match: ?vf_04C@type_20C2F0@@UAEXXZ @ 0x0020C3C0
void type_20C2F0::vf_04C()
{
    type_2053C0::sub_205BF0(2);
    sub_1FC310()->sub_1FBDA0(sub_2046C0(0));
}

// match: ?vf_054@type_20C2F0@@UAEXXZ @ 0x0020C3F0
void type_20C2F0::vf_054()
{
    sub_20CB20();
}

// match: ?vf_058@type_20C2F0@@UAEXXZ @ 0x0020C410
void type_20C2F0::vf_058()
{
    type_4F8054 *var_8 = dword_4F8054;
    type_4F8054_B0 *var_4 = var_8->unk_B0;

    if (!var_8 || !var_4)
        return;
    var_4->sub_1CD370();
    var_8->sub_1CC8F0(7, 10);
}
