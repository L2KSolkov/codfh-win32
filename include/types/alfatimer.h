/*
 * alfatimer (unit_073360): the script timers, named from the image's own
 * string "alfatimer::m_freeList", which sub_73360 passes when it sets up
 * their pool dword_449B48. A timer posts its message to its object once
 * the clock dword_449B40 passes its time (sub_73650); the list
 * dword_449B44 is kept in time order (sub_73590).
 */
#ifndef ALFATIMER_H
#define ALFATIMER_H

#include "rw/ostypes.h"
#include "types/alfasched.h"
#include "types/type_439E78.h"
#include "types/type_67620.h"

// A timer (0x18 bytes, one of m_freeList's elements).
struct type_73360
{
    union
    {
        RwUInt32 unk_00;        // its object's handle
        type_439E78_00 unk_00_h;
    };
    RwInt32 unk_04;             // the message it posts
    RwInt32 unk_08;             // the timer's own argument, posted with it
    RwInt32 unk_0C;             // its object's vf_028 when registered
    RwReal unk_10;              // when it fires
    type_73360 *unk_14;         // the next timer
};

extern RwReal dword_449B40;         // the timers' clock
extern type_73360 *dword_449B44;    // the timers, soonest first
extern type_16C2A0 dword_449B48;    // alfatimer::m_freeList

void sub_73550();
void sub_73590(type_73360 *arg_0);
void sub_73610(type_73360 *arg_0, type_73360 *arg_4);

#endif
