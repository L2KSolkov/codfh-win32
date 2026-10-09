// Single player compiles src/recovered/unit_144940.cpp as two files (PLAN_SP SP1); this is part 2.
// Evidence: sub_145A40's twin (SP 0xF0E00) matches only when the functions from sub_145E20 on (type_4D1DB8's) are in another file: it keeps registers across their calls as VC does for a callee it has not seen.
#define CODFH_SP_PART 2
#include "../../recovered/unit_144940.cpp"
