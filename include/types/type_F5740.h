/*
 * type_F5740: a triggered particle (0xBC bytes, from the pool dword_4BFDD4,
 * "m_triggeredParticles"), named for the function that starts one
 * (sub_F5740): a ParticleTrigger's emitter, made from one of its settings
 * (ParticleTrigger_entry). The update (sub_F4890) starts its particle
 * system at the trigger after its delay, with its sound and blast, and
 * then, when it has children (unk_7C), fires them on a random interval,
 * each emission scheduled (type_F58B0) with a random delay.
 */
#ifndef TYPE_F5740_H
#define TYPE_F5740_H

#include "rw/ostypes.h"
#include "rw/bamatrix.h"
#include "types/type_3DF8D8.h"
#include "types/type_129_base.h"
#include "types/type_F2880.h"
#include "types/alfasched.h"
#include "types/ParticleTrigger.h"
#include "types/type_67260.h"

struct type_F5740
{
    RwInt32 unk_00;             // the particle system (sub_F2FF0's id)
    RwInt32 unk_04;             // the emitter's index in its trigger
    RwReal unk_08;              // the delay, in frames
    RwV3d unk_0C;               // the offset from the trigger
    RwInt16 unk_18;             // set once started
    RwInt16 unk_1A;             // the sound follows the player
    RwInt16 unk_1C;             // placed by the trigger's whole matrix
    RwInt16 unk_1E;             // the offset is in the world, not turned
    type_3DF8D8_04 unk_20;      // its sound's key
    type_F2880 unk_28;          // its particle system
    RwInt32 unk_34;             // set for its blast
    RwReal unk_38;              // its blast's radius
    union
    {
        RwInt32 unk_3C;         // and damage (a float to the blast,
        RwReal unk_3C_f;        // sub_F4890)
    };
    RwReal unk_40;
    RwReal unk_44;
    union
    {
        RwInt32 unk_48;
        RwReal unk_48_f;        // single player copies reals here (SP 0xBAC00)
    };
    union
    {
        RwInt32 unk_4C;
        RwReal unk_4C_f;
    };
    RwInt32 unk_50;
    type_144940 unk_54;         // its trigger
    RwInt32 unk_60;             // its sound
    RwReal unk_64;
    RwInt32 unk_68;
    RwInt32 unk_6C;
    RwInt32 unk_70;
    RwReal unk_74;
    RwInt32 unk_78;
    RwInt32 unk_7C;             // children fire from it
    RwInt32 unk_80;             // how many times (-1: without end)
    RwInt32 unk_84;             // how many times so far
    RwReal unk_88;              // the interval's bounds
    RwReal unk_8C;
    RwReal unk_90;              // the time to the next
    RwInt32 unk_94;             // how many emissions next (0: a random count)
    RwInt32 unk_98;             // the count's bounds
    RwInt32 unk_9C;
    RwReal unk_A0;              // each emission's delay's bounds
    RwReal unk_A4;
    type_F5740 *unk_A8;         // the live list (dword_4BFDD0)
    type_F5740 *unk_AC;
    type_F5740 *unk_B0;         // its children (sub_F5BC0)
    type_F5740 *unk_B4;         // its parent, or the previous child
    RwInt32 unk_B8;
};
typedef RwChar type_F5740_size_check[sizeof(type_F5740) == 0xBC ? 1 : -1];

// An emitter's blast settings as the update (sub_F4890) builds them from
// its fields (unk_3C to unk_78), in the fields' own types: after a
// type_67260 they are what the player's explosion shake reads
// (type_114F90's unk_50).
struct type_F4890_50
{
    union
    {
        RwInt32 unk_00;
        RwReal unk_00_r;        // a thrown grenade's (sub_1AE8F0)
    };
    union
    {
        RwInt32 unk_04;
        RwReal unk_04_r;        // the emitter's damage (SP 0xBAFC0)
    };
    RwReal unk_08;
    RwReal unk_0C;
    RwInt32 unk_10;
    RwInt32 unk_14;
    union
    {
        RwInt32 unk_18;
        RwReal unk_18_r;        // a thrown grenade's (sub_1AE8F0)
    };
    RwReal unk_1C;
    RwInt32 unk_20;
    RwInt32 unk_24;
    RwInt32 unk_28;
    RwReal unk_2C;
    RwInt32 unk_30;
};
// The blast's record (0x84 bytes): its radius (unk_4C_r) and damage
// (unk_04), then the settings above; the blast (type_4AE70::unk_30) and
// the player's shake take it.
struct type_F4890_blast : type_67260
{
#ifdef CODFH_SP // shape: SP 0xBAFC0 clears these base fields through their float values.
    type_F4890_blast()
    {
        unk_40_r = 0.0f;
        unk_44_r = 0.0f;
        *(RwReal *)&unk_48 = 0.0f;
    }
#endif
    type_F4890_50 unk_50;
};

// A scheduled emission (from the pool dword_4BFDF4, "m_scheduledParticles";
// the list dword_4BFDCC), named for the function that schedules one: the
// emitter and the time left.
struct type_F58B0
{
    type_F5740 *unk_00;
    RwReal unk_04;
    type_F58B0 *unk_08;
    type_F58B0 *unk_0C;
};

extern type_F58B0 *dword_4BFDCC;
extern type_F5740 *dword_4BFDD0;
extern type_16C2A0 dword_4BFDD4;
extern type_16C2A0 dword_4BFDF4;

// Set-up, restart and shutdown.
void sub_F47F0();
void sub_F4850();
void sub_F4860();
// The update by arg_0 frames.
void sub_F4890(RwReal arg_0);
// The matrix of the emitter arg_0 (arg_8: at the trigger's centre), and of a
// child's emission, at a random point in its trigger's shape.
void sub_F5370(type_F5740 *arg_0, RwMatrix *arg_4, bool arg_8);
void sub_F54E0(type_F5740 *arg_0, RwMatrix *arg_4);
// Counts the schedule down by arg_0; takes the first emission due.
void sub_F57C0(RwReal arg_0);
type_F58B0 *sub_F57F0();
// Schedules an emission of arg_0 in arg_4 frames.
type_F58B0 *sub_F58B0(type_F5740 *arg_0, RwReal arg_4);
// Makes one from emitter arg_4 of the trigger arg_0 (settings arg_8).
type_F5740 *sub_F5920(ParticleTrigger *arg_0, RwInt32 arg_4, ParticleTrigger_entry *arg_8);
// Stops them all.
void sub_F5E30();

#endif
