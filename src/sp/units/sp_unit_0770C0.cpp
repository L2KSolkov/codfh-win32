// Single player compiles unit_0770C0 and unit_078AF0 as one file (PLAN_SP SP1): default.xbe
// interleaves their functions over SP 0x62180-0x63380 (the CAnimObjectPool members at SP
// 0x63060-0x63130 sit between unit_0770C0's), and sub_78790 (SP 0x63210) keeps ecx across the
// emptied CAnimObjectPool::sub_78C00 as VC does only for a callee in the same file. Built for
// single player only (tools/target.py; the multiplayer build never compiles src/sp/).
#include "../../recovered/unit_0770C0.cpp"
#include "../../recovered/unit_078AF0.cpp"
