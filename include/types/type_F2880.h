/*
 * type_F2880: a holder of a particle system (12 bytes: a link in the
 * system's list of holders, then the system), anchored at its setter
 * sub_F2880, like the RenderWare object holders (types/type_129_base.h).
 * sub_F2880 leaves the system it held (sub_F44E0) and joins arg_0's list
 * (sub_F4480). Its constructor is inline; its destructor (sub_F2880(0)) is
 * inline too, its out-of-line copy emitted for the particle spawner's
 * unwinding (sub_F0740).
 */
#ifndef TYPE_F2880_H
#define TYPE_F2880_H

#include "rw/ostypes.h"

// The particle system (types/type_F2FF0.h); sub_F3300 destroys one.
struct type_F2FF0;

struct type_F2880
{
    type_F2880 *unk_00;         // the system's next and previous holders
    type_F2880 *unk_04;         // (type_F2FF0::sub_F4480)
    type_F2FF0 *unk_08;

    type_F2880()
    {
        unk_08 = 0;
        unk_00 = 0;
        unk_04 = 0;
    }
    ~type_F2880()
    {
        sub_F2880(0);
    }
    // Holds the system arg_0 (0 for none).
    void sub_F2880(type_F2FF0 *arg_0);
    // Clears it as the constructor does (type_144940::init's likewise;
    // sub_F5920).
    void init()
    {
        unk_08 = 0;
        unk_00 = 0;
        unk_04 = 0;
    }
    // An inline accessor for unk_08, with no address and so no database
    // name; named for its field. Evidence: the particle spawner (sub_F0900,
    // sub_F0AF0) reads it through a temporary.
    type_F2FF0 *get_unk_08()
    {
        type_F2FF0 *r = unk_08;
        return r;
    }
    // Likewise for the links (type_F2FF0::sub_F44E0 reads each through a
    // temporary).
    type_F2880 *get_unk_00()
    {
        type_F2880 *r = unk_00;
        return r;
    }
    type_F2880 *get_unk_04()
    {
        type_F2880 *r = unk_04;
        return r;
    }
};

// Destroys the particle system arg_0 (counting it off dword_4BFD30 when its
// flag 0x20 is set).
void sub_F3300(type_F2FF0 *arg_0);

#endif
