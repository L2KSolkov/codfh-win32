/*
 * The in-game screens (unit_1FF250; its traces call it "IngameScreens"):
 * the pause menu, the in-game controls' legend and the eleven screens shown
 * over the game (the scoreboards, the team selection, the error screens).
 */
#ifndef GAME_INGAMESCREENS_H
#define GAME_INGAMESCREENS_H

#include "rw/ostypes.h"

struct type_1FBDA0_menu;
struct type_21A5E0;
namespace kujuUI {
struct type_3E75B8;
}

// The screens (0x44 bytes; the one instance, dword_5043BC, is given by
// sub_1FF250): the pause menu (unk_00, loaded from "PauseMenu.layout") and
// whether it is shown (unk_04: sub_2006A0 shows or hides it, pushing the
// root widget unk_08 onto the pad's widget stack; sub_1EF160, shared
// through /OPT:ICF, reads it); the screen picked (unk_0C, sub_2008B0; the
// screen itself, sub_200900; whether it exists, sub_200890) and whether it
// is shown (unk_3C: sub_2007A0 and sub_200780); the screens (unk_10:
// sub_1FF3F0 builds them for the game type, deathmatch or team, and
// sub_1FFD10 deletes them); the legend's flags last shown (unk_40,
// sub_1FFE80). sub_2003E0 runs a frame of them, sub_200630 rebuilds the
// screens, sub_200920 tells the screen shown to act (its slot 19).
struct type_1FF250
{
    type_21A5E0 *unk_00;
    bool unk_04;
    kujuUI::type_3E75B8 *unk_08;
    RwInt32 unk_0C;
    type_1FBDA0_menu *unk_10[11];
    bool unk_3C;
    RwInt32 unk_40;

    type_1FF250();
    ~type_1FF250();
    // An inline accessor for unk_0C, with no address and so no database
    // name; named for its field. Evidence: the HUD's render
    // (type_DC400::sub_DF000) reads it through a `this` copy and a return
    // slot of their own.
    RwInt32 get_unk_0C()
    {
        return unk_0C;
    }
    void sub_1FF3F0();
    void sub_1FFD10();
    void sub_1FFE80();
    void sub_2003E0(RwReal arg_0);
    void sub_200630();
    bool sub_2006A0(bool arg_0);
    bool sub_200740();
    bool sub_200780();
    bool sub_2007A0(bool arg_0);
    bool sub_200890(RwInt32 arg_0);
    bool sub_2008B0(RwInt32 arg_0);
    type_1FBDA0_menu *sub_200900();
    void sub_200920();
    bool sub_1EF160();
};
extern type_1FF250 *dword_5043BC;
type_1FF250 *sub_1FF250();
// A compiled-out check that the screens are the one instance: no code, but
// its test of `this` moves the compiler's register rotation (the
// constructor, destructor and frame, sub_1FF260, sub_1FFD70, sub_2003E0).
#define INGAMESCREENS_CHECK() { if (dword_5043BC != this) { } }

#endif
