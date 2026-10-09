/* Single player compiles src/rwa/unit_247430.c, unit_243AE0.c and rwasymboltable.c as one file
 * (PLAN_SP SP1), each source in parts (CODFH_SP_PART) in default.xbe's order:
 * - .rdata: unit_243AE0's interface IDs (SP 0x2EE6C4), then the stream node interface's ID
 *   (0x2EE7E4) and unit_247430's (0x2EE7F4);
 * - .data: unit_247430's extensions (SP 0x32BDB8), unit_243AE0's tables (0x32BDC8), then
 *   unit_247430's tables (0x32BF1C): one object's data on both sides of the other's;
 * - code: unit_247430's up to sub_249160 (SP 0x15B380-0x15D320), unit_243AE0's
 *   RwaListenerInterfaceRegister_0 (0x15D320), rwasymboltable's (0x15D380-0x15D50F), then
 *   unit_247430's interface registrations (0x15D510).
 * Built for single player only (tools/target.py; the multiplayer build never compiles src/sp/). */
#define CODFH_SP_PART 1
#include "../../rwa/unit_243AE0.c"
#include "../../rwa/unit_247430.c"
#undef CODFH_SP_PART
#define CODFH_SP_PART 2
#include "../../rwa/unit_243AE0.c"
#include "../../rwa/unit_247430.c"
#undef CODFH_SP_PART
#define CODFH_SP_PART 3
#include "../../rwa/unit_243AE0.c"
#include "../../rwa/rwasymboltable.c"
#include "../../rwa/unit_247430.c"
