/*
 * The Live menus (game/livebase.h has their base): the login pages, the
 * create session and session list pages, and the in-game menus 0 to 13.
 */
#ifndef GAME_LIVEMENU_H
#define GAME_LIVEMENU_H

#include "game/livebase.h"
#include "game/hostoptions.h"
#include "game/browser.h"
#include <list>

struct type_1FBDA0_menu;


struct type_204B10;
// The Live login pages' base (off_3E84A0, 0x188 bytes): the player's name
// ("LoginPlayerName", unk_130; set by sub_205050) and friends list
// ("LoginFriendsList", unk_158), the entry picked (unk_180, cleared by
// slot 15), and whether it shows the network warning (unk_184): the pages
// that do count themselves (dword_504570), the first building the warning
// (dword_50456C) and the last deleting it. Its update (slot 5) shows the
// Live status (sub_205070), opens the in-game menu 13 when dword_504568
// asks, runs the in-game menus' loading and pushes the warning onto the
// pad's widget stack while the network game is down (sub_204E50) and
// kujuUI is not drawing (byte_50438C). Slot 6 is folded (/OPT:ICF) with
// another page's (0x21B8D0).
struct type_2049D0 : type_20E850
{
    kujuUI::type_1F28C0 unk_130;
    kujuUI::type_1F28C0 unk_158;
    RwInt32 unk_180;
    bool unk_184;

    type_2049D0(const RwChar *arg_0, kujuUI::type_1EFCF0<kujuUI::type_3E7D08 *> *arg_4, bool arg_8);
    virtual ~type_2049D0();
    virtual void vf_014(RwReal arg_0);
    virtual void vf_018(kujuUI::type_1E4130 *arg_0);
    virtual void givenFocus();
    virtual void lostFocus();
    virtual void vf_03C();
    virtual void vf_040();
    static bool sub_204E50();
    // Whether the pages may search: always (0x204EA0).
    static bool sub_204EA0();
    void sub_205050(const type_1A5EA0 &arg_0);
    void sub_205070(RwInt32 arg_0);
    // Pushed onto the pad's widget stack (0x20A520): the Live options'
    // "FriendsList" pushes its sign-in page, the Live base's check pushes
    // the Live options.
    void sub_20A520();
};
// The Live sign-in statuses' texts ("Not signed in.", "Signing in...",
// "Sign-In Failed", "Not Signed In: Passcode Needed", "Signed in:"; the
// Live login pages' status text, sub_205070).
extern const RwChar *dword_42D278[5];
extern RwInt32 dword_504570;
extern type_204B10 *dword_50456C;
extern RwInt32 dword_504568;
extern RwInt32 dword_504574;
// The text arg_0 with zero to three dots (sub_1CBA30) cycling four times a
// second as the time flt_505180 advances by arg_4 (the searching pages'
// "Searching...").
type_1CB670 sub_20EB30(const type_1CB670 &arg_0, RwReal arg_4);
extern RwReal flt_505180;

// The network warning ("NetworkWarningContext.layout", off_3E8500, 0x1BC
// bytes): an "Acknowledge" action (unk_188, over sub_204C50: back to the
// in-game menu 13 with the pad's stack emptied) and a "Countdown" text
// (unk_194, emptied by its update).
struct type_204B10 : type_2049D0
{
    kujuUI::type_3E7CE8<type_204B10> unk_188;
    kujuUI::type_1F28C0 unk_194;

    type_204B10();
    virtual ~type_204B10();
    virtual void vf_014(RwReal arg_0);
    void sub_204C50();
};

// The create session page (off_3E8688 and, over its host options,
// off_3E8680; 0x710 bytes; sub_2053C0 builds it over the layout arg_0,
// with arg_4 for its login page): the host's options (the second base),
// the actions "Create" (unk_528, allowed while the name has a character
// other than a space, sub_205F70), "Back" (unk_540), and "OpenAdvanced",
// "CancelAdvanced" and "CloseAdvanced" (unk_550 to unk_570) for the
// advanced options' page (unk_580), with the focus kept for each (unk_708,
// unk_70C). Slot 15 fills its texts (sub_205880); slots 17 and 18 (pure)
// run the session made and give the menu to go back to. The last page's
// number is kept in dword_42D28C (set by sub_205BF0, given by sub_205C00).
struct type_2053C0 : type_2049D0, type_200B90
{
    kujuUI::type_3E7264<type_2053C0> unk_528;
    kujuUI::type_3E7CE8<type_2053C0> unk_540;
    kujuUI::type_3E7CE8<type_2053C0> unk_550;
    kujuUI::type_3E7CE8<type_2053C0> unk_560;
    kujuUI::type_3E7CE8<type_2053C0> unk_570;
    type_2049D0 unk_580;
    kujuUI::type_3E7D08 *unk_708;
    kujuUI::type_3E7D08 *unk_70C;

    type_2053C0(const RwChar *arg_0, bool arg_4);
    virtual ~type_2053C0();
    virtual void vf_014(RwReal arg_0);
    virtual void vf_03C();
    virtual void vf_044() = 0;
    virtual type_1FBDA0_menu *vf_048() = 0;
    // The host options' slot 0, told of a change: the defaults for the
    // game type picked (1, 2, 4 and 8).
    virtual void vf_00();
    void sub_205A40();
    void sub_205A90();
    void sub_205AD0();
    void sub_205B40();
    void sub_205BA0();
    static void sub_205BF0(RwInt32 arg_0);
    static RwInt32 sub_205C00();
    void sub_205C10();
    bool sub_205F70();
};
extern RwInt32 dword_42D28C;

// The create session menu (in-game menu 0, off_3E8708 and off_3E8700):
// the create session page over "CreateSession.layout", starting the game as
// the host (slot 17) and giving the menu it came from (slot 18: 6, 1 or 7
// for the pages 0, 1 and 2).
struct type_206190 : type_2053C0
{
    type_206190();
    virtual ~type_206190();
    virtual void vf_044();
    virtual type_1FBDA0_menu *vf_048();
};

// The find session page (in-game menu 1, "FindSession.layout", off_3E87C0,
// 0x310 bytes): set once built (unk_188); the actions "Find" (unk_18C,
// sub_206960: the search set from its settings, then the in-game menu 7),
// "Back" (unk_198, sub_206FC0), "ResetSettings" (unk_1A4, sub_206850, also
// run when it is shown) and the players' and rules' hooks (unk_1B0,
// sub_206AE0: the minimum players kept below the players picked; unk_1BC,
// empty); its settings: the game type (unk_1C8), the level (unk_1E8), the
// players (unk_208), the minimum players (unk_228), the game subtype, team
// balance and friendly fire (unk_2A4 to unk_2E4); its widgets by name
// (unk_304).
struct type_2062B0 : type_2049D0
{
    RwInt32 unk_188;
    kujuUI::type_3E7CE8<type_2062B0> unk_18C;
    kujuUI::type_3E7CE8<type_2062B0> unk_198;
    kujuUI::type_3E7CE8<type_2062B0> unk_1A4;
    kujuUI::type_3E7CE8<type_2062B0> unk_1B0;
    kujuUI::type_3E7CE8<type_2062B0> unk_1BC;
    type_210180 unk_1C8;
    type_211680 unk_1E8;
    type_213680 unk_208;
    kujuUI::type_1E76A0 unk_228;
    type_214A90 unk_2A4;
    type_214A90 unk_2C4;
    type_214A90 unk_2E4;
    kujuUI::type_1EFCF0<kujuUI::type_3E7D08 *> unk_304;

    type_2062B0();
    virtual ~type_2062B0();
    virtual void vf_03C();
    void sub_206850();
    void sub_206960();
    void sub_206AE0();
    // The instant action page's "Back" (shared through /OPT:ICF).
    void sub_206FC0();
    // Empty: shared through /OPT:ICF.
    void sub_1E41C0();
};
// The search's settings (the game type's three rules, 4 for any) and its
// minimum players.
extern RwInt32 dword_42CBA8;
extern RwInt32 dword_42CBAC;
extern RwInt32 dword_42CBB0;
extern RwInt32 dword_4FDAA0;

// The instant action page (in-game menu 2, "InstantAction.layout",
// off_3E8868, 0x1E4 bytes): an action per game type ("Any", 0x20;
// "Deathmatch", 1; "TeamDeathmatch", 2; "CaptureTheFlag", 4;
// "SearchAndDestroy", 8: unk_188 to unk_1C8, each running sub_206F90 with
// its type: a game found at once, then the in-game menu 3) and "Back"
// (unk_1D8, sub_206FC0: the in-game menu 6).
struct type_206D10 : type_2049D0
{
    kujuUI::type_3E88C4<type_206D10> unk_188;
    kujuUI::type_3E88C4<type_206D10> unk_198;
    kujuUI::type_3E88C4<type_206D10> unk_1A8;
    kujuUI::type_3E88C4<type_206D10> unk_1B8;
    kujuUI::type_3E88C4<type_206D10> unk_1C8;
    kujuUI::type_3E7CE8<type_206D10> unk_1D8;

    type_206D10();
    virtual ~type_206D10();
    void sub_206F90(RwInt32 arg_0);
    void sub_206FC0();
};
// Sets the game type the instant action searches with (dword_42D294).
void sub_208990(RwInt32 arg_0);

struct type_1D9270_session;
// A session found by the instant action's search with its score
// (sub_207A40); ordered by score, highest first (operator<, out of line,
// compares the other way round).
struct type_207140
{
    type_1D9270_session *unk_00;
    RwInt32 unk_04;

    bool operator<(const type_207140 &arg_0) const;
};

// The instant action's results (in-game menu 3, "InstantActionDetails.layout",
// off_3E8968, 0x8730 bytes): the pages shown while searching
// ("Searching.layout", unk_188), after a failed join ("JoinFailed.layout",
// unk_310) and when nothing is found ("NoSessionsFound.layout", unk_498);
// the session's "Details" (unk_620); the actions "Back" (unk_648 and
// unk_66C), "Join" (unk_654), "Next" (unk_660), "Create" (unk_678) and the
// empty page's "Back" (unk_684); the failure's "Reason" and "FailHeader"
// and the search's "SearchText" (unk_690, unk_6B8, unk_6E0); the search's
// settings (unk_708 to unk_712, as the network game's session settings),
// whether a search runs (unk_714), the sessions found with their scores
// (unk_718, the one shown unk_724) and their buffer (unk_728), whether a
// join runs (unk_8728) and unk_872C.
struct type_207160 : type_2049D0
{
    type_2049D0 unk_188;
    type_2049D0 unk_310;
    type_2049D0 unk_498;
    kujuUI::type_1F28C0 unk_620;
    kujuUI::type_3E7CE8<type_207160> unk_648;
    kujuUI::type_3E7CE8<type_207160> unk_654;
    kujuUI::type_3E7CE8<type_207160> unk_660;
    kujuUI::type_3E7CE8<type_207160> unk_66C;
    kujuUI::type_3E7CE8<type_207160> unk_678;
    kujuUI::type_3E7CE8<type_207160> unk_684;
    kujuUI::type_1F28C0 unk_690;
    kujuUI::type_1F28C0 unk_6B8;
    kujuUI::type_1F28C0 unk_6E0;
    RwChar *unk_708;
    RwUInt8 unk_70C;
    RwUInt8 unk_70D[4];
    RwUInt8 unk_711;
    RwUInt16 unk_712;
    RwInt32 unk_714;
    std::list<type_207140> unk_718;
    std::list<type_207140>::iterator unk_724;
    RwUInt8 unk_728[0x8000];
    bool unk_8728;
    RwInt32 unk_872C;

    type_207160();
    virtual ~type_207160();
    virtual void vf_014(RwReal arg_0);
    virtual void vf_03C();
    void sub_207650();
    // +0x040: its override (sub_2076D0), as its vtable has it.
    virtual void vf_040();
    void sub_207720();
    void sub_207880();
    static RwInt32 sub_207A40(type_1D9270_session *arg_0, RwInt32 arg_4, RwInt32 arg_8);
    void sub_207AE0();
    void sub_207D10();
    void sub_207D90();
    void sub_207E30();
    void sub_208400();
    bool sub_2089A0();
    void sub_208A00();
    void sub_208A50();
};
// The session settings' map (word_4F62F8) and game type (dword_42D294)
// the instant action searches with.
#ifdef CODFH_PLAIN
extern RwUInt16 &word_4F62F8;
#else
extern RwUInt16 word_4F62F8;
#endif
// A text emptied when the instant action's results are shown (its users
// are not matched yet).
extern type_1CB670 unk_4F7E9C;
extern RwInt32 dword_42D294;

// The system link's create session menu (in-game menu 8, off_3E8AA8 and
// off_3E8AA4): the create session page over
// "XboxSysLinkCreateSession.layout", starting the game as the host over
// the system link (slot 17) and giving the menu it came from (slot 18: 10
// or 9 for the pages 0 and 2).
struct type_2097E0 : type_2053C0
{
    type_2097E0();
    virtual ~type_2097E0();
    virtual void vf_044();
    virtual type_1FBDA0_menu *vf_048();
};

// The system link's menu (in-game menu 10, "XboxSysLink.layout", off_3E8B48,
// 0x1B8 bytes): the actions "FindSession" (unk_188: the in-game menu 9),
// "CreateSession" (unk_194: page 0, the in-game menu 8), "Back" (unk_1A0,
// over sub_20BE30: the in-game menu 13) and "Options" (unk_1AC: the
// options' mode 1, sub_20B920, then the in-game menu 5).
struct type_2098F0 : type_2049D0
{
    kujuUI::type_3E7CE8<type_2098F0> unk_188;
    kujuUI::type_3E7CE8<type_2098F0> unk_194;
    kujuUI::type_3E7CE8<type_2098F0> unk_1A0;
    kujuUI::type_3E7CE8<type_2098F0> unk_1AC;

    type_2098F0();
    virtual ~type_2098F0();
    void sub_209AD0();
    void sub_209B00();
    void sub_209B30();
    // Shared through /OPT:ICF with another menu's back to menu 13.
    void sub_20BE30();
};
// The options page's mode (dword_42D2A8, set by sub_20B920): set, its
// "Back" returns to the system link's menu 10, else to menu 6.
extern RwInt32 dword_42D2A8;
void sub_20B920(RwInt32 arg_0);

// In-game menu 11 (off_3E8C60, 0x18C bytes), a sign-in page with no layout
// of its own: its update (slot 5) asks the service started last
// (sub_227560) for step 2 once after being shown (unk_188) and takes
// itself off the pad's widget stack, to be asked again, while the
// service's state is not 2.
struct type_209D00 : type_2049D0
{
    RwInt32 unk_188;

    type_209D00();
    virtual ~type_209D00();
    virtual void vf_014(RwReal arg_0);
    // vf_018, as the image's vtable has it (a trivial body, folded into
    // sub_15FB30 with every other copy).
    virtual void vf_018(kujuUI::type_1E4130 *arg_0)
    {
    }
};

// The Live options ("LiveOptions.layout", off_3E8D00, 0x3A0 bytes; one,
// dword_504578, built by sub_20A540): "Back" (unk_188), "FriendsList"
// (unk_194, pushing unk_1C4), "PlayerList" (unk_1A0, empty: folded by
// /OPT:ICF into 0x1E41C0), "AppearOffline" (unk_1AC, toggling the
// service's unk_A0) and "SignOut" (unk_1B8, back to the in-game menu 13);
// the texts "FriendsFlagText" (unk_350, set by its update, slot 5) and
// "AppearStatus" (unk_378, set by sub_20A0E0).
struct type_209E00 : type_2049D0
{
    kujuUI::type_3E7CE8<type_209E00> unk_188;
    kujuUI::type_3E7CE8<type_209E00> unk_194;
    kujuUI::type_3E7CE8<type_209E00> unk_1A0;
    kujuUI::type_3E7CE8<type_209E00> unk_1AC;
    kujuUI::type_3E7CE8<type_209E00> unk_1B8;
    type_209D00 unk_1C4;
    kujuUI::type_1F28C0 unk_350;
    kujuUI::type_1F28C0 unk_378;

    type_209E00();
    virtual ~type_209E00();
    virtual void vf_014(RwReal arg_0);
    virtual void vf_018(kujuUI::type_1E4130 *arg_0);
    void sub_20A0E0();
    void sub_20A1B0();
    void sub_20A1D0();
    void sub_1E41C0();
    void sub_20A1F0();
    void sub_20A240();
};
extern type_209E00 *dword_504578;

// In-game menu 12 (off_3E8DC0, 0x18C bytes), a sign-in page with no layout
// of its own: its update (slot 5) asks the service started last for step 1
// once after being shown (unk_188) and, unless the network system's state
// is 1, opens the in-game menu 6 (state 4) or 13, to be asked again.
struct type_20A670 : type_2049D0
{
    RwInt32 unk_188;

    type_20A670();
    virtual ~type_20A670();
    virtual void vf_014(RwReal arg_0);
    // vf_018, as the image's vtable has it (a trivial body, folded into
    // sub_15FB30 with every other copy).
    virtual void vf_018(kujuUI::type_1E4130 *arg_0)
    {
    }
};

// In-game menu 4, a message ("Message.layout", off_3E8E28, 0x1C4 bytes;
// the one shown, dword_50457C): an "OK" action (unk_188, taking the page
// off the pad's widget stack and calling unk_1BC with unk_1C0 when set)
// and a "Message" text (unk_194).
struct type_20A7B0 : type_2049D0
{
    kujuUI::type_3E7CE8<type_20A7B0> unk_188;
    kujuUI::type_1F28C0 unk_194;
    void (*unk_1BC)(RwInt32 arg_0);
    RwInt32 unk_1C0;

    type_20A7B0();
    virtual ~type_20A7B0();
    void sub_20A940();
};
extern type_20A7B0 *dword_50457C;

struct type_4F45F8;
// In-game menu 13, the multiplayer menu ("MultiplayerMenu.layout",
// off_3E8EC0, 0x3E8 bytes): "Back" (unk_310, over sub_20AD30: back to the
// dashboard), "PlayOnline" (unk_31C: the in-game menu 12, or 6 while the
// voice runs), "PlayLANGame" (unk_32C: the system link's menu 10) and the
// text "PlayLive" (unk_3C0, set by its update, slot 5, which also shows the
// join failure page unk_188, "JoinFailed.layout", with its "Back"
// (unk_33C, over sub_20BE60), "Reason" (unk_348) and "FailHeader"
// (unk_370) texts). Slot 15 leaves for the dashboard's menu; slot 16 takes
// the join failure page off the pad's widget stack.
struct type_20AA10 : type_2049D0
{
    type_2049D0 unk_188;
    kujuUI::type_3E7CE8<type_20AA10> unk_310;
    kujuUI::type_3E7264<type_20AA10> unk_31C;
    kujuUI::type_3E7264<type_20AA10> unk_32C;
    kujuUI::type_3E7CE8<type_20AA10> unk_33C;
    kujuUI::type_1F28C0 unk_348;
    kujuUI::type_1F28C0 unk_370;
    kujuUI::type_1F28C0 unk_398;
    kujuUI::type_1F28C0 unk_3C0;

    type_20AA10();
    virtual ~type_20AA10();
    virtual void vf_014(RwReal arg_0);
    virtual void vf_03C();
    virtual void vf_040();
    void sub_20AD30();
    void sub_20AE90();
    void sub_20AF10();
    // Shared through /OPT:ICF with the host options' (always true).
    bool sub_2015D0();
    // The join failure's "Back": the same code as the Xbox Live menu's,
    // shared through /OPT:ICF.
    void sub_20BE60();
};
// The launch data handed to the dashboard (0x6A0 bytes), and its path
// ("d:\\default.xbe", in .data).
extern type_4F45F8 unk_504580;
extern RwChar aDDefaultXbe[];

// In-game menu 5, the options ("Options.layout", off_3E8FC0, 0x368 bytes):
// the front end's options page (its second base) with its widgets and
// selectors by name, "Back" (unk_340) and "Accept" (unk_350, writing the
// settings back first). It reads the settings when shown (slot 15) and
// follows the voice chat's speakers (unk_360) in its update (slot 5).
struct type_20B570 : type_2049D0, type_1FC320
{
    kujuUI::type_3E7CE8<type_20B570> unk_340;
    kujuUI::type_3E7CE8<type_20B570> unk_350;
    type_1FD490_value unk_360;
    RwInt32 unk_364;

    type_20B570();
    virtual ~type_20B570();
    virtual void vf_014(RwReal arg_0);
    virtual void vf_03C();
    void sub_20B8A0();
    void sub_20B8F0();
};

// In-game menu 6, the Xbox Live menu ("PlayOnline.layout", off_3E9050,
// 0x3DC bytes): "InstantAction" (unk_310: the in-game menu 2),
// "FindSession" (unk_31C: menu 1), "CreateSession" (unk_328: menu 0 with
// the page's mode 0), "XboxLiveOptions" (unk_334: the Live options),
// "Options" (unk_340: menu 5), "Back" (unk_34C: menu 13) and the text
// "PlayLive" (unk_3B4, set by its update, slot 5, which also shows the join
// failure page unk_188 with its "Back" (unk_358), "Reason" (unk_364) and
// "FailHeader" (unk_38C)). Slot 16 is the multiplayer menu's (0x20AFB0,
// the same code).
struct type_20B9D0 : type_2049D0
{
    type_2049D0 unk_188;
    kujuUI::type_3E7CE8<type_20B9D0> unk_310;
    kujuUI::type_3E7CE8<type_20B9D0> unk_31C;
    kujuUI::type_3E7CE8<type_20B9D0> unk_328;
    kujuUI::type_3E7CE8<type_20B9D0> unk_334;
    kujuUI::type_3E7CE8<type_20B9D0> unk_340;
    kujuUI::type_3E7CE8<type_20B9D0> unk_34C;
    kujuUI::type_3E7CE8<type_20B9D0> unk_358;
    kujuUI::type_1F28C0 unk_364;
    kujuUI::type_1F28C0 unk_38C;
    kujuUI::type_1F28C0 unk_3B4;

    type_20B9D0();
    virtual ~type_20B9D0();
    virtual void vf_014(RwReal arg_0);
    virtual void vf_040();
    void sub_20BD70();
    // "FindSession": the same code as the next menu's (0x20C390), shared
    // through /OPT:ICF.
    void sub_20C390();
    void sub_20BDA0();
    void sub_20BDD0();
    void sub_20BE00();
    void sub_20BE30();
    void sub_20BE60();
};
// The "PlayLive" text: "Signing in..." in state 1, else "Play on Xbox
// Live".
type_1A5EA0 sub_20B3A0();
// Whether the session is over the system link.
bool sub_20B410();

// The session list's columns (off_3E9298, 0x10 bytes): the list box's
// columns object over the found sessions' rows (type_1FB520), kept sorted:
// the selected row (sub_20E520), a row added in its place (sub_20E540, at
// sub_20E710's index: after every row it does not sort before) and a row
// by index (sub_21DF90). Its destructor is the compiler's (out of line at
// 0x21D8A0, its deleting form at 0x21DE30).
struct type_20E4F0 : kujuUI::type_1ECA30
{
    type_20E4F0(RwUInt32 arg_0);
    kujuUI::type_3E74C0 *sub_20E520();
    RwInt32 sub_20E540(type_1FB520 *arg_0);
    RwInt32 sub_20E710(type_1FB520 *arg_0);
    type_1FB520 *sub_21DF90(RwUInt32 arg_0);
};

// The session list page (off_3E91F8 and off_3E91DC, 0x8770 bytes), the base
// of the in-game menus 7 (Xbox Live) and 9 (system link): the search's
// description (unk_198: the player's name, unk_19C from slot 17, the map
// unk_1A2) and its results' buffer (unk_1A4), the columns (its second base,
// "SessionsActive"), the pages "NoSessionsFound" (unk_81A4, with "Create"
// and "Back"), "JoinFailed" (unk_832C, with "Back", "Reason" and
// "FailHeader") and "SearchingForGames" (unk_84B4, with "Back" and
// "Searching"), the join (unk_8640 over sub_20CFB0 while a row is
// selected), "Cancel"/"Back" (unk_8658), "Refresh" (unk_8698), "NextSort"
// (unk_86A8) with "SortText" (unk_8730), the rows made (unk_8758), whether
// the search runs (unk_8764), whether the join failed after joining
// (unk_8768) and unk_876C. Slots 17 to 22 are the menus': whether the
// search is over Xbox Live (vf_044), back (vf_048), create (vf_04C), the
// "NoSessionsFound" page's back (vf_050), and the join failure's back
// (vf_054, or vf_058 after joining).
struct type_20C470 : type_2049D0, type_20E4F0
{
    const RwChar *unk_198;
    bool unk_19C;
    RwUInt8 unk_19D;
    RwUInt8 unk_19E;
    RwUInt8 unk_19F;
    RwUInt8 unk_1A0;
    RwUInt8 unk_1A1;
    RwUInt16 unk_1A2;
    RwUInt8 unk_1A4[0x8000];
    type_2049D0 unk_81A4;
    type_2049D0 unk_832C;
    type_2049D0 unk_84B4;
    kujuUI::type_3E7264<type_20C470> unk_8640;
    kujuUI::type_3E7CE8<type_20C470> unk_8658;
    kujuUI::type_3E7CE8<type_20C470> unk_8668;
    kujuUI::type_3E7CE8<type_20C470> unk_8678;
    kujuUI::type_3E7CE8<type_20C470> unk_8688;
    kujuUI::type_3E7CE8<type_20C470> unk_8698;
    kujuUI::type_3E7CE8<type_20C470> unk_86A8;
    kujuUI::type_1F28C0 unk_86B8;
    kujuUI::type_1F28C0 unk_86E0;
    kujuUI::type_1F28C0 unk_8708;
    kujuUI::type_1F28C0 unk_8730;
    std::list<type_1FB520 *> unk_8758;
    RwInt32 unk_8764;
    bool unk_8768;
    RwInt32 unk_876C;

    type_20C470(const RwChar *arg_0, bool arg_4);
    virtual ~type_20C470();
    virtual void vf_014(RwReal arg_0);
    virtual void vf_038();
    virtual void vf_03C();
    virtual void vf_040();
    virtual bool vf_044() = 0;
    virtual void vf_048() = 0;
    virtual void vf_04C() = 0;
    virtual void vf_050() = 0;
    virtual void vf_054() = 0;
    virtual void vf_058() = 0;
    virtual void pvf_010();
    virtual void pvf_014();
    void sub_20CA70();
    void sub_20CB20();
    void sub_20CB70();
    // Empty, folded (/OPT:ICF) into pDtor (0x1E41C0): the search's start calls it last.
    void sub_1E41C0();
    void sub_20CF20();
    void sub_20CF70();
    void sub_20CFB0();
    bool sub_20D420();
    void sub_20D440();
    void sub_20D470();
    void sub_20D8D0();
    // The rows' index for a session named arg_0 at the address arg_1C and
    // port arg_20: the row already listing it, else where the name sorts.
    RwInt32 sub_20DC80(type_1A5EA0 arg_0, const RwUInt8 *arg_1C, RwUInt16 arg_20);
    void sub_20DE80();
    void sub_20E060();
};

// In-game menu 7, the Xbox Live session list ("SessionList.layout",
// off_3E9100 and off_3E90E4): over Xbox Live (slot 17, folded into
// 0x2015D0), back to the in-game menu 1, create with menu 0 (the page's mode
// 2), refresh after a join failure, or after joining its session's error
// set (setError: 7, 10) once its unk_B0 is stopped. Slot 20 is empty
// (folded into 0x1E41C0).
struct type_20C2F0 : type_20C470
{
    type_20C2F0();
    virtual ~type_20C2F0();
    virtual bool vf_044();
    virtual void vf_048();
    virtual void vf_04C();
    virtual void vf_050();
    virtual void vf_054();
    virtual void vf_058();
};

// In-game menu 9, the system link's session list
// ("XboxSysLinkSessionList.layout", off_3E8BD8 and off_3E8BBC): not over
// Xbox Live (slot 17, folded into 0x1E4AA0), back to the in-game menu 10,
// create with menu 8 (the page's mode 2), refresh after a join failure (the
// Xbox Live list's, 0x20C3F0). Slots 20 and 22 are empty (folded into
// 0x1E41C0).
struct type_209BF0 : type_20C470
{
    type_209BF0();
    virtual ~type_209BF0();
    virtual bool vf_044();
    virtual void vf_048();
    virtual void vf_04C();
    virtual void vf_050();
    virtual void vf_054();
    virtual void vf_058();
};

#endif
