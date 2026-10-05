/*
 * type_10F710: what an entity's vf_00C returns (a checked downcast, like
 * vf_008 and vf_014): a player, anchored at its lowest known method
 * sub_10F710. type_3CE5AC reaches it through its group's unk_2BC entity.
 *
 *   +0x1B2C unk_1B2C  when set, sub_10F7E0 stores 0 whatever it is given
 *   +0x21F0 unk_21F0  20 flags: sub_10F7E0 sets one, sub_10F710 returns
 *                     the first set (19 when none is, or while unk_2240 is
 *                     clear)
 *   +0x2240 unk_2240  cleared by type_3CE5AC::vf_00C
 */
#ifndef TYPE_10F710_H
#define TYPE_10F710_H

#include <string.h>
#include "rw/ostypes.h"
#include "rw/rtquat.h"
#include "types/type_3D3548.h"
#include "types/type_D48D0.h"
#include "types/type_4C19C0.h"
#include "types/type_129_base.h"
#include "types/type_67260.h"
#include "types/AIData.h"
#include "types/type_44350.h"

// type_10F710_21B4: the player's inventory, embedded at +0x21B4 and named
// for its container and offset (src/recovered/unit_1154A0.cpp): a count for
// each of its kinds 1 to 12 (1 the health packs), the kind selected and a
// flag. "GivePlayerInventoryItem" adds arg_4 of the kind arg_0 (sub_116080)
// and then selects it (sub_115980).
struct type_10F710_21B4
{
    RwInt32 unk_00[13];
    RwInt32 unk_34;             // the kind selected (0 for none)
    RwInt32 unk_38;

    // An inline accessor for unk_34, with no address and so no database
    // name; named for its field. Evidence: the second network player's step
    // (sub_1BAE40) reads it through a slot of its own.
    RwInt32 get_unk_34()
    {
        RwInt32 r = unk_34;
        return r;
    }

    // Out of line and empty: the player's constructor calls the one
    // (sub_6FCD0, folded by /OPT:ICF with the functions returning this) and
    // its destructor the other (pDtor, folded at 0x1E41C0).
    type_10F710_21B4();
    ~type_10F710_21B4();

    // Adds arg_4 of the kind arg_0, up to the most its weapon holds for the
    // grenades and the like (showing arg_4), else selecting it; the count.
    RwInt32 sub_116080(RwInt32 arg_0, RwInt32 arg_4);
    // The player's take-down; 1.
    RwInt32 sub_115500();
    // Fills the checkpoint's inventory record arg_0 (the player's
    // sub_111040).
    void sub_1162C0(struct type_D90B0_18 *arg_0);
    // Selects the kind arg_0 (and the HUD's icon).
    void sub_115980(RwInt32 arg_0);
    // Empties it (the player's set-up); 1.
    RwInt32 sub_1154A0();
    // The HUD's count for the kind selected, fading in or out for the time
    // arg_0 (flt_429B40).
    void sub_115520(RwReal arg_0);
    // Selects the next kind it has (0 for none; not the health packs).
    RwInt32 sub_115620();
    // Uses one of the kind arg_4 (-1 the one selected; arg_0 passed on for a
    // weapon): a health pack heals, or at full health plays the music; the
    // others the player's sub_108BC0. Then selects the next when none are
    // left.
    void sub_115690(RwReal arg_0, RwInt32 arg_4);
    // Takes the pickup arg_0: a health pack, a health pack for later,
    // rounds for a weapon or an inventory kind, by the pickup's kind; what it
    // gave (-1 for nothing, 13 for rounds).
    RwInt32 sub_1159C0(struct type_3D94B8 *arg_0);
    // Whether it has any kind but the health packs.
    RwInt32 sub_116270();
    // The count of the kind arg_0: out of line, and folded (/OPT:ICF) into
    // another class's identical accessor at 0x1E3BF0.
    RwInt32 sub_1E3BF0(RwInt32 arg_0);
};
// The alpha of the HUD's inventory count and how fast it fades (.data;
// type_10F710_21B4::sub_115520).
extern RwReal flt_429B40;
extern RwReal flt_429B44;
// The rounds a pickup gives, scaled by difficulty (.data; sub_1159C0).
extern RwReal flt_4F2884[3];

// type_10F710_1A48: a player's copy of a weapon (type_10F710::unk_1A48),
// named for its container and offset. CWeaponBehavior's HandleAttributes
// updates its six points (from its settings' unk_1C0 to unk_1D8 and unk_3EC
// to unk_404); the HUD's crosshair reads its settings (unk_448) and its
// spread fraction (sub_11D690).
//
// Its code is src/recovered/unit_116310.cpp (vtable off_3DA5E8, 0x470
// bytes); sub_116490 builds one of it or of the three derived classes below
// by the weapon's index.

// The data of the weapon's animation events (vf_030), named for what reads
// them: a point or a tag, and a particle system (1300 to 1302); a shell's
// kind, particle system and sound key (3000); a sound key and its flags
// (1100).
struct type_10F710_1A48_ev
{
    RwInt32 unk_00;
    RwInt32 unk_04;
    RwInt32 unk_08;
    RwInt32 unk_0C;
};
struct type_10F710_1A48_shell
{
    RwInt32 unk_00;
    RwInt32 unk_04;
    type_3DF8D8_04 unk_08;
};
struct type_10F710_1A48_snd
{
    type_3DF8D8_04 unk_00;
    RwUInt32 unk_08;
};

// A weapon copy's state in a checkpoint (vf_03C, vf_040); named for its
// owner. Only what they copy is known.
struct type_10F710_1A48_save
{
    RwUInt8 unk_00[0x4];
    RwInt32 unk_04;
    RwInt32 unk_08;
    RwUInt8 unk_0C;
    RwUInt8 unk_0D;
    RwUInt8 unk_0E;
    RwUInt8 unk_0F;
    RwInt32 unk_10;
    RwInt32 unk_14;
    RwUInt8 unk_18[0x8];
    RwReal unk_20;
    RwReal unk_24;
    RwUInt8 unk_28;
    RwUInt8 unk_29[0x7];
    RwReal unk_30;
    RwUInt8 unk_34[0x84];
    RwInt32 unk_B8;
    RwInt32 unk_BC;
    RwUInt8 unk_C0[0x38];
    RwUInt8 unk_F8[0x84];
};

struct type_10F710_1A48
{
    // sub_116870: its members (the holders and records empty).
    type_10F710_1A48();
    // Virtual: the player's take-down deletes its copies through slot 0.
    // sub_116700: puts it away (unk_41C, sub_116470), then its holders go.
    // Defined here: the derived kinds' compiler-written destructors reserve
    // the frame of its expansion, but call it.
    virtual ~type_10F710_1A48()
    {
        unk_41C = 0;
        sub_116470();
    }
    // +0x004: sets it up for the player arg_0 with its clump arg_4 and its
    // index arg_8 (sub_116BD0, from sub_116490), reloading its model when
    // arg_C is set: takes its settings, a full clip and its state reset.
    virtual bool vf_004(struct type_10F710 *arg_0, RpClump *arg_4, RwInt32 arg_8, RwInt32 arg_C);
    // +0x008: loads its model once (sub_116A40): its settings' named
    // object (kind 5) gives a clump, cloned onto the player's clump
    // (arg_4's frame) and held in unk_420 (weapons 30 and 36 only when
    // there is one). Returns 1, or 0 with no such object.
    virtual bool vf_008(struct type_10F710 *arg_0, RpClump *arg_4, RwInt32 arg_8);
    // +0x00C: drops its model (sub_1169E0): releases unk_43C and unk_420.
    virtual bool vf_00C();
    // +0x010: whether it needs reloading (sub_1193B0): its clip empty with
    // rounds in reserve, not reloading and ready.
    virtual bool vf_010();
    // +0x014: whether it may reload (sub_119400): its clip not full, rounds
    // in reserve, not reloading or busy and ready (weapon 15 only when
    // empty).
    virtual bool vf_014();
    // +0x018: fires (sub_1176F0); whether it did.
    virtual bool vf_018();
    // +0x01C: plays its settings' animation unk_2C on the player once the
    // idle flag unk_10 is set (sub_117650); whether it did.
    virtual bool vf_01C();
    // +0x020: starts a reload (sub_119180): stops its firing sound, plays
    // its reload sound and animation (the aimed one while unk_230, or
    // settings unk_84 when unk_80); 0 with no rounds in reserve.
    virtual bool vf_020();
    virtual void vf_024();
    // +0x028: the next step of the player's death (sub_119500): the hit
    // animation (unk_14 0), the death by stance (1), then after the fade
    // (sub_119480) the freeze (2 on); 0 when an animation is missing.
    virtual bool vf_028();
    virtual void vf_02C();
    // +0x030: its animation's event arg_0 with its data arg_4 (sub_119FA0;
    // the player's vf_170 passes its own on, the weapon change 1, 0, 0 for
    // an animation's end); arg_8 is unused.
    virtual void vf_030(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8);
    // +0x034: run on readying one whose settings' unk_20 is set
    // (sub_11D350); only known by its width.
    virtual void vf_034();
    // +0x038: 0 (sub_11D330).
    virtual RwInt32 vf_038();
    // +0x03C and +0x040: save its state into, and restore it from, the
    // checkpoint record arg_0 (sub_11D890, sub_11D9A0).
    virtual void vf_03C(struct type_10F710_1A48_save *arg_0);
    virtual void vf_040(struct type_10F710_1A48_save *arg_0);

    RwUInt8 unk_04[0xC];
    RwUInt8 unk_10;             // set by the player's vf_258 when idle
    RwUInt8 unk_11;             // cleared, with unk_12, and unk_13 set, when
    RwUInt8 unk_12;             // the player changes weapon
    RwUInt8 unk_13;
    RwInt32 unk_14;
    RwReal unk_18;              // its recoil, recovering each frame (the
    RwReal unk_1C;              // player's vf_038); unk_1C and unk_20 go
    RwReal unk_20;              // into unk_238 or unk_25C by the stance
    union
    {
        struct
        {
            RwInt32 unk_24;
            RwInt32 unk_28;
            RwInt32 unk_2C;
            RwInt32 unk_30;
            RwInt32 unk_34;
            RwInt32 unk_38;
        };
        RwLine unk_24_l;        // the recoil's line (vf_018)
    };
    RwUInt8 unk_3C;
    RwUInt8 unk_3D[0x3];
    RwInt32 unk_40;
    RwUInt8 unk_44;
    RwUInt8 unk_45;
    RwUInt8 unk_46;             // while set, its sound unk_21C plays
    RwUInt8 unk_47;
    RwInt32 unk_48;
    RwInt32 unk_4C;
    RwReal unk_50;              // weapon 4's twist of bone unk_58 (the
    RwReal unk_54;              // player's sub_110A60, carrying bone unk_5C);
                                // for weapon 4, 360 over a clip's rounds
    RwInt32 unk_58;
    RwInt32 unk_5C;
    RwInt32 unk_60;
    RwReal unk_64;              // the last shot's sideways kick (vf_018)
    RwUInt8 unk_68[0x108];
    RtQuat unk_170[3];          // by stance, identity at set-up
    RtQuat unk_1A0[3];
    RwV3d unk_1D0[3];
    RwV3d unk_1F4[3];
    RwReal unk_218;             // the zoom's fraction reached (the player's
                                // sub_104FF0)
    RwInt32 unk_21C;            // its sound
    RwReal unk_220;             // a time the recoil recovers after
    RwInt32 unk_224;            // its state (1 put away, 2 dropped)
    RwInt32 unk_228;            // any of these three holds the player's
    RwInt32 unk_22C;            // bipod down
    RwInt32 unk_230;
    RwInt32 unk_234;
    union
    {
        struct
        {
            RwV3d unk_238;
            RwV3d unk_244;
            RwV3d unk_250;
            RwV3d unk_25C;
            RwV3d unk_268;
            RwV3d unk_274;
        };
        struct
        {
            RwV3d unk_238_a[3]; // by stance (vf_038)
            RwV3d unk_25C_a[3]; // likewise, while the player's unk_1B04
        };
    };
    RwV3d unk_280;              // cleared by sub_1062A0
    RwV3d unk_28C;
    RwReal unk_298;
    type_10F710_1A48_29C unk_29C;
    type_10F710_1A48_29C unk_2D4;
    type_67260 unk_30C;
    RwUInt8 unk_35C[0x34];
    type_67260 unk_390;
    RwUInt8 unk_3E0[0x34];
    RwInt32 unk_414;            // the rounds loaded
    RwInt32 unk_418;            // the rounds in reserve
    RwUInt8 unk_41C;            // it is drawn (the player's sub_110A60)
    RwUInt8 unk_41D;
    RwUInt8 unk_41E;            // it may be selected (sub_108BC0); set
                                // once its model is loaded (vf_008)
    RwUInt8 unk_41F;
    type_129940 unk_420;        // its model's clump (the player's sub_111000)
    struct type_10F710 *unk_42C;    // its player (its model is tied to it)
    type_129940 unk_430;        // the player's clump it hangs on (unk_430.unk_08)
    type_129940 unk_43C;
    type_4C19C0 *unk_448;       // its settings
    RwInt32 unk_44C;
    RwReal unk_450;
    RwReal unk_454;
    RwInt32 unk_458;            // its type (the player's vf_160 maps it)
    RwInt32 unk_45C;            // its kind (2: no select or deselect
                                // animation needed)
    struct type_10F710_1A48 *unk_460; // its partner copy (the player's
                                      // sub_10D8A0 pairs 29 with 30, 35 with 36)
    RwUInt8 unk_464;            // set on the second of a pair
    RwUInt8 unk_465;            // its particles follow it (event 1302)
    RwUInt8 unk_466[0x2];
    RwInt32 unk_468;            // shots run together (vf_018)
    RwUInt8 unk_46C[0x4];

    // Inline setters for unk_464 and unk_460, with no address and so no
    // database names; named for their fields. Evidence: the player's
    // sub_10D8A0 stores through temporaries holding the copy (the inlines'
    // `this`) and the value.
    void set_unk_464(RwUInt8 arg_0)
    {
        unk_464 = arg_0;
    }
    void set_unk_460(struct type_10F710_1A48 *arg_0)
    {
        unk_460 = arg_0;
    }
    // Called on each copy by the player's sub_10D8A0 before it is deleted;
    // only known by its width.
    void sub_116470();
    // What sub_116470 runs; only the width is known.
    bool sub_117080();

    // A fraction (0 to 1) the HUD's crosshair spreads by
    // (type_DC400::sub_E08B0); only the width is known.
    RwReal sub_11D690();
    // Sets that fraction (the player's movement raises it to the stick's).
    void sub_11D650(RwReal arg_0);
    // Called on each copy by the player's take-down before any is deleted;
    // only known by its width.
    void sub_117050();
    // Readies it (the player's system start passes 1 and 1); only known by
    // its widths.
    bool sub_1170B0(RwInt32 arg_0, RwInt32 arg_4);
    // Takes the stance arg_0 (the player's vf_238 passes 0 for arg_4); only
    // known by its widths.
    bool sub_119830(RwInt32 arg_0, RwInt32 arg_4);
    // Puts it away (the weapon change); only known by its width.
    bool sub_117370();
    // Whether it allows a stance change now; only known by its width.
    bool sub_1175D0();
    // Whether it may fire now, and whether it may be aimed (the player's
    // posture and its states); only known by their widths.
    bool sub_117460();
    bool sub_117510();
    // Ends its recoil into the stance's sway (sub_11D740; arg_0 picks the
    // aimed sway); only known by its callers' widths.
    void sub_11D740(bool arg_0);
    // The sequence event's step (sub_11CF50); only known by its width.
    void sub_11CF50(struct type_10F710 *arg_0);
    // The rumble for weapons 4 and 8 (sub_119050, from vf_018).
    void sub_119050();
    // Plays its settings' animation unk_5C on the player and marks it busy
    // (the player's update); only known by its width.
    void sub_1190B0();
    // An inline accessor for unk_448, with no address and so no database
    // name; named for its field. Evidence: the player's start reads the
    // settings through a temporary of its own each time.
    type_4C19C0 *get_unk_448()
    {
        return unk_448;
    }
    // Likewise for unk_428, through a result local (sub_110A60 copies its
    // clump through a temporary).
    RpClump *get_unk_428()
    {
        RpClump *r = unk_420.unk_08;
        return r;
    }
    // Likewise for unk_41C (sub_110A60 tests it through a byte temporary).
    RwUInt8 get_unk_41C()
    {
        return unk_41C;
    }
    // Likewise for unk_41E (sub_108BC0 tests it through a byte temporary).
    RwUInt8 get_unk_41E()
    {
        return unk_41E;
    }
    // Likewise for unk_450 and unk_454 (the particle callbacks' turn and
    // scale, sub_119BA0).
    RwReal get_unk_450()
    {
        return unk_450;
    }
    RwReal get_unk_454()
    {
        return unk_454;
    }
    // Likewise for unk_458 (the stance change reads the weapon in hand's
    // kind through it, which loads the index before the array).
    RwInt32 get_unk_458()
    {
        return unk_458;
    }
    // Likewise for unk_45C (the weapon change).
    RwInt32 get_unk_45C()
    {
        return unk_45C;
    }
};
typedef RwChar type_10F710_1A48_size_check[sizeof(type_10F710_1A48) == 0x470 ? 1 : -1];

// The three kinds of weapon copy sub_116490 builds besides the base, named
// for their vtables (their constructors inline there). Their destructors are
// compiler-written and identical, so /OPT:ICF kept one (sub_116850, with its scalar
// deleting destructor sub_1166D0).
//   type_3DA510  weapons 0, 1, 27, 28
//   type_3DA558  weapons 29, 35 (no vf_010 or vf_014: sub_1E4AA0)
//   type_3DA5A0  weapons 19 to 22, 31, 33, 34, 38 (likewise), 0x480 bytes
struct type_3DA510 : type_10F710_1A48
{
    virtual bool vf_004(struct type_10F710 *arg_0, RpClump *arg_4, RwInt32 arg_8, RwInt32 arg_C);
    // Fires (sub_11C540); see its definition.
    virtual bool vf_018();
};

// The mounted kind (unk_45C 4).
struct type_3DA558 : type_10F710_1A48
{
    virtual bool vf_004(struct type_10F710 *arg_0, RpClump *arg_4, RwInt32 arg_8, RwInt32 arg_C);
    // Fires (sub_11B9C0); see its definition.
    virtual bool vf_018();
    // vf_010, as the image's vtable has it (a trivial body, folded into
    // sub_1E4AA0 with every other copy).
    virtual bool vf_010()
    {
        return false;
    }
    // vf_014, as the image's vtable has it (a trivial body, folded into
    // sub_1E4AA0 with every other copy).
    virtual bool vf_014()
    {
        return false;
    }
};

// The launcher kind (unk_45C 2): loaded, then fired by its animation's
// event 1900 (sub_11B040), then back to the weapon before.
struct type_3DA5A0 : type_10F710_1A48
{
    virtual bool vf_004(struct type_10F710 *arg_0, RpClump *arg_4, RwInt32 arg_8, RwInt32 arg_C);
    virtual bool vf_018();
    virtual void vf_030(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8);
    // Fires its projectile (sub_11B040); only known by its widths.
    void sub_11B040(RwInt32 arg_0, RwInt32 arg_4);
    // Loads it (sub_11B870, the base's event handler at a weapon change to
    // it); arg_0 is unused.
    void sub_11B870(RwReal arg_0);

    RwInt32 unk_470;            // cleared when the player dies with it; set
                                // while loaded
    RwInt32 unk_474;            // loading
    RwInt32 unk_478;            // fired
    RwInt32 unk_47C;            // loaded from a change (picks the animation)
    // vf_010, as the image's vtable has it (a trivial body, folded into
    // sub_1E4AA0 with every other copy).
    virtual bool vf_010()
    {
        return false;
    }
    // vf_014, as the image's vtable has it (a trivial body, folded into
    // sub_1E4AA0 with every other copy).
    virtual bool vf_014()
    {
        return false;
    }
    // vf_020, as the image's vtable has it (a trivial body, folded into
    // sub_2015D0 with every other copy).
    virtual bool vf_020()
    {
        return true;
    }
};
typedef RwChar type_3DA5A0_size_check[sizeof(type_3DA5A0) == 0x480 ? 1 : -1];
// How far the launcher's projectile starts along the camera's at row
// (.data; sub_11B040).
extern RwReal dword_429B64;

// type_10F710_2178: the player's ladder state (type_10F710::unk_2178), as
// "SetLadderMovement" reads it.
struct type_10F710_2178
{
    RwUInt8 unk_00[0x60];
    RwMatrix unk_60;            // its placing: climbed along up (sub_114AA0)
    RwUInt8 unk_A0[0x38];
    RwInt32 unk_D8;             // the ladder movement ("SetLadderMovement")

    // An inline setter for unk_D8, with no address and so no database name;
    // named for its field. Evidence: "SetLadderMovement" stores through a
    // temporary holding unk_2178 (the inline's `this`).
    void set_unk_D8(RwInt32 arg_0)
    {
        unk_D8 = arg_0;
    }
};

struct type_10F710 : type_3D3548
{
    // Built for the trigger arg_0 (sub_FD730): its members, then its set-up
    // (sub_FDC10, "Player::Init()" in its messages). Defined here and not
    // expanded: the network player's constructors (sub_1B7C30, sub_1BABA0)
    // call it and reserve its expansion's ten slots.
    type_10F710(type_712B0 *arg_0)
    {
        sub_FDC10(arg_0);
    }
    RwInt32 sub_FDC10(type_712B0 *arg_0);
    // Takes it down (vf_230), then its members' destructors run (sub_FDB30;
    // its scalar deleting destructor is sub_FDB00). Defined here and not
    // expanded: the network player's destructors reserve its six slots.
    ~type_10F710()
    {
        vf_230();
    }

    // Overrides (src/recovered/unit_0FD730.cpp).
    virtual void vf_038(RwReal arg_0);
    // Its step (sub_101550, unit_0FD730) and its step after the others'
    // (sub_105B00, not yet matched), which the network player's overrides
    // call.
    virtual void vf_03C(RwReal arg_0);
    // Its collision step (sub_113010).
    virtual void vf_044(RwReal arg_0);
    virtual void vf_04C(RwReal arg_0);
    virtual RwInt32 vf_080(RwInt32 arg_0, RpIntersection *arg_4, RwReal *arg_8, RwReal arg_C);
    virtual type_3D2E7C *vf_098();
    // +0x060 (sub_10EF70): touching a soldier, a vehicle, a player or a
    // solid entity it steps back out of it (a soldier's pelvis at its
    // height for one in AI state 0), and tells the script "BlockingEntity"
    // when that one stands close ahead of its camera; an entity with a
    // destroyed version it keeps as unk_2114.
    virtual RwInt32 vf_060(type_3D3548 *arg_0);
    // +0x064 (sub_10FEB0): a bullet's hit: unless its damage is off or it
    // still flashes, the shooter's blow, the damage (with a dying cry by
    // the hit's kind) unless invulnerable, a hurt sound, and a flash, blur
    // and shake when the shooter is in view; its AI turns to the shooter.
    virtual RwInt32 vf_064(struct type_75600 *arg_0);
    // +0x068 (sub_110310): an explosion's hit when it reaches it (1 when
    // out of range): damage by its zones (or falling off to its radius), the
    // shakes, the instigator's blow, a dying cry and the HUD's marker.
    virtual RwInt32 vf_068(struct type_758F0 *arg_0);
    virtual void vf_0C0(RwV3d *arg_0);
    // +0x040 (sub_1142B0): moves it for the time arg_0: its velocity unk_C0
    // turned by its frame into unk_D8 (a fall with gravity, slowed for the
    // time scale 2), its position (unk_434) and frame, its turn unk_E8; in
    // state 12 sub_113D90 moves it instead. It resets after a gap of frames.
    virtual void vf_040(RwReal arg_0);
    // State 12's movement (vf_040); only known by its widths.
    void sub_113D90(RwFrame *arg_0, RwReal arg_4);
    virtual void vf_210(struct type_D05C0 *arg_0);
    virtual RwInt32 vf_0AC();
    virtual void vf_104(RwMatrix *arg_0);
    virtual void vf_108(RwV3d *arg_0);
    virtual void vf_110(RwV3d *arg_0, type_3D3548 *arg_4, RwInt32 arg_8);
    virtual RwInt32 vf_160();
    virtual void vf_170(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C);
    virtual void vf_230();
    virtual void vf_220(type_3D3548 *arg_0, RwInt32 arg_4);

    // New virtuals. +0x234 (sub_1111A0) sends it along the spline arg_0 to
    // the point arg_4 (state 11, sub_10B930); +0x240 (sub_1112F0, a float
    // second) takes two arguments, only known by width; +0x244 (sub_105A10)
    // places its camera at its bone 1 (or its aim matrix unk_490 for weapons
    // 0x1D and 0x23 in a vehicle's seat 2), 0 without a frame or camera.
    virtual void vf_234(struct SplinePath *arg_0, RwV3d *arg_4);
    // +0x238: sets the player's posture ("SetPlayerPosture").
    virtual void vf_238(RwInt32 arg_0);
    // Overrides defined in the class (out-of-line places in unit_0FD730, where the
    // constructor's vtable emits them), in the image's order (0xFD8C0-0xFDAC0); vf_23C
    // is its own new virtual, so it keeps its place among them.
    virtual RwInt32 vf_09C()
    {
        return unk_54C;
    }
    virtual void vf_0A0(RwUInt32 arg_0)
    {
        unk_54C = arg_0;
    }
    virtual RwInt32 vf_138()
    {
        return unk_1B38;
    }
    virtual type_3D3548 *vf_118()
    {
        return unk_550.unk_54.sub_D4910();
    }
    virtual void vf_11C(type_3D3548 *arg_0)
    {
        unk_550.unk_54.sub_D48D0(arg_0);
    }
    virtual AIData *vf_120()
    {
        return &unk_550;
    }
    virtual RwInt32 vf_174()
    {
        return (RwInt32)(unk_19E0 * unk_19DC);
    }
    virtual void vf_178(RwInt32 arg_0)
    {
        unk_19DC = arg_0 / 100.0f;
    }
    virtual void vf_180(RwInt32 arg_0)
    {
        unk_19DC += arg_0 / 100.0f;
    }
    virtual RwReal vf_17C()
    {
        return unk_19DC;
    }
    virtual void vf_23C(RwReal arg_0)
    {
        unk_19DC = arg_0;
    }
    virtual RwReal vf_10C()
    {
        return 5000.0f;
    }
    virtual RwReal vf_0FC()
    {
        return unk_53C;
    }
    virtual RwReal vf_100()
    {
        return unk_540;
    }
    virtual RwInt32 vf_0BC()
    {
        return unk_1A04;
    }
    virtual RwInt32 vf_1E4()
    {
        return unk_19D0 == 5 && unk_4D0 == 1;
    }
    // +0x23C: sets the player's health, a percentage
    // ("SetPlayerHealthPercentage").
    // +0x240: bobs the view offset arg_0 for the time arg_4 as it walks
    // (sub_111220 with its trigger's unk_204 to unk_228).
    virtual void vf_240(RwV3d *arg_0, RwReal arg_4);
    virtual RwInt32 vf_244();
    // +0x248: whether the entity arg_0 is an ally it may target (not the one
    // vf_200 gives); +0x24C: whether it is an enemy.
    virtual RwInt32 vf_248(type_3D3548 *arg_0);
    virtual RwInt32 vf_24C(type_3D3548 *arg_0);
    // Empty: folded (/OPT:ICF) into sub_15FB30. They take the time step:
    // the network player's defuse and plant (sub_1BA700, sub_1BA810).
    virtual void vf_250(RwReal arg_0);
    virtual void vf_254(RwReal arg_0);
    // +0x258 (sub_10DBD0): sways the weapon in hand for the time arg_0 by
    // its settings for the stance (blending a stance change), with the
    // sticks, and resets its clump's frame; it also ends its sound and
    // cooling states. Its last new slot: the second network player
    // overrides it (sub_1BBFB0).
    virtual void vf_258(RwReal arg_0);

    RwUInt8 unk_3A8[0x8];
    RwInt32 *unk_3B0;           // set with unk_1C0 by sub_83850 (kind 7) at
                                // the start
    RwUInt8 unk_3B4[0x20];
    RwInt32 unk_3D4;            // passed to sub_1745C0 by its take-down
    RwInt32 unk_3D8;            // its pad (the aim assist reads its stick)
    RwInt32 unk_3DC;            // the player's index (dword_4F28F0's unk_1C at
                                // its set-up; sub_FEFE0)
    RwReal unk_3E0;             // set to 45 by a stance change
    RwReal unk_3E4;             // reset each frame (vf_038) to 1e37
    RwReal unk_3E8;             // and -2
    RwReal unk_3EC;
    RwReal unk_3F0;             // the look's pitch speed (sub_10A330)
    RwReal unk_3F4;
    RwReal unk_3F8;             // and its spring's velocity
    RwReal unk_3FC;             // the strafe's turn (sub_109AE0)
    RwReal unk_400;             // and its spring's velocity
    // The view's bob (vf_240): a lift springing back to rest with its
    // velocity, the two swings' phases, a dip by the stick with its
    // velocity.
    RwReal unk_404;
    RwReal unk_408;
    RwReal unk_40C;
    RwReal unk_410;
    RwInt32 unk_414;
    RwReal unk_418;
    RwReal unk_41C;
    RwReal unk_420;             // the height it has moved by (vf_0C0)
    RwInt32 unk_424;            // the frame it last moved on (vf_040)
    RwReal unk_428;             // a countdown to jumping again (sub_10A9D0)
    RwInt32 unk_42C;            // its fall was slowed for the time scale 2
    RwInt32 unk_430;            // it was in state 12 (vf_040)
    RwV3d unk_434;              // its position when last placed (vf_0C0)
    RwV3d unk_440;
    // The aim assist (sub_100AD0): the turn's scale, counters, the stick's
    // last turns, the point aimed at and the range scale.
    RwReal unk_44C;
    RwInt32 unk_450;
    RwInt32 unk_454;            // a target is assisted
    RwInt32 unk_458;
    RwInt32 unk_45C;
    RwInt32 unk_460;
    RwReal unk_464;             // the stick's turn
    RwReal unk_468;             // and the one before
    RwInt32 unk_46C;
    RwReal unk_470;             // the yaw scale near a target
    RwV3d unk_474;              // the point it aims at
    RwReal unk_480;
    RwUInt8 unk_484[0xC];
    RwMatrix unk_490;           // an aim matrix (vf_244)
    RwInt32 unk_4D0;            // the posture in a vehicle
                                // ("VehicleGetPlayerPosture")
    RwInt32 unk_4D4;            // the posture it is switching to (the
                                // tank's seat switch, sub_1571E0)
    RwInt32 unk_4D8;            // cleared, with unk_4DC and unk_4E8, entering
    RwReal unk_4DC;             // a kind-1 vehicle (sub_10F900), whose view
    RwReal unk_4E0;             // starts at its field of view (unk_534)
    RwReal unk_4E4;
    RwReal unk_4E8;             // the view's zoom speed (the tank's vf_03C,
                                // sub_141700)
    RwReal unk_4EC;
    RwReal unk_4F0;             // a sideways sway and its spring's
    RwReal unk_4F4;             // velocity (the second player's vf_240)
    RwInt32 unk_4F8;
    RwReal unk_4FC;             // the scope's sway angles, in degrees
    RwReal unk_500;             // (sub_1116A0), and its offsets from them
    RwReal unk_504;
    RwReal unk_508;
    RwInt32 unk_50C;            // set while the offsets decay
    RwReal unk_510;             // the highest point of a fall (vf_044)
    RwInt32 unk_514;            // counts its landings (vf_044)
    RwReal unk_518;             // how long it has fallen (vf_044); cleared
                                // entering state 12 (vf_040)
    RwInt32 unk_51C;            // cleared when it takes a ladder
    RwInt32 unk_520;            // set while a pulse zone's charge holds it
                                // (unit_17D590)
    // An inline setter for unk_520, with no address and so no database
    // name; named for its field. Evidence: the pulse zones store their
    // constants through a register (a substituted argument).
    void set_unk_520(bool arg_0)
    {
        unk_520 = arg_0;
    }
    RwReal unk_524;             // its eye height by stance (flt_429B10)
    RwReal unk_528;             // its spring's velocity (vf_044)
    RwReal unk_52C;             // a time the HUD's hit marker lasts (vf_240)
    RwReal unk_530;             // its look's pitch, -89 to 89 degrees
    RwReal unk_534;             // its camera's field of view (the HUD's
                                // render, type_DC400::sub_DF000)
    RwReal unk_538;             // a scale of the screen the HUD places its
                                // name labels by
    RwReal unk_53C;             // vf_0FC
    RwReal unk_540;             // vf_100
    RwReal unk_544;             // the pitch within the bipod's range
    RwReal unk_548;             // the yaw within it
    RwInt32 unk_54C;            // vf_09C, vf_0A0
    AIData unk_550;             // its AI (vf_120; vf_118 and vf_11C through
                                // its unk_54)
    RwInt32 unk_19D0;           // the player's posture: 7 on a mounted weapon
                                // ("AreWeUsingAMountedWeapon",
                                // "IsPlayerUsingAMountedWeapon")
    RwInt32 unk_19D4;           // counts the frames of one movement state
    RwInt32 unk_19D8;           // the bipod's animation state (sub_109110)
    RwReal unk_19DC;            // its health, a fraction (vf_17C; the hit
                                // points are it times unk_19E0)
    RwInt32 unk_19E0;           // its full hit points
    RwReal unk_19E4;            // the hurt flash's times (vf_064 restarts
    RwReal unk_19E8;            // unk_19EC and unk_19F0 from them)
    RwReal unk_19EC;
    RwReal unk_19F0;
    RwInt32 unk_19F4;           // which death animation, 1 or 2 (vf_028)
    RwInt32 unk_19F8;           // while positive, no weapon change (set by
                                // the dying states)
    RwInt32 unk_19FC;           // whether its damage is off
                                // ("DisablePlayerDamage")
    RwReal unk_1A00;            // an eye height "IsTargetWithinDefendArea"
                                // takes off the player's position
    RwInt32 unk_1A04;           // the stance: indexes its weapons' spread
                                // (type_4C19C0::unk_308, unk_314)
    RwInt32 unk_1A08;           // the stance before (vf_238)
    RwUInt8 unk_1A0C;           // set by a stance change
    RwUInt8 unk_1A0D[0x3];
    RwReal unk_1A10;            // how far a stance change has blended
    RwUInt8 unk_1A14[0x4];
    RwReal unk_1A18;            // the stance change's rate (1 over 30 times
                                // its animation's length; sub_119830)
    RwInt32 unk_1A1C;           // whether it is confined ("SetPlayerConfined")
    RwReal unk_1A20;            // from its trigger at the start (the aim
    RwReal unk_1A24;            // assist's base by posture)
    RwReal unk_1A28;
    RwUInt8 unk_1A2C[0x4];
    RwReal unk_1A30;            // the aim assist's result
    type_D48D0 unk_1A34;        // the player's target (type_3D410's scan
                                // sub_3D7D0 counts it for the group)
    RwReal unk_1A38;            // the strafe's turn toward its target, in
                                // degrees (sub_1097C0; the aim assist clears
                                // it)
    type_129940 unk_1A3C;       // a clump it holds
    type_10F710_1A48 *unk_1A48[39]; // its copies of the weapons, by the
                                    // index of their settings (type_4C19C0)
    RwInt32 unk_1AE4;           // the weapon in hand, an index into unk_1A48
    RwInt32 unk_1AE8;           // whether the weapon in hand is other than
                                // unk_1B30[0]
    RwInt32 unk_1AEC;           // the weapon in hand while vf_1E4 holds
    RwInt32 unk_1AF0;           // the weapon before a quick select
    RwReal unk_1AF4;            // an angle (wrapped by a stance change)
    RwV3d unk_1AF8;             // the weapon's sway (vf_258)
    RwInt32 unk_1B04;           // picks the recoil settings (vf_038)
    RwInt32 unk_1B08;           // ends the recoil at once
    RwInt32 unk_1B0C;           // aiming with the second settings
    RwInt32 unk_1B10;           // set when a reload starts while aiming
    RwInt32 unk_1B14;           // cleared when a weapon is put away
    RwInt32 unk_1B18;           // cleared when the weapon has cooled
    RwInt32 unk_1B1C;           // (vf_258) with unk_1B1C
    RwInt32 unk_1B20;           // set as a fire starts (the second
    RwInt32 unk_1B24;           // network player's step), with its count
    RwInt32 unk_1B28;           // "SetMyMMGYawAndPitch" requires it set to
                                // reach the mounted weapon through unk_210C
    RwInt32 unk_1B2C;
    RwInt32 unk_1B30[2];        // from its trigger at the start
    RwInt32 unk_1B38;           // vf_138
    RwInt32 unk_1B3C;           // sub_1014E0; its weapon off (sub_10E750)
    // An inline setter for it, with no address and so no database name;
    // named for its field. Evidence: the network player (sub_1A6F50) sets
    // it through a copy of its pointer with the value widened into a
    // register, as a bool argument gives.
    void set_unk_1B3C(bool arg_0)
    {
        unk_1B3C = arg_0;
    }
    RwInt32 unk_1B40;           // the crosshair off (sub_10E750)
    RwInt32 unk_1B44;           // set when the weapon needs reloading; the
                                // step reloads it (vf_020) and clears it
    RwInt32 unk_1B48[39][3];    // per weapon, three values sub_106830 tests
    RwChar unk_1D1C[39][0x18];  // its weapons' names (the network player
                                // flashes one picked up, sub_1B91E0)
    // The recoil (sub_1116A0): the kicks for the pitch and the yaw, their
    // springs' positions and velocities (sub_112DA0), and the fires left
    // before a kick for the kinds that count them (unk_20DC).
    RwReal unk_20C4;
    RwReal unk_20C8;
    RwReal unk_20CC;
    RwReal unk_20D0;
    RwReal unk_20D4;
    RwReal unk_20D8;
    RwInt32 unk_20DC;           // cleared with unk_1B24 when not aiming
    RwReal unk_20E0;            // the look's pitch at a burst's first fire
    RwReal unk_20E4;            // and the view's heading then, in degrees
    RwInt32 unk_20E8;           // set during a burst
    RwInt32 unk_20EC;           // set once the weapon's settings' animation
                                // unk_8C played, cleared at a fire (the step)
    RwReal unk_20F0;            // button 3's value at the last step
    RwInt32 unk_20F4;           // set while button 3 stays down (the step)
    RwInt32 unk_20F8;           // the weapon to change to (-1 for none;
                                // sub_100560)
    struct type_44C4E8 *unk_20FC;   // its footstep's voice
    RwReal unk_2100;            // the time to the next footstep
    type_D48D0 unk_2104;        // the player's buddy ("SetPlayerBuddy")
    type_D48D0 unk_2108;
    type_D48D0 unk_210C;        // the entity whose vf_028 is the player's
                                // mounted weapon ("SetMyMMGYawAndPitch")
    type_D48D0 unk_2110;        // the player's camera (the script command
                                // "CameraShake", sub_44AD0)
    type_D48D0 unk_2114;
    type_D48D0 unk_2118;
    RwV3d unk_211C;             // the end of the spline it follows
    struct SplinePath *unk_2128;    // the spline it follows (sub_10B930)
    RwReal unk_212C;            // how far along
    RwReal unk_2130;            // where it ends
    RwInt32 unk_2134;           // its weapon streaming slot (sub_10DA70)
    RwInt32 unk_2138;           // 0 after "RequestToStreamPlayerWeapon", 1
                                // after "RemovePlayerWeapon"
    RwV3d unk_213C;             // where it leaves a vehicle for
                                // ("PlayerExitVehicleTransition")
    RwReal unk_2148;            // while nonzero, unk_2150 replaces the
    RwReal unk_214C;            // forward stick (sub_109110; unk_214C the
                                // turning one); sub_10C290
    RwReal unk_2150;            // clears the five
    RwReal unk_2154;            // the time in the exit state (sub_10BB30)
    RwReal unk_2158;            // replaces the look stick while unk_2148
    RwInt32 unk_215C;           // keeps unk_28's movement flags (sub_10AEB0)
    RwReal unk_2160;            // cleared, with unk_2164 (arg 4 times 60)
    RwReal unk_2164;            // and unk_2168 (its trigger volume's first
    RwV3d unk_2168;             // point) set, by "PlayerEnterVehicleTransition"
    type_D48D0 unk_2174;
    struct type_10F710_2178 *unk_2178;  // its ladder ("SetLadderMovement")
    RwInt32 unk_217C;           // while set the launcher does not fire
    type_D48D0 unk_2180;        // the vehicle it is in (sub_10F8A0)
    RwInt32 unk_2184;           // its seat
    struct type_4CFE30 *unk_2188;   // the vehicle trigger near it
    RwInt32 unk_218C;           // the seat it entered (sub_10F900)
    RwUInt8 unk_2190[0xC];
    RwReal unk_219C[3];         // by stance: its collision height
    RwReal unk_21A8[3];         // and its centre's rise above its bone 1
    type_10F710_21B4 unk_21B4;  // the player's inventory
    RwInt32 unk_21F0[20];
    RwInt32 unk_2240;
    RwInt32 unk_2244;           // while set, the step's weapon change (button
                                // 13) and inventory use (button 14) wait
    RwInt32 unk_2248;           // button 29's setting and button 30's
    RwInt32 unk_224C;           // at its set-up (the pad manager's sub_EED00)
    RwInt32 unk_2250;           // whether its stealth message shows
                                // ("PlayerStealthMessageActive")
    RwInt32 unk_2254;           // set by its set-up (sub_FDC10)
    RwInt32 unk_2258;
    RwUInt8 unk_225C[0x4];

    // The first of its twenty flags (unk_21F0) set, while unk_2240 is and
    // button 15 is pressed; 19 otherwise.
    RwInt32 sub_10F710();
    // The first set whatever the button (19 for none).
    RwInt32 sub_10F790();
    // Its vehicle's type_3DBC78 (vf_010 of unk_2180), 0 without one.
    // +0x200: its override (sub_10F860), as its vtable has it.
    virtual type_3D3548 *vf_200();
    // Whether the player is near the bomb site of the performance map arg_0
    // (arg_4; "SetBombSiteInProximity"); only the widths are known.
    void sub_1BA910(struct type_4CFE30 *arg_0, bool arg_4);
    // Likewise for the capture-flag base ("SetCaptureFlagBaseInProximity").
    void sub_1BA980(struct type_4CFE30 *arg_0, bool arg_4);
    // An inline accessor for unk_19D0, with no address and so no database
    // name; named for its field. Evidence: sub_46E40 and sub_46EF0 test it
    // through a temporary of its own.
    RwInt32 get_unk_19D0()
    {
        return unk_19D0;
    }
    // Likewise, through a local of its own: type_3D32F8's sub_75CB0 copies
    // the posture into its own local through a temporary, which an
    // assignment from the accessor above does not give.
    // An inline accessor for unk_538, with no address and so no database
    // name; named for its field. Evidence: the HUD's render
    // (type_DC400::sub_DF000) reads it inside a conditional through a result
    // slot of its own.
    RwReal get_unk_538()
    {
        return unk_538;
    }
    // Likewise for unk_534: sub_FF1A0 hands it to the camera through a
    // temporary of its own.
    // Likewise for unk_3EC, through a local of its own: the aim assist
    // (sub_100AD0) takes its magnitude from a temporary.
    RwReal get_unk_3EC()
    {
        RwReal r = unk_3EC;
        return r;
    }
    RwReal get_unk_534()
    {
        return unk_534;
    }
    // Likewise for unk_1AE4 (the rounds display, sub_115390).
    // Likewise for unk_1AEC (sub_10FBF0 restores the weapon in hand from it
    // through a temporary of its own).
    RwInt32 get_unk_1AEC()
    {
        RwInt32 r = unk_1AEC;
        return r;
    }
    RwInt32 get_unk_1AE4()
    {
        RwInt32 r = unk_1AE4;
        return r;
    }
    // The same index through a direct return (no local): an inline with no
    // address and so no database name, named for what it gives. Evidence:
    // a grenade's start (type_3DC8B8::vf_000) copies a garbage slot into the
    // conditional's temporary before the field, as direct returns do.
    RwInt32 hand_index()
    {
        return unk_1AE4;
    }
    // Its weapon in hand (unk_1A48[unk_1AE4]): an inline with no address
    // and so no database name, named for what it gives. Evidence: the
    // weapon copies' event handler (vf_030) reads it through a `this`
    // temporary holding the player, the index loaded first.
    struct type_10F710_1A48 *get_hand()
    {
        return unk_1A48[unk_1AE4];
    }
    // The weapon in hand's sub_117370 and sub_1170B0: inlines with no
    // address and so no database names, named for what they call.
    // Evidence: the second network player's part (sub_1BCE50) calls each
    // through a `this` temporary holding the player (in the player's own
    // members they expand to the plain calls).
    void hand_117370()
    {
        unk_1A48[unk_1AE4]->sub_117370();
    }
    void hand_1170B0(RwInt32 arg_0, RwInt32 arg_4)
    {
        unk_1A48[unk_1AE4]->sub_1170B0(arg_0, arg_4);
    }
    // Its camera (unk_2110's entity), through a result local: an inline
    // with no address and so no database name. Evidence: the explosion's
    // hit (vf_068) keeps it in a temporary after the posture tests' own.
    struct type_3DD948 *get_unk_2110()
    {
        struct type_3DD948 *r = (struct type_3DD948 *)unk_2110.sub_D4910();
        return r;
    }
    RwInt32 get_unk_19D0_r()
    {
        RwInt32 r = unk_19D0;
        return r;
    }
    // Shocks the player (the script command "PlayerShock", sub_44C70,
    // passes its second argument and 1.0f); only the widths are known.
    void sub_1109A0(RwReal arg_0, RwReal arg_4);
    // An explosion's shake at the distance arg_0: within arg_10 its camera
    // shakes (arg_C scaled by arg_14, for arg_18 and arg_1C), within arg_8
    // the screen blurs and the pad rumbles by arg_4.
    void sub_110900(RwReal arg_0, RwReal arg_4, RwReal arg_8, RwReal arg_C, RwReal arg_10, RwReal arg_14,
                    RwReal arg_18, RwReal arg_1C);
    // Shakes its camera by arg_0 (for three times as long, sub_175E50).
    void sub_110A10(RwReal arg_0);
    // Whether a vehicle is near the player, of the map entry arg_0 (any for
    // 0; "VehicleInProximity"); only the widths are known.
    // Lock its movement and set its state ("LockPlayerMovement",
    // "SetPlayerState"); only the widths are known.
    void sub_108FF0(RwInt32 arg_0);
    // Fills the save's copy of its state (the checkpoint save, sub_D8F80).
    void sub_111040(struct type_D90B0 *arg_0);
    // Resets the camera zoom ("ResetCameraZoom").
    void sub_104F70();
    void sub_1090F0(RwInt32 arg_0);
    // Puts the player on (arg_0) or takes it off a moving platform;
    // type_3D32F8's sub_75CB0 passes 0 and 0. Only the widths are known.
    void sub_10F8A0(type_3D3548 *arg_0, RwInt32 arg_4);
    // Levels its frame (its at and right rows flattened, then made
    // orthonormal); 1 when it is level already, 0 without a frame, else 2.
    RwInt32 sub_FF030();
    // Copies the player's entry of dword_4F2AAC into the four records of
    // dword_4F4638's unk_50.
    void sub_FEFE0();
    // Enters the vehicle arg_0 (seat arg_4; sub_10F900), or with 0 leaves its
    // own (sub_10FBF0); its take-down passes 0 and 0.
    void sub_10F810(type_3D3548 *arg_0, RwInt32 arg_4);
    // On a ladder: leaves it (state 0) when its feet are out of the ladder's
    // volume, or for state 2 once it stands on the ground; arg_0 unused.
    void sub_114E70(RwReal arg_0);
    // Climbing a ladder for the time arg_0: along its up axis at the forward
    // input's speed (reversed looking down past -15 degrees, stopped by its
    // movement 3, 1 downward or 2 upward), springing each coordinate there;
    // the jump input leaves it (state 1).
    void sub_114AA0(RwReal arg_0);
    // Tells the script "PlayerBlewStealth" while unk_2250 is set.
    void sub_114F50();
    // The shake of the explosion arg_0 at arg_4: its camera's and the
    // player's, each fading with the distance to its range.
    void sub_114F90(struct type_114F90 *arg_0, RwV3d *arg_4);
    // Adds arg_0 to its health fraction, within 0 to 1.
    void sub_1150A0(RwReal arg_0);
    // The world of its weapon in hand's clump.
    struct RpWorld *sub_111000();
    // Builds its camera (type_3DD948) above it and keeps its handle in
    // unk_2110.
    void sub_FF1A0();
    // Its start from its trigger ("Player::SystemStartInit()" in its
    // message): the camera, the weapons and their rounds, the inventory, its
    // script object and squad.
    void sub_FF210();
    // Called by it: sub_10C650 builds its model from its trigger's key
    // (unk_CC, a clump object of kind 3) into unk_1A3C, the other is only
    // known by its width.
    void sub_10C650();
    // Rebuilds its 39 weapon copies (sub_116490), deleting the old ones,
    // with its trigger's flags (unk_114) for which to give geometry, and
    // pairs 29 with 30 and 35 with 36 ("Allocated %d bytes for %d
    // CPlayerWeapon classes.").
    void sub_10D8A0();
    // Selects the weapon arg_0 (-1 for none): puts the one in hand away (a
    // dropped one at once, telling the script "PickedUpWeapon"), warning of
    // missing select and deselect animations, then changes at once if one
    // is missing.
    void sub_100200(RwInt32 arg_0);
    // Changes to the weapon unk_20F8 (unless unk_19F8 holds it off).
    void sub_100560();
    // The forward movement from the stick (scaled by arg_0 forwards and
    // arg_4 backwards; arg_8, the frame's time, unused), and the bipod
    // stance's animations ("WARNING: Missing start anim", "... idle anim").
    void sub_109110(RwReal arg_0, RwReal arg_4, RwReal arg_8);
    // The sideways movement from the stick (scaled by arg_0; arg_4, the
    // frame's time, unused).
    void sub_109660(RwReal arg_0, RwReal arg_4);
    // The same with a target (unk_1A34): with the trigger's unk_348 the
    // strafe turns about it (unk_1A38, the camera's heading against the
    // target's direction, within unk_350).
    void sub_1097C0(RwReal arg_0, RwReal arg_4);
    // Two movement states' updates over the frame's time arg_0: the
    // trigger's speeds and movement vectors, then the forward, sideways,
    // turning and looking inputs (sub_109110, sub_109660, sub_10A330,
    // sub_109AE0), state 3 when bit 1 of unk_28 is set; the first counts its
    // frames and settles the weapon's spread, the second keeps unk_28 while
    // unk_215C is set.
    void sub_10AD70(RwReal arg_0);
    void sub_10AEB0(RwReal arg_0);
    // The look's pitch from the stick (arg_0 its speed, arg_4 the frame's
    // time): a vehicle's seat turns the vehicle, a mounted weapon its pitch
    // with its springs, else its own within the bipod's range; -89 to 89.
    void sub_10A330(RwReal arg_0, RwReal arg_4);
    // More movement states: crouched (by stance, state 14 or 0 when bit 1 of
    // unk_28 is set), in a vehicle's seat (unk_2180 steered by the sticks),
    // a passenger's (turning its frame by unk_E8), and on a mounted weapon
    // (unk_210C zoomed by button 6).
    void sub_10AFD0(RwReal arg_0);
    void sub_10B120(RwReal arg_0);
    void sub_10B2E0(RwReal arg_0);
    void sub_10B410(RwReal arg_0);
    // Two dying states: the crouched movement vectors, the second first
    // putting the weapon away (back to unk_1AF0's while unk_1B2C is set),
    // the music's stops and leaving the recoil's second settings.
    void sub_10B6F0(RwReal arg_0);
    void sub_10B790(RwReal arg_0);
    // The state 12 and 14 steps (the step's switch); only the widths are
    // known.
    void sub_10B560(RwReal arg_0);
    void sub_10BB30(RwReal arg_0);
    // The spline state: moves it along unk_2128 by a thousandth of its
    // length each frame to unk_2130 (button 15 leaves it).
    void sub_10B930(RwReal arg_0);
    // The on-foot state: the stance's speeds (scaled with the recoil's
    // second settings), the aim-assisted strafe while a target is held, the
    // jump (button 4, state 1, its sound) and the footsteps.
    void sub_10A9D0(RwReal arg_0);
    // Leaves the forced movement (unk_2148 to unk_2158) for state 0, the
    // weapon on, playing its select animation.
    void sub_10C290();
    // Footsteps over the frame's time arg_0: the sticks' deflection runs the
    // time down to the stance's interval (flt_44D490, faster with the
    // recoil's second settings), then plays its surface's index sound at the
    // stance's volume (flt_44E814).
    void sub_10C370(RwReal arg_0);
    // Likewise the yaw (turning unk_E8, with the strafe's turn about a
    // target through its own spring, unk_3FC).
    void sub_109AE0(RwReal arg_0, RwReal arg_4);
    // Leaves the recoil's second settings (unk_1B04 off, unk_1B08 on): the
    // field of view back from its trigger, dword_4CF540 back to
    // dword_4CF468, and the weapon's recoil folded into its aim.
    void sub_1062A0();
    // The weapon of the pick-up settings index arg_0 (-1 for none).
    RwInt32 sub_1068A0(RwInt32 arg_0);
    // Shows the weapon in hand's rounds (sub_115390).
    void sub_108B60();
    // Selects the weapon of the quick-select slot arg_0 (2, 5, 7 to 12) if it
    // may be; arg_4 unused.
    void sub_108BC0(RwInt32 arg_0, RwInt32 arg_4);
    // The same function as the second network player's step calls it, with
    // a float second argument (it pushes 1.0f's bits; the function ignores
    // it): aliased to 0x108BC0.
    void sub_108BC0(RwInt32 arg_0, RwReal arg_4);
    // The soldier under the crosshair within arg_0 (the HUD's name and
    // health colour, sub_1BAE40), or 0; only the width is known.
    struct type_3DAFC8 *sub_108CC0(RwReal arg_0);
    // The aim in and out, and the step's last part; only the widths are
    // known.
    void sub_104FF0(RwReal arg_0);
    void sub_10C7B0(RwReal arg_0);
    // Leans the root's rotation arg_0 by the stick (the pose, sub_10C7B0);
    // only the widths are known.
    void sub_1116A0(RtQuat *arg_0, RwReal arg_4);
    // The inventory kind of weapon arg_0 (3 for others).
    RwInt32 sub_1064C0(RwInt32 arg_0);
    // Whether the weapon of the pick-up arg_0 is streamed, requesting it if
    // not (1 for pick-ups that are not weapons, 0 without one).
    RwInt32 sub_106620(struct type_3D94B8 *arg_0);
    // Takes the pickup arg_0 it stands on (the late step, when sub_106620
    // allows); only the width is known.
    void sub_106A60(struct type_3D94B8 *arg_0);
    // Flag 15 (a stealth kill's prompt): set while its target (unk_1A34), an
    // AI within 300 of it on its side, is one whose AI allows it; on the
    // way, while flag 15 is the one shown, it alerts the target's AI and
    // those of the entities within 300 of the target.
    void sub_1048E0();
    // Changes stance by the stick's down (arg_0) and up (arg_4), unless
    // there is no room to stand (sub_115230 at the frame raised by 65 or 85)
    // or it is confined (unk_1A1C 2); 1 and 3 are two confinements' orders.
    void sub_104480(RwReal arg_0, RwReal arg_4);
    // Whether arg_0 is one of weapon arg_4's three values in unk_1B48 (1 to
    // 38 only).
    RwInt32 sub_106830(RwInt32 arg_0, RwInt32 arg_4);
    // Draws the crosshair (HUD element 0x5A): along the gun in a vehicle's
    // seat 2, offset on a mounted weapon of kind 2, else at the HUD's place.
    void sub_100680();
    // Draws its clumps for the pass arg_0 (sub_125F20; only the width is
    // known): its model's (unless a sniper's scope is up or in a vehicle's
    // gun) and the weapon's, through sub_110EC0, with weapon 4's bone twist;
    // on a mounted weapon that one draws itself (sub_1679C0).
    void sub_110A60(RwInt32 arg_0);
    // Keeps the vehicle trigger arg_0 as the one near it when it accepts the
    // player (sub_BF470), or none for 0.
    void sub_10F8D0(struct type_4CFE30 *arg_0);
    // The player's weapon commands, only known by width: on or off
    // ("TurnPlayerWeaponOnorOff"), the crosshair on or off
    // ("TurnCrosshairOnorOff"), whether weapon arg_0 is streamed
    // ("IsPlayerWeaponStreamed"), streaming it ("RequestToStreamPlayerWeapon")
    // and removing it ("RemovePlayerWeapon").
    void sub_10E750(RwInt32 arg_0, RwInt32 arg_4);
    void sub_10E880(RwInt32 arg_0);
    RwInt32 sub_10E8C0(RwInt32 arg_0);
    // Weapon arg_0's streamed slot (sub_16F860 of its settings' unk_24).
    RwInt32 sub_10E900(RwInt32 arg_0);
    // The first of the three slots neither of its two weapons (unk_1B30)
    // takes, 2 when both are taken.
    RwInt32 sub_10E930();
    void sub_10DA70(RwInt32 arg_0);
    // Puts the player on the ladder arg_0 (LadderTrigger's sub_CAC30).
    void sub_114920(class LadderTrigger *arg_0);
    // Gives the player the weapon arg_0 in its slot arg_8 (0 the one in
    // hand, 1 the other), selecting it when arg_4 is set; -1 with arg_4 set
    // and slot 0 only turns its weapon on, with slot 1 and arg_4 clear it
    // empties the other slot. A weapon it has already swaps slots.
    void sub_10E9D0(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8);
    // Dismounts the player's mounted weapon ("DetachFromMountedWeapon") when
    // it may (unk_1B28, sub_169350); whether it did.
    RwInt32 sub_10FB70();
    // Sets flag arg_0 of unk_21F0 to arg_4.
    void sub_10F7E0(RwInt32 arg_0, RwInt32 arg_4);
    // Enter and leave a vehicle; only known by their widths.
    void sub_10F900(type_3D3548 *arg_0, RwInt32 arg_4);
    void sub_10FBF0();
    // vf_00C, as the image's vtable has it (a trivial body, folded into
    // sub_6FCD0 with every other copy).
    virtual type_10F710 *vf_00C()
    {
        return this;
    }
    // vf_054, as the image's vtable has it (a trivial body, folded into
    // sub_15FB30 with every other copy).
    virtual void vf_054(RwInt32 arg_0)
    {
    }
    // vf_058, as the image's vtable has it (a trivial body, folded into
    // sub_32260 with every other copy).
    virtual RwInt32 vf_058(struct type_3DF8D8_04 *arg_0)
    {
        return 0;
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
// The player's trigger as its take-down reads it: a key at +0x244 naming an
// object whose handle (+0x24) it clears. A view of type_712B0 (whose own
// fields end before it), named for the entity.
struct type_712B0_10F710 : Trigger
{
    RwUInt8 unk_C0[0xC];
    type_3DF8D8_04 unk_CC;      // its model's key (sub_10C650)
    RwUInt8 unk_D4[0x1C];
    RwReal unk_F0;              // a field of view the aim assist compares
    RwUInt8 unk_F4[0x14];
    RwInt32 unk_108[2];         // copied into the player's unk_1B30
    RwUInt8 unk_110[0x4];
    RwChar unk_114[39];          // per weapon: whether its copy gets
                                // geometry (the player's sub_10D8A0)
    RwUInt8 unk_13B;
    RwInt32 unk_13C;            // the weapon in hand at the start
    RwInt32 unk_140;            // the player's frame follows its movement
                                // (vf_040)
    // The movement speeds and settings of its states (sub_10AD70).
    union
    {
        struct
        {
            RwUInt8 unk_144[0x4];
            RwReal unk_148;     // the player's height on an animated entity
                                // (type_3DA6C0::sub_75AF0 adds 10 to it)
            RwUInt8 unk_14C[0x4];
            RwReal unk_150;     // the root's height (the player's pose,
                                // sub_10C7B0)
        };
        RwReal unk_144_a[3];    // by stance: the eye height (the second
                                // network player's vf_04C)
    };
    RwReal unk_154;
    RwReal unk_158;
    RwReal unk_15C;             // the look stick's dead zone
    RwUInt8 unk_160[0x4];
    RwReal unk_164[3];          // crouched, by stance: forwards
    RwReal unk_170[3];          // and backwards
    RwReal unk_17C;             // forwards
    RwReal unk_180;             // backwards
    RwV3d unk_184;              // crouched: into the entity's unk_10C
    RwV3d unk_190;              // into the entity's unk_10C
    RwV3d unk_19C;              // crouched: into its unk_134
    RwV3d unk_1A8;              // into its unk_134
    RwReal unk_1B4;             // crouched: the look speed
    RwReal unk_1B8;             // the look speed
    RwUInt8 unk_1BC[0x10];
    RwReal unk_1CC;             // its greatest (unk_344 its rise)
    RwUInt8 unk_1D0[0x8];
    RwReal unk_1D8;             // the jump's speed
    RwUInt8 unk_1DC[0x4];
    RwReal unk_1E0;             // mounted weapons' look springs by zoom
                                // kind (unk_1E0, unk_1E4 zoomed; unk_170,
                                // unk_174), -1 for the weapon's own
    RwReal unk_1E4[3];          // crouched, by stance: sideways
    RwReal unk_1F0;             // sideways
    RwReal unk_1F4;             // copied into the player's unk_1A20 to
    RwReal unk_1F8;             // unk_1A28
    RwUInt8 unk_1FC[0x8];
    RwReal unk_204;             // the view's bob (the player's vf_240):
    RwReal unk_208;             // up and down unk_204, unk_210, unk_21C and
    RwUInt8 unk_20C[0x4];       // unk_220; sideways unk_214, unk_218,
    RwReal unk_210;             // unk_224 and unk_228
    RwReal unk_214;
    RwReal unk_218;
    RwReal unk_21C;
    RwReal unk_220;
    RwReal unk_224;
    RwReal unk_228;
    RwReal unk_22C;             // the look spring's settings
    RwReal unk_230;
    RwUInt8 unk_234[0x8];
    RwReal unk_23C;             // the fall that hurts (the player's vf_044)
    RwReal unk_240;             // and the fall that kills
    type_3DF8D8_04 unk_244;
    type_3DF8D8_04 unk_24C;     // its camera object (kind 3; the camera's
                                // set-up, sub_174BC0)
    RwInt32 unk_254;            // set while the player's attributes come from
                                // the previous level or the memory card
    RwUInt8 unk_258[0xAC];
    // The aim assist's settings (sub_100AD0).
    RwInt32 unk_304;            // on
    RwReal unk_308;
    RwInt32 unk_30C;
    RwReal unk_310;             // the strafe turn's scale (with unk_360)
    RwUInt8 unk_314[0x8];
    RwReal unk_31C;
    RwReal unk_320;             // a range
    RwReal unk_324;
    RwReal unk_328;             // the aim assist's sideways reach at an enemy
    RwReal unk_32C;             // and at an ally: from unk_32C near to unk_330
    RwReal unk_330;             // at 2000 units (sub_FCD90)
    RwReal unk_334;
    RwInt32 unk_338;
    RwReal unk_33C;
    RwInt32 unk_340;
    RwReal unk_344;
    RwInt32 unk_348;            // strafing turns about the target
    RwReal unk_34C;
    RwReal unk_350;             // that turn's limit
    RwReal unk_354;             // its spring's settings
    RwReal unk_358;
    RwReal unk_35C;
    RwReal unk_360;
    RwReal unk_364[3];          // by stance
    RwReal unk_370[3];
    RwReal unk_37C;             // the look speed while aim-assisted
    RwUInt8 unk_380[0x4];
    RwInt32 unk_384[39];        // each weapon's rounds (-1 for none)
    RwUInt8 unk_420[0x30];
    type_3DF8D8_04 unk_450;     // its camera's scripts: a state machine
    type_3DF8D8_04 unk_458;     // (sub_70E10) and a task (sub_70F40), and
    type_3DF8D8_04 unk_460;     // the object given the camera's entity (the
                                // camera's set-up, sub_174BC0)

    // An inline accessor for unk_F0, with no address and so no database
    // name; named for its field. Evidence: "ResetCameraZoom" (sub_104F70)
    // copies it through a temporary into the player's unk_534.
    RwReal get_unk_F0()
    {
        return unk_F0;
    }
};

// The object named arg_0 among the keys (the player's start reads its
// class's script this way).
type_3DF8D8 *sub_198880(const RwChar *arg_0);
// Puts the entity arg_0 in a squad (src/recovered/unit_03DF30.cpp).
void sub_3EE10(type_3D3548 *arg_0);
// Registers arg_0 with the Vision Scheduler's two schedules
// (src/recovered/unit_040720.cpp).
void sub_40A60(type_67620 *arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C,
               struct type_3D2E7C *arg_10);

// Called last by the player's take-down with the player and its unk_3D4;
// only known by its widths.
void sub_1745C0(type_3D3548 *arg_0, RwInt32 arg_4);

// What the entity hit tells the player's vf_220 (type_3D3548::sub_D2AD0
// passes it on by width): only its slot +0x058 is known, a kind (5 leaves
// the hit unrecorded).
struct type_10F710_220
{
    virtual void vf_000();
    virtual void vf_004();
    virtual void vf_008();
    virtual void vf_00C();
    virtual void vf_010();
    virtual void vf_014();
    virtual void vf_018();
    virtual void vf_01C();
    virtual void vf_020();
    virtual void vf_024();
    virtual void vf_028();
    virtual void vf_02C();
    virtual void vf_030();
    virtual void vf_034();
    virtual void vf_038();
    virtual void vf_03C();
    virtual void vf_040();
    virtual void vf_044();
    virtual void vf_048();
    virtual void vf_04C();
    virtual void vf_050();
    virtual void vf_054();
    virtual RwInt32 vf_058();
};

// dword_4C194C: what the player's update aims at, passed to sub_100880;
// the aim pass (sub_FCD90, one atomic at a time) fills it.
struct type_4C194C
{
    RwReal unk_00;              // the aim ray's length
    RwReal unk_04;              // the best score so far
    type_D48D0 unk_08;          // the entity it belongs to
    RwReal unk_0C;              // its bearing, in degrees (an ally's)
    RwInt32 unk_10;             // the part vf_07C hit on an enemy (-1: none)
};
extern type_4C194C dword_4C194C;
// Globals the player's step reads or sets (.data): copied into unk_1B24 at
// a fire (dword_429AA0) and into unk_20DC when button 3 is up or the clip
// empty (dword_429744); set while its trigger's unk_140 holds it
// (dword_429498[3].unk_04, the fire input's flag).
extern RwInt32 dword_429744;
// The player's set-up (sub_FDC10): its unk_108 (.rdata), the weapons'
// names by language, and globals it resets.
extern const RwReal flt_3D9728;
extern const RwChar **dword_429A84[];
extern RwInt32 dword_4C19AC;
extern RwUInt8 byte_429700;
extern RwInt32 dword_429AA0;
// The look speed's scale for the still player (4.0): a float constant
// multiplied in a double expression (the step), so named.
extern const RwReal flt_3CE7F4;
// The scope's sway scales by stance change (.data; sub_1116A0) and the
// sideways sway's range and lean (sub_1116A0).
extern RwReal flt_429B00;
extern RwReal flt_429B04;
extern RwReal flt_429ADC;
extern RwReal flt_429B0C;
// The collision step's settings (.data; vf_044): the frame's spring
// (flt_429724 to flt_42972C), the radius scale, the collision height by
// stance, the jump's waits by the fall's speed (flt_429718, flt_42971C)
// and after landing (flt_429740), the hit marker's time on a hurting fall
// (flt_429B34), the longest fall (flt_429B38) and whether falls are
// measured (dword_429B3C).
extern RwReal flt_429724;
extern RwReal flt_429728;
extern RwReal flt_42972C;
extern RwReal flt_429B1C;
extern RwReal flt_429B28[];
extern RwReal flt_429718;
extern RwReal flt_42971C;
extern RwReal flt_429740;
extern RwReal flt_429B34;
extern RwReal flt_429B38;
extern RwInt32 dword_429B3C;
// dword_4FB9F8: a flag read (through a temporary, as by an inline accessor
// with a result local: get_4FB9F8) by the player's HUD update and three
// others; only that is known.
#ifdef CODFH_PLAIN
extern RwInt32 &dword_4FB9F8;
#else
extern RwInt32 dword_4FB9F8;
#endif
inline RwInt32 get_4FB9F8()
{
    RwInt32 r = dword_4FB9F8;
    return r;
}
// The player arg_0's HUD update for the aim arg_4: the crosshair (unless in
// a vehicle's seat 2, sub_100680), the hit marker for an enemy it hit, and
// the target marker's alpha by the distance to an ally aimed at.
void sub_100880(type_10F710 *arg_0, type_4C194C *arg_4);

// The player arg_0's aim assist for the aim arg_4: slows its turn over an
// enemy target and turns its frame toward it by the stick.
void sub_100AD0(type_10F710 *arg_0, type_4C194C *arg_4);
// The aim assist's thresholds and scales (.data).
extern RwReal flt_429748;
extern RwReal flt_42974C;
extern RwReal dword_429750;
extern RwReal dword_429754;
extern RwInt32 dword_429758;
extern RwInt32 dword_42975C;
extern RwInt32 dword_429760;
// The axis its frame turns about (.rdata).
extern const RwV3d stru_3D973C;
// The axis its turned view rotates about (.rdata; sub_108CC0).
extern const RwV3d stru_3D9730;

// The first entity of the entity list (walked by unk_10).
#ifdef CODFH_PLAIN
extern type_3D3548 *&dword_4B86A0;
#else
extern type_3D3548 *dword_4B86A0;
#endif
// The first entity of the second entity list (walked by unk_10; the
// target search sub_108CC0 walks both).
#ifdef CODFH_PLAIN
extern type_3D3548 *&dword_4B8690;
#else
extern type_3D3548 *dword_4B8690;
#endif
// The squared range of that alert (.data; 90000).
extern RwReal flt_429AA4;

// The point of the triangle arg_0 (with the normal arg_4) nearest *arg_8,
// into *arg_8; the squared distance.
RwReal sub_8F960(RwV3d **arg_0, RwV3d *arg_4, RwV3d *arg_8);
// The player's aim search (a type_93DF0 in arg_10): the world triangle
// callback keeps the nearest point and whether it is a floor it may stand
// on, the atomic callback the nearest entity within its aim cone.
RpCollisionTriangle *sub_104B30(RpIntersection *arg_0, RpWorldSector *arg_4, RpCollisionTriangle *arg_8,
                                RwReal arg_C, void *arg_10);
RpAtomic *sub_104D00(RpIntersection *arg_0, RpWorldSector *arg_4, RpAtomic *arg_8, RwReal arg_C,
                     void *arg_10);

// Shows the rounds loaded and in reserve (arg_0, arg_4) on the HUD; only
// known by its widths.
void sub_115390(RwInt32 arg_0, RwInt32 arg_4);

// Fills the entity arg_0's trigger volume (arg_4, its unk_248), as
// sub_144C80; only known by its widths.
struct type_145B40;
void sub_145970(type_3D3548 *arg_0, type_145B40 *arg_4);
// dword_4D51C0: an object only known by its method sub_15B720, which the
// vehicle seat's update calls last.
typedef struct RwCamera RwCamera;
struct type_15BCC0;
struct type_15BB60;
struct type_15B730_00;
struct type_4D51C0
{
    // A decal manager (unit_15B110, only reached from sub_15B5D0's dead
    // body): the unit square's corners, the decals by 20 slots, a list of
    // their extras, and a pool of 50 decals (unk_210; unk_208 its free
    // list, unk_20C how many are in use).
    RwV2d unk_00[4];
    RwUInt8 unk_20[0x94];
    type_15BCC0 *unk_B4[20];
    RwV3d unk_104[20];
    RwInt32 unk_1F4;
    type_15BB60 *unk_1F8;
    type_15BB60 *unk_1FC;
    RwInt32 unk_200;
    RwUInt8 unk_204[0x4];
    type_15BCC0 *unk_208;
    RwInt32 unk_20C;
    type_15BCC0 *unk_210;

    // Empty, out of line: folded (/OPT:ICF) into sub_6FCD0 (it returns
    // this); its dynamic initializer (0x30BC00) calls it.
    type_4D51C0();
    // A decal from the pool (freeing unprotected ones when all 50 are in
    // use), or 0; flagged in use.
    type_15BCC0 *sub_15C510();
    // Drops the decal arg_0's extra (unk_130) from the list.
    void sub_15BB60(type_15BCC0 *arg_0);
    // The point and UV at (arg_0, arg_4) in the quad arg_8, into *arg_C
    // and *arg_10 (bilinear, the square's corners at +-0.5).
    void sub_15C610(RwReal arg_0, RwReal arg_4, type_15B730_00 *arg_8, RwV2d *arg_C, RwV2d *arg_10);
    // A decal for the owner arg_18 over the quad arg_10 (its matrix arg_14
    // or the identity), cut to the points arg_0 to arg_C (arg_C only for
    // four), with the flags arg_20 and arg_24's settings; 0 without one.
    type_15BCC0 *sub_15BCC0(RwV2d *arg_0, RwV2d *arg_4, RwV2d *arg_8, RwV2d *arg_C, RwInt32 arg_10,
                            type_15B730_00 *arg_14, RwMatrix *arg_18, struct type_4D5170 *arg_1C,
                            RwInt32 arg_20, RwInt32 arg_24, type_15BCC0 *arg_28);
    void sub_15B720();
    // Called after the player enters or leaves a vehicle (sub_10F900).
    void sub_15B5D0();
    // Empty: folded (/OPT:ICF) into pDtor (0x1E41C0), whose database name it
    // takes; called after the player leaves a vehicle (sub_10FBF0).
    void pDtor();
    // Empty: folded (/OPT:ICF) into sub_15FB30; the main render (sub_125F20)
    // calls it with the camera.
    void sub_15FB30(RwCamera *arg_0);
};
extern type_4D51C0 dword_4D51C0;

// The player's model's set-up (sub_10C650); only the widths are known.
void sub_16D9A0(RpClump *arg_0);
RpAtomic *sub_1169B0(RpAtomic *arg_0, void *arg_4);
// The weapon copies' particle systems' callbacks (type_F2FF0::unk_154):
// following the weapon in hand (vf_030, the stance change) and the muzzle
// flash (vf_018).
RwInt32 sub_119BA0(struct type_F2FF0 *arg_0);
RwInt32 sub_119D50(struct type_F2FF0 *arg_0);
// The weapon copy's fire (vf_018): the axes its aim turns about for the
// recoil and the spread (.rdata) and whether particles spawned now take
// the standard rate (dword_4C19A8, also in game/particlerender.h).
extern const RwV3d stru_3DA4F0;
extern const RwV3d stru_3DA4FC;
extern RwInt32 dword_4C19A8;
// A debug check of a float, empty in this build (folded with the other
// empty functions returning 0 at sub_170ED0); the player's step and the
// weapon copy's fire pass it their angles.
RwInt32 sub_170ED0(RwReal arg_0);

// The look spring's weight on foot (.data).
extern RwReal flt_429708;

// The streaming slot of the group arg_0 (-1 while it is not streamed);
// only known by its widths.
RwInt32 sub_16F860(RwInt32 arg_0);
// Whether the group arg_0 is being streamed, and streaming it into slot
// arg_0 (arg_4 the group; whether it started); only known by their widths.
RwInt32 sub_16F8A0(RwInt32 arg_0);
// A new copy of weapon arg_8 for the player arg_0 with its clump arg_4,
// with its geometry when arg_C is set; only known by its widths.
// The game's operator new with a memory type (0x12F0E0), and its matching
// delete for the unwind.
void *operator new(size_t arg_0, RwUInt32 arg_4);
void operator delete(void *arg_0, RwUInt32 arg_4);
// The object at 0x4E5E50 (types/type_4E5E50.h).
#include "types/type_4E5E50.h"
// Two words the player's death waits on before its fade (vf_028); only
// known by their widths.
#ifdef CODFH_PLAIN
extern RwInt32 &dword_4FBAA8;
#else
extern RwInt32 dword_4FBAA8;
#endif
#ifdef CODFH_PLAIN
extern RwInt32 &dword_4FBAA4;
#else
extern RwInt32 dword_4FBAA4;
#endif
// The fade's callback (sub_119480, the player's death): only known by what
// it reads; the object at dword_4F805C by its word at +0x217C, dword_4F83D8
// by its width, and the object at 0x4F7EB8's calls by theirs.
void sub_119480();
struct type_4F805C
{
    RwUInt8 unk_00[0x19DC];
    RwReal unk_19DC;            // its health, a fraction (the pause menu's
                                // "kill" is offered while it is above 0)
    RwUInt8 unk_19E0[0x79C];
    RwInt32 unk_217C;
    RwUInt8 unk_2180[0x11C];
    RwInt32 unk_229C;           // cleared when an enemy takes its team's flag
                                // (the flag part's sub_1B1DE0)

    // Whether unk_229C is set: an inline with no address and so no database
    // name, named for what it returns. Evidence: the flag part's sub_1B1DE0
    // tests it through setne before clearing it.
    bool has_unk_229C()
    {
        return (bool)unk_229C;
    }

    // The number of teams with players in (the bomb sites compare it with
    // the game's team count, type_4F6950::sub_1A3D50); only the width is
    // known.
    RwInt32 sub_1B8420();
    static type_4F805C *get();
};
#ifdef CODFH_PLAIN
// (plain builds: a field of the multiplayer manager unk_4F7EB8; see unit_1A8B20)
extern type_4F805C *&dword_4F805C;
#else
extern type_4F805C *dword_4F805C;
#endif
// An inline accessor with no address and so no database name, named for
// what it returns. Evidence: the bomb sites (sub_1A3D50) copy dword_4F805C
// into a local of its own before calling through it.
inline type_4F805C *type_4F805C::get()
{
    type_4F805C *r = dword_4F805C;
    return r;
}
#ifdef CODFH_PLAIN
// (plain builds: a field of the multiplayer manager unk_4F7EB8; see unit_1A8B20)
extern RwInt32 &dword_4F83D8;
#else
extern RwInt32 dword_4F83D8;
#endif
// Shows the rounds arg_0 and reserve arg_4 on the HUD (unit_0FD730).
void sub_115390(RwInt32 arg_0, RwInt32 arg_4);
// Takes down a weapon model's clump (the copies' sub_117050); only the width
// is known.
void sub_16E040(RpClump *arg_0);
// RpClumpForAllAtomics callback: stops the atomic arg_0 rendering (the
// weapon copies' vf_008).
RpAtomic *sub_1169B0(RpAtomic *arg_0, void *arg_4);
struct type_10F710_1A48 *sub_116490(struct type_10F710 *arg_0, RpClump *arg_4, RwInt32 arg_8, RwInt32 arg_C);
RwInt32 sub_16F900(RwInt32 arg_0, RwInt32 arg_4);
// The count sub_110EC0 keeps while sub_110A60 draws the weapon's clump:
// with both unk_00 and unk_04 set it skips the first atomic, with only
// unk_00 the second; unk_08 counts the atomics.
struct type_110EC0
{
    RwInt32 unk_00;
    RwInt32 unk_04;
    RwInt32 unk_08;
};
// Draws the atomic arg_0 once this camera frame when it is in view (flag 4
// of its object's flags set meanwhile), counting it in arg_4 (a
// type_110EC0) when given.
RpAtomic *sub_110EC0(RpAtomic *arg_0, void *arg_4);

// The view bob's springs (vf_240; .data): the lift's settings and the
// dip's scale and settings.
extern RwReal flt_42970C;
extern RwReal flt_429710;
extern RwReal flt_429714;
extern RwReal flt_429AD0;
extern RwReal flt_429AD4;
extern RwReal flt_429AD8;

// "BlockingEntity"'s range ahead of the camera (vf_060; .data): a scale
// of the facing, an offset and a distance.
extern RwReal flt_429AAC;
extern RwReal flt_429AB0;
extern RwReal flt_429AB4;

// Invulnerability (vf_064 takes no damage while it is set) and the dying
// cry's sound (.data; vf_064).
extern RwUInt8 byte_4F28F8;
extern RwInt32 dword_44E8B8;

// The shakes' scale and time when the explosion's hit was a direct one
// (vf_068; .data).
extern RwReal flt_429AC0;
extern RwReal flt_429AC4;

// The eye heights by stance (vf_040; .data).
extern RwReal flt_429B10[];

// Cleared before the player draws its clumps (sub_110A60; sub_122820 reads
// them).
extern RwInt32 dword_4CF7A4;
extern RwInt32 dword_4CF7BC;

// The group each streaming slot holds (-1 for none; sub_10DA70).
extern RwInt32 dword_4E54D0[];
// The slot holding the group arg_0 (sub_16F860), and what each slot holds:
// the weapon it streamed in the high word (the player's sub_10FBF0 clears
// the vehicle weapon's).
RwInt32 sub_16F860(RwInt32 arg_0);
extern RwInt32 dword_4E5518[];

// The player's eye heights above its frame's position (vf_110): standing
// and in the vehicle-driving posture.
extern RwReal flt_429AB8;
extern RwReal flt_429ABC;

// The screen blur's kind for shocks (.data).
extern RwInt32 dword_429704;

// A swaying offset (the player's weapon bob): arg_0 to arg_4 by arg_14 for
// its size, the phase *arg_10 advancing by arg_8 to arg_C by arg_14 times
// arg_18 (decaying while arg_14 is 0), wrapped to -pi to pi; the sine of the
// phase times the size.
RwReal sub_111220(RwReal arg_0, RwReal arg_4, RwReal arg_8, RwReal arg_C, RwReal *arg_10, RwReal arg_14,
                  RwReal arg_18);
// One step of the spring sub_112DA0 runs: *arg_8 pulled toward arg_4 - *arg_0
// by arg_C, keeping arg_10 of itself, within arg_14, then added to *arg_0.
void sub_112EB0(RwReal *arg_0, RwReal arg_4, RwReal *arg_8, RwReal arg_C, RwReal arg_10, RwReal arg_14);
// *arg_0 the point arg_C of the way from *arg_4 to *arg_8, and the same
// eased (3t^2 - 2t^3; sub_112F80 for a float).
void sub_112F20(RwV3d *arg_0, RwV3d *arg_4, RwV3d *arg_8, RwReal arg_C);
RwReal sub_112F80(RwReal arg_0, RwReal arg_4, RwReal arg_8);
void sub_112FC0(RwV3d *arg_0, RwV3d *arg_4, RwV3d *arg_8, RwReal arg_C);

// An explosion's shake settings (type_10F710::sub_114F90): the camera's
// range and strength with its two times, the player's range and strength.
// Its zones as the player's vf_068 reads them: full damage within unk_18,
// falling off to the radius (or to unk_08 crouched, unk_0C when well above
// it); the shakes within unk_1C (the camera's) or unk_2C (the player's)
// with their settings.
struct type_114F90_50
{
    RwUInt8 unk_00[0x8];
    RwReal unk_08;
    RwReal unk_0C;
    RwReal unk_10;              // the damages within unk_08 and unk_0C (a
    RwReal unk_14;              // soldier's posture classes 1 and 2,
                                // type_3DAFC8::vf_068)
    RwReal unk_18;
    RwReal unk_1C;
    RwReal unk_20;
    RwReal unk_24;
    RwReal unk_28;
    RwReal unk_2C;
    RwReal unk_30;
};
struct type_114F90
{
    RwUInt8 unk_00[0x50];
    union
    {
        type_114F90_50 unk_50;
        struct
        {
            RwUInt8 unk_50_b[0x1C];
            RwReal unk_6C;
            RwReal unk_70;
            RwReal unk_74;
            RwReal unk_78;
            RwReal unk_7C;
            RwReal unk_80;
        };
    };
};
// The player's room test (a type_93DF0 in arg_C or arg_10): the triangle
// callback marks a hit (unk_60), the atomic callback runs it on an atomic of
// an entity with bit 2 of unk_28, the world callback marks a hit unless the
// material's flags are among unk_74.
RpCollisionTriangle *sub_115110(RpIntersection *arg_0, RpCollisionTriangle *arg_4, RwReal arg_8, void *arg_C);
RpAtomic *sub_115130(RpIntersection *arg_0, RpWorldSector *arg_4, RpAtomic *arg_8, RwReal arg_C,
                     void *arg_10);
RpCollisionTriangle *sub_1151B0(RpIntersection *arg_0, RpWorldSector *arg_4, RpCollisionTriangle *arg_8,
                                RwReal arg_C, void *arg_10);

// Whether a sphere at arg_0 of radius arg_4 is blocked (the stance change);
// only known by the widths.
RwInt32 sub_115230(RwV3d *arg_0, RwReal arg_4);

// The health pick-up multiplier for the difficulty dword_42B714
// ("GameDiff:GetPlayerHealthPupMultiplier" in its message), 1 outside 0 to 2.
RwReal sub_104420();
extern RwReal flt_4F28CC[3];
// The projectile generators' spread multiplier by difficulty, likewise
// (type_1227C0's sub_121230 reads it through an inline copy).
extern RwReal flt_4F289C[3];
// The angle arg_0 wrapped into -pi to pi.
RwReal sub_104850(RwReal arg_0);

// Whether the player arg_0's target (unk_1A34) is a soldier, a type_3DBC78
// or a type_3DDB98 it may target (vf_248).
RwInt32 sub_100A50(type_10F710 *arg_0);
// Whether the current player (sub_1745A0 of dword_429EB0) has unk_1B3C set,
// unless its camera's unk_414 is.
RwInt32 sub_1014E0();

struct type_42B740;
extern type_42B740 *dword_4F2AAC[5];

typedef RwChar type_10F710_size_check[sizeof(type_10F710) == 0x2260 ? 1 : -1];

#endif
