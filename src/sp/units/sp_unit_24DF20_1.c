/* Single player compiles src/rwa/xbox/unit_24DF20.c as 2 files (PLAN_SP SP1); this is part 1,
 * the output object: its code follows unit_24DA70's (SP 0x163F60) and its data (SP 0x32CB50)
 * follows unit_24EC60's and unit_24DA70's. Part 2 (sp_unit_24DF20_2.c) is the module tables
 * and their open/close, before unit_24EC60.
 * Built for single player only (tools/target.py; the multiplayer build never compiles src/sp/). */
#define CODFH_SP_PART 1
#include "../../rwa/xbox/unit_24DF20.c"
