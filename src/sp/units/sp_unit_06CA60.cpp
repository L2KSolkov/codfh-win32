// Single player compiles unit_06CA60, unit_070CA0 and unit_071360 as one file (PLAN_SP SP1):
// default.xbe lays their functions out as repeated 06CA60, 070CA0, 071360 runs over SP
// 0x5BA20-0x5F040, and sub_71220 (SP 0x5E3D0) keeps edx across type_3D2E20::sub_708F0 as VC does
// only for a callee in the same file. Built for single player only (tools/target.py; the
// multiplayer build never compiles src/sp/).
#include "../../recovered/unit_06CA60.cpp"
#include "../../recovered/unit_070CA0.cpp"
#include "../../recovered/unit_071360.cpp"
