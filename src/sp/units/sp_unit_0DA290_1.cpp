// Single player compiles src/recovered/unit_0DA290.cpp as two files (PLAN_SP SP1); this is part 1.
// Evidence: the image's .rdata has the unit's two unreferenced 16.666666f twice: at its head (SP 0x2E37E0) and again after its strings, before the attract movie's 15.945946f (SP 0x2E399C, 0x2E39A0): a second file, the slide show and the attract movie (SP 0xA5E60-0xA62AF).
#define CODFH_SP_PART 1
#include "../../recovered/unit_0DA290.cpp"
