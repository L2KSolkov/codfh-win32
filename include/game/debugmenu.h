/*
 * The debug menu (unk_4E73A8, unit_183130): a tree of named groups and
 * items built at start-up (sub_183130: "Renderer Switching", "Game
 * Settings", "Cheats", "Debug Switches"), each item pointing at the
 * variable it shows. Every name and node comes from the RenderWare heap
 * (dword_520214, hint 0x3425C), its bytes counted in unk_18.
 */
#ifndef GAME_DEBUGMENU_H
#define GAME_DEBUGMENU_H

#include "rw/ostypes.h"

typedef struct RwCamera RwCamera;
struct type_4E73A8_14;

// An item (0x18 bytes): its kind (0 a group, 1 an integer, 2 a switch, 7 a
// float), its name, and the variable (or, for a group, the group) it
// shows; linked in its group.
struct type_4E73A8_18
{
    union
    {
        struct
        {
            RwUInt32 unk_00_b : 32; // its kind, as the builders assign it (a
        };                          // bitfield: by masking)
        RwUInt32 unk_00;            // its kind (the low 14 bits), 0x4000 set
    };                              // when it cannot be changed, and 0x8000
    RwChar *unk_04;             // its name
    union
    {
        RwInt32 unk_08;
        const RwChar *unk_08_s; // its help text (sub_184910)
    };
    union
    {
        void *unk_0C;           // its variable, or its group
        RwUInt8 *unk_0C_b;      // (kind 14: a byte)
    };
    type_4E73A8_18 *unk_10;     // the next in its group
    type_4E73A8_18 *unk_14;     // and the previous
};

// A group (0x14 bytes): its name, how many items it has, its first and last
// items, and the group it is in.
struct type_4E73A8_14
{
    RwChar *unk_00;
    RwInt32 unk_04;
    type_4E73A8_18 *unk_08;
    type_4E73A8_18 *unk_0C;
    type_4E73A8_14 *unk_10;
};

struct type_4E73A8
{
    RwUInt8 unk_00;             // its text colour, blue, green, red and
    RwUInt8 unk_01;             // alpha (yellow: the constructor,
    RwUInt8 unk_02;             // sub_184CC0)
    RwUInt8 unk_03;
    struct type_DA580 *unk_04;  // the font it draws with (the HUD's)
    type_4E73A8_14 *unk_08;     // the root group (off_42A4D4)
    type_4E73A8_14 *unk_0C;     // the group shown
    type_4E73A8_18 *unk_10;     // and its item selected
    RwInt32 unk_14;
    RwInt32 unk_18;             // the bytes it has taken from the heap
    struct Rt2dBrush *unk_1C;   // its brush and camera while it draws
    RwCamera *unk_20;           // (sub_183FD0 to sub_1840C0)
    RwInt32 unk_24;             // the render states it changes while it
    RwInt32 unk_28;             // draws, kept by sub_184760 and put back
    RwInt32 unk_2C;             // by sub_184870
    RwInt32 unk_30;
    RwInt32 unk_34;
    RwInt32 unk_38;
    RwInt32 unk_3C;
    RwInt32 unk_40;

    // Inline: its dynamic initializer (0x30BF80) calls sub_184CC0 on it.
    type_4E73A8()
    {
        sub_184CC0();
    }
    void sub_184CC0();

    // Draws it for the camera arg_0 (the main render, sub_125F20, when not
    // told to skip the HUD).
    void sub_184100(RwCamera *arg_0);
    // Builds the menu (the game loop's set-up), frees it (its shut-down),
    // and runs it each frame.
    void sub_183130();
    void sub_1833D0();
    void sub_183840();
    // A new group named arg_4 in the group arg_0 (the root for 0).
    type_4E73A8_14 *sub_183440(type_4E73A8_14 *arg_0, const RwChar *arg_4);
    // A new item named arg_4 showing the variable arg_8 of the kind arg_C
    // in the group arg_0 (the root for 0); sub_183700 also takes unk_08.
    type_4E73A8_18 *sub_183610(type_4E73A8_14 *arg_0, const RwChar *arg_4, void *arg_8, RwInt32 arg_C);
    // Frees the group arg_0's items and groups (and it, unless the root).
    void sub_183640(type_4E73A8_14 *arg_0);
    // Starts drawing on the main camera (0 without one): a white brush, the
    // HUD's font and a unit square; and ends it.
    RwInt32 sub_183FD0();
    void sub_1840C0();
    // Set before and after it draws (only the widths are known).
    void sub_184760();
    void sub_184870();
    // Draws the help text arg_0 (an item's) at the right, wrapped.
    void sub_184910(const RwChar *arg_0);
    // Wraps the text arg_0 within arg_10 at (*arg_8, *arg_C): its size into
    // them (arg_4 0), or drawn (arg_4 1).
    void sub_1849C0(const RwChar *arg_0, RwInt32 arg_4, RwInt32 *arg_8, RwInt32 *arg_C, RwInt32 arg_10);
    // Draws the text arg_0 at (arg_4, arg_8).
    void sub_184C50(const RwChar *arg_0, RwInt32 arg_4, RwInt32 arg_8);
    type_4E73A8_18 *sub_183700(type_4E73A8_14 *arg_0, const RwChar *arg_4, void *arg_8, RwInt32 arg_C,
                               RwInt32 arg_10);
};
typedef RwChar type_4E73A8_size_check[sizeof(type_4E73A8) == 0x44 ? 1 : -1];
extern type_4E73A8 unk_4E73A8;

// A group of the profiler's render timers (0x18 bytes, in .data at
// dword_42A4F0, ended by -1): its name ("General Types", ...) and its group
// in the performance menu, made on first use.
struct type_42A4F0
{
    RwInt32 unk_00;
    RwChar unk_04[0x10];
    type_4E73A8_14 *unk_14;
};
extern type_42A4F0 dword_42A4F0[];

// A render timer (0x4C bytes, in .data at dword_42A598, ended by -1; the
// profiler keeps its unk_20 and unk_44): its group, its name, this
// frame's time, and what the performance display keeps of it.
struct type_42A598
{
    RwInt32 unk_00;             // its group (dword_42A4F0), -1 at the end
    RwChar unk_04[0x1C];        // its name
    RwInt32 unk_20;             // this frame's time (then its share of 180)
    RwInt32 unk_24;             // the last frame's
    RwReal unk_28;              // the most seen
    RwReal unk_2C;              // the sum, over
    RwInt32 unk_30;             // this many frames
    RwUInt8 unk_34[0x4];
    RwInt32 unk_38;             // set to reset it
    RwInt32 unk_3C;             // its graph's colour (0xBBGGRR)
    RwInt32 unk_40;             // its graph shown (a switch in the menu)
    RwInt32 unk_44;             // how deep it is open
    RwInt32 unk_48;             // its label's percentage offset
};
typedef RwChar type_42A598_size_check[sizeof(type_42A598) == 0x4C ? 1 : -1];
extern type_42A598 dword_42A598[];

// The performance display (dword_4E73F0): the render timers as text and
// graphs, its switches in the debug menu under "Performance Statistics".
struct type_4E73F0
{
    RwInt32 unk_00;             // the text shown
    RwReal unk_04;              // the graphs' frame rate (30)
    RwInt32 unk_08;             // set to reset them all
    RwInt32 unk_0C;             // show the highest four
    RwInt32 unk_10;
    RwUInt8 unk_14[0x4];
    RwInt32 unk_18;             // the next sample (0 to 94)
    RwReal unk_1C[49][95];      // each timer's samples

#ifdef CODFH_SP // inline: dword_4E73F0 is static .data (SP 0x3239A8, +4 = 30.0f), no initializer or out-of-line copy
    type_4E73F0()
    {
        unk_08 = 1;
        unk_18 = 0;
        unk_00 = 0;
        unk_04 = 30.0f;
        unk_08 = 0;
        unk_0C = 0;
        unk_10 = 0;
    }
#else
    type_4E73F0();
#endif
    // Makes its switches (clearing them first) and frees them.
    void sub_184CF0();
    void sub_184E40();
    // Clears the timers' statistics.
    void sub_184F00();
    // Its step and its draw for the camera arg_0 (the first menu's draw).
    void sub_184F90();
    void sub_1851C0(RwCamera *arg_0);
    void sub_185220();
    void sub_185390(RwCamera *arg_0);
    void sub_1859A0(RwInt32 arg_0);
    // Draws the arg_8 points arg_4 as a line (closed when arg_C is set) in
    // the colour arg_10 (one a point when arg_14 is set) for the camera
    // arg_0.
    void sub_185820(RwCamera *arg_0, RwV2d *arg_4, RwInt32 arg_8, RwInt32 arg_C, RwRGBA *arg_10,
                    RwInt32 arg_14);
    void sub_185B50();
};
typedef RwChar type_4E73F0_size_check[sizeof(type_4E73F0) == 0x48D8 ? 1 : -1];
extern type_4E73F0 dword_4E73F0;
// The root group (in .data).
extern type_4E73A8_14 off_42A4D4;

#endif
