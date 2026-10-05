/*
 * PlayerTrigger (the class name it registers with the class factory at
 * 0x30A8E9, with its MakeNew, sub_A9980, and its size, 0x470): the player's
 * trigger, derived from Trigger, anchored at its vtables off_3D5F98 and
 * off_3D5F90 (+0x18), which its constructor (sub_A9A00) and destructor
 * (sub_AA2F0) install. It holds the player's settings, which it copies into
 * the player entity (sub_ACF10), its weapons (39 flags and slots), and the
 * player entity itself (unk_46C), which its destructor deletes. It listens
 * to Id, dword_4B8750, RWS::iMsgStartSystem, dword_4B67B8, dword_4B67C0 and
 * dword_4B67B0. The pause menu's options (sub_18E380) and the front end's
 * difficulty setting reach it through the player entity's unk_34C.
 */
#ifndef TYPES_PLAYERTRIGGER_H
#define TYPES_PLAYERTRIGGER_H

#include "rw/ostypes.h"
#include "types/type_3DF8D8.h"
#include "types/type_44350.h"
#include "types/type_D48D0.h"

struct type_10F710;

// A vector the trigger sets whole through an inline, with no address and so
// no database name. Evidence: the constructor stores each of its four
// vectors (and clears unk_E4 and unk_444) through a temporary holding its
// address, in the order x, y, z.
// It is copied whole into the player's unk_3C_v, an RwV3d.
struct PlayerTrigger_v3d : RwV3d
{
    void set(RwReal arg_0, RwReal arg_4, RwReal arg_8)
    {
        x = arg_0;
        y = arg_4;
        z = arg_8;
    }
};

// The player's default unk_108 (-5.0f), a constant the constructor loads
// from the unit's data rather than as an immediate.
extern const RwReal flt_3D5F84;
// Set once the death animations are registered (sub_AD030); sub_AA3F0
// clears it for the next level.
extern RwInt32 dword_4B67E4;
void sub_AA3F0();

class PlayerTrigger : public Trigger
{
public:
    RWS_MAKENEWCLASS(PlayerTrigger);
    RWS_DECLARE_CLASSID(PlayerTrigger);

    PlayerTrigger(const RWS::CAttributePacket &attr);
    ~PlayerTrigger();

    virtual void HandleAttributes(const RWS::CAttributePacket &attr);
    virtual void HandleEvents(RWS::CMsg &pMsg);
    // Its key (&unk_244).
    // Inline: the constructor's vtable emits them after it, before ??_G (the image's order).
    virtual type_3DF8D8_04 * vf_01C()
    {
        return &unk_244;
    }

    // Puts back the weapons it started with (unk_264, unk_258).
    void sub_AC900();
    // Applies the difficulty (dword_4F28F0's unk_18) to its settings.
    void sub_ACA70();
    // Gives it the weapon arg_0 (arg_4: unused here).
    void sub_ACDB0(RwInt32 arg_0, RwInt32 arg_4);
    // Assigns each weapon's settings their class and names the ones it has.
    void sub_ACE00();
    // Moves the player entity to its own matrix.
    void sub_ACEA0();
    // Copies its settings into the player arg_0.
    void sub_ACF10(type_10F710 *arg_0);
    // Registers the GameWeapons death animations once (dword_4B67E4).
    void sub_AD030();
    // Takes command 111's value and does nothing with it: an inline with no
    // address, named for what it does. Evidence: HandleAttributes (sub_AA400)
    // stores the value in a slot of its own right after the command's (the
    // argument's), and nothing reads it; an empty body, an unused local or a
    // `const &` argument lay the slots out otherwise.
    void skip_value(RwInt32 arg_0)
    {
    }

    RwInt32 unk_C0;             // the player's unk_3D4 (-1)
    RwInt32 unk_C4;             // its pad (the player's unk_3D8)
    RwInt32 unk_C8;             // its index (the player's unk_3DC)
    type_3DF8D8_04 unk_CC;
    RwReal unk_D4;              // the player's unk_48
    RwReal unk_D8;              // unk_50
    RwReal unk_DC;              // unk_4C
    RwReal unk_E0;              // unk_108
    PlayerTrigger_v3d unk_E4;   // unk_3C
    RwReal unk_F0;              // unk_534: tan of the field of view
    RwReal unk_F4;              // unk_53C
    RwReal unk_F8;              // unk_540
    RwInt32 unk_FC;             // unk_19E0: its full hit points
    RwInt32 unk_100;            // unk_19E4 (as a real)
    RwInt32 unk_104;            // unk_19E8 (as a real)
    RwInt32 unk_108[2];         // its two weapons (-1 for none)
    RwUInt8 unk_110[0x4];
    RwInt8 unk_114[0x27];       // set: it has the weapon
    RwUInt8 unk_13B;
    RwInt32 unk_13C;            // its first weapon
    RwInt32 unk_140;
    RwReal unk_144;
    RwReal unk_148;
    RwReal unk_14C;
    RwReal unk_150;
    RwReal unk_154;             // unk_158 by the difficulty
    RwReal unk_158;
    RwInt32 unk_15C;
    RwReal unk_160;
    RwReal unk_164;
    RwReal unk_168;
    RwReal unk_16C;
    RwReal unk_170;
    RwReal unk_174;
    RwReal unk_178;
    RwReal unk_17C;
    RwReal unk_180;
    PlayerTrigger_v3d unk_184;
    PlayerTrigger_v3d unk_190;
    PlayerTrigger_v3d unk_19C;
    PlayerTrigger_v3d unk_1A8;
    RwReal unk_1B4;             // unk_1C0 by the difficulty
    RwReal unk_1B8;
    RwReal unk_1BC;
    RwReal unk_1C0;
    RwReal unk_1C4;             // the easy scale
    RwReal unk_1C8;             // the hard scale
    RwReal unk_1CC;             // unk_1D0 by the difficulty
    RwReal unk_1D0;
    RwInt32 unk_1D4;
    RwReal unk_1D8;
    RwReal unk_1DC;
    RwReal unk_1E0;
    RwReal unk_1E4;
    RwReal unk_1E8;
    RwReal unk_1EC;
    RwReal unk_1F0;
    RwReal unk_1F4;             // unk_1FC by the difficulty
    RwReal unk_1F8;             // unk_200 by the difficulty
    RwReal unk_1FC;
    RwReal unk_200;
    RwReal unk_204;
    RwReal unk_208;             // unk_20C by the difficulty
    RwReal unk_20C;
    RwReal unk_210;
    RwReal unk_214;
    RwReal unk_218;
    RwReal unk_21C;
    RwReal unk_220;
    RwReal unk_224;
    RwReal unk_228;
    RwReal unk_22C;
    RwReal unk_230;
    RwReal unk_234;
    RwReal unk_238;
    RwReal unk_23C;
    RwReal unk_240;
    type_3DF8D8_04 unk_244;
    type_3DF8D8_04 unk_24C;     // "DeathAnims" (a name's key)
    RwInt32 unk_254;
    RwInt32 unk_258[2];         // its first two weapons, as it started
    RwInt32 unk_260;
    RwInt32 unk_264[0x27];      // its weapons' slots as it started (-1 for
                                // none)
    RwInt32 unk_300;            // set: its weapons were changed (dword_4B67B0
                                // puts back the ones it started with)
    RwInt32 unk_304;            // set from option dword_4F2368
    RwReal unk_308;
    RwInt32 unk_30C;
    RwReal unk_310;
    RwReal unk_314;             // the hard scale of unk_1F8, unk_1F4, unk_208
    RwReal unk_318;             // the easy scale of them
    RwReal unk_31C;
    RwReal unk_320;
    RwReal unk_324;
    RwReal unk_328;
    RwReal unk_32C;
    RwReal unk_330;
    RwReal unk_334;
    RwInt32 unk_338;
    RwReal unk_33C;
    RwInt32 unk_340;
    RwReal unk_344;
    RwInt32 unk_348;
    RwReal unk_34C;
    RwReal unk_350;
    RwReal unk_354;
    RwReal unk_358;
    RwReal unk_35C;
    RwReal unk_360;
    RwReal unk_364;
    RwReal unk_368;
    RwReal unk_36C;
    RwReal unk_370;
    RwReal unk_374;
    RwReal unk_378;
    RwReal unk_37C;
    RwInt32 unk_380;
    RwInt32 unk_384[0x27];      // its weapons' slots (-1 for none)
    RwReal unk_420;
    RwReal unk_424;
    RwReal unk_428;
    RwReal unk_42C;
    RwReal unk_430;
    RwReal unk_434;
    RwReal unk_438;
    type_3DF8D8_04 unk_43C;
    PlayerTrigger_v3d unk_444;
    type_3DF8D8_04 unk_450;
    type_3DF8D8_04 unk_458;
    type_3DF8D8_04 unk_460;
    RwInt32 unk_468;            // set once dword_4B8750 has come
    type_D48D0 unk_46C;         // the player entity
    // vf_008, as the image's vtable has it (a trivial body, folded into
    // sub_115460 with every other copy).
    virtual RwInt32 vf_008()
    {
        return 1;
    }
};

#endif
