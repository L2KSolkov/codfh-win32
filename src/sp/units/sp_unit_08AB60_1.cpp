// Single player compiles src/recovered/unit_08AB60.cpp as two files (PLAN_SP SP1); this is part 1.
// Evidence: sub_8D660's twin (SP 0x71560) matches only when the vector helpers (sub_8B920 to sub_8C410, SP 0x6FC30-0x70380) are in another file: it keeps registers across their calls as VC does for a callee it has not seen.
#define CODFH_SP_PART 1
#include "../../recovered/unit_08AB60.cpp"
