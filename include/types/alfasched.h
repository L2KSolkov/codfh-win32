/*
 * alfasched: a scheduler, named from the image's own string
 * "alfasched::m_freeList", which sub_71F20 passes when it sets up the pool at
 * +0xC (so the member is m_freeList). Two live in .data, flt_438D38 and
 * flt_438D88 (0x50 apart; the database names them for their first dword),
 * which the CanShoot functions (sub_31AD0 to sub_31E00) run.
 *
 *   +0x0C m_freeList  a type_16C2A0 pool
 *   +0x2C..+0x40      sub_71F20's six arguments; +0x44 and +0x48 zeroed
 *
 * It is 0x4C bytes (see the size check below).
 */
#ifndef ALFASCHED_H
#define ALFASCHED_H

#include "rw/ostypes.h"
#include "types/type_67620.h"

// type_16C2A0: the pool alfasched keeps its free entries in, anchored at its
// destructor sub_16C2A0 (sub_71F00 runs it on m_freeList). sub_16C2C0 sets
// it up; sub_16C7E0 is true when its +0x08 count is 0.
struct type_16C2A0
{
    RwUInt32 unk_00;        // flags: 1 its memory is not its own, 2 no
                            // guard word (0x2F2F2F2F marks a taken element)
    RwUInt8 *unk_04;        // its memory
    RwUInt8 *unk_08;        // the first free element (each free element
                            // links the next in its last word)
    RwInt32 unk_0C;         // the element count
    RwInt32 unk_10;         // the element size
    RwInt32 unk_14;         // the most ever taken at once
    RwInt32 unk_18;         // the free count (AIHearing's sub_3C220 checks
                            // that all 25 of its listeners came back)
    RwUInt8 unk_1C[0x4];

    // sub_16C280 and sub_16C2A0 (alfahash's constructor and destructor call
    // them on its m_pool; see config/aliases.txt).
    type_16C2A0();
    ~type_16C2A0();
    bool sub_16C7E0();
    // An inline accessor for unk_18, with no address and so no database
    // name; named for its field. Evidence: sub_3C220 reads it through a
    // temporary of its own.
    RwInt32 get_unk_18()
    {
        RwInt32 r = unk_18;
        return r;
    }
    // Likewise for the element count (the entity manager's sub_D56D0 walks
    // a pool's elements up to it through a temporary of its own).
    RwInt32 get_unk_0C()
    {
        RwInt32 r = unk_0C;
        return r;
    }
    // Likewise for the element size (the AIManeuverManager's sub_3CE20
    // picks its pool through a temporary of it).
    RwInt32 get_unk_10()
    {
        RwInt32 r = unk_10;
        return r;
    }
    // Whether elements are out (fewer free than there are); an inline with
    // no address and so no database name. Evidence: sub_3CD10 tests the
    // result as a bool (movzx of the setnz byte).
    bool in_use()
    {
        return unk_18 != unk_0C;
    }
    // Whether arg_0 is one of this pool's elements.
    bool sub_16C770(void *arg_0);
    // Sets the pool up for arg_0 elements of arg_4 bytes, named arg_8
    // ("m_freeDistanceParams" for sub_34FA0); arg_C and arg_10 are only
    // known by width (4 and 0 there).
    void sub_16C2C0(RwInt32 arg_0, RwInt32 arg_4, const RwChar *arg_8, RwInt32 arg_C, bool arg_10);
    // Takes over arg_8 as the memory for arg_0 elements of arg_4 bytes
    // (sub_16C2C0 passes what it allocated; arg_C is unused).
    void sub_16C390(RwInt32 arg_0, RwInt32 arg_4, RwUInt8 *arg_8, RwInt32 arg_C);
    // Links every element into the free list.
    void sub_16C430();
    // Sets the pool up with no elements (type_4B83A0's sub_D64A0 when its
    // count is 0).
    void sub_16C3E0();
    // Shuts the pool down, warning of elements not freed when arg_0 is set.
    void sub_16C4D0(bool arg_0);
    // Takes an element (arg_0 is only known by width: 0 is passed), 0 when
    // none is left.
    void *sub_16C5A0(RwInt32 arg_0);
    // Returns the element arg_0 to the pool.
    void sub_16C710(void *arg_0);
    // Returns the element at the index arg_0 to the pool (sub_16C6A0, then
    // sub_16C710).
    void sub_16C6E0(RwInt32 arg_0);
    // The element at the index arg_0, and the index of the element arg_0.
    void *sub_16C6A0(RwInt32 arg_0);
    RwUInt32 sub_16C650(void *arg_0);
};
typedef RwChar type_16C2A0_size_check[sizeof(type_16C2A0) == 0x20 ? 1 : -1];

// Both callbacks are cdecl with the same four arguments (the entry's
// object, then an int, a float and an int); sub_31DB0 ignores them.
// type_72050: what alfasched's registrations (sub_72050, sub_72120) return
// by value, named after the function that creates it. Four bytes, returned
// through a hidden pointer, so it has a constructor of its own (VC7.1 returns
// a four-byte struct without one in eax); sub_32F70 hands its unk_00 to
// sub_67620 as a handle.
struct type_72050
{
    RwInt32 unk_00;

    type_72050();
};

// alfasched_entry: a registration, one of m_freeList's 0x1C-byte elements:
// the registered object's handle (in dword_439E78, which sub_67620
// resolves) and the next entry of the schedule's list (sub_722E0 walks it
// from the alfasched's first dword).
struct alfasched_entry
{
    RwUInt32 unk_00;            // its own handle (kind 5)
    union
    {
        RwUInt32 unk_04;        // the registered object's handle
        type_439E78_00 unk_04_h;
    };
    RwInt32 unk_08;             // the callbacks' three arguments
    RwReal unk_0C;
    RwInt32 unk_10;
    RwInt32 unk_14;             // the object's vf_028 when registered (-1
                                // once dropped while it runs)
    alfasched_entry *unk_18;
};
typedef RwChar alfasched_entry_size_check[sizeof(alfasched_entry) == 0x1C ? 1 : -1];

typedef RwInt32 (*alfasched_callback)(type_67620 *arg_0, RwInt32 arg_4, RwReal arg_8,
                                      RwInt32 arg_C);
typedef alfasched_callback alfasched_test;

struct alfasched
{
    alfasched_entry *unk_00;    // the list's first entry
    alfasched_entry *unk_04;    // its last
    alfasched_entry *unk_08;    // the entry being run (sub_72560)
    type_16C2A0 m_freeList;
    RwInt32 unk_2C;
    RwInt32 unk_30;
    RwInt32 unk_34;
    RwInt32 unk_38;
    alfasched_callback unk_3C;
    alfasched_test unk_40;
    RwReal unk_44;              // the time run up (sub_72560)
    RwInt32 unk_48;             // set when the running entry is dropped

    // sub_71EC0 and sub_71F00.
    alfasched();
    ~alfasched();
    // Stores its six arguments at +0x2C and sets up m_freeList with arg_0
    // entries of 0x1C bytes.
    void sub_71F20(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C,
                         alfasched_callback arg_10, alfasched_test arg_14);
    // Both return what sub_71FF0 does (nonzero while entries remain);
    // sub_71FC0 also empties m_freeList.
    RwInt32 sub_71FA0();
    RwInt32 sub_71FC0();
    // Unregisters everything, warning when anything was left (returns 0).
    RwInt32 sub_71FF0();
    // Register arg_0 (search type arg_4, data arg_8, id arg_C) and return
    // its entry; sub_72120 is used for search type 12.
    type_72050 sub_72050(type_67620 *arg_0, RwInt32 arg_4, RwReal arg_8, RwInt32 arg_C);
    type_72050 sub_72120(type_67620 *arg_0, RwInt32 arg_4, RwReal arg_8, RwInt32 arg_C);
    // Unregisters arg_0.
    void sub_72240(type_67620 *arg_0);
    // Unregisters the entry with handle arg_0 (sub_67620 resolves it).
    void sub_722B0(RwUInt32 arg_0);
    // Whether arg_0 is one of this schedule's entries.
    RwInt32 sub_722E0(alfasched_entry *arg_0);
    // The entry of arg_0 still current (its vf_028 unchanged), or 0.
    alfasched_entry *sub_72320(type_67620 *arg_0);
    // Links arg_0 in after the running entry, or first; links arg_0 last.
    void sub_72380(alfasched_entry *arg_0);
    void sub_72410(alfasched_entry *arg_0);
    // Unlinks and frees the entry arg_0; unlinks the entry arg_4 (after
    // arg_0, or first), tells unk_40 and frees it.
    void sub_72450(alfasched_entry *arg_0);
    void sub_724B0(alfasched_entry *arg_0, alfasched_entry *arg_4);
    // Runs the schedule for the time step arg_0.
    void sub_72560(RwReal arg_0);
    // Drops the entries arg_0 returns 0 for.
    void sub_726E0(alfasched_callback arg_0);
    // The number of entries.
    RwInt32 sub_727D0();
};
// 0x4C bytes: the Distance Scheduler's pool dword_4391EC follows its
// alfasched dword_4391A0 at +0x4C (the CanShoot and A* pairs lie 0x50 apart,
// with four bytes between).
typedef RwChar alfasched_size_check[sizeof(alfasched) == 0x4C ? 1 : -1];

#endif
