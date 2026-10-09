// Single player compiles unit_125490 and unit_1279C0 as one file (PLAN_SP SP1): default.xbe
// interleaves their functions over SP 0xDAE60-0xDD8B0, and sub_125A50 (SP 0xDC6B0) keeps eax/ecx
// live across the emptied sub_1288F0 as VC does only for a callee in the same file. Built for
// single player only (tools/target.py; the multiplayer build never compiles src/sp/).
#include "../../recovered/unit_125490.cpp"
#include "../../recovered/unit_1279C0.cpp"
