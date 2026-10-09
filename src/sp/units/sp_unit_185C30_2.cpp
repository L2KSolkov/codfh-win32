// Single player compiles src/recovered/unit_185C30.cpp as two files (PLAN_SP SP1); this is part 2,
// merged with unit_188380: default.xbe interleaves their functions over SP 0x11BBF0-0x11E940
// (type_4EBE00's members at SP 0x11C2F0-0x11D280 and 0x11D7C0-0x11D980 between unit_185C30's).
// Built for single player only (tools/target.py; the multiplayer build never compiles src/sp/).
#define CODFH_SP_PART 2
#include "../../recovered/unit_185C30.cpp"
#include "../../recovered/unit_188380.cpp"
