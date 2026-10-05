/*
 * type_6EE50: an object's script thread manager (type_67620::vf_030), named
 * after its method sub_6EE50, which starts a thread (the script command
 * "CreateThread", sub_44820, passes its two arguments) and returns it
 * (type_6EE50_thread); only what the command uses is known.
 */
#ifndef TYPE_6EE50_H
#define TYPE_6EE50_H

#include "rw/ostypes.h"

struct type_6EE50_thread
{
    RwUInt8 unk_00[0x4];
    RwInt32 unk_04;         // its id, which "CreateThread" returns

    // An inline accessor for unk_04, with no address and so no database
    // name; named for its field. Evidence: sub_44820 reads it through a
    // temporary of its own.
    RwInt32 get_unk_04()
    {
        RwInt32 r = unk_04;
        return r;
    }
};

struct type_6EE50
{
    type_6EE50_thread *sub_6EE50(RwInt32 arg_0, RwInt32 arg_4);
};

#endif
