// Single player compiles unit_18F3C0 and unit_192BE0 as one file (PLAN_SP SP1): default.xbe
// interleaves their functions over SP 0x122120-0x1275D0 (unit_192BE0's type_3DFE20::vf_000 twin at SP
// 0x1223A0 between unit_18F3C0's first runs, unit_18F3C0 runs at SP 0x124C00, 0x124E50 and
// 0x125A60-0x1261F0 between unit_192BE0's), and sub_196B70 (SP 0x125030) reads bp_4 once into
// esi and keeps it across sub_166990, as VC does only when sub_18F8B0 (SP 0x1223D0), which gets
// bp_4's address, is a callee in the same file.
// Built for single player only (tools/target.py; the multiplayer build never compiles src/sp/).
#include "../../recovered/unit_18F3C0.cpp"
#include "../../recovered/unit_192BE0.cpp"
