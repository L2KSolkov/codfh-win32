/*
 * The late service (unit_2261C0) with its real layout, for the units that
 * see the XDK. game/startup.h declares the same class for the others, with
 * the XDK's types as bytes; include this header first to get this view.
 */
#ifndef GAME_LIVESERVICE_H
#define GAME_LIVESERVICE_H

#include <vector>
#include "types/cXboxLive.h"
#include "game/xboxlive.h"
#include "rw/rwxbox.h"

// The late service (unit_2261C0): the host of the Live engine (uix.lib),
// built on first use by sub_227560 (a function's static at dword_5051E8).
// It starts the engine with the UI plugin (unk_506318) and the audio plugin
// (unk_5064DC), runs and draws it each frame, starts its features (sign-in,
// friends, players), registers the players list's items (unk_148), follows
// the mute list and joins the sessions friends invite to (unk_04).
struct type_22AF50;
struct type_5051E8
{
    RwInt32 unk_00;             // set: the session joined (unk_04) differs
                                // from the network system's
    type_1D9270_session unk_04; // the session a friend's invite joins
    DWORD unk_78;               // the engine's "host no migration"
    IDirect3DSurface8 *unk_7C;  // the back buffer the engine draws to
    DWORD unk_80;               // the engine's DoWork flags
    LiveEngine *unk_84;
    bool unk_88;                // set: the voice mail engine is given
    DWORD unk_8C;
    RwInt32 unk_90;             // the feature started (sub_2270E0's argument)
    DWORD unk_94;               // the notification state's flags
    XNKID unk_98;               // the session the notification state names
    RwInt32 unk_A0;             // set: appearing offline (the Live options)
    RwInt32 unk_A4;             // cleared by the front end's leave
                                // (sub_1C4B10) when set
    XONLINE_ACCEPTED_GAMEINVITE unk_A8;
    RwInt32 unk_144;            // set: unk_A8 waits to be joined
    std::vector<type_22AF50 *> unk_148; // the players list's items
    RwInt32 unk_158;            // the network system's state, last seen
    bool unk_15C;               // set: the mute list is started
    bool unk_15D;
    XONLINETASK_HANDLE unk_160; // the mute list's start
    RwInt32 unk_164;            // set: the mute list is to be read
    RwUInt32 unk_168;           // the peer the mute list is checked for
    XONLINETASK_HANDLE unk_16C; // the mute list's read
    DWORD unk_170;
    XONLINE_MUTELISTUSER unk_174[0xFA];
    type_1DDE20_mask unk_1114;  // the peers to register
    type_1DDE20_mask unk_1116;  // the peers registered
    RwInt32 unk_1118;           // the engine's "display connection errors"
    RwInt32 unk_111C;           // set: the end of a game neither tells the
                                // rules nor fades (the manager's step)
    RwInt32 unk_1120;
    RwInt32 unk_1124;           // set: the dashboard's launch leaves the
                                // launch data's Xbox Live choice clear

    type_5051E8();
    RwInt32 sub_226360();
    void sub_2266D0(const type_1CCA10 &arg_0);
    void sub_226D60();
    void sub_226D80();
    void sub_226DD0(const type_1CCA10 &arg_0);
    void sub_227070();
    // What the multiplayer manager's leave passes on (sub_1AA320).
    void sub_2270E0(RwInt32 arg_0);
    // The Live feature ended (CLiveEngine::EndFeature), then sub_2279D0
    // called with 1.
    void sub_227530();
    // What the Live pages ask: its state (sub_2275D0; the sign-in page
    // waits for 2), appearing offline or not (sub_227B80) and signing out
    // (sub_2278C0).
    RwInt32 sub_2275D0();
    // What the front end passes on (sub_1C44B0, sub_1C44D0).
    void sub_2275F0(RwInt32 arg_0);
    void sub_227660(RwInt32 arg_0);
    void sub_227870();
    void sub_2278C0();
    RwInt32 sub_227950();
    bool sub_2279D0(bool arg_0);
    void sub_227AC0(RwInt32 arg_0);
    void sub_227B80(RwInt32 arg_0);
    void sub_227BA0();
    void sub_227C00();
    void sub_227C50();
    void sub_227CA0();
    void sub_227D70(const XONLINE_FRIEND *arg_0);
    void sub_227F30();
    // The voice chat's (sub_1C6EC0, sub_1C7420): stops and restarts the
    // voice manager's engine; follows the speakers' setting.
    void sub_227F70();
    void sub_228000();
    void sub_228040();
    void sub_228090(RwInt32 arg_0);
    // What the in-game menus' loop asks each frame: whether the pad's events
    // are dropped (sub_2280E0), and a step after drawing (sub_227070).
    RwInt32 sub_2280E0();
    // Whether the dashboard's launch may ask to sign in again (sub_228100).
    bool sub_228100();
    void sub_228120(UIX_EXIT_INFO *arg_0, RwInt32 arg_4);
    RwInt32 sub_2281F0(UIX_EXIT_INFO *arg_0, RwInt32 arg_4);
    void sub_228240(UIX_EXIT_INFO *arg_0, RwInt32 arg_4);
    // What the multiplayer manager's reset and leave pass on (sub_1AF6F0,
    // sub_1AF750).
    void sub_2283F0(RwInt32 arg_0);

    // An inline accessor for unk_1124, with no address and so no database
    // name; named for its field. Evidence: the dashboard's launch
    // (sub_20AD30) reads it through a `this` copy and a return slot.
    RwInt32 get_unk_1124()
    {
        return unk_1124;
    }

    // An inline accessor for unk_111C, with no address and so no database
    // name; named for its field. Evidence: the multiplayer manager's step
    // (sub_1AAB50) reads it through a `this` copy and a return slot.
    RwInt32 get_unk_111C()
    {
        return unk_111C;
    }
    // Inline accessors for unk_A4, with no addresses and so no database
    // names; named for their field. Evidence: the front end's leave
    // (sub_1C4B10) reads it through a `this` copy and a return slot, and
    // clears it through a `this` slot.
    // An inline accessor for unk_A0, with no address and so no database
    // name; named for its field. Evidence: the Live options' "AppearOffline"
    // (sub_20A1F0) reads it through a `this` copy and a named local.
    // Likewise returning it directly: its value goes through a temporary
    // after the `this` copy's. Evidence: the Live options' status text
    // (sub_20A0E0).
    RwInt32 get_unk_A0_direct()
    {
        return unk_A0;
    }
    RwInt32 get_unk_A0()
    {
        RwInt32 r = unk_A0;
        return r;
    }
    RwInt32 get_unk_A4()
    {
        return unk_A4;
    }
    // Evidence: the Xbox Live menu's update (type_20B9D0::vf_014) joins
    // the waiting session when it is set.
    RwInt32 get_unk_144()
    {
        return unk_144;
    }
    void set_unk_A4(RwInt32 arg_0)
    {
        unk_A4 = arg_0;
    }
    // An inline setter for unk_1120, with no address and so no database
    // name; named for its field. Evidence: the UI plugin's text box render
    // (CUITextBoxObject::vf_01C) sets it through a `this` slot, with the
    // value loaded into a register first, as a bool converts.
    void set_unk_1120(bool arg_0)
    {
        unk_1120 = arg_0;
    }
    // Its first word: an out-of-line getter folded by /OPT:ICF into 0x1EE9D0
    // (config/aliases.txt); the game data's step (sub_1B5A40) ends the game
    // when it is set.
    RwInt32 sub_1EE9D0() const;
};
// The first signed-in port (-1 when none) of arg_0, or of the signed-in
// users when it is 0.
RwInt32 sub_227900(XONLINE_USER *arg_0);
void sub_226DA0(RwInt32 arg_0);
type_5051E8 *sub_227560();
// unk_1120's getter: a free inline with no address. Evidence: the in-game
// screens' legend update (sub_1FFE80) keeps the service in a slot nearer
// the frame than the value read from it.
inline RwInt32 get_unk_1120(type_5051E8 *arg_0)
{
    return arg_0->unk_1120;
}

// Set: the pads' input goes to the engine (the late service's frame hands it
// the pad's state; otherwise its input is cleared).
extern RwInt32 dword_42926C;
// The Live engine's skin file (uix.lib's data).
extern const RwChar *pSkinFileName;
// The language's index for the engine (unit_19B0F0).
RwInt32 sub_19BEA0();
// The pad's state (game/padlib.h, not included here: its levels.h clashes
// with game/waitscreen.h's declarations).
struct type_4F4638;
type_4F4638 *sub_19E4B0();

#endif
