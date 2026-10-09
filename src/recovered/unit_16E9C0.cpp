// The clump banks (game/clumpbank.h).

#include "rw/ostypes.h"
#include "rw/bastream.h"
#include "rw/batextur.h"
#include "rw/bamemory.h"
#include "rw/rt2d.h"
#include "types/asynchload.h"
#include "game/clumpbank.h"
#include "game/functions.h"
#include "game/gameloop.h"
#include "game/data.h"
#include <string.h>
#include <stdio.h>

// Its data definitions (PLAN M5), in the image's address order.
// 0x003DCFE0
extern const RwReal flt_3DCFE0 = 16.666666f;
// 0x003DCFE4
/* Full-width (Shift-JIS) codes of the digits, capitals and small letters and the ASCII they
   start from; nothing in the image reads these tables. */
extern const RwUInt16 unk_3DCFE4[3][2] = { { 0x824F, 0x30 }, { 0x8260, 0x41 }, { 0x8281, 0x61 } };
// 0x003DCFF0
/* The full-width punctuation (0-terminated) */
extern const RwUInt16 unk_3DCFF0[34] =
{
    0x8140, 0x8149, 0x8168, 0x8194, 0x8190, 0x8193, 0x8195, 0x8166,
    0x8169, 0x816A, 0x8196, 0x817B, 0x8143, 0x817C, 0x8144, 0x815E,
    0x8146, 0x8147, 0x8171, 0x8181, 0x8172, 0x8148, 0x8197, 0x816D,
    0x818F, 0x816E, 0x814F, 0x8151, 0x8165, 0x816F, 0x8162, 0x8170,
    0x8150, 0x0000,
};
// 0x003DD038
/* and the ASCII punctuation it stands for */
extern const RwUInt16 unk_3DD038[34] =
{
    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
    0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F,
    0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40, 0x5B,
    0x5C, 0x5D, 0x5E, 0x5F, 0x60, 0x7B, 0x7C, 0x7D,
    0x7E, 0x00,
};
// 0x00429EA8
RwInt32 dword_429EA8 = -1;
// 0x004E51B8
type_4E51B8 dword_4E51B8;
// 0x004E51C0
#ifndef CODFH_PLAIN
RwUInt32 dword_4E51C0;
#endif
// 0x004E51C4
RwInt32 dword_4E51C4;
// 0x004E51C8
RwInt32 dword_4E51C8;
// End of its data definitions.

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3DCFE0@@3MB @ 0x003DCFE0
// match: ?unk_3DCFE4@@3QAY01$$CBGA @ 0x003DCFE4
// match: ?unk_3DCFF0@@3QBGB @ 0x003DCFF0
// match: ?unk_3DD038@@3QBGB @ 0x003DD038
// match: ??_C@_0BD@OMDOPMHC@Request?5to?5load?5?$CFs?$AA@ @ 0x003DD07C
// match: ??_C@_0P@INKEJNLP@cbank_?$CF02d?4bin?$AA@ @ 0x003DD090
// match: ??_C@_0IE@FLKMEHCP@File?5contained?5?$CFd?5clumps?4?5?$CFd?5loa@ @ 0x003DD0A0
// match: ??_C@_0BN@PDGMFJHE@?7?5MemoryHeap?5At?3?5?$CI?$CF08d?1?$CF08d?$CJ?$AA@ @ 0x003DD124
// match: ??_C@_0CO@JPKDKFLJ@?7Ignoring?5clump?3?5?$CI0x?$CFx?00x?$CFx?$CJ?4?5Al@ @ 0x003DD144
// match: ??_C@_0BN@COPCCLEM@?7Loading?5clump?5?3?5?$CI0x?$CFx?00x?$CFx?$CJ?$AA@ @ 0x003DD174
// match: ??_C@_0BH@GAPFBAHN@?7Stream?5Skip?3?5?$CFd?5bytes?$AA@ @ 0x003DD194
// match: ??_C@_0BG@HMJIFPOM@Clumps?2cbank_?$CF02d?4bin?$AA@ @ 0x003DD1AC
// match: ??_C@_0EK@KEHJNCCJ@A?5request?5to?5load?5cbank_?$CF02d?4bin@ @ 0x003DD1C8
// match: ??_C@_0CM@JNDEGAPM@Unloaded?5?$CFd?5GodIDs?4?5?$CFd?5slots?5are@ @ 0x003DD214
// match: ??_C@_0CB@GLOMJADP@?7Unloading?5GodID?5?$CI0x?$CF08x?00x?$CF08x?$CJ@ @ 0x003DD240
// match: ??_C@_0CC@COEAAMEI@Request?5to?5unload?5cbank_?$CF02d?4bin@ @ 0x003DD264
// match: .CRT$XCU+0 @ 0x00427134
// match: ?dword_429EA8@@3HA @ 0x00429EA8

// match: _$E1 @ 0x0030BCB0

// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).

type_4E51D0 dword_4E51D0[64];

// match: ?sub_16E9C0@@YAXXZ @ 0x0016E9C0
// sp-match: ?sub_16E9C0@@YAXXZ @ 0x0010BFB0
// Unloads the bank when an unload is pending (dword_4E51C8).
void sub_16E9C0()
{
    if (dword_4E51C8)
        sub_16EFD0();
}

// match: ?sub_16E9E0@@YAXH@Z @ 0x0016E9E0
// sp-match: ?sub_16E9E0@@YAXH@Z @ 0x0010C160
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Loads the bank arg_0 now (none for -1; nothing when it is loaded),
// unloading the one before.
void sub_16E9E0(RwInt32 arg_0)
{
    RwChar var_128[0x100];
    RwChar var_28[0x20];
    RwStream *l4;

    if (arg_0 == -1)
        return;
    if (sub_16EE80(arg_0))
        return;
    sub_16EFD0();
    sprintf(var_28, "cbank_%02d.bin", arg_0);
    sprintf(var_128, "Request to load %s", var_28);
#ifndef CODFH_SP
    sub_19A750(var_128);
#endif
    sub_16EDB0(var_128, 0x100, arg_0);
    l4 = RwStreamOpen(rwSTREAMFILENAME, rwSTREAMREAD, var_128);
    if (l4)
    {
        sub_16EAE0(l4, arg_0);
        RwStreamClose(l4, 0);
    }
}

// match: ?sub_16EAB0@@YAXH@Z @ 0x0016EAB0
// sp-match: ?sub_16EAB0@@YAXH@Z @ 0x0010C210
void sub_16EAB0(RwInt32 arg_0)
{
    if (arg_0 == -1)
        return;
    if (sub_16EE80(arg_0))
        return;
    sub_16EFD0();
    sub_16E9E0(arg_0);
}

// match: ?sub_16EAE0@@YAXPAURwStream@@H@Z @ 0x0016EAE0
// sp-match: ?sub_16EAE0@@YAXPAURwStream@@H@Z @ 0x0010BFC0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Reads the bank arg_4 from the stream arg_0: its directory, then each
// clump not already made (a kind-3 object in the bank's heap, its keys
// recorded through sub_16ED90), skipping the data of those that are.
void sub_16EAE0(RwStream *arg_0, RwInt32 arg_4)
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
#ifndef CODFH_SP
                sub_19A750("\tStream Skip: %d bytes", frm_24);
#endif
                RwStreamSkip(arg_0, frm_24);
                frm_24 = 0;
            }
#ifndef CODFH_SP
            sub_19A750("\tLoading clump : (0x%x,0x%x)", m_18->unk_00.unk_00, m_18->unk_00.unk_04);
#endif
            RwStreamRead(arg_0, &var_40, sizeof(var_40));
            RtlEnterCriticalSection(&dword_44BFB8);
            sub_16F250(&var_40.unk_0C.unk_04, 3);
            ebp_14 = (type_16EAE0_obj *)sub_199010(&var_40.unk_0C.unk_04, 3);
            ebp_14->unk_0C = 2;
            ebp_14->unk_10.unk_00 = &dword_4E51B8;
            ebp_14->unk_10.set_unk_0C(sub_16ED90, 0);
            RtlLeaveCriticalSection(&dword_44BFB8);
            ebp_14->vf_000(arg_0, &var_40);
            RtlEnterCriticalSection(&dword_44BFB8);
            sub_198FE0((type_3DF8D8_base *)((type_199010 *)ebp_14));
            l1C++;
            RtlLeaveCriticalSection(&dword_44BFB8);
        }
        else
        {
#ifndef CODFH_SP
            sub_19A750("\tIgnoring clump: (0x%x,0x%x). Already Loaded!", m_18->unk_00.unk_00,
                       m_18->unk_00.unk_04);
#endif
            frm_24 += m_18->unk_08;
        }
#ifndef CODFH_SP
        sub_19A750("\t MemoryHeap At: (%08d/%08d)", dword_4E51B8.unk_04, dword_4E51B8.unk_08);
#endif
        m_18++;
        lv_10--;
    }
#ifndef CODFH_SP
    sub_19A750("File contained %d clumps. %d loaded with a total mem footprint of %d bytes. %d slots are still "
               "available.  %d bytes are still free.",
               var_48.unk_00, l1C, dword_4E51B8.unk_04, sub_16EF70(), dword_4E51B8.unk_08 - dword_4E51B8.unk_04);
#endif
    dword_4E51C4 = arg_4;
    if (frm_24)
    {
        RwStreamSkip(arg_0, frm_24);
        frm_24 = 0;
    }
    if (bp_4)
        RwFree(bp_4);
}

// match: ?sub_16ED90@@YAPAUtype_4E51D0@@PAXPAUtype_3DF8D8_04@@H@Z @ 0x0016ED90
// sp-match: ?sub_16ED90@@YAPAUtype_4E51D0@@PAXPAUtype_3DF8D8_04@@H@Z @ 0x0010BF90
type_4E51D0 *sub_16ED90(void *arg_0, type_3DF8D8_04 *arg_4, RwInt32 arg_8)
{
    return sub_16F250(arg_4, arg_8);
}

// match: ?sub_16EDB0@@YAXPADHH@Z @ 0x0016EDB0
// sp-match: ?sub_16EDB0@@YAXPADHH@Z @ 0x0010BC50
// The path of the bank arg_8's file into arg_0 (arg_4 bytes).
void sub_16EDB0(RwChar *arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    RwChar var_108[0x100];
    RwChar var_308[0x200];

    sprintf(var_308, "Clumps\\cbank_%02d.bin", arg_8);
    sub_D7F40(var_108, var_308);
    sub_D7F20(var_308, var_108);
    memset(arg_0, 0, arg_4);
    strncpy(arg_0, var_308, strlen(var_308) < (RwUInt32)arg_4 ? strlen(var_308) : arg_4 - 1);
}

// match: ?sub_16EE80@@YAHH@Z @ 0x0016EE80
// sp-match: ?sub_16EE80@@YAHH@Z @ 0x0010BD20
RwInt32 sub_16EE80(RwInt32 arg_0)
{
    if (dword_4E51C4 == arg_0)
        return 1;
    return 0;
}

// match: ?sub_16EEA0@@YAHXZ @ 0x0016EEA0
// sp-match: ?sub_16EEA0@@YAHXZ @ 0x0010BD40
RwInt32 sub_16EEA0()
{
    return dword_4E51C4 != -1;
}

// match: ?sub_16EEC0@@YAXH@Z @ 0x0016EEC0
// sp-match: ?sub_16EEC0@@YAXH@Z @ 0x0010BD50
void sub_16EEC0(RwInt32 arg_0)
{
    RwChar var_24[0x20];

    if (sub_16EE80(arg_0))
    {
#ifndef CODFH_SP
        sub_19A750("A request to load cbank_%02d.bin is ignored because it is already loaded!", arg_0);
#endif
        return;
    }
    sprintf(var_24, "cbank_%02d.bin", arg_0);
    if (sub_81FB0(3, var_24, arg_0))
        return;
    if (sub_82020(3, arg_0))
        return;
    sub_82130();
#ifndef CODFH_SP
    sub_19A750("Request to load %s", var_24);
#endif
    sub_81EB0(3, var_24, arg_0);
}

// match: ?sub_16EF70@@YAHXZ @ 0x0016EF70
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The key slots still free.
RwInt32 sub_16EF70()
{
    RwInt32 var_C;
    type_4E51D0 *bp_8;
    RwInt32 bp_4;

    bp_4 = 0;
    for (bp_8 = dword_4E51D0, var_C = 0; var_C < 64; var_C++, bp_8++)
    {
        if (!bp_8->unk_00.unk_00 || !bp_8->unk_00.unk_04)
            bp_4++;
    }
    return bp_4;
}

// match: ?sub_16EFD0@@YAXXZ @ 0x0016EFD0
// sp-match: ?sub_16EFD0@@YAXXZ @ 0x0010BDD0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Unloads the bank: every key it made, kind by kind (6, 7, then 3), and
// empties its heap and table.
void sub_16EFD0()
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
    if (dword_4E51C4 != -1)
    {
#ifndef CODFH_SP
        sub_19A750("Request to unload cbank_%02d.bin\n", dword_4E51C4);
#endif
        while (*ebp_14)
        {
            for (var_20 = dword_4E51D0, var_24 = 0; var_24 < 64; var_24++, var_20++)
            {
                l1C = (type_16EAE0_obj *)sub_198710(&var_20->unk_00);
                if (l1C && var_20->unk_08 == *ebp_14)
                {
                    sub_D61F0(&var_20->unk_00);
                    if (var_20->unk_08 == 7)
                    {
                        RwTexDictionary *var_28 = l1C->unk_24;

                        if (var_28)
                            RwTexDictionaryDestroy(var_28);
                    }
                    sub_198F00(&var_20->unk_00);
                    m_18++;
#ifndef CODFH_SP
                    sub_19A750("\tUnloading GodID (0x%08x,0x%08x)", var_20->unk_00.unk_00, var_20->unk_00.unk_04);
#endif
                    var_20->unk_00.unk_00 = 0;
                    var_20->unk_00.unk_04 = 0;
                    var_20->unk_08 = 0;
                }
            }
            ebp_14++;
        }
#ifndef CODFH_SP
        sub_19A750("Unloaded %d GodIDs. %d slots are available.", m_18, sub_16EF70());
#endif
        dword_4E51B8.unk_04 = 0;
    }
    dword_4E51C4 = -1;
    dword_4E51C8 = 0;
    memset(dword_4E51D0, 0, sizeof(dword_4E51D0));
}

// match: ?sub_16F160@@YAXXZ @ 0x0016F160
// sp-match: ?sub_16F160@@YAXXZ @ 0x0010BEB0
void sub_16F160()
{
    memset(dword_4E51D0, 0, sizeof(dword_4E51D0));
    dword_4E51C4 = -1;
    dword_429EA8 = -1;
    dword_4E51B8.unk_00 = 0;
    dword_4E51B8.unk_04 = 0;
    dword_4E51B8.unk_08 = 0;
    dword_4E51C8 = 0;
}

// match: ?sub_16F1C0@@YAXXZ @ 0x0016F1C0
// sp-match: ?sub_16F1C0@@YAXXZ @ 0x0010BEF0
void sub_16F1C0()
{
    sub_16EFD0();
}

// match: ?sub_16F1D0@@YAXXZ @ 0x0016F1D0
// sp-match: ?sub_16F1D0@@YAXXZ @ 0x0010BF00
void sub_16F1D0()
{
    sub_16EFD0();
    dword_4E51B8.unk_00 = 0;
    dword_4E51B8.unk_04 = 0;
    dword_4E51B8.unk_08 = 0;
}

// match: ?sub_16F200@@YAPAUtype_4E51D0@@XZ @ 0x0016F200
// sp-match: ?sub_16F200@@YAPAUtype_4E51D0@@XZ @ 0x0010BF20
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
type_4E51D0 *sub_16F200()
{
    RwInt32 var_8;
    type_4E51D0 *l4;

    for (l4 = dword_4E51D0, var_8 = 0; var_8 < 64; var_8++, l4++)
    {
        if (!l4->unk_00.unk_00 && !l4->unk_00.unk_04)
            return l4;
    }
    return 0;
}

// match: ?sub_16F250@@YAPAUtype_4E51D0@@PAUtype_3DF8D8_04@@H@Z @ 0x0016F250
// sp-match: ?sub_16F250@@YAPAUtype_4E51D0@@PAUtype_3DF8D8_04@@H@Z @ 0x0010BF40
type_4E51D0 *sub_16F250(type_3DF8D8_04 *arg_0, RwInt32 arg_4)
{
    type_4E51D0 *var_4;

    var_4 = sub_16F200();
    var_4->unk_00 = *arg_0;
    var_4->unk_08 = arg_4;
    return var_4;
}

// match: ?sub_16F280@@YAHI@Z @ 0x0016F280
// sp-match: ?sub_16F280@@YAHI@Z @ 0x0010BF60
// Sets the heap's base to arg_0, 32-aligned.
RwInt32 sub_16F280(RwUInt32 arg_0)
{
    if (arg_0 & 0x1F)
        arg_0 = (arg_0 + 0x20) & ~0x1F;
    dword_4E51B8.unk_00 = arg_0;
    dword_4E51B8.unk_04 = 0;
    return 1;
}


#ifdef CODFH_PLAIN
// Plain builds (tools/plainbuild.py): the variables below are a second name for this unit's
// variables' bytes in the image (tools/session/overlapvars.py --aliases); only the placement
// link gives them one storage, so any other link binds them here at the image offset.
// (bound at start-up: the library initialization area runs before every game constructor)
#pragma warning(disable: 4073)
#pragma init_seg(lib)
// 0x004E51C0: dword_4E51B8 + 0x8
RwUInt32 &dword_4E51C0 = *(RwUInt32 *)((RwUInt8 *)&dword_4E51B8 + 0x8);
#endif
