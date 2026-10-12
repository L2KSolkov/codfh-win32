// The handle table dword_439E78 (type_439E78): its reset (sub_672F0 and
// "Restart", sub_67340), registration (sub_673C0), release (sub_67520) and
// lookup (sub_67620), preceded by type_67260's constructor. alfahash follows
// at sub_676A0. The file's original name and whether the constructor
// belongs to it are not recovered (M1), so it is named for its start
// address.

#include <string.h>

#include "rw/ostypes.h"
#include "game/functions.h"
#include "types/type_439E78.h"
#include "types/type_67260.h"
#include "types/alfaobject.h"
#include "types/type_3D2E7C.h"
#ifdef CODFH_SP
#include "types/type_365A0.h"
#endif

// Its data definitions (PLAN M5), in the image's address order.
// 0x00428A30
RwInt32 dword_428A30 = 1;
// 0x00439E78
type_439E78 dword_439E78[0x1444];
// 0x004491A8
RwInt32 dword_4491A8;
// 0x004491AC
RwUInt32 dword_4491AC[4];
// 0x004491BC
RwInt32 dword_4491BC;
// End of its data definitions.



// dword_428A30: the serial of the next handle (from 1).
extern RwInt32 dword_428A30;
// dword_439E78: the handle table.
extern type_439E78 dword_439E78[0x1444];
// dword_4491AC: the last four indices released, reused first, in a ring
// whose next slot is dword_4491A8.
extern RwInt32 dword_4491A8;
extern RwUInt32 dword_4491AC[4];
// dword_4491BC: cleared with the table; no other use is known.
extern RwInt32 dword_4491BC;

// sub_71940: destroys an AI object (kind 4); kinds 1 to 3 are in
// types/alfaobject.h.
void sub_71940(type_3D2E7C *arg_0);

void sub_67650(type_439E78_00 arg_0, type_67620 **arg_4, RwInt32 arg_8);

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_07EKAIBOKF@Restart?$AA@ @ 0x003D2750
// match: ??_C@_08NKPDJDJD@Shutdown?$AA@ @ 0x003D2758
// match: ??_C@_0BA@NALJLPGN@Out?5of?5Handles?$CB?$AA@ @ 0x003D2764
// match: ?dword_428A30@@3HA @ 0x00428A30

#ifndef CODFH_SP // single player has it inline (include/types/type_67260.h)
// match: ??0type_67260@@QAE@XZ @ 0x00067260

type_67260::type_67260()
{
    unk_00 = 0;
    unk_04 = 0;
    memset(unk_08, 0, sizeof(unk_08));
    unk_00 = 1;
    unk_04 = 0;
    unk_38 = 0;
    unk_3C = 0;
    unk_40 = 0;
    unk_44 = 0;
    unk_48 = 0;
    unk_4C = 0;
}
#endif

// match: sub_672F0 @ 0x000672F0
// sp-match: sub_672F0 @ 0x00057A20
// Empties the handle table.
void sub_672F0()
{
    dword_428A30 = 1;
    memset(dword_439E78, 0, sizeof(dword_439E78));
    dword_4491BC = 0;
    memset(dword_4491AC, 0, sizeof(dword_4491AC));
    dword_4491A8 = 0;
}

// match: sub_67340 @ 0x00067340
// Empties the handle table on a restart.
void sub_67340()
{
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS) // MP only: single player compiles the debug print out (the text is not in default.xbe)
    sub_19A750("Restart");
#endif
    dword_428A30 = 1;
    memset(dword_439E78, 0, sizeof(dword_439E78));
    dword_4491BC = 0;
    memset(dword_4491AC, 0, sizeof(dword_4491AC));
    dword_4491A8 = 0;
}

// match: sub_673A0 @ 0x000673A0
void sub_673A0()
{
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS) // MP only: single player compiles the debug print out (the text is not in default.xbe)
    sub_19A750("Shutdown");
#endif
}

// match: sub_673C0 @ 0x000673C0
// sp-match: sub_673C0 @ 0x00057AC0
// Registers arg_0, of kind arg_4, under a new handle and returns it: at a
// recently released index when one is free, else at the first free index
// from 1.
RwUInt32 sub_673C0(type_67620 *arg_0, RwInt32 arg_4)
{
    RwInt32 l14;
    type_439E78_00 var_10;
    RwUInt32 *ebp_C;
    RwInt32 v8;
    RwInt32 var_4;

    v8 = 0;
    if (dword_428A30 == 0)
        dword_428A30 = 1;
    for (ebp_C = dword_4491AC, var_4 = 0; var_4 < 4; var_4++, ebp_C++) {
        if (*ebp_C != 0 && dword_439E78[*ebp_C].unk_00 == 0 && dword_439E78[*ebp_C].unk_08 == 0) {
            var_10.unk_00 = (RwUInt16)*ebp_C;
            var_10.unk_02 = (RwUInt16)dword_428A30;
            sub_67650(var_10, &arg_0, arg_4);
            *ebp_C = 0;
            v8 = 1;
            dword_428A30++;
            break;
        }
    }
    if (v8 == 0) {
        for (l14 = 1; l14 < 0x1444; l14++) {
            if (dword_439E78[l14].unk_00 == 0 && dword_439E78[l14].unk_08 == 0) {
                var_10.unk_00 = (RwUInt16)l14;
                var_10.unk_02 = (RwUInt16)dword_428A30;
                sub_67650(var_10, &arg_0, arg_4);
                v8 = 1;
                dword_428A30++;
                break;
            }
        }
    }
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS) // single player compiles the debug print out (SP 0x57AC0)
    if (v8 == 0)
        sub_19A750("Out of Handles!");
#endif
    return *(RwUInt32 *)&var_10;
}

// match: sub_67520 @ 0x00067520
// sp-match: sub_67520 @ 0x00057BA0
// Releases the handle arg_0, destroying its object by its kind.
void sub_67520(RwUInt32 arg_0)
{
    if (arg_0 != 0) {
        switch (dword_439E78[(RwUInt16)arg_0].unk_04) {
        case 4:
            sub_71940((type_3D2E7C *)sub_67620(arg_0));
            break;
        case 1:
            sub_71A60((type_3D2CD0 *)sub_67620(arg_0));
            break;
        case 2:
            sub_71B60((type_3D2DB8 *)sub_67620(arg_0));
            break;
        case 3:
            sub_71C60((type_3D2E20 *)sub_67620(arg_0));
            break;
        }
    }
    dword_4491AC[dword_4491A8] = (RwUInt16)arg_0;
    dword_4491A8 = (dword_4491A8 + 1) & 3;
    dword_439E78[(RwUInt16)arg_0].unk_00 = 0;
    dword_439E78[(RwUInt16)arg_0].unk_08 = 0;
    dword_439E78[(RwUInt16)arg_0].unk_04 = 0;
}

// match: sub_67620 @ 0x00067620
// sp-match: sub_67620 @ 0x00057A60
type_67620 *sub_67620(RwInt32 arg_0)
{
    if (dword_439E78[(RwUInt16)arg_0].unk_00 == arg_0)
        return dword_439E78[(RwUInt16)arg_0].unk_08;
    return 0;
}
#ifdef CODFH_SP
// shape: sp_sub_67620_h (folded into sub_67620, SP 0x57A60): sub_67620's body again, taking the
// handle as a type_365A0 by value. sub_353A0's case 9 (SP 0x2A160) passes the handle that way, which
// gives the image's `mov ecx, eax; push ecx`; the linker folds the two bodies.
type_67620 *sp_sub_67620_h(type_365A0 arg_0)
{
    if (dword_439E78[(RwUInt16)arg_0.unk_00].unk_00 == (RwInt32)arg_0.unk_00)
        return dword_439E78[(RwUInt16)arg_0.unk_00].unk_08;
    return 0;
}
#endif

// match: sub_67650 @ 0x00067650
// sp-match: sub_67650 @ 0x00057A80
// Fills arg_0's entry: the handle, the object *arg_4 and its kind arg_8.
void sub_67650(type_439E78_00 arg_0, type_67620 **arg_4, RwInt32 arg_8)
{
    dword_439E78[arg_0.unk_00].unk_00_h.unk_00 = arg_0.unk_00;
    dword_439E78[arg_0.unk_00].unk_00_h.unk_02 = arg_0.unk_02;
    dword_439E78[arg_0.unk_00].unk_08 = *arg_4;
    dword_439E78[arg_0.unk_00].unk_04 = arg_8;
}
