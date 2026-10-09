/*
 * type_DC400: the HUD (dword_4B9190; "SetHudVisible" and the other HUD
 * script commands reach it there), a 0x1A500-byte object sub_E9790 makes
 * with new when its flag 4 is set and then sets up (sub_DC5F0). Named for
 * its constructor. It holds 151 items of 0x2C0 bytes from +0xE0 (quads,
 * images and text, some parents of others), two kujuUI fonts (unk_88,
 * unk_8C), the HUD font (unk_1A028), its texture dictionary (unk_1A024),
 * the damage markers (unk_1A0D4) and the soldiers' name labels
 * (unk_1A1A8). The layout is filled in as its methods are recovered; the
 * rest is padding.
 */
#ifndef TYPE_DC400_H
#define TYPE_DC400_H

#include <string>
#include "types/type_505188.h"
#include <vector>

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "rw/bamatrix.h"
#include "rw/badevice.h"
#include "rw/rt2d.h"
#include "rw/batextur.h"
#include "rw/baraster.h"
#include "types/type_D48D0.h"
#include "types/type_1DDE20_mask.h"
#include "types/type_1CCA10.h"
#include "game/loc.h"
#include "game/pool.h"
#include "game/netqueue.h"
#include "types/type_3D3548.h"
#include "types/type_10F710.h"
#include "types/type_3DAFC8.h"
#include "types/type_DA580.h"
#include "types/type_62A60.h"
#include "game/netscore.h"
#include "game/netlisten.h"
#include "types/SplinePath.h"
#include "rw/rphanim.h"
#include "rw/baengine.h"
#include "game/startup.h"
#include "game/objectives.h"
#include "game/kujufont.h"

struct RwCamera;

// The 0x18-byte records of type_DC400::unk_1A0D4, the damage direction
// markers (items 0x8B to 0x8F): the direction the hit came from (unk_00),
// when (unk_0C, dword_4B9154), whether it shows (unk_10) and the attacker
// (unk_14).
struct type_DC500
{
    RwV3d unk_00;
    RwReal unk_0C;
    RwInt32 unk_10;
    type_D48D0 unk_14;
};

// The 0x30-byte records of type_DC400::unk_1A1A8, the soldiers' name labels:
// the name (unk_00), whether the record is in use (unk_24), the soldier
// (unk_28) and the index of the HUD item they drive (unk_2C, 106 on).
struct type_DC530
{
    RwChar unk_00[0x20];
    RwReal unk_20;              // its time shown (type_DC400::sub_DD1C0)
    RwInt32 unk_24;
    type_D48D0 unk_28;
    RwInt32 unk_2C;
};

// The items' starting value of unk_24 (.data).
#ifdef CODFH_PLAIN
extern RwReal &flt_4B8F14;
#else
extern RwReal flt_4B8F14;
#endif

// The in-game screens the HUD makes at set-up (unk_1A4B0: game/ingamescreens.h;
// the database's constructor sub_1FF260 is type_1FF250's).
struct type_1FF250;

// The HUD's counts: MP's, and single player's (CODFH_SP). Single player's HUD is 0xF420 bytes
// (SP 0xB2CDA allocates it; MP's is 0x1A500): 101 items of 0x260 bytes from +0x80 (their
// children 16; SP 0xA7A20 indexes them by 0x260 and its tail starts at +0xF060), one objective
// pointer angle (its set-up, SP 0xAC7D0, clears four fields before the 15 marker angles where
// MP's clears five) and 10 name labels (its constructor, SP 0xA99B0, builds ten of 0x30 bytes).
#ifdef CODFH_SP // SP 0xA99B0, 0xAC7D0
enum { type_DC400_items = 101, type_DC400_children = 20, type_DC400_D8 = 1,
       type_DC400_objectives = 1, type_DC400_labels = 10 };
#else // MP 0xDC400, 0xDC5F0
enum { type_DC400_items = 151, type_DC400_children = 40, type_DC400_D8 = 2,
       type_DC400_objectives = 2, type_DC400_labels = 16 };
#endif

// The HUD's items (0x2C0 bytes; 151 of them from +0xE0): a quad (unk_118,
// drawn with the texture's raster unk_114), a frame matrix (unk_1A0), up to
// 40 children (unk_204) and their text settings (unk_2B0 on, unk_2B4 the
// alignment, unk_2BC which font).
struct type_DC400_E0
{
    RwChar unk_00[0x20];        // its name
    RwInt32 unk_20;
    RwReal unk_24;
    RwInt32 unk_28;             // set: restart the fade unk_2C
    RwReal unk_2C;              // a fade's time left (sub_DD1C0)
    RwInt32 unk_30;             // fading out (-1) or in (1) (sub_DD1C0)
    RwRGBAReal unk_34;
    RwInt32 unk_44;
    RwInt32 unk_48;
    RwInt32 unk_4C;
    RwInt32 unk_50;
    RwInt32 unk_54;
    RwInt32 unk_58;
    RwInt32 unk_5C;
    RwChar unk_60[0x80];        // its text
    RwV3d unk_E0[4];
    RwTexture *unk_110;
    RwRaster *unk_114;
    RwIm2DVertex unk_118[4];
    RwV2d unk_188;
    RwRGBA unk_190;
    RwUInt8 unk_194[0xC];
    RwMatrix unk_1A0;
    RwReal unk_1E0;             // its angle (sub_E6270)
    RwReal unk_1E4;
    RwV3d unk_1E8;              // its pivot, a fraction of its size (the
                                // shell's command 101 sets it whole)
    RwV3d unk_1F4;
    type_DC400_E0 *unk_200;     // its parent
    type_DC400_E0 *unk_204[type_DC400_children]; // its children (unk_2A4 of them)
    RwInt32 unk_2A4;
    RwInt32 unk_2A8;
    RwInt32 unk_2AC;
#ifndef CODFH_SP // MP only: single player's item has 20 children and no +0x2B0..+0x2BF (SP 0xAC7D0
                 // clears unk_204[20], then unk_2A4 at +0x254; SP 0xA8C20, 0xA94F0, 0xA98B0)
    RwInt32 unk_2B0;
    RwInt32 unk_2B4;
    RwReal unk_2B8;             // item 80's blink time (sub_DD1C0)
    RwInt32 unk_2BC;
#endif
};

// Two places of the HUD's items (type_DC400::unk_14): one taken when the
// HUD is reset (sub_E0CC0), one when it shows a vehicle (sub_E0B60).
struct type_DC400_14
{
    RwV2d unk_00;
    RwV2d unk_08;
};

struct type_DC400
{
    RwInt32 unk_00;
    RwInt32 unk_04;             // dword_4B86F8's pause bit at set-up
    RwInt32 unk_08;
    RwInt32 unk_0C;
    RwInt32 unk_10;
    type_DC400_14 unk_14[4];
    RwReal unk_54;              // the crosshair's place (the player's
    RwReal unk_58;              // sub_100680 draws it there)
#ifndef CODFH_SP // MP +0x5C..+0xB7; single player has none of them: its unk_B8 is at +0x5C (SP 0xAAD20 compares it there, MP 0xDFE00's +0xB8) and its later members sit 0x5C lower
    RwReal unk_5C;
    RwRGBA unk_60[5];           // the objectives' states' colours (sub_E7D00)
    RwRGBA unk_74;              // colours the shell's commands set
    RwRGBA unk_78;
    RwInt32 unk_7C;
    RwInt32 unk_80;
    RwReal unk_84;
    type_E8780<type_1E5A60> unk_88;
    type_E8780<type_1E5A60> unk_8C;
    RwInt32 unk_90;
    RwInt32 unk_94;
    RwTexture *unk_98[4];       // the CTF teams' icons (sub_E0E90)
    RwTexture *unk_A8[4];       // and their flags' icons
#endif
    RwReal unk_B8;
    RwInt32 unk_BC;
    RwInt32 unk_C0;
    RwInt32 unk_C4;
    RwInt32 unk_C8;
    RwInt32 unk_CC;
    RwInt32 unk_D0;
    RwReal unk_D4;              // the radar's heading (sub_E4030)
    RwInt32 unk_D8[type_DC400_D8];
    type_DC400_E0 unk_E0[type_DC400_items];
    RwInt32 unk_1A020;
    RwTexDictionary *unk_1A024;
    type_DA580 *unk_1A028;      // the HUD's font
    RwCamera *unk_1A02C;
    RwInt32 unk_1A030;          // the vehicle's kind (sub_E0B60)
    type_D48D0 unk_1A034;
    RwReal unk_1A038;           // the vehicle's heading and its turret's
    RwReal unk_1A03C;           // (degrees from north; sub_DD1C0)
    RwReal unk_1A040;           // the radar's heading, its target (sub_E4030)
    RwReal unk_1A044;           // and its smoothed value
    RwReal unk_1A048;           // its smoothing rate
    RwReal unk_1A04C[type_DC400_objectives]; // the objectives' pointers' angles
    RwReal unk_1A054[15];       // the markers' pointers' angles
    RwInt32 unk_1A090[6];
    RwInt32 unk_1A0A8;
    RwReal unk_1A0AC;           // the flash's time (sub_DD1C0)
    RwReal unk_1A0B0;           // the screen flash's colour (sub_E5C60)
    RwReal unk_1A0B4;
    RwReal unk_1A0B8;
    RwReal unk_1A0BC;
    union
    {
        RwInt32 unk_1A0C0;
        RwReal unk_1A0C0_f;     // the flash's length (sub_DD1C0)
    };
    RwReal unk_1A0C4;           // its alpha, 0 to 2 (x 128)
    RwReal unk_1A0C8;
    RwInt32 unk_1A0CC;
    RwInt32 unk_1A0D0;
    type_DC500 unk_1A0D4[5];
    RwV2d unk_1A14C;            // the shell's commands 50 and 51 set
    RwV2d unk_1A154;            // each whole
    const RwChar *unk_1A15C;    // item 2's text
    RwReal unk_1A160;           // item 2's scroll time (sub_E5480)
    RwChar unk_1A164[0x40];     // item 2's text before its colon
    RwInt32 unk_1A1A4;          // the buddy's icon (sub_DFF40)
    type_DC530 unk_1A1A8[type_DC400_labels];
    RwInt32 unk_1A4A8;
    RwReal unk_1A4AC;
#ifndef CODFH_SP // MP only: single player makes no in-game screens (kujuUI), its later members sit 4 lower
    type_1FF250 *unk_1A4B0;
#endif
#ifdef CODFH_SP // a float in single player (SP 0xACDB0 and 0xA81E0 load it with fld at +0xF3CC)
    RwReal unk_1A4B4;
#else
    RwInt32 unk_1A4B4;
#endif
    RwUInt8 unk_1A4B8;
    RwUInt8 unk_1A4B9[3];
    RwInt32 unk_1A4BC;
    RwChar unk_1A4C0[0x40];     // the HUD font's name (sub_E52B0)
#ifdef CODFH_SP // single player's HUD is 0xF420 bytes (SP 0xB2CDA allocates it): 8 more after the name
    RwUInt8 unk_sp_F418[0x8];
#endif

    type_DC400();
    ~type_DC400();
    // Sets the HUD up for the camera arg_0; returns 1.
    RwInt32 sub_DC5F0(RwCamera *arg_0);
    void sub_DEB80(RwInt32 arg_0);
    void sub_DEEB0(RwInt32 arg_0);
#ifdef CODFH_SP
    // Single player only: the pause screen's parts sub_DF000 draws (SP 0xA81E0, 0xA7FB0).
    void sp_sub_A81E0();
    void sp_sub_A7FB0();
    // Single player only (SP 0xA9E00).
    void sp_sub_A9E00(RwInt32 arg_0);
#endif
    void sub_DEEF0(RwInt32 arg_0);
    // Sets item arg_0's colour unk_34 (items 0 to 150 only).
    void sub_E7480(RwInt32 arg_0, RwRGBAReal *arg_4);
    // Sets item arg_0's depth arg_4 (0 near, 1 far) and its quad's screen z.
    void sub_E7140(RwInt32 arg_0, RwReal arg_4);
    // Sets item arg_0's unk_188 and marks it for rebuilding.
    void sub_E74D0(RwInt32 arg_0, RwV2d *arg_4);
    // The HUD's frame: the pending toggle (byte_4B8975) first, then the
    // items from the first; arg_0 (the frame's time) unused.
    void sub_DD180(RwReal arg_0);
    // The HUD's update over the frame's time arg_0 (the shell manager's,
    // type_4B8EF0::sub_E9AD0, calls it after sub_DD180): the player's and
    // the network game's items, the name labels, the items' fades, the
    // radar, the vehicle, the mode icon, the flash, the damage markers and
    // the in-game screens.
    void sub_DD1C0(RwReal arg_0);
    // Flips dword_4CF9A8 and redoes the items from the first.
    void sub_DFDD0();
    void sub_E6610(type_DC400_E0 *arg_0);
    // Marks arg_0 and its shown children for rebuilding (unk_2A8).
    void sub_E70D0(type_DC400_E0 *arg_0);
    // Reads the HUD's textures (the dictionary at arg_0) and builds it;
    // arg_4 (the shell manager passes F_HUD.TXD) unused.
    bool sub_DFB00(const RwChar *arg_0, const RwChar *arg_4);
    void sub_E07A0(RwInt32 arg_0, RwInt32 arg_4);
    void sub_E07D0();
    // Sets item arg_0's unk_50.
    void sub_E09E0(RwInt32 arg_0, RwInt32 arg_4);
    // Builds the HUD: its items' parents, names, texts, depths, textures,
    // localised texts and fonts, then sets each named item up from its
    // image.
    void sub_E0E90();
    void sub_E3B50(RwInt32 arg_0);
    // Sets item arg_0's alpha arg_4 (0 to 1; unk_24) and those of the items
    // shown with it.
    void sub_E3B90(RwInt32 arg_0, RwReal arg_4);
    // Applies the alpha arg_4 (0 to 255) to the item arg_0's quad and its
    // shown children's.
    void sub_E3CB0(type_DC400_E0 *arg_0, RwInt32 arg_4);
    // Likewise for arg_0 alone.
    void sub_E3DB0(type_DC400_E0 *arg_0, RwInt32 arg_4);
    // Item arg_0's text on (unk_2B0), its font (unk_2BC) and its alignment
    // (unk_2B4).
    void sub_E7540(RwInt32 arg_0, RwInt32 arg_4);
    void sub_E7570(RwInt32 arg_0, RwInt32 arg_4);
    void sub_E75A0(RwInt32 arg_0, RwInt32 arg_4);
    // Item arg_0's colour (unk_190).
    void sub_E75D0(RwInt32 arg_0, RwRGBA arg_4);
    // Empty but for a white it never uses; the camera arg_0 unused.
    void sub_E82F0(RwCamera *arg_0);
    // The HUD's render to the camera arg_0 (unk_1A02C when 0): the name
    // labels over the soldiers, then the items, the kujuUI text, the teams
    // and the scoreboard, the flash and unk_1A4B0, under its render states.
    void sub_DF000(RwCamera *arg_0);
    // Draws the kujuUI text of arg_0 and its children.
    void sub_E7600(type_DC400_E0 *arg_0);
    // Marks the items of each list in dword_4293D0 with its bit (unk_2AC).
    void sub_E83F0();
    // Hides the buddy (item 0x90) and resets its items' depth and alpha.
    void sub_E8470();
    // Resets the HUD's vehicle, records, labels and flags.
    void sub_DF880();
    // Frees the HUD's font, dictionary and unk_1A4B0; returns 1.
    RwInt32 sub_DF9F0();
    // Marks a hit from arg_0 (or from the point arg_4): rumbles the pad and,
    // unless arg_0 is marked already, turns a free marker to face it.
    void sub_DFB40(type_3D3548 *arg_0, RwV3d *arg_4);
    // Turns item arg_0 to the angle arg_4 (degrees).
    void sub_E5F60(RwInt32 arg_0, RwReal arg_4);
    // The name label of the soldier arg_0: its own, else a free one taken
    // for it (0 when none is free).
    type_DC530 *sub_E84E0(type_3DAFC8 *arg_0);
    // The letterbox bars (items 0x56 and 0x57) while unk_90 is 1 or 2.
    void sub_E79C0();
    // Draws the box (arg_0, arg_4) to (arg_8, arg_C) in the colour arg_10.
    void sub_E7AB0(RwReal arg_0, RwReal arg_4, RwReal arg_8, RwReal arg_C, RwRGBA arg_10);
    // Shows arg_0 at arg_4 (pixels; z unused) in the colour arg_10 with the
    // HUD font, narrowed for widescreen.
    void sub_E8220(const RwChar *arg_0, RwV3d arg_4, RwRGBA arg_10);
    // The objectives' labels ("A:", "B:", at item 0x52) and their states (at
    // item 0x53) in the states' colours, while item 0x52 is on.
    void sub_E7D00();
    // Draws the screen flash: the whole screen in unk_1A0B0's colour.
    void sub_E5C60();
    // Draws the item arg_0 and its shown children: text with the HUD font
    // (item 2 being the scrolling subtitles), or its quad.
    void sub_E5480(type_DC400_E0 *arg_0);
    // Turns the direction arg_4 (of item 31's height, times arg_10) toward
    // arg_8 as seen from the camera, smoothing the angle *arg_C over the time
    // arg_0.
    void sub_E3E60(RwReal arg_0, RwV3d *arg_4, RwV3d *arg_8, RwReal *arg_C, RwReal arg_10);
    // The radar: turns it to the camera's heading (from the level's north,
    // dword_4B8EF0's unk_00) over the time arg_0, then points at each
    // objective (along its path when it has one) and at each marker, with
    // the objectives' icons for the game type.
    void sub_E4030(RwReal arg_0);
    // The scoreboard at item 0x54: a label, a score and a player's name per
    // line, for the players unk_4F7EB8.unk_04 lists.
    void sub_E7EF0();
    // Loads the HUD font arg_0 (the current one's name when 0; "t10" when it
    // will not load) in place of the current one.
    void sub_E52B0(const RwChar *arg_0);
    // Item arg_0's unk_50.
    RwInt32 sub_E0A10(RwInt32 arg_0);
    // Turns item arg_0's unk_50 on and sets its unk_30 to arg_4.
    void sub_E0A30(RwInt32 arg_0, RwInt32 arg_4);
    void sub_E0A70(RwReal arg_0);
    void sub_E0DD0();
    // Empty: its arg_0 and two locals are unused.
    void sub_E09D0(RwInt32 arg_0);
    // Rebuilds item arg_0's matrix: turned by its angle about its pivot and
    // scaled by (arg_4, arg_8).
    void sub_E6270(RwInt32 arg_0, RwReal arg_4, RwReal arg_8);
    // Fades item 0x60 out over unk_1A0C8 as unk_1A4AC runs up by arg_0.
    void sub_DEF40(RwReal arg_0);
    // Shows arg_0 in item 0x46, 0x4A or 0x4F when it is on.
    void sub_E0220(RwInt32 arg_0);
    void sub_E0280(RwInt32 arg_0);
    void sub_E02E0(RwInt32 arg_0);
    // Sets item arg_0's text to arg_4.
    void sub_E7380(RwInt32 arg_0, const RwChar *arg_4);
    // Makes item arg_4 a child of item arg_0.
    void sub_E6570(RwInt32 arg_0, RwInt32 arg_4);
    // Names item arg_0 arg_4 and sets its flags unk_54, unk_5C, unk_58,
    // unk_44, unk_48 and unk_4C.
    void sub_E6F90(RwInt32 arg_0, const RwChar *arg_4, bool arg_8, bool arg_C, bool arg_10, bool arg_14,
                   bool arg_18, bool arg_1C);
    // Sets the fade unk_B8 (clamped to 0..1) on item 6 when item 4 is on.
    void sub_DFE00(RwReal arg_0);
    // Shows item 0x90 as arg_0, with the buddy arg_4's icon.
    void sub_DFEB0(bool arg_0, type_3D3548 *arg_4);
    // The buddy's health icon: 1 a person, 2 the M12, else the T34.
    void sub_DFF40(RwInt32 arg_0);
    // Sets item arg_0's image to the texture arg_4 of the HUD's dictionary,
    // sized to it unless the item has a size (or arg_8 asks); 0 when it is
    // not found.
    RwInt32 sub_E39B0(RwInt32 arg_0, const RwChar *arg_4, RwInt32 arg_8);
    // The buddy arg_0's health bar (item 0x93), or item 0x90 off when the
    // buddy is gone (its unk_28_9).
    void sub_DFFC0(type_D48D0 arg_0);
    // Sets unk_84 (clamped to 0..1) on item 0x96 when item 0x94 is on.
    void sub_E0080(RwReal arg_0);
    // Shows the time arg_0 (seconds) as minutes, ":" and seconds in items
    // 0x43, 0x42 and 0x44 when all three are on.
    void sub_E0110(RwReal arg_0);
    // Shows one of items 0xB, 0xC and 0xD by arg_0 (0, 1 or 2).
    void sub_E0340(RwInt32 arg_0);
    // Sets the HUD's mode unk_C0 and shows its icon among items 0x7B to 0x87
    // (none while the player's unk_1B2C is set).
    void sub_E0410(RwInt32 arg_0);
    // Sets unk_CC and from it the mode unk_C0 (sub_E0410).
    void sub_E06E0(RwInt32 arg_0);
    // Sets unk_C8 and from it unk_C4.
    void sub_E0800(RwInt32 arg_0);
    // Spreads the crosshair's four arms (items 0x5B to 0x5E) by the player's
    // weapon in hand; arg_0 unused.
    void sub_E08B0(RwReal arg_0);
    // Blends item 0x69 from unk_4B8F34's colour toward unk_4B8F38's by
    // arg_0, and scales it by arg_0.
    void sub_E0A90(RwReal arg_0);
    // Clears the HUD's flags and every list record's unk_14, and hides
    // item 0x88.
    void sub_E0E00();
    // Shows the vehicle arg_4 of kind arg_0 (arg_8 1 moves the items to their
    // second places).
    void sub_E0B60(RwInt32 arg_0, type_3D3548 *arg_4, RwInt32 arg_8);
    // Undoes sub_E0B60.
    void sub_E0CC0();
    // Places item arg_0 at (arg_4, arg_8), the x widened by 4/3 while
    // dword_4CF9A8 is set.
    void sub_E7050(RwInt32 arg_0, RwReal arg_4, RwReal arg_8);
    // The screen point of the world point arg_0 into *arg_4 (pixels, and
    // the depth), through the main camera at the player's field of view.
    void sub_DEC40(RwV3d *arg_0, RwV3d *arg_4);
    // Places item arg_0 at (arg_4, arg_8), unwidened.
    void sub_E6200(RwInt32 arg_0, RwReal arg_4, RwReal arg_8);
    // Sets item arg_0's four corner colours to (arg_4, arg_8, arg_C) and the
    // alpha arg_10.
    void sub_E7200(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C, RwInt32 arg_10);
    // Sets item arg_0's four corner colours.
    void sub_E7270(RwInt32 arg_0, RwRGBA *arg_4, RwRGBA *arg_8, RwRGBA *arg_C, RwRGBA *arg_10);

    // Sets unk_1A020: an inline with no address and so no database name.
    // Evidence: the pause menu's options (sub_18E380) store it through a
    // temporary holding the value, then one holding the HUD.
    RwInt32 get_unk_1A020()
    {
        RwInt32 r = unk_1A020;
        return r;
    }
    void set_unk_1A020(RwInt32 arg_0)
    {
        unk_1A020 = arg_0;
    }
};

// The radar's range (sub_E4030 divides the distances by 100 times it).
#ifdef CODFH_PLAIN
extern RwReal &flt_4B8F30;
#else
extern RwReal flt_4B8F30;
#endif
// The radar's path search: its iterations (flt_4293E4), its tolerance
// (flt_4293E8) and sub_BA450's steps (flt_4293EC, flt_4293F0).
extern RwReal flt_4293E4;
extern RwReal flt_4293E8;
extern RwReal flt_4293EC;
extern RwReal flt_4293F0;

// The objective texts' strings: std::string with an assignment that returns
// itself. Named for its array. Evidence: the HUD's build (sub_E0E90) keeps
// the element it assigns in a `this` copy of its own, which the standard
// operator= (returning assign's result) does not take.
struct type_4B89B0 : std::string
{
    // Empty, declared out of line: folded (/OPT:ICF) into sub_E87E0 with the
    // other string types' default constructors; the HUD texts' initializers
    // call it (config/aliases.txt).
    type_4B89B0();
    type_4B89B0 &operator=(const std::string &arg_0)
    {
        assign(arg_0);
        return *this;
    }
};
// The HUD's localised texts (sub_E0E90 fetches them): the objectives'
// states (unk_4B89B0, by the keys in unk_3D8070; sub_E7D00 shows objectives
// A and B), the spectator's texts, the host wait texts and the scoreboard's
// places (unk_4B8AB0, "1st" to "3rd").
extern type_4B89B0 unk_4B89B0[7];
extern type_4B89B0 unk_4B8990;
extern type_4B89B0 unk_4B8A74;
extern type_4B89B0 unk_4B8A90;
extern std::string unk_4B8AB0[3];
extern type_4B89B0 unk_4B8B04;
extern type_4B89B0 unk_4B8B20;
// The objectives' state keys ("HUD_OBJECTIVEINCOMPLETE" to
// "HUD_OBJECTIVEDESTROYED"; .rdata, the database's aHudObjectivein).
extern const RwChar unk_3D8070[7][0x20];
// The localised text's manager (unk_4FEB0C) is in game/loc.h.
type_1A5EA0 sub_E3970(const RwChar *arg_0, RwInt32 arg_4);
// The spectator's text the HUD shows at item 0x59 when it follows no one
// (sub_DD1C0); only the width is known.
struct type_1CB670 sub_1C5350();

// What dword_4F8054's unk_B0 points at (0x36C bytes, allocated from the
// memory pool sub_1CBC30 gives): the players' names from +0x90. Only the
// widths are known where no comment says more. Its constructor is
// compiler-generated and out of line (its members have constructors).
struct type_4F8054;
struct type_3DA44C;
struct type_1F8560;
// A player: name, address and port (sub_1CFAC0 fills them in for a peer
// joining through the host).
struct type_4F8054_B0_90
{
    RwChar unk_00[0x18];        // the name
    RwUInt8 unk_18[4];          // the address
    RwInt32 unk_1C;
    RwUInt16 unk_20;            // the port
    RwUInt16 unk_22;
};
struct type_4F8054_B0
{
    type_4F8054 *unk_00;        // the game
    RwInt32 unk_04;             // this machine's peer
    RwInt32 unk_08;
    type_1DDE20_mask unk_0C;    // the peers in the game
    RwUInt16 unk_0E;
    RwChar unk_10[0x18];        // the joining player's name
    RwInt32 unk_28;
    RwInt32 unk_2C;             // set: the joining player's details came
    type_1DDE20_mask unk_30;    // the peers waiting to join
    RwUInt16 unk_32;
    RwInt32 unk_34;             // the host's join state
    RwInt32 unk_38;             // the host's join state at the last step
    RwInt32 unk_3C;             // the joining peer (666 for none)
    RwInt32 unk_40;             // the host's join message's handle
    type_1CCA10 unk_44;         // the host's join state's deadline
    type_1DDE20_mask unk_48;    // the peers not yet connected to
    type_1DDE20_mask unk_4A;
    type_1DDE20_mask unk_4C;    // the peers still to be kicked
    RwUInt16 unk_4E;
    RwInt32 unk_50[16];         // the connections, one a peer
    type_4F8054_B0_90 unk_90[16]; // the players
    type_1CCA10 unk_2D0[16];
    RwInt32 unk_310;            // the join state (7 in the state the voice chat also runs in)
    RwInt32 unk_314;            // the join state at the last step
    RwInt32 unk_318;            // the join message's handle
    type_1CCA10 unk_31C;        // the join state's deadline
    type_1CCA10 unk_320;
    type_1DDE20_mask unk_324;   // the peers told to kick someone
    RwUInt16 unk_326;
    RwInt32 unk_328[16];        // their kick notices' handles
    type_1CCA10 unk_368;

    static void *operator new(size_t arg_0)
    {
        return sub_1CBC30()->sub_1F8BF0(arg_0);
    }
    static void operator delete(void *arg_0)
    {
        sub_1CBC30()->sub_1F8C30(arg_0);
    }
    // The peers in the game but this machine. Defined here but not inlined
    // (it is called at sub_1A8050): its callers still reserve its
    // expansion's two slots (docs/toolchain.md).
    type_1DDE20_mask sub_1A8050()
    {
        // A compiled-out check: the registers after it are one load on
        // (docs/toolchain.md).
        if (!unk_04)
        {
        }
        type_1DDE20_mask var_4 = unk_0C;

        if (!var_4.empty())
            var_4.clear(unk_04);
        // A compiled-out check: the registers after it are one load on
        // (docs/toolchain.md).
        if (!unk_04)
        {
        }
        return var_4;
    }
    // This machine's peer (the voice chat compares a talker with it).
    RwInt32 sub_1CFF90();
    // Resets it for the game arg_0; empties it; its step at the time arg_0;
    // and sub_1CD6E0 (the game's slot 26 passes its argument on).
    void sub_1CCC00(type_4F8054 *arg_0);
    void sub_1CCD20();
    void sub_1CFD50(const type_1CCA10 &arg_0);
    void sub_1CD6E0(RwInt32 arg_0);
    void sub_1CD370();
    // The join's step at the time arg_0: sends this machine's details, waits
    // for the ack and the peers' details and connects to each (named by its
    // traces); sub_1CD450 is its connected state, sub_1CFC20 drops peer
    // arg_0.
    void sub_1CCD60(const type_1CCA10 &arg_0);
    // The server's join step at the time arg_0; this machine as peer arg_0
    // of the server; peer arg_0 joining through the host at the address
    // arg_4 and port arg_8; this machine as the server; closes peer arg_0
    // (its trace: "close player"); this machine's peer (0 when none) and
    // whether it has one; tells the host whether this machine reached peer
    // arg_0 (arg_4, its traces: "informing host that we ...").
    void sub_1CD780(const type_1CCA10 &arg_0);
    void sub_1CF750(RwInt32 arg_0);
    void sub_1CFAC0(RwInt32 arg_0, const RwUInt8 *arg_4, RwUInt16 arg_8);
    void sub_1CFB80();
    void sub_1CFC20(RwInt32 arg_0);
    RwInt32 sub_1CFFC0();
    void sub_1CFFF0(RwInt32 arg_0, RwInt32 arg_4);
    // Named by its trace ("handlePossibleDisconnections:: We've lost the
    // server!"): kicks the peers not heard from for 30 seconds.
    void handlePossibleDisconnections();
    // Closes the game (its trace: "cNetGameSessionManagement: Closing
    // game..."); kicks peer arg_0; tells the others to kick peer arg_0.
    void sub_1CD690(RwInt32 arg_0);
    // Named by its traces ("sendPlayerKicks() : ...").
    void sendPlayerKicks(RwInt32 arg_0);
    RwInt32 sub_1CE650(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, type_1F8560 *arg_C, RwInt32 arg_10);
    // An inline accessor for unk_310, with no address and so no database
    // name; named for its field. Evidence: the voice chat's step
    // (sub_1C6350) reads it through a result local.
    // Likewise returning it directly (no database name either). Evidence:
    // the join (type_4F7EB8::sub_1A9CE0) switches on it through a copy of an
    // unwritten slot.
    RwInt32 get_unk_310_direct()
    {
        return unk_310;
    }
    RwInt32 get_unk_310()
    {
        RwInt32 r = unk_310;
        return r;
    }
    // sub_1A8050 inline: the peers in the game but this machine. Evidence:
    // the voice chat's sub_1C7840 computes them in place through a result
    // local and a local for this machine's peer.
    type_1DDE20_mask others()
    {
        type_1DDE20_mask r = unk_0C;
        if (!r.empty())
            r.clear(get_unk_04());
        return r;
    }
    // The same taking the peer out after one compiled-out check (discard),
    // with one more check before the copy out: the vote calls (sub_1C32B0,
    // sub_1C3520) shift with the registers one load on and copy the result
    // one load further (docs/toolchain.md).
    type_1DDE20_mask others_checked()
    {
        type_1DDE20_mask r = unk_0C;
        if (!r.empty())
            r.discard(get_unk_04());
        if (!r.unk_00)
        {
        }
        return r;
    }
    RwInt32 get_unk_04()
    {
        RwInt32 r = unk_04;
        return r;
    }
    // Inline too, named for its field. Evidence: handlePossibleDisconnections
    // (sub_1CD450) reads each through a slot of its own.
    type_1CCA10 get_unk_2D0(RwInt32 arg_0)
    {
        return unk_2D0[arg_0];
    }
    // Inline too, named for their fields. Evidence: the server's join step
    // (sub_1CD780) shifts by unk_3C through a result local and stores its
    // deadlines source first.
    RwInt32 get_unk_3C()
    {
        RwInt32 r = unk_3C;
        return r;
    }
    // The joining peer and this machine's peer again, with compiled-out
    // checks after the read (two, one and two): inlines with no address,
    // named for what they return. Evidence: the server's join step
    // (sub_1CD780) and sendPlayerKicks take them out of a copied mask with
    // the shift loaded that many loads on from the plain getters'
    // (docs/toolchain.md).
    // Whether peer arg_0 is in the game, after two compiled-out checks: an
    // inline with no address, named for what it does. Evidence:
    // handlePossibleDisconnections tests it inside an `||` with its
    // registers four loads on from the test before (docs/toolchain.md).
    RwInt32 in_game(RwInt32 arg_0)
    {
        if (!unk_0C.unk_00)
        {
        }
        if (!unk_0C.unk_00)
        {
        }
        return unk_0C.test(arg_0);
    }
    RwInt32 joiner()
    {
        RwInt32 r = unk_3C;
        if (!unk_3C)
        {
        }
        if (!unk_3C)
        {
        }
        return r;
    }
    RwInt32 self()
    {
        RwInt32 r = unk_08;
        if (!unk_08)
        {
        }
        return r;
    }
    RwInt32 self2()
    {
        RwInt32 r = unk_08;
        if (!unk_08)
        {
        }
        if (!unk_08)
        {
        }
        return r;
    }
    void set_unk_44(const type_1CCA10 &arg_0)
    {
        unk_44 = arg_0;
    }
    // Inline too, named for its field. Evidence: the join step builds each
    // deadline after the literal it adds, then stores it source first.
    void set_unk_31C(const type_1CCA10 &arg_0)
    {
        unk_31C = arg_0;
    }
    // Inline too (the join step shifts by it through a result local).
    RwInt32 get_unk_08()
    {
        RwInt32 r = unk_08;
        return r;
    }
    // The host's peer: unk_08 again, after a compiled-out check
    // (docs/toolchain.md). An inline with no address, named for what it
    // gives. Evidence: the network game's message checks (sNetGameEP.cpp)
    // read it through a result local, the registers one load on.
    RwInt32 host()
    {
        if (!unk_08)
        {
        }
        RwInt32 r = unk_08;
        return r;
    }
    // Inline too, named for its field (the multiplayer manager's sub_1ACA70
    // counts the peers from a copy).
    type_1DDE20_mask get_unk_0C()
    {
        // A compiled-out check (docs/toolchain.md): the copy after it is one
        // load on.
        if (!unk_08)
        {
        }
        return unk_0C;
    }
};

// The network game's two other parts (0x7A0 and 0x6A0 bytes, from the same
// pool): the first (type_1D0100) is in game/netqueue.h, the second has an
// empty destructor (folded by /OPT:ICF into pDtor, 0x1E41C0).
// The join message the players send (a local of their join step): the
// server's name and the session key. Sends it for the game arg_0 to the
// peers arg_4, its handle into arg_8; 0 when sent.
// The kick notice the players send (a local of sub_1CD6E0; its trace
// "Sent playerKickNotification"): sends it for the game arg_0 to the peers
// arg_4, its handle into arg_8; 0 when sent.
struct type_1D7870
{
    RwUInt8 unk_00;

    RwInt32 sub_1D7870(type_4F8054 *arg_0, const type_1DDE20_mask &arg_4, RwInt32 *arg_8);
    // Read back from the stream arg_0 (arg_4 bits); whether it may go from
    // the peer arg_4 to the peers arg_8 of the game arg_0.
    RwInt32 sub_1D7920(type_1F8560 *arg_0, RwInt32 arg_4);
    RwInt32 sub_1D79B0(type_4F8054 *arg_0, RwInt32 arg_4, const type_1DDE20_mask &arg_8);
};
// The player kick the players send (a local of sendPlayerKicks): the
// player's index, name and address. Sends it for the game arg_0 to the
// peers arg_4, its handle into arg_8.
// The server's join messages (locals of sub_1CD780): "please wait", the
// join's start (the peer), the other players' details (their count,
// records, indexes and 12 bytes each from the game's slot 14), a player's
// arrival (index, name, the 12 bytes, address, port and unk_1C) and the
// join's end (the server's name). Each sends itself for the game arg_0 to
// the peers arg_4, its handle into arg_8; 0 when sent.
struct type_1D6020
{
    RwUInt8 unk_00;

    RwInt32 sub_1D6020(type_4F8054 *arg_0, const type_1DDE20_mask &arg_4, RwInt32 *arg_8);
    // Read back from the stream arg_0 (arg_4 bits); whether it may go from
    // the peer arg_4 to the peers arg_8 of the game arg_0.
    RwInt32 sub_1D60D0(type_1F8560 *arg_0, RwInt32 arg_4);
    RwInt32 sub_1D6160(type_4F8054 *arg_0, RwInt32 arg_4, const type_1DDE20_mask &arg_8);
};
struct type_1D5DC0
{
    RwUInt8 unk_00;

    RwInt32 sub_1D5DC0(type_4F8054 *arg_0, const type_1DDE20_mask &arg_4, RwInt32 *arg_8);
    // Read back from the stream arg_0 (arg_4 bits); whether it may go from
    // the peer arg_4 to the peers arg_8 of the game arg_0.
    RwInt32 sub_1D5E80(type_1F8560 *arg_0, RwInt32 arg_4);
    RwInt32 sub_1D5F20(type_4F8054 *arg_0, RwInt32 arg_4, const type_1DDE20_mask &arg_8);
};
struct type_1D6700
{
    RwInt32 unk_00;
    type_4F8054_B0_90 unk_04[16];
    RwUInt8 unk_244[16];
    RwUInt8 unk_254[16][0xC];

    RwInt32 sub_1D6700(type_4F8054 *arg_0, const type_1DDE20_mask &arg_4, RwInt32 *arg_8);
    // Read back from the stream arg_0 (arg_4 bits); whether it may go from
    // the peer arg_4 to the peers arg_8 of the game arg_0.
    RwInt32 sub_1D6920(type_1F8560 *arg_0, RwInt32 arg_4);
    RwInt32 sub_1D6B20(type_4F8054 *arg_0, RwInt32 arg_4, const type_1DDE20_mask &arg_8);
};
struct type_1D6EB0
{
    RwUInt8 unk_00;
    RwChar unk_01[0x18];
    RwUInt8 unk_19[0xC];
    RwUInt8 unk_25[4];
    RwUInt8 unk_29;
    RwUInt16 unk_2A;
    RwInt32 unk_2C;

    RwInt32 sub_1D6EB0(type_4F8054 *arg_0, const type_1DDE20_mask &arg_4, RwInt32 *arg_8);
    // Read back from the stream arg_0 (arg_4 bits); whether it may go from
    // the peer arg_4 to the peers arg_8 of the game arg_0.
    RwInt32 sub_1D7010(type_1F8560 *arg_0, RwInt32 arg_4);
    RwInt32 sub_1D7120(type_4F8054 *arg_0, RwInt32 arg_4, const type_1DDE20_mask &arg_8);
};
struct type_1D6C60
{
    RwChar unk_00[0x18];

    RwInt32 sub_1D6C60(type_4F8054 *arg_0, const type_1DDE20_mask &arg_4, RwInt32 *arg_8);
    // Read back from the stream arg_0 (arg_4 bits); whether it may go from
    // the peer arg_4 to the peers arg_8 of the game arg_0.
    RwInt32 sub_1D6D20(type_1F8560 *arg_0, RwInt32 arg_4);
    RwInt32 sub_1D6DA0(type_4F8054 *arg_0, RwInt32 arg_4, const type_1DDE20_mask &arg_8);
};
struct type_1D7200
{
    RwUInt8 unk_00;
    RwChar unk_01[0x18];
    RwUInt8 unk_19[4];

    RwInt32 sub_1D7200(type_4F8054 *arg_0, const type_1DDE20_mask &arg_4, RwInt32 *arg_8);
    // Read back from the stream arg_0 (arg_4 bits); whether it may go from
    // the peer arg_4 to the peers arg_8 of the game arg_0.
    RwInt32 sub_1D7340(type_1F8560 *arg_0, RwInt32 arg_4);
    RwInt32 sub_1D7420(type_4F8054 *arg_0, RwInt32 arg_4, const type_1DDE20_mask &arg_8);
};
// The connection report the players send the host (a local of
// sub_1CFFF0): the peer and whether this machine reached it.
struct type_1D6480
{
    RwUInt8 unk_00;
    RwInt32 unk_04;

    RwInt32 sub_1D6480(type_4F8054 *arg_0, const type_1DDE20_mask &arg_4, RwInt32 *arg_8);
    // Read back from the stream arg_0 (arg_4 bits); whether it may go from
    // the peer arg_4 to the peers arg_8 of the game arg_0.
    RwInt32 sub_1D6550(type_1F8560 *arg_0, RwInt32 arg_4);
    RwInt32 sub_1D65C0(type_4F8054 *arg_0, RwInt32 arg_4, const type_1DDE20_mask &arg_8);
};
struct type_1D6230
{
    RwChar unk_00[0x18];
    RwInt32 unk_18;

    RwInt32 sub_1D6230(type_4F8054 *arg_0, const type_1DDE20_mask &arg_4, RwInt32 *arg_8);
    // Read back from the stream arg_0 (arg_4 bits); whether it may go from
    // the peer arg_4 to the peers arg_8 of the game arg_0.
    RwInt32 sub_1D62F0(type_1F8560 *arg_0, RwInt32 arg_4);
    RwInt32 sub_1D6370(type_4F8054 *arg_0, RwInt32 arg_4, const type_1DDE20_mask &arg_8);
};

// A ping's packet (a local of the time keeper's): the time it was sent
// and the time the peer answered it (0 while a request). Sent to the peers
// arg_4 of the game arg_0, its handle into arg_8 (sub_1D7560), and read
// from the stream arg_0 (sub_1D7650, 0 on an error).
struct type_1D7560
{
    type_1CCA10 unk_00;
    type_1CCA10 unk_04;

    RwInt32 sub_1D7560(type_4F8054 *arg_0, const type_1DDE20_mask &arg_4, RwInt32 *arg_8);
    RwInt32 sub_1D7650(type_1F8560 *arg_0, RwInt32 arg_4);
    // Inline setters with no addresses, named for their fields. Evidence:
    // the ping's read (sub_1D7650) builds each time in a slot of its own
    // and stores it with `this` loaded first, as a by-value parameter gives.
    void set_unk_00(type_1CCA10 arg_0)
    {
        unk_00 = arg_0;
    }
    void set_unk_04(type_1CCA10 arg_0)
    {
        unk_04 = arg_0;
    }
    // Whether it may go to the peers arg_4: always (an empty check whose
    // body /OPT:ICF folds into sub_18F420's, config/aliases.txt).
    RwInt32 sub_18F420(type_4F8054 *arg_0, const type_1DDE20_mask &arg_4);
};
// Two messages read back in sNetGameEP.cpp whose senders are elsewhere: a
// peer and a name (sub_1D7760, message 10), and a name (sub_1D77F0,
// message 11). Each is read from the stream arg_0 (arg_4 bits).
struct type_1D7760
{
    RwUInt8 unk_00;
    RwChar unk_01[0x18];

    RwInt32 sub_1D7760(type_1F8560 *arg_0, RwInt32 arg_4);
};
struct type_1D77F0
{
    RwChar unk_00[0x18];

    RwInt32 sub_1D77F0(type_1F8560 *arg_0, RwInt32 arg_4);
};
// A ping's record: when it was sent, the peer's time in its answer and
// the round trip.
struct cTimeKeeper_0C
{
    type_1CCA10 unk_00;
    type_1CCA10 unk_04;
    type_1CCA10 unk_08;
};
// cTimeKeeper (named by its trace, "KNET: cTimeKeeper() - Packet sent back
// to us, which we don't remember sending..."): the network game's third
// part (0x6A0 bytes). It pings the peers four at a time every 600
// milliseconds, keeps each peer's last eight pings, and from them each
// peer's latency (half the round trip) and clock offset.
struct cTimeKeeper
{
    type_4F8054 *unk_00;        // the network game
    type_1CCA10 unk_04;         // when the last pings went out
    RwUInt32 unk_08;            // the next peer to ping
    cTimeKeeper_0C unk_0C[16][8];
    RwUInt8 unk_60C[16];        // each peer's next record
    type_1CCA10 unk_61C[16];    // each peer's latency
    RwInt32 unk_65C[16];        // each peer's clock offset
    type_1DDE20_mask unk_69C;   // the peers joined since the last pings

    cTimeKeeper();
    ~cTimeKeeper();
    // Peer arg_0's latency by value, after a compiled-out check: an inline
    // with no address, named for its field. Evidence: the log's debug
    // display (sub_1B00F0) copies it into a slot of its own before reading
    // it, a register load on.
    type_1CCA10 get_unk_61C(RwInt32 arg_0)
    {
        if (!unk_61C)
        {
        }
        return unk_61C[arg_0];
    }
    static void *operator new(size_t arg_0)
    {
        return sub_1CBC30()->sub_1F8BF0(arg_0);
    }
    static void operator delete(void *arg_0)
    {
        sub_1CBC30()->sub_1F8C30(arg_0);
    }
    // Starts it for the game arg_0; its step.
    void sub_1D4B80(type_4F8054 *arg_0);
    void sub_1D4CA0();
    // Drops peer arg_0 (the players' sub_1CFC20).
    void sub_1D4C00(RwInt32 arg_0);
    // Peer arg_0 has joined (the server's join step).
    void sub_1D4C60(RwInt32 arg_0);
    // A ping (message 7) from peer arg_8 in the stream arg_C: answered, or
    // its record completed; 0 when not a ping or unreadable.
    RwInt32 sub_1D5010(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, type_1F8560 *arg_C, RwInt32 arg_10);
    // Empty in this build (folded by /OPT:ICF into pDtor, 0x1E41C0).
    void pDtor();
};
typedef RwChar cTimeKeeper_size_check[sizeof(cTimeKeeper) == 0x6A0 ? 1 : -1];

// What createServer takes: the server's name, its settings and the map.
struct type_1CC1F0
{
    const RwChar *unk_00;       // the server's name
    RwUInt8 unk_04;
    RwUInt8 unk_05[4];
    RwUInt8 unk_09;
    RwUInt16 unk_0A;
    const RwChar *unk_0C;       // the game's name
    RwUInt8 unk_10;             // the map
    RwUInt8 unk_11;
    RwUInt8 unk_12;
    RwUInt8 unk_13;
    RwUInt8 unk_14;
    RwUInt8 unk_15;
    RwUInt8 unk_16;
};
// What joinServer takes from the server found: its address, its port, its
// name and its settings.
struct type_1CC3C0
{
    RwUInt8 unk_00[4];
    RwUInt8 unk_04[4];
    RwUInt16 unk_08;
    RwUInt8 unk_0A[6];
    RwChar unk_10[0x18];
    RwUInt8 unk_28;
    RwUInt8 unk_29;
    RwUInt8 unk_2A;
    RwUInt8 unk_2B;
    RwUInt8 unk_2C;
    RwUInt8 unk_2D;
    RwUInt8 unk_2E;
};

// The network game's server settings (0x30 bytes; all -1 when none).
struct type_4F8054_4C
{
    RwInt32 unk_00[4];
    RwInt32 unk_10;
    RwInt32 unk_14;
    RwInt32 unk_18;
    RwUInt8 unk_1C;
    RwUInt8 unk_1D[0xF];
    RwInt32 unk_2C;
};

// The session description (0x34 bytes, at the network game's +0x18) as a
// whole: its size, the game's name, and its settings (unk_2B the most
// players).
struct type_4F8054_18
{
    RwUInt32 unk_00;
    RwChar unk_04[0x18];
    RwUInt8 unk_1C[4];
    RwUInt16 unk_20;
    RwUInt16 unk_22;
    RwInt32 unk_24;
    RwUInt8 unk_28;
    RwUInt8 unk_29;
    RwUInt8 unk_2A;
    RwUInt8 unk_2B;
    RwUInt8 unk_2C;
    RwUInt8 unk_2D;
    RwUInt16 unk_2E;
    RwInt32 unk_30;
};

// The network game (dword_4F8054): cNetGame, named by its traces
// ("cNetGame::createServer", "cNetGame::joinServer",
// "cNetGame::deinitialise"). Abstract (19 pure virtuals, slots 4 to 22).
struct type_4F8054
{
    virtual ~type_4F8054();
    // Resets it; takes the session down; its step at the time arg_0.
    virtual void vf_004();
    virtual void vf_008();
    virtual void vf_00C(const type_1CCA10 &arg_0);
    // The game's name (for the session key).
    virtual const RwChar *vf_010() = 0;
    // Whether peer arg_0 may join (the server's join step).
    virtual RwInt32 vf_014(RwInt32 arg_0) = 0;
    // Whether peer arg_0 is connected (the players' join step waits on it).
    virtual RwInt32 vf_018(RwInt32 arg_0) = 0;
    // The platform's hooks (the Xbox side's, types/cXboxLiveNetGame.h,
    // give their widths); only the widths are known.
    virtual RwInt32 vf_01C(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C, RwInt32 arg_10) = 0;
    virtual RwInt32 vf_020(RwInt32 arg_0, RwInt32 arg_4) = 0;
    virtual RwInt32 vf_024(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8) = 0;
    virtual RwInt32 vf_028(RwInt32 arg_0) = 0;
    virtual void vf_02C(RwInt32 arg_0, RwInt32 arg_4) = 0;
    // Peer arg_0 has left (the players' sub_1CFC20).
    virtual void vf_030(RwInt32 arg_0) = 0;
    virtual void vf_034(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8) = 0;
    // Peer arg_0's arg_8 bytes of platform data into arg_4.
    virtual void vf_038(RwInt32 arg_0, RwUInt8 *arg_4, RwInt32 arg_8) = 0;
    virtual RwInt32 vf_03C() = 0;
    virtual RwInt32 vf_040(RwInt32 arg_0) = 0;
    virtual void vf_044(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C, RwInt32 arg_10) = 0;
    virtual RwInt32 vf_048(RwInt32 arg_0, RwInt32 arg_4) = 0;
    // Drops the peers arg_0.
    virtual void vf_04C(const type_1DDE20_mask &arg_0) = 0;
    virtual RwInt32 vf_050() = 0;
    virtual void vf_054(RwInt32 arg_0) = 0;
    virtual void vf_058(RwInt32 arg_0) = 0;
    // createServer and joinServer (named by their traces), the game's
    // options and the rest.
    virtual void vf_05C(const type_1CC1F0 *arg_0);
    virtual void vf_060(const type_1CC1F0 *arg_0, const type_1CC3C0 *arg_4, RwInt32 arg_8);
    virtual void vf_064(RwUInt8 arg_0, RwUInt8 arg_4, RwUInt8 arg_8, RwUInt8 arg_C, RwUInt8 arg_10);
    virtual void vf_068(RwInt32 arg_0);
    // Inline: the constructor's vtable emits them after it, before ??_G (the image's order).
    virtual RwInt32 vf_06C()
    {
        if (unk_3C)
            return 0;
        return 1;
    }
    virtual void vf_070(const type_1CC1F0 *arg_0, const type_4F8054_4C *arg_4, RwInt32 arg_8, RwInt32 arg_C);
    // Inline, their bodies shared with other classes' (/OPT:ICF): 1, 0,
    // nothing, nothing.
    virtual RwInt32 vf_074()
    {
        return 1;
    }
    virtual RwInt32 vf_078(RwInt32 arg_0)
    {
        return 0;
    }
    virtual void vf_07C()
    {
    }
    virtual void vf_080(RwInt32 arg_0, RwInt32 arg_4)
    {
    }
    virtual void vf_084(RwInt32 arg_0, RwInt32 arg_4)
    {
    }

    RwInt32 unk_04;             // the session's state (2 and 5 run the voice chat)
    RwInt32 unk_08;             // the state at the last step
    RwInt32 unk_0C;
    RwInt32 unk_10;             // set: no steps
    RwInt32 unk_14;
    RwUInt32 unk_18;            // the session description's size (0x34)
                                // (type_4F8054_18 views it)
    RwChar unk_1C[0x18];        // the game's name
    RwUInt8 unk_34[4];
    RwUInt16 unk_38;
    RwUInt16 unk_3A;
    RwInt32 unk_3C;
    RwUInt8 unk_40;             // the map
    RwUInt8 unk_41;
    RwUInt8 unk_42;
    RwUInt8 unk_43;
    RwUInt8 unk_44;
    RwUInt8 unk_45;
    RwUInt16 unk_46;
    RwInt32 unk_48;
    type_4F8054_4C unk_4C;
    type_1CCA10 unk_7C;         // the session's time
    RwChar unk_80[0x18];        // the server's name
    RwUInt8 unk_98[4];
    RwUInt16 unk_9C;
    RwUInt16 unk_9E;
    type_4F8054_A0 *unk_A0;     // told of peers joining and leaving
    type_4F8054_A4 *unk_A4;     // told of messages
    type_4F8054_A8 *unk_A8;     // told when joining fails
    type_1D0100 *unk_AC;
    type_4F8054_B0 *unk_B0;
    cTimeKeeper *unk_B4;
    RwInt32 unk_B8;
    RwInt32 unk_BC;
    type_1CCA10 unk_C0;
    type_1CCA10 unk_C4;
    RwInt32 unk_C8;
    RwInt32 unk_CC;

    type_4F8054();
    // Opens it on port arg_0 (the multiplayer manager's set-up, 0x3F9);
    // only the width is known.
    void sub_1D5BB0(RwInt32 arg_0);
    static void *operator new(size_t arg_0)
    {
        return sub_1CBC30()->sub_1F8BF0(arg_0);
    }
    static void operator delete(void *arg_0)
    {
        sub_1CBC30()->sub_1F8C30(arg_0);
    }
    // Takes the session down and resets it.
    void sub_1CC120();
    // Sends the message arg_4 to the peers arg_0 (arg_8 passed on), with
    // five different delivery kinds; 0 when there are no peers.
    RwInt32 sub_1CC5F0(const type_1DDE20_mask &arg_0, type_1F8560 *arg_4, RwInt32 arg_8);
    RwInt32 sub_1CC640(const type_1DDE20_mask &arg_0, type_1F8560 *arg_4, RwInt32 arg_8);
    RwInt32 sub_1CC690(const type_1DDE20_mask &arg_0, type_1F8560 *arg_4, RwInt32 arg_8);
    RwInt32 sub_1CC6E0(const type_1DDE20_mask &arg_0, type_1F8560 *arg_4, RwInt32 arg_8);
    RwInt32 sub_1CC730(const type_1DDE20_mask &arg_0, type_1F8560 *arg_4, RwInt32 arg_8);
    // Tells the peer listener of a peer joining and leaving.
    void sub_1CC780(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C);
    void sub_1CC7D0(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C);
    // Hands the message in the stream arg_8 (its kind read ahead) to the
    // third part, else to the players.
    void sub_1CC820(RwInt32 arg_0, RwInt32 arg_4, type_1F8560 *arg_8, RwInt32 arg_C);
    // Tells the message listener.
    void sub_1CC8A0(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C, RwInt32 arg_10);
    // Sets the error arg_0 (arg_4 with it); the packet engine's failure;
    // the error arg_0's name. Named by their traces
    // ("cNetGame::setError(%d : %s)", "packetEngineHasRunOutOfRam - has
    // been called... Panic!", "Error condition missing from
    // errorToString()").
    void setError(RwInt32 arg_0, RwInt32 arg_4);
    void packetEngineHasRunOutOfRam();
    const RwChar *errorToString(RwInt32 arg_0);
    // Empties the players and restarts.
    void sub_1CCB10();
    // The session key: the game's name hashed with the time (666 for 0).
    RwInt32 sub_1CCB40();
    // Inline accessors with no address and so no database names, named for
    // their fields. Evidence: the voice chat (sub_1C6350, sub_1C6700) reads
    // each through a result local, the time through a `this` copy too; the
    // step (sub_1CC540) reads unk_10 through one.
    RwInt32 get_unk_04()
    {
        RwInt32 r = unk_04;
        return r;
    }
    RwInt32 get_unk_10()
    {
        RwInt32 r = unk_10;
        return r;
    }
    // An inline accessor for unk_14 (the reason a session ended), with no
    // address and so no database name; named for its field. Evidence: the
    // join (type_4F7EB8::sub_1A9CE0) reads it through a slot of its own.
    RwInt32 get_unk_14()
    {
        RwInt32 r = unk_14;
        return r;
    }
    RwInt32 get_unk_B8()
    {
        RwInt32 r = unk_B8;
        return r;
    }
    type_1CCA10 get_unk_7C()
    {
        return unk_7C;
    }

    // An inline accessor with no address and so no database name, named for
    // its field. Evidence: the scoreboard (sub_E7EF0) reads unk_B0 through a
    // `this` copy and a result of their own.
    type_4F8054_B0 *get_unk_B0()
    {
        type_4F8054_B0 *r = unk_B0;
        return r;
    }
    // The same after a compiled-out check (docs/toolchain.md). Evidence: the
    // vote calls (sub_1C32B0, sub_1C3520) copy the players' mask one load on.
    type_4F8054_B0 *get_unk_B0_checked()
    {
        type_4F8054_B0 *r = unk_B0;
        if (!unk_B0)
        {
        }
        return r;
    }
    // Inline too, with no addresses; named for their fields. Evidence: the
    // players' join step (sub_1CCD60) reads unk_AC through a slot of its
    // own, and unk_A8 through one and a dead return slot.
    type_4F8054_A8 *get_unk_A8()
    {
        return unk_A8;
    }
    // The session description as a whole: an inline with no address, named
    // for what it gives. Evidence: cXboxLive's join request handling
    // (sub_1DA6D0) keeps its address in a slot of its own.
    type_4F8054_18 *get_desc()
    {
        return (type_4F8054_18 *)&unk_18;
    }
    type_1D0100 *get_unk_AC()
    {
        return unk_AC;
    }
    cTimeKeeper *get_unk_B4()
    {
        return unk_B4;
    }
    static type_4F8054 *get();
};
#ifdef CODFH_PLAIN
// (plain builds: a field of the multiplayer manager unk_4F7EB8; see unit_1A8B20)
extern type_4F8054 *&dword_4F8054;
#else
extern type_4F8054 *dword_4F8054;
#endif
inline type_4F8054 *type_4F8054::get()
{
    type_4F8054 *r = dword_4F8054;
    return r;
}

// The two ends of item 0x69's colour (sub_E0A90).
#ifdef CODFH_PLAIN
extern RwRGBA &unk_4B8F34;
#else
extern RwRGBA unk_4B8F34;
#endif
#ifdef CODFH_PLAIN
extern RwRGBA &unk_4B8F38;
#else
extern RwRGBA unk_4B8F38;
#endif

// Reads the texture dictionary at the path arg_0 (as sub_DC000 does).
RwTexDictionary *sub_E8320(const RwChar *arg_0);
// Destroys the dictionary arg_0 when there is one.
void sub_E83D0(RwTexDictionary *arg_0);
// Lists of item indices, each ending with -1 (one list; .data).
extern RwInt32 *dword_4293D0[];

// A toggle of dword_4CF9A8 the HUD's frame takes once (sub_DD180).
extern bool byte_4B8975;
#ifdef CODFH_PLAIN
extern RwInt32 &dword_4CF9A8;
#else
extern RwInt32 dword_4CF9A8;
#endif
extern RwReal flt_4B8984;
// The time the damage markers are stamped with (sub_DFB40); the shell's
// command 100 sets it, times 1000.
#ifdef CODFH_PLAIN
extern RwReal &dword_4B9154;
#else
extern RwReal dword_4B9154;
#endif
// Hands the HUD font arg_0 to the game's text (sub_E52B0); only the width
// is known.
void sub_186970(type_DA580 *arg_0);
// Springs *arg_0 toward arg_4 with the velocity *arg_8 (arg_C, arg_10 and
// arg_14 its settings) over the time arg_18; only the widths are known.
void sub_112DA0(RwReal *arg_0, RwReal arg_4, RwReal *arg_8, RwReal arg_C, RwReal arg_10, RwReal arg_14,
                RwReal arg_18);
// The subtitles' box (its place), their two colours and the rate they
// scroll at, and the flags the HUD's drawing reads or sets (sub_E5480).
#ifdef CODFH_PLAIN
extern RwV2d &dword_4B8F88;
#else
extern RwV2d dword_4B8F88;
#endif
#ifdef CODFH_PLAIN
extern RwRGBA &dword_4B8F98;
#else
extern RwRGBA dword_4B8F98;
#endif
#ifdef CODFH_PLAIN
extern RwRGBA &dword_4B8F9C;
#else
extern RwRGBA dword_4B8F9C;
#endif
#ifdef CODFH_PLAIN
extern RwReal &dword_4B8FA0;
#else
extern RwReal dword_4B8FA0;
#endif
extern RwInt32 dword_4B897C;
extern RwInt32 dword_4B8980;
extern RwReal flt_4293D8;
// The language (sub_19B0A0) and the text converters for languages 1 and 2
// (nonzero when arg_0 was converted into arg_4); only the widths are known.
RwInt32 sub_19B0A0();
RwInt32 sub_19BC70(RwChar *arg_0, RwChar *arg_4);
RwInt32 sub_19BCB0(const RwChar *arg_0, RwChar *arg_4);
// Whether the HUD draws (sub_DF000), and the height above the head bone its
// name labels sit at.
extern RwInt32 dword_42926C;
#ifdef CODFH_PLAIN
extern RwReal &dword_4B9158;
#else
extern RwReal dword_4B9158;
#endif
// Transforms the arg_8 points arg_4 by the matrix arg_C into arg_0; only
// the widths are known.
RwV3d *sub_141590(RwV3d *arg_0, RwV3d *arg_4, RwInt32 arg_8, RwMatrix *arg_C);
// The angle between the directions arg_0 and arg_4 (degrees).
RwReal sub_141240(RwV3d *arg_0, RwV3d *arg_4);
// The z axis {0, 0, 1} the items turn about (sub_E6270; .rdata).
extern const RwV3d unk_3D805C;
// The widescreen text offset (sub_E8220; .data).
extern RwReal flt_4293C4;
// How far the items off centre move out in widescreen (sub_E6610; .data).
extern RwReal flt_4293C0;

// Clears item 2's scroll time: a free inline with no address and so no
// database name. Evidence: the basic sound's play (sub_193170) stores it
// through a temporary holding the HUD.
#ifdef CODFH_PLAIN
extern type_DC400 *&dword_4B9190;
#else
extern type_DC400 *dword_4B9190;
#endif
inline void clear_hud_unk_1A160()
{
    type_DC400 *h = dword_4B9190;
    h->unk_1A160 = 0;
}
#ifndef CODFH_SP // MP only: single player's HUD has no unk_90
// The same for the HUD's unk_90 (its letterbox bars) set to 1: no address,
// so no database name; named for the field it sets. Evidence: the
// multiplayer manager's view changes (sub_1AB440) store through a
// temporary holding the HUD each time.
inline void set_hud_unk_90()
{
    type_DC400 *h = dword_4B9190;
    h->unk_90 = 1;
}
// The same clearing it (the local respawn, type_4F7EB8::sub_1ABE30).
inline void clear_hud_unk_90()
{
    type_DC400 *h = dword_4B9190;
    h->unk_90 = 0;
}
#endif

// Settings the shell's commands set (CShellBehaviorClass::HandleAttributes,
// sub_B0980), by the kind of value each command hands over: the HUD's and
// the front end's colours, places and sizes, and named variables' keys.
struct type_3DF8D8_04;
#ifdef CODFH_PLAIN
extern RwReal &flt_4B8F0C;
#else
extern RwReal flt_4B8F0C;
#endif
#ifdef CODFH_PLAIN
extern RwReal &flt_4B8F10;
#else
extern RwReal flt_4B8F10;
#endif
#ifdef CODFH_PLAIN
extern RwRGBA &dword_4B8F20;
#else
extern RwRGBA dword_4B8F20;
#endif
#ifdef CODFH_PLAIN
extern RwRGBA &dword_4B8F24;
#else
extern RwRGBA dword_4B8F24;
#endif
#ifdef CODFH_PLAIN
extern RwInt32 &dword_4B8F3C;
#else
extern RwInt32 dword_4B8F3C;
#endif
#ifdef CODFH_PLAIN
extern RwInt32 &dword_4B8F40;
#else
extern RwInt32 dword_4B8F40;
#endif
#ifdef CODFH_PLAIN
extern RwRGBA &dword_4B8F44;
#else
extern RwRGBA dword_4B8F44;
#endif
#ifdef CODFH_PLAIN
extern RwRGBA &dword_4B8F48;
#else
extern RwRGBA dword_4B8F48;
#endif
#ifdef CODFH_PLAIN
extern RwRGBA &dword_4B8F4C;
#else
extern RwRGBA dword_4B8F4C;
#endif
#ifdef CODFH_PLAIN
extern RwRGBA &dword_4B8F50;
#else
extern RwRGBA dword_4B8F50;
#endif
#ifdef CODFH_PLAIN
extern RwV2d &dword_4B8F54;
#else
extern RwV2d dword_4B8F54;
#endif
#ifdef CODFH_PLAIN
extern RwInt32 &dword_4B8F5C;
#elif defined(CODFH_SP) // a float in single player (SP 0x3B58AC: fcomp and fdiv in SP 0xACDB0, 0xA81E0)
extern RwReal dword_4B8F5C;
#else
extern RwInt32 dword_4B8F5C;
#endif
#ifdef CODFH_PLAIN
extern RwInt32 &dword_4B8F60;
#elif defined(CODFH_SP) // a float in single player (SP 0x3B58B0: fld and fmul in SP 0xA81E0)
extern RwReal dword_4B8F60;
#else
extern RwInt32 dword_4B8F60;
#endif
#ifdef CODFH_PLAIN
extern RwReal &flt_4B8F7C;
#else
extern RwReal flt_4B8F7C;
#endif
struct type_3DF8D8_04_data;
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &unk_4B8F90;
#else
extern type_3DF8D8_04_data unk_4B8F90;
#endif
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &unk_4B8FF4;
#else
extern type_3DF8D8_04_data unk_4B8FF4;
#endif
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &unk_4B8FFC;
#else
extern type_3DF8D8_04_data unk_4B8FFC;
#endif
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &unk_4B9004;
#else
extern type_3DF8D8_04_data unk_4B9004;
#endif
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &unk_4B900C;
#else
extern type_3DF8D8_04_data unk_4B900C;
#endif
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &unk_4B9014;
#else
extern type_3DF8D8_04_data unk_4B9014;
#endif
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &unk_4B901C;
#else
extern type_3DF8D8_04_data unk_4B901C;
#endif
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &unk_4B9024;
#else
extern type_3DF8D8_04_data unk_4B9024;
#endif
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &unk_4B902C;
#else
extern type_3DF8D8_04_data unk_4B902C;
#endif
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &unk_4B9034;
#else
extern type_3DF8D8_04_data unk_4B9034;
#endif
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &unk_4B903C;
#else
extern type_3DF8D8_04_data unk_4B903C;
#endif
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &unk_4B9044;
#else
extern type_3DF8D8_04_data unk_4B9044;
#endif
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &unk_4B904C;
#else
extern type_3DF8D8_04_data unk_4B904C;
#endif
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &unk_4B908C;
#else
extern type_3DF8D8_04_data unk_4B908C;
#endif
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &unk_4B9094;
#else
extern type_3DF8D8_04_data unk_4B9094;
#endif
#ifdef CODFH_PLAIN
extern RwReal &flt_4B915C;
#else
extern RwReal flt_4B915C;
#endif
#ifdef CODFH_PLAIN
extern RwReal &flt_4B9160;
#else
extern RwReal flt_4B9160;
#endif
#ifdef CODFH_PLAIN
extern RwReal &flt_4B9164;
#else
extern RwReal flt_4B9164;
#endif
#ifdef CODFH_PLAIN
extern RwReal &flt_4B9168;
#else
extern RwReal flt_4B9168;
#endif
#ifdef CODFH_PLAIN
extern RwInt32 &dword_4B916C;
#else
extern RwInt32 dword_4B916C;
#endif
#ifdef CODFH_PLAIN
extern RwInt32 &dword_4B9170;
#else
extern RwInt32 dword_4B9170;
#endif
#ifdef CODFH_PLAIN
extern RwV2d &dword_4B9174;
#else
extern RwV2d dword_4B9174;
#endif
#ifdef CODFH_PLAIN
extern RwRGBAReal &unk_4B917C;
#else
extern RwRGBAReal unk_4B917C;
#endif
// The HUD's update (sub_DD1C0): the network game's layout scale of item
// 0x50 (flt_4293F8, flt_4293FC), the console's message time (flt_4B8B3C),
// the items' faded alphas (flt_4B8F14 out, flt_4B8F18 in) and fade time
// (dword_4B8F1C), and the words it picks item 0x58's text and unk_94 by.
extern RwReal flt_4293F8;
extern RwReal flt_4293FC;
extern RwReal flt_4B8B3C;
#ifdef CODFH_PLAIN
extern RwReal &flt_4B8F18;
#else
extern RwReal flt_4B8F18;
#endif
#ifdef CODFH_PLAIN
extern RwReal &dword_4B8F1C;
#else
extern RwReal dword_4B8F1C;
#endif
#ifdef CODFH_PLAIN
extern RwInt32 &dword_4F62FC;
#else
extern RwInt32 dword_4F62FC;
#endif
#ifdef CODFH_PLAIN
// (plain builds: a field of the multiplayer manager unk_4F7EB8; see unit_1A8B20)
extern RwInt32 &dword_4F80E8;
#else
extern RwInt32 dword_4F80E8;
#endif

#endif
