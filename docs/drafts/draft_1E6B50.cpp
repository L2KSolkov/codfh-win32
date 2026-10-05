/*
 * kujuUI's images (game/kujufont.h): a 32-bit image, read from a .tga (8,
 * 24 or 32 bits), flipped and halved.
 */
#include <string.h>
#include "game/kujuui.h"
#include "game/kujufont.h"
#include "game/fileio.h"

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

// match: ?sub_1E6BC0@@YA_NPAVcFileIn@kujuUI@@PAII@Z @ 0x001E6BC0
bool sub_1E6BC0(cFileIn *arg_0, RwUInt32 *arg_4, RwUInt32 arg_8)
{
    if (arg_0->sub_1C8BA0(arg_4, arg_8 * 4))
        return true;
    return false;
}

// match: ?sub_1E6BF0@@YA_NPAVcFileIn@kujuUI@@PAII@Z @ 0x001E6BF0
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

// match: ?sub_1E6C50@@YA_NPAVcFileIn@kujuUI@@PAII@Z @ 0x001E6C50
bool sub_1E6C50(cFileIn *arg_0, RwUInt32 *arg_4, RwUInt32 arg_8)
{
    RwUInt32 *var_8 = arg_4;
    RwUInt32 *var_C = arg_4 + arg_8;
    RwUInt32 var_4 = 0;
    while (var_8 != var_C)
    {
        RwUInt8 var_D;
        if (!arg_0->sub_1C8BA0(&var_D, 1))
            break;
        *var_8 = (var_D << 24) | 0xFFFFFF;
        ++var_4;
        ++var_8;
    }
    return var_8 == var_C;
}

// match: ?sub_1E6CD0@@YAXPBDPAPAUtype_1E6B50@@@Z @ 0x001E6CD0
void sub_1E6CD0(const RwChar *arg_0, type_1E6B50 **arg_4)
{
    *arg_4 = 0;
    cFileIn *var_10 = 0;
    sub_1C8CA0(arg_0, &var_10);
    if (!var_10)
        return;
    RwUInt8 var_25 = 0;
    RwUInt16 var_24 = 0;
    RwUInt16 var_20 = 0;
    RwUInt8 var_26 = 0;
    RwUInt8 var_15 = 0;
    bool var_16 = true;
    RwUInt8 var_1C[4];
    var_16 &= var_10->sub_1C8BA0(var_1C, 2);
    var_16 &= var_10->sub_1C8BA0(&var_25, 1);
    var_16 &= var_10->sub_1C8BA0(var_1C, 4);
    var_16 &= var_10->sub_1C8BA0(var_1C, 4);
    var_16 &= var_10->sub_1C8BA0(var_1C, 1);
    var_16 &= var_10->sub_1C8BA0(&var_24, 2);
    var_16 &= var_10->sub_1C8BA0(&var_20, 2);
    var_16 &= var_10->sub_1C8BA0(&var_26, 1);
    var_16 &= var_10->sub_1C8BA0(&var_15, 1);
    RwUInt32 var_14 = var_24 * var_20;
    switch (var_25)
    {
    case 2:
        if (var_26 != 32 && var_26 != 24)
            return;
        break;
    case 3:
        if (var_26 != 8)
            return;
        break;
    default:
        return;
    }
    if (var_16)
    {
        RwUInt32 *var_2C = new RwUInt32[var_14];
        bool var_27 = false;
        switch (var_26)
        {
        case 8:
            var_27 = sub_1E6C50(var_10, var_2C, var_14);
            break;
        case 24:
            var_27 = sub_1E6BF0(var_10, var_2C, var_14);
            break;
        case 32:
            var_27 = sub_1E6BC0(var_10, var_2C, var_14);
            break;
        }
        if (var_27)
        {
            *arg_4 = new type_1E6B50(var_24, var_20, &var_2C);
            if (!var_15)
                (*arg_4)->sub_1E6FD0();
        }
        else
            delete var_2C;
    }
    delete var_10;
}

// match: ?sub_1E6FD0@type_1E6B50@@QAEXXZ @ 0x001E6FD0
void type_1E6B50::sub_1E6FD0()
{
    RwUInt32 *var_8 = new RwUInt32[unk_00 * unk_04];
    RwUInt32 *var_C = &unk_08[(unk_04 - 1) * unk_00];
    RwUInt32 *var_4 = var_8;
    for (RwUInt32 var_10 = 0; var_10 != unk_04; ++var_10)
    {
        memcpy(var_4, var_C, unk_00 * 4);
        var_C -= unk_00;
        var_4 += unk_00;
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
void type_1E6B50::sub_1E7100(type_1E6B50 **arg_0)
{
    RwUInt32 var_1C = unk_00 / 2;
    RwUInt32 var_24 = unk_04 / 2;
    RwUInt32 var_14 = var_1C * var_24;
    RwUInt32 *var_20 = new RwUInt32[var_14];
    RwUInt32 *var_34 = var_20;
    RwUInt32 *var_18 = var_20 + var_14;
    const RwUInt32 *var_10 = unk_08;
    RwUInt32 var_30 = 0;
    RwUInt32 var_28 = unk_00 / 2;
    RwUInt32 var_2C = 0;
    while (var_34 != var_18)
    {
        RwUInt32 var_44[4];
        var_44[0] = var_10[0];
        var_44[1] = var_10[1];
        var_44[2] = var_10[unk_00];
        var_44[3] = var_10[unk_00 + 1];
        *var_34 = sub_1E70A0(var_44, 0) | sub_1E70A0(var_44, 8) | sub_1E70A0(var_44, 16) | sub_1E70A0(var_44, 24);
        ++var_30;
        var_10 += 2;
        if (var_30 == var_28)
        {
            var_10 += unk_00;
            var_30 = 0;
        }
        ++var_34;
        ++var_2C;
    }
    *arg_0 = new type_1E6B50(var_1C, var_24, &var_20);
}

extern RwUInt32 dword_42D0CC;

// match: ?sub_1E72B0@@YAIXZ @ 0x001E72B0
RwUInt32 sub_1E72B0()
{
    return dword_42D0CC;
}
