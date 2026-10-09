/* Single player compiles src/rwa/xbox/unit_24DF20.c as 2 files (PLAN_SP SP1); this is part 2,
 * the module tables (unk_4305EC-unk_430654) and their open/close (sub_24EBD0, sub_24EC10):
 * default.xbe has the two functions (SP 0x161BC0, 0x161C00) right before unit_24EC60's code
 * (0x161C50) and the tables (SP 0x32C668-0x32C6DB) before unit_24EC60's data, which starts at
 * the next 8-byte boundary (0x32C6E0: an object boundary, not a table entry), while part 1
 * (sp_unit_24DF20_1.c) follows unit_24DA70 (code SP 0x163F60, data 0x32CB50). Multiplayer has
 * the two pieces at unit_24DF20's end (0x24EBD0-0x24EC60, 0x4305EC-0x430660).
 * Built for single player only (tools/target.py; the multiplayer build never compiles src/sp/). */
#define CODFH_SP_PART 2
#include "../../rwa/xbox/unit_24DF20.c"
