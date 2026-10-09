// The projectiles (types/projectile.h): the nine pools and their
// projectile classes.

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "rw/bamatrix.h"
#include "types/projectile.h"
#include "types/type_3D3548.h"
#include "game/functions.h"
#include "game/gameloop.h"
#include "game/data.h"
#include "game/frand.h"
#include "types/type_3D32F8.h"
#include "types/type_4AE70.h"
#include "rw/bavector.h"
#include "game/decals.h"
#include "game/surfaceparticles.h"
#include "types/CGlobalSounds.h"
#include "game/clones.h"
#include "game/particles.h"
#include "rw/rpatomic.h"
#include "rw/rpmaterial.h"
#include "rw/baengine.h"
#include "rw/badevice.h"
#include "types/type_92430.h"
#include "types/type_10F710.h"
#include "game/cheats.h"
#include "types/type_72810.h"
#include "types/type_D4C80.h"
#include "rw/rpworld.h"
#include "rw/rphanim.h"
#include "types/type_3DAFC8.h"
#include "rws/csystemcommands.h"
#include "types/type_4B9E90.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003DC6C0
extern const RwReal flt_3DC6C0 = 16.666666f;
// 0x00429E40
RwReal dword_429E40 = 4.0f;
// 0x00429E44
RwInt32 dword_429E44 = 60;
// 0x00429E48
RwInt32 dword_429E48 = 75;
// 0x00429E4C
RwInt32 dword_429E4C = 175;
// 0x00429E50
RwInt32 dword_429E50 = 300;
// 0x00429E54
type_429E54 stru_429E54 = { 0x80FFF0C8, 0x80FFF0C8, 1065353216, 1065353216, 1084227584, 0, 0 };
// 0x00429E70
RwReal dword_429E70 = 22.0f;
// 0x00429E74
RwReal dword_429E74 = 20.0f;
// 0x00429E78
RwReal dword_429E78 = 7.0f;
// 0x00429E7C
RwInt32 dword_429E7C = 1;
// 0x00429E80
RwReal dword_429E80 = 0.1f;
// 0x00429E84
RwReal dword_429E84 = 10.0f;
// 0x00429E88
RwReal dword_429E88 = 32.0f;
// 0x00429E8C
RwReal dword_429E8C = 200.0f;
// 0x00429E90
RwReal dword_429E90 = -0.069f;
// 0x004E1B60
RwInt32 dword_4E1B60;
// 0x004FB9F8
#ifndef CODFH_PLAIN
RwInt32 dword_4FB9F8;
#endif
// End of its data definitions.

// Vtables (.rdata, PLAN M5): each in its own placement range (config/splits.txt).
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3DC6C0@@3MB @ 0x003DC6C0
// match: ??_C@_0O@ENAGGMAG@m_projectiles?$AA@ @ 0x003DC6C4
// match: ??_7type_3DC6D8@@6B@ @ 0x003DC6D8
// match: ??_7type_3DC738@@6B@ @ 0x003DC738
// match: ??_7type_3DC798@@6B@ @ 0x003DC798
// match: ??_7type_3DC7F8@@6B@ @ 0x003DC7F8
// match: ??_7type_3DC858@@6B@ @ 0x003DC858
// match: ??_7type_3DC8B8@@6B@ @ 0x003DC8B8
// match: ??_C@_06OCIKGMNM@tracer?$AA@ @ 0x003DC920
// match: __ehhandler$?sub_15F590@type_4E19F8@@QAEPAUtype_3DC7F8@@HPAUtype_3D3548@@PAURwMatrixTag@@PAURwV3d@@HPAUtype_439A48@@PAUtype_429E54@@@Z>1>8 @ 0x0041E0CC
// match: __ehhandler$?sub_15F590@type_4E19F8@@QAEPAUtype_3DC7F8@@HPAUtype_3D3548@@PAURwMatrixTag@@PAURwV3d@@HPAUtype_439A48@@PAUtype_429E54@@@Z>1 @ 0x0041E0E4
// match: __ehhandler$??0type_3DC8B8@@QAE@XZ>1>8 @ 0x0041E100
// match: __ehhandler$??0type_3DC8B8@@QAE@XZ>1 @ 0x0041E110
// match: __ehhandler$?sub_1614E0@type_3DC7F8@@QAEXPAURwMatrixTag@@PAUtype_3D3548@@PAUtype_439A48@@@Z>1>8 @ 0x0041E12C
// match: __ehhandler$?sub_1614E0@type_3DC7F8@@QAEXPAURwMatrixTag@@PAUtype_3D3548@@PAUtype_439A48@@@Z>1 @ 0x0041E134
// match: .CRT$XCU+0 @ 0x0042712C
// match: ?dword_429E40@@3MA @ 0x00429E40
// match: ?dword_429E44@@3HA @ 0x00429E44
// match: ?dword_429E48@@3HA @ 0x00429E48
// match: ?dword_429E4C@@3HA @ 0x00429E4C
// match: ?dword_429E50@@3HA @ 0x00429E50
// match: ?stru_429E54@@3Utype_429E54@@A @ 0x00429E54
// match: ?dword_429E70@@3MA @ 0x00429E70
// match: ?dword_429E74@@3MA @ 0x00429E74
// match: ?dword_429E78@@3MA @ 0x00429E78
// match: ?dword_429E7C@@3HA @ 0x00429E7C
// match: ?dword_429E80@@3MA @ 0x00429E80
// match: ?dword_429E84@@3MA @ 0x00429E84
// match: ?dword_429E88@@3MA @ 0x00429E88
// match: ?dword_429E8C@@3MA @ 0x00429E8C
// match: ?dword_429E90@@3MA @ 0x00429E90

// match: _$E2 @ 0x0030BC40
// match: _$E3 @ 0x0030E880
// sp-match: _$E3 @ 0x0021EC50
// sp-match: _$E2 @ 0x0021DC30

// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).

type_4E19F8 dword_4E19F8[9];

// match: ?sub_15F1B0@@YAXXZ @ 0x0015F1B0
// sp-match: ?sub_15F1B0@@YAXXZ @ 0x00101CA0
// Sets the pools up: their sizes by kind.
void sub_15F1B0()
{
    dword_4E19F8[0].sub_15F3D0(0x300, 0);
    dword_4E19F8[1].sub_15F3D0(0x100, 1);
    dword_4E19F8[2].sub_15F3D0(0x40, 2);
    dword_4E19F8[3].sub_15F3D0(0x10, 3);
    dword_4E19F8[4].sub_15F3D0(0x10, 4);
    dword_4E19F8[5].sub_15F3D0(0x10, 5);
    dword_4E19F8[6].sub_15F3D0(0x14, 6);
    dword_4E19F8[7].sub_15F3D0(0x100, 7);
    dword_4E19F8[8].sub_15F3D0(0x40, 8);
}

// match: ?sub_15F240@@YAXXZ @ 0x0015F240
// sp-match: ?sub_15F240@@YAXXZ @ 0x00101ED0
void sub_15F240()
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 9; var_4++)
        dword_4E19F8[var_4].sub_15F490();
}

// match: ?sub_15F280@@YAXXZ @ 0x0015F280
// sp-match: ?sub_15F280@@YAXXZ @ 0x00101EF0
void sub_15F280()
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 9; var_4++)
        dword_4E19F8[var_4].sub_15F4B0();
}

// match: ?sub_15F2C0@@YAHHHPAURwMatrixTag@@PAURwV3d@@HPAUtype_439A48@@H@Z @ 0x0015F2C0
// sp-match: ?sub_15F2C0@@YAHHHPAURwMatrixTag@@PAURwV3d@@HPAUtype_439A48@@H@Z @ 0x001021D0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Spawns a projectile from its settings' pool; effect flag 0x200 with no
// colours takes the player's trigger's (its +0x420, a type_429E54).
RwInt32 sub_15F2C0(RwInt32 arg_0, RwInt32 arg_4, RwMatrix *arg_8, RwV3d *arg_C, RwInt32 arg_10,
                   type_439A48 *arg_14, RwInt32 arg_18)
{
    type_712B0 *var_C;
    type_3D3548 *bp_8;
    type_439A48 *bp_4;

    bp_4 = arg_14;
    if (!arg_18 && (arg_0 & 0x200))
    {
        bp_8 = sub_1745A0(0);
        if (bp_8)
        {
            var_C = bp_8->get_unk_34C();
            if (var_C)
                arg_18 = (RwInt32)var_C + 0x420;
        }
    }
    return (RwInt32)dword_4E19F8[bp_4->unk_00].sub_15F590(arg_0, (type_3D3548 *)arg_4, arg_8, arg_C, arg_10,
                                                          arg_14, (type_429E54 *)arg_18);
}

// match: ?sub_15F350@@YAXM@Z @ 0x0015F350
// sp-match: ?sub_15F350@@YAXM@Z @ 0x00101D30
void sub_15F350(RwReal arg_0)
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 9; var_4++)
        dword_4E19F8[var_4].sub_15FF50(arg_0);
}

// match: ?sub_15F390@@YAXPAURwCamera@@@Z @ 0x0015F390
// sp-match: ?sub_15F390@@YAXPAURwCamera@@@Z @ 0x00101D60
void sub_15F390(RwCamera *arg_0)
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 9; var_4++)
        dword_4E19F8[var_4].sub_15FFF0(arg_0);
}

// match: ?sub_15F3D0@type_4E19F8@@QAEXHH@Z @ 0x0015F3D0
// sp-match: ?sub_15F3D0@type_4E19F8@@QAEXHH@Z @ 0x00101760
void type_4E19F8::sub_15F3D0(RwInt32 arg_0, RwInt32 arg_4)
{
    RwInt32 var_4;

    var_4 = 0;
    unk_00 = arg_4;
    switch (arg_4)
    {
    case 3:
        var_4 = sizeof(type_3DC798);
        break;
    case 4:
        var_4 = sizeof(type_3DC858);
        break;
    case 2:
    case 5:
    case 6:
        var_4 = sizeof(type_3DC8B8);
        break;
    case 0:
        var_4 = sizeof(type_3DC7F8);
        break;
    case 1:
        var_4 = sizeof(type_3DC7F8);
        break;
    case 7:
        var_4 = sizeof(type_3DC738);
        break;
    case 8:
        var_4 = sizeof(type_3DC6D8);
        break;
    }
#ifdef CODFH_SP
    unk_04.sub_16C2C0(arg_0, var_4, "m_projectiles", 8, 0); // SP 0x101798: 8-byte alignment, flag 0
#else
    unk_04.sub_16C2C0(arg_0, var_4, "m_projectiles", 0x10, 1);
#endif
    unk_24 = 0;
}

// match: ?sub_15F490@type_4E19F8@@QAEXXZ @ 0x0015F490
// sp-match: ?sub_15F490@type_4E19F8@@QAEXXZ @ 0x00101D90
void type_4E19F8::sub_15F490()
{
    sub_15FF00();
}

// match: ?sub_15F4B0@type_4E19F8@@QAEXXZ @ 0x0015F4B0
// sp-match: ?sub_15F4B0@type_4E19F8@@QAEXXZ @ 0x00101DA0
void type_4E19F8::sub_15F4B0()
{
    sub_15FF00();
    unk_04.sub_16C4D0(1);
}

// match: ?sub_15F4D0@type_4E19F8@@QAEXPAUtype_3DC7F8@@@Z @ 0x0015F4D0
// sp-match: ?sub_15F4D0@type_4E19F8@@QAEXPAUtype_3DC7F8@@@Z @ 0x001017E0
void type_4E19F8::sub_15F4D0(type_3DC7F8 *arg_0)
{
    arg_0->unk_40 = unk_24;
    arg_0->unk_44 = 0;
    if (unk_24)
        unk_24->unk_44 = arg_0;
    unk_24 = arg_0;
}

// match: ?sub_15F520@type_4E19F8@@QAEXPAUtype_3DC7F8@@@Z @ 0x0015F520
// sp-match: ?sub_15F520@type_4E19F8@@QAEXPAUtype_3DC7F8@@@Z @ 0x00101810
void type_4E19F8::sub_15F520(type_3DC7F8 *arg_0)
{
    type_3DC7F8 *var_4;

    var_4 = arg_0->unk_44;
    if (var_4)
        var_4->unk_40 = arg_0->unk_40;
    var_4 = arg_0->unk_40;
    if (var_4)
        var_4->unk_44 = arg_0->unk_44;
    if (arg_0 == unk_24)
        unk_24 = arg_0->unk_40;
    arg_0->unk_40 = 0;
    arg_0->unk_44 = 0;
}

// match: ?sub_15F590@type_4E19F8@@QAEPAUtype_3DC7F8@@HPAUtype_3D3548@@PAURwMatrixTag@@PAURwV3d@@HPAUtype_439A48@@PAUtype_429E54@@@Z @ 0x0015F590
// sp-match: ?sub_15F590@type_4E19F8@@QAEPAUtype_3DC7F8@@HPAUtype_3D3548@@PAURwMatrixTag@@PAURwV3d@@HPAUtype_439A48@@PAUtype_429E54@@@Z @ 0x00101F50
type_3DC7F8 *type_4E19F8::sub_15F590(RwInt32 arg_0, type_3D3548 *arg_4, RwMatrix *arg_8, RwV3d *arg_C,
                                     RwInt32 arg_10, type_439A48 *arg_14, type_429E54 *arg_18)
{
    type_3DC8B8 *q28;
    type_3DC8B8 *frm_24;
    type_4E19F8 *var_20;
    RwReal l1C;
    type_3DC8B8 *m_18;
    RwReal ebp_14;
    type_3DC7F8 *lv_10;

    lv_10 = 0;
    switch (unk_00)
    {
    case 3:
        lv_10 = new (unk_04.sub_16C5A0(0)) type_3DC798;
        break;
    case 4:
        lv_10 = new (unk_04.sub_16C5A0(0)) type_3DC858;
        break;
    case 2:
    case 5:
        lv_10 = new (unk_04.sub_16C5A0(0)) type_3DC8B8;
        break;
    case 6:
        lv_10 = new (unk_04.sub_16C5A0(0)) type_3DC8B8;
        if (!unk_04.get_unk_18())
        {
            var_20 = projectile_pool(6);
            m_18 = (type_3DC8B8 *)var_20->unk_24;
            frm_24 = 0;
            ebp_14 = 1.0e9f;
            while (m_18)
            {
                q28 = (type_3DC8B8 *)m_18->unk_40;
                l1C = m_18->vf_054();
                if (l1C < ebp_14)
                {
                    ebp_14 = l1C;
                    frm_24 = m_18;
                }
                m_18 = q28;
            }
            frm_24->vf_060();
        }
        break;
#ifdef CODFH_SP // one case for kinds 0 and 1 (SP 0x101F50)
    case 0:
    case 1:
        lv_10 = new (unk_04.sub_16C5A0(0)) type_3DC7F8;
        break;
#else
    case 0:
        lv_10 = new (unk_04.sub_16C5A0(0)) type_3DC7F8;
        break;
    case 1:
        lv_10 = new (unk_04.sub_16C5A0(0)) type_3DC7F8;
        break;
#endif
    case 7:
        lv_10 = new (unk_04.sub_16C5A0(0)) type_3DC738;
        break;
    case 8:
        lv_10 = new (unk_04.sub_16C5A0(0)) type_3DC6D8;
        break;
    }
    if (lv_10)
    {
        lv_10->vf_000(arg_0, arg_4, arg_14, arg_18);
        lv_10->vf_008(arg_8);
        lv_10->vf_00C(arg_C);
        lv_10->vf_010(arg_10);
        sub_15F4D0(lv_10);
    }
    return lv_10;
}

// match: ?vf_01C@type_3DC7F8@@UAEXM@Z @ 0x0015FB30
// sp-match: ?vf_01C@type_3DC7F8@@UAEXM@Z @ 0x000D60D0
void type_3DC7F8::vf_01C(RwReal arg_0)
{
}

// match: ?vf_050@type_3DC7F8@@UAEXXZ @ 0x0015FB40
// sp-match: ?vf_050@type_3DC7F8@@UAEXXZ @ 0x001016E0
void type_3DC7F8::vf_050()
{
    unk_1C = unk_1C - unk_3C->unk_50;
}

// match: ?vf_054@type_3DC7F8@@UAEMXZ @ 0x0015FB60
// sp-match: ?vf_054@type_3DC7F8@@UAEMXZ @ 0x001016F0
RwReal type_3DC7F8::vf_054()
{
    return unk_1C;
}

// match: ?vf_020@type_3DC798@@UAEMXZ @ 0x0015FB80
// sp-match: ?vf_020@type_3DC798@@UAEMXZ @ 0x00101E70
RwReal type_3DC798::vf_020()
{
    return unk_3C->unk_40;
}

// match: ?vf_020@type_3DC738@@UAEMXZ @ 0x0015FBA0
// sp-match: ?vf_020@type_3DC738@@UAEMXZ @ 0x00101850
RwReal type_3DC738::vf_020()
{
    return unk_78;
}

// match: ?vf_040@type_3DC738@@UAEHXZ @ 0x0015FBC0
// sp-match: ?vf_040@type_3DC738@@UAEHXZ @ 0x00101860
RwInt32 type_3DC738::vf_040()
{
    return unk_88;
}

// match: ?vf_044@type_3DC738@@UAEMXZ @ 0x0015FBE0
// sp-match: ?vf_044@type_3DC738@@UAEMXZ @ 0x00101870
RwReal type_3DC738::vf_044()
{
    return unk_70;
}

// match: ?vf_048@type_3DC738@@UAEMXZ @ 0x0015FC00
// sp-match: ?vf_048@type_3DC738@@UAEMXZ @ 0x00101880
RwReal type_3DC738::vf_048()
{
    return unk_74;
}

// match: ?vf_020@type_3DC6D8@@UAEMXZ @ 0x0015FC20
// sp-match: ?vf_020@type_3DC6D8@@UAEMXZ @ 0x00101F10
RwReal type_3DC6D8::vf_020()
{
    return unk_98;
}

// match: ?vf_040@type_3DC6D8@@UAEHXZ @ 0x0015FC40
// sp-match: ?vf_040@type_3DC6D8@@UAEHXZ @ 0x00101F20
RwInt32 type_3DC6D8::vf_040()
{
    return unk_A8;
}

// match: ?vf_044@type_3DC6D8@@UAEMXZ @ 0x0015FC60
// sp-match: ?vf_044@type_3DC6D8@@UAEMXZ @ 0x00101F30
RwReal type_3DC6D8::vf_044()
{
    return unk_8C;
}

// match: ?vf_048@type_3DC6D8@@UAEMXZ @ 0x0015FC80
// sp-match: ?vf_048@type_3DC6D8@@UAEMXZ @ 0x00101F40
RwReal type_3DC6D8::vf_048()
{
    return unk_90;
}

// match: ??0type_3DC858@@QAE@XZ @ 0x0015FCA0
// sp-match: ??0type_3DC858@@QAE@XZ @ 0x00101DC0
// (Defined in the class, in types/projectile.h.)

// match: ?vf_058@type_3DC858@@UAEHXZ @ 0x0015FD20
// sp-match: ?vf_058@type_3DC858@@UAEHXZ @ 0x00125B30
RwInt32 type_3DC858::vf_058()
{
    return 6;
}

// match: ??0type_3DC8B8@@QAE@XZ @ 0x0015FD30
// match: ?vf_014@type_3DC7F8@@UAE_NM@Z @ 0x001608F0
// sp-match: ??0type_3DC8B8@@QAE@XZ @ 0x00101DF0
// sp-match: ?vf_014@type_3DC7F8@@UAE_NM@Z @ 0x00103800
// Its step by arg_0: the line to where it moves against the collision
// worlds, their atomics and the pool-6 projectiles; a hit entity takes the
// shot (vf_064, then its effects, vf_028), a hit pool-6 projectile has its
// time pushed back, a surface its effects (vf_02C); a hit bounces it when
// the cheat flags say so (twice at most). True when it is done.
bool type_3DC7F8::vf_014(RwReal arg_0)
{
    RwV3d var_10;
    type_3D3548 *var_14;
    type_161470 var_78;
    RpIntersection var_94;
    RwInt32 var_98;

    RwV3dScale(&var_10, &unk_10, arg_0);
    RwV3dAdd(&var_10, &unk_04, &var_10);
    var_14 = unk_30.sub_D4910();
    var_78.unk_00 = 1.0e37f;
    var_78.unk_0C = 0;
    var_78.unk_10 = 0;
    var_94.type = rpINTERSECTLINE;
    var_94.t.line.start = unk_04;
    var_94.t.line.end = var_10;
    var_78.sub_161470();
    var_78.unk_14 = unk_24;
    var_78.unk_18 = var_14;
    var_78.unk_1C = unk_34;
    var_78.unk_4C = 0xFFFF;
    var_78.unk_48 = sub_8F940();
    var_78.unk_00 = 1.0e37f;
    if (!(unk_28 & 2))
    {
        for (var_98 = 0; var_98 < 4; var_98++)
        {
            type_4E5D30 *var_9C = &dword_4E5D30[var_98];

            if (var_9C->get_unk_00() && var_9C->get_unk_28())
            {
                RpWorld *var_A8 = var_9C->unk_28;
                type_91F40 var_D4;

                sub_91F40(var_A8, &var_94.t.line, &var_D4, 1, 0x180000, 1); // not an address: line-test flags
                if (var_D4.unk_00 && var_D4.unk_04 < var_78.unk_00)
                {
                    var_78.unk_00 = var_D4.unk_04;
                    var_78.unk_2C = var_D4.unk_14;
                    var_78.unk_20 = var_D4.unk_08;
                    var_78.unk_0C = 0;
                    var_78.unk_38 = var_D4.unk_14;
                    var_78.unk_4C = material_data(((type_96E30 *)var_9C->get_unk_28())
                                                      ->unk_10[(RwUInt16)((RpTriangle *)var_D4.unk_00)->matIndex])->unk_04;
                }
            }
        }
    }
    for (var_98 = 0; var_98 < 4; var_98++)
    {
        type_4E5D30 *var_E4 = &dword_4E5D30[var_98];

        if (var_E4->get_unk_00() && var_E4->get_unk_28())
            RpWorldForAllAtomicIntersections(var_E4->get_unk_28(), &var_94, sub_1660C0, &var_78);
    }
    if (unk_4E5CD8.unk_00 && get_4E5D00())
        RpWorldForAllAtomicIntersections(get_4E5D00(), &var_94, sub_1660C0, &var_78);
    RwReal var_FC = 2.0f;
    type_3DC7F8 *var_100 = 0;
    type_4E19F8 *var_104 = projectile_pool(6);
    type_3DC7F8 *var_108 = var_104->unk_24;
    RwLine var_120;
    RwSphere var_130;
    RwReal var_134;

    while (var_108)
    {
        var_120.start = unk_04;
        var_120.end = var_10;
        var_130.center = var_108->unk_04;
        var_130.radius = dword_429E70;
        if (RtLineSphereIntersectionTest(&var_120, &var_130, &var_134) && var_134 < var_FC)
        {
            var_FC = var_134;
            var_100 = var_108;
        }
        var_108 = var_108->unk_40;
    }
    bool var_139 = dword_4B87C8 - unk_1C > unk_20;
    bool var_13A = false;
    if (var_78.unk_00 <= 1.0f || var_139 && vf_03C())
    {
        RwInt32 var_140 = 1;
        RwInt32 var_144 = 0;
        RwMatrix var_1B0;

        if (var_78.unk_0C)
        {
            type_3D3548 *var_148 = sub_FB960(var_78.unk_0C);

            if (var_148)
            {
                var_13A = true;
                RwInt32 var_14C = var_148->vf_1D4();
                if (var_14C != 0x38)
                {
                    type_439A48 *var_150 = unk_3C;
                    RwReal var_154 = var_78.unk_00;
                    RwV3d var_160;
                    type_75600 var_1E0;

                    RwV3dSub(&var_160, &var_94.t.line.end, &var_94.t.line.start);
                    RwV3dScale(&var_160, &var_160, var_154);
                    RwV3dAdd(&var_78.unk_20, &var_94.t.line.start, &var_160);
#ifdef CODFH_SP // single player has no dword_4FB9F8 test (SP 0x103BEF)
                    if (!(get_unk_2C_side(var_148) == (unk_24 & 7)))
#else
                    if (get_4FB9F8() || !(get_unk_2C_side(var_148) == (unk_24 & 7)))
#endif
                    {
                        sub_140F00(&var_1B0, &var_78.unk_20, &var_78.unk_2C);
                        var_144 = 1;
                        var_1E0.unk_00_w = var_150->unk_00;
                        var_1E0.unk_02_w = 0;
                        var_1E0.unk_04 = (RwInt32)this;
                        var_1E0.unk_08 = unk_24;
                        var_1E0.unk_14 = (RwInt32)&var_78.unk_20;
                        var_1E0.unk_18 = (RwInt32)&var_78.unk_2C;
                        var_1E0.unk_20 = &var_78.unk_38;
                        var_1E0.unk_1C = (RwInt32)&var_1B0;
                        var_1E0.unk_0C = var_14;
                        var_1E0.unk_10 = unk_34;
                        var_1E0.unk_28 = var_150->unk_04;
                        var_1E0.unk_2C = var_150->unk_04;
                        var_1E0.unk_24 = var_78.unk_44;
                        var_148->vf_064(&var_1E0);
                    }
                }
                else
                {
                    var_140 = 0;
                }
                if (var_148->unk_2C_7 | var_148->unk_2C_24 | var_148->unk_2C_18 | var_148->unk_2C_25)
                {
                    sub_140F00(&var_1B0, &var_78.unk_20, &var_78.unk_2C);
                    var_144 = 1;
                }
            }
            if (var_144)
                vf_028(var_148, &var_1B0, var_14);
        }
        else if (var_100)
        {
            var_100->advance_time();
        }
        else if (!var_13A)
        {
            RwV3d var_1F0;
            RwMatrix var_230;

            if (var_139 && vf_03C())
            {
                RwV3dNormalize(&var_1F0, &unk_10);
                sub_140F00(&var_1B0, &var_10, &var_1F0);
            }
            else
            {
                sub_140F00(&var_230, &var_78.unk_20, &var_78.unk_2C);
            }
            switch (var_78.unk_4C & 0xFFFF)
            {
            default:
                vf_02C(var_78.unk_4C & 0xFFFF, &var_230, var_14, 1);
                break;
            case 0x38:
                var_140 = 0;
                break;
            }
        }
        // A check compiled out of this build (it moves the registers one step).
        if (unk_3C)
        {
        }
        if (var_140)
        {
            if ((var_14 && var_14->vf_00C() && ((type_4B8888 *)dword_4B8888)->unk_00_1)
                || ((type_4B8888 *)dword_4B8888)->unk_00_3)
            {
                RwV3d var_240;
                RwV3d var_24C;
                RwV3d var_258;
                RwReal var_25C;
                RwV3d var_268;
                RwV3d var_274;
                RwV3d var_280;
                RwReal var_284;

                unk_2C++;
                if (unk_2C > 2)
                    return true;
                var_240 = var_78.unk_38;
                var_24C = unk_10;
                RwV3dNormalize(&var_24C, &var_24C);
                var_258 = var_24C;
                var_25C = RwV3dDotProduct(&var_258, &var_240) * 2;
                RwV3dScale(&var_268, &var_240, var_25C);
                RwV3dSub(&var_274, &var_258, &var_268);
                RwV3dScale(&var_280, &var_24C, -2.0f);
                var_284 = RwV3dLength((RwV3d *)&unk_10);
                unk_10 = var_274;
                RwV3dScale(&unk_10, &unk_10, var_284);
                var_10 = var_78.unk_20;
                RwV3dAdd(&var_10, &var_10, &var_280);
                unk_04 = var_10;
            }
            else
            {
                return true;
            }
        }
    }
    if (var_139)
        return true;
    if (dword_4B87C8 != unk_1C)
        unk_04 = var_10;
    vf_01C(arg_0);
    return false;
}

// match: __ehhandler$??0type_3DC8B8@@QAE@XZ-0x16 @ 0x00301EB0
// match: __ehhandler$??0type_3DC8B8@@QAE@XZ @ 0x00301EC6
// (Defined in the class, in types/projectile.h.)

// match: ??1type_3DC7F8@@QAE@XZ @ 0x0015FDF0
// sp-match: ??1type_3DC7F8@@QAE@XZ @ 0x00101700
// sp-match: ??1type_3DC7F8@@QAE@XZ @ 0x00101700
type_3DC7F8::~type_3DC7F8()
{
}

// match: ?vf_044@type_3DC798@@UAEMXZ @ 0x0015FE10
// sp-match: ?vf_044@type_3DC798@@UAEMXZ @ 0x00101E80
RwReal type_3DC798::vf_044()
{
    return unk_3C->unk_04;
}

// match: ?vf_048@type_3DC798@@UAEMXZ @ 0x0015FE30
// sp-match: ?vf_048@type_3DC798@@UAEMXZ @ 0x00101E90
RwReal type_3DC798::vf_048()
{
    return unk_3C->unk_4C;
}

// match: ?vf_05C@type_3DC8B8@@UAEPAXXZ @ 0x0015FE50
// sp-match: ?vf_05C@type_3DC8B8@@UAEPAXXZ @ 0x00101EA0
void *type_3DC8B8::vf_05C()
{
    return &unk_130;
}

// match: ?vf_060@type_3DC8B8@@UAEXXZ @ 0x0015FE70
// sp-match: ?vf_060@type_3DC8B8@@UAEXXZ @ 0x00101EB0
void type_3DC8B8::vf_060()
{
    unk_15C = 1;
}

// match: ?vf_064@type_3DC8B8@@UAEHXZ @ 0x0015FE90
// sp-match: ?vf_064@type_3DC8B8@@UAEHXZ @ 0x00101EC0
RwInt32 type_3DC8B8::vf_064()
{
    return unk_74;
}

// match: ?sub_15FEB0@type_4E19F8@@QAEHPAUtype_3DC7F8@@H@Z @ 0x0015FEB0
// sp-match: ?sub_15FEB0@type_4E19F8@@QAEHPAUtype_3DC7F8@@H@Z @ 0x00101890
RwInt32 type_4E19F8::sub_15FEB0(type_3DC7F8 *arg_0, RwInt32 arg_4)
{
    RwInt32 var_4;

    var_4 = 0;
    if (arg_0->vf_004() || arg_4)
    {
        sub_15F520(arg_0);
        unk_04.sub_16C710(arg_0);
        var_4 = 1;
    }
    return var_4;
}

// match: ?sub_15FF00@type_4E19F8@@QAEXXZ @ 0x0015FF00
// sp-match: ?sub_15FF00@type_4E19F8@@QAEXXZ @ 0x001018E0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_4E19F8::sub_15FF00()
{
    type_3DC7F8 *var_8;
    type_3DC7F8 *l4;

    var_8 = 0;
    l4 = unk_24;
    while (l4)
    {
        var_8 = l4->unk_40;
        sub_15FEB0(l4, 1);
        l4 = var_8;
    }
    unk_24 = 0;
}

// match: ?sub_15FF50@type_4E19F8@@QAEXM@Z @ 0x0015FF50
// sp-match: ?sub_15FF50@type_4E19F8@@QAEXM@Z @ 0x00101910
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_4E19F8::sub_15FF50(RwReal arg_0)
{
    type_3DC7F8 *var_8;
    type_3DC7F8 *l4;

    var_8 = 0;
    l4 = unk_24;
    while (l4)
    {
        var_8 = l4->unk_40;
        if (!l4->unk_6C && l4->vf_014(arg_0))
            l4->unk_6C = 1;
        if (l4->unk_6C)
            sub_15FEB0(l4, 0);
        l4 = var_8;
    }
}

// match: ?sub_15FFD0@@YAPAURpMaterial@@PAU1@PAX@Z @ 0x0015FFD0
// sp-match: ?sub_15FFD0@@YAPAURpMaterial@@PAU1@PAX@Z @ 0x00101960
// Sets each material's colour (the tracers', through
// RpGeometryForAllMaterials).
RpMaterial *sub_15FFD0(RpMaterial *arg_0, void *arg_4)
{
    RpMaterialSetColor(arg_0, (RwRGBA *)arg_4);
    return arg_0;
}

#ifdef CODFH_SP
void sp_sub_101710(const RwRGBAReal *arg_0);
#endif

// match: ?sub_15FFF0@type_4E19F8@@QAEXPAURwCamera@@@Z @ 0x0015FFF0
// sp-match: ?sub_15FFF0@type_4E19F8@@QAEXPAURwCamera@@@Z @ 0x00101970
// Draws the tracers (kinds 0 and 7) older than dword_429E40 in front of the
// camera arg_0: the "tracer" mesh stretched along each one's velocity, its
// colour fading out towards its distance unk_58.
void type_4E19F8::sub_15FFF0(RwCamera *arg_0)
{
    type_3DC7F8 *var_8;
    RwInt32 var_C;
    RpAtomic *var_10;
#ifndef CODFH_SP
    RwV3d var_1C;
#endif
    RwV3d var_28;
    RwMatrix var_70;
    RwReal var_74;
    RwRGBAReal var_84;
    RpGeometry *var_88;
    RwRGBA var_90;

    if ((unk_00 == 0 || unk_00 == 7) && RwCameraBeginUpdate(arg_0))
    {
        var_8 = unk_24;
        if (!var_8)
            return;
        var_C = 0;
        RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void *)1);
        RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void *)1);
        RwRenderStateSet(rwRENDERSTATECULLMODE, (void *)1);
        RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)0);
        RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void *)1);
        RwRenderStateSet(rwRENDERSTATESRCBLEND, (void *)5);
        RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void *)6);
        RwRenderStateSet(rwRENDERSTATESHADEMODE, (void *)2);
        RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, (void *)2);
        var_10 = sub_F2D80("tracer");
        if (var_10)
        {
            var_10->boundingSphere.radius = var_8->unk_4C * 100.0f;
            sub_123AF0(var_10, 0, &var_8->unk_5C, 0, 0, 0);
            while (var_8)
            {
                if (dword_4B87C8 - var_8->unk_1C > dword_429E40)
                {
#ifdef CODFH_SP // shape: block-scoped, so its copy loads all three words first (SP 0x101A5A)
                    RwV3d var_1C = var_8->unk_04;
#else
                    var_1C = var_8->unk_04;
#endif
                    sub_1414C0(&var_1C, &var_1C, &arg_0->viewMatrix);
                    if (var_1C.z >= 0.0f)
                    {
                        RwV3dNormalize(&var_28, &var_8->unk_10);
                        sub_140CE0(&var_70, &var_8->unk_04, &var_28);
                        RwV3dScale(&var_70.right, &var_70.right, var_8->unk_50);
                        RwV3dScale(&var_70.up, &var_70.up, var_8->unk_54);
                        RwV3dScale(&var_70.at, &var_70.at, var_8->unk_4C);
                        var_70.pos.x -= 50.0f * var_70.at.x;
                        var_70.pos.y -= 50.0f * var_70.at.y;
                        var_70.pos.z -= 50.0f * var_70.at.z;
                        if (var_8->unk_58 > 0.0f && var_1C.z > 0.0f)
                        {
                            var_74 = var_1C.z / var_8->unk_58;
                            var_84 = var_8->unk_5C;
                            var_84.alpha = (0.0f - var_84.alpha) * var_74 + var_84.alpha;
                            if (var_84.alpha < 0.0f)
                                var_84.alpha = 0;
#ifdef CODFH_SP // single player sets the colour through sp_sub_101710 (SP 0x101BD4)
                            sp_sub_101710(&var_84);
#else
                            dword_4CEAC8 = var_84;
#endif
                            var_88 = RpAtomicGetGeometry(var_10);
                            if (var_88)
                            {
                                var_88->flags |= rpGEOMETRYMODULATEMATERIALCOLOR;
                                RwRGBAFromRwRGBARealMacro(&var_90, &var_84);
                                RpGeometryForAllMaterials(var_88, sub_15FFD0, &var_90);
                            }
                        }
                        sub_123FE0((type_1243F0 *)&var_70, 1, 0);
                    }
                }
                var_8 = var_8->unk_40;
            }
            sub_124D70();
        }
        RwCameraEndUpdate(arg_0);
    }
}

#ifdef CODFH_SP
// sp-match: ?sp_sub_101710@@YAXPBURwRGBAReal@@@Z @ 0x00101710
// Single player only (SP 0x101710, called by sub_15FFF0 at SP 0x101BD4): sets the clones
// pass's material colour dword_4CEAC8 from arg_0.
void sp_sub_101710(const RwRGBAReal *arg_0)
{
    dword_4CEAC8 = *arg_0;
}
#endif

// match: ??0type_4E19F8@@QAE@XZ @ 0x00160420
// sp-match: ??0type_4E19F8@@QAE@XZ @ 0x00101740
type_4E19F8::type_4E19F8()
{
}

// match: ??1type_4E19F8@@QAE@XZ @ 0x00160440
// sp-match: ??1type_4E19F8@@QAE@XZ @ 0x00101750
type_4E19F8::~type_4E19F8()
{
}

// match: ?vf_000@type_3DC7F8@@UAEXHPAUtype_3D3548@@PAUtype_439A48@@PAUtype_429E54@@@Z @ 0x00160460
// sp-match: ?vf_000@type_3DC7F8@@UAEXHPAUtype_3D3548@@PAUtype_439A48@@PAUtype_429E54@@@Z @ 0x00102240
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3DC7F8::vf_000(RwInt32 arg_0, type_3D3548 *arg_4, type_439A48 *arg_8, type_429E54 *arg_C)
{
    type_F1230 *ebp_34;
    type_F1230 *var_30;
    RwReal var_2C;
    type_429E54 *lcl_28;
    RwRGBAReal frm_24;
    RwRGBAReal v14;
    type_439A48 *l4;

    unk_28 = 0;
    unk_3C = arg_8;
    unk_1C = dword_4B87C8;
    unk_20 = 480.0f;
    unk_6C = 0;
    unk_40 = 0;
    unk_44 = 0;
    unk_48 = 0;
    unk_2C = 0;
    lcl_28 = arg_C;
    if (!lcl_28)
        lcl_28 = &stru_429E54;
    frm_24.red = (RwReal)((lcl_28->unk_00 & 0xFF0000) >> 16) / 255.0f;
    frm_24.green = (RwReal)((lcl_28->unk_00 & 0xFF00) >> 8) / 255.0f;
    frm_24.blue = (RwReal)(lcl_28->unk_00 & 0xFF) / 255.0f;
    frm_24.alpha = (RwReal)((lcl_28->unk_00 & 0xFF000000) >> 24) / 255.0f;
    if (lcl_28->unk_04)
    {
        v14.red = (RwReal)((lcl_28->unk_04 & 0xFF0000) >> 16) / 255.0f;
        v14.green = (RwReal)((lcl_28->unk_04 & 0xFF00) >> 8) / 255.0f;
        v14.blue = (RwReal)(lcl_28->unk_04 & 0xFF) / 255.0f;
        v14.alpha = (RwReal)((lcl_28->unk_04 & 0xFF000000) >> 24) / 255.0f;
    }
    else
    {
        v14.red = frm_24.red;
        v14.green = frm_24.green;
        v14.blue = frm_24.blue;
        v14.alpha = frm_24.alpha;
    }
    var_2C = frand_range(0.0f, 1.0f);
    unk_5C.red = (v14.red - frm_24.red) * var_2C + frm_24.red;
    unk_5C.green = (v14.green - frm_24.green) * var_2C + frm_24.green;
    unk_5C.blue = (v14.blue - frm_24.blue) * var_2C + frm_24.blue;
    unk_5C.alpha = (v14.alpha - frm_24.alpha) * var_2C + frm_24.alpha;
    unk_4C = frand_range(lcl_28->unk_10_r, lcl_28->unk_10_r + lcl_28->unk_14_r);
    unk_50 = lcl_28->unk_08_r;
    unk_54 = lcl_28->unk_0C_r;
    unk_58 = lcl_28->unk_18_r;
    unk_24 = arg_0;
    if (arg_4)
    {
        unk_30.sub_D48D0(arg_4);
        unk_34 = arg_4->unk_2C;
    }
    else
    {
        unk_30.sub_D48D0(0);
        unk_34 = arg_0;
    }
    unk_38 = 0;
    l4 = arg_8;
    if (l4->unk_08[0].unk_00 && l4->unk_08[0].unk_04)
    {
        var_30 = (type_F1230 *)sub_F1230();
        ((type_4B9E90 *)var_30)->sub_F0880(l4->unk_08[0].unk_04, l4->unk_08[0].unk_08, l4->unk_08[0].unk_0C, 0);
        ((type_4B9E90 *)var_30)->sub_F0A10((type_3D3548 *)this, l4->unk_08[0].unk_14, 2);
        var_30->set_unk_2C(l4->unk_08[0].unk_10);
    }
    if (l4->unk_08[1].unk_00 && l4->unk_08[1].unk_04)
    {
        ebp_34 = (type_F1230 *)sub_F1230();
        ((type_4B9E90 *)ebp_34)->sub_F0880(l4->unk_08[1].unk_04, l4->unk_08[1].unk_08, l4->unk_08[1].unk_0C, 0);
        ((type_4B9E90 *)ebp_34)->sub_F0A10((type_3D3548 *)this, l4->unk_08[1].unk_14, 2);
        ebp_34->set_unk_2C(l4->unk_08[1].unk_10);
    }
}

// match: ?vf_004@type_3DC7F8@@UAEHXZ @ 0x00160840
// sp-match: ?vf_004@type_3DC7F8@@UAEHXZ @ 0x001024E0
RwInt32 type_3DC7F8::vf_004()
{
    sub_F12A0((type_3D3548 *)this, &unk_04);
    return 1;
}

// match: ?vf_008@type_3DC7F8@@UAEXPAURwMatrixTag@@@Z @ 0x00160870
// sp-match: ?vf_008@type_3DC7F8@@UAEXPAURwMatrixTag@@@Z @ 0x00102500
void type_3DC7F8::vf_008(RwMatrix *arg_0)
{
    unk_04 = arg_0->pos;
}

// match: ?vf_00C@type_3DC7F8@@UAEXPAURwV3d@@@Z @ 0x001608A0
// sp-match: ?vf_00C@type_3DC7F8@@UAEXPAURwV3d@@@Z @ 0x00102B70
void type_3DC7F8::vf_00C(RwV3d *arg_0)
{
    unk_10 = *arg_0;
}

// match: ?vf_010@type_3DC7F8@@UAEXH@Z @ 0x001608D0
// sp-match: ?vf_010@type_3DC7F8@@UAEXH@Z @ 0x00102520
void type_3DC7F8::vf_010(RwInt32 arg_0)
{
    unk_48 = arg_0;
}

#ifndef CODFH_SP // single player has it inline (include/types/projectile.h)
// match: ?sub_161470@type_161470@@QAEXXZ @ 0x00161470
void type_161470::sub_161470()
{
    unk_00 = 1.0e37f;
    unk_0C = 0;
    unk_10 = 0;
    unk_18 = 0;
    unk_08 = 0;
    unk_04 = 1.0e37f;
    unk_50 = 0;
    unk_54 = 0;
    unk_58 = 0;
}
#endif

// match: ?sub_1614E0@type_3DC7F8@@QAEXPAURwMatrixTag@@PAUtype_3D3548@@PAUtype_439A48@@@Z @ 0x001614E0
// match: __ehhandler$?sub_1614E0@type_3DC7F8@@QAEXPAURwMatrixTag@@PAUtype_3D3548@@PAUtype_439A48@@@Z-0x8 @ 0x00301ED0
// match: __ehhandler$?sub_1614E0@type_3DC7F8@@QAEXPAURwMatrixTag@@PAUtype_3D3548@@PAUtype_439A48@@@Z @ 0x00301ED8
// sp-match: ?sub_1614E0@type_3DC7F8@@QAEXPAURwMatrixTag@@PAUtype_3D3548@@PAUtype_439A48@@@Z @ 0x00104020
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3DC7F8::sub_1614E0(RwMatrix *arg_0, type_3D3548 *arg_4, type_439A48 *arg_8)
{
    RwInt32 var_50;
    RwInt32 var_4C;
    type_3D3548 *var_48;
    RwReal loc44;
    type_4AE70 var_40;

    var_40.unk_00 = 0x804;
    if (arg_4)
    {
        switch (arg_4->unk_2C & 7)
        {
        case 1:
            var_40.unk_00 = 0x801;
            break;
        case 2:
            var_40.unk_00 = 0x802;
            break;
        }
    }
    var_40.unk_04 = unk_30;
    var_40.unk_08 = (RwInt32)this;
    var_40.unk_0C = arg_0;
    if (arg_8)
    {
        var_40.unk_10 = arg_8->unk_4C;
        var_40.unk_14 = arg_8->unk_4C;
        var_40.unk_18 = arg_8->unk_4C;
        var_40.unk_2C = arg_8->unk_54;
        var_40.unk_30 = (RwInt32)arg_8;
    }
    else
    {
        var_40.unk_10 = vf_048();
        var_40.unk_14 = vf_048();
        var_40.unk_18 = vf_048();
        var_40.unk_2C = vf_044();
        var_40.unk_30 = 0;
    }
    var_48 = sub_1745A0(0);
    var_4C = 0;
    var_50 = 1;
    if (var_48 && var_48->vf_200() && var_48->vf_1E4())
    {
        var_4C = 1;
        var_50 = var_48->unk_28_2;
        var_48->unk_28_2 = 1;
    }
    sub_9A960(&var_40);
    if (var_4C)
        var_48->unk_28_2 = var_50;
    // An unused slot above `this` (see unused_slot).
    unused_slot();
    loc44 = vf_048() * vf_048();
    sub_1616F0(2, loc44);
    sub_1616F0(3, loc44);
    sub_1616F0(4, loc44);
    sub_1616F0(6, loc44);
    sub_1616F0(5, loc44);
    sub_1616F0(8, loc44);
}

// match: ?sub_1616F0@type_3DC7F8@@QAEXHM@Z @ 0x001616F0
// sp-match: ?sub_1616F0@type_3DC7F8@@QAEXHM@Z @ 0x00102530
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3DC7F8::sub_1616F0(RwInt32 arg_0, RwReal arg_4)
{
    RwV3d *var_20;
    RwV3d l1C;
    RwReal lv_10;
    type_3DC7F8 *var_C;
    type_4E19F8 *bp_8;
    type_3DC7F8 *bp_4;

    bp_8 = projectile_pool(arg_0);
    bp_4 = bp_8->unk_24;
    while (bp_4)
    {
        var_C = bp_4->unk_40;
        var_20 = &bp_4->unk_04;
        RwV3dSubMacro(&l1C, var_20, &unk_04);
        lv_10 = RwV3dDotProduct(&l1C, &l1C);
        if (lv_10 <= arg_4)
        {
            bp_4->vf_04C();
            bp_4->vf_050();
        }
        bp_4 = var_C;
    }
}

// match: ?vf_030@type_3DC7F8@@UAEXPAURwMatrixTag@@@Z @ 0x001617B0
// sp-match: ?vf_030@type_3DC7F8@@UAEXPAURwMatrixTag@@@Z @ 0x001025A0
void type_3DC7F8::vf_030(RwMatrix *arg_0)
{
    sub_F2FF0(0x68C3708F, arg_0, 1, 1, 0, 0); // not an address: a particle system's name hash
}

// match: ?vf_034@type_3DC7F8@@UAEXPAUtype_3D3548@@PAURwMatrixTag@@@Z @ 0x001617E0
// sp-match: ?vf_034@type_3DC7F8@@UAEXPAUtype_3D3548@@PAURwMatrixTag@@@Z @ 0x001025C0
void type_3DC7F8::vf_034(type_3D3548 *arg_0, RwMatrix *arg_4)
{
    RwInt32 var_8;
    RwInt32 var_C;
    RwMatrix var_50;
    RwV3d *var_54;
    RwV3d *var_58;
    RwV3d var_64;

    if (arg_0->unk_28_9 || arg_0->unk_28_0)
        return;
    var_8 = RpRandom() % 101;
    if (var_8 < 33)
    {
        var_C = RpRandom() % 101;
        sub_F2FF0(0x8B4CF8C0, arg_4, 1, 1, 0, 0); // not an address: a particle system's name hash
        if (var_C > 50)
            var_C = 0x65E78FD8; // not an address: a particle system's name hash
        else
            var_C = 0x4B041CBE; // not an address: a particle system's name hash
        sub_F2FF0(var_C, arg_4, 1, 1, 0, 0);
        RwMatrixSetIdentityMacro(&var_50);
        var_54 = &var_50.at;
        var_58 = &var_50.pos;
        *var_58 = arg_4->pos;
        *var_54 = unk_10;
        RwV3dNormalize(var_54, var_54);
        var_64 = var_50.at;
        sub_140440(&var_50, &var_64, frand_range(-3.14159f, 3.14159f));
        sub_F2FF0(0x98E3B465, &var_50, 1, 1, 0, 0); // not an address: a particle system's name hash
    }
    else
    {
        sub_F2FF0(0x267F639A, arg_4, 1, 1, 0, 0); // not an address: a particle system's name hash
    }
}

// match: ?vf_02C@type_3DC7F8@@UAEXHPAURwMatrixTag@@PAUtype_3D3548@@H@Z @ 0x001619D0
// sp-match: ?vf_02C@type_3DC7F8@@UAEXHPAURwMatrixTag@@PAUtype_3D3548@@H@Z @ 0x00102770
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3DC7F8::vf_02C(RwInt32 arg_0, RwMatrix *arg_4, type_3D3548 *arg_8, RwInt32 arg_C)
{
    RwInt32 var_10;
    RwInt32 var_C;
    type_4E5E40 *bp_8;
    type_4E5E40_08 *bp_4;

    arg_0 &= 0xFFFF;
    if (arg_0 == 0xFFFF)
        arg_0 = 12;
    if (arg_0 != 0xFFFF)
    {
        bp_8 = &dword_4E5E40;
        bp_4 = bp_8->unk_08;
        if (bp_4 && (RwUInt32)arg_0 < bp_8->unk_00[1])
        {
            var_10 = bp_4[arg_0].unk_04[0];
            if (var_10 > -1)
                sub_F2750(0, var_10, arg_4, 0);
            if (arg_C)
            {
                var_C = bp_4[arg_0].unk_04[1];
                if (var_C > -1)
                    sub_F04E0(arg_4, var_C, 0);
            }
            vf_024(&arg_4->pos, &dword_4B1E80, bp_4[arg_0].unk_00, arg_8, 0);
        }
    }
}

// match: ?vf_028@type_3DC7F8@@UAEXPAUtype_3D3548@@PAURwMatrixTag@@0@Z @ 0x00161AC0
// sp-match: ?vf_028@type_3DC7F8@@UAEXPAUtype_3D3548@@PAURwMatrixTag@@0@Z @ 0x00102800
void type_3DC7F8::vf_028(type_3D3548 *arg_0, RwMatrix *arg_4, type_3D3548 *arg_8)
{
    RwInt32 var_4;

    var_4 = -1;
    if (arg_0)
    {
        var_4 = arg_0->vf_1D4();
        if (arg_0->unk_2C_17 || arg_0->unk_2C_5 || arg_0->unk_2C_21)
            vf_034(arg_0, arg_4);
    }
    if (var_4 != -1)
        vf_02C(var_4, arg_4, arg_8, 0);
}

// match: ?vf_038@type_3DC7F8@@UAEXPAURwMatrixTag@@@Z @ 0x00161B50
// sp-match: ?vf_038@type_3DC7F8@@UAEXPAURwMatrixTag@@@Z @ 0x00102860
void type_3DC7F8::vf_038(RwMatrix *arg_0)
{
    sub_F2FF0(0x3C524C89, arg_0, 0, 1, 0, 0); // not an address: a particle system's name hash
    sub_F2FF0(0x440B8018, arg_0, 0, 1, 0, 0); // not an address: a particle system's name hash
    sub_F2FF0(0x7F56AB78, arg_0, 0, 1, 0, 0); // not an address: a particle system's name hash
    sub_F2FF0(0x87ACF10D, arg_0, 0, 1, 0, 0); // not an address: a particle system's name hash
}

// match: ?vf_024@type_3DC7F8@@UAEXPAURwV3d@@PAUtype_3DF8D8_04@@HPAUtype_3D3548@@H@Z @ 0x00161BD0
// sp-match: ?vf_024@type_3DC7F8@@UAEXPAURwV3d@@PAUtype_3DF8D8_04@@HPAUtype_3D3548@@H@Z @ 0x001028C0
void type_3DC7F8::vf_024(RwV3d *arg_0, type_3DF8D8_04 *arg_4, RwInt32 arg_8, type_3D3548 *arg_C,
                            RwInt32 arg_10)
{
    RwInt32 var_4;

    if (!arg_10)
        arg_10 = 0x40;
    var_4 = 0;
    if (arg_8 == -2)
        var_4 = dword_4B1E98.sub_8A980(arg_4, arg_C, arg_10, arg_0, 0, 0);
    else
        var_4 = dword_4B1E98.sub_8AA70(arg_4, arg_8, arg_C, arg_10, arg_0, 0, 0);
}


































// Members /OPT:ICF folded into shared trivial bodies (config/aliases.txt): defined here for
// the authentic link (PLAN M7); the placement link takes the shared bodies.

// ?vf_018@type_3DC7F8@@UAEXXZ (folded into the empty body at 0x1E41C0)
void type_3DC7F8::vf_018()
{
}

// ?vf_03C@type_3DC798@@UAEHXZ (folded into `return 0` at 0x1E4CB0)
RwInt32 type_3DC798::vf_03C()
{
    return 0;
}

// ?vf_03C@type_3DC7F8@@UAEHXZ (folded into `return 0` at 0x1E4CB0)
RwInt32 type_3DC7F8::vf_03C()
{
    return 0;
}

// ?vf_03C@type_3DC858@@UAEHXZ (folded into `return 0` at 0x1E4CB0)
RwInt32 type_3DC858::vf_03C()
{
    return 0;
}

// ?vf_03C@type_3DC8B8@@UAEHXZ (folded into `return 0` at 0x1E4CB0)
RwInt32 type_3DC8B8::vf_03C()
{
    return 0;
}

// ?vf_040@type_3DC7F8@@UAEHXZ (folded into `return 0` at 0x1E4CB0)
RwInt32 type_3DC7F8::vf_040()
{
    return 0;
}

// ?vf_04C@type_3DC7F8@@UAEXXZ (folded into the empty body at 0x1E41C0)
void type_3DC7F8::vf_04C()
{
}

// ?vf_058@type_3DC798@@UAEHXZ (folded into `return 4` at 0x9E000)
RwInt32 type_3DC798::vf_058()
{
    return 4;
}

// ?vf_058@type_3DC7F8@@UAEHXZ (folded into `return 0` at 0x1E4CB0)
RwInt32 type_3DC7F8::vf_058()
{
    return 0;
}

// Members /OPT:ICF folded into shared trivial bodies (config/aliases.txt): defined here for
// the authentic link (PLAN M7); the placement link takes the shared bodies.

// ??3type_3DC7F8@@SAXPAX0@Z (folded into the empty debug print at 0x19A750)
void type_3DC7F8::operator delete(void *arg_0, void *arg_4)
{
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??2type_3DC7F8@@SAPAXIPAX@Z (folded into 0x6CCF0)
void *type_3DC7F8::operator new(RwUInt32 arg_0, void *arg_4)
{
    return arg_4;
}

// ?vf_01C@type_3DC798@@UAEXM@Z (folded into 0x165980)
void type_3DC798::vf_01C(RwReal arg_0)
{
    type_439A48 *var_4;

    var_4 = unk_3C;
    if (var_4->unk_3C)
        unk_10.y = arg_0 * var_4->unk_40 + unk_10.y;
}

// ?vf_01C@type_3DC8B8@@UAEXM@Z (folded into 0x165980)
void type_3DC8B8::vf_01C(RwReal arg_0)
{
    type_439A48 *var_4;

    var_4 = unk_3C;
    if (var_4->unk_3C)
        unk_10.y = arg_0 * var_4->unk_40 + unk_10.y;
}

// ?vf_020@type_3DC7F8@@UAEMXZ (folded into 0x73BC0)
RwReal type_3DC7F8::vf_020()
{
    return 0.0f;
}

// ?vf_020@type_3DC858@@UAEMXZ (folded into 0x15FB80)
RwReal type_3DC858::vf_020()
{
    return unk_3C->unk_40;
}

// ?vf_020@type_3DC8B8@@UAEMXZ (folded into 0x15FB80)
RwReal type_3DC8B8::vf_020()
{
    return unk_3C->unk_40;
}

// ?vf_038@type_3DC6D8@@UAEXPAURwMatrixTag@@@Z (folded into 0x1659C0)
void type_3DC6D8::vf_038(struct RwMatrixTag *arg_0)
{
    sub_F2FF0(0xFC34701D, arg_0, 0, 1, 0, 0); // not an address: a particle system's name hash
    sub_F2FF0(0x6D27082E, arg_0, 0, 1, 0, 0); // not an address: a particle system's name hash
    sub_F2FF0(0x3010F21D, arg_0, 0, 1, 0, 0); // not an address: a particle system's name hash
    sub_F2FF0(0xE46D3977, arg_0, 0, 1, 0, 0); // not an address: a particle system's name hash
    sub_F2FF0(0xF8E85410, arg_0, 0, 1, 0, 0); // not an address: a particle system's name hash
    sub_F2FF0(0x7A855E3F, arg_0, 0, 1, 0, 0); // not an address: a particle system's name hash
}

// ?vf_03C@type_3DC6D8@@UAEHXZ (folded into 0x115460)
RwInt32 type_3DC6D8::vf_03C()
{
    return 1;
}

// ?vf_03C@type_3DC738@@UAEHXZ (folded into 0x115460)
RwInt32 type_3DC738::vf_03C()
{
    return 1;
}

// ?vf_040@type_3DC798@@UAEHXZ (folded into 0x115460)
RwInt32 type_3DC798::vf_040()
{
    return 1;
}

// ?vf_040@type_3DC858@@UAEHXZ (folded into 0x115460)
RwInt32 type_3DC858::vf_040()
{
    return 1;
}

// ?vf_040@type_3DC8B8@@UAEHXZ (folded into 0x115460)
RwInt32 type_3DC8B8::vf_040()
{
    return 1;
}

// ?vf_044@type_3DC7F8@@UAEMXZ (folded into 0x73BC0)
RwReal type_3DC7F8::vf_044()
{
    return 0.0f;
}

// ?vf_044@type_3DC858@@UAEMXZ (folded into 0x15FE10)
RwReal type_3DC858::vf_044()
{
    return unk_3C->unk_04;
}

// ?vf_044@type_3DC8B8@@UAEMXZ (folded into 0x15FE10)
RwReal type_3DC8B8::vf_044()
{
    return unk_3C->unk_04;
}

// ?vf_048@type_3DC7F8@@UAEMXZ (folded into 0x73BC0)
RwReal type_3DC7F8::vf_048()
{
    return 0.0f;
}

// ?vf_048@type_3DC858@@UAEMXZ (folded into 0x15FE30)
RwReal type_3DC858::vf_048()
{
    return unk_3C->unk_4C;
}

// ?vf_048@type_3DC8B8@@UAEMXZ (folded into 0x15FE30)
RwReal type_3DC8B8::vf_048()
{
    return unk_3C->unk_4C;
}

// ?vf_058@type_3DC6D8@@UAEHXZ (folded into 0xC5540)
RwInt32 type_3DC6D8::vf_058()
{
    return 3;
}

// ?vf_058@type_3DC738@@UAEHXZ (folded into 0x195D00)
RwInt32 type_3DC738::vf_058()
{
    return 2;
}

// ?vf_058@type_3DC8B8@@UAEHXZ (folded into 0xA17A0)
RwInt32 type_3DC8B8::vf_058()
{
    return 5;
}
