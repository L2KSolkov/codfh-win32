/*
 * The animation banks (unit_0770C0): a table of dword_449C90 banks
 * (dword_449C94, 0x44 bytes each) sharing one heap (dword_449C98), set up
 * by sub_770F0 ("ANIMATION HEAP SIZE ALLOCATION"). A bank holds the data
 * set loaded from "ANIMGRPS\..." (sub_77540), built in its part of the heap.
 */
#ifndef ANIMBANK_H
#define ANIMBANK_H

#include "rw/ostypes.h"
#include "rw/bastream.h"
#include "types/type_439E78.h"
#include "types/animobjpool.h"
#include "rw/rtquat.h"
#include "types/animkey.h"

// An animation of a set (type_77D30::unk_28's chains): its id, its name
// and the next in its chain.
struct type_77D30_28
{
    RwInt32 unk_00;             // its id (sub_788C0 asks whether it plays)
    RwChar unk_04[0x20];        // its name
    type_77D30_28 *unk_24;      // the next in its chain
    void *unk_28;               // an animation, released with sub_7FFB0
    RwUInt8 *unk_2C;            // deleted
};

// A loaded animation data set ("ADST"), 0x2C bytes with its hash table
// running on past unk_28 (0x40 chains), built in a bank's memory or on the
// heap by its placement operator new (sub_77C10) and constructor (sub_77CA0),
// read from a stream by sub_77E40; destroyed by sub_77D30.
struct type_77D30
{
    RwUInt8 unk_00;             // built
    RwUInt8 unk_01[0x3];
    RwUInt32 unk_04;            // 'ADST'
    RwInt32 unk_08;             // 0x1000
    RwInt32 unk_0C;
    RwInt32 unk_10;
    RwUInt32 unk_14;            // its size
    RwInt32 unk_18;             // the chains' count (0x40)
    RwInt32 unk_1C;             // the hash mask (unk_18 - 1)
    RwUInt8 *unk_20;            // the free memory after the table (0 on the
    RwUInt32 unk_24;            // heap) and the memory's size (0 on the heap)
    type_77D30_28 *unk_28[1];   // the animations' chains, by id & unk_1C

    // Sets itself up in the bank memory arg_4 of arg_8 bytes, or on the heap
    // when arg_4 is 0 (arg_0 is the class's size; the table takes 0x100
    // more).
    static void *operator new(RwUInt32 arg_0, RwUInt8 *arg_4, RwUInt32 arg_8);
    type_77D30();
    ~type_77D30();
    // Adds the animation named Source (its hash the id) with the data
    // arg_4 and arg_8; whether there was memory for it.
    bool sub_78260(const RwChar *Source, void *arg_4, RwUInt8 *arg_8);
    // arg_0 bytes (rounded to 4) of its own memory, or 0 when out of it.
    void *sub_78370(RwUInt32 arg_0);
    // Finds the animation arg_0: its two data pointers into *arg_4 and
    // *arg_8 (either may be 0); whether it is there.
    bool sub_77DC0(RwInt32 arg_0, void **arg_4, void **arg_8);
    // An inline accessor for its size, with no address and so no database
    // name; named for its field. Evidence: sub_776F0 reads it twice, each
    // through a local of its own.
    RwUInt32 get_unk_14()
    {
        RwUInt32 r = unk_14;
        return r;
    }
    // Whether it lives on the heap (no bank memory): an inline with no
    // address and so no database name, named for what it tests. Evidence:
    // sub_773A0 tests it through a `this` copy and a byte temporary.
    bool is_heap()
    {
        return unk_24 == 0 && unk_20 == 0;
    }
    // Inline setters, with no address and so no database names, named for
    // their fields. Evidence: sub_77E40 stores the two words it read
    // through a by-value temporary each.
    void set_unk_0C(RwInt32 arg_0)
    {
        unk_0C = arg_0;
    }
    void set_unk_10(RwInt32 arg_0)
    {
        unk_10 = arg_0;
    }
};

// A bank (0x44 bytes): its index, flags (bit 31 while it loads), the id
// of the set it holds, its memory, and the set's name.
// A set's id (two words), passed whole to sub_77540 by the loading thread.
struct type_449C94_08
{
    RwInt32 unk_00;
    RwInt32 unk_04;
};
struct type_449C94
{
    RwUInt32 unk_00;            // its index
    RwUInt32 unk_04;            // bit 31: loading
    union
    {
        struct
        {
            RwInt32 unk_08;     // the set's id, two words
            RwInt32 unk_0C;
        };
        type_449C94_08 unk_08_s;    // the same, as the loading thread passes it
    };
    type_77D30 *unk_10;         // the set, built at the bank's memory
    RwUInt32 unk_14;            // the bank's size
    RwInt32 unk_18;
    RwInt32 unk_1C;             // loaded
    RwUInt32 unk_20;            // the largest set it has held
    RwChar unk_24[0x20];        // the set's name
};

// A bank load request (sub_77540 builds one for sub_776F0): the bank, the
// set's id and the file's path.
struct type_776F0
{
    RwUInt32 unk_00;
    RwInt32 unk_04;
    RwInt32 unk_08;
    RwChar unk_0C[0x104];
};

extern RwUInt32 dword_449C90;       // the banks' count
extern type_449C94 *dword_449C94;   // the banks
extern RwUInt8 *dword_449C98;       // their heap

// The last load error's message.
extern RwChar byte_449B90[];
// sub_D7F20: the platform path of the file arg_4 into arg_0.
void sub_D7F20(RwChar *arg_0, const RwChar *arg_4);
// sub_776F0: loads the set in the stream arg_0 for the request arg_4 (arg_8
// only known by width); whether it could. sub_77E40 builds a set from the
// stream arg_0 in the memory arg_4 of arg_8 bytes.
RwInt32 sub_776F0(struct RwStream *arg_0, type_776F0 *arg_4, RwInt32 arg_8);
type_77D30 *sub_77E40(struct RwStream *arg_0, void *arg_4, RwUInt32 arg_8);
// Sets up the set arg_0 (unit_0770C0); only the widths are known.
RwInt32 sub_77AC0(type_77D30 *arg_0);

// sub_788C0: whether the animation arg_0 is active (arg_4 only known by
// width); sub_81EB0: queues the asynchronous job arg_0 (2 loads a bank) for
// the file arg_4 with the word arg_8 (a bank, passed as a word, for job 2).
bool sub_788C0(RwInt32 arg_0, bool arg_4);
void sub_81EB0(RwInt32 arg_0, const RwChar *arg_4, RwInt32 arg_8);
// Loads the set arg_4 named arg_0 into the bank arg_C (the loading thread
// passes 1 and 0 as arg_10 and arg_14, which it does not read).
RwInt32 sub_77540(const RwChar *arg_0, type_449C94_08 arg_4, RwUInt32 arg_C, RwInt32 arg_10, RwInt32 arg_14);
// Whether the set arg_0 is already loaded to slot arg_8 (CAnimPackSelector's
// HandleEvents skips it then).
RwInt32 sub_774F0(type_449C94_08 arg_0, RwInt32 arg_8);

// An animation's events (0x1C bytes with the entries running on): their
// count, then each event's id, time and data.
struct type_783F0_04
{
    RwInt32 unk_00;             // its id
    RwReal unk_04;              // its time (read in 120ths)
    union
    {
        struct
        {
            RwInt32 unk_08;     // its data (vf_170's third argument)
            RwUInt8 unk_0C[0xC];
        };
        RwV3d unk_08_v;         // or a position (event 3)
        RtQuat unk_08_q;        // or a rotation (event 4)
    };
};

struct type_783F0
{
    RwInt32 unk_00;             // the events' count
    type_783F0_04 unk_04[1];

    // The first event at or after the time arg_0 with the id arg_4 (any for
    // -1); the event after arg_0 (with the id arg_4, the last such, unless
    // -1).
    type_783F0_04 *sub_78550(RwReal arg_0, RwInt32 arg_4);
    type_783F0_04 *sub_785C0(type_783F0_04 *arg_0, RwInt32 arg_4);
};
type_783F0 *sub_783F0(RwStream *arg_0, type_783F0 *arg_4, RwUInt32 arg_8);
type_783F0 *sub_784D0(RwStream *arg_0, RwUInt32 arg_4);
RwUInt32 sub_78670(RwInt32 arg_0);

// The animation players' pools (unit_078AF0).
extern CAnimObjectPool byte_44A508[3];

// Pool arg_0: an inline with no address and so no database name, named for
// what it returns. Evidence: DogTrigger's vf_020 (sub_A4840), sub_B8EC0 and
// sub_1C07E0 compute the constant pool's place at run time (an inline's
// parameter is not folded at /Od) to read its free count.
inline CAnimObjectPool &get_pool(RwInt32 arg_0)
{
    return byte_44A508[arg_0];
}

// The pools' sizes (count and element size by pool).
struct type_428BEC
{
    RwInt32 unk_00;
    RwInt32 unk_04;
    RwInt32 unk_08;
};
extern type_428BEC dword_428BEC[3];

// The animation players' handle table (0xB3 entries of 12 bytes, entry 0
// unused): each entry's pool, handle and player.
struct type_449CA0
{
    RwInt32 unk_00;             // the pool
    union
    {
        RwUInt32 unk_04;        // the handle
        type_439E78_00 unk_04_h;
    };
    void *unk_08;               // the player
};
extern type_449CA0 dword_449CA0[0xB3];
// The next handle serial (0x428C0C): the image keeps it in dword_428BEC's last
// entry's third field (the code indexes dword_428BEC in 12-byte steps, so the
// table spans it); named here for what it holds.
#define dword_428C0C (dword_428BEC[2].unk_08)
extern RwInt32 dword_44A504;

// A player as sub_788C0 reads it: its tracks (type_7C8D0_30).
struct type_788C0
{
    RwUInt8 unk_00[0x10];
    RwInt16 unk_10;             // its pool
    RwUInt8 unk_12[0x1A];
    RwUInt32 unk_2C;            // the tracks' count
    struct type_7C8D0_30 *unk_30;
};

// sub_78AC0: the player with the handle arg_0, or 0 (as type_3D3548.h
// declares it).
struct type_78AC0;
type_78AC0 *sub_78AC0(RwInt32 arg_0);
RwUInt32 sub_789A0(void *arg_0, RwInt32 arg_4);
void sub_78A80(RwUInt32 arg_0);
// A new player from the pool arg_0, and releasing the player arg_0.
RwUInt32 sub_78830(RwInt32 arg_0);
void sub_78870(RwInt32 arg_0);
// sub_16C800: the FNV-1 hash of the string arg_0 from the basis arg_4.
RwUInt32 sub_16C800(const RwChar *arg_0, RwUInt32 arg_4);

// The animation system's parts (their units follow), set up and torn down
// with the pools (sub_786A0, sub_78790, sub_787F0); the callbacks are only
// known by address.
void sub_79260();
bool sub_7A410(RwInt32 arg_0, type_7A410_cb arg_4);
struct type_7C8D0;
struct type_80300;
RwInt32 sub_7A4E0(void (*arg_0)(type_7C8D0 *, type_80300 *, RwInt32, bool));
// The animation event callback: hands the event arg_0 (its data arg_4), the
// track arg_C's animation and the player arg_10 to the entity arg_8's
// vf_170.
void sub_78D10(RwInt32 arg_0, void *arg_4, struct type_3D3548 *arg_8,
               struct type_7C8D0_30 *arg_C, struct type_7C8D0 *arg_10);
void sub_134320(type_7C8D0 *arg_0, type_80300 *arg_4, RwInt32 arg_8, bool arg_C);
void sub_150350(type_7C8D0 *arg_0, type_80300 *arg_4, RwInt32 arg_8, bool arg_C);
void sub_155D30(type_7C8D0 *arg_0, type_80300 *arg_4, RwInt32 arg_8, bool arg_C);
void sub_17F620(type_7C8D0 *arg_0, type_80300 *arg_4, RwInt32 arg_8, bool arg_C);
void sub_181140(type_7C8D0 *arg_0, type_80300 *arg_4, RwInt32 arg_8, bool arg_C);
void sub_16B0C0(type_7C8D0 *arg_0, type_80300 *arg_4, RwInt32 arg_8, bool arg_C);
// sub_31DB0 as sub_78790 calls it, with no arguments (an empty function the
// alfasched test shares through /OPT:ICF).
RwInt32 sub_31DB0();

// Sets up the banks' heap ("ANIMATION HEAP SIZE ALLOCATION") from arg_0
// sizes of arg_4 at arg_8 (unit_0770C0; CAnimBankInfo passes its six).
void sub_770F0(RwUInt32 arg_0, RwUInt32 arg_4, RwUInt32 *arg_8);

#endif
