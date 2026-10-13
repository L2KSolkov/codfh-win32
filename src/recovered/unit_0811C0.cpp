// The asynchronous loading queue ("AsynchLoadingQueue"): a ring of load
// requests, the thread that loads them and the locks around both. The file's
// original name is not recovered (M1), so it is named for its start address.

#include <string.h>

#include "rw/ostypes.h"
#include "game/functions.h"
#include "types/asynchload.h"
#include "types/animbank.h"
#include "rw/bastream.h"
#ifdef CODFH_WIN32
// (as windows.h declares it: kernel32's)
extern "C" __declspec(dllimport) void __stdcall Sleep(RwUInt32 dwMilliseconds);
#endif

// Its data definitions (PLAN M5), in the image's address order.
// 0x003D3D64
extern const RwReal flt_3D3D64 = 16.666666f;
// 0x00428E14
RwInt32 dword_428E14 = 1;
// 0x00428E18
RwInt32 dword_428E18 = -1;
// 0x00428E1C
RwInt32 dword_428E1C = 4096;
// 0x00428E20
RwInt32 dword_428E20 = -1;
// 0x00428E24
RwInt32 dword_428E24 = 1;
// 0x0044BA98
RTL_CRITICAL_SECTION dword_44BA98;
// 0x0044BAB4
RTL_CRITICAL_SECTION dword_44BAB4;
// 0x0044BAD0
RwInt32 dword_44BAD0;
// 0x0044BAD4
RwUInt32 dword_44BAD4;
// 0x0044BAD8
type_44BAD8 dword_44BAD8[16];
// 0x0044BF98
RwInt32 dword_44BF98;
// 0x0044BF9C
RTL_CRITICAL_SECTION dword_44BF9C;
// 0x0044BFB8
RTL_CRITICAL_SECTION dword_44BFB8;
// 0x0044BFD4
RTL_CRITICAL_SECTION dword_44BFD4;
// 0x0044BFF0
RwInt32 dword_44BFF0;
// 0x0044BFF4
RwUInt8 byte_44BFF4;
// 0x0044BFF8
type_44BAD8 *dword_44BFF8;
// 0x0044BFFC
type_44BAD8 *dword_44BFFC;
// 0x0044C000
RwInt32 dword_44C000;
// 0x0044C004
RwInt32 dword_44C004;
// 0x0044C008
void *(*dword_44C008)(size_t size, RwUInt32 hint);
// 0x0044C00C
void *(*dword_44C00C)(size_t size, RwUInt32 hint);
// 0x0044C010
void *(*dword_44C010)(size_t numObj, size_t sizeObj, RwUInt32 hint);
// 0x0044C014
void *(*dword_44C014)(size_t numObj, size_t sizeObj, RwUInt32 hint);
// 0x0044C018
void *(*dword_44C018)(void *mem, size_t newSize, RwUInt32 hint);
// 0x0044C01C
void *(*dword_44C01C)(void *mem, size_t newSize, RwUInt32 hint);
// 0x0044C020
RwInt32 dword_44C020;
// 0x0044C028
RwInt32 dword_44C028;
// 0x0044C02C
RTL_CRITICAL_SECTION dword_44C02C;
// 0x0044C048
RTL_CRITICAL_SECTION dword_44C048;
// 0x0044C064
RwInt32 dword_44C064;
// 0x0044C068
RTL_CRITICAL_SECTION dword_44C068;
// 0x0044C084
RTL_CRITICAL_SECTION dword_44C084;
// End of its data definitions.


// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).
type_84230 dword_4AF038[0x14];
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3D3D64@@3MB @ 0x003D3D64
// match: ??_C@_0CM@EHEMJEM@AsynchLoadingQueue?3?3ShutdownClas@ @ 0x003D3D68
// match: ??_C@_0EC@KLOAIGFO@AsynchLoadingQueue?3?3ShutdownClas@ @ 0x003D3D98
// match: ??_C@_0EC@PLHEPBPA@AsynchLoadingQueue?3?3ShutdownClas@ @ 0x003D3DE0
// match: ??_C@_0CO@MFONBFDA@AsynchLoadingQueue?3?3ShutdownClas@ @ 0x003D3E24
// match: ??_C@_0DN@MHOIMLEN@bad?5section?5asynch?5loading?5queue@ @ 0x003D3E54
// match: ??_C@_0CG@ODLNPGJE@?$CK?$CK?$CK?$CK?6?$CK?$CK?$CK?$CK?5DONE?5?$CFs?5?$CFs?5load?5at?5?$CFd?6@ @ 0x003D3E94
// match: ??_C@_0P@KPECCJIM@AnimBankLoaded?$AA@ @ 0x003D3EBC
// match: ??_C@_0BP@HIKNKGCD@Finished?5Loading?5AnimBank?4?4?4?4?6?$AA@ @ 0x003D3ECC
// match: ??_C@_0BI@EICIBJFM@Loading?5anim?5bank?3?5?$CFs?$CB?6?$AA@ @ 0x003D3EEC
// match: ??_C@_0CB@ENEGGMEB@Finished?5Loading?5clump?5bank?4?4?4?4?6@ @ 0x003D3F04
// match: ??_C@_0BA@JMNDOOKB@ClumpBankLoaded?$AA@ @ 0x003D3F28
// match: ??_C@_0BN@CKDOBBOI@Loading?5clump?5bank?5file?5?$CFs?$CB?6?$AA@ @ 0x003D3F38
// match: ??_C@_0CJ@FJCHHHEF@?$CK?$CK?$CKERROR?3?5unable?5to?5open?5clump?5f@ @ 0x003D3F58
// match: ??_C@_0CN@MKJKFIGE@Finished?5Loading?5weapon?5clump?5ba@ @ 0x003D3F84
// match: ??_C@_0CE@HJAEHCKD@Loading?5weapon?5clump?5bank?5file?5?$CF@ @ 0x003D3FB4
// match: ??_C@_0BN@ODBGODEG@Section?5?$CFd?5finished?5loading?6?$AA@ @ 0x003D3FD8
// match: ??_C@_0BP@GNJHEDOO@Aborted?5load?5of?5Section?5?$CFd?4?4?4?6?$AA@ @ 0x003D3FF8
// match: ??_C@_01EEMJAFIK@?6?$AA@ @ 0x003D4018
// match: ??_C@_03JDANDILB@?$CFd?5?$AA@ @ 0x003D401C
// match: ??_C@_0O@GDGCLCDG@Now?5loading?3?5?$AA@ @ 0x003D4020
// match: ??_C@_0BM@FNLAMAGD@Section?5?$CFd?5started?5loading?6?$AA@ @ 0x003D4030
// match: ??_C@_0CH@OIHBABLC@?$CK?$CK?$CK?$CK?6?$CK?$CK?$CK?$CK?5BEGIN?5?$CFs?5?$CFs?5load?5at?5?$CFd@ @ 0x003D404C
// match: ??_C@_04OHJIHAFH@None?$AA@ @ 0x003D4074
// match: ??_C@_0L@PKOIGJBH@eAnimGroup?$AA@ @ 0x003D407C
// match: ??_C@_0P@FAOMPCCN@eLoadSoundBank?$AA@ @ 0x003D4088
// match: ??_C@_0L@BKDLMKGD@eClumpBank?$AA@ @ 0x003D4098
// match: ??_C@_08HBMMPBJL@eSection?$AA@ @ 0x003D40A4
// match: ??_C@_0DA@FCGPBNDO@?$CK?$CK?$CK?$CK?6?$CK?$CK?$CK?$CK?5Added?5?$CFs?5to?5loading?5qu@ @ 0x003D40B0
// match: ??_C@_0CC@IDKDNMNL@The?5asynch?5loading?5queue?5is?5FULL@ @ 0x003D40E0
// match: ??_C@_0CF@OFLCDGPC@Canceling?5queued?5load?5of?5section@ @ 0x003D4104
// match: ??_C@_0DH@DFADOHAL@?$CIAbortUnneededSections?4?4?4?$CJAborti@ @ 0x003D412C
// match: ??_C@_0DN@IIFODILO@?$CIAbortPendingClumpBanks?4?4?4?$CJCance@ @ 0x003D4164
// match: ??_C@_0CD@PELAHCAK@Loading?5thread?5finished?5loading?4@ @ 0x003D41A4
// match: ??_C@_0CI@FLOMKPBC@Waiting?5for?5loading?5thread?5to?5fi@ @ 0x003D41C8
// match: ??_C@_0DG@BCOKMPNN@?$CIWaitForCurrentLoadToFinish?4?4?4?$CJA@ @ 0x003D41F0
// match: ??_C@_0FK@KHMOEHGO@XBOXDestroyThread?3?3?5Done?5waiting@ @ 0x003D4228
// match: ??_C@_0DK@EJIMOBAC@XBOXDestroyThread?3?3?5Waiting?5for?5@ @ 0x003D4284
// match: .CRT$XCU+0 @ 0x00426DF8
// match: ?dword_428E14@@3HA @ 0x00428E14
// match: ?dword_428E18@@3HA @ 0x00428E18
// match: ?dword_428E1C@@3HA @ 0x00428E1C
// match: ?dword_428E20@@3HA @ 0x00428E20
// match: ?dword_428E24@@3HA @ 0x00428E24

// match: _$E1 @ 0x00309C40
// match: ?sub_811C0@@YAXXZ @ 0x000811C0
// sp-match: ?sub_811C0@@YAXXZ @ 0x000692D0

void sub_811C0()
{
    type_44BAD8 *var_4;

    sub_82370();
#if defined(CODFH_SP) && !defined(CODFH_WIN32)
    // shape: SP 0x692D0 pins the import read, then the ready store, before
    // the first argument push; MP 0x811C0 uses the original import calls.
    sp_queue_initialize_function initialize = sp_RtlInitializeCriticalSection_import;
    _ReadWriteBarrier();
    dword_44C004 = 1;
    _WriteBarrier();
    initialize(&dword_44BAB4);
    initialize(&dword_44BFB8);
    initialize(&dword_44BF9C);
    initialize(&dword_44BA98);
    initialize(&dword_44BFD4);
#else
    dword_44C004 = 1;
    RtlInitializeCriticalSection(&dword_44BAB4);
    RtlInitializeCriticalSection(&dword_44BFB8);
    RtlInitializeCriticalSection(&dword_44BF9C);
    RtlInitializeCriticalSection(&dword_44BA98);
    RtlInitializeCriticalSection(&dword_44BFD4);
#endif
    dword_44BF98 = 0;
    dword_44BFF0 = 0;
    sub_2A7870(&dword_44BFD4);
    dword_44C000 = 0;
    dword_44C008 = 0;
    dword_44C00C = 0;
    dword_44C010 = 0;
    dword_44C014 = 0;
    dword_44C018 = 0;
    dword_44C01C = 0;
    for (var_4 = dword_44BAD8; var_4 < &dword_44BAD8[16]; var_4++)
    {
        var_4->unk_40 = -1;
        var_4->unk_48 = 0;
    }
    dword_44BFF8 = dword_44BAD8;
    dword_44BFFC = dword_44BAD8;
    dword_428E14 = 1;
    dword_44BAD0 = 0;
    dword_44BAD4 = sub_823D0(sub_81590);
    sub_19A750((void *)dword_44BAD4);
    sub_19A750((void *)sub_81E40);
    sub_822F0();
}

// match: ?sub_81300@@YAXXZ @ 0x00081300
// sp-match: ?sub_81300@@YAXXZ @ 0x000693C0
void sub_81300()
{
    sub_821C0();
}

// "AsynchLoadingQueue::ShutdownClass()".
// match: ?sub_81310@@YAXXZ @ 0x00081310
// sp-match: ?sub_81310@@YAXXZ @ 0x000693D0
void sub_81310()
{
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
    sub_19A750("AsynchLoadingQueue::ShutdownClass(): Begin...");
#endif
    sub_821C0();
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
    sub_19A750("AsynchLoadingQueue::ShutdownClass(): Unhooking VBlankInterrupt...");
#endif
    sub_19A750();
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
    sub_19A750("AsynchLoadingQueue::ShutdownClass(): Destroying loading thread...");
#endif
    sub_823F0(dword_44BAD4);
    dword_44C004 = 0;
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
    sub_19A750("AsynchLoadingQueue::ShutdownClass(): End...");
#endif
    sub_2A7870(0);
}

// match: ?sub_81380@@YAXXZ @ 0x00081380
// sp-match: ?sub_81380@@YAXXZ @ 0x00068BF0
void sub_81380()
{
    RwInt32 var_4;

    dword_428E14 = 0;
    sub_82310();
    sub_1B29D0(15);
    var_4 = 0;
    while (dword_4CF888)
    {
        sub_1B29D0(15);
        if (var_4++ > 30)
        {
            break;
        }
    }
    sub_822F0();
    dword_428E14 = 1;
}

#ifdef CODFH_SP
// Single player keeps every store to the state (SP 0x68CB6 stores 0 before it is
// overwritten) and stores var_4 before it (SP 0x68CDF): both are volatile there.
// asynchload.h declares the state plain, so this function reads it through a cast.
#define dword_44C020 (*(volatile RwInt32 *)&dword_44C020)
#endif
// match: ?sub_813E0@@YAXH@Z @ 0x000813E0
// sp-match: ?sub_813E0@@YAXH@Z @ 0x00068C50
void sub_813E0(RwInt32 arg_0)
{
#ifdef CODFH_SP
    volatile RwInt32 var_4;
#else
    RwInt32 var_4;
#endif
    RwMemoryFunctions *v8;
    type_44BAD8 *varC;

    var_4 = 0;
    v8 = RwOsGetMemoryInterface();
    dword_44C00C = v8->rwmalloc;
    dword_44C014 = v8->rwcalloc;
    dword_44C01C = v8->rwrealloc;
    if (dword_44C008)
    {
        if (v8->rwmalloc != dword_44C008 || v8->rwcalloc != dword_44C010 || v8->rwrealloc != dword_44C018)
        {
            v8->rwmalloc = dword_44C008;
            v8->rwcalloc = dword_44C010;
            v8->rwrealloc = dword_44C018;
        }
    }
    dword_44C020 = 0;
    if (arg_0)
    {
        var_4 = 1;
        dword_44C020 = 1;
        sub_81380();
    }
    else
    {
        for (varC = dword_44BAD8; varC < &dword_44BAD8[16]; varC++)
        {
            if (varC->unk_48)
            {
                var_4 = 1;
                dword_44C020 = 1;
                sub_81380();
                break;
            }
        }
    }
    if (var_4)
    {
        v8 = RwOsGetMemoryInterface();
        dword_44C008 = v8->rwmalloc;
        dword_44C010 = v8->rwcalloc;
        dword_44C018 = v8->rwrealloc;
        dword_44C020 = 2;
    }
    else
    {
        dword_44C020 = 3;
    }
    if (dword_44C00C)
    {
        if (v8->rwmalloc != dword_44C00C || v8->rwcalloc != dword_44C014 || v8->rwrealloc != dword_44C01C)
        {
            v8->rwmalloc = dword_44C00C;
            v8->rwcalloc = dword_44C014;
            v8->rwrealloc = dword_44C01C;
            dword_44C020 = 4;
        }
    }
    v8 = RwOsGetMemoryInterface();
}
#ifdef CODFH_SP
#undef dword_44C020
#endif

#ifdef CODFH_SP
// Single player's debug print is an empty inline: its format text is gone, but its
// arguments are still evaluated (sub_81590 keeps the type name copies and the time
// reads, SP 0x68DDC-0x68E9B, 0x69126).
static inline void sp_debug_print(const RwChar *, ...) {}
#endif
// The loading thread.
// match: ?sub_81590@@YGIPAX@Z @ 0x00081590
// sp-match: ?sub_81590@@YGIPAX@Z @ 0x00068D80
RwUInt32 __stdcall sub_81590(void *arg_0)
{
    type_173F50 *var154;
    type_449C94 *var_150;
    RwStream *slot_14C;
    RwInt32 var_148;
    RwInt32 l144;
    RwStream *var_140;
    type_44BAD8 *local_13C;
    RwInt32 lv_138;
    type_44BAD8 *y134;
    type_44BAD8 *lcl_130;
    RwChar l12C[0x20];
    type_44BAD8 *p10C;
    RwChar var_108[0x100];

    while (dword_44C004 == 1)
    {
        p10C = dword_44BFF8;
        if (p10C && p10C->unk_48)
        {
            switch (p10C->unk_40)
            {
            case 0:
                strcpy(l12C, "eSection");
                break;
            case 3:
                strcpy(l12C, "eClumpBank");
                break;
            case 1:
                strcpy(l12C, "eLoadSoundBank");
                break;
            case 2:
                strcpy(l12C, "eAnimGroup");
                break;
            default:
                strcpy(l12C, "None");
                break;
            }
#if defined(CODFH_SP) && !defined(CODFH_SP_LOGS)
            sp_debug_print("", l12C, p10C->unk_00, RWS::Time::GetTime());
#else
            sub_19A750("****\n**** BEGIN %s %s load at %d\n****\n", l12C, p10C->unk_00, RWS::Time::GetTime());
#endif
#ifdef CODFH_EXTRA_LOGS // (the GameCube build, main.dol 0x8006A6E4: the request's start time and kind)
            RwUInt32 extra_start = RWS::Time::GetTime();
            RwInt32 extra_type = p10C->unk_40;
#endif
            switch (p10C->unk_40)
            {
            case 0:
                dword_428E20 = 0;
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
                sub_19A750("Section %d started loading\n", p10C->unk_44);
#endif
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
                sub_19A750("Now loading: ");
#endif
                lcl_130 = dword_44BFF8;
                while (lcl_130 != dword_44BFFC)
                {
                    if (lcl_130->unk_40 == 0 && lcl_130->unk_48)
                    {
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
                        sub_19A750("%d ", lcl_130->unk_44);
#endif
                    }
                    lcl_130++;
                    if (lcl_130 == &dword_44BAD8[16])
                    {
                        lcl_130 = dword_44BAD8;
                    }
                }
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
                sub_19A750("\n");
#endif
                setLoadingSection_((RwInt16)p10C->unk_44);
                sub_D8230(p10C->unk_44);
                dword_44BF98 = 1;
                RtlEnterCriticalSection(&dword_44BAB4);
                word_429EAC = -1;
                if (dword_44C000)
                {
                    lv_138 = sub_1745F0(p10C->unk_44);
                    sub_174030((RwUInt16)lv_138, 1);
                    dword_44C000 = 0;
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
                    sub_19A750("Aborted load of Section %d...\n", p10C->unk_44);
#endif
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
                    sub_19A750("Now loading: ");
#endif
                    y134 = dword_44BFF8;
                    y134++;
                    if (y134 == &dword_44BAD8[16])
                    {
                        y134 = dword_44BAD8;
                    }
                    while (y134 != dword_44BFFC)
                    {
                        if (y134->unk_40 == 0 && y134->unk_48)
                        {
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
                            sub_19A750("%d ", y134->unk_44);
#endif
                        }
                        y134++;
                        if (y134 == &dword_44BAD8[16])
                        {
                            y134 = dword_44BAD8;
                        }
                    }
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
                    sub_19A750("\n");
#endif
                }
                else
                {
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
                    sub_19A750("Section %d finished loading\n", p10C->unk_44);
#endif
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
                    sub_19A750("Now loading: ");
#endif
                    local_13C = dword_44BFF8;
                    local_13C++;
                    if (local_13C == &dword_44BAD8[16])
                    {
                        local_13C = dword_44BAD8;
                    }
                    while (local_13C != dword_44BFFC)
                    {
                        if (local_13C->unk_40 == 0 && local_13C->unk_48)
                        {
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
                            sub_19A750("%d ", local_13C->unk_44);
#endif
                        }
                        local_13C++;
                        if (local_13C == &dword_44BAD8[16])
                        {
                            local_13C = dword_44BAD8;
                        }
                    }
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
                    sub_19A750("\n");
#endif
                }
                p10C->unk_48 = 0;
                RtlLeaveCriticalSection(&dword_44BAB4);
                dword_44BF98 = 0;
                break;
            case 3:
                if (((p10C->unk_44 & 0x80000000) != 0) != 0)
                {
                    var_148 = (p10C->unk_44 & 0xFF00) >> 8;
                    l144 = p10C->unk_44 & 0xFF;
                    sub_16F770(var_108, 0x100, l144);
                    sub_19BB40(var_108, 1);
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
                    sub_19A750("Loading weapon clump bank file %s!\n", var_108);
#endif
                    sub_82350();
                    var_140 = RwStreamOpen(rwSTREAMFILENAME, rwSTREAMREAD, var_108);
                    sub_82360();
                    if (var_140)
                    {
                        sub_16F460(var_140, var_148, l144);
                        RwStreamClose(var_140, 0);
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
                        sub_19A750("Finished Loading weapon clump bank file....\n");
#endif
                    }
                    else
                    {
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
                        sub_19A750("***ERROR: unable to open clump file %s!\n", var_108);
#endif
                    }
                    sub_19BB40(var_108, 0);
                }
                else if (dword_4E5CC4)
                {
                    while (sub_16EEA0())
                    {
                        dword_4E51C8 = 1;
                    }
                    dword_4E51C8 = 0;
                    sub_16EDB0(var_108, 0x100, p10C->unk_44);
                    sub_19BB40(var_108, 1);
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
                    sub_19A750("Loading clump bank file %s!\n", var_108);
#endif
                    slot_14C = RwStreamOpen(rwSTREAMFILENAME, rwSTREAMREAD, var_108);
                    if (slot_14C)
                    {
                        sub_16EAE0(slot_14C, p10C->unk_44);
                        RwStreamClose(slot_14C, 0);
                        sub_6B5F0("ClumpBankLoaded", 0, 0, 0, 0, 0, 1, 0);
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
                        sub_19A750("Finished Loading clump bank....\n");
#endif
                    }
                    else
                    {
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
                        sub_19A750("***ERROR: unable to open clump file %s!\n", var_108);
#endif
                    }
                    sub_19BB40(var_108, 0);
                }
                break;
            case 1:
                if (dword_4B2068)
                {
                    sub_885B0(1);
                    break;
                }
                sub_82C70(&dword_4AF038[0].unk_00, 1);
                dword_4AF24C = 7;
                break;
            case 2:
                var_150 = (type_449C94 *)p10C->unk_44;
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
                sub_19A750("Loading anim bank: %s!\n", p10C->unk_00);
#endif
                sub_19BB40(p10C->unk_00, 1);
                sub_82350();
                sub_77540(p10C->unk_00, var_150->unk_08_s, var_150->unk_00, 1, 0);
                sub_82360();
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
                sub_19A750("Finished Loading AnimBank....\n");
#endif
                sub_6B5F0("AnimBankLoaded", 0, 0, 0, 0, 0, 1, 0);
                sub_19BB40(p10C->unk_00, 0);
                break;
            }
#if defined(CODFH_SP) && !defined(CODFH_SP_LOGS)
            sp_debug_print("", l12C, p10C->unk_00, RWS::Time::GetTime());
#else
            sub_19A750("****\n**** DONE %s %s load at %d\n****\n", l12C, p10C->unk_00, RWS::Time::GetTime());
#endif
#ifdef CODFH_EXTRA_LOGS // (the GameCube build, main.dol 0x8006AAE8)
            sub_19A750("Done reading type %d time=%.2f\n", extra_type,
                       (RwReal)(RWS::Time::GetTime() - extra_start) * 0.001f);
#endif
            dword_44BF98 = 1;
            RtlEnterCriticalSection(&dword_44BAB4);
            p10C->unk_48 = 0;
            dword_44C000 = 0;
            while (dword_44BFF8 != dword_44BFFC)
            {
                dword_44BFF8++;
                if (dword_44BFF8 == &dword_44BAD8[16])
                {
                    dword_44BFF8 = dword_44BAD8;
                }
                if (dword_44BFF8->unk_48)
                {
                    break;
                }
            }
            if (dword_44BFF8->unk_48 && dword_44BFF8->unk_40 == 0)
            {
                var154 = (type_173F50 *)sub_173F50((RwUInt16)dword_44BFF8->unk_44);
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
                if (!var154)
                {
                    sub_19A750("bad section asynch loading queue stuff thingy dohicky mabob\n");
                }
#endif
                var154->set_unk_08((RwInt16)dword_44BFF8->unk_44);
            }
            RtlLeaveCriticalSection(&dword_44BAB4);
            dword_44BF98 = 0;
        }
        if (!p10C || !p10C->unk_48)
        {
            dword_428E14 = 1;
#ifdef CODFH_WIN32
            // (the port: nothing queued, a millisecond's rest. On the Xbox the lowest priority and
            // the render's suspending it kept this loop to idle time on the one core; a PC gives
            // it a core of its own, which it spun at 100%.)
            Sleep(1);
#endif
        }
    }
    dword_44BF98 = 1;
    RtlEnterCriticalSection(&dword_44BAB4);
    dword_44C004 = 2;
    RtlLeaveCriticalSection(&dword_44BAB4);
    dword_44BF98 = 0;
    ExitThread(1);
}

// match: ?sub_81E40@@YAXPAX@Z @ 0x00081E40
// sp-match: ?sub_81E40@@YAXPAX@Z @ 0x00068950
void sub_81E40(void *arg_0)
{
    byte_44BFF4 = 1;
    byte_44BFF4 = 0;
    if (dword_428E14)
    {
        sub_19A750(arg_0);
    }
    else
    {
        dword_428E14 = 1;
        if (sub_170ED0(dword_44C028) != dword_44C028)
        {
            dword_428E14 = 0;
        }
        sub_19A750(arg_0);
    }
}

// match: ?sub_81EB0@@YAXHPBDH@Z @ 0x00081EB0
// sp-match: ?sub_81EB0@@YAXHPBDH@Z @ 0x00069230
void sub_81EB0(RwInt32 arg_0, const RwChar *arg_4, RwInt32 arg_8)
{
    RwInt32 var_4;

#if defined(CODFH_SP) && !defined(CODFH_SP_LOGS)
    // Single player compiles the print out but still reads the time (SP 0x69230).
    RWS::Time::GetTime();
#else
    sub_19A750("****\n**** Added %s to loading queue at %d\n****\n", arg_4, RWS::Time::GetTime());
#endif
    var_4 = arg_0;
    sub_81EF0(arg_0, arg_4, arg_8);
}

// match: ?sub_81EF0@@YAXHPBDH@Z @ 0x00081EF0
void sub_81EF0(RwInt32 arg_0, const RwChar *arg_4, RwInt32 arg_8)
{
    strncpy(dword_44BFFC->unk_00, arg_4, 0x40);
    dword_44BFFC->unk_00[0x3F] = 0;
    dword_44BFFC->unk_40 = arg_0;
    dword_44BFFC->unk_44 = arg_8;
    dword_44BF98 = 1;
    RtlEnterCriticalSection(&dword_44BAB4);
    dword_44BFFC->unk_48 = 1;
    dword_44BFFC++;
    if (dword_44BFFC == &dword_44BAD8[16])
    {
        dword_44BFFC = dword_44BAD8;
    }
    RtlLeaveCriticalSection(&dword_44BAB4);
    dword_44BF98 = 0;
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS) // MP only: single player compiles the debug print out (the text is not in default.xbe)
    if (dword_44BFFC == dword_44BFF8)
    {
        sub_19A750("The asynch loading queue is FULL!");
    }
#endif
}

// match: ?sub_81FB0@@YAHHPBDH@Z @ 0x00081FB0
// sp-match: ?sub_81FB0@@YAHHPBDH@Z @ 0x00068A30
RwInt32 sub_81FB0(RwInt32 arg_0, const RwChar *arg_4, RwInt32 arg_8)
{
    type_44BAD8 *var_4;

    for (var_4 = dword_44BAD8; var_4 < &dword_44BAD8[16]; var_4++)
    {
        if (var_4->unk_48 && var_4->unk_40 == arg_0 && var_4->unk_44 == arg_8 && !_strcmpi(var_4->unk_00, arg_4))
        {
            return 1;
        }
    }
    return 0;
}

// match: ?sub_82020@@YAHHH@Z @ 0x00082020
// sp-match: ?sub_82020@@YAHHH@Z @ 0x00068A90
RwInt32 sub_82020(RwInt32 arg_0, RwInt32 arg_4)
{
    RwInt32 var_4;

    if (dword_44BFF8 && dword_44BFF8->unk_48 && dword_44BFF8->unk_40 == arg_0 && dword_44BFF8->unk_44 == arg_4)
    {
        var_4 = 1;
    }
    else
    {
        var_4 = 0;
    }
    return var_4;
}

// "(AbortUnneededSections...)".
// match: ?sub_82070@@YAXHHHH@Z @ 0x00082070
// sp-match: ?sub_82070@@YAXHHHH@Z @ 0x00068AC0
void sub_82070(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C)
{
    type_44BAD8 *var_4;
    RwInt32 local_8;

    for (var_4 = dword_44BAD8; var_4 < &dword_44BAD8[16]; var_4++)
    {
        if (var_4->unk_40 == 0 && var_4->unk_48)
        {
            local_8 = var_4->unk_44;
            if (local_8 != arg_0 && local_8 != arg_4 && local_8 != arg_8 && local_8 != arg_C)
            {
                if (sub_82020(0, local_8))
                {
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
                    sub_19A750("(AbortUnneededSections...)Aborting load of section %d\n", local_8);
#endif
                    dword_44C000 = 1;
                }
                else
                {
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
                    sub_19A750("Canceling queued load of section %d\n", local_8);
#endif
                    var_4->unk_48 = 0;
                }
            }
        }
    }
}

// "(AbortPendingClumpBanks...)".
// match: ?sub_82130@@YAXXZ @ 0x00082130
// sp-match: ?sub_82130@@YAXXZ @ 0x00068B30
void sub_82130()
{
    type_44BAD8 *var_4;

    for (var_4 = dword_44BAD8; var_4 < &dword_44BAD8[16]; var_4++)
    {
        if (var_4->unk_40 == 3 && var_4->unk_48 && ((var_4->unk_44 & 0x80000000) != 0) == 0
            && !sub_82020(var_4->unk_40, var_4->unk_44))
        {
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
            sub_19A750("(AbortPendingClumpBanks...)Canceling queued load of bank %d\n", var_4->unk_44);
#endif
            var_4->unk_48 = 0;
        }
    }
}

// "(WaitForCurrentLoadToFinish...)".
// match: ?sub_821C0@@YAXXZ @ 0x000821C0
// sp-match: ?sub_821C0@@YAXXZ @ 0x00069240
void sub_821C0()
{
    type_44BAD8 *var_4;

    dword_44BF98 = 1;
    RtlEnterCriticalSection(&dword_44BAB4);
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
    sub_19A750("(WaitForCurrentLoadToFinish...)Aborting all sections\n");
#endif
    for (var_4 = dword_44BAD8; var_4 < &dword_44BAD8[16]; var_4++)
    {
        if (var_4 != dword_44BFF8)
        {
            var_4->unk_48 = 0;
        }
    }
    RtlLeaveCriticalSection(&dword_44BAB4);
    dword_44BF98 = 0;
    if (dword_44BFF8 && dword_44BFF8->unk_48)
    {
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
        sub_19A750("Waiting for loading thread to finish...");
#endif
        while (dword_44BFF8->unk_48)
        {
            sub_813E0(0);
            sub_16E9C0();
        }
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
        sub_19A750("Loading thread finished loading...");
#endif
    }
    dword_44C000 = 0;
    dword_44BFF8 = dword_44BAD8;
    dword_44BFFC = dword_44BAD8;
}

// match: ?sub_822A0@@YAXXZ @ 0x000822A0
void sub_822A0()
{
    if (dword_44BFF8 && dword_44BFF8->unk_48)
    {
        sub_19A750("Waiting for loading thread to finish...");
        while (dword_44BFF8->unk_48)
        {
            sub_813E0(0);
            sub_16E9C0();
        }
        sub_19A750("Loading thread finished loading...");
    }
}

// match: ?sub_822F0@@YAXXZ @ 0x000822F0
// sp-match: ?sub_822F0@@YAXXZ @ 0x00068B70
void sub_822F0()
{
    dword_44BFF0 = 1;
    RtlEnterCriticalSection(&dword_44BF9C);
}

// match: ?sub_82310@@YAXXZ @ 0x00082310
// sp-match: ?sub_82310@@YAXXZ @ 0x00068B90
void sub_82310()
{
    RtlLeaveCriticalSection(&dword_44BF9C);
    dword_44BFF0 = 0;
}

// match: ?sub_82330@@YAXXZ @ 0x00082330
// sp-match: ?sub_82330@@YAXXZ @ 0x00068BB0
void sub_82330()
{
    RtlEnterCriticalSection(&dword_44BA98);
}

// match: ?sub_82340@@YAXXZ @ 0x00082340
// sp-match: ?sub_82340@@YAXXZ @ 0x00068BC0
void sub_82340()
{
    RtlLeaveCriticalSection(&dword_44BA98);
}

// match: ?sub_82350@@YAXXZ @ 0x00082350
// sp-match: ?sub_82350@@YAXXZ @ 0x00068BD0
void sub_82350()
{
    dword_44BAD0 = 1;
}

// match: ?sub_82360@@YAXXZ @ 0x00082360
// sp-match: ?sub_82360@@YAXXZ @ 0x00068BE0
void sub_82360()
{
    dword_44BAD0 = 0;
}

// match: ?sub_82370@@YAXXZ @ 0x00082370
// sp-match: ?sub_82370@@YAXXZ @ 0x00069400
void sub_82370()
{
    dword_44C064 = -1;
    dword_44C028 = -1;
}

// match: ?sub_82390@@YAXXZ @ 0x00082390
// sp-match: ?sub_82390@@YAXXZ @ 0x00069410
void sub_82390()
{
    RtlInitializeCriticalSection(&dword_44C068);
    RtlInitializeCriticalSection(&dword_44C084);
    RtlInitializeCriticalSection(&dword_44C02C);
    RtlInitializeCriticalSection(&dword_44C048);
}

// match: ?sub_823D0@@YAIP6GIPAX@Z@Z @ 0x000823D0
// sp-match: ?sub_823D0@@YAIP6GIPAX@Z@Z @ 0x000694D0
RwUInt32 sub_823D0(PTHREAD_START_ROUTINE arg_0)
{
    return sub_82410(arg_0);
}

// match: ?sub_823F0@@YAXI@Z @ 0x000823F0
// sp-match: ?sub_823F0@@YAXI@Z @ 0x000694E0
void sub_823F0(RwUInt32 arg_0)
{
    sub_82450(arg_0);
}

// match: ?sub_82410@@YAIP6GIPAX@Z@Z @ 0x00082410
// sp-match: ?sub_82410@@YAIP6GIPAX@Z@Z @ 0x00069440
RwUInt32 sub_82410(PTHREAD_START_ROUTINE arg_0)
{
    void *var_4;
    RwUInt32 local_8;

    var_4 = CreateThread(0, 0x40000, arg_0, 0, 0, &local_8); // not an address: a 256 KB stack
    SetThreadPriority(var_4, -2);
    ResumeThread(var_4);
    return local_8;
}

// "XBOXDestroyThread".
// match: ?sub_82450@@YAII@Z @ 0x00082450
// sp-match: ?sub_82450@@YAII@Z @ 0x00069480
RwUInt32 sub_82450(RwUInt32 arg_0)
{
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
    // Single player compiles the debug prints out (SP 0x69480).
    sub_19A750("XBOXDestroyThread:: Waiting for loading thread to exit...");
#endif
    dword_44C004 = 0;
#ifdef CODFH_SP
    // shape: single player re-reads the flag before the first wait (SP 0x6948A).
    while (*(volatile RwInt32 *)&dword_44C004 != 2)
#else
    while (dword_44C004 != 2)
#endif
    {
        sub_813E0(1);
    }
    dword_44C004 = 0;
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
    sub_19A750("XBOXDestroyThread:: Done waiting for loading thread to exit.  Loading thread destroyed...");
#endif
    return arg_0;
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?sub_19A750@@YAXPAX@Z (folded into 0x19A750)
// Single player keeps the calls to it (the shared empty body; SP 0x68990 tail call,
// sub_811C0's two calls): its body here would let /O2 drop them, so SP only declares it.
#ifndef CODFH_SP
void sub_19A750(void * arg_0)
{
}
#endif


#ifdef CODFH_PLAIN
// Plain builds (tools/plainbuild.py): the variables below are a second name for this unit's
// variables' bytes in the image (tools/session/overlapvars.py --aliases); only the placement
// link gives them one storage, so any other link binds them here at the image offset.
// (bound at start-up: the library initialization area runs before every game constructor)
#pragma warning(disable: 4073)
#pragma init_seg(lib)
// 0x004AF24C: dword_4AF038 + 0x214
RwInt32 &dword_4AF24C = *(RwInt32 *)((RwUInt8 *)&dword_4AF038 + 0x214);
#endif
