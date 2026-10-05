/*
 * kujuUI's selectable widget (game/kujuui.h): a widget with a look, its
 * rectangle and hidden flag given through its second interface and its look
 * set through its third.
 */
#include "game/kujuui.h"

using namespace kujuUI;

// Vtables (.rdata, PLAN M5): each in its own placement range (config/splits.txt).
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_7type_3E76B4@kujuUI@@6Btype_3E76E4@1@@ @ 0x003E769C
// match: ??_7type_3E76B4@kujuUI@@6Btype_3E75E8@1@@ @ 0x003E76A0
// match: ??_7type_3E76B4@kujuUI@@6Btype_3E7D08@1@@ @ 0x003E76B4
// match: ??_7type_3E76E4@kujuUI@@6B@ @ 0x003E76E4
// match: __ehhandler$??0type_3E76B4@kujuUI@@QAE@PBDPBUtype_1E0330_rect@1@PAUtype_3E7D08@1@@Z>1>8 @ 0x00420B28
// match: __ehhandler$??0type_3E76B4@kujuUI@@QAE@PBDPBUtype_1E0330_rect@1@PAUtype_3E7D08@1@@Z>1 @ 0x00420B40
// match: __ehhandler$??1type_3E76B4@kujuUI@@UAE@XZ>1>8 @ 0x00420B5C
// match: __ehhandler$??1type_3E76B4@kujuUI@@UAE@XZ>1 @ 0x00420B6C

// match: ??0type_3E76B4@kujuUI@@QAE@PBDPBUtype_1E0330_rect@1@PAUtype_3E7D08@1@@Z @ 0x001EFDA0
// match: __ehhandler$??0type_3E76B4@kujuUI@@QAE@PBDPBUtype_1E0330_rect@1@PAUtype_3E7D08@1@@Z-0x1E @ 0x003041C0
// match: __ehhandler$??0type_3E76B4@kujuUI@@QAE@PBDPBUtype_1E0330_rect@1@PAUtype_3E7D08@1@@Z @ 0x003041DE

// arg_0 goes straight into the look's constructor, which takes a look
// definition (docs/questions.md: its declared type is a string's).
type_3E76B4::type_3E76B4(const RwChar *arg_0, const type_1E0330_rect *arg_4, type_3E7D08 *arg_8) : type_3E7D08(arg_8)
{
    unk_14 = new type_1E37A0((type_1E3BA0 *)arg_0);
    unk_18 = false;
    unk_14->sub_1E3A30(arg_4);
    unk_14->sub_1E3B20(0);
}

// match: ??1type_3E76B4@kujuUI@@UAE@XZ @ 0x001EFEA0
// match: __ehhandler$??1type_3E76B4@kujuUI@@UAE@XZ-0x2F @ 0x003041F0
// match: __ehhandler$??1type_3E76B4@kujuUI@@UAE@XZ @ 0x0030421F
type_3E76B4::~type_3E76B4()
{
    delete unk_14;
}

// match: ?vf_018@type_3E76B4@kujuUI@@UAEXPAUtype_1E4130@2@@Z @ 0x001EFF70
void type_3E76B4::vf_018(type_1E4130 *arg_0)
{
    if (!unk_18)
        unk_14->sub_1E3950(arg_0);
}

// match: ?sub_1EFFA0@type_3E76B4@kujuUI@@QAEXH@Z @ 0x001EFFA0
void type_3E76B4::sub_1EFFA0(RwInt32 arg_0)
{
    unk_14->sub_1E3B20(arg_0);
}

// match: ?sub_1EFFC0@type_3E76B4@kujuUI@@QAEHXZ @ 0x001EFFC0
RwInt32 type_3E76B4::sub_1EFFC0()
{
    return unk_14->sub_1E3B80();
}

// match: ?pvf_000@type_3E76B4@kujuUI@@UAEXH@Z @ 0x001EFFE0
void type_3E76B4::pvf_000(RwInt32 arg_0)
{
    unk_14->sub_1E3A00((type_1E3BA0 *)arg_0);
}

// match: ?pvf_008@type_3E76B4@kujuUI@@UAEXPBUtype_1E0330_rect@2@@Z @ 0x001F0000
void type_3E76B4::pvf_008(const type_1E0330_rect *arg_0)
{
    unk_14->sub_1E3A30(arg_0);
}

// match: ?pvf_004@type_3E76B4@kujuUI@@UAEPBUtype_1E0330_rect@2@XZ @ 0x001F0020
const type_1E0330_rect *type_3E76B4::pvf_004()
{
    return unk_14->sub_1E3B60();
}

// match: ?pvf_00C@type_3E76B4@kujuUI@@UAE_NXZ @ 0x001F0040
bool type_3E76B4::pvf_00C()
{
    return unk_18;
}

// match: ?pvf_010@type_3E76B4@kujuUI@@UAEX_N@Z @ 0x001F0060
void type_3E76B4::pvf_010(bool arg_0)
{
    unk_18 = arg_0;
}

// match: ?vf_020@type_3E76B4@kujuUI@@UAE?AUtype_1E0330_rect@2@XZ @ 0x001F0080
type_1E0330_rect type_3E76B4::vf_020()
{
    return *unk_14->sub_1E3B60();
}

// match: ??1type_3E70B0@kujuUI@@UAE@XZ @ 0x001F00C0
type_3E70B0::~type_3E70B0()
{
}
