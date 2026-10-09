// Split from unit_0F2880.cpp at 0x0F39F0, where the image starts another object (type_F2FF0's,
// its operator delete first): its .rdata begins at 0x3D9304 with its own copy of the
// unreferenced 16.666666, before sub_F3C70's -15 (its first literal, which unit_0FD730's -15
// shares), after the sprite systems' literals (PLAN M7).

#include <string.h>
#include <stdio.h>
#include "rw/ostypes.h"
#include "game/frand.h"
#include "rw/bamatrix.h"
#include "rw/baframe.h"
#include "rw/bastream.h"
#include "rw/babintex.h"
#include "rw/batextur.h"
#include "rw/badevice.h"
#include "rw/baengine.h"
#include "rw/rpatomic.h"
#include "rw/rprandom.h"
#include "rw/rt2d.h"
#include "game/data.h"
#include "game/functions.h"
#include "game/gameloop.h"
#include "game/decals.h"
#include "game/particles.h"
#include "types/asynchload.h"
#include "types/type_3D3548.h"
#include "types/type_F2880.h"
#include "rws/skinhelper.h"
#include "game/pooledconsts.h"
#include "rw/bavector.h"

// Its data definitions (PLAN M5), in the image's address order.
#ifndef CODFH_SP // MP only: single player has no unreferenced 16.666666f here: unit_0F4570's constants follow unit_0F2880's "%s.spp" (SP 0x2E58C0-0x2E58C8)
// 0x003D9304
extern const RwReal flt_3D9304 = 16.666666f;
#endif

// match: ?flt_3D9304@@3MB @ 0x003D9304


// match: ??3type_F2FF0@@SAXPAX@Z @ 0x000F39F0
// sp-match: ??3type_F2FF0@@SAXPAX@Z @ 0x000B9E80
void type_F2FF0::operator delete(void *arg_0)
{
    if (dword_4BFD44.sub_16C770(arg_0))
    {
        dword_4BFD44.sub_16C710(arg_0);
    }
    else if (dword_4BFD98.sub_16C770(arg_0))
    {
        dword_4BFD98.sub_16C710(arg_0);
        dword_4BCE3C--;
    }
    dword_4BFDC4--;
}
// match: ??0type_F2FF0@@QAE@XZ @ 0x000F3A60
// sp-match: ??0type_F2FF0@@QAE@XZ @ 0x000B9ED0
type_F2FF0::type_F2FF0()
{
    unk_40 = 0;
    unk_48 = 0;
    unk_4C = 0;
    unk_15C = 0;
    unk_60.unk_00 = 0;
    unk_60.unk_04 = 0;
    unk_150 = 0;
    unk_60.unk_D4 = 0;
    unk_60.unk_D8 = 0;
}
// match: ??1type_F2FF0@@QAE@XZ @ 0x000F3AE0
// sp-match: ??1type_F2FF0@@QAE@XZ @ 0x000BA540
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
type_F2FF0::~type_F2FF0()
{
    if (unk_40 & 4)
    {
        sub_F3B50();
    }
    if (unk_15C)
    {
        type_F2880 *bp_8 = unk_15C;
        type_F2880 *bp_4 = 0;

        while (bp_8)
        {
            bp_4 = bp_8->unk_00;
            bp_8->sub_F2880(0);
            bp_8 = bp_4;
        }
        unk_15C = 0;
    }
}
// match: ?sub_F3B50@type_F2FF0@@QAEHXZ @ 0x000F3B50
// sp-match: ?sub_F3B50@type_F2FF0@@QAEHXZ @ 0x000B9F00
RwInt32 type_F2FF0::sub_F3B50()
{
    if (unk_40 & 4)
    {
        if (unk_40 & 0x10)
        {
            if (unk_60.unk_00)
            {
                ::operator delete(unk_60.unk_00);
            }
            if (unk_60.unk_04)
            {
                ::operator delete(unk_60.unk_04);
            }
            unk_60.unk_00 = 0;
            unk_60.unk_04 = 0;
            dword_4BFDC0 -= unk_60.unk_1C;
        }
        sub_F2F80(this);
        sub_19E940(&unk_60);
    }
    unk_40 = 0;
    return 1;
}
// match: ?sub_F3C00@type_F2FF0@@QAEHPAUtype_F3130@@PAURwMatrixTag@@MHH_N@Z @ 0x000F3C00
// sp-match: ?sub_F3C00@type_F2FF0@@QAEHPAUtype_F3130@@PAURwMatrixTag@@MHH_N@Z @ 0x000BA580
RwInt32 type_F2FF0::sub_F3C00(type_F3130 *arg_0, RwMatrix *arg_4, RwReal arg_8, RwInt32 arg_C, RwInt32 arg_10,
                              bool arg_14)
{
    if (arg_0->unk_00 >= 3 && arg_0->unk_A8)
    {
        if (arg_C != 1)
        {
            return sub_F3E70(arg_0, arg_4, arg_8, arg_C);
        }
        return 0;
    }
    return sub_F3C70(arg_0, arg_4, arg_8, arg_C, arg_10, arg_14);
}
// match: ?sub_F3C70@type_F2FF0@@QAEHPAUtype_F3130@@PAURwMatrixTag@@MHH_N@Z @ 0x000F3C70
// sp-match: ?sub_F3C70@type_F2FF0@@QAEHPAUtype_F3130@@PAURwMatrixTag@@MHH_N@Z @ 0x000B9F70
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_F2FF0::sub_F3C70(type_F3130 *arg_0, RwMatrix *arg_4, RwReal arg_8, RwInt32 arg_C, RwInt32 arg_10,
                              bool arg_14)
{
    RwReal bp_8;
    RwReal bp_4;

    if (unk_40 & 4)
    {
        sub_F3B50();
    }
    unk_44 = arg_0;
    sub_19EC70(&unk_60, arg_4, arg_0, arg_14);
    unk_58 = 0.0f;
    if (arg_0->unk_20 == 0.0f)
    {
        unk_58 = arg_0->unk_24;
    }
    unk_00 = *arg_4;
    if (arg_C != 1 && arg_10)
    {
        bp_4 = (RwReal)RpRandom() * (1.0f / RPRANDMAX);
        unk_00.pos.x += lerp(-15.0f, 15.0f, bp_4);
        bp_8 = (RwReal)RpRandom() * (1.0f / RPRANDMAX);
        unk_00.pos.z += lerp(-15.0f, 15.0f, bp_8);
    }
    unk_5C = arg_0->unk_04;
    if (unk_5C)
    {
        RwTextureSetFilterMode(unk_5C, rwFILTERLINEAR);
    }
    unk_40 = 9;
    unk_50 = arg_8;
    unk_54 = unk_50;
    unk_154 = 0;
    unk_60.unk_14 = 1;
    if (unk_44->unk_00 >= 4 && unk_44->unk_F8 + unk_44->unk_FC + unk_44->unk_100 + unk_44->unk_104 != 0.0f)
    {
        unk_60.unk_14 |= 8;
    }
    if (arg_C == 1)
    {
        unk_40 |= 0x20;
    }
    sub_F2F40(this);
    unk_40 |= 4;
    return 1;
}
// match: ?sub_F3E70@type_F2FF0@@QAEHPAUtype_F3130@@PAURwMatrixTag@@MH@Z @ 0x000F3E70
// sp-match: ?sub_F3E70@type_F2FF0@@QAEHPAUtype_F3130@@PAURwMatrixTag@@MH@Z @ 0x000BA0D0
RwInt32 type_F2FF0::sub_F3E70(type_F3130 *arg_0, RwMatrix *arg_4, RwReal arg_8, RwInt32 arg_C)
{
    RwMatrix var_50;
    RwV3d *var_54;
    RwV3d var_60;
    RwInt32 var_64;

    if (unk_40 & 4)
    {
        sub_F3B50();
    }
    unk_44 = arg_0;
    var_50 = *arg_4;
    if (RwV3dLength((RwV3d *)&var_50.right) < 0.0001f
        || RwV3dLength((RwV3d *)&var_50.up) < 0.0001f
        || RwV3dLength((RwV3d *)&var_50.at) < 0.0001f)
    {
        var_54 = &var_50.pos;
        var_60 = *var_54;
        RwMatrixSetIdentityMacro(&var_50);
        *var_54 = var_60;
        RwMatrixUpdate(&var_50);
    }
    RwMatrixOrthoNormalize(&var_50, &var_50);
    unk_00 = var_50;
    unk_60.unk_1C = arg_0->unk_08;
    unk_60.unk_00 = (RwMatrix *)RWSMalloc(unk_60.unk_1C * 0x40, 0x34250); // not an address: an allocation tag
    unk_60.unk_04 = (type_F2FF0_60_04 *)RWSMalloc(unk_60.unk_1C * 0x24, 0x34250); // not an address: an allocation tag
    if (!unk_60.unk_00 || !unk_60.unk_04)
    {
        if (unk_60.unk_00)
        {
            ::operator delete(unk_60.unk_00);
        }
        if (unk_60.unk_04)
        {
            ::operator delete(unk_60.unk_04);
        }
        unk_60.unk_00 = 0;
        unk_60.unk_04 = 0;
        return 0;
    }
    dword_4BFDC0 += unk_60.unk_1C;
    for (var_64 = 0; var_64 < unk_60.unk_1C; var_64++)
    {
        unk_60.unk_00[var_64] = unk_00;
        unk_60.unk_00[var_64].pos.z = 10000000.0f;
        unk_60.unk_04[var_64].unk_00 = -1.0f;
    }
    unk_60.unk_20 = sub_F2D80(arg_0->unk_AC);
    unk_40 = 0x19;
    unk_50 = arg_8;
    unk_54 = unk_50;
    if (arg_C == 1)
    {
        unk_40 |= 0x20;
    }
    unk_60.unk_14 = 1;
    unk_60.unk_18 = 0;
    unk_60.unk_08 = 0;
    unk_60.unk_0C = 0;
    unk_60.unk_10 = 0;
    unk_154 = 0;
    sub_F2F40(this);
    unk_40 |= 4;
    return 1;
}
// match: ?sub_F4190@type_F2FF0@@QAEHPAURwCamera@@MM@Z @ 0x000F4190
// sp-match: ?sub_F4190@type_F2FF0@@QAEHPAURwCamera@@MM@Z @ 0x000BA5C0
RwInt32 type_F2FF0::sub_F4190(RwCamera *arg_0, RwReal arg_4, RwReal arg_8)
{
    if (unk_40 & 0x10)
    {
        return sub_F4300(arg_4, arg_8);
    }
    return sub_F41D0(arg_0, arg_4, arg_8);
}
// match: ?sub_F41D0@type_F2FF0@@QAEHPAURwCamera@@MM@Z @ 0x000F41D0
// sp-match: ?sub_F41D0@type_F2FF0@@QAEHPAURwCamera@@MM@Z @ 0x000BA320
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_F2FF0::sub_F41D0(RwCamera *arg_0, RwReal arg_4, RwReal arg_8)
{
    RwReal x1C;
    RwReal w20;
    RwSphere m_18;
    RwInt32 bp_8;
    RwInt32 bp_4;

    dword_4BFDBC = arg_0;
    bp_4 = 1;
    if (unk_40 & 1)
    {
        bp_8 = rwSPHEREINSIDE;
        m_18.center = unk_00.pos;
        m_18.radius = 6000.0f;
        if (arg_0)
        {
            bp_8 = RwCameraFrustumTestSphere(arg_0, &m_18);
        }
        // Always taken: the test's result is not used.
        if (TRUE)
        {
            if (unk_154)
            {
                bp_4 = ((RwInt32 (*)(type_F2FF0 *, RwReal))unk_154)(this, arg_8);
            }
            unk_60.unk_70 = unk_58;
            unk_58 += arg_8;
            unk_54 = arg_4;
            unk_40 |= 2;
        }
        else
        {
            unk_40 &= ~2;
        }
        if (unk_44->unk_20 > 0.0f)
        {
            w20 = unk_44->unk_20;
            x1C = unk_44->unk_24;
#ifdef CODFH_SP
            if (unk_58 > w20 + x1C + 0.1f) // shape: compared the other way round (SP 0xBA3CB)
#else
            if (w20 + x1C + 0.1f < unk_58)
#endif
            {
                bp_4 = 0;
            }
        }
    }
    return bp_4;
}
// match: ?sub_F4300@type_F2FF0@@QAEHMM@Z @ 0x000F4300
// sp-match: ?sub_F4300@type_F2FF0@@QAEHMM@Z @ 0x000BA3F0
RwInt32 type_F2FF0::sub_F4300(RwReal arg_0, RwReal arg_4)
{
    RwInt32 var_4 = 1;

    if (unk_40 & 1)
    {
        unk_40 |= 8;
        if (unk_40 & 8)
        {
            if (unk_154)
            {
                var_4 = ((RwInt32 (*)(type_F2FF0 *, RwReal))unk_154)(this, arg_4);
            }
            if (var_4)
            {
                var_4 = sub_EF040(this, arg_4);
            }
            unk_54 = arg_0;
            unk_40 |= 2;
        }
        else
        {
            unk_40 &= ~2;
        }
    }
    return var_4;
}
// match: ?sub_F43B0@type_F2FF0@@QAEXXZ @ 0x000F43B0
// sp-match: ?sub_F43B0@type_F2FF0@@QAEXXZ @ 0x000BA450
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_F2FF0::sub_F43B0()
{
    RwRaster *bp_8;
    RwUInt32 bp_4;

    bp_4 = 0xB;
    if ((unk_40 & bp_4) == bp_4)
    {
        if (unk_40 & 0x10)
        {
            sub_EFB70(this);
        }
        else
        {
            if (!unk_44->unk_80)
            {
                RwRenderStateSet(rwRENDERSTATESRCBLEND, (void *)rwBLENDSRCALPHA);
                RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void *)rwBLENDINVSRCALPHA);
            }
            else
            {
                RwRenderStateSet(rwRENDERSTATESRCBLEND, (void *)rwBLENDSRCALPHA);
                RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void *)rwBLENDONE);
            }
            if (unk_5C)
            {
                bp_8 = RwTextureGetRaster(unk_5C);
                RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void *)bp_8);
            }
            else
            {
                return;
            }
            sub_19F740(&unk_60, this, unk_44, unk_40);
        }
    }
}
// match: ?sub_F4480@type_F2FF0@@QAEXPAUtype_F2880@@@Z @ 0x000F4480
// sp-match: ?sub_F4480@type_F2FF0@@QAEXPAUtype_F2880@@@Z @ 0x000BA4D0
void type_F2FF0::sub_F4480(type_F2880 *arg_0)
{
    arg_0->unk_00 = get_unk_15C();
    arg_0->unk_04 = 0;
    if (unk_15C)
    {
        get_unk_15C()->unk_04 = arg_0;
    }
    unk_15C = arg_0;
}
// match: ?sub_F44E0@type_F2FF0@@QAEXPAUtype_F2880@@@Z @ 0x000F44E0
// sp-match: ?sub_F44E0@type_F2FF0@@QAEXPAUtype_F2880@@@Z @ 0x000BA500
void type_F2FF0::sub_F44E0(type_F2880 *arg_0)
{
    type_F2880 *var_4;

    var_4 = arg_0->unk_04;
    if (var_4)
    {
        var_4->unk_00 = arg_0->get_unk_00();
    }
    var_4 = arg_0->unk_00;
    if (var_4)
    {
        var_4->unk_04 = arg_0->get_unk_04();
    }
    if (arg_0 == unk_15C)
    {
        unk_15C = arg_0->get_unk_00();
    }
    arg_0->unk_00 = 0;
    arg_0->unk_04 = 0;
}
