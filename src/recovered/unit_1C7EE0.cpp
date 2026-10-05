// The assertion report and wide-string helpers (game/assert.h).

#include <stdlib.h>

#include "game/assert.h"
#include "game/functions.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x0042CBD0
const RwChar *dword_42CBD0[6] = { "Assertion failure", "Precondition failure - a condition of calling a method wasn't fulfilled", "Postcondition failure - the state at the end of a method was incorrect", "Assertion - always fails at this point", "Default fail - an unhandled state exists for a switch statement", "Verify fail" };
// End of its data definitions.


// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0M@HONGBCB@Verify?5fail?$AA@ @ 0x003E39A0
// match: ??_C@_0EA@NACADMOE@Default?5fail?5?9?5an?5unhandled?5stat@ @ 0x003E39B0
// match: ??_C@_0CH@HOBCFACN@Assertion?5?9?5always?5fails?5at?5this@ @ 0x003E39F0
// match: ??_C@_0EH@LGKOODNF@Postcondition?5failure?5?9?5the?5stat@ @ 0x003E3A18
// match: ??_C@_0EI@BPBGPJI@Precondition?5failure?5?9?5a?5conditi@ @ 0x003E3A60
// match: ??_C@_0BC@GMCECFHL@Assertion?5failure?$AA@ @ 0x003E3AA8
// match: ??_C@_0P@GFBDOFIC@?6In?5function?3?5?$AA@ @ 0x003E3ABC
// match: ??_C@_04OKDCABBP@?$CC?3?6?6?$AA@ @ 0x003E3ACC
// match: ??_C@_0L@HBPHLIGN@?6In?5file?5?$CC?$AA@ @ 0x003E3AD4
// match: ??_C@_0BL@KKIKFCGA@Assertion?5failure?5on?5line?5?$AA@ @ 0x003E3AE0
// match: ?dword_42CBD0@@3PAPBDA @ 0x0042CBD0

// match: ?sub_1C7EE0@@YAXPBDPAPAD@Z @ 0x001C7EE0

void sub_1C7EE0(const RwChar *arg_0, RwChar **arg_4)
{
    while (*arg_0)
    {
        **arg_4 = *arg_0;
        (*arg_4)++;
        arg_0++;
    }
}

// match: ?sub_1C7F20@@YAX_NPBDH1H@Z @ 0x001C7F20
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_1C7F20(bool arg_0, const RwChar *arg_4, RwInt32 arg_8, const RwChar *arg_C, RwInt32 arg_10)
{
    RwChar var_410[0x400];
    RwChar *lv_10;
    RwChar var_C[8];

    if (!arg_0)
    {
        const RwChar *slot_414;

        slot_414 = 0;
        switch (arg_10)
        {
        case 0:
            slot_414 = dword_42CBD0[0];
            break;
        case 1:
            slot_414 = dword_42CBD0[1];
            break;
        case 2:
            slot_414 = dword_42CBD0[2];
            break;
        case 3:
            slot_414 = dword_42CBD0[3];
            break;
        case 5:
            slot_414 = dword_42CBD0[5];
            break;
        case 4:
            slot_414 = dword_42CBD0[4];
            break;
        default:
            sub_19A750();
        }
        lv_10 = var_410;
        _itoa(arg_8, var_C, 10);
        sub_1C7EE0("Assertion failure on line ", &lv_10);
        sub_1C7EE0(var_C, &lv_10);
        sub_1C7EE0("\nIn file \"", &lv_10);
        sub_1C7EE0(arg_4, &lv_10);
        sub_1C7EE0("\":\n\n", &lv_10);
        sub_1C7EE0(slot_414, &lv_10);
        sub_1C7EE0("\nIn function: ", &lv_10);
        sub_1C7EE0(arg_C, &lv_10);
        sub_1C7EE0("\n", &lv_10);
        sub_19A750();
    }
}

// match: ?sub_1C80A0@@YAHPBG@Z @ 0x001C80A0
RwInt32 sub_1C80A0(const RwUInt16 *arg_0)
{
    RwInt32 var_4;

    var_4 = 0;
    while (*arg_0)
    {
        var_4++;
        arg_0++;
    }
    return var_4;
}

// match: ?sub_1C80D0@@YAXPADPBG@Z @ 0x001C80D0
void sub_1C80D0(RwChar *arg_0, const RwUInt16 *arg_4)
{
    while (*arg_4)
    {
        *arg_0 = (RwChar)*arg_4;
        arg_4++;
        arg_0++;
    }
    *arg_0 = 0;
}
