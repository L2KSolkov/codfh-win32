// The section slots (dword_4E5D30): the image's four; with CODFH_ALL_SECTIONS (the port's game
// builds, single player's and multiplayer's, not the dedicated server's) enough for every section
// of a level at once (the levels' ids reach 22; the slot tag kept on a section's objects is 8
// bits). Only what loading and drawing the sections needs walks them all: the collision queries,
// the AI's paths, the lighting zones and multiplayer's section messages (the peers' four) still
// see the first four.
#ifndef GAME_SECTIONSLOTS_H
#define GAME_SECTIONSLOTS_H

#include "rw/ostypes.h"

#ifdef CODFH_ALL_SECTIONS
#define SECTION_SLOTS 32
// (port/src/debug/trigtools.cpp, Level, Sections: the switch, and the load of every
// section the level has not loaded)
RwInt32 port_all_sections_on();
void port_all_sections_load();
#else
#define SECTION_SLOTS 4
#endif

#endif
