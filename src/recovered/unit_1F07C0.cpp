/*
 * kujuUI's text button (game/kujuui.h): a button showing a text it is the
 * source of, and its creator ("textbutton").
 */
#include "game/kujuui.h"
#include "game/parsedfile.h"
#include "types/type_4D1DB8.h"

namespace kujuUI {

// Vtables (.rdata, PLAN M5): each in its own placement range (config/splits.txt).
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_7type_3E79B4@kujuUI@@6B@ @ 0x003E7990
// match: ??_7type_3E79B4@kujuUI@@6Btype_3E76E4@1@@ @ 0x003E799C
// match: ??_7type_3E79B4@kujuUI@@6Btype_3E75E8@1@@ @ 0x003E79A0
// match: ??_7type_3E79B4@kujuUI@@6Btype_3E7D08@1@@ @ 0x003E79B4
// match: __ehhandler$??0type_3E79B4@kujuUI@@QAE@PBDPBUtype_1E0330_rect@1@_NPAUtype_1ED670_object@1@33ABUtype_1A5EA0@@PAUtype_1F28C0@1@HIPAUtype_3E7D08@1@@Z>1>8 @ 0x00420C0C
// match: __ehhandler$??0type_3E79B4@kujuUI@@QAE@PBDPBUtype_1E0330_rect@1@_NPAUtype_1ED670_object@1@33ABUtype_1A5EA0@@PAUtype_1F28C0@1@HIPAUtype_3E7D08@1@@Z>1 @ 0x00420C24
// match: __ehhandler$??1type_3E79B4@kujuUI@@UAE@XZ>1>8 @ 0x00420C40
// match: __ehhandler$??1type_3E79B4@kujuUI@@UAE@XZ>1 @ 0x00420C50

// match: ??0type_3E79B4@kujuUI@@QAE@PBDPBUtype_1E0330_rect@1@_NPAUtype_1ED670_object@1@33ABUtype_1A5EA0@@PAUtype_1F28C0@1@HIPAUtype_3E7D08@1@@Z @ 0x001F07C0
// match: __ehhandler$??0type_3E79B4@kujuUI@@QAE@PBDPBUtype_1E0330_rect@1@_NPAUtype_1ED670_object@1@33ABUtype_1A5EA0@@PAUtype_1F28C0@1@HIPAUtype_3E7D08@1@@Z-0x1E @ 0x003042C0
// match: __ehhandler$??0type_3E79B4@kujuUI@@QAE@PBDPBUtype_1E0330_rect@1@_NPAUtype_1ED670_object@1@33ABUtype_1A5EA0@@PAUtype_1F28C0@1@HIPAUtype_3E7D08@1@@Z @ 0x003042DE

type_3E79B4::type_3E79B4(const RwChar *arg_0, const type_1E0330_rect *arg_4, bool arg_8, type_1ED670_object *arg_C,
                         type_1ED670_object *arg_10, type_1ED670_object *arg_14, const type_1A5EA0 &arg_18,
                         type_1F28C0 *arg_1C, RwInt32 arg_20, RwUInt32 arg_24, type_3E7D08 *arg_28)
    : type_3E6D70(arg_0, arg_4, arg_8, arg_C, arg_10, arg_14, arg_28), unk_30(arg_20, arg_4, arg_24, true)
{
    if (arg_1C)
    {
        arg_1C->sub_1E7540(this);
        pvf_008(arg_1C->unk_08);
    }
    else
        pvf_008(arg_18);
}

// match: ??_Gtype_3E79B4@kujuUI@@UAEPAXI@Z @ 0x001F08D0

// match: ??1type_3E79B4@kujuUI@@UAE@XZ @ 0x001F0900
// match: __ehhandler$??1type_3E79B4@kujuUI@@UAE@XZ-0x2F @ 0x003042F0
// match: __ehhandler$??1type_3E79B4@kujuUI@@UAE@XZ @ 0x0030431F
type_3E79B4::~type_3E79B4()
{
}

// match: ?vf_008@type_3E79B4@kujuUI@@UAEXXZ @ 0x001F09A0
void type_3E79B4::vf_008()
{
    unk_30.sub_1F1AA0();
    type_3E6D70::vf_008();
}

// match: ?vf_00C@type_3E79B4@kujuUI@@UAEXXZ @ 0x001F09C0
void type_3E79B4::vf_00C()
{
    unk_30.sub_1F1AD0();
    type_3E6D70::vf_00C();
}

// match: ?vf_018@type_3E79B4@kujuUI@@UAEXPAUtype_1E4130@2@@Z @ 0x001F09E0
void type_3E79B4::vf_018(type_1E4130 *arg_0)
{
    if (!pvf_00C())
    {
        type_3E76B4::vf_018(arg_0);
        unk_30.sub_1F1B10(arg_0);
    }
}

// match: ?vf_014@type_3E79B4@kujuUI@@UAEXM@Z @ 0x001F0A20
void type_3E79B4::vf_014(RwReal arg_0)
{
    type_3E6D70::vf_014(arg_0);
    unk_30.sub_1F1E00(sub_1EFFC0());
}

// match: ?pvf_008@type_3E79B4@kujuUI@@UAEXPBUtype_1E0330_rect@2@@Z @ 0x001F0A50
void type_3E79B4::pvf_008(const type_1E0330_rect *arg_0)
{
    type_3E76B4::pvf_008(arg_0);
    static_cast<type_3E75E8 &>(unk_30).pvf_008(arg_0);
}

// match: ?pvf_008@type_3E79B4@kujuUI@@UAEXABUtype_1A5EA0@@@Z @ 0x001F0A80
void type_3E79B4::pvf_008(const type_1A5EA0 &arg_0)
{
    unk_30.sub_1F1D10(arg_0);
    static_cast<type_3E75E8 &>(unk_30).pvf_008(static_cast<type_3E76B4 *>(this)->pvf_004());
}

// match: ??_Etype_3E79B4@kujuUI@@WM@AEPAXI@Z @ 0x001F0AC0

// match: ??_Etype_3E79B4@kujuUI@@WCM@AEPAXI@Z @ 0x001F0AD0






}
