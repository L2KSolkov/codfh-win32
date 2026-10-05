// Split from unit_1B7B20.cpp at 0x1BAA90, where the image ends that object (its deferred
// functions come before the next out-of-line one; PLAN M7).

#include "rw/ostypes.h"
#include "rw/bamatrix.h"
#include "rw/baframe.h"
#include "rw/bavector.h"
#include "game/functions.h"
#include "types/type_3D32F8.h"
#include "game/netmsg.h"
#include "game/netplayer.h"
#include "types/type_FC6F0.h"
#include "types/type_3DAFC8.h"
#include "types/type_4D1DB8.h"
#include "game/debugtext.h"
#include "game/worldmgr.h"
#include "types/type_4E5D30.h"
#include "rw/rpcollis.h"
#include "game/clumputil.h"
#include "rw/rphanim.h"
#include "game/data.h"
#include "game/gameloop.h"
#include "game/flags.h"
#include "game/bombsites.h"
#include "types/type_DC400.h"
#include "types/type_3DD948.h"
#include "types/soundbank.h"
#include "types/type_3D94B8.h"
#include "types/PickupTrigger.h"
#include "game/loc.h"
#include "game/mpgame.h"
#include "game/netscore.h"
#include <string.h>
#include <math.h>
#include "types/type_4C09B0.h"
#include "types/type_4C19C0.h"
#include "types/type_3DF8D8.h"
#include "game/textmanager.h"
#include "types/alfaobject.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003E2914
extern const RwReal flt_3E2914 = 16.666666f;
// 0x003E2918
extern const RwV3d stru_3E2918 = { 0.0f, 1.0f, 0.0f };
// 0x003E2924
extern const RwReal flt_3E2924 = 0.01f;
// 0x003E2928
extern const RwReal flt_3E2928 = 0.01f;

// match: ?flt_3E2914@@3MB @ 0x003E2914
// match: ?stru_3E2918@@3URwV3d@@B @ 0x003E2918
// match: ?flt_3E2924@@3MB @ 0x003E2924
// match: ?flt_3E2928@@3MB @ 0x003E2928


// match: __ehhandler$?sub_1BAA90@@YAPAUtype_1BABA0@@PAUtype_712B0@@@Z>1>8 @ 0x0041F03C
// match: __ehhandler$?sub_1BAA90@@YAPAUtype_1BABA0@@PAUtype_712B0@@@Z>1 @ 0x0041F044
// match: ??_Gtype_1BABA0@@UAEPAXI@Z @ 0x001BADA0
// match: ??1type_1BABA0@@UAE@XZ @ 0x001BADD0
// match: ?vf_05C@type_1BABA0@@WCCGA@AEXXZ @ 0x001BD330
// match: ??_7type_1BABA0@@6Btype_4F6B00_120@@@ @ 0x003E292C
// match: ??_7type_1BABA0@@6Btype_10F710@@@ @ 0x003E2960
// match: ??_7type_4F6B00_120@@6B@ @ 0x003E2BBC

// match: ?sub_1BAA90@@YAPAUtype_1BABA0@@PAUtype_712B0@@@Z @ 0x001BAA90
// match: __ehhandler$?sub_1BAA90@@YAPAUtype_1BABA0@@PAUtype_712B0@@@Z-0x11 @ 0x00302DD0
// match: __ehhandler$?sub_1BAA90@@YAPAUtype_1BABA0@@PAUtype_712B0@@@Z @ 0x00302DE1
type_1BABA0 *sub_1BAA90(type_712B0 *arg_0)
{
    type_1BABA0 *var_10;

    var_10 = (type_1BABA0 *)sub_D56D0(0x22F0, arg_0->unk_24_18, arg_0->vf_008());
    if (var_10 != 0) {
        var_10 = new (var_10) type_1BABA0(arg_0);
        if (var_10->unk_28 & 0x400000) { // not an address: entity flag
            sub_D5A60(var_10, 0);
            var_10 = 0;
        }
    } else
        sub_19A750("WARNING: A spawn could not be created due to lack of entity memory. Trigger "
                   "location(%6.2f,%6.2f,%6.2f)",
                   arg_0->unk_90, arg_0->unk_94, arg_0->unk_98);
    return var_10;
}
// match: ??0type_1BABA0@@QAE@PAUtype_712B0@@@Z @ 0x001BABA0
type_1BABA0::type_1BABA0(type_712B0 *arg_0) : type_10F710(arg_0)
{
    RwMatrixSetIdentityMacro(&unk_22B0);
    unk_530 = 0;
    unk_1A04 = 0;
    unk_2294 = 0;
    unk_2284 = 0;
    unk_1B1C = 0;
    unk_2288 = 0;
    unk_228C = 0;
    unk_2290 = 0;
    unk_2298 = 0;
    unk_229C = 0;
    unk_22A0 = 0;
    unk_22A4 = 0;
    unk_217C = 1;
}
// The player's frame step, then its frame kept at its view.
// match: ?vf_038@type_1BABA0@@UAEXM@Z @ 0x001BADF0
void type_1BABA0::vf_038(RwReal arg_0)
{
    RwMatrix *var_4;

    type_10F710::vf_038(arg_0);
    var_4 = RwFrameGetMatrix(get_unk_340());
    *var_4 = unk_22B0;
}
// The step. The recoil's time runs down. With its trigger: unless it is
// still (trigger unk_140), the listener is put behind its eye (3 units back
// along its view) facing along it, its sounds follow it, at no health it
// dies (posture 9 from 5, else 10, the camera let go), the aim pass runs
// along the camera's view over the section worlds (the aim ray's length
// flt_4B8F2C set), and dying it falls (sub_10B790). Then the weapons'
// times, the inventory's count, the HUD's name and health colour of the
// soldier under the crosshair, its performance and animation; the weapon
// state its network part took (fire, reload, throw, cook), the stance
// change (blended at unk_1A18), the sway (vf_258), and aiming in or out.
// match: ?vf_03C@type_1BABA0@@UAEXM@Z @ 0x001BAE40
void type_1BABA0::vf_03C(RwReal arg_0)
{
    // The locals' names state their slots (docs/toolchain.md).
    RwInt32 t88;
    RwInt32 ebp_84;
    RwInt32 r80;
    type_6D380 *p7C;
    RwRGBAReal fp_78;
    RwReal q68;
    type_4E5D30 *var_64;
    RwInt32 stk_60;
    RwMatrix *y5C;
    type_1BAE40_58 slot_58;
    RwV3d stk_2C;
    type_3DD948 *t20;
    RwV3d *l1C;
    RwV3d m_18;
    type_712B0_10F710 *slot_C;
    type_10F710_1A48 *bp_8;
    type_3DAFC8 *bp_4;

    if (unk_19EC > 0.0f)
        unk_19EC -= arg_0;
    slot_C = (type_712B0_10F710 *)unk_344.unk_08;
    if (slot_C && slot_C->vf_008() != 1)
    {
        slot_C = 0;
    }
    if (!slot_C)
        return;
    if (!slot_C->unk_140)
    {
        l1C = &RwFrameGetLTM(get_unk_340())->at;
        m_18 = *sub_CD550();
        m_18.x -= l1C->x * 3.0f;
        m_18.y -= l1C->y * 3.0f;
        m_18.z -= l1C->z * 3.0f;
        do
        {
            dword_44E8AC->unk_28 = m_18;
            dword_44E8AC->unk_70 |= 1;
        } while (0);
        do
        {
            dword_44E8AC->unk_4C = *l1C;
            RwV3dCrossProductMacro(&dword_44E8AC->unk_58, &dword_44E8AC->unk_40, &dword_44E8AC->unk_4C);
            dword_44E8AC->unk_70 |= 4;
        } while (0);
        unk_1C0.sub_89540(sub_CD550());
        if (!unk_19F8 && unk_19DC <= 0.0f)
        {
            if (unk_19D0 == 5)
                unk_19D0 = 9;
            else
            {
                unk_19D0 = 0xA;
                t20 = (type_3DD948 *)unk_2110.sub_D4910();
                if (t20)
                    t20->unk_3B0 = 0;
            }
        }
        if (flt_4B8F2C != 0.0f)
        {
            y5C = RwFrameGetMatrix(RwCameraGetFrame((RwCamera *)dword_4E5C74));
            slot_58.unk_00 = flt_4B8F2C;
            intersection.type = rpINTERSECTLINE;
            slot_58.unk_04 = intersection.t.line.start = y5C->pos;
            intersection.t.line.end.x = slot_58.unk_10.x = y5C->at.x * 2000.0f + intersection.t.line.start.x;
            intersection.t.line.end.y = slot_58.unk_10.y = y5C->at.y * 2000.0f + intersection.t.line.start.y;
            intersection.t.line.end.z = slot_58.unk_10.z = y5C->at.z * 2000.0f + intersection.t.line.start.z;
            slot_58.unk_1C = -1.0f;
            slot_58.unk_20 = 0;
            slot_58.unk_24 = slot_C->unk_1B4;
            slot_58.unk_28 = 0;
            if (sub_FCAE0(&intersection.t.line.start, &intersection.t.line.end, &stk_2C, 0, 0x410000, 1, 1)) // not an address: flags
                intersection.t.line.end = stk_2C;
            if (intersection.t.line.start.x != intersection.t.line.end.x ||
                intersection.t.line.start.y != intersection.t.line.end.y ||
                intersection.t.line.start.z != intersection.t.line.end.z)
            {
                for (stk_60 = 0; stk_60 < 4; stk_60++)
                {
                    var_64 = &dword_4E5D30[stk_60];
                    if (var_64->get_unk_00() != 0 && var_64->get_unk_28() != 0)
                        RpWorldForAllAtomicIntersections(var_64->get_unk_28(), &intersection, sub_FCD90, &slot_58);
                }
            }
        }
        if (unk_19D0 == 0xA)
            sub_10B790(arg_0);
    }
    unk_1A48[unk_1AE4]->unk_220 += arg_0;
    bp_8 = unk_1A48[unk_1AE4]->unk_460;
    if (bp_8)
        bp_8->unk_220 += arg_0;
    sub_1048E0();
    unk_21B4.sub_115520(arg_0);
    bp_4 = sub_108CC0(800.0f);
    if (bp_4)
    {
        dword_4B9190->sub_E7380(0x6A, bp_4->unk_62C);
        q68 = bp_4->vf_17C();
        if (q68 > 0.5f)
        {
            q68 = (q68 - 0.5f) / 0.5f;
            fp_78.red = 1.0f - q68;
            fp_78.green = 1.0f;
            fp_78.blue = q68 * 0.25f;
            fp_78.alpha = 1.0f;
        }
        else
        {
            q68 = q68 / 0.5f;
            fp_78.red = 1.0f;
            fp_78.green = q68;
            fp_78.blue = 0.0f;
            fp_78.alpha = 1.0f;
        }
        dword_4B9190->sub_E7480(0x6A, &fp_78);
    }
    else
        dword_4B9190->sub_E7380(0x6A, "");
    if (unk_284 && unk_88_9)
    {
        p7C = vf_090();
        if (p7C)
            ((type_3D2CD0 *)p7C)->sub_6D5A0(arg_0);
        vf_21C(arg_0);
    }
    unk_1B20 = 0;
    if (!unk_1B1C)
    {
        unk_1B24 = 0;
        unk_20DC = 0;
    }
    if (unk_19D0 == 0xA || unk_19D0 == 9)
        unk_1A48[unk_1AE4]->vf_02C();
    else if (unk_1B3C)
    {
        if (unk_1B1C && !unk_2288)
        {
            unk_1A48[unk_1AE4]->unk_414 = unk_1A48[unk_1AE4]->get_unk_448()->unk_C8;
            switch (unk_1A48[unk_1AE4]->unk_48)
            {
            case 1:
            case 2:
                if (!unk_229C)
                {
                    unk_1A48[unk_1AE4]->vf_018();
                    unk_1B20 = 1;
                    unk_1B24 = dword_42CAE8;
                    if (arg_0 < 2.0f)
                        unk_1B24++;
                }
                break;
            default:
                unk_1A48[unk_1AE4]->vf_018();
                unk_1B20 = 1;
                unk_1B24 = dword_42CAE8;
                if (arg_0 < 2.0f)
                    unk_1B24++;
            }
            unk_229C = 1;
        }
        else if (unk_1B1C && unk_2288 && !unk_2298 && !unk_1A48[unk_1AE4]->unk_11)
        {
            unk_1A48[unk_1AE4]->sub_1190B0();
            unk_1A48[unk_1AE4]->unk_45 = 1;
            unk_2298 = 1;
        }
        else if (unk_228C && !unk_1A48[unk_1AE4]->unk_12 && !unk_22A0)
        {
            unk_1A48[unk_1AE4]->unk_418 = unk_1A48[unk_1AE4]->get_unk_448()->unk_C8;
            unk_1A48[unk_1AE4]->vf_020();
        }
        else if (unk_2290 && !unk_22A4)
        {
            sub_108BC0(unk_21B4.get_unk_34(), 1.0f);
        }
    }
    if (unk_2294 != unk_1A04)
    {
        if ((RwUInt32)(unk_1A04 + 1) % 3 == unk_2294)
            unk_1A48[unk_1AE4]->sub_119830(unk_2294, 1);
        else
            unk_1A48[unk_1AE4]->sub_119830(unk_2294, 0);
        unk_1A04 = unk_2294;
        unk_1A0C = 1;
        unk_1A10 = 0;
    }
    if (unk_1A0C)
    {
        unk_1A10 += arg_0 * 0.5f * unk_1A18;
        if (unk_1A10 >= 1.0f)
        {
            unk_1A0C = 0;
            unk_1A08 = unk_1A04;
        }
    }
    vf_258(arg_0);
    if (unk_2284)
    {
        if (unk_1B04)
        {
            if (unk_1B10)
            {
                unk_1A48[unk_1AE4]->sub_11D740(0);
                unk_1B04 = 0;
                unk_1B08 = 1;
                unk_1A48[unk_1AE4]->unk_298 -= 1.0f;
            }
        }
        else if (!unk_1A48[unk_1AE4]->unk_12)
        {
            unk_1A48[unk_1AE4]->sub_11D740(0);
            unk_1B04 = 1;
            unk_1B08 = 0;
        }
        sub_104FF0(arg_0);
    }
    else if (unk_1B04)
    {
        unk_1A48[unk_1AE4]->sub_11D740(1);
        sub_1062A0();
        sub_104FF0(arg_0);
        if (!unk_1A48[unk_1AE4]->unk_22C)
        {
            t88 = unk_1A48[unk_1AE4]->get_unk_448()->unk_28;
            if (sub_77B70(t88, (void **)(&ebp_84), (void **)(&r80)) && !unk_1A48[unk_1AE4]->unk_12)
            {
                unk_284->sub_794C0(0.0f);
                unk_284->sub_796A0((RtAnimAnimation *)ebp_84, t88, 0, (struct type_783F0 *)r80, 0.0f, 1.0f, 1.0f);
            }
            else if (!unk_1A48[unk_1AE4]->unk_12)
                sub_16C220("WARNING: Missing idle anim %d.", unk_1A48[unk_1AE4]->get_unk_448()->unk_28);
        }
    }
    else if (unk_1B08 || unk_1B04 && unk_1A0C)
        sub_104FF0(arg_0);
    sub_10C7B0(arg_0);
}
// The late step: while it has its trigger, the entity's own (sub_CDF40), no
// step raising or explosion hits, its frame's matrix kept orthonormal every
// 64 frames, the stance's eye height (blended during a stance change), and
// its model and the weapon's placed at its root bone raised by 50 (z).
// match: ?vf_04C@type_1BABA0@@UAEXM@Z @ 0x001BBD90
void type_1BABA0::vf_04C(RwReal arg_0)
{
    type_712B0_10F710 *var_8;
    RwFrame *var_C;
    RwMatrix *var_10;
    RwReal var_14;
    RpHAnimHierarchy *var_18;
    RwMatrix *var_1C;
    RwMatrix var_60;
    RwV3d var_6C;

    var_8 = (type_712B0_10F710 *)unk_344.unk_08;
    if (var_8 && var_8->vf_008() != 1)
    {
        var_8 = 0;
    }
    if (!var_8)
        return;
    sub_CDF40(arg_0);
    unk_28_4 = 0;
    unk_28_5 = 0;
    unk_28_2 = 0;
    var_C = unk_338.unk_08;
    var_10 = RwFrameGetMatrix(var_C);
    if ((dword_4B87D8 & 0x3F) == 0x3F)
        RwMatrixOrthoNormalize(var_10, var_10);
    unk_3E0 += arg_0;
    unk_48 = var_8->unk_144_a[unk_1A04];
    if (unk_1A0C)
        unk_48 = sub_112F80(var_8->unk_144_a[unk_1A08], var_8->unk_144_a[unk_1A04], unk_1A10);
    var_14 = 100.0f;
    var_18 = unk_284->unk_18;
    var_1C = RpHAnimHierarchyGetMatrixArray(var_18);
    RwMatrixInvert(&var_60, RwFrameGetLTM(RpClumpGetFrame(unk_1A3C.get_unk_08())));
    sub_1414C0(&var_6C, &var_1C->pos, &var_60);
    var_6C.z += 50.0f;
    sub_16DFA0(unk_1A3C.get_unk_08(), &var_6C, var_14);
    sub_16DFA0(unk_1A48[unk_1AE4]->get_unk_428(), &var_6C, var_14);
    vf_1D0();
}
// The weapon's sway as the player's (sub_10DBD0, its vf_258), driven by its
// velocity against its trigger's speeds instead of the pad; a looping
// sound left over from a weapon change is stopped and its end played once
// the weapon has cooled past 2.
// match: ?vf_258@type_1BABA0@@UAEXM@Z @ 0x001BBFB0
void type_1BABA0::vf_258(RwReal arg_0)
{
    // The locals' names state their slots (docs/toolchain.md).
    RwReal stk_60;
    type_4C19C0 *y5C;
    RwV3d slot_58;
    RwV3d *x4C;
    RwV3d *w48;
    RwV3d *loc44;
    RwV3d *fp_40;
    RwV3d *ebp_3C;
    RwV3d *local_38;
    RwV3d local_34;
    RwV3d slot_28;
    RwV3d l1C;
    RwReal lv_10;
    type_712B0_10F710 *slot_C;
    RwFrame *bp_8;
    type_4C19C0 *bp_4;

    bp_8 = RpClumpGetFrame(unk_1A3C.get_unk_08());
    bp_4 = unk_1A48[unk_1AE4]->unk_448;
    if (bp_8)
    {
        slot_C = (type_712B0_10F710 *)unk_344.unk_08;
        if (slot_C && slot_C->vf_008() != 1)
        {
            slot_C = 0;
        }
        if (unk_1A48[unk_1AE4]->unk_46 && !bp_4->unk_1C)
        {
            unk_1A48[unk_1AE4]->unk_46 = 0;
        }
        if (bp_4->unk_1C && unk_1A48[unk_1AE4]->unk_46 && unk_1A48[unk_1AE4]->unk_220 - bp_4->unk_BC > 2.0f)
        {
            unk_1C0.sub_8A910(unk_1A48[unk_1AE4]->unk_21C);
            unk_1A48[unk_1AE4]->unk_21C = 0;
            unk_1C0.sub_8A980(&bp_4->unk_14, this, 1, sub_CD550(), 0, 0);
            unk_1A48[unk_1AE4]->unk_46 = 0;
        }
        slot_28 = bp_4->unk_19C_a[unk_1A04];
        l1C = bp_4->unk_1E4_a[unk_1A04];
        local_34 = bp_4->unk_208_a[unk_1A04];
        if (unk_1B04)
        {
            slot_28 = bp_4->unk_19C_a[unk_1A04];
            l1C = bp_4->unk_238_a[unk_1A04];
            local_34 = bp_4->unk_25C_a[unk_1A04];
        }
        if (unk_1A0C)
        {
            x4C = &bp_4->unk_19C_a[unk_1A04];
            w48 = &bp_4->unk_19C_a[unk_1A08];
            if (unk_1B04)
            {
                local_38 = &bp_4->unk_238_a[unk_1A04];
                fp_40 = &bp_4->unk_238_a[unk_1A08];
                ebp_3C = &bp_4->unk_25C_a[unk_1A04];
                loc44 = &bp_4->unk_25C_a[unk_1A08];
            }
            else
            {
                local_38 = &bp_4->unk_1E4_a[unk_1A04];
                fp_40 = &bp_4->unk_1E4_a[unk_1A08];
                ebp_3C = &bp_4->unk_208_a[unk_1A04];
                loc44 = &bp_4->unk_208_a[unk_1A08];
            }
            sub_112FC0(&slot_28, w48, x4C, unk_1A10);
            sub_112FC0(&l1C, fp_40, local_38, unk_1A10);
            sub_112FC0(&local_34, loc44, ebp_3C, unk_1A10);
        }
        unk_1AF8.z = 0.0f;
        unk_1AF8.y = 0.0f;
        unk_1AF8.x = 0.0f;
        if (!bp_4->unk_20)
        {
            if (unk_1A04 != 2 || !unk_1B1C)
            {
                RwV3dAdd(&unk_1AF8, &unk_1AF8, &slot_28);
            }
            else
            {
                unk_1AF8 = slot_28;
            }
            if (unk_1B04 || unk_1B08)
            {
                if (unk_1B0C && !unk_1A0C)
                {
                    RwV3dAdd(&unk_1AF8, &unk_1AF8, &unk_1A48[unk_1AE4]->unk_28C);
                }
                else
                {
                    y5C = unk_1A48[unk_1AE4]->unk_448;
                    sub_112FC0(&slot_58, &y5C->unk_3C8_a[unk_1A08], &y5C->unk_3C8_a[unk_1A04], unk_1A10);
                    RwV3dAdd(&unk_1AF8, &unk_1AF8, &slot_58);
                }
            }
        }
        unk_1AF8.x += sin(local_34.x * unk_1AF4) * l1C.x;
        unk_1AF8.y += sin(local_34.y * unk_1AF4) * l1C.y;
        unk_1AF8.z += sin(local_34.z * unk_1AF4) * l1C.z;
        if (unk_1A48[unk_1AE4]->unk_18 > bp_4->unk_2B4_r[unk_1A04])
        {
            if (unk_1B04)
            {
                unk_1A48[unk_1AE4]->unk_18 = bp_4->unk_34C_r[unk_1A04];
            }
            else
            {
                unk_1A48[unk_1AE4]->unk_18 = bp_4->unk_2B4_r[unk_1A04];
            }
        }
        lv_10 = 0.0f;
        if (unk_19D0 != 6 && unk_19D0 != 12)
        {
            lv_10 = (unk_2270.unk_08 / slot_C->unk_164[unk_1A04] < 0.0f ? -unk_2270.unk_08 / slot_C->unk_164[unk_1A04]
                                                                       : unk_2270.unk_08 / slot_C->unk_164[unk_1A04]) < 1.0f
                         ? (unk_2270.unk_08 / slot_C->unk_164[unk_1A04] < 0.0f
                                ? -unk_2270.unk_08 / slot_C->unk_164[unk_1A04]
                                : unk_2270.unk_08 / slot_C->unk_164[unk_1A04])
                         : 1.0f;
            if (unk_2148 != 0.0f)
            {
                lv_10 = unk_2150;
            }
            stk_60 = (unk_2270.unk_00 / slot_C->unk_1E4[unk_1A04] < 0.0f ? -unk_2270.unk_00 / slot_C->unk_1E4[unk_1A04]
                                                                       : unk_2270.unk_00 / slot_C->unk_1E4[unk_1A04]) < 1.0f
                         ? (unk_2270.unk_00 / slot_C->unk_1E4[unk_1A04] < 0.0f
                                ? -unk_2270.unk_00 / slot_C->unk_1E4[unk_1A04]
                                : unk_2270.unk_00 / slot_C->unk_1E4[unk_1A04])
                         : 1.0f;
            if (stk_60 > lv_10)
            {
                lv_10 = stk_60;
            }
            if (unk_1A04 != 2 || !unk_1B1C)
            {
                unk_1AF4 += lv_10 * bp_4->unk_22C_r[unk_1A04] * arg_0;
            }
            if (unk_1B04)
            {
                unk_1AF4 += arg_0 * bp_4->unk_280_r[unk_1A04];
            }
        }
        RwFrameSetIdentity(bp_8);
        RwFrameUpdateObjects(bp_8);
    }
}
// match: ?vf_244@type_1BABA0@@UAEHXZ @ 0x001BCA20
RwInt32 type_1BABA0::vf_244()
{
    return type_10F710::vf_244();
}
// The view's bob as the player's (vf_240), driven by its velocity instead
// of the pad (forwards unk_2278 and sideways unk_2270 against its trigger's
// speeds, each at most 1), with a sideways sway (unk_4F0) of its own.
// match: ?vf_240@type_1BABA0@@UAEXPAURwV3d@@M@Z @ 0x001BCA40
void type_1BABA0::vf_240(RwV3d *arg_0, RwReal arg_4)
{
    // The locals' names state their slots (docs/toolchain.md).
    RwReal l1C;
    RwReal m_18;
    RwReal ebp_14;
    RwReal lv_10;
    type_712B0_10F710 *slot_C;
    RwReal bp_8;
    RwReal bp_4;

    sub_112DA0(&unk_404, 0.0f, &unk_408, flt_42CAEC, flt_42CAF0, flt_42CAF4, arg_4);
    arg_0->y = arg_0->y - unk_404;
    ebp_14 = 0.0f;
    m_18 = 0.0f;
    l1C = 0.0f;
    slot_C = (type_712B0_10F710 *)unk_344.unk_08;
    if (slot_C && slot_C->vf_008() != 1)
    {
        slot_C = 0;
    }
    l1C = (unk_2270.unk_08 / slot_C->unk_164[unk_1A04] < 1.0f ? unk_2270.unk_08 / slot_C->unk_164[unk_1A04] : 1.0f) >
                  -1.0f
              ? (unk_2270.unk_08 / slot_C->unk_164[unk_1A04] < 1.0f ? unk_2270.unk_08 / slot_C->unk_164[unk_1A04]
                                                                  : 1.0f)
              : -1.0f;
    ebp_14 = l1C < 0.0f ? -l1C : l1C;
    m_18 = (unk_2270.unk_00 / slot_C->unk_1E4[unk_1A04] < 0.0f ? -unk_2270.unk_00 / slot_C->unk_1E4[unk_1A04]
                                                             : unk_2270.unk_00 / slot_C->unk_1E4[unk_1A04]) < 1.0f
               ? (unk_2270.unk_00 / slot_C->unk_1E4[unk_1A04] < 0.0f ? -unk_2270.unk_00 / slot_C->unk_1E4[unk_1A04]
                                                                   : unk_2270.unk_00 / slot_C->unk_1E4[unk_1A04])
               : 1.0f;
    if (m_18 > ebp_14)
    {
        ebp_14 = m_18;
    }
    bp_4 = arg_4 * 0.5f;
    arg_0->y += sub_111220(slot_C->unk_204, slot_C->unk_210, slot_C->unk_21C, slot_C->unk_220, &unk_40C, ebp_14, bp_4);
    if (l1C < 0.0f)
    {
        lv_10 = 0.0f;
    }
    else
    {
        lv_10 = flt_42CB00 * l1C;
    }
    sub_112DA0(&unk_418, lv_10, &unk_41C, flt_42CB04, flt_42CB08, 1000.0f, arg_4);
    arg_0->y = arg_0->y - unk_418;
    if (m_18 > 0.5f)
    {
        ebp_14 = 0.0f;
    }
    arg_0->x += sub_111220(slot_C->unk_214, slot_C->unk_218, slot_C->unk_224, slot_C->unk_228, &unk_410, ebp_14, bp_4);
    bp_8 = 0.0f;
    sub_112DA0(&unk_4F0, bp_8, &unk_4F4, flt_42CAF8, flt_42CAFC, 1000.0f, arg_4);
    arg_0->x = arg_0->x + unk_4F0;
}
extern const RwV3d stru_3E2918;
// The remote player's state from the network player showing it: its view
// matrix turned by the facing *arg_4 about stru_3E2918 and placed at *arg_0
// (raised to eye height), its look's pitch *arg_C, its velocity *arg_8; the
// weapon *arg_14 taken in hand (streamed in first, else requested); its
// stance from *arg_10; the flag bits *arg_18 (their previous values kept).
// match: ?pvf_000@type_1BABA0@@UAEXPAUtype_1F8560_v@@PAUtype_4F6B00_F4@@0PAH22PAIPAG@Z @ 0x001BCE50
void type_1BABA0::pvf_000(type_1F8560_v *arg_0, type_4F6B00_F4 *arg_4, type_1F8560_v *arg_8, RwInt32 *arg_C,
                          RwInt32 *arg_10, RwInt32 *arg_14, RwUInt32 *arg_18, RwUInt16 *arg_1C)
{
    RwReal var_4;

    unk_22B0.flags = 2;
    unk_22B0.pad1 = 0;
    unk_22B0.pad2 = 0;
    unk_22B0.pad3 = 0;
    RwMatrixSetIdentityMacro(&unk_22B0);
    var_4 = *(RwReal *)arg_4;
    RwMatrixRotate(&unk_22B0, &stru_3E2918, var_4, rwCOMBINEPRECONCAT);
    unk_22B0.pos.x = arg_0->unk_00;
    unk_22B0.pos.y = arg_0->unk_04 + unk_48;
    unk_22B0.pos.z = arg_0->unk_08;
    unk_530 = *(RwReal *)arg_C;
    unk_2270.unk_00 = arg_8->unk_00;
    unk_2270.unk_04 = arg_8->unk_04;
    unk_2270.unk_08 = arg_8->unk_08;
    if (!unk_1B2C && unk_1AE4 != *arg_14)
    {
        if (sub_10E8C0(*arg_14))
        {
            unk_2134 = sub_10E900(unk_1AE4);
            hand_117370();
            unk_1B30[unk_1AE8] = *arg_14;
            unk_1AE4 = *arg_14;
            unk_1A48[unk_1AE4]->vf_008(this, unk_1A3C.get_unk_08(), unk_1AE4);
            hand_1170B0(1, 1);
        }
        else
            sub_10DA70(*arg_14);
    }
    switch (*arg_10)
    {
    case 0:
        unk_2294 = 0;
        break;
    case 8:
        unk_2294 = 2;
        break;
    default:
        unk_2294 = 1;
    }
    unk_2298 = unk_2288;
    unk_22A0 = unk_228C;
    unk_22A4 = unk_2290;
    unk_2284 = *arg_18 & 2;
    unk_2288 = *arg_18 & 0x40;
    unk_1B1C = (*arg_18 & 1) || unk_2288 ? 1 : 0;
    unk_228C = *arg_18 & 4;
    unk_2290 = *arg_18 & 8;
    if (!unk_1B1C)
        unk_229C = 0;
}
// match: ?sub_1BD1C0@type_1BABA0@@QAEXPAURwMatrixTag@@@Z @ 0x001BD1C0
void type_1BABA0::sub_1BD1C0(RwMatrix *arg_0)
{
    unk_22B0 = *arg_0;
    unk_530 = 0;
    unk_2270.unk_08 = 0.1f;
    unk_2270.unk_04 = 0.1f;
    unk_2270.unk_00 = 0.1f;
    unk_1A04 = 0;
    unk_2294 = 0;
    unk_2284 = 0;
    unk_1B1C = 0;
    unk_2288 = 0;
    unk_228C = 0;
}
// match: ?pvf_014@type_1BABA0@@UAEXPAUtype_75600@@@Z @ 0x001BD270
void type_1BABA0::pvf_014(type_75600 *arg_0)
{
    vf_064(arg_0);
}
// match: ?pvf_018@type_1BABA0@@UAEXPAUtype_75600@@@Z @ 0x001BD2A0
void type_1BABA0::pvf_018(type_75600 *arg_0)
{
    unk_19DC = 0;
    vf_064(arg_0);
    unk_19F8 = 0;
    unk_19D0 = 0xA;
}
// match: ?pvf_020@type_1BABA0@@UAEXPAUtype_4AE70@@@Z @ 0x001BD2F0
void type_1BABA0::pvf_020(type_4AE70 *arg_0)
{
    unk_19DC = 0;
    unk_19F8 = 0;
    unk_19D0 = 0xA;
}
