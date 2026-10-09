// The soldiers' weapons (type_15CCE0, two in each soldier, type_3DAFC8's
// unk_3E0 and unk_4E0).

#include "rw/ostypes.h"
#include "rw/bamatrix.h"
#include "game/vecutil.h"
#include "types/type_15CCE0.h"
#include "types/type_4D53F8.h"
#include "types/type_495F0.h"
#include "types/type_3DAFC8.h"
#include "game/functions.h"
#include "game/clumpdata.h"
#include "game/frand.h"
#include "types/AIData.h"
#include "types/type_1227C0.h"
#include "game/data.h"
#include "rw/bavector.h"
#include <math.h>
#include "types/type_F2FF0.h"
#include "types/type_3D3548.h"
#include <string.h>
#include "rws/clumphelper.h"
#include "types/type_3DF8D8.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003DC6B4
extern const RwReal flt_3DC6B4 = 16.666666f;
// 0x003DC6B8
extern const RwReal flt_3DC6B8 = 16.666666f;
// 0x004D53E0
RwInt32 dword_4D53E0;
// 0x004D53E4
RwInt32 dword_4D53E4;
// 0x004D53E8
RwReal dword_4D53E8;
// 0x004D53EC
RwReal dword_4D53EC;
// 0x004D53F0
RwReal dword_4D53F0;
// 0x004D53F4
RwReal dword_4D53F4;
// End of its data definitions.


// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0BE@LDBFMJMN@SingleBurstFinished?$AA@ @ 0x003D2798
// match: ??_C@_0BC@PKNOEPGK@AllBurstsFinished?$AA@ @ 0x003D27AC
// match: ?flt_3DC6B4@@3MB @ 0x003DC6B4
// match: ?flt_3DC6B8@@3MB @ 0x003DC6B8
// match: __real@b8d1b717 @ 0x003DC6BC
// match: __ehhandler$??0type_15CCE0@@QAE@XZ>1>8 @ 0x0041E064
// match: __ehhandler$??0type_15CCE0@@QAE@XZ>1 @ 0x0041E074
// match: __ehhandler$??1type_15CCE0@@QAE@XZ>1>8 @ 0x0041E090
// match: __ehhandler$??1type_15CCE0@@QAE@XZ>1 @ 0x0041E0B0

// match: ??0type_15CCE0@@QAE@XZ @ 0x0015CCE0
// match: __ehhandler$??0type_15CCE0@@QAE@XZ-0x16 @ 0x00301E10
// match: __ehhandler$??0type_15CCE0@@QAE@XZ @ 0x00301E26
// sp-match: ??0type_15CCE0@@QAE@XZ @ 0x001004D0

type_15CCE0::type_15CCE0()
{
    unk_00 = 0;
    unk_08 = 0;
    unk_88 = 0;
    unk_1C = 0;
    unk_04 = -1;
    unk_B0 = 0;
    unk_B4 = 0;
    unk_20 = 0;
    unk_0C = 0;
    unk_70 = 0.0f;
    unk_80 = 0;
    unk_84 = 0;
    unk_A0 = 0;
    unk_A4 = 0;
    unk_A8 = 0;
    unk_AC = 0;
    unk_CC = 0;
    unk_C4 = 0;
    unk_C8 = 0;
    unk_CC = 0;
    zero_v3d(&unk_D0);
    zero_v3d(&unk_B8);
    memset(unk_90, 0, sizeof(unk_90));
    RwMatrixSetIdentityMacro(&unk_30);
}

// match: ??1type_15CCE0@@QAE@XZ @ 0x0015CF60
// match: __ehhandler$??1type_15CCE0@@QAE@XZ-0x36 @ 0x00301E30
// match: __ehhandler$??1type_15CCE0@@QAE@XZ @ 0x00301E66
// sp-match: ??1type_15CCE0@@QAE@XZ @ 0x00100600
type_15CCE0::~type_15CCE0()
{
    if (unk_08)
        sub_15D360();
}

// match: ?sub_15D010@type_15CCE0@@QAEXPAUtype_3DAFC8@@H@Z @ 0x0015D010
// sp-match: ?sub_15D010@type_15CCE0@@QAEXPAUtype_3DAFC8@@H@Z @ 0x00101250
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Takes up the NPC weapon arg_4 for the soldier arg_0 (unless it holds a
// model or a type already): its definition (the settings' named kind-26
// object), a copy of its model, its handle on the owner, its bullets' kind
// (by weapon and owner) and settings, the settings' first 0x30 bytes
// copied into their bullets' record.
void type_15CCE0::sub_15D010(type_3DAFC8 *arg_0, RwInt32 arg_4)
{
    RwInt32 var_14;
    type_3DF8D8 *lv_10;
    RwInt32 var_C;
    RpClump *bp_8;
    type_4D53F8 *bp_4;

    if (get_unk_18() || unk_04 != -1)
        return;
    bp_4 = sub_15CB10(arg_4);
    unk_0C = (RwInt32)sub_198800(&bp_4->unk_48);
    if (!unk_0C || ((type_3DF8D8 *)unk_0C)->vf_008() != 26)
        return;
    var_C = definition_model((type_3DF8D8 *)unk_0C);
    bp_8 = RpClumpClone((RpClump *)var_C);
    unk_10.sub_129620(bp_8);
    unk_10.sub_129690(arg_0);
    RWS::ClumpHelper::SetCanCollide(*bp_8, 0);
    RWS::ClumpHelper::SetIsVisible(*bp_8, 1);
    unk_B4 = bp_4->unk_78;
    unk_04 = arg_4;
    unk_00 = 0;
    unk_7C = 0;
    unk_CC = 0;
    sub_15E950(1);
    sub_15E9B0(0);
    unk_78.sub_D48D0(arg_0);
    if (bp_4->unk_74)
    {
        lv_10 = sub_198800(&bp_4->unk_58);
        if (lv_10)
            lv_10->vf_008();
        var_14 = ((RwInt32)((type_3DF9C4 *)lv_10)->sub_190A10());
        RWS::ClumpHelper::SetCanCollide(*(RpClump *)var_14, 0);
        bp_4->unk_94.unk_38 = var_14;
    }
    if (sub_15EF80() == 8)
    {
        bp_4->unk_94.unk_38 = var_C;
        bp_4->unk_94.unk_00 = 2;
        if ((arg_0->unk_2C & 7) == 2)
            unk_74 = 0x402;
        else
            unk_74 = 0x401;
    }
    else if ((arg_0->unk_2C & 7) == 2)
    {
        if (bp_4->unk_74)
        {
            unk_74 = 0x1002;
            bp_4->unk_94.unk_00 = 3;
        }
        else
        {
            unk_74 = 0x202;
            bp_4->unk_94.unk_00 = 0;
        }
    }
    else
    {
        if (bp_4->unk_74)
        {
            unk_74 = 0x1001;
            bp_4->unk_94.unk_00 = 3;
        }
        else
        {
            unk_74 = 0x201;
            bp_4->unk_94.unk_00 = 0;
        }
    }
    unk_B8 = bp_4->unk_88_v;
    unk_88 = 0;
    unk_8C = 0;
    unk_9C = 0;
    unk_A4 = bp_4->unk_160;
    unk_A0 = 1;
    unk_C8 = sub_15EE60() ? -25.0f : 0.0f;
    unk_A8 = unk_C8;
    memcpy(bp_4->unk_94.unk_08, bp_4, sizeof(bp_4->unk_94.unk_08));
    if (arg_0->vf_120())
        sub_15D900(0);
    if (bp_4->unk_34)
        unk_90[0] = bp_4->unk_30;
    unk_08 = 1;
}

// match: ?sub_15D360@type_15CCE0@@QAEXXZ @ 0x0015D360
// sp-match: ?sub_15D360@type_15CCE0@@QAEXXZ @ 0x000FFD20
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Puts it away: its particle systems destroyed, its model released.
void type_15CCE0::sub_15D360()
{
    type_F2FF0 *var_8;
    RwInt32 l4;

    for (l4 = 0; l4 < 3; l4++)
    {
        var_8 = unk_DC[l4].get_unk_08();
        if (var_8)
            sub_F3300(var_8);
    }
    unk_10.sub_129940(0);
    unk_04 = -1;
    unk_00 = 0;
    unk_08 = 0;
}

// match: ?sub_15D3E0@type_15CCE0@@QAEXXZ @ 0x0015D3E0
// sp-match: ?sub_15D3E0@type_15CCE0@@QAEXXZ @ 0x000FFD70
// Shows its model (once).
void type_15CCE0::sub_15D3E0()
{
    if (unk_00)
        return;
    unk_00 = 1;
    sub_173180(get_unk_18());
}

// match: ?sub_15D420@type_15CCE0@@QAEXXZ @ 0x0015D420
// sp-match: ?sub_15D420@type_15CCE0@@QAEXXZ @ 0x00100690
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Hides its model: its owner told "AllBurstsFinished" and to stop, the
// firing stopped and its particle systems destroyed.
void type_15CCE0::sub_15D420()
{
    type_F2FF0 *var_C;
    RwInt32 bp_8;
    type_3D3548 *bp_4;

    if (!unk_00)
        return;
    unk_00 = 0;
    sub_1735A0(get_unk_18());
    bp_4 = unk_78.sub_D4910();
    if (bp_4->vf_098())
        sub_6B5F0("AllBurstsFinished", (type_67620 *)(bp_4->vf_098()), 0, 0, 0, 0, 1, 0);
    bp_4->vf_1B0(0);
    unk_8C = 0;
    sub_15EB50();
    for (bp_8 = 0; bp_8 < 3; bp_8++)
    {
        var_C = unk_DC[bp_8].get_unk_08();
        if (var_C)
            sub_F3300(var_C);
    }
}

// match: ?sub_15D510@type_15CCE0@@QAEXHH@Z @ 0x0015D510
// sp-match: ?sub_15D510@type_15CCE0@@QAEXHH@Z @ 0x00100730
void type_15CCE0::sub_15D510(RwInt32 arg_0, RwInt32 arg_4)
{
    unk_8C = arg_0;
    if (!arg_0)
        sub_15EB50();
    else
        unk_7C = 1;
    if (arg_4)
        memcpy(unk_90, (void *)arg_4, sizeof(unk_90));
}

// match: ?sub_15D570@@YAHPAUtype_F2FF0@@@Z @ 0x0015D570
// sp-match: ?sub_15D570@@YAHPAUtype_F2FF0@@@Z @ 0x000FFD90
RwInt32 sub_15D570(type_F2FF0 *arg_0)
{
    type_15CCE0 *var_4;

    var_4 = (type_15CCE0 *)arg_0->unk_158;
    sub_EC2D0(var_4->get_unk_18(), (RwInt32)arg_0, 0x46495245, 0, 1); // not an address: 'FIRE'
    return 1;
}

// match: ?sub_15D5B0@type_15CCE0@@QAEXHPAUtype_F2FF0@@@Z @ 0x0015D5B0
// sp-match: ?sub_15D5B0@type_15CCE0@@QAEXHPAUtype_F2FF0@@@Z @ 0x000FFDC0
void type_15CCE0::sub_15D5B0(RwInt32 arg_0, type_F2FF0 *arg_4)
{
    unk_DC[arg_0].sub_F2880(arg_4);
    if (arg_4)
    {
        arg_4->unk_154 = sub_15D570;
        arg_4->unk_158 = (RwInt32)this;
    }
}

// match: ?sub_15D600@type_15CCE0@@QAEXM@Z @ 0x0015D600
// sp-match: ?sub_15D600@type_15CCE0@@QAEXM@Z @ 0x00101490
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Its step by arg_0: while not firing, its spread and recoil recover (to
// the settings' bounds); while firing, they grow, and with the settings'
// unk_124 it fires at its owner's point each time the timer runs out.
void type_15CCE0::sub_15D600(RwReal arg_0)
{
    type_3DAFC8 *var_10;
    type_3DAFC8 *var_C;
    type_3D3548 *bp_8;
    type_4D53F8 *bp_4;

    if (unk_04 == -1)
        return;
    bp_4 = sub_15CB10(unk_04);
    if (!unk_00 || !unk_8C || unk_9C)
    {
        unk_A4 = arg_0 + unk_A4;
        if (unk_A4 > bp_4->unk_160)
            unk_A4 = bp_4->unk_160;
        unk_A8 = arg_0 * bp_4->unk_168 + unk_A8;
        if (unk_A8 < unk_C8)
            unk_A8 = unk_C8;
    }
    else
    {
        if (unk_C4)
            unk_A8 = 0;
        else if (unk_A4 <= 0.0f && unk_A8 < 75.0f)
            unk_A8 = arg_0 * bp_4->unk_164_r + unk_A8;
        else
            unk_A4 = unk_A4 - arg_0;
#ifdef CODFH_SP // single player fires through the timer on its own, counts shots and reports "SingleShotFinished" (SP 0x101490)
        if (bp_4->unk_124)
        {
            unk_88 -= arg_0;
            if (unk_88 > 0.0f)
                return;
            if (unk_C4)
            {
                unk_1C = unk_1C + 1;
                unk_84 = 1;
            }
            if (unk_80 > 0)
            {
                sub_15DE60(0);
                unk_80 = unk_80 - 1;
            }
            if (unk_80 == 0)
                sub_15D900(1);
            return;
        }
        unk_88 -= arg_0;
        if (unk_88 <= 0.0f && unk_7C)
        {
            RwReal m_C;

            sub_15DE60(0);
            unk_80 = unk_80 - 1;
            if (unk_80 == 0)
            {
                sub_15D900(1);
                unk_7C = 0;
                return;
            }
            bp_8 = unk_78.sub_D4910();
            m_C = unk_88 * (1.0f / 60.0f);
            if (bp_8->vf_098())
                sub_6B5F0("SingleShotFinished", (type_67620 *)(bp_8->vf_098()), 0, 0, (RwInt32 *)(&m_C), 1, 1, 0);
            unk_88 = 0;
            unk_8C = 0;
            bp_8->vf_1B0(0);
        }
        unk_7C = 0;
#else
        if (bp_4->unk_124)
        {
            unk_88 = unk_88 - arg_0;
            if (unk_88 <= 0.0f && unk_78.sub_D4910() && unk_78.sub_D4910()->vf_008())
            {
                var_C = unk_78.sub_D4910()->vf_008();
                sub_15DE60(&var_C->unk_818_v);
            }
        }
        else
        {
            if (unk_78.sub_D4910() && unk_78.sub_D4910()->vf_008())
            {
                var_10 = unk_78.sub_D4910()->vf_008();
                sub_15DE60(&var_10->unk_818_v);
            }
            unk_88 = 0;
            unk_8C = 0;
            bp_8 = unk_78.sub_D4910();
            bp_8->vf_1B0(0);
        }
        unk_7C = 0;
#endif
    }
}

// match: ?sub_15D8A0@type_15CCE0@@QAEXPAURwV3d@@HHMMM@Z @ 0x0015D8A0
// sp-match: ?sub_15D8A0@type_15CCE0@@QAEXPAURwV3d@@HHMMM@Z @ 0x001016A0
void type_15CCE0::sub_15D8A0(RwV3d *arg_0, RwInt32 arg_4, RwInt32 arg_8, RwReal arg_C, RwReal arg_10,
                             RwReal arg_14)
{
    dword_4D53E0 = arg_4;
    dword_4D53E4 = arg_8;
    dword_4D53E8 = arg_C;
    dword_4D53EC = arg_10;
    dword_4D53F0 = arg_14;
    unk_1C = unk_1C + 1;
    sub_15DE60(arg_0);
}

// match: ?sub_15D900@type_15CCE0@@QAEXH@Z @ 0x0015D900
// sp-match: ?sub_15D900@type_15CCE0@@QAEXH@Z @ 0x00100780
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// A burst ends: with bursts left, the time to the next (its settings'
// ranges, plus a pause and shots by how far the owner's target is, as its
// AI's sub_17100 gives it) and "SingleBurstFinished" (with arg_0, and the
// pause in seconds); else the next round of bursts likewise,
// "AllBurstsFinished" (with arg_0) and the firing stopped.
void type_15CCE0::sub_15D900(RwInt32 arg_0)
{
    RwReal var_24;
    RwInt32 var_20;
    RwInt32 l1C;
    RwReal m_18;
    RwReal ebp_14;
    RwReal lv_10;
    RwInt32 var_C;
    type_3D3548 *bp_8;
    type_4D53F8 *bp_4;

    if (unk_04 == -1)
        return;
    bp_4 = sub_15CB10(unk_04);
    bp_8 = unk_78.sub_D4910();
    unk_84 = unk_84 - 1;
    if (unk_84 > 0)
    {
        if (bp_4->unk_11C <= bp_4->unk_120)
            unk_88 = frand_range(bp_4->unk_11C, bp_4->unk_120);
        else
            unk_88 = frand_range(bp_4->unk_120, bp_4->unk_11C);
        if (bp_4->unk_12C <= bp_4->unk_130)
            unk_80 = RpRandom() % (bp_4->unk_130 - bp_4->unk_12C + 1) + bp_4->unk_12C;
        else
            unk_80 = RpRandom() % (bp_4->unk_12C - bp_4->unk_130 + 1) + bp_4->unk_130;
        if (bp_8->vf_120())
        {
            ebp_14 = bp_8->vf_120()->sub_17100();
            if (ebp_14 < bp_4->unk_16C)
            {
                lv_10 = bp_4->unk_15C;
                var_C = bp_4->unk_144;
            }
            else if (ebp_14 < bp_4->unk_170)
            {
                lv_10 = bp_4->unk_158;
                var_C = bp_4->unk_140;
            }
            else
            {
                lv_10 = bp_4->unk_154;
                var_C = bp_4->unk_13C;
            }
        }
        else
        {
            lv_10 = bp_4->unk_15C;
            var_C = bp_4->unk_144;
        }
        unk_88 = lv_10 + unk_88;
        unk_80 = unk_80 + var_C;
        if (unk_80 <= 0)
            unk_80 = 1;
#ifdef CODFH_SP // shape: the time is block-scoped, so it reuses the dead arg_0 slot (SP 0x100780 has no frame)
        if (arg_0)
        {
            RwReal m_18;

            m_18 = unk_88 / 60.0f;
            if (bp_8->vf_098())
                sub_6B5F0("SingleBurstFinished", (type_67620 *)(bp_8->vf_098()), 0, 0, (RwInt32 *)(&m_18), 1, 1, 0);
        }
#else
        if (arg_0)
        {
            m_18 = unk_88 / 60.0f;
            if (bp_8->vf_098())
                sub_6B5F0("SingleBurstFinished", (type_67620 *)(bp_8->vf_098()), 0, 0, (RwInt32 *)(&m_18), 1, 1, 0);
        }
#endif
        sub_15EB50();
        unk_88 = 0;
    }
    else
    {
        if (bp_4->unk_134 <= bp_4->unk_138)
            unk_84 = RpRandom() % (bp_4->unk_138 - bp_4->unk_134 + 1) + bp_4->unk_134;
        else
            unk_84 = RpRandom() % (bp_4->unk_134 - bp_4->unk_138 + 1) + bp_4->unk_138;
        if (bp_4->unk_12C <= bp_4->unk_130)
            unk_80 = RpRandom() % (bp_4->unk_130 - bp_4->unk_12C + 1) + bp_4->unk_12C;
        else
            unk_80 = RpRandom() % (bp_4->unk_12C - bp_4->unk_130 + 1) + bp_4->unk_130;
        if (unk_C4 || !bp_8->vf_120())
            var_24 = bp_4->unk_16C;
        else
            var_24 = bp_8->vf_120()->sub_17100();
        if (var_24 < bp_4->unk_16C)
        {
            var_20 = bp_4->unk_150;
            l1C = bp_4->unk_144;
        }
        else if (var_24 < bp_4->unk_170)
        {
            var_20 = bp_4->unk_14C;
            l1C = bp_4->unk_140;
        }
        else
        {
            var_20 = bp_4->unk_148;
            l1C = bp_4->unk_13C;
        }
        unk_84 = unk_84 + var_20;
        if (unk_84 <= 0)
            unk_84 = 1;
        unk_80 = unk_80 + l1C;
        if (unk_80 <= 0)
            unk_80 = 1;
        if (arg_0 && bp_8->vf_098())
            sub_6B5F0("AllBurstsFinished", (type_67620 *)(bp_8->vf_098()), 0, 0, 0, 0, 1, 0);
        bp_8->vf_1B0(0);
        unk_8C = 0;
        sub_15EB50();
        unk_88 = 0;
    }
}

// match: ?sub_15DE60@type_15CCE0@@QAEXPAURwV3d@@@Z @ 0x0015DE60
// sp-match: ?sub_15DE60@type_15CCE0@@QAEXPAURwV3d@@@Z @ 0x00100AE0
// Fires at *arg_0 (or where it aims) from its model's "FIRE" point: a
// grenade (kind 8) along the arc its drop settings allow (the speed stored
// in the settings' unk_7C_r, the launch angle raised within the drop's
// range, a random turn), any other shot spread by the owner's vf_164 and
// vf_168 (times the difficulty's multiplier); its particle systems at the
// muzzle, the shot (a grenade's fuse lengthened by the drop's), its sound,
// and the time to the next.
void type_15CCE0::sub_15DE60(RwV3d *arg_0)
{
    RwReal var_190;
    type_15F2C0 *var_18C;
    type_F2FF0 *var_188;
    RwInt32 var_180;
    RwReal var_160;
    RwReal var_140;
    RwReal var_124;
    RwReal var_120;
    RwReal var_11C;
    RwReal var_118;
    RwV3d var_114;
    RwInt32 var_104;
    RwMatrix var_100;
    RwReal var_B4;
    RwReal var_AC;
    RwReal var_A8;
    RwReal var_A4;
    RwV3d var_A0;
    RwV3d var_94;
    RwV3d var_88;
    RwV3d var_7C;
    RwV3d var_70;
    RwInt32 var_64;
    RwMatrix var_60;
    RwInt32 var_20;
    RwMatrix *var_18;
    RwFrame *var_14;
    type_3D3548 *var_C;
    type_4D53F8 *var_8;

    if (unk_04 == -1)
        return;
    var_8 = sub_15CB10(unk_04);
    var_C = unk_78.sub_D4910();
#ifdef CODFH_SP // single player (SP 0x100B14): with no rounds left and no infinite clip it reports "OutOfAmmo", stops the trigger and the owner's firing instead of shooting
    if (unk_1C <= 0 && unk_20 == 0)
    {
        if (var_C->vf_098())
            sub_6B5F0("OutOfAmmo", (type_67620 *)(var_C->vf_098()), 0, 0, 0, 0, true, false);
        sub_15E9B0(0);
        unk_8C = 0;
        var_C->vf_1B0(0);
        sub_15EB50();
        return;
    }
#endif
    var_14 = RpClumpGetFrame(get_unk_18());
    var_18 = RwFrameGetMatrix(var_14);
    var_20 = definition_model((type_3DF8D8 *)unk_0C);
    var_64 = sub_EC2D0((RpClump *)var_20, (RwInt32)&var_60, 0x46495245, 0, 1); // not an address: 'FIRE'
    if (arg_0)
        var_70 = *arg_0;
    else
        sub_15E9E0(&var_70);
    if (var_64)
        sub_1414C0(&var_7C, &var_60.pos, var_18);
    else
        sub_1414C0(&var_7C, &var_8->unk_88_v, var_18);
#ifdef CODFH_SP // single player (SP 0x100C21: fsub before RwV3dNormalize) aims along the muzzle-to-target difference, not the target point
    RwV3dSub(&var_88, &var_70, &var_7C);
#else
    var_88 = var_70;
#endif
    RwV3dNormalize(&var_88, &var_88);
    if (var_8->unk_94.unk_40_r != 0.0f)
    {
        if (sub_15EF80() == 8)
        {
            RwV3dSub(&var_94, &var_70, &var_7C);
            var_A0 = var_94;
            var_A0.y = 0;
            var_A4 = var_94.y;
            if (RwV3dDotProduct(&var_A0, &var_A0) > 0.001f)
            {
                var_A8 = RwV3dLength((RwV3d *)&var_A0);
                var_AC = 1.0f / var_A8;
                var_A0.x = var_A0.x * var_AC;
                var_A0.z = var_A0.z * var_AC;
                if (var_A8 > dword_4D53E8)
                    var_A8 = dword_4D53E8;
                if (var_A8 < 0.0f)
                    var_B4 = (RwReal)atan((RwDouble)(var_A4 / (-var_A8))) * 180.0f / 3.14159f;
                else
                    var_B4 = (RwReal)atan((RwDouble)(var_A4 / var_A8)) * 180.0f / 3.14159f;
            }
            else
            {
                var_A8 = 0;
                var_B4 = 0;
            }
            sub_1213D0(&var_A0, &var_100);
            var_104 = RpRandom() % (dword_4D53E4 - dword_4D53E0 + 1) + dword_4D53E0;
            if (var_104 + var_B4 > 80.0f)
                var_104 = (RwInt32)((90.0f - var_B4) * 0.5f + var_B4);
            RwMatrixRotate(&var_100, &var_100.right, (RwReal)-var_104, rwCOMBINEPOSTCONCAT);
            var_88 = var_100.at;
            var_114.x = 0;
            var_114.y = 1.0f;
            var_114.z = 0;
            var_118 = RwV3dDotProduct(&var_100.at, &var_114);
            var_11C = RwV3dDotProduct(&var_100.at, &var_A0);
            var_120 = 0.5f * var_8->unk_94.unk_40_r * var_A8 * var_A8;
            var_124 = (var_A4 * var_11C - var_A8 * var_118) * var_11C;
            if (var_124 > 0.0001f || var_124 < -0.0001f)
            {
                var_120 = var_120 / var_124;
                if (var_120 < 0.0f)
                    var_120 = -var_120;
                else if (var_120 > 0.0f)
                    var_120 = sqrtf(var_120);
            }
            else
            {
                var_120 = 0;
            }
            var_8->unk_7C_r = var_120;
            var_140 = frand_range(-dword_4D53EC, dword_4D53EC);
            RwMatrixRotate(&var_100, &var_100.up, var_140, rwCOMBINEPOSTCONCAT);
        }
        else
        {
            sub_1213D0(&var_88, &var_100);
        }
    }
    else
    {
        sub_1213D0(&var_88, &var_100);
    }
    if (sub_15EF80() != 8 && !unk_CC)
    {
        var_160 = frand_range(-var_C->vf_164() * (dword_42B714 > -1 && dword_42B714 < 3 ? flt_4F2878[dword_42B714] : 1.0f),
                              var_C->vf_164() * (dword_42B714 > -1 && dword_42B714 < 3 ? flt_4F2878[dword_42B714] : 1.0f));
        RwMatrixRotate(&var_100, &var_100.up, var_160, rwCOMBINEPOSTCONCAT);
        var_160 = frand_range(-var_C->vf_168() * (dword_42B714 > -1 && dword_42B714 < 3 ? flt_4F2878[dword_42B714] : 1.0f),
                              var_C->vf_168() * (dword_42B714 > -1 && dword_42B714 < 3 ? flt_4F2878[dword_42B714] : 1.0f));
        RwMatrixRotate(&var_100, &var_100.right, var_160, rwCOMBINEPOSTCONCAT);
    }
    var_100.pos = var_7C;
    RwV3dScale(&var_88, &var_100.at, var_8->unk_7C_r);
    if (var_64)
    {
        for (var_180 = 0; var_180 < 3; var_180++)
        {
            if (unk_90[var_180])
            {
                var_188 = unk_DC[var_180].get_unk_08();
                if (var_188)
                    sub_F3300(var_188);
                var_188 = (type_F2FF0 *)sub_F2FF0(unk_90[var_180], &var_100, 0, 1, 0, 0);
                sub_15D5B0(var_180, var_188);
            }
        }
    }
    var_18C = (type_15F2C0 *)sub_15F2C0(unk_74, (RwInt32)var_C, &var_100, &var_88, var_C->vf_138(),
                                        (type_439A48 *)&var_8->unk_94, 0);
    if (sub_15EF80() == 8 && dword_4D53F0 >= 0.0f && var_18C)
    {
        var_190 = dword_4D53F0 - var_8->unk_E4;
        var_18C->unk_1C = var_190 + var_18C->unk_1C;
    }
    if (!var_8->unk_70 || !unk_AC)
        unk_AC = var_C->unk_1C0.sub_8A980(&var_8->unk_60, var_C, 2, var_C->sub_CD550(), 0, 0);
    unk_B0 = 3;
    if (!unk_20)
        unk_1C = unk_1C - 1;
    unk_88 = unk_88 + var_8->unk_118;
}

// match: ?sub_15E890@type_15CCE0@@QAEXPAURwV3d@@@Z @ 0x0015E890
// sp-match: ?sub_15E890@type_15CCE0@@QAEXPAURwV3d@@@Z @ 0x000FFE00
void type_15CCE0::sub_15E890(RwV3d *arg_0)
{
    RwFrame *var_C;
    RwMatrix *var_10;
    RwInt32 var_18;
    RwMatrix var_60;
    RwInt32 var_64;
    type_4D53F8 *var_68;

    var_C = RpClumpGetFrame(get_unk_18());
    var_10 = RwFrameGetMatrix(var_C);
    var_18 = definition_model((type_3DF8D8 *)unk_0C);
    var_64 = sub_EC2D0((RpClump *)var_18, (RwInt32)&var_60, 0x46495245, 0, 1); // not an address: 'FIRE'
    if (var_64)
    {
        sub_1414C0(arg_0, &var_60.pos, var_10);
    }
    else
    {
        var_68 = sub_15CB10(unk_04);
        sub_1414C0(arg_0, &var_68->unk_88_v, var_10);
    }
}

// match: ?sub_15E950@type_15CCE0@@QAEXH@Z @ 0x0015E950
// sp-match: ?sub_15E950@type_15CCE0@@QAEXH@Z @ 0x000FFE80
// Resets the time to its next shot: none with arg_0, else its settings'.
void type_15CCE0::sub_15E950(RwInt32 arg_0)
{
    type_4D53F8 *var_4;

    if (unk_04 == -1)
        return;
    if (arg_0)
    {
        unk_88 = 0;
    }
    else
    {
        var_4 = sub_15CB10(unk_04);
        unk_88 = var_4->unk_118;
    }
}

// match: ?sub_15E9B0@type_15CCE0@@QAEXH@Z @ 0x0015E9B0
// sp-match: ?sub_15E9B0@type_15CCE0@@QAEXH@Z @ 0x000FFEC0
// Refills it (its settings' unk_80); arg_0 is unused.
void type_15CCE0::sub_15E9B0(RwInt32 arg_0)
{
    if (unk_04 == -1)
        return;
    unk_1C = dword_4D53F8[unk_04].unk_80;
}

// match: ?sub_15E9E0@type_15CCE0@@QAEXPAURwV3d@@@Z @ 0x0015E9E0
// sp-match: ?sub_15E9E0@type_15CCE0@@QAEXPAURwV3d@@@Z @ 0x000FFEE0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Where it aims: the point it was given, else (firing) at its owner's AI
// target (vf_110), else 1000 ahead of its model; raised by unk_A8.
void type_15CCE0::sub_15E9E0(RwV3d *arg_0)
{
    RwMatrix *var_10;
    bool var_9;
    type_3D3548 *frm_8;
    type_3D3548 *l4;

    frm_8 = 0;
    if (unk_04 == -1)
        return;
    l4 = unk_78.sub_D4910();
    if (l4->vf_120())
        frm_8 = l4->vf_120()->get_unk_1374();
    var_9 = (bool)unk_A0;
    if (unk_CC)
    {
        *arg_0 = unk_D0;
        return;
    }
    if (frm_8 && var_9)
    {
        frm_8->vf_110(arg_0, l4, 0);
        arg_0->y = arg_0->y + unk_A8;
        return;
    }
    var_10 = RwFrameGetMatrix(RpClumpGetFrame(get_unk_18()));
    *arg_0 = var_10->pos;
    RwV3dIncrementScaledMacro(arg_0, &var_10->at, 1000.0f);
    arg_0->y = arg_0->y + unk_A8;
}

// match: ?sub_15EB50@type_15CCE0@@QAEXXZ @ 0x0015EB50
// sp-match: ?sub_15EB50@type_15CCE0@@QAEXXZ @ 0x000FFFF0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Stops its firing sound, and plays its settings' unk_68 sound (with their
// unk_70) in its place.
void type_15CCE0::sub_15EB50()
{
    type_3D3548 *var_8;
    type_4D53F8 *l4;

    if (unk_04 == -1)
        return;
    l4 = sub_15CB10(unk_04);
    var_8 = unk_78.sub_D4910();
    if (unk_AC)
    {
        var_8->unk_1C0.sub_8A910(unk_AC);
        unk_AC = 0;
        if (l4->unk_70)
            var_8->unk_1C0.sub_8A980(&l4->unk_68, var_8, 2, var_8->sub_CD550(), 0, 0);
    }
}

// match: ?sub_15EBF0@type_15CCE0@@QAEMXZ @ 0x0015EBF0
// sp-match: ?sub_15EBF0@type_15CCE0@@QAEMXZ @ 0x00100060
RwReal type_15CCE0::sub_15EBF0()
{
    type_4D53F8 *var_4;

    if (unk_04 == -1)
        return 0.0f;
    var_4 = sub_15CB10(unk_04);
    return var_4->unk_16C;
}

// match: ?sub_15EC30@type_15CCE0@@QAEMXZ @ 0x0015EC30
// sp-match: ?sub_15EC30@type_15CCE0@@QAEMXZ @ 0x00100080
RwReal type_15CCE0::sub_15EC30()
{
    type_4D53F8 *var_4;

    if (unk_04 == -1)
        return 0.0f;
    var_4 = sub_15CB10(unk_04);
    return var_4->unk_170;
}

// match: ?sub_15EC70@type_15CCE0@@QAEHXZ @ 0x0015EC70
// sp-match: ?sub_15EC70@type_15CCE0@@QAEHXZ @ 0x001000A0
RwInt32 type_15CCE0::sub_15EC70()
{
    type_4D53F8 *var_4;

    if (unk_04 == -1)
        return 0;
    var_4 = sub_15CB10(unk_04);
    return var_4->unk_128;
}

// match: ?sub_15ECB0@type_15CCE0@@QAEMXZ @ 0x0015ECB0
// sp-match: ?sub_15ECB0@type_15CCE0@@QAEMXZ @ 0x001011F0
RwReal type_15CCE0::sub_15ECB0()
{
    type_4D53F8 *var_4;

    if (unk_04 == -1)
        return 0.0f;
    var_4 = sub_15CB10(unk_04);
    if (sub_15EF80() != 3 && var_4->unk_174 > 0.0f)
        return dword_4D53F4 + var_4->unk_174;
    return var_4->unk_174;
}

// match: ?sub_15ED20@type_15CCE0@@QAEMXZ @ 0x0015ED20
// sp-match: ?sub_15ED20@type_15CCE0@@QAEMXZ @ 0x001000C0
RwReal type_15CCE0::sub_15ED20()
{
    type_4D53F8 *var_4;

    if (unk_04 == -1)
        return 0.0f;
    var_4 = sub_15CB10(unk_04);
    return var_4->unk_178;
}

// match: ?sub_15ED60@type_15CCE0@@QAEMXZ @ 0x0015ED60
// sp-match: ?sub_15ED60@type_15CCE0@@QAEMXZ @ 0x001000E0
RwReal type_15CCE0::sub_15ED60()
{
    type_4D53F8 *var_4;

    if (unk_04 == -1)
        return 0.0f;
    var_4 = sub_15CB10(unk_04);
    return var_4->unk_17C;
}

// match: ?sub_15EDA0@type_15CCE0@@QAEMXZ @ 0x0015EDA0
// sp-match: ?sub_15EDA0@type_15CCE0@@QAEMXZ @ 0x00100100
RwReal type_15CCE0::sub_15EDA0()
{
    type_4D53F8 *var_4;

    if (unk_04 == -1)
        return 0.0f;
    var_4 = sub_15CB10(unk_04);
    return var_4->unk_180;
}

// match: ?sub_15EDE0@type_15CCE0@@QAEMXZ @ 0x0015EDE0
// sp-match: ?sub_15EDE0@type_15CCE0@@QAEMXZ @ 0x00100120
RwReal type_15CCE0::sub_15EDE0()
{
    type_4D53F8 *var_4;

    if (unk_04 == -1)
        return 0.0f;
    var_4 = sub_15CB10(unk_04);
    return var_4->unk_184;
}

// match: ?sub_15EE20@type_15CCE0@@QAEMXZ @ 0x0015EE20
RwReal type_15CCE0::sub_15EE20()
{
    type_4D53F8 *var_4;

    if (unk_04 == -1)
        return 0.0f;
    var_4 = sub_15CB10(unk_04);
    return var_4->unk_188;
}

// match: ?sub_15EE60@type_15CCE0@@QAEHXZ @ 0x0015EE60
// sp-match: ?sub_15EE60@type_15CCE0@@QAEHXZ @ 0x00101240
// Whether its class (sub_15EF80) is 0.
RwInt32 type_15CCE0::sub_15EE60()
{
    RwInt32 var_4;

    var_4 = sub_15EF80();
    return var_4 == 0;
}

// match: ?sub_15EE90@type_15CCE0@@QAEHXZ @ 0x0015EE90
// sp-match: ?sub_15EE90@type_15CCE0@@QAEHXZ @ 0x00100160
RwInt32 type_15CCE0::sub_15EE90()
{
    RwInt32 var_4;

    var_4 = 0;
    switch (unk_04)
    {
    case 0x0:
    case 0x1:
    case 0x6:
    case 0x7:
    case 0x8:
    case 0x9:
    case 0xB:
    case 0xC:
    case 0xF:
    case 0x10:
    case 0x14:
    case 0x15:
    case 0x19:
    case 0x1C:
    case 0x1F:
    case 0x20:
    case 0x21:
    case 0x22:
    case 0x23:
    case 0x24:
    case 0x31:
    case 0x32:
    case 0x33:
    case 0x34:
    case 0x35:
    case 0x36:
    case 0x37:
    case 0x38:
    case 0x39:
    case 0x3A:
    case 0x3B:
    case 0x3C:
    case 0x40:
    case 0x41:
    case 0x42:
    case 0x43:
    case 0x44:
    case 0x45:
    case 0x4C:
    case 0x4D:
    case 0x4E:
    case 0x4F:
    case 0x50:
    case 0x51:
    case 0x5B:
    case 0x5C:
    case 0x5D:
    case 0x5E:
    case 0x5F:
    case 0x60:
    case 0x6A:
    case 0x6B:
    case 0x6C:
    case 0x73:
    case 0x74:
    case 0x75:
    case 0x7C:
    case 0x7D:
    case 0x7E:
    case 0x7F:
        var_4 = 1;
        break;
    case 0x2:
    case 0x1A:
    case 0x25:
    case 0x26:
    case 0x27:
    case 0x6D:
    case 0x6E:
    case 0x6F:
        var_4 = 3;
        break;
    case 0x3:
    case 0xE:
    case 0x28:
    case 0x29:
    case 0x2A:
    case 0x49:
    case 0x4A:
    case 0x4B:
        var_4 = 2;
        break;
    case 0x4:
    case 0xA:
    case 0xD:
    case 0x11:
    case 0x16:
    case 0x17:
    case 0x18:
    case 0x1E:
    case 0x2B:
    case 0x2C:
    case 0x2D:
    case 0x3D:
    case 0x3E:
    case 0x3F:
    case 0x46:
    case 0x47:
    case 0x48:
    case 0x52:
    case 0x53:
    case 0x54:
    case 0x61:
    case 0x62:
    case 0x63:
    case 0x64:
    case 0x65:
    case 0x66:
    case 0x67:
    case 0x68:
    case 0x69:
    case 0x79:
    case 0x7A:
    case 0x7B:
        var_4 = 0;
        break;
    }
    return var_4;
}

// match: ?sub_15EF80@type_15CCE0@@QAEHXZ @ 0x0015EF80
// sp-match: ?sub_15EF80@type_15CCE0@@QAEHXZ @ 0x00100AD0
RwInt32 type_15CCE0::sub_15EF80()
{
    return sub_15EFA0(unk_04);
}

// match: ?sub_15EFA0@@YAHH@Z @ 0x0015EFA0
// sp-match: ?sub_15EFA0@@YAHH@Z @ 0x00100230
// The class of the weapon type arg_0: 0 to 4, 8 for grenades, -1 outside
// 0 to 0x7F.
RwInt32 sub_15EFA0(RwInt32 arg_0)
{
    RwInt32 var_4;

    var_4 = -1;
    switch (arg_0)
    {
    case 0x0:
    case 0x1:
    case 0x6:
    case 0x7:
    case 0x8:
    case 0x9:
    case 0xB:
    case 0xC:
    case 0xF:
    case 0x10:
    case 0x14:
    case 0x15:
    case 0x19:
    case 0x1C:
    case 0x1F:
    case 0x20:
    case 0x21:
    case 0x22:
    case 0x23:
    case 0x24:
    case 0x31:
    case 0x32:
    case 0x33:
    case 0x34:
    case 0x35:
    case 0x36:
    case 0x37:
    case 0x38:
    case 0x39:
    case 0x3A:
    case 0x3B:
    case 0x3C:
    case 0x40:
    case 0x41:
    case 0x42:
    case 0x43:
    case 0x44:
    case 0x45:
    case 0x4C:
    case 0x4D:
    case 0x4E:
    case 0x4F:
    case 0x50:
    case 0x51:
    case 0x5B:
    case 0x5C:
    case 0x5D:
    case 0x5E:
    case 0x5F:
    case 0x60:
    case 0x6A:
    case 0x6B:
    case 0x6C:
    case 0x73:
    case 0x74:
    case 0x75:
    case 0x7C:
    case 0x7D:
    case 0x7E:
    case 0x7F:
        var_4 = 0;
        break;
    case 0x2:
    case 0x1A:
    case 0x25:
    case 0x26:
    case 0x27:
    case 0x6D:
    case 0x6E:
    case 0x6F:
        var_4 = 3;
        break;
    case 0x3:
    case 0xE:
    case 0x28:
    case 0x29:
    case 0x2A:
    case 0x49:
    case 0x4A:
    case 0x4B:
        var_4 = 1;
        break;
    case 0x4:
    case 0xA:
    case 0x11:
    case 0x16:
    case 0x1E:
    case 0x2B:
    case 0x2C:
    case 0x2D:
    case 0x3D:
    case 0x3E:
    case 0x3F:
    case 0x46:
    case 0x47:
    case 0x48:
    case 0x52:
    case 0x53:
    case 0x54:
    case 0x61:
    case 0x62:
    case 0x63:
    case 0x64:
    case 0x65:
    case 0x66:
    case 0x67:
    case 0x68:
    case 0x69:
    case 0x79:
    case 0x7A:
    case 0x7B:
        var_4 = 2;
        break;
    case 0xD:
    case 0x17:
    case 0x18:
        var_4 = 4;
        break;
    case 0x5:
    case 0x12:
    case 0x13:
    case 0x1B:
    case 0x1D:
    case 0x2E:
    case 0x2F:
    case 0x30:
    case 0x55:
    case 0x56:
    case 0x57:
    case 0x58:
    case 0x59:
    case 0x5A:
    case 0x70:
    case 0x71:
    case 0x72:
    case 0x76:
    case 0x77:
    case 0x78:
        var_4 = 8;
        break;
    }
    return var_4;
}

// match: ?sub_15F0A0@type_15CCE0@@QAEHXZ @ 0x0015F0A0
// sp-match: ?sub_15F0A0@type_15CCE0@@QAEHXZ @ 0x00100310
RwInt32 type_15CCE0::sub_15F0A0()
{
    RwInt32 var_4;

    var_4 = 0;
    switch (unk_04)
    {
    case -1:
        var_4 = 1;
        break;
    case 0x0:
    case 0x1:
    case 0x6:
    case 0x7:
    case 0x8:
    case 0xF:
    case 0x15:
    case 0x19:
    case 0x1C:
    case 0x1F:
    case 0x20:
    case 0x21:
    case 0x22:
    case 0x23:
    case 0x24:
    case 0x31:
    case 0x32:
    case 0x33:
    case 0x34:
    case 0x35:
    case 0x36:
    case 0x37:
    case 0x38:
    case 0x39:
    case 0x4C:
    case 0x4D:
    case 0x4E:
    case 0x5E:
    case 0x5F:
    case 0x60:
    case 0x6A:
    case 0x6B:
    case 0x6C:
    case 0x73:
    case 0x74:
    case 0x75:
    case 0x7C:
    case 0x7D:
    case 0x7E:
    case 0x7F:
        var_4 = 1;
        break;
    case 0x9:
    case 0xB:
    case 0xC:
    case 0x10:
    case 0x14:
    case 0x3A:
    case 0x3B:
    case 0x3C:
    case 0x40:
    case 0x41:
    case 0x42:
    case 0x43:
    case 0x44:
    case 0x45:
    case 0x4F:
    case 0x50:
    case 0x51:
    case 0x5B:
    case 0x5C:
    case 0x5D:
#ifdef CODFH_SP // single player gives this group its own class 5 (SP 0x100332)
        var_4 = 5;
#else
        var_4 = 1;
#endif
        break;
    case 0x2:
    case 0x5:
    case 0x12:
    case 0x13:
    case 0x1A:
    case 0x1B:
    case 0x1D:
    case 0x25:
    case 0x26:
    case 0x27:
    case 0x2E:
    case 0x2F:
    case 0x30:
    case 0x55:
    case 0x56:
    case 0x57:
    case 0x58:
    case 0x59:
    case 0x5A:
    case 0x6D:
    case 0x6E:
    case 0x6F:
    case 0x70:
    case 0x71:
    case 0x72:
    case 0x76:
    case 0x77:
    case 0x78:
        var_4 = 4;
        break;
    case 0x3:
    case 0xE:
    case 0x28:
    case 0x29:
    case 0x2A:
    case 0x49:
    case 0x4A:
    case 0x4B:
        var_4 = 3;
        break;
    case 0x4:
    case 0xA:
    case 0xD:
    case 0x11:
    case 0x16:
    case 0x17:
    case 0x18:
    case 0x1E:
    case 0x2B:
    case 0x2C:
    case 0x2D:
    case 0x3D:
    case 0x3E:
    case 0x3F:
    case 0x46:
    case 0x47:
    case 0x48:
    case 0x52:
    case 0x53:
    case 0x54:
    case 0x61:
    case 0x62:
    case 0x63:
    case 0x64:
    case 0x65:
    case 0x66:
    case 0x67:
    case 0x68:
    case 0x69:
    case 0x79:
    case 0x7A:
    case 0x7B:
        var_4 = 2;
        break;
    }
    return var_4;
}
