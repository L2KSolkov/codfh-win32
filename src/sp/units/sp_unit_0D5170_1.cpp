// Single player compiles src/recovered/unit_0D5170.cpp as two files (PLAN_SP SP1); this is part 1, type_4B85F8's members (SP 0xA1410-0xA14FF).
// Evidence: sub_D5320 and sub_D5570 (SP 0xA1910, 0xA21A0) match only with type_4B85F8's members in
// another file: they reload what VC would keep across a call of a member it had already
// compiled in the same file. Built for single player only (tools/target.py; the multiplayer build never compiles src/sp/).
#define CODFH_SP_PART 1
#include "../../recovered/unit_0D5170.cpp"
