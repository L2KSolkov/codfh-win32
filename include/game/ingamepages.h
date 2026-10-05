/*
 * The screens shown over the game (game/ingamescreens.h builds them): each
 * an in-game menu (a top layout page) of its own class, not yet matched;
 * only their sizes, their constructors' arguments and the members called
 * are known.
 */
#ifndef GAME_INGAMEPAGES_H
#define GAME_INGAMEPAGES_H

#include "game/ingamemenu.h"
#include "game/livemenu.h"
#include "game/options.h"
#include "game/hostoptions.h"
#include "game/frontend.h"

struct type_21A5E0;
// The in-game pages' base (off_3EA348, 0x154 bytes; over the Live menus'
// base): the pause menu it belongs to (unk_130) and the entry it goes back
// to there (unk_134, -1 at first), a "Back" (unk_138, over slot 16: the
// pause menu's entry unk_134) and an "Options" (unk_144, over slot 17: the
// pause menu's options, entry 0x16), and whether it is shown (unk_150,
// slot 18; set by slot 2 with byte_4B8974, cleared by slot 3). Slots 15
// and 19 are empty (folded into 0x1E41C0); its kind (slot 9, 0x1A) is an
// inline whose copy sits with the game type vote (0x215B70).
struct type_21CB10 : type_20E850
{
    type_21A5E0 *unk_130;
    RwInt32 unk_134;
    kujuUI::type_3E7CE8<type_21CB10> unk_138;
    kujuUI::type_3E7CE8<type_21CB10> unk_144;
    bool unk_150;

    type_21CB10(const RwChar *arg_0, type_21A5E0 *arg_4, kujuUI::type_1EFCF0<kujuUI::type_3E7D08 *> *arg_8);
    virtual ~type_21CB10();
    virtual void vf_008();
    virtual void vf_00C();
    virtual RwInt32 vf_024()
    {
        return 0x1A;
    }
    virtual void vf_03C();
    virtual void vf_040();
    virtual void vf_044();
    virtual bool vf_048();
    virtual void vf_04C();
    // Whether it belongs to a pause menu: an inline with no address, named
    // for what it gives. Evidence: the cancel warnings' show (sub_2155A0)
    // tests the screen shown through xor, setne and a test.
    bool in_pause_menu()
    {
        return unk_130 != 0;
    }
};
// Set while an in-game page is shown (cleared when one is left outside a
// network game).
extern RwUInt8 byte_4B8974;

// The pause menu (off_3EA018, 0x3E4 bytes; the one instance, dword_5051D8,
// is given by sub_21A5E0): an in-game page over the layout arg_0 (built by
// the in-game screens with "PauseMenu.layout") with its entries' pages
// (unk_158, built by sub_21ADB0: 0 the menu itself, 1 unk_15C, 2 the team
// selection, 3 the defect, 4 the host's options, 5 to 7 the vote's current
// players, maps and game types, 8 to 0xC the vote's pages, 0xD the game
// settings, 0xE the quit, 0xF the next round, 0x10 the online settings,
// 0x11 the kick page, 0x12 unk_1A0, 0x13 "PleaseInsertController", 0x14 the
// debug menu, 0x15 the Live options, 0x16 and 0x17 the sign-in pages), the
// one shown (unk_154, -1 at first; sub_21AC10 moves it, taking the old off
// the pad's widget stack and pushing the new, and sub_21C200 moves it with
// the page to go back to), its entries' actions ("resume" unk_1B8: the game
// resumed, sub_21C360; "live", "weapons", "team", "host", "vote",
// "settings", "quit", "debug" and "kill", unk_1C4 to unk_230; unk_240 the
// player killed and back; unk_24C doing nothing), the map's image library
// and look (unk_258, unk_25C; cleared by sub_21C740), its texts ("map"
// unk_260, "votetext", "mapname", "gametype", "gametypeinfo" and
// "XboxLiveOptions", unk_268 to unk_308), the shell's hooks while it is up
// (unk_330, dword_504378), and whether a vote was called and is to be
// confirmed (unk_3E0, unk_3E1).
// The maps' image suffixes by the game type's kind ("_death", "_destroy",
// "_ctf", "score"): the pause menu's loading (sub_21BD60) appends one to
// "gui_map" and the map's number.
extern const RwChar *off_42D2AC[];

struct type_21A5E0 : type_21CB10
{
    RwInt32 unk_154;
    type_21CB10 *unk_158[0x18];

    // The page shown (0 when none, unk_154 == 0x18) into arg_0: an inline
    // with no address, named for what it gives. Evidence: the legend update
    // (sub_1FFE80) writes each branch's value straight into its local after
    // a `this` slot.
    void get_shown(kujuUI::type_3E7D08 *&arg_0)
    {
        if (unk_154 != 0x18)
            arg_0 = unk_158[unk_154];
        else
            arg_0 = 0;
    }
    kujuUI::type_3E7CE8<type_21A5E0> unk_1B8;
    kujuUI::type_3E7CE8<type_21A5E0> unk_1C4;
    kujuUI::type_3E7CE8<type_21A5E0> unk_1D0;
    kujuUI::type_3E7264<type_21A5E0> unk_1DC;
    kujuUI::type_3E7264<type_21A5E0> unk_1EC;
    kujuUI::type_3E7264<type_21A5E0> unk_1FC;
    kujuUI::type_3E7CE8<type_21A5E0> unk_20C;
    kujuUI::type_3E7CE8<type_21A5E0> unk_218;
    kujuUI::type_3E7CE8<type_21A5E0> unk_224;
    kujuUI::type_3E7264<type_21A5E0> unk_230;
    kujuUI::type_3E7CE8<type_21A5E0> unk_240;
    kujuUI::type_3E7CE8<type_21A5E0> unk_24C;
    type_E8780<kujuUI::type_1ECCE0> unk_258;
    kujuUI::type_1E3BA0 *unk_25C;
    kujuUI::type_1E7490 unk_260;
    kujuUI::type_1F28C0 unk_268;
    kujuUI::type_1F28C0 unk_290;
    kujuUI::type_1F28C0 unk_2B8;
    kujuUI::type_1F28C0 unk_2E0;
    kujuUI::type_1F28C0 unk_308;
    type_3E83E4 unk_330;
    bool unk_3E0;
    bool unk_3E1;

    type_21A5E0(const RwChar *arg_0);
    virtual ~type_21A5E0();
    virtual kujuUI::eEventWasHandled processEvent(const kujuUI::cStateChange &arg_0);
    virtual void vf_008();
    virtual void vf_00C();
    virtual void vf_014(RwReal arg_0);
    virtual void vf_018(kujuUI::type_1E4130 *arg_0);
    virtual void vf_03C();
    virtual void vf_040();
    RwInt32 sub_21ABF0();
    bool sub_21AC10(RwInt32 arg_0);
    bool sub_21ADB0();
    void sub_21B8F0();
    void sub_21C200(RwInt32 arg_0, RwInt32 arg_4);
    // A vote answered: yes or no.
    void sub_21C250(bool arg_0);
    // The next round asked answered: yes (1) or no (0), which it ignores,
    // resetting the menu.
    void sub_21C280(RwInt32 arg_0);
    // The quit asked answered: yes or no.
    void sub_21C2A0(bool arg_0);
    // The defect asked answered: yes or no.
    void sub_21C2D0(bool arg_0);
    void sub_21C360();
    void sub_21C380();
    void sub_21C3A0();
    void sub_21C3C0();
    void sub_21C3E0();
    bool sub_21C400();
    bool sub_21C410();
    void sub_21C430();
    void sub_21C4C0();
    bool sub_21C620();
    void sub_21C670();
    bool sub_21C6A0();
    void sub_21C6E0();
    void sub_21C700();
    void sub_21C720();
    void sub_21C740();
    // Empty: shared through /OPT:ICF.
    void sub_1E41C0();
};
extern type_21A5E0 *dword_5051D8;
type_21A5E0 *sub_21A5E0();


struct type_2207A0;

struct type_223280;
// A vote over the game (off_3E96F8, 0x194 bytes; the pause menu builds
// them): its question ("VoteText", unk_16C, set from slot 22 when shown,
// slot 2) and "yes" and "no" (unk_154, unk_160, over slots 20 and 21: the
// pause menu's vote answered).
struct type_216130 : type_21CB10
{
    kujuUI::type_3E7CE8<type_216130> unk_154;
    kujuUI::type_3E7CE8<type_216130> unk_160;
    kujuUI::type_1F28C0 unk_16C;

    type_216130(const RwChar *arg_0, type_21A5E0 *arg_4);
    virtual ~type_216130();
    virtual void vf_008();
    virtual void vf_050();
    virtual void vf_054();
    virtual type_1CB670 vf_058() = 0;
};
// The votes on the game type, the next map and a player's kick (off_3E9588,
// off_3E9600 and off_3E9678): their questions (slot 22) name what is voted.
struct type_215B40 : type_216130
{
    type_215B40(const RwChar *arg_0, type_21A5E0 *arg_4);
    virtual ~type_215B40();
    virtual type_1CB670 vf_058();
};
struct type_215D40 : type_216130
{
    type_215D40(const RwChar *arg_0, type_21A5E0 *arg_4);
    virtual ~type_215D40();
    virtual type_1CB670 vf_058();
};
struct type_215F30 : type_216130
{
    type_215F30(const RwChar *arg_0, type_21A5E0 *arg_4);
    virtual ~type_215F30();
    virtual type_1CB670 vf_058();
};

// The debug menu ("DebugMenu.layout", off_3E9790, 0x184 bytes): "kill"
// (unk_154, the player killed; shared through /OPT:ICF at 0x217120),
// "reset" (unk_160), "round" and "round5" (unk_16C, unk_178: 30 and 5
// seconds added to the round), each back to the game after.
struct type_216440 : type_21CB10
{
    kujuUI::type_3E7CE8<type_216440> unk_154;
    kujuUI::type_3E7CE8<type_216440> unk_160;
    kujuUI::type_3E7CE8<type_216440> unk_16C;
    kujuUI::type_3E7CE8<type_216440> unk_178;

    type_216440(const RwChar *arg_0, type_21A5E0 *arg_4);
    virtual ~type_216440();
    void sub_217120();
    void sub_216620();
    void sub_216650();
    void sub_216690();
};

// The defect asked ("Defect.layout", off_3E97F0, 0x16C bytes): "yes" and
// "no" (unk_154, unk_160) answered to the pause menu.
struct type_216760 : type_21CB10
{
    kujuUI::type_3E7CE8<type_216760> unk_154;
    kujuUI::type_3E7CE8<type_216760> unk_160;

    type_216760(const RwChar *arg_0, type_21A5E0 *arg_4);
    virtual ~type_216760();
    void sub_2168C0();
    void sub_2168E0();
};

// The error screens ("ErrorScreen.layout" and "JoinError.layout", off_3E98C8,
// 0x188 bytes): the message ("Reason", unk_154, set by sub_216C10 from the
// text arg_0) and "continue" (unk_17C, shared through /OPT:ICF at
// 0x220A80).
struct type_216C10 : type_21CB10
{
    kujuUI::type_1F28C0 unk_154;
    kujuUI::type_3E7CE8<type_216C10> unk_17C;

    type_216C10(const RwChar *arg_0, type_21A5E0 *arg_4);
    virtual ~type_216C10();
    void sub_216C10(const RwChar *arg_0);
    void sub_220A80();
    // vf_040, as the image's vtable has it (a trivial body, folded into
    // sub_1E41C0 with every other copy).
    virtual void vf_040()
    {
    }
    // vf_024, as the image's vtable has it (a trivial body, folded into
    // sub_195D00 with every other copy).
    virtual RwInt32 vf_024()
    {
        return 2;
    }
};

// The game settings ("GameSettings.layout", off_3E9938, 0x358 bytes): the
// front end's options page (its second base) with its widgets and
// selectors by name, "Accept" (unk_310: the settings written back, then
// back to the game), "kill" (unk_320: the player killed, then back to the
// game), and two unnamed actions its selectors check (unk_330, unk_340,
// empty). It reads the settings when shown (slot 2) and follows the voice
// chat's speakers (unk_350) in its update (slot 5); its kind (slot 9) is
// 0x3A, folded (/OPT:ICF) into 0x222540.
struct type_216D20 : type_21CB10, type_1FC320
{
    RwInt32 unk_30C;
    kujuUI::type_3E7CE8<type_216D20> unk_310;
    kujuUI::type_3E7CE8<type_216D20> unk_320;
    kujuUI::type_3E7CE8<type_216D20> unk_330;
    kujuUI::type_3E7CE8<type_216D20> unk_340;
    type_1FD490_value unk_350;
    RwInt32 unk_354;

    type_216D20(const RwChar *arg_0, type_21A5E0 *arg_4);
    virtual ~type_216D20();
    virtual void vf_008();
    virtual void vf_014(RwReal arg_0);
    virtual RwInt32 vf_024();
    void sub_2170F0();
    void sub_217120();
    // Empty, and one calling it: shared through /OPT:ICF.
    void sub_1E41C0();
    void sub_39440();
};

// The two-prompt dialog (off_3E9A0C, 0x20C bytes; the one instance,
// dword_5051D4, over "GenericTwoPromptIngameScreen.layout" (sub_2172F0) or
// "GenericTwoPromptScreen.layout" (sub_2173A0), deleted by sub_217450):
// the texts "Title" (unk_160, when the page has no title of its own),
// "Prompt" (unk_188), "Option1Text" and "Option2Text" (unk_1B0, unk_1D8),
// and "Option1", "Option2" and "Back" (unk_130 to unk_150), each taking the
// dialog off the pad's widget stack and running the caller's action
// (unk_200 to unk_208) when it allows it. sub_2171F0 shows it, sub_2172A0
// hides it; its buttons (slot 9) are 2, with 8 for "Back" and 0x10 for
// both options.
struct type_217670 : type_20E850
{
    kujuUI::type_3E7264<type_217670> unk_130;
    kujuUI::type_3E7264<type_217670> unk_140;
    kujuUI::type_3E7264<type_217670> unk_150;
    kujuUI::type_1F28C0 unk_160;
    kujuUI::type_1F28C0 unk_188;
    kujuUI::type_1F28C0 unk_1B0;
    kujuUI::type_1F28C0 unk_1D8;
    kujuUI::type_1ED670_object *unk_200;
    kujuUI::type_1ED670_object *unk_204;
    kujuUI::type_1ED670_object *unk_208;

    type_217670(const RwChar *arg_0);
    virtual ~type_217670();
    virtual RwInt32 vf_024();
    void sub_217490();
    bool sub_2174D0();
    void sub_217500();
    bool sub_217540();
    void sub_217570();
    bool sub_2175C0();
};
extern type_217670 *dword_5051D4;
void sub_2171F0(const type_1A5EA0 &arg_0, const type_1A5EA0 &arg_4, const type_1A5EA0 &arg_8,
                kujuUI::type_1ED670_object *arg_C, const type_1A5EA0 &arg_10, kujuUI::type_1ED670_object *arg_14,
                kujuUI::type_1ED670_object *arg_18);
bool sub_2172A0();
void sub_2172F0();
void sub_2173A0();
void sub_217450();

// The host's options ("HostOptions.layout", off_3E9A78, 0x170 bytes):
// "settings" (unk_154: the pause menu's entry 0x10) and "kick" (unk_160:
// entry 0x11, while there is more than one player), each back to entry 4.
struct type_2179E0 : type_21CB10
{
    kujuUI::type_3E7CE8<type_2179E0> unk_154;
    kujuUI::type_3E7264<type_2179E0> unk_160;

    type_2179E0(const RwChar *arg_0, type_21A5E0 *arg_4);
    virtual ~type_2179E0();
    void sub_217B40();
    void sub_217B60();
    bool sub_217B80();
};

// The host options' advanced page (off_3E9F28, 0x188 bytes): a Live login
// page over its layout. Its destructor is the compiler's (the host options
// pages' destructor expands it; its unwinding calls the copy at 0x219FC0).
struct type_219F60 : type_2049D0
{
    type_219F60(const RwChar *arg_0, kujuUI::type_1EFCF0<kujuUI::type_3E7D08 *> *arg_4, bool arg_8);
    // vf_024, as the image's vtable has it (the same `return 0x3A` as
    // type_222350's, folded into sub_222540).
    virtual RwInt32 vf_024()
    {
        return 0x3A;
    }
};

// The host options pages' base (off_3E9F78 and off_3E9F74, 0x6C0 bytes): an
// in-game page over the layout arg_0 and the host's options (its second
// base, built with arg_C) with their widgets by name, "Save" (unk_4F8: the
// options written and sent, then back), "OpenAdvanced" and
// "CancelAdvanced" (unk_508, unk_518: the options kept or restored and the
// advanced page, unk_538 over the layout arg_4, pushed or taken off the
// pad's widget stack) and "CloseAdvanced" (unk_528). It reads the options
// when shown (slot 2) and leaves the advanced page when left (slot 3); its
// update (slot 5, folded into 0x223810) is the Live menus' and its kind
// (slot 9) 0x3A (folded into 0x222540).
struct type_219FE0 : type_21CB10, type_200B90
{
    RwUInt8 unk_4F4[4];
    kujuUI::type_3E7CE8<type_219FE0> unk_4F8;
    kujuUI::type_3E7CE8<type_219FE0> unk_508;
    kujuUI::type_3E7CE8<type_219FE0> unk_518;
    kujuUI::type_3E7CE8<type_219FE0> unk_528;
    type_219F60 unk_538;

    type_219FE0(const RwChar *arg_0, const RwChar *arg_4, type_21A5E0 *arg_8, bool arg_C);
    virtual ~type_219FE0();
    virtual void vf_008();
    virtual void vf_00C();
    virtual void vf_014(RwReal arg_0);
    virtual RwInt32 vf_024();
    void sub_21A460();
    void sub_21A490();
    void sub_21A4C0();
    void sub_21A4F0();
};

// The end of round host settings ("EndRoundHostSettings.layout" with
// "OnlineSettingsAdvanced.layout", off_3E9860 and off_3E985C, 0x6C8
// bytes): the host options pages' base with no pause menu; "Back" (slot
// 16) tells the widget it was opened from (unk_6C0, slot 7 with 1, 0),
// and its kind (slot 9) is 0x3A with one, else 0x32.
struct type_216990 : type_219FE0
{
    kujuUI::type_3E7D08 *unk_6C0;
    RwInt32 unk_6C4;

    type_216990(const RwChar *arg_0, const RwChar *arg_4, kujuUI::type_3E7D08 *arg_8);
    virtual ~type_216990();
    virtual RwInt32 vf_024();
    virtual void vf_040();
};

// The online settings ("OnlineSettings.layout" with
// "OnlineSettingsAdvanced.layout", off_3E9B00 and off_3E9AFC, 0x6D0 bytes):
// the host options pages' base over the pause menu with "SaveNow" (unk_6C0:
// the options written and sent, and the pause menu left); it also updates
// the time limit when shown (slot 2).
struct type_217CD0 : type_219FE0
{
    kujuUI::type_3E7CE8<type_217CD0> unk_6C0;

    type_217CD0(const RwChar *arg_0, const RwChar *arg_4, type_21A5E0 *arg_8);
    virtual ~type_217CD0();
    virtual void vf_008();
    void sub_217E60();
};

// The team selection's base (off_3EA798, 0x1C4 bytes): "team1" and "team2"
// (unk_154, unk_160: the team joined, then back into the game, or over the
// pause menu to its entry 3 when it changed), "team1focus" and
// "team2focus" (unk_178, unk_184: the team's flag shown on "flag",
// unk_190), the teams' widgets by name (unk_1B0: unk_1BC, the one focused
// when shown, slot 2, by the team the player is in), and the flags'
// libraries and looks (unk_198, unk_1A4; loaded when loaded, slot 15, and
// freed by sub_221430). The team shown (unk_16C) and picked (unk_170, the
// one before in unk_174). Its kind (slot 9) is 0x1A over a pause menu,
// else 0x12.
struct type_220C40 : type_21CB10
{
    kujuUI::type_3E7CE8<type_220C40> unk_154;
    kujuUI::type_3E7CE8<type_220C40> unk_160;
    RwInt32 unk_16C;
    RwInt32 unk_170;
    RwInt32 unk_174;
    kujuUI::type_3E7CE8<type_220C40> unk_178;
    kujuUI::type_3E7CE8<type_220C40> unk_184;
    kujuUI::type_1E7490 unk_190;
    type_E8780<kujuUI::type_1ECCE0> unk_198[3];
    kujuUI::type_1E3BA0 *unk_1A4[3];
    kujuUI::type_1EFCF0<kujuUI::type_3E7D08 *> unk_1B0;
    kujuUI::type_3E7D08 *unk_1BC[3];

    type_220C40(const RwChar *arg_0, type_21A5E0 *arg_4);
    virtual ~type_220C40();
    virtual void vf_008();
    virtual RwInt32 vf_024();
    virtual void vf_03C();
    void sub_220FE0();
    void sub_221050();
    void sub_2210C0();
    void sub_2210E0();
    bool sub_221100(RwInt32 arg_0);
    bool sub_221140(RwInt32 arg_0);
    void sub_221430();
};
// The weapons' libraries by team ("w_weaponsGB" to "w_weaponsDE").
extern const RwChar *off_42D2E8[];

// The initial team selection ("InitialTeamSelect.layout", off_3E9B98, 0x1E4
// bytes): the team selection's base with "auto" (unk_1CC: the game picks
// the team) and "autofocus" (unk_1D8: its flag shown), and the "auto"
// widget by name (the base's third, unk_1BC[2]).
struct type_217F40 : type_220C40
{
    RwInt32 unk_1C8;
    kujuUI::type_3E7CE8<type_217F40> unk_1CC;
    kujuUI::type_3E7CE8<type_217F40> unk_1D8;

    type_217F40(const RwChar *arg_0, type_21A5E0 *arg_4);
    virtual ~type_217F40();
    void sub_218110();
    void sub_218130();
};

// A row of the kick list (off_3EA3A8, 0x60 bytes): a player's index
// (unk_40, sub_21D030) and name (unk_44, sub_21D050), ordered by name
// (sub_21D0A0).
struct type_21CE60 : kujuUI::type_3E74C0
{
    RwInt32 unk_40;
    type_1A5EA0 unk_44;

    type_21CE60(RwInt32 arg_0, type_1A5EA0 arg_4);
    virtual ~type_21CE60();
    virtual void vf_004();
    RwInt32 sub_21D030();
    type_1A5EA0 sub_21D050();
    bool sub_21D0A0(const type_21CE60 &arg_0);
};

// The quit asked (off_3EA3C0, 0x194 bytes): "yes" and "no" (unk_154,
// unk_160) and the question ("Prompt", unk_16C: "QUIT_GAME_HOST" or
// "QUIT_GAME?", set when shown, slot 2).
struct type_21D0D0 : type_21CB10
{
    kujuUI::type_3E7CE8<type_21D0D0> unk_154;
    kujuUI::type_3E7CE8<type_21D0D0> unk_160;
    kujuUI::type_1F28C0 unk_16C;

    type_21D0D0(const RwChar *arg_0, type_21A5E0 *arg_4);
    virtual ~type_21D0D0();
    virtual void vf_008();
    void sub_21D340();
    void sub_21D390();
};

// The kick list's columns (off_3E9CA0, 0x10 bytes): a list box's columns
// object over the kick list's rows, kept sorted (sub_218BB0 adds a row at
// sub_218C90's index); the selected row and a row by index are shared
// through /OPT:ICF with the session list's (0x20E520, 0x21DF90). Its
// destructor is the compiler's (out of line at 0x21D8A0).
struct type_218B80 : kujuUI::type_1ECA30
{
    type_218B80(RwUInt32 arg_0);
    type_21CE60 *sub_20E520();
    RwInt32 sub_218BB0(type_21CE60 *arg_0);
    RwInt32 sub_218C90(type_21CE60 *arg_0);
    type_21CE60 *sub_21DF90(RwUInt32 arg_0);
};

// A row of a scoreboard's players (off_3EA420, 0x6C bytes): the player's
// index (unk_40; the local player's row is selected), name (unk_44,
// sub_21D700) and the two counts it is ordered by, highest first (unk_60,
// sub_21D740, then unk_64, sub_21D720; sub_21D760), and unk_68; its texts
// (slot 1, sub_21D5A0) are built in type_1CB670 locals.
struct type_21D470 : kujuUI::type_3E74C0
{
    RwInt32 unk_40;
    type_1A5EA0 unk_44;
    RwInt32 unk_60;
    RwInt32 unk_64;
    RwInt32 unk_68;

    type_21D470(RwInt32 arg_0, const type_1A5EA0 &arg_4, RwInt32 arg_8, RwInt32 arg_C, RwInt32 arg_10);
    virtual ~type_21D470();
    virtual void vf_004();
    const type_1A5EA0 *sub_21D700() const;
    RwInt32 sub_21D720() const;
    RwInt32 sub_21D740() const;
    bool sub_21D760(const type_21D470 &arg_0);
};

// A scoreboard's players' columns' base (off_3EA450, 0x10 bytes): a list
// box's columns object over the rows kept sorted (sub_21DDF0 adds a row at
// sub_21DE60's index) and a row by index (sub_21DF90, shared through
// /OPT:ICF with the session list's and the kick list's). Its destructor is
// the compiler's (out of line at 0x21D8A0, shared the same way).
struct type_21DDC0 : kujuUI::type_1ECA30
{
    type_21DDC0(RwUInt32 arg_0);
    RwInt32 sub_21DDF0(type_21D470 *arg_0);
    RwInt32 sub_21DE60(type_21D470 *arg_0);
    type_21D470 *sub_21DF90(RwUInt32 arg_0);
};

// A scoreboard's players (off_3EA434, 0x1C bytes; the scoreboard, sub_21EB30,
// makes two): three columns (0xB4, 0x1E and 0x1C wide) and the rows
// (unk_10), deleted by sub_21D950 and added by sub_21D9F0 (selected when
// they are the local player's).
struct type_21D7C0 : type_21DDC0
{
    std::list<type_21D470 *> unk_10;

    type_21D7C0();
    virtual ~type_21D7C0();
    void sub_21D950();
    RwInt32 sub_21D9F0(RwInt32 arg_0, const type_1A5EA0 &arg_4, RwInt32 arg_8, RwInt32 arg_C, RwInt32 arg_10);
};

// A scoreboard's options (off_3EA4A8, 0x204 bytes; the scoreboard builds one
// over its options' layout): of the scoreboard's kind (unk_154: 1 at a
// round's end, 2 at the game's end), with the host's "settings" (unk_158:
// the end of round host settings, unk_1F8, pushed on the pad's widget
// stack and shown), "Level" (unk_1B0, the level selector; a level picked,
// unk_174, is set and restarts the countdown) and "countdown" (unk_1D0:
// the time left, unk_1FC, shown by sub_21E3E0 and restarted by sub_21E3B0;
// the front end leaves when it runs out, sub_21E520), a client's "quit"
// (unk_180: confirmed through the two-prompt dialog, unk_198 leaving the
// game, sub_1C44A0, and unk_1A4 doing nothing) and "wait" (unk_18C, doing
// nothing), and "continue" (unk_164: the front end's screens left, while
// unk_200 allows). Its kind (slot 9) is 0x32 with the host settings, 0x12
// for a client, 2 for the host and 0 while it may not continue. The
// countdown's text (sub_21E3E0) and "quit" (sub_21E880) unwind strings
// through the library's out-of-line string destructor (sub_43900) and are
// not matched (docs/questions.md).
struct type_21DFE0 : type_21CB10
{
    RwInt32 unk_154;
    kujuUI::type_3E7CE8<type_21DFE0> unk_158;
    kujuUI::type_3E7264<type_21DFE0> unk_164;
    kujuUI::type_3E7CE8<type_21DFE0> unk_174;
    kujuUI::type_3E7CE8<type_21DFE0> unk_180;
    kujuUI::type_3E7CE8<type_21DFE0> unk_18C;
    kujuUI::type_3E7CE8<type_21DFE0> unk_198;
    kujuUI::type_3E7CE8<type_21DFE0> unk_1A4;
    type_211680 unk_1B0;
    kujuUI::type_1F28C0 unk_1D0;
    type_216990 *unk_1F8;
    RwReal unk_1FC;
    bool unk_200;

    type_21DFE0(RwInt32 arg_0, const RwChar *arg_4, type_21A5E0 *arg_8);
    virtual ~type_21DFE0();
    virtual void vf_008();
    virtual void vf_00C();
    virtual void vf_014(RwReal arg_0);
    virtual bool vf_01C(RwInt32 arg_0, RwInt32 arg_4);
    virtual RwInt32 vf_024();
    virtual void vf_038();
    virtual void vf_04C();
    void sub_21E3B0();
    void sub_21E3E0();
    void sub_21E4D0();
    void sub_21E520();
    void sub_21E530();
    bool sub_21E780();
    void sub_21E880();
    void sub_21E9A0();
    // Empty, and the front end's screens left: shared through /OPT:ICF.
    void sub_1E41C0();
    void sub_220A80();
    // vf_040, as the image's vtable has it (a trivial body, folded into
    // sub_1E41C0 with every other copy).
    virtual void vf_040()
    {
    }
};

// A player's place in the scoreboard's ranking (type_21EB30::sub_21F1C0):
// its index, score and deaths. Only the widths are known.
struct type_21F1C0_entry
{
    RwInt32 unk_00;
    RwInt32 unk_04;
    RwInt32 unk_08;
};

// The scoreboards' base (off_3EA5F8, 0x3A8 bytes): an in-game page over its
// layout, of the kind unk_154 (0 during the game, 1 at a round's end, 2 at
// the game's end), by teams or not (unk_39C), with "continue" (unk_158),
// the players' names ("leftnames" and "rightnames", unk_1D4 and unk_1F0),
// the teams' flags ("leftflag" and "rightflag", unk_164 and unk_16C, their
// libraries and looks unk_174 and unk_17C, loaded by sub_2203E0 and
// dropped by sub_220680), the teams' names ("leftteamname" and
// "rightteamname", unk_184 and unk_1AC), unk_20C and unk_234, the round
// totals and scores ("leftroundtotal", "rightroundtotal", "leftroundscore"
// and "rightroundscore", unk_25C to unk_2D4), "headertext", "centretext",
// "abovecentretext" and "bestplayertext" (unk_2FC to unk_374), which side
// is shown (unk_39D, swapped by the pad's button 0x19 while shown) and the
// players last shown (unk_39E), with unk_3A0 and unk_3A4. Its texts
// (sub_21F1C0) and showing (slot 2, sub_21FB60) are not matched.
struct type_21EB30 : type_21CB10
{
    RwInt32 unk_154;
    kujuUI::type_3E7CE8<type_21EB30> unk_158;
    kujuUI::type_1E7490 unk_164;
    kujuUI::type_1E7490 unk_16C;
    type_E8780<kujuUI::type_1ECCE0> unk_174[2];
    kujuUI::type_1E3BA0 *unk_17C[2];
    kujuUI::type_1F28C0 unk_184;
    kujuUI::type_1F28C0 unk_1AC;
    type_21D7C0 unk_1D4;
    type_21D7C0 unk_1F0;
    kujuUI::type_1F28C0 unk_20C;
    kujuUI::type_1F28C0 unk_234;
    kujuUI::type_1F28C0 unk_25C;
    kujuUI::type_1F28C0 unk_284;
    kujuUI::type_1F28C0 unk_2AC;
    kujuUI::type_1F28C0 unk_2D4;
    kujuUI::type_1F28C0 unk_2FC;
    kujuUI::type_1F28C0 unk_324;
    kujuUI::type_1F28C0 unk_34C;
    kujuUI::type_1F28C0 unk_374;
    bool unk_39C;
    bool unk_39D;
    type_1DDE20_mask unk_39E;
    RwInt32 unk_3A0;
    RwInt32 unk_3A4;

    type_21EB30(bool arg_0, RwInt32 arg_4, const RwChar *arg_8, type_21A5E0 *arg_C);
    virtual ~type_21EB30();
    virtual void vf_008();
    virtual void vf_00C();
    virtual void vf_014(RwReal arg_0);
    void sub_21F1C0();
    void sub_2203E0();
    void sub_220680();
    void sub_220A80();
    // Whether it is by teams: an inline accessor with no address, named for
    // its field. Evidence: the flags' loading (sub_2203E0) and the
    // constructor test it through a byte slot of its own.
    bool get_unk_39C()
    {
        return unk_39C;
    }
    // vf_040, as the image's vtable has it (a trivial body, folded into
    // sub_1E41C0 with every other copy).
    virtual void vf_040()
    {
    }
    // vf_024, as the image's vtable has it (a trivial body, folded into
    // sub_1E4CB0 with every other copy).
    virtual RwInt32 vf_024()
    {
        return 0;
    }
};
// The flags' libraries by country (off_42D2C4: GB, US, RU and DE), the
// flags' looks' state names ("score", off_42D2B8) and their states
// (dword_5051DC).
extern const RwChar *off_42D2C4[];
extern const RwChar *off_42D2B8[];
extern RwInt32 dword_5051DC[];

// A scoreboard (off_3EA710, 0x3B8 bytes): of the kind arg_0 (0 during the
// game, 1 at a round's end, 2 at the game's end), by teams unless the game
// type is 1, loaded from the layout arg_4 with its options (unk_3B4, over
// the options' layout arg_8; none during the game) shown, updated, drawn
// and given the pad's events first, over the pause menu arg_C; "continue"
// (unk_3A8) leaves the front end's screens (sub_220A80).
struct type_2207A0 : type_21EB30
{
    kujuUI::type_3E7CE8<type_2207A0> unk_3A8;
    type_21DFE0 *unk_3B4;

    type_2207A0(RwInt32 arg_0, const RwChar *arg_4, const RwChar *arg_8, type_21A5E0 *arg_C);
    virtual ~type_2207A0();
    virtual kujuUI::eEventWasHandled processEvent(const kujuUI::cStateChange &arg_0);
    virtual void vf_008();
    virtual void vf_00C();
    virtual void vf_014(RwReal arg_0);
    virtual void vf_018(kujuUI::type_1E4130 *arg_0);
    virtual RwInt32 vf_024();
    virtual void vf_04C();
    void sub_220A80();
};

// A "use now" question ("UseNow.layout", off_3EA800, 0x16C bytes; the pause
// menu's entry 0x12): "yes" and "no" (unk_154, unk_160) answer the pause
// menu as the next round's do (their actions shared through /OPT:ICF).
struct type_221590 : type_21CB10
{
    kujuUI::type_3E7CE8<type_221590> unk_154;
    kujuUI::type_3E7CE8<type_221590> unk_160;

    type_221590(const RwChar *arg_0, type_21A5E0 *arg_4);
    virtual ~type_221590();
    void sub_219E70();
    void sub_219E90();
};

// A vote's confirmation (off_3EA890, 0x33C bytes; the pause menu's entry
// 0xC): the votes' page with "WillStartRound.layout" (unk_194: "ok",
// unk_31C, and "cancel", unk_328) over it, and what is voted (unk_334, -1
// at first: 0 the level, 1 the game type, 2 a player's kick; its value
// unk_338), carried out by sub_221FC0. "yes" (slot 20) asks the
// confirmation unless a kick is voted, which it carries out at once; "no"
// (slot 21) forgets the vote. Its question (slot 22, sub_221A80) unwinds
// strings through the library's out-of-line string destructor (sub_43900)
// and is not matched.
struct type_221780 : type_216130
{
    type_2049D0 unk_194;
    kujuUI::type_3E7CE8<type_221780> unk_31C;
    kujuUI::type_3E7CE8<type_221780> unk_328;
    RwInt32 unk_334;
    RwInt32 unk_338;

    type_221780(const RwChar *arg_0, type_21A5E0 *arg_4);
    virtual ~type_221780();
    virtual void vf_008();
    virtual void vf_00C();
    virtual void vf_050();
    virtual void vf_054();
    virtual type_1CB670 vf_058();
    void sub_2219A0();
    void sub_2219E0();
    void sub_221FC0();
};

// The votes' pages over the game type ("VoteGame.layout", off_3EA950) and
// the level ("VoteMap.layout", off_3EA9C0), 0x18C bytes each (the pause
// menu's entries 0xB and 0xA): the value picked ("MapType", the game type
// selector, or "Level", the level selector; unk_16C, unk_154 its action
// doing nothing) and "confirm" (unk_160: the vote called and back to the
// pause menu's entry 0). Their kind (slot 9) is 0x3A, one inline shared
// through /OPT:ICF.
struct type_2220E0 : type_21CB10
{
    kujuUI::type_3E7CE8<type_2220E0> unk_154;
    kujuUI::type_3E7CE8<type_2220E0> unk_160;
    type_210180 unk_16C;

    type_2220E0(const RwChar *arg_0, type_21A5E0 *arg_4);
    virtual ~type_2220E0();
    virtual RwInt32 vf_024()
    {
        return 0x3A;
    }
    void sub_222270();
    // Empty: shared through /OPT:ICF.
    void sub_1E41C0();
};
struct type_222350 : type_21CB10
{
    kujuUI::type_3E7CE8<type_222350> unk_154;
    kujuUI::type_3E7CE8<type_222350> unk_160;
    type_211680 unk_16C;

    type_222350(const RwChar *arg_0, type_21A5E0 *arg_4);
    virtual ~type_222350();
    virtual RwInt32 vf_024()
    {
        return 0x3A;
    }
    void sub_2224E0();
    // Empty: shared through /OPT:ICF.
    void sub_1E41C0();
};

// The votes' choice ("VoteOptions.layout", off_3EAA40, 0x17C bytes; the pause
// menu's entry 8): "player" (unk_154, while more than two players are in
// the session, or two with this machine the host), "map" and "game"
// (unk_164, unk_170), each the pause menu's entry 9, 0xA or 0xB with 8 to
// go back to.
struct type_2225E0 : type_21CB10
{
    kujuUI::type_3E7264<type_2225E0> unk_154;
    kujuUI::type_3E7CE8<type_2225E0> unk_164;
    kujuUI::type_3E7CE8<type_2225E0> unk_170;

    type_2225E0(const RwChar *arg_0, type_21A5E0 *arg_4);
    virtual ~type_2225E0();
    void sub_222790();
    void sub_2227B0();
    void sub_2227D0();
    bool sub_2227F0();
};

// The weapon selection (off_3EAC08, 0x210 bytes; the pause menu's entry 1
// over "weaponselect.layout", and the in-game screens' first over
// "initialweaponselect.layout" when arg_0 is set): the weapon classes
// ("weaponselect", unk_1C8, over the widgets' registry unk_1BC; "Machine
// Gun", "Rifle", "Sniper Rifle" and "Heavy MG"), its picture ("weapon",
// unk_184: the look for the class picked and the team shown, unk_190, from
// the teams' libraries unk_194 and looks unk_19C, loaded when loaded, slot
// 15, and dropped by sub_223C50), its hint ("weaponhint", unk_1E8),
// "selectweapon" (unk_160: the weapon set and back, or the front end's
// screens left) and "WeaponBack" (unk_178, in the pause menu only).
struct type_223280 : type_21CB10
{
    kujuUI::type_3E7CE8<type_223280> unk_154;
    kujuUI::type_3E7CE8<type_223280> unk_160;
    kujuUI::type_3E7CE8<type_223280> unk_16C;
    kujuUI::type_3E7CE8<type_223280> unk_178;
    kujuUI::type_1E7490 unk_184;
    RwInt32 unk_18C;            // the weapon class shown
    RwInt32 unk_190;
    type_E8780<kujuUI::type_1ECCE0> unk_194[2];
    kujuUI::type_1E3BA0 *unk_19C[2][4];
    kujuUI::type_1EFCF0<kujuUI::type_3E7D08 *> unk_1BC;
    type_1FCDC0<type_224010_value> unk_1C8;
    kujuUI::type_1F28C0 unk_1E8;

    type_223280(RwInt32 arg_0, type_21A5E0 *arg_4);
    virtual ~type_223280();
    virtual void vf_008();
    virtual void vf_014(RwReal arg_0);
    virtual RwInt32 vf_024();
    virtual void givenFocus();
    virtual void vf_03C();
    void sub_223830();
    void sub_223890();
    bool sub_223940(RwInt32 arg_0);
    void sub_223C50();
    void sub_223D00(type_224010_value arg_0);
    void sub_223F50();
};

// The kick page (off_3E9C50 and off_3E9C34, 0x340 bytes): the other players'
// rows ("PlayerList", its second base; the rows kept in unk_164, filled
// when shown, slot 2, and cleared by sub_222C70, shared through /OPT:ICF)
// and the confirmation ("KickPlayerConfirm.layout", unk_170, loaded with
// it, slot 14; the player's name "KickPlayerConfirm", unk_2F8, "Yes" and
// "No", unk_320 and unk_330). Leaving takes the confirmation off the pad's
// widget stack (slot 3, shared through /OPT:ICF at 0x222F20).
struct type_2181E0 : type_21CB10, type_218B80
{
    std::list<type_21CE60 *> unk_164;
    type_2049D0 unk_170;
    kujuUI::type_1F28C0 unk_2F8;
    kujuUI::type_3E7CE8<type_2181E0> unk_320;
    kujuUI::type_3E7CE8<type_2181E0> unk_330;

    type_2181E0(const RwChar *arg_0, type_21A5E0 *arg_4);
    virtual ~type_2181E0();
    virtual void vf_008();
    virtual void vf_00C();
    virtual void vf_038();
    virtual void pvf_010();
    void sub_2184D0();
    void sub_2187B0();
    void sub_2187E0();
    void sub_218800();
    void sub_222C70();
};

// The vote on a player ("VotePlayer.layout", off_3EAB08 and off_3EAAEC, 0x348
// bytes; the pause menu's entry 9): the kick page's layout over the other
// players ("PlayerList", its second base, the rows kept in unk_164 and
// cleared by sub_222C70, the players shown unk_340, filled when shown,
// slot 2, and again when they change, slot 5) with the confirmation
// ("VotePlayerConfirm.layout", unk_170: the player's name
// "VotePlayerConfirm", unk_2F8, "Yes" calling the vote, unk_320, and "No"
// going back, unk_330), and unk_344. Its columns' selection handler (slot 4,
// sub_222F60) is the kick page's.
struct type_222960 : type_21CB10, type_218B80
{
    std::list<type_21CE60 *> unk_164;
    type_2049D0 unk_170;
    kujuUI::type_1F28C0 unk_2F8;
    kujuUI::type_3E7CE8<type_222960> unk_320;
    kujuUI::type_3E7CE8<type_222960> unk_330;
    type_1DDE20_mask unk_340;
    RwInt32 unk_344;

    type_222960(const RwChar *arg_0, type_21A5E0 *arg_4);
    virtual ~type_222960();
    virtual void vf_008();
    virtual void vf_00C();
    virtual void vf_014(RwReal arg_0);
    virtual void vf_038();
    virtual void pvf_010();
    void sub_222C70();
    void sub_222D20();
    void sub_223050();
    void sub_2231A0();
};

// The in-game controls' legend ("IngameControls.layout", off_3E9CF0, 0x1A4
// bytes; the one instance, dword_5043C0) over the pause menu arg_4: its
// texts "LeftText" (unk_154, set by sub_218F20) and "RightText" (unk_17C).
struct type_218DD0 : type_21CB10
{
    kujuUI::type_1F28C0 unk_154;
    kujuUI::type_1F28C0 unk_17C;

    type_218DD0(const RwChar *arg_0, type_21A5E0 *arg_4);
    virtual ~type_218DD0();
    void sub_218F20(const type_1A5EA0 &arg_0);
};
extern type_218DD0 *dword_5043C0;

// A sign-in page with no layout of its own (off_3E9D40, 0x154 bytes): shown
// (slot 2), it asks the service started last for step 6, and its update
// (slot 5) goes back while the service's state is not 6.
struct type_218F40 : type_21CB10
{
    type_218F40(type_21A5E0 *arg_0);
    virtual ~type_218F40();
    // vf_00C, as the image's vtable has it: type_219C20's code (folded into
    // sub_219CC0); defined in unit_218F40.
    virtual void vf_00C();
    virtual void vf_008();
    virtual void vf_014(RwReal arg_0);
    // vf_018, as the image's vtable has it (a trivial body, folded into
    // sub_15FB30 with every other copy).
    virtual void vf_018(kujuUI::type_1E4130 *arg_0)
    {
    }
};

// The in-game Live options ("LiveOptionsInGame.layout", off_3E9DB8, 0x224
// bytes): "FriendsList" and "PlayersList" (unk_154, unk_164: the pause
// menu's entries 0x16 and 0x17, back to 0x15), "AppearOffline" (unk_174),
// "SignOut" (unk_184: confirmed through the two-prompt dialog, with
// unk_190 signing out and unk_19C doing nothing; not over the system link)
// and the texts "FriendsFlagText", "AppearStatus" and "SignOutStatus"
// (unk_1A8 to unk_1F8), with whether the service was signed in when they
// were last set (unk_220).
struct type_219010 : type_21CB10
{
    kujuUI::type_3E7264<type_219010> unk_154;
    kujuUI::type_3E7264<type_219010> unk_164;
    kujuUI::type_3E7264<type_219010> unk_174;
    kujuUI::type_3E7CE8<type_219010> unk_184;
    kujuUI::type_3E7CE8<type_219010> unk_190;
    kujuUI::type_3E7CE8<type_219010> unk_19C;
    kujuUI::type_1F28C0 unk_1A8;
    kujuUI::type_1F28C0 unk_1D0;
    kujuUI::type_1F28C0 unk_1F8;
    bool unk_220;

    type_219010(const RwChar *arg_0, type_21A5E0 *arg_4);
    virtual ~type_219010();
    virtual void vf_014(RwReal arg_0);
    void sub_219320();
    void sub_2194E0();
    void sub_219500();
    void sub_219520();
    void sub_219560();
    bool sub_219A80();
    void sub_219AA0();
    bool sub_219AD0();
    // Empty: shared through /OPT:ICF.
    void sub_1E41C0();
};

// A sign-in page with no layout of its own (off_3E9E68, 0x154 bytes): shown
// (slot 2), it asks the service started last for step 7, left (slot 3) it
// ends the service's Live feature, and its update (slot 5) goes back while
// the service's state is not 7.
struct type_219C20 : type_21CB10
{
    type_219C20(type_21A5E0 *arg_0);
    virtual ~type_219C20();
    virtual void vf_008();
    virtual void vf_00C();
    virtual void vf_014(RwReal arg_0);
    // vf_018, as the image's vtable has it (a trivial body, folded into
    // sub_15FB30 with every other copy).
    virtual void vf_018(kujuUI::type_1E4130 *arg_0)
    {
    }
};

// The next round asked ("NextRound.layout", off_3E9EB8, 0x16C bytes): "yes"
// and "no" (unk_154, unk_160) answer the pause menu.
struct type_219D10 : type_21CB10
{
    kujuUI::type_3E7CE8<type_219D10> unk_154;
    kujuUI::type_3E7CE8<type_219D10> unk_160;

    type_219D10(const RwChar *arg_0, type_21A5E0 *arg_4);
    virtual ~type_219D10();
    void sub_219E70();
    void sub_219E90();
};

// A warning the cancel warnings page shows (only its slots are known):
// cancelled (slot 0, the page's "Cancel"), whether another may take its
// place (slot 1), and told it is no longer shown (slot 2). The network
// game's step (sub_1A2A80) shows and hides dword_5051D0.
struct type_5051D0
{
    virtual void vf_000() = 0;
    virtual bool vf_004() = 0;
    // Empty, out of line: folded (/OPT:ICF) into pDtor (0x1E41C0).
    virtual void vf_008();
};
// The one warning the network game's step shows (dword_5051D0): its cancel
// leaves the game (sub_1C44A0; its code folded, /OPT:ICF, into type_21DFE0's
// sub_21E9A0) and another may always take its place (0x1E4AA0, likewise).
// Its implicit constructor stores both vtables (0x30DB20).
struct type_5051D0_quit : type_5051D0
{
    virtual void vf_000();
    virtual bool vf_004();
    // Its kind (4): a new virtual (slot 0xC: the image's vtable ends with it), folded
    // (/OPT:ICF) into Trigger's vf_018 (0x9E000).
    virtual RwInt32 vf_00C();
};
extern type_5051D0_quit dword_5051D0;

// The cancel warnings ("CancelWarnings.layout", off_3E94E0, 0x190 bytes;
// the one instance, dword_5051CC): the warning shown (unk_154) with its
// text ("Warning", unk_158) and "Cancel" (unk_180), and the in-game screen
// to go back to (unk_18C, 0xB for none). The warnings are shown
// (sub_2155A0: over the screen shown unless it is a page with a pause
// menu), hidden (sub_2156B0), tested (sub_215910, sub_215A90) and
// retexted (sub_215970); the page's own screen (0xA) exists (sub_215A50).
// Its kind (slot 9) is 4 for dword_5051D0, else 0.
struct type_215740 : type_21CB10
{
    type_5051D0 *unk_154;
    kujuUI::type_1F28C0 unk_158;
    kujuUI::type_3E7CE8<type_215740> unk_180;
    RwInt32 unk_18C;

    type_215740(type_21A5E0 *arg_0);
    virtual ~type_215740();
    virtual kujuUI::eEventWasHandled processEvent(const kujuUI::cStateChange &arg_0);
    virtual void vf_008();
    virtual void vf_00C();
    virtual RwInt32 vf_024();
    void sub_2158B0();
    static bool sub_2155A0(type_5051D0 *arg_0);
    static void sub_2156B0(type_5051D0 *arg_0);
    static bool sub_215910(type_5051D0 *arg_0);
    static void sub_215970(const type_1A5EA0 &arg_0, type_5051D0 *arg_4);
    static bool sub_215A50();
    static bool sub_215A90();
};
extern type_215740 *dword_5051CC;

// The in-game menus (the in-game menus' module, unit_204020, builds one of
// each, in this order, as menus 0 to 13; menus 0 to 3, 8 and 10 are in
// game/livemenu.h): each
// a menu of its own class, not yet matched; only their sizes and
// constructors are known.

#endif
