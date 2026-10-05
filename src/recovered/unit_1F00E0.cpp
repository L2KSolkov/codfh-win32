/*
 * kujuUI's static image (\COD\SHARED\UI\cStaticImage.cpp, game/kujuui.h):
 * its traces name the class and its focus and event handlers, which only
 * report being called (level 3); and its creator ("image").
 */
#include "game/kujuui.h"
#include "game/assert.h"
#include "game/parsedfile.h"

namespace kujuUI {

// Vtables (.rdata, PLAN M5): each in its own placement range (config/splits.txt).
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_7cStaticImage@kujuUI@@6Btype_3E76E4@1@@ @ 0x003E76E8
// match: ??_7cStaticImage@kujuUI@@6Btype_3E75E8@1@@ @ 0x003E76EC
// match: ??_7cStaticImage@kujuUI@@6Btype_3E7D08@1@@ @ 0x003E7700
// match: ??_C@_0CA@FPBJGCCD@?2COD?2SHARED?2UI?2cStaticImage?4cpp?$AA@ @ 0x003E7730
// match: ??_C@_0DH@ILNNBHCM@void?5__thiscall?5kujuUI?3?3cStaticI@ @ 0x003E7750
// match: ??_C@_0DG@EGKJKCBD@void?5__thiscall?5kujuUI?3?3cStaticI@ @ 0x003E7788
// match: ??_C@_0HA@PBDEEJKF@enum?5kujuUI?3?3eEventWasHandled?5__@ @ 0x003E77C0

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






}
