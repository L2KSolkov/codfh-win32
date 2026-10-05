/*
 * The frame time and the screen fade (unit_124DC0). sub_124DC0 keeps the
 * last ten frame times; the fade (sub_124EE0 starts it, sub_124F70 runs it,
 * sub_125060 draws it) covers the screen with a quad whose alpha follows
 * its progress, and calls a function once it ends (sub_1252E0 sets them).
 */
#ifndef GAME_FADE_H
#define GAME_FADE_H

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "rw/baengine.h"
#include "rw/baraster.h"

// The last ten frame times, oldest first, and the time of the last frame.
extern RwReal dword_4CF3C0[10];
extern RwReal flt_4CF430;

// The fade: whether it runs (and whether it is still drawn after it ends),
// its direction (0 in, 1 out), its time so far and length (its length in
// seconds by 1000/16.666666), the raster it draws with (the quad is white
// with one, black without), whether it is held back, and the function
// called at the end of each direction.
extern RwUInt8 byte_4CF428;
extern RwUInt8 byte_4CF400;
extern RwUInt8 byte_4CF408;
extern RwInt32 dword_4CF3EC;
extern RwReal dword_4CF3F8;
extern RwReal dword_4CF3FC;
extern RwRaster *dword_4CF3F4;
extern RwInt32 dword_4CF410;
extern RwInt32 dword_4CF42C;
extern void (*dword_4CF404)();
extern void (*dword_4CF40C)();

// The render states the fade's draw saves and restores.
extern RwInt32 dword_4CF420;
extern RwInt32 dword_4CF3E8;
extern RwInt32 dword_4CF3F0;
extern RwInt32 dword_4CF414;
extern RwInt32 dword_4CF41C;
extern RwInt32 dword_4CF424;
extern RwRaster *dword_4CF418;

// Whether the fade has run its length: an inline with no address and so no
// database name, named for what it tests. Evidence: the local respawn
// (type_4F7EB8::sub_1ABE30) tests it through a result slot of its own.
inline bool fade_done()
{
    return dword_4CF3F8 >= dword_4CF3FC;
}

void sub_124DC0(RwReal arg_0);
void sub_124E90();
void sub_124EE0(RwReal arg_0, RwInt32 arg_4);
void sub_124F70(RwReal arg_0);
void sub_125060(RwCamera *arg_0);
void sub_1252E0(void (*arg_0)(), RwInt32 arg_4);
void sub_125320();
void sub_1253A0();
void sub_125410();

#endif
