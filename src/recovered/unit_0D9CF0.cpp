// The saves: the memory card (type_D9CF0, a stub on this build) and the
// save record (type_DA0A0). The original file name is not in the image, so
// it is named for its start address.

#include <string.h>

#include "rw/ostypes.h"
#include "game/data.h"
#include "game/functions.h"
#include "types/type_DA0A0.h"
#include "game/gameloop.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x004292B0
RwInt32 dword_4292B0 = -1;
// 0x004292B4
type_4292B4 unk_4292B4 = { 0, 0, 1.0f, 2 };
// 0x004B88AC
RwInt32 dword_4B88AC;
// End of its data definitions.


// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_06NPAAKFED@Player?$AA@ @ 0x003D7E78
// match: ?dword_4292B0@@3HA @ 0x004292B0
// match: ?unk_4292B4@@3Utype_4292B4@@A @ 0x004292B4

// match: ?sub_D9CF0@type_D9CF0@@QAE_NHH@Z @ 0x000D9CF0

bool type_D9CF0::sub_D9CF0(RwInt32 arg_0, RwInt32 arg_4)
{
    RwInt32 var_4;

    dword_4B8970 = 1.225f;
    dword_4B88AC = 0;
    if (sub_1A1790(0))
    {
        var_4 = sub_1A1D40();
    }
    return true;
}

// match: ?sub_D9D30@type_D9CF0@@QAEHXZ @ 0x000D9D30
// sp-match: ?sub_D9D30@type_D9CF0@@QAEHXZ @ 0x000A4A50
RwInt32 type_D9CF0::sub_D9D30()
{
    RwInt32 var_4;

    var_4 = 0;
    unk_08 = var_4;
    if (var_4)
    {
        unk_00 = -1;
    }
    return var_4;
}

// match: ?sub_D9D60@type_D9CF0@@QAE_NPAHPAY0M@D@Z @ 0x000D9D60
// sp-match: ?sub_D9D60@type_D9CF0@@QAE_NPAHPAY0M@D@Z @ 0x000A4A60
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
bool type_D9CF0::sub_D9D60(RwInt32 *arg_0, RwChar (*arg_4)[12])
{
    RwInt32 var_14;
    RwInt32 lv_10;
    type_4F5DC4_04 *var_C;
    RwInt32 bp_8;
    bool var_1;

    var_1 = false;
    arg_4[0][0] = arg_4[1][0] = arg_4[2][0] = arg_4[3][0] = 0;
    for (var_14 = 0; var_14 < 4; var_14++)
    {
        bp_8 = dword_4F5DC4[var_14].unk_00;
        lv_10 = dword_4F6158[var_14];
        if (lv_10 || bp_8)
        {
            var_1 = true;
            arg_0[var_14] = 0;
            var_C = &dword_4F5DC4[var_14].unk_04;
            if (lv_10)
            {
                sub_1A1BB0(arg_4[var_14], var_14);
            }
            else
            {
                strcpy(arg_4[var_14], var_C->unk_10);
            }
        }
        else
        {
            arg_0[var_14] = 1;
        }
    }
    return var_1;
}

// match: ?sub_D9E50@type_D9CF0@@QAEHH@Z @ 0x000D9E50
// sp-match: ?sub_D9E50@type_D9CF0@@QAEHH@Z @ 0x000A4E50
RwInt32 type_D9CF0::sub_D9E50(RwInt32 arg_0)
{
    type_DA0A0 var_D0;
    RwInt32 var_D4;

    var_D4 = 0;
    sub_D9EC0(&var_D0);
    sub_1A26B0(arg_0);
    sub_1A1820(&var_D0, arg_0);
    return var_D4;
}

// match: ?sub_D9EC0@@YAXPAUtype_DA0A0@@@Z @ 0x000D9EC0
// sp-match: ?sub_D9EC0@@YAXPAUtype_DA0A0@@@Z @ 0x000A4B10
void sub_D9EC0(type_DA0A0 *arg_0)
{
    type_DA0A0 *var_4;

    {
        RwInt32 var_8;          // never used; the image's frame keeps its slot
    }
    arg_0->sub_DA0A0();
    if (sub_19B050() == dword_4F28F0->get_unk_54())
    {
        arg_0->unk_0C = (RwUInt16)sub_19B050();
        arg_0->unk_64.sub_19AC40(&dword_4F28F0->unk_5C);
    }
    else
    {
        var_4 = &dword_4F28F0->unk_B8;
        arg_0->unk_0C = var_4->unk_0C;
        arg_0->unk_64 = var_4->unk_64;
    }
    arg_0->unk_00 = 0x434F4431;
    arg_0->unk_04 = 0x101;
    arg_0->unk_08 = 0xC8;
    arg_0->unk_0E = (RwUInt16)dword_4F28F0->get_unk_54();
    strcpy(arg_0->unk_10, dword_4F28F0->unk_48);
    arg_0->unk_20.unk_00 = dword_4F28F0->get_unk_14();
    arg_0->unk_20.unk_04 = dword_4F28F0->get_unk_18();
    arg_0->unk_20.unk_08 = dword_4F28F0->get_unk_1C();
    arg_0->unk_20.unk_0C = dword_4F28F0->get_unk_21();
    arg_0->unk_20.unk_0D = dword_4F28F0->get_unk_22();
    arg_0->unk_20.unk_0E = dword_4F28F0->get_unk_20();
    arg_0->unk_20.unk_0F = dword_4F28F0->get_unk_28();
    arg_0->unk_20.unk_10 = dword_4F28F0->unk_180 != 0;
    arg_0->unk_20.unk_11 = dword_4F28F0->unk_181 != 0;
    arg_0->unk_20.unk_14 = sub_19B080();
    arg_0->unk_20.unk_18 = dword_4F28F0->unk_30;
    arg_0->unk_20.unk_1C = dword_4F28F0->unk_2C;
    strcpy(arg_0->unk_20.unk_20, dword_4F28F0->unk_183);
    arg_0->unk_1C = arg_0->sub_19ABA0();
}

#ifdef CODFH_SP
#include "sp/sp_launch.h"
void sp_sub_1291D0(RwInt32 arg_0);

// Loads slot arg_0's save into the save state (the reverse of sub_D9EC0);
// 0.
// sp-match: ?sp_sub_A4CA0@type_D9CF0@@QAEHH@Z @ 0x000A4CA0
RwInt32 type_D9CF0::sp_sub_A4CA0(RwInt32 arg_0)
{
    type_DA0A0 rec;

    rec.unk_64.clear();
    rec = dword_4F5DC0[arg_0].unk_08;
    sub_1A26B0(arg_0);
    dword_4F28F0->unk_B8 = rec;
    dword_4F28F0->unk_54 = rec.unk_0E;
    if (!((sp_type_3EC3B0 *)dword_4F45F8)->unk_18)
    {
        sub_19B000(rec.unk_0C);
    }
    else
    {
        sub_19B000(((sp_type_3EC3B0 *)dword_4F45F8)->unk_1C);
    }
    rec.unk_10[11] = 0;
    strcpy(dword_4F28F0->unk_48, rec.unk_10);
    dword_4F28F0->unk_14 = rec.unk_20.unk_00;
    dword_4F28F0->unk_18 = rec.unk_20.unk_04;
    dword_4F28F0->unk_1C = rec.unk_20.unk_08;
    dword_4F28F0->unk_21 = rec.unk_20.unk_0C;
    dword_4F28F0->unk_22 = rec.unk_20.unk_0D;
    dword_4F28F0->unk_20 = rec.unk_20.unk_0E;
    dword_4F28F0->unk_28 = rec.unk_20.unk_0F;
    dword_4F28F0->unk_180 = rec.unk_20.unk_10;
    dword_4F28F0->unk_181 = rec.unk_20.unk_11;
    sp_sub_1291D0(rec.unk_20.unk_14);
    strcpy(dword_4F28F0->unk_183, rec.unk_20.unk_20);
    dword_4F28F0->unk_30 = rec.unk_20.unk_18;
    dword_4F28F0->unk_2C = rec.unk_20.unk_1C;
    dword_4F28F0->unk_5C = rec.unk_64.unk_00;
    return 0;
}
#endif

#ifndef CODFH_SP // single player has both inline (include/types/type_DA0A0.h)
// match: ?sub_DA0A0@type_DA0A0@@QAEXXZ @ 0x000DA0A0
void type_DA0A0::sub_DA0A0()
{
    RwInt32 var_4;              // never used; the image's frame keeps their
    RwInt32 var_8;              // slots
    RwInt32 var_C;

    sub_DA0F0(0xC8);
    unk_20.sub_DA150();
    unk_64.clear();
}

// match: ?sub_DA0F0@type_DA0A0@@QAEXH@Z @ 0x000DA0F0
void type_DA0A0::sub_DA0F0(RwInt32 arg_0)
{
    unk_00 = 0x434F4431;
    unk_04 = 0x101;
    arg_0 = arg_0;
    unk_0C = 1;
    unk_0E = 1;
    memset(unk_10, 0, 0xC);
    unk_1C = 0;
}

#endif

#ifndef CODFH_SP // single player has it inline (include/types/type_DA0A0.h)
// match: ?sub_DA150@type_DA150@@QAEXXZ @ 0x000DA150
// sp-match: ?sub_DA150@type_DA150@@QAEXXZ @ 0x000A4980
// (type_DA0A0_64::clear, an inline single player keeps out of line: sub_D9EC0 and SP 0x1290C3 call it)
// sp-match: ?clear@type_DA0A0_64@@QAEXXZ @ 0x000A49F0
void type_DA150::sub_DA150()
{
    unk_00 = 1;
    unk_04 = 1;
    unk_08 = 0;
    unk_0C = 1;
    unk_0D = 0;
    unk_0E = 1;
    unk_0F = 1;
    unk_10 = 1;
    unk_11 = 1;
    unk_14 = 1;
    unk_18 = 0;
    unk_1C = 0;
    memset(unk_20, 0, 0x20);
    strcpy(unk_20, "Player");
    memset(unk_40, 0, 2);
}
#endif

// match: ?sub_DA200@type_D9CF0@@QAEHXZ @ 0x000DA200
RwInt32 type_D9CF0::sub_DA200()
{
    RwInt32 var_4;

    var_4 = 0;
    return var_4;
}

// match: ?sub_DA220@type_D9CF0@@QAEHXZ @ 0x000DA220
// sp-match: ?sub_DA220@type_D9CF0@@QAEHXZ @ 0x000A4E30
RwInt32 type_D9CF0::sub_DA220()
{
    return dword_4292B0;
}

// match: ?sub_DA230@type_D9CF0@@QAE_NXZ @ 0x000DA230
// sp-match: ?sub_DA230@type_D9CF0@@QAE_NXZ @ 0x000A4EA0
bool type_D9CF0::sub_DA230()
{
    RwInt32 var_4;

    var_4 = unk_04;
    if (var_4 >= sub_DA280())
    {
        return true;
    }
    return sub_DA220() + unk_04 >= sub_DA280();
}

// match: ?sub_DA280@type_D9CF0@@QAEHXZ @ 0x000DA280
// sp-match: ?sub_DA280@type_D9CF0@@QAEHXZ @ 0x000A4E40
RwInt32 type_D9CF0::sub_DA280()
{
    return 0xC8;
}

// Members /OPT:ICF folded into shared trivial bodies (config/aliases.txt): defined here for
// the authentic link (PLAN M7); the placement link takes the shared bodies.

// ?pDtor@type_D9CF0@@QAEXXZ (folded into the empty body at 0x1E41C0)
void type_D9CF0::pDtor()
{
}
