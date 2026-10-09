// The surfaces' particle events (include/game/surfaceparticles.h). The
// original file name is not in the image, so it is named for its start
// address.

#include "rw/ostypes.h"
#include "rw/bamatrix.h"
#include "game/functions.h"
#include "game/gameloop.h"
#include "game/surfaceparticles.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x004BC894
type_4BC894 *dword_4BC894[4];
// 0x004BC8A4
RwInt32 dword_4BC8A4[4];
// End of its data definitions.


// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0DB@HPOBDACJ@Surfaces?$CLParticles?$CLParticleEvent@ @ 0x003D91E8
// match: ??_C@_0DH@MKIPENJG@Surfaces?$CLParticles?$CLParticleEvent@ @ 0x003D921C
// match: ??_C@_0DC@FNCJFEIH@Surfaces?$CLParticles?$CLParticleEvent@ @ 0x003D9254
// match: ??_C@_0CP@HLKNMMJJ@Surfaces?$CLParticles?$CLParticleEvent@ @ 0x003D9288

// match: ?sub_F25F0@@YAXXZ @ 0x000F25F0
// sp-match: ?sub_F25F0@@YAXXZ @ 0x000B8FC0

void sub_F25F0()
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 4; var_4++)
    {
        dword_4BC894[var_4] = 0;
        dword_4BC8A4[var_4] = 0;
    }
}

// match: ?sub_F2630@@YAXXZ @ 0x000F2630
// sp-match: ?sub_F2630@@YAXXZ @ 0x000B8FF0
void sub_F2630()
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 4; var_4++)
    {
        if (dword_4BC894[var_4])
        {
            delete dword_4BC894[var_4];
        }
    }
    sub_F25F0();
}

// match: ?sub_F2680@@YAXXZ @ 0x000F2680
// sp-match: ?sub_F2680@@YAXXZ @ 0x000B9020
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_F2680()
{
    type_1989D0 *lv_10;
    type_1989D0 *slot_C;
    type_1989D0 *bp_8;
    type_1989D0 *bp_4;

    lv_10 = sub_1989D0("Surfaces+Particles+ParticleEvents+BulletImpact", 0x37, 0, 0, 0);
    lv_10->unk_10 = dword_4BC8A4;
    lv_10->unk_14 = dword_4BC894;
    bp_8 = sub_1989D0("Surfaces+Particles+ParticleEvents+TankShellImpact", 0x37, 0, 0, 0);
    bp_8->unk_10 = &dword_4BC8A4[1];
    bp_8->unk_14 = &dword_4BC894[1];
    bp_4 = sub_1989D0("Surfaces+Particles+ParticleEvents+ArtilleryShellImpact", 0x37, 0, 0, 0);
    bp_4->unk_10 = &dword_4BC8A4[2];
    bp_4->unk_14 = &dword_4BC894[2];
    slot_C = sub_1989D0("Surfaces+Particles+ParticleEvents+AntiTankImpact", 0x37, 0, 0, 0);
    slot_C->unk_10 = &dword_4BC8A4[3];
    slot_C->unk_14 = &dword_4BC894[3];
    dword_4B86FC--;
}

// match: ?sub_F2750@@YAHHHPAURwMatrixTag@@H@Z @ 0x000F2750
// sp-match: ?sub_F2750@@YAHHHPAURwMatrixTag@@H@Z @ 0x000B90B0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_F2750(RwInt32 arg_0, RwInt32 arg_4, RwMatrix *arg_8, RwInt32 arg_C)
{
    type_F2750 *slot_C;
    RwInt32 bp_8;
    RwInt32 bp_4;

    bp_8 = -1;
    if (arg_0 < 4)
    {
        for (bp_4 = 0; bp_4 < dword_4BC8A4[arg_0] && bp_8 == -1; bp_4++)
        {
            if (dword_4BC894[arg_0][bp_4].unk_00 == arg_4)
            {
                bp_8 = bp_4;
            }
        }
        if (bp_8 != -1)
        {
            slot_C = (type_F2750 *)sub_198900((type_3DF8D8_04 *)&dword_4BC894[arg_0][bp_8].unk_04, 0x39, 0, 0, 0, 0);
            if (slot_C)
            {
                for (bp_4 = 0; bp_4 < slot_C->unk_10; bp_4++)
                {
                    if (arg_C)
                    {
                        sub_F2FF0(slot_C->unk_14[bp_4], arg_8, arg_0 == 0, 1, false, true);
                    }
                    else
                    {
                        sub_F2FF0(slot_C->unk_14[bp_4], arg_8, arg_0 == 0, 1, false, false);
                    }
                }
            }
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
    return 1;
}
