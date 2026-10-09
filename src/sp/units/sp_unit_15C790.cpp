// Single player compiles unit_15C790 and unit_15CCE0 as one file (PLAN_SP SP1): its
// type_15CCE0 functions keep registers across sub_15CB10 as VC does only for a callee in the
// same file (SP 0x101250, 0xFFE80 and 0xFFE00, the twins of sub_15D010, sub_15E950 and
// sub_15E890, match with sub_15CB10 compiled beside them). Built for single player only
// (tools/target.py; the multiplayer build never compiles src/sp/).
#include "../../recovered/unit_15C790.cpp"
#include "../../recovered/unit_15CCE0.cpp"
