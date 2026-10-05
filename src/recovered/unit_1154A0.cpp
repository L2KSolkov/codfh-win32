// The player's inventory (type_10F710_21B4, types/type_10F710.h): its counts
// of the kinds 1 to 12, the kind selected, using one and taking a pickup,
// and the HUD's count. The original file name is not in the image, so it is
// named for its start address.

#include <stdio.h>

#include "rw/ostypes.h"
#include "types/type_3D3548.h"
#include "types/type_10F710.h"
#include "types/type_3DF8D8.h"
#include "types/type_3D94B8.h"
#include "types/type_DA0A0.h"
#include "types/type_DC400.h"
#include "types/soundbank.h"
#include "types/CGlobalSounds.h"
#include "game/functions.h"
#include "game/data.h"
#include "game/textmanager.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x00429B40
RwReal flt_429B40 = 1.0f;
// 0x00429B44
RwReal flt_429B44 = 0.01f;
// 0x00429B48
// Not referenced by name: one object (a lone zero global would be .bss).
RwUInt32 unk_429B48[7] = { 0x0, 0xC1200000 /* -10.0f */, 0x42A00000 /* 80.0f */, 0x3E4CCCCD /* 0.2f */, 0x451C4000 /* 2500.0f */, 0x42700000 /* 60.0f */, 0x41200000 /* 10.0f */ };
// End of its data definitions.


// A pickup's rounds scale for the difficulty (flt_4F2884 by dword_42B714; 1
// out of range): an inline with no address and so no database name, named
// for the table. Evidence: sub_1159C0 keeps it in a temporary of its own
// each time.
inline RwReal get_4F2884()
{
    if (dword_42B714 > -1 && dword_42B714 < 3)
    {
        return flt_4F2884[dword_42B714];
    }
    return 1.0f;
}

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_429B40@@3MA @ 0x00429B40
// match: ?flt_429B44@@3MA @ 0x00429B44
// match: ?unk_429B48@@3PAIA @ 0x00429B48

// match: ?sub_1154A0@type_10F710_21B4@@QAEHXZ @ 0x001154A0

// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_10F710_21B4::sub_1154A0()
{
    RwInt32 bp_8;
    RwInt32 bp_4;

    bp_4 = 1;
    flt_429B40 = 1.0f;
    unk_38 = 0;
    for (bp_8 = 0; bp_8 < 13; bp_8++)
    {
        unk_00[bp_8] = 0;
    }
    unk_34 = 0;
    return bp_4;
}

// match: ?sub_115500@type_10F710_21B4@@QAEHXZ @ 0x00115500
RwInt32 type_10F710_21B4::sub_115500()
{
    RwInt32 var_4;

    var_4 = 1;
    return var_4;
}

// match: ?sub_115520@type_10F710_21B4@@QAEXM@Z @ 0x00115520
void type_10F710_21B4::sub_115520(RwReal arg_0)
{
    RwChar var_48[0x40];

    if (unk_34 && unk_34 != -1)
    {
        sprintf(var_48, "%d", unk_00[unk_34]);
        sub_EAB80(var_48, 4);
        flt_429B40 += flt_429B44 * arg_0;
    }
    else
    {
        sub_EAB80("", 4);
        flt_429B40 -= flt_429B44 * arg_0;
    }
    if (flt_429B40 > 1.0f)
    {
        flt_429B40 = 1.0f;
    }
    else if (flt_429B40 < 0.0f)
    {
        flt_429B40 = 0.0f;
    }
    dword_4B9190->sub_E3B90(0x14, flt_429B40);
}

// match: ?sub_115620@type_10F710_21B4@@QAEHXZ @ 0x00115620
RwInt32 type_10F710_21B4::sub_115620()
{
    if (sub_116270())
    {
        do
        {
            unk_34++;
            if (unk_34 > 12)
            {
                unk_34 = 1;
            }
        } while (!unk_00[unk_34]);
    }
    else
    {
        unk_34 = 0;
    }
    if (unk_34 == 1)
    {
        return sub_115620();
    }
    return unk_34;
}

// match: ?sub_115690@type_10F710_21B4@@QAEXMH@Z @ 0x00115690
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_10F710_21B4::sub_115690(RwReal arg_0, RwInt32 arg_4)
{
    RwChar slot_28[0x20];
    type_10F710 *bp_4;

    if (arg_4 == -1)
    {
        arg_4 = unk_34;
    }
    if (!unk_00[arg_4])
    {
        return;
    }
    bp_4 = (type_10F710 *)sub_1745A0(0);
    if (!bp_4)
    {
        return;
    }
    switch (arg_4)
    {
    case 1:
    {
        type_3DF8D8_04 *stk_2C;
        RwReal frm_30;

        frm_30 = bp_4->vf_17C();
        if (frm_30 != 1.0f)
        {
            if (frm_30 > 0.0f && bp_4->unk_19D0 != 10)
            {
                bp_4->sub_1150A0(sub_104420() * 0.5f);
                dword_4B1E98.sub_8A980(&dword_4B1B38, 0, 0, (RwV3d *)bp_4->vf_0C4(), 1, 0);
                unk_00[arg_4]--;
            }
        }
        else
        {
            type_3DF8D8_04 var_38;

            var_38.unk_00 = 0x38A4A286; // not an address: a key
            var_38.unk_04 = 0x5E1FD9E7; // not an address: a key
            stk_2C = sub_17C630();
            if (!stk_2C || (stk_2C && stk_2C->unk_00 != var_38.unk_00))
            {
                sub_17C6C0(1);
                sub_17C500(&var_38, 1, 1);
            }
            bp_4->vf_23C(1.0f);
        }
        sprintf(slot_28, "%d", sub_1E3BF0(1));
        sub_EAB80(slot_28, 7);
        break;
    }
    case 2:
    case 5:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    {
        RwChar m_78[0x40];

        if (!bp_4->unk_1B1C && !bp_4->unk_1A0C && !bp_4->unk_1B2C)
        {
            if (bp_4->unk_1B04)
            {
                bp_4->unk_1B04 = 0;
                bp_4->unk_1B08 = 1;
                bp_4->unk_1A48[bp_4->unk_1AE4]->unk_298 -= 1.0f;
            }
            bp_4->sub_108BC0(arg_4, arg_0);
            unk_00[arg_4]--;
            sprintf(m_78, "%d", unk_00[arg_4]);
            sub_EAB80(m_78, 3);
        }
        break;
    }
    }
    if (arg_4 != 1)
    {
        sub_115980(arg_4);
    }
    if (!unk_00[arg_4])
    {
        RwInt32 r7C;

        r7C = sub_115620();
        if (r7C)
        {
            sub_115980(r7C);
        }
    }
}

// match: ?sub_115980@type_10F710_21B4@@QAEXH@Z @ 0x00115980
void type_10F710_21B4::sub_115980(RwInt32 arg_0)
{
    unk_34 = arg_0;
    if (dword_4B9190)
    {
        dword_4B9190->sub_E09D0(unk_34);
    }
}

// match: ?sub_1159C0@type_10F710_21B4@@QAEHPAUtype_3D94B8@@@Z @ 0x001159C0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_10F710_21B4::sub_1159C0(type_3D94B8 *arg_0)
{
    RwInt32 frm_54;
    RwChar s50[0x20];
    RwInt32 fp_2C;
    type_10F710 *q28;
    RwInt32 frm_24;
    RwInt32 t20;
    type_10F710 *l1C;
    RwInt32 m_18;
    RwInt32 ebp_14;
    RwInt32 lv_10;
    RwInt32 slot_C;
    RwInt32 bp_8;
    type_4C19C0 *bp_4;

    m_18 = sub_116270();
    frm_24 = -1;
    ebp_14 = arg_0->unk_3B0.sub_FB710();
    slot_C = -1;
    l1C = (type_10F710 *)sub_1745A0(0);
    bp_8 = -1;
    lv_10 = 0;
    if (!l1C)
    {
        return frm_24;
    }
    switch (ebp_14)
    {
    case 0x4B:
    case 0x4C:
    case 0x5A:
    case 0x5B:
        q28 = (type_10F710 *)sub_1745A0(0);
        if (q28 && q28->vf_17C() > 0.0f && q28->unk_19D0 != 10)
        {
            q28->sub_1150A0(sub_104420() * 0.25f);
            dword_4B1E98.sub_8A980(&dword_4B1B38, 0, 0, (RwV3d *)q28->vf_0C4(), 1, 0);
            frm_24 = 1;
        }
        break;
    case 0x4D:
        unk_00[1]++;
        frm_24 = unk_00[1];
        fp_2C = 0;
        switch (dword_42B714)
        {
        case 0:
            fp_2C = 6;
            break;
        case 1:
            fp_2C = 4;
            break;
        default:
            fp_2C = 2;
        }
        if (unk_00[1] > fp_2C)
        {
            unk_00[1] = fp_2C;
        }
        sprintf(s50, "%d", sub_1E3BF0(1));
        sub_EAB80(s50, 7);
        break;
    case 0x4E:
    case 0x4F:
        bp_8 = 0x14;
        slot_C = 8;
        lv_10 = 1;
        break;
    case 0x50:
    case 0x51:
        bp_8 = 0x15;
        slot_C = 2;
        lv_10 = 1;
        break;
    case 0x52:
    case 0x53:
        bp_8 = 0x1F;
        slot_C = 5;
        lv_10 = 1;
        break;
    case 0x54:
    case 0x55:
        bp_8 = 0x16;
        slot_C = 9;
        lv_10 = 1;
        break;
    case 0x56:
    case 0x57:
        bp_8 = 0x21;
        slot_C = 7;
        lv_10 = 1;
        break;
    case 0x58:
    case 0x59:
        bp_8 = 0x13;
        slot_C = 0xA;
        lv_10 = 1;
        break;
    case 0x6C:
        bp_8 = 0x22;
        slot_C = 0xB;
        lv_10 = 1;
        break;
    case 0x6D:
        bp_8 = 0x26;
        slot_C = 0xC;
        lv_10 = 1;
        break;
    case 0x12:
    case 0x13:
    case 0x14:
        bp_8 = 0xB;
        break;
    case 0x15:
    case 0x16:
    case 0x17:
        bp_8 = 8;
        break;
    case 0x18:
    case 0x19:
    case 0x1A:
        bp_8 = 0xA;
        break;
    case 0x1B:
    case 0x1C:
    case 0x1D:
        bp_8 = 7;
        break;
    case 0x1E:
    case 0x1F:
    case 0x20:
        bp_8 = 9;
        break;
    case 0x21:
    case 0x22:
    case 0x23:
        bp_8 = 2;
        break;
    case 0x24:
    case 0x25:
    case 0x26:
        bp_8 = 4;
        break;
    case 0x27:
    case 0x28:
    case 0x29:
        bp_8 = 6;
        break;
    case 0x2A:
    case 0x2B:
    case 0x2C:
        bp_8 = 3;
        break;
    case 0x2D:
    case 0x2E:
    case 0x2F:
        bp_8 = 5;
        break;
    case 0x30:
    case 0x31:
    case 0x32:
        bp_8 = 0xE;
        break;
    case 0x36:
    case 0x37:
    case 0x38:
        bp_8 = 0xF;
        break;
    case 0x39:
    case 0x3A:
    case 0x3B:
        bp_8 = 0x12;
        break;
    case 0x3C:
    case 0x3D:
    case 0x3E:
        bp_8 = 0;
        break;
    case 0x3F:
    case 0x40:
    case 0x41:
        bp_8 = 1;
        break;
    case 0x42:
    case 0x43:
    case 0x44:
        bp_8 = -1;
        break;
    case 0x45:
    case 0x46:
    case 0x47:
        bp_8 = -1;
        break;
    case 0x48:
    case 0x49:
    case 0x4A:
        bp_8 = -1;
        break;
    case 0x5D:
    case 0x5E:
        bp_8 = 0xC;
        break;
    case 0x60:
    case 0x61:
        bp_8 = 0xD;
        break;
    case 0x33:
    case 0x34:
    case 0x35:
    case 0x63:
    case 0x64:
        bp_8 = 0x10;
        break;
    case 0x66:
    case 0x67:
        bp_8 = 0x11;
        break;
    case 0x69:
    case 0x6A:
        bp_8 = 0x25;
        break;
    }
    if (lv_10)
    {
        frm_54 = unk_00[slot_C];
        bp_4 = l1C->unk_1A48[bp_8]->unk_448;
        t20 = bp_4->unk_CC;
        if (frm_54 == t20)
        {
            frm_24 = -1;
        }
        else
        {
            frm_54 += (RwInt32)(arg_0->unk_3B0.unk_04
                                * get_4F2884());
            if (frm_54 > t20)
            {
                frm_54 = t20;
            }
            frm_24 = unk_00[slot_C];
        }
        unk_00[slot_C] = frm_54;
    }
    else if (bp_8 != -1)
    {
        l1C->unk_1A48[bp_8]->unk_418 +=
            (RwInt32)(arg_0->unk_3B0.unk_04
                      * get_4F2884());
        if (l1C->unk_1A48[bp_8]->unk_418 > l1C->unk_1A48[bp_8]->get_unk_448()->unk_CC)
        {
            l1C->unk_1A48[bp_8]->unk_418 = l1C->unk_1A48[bp_8]->get_unk_448()->unk_CC;
        }
        if (bp_8 == l1C->unk_1AE4)
        {
            dword_4B9190->sub_E07A0(l1C->unk_1A48[bp_8]->unk_414,
                                    l1C->unk_1A48[bp_8]->get_unk_448()->unk_C8);
        }
        if (l1C->unk_1AE4 == bp_8 && !l1C->unk_1A48[l1C->unk_1AE4]->unk_414)
        {
            l1C->unk_1A48[l1C->unk_1AE4]->vf_020();
        }
        frm_24 = 0xD;
    }
    if (!m_18 && sub_116270() && dword_4B9190)
    {
        dword_4B9190->sub_E09D0(sub_115620());
    }
    return frm_24;
}

// match: ?sub_116080@type_10F710_21B4@@QAEHHH@Z @ 0x00116080
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_10F710_21B4::sub_116080(RwInt32 arg_0, RwInt32 arg_4)
{
    RwChar local_38[0x20];
    RwInt32 m_18;
    RwChar ebp_14[0x8];
    RwInt32 bp_8;
    type_4C19C0 *bp_4;

    unk_00[arg_0] += arg_4;
    if (arg_0 == 2 || arg_0 == 3 || arg_0 == 5 || arg_0 == 7 || arg_0 == 0xB || arg_0 == 0xC || arg_0 == 8
        || arg_0 == 9 || arg_0 == 0xA)
    {
        bp_8 = -1;
        switch (arg_0)
        {
        case 2:
            bp_8 = 0x15;
            break;
        case 5:
            bp_8 = 0x1F;
            break;
        case 7:
            bp_8 = 0x21;
            break;
        case 11:
            bp_8 = 0x22;
            break;
        case 12:
            bp_8 = 0x26;
            break;
        case 8:
            bp_8 = 0x14;
            break;
        case 9:
            bp_8 = 0x16;
            break;
        case 10:
            bp_8 = 0x13;
            break;
        }
        if (bp_8 != -1)
        {
            bp_4 = ((type_10F710 *)sub_1745A0(0))->unk_1A48[bp_8]->get_unk_448();
            m_18 = bp_4->unk_CC;
            if (unk_00[arg_0] > m_18)
            {
                unk_00[arg_0] = m_18;
            }
        }
        sprintf(ebp_14, "%d", arg_4);
        sub_EAB80(ebp_14, 3);
    }
    else if (arg_0 != 1)
    {
        dword_4B9190->sub_E09D0(arg_0);
        sub_115980(arg_0);
    }
    else
    {
        sprintf(local_38, "%d", sub_1E3BF0(1));
        sub_EAB80(local_38, 7);
        dword_4B9190->sub_E07D0();
    }
    return unk_00[arg_0];
}

// match: ?sub_116270@type_10F710_21B4@@QAEHXZ @ 0x00116270
RwInt32 type_10F710_21B4::sub_116270()
{
    RwInt32 var_4;

    for (var_4 = 1; var_4 <= 12; var_4++)
    {
        if (unk_00[var_4] && var_4 != 1)
        {
            return 1;
        }
    }
    return 0;
}

// match: ?sub_1162C0@type_10F710_21B4@@QAEXPAUtype_D90B0_18@@@Z @ 0x001162C0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_10F710_21B4::sub_1162C0(type_D90B0_18 *arg_0)
{
    RwInt32 bp_8;
    RwUInt32 bp_4;

    bp_8 = unk_34;
    arg_0->unk_00 = bp_8;
    for (bp_4 = 0; bp_4 < 13; bp_4++)
    {
        arg_0->unk_04[bp_4] = unk_00[bp_4];
    }
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??0type_10F710_21B4@@QAE@XZ (folded into 0x6FCD0)
type_10F710_21B4::type_10F710_21B4()
{
    
}

// ??1type_10F710_21B4@@QAE@XZ (folded into 0x1E41C0)
type_10F710_21B4::~type_10F710_21B4()
{
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?sub_1E3BF0@type_10F710_21B4@@QAEHH@Z (folded into 0x1E3BF0)
RwInt32 type_10F710_21B4::sub_1E3BF0(RwInt32 arg_0)
{
    return unk_00[arg_0];
}
