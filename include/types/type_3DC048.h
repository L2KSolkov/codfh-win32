/*
 * type_3DC048: an entity class derived from type_3DBC78, anchored at its
 * vtable off_3DC048 (193 slots), which sub_155470, sub_155720 and sub_15A8C0
 * install (sub_155470 calls sub_1555A0, which installs off_3DBC78). It is the
 * class type_3D3548::vf_014 returns: its slot +0x014 returns this (sub_6FCD0).
 * Its AI object is embedded at +0x11A0 (vf_120 is sub_14CD40).
 */
#ifndef TYPE_3DC048_H
#define TYPE_3DC048_H

#include "types/type_3DBC78.h"

// The tank's set-up (sub_155780) starts two of its values at this.
extern RwReal dword_429DC8;
// Its vf_03C's tuning: the turn springs' constants, the gun's pitch
// limits, the zoomed field of view and the gun's raise when manned.
extern RwReal flt_429DE8;
extern RwReal flt_429DEC;
extern RwReal flt_429DF0;
extern RwReal flt_429DF4;
extern RwReal dword_429DF8;
extern RwReal dword_429DFC;

// A bone the tank's set-up (sub_155780) records, and its procedural track
// (sub_155D30) turns: its index, a turn scale, the axis (0 to 5: -x, -y,
// -z, x, y, z), a ratio's parts and the bone's rest rotation, saved when
// the pose key is built.
struct type_3DC048_2918
{
    RwInt32 unk_00;
    RwInt32 unk_04;         // on: vf_038 eases unk_10 up to unk_14 (off:
                            // down to 0), 1/30 of the step a step
    RwInt32 unk_08;
    RwInt32 unk_0C;
    union
    {
        RwReal unk_10;
        RwInt32 unk_10_i;   // set from the script's raw argument (sub_15A4A0)
    };
    union
    {
        RwReal unk_14;
        RwInt32 unk_14_i;
    };
    RtQuat unk_18;
};

struct type_3DC048 : type_3DBC78
{
    // Placed after type_3DBC78 (0x2860 bytes, its factory's allocation,
    // sub_14C820).
    // Its set-up (sub_155780) clears everything from here to unk_29A0
    // but unk_286C, unk_288C (its trigger's unk_1A0 and unk_1A8) and the
    // two set to dword_429DC8.
    RwInt32 unk_2860;
    RwInt32 unk_2864;
    RwReal unk_2868;        // its turret's heading, 0 to 360 degrees
                            // (AIData::sub_1BFB0 centres it)
    RwReal unk_286C;
    RwReal unk_2870;        // AIData::sub_1D2C0 turns by it (vf_298)
    RwReal unk_2874;
    RwReal unk_2878;
    RwReal unk_287C;
    RwReal unk_2880;
    RwReal unk_2884;
    RwReal unk_2888;
    RwReal unk_288C;
    RwReal unk_2890;        // the turret's turn and the gun's pitch, in
    RwReal unk_2894;        // degrees: the gunner rides the turret bone
    RwReal unk_2898;        // turned by them (type_3DBC78::vf_04C)
    RwReal unk_289C;
    RwReal unk_28A0;
    RwReal unk_28A4;
    RwV3d unk_28A8;
    RwV3d unk_28B4;
    RwInt32 unk_28C0;       // the gunner's camera starts at rest (vf_044)
    RwReal unk_28C4;        // the camera's distance and its spring speed
    RwReal unk_28C8;
    RwReal unk_28CC;        // the distance it eases toward (pulled in by
    RwReal unk_28D0;        // a hit, for a time)
    RwReal unk_28D4;        // the camera's pitch and its spring speed
    RwReal unk_28D8;
    RwInt32 unk_28DC;       // AIData::sub_1D620 only steers with vf_294
                            // while it is not -1; the turret bone's index
                            // (bone 2; type_3DBC78::vf_04C)
    RwInt32 unk_28E0;       // the gun's bone (3)
    type_153C40 unk_28E4[2];    // the turret's and the gun's turns
                                // (sub_153C40)
    RwInt32 unk_290C;       // vf_2E0
    RwReal unk_2910;        // vf_2E8
    RwReal unk_2914;
    type_3DC048_2918 unk_2918[3];   // bones 4, 6 and 7
    struct type_3DFEEC *unk_2990;   // the object its turret tracks, while
                                    // unk_2994 is set (sub_15A0F0)
    RwInt32 unk_2994;
    RwInt32 unk_2998;       // centring the turret and gun (vf_03C runs
                            // sub_156FC0 instead of their controls)
    RwReal unk_299C;        // the centring's speeds (sub_141700)
    RwReal unk_29A0;
    RwUInt8 unk_29A4[0xC];

    // Built for the trigger arg_0: the vehicle's bare constructor
    // (sub_1555A0), then its own set-up (sub_155780). Inlined into its
    // factory (sub_155470).
    type_3DC048(type_712B0 *arg_0)
    {
        sub_155780(arg_0);
    }
    // Built bare, for the flak gun (its constructor, sub_15A8C0, inlines
    // it).
    type_3DC048()
    {
    }
    // Takes it down (its own vf_230, empty and folded into pDtor), then the
    // vehicle's destructor. Inline, defined in unit_155470.cpp after vf_2E0:
    // the flak gun's destructor (sub_15A9E0) inlines it; its out-of-line copy
    // is sub_155720, whose EH handler the image has after vf_2E0's code.
    inline ~type_3DC048();
    // Its set-up from the trigger arg_0: the vehicle's (sub_14D2C0), its
    // kind flags, its turret and gun bones and its guns' tags ("RIFA" to
    // "RIFC"); 1.
    RwInt32 sub_155780(type_712B0 *arg_0);

    // Its turret's tracking step (sub_15A160: toward unk_2990's point, the
    // turn eased within 0.99 of its facing and the pitch within 0.087,
    // ending the tracking when the object has no point) and its centring
    // (sub_156FC0).
    void sub_15A160();
    void sub_156FC0();
    // Its turret's turning sound: started (unk_1148, unless playing) and
    // stopped, with the stop sound (from the player when the player
    // drives).
    void sub_159950();
    void sub_159A00();
    // +0x03C: the vehicle's step, then its turret: its gun's firing, the
    // driving player's zoom, and the turret's and the gun's turns (by the
    // player's sticks, eased by sub_112DA0, the turret kept within its arc
    // unk_286C and the limits vf_2E4 and vf_2EC).
    virtual void vf_03C(RwReal arg_0);
    // +0x038: its procedural track (sub_155D30) started once, its recorded
    // bones eased, then its AI steps by arg_0.
    virtual void vf_038(RwReal arg_0);
    // +0x044: the vehicle's, then its player rider's place: the driver
    // (posture 0) on the turret's circle, turned with it; the gunner
    // (posture 2) with the camera eased behind the turret (unk_28A8, kept
    // unk_28C4 from it and pulled in, unk_28CC, when a line test hits),
    // its aim matrix looking at the tank.
    virtual void vf_044(RwReal arg_0);
    // +0x268, +0x270: the vehicle's getting in and out, the turret part
    // hidden while the player is in (sub_159910).
    virtual void vf_268(struct type_10F710 *arg_0);
    virtual void vf_270();
    // +0x28C: its turn arg_0 while its engine runs and it may move.
    virtual void vf_28C(RwReal arg_0);
    // +0x294, +0x298: the turret's and the gun's turns (arg_4 unused),
    // unless it is locked (unk_2994) or may not attack; the turret's turns
    // the tank itself when it has a gun bone but no turret bone.
    virtual void vf_294(RwReal arg_0, RwReal arg_4);
    virtual void vf_298(RwReal arg_0, RwReal arg_4);
    // +0x2A4: whether gun arg_0 may fire: gun 0 only while it may attack
    // with no rider incoming, loaded, with rounds, not blocked (flag
    // 1 << arg_0 of unk_1100), and at a target it may shoot (vf_2F0 of its
    // AI's unk_1374).
    virtual RwInt32 vf_2A4(RwInt32 arg_0);
    // +0x2A8: fires gun arg_0 (unless arg_8, only when vf_2A4 allows): at
    // the point *arg_4 for guns 1 and 2 when given, spread by the
    // difficulty (or by the player's weapon for the player's own shots),
    // with its particles and sound; 1 when it fired.
    virtual RwInt32 vf_2A8(RwInt32 arg_0, RwV3d *arg_4, RwInt32 arg_8);
    // +0x300: gun 0's own firing; only the width is known.
    virtual RwInt32 vf_300(RwInt32 arg_0);
    // +0x2B0: starts centring its turret and gun (with the turning sound).
    virtual void vf_2B0();
    // +0x2F0: whether it may target arg_0: always without a turret or a
    // target, else when its gun can bear on arg_0 (sub_1409C0, within
    // vf_2E8) and it is within its range (unk_2914, squared).
    virtual RwInt32 vf_2F0(type_3D3548 *arg_0);
    // +0x058: whether arg_0 names the object its turret tracks, else the
    // vehicle's.
    virtual RwInt32 vf_058(struct type_3DF8D8_04 *arg_0);
    // +0x2B8: the vehicle's sounds, then the turret's and the gun's turning
    // sound by their turns (beyond flt_429E2C), unless it is centring.
    virtual void vf_2B8();
    // +0x054: the vehicle's (a render part per arg_0; only the width is
    // known).
    virtual void vf_054(RwInt32 arg_0);
    // +0x110: the point others aim at: its turret bone, else the
    // vehicle's; its position raised by 75 without an animation.
    virtual void vf_110(RwV3d *arg_0, type_3D3548 *arg_4, RwInt32 arg_8);
    virtual void vf_230();
    // +0x2FC: the vehicle's (its seats).
    virtual void vf_2FC(RwReal arg_0);
    virtual RwInt32 vf_2E0();
    virtual RwReal vf_2E8();
    // The state of hatch arg_0 ("VehicleGetHatchState", which requires flag
    // bit 18 of unk_2C); only the widths are known.
    RwInt32 sub_15A480(RwInt32 arg_0);
    // Turret tracking of the object arg_0 on, and off
    // ("VehicleEnableTurretTrack", "VehicleDisableTurretTrack").
    void sub_15A0F0(struct type_3DFEEC *arg_0);
    void sub_15A120();
    // Restrict its targets to the zone (arg_0, arg_4) and lift the
    // restriction ("SetRestrictedTankTargetZone",
    // "ClearRestrictedTankTargetZone"); only the widths are known.
    void sub_15A530(RwReal arg_0, RwReal arg_4);
    void sub_15A590();
    // Sets hatch arg_0 with the options arg_4 to arg_10
    // ("VehicleSetHatchState"); only the widths are known.
    void sub_15A4A0(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C,
                    RwInt32 arg_10);
    // Shows its "Turret" part or hides it (sub_16D8C0 of unk_264 with
    // arg_0 != 0); only the widths are known.
    void sub_159910(RwInt32 arg_0);
    // vf_014, as the image's vtable has it (a trivial body, folded into
    // sub_6FCD0 with every other copy).
    virtual type_3DC048 *vf_014()
    {
        return this;
    }
};

typedef RwChar type_3DC048_size_check[sizeof(type_3DC048) == 0x29B0 ? 1 : -1];

// sub_155470: the tank's factory (VehicleTrigger's vf_020 for a tank), as
// sub_14C820 is the vehicle's.
struct type_712B0;
type_3DC048 *sub_155470(type_712B0 *arg_0);

// sub_1571D0: the seat switch's fade callback (dword_4D5160 = 1).
void sub_1571D0();
// sub_1571E0: the player arg_0's seat switch in the tank arg_8 (arg_4
// unused): by the pad's buttons 9 and 10 a fade starts (sub_1571D0 ends
// it); at its end the player takes the posture unk_4D4 (1 the gunner: the
// weapon in hand given back; 2: the tank's weapon, sub_157600).
void sub_1571E0(struct type_10F710 *arg_0, RwInt32 arg_4, type_3DC048 *arg_8);
// sub_157600: puts the weapon kind 35 (arg_4 1) or 29 in the player
// arg_0's hand.
void sub_157600(struct type_10F710 *arg_0, RwInt32 arg_4);
extern RwInt32 dword_4D5160;
// vf_044's camera tuning (400, 0.02, 0.08, 0.6, 10, 0.005, 0.5, 0.08, 0.4,
// 20, 400, 40, 40) and the rotation axes x and y.
extern RwReal dword_429DC4;
extern RwReal dword_429DD0;
extern RwReal dword_429E00;
extern RwReal dword_429E04;
extern RwReal flt_429E08;
extern RwReal flt_429E0C;
extern RwReal dword_429E10;
extern RwReal dword_429E14;
extern RwReal dword_429E18;
extern RwReal dword_429E1C;
extern RwReal flt_429E20;
extern RwReal flt_429E24;
extern RwReal flt_429E28;
// The vehicles' object's constants (unit_14C930, 0x3DBC58-0x3DBC74): its frame time and
// two axes, read here.
extern const RwReal flt_3DBC58;
extern const RwV3d stru_3DBC5C;
extern const RwV3d stru_3DBC68;
// sub_15F2C0: fires a projectile of the kind flags arg_0 for arg_4 from the
// matrix arg_8 at the velocity *arg_C (arg_10, and the settings arg_14 and
// arg_18); its definition's prototype (game/type_495F0.h): the owner and the
// last word travel as words.
struct type_439A48;
RwInt32 sub_15F2C0(RwInt32 arg_0, RwInt32 arg_4, RwMatrix *arg_8, RwV3d *arg_C, RwInt32 arg_10,
                   type_439A48 *arg_14, RwInt32 arg_18);
extern RwReal flt_4F2890[3];
extern RwReal flt_429E2C;
// sub_FCAE0: a line test from *arg_0 to *arg_4, its hit into *arg_8;
// nonzero on a hit. Only the widths of the rest are known.
struct RwV3d;
RwInt32 sub_FCAE0(RwV3d *arg_0, RwV3d *arg_4, RwV3d *arg_8, RwV3d *arg_C, RwInt32 arg_10, RwInt32 arg_14, RwInt32 arg_18);
extern RwReal flt_429DCC;

// The key frames sub_159AC0 builds and sub_159CB0 turns into a UV
// animation's: a node's frames and their count.
struct type_159AC0
{
    union
    {
        struct RpUVAnimKeyFrame *unk_00;
        RwUInt8 *unk_00_b;      // walked by the scheme's key frame size
    };
    RwInt32 unk_04;
};
// A UV animation as RenderWare's own code lays it out (the frames at +0x10,
// the key frame size in the scheme at +8), unlike the game's RtAnimAnimation.
struct type_159CB0_info
{
    RwInt32 typeID;
    RwInt32 interpKeyFrameSize;
    RwInt32 animKeyFrameSize;
};
struct type_159CB0
{
    type_159CB0_info *interpInfo;
    RwInt32 numFrames;
    RwInt32 flags;
    RwReal duration;
    struct RpUVAnimKeyFrame *pFrames;
};
// sub_159CB0: fills the UV animation arg_0 from the arg_8 nodes' key frames
// arg_4, the first two of each node first, then by time; 1.
RwInt32 sub_159CB0(RtAnimAnimation *arg_0, type_159AC0 *arg_4, RwInt32 arg_8);

// sub_155D30: the tank's procedural track (as sub_150350 is the vehicle's;
// arg_8 is the tank): its pose key, with room for translations, and its
// three recorded bones' rest rotations; then the vehicle's step, the turret
// and the gun, the recorded bones, and, while it plays its own animation
// and has none queued, the turns of unk_28E4.
void sub_155D30(struct type_7C8D0 *arg_0, struct type_80300 *arg_4, RwInt32 arg_8, bool arg_C);

#endif
