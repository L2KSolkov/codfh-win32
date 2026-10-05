/*
 * type_3DD948: the player's camera entity (unit_174950), derived from
 * type_3D3548 and anchored at its vtable off_3DD948, which its constructor
 * (sub_174B20) installs; sub_174A70 builds one (0x440 bytes) in entity
 * memory. The player keeps its handle at +0x2110 (type_10F710::sub_FF1A0).
 * The script's camera commands see the same object as type_62A60 (kind
 * 0x100000 in unk_2C, which the set-up sets; the mode at +0x414 and the
 * spline path at +0x42C).
 *
 * Its modes (unk_414, "SetCameraMode"): 0 follows the player (vf_244 of the
 * entity it is attached to), 1 rides the player's head bone (vf_04C), 2 and
 * 3 glide to the matrix unk_3D0 at the rate unk_410 ("IHaveArrived" when
 * there; 3 leaves the render camera alone), 4 runs along the spline path
 * unk_42C ("SplinePathArrived" at its end).
 */
#ifndef TYPE_3DD948_H
#define TYPE_3DD948_H

#include "rw/ostypes.h"
#include "rw/bamatrix.h"
#include "types/type_3D3548.h"
#include "types/type_D48D0.h"
#include "types/type_439E78.h"

struct SplinePath;
typedef struct RwCamera RwCamera;

struct type_3DD948 : type_3D3548
{
    virtual void vf_03C(RwReal arg_0);
    virtual void vf_044(RwReal arg_0);
    virtual void vf_04C(RwReal arg_0);
    virtual struct type_6D380 *vf_090();
    virtual type_3D2E7C *vf_098();
    virtual RwUInt8 *vf_0E0();
    virtual void vf_0EC(RwInt32 arg_0, RwInt32 arg_4);
    virtual void vf_1C4(RwInt32 arg_0);
    virtual void vf_230();
    ~type_3DD948();

    RwUInt8 unk_3A8[0x8];
    RwInt32 unk_3B0;            // set when it lands (vf_1C4): the follow
                                // keeps the render camera's position
    RwReal unk_3B4;             // the shake's size ("CameraShake", sub_175E50)
    RwReal unk_3B8;             // its time left, in frames
    RwReal unk_3BC;             // its fall per frame
    RwReal unk_3C0;             // its field of view (the player's unk_534)
    RwInt32 unk_3C4;            // its script object's handle (vf_098)
    union
    {
        RwInt32 unk_3C8;        // its performance player's handle (vf_090;
        type_439E78_00 unk_3C8_h;   // the set-up copies it as the struct)
    };
    RwInt32 unk_3CC;            // set up (vf_230 shuts it down once)
    RwMatrix unk_3D0;           // the matrix modes 2 and 3 glide to
    RwReal unk_410;             // their rate (0.02), and the spline's
    RwInt32 unk_414;            // its mode ("SetCameraMode")
    RwInt32 unk_418;            // the mode of the frame before
    type_D48D0 unk_41C;         // the entity it follows
    RwCamera *unk_420;          // the render camera (dword_4E5C74)
    RwInt16 unk_424[2];         // its scene map entry (vf_0E0, vf_0EC)
    RwUInt8 unk_428[2];
    RwUInt8 unk_42A[0x2];
    SplinePath *unk_42C;        // mode 4's spline path
    RwReal unk_430;             // and how far along it
    RwUInt8 unk_434[0xC];

    type_3DD948(RwV3d *arg_0, RwReal arg_4, type_3D3548 *arg_8);
    // The placement pair it is built in entity memory with (sub_6CCF0 and
    // the empty sub_19A750), and its plain operator delete for its deleting
    // destructor (folded into sub_19A750 too).
    static void *operator new(RwUInt32 arg_0, void *arg_4);
    static void operator delete(void *arg_0, void *arg_4);
    static void operator delete(void *arg_0);
    // Sets it up for the entity arg_8 with the field of view arg_4 (arg_0
    // unused): its trigger's camera object (kind 3), a collision atomic of
    // radius arg_4 on its frame, its script object with the trigger's two
    // scripts and its entity key, its animation, its performance player.
    // Returns 0 without a camera object.
    RwInt32 sub_174BC0(RwV3d *arg_0, RwReal arg_4, type_3D3548 *arg_8);
    // Places the render camera's frame at the matrix arg_0 (mode 1 and the
    // script's "SetCameraAlign...").
    void sub_1752A0(RwMatrix *arg_0);
    // Shakes it by arg_0 (on the follow, at least 3 while the entity's
    // unk_1B04 is set and it is over the constant 0x3D7118) for arg_4
    // frames, falling by arg_0 * arg_8 a frame; a shake of a longer time
    // left is kept.
    void sub_175E50(RwReal arg_0, RwReal arg_4, RwReal arg_8);
    // Sets the matrix modes 2 and 3 glide to (its rows, not its flags).
    void sub_175F00(RwMatrix *arg_0);
    // An inline accessor for unk_414, with no address and so no database
    // name; named for its field. Evidence: the player's look (sub_10A330)
    // compares it through a temporary of its own.
    RwInt32 get_unk_414()
    {
        RwInt32 r = unk_414;
        return r;
    }
    // vf_054, as the image's vtable has it (a trivial body, folded into
    // sub_15FB30 with every other copy).
    virtual void vf_054(RwInt32 arg_0)
    {
    }
    // vf_058, as the image's vtable has it (a trivial body, folded into
    // sub_32260 with every other copy).
    virtual RwInt32 vf_058(struct type_3DF8D8_04 *arg_0)
    {
        return 0;
    }
    // vf_040, as the image's vtable has it (a trivial body, folded into
    // sub_FB430 with every other copy).
    virtual void vf_040(RwReal arg_0)
    {
        type_3D3548::vf_040(arg_0);
    }
    // Collision_DispatchAtomicIntersectionsBySelectorFlag, as the image's vtable has it (a trivial body, folded into
    // sub_177080 with every other copy).
    virtual void Collision_DispatchAtomicIntersectionsBySelectorFlag(RpAtomic *arg_0,
                                                                     RpIntersection *arg_4,
                                                                     struct type_93700 *arg_8)
    {
        if (arg_8)
            arg_8->unk_5C = 1;
    }
};
typedef RwChar type_3DD948_size_check[sizeof(type_3DD948) == 0x440 ? 1 : -1];

// Builds a camera at arg_0 with the field of view arg_4 for the entity
// arg_8, or returns 0 when there is no entity memory.
type_3DD948 *sub_174A70(RwV3d *arg_0, RwReal arg_4, type_3D3548 *arg_8);

#endif
