/*
 * kujuUI's button (game/kujuui.h): the widget named "button" and its
 * creator, which finds its action and focus hooks by id (the template
 * lookups sub_1E0CB0 and type_1ED670::sub_1E0D50 are instantiated here).
 */
#include "game/kujuui.h"
#include "game/fileio.h"
#include "game/frontend.h"
#include "game/parsedfile.h"
#include "types/type_4D1DB8.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003E6D54
// (unreferenced: the image has it first in this object's data, before its vtables)
extern const RwInt32 dword_3E6D54 = 3;
// End of its data definitions.

namespace kujuUI {

// Vtables (.rdata, PLAN M5): each in its own placement range (config/splits.txt).
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?dword_3E6D54@@3HB @ 0x003E6D54
// match: ??_7type_3E6D70@kujuUI@@6Btype_3E76E4@1@@ @ 0x003E6D58
// match: ??_7type_3E6D70@kujuUI@@6Btype_3E75E8@1@@ @ 0x003E6D5C
// match: ??_7type_3E6D70@kujuUI@@6Btype_3E7D08@1@@ @ 0x003E6D70

// match: ??0type_3E6D70@kujuUI@@QAE@PBDPBUtype_1E0330_rect@1@_NPAUtype_1ED670_object@1@33PAUtype_3E7D08@1@@Z @ 0x001E0670

type_3E6D70::type_3E6D70(const RwChar *arg_0, const type_1E0330_rect *arg_4, bool arg_8, type_1ED670_object *arg_C,
                         type_1ED670_object *arg_10, type_1ED670_object *arg_14, type_3E7D08 *arg_18)
    : type_3E76B4(arg_0, arg_4, arg_18)
{
    unk_1C = arg_C;
    unk_20 = arg_10;
    unk_24 = arg_14;
    unk_28 = arg_8;
}

// match: ??_Gtype_3E6D70@kujuUI@@UAEPAXI@Z @ 0x001E06E0

// match: ??1type_3E6D70@kujuUI@@UAE@XZ @ 0x001E0710
type_3E6D70::~type_3E6D70()
{
}

// match: ?givenFocus@type_3E6D70@kujuUI@@UAEXXZ @ 0x001E0740
void type_3E6D70::givenFocus()
{
    if (unk_20)
        unk_20->pvf_008();
}

// match: ?lostFocus@type_3E6D70@kujuUI@@UAEXXZ @ 0x001E0770
void type_3E6D70::lostFocus()
{
    if (unk_24)
        unk_24->pvf_008();
}

// match: ?vf_014@type_3E6D70@kujuUI@@UAEXM@Z @ 0x001E07A0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3E6D70::vf_014(RwReal arg_0)
{
    bool var_9;
    RwInt32 bp_8;
    bool var_1;

    var_9 = sub_1F7720();
    var_1 = (bool)!sub_1E0930();
    bp_8 = 6;
    if (var_1)
    {
        if (var_9)
            bp_8 = 4;
        else
            bp_8 = 3;
    }
    else if (var_9)
    {
        if (sub_1EFFC0() == 5)
            bp_8 = 5;
        else
            bp_8 = 1;
    }
    else
        bp_8 = 0;
    sub_1EFFA0(bp_8);
}

// match: ?processEvent@type_3E6D70@kujuUI@@UAE?AW4eEventWasHandled@2@ABVcStateChange@2@@Z @ 0x001E0840
eEventWasHandled type_3E6D70::processEvent(const cStateChange &arg_0)
{
    RwInt32 var_4 = 1;

    switch (arg_0.get_unk_00())
    {
    case 4:
        if (unk_1C && sub_1EFFC0() != 3)
        {
            if (arg_0.get_unk_04() == 0)
            {
                sub_1EFFA0(5);
                if (dword_504378)
                    dword_504378->vf_04(2);
            }
            else if (sub_1EFFC0() == 5)
            {
                unk_1C->pvf_008();
                sub_1EFFA0(1);
            }
        }
        var_4 = 0;
        break;
    }
    return (eEventWasHandled)var_4;
}

// match: ?vf_010@type_3E6D70@kujuUI@@UAE_NXZ @ 0x001E08F0
bool type_3E6D70::vf_010()
{
    return unk_28 || sub_1E0930();
}

// match: ?sub_1E0930@type_3E6D70@kujuUI@@QAE_NXZ @ 0x001E0930
bool type_3E6D70::sub_1E0930()
{
    return unk_1C && unk_1C->pvf_00C() && !pvf_00C();
}

// match: ??_Etype_3E6D70@kujuUI@@WM@AEPAXI@Z @ 0x001E0990








}
