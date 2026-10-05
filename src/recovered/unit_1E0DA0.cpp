/*
 * kujuUI's caret (\COD\SHARED\UI\cCaret.cpp, game/kujuui.h): its traces
 * name the class and its focus and event handlers, which only report being
 * called (level 3).
 */
#include "game/kujuui.h"
#include "game/assert.h"

namespace kujuUI {

// How long the caret is shown and hidden (0x3E6E04).
static const RwReal unk_3E6E04 = 0.5f;

// Vtables (.rdata, PLAN M5): each in its own placement range (config/splits.txt).
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: _unk_3E6E04 @ 0x003E6E04
// match: ??_7cCaret@kujuUI@@6Btype_3E76E4@1@@ @ 0x003E6E08
// match: ??_7cCaret@kujuUI@@6Btype_3E75E8@1@@ @ 0x003E6E0C
// match: ??_7cCaret@kujuUI@@6Btype_3E7D08@1@@ @ 0x003E6E20
// match: ??_C@_0BK@KKIHBCBA@?2COD?2SHARED?2UI?2cCaret?4cpp?$AA@ @ 0x003E6E50
// match: ??_C@_0DB@BKMHNGK@void?5__thiscall?5kujuUI?3?3cCaret?3?3@ @ 0x003E6E6C
// match: ??_C@_0DA@FCAKAIAI@void?5__thiscall?5kujuUI?3?3cCaret?3?3@ @ 0x003E6EA0
// match: ??_C@_0GK@LCPDIIBG@enum?5kujuUI?3?3eEventWasHandled?5__@ @ 0x003E6ED0

// match: ??0cCaret@kujuUI@@QAE@PBDPBUtype_1E0330_rect@1@PAUtype_3E7D08@1@@Z @ 0x001E0DA0

cCaret::cCaret(const RwChar *arg_0, const type_1E0330_rect *arg_4, type_3E7D08 *arg_8)
    : type_3E76B4(arg_0, arg_4, arg_8)
{
    unk_1C = false;
    unk_20 = unk_3E6E04;
    unk_24 = 0;
}

// match: ??_GcCaret@kujuUI@@UAEPAXI@Z @ 0x001E0E00

// match: ??1cCaret@kujuUI@@UAE@XZ @ 0x001E0E30
cCaret::~cCaret()
{
}

// match: ?givenFocus@cCaret@kujuUI@@UAEXXZ @ 0x001E0E60
void cCaret::givenFocus()
{
#line 55 "\\COD\\SHARED\\UI\\cCaret.cpp"
    sub_1C7F20(false, __FILE__, __LINE__, __FUNCSIG__, 3);
}

// match: ?lostFocus@cCaret@kujuUI@@UAEXXZ @ 0x001E0E90
void cCaret::lostFocus()
{
#line 63 "\\COD\\SHARED\\UI\\cCaret.cpp"
    sub_1C7F20(false, __FILE__, __LINE__, __FUNCSIG__, 3);
}

// match: ?processEvent@cCaret@kujuUI@@UAE?AW4eEventWasHandled@2@ABVcStateChange@2@@Z @ 0x001E0EC0
eEventWasHandled cCaret::processEvent(const cStateChange &arg_0)
{
#line 80 "\\COD\\SHARED\\UI\\cCaret.cpp"
    sub_1C7F20(false, __FILE__, __LINE__, __FUNCSIG__, 3);
    return (eEventWasHandled)1;
}

// match: ?vf_014@cCaret@kujuUI@@UAEXM@Z @ 0x001E0EF0
void cCaret::vf_014(RwReal arg_0)
{
    unk_24 += arg_0;
    if (unk_24 > unk_20)
    {
        unk_24 = 0;
        unk_1C = !unk_1C;
    }
}

// match: ?vf_018@cCaret@kujuUI@@UAEXPAUtype_1E4130@2@@Z @ 0x001E0F40
void cCaret::vf_018(type_1E4130 *arg_0)
{
    if (unk_1C)
        type_3E76B4::vf_018(arg_0);
}

// match: ??_EcCaret@kujuUI@@WM@AEPAXI@Z @ 0x001E0F70
}
