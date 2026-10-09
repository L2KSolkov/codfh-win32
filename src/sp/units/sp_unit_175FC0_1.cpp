// Single player compiles src/recovered/unit_175FC0.cpp as two files (PLAN_SP SP1); this is part 1, type_4E5E50's and type_176040's constructors and type_4E5E50's destructor (SP 0x110200-0x1102C0).
// Evidence: default.xbe lays the constructors out apart from the rest (unit_174950's functions
// between them), and type_4E5E50's constructor (SP 0x110240) matches only when sub_176100 is
// not compiled before it in the same file. Built for single player only (tools/target.py; the
// multiplayer build never compiles src/sp/).
#define CODFH_SP_PART 1
#include "../../recovered/unit_175FC0.cpp"
