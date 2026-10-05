/*
 * The CCESS pool manager (unit_08AB60; "SetCCESSPoolManagerState" sets its
 * state, dword_4B2178): trackers for the objects that take part, drawn from
 * two pools ("m_freeTriggerTracker", "m_freeSpecialTriggerTracker"), and ten
 * slots that pick one of them now and then.
 */
#ifndef TYPES_CCESS_H
#define TYPES_CCESS_H

#include "rw/ostypes.h"
#include "types/alfasched.h"
#include "types/type_44350.h"

struct type_3D3548;

// The objects taking part are triggers (type_712B0; an entity's unk_34C):
// sub_8B4C0 gives a vehicle's (kind 0x1F) the second index.

// A tracker (16 bytes, from dword_4B2188).
struct type_8AFF0_node
{
    type_712B0 *unk_00;
    RwInt32 unk_04;             // the slots it serves
    RwInt32 unk_08;             // taken this round
    type_8AFF0_node *unk_0C;    // the next
};

// A special tracker (16 bytes, from dword_4B21A8).
struct type_8B4C0_node
{
    type_712B0 *unk_00;
    RwInt32 unk_04;             // its index (2 for kind 31)
    RwInt32 unk_08;             // its slots' kind (0 when vf_18 is 1, 1 when 2)
    type_8B4C0_node *unk_0C;
};

// A slot (0x18 bytes): five of kind 0 (dword_4B20F0) and five of kind 1
// (dword_4B2078).
struct type_8AEB0
{
    type_712B0 *unk_00;     // the object it last picked
    RwReal unk_04;              // counts up by one a round
    RwReal unk_08;              // the time left
    RwInt32 unk_0C;             // how many it has picked
    RwInt32 unk_10;             // its index
    RwInt32 unk_14;             // its kind
};

// The pool manager (dword_4B2174) is a CCESSPoolTrigger
// ("SetCCESSPoolManager", sub_8B770): types/CCESSPoolTrigger.h.
#include "types/CCESSPoolTrigger.h"

extern type_8AEB0 dword_4B2078[5];
extern type_8AEB0 dword_4B20F0[5];
extern type_8AFF0_node *dword_4B2168;
extern type_8AFF0_node *dword_4B216C;
extern type_8B4C0_node *dword_4B2170;
extern CCESSPoolTrigger *dword_4B2174;
extern RwInt32 dword_4B217C;
extern RwInt32 dword_4B2180;
extern RwInt32 dword_4B2184;
extern type_16C2A0 dword_4B2188;
extern type_16C2A0 dword_4B21A8;

void sub_8AB60();
void sub_8ABA0();
void sub_8ACE0();
void sub_8ACF0();
void sub_8AD20();
void sub_8ADD0(RwReal arg_0);
void sub_8AEB0(type_8AEB0 *arg_0, RwInt32 arg_4, type_8AFF0_node *arg_8, RwReal arg_C);
RwInt32 sub_8AFF0(RwInt32 arg_0, type_8AFF0_node *arg_4, type_8AEB0 *arg_8);
// Turn pool creation on and off for the trigger arg_0
// ("ToggleCCESSPoolCreation").
type_8AFF0_node *sub_8B180(type_712B0 *arg_0);
void sub_8B250(type_712B0 *arg_0);
// Clears the pool triggers answering slot arg_0 ("ClearCCESSPoolTriggers").
void sub_8B380(RwInt32 arg_0);
void sub_8B3C0(RwInt32 arg_0, type_8AFF0_node **arg_4, RwInt32 *arg_8);
// Creates the special pool entry for the trigger arg_0, giving its entity
// in *arg_4 ("SpecialCCESSPoolCreation").
type_8B4C0_node *sub_8B4C0(type_712B0 *arg_0, type_3D3548 **arg_4);
void sub_8B6B0(type_712B0 *arg_0);
// Makes the trigger arg_0 the pool manager (arg_4 set) or lets it go
// ("SetCCESSPoolManager"), and sets the most trackers of index arg_0 of
// kind arg_4 to arg_8 ("ChangeCCESSPoolSize").
void sub_8B770(type_712B0 *arg_0, RwInt32 arg_4);
void sub_8B810(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8);
void sub_8B840(type_3D3548 *arg_0);

#endif
