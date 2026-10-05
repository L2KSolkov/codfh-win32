/*
 * type_4B9E90: a particle spawner, one of the 128 in the pool dword_4B9E90
 * (0x54 bytes each), named after the pool (src/recovered/unit_0F06B0.cpp).
 * sub_F1230 hands out the first free one (unk_20 clear), flushing the first
 * when none is. "SpawnParticleSpawner" (sub_4AF10) sets one up; the update
 * (sub_F0C40) emits its particle system at the target every unk_18 frames,
 * unk_10 times.
 *
 * The target (unk_20) is 1: an entity, held by handle (unk_24), placed at
 * its clump's tagged matrix unk_1C or else its frame; 2: an object with a
 * position and a direction (type_4B9E90_28, unk_28); 3: the point unk_00.
 */
#ifndef TYPE_4B9E90_H
#define TYPE_4B9E90_H

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "types/type_D48D0.h"
#include "types/type_F2880.h"

struct type_3D3548;

// The kind-2 target: only what sub_F0AF0 reads is known.
struct type_4B9E90_28
{
    RwInt32 unk_00;
    RwV3d unk_04;               // its position
    RwV3d unk_10;               // its direction
    RwInt32 unk_1C;
    RwReal unk_20;              // positive while it is live

    // An inline accessor for unk_20, with no address and so no database
    // name; named for its field. Evidence: sub_F0AF0 compares it through a
    // temporary.
    RwReal get_unk_20()
    {
        RwReal r = unk_20;
        return r;
    }
};

struct type_4B9E90
{
    RwV3d unk_00;               // the kind-3 target: a point
    RwInt32 unk_0C;             // the particle system's id
    RwInt32 unk_10;             // emissions left (0x7FFFFFFF: endless)
    RwReal unk_14;              // frames to the next emission
    RwReal unk_18;              // frames between emissions
    RwInt32 unk_1C;             // the clump tag to place it at ("PT" and two
                                // digits for 0 to 99), 0 for none
    RwInt32 unk_20;             // the target's kind (0: free)
    type_D48D0 unk_24;          // the kind-1 target
    void *unk_28;               // the kind-2 target
    RwReal unk_2C;              // the spacing ("SpawnParticleSpawner"'s sixth
                                // argument): moving further than it between
                                // emissions fills the way in
    RwV3d unk_30;               // where it last emitted
    RwInt32 unk_3C;             // set by sub_F0880 and sub_F0A10
    RwInt32 unk_40;             // whether the system stays attached
    type_F2880 unk_44;          // the particle system
    RwUInt8 unk_50;             // the emission chance, 0 to 255
    RwUInt8 unk_51[3];

    type_4B9E90();
    ~type_4B9E90();
    void sub_F07C0();
    // Sets it up with the particle system arg_0, arg_4 emissions (-1:
    // endless; none when arg_C, attached, is set) every arg_8 frames.
    void sub_F0880(RwInt32 arg_0, RwInt32 arg_4, RwReal arg_8, RwInt32 arg_C);
    // Destroys an attached system and frees it.
    void sub_F0900();
    // The target (an entity for kind 1), or 0.
    void *sub_F0960();
    void sub_F09B0(type_3D3548 *arg_0);
    // Attaches it to the target arg_0 of kind arg_8 at the tag arg_4 (0 to
    // 99: "PT" and its digits; -1: none).
    void sub_F0A10(type_3D3548 *arg_0, RwInt32 arg_4, RwInt32 arg_8);
    // Sets the emission chance, 0 to 1.
    void sub_F0AA0(RwReal arg_0);
    // Moves an attached system's matrix to the target.
    void sub_F0AF0();
    // Advances it by arg_0 frames; arg_4, when given, is the position to
    // emit at.
    void sub_F0C40(RwReal arg_0, RwV3d *arg_4);

    // An inline accessor for unk_20, with no address and so no database
    // name; named for its field. Evidence: the pool's loops (sub_F11D0,
    // sub_F1230) test it through a temporary.
    RwInt32 get_unk_20()
    {
        RwInt32 r = unk_20;
        return r;
    }
    // Likewise for unk_40 (sub_F0900).
    RwInt32 get_unk_40()
    {
        RwInt32 r = unk_40;
        return r;
    }
};
typedef RwChar type_4B9E90_size_check[sizeof(type_4B9E90) == 0x54 ? 1 : -1];

extern type_4B9E90 dword_4B9E90[128];

void sub_F1190();
void sub_F11D0(RwReal arg_0);
type_4B9E90 *sub_F1230();
// Fires the spawners on the entity arg_0 once more (at the position arg_4
// when given) and frees them ("DestroySelf", sub_454A0, passes 0).
void sub_F12A0(type_3D3548 *arg_0, RwV3d *arg_4);

#endif
