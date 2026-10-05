// An id with two strings (types/type_505188.h), and the library's string
// members it needs out of line.

#include "types/type_505188.h"

// Its frame's unused slots are the string constructor's expansions,
// reserved though it is not inlined (docs/toolchain.md).
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: __ehhandler$??0type_505188@@QAE@XZ>1>8 @ 0x0041EAF0
// match: __ehhandler$??0type_505188@@QAE@XZ>1 @ 0x0041EAF8
// match: __ehhandler$??1type_505188@@QAE@XZ>1>8 @ 0x0041EB14
// match: __ehhandler$??1type_505188@@QAE@XZ>1 @ 0x0041EB1C

// match: ??0type_505188@@QAE@XZ @ 0x001A5E10
// match: __ehhandler$??0type_505188@@QAE@XZ-0xE @ 0x00302930
// match: __ehhandler$??0type_505188@@QAE@XZ @ 0x0030293E

type_505188::type_505188() : unk_00(-1), unk_04(""), unk_20(""), unk_3C(0)
{
}

// Defined in its class (types/type_505188.h), not inlined.
// match: ??0type_1A5EA0@@QAE@PBD@Z @ 0x001A5EA0

// match: ??1type_505188@@QAE@XZ @ 0x001A5EF0
// match: __ehhandler$??1type_505188@@QAE@XZ-0xB @ 0x00302950
// match: __ehhandler$??1type_505188@@QAE@XZ @ 0x0030295B
type_505188::~type_505188()
{
}


// match: ?sub_1A5F60@type_505188@@QBEABUtype_1A5EA0@@XZ @ 0x001A5F60
const type_1A5EA0 &type_505188::sub_1A5F60() const
{
    return unk_04;
}

// The library's compares, out of line here.
// match: ?compare@?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@QBEHABV12@@Z @ 0x001A6010
// match: ?compare@?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@QBEHIIPBDI@Z @ 0x001A6060
// match: ?sub_1A5F80@type_505188@@QBE_NABU1@@Z @ 0x001A5F80
bool type_505188::sub_1A5F80(const type_505188 &arg_0) const
{
    return unk_04 < arg_0.sub_1A5F60();
}

// match: ?sub_1A5FC0@type_505188@@QBE_NABU1@@Z @ 0x001A5FC0
bool type_505188::sub_1A5FC0(const type_505188 &arg_0) const
{
    return unk_04 == arg_0.sub_1A5F60();
}

// match: ?sub_1A5FF0@type_505188@@QBE_NXZ @ 0x001A5FF0
bool type_505188::sub_1A5FF0() const
{
    return unk_04.empty();
}
