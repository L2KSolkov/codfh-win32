// The weapon banks (game/weaponbank.h).

#include "rw/ostypes.h"
#include "rw/bastream.h"
#include "rw/batextur.h"
#include "rw/bamemory.h"
#include "rw/rt2d.h"
#include "types/asynchload.h"
#include "game/weaponbank.h"
#include "game/functions.h"
#include "game/gameloop.h"
#include <string.h>
#include <stdio.h>

// Its data definitions (PLAN M5), in the image's address order.
// 0x004E54D0
RwInt32 dword_4E54D0[3];
// 0x004E54DC
RwInt32 dword_4E54DC[3];
// 0x004E54E8
RwInt32 dword_4E54E8[3];
// 0x004E54F4
type_4E51B8 dword_4E54F4[3];
// 0x004E5518
RwInt32 dword_4E5518[3];
// End of its data definitions.

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0P@EDLKGHJD@wbank_?$CF02d?4bin?$AA@ @ 0x003DD288
// match: ??_C@_0KH@MCLHJDGA@Weapon?5file?5contained?5?$CFd?5weapon?5@ @ 0x003DD298
// match: ??_C@_0CD@CBJPJCKL@?7Loading?5weapon?5clump?3?5?$CI0x?$CFx?00x?$CF@ @ 0x003DD340
// match: ??_C@_0BK@GAOMNCMP@WPNBANK?2?$CFs?2wbank_?$CF02d?4bin?$AA@ @ 0x003DD364
// match: ??_C@_05EHGGLLKA@26_50?$AA@ @ 0x003DD380
// match: ??_C@_04IOEMFMNI@0_25?$AA@ @ 0x003DD388
// match: ??_C@_0BE@EEAIMGGG@Request?5to?5load?5?$CFs?6?$AA@ @ 0x003DD390
// match: ??_C@_0EM@KAKMPMKG@A?5request?5to?5load?5wbank_?$CF02d?4bin@ @ 0x003DD3A8
// match: ??_C@_0EK@MHJIHBIH@?7Request?5to?5load?5wbank_?$CF02d?4bin?5@ @ 0x003DD3F8
// match: ??_C@_0FF@CGFMIPGK@A?5request?5to?5load?5wbank_?$CF02d?4bin@ @ 0x003DD448
// match: ??_C@_0CC@BMFGHOFB@Request?5to?5unload?5wbank_?$CF02d?4bin@ @ 0x003DD4A0
// match: .CRT$XCU+0 @ 0x00427138

// match: _$E1 @ 0x0030BD00

// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).

type_4E51D0 dword_4E5528[3][8];

// match: ?sub_16F2C0@@YAXHH@Z @ 0x0016F2C0
// sp-match: ?sub_16F2C0@@YAXHH@Z @ 0x0010C940
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Loads the weapon bank arg_4 into the slot arg_0 now (not when it is
// there already or the slot is busy), unloading the slot first.
void sub_16F2C0(RwInt32 arg_0, RwInt32 arg_4)
{
    RwChar var_128[0x100];
    RwChar var_28[0x20];
    RwStream *l4;

    if (arg_4 == -1 || arg_0 >= 3)
        return;
    if (sub_16F860(arg_4) == arg_0)
        return;
    if (get_bank_state(arg_0))
        return;
    sub_16FAE0(arg_0);
    dword_4E54DC[arg_0] = arg_4;
    dword_4E5518[arg_0] = make_bank_state(0, 1);
    sprintf(var_28, "wbank_%02d.bin", arg_4);
    sprintf(var_128, "Request to load %s", var_28);
#ifndef CODFH_SP // single player compiles the debug print out (the message is still formatted: SP 0x10C9C2)
    sub_19A750(var_128);
#endif
    sub_16F770(var_128, 0x100, arg_4);
    l4 = RwStreamOpen(rwSTREAMFILENAME, rwSTREAMREAD, var_128);
    if (l4)
    {
        sub_16F460(l4, arg_0, arg_4);
        RwStreamClose(l4, 0);
    }
}

// match: ?sub_16F3E0@@YAXHH@Z @ 0x0016F3E0
// sp-match: ?sub_16F3E0@@YAXHH@Z @ 0x0010CA20
// Sets the slot arg_0's bank to arg_4 and loads it (as sub_16F2C0).
void sub_16F3E0(RwInt32 arg_0, RwInt32 arg_4)
{
    RwInt32 var_4;

    if (arg_4 == -1 || arg_0 >= 3)
        return;
    if (sub_16F860(arg_4) == arg_0)
        return;
    if (get_bank_state(arg_0))
        return;
    sub_16FAE0(arg_0);
    dword_4E54DC[arg_0] = arg_4;
    var_4 = (arg_0 << 8) + arg_4 + 0x80000000; // not an address: the request id's flag
    sub_16F2C0(arg_0, arg_4);
}

// match: ?sub_16F460@@YAXPAURwStream@@HH@Z @ 0x0016F460
// sp-match: ?sub_16F460@@YAXPAURwStream@@HH@Z @ 0x0010C770
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Reads the bank arg_8 into the slot arg_4 from the stream arg_0 (as the
// clump banks' sub_16EAE0, with the slot's heap and table).
void sub_16F460(RwStream *arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    type_16EAE0_hdr var_48;
    type_141C10 var_40;
    RwInt32 frm_24;
    RwInt32 var_20;
    RwInt32 l1C;
    type_16EAE0 *m_18;
    type_16EAE0_obj *ebp_14;
    RwInt32 lv_10;
    type_3DF8D8_04 var_C;
    type_16EAE0 *bp_4;

    l1C = 0;
    RwStreamRead(arg_0, &var_48, sizeof(var_48));
    lv_10 = var_48.unk_00;
    bp_4 = 0;
    m_18 = 0;
    frm_24 = 0;
    var_20 = 0;
    if (var_48.unk_00)
    {
        var_20 = var_48.unk_00 * sizeof(type_16EAE0);
        bp_4 = (type_16EAE0 *)RwMalloc(var_20, 0x34250); // not an address: a memory hint
        RwStreamRead(arg_0, bp_4, var_20);
        m_18 = bp_4;
    }
    while (lv_10)
    {
        var_C.unk_00 = m_18->unk_00.unk_00;
        var_C.unk_04 = m_18->unk_00.unk_04;
        ebp_14 = (type_16EAE0_obj *)sub_198710(&var_C);
        if (!ebp_14)
        {
            if (frm_24)
            {
#ifndef CODFH_SP // single player compiles the debug print out
                sub_19A750("\tStream Skip: %d bytes", frm_24);
#endif
                RwStreamSkip(arg_0, frm_24);
                frm_24 = 0;
            }
#ifndef CODFH_SP // single player compiles the debug print out
            sub_19A750("\tLoading weapon clump: (0x%x,0x%x)", m_18->unk_00.unk_00, m_18->unk_00.unk_04);
#endif
            RwStreamRead(arg_0, &var_40, sizeof(var_40));
            RtlEnterCriticalSection(&dword_44BFB8);
            sub_16FE00(arg_4, &var_40.unk_0C.unk_04, 3);
            ebp_14 = (type_16EAE0_obj *)sub_199010(&var_40.unk_0C.unk_04, 3);
            ebp_14->unk_0C = 2;
            ebp_14->unk_10.unk_00 = &dword_4E54F4[arg_4];
            ebp_14->unk_10.set_unk_0C(sub_16F750, arg_4);
            RtlLeaveCriticalSection(&dword_44BFB8);
            ebp_14->vf_000(arg_0, &var_40);
            RtlEnterCriticalSection(&dword_44BFB8);
            sub_198FE0((type_3DF8D8_base *)((type_199010 *)ebp_14));
            l1C++;
            RtlLeaveCriticalSection(&dword_44BFB8);
        }
        else
        {
#ifndef CODFH_SP // single player compiles the debug print out
            sub_19A750("\tIgnoring clump: (0x%x,0x%x). Already Loaded!", m_18->unk_00.unk_00,
                       m_18->unk_00.unk_04);
#endif
            frm_24 += m_18->unk_08;
        }
        m_18++;
        lv_10--;
    }
    if (frm_24)
    {
        RwStreamSkip(arg_0, frm_24);
        frm_24 = 0;
    }
#ifndef CODFH_SP // single player compiles the debug print out
    sub_19A750("Weapon file contained %d weapon clumps. %d loaded with a total mem footprint of %d bytes. \n%d "
               "slots are still available.  %d bytes are still free in weapon bank (%d).",
               var_48.unk_00, l1C, dword_4E54F4[arg_4].unk_04, sub_16FAC0(arg_4),
               dword_4E54F4[arg_4].unk_08 - dword_4E54F4[arg_4].unk_04, arg_4);
#endif
    dword_4E54D0[arg_4] = arg_8;
    dword_4E54DC[arg_4] = -1;
    clear_bank_state(arg_4, 0);
    if (bp_4)
        RwFree(bp_4);
}

// match: ?sub_16F750@@YAPAUtype_4E51D0@@PAXPAUtype_3DF8D8_04@@H@Z @ 0x0016F750
// sp-match: ?sub_16F750@@YAPAUtype_4E51D0@@PAXPAUtype_3DF8D8_04@@H@Z @ 0x0010C690
type_4E51D0 *sub_16F750(void *arg_0, type_3DF8D8_04 *arg_4, RwInt32 arg_8)
{
    return sub_16FE00((RwInt32)arg_0, arg_4, arg_8);
}

// match: ?sub_16F770@@YAXPADHH@Z @ 0x0016F770
// sp-match: ?sub_16F770@@YAXPADHH@Z @ 0x0010C240
// The path of the weapon bank arg_8's file into arg_0 (arg_4 bytes).
void sub_16F770(RwChar *arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    RwChar var_108[0x100];
    RwChar var_308[0x200];

    sprintf(var_308, "WPNBANK\\%s\\wbank_%02d.bin", arg_8 <= 25 ? "0_25" : "26_50", arg_8);
    strncpy(var_108, var_308, 0x100);
    sub_D7F20(var_308, var_108);
    memset(arg_0, 0, arg_4);
    strncpy(arg_0, var_308, strlen(var_308) < (RwUInt32)arg_4 ? strlen(var_308) : arg_4 - 1);
}

// match: ?sub_16F860@@YAHH@Z @ 0x0016F860
// sp-match: ?sub_16F860@@YAHH@Z @ 0x0010C320
// The slot holding the bank arg_0, or -1.
RwInt32 sub_16F860(RwInt32 arg_0)
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 3; var_4++)
    {
        if (dword_4E54D0[var_4] == arg_0)
            return var_4;
    }
    return -1;
}

// match: ?sub_16F8A0@@YAHH@Z @ 0x0016F8A0
// sp-match: ?sub_16F8A0@@YAHH@Z @ 0x0010C340
RwInt32 sub_16F8A0(RwInt32 arg_0)
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 3; var_4++)
    {
        if (dword_4E54DC[var_4] == arg_0)
            return 1;
    }
    return 0;
}

// match: ?sub_16F8E0@@YAHHH@Z @ 0x0016F8E0
// sp-match: ?sub_16F8E0@@YAHHH@Z @ 0x0010C370
RwInt32 sub_16F8E0(RwInt32 arg_0, RwInt32 arg_4)
{
    if (dword_4E54DC[arg_0] == arg_4)
        return 1;
    return 0;
}

// match: ?sub_16F900@@YAHHH@Z @ 0x0016F900
// sp-match: ?sub_16F900@@YAHHH@Z @ 0x0010C6A0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Queues the load of the weapon bank arg_4 into the slot arg_0; 0 when it
// is ignored.
RwInt32 sub_16F900(RwInt32 arg_0, RwInt32 arg_4)
{
    RwChar var_28[0x20];
    RwInt32 l4;

    if (sub_16F860(arg_4) == arg_0)
    {
#ifndef CODFH_SP // single player compiles the debug print out
        sub_19A750("A request to load wbank_%02d.bin is ignored because it is already loaded in slot %d!", arg_4,
                   arg_0);
#endif
        return 0;
    }
    if (sub_16F8E0(arg_0, arg_4))
    {
#ifndef CODFH_SP // single player compiles the debug print out
        sub_19A750("\tRequest to load wbank_%02d.bin is ignored because it is already loading!", arg_4);
#endif
        return 0;
    }
    if (get_bank_state(arg_0))
    {
#ifndef CODFH_SP // single player compiles the debug print out
        sub_19A750("A request to load wbank_%02d.bin is ignored because the bank(%d) is locked!", arg_4, arg_0);
#endif
        return 0;
    }
    sub_16FAE0(arg_0);
    dword_4E54DC[arg_0] = arg_4;
    dword_4E5518[arg_0] = make_bank_state(0, 1);
    l4 = (arg_0 << 8) + arg_4 + 0x80000000; // not an address: the request id's flag
    sprintf(var_28, "wbank_%02d.bin", arg_4);
    if (sub_81FB0(3, var_28, l4))
        return 1;
    if (sub_82020(3, l4))
        return 1;
#ifndef CODFH_SP // single player compiles the debug print out
    sub_19A750("Request to load %s\n", var_28);
#endif
    sub_81EB0(3, var_28, l4);
    return 1;
}

// match: ?sub_16FA60@@YAHH@Z @ 0x0016FA60
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The keys the slot arg_0's table holds.
RwInt32 sub_16FA60(RwInt32 arg_0)
{
    RwInt32 var_C;
    type_4E51D0 *bp_8;
    RwInt32 bp_4;

    bp_4 = 0;
    for (bp_8 = dword_4E5528[arg_0], var_C = 0; var_C < 8; var_C++, bp_8++)
    {
        if (bp_8->unk_00.unk_00 || bp_8->unk_00.unk_04)
            bp_4++;
    }
    return bp_4;
}

// match: ?sub_16FAC0@@YAHH@Z @ 0x0016FAC0
RwInt32 sub_16FAC0(RwInt32 arg_0)
{
    return 8 - sub_16FA60(arg_0);
}

// match: ?sub_16FAE0@@YAXH@Z @ 0x0016FAE0
// sp-match: ?sub_16FAE0@@YAXH@Z @ 0x0010C390
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Unloads the slot arg_0's bank (as the clump banks' sub_16EFD0).
void sub_16FAE0(RwInt32 arg_0)
{
    RwInt32 var_24;
    type_4E51D0 *var_20;
    type_16EAE0_obj *l1C;
    RwInt32 m_18;
    RwInt32 *ebp_14;
    RwInt32 lv_10[4];

    m_18 = 0;
    lv_10[0] = 6;
    lv_10[1] = 7;
    lv_10[2] = 3;
    lv_10[3] = 0;
    ebp_14 = lv_10;
    if (dword_4E54D0[arg_0] != -1)
    {
#ifndef CODFH_SP // single player compiles the debug print out
        sub_19A750("Request to unload wbank_%02d.bin\n", dword_4E54D0[arg_0]);
#endif
        while (*ebp_14)
        {
            for (var_20 = dword_4E5528[arg_0], var_24 = 0; var_24 < 8; var_24++, var_20++)
            {
                l1C = (type_16EAE0_obj *)sub_198710(&var_20->unk_00);
                if (l1C && var_20->unk_08 == *ebp_14)
                {
                    if (var_20->unk_08 == 7)
                    {
                        RwTexDictionary *var_28 = l1C->unk_24;

                        if (var_28)
                            RwTexDictionaryDestroy(var_28);
                    }
                    sub_198F00(&var_20->unk_00);
                    m_18++;
#ifndef CODFH_SP // single player compiles the debug print out
                    sub_19A750("\tUnloading GodID (0x%08x,0x%08x)", var_20->unk_00.unk_00, var_20->unk_00.unk_04);
#endif
                    var_20->unk_00.unk_00 = 0;
                    var_20->unk_00.unk_04 = 0;
                    var_20->unk_08 = 0;
                }
            }
            ebp_14++;
        }
#ifndef CODFH_SP // single player compiles the debug print out
        sub_19A750("Unloaded %d GodIDs. %d slots are available.", m_18, sub_16FAC0(arg_0));
#endif
        dword_4E54F4[arg_0].unk_04 = 0;
    }
    dword_4E54D0[arg_0] = -1;
    memset(dword_4E5528[arg_0], 0, sizeof(dword_4E5528[arg_0]));
}

// match: ?sub_16FC80@@YAXXZ @ 0x0016FC80
// sp-match: ?sub_16FC80@@YAXXZ @ 0x0010C480
void sub_16FC80()
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 3; var_4++)
    {
        memset(dword_4E5528[var_4], 0, sizeof(dword_4E5528[var_4]));
        dword_4E54D0[var_4] = -1;
        dword_4E54DC[var_4] = -1;
        dword_4E54E8[var_4] = -1;
        dword_4E5518[var_4] = 0;
        memset(&dword_4E54F4[var_4], 0, sizeof(dword_4E54F4[var_4]));
    }
}

// match: ?sub_16FD10@@YAXXZ @ 0x0016FD10
// sp-match: ?sub_16FD10@@YAXXZ @ 0x0010C510
void sub_16FD10()
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 3; var_4++)
    {
        sub_16FAE0(var_4);
        dword_4E54DC[var_4] = -1;
        dword_4E5518[var_4] = 0;
    }
}

// match: ?sub_16FD60@@YAXXZ @ 0x0016FD60
// sp-match: ?sub_16FD60@@YAXXZ @ 0x0010C540
void sub_16FD60()
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 3; var_4++)
        sub_16FAE0(var_4);
    sub_16FC80();
}

// match: ?sub_16FDA0@@YAPAUtype_4E51D0@@H@Z @ 0x0016FDA0
// sp-match: ?sub_16FDA0@@YAPAUtype_4E51D0@@H@Z @ 0x0010C560
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
type_4E51D0 *sub_16FDA0(RwInt32 arg_0)
{
    RwInt32 var_8;
    type_4E51D0 *l4;

    for (l4 = dword_4E5528[arg_0], var_8 = 0; var_8 < 8; var_8++, l4++)
    {
        if (!l4->unk_00.unk_00 && !l4->unk_00.unk_04)
            return l4;
    }
    return 0;
}

// match: ?sub_16FE00@@YAPAUtype_4E51D0@@HPAUtype_3DF8D8_04@@H@Z @ 0x0016FE00
// sp-match: ?sub_16FE00@@YAPAUtype_4E51D0@@HPAUtype_3DF8D8_04@@H@Z @ 0x0010C590
type_4E51D0 *sub_16FE00(RwInt32 arg_0, type_3DF8D8_04 *arg_4, RwInt32 arg_8)
{
    type_4E51D0 *var_4;

    var_4 = sub_16FDA0(arg_0);
    var_4->unk_00 = *arg_4;
    var_4->unk_08 = arg_8;
    return var_4;
}

// match: ?sub_16FE40@@YAHHI@Z @ 0x0016FE40
// sp-match: ?sub_16FE40@@YAHHI@Z @ 0x0010C5C0
RwInt32 sub_16FE40(RwInt32 arg_0, RwUInt32 arg_4)
{
    if (arg_4 & 0x1F)
        arg_4 = (arg_4 + 0x20) & ~0x1F;
    dword_4E54F4[arg_0].unk_00 = arg_4;
    dword_4E54F4[arg_0].unk_04 = 0;
    return 1;
}

// match: ?sub_16FE80@@YAHI@Z @ 0x0016FE80
// sp-match: ?sub_16FE80@@YAHI@Z @ 0x0010C5F0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Lays the three slots' heaps out one after another from arg_0 (none for
// 0).
RwInt32 sub_16FE80(RwUInt32 arg_0)
{
    RwInt32 var_8;
    RwUInt32 l4;

    l4 = 0;
    for (var_8 = 0; var_8 < 3; var_8++)
    {
        if (arg_0)
        {
            sub_16FE40(var_8, arg_0 + l4);
            l4 += dword_4E54F4[var_8].unk_08;
        }
        else
        {
            sub_16FE40(var_8, 0);
            dword_4E54F4[var_8].unk_08 = 0;
        }
    }
    return 1;
}

// match: ?sub_16FF00@@YAXI@Z @ 0x0016FF00
// sp-match: ?sub_16FF00@@YAXI@Z @ 0x0010C640
// Shares arg_0 bytes between the three slots' heaps (32-aligned).
void sub_16FF00(RwUInt32 arg_0)
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 3; var_4++)
        set_bank_size(var_4, ((RwInt32)arg_0 / 3) & ~0x1F);
}

// match: ?sub_16FF40@@YAHXZ @ 0x0016FF40
// sp-match: ?sub_16FF40@@YAHXZ @ 0x0010C670
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_16FF40()
{
    RwInt32 var_C;
    RwInt32 bp_8;
    RwInt32 bp_4;

    bp_4 = 0;
    for (bp_8 = 0; bp_8 < 3; bp_8++)
    {
        var_C = dword_4E54F4[bp_8].unk_08;
        bp_4 += var_C;
    }
    return bp_4;
}
