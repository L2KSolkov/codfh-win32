// The spline paths' table and the animated textures (type_143DC0) with their
// manager (unk_4E5CC8).

#include "rw/ostypes.h"
#include "rw/rpmaterial.h"
#include "types/type_143DC0.h"
#include "types/SplinePath.h"
#include "game/gameloop.h"
#include "rw/rt2d.h"
#include "game/functions.h"
#include "rw/babintex.h"
#include "types/type_141C10.h"
#include <string.h>

// Its data definitions (PLAN M5), in the image's address order.
// 0x00429CD0
const RwChar *off_429CD0[12] = {
    "PUT_PPSH41",
    "PUT_MP40",
    "KarBack",
    "KarFront",
    "PPSHBack",
    "PPSHFront",
    "PUT_RGD33",
    "VT_Jeep_back",
    "VT_Jeep_front",
    "VT_Jeep_side",
    "test5_LF",
    "aCobbles",
};

// match: ??_C@_08BFDCGGIN@aCobbles?$AA@ @ 0x003DB8FC
// match: ??_C@_08EEINOGBD@test5_LF?$AA@ @ 0x003DB908
// match: ??_C@_0N@DEAAFAJM@VT_Jeep_side?$AA@ @ 0x003DB914
// match: ??_C@_0O@CNKBDOJG@VT_Jeep_front?$AA@ @ 0x003DB924
// match: ??_C@_0N@DHPIPNEK@VT_Jeep_back?$AA@ @ 0x003DB934
// match: ??_C@_09PEPAKNKM@PUT_RGD33?$AA@ @ 0x003DB944
// match: ??_C@_09ELDCHINP@PPSHFront?$AA@ @ 0x003DB950
// match: ??_C@_08KCIFHOJA@PPSHBack?$AA@ @ 0x003DB95C
// match: ??_C@_08BCMLPAPP@KarFront?$AA@ @ 0x003DB968
// match: ??_C@_07OIDAEJOM@KarBack?$AA@ @ 0x003DB974
// match: ??_C@_08MLGKMIOG@PUT_MP40?$AA@ @ 0x003DB97C
// match: ??_C@_0L@PLDEEBFM@PUT_PPSH41?$AA@ @ 0x003DB988
// match: ?off_429CD0@@3PAPBDA @ 0x00429CD0
// 0x004CFA18
SplinePath *dword_4CFA18[0x100];
// 0x004CFE18
RwInt32 dword_4CFE18;
// 0x004CFE1C
RwUInt32 dword_4CFE1C;
// 0x004CFE20
RwInt32 dword_4CFE20;
// 0x004CFE24
RwInt32 dword_4CFE24;
// 0x004CFE28
RwTexDictionary *object;
// End of its data definitions.


// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: __ehhandler$??0type_143DC0@@QAE@XZ>1>8 @ 0x0041DBE8
// match: __ehhandler$??0type_143DC0@@QAE@XZ>1 @ 0x0041DBF8
// match: __ehhandler$??1type_143DC0@@QAE@XZ>1>8 @ 0x0041DC14
// match: __ehhandler$??1type_143DC0@@QAE@XZ>1 @ 0x0041DC2C
// match: __ehhandler$?sub_143F60@type_143DC0@@QAEXXZ>1>8 @ 0x0041DC48
// match: __ehhandler$?sub_143F60@type_143DC0@@QAEXXZ>1 @ 0x0041DC50
// match: __ehhandler$?sub_144110@type_143DC0@@QAEXPAURpMaterial@@H@Z>1>8 @ 0x0041DC6C
// match: __ehhandler$?sub_144110@type_143DC0@@QAEXPAURpMaterial@@H@Z>1 @ 0x0041DC74
// match: __ehhandler$?sub_1441A0@type_143DC0@@QAEPAUtype_143D90@@PAURpMaterial@@H@Z>1>8 @ 0x0041DC90
// match: __ehhandler$?sub_1441A0@type_143DC0@@QAEPAUtype_143D90@@PAURpMaterial@@H@Z>1 @ 0x0041DC98

// match: sub_143CE0 @ 0x00143CE0
// sp-match: sub_143CE0 @ 0x000EF570

void sub_143CE0()
{
    RwInt32 var_4;

    dword_4CFE20 = 0;
    dword_4CFE18 = 1;
    dword_4CFE1C = 0;
    for (var_4 = 0; var_4 < 0x100; var_4++)
        dword_4CFA18[var_4] = 0;
}

// match: sub_143D40 @ 0x00143D40
// sp-match: sub_143D40 @ 0x000EF5A0
void sub_143D40()
{
    if (dword_4CFE18)
        dword_4CFE18 = 0;
}

// match: sub_143D60 @ 0x00143D60
// sp-match: sub_143D60 @ 0x000EF5C0
RwUInt32 sub_143D60(SplinePath *arg_0)
{
    dword_4CFA18[dword_4CFE1C] = arg_0;
    dword_4CFE1C++;
    return dword_4CFE1C - 1;
}

// match: ??0type_143D90@@QAE@PAURpMaterial@@H@Z @ 0x00143D90
// sp-match: ??0type_143D90@@QAE@PAURpMaterial@@H@Z @ 0x000EF5E0
type_143D90::type_143D90(RpMaterial *arg_0, RwInt32 arg_4)
{
    unk_08 = arg_0;
    unk_0C = arg_4;
}

// match: ??0type_143DC0@@QAE@XZ @ 0x00143DC0
// match: __ehhandler$??0type_143DC0@@QAE@XZ-0x13 @ 0x003019D0
// match: __ehhandler$??0type_143DC0@@QAE@XZ @ 0x003019E3
// sp-match: ??0type_143DC0@@QAE@XZ @ 0x000EF8F0
type_143DC0::type_143DC0() : unk_28(0), unk_2C(0x3C)
{
    sub_143F10();
}

// match: ??1type_143DC0@@QAE@XZ @ 0x00143E30
// match: __ehhandler$??1type_143DC0@@QAE@XZ-0x1B @ 0x003019F0
// match: __ehhandler$??1type_143DC0@@QAE@XZ @ 0x00301A0B
// sp-match: ??1type_143DC0@@QAE@XZ @ 0x000EF950
// Deletes the material entries.
type_143DC0::~type_143DC0()
{
    for (type_16B900 var_14(&unk_34); var_14.sub_16B9D0(); var_14.sub_16BA10(0))
        delete (type_143D90 *)var_14.sub_16B990();
}

// match: ?sub_143F10@type_143DC0@@QAEXXZ @ 0x00143F10
// sp-match: ?sub_143F10@type_143DC0@@QAEXXZ @ 0x000EF600
// Empties it: no textures, steps or materials, one step a second.
void type_143DC0::sub_143F10()
{
    unk_28 = 0;
    unk_30 = 0;
    unk_2C = 1;
    unk_104 = 0;
    unk_80 = 0;
    unk_34.sub_16B830();
}

// match: ?sub_143F60@type_143DC0@@QAEXXZ @ 0x00143F60
// match: __ehhandler$?sub_143F60@type_143DC0@@QAEXXZ-0x8 @ 0x00301A20
// match: __ehhandler$?sub_143F60@type_143DC0@@QAEXXZ @ 0x00301A28
// sp-match: ?sub_143F60@type_143DC0@@QAEXXZ @ 0x000EF630
// Each frame: every 60 / unk_2C frames the next step's texture goes on each
// material still referenced.
void type_143DC0::sub_143F60()
{
    unk_28++;
    if (unk_28 > 60 / unk_2C)
    {
        unk_28 = 0;
        unk_30++;
        if (unk_30 >= unk_104)
            unk_30 = 0;
        for (type_16B900 var_14(&unk_34); var_14.sub_16B9D0(); var_14.sub_16BA10(0))
        {
            RpMaterial *var_18;

            var_18 = ((type_143D90 *)var_14.sub_1E3480())->sub_FB710();
            if (var_18 && var_18->refCount)
                RpMaterialSetTexture(var_18, unk_40[unk_84[unk_30]]);
        }
    }
}

// match: ?sub_144070@type_143DC0@@QAEXPAURwTexture@@@Z @ 0x00144070
// sp-match: ?sub_144070@type_143DC0@@QAEXPAURwTexture@@@Z @ 0x000EF720
void type_143DC0::sub_144070(RwTexture *arg_0)
{
    if (unk_80 < 0x10)
    {
        unk_40[unk_80] = arg_0;
        unk_80++;
    }
}

// match: ?sub_1440C0@type_143DC0@@QAEXH@Z @ 0x001440C0
// sp-match: ?sub_1440C0@type_143DC0@@QAEXH@Z @ 0x000EF740
void type_143DC0::sub_1440C0(RwInt32 arg_0)
{
    if (unk_104 < 0x20 && arg_0 < 0x10)
    {
        unk_84[unk_104] = arg_0;
        unk_104++;
    }
}

// match: ?sub_144110@type_143DC0@@QAEXPAURpMaterial@@H@Z @ 0x00144110
// match: __ehhandler$?sub_144110@type_143DC0@@QAEXPAURpMaterial@@H@Z-0xB @ 0x00301A40
// match: __ehhandler$?sub_144110@type_143DC0@@QAEXPAURpMaterial@@H@Z @ 0x00301A4B
// sp-match: ?sub_144110@type_143DC0@@QAEXPAURpMaterial@@H@Z @ 0x000EF770
void type_143DC0::sub_144110(RpMaterial *arg_0, RwInt32 arg_4)
{
    type_143D90 *var_10;

    var_10 = new type_143D90(arg_0, arg_4);
    if (var_10)
        unk_34.sub_16B860(var_10);
}

// match: ?sub_1441A0@type_143DC0@@QAEPAUtype_143D90@@PAURpMaterial@@H@Z @ 0x001441A0
// sp-match: ?sub_1441A0@type_143DC0@@QAEPAUtype_143D90@@PAURpMaterial@@H@Z @ 0x000EF7E0
type_143D90 *type_143DC0::sub_1441A0(RpMaterial *arg_0, RwInt32 arg_4)
{
    for (type_16B900 var_14(&unk_34); var_14.sub_16B9D0(); var_14.sub_16BA10(0))
    {
        type_143D90 *var_18;

        var_18 = (type_143D90 *)var_14.sub_1E3480();
        if (var_18->sub_FB710() == arg_0 && var_18->sub_6CB40() == arg_4)
            return var_18;
    }
    return 0;
}

// match: ?sub_144260@type_143DC0@@QAEXPBD@Z @ 0x00144260
// sp-match: ?sub_144260@type_143DC0@@QAEXPBD@Z @ 0x000EF8C0
void type_143DC0::sub_144260(const RwChar *arg_0)
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 0x1F; var_4++)
    {
        if (arg_0[var_4])
            unk_08[var_4] = arg_0[var_4];
        else
            break;
    }
    unk_08[var_4] = 0;
}














// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?sub_6CB40@type_143D90@@QAEHXZ (folded into 0x6CB40)
RwInt32 type_143D90::sub_6CB40()
{
    return unk_0C;
}

// ?sub_FB710@type_143D90@@QAEPAURpMaterial@@XZ (folded into 0xFB710)
#ifndef CODFH_SP
// Single player calls it as another file's (SP 0xEF7E0 reloads ecx after
// the call): the body is multiplayer-only here.
struct RpMaterial * type_143D90::sub_FB710()
{
    return unk_08;
}
#endif
