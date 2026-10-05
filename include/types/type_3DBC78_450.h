/*
 * type_3DBC78_450: the physics body type_3DBC78 holds at +0x450 and again
 * at +0x7B0 (0x360 bytes each; sub_14D2C0 sets both up with sub_147080).
 * type_3DBC78's constructors build them inline and destroy them with
 * pDtor, which is folded with other types' empty destructors (sub_14C930,
 * sub_14CF20, sub_1555A0 unwind through it), so the type is named after
 * its container and offset.
 *
 *   +0x000 unk_00   13 contact points (sub_147710 bounds the kind-2 ones)
 *   +0x124 unk_124  a velocity: sub_14C140 takes its length
 *   +0x170 unk_170  its matrix (the model's, sub_147080); sub_14C140 dots
 *                   unk_124 with its at vector
 *   +0x2D0 unk_2D0  four vertical planes bounding it (sub_147710, or the
 *                   model's box, sub_147930)
 */
#ifndef TYPE_3DBC78_450_H
#define TYPE_3DBC78_450_H

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "rw/bamatrix.h"
#include "types/type_3DF8D8.h"
#include "game/functions.h"

struct type_3DBC78;
struct type_3D3548;

// A contact point of a body: a position, a radius (sub_147710 takes the
// least) and a kind.
struct type_147710
{
    RwV3d unk_00;
    RwReal unk_0C;
    RwInt32 unk_10;
};

// A vehicle's trigger (type_712B0) as sub_147080 reads it: its model's key
// and its physics settings.
struct type_712B0_3DBC78
{
    RwUInt8 unk_00[0x90];
    RwV3d unk_90;               // its position (its matrix's)
    RwUInt8 unk_9C[0x24];
    type_3DF8D8_04 unk_C0;      // its model
    type_3DF8D8_04 unk_C8;      // its AI script and tasks, and the object
    type_3DF8D8_04 unk_D0;      // whose id goes in unk_2620 (sub_14D2C0)
    type_3DF8D8_04 unk_D8;
    type_3DF8D8_04 unk_E0;      // its own name
    RwInt32 unk_E8;             // its vehicle: 0 a jeep, 1 a tank
    RwUInt32 unk_EC;            // its kind: 2 and 3 carry the player
                                // (type_3DBC78::vf_230)
    RwUInt32 unk_F0;            // its mass
    RwUInt32 unk_F4;
    RwReal unk_F8;              // its top speed, in the scripts' units
    RwInt32 unk_FC;             // its riders (sub_14D2C0)
    RwInt32 unk_100;            // its gimp level
    RwV3d unk_104;              // the player's seat (vf_268; vf_2FC copies
    RwReal unk_110;             // it to unk_118); the tank driver's
                                // distance from it, around the turret
    RwInt32 unk_114;            // the tank gunner's weapon kind (1: 35,
                                // else 29; sub_157600)
    RwV3d unk_118;
    RwReal unk_124;             // the AI settings sub_14D2C0 copies into
    RwReal unk_128;             // type_3DBC78's unk_1150 to unk_1178
    RwReal unk_12C;
    RwReal unk_130;
    RwReal unk_134;
    RwReal unk_138;
    RwInt32 unk_13C;
    RwInt32 unk_140;            // its health
    RwInt32 unk_144;            // its armour
    RwReal unk_148;             // health regained a step
    RwReal unk_14C;
    RwReal unk_150;
    RwReal unk_154;
    RwInt32 unk_158;
    RwInt32 unk_15C[4];         // the guns' damage, their unk_28, and
    RwInt32 unk_16C[4];         // their rates of fire (a second over it,
    RwInt32 unk_17C[4];         // their unk_30: type_15B110::sub_15B2A0)
    RwReal unk_18C;             // a bullet's damage scale by where it hits:
    RwReal unk_190;             // the front, a side, the rear and the top
    RwReal unk_194;             // (type_3DBC78::vf_064)
    RwReal unk_198;
    RwReal unk_19C_f;           // the tank's turning speed (its vf_03C)
    RwReal unk_1A0;             // the tank's unk_286C
    RwUInt8 unk_1A4[0x4];
    RwReal unk_1A8;             // the tank's unk_288C
    RwInt32 unk_1AC;            // it mounts a gun (sub_166D40 of the
    RwInt32 unk_1B0;            // settings from here to unk_1E8)
    RwInt32 unk_1B4;            // its gun's tag in the clump: "PGN0" plus
                                // this mod 10 (type_3DBC78::vf_04C)
    RwInt32 unk_1B8;
    RwInt32 unk_1BC;
    RwUInt8 unk_1C0[0x8];
    RwInt32 unk_1C8;
    RwInt32 unk_1CC;
    RwInt32 unk_1D0;
    RwUInt8 unk_1D4[0x14];
    RwInt32 unk_1E8;
    type_3DF8D8_04 unk_1EC;     // a spline for its AI (unk_11A0.unk_D14)
    RwUInt8 unk_1F4[0xC];
    RwReal unk_200;             // a flak gun's arc (FlakTrigger's; its
                                // set-up, sub_15AA70)
    RwInt32 unk_204;            // whether the flak gun goes down with its
    RwInt32 unk_208;            // gunner, its loader, its third crewman
    RwInt32 unk_20C;            // (sub_15AF20, sub_15AEE0, sub_15AF60)

    // VehicleTrigger::sub_C1010 (types/VehicleTrigger.h): posts its
    // messages to the AI object arg_0.
    void sub_C1010(struct type_3D2E7C *arg_0);
};

// A move gathered before it is applied (sub_149920, sub_149D60): a
// translation and a turn.
struct type_149920
{
    RwV3d unk_00;
    RwV3d unk_0C;
};

struct type_3DBC78_450;
// sub_14A5E0's search, handed to its triangle callback sub_14A870: the
// point (in the world and the body's frame), its radius and last position,
// its move, the body, the pushes gathered and how many, the world searched
// and whether a player drives.
struct type_14A5E0
{
    RwV3d unk_00;
    RwV3d unk_0C;
    RwReal unk_18;
    RwV3d unk_1C;
    RwV3d unk_28;
    type_3DBC78_450 *unk_34;
    type_149920 unk_38;
    RwInt32 unk_50;
    RwMatrixTag *unk_54;        // an atomic's matrix (sub_14AE80)
    struct RpWorld *unk_58;
    type_3DBC78 *unk_5C;        // the vehicle (sub_14BEE0's search)
    RwInt32 unk_60;
    RwInt32 unk_64;             // set when an atomic's triangle pushed it,
    RwV3d unk_68;               // and where, from the atomic, doubled
    RwInt32 unk_74;             // (no byte arrays: they add a /GS cookie)
};

struct type_3DBC78_450
{
    type_147710 unk_00[13];
    RwInt32 unk_104;            // physics on or off ("VehicleEnablePhysics")
    RwInt32 unk_108;            // the gimp level ("VehicleSetGimpLevel"; 3
                                // turns physics off)
    RwV3d unk_10C;
    RwV3d unk_118;
    RwV3d unk_124;
    RwV3d unk_130;
    RwV3d unk_13C;
    RwV3d unk_148;
    RwV3d unk_154;
    RwV3d unk_160;
    RwUInt8 unk_16C[0x4];
    RwMatrixTag unk_170;
    RwMatrixTag unk_1B0;
    RwMatrixTag unk_1F0;
    RwInt32 unk_230;
    RwInt32 unk_234;
    RwReal unk_238;
    RwReal unk_23C;             // a steering torque (sub_147B50)
    RwInt32 unk_240;            // set when the cruise speed was passed
    RwReal unk_244;
    RwReal unk_248;
    RwReal unk_24C;             // its mass
    RwReal unk_250;             // and its inverse
    RwReal unk_254;
    RwReal unk_258;
    RwV3d unk_25C;
    RwReal unk_268;             // the top speed ("VehicleSetMaxSpeed")
    RwReal unk_26C;             // the cruise speed ("VehicleSetCruiseSpeed")
    RwReal unk_270;
    RwReal unk_274;
    RwReal unk_278;
    RwInt32 unk_27C;
    RwV3d unk_280;
    RwV3d unk_28C;
    RwInt32 unk_298;
    RwInt32 unk_29C;
    RwInt32 unk_2A0;
    RwUInt8 unk_2A4;            // set when the model's box gave the planes
    RwUInt8 unk_2A5[0x3];
    type_3D3548 *unk_2A8;       // the entity it last touched (sub_14C6E0),
    RwV3d unk_2AC;              // where that entity was,
    RwV3d unk_2B8;              // and how far it has moved since
    RwUInt8 unk_2C4[0xC];
    RwPlane unk_2D0[4];
    RwPlane unk_310[4];         // the planes through its matrix (sub_147A20)
    RwReal unk_350;             // its step (sub_147B50, at most 3)
    RwUInt8 unk_354[0xC];

    // An empty constructor and destructor, inline (the vehicle's constructor
    // still marks each body built; its destructor takes them down without a
    // call). The destructor's out-of-line copy, which the vehicle's unwind
    // funclets call, is folded into pDtor (config/aliases.txt).
    type_3DBC78_450()
    {
    }
    ~type_3DBC78_450()
    {
    }
    // Sets the body up from the vehicle's trigger arg_0 at the matrix
    // arg_4.
    void sub_147080(type_712B0_3DBC78 *arg_0, RwMatrixTag *arg_4);
    // The planes from the kind-2 contact points (unless the model's box
    // gave them), and from a box's corners arg_0 and arg_4.
    void sub_147710();
    void sub_147930(RwV3d *arg_0, RwV3d *arg_4);
    // The planes through its matrix, into arg_0 (four).
    void sub_147A20(RwPlane *arg_0);
    // Steps the body by arg_8, and the one following arg_4 (the vehicle
    // arg_0's second body).
    void sub_147B50(type_712B0_3DBC78 *arg_0, type_3D3548 *arg_4, RwReal arg_8);
    void sub_148F60(type_3DBC78 *arg_0, type_3DBC78_450 *arg_4, RwReal arg_8);
    // Applies the force arg_4 at arg_0, to the body or into arg_0.
    void sub_149780(RwV3d *arg_0, RwV3d *arg_4);
    void sub_149920(type_149920 *arg_0, RwV3d *arg_4, RwV3d *arg_8);
    // Moves it on by its step, and by the gathered move arg_0.
    void sub_149AA0();
    void sub_149D60(type_149920 *arg_0);
    // Points and vectors from its frame into the world's.
    void sub_149E80(RwV3d *arg_0, RwReal arg_4, RwReal arg_8, RwReal arg_C);
    void sub_149EC0(RwV3d *arg_0, RwV3d *arg_4);
    void sub_149F00(RwV3d *arg_0, RwReal arg_4, RwReal arg_8, RwReal arg_C);
    void sub_149F40(RwV3d *arg_0, RwV3d *arg_4);
    // Sets it on the ground (gimp level 2); its contacts otherwise.
    RwInt32 sub_149F80(RwInt32 arg_0);
    RwInt32 sub_14A250(type_3D3548 *arg_0, RwReal arg_4, RwInt32 arg_8);
    // A hull point against the walls, and a contact point out of the
    // ground; whether it touched.
    RwInt32 sub_14A5E0(type_3D3548 *arg_0, type_147710 *arg_4, RwReal arg_8, RwV3d *arg_C);
    RwInt32 sub_14AAD0(type_147710 *arg_0, type_149920 *arg_4);
    // The nearest hit on the line from arg_0 to arg_4 in the sections'
    // collision worlds.
    type_91F40 *sub_14AD30(RwV3d *arg_0, RwV3d *arg_4, RwInt32 arg_8);
    // The vehicle arg_0's collisions with other entities (gimp level 0).
    RwInt32 sub_14BEE0(type_3DBC78 *arg_0);
    // Sets the speed along the velocity (the scripts' units), and holds the
    // cruise speed (the throttle unk_23C toward it).
    void sub_14C1D0(RwReal arg_0);
    void sub_14C340();
    // The speed of the entity arg_0 against it (0 when it was not the one
    // last touched).
    RwReal sub_14C6E0(type_3D3548 *arg_0);
    RwInt32 sub_14C520(RwV3d *arg_0);
    // The signed speed: unk_124's length scaled by two constants, negated
    // when unk_124 points against unk_170's at vector.
    RwReal sub_14C140();
    // Sets the cruise speed ("VehicleSetCruiseSpeed").
    void sub_14C270(RwReal arg_0);
};

// The bodies' tuning, writable floats (sub_147080, sub_147B50,
// sub_148F60, sub_149AA0).
extern RwReal dword_429D3C;
extern RwReal flt_429D2C;
extern RwReal dword_429D04;
extern RwReal dword_429D40;
extern RwReal flt_429D18;
extern RwReal flt_429D1C;
extern RwReal flt_429D20;
extern RwReal flt_429D28;
extern RwReal flt_429D34;
extern RwReal flt_429D44;
extern RwReal flt_429D4C;
extern RwReal flt_429D5C;
extern RwReal flt_429D60;
extern RwReal flt_429D78;
extern RwReal flt_429D7C;
extern RwReal flt_429D80;
extern RwReal flt_429D84;
extern RwReal flt_429D88;
extern RwReal flt_429D08;
extern RwReal flt_429D0C;
extern RwReal flt_429D10;
extern RwReal flt_429D64;
extern RwReal flt_429D68;
// Whether a contact's turn is scaled by flt_4D50FC before it is applied (1).
extern RwInt32 dword_429D8C;
extern RwReal flt_4D50FC;
// The largest contact turn seen (sub_14A250).
extern RwReal flt_4D5104;
// sub_14A5E0's result; nothing here sets it.
extern RwInt32 dword_4D31B0;
// sub_14A5E0's triangle callback.
struct RpCollisionTriangle *sub_14A870(struct RpIntersection *arg_0, struct RpWorldSector *arg_4,
                                       struct RpCollisionTriangle *arg_8, RwReal arg_C, void *arg_10);
// The atomics' triangle callback (sub_14B570's search).
struct RpCollisionTriangle *sub_14AE80(struct RpIntersection *arg_0, struct RpCollisionTriangle *arg_4,
                                       RwReal arg_8, void *arg_C);
// Pushes the entity arg_4 out of the box of arg_0's body (the player,
// arg_8, by its placed position).
void sub_14B140(type_14A5E0 *arg_0, type_3D3548 *arg_4, RwInt32 arg_8);
// The side a push out of a box goes through (cos 30 degrees).
extern RwReal flt_429D9C;
// The vehicles' atomic callback (sub_14BEE0's search).
struct RpAtomic *sub_14B570(struct RpIntersection *arg_0, struct RpWorldSector *arg_4, struct RpAtomic *arg_8,
                            RwReal arg_C, void *arg_10);
// The atomic callback for a vehicle no player drives.
struct RpAtomic *sub_14BA00(struct RpIntersection *arg_0, struct RpWorldSector *arg_4, struct RpAtomic *arg_8,
                            RwReal arg_C, void *arg_10);
// Two vehicles' contact points' push (sub_14BA00).
extern RwReal flt_429D50;
// Whether the sphere arg_4 (its centre; arg_8 its radius) is inside the four
// planes arg_0.
RwInt32 sub_14C660(RwPlane *arg_0, RwV3d *arg_4, RwReal arg_8);
// A hard collision's push (sub_14B570).
extern RwReal flt_429D54;
// The vehicles' atomics' spheres are scaled by it (sub_14FFA0; 2).
extern RwReal flt_429DA0;
// A push's scale (vf_264; 1).
extern RwReal flt_429DB4;
// Cleared when the player gets in (vf_268); only the width is known.
extern RwInt32 dword_4D5164;
// The world's up (game/render.h also declares it; that header's Direct3D
// declarations clash with the HUD's).
extern RwV3d dword_429D90;
// The tracks' speed scale (vf_234; 2.8).
extern RwReal flt_429DB8;
// The cosine of the tanks' field of fire (vf_2D4; 30 degrees' worth, about
// 0.933).
extern RwReal flt_429DD8;
// sub_14D2C0's contact points: the outer ones' lateral and vertical
// offsets from the wheels (-75, 160, 50) and their radius (130).
extern RwReal flt_429DA4;
extern RwReal flt_429DA8;
extern RwReal flt_429DAC;
extern RwReal dword_429DB0;
// vf_04C: its aim point's lead (5, by 60 / the step) and the rider's offset
// from the turret bone (x unset in the image, 100, -50).
extern RwReal flt_429DD4;
extern RwReal dword_4D5168;
extern RwReal dword_429DBC;
extern RwReal dword_429DC0;
// The tanks' engagement tuning (vf_2D8): its size's weight (2), the facing
// that counts as toward (0.86) and the aim cone (0.92).
extern RwReal flt_429DE4;
extern RwReal flt_429DE0;
extern RwReal flt_429DDC;
// Whether the velocity is capped at the top speed (1).
extern RwInt32 dword_429D74;
// Steps left in which a body is put back at its trigger (sub_147B50).
extern RwInt32 dword_4D50F8;
// sub_14AD30's hit and its nearest.
extern type_91F40 dword_4D5134;
extern type_91F40 dword_4D5108;

#endif
