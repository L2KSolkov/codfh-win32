/*
 * The game browser's rows (unit_1FB520): a list box row over a session found
 * on the network, sorted by the browser's sort mode.
 */
#ifndef GAME_BROWSER_H
#define GAME_BROWSER_H

#include "game/kujuui.h"

// A session the browser lists: its name (unk_10) and four small numbers
// (unk_28 to unk_2B: its row shows unk_2B's and unk_28's names and
// unk_29 of unk_2A; the sort modes 1 to 3 order by unk_28, unk_29 and
// unk_2B). Only these fields are known.
struct type_1FB520_session
{
    RwUInt8 unk_00[4];
    RwUInt8 unk_04[4];          // the address
    RwUInt16 unk_08;            // the port
    RwUInt8 unk_0A[6];
    RwChar unk_10[0x18];
    RwUInt8 unk_28;
    RwUInt8 unk_29;
    RwUInt8 unk_2A;
    RwUInt8 unk_2B;
    RwUInt8 unk_2C[8];
    RwUInt8 unk_34;             // set: a session found (the session list's fill)
    RwUInt8 unk_35[0x3F];       // the network game's results are 0x74 bytes each
};

// A browser row (off_3E7E48, 0x44 bytes) over the session unk_40: whether
// it sorts before arg_0 by the sort mode (sub_1FB5A0: 0 by name), its
// session's name (sub_1FB760) and its texts (slot 1, sub_1FB7B0: the
// session's, or "Host new" for the row without one).
struct type_1FB520 : kujuUI::type_3E74C0
{
    type_1FB520_session *unk_40;

    // Its destructor is the compiler's (sub_1FB580).
    type_1FB520(type_1FB520_session *arg_0);
    virtual void vf_004();
    bool sub_1FB5A0(const type_1FB520 &arg_0);
    type_1A5EA0 sub_1FB760();
    // Its session: out of line, the same code as the kick row's index getter
    // (/OPT:ICF, 0x21D030; the session list's sub_20DC80 calls it).
    type_1FB520_session *sub_21D030();
};

// The browser's sort mode (dword_5043AC), given and set.
extern RwInt32 dword_5043AC;
RwInt32 sub_1FBB50();
void sub_1FBB60(RwInt32 arg_0);

#endif
