// Split from unit_0863C0.cpp at 0x088830, where the image starts another object (the voice
// manager, type_8A980, its constructor first): its .rdata begins at 0x3D4F34 with its own
// 16.666666, the unreferenced constant every game object starts its constants with (PLAN M7).

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rw/ostypes.h"
#include "game/functions.h"
#include "types/soundbank.h"
#include "types/musicplayer.h"
#include "rw/bastream.h"
#include "types/type_3DF8D8.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003D4F34
extern const RwReal flt_3D4F34 = 16.666666f;

// match: ?flt_3D4F34@@3MB @ 0x003D4F34


// match: __ehhandler$??1type_8A980@@QAE@XZ>1>8 @ 0x0041B700
// match: __ehhandler$??1type_8A980@@QAE@XZ>1 @ 0x0041B708
// match: ??_C@_0CK@NGOKEADA@Ambience2?5sound?5disabled?5in?5Glob@ @ 0x003D4F38
// match: ??_C@_0CK@LLGMLDGK@Ambience1?5sound?5disabled?5in?5Glob@ @ 0x003D4F64
// match: ??_C@_0CH@LMABOLPB@Debris?5sound?5disabled?5in?5GlobalS@ @ 0x003D4F90
// match: ??_C@_0CN@GBLEFBOC@WeaponsFoley?5sound?5disabled?5in?5G@ @ 0x003D4FB8
// match: ??_C@_0CJ@GEOABMLB@Vehicles?5sound?5disabled?5in?5Globa@ @ 0x003D4FE8
// match: ??_C@_0CM@MHLJPLNN@WeaponsFire?5sound?5disabled?5in?5Gl@ @ 0x003D5014
// match: ??_C@_0CG@OIOFOHEJ@Foley?5sound?5disabled?5in?5GlobalSo@ @ 0x003D5040
// match: ??_C@_0CH@CJPINAMK@Dialog?5sound?5disabled?5in?5GlobalS@ @ 0x003D5068
// match: ??_C@_0DM@NAOLKKKM@AUDIO?3?3VoiceManager?3?3?5While?5tryi@ @ 0x003D5090
// match: ??_C@_0L@FLNGNKIA@0x?$CFX?0?50x?$CFX?$AA@ @ 0x003D50CC

// match: ??0type_8A980@@QAE@XZ @ 0x00088830
// sp-match: ??0type_8A980@@QAE@XZ @ 0x0006DCE0
type_8A980::type_8A980()
{
    unk_04[0] = 0;
    unk_04[1] = 0;
    unk_04[2] = 0;
    unk_04[3] = 0;
    unk_04[4] = 0;
    unk_04[5] = 0;
    unk_04[6] = 0;
    unk_04[7] = 0;
    unk_00 = 0;
    unk_44[0] = 0;
    unk_44[1] = 0;
    unk_44[2] = 0;
    unk_44[3] = 0;
    unk_44[4] = 0;
    unk_44[5] = 0;
    unk_44[6] = 0;
    unk_44[7] = 0;
    unk_44[8] = 0;
    unk_44[9] = 0;
    unk_44[10] = 0;
    unk_44[11] = 0;
    unk_44[12] = 0;
    unk_44[13] = 0;
    unk_44[14] = 0;
    unk_44[15] = 0;
}
// Takes the virtual voice lists arg_0 (arg_4 only known by width): a voice
// for each slot, each registered in dword_44C4E8.
// match: ?sub_88950@type_8A980@@QAEXPAUtype_83A70@@H@Z @ 0x00088950
// sp-match: ?sub_88950@type_8A980@@QAEXPAUtype_83A70@@H@Z @ 0x0006DD40
void type_8A980::sub_88950(type_83A70 *arg_0, RwInt32 arg_4)
{
    RwInt32 var_4;
    RwInt32 local_8;

    local_8 = 0;
    unk_44[0] = arg_0->unk_00;
    unk_44[1] = arg_0->unk_08;
    unk_44[2] = arg_0->unk_10;
    unk_44[3] = arg_0->unk_18;
    unk_44[4] = arg_0->unk_20;
    unk_44[5] = arg_0->unk_28;
    unk_44[6] = arg_0->unk_30;
    unk_44[7] = arg_0->unk_38;
    unk_04[0] = arg_0->unk_04;
    unk_04[1] = arg_0->unk_0C;
    unk_04[2] = arg_0->unk_14;
    unk_04[3] = arg_0->unk_1C;
    unk_04[4] = arg_0->unk_24;
    unk_04[5] = arg_0->unk_2C;
    unk_04[6] = arg_0->unk_34;
    unk_04[7] = arg_0->unk_3C;
    if (unk_44[0])
    {
        for (var_4 = 0; var_4 < unk_44[0]; var_4++)
        {
            unk_04[0][var_4] = (RwInt32)RwaStreamCreate(0, 0, 4, 0, 0);
            dword_44C4E8[sub_83D30()] = unk_04[0][var_4];
        }
    }
    else
    {
        unk_04[0] = 0;
    }
    if (unk_44[1])
    {
        for (var_4 = 0; var_4 < unk_44[1]; var_4++)
        {
            unk_04[1][var_4] = (RwInt32)RwaStreamCreate(0, 0, 4, 0, 0);
            dword_44C4E8[sub_83D30()] = unk_04[1][var_4];
        }
    }
    else
    {
        unk_04[1] = 0;
    }
    if (unk_44[2])
    {
        for (var_4 = 0; var_4 < unk_44[2]; var_4++)
        {
            unk_04[2][var_4] = (RwInt32)RwaStreamCreate(0, 0, 4, 0, 0);
            dword_44C4E8[sub_83D30()] = unk_04[2][var_4];
        }
    }
    else
    {
        unk_04[2] = 0;
    }
    if (unk_44[3])
    {
        for (var_4 = 0; var_4 < unk_44[3]; var_4++)
        {
            unk_04[3][var_4] = (RwInt32)RwaStreamCreate(0, 0, 4, 0, 0);
            dword_44C4E8[sub_83D30()] = unk_04[3][var_4];
        }
    }
    else
    {
        unk_04[3] = 0;
    }
    if (unk_44[4])
    {
        for (var_4 = 0; var_4 < unk_44[4]; var_4++)
        {
            unk_04[4][var_4] = (RwInt32)RwaStreamCreate(0, 0, 4, 0, 0);
            dword_44C4E8[sub_83D30()] = unk_04[4][var_4];
        }
    }
    else
    {
        unk_04[4] = 0;
    }
    if (unk_44[5])
    {
        for (var_4 = 0; var_4 < unk_44[5]; var_4++)
        {
            unk_04[5][var_4] = (RwInt32)RwaStreamCreate(0, 0, 4, 0, 0);
            dword_44C4E8[sub_83D30()] = unk_04[5][var_4];
        }
    }
    else
    {
        unk_04[5] = 0;
    }
    if (unk_44[6])
    {
        for (var_4 = 0; var_4 < unk_44[6]; var_4++)
        {
            unk_04[6][var_4] = (RwInt32)RwaStreamCreate(0, 0, 4, 0, 0);
            dword_44C4E8[sub_83D30()] = unk_04[6][var_4];
        }
    }
    else
    {
        unk_04[6] = 0;
    }
    if (unk_44[7])
    {
        for (var_4 = 0; var_4 < unk_44[7]; var_4++)
        {
            unk_04[7][var_4] = (RwInt32)RwaStreamCreate(0, 0, 4, 0, 0);
            dword_44C4E8[sub_83D30()] = unk_04[7][var_4];
        }
    }
    else
    {
        unk_04[7] = 0;
    }
    unk_00 = 0;
    if (local_8 > dword_4B2070)
    {
        dword_4B2070 = local_8;
    }
}
// match: ??1type_8A980@@QAE@XZ @ 0x00088DA0
// match: __ehhandler$??1type_8A980@@QAE@XZ-0xB @ 0x002FFA10
// match: __ehhandler$??1type_8A980@@QAE@XZ @ 0x002FFA1B
// sp-match: ??1type_8A980@@QAE@XZ @ 0x0006F1F0
type_8A980::~type_8A980()
{
    sub_88DF0();
}
// Lets every voice go: lists 7 to 1 through sub_8A910, list 0's emitters
// stopped and released first; then the pool and the banks this still holds.
// match: ?sub_88DF0@type_8A980@@QAEXXZ @ 0x00088DF0
// sp-match: ?sub_88DF0@type_8A980@@QAEXXZ @ 0x0006EE20
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_8A980::sub_88DF0()
{
    RwInt32 var_8;
    RwInt32 l4;

    if (!(var_8 = unk_44[5] + unk_44[0] + unk_44[1] + unk_44[3] + unk_44[2] + unk_44[4] + unk_44[6] + unk_44[7]))
    {
        return;
    }
    if (var_8 == 0)
    {
        return;
    }
    if (unk_04[7])
    {
        for (l4 = unk_44[7] - 1; l4 >= 0; l4--)
        {
            if (unk_04[7][l4])
            {
                sub_8A910(unk_04[7][l4]);
                sub_83D70(unk_04[7][l4]);
                DSPHandle_Stop(reinterpret_cast<void *>(unk_04[7][l4]), 0, 0);
                if (dword_44E8B4 == unk_04[7][l4])
                {
                    dword_44E8B4 = 0;
                }
                unk_04[7][l4] = 0;
            }
        }
        unk_04[7] = 0;
        unk_44[7] = 0;
    }
    if (unk_04[6])
    {
        for (l4 = unk_44[6] - 1; l4 >= 0; l4--)
        {
            if (unk_04[6][l4])
            {
                sub_8A910(unk_04[6][l4]);
                sub_83D70(unk_04[6][l4]);
                DSPHandle_Stop(reinterpret_cast<void *>(unk_04[6][l4]), 0, 0);
                if (dword_44E8B4 == unk_04[6][l4])
                {
                    dword_44E8B4 = 0;
                }
                unk_04[6][l4] = 0;
            }
        }
        unk_04[6] = 0;
        unk_44[6] = 0;
    }
    if (unk_04[5])
    {
        for (l4 = unk_44[5] - 1; l4 >= 0; l4--)
        {
            if (unk_04[5][l4])
            {
                sub_8A910(unk_04[5][l4]);
                sub_83D70(unk_04[5][l4]);
                DSPHandle_Stop(reinterpret_cast<void *>(unk_04[5][l4]), 0, 0);
                if (dword_44E8B4 == unk_04[5][l4])
                {
                    dword_44E8B4 = 0;
                }
                unk_04[5][l4] = 0;
            }
        }
        unk_04[5] = 0;
        unk_44[5] = 0;
    }
    if (unk_04[4])
    {
        for (l4 = unk_44[4] - 1; l4 >= 0; l4--)
        {
            if (unk_04[4][l4])
            {
                sub_8A910(unk_04[4][l4]);
                sub_83D70(unk_04[4][l4]);
                DSPHandle_Stop(reinterpret_cast<void *>(unk_04[4][l4]), 0, 0);
                if (dword_44E8B4 == unk_04[4][l4])
                {
                    dword_44E8B4 = 0;
                }
                unk_04[4][l4] = 0;
            }
        }
        unk_04[4] = 0;
        unk_44[4] = 0;
    }
    if (unk_04[3])
    {
        for (l4 = unk_44[3] - 1; l4 >= 0; l4--)
        {
            if (unk_04[3][l4])
            {
                sub_8A910(unk_04[3][l4]);
                sub_83D70(unk_04[3][l4]);
                DSPHandle_Stop(reinterpret_cast<void *>(unk_04[3][l4]), 0, 0);
                if (dword_44E8B4 == unk_04[3][l4])
                {
                    dword_44E8B4 = 0;
                }
                unk_04[3][l4] = 0;
            }
        }
        unk_04[3] = 0;
        unk_44[3] = 0;
    }
    if (unk_04[2])
    {
        for (l4 = unk_44[2] - 1; l4 >= 0; l4--)
        {
            if (unk_04[2][l4])
            {
                sub_8A910(unk_04[2][l4]);
                sub_83D70(unk_04[2][l4]);
                DSPHandle_Stop(reinterpret_cast<void *>(unk_04[2][l4]), 0, 0);
                if (dword_44E8B4 == unk_04[2][l4])
                {
                    dword_44E8B4 = 0;
                }
                unk_04[2][l4] = 0;
            }
        }
        unk_04[2] = 0;
        unk_44[2] = 0;
    }
    if (unk_04[1])
    {
        for (l4 = unk_44[1] - 1; l4 >= 0; l4--)
        {
            if (unk_04[1][l4])
            {
                sub_8A910(unk_04[1][l4]);
                sub_83D70(unk_04[1][l4]);
                DSPHandle_Stop(reinterpret_cast<void *>(unk_04[1][l4]), 0, 0);
                if (dword_44E8B4 == unk_04[1][l4])
                {
                    dword_44E8B4 = 0;
                }
                unk_04[1][l4] = 0;
            }
        }
        unk_04[1] = 0;
        unk_44[1] = 0;
    }
    if (unk_04[0])
    {
        for (l4 = unk_44[0] - 1; l4 >= 0; l4--)
        {
            if (unk_04[0][l4])
            {
                SoundEmitter_Stop((type_44C4E8 *)unk_04[0][l4], 0);
                sub_23B8F0((type_44C4E8 *)unk_04[0][l4], 0);
                sub_83D70(unk_04[0][l4]);
                DSPHandle_Stop(reinterpret_cast<void *>(unk_04[0][l4]), 0, 0);
                if (dword_44E8B4 == unk_04[0][l4])
                {
                    dword_44E8B4 = 0;
                }
                unk_04[0][l4] = 0;
            }
        }
        unk_04[0] = 0;
        unk_44[0] = 0;
    }
    if (unk_24.get_unk_10())
    {
        unk_24.sub_16C6E0(0);
        unk_24.sub_16C4D0(1);
    }
    for (l4 = 0; l4 < 0x14; l4++)
    {
        if (dword_4B1CA0[l4].unk_04 && dword_4B1CA0[l4].unk_14 == this)
        {
            while (dword_4B1CA0[l4].unk_04)
            {
                dword_4B1CA0[l4].sub_85730();
            }
            dword_4B1CA0[l4].unk_00 = 0;
            dword_4B1CA0[l4].unk_14 = 0;
        }
    }
}
// Moves every playing voice of the lists to arg_0, telling the library of
// those it holds a handle for.
// match: ?sub_89540@type_8A980@@QAEXPAURwV3d@@@Z @ 0x00089540
// sp-match: ?sub_89540@type_8A980@@QAEXPAURwV3d@@@Z @ 0x0006DFE0
void type_8A980::sub_89540(RwV3d *arg_0)
{
    RwInt32 var_4;

    sub_85800(&unk_00);
    if (unk_04[0])
    {
        for (var_4 = 0; var_4 < unk_44[0]; var_4++)
        {
            if (unk_04[0][var_4] && ((((type_44C4E8 *)unk_04[0][var_4])->unk_34 & 2) != 0) != 0)
            {
                do
                {
                    ((type_44C4E8 *)unk_04[0][var_4])->unk_58 = *arg_0;
                    if (((type_44C4E8 *)unk_04[0][var_4])->unk_30)
                    {
                        Behavior_DispatchCallback(((type_44C4E8 *)unk_04[0][var_4])->unk_30, 0, 1, arg_0);
                    }
                } while (0);
            }
        }
    }
    if (unk_04[1])
    {
        for (var_4 = 0; var_4 < unk_44[1]; var_4++)
        {
            if (unk_04[1][var_4] && ((((type_44C4E8 *)unk_04[1][var_4])->unk_34 & 2) != 0) != 0)
            {
                do
                {
                    ((type_44C4E8 *)unk_04[1][var_4])->unk_58 = *arg_0;
                    if (((type_44C4E8 *)unk_04[1][var_4])->unk_30)
                    {
                        Behavior_DispatchCallback(((type_44C4E8 *)unk_04[1][var_4])->unk_30, 0, 1, arg_0);
                    }
                } while (0);
            }
        }
    }
    if (unk_04[2])
    {
        for (var_4 = 0; var_4 < unk_44[2]; var_4++)
        {
            if (unk_04[2][var_4] && ((((type_44C4E8 *)unk_04[2][var_4])->unk_34 & 2) != 0) != 0)
            {
                do
                {
                    ((type_44C4E8 *)unk_04[2][var_4])->unk_58 = *arg_0;
                    if (((type_44C4E8 *)unk_04[2][var_4])->unk_30)
                    {
                        Behavior_DispatchCallback(((type_44C4E8 *)unk_04[2][var_4])->unk_30, 0, 1, arg_0);
                    }
                } while (0);
            }
        }
    }
    if (unk_04[3])
    {
        for (var_4 = 0; var_4 < unk_44[3]; var_4++)
        {
            if (unk_04[3][var_4] && ((((type_44C4E8 *)unk_04[3][var_4])->unk_34 & 2) != 0) != 0)
            {
                do
                {
                    ((type_44C4E8 *)unk_04[3][var_4])->unk_58 = *arg_0;
                    if (((type_44C4E8 *)unk_04[3][var_4])->unk_30)
                    {
                        Behavior_DispatchCallback(((type_44C4E8 *)unk_04[3][var_4])->unk_30, 0, 1, arg_0);
                    }
                } while (0);
            }
        }
    }
    if (unk_04[4])
    {
        for (var_4 = 0; var_4 < unk_44[4]; var_4++)
        {
            if (unk_04[4][var_4] && ((((type_44C4E8 *)unk_04[4][var_4])->unk_34 & 2) != 0) != 0)
            {
                do
                {
                    ((type_44C4E8 *)unk_04[4][var_4])->unk_58 = *arg_0;
                    if (((type_44C4E8 *)unk_04[4][var_4])->unk_30)
                    {
                        Behavior_DispatchCallback(((type_44C4E8 *)unk_04[4][var_4])->unk_30, 0, 1, arg_0);
                    }
                } while (0);
            }
        }
    }
    if (unk_04[5])
    {
        for (var_4 = 0; var_4 < unk_44[5]; var_4++)
        {
            if (unk_04[5][var_4] && ((((type_44C4E8 *)unk_04[5][var_4])->unk_34 & 2) != 0) != 0)
            {
                do
                {
                    ((type_44C4E8 *)unk_04[5][var_4])->unk_58 = *arg_0;
                    if (((type_44C4E8 *)unk_04[5][var_4])->unk_30)
                    {
                        Behavior_DispatchCallback(((type_44C4E8 *)unk_04[5][var_4])->unk_30, 0, 1, arg_0);
                    }
                } while (0);
            }
        }
    }
    if (unk_04[6])
    {
        for (var_4 = 0; var_4 < unk_44[6]; var_4++)
        {
            if (unk_04[6][var_4] && ((((type_44C4E8 *)unk_04[6][var_4])->unk_34 & 2) != 0) != 0)
            {
                do
                {
                    ((type_44C4E8 *)unk_04[6][var_4])->unk_58 = *arg_0;
                    if (((type_44C4E8 *)unk_04[6][var_4])->unk_30)
                    {
                        Behavior_DispatchCallback(((type_44C4E8 *)unk_04[6][var_4])->unk_30, 0, 1, arg_0);
                    }
                } while (0);
            }
        }
    }
    if (unk_04[7])
    {
        for (var_4 = 0; var_4 < unk_44[7]; var_4++)
        {
            if (unk_04[7][var_4] && ((((type_44C4E8 *)unk_04[7][var_4])->unk_34 & 2) != 0) != 0)
            {
                do
                {
                    ((type_44C4E8 *)unk_04[7][var_4])->unk_58 = *arg_0;
                    if (((type_44C4E8 *)unk_04[7][var_4])->unk_30)
                    {
                        Behavior_DispatchCallback(((type_44C4E8 *)unk_04[7][var_4])->unk_30, 0, 1, arg_0);
                    }
                } while (0);
            }
        }
    }
}
// A voice from the list arg_0: the first that is not playing, or else the
// next in turn, stopped for the taker (list 0 only gives one up when arg_4
// is set or it was asked for as 0, not 8, and the vehicles only with arg_4).
// match: ?sub_89B00@type_8A980@@QAEHHH@Z @ 0x00089B00
// sp-match: ?sub_89B00@type_8A980@@QAEHHH@Z @ 0x0006E2C0
RwInt32 type_8A980::sub_89B00(RwInt32 arg_0, RwInt32 arg_4)
{
    RwInt32 var_4;

    switch (arg_0)
    {
    case 0:
    case 8:
        if (unk_04[0])
        {
            if (dword_44E840)
            {
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
                // single player compiles the debug print out (SP 0x6E2C0)
                if (dword_44E860 && dword_44E86C)
                {
                    sub_19A750("Dialog sound disabled in GlobalSounds!");
                }
#endif
                return 0;
            }
            for (var_4 = 0; var_4 < unk_44[0]; var_4++)
            {
                if (unk_04[0][var_4] && ((((type_44C4E8 *)unk_04[0][var_4])->unk_34 & 2) != 0) == 0)
                {
                    return unk_04[0][var_4];
                }
            }
            if (arg_4 || !arg_0)
            {
                unk_64[0]++;
                if (unk_64[0] >= unk_44[0])
                {
                    unk_64[0] = 0;
                }
                if (unk_04[0][unk_64[0]])
                {
                    SoundEmitter_Stop((type_44C4E8 *)unk_04[0][unk_64[0]], 0);
                    sub_3C6C0(unk_04[0][unk_64[0]]);
                    return unk_04[0][unk_64[0]];
                }
            }
        }
        break;
    case 1:
        if (unk_04[1])
        {
            if (dword_44E844)
            {
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
                if (dword_44E860 && dword_44E86C)
                {
                    sub_19A750("Foley sound disabled in GlobalSounds!");
                }
#endif
                return 0;
            }
            for (var_4 = 0; var_4 < unk_44[1]; var_4++)
            {
                if (unk_04[1][var_4] && ((((type_44C4E8 *)unk_04[1][var_4])->unk_34 & 2) != 0) == 0)
                {
                    return unk_04[1][var_4];
                }
            }
            unk_64[1]++;
            if (unk_64[1] >= unk_44[1])
            {
                unk_64[1] = 0;
            }
            if (unk_04[1][unk_64[1]])
            {
                SoundEmitter_Stop((type_44C4E8 *)unk_04[1][unk_64[1]], 0);
                sub_3C6C0(unk_04[1][unk_64[1]]);
                return unk_04[1][unk_64[1]];
            }
        }
        break;
    case 2:
        if (unk_04[2])
        {
            if (dword_44E848)
            {
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
                if (dword_44E860 && dword_44E86C)
                {
                    sub_19A750("WeaponsFire sound disabled in GlobalSounds!");
                }
#endif
                return 0;
            }
            for (var_4 = 0; var_4 < unk_44[2]; var_4++)
            {
                if (unk_04[2][var_4] && ((((type_44C4E8 *)unk_04[2][var_4])->unk_34 & 2) != 0) == 0)
                {
                    return unk_04[2][var_4];
                }
            }
            unk_64[2]++;
            if (unk_64[2] >= unk_44[2])
            {
                unk_64[2] = 0;
            }
            if (unk_04[2][unk_64[2]])
            {
                SoundEmitter_Stop((type_44C4E8 *)unk_04[2][unk_64[2]], 0);
                sub_3C6C0(unk_04[2][unk_64[2]]);
                return unk_04[2][unk_64[2]];
            }
        }
        break;
    case 3:
        if (unk_04[3])
        {
            if (dword_44E84C)
            {
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
                if (dword_44E860 && dword_44E86C)
                {
                    sub_19A750("Vehicles sound disabled in GlobalSounds!");
                }
#endif
                return 0;
            }
            for (var_4 = 0; var_4 < unk_44[3]; var_4++)
            {
                if (unk_04[3][var_4] && ((((type_44C4E8 *)unk_04[3][var_4])->unk_34 & 2) != 0) == 0)
                {
                    return unk_04[3][var_4];
                }
            }
            if (arg_4)
            {
                unk_64[3]++;
                if (unk_64[3] >= unk_44[3])
                {
                    unk_64[3] = 0;
                }
                if (unk_04[3][unk_64[3]])
                {
                    SoundEmitter_Stop((type_44C4E8 *)unk_04[3][unk_64[3]], 0);
                    sub_3C6C0(unk_04[3][unk_64[3]]);
                    return unk_04[3][unk_64[3]];
                }
            }
        }
        break;
    case 4:
        if (unk_04[4])
        {
            if (dword_44E850)
            {
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
                if (dword_44E860 && dword_44E86C)
                {
                    sub_19A750("WeaponsFoley sound disabled in GlobalSounds!");
                }
#endif
                return 0;
            }
            for (var_4 = 0; var_4 < unk_44[4]; var_4++)
            {
                if (unk_04[4][var_4] && ((((type_44C4E8 *)unk_04[4][var_4])->unk_34 & 2) != 0) == 0)
                {
                    return unk_04[4][var_4];
                }
            }
            unk_64[4]++;
            if (unk_64[4] >= unk_44[4])
            {
                unk_64[4] = 0;
            }
            if (unk_04[4][unk_64[4]])
            {
                SoundEmitter_Stop((type_44C4E8 *)unk_04[4][unk_64[4]], 0);
                sub_3C6C0(unk_04[4][unk_64[4]]);
                return unk_04[4][unk_64[4]];
            }
        }
        break;
    case 5:
        if (unk_04[5])
        {
            if (dword_44E854)
            {
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
                if (dword_44E860 && dword_44E86C)
                {
                    sub_19A750("Debris sound disabled in GlobalSounds!");
                }
#endif
                return 0;
            }
            for (var_4 = 0; var_4 < unk_44[5]; var_4++)
            {
                if (unk_04[5][var_4] && ((((type_44C4E8 *)unk_04[5][var_4])->unk_34 & 2) != 0) == 0)
                {
                    return unk_04[5][var_4];
                }
            }
            unk_64[5]++;
            if (unk_64[5] >= unk_44[5])
            {
                unk_64[5] = 0;
            }
            if (unk_04[5][unk_64[5]])
            {
                SoundEmitter_Stop((type_44C4E8 *)unk_04[5][unk_64[5]], 0);
                sub_3C6C0(unk_04[5][unk_64[5]]);
                return unk_04[5][unk_64[5]];
            }
        }
        break;
    case 6:
        if (unk_04[6])
        {
            if (dword_44E858)
            {
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
                if (dword_44E860 && dword_44E86C)
                {
                    sub_19A750("Ambience1 sound disabled in GlobalSounds!");
                }
#endif
                return 0;
            }
            for (var_4 = 0; var_4 < unk_44[6]; var_4++)
            {
                if (unk_04[6][var_4] && ((((type_44C4E8 *)unk_04[6][var_4])->unk_34 & 2) != 0) == 0)
                {
                    return unk_04[6][var_4];
                }
            }
            unk_64[6]++;
            if (unk_64[6] >= unk_44[6])
            {
                unk_64[6] = 0;
            }
            if (unk_04[6][unk_64[6]])
            {
                SoundEmitter_Stop((type_44C4E8 *)unk_04[6][unk_64[6]], 0);
                sub_3C6C0(unk_04[6][unk_64[6]]);
                return unk_04[6][unk_64[6]];
            }
        }
        break;
    case 7:
        if (unk_04[7])
        {
            if (dword_44E85C)
            {
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
                if (dword_44E860 && dword_44E86C)
                {
                    sub_19A750("Ambience2 sound disabled in GlobalSounds!");
                }
#endif
                return 0;
            }
            for (var_4 = 0; var_4 < unk_44[7]; var_4++)
            {
                if (unk_04[7][var_4] && ((((type_44C4E8 *)unk_04[7][var_4])->unk_34 & 2) != 0) == 0)
                {
                    return unk_04[7][var_4];
                }
            }
            unk_64[7]++;
            if (unk_64[7] >= unk_44[7])
            {
                unk_64[7] = 0;
            }
            if (unk_04[7][unk_64[7]])
            {
                SoundEmitter_Stop((type_44C4E8 *)unk_04[7][unk_64[7]], 0);
                sub_3C6C0(unk_04[7][unk_64[7]]);
                return unk_04[7][unk_64[7]];
            }
        }
        break;
    }
    return 0;
}
// Plays the sound arg_0 with arg_4 on a voice of the list arg_8: its
// chance, then its pitch and volume with their random spreads (a music
// sound's are fixed tenths of it), ducked or scaled by the volumes unless
// arg_10 is set, its loop flag and library parameters 2 and 3.
// match: ?sub_8A440@type_8A980@@QAEHPAUtype_199010@@HHHH@Z @ 0x0008A440
// sp-match: ?sub_8A440@type_8A980@@QAEHPAUtype_199010@@HHHH@Z @ 0x0006E7B0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_8A980::sub_8A440(type_199010 *arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C,
                              RwInt32 arg_10)
{
    RwChar var_120[0x100];
    RwReal slot_1C;
    RwInt32 var_18;
    RwInt32 var_14;
    RwReal lv_10;
    RwInt32 var_C;
    RwInt32 bp_8;
    RwInt32 bp_4;

    var_18 = 0;
    if (!arg_4)
    {
        return 0;
    }
    var_18 = sub_89B00(arg_8, arg_C);
    if (!var_18)
    {
        if (dword_44E860 && dword_44E86C)
        {
            sprintf(var_120, "AUDIO::VoiceManager:: While trying to play alias 0x%X, 0x%X",
                    arg_0->unk_04.unk_00, arg_0->unk_04.unk_04);
        }
        return 0;
    }
    if (arg_0->unk_12 && !arg_10)
    {
        dword_44E8B4 = var_18;
        sub_84610();
    }
    sub_84170((RwInt32)arg_0, var_18);
    if (rand() % 100 + 1 > arg_0->unk_15)
    {
        return 0;
    }
    sub_23B8F0((type_44C4E8 *)var_18, arg_4);
    if (arg_0->unk_1B)
    {
        bp_8 = arg_0->unk_1C * arg_0->unk_20 / 100;
        var_14 = arg_0->unk_1C * (arg_0->unk_20 / 12) / 100;
    }
    else
    {
        bp_8 = arg_0->unk_1C * arg_0->unk_20 / 100;
        var_14 = arg_0->unk_1C * arg_0->unk_22 / 100;
    }
    lv_10 = (RwReal)(rand() % (var_14 * 2 + 1) - var_14 + bp_8);
    if (lv_10 <= 1000.0f)
    {
        lv_10 *= 4.0f;
    }
    if (dword_44E8A0 == 2 && !arg_10)
    {
        lv_10 *= flt_428E30;
    }
    else if (dword_44E898 == 2 && !arg_10)
    {
        lv_10 *= flt_44E808;
    }
    sub_170ED0(&lv_10);
    do
    {
        ((type_44C4E8 *)var_18)->unk_3C = lv_10;
        if (((type_44C4E8 *)var_18)->unk_30)
        {
            RWA_SET_PARAM_REAL(((type_44C4E8 *)var_18)->unk_30, 4, 1, lv_10);
        }
    } while (0);
    if (arg_0->unk_1B)
    {
        var_C = arg_0->unk_10 * 9 / 10;
        bp_4 = arg_0->unk_10 / 10;
    }
    else
    {
        var_C = arg_0->unk_10;
        bp_4 = arg_0->unk_11;
    }
    slot_1C = (RwReal)(rand() % (bp_4 * 2 + 1) - bp_4 + var_C);
    slot_1C = slot_1C / 100.0f;
    if (dword_44E8A0 == 2 && !arg_10)
    {
        slot_1C *= 1.0f - flt_44E88C;
    }
    else if (dword_44E898 == 2 && !arg_10)
    {
        slot_1C *= 1.0f - flt_44E5E8;
    }
#ifndef CODFH_SP
    // single player has no third ducking case (SP 0x6E7B0 tests two)
    else if (dword_44E89C == 2 && !arg_10)
    {
        slot_1C *= 1.0f - flt_44D4BC;
    }
#endif
    if (dword_44E8B4 && !arg_10)
    {
#ifdef CODFH_SP
        // shape: the volume share in a local first, not reassociated (SP 0x6E7B0)
        RwReal f = (100 - arg_0->unk_13) / 100.0f;
        slot_1C *= f * (arg_0->unk_10 / 100.0f);
#else
        slot_1C *= (100 - arg_0->unk_13) / 100.0f * (arg_0->unk_10 / 100.0f);
#endif
    }
    if (slot_1C < 0.0f)
    {
        slot_1C = 0.0f;
    }
    if (slot_1C > 1.0f)
    {
        slot_1C = 1.0f;
    }
    do
    {
        ((type_44C4E8 *)var_18)->unk_40 = slot_1C;
        if (((type_44C4E8 *)var_18)->unk_30)
        {
            RWA_SET_PARAM_REAL(((type_44C4E8 *)var_18)->unk_30, 5, 1, slot_1C);
        }
    } while (0);
    do
    {
        if (arg_0->unk_14)
        {
            ((type_44C4E8 *)var_18)->unk_34 |= 4;
        }
        else
        {
            ((type_44C4E8 *)var_18)->unk_34 &= ~4;
        }
        if (((type_44C4E8 *)var_18)->unk_30)
        {
            RWA_SET_PARAM_INT(((type_44C4E8 *)var_18)->unk_30, 8, 1, (RwInt32)arg_0->unk_14);
        }
    } while (0);
    do
    {
        ((type_44C4E8 *)var_18)->unk_70 = arg_0->unk_24 * 100.0f;
        if (((type_44C4E8 *)var_18)->unk_30)
        {
            RWA_SET_PARAM_REAL(((type_44C4E8 *)var_18)->unk_30, 2, 1, arg_0->unk_24 * 100.0f);
        }
    } while (0);
    do
    {
        ((type_44C4E8 *)var_18)->unk_74 = arg_0->unk_26 * 100.0f;
        if (((type_44C4E8 *)var_18)->unk_30)
        {
            RWA_SET_PARAM_REAL(((type_44C4E8 *)var_18)->unk_30, 3, 1, arg_0->unk_26 * 100.0f);
        }
    } while (0);
    SoundEmitter_Stop((type_44C4E8 *)var_18, 1);
    return var_18;
}
// match: ?sub_8A910@type_8A980@@QAEXH@Z @ 0x0008A910
// sp-match: ?sub_8A910@type_8A980@@QAEXH@Z @ 0x0006EBE0
void type_8A980::sub_8A910(RwInt32 arg_0)
{
    if (arg_0)
    {
        sub_3C6C0(arg_0);
        if (((((type_44C4E8 *)arg_0)->unk_34 & 2) != 0) != 0)
        {
            SoundEmitter_Stop((type_44C4E8 *)arg_0, 0);
        }
    }
}
// match: ?sub_8A950@type_8A980@@SAHH@Z @ 0x0008A950
// sp-match: ?sub_8A950@type_8A980@@SAHH@Z @ 0x0006EC10
RwInt32 type_8A980::sub_8A950(RwInt32 arg_0)
{
    if (arg_0 && arg_0 != -1)
    {
        return (((type_44C4E8 *)arg_0)->unk_34 & 2) != 0;
    }
    return 0;
}
// Plays the sound under the key arg_0 for the entity arg_4 through its
// alias, and moves the voice to arg_C.
// match: ?sub_8A980@type_8A980@@QAEHPAUtype_3DF8D8_04@@PAUtype_3D3548@@HPAURwV3d@@HH@Z @ 0x0008A980
// sp-match: ?sub_8A980@type_8A980@@QAEHPAUtype_3DF8D8_04@@PAUtype_3D3548@@HPAURwV3d@@HH@Z @ 0x0006EC30
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_8A980::sub_8A980(type_3DF8D8_04 *arg_0, type_3D3548 *arg_4, RwInt32 arg_8,
                              RwV3d *arg_C, RwInt32 arg_10, RwInt32 arg_14)
{
    RwChar var_90[0x80];
    RwInt32 frm_8;
    type_8A980_alias *l4;

    l4 = (type_8A980_alias *)sub_198800(arg_0);
    if (!l4)
    {
        if (dword_44E860 && dword_44E86C)
        {
            sprintf(var_90, "0x%X, 0x%X", arg_0->unk_00, arg_0->unk_04);
        }
        return 0;
    }
    frm_8 = l4->vf_0C(this, arg_4, arg_8, arg_C, arg_10, arg_14);
    if (frm_8 && frm_8 != -1 && arg_C)
    {
        do
        {
            ((type_44C4E8 *)frm_8)->unk_58 = *arg_C;
            if (((type_44C4E8 *)frm_8)->unk_30)
            {
                Behavior_DispatchCallback(((type_44C4E8 *)frm_8)->unk_30, 0, 1, arg_C);
            }
        } while (0);
    }
    return frm_8;
}
// The same for the entry arg_4 of an index alias.
// match: ?sub_8AA70@type_8A980@@QAEHPAUtype_3DF8D8_04@@HPAUtype_3D3548@@HPAURwV3d@@HH@Z @ 0x0008AA70
// sp-match: ?sub_8AA70@type_8A980@@QAEHPAUtype_3DF8D8_04@@HPAUtype_3D3548@@HPAURwV3d@@HH@Z @ 0x0006ED20
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_8A980::sub_8AA70(type_3DF8D8_04 *arg_0, RwInt32 arg_4, type_3D3548 *arg_8,
                              RwInt32 arg_C, RwV3d *arg_10, RwInt32 arg_14, RwInt32 arg_18)
{
    RwChar var_90[0x80];
    RwInt32 frm_8;
    type_8A980_alias *l4;

    l4 = (type_8A980_alias *)sub_198800(arg_0);
    if (!l4)
    {
        if (dword_44E860 && dword_44E870)
        {
            sprintf(var_90, "0x%X, 0x%X", arg_0->unk_00, arg_0->unk_04);
        }
        return 0;
    }
    frm_8 = l4->vf_14(this, arg_4, arg_8, arg_C, arg_10, arg_14, arg_18);
    if (frm_8 && frm_8 != -1 && arg_10)
    {
        do
        {
            ((type_44C4E8 *)frm_8)->unk_58 = *arg_10;
            if (((type_44C4E8 *)frm_8)->unk_30)
            {
                Behavior_DispatchCallback(((type_44C4E8 *)frm_8)->unk_30, 0, 1, arg_10);
            }
        } while (0);
    }
    return frm_8;
}
