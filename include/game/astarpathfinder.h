/*
 * The A* path finder (Source\GameCore\pathnodemanager\astarpathfinder.cpp,
 * the path its asserts pass): three finders for the scheduled searches
 * (dword_4BFED0; the first takes the searches of type 2, the others type 1)
 * and one for the searches that must finish at once (dword_4BFE28). A
 * search (type_169D0, the request) runs over the path-node graph
 * (unk_4C00E8) a few expansions per frame (sub_F6090), keeping a record
 * (type_F6400) per node it reaches, hashed by the node's index.
 */
#ifndef GAME_ASTARPATHFINDER_H
#define GAME_ASTARPATHFINDER_H

#include "rw/ostypes.h"
#include "types/type_169D0.h"
#include "types/type_F8350.h"

struct type_3D3548;

// A node's search record (0x2C bytes, from the finder's unk_84): open
// (bit 0) or closed (bit 1), the node, the cost so far, a second cost, the
// estimate and their sum, the open or closed list's links, the record it
// was reached from and the hash chain.
struct type_F6400
{
    RwUInt32 unk_00;
    RwInt16 unk_04;             // the node's index
    RwUInt8 unk_06[0x2];
    type_F8350 *unk_08;
    RwReal unk_0C;
    RwReal unk_10;
    RwReal unk_14;
    RwReal unk_18;
    type_F6400 *unk_1C;
    type_F6400 *unk_20;
    type_F6400 *unk_24;
    type_F6400 *unk_28;
};

// A finder (0xA8 bytes).
struct type_4BFED0
{
    RwInt32 unk_00;             // set once it has stepped this frame
    RwInt32 unk_04;             // the immediate finder's
    RwInt32 unk_08;             // expansions this step
    type_169D0 unk_0C;          // its copy of the request
    type_169D0 *unk_58;         // the request
    RwInt32 unk_5C;             // the steps it may take
    RwUInt32 unk_60;            // the steps taken
    RwInt32 unk_64;             // the start's and goal's indices
    RwInt32 unk_68;
    RwInt32 unk_6C;
    type_F8350 *unk_70;         // the goal node
    type_F6400 *unk_74;         // the record being expanded
    type_F6400 *unk_78;         // the open list (best first)
    type_F6400 *unk_7C;         // the closed list (the path, from its end)
    type_F6400 **unk_80;        // the hash's 1024 chains
    type_F6400 *unk_84;         // the 1024 records
    RwInt32 unk_88;             // and how many are out
    RwInt32 unk_8C;             // records opened
    RwInt32 unk_90;             // and closed
    RwInt32 unk_94;             // a search is running
    RwInt32 unk_98;
    RwInt32 unk_9C;             // it is reserved
    RwInt32 unk_A0;             // the search's id
    RwUInt32 unk_A4;            // the search types it takes

    type_4BFED0();
#ifdef CODFH_SP
    // Single player's destructor is out of line: dword_4BFE28's exit
    // function (SP 0x21E910) jumps to the folded empty body (SP 0x5A260).
    // Only declared: the placement link binds it there.
    ~type_4BFED0();
#endif
    type_F6400 *sub_F6400();
    type_F6400 *sub_F6450(RwInt32 arg_0);
    void sub_F6510();
    void sub_F65E0();
    void sub_F6600();
    void sub_F6680();
    void sub_F6700();
    void sub_F6C50();
    void sub_F6C80(type_F6400 *arg_0);
    void sub_F6D60(type_F6400 *arg_0);
    RwInt32 sub_F6DE0(type_169D0 *arg_0, RwInt32 arg_4);
    RwInt32 sub_F6FC0();
    RwInt32 sub_F7470(type_169D0 *arg_0);
    RwInt32 sub_F7620(type_F6400 *arg_0, type_169D0 *arg_4);
    // The outcome's log (empty in this build): the entity, the search id,
    // the request, a message and where it was raised.
    void sub_F7B90(type_3D3548 *arg_0, RwInt32 arg_4, type_169D0 *arg_8, const RwChar *arg_C,
                   const RwChar *arg_10, RwInt32 arg_14);

    // Inline accessors for unk_94 and unk_9C, with no address and so no
    // database names; named for their fields. Evidence: sub_F62F0 reads each
    // through a temporary.
    RwInt32 get_unk_94()
    {
        RwInt32 r = unk_94;
        return r;
    }
    RwInt32 get_unk_9C()
    {
        RwInt32 r = unk_9C;
        return r;
    }
    // Likewise for unk_A0 (sub_F6200 and sub_F6270).
    RwInt32 get_unk_A0()
    {
        RwInt32 r = unk_A0;
        return r;
    }
};
typedef RwChar type_4BFED0_size_check[sizeof(type_4BFED0) == 0xA8 ? 1 : -1];

// The finders' settings: the steps a type-1 and a type-2 search and an
// immediate one may take per call, and whether they are set up.
extern RwInt32 dword_4BFE18;
extern RwInt32 dword_4BFE1C;
extern RwInt32 dword_4BFE20;
extern RwInt32 dword_4BFE24;
extern type_4BFED0 dword_4BFE28;
extern type_4BFED0 dword_4BFED0[3];
// The most steps a found and a failed search took, and the searches
// started and their peak.
extern RwUInt32 dword_4C00C8;
extern RwUInt32 dword_4C00CC;
#ifdef CODFH_PLAIN
extern RwUInt32 &dword_4C00D4;
#else
extern RwUInt32 dword_4C00D4;
#endif
#ifdef CODFH_PLAIN
extern RwUInt32 &dword_4C00D8;
#else
extern RwUInt32 dword_4C00D8;
#endif
// The expansions a step may make, and the steps before a search is
// reported as slow (.data).
extern RwInt32 dword_4296D8;
extern RwUInt32 dword_4296F0;
// The cost functions' distances and factor (.data).
extern RwReal flt_4296DC;
extern RwReal flt_4296E0;
extern RwReal flt_4296E4;
extern RwReal flt_4296E8;
extern RwReal flt_4296EC;

void sub_F5F10();
void sub_F5FE0();
void sub_F6030();
void sub_F6090();
RwInt32 sub_F6100(RwInt32 arg_0);
RwInt32 sub_F6130(RwInt32 arg_0);
RwInt32 sub_F6160(RwInt32 arg_0, RwUInt32 arg_4);
RwInt32 sub_F61A0(RwInt32 arg_0);
RwInt32 sub_F6200(RwInt32 arg_0);
void sub_F6270(RwInt32 arg_0);
// Starts the search arg_0 with the id arg_4 on a free finder taking the
// type arg_8 (arg_C: at once, on the immediate finder); -1 when none is
// free.
RwInt32 sub_F62F0(type_169D0 *arg_0, RwInt32 arg_4, RwUInt32 arg_8, RwInt32 arg_C);
// The cost functions, the heuristic and the filters, and their selectors.
RwReal sub_F6750(type_F6400 *arg_0, type_F8350 *arg_4, RwInt32 arg_8, RwInt32 arg_C, type_169D0 *arg_10,
                 RwReal *arg_14);
RwReal sub_F6840(type_F6400 *arg_0, type_F8350 *arg_4, RwInt32 arg_8, RwInt32 arg_C, type_169D0 *arg_10,
                 RwReal *arg_14);
RwReal sub_F6970(type_F6400 *arg_0, type_F8350 *arg_4, RwInt32 arg_8, RwInt32 arg_C, type_169D0 *arg_10,
                 RwReal *arg_14);
RwReal sub_F6B00(type_F8350 *arg_0, RwInt32 arg_4, type_F8350 *arg_8, RwInt32 arg_C);
RwInt32 sub_F6B70(type_F8350 *arg_0, type_169D0 *arg_4);
RwInt32 sub_F6B80(type_F8350 *arg_0, type_169D0 *arg_4);
type_169D0_cost sub_F6BB0(RwInt32 arg_0);
type_169D0_heuristic sub_F6BF0(RwInt32 arg_0);
type_169D0_filter sub_F6C10(RwInt32 arg_0);

#endif
