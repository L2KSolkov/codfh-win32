/*
 * type_3DDB98: an entity class derived from type_3D3548, anchored at its
 * vtable off_3DDB98, which sub_176F60 installs (building a type_15CCE0 at
 * +0x3E0 with sub_15CCE0, as type_3DAFC8's sub_134C50 does). It is the class
 * type_3D3548::vf_024 returns: its slot +0x024 returns this (sub_6FCD0).
 * Its kind (unk_2C & 0x3FFFFF0) is 0x200000 (sub_1774C0, which sub_176F60
 * calls). It is the gimp a GimpTrigger spawns (sub_176E50; unit_176E50):
 * the strings after its vtable name "GimpEntity::HeadMesh",
 * "GimpEntity::BodyMesh" and "GimpEntity::CharacterDef".
 */
#ifndef TYPE_3DDB98_H
#define TYPE_3DDB98_H

#include "rw/ostypes.h"
#include "types/type_3D3548.h"
#include "game/functions.h"
#include "types/type_15CCE0.h"
#include "types/type_D48D0.h"
#include "types/type_129_base.h"
#include "types/type_439E78.h"
#include "types/type_3DAFC8.h"

struct type_3DDB98 : type_3D3548
{
    virtual void vf_03C(RwReal arg_0);
    virtual void vf_04C(RwReal arg_0);
    virtual void vf_054(RwInt32 arg_0);
    virtual RwInt32 vf_058(struct type_3DF8D8_04 *arg_0);
    virtual RwInt32 vf_060(type_3D3548 *arg_0);
    virtual RwInt32 vf_064(struct type_75600 *arg_0);
    virtual RwInt32 vf_068(struct type_758F0 *arg_0);
    virtual RwInt32 vf_06C(type_3D3548 *arg_0);
    // A collision query's hit on it (its done flag set).
    virtual void Collision_DispatchAtomicIntersectionsBySelectorFlag(RpAtomic *arg_0, RpIntersection *arg_4,
                                                                     struct type_93700 *arg_8);
    virtual void vf_078();
    virtual RwInt32 vf_07C(RwInt8 arg_0, RpIntersection *arg_4, RwReal *arg_8, RwInt32 arg_C);
    virtual void vf_088(RwInt32 arg_0);
    virtual RwUInt8 *vf_08C(RwInt32 arg_0, RwInt32 arg_4);
    virtual struct type_6D380 *vf_090();
    virtual void vf_094(RwUInt32 arg_0);
    virtual type_3D2E7C *vf_098();
    virtual RwInt32 vf_09C();
    virtual void vf_0A0(RwUInt32 arg_0);
    virtual RwInt32 vf_0AC();
    virtual void vf_0B0(RwInt32 arg_0, RwInt32 arg_4);
    virtual void vf_0B4();
    virtual RwUInt8 *vf_0E0();
    virtual RwInt32 vf_0E4(RwInt32 arg_0);
    virtual RwInt32 vf_0E8();
    virtual void vf_0EC(RwInt32 arg_0, RwInt32 arg_4);
    virtual RwInt8 *vf_0F0();
    virtual struct SplinePath *vf_0F4();
    virtual void vf_0F8(RwReal arg_0);
    virtual void vf_12C(RwInt32 arg_0);
    virtual RwInt32 vf_160();
    virtual void vf_170(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C);
    virtual RwInt32 vf_174();
    virtual void vf_178(RwInt32 arg_0);
    virtual RwReal vf_17C();
    virtual void vf_180(RwInt32 arg_0);
    virtual void vf_1AC(RwInt32 arg_0);
    virtual void vf_1C4(RwInt32 arg_0);
    virtual RwReal vf_1F0();
    virtual void vf_210(struct type_D05C0 *arg_0);
    virtual bool vf_224(struct type_3DF8D8 *arg_0, RwInt32 arg_4, RwInt32 *arg_8);
    virtual void vf_230();
    // +0x234, +0x238: whether it may go along its spline, and to its point
    // ("SetSplineGoodToGo", "SetPointGoodToGo").
    virtual void vf_234(RwInt32 arg_0);
    virtual void vf_238(RwInt32 arg_0);
    // +0x23C, +0x240: its attitude ("GetAttitude", "SetEngineAttitude").
    virtual RwInt32 vf_23C();
    virtual void vf_240(RwInt32 arg_0);

    RwUInt8 unk_3A8[0x8];
    RwInt32 *unk_3B0;           // its sounds' state (sub_83850, its set-up)
    RwUInt8 unk_3B4[0x20];
    RwInt32 unk_3D4;            // set when "AttachToEntity" gives it a ride
    type_D48D0 unk_3D8;         // the vehicle it rides ("RideVehicle")
    RwInt32 unk_3DC;            // the ride's tag
    type_15CCE0 unk_3E0;        // built by sub_15CCE0 in sub_176F60
    type_7CBD0_t unk_4E0[25];   // its second animation's translations
                                // relative to the bind pose (the set-up)
    RwUInt8 unk_670[0x2];
    RwInt16 unk_672;            // as type_3DAFC8's unk_7E2
                                // ("PlayHitDeathAnimDefaultData")
    RwV3d unk_674;              // a head shot's kick (vf_064)
    RwV3d unk_680;              // and the bullet's direction
    RwReal unk_68C;             // its second animation's scale
    RwReal unk_690;             // and its first's (by its definition, else
                                // random)
    RwInt8 unk_694;             // as type_3DAFC8's unk_805 (sub_5ACE0)
    RwInt8 unk_695;             // 2 after a head shot (vf_064)
    RwUInt8 unk_696[0x2];
    RwInt32 unk_698;            // its definition has a fixed scale
    RwUInt32 unk_69C;           // its hat tag ("HAT" for none)
    RwInt32 unk_6A0;            // its script object's handle (vf_09C,
                                // vf_0A0)
    union
    {
        RwUInt32 unk_6A4;       // its performance player's handle (vf_094;
        type_439E78_00 unk_6A4_h;   // the set-up copies it as the struct)
    };
    RwInt16 unk_6A8[2];         // its scene map entry (vf_0E0)
    RwUInt8 unk_6AC[2];
    RwUInt8 unk_6AE[0x2];
    RwInt32 unk_6B0;            // vf_088
    RwUInt8 unk_6B4[0xC];       // [3]: vf_0B4 copies it into unk_758
    RwUInt8 unk_6C0[0xC];
    type_129940 unk_6CC;
    type_129940 unk_6D8;
    RwReal unk_6E4;             // how far along its spline path
    RwUInt8 unk_6E8[0x8];
    RwMatrix unk_6F0;           // its offset from its spline ("SetSplineOffsetXYZ")
    RwReal unk_730;
    struct SplinePath *unk_734; // its spline path (vf_0F4)
    RwReal unk_738;             // the end of its spline path (sub_5B800)
    RwInt32 unk_73C;
    RwInt32 unk_740;            // its health (vf_174 to vf_180), up to
    RwInt32 unk_744;            // this
    RwInt8 unk_748[0xC];        // its hit-death values (vf_0F0)
    RwInt32 unk_754;            // vf_0AC, vf_0B0
    RwInt32 unk_758;
    RwInt32 unk_75C;            // its attitude (vf_23C, vf_240)
    RwUInt32 unk_760;           // flags: 1 set by vf_12C; 2 it may go along
                                // its spline (vf_234), 4 to its point
                                // (vf_238), the two exclusive
    RwInt32 unk_764;            // its trigger's command 17
    RwReal unk_768;             // its spline path's speed
    RwV3d unk_76C;              // its point on the path (at its own height)
    RwV3d unk_778;
    RwInt32 unk_784;
    RwUInt8 unk_788[0x8];

    // Built for the trigger arg_0 (its set-up, sub_1774C0).
    type_3DDB98(class GimpTrigger *arg_0)
    {
        sub_1774C0(arg_0);
    }
    ~type_3DDB98()
    {
        vf_230();
    }
    RwInt32 sub_1774C0(class GimpTrigger *arg_0);
    // The placement pair it is built in entity memory with (sub_6CCF0 and
    // the empty sub_19A750), and its plain operator delete for its deleting
    // destructor (folded into sub_19A750 too).
    static void *operator new(RwUInt32 arg_0, void *arg_4);
    static void operator delete(void *arg_0, void *arg_4);
    static void operator delete(void *arg_0);

    // Its body's and head's clumps (as type_3DAFC8's sub_13ACE0 and
    // sub_13ADA0).
    void sub_179AB0(RpClump *arg_0);
    void sub_179B70(RpClump *arg_0);
    // Moves it along its spline path or to its point (vf_03C).
    void sub_179530();
    // Takes arg_0 damage (as type_3DAFC8's sub_13C490).
    void sub_17AE80(RwInt32 arg_0);
    // Its weapon arg_0 into its hand (as type_3DAFC8's sub_138760).
    void sub_17BDD0(type_15CCE0 *arg_0, RwInt32 arg_4, RwInt32 arg_8);
    // As type_3DAFC8::sub_13F660 ("EnableWeaponRender").
    void sub_17A840(RwInt32 arg_0, RwInt32 arg_4);
    // As type_3DAFC8::sub_13DF40 ("SendFlying").
    void sub_17BF90(RwV3d *arg_0, RwReal arg_4);
    // Its goto point *arg_0 ("SetupGotoPoint").
    void sub_17BF10(RwV3d *arg_0);
    // Its spline path ("DivorceSplinePath" clears it with 0): from its
    // start, at 100 units a second (1/30 for a path over 2500000 long).
    void sub_178640(struct SplinePath *arg_0);
    // Sets its spline path's end, as type_3DA6C0::set_unk_444 (the clamp's
    // result dropped), out of line ("SetSplinePathFromName") and inline
    // ("SetSplineEndPosition", which expands the same body; the inline one
    // has no address and so no database name, and is named for its field).
    void sub_5B800(RwReal arg_0);
    void set_unk_738(RwReal arg_0)
    {
        unk_738 = arg_0;
        sub_22C20(unk_738, 0.0f, 1.0f);
    }

    // An inline accessor for unk_6F0, with no address and so no database name;
    // named for its field. Evidence: "SetSplineOffsetXYZ" holds the object
    // in a temporary of its own before taking the address.
    RwMatrix *get_unk_6F0()
    {
        return &unk_6F0;
    }
    // vf_024, as the image's vtable has it (a trivial body, folded into
    // sub_6FCD0 with every other copy).
    virtual struct type_3DDB98 *vf_024()
    {
        return this;
    }
    // vf_124, as the image's vtable has it (a trivial body, folded into
    // sub_15FB30 with every other copy).
    virtual void vf_124(RwReal arg_0)
    {
    }
    // vf_0B8, as the image's vtable has it (a trivial body, folded into
    // sub_19C380 with every other copy).
    virtual void vf_0B8(RwInt32 arg_0)
    {
        unk_758 = arg_0;
    }
    // vf_128, as the image's vtable has it (a trivial body, folded into
    // sub_73BC0 with every other copy).
    virtual RwReal vf_128()
    {
        return 0.0f;
    }
    // vf_228, as the image's vtable has it (a trivial body, folded into
    // sub_13ACC0 with every other copy).
    virtual bool vf_228()
    {
        type_3D3548::vf_228();
        return true;
    }
    // Overrides the image's vtable has whose bodies are type_3DAFC8's (ICF
    // folded them): vf_0BC (defined in unit_176E50) and vf_1F4.
    virtual RwInt32 vf_0BC();
    virtual RwReal vf_1F4()
    {
        return unk_3E0.sub_15EE20();
    }
};

// A particle system's callback while it follows a gimp (vf_170).
RwInt32 sub_179C10(struct type_F2FF0 *arg_0);

typedef RwChar type_3DDB98_size_check[sizeof(type_3DDB98) == 0x790 ? 1 : -1];

#endif
