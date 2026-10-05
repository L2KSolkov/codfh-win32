/*
 * kujuUI's static image (\COD\SHARED\UI\cStaticImage.cpp, game/kujuui.h):
 * its traces name the class and its focus and event handlers, which only
 * report being called (level 3); and its creator ("image").
 */
#include "game/kujuui.h"
#include "game/assert.h"
#include "game/parsedfile.h"

namespace kujuUI {

// match: ??0cStaticImage@kujuUI@@QAE@PBDPBUtype_1E0330_rect@1@PAUtype_3E7D08@1@@Z @ 0x001F00E0
cStaticImage::cStaticImage(const RwChar *arg_0, const type_1E0330_rect *arg_4, type_3E7D08 *arg_8)
    : type_3E76B4(arg_0, arg_4, arg_8)
{
}

// match: ??_GcStaticImage@kujuUI@@UAEPAXI@Z @ 0x001F0130

// match: ??1cStaticImage@kujuUI@@UAE@XZ @ 0x001F0160
cStaticImage::~cStaticImage()
{
}

// match: ?givenFocus@cStaticImage@kujuUI@@UAEXXZ @ 0x001F0190
void cStaticImage::givenFocus()
{
#line 46 "\\COD\\SHARED\\UI\\cStaticImage.cpp"
    sub_1C7F20(false, __FILE__, __LINE__, __FUNCSIG__, 3);
}

// match: ?lostFocus@cStaticImage@kujuUI@@UAEXXZ @ 0x001F01C0
void cStaticImage::lostFocus()
{
#line 52 "\\COD\\SHARED\\UI\\cStaticImage.cpp"
    sub_1C7F20(false, __FILE__, __LINE__, __FUNCSIG__, 3);
}

// match: ?processEvent@cStaticImage@kujuUI@@UAE?AW4eEventWasHandled@2@ABVcStateChange@2@@Z @ 0x001F01F0
eEventWasHandled cStaticImage::processEvent(const cStateChange &arg_0)
{
#line 71 "\\COD\\SHARED\\UI\\cStaticImage.cpp"
    sub_1C7F20(false, __FILE__, __LINE__, __FUNCSIG__, 3);
    return (eEventWasHandled)1;
}

// match: ??_EcStaticImage@kujuUI@@WM@AEPAXI@Z @ 0x001F0220

// match: ??0type_3E7830@kujuUI@@QAE@XZ @ 0x001F0230
type_3E7830::type_3E7830()
{
}

// match: ??_Gtype_3E7830@kujuUI@@UAEPAXI@Z @ 0x001F0250

// match: ??1type_3E7830@kujuUI@@UAE@XZ @ 0x001F0280
type_3E7830::~type_3E7830()
{
}

// match: ?vf_004@type_3E7830@kujuUI@@UAEPBDXZ @ 0x001F02A0
const RwChar *type_3E7830::vf_004()
{
    return "image";
}

// match: ?vf_008@type_3E7830@kujuUI@@UAEXPAUtype_1C8DF0@2@HHPAUtype_1ED670@2@PAUtype_3E7D08@2@PAPAU52@@Z @ 0x001F02B0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3E7830::vf_008(type_1C8DF0 *arg_0, RwInt32 arg_4, RwInt32 arg_8, type_1ED670 *arg_C, type_3E7D08 *arg_10,
                         type_3E7D08 **arg_14)
{
    type_1E0330_rect var_20(0, 0, 0, 0);
    const RwChar *lv_10;

    if (sub_1F7D80(arg_0, arg_4, &lv_10) == 1 && sub_1F7B10(arg_0, lv_10, &var_20) == 1)
    {
        *arg_14 = new cStaticImage(lv_10, &var_20, arg_10);
        sub_1F7CC0(arg_0, arg_C, static_cast<type_3E76B4 *>(*arg_14));
        sub_1F7DB0(arg_0, arg_C, static_cast<type_3E76B4 *>(*arg_14));
    }
}

// match: ?vf_00C@type_3E7830@kujuUI@@UAEXPAVcScopeValidator@2@@Z @ 0x001F03F0
void type_3E7830::vf_00C(cScopeValidator *arg_0)
{
    arg_0->sub_1CA1A0(sub_1E3700());
}
}
