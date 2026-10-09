/*
 * The cancel warnings (game/ingamepages.h): the one page showing a warning
 * over the game with its text and "Cancel", and the warnings' calls to
 * show, hide and retext it.
 */
#include "game/ingamepages.h"
#include "game/ingamescreens.h"
#include "game/gameloop.h"

// Its data definitions (PLAN M5), in the image's address order.
#ifndef CODFH_SP // MP only: unreferenced constants single player does not emit (not in default.xbe; /O2 keeps them only while they are external)
// 0x003E94CC
extern const RwReal flt_3E94CC = 0.01f;
// 0x003E94D0
extern const RwReal flt_3E94D0 = 0.01f;
// 0x003E94D4
extern const RwReal flt_3E94D4 = 16.666666f;
#endif
// 0x005051CC
type_215740 *dword_5051CC;
// End of its data definitions.


// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).
type_5051D0_quit dword_5051D0;
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3E94CC@@3MB @ 0x003E94CC
// match: ?flt_3E94D0@@3MB @ 0x003E94D0
// match: ?flt_3E94D4@@3MB @ 0x003E94D4
// match: ??_C@_07KGMMFLDN@Warning?$AA@ @ 0x003E94D8
// match: ??_7type_215740@@6B@ @ 0x003E94E0
// match: ??_C@_0BL@FMIEBLMM@CancelWarningScreen?4layout?$AA@ @ 0x003E9530
// match: ??_7?$type_3E7CE8@Utype_215740@@@kujuUI@@6B@ @ 0x003E954C
// match: ??_7type_5051D0_quit@@6B@ @ 0x003E955C
// match: ??_7type_5051D0@@6B@ @ 0x003E956C
// match: __ehhandler$??0type_215740@@QAE@PAUtype_21A5E0@@@Z>1>8 @ 0x004241A0
// match: __ehhandler$??0type_215740@@QAE@PAUtype_21A5E0@@@Z>1 @ 0x004241B8
// match: __ehhandler$??1type_215740@@UAE@XZ>1>8 @ 0x004241D4
// match: __ehhandler$??1type_215740@@UAE@XZ>1 @ 0x004241EC
// match: .CRT$XCU+0 @ 0x0042736C

// match: _$E1 @ 0x0030DB20

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

                if (!var_10->in_pause_menu())
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
    bool var_1 = (bool)(dword_5051CC->unk_154 == arg_0);

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
// match: __ehhandler$??0type_215740@@QAE@PAUtype_21A5E0@@@Z-0x24 @ 0x00306FA0
// match: __ehhandler$??0type_215740@@QAE@PAUtype_21A5E0@@@Z @ 0x00306FC4
type_215740::type_215740(type_21A5E0 *arg_0)
    : type_21CB10("CancelWarningScreen.layout", arg_0, 0), unk_154(0), unk_180(this, &type_215740::sub_2158B0)
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
    if (unk_154 == &dword_5051D0)
        return 4;
    return 0;
}

// match: ?sub_215910@type_215740@@SA_NPAUtype_5051D0@@@Z @ 0x00215910
bool type_215740::sub_215910(type_5051D0 *arg_0)
{
    return sub_215A50() && dword_5051CC->unk_154 == arg_0;
}

// match: ?processEvent@type_215740@@UAE?AW4eEventWasHandled@kujuUI@@ABVcStateChange@3@@Z @ 0x00215950
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
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
bool type_215740::sub_215A50()
{
    bool var_5;
    type_1FF250 *l4;

    l4 = sub_1FF250();
    var_5 = (bool)(l4 && l4->sub_200890(0xA));
    return var_5;
}

// match: ?sub_215A90@type_215740@@SA_NXZ @ 0x00215A90
bool type_215740::sub_215A90()
{
    return (bool)dword_5051CC->unk_154;
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

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?vf_000@type_5051D0_quit@@UAEXXZ (folded into 0x21E9A0)
void type_5051D0_quit::vf_000()
{
    sub_1C44A0();
}

// ?vf_004@type_5051D0_quit@@UAE_NXZ (folded into 0x1E4AA0)
bool type_5051D0_quit::vf_004()
{
    return false;
}

// ?vf_00C@type_5051D0_quit@@UAEHXZ (folded into 0x9E000)
RwInt32 type_5051D0_quit::vf_00C()
{
    return 4;
}

// ?vf_008@type_5051D0@@UAEXXZ (folded into 0x1E41C0)
void type_5051D0::vf_008()
{
}
