/*
 * The Live menus' base (unit_20E850): a top layout page loaded from the
 * layout arg_0 with objects of its own by name (unk_118) and the "LiveMenu"
 * action (unk_124), which shows the front end's Live screen while the Xbox
 * Live voice runs. The Live menus (game/livemenu.h) and the in-game pages
 * (game/ingamepages.h) build on it.
 */
#ifndef GAME_LIVEBASE_H
#define GAME_LIVEBASE_H

#include "game/kujuilayout.h"

// The Live menus' base (off_3E92F8, 0x130 bytes): loaded from the layout
// arg_0 (none when it is empty) with the widgets' names arg_4, its objects
// by name (unk_118, which it registers with the layout; sub_204FC0 adds
// arg_4 under the name arg_0) and the "LiveMenu" action over sub_20EA00
// (unk_124). Its update (slot 5) is the layout page's; sub_20EA40 loads it
// to the end, suspending the async loader's work the first time.
struct type_20E850 : kujuUI::cTopLayoutPage
{
    kujuUI::type_1EFCF0<kujuUI::type_3E70B0> unk_118;
    kujuUI::type_3E7CE8<type_20E850> unk_124;

    type_20E850(const RwChar *arg_0, kujuUI::type_1EFCF0<kujuUI::type_3E7D08 *> *arg_4);
    virtual ~type_20E850();
    virtual void vf_014(RwReal arg_0);
    void sub_204FC0(const RwChar *arg_0, kujuUI::type_3E70B0 *arg_4);
    void sub_20EA00();
    void sub_20EA40();
};

#endif
