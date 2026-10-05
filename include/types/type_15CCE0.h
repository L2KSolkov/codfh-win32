/*
 * type_15CCE0: an object embedded twice in type_3DAFC8, at +0x3E0 and +0x4E0,
 * anchored at its constructor sub_15CCE0 (no vtable; destructor sub_15CF60),
 * which sub_134C50 calls for both. The constructor and destructor reach
 * +0xDC, where three 12-byte elements start, so it is at least 0x100 bytes,
 * and the two instances are 0x100 apart, so it is exactly that.
 *
 *   +0x00 unk_00  tested against zero by sub_14DF0; only its width is known
 *   +0x04 unk_04  a kind code: sub_15EF80 maps it through sub_15EFA0's
 *                 128-case table to 0-4 or 8
 */
#ifndef TYPE_15CCE0_H
#define TYPE_15CCE0_H

#include "rw/ostypes.h"
#include "rw/bamatrix.h"
#include "types/type_129_base.h"
#include "types/type_D48D0.h"
#include "types/type_F2880.h"
#include "types/type_495F0.h"

struct type_15CCE0
{
    RwInt32 unk_00;
    RwInt32 unk_04;         // the weapon type ("GetWeaponType")
    RwInt32 unk_08;         // taken up (the destructor puts it away)
    RwInt32 unk_0C;
    type_129940 unk_10;     // its model ("EnableWeaponRender")
    RwInt32 unk_1C;         // none left when 0 (type_3DAFC8::vf_13C)
    RwInt32 unk_20;         // an infinite clip ("InfiniteAmmoClip",
                            // type_3DAFC8::vf_248)
    RwUInt8 unk_24[0xC];
    RwMatrix unk_30;        // its model's matrix as it was (the soldier's
                            // vf_03C watches it for a dropped weapon)
    RwReal unk_70;          // how long it has lain still
    RwInt32 unk_74;         // its bullets' kind (0x201, 0x202, 0x401, 0x402,
                            // 0x1001 or 0x1002 by weapon and owner)
    type_D48D0 unk_78;
    RwInt32 unk_7C;
    RwInt32 unk_80;
    RwInt32 unk_84;
    RwReal unk_88;          // time to its next shot (by the settings'
                            // unk_124)
    RwInt32 unk_8C;
    RwInt32 unk_90[3];
    RwInt32 unk_9C;
    RwInt32 unk_A0;         // set while the soldier fires at no target
                            // ("SetFireAtNoTarget" stores its inverse)
    RwReal unk_A4;
    RwReal unk_A8;
    RwInt32 unk_AC;
    RwInt32 unk_B0;
    RwInt32 unk_B4;         // its settings' unk_78
    RwV3d unk_B8;
    RwInt32 unk_C4;         // and "SetFireAtNoTarget"'s value itself
    RwReal unk_C8;          // -25 for some weapons (sub_15EE60), else 0
    RwInt32 unk_CC;         // set while it aims at unk_D0
    RwV3d unk_D0;           // (type_3DAFC8::sub_138D00)
    type_F2880 unk_DC[3];       // particle systems

    // Its constructor and destructor (sub_15CCE0, sub_15CF60).
    type_15CCE0();
    ~type_15CCE0();

    // An inline setter for unk_A0, with no address and so no database name;
    // named for its field. Evidence: "SetFireAtNoTarget" stores through a
    // temporary holding &unk_3E0 of the vf_008 result.
    void set_unk_A0(RwInt32 arg_0)
    {
        unk_A0 = arg_0;
    }

    RwInt32 sub_15EF80();
    // An inline accessor for unk_00, with no address and so no database name;
    // named for its field. Evidence: type_3DAFC8::has_grenade_in_hand
    // ("DoIHaveAGrenadeInHand") tests it through a compiler temporary.
    RwInt32 get_unk_00()
    {
        RwInt32 r = unk_00;
        return r;
    }
    // Likewise for unk_18 ("EnableWeaponRender" reads it through a
    // temporary at each use).
    RpClump *get_unk_18()
    {
        RpClump *r = unk_10.unk_08;
        return r;
    }
    // An inline accessor for unk_04, with no address and so no database
    // name; named for its field. Evidence: type_3DAFC8::sub_138760 and
    // vf_134 switch on it through a temporary that first takes a copy of
    // the inline's own return slot (a direct return, no local), as the
    // player's sub_10F900 does with type_3DBC78::get_unk_1188.
    RwInt32 get_unk_04()
    {
        return unk_04;
    }
    // A class of the unk_04 code: 1, 2, 3 or 4 (0 for codes it does not
    // list); AIData::sub_29630 passes it to sub_6D0A0.
    RwInt32 sub_15F0A0();
    // A performance selector sub_47F90 adds to the owner's flags; only the
    // width is known.
    RwInt32 sub_15EE90();
    // The weapon's ranges, whether it is a bolt-action rifle, its reload
    // and its force (type_3DAFC8's vf_144 to vf_15C, vf_140, vf_1F4); only
    // the widths are known.
    RwReal sub_15EBF0();
    RwReal sub_15EC30();
    RwReal sub_15ECB0();
    RwReal sub_15ED20();
    RwReal sub_15ED60();
    RwReal sub_15EDA0();
    RwInt32 sub_15EC70();
    void sub_15E9B0(RwInt32 arg_0);
    RwReal sub_15EE20();
    RwReal sub_15EDE0();
    // Put the weapon away (type_3DAFC8::sub_136D40), and take up the type
    // arg_4 for the owner arg_0 (sub_136DA0); only the widths are known.
    void sub_15D420();
    void sub_15D360();
    void sub_15D010(struct type_3DAFC8 *arg_0, RwInt32 arg_4);
    // Only the widths are known.
    void sub_15E950(RwInt32 arg_0);
    RwInt32 sub_15EE60();
    void sub_15D900(RwInt32 arg_0);
    void sub_15EB50();
    // Fires at the point *arg_0; only the width is known.
    void sub_15DE60(RwV3d *arg_0);
    // Holds the particle system arg_4 in its slot arg_0 (0 to 2), which
    // then calls sub_15D570 with this weapon.
    void sub_15D5B0(RwInt32 arg_0, struct type_F2FF0 *arg_4);
    void sub_15D3E0();
    // Fires (arg_0 1) or stops (type_3DAFC8's vf_1B0, vf_1B4); only the
    // widths are known.
    void sub_15D510(RwInt32 arg_0, RwInt32 arg_4);
    // Where it aims into *arg_0 (type_3DAFC8::vf_244); only the width is
    // known.
    void sub_15E9E0(RwV3d *arg_0);
    // Its muzzle's position into *arg_0 (type_3DAFC8::sub_138D00); only the
    // width is known.
    void sub_15E890(RwV3d *arg_0);
    // Its state from arg_0 (type_3DAFC8::sub_138760 passes an integer as a
    // float); only the width is known.
    void sub_15D600(RwReal arg_0);
    // Aims at the point *arg_0 (when given) and stops: inlines with no
    // address and so no database name, named for what they do. Evidence:
    // type_3DAFC8::sub_138D00 holds &unk_3E0 in a temporary (the inline's
    // this) and tests the point's address before copying it.
    void aim_at(RwV3d *arg_0)
    {
        unk_CC = 1;
        if (arg_0)
            unk_D0 = *arg_0;
    }
    void stop_aiming(RwV3d *arg_0)
    {
        unk_CC = 0;
        if (arg_0)
            unk_D0 = *arg_0;
    }
    // Drops the grenade in hand at *arg_0 ("DropGrenade" passes 0, 90,
    // 3000, 0 and -1 for the rest); only the widths are known.
    void sub_15D8A0(RwV3d *arg_0, RwInt32 arg_4, RwInt32 arg_8, RwReal arg_C, RwReal arg_10,
                    RwReal arg_14);
};

// Whether arg_0 is a weapon type (0 to 0x7F): an inline with no address and
// so no database name, named for what it tests. Evidence: type_3DAFC8's
// sub_136D40 copies the type into a temporary and tests a 1/0 result
// temporary.
inline RwInt32 valid_weapon_type(RwInt32 arg_0)
{
    if (arg_0 >= 0 && arg_0 < 0x80)
        return 1;
    return 0;
}
// The grenade drop's settings (sub_15D8A0 stores its arguments here for
// sub_15DE60).
extern RwInt32 dword_4D53E0;
extern RwInt32 dword_4D53E4;
extern RwReal dword_4D53E8;
extern RwReal dword_4D53EC;          // a random turn's bound
extern RwReal dword_4D53F0;
// Added to a weapon's unk_174 setting (sub_15ECB0) unless its class is 3.
extern RwReal dword_4D53F4;

// What sub_15F2C0 returns for a shot: only its unk_1C (the grenade drop's
// fuse, sub_15DE60 adds to it) is known.
struct type_15F2C0
{
    RwUInt8 unk_00[0x1C];
    RwReal unk_1C;
};
// The difficulty's spread multipliers (by dword_42B714).
extern RwReal flt_4F2878[3];

// The class of the weapon type arg_0 (type_15CCE0::sub_15EF80).
RwInt32 sub_15EFA0(RwInt32 arg_0);

// A weapon's particle system's callback (its unk_154; its unk_158 the
// weapon): the system at the model's "FIRE" point.
RwInt32 sub_15D570(struct type_F2FF0 *arg_0);

// An NPC weapon definition's model (the value sub_18F800 finds for the
// reference at its +0x10): an inline with no address and so no database
// name, named for what it returns. Evidence: sub_15D010 copies the
// definition into an argument temporary after the getter's.
inline RwInt32 definition_model(struct type_3DF8D8 *arg_0)
{
    return ((type_495F0 *)arg_0)->sub_18F800((type_18F800 *)&arg_0->unk_10);
}
typedef RwChar type_15CCE0_size_check[sizeof(type_15CCE0) == 0x100 ? 1 : -1];

#endif
