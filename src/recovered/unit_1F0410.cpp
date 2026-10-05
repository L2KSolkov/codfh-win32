/*
 * kujuUI's static text (\COD\SHARED\UI\cStaticText.cpp, game/kujuui.h): its
 * traces name the class and its focus and event handlers, which only report
 * being called (level 3).
 */
#include "game/kujuui.h"
#include "game/assert.h"

namespace kujuUI {

// Vtables (.rdata, PLAN M5): each in its own placement range (config/splits.txt).
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_7cStaticText@kujuUI@@6Btype_3E7258@1@@ @ 0x003E7840
// match: ??_7cStaticText@kujuUI@@6Btype_3E7D08@1@@ @ 0x003E7850
// match: ??_C@_0BP@ONLMLJCP@?2COD?2SHARED?2UI?2cStaticText?4cpp?$AA@ @ 0x003E7890
// match: ??_C@_0DG@MGLAIILC@void?5__thiscall?5kujuUI?3?3cStaticT@ @ 0x003E78B0
// match: ??_C@_0DF@JJFHGEHD@void?5__thiscall?5kujuUI?3?3cStaticT@ @ 0x003E78E8
// match: ??_C@_0GP@NCCMMDNO@enum?5kujuUI?3?3eEventWasHandled?5__@ @ 0x003E7920
// match: __ehhandler$??0cStaticText@kujuUI@@QAE@HPBUtype_1E0330_rect@1@IPAUtype_1F28C0@1@PAUtype_3E7D08@1@@Z>1>8 @ 0x00420BAC
// match: __ehhandler$??0cStaticText@kujuUI@@QAE@HPBUtype_1E0330_rect@1@IPAUtype_1F28C0@1@PAUtype_3E7D08@1@@Z>1 @ 0x00420BC4
// match: __ehhandler$??1cStaticText@kujuUI@@UAE@XZ>1>8 @ 0x00420BE0
// match: __ehhandler$??1cStaticText@kujuUI@@UAE@XZ>1 @ 0x00420BF0

// match: ??0cStaticText@kujuUI@@QAE@HPBUtype_1E0330_rect@1@IPAUtype_1F28C0@1@PAUtype_3E7D08@1@@Z @ 0x001F0410
// match: __ehhandler$??0cStaticText@kujuUI@@QAE@HPBUtype_1E0330_rect@1@IPAUtype_1F28C0@1@PAUtype_3E7D08@1@@Z-0x1E @ 0x00304250
// match: __ehhandler$??0cStaticText@kujuUI@@QAE@HPBUtype_1E0330_rect@1@IPAUtype_1F28C0@1@PAUtype_3E7D08@1@@Z @ 0x0030426E

cStaticText::cStaticText(RwInt32 arg_0, const type_1E0330_rect *arg_4, RwUInt32 arg_8, type_1F28C0 *arg_C,
                         type_3E7D08 *arg_10)
    : type_3E7D08(arg_10), unk_10(arg_0, arg_4, arg_8, true)
{
    if (arg_C)
    {
        pvf_008(arg_C->unk_08);
        arg_C->sub_1E7540(this);
    }
}

// match: ??_GcStaticText@kujuUI@@UAEPAXI@Z @ 0x001F04E0

// match: ??1cStaticText@kujuUI@@UAE@XZ @ 0x001F0510
// match: __ehhandler$??1cStaticText@kujuUI@@UAE@XZ-0x2F @ 0x00304280
// match: __ehhandler$??1cStaticText@kujuUI@@UAE@XZ @ 0x003042AF
cStaticText::~cStaticText()
{
}

// match: ?givenFocus@cStaticText@kujuUI@@UAEXXZ @ 0x001F05A0
void cStaticText::givenFocus()
{
#line 55 "\\COD\\SHARED\\UI\\cStaticText.cpp"
    sub_1C7F20(false, __FILE__, __LINE__, __FUNCSIG__, 3);
}

// match: ?lostFocus@cStaticText@kujuUI@@UAEXXZ @ 0x001F05D0
void cStaticText::lostFocus()
{
#line 61 "\\COD\\SHARED\\UI\\cStaticText.cpp"
    sub_1C7F20(false, __FILE__, __LINE__, __FUNCSIG__, 3);
}

// match: ?processEvent@cStaticText@kujuUI@@UAE?AW4eEventWasHandled@2@ABVcStateChange@2@@Z @ 0x001F0600
eEventWasHandled cStaticText::processEvent(const cStateChange &arg_0)
{
#line 80 "\\COD\\SHARED\\UI\\cStaticText.cpp"
    sub_1C7F20(false, __FILE__, __LINE__, __FUNCSIG__, 3);
    return (eEventWasHandled)1;
}

// match: ?vf_018@cStaticText@kujuUI@@UAEXPAUtype_1E4130@2@@Z @ 0x001F0630
void cStaticText::vf_018(type_1E4130 *arg_0)
{
    unk_10.sub_1F1B10(arg_0);
}

// match: ?vf_008@cStaticText@kujuUI@@UAEXXZ @ 0x001F0650
void cStaticText::vf_008()
{
    unk_10.sub_1F1AA0();
    type_3E7D08::vf_008();
}

// match: ?vf_00C@cStaticText@kujuUI@@UAEXXZ @ 0x001F0670
void cStaticText::vf_00C()
{
    unk_10.sub_1F1AD0();
    type_3E7D08::vf_00C();
}

// match: ?pvf_004@cStaticText@kujuUI@@UAEXH@Z @ 0x001F0690
void cStaticText::pvf_004(RwInt32 arg_0)
{
    unk_10.sub_1F1E00(arg_0);
}

// match: ?pvf_008@cStaticText@kujuUI@@UAEXABUtype_1A5EA0@@@Z @ 0x001F06B0
void cStaticText::pvf_008(const type_1A5EA0 &arg_0)
{
    unk_10.sub_1F1D10(arg_0);
    static_cast<type_3E75E8 &>(unk_10).pvf_008(vf_030());
}

// match: ?vf_034@cStaticText@kujuUI@@UAEXPBUtype_1E0330_rect@2@@Z @ 0x001F06F0
void cStaticText::vf_034(const type_1E0330_rect *arg_0)
{
    static_cast<type_3E75E8 &>(unk_10).pvf_008(arg_0);
}

// match: ?vf_030@cStaticText@kujuUI@@UAEPBUtype_1E0330_rect@2@XZ @ 0x001F0710
const type_1E0330_rect *cStaticText::vf_030()
{
    return static_cast<type_3E75E8 &>(unk_10).pvf_004();
}

// match: ?vf_038@cStaticText@kujuUI@@UAE_NXZ @ 0x001F0730
bool cStaticText::vf_038()
{
    return static_cast<type_3E75E8 &>(unk_10).pvf_00C();
}

// match: ?vf_03C@cStaticText@kujuUI@@UAEX_N@Z @ 0x001F0750
void cStaticText::vf_03C(bool arg_0)
{
    static_cast<type_3E75E8 &>(unk_10).pvf_010(arg_0);
}

// match: ?vf_020@cStaticText@kujuUI@@UAE?AUtype_1E0330_rect@2@XZ @ 0x001F0770
type_1E0330_rect cStaticText::vf_020()
{
    return *static_cast<type_3E75E8 &>(unk_10).pvf_004();
}

// match: ??_EcStaticText@kujuUI@@WM@AEPAXI@Z @ 0x001F07B0
}
