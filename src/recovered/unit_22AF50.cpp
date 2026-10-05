// Split from unit_22AE00.cpp at 0x22AF50, where the image starts another object (the players
// list item, type_22AF50, its constructor first): its .rdata begins at 0x3EB048 with its own
// constant block (0.01, 0.01, 16.666666) before its vtable (PLAN M7).

#include <string.h>
#include <stdio.h>
#include "game/uixfont.h"
#include "game/frontend.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003EB048
extern const RwReal flt_3EB048 = 0.01f;
// 0x003EB04C
extern const RwReal flt_3EB04C = 0.01f;
// 0x003EB050
extern const RwReal flt_3EB050 = 16.666666f;

// match: ?flt_3EB048@@3MB @ 0x003EB048
// match: ?flt_3EB04C@@3MB @ 0x003EB04C
// match: ?flt_3EB050@@3MB @ 0x003EB050


// The voice chat's status tests (game/voice.h), kept out of line here.

// match: ??0type_22AF50@@QAE@IU_XUID@@PBDH@Z @ 0x0022AF50
// match: ??_7type_22AF50@@6B@ @ 0x003EB054
type_22AF50::type_22AF50(RwUInt32 arg_0, XUID arg_4, const RwChar *arg_10, RwInt32 arg_14)
{
    unk_04 = arg_4;
    unk_48 = arg_14;
    _snwprintf(unk_10, 0x1A, L"%S", arg_10);
    unk_10[0x19] = 0;
    unk_44 = 1;
    unk_4C = arg_0;
}
