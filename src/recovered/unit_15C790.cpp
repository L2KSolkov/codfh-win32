// The NPC weapons' settings (type_4D53F8, 128 of them at dword_4D53F8):
// their set-up and shutdown, lookup by index and by name, and setters.

#include "rw/ostypes.h"
#include "types/type_4D53F8.h"
#include "types/type_72810.h"
#include "game/gameloop.h"
#include <string.h>
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: __ehhandler$??0type_4D53F8@@QAE@XZ>1>8 @ 0x0041E01C
// match: __ehhandler$??0type_4D53F8@@QAE@XZ>1 @ 0x0041E024
// match: __ehhandler$??1type_4D53F8@@QAE@XZ>1>8 @ 0x0041E040
// match: __ehhandler$??1type_4D53F8@@QAE@XZ>1 @ 0x0041E048
// match: .CRT$XCU+0 @ 0x00427128

// match: _$E1 @ 0x0030BC10
// match: _$E2 @ 0x0030E860

// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).

type_4D53F8 dword_4D53F8[128];

// match: ?sub_15C790@@YAXXZ @ 0x0015C790
// Clears every NPC weapon's settings (the game's set-up, sub_D6820).
void sub_15C790()
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 128; var_4++)
        dword_4D53F8[var_4].sub_15C980();
}

// match: ?sub_15C7D0@@YAXXZ @ 0x0015C7D0
// Marks every one unready (the game's shutdown, sub_D7040).
void sub_15C7D0()
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 128; var_4++)
        dword_4D53F8[var_4].sub_15CA80();
}

// match: ??0type_4D53F8@@QAE@XZ @ 0x0015C810
// match: __ehhandler$??0type_4D53F8@@QAE@XZ-0xB @ 0x00301DD0
// match: __ehhandler$??0type_4D53F8@@QAE@XZ @ 0x00301DDB
type_4D53F8::type_4D53F8()
{
    unk_44 = 0;
}

// match: ??1type_4D53F8@@QAE@XZ @ 0x0015C920
// match: __ehhandler$??1type_4D53F8@@QAE@XZ-0xB @ 0x00301DF0
// match: __ehhandler$??1type_4D53F8@@QAE@XZ @ 0x00301DFB
type_4D53F8::~type_4D53F8()
{
    if (unk_44)
        sub_15CA80();
}

// match: ?sub_15C980@type_4D53F8@@QAEHXZ @ 0x0015C980
RwInt32 type_4D53F8::sub_15C980()
{
    unk_44 = 0;
    unk_48.unk_00 = 0;
    unk_48.unk_04 = 0;
    unk_58.unk_00 = 0;
    unk_58.unk_04 = 0;
    unk_74 = 0;
    unk_7C = 0;
    unk_118 = 0.0f;
    unk_94.unk_04_r = 0.0f;
    unk_80 = 0;
    unk_84 = 0;
    unk_94.unk_40_r = 0.0f;
    unk_94.unk_3C = 1;
    unk_94.unk_44 = 0;
    unk_94.unk_48 = 0;
    memset(unk_94.unk_08, 0, sizeof(unk_94.unk_08));
    unk_44 = 0;
    unk_30 = 0;
    unk_34 = 0;
    return 1;
}

// match: ?sub_15CA80@type_4D53F8@@QAEHXZ @ 0x0015CA80
RwInt32 type_4D53F8::sub_15CA80()
{
    unk_44 = 0;
    return 1;
}

// match: ?sub_15CAA0@type_4D53F8@@QAEHXZ @ 0x0015CAA0
RwInt32 type_4D53F8::sub_15CAA0()
{
    unk_44 = 1;
    return 1;
}

// match: ?sub_15CAC0@type_4D53F8@@QAEXXZ @ 0x0015CAC0
void type_4D53F8::sub_15CAC0()
{
    sub_198900((type_3DF8D8_04 *)&unk_48, 26, 0, 0, 0, 0);
    if (unk_74)
        sub_198900((type_3DF8D8_04 *)&unk_58, 3, 0, 0, 0, 0);
}

// match: ?sub_15CB10@@YAPAUtype_4D53F8@@H@Z @ 0x0015CB10
type_4D53F8 *sub_15CB10(RwInt32 arg_0)
{
    if (arg_0 < 0 || arg_0 >= 128)
        return 0;
    return &dword_4D53F8[arg_0];
}

// match: ?sub_15CB40@@YAHPBUtype_3DF8D8_04@@@Z @ 0x0015CB40
RwInt32 sub_15CB40(const type_3DF8D8_04 *arg_0)
{
    RwInt32 var_4;

    if (arg_0->unk_00 == 0 && arg_0->unk_04 == 0)
        return -1;
    if (arg_0->unk_00 == (RwUInt32)-1 && arg_0->unk_04 == (RwUInt32)-1)
        return -1;
    for (var_4 = 0; var_4 < 128; var_4++)
    {
        if (dword_4D53F8[var_4].unk_48.unk_00 == arg_0->unk_00 && dword_4D53F8[var_4].unk_48.unk_04 == arg_0->unk_04)
            return var_4;
    }
    return -1;
}

// match: ?sub_15CBD0@type_4D53F8@@QAEXM@Z @ 0x0015CBD0
void type_4D53F8::sub_15CBD0(RwReal arg_0)
{
    unk_94.unk_40_r = arg_0;
}

// match: ?sub_15CBF0@type_4D53F8@@QAEXH@Z @ 0x0015CBF0
void type_4D53F8::sub_15CBF0(RwInt32 arg_0)
{
    unk_94.unk_44 = arg_0;
}

// match: ?sub_15CC10@type_4D53F8@@QAEXH@Z @ 0x0015CC10
void type_4D53F8::sub_15CC10(RwInt32 arg_0)
{
    unk_94.unk_48 = arg_0;
}

// match: ?sub_15CC30@type_4D53F8@@QAEXI@Z @ 0x0015CC30
void type_4D53F8::sub_15CC30(RwUInt32 arg_0)
{
    unk_94.unk_04_r = (RwReal)arg_0;
}

// match: ?sub_15CC60@type_4D53F8@@QAEXM@Z @ 0x0015CC60
void type_4D53F8::sub_15CC60(RwReal arg_0)
{
    unk_94.unk_4C_r = arg_0;
}

// match: ?sub_15CC80@type_4D53F8@@QAEXM@Z @ 0x0015CC80
void type_4D53F8::sub_15CC80(RwReal arg_0)
{
    unk_E4 = arg_0;
}

// match: ?sub_15CCA0@type_4D53F8@@QAEXH@Z @ 0x0015CCA0
void type_4D53F8::sub_15CCA0(RwInt32 arg_0)
{
    unk_74 = arg_0;
    if (arg_0)
        unk_94.unk_00 = 3;
    else
        unk_94.unk_00 = 0;
}
