/*
 * The RenderWare object holders (12 bytes each: a link in the object's list
 * of holders, then the object). Each holds one object, linking itself into
 * its list, and destroys it once no holder is left. Their constructors and
 * destructors are inline; the destructors' out-of-line copies (for unwind
 * funclets) are emitted with the first code that needs them.
 *
 *   type_129B10  a frame (sub_129B10 releases it)
 *   type_129940  a clump (sub_129940 sets it, 0 releasing it)
 *   type_1294D0  an atomic (sub_1294D0 releases it)
 *   type_129BD0  a light (sub_129BD0 sets it, sub_129C40 releases it)
 *
 * type_144940 holds a trigger the same way, but without the empty base.
 */
#ifndef TYPE_129_BASE_H
#define TYPE_129_BASE_H

#include "rw/ostypes.h"
#include "rw/baframe.h"
#include "rw/rpatomic.h"
#include "rw/rplight.h"

// The holders' base: its destructor is empty and inline, but the holders'
// destructors keep an EH state around it and the unwind funclets call its
// out-of-line copy (pDtor, one of the empty functions /OPT:ICF folded at
// 0x1E41C0).
struct type_129_base
{
    ~type_129_base()
    {
    }
};

struct type_129B10 : type_129_base
{
    RwInt32 unk_00;
    RwInt32 unk_04;
    RwFrame *unk_08;

    type_129B10()
    {
        unk_08 = 0;
        unk_00 = 0;
        unk_04 = 0;
    }
    ~type_129B10()
    {
        sub_129B10();
        unk_08 = 0;
        unk_00 = 0;
        unk_04 = 0;
    }
    RwInt32 sub_129B10();
    // Holds the frame arg_0 instead (releasing the one held).
    void sub_129A70(RwFrame *arg_0);
    // Hands the entity arg_0 to the frame held (sub_129AE0, through
    // sub_129BB0).
    void sub_129AE0(struct type_3D3548 *arg_0);
    void sub_129BB0(RwFrame *arg_0, struct type_3D3548 *arg_4);
    // An inline accessor for unk_08, with no address and so no database
    // name; named for its field. Evidence: the player's take-down
    // (type_10F710::vf_230) tests it through a temporary, and the aim assist
    // (sub_100AD0) copies it through one into its own local.
    RwFrame *get_unk_08()
    {
        RwFrame *r = unk_08;
        return r;
    }
};

typedef struct RpClump RpClump;

struct type_129940 : type_129_base
{
    RwInt32 unk_00;
    RwInt32 unk_04;
    RpClump *unk_08;

    type_129940()
    {
        unk_08 = 0;
        unk_00 = 0;
        unk_04 = 0;
    }
    ~type_129940()
    {
        sub_129940(0);
        unk_08 = 0;
        unk_00 = 0;
        unk_04 = 0;
    }
    // Releases the clump (arg_0: even while other holders point at it),
    // destroying it once none is left; 1 unless it had to stay.
    RwBool sub_129940(RwInt32 arg_0);
    // Holds the clump arg_0, and ties it to the entity arg_0 (the player's
    // model, type_10F710::sub_10C650); only the widths are known.
    void sub_129620(RpClump *arg_0);
    void sub_129690(struct type_3D3548 *arg_0);
    // Hands the entity arg_4 to the clump arg_0's atomics, lights and
    // frames.
    void sub_129750(RpClump *arg_0, struct type_3D3548 *arg_4);
    // Likewise (type_10F710::vf_230).
    RpClump *get_unk_08()
    {
        return unk_08;
    }
};

// What the clump's release (sub_129940) hands its callbacks: the clump,
// and the entity its parts must belong to to leave the world with it.
struct type_129940_data
{
    RpClump *unk_00;
    struct type_3D3548 *unk_04;
};

struct type_1294D0 : type_129_base
{
    RwInt32 unk_00;
    RwInt32 unk_04;
    RpAtomic *unk_08;

    type_1294D0()
    {
        unk_08 = 0;
        unk_00 = 0;
        unk_04 = 0;
    }
    ~type_1294D0()
    {
        sub_1294D0();
        unk_08 = 0;
        unk_00 = 0;
        unk_04 = 0;
    }
    RwBool sub_1294D0();
    // Holds the atomic arg_0 instead (releasing the one held).
    void sub_129430(RpAtomic *arg_0);
    // Hands the entity arg_0 to the atomic held (the pickup's set-up,
    // sub_FADB0); only the width is known.
    void sub_1294A0(struct type_3D3548 *arg_0);
    // Hands the entity arg_4 to the atomic arg_0 and its frame.
    void sub_1295E0(RpAtomic *arg_0, struct type_3D3548 *arg_4);
};

struct type_129BD0 : type_129_base
{
    RwInt32 unk_00;
    RwInt32 unk_04;
    RpLight *unk_08;

    type_129BD0()
    {
        unk_08 = 0;
        unk_00 = 0;
        unk_04 = 0;
    }
    // Out of line for WorldLight's constructor's unwinding (sub_C54E0).
    ~type_129BD0()
    {
        sub_129C40();
        unk_08 = 0;
        unk_00 = 0;
        unk_04 = 0;
    }

    // Holds arg_0 (0 for none), leaving the light it held.
    void sub_129BD0(RpLight *arg_0);
    // Leaves its light, destroying it (and its frame) if no holder is left.
    RwBool sub_129C40();
    // An inline accessor for unk_08, with no address and so no database
    // name; named for its field. Evidence: WorldLight tests it through a
    // temporary.
    RpLight *get_unk_08()
    {
        return unk_08;
    }
};

class Trigger;

struct type_144940
{
    RwInt32 unk_00;
    RwInt32 unk_04;
    union
    {
        Trigger *unk_08;
        // A projectile generator's trigger (type_1227C0::unk_18).
        class ProjectileGeneratorTrigger *unk_08_pg;
        // An objective's target object (game/objectives.h).
        struct type_4E56A0_34 *unk_08_obj;
    };

    type_144940()
    {
        unk_08 = 0;
        unk_00 = 0;
        unk_04 = 0;
    }
    ~type_144940()
    {
        sub_144940(0);
    }
    // Holds the trigger arg_0 (0 for none).
    void sub_144940(Trigger *arg_0);
    // An inline accessor for unk_08, with no address and so no database
    // name; named for its field. Evidence: the player's pick-up take
    // (sub_106A60) copies the pick-up's trigger through a temporary into
    // its own local.
    Trigger *get_unk_08()
    {
        Trigger *r = unk_08;
        return r;
    }
    // Clears it as the constructor does, for one built in raw pool memory;
    // an inline with no address, named for what it does. Evidence: the
    // triggered particles' set-up (sub_F5920) clears it field by field
    // through a temporary holding its address.
    void init()
    {
        unk_08 = 0;
        unk_00 = 0;
        unk_04 = 0;
    }
};

#endif
