/*
 * The profiler (unit_16D220): 49 named timing sections (dword_4E23E8,
 * named by sub_16D3A0), each with this frame's and the last frame's
 * counters, opened and closed around work by sub_16D7F0/sub_16D850 (which
 * also keep the render timers' times and depths, dword_42A598's unk_20 and
 * unk_44 (game/debugmenu.h)), and the frame's own
 * counters (dword_4E23CC, the last frame's dword_4E23B0), all in
 * milliseconds from RWS::Time::GetTime.
 */
#ifndef GAME_PROFILER_H
#define GAME_PROFILER_H

#include "rw/ostypes.h"

// A section's counters for one frame.
struct type_16D6E0
{
    RwInt32 unk_00;             // opened at
    RwInt32 unk_04;             // closed at
    RwInt32 unk_08;             // the time inside this frame
    RwInt32 unk_0C;             // the time inside altogether
    RwInt32 unk_10;             // times opened
    RwInt32 unk_14;             // the least and the most unk_0C seen at a
    RwInt32 unk_18;             // frame's end
};

// A timing section.
struct type_4E23E8
{
    type_16D6E0 unk_00;         // this frame's
    type_16D6E0 unk_1C;         // the last frame's
    RwChar unk_38[0x20];        // its name
    RwUInt8 unk_58;             // shown
    RwUInt8 unk_59[0x3];

    void sub_16D220(const RwChar *arg_0, RwUInt8 arg_4);
    void sub_16D270();
    void sub_16D2A0();
    void sub_16D330();
    void sub_16D360();
    // An empty method the shutdown calls on each section, folded by
    // /OPT:ICF into pDtor (0x1E41C0), whose database name it takes.
    void pDtor();
};
typedef RwChar type_4E23E8_size_check[sizeof(type_4E23E8) == 0x5C ? 1 : -1];

extern type_4E23E8 dword_4E23E8[49];
extern type_16D6E0 dword_4E23B0;
extern type_16D6E0 dword_4E23CC;
extern RwInt32 dword_4E3584;
extern RwInt32 dword_4E3588;

// Clears the counters arg_0 (unk_14 to -1).
void sub_16D6E0(type_16D6E0 *arg_0);
void sub_16D3A0();
void sub_16D630();
void sub_16D6A0();
void sub_16D730();
void sub_16D740();
void sub_16D780();
void sub_16D7F0(RwInt32 arg_0);
void sub_16D850(RwInt32 arg_0);

#endif
