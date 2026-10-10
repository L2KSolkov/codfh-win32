/*
 * type_1227C0: a projectile generator (the "PG_" commands), named after
 * sub_1227C0, which returns the one with the id arg_0. The image's own
 * strings call the class ProjectileGenerator ("WARNING: ProjectileGenerator::
 * ClearSound(): ..." in sub_121A50) and its pool m_freeGeneratorList
 * (sub_122230); the database names are kept. Its vtable is off_3DA67C
 * (10 slots); its constructor is sub_11F3D0 and its destructor, inline,
 * has its out-of-line copy at sub_11DBA0.
 *
 * Two kinds derive from it, each with its own trigger kind (the trigger's
 * unk_E0; sub_1223B0): type_11DB10 (0, off_3DA654), which fires bullets, and
 * type_11E440 (1, off_3DA6C0), which lobs shells. Both live in the pool
 * dword_4CEA48 (sized for the larger) and on the list dword_4CE8F8 (through
 * unk_100); each has an id in the table dword_4CE900 (sub_1226D0).
 *
 * It fires in bursts (unk_40 shots, unk_44 apart) at its target: an entity
 * (unk_24; unk_38 1, or 0 to pick the nearest, sub_120E80), a point (unk_54;
 * 2) or a spline path (unk_DC; 3), from its matrix (unk_70), which follows
 * its parent entity (unk_E0) and its turret and barrel (unk_E8, unk_EC).
 */
#ifndef TYPE_1227C0_H
#define TYPE_1227C0_H

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "rw/bamatrix.h"
#include "types/type_D48D0.h"
#include "types/type_129_base.h"
#include "types/type_F2880.h"
#include "types/type_67260.h"
#include "types/type_3DF8D8.h"

struct type_3D3548;
struct SplinePath;
struct type_16C2A0;
class ProjectileGeneratorTrigger;

// A generator's id: its index in the table dword_4CE900 in the low word, a
// serial in the high (sub_1226D0 builds one in a local).
struct type_4CE900_00
{
    union
    {
        RwInt32 unk_00;
        struct
        {
            RwUInt16 unk_00_w;
            RwUInt16 unk_02_w;
        };
    };
};

struct type_1227C0
{
    type_1227C0();
    // Defined here: its out-of-line copy (sub_11DBA0) is emitted with the
    // bullets' generator's constructor, for its unwinding.
    virtual ~type_1227C0()
    {
    }
    // +0x004: sets it up from its trigger arg_0 (sub_11F500).
    virtual void vf_004(ProjectileGeneratorTrigger *arg_0);
    // +0x008: stops it: its sound, its hold on its turret and barrel, its
    // particle systems and its trigger (sub_11F7D0).
    virtual void vf_008();
    // +0x00C: the kind's settings from arg_0; empty here (folded, /OPT:ICF,
    // into sub_15FB30).
    virtual void vf_00C(ProjectileGeneratorTrigger *arg_0)
    {
    }
    // +0x010: its update by arg_0 frames (1 a frame at 60 Hz; sub_11FAD0).
    virtual void vf_010(RwReal arg_0);
    // +0x014: turns its line-of-sight check on or off ("PG_EnableLOSCheck");
    // empty here (sub_15FB30).
    virtual void vf_014(RwInt32 arg_0)
    {
    }
    // +0x018 and +0x01C: checked downcasts to the bullets' and the shells'
    // generator (0 here, sub_1E4CB0; the kind's own returns this, sub_6FCD0).
    virtual type_1227C0 *vf_018()
    {
        return 0;
    }
    virtual type_1227C0 *vf_01C()
    {
        return 0;
    }
    // +0x020: whether it may fire at the point arg_0 (1 here, sub_1F5A00).
    virtual RwInt32 vf_020(RwV3d *arg_0)
    {
        return 1;
    }
    // +0x024: fires; whether it did (0 here, sub_1E4CB0).
    virtual RwInt32 vf_024()
    {
        return 0;
    }

    RwUInt8 unk_04[0xC];
    RwInt32 unk_10;             // its sound (the emitter's id)
    RwInt32 unk_14;             // 1 firing, 2 once updated, 0 stopped
    type_144940 unk_18;         // its trigger (unk_18.unk_08_pg)
    type_D48D0 unk_24;          // the entity it targets
    RwInt32 unk_28;             // forced to fire ("PG_ForcedFire")
    RwInt32 unk_2C;             // clear while its turret turns (sub_11EE20)
    RwInt32 unk_30;             // its firing stages are on
    RwInt32 unk_34;             // its firing stage (0 to 2; 3 none)
    RwInt32 unk_38;             // its target: 0 the nearest entity, 1 an
                                // entity, 2 a point, 3 its path
    RwInt32 unk_3C;             // the bursts left in its stage
    RwInt32 unk_40;             // the shots left in its burst
    RwReal unk_44;              // the frames to its next shot
    RwInt32 unk_48;             // its first shot at the target
    RwReal unk_4C;              // its turret's turn rate
    RwInt32 unk_50;             // the shots left before its long pause
    RwV3d unk_54;               // the point it targets
    union
    {
#ifdef CODFH_SP // a real in single player (SP 0xD84D2: fstp)
        RwReal unk_60;
#else
        RwInt32 unk_60;         // the target's spread ("PG_TargetPoint"'s
#endif
        RwReal unk_60_r;        // argument 4, passed on as raw bits)
    };
    RwUInt8 unk_64[0xC];
    RwMatrixTag unk_70;         // its matrix
    RwV3d unk_B0;               // the point it aims at
    RwV3d unk_BC;               // and the last
    RwReal unk_C8;              // the target's height offset
    RwReal unk_CC;              // its place along its path (0 to 1)
    RwReal unk_D0;              // its speed along it
    RwInt32 unk_D4;             // its firing-arc check is on (always 1)
    RwInt32 unk_D8;             // passed to sub_15F2C0
    SplinePath *unk_DC;         // its path
    type_D48D0 unk_E0;          // its parent entity
    RwInt32 unk_E4;             // its attach point on it
    type_D48D0 unk_E8;          // its turret
    type_D48D0 unk_EC;          // its barrel
    RwInt32 unk_F0;             // how it follows its parent: 0 not, 1 its
                                // frame, 2 the tagged matrix 'PGN0'+unk_E4
    RwInt32 unk_F4;             // likewise with the turret's 'FIRE'
    RwInt32 unk_F8;             // likewise with the turret's 'OPR0'
    RwInt32 unk_FC;             // likewise with the turret's 'ATMT'
    type_1227C0 *unk_100;       // the next on the list dword_4CE8F8
    union
    {
        RwInt32 unk_104;        // its id (sub_1226D0)
        type_4CE900_00 unk_104_h; // the same id as its index/serial record
    };
    type_F2880 unk_108[3];      // its muzzle particle systems
    RwV3d unk_12C;              // its turret's facing
    RwReal unk_138;             // the frames its turret holds its aim
    RwReal unk_13C;             // once the target leaves its arc, left
    RwInt32 unk_140;            // it pauses when its turret or barrel is hit
    RwReal unk_144;             // the frames left of that pause
    RwUInt32 unk_148;           // that pause's range in frames (the trigger's
                                // unk_220)
    RwUInt32 unk_14C;           // the turret's and barrel's hit points (vf_174),
                                // high and low words, as last seen

    // Its update of the matrix from its parent (sub_11F9E0), whether its
    // parent, barrel and turret still stand (sub_11F8E0), its forced shot
    // (sub_120150), the burst's end (sub_120170), its first firing stage
    // (sub_120310) and the next (sub_1205C0).
    void sub_11F9E0();
    RwInt32 sub_11F8E0();
    void sub_120150();
    void sub_120170();
    void sub_120310();
    void sub_1205C0();
    // Its shot at the point it aims at with the spread arg_0 (sub_120740):
    // the first at the target (sub_120930), then the next (sub_120A70), or
    // at a point (sub_1207A0); whether it fired.
    RwInt32 sub_120740(RwReal arg_0);
    RwInt32 sub_1207A0();
    void sub_120930(RwReal arg_0);
    void sub_120A70();
    // Picks its target (sub_120DE0: the player, the nearest enemy, or none);
    // whether it has one. sub_120E80 finds the nearest.
    RwInt32 sub_120DE0();
    type_3D3548 *sub_120E80();
    // Its line of sight to arg_0 from its matrix or arg_4 (sub_1409C0).
    RwInt32 sub_1210A0(RwV3d *arg_0);
    RwInt32 sub_121100(RwV3d *arg_0, RwMatrix *arg_4);
    // Starts its sound (sub_121150); ClearSound (sub_121A50).
    void sub_121150();
    void sub_121A50();
    // Spreads the direction arg_0 by its random angles into arg_4's rows
    // (sub_121230).
    void sub_121230(RwV3d *arg_0, RwMatrix *arg_4);
    // Its default target ("PG_TargetDefault"), a point ("PG_TargetPoint"),
    // a named point ("PG_TargetNamedPoint"), an entity
    // ("PG_TargetObjectByScript"); its firing stages on or off
    // ("PG_EnableFiringStages").
    void sub_121870();
#ifdef CODFH_SP // the spread is a real in single player (SP 0xD83C0 passes its float copy)
    void sub_1218A0(RwV3d *arg_0, RwReal arg_4);
    void sub_121910(type_3DF8D8_04 *arg_0, RwReal arg_4);
#else
    void sub_1218A0(RwV3d *arg_0, RwInt32 arg_4);
    void sub_121910(type_3DF8D8_04 *arg_0, RwInt32 arg_4);
#endif
    RwInt32 sub_121960(type_3D3548 *arg_0);
    void sub_121A30(RwInt32 arg_0);
    // Its id (sub_121B30); its particle system arg_0 held at arg_4, which
    // then follows it (sub_121B90); the one held there (sub_121BE0).
    void sub_121B30(RwInt32 arg_0);
    void sub_121B90(struct type_F2FF0 *arg_0, RwInt32 arg_4);
    struct type_F2FF0 *sub_121BE0(RwInt32 arg_0);
    // Its default path: the spline of the object under its trigger's key
    // (+0xE8), or 0.
    SplinePath *sub_121C10();
    // Sets its parent entity and attach point ("PG_SetParentAndAttachPoint";
    // 0 and 0 detach it).
    void sub_121C70(type_3D3548 *arg_0, RwInt32 arg_4);
    // Stops (0) or starts (1) firing ("PG_ManipulateProjectileGenerator"),
    // finding its parent, turret and barrel on starting.
    void sub_121D20(RwInt32 arg_0);
    // The point it fires from into *arg_0.
    void sub_122150(RwV3d *arg_0);
    // The default path through a local: an inline function with no address
    // and so no database name; named for what it returns. Evidence:
    // "PG_SetSplinePathFromName" stores sub_121C10's result in a local
    // placed among the checks' (an inline's local) before assigning it.
    SplinePath *get_default_path()
    {
        SplinePath *r = sub_121C10();
        return r;
    }
    // Its turret's turn rate through a local of its own; an inline with no
    // address, named for what it returns. Evidence: sub_11EE20 scales by it
    // through a separate temporary for each component.
    RwReal get_turn_rate()
    {
        RwReal r = unk_4C;
        return r;
    }
    // The next on the list and its id, each through a local of its own:
    // inlines with no address, named for their fields. Evidence:
    // sub_1225D0 reads both through temporaries.
    type_1227C0 *get_unk_100()
    {
        type_1227C0 *r = unk_100;
        return r;
    }
    // Evidence: the two factories sub_122410/sub_1224F0 allocate this
    // return temporary at -0x24 before the list getter's inline local
    // at -0x28. Returning the existing id record reproduces that order;
    // a scalar getter's local is allocated after the list getter's.
    type_4CE900_00 get_unk_104_h()
    {
        return unk_104_h;
    }
    // Its trigger through a local of its own; an inline with no address,
    // named for what it returns.
    ProjectileGeneratorTrigger *get_trigger()
    {
        ProjectileGeneratorTrigger *r = unk_18.unk_08_pg;
        return r;
    }
};
typedef RwChar type_1227C0_size_check[sizeof(type_1227C0) == 0x150 ? 1 : -1];

// The bullets' generator (its trigger's kind 0; vtable off_3DA654).
struct type_11DB10 : type_1227C0
{
    type_11DB10();
    virtual void vf_004(ProjectileGeneratorTrigger *arg_0);
    virtual void vf_008();
    virtual void vf_00C(ProjectileGeneratorTrigger *arg_0);
    virtual void vf_010(RwReal arg_0);
    virtual void vf_014(RwInt32 arg_0);
    virtual type_1227C0 *vf_018()
    {
        return this;
    }
    virtual RwInt32 vf_020(RwV3d *arg_0);
    virtual RwInt32 vf_024();

    // Pooled: its deleting destructor frees nothing, and it is built in its
    // pool slot with the placement pair (sub_6CCF0 and the empty sub_19A750,
    // folded by /OPT:ICF).
    void operator delete(void *arg_0)
    {
    }
    static void *operator new(RwUInt32 arg_0, void *arg_4);
    static void operator delete(void *arg_0, void *arg_4);

    type_10F710_1A48_29C unk_150;   // a bullet's settings (kind 0)
    type_67260 unk_188;             // or a projectile's (kinds 2 and 3),
    RwReal unk_1D8;                 // copied from its trigger (vf_00C)
    RwInt32 unk_1DC;
    RwReal unk_1E0;
    RwReal unk_1E4;
    RwInt32 unk_1E8;
    RwInt32 unk_1EC;
    RwReal unk_1F0;
    RwReal unk_1F4;
    RwInt32 unk_1F8;
    RwInt32 unk_1FC;
    RwInt32 unk_200;
    RwReal unk_204;
    RwInt32 unk_208;
    RwInt32 unk_20C;                // its line-of-sight check is on ("PG_EnableLOSCheck")
};
typedef RwChar type_11DB10_size_check[sizeof(type_11DB10) == 0x210 ? 1 : -1];

// The shells' settings as sub_15F2C0 takes them (0xB0 bytes; its table 7 or
// 8), built by sub_11E4A0.
struct type_11E4A0 : type_67260
{
    type_11E4A0();

    RwReal unk_50;              // copied from the shells' generator's
    RwInt32 unk_54;             // trigger (type_11E440::vf_00C)
    RwReal unk_58;
    RwReal unk_5C;
    RwInt32 unk_60;
    RwInt32 unk_64;
    RwReal unk_68;
    RwReal unk_6C;
    RwInt32 unk_70;
    RwInt32 unk_74;
    RwInt32 unk_78;
    RwReal unk_7C;
    RwInt32 unk_80;
    RwInt32 unk_84;
    RwInt32 unk_88;
    RwInt32 unk_8C;
    RwInt32 unk_90;
    RwReal unk_94;
    RwReal unk_98;              // the shell's flight time (sub_11E850)
    RwReal unk_9C;
    RwReal unk_A0;
    RwV3d unk_A4;               // the point it aims at
};

// The shells' generator (its trigger's kind 1; vtable off_3DA6C0).
struct type_11E440 : type_1227C0
{
    type_11E440();
    virtual void vf_004(ProjectileGeneratorTrigger *arg_0);
    virtual void vf_008();
    virtual void vf_00C(ProjectileGeneratorTrigger *arg_0);
    virtual void vf_010(RwReal arg_0);
    virtual type_1227C0 *vf_01C()
    {
        return this;
    }
    virtual RwInt32 vf_024();

    // As type_11DB10's.
    void operator delete(void *arg_0)
    {
    }
    static void *operator new(RwUInt32 arg_0, void *arg_4);
    static void operator delete(void *arg_0, void *arg_4);

    type_11E4A0 unk_150;
};
typedef RwChar type_11E440_size_check[sizeof(type_11E440) == 0x200 ? 1 : -1];

// The id table's entries: an id and the generator (0x28 of them from 1;
// dword_4CE900).
struct type_4CE900 : type_4CE900_00
{
    type_1227C0 *unk_04;
};
extern type_4CE900 dword_4CE900[41];
extern RwInt32 dword_4CE8F0;        // the next serial
extern type_1227C0 *dword_4CE8F8;   // the generators' list
extern struct type_16C2A0 dword_4CEA48;    // their pool, m_freeGeneratorList

// The callbacks sub_121D20 installs on its turret (sub_11EE20, turning it to
// the target) and barrel (sub_11F2B0, keeping it at the tagged matrix
// 'OPR0'+arg_8), with the generator arg_4 (type_3D3548::sub_D3700).
void sub_11EE20(type_3D3548 *arg_0, type_1227C0 *arg_4, RwInt32 arg_8);
void sub_11F2B0(type_3D3548 *arg_0, type_1227C0 *arg_4, RwInt32 arg_8);
// Builds the rows of *arg_4 about the direction *arg_0 (sub_1213D0), and
// the direction to lob a shell from *arg_0 to *arg_4 at the speed arg_8 with
// the gravity arg_C (the high arc with arg_10) into *arg_14; whether it can.
void sub_1213D0(RwV3d *arg_0, RwMatrix *arg_4);
RwInt32 sub_1215E0(RwV3d *arg_0, RwV3d *arg_4, RwReal arg_8, RwReal arg_C, RwInt32 arg_10,
                   RwMatrix *arg_14);
// A particle system's callback while a generator holds it: follows its
// matrix (sub_121B50).
RwInt32 sub_121B50(struct type_F2FF0 *arg_0);
// The pool's set-up, reset and shut-down (sub_122230, sub_1222A0,
// sub_1222D0); all generators' update by arg_0 frames (sub_1222F0).
void sub_122230();
void sub_1222A0();
void sub_1222D0();
void sub_1222F0(RwReal arg_0);
type_1227C0 *sub_1227C0(RwInt32 arg_0);
// Creates a projectile generator for the trigger arg_0 (kind 0x13),
// returning its id, and destroys one ("PG_ManipulateProjectileGenerator"
// operations 0 and 3); sub_122410 and sub_1224F0 create each kind.
RwInt32 sub_1223B0(class type_712B0 *arg_0);
RwInt32 sub_122410(ProjectileGeneratorTrigger *arg_0);
RwInt32 sub_1224F0(ProjectileGeneratorTrigger *arg_0);
void sub_1225D0(type_1227C0 *arg_0);
// Destroys them all (sub_122680); gives arg_0 an id and frees one
// (sub_1226D0, sub_122790).
void sub_122680();
RwInt32 sub_1226D0(type_1227C0 *arg_0);
void sub_122790(RwInt32 arg_0);

#endif
