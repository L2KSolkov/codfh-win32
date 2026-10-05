/*
 * kujuUI's images (game/kujufont.h): a 32-bit image, read from a .tga (8,
 * 24 or 32 bits), flipped and halved.
 */
#include <string.h>
#include "game/kujuui.h"
#include "game/kujufont.h"
#include "game/fileio.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x0042D0CC
const RwChar *dword_42D0CC = "";
// End of its data definitions.

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: __ehhandler$?sub_1E6CD0@@YAXPBDPAPAUtype_1E6B50@@@Z>1>8 @ 0x00420180
// match: __ehhandler$?sub_1E6CD0@@YAXPBDPAPAUtype_1E6B50@@@Z>1 @ 0x00420188
// match: __ehhandler$?sub_1E7100@type_1E6B50@@QAEXPAPAU1@@Z>1>8 @ 0x004201A4
// match: __ehhandler$?sub_1E7100@type_1E6B50@@QAEXPAPAU1@@Z>1 @ 0x004201AC
// match: .CRT$XCU+0 @ 0x00427348
// match: ?dword_42D0CC@@3PBDB @ 0x0042D0CC

// match: _$E1 @ 0x0030DA10

using namespace kujuUI;

// match: ??0type_1E6B50@@QAE@IIPAPAI@Z @ 0x001E6B50
type_1E6B50::type_1E6B50(RwUInt32 arg_0, RwUInt32 arg_4, RwUInt32 **arg_8)
{
    unk_00 = arg_0;
    unk_04 = arg_4;
    unk_08 = *arg_8;
    *arg_8 = 0;
}

// match: ??1type_1E6B50@@QAE@XZ @ 0x001E6B90
type_1E6B50::~type_1E6B50()
{
    delete unk_08;
}

// match: ?sub_1E6BC0@@YA_NPAUcFileIn@kujuUI@@PAII@Z @ 0x001E6BC0
bool sub_1E6BC0(cFileIn *arg_0, RwUInt32 *arg_4, RwUInt32 arg_8)
{
    if (arg_0->sub_1C8BA0(arg_4, arg_8 * 4))
        return true;
    return false;
}

// match: ?sub_1E6BF0@@YA_NPAUcFileIn@kujuUI@@PAII@Z @ 0x001E6BF0
bool sub_1E6BF0(cFileIn *arg_0, RwUInt32 *arg_4, RwUInt32 arg_8)
{
    RwUInt32 *var_4 = arg_4 + arg_8;
    while (arg_4 != var_4)
    {
        RwUInt32 var_8 = 0xFF000000;
        if (!arg_0->sub_1C8BA0(&var_8, 3))
            return false;
        *arg_4 = var_8;
        ++arg_4;
    }
    return true;
}

// match: ?sub_1E6C50@@YA_NPAUcFileIn@kujuUI@@PAII@Z @ 0x001E6C50
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
bool sub_1E6C50(cFileIn *arg_0, RwUInt32 *arg_4, RwUInt32 arg_8)
{
    RwUInt32 *var_8 = arg_4;
    RwUInt32 *local_C = arg_4 + arg_8;
    RwUInt32 bp_4 = 0;
    while (var_8 != local_C)
    {
        RwUInt8 var_D;
        if (!arg_0->sub_1C8BA0(&var_D, 1))
            break;
        *var_8 = (var_D << 24) | 0xFFFFFF;
        ++bp_4;
        ++var_8;
    }
    return var_8 == local_C;
}

// match: ?sub_1E6CD0@@YAXPBDPAPAUtype_1E6B50@@@Z @ 0x001E6CD0
// match: __ehhandler$?sub_1E6CD0@@YAXPBDPAPAUtype_1E6B50@@@Z-0xB @ 0x00303BD0
// match: __ehhandler$?sub_1E6CD0@@YAXPBDPAPAUtype_1E6B50@@@Z @ 0x00303BDB
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_1E6CD0(const RwChar *arg_0, type_1E6B50 **arg_4)
{
    *arg_4 = 0;
    cFileIn *lv_10 = 0;
    sub_1C8CA0(arg_0, &lv_10);
    if (lv_10)
    {
        RwUInt8 var_25 = 0;
        RwUInt16 slot_24 = 0;
        RwUInt16 v20 = 0;
        RwUInt8 v26 = 0;
        RwUInt8 r15 = 0;
        bool var_16 = true;
        RwUInt8 loc1C[4];
        var_16 &= lv_10->sub_1C8BA0(loc1C, 2);
        var_16 &= lv_10->sub_1C8BA0(&var_25, 1);
        var_16 &= lv_10->sub_1C8BA0(loc1C, 4);
        var_16 &= lv_10->sub_1C8BA0(loc1C, 4);
        var_16 &= lv_10->sub_1C8BA0(loc1C, 1);
        var_16 &= lv_10->sub_1C8BA0(&slot_24, 2);
        var_16 &= lv_10->sub_1C8BA0(&v20, 2);
        var_16 &= lv_10->sub_1C8BA0(&v26, 1);
        var_16 &= lv_10->sub_1C8BA0(&r15, 1);
        RwUInt32 v14 = slot_24 * v20;
        switch (var_25)
        {
        case 2:
            if (v26 != 32 && v26 != 24)
                return;
            break;
        case 3:
            if (v26 != 8)
                return;
            break;
        default:
            return;
        }
        if (var_16)
        {
            RwUInt32 *var_2C = new RwUInt32[v14];
            bool var_27 = false;
            switch (v26)
            {
            case 8:
                var_27 = sub_1E6C50(lv_10, var_2C, v14);
                break;
            case 24:
                var_27 = sub_1E6BF0(lv_10, var_2C, v14);
                break;
            case 32:
                var_27 = sub_1E6BC0(lv_10, var_2C, v14);
                break;
            }
            if (var_27)
            {
                *arg_4 = new type_1E6B50(slot_24, v20, &var_2C);
                if (!r15)
                    (*arg_4)->sub_1E6FD0();
            }
            else
                delete var_2C;
        }
        delete lv_10;
    }
}

// match: ?sub_1E6FD0@type_1E6B50@@QAEXXZ @ 0x001E6FD0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_1E6B50::sub_1E6FD0()
{
    RwUInt32 *var_8 = new RwUInt32[unk_00 * unk_04];
    RwUInt32 *local_C = &unk_08[(unk_04 - 1) * unk_00];
    RwUInt32 *bp_4 = var_8;
    for (RwUInt32 var_10 = 0; var_10 != unk_04; ++var_10)
    {
        memcpy(bp_4, local_C, unk_00 * 4);
        local_C -= unk_00;
        bp_4 += unk_00;
    }
    delete unk_08;
    unk_08 = var_8;
}

// match: ?sub_1E70A0@@YAIPBII@Z @ 0x001E70A0
RwUInt32 sub_1E70A0(const RwUInt32 *arg_0, RwUInt32 arg_4)
{
    RwUInt32 var_4 = 0;
    for (RwInt32 var_8 = 0; var_8 != 4; ++var_8)
        var_4 += (arg_0[var_8] >> arg_4) & 0xFF;
    var_4 /= 4;
    var_4 <<= arg_4;
    return var_4;
}

// match: ?sub_1E7100@type_1E6B50@@QAEXPAPAU1@@Z @ 0x001E7100
// match: __ehhandler$?sub_1E7100@type_1E6B50@@QAEXPAPAU1@@Z-0xB @ 0x00303BF0
// match: __ehhandler$?sub_1E7100@type_1E6B50@@QAEXPAPAU1@@Z @ 0x00303BFB
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_1E6B50::sub_1E7100(type_1E6B50 **arg_0)
{
    RwUInt32 lv_1C = unk_00 / 2;
    RwUInt32 t24 = unk_04 / 2;
    RwUInt32 v14 = lv_1C * t24;
    RwUInt32 *var20 = new RwUInt32[v14];
    RwUInt32 *ebp_34 = var20;
    RwUInt32 *bp_18 = var20 + v14;
    const RwUInt32 *lv_10 = unk_08;
    RwUInt32 var_30 = 0;
    RwUInt32 local_28 = unk_00 / 2;
    RwUInt32 bp_2C = 0;
    while (ebp_34 != bp_18)
    {
        RwUInt32 var_44[4];
        var_44[0] = lv_10[0];
        var_44[1] = lv_10[1];
        var_44[2] = lv_10[unk_00];
        var_44[3] = lv_10[unk_00 + 1];
        *ebp_34 = sub_1E70A0(var_44, 0) | sub_1E70A0(var_44, 8) | sub_1E70A0(var_44, 16) | sub_1E70A0(var_44, 24);
        ++var_30;
        lv_10 += 2;
        if (var_30 == local_28)
        {
            lv_10 += unk_00;
            var_30 = 0;
        }
        ++ebp_34;
        ++bp_2C;
    }
    *arg_0 = new type_1E6B50(lv_1C, t24, &var20);
}

extern const RwChar *dword_42D0CC;

// match: ?sub_1E72B0@@YAPBDXZ @ 0x001E72B0
const RwChar *sub_1E72B0()
{
    return dword_42D0CC;
}

// The length of dword_42D0CC, measured when the program starts (nothing reads it).
RwUInt32 dword_504208 = strlen(dword_42D0CC);
