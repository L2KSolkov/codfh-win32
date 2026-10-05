/*
 * The find session page (in-game menu 1, game/livemenu.h): its search
 * settings reset, the search started with them, and the minimum players
 * kept below the players picked. The constructor (sub_2062B0) unwinds its
 * text temporaries through the library's out-of-line string destructor
 * (sub_43900) and is not matched yet (docs/questions.md).
 */
#include "game/livemenu.h"
#include "game/ingamemenu.h"

using namespace kujuUI;

// match: ??_Gtype_2062B0@@UAEPAXI@Z @ 0x002066B0
// match: ??1type_2062B0@@UAE@XZ @ 0x002066E0
type_2062B0::~type_2062B0()
{
}

// match: ?vf_03C@type_2062B0@@UAEXXZ @ 0x00206830
void type_2062B0::vf_03C()
{
    type_2049D0::vf_03C();
    sub_206850();
}

// match: ?sub_206850@type_2062B0@@QAEXXZ @ 0x00206850
void type_2062B0::sub_206850()
{
    type_505188 var_54;
    type_211860_key var_10 = { &var_54 };

    unk_1E8.sub_201EC0(var_10);
    unk_1C8.sub_201EC0((type_210430_value)0x20);
    unk_208.sub_201EC0((type_2138C0_value)8);
    unk_228.sub_1E7BB0(0);
    unk_2A4.sub_201EC0((type_214C30_value)2);
    unk_2C4.sub_201EC0((type_214C30_value)2);
    unk_2E4.sub_201EC0((type_214C30_value)2);
}

// match: ?sub_206960@type_2062B0@@QAEXXZ @ 0x00206960
void type_2062B0::sub_206960()
{
    type_505188 *var_4 = unk_1E8.sub_1FD030().get_unk_00();

    sub_1C3D80(var_4->sub_1A5FF0() ? -1 : var_4->sub_1EE9D0());
    unk_4FDBB0.unk_00 = unk_1C8.get_value();
    dword_4F6300 = unk_208.get_value();
    dword_4FDAA0 = unk_228.get_unk_08();
    RwInt32 var_10 = 4;
    RwInt32 var_8 = unk_2A4.sub_1FD030();
    if (var_8 == 1)
        var_10 = 2;
    else if (var_8 == 0)
        var_10 = 0;
    dword_42CBA8 = var_10;
    RwInt32 var_14 = 4;
    var_8 = unk_2C4.sub_1FD030();
    if (var_8 == 1)
        var_14 = 2;
    else if (var_8 == 0)
        var_14 = 1;
    dword_42CBAC = var_14;
    RwInt32 var_C = 4;
    var_8 = unk_2E4.sub_1FD030();
    if (var_8 == 1)
        var_C = 2;
    else if (var_8 == 0)
        var_C = 1;
    dword_42CBB0 = var_C;
    sub_1FC310()->sub_1FBDA0(sub_2046C0(7));
}

// match: ?sub_206AE0@type_2062B0@@QAEXXZ @ 0x00206AE0
void type_2062B0::sub_206AE0()
{
    if (unk_188)
    {
        RwInt32 var_4;

        switch (unk_208.sub_1FD030())
        {
        case 1:
            var_4 = 4;
            break;
        case 2:
            var_4 = 8;
            break;
        default:
            var_4 = 0x10;
        }
        unk_228.sub_1E7BD0(var_4 - 1);
    }
}
