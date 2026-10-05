/*
 * AIData (database anchor type_154C0: constructor sub_154C0, no vtable): an
 * entity's AI object. Entities embed it and return it from vf_120.
 *
 * Name evidence: sub_16E30 reports "An AIData entity slot was not cleared on
 * restart/shutdown!" (0x3CDB04) about the slot table unk_438CA8, and this
 * object's sub_16BC0 claims its slot there (unk_518); the surviving source
 * path "Source\GameCore\ai\aidatapathing.cpp" names the class too.
 *
 *   +0x00   unk_00   a float: sub_12970 compares it with flt_427400
 *   +0x58   unk_58   compared with 2 and 4 by the second handlers; set to 1
 *                    by the first handlers
 *   +0x5C   unk_5C   record number in the handler table unk_427408;
 *                    sub_17AB0 stores its argument here
 *   +0x60   unk_60   the action unk_64 accumulates for (sub_17B40, sub_17B90)
 *   +0x64   unk_64   a float accumulated while unk_5C stays unk_60
 *   +0x68   unk_68   a one-shot flag: sub_13830 requires it and clears it
 *   +0x74   unk_74   a float; sub_12290 requires it not above 0.0
 *   +0x80   unk_80   32 records of 32 bytes (see type_154C0_80.h)
 *   +0x49C  unk_49C  flags: sub_17B40 tests bit 4, sub_15370 bit 9, sub_13F60 bit 13
 *   +0x4E0  unk_4E0  zeroed by sub_16BC0; only its width is known
 *   +0x518  unk_518  record index: sub_16ED0 reads another entity's AI
 *                    object's unk_518 to pick a record here
 *   +0x52C  unk_52C  tested against zero by sub_14DF0
 *   +0x534  unk_534  tested by sub_18E90, set to 1 by sub_22F70
 *   +0x568  unk_568  the owning entity (sub_16BC0)
 *   +0x578  unk_578  a state code: sub_238E0 tests 6, 0x26, 0x2A; sub_23930
 *                    tests 5, 0x2B, 0x2C
 *   +0x540  unk_540  a mode from the owner's kind bits (sub_16BC0)
 *   +0x544  unk_544  compared with 0 and 1 by sub_12970
 *   +0x5B0  unk_5B0  a point: sub_13900 copies it in; x/y/z are read with fld
 *   +0xA74  unk_A24.unk_50  handle to an entity; sub_14800 requires it to match unk_1374
 *   +0xF54..+0xF64    path nodes (type_F8350 *); unk_F60 is the current one,
 *                    copied from unk_F54, unk_F5C or unk_F64
 *   +0x12F4..+0x1354 five type_154C0_12F4 (cover points); sub_23BE0 uses
 *                    unk_1324
 *   +0x1178 unk_1178 a float: sub_17AB0 sets a random delay for action 1
 *   +0x1374 unk_1374 handle to an entity
 *   +0x1390 unk_1390 handle: sub_18DA0 points it at an entity with an AI object
 *   +0x1394 unk_1394 reset to 0 by sub_18DA0
 *   +0x137C unk_137C handle: sub_17A20 copies unk_1374 into it for most states
 *   +0x13B4 unk_13B4 a float: sub_14EA0 compares unk_13B4 - 100 with sub_20570
 *   +0x13E0 unk_13E0 a float: sub_14EA0 sets it to 2700.0
 *   +0x1430 unk_1430 compared with -1 by sub_14930
 */
#ifndef AIDATA_H
#define AIDATA_H

#include "rw/ostypes.h"
#include "types/type_365A0.h"
#include "rw/batypes.h"
#include "rw/bamatrix.h"
#include "types/type_154C0_12F4.h"
#include "types/type_154C0_80.h"
#include "types/type_154C0_5BC.h"
#include "types/type_154C0_1444.h"
#include "types/type_3DF8D8.h"
#include "types/type_154C0_1048.h"
#include "types/type_154C0_F80.h"
#include "game/data.h"
#include "game/functions.h"
#include "types/type_14D180.h"
#include "types/type_D48D0.h"
#include "types/type_3DF30.h"
#include "types/SplinePath.h"
#include "types/type_F8350.h"

struct type_3D3548;
struct type_3DBC78;
struct type_3DC048;
struct type_3DAFC8_1DDC;

struct AIData
{
    RwReal unk_00;
    RwV3d unk_04[3];        // up to three nearby kind-11 nodes' points (sub_31E20)
    RwV3d unk_28[3];        // and facings (sub_31E20)
    RwInt32 unk_4C;         // bit n: node n is of kind 15 (sub_31E20); cleared by sub_1FC70
    RwInt32 unk_50;         // cleared by sub_1FC70
    type_D48D0 unk_54;      // handle; the constructor and destructor clear it
    RwInt32 unk_58;
    RwInt32 unk_5C;
    RwInt32 unk_60;
    RwReal unk_64;
    RwInt32 unk_68;
    RwInt32 unk_6C;         // read and cleared by type_3CE4B4::sub_33820
    RwInt32 unk_70;         // set by sub_28F00
    RwReal unk_74;          // the attack stand hold count
                            // ("SetAttackStandHoldCount")
    RwReal unk_78;          // an arrival distance (sub_1DF60)
    RwReal unk_7C;          // counted down by sub_172F0 while positive
    type_154C0_80 unk_80[0x20];
    RwInt32 unk_480;
    RwV3d unk_484;          // passed by value to sub_1AE80 by sub_172F0
    RwUInt8 unk_490[0x4];
    RwInt32 unk_494;        // passed to the owner's vf_2A8 by sub_1F470
    RwInt32 unk_498;        // shots left: sub_1F470 counts it down
    union
    {
        RwUInt32 unk_49C;
        struct
        {
            RwUInt32 unk_49C_0 : 3;
            RwUInt32 unk_49C_3 : 1;     // hurt by bullets and explosions
                                        // (type_3DAFC8's vf_064, vf_068)
            RwUInt32 unk_49C_4 : 2;
            RwUInt32 unk_49C_6 : 1;     // under AI control, the projectile
                                        // generators may target it
                                        // (sub_120E80, sub_121960)
            RwUInt32 unk_49C_7 : 2;
            RwUInt32 unk_49C_9 : 1;     // with sub_238E0, keeps a soldier
                                        // from the tanks' alert
                                        // (type_3DBC78::vf_2D0)
            RwUInt32 unk_49C_10 : 1;    // facing blocked ("BlockFacing")
            RwUInt32 unk_49C_11 : 3;
            RwUInt32 unk_49C_14 : 1;    // keeps a soldier alive at no hit
                                        // points (type_3DAFC8::sub_13C490)
            RwUInt32 unk_49C_15 : 4;
            RwUInt32 unk_49C_19 : 1;    // told when it hits its target
                                        // ("TargetHit", type_3D3548's
                                        // sub_D2AD0)
            RwUInt32 unk_49C_20 : 1;
            RwUInt32 unk_49C_21 : 1;    // keeps a soldier from being run over
                                        // (type_3DAFC8::vf_060)
            RwUInt32 unk_49C_22 : 7;
            RwUInt32 unk_49C_29 : 1;    // a tank engages every entity it
                                        // may (type_3DBC78::vf_2D0)
        };
    };
    RwInt32 unk_4A0;        // set while sub_1A950 reverses towards its point
    RwInt32 unk_4A4;        // sub_1C880's result, kept by sub_1EA70
    RwReal unk_4A8;         // a countdown: sub_1D580 logs and restarts it at 60
    RwInt32 unk_4AC;        // -1, 0 or 1, drawn by sub_1D2C0
    RwInt32 unk_4B0;        // sub_1B120 stops the owner while it is set
    RwInt32 unk_4B4;        // set by sub_1B2B0 when the owner comes close
    RwReal unk_4B8[5][2];   // a history of (1 - facing dot, time step) pairs;
                            // sub_1B710 shifts it down one and adds the newest
    RwInt32 unk_4E0;
    RwV3d unk_4E4;          // a point sub_1B2B0 measures the owner against
    RwV3d *unk_4F0;         // a target point; sub_17140 stores it
    RwV3d unk_4F4;          // a copy of the vehicle cover point (sub_1F520)
    RwV3d unk_500;
    RwV3d unk_50C;          // zeroed by sub_17140; read and written with fld/fstp
    RwInt32 unk_518;
    RwInt32 unk_51C;        // AI control ("GetAIControl", "SetAIControl");
                            // required nonzero by sub_1A1F0
    RwInt32 unk_520;        // set to 1 by sub_18BB0 on acquiring a target;
                            // alerted ("SetAlerted", "IsAlerted")
    RwInt32 unk_524;
    RwInt32 unk_528;        // cleared by sub_23790
    RwInt32 unk_52C;        // whether the target may leave the line of sight
                            // ("SetAllowTargetLOSLoss")
    RwInt32 unk_530;        // reset by sub_18BB0 on acquiring a target
    RwInt32 unk_534;
    RwInt32 unk_538;        // the sound classes heard (AIHearing's sub_3C980);
                            // sub_172F0: -1 while unk_5C is 0, 4 or 0x1A, else 0
    RwInt32 unk_53C;        // the sound kinds heard; 0x57 from the constructor
    RwInt32 unk_540;        // the sides heard (0: all)
    RwInt32 unk_544;
    RwInt32 unk_548;        // cleared by sub_19010
    RwUInt32 unk_54C;       // flags: sub_18BB0 clears bit 2; sub_22110 clears it
    RwReal unk_550;         // time in states 3, 4 and 0x1A (sub_172F0)
    RwReal unk_554;         // time out of them; cleared with unk_54C by sub_22110
    RwReal unk_558;         // sub_22110 only acts while it is not positive
    RwInt32 unk_55C;
    RwInt32 unk_560;
    RwInt32 unk_564;
    type_3D3548 *unk_568;
    type_3DF30 *unk_56C;    // the group the entity is in (sub_17030)
    RwInt32 unk_570;        // the group's unk_2B4, copied by sub_17030
    union
    {
        RwUInt32 unk_574;       // a handle sub_1A1F0 resolves with sub_3D3E0
        type_365A0 unk_574_h;
    };
    RwInt32 unk_578;
    RwReal unk_57C;         // time, advanced by sub_172F0
    type_D48D0 unk_580;     // handle: the entity sub_1A630 keeps pace with
    type_D48D0 unk_584;
    RwReal unk_588;         // how long the unk_584 entity has blocked the path
                            // (sub_30A50; reset by sub_309E0)
    RwReal unk_58C;         // a distance: sub_1A630 compares the gap with it
    RwReal unk_590;         // a speed sub_1A630 divides by
    RwReal unk_594;         // time accumulated by sub_192D0
    RwInt32 unk_598;        // sub_19780 heads for unk_D70 only while this
    RwInt32 unk_59C;        // and unk_59C are both 0
    RwInt32 unk_5A0;        // sub_2D3A0 hands over to sub_2C220 while it is set
    RwInt32 unk_5A4;        // set by sub_29380; sub_332D0 plans a type 0, 1 or
                            // 4 search only while it is set
    type_F8350 *unk_5A8;    // a path node: sub_29540 plans to its point
    RwInt32 unk_5AC;        // passed along with unk_5A8 to sub_29940
    RwV3d unk_5B0;
    type_154C0_5BC unk_5BC; // five paths (see type_154C0_5BC): sub_28D80
    type_154C0_5BC unk_734; // plans into unk_5BC and unk_734, sub_28C60 into
    type_154C0_5BC unk_8AC; // unk_A24; unk_8AC is followed by sub_192D0 and
    type_154C0_5BC unk_A24; // its kin, unk_B9C planned by sub_31240
    type_154C0_5BC unk_B9C; // (sub_1A2E0)
    SplinePath *unk_D14;   // a spline sub_5B240 takes from an object's +0x24
    RwReal unk_D18;         // a spline position (sub_1B2B0)
    RwReal unk_D1C;         // the spline's end (1.0 from sub_5B240)
    RwReal unk_D20;         // the spline increment (type_3D3548 vf_124, vf_128)
    RwReal unk_D24;         // the spline step: sub_2E2F0 advances unk_D18 by it
                            // over the control points
    RwUInt8 unk_D28[0x8];
    RwMatrix unk_D30;       // set to identity by the constructor; sub_213B0 has
                            // the spline (sub_BA990) fill it
    RwV3d unk_D70;          // a point: sub_29ED0 reads it with fld, sub_16DD0
                            // makes it the target
    RwV3d unk_D7C;          // the owner's position when sub_29FC0 set a path
    RwReal unk_D88;         // a range per state, set by sub_17190
    RwV3d unk_D8C;          // a direction: sub_19570 has arrived once the offset
                            // to unk_D70 points against it
    RwV3d unk_D98;          // the horizontal direction from unk_D70 to the
                            // spline point (sub_2E2F0)
    RwV3d unk_DA4;          // the owner's position when sub_17BF0 changed state
    RwV3d unk_DB0;
    RwInt32 unk_DBC;        // set to 1 by sub_17190 for some states
    RwInt32 unk_DC0;        // when set, sub_2CE90 casts along unk_8AC's unk_08
    RwV3d unk_DC4;          // the horizontal direction to unk_D70 (sub_29ED0)
    RwInt32 unk_DD0;        // compared with its argument by sub_23CD0
    RwInt32 unk_DD4;        // set by sub_22EF0
    RwInt32 unk_DD8;        // lets sub_244E0 plan a path to a new node (sub_29630)
    type_154C0_5BC unk_DDC; // a seventh path: sub_29630 plans to a node
    type_F8350 *unk_F54;
    type_F8350 *unk_F58;
    type_F8350 *unk_F5C;
    type_F8350 *unk_F60;
    type_F8350 *unk_F64;
    RwReal unk_F68;         // set to 2500.0 by sub_204E0 and sub_20370
    RwReal unk_F6C;         // the cover point search radius
                            // ("SetCoverPointSearchRadius")
    RwV3d unk_F70;          // zeroed (z, y, x) by sub_23CD0
    type_D48D0 unk_F7C;     // the tracked entity at the last defend-area search
    type_154C0_F80 unk_F80[25]; // results for the unk_1048 search (sub_27CC0)
    type_154C0_1048 unk_1048;   // node searches (sub_F8970); sub_154C0 builds
    RwV3d unk_10A8;         // compared with the tracked entity's position
                            // (sub_28F30)
    RwV3d unk_10B4;         // the owner's position at the last unk_1114 search
    type_D48D0 unk_10C0;    // handle; sub_19F30 compares it with unk_1374
    type_154C0_F80 unk_10C4[10]; // results for the unk_1114 search (sub_28F30)
    type_154C0_1048 unk_1114;   // both inline
    RwInt32 unk_1174;       // the next unk_10C4 result sub_28F30 tries
    RwReal unk_1178;
    type_154C0_5BC unk_117C; // a sixth path: sub_29780 plans to a vehicle cover point
    type_154C0_12F4 unk_12F4;
    type_154C0_12F4 unk_130C;
    type_154C0_12F4 unk_1324;
    type_154C0_12F4 unk_133C;
    type_154C0_12F4 unk_1354;
    RwInt32 unk_136C;       // set by sub_22F30
    type_D48D0 unk_1370;    // handle: sub_24BA0 walks only its entity under flag 22
    type_D48D0 unk_1374;
    RwReal unk_1378;        // time tracking the entity (sub_172F0); reset by
                            // sub_18BB0 on a target change
    type_D48D0 unk_137C;
    RwV3d unk_1380;         // where sub_1EA70 last saw the tracked entity
    RwInt32 unk_138C;
    type_D48D0 unk_1390;
    RwReal unk_1394;        // time, advanced by sub_172F0
    RwReal unk_1398;        // reset to 1e37 by sub_22F70 and sub_23670
    RwReal unk_139C;        // the nearest blocker on the way to a player
                            // target (sub_41B20); reset by sub_18BB0 on a
                            // target change
    type_3DF8D8_04 unk_13A0; // a key, cleared by sub_20370 and sub_204E0
    RwV3d unk_13A8;         // a point sub_192D0 measures unk_8AC's unk_20 against
    RwReal unk_13B4;
    RwReal unk_13B8;        // sub_205E0 passes both to sub_20670 and asks
    RwReal unk_13BC;        // whether either is nonzero
    type_D48D0 unk_13C0;    // handle; sub_20AC0 falls back to its entity
    RwV3d unk_13C4;         // copies of unk_13EC and unk_13F8 (sub_213B0)
    RwV3d unk_13D0;
    RwInt32 unk_13DC;       // set to 3 by sub_20370
    RwReal unk_13E0;
    type_D48D0 unk_13E4;    // handle; sub_20C00 resolves it
    type_D48D0 unk_13E8;    // handle: the follow target in state 0x2C (sub_190C0)
    RwV3d unk_13EC;         // a point: sub_212E0 fills both from the unk_13E8
    RwV3d unk_13F8;         // entity (sub_D42B0 / sub_D4290 or sub_20830)
    RwInt32 unk_1404;       // a mode: sub_20C50 stores its arg_4; compared
                            // with 3 and 4 by sub_24F60
    type_3DF8D8_04 unk_1408; // the key of the spline object being followed
                             // (sub_20DA0); sub_20C50 zeroes the halves
    SplinePath *unk_1410;  // the spline being followed; sub_212A0 requires it
    RwReal unk_1414;        // the furthest spline parameter reached (sub_213B0)
    RwV3d unk_1418;         // the spline point at unk_1414
    RwInt32 unk_1424;       // lets sub_213B0 accept a parameter behind unk_1414
    RwReal unk_1428;        // a leash distance: sub_213B0 stops past it
    RwReal unk_142C;        // with flag 13, sub_213B0 also moves unk_13A8
    RwInt32 unk_1430;       // set to its argument by sub_1A5A0
    RwReal unk_1434;        // a time, cleared by sub_1A5A0 for state 3 and unknown
                            // states; type_3CE4B4::vf_034 waits 60 past it
    RwV3d unk_1438;         // three floats sub_1A2E0 stores x, y, z; sub_1A5A0 zeroes them
    type_154C0_1444 unk_1444[3];

    // sub_154C0 and sub_16AB0.
    AIData();
    ~AIData();

    // Returns arg_0's record (the one arg_0's AI object's unk_518 selects).
    // If the record's handle no longer resolves to a live entity it is
    // pointed at arg_0 and reset; *arg_4 (when given) gets 0 in that case,
    // 1 if the handle still resolved. Returns 0 for no entity or no AI.
    // Attaches the AI object to its owner: unk_568, an entity slot in
    // unk_438CA8 (unk_518) and the mode unk_540 from the owner's kind bits.
    void sub_16BC0(type_3D3548 *arg_0);
    // Detaches the AI object from its owner, undoing sub_16BC0: releases the
    // five unk_12F4 records, leaves the group, clears its unk_438CA8 slot and
    // finally unk_568.
    void sub_16C50();
    // Called by sub_16C50; they work on unk_13E4, unk_F5C and one unk_12F4
    // record respectively (sub_23100). Results, if any, are unused there.
    void sub_20C00();
    void sub_238B0();
    // Releases the record arg_0 refers to (clears its flag bit 2 and entity
    // handle when the owner holds it); returns it, or 0 when another entity
    // holds it.
    type_14D180 *sub_23100(type_154C0_12F4 *arg_0);
    // Clears +0x4C and +0x50, then works through the owner (unk_568).
    void sub_1FC70();
    // The unk_80 record of arg_0 (claimed for it when free); callers pass 0
    // for arg_4.
    type_154C0_80 *sub_16ED0(type_3D3548 *arg_0, RwBool *arg_4);
    // The tracked entity's record float (its unk_0C), or -1 without one.
    RwReal sub_17100();
    // For states 8-13 and 16-29, points unk_137C at the tracked entity. Its
    // argument is unused and only known by width.
    void sub_17A20(RwReal arg_0);
    // Sets the target point unk_4F0 and zeroes unk_50C. Callers pass entity
    // positions (sub_CD550) and points inside AI objects.
    void sub_17140(RwV3d *arg_0);
    // Sets flags in unk_49C; flag 0x8000 first targets the tracked entity and
    // runs sub_29ED0.
    void sub_16D70(RwUInt32 arg_0);
    // Clears flags in unk_49C; flag 0x8000 with unk_DBC set first targets
    // unk_D70.
    void sub_16DD0(RwUInt32 arg_0);
    // Leaves the group (through its sub_3E7C0).
    void sub_17080();
    // Sets unk_DC4 to the horizontal direction from the owner to unk_D70,
    // normalised unless it is (nearly) zero.
    void sub_29ED0();
    // Takes over the path arg_4 as arg_0 (the path unk_8AC is followed
    // along): picks the node to head for first, the first node within 150
    // in height with a clear line from the owner when arg_8 is set (and the
    // owner's unk_28 bit 7 is clear), else the nearest such node unless it
    // is the one already next; then sets the heading unk_08 and the point
    // unk_38 (checking the owner's sphere against the turn, sub_91F40 lines
    // and the path's unk_34), stores the owner's position in unk_D70,
    // unk_D7C and the path's unk_44, the direction to unk_38 in unk_D8C,
    // and restarts following (sub_2AE00, sub_29ED0, sub_309E0, sub_2CE90
    // under flag 2 or 25).
    void sub_29FC0(type_154C0_5BC *arg_0, type_154C0_5BC *arg_4, RwInt32 arg_8);
    // Called by sub_29FC0 with the owner's position arg_0, the path's point
    // arg_4 (its unk_38) and the path: moves the steering point unk_D70
    // towards arg_4 within a range from unk_D88 (scaled by how straight the
    // turn is), then aside along the path's heading, keeping it within
    // reach; stores the owner's position in unk_D7C and the direction from
    // it to unk_D70 in unk_D8C (and unk_D70 in unk_13A8 under flag 24).
    void sub_2AE00(RwV3d *arg_0, RwV3d *arg_4, type_154C0_5BC *arg_8);
    // Joins the group arg_0 (or none), copying its unk_2B4.
    void sub_17030(type_3DF30 *arg_0);
    // The entity of the group's handle, or 0 without a group.
    type_3D3548 *sub_170C0();
    // Sets unk_D88 (and for some states unk_DBC) from the state unk_578. Its
    // argument is unused and only known by width.
    void sub_17190(RwReal arg_0);
    // Sets the action (unk_5C), restarting the accumulator when it changes;
    // action 1 also draws a random delay into unk_1178.
    void sub_17AB0(RwInt32 arg_0);
    // unk_64 while flag bit 4 is set and the action is still unk_60; else
    // restarts the accumulation for the current action and returns 0.
    RwReal sub_17B40();
    // Adds arg_0 to unk_64 under the same condition, else restarts it.
    void sub_17B90(RwReal arg_0);
    // Returns 1 for an entity with no AI object, else sub_18F00 on arg_0's
    // record (from sub_16ED0) and arg_4; arg_4 is only known by width.
    RwInt32 sub_18E40(type_3D3548 *arg_0, RwInt32 arg_4);
    // Sets the tracked entity (unk_1374) to arg_0, remembering the previous
    // one in unk_137C and logging "FoundTarget"/"LostTarget".
    void sub_18BB0(type_3D3548 *arg_0);
    // Does nothing; sub_172F0 calls it for state 10 with unk_484 by value.
    void sub_1AE80(RwV3d arg_0, RwReal arg_C);
    // Turns the owner towards the tracked entity (unk_1374) through vf_29C
    // on the owner's unk_624 entity. sub_172F0 calls it for state 39 with
    // its own float argument (which it reads with fld); arg_0 is unused here.
    void sub_19CA0(RwReal arg_0);
    // Points unk_1390 at arg_0 (resetting unk_1394) when arg_0 has an AI
    // object.
    void sub_18DA0(type_3D3548 *arg_0);
    // 1 for an entity without an AI object; otherwise sub_18E90 on its
    // record.
    RwBool sub_18DF0(type_3D3548 *arg_0, RwBool arg_4);
    RwBool sub_18E90(type_154C0_80 *arg_0, RwBool arg_4);
    // 1 when arg_0 (with a vf_00C entity) is within 300 of the record's point.
    RwBool sub_18F80(type_3D3548 *arg_0, type_154C0_80 *arg_4);
    // Tests a point against the AI object's floats at +0x13B8/+0x13BC with a
    // float threshold (callers pass 0.0f and -175.0f), through sub_20670.
    RwInt32 sub_205E0(RwV3d *arg_0, RwReal arg_4);
    // sub_205E0's worker: it passes arg_0, unk_13BC, unk_13B8, its own
    // threshold and whether either of those two floats is nonzero.
    RwInt32 sub_20670(RwV3d *arg_0, RwReal arg_4, RwReal arg_8, RwReal arg_C, RwInt32 arg_10);
    // Sets flag 13 and a leash around arg_0 (unk_13A8 and unk_13D0) with
    // radius arg_4 and the two further distances arg_8 and arg_C (each raised
    // to flt_4275B8 when nonzero and below its minimum; arg_8's test reads
    // flt_4275BC); records the owner's facing (unk_13C4), mode 3 (unk_13DC),
    // and clears the unk_13A0 key, the unk_13C0 entity, unk_F68 (to 2500)
    // and unk_F70.
    void sub_20370(RwV3d *arg_0, RwReal arg_4, RwReal arg_8, RwReal arg_C);
    // Sets flag 13 and a leash around the object registered under arg_0,
    // as sub_20370 does for a point: for kinds 0x2C and 0x2E with flag 2
    // around the entity whose id it holds (its speed direction, else its
    // facing), otherwise around its vf_00C point along its vf_010, keeping
    // the key in unk_13A0. Widens arg_4 by 100 when it is under the
    // entity's radius plus 100. Returns 1 when a leash was set.
    RwInt32 sub_1FF10(type_3DF8D8_04 *arg_0, RwReal arg_4, RwReal arg_8, RwReal arg_C);
    // Clears flag 13, the unk_13A0 key and the unk_13C0 entity, and resets
    // unk_F68 (to 2500) and unk_F70.
    void sub_204E0();
    // Copy the position of arg_4 (the unk_13C0 / unk_13E8 entity when 0)
    // into *arg_0, 120 lower for an entity with kind bit 4, and return arg_0.
    RwV3d *sub_20AC0(RwV3d *arg_0, type_3D3548 *arg_4);
    RwV3d *sub_20B30(RwV3d *arg_0, type_3D3548 *arg_4);
    // Makes arg_0 the unk_13E4 entity, releasing the previous one
    // (sub_20C00) and registering with arg_0 (sub_D3FF0).
    void sub_20BA0(type_3D3548 *arg_0);
    // Of the 32 unk_80 records, the entity of a live one (subject to the
    // record's flag bit 1 and distance, the entity's kind and side bits and
    // its +0x28 bit 9); 0 when arg_0 or arg_4 is set or none qualifies.
    type_3D3548 *sub_1FCC0(RwInt32 arg_0, RwInt32 arg_4);
    // When arg_0 is further than arg_C (dword_4275C8 when 0.0f) from arg_8,
    // ignoring height: *arg_4 = the direction to it, *arg_8 = arg_0, and 1.
    RwInt32 sub_20830(RwV3d *arg_0, RwV3d *arg_4, RwV3d *arg_8, RwReal arg_C);
    // Under flag 13, moves the leash centre unk_13A8 with its anchor: the
    // unk_13C0 entity's position (sub_20AC0), with unk_13C4 / unk_13D0 from
    // the entity itself when it is also the unk_13E4 one, else from
    // sub_20830; without an entity, the point (vf_00C) of the object keyed
    // unk_13A0 (kind 0x2C to 0x2E), clearing the leash (sub_204E0) when the
    // key finds no such object.
    void sub_208F0();
    // 1 when arg_0 (the unk_13E8 entity when 0) exists and unk_1410 is set.
    RwInt32 sub_212A0(type_3D3548 *arg_0);
    // Whether this AI and arg_0's share a leash: 1 when arg_0 is the unk_13E8
    // follow target (unless the action unk_578 is 0x26), or when both have
    // flag 13 and the same unk_13C0 entity, or (without one) the same
    // unk_13A0 key, or (without a key) leash centres within 100.
    RwInt32 sub_21120(type_3D3548 *arg_0);
    // Updates unk_13EC / unk_13F8 from the unk_13E8 entity unless
    // sub_212A0 holds.
    void sub_212E0();
    // Enters the state arg_0: resets the target (sub_17140, unk_50C) and
    // path flags, remembers the owner's position in unk_DA4, then per state
    // takes over one of the paths into unk_8AC (sub_29FC0), starts along the
    // unk_D14 spline, heads for a point, or sets timers; states 16/34 and
    // 24/33 become 34 and 33 for an owner whose vf_014 entity's vf_2DC is
    // set. Records the state in unk_578 (resetting unk_57C on a change).
    // Returns what sub_192D0 returned for states 2, 41 and 46, 0 when state
    // 47 finds no path, else 0.
    RwInt32 sub_17BF0(RwInt32 arg_0);
    // The per-frame update (arg_0 is the time step): unless the owner's
    // unk_28 bit 9 is set (which clears flags 5 and 6), advances or counts
    // down the timers, sets unk_54C bits 1 and 2 from them, keeps the
    // owner's top speed in unk_590, runs the handler for the state unk_578,
    // then sub_212E0 and sub_208F0.
    void sub_172F0(RwReal arg_0);
    void sub_30A50(RwReal arg_0);
    // Copies the vf_1C8 object arg_8 into arg_4 with the frame arg_0's at
    // and right rows, resets every record's flag and distance, and runs the
    // collision queries for arg_8's set records (sub_992B0) and followed
    // entities (sub_9A2D0) into it.
    void sub_30B90(RwMatrix *arg_0, type_3DAFC8_1DDC *arg_4, type_3DAFC8_1DDC *arg_8);
    // State handlers of sub_172F0: sub_198A0 follows the unk_8AC path after
    // its tracked entity (logging "AStar_ArrivedATDestination" and the
    // like); sub_1ECF0 steers a tank at the tracked entity by the path, the
    // node or its facing (RtQuatConvertToMatrix); sub_1B540 is disabled (a
    // `goto` past its body).
    void sub_198A0(RwReal arg_0);
    void sub_1B540(RwReal arg_0);
    void sub_1ECF0(RwReal arg_0);
    // Places *arg_4 at the offset arg_0 in the owner's frame (sub_1414C0),
    // pulls it back to where a line from the owner's eye hits something
    // (sub_D2FC0) once that is over flt_4275D4 away, and then drops it onto
    // the ground below (a second line test). The result is the last test's.
    RwInt32 sub_21A90(RwV3d *arg_0, RwV3d *arg_4);
    // Finds a spot beside or behind the owner, away from arg_0 (0 when the
    // owner has no vf_008 object, arg_0 is missing, or the two are on
    // different sides per cmp_unk_2C): tries dword_4275D8 ahead when the owner
    // faces away from arg_0 and the vf_1C8 object's fifth unk_54 flag is clear, then to the side
    // away from it and the other side, then behind (sub_21A90). A spot found
    // becomes the vf_008 object's unk_604 and the target (unk_4F0, unk_5B0).
    RwInt32 sub_21C90(type_3D3548 *arg_0);
    // Advances along the unk_1410 spline towards arg_0 (the unk_13E8 entity
    // when 0): takes the nearest parameter past unk_1414 unless the entity
    // is over unk_1428 away at a different height, moves the follow point
    // (sub_20830) and logs arrival at the spline's end.
    void sub_213B0(type_3D3548 *arg_0);
    // The horizontal speed of arg_0 (its vf_0C8 with y zeroed) when over 5,
    // else 0. Then *arg_4 gets that velocity in arg_0's frame (sub_141320)
    // or as it is for kinds 0x40080, and *arg_8 the world velocity.
    RwReal sub_1FDF0(type_3D3548 *arg_0, RwV3d *arg_4, RwV3d *arg_8);
    // Makes arg_0 the unk_13E8 follow target: sets unk_13EC / unk_13F8 from
    // it and unk_1404 to arg_4, and clears unk_1408, unk_140C and unk_1410.
    void sub_20C50(type_3D3548 *arg_0, RwInt32 arg_4);
    // Starts following the spline of the object keyed *arg_14 (kind 0x2C or
    // 0x2E with flag 0x80): sub_20C50 with arg_0 and arg_8, then the leash
    // arg_C (unk_1428), mode arg_4 (unk_1424), the key (unk_1408) and the
    // spline (unk_1410); the parameter nearest unk_13F8 becomes unk_1414 and
    // its point unk_1418 (and unk_13F8). unk_13EC becomes the horizontal
    // direction along the spline: in mode 1 towards the owner's nearest
    // point, else forward (backward near the end, within 0.001). With a
    // positive arg_10 (kept in unk_142C) also sets the unk_1418 leash
    // (sub_20370) and copies unk_13EC to unk_13C4.
    void sub_20DA0(type_3D3548 *arg_0, RwInt32 arg_4, RwInt32 arg_8, RwReal arg_C,
                   RwReal arg_10, type_3DF8D8_04 *arg_14);
    // State 37 of sub_172F0: keeps following the tracked entity (sub_19F90)
    // and checks the vehicle cover record unk_12F4 refers to, logging it lost,
    // invalid (flag bit 1 clear) or moved (over 200 from the owner).
    void sub_1FA00(RwReal arg_0);
    // State 35 of sub_172F0: heads for the vehicle cover point unk_12F4
    // refers to (copied into unk_D70 and unk_4F4) as sub_19780 moves, and
    // logs arrival within 125, an invalid point or a lost one.
    void sub_1F520(RwReal arg_0);
    // State 36 of sub_172F0: follows the unk_8AC path to the vehicle cover
    // point, checking every 15 time units whether it moved over 500 from the
    // path's point; logs arrival, or an invalid or lost point (ending the
    // path).
    void sub_1F7C0(RwReal arg_0);
    // A distance-like float for a point, from the box between it and the
    // AI object's +0x13A8 point (RwV3dLength).
    RwReal sub_20570(RwV3d *arg_0);
    // Stores arg_0 at +0xDD4 (and through sub_22F30 at +0x136C), clears
    // unk_F54 when it is 0, and returns 1. arg_0 is only known by width.
    RwInt32 sub_22EF0(RwInt32 arg_0);
    // Copies unk_F54 into unk_F5C and resets +0x1398.
    void sub_23670();
    // Sets unk_F5C to arg_0 (registering it when its kind is 0x11).
    void sub_236F0(type_F8350 *arg_0);
    // unk_F54 if it passes sub_205E0 (when flag bit 13 is set) and
    // sub_26A80, else 0.
    type_F8350 *sub_23B60();
    // 1 for a record whose flag bit 0 or 1 is set; otherwise, when unk_534 and
    // arg_4 are set, sub_18F80 on the record's entity. arg_4 is only known by
    // width.
    RwInt32 sub_18F00(type_154C0_80 *arg_0, RwInt32 arg_4);
    // The owner's score for the target arg_0 (type_3D410's sub_3DCD0 takes
    // the best): by the owner's kind (unk_2C flags 0x20, 0x40000, 0x80),
    // through sub_404A0 or sub_3FAC0, sub_401B0 or sub_403F0; -2 for none.
    RwInt32 sub_3FA10(type_3D3548 *arg_0);
    // The score for arg_0 when the owner has a vehicle-like unk_61C
    // (sub_3FA10). Stays binary (docs/units.md).
    RwInt32 sub_404A0(type_3D3548 *arg_0);
    // 1 when the tracked entity (unk_1374) is also the unk_A24 path's entity
    // and that path's node count (unk_64.unk_2C) is set.
    RwBool sub_19ED0();
    // 1 when the tracked entity is also the entity of the handle unk_10C0
    // and the unk_734 path's node count (unk_64.unk_2C) is set.
    RwBool sub_19F30();
    // With an owner whose vf_098 is nonzero: clears unk_548, then passes
    // vf_098 to sub_31BE0 when arg_0 is set, else to sub_31C30 and clears
    // unk_544. arg_4 is overwritten before use; only the widths are known.
    void sub_19010(RwInt32 arg_0, RwInt32 arg_4);
    // Copies the tracked entity's position into unk_D70 and calls
    // sub_19570(arg_0); without one, logs "AStar_LostFollowTarget". Its
    // argument is sub_172F0's float argument (state 45).
    void sub_194E0(RwReal arg_0);
    // Called with sub_172F0's float argument (state 40) and by sub_194E0.
    // Moves as sub_19780 does, then logs "AStar_ArrivedATDestination" once
    // unk_D70 is within 125 (ignoring height) or behind unk_D8C.
    void sub_19570(RwReal arg_0);
    // State 32 of sub_172F0. Unless sub_2DAA0 reports done, follows the
    // tracked entity (owner kind bit 5 with flag 15) or heads for unk_D70,
    // then applies the flag 23 / flag 2 follow-ups.
    void sub_19780(RwReal arg_0);
    // States 2, 15, 31, 41, 46 and 47 of sub_172F0. Follows the unk_8AC path
    // with sub_2B740 and logs arrival at a destination (returning 1) or a
    // cover point; in state 0x29 it also logs "AStar_TargetMoved" every 30
    // time units once unk_13A8 is over 500 from the path's point.
    RwInt32 sub_192D0(RwReal arg_0);
    // Positive on arrival, negative at a cover point, else 0 (as
    // sub_192D0 reads it); returns 1 for an empty path.
    RwInt32 sub_2B740(type_154C0_5BC *arg_0);
    // Whether arg_4 has reached the path point arg_8 (sub_2B740 passes
    // unk_D70, the path's unk_38 and its direction unk_08): 0 when the two
    // heights are more than 70 below or 150 above each other (from the
    // higher one), 1 within 64; else 1 when the heading arg_C (flattened,
    // normalised if arg_10) points back from arg_8 towards arg_4 within 200.
    // arg_0 is unused.
    RwInt32 sub_2AC00(type_154C0_5BC *arg_0, RwV3d *arg_4, RwV3d *arg_8, RwV3d *arg_C,
                      RwInt32 arg_10);
    // Advances along the unk_D14 spline: the parameter is unk_D18 plus
    // unk_D24 per control point, past the end unk_D1C or below 0 wrapped
    // or clamped by the spline's mode (unk_1C & 3). Fills unk_D30 through
    // sub_BA990 and sets unk_D98 to the horizontal direction from unk_D70 to
    // the point (zero with fewer than two control points).
    void sub_2E2F0();
    // States 5, 43 and 44 of sub_172F0. Follows the unk_8AC path as
    // sub_192D0 does; in states 0x2B and 0x2C it then logs a lost follow
    // target and checks the unk_F60 cover point with sub_25DD0.
    void sub_190C0(RwReal arg_0);
    // States 8 and 11 of sub_172F0. Steers the owner along the unk_8AC path
    // (sub_1A950 gives the turn and speed) and logs arrival.
    void sub_1B120(RwReal arg_0);
    // State 9 of sub_172F0: follows the unk_8AC path towards its entity
    // (unk_8AC.unk_50), logging a lost target, a target that moved over 1000
    // (checked every 60 time units) and arrival.
    void sub_1AE90(RwReal arg_0);
    // State 12 of sub_172F0: steers towards unk_D70 (sub_1A950). Near the
    // end of the unk_D14 spline (flag 27) it stops once within
    // 20 * speed of unk_4E4 (unk_4B4); otherwise keeps pace (sub_1A630).
    void sub_1B2B0(RwReal arg_0);
    // State 16 of sub_172F0; sub_1D560 (state 34) only forwards to it. With
    // flag 17 and a tracked entity that sub_18DF0 accepts, aims at it
    // (sub_1C4F0) when out of the owner's vf_14C range in mode 2; otherwise
    // turns by the owner's +0x2870. Every 30 time units logs
    // "AttackPauseFinished" and redraws unk_4AC.
    void sub_1D2C0(RwReal arg_0);
    void sub_1D560(RwReal arg_0);
    // State 17: counts unk_4A8 down by arg_0; once it is below 0, logs
    // "LookOutEntityEmerged" with the owner's vf_25C and restarts it at 60.
    void sub_1D580(RwReal arg_0);
    // Pass the owner's vf_098 to sub_31DC0 / sub_31E00; sub_1FC70 first
    // clears unk_4C and unk_50.
    void sub_1FC40();
    // State 27 of sub_172F0: stops the owner and, with a tracked entity,
    // aims at it through sub_1C4F0; otherwise, or when that fails, stops
    // turning too.
    void sub_1F2A0(RwReal arg_0);
    // State 28: steers towards the tracked entity with sub_1B710.
    void sub_1F390(RwReal arg_0);
    // State 29: fires through the owner's vf_2A8 while unk_498 shots are
    // left and logs "FireWeaponCompleted" when they run out.
    void sub_1F470(RwReal arg_0);
    // States 38 and 42: checks the unk_F60 cover node (sub_25DD0) and, in
    // state 0x2A, the unk_13E8 follow target.
    void sub_1FB80(RwReal arg_0);
    // Aims arg_0 at arg_4 (its sub_1BEF0 point) within range arg_8; 0 when
    // arg_4's record is not live and arg_0's vf_018 is clear, else 1. Steers
    // and pitches as sub_1D620 does (sub_1BAA0). Calls vf_2A8(0) when the
    // turn is at least 0.985, the pitch within 0.0872 and the line tests
    // (sub_D2FC0; the first only when unk_450's sub_14C140 is over
    // flt_4275C4 or arg_4 is beyond vf_254) are clear, and vf_2A8(1) when the
    // turn is at least 0.6 for an arg_4 with a vf_008, vf_024 or qualifying
    // vf_00C. For such an arg_4 also calls vf_2A8(2) with the point when
    // sub_1BD50 reports a turn over 0.3301. arg_C is unused; sub_1F2A0 passes
    // 1000000.0f and 1.
    RwInt32 sub_1C4F0(type_3DC048 *arg_0, type_3D3548 *arg_4, RwReal arg_8, RwInt32 arg_C);
    // The same outputs as sub_1A950, towards the point arg_14 (unk_D70 when
    // 0): *arg_8 is the cross product of the facing and the direction to it,
    // *arg_C a turn amount from the unk_4B8 history clamped to [-1, 1], and
    // *arg_10 a speed that drops as the turn grows. 0 when the point is
    // straight above or below.
    RwInt32 sub_1B710(RwReal arg_0, type_3DC048 *arg_4, RwV3d *arg_8, RwReal *arg_C,
                      RwReal *arg_10, RwV3d *arg_14);
    // Asks arg_4 for a point near arg_0 (its vf_110) into *arg_8 and, when
    // arg_C is set and arg_4 qualifies, replaces it by a collision point
    // from sub_92430 above the owner. Returns 1.
    RwInt32 sub_1BEF0(type_3DC048 *arg_0, type_3D3548 *arg_4, RwV3d *arg_8, RwInt32 arg_C);
    // Steers arg_0 towards arg_4 within range arg_8, with the outputs of
    // sub_1B710 in arg_C and arg_10 and two more floats in arg_14 and
    // arg_18; tested against zero. arg_1C is only known by width.
    RwInt32 sub_1BAA0(type_3DC048 *arg_0, RwV3d *arg_4, RwReal arg_8, RwV3d *arg_C,
                      RwReal *arg_10, RwReal *arg_14, RwReal *arg_18, RwV3d *arg_1C);
    // Aims arg_0 at the point arg_4, with the cross product in *arg_8 and a
    // turn amount in *arg_C (as sub_1B710 gives them); tested against zero
    // by sub_1C4F0.
    RwInt32 sub_1BD50(type_3DC048 *arg_0, RwV3d *arg_4, RwV3d *arg_8, RwReal *arg_C);
    // State 33 of sub_172F0: keeps the owner aimed at the tracked entity
    // (sub_1C4F0), re-planning with sub_1C880 every 300 time units or when
    // the entity has moved over 1500 from unk_1380, and otherwise turning
    // towards it (sub_1B710) unless the owner's vf_2A4 says it is busy.
    void sub_1EA70(RwReal arg_0);
    // State 22 of sub_172F0: drives the owner to the point unk_5B0
    // (sub_1B710), at half speed while barely turning, and logs arrival
    // within unk_78; otherwise sub_1BFB0. The first time round (unk_4A8
    // not positive) it sets flag 16 when the point lies behind.
    void sub_1DF60(RwReal arg_0);
    void sub_1BFB0(type_3DC048 *arg_0);
    // Follows the unk_8AC path, as sub_192D0 does: unless it is empty,
    // sets flag 16 when (with unk_32 and more than one node, flag 16 clear)
    // the path's last leg points against the owner's facing; drives along it
    // (sub_1B710, stopped for unk_4B0), logs arrival at a destination or
    // cover point from sub_2B740 (emptying the path), then aims at the
    // tracked entity as sub_1E210 does, or sub_1BFB0.
    void sub_1DB60(RwReal arg_0);
    // Follows the moving target of the unk_8AC path (its unk_50 handle; logs
    // "AStar_LostFollowTarget" and empties the path without one), logging
    // "AStar_TargetMoved" every 60 time units (unk_594) once it is over 1000
    // from the path's goal and the tracked entity's record is live. Drives
    // along the path (sub_1B710), logs arrival, then steers (sub_1BAA0)
    // towards the tracked entity's aim point (sub_1BEF0) or 1000 ahead, and
    // levels the owner's pitch by the difference sub_1BAA0 reports.
    void sub_1D620(RwReal arg_0);
    // State 23 of sub_172F0: drives with
    // sub_1B710 and, with flag 17 and a tracked entity sub_18DF0 accepts,
    // aims at it (sub_1C4F0), stopping first unless flag 20 or a vehicle-like
    // target says otherwise; without one, sub_1BFB0. Then keeps pace
    // (sub_1A630) or stops for unk_4B0.
    void sub_1E210(RwReal arg_0);
    // Chases the tracked entity (unk_1374) along the unk_8AC path: drops the
    // path when the entity is inside the owner's vf_258 range (flag 16
    // clear) or has moved over 1500 from unk_1380. While the path lasts,
    // drives along it (sub_1B710) unless the owner's vf_2A4 says it is busy
    // and the entity is beyond vf_254, dropping it when stopped for unk_4B0
    // with the goal behind, or on arrival (sub_2B740). Without a path it
    // re-plans (sub_1C880, in range mode when within vf_254) every 300 time
    // units, else turns towards the entity. Then aims at it (sub_1C4F0).
    void sub_1E530(RwReal arg_0);
    // Picks a point for arg_0 to go to near arg_4 by node searches (filter
    // kind 8, radius 1000) at the owner's height: with arg_8, back along the
    // line from arg_4 through arg_0 at twice, once and half its vf_254 range;
    // otherwise beyond arg_4 at twice that range, to either side of arg_4,
    // then to either side of arg_0 at 1.5 times it. Logs
    // "SetTaskCommand_GoToPoint" with the node found and returns 1, or 0.
    RwInt32 sub_1C880(type_3DC048 *arg_0, type_3D3548 *arg_4, RwInt32 arg_8);
    // Answers the player's "go go go": logs "PlayerDidGoGoGo" and, when
    // sub_1A1F0 allows, sets unk_1438 2000 units ahead of the owner along the
    // player's facing, then either attacks from a cover node or plans a path
    // (unk_B9C) to the player's point.
    void sub_1A2E0();
    // Sets arg_0's speed (vf_280) to keep pace with the unk_580 entity: within
    // 1.2 times unk_58C it scales or clamps the speed, beyond that it stops
    // when unk_D70 lies behind. Callers: sub_1B2B0 and sub_1E210.
    void sub_1A630(type_3DBC78 *arg_0, RwReal arg_4);
    // Plans the path arg_0 towards arg_4; sub_1A2E0 passes 5 and 500.0f and
    // tests the result. Only the widths of arg_8 and the result are known.
    RwInt32 sub_31240(type_154C0_5BC *arg_0, RwV3d *arg_4, RwInt32 arg_8, RwReal arg_C);
    // Works out, for the entity arg_4, the offset to arg_14 (unk_D70 when 0)
    // into *arg_8, a turn amount into *arg_C and a speed into *arg_10.
    // sub_1B2B0 tests the result against zero; only its width is known.
    RwInt32 sub_1A950(RwReal arg_0, type_3DBC78 *arg_4, RwV3d *arg_8, RwReal *arg_C,
                      RwReal *arg_10, RwV3d *arg_14);
    // Whether the node arg_0 suits the follow target (sub_24F30) from its
    // frame (sub_250D0) by sub_26000, which sets *arg_4 when the player is
    // near it (sub_190C0's reading); 0 without a target.
    RwInt32 sub_25DD0(type_F8350 *arg_0, RwInt32 *arg_4);
    // Called by sub_19780. sub_2DAA0 gets arg_0, unk_D88 and 0 and is tested
    // against zero; sub_19F90 gets the tracked entity. sub_2DAA0 follows the
    // spline unk_D14 (arg_4 the reach; arg_8 a second reach, a float).
    RwInt32 sub_2DAA0(RwReal arg_0, RwReal arg_4, RwReal arg_8);
    // Turns the owner's vf_1C8 object towards unk_D70 (sub_2F440 or sub_2E580)
    // or, failing that, the facing unk_DC4 by at most 6 degrees a unit of arg_0.
    void sub_2C220(RwReal arg_0);
    void sub_19F90(type_3D3548 *arg_0, RwReal arg_4);
    void sub_2E520(RwV3d *arg_0, RwReal arg_4);
    // Unless flag 15 is set, unk_59C is set, or unk_598 is clear with flag
    // 18 set: with unk_5A0, sub_2C220; otherwise, for an owner with a
    // vf_1C8 object, turns towards unk_D70 (horizontally; along the facing
    // when it is straight above or below) through sub_2F440 with the turn's
    // cosine against the right row and its heading in degrees (sub_13F9E0).
    // Returns whether unk_598 or unk_59C is set.
    RwInt32 sub_2D3A0();
    // Whether unk_598 or unk_59C is set: an inline with no address and so
    // no database name (sub_943E0 tests its materialised result).
    RwInt32 is_blocked()
    {
        return unk_598 != 0 || unk_59C != 0;
    }
    // Steers the owner's vf_1C8 object arg_0 (frame arg_4) while flag bit 5
    // of the owner's unk_28 is set: sub_2F440 under flag 18, and under flag
    // 0 towards the nearest of the object's followed entities or stored
    // directions (unk_2D4 / unk_54, records 0-2), turning at a signed rate
    // of 6 (scaled by flt_4275EC) or 12 unless arg_8 and arg_10's sign
    // allow the heading arg_14. The turn goes into the owner's unk_E8,
    // capped at the rate, scaled by 1 / arg_18; the heading comes back in
    // *arg_1C. Returns 1 when it turned, or unk_598 or unk_59C is set.
    RwInt32 sub_2E580(type_3DAFC8_1DDC *arg_0, RwMatrix *arg_4, RwV3d *arg_8, RwV3d *arg_C,
                      RwReal arg_10, RwReal arg_14, RwReal arg_18, RwReal *arg_1C);
    // Drives the vf_1C8 object arg_0 of the owner (frame matrix arg_4)
    // towards arg_8 along arg_C, with the two angles arg_10 and arg_14 and
    // the time step arg_18; two floats come back in *arg_1C and *arg_20.
    RwInt32 sub_2F440(type_3DAFC8_1DDC *arg_0, RwMatrix *arg_4, RwV3d *arg_8, RwV3d *arg_C,
                   RwReal arg_10, RwReal arg_14, RwReal arg_18, RwReal *arg_1C, RwReal *arg_20);
    // Casts a line from the owner towards unk_D70 (along unk_8AC's unk_08
    // when unk_DC0 is set), arg_8 long while unk_598 or unk_59C is set, else
    // arg_4, raised by the owner's height, through the dword_4E5D30 worlds
    // (sub_2C9B0). A blocking entity sets unk_59C under flag 25 (else
    // sub_30850(1)) and, with arg_0, logs "AStar_PathBlocked" and hands it to
    // sub_309E0; returns 1. A clear line undoes that ("AStar_PathUnBlocked")
    // and returns 0. With an empty path, returns whether unk_598 or unk_59C
    // is set. sub_19780 passes 1, 260, 300.
    RwInt32 sub_2CE90(RwInt32 arg_0, RwReal arg_4, RwReal arg_8);
    // Starts or stops (arg_0) avoiding a blocked path; only the width of
    // arg_0 is known.
    void sub_30850(RwInt32 arg_0);
    // Reacts to the entity arg_0 blocking the path.
    void sub_309E0(type_3D3548 *arg_0);
    // With flag 23: marks the path blocked (sub_30850(1)) unless it already
    // is, and unless unk_59C is set logs "AStar_PathBlocked" and makes arg_0
    // the blocking entity (sub_309E0). Without it, clears the block.
    void sub_308C0(type_3D3548 *arg_0);
    // With flag 23: clears the block unless it is clear and, unless unk_59C
    // is set, logs "AStar_PathUnBlocked". Without it, clears the block.
    void sub_30960();
    // Logs "MatchedOrientation" when sub_2D5C0 accepts arg_0; sub_172F0
    // passes unk_484 by value and its own float argument (state 30).
    void sub_1A190(RwV3d arg_0, RwReal arg_C);
    // State 20 of sub_172F0 (unk_484 by value and its float argument):
    // turns the owner towards arg_0, or towards the unk_580 entity under
    // flag 7 or 8, logging "MatchedOrientation" once facing it. arg_C is
    // unused.
    void sub_1CFE0(RwV3d arg_0, RwReal arg_C);
    // With unk_1430 at -1, flag 26 of unk_49C and unk_51C set, and none of
    // the flag 4 / flag 9 exclusions, asks the unk_574 object's vf_024 about
    // the owner; otherwise 0.
    RwInt32 sub_1A1F0();
    // Sets unk_1430 to arg_0. States 0-2 keep the rest; state 3 clears
    // unk_1434; any other value also zeroes unk_1438 and calls sub_23CD0(0, 1).
    void sub_1A5A0(RwInt32 arg_0);
    // Sets the cover-point search type unk_DD0 to arg_0 and returns 1. On a
    // change it clears unk_F70 and the unk_1324 / unk_1354 records, and when
    // arg_4 is set logs "CoverPointSearchTypeChanged" with the new type.
    RwInt32 sub_23CD0(RwInt32 arg_0, RwInt32 arg_4);
    // The point to head for: the unk_574 object's unk_5AC for a kind-5
    // object, else unk_1438 while unk_1430 is set; 0 when neither.
    RwInt32 sub_23C30(RwV3d *arg_0);
    // Picks the best unk_1048 search result for mode arg_0: in mode 1 the
    // one nearest the point to head for (sub_23C30) among those at least
    // 500 nearer to it than the owner is; in modes 0 and 2 the best score (kind
    // 0x11 nodes' scores scaled down first).
    void sub_23F60(RwInt32 arg_0);
    // Whether result arg_0 beats the best so far (*arg_C, reset to 1e37
    // when negative) while not under arg_8, keeping it in *arg_C: in mode 1
    // (arg_4) its node's squared distance from the point to head for, only
    // for nodes at least 500 nearer to it than the owner; else its score.
    RwInt32 sub_242B0(RwInt32 arg_0, RwInt32 arg_4, RwReal arg_8, RwReal *arg_C);
    // In modes 0 and 2 (arg_4; arg_0 is unused), unless the owner has kind
    // bits 7 or 18, finds the nearest usable vehicle cover record (flags
    // 0-1 set, 2 clear, within 5000, passing sub_205E0 under flag 13) of the
    // tracked entity (flag 22) or of the owner's side's entity list
    // (dword_4B8600). If it differs from unk_1324, unk_1354 and unk_130C
    // and, with unk_DD4, beats the node search's score, it plans a path to
    // it when unk_DD8 is set (setting *arg_C; arg_8 goes to sub_29780) and
    // on success makes it unk_1324 and returns 1.
    RwInt32 sub_24BA0(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 *arg_C);
    // Chooses a defend-area cover node: searches again (unk_1048, filter
    // kind arg_4, 25 results) around unk_13A8 under flag 13 or the owner
    // unless unk_DD4 is set and neither the tracked entity nor the owner has
    // moved over 600 from unk_F70, then sub_24BA0; with unk_DD4, results
    // (sub_242B0 against arg_8, sub_25890, not the current node) are tried
    // in turn until one is free and accepted (sub_26A80), keeping it in
    // unk_F54 (and *arg_0) or planning a path to it (sub_29630 with arg_C)
    // when unk_DD8 is set. Returns 1 when a node was taken.
    RwInt32 sub_244E0(type_F8350 **arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C);
    // The Distance Scheduler's AI-side range tests (sub_353A0): each is 1
    // when its target lies between the squared distances arg_0 and arg_4,
    // storing the distance in *arg_8. sub_21610 and sub_221E0 also take an
    // entity and a flag, sub_21790 a flag.
    RwBool sub_21610(RwReal arg_0, RwReal arg_4, RwReal *arg_8, type_3D3548 *arg_C,
                     RwInt32 arg_10);
    RwBool sub_21790(RwReal arg_0, RwReal arg_4, RwReal *arg_8, RwInt32 arg_C);
    RwBool sub_21910(RwReal arg_0, RwReal arg_4, RwReal *arg_8);
    RwBool sub_221E0(RwReal arg_0, RwReal arg_4, RwReal *arg_8, type_3D3548 *arg_C,
                     RwInt32 arg_10);
    // Another cover-node search taking sub_244E0's arguments (sub_34E60
    // passes 0, 0x10, 2 and the search id for cover-point search type 2):
    // around the follow target (sub_24F30; raised to its eye height, less
    // 50 when crouched), searching again unless it is within 600 of unk_F70,
    // then sub_24BA0; results must also suit the follow frame (sub_250D0,
    // sub_26000, sub_25B60), and a new node's path is planned in mode 6.
    RwInt32 sub_25180(type_F8350 **arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C);
    // 1 when the records match in unk_00, unk_04 and entity (sub_23E50), and
    // also lie within 500 of each other (sub_23EA0).
    RwInt32 sub_23E50(type_154C0_12F4 *arg_0, type_154C0_12F4 *arg_4);
    RwInt32 sub_23EA0(type_154C0_12F4 *arg_0, type_154C0_12F4 *arg_4);
    // The follow target: the unk_13E8 entity with its point, the direction
    // unk_13EC and mode unk_1404; or, under flag 13, the unk_13C0 entity
    // with unk_13A8 / unk_13D0 by unk_13DC. 0 when there is neither.
    RwInt32 sub_24F30(RwV3d *arg_0, type_3D3548 **arg_4, RwReal *arg_8, RwV3d *arg_C,
                      RwInt32 *arg_10);
    // Builds arg_0 at arg_4 facing arg_C, or facing away from arg_8
    // horizontally when arg_C is 0, zero-length or arg_10 is 3 (sub_140CE0).
    void sub_250D0(RwMatrix *arg_0, RwV3d *arg_4, RwV3d *arg_8, RwV3d *arg_C, RwInt32 arg_10);
    // Whether the node arg_0 beats the current node unk_F60 (1 without one):
    // 0 without a tracked entity (unk_1374) or when arg_0 lies back towards
    // unk_F60 as seen from the entity; else 1 when arg_0 is nearer the
    // entity, kind-0x11 nodes counting their squared distance at 0.0001.
    RwInt32 sub_25890(type_F8350 *arg_0);
    // Whether the node arg_0 is preferable to the current node unk_F60 from
    // the frame arg_4 (built by sub_250D0) in the follow mode arg_8 (from
    // sub_24F30): 1 without a current node, 0 for the current node itself.
    // Modes 0 and 1 weigh which of the two lie ahead (the dot of arg_4's at
    // row with each offset) and which is farther; mode 1 also takes a nearer
    // node when both lie behind; mode 2 only that; modes 3 and 4 the nearer
    // node; any other mode answers arg_C.
    RwInt32 sub_25B60(type_F8350 *arg_0, RwMatrix *arg_4, RwInt32 arg_8, RwInt32 arg_C);
    // Sets unk_528.
    void sub_26A30();
    // Passes the current node unk_F60, if any, to sub_266A0.
    void sub_26A50();
    // Places the owner at the cover node arg_0 (its frame detached and set
    // to the node's cover orientation and point; its motion cleared).
    void sub_266A0(type_F8350 *arg_0);
    // Turns towards the direction arg_0; arg_4 is a point (sub_2E520 passes
    // its target, sub_1A190 passes 0) and arg_8 a time step. sub_1A190
    // tests the result; only its width is known.
    RwInt32 sub_2D5C0(RwV3d *arg_0, RwV3d *arg_4, RwReal arg_8);
    // Stores arg_0 at +0x5A4 and returns 1; arg_0 is only known by width.
    RwInt32 sub_29380(RwInt32 arg_0);
    // 1 when sub_23BE0 finds a cover point and sub_28890 accepts it for
    // arg_0.
    RwBool sub_28840(type_3D3548 *arg_0);
    // With a free node (sub_27CC0), moves and orients the owner to the
    // unk_F54 node (vf_0C0, vf_0D4) and makes it current; 1 then, else 0.
    RwInt32 sub_27E30();
    // Searches the nodes within 50 of the owner (unk_1048, filter kind 4)
    // and keeps the best in unk_F54 when it is free and usable; 1 then (and
    // *arg_0, when given, gets unk_F54 if it was already that node).
    RwInt32 sub_27CC0(type_F8350 **arg_0);
    // The node to head for along the facing arg_4 (arg_0 is unused): of the
    // nodes found around unk_13A8 within unk_13B4 (under flag 13) or around
    // the owner within 1500, those farther than half that range (250000
    // squared without the flag) from the search centre; the nearest one the
    // owner sees ahead (dot over 0.55), else the nearest at all. Returns its
    // point (unk_10), or 0.
    RwV3d *sub_27EB0(RwV3d *arg_0, RwV3d *arg_4);
    // Of the last search's results, takes the nearest free usable node that
    // sub_28200 accepts for arg_0 as the target (unk_5B0); 1 then.
    RwInt32 sub_28640(RwInt32 arg_0);
    // Whether the cover node arg_4 faces the point arg_0 (a RwV3d's address,
    // passed as an integer): its orientation's at row against the direction
    // to the point, dot over 0.2.
    RwInt32 sub_28200(RwInt32 arg_0, type_F8350 *arg_4);
    // Sets unk_70 unless the action unk_5C is 1 or 0x18.
    void sub_28F00();
    // Clears unk_A24's node count (unk_64.unk_2C).
    void sub_29360();
    // The heading to its path point, in radians ("GetLocalYawAngleToPathPoint"):
    // the flat offset to unk_D70 in the owner's frame, through sub_2C1E0.
    RwReal sub_2C040();
    // Plans the path arg_0 with the options arg_4 to arg_2C; returns a
    // result code (-1 on failure, as its callers treat it). Only the widths
    // of the integer options are known.
    RwInt32 sub_29940(type_154C0_5BC *arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C,
                      type_3D3548 *arg_10, type_F8350 *arg_14, RwInt32 arg_18, RwInt32 arg_1C,
                      RwInt32 arg_20, RwInt32 arg_24, RwReal arg_28, RwInt32 arg_2C);
    // Fills the path arg_20 from the owner to the entity arg_0 (or to what
    // its vf_00C entity's vf_200 gives, for kind bit 4) and plans it.
    RwInt32 sub_29410(type_3D3548 *arg_0, RwReal arg_4, RwInt32 arg_8, RwInt32 arg_C,
                      RwInt32 arg_10, RwInt32 arg_14, RwInt32 arg_18, RwInt32 arg_1C,
                      type_154C0_5BC *arg_20, RwInt32 arg_24, RwInt32 arg_28, RwInt32 arg_2C,
                      RwReal arg_30, RwInt32 arg_34);
    // Points unk_580 at arg_0 and plans the path unk_5BC to it (sub_29410).
    RwInt32 sub_293A0(type_3D3548 *arg_0, RwReal arg_4, RwInt32 arg_8, RwInt32 arg_C,
                      RwInt32 arg_10, RwInt32 arg_14, RwInt32 arg_18, RwInt32 arg_1C,
                      RwInt32 arg_20, RwInt32 arg_24, RwInt32 arg_28, RwReal arg_2C,
                      RwInt32 arg_30);
    // Plan to the unk_580 entity (sub_28B50), the tracked entity into unk_A24
    // (sub_28C60) or unk_5B0 into unk_5BC / unk_734 (sub_28D80), with
    // options chosen by arg_0; log "AStar_PathNotFound" on failure.
    RwInt32 sub_28B50(RwInt32 arg_0, RwReal arg_4, RwInt32 arg_8);
    // Searches the nodes within 1000 of the owner for the nearest one over
    // 700 from arg_0 that is nearer the owner than arg_0; on success copies
    // its point into unk_5B0 and returns 1.
    RwInt32 sub_28470(RwV3d *arg_0);
    RwInt32 sub_28C60(RwInt32 arg_0, RwReal arg_4, RwInt32 arg_8);
    RwInt32 sub_28D80(RwInt32 arg_0, RwReal arg_4, RwInt32 arg_8);
    // Fill the path arg_1C from the owner's position to the node unk_5A8
    // (sub_29540) or to unk_5B0 (sub_29870) with the radius arg_0 and
    // options arg_4..arg_10, then plan it (sub_29940).
    RwInt32 sub_29540(RwReal arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C, RwInt32 arg_10,
                      RwInt32 arg_14, RwInt32 arg_18, type_154C0_5BC *arg_1C, RwInt32 arg_20,
                      RwInt32 arg_24, RwInt32 arg_28, RwReal arg_2C, RwInt32 arg_30);
    RwInt32 sub_29870(RwReal arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C, RwInt32 arg_10,
                      RwInt32 arg_14, RwInt32 arg_18, type_154C0_5BC *arg_1C, RwInt32 arg_20,
                      RwInt32 arg_24, RwInt32 arg_28, RwReal arg_2C, RwInt32 arg_30);
    // Plans the path unk_117C to the vehicle cover point arg_0 refers to.
    RwInt32 sub_29780(type_154C0_12F4 *arg_0, RwInt32 arg_4, RwInt32 arg_8);
    // Stores arg_0 at +0x136C; when it is 0, clears unk_1324 through
    // sub_23D90. arg_0 is only known by width.
    void sub_22F30(RwInt32 arg_0);
    // Resets one type_154C0_12F4 record.
    void sub_23D90(type_154C0_12F4 *arg_0);
    // The unk_1444 record with id arg_0 whose point is within 300 of arg_4
    // across and 200 in height (flt_4275DC, flt_4275E0), or 0.
    // Whether arg_4 can be seen from the node arg_0: the answer cached for
    // the node (sub_22690), else a line test (sub_D2FC0) from the node's
    // offset point (sub_F8FE0, placed by the node's orientation) to the
    // point arg_4 gives (its vf_110), cached by sub_22780. 0 without an
    // entity or for an owner with flag bit 1.
    RwInt32 sub_22370(type_F8350 *arg_0, type_3D3548 *arg_4);
    type_154C0_1444 *sub_22690(type_F8350 *arg_0, RwV3d *arg_4);
    // Records the node arg_0 at arg_4 (with arg_8) in an unk_1444 slot: the
    // first slot not holding the current node unk_F60, preferring one that
    // does not hold unk_F54; the current node's own slot if it is arg_0.
    void sub_22780(type_F8350 *arg_0, RwV3d *arg_4, RwInt32 arg_8);
    // Whether the node arg_0 suits a direction: kind 14 always; kinds 5, 9,
    // 11-13, 17 and 19 when the matrix arg_4's at row is within
    // (-0.4, 0.4) of arg_8; otherwise by which side of arg_4 arg_C lies
    // for kinds 3 and 4, unless the at row dots arg_8 below 0.3.
    RwInt32 sub_25EB0(type_F8350 *arg_0, RwMatrix *arg_4, RwV3d *arg_8, RwV3d *arg_C);
    // Whether the cover node arg_0 suits the frame arg_4 (the owner's)
    // against the point arg_8 within range arg_10, in mode arg_14: it must
    // pass sub_23A10 (or be kind 0x0E), sub_26A80 for the tracked entity or,
    // without one, not be near the player on the owner's side (then *arg_18
    // is set), lie within the height band and range of arg_8, and face the
    // way the mode asks: modes 0 to 2 through sub_25EB0 by the facing,
    // mode 3 by the node's orientation against the frame's rows, mode 4 by
    // distance alone. arg_C is unused.
    RwInt32 sub_26000(type_F8350 *arg_0, RwMatrix *arg_4, RwV3d *arg_8, RwInt32 arg_C,
                      RwReal arg_10, RwInt32 arg_14, RwInt32 *arg_18);
    // The record arg_0 refers to (through sub_155340), after checking its
    // flags and entity.
    type_14D180 *sub_23050(type_154C0_12F4 *arg_0);
    // Moves to the next path node: releases unk_F60 (sub_F7BA0), makes
    // unk_F5C current and registers it, and for a kind-0x11 node points the
    // owner's unk_618 at the node's entity (sub_16A380, sub_13F4D0).
    void sub_22F70();
    // Releases unk_12F4, shifts unk_12F4 into unk_130C and unk_133C into
    // unk_12F4, claims the new unk_12F4 and resets unk_133C.
    void sub_231B0();
    // Copies the record arg_4 into arg_0.
    void sub_23DF0(type_154C0_12F4 *arg_0, type_154C0_12F4 *arg_4);
    // Passes unk_133C and unk_1324 to sub_23DF0.
    void sub_23760();
    // unk_1324, when sub_279B0 finds a record for it and the tracked entity;
    // else 0.
    type_154C0_12F4 *sub_23BE0();
    // With a free vehicle cover point (sub_23BE0; flag bits 0 and 1 set, 2
    // clear), keeps it (sub_23760), clears the node target (sub_22EF0) and
    // logs "VehicleCoverPointFound".
    void sub_23230();
    // The entity of the unk_12F4 record's handle.
    type_3D3548 *sub_232F0();
    // With a free unk_F54 node that sub_25DD0 accepts, takes it (sub_23670),
    // clears the node target and logs "DefendAreaCoverPointFound".
    void sub_23320();
    // Sets unk_F54.
    void sub_23530(type_F8350 *arg_0);
    // Copies unk_1354 into unk_1324 when arg_0 is 0, else resets unk_1324.
    // arg_0 is only known by width.
    void sub_23550(RwInt32 arg_0);
    // Like sub_22F70, but makes unk_F64 the current node and clears it.
    void sub_235A0();
    // Leaves the current node unk_F60 (remembered in unk_F58) and sets the
    // wait unk_1398 by its kind: 120 for 0x11, 0 for 0x0E, 21600 for 0x13,
    // else 480.
    void sub_23790();
    // Releases unk_12F4 into unk_130C and resets it.
    void sub_23860();
    // The record unk_12F4 refers to, when unk_578 is 0x23, 0x24 or 0x25 and
    // the record's flag bits 0 and 1 are set; else 0.
    type_14D180 *sub_23980();
    // 0 for nodes of kind 7, 8 or 14. For an owner whose vf_008 entity is
    // in mode 3, 1 only for kinds 12, 13, 19, or 3, 4, 5, 9 with flag 8, or
    // 5, 9 with flag 9 (0 with flag 6); for any other owner, 1.
    RwInt32 sub_23A10(type_F8350 *arg_0);
    // Whether the cover node arg_0 (sub_23A10 must accept it) shields a
    // spot from arg_8 for arg_4: the node's facing (the at row of its
    // orientation unk_1C) points at arg_4 at least as much as sub_27500
    // requires and arg_4 is over 500 away; then 1 unless one of the 32
    // unk_80 entities on the other side (cmp_unk_2C) within 10000 is behind
    // the node nearer than arg_8, or in front of it within 500.
    RwInt32 sub_27550(type_F8350 *arg_0, RwV3d *arg_4, RwV3d *arg_8);
    // Whether the current node unk_F60 faces arg_0 at least as much as
    // sub_27500 requires (the at row of its orientation, dotted with the
    // offset to arg_0 unnormalised); 0 without a node or arg_0.
    RwInt32 sub_27370(type_3D3548 *arg_0);
    // Registers an A* search of type arg_0 for the owner (sub_32F70 with
    // arg_8) and returns its id; 0 for types 0 and 4. Types 2, 3 and 5 need
    // a target arg_4 (kept in unk_580; otherwise a warning is printed and 0
    // returned); type 11 registers as type 6 towards the spline point
    // unk_1418 (copied into unk_5B0). arg_C is unused.
    // With a kind-6 unk_574 object (type_3CE278) that has a node, makes the
    // node's point the target unk_5B0 and returns 1; else 0.
    RwInt32 sub_28780();
    // Occupies the selected defend-area cover node (unk_F54, which must be
    // the found node unk_F5C, free, and accepted by sub_25DD0) through
    // sub_F7BA0 and returns 1; otherwise reports why (sub_6B060) and
    // returns 0.
    RwInt32 sub_233B0();
    // With unk_54C set, flag 4 and unk_558 not positive: 1 when the group's
    // unk_04.unk_29C is over 900 (which it then zeroes), else 2; clears
    // unk_54C and unk_554. Otherwise 0.
    RwInt32 sub_22110();
    RwInt32 sub_28A60(RwInt32 arg_0, type_3D3548 *arg_4, RwReal arg_8, RwInt32 arg_C);
    // Plans the path unk_DDC from the owner to the node arg_0 (sub_29940
    // with arg_4, arg_C and arg_10; arg_8 goes into the path's unk_60). The
    // arrival range is 100, or for a kind-0x11 node the reach sub_6D0A0
    // gives for the owner's vf_008 object's unk_3E0 class.
    RwInt32 sub_29630(type_F8350 *arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C,
                      RwInt32 arg_10);
    // Finds the record for the cover point arg_0 and the entity arg_4 (or
    // checks arg_8); returns it or 0.
    type_14D180 *sub_279B0(type_154C0_12F4 *arg_0, type_3D3548 *arg_4, type_14D180 *arg_8);
    // With a planned unk_A24 path (sub_19ED0), finds where it leaves the
    // sphere of radius unk_13B4 - 100 around unk_13A8: walking its nodes from
    // the last, the first one beyond the radius and the one after it. With
    // only a near node, that node's point; with both, the point where the
    // segment between them crosses the sphere (RaySphereIntersect). 0 when
    // there is no such point; else whether sub_42210 accepts it, raised by
    // twice the owner's height, against the unk_1374 entity's vf_110 point.
    RwInt32 sub_228A0();
    // Whether the cover point arg_4 serves against entity arg_0: the owner
    // faces it (dot over 0.3) or is within 250 of it, and its facing (unk_20)
    // points towards arg_0 (dot over 0.3).
    RwInt32 sub_28890(type_3D3548 *arg_0, type_154C0_12F4 *arg_4);
    // Picks the next node to move to around the tracked entity (unk_1374):
    // unless both it and the owner are within 300 of where they were at the
    // last search, searches again (unk_1114, filter kind 9, radius the
    // owner's vf_114) and shuffles the first five results. Then takes the
    // next result (unk_1174) whose point passes sub_205E0 under flag 13, or
    // once they run out the search's fallback node; its point goes to
    // unk_5B0 and the result is 1, else 0.
    RwInt32 sub_28F30();
    // 1 when unk_578 is 6, 0x26 or 0x2A and there is a current node; its
    // argument is unused.
    RwBool sub_238E0(type_3D3548 *arg_0);
    // Sets the nearest blocker on the way to the target (unk_139C) and
    // unk_534 to whether it is beyond 0.9: an inline with no address
    // and so no database name, named for its field. Evidence: the soldier's
    // vf_134 stores its float argument through a parameter slot and a copy
    // of `this`, then a 1/0 temporary; sub_18BB0 expands it with 0.
    void set_unk_139C(RwReal arg_0)
    {
        unk_139C = arg_0;
        unk_534 = arg_0 > 0.9f;
    }
    // 1 when unk_578 is 5, 0x2B or 0x2C and there is a current node.
    RwBool sub_23930();
    // Whether the node arg_0 suits the attack on arg_4: facing it, clear of
    // the 32 unk_80 entities on the other side, and (without arg_8) passing
    // sub_22370; without arg_4, the node must face the point sub_23C30 gives.
    // *arg_C (optional) is set when the player stands on the node.
    RwInt32 sub_26A80(type_F8350 *arg_0, type_3D3548 *arg_4, RwInt32 arg_8, RwInt32 *arg_C);

    // An inline accessor for unk_13B4, with no address and so no database
    // name; it is named for the field it returns. Evidence for its shape:
    // sub_27EB0 reads +0x13B4 twice, each time into its own compiler
    // temporary in the slots just above `this`, which is what an inline
    // function holding its result in a local expands to (docs/toolchain.md).
    RwReal get_unk_13B4()
    {
        RwReal r = unk_13B4;
        return r;
    }

    // An inline setter for unk_5B0, likewise nameless in the database and
    // named for its field. Evidence for its shape: sub_21C90 computes the
    // source point's address (a call result plus 0x604) into a compiler
    // temporary just above `this`, then copies through it into this + 0x5B0,
    // which is an inline member's argument copy.
    void set_unk_5B0(RwV3d *arg_0)
    {
        unk_5B0 = *arg_0;
    }

    // Inline accessors for unk_DD4, unk_DBC and unk_DC0, likewise nameless
    // and named for their fields. Evidence: sub_244E0 (unk_DD4, twice),
    // sub_2CE90 and sub_2C9B0 read each into a compiler temporary (just above
    // `this`, or among sub_2C9B0's temporaries) and test it there.
    // Inline accessor for unk_5A4, likewise nameless in the database and
    // named for its field. Evidence: sub_332D0 tests it through a compiler
    // temporary.
    RwInt32 get_unk_5A4()
    {
        RwInt32 r = unk_5A4;
        return r;
    }
    RwInt32 get_unk_DD4()
    {
        RwInt32 r = unk_DD4;
        return r;
    }
    RwInt32 get_unk_DBC()
    {
        RwInt32 r = unk_DBC;
        return r;
    }
    RwInt32 get_unk_DC0()
    {
        RwInt32 r = unk_DC0;
        return r;
    }

    // Inline accessors for unk_578, unk_57C, unk_F54, unk_F60 and unk_1178,
    // likewise nameless and named for their fields. Evidence:
    // type_3CE4B4::sub_33820 reads each (unk_57C and unk_F54 several times)
    // into its own compiler temporary among the ones above `this`.
    // Likewise for unk_DD0 (sub_34E60 tests it through a temporary).
    // The unk_13E8 entity (sub_D4910), likewise nameless and named for the
    // field. Evidence: the Distance Scheduler's sub_353A0 computes it into a
    // compiler temporary before pushing any other argument of the call it
    // is passed to, where a direct sub_D4910 call is evaluated in turn.
    type_3D3548 *get_unk_13E8()
    {
        type_3D3548 *r = unk_13E8.sub_D4910();
        return r;
    }
    // An inline accessor for unk_56C and an inline setter for unk_7C,
    // likewise nameless and named for their fields. Evidence:
    // type_3CE5E8::vf_00C holds each vf_120() result it calls them on in a
    // temporary of its own (the inline's `this`), and unk_56C's value in
    // another before calling on it.
    // Likewise for unk_520 and unk_7C (type_3CE5E8::vf_018 tests each
    // through a temporary).
    RwInt32 get_unk_520()
    {
        return unk_520;
    }
    RwReal get_unk_7C()
    {
        return unk_7C;
    }
    // Likewise for unk_574 and unk_DD8 (type_3CE5E8's sub_3A170 and vf_014
    // hold the vf_120() result they call these on in a temporary).
    RwUInt32 get_unk_574()
    {
        return unk_574;
    }
    // The same as a handle (the squad's removal, type_3DF30::sub_3E3B0,
    // numbers its temporary with the other handle getters').
    type_365A0 get_unk_574_h()
    {
        return unk_574_h;
    }
    void set_unk_DD8(RwInt32 arg_0)
    {
        unk_DD8 = arg_0;
    }
    // Whether there is an order (unk_1430 set), and dropping it
    // (sub_1A5A0(-1)): inline members with no address and so no database
    // names; named for the field. Evidence: type_3CE5E8::sub_3B7E0 keeps the
    // vf_120() result it calls each on in a temporary of its own.
    RwBool has_unk_1430()
    {
        return unk_1430 != -1;
    }
    void clear_unk_1430()
    {
        sub_1A5A0(-1);
    }
    type_3DF30 *get_unk_56C()
    {
        return unk_56C;
    }
    void set_unk_7C(RwReal arg_0)
    {
        unk_7C = arg_0;
    }
    RwInt32 get_unk_DD0()
    {
        RwInt32 r = unk_DD0;
        return r;
    }
    RwInt32 get_unk_578()
    {
        return unk_578;
    }
    RwReal get_unk_57C()
    {
        RwReal r = unk_57C;
        return r;
    }
    // An inline accessor for unk_5B0's address, likewise nameless and named
    // for its field. Evidence: "GotoPointUsingRegistration" (sub_48DA0) keeps
    // the AI object in a compiler temporary each time it takes the point
    // (an inline member's `this`), where a direct member access would not.
    RwV3d *get_unk_5B0()
    {
        return &unk_5B0;
    }
    type_F8350 *get_unk_F54()
    {
        type_F8350 *r = unk_F54;
        return r;
    }
    // The cover point's position and orientation for the node arg_0 into
    // *arg_4 and *arg_8 ("PlayCoverPointRegistrationPerformance",
    // sub_46C80): the node's orientation turned half round and then by the
    // y of its offset (sub_F8FE0), its at vector, and the node's point.
    void sub_22C80(type_F8350 *arg_0, RwV3d *arg_4, RwV3d *arg_8);
    // Unlike the others it has no result local: "SnapToCover" (sub_46D60)
    // assigns it straight into its own local, where a local would be copied.
    type_F8350 *get_unk_F60()
    {
        return unk_F60;
    }
    RwReal get_unk_1178()
    {
        RwReal r = unk_1178;
        return r;
    }
    // The tracked entity (unk_1374) and how long it has been tracked
    // (unk_1378): inline accessors, likewise nameless and named for their
    // fields. Evidence: the target scores (sub_401B0, sub_403F0) keep each
    // vf_120() result they call these on in a temporary of its own, and
    // unk_1378's value in another.
    // Sets the spline's end, as type_3DA6C0::set_unk_444 (the clamp's
    // result dropped); likewise nameless and named for its field.
    void set_unk_D1C(RwReal arg_0)
    {
        unk_D1C = arg_0;
        sub_22C20(unk_D1C, 0.0f, 1.0f);
    }
    // An inline accessor for unk_136C, likewise nameless and named for its
    // field. Evidence: "GetVehicleCoverPointSearch" reads it through a local
    // placed after every check's.
    RwInt32 get_unk_136C()
    {
        RwInt32 r = unk_136C;
        return r;
    }
    // Whether the defend area selected is better
    // ("IsDefendAreaSelectedBetter"): the found node unk_F5C, when it is not
    // the current node unk_F60, beats it from the follow frame (sub_24F30,
    // sub_250D0, sub_25B60 answering 0 for modes it does not weigh).
    RwInt32 sub_25A50();
    // Sets unk_74: an inline setter, likewise nameless and named for its
    // field. Evidence: "SetAttackStandHoldCount" stores through a temporary
    // holding the vf_120 result, placed after the checks' locals.
    void set_unk_74(RwReal arg_0)
    {
        unk_74 = arg_0;
    }
    // An inline accessor for unk_D18, likewise nameless and named for its
    // field. Evidence: "GetSplinePositionFromName" reads it through a local
    // placed after every check's.
    RwReal get_unk_D18()
    {
        RwReal r = unk_D18;
        return r;
    }
    // An inline accessor for unk_D14, likewise nameless and named for its
    // field. Evidence: "HasDefaultSplinePath" tests it through a local
    // placed after every check's (an inline's result local).
    SplinePath *get_unk_D14()
    {
        SplinePath *r = unk_D14;
        return r;
    }
    // Likewise for unk_D20: type_3D3548's vf_128 returns it through a
    // temporary of its own (the result local), after unk_D14's.
    RwReal get_unk_D20()
    {
        RwReal r = unk_D20;
        return r;
    }
    type_3D3548 *get_unk_1374()
    {
        return unk_1374.sub_D4910();
    }
    RwReal get_unk_1378()
    {
        return unk_1378;
    }
    // Likewise for unk_1394 ("ShouldIDoTheAssaultWalk", sub_49AF0, compares
    // the player's through a temporary).
    RwReal get_unk_1394()
    {
        return unk_1394;
    }
    // An inline accessor for unk_5A0 with a result local, likewise nameless
    // and named for its field. Evidence: "IsPathBlockedWhileStrafing" copies
    // it through a compiler temporary allocated after its unused slots.
    RwInt32 get_unk_5A0()
    {
        RwInt32 r = unk_5A0;
        return r;
    }
    // Likewise for unk_1430 and unk_1434 ("FoundPointPathForGoGoGo",
    // "DidIJustGoGoGo" test them through temporaries).
    RwInt32 get_unk_1430()
    {
        return unk_1430;
    }
    RwReal get_unk_1434()
    {
        return unk_1434;
    }
};

#endif
