/*
 * The waiting screens (unit_185C30): the front end's message boxes shown
 * while the game saves or looks for the memory card, each frame drawn by
 * sub_185C30 around a caller's draw.
 */
#ifndef GAME_WAITSCREEN_H
#define GAME_WAITSCREEN_H

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "rw/badevice.h"

#include <string.h>

typedef struct RwCamera RwCamera;
struct type_D9CF0;

// A message box's answer: which choice (1 yes), set when it closes.
struct type_186E70
{
    RwInt32 unk_00;
    RwUInt8 unk_04;
};
// The front end's message boxes: sub_186E70 opens message arg_0 (its answer
// into arg_4), sub_186F80 closes one, sub_188350 gives the one open; only
// the widths are known.
RwInt32 sub_188350();
RwInt32 sub_186E70(RwInt32 arg_0, void *arg_4, void *arg_8);
// An answer with the message's parameter (the save's name).
struct type_186E70_08 : type_186E70
{
    void *unk_08;
};
void sub_186F80(RwInt32 arg_0, RwInt32 arg_4);
void sub_187040();
// Whether a save may go ahead (sub_186020): what to do and the card's
// result.
struct type_186020
{
    RwInt32 unk_00;
    RwInt32 unk_04;

    type_186020(RwInt32 arg_0, RwInt32 arg_4)
    {
        unk_00 = arg_0;
        unk_04 = arg_4;
    }
    // Compares what to do with arg_0: an inline with no address. Evidence:
    // the save flow (sub_186140) tests each returned value through a byte
    // (sete).
    bool operator==(RwInt32 arg_0)
    {
        return unk_00 == arg_0;
    }
};
extern RwUInt8 byte_4EBCC8;
extern RwUInt8 byte_4EBCC9;
extern RwUInt8 byte_4B8894;
extern RwInt32 dword_4EBCCC;
// Set while saving is switched off (the messages are skipped).
extern RwInt32 dword_4F5A30;
RwInt32 sub_185D50(RwCamera *arg_0, type_D9CF0 *arg_4, void (*arg_8)(RwCamera *, void *), void *arg_C,
                   bool arg_10);
type_186020 sub_186630(RwCamera *arg_0, type_D9CF0 *arg_4, bool arg_8, bool arg_C,
                       void (*arg_10)(RwCamera *, void *), void *arg_14);
void sub_185FD0(RwCamera *arg_0, void (*arg_4)(RwCamera *, void *), void *arg_8);
// Saves into slot arg_8 of the card arg_4 (0 on this build).
type_186020 sub_186140(RwCamera *arg_0, type_D9CF0 *arg_4, RwInt32 arg_8, bool arg_C, RwInt32 arg_10,
                       void *arg_14, void (*arg_18)(RwCamera *, void *), void *arg_1C);
void sub_185F30(RwCamera *arg_0, void (*arg_4)(RwCamera *, void *), void *arg_8);
type_186020 sub_186020(RwCamera *arg_0, type_D9CF0 *arg_4, bool arg_8, void (*arg_C)(RwCamera *, void *),
                       void *arg_10);
// The checkpoint's save into the save state's slot (arg_8 unused).
type_186020 sub_1866E0(RwCamera *arg_0, type_D9CF0 *arg_4, RwInt32 arg_8, void (*arg_C)(RwCamera *, void *),
                       void *arg_10);
void sub_185F80(RwCamera *arg_0, void (*arg_4)(RwCamera *, void *), void *arg_8);
// The sound system's update (types/soundbank.h, which clashes with the
// music player's header here).
extern "C" void RwaCoreUpdate();
// Whether the memory unit operation still runs.
RwInt32 sub_186D00();


// The message boxes' state (in .bss): the one open (-1 none), the font,
// whether they are shown, their colours and layout, and the loaded text.
extern RwInt32 dword_4EBD34;
extern struct type_DA580 *dword_4EBD2C;
extern RwInt32 dword_4EBCD8;
extern RwInt32 dword_4EBCDC;
extern const RwChar *dword_4EBCE0[5];   // the button bar's labels (looked up once)
extern RwV2d dword_4EBCF8;      // the boxes' centre, and with a level
extern RwV2d dword_4EBD08;      // script running
extern RwRGBA dword_4EBD10;
extern RwRGBA dword_4EBD14;
extern RwRGBA dword_4EBD20;
extern RwRGBA dword_4EBD24;
extern RwInt32 dword_4EBD30;
extern RwRGBA dword_4EBDE8;
extern RwUInt8 byte_4EBDF4;     // the text stays loaded
extern void *pBlock;            // the loaded text
void sub_186E10();

// The 512x448 layout's x and y on the 640x480 screen; by const reference,
// as sub_1889C0 copies each argument to a temporary. Its arguments are
// members, which bind without a copy, so the calls pass +x
// (docs/toolchain.md).
inline RwReal scale_screen_x(const RwReal &arg_0)
{
    return arg_0 * 1.25f;
}
inline RwReal scale_screen_y(const RwReal &arg_0)
{
    return arg_0 * 1.07142857f;
}
struct type_4EBE00;
struct type_4EBE00_DC;
// A message box's choice (0x2C bytes): its text and what left or right
// (unk_1C) and accept (unk_24) call, each with its argument.
struct type_4EBE00_100
{
    RwChar unk_00[0x1C];
    void (*unk_1C)(type_4EBE00 *arg_0, type_4EBE00_DC *arg_4, RwChar *arg_8, RwInt32 arg_C);
    RwInt32 unk_20;
    void (*unk_24)(type_4EBE00 *arg_0, type_4EBE00_DC *arg_4, RwChar *arg_8, RwInt32 arg_C);
    RwInt32 unk_28;

    // Clears it (its text, change and select).
    void sub_18A3E0();
};
// A message box's line (0x270 bytes): its choices, how many, the one
// selected and whether a gap goes before it; drawn by sub_18A1F0 (the next
// unit).
struct type_4EBE00_DC
{
    RwChar unk_00[0x100];       // its text
    type_4EBE00_100 unk_100[8];
    RwInt32 unk_260;            // its choices
    RwInt32 unk_264;            // its choice selected (-1 none)
    RwInt32 unk_268;            // 1 when reset
    RwInt32 unk_26C;            // a gap goes before it

    // Clears it; adds the choice arg_0 (its text); whether any choice does
    // anything (so it can be selected).
    void sub_18A110();
    type_4EBE00_100 *sub_18A190(const RwChar *arg_0);
    RwInt32 sub_18A380();

    void sub_18A1F0(RwInt32 arg_0, RwV2d *arg_4, struct type_4EBE00 *arg_8);
};
typedef RwChar type_4EBE00_DC_size_check[sizeof(type_4EBE00_DC) == 0x270 ? 1 : -1];
// A message box's button bar: which of the five buttons it shows.
struct type_4EBE00_04
{
    RwInt32 unk_00[5];

    type_4EBE00_04();
    void sub_18A430();
};
// A message box (0x32A4 bytes; two at dword_4EBE00, the open ones up to
// dword_4EBD34): its constructor sub_188380 and most methods are in the
// next unit.
struct type_4EBE00
{
    RwInt32 unk_00;             // in use
    type_4EBE00_04 unk_04;      // the buttons its bar shows
    RwInt32 unk_18;
    RwReal unk_1C;              // its width and height (100 and 100 when
    RwReal unk_20;              // reset)
    RwReal unk_24;              // its offset
    RwReal unk_28;
    RwInt32 unk_2C;             // its lines
    RwUInt8 unk_30[0x8];
    RwInt32 unk_38;             // the line selected
    RwIm2DVertex unk_3C[4];     // its backdrop
    RwV3d unk_AC[4];            // its corners: bottom left, top left,
                                // bottom right, top right (sub_1889C0)
    type_4EBE00_DC unk_DC[16];
    RwChar unk_27DC[5][0x100];  // its heading lines
    RwInt32 unk_2CDC;           // its message
    RwInt32 unk_2CE0;           // its heading centred
    RwInt32 unk_2CE4;           // it has a button bar (sub_187800)
    void (*unk_2CE8)(type_4EBE00 *arg_0, RwInt32 arg_4); // its update, with
    RwInt32 unk_2CEC;                                     // this
    RwInt32 unk_2CF0;           // back does not close it
    RwIm2DVertex unk_2CF4[4];   // the heading's backdrop
    RwIm2DVertex unk_2D64[4];   // and its frame's pieces
    RwIm2DVertex unk_2DD4[4];
    RwIm2DVertex unk_2E44[4];
    RwIm2DVertex unk_2EB4[4];
    RwIm2DVertex unk_2F24[4];
    RwIm2DVertex unk_2F94[4];
    RwIm2DVertex unk_3004[4];
    RwIm2DVertex unk_3074[4];
    RwIm2DVertex unk_30E4[4];
    RwIm2DVertex unk_3154[4];
    RwIm2DVertex unk_31C4[4];
    RwIm2DVertex unk_3234[4];

    type_4EBE00();
    // Resets it: no lines, nothing selected, a centred heading, no bar.
    void sub_1883B0();
    void sub_188490();
    // Sizes it to its heading and lines, lays it out offset by arg_0 and
    // arg_4 (sub_1889C0), and selects its first selectable line.
    void sub_1884B0(RwReal arg_0, RwReal arg_4);
    void sub_1889C0(RwReal arg_0, RwReal arg_4);
    // The line above and below arg_0 (the selection moving).
    RwInt32 sub_18A060(RwInt32 arg_0);
    RwInt32 sub_189FB0(RwInt32 arg_0);
    // Its backdrop's depth for the camera arg_0 (arg_4 of the way from the
    // near to the far plane).
    void sub_1888F0(RwCamera *arg_0, RwReal arg_4);
    // A new line.
    type_4EBE00_DC *sub_188970();
    // Sets heading line arg_0.
    void set_heading(RwInt32 arg_0, const RwChar *arg_4)
    {
        strcpy(unk_27DC[arg_0], arg_4);
    }
};
typedef RwChar type_4EBE00_size_check[sizeof(type_4EBE00) == 0x32A4 ? 1 : -1];
extern type_4EBE00 dword_4EBE00[2];
// The messages' openers (in .data, ended by -1).
struct type_42B518
{
    RwInt32 unk_00;
    void (*unk_04)(type_4EBE00 *arg_0, RwInt32 arg_4);
};
extern type_42B518 off_42B518[];
extern void *dword_4EBD04;      // the message boxes' font (sub_186E70)
extern RwInt32 dword_4EBD38[0x2C]; // the pad bindings held while one is open
void sub_1882C0();
// The pad buttons the boxes answer to: up, down, left, right, accept and
// back (in .bss).
extern RwInt32 dword_4EBD28;
extern RwInt32 dword_4EBD1C;
extern RwInt32 dword_4EBD00;
extern RwInt32 dword_4EBDF0;
extern RwInt32 dword_4EBD18;
extern RwInt32 dword_4EBDEC;
// The front end's state (6 while its own menus run).
#ifdef CODFH_PLAIN
extern RwInt32 &dword_4F3168;
#else
extern RwInt32 dword_4F3168;
#endif
void sub_18E380(type_4EBE00 *arg_0, type_4EBE00_DC *arg_4, RwChar *arg_8, RwInt32 arg_C);
RwInt32 sub_186D00();
type_4EBE00 *sub_186D10();
void sub_186DA0();
// Draws the message box arg_0, and the button bar.
void sub_187400(type_4EBE00 *arg_0);
// Draws the text arg_8 at *arg_4 in the style arg_0 (arg_C unused here).
void sub_1879F0(RwInt32 arg_0, RwV2d *arg_4, const RwChar *arg_8, RwRGBA *arg_C);
void sub_187800();
// Where the button bar's labels go, by how many there are (fractions of
// a 512 by 448 screen; in .data).
struct type_42B490
{
    RwReal unk_00;
    RwReal unk_04;
    RwReal unk_08;
};
extern type_42B490 dword_42B490[3][3];
extern RwReal flt_42B478;       // the large text's scale
// The text object named arg_0 (also declared in types/type_10F710.h).
struct type_3DF8D8 *sub_198880(const RwChar *arg_0);

// The text parser's cursor (unit_188380): where it is, the end, and the
// token buffer.
struct type_18A530
{
    RwChar *unk_00;
    RwChar *unk_04;
    RwChar *unk_08;
};
// A card message's state (sub_18B670): the card, its search's result, its
// free space and when to look again.
struct type_18B670
{
    struct type_D9CF0 *unk_00;
    RwInt32 unk_04;
    RwInt32 unk_08;
    RwUInt32 unk_0C;
};
void sub_1870D0();
// A memory card slot's choice (four at dword_4F24A8; sub_18CE40 selects
// it): where the slot chosen and whether it is empty go, its slot, whether
// it is empty, and whether an empty slot cannot be chosen (loading).
struct type_4F24A8
{
    RwInt32 *unk_00;
    RwInt32 unk_04;
    RwUInt8 *unk_08;
    RwUInt8 unk_0C;
    RwUInt8 unk_0D;
    RwUInt8 unk_0E[0x2];
};
extern type_4F24A8 dword_4F24A8[4];
// The memory card slot menu's state (sub_18CFA0): the answer (3 cancel),
// its mode (0 and 1 save, 2 load, 3 create), whether to read the slots'
// names again, the slots' choices, the slot selected first, and the slot
// chosen.
struct type_18CFA0 : type_18B670
{
    RwInt32 unk_10;
    RwInt32 unk_14;
    RwInt32 unk_18;
    RwUInt8 unk_1C;
    RwUInt8 unk_1D[0x3];
    type_4F24A8 *unk_20;
    RwInt32 unk_24;
    RwInt32 unk_28;
    RwUInt8 unk_2C;
    RwUInt8 unk_2D[0x3];
    type_4EBE00_100 *unk_30[4];
};
// A save message's state (sub_18BCD0, sub_18BD90): the answer, whether
// it can be cancelled and whether it overwrites.
struct type_18BCD0
{
    RwInt32 unk_00;
    RwUInt8 unk_04;
    RwUInt8 unk_05[0x3];
    RwInt32 unk_08;
};
// A name table's entry (ended by a null name).
struct type_18A470
{
    const RwChar *unk_00;
    // The string the tag names (sub_18A730 sets it).
    RwChar **unk_04;
};
// The text parser's string cursor (sub_18A730): the output position, the
// tag just read and the name table.
struct type_18A730 : type_18A530
{
    RwChar *unk_0C;
    type_18A470 *unk_10;
};
// A text parser pass (sub_18A890): the tag's reader and cursor, and the
// string's reader and cursor.
struct type_18A890
{
    RwChar *(*unk_00)(type_18A530 *);
    type_18A530 *unk_04;
    RwChar *(*unk_08)(type_18A530 *);
    type_18A530 *unk_0C;
};
// "No Translation", for a tag without a string.
extern RwChar byte_42B4FC[];
RwChar *sub_18A890(const RwChar *arg_0, type_18A470 *arg_4, RwChar *arg_8);
// The not enough free blocks text, by language (sub_18D8A0), and the
// blocks needed.
extern const RwChar *off_42C7F4[7];
extern RwInt32 dword_4F616C;
// Opens a message box with the text arg_4.
void sub_18D6D0(type_4EBE00 *arg_0, RwChar *arg_4);
// The in-game messages (_Insert_Controller_1 on; their loader is at
// 0x1A26F0).
extern RwChar *dword_4F6178[29];
// The Xbox Live state: sub_19C440 shows the friends list, sub_19C3A0 and
// sub_19C3F0 appear offline and online, sub_19C490 and sub_19C4D0 sign in
// and out.
// (Declared in game/xboxlive.h.)
// The in-game options (the options menu, sub_18E640, names them): the sound
// mode, the turn speed, the control set, subtitles, invert aim, controller
// shake, hint messages, the friendly fire block and aim assist, kept in
// the save state (unk_18, unk_1C, unk_21, unk_22, unk_20, unk_28, unk_180,
// unk_181); sub_18E380 applies them.
extern RwInt32 dword_4F2348;
extern RwInt32 dword_4F234C;
extern RwInt32 dword_4F2350;
extern RwInt32 dword_4F2354;
extern RwInt32 dword_4F2358;
extern RwInt32 dword_4F235C;
extern RwInt32 dword_4F2360;
extern RwInt32 dword_4F2364;
extern RwInt32 dword_4F2368;
void sub_18E380(type_4EBE00 *arg_0, type_4EBE00_DC *arg_4, RwChar *arg_8, RwInt32 arg_C);
// The pause menu's height offset, and whether the bar shows the pad's
// buttons.
extern RwReal flt_42B510;
extern RwInt32 dword_42926C;
// The pad whose controller was removed (_Insert_Controller_1, sub_18F330),
// and an accessor for it with no address and so no database name. Evidence:
// sub_18F330 reads it through a temporary (a result local).
#ifdef CODFH_PLAIN
extern RwInt32 &dword_4B9E50;
#else
extern RwInt32 dword_4B9E50;
#endif
inline RwInt32 get_dword_4B9E50()
{
    RwInt32 r = dword_4B9E50;
    return r;
}
// Whether a pad is set (dword_4B9E50 is not -1): an inline with no address,
// named for what it tests. Evidence: the voice chat (sub_1C6920,
// sub_1C6EC0) tests it as a value made by setne before branching.
inline RwInt32 has_dword_4B9E50()
{
    return dword_4B9E50 != -1;
}
// The memory card messages (sub_18AF40 loads them).
extern RwChar *dword_4F2370[0x4D];
RwChar *sub_18AF40(RwChar *arg_0);
// The platform path of the file arg_4 into arg_0.
void sub_D7F20(RwChar *arg_0, const RwChar *arg_4);
// The file size of the file handle arg_0.
RwUInt32 sub_16D200(void *arg_0);
// The language.
RwInt32 sub_19B0A0();

#endif
