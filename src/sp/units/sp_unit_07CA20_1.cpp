// Single player compiles src/recovered/unit_07CA20.cpp as two files; this is part 1.
// Evidence: sub_80910's twin (SP 0x682D0) matches only when sub_7CA20 and sub_7CAC0 (SP 0x65C10, 0x65C80) are in
// another file, sub_7D2F0's (SP 0x663B0) only when they are in its own; the image holds the first file at
// SP 0x65C10-0x67AFF and the second from sub_7FC90 (SP 0x67B10) on.
#define CODFH_SP_PART 1
#include "../../recovered/unit_07CA20.cpp"
