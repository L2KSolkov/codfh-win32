// Single player compiles src/recovered/unit_0FB7A0.cpp as 3 files (PLAN_SP SP1); this is part 2.
// Evidence: type_3D96FC's and type_3D9718's vf_000/vf_00C twins (SP 0xBF410, 0xBF430, 0xBF810, 0xBF830) keep this across their calls to type_3D96F0's vf_000/vf_004 (SP 0xBF6B0, 0xBF6D0), as VC does for a callee in another file; the image places type_3D96F0's methods (0xBF6B0-0xBF7E0) between the two.
#define CODFH_SP_PART 2
#include "../../recovered/unit_0FB7A0.cpp"
