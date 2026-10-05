/*
 * The asynchronous loading queue ("AsynchLoadingQueue", unit_0811C0): a ring
 * of sixteen load requests a loading thread works through, and the locks
 * around it. Its debug strings name the class and some of its methods
 * ("AsynchLoadingQueue::ShutdownClass()", "(AbortUnneededSections...)",
 * "(AbortPendingClumpBanks...)", "(WaitForCurrentLoadToFinish...)"); the
 * functions keep their database names, with those names in comments.
 */
#ifndef TYPES_ASYNCHLOAD_H
#define TYPES_ASYNCHLOAD_H

#include "rw/ostypes.h"
#include "rws/gftime.h"
#include "xbox/xboxkrnl.h"
#include "xbox/xapi.h"
#include "rw/bamemory.h"
#include "types/soundbank.h"

// A load request (0x4C bytes): what to load (its file name), its kind (the
// loading thread's names for them: 0 "eSection", 1 "eLoadSoundBank", 2
// "eAnimGroup", 3 "eClumpBank", any other "None"), its section or bank, and
// whether it is still wanted.
struct type_44BAD8
{
    RwChar unk_00[0x40];
    RwInt32 unk_40;
    RwInt32 unk_44;
    RwInt32 unk_48;
};

// The queue: its requests, the one the thread works on (dword_44BFF8) and
// the next free one (dword_44BFFC); dword_44BF98 is set while the queue is
// being changed.
extern type_44BAD8 dword_44BAD8[16];
extern type_44BAD8 *dword_44BFF8;
extern type_44BAD8 *dword_44BFFC;
extern RwInt32 dword_44BF98;
// The locks: the queue's (dword_44BAB4), the loading thread's (dword_44BF9C,
// held while it may not run, dword_44BFF0 set meanwhile), dword_44BA98's
// (sub_82330, sub_82340) and dword_44BFB8; dword_44BFD4 is handed to
// RenderWare (sub_2A7870).
extern RTL_CRITICAL_SECTION dword_44BA98;
extern RTL_CRITICAL_SECTION dword_44BAB4;
extern RTL_CRITICAL_SECTION dword_44BF9C;
extern RTL_CRITICAL_SECTION dword_44BFB8;
extern RTL_CRITICAL_SECTION dword_44BFD4;
// The locks sub_82390 sets up (not otherwise used here).
extern RTL_CRITICAL_SECTION dword_44C02C;
extern RTL_CRITICAL_SECTION dword_44C048;
extern RTL_CRITICAL_SECTION dword_44C068;
extern RTL_CRITICAL_SECTION dword_44C084;
extern RwInt32 dword_44BFF0;
// Whether the queue is running (dword_44C004), loading may proceed
// (dword_428E14), a stream is open (dword_44BAD0), sections were aborted
// (dword_44C000), and the loading thread (dword_44BAD4).
extern RwInt32 dword_44C004;
extern RwInt32 dword_428E14;
extern RwInt32 dword_44BAD0;
extern RwInt32 dword_44C000;
extern RwUInt32 dword_44BAD4;           // its thread id, which sub_823D0 returns
// RenderWare's allocation functions as the loading thread leaves them
// (dword_44C008, 44C010, 44C018) and as the game had them (dword_44C00C,
// 44C014, 44C01C): sub_813E0 swaps them around its wait, dword_44C020
// saying how far it got.
extern void *(*dword_44C008)(size_t size, RwUInt32 hint);
extern void *(*dword_44C00C)(size_t size, RwUInt32 hint);
extern void *(*dword_44C010)(size_t numObj, size_t sizeObj, RwUInt32 hint);
extern void *(*dword_44C014)(size_t numObj, size_t sizeObj, RwUInt32 hint);
extern void *(*dword_44C018)(void *mem, size_t newSize, RwUInt32 hint);
extern void *(*dword_44C01C)(void *mem, size_t newSize, RwUInt32 hint);
extern RwInt32 dword_44C020;
extern RwInt32 dword_44C028;
extern RwInt32 dword_44C064;
extern RwUInt8 byte_44BFF4;

void sub_811C0();
void sub_81300();
void sub_81310();
void sub_81380();
void sub_813E0(RwInt32 arg_0);
void sub_81E40(void *arg_0);
void sub_81EF0(RwInt32 arg_0, const RwChar *arg_4, RwInt32 arg_8);
RwInt32 sub_81FB0(RwInt32 arg_0, const RwChar *arg_4, RwInt32 arg_8);
RwInt32 sub_82020(RwInt32 arg_0, RwInt32 arg_4);
void sub_82070(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C);
void sub_82130();
void sub_821C0();
void sub_822A0();
void sub_822F0();
void sub_82310();
void sub_82330();
void sub_82340();
void sub_82350();
void sub_82360();
void sub_82370();
void sub_82390();
RwUInt32 sub_823D0(PTHREAD_START_ROUTINE arg_0);
void sub_823F0(RwUInt32 arg_0);
RwUInt32 sub_82410(PTHREAD_START_ROUTINE arg_0);
RwUInt32 sub_82450(RwUInt32 arg_0);
RwUInt32 __stdcall sub_81590(void *arg_0);

// Helpers elsewhere: sub_2A7870 hands RenderWare its texture lock,
// RWS::Time::GetTime is the time in milliseconds (GetTickCount), sub_170ED0 an
// empty test returning 0 that /OPT:ICF shares, sub_16E9C0 unloads the clump
// bank when an unload is pending (game/clumpbank.h); the debug print (sub_19A750) as these calls use it.
extern "C" void sub_2A7870(RTL_CRITICAL_SECTION *arg_0);
RwInt32 sub_170ED0(RwInt32 arg_0);
void sub_16E9C0();
// sub_1B29D0 waits arg_0 milliseconds; dword_4CF888 is the memory handler's
// busy flag (rws/memoryhandler.h; sub_81380 waits up to 31 times for it).
void sub_1B29D0(RwUInt32 arg_0);
extern RwInt32 dword_4CF888;
void sub_19A750();
void sub_19A750(void *arg_0);

// What the loading thread (sub_81590) calls to do each kind of load:
// sections: sub_D8230 loads the section arg_0, sub_1745F0 finds its slot
// (sub_174030 then unloads it), sub_173F50 its record (the section it holds
// at +8); dword_428E20 is cleared and word_429EAC holds the section while
// it loads. Clump banks: sub_16F770 and sub_16EDB0 name a weapon or plain
// bank's file into arg_0 (arg_4 bytes), sub_16F460 and sub_16EAE0 read it
// from the stream arg_0; sub_16EEA0 is busy while dword_4E5CC4's sound
// streams play (dword_4E51C8 set meanwhile). Sound banks: sub_885B0 (when
// dword_4B2068 is set) or sub_82C70 on dword_4AF038. sub_19BB40 marks the
// file arg_0 as loading (arg_4 1) or done (0).
struct type_173F50
{
    RwUInt8 unk_00[0x8];
    RwInt16 unk_08;
    RwUInt8 unk_0A[0x6];
    RwUInt8 unk_10[0x4];        // what the section loaders (unit_141BB0) pass
                                // RpWorldStreamRead with the stream

    // Inline: no address, so no database name; named for its field. The
    // loading thread passes its argument through a two-byte temporary.
    void set_unk_08(RwInt16 arg_0)
    {
        unk_08 = arg_0;
    }
};
void sub_D8230(RwInt32 arg_0);
RwInt32 sub_1745F0(RwInt32 arg_0);
void sub_174030(RwUInt16 arg_0, RwInt32 arg_4);
struct type_4E5D30;
type_4E5D30 *sub_173F50(RwUInt16 arg_0);
void sub_16F770(RwChar *arg_0, RwInt32 arg_4, RwInt32 arg_8);
void sub_16EDB0(RwChar *arg_0, RwInt32 arg_4, RwInt32 arg_8);
void sub_16F460(struct RwStream *arg_0, RwInt32 arg_4, RwInt32 arg_8);
void sub_16EAE0(struct RwStream *arg_0, RwInt32 arg_4);
RwInt32 sub_16EEA0();
void sub_885B0(RwInt32 arg_0);
extern RwInt32 dword_428E20;
extern RwInt16 word_429EAC;
// Inline: no address, so no database name; named for what it sets (the
// loading thread passes its argument through a two-byte temporary).
inline void setLoadingSection_(RwInt16 arg_0)
{
    word_429EAC = arg_0;
}
extern RwInt32 dword_4E5CC4;
extern RwInt32 dword_4E51C8;
extern RwInt32 dword_4B2068;

#endif
