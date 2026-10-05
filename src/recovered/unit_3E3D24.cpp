// An object of data only (or whose code the original link dropped): the
// localisation tables' folder names (dword_42CCF8) and their sizes and counts,
// which the loader (type_1CAC10::sub_1CADA0, unit_1CADA0) reads. The image has
// the names' texts after the language tables' (unit_1CA890), the constants after
// them, and the names' table after the language tables in .data.

#include "rw/ostypes.h"
#include "rw/batypes.h"

// Its data definitions (PLAN M5). The constants come first: VC7.1 emits data
// definitions last-defined first, and the image has them after the names' texts.
// 0x003E3D3C
extern const RwUInt32 dword_3E3D3C[3] = { 0xA000, 0x7800, 0x7800 };
// 0x003E3D48
extern const RwUInt32 dword_3E3D48[3] = { 500, 100, 6 };
// 0x0042CCF8
const RwChar *dword_42CCF8[3] = { "GLOBAL", "INGAME", "EULA" };
// End of its data definitions.

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_04MFPPCKKL@EULA?$AA@ @ 0x003E3D24
// match: ??_C@_06LKGFGFOF@INGAME?$AA@ @ 0x003E3D2C
// match: ??_C@_06FNIPBJLB@GLOBAL?$AA@ @ 0x003E3D34
// match: ?dword_3E3D3C@@3QBIB @ 0x003E3D3C
// match: ?dword_3E3D48@@3QBIB @ 0x003E3D48
// match: ?dword_42CCF8@@3PAPBDA @ 0x0042CCF8
