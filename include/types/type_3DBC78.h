/*
 * type_3DBC78: the entity class the AI action handlers take, derived from
 * type_3D3548 and anchored at its vtable off_3DBC78 (192 slots, +0x000 to
 * +0x2FC), which sub_14C930, sub_14CF20 and sub_1555A0 install. Its vtable
 * adds the slots from +0x234 on; the handlers call vf_2DC, which only this
 * family has. type_3DC048 and off_3DC378 derive from it.
 *
 * Fields: +0xDC0 and +0x1170 lie past type_3D3548's end (at most 0x3E0), so
 * they belong to this class. Where type_3D3548 ends inside unk_388 is not
 * known.
 */
#ifndef TYPE_3DBC78_H
#define TYPE_3DBC78_H

#include "rw/ostypes.h"
#include "types/type_3D3548.h"
#include "types/type_14D180.h"
#include "types/type_154C0_12F4.h"
#include "types/type_3DBC78_450.h"
#include "types/type_D48D0.h"
#include "types/type_129_base.h"
#include "types/type_15B110.h"
#include "types/AIData.h"
#include "rw/rtquat.h"

struct type_10F710;
struct type_712B0;

// type_3DBC78::unk_3D4 (built by sub_14D000; nothing to take down): keys
// of sound aliases, among them the player's getting in (unk_30, vf_268) and
// out (unk_38, vf_270).
// A track: its material and its UV animation's time (vf_2B4 advances it,
// vf_054 applies it).
struct type_3DBC78_B10
{
    struct RpMaterial *unk_00;
    RwReal unk_04;
};

// A record sub_153C40 sets up for a tank (type_3DC048).
struct type_153C40
{
    RwInt32 unk_00;
    RwInt32 unk_04;
    RwV3d unk_08;
};

// The pose its procedural track builds (the interpolator's +0x144): the
// node count behind unk_04, then each node's rotation and, after them, its
// translation (a vector in a 16-byte record).
struct type_153890
{
    RwUInt8 unk_00[0x4];
    RwUInt8 *unk_04;
    RwUInt8 unk_08[0x8];
    RtQuat unk_10[1];
};

// The kind-0x27 object's data (its unk_10) as the vehicle's set-up
// (sub_14D2C0) reads it: its sounds' keys (type_14D000, through unk_00),
// its kind (0 and 2 give the vehicle flags 0x82, 1, 3 and 4 0x81), its kind
// for the HUD and its display name.
struct type_14D2C0_00
{
    RwUInt8 unk_00[0x10];
    struct type_14D000 *unk_10;
};
// A gun's model record in the vehicle's data (the guns' set-up,
// type_15B110::sub_15B2A0, takes its model object's clump by it).
struct type_14D2C0_0C
{
    RwInt32 unk_00;
    type_3DF8D8_04 unk_04;
};
struct type_14D2C0_10
{
    type_14D2C0_00 *unk_00;
    RwUInt8 unk_04[0x8];
    type_14D2C0_0C unk_0C[4];   // the guns' projectile models
    RwReal unk_3C[4];           // their projectiles' speeds
    RwInt32 unk_4C[4][2];       // their particle systems
    RwReal unk_6C[4];           // (times 60, the guns' unk_1C)
    RwInt32 unk_7C[4];          // their magazines
    RwInt32 unk_8C;
    RwInt32 unk_90;
    RwUInt8 unk_94[0x4];
    const RwChar *unk_98;

    // Inline accessors for the guns' settings, each through a local of its
    // own (docs/toolchain.md): the guns' set-up copies every one through a
    // temporary, and indexes unk_4C by a constant it still shifts at run
    // time (an inline's argument).
    RwInt32 get_unk_4C(RwInt32 arg_0, RwInt32 arg_4)
    {
        RwInt32 r = unk_4C[arg_0][arg_4];
        return r;
    }
    RwReal get_unk_3C(RwInt32 arg_0)
    {
        RwReal r = unk_3C[arg_0];
        return r;
    }
    RwReal get_unk_6C(RwInt32 arg_0)
    {
        RwReal r = unk_6C[arg_0];
        return r;
    }
    RwInt32 get_unk_7C(RwInt32 arg_0)
    {
        RwInt32 r = unk_7C[arg_0];
        return r;
    }
    // An inline accessor for unk_90, through a local of its own
    // (docs/toolchain.md): the tank's set-up (sub_155780) copies it
    // through a temporary taken after its named locals.
    RwInt32 get_unk_90()
    {
        RwInt32 r = unk_90;
        return r;
    }

    // An inline accessor for unk_8C, with no address and so no database
    // name. Evidence: the set-up switches on it through a temporary first
    // loaded from the slot of an inline's result (docs/toolchain.md).
    RwInt32 get_unk_8C()
    {
        return unk_8C;
    }
};

// A gun's projectile model record, through a free inline: the guns' set-up
// (sub_15B2A0) loads the index before the data (the arguments evaluate right
// to left).
inline type_14D2C0_0C *get_gun_model(type_14D2C0_10 *arg_0, RwInt32 arg_4)
{
    return &arg_0->unk_0C[arg_4];
}

struct type_14D000
{
    type_3DF8D8_04 unk_00;
    type_3DF8D8_04 unk_08;
    type_3DF8D8_04 unk_10;
    type_3DF8D8_04 unk_18;
    type_3DF8D8_04 unk_20;
    type_3DF8D8_04 unk_28;
    type_3DF8D8_04 unk_30;
    type_3DF8D8_04 unk_38;
    type_3DF8D8_04 unk_40;
    type_3DF8D8_04 unk_48;
    type_3DF8D8_04 unk_50;
    type_3DF8D8_04 unk_58[4];

    // Defined here: VC7.1 does not inline it (sub_14D000 is called), but
    // the vehicle's constructor still reserves its expansion's temporaries.
    type_14D000()
    {
    }
};

struct type_3DBC78 : type_3D3548
{
    // The base's slots it overrides with accessors of its own (sub_14CA50
    // to sub_14CEF0) and its take-down (vf_230, sub_14ED60).
    virtual void vf_230();
    virtual void vf_220(type_3D3548 *arg_0, RwInt32 arg_4);
    virtual void vf_038(RwReal arg_0);
    virtual void vf_1D0();
    // +0x058: sub_17F550 (a later unit; only the width is known).
    virtual RwInt32 vf_058(struct type_3DF8D8_04 *arg_0);
    // +0x044: empty (folded, /OPT:ICF, into sub_15FB30).
    virtual void vf_044(RwReal arg_0);
    // +0x040: its move by the step arg_0: by its animation (bone unk_B2C,
    // its body following) while one plays, else by its physics, the
    // physics frame then placing it; then its shadow.
    virtual void vf_040(RwReal arg_0);
    // +0x04C: its step: the base's, its sounds (vf_2B8), its aim point
    // (unk_117C, led by its facing), the scan (vf_2D0), the gun it mounts
    // (unk_1190) at its tag, its AI, and a player riding its turret.
    virtual void vf_04C(RwReal arg_0);
    virtual struct type_6D380 *vf_090();
    virtual type_3D2E7C *vf_098();
    virtual void vf_054(RwInt32 arg_0);
    virtual void vf_0EC(RwInt32 arg_0, RwInt32 arg_4);
    virtual void vf_170(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C);
    virtual void vf_03C(RwReal arg_0);
    virtual RwInt32 vf_060(type_3D3548 *arg_0);
    virtual RwInt32 vf_064(struct type_75600 *arg_0);
    virtual RwInt32 vf_068(struct type_758F0 *arg_0);
    virtual RwInt32 vf_06C(type_3D3548 *arg_0);
    virtual void vf_0C0(RwV3d *arg_0);
    virtual RwV3d *vf_0C8();
    virtual void vf_0D0(RwV3d *arg_0);
    virtual void vf_0D4(RtQuat *arg_0);
    virtual void vf_0D8(RwV3d *arg_0);
    virtual RwReal vf_0FC();
    virtual RwReal vf_100();
    virtual void vf_104(RwMatrix *arg_0);
    virtual void vf_108(RwV3d *arg_0);
    virtual RwReal vf_10C();
    virtual void vf_110(RwV3d *arg_0, type_3D3548 *arg_4, RwInt32 arg_8);
    virtual RwReal vf_114();
    virtual RwInt32 vf_16C(RwInt32 arg_0, RwInt32 arg_4);
    virtual void vf_234();
    // Inline: the constructor's vtable emits them after it, before ??_G (the image's order).
    virtual void vf_094(RwUInt32 arg_0)
    {
        unk_1128 = arg_0;
    }
    virtual RwReal vf_238()
    {
        return unk_1164;
    }
    // +0x23C: its vision multiplier, and +0x244 a flag, the script
    // command's second argument ("SetVisionMultiplier"; the soldier's
    // counterpart, type_3DAFC8::vf_240, tests it as an integer).
    // Inline: the constructor's vtable emits them after it, before ??_G (the image's order).
    virtual void vf_23C(RwReal arg_0)
    {
        unk_1164 = arg_0;
    }
    // Inline: the constructor's vtable emits them after it, before ??_G (the image's order).
    virtual RwInt32 vf_240()
    {
        return unk_1158;
    }
    // Inline: the constructor's vtable emits them after it, before ??_G (the image's order).
    virtual void vf_244(RwInt32 arg_0)
    {
        unk_1158 = arg_0;
    }
    // +0x248: the vehicle's death task ("VehicleGetDeathTask").
    // Inline: the constructor's vtable emits them after it, before ??_G (the image's order).
    virtual RwInt32 vf_248()
    {
        return unk_2620;
    }
    // Inline: the constructor's vtable emits them after it, before ??_G (the image's order).
    virtual RwInt32 vf_174()
    {
        return unk_2624;
    }
    virtual void vf_178(RwInt32 arg_0)
    {
        unk_2624 = arg_0;
    }
    virtual void vf_180(RwInt32 arg_0)
    {
        unk_2624 += arg_0;
        if (unk_2624 > unk_2628)
            unk_2624 = unk_2628;
    }
    virtual RwInt32 vf_0DC()
    {
        return unk_DB0;
    }
    virtual RwReal vf_17C()
    {
        return (RwReal)unk_2624 / unk_2628;
    }
    virtual RwInt32 vf_24C()
    {
        return unk_262C;
    }
    // Inline: the constructor's vtable emits them after it, before ??_G (the image's order).
    virtual RwReal vf_250()
    {
        return (RwReal)unk_262C / unk_2630;
    }
    // +0x254: its unk_116C (sub_14CC60); AIData::sub_1E530 compares it with
    // the distance to the tracked entity.
    // Inline: the constructor's vtable emits them after it, before ??_G (the image's order).
    virtual RwReal vf_164()
    {
        return unk_1174;
    }
    virtual RwReal vf_168()
    {
        return unk_1178;
    }
    virtual RwReal vf_254()
    {
        return unk_116C;
    }

    // +0x258: its unk_1170 (sub_14CC80); sub_152A0 scales it by 1.5.
    // Inline: the constructor's vtable emits them after it, before ??_G (the image's order).
    virtual RwReal vf_258()
    {
        return unk_1170;
    }
    // +0x25C: its +0x1140 dword (sub_14CCA0); AIData::sub_1D580 logs it.
    // Inline: the constructor's vtable emits them after it, before ??_G (the image's order).
    virtual RwInt32 vf_25C()
    {
        return unk_1140;
    }
    // Inline: the constructor's vtable emits them after it, before ??_G (the image's order).
    virtual RwUInt8 * vf_260()
    {
        return (RwUInt8 *)&unk_117C;
    }
    virtual void vf_264(RwInt32 arg_0, RwV3d *arg_4, RwV3d *arg_8);
    // +0x268 to +0x274: attach the player arg_0 to the vehicle, or to its
    // mounted weapon, and detach them ("VehicleAttachEntity",
    // "VehicleAttachEntityToMountedWeapon").
    virtual void vf_268(type_10F710 *arg_0);
    virtual void vf_26C(type_10F710 *arg_0);
    virtual void vf_270();
    virtual void vf_274();
    // +0x278: the engine on or off ("VehicleSetEngine").
    virtual void vf_278(RwInt32 arg_0);
    // +0x27C: whether someone rides it ("RideVehicle" 1,
    // "StopRidingVehicle" 0).
    // Inline: the constructor's vtable emits them after it, before ??_G (the image's order).
    virtual RwUInt8 * vf_0E0()
    {
        return (RwUInt8 *)unk_112C;
    }
    virtual RwInt32 vf_09C()
    {
        return unk_1124;
    }
    virtual void vf_0A0(RwUInt32 arg_0)
    {
        unk_1124 = arg_0;
    }
    virtual AIData * vf_120()
    {
        return &unk_11A0;
    }
    virtual type_3D3548 * vf_118()
    {
        return unk_11A0.unk_54.sub_D4910();
    }
    virtual void vf_11C(type_3D3548 *arg_0)
    {
        unk_11A0.unk_54.sub_D48D0(arg_0);
    }
    virtual void vf_27C(RwInt32 arg_0)
    {
        unk_1140 = arg_0;
    }
    // +0x280: the throttle, a speed ("VehicleSetThrottle"; "VehicleSetBrake"
    // passes 0; its implementation sub_151F80 reads it with fld).
    virtual void vf_280(RwReal arg_0);
    // Inline: the constructor's vtable emits them after it, before ??_G (the image's order).
    virtual RwReal vf_284()
    {
        return unk_450.unk_244;
    }
    // +0x288: the throttle limit ("VehicleSetMaxThrottle").
    // Inline: the constructor's vtable emits them after it, before ??_G (the image's order).
    virtual void vf_288(RwInt32 arg_0)
    {
        *(RwInt32 *)&unk_2638 = arg_0;
    }
    // +0x28C: a turn amount (AIData::sub_1B120); results unused.
    virtual void vf_28C(RwReal arg_0);
    // +0x290: the brake ("VehicleSetBrake"); AIData::sub_1B120 passes 1 when
    // stopping.
    // Inline: the constructor's vtable emits them after it, before ??_G (the image's order).
    virtual void vf_290(RwInt32 arg_0)
    {
        unk_450.unk_230 = arg_0;
    }
    // +0x294, +0x298: AIData::sub_1F2A0 passes (0.0f, 1.0f) to both to stop;
    // results unused.
    virtual void vf_294(RwReal arg_0, RwReal arg_4);
    virtual void vf_298(RwReal arg_0, RwReal arg_4);
    // +0x29C: sub_19CA0 passes it a turn amount; its result is unused.
    virtual void vf_29C(RwReal arg_0);
    // +0x2A0: disables weapon arg_0 or not ("SetVehicleWeaponDisabled");
    // only the widths are known.
    virtual void vf_2A0(RwInt32 arg_0, RwInt32 arg_4);
    // +0x2A4: AIData::sub_1EA70 passes 0 and only steers when it returns
    // 0. Only the widths are known.
    virtual RwInt32 vf_2A4(RwInt32 arg_0);
    // +0x2A8: AIData::sub_1F470 passes its unk_494, 0, 0 and tests the
    // result; AIData::sub_1C4F0 passes 0 or 1 with no point, or 2 with the
    // point it aims at. arg_8 is only known by width.
    // Inline: the constructor's vtable emits them after it, before ??_G (the image's order).
    virtual RwInt32 vf_2A8(RwInt32 arg_0, RwV3d *arg_4, RwInt32 arg_8)
    {
        return 0;
    }
    // +0x2AC (sub_14CE30): fires continuously for arg_0
    // ("FireWeaponContinuous"); only the width is known.
    // Inline: the constructor's vtable emits them after it, before ??_G (the image's order).
    virtual RwInt32 vf_2AC(RwInt32 arg_0)
    {
        unk_DFC.unk_300 = arg_0;
        return 1;
    }
    virtual void vf_2B0();
    virtual void vf_2B4(type_3DBC78_B10 *arg_0, RwReal arg_4);
    // +0x2B8: its movement sounds by its speeds (unk_450.unk_244 and
    // unk_248): starting, stopping and turning, from the player when the
    // player drives it; the running sound's voice goes in unk_1144.
    virtual void vf_2B8();
    // +0x2BC: its running sound by its pitch (the facing's height beyond
    // sin 15 degrees: 0 downhill, 1 level, 2 uphill, kept in unk_114C),
    // restarted on each change.
    virtual void vf_2BC();
    virtual RwMatrix *vf_2C0();

    // +0x2C4: the vehicle's mounted weapon ("VehicleGetMountedWeapon");
    // tested against zero by sub_126B0.
    // Inline: the constructor's vtable emits them after it, before ??_G (the image's order).
    virtual type_3DC9B0 * vf_2C4()
    {
        return (type_3DC9B0 *)unk_1190.sub_D4910();
    }
    // +0x2C8, +0x2CC: attach the player arg_0 as a passenger with the
    // options arg_4 to arg_10, and detach them
    // ("VehicleAttachPlayerPassenger"); only the widths are known.
    virtual void vf_2C8(type_10F710 *arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C,
                        RwInt32 arg_10);
    virtual void vf_2CC();
    // +0x2D0: its scan of the 32 tracked entities (unk_438CA8): clears the
    // cover points facing a close enemy vehicle, engages (vf_2D8) its
    // targets, alerts the soldiers it threatens (vf_2D4, "TankAlert"), and
    // says when its path becomes blocked or clear (unk_11A0.unk_4B0).
    virtual void vf_2D0(RwReal arg_0, RwV3d *arg_4);
    // +0x2D4: whether the tank threatens arg_0 ("IsThreatenedByTank" passes
    // 0 and 0 for the rest); only the widths are known.
    virtual bool vf_2D4(type_3D3548 *arg_0, RwV3d *arg_4, RwReal *arg_8);
    // +0x2D8: whether it may engage the entity arg_4: within reach (*arg_10,
    // else from both sizes, longer for players and alerted AI, or its
    // turret's reach by how they face; arg_8 adds 250), within its height,
    // and within its aim (*arg_C, else its facing, sub_154440).
    virtual bool vf_2D8(RwReal arg_0, type_3D3548 *arg_4, RwInt32 arg_8, RwV3d *arg_C, RwReal *arg_10);

    // +0x2DC: tested against zero by sub_13150; the base implementation
    // (sub_1E4CB0) returns 0. Only its width is established.
    virtual RwInt32 vf_2DC();
    // +0x2E0: 0 here (sub_1E4CB0); the tank's gives unk_290C.
    virtual RwInt32 vf_2E0();
    // +0x2E4: a constant here (sub_17E9B0, folded); the flak gun's gives
    // its -unk_29B0. Inline: its -360.0f is the constructor's object's literal
    // (the image has it after that object's vtable).
    virtual RwReal vf_2E4() { return -360.0f; }
    // Inline: the constructor's vtable emits them after it, before ??_G (the image's order).
    virtual RwInt32 vf_1DC()
    {
        return unk_2854;
    }
    virtual RwReal vf_1E0()
    {
        return unk_2850;
    }
    virtual RwReal vf_2E8()
    {
        return -1.0f;
    }
    // Inline: the constructor's vtable emits them after it, before ??_G (the image's order).
    virtual RwReal vf_2EC()
    {
        return 360.0f;
    }
    // +0x2F0: whether the entity may target arg_0; sub_401B0 scores a
    // target only when it returns nonzero. Only its width is established.
    virtual RwInt32 vf_2F0(type_3D3548 *arg_0);
    // +0x2F4: the matrix of its gun arg_0 into *arg_4 (the player's
    // sub_100680 aims the crosshair along seat 2's); only the widths are
    // known.
    virtual void vf_2F4(RwInt32 arg_0, RwMatrix *arg_4);
    // +0x2F8: takes the model arg_0 (a warning names arg_4 when it is not a
    // model): its clump, its frame and guns, and its tracks' materials.
    virtual void vf_2F8(struct type_3DF8D8 *arg_0, void *arg_4);
    // +0x2FC: its seats' update for the step arg_0 (kinds 2 and 3, vf_03C).
    virtual void vf_2FC(RwReal arg_0);

    RwUInt8 unk_3A8[0x8];
    RwInt32 *unk_3B0;           // its sounds' state (sub_83850, as
    RwUInt8 unk_3B4[0x20];      // type_3D32F8's)
    type_14D000 unk_3D4;
    RwUInt8 unk_44C[0x4];
    type_3DBC78_450 unk_450;    // its physics bodies (sub_14D2C0)
    type_3DBC78_450 unk_7B0;
    type_3DBC78_B10 unk_B10;    // its tracks, left and right (sub_150200:
    type_3DBC78_B10 unk_B18;    // the "vtrack" textures, an "l" after the
                                // name for the left)
    RwInt32 unk_B20;        // sub_19CA0 requires it not to be -1
    RwReal unk_B24;         // turned by vf_29C (clamped steps)
    RwInt32 unk_B28;            // its body runs by physics (vf_040), not
                                // by its animation
    RwInt16 unk_B2C;            // the bone its body follows while animated
    RwUInt8 unk_B2E[0x2];
    type_129B10 unk_B30;
    // Its animation's bones its procedural track (sub_150350) turns: the
    // wheels (by bone id; a 1 in unk_C08 marks the right side's), the
    // steered ones (by unk_450.unk_248, up to 45 degrees), the track
    // wheels (a 1 in unk_D38 for the right), and the root it translates.
    RwInt32 unk_B3C;
    RwInt16 unk_B40[0x64];
    RwInt16 unk_C08[0x64];
    RwInt32 unk_CD0;
    RwInt16 unk_CD4[0x32];
    RwInt16 unk_D38[0x32];
    RwInt32 unk_D9C;
    RwReal unk_DA0;             // its tracks' speeds, right and left
    RwReal unk_DA4;             // (vf_234)
    RwReal unk_DA8;             // the wheels' turns, right and left, in
    RwReal unk_DAC;             // degrees (sub_150350)
    RwInt32 unk_DB0;            // from its trigger (sub_14D2C0; vf_0DC)
    RwInt32 unk_DB4;            // its procedural track (vf_038)
    struct type_7CBD0_hdr *unk_DB8; // its pose key (sub_150350), its
                                    // rotations after it; freed by vf_230
    RwInt32 unk_DBC;            // that key's size
    RwInt32 unk_DC0;        // tested against zero by sub_152A0; whether it
                            // may attack ("Vehicle_AllowAttack"), set while
                            // it has riders
    RwInt32 unk_DC4;        // whether it may move ("Vehicle_AllowMove"), set
                            // with two riders and none incoming
    RwInt32 unk_DC8;        // its riders ("Vehicle_IncrementRiderCount")
    RwInt32 unk_DCC;        // its incoming riders
    RwInt32 unk_DD0;        // the tank's horizontal field of view
                            // ("GetTankHFOV"; "SetTankHFOV" sets it as AI
                            // parameter 2)
    RwInt32 unk_DD4;        // its kind for the HUD (the player's sub_10F900
                            // hands it to type_DC400::sub_E0B60)
    RwUInt8 unk_DD8[0x20];
    RwInt32 unk_DF8;        // cleared before its collisions (sub_14A250)
    type_15B110 unk_DFC;        // its guns: the main gun's tag in its clump
                                // at unk_00[0].unk_38 (AIData::sub_1BAA0),
                                // the third's at unk_00[2].unk_38
                                // (AIData::sub_1BD50 reads the tagged
                                // matrix, sub_EC2D0)
    RwInt32 unk_1100;
    RwInt32 unk_1104;       // steps of a push left (sub_148F60)
    RwV3d unk_1108;         // the push, fading by unk_1120 a step
    RwV3d unk_1114;         // where it applies
    RwReal unk_1120;
    RwInt32 unk_1124;           // vf_09C, vf_0A0
    RwUInt32 unk_1128;          // vf_094
    RwInt16 unk_112C[2];        // words vf_0EC sets (vf_0E0 hands out
                                // their address); sub_14D2C0 clears six
    RwUInt8 unk_1130[0x4];      // bytes from here and sets the next two
    RwInt32 unk_1134;           // its engine is running (vf_278)
    RwInt32 unk_1138;           // moving: vf_2B8 plays its move sounds
    RwInt32 unk_113C;       // set while a player drives it: a soldier it
                            // touches is run over even when it stands still
                            // (type_3DAFC8::vf_060)
    RwInt32 unk_1140;           // vf_25C, vf_27C
    RwInt32 unk_1144;           // its engine sound's voice (vf_278)
    RwInt32 unk_1148;           // another sound's voice (sub_153B30)
    RwInt16 unk_114C;           // -1 whenever vf_2B8 changes unk_1144
    RwUInt8 unk_114E[0x2];
    RwReal unk_1150;            // the cosines of half its field of view
    RwReal unk_1154;            // across and of a degree (AI parameters 2
                                // and 3; vf_0FC, vf_100 give -1 while
                                // unk_1158 is set)
    RwInt32 unk_1158;           // vf_240, vf_244
    RwReal unk_115C;            // its ranges, AI parameters 4 and 5 (times
    RwReal unk_1160;            // 100; vf_10C, vf_114)
    RwReal unk_1164;            // vf_238, vf_23C
    RwReal unk_1168;            // AI parameter 6 (vf_114)
    // An inline accessor for unk_113C, with no address and so no database
    // name; named for its field. Evidence: type_3DAFC8::vf_060 tests it
    // through a slot of its own after the other inlines' locals.
    RwInt32 get_unk_113C()
    {
        RwInt32 r = unk_113C;
        return r;
    }
    RwReal unk_116C;        // returned by vf_254 (sub_14CC60)
    RwReal unk_1170;        // returned by vf_258 (sub_14CC80)
    RwReal unk_1174;            // vf_164
    RwReal unk_1178;            // vf_168
    RwV3d unk_117C;             // the point it watches (vf_2D4; vf_260
                                // hands out its address)
    RwInt32 unk_1188;       // its kind (0 or 1: the player's sub_10F900)
    // An inline accessor for unk_1188, with no address and so no database
    // name; named for its field. Evidence: the player's sub_10F900 switches
    // on it through a temporary that first takes a copy of the inline's own
    // return slot (a direct return, no local).
    RwInt32 get_unk_1188()
    {
        return unk_1188;
    }
    type_D48D0 unk_118C;        // the player passenger
                                // ("VehicleGetPlayerPassenger")
    type_D48D0 unk_1190;
    RwInt32 unk_1194;
    RwUInt8 unk_1198[0x8];
    AIData unk_11A0;            // its AI
    RwInt32 unk_2620;           // vf_248
    RwInt32 unk_2624;           // its health (vf_174, vf_178; vf_180 adds,
    RwInt32 unk_2628;           // capped at its full health unk_2628;
                                // vf_17C, the fraction)
    RwInt32 unk_262C;           // vf_24C, and its fraction of unk_2630
    RwInt32 unk_2630;           // (vf_250)
    RwReal unk_2634;            // health regained a step (vf_03C)
    RwReal unk_2638;            // its steering limit (vf_280; vf_288 takes
                                // its bits)
    type_14D180 unk_263C[0xC];  // built by sub_1555A0 and sub_14C930
    RwReal unk_284C;            // vf_2D0: the cover reach to the sides
    RwReal unk_2850;            // vf_1E0
    RwInt32 unk_2854;           // vf_1DC
    RwInt32 unk_2858;
    RwUInt8 unk_285C[0x4];

    // Built for the trigger arg_0 (the rest of the set-up is sub_14D2C0).
    // Defined here: VC7.1 does not inline it into the factory (sub_14C820),
    // which still reserves its frame; its out-of-line copy is sub_14C930.
    type_3DBC78(type_712B0 *arg_0)
    {
        sub_14D2C0(arg_0);
    }
    // Built bare, for a derived vehicle's own set-up: its out-of-line
    // definition is sub_1555A0, in the tank's unit (unit_155470), and the
    // tank's factory (which inlines the tank's constructor) reserves
    // nothing for it.
    type_3DBC78();
    // Taken down (vf_230), then its members go. Defined in the class but
    // not inlined (its members have destructors): the tank's destructor
    // (sub_155720) reserves the expansion's six temporaries; its
    // out-of-line copy is sub_14CF20 (unit_147080).
    ~type_3DBC78()
    {
        vf_230();
    }
    // The placement pair sub_14C820 builds it in entity memory with, as
    // type_3D32F8's (sub_6CCF0 and the empty sub_19A750); the plain operator
    // delete, empty and folded likewise, for its scalar deleting destructor
    // (the placement one hides the base's).
    static void *operator new(RwUInt32 arg_0, void *arg_4);
    static void operator delete(void *arg_0, void *arg_4);
    static void operator delete(void *arg_0);
    RwInt32 sub_14D2C0(type_712B0 *arg_0);

    // The record arg_0 indexes, when arg_0's handle points at this entity;
    // else 0.
    type_14D180 *sub_155340(type_154C0_12F4 *arg_0);
    // Switches to the destroyed clump ("SwitchToDestroyedClump"); whether it
    // did.
    bool sub_153CB0();
    // Stops its engine sounds (before the player leaves, vf_270).
    void sub_153B30();
    // Its direction of travel into *arg_0 (zero when it barely moves) and
    // the way it faces into *arg_4 (its facing when it reverses into a turn
    // or its physics are off, else its travel).
    void sub_154440(RwV3d *arg_0, RwV3d *arg_4);
    // Places its cover points on its model and marks each clear or not.
    void sub_154EA0();
    // Sets (arg_C) or adds to node arg_4 of the pose arg_0 the matrix
    // arg_8's translation and rotation.
    void sub_153890(type_153890 *arg_0, RwInt32 arg_4, RwMatrix *arg_8, RwInt32 arg_C);
    // Sets the record arg_0 up: arg_4, a random amount from arg_8 to arg_C
    // (either sign), and the vector *arg_10 (the tanks' set-up passes two).
    void sub_153C40(type_153C40 *arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C, RwV3d *arg_10);
    // Enables its cover points ("EnableVehicleCoverPoints"); only the width
    // is known.
    void sub_154E30(RwInt32 arg_0);
    // The matrix of the record arg_0's tag in its clump, into *arg_4;
    // arg_0, or 0 without a clump.
    type_14D180 *sub_1553E0(type_14D180 *arg_0, RwMatrix *arg_4);
    // vf_010, as the image's vtable has it (a trivial body, folded into
    // sub_6FCD0 with every other copy).
    virtual type_3DBC78 *vf_010()
    {
        return this;
    }
    // vf_214, as the image's vtable has it (a trivial body, folded into
    // sub_73D80 with every other copy).
    virtual void vf_214(struct type_D05C0 *arg_0, RwFrame *arg_4, RwReal arg_8)
    {
    }
};

// Builds the vehicle for the trigger arg_0 (0 when there is no entity
// memory for it).
type_3DBC78 *sub_14C820(type_712B0 *arg_0);

// vf_2F8's clump callbacks: the atomics' spheres doubled, and the tracks'
// materials found (sub_1501A0 and its material callback sub_150200, which
// gives them a UV animation).
struct RpAtomic *sub_14FFA0(struct RpAtomic *arg_0, void *arg_4);
struct RpAtomic *sub_1501A0(struct RpAtomic *arg_0, void *arg_4);
struct RpMaterial *sub_150200(struct RpMaterial *arg_0, void *arg_4);
// Its procedural track's callback (vf_038), and what the fade ends with
// when a player's vehicle is destroyed (vf_03C): the sound off.
void sub_150350(struct type_7C8D0 *arg_0, struct type_80300 *arg_4, RwInt32 arg_8, bool arg_C);
void sub_150B00();
// Restores the player's field of view (leaving a vehicle, vf_270).
void sub_151550();
// A track's UV animation (a later unit), or 0.
struct RtAnimAnimation *sub_159AC0();
// sub_1501A0's search: the vehicle and where to note a track was found.
struct type_150200
{
    type_3DBC78 *unk_00;
    RwInt32 *unk_04;
};
// The rotation of arg_10 degrees about the axis (arg_4, arg_8, arg_C) into
// arg_0's axes (its position is left).
void sub_14D1B0(RwMatrix *arg_0, RwReal arg_4, RwReal arg_8, RwReal arg_C, RwReal arg_10);

#endif
