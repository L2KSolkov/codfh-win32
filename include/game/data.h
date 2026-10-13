/*
 * Data in units not yet recovered as source, declared once with the types
 * their uses establish. Names are the database's.
 */
#ifndef GAME_DATA_H
#define GAME_DATA_H

#include <string.h>

#include "rw/ostypes.h"
#include "types/type_4E5D30.h"
#include "types/type_D48D0.h"
#include "types/type_4B8600.h"
#include "types/alfasched.h"
#include "types/type_35120.h"
#include "types/type_409A0.h"
#include "types/type_42AF0.h"
#include "types/type_3C540.h"
#include "types/type_1DDE20_mask.h"
#include "types/type_4C00E8.h"
#include "types/type_4C00D0.h"

// flt_427400: a float in .data just before the handler table unk_427408
// (90.0 in the image); sub_12970 compares the AI object's unk_00 with it.
extern RwReal flt_427400;

// deltaTime: a float in .data at 0x429284 (the database's name);
// sub_14EA0 adds it to the AI object's unk_00.
extern RwReal deltaTime;
// An inline accessor for deltaTime, with no address and so no database
// name. Evidence: sub_14C6E0 copies it into a temporary of its own before
// the call whose result it divides.
inline RwReal get_deltaTime()
{
    RwReal r = deltaTime;
    return r;
}

// flt_428A08 and flt_428A0C: 30.0 and 0.001, writable, read by "SetTurnMode"
// (sub_48570): how far it leads the target along unk_50C, and the lead per
// unit of distance.
extern RwReal flt_428A08;
extern RwReal flt_428A0C;
// flt_428A10 and flt_428A14: writable floats "GetWeaponsStandMeleeRange"
// (sub_491C0) adds to the stand melee range for a target with flag 4 of its
// unk_2C, and gives instead for other targets.
extern RwReal flt_428A10;
extern RwReal flt_428A14;
// dword_42910C: a writable float the dog's set-up (type_3D5658::sub_9C6E0)
// copies into the entity's unk_108.
extern RwReal dword_42910C;
// dword_4290C0, dword_4290C4, dword_4290C8: writable floats (0.65, 0.1 and
// 0.5) sub_9A2D0 sorts a contact's direction by (ahead, beside, behind).
extern RwReal dword_4290C0;
extern RwReal dword_4290C4;
extern RwReal dword_4290C8;
// flt_4290CC: how far a wall triangle must face the entity to be sorted
// into its contact records (-0.5); flt_4290E0: how wide it must be (40,
// else 400 high) (sub_992B0).
extern RwReal flt_4290CC;
extern RwReal flt_4290E0;
// flt_4290EC: how far from vertical a triangle's normal must be for
// sub_959E0 to drop points onto it (0.352).
extern RwReal flt_4290EC;
// flt_4290E4: how much farther a blocked AI (AIData::is_blocked) reaches
// for contacts (sub_943E0).
extern RwReal flt_4290E4;
// flt_4290D0: how far above the searching frame a triangle must reach to
// be sorted into its contact records (sub_98200; 55).
extern RwReal flt_4290D0;
// flt_4290D4: how much wider the contact records reach than the collision
// radii (sub_948A0).
extern RwReal flt_4290D4;
// dword_429BCC: while set, sub_96EF0 prints the gathered triangle count
// into a buffer it never shows.
extern RwInt32 dword_429BCC;
// flt_4290E8, flt_4290DC: how upright a triangle must be for a soldier to
// stand on it, and how steep for a contact (sub_97790).
extern RwReal flt_4290E8;
extern RwReal flt_4290DC;
// flt_4290D8: how much wider the soldier's second contact radii are;
// flt_4290F0: the scale of its side radius (sub_985B0).
extern RwReal flt_4290D8;
extern RwReal flt_4290F0;
// Likewise flt_428A18 and flt_428A1C for the lunge range
// ("GetWeaponsLungeMeleeRange", sub_49270), flt_428A20 and flt_428A24 for
// the run range ("GetWeaponsRunMeleeRange", sub_49320).
extern RwReal flt_428A18;
extern RwReal flt_428A1C;
extern RwReal flt_428A20;
extern RwReal flt_428A24;

// Pooled constants (game/pooledconsts.h) still read by name: flt_3CD8E0
// (1.0), flt_3CD84C (0.0), flt_3D7118 (3.0). Loaded at run time, so
// variables, not literals.
extern const RwReal flt_3CD8E0;
extern const RwReal flt_3D7118;
extern const RwReal flt_3CD84C;

// dword_438CA0 and unk_438CA8: a count and a table of 32 entity handles in
// .data; sub_16D10 clears them and sub_16E80 fills the first free handle.
// sub_32F70 also takes a new A* search id from dword_438CA0.
extern RwInt32 dword_438CA0;
extern type_D48D0 unk_438CA8[32];

// dword_429EB0: an index into sub_1745A0's entity table (.data, 13 users);
// sub_1A2E0 uses the entity it selects as the player.
extern RwInt32 dword_429EB0;

// dword_4275C8: a float in .data (the database names it dword_); sub_20830
// copies it into its float argument as the default distance.
extern RwReal dword_4275C8;

// flt_4275D0 (100.0) and flt_4275D4 (150.0): floats in .data; AIData::sub_21A90
// uses them as a drop height and a minimum clear distance.
extern RwReal flt_4275D0;
extern RwReal flt_4275D4;

// flt_4275B8 and flt_4275BC (both 50.0): floats in .data; AIData::sub_20370
// raises its two nonzero radii to at least flt_4275B8 (the second is tested
// against flt_4275BC).
extern RwReal flt_4275B8;
extern RwReal flt_4275BC;

// dword_4275D8 (400.0): a float in .data (the database names it dword_);
// AIData::sub_21C90 tries offsets of that size to each side and behind.
extern RwReal dword_4275D8;

// flt_4275CC (100.0): a float in .data; AIData::sub_213B0 passes it to
// sub_20830 as the follow distance.
extern RwReal flt_4275CC;

// flt_4275E4 (150.0) and flt_4275E8 (22500.0): floats in .data;
// AIData::sub_26000 uses them as the height band (above and below) and the
// squared distance within which the player spoils a cover node.
extern RwReal flt_4275E4;
extern RwReal flt_4275E8;

// flt_4275EC (4.0): a float in .data; AIData::sub_2E580 scales its default
// turn rate (6.0) by it.
extern RwReal flt_4275EC;

// flt_438D30: a float in .data; how long an entity may block an AI's path
// before AIData::sub_30A50 logs "BlockingEntity".
extern RwReal flt_438D30;

// dword_438D28 and flt_438D2C: floats in .data. AIData::sub_2F440 widens the
// clearance to a blocking entity by dword_438D28 while the path is blocked
// (unk_598), and measures the owner's radius less flt_438D2C.
extern RwReal dword_438D28;
extern RwReal flt_438D2C;

// dword_4275F0 (30.0): a float in .data, the height sub_31C50 asks an entity
// to shoot from.
extern RwReal dword_4275F0;

// flt_438D38 and flt_438D88: the two CanShoot schedulers (see
// types/alfasched.h); the database names them for their first dword.
extern alfasched flt_438D38;
extern alfasched flt_438D88;

// The A* scheduler's state (Source/GameCore/ai/astarscheduler.cpp): its two
// alfasched, dword_438DE8 and dword_438E38, and dword_438DD8 and
// dword_438DE4, which sub_32E50 clears with dword_438DDC.
extern alfasched dword_438DE8;
extern alfasched dword_438E38;
extern RwInt32 dword_438DD8;
extern RwInt32 dword_438DE4;
// dword_438DE0: the entity sub_33190 is clearing the schedulers of.
extern RwInt32 dword_438DE0;

// off_4275F4: the A* search types' names, "eASST_PathToTarget" to
// "eASST_PathToFollowEntitySplinePoint" (12 entries), which the scheduler's
// log messages print.
extern const RwChar *off_4275F4[13];      // ended by 0

// flt_3CDE18 (0.5), flt_3CDE1C (0.2), flt_3CDE20 (0.3), flt_3CDE24 (0.5) and
// flt_3CDE28 (100.0): named float constants in .rdata, not literals. The
// code negates them with fchs and squares flt_3CDE28 by two loads, where a
// literal would be folded, and two of them hold the same 0.5 at different
// addresses. AIData::sub_26000 uses all five as facing thresholds (and
// sub_25EB0 uses flt_3CDE20).
extern const RwReal flt_3CDE18;
extern const RwReal flt_3CDE1C;
extern const RwReal flt_3CDE20;
extern const RwReal flt_3CDE24;
extern const RwReal flt_3CDE28;

// dword_438DDC: set to 1 by AIData::sub_244E0 whenever it runs a new
// defend-area node search.
extern RwInt32 dword_438DDC;

// dword_4B8600: sixteen entity-list heads (type_4B8600).
#ifdef CODFH_PLAIN
extern type_4B8600 (&dword_4B8600)[16];
#else
extern type_4B8600 dword_4B8600[16];
#endif

// dword_4E5D30: four collision-world entries (type_4E5D30); more with CODFH_ALL_SECTIONS.
#include "game/sectionslots.h"
extern type_4E5D30 dword_4E5D30[SECTION_SLOTS];

// The checkpoint register ("SetCheckPointRegister", "GetCheckPointRegister"),
// the key of the checkpoint object it names (dword_4B914C) and the default
// clump bank ("SetDefaultClumpBank").
extern RwInt32 dword_4B8780;
struct type_3DF8D8_04;
struct type_3DF8D8_04_data;
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &dword_4B914C;
#else
extern type_3DF8D8_04_data dword_4B914C;
#endif
extern RwInt32 dword_429EA8;

// flt_4275C4 (5.0): a float in .data; AIData::sub_1C4F0 compares its owner's
// unk_450.sub_14C140() with it.
extern RwReal flt_4275C4;

// flt_4275C0 (400.0): a float in .data; AIData::sub_1B2B0 scales the
// squared speed by it.
extern RwReal flt_4275C0;

// flt_4275DC (90000.0) and flt_4275E0 (40000.0): floats in .data;
// AIData::sub_22690 compares a squared distance and a height with them.
extern RwReal flt_4275DC;
extern RwReal flt_4275E0;

// unk_4C00E8: the path-node graph (type_4C00E8).
extern type_4C00E8 unk_4C00E8;

// dword_4B87C8: a float time (type_3CE4B4::vf_034 compares it with a
// member's AIData::unk_1434 plus 60).
extern RwReal dword_4B87C8;

// dword_449288 and dword_449284: what "RegisterAStarCheck" stores in the AI
// object's unk_560 and unk_564 with a new check; only their widths are known.
extern RwInt32 dword_449288;
extern RwInt32 dword_449284;
// dword_4B2178: the CCESS pool manager's state ("SetCCESSPoolManagerState").
extern RwInt32 dword_4B2178;
// Buffer (the database's name, 0x439948): a text buffer the script commands
// format messages into that nothing then shows ("PrimeAudioStream").
extern RwChar Buffer[];
// "FadeSubstreamVolume"'s arguments, kept in globals: the voice type
// (dword_428A2C, -1 at first), the two volumes in percent (flt_439E70) and
// fade times (dword_439E68), and a working volume (dword_428A28, a float).
#ifndef CODFH_SP // file-static in single player (unit_0441B0: sub_5F950, SP 0x4E5A0)
extern RwInt32 dword_428A2C;
extern RwReal flt_439E70[2];
#endif
extern RwInt32 dword_439E68[2];
#ifndef CODFH_SP // single player defines it static in unit_0441B0 (sub_5F950 drops a dead store, SP 0x4E5A0)
extern RwReal dword_428A28;
#endif
#include "types/type_8A980.h"
#include "types/type_DA0A0.h"
// dword_4E5E40: the index-sound table; unk_08 lists 12-byte entries whose
// first word is the index an entity's tag (type_3D3548::unk_290, unk_294)
// selects ("EfuncPlayIndexSound").
struct type_4E5E40_08
{
    RwInt32 unk_00;
    RwUInt32 unk_04[0x2];
};
struct type_4E5E40
{
    RwUInt32 unk_00[0x2];
    type_4E5E40_08 *unk_08;

    // Inline: its initializer (0x30BE80) clears the list, then the rest.
    type_4E5E40()
    {
        unk_08 = 0;
        unk_00[0] = 0;
        unk_00[1] = 0;
    }
};
extern type_4E5E40 dword_4E5E40;
// dword_44E838 and dword_44E874: more debug switches: with the first set, a
// tagless index sound plays a fixed warning sound; with dword_44E860 and the
// second, it formats a warning for the debug print.
extern RwInt32 dword_44E838;
extern RwInt32 dword_44E874;
extern type_8A980 dword_4B1E98;
// dword_44E860 and dword_44E86C: debug switches; with both set,
// "EfuncPlaySound" formats a complaint about an unknown sound alias.
extern RwInt32 dword_44E860;
extern RwInt32 dword_44E86C;
// dword_4E5648: whether the objective target system is on
// ("EnableObjectiveTargetSystem").
extern RwInt32 dword_4E5648;
// dword_4F28F0: an object only known by its byte unk_28, which lets help
// messages show ("DisplayHelpMessage" reads it through an inline accessor
// with a result local, get_unk_28).
struct type_DA0A0;
// Its +0x38 block (sub_19AEA0 clears it through a `this` temporary: an
// inline with no address and so no database name, named for what it does).
struct type_4F28F0_38
{
    RwInt32 unk_00;
    RwInt32 unk_04;
    RwInt32 unk_08;

    void clear()
    {
        memset(this, 0, 8);
        unk_08 = -1;
    }
};
struct type_4F28F0
{
#ifdef CODFH_SP // a constructor clearing unk_38: byte_4F2908 is static .data (SP 0x3285C8, -1 at +0x40)
    // /O2 initializes it statically, with no initializer (multiplayer's is
    // unk_4F2940's, unit_19AAB0).
    type_4F28F0()
    {
        unk_38.clear();
    }
#endif
    RwInt32 unk_00;
    RwInt32 unk_04;
    RwInt32 unk_08;             // unk_10 is set (sub_19B000)
    RwUInt8 unk_0C;
    RwUInt8 unk_0D[0x3];
    RwInt32 unk_10;             // the level (sub_19B000; dword_4F28F4)
    RwInt32 unk_14;             // saved into the record's settings
    RwInt32 unk_18;             // (sub_D9EC0); the shell's difficulty
    RwInt32 unk_1C;
    RwUInt8 unk_20;             // rumble on (the pad manager's sub_EED30)
    RwUInt8 unk_21;
    RwUInt8 unk_22;
    RwUInt8 unk_23;
    RwInt32 unk_24;             // the difficulty (sub_19B080, "difficulty =
                                // %d from shell")
    RwUInt8 unk_28;
    RwUInt8 unk_29[0x3];
    RwInt32 unk_2C;
    RwInt32 unk_30;
    RwInt32 unk_34;             // the language (sub_19B0A0; dword_4F28FC)
    type_4F28F0_38 unk_38;
    RwInt32 unk_44;             // passed to sub_1866E0 by the checkpoint save
    RwChar unk_48[0xC];         // the record's name
    RwInt32 unk_54;             // the furthest level reached
    RwUInt8 unk_58;             // set once unk_5C holds a checkpoint
    RwUInt8 unk_59[0x3];
    type_D90B0 unk_5C;          // the player's state at the checkpoint
    type_DA0A0 unk_B8;          // the save record
    RwUInt8 unk_180;
    RwUInt8 unk_181;
    RwUInt8 unk_182;
    RwChar unk_183[0x20];

    // An inline accessor, with no address and so no database name; named for
    // its field. Evidence: "DisplayHelpMessage" copies the byte into a byte
    // local after its own before testing it.
    RwUInt8 get_unk_28()
    {
        RwUInt8 r = unk_28;
        return r;
    }
    // Likewise for unk_44 and unk_54: the checkpoint save (sub_D8F80) reads
    // each through a temporary of its own (a result local) before the rest
    // of its expression.
    // Likewise for the fields the save record takes (sub_D9EC0 reads each
    // through a temporary of its own).
    RwInt32 get_unk_14()
    {
        RwInt32 r = unk_14;
        return r;
    }
    RwInt32 get_unk_18()
    {
        RwInt32 r = unk_18;
        return r;
    }
    // A direct-return accessor for it: the options menu (sub_18E640)
    // switches on it through a slot nothing wrote first.
    // Likewise for unk_14. Evidence: the front end's speaker setting
    // (sub_1C4F30) switches on it through a slot left unwritten.
    RwInt32 get_unk_14_direct()
    {
        return unk_14;
    }
    RwInt32 get_unk_18_direct()
    {
        return unk_18;
    }
    RwInt32 get_unk_1C()
    {
        RwInt32 r = unk_1C;
        return r;
    }
    RwUInt8 get_unk_20()
    {
        RwUInt8 r = unk_20;
        return r;
    }
    RwUInt8 get_unk_21()
    {
        RwUInt8 r = unk_21;
        return r;
    }
    RwUInt8 get_unk_22()
    {
        RwUInt8 r = unk_22;
        return r;
    }
    RwInt32 get_unk_44()
    {
        RwInt32 r = unk_44;
        return r;
    }
    RwInt32 get_unk_54()
    {
        RwInt32 r = unk_54;
        return r;
    }
    // Likewise for unk_180: the shell scene's set-up (type_DC400::sub_DC5F0)
    // reads it through a temporary of its own, widened.
    RwInt32 get_unk_180()
    {
        RwInt32 r = unk_180;
        return r;
    }

    // Sets the state to its defaults ("Player", difficulty 1).
    void sub_19AEA0();
};
extern type_4F28F0 *dword_4F28F0;
// Sets the save state's furthest level: a free inline with no address and so
// no database name, named for its field. Evidence: the checkpoint save
// (sub_D8F80) stores it through a temporary holding the value (the
// argument) and loads dword_4F28F0 directly, where a member setter would
// copy the pointer into a temporary too.
inline void set_4F28F0_unk_54(RwInt32 arg_0)
{
    dword_4F28F0->unk_54 = arg_0;
}
// Likewise for the fields the pause menu's options apply (sub_18E380), each
// stored through a temporary holding the value.
inline void set_4F28F0_unk_14(RwInt32 arg_0)
{
    dword_4F28F0->unk_14 = arg_0;
}
inline void set_4F28F0_unk_1C(RwInt32 arg_0)
{
    dword_4F28F0->unk_1C = arg_0;
}
// Likewise for the settings the shell hands the state (sub_19AD20).
inline void set_4F28F0_unk_18(RwInt32 arg_0)
{
    dword_4F28F0->unk_18 = arg_0;
}
inline void set_4F28F0_unk_22(RwUInt8 arg_0)
{
    dword_4F28F0->unk_22 = arg_0;
}
inline void set_4F28F0_unk_183(const RwChar *arg_0)
{
    strcpy(dword_4F28F0->unk_183, arg_0);
}
inline void set_4F28F0_unk_180(bool arg_0)
{
    dword_4F28F0->unk_180 = arg_0;
}
inline void set_4F28F0_unk_181(bool arg_0)
{
    dword_4F28F0->unk_181 = arg_0;
}
// dword_4B67CC: the CAnimPackSelector behaviour (types/CAnimPackSelector.h),
// 0 when absent.
class CAnimPackSelector;
extern CAnimPackSelector *dword_4B67CC;
// An inline accessor for it, with no address and so no database name; named
// for the global. Evidence: "DidIJustGoGoGo" and "FinishedGoGoGo" read it
// into a compiler temporary allocated with the inline functions' locals, and
// "FinishedGoGoGo" copies it from there even into a plain assignment.
inline RwReal get_dword_4B87C8()
{
    RwReal r = dword_4B87C8;
    return r;
}

// The AI schedulers' handle tables' sizes: the image's, or with the port's debug tools room for
// their bots (port/src/debug/trigtools.cpp; each soldier takes two vision handles, two or three
// distance ones, and a maneuver's).
#if defined(CODFH_DRAW_TRIGGERS) && !defined(CODFH_SP)
#define VISION_HANDLES 258
#define DISTANCE_HANDLES 385
#define MANEUVER_HANDLES 192
#else
#define VISION_HANDLES 66
#define DISTANCE_HANDLES 97
#define MANEUVER_HANDLES 64
#endif

// The Distance Scheduler (sub_34FA0 sets it up): its two alfasched,
// dword_4391A0 (32 entries) and dword_439210 (64), its registrations' pool
// dword_4391EC ("m_freeDistanceParams", 97 of type_35120), and the handle
// table dword_438E90 (97 entries; entry 0 is never handed out) with its
// serial counter dword_439198. dword_438E88, when set, is a handle
// sub_365A0 hands out again instead of a new one.
extern alfasched dword_4391A0;
extern alfasched dword_439210;
extern type_16C2A0 dword_4391EC;
extern type_438E90 dword_438E90[DISTANCE_HANDLES];
extern type_365A0 *dword_438E88;
extern RwInt32 dword_439198;

// The Vision Scheduler (sub_40720 sets it up): its two alfasched,
// dword_439840 and dword_4398B0 (32 entries each), its registrations' pool
// dword_43988C ("m_freeVisionParams", 64 of type_409A0), and the handle
// table dword_439618 with its serial counter dword_439838; dword_439828
// is cleared with them. sub_408F0 keeps the time step in dword_43982C and
// counts the looks it runs in dword_439834 and dword_439830; sub_40BD0
// keeps a time step in dword_43983C. dword_42767C (.data) bounds the
// registrations' countdowns.
extern alfasched dword_439840;
extern type_16C2A0 dword_43988C;
extern alfasched dword_4398B0;
extern type_439618 dword_439618[VISION_HANDLES];
extern RwInt32 dword_439828;
extern RwInt32 dword_439838;
extern RwReal dword_43983C;
extern RwInt32 dword_439834;
extern RwInt32 dword_439830;
extern RwReal dword_43982C;
extern RwInt32 dword_42767C;
// flt_427680 (4000000.0, .data): a squared distance; sub_40C60 lets a
// registration's countdown put off a look at a target beyond it.
extern RwReal flt_427680;

// The action queue (sub_42990 sets it up; type_42AF0): its pool dword_439910
// ("m_actionPool", 1000 records), first and last actions dword_439904 and
// dword_439900, the running action dword_4398FC and the tick's last
// dword_43990C, and byte_439908 while a tick runs. dword_4B8710, when set,
// has each tick send "Tick" (sub_42C50).
extern type_16C2A0 dword_439910;
extern type_42AF0 *dword_439904;
extern type_42AF0 *dword_439900;
extern type_42AF0 *dword_4398FC;
extern type_42AF0 *dword_43990C;
extern RwUInt8 byte_439908;
extern RwInt32 dword_4B8710;
// dword_4B8720: the number of restarts ("GetNumberOfRestarts").
extern RwInt32 dword_4B8720;

// The message system's debug settings, which CDebugScript's commands set
// (sub_43200) and sub_67B10, sub_6A970 and sub_6B060 read; String holds a
// name (command 7; the script VM's globals follow its 0x20 bytes), and
// byte_44930C says whether it starts with a digit.
extern RwInt32 dword_44928C;
extern RwInt32 dword_449294;
extern RwInt32 dword_4492A8;
extern RwInt32 dword_4492B0;
extern RwChar String[0x20];
extern RwUInt8 byte_44930C;
extern RwInt32 dword_449310;
extern RwUInt8 byte_449316;
extern RwUInt8 byte_449317;

// The script commands' globals: dword_4B87DC (the time scale mode: 1 slowed,
// 0 normal, 3 and 4 left alone) and dword_42928C (the slowed rate, .data),
// both set by "TimeScale" (sub_44BB0); dword_4CF450, the fog type
// ("SetFogType", sub_45050). The controller rumble ("ControllerShake", sub_449E0)
// is the pad manager's, unk_4B9308 (game/gameloop.h).
extern RwInt32 dword_4B87DC;
extern RwReal dword_42928C;
extern RwInt32 dword_4CF450;

// The performance maps, by id (2000; dword_4CFE30), and the performance
// lookup dword_4B92D4 ("PlayHitDeathAnim", sub_46720): sub_ECDA0 finds the
// performance of kind arg_8 in the map entry arg_4 for the entity arg_0.
// "PZ_Manipulate" reads its particle zone fields: a matrix unk_60 (only its
// start is known; RwMatrix's alignment would move the fields), the particle
// system unk_DC it spawns there, and the zone object unk_D8.
struct type_17DB90;
struct type_4CFE30
{
    RwUInt8 unk_00[0x60];
    RwUInt8 unk_60[0x4C];
    struct type_71250 *unk_AC;  // its message filter list (sub_6C5A0)
    RwUInt8 unk_B0[0x28];
    type_17DB90 *unk_D8;
    RwInt32 unk_DC;
    RwUInt8 unk_E0[0xC0];
    RwUInt8 unk_1A0[0x4];

    // An inline accessor for unk_AC, with no address and so no database
    // name; named for its field. Evidence: in a conditional's arm
    // (sub_6C5A0) it copies its uninitialised return temporary into the
    // conditional's before storing its value there.
    struct type_71250 *get_unk_AC()
    {
        return unk_AC;
    }
};
// type_17DB90: the zone object of a type_4CFE30 ("PZ_Manipulate";
// types/type_17DB90.h).
struct type_17DB90;
extern type_4CFE30 *dword_4CFE30[2000];
typedef struct RwStream RwStream;

// A performance key: the entity's values (the first four, then the one for
// kind 6, then the one for kind 7) and whether each counts (+6 on).
struct type_ECA40
{
    RwInt8 unk_00[6];
    RwInt8 unk_06[6];
};
// An entry of the lookup (16 bytes; 12 read): the length of its data (6 for
// one value each, else groups, each a count and that many values), its
// performances by kind (6 and 7, then the same for the second pick) and its
// data.
struct type_EC750
{
    RwInt32 unk_00;
    RwInt16 unk_04[4];
    RwInt8 *unk_0C;
};
struct type_ECDA0
{
    RwInt32 unk_00;             // the entries' count
    type_EC750 *unk_04;         // the entries
    RwInt8 *unk_08;             // their data

    // Made by sub_1EE9E0 (shared, /OPT:ICF, with type_ED340's) and freed by
    // sub_EC6D0; the GodAsset that loads it (sub_192220) news and deletes it.
    type_ECDA0();
    ~type_ECDA0();

    // Reads the lookup from arg_0 (sub_192220).
    void sub_EC750(RwStream *arg_0);
    // Whether the entry arg_4 fits the key arg_0 for kind 6 (sub_ECA40) and
    // kind 7 (sub_ECBE0): arg_4 when it does, else 0.
    type_EC750 *sub_ECA40(type_ECA40 *arg_0, type_EC750 *arg_4);
    type_EC750 *sub_ECBE0(type_ECA40 *arg_0, type_EC750 *arg_4);
    // The performance of kind arg_8 (6 or 7; the second pick when arg_C is
    // set) for the key arg_4, retried without its first value; -1 when
    // there is none.
    RwInt16 sub_ECDA0(type_3D3548 *arg_0, void *arg_4, RwInt32 arg_8, bool arg_C);
};
// What sub_EC880 and sub_EC970 are given: an entity at +0xC and two times
// at +0x28 and +0x2C; only those are known.
struct type_EC880_00
{
    RwUInt8 unk_00[0xC];
    type_3D3548 *unk_0C;
    RwUInt8 unk_10[0x18];
    RwReal unk_28;
    RwReal unk_2C;
};
// The object sub_EC880 and sub_EC970 are called on (they do not use it);
// named for its method.
struct type_EC880
{
    // A performance value from 0 to 2 from arg_0's time (unk_28, up to 35;
    // sub_EC970 unk_2C) and arg_4 (up to 2500), give or take one at random;
    // 3 when arg_0's entity's vf_160 is 4 (sub_EC880 only).
    RwInt8 sub_EC880(type_EC880_00 *arg_0, RwReal arg_4);
    RwInt8 sub_EC970(type_EC880_00 *arg_0, RwReal arg_4);
};
// A clamp of arg_0 between arg_4 and arg_8, by reference (the int sibling
// of sub_22C20).
const RwInt32 &sub_ECF40(const RwInt32 &arg_0, const RwInt32 &arg_4, const RwInt32 &arg_8);
extern type_ECDA0 *dword_4B92D4;
inline void set_dword_4B92D4(type_ECDA0 *arg_0)
{
    dword_4B92D4 = arg_0;
}

// The performance lookup dword_4B92FC (sub_46570, sub_47F90), loaded by
// sub_191FF0 (sub_ED030) as dword_4B92D4 is by sub_192220 (sub_EC750), both
// built by sub_1EE9E0; whether they are one class is not known
// (docs/questions.md). sub_ED340 finds the performance for the entity arg_0,
// its performance values arg_4 and the selector arg_8.
// A performance of a type_ED340 entry: its two picks and its selector.
struct type_ED030_08
{
    RwInt16 unk_00;
    RwInt16 unk_02;
    RwInt8 unk_04;
    RwUInt8 unk_05;
};
// An entry (12 bytes): its key (six values), its performances' count and
// its performances.
struct type_ED030
{
    RwUInt8 unk_00[6];
    RwUInt8 unk_06;
    RwUInt8 unk_07;
    type_ED030_08 *unk_08;
};
// The record the file holds for an entry: its key and 35 pairs of picks by
// selector (-1 for none).
struct type_ED030_rec
{
    RwUInt8 unk_00[6];
    RwInt16 unk_06[35][2];
};
struct type_ED340
{
    RwInt32 unk_00;             // the entries' count
    type_ED030 *unk_04;         // the entries, sorted by key
    type_ED030 *unk_08;         // a copy for partial keys

    // Made by sub_1EE9E0; frees the entries (sub_ECF70) when the GodAsset
    // that loads it (sub_1920A0) deletes it.
    type_ED340();
    ~type_ED340();
    // Reads the lookup from arg_0 (sub_191FF0), then sorts it (sub_ED2A0).
    void sub_ED030(RwStream *arg_0);
    void sub_ED2A0();
    RwInt16 sub_ED340(type_3D3548 *arg_0, RwUInt8 *arg_4, RwInt32 arg_8, bool arg_C);
    // The same with the key's unset values cleared in a sorted copy.
    RwInt16 sub_ED460(RwUInt8 *arg_0, RwInt32 arg_4, bool arg_8);
    // The pick (the second when arg_10) of selector arg_C for the key arg_8
    // among the arg_4 sorted entries arg_0, falling back through lower
    // selectors; -1 when there is none.
    RwInt16 sub_ED530(type_ED030 *arg_0, RwInt32 arg_4, RwUInt8 *arg_8, RwInt32 arg_C, bool arg_10);
};
// The entries' order: their keys' six bytes (qsort and bsearch's compare).
RwInt32 sub_ED2D0(const void *arg_0, const void *arg_4);
// The empty function (the debug print, sub_19A750) the lookups' readers pass
// each value they read to, as a byte-order fix folded away.
void sub_19A750(RwInt16 *arg_0);
extern type_ED340 *dword_4B92FC;
// Setters for the three lookups with no addresses and so no database names.
// Evidence: the GodAssets that load them (sub_191FF0, sub_192220,
// sub_192460) store each through a temporary holding the value.
inline void set_dword_4B92FC(type_ED340 *arg_0)
{
    dword_4B92FC = arg_0;
}

// The scene lookup dword_4B9300 ("SetSceneMap", sub_48A10; loaded by
// sub_192460), likewise a separate placeholder: sub_ED850 finds the scene
// performance for the map entry arg_0, with a value for the entity's
// performance values' byte 2 in *arg_4 when given (sub_48EE0; "SetSceneMap"
// passes 0).
// A scene key as sub_ED850 is given it: its two values, then whether each
// counts.
struct type_ED850_key
{
    RwInt16 unk_00[2];
    RwInt8 unk_04[2];
};
// An entry of the scene lookup (8 bytes): its key (two values), its
// performance and the value it gives.
struct type_ED6B0
{
    RwInt16 unk_00[2];
    RwInt16 unk_04[2];
};
struct type_ED850
{
    RwInt32 unk_00;             // the entries' count
    type_ED6B0 *unk_04;         // the entries, sorted by key

    type_ED850();
    // Frees the entries (sub_ED680) when the GodAsset that loads it
    // (sub_192510) deletes it.
    ~type_ED850();
    // Reads the lookup from arg_0 (sub_192460), then sorts it (sub_ED7B0).
    void sub_ED6B0(RwStream *arg_0);
    void sub_ED7B0();
    RwInt16 sub_ED850(RwUInt8 *arg_0, RwInt16 *arg_4);
    // The lookup for a key with a value unset: none (-1).
    RwInt16 sub_ED910(RwUInt8 *arg_0, RwInt16 *arg_4);
};
// The scene entries' order: their keys' two values.
RwInt32 sub_ED7E0(const void *arg_0, const void *arg_4);
extern type_ED850 *dword_4B9300;
inline void set_dword_4B9300(type_ED850 *arg_0)
{
    dword_4B9300 = arg_0;
}

// dword_4B9190: the HUD (type_DC400, include/types/type_DC400.h): "SetHudVisible"
// shows and hides its items, the game loop pauses it (sub_D7C20), and the
// script commands set its buddy display, pain markers and crosshair colour.
struct type_DC400;
#ifdef CODFH_PLAIN
extern type_DC400 *&dword_4B9190;
#else
extern type_DC400 *dword_4B9190;
#endif

// dword_4F6950: the multiplayer game's bomb sites.
#include "game/bombsites.h"

// dword_4F6A7C: the multiplayer game's flags.
#include "game/flags.h"

// The game data's settings block (its +8, 0x34 bytes): reset (sub_1B46F0),
// written and read with the network (sub_1B4780, sub_1B48A0; the widths
// of the ranged numbers give 9999999, 999, 6 and 8 as their ranges).
struct type_4FB9E0_08
{
    RwInt32 unk_00;         // the game type ("GetGameType"; 5 bits, 1 at
                            // first)
    RwInt32 unk_04;         // (dword_4FB9EC)
    RwInt32 unk_08;
    RwInt32 unk_0C;
    RwInt32 unk_10;
    RwReal unk_14;
    RwInt32 unk_18;         // up to 9999999
    RwInt32 unk_1C;         // up to 999
    RwInt32 unk_20;
    RwInt32 unk_24;         // up to 6
    RwInt32 unk_28;         // up to 8
    RwReal unk_2C;          // (dword_4FBA14; the multiplayer manager's
                            // spectating passes it to sub_1B6DE0)
    RwInt32 unk_30;

    // Empty and out of line (the game data's constructor and destructor call
    // them): folded by /OPT:ICF into sub_6FCD0 and pDtor (config/aliases.txt).
    type_4FB9E0_08();
    ~type_4FB9E0_08();
    void sub_1B46F0();
    void sub_1B4780(struct type_1F8560 *arg_0);
    // An inline accessor for unk_28, with no address and so no database
    // name; named for its field. Evidence: the front end's sub_1C4BC0 reads
    // the second block's through a slot of its own.
    RwInt32 get_unk_28()
    {
        RwInt32 r = unk_28;
        return r;
    }
    // An inline setter for unk_14 (a whole number of seconds), with no
    // address and so no database name; named for its field. Evidence: the
    // host options' write (sub_201A70) passes the time through a slot of
    // its own and converts it as unsigned.
    void set_unk_14(RwUInt32 arg_0)
    {
        unk_14 = arg_0;
    }
    // Likewise for unk_00 (the game type). Evidence: the vote confirmation
    // (sub_221FC0) passes the type through a slot of its own.
    void set_unk_00(RwInt32 arg_0)
    {
        unk_00 = arg_0;
    }

    void sub_1B48A0(struct type_1F8560 *arg_0);
};

// The game data's sixteen records at +0x74 (one word, cleared by
// sub_1B46D0; its constructor, sub_1B46B0, clears it). Their destructor is
// empty and out of line, folded into pDtor.
struct type_4FB9E0_74
{
    RwInt32 unk_00;

    type_4FB9E0_74();
    ~type_4FB9E0_74();
    void sub_1B46D0();
    // An inline accessor for unk_00, with no address and so no database
    // name; named for its field. Evidence: the data's sub_1B4D40 reads it
    // through a slot of its own.
    RwInt32 get_unk_00()
    {
        RwInt32 r = unk_00;
        return r;
    }
};

// dword_4FB9E0: the game's rules, as the script commands read them
// (0x11C bytes). Its constructor (sub_1B49B0) builds the two settings
// blocks and the records, then resets it (sub_1B4AA0).
struct type_4FB9E0
{
    struct type_4F8058 *unk_00; // the session (sub_1B55B0)
    RwInt32 unk_04;             // the network game state (sub_1B4CF0: 0 GUI,
                                // 1 game, 2 loading a level, 3 end scores)
    type_4FB9E0_08 unk_08;  // the settings
    RwInt32 unk_3C;
    type_4FB9E0_08 unk_40;  // a second settings block
    type_4FB9E0_74 unk_74[16];
    RwInt32 unk_B4;
    RwInt32 unk_B8;
    RwInt32 unk_BC;
    RwReal unk_C0;          // the round's time (a client's, from the host)
    RwInt32 unk_C4;         // (dword_4FBAA4)
    RwInt32 unk_C8;         // (dword_4FBAA8)
    RwReal unk_CC;          // the time waited for the clients at a game's end
    RwReal unk_D0;          // the time at the level's start, in seconds
    RwInt32 unk_D4;         // set once the wait has started
    RwInt32 unk_D8;         // (dword_4FBAB8; cleared at a level's load,
    RwInt32 unk_DC;         // with unk_DC, sub_1A9160)
    RwInt32 unk_E0;
    RwInt32 unk_E4;
    RwInt32 unk_E8;         // (dword_4FBAC8)
    RwInt32 unk_EC;         // (dword_4FBACC)
    RwInt32 unk_F0;         // (dword_4FBAD0; compared with the team count)
    RwInt32 unk_F4;
    RwInt32 unk_F8;
    RwInt32 unk_FC;
    RwInt32 unk_100;
    RwInt32 unk_104;
    RwInt32 unk_108;
    RwInt32 unk_10C;        // set for four teams (the HUD's radar,
                            // type_DC400::sub_E4030, picks their icons)
    RwReal unk_110;         // a countdown (sub_1B6DE0 sets it, sub_1B6E00 runs it)
    RwInt32 unk_114;        // 1 at first
    RwInt32 unk_118;

    type_4FB9E0();
    ~type_4FB9E0();
    // An inline accessor for unk_D8, with no address and so no database
    // name; named for its field. Evidence: the front end's sub_1C4C00 reads
    // it through a slot of its own.
    RwInt32 get_unk_D8()
    {
        RwInt32 r = unk_D8;
        return r;
    }
    // The second settings block by reference: an inline with no address,
    // named for its field. Evidence: the front end's settings copy
    // (sub_1C3D20) loads the source before the count and the target.
    const type_4FB9E0_08 &get_unk_40()
    {
        return unk_40;
    }

    // Resets it ("Clean game flow manager"; the outer loop calls it before
    // each run, sub_D9C00): the settings, the records and the rest
    // (sub_1B5700).
    void sub_1B4AA0();
    void sub_1B5700();

    // An inline accessor for unk_08, with no address and so no database
    // name; named for its field. Evidence: "GetGameType" copies it through
    // a local of its own placed after the command's.
    RwInt32 get_unk_08()
    {
        RwInt32 r = unk_08.unk_00;
        return r;
    }
    // Likewise, returning it directly (no database name either). Evidence:
    // the spawn points' sorting (sub_1C1CE0) switches on it through a slot
    // left unwritten, which a direct return gives.
    RwInt32 get_unk_08_00()
    {
        return unk_08.unk_00;
    }
    // Told of a team's (or, with 1, a player's) win when every other
    // player is done (the scores' sub_1B2D00); only the width is known.
    void sub_1B6550(RwInt32 arg_0);
    // Inline accessors for unk_E8, unk_EC and unk_F0, with no addresses and
    // so no database names; named for their fields. Evidence: the game
    // score's round total (sub_1B38E0) reads each through a slot of its own.
    RwInt32 get_unk_E8()
    {
        RwInt32 r = unk_E8;
        return r;
    }
    RwInt32 get_unk_EC()
    {
        RwInt32 r = unk_EC;
        return r;
    }
    RwInt32 get_unk_F0()
    {
        RwInt32 r = unk_F0;
        return r;
    }
    // What the callbacks it hands out (sub_1B4470 to sub_1B4520) call; only
    // the widths are known.
    void sub_1B5750();
    // Copies settings arg_0 into unk_08 (sub_1B55D0), or into unk_40 with
    // unk_3C marking a change of game type or level (sub_1B5600; arg_4 runs
    // sub_1B6310), and applies unk_40 (sub_1B5690: the deathmatch's word,
    // the front end's copy, the level index).
    void sub_1B55D0(const type_4FB9E0_08 &arg_0);
    void sub_1B5600(const type_4FB9E0_08 &arg_0, RwInt32 arg_4);
    void sub_1B5690();
    void sub_1B6310();
    // unk_B4 cleared, unk_B8 set.
    void sub_1B57A0();
    void sub_1B57C0();
    // A level change to arg_0 selected (unk_F4 set when it differs, unk_F8
    // stored); the host's or the client's step (sub_1B6200, sub_1B6B50);
    // the in-game step with the time elapsed (sub_1B5BF0, sub_1B6E00).
    void sub_1B5B50(RwInt32 arg_0);
    void sub_1B5BC0();
    void sub_1B6200();
    void sub_1B6B50();
    void sub_1B5BF0();
    // What the end of a round calls; only the widths are known.
    // Balances the teams after a round: when one has more than one player
    // over the other, the local player moves (sub_1AFF20) if the rank rules
    // allow it.
    void sub_1B5F90();
    void sub_1B60E0();
    void sub_1B6C20();
    RwInt32 sub_1B6CF0();
    // The wait's time counted (sub_1B6C80); the round's time and what is
    // left of it (sub_1B6D80, sub_1B6DA0); the countdown's left, whether it
    // runs, and its value (sub_1B6E50, sub_1B6E80).
    void sub_1B6C80();
    RwReal sub_1B6D80();
    RwReal sub_1B6DA0();
    RwReal sub_1B6E80();
    void sub_1B6E00(RwReal arg_0);
    void sub_1B6360();
    void sub_1B6250();
    void sub_1B69B0();
    void sub_1B6AA0();
    // The same without a result local, with no address and so no database
    // name; named for what it returns. Evidence: the HUD's radar
    // (type_DC400::sub_E4030) switches on it through a copy of its unwritten
    // return temporary (docs/toolchain.md).
    RwInt32 get_game_type()
    {
        return unk_08.unk_00;
    }
    // Its setter, likewise nameless; named for what it sets. Evidence: the
    // join (type_4F7EB8::sub_1A9CE0) stores the host's game type through
    // an argument slot of its own.
    void set_game_type(RwInt32 arg_0)
    {
        unk_08.unk_00 = arg_0;
    }
    // The number of teams: 4 with unk_10C set, else 2. An inline with no
    // address and so no database name; named for what it returns. Evidence:
    // the radar compares its result local with 4.
    // An inline accessor for unk_10C, with no address and so no database
    // name; named for its field. Evidence: the manager's spawn points
    // (sub_1AC4E0) read it through a slot of its own.
    RwInt32 get_unk_10C()
    {
        RwInt32 r = unk_10C;
        return r;
    }
    // Its unk_10C: identical to cScopeValidator::sub_1CA260 and folded
    // (/OPT:ICF) into it; the join (sub_1AC5D0) calls it.
    RwInt32 sub_1CA260() const;
    // Tells the rules of player arg_0 joining (sub_1AC5D0); only the width
    // is known.
    void sub_1B4EA0(RwInt32 arg_0);
    RwInt32 get_team_count()
    {
        RwInt32 r;

        if (unk_10C)
        {
            r = 4;
        }
        else
        {
            r = 2;
        }
        return r;
    }
    // Inline accessors for unk_C4 and unk_C8, with no address and so no
    // database names; named for their fields. Evidence: the multiplayer
    // manager's handlers (sub_1AF370) read each through a slot of its own.
    // An inline accessor for unk_0C, with no address and so no database
    // name; named for its field. Evidence: the multiplayer manager's input
    // step (sub_1AADF0) reads it through a slot of its own each time.
    RwInt32 get_unk_0C()
    {
        RwInt32 r = unk_08.unk_04;
        return r;
    }
    // Whether the pause is refused (the input step); only the width is
    // known.
    RwInt32 sub_1B6E50();
    // An empty method (pDtor, folded by /OPT:ICF): the host's start
    // (type_4F7EB8::sub_1A9A70) calls it before taking the settings.
    void pDtor();
    RwInt32 get_unk_C4()
    {
        RwInt32 r = unk_C4;
        return r;
    }
    RwInt32 get_unk_C8()
    {
        RwInt32 r = unk_C8;
        return r;
    }
    // What the multiplayer manager's handlers pass on (sub_1AF320 and on);
    // only the widths are known.
    void sub_1B5470(const struct type_3E1074 &arg_0);
    // Sets the level to load (the settings' unk_28; the save state's and the
    // front end's copies take it, sub_19B000 and sub_1C3D80).
    void sub_1B54B0(RwInt32 arg_0);
    void sub_1B5510(RwInt32 arg_0);
    void sub_1B6A30(const struct type_3E1044 &arg_0);
    void sub_1B6B30(const struct type_3E0EB8 &arg_0);
    // A client's round end (sub_1B6A50) and whether the level may load
    // (sub_1B6BB0: not while a rejoin's session is still in state 5).
    void sub_1B6A50();
    RwInt32 sub_1B6BB0();
    // Its unk_B8: an out-of-line getter folded by /OPT:ICF into 0x1F5840
    // (config/aliases.txt).
    RwInt32 sub_1F5840();
    // Completes the search-and-destroy objectives
    // ("SDObjectivesComplete").
    void sub_1B6530();
    // Its part of the full game state, written and read (sub_1B57E0,
    // sub_1B5860), whether it takes one (sub_1E3480, 1), after taking one
    // (sub_1B59D0), its rules message written and read (sub_1B4C10,
    // sub_1B4C80), and a dword it is sent (sub_1B6EF0). Only the widths
    // are known.
    void sub_1B57E0(struct type_1F8560 *arg_0);
    void sub_1B5860(struct type_1F8560 *arg_0);
    RwInt32 sub_1E3480();
    void sub_1B59D0();
    void sub_1B4C10(struct type_1F8560 *arg_0);
    void sub_1B4C80(struct type_1F8560 *arg_0);
    void sub_1B6EF0(RwUInt32 arg_0);
    // Sets the network game state (the multiplayer manager's clean-up
    // passes 0, sub_1A8E80), printing "(%s) Entering %s game state".
    void sub_1B4CF0(RwInt32 arg_0);
    // The peers with a record set, and every record cleared.
    type_1DDE20_mask sub_1B4D40();
    void sub_1B4DB0();
    // Takes the session (the manager's set-up); only the width is known.
    void sub_1B55B0(struct type_4F8058 *arg_0);
    // What the multiplayer manager's step calls: after its unk_4FC
    // (sub_1B6EA0), with the network game's unk_10 at the end of a game
    // (sub_1B5110), and each step (sub_1B5A40). Only the widths are known.
    void sub_1B6EA0();
    // After the round's scores are sent (the scores' sub_1B3400); only the
    // width is known.
    void sub_1B6130();
    // The players in the game whose network player has no unk_130 set, and
    // the teams with such players.
    RwInt32 sub_1B6580();
    RwInt32 sub_1B6650();
    // Its game over (sub_1B6200, sub_1B6250) and round's end (sub_1B6310)
    // fades; the round's check for an early end (sub_1B6770); an id folded
    // into sub_1E4CB0 (0).
    RwInt32 sub_1B6770();
    RwInt32 sub_1E4CB0();
    // What the multiplayer manager's view changes pass on (sub_1AB440);
    // only the width is known.
    void sub_1B6DE0(RwReal arg_0);
    void sub_1B5110(RwInt32 arg_0);
    void sub_1B5A40();
    // What the game loop's wrappers (sub_1A2D60, sub_1A2D70, sub_1A2D80)
    // call; only the widths are known.
    void sub_1B52D0();
    // A level load completes (once, unk_D8): state 1, the manager reset; a
    // client asks the host to synchronise (or, rejoining, spectates), the
    // host sends the full game state to the peers with records. Then the
    // keep-alive thread stops (sub_1B2860).
    void sub_1B4F40();
    // What the level load's completion calls; only the widths are known.
    void sub_1B59F0();
    void sub_1B6470();
    // After a level load (the host's, sub_1B4F40): the scoreboard shown for
    // a deathmatch or a game with unk_08.unk_0C set (sub_1C4A30, unk_104),
    // else the team screen (sub_1C4A60, unk_108); and which one closes with
    // arg_0 stored (sub_1B5250).
    void sub_1B51D0();
    void sub_1B5250(RwInt32 arg_0);
    // A level load starts: state 2, and the host sends the rules message
    // ("(HOST) Broadcast level load start to clients"); then the network's
    // keep-alive thread starts (sub_1B2810).
    void sub_1B4DF0();
};
typedef RwChar type_4FB9E0_size_check[sizeof(type_4FB9E0) == 0x11C ? 1 : -1];
extern type_4FB9E0 dword_4FB9E0;

// dword_4B69F0: whether the frustum check is off ("EnableFrustumCheck"
// stores 1 less its argument).
extern RwInt32 dword_4B69F0;
// dword_42B714: the game difficulty ("GetGameDifficulty").
extern RwInt32 dword_42B714;
// The five-way blend's weight scale (unk_00) and rate (unk_04)
// (type_3D32F8::sub_76960), one .data object: its third dword is zero, and
// a lone zero global would be in .bss.
struct type_428BE0
{
    RwReal unk_00;
    RwReal unk_04;
    RwInt32 unk_08;
};
extern type_428BE0 unk_428BE0;
// A copy of its weights and angles for display (.data).
extern RwReal flt_449B68[5];
extern RwReal flt_449B7C;
extern RwReal flt_449B80;
extern RwReal flt_449B84;
extern RwReal flt_449B88;

// The AIHearing class's listeners (dword_43925C) and lasting sounds
// (dword_439260) and their pools (dword_439264, 25 of type_3C720;
// dword_439284, 10 of type_3C540).
extern type_3C720 *dword_43925C;
extern type_3C540 *dword_439260;
extern type_16C2A0 dword_439264;
extern type_16C2A0 dword_439284;

// dword_4B86F8: flags; while bit 4 is set no sound is emitted (sub_3C4B0);
// "RestartLevel" sets bit 3.
extern RwUInt32 dword_4B86F8;

// The AIManeuverManager's pools, the large (dword_4395B0) and the normal
// (dword_4395D0), 32 each, sized for the largest kind and the next largest;
// its handle serial dword_4395A8 (dword_4395AC is cleared with it); and its
// handle table dword_4392A8 (64 entries).
extern type_16C2A0 dword_4395B0;
extern type_16C2A0 dword_4395D0;
extern RwInt32 dword_4395A8;
extern RwInt32 dword_4395AC;

struct type_3CE6D0;
struct type_3D410;

// An entry of dword_4392A8: the handle, the object's kind and the object.
struct type_4392A8
{
    type_365A0 unk_00;
    RwInt32 unk_04;
    type_3CE6D0 *unk_08;
};
extern type_4392A8 dword_4392A8[MANEUVER_HANDLES];

struct type_3DF30;

// The squads: the list dword_4395F0 (through type_3DF30::unk_2AC), the next
// squad id dword_4395F4 and their pool dword_4395F8 ("m_freeSquadList",
// 25 of 0x2E0 bytes).
extern type_3DF30 *dword_4395F0;
extern RwInt32 dword_4395F4;
extern type_16C2A0 dword_4395F8;

// The frame counter, and the per-frame counts sub_3ED10 starts anew
// (type_4C00D0).
extern RwUInt32 dword_4B87D8;
extern type_4C00D0 dword_4C00D0;
extern type_4C00D0 dword_4C0150;

// off_427628: per kind (7), the test sub_3D150 runs for a kind no object of
// the group has yet (arg_0 the kind, arg_4 the context; 0 for none) and the
// object's size.
struct type_427628
{
    RwInt32 (*unk_00)(RwInt32 arg_0, type_3D410 *arg_4);
    RwInt32 unk_04;
};
extern type_427628 off_427628[7];

// dword_427660: the two periodic updates type_3D410::sub_3D5F0 runs: each
// entry's unk_00 selects the entry whose function is called (sub_3D700) and
// unk_08 is its period (none when not positive). Entry 0 runs sub_3D7D0.
struct type_427660
{
    RwInt32 unk_00;
    void (*unk_04)(RwInt32 arg_0, type_3D410 *arg_4);
    RwInt16 unk_08;
    RwUInt8 unk_0A[0x2];
};
extern type_427660 dword_427660[2];
// flt_427678 (240.0, .data): the target scores (sub_3FAC0) add to a target
// whose record's unk_10 is below it.
extern RwReal flt_427678;

// byte_4C1940: while set, type_3D410's sub_3DE00 accepts no target with
// flag 4 of unk_2C.
extern RwUInt8 byte_4C1940;

// unk_4292B4 (one .data object: a lone zero global would be in .bss).
struct type_4292B4
{
    RwInt32 unk_00;
    RwInt32 unk_04;
    RwReal unk_08;
    RwInt32 unk_0C;
};
extern type_4292B4 unk_4292B4;

// The face animations (unit_176E50, .data): their names and blend times
// (sub_17AD60 picks one of the first four, the death faces).
struct type_42A370
{
    RwChar unk_00[0x20];
    RwReal unk_20;
};
extern type_42A370 byte_42A370[9];

#ifdef CODFH_SP
// A level's entry in PlayerTrigger::HandleAttributes' checkpoint table (single player, SP 0x84FB3):
// its number, whether it carries the checkpoint's attributes over, and its chapter.
struct sp_level_chapter
{
    RwInt32 level;
    RwUInt8 carries;
    RwUInt8 chapter;
};
#endif

#endif
