// The null-safe string's editing (types/type_505188.h): insertion, erasure,
// appending strings and numbers, and the std::string pieces they pull in.

#include <stdlib.h>

#include "types/type_505188.h"

// Each substring is copied into a string of its own before it is used.
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: __ehhandler$?sub_1C8110@type_1A5EA0@@QAEAAU1@IPBD@Z>1>8 @ 0x0041F628
// match: __ehhandler$?sub_1C8110@type_1A5EA0@@QAEAAU1@IPBD@Z>1 @ 0x0041F658
// match: __ehhandler$?sub_1C8330@type_1A5EA0@@QAEAAU1@II@Z>1>8 @ 0x0041F674
// match: __ehhandler$?sub_1C8330@type_1A5EA0@@QAEAAU1@II@Z>1 @ 0x0041F69C
// match: __ehhandler$?sub_1C8540@type_1A5EA0@@QAEAAU1@H@Z>1>8 @ 0x0041F6B8
// match: __ehhandler$?sub_1C8540@type_1A5EA0@@QAEAAU1@H@Z>1 @ 0x0041F6C0

// match: ?sub_1C8110@type_1A5EA0@@QAEAAU1@IPBD@Z @ 0x001C8110
// match: __ehhandler$?sub_1C8110@type_1A5EA0@@QAEAAU1@IPBD@Z-0x36 @ 0x003032A0
// match: __ehhandler$?sub_1C8110@type_1A5EA0@@QAEAAU1@IPBD@Z @ 0x003032D6

type_1A5EA0 &type_1A5EA0::sub_1C8110(RwUInt32 arg_0, const RwChar *arg_4)
{
    if (arg_0 > size())
        arg_0 = size();
    type_1A5EA0 var_2C;

    var_2C = substr(0, arg_0);
    var_2C.sub_1C84F0(arg_4);
    var_2C.sub_1C84F0(substr(arg_0));
    *this = var_2C;
    return *this;
}

// match: ?sub_1C8300@type_1A5EA0@@QAEAAU1@ID@Z @ 0x001C8300
type_1A5EA0 &type_1A5EA0::sub_1C8300(RwUInt32 arg_0, RwChar arg_4)
{
    RwChar var_4[2];

    var_4[0] = arg_4;
    var_4[1] = 0;
    return sub_1C8110(arg_0, var_4);
}

// As sub_1C8110.
// match: ?sub_1C8330@type_1A5EA0@@QAEAAU1@II@Z @ 0x001C8330
// match: __ehhandler$?sub_1C8330@type_1A5EA0@@QAEAAU1@II@Z-0x20 @ 0x003032E0
// match: __ehhandler$?sub_1C8330@type_1A5EA0@@QAEAAU1@II@Z @ 0x00303300
type_1A5EA0 &type_1A5EA0::sub_1C8330(RwUInt32 arg_0, RwUInt32 arg_4)
{
    if (arg_0 + arg_4 > size())
        arg_4 = size() - arg_0;
    type_1A5EA0 var_2C = substr(0, arg_0);

    var_2C.sub_1C84F0(substr(arg_0 + arg_4));
    *this = var_2C;
    return *this;
}

// match: ?sub_1C84D0@type_1A5EA0@@QAEXXZ @ 0x001C84D0
void type_1A5EA0::sub_1C84D0()
{
    clear();
}

// match: ?sub_1C84F0@type_1A5EA0@@QAEAAU1@ABU1@@Z @ 0x001C84F0
type_1A5EA0 &type_1A5EA0::sub_1C84F0(const type_1A5EA0 &arg_0)
{
    append(arg_0.c_str());
    return *this;
}

// match: ?sub_1C8540@type_1A5EA0@@QAEAAU1@H@Z @ 0x001C8540
// match: __ehhandler$?sub_1C8540@type_1A5EA0@@QAEAAU1@H@Z-0x8 @ 0x00303310
// match: __ehhandler$?sub_1C8540@type_1A5EA0@@QAEAAU1@H@Z @ 0x00303318
type_1A5EA0 &type_1A5EA0::sub_1C8540(RwInt32 arg_0)
{
    RwChar var_20[16];

    _itoa(arg_0, var_20, 10);
    sub_1C84F0(var_20);
    return *this;
}

// match: ?sub_1C85D0@type_1A5EA0@@QAEAAU1@H@Z @ 0x001C85D0
type_1A5EA0 &type_1A5EA0::sub_1C85D0(RwInt32 arg_0)
{
    return sub_1C8540(arg_0);
}

// std::string's copy constructor, out of line where the conversion of the
// first substring in sub_1C8110 calls it (inlined elsewhere).
// match: ??0?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@QAE@ABV01@@Z @ 0x001C85F0

// The std::string pieces these pull in, out of line here.
// match: ?clear@?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@QAEXXZ @ 0x001C8630
// match: ?substr@?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@QBE?AV12@II@Z @ 0x001C86B0
// match: ?erase@?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@QAE?AViterator@12@V312@0@Z @ 0x001C8700
// match: ?append@?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@QAEAAV12@PBDI@Z @ 0x001C87E0
// match: ?append@?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@QAEAAV12@ABV12@II@Z @ 0x001C8900
