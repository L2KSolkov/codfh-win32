/*
 * type_3DC9B0: an entity class derived from type_3D3548, anchored at its
 * vtable off_3DC9B0, which its constructor sub_166E00 installs after calling
 * type_3D3548's sub_CC960. sub_166FA0 initialises it (kind bits 0x80000 in
 * unk_2C, 0x3F12D57C in unk_4C0). Instances are chained in a list from
 * dword_4B86D0 through +0x10, and sub_16A340 finds the one whose unk_4EC
 * matches a path node's key (sub_16A380). It is the mounted weapon
 * (unit_166990; its settings are type_4E1B70's).
 */
#ifndef TYPE_3DC9B0_H
#define TYPE_3DC9B0_H

#include "rw/ostypes.h"
#include "types/type_3D3548.h"
#include "rw/rpatomic.h"
#include "rw/rphanim.h"

// The object registered under a handle (game/functions.h; its inline accessors call it).
struct type_67620;
type_67620 *sub_67620(RwInt32 arg_0);

struct type_3DC9B0 : type_3D3548
{
    // Overrides (unit_166990); only the widths of most are known.
    virtual void vf_038(RwReal arg_0);
    virtual void vf_03C(RwReal arg_0);
    virtual void vf_04C(RwReal arg_0);
    virtual void vf_054(RwInt32 arg_0);
    // Whether the key *arg_0 names its model (its settings' unk_00 or
    // unk_08, the settings its trigger picks).
    virtual RwInt32 vf_058(struct type_3DF8D8_04 *arg_0);
    // Its script object (the handle unk_5C4), and the handle itself.
    // Inline: the constructor's vtable emits them after it, before ??_G (the image's order).
    virtual type_3D3548 * vf_1F8(RwInt32 arg_0)
    {
        return unk_5C0.sub_D4910();
    }
    virtual void vf_1FC(type_3D3548 *arg_0, RwInt32 arg_4)
    {
        unk_5C0.sub_D48D0(arg_0);
    }
    virtual type_3D2E7C * vf_098()
    {
        return (type_3D2E7C *)sub_67620(unk_5C4);
    }
    virtual RwInt32 vf_09C()
    {
        return unk_5C4;
    }
    virtual void vf_0A0(RwUInt32 arg_0)
    {
        unk_5C4 = arg_0;
    }
    virtual void vf_170(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C);
    virtual void vf_1C4(RwInt32 arg_0);
    // Its user (unk_5C0; the argument is unused), and setting it.
    // Shuts it down (its destructor calls it too).
    virtual void vf_230();
    // Its destructor: takes it down, then the base's (not expanded). Out of
    // line at sub_166C60, with its scalar deleting destructor at sub_166C30.
    ~type_3DC9B0()
    {
        vf_230();
    }

    RwUInt8 unk_3A8[0x8];
    RwInt32 unk_3B0;            // its settings (sub_166990)
    RwInt32 unk_3B4;            // sub_16A680's result on reloading
    RwReal unk_3B8;             // the pitch and
    RwReal unk_3BC;             // yaw "SetMyMMGYawAndPitch" sets
    RwReal unk_3C0;             // the pitch and yaw before this aim
    RwReal unk_3C4;             // (sub_167BC0)
    RwUInt8 unk_3C8[0x8];
    RwMatrix unk_3D0;           // its weapon's tag matrix at the start
    RwReal unk_410;             // time since it last fired
    RwReal unk_414;             // its recoil, random each shot (sub_169380)
    RwReal unk_418;
    RwReal unk_41C;             // how far through its zoom (vf_04C)
    RwReal unk_420;             // 70
    RwInt32 unk_424;
    RwInt32 unk_428;
    RwUInt8 unk_42C[0x4];
    RwMatrix unk_430;           // its aim matrix
    RwInt32 unk_470;
    RwInt32 unk_474;
    RwInt32 unk_478;
    RwInt32 unk_47C;            // cleared when a player mounts it (type_3D32F8)
    RwInt32 unk_480;
    RwInt32 unk_484;
    RwInt32 unk_488;            // set while it is zoomed (the player's
                                // mounted state, type_10F710::sub_10B410)
    RwInt32 unk_48C;            // set while it is dismounted
    RwInt32 unk_490;
    RwInt32 unk_494;
    RwInt32 unk_498;            // its zoom kind (1 a vehicle's, 2 an
                                // animated background entity's)
    RwInt32 unk_49C;
    RwInt32 unk_4A0;
    RwInt32 unk_4A4;
    RpAtomic *unk_4A8;          // its "weapon" part
    type_129B10 unk_4AC;        // its frame
    RwInt32 unk_4B8;
    RwInt32 unk_4BC;            // fire even without seeing the target
                                // ("SetMyMMGToFireEvenIfICantSeeTarget")
    RwReal unk_4C0;             // the cosines of its pitch and yaw limits
    RwReal unk_4C4;             // (sub_27500 returns the first for a
                                // kind-0x11 node)
    RwReal unk_4C8;             // its settings' unk_18 by the difficulty
    RwInt32 unk_4CC;
    RwInt32 unk_4D0;
    struct type_7CBD0_hdr *unk_4D4; // its pose key (sub_16B0C0) and its
    RwInt32 unk_4D8;                // size
    RwInt32 unk_4DC;            // bones 1 to 3 of its hierarchy (kind 4)
    RwInt32 unk_4E0;
    RwInt32 unk_4E4;
    RwInt32 unk_4E8;
    RwInt32 unk_4EC;            // the key sub_16A340 matches
    RwInt32 unk_4F0;            // an NPC aims it (sub_16AAE0)
    RwInt32 unk_4F4;            // (sub_169380)
    RwUInt8 unk_4F8[0x8];
    RwMatrix unk_500;           // its "weapon" part's matrix at the start
    RwMatrix unk_540;           // its model's matrix at the aim's reset
    RwUInt8 unk_580[0x40];
    type_D48D0 unk_5C0;         // its user: the entity attached to the
                                // weapon ("VehicleMountedWeaponGetAttachedEntity")
    RwInt32 unk_5C4;            // its script object's handle
    type_129940 unk_5C8;        // its model
    RwInt32 unk_5D4;
    RwUInt8 unk_5D8[0x8];

    // Built for the trigger arg_0: in the class but never inlined (its
    // members have destructors), so sub_1669B0 reserves the expansion's
    // temporaries; out of line at sub_166AC0. Or from settings (sub_166E00,
    // the arguments of sub_166FA0).
    type_3DC9B0(type_712B0 *arg_0)
    {
        sub_166F20(arg_0);
    }
    type_3DC9B0(RwInt32 arg_0, RwInt32 arg_4, RwMatrix *arg_8, RwInt32 arg_C, type_712B0 *arg_10,
                RwInt32 arg_14, RwInt32 arg_18, RwInt32 arg_1C, RwInt32 arg_20, RwInt32 arg_24,
                RwInt32 arg_28);
    // Sets it up from its trigger arg_0 (the base's sub_CCCD0, then
    // sub_166FA0 with the trigger's settings).
    void sub_166F20(type_712B0 *arg_0);
    // Sets it up; only the widths are known.
    RwInt32 sub_166FA0(RwInt32 arg_0, RwInt32 arg_4, RwMatrix *arg_8, RwInt32 arg_C, type_712B0 *arg_10,
                    RwInt32 arg_14, RwInt32 arg_18, RwInt32 arg_1C, RwInt32 arg_20, RwInt32 arg_24,
                    RwInt32 arg_28);

    // Aims its weapon part by its pitch and yaw (within their limits),
    // following its frame while the player or an NPC uses it.
    void sub_167BC0();
    // Where a user gets off it (by value); only the width is known.
    void sub_16A030(RwMatrix *arg_0);
    // Whether the entity arg_0 may use it (by its kind and its trigger's
    // flags or tests), and what its NPC user's dismount runs; only the
    // widths are known.
    RwInt32 sub_169190(type_3D3548 *arg_0);
    void sub_16A620();
    // Its NPC's aim and its firing (vf_03C); only the widths are known.
    void sub_16AAE0();
    // An empty method kind 4 calls in place of the aim (vf_04C); folded
    // into pDtor by /OPT:ICF (config/aliases.txt).
    void pDtor();
    // Fires it (for its user, or nothing without one): its projectiles,
    // its ammunition, recoil and camera shake and its fire animation; 1
    // when it fired (sub_169B70), else 0.
    RwInt32 sub_169380();
    // Whether it can fire now; only the width is known.
    RwInt32 sub_169B70();
    // Its key (unk_4EC, for sub_16A340); only the width is known.
    RwInt32 sub_16A240();

    // An inline accessor for unk_4C0, with no address and so no database
    // name; named for its field. Evidence for its shape: sub_27500 copies
    // +0x4C0 into a compiler temporary below its own local and loads the
    // result from there, which is what an inline function holding its
    // result in a local expands to (docs/toolchain.md).
    RwReal get_unk_4C0()
    {
        RwReal r = unk_4C0;
        return r;
    }

    // The placement pair it is built in entity memory with (sub_6CCF0 and
    // the empty sub_19A750), and its plain operator delete for its deleting
    // destructor (folded into sub_19A750 too).
    static void *operator new(RwUInt32 arg_0, void *arg_4);
    static void operator delete(void *arg_0, void *arg_4);
    static void operator delete(void *arg_0);

    // The minimum and maximum burst and pause lengths ("GetMyMMG...").
    RwReal sub_16B5C0();
    RwReal sub_16B620();
    RwReal sub_16B680();
    RwReal sub_16B6E0();
    // Reloads: stores sub_16A680's result in unk_3B4 ("MountedWeaponReloaded").
    void sub_16A660();
    // Resets the aim matrix ("ResetNPCMountedWeaponAimMatrix").
    void sub_168F40();
    // Copies its clump's tag matrix into *arg_0 (the second tag when arg_4
    // is set), in world space unless arg_8 is set; 0 without a clump.
    // "PlayPickUpMMGPerformance" plays the pick-up at it.
    RwInt32 sub_16A3B0(RwMatrix *arg_0, RwInt32 arg_4, RwInt32 arg_8);
    // Mounts and dismounts the player arg_0 (type_3D32F8's vf_238, vf_23C).
    void sub_168820(struct type_10F710 *arg_0);
    void sub_168A90(struct type_10F710 *arg_0);
    // Whether it may be dismounted now (the player's sub_10FB70 passes 1);
    // only the widths are known.
    RwInt32 sub_169350(RwInt32 arg_0);
    // Draws itself for the player on it (the player's sub_110A60 passes
    // its pass argument); only the width is known.
    void sub_1679C0(RwInt32 arg_0);
    // Zooms in (arg_4 1) or out for the player arg_0; only the widths are
    // known.
    void sub_16A1D0(struct type_10F710 *arg_0, RwInt32 arg_4);
    // The pitch's limit (180 for none); only the width is known.
    RwReal sub_16A790();
    // Where it aims into *arg_0 (the soldier's vf_244), and aims from the
    // matrix *arg_0 (sub_13F350); only the widths are known.
    void sub_16A580(RwV3d *arg_0);
    void sub_16A440(RwMatrix *arg_0);
    // Fires (arg_0 1) or stops (the soldier's vf_1B4); mounts the soldier
    // arg_0 (0 when it may not) and dismounts it (sub_13F590).
    void sub_169170(RwInt32 arg_0);
    RwInt32 sub_168E10(struct type_3DAFC8 *arg_0);
    void sub_169000(struct type_3DAFC8 *arg_0);
    // The yaw's limit (180 for none); only the width is known.
    RwReal sub_16A890();
    // The matrix of its tag arg_4 (-1 for its muzzle) into *arg_0 (the
    // soldier's vf_170 spawns particles there); only the widths are known.
    void sub_169F30(RwMatrix *arg_0, RwInt32 arg_4);
    // Whether the point arg_0 is within its pitch and yaw limits (cosines
    // unk_4C0 and unk_4C4, widened by arg_4 and arg_8) from its clump's
    // frame (sub_1409C0); AIData::sub_404A0 asks with the target's
    // position and 0, 0. 0 without a clump.
    RwInt32 sub_16A990(RwV3d *arg_0, RwReal arg_4, RwReal arg_8);
    // The rounds it holds when reloaded: its trigger's (by kind) unless
    // -1, else its settings' unk_40.
    RwInt32 sub_16A680();
    // vf_028, as the image's vtable has it (a trivial body, folded into
    // sub_6FCD0 with every other copy).
    virtual struct type_3DC9B0 *vf_028()
    {
        return this;
    }
    // vf_040, as the image's vtable has it (a trivial body, folded into
    // sub_FB430 with every other copy).
    virtual void vf_040(RwReal arg_0)
    {
        type_3D3548::vf_040(arg_0);
    }
    // vf_044, as the image's vtable has it (a trivial body, folded into
    // sub_175E30 with every other copy).
    virtual void vf_044(RwReal arg_0)
    {
        type_3D3548::vf_044(arg_0);
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
typedef RwChar type_3DC9B0_size_check[sizeof(type_3DC9B0) == 0x5E0 ? 1 : -1];

// The index of the bone arg_4 in the hierarchy arg_0: an inline with no
// address and so no database name, named for what it returns. Evidence:
// the weapon's update (vf_04C) copies the hierarchy into an argument
// temporary and the index into a result local.
inline RwInt32 bone_index(RpHAnimHierarchy *arg_0, RwInt32 arg_4)
{
    RwInt32 r = RpHAnimIDGetIndex(arg_0, arg_4);
    return r;
}

// The axes the aim turns about (.rdata): x, y and z.
extern const RwV3d stru_3DC984;
extern const RwV3d stru_3DC990;
extern const RwV3d stru_3DC99C;
// The kind-4 weapon's procedural animation track (type_3DC9B0::vf_038).
void sub_16B0C0(struct type_7C8D0 *arg_0, struct type_80300 *arg_4, RwInt32 arg_8, bool arg_C);
// The NPC gunner's aim (sub_16AAE0): its largest turn a step (in degrees),
// the height of the aim's at row that always passes, and the angle under
// which it may fire.
extern RwReal flt_429E94;
extern RwReal flt_429E98;
extern RwReal flt_429E9C;
// The update callback of a particle system its vf_170 spawns (message
// 0x516): the system follows the weapon's bone unk_158; with the weapon
// gone, 0 (to end it) unless its definition runs for a set time.
RwInt32 sub_169BC0(struct type_F2FF0 *arg_0);

// The angles of the matrix arg_0 in degrees: the yaw into *arg_8, the
// pitch into *arg_4 and the roll into *arg_C (straight up or down: no roll).
void sub_167A50(RwMatrix *arg_0, RwReal *arg_4, RwReal *arg_8, RwReal *arg_C);

// The difficulty's multipliers of a mounted weapon's settings' unk_18
// (by dword_42B714).
extern RwReal flt_4F2860[3];
extern RwInt32 dword_42B714;
// That multiplier (1 outside 0 to 2): an inline with no address and so no
// database name, named for what it returns. Evidence: the set-up
// (sub_166FA0) stores both branches into one local among its inline
// temporaries, above `this` (a conditional's temporary would sit below).
inline RwReal mmg_difficulty_scale()
{
    RwReal r;

    if (dword_42B714 > -1 && dword_42B714 < 3)
        r = flt_4F2860[dword_42B714];
    else
        r = 1.0f;
    return r;
}

#endif
