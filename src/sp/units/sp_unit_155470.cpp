// SP compiles sub_14D1B0 (0xF5D80) beside its two callers (PLAN_SP SP1):
// the tank's vf_044 (0xFDBA0) and the vehicle's vf_04C (0xFC3C0) both need
// the helper's out-of-line definition visible for their argument scheduling.
// Including the remaining vehicle definitions changes two matched tank
// functions, so those definitions stay in sp_unit_14C820_1.cpp.
#define CODFH_SP_PART 2
#include "../../recovered/unit_14C820.cpp"
#undef CODFH_SP_PART
#include "../../recovered/unit_155470.cpp"
