// Single player compiles src/recovered/unit_03CA10.cpp as two files (PLAN_SP SP1); this is part 1, everything but sub_3D3E0.
// Evidence: vf_01C's twin (SP 0x2E290) is compiled in place (not deferred after its callee) and
// keeps its values in ebx/esi/edi across its calls of sub_3D3E0 (SP 0x2E2AA) as VC does for a callee it has not
// compiled, while sub_3CBF0, sub_3CC80 and sub_3CE20 (SP 0x2E4D0, 0x2E540, 0x2E5A0) keep registers
// across sub_3CD60, sub_3CDB0, sub_3D3A0 and sub_3D2E0, so those stay in one file. Built for
// single player only (tools/target.py; the multiplayer build never compiles src/sp/).
#define CODFH_SP_PART 1
#include "../../recovered/unit_03CA10.cpp"
