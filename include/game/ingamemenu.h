/*
 * The in-game menus' manager (unit_1FBBF0; named by its traces,
 * "InGameMenuManager::ShowMenu()" and "::KillMenu()"): the one instance
 * (dword_5043B0) runs the menu shown over the game, passing kujuUI's
 * events, updates and drawing to the pad's widget stack.
 */
#ifndef GAME_INGAMEMENU_H
#define GAME_INGAMEMENU_H

#include "game/kujuilayout.h"

// An in-game menu: a top layout page with slots of its own, told it is
// shown (slot 15) and hidden (slot 16), reset before it is shown
// (sub_20EA40), and told to act (slot 19, the in-game screens'
// sub_200920). Only these are known.
struct type_1FBDA0_menu : kujuUI::cTopLayoutPage
{
    virtual void vf_03C();
    virtual void vf_040();
    virtual void vf_044();
    virtual void vf_048();
    virtual void vf_04C();
    void sub_20EA40();
};

// The manager (off_3E7E68, 0x10 bytes): the menu shown (unk_04), the pad's
// event source it reads (unk_08, kept in dword_5043B4) and the time of its
// last frame (unk_0C). It updates (sub_1FBD00, while a menu is shown) and
// draws (sub_1FBD40) the pad's widget stack and passes it its events;
// shows the menu arg_0 (sub_1FBDA0) and hides the one shown (sub_1FBE20);
// runs the menus on the camera arg_0 until none is shown (sub_1FBE70).
class InGameMenuManager : public kujuUI::type_3E6CE4
{
public:
    type_1FBDA0_menu *unk_04;
    struct kujuUI::type_1E3DB0 *unk_08;
    RwUInt32 unk_0C;

    InGameMenuManager(type_1FBDA0_menu *arg_0);
    virtual ~InGameMenuManager();
    virtual kujuUI::eEventWasHandled processEvent(const kujuUI::cStateChange &arg_0);
    // Whether a menu is shown: an inline with no address, named for what it
    // gives. Evidence: sub_1FBD00 and sub_1FBE70 test it through setne.
    bool showing()
    {
        return unk_04 != 0;
    }
    void sub_1FBD00(RwReal arg_0);
    void sub_1FBD40(kujuUI::type_1E4130 *arg_0);
    void sub_1FBDA0(type_1FBDA0_menu *arg_0);
    void sub_1FBE20();
    void sub_1FBE70(RwCamera *arg_0);
};
extern InGameMenuManager *dword_5043B0;
// The in-game menu arg_0 (sub_2046C0) and the menus' clean-up (sub_204620);
// the front end's sound settings reset and restored (sub_1C40F0,
// sub_1C41F0); the colour the menus' camera is cleared to (unk_5043B8).
type_1FBDA0_menu *sub_2046C0(RwInt32 arg_0);
void sub_204620();
// The in-game menus' loading (sub_204100 starts it, sub_204700 runs a
// step of it, sub_204750 whether it is done) and the menu the shell opens
// with (dword_5044DC: 0 marks the front end's setting sub_1C4F70 too);
// only the widths are known.
void sub_204100();
void sub_204700();
bool sub_204750();
// The menu arg_0 queued to load unless it is loaded (sub_204020); all of
// them queued (sub_204060); whether any are built (sub_2046E0).
void sub_204020(RwInt32 arg_0);
// How many menus are loaded (or failed and given up on).
RwInt32 sub_204770();
void sub_204060();
bool sub_2046E0();
extern RwInt32 dword_5044DC;
void sub_1C40F0();
void sub_1C41F0();
extern RwRGBA unk_5043B8;
extern kujuUI::type_1E3DB0 *dword_5043B4;
InGameMenuManager *sub_1FC310();

#endif
