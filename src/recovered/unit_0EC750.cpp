// The performance lookups (include/game/data.h: type_ECDA0, type_ED340,
// type_ED850). The original file name is not in the image, so it is named for
// its start address.

#include <stdlib.h>
#include <string.h>

#include "rw/ostypes.h"
#include "rw/bastream.h"
#include "rw/rprandom.h"
#include "game/data.h"
#include "game/functions.h"
#include "types/type_3D3548.h"
#include "types/alfaobject.h"
#include "rw/badevice.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003D8EE8
extern const RwReal flt_3D8EE8 = 16.666666f;
// 0x004B92D4
type_ECDA0 *dword_4B92D4;
// 0x004B92D8
RwReal flt_4B92D8[9];
// 0x004B92FC
type_ED340 *dword_4B92FC;
// 0x004B9300
type_ED850 *dword_4B9300;
// 0x004B9304
type_4B9304 *dword_4B9304;
// End of its data definitions.


// The engine's memory functions' first two slots (include/rw/bamemory.h).

// Frees its data and entries (the data's check comes twice: once more after
// the entries).
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3D8EE8@@3MB @ 0x003D8EE8
// match: __real@420c0000 @ 0x003D8EEC
// match: ?byte_3D8EF0@?1??sub_ED340@type_ED340@@QAEFPAUtype_3D3548@@PAEH_N@Z@4QBCB @ 0x003D8EF0

// match: ??1type_ECDA0@@QAE@XZ @ 0x000EC6D0
// sp-match: ??1type_ECDA0@@QAE@XZ @ 0x000B5140

type_ECDA0::~type_ECDA0()
{
    if (unk_08)
    {
        RwFree(unk_08);
        unk_08 = 0;
    }
    if (unk_04)
    {
        RwFree(unk_04);
        unk_04 = 0;
        unk_00 = 0;
    }
    if (unk_08)
    {
        RwFree(unk_08);
        unk_08 = 0;
    }
}

// match: ?sub_EC750@type_ECDA0@@QAEXPAURwStream@@@Z @ 0x000EC750
// sp-match: ?sub_EC750@type_ECDA0@@QAEXPAURwStream@@@Z @ 0x000B51A0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_ECDA0::sub_EC750(RwStream *arg_0)
{
    RwInt32 lv_10;
    RwInt32 slot_C;
    RwUInt32 bp_8;
    RwUInt32 bp_4;

    if (!RwStreamReadInt32(arg_0, &unk_00, 4))
    {
        return;
    }
    unk_04 = (type_EC750 *)RwMalloc(unk_00 * 0x10, 0x34258); // not an address: an allocation tag
    for (slot_C = 0; slot_C < unk_00; slot_C++)
    {
        bp_8 = RwStreamRead(arg_0, &unk_04[slot_C], 0xC);
    }
    if (!RwStreamReadInt32(arg_0, (RwInt32 *)&bp_4, 4))
    {
        return;
    }
    unk_08 = (RwInt8 *)RwMalloc(bp_4, 0x34258); // not an address: an allocation tag
    bp_8 = RwStreamRead(arg_0, unk_08, bp_4);
    for (slot_C = 0, lv_10 = 0; slot_C < unk_00; slot_C++)
    {
        unk_04[slot_C].unk_0C = unk_08 + lv_10;
        lv_10 += unk_04[slot_C].unk_00;
    }
}

// match: ?sub_EC880@type_EC880@@QAECPAUtype_EC880_00@@M@Z @ 0x000EC880
// sp-match: ?sub_EC880@type_EC880@@QAECPAUtype_EC880_00@@M@Z @ 0x000B5570
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt8 type_EC880::sub_EC880(type_EC880_00 *arg_0, RwReal arg_4)
{
    RwReal slot_C;
    RwInt32 bp_8;
    RwReal bp_4;

    if (arg_0->unk_0C)
    {
        switch (arg_0->unk_0C->vf_160())
        {
        case 4:
            return 3;
        }
    }
#ifdef CODFH_SP
    // shape: the clamps' results used in place, not copied (SP 0xB5570)
    bp_8 = (RwInt8)(sub_22C20(arg_0->unk_28, 0.0f, 35.0f) / 35.0f + sub_22C20(arg_4, 0.0f, 2500.0f) / 2500.0f);
#else
    slot_C = sub_22C20(arg_0->unk_28, 0.0f, 35.0f);
    bp_4 = sub_22C20(arg_4, 0.0f, 2500.0f);
    bp_8 = (RwInt8)(slot_C / 35.0f + bp_4 / 2500.0f);
#endif
    bp_8 = bp_8 + RpRandom() % 3 - 1;
    bp_8 = sub_ECF40(bp_8, 0, 2);
    return (RwInt8)bp_8;
}

// match: ?sub_EC970@type_EC880@@QAECPAUtype_EC880_00@@M@Z @ 0x000EC970
// sp-match: ?sub_EC970@type_EC880@@QAECPAUtype_EC880_00@@M@Z @ 0x000B5650
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt8 type_EC880::sub_EC970(type_EC880_00 *arg_0, RwReal arg_4)
{
    RwReal slot_C;
    RwInt32 bp_8;
    RwReal bp_4;

#ifdef CODFH_SP
    // shape: the clamps' results used in place, not copied (SP 0xB5650)
    bp_8 = (RwInt8)(sub_22C20(arg_0->unk_2C, 0.0f, 35.0f) / 35.0f + sub_22C20(arg_4, 0.0f, 2500.0f) / 2500.0f);
#else
    slot_C = sub_22C20(arg_0->unk_2C, 0.0f, 35.0f);
    bp_4 = sub_22C20(arg_4, 0.0f, 2500.0f);
    bp_8 = (RwInt8)(slot_C / 35.0f + bp_4 / 2500.0f);
#endif
    bp_8 = bp_8 + RpRandom() % 3 - 1;
    bp_8 = sub_ECF40(bp_8, 0, 2);
    return (RwInt8)bp_8;
}

// match: ?sub_ECA40@type_ECDA0@@QAEPAUtype_EC750@@PAUtype_ECA40@@PAU2@@Z @ 0x000ECA40
// sp-match: ?sub_ECA40@type_ECDA0@@QAEPAUtype_EC750@@PAUtype_ECA40@@PAU2@@Z @ 0x000B5270
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
type_EC750 *type_ECDA0::sub_ECA40(type_ECA40 *arg_0, type_EC750 *arg_4)
{
    RwInt32 slot_C;
    RwInt32 bp_8;
    RwInt32 bp_4;

    if (arg_4->unk_00 == 6)
    {
        for (bp_4 = 0; bp_4 < 4; bp_4++)
        {
            if (arg_0->unk_06[bp_4] && arg_0->unk_00[bp_4] != arg_4->unk_0C[bp_4])
            {
                return 0;
            }
        }
        if (arg_0->unk_06[4] && arg_0->unk_00[4] != arg_4->unk_0C[4])
        {
            return 0;
        }
    }
    else
    {
        for (bp_4 = 0, bp_8 = 0; bp_4 < 4; bp_4++)
        {
            for (slot_C = 1; slot_C <= arg_4->unk_0C[bp_8]; slot_C++)
            {
                if (!arg_0->unk_06[bp_4] || arg_0->unk_00[bp_4] == arg_4->unk_0C[bp_8 + slot_C])
                {
                    break;
                }
            }
            if (slot_C > arg_4->unk_0C[bp_8])
            {
                return 0;
            }
            bp_8 = bp_8 + arg_4->unk_0C[bp_8] + 1;
        }
        for (slot_C = 1; slot_C <= arg_4->unk_0C[bp_8]; slot_C++)
        {
            if (!arg_0->unk_06[4] || arg_0->unk_00[4] == arg_4->unk_0C[bp_8 + slot_C])
            {
                break;
            }
        }
        if (slot_C > arg_4->unk_0C[bp_8])
        {
            return 0;
        }
    }
    return arg_4;
}

// match: ?sub_ECBE0@type_ECDA0@@QAEPAUtype_EC750@@PAUtype_ECA40@@PAU2@@Z @ 0x000ECBE0
// sp-match: ?sub_ECBE0@type_ECDA0@@QAEPAUtype_EC750@@PAUtype_ECA40@@PAU2@@Z @ 0x000B5360
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
type_EC750 *type_ECDA0::sub_ECBE0(type_ECA40 *arg_0, type_EC750 *arg_4)
{
    RwInt32 slot_C;
    RwInt32 bp_8;
    RwInt32 bp_4;

    if (arg_4->unk_00 == 6)
    {
        for (bp_4 = 0; bp_4 < 4; bp_4++)
        {
            if (arg_0->unk_06[bp_4] && arg_0->unk_00[bp_4] != arg_4->unk_0C[bp_4])
            {
                return 0;
            }
        }
        if (arg_0->unk_06[5] && arg_0->unk_00[5] != arg_4->unk_0C[5])
        {
            return 0;
        }
    }
    else
    {
        for (bp_4 = 0, bp_8 = 0; bp_4 < 4; bp_4++)
        {
            for (slot_C = 1; slot_C <= arg_4->unk_0C[bp_8]; slot_C++)
            {
                if (!arg_0->unk_06[bp_4] || arg_0->unk_00[bp_4] == arg_4->unk_0C[bp_8 + slot_C])
                {
                    break;
                }
            }
            if (slot_C > arg_4->unk_0C[bp_8])
            {
                return 0;
            }
            bp_8 = bp_8 + arg_4->unk_0C[bp_8] + 1;
        }
        bp_8 = bp_8 + arg_4->unk_0C[bp_8] + 1;
        for (slot_C = 1; slot_C <= arg_4->unk_0C[bp_8]; slot_C++)
        {
            if (!arg_0->unk_06[5] || arg_0->unk_00[5] == arg_4->unk_0C[bp_8 + slot_C])
            {
                break;
            }
        }
        if (slot_C > arg_4->unk_0C[bp_8])
        {
            return 0;
        }
    }
    return arg_4;
}

// match: ?sub_ECDA0@type_ECDA0@@QAEFPAUtype_3D3548@@PAXH_N@Z @ 0x000ECDA0
// sp-match: ?sub_ECDA0@type_ECDA0@@QAEFPAUtype_3D3548@@PAXH_N@Z @ 0x000B5450
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt16 type_ECDA0::sub_ECDA0(type_3D3548 *arg_0, void *arg_4, RwInt32 arg_8, bool arg_C)
{
    type_EC750 *bp_8;
    RwInt32 bp_4;

    bp_8 = 0;
    if (arg_8 == 6)
    {
        for (bp_4 = 0; bp_4 < unk_00; bp_4++)
        {
            bp_8 = sub_ECA40((type_ECA40 *)arg_4, &unk_04[bp_4]);
            if (bp_8)
            {
                break;
            }
        }
        if (!bp_8)
        {
            ((type_ECA40 *)arg_4)->unk_06[0] = 0;
            for (bp_4 = 0; bp_4 < unk_00; bp_4++)
            {
                bp_8 = sub_ECA40((type_ECA40 *)arg_4, &unk_04[bp_4]);
                if (bp_8)
                {
                    break;
                }
            }
        }
    }
    else if (arg_8 == 7)
    {
        for (bp_4 = 0; bp_4 < unk_00; bp_4++)
        {
            bp_8 = sub_ECBE0((type_ECA40 *)arg_4, &unk_04[bp_4]);
            if (bp_8)
            {
                break;
            }
        }
        if (!bp_8)
        {
            ((type_ECA40 *)arg_4)->unk_06[0] = 0;
            for (bp_4 = 0; bp_4 < unk_00; bp_4++)
            {
                bp_8 = sub_ECBE0((type_ECA40 *)arg_4, &unk_04[bp_4]);
                if (bp_8)
                {
                    break;
                }
            }
        }
    }
    else
    {
        return -1;
    }
    if (bp_8)
    {
        arg_8 -= arg_C ? 4 : 6;
        if (bp_8->unk_04[arg_8] != -1)
        {
            return bp_8->unk_04[arg_8];
        }
    }
    return -1;
}

// match: ?sub_ECF40@@YAABHABH00@Z @ 0x000ECF40
// sp-match: ?sub_ECF40@@YAABHABH00@Z @ 0x000B5550
const RwInt32 &sub_ECF40(const RwInt32 &arg_0, const RwInt32 &arg_4, const RwInt32 &arg_8)
{
    if (arg_0 > arg_8)
    {
        return arg_8;
    }
    if (arg_0 < arg_4)
    {
        return arg_4;
    }
    return arg_0;
}

// match: ??1type_ED340@@QAE@XZ @ 0x000ECF70
// sp-match: ??1type_ED340@@QAE@XZ @ 0x000B5720
type_ED340::~type_ED340()
{
    RwUInt32 var_4;

    for (var_4 = 0; var_4 < unk_00; var_4++)
    {
        if (unk_04[var_4].unk_08)
        {
            RwFree(unk_04[var_4].unk_08);
            unk_04[var_4].unk_08 = 0;
        }
    }
    if (unk_04)
    {
        RwFree(unk_04);
        unk_04 = 0;
    }
    if (unk_08)
    {
        RwFree(unk_08);
        unk_08 = 0;
    }
}

// match: ?sub_ED030@type_ED340@@QAEXPAURwStream@@@Z @ 0x000ED030
// sp-match: ?sub_ED030@type_ED340@@QAEXPAURwStream@@@Z @ 0x000B5790
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_ED340::sub_ED030(RwStream *arg_0)
{
    type_ED030_rec lcl_B0;
    RwInt32 ebp_14;
    RwInt32 lv_10;
    RwInt32 slot_C;
    RwInt32 bp_8;
    RwInt32 bp_4;

    if (!RwStreamReadInt32(arg_0, &lv_10, 4))
    {
        return;
    }
    unk_04 = (type_ED030 *)RwMalloc(lv_10 * 0xC, 0x34258); // not an address: an allocation tag
    unk_08 = (type_ED030 *)RwMalloc(lv_10 * 0xC, 0x34258); // not an address: an allocation tag
    unk_00 = lv_10;
    for (slot_C = 0; slot_C < lv_10; slot_C++)
    {
        RwStreamRead(arg_0, &lcl_B0, 0x92);
        for (ebp_14 = 0; ebp_14 < 35; ebp_14++)
        {
            sub_19A750(&lcl_B0.unk_06[ebp_14][0]);
            sub_19A750(&lcl_B0.unk_06[ebp_14][1]);
        }
        for (ebp_14 = 0; ebp_14 < 6; ebp_14++)
        {
            unk_04[slot_C].unk_00[ebp_14] = lcl_B0.unk_00[ebp_14];
        }
        for (ebp_14 = 0, bp_4 = 0; ebp_14 < 35; ebp_14++)
        {
            if (lcl_B0.unk_06[ebp_14][0] != -1)
            {
                bp_4++;
            }
        }
        unk_04[slot_C].unk_08 = (type_ED030_08 *)RwMalloc(bp_4 * 6, 0x34258); // not an address: an allocation tag
        unk_04[slot_C].unk_06 = (RwUInt8)bp_4;
        for (ebp_14 = 0, bp_8 = 0; ebp_14 < 35; ebp_14++)
        {
            if (lcl_B0.unk_06[ebp_14][0] != -1)
            {
                unk_04[slot_C].unk_08[bp_8].unk_00 = lcl_B0.unk_06[ebp_14][0];
                unk_04[slot_C].unk_08[bp_8].unk_02 = lcl_B0.unk_06[ebp_14][1];
                unk_04[slot_C].unk_08[bp_8].unk_04 = (RwInt8)ebp_14;
                bp_8++;
            }
        }
    }
}

// match: ?sub_ED2A0@type_ED340@@QAEXXZ @ 0x000ED2A0
// sp-match: ?sub_ED2A0@type_ED340@@QAEXXZ @ 0x000B5BA0
void type_ED340::sub_ED2A0()
{
    qsort(unk_04, unk_00, 0xC, sub_ED2D0);
}

// match: ?sub_ED2D0@@YAHPBX0@Z @ 0x000ED2D0
// sp-match: ?sub_ED2D0@@YAHPBX0@Z @ 0x000B5A50
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_ED2D0(const void *arg_0, const void *arg_4)
{
    RwInt32 slot_C;
    const RwUInt8 *bp_8;
    const RwUInt8 *bp_4;

    bp_4 = (const RwUInt8 *)arg_0;
    bp_8 = (const RwUInt8 *)arg_4;
    for (slot_C = 0; slot_C < 6; slot_C++)
    {
        if (bp_4[slot_C] < bp_8[slot_C])
        {
            return -1;
        }
        if (bp_4[slot_C] > bp_8[slot_C])
        {
            return 1;
        }
    }
    return 0;
}

// match: ?sub_ED340@type_ED340@@QAEFPAUtype_3D3548@@PAEH_N@Z @ 0x000ED340
// sp-match: ?sub_ED340@type_ED340@@QAEFPAUtype_3D3548@@PAEH_N@Z @ 0x000B5C50
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt16 type_ED340::sub_ED340(type_3D3548 *arg_0, RwUInt8 *arg_4, RwInt32 arg_8, bool arg_C)
{
    // (a static: the image has it after the earlier functions' 35.0f literal)
    static const RwInt8 byte_3D8EF0[3] = { 0x1F, 0x2F, 0x0F };
    RwUInt8 l18[0xC];
    RwInt32 x1C;
    RwInt16 bp_8;
    RwInt32 bp_4;

    memcpy(l18, arg_4, 0xC);
    for (bp_4 = 0; bp_4 < 6; bp_4++)
    {
        if (!l18[6 + bp_4])
        {
            bp_8 = sub_ED460(l18, arg_8, arg_C);
            return bp_8;
        }
    }
    bp_8 = sub_ED530(unk_04, unk_00, l18, arg_8, arg_C);
    bp_4 = 0;
    while (bp_8 == -1 && bp_4 < 3)
    {
        for (x1C = 0; x1C < 6; x1C++)
        {
            l18[6 + x1C] = byte_3D8EF0[bp_4] & (1 << x1C);
        }
        bp_4++;
        bp_8 = sub_ED460(l18, arg_8, arg_C);
    }
    return bp_8;
}

// match: ?sub_ED460@type_ED340@@QAEFPAEH_N@Z @ 0x000ED460
// sp-match: ?sub_ED460@type_ED340@@QAEFPAEH_N@Z @ 0x000B5BC0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt16 type_ED340::sub_ED460(RwUInt8 *arg_0, RwInt32 arg_4, bool arg_8)
{
    RwInt32 bp_8;
    RwInt32 bp_4;

    memcpy(unk_08, unk_04, unk_00 * 0xC);
    for (bp_4 = 0; bp_4 < 6; bp_4++)
    {
        if (!arg_0[6 + bp_4])
        {
            for (bp_8 = 0; bp_8 < unk_00; bp_8++)
            {
                unk_08[bp_8].unk_00[bp_4] = 0;
            }
        }
    }
    qsort(unk_08, unk_00, 0xC, sub_ED2D0);
    return sub_ED530(unk_08, unk_00, arg_0, arg_4, arg_8);
}

// match: ?sub_ED530@type_ED340@@QAEFPAUtype_ED030@@HPAEH_N@Z @ 0x000ED530
// sp-match: ?sub_ED530@type_ED340@@QAEFPAUtype_ED030@@HPAEH_N@Z @ 0x000B5A90
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt16 type_ED340::sub_ED530(type_ED030 *arg_0, RwInt32 arg_4, RwUInt8 *arg_8, RwInt32 arg_C, bool arg_10)
{
    RwUInt8 u14[0xC];
#ifdef CODFH_SP
    // shape: the found entry re-read at each use (SP 0xB5A90 stores and reloads it)
    type_ED030 *volatile bp_18;
#else
    type_ED030 *bp_18;
#endif
    RwInt32 bp_4;

    memcpy(u14, arg_8, 6);
    bp_18 = (type_ED030 *)bsearch(u14, arg_0, arg_4, 0xC, sub_ED2D0);
    if (bp_18 && bp_18->unk_06 >= 1)
    {
        while (arg_C >= 0)
        {
            for (bp_4 = 0; bp_4 < bp_18->unk_06; bp_4++)
            {
                if (bp_18->unk_08[bp_4].unk_04 == arg_C)
                {
                    if (arg_10)
                    {
                        return bp_18->unk_08[bp_4].unk_02;
                    }
                    else
                    {
                        return bp_18->unk_08[bp_4].unk_00;
                    }
                }
            }
            if (arg_C >= 25)
            {
                arg_C = 0;
            }
            else if (arg_C >= 16)
            {
                return -1;
            }
            else if (arg_C > 0)
            {
                if ((arg_C -= 4) < 0)
                {
                    arg_C = 0;
                }
            }
            else
            {
                arg_C = -1;
            }
        }
    }
    return -1;
}

// match: ??0type_ED850@@QAE@XZ @ 0x000ED650
// sp-match: ??0type_ED850@@QAE@XZ @ 0x000B5D50
type_ED850::type_ED850()
{
    unk_00 = 0;
    unk_04 = 0;
}

// match: ??1type_ED850@@QAE@XZ @ 0x000ED680
// sp-match: ??1type_ED850@@QAE@XZ @ 0x000B5D60
type_ED850::~type_ED850()
{
    if (unk_04)
    {
        RwFree(unk_04);
        unk_04 = 0;
    }
}

// match: ?sub_ED6B0@type_ED850@@QAEXPAURwStream@@@Z @ 0x000ED6B0
// sp-match: ?sub_ED6B0@type_ED850@@QAEXPAURwStream@@@Z @ 0x000B5D80
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_ED850::sub_ED6B0(RwStream *arg_0)
{
    RwInt32 slot_C;
    RwInt32 bp_8;
    RwInt32 bp_4;

    if (!RwStreamReadInt32(arg_0, &bp_8, 4))
    {
        return;
    }
    unk_04 = (type_ED6B0 *)RwMalloc(bp_8 * 8, 0x34258); // not an address: an allocation tag
    unk_00 = bp_8;
    for (bp_4 = 0; bp_4 < bp_8; bp_4++)
    {
        RwStreamRead(arg_0, &unk_04[bp_4], 8);
        for (slot_C = 0; slot_C < 2; slot_C++)
        {
            sub_19A750(&unk_04[bp_4].unk_00[slot_C]);
        }
        for (slot_C = 0; slot_C < 2; slot_C++)
        {
            sub_19A750(&unk_04[bp_4].unk_04[slot_C]);
        }
    }
}

// match: ?sub_ED7B0@type_ED850@@QAEXXZ @ 0x000ED7B0
// sp-match: ?sub_ED7B0@type_ED850@@QAEXXZ @ 0x000B5EA0
void type_ED850::sub_ED7B0()
{
    qsort(unk_04, unk_00, 8, sub_ED7E0);
}

// match: ?sub_ED7E0@@YAHPBX0@Z @ 0x000ED7E0
// sp-match: ?sub_ED7E0@@YAHPBX0@Z @ 0x000B5E50
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_ED7E0(const void *arg_0, const void *arg_4)
{
    RwInt32 slot_C;
    const RwInt16 *bp_8;
    const RwInt16 *bp_4;

    bp_4 = (const RwInt16 *)arg_0;
    bp_8 = (const RwInt16 *)arg_4;
    for (slot_C = 0; slot_C < 2; slot_C++)
    {
        if (bp_4[slot_C] < bp_8[slot_C])
        {
            return -1;
        }
        if (bp_4[slot_C] > bp_8[slot_C])
        {
            return 1;
        }
    }
    return 0;
}

// match: ?sub_ED850@type_ED850@@QAEFPAEPAF@Z @ 0x000ED850
// sp-match: ?sub_ED850@type_ED850@@QAEFPAEPAF@Z @ 0x000B5EC0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt16 type_ED850::sub_ED850(RwUInt8 *arg_0, RwInt16 *arg_4)
{
    RwUInt8 r10[8];
    type_ED6B0 *frm_14;
    RwInt32 bp_4;

    for (bp_4 = 0; bp_4 < 2; bp_4++)
    {
        if (!((type_ED850_key *)arg_0)->unk_04[bp_4])
        {
            return sub_ED910(arg_0, arg_4);
        }
    }
    memcpy(r10, arg_0, 4);
    frm_14 = (type_ED6B0 *)bsearch(r10, unk_04, unk_00, 8, sub_ED7E0);
    if (frm_14)
    {
        if (arg_4)
        {
            *arg_4 = frm_14->unk_04[1];
        }
        return frm_14->unk_04[0];
    }
    return -1;
}

// match: ?sub_ED910@type_ED850@@QAEFPAEPAF@Z @ 0x000ED910
// sp-match: ?sub_ED910@type_ED850@@QAEFPAEPAF@Z @ 0x000B5E90
RwInt16 type_ED850::sub_ED910(RwUInt8 *arg_0, RwInt16 *arg_4)
{
    return -1;
}

// match: ??0type_4B9304@@QAE@XZ @ 0x000ED930
// sp-match: ??0type_4B9304@@QAE@XZ @ 0x000B5F60
type_4B9304::type_4B9304()
{
    unk_04 = 0;
    unk_00 = 0;
    unk_0C = 0;
    unk_08 = 0;
    unk_14 = 0;
    unk_10 = 0;
    unk_18 = 0;
}

// match: ??1type_4B9304@@QAE@XZ @ 0x000ED990
// sp-match: ??1type_4B9304@@QAE@XZ @ 0x000B5F80
type_4B9304::~type_4B9304()
{
    if (unk_00)
    {
        RwFree(unk_00);
        unk_00 = 0;
    }
    if (unk_08)
    {
        RwFree(unk_08);
        unk_08 = 0;
    }
    if (unk_10)
    {
        RwFree(unk_10);
        unk_10 = 0;
    }
    if (unk_18)
    {
        RwFree(unk_18);
        unk_18 = 0;
    }
    if (unk_10)
    {
        RwFree(unk_10);
        unk_10 = 0;
    }
}

// match: ?sub_EDA50@type_4B9304@@QAEXPAURwStream@@@Z @ 0x000EDA50
// sp-match: ?sub_EDA50@type_4B9304@@QAEXPAURwStream@@@Z @ 0x000B5FF0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_4B9304::sub_EDA50(RwStream *arg_0)
{
    type_EDA50_sub *q28;
    type_EDA50_sub *frm_24;
    type_EDA50_sub *t20;
    RwInt32 l1C;
    RwInt32 m_18;
    RwInt32 ebp_14;
    RwInt32 lv_10;
    RwInt32 slot_C;
    RwInt32 bp_8;
    RwUInt32 bp_4;

    slot_C = 0;
    if (!RwStreamReadInt32(arg_0, &unk_04, 4))
    {
        return;
    }
    if (!RwStreamReadInt32(arg_0, &unk_0C, 4))
    {
        return;
    }
    if (!RwStreamReadInt32(arg_0, &unk_14, 4))
    {
        return;
    }
    if (!RwStreamReadInt32(arg_0, &ebp_14, 4))
    {
        return;
    }
    if (unk_04)
    {
        unk_00 = (type_EDA50_a **)RwMalloc(unk_04 * 4, 0x34258); // not an address: an allocation tag
    }
    else
    {
        unk_00 = 0;
    }
    if (unk_0C)
    {
        unk_08 = (type_EDA50_b **)RwMalloc(unk_0C * 4, 0x34258); // not an address: an allocation tag
    }
    else
    {
        unk_08 = 0;
    }
    if (unk_14)
    {
        unk_10 = (type_EDA50_a **)RwMalloc(unk_14 * 4, 0x34258); // not an address: an allocation tag
    }
    else
    {
        unk_10 = 0;
    }
    unk_18 = (RwUInt8 *)RwMalloc(ebp_14, 0x34258); // not an address: an allocation tag
    for (bp_8 = 0; bp_8 < unk_04; bp_8++)
    {
        bp_4 = RwStreamRead(arg_0, unk_18 + slot_C, 4);
        unk_00[bp_8] = (type_EDA50_a *)(unk_18 + slot_C);
        slot_C += bp_4;
        for (l1C = 0; l1C < unk_00[bp_8]->unk_02; l1C++)
        {
            bp_4 = RwStreamRead(arg_0, unk_18 + slot_C, 8);
            t20 = (type_EDA50_sub *)(unk_18 + slot_C);
            slot_C = bp_4 + t20->unk_06 * 4 + slot_C;
            for (lv_10 = 0; lv_10 < t20->unk_06; lv_10++)
            {
                t20->unk_08[lv_10] = (type_EDA50_item *)(unk_18 + slot_C);
                bp_4 = RwStreamRead(arg_0, unk_18 + slot_C, 4);
                slot_C += bp_4;
                for (m_18 = 0; m_18 < t20->unk_08[lv_10]->unk_00; m_18++)
                {
                    bp_4 = RwStreamRead(arg_0, unk_18 + slot_C, 4);
                    slot_C += bp_4;
                }
            }
        }
    }
    for (bp_8 = 0; bp_8 < unk_0C; bp_8++)
    {
        bp_4 = RwStreamRead(arg_0, unk_18 + slot_C, 8);
        unk_08[bp_8] = (type_EDA50_b *)(unk_18 + slot_C);
        slot_C += bp_4;
        for (l1C = 0; l1C < unk_08[bp_8]->unk_04; l1C++)
        {
            bp_4 = RwStreamRead(arg_0, unk_18 + slot_C, 8);
            frm_24 = (type_EDA50_sub *)(unk_18 + slot_C);
            slot_C = bp_4 + frm_24->unk_06 * 4 + slot_C;
            for (lv_10 = 0; lv_10 < frm_24->unk_06; lv_10++)
            {
                frm_24->unk_08[lv_10] = (type_EDA50_item *)(unk_18 + slot_C);
                bp_4 = RwStreamRead(arg_0, unk_18 + slot_C, 4);
                slot_C += bp_4;
                for (m_18 = 0; m_18 < frm_24->unk_08[lv_10]->unk_00; m_18++)
                {
                    bp_4 = RwStreamRead(arg_0, unk_18 + slot_C, 4);
                    slot_C += bp_4;
                }
            }
        }
    }
    for (bp_8 = 0; bp_8 < unk_14; bp_8++)
    {
        bp_4 = RwStreamRead(arg_0, unk_18 + slot_C, 4);
        unk_10[bp_8] = (type_EDA50_a *)(unk_18 + slot_C);
        slot_C += bp_4;
        for (l1C = 0; l1C < unk_10[bp_8]->unk_02; l1C++)
        {
            bp_4 = RwStreamRead(arg_0, unk_18 + slot_C, 8);
            q28 = (type_EDA50_sub *)(unk_18 + slot_C);
            slot_C = bp_4 + q28->unk_06 * 4 + slot_C;
            for (lv_10 = 0; lv_10 < q28->unk_06; lv_10++)
            {
                q28->unk_08[lv_10] = (type_EDA50_item *)(unk_18 + slot_C);
                bp_4 = RwStreamRead(arg_0, unk_18 + slot_C, 4);
                slot_C += bp_4;
                for (m_18 = 0; m_18 < q28->unk_08[lv_10]->unk_00; m_18++)
                {
                    bp_4 = RwStreamRead(arg_0, unk_18 + slot_C, 4);
                    slot_C += bp_4;
                }
            }
        }
    }
}

// match: ?sub_EDFE0@type_4B9304@@QAEHFF@Z @ 0x000EDFE0
// sp-match: ?sub_EDFE0@type_4B9304@@QAEHFF@Z @ 0x000B6440
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_4B9304::sub_EDFE0(RwInt16 arg_0, RwInt16 arg_4)
{
    RwInt32 l1C;
    RwInt32 m_18;
    type_EDA50_sub *ebp_14;
    type_EDA50_a *lv_10;
    RwInt32 slot_C;
    RwInt32 bp_8;
    RwInt32 bp_4;

    lv_10 = 0;
    ebp_14 = 0;
    if (!unk_04)
    {
        return 0;
    }
    bp_4 = 0;
    do
    {
        lv_10 = unk_00[bp_4];
    } while (lv_10->unk_00 != arg_0 && ++bp_4 < unk_04);
    if (bp_4 >= unk_04)
    {
        return 0;
    }
    ebp_14 = (type_EDA50_sub *)(unk_00[bp_4] + 1);
    for (bp_4 = 0; bp_4 < lv_10->unk_02; bp_4++)
    {
        for (m_18 = 0; m_18 < 3; m_18++)
        {
            if (ebp_14->unk_00[m_18] == arg_4)
            {
                break;
            }
        }
        if (ebp_14->unk_00[m_18] == arg_4)
        {
            break;
        }
        l1C = ebp_14->unk_06 * 8 + 8;
        for (m_18 = 0; m_18 < ebp_14->unk_06; m_18++)
        {
            l1C = l1C + ebp_14->unk_08[m_18]->unk_00 * 4;
        }
        ebp_14 = RWPLUGINOFFSET(type_EDA50_sub, ebp_14, l1C);
    }
    if (bp_4 == lv_10->unk_02)
    {
        return 0;
    }
    bp_8 = rand() % 100 + 1;
    for (bp_4 = 0, slot_C = 0; bp_4 < ebp_14->unk_06; bp_4++)
    {
        slot_C = ebp_14->unk_08[bp_4]->unk_02 + slot_C;
        if (bp_8 <= slot_C)
        {
            return (RwInt32)ebp_14->unk_08[bp_4];
        }
    }
    return 0;
}

// match: ?sub_EE1A0@type_4B9304@@QAEHHF@Z @ 0x000EE1A0
// sp-match: ?sub_EE1A0@type_4B9304@@QAEHHF@Z @ 0x000B6520
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_4B9304::sub_EE1A0(RwInt32 arg_0, RwInt16 arg_4)
{
    RwInt32 l1C;
    RwInt32 m_18;
    type_EDA50_sub *ebp_14;
    type_EDA50_b *lv_10;
    RwInt32 slot_C;
    RwInt32 bp_8;
    RwInt32 bp_4;

    lv_10 = 0;
    ebp_14 = 0;
    if (!unk_0C)
    {
        return 0;
    }
    bp_4 = 0;
    do
    {
        lv_10 = unk_08[bp_4];
        bp_4++;
    } while (lv_10->unk_00 != arg_0 && bp_4 < unk_0C);
    if (bp_4 >= unk_0C)
    {
        return 0;
    }
    ebp_14 = (type_EDA50_sub *)(unk_08[bp_4] + 1);
    for (bp_4 = 0; bp_4 < lv_10->unk_04; bp_4++)
    {
        for (m_18 = 0; m_18 < 3; m_18++)
        {
            if (ebp_14->unk_00[m_18] == arg_4)
            {
                break;
            }
        }
        if (ebp_14->unk_00[m_18] == arg_4)
        {
            break;
        }
        l1C = ebp_14->unk_06 * 8 + 8;
        for (m_18 = 0; m_18 < ebp_14->unk_06; m_18++)
        {
            l1C = l1C + ebp_14->unk_08[m_18]->unk_00 * 4;
        }
        ebp_14 = RWPLUGINOFFSET(type_EDA50_sub, ebp_14, l1C);
    }
    if (bp_4 == lv_10->unk_04)
    {
        return 0;
    }
    bp_8 = rand() % 100 + 1;
    for (bp_4 = 0, slot_C = 0; bp_4 < ebp_14->unk_06; bp_4++)
    {
        slot_C = ebp_14->unk_08[bp_4]->unk_02 + slot_C;
        if (bp_8 <= slot_C)
        {
            return (RwInt32)ebp_14->unk_08[bp_4];
        }
    }
    return 0;
}

// match: ?sub_EE360@type_4B9304@@QAEHCCC@Z @ 0x000EE360
// sp-match: ?sub_EE360@type_4B9304@@QAEHCCC@Z @ 0x000B6600
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_4B9304::sub_EE360(RwInt8 arg_0, RwInt8 arg_4, RwInt8 arg_8)
{
    RwInt32 l1C;
    RwInt32 m_18;
    type_EDA50_sub *ebp_14;
    type_EDA50_a *lv_10;
    RwInt32 slot_C;
    RwInt32 bp_8;
    RwInt32 bp_4;

    lv_10 = 0;
    ebp_14 = 0;
    if (!unk_14)
    {
        return 0;
    }
    bp_4 = 0;
    do
    {
        lv_10 = unk_10[bp_4];
    } while (lv_10->unk_00 != (arg_0 | arg_4 << 8) && ++bp_4 < unk_14);
    if (bp_4 >= unk_14)
    {
        bp_4 = 0;
        do
        {
            lv_10 = unk_10[bp_4];
        } while ((lv_10->unk_00 & 0xFF) != arg_0 && ++bp_4 < unk_14);
    }
    if (bp_4 >= unk_14)
    {
        return 0;
    }
    ebp_14 = (type_EDA50_sub *)(unk_10[bp_4] + 1);
    for (bp_4 = 0; bp_4 < lv_10->unk_02; bp_4++)
    {
        if ((ebp_14->unk_00[0] & 0xFF) == arg_8)
        {
            break;
        }
        l1C = ebp_14->unk_06 * 8 + 8;
        for (m_18 = 0; m_18 < ebp_14->unk_06; m_18++)
        {
            l1C = l1C + ebp_14->unk_08[m_18]->unk_00 * 4;
        }
        ebp_14 = RWPLUGINOFFSET(type_EDA50_sub, ebp_14, l1C);
    }
    if (bp_4 == lv_10->unk_02)
    {
        return 0;
    }
    bp_8 = rand() % 100 + 1;
    for (bp_4 = 0, slot_C = 0; bp_4 < ebp_14->unk_06; bp_4++)
    {
        slot_C = ebp_14->unk_08[bp_4]->unk_02 + slot_C;
        if (bp_8 <= slot_C)
        {
            return (RwInt32)ebp_14->unk_08[bp_4];
        }
    }
    return 0;
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??0type_ECDA0@@QAE@XZ (folded into 0x1EE9E0)
type_ECDA0::type_ECDA0()
{
    unk_00 = 0;
    unk_04 = 0;
    unk_08 = 0;
}

// ??0type_ED340@@QAE@XZ (folded into 0x1EE9E0)
// sp-match: ??0type_ED340@@QAE@XZ @ 0x000B5710
type_ED340::type_ED340()
{
    unk_00 = 0;
    unk_04 = 0;
    unk_08 = 0;
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?sub_19A750@@YAXPAF@Z (folded into 0x19A750)
#ifndef CODFH_SP
// Single player keeps the calls (SP 0xB5790, 0xB5D80): the empty body is
// not defined here, or /O2 drops them.
void sub_19A750(RwInt16 * arg_0)
{
}
#endif
