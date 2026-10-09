/*
 * type_3DAFC8: an entity class derived from type_3D3548, anchored at its
 * vtable off_3DAFC8, which sub_134C50 and sub_135310 install (sub_134C50
 * calls type_3D3548's sub_CC960). off_3E3008 derives from it. It is the class
 * type_3D3548::vf_008 returns: its slot +0x008 returns this (sub_6FCD0).
 *
 * Its AI object is embedded at +0x8A0 (vf_120 is sub_135110).
 */
#ifndef TYPE_3DAFC8_H
#define TYPE_3DAFC8_H

#include "rw/ostypes.h"
#include "types/type_3D3548.h"
#include "types/type_3DC9B0.h"
#include "types/type_15CCE0.h"
#include "types/type_D48D0.h"
#include "types/type_129_base.h"
#include "types/type_3DAFC8_1DDC.h"
#include "types/AIData.h"
#include "types/SoldierTrigger.h"
#include "types/animkey.h"

// type_3DAFC8_610: what type_3DAFC8's +0x610 points at: an object with a
// vtable ("CanGetPointFromGrenade" calls its +0x05C) and a point at +4
// (AIData::sub_17BF0 measures the owner from it); named after the field that
// refers to it.
struct type_3DAFC8_610
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
    virtual void vf_058();
    // +0x05C: a point "CanGetPointFromGrenade" hands AIData::sub_28470.
    virtual RwV3d *vf_05C();

    RwV3d unk_04;
    RwV3d unk_10;   // its velocity: "CanIDiveAwayFromGrenade" dives across it

    // Inline accessor for unk_04's address, with no address of its own and
    // so no database name; named for its field. Evidence: AIData::sub_17BF0
    // holds the object pointer in a compiler temporary above `this` (an
    // inline member's `this`) and reads the point at +4 through it, ahead of
    // the other operand of each subtraction.
    RwV3d *get_unk_04()
    {
        return &unk_04;
    }
};

// The mounted weapon (the entity a soldier's unk_618 holds) is
// type_3DC9B0 (types/type_3DC9B0.h).

// The data of the soldier's messages (vf_170), by the widths and offsets it
// reads; named after the function.
struct type_13AE40_msg
{
    RwInt32 unk_00;
    RwInt32 unk_04;
    RwInt32 unk_08;
    RwInt32 unk_0C;
};
// 0x9C4's: the hatch state (0 open, 1 closed), the hatch and two options,
// then (in type_13AE40_msg's unk_04) the last option.
struct type_13AE40_hatch
{
    RwUInt8 unk_00;
    RwUInt8 unk_01;
    RwUInt8 unk_02;
    RwUInt8 unk_03;
};
// 0xA28's: the vision multiplier.
struct type_13AE40_vision
{
    RwReal unk_00;
};

// What the soldier's set-up (sub_135430) matches its definition and head
// against, named after their addresses: the definitions drawn at a fixed
// scale (0x42A0B8, dword_42A1C0 of them) and the heads' hat tags (0x42A1C8,
// dword_42A36C of them); then each node's parent (-1 for the root) and its
// bind pose offset, which the second animation's translations are made
// relative to.
// Their key: a model key's two halves (as type_3DF8D8_04, but without its
// constructors: the tables are initialized data).
struct type_42A0B8_00
{
    RwUInt32 unk_00;
    RwUInt32 unk_04;
};
struct type_42A0B8
{
    type_42A0B8_00 unk_00;
    RwReal unk_08;
};
struct type_42A1C8
{
    type_42A0B8_00 unk_00;
    RwInt32 unk_08;
};

// A soldier's dodge check in one direction (sub_13E580), named after the
// field that holds four: the line test's hit fraction, and the frames until
// it is tested again (30).
struct type_3DAFC8_2144
{
    RwReal unk_00;
    RwReal unk_04;
};

#ifdef CODFH_SP
// The difficulty's multiplier of flt_4F28C0 (1 outside 0 to 2): single
// player's soldiers scale by it where multiplayer multiplies by 1 (vf_1F0,
// SP 0xEC0B0, the soldier's and type_3DDB98's folded); named for what it
// returns.
extern RwReal flt_4F28C0[3];
extern RwInt32 dword_42B714;
inline RwReal get_4F28C0()
{
    if (dword_42B714 > -1 && dword_42B714 < 3)
    {
        return flt_4F28C0[dword_42B714];
    }
    return 1.0f;
}
#endif

struct type_3DAFC8 : type_3D3548
{
    // Built from its trigger (sub_134B40 spawns it): the base, its members,
    // then its set-up (sub_135430). Defined in the class but not inlined
    // (its members have destructors): sub_134B40's frame keeps room for
    // the expansion, and its out-of-line copy is sub_134C50.
    type_3DAFC8(struct SoldierTrigger *arg_0)
    {
        sub_135430(arg_0);
    }
    // Its destructor takes it down (vf_230, sub_136B10) before its members
    // go; its scalar deleting destructor is sub_1352E0. Defined here and not
    // expanded: the remote player's destructor (sub_1BEEB0) reserves its
    // seven slots; its out-of-line copy is sub_135310.
    ~type_3DAFC8()
    {
        vf_230();
    }
    // +0x05C: forgets its first prop (handle and value). Defined here: its
    // out-of-line copy lies with the remote player's code (sub_1C06A0),
    // whose network part reaches it through a thunk (sub_1C06D0).
    // An inline accessor for unk_1DC0, with no address and so no database
    // name; named for its field. Evidence: the remote player's performance
    // (sub_1BF5E0) reads it through a slot of its own each time.
    RwReal get_unk_1DC0()
    {
        RwReal r = unk_1DC0;
        return r;
    }
#ifndef CODFH_SP // MP @ 0x1C06A0 (type_3DAFC8's slot 0x05C); SP @ 0x2E6EB4 has no such slot
    virtual void vf_05C()
    {
        unk_35C[0].sub_D48D0(0);
        unk_364[0] = -1;
    }
#endif
    // The placement pair sub_134B40 builds it in entity memory with, as
    // type_3DAC58's (sub_6CCF0 and the empty sub_19A750), and its plain
    // operator delete (folded into sub_19A750).
    static void *operator new(RwUInt32 arg_0, void *arg_4);
    static void operator delete(void *arg_0, void *arg_4);
    static void operator delete(void *arg_0);

    // The overrides defined in the class, in the order they are emitted
    // with its vtable (unit_1340D0).
    virtual void vf_094(RwUInt32 arg_0)
    {
        unk_844 = arg_0;
    }
    virtual void vf_0A4(RwInt32 arg_0)
    {
        unk_1D44 = arg_0;
    }
    virtual RwInt32 vf_0A8()
    {
        return unk_1D44;
    }
    virtual void vf_088(RwInt32 arg_0)
    {
        unk_848 = arg_0;
    }
    virtual RwInt32 vf_09C()
    {
        return unk_840;
    }
    virtual void vf_0A0(RwUInt32 arg_0)
    {
        unk_840 = arg_0;
    }
    virtual RwInt32 vf_0AC()
    {
        return unk_864;
    }
    virtual void vf_0B4()
    {
        unk_868 = unk_84C[3];
    }
    virtual void vf_0B8(RwInt32 arg_0)
    {
        unk_868 = arg_0;
    }
    virtual RwUInt8 *vf_0E0()
    {
        return (RwUInt8 *)unk_898;
    }
    virtual RwInt8 *vf_0F0()
    {
        return unk_1D38;
    }
    // Its collision priority is its trigger's.
    virtual void vf_1AC(RwInt32 arg_0)
    {
        ((struct SoldierTrigger *)get_unk_34C())->unk_160 = arg_0;
    }
    // +0x234 to +0x240, new: its vision multiplier and a flag
    // ("SetVisionMultiplier" sets +0x238 and +0x240), and their getters.
    virtual RwReal vf_234()
    {
        return unk_880;
    }
    virtual void vf_238(RwReal arg_0)
    {
        unk_880 = arg_0;
    }
    virtual RwInt32 vf_23C()
    {
        return unk_874;
    }
    virtual void vf_240(RwInt32 arg_0)
    {
        unk_874 = arg_0;
    }
    virtual RwInt32 vf_138()
    {
        return unk_2140;
    }
    // Its hit points, setting them and adding to them (no more than its full
    // hit points).
    virtual RwInt32 vf_174()
    {
        return unk_1D20;
    }
    virtual void vf_178(RwInt32 arg_0)
    {
        unk_1D20 = arg_0;
    }
    virtual void vf_180(RwInt32 arg_0)
    {
        unk_1D20 += arg_0;
        if (unk_1D20 > unk_1D24)
            unk_1D20 = unk_1D24;
    }
    // +0x244, new: where it aims, for the five-way blend (sub_139620);
    // returns arg_0.
#ifdef CODFH_SP // not virtual in single player: its vtable (SP 0x2E6EB8) has no slot for it, MP's
                // +0x248 on sit 8 lower there (with vf_05C's); SP 0xE9B00 calls vf_25C through +0x254
    RwV3d *vf_244(RwV3d *arg_0);
#else
    virtual RwV3d *vf_244(RwV3d *arg_0);
#endif
#ifdef CODFH_SP
    // Single player only: the grenade throw and its helpers (SP 0xE4B50, 0xE4B60, 0xE4BB0;
    // case 0x76C of vf_170 calls them).
    void sp_sub_E4B50();
    void sp_sub_E4B60(RwV3d *arg_0, RwReal arg_4, RwReal arg_8, RwReal arg_C, RwReal arg_10);
    void sp_sub_E4BB0();
#endif
    // +0x248: an infinite ammunition clip on or off ("InfiniteAmmoClip").
    virtual void vf_248(RwInt32 arg_0);
    // +0x24C: whether it fires at no target ("SetFireAtNoTarget").
    virtual void vf_24C(RwInt32 arg_0);
    // +0x250: suppresses it; returns its suppression.
    virtual RwReal vf_250();
    // +0x254: whether the soldier is suppressed ("GetSuppressed"); +0x258
    // and +0x25C its attitude ("GetAttitude", "SetEngineAttitude").
    virtual RwInt32 vf_254()
    {
        return unk_1D2C > 0.0f;
    }
    virtual RwInt32 vf_258()
    {
        return unk_1D34;
    }
    virtual void vf_25C(RwInt32 arg_0)
    {
        unk_1D34 = arg_0;
    }
    // The next member of its group, through its AI object's handle.
    virtual type_3D3548 *vf_118()
    {
        return unk_8A0.unk_54.sub_D4910();
    }
    virtual void vf_11C(type_3D3548 *arg_0)
    {
        unk_8A0.unk_54.sub_D48D0(arg_0);
    }
    virtual AIData *vf_120()
    {
        return &unk_8A0;
    }
    virtual RwReal vf_17C()
    {
        return (RwReal)unk_1D20 / ((RwReal)unk_1D24);
    }
    // +0x260, new: sets its hit points to arg_0 of its full hit points.
    virtual void vf_260(RwReal arg_0)
    {
        unk_1D20 = unk_1D24 * arg_0;
    }
    // Its weapon's (unk_3E0's) ranges, ammunition, reload and force.
    virtual RwReal vf_144()
    {
        return unk_3E0.sub_15EBF0();
    }
    virtual RwReal vf_148()
    {
        return unk_3E0.sub_15EC30();
    }
    virtual RwReal vf_14C()
    {
        return unk_3E0.sub_15ECB0();
    }
    virtual RwReal vf_150()
    {
        return unk_3E0.sub_15ED20();
    }
    virtual RwReal vf_154()
    {
        return unk_3E0.sub_15ED60();
    }
    virtual RwReal vf_158()
    {
        return unk_3E0.sub_15EDA0();
    }
    virtual RwInt32 vf_15C()
    {
        return unk_3E0.sub_15EC70();
    }
    virtual RwInt32 vf_13C()
    {
        return unk_3E0.unk_1C == 0;
    }
    virtual void vf_140()
    {
        unk_3E0.sub_15E9B0(0);
    }
    virtual RwReal vf_1F4()
    {
        return unk_3E0.sub_15EE20();
    }
    virtual type_3DAFC8_1DDC *vf_1C8()
    {
        return &unk_1DDC;
    }

    // +0x230: takes it down (sub_136B10).
    virtual void vf_230();
    // +0x038: its update.
    virtual void vf_038(RwReal arg_0);
    virtual void vf_21C(RwReal arg_0);
    virtual void vf_190(RwInt32 arg_0);
    virtual void vf_1A0(RwInt32 arg_0);
    virtual void vf_210(struct type_D05C0 *arg_0);
    virtual bool vf_224(struct type_3DF8D8 *arg_0, RwInt32 arg_4, RwInt32 *arg_8);
    virtual bool vf_228();
    virtual void vf_0EC(RwInt32 arg_0, RwInt32 arg_4);
    virtual RwReal vf_0FC();
    virtual RwReal vf_100();
    virtual RwReal vf_10C();
    virtual RwReal vf_130();
    virtual RwReal vf_114();
    virtual RwReal vf_164();
    virtual RwReal vf_168();
    virtual void vf_1B0(RwInt32 arg_0);
    // +0x170: its message handler.
    virtual void vf_170(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C);
    // +0x060: a touch by the entity arg_0; 0.
    virtual RwInt32 vf_060(type_3D3548 *arg_0);
    // +0x134: whether it can shoot arg_4 from the offset arg_0 (*arg_14
    // takes a float, the distance along to a blocker).
    virtual RwInt32 vf_134(RwV3d *arg_0, type_3D3548 *arg_4, RwInt32 arg_8, RwInt32 arg_C,
                           RwInt32 *arg_10, RwInt32 *arg_14, RwInt32 arg_18);
    virtual void vf_1B4(RwInt32 arg_0);
    virtual RwUInt8 *vf_08C(RwInt32 arg_0, RwInt32 arg_4);
    virtual type_3D2E7C *vf_098();
    virtual struct type_6D380 *vf_090();
    virtual void vf_0B0(RwInt32 arg_0, RwInt32 arg_4);
    virtual RwInt32 vf_208(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwReal arg_C,
                           RwReal arg_10, RwReal arg_14, RwInt32 arg_18);
    virtual RwInt32 vf_0BC();
    virtual void vf_1C4(RwInt32 arg_0);
    virtual RwInt32 vf_16C(RwInt32 arg_0, RwInt32 arg_4);
    virtual void vf_104(RwMatrix *arg_0);
    virtual void vf_108(RwV3d *arg_0);
    virtual void vf_110(RwV3d *arg_0, type_3D3548 *arg_4, RwInt32 arg_8);
    virtual RwInt32 vf_07C(RwInt8 arg_0, RpIntersection *arg_4, RwReal *arg_8, RwInt32 arg_C);
    virtual RwInt32 vf_064(struct type_75600 *arg_0);
    virtual RwInt32 vf_068(struct type_758F0 *arg_0);
    virtual RwInt32 vf_06C(type_3D3548 *arg_0);
    virtual RwInt32 vf_058(struct type_3DF8D8_04 *arg_0);
    virtual void vf_054(RwInt32 arg_0);
    // +0x1CC: drops its pickup (arg_0: floating).
    virtual void vf_1CC(RwInt32 arg_0);
    // +0x04C: its update after the base's.
    virtual void vf_04C(RwReal arg_0);
    // +0x03C: its logic.
    virtual void vf_03C(RwReal arg_0);

    RwUInt8 unk_3A8[0x8];       // where type_3D3548 ends inside this is not known
    RwInt32 *unk_3B0;           // its sounds' state (sub_83850, its set-up)
    RwUInt8 unk_3B4[0x2C];
    type_15CCE0 unk_3E0;        // built by sub_15CCE0 in sub_134C50
    type_15CCE0 unk_4E0;        // built by sub_15CCE0 in sub_134C50
    RwInt32 unk_5E0;            // sub_31C50 logs "MaybeThrowAGrenade" while it
                                // is set
    RwReal unk_5E4;             // a grenade may be thrown from 120 on
                                // (sub_136EC0)
    RwInt32 unk_5E8;            // the bone the grenade is held at (vf_04C)
    RwV3d unk_5EC;              // the grenade throw point ("SetGrenadeThrowPoint")
    RwInt32 unk_5F8;            // set while unk_5EC holds one (cleared by
                                // "CancelGrenadeThrowPoint")
    RwReal unk_5FC;             // the grenade timer override, in frames
                                // ("OverrideNPCGrenadeTimer": seconds x 60)
    RwInt32 unk_600;            // set while it fires at no target (vf_24C,
                                // sub_13F4F0)
    RwV3d unk_604;              // AIData::sub_21C90 stores a point here and
                                // makes it its target (unk_4F0, unk_5B0)
    type_3DAFC8_610 *unk_610;   // AIData::sub_17BF0 plans a path near it
    type_D48D0 unk_614;         // the tank threatening the soldier
                                // ("IsThreatenedByTank")
    type_D48D0 unk_618;         // handle; sub_14AA0 requires it to resolve
    RwInt32 unk_61C;            // type_3CE5E8 passes over an entity while set
    RwInt32 unk_620;            // set when "AttachToEntity" gives it a ride
    type_D48D0 unk_624;         // likewise while it resolves (the ride)
    RwInt32 unk_628;            // the ride's tag
    RwChar unk_62C[0x20];       // its name, which the HUD labels it with
                                // (type_DC400::sub_E84E0 copies it)
    RwInt32 unk_64C;            // whether the name shows colour-coded
                                // ("EnableColorCodedName")
    type_7CBD0_t unk_650[25];   // its second animation's translation
                                // offsets by node (vf_03C)
    RwUInt8 unk_7E0[0x2];
    RwInt16 unk_7E2;            // the hit-death performance's partner, set by
                                // "PlayHitDeathAnimDefaultData"
    RwV3d unk_7E4;              // a head shot's direction, scaled and raised
    RwV3d unk_7F0;              // and as it was (vf_064)
    RwReal unk_7FC;             // its second animation's scale (vf_04C)
    RwReal unk_800;             // its scale (with cheat flag 4, sub_13C490)
    RwInt8 unk_804;             // 2 after such a head shot (vf_064)
    RwInt8 unk_805;             // 1 hurt, 2 dying (sub_13C490); 9 while a
                                // facial animation plays (sub_5AC50)
    RwUInt8 unk_806[0x2];
    RwInt32 unk_808;            // no head shot effect while set (vf_064)
    RwInt32 unk_80C;            // the node unk_834 follows (vf_04C)
    RwInt32 unk_810;            // its pickup (below 0x6E; -1 for none) and
    RwInt32 unk_814;            // how many ("SetPickup")
#ifndef CODFH_SP // MP +0x818..+0x823; single player has none: its vtable-paired methods (vf_094 SP, vf_09C, ...) read MP's +0x824..+0x898 0xC lower, +0x810/+0x814 in place, and AIData stays at +0x8A0 (16-aligned)
    union
    {
        struct
        {
            RwInt32 unk_818;    // zeroed by its set-up (sub_135430)
            RwInt32 unk_81C;
            RwInt32 unk_820;
        };
        RwV3d unk_818_v;        // where its weapon's timed shots go
                                // (type_15CCE0::sub_15D600)
    };
#endif
    RwInt32 unk_824;            // flags: 1 and 2 the five-way blends of
                                // modes 0 and 1 (sub_139550, vf_21C); head
                                // tracking's (sub_1340D0) 4 on, 8 kept when
                                // its track ends, 0x10 turning off
    type_129940 unk_828;        // two clump holders (the constructor and
    type_129940 unk_834;        // destructor)
    RwUInt32 unk_840;           // the handles vf_09C and vf_0A0 and
    RwUInt32 unk_844;           // vf_094 set
    RwInt32 unk_848;            // its performance kind (vf_088)
    RwUInt8 unk_84C[0xC];       // its performance values and its special
    RwUInt8 unk_858[0xC];       // idle ones (vf_08C); vf_0B4 copies
                                // unk_84C[3] into unk_868
    RwInt32 unk_864;            // its posture (vf_0AC)
    RwInt32 unk_868;            // vf_0B8's value
    RwReal unk_86C;             // vf_0FC's and vf_100's values (a constant
    RwReal unk_870;             // instead while unk_874 is set)
    RwInt32 unk_874;            // the vision flag (vf_240)
    RwReal unk_878;             // its view range, and alerted (vf_10C,
    RwReal unk_87C;             // vf_114)
    RwReal unk_880;             // the vision multiplier (vf_238)
    RwReal unk_884;             // vf_114's factor while bit 13 of its AI
                                // object's unk_49C is clear
    RwReal unk_888;             // vf_130's value
    RwReal unk_88C;             // vf_164's and vf_168's values
    RwReal unk_890;
    RwReal unk_894;             // while its AI object holds it alive, the
                                // time it ignores bullets for (vf_064)
    RwInt16 unk_898[0x4];       // its scene values (vf_0EC; vf_0E0)
    AIData unk_8A0;             // its AI object (vf_120)
    RwInt32 unk_1D20;           // its hit points and
    RwInt32 unk_1D24;           // its full hit points
    RwInt32 unk_1D28;           // its step mode (1: a quarter step, vf_210)
    RwReal unk_1D2C;            // positive while it is suppressed (vf_254)
    RwReal unk_1D30;            // the suppression time left (vf_250)
    RwInt32 unk_1D34;           // its attitude (vf_258)
    RwInt8 unk_1D38[0xC];       // its hit-death values (vf_0F0)
    RwInt32 unk_1D44;           // its disabled performances (vf_0A4)
    RwInt32 unk_1D48;           // set once its pickup is dropped (vf_1CC)
    RwInt16 unk_1D4C;           // the five-way blends' animations (modes 0
    RwInt16 unk_1D4E;           // and 1: sub_139550, sub_13A340; -1 for none)
    RwInt32 unk_1D50[5];        // mode 0's weights, cleared
    RwV3d unk_1D64;             // the five-way blend's origin in its frame
    RwV3d unk_1D70[5];          // and its directions (vf_244, sub_139620)
    RwInt32 unk_1DAC[5];        // mode 1's
    RwReal unk_1DC0;            // mode 1's angle (sub_13A410)
    RwInt32 unk_1DC4;           // head tracking's procedural track (sub_134320)
    RwV3d unk_1DC8;             // the point the head turns to (sub_134320)
    RwReal unk_1DD4;            // when head tracking last turned on or off
    RwReal unk_1DD8;            // how long it blends, in frames
    type_3DAFC8_1DDC unk_1DDC;  // vf_1C8
    RwInt32 unk_2140;           // vf_138's value
    type_3DAFC8_2144 unk_2144[4];   // the dodge checks by direction
                                    // (sub_13E580)
    RwInt32 unk_2164;           // set while it is up (vf_230 clears it)
    RwUInt8 unk_2168[0x8];

    // Points unk_618 at arg_0 (sub_D48D0).
    void sub_13F4D0(type_3D3548 *arg_0);
    // Whether the soldier can dive along *arg_0, nothing but the entity arg_4
    // in the way ("CanIDiveForward" passes 0 and 0 for the rest).
    RwInt32 sub_13E9A0(RwV3d *arg_0, type_3D3548 *arg_4, RwInt32 arg_8);
    // Whether the soldier can dodge in direction arg_0 (0 to 3) with arg_4
    // and arg_8 ("GetDodgeDirection"); only the widths are known.
    RwInt32 sub_13E580(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8);
    // Turns the weapon's rendering on or off ("EnableWeaponRender"); only
    // the widths are known.
    void sub_13F660(RwInt32 arg_0, RwInt32 arg_4);
    // Whether to melee attack, given arg_0 ("ShouldIMeleeAttack"); only the
    // widths are known.
    RwInt32 sub_137200(RwInt32 arg_0);
    // Drops the grenade in hand ("DropGrenade").
    void sub_136E00();
    // Whether to throw a grenade, given arg_0 ("ShouldIThrowAGrenade"); only
    // the widths are known.
    RwInt32 sub_136EC0(RwInt32 arg_0);
    // Sets the advanced shot location arg_0 ("SetAdvancedShotLocation");
    // only the widths are known.
    RwInt32 sub_138D00(RwInt32 arg_0);
    // The five-way blends of "SetFiveWayBlend" modes 0 and 1, on or off.
    void sub_139550(bool arg_0);
    // Sends the soldier flying along arg_0 with arg_4 ("SendFlying"); only
    // the widths are known.
    void sub_13DF40(RwV3d *arg_0, RwReal arg_4);
    void sub_13A340(bool arg_0);
    // Head tracking ("SetHeadTrack"): on or off, whether to keep it when
    // its track ends, and how long it blends in or out, in seconds.
    void sub_1340D0(bool arg_0, bool arg_4, RwReal arg_8);
    // Mounts (1) or dismounts (0) the weapon unk_618 holds
    // ("AttachToMountedWeapon", "DetachFromMountedWeapon"); "SnapToCover"
    // keeps its result. Only the widths are known.
    RwInt32 sub_13F590(RwInt32 arg_0);

    // The mounted weapon unk_618 holds: an inline accessor with no address,
    // so no database name; named for its field. Evidence: the script
    // commands on mounted weapons ("SetMyMMGToFireEvenIfICantSeeTarget",
    // "GetMyMMGMinBurstLength" and the like) keep the soldier they call it
    // on in a temporary of its own.
    type_3DC9B0 *get_unk_618()
    {
        return (type_3DC9B0 *)unk_618.sub_D4910();
    }

    // Inline accessor for unk_5E0, with no address and so no database name;
    // named for its field. Evidence: sub_31C50 keeps the object in a `this`
    // temporary and then the field in a second one before testing it (a
    // local holding the result would come before `this`).
    RwInt32 get_unk_5E0()
    {
        return unk_5E0;
    }
    // Whether a grenade is in hand: unk_4E0's class (sub_15EF80) is 8 and its
    // unk_00 is set. An inline function with no address and so no database
    // name, named for what it tests. Evidence: "DoIHaveAGrenadeInHand"
    // (sub_49970) calls vf_008 once for both tests and keeps the result in a
    // compiler temporary (an inline member's `this`).
    RwInt32 has_grenade_in_hand()
    {
        return unk_4E0.sub_15EF80() == 8 && unk_4E0.get_unk_00() != 0;
    }
    // Inline setters for unk_5F8 and unk_5FC, with no address and so no
    // database name; named for their fields. Evidence:
    // "CancelGrenadeThrowPoint" and "OverrideNPCGrenadeTimer" keep the vf_008
    // result they store through in a compiler temporary (an inline member's
    // `this`), where a direct store would not.
    void set_unk_5F8(RwInt32 arg_0)
    {
        unk_5F8 = arg_0;
    }
    void set_unk_5FC(RwReal arg_0)
    {
        unk_5FC = arg_0;
    }
    // Likewise for the throw point: *arg_0, when given, becomes unk_5EC and
    // sets unk_5F8. Evidence: "SetGrenadeThrowPoint" keeps the vf_008 result
    // in a compiler temporary and tests the point's address, which only an
    // inlined pointer parameter would.
    void set_unk_5EC(RwV3d *arg_0)
    {
        if (arg_0)
        {
            unk_5EC = *arg_0;
            unk_5F8 = 1;
        }
    }
    // Likewise for unk_61C (type_3CE5E8::vf_018).
    RwInt32 get_unk_61C()
    {
        return unk_61C;
    }

    // Stops its current performance (type_3D2CD0::sub_6D380); only the
    // width is known.
    void sub_13F4F0();
    // Blends head tracking in or out over unk_1DD8 frames, starting and
    // stopping its procedural track (sub_136CF0 calls it each frame).
    void sub_134160();
    // Sets it up from its trigger arg_0 (the constructor calls it); returns
    // 1.
    RwInt32 sub_135430(struct SoldierTrigger *arg_0);
    // Puts its weapon away, when it has a valid one; changes it to the
    // type arg_0.
    void sub_136D40();
    void sub_136DA0(RwInt32 arg_0);
    // The five-way blends of modes 0 and 1 (vf_21C runs them while flags 1
    // and 2 of unk_824 are set).
    void sub_139620();
    void sub_13A410();
    // Hold copies of the clump arg_0 in unk_828 and unk_834.
    void sub_13ACE0(RpClump *arg_0);
    void sub_13ADA0(RpClump *arg_0);
    // Adds arg_0 of its full hit points (the player's sub_101550).
    void sub_13F940(RwReal arg_0);
    // The five-way blend's weighting (as type_3D32F8::sub_76E70) and the
    // sector of *arg_0 among the directions arg_4[1] to arg_4[4].
#ifdef CODFH_SP // single player's sub_13A070 takes no blend (SP 0xE6580 ends ret 8)
    void sub_13A070(RwInt32 *arg_0, RwReal *arg_4);
#else
    void sub_13A070(RwInt32 *arg_0, RwReal *arg_4, RwReal arg_8);
#endif
    RwInt32 sub_13A1F0(RwV3d *arg_0, RwV3d *arg_4);
    // Aims its mounted weapon (vf_04C passes its time); the argument is
    // unused.
    void sub_13F350(RwReal arg_0);
    // Puts the weapon arg_0's model in its hand at the bone arg_4 (vf_04C).
    void sub_138760(type_15CCE0 *arg_0, RwInt32 arg_4, RwInt32 arg_8);
    // Takes arg_0 damage.
    void sub_13C490(RwInt32 arg_0);
    // vf_008, as the image's vtable has it (a trivial body, folded into
    // sub_6FCD0 with every other copy).
    virtual type_3DAFC8 *vf_008()
    {
        return this;
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
    // vf_160, as the image's vtable has it (a trivial body, folded into
    // sub_177040 with every other copy).
    virtual RwInt32 vf_160()
    {
        return unk_3E0.sub_15EF80();
    }
    // vf_1F0, as the image's vtable has it (a trivial body, folded into
    // sub_177340 with every other copy).
    virtual RwReal vf_1F0()
    {
#ifdef CODFH_SP // single player scales by the difficulty (SP 0xEC0B0)
        return unk_3E0.sub_15EDE0() * get_4F28C0();
#else
        return unk_3E0.sub_15EDE0() * 1.0f;
#endif
    }
    // Overrides the image's vtable has whose bodies are type_3DDB98's vf_078
    // and type_3D5658's vf_0E4 and vf_0E8 (ICF folded them; defined in
    // unit_1340D0).
    virtual void vf_078();
    virtual RwInt32 vf_0E4(RwInt32 arg_0);
    virtual RwInt32 vf_0E8();
};
typedef RwChar type_3DAFC8_size_check[sizeof(type_3DAFC8) == 0x2170 ? 1 : -1];

// Head tracking's procedural track callback (sub_134160 starts it).
void sub_134320(struct type_7C8D0 *arg_0, struct type_80300 *arg_4, RwInt32 arg_8,
                bool arg_C);

// The damage multipliers by the part a bullet hits (0x4B92D8).
extern RwReal flt_4B92D8[9];

// The damage multiplier for the part arg_0, 1 from 9 on: an inline with no
// address and so no database name, named for what it returns. Evidence:
// type_3DAFC8::vf_064 (and the remote player's, sub_1C0430) copies the part into a temporary and reads the result through
// another.
inline RwReal part_damage_multiplier(RwInt32 arg_0)
{
    if (arg_0 < 9)
        return flt_4B92D8[arg_0];
    return 1.0f;
}

// Sets the damage multiplier for the part arg_0 (below 9). Evidence: the
// shell's HandleAttributes (sub_B0980) stores the value into a temporary
// before its bound check.
inline void set_part_multiplier(RwInt32 arg_0, RwReal arg_4)
{
    if (arg_0 < 9)
        flt_4B92D8[arg_0] = arg_4;
}

#endif
