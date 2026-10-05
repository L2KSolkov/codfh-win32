/*
 * The cancel warnings (game/ingamepages.h): the one page showing a warning
 * over the game with its text and "Cancel", and the warnings' calls to
 * show, hide and retext it.
 */
#include "game/ingamepages.h"
#include "game/ingamescreens.h"
#include "game/gameloop.h"

using namespace kujuUI;

// match: ?sub_2155A0@type_215740@@SA_NPAUtype_5051D0@@@Z @ 0x002155A0
bool type_215740::sub_2155A0(type_5051D0 *arg_0)
{
    if (!dword_5051CC->unk_154)
    {
        dword_5051CC->unk_154 = arg_0;
        type_1FF250 *var_8 = sub_1FF250();

        dword_5051CC->unk_18C = 0xB;
        if (var_8->sub_200740() && !var_8->sub_1EF160())
        {
            RwInt32 var_C = var_8->unk_0C;

            if (var_C == 6 || var_C == 7)
            {
                type_21CB10 *var_10 = (type_21CB10 *)var_8->sub_200900();

                if (!(var_10->unk_130 != 0))
                    dword_5051CC->unk_18C = var_C;
            }
        }
        var_8->sub_2006A0(true);
        var_8->sub_2008B0(0xA);
        var_8->sub_2007A0(true);
    }
    else if (dword_5051CC->unk_154->vf_004())
    {
        dword_5051CC->unk_154 = arg_0;
    }
    bool var_1 = dword_5051CC->unk_154 == arg_0;

    return var_1;
}

// match: ?sub_2156B0@type_215740@@SAXPAUtype_5051D0@@@Z @ 0x002156B0
void type_215740::sub_2156B0(type_5051D0 *arg_0)
{
    if (arg_0 == dword_5051CC->unk_154)
    {
        if (dword_5051CC->unk_18C != 0xB)
        {
            sub_1FF250()->sub_2008B0(dword_5051CC->unk_18C);
            sub_1FF250()->sub_2007A0(true);
            sub_D7C10(false);
        }
        else
        {
            sub_1FF250()->sub_2006A0(false);
            sub_1FF250()->sub_2007A0(false);
        }
        dword_5051CC->unk_154 = 0;
    }
}

// match: ??0type_215740@@QAE@PAUtype_21A5E0@@@Z @ 0x00215740
type_215740::type_215740(type_21A5E0 *arg_0)
    : type_21CB10("CancelWarnings.layout", arg_0, 0), unk_154(0), unk_180(this, &type_215740::sub_2158B0)
{
    sub_204FC0("Warning", &unk_158);
    sub_204FC0("Cancel", &unk_180);
    sub_20EA40();
    dword_5051CC = this;
}

// match: ??_Gtype_215740@@UAEPAXI@Z @ 0x00215820
// match: ??1type_215740@@UAE@XZ @ 0x002159A0
type_215740::~type_215740()
{
    if (unk_154)
    {
        unk_154->vf_008();
        unk_154 = 0;
    }
    dword_5051CC = 0;
}

// match: ?vf_00C@type_215740@@UAEXXZ @ 0x00215850
void type_215740::vf_00C()
{
    if (unk_154)
    {
        unk_154->vf_008();
        unk_154 = 0;
    }
}

// match: ?vf_008@type_215740@@UAEXXZ @ 0x00215890
void type_215740::vf_008()
{
    sub_1FF250()->sub_2006A0(false);
}

// match: ?sub_2158B0@type_215740@@QAEXXZ @ 0x002158B0
void type_215740::sub_2158B0()
{
    unk_154->vf_000();
}

// match: ?vf_024@type_215740@@UAEHXZ @ 0x002158E0
RwInt32 type_215740::vf_024()
{
    return unk_154 == &dword_5051D0 ? 4 : 0;
}

// match: ?sub_215910@type_215740@@SA_NPAUtype_5051D0@@@Z @ 0x00215910
bool type_215740::sub_215910(type_5051D0 *arg_0)
{
    return sub_215A50() && dword_5051CC->unk_154 == arg_0;
}

// match: ?processEvent@type_215740@@UAE?AW4eEventWasHandled@kujuUI@@ABUcStateChange@3@@Z @ 0x00215950
eEventWasHandled type_215740::processEvent(const cStateChange &arg_0)
{
    cTopLayoutPage::processEvent(arg_0);
    return (eEventWasHandled)0;
}

// match: ?sub_215970@type_215740@@SAXABUtype_1A5EA0@@PAUtype_5051D0@@@Z @ 0x00215970
void type_215740::sub_215970(const type_1A5EA0 &arg_0, type_5051D0 *arg_4)
{
    if (dword_5051CC->unk_154 == arg_4)
        dword_5051CC->unk_158.sub_1F28C0(arg_0);
}

// match: ?sub_215A50@type_215740@@SA_NXZ @ 0x00215A50
bool type_215740::sub_215A50()
{
    type_1FF250 *var_4 = sub_1FF250();
    bool var_5 = (bool)(var_4 && var_4->sub_200890(0xA));

    return var_5;
}

// match: ?sub_215A90@type_215740@@SA_NXZ @ 0x00215A90
bool type_215740::sub_215A90()
{
    return dword_5051CC->unk_154 != 0;
}

// The action's members (game/kujuui.h's template, its definitions
// repeated here).
// match: ??0?$type_3E7CE8@Utype_215740@@@kujuUI@@QAE@PAUtype_215740@@P82@AEXXZ@Z @ 0x00215AB0
template <class T> type_3E7CE8<T>::type_3E7CE8(T *arg_0, void (T::*arg_4)())
{
    unk_04 = arg_0;
    unk_08 = arg_4;
}

// match: ??_G?$type_3E7CE8@Utype_215740@@@kujuUI@@UAEPAXI@Z @ 0x00215B10
// match: ??1?$type_3E7CE8@Utype_215740@@@kujuUI@@UAE@XZ @ 0x00215AF0
template <class T> type_3E7CE8<T>::~type_3E7CE8()
{
}

template <class T> void type_3E7CE8<T>::pvf_008()
{
    (unk_04->*unk_08)();
}
