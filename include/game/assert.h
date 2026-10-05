/*
 * The assertion report and wide-string helpers (unit_1C7EE0).
 */
#ifndef GAME_ASSERT_H
#define GAME_ASSERT_H

#include "rw/ostypes.h"

// Appends the string arg_0 at *arg_4 and moves *arg_4 past it (no end).
void sub_1C7EE0(const RwChar *arg_0, RwChar **arg_4);
// Unless arg_0 holds, builds "Assertion failure on line <arg_8>\nIn file
// \"<arg_4>\":\n\n<the level arg_10's name>\nIn function: <arg_C>\n" and
// stops in the (empty in this build) debug hook.
void sub_1C7F20(bool arg_0, const RwChar *arg_4, RwInt32 arg_8, const RwChar *arg_C, RwInt32 arg_10);
// The assertion levels' names (dword_42CBD0, six).
extern const RwChar *dword_42CBD0[6];
// The length of the wide string arg_0, and its copy into the narrow
// string arg_0 (the low bytes).
RwInt32 sub_1C80A0(const RwUInt16 *arg_0);
void sub_1C80D0(RwChar *arg_0, const RwUInt16 *arg_4);

#endif
