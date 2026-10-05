/*
 * The pads' library under the pad manager (unit_19D920): the four
 * controllers' XInput records (dword_4F4638), their button bindings (the
 * control sets' tables, game/levels.h), reading them into the manager's
 * pads, and their rumble.
 */
#ifndef GAME_PADLIB_H
#define GAME_PADLIB_H

#include <xtl.h>

#include "rw/ostypes.h"
#include "game/levels.h"
#include "game/gameloop.h"

// A controller (0x9C bytes): its state this frame and the last, its
// capabilities, its handle (0 while out), whether it came in this frame,
// its control set's bindings and its rumble feedback.
struct type_4F4638
{
    XINPUT_STATE unk_00;
    XINPUT_STATE unk_16;
    XINPUT_CAPABILITIES unk_2C;
    HANDLE unk_48;
    RwInt32 unk_4C;
    type_42B740 *unk_50;
    XINPUT_FEEDBACK unk_54;
};
extern type_4F4638 dword_4F4638[4];
extern RwInt32 dword_4F48A8;        // the library is set up
// An input a binding reads (16 bytes): its kind (0 a digital button's mask,
// 1 an analog button's index, 2 to 5 the sticks' axes), its mask and its
// analog button.
struct type_42C5D8
{
    RwInt32 unk_00;
    RwInt32 unk_04;
    RwInt32 unk_08;
    RwInt32 unk_0C;
};
extern type_42C5D8 dword_42C5D8[];
extern RwReal flt_42C77C;           // the sticks' dead zone
extern RwReal flt_42C778;           // the analog buttons' least value

RwInt32 sub_19D920(type_4F4638 *arg_0);
void sub_19D990();
RwReal sub_19DA80(RwInt16 arg_0);
RwReal sub_19DB10(RwInt16 arg_0);
RwReal sub_19DBA0(type_4F4638 *arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C);
void sub_19DE30(type_4F4638 *arg_0, type_4B9308_pad *arg_4);
void sub_19E180(RwInt32 arg_0);
void sub_19E250(type_4F4638 *arg_0, type_4B9308_pad *arg_4, RwReal arg_8);
RwInt32 sub_19E3E0();
type_4F4638 *sub_19E4B0();

#endif
