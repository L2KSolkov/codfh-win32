// An object of data only (or whose code the original link dropped): the
// 16.666666 header constant of the game's other objects and the loading
// screens' names by language (off_429408, read by type_4B8EF0::sub_E9CA0 in
// unit_0E8F40), at 0x3D8D18-0x3D8D58 and 0x429408-0x429444, between
// unit_0E8800's data and unit_0E8F40's.

#include "rw/ostypes.h"
#include "rw/batypes.h"

// Its data definitions (PLAN M5).
// 0x00429408
const RwChar *off_429408[15] = {
    "loading_eng",
    "loading_ger",
    "loading_fre",
    "loading_ger",
    "loading_fre",
    "loading_ita",
    "loading_spa",
    "loading_eng",
    "loading_eng",
    "loading_eng",
    "loading_eng",
    "loading_eng",
    "loading_eng",
    "loading_eng",
    "loading_eng",
};
// (defined after the table: VC7.1 emits data definitions last-defined first, and the
// image has the constant first)
#ifndef CODFH_SP // MP only: single player has no unreferenced 16.666666f here: the names follow sp_fendname's texts (SP 0x2E5304)
// 0x003D8D18
extern const RwReal flt_3D8D18 = 16.666666f;
#endif
// End of its data definitions.

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3D8D18@@3MB @ 0x003D8D18
// match: ??_C@_0M@LPPGBDBF@loading_spa?$AA@ @ 0x003D8D1C
// match: ??_C@_0M@IHFLAMDC@loading_ita?$AA@ @ 0x003D8D28
// match: ??_C@_0M@LPNJKFNC@loading_fre?$AA@ @ 0x003D8D34
// match: ??_C@_0M@BLIPPDNE@loading_ger?$AA@ @ 0x003D8D40
// match: ??_C@_0M@IKGGDCKK@loading_eng?$AA@ @ 0x003D8D4C
// match: ?off_429408@@3PAPBDA @ 0x00429408
