// Single player compiles src/recovered/unit_185C30.cpp as two files (PLAN_SP SP1); this is part 1:
// its data and the waiting-screen frames (SP 0x11B740-0x11BBF0, laid out ahead of everything
// else of the unit). Evidence: sub_185C30's twin (SP 0x11B76D) re-reads dword_42926C after
// calling sub_188350, as VC does for a callee it has not compiled in the same file.
#define CODFH_SP_PART 1
#include "../../recovered/unit_185C30.cpp"
