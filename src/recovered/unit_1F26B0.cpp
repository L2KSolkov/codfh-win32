// kujuUI's text measure and type_1F28C0: split from unit_1F1420.cpp at 0x1F26B0, where the image
// ends that object (its deferred functions come before the next out-of-line one; PLAN M7).

#include <math.h>
#include <string.h>
#include "game/kujuui.h"
#include "game/loc.h"

using namespace kujuUI;

// match: __ehhandler$??0type_1F28C0@kujuUI@@QAE@XZ>1>8 @ 0x00420E74
// match: __ehhandler$??0type_1F28C0@kujuUI@@QAE@XZ>1 @ 0x00420E7C
// match: __ehhandler$??1type_1F28C0@kujuUI@@UAE@XZ>1>8 @ 0x00420E98
// match: __ehhandler$??1type_1F28C0@kujuUI@@UAE@XZ>1 @ 0x00420EA0
// match: ??_Gtype_1F28C0@kujuUI@@UAEPAXI@Z @ 0x001F2800
// match: ??_7type_1F28C0@kujuUI@@6B@ @ 0x003E7A30

// match: ?sub_1F26B0@type_1E5A60@@QAEIPBDIPAI1H@Z @ 0x001F26B0
RwUInt32 type_1E5A60::sub_1F26B0(const RwChar *arg_0, RwUInt32 arg_4, RwUInt32 *arg_8, RwUInt32 *arg_C, RwInt32 arg_10)
{
    RwInt32 bp_4;
    RwChar var_108[0x100];
    RwInt32 var_10C;
    if (arg_10 != -1)
    {
        memcpy(var_108, arg_0, arg_10);
        var_108[arg_10] = 0;
        arg_0 = var_108;
    }
    var_10C = unk_0E / 2;
    while (*arg_0)
    {
        sub_1E69D0(arg_0, arg_4, arg_8, &bp_4, &arg_0);
        var_10C += sub_1E60E0();
        if (!*arg_0)
            *arg_C = var_10C - unk_0E / 2;
    }
    return *arg_8;
}
// match: ??0type_1F28C0@kujuUI@@QAE@XZ @ 0x001F2790
// match: __ehhandler$??0type_1F28C0@kujuUI@@QAE@XZ-0x8 @ 0x00304500
// match: __ehhandler$??0type_1F28C0@kujuUI@@QAE@XZ @ 0x00304508
type_1F28C0::type_1F28C0() : unk_04(0)
{
    unk_24 = 0;
}
// match: ??1type_1F28C0@kujuUI@@UAE@XZ @ 0x001F2830
// match: __ehhandler$??1type_1F28C0@kujuUI@@UAE@XZ-0x8 @ 0x00304520
// match: __ehhandler$??1type_1F28C0@kujuUI@@UAE@XZ @ 0x00304528
type_1F28C0::~type_1F28C0()
{
}
// match: ?sub_1F2890@type_1F28C0@kujuUI@@QAEXXZ @ 0x001F2890
void type_1F28C0::sub_1F2890()
{
    if (unk_04)
        unk_04->pvf_008(unk_08);
}
// match: ?sub_1F28C0@type_1F28C0@kujuUI@@QAEXABUtype_1A5EA0@@@Z @ 0x001F28C0
void type_1F28C0::sub_1F28C0(const type_1A5EA0 &arg_0)
{
    static_cast<type_1A5EA0 &>(unk_08) = arg_0;
    sub_1F2890();
}
// match: ??1type_3E7258@kujuUI@@UAE@XZ @ 0x001F2900
type_3E7258::~type_3E7258()
{
}
