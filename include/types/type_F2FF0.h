/*
 * type_F2FF0: a particle system (0x160 bytes), as sub_F2FF0 returns it
 * (declared there as a plain word, which its callers pass on). Built in a
 * slot of one of two pools (game/particles.h) by sub_F3130: its matrix,
 * its flags, its definition (type_F3130), its links in the live list, its
 * clocks and texture, its particles' state (unk_60, run by sub_19EC70 and
 * the rest) and what ties it to an entity: the entity's handle id
 * (unk_150), a callback (unk_154, sub_CDFA0) and a value the callback
 * passes on (unk_158), and the holders that hold it (unk_15C, type_F2880).
 *
 * unk_40's flags: 1 live, 2 visible, 4 set up, 8 (a mesh system's) drawn,
 * 0x10 a mesh system (kind 3 and up with unk_A8 set), 0x20 counted in
 * dword_4BFD30, 0x40 the render pass it belongs to.
 */
#ifndef TYPE_F2FF0_H
#define TYPE_F2FF0_H

#include "rw/ostypes.h"
#include "rw/bamatrix.h"
#include "rw/batextur.h"
#include "rw/baengine.h"
#include "rw/rpatomic.h"
#include "types/type_F3130.h"
#include "types/type_D48D0.h"

struct type_F2880;

// The particles' first point setter (game/particlerender.h, which needs the
// D3D headers): declared here too for the units that cannot include it
// (the third weapon kind's fire hands it a system's particles, unk_60).
struct type_19E9B0;
void sub_19E9B0(type_19E9B0 *arg_0, RwV3d *arg_4);
void sub_19E9E0(type_19E9B0 *arg_0, RwV3d *arg_4);

// A mesh system particle's state, 0x24 bytes (sub_F3E70 allocates them and
// sets unk_00 to -1).
struct type_F2FF0_60_04
{
    RwReal unk_00;              // its age (-1: free; sub_EF040)
    RwV3d unk_04;               // its velocity
    RwV3d unk_10;               // its spin axis
    RwReal unk_1C;              // and rate
    RwInt32 unk_20;             // set once its trail has started
};

// The particles' state (sub_19EC70 sets it up, sub_19F740 draws it,
// sub_19E940 frees it); only what the system itself touches is known.
struct type_F2FF0_60
{
    RwMatrix *unk_00;           // the particles' matrices (a mesh system's)
    type_F2FF0_60_04 *unk_04;   // and their states
    RwReal unk_08;              // its age (a mesh system's, sub_EF040)
    RwReal unk_0C;              // the age at the last emission
    RwReal unk_10;              // and at the last trail
    RwUInt32 unk_14;            // flag 8: the definition's spin (unk_F8 to unk_104) is set
    RwInt32 unk_18;
    RwInt32 unk_1C;             // the particle count (a mesh system's)
    RpAtomic *unk_20;           // the mesh (sub_F2D80)
    RwUInt8 unk_24[0x4C];
    RwReal unk_70;              // the age before the last update
    RwUInt8 unk_74[0x60];
    RwInt32 unk_D4;
    RwInt32 unk_D8;
    RwUInt8 unk_DC[0x14];
};

struct type_F2FF0
{
    RwMatrixTag unk_00;         // where it was started
    RwUInt32 unk_40;            // its flags (above)
    type_F3130 *unk_44;         // its definition
    type_F2FF0 *unk_48;         // the live list (dword_4BFD34)
    type_F2FF0 *unk_4C;
    RwReal unk_50;              // the clock at its start
    RwReal unk_54;              // the clock at its last update
    RwReal unk_58;              // its age
    RwTexture *unk_5C;
    type_F2FF0_60 unk_60;
    union
    {
        RwInt32 unk_150;
        type_3D3548_384 unk_150_h;  // as the weapon copies' event handler
    };                              // stores it whole (vf_030)
    RwInt32 (*unk_154)(type_F2FF0 *arg_0);
    RwInt32 unk_158;
    type_F2880 *unk_15C;        // its holders

    // sub_F3A60 and sub_F3AE0 (which lets its holders go).
    type_F2FF0();
    ~type_F2FF0();
    // Returns it to its pool (sub_F39F0).
    static void operator delete(void *arg_0);
    // The placement pair sub_F3130 builds it in its pool slot with, as
    // type_3D2CD0's (sub_6CCF0 and the empty sub_19A750).
    static void *operator new(RwUInt32 arg_0, void *arg_4);
    static void operator delete(void *arg_0, void *arg_4);
    // Takes it down (freeing a mesh system's buffers) and off the live list.
    RwInt32 sub_F3B50();
    // Sets it up from the definition arg_0 at the matrix arg_4 at the clock
    // arg_8: a mesh system (sub_F3E70: its matrix made orthonormal, identity
    // when an axis is degenerate, and a matrix and state per particle; not for
    // kind 1) or a sprite one (sub_F3C70).
    RwInt32 sub_F3C00(type_F3130 *arg_0, RwMatrix *arg_4, RwReal arg_8, RwInt32 arg_C, RwInt32 arg_10,
                      bool arg_14);
    RwInt32 sub_F3C70(type_F3130 *arg_0, RwMatrix *arg_4, RwReal arg_8, RwInt32 arg_C, RwInt32 arg_10,
                      bool arg_14);
    RwInt32 sub_F3E70(type_F3130 *arg_0, RwMatrix *arg_4, RwReal arg_8, RwInt32 arg_C);
    // Updates it (a mesh system by sub_F4300, a sprite one by sub_F41D0) in
    // the camera arg_0 at the clock arg_4 by arg_8 frames; 0 when it is done.
    RwInt32 sub_F4190(RwCamera *arg_0, RwReal arg_4, RwReal arg_8);
    RwInt32 sub_F41D0(RwCamera *arg_0, RwReal arg_4, RwReal arg_8);
    RwInt32 sub_F4300(RwReal arg_0, RwReal arg_4);
    // Draws it.
    void sub_F43B0();
    // An inline accessor for unk_15C, with no address and so no database
    // name; named for its field. Evidence: sub_F4480 reads it through a
    // temporary each time.
    type_F2880 *get_unk_15C()
    {
        type_F2880 *r = unk_15C;
        return r;
    }
    // Links and unlinks the holder arg_0.
    void sub_F4480(type_F2880 *arg_0);
    void sub_F44E0(type_F2880 *arg_0);
};
typedef RwChar type_F2FF0_size_check[sizeof(type_F2FF0) == 0x160 ? 1 : -1];

#endif
