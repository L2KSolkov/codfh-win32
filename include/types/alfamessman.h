/*
 * alfamessman: the message manager, named from the image's own strings
 * ("alfamessman::m_messagePool" and its other pools' names, which its
 * set-up sub_6B3B0 passes). Its state is static: six type_16C2A0 pools and
 * the registration array, globals the database names by address; each
 * declaration below gives the member's name from those strings.
 */
#ifndef ALFAMESSMAN_H
#define ALFAMESSMAN_H

#include "rw/ostypes.h"
#include "types/alfasched.h"
#include "types/type_439E78.h"
#include "game/data.h"

extern type_16C2A0 dword_4493D4;    // m_messagePool (0x18-byte messages)
extern type_16C2A0 dword_4493B4;    // m_registrationPool (0x1C bytes)
extern type_16C2A0 dword_449394;    // m_filterListSmallPool (0xE bytes)
extern type_16C2A0 dword_449374;    // m_filterListLargePool (0x2E bytes)
extern type_16C2A0 dword_449354;    // m_messageArgsSmallPool (0x10 bytes)
extern type_16C2A0 dword_449334;    // m_messageArgsLargePool (0x28 bytes)
extern RwInt16 *dword_449330;       // m_registrationArray: 0x546 list heads
                                    // (-1 for none)
extern RwInt32 dword_44932C;        // -1 after set-up and restarts

// A registration (0x1C bytes from m_registrationPool) of a script, trigger
// or handler for a message kind (unk_1B: 1, 2 or 3), kept in the list of
// m_registrationArray[unk_14] through unk_10 and unk_12 (indices in the
// pool, -1 for none).
struct type_6B960
{
    union
    {
        RwUInt32 unk_00;    // the registered object's handle
        type_439E78_00 unk_00_h;
    };
    RwInt32 unk_04;
    union
    {
        struct type_6B9A0_08 *unk_08;
        RwInt16 unk_08_s;
    };
    RwInt16 unk_0C;
    RwInt16 unk_0E;
    RwInt16 unk_10;         // the next registration of the list
    RwInt16 unk_12;         // the previous one
    RwInt32 unk_14;         // the message kind (its list)
    RwInt8 unk_18;
    RwInt8 unk_19;
    RwUInt8 unk_1A;         // 1: unregistered while its kind is being sent
    RwUInt8 unk_1B;         // the registration's kind
};
typedef RwChar type_6B960_size_check[sizeof(type_6B960) == 0x1C ? 1 : -1];

// A registration of kind 2 (sub_6BAE0), whose unk_00 is a callback: it
// takes unk_04 and the message and returns whether to stay registered.
struct type_6BAE0
{
    RwInt32 (*unk_00)(RwInt32 arg_0, struct type_42E00 *arg_4);
    RwInt32 unk_04;
};

// What a registration of kind 1 points at (unk_08); only its flag at +6 is
// known (sub_6B9A0 drops the queued messages when it is set).
struct type_6B9A0_08
{
    RwUInt16 unk_00;        // a state handler's id
    RwUInt16 unk_02;        // and code offset (0xFFFF for none)
    RwUInt8 unk_04[0x2];
    RwUInt8 unk_06;
};

// The registration at the pool index arg_0 (0 for -1): an inline with no
// address and so no database name, named for what it returns. Evidence:
// sub_6BB40 converts a list link to its short argument in a temporary
// packed after its locals, and assigns each branch's result straight into
// its local.
inline type_6B960 *get_registration(RwInt16 arg_0)
{
    if (arg_0 == -1)
        return 0;
    return (type_6B960 *)dword_4493B4.sub_16C6A0(arg_0);
}

// The performance map at arg_0 (0 out of range): an inline with no address
// and so no database name, named for what it returns. Evidence: sub_6BF60
// converts a message's short to its int argument in a temporary after its
// locals and assigns each branch's result straight into its local.
inline struct type_4CFE30 *get_performance_map(RwInt32 arg_0)
{
    if (arg_0 >= 0 && arg_0 < 2000)
        return dword_4CFE30[arg_0];
    return 0;
}

// The pool index of the registration arg_0 (-1 for 0): an inline with no
// address and so no database name, the counterpart of get_registration.
// Evidence: type_3D2DB8::sub_6F7E0 stores each branch's result in one
// temporary and then its low half.
inline RwInt32 get_registration_index(type_6B960 *arg_0)
{
    if (arg_0 != 0)
        return dword_4493B4.sub_16C650(arg_0);
    return -1;
}

// sub_6BD30: frees what is left before a restart or shutdown.
void sub_6BD30();
void sub_6B510();

// Registers the callback arg_4 (kind 2) for the object arg_0 (arg_8 its
// argument), on the message arg_C of the script arg_10 with the flags arg_14;
// ends a registration.
#ifdef CODFH_SP
// Single player's arg_10 is unsigned: its callers zero-extend the script
// number they pass (movzx at SP 0x92410, 0x92530 and 0x7CB31).
type_6B960 *sub_6BAE0(RwInt32 arg_0, RwUInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C, RwUInt8 arg_10,
                      RwInt8 arg_14);
#else
type_6B960 *sub_6BAE0(RwInt32 arg_0, RwUInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C, RwInt8 arg_10,
                      RwInt8 arg_14);
#endif
void sub_6BC40(type_6B960 *arg_0);
// A registration's flags from two nibbles: an inline with no address and so
// no database name, named for what it builds. Evidence: VehicleEnterExitTrigger
// builds (2 << 4) | 2 at run time (an inline's arguments are not folded).
inline RwInt8 msg_flags(RwInt32 arg_0, RwInt32 arg_4)
{
    return (RwInt8)((arg_0 << 4) | arg_4);
}

#endif
