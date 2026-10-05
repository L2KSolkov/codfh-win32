/*
 * type_4D53F8: an NPC weapon's settings (0x18C bytes), 128 of them at
 * dword_4D53F8; sub_15CB10 returns one by index (0 outside 0 to 127).
 * CNPCWeaponBehavior's HandleAttributes (sub_A5AC0) fills one from its
 * commands, some fields through setters; only the fields it and they write
 * are known.
 */
#ifndef TYPE_4D53F8_H
#define TYPE_4D53F8_H

#include "rw/ostypes.h"
#include "types/type_3DF8D8.h"
#include "types/type_F2880.h"
#include "types/type_67260.h"

struct type_4D53F8
{
    // Out of line for the array's dynamic initializer (0x30BC10, no unit
    // places it yet) and its destructor thunk (sub_30E860): the destructor
    // releases it when ready.
    type_4D53F8();
    ~type_4D53F8();
    // Clears it (the game's set-up, sub_15C790, for each of them) and
    // returns 1.
    RwInt32 sub_15C980();
    // Marks it unready (unk_44) and returns 1 (sub_15C7D0, the
    // destructor).
    RwInt32 sub_15CA80();
    // Marks it ready (unk_44) and returns 1 (CNPCWeaponBehavior's
    // HandleEvents, on the message Id).
    RwInt32 sub_15CAA0();
    // Registers its names (unk_48, and unk_58 when unk_74 is set; SoldierTrigger's
    // weapons).
    void sub_15CAC0();
    // Setters: unk_94's unk_40_r, unk_44, unk_48, unk_04_r (from an
    // unsigned), unk_4C_r, then unk_E4
    // and unk_74 (which does more with a nonzero value).
    void sub_15CBD0(RwReal arg_0);
    void sub_15CBF0(RwInt32 arg_0);
    void sub_15CC10(RwInt32 arg_0);
    void sub_15CC30(RwUInt32 arg_0);
    void sub_15CC60(RwReal arg_0);
    void sub_15CC80(RwReal arg_0);
    void sub_15CCA0(RwInt32 arg_0);

    RwInt32 unk_00;
    RwInt32 unk_04;
    RwInt32 unk_08;
    RwReal unk_0C;
    RwInt32 unk_10;
    RwInt32 unk_14;
    RwInt32 unk_18;
    RwInt32 unk_1C;
    RwInt32 unk_20;
    RwReal unk_24;
    RwInt32 unk_28;
    RwInt32 unk_2C;
    RwInt32 unk_30;
    RwInt32 unk_34;
    type_F2880 unk_38;          // a particle system
    RwInt32 unk_44;
    type_3DF8D8_04 unk_48;
    type_3DF8D8_04 unk_50;
    type_3DF8D8_04 unk_58;
    type_3DF8D8_04 unk_60;
    type_3DF8D8_04 unk_68;
    RwInt32 unk_70;
    RwInt32 unk_74;
    RwInt32 unk_78;
    union
    {
        RwInt32 unk_7C;         // written as an integer (sub_A5AC0)
        RwReal unk_7C_r;        // its shots' speed; a grenade's the arc
                                // needs (type_15CCE0::sub_15DE60)
    };
    RwInt32 unk_80;
    RwInt32 unk_84;
    union
    {
        struct
        {
            RwInt32 unk_88;
            RwInt32 unk_8C;
            RwInt32 unk_90;
        };
        RwV3d unk_88_v;         // the weapon copies it whole (sub_15D010)
    };
    type_67260 unk_94;          // its bullets' settings (unk_00 3 with
                                // unk_74 set, else 0)
    RwReal unk_E4;
    RwInt32 unk_E8;
    RwReal unk_EC;
    RwReal unk_F0;
    RwInt32 unk_F4;
    RwInt32 unk_F8;
    RwReal unk_FC;
    RwReal unk_100;
    RwInt32 unk_104;
    RwInt32 unk_108;
    RwInt32 unk_10C;
    RwReal unk_110;
    RwInt32 unk_114;
    RwReal unk_118;
    RwReal unk_11C;
    RwReal unk_120;
    RwInt32 unk_124;
    RwInt32 unk_128;
    RwInt32 unk_12C;
    RwInt32 unk_130;
    RwInt32 unk_134;
    RwInt32 unk_138;
    RwInt32 unk_13C;
    RwInt32 unk_140;
    RwInt32 unk_144;
    RwInt32 unk_148;
    RwInt32 unk_14C;
    RwInt32 unk_150;
    RwReal unk_154;
    RwReal unk_158;
    RwReal unk_15C;
    RwReal unk_160;
    union
    {
        RwInt32 unk_164;        // written as an integer (sub_A5AC0)
        RwReal unk_164_r;       // read as a real: the recoil's growth
                                // while firing (type_15CCE0::sub_15D600)
    };
    RwReal unk_168;
    RwReal unk_16C;
    RwReal unk_170;
    RwReal unk_174;
    RwReal unk_178;
    RwReal unk_17C;
    RwReal unk_180;
    RwReal unk_184;
    RwReal unk_188;
};
typedef RwChar type_4D53F8_size_check[sizeof(type_4D53F8) == 0x18C ? 1 : -1];

extern type_4D53F8 dword_4D53F8[128];

// NPC weapon settings arg_0 (0 outside 0 to 127).
type_4D53F8 *sub_15CB10(RwInt32 arg_0);
// The index of the NPC weapon settings whose name (unk_48) is the key arg_0,
// or -1 (none for a key of 0 or -1).
RwInt32 sub_15CB40(const type_3DF8D8_04 *arg_0);

#endif
