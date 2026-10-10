/*
 * The projectiles (unit_15F1B0): nine pools (dword_4E19F8, one per kind,
 * 0x28 bytes each) of projectile objects built in place by kind
 * (type_4E19F8::sub_15F590, which sub_15F2C0 reaches through the settings'
 * unk_00). The classes are named for their vtables:
 *
 *   type_3DC7F8  the base (0x70; kinds 0 and 1)
 *   type_3DC798  with a model (0x8C; kind 3), and type_3DC6D8 (0xC4; kind
 *                8) derived from it
 *   type_3DC738  (0x8C; kind 7)
 *   type_3DC858  (0x98; kind 4, sub_15FCA0 its constructor)
 *   type_3DC8B8  (0x1B0; kinds 2, 5 and 6, sub_15FD30 its constructor)
 *
 * Their slot 0x58 gives their class code (0, 4, 3, 2, 6 and 5); the
 * constant and empty slots are folded by /OPT:ICF (config/aliases.txt).
 */
#ifndef TYPES_PROJECTILE_H
#define TYPES_PROJECTILE_H

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "rw/bamatrix.h"
#include "types/type_129_base.h"
#include "types/type_D48D0.h"
#include "types/type_F2880.h"
#include "types/alfasched.h"
#include "types/type_495F0.h"
#include "rw/rpcollis.h"
#include "types/type_92430.h"

struct type_3D3548;
typedef struct RwCamera RwCamera;

// A projectile's colours and life (vf_000's arg_C; stru_429E54 without
// one; ProjectileGeneratorTrigger copies it too): two packed colours it picks between, its life's range and three
// values it keeps.
struct type_429E54
{
    RwUInt32 unk_00;            // a colour (0xAARRGGBB)
    RwUInt32 unk_04;            // the other (0: the first)
    union
    {
        RwInt32 unk_08;         // written as integers; read as the tracer's
        RwReal unk_08_r;        // width,
    };
    union
    {
        RwInt32 unk_0C;
        RwReal unk_0C_r;        // height
    };
    union
    {
        RwInt32 unk_10;         // written as integers (the trigger's
        RwReal unk_10_r;        // HandleAttributes); read as its length's
    };                          // (and life's) range: from unk_10_r
    union
    {
        RwInt32 unk_14;
        RwReal unk_14_r;        // to unk_10_r + unk_14_r
    };
    union
    {
        RwInt32 unk_18;
        RwReal unk_18_r;        // and fading distance
    };
};
extern type_429E54 stru_429E54;
// The radius a pool-6 projectile is hit within (22).
extern RwReal dword_429E70;
// The grenades' gravity per frame (-0.069).
extern RwReal dword_429E90;
// A velocity from arg_0 and arg_4 under that gravity (the grenade's step).
#ifndef CODFH_SP // static in single player (unit_161C50)
void sub_164210(RwV3d *arg_0, RwV3d *arg_4, RwV3d *arg_8);
#endif
// A grenade's unk_88 at its start (20).
extern RwReal dword_429E74;
// The most a grenade spins per frame (7).
extern RwReal dword_429E78;
// How deep a grenade's step may repeat itself for the rest of a frame (1),
// and how deep it is now.
extern RwInt32 dword_429E7C;
extern RwInt32 dword_4E1B60;
// How far a grenade stays off what it hits (0.1).
extern RwReal dword_429E80;
// The squared speed along the normal below which a grenade stops (10).
extern RwReal dword_429E84;
// A grenade's sphere radii (32 and 200).
extern RwReal dword_429E88;
extern RwReal dword_429E8C;

// The values a grenade's step passes with "GrenadeAlert" (sub_6B5F0's
// arg_10, three): the entity's distance, the grenade's fuse and the
// entities alerted so far.
struct type_161FC0_alert
{
    RwReal unk_00;
    RwReal unk_04;
    RwInt32 unk_08;
};
// And with "GrenadeExplode" (four): where it went off and the entity's
// distance.
struct type_161FC0_explode
{
    RwV3d unk_00;
    RwReal unk_0C;
};
// How long a tracer waits before it is drawn (4).
extern RwReal dword_429E40;

// A projectile's line query (0x5C bytes, on its step's stack): the nearest
// hit so far along the line (from 1e37), what it hit (an atomic, for the
// world atomics' callback sub_1660C0) and where, the projectile's flags,
// owner and owner's flags, the search id and the surface. sub_161470 resets
// it.
struct type_161470
{
    RwReal unk_00;              // the nearest hit's fraction of the line
    RwReal unk_04;
    RwInt32 unk_08;
    RpAtomic *unk_0C;           // the atomic hit (0: the world)
    RpAtomic *unk_10;           // the atomic being tested (sub_1660C0)
    RwInt32 unk_14;             // the projectile's flags
    struct type_3D3548 *unk_18; // its owner
    RwInt32 unk_1C;             // its owner's flags
    RwV3d unk_20;               // the hit point
    RwV3d unk_2C;               // the surface's normal
    RwV3d unk_38;
    RwInt32 unk_44;
    RwInt32 unk_48;             // the search's id (sub_8F940)
    RwInt32 unk_4C;             // the surface (0xFFFF: none)
    RwReal unk_50;              // a grenade's sphere radii (dword_429E88,
    RwReal unk_54;              // dword_429E8C)
    RwInt32 unk_58;

#ifdef CODFH_SP // inline in single player (SP 0x1041A0, 0x105CD0 and 0x1063A0 expand it)
    void sub_161470()
    {
        unk_00 = 1.0e37f;
        unk_0C = 0;
        unk_10 = 0;
        unk_18 = 0;
        unk_08 = 0;
        unk_04 = 1.0e37f;
        unk_50 = 0;
        unk_54 = 0;
        unk_58 = 0;
    }
#else
    void sub_161470();
#endif
};
typedef RwChar type_161470_size_check[sizeof(type_161470) == 0x5C ? 1 : -1];
// A material's game data (sub_FC000): an inline with no address and so no
// database name, named for what it returns. Evidence: the projectiles'
// step (type_3DC7F8::vf_014) copies the material into an argument
// temporary and the data into a result local.
inline type_FC000 *material_data(void *arg_0)
{
    type_FC000 *r = sub_FC000(arg_0);
    return r;
}
// The atomics' triangles' callback of the line query (sub_1660C0 runs it):
// the nearest so far and its atomic.
RpCollisionTriangle *sub_166950(RpIntersection *arg_0, RpCollisionTriangle *arg_4, RwReal arg_8,
                                void *arg_C);
// The world atomics' callback of the projectiles' line query (its data a
// type_161470).
RpAtomic *sub_1660C0(RpIntersection *arg_0, RpWorldSector *arg_4, RpAtomic *arg_8, RwReal arg_C,
                     void *arg_10);

struct type_3DC7F8
{
    // Starts it: its flags arg_0, its owner arg_4, its settings arg_8 (and
    // their particle effects on it) and colours arg_C.
    virtual void vf_000(RwInt32 arg_0, type_3D3548 *arg_4, type_439A48 *arg_8, type_429E54 *arg_C);
    virtual RwInt32 vf_004();
    // Its position from the matrix arg_0, its velocity, and unk_48.
    virtual void vf_008(RwMatrix *arg_0);
    virtual void vf_00C(RwV3d *arg_0);
    virtual void vf_010(RwInt32 arg_0);
    // Its step by arg_0; true when it is done.
    virtual bool vf_014(RwReal arg_0);
    virtual void vf_018();
    virtual void vf_01C(RwReal arg_0);
    virtual RwReal vf_020();
    // Its sound arg_8 under the key arg_4 at arg_0 (-2: the key's own),
    // with the flags arg_10 (0x40 without).
    virtual void vf_024(RwV3d *arg_0, type_3DF8D8_04 *arg_4, RwInt32 arg_8, type_3D3548 *arg_C,
                        RwInt32 arg_10);
    // Its hit on arg_0 at the matrix arg_4 (for arg_8): the entity's
    // effects (vf_034) for soldiers, players and some others, and its
    // surface's (vf_02C).
    virtual void vf_028(type_3D3548 *arg_0, RwMatrix *arg_4, type_3D3548 *arg_8);
    // The surface arg_0's particles, decal (with arg_C) and sound.
    virtual void vf_02C(RwInt32 arg_0, RwMatrix *arg_4, type_3D3548 *arg_8, RwInt32 arg_C);
    // Its particle effect at the matrix arg_0.
    virtual void vf_030(RwMatrix *arg_0);
    // Blood on the entity arg_0 at the matrix arg_4 (a third of the time).
    virtual void vf_034(type_3D3548 *arg_0, RwMatrix *arg_4);
    virtual void vf_038(RwMatrix *arg_0);
    virtual RwInt32 vf_03C();
    virtual RwInt32 vf_040();
    virtual RwReal vf_044();
    virtual RwReal vf_048();
    virtual void vf_04C();
    // Its time taken down by its settings' unk_50, and its time.
    virtual void vf_050();
    virtual RwReal vf_054();
    virtual RwInt32 vf_058();

    RwV3d unk_04;               // its position
    RwV3d unk_10;               // its velocity
    RwReal unk_1C;              // its time (from dword_4B87C8)
    RwReal unk_20;              // 480
    RwInt32 unk_24;             // its flags
    RwInt32 unk_28;
    RwUInt16 unk_2C;
    RwUInt8 unk_2E[0x2];
    type_D48D0 unk_30;          // its owner
    RwInt32 unk_34;             // its owner's flags (or its own)
    RwInt32 unk_38;
    type_439A48 *unk_3C;        // its settings
    type_3DC7F8 *unk_40;        // the next in its pool's list
    type_3DC7F8 *unk_44;        // and the previous
    RwInt32 unk_48;
    RwReal unk_4C;              // its life (and a tracer's length)
    RwReal unk_50;              // a tracer's width,
    RwReal unk_54;              // height
    RwReal unk_58;              // and fading distance
    RwRGBAReal unk_5C;          // its colour
    RwInt32 unk_6C;             // done

    type_3DC7F8()
    {
    }
    // Its blast at the matrix arg_0 (the owner arg_4's side, the settings
    // arg_8's radii, else its own), with the player hit by explosions for
    // it; then the kinds 2 to 6 and 8 within its radius set off too.
    void sub_1614E0(RwMatrix *arg_0, type_3D3548 *arg_4, type_439A48 *arg_8);
    // Its time taken down by its settings' unk_50 as vf_050 does, but
    // through a local: an inline with no address and so no database name,
    // named for what it does. Evidence: the step (vf_014) pushes back the
    // pool-6 projectile it hits so, holding its settings in a temporary.
    void advance_time()
    {
        type_439A48 *r = unk_3C;
        unk_1C = unk_1C - r->unk_50;
    }
    // Sets off the projectiles of the kind arg_0 within the squared
    // distance arg_4 of it (their vf_04C and vf_050).
    void sub_1616F0(RwInt32 arg_0, RwReal arg_4);
    // Empty; the derived constructors' unwinding calls it (sub_15FDF0).
    ~type_3DC7F8();

    // The pools' placement pair: operator new (sub_6CCF0, which returns
    // arg_4) and an empty operator delete (folded into sub_19A750).
    static void *operator new(RwUInt32 arg_0, void *arg_4);
    static void operator delete(void *arg_0, void *arg_4);
};
typedef RwChar type_3DC7F8_size_check[sizeof(type_3DC7F8) == 0x70 ? 1 : -1];

struct type_3DC798 : type_3DC7F8
{
    virtual void vf_000(RwInt32 arg_0, type_3D3548 *arg_4, type_439A48 *arg_8, type_429E54 *arg_C);
    virtual RwInt32 vf_004();
    virtual void vf_008(RwMatrix *arg_0);
    virtual bool vf_014(RwReal arg_0);
    virtual void vf_01C(RwReal arg_0);
    virtual RwReal vf_020();
    virtual void vf_028(type_3D3548 *arg_0, RwMatrix *arg_4, type_3D3548 *arg_8);
    virtual void vf_02C(RwInt32 arg_0, RwMatrix *arg_4, type_3D3548 *arg_8, RwInt32 arg_C);
    virtual void vf_038(RwMatrix *arg_0);
    virtual RwInt32 vf_03C();
    virtual RwInt32 vf_040();
    virtual RwReal vf_044();
    virtual RwReal vf_048();
    virtual RwInt32 vf_058();

    type_129940 unk_70;         // its model (a copy of its settings')
    RwUInt8 unk_7C[0x10];

    type_3DC798()
    {
    }
};
typedef RwChar type_3DC798_size_check[sizeof(type_3DC798) == 0x8C ? 1 : -1];

struct type_3DC738 : type_3DC7F8
{
    virtual void vf_000(RwInt32 arg_0, type_3D3548 *arg_4, type_439A48 *arg_8, type_429E54 *arg_C);
    virtual RwInt32 vf_004();
    virtual void vf_01C(RwReal arg_0);
    virtual RwReal vf_020();
    virtual RwInt32 vf_03C();
    virtual RwInt32 vf_040();
    virtual RwReal vf_044();
    virtual RwReal vf_048();
    virtual RwInt32 vf_058();

    RwReal unk_70;
    RwReal unk_74;
    RwReal unk_78;              // its fall speed
    RwReal unk_7C;              // and its gain
    RwReal unk_80;              // time before it falls
    RwInt32 unk_84;             // it falls
    RwInt32 unk_88;

    type_3DC738()
    {
    }
};
typedef RwChar type_3DC738_size_check[sizeof(type_3DC738) == 0x8C ? 1 : -1];

struct type_3DC6D8 : type_3DC798
{
    virtual void vf_000(RwInt32 arg_0, type_3D3548 *arg_4, type_439A48 *arg_8, type_429E54 *arg_C);
    virtual bool vf_014(RwReal arg_0);
    virtual void vf_01C(RwReal arg_0);
    virtual RwReal vf_020();
    virtual void vf_028(type_3D3548 *arg_0, RwMatrix *arg_4, type_3D3548 *arg_8);
    virtual void vf_02C(RwInt32 arg_0, RwMatrix *arg_4, type_3D3548 *arg_8, RwInt32 arg_C);
    virtual void vf_038(RwMatrix *arg_0);
    virtual RwInt32 vf_03C();
    virtual RwInt32 vf_040();
    virtual RwReal vf_044();
    virtual RwReal vf_048();
    virtual RwInt32 vf_058();

    RwReal unk_8C;
    RwReal unk_90;
    RwUInt8 unk_94[0x4];
    RwReal unk_98;
    RwReal unk_9C;
    RwReal unk_A0;
    RwInt32 unk_A4;
    RwInt32 unk_A8;
    RwReal unk_AC;              // time before its sound
    RwInt32 unk_B0;             // its sound
    RwInt32 unk_B4;             // started
    RwV3d unk_B8;               // where it heads

    type_3DC6D8()
    {
    }
};
typedef RwChar type_3DC6D8_size_check[sizeof(type_3DC6D8) == 0xC4 ? 1 : -1];

struct type_3DC858 : type_3DC7F8
{
    virtual void vf_000(RwInt32 arg_0, type_3D3548 *arg_4, type_439A48 *arg_8, type_429E54 *arg_C);
    virtual RwInt32 vf_004();
    virtual void vf_008(RwMatrix *arg_0);
    virtual bool vf_014(RwReal arg_0);
    virtual void vf_01C(RwReal arg_0);
    virtual RwReal vf_020();
    virtual void vf_028(type_3D3548 *arg_0, RwMatrix *arg_4, type_3D3548 *arg_8);
    virtual void vf_02C(RwInt32 arg_0, RwMatrix *arg_4, type_3D3548 *arg_8, RwInt32 arg_C);
    virtual void vf_038(RwMatrix *arg_0);
    virtual RwInt32 vf_03C();
    virtual RwInt32 vf_040();
    virtual RwReal vf_044();
    virtual RwReal vf_048();
    virtual RwInt32 vf_058();

    type_F2880 unk_70;          // a particle system
    type_129940 unk_7C;         // its model (a copy of its settings')
    RwUInt8 unk_88[0x10];

    // Defined here: VC7.1 does not inline it (its members have destructors),
    // but the factory (sub_15F590) reserves its temporaries; its out-of-line
    // copy is sub_15FCA0.
    type_3DC858()
    {
    }
};
typedef RwChar type_3DC858_size_check[sizeof(type_3DC858) == 0x98 ? 1 : -1];

struct type_3DC8B8 : type_3DC7F8
{
    virtual void vf_000(RwInt32 arg_0, type_3D3548 *arg_4, type_439A48 *arg_8, type_429E54 *arg_C);
    virtual RwInt32 vf_004();
    virtual void vf_008(RwMatrix *arg_0);
    virtual bool vf_014(RwReal arg_0);
    virtual void vf_01C(RwReal arg_0);
    virtual RwReal vf_020();
    virtual void vf_038(RwMatrix *arg_0);
    virtual RwInt32 vf_03C();
    virtual RwInt32 vf_040();
    virtual RwReal vf_044();
    virtual RwReal vf_048();
    virtual void vf_04C();
    virtual RwInt32 vf_058();
    virtual void *vf_05C();
    // Marks it for removal (the pool of kind 6 frees its oldest when full).
    virtual void vf_060();
    virtual RwInt32 vf_064();

    RwInt32 unk_70;             // its settings' table (unk_00)
    RwInt32 unk_74;             // its owner's weapon in hand (-1: none)
    RwInt32 unk_78;             // clear: it stops when it lands
    RwV3d unk_7C;               // the axis it spins about (its step's cross
                                // product; RwMatrixRotate)
    RwReal unk_88;              // its spin per frame: 20 (dword_429E74)
    RwInt32 unk_8C;
    RwInt32 unk_90;
    type_129940 unk_94;         // its model (a copy of its settings')
    RwInt32 unk_A0;
    RwInt32 unk_A4;
    type_D48D0 unk_A8[32];      // entities not told "GrenadeExplodeCancel"
    RwInt32 unk_128;            // set: no "GrenadeExplodeCancel" (vf_004)
    RwInt32 unk_12C;
    RwV3d unk_130;              // where it will land (sub_164210; vf_05C)
    RwInt32 unk_13C;            // how it sticks to unk_1A0: 1 to its frame,
                                // 2 and 3 to its nearest bone
    RwInt32 unk_140;            // that bone (-1: none)
    RwV3d unk_144;              // its offset from the bone
    RwInt32 unk_150;
    RwInt32 unk_154;            // the entities alerted
    RwInt32 unk_158;            // its bounces off the world
    RwInt32 unk_15C;            // marked for removal
    RwMatrixTag unk_160;        // the matrix of the frame it sticks to
    type_D48D0 unk_1A0;         // the entity it sticks to
    RwUInt8 unk_1A4[0xC];

    // Likewise (sub_15FD30).
    type_3DC8B8()
    {
    }
};
typedef RwChar type_3DC8B8_size_check[sizeof(type_3DC8B8) == 0x1B0 ? 1 : -1];

// A pool of projectiles of one kind (0x28 bytes): its kind, its memory pool
// and its live list. Its constructor and destructor are out of line
// (sub_160420, sub_160440) for the array's dynamic initializer.
struct type_4E19F8
{
    RwInt32 unk_00;             // its kind
    type_16C2A0 unk_04;
    type_3DC7F8 *unk_24;        // its projectiles

    type_4E19F8();
    ~type_4E19F8();
    // Sets it up for arg_0 projectiles of the kind arg_4.
    void sub_15F3D0(RwInt32 arg_0, RwInt32 arg_4);
    // Frees its projectiles, and shuts the memory pool down.
    void sub_15F490();
    void sub_15F4B0();
    // Links arg_0 in first, and unlinks it.
    void sub_15F4D0(type_3DC7F8 *arg_0);
    void sub_15F520(type_3DC7F8 *arg_0);
    // Builds a projectile of its kind and starts it (sub_15F2C0's
    // arguments).
    type_3DC7F8 *sub_15F590(RwInt32 arg_0, type_3D3548 *arg_4, RwMatrix *arg_8, RwV3d *arg_C,
                            RwInt32 arg_10, type_439A48 *arg_14, type_429E54 *arg_18);
    // Frees arg_0 when it is finished (vf_004) or arg_4 is set; 1 if freed.
    RwInt32 sub_15FEB0(type_3DC7F8 *arg_0, RwInt32 arg_4);
    void sub_15FF00();
    // Steps its projectiles by arg_0, freeing those done; draws them.
    void sub_15FF50(RwReal arg_0);
    void sub_15FFF0(RwCamera *arg_0);
};
typedef RwChar type_4E19F8_size_check[sizeof(type_4E19F8) == 0x28 ? 1 : -1];
extern type_4E19F8 dword_4E19F8[9];

// The pool of the kind arg_0: an inline with no address and so no database
// name, named for what it returns. Evidence: the factory's reclaiming
// (sub_15F590) scales the constant kind 6 at run time.
inline type_4E19F8 *projectile_pool(RwInt32 arg_0)
{
    return &dword_4E19F8[arg_0];
}

#endif
