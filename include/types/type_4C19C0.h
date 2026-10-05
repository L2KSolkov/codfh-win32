/*
 * type_4C19C0: a weapon's settings (0x550 bytes), 39 of them at dword_4C19C0;
 * sub_119B70 returns one by index (0 outside 0 to 38). CWeaponBehavior's
 * HandleAttributes (sub_C12C0) fills one from its commands, and those of
 * CExplosiveBehavior (sub_C4930), CAntiTankBehavior (sub_C4E30) and
 * CGrenadeBehavior (sub_C5020) more; only the fields they write are known,
 * and their types only as they write them.
 *
 *   +0x1C0 to +0x1D8, +0x3EC to +0x404  six points each player's copy of the
 *                    weapon (type_10F710::unk_1A48) takes too, at +0x238 on
 */
#ifndef TYPE_4C19C0_H
#define TYPE_4C19C0_H

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "types/type_3DF8D8.h"

struct type_4C19C0
{
    // Its keys empty. Inline, but not expanded: dword_4C19C0's dynamic
    // initializer calls its out-of-line copy (sub_11DAB0) and keeps the 8
    // bytes VC7.1 reserved for it in its frame.
    type_4C19C0()
    {
    }

    type_3DF8D8_04 unk_00;
    RwUInt8 unk_08[0x4];
    type_3DF8D8_04 unk_0C;
    type_3DF8D8_04 unk_14;
    RwUInt8 unk_1C;
    RwUInt8 unk_1D[0x3];
    RwInt32 unk_20;
    RwInt32 unk_24;             // its streamed group (sub_16F860: -1 while
                                // not streamed)
    RwInt32 unk_28;
    RwInt32 unk_2C;
    RwInt32 unk_30;
    RwInt32 unk_34;
    RwInt32 unk_38;
    RwInt32 unk_3C;
    RwInt32 unk_40;
    RwInt32 unk_44;
    RwInt32 unk_48;
    RwInt32 unk_4C;
    RwInt32 unk_50;
    RwInt32 unk_54;
    RwInt32 unk_58;
    RwInt32 unk_5C;
    RwInt32 unk_60;
    RwInt32 unk_64;
    RwInt32 unk_68;
    RwInt32 unk_6C;
    RwInt32 unk_70;
    RwInt32 unk_74;
    RwInt32 unk_78;
    RwInt32 unk_7C;
    RwInt32 unk_80;
    RwInt32 unk_84;
    RwInt32 unk_88;
    RwInt32 unk_8C;
    RwInt32 unk_90;
    RwInt32 unk_94;
    union
    {
        RwInt32 unk_98;
        RwReal unk_98_f;    // the tank main gun's shake, as a float (the
                            // tank's vf_300)
    };
    RwReal unk_9C;
    union
    {
        RwInt32 unk_A0;
        RwReal unk_A0_f;    // as a float (the launcher's sub_11B040)
    };
    union
    {
        RwInt32 unk_A4;
        RwReal unk_A4_f;    // as a float (the launcher's sub_11B040)
    };
    RwReal unk_A8;
    union
    {
        RwInt32 unk_AC;
        RwReal unk_AC_f;    // as a float (the launcher's sub_11B040)
    };
    RwInt32 unk_B0;
    RwInt32 unk_B4;
    union
    {
        RwInt32 unk_B8;
        RwReal unk_B8_f;    // as a float (the mounted weapon's fire)
    };
    RwReal unk_BC;
    union
    {
        RwInt32 unk_C0;
        RwReal unk_C0_f;    // as a float (the launcher's sub_11B040)
    };
    RwInt32 unk_C4;
    RwUInt32 unk_C8;            // a clip's rounds (the player's start divides
                                // by it, unsigned)
    RwUInt32 unk_CC;            // the most rounds in reserve
    RwReal unk_D0;
    RwInt32 unk_D4;
    RwInt32 unk_D8;
    union
    {
        RwInt32 unk_DC;
        RwReal unk_DC_f;        // (the melee strike copies it as a real)
    };
    RwReal unk_E0;
    RwReal unk_E4;
    RwReal unk_E8;
    RwReal unk_EC;
    RwReal unk_F0;
    RwReal unk_F4;
    RwReal unk_F8;
    RwReal unk_FC;
    RwReal unk_100;
    RwReal unk_104;
    RwReal unk_108;
    RwReal unk_10C;
    RwReal unk_110;
    RwReal unk_114;
    RwReal unk_118;
    RwReal unk_11C;
    RwReal unk_120;
    RwReal unk_124;
    RwReal unk_128;
    RwReal unk_12C;
    RwReal unk_130;
    RwReal unk_134;
    RwReal unk_138;
    RwReal unk_13C;
    RwReal unk_140;
    RwReal unk_144;
    RwInt32 unk_148;
    RwUInt8 unk_14C;
    RwUInt8 unk_14D;
    RwUInt8 unk_14E[0x2];
    RwReal unk_150;
    RwReal unk_154;
    RwReal unk_158;
    RwReal unk_15C;
    RwReal unk_160;
    RwReal unk_164;
    RwV3d unk_168;
    RwV3d unk_174;
    RwUInt8 unk_180[0xC];
    union
    {
        RwInt32 unk_18C;
        RwReal unk_18C_f;    // as a float (the mounted weapon's fire)
    };
    union
    {
        RwInt32 unk_190;
        RwReal unk_190_f;    // as a float (the mounted weapon's fire)
    };
    union
    {
        RwInt32 unk_194;
        RwReal unk_194_f;    // as a float (the mounted weapon's fire)
    };
    union
    {
        RwInt32 unk_198;
        RwReal unk_198_f;    // as a float (the mounted weapon's fire)
    };
    union
    {
        struct
        {
            RwV3d unk_19C;
            RwV3d unk_1A8;
            RwV3d unk_1B4;
        };
        RwV3d unk_19C_a[3]; // by stance: the weapon sway's offset (the
                            // player's sub_10DBD0)
    };
    union
    {
        struct
        {
            RwV3d unk_1C0;
            RwV3d unk_1CC;
            RwV3d unk_1D8;
        };
        RwV3d unk_1C0_a[3];     // by stance (the copies' unk_238_a)
    };
    union
    {
        struct
        {
            RwV3d unk_1E4;
            RwV3d unk_1F0;
            RwV3d unk_1FC;
        };
        RwV3d unk_1E4_a[3]; // by stance: the sway's swing
    };
    union
    {
        struct
        {
            RwV3d unk_208;
            RwV3d unk_214;
            RwV3d unk_220;
        };
        RwV3d unk_208_a[3]; // by stance: the swing's rates
    };
    union
    {
        struct
        {
            RwInt32 unk_22C;
            RwInt32 unk_230;
            RwInt32 unk_234;
        };
        RwReal unk_22C_r[3]; // by stance: the swing's speed by the stick
    };
    union
    {
        struct
        {
            RwV3d unk_238;
            RwV3d unk_244;
            RwV3d unk_250;
        };
        RwV3d unk_238_a[3]; // likewise, with the recoil's second settings
    };
    union
    {
        struct
        {
            RwV3d unk_25C;
            RwV3d unk_268;
            RwV3d unk_274;
        };
        RwV3d unk_25C_a[3]; // likewise
    };
    union
    {
        struct
        {
            RwInt32 unk_280;
            RwInt32 unk_284;
            RwInt32 unk_288;
        };
        RwReal unk_280_r[3]; // the swing's own speed with them
    };
    bool unk_28C;
    RwUInt8 unk_28D[0x1B];
    union
    {
        struct
        {
            RwInt32 unk_2A8;
            RwInt32 unk_2AC;
            RwInt32 unk_2B0;
        };
        RwUInt32 unk_2A8_u[3];    // by stance: the shots before the recoil kicks (vf_018)
    };
    union
    {
        struct
        {
            RwInt32 unk_2B4;
            RwInt32 unk_2B8;
            RwInt32 unk_2BC;
        };
        RwReal unk_2B4_r[3];   // by stance (the player's recoil, vf_038)
    };
    union
    {
        struct
        {
            RwInt32 unk_2C0;
            RwInt32 unk_2C4;
            RwInt32 unk_2C8;
        };
        RwReal unk_2C0_r[3];   // by stance (the weapon copy's fire, vf_018)
    };
    union
    {
        struct
        {
            RwInt32 unk_2CC;
            RwInt32 unk_2D0;
            RwInt32 unk_2D4;
        };
        RwReal unk_2CC_r[3];   // by stance (the weapon copy's fire, vf_018)
    };
    union
    {
        struct
        {
            RwInt32 unk_2D8;
            RwInt32 unk_2DC;
            RwInt32 unk_2E0;
        };
        RwReal unk_2D8_r[3];   // by stance (the weapon copy's fire, vf_018)
    };
    union
    {
        struct
        {
            RwInt32 unk_2E4;
            RwInt32 unk_2E8;
            RwInt32 unk_2EC;
        };
        RwReal unk_2E4_r[3];   // by stance (the player's recoil, vf_038)
    };
    union
    {
        struct
        {
            RwInt32 unk_2F0;
            RwInt32 unk_2F4;
            RwInt32 unk_2F8;
        };
        RwReal unk_2F0_r[3];   // the spread by stance (the tank's vf_2A8)
    };
    union
    {
        struct
        {
            RwInt32 unk_2FC;
            RwInt32 unk_300;
            RwInt32 unk_304;
        };
        RwReal unk_2FC_r[3];   // by stance (the player's recoil, vf_038)
    };
    RwReal unk_308[3];          // by stance: the crosshair's least and
    RwReal unk_314[3];          // greatest spread (type_DC400::sub_E08B0)
    bool unk_320;
    RwUInt8 unk_321[0x3];
    RwReal unk_324;
    RwUInt8 unk_328[0x18];
    RwInt32 unk_340;
    RwInt32 unk_344;
    RwInt32 unk_348;
    union
    {
        struct
        {
            RwInt32 unk_34C;
            RwInt32 unk_350;
            RwInt32 unk_354;
        };
        RwReal unk_34C_r[3];   // by stance (the player's recoil, vf_038)
    };
    union
    {
        struct
        {
            RwInt32 unk_358;
            RwInt32 unk_35C;
            RwInt32 unk_360;
        };
        RwReal unk_358_r[3];   // by stance (the weapon copy's fire, vf_018)
    };
    union
    {
        struct
        {
            RwInt32 unk_364;
            RwInt32 unk_368;
            RwInt32 unk_36C;
        };
        RwReal unk_364_r[3];   // by stance (the weapon copy's fire, vf_018)
    };
    union
    {
        struct
        {
            RwInt32 unk_370;
            RwInt32 unk_374;
            RwInt32 unk_378;
        };
        RwReal unk_370_r[3];   // by stance (the weapon copy's fire, vf_018)
    };
    union
    {
        struct
        {
            RwInt32 unk_37C;
            RwInt32 unk_380;
            RwInt32 unk_384;
        };
        RwReal unk_37C_r[3];   // by stance (the player's recoil, vf_038)
    };
    union
    {
        struct
        {
            RwInt32 unk_388;
            RwInt32 unk_38C;
            RwInt32 unk_390;
        };
        RwReal unk_388_r[3];   // by stance (the weapon copy's fire, vf_018)
    };
    union
    {
        struct
        {
            RwInt32 unk_394;
            RwInt32 unk_398;
            RwInt32 unk_39C;
        };
        RwReal unk_394_r[3];   // by stance (the player's recoil, vf_038)
    };
    bool unk_3A0;
    RwUInt8 unk_3A1[0x3];
    union
    {
        struct
        {
            RwReal unk_3A4;
            RwReal unk_3A8;
            RwReal unk_3AC;
        };
        RwReal unk_3A4_r[3];    // by stance: a range that widens the
                                // player's aim cone (sub_104D00)
    };
    union
    {
        struct
        {
            RwReal unk_3B0;
            RwReal unk_3B4;
            RwReal unk_3B8;
        };
        RwReal unk_3B0_a[3];    // by stance: bounds the copies' sway
    };                          // (unk_298, sub_119830) with unk_410_a
    union
    {
        struct
        {
            RwInt32 unk_3BC;
            RwInt32 unk_3C0;
            RwInt32 unk_3C4;
        };
        RwReal unk_3BC_r[3];    // by stance, with the recoil's second
                                // settings: the look's scale
    };
    union
    {
        struct
        {
            RwV3d unk_3C8;
            RwV3d unk_3D4;
            RwV3d unk_3E0;
        };
        RwV3d unk_3C8_a[3]; // by stance: an offset with them
    };
    union
    {
        struct
        {
            RwV3d unk_3EC;
            RwV3d unk_3F8;
            RwV3d unk_404;
        };
        RwV3d unk_3EC_a[3];     // by stance (the copies' unk_25C_a)
    };
    union
    {
        struct
        {
            RwReal unk_410;
            RwReal unk_414;
            RwReal unk_418;
        };
        RwReal unk_410_a[3];
    };
    RwUInt8 unk_41C[0x60];
    union
    {
        struct
        {
            RwInt32 unk_47C;
            RwInt32 unk_480;
            RwInt32 unk_484;
        };
        RwReal unk_47C_r[3];    // by stance, with the recoil's second
                                // settings (type_10F710::sub_10B930)
    };
    union
    {
        RwInt32 unk_488;
        RwReal unk_488_f;    // as a float (the mounted weapon's fire)
    };
    union
    {
        RwInt32 unk_48C;
        RwReal unk_48C_f;    // as a float (the mounted weapon's fire)
    };
    RwReal unk_490;
    RwReal unk_494;
    union
    {
        struct
        {
            RwReal unk_498;
            RwReal unk_49C;
        };
        RwReal unk_498_a[2];    // by the throw (the grenade handler, sub_1AE8F0)
    };
    RwInt32 unk_4A0;
    RwInt32 unk_4A4;
    RwInt32 unk_4A8;
    union
    {
        struct
        {
            union
            {
                RwInt32 unk_4AC;
                RwReal unk_4AC_f;    // as a float (the launcher's sub_11B040)
            };
            RwInt32 unk_4B0;
        };
        RwInt32 unk_4AC_a[2];   // by the throw (the grenade handler, sub_1AE8F0)
    };
    RwReal unk_4B4;
    union
    {
        RwInt32 unk_4B8;
        RwReal unk_4B8_f;    // as a float (the launcher's sub_11B040)
    };
    RwReal unk_4BC;
    RwReal unk_4C0;
    union
    {
        RwInt32 unk_4C4;
        RwReal unk_4C4_f;    // as a float (the launcher's sub_11B040)
    };
    union
    {
        RwInt32 unk_4C8;
        RwReal unk_4C8_f;    // as a float (the launcher's sub_11B040)
    };
    RwReal unk_4CC;
    RwInt32 unk_4D0;
    RwInt32 unk_4D4;
    RwReal unk_4D8;
    RwInt32 unk_4DC;
    RwInt32 unk_4E0;
    RwInt32 unk_4E4;
    RwReal unk_4E8;
    RwReal unk_4EC;
    RwReal unk_4F0;
    RwReal unk_4F4;
    RwReal unk_4F8;
    RwInt32 unk_4FC;
    RwInt32 unk_500;
    RwReal unk_504;
    RwReal unk_508;
    RwReal unk_50C;
    RwReal unk_510;
    RwReal unk_514;
    RwInt32 unk_518;
    RwInt32 unk_51C;
    RwInt32 unk_520;
    RwReal unk_524;
    RwInt32 unk_528;
    RwInt32 unk_52C;
    RwInt32 unk_530;
    RwInt32 unk_534;
    RwInt32 unk_538;
    RwReal unk_53C;
    RwInt32 unk_540;
    RwInt32 unk_544;
    RwInt32 unk_548;
    RwInt32 unk_54C;
};
typedef RwChar type_4C19C0_size_check[sizeof(type_4C19C0) == 0x550 ? 1 : -1];

// The 39 weapon settings (sub_116310 clears them).
extern type_4C19C0 dword_4C19C0[39];
// Weapon settings arg_0 (0 outside 0 to 38).
type_4C19C0 *sub_119B70(RwInt32 arg_0);

// The keys of the GameWeapons death animations PlayerTrigger registers
// (sub_AD030): "DeathAnims+PPSH_Hit" at dword_4C1970 (four words cleared),
// then the ten Stand_Death_A to Bipod_Freeze at dword_4C1980; sub_116310
// clears them.
extern RwInt32 dword_4C1970[4];
extern RwInt32 dword_4C1980[10];

#endif
