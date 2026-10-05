/*
 * kujuUI's list box's rows, its creator ("listbox") and its columns
 * (game/kujuui.h).
 */
#include "game/kujuui.h"
#include "game/parsedfile.h"
#include "types/type_4D1DB8.h"

namespace kujuUI {

// Vtables (.rdata, PLAN M5): each in its own placement range (config/splits.txt).
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_7type_3E74C0@kujuUI@@6B@ @ 0x003E74C0
// match: __ehhandler$?sub_1EBFA0@type_3E74C0@kujuUI@@QAEXPAUtype_3E7490@2@@Z>1>8 @ 0x00420614
// match: __ehhandler$?sub_1EBFA0@type_3E74C0@kujuUI@@QAEXPAUtype_3E7490@2@@Z>1 @ 0x00420624

// match: ??0type_3E74C0@kujuUI@@QAE@XZ @ 0x001EBE50

type_3E74C0::type_3E74C0()
{
    unk_3C = 0;
}

// match: ??_Gtype_3E74C0@kujuUI@@UAEPAXI@Z @ 0x001EBE90

// match: ??1type_3E74C0@kujuUI@@UAE@XZ @ 0x001EBEC0
type_3E74C0::~type_3E74C0()
{
    if (sub_1EC230())
        unk_3C->sub_1EAB50(this);
}

// match: ?sub_1EBF00@type_3E74C0@kujuUI@@QAEXXZ @ 0x001EBF00
void type_3E74C0::sub_1EBF00()
{
    for (RwUInt32 var_4 = 0; var_4 < unk_3C->sub_1EB090(); ++var_4)
        (*unk_28.at(var_4))->sub_1F1AA0();
}

// match: ?sub_1EBF50@type_3E74C0@kujuUI@@QAEXXZ @ 0x001EBF50
void type_3E74C0::sub_1EBF50()
{
    for (RwUInt32 var_4 = 0; var_4 < unk_3C->sub_1EB090(); ++var_4)
        (*unk_28.at(var_4))->sub_1F1AD0();
}

// match: ?sub_1EBFA0@type_3E74C0@kujuUI@@QAEXPAUtype_3E7490@2@@Z @ 0x001EBFA0
// match: __ehhandler$?sub_1EBFA0@type_3E74C0@kujuUI@@QAEXPAUtype_3E7490@2@@Z-0x16 @ 0x00303E90
// match: __ehhandler$?sub_1EBFA0@type_3E74C0@kujuUI@@QAEXPAUtype_3E7490@2@@Z @ 0x00303EA6
void type_3E74C0::sub_1EBFA0(type_3E7490 *arg_0)
{
    unk_3C = arg_0;
    type_1E0330_rect var_1C(0, 0, 10.0f, 10.0f);
    for (RwUInt32 var_20 = 0; var_20 < unk_3C->sub_1EB090(); ++var_20)
    {
        *unk_14.next() = new type_1E37A0(unk_3C->sub_190360());
        *unk_28.next() = new type_1F1420(unk_3C->sub_1EAC10(), &var_1C, unk_3C->sub_1EB110(var_20), true);
        (*unk_28.back())->sub_1F2410(0);
    }
    vf_004();
}

// match: ?sub_1EC110@type_3E74C0@kujuUI@@QAEXXZ @ 0x001EC110
void type_3E74C0::sub_1EC110()
{
    for (::type_1E61A0_it<type_1E37A0 *, 4> var_8 = unk_14.begin(); var_8.ne(unk_14.end()); var_8.inc())
        delete *var_8.get();
    unk_14.clear();
    for (::type_1E61A0_it<type_1F1420 *, 4> var_10 = unk_28.begin(); var_10.ne(unk_28.end()); var_10.inc())
        delete *var_10.get();
    unk_28.clear();
    unk_3C = 0;
}

// match: ?sub_1EC230@type_3E74C0@kujuUI@@QAE_NXZ @ 0x001EC230
bool type_3E74C0::sub_1EC230()
{
    return unk_3C != 0;
}

// match: ?sub_1EC250@type_3E74C0@kujuUI@@QAEXH@Z @ 0x001EC250
void type_3E74C0::sub_1EC250(RwInt32 arg_0)
{
    for (RwUInt32 var_4 = 0; var_4 < unk_3C->sub_1EB090(); ++var_4)
    {
        (*unk_28.at(var_4))->sub_1F1E00(arg_0);
        (*unk_14.at(var_4))->sub_1E3B20(arg_0);
    }
}

// match: ?sub_1EC2C0@type_3E74C0@kujuUI@@QAEXABUtype_1A5EA0@@I@Z @ 0x001EC2C0
void type_3E74C0::sub_1EC2C0(const type_1A5EA0 &arg_0, RwUInt32 arg_4)
{
    type_1F1420 *var_4 = *unk_28.at(arg_4);
    var_4->sub_1F1D10(arg_0);
}

// match: ?sub_1EC2F0@type_3E74C0@kujuUI@@QAEXPAUtype_1E4130@2@@Z @ 0x001EC2F0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3E74C0::sub_1EC2F0(type_1E4130 *arg_0)
{
    for (RwUInt32 var_4 = 0; var_4 < unk_3C->sub_1EB090(); ++var_4)
    {
        type_1F1420 *var_8 = *unk_28.at(var_4);
        type_1E37A0 *local_C = *unk_14.at(var_4);
        local_C->sub_1E3950(arg_0);
        var_8->sub_1F1B10(arg_0);
    }
}

// match: ?sub_1EC370@type_3E74C0@kujuUI@@QAEXPBUtype_1E0330_rect@2@I@Z @ 0x001EC370
void type_3E74C0::sub_1EC370(const type_1E0330_rect *arg_0, RwUInt32 arg_4)
{
    type_1F1420 *var_4 = *unk_28.at(arg_4);
    var_4->sub_1F20E0(unk_3C->sub_1EB110(arg_4));
    var_4->pvf_008(arg_0);
    (*unk_14.at(arg_4))->sub_1E3A30(arg_0);
}















// The array template's members this unit instantiates first.
// match: ?next@?$type_1E61A0@PAUtype_1E37A0@kujuUI@@$03@@QAEPAPAUtype_1E37A0@kujuUI@@XZ @ 0x001EC3E0
// match: ?clear@?$type_1E61A0@PAUtype_1E37A0@kujuUI@@$03@@QAEXXZ @ 0x001EC420
// match: ?back@?$type_1E61A0@PAUtype_1F1420@kujuUI@@$03@@QAEPAPAUtype_1F1420@kujuUI@@XZ @ 0x001EC470
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?sub_FB710@type_1ECA30@kujuUI@@QAEIXZ (folded into 0xFB710)
RwUInt32 kujuUI::type_1ECA30::sub_FB710()
{
    return unk_08;
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?sub_1E3480@type_1ECA30@kujuUI@@QAEPAUtype_3E7490@2@XZ (folded into 0x1E3480)
struct kujuUI::type_3E7490 * kujuUI::type_1ECA30::sub_1E3480()
{
    return unk_04;
}
