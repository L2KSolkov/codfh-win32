/*
 * kujuUI's on-screen keyboard's key (game/kujuui.h): a text button that is
 * its own do-nothing action when it is given none.
 */
#include "game/kujuui.h"

using namespace kujuUI;

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_7type_3E7C30@kujuUI@@6Btype_3E79B4@1@@ @ 0x003E7C0C
// match: ??_7type_3E7C30@kujuUI@@6Btype_3E75E8@1@@ @ 0x003E7C1C
// match: ??_7type_3E7C30@kujuUI@@6Btype_3E7D08@1@@ @ 0x003E7C30
// match: __ehhandler$??1type_3E7C30@kujuUI@@UAE@XZ>1>8 @ 0x004212A4
// match: __ehhandler$??1type_3E7C30@kujuUI@@UAE@XZ>1 @ 0x004212AC

// match: ??0type_3E7C30@kujuUI@@QAE@PBDPBUtype_1E0330_rect@1@ABUtype_1A5EA0@@HPAUtype_1ED670_object@1@PAUtype_3E7D08@1@@Z @ 0x001F5870

type_3E7C30::type_3E7C30(const RwChar *arg_0, const type_1E0330_rect *arg_4, const type_1A5EA0 &arg_8, RwInt32 arg_C,
                         type_1ED670_object *arg_10, type_3E7D08 *arg_14)
    : type_3E79B4(arg_0, arg_4, true, arg_10 ? arg_10 : this, 0, 0, arg_8, 0, arg_C, 1, arg_14)
{
}

// match: ??_Gtype_3E7C30@kujuUI@@UAEPAXI@Z @ 0x001F5930

// match: ??1type_3E7C30@kujuUI@@UAE@XZ @ 0x001F5960
// match: __ehhandler$??1type_3E7C30@kujuUI@@UAE@XZ-0x8 @ 0x003048F0
// match: __ehhandler$??1type_3E7C30@kujuUI@@UAE@XZ @ 0x003048F8
type_3E7C30::~type_3E7C30()
{
}

// match: ??_Etype_3E7C30@kujuUI@@WM@AEPAXI@Z @ 0x001F5A20
// match: ??_Etype_3E7C30@kujuUI@@WCM@AEPAXI@Z @ 0x001F5A30
// match: ??_Etype_3E7C30@kujuUI@@WMM@AEPAXI@Z @ 0x001F5A40

// match: ?processEvent@type_3E7C30@kujuUI@@UAE?AW4eEventWasHandled@2@ABVcStateChange@2@@Z @ 0x001F5A00
eEventWasHandled type_3E7C30::processEvent(const cStateChange &arg_0)
{
    return (eEventWasHandled)1;
}
