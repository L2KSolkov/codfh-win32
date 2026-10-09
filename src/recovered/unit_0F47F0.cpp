// The triggered particles (types/type_F5740.h). The original file name is
// not in the image, so it is named for its start address.

#include <string.h>

#include "rw/ostypes.h"
#include "rw/bamatrix.h"
#include "game/frand.h"
#include "game/functions.h"
#include "game/particles.h"
#include "types/type_44350.h"
#include "types/ParticleTrigger.h"
#include "types/type_F5740.h"
#include "types/type_4AE70.h"
#include "types/soundbank.h"
#include "types/type_10F710.h"
#include "types/type_F2FF0.h"
#include "game/data.h"
#include "game/astarpathfinder.h"
#ifdef CODFH_SP
#include "game/gameloop.h"    // sub_19B050 (the level)
#endif

// Its data definitions (PLAN M5), in the image's address order.
// 0x003D932C
extern const RwReal flt_3D932C = 16.666666f;
// 0x004BFDCC
type_F58B0 *dword_4BFDCC;
// 0x004BFDD0
type_F5740 *dword_4BFDD0;
// End of its data definitions.


// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).
type_16C2A0 dword_4BFDD4;
type_16C2A0 dword_4BFDF4;
type_4BFED0 dword_4BFED0[3];
type_4BFED0 dword_4BFE28;
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3D932C@@3MB @ 0x003D932C
// match: ??_C@_0BF@HAGIPECP@m_scheduledParticles?$AA@ @ 0x003D9330
// match: ??_C@_0BF@MCIPIHMC@m_triggeredParticles?$AA@ @ 0x003D9348
// match: ??_C@_0DK@IIJGMNAJ@Warning?4?4adding?5child?5triggered?5@ @ 0x003D9360
// match: __ehhandler$?sub_F4890@@YAXM@Z>1>8 @ 0x0041D094
// match: __ehhandler$?sub_F4890@@YAXM@Z>1 @ 0x0041D0A4
// match: .CRT$XCU+0 @ 0x00427070
// match: .CRT$XCU+4 @ 0x00427074
// match: .CRT$XCU+8 @ 0x00427078
// match: .CRT$XCU+12 @ 0x0042707C

// match: _$E2 @ 0x0030B650
// match: _$E3 @ 0x0030E540
// match: _$E5 @ 0x0030B670
// match: _$E6 @ 0x0030E550
// match: _$E8 @ 0x0030B690
// match: _$E9 @ 0x0030E560
// match: _$E11 @ 0x0030B6C0
// match: _$E12 @ 0x0030E580
// match: ?sub_F47F0@@YAXXZ @ 0x000F47F0
// sp-match: ?sub_F47F0@@YAXXZ @ 0x000BA820
// sp-match: _$E2 @ 0x0021D6D0
// sp-match: _$E5 @ 0x0021D6F0
// sp-match: _$E8 @ 0x0021D710
// sp-match: _$E11 @ 0x0021D740
// sp-match: _$E3 @ 0x0021E8D0
// sp-match: _$E6 @ 0x0021E8E0
// sp-match: _$E9 @ 0x0021E8F0
// sp-match: _$E12 @ 0x0021E910

void sub_F47F0()
{
    dword_4BFDD4.sub_16C2C0(0xAF, 0xBC, "m_triggeredParticles", 4, 0);
    dword_4BFDD0 = 0;
    dword_4BFDF4.sub_16C2C0(0xAF, 0xBC, "m_scheduledParticles", 4, 0);
    dword_4BFDCC = 0;
}

// match: ?sub_F4850@@YAXXZ @ 0x000F4850
// sp-match: ?sub_F4850@@YAXXZ @ 0x000BAF90
void sub_F4850()
{
    sub_F5E30();
}

// match: ?sub_F4860@@YAXXZ @ 0x000F4860
// sp-match: ?sub_F4860@@YAXXZ @ 0x000BAFA0
void sub_F4860()
{
    sub_F5E30();
    dword_4BFDD4.sub_16C4D0(1);
    dword_4BFDF4.sub_16C4D0(1);
}

// The update by arg_0 frames, while there is a player. An emitter with
// children fires them, while its count lasts, when its interval runs out
// (a random count of emissions, each after a random delay; the next
// interval random too), and starts each emission due: its particle system
// at the child's matrix placed by the emission's, its sound (at the player
// when it follows the player, else at the emission) and, with a blast, a
// blast of the emitter's radius and damage there (the player shaken by
// it). A started emitter keeps its sound following the player while it
// plays and is let go once it has no children, system or sound left. An
// emitter without children starts after its delay: its particle system at
// its matrix, its sound and its blast.
// match: ?sub_F4890@@YAXM@Z @ 0x000F4890
// match: __ehhandler$?sub_F4890@@YAXM@Z-0x16 @ 0x003010D0
// match: __ehhandler$?sub_F4890@@YAXM@Z @ 0x003010E6
// sp-match: ?sub_F4890@@YAXM@Z @ 0x000BAFC0
void sub_F4890(RwReal arg_0)
{
    type_F5740 *v_14;
    type_F5740 *v_18;
    type_3D3548 *v_1C;
    RwInt32 v_20;
    type_F58B0 *v_50;
    type_F5740 *v_54;
    RwMatrix v_A0;
    type_F5740 *v_A4;
    type_F5740 *v_A8;
    RwMatrix v_F0;
    RwMatrix v_230;

    v_14 = 0;
    v_18 = dword_4BFDD0;
    v_1C = sub_1745A0(0);
    if (!v_1C)
        return;
    while (v_18)
    {
        v_14 = v_18->unk_A8;
        if (v_18->unk_7C)
        {
            if (v_18->unk_84 < v_18->unk_80 || v_18->unk_80 == -1)
            {
                if (v_18->unk_90 > 0.0f && !v_18->unk_94)
                    v_18->unk_90 = v_18->unk_90 - arg_0;
                else
                {
                    v_18->unk_18 = 1;
                    v_20 = 0;
                    if (v_18->unk_94)
                        v_20 = v_18->unk_94;
                    else
                        v_20 = RpRandom() % (v_18->unk_9C - v_18->unk_98 + 1) + v_18->unk_98;
                    while (v_20-- > 0)
                    {
                        RwReal v_38;

                        v_38 = frand_range(v_18->unk_A0, v_18->unk_A4);
                        sub_F58B0(v_18, v_38);
                    }
                    v_18->unk_94 = 0;
                    v_18->unk_84++;
                    v_18->unk_90 = frand_range(v_18->unk_88, v_18->unk_8C);
                }
                sub_F57C0(arg_0);
                v_50 = 0;
                while ((v_50 = sub_F57F0()) != 0)
                {
                    v_54 = v_50->unk_00;
                    sub_F54E0(v_54, &v_A0);
                    v_A4 = v_54;
                    while (v_A4)
                    {
                        v_A8 = v_A4->unk_B0;
                        sub_F5370(v_A4, &v_F0, true);
                        RwMatrixTransform(&v_F0, &v_A0, rwCOMBINEPOSTCONCAT);
                        v_A4->unk_28.sub_F2880((type_F2FF0 *)sub_F2FF0(v_A4->unk_00, &v_F0, 0, 0, v_A4->unk_B8 != 0,
                                                                       false));
                        if (v_54->unk_20.unk_00 && v_54->unk_20.unk_04)
                        {
                            if (v_54->unk_1A && v_1C)
                                v_54->unk_60 = dword_4B1E98.sub_8A980(&v_54->unk_20, 0, 8, v_1C->sub_CD550(), 0, 0);
                            else
                                v_54->unk_60 = dword_4B1E98.sub_8A980(&v_54->unk_20, 0, 8, &v_F0.pos, 0, 0);
                            if (v_54->unk_60 == -1)
                                v_54->unk_60 = 0;
                            if (v_54->unk_60)
                            {
                                if (v_54->unk_1A && v_1C)
                                {
                                    do
                                    {
                                        ((type_44C4E8 *)v_54->unk_60)->unk_58 = *v_1C->sub_CD550();
                                        if (((type_44C4E8 *)v_54->unk_60)->unk_30)
                                        {
                                            Behavior_DispatchCallback(((type_44C4E8 *)v_54->unk_60)->unk_30, 0, 1,
                                                       v_1C->sub_CD550());
                                        }
                                    } while (0);
                                }
                                else
                                {
                                    do
                                    {
                                        ((type_44C4E8 *)v_54->unk_60)->unk_58 = v_F0.pos;
                                        if (((type_44C4E8 *)v_54->unk_60)->unk_30)
                                        {
                                            Behavior_DispatchCallback(((type_44C4E8 *)v_54->unk_60)->unk_30, 0, 1, &v_F0.pos);
                                        }
                                    } while (0);
                                }
                            }
                        }
                        if (v_54->unk_34)
                        {
                            type_F4890_50 v_124;

                            v_124.unk_00_r = 0.0f;
                            v_124.unk_04_r = v_54->unk_3C_f;
                            v_124.unk_08 = v_54->unk_40;
                            v_124.unk_0C = v_54->unk_44;
                            v_124.unk_10 = v_54->unk_48;
                            v_124.unk_14 = v_54->unk_4C;
                            v_124.unk_18 = v_54->unk_50;
                            v_124.unk_1C = v_54->unk_64;
                            v_124.unk_24 = v_54->unk_6C;
                            v_124.unk_20 = v_54->unk_68;
                            v_124.unk_28 = v_54->unk_70;
                            v_124.unk_2C = v_54->unk_74;
                            v_124.unk_30 = v_54->unk_78;
                            type_F4890_blast v_1B0;

                            v_1B0.unk_4C_r = v_54->unk_38;
                            v_1B0.unk_04 = v_54->unk_3C;
                            v_1B0.unk_50 = v_124;
                            type_4AE70 v_1E4;

                            v_1E4.unk_00 = 0x804;
                            v_1E4.unk_08 = 0;
                            v_1E4.unk_0C = &v_F0;
                            v_1E4.unk_10 = v_54->unk_38;
                            v_1E4.unk_14 = v_54->unk_38;
                            v_1E4.unk_18 = v_54->unk_38;
                            v_1E4.unk_2C = v_54->unk_3C_f;
                            v_1E4.unk_30 = (RwInt32)&v_1B0;
                            sub_9A960(&v_1E4);
                            if (sub_1745A0(0))
                                ((type_10F710 *)sub_1745A0(0))->sub_114F90((type_114F90 *)&v_1B0, &v_F0.pos);
                        }
                        v_A4 = v_A8;
                    }
                }
            }
            if (v_18->unk_18)
            {
                if (v_18->unk_60)
                {
                    if ((((((type_44C4E8 *)v_18->unk_60)->unk_34 & 2) != 0) != 0))
                    {
                        if (v_18->unk_1A && v_1C)
                        {
                            do
                            {
                                ((type_44C4E8 *)v_18->unk_60)->unk_58 = *v_1C->sub_CD550();
                                if (((type_44C4E8 *)v_18->unk_60)->unk_30)
                                {
                                    Behavior_DispatchCallback(((type_44C4E8 *)v_18->unk_60)->unk_30, 0, 1, v_1C->sub_CD550());
                                }
                            } while (0);
                        }
                    }
                    else
                        v_18->unk_60 = 0;
                }
                if (!v_18->unk_7C && !v_18->unk_28.get_unk_08() && !v_18->unk_60)
                    sub_F5C70(v_18);
            }
        }
        else if (v_18->unk_18)
        {
            if (v_18->unk_60)
            {
                if ((((((type_44C4E8 *)v_18->unk_60)->unk_34 & 2) != 0) != 0))
                {
                    if (v_18->unk_1A && v_1C)
                    {
                        do
                        {
                            ((type_44C4E8 *)v_18->unk_60)->unk_58 = *v_1C->sub_CD550();
                            if (((type_44C4E8 *)v_18->unk_60)->unk_30)
                            {
                                Behavior_DispatchCallback(((type_44C4E8 *)v_18->unk_60)->unk_30, 0, 1, v_1C->sub_CD550());
                            }
                        } while (0);
                    }
                }
                else
                    v_18->unk_60 = 0;
            }
            if (!v_18->unk_28.get_unk_08() && !v_18->unk_60)
                sub_F5C70(v_18);
        }
        else if (v_18->unk_08 <= 0.0f && !v_18->unk_18)
        {
            v_18->unk_18 = 1;
            sub_F5370(v_18, &v_230, false);
            v_18->unk_28.sub_F2880((type_F2FF0 *)sub_F2FF0(v_18->unk_00, &v_230, 0, 0, v_18->unk_B8 != 0, false));
            if (v_18->unk_20.unk_00 && v_18->unk_20.unk_04)
            {
                if (v_18->unk_1A && v_1C)
                    v_18->unk_60 = dword_4B1E98.sub_8A980(&v_18->unk_20, 0, 8, v_1C->sub_CD550(), 0, 0);
                else
                    v_18->unk_60 = dword_4B1E98.sub_8A980(&v_18->unk_20, 0, 8, &v_230.pos, 0, 0);
                if (v_18->unk_60 == -1)
                    v_18->unk_60 = 0;
                if (v_18->unk_60)
                {
                    if (v_18->unk_1A && v_1C)
                    {
                        do
                        {
                            ((type_44C4E8 *)v_18->unk_60)->unk_58 = *v_1C->sub_CD550();
                            if (((type_44C4E8 *)v_18->unk_60)->unk_30)
                            {
                                Behavior_DispatchCallback(((type_44C4E8 *)v_18->unk_60)->unk_30, 0, 1, v_1C->sub_CD550());
                            }
                        } while (0);
                    }
                    else
                    {
                        do
                        {
                            ((type_44C4E8 *)v_18->unk_60)->unk_58 = v_230.pos;
                            if (((type_44C4E8 *)v_18->unk_60)->unk_30)
                            {
                                Behavior_DispatchCallback(((type_44C4E8 *)v_18->unk_60)->unk_30, 0, 1, &v_230.pos);
                            }
                        } while (0);
                    }
                }
            }
            if (v_18->unk_34)
            {
                type_F4890_50 v_264;

                v_264.unk_00_r = 0.0f;
                v_264.unk_04_r = v_18->unk_3C_f;
                v_264.unk_08 = v_18->unk_40;
                v_264.unk_0C = v_18->unk_44;
                v_264.unk_10 = v_18->unk_48;
                v_264.unk_14 = v_18->unk_4C;
                v_264.unk_18 = v_18->unk_50;
                v_264.unk_1C = v_18->unk_64;
                v_264.unk_24 = v_18->unk_6C;
                v_264.unk_20 = v_18->unk_68;
                v_264.unk_28 = v_18->unk_70;
                v_264.unk_2C = v_18->unk_74;
                v_264.unk_30 = v_18->unk_78;
                type_F4890_blast v_2F0;

                v_2F0.unk_4C_r = v_18->unk_38;
                v_2F0.unk_04 = v_18->unk_3C;
                v_2F0.unk_50 = v_264;
                type_4AE70 v_324;

                v_324.unk_00 = 0x804;
                v_324.unk_08 = 0;
                v_324.unk_0C = &v_230;
                v_324.unk_10 = v_18->unk_38;
                v_324.unk_14 = v_18->unk_38;
                v_324.unk_18 = v_18->unk_38;
                v_324.unk_2C = v_18->unk_3C_f;
                v_324.unk_30 = (RwInt32)&v_2F0;
                sub_9A960(&v_324);
            }
        }
        else if (v_18->unk_08 > 0.0f)
            v_18->unk_08 = v_18->unk_08 - arg_0;
        v_18 = v_14;
    }
}

// match: ?sub_F5370@@YAXPAUtype_F5740@@PAURwMatrixTag@@_N@Z @ 0x000F5370
// sp-match: ?sub_F5370@@YAXPAUtype_F5740@@PAURwMatrixTag@@_N@Z @ 0x000BA870
void sub_F5370(type_F5740 *arg_0, RwMatrix *arg_4, bool arg_8)
{
    Trigger *var_4 = arg_0->unk_54.unk_08;
    RwV3d var_10;

    RwMatrixSetIdentity(arg_4);
    if (var_4)
    {
        if (arg_0->unk_1C)
        {
            *arg_4 = *(RwMatrix *)var_4->unk_60;
        }
        else
        {
            arg_4->pos = *(RwV3d *)&var_4->unk_90;
        }
        if (arg_8)
        {
            arg_4->pos.z = 0.0f;
            arg_4->pos.y = 0.0f;
            arg_4->pos.x = 0.0f;
        }
    }
    if (!arg_0->unk_1E)
    {
        sub_1414C0(&var_10, &arg_0->unk_0C, arg_4);
        arg_4->pos = var_10;
    }
    else
    {
        arg_4->pos = arg_0->unk_0C;
    }
}

// match: ?sub_F54E0@@YAXPAUtype_F5740@@PAURwMatrixTag@@@Z @ 0x000F54E0
// sp-match: ?sub_F54E0@@YAXPAUtype_F5740@@PAURwMatrixTag@@@Z @ 0x000BA950
void sub_F54E0(type_F5740 *arg_0, RwMatrix *arg_4)
{
    RwV3d var_C;
    RwV3d var_18;
    Trigger *var_1C;

    RwMatrixSetIdentity(arg_4);
    if (arg_0->unk_7C)
    {
        var_1C = arg_0->unk_54.unk_08;
        switch (var_1C->get_unk_46())
        {
        case 0:
            var_18.x = var_18.y = var_18.z = var_1C->get_unk_48();
            break;
        case 1:
            var_18.x = var_18.z = var_1C->get_unk_48();
            var_18.y = var_1C->get_unk_4C() / 2.0f;
            break;
        case 2:
            var_18.x = var_1C->get_unk_48() / 2.0f;
            var_18.y = var_1C->get_unk_4C() / 2.0f;
            var_18.z = var_1C->get_unk_50() / 2.0f;
            break;
        default:
            var_18.x = var_18.y = var_18.z = 0.0f;
            break;
        }
        var_18.x = frand_range(-var_18.x, var_18.x);
        var_18.y = frand_range(-var_18.y, var_18.y);
        var_18.z = frand_range(-var_18.z, var_18.z);
        *arg_4 = *(RwMatrix *)var_1C->unk_60;
        sub_1414C0(&var_C, &var_18, arg_4);
        arg_4->pos = var_C;
    }
}

// match: ?sub_F5740@@YAPAUtype_F5740@@PAVParticleTrigger@@HPAUParticleTrigger_entry@@@Z @ 0x000F5740
// sp-match: ?sub_F5740@@YAPAUtype_F5740@@PAVParticleTrigger@@HPAUParticleTrigger_entry@@@Z @ 0x000BB7F0
type_F5740 *sub_F5740(ParticleTrigger *arg_0, RwInt32 arg_4, ParticleTrigger_entry *arg_8)
{
    type_F5740 *var_4 = sub_F5920(arg_0, arg_4, arg_8);

    if (var_4)
    {
        var_4->unk_A8 = dword_4BFDD0;
        var_4->unk_AC = 0;
        if (dword_4BFDD0)
        {
            dword_4BFDD0->unk_AC = var_4;
        }
        dword_4BFDD0 = var_4;
        var_4->unk_B4 = 0;
        var_4->unk_B0 = 0;
    }
    return var_4;
}

// match: ?sub_F57C0@@YAXM@Z @ 0x000F57C0
// sp-match: ?sub_F57C0@@YAXM@Z @ 0x000BAB20
void sub_F57C0(RwReal arg_0)
{
    type_F58B0 *var_4 = dword_4BFDCC;

    while (var_4)
    {
        var_4->unk_04 -= arg_0;
        var_4 = var_4->unk_08;
    }
}

// match: ?sub_F57F0@@YAPAUtype_F58B0@@XZ @ 0x000F57F0
// sp-match: ?sub_F57F0@@YAPAUtype_F58B0@@XZ @ 0x000BAB50
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
type_F58B0 *sub_F57F0()
{
    type_F58B0 *slot_C;
    type_F58B0 *bp_8;
    type_F58B0 *bp_4;

    bp_8 = 0;
    bp_4 = dword_4BFDCC;
    while (bp_4)
    {
        if (bp_4->unk_04 <= 0.0f)
        {
            bp_8 = bp_4;
            slot_C = bp_8->unk_0C;
            if (slot_C)
            {
                slot_C->unk_08 = bp_8->unk_08;
            }
            slot_C = bp_8->unk_08;
            if (slot_C)
            {
                slot_C->unk_0C = bp_8->unk_0C;
            }
            if (bp_8 == dword_4BFDCC)
            {
                dword_4BFDCC = bp_8->unk_08;
            }
            bp_8->unk_08 = 0;
            bp_8->unk_0C = 0;
            dword_4BFDF4.sub_16C710(bp_8);
            break;
        }
        bp_4 = bp_4->unk_08;
    }
    return bp_8;
}

// match: ?sub_F58B0@@YAPAUtype_F58B0@@PAUtype_F5740@@M@Z @ 0x000F58B0
// sp-match: ?sub_F58B0@@YAPAUtype_F58B0@@PAUtype_F5740@@M@Z @ 0x000BABC0
type_F58B0 *sub_F58B0(type_F5740 *arg_0, RwReal arg_4)
{
    type_F58B0 *var_4 = (type_F58B0 *)dword_4BFDF4.sub_16C5A0(0);

    if (var_4)
    {
        var_4->unk_00 = arg_0;
        var_4->unk_04 = arg_4;
        var_4->unk_08 = dword_4BFDCC;
        var_4->unk_0C = 0;
        if (dword_4BFDCC)
        {
            dword_4BFDCC->unk_0C = var_4;
        }
        dword_4BFDCC = var_4;
    }
    return var_4;
}

// match: ?sub_F5920@@YAPAUtype_F5740@@PAVParticleTrigger@@HPAUParticleTrigger_entry@@@Z @ 0x000F5920
// sp-match: ?sub_F5920@@YAPAUtype_F5740@@PAVParticleTrigger@@HPAUParticleTrigger_entry@@@Z @ 0x000BAC00
type_F5740 *sub_F5920(ParticleTrigger *arg_0, RwInt32 arg_4, ParticleTrigger_entry *arg_8)
{
    type_F5740 *var_4 = (type_F5740 *)dword_4BFDD4.sub_16C5A0(0);

    if (var_4)
    {
        var_4->unk_00 = arg_8->unk_04;
        var_4->unk_08 = arg_8->unk_08_f * 60.0f;
        var_4->unk_1A = arg_8->unk_20_w;
        var_4->unk_60 = 0;
        var_4->unk_18 = 0;
        var_4->unk_34 = arg_8->unk_2C;
        var_4->unk_38 = arg_8->unk_30;
        var_4->unk_3C = arg_8->unk_34;
        var_4->unk_04 = arg_4;
        var_4->unk_1C = arg_8->unk_02;
        var_4->unk_1E = arg_8->unk_24_w;
#ifdef CODFH_SP // single player fills them on level 7 (SP 0xBAC00 calls sub_19B050), as reals
        if (sub_19B050() == 7)
        {
            var_4->unk_44 = arg_8->unk_30;
            var_4->unk_40 = var_4->unk_44;
            var_4->unk_4C_f = arg_8->unk_34_f;
            var_4->unk_48_f = var_4->unk_4C_f;
        }
#else
        // Never taken: the fields it fills are unused.
        if (FALSE)
        {
            var_4->unk_44 = arg_8->unk_30;
            var_4->unk_40 = var_4->unk_44;
            var_4->unk_4C = arg_8->unk_34;
            var_4->unk_48 = var_4->unk_4C;
        }
#endif
        var_4->unk_54.init();
        var_4->unk_54.sub_144940(arg_0);
        var_4->unk_28.init();
        var_4->unk_0C = arg_8->unk_0C;
        var_4->unk_80 = arg_8->unk_68;
        var_4->unk_84 = 0;
        var_4->unk_88 = arg_8->unk_6C_f;
        var_4->unk_8C = arg_8->unk_70_f;
        var_4->unk_90 = frand_range(var_4->unk_88, var_4->unk_8C);
        var_4->unk_7C = arg_8->unk_64;
        var_4->unk_94 = arg_8->unk_74;
        var_4->unk_98 = arg_8->unk_78;
        var_4->unk_9C = arg_8->unk_7C;
        var_4->unk_A0 = arg_8->unk_80;
        var_4->unk_A4 = arg_8->unk_84;
        var_4->unk_64 = arg_8->unk_4C;
        var_4->unk_68 = arg_8->unk_50;
        var_4->unk_6C = arg_8->unk_58;
        var_4->unk_70 = arg_8->unk_54;
        var_4->unk_74 = arg_8->unk_5C;
        var_4->unk_78 = arg_8->unk_60;
        memcpy(&var_4->unk_20, &arg_8->unk_18, 8);
    }
    return var_4;
}

// match: ?sub_F5BC0@@YAPAUtype_F5740@@PAU1@PAVParticleTrigger@@HPAUParticleTrigger_entry@@@Z @ 0x000F5BC0
// sp-match: ?sub_F5BC0@@YAPAUtype_F5740@@PAU1@PAVParticleTrigger@@HPAUParticleTrigger_entry@@@Z @ 0x000BAD90
type_F5740 *sub_F5BC0(type_F5740 *arg_0, ParticleTrigger *arg_4, RwInt32 arg_8, ParticleTrigger_entry *arg_C)
{
    type_F5740 *var_4 = sub_F5920(arg_4, arg_8, arg_C);

    if (var_4)
    {
        var_4->unk_AC = 0;
        var_4->unk_A8 = 0;
        var_4->unk_B4 = arg_0;
        if (arg_0)
        {
            var_4->unk_B0 = arg_0->unk_B0;
            if (arg_0->unk_B0)
            {
                arg_0->unk_B0->unk_B4 = var_4;
            }
            arg_0->unk_B0 = var_4;
        }
        else
        {
#ifndef CODFH_SP // single player compiles the debug print out (SP 0xBAD90)
            sub_19A750("Warning..adding child triggered particle to null parent.\n");
#endif
            var_4->unk_B0 = 0;
        }
    }
    return var_4;
}

// match: ?sub_F5C70@@YAXPAUtype_F5740@@@Z @ 0x000F5C70
// sp-match: ?sub_F5C70@@YAXPAUtype_F5740@@@Z @ 0x000BAE00
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_F5C70(type_F5740 *arg_0)
{
    type_F58B0 *m_18;
    ParticleTrigger *ebp_14;
    Trigger *lv_10;
    type_F2FF0 *slot_C;
    type_F58B0 *bp_8;
    type_F5740 *bp_4;

    slot_C = arg_0->unk_28.unk_08;
    if (slot_C)
    {
        sub_F3300(slot_C);
    }
    arg_0->unk_28.sub_F2880(0);
    lv_10 = arg_0->unk_54.unk_08;
    if (lv_10 && lv_10->vf_008() == 0x12)
    {
        ebp_14 = (ParticleTrigger *)lv_10;
        ebp_14->sub_A8EE0(arg_0);
    }
    arg_0->unk_54.sub_144940(0);
    bp_4 = arg_0->unk_B0;
    if (arg_0->unk_AC)
    {
        arg_0->unk_AC->unk_A8 = arg_0->unk_A8;
    }
    if (arg_0->unk_A8)
    {
        arg_0->unk_A8->unk_AC = arg_0->unk_AC;
    }
    if (arg_0 == dword_4BFDD0)
    {
        dword_4BFDD0 = arg_0->unk_A8;
    }
    arg_0->unk_A8 = 0;
    arg_0->unk_AC = 0;
    bp_8 = dword_4BFDCC;
    while (bp_8)
    {
        m_18 = bp_8->unk_08;
        if (bp_8->unk_00 == arg_0)
        {
            if (bp_8->unk_0C)
            {
                bp_8->unk_0C->unk_08 = bp_8->unk_08;
            }
            if (bp_8->unk_08)
            {
                bp_8->unk_08->unk_0C = bp_8->unk_0C;
            }
            if (bp_8 == dword_4BFDCC)
            {
                dword_4BFDCC = bp_8->unk_08;
            }
            bp_8->unk_08 = 0;
            bp_8->unk_0C = 0;
            dword_4BFDF4.sub_16C710(bp_8);
        }
        bp_8 = m_18;
    }
    dword_4BFDD4.sub_16C710(arg_0);
    if (bp_4)
    {
        sub_F5C70(bp_4);
    }
}

// match: ?sub_F5E30@@YAXXZ @ 0x000F5E30
// sp-match: ?sub_F5E30@@YAXXZ @ 0x000BAF10
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_F5E30()
{
    type_F58B0 *ebp_14;
    type_F58B0 *lv_10;
    type_F58B0 *slot_C;
    type_F5740 *bp_8;
    type_F5740 *bp_4;

    bp_4 = dword_4BFDD0;
    bp_8 = 0;
    while (bp_4)
    {
        bp_8 = bp_4->unk_A8;
        sub_F5C70(bp_4);
        bp_4 = bp_8;
    }
    slot_C = dword_4BFDCC;
    lv_10 = 0;
    while (slot_C)
    {
        lv_10 = slot_C->unk_08;
        ebp_14 = slot_C->unk_0C;
        if (ebp_14)
        {
            ebp_14->unk_08 = slot_C->unk_08;
        }
        ebp_14 = slot_C->unk_08;
        if (ebp_14)
        {
            ebp_14->unk_0C = slot_C->unk_0C;
        }
        if (slot_C == dword_4BFDCC)
        {
            dword_4BFDCC = slot_C->unk_08;
        }
        slot_C->unk_08 = 0;
        slot_C->unk_0C = 0;
        dword_4BFDF4.sub_16C710(slot_C);
        slot_C = lv_10;
    }
}
