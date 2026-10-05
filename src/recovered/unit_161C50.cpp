// Split from unit_15F1B0.cpp at 0x161C50, where the image starts another object (the
// grenade, type_3DC8B8's members): its .rdata begins at 0x3DC928 with its own constants
// (the frame time first) before the grenade events' texts (PLAN M7).

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
// 0x003DC928
extern const RwReal flt_3DC928 = 16.666666f;
// 0x003DC92C
extern const RwReal flt_3DC92C = 0.01f;
// 0x003DC930
extern const RwReal flt_3DC930 = 0.01f;

// match: ?flt_3DC928@@3MB @ 0x003DC928
// match: ?flt_3DC92C@@3MB @ 0x003DC92C
// match: ?flt_3DC930@@3MB @ 0x003DC930
// match: ??_C@_0BF@DJBECKFN@GrenadeExplodeCancel?$AA@ @ 0x003DC934
// match: ??_C@_0P@CCMBNONG@GrenadeExplode?$AA@ @ 0x003DC94C
// match: ??_C@_0N@FIIGCDMA@GrenadeAlert?$AA@ @ 0x003DC95C
// match: ??_C@_0BG@NKBLEGKG@GrenadeIsFreakingOnMe?$AA@ @ 0x003DC96C


// match: ?vf_000@type_3DC8B8@@UAEXHPAUtype_3D3548@@PAUtype_439A48@@PAUtype_429E54@@@Z @ 0x00161C50
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// A grenade starts as the base does (without colours), with a copy of its
// settings' model and its owner's weapon in hand.
void type_3DC8B8::vf_000(RwInt32 arg_0, type_3D3548 *arg_4, type_439A48 *arg_8, type_429E54 *arg_C)
{
    RwInt32 var_8;
    type_439A48 *l4;

    l4 = arg_8;
    type_3DC7F8::vf_000(arg_0, arg_4, arg_8, 0);
    unk_94.sub_129620(RpClumpClone((RpClump *)l4->unk_38));
    unk_8C = 0;
    unk_90 = 1;
    unk_70 = l4->unk_00;
    unk_74 = arg_4 && arg_4->vf_00C() ? arg_4->vf_00C()->hand_index() : -1;
    unk_78 = 1;
    unk_A0 = 0;
    unk_A4 = 0;
    unk_128 = 0;
    unk_12C = 0;
    unk_158 = 0;
    unk_88 = dword_429E74;
    unk_154 = 0;
    unk_15C = 0;
    unk_13C = -1;
    unk_140 = -1;
    unk_150 = 0;
    unk_1A0.sub_D48D0(0);
    unk_7C.x = 1.0f;
    unk_7C.y = 0;
    unk_7C.z = 0;
    unk_144.z = 0;
    unk_144.y = 0;
    unk_144.x = 0;
    for (var_8 = 0; var_8 < 32; var_8++)
        unk_A8[var_8].sub_D48D0(0);
}
// match: ?vf_004@type_3DC8B8@@UAEHXZ @ 0x00161E30
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Done: unless unk_128 is set, tells each entity in unk_438CA8 not in
// unk_A8 "GrenadeExplodeCancel" (with where it was); then as the base, its
// model released.
RwInt32 type_3DC8B8::vf_004()
{
    RwV3d var_24;
    RwInt32 bp_18;
    type_3D3548 *var_14;
    RwV3d ebp_10;
    RwReal l4;

    if (!unk_128)
    {
        ebp_10.x = unk_04.x;
        ebp_10.y = unk_04.y;
        ebp_10.z = unk_04.z;
        l4 = 0;
        for (bp_18 = 0; bp_18 < 32; bp_18++)
        {
            var_14 = unk_438CA8[bp_18].sub_D4910();
            if (var_14 && !unk_A8[bp_18].sub_D4910())
            {
                RwV3dSub(&var_24, var_14->sub_CD550(), &unk_04);
                l4 = RwV3dLength((RwV3d *)&var_24);
                sub_6B5F0("GrenadeExplodeCancel", (type_67620 *)(var_14->vf_098()), 0, 0, (RwInt32 *)(&ebp_10), 4, 1, 0);
            }
        }
    }
    type_3DC7F8::vf_004();
    if (unk_94.get_unk_08())
        unk_94.sub_129940(0);
    return 1;
}
// match: ?vf_008@type_3DC8B8@@UAEXPAURwMatrixTag@@@Z @ 0x00161F70
// Its model placed at the matrix arg_0.
void type_3DC8B8::vf_008(RwMatrix *arg_0)
{
    RwFrame *var_4;

    var_4 = RpClumpGetFrame(unk_94.get_unk_08());
    *RwFrameGetMatrix(var_4) = *arg_0;
    sub_173180(unk_94.get_unk_08());
}

// A real's size as the grenade's step tests it: through a ternary that
// copies either branch into a temporary (not fabs, which the image calls
// elsewhere).
#define ABS_(x) ((x) < 0.0f ? -(x) : (x))

// match: ?vf_014@type_3DC8B8@@UAE_NM@Z @ 0x00161FC0
// Its step by arg_0. Unless it sticks to something (unk_12C), its model moves
// by its velocity and gravity; the line (or, for a table-6 grenade at rest, a
// sphere) there is tested against the worlds and their atomics. A hit sticks
// a table-5 grenade (to the entity's nearest bone or frame), bounces the
// others off the surface (with its sound), alerts the entities near where it
// will land and spins it. Stuck, it follows what it sticks to. When its fuse
// is over it tells the entities it alerted, blows up (vf_024's sound, its
// effects, a shake, sub_1614E0) and is done (true).
bool type_3DC8B8::vf_014(RwReal arg_0)
{
    type_439A48 *var_8 = unk_3C;
    RwReal var_C = arg_0;
    RwInt32 var_10 = 0;
    RwInt32 var_24 = ABS_(unk_10.x) < 1.0e-5f && ABS_(unk_10.y) < 1.0e-5f && ABS_(unk_10.z) < 1.0e-5f;
    type_3D3548 *var_28 = unk_30.sub_D4910();
    RpClump *var_2C = unk_94.unk_08;
    RwFrame *var_30 = RpClumpGetFrame(var_2C);
    RwFrame *var_34 = RwFrameGetParent(var_30);
    RwMatrix var_80 = *RwFrameGetMatrix(var_30);
    RwV3d var_8C;

    if (unk_15C)
    {
        if (var_34)
            vf_04C();
        return true;
    }
    if (!unk_12C)
    {
        RwV3dScale(&var_8C, &unk_10, arg_0);
        if (unk_8C)
        {
            unk_8C = 0;
        }
        else
        {
            RwReal var_90 = 0.5f * arg_0 * arg_0;
            RwReal var_94 = vf_020() * var_90;

            var_8C.y = var_8C.y + var_94;
        }
        RwV3dAdd(&var_8C, &var_80.pos, &var_8C);
        if (!unk_78)
        {
            unk_8C = 1;
            unk_10.x = unk_10.y = unk_10.z = 0.0f;
        }
        RwV3d var_A0;

        RwV3dSub(&var_A0, &var_80.pos, &var_8C);
        if (var_A0.x != 0.0f || var_A0.y != 0.0f || var_A0.z != 0.0f || unk_70 == 6)
        {
            type_161470 var_100;

            var_100.unk_00 = 1.0e37f;
            var_100.unk_0C = 0;
            var_100.unk_10 = 0;
            RwInt32 var_104 = 6;
            RwInt32 var_10C = unk_70 == var_104 && !unk_78;
            RpIntersection var_128;
            RwInt32 var_12C;

            if (!var_10C)
            {
                var_128.type = rpINTERSECTLINE;
                var_128.t.line.start = var_80.pos;
                var_128.t.line.end = var_8C;
                var_100.sub_161470();
                var_100.unk_14 = unk_24;
                var_100.unk_18 = var_28;
                var_100.unk_1C = unk_34;
                for (var_12C = 0; var_12C < 4; var_12C++)
                {
                    type_4E5D30 *var_130 = &dword_4E5D30[var_12C];

                    if (var_130->get_unk_00() && var_130->get_unk_28())
                    {
                        RpWorld *var_13C = var_130->unk_28;
                        type_91F40 var_168;

                        sub_91F40(var_13C, &var_128.t.line, &var_168, 1, 0x180000, 1); // not an address: line-test flags
                        if (var_168.unk_00 && var_168.unk_04 < var_100.unk_00)
                        {
                            var_100.unk_00 = var_168.unk_04;
                            var_100.unk_2C = var_168.unk_14;
                            var_100.unk_20 = var_168.unk_08;
                            var_100.unk_0C = 0;
                            var_100.unk_4C = material_data(((type_96E30 *)var_130->get_unk_28())
                                                               ->unk_10[(RwUInt16)((RpTriangle *)var_168.unk_00)->matIndex])->unk_04;
                        }
                    }
                }
            }
            else
            {
                var_128.type = rpINTERSECTSPHERE;
                var_128.t.sphere.center = var_80.pos;
                var_128.t.sphere.radius = dword_429E8C > dword_429E88 ? dword_429E8C : dword_429E88;
                var_100.sub_161470();
                var_100.unk_14 = unk_24;
                var_100.unk_18 = var_28;
                var_100.unk_1C = unk_34;
                var_100.unk_08 = (RwInt32)var_30;
                var_100.unk_50 = dword_429E88;
                var_100.unk_54 = dword_429E8C;
                var_100.unk_58 = 1;
            }
            for (var_12C = 0; var_12C < 4; var_12C++)
            {
                type_4E5D30 *var_17C = &dword_4E5D30[var_12C];

                if (var_17C->get_unk_00() && var_17C->get_unk_28())
                    RpWorldForAllAtomicIntersections(var_17C->get_unk_28(), &var_128, sub_1660C0, &var_100);
            }
            if (unk_4E5CD8.unk_00 && get_4E5D00())
                RpWorldForAllAtomicIntersections(get_4E5D00(), &var_128, sub_1660C0, &var_100);
            if (var_100.unk_00 <= 1.0f)
            {
                if (unk_3C->unk_00 == 5)
                {
                    unk_10.x = unk_10.y = unk_10.z = 0.0f;
                    unk_12C = 1;
                    sub_140CE0(&var_80, &var_100.unk_20, &var_100.unk_2C);
                    unk_04 = var_80.pos;
                    RwFrameTransform(var_30, &var_80, rwCOMBINEREPLACE);
                    dword_4B1E98.sub_8A980(&dword_4B1B58, 0, 0, &unk_04, 1, 0);
                }
                unk_A0++;
                var_C = var_100.unk_00 * arg_0;
                if (var_100.unk_0C)
                {
                    type_3D3548 *var_194 = sub_FB960(var_100.unk_0C);

                    if (var_194)
                    {
                        if (var_194->vf_00C() || var_194->vf_008())
                            var_10 = 1;
                        if (unk_12C)
                        {
                            RwInt32 var_198 = var_194->vf_174();

                            if (var_194->unk_28_0 || var_194->unk_28_9 || var_198 < 1)
                            {
                                unk_1C = 0;
                            }
                            else
                            {
                                unk_1A0.sub_D48D0(var_194);
                                switch (var_194->unk_2C & 0x3FFFFF0)
                                {
                                case 0x200000: // not an address: entity kind
                                case 0x20:
                                    {
                                        unk_13C = 2;
                                        RpHAnimHierarchy *var_1A0 = var_194->unk_284->unk_18;
                                        RwMatrix *var_1A4 = RpHAnimHierarchyGetMatrixArray(var_1A0);
                                        RwInt32 var_1A8 = var_1A0->numNodes;
                                        RwReal var_1AC = 1.0e7f;
                                        RwMatrix *var_1B0 = RwFrameGetMatrix(var_30);
                                        RwV3d var_1BC = var_1B0->pos;
                                        RwInt32 var_1C0;

                                        unk_140 = -1;
                                        for (var_1C0 = 0; var_1C0 < var_1A8; var_1C0++)
                                        {
                                            RwReal var_1C4 = (var_1BC.x - var_1A4[var_1C0].pos.x) * (var_1BC.x - var_1A4[var_1C0].pos.x)
                                                + (var_1BC.y - var_1A4[var_1C0].pos.y) * (var_1BC.y - var_1A4[var_1C0].pos.y)
                                                + (var_1BC.z - var_1A4[var_1C0].pos.z) * (var_1BC.z - var_1A4[var_1C0].pos.z);

                                            if (var_1C4 < var_1AC)
                                            {
                                                var_1AC = var_1C4;
                                                unk_140 = var_1C0;
                                            }
                                        }
                                        if (unk_140 != -1)
                                        {
                                            RwMatrix var_210 = var_1A4[unk_140];
                                            RwMatrix var_250;
                                            RwV3d var_25C;

                                            RwMatrixInvert(&var_250, &var_210);
                                            RwMatrixTransform(var_1B0, &var_250, rwCOMBINEPOSTCONCAT);
                                            unk_144 = var_1B0->pos;
                                            RwV3dScale(&var_25C, &var_1A4[unk_140].right, 5.0f);
                                            RwV3dAdd(&unk_144, &unk_144, &var_25C);
                                        }
                                        else
                                        {
                                            unk_13C = 1;
                                        }
                                    }
                                    break;
                                case 0x40000: // not an address: entity kind
                                case 0x2000000:
                                    {
                                        unk_13C = 3;
                                        RpHAnimHierarchy *var_260 = var_194->unk_284->unk_18;
                                        RwMatrix *var_264 = RpHAnimHierarchyGetMatrixArray(var_260);
                                        RwInt32 var_268 = var_260->numNodes;
                                        RwReal var_26C = 1.0e7f;
                                        RwMatrix var_2B0 = *RwFrameGetMatrix(var_30);
                                        RwV3d var_2BC = var_2B0.pos;
                                        RwInt32 var_2C0;

                                        unk_140 = -1;
                                        for (var_2C0 = 0; var_2C0 < var_268; var_2C0++)
                                        {
                                            RwReal var_2C4 = (var_2BC.x - var_264[var_2C0].pos.x) * (var_2BC.x - var_264[var_2C0].pos.x)
                                                + (var_2BC.y - var_264[var_2C0].pos.y) * (var_2BC.y - var_264[var_2C0].pos.y)
                                                + (var_2BC.z - var_264[var_2C0].pos.z) * (var_2BC.z - var_264[var_2C0].pos.z);

                                            if (var_2C4 < var_26C)
                                            {
                                                var_26C = var_2C4;
                                                unk_140 = var_2C0;
                                            }
                                        }
                                        if (unk_140 != -1)
                                        {
                                            RwMatrix var_310 = var_264[unk_140];
                                            RwMatrix var_350;

                                            RwMatrixInvert(&var_350, &var_310);
                                            RwMatrixTransform(&var_2B0, &var_350, rwCOMBINEPOSTCONCAT);
                                            unk_144 = var_2B0.pos;
                                        }
                                        else
                                        {
                                            unk_13C = 1;
                                        }
                                    }
                                    break;
                                default:
                                    {
                                        unk_13C = 1;
                                        RwFrame *var_358 = var_194->get_unk_340();
                                        RwMatrix *var_35C = RwFrameGetMatrix(var_358);
                                        RwMatrix var_3A0;

                                        unk_160 = *var_35C;
                                        RwMatrixInvert(&var_3A0, var_35C);
                                        RwMatrixTransform(&var_80, &var_3A0, rwCOMBINEPOSTCONCAT);
                                        RwFrameTransform(var_30, &var_80, rwCOMBINEREPLACE);
                                        RwFrameAddChild(var_358, var_30);
                                        unk_1A0.sub_D48D0(var_194);
                                    }
                                }
                                dword_4B1E98.sub_8A980(&dword_4B1B58, 0, 0, (RwV3d *)var_194->vf_0C4(), 1, 0);
                                RwReal var_3A4 = var_8->unk_50;

                                if (var_194->vf_098())
                                    sub_6B5F0("GrenadeIsFreakingOnMe", (type_67620 *)(var_194->vf_098()), 0, 0, (RwInt32 *)(&var_3A4), 1, 1, 0);
                            }
                        }
                        if (unk_70 == 6 && var_24 && var_10C && unk_A0 > 8)
                        {
                            RwInt32 var_3A8 = 0;

                            switch (var_194->unk_2C & 0x3FFFFF0)
                            {
                            case 0x1000000:
                            case 0x80:
                            case 0x40000: // not an address: entity kind
                            case 0x2000000:
                                var_3A8 = 1;
                                break;
                            default:
                                var_3A8 = 0;
                            }
                            if (var_3A8)
                                unk_1C -= var_8->unk_50;
                        }
                        type_439A48 *var_3B0 = unk_3C;
                        type_75600 var_3E0;
                        RwMatrix var_420;

                        var_3E0.unk_00_w = var_3B0->unk_00;
                        var_3E0.unk_02_w = 0;
                        var_3E0.unk_04 = (RwInt32)this;
                        var_3E0.unk_14 = (RwInt32)&var_100.unk_20;
                        var_3E0.unk_18 = (RwInt32)&var_100.unk_2C;
                        var_3E0.unk_20 = &var_100.unk_38;
                        var_3E0.unk_1C = (RwInt32)&var_420;
                        var_3E0.unk_08 = unk_24;
                        var_3E0.unk_0C = var_28;
                        var_3E0.unk_10 = unk_34;
                        var_3E0.unk_28 = 0;
                        var_3E0.unk_2C = 0;
                        var_3E0.unk_24 = var_100.unk_44;
                        var_194->vf_064(&var_3E0);
                    }
                }
                if (!unk_12C)
                {
                    RwReal var_424 = RwV3dLength((RwV3d *)&var_A0);
                    RwReal var_428 = var_100.unk_00 * var_424;

                    if (dword_429E80 > var_428)
                    {
                        if (var_428 < 0.0f)
                            var_8C = var_100.unk_20;
                        else
                            var_8C = var_128.t.line.start;
                    }
                    else
                    {
                        RwV3d var_434;

                        var_8C = var_100.unk_20;
                        RwV3dNormalize(&var_434, &var_A0);
                        RwV3dIncrementScaledMacro(&var_8C, &var_434, dword_429E80);
                    }
                    RwReal var_438 = RwV3dDotProduct(&unk_10, &var_100.unk_2C);

                    RwV3dIncrementScaledMacro(&unk_10, &var_100.unk_2C, -2.0f * var_438);
                    RwV3d var_444;

                    if (var_100.unk_2C.x == 0.0f && var_100.unk_2C.y == 0.0f && var_100.unk_2C.z == 0.0f)
                    {
                        var_444 = unk_10;
                        RwV3dNormalize(&var_444, &var_444);
                    }
                    else
                    {
                        var_444 = var_100.unk_2C;
                    }
                    RwReal var_448 = RwV3dDotProduct(&unk_10, &var_444);
                    RwV3d var_454;
                    RwV3d var_460;

                    RwV3dScale(&var_454, &var_444, var_448);
                    RwV3dSub(&var_460, &unk_10, &var_454);
                    RwV3dScale(&var_460, &var_460, var_8->unk_48);
                    RwInt32 var_468 = RwV3dDotProduct(&var_454, &var_454) < dword_429E84;

                    if (var_10)
                    {
                        RwV3dScale(&var_454, &var_454, var_8->unk_44 * var_8->unk_44);
                        if (!var_468)
                        {
                            vf_024(&var_100.unk_20, &dword_4B1B50, -2, var_28, 0);
                        }
                        else if (!unk_A4)
                        {
                            vf_024(&var_100.unk_20, &dword_4B1B50, -2, var_28, 0);
                            unk_A4 = 1;
                        }
                    }
                    else
                    {
                        RwV3dScale(&var_454, &var_454, var_8->unk_44);
                        if (!var_468)
                        {
                            vf_024(&var_100.unk_20, &dword_4B1C38, -2, var_28, 0);
                        }
                        else if (!unk_A4)
                        {
                            vf_024(&var_100.unk_20, &dword_4B1C38, -2, var_28, 0);
                            unk_A4 = 1;
                        }
                    }
                    if (var_468)
                        var_454.x = var_454.y = var_454.z = 0.0f;
                    RwV3dAdd(&unk_10, &var_454, &var_460);
                    if (unk_70 == 6 && ABS_(unk_10.x) < 0.1f && ABS_(unk_10.y) < 0.1f && ABS_(unk_10.z) < 0.1f)
                    {
                        unk_78 = 0;
                        unk_8C = 1;
                    }
                    if (!var_10)
                    {
                        unk_158++;
                        if (unk_158 >= 4 && RwV3dLength((RwV3d *)&unk_10) < 50.0f)
                        {
                            sub_164210(&unk_04, &unk_10, &unk_130);
                            type_161FC0_alert var_480;

                            var_480.unk_00 = 0;
                            var_480.unk_04 = var_8->unk_50;
                            var_480.unk_08 = unk_154;
                            RwReal var_484 = (unk_3C->unk_4C + 300.0f) * (unk_3C->unk_4C + 300.0f);

                            if (dword_4B87C8 - unk_1C + 3.0f < var_8->unk_50)
                            {
                                RwInt32 var_488;

                                for (var_488 = 0; var_488 < 32; var_488++)
                                {
                                    type_3D3548 *var_48C = unk_438CA8[var_488].sub_D4910();

                                    if (var_48C && !unk_A8[var_488].sub_D4910())
                                    {
                                        RwReal var_490 = sub_140C90(var_48C->sub_CD550(), &unk_130);

                                        if (var_490 < var_484)
                                        {
                                            RwV3d var_49C;

                                            RwV3dSub(&var_49C, var_48C->sub_CD550(), &unk_130);
                                            var_480.unk_00 = RwV3dLength((RwV3d *)&var_49C);
                                            sub_6B5F0("GrenadeAlert", (type_67620 *)(var_48C->vf_098()), 0, 0, (RwInt32 *)(&var_480), 3, 1, 0);
                                            if (var_48C->vf_008())
                                                var_48C->vf_008()->unk_610 = (type_3DAFC8_610 *)this;
                                            unk_A8[var_488] = unk_438CA8[var_488];
                                            if (!var_48C->vf_00C())
                                            {
                                                if (unk_154 <= 0)
                                                    var_48C->unk_1C0.sub_8A980(&dword_4B1C38, var_48C, 2, var_48C->sub_CD550(), 0, 0);
                                                unk_154++;
                                                var_480.unk_08 = unk_154;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    RwV3dCrossProduct(&unk_7C, &var_80.at, &var_444);
                    RwReal var_4A0 = 0;

                    if (RwV3dDotProduct(&unk_7C, &unk_7C) > 1.0e-4f)
                    {
                        RwV3dNormalize(&unk_7C, &unk_7C);
                        var_4A0 = acos(0.99999f > ((var_4A0 = RwV3dDotProduct(&var_444, &var_80.at)) > -0.99999f
                                                       ? var_4A0 : -0.99999f)
                                           ? (var_4A0 > -0.99999f ? var_4A0 : -0.99999f) : 0.99999f) * 57.295776f;
                        if (dword_429E78 * arg_0 >= var_4A0)
                            var_4A0 = var_4A0 / arg_0;
                        else
                            var_4A0 = dword_429E78;
                        unk_7C.x = RwV3dDotProduct(&unk_7C, &var_80.right);
                        unk_7C.y = RwV3dDotProduct(&unk_7C, &var_80.up);
                        unk_7C.z = RwV3dDotProduct(&unk_7C, &var_80.at);
                    }
                    unk_88 = var_4A0;
                }
            }
        }
    }
    else
    {
        type_3D3548 *var_4B4 = unk_1A0.sub_D4910();

        if (var_4B4)
        {
            var_34 = RwFrameGetParent(var_30);
            if (!var_4B4)
                return false;
            RwInt32 var_4B8 = var_4B4->vf_174();
            RwMatrix *var_4BC;

            if (var_4B4->unk_28_0 || var_4B4->unk_28_9 || var_4B8 < 1 || unk_13C == 1 && !var_34)
            {
                if (unk_13C == 1 && var_34)
                {
                    RwFrameRemoveChild(var_30);
                    var_4BC = &unk_160;
                }
                unk_1C = 0;
            }
            switch (unk_13C)
            {
            case 1:
                if (var_34)
                {
                    var_4BC = RwFrameGetMatrix(var_34);
                    unk_160 = *var_4BC;
                    var_80 = *RwFrameGetMatrix(var_30);
                    RwMatrixTransform(&var_80, var_4BC, rwCOMBINEPOSTCONCAT);
                    unk_04 = var_80.pos;
                }
                break;
            case 2:
            case 3:
                {
                    type_3D3548 *var_4C4 = unk_1A0.sub_D4910();

                    if (var_4C4)
                    {
                        RpHAnimHierarchy *var_4C8 = var_4C4->unk_284->unk_18;
                        RwMatrix *var_4CC = RpHAnimHierarchyGetMatrixArray(var_4C8);
                        RwMatrix var_510;

                        RwMatrixSetIdentity(&var_510);
                        var_510.pos = unk_144;
                        RwMatrixTransform(&var_510, &var_4CC[unk_140], rwCOMBINEPOSTCONCAT);
                        RwMatrix *var_514 = RwFrameGetMatrix(var_30);

                        *var_514 = var_510;
                        RwFrameUpdateObjects(var_30);
                    }
                }
                break;
            }
        }
    }
    if (dword_4B87C8 - unk_1C > var_8->unk_50)
    {
        RwFrame *var_518 = RwFrameGetParent(var_30);

        if (var_518)
        {
            vf_04C();
            var_80 = *RwFrameGetMatrix(var_30);
        }
        type_161FC0_explode var_528;
        RwInt32 var_52C;

        var_528.unk_00.x = unk_04.x;
        var_528.unk_00.y = unk_04.y;
        var_528.unk_00.z = unk_04.z;
        var_528.unk_0C = 0;
        for (var_52C = 0; var_52C < 32; var_52C++)
        {
            if (unk_A8[var_52C].sub_D4910())
            {
                RwV3d var_538;

                RwV3dSub(&var_538, unk_A8[var_52C].sub_D4910()->sub_CD550(), &unk_04);
                var_528.unk_0C = RwV3dLength((RwV3d *)&var_538);
                type_3D3548 *var_53C = unk_A8[var_52C].sub_D4910();

                sub_6B5F0("GrenadeExplode", (type_67620 *)(var_53C->vf_098()), 0, 0, (RwInt32 *)(&var_528), 4, 1, 0);
            }
        }
        unk_128 = 1;
        type_439A48 *var_540 = unk_3C;

        vf_024(&var_80.pos, &dword_4B1B20, -2, var_28, 0);
        vf_038(&var_80);
        unk_4E5E50.sub_176180(8, &var_80.pos, 1.0f, 0);
        sub_1614E0(&var_80, var_28, var_540);
        if (!var_518)
            unk_04 = var_8C;
        return true;
    }
    if (!unk_12C)
    {
        unk_04 = var_8C;
        var_80.pos = var_8C;
        RwReal var_544 = arg_0 * unk_88;

        if (!unk_8C && var_544 != 0.0f && unk_70 != 6)
            RwMatrixRotate(&var_80, &unk_7C, var_544, rwCOMBINEPRECONCAT);
        RwFrameTransform(var_30, &var_80, rwCOMBINEREPLACE);
        if (var_C != arg_0 && dword_429E7C > dword_4E1B60)
        {
            // A check compiled out of this build (it moves the registers one step).
            if (unk_78)
            {
            }
            dword_4E1B60++;
            vf_014(arg_0 - var_C);
            dword_4E1B60 = 0;
        }
        else if (!unk_8C)
        {
            vf_01C(var_C);
        }
    }
    return false;
}
// match: ?sub_164210@@YAXPAURwV3d@@00@Z @ 0x00164210
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The grenade's step (vf_014): a velocity from arg_0 and arg_4 under the
// gravity dword_429E90, into *arg_8 (its y from arg_0; the local's y is
// never set).
void sub_164210(RwV3d *arg_0, RwV3d *arg_4, RwV3d *arg_8)
{
    RwReal var_14;
    RwReal lv_10;
    RwV3d var_C;

    var_C.x = -(var_14 = arg_4->x - dword_429E90 * arg_0->x) / dword_429E90;
    var_C.z = -(lv_10 = arg_4->z - dword_429E90 * arg_0->z) / dword_429E90;
    *arg_8 = var_C;
    arg_8->y = arg_0->y;
}
// match: ?vf_04C@type_3DC8B8@@UAEXXZ @ 0x00164280
// Set off while held (unk_13C 1, its model on a frame and an entity in
// unk_1A0): its model taken off the frame to where the frame is, and its
// position from it.
void type_3DC8B8::vf_04C()
{
    RwFrame *var_C;
    RwFrame *var_10;
    type_3D3548 *var_14;
    RwMatrix *var_18;
    RwMatrix var_60;

    if (unk_13C == 1)
    {
        var_C = RpClumpGetFrame(unk_94.get_unk_08());
        var_10 = RwFrameGetParent(var_C);
        if (var_10)
        {
            var_14 = unk_1A0.sub_D4910();
            if (!var_14)
                return;
            var_18 = RwFrameGetMatrix(var_10);
            RwFrameRemoveChild(var_C);
            RwFrameTransform(var_C, var_18, rwCOMBINEPOSTCONCAT);
            var_60 = *RwFrameGetMatrix(var_C);
            unk_04 = var_60.pos;
        }
    }
}
// match: ?vf_038@type_3DC8B8@@UAEXPAURwMatrixTag@@@Z @ 0x00164350
void type_3DC8B8::vf_038(RwMatrix *arg_0)
{
    sub_F2FF0(0x7F1EBD6D, arg_0, 0, 1, 0, 0); // not an address: a particle system's name hash
    sub_F2FF0(0x53BAD95A, arg_0, 0, 1, 0, 0); // not an address: a particle system's name hash
    sub_F2FF0(0xF9933423, arg_0, 0, 1, 0, 0); // not an address: a particle system's name hash
}
// match: ?vf_000@type_3DC798@@UAEXHPAUtype_3D3548@@PAUtype_439A48@@PAUtype_429E54@@@Z @ 0x001643B0
void type_3DC798::vf_000(RwInt32 arg_0, type_3D3548 *arg_4, type_439A48 *arg_8, type_429E54 *arg_C)
{
    type_439A48 *var_4;

    var_4 = arg_8;
    type_3DC7F8::vf_000(arg_0, arg_4, arg_8, 0);
    unk_70.sub_129620(RpClumpClone((RpClump *)var_4->unk_38));
}
// match: ?vf_004@type_3DC798@@UAEHXZ @ 0x00164400
RwInt32 type_3DC798::vf_004()
{
    type_3DC7F8::vf_004();
    if (unk_70.get_unk_08())
        unk_70.sub_129940(0);
    return 1;
}
// match: ?vf_008@type_3DC798@@UAEXPAURwMatrixTag@@@Z @ 0x00164440
void type_3DC798::vf_008(RwMatrix *arg_0)
{
    RwFrame *var_4;

    var_4 = RpClumpGetFrame(unk_70.get_unk_08());
    *RwFrameGetMatrix(var_4) = *arg_0;
    sub_173180(unk_70.get_unk_08());
}
// match: ?vf_02C@type_3DC798@@UAEXHPAURwMatrixTag@@PAUtype_3D3548@@H@Z @ 0x00164490
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The surface arg_0's particles and decal (with arg_C), or with none its
// own blast effects; its sound; and its blast when it has one (vf_040).
void type_3DC798::vf_02C(RwInt32 arg_0, RwMatrix *arg_4, type_3D3548 *arg_8, RwInt32 arg_C)
{
    RwInt32 var_10;
    RwInt32 var_C;
    type_4E5E40 *bp_8;
    type_4E5E40_08 *bp_4;

    arg_0 &= 0xFFFF;
    if (arg_0 != 0xFFFF)
    {
        bp_8 = &dword_4E5E40;
        bp_4 = bp_8->unk_08;
        if (bp_4 && (RwUInt32)arg_0 < bp_8->unk_00[1])
        {
            var_10 = bp_4[arg_0].unk_04[0];
            if (var_10 > -1)
                sub_F2750(1, var_10, arg_4, 1);
            if (arg_C)
            {
                var_C = bp_4[arg_0].unk_04[1];
                if (var_C > -1)
                    sub_F04E0(arg_4, var_C, 0);
            }
        }
    }
    else
    {
        if (unk_3C->unk_00 == 3)
            vf_038(arg_4);
        else
            vf_038(arg_4);
    }
    dword_4B1E98.sub_8A980(&dword_4B1F1C, arg_8, 0, &arg_4->pos, 0, 0);
    if (vf_040())
        sub_1614E0(arg_4, arg_8, unk_3C);
}
// match: ?vf_028@type_3DC798@@UAEXPAUtype_3D3548@@PAURwMatrixTag@@0@Z @ 0x001645B0
void type_3DC798::vf_028(type_3D3548 *arg_0, RwMatrix *arg_4, type_3D3548 *arg_8)
{
    RwInt32 var_4;

    var_4 = -1;
    if (arg_0)
    {
        var_4 = arg_0->vf_1D4();
        if (arg_0->vf_024() || arg_0->vf_008())
            var_4 = -1;
    }
    type_3DC798::vf_02C(var_4, arg_4, arg_8, 0);
}
// match: ?vf_014@type_3DC798@@UAE_NM@Z @ 0x00164620
// Its step: its model moved by its velocity (and gravity, vf_020) unless the
// line there meets the worlds or an atomic; a hit (unless on its owner's
// own vehicle) makes an impact effect near the line's end, shakes and
// shoots the entity (vf_064, then vf_028) or marks the surface (vf_02C),
// and ends it where it hit. True when it is done.
bool type_3DC798::vf_014(RwReal arg_0)
{
    type_3D3548 *var_8;
    RpClump *var_C;
    RwFrame *var_10;
    RwMatrix var_50;
    RwV3d var_5C;
    RwReal var_60;
    RwReal var_64;
    type_161470 var_C8;
    RpIntersection var_E4;
    RwInt32 var_E8;

    var_8 = unk_30.sub_D4910();
    var_C = unk_70.unk_08;
    var_10 = RpClumpGetFrame(var_C);
    var_50 = *RwFrameGetMatrix(var_10);
    RwV3dScale(&var_5C, &unk_10, arg_0);
    var_60 = 0.5f * arg_0 * arg_0;
    var_64 = vf_020() * var_60;
    var_5C.y = var_5C.y + var_64;
    RwV3dAdd(&var_5C, &var_50.pos, &var_5C);
    var_C8.unk_00 = 1.0e37f;
    var_C8.unk_0C = 0;
    var_C8.unk_10 = 0;
    var_E4.type = rpINTERSECTLINE;
    var_E4.t.line.start = var_50.pos;
    var_E4.t.line.end = var_5C;
    var_C8.sub_161470();
    var_C8.unk_20.x = 0;
    var_C8.unk_20.y = 0;
    var_C8.unk_20.z = 0;
    var_C8.unk_2C.x = 0;
    var_C8.unk_2C.y = 0;
    var_C8.unk_2C.z = 1.0f;
    var_C8.unk_14 = unk_24;
    var_C8.unk_18 = var_8;
    var_C8.unk_1C = unk_34;
    for (var_E8 = 0; var_E8 < 4; var_E8++)
    {
        type_4E5D30 *var_EC = &dword_4E5D30[var_E8];

        if (var_EC->get_unk_00() && var_EC->get_unk_28())
        {
            RpWorld *var_F8 = var_EC->unk_28;
            type_91F40 var_124;

            sub_91F40(var_F8, &var_E4.t.line, &var_124, 1, 0x180000, 1); // not an address: line-test flags
            if (var_124.unk_00 && var_124.unk_04 < var_C8.unk_00)
            {
                var_C8.unk_00 = var_124.unk_04;
                var_C8.unk_2C = var_124.unk_14;
                var_C8.unk_20 = var_124.unk_08;
                var_C8.unk_0C = 0;
                var_C8.unk_4C = material_data(((type_96E30 *)var_EC->get_unk_28())
                                                  ->unk_10[(RwUInt16)((RpTriangle *)var_124.unk_00)->matIndex])->unk_04;
            }
        }
    }
    for (var_E8 = 0; var_E8 < 4; var_E8++)
    {
        type_4E5D30 *var_134 = &dword_4E5D30[var_E8];

        if (var_134->get_unk_00() && var_134->get_unk_28())
            RpWorldForAllAtomicIntersections(var_134->get_unk_28(), &var_E4, sub_1660C0, &var_C8);
    }
    if (unk_4E5CD8.unk_00 && get_4E5D00())
        RpWorldForAllAtomicIntersections(get_4E5D00(), &var_E4, sub_1660C0, &var_C8);
    bool var_14D = dword_4B87C8 - unk_1C > unk_20;
    bool var_14E = false;
    if (var_8)
        var_14E = var_8->vf_00C() && var_C8.unk_0C && var_8->vf_00C()->vf_200() == sub_FB960(var_C8.unk_0C);
    if (!var_14E)
    {
        if (var_C8.unk_00 <= 1.0f || var_14D && vf_03C())
        {
            RwInt32 var_15C = 1;
            RwV3d var_168;
            RwV3d var_174;
            RwMatrix var_1C0;

            if (var_C8.unk_00 <= 1.0f)
                unk_4E5E50.sub_176180(8, &var_C8.unk_20, 1.0f, 0);
            var_168.x = 0;
            var_168.y = 1.0f;
            var_168.z = 0;
            if (var_14D && vf_03C())
            {
                RwV3dNormalize(&var_174, &unk_10);
                sub_140F00(&var_1C0, &var_5C, &unk_10);
            }
            else if (RwV3dDotProduct(&var_C8.unk_2C, &var_C8.unk_2C) < 0.9f)
            {
                RwV3d var_1CC;

                RwV3dScale(&var_1CC, &unk_10, -1.0f);
                RwV3dNormalize(&var_1CC, &var_1CC);
                sub_140F00(&var_1C0, &var_C8.unk_20, &var_1CC);
            }
            else
            {
                sub_140F00(&var_1C0, &var_C8.unk_20, &var_C8.unk_2C);
            }
            if (var_C8.unk_0C)
            {
                type_3D3548 *var_1D0 = sub_FB960(var_C8.unk_0C);

                if (var_1D0)
                {
                    if (var_C8.unk_18 && (var_C8.unk_18->unk_24 & 1) && (var_C8.unk_18->unk_20 & 8))
                        sub_D4950(var_1D0);
                    type_439A48 *var_1D4 = unk_3C;
                    type_75600 var_204;

                    var_204.unk_00_w = var_1D4->unk_00;
                    var_204.unk_02_w = 0;
                    var_204.unk_04 = (RwInt32)this;
                    var_204.unk_14 = (RwInt32)&var_C8.unk_20;
                    var_204.unk_18 = (RwInt32)&var_C8.unk_2C;
                    var_204.unk_20 = &var_C8.unk_38;
                    var_204.unk_1C = (RwInt32)&var_1C0;
                    var_204.unk_08 = unk_24;
                    var_204.unk_0C = var_8;
                    var_204.unk_10 = unk_34;
                    var_204.unk_28 = var_1D4->unk_04;
                    var_204.unk_2C = var_1D4->unk_04;
                    var_204.unk_24 = var_C8.unk_44;
                    var_1D0->vf_064(&var_204);
                }
                vf_028(var_1D0, &var_1C0, var_8);
            }
            else
            {
                switch (var_C8.unk_4C & 0xFFFF)
                {
                default:
                    if (unk_3C->unk_00 == 3)
                        vf_02C(var_C8.unk_4C & 0xFFFF, &var_1C0, var_8, 1);
                    else
                        vf_02C(var_C8.unk_4C & 0xFFFF, &var_1C0, var_8, 1);
                    break;
                case 0x38:
                    var_15C = 0;
                    break;
                }
            }
            unk_04 = var_1C0.pos;
            if (var_15C)
                return true;
        }
    }
    if (var_14D)
    {
        unk_04 = var_5C;
        return true;
    }
    unk_04 = var_5C;
    var_50.pos = var_5C;
    RwFrameTransform(var_10, &var_50, rwCOMBINEREPLACE);
    vf_01C(arg_0);
    return false;
}
// match: ?vf_038@type_3DC798@@UAEXPAURwMatrixTag@@@Z @ 0x00164EE0
void type_3DC798::vf_038(RwMatrix *arg_0)
{
    sub_F2FF0(0xFC34701D, arg_0, 0, 1, 0, 1); // not an address: a particle system's name hash
    sub_F2FF0(0x6D27082E, arg_0, 0, 1, 0, 1); // not an address: a particle system's name hash
    sub_F2FF0(0x3010F21D, arg_0, 0, 1, 0, 1); // not an address: a particle system's name hash
    sub_F2FF0(0xE46D3977, arg_0, 0, 1, 0, 1); // not an address: a particle system's name hash
    sub_F2FF0(0xF8E85410, arg_0, 0, 1, 0, 1); // not an address: a particle system's name hash
    sub_F2FF0(0x7A855E3F, arg_0, 0, 1, 0, 1); // not an address: a particle system's name hash
}
// match: ?vf_000@type_3DC858@@UAEXHPAUtype_3D3548@@PAUtype_439A48@@PAUtype_429E54@@@Z @ 0x00164F90
void type_3DC858::vf_000(RwInt32 arg_0, type_3D3548 *arg_4, type_439A48 *arg_8, type_429E54 *arg_C)
{
    type_439A48 *var_4;

    var_4 = arg_8;
    type_3DC7F8::vf_000(arg_0, arg_4, arg_8, 0);
    unk_7C.sub_129620(RpClumpClone((RpClump *)var_4->unk_38));
    unk_70.sub_F2880(0);
}
// match: ?vf_004@type_3DC858@@UAEHXZ @ 0x00164FF0
RwInt32 type_3DC858::vf_004()
{
    type_3DC7F8::vf_004();
    if (unk_7C.get_unk_08())
        unk_7C.sub_129940(0);
    return 1;
}
// match: ?vf_008@type_3DC858@@UAEXPAURwMatrixTag@@@Z @ 0x00165030
void type_3DC858::vf_008(RwMatrix *arg_0)
{
    RwFrame *var_4;

    var_4 = RpClumpGetFrame(unk_7C.get_unk_08());
    *RwFrameGetMatrix(var_4) = *arg_0;
    sub_173180(unk_7C.get_unk_08());
}
// match: ?vf_02C@type_3DC858@@UAEXHPAURwMatrixTag@@PAUtype_3D3548@@H@Z @ 0x00165080
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3DC858::vf_02C(RwInt32 arg_0, RwMatrix *arg_4, type_3D3548 *arg_8, RwInt32 arg_C)
{
    RwInt32 var_10;
    RwInt32 var_C;
    type_4E5E40 *bp_8;
    type_4E5E40_08 *bp_4;

    arg_0 &= 0xFFFF;
    if (arg_0 != 0xFFFF)
    {
        bp_8 = &dword_4E5E40;
        bp_4 = bp_8->unk_08;
        if (bp_4 && (RwUInt32)arg_0 < bp_8->unk_00[1])
        {
            var_10 = bp_4[arg_0].unk_04[0];
            if (var_10 > -1)
                sub_F2750(3, var_10, arg_4, 0);
            if (arg_C)
            {
                var_C = bp_4[arg_0].unk_04[1];
                if (var_C > -1)
                    sub_F04E0(arg_4, var_C, 0);
            }
        }
    }
    if (vf_040())
    {
        sub_1614E0(arg_4, arg_8, unk_3C);
        dword_4B1E98.sub_8A980(&dword_4B1C48, arg_8, 0, &arg_4->pos, 0, 0);
        vf_038(arg_4);
    }
}
// match: ?vf_028@type_3DC858@@UAEXPAUtype_3D3548@@PAURwMatrixTag@@0@Z @ 0x00165180
void type_3DC858::vf_028(type_3D3548 *arg_0, RwMatrix *arg_4, type_3D3548 *arg_8)
{
    RwInt32 var_4;

    var_4 = -1;
    if (arg_0)
        var_4 = arg_0->vf_1D4();
    type_3DC858::vf_02C(var_4, arg_4, arg_8, 0);
}
// match: ?vf_014@type_3DC858@@UAE_NM@Z @ 0x001651D0
// Its step: as the model projectile's (without the vehicle and impact
// checks), its particle system destroyed when it ends.
bool type_3DC858::vf_014(RwReal arg_0)
{
    type_3D3548 *var_8;
    RpClump *var_C;
    RwFrame *var_10;
    RwMatrix var_50;
    RwV3d var_5C;
    RwReal var_60;
    RwReal var_64;
    type_161470 var_C8;
    RpIntersection var_E4;
    RwInt32 var_E8;

    var_8 = unk_30.sub_D4910();
    var_C = unk_7C.unk_08;
    var_10 = RpClumpGetFrame(var_C);
    var_50 = *RwFrameGetMatrix(var_10);
    RwV3dScale(&var_5C, &unk_10, arg_0);
    var_60 = 0.5f * arg_0 * arg_0;
    var_64 = vf_020() * var_60;
    var_5C.y = var_5C.y + var_64;
    RwV3dAdd(&var_5C, &var_50.pos, &var_5C);
    var_C8.unk_00 = 1.0e37f;
    var_C8.unk_0C = 0;
    var_C8.unk_10 = 0;
    var_E4.type = rpINTERSECTLINE;
    var_E4.t.line.start = var_50.pos;
    var_E4.t.line.end = var_5C;
    var_C8.sub_161470();
    var_C8.unk_14 = unk_24;
    var_C8.unk_18 = var_8;
    var_C8.unk_1C = unk_34;
    for (var_E8 = 0; var_E8 < 4; var_E8++)
    {
        type_4E5D30 *var_EC = &dword_4E5D30[var_E8];

        if (var_EC->get_unk_00() && var_EC->get_unk_28())
        {
            RpWorld *var_F8 = var_EC->unk_28;
            type_91F40 var_124;

            sub_91F40(var_F8, &var_E4.t.line, &var_124, 1, 0x180000, 1); // not an address: line-test flags
            if (var_124.unk_00 && var_124.unk_04 < var_C8.unk_00)
            {
                var_C8.unk_00 = var_124.unk_04;
                var_C8.unk_2C = var_124.unk_14;
                var_C8.unk_20 = var_124.unk_08;
                var_C8.unk_0C = 0;
                var_C8.unk_4C = material_data(((type_96E30 *)var_EC->get_unk_28())
                                                  ->unk_10[(RwUInt16)((RpTriangle *)var_124.unk_00)->matIndex])->unk_04;
            }
        }
    }
    for (var_E8 = 0; var_E8 < 4; var_E8++)
    {
        type_4E5D30 *var_134 = &dword_4E5D30[var_E8];

        if (var_134->get_unk_00() && var_134->get_unk_28())
            RpWorldForAllAtomicIntersections(var_134->get_unk_28(), &var_E4, sub_1660C0, &var_C8);
    }
    if (unk_4E5CD8.unk_00 && get_4E5D00())
        RpWorldForAllAtomicIntersections(get_4E5D00(), &var_E4, sub_1660C0, &var_C8);
    bool var_14D = dword_4B87C8 - unk_1C > unk_20;
    if (var_C8.unk_00 <= 1.0f || var_14D && vf_03C())
    {
        RwV3d var_15C;
        RwV3d var_170;
        RwMatrix var_1B0;

        var_15C.x = 0;
        var_15C.y = 1.0f;
        var_15C.z = 0;
        if (unk_70.get_unk_08())
        {
            sub_F3300(unk_70.get_unk_08());
            unk_70.sub_F2880(0);
        }
        if (var_14D && vf_03C())
        {
            RwV3dNormalize(&var_170, &unk_10);
            sub_140F00(&var_1B0, &var_5C, &unk_10);
        }
        else if (RwV3dDotProduct(&var_C8.unk_2C, &var_C8.unk_2C) < 0.9f)
        {
            RwV3d var_1BC;

            RwV3dScale(&var_1BC, &unk_10, -1.0f);
            RwV3dNormalize(&var_1BC, &var_1BC);
            sub_140F00(&var_1B0, &var_C8.unk_20, &var_1BC);
        }
        else
        {
            sub_140F00(&var_1B0, &var_C8.unk_20, &var_C8.unk_2C);
        }
        if (var_C8.unk_0C)
        {
            type_3D3548 *var_1C0 = sub_FB960(var_C8.unk_0C);

            if (var_1C0)
            {
                type_439A48 *var_1C4 = unk_3C;
                type_75600 var_1F4;

                var_1F4.unk_00_w = var_1C4->unk_00;
                var_1F4.unk_02_w = 0;
                var_1F4.unk_04 = (RwInt32)this;
                var_1F4.unk_14 = (RwInt32)&var_C8.unk_20;
                var_1F4.unk_18 = (RwInt32)&var_C8.unk_2C;
                var_1F4.unk_20 = &var_C8.unk_38;
                var_1F4.unk_1C = (RwInt32)&var_1B0;
                var_1F4.unk_08 = unk_24;
                var_1F4.unk_0C = var_8;
                var_1F4.unk_10 = unk_34;
                var_1F4.unk_28 = var_1C4->unk_04;
                var_1F4.unk_2C = var_1C4->unk_04;
                var_1F4.unk_24 = var_C8.unk_44;
                var_1C0->vf_064(&var_1F4);
            }
            vf_028(var_1C0, &var_1B0, var_8);
        }
        else
        {
            vf_02C(var_C8.unk_4C & 0xFFFF, &var_1B0, var_8, 0);
        }
        unk_04 = var_1B0.pos;
        return true;
    }
    if (var_14D)
    {
        unk_04 = var_5C;
        if (unk_70.get_unk_08())
        {
            sub_F3300(unk_70.get_unk_08());
            unk_70.sub_F2880(0);
        }
        return true;
    }
    unk_04 = var_5C;
    var_50.pos = var_5C;
    RwFrameTransform(var_10, &var_50, rwCOMBINEREPLACE);
    vf_01C(arg_0);
    return false;
}
// match: ?vf_01C@type_3DC858@@UAEXM@Z @ 0x00165980
// Its fall by arg_0 (the settings' gravity unk_40 when unk_3C is set); the
// model projectile's and the grenade's slot too (folded by /OPT:ICF).
void type_3DC858::vf_01C(RwReal arg_0)
{
    type_439A48 *var_4;

    var_4 = unk_3C;
    if (var_4->unk_3C)
        unk_10.y = arg_0 * var_4->unk_40 + unk_10.y;
}
// match: ?vf_038@type_3DC858@@UAEXPAURwMatrixTag@@@Z @ 0x001659C0
// Six effects at the matrix arg_0 (the kind-8 projectile's slot too).
void type_3DC858::vf_038(RwMatrix *arg_0)
{
    sub_F2FF0(0xFC34701D, arg_0, 0, 1, 0, 0); // not an address: a particle system's name hash
    sub_F2FF0(0x6D27082E, arg_0, 0, 1, 0, 0); // not an address: a particle system's name hash
    sub_F2FF0(0x3010F21D, arg_0, 0, 1, 0, 0); // not an address: a particle system's name hash
    sub_F2FF0(0xE46D3977, arg_0, 0, 1, 0, 0); // not an address: a particle system's name hash
    sub_F2FF0(0xF8E85410, arg_0, 0, 1, 0, 0); // not an address: a particle system's name hash
    sub_F2FF0(0x7A855E3F, arg_0, 0, 1, 0, 0); // not an address: a particle system's name hash
}
// match: ?vf_000@type_3DC738@@UAEXHPAUtype_3D3548@@PAUtype_439A48@@PAUtype_429E54@@@Z @ 0x00165A70
void type_3DC738::vf_000(RwInt32 arg_0, type_3D3548 *arg_4, type_439A48 *arg_8, type_429E54 *arg_C)
{
    type_439A48_84 *var_4;

    var_4 = (type_439A48_84 *)arg_8;
    type_3DC7F8::vf_000(arg_0, arg_4, arg_8, arg_C);
    unk_78 = var_4->unk_40;
    unk_84 = var_4->unk_90;
    unk_7C = var_4->unk_88;
    unk_80 = var_4->unk_8C;
    unk_70 = var_4->unk_04;
    unk_74 = var_4->unk_4C;
    unk_88 = var_4->unk_84;
    unk_20 = var_4->unk_94 * 60.0f;
}
// match: ?vf_004@type_3DC738@@UAEHXZ @ 0x00165B20
RwInt32 type_3DC738::vf_004()
{
    type_3DC7F8::vf_004();
    return 1;
}
// match: ?vf_01C@type_3DC738@@UAEXM@Z @ 0x00165B40
// Its fall by arg_0: after its delay (unk_80), its fall speed grows by
// unk_7C up to the speed it has.
void type_3DC738::vf_01C(RwReal arg_0)
{
    RwReal var_4;

    if (unk_84 && unk_80 <= 0.0f)
    {
        unk_78 = unk_78 - arg_0 * unk_7C;
        var_4 = arg_0 * unk_78;
        if (-var_4 < unk_10.y)
            unk_10.y = arg_0 * unk_78 + unk_10.y;
    }
    else
    {
        unk_80 = unk_80 - arg_0;
        unk_10.y = arg_0 * unk_78 + unk_10.y;
    }
}
// match: ?vf_000@type_3DC6D8@@UAEXHPAUtype_3D3548@@PAUtype_439A48@@PAUtype_429E54@@@Z @ 0x00165BF0
void type_3DC6D8::vf_000(RwInt32 arg_0, type_3D3548 *arg_4, type_439A48 *arg_8, type_429E54 *arg_C)
{
    type_439A48_84 *var_4;

    var_4 = (type_439A48_84 *)arg_8;
    type_3DC7F8::vf_000(arg_0, arg_4, arg_8, 0);
    unk_70.sub_129620(RpClumpClone((RpClump *)var_4->unk_38));
    unk_98 = var_4->unk_40;
    unk_A4 = var_4->unk_90;
    unk_9C = var_4->unk_88;
    unk_A0 = var_4->unk_8C;
    unk_8C = var_4->unk_04;
    unk_90 = var_4->unk_4C;
    unk_A8 = var_4->unk_84;
    unk_20 = var_4->unk_94 * 60.0f;
    unk_AC = var_4->unk_A0;
    unk_B0 = 0;
    unk_B4 = 0;
    unk_B8 = var_4->unk_A4;
}
// match: ?vf_02C@type_3DC6D8@@UAEXHPAURwMatrixTag@@PAUtype_3D3548@@H@Z @ 0x00165D10
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3DC6D8::vf_02C(RwInt32 arg_0, RwMatrix *arg_4, type_3D3548 *arg_8, RwInt32 arg_C)
{
    RwInt32 var_10;
    RwInt32 var_C;
    type_4E5E40 *bp_8;
    type_4E5E40_08 *bp_4;

    arg_0 &= 0xFFFF;
    if (arg_0 != 0xFFFF)
    {
        bp_8 = &dword_4E5E40;
        bp_4 = bp_8->unk_08;
        if (bp_4 && (RwUInt32)arg_0 < bp_8->unk_00[1])
        {
            var_10 = bp_4[arg_0].unk_04[0];
            if (var_10 > -1)
                sub_F2750(2, var_10, arg_4, 0);
            if (arg_C)
            {
                var_C = bp_4[arg_0].unk_04[1];
                if (var_C > -1)
                    sub_F04E0(arg_4, var_C, 0);
            }
        }
    }
    else
    {
        vf_038(arg_4);
    }
    dword_4B1E98.sub_8A980(&dword_4AF008, arg_8, 0, &arg_4->pos, 0, 0);
    if (vf_040())
        sub_1614E0(arg_4, arg_8, unk_3C);
}
// match: ?vf_028@type_3DC6D8@@UAEXPAUtype_3D3548@@PAURwMatrixTag@@0@Z @ 0x00165E10
void type_3DC6D8::vf_028(type_3D3548 *arg_0, RwMatrix *arg_4, type_3D3548 *arg_8)
{
    RwInt32 var_4;

    var_4 = -1;
    if (arg_0)
        var_4 = arg_0->vf_1D4();
    type_3DC798::vf_02C(var_4, arg_4, arg_8, 0);
}
// match: ?vf_014@type_3DC6D8@@UAE_NM@Z @ 0x00165E60
// Its step: every fourth frame its model along its velocity; once its delay
// is over, its sound (one of two by the player's distance from where it
// heads); then as the model projectile.
bool type_3DC6D8::vf_014(RwReal arg_0)
{
    RwReal var_78;
    RwV3d var_74;
    type_73050 var_68;
    type_3D3548 *var_60;
    type_439A48_84 *var_5C;
    RwFrame *var_58;
    RwMatrix var_50;
    RwV3d var_10;

    if (!(dword_4B87D8 & 3))
    {
        RwV3dNormalize(&var_10, &unk_10);
        sub_140CE0(&var_50, &unk_04, &var_10);
        var_58 = RpClumpGetFrame(unk_70.get_unk_08());
        *RwFrameGetMatrix(var_58) = var_50;
        RwFrameUpdateObjects(var_58);
    }
    unk_AC = unk_AC - arg_0;
    if (unk_AC < 0.0f && !unk_B4)
    {
        var_5C = (type_439A48_84 *)unk_3C;
        var_60 = sub_1745A0(0);
        if (var_60)
        {
            var_68.unk_00 = 0;
            var_68.unk_04 = 0;
            RwV3dSub(&var_74, (RwV3d *)var_60->vf_0C4(), &unk_B8);
            var_78 = RwV3dLength((RwV3d *)&var_74);
            if (var_78 > var_5C->unk_9C)
            {
                var_68.unk_00 = 0x72A6FBE6; // not an address: a sound's key
                var_68.unk_04 = 0xBCF6B659; // not an address: a sound's key
            }
            else
            {
                var_68.unk_00 = 0x72A6FBE6; // not an address: a sound's key
                var_68.unk_04 = 0xBCF6B65A; // not an address: a sound's key
            }
            unk_B0 = dword_4B1E98.sub_8A980((type_3DF8D8_04 *)&var_68, 0, 0x10, &unk_04, 0, 0);
            unk_B4 = 1;
        }
    }
    return type_3DC798::vf_014(arg_0);
}
// match: ?vf_01C@type_3DC6D8@@UAEXM@Z @ 0x00166040
// Its fall by arg_0: after its delay (unk_A0), with its speed growing by
// unk_9C when unk_A4 is set.
void type_3DC6D8::vf_01C(RwReal arg_0)
{
    unk_A0 = unk_A0 - arg_0;
    if (unk_A4 && unk_A0 <= 0.0f)
        unk_98 = arg_0 * unk_9C + unk_98;
    unk_10.y = arg_0 * unk_98 + unk_10.y;
}
// match: ?sub_1660C0@@YAPAURpAtomic@@PAURpIntersection@@PAURpWorldSector@@PAU1@MPAX@Z @ 0x001660C0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The worlds' atomics' callback of a projectile's query arg_10 (a
// type_161470): skipping atomics collision ignores, kind-0x38 entities, the
// owner and what the owner rides, it suppresses a soldier of another side
// the line passes, then tests the entity by its mode (unk_58: a line for 2,
// vf_080 for 0, vf_07C for 1, else the atomic's triangles, sub_166950) or,
// for a sphere, builds a collision search (sub_95030's context) for mode 2
// with the query's radii. The nearest hit (under unk_00) is kept with its
// point and normal.
RpAtomic *sub_1660C0(RpIntersection *arg_0, RpWorldSector *arg_4, RpAtomic *arg_8, RwReal arg_C, void *arg_10)
{
    RwInt32 loc44;
    RwInt32 fp_40;
    RwInt32 l3C;
    RwUInt32 local_38;
    RwInt32 local_34;
    RwInt32 local_30;
    RwInt32 stk_2C;
    RwV3d var28;
    type_3D3548 *l1C;
    type_3D3548 *m_18;
    RwInt32 ebp_14;
    RwInt32 lv_10;
    type_161470 *var_C;
    RpGeometry *bp_8;
    RwInt32 bp_4;

    var_C = (type_161470 *)arg_10;
    if (sub_FB9C0(arg_8) & 0x10)
        return arg_8;
    m_18 = sub_FB960(arg_8);
    if (m_18)
    {
        local_30 = m_18->vf_1D4();
        if (local_30 == 0x38)
            return arg_8;
    }
    l1C = sub_FB960(arg_8);
    ebp_14 = 0;
    if (var_C->unk_18)
        ebp_14 = RwFrameGetParent(l1C->get_unk_340()) == var_C->unk_18->get_unk_340();
    if (l1C && l1C != var_C->unk_18 && !ebp_14 && l1C->unk_2C_5 && var_C->unk_18
        && (l1C->unk_2C & 7) != (var_C->unk_18->unk_2C & 7))
        ((type_3DAFC8 *)l1C)->vf_250();
    if (arg_C > var_C->unk_00)
        return arg_8;
    switch (arg_0->type)
    {
    case rpINTERSECTLINE:
        var28 = arg_0->t.line.end;
        break;
    case rpINTERSECTPOINT:
        var28 = arg_0->t.point;
        break;
    case rpINTERSECTSPHERE:
        var28 = arg_0->t.sphere.center;
        break;
    }
    if (l1C == var_C->unk_18 || ebp_14)
        return arg_8;
    if (!RWS::RpAtomicCollisionProperties::GetIsSolid(*arg_8))
        return arg_8;
    lv_10 = 0;
    stk_2C = -1;
    bp_4 = 0;
    bp_8 = RpAtomicGetGeometry(arg_8);
    if (l1C && arg_0->type == rpINTERSECTLINE)
    {
        if (l1C->unk_28_2 || l1C->vf_00C() && l1C->vf_1E4())
        {
            local_38 = var_C->unk_14 & 0x3FFFFF0;
            if (!(local_38 & l1C->unk_30))
                return arg_8;
        }
        else
        {
            return arg_8;
        }
        local_34 = l1C->unk_28_0;
        l1C->unk_54 = var_C->unk_48;
        if (l1C->unk_58 == 2)
        {
            l3C = l1C->vf_084(3, arg_0, &arg_C, &var_C->unk_38);
            if (l3C && arg_C < var_C->unk_00 && arg_C >= 0.0f)
            {
                bp_4 = 1;
                lv_10 = 1;
            }
        }
        else if (l1C->unk_58 == 0 && !local_34)
        {
            fp_40 = l1C->vf_080(1, arg_0, &arg_C, 1.0f);
            if (fp_40 && arg_C < var_C->unk_00 && arg_C >= 0.0f)
            {
                bp_4 = 1;
                lv_10 = 1;
            }
        }
        else if (l1C->unk_58 == 1 && !local_34)
        {
            loc44 = 0;
            if (var_C->unk_18 && (l1C->unk_2C & 7) == (var_C->unk_18->unk_2C & 7))
                loc44 = 1;
            stk_2C = l1C->vf_07C(1, arg_0, &arg_C, loc44);
            if (stk_2C != -1 && arg_C < var_C->unk_00 && arg_C >= 0.0f)
            {
                bp_4 = 1;
                lv_10 = 1;
            }
        }
        else if (bp_8)
        {
            RpAtomicForAllIntersections(arg_8, arg_0, sub_166950, arg_10);
        }
    }
    else if (bp_8)
    {
        if (l1C->unk_58 == 2 && var_C->unk_08)
        {
            RwInt32 var_128;
            RwV3d frm_124;
            type_93DF0 fp_118;
            type_D1990 stk_60;
            RwInt32 stk_58;
            RwV3d lv_54;
            RwReal q48;

            fp_118.unk_4C = var_C->unk_50;
            fp_118.unk_74 = 0x180000; // not an address: material flags
            frm_124.x = 0;
            frm_124.y = 0;
            frm_124.z = 0;
            fp_118.unk_6C = &frm_124;
            fp_118.unk_24 = arg_0->t.sphere.radius * arg_0->t.sphere.radius;
            fp_118.unk_20 = 0;
            fp_118.unk_18 = 0;
            fp_118.unk_04 = 0;
            fp_118.unk_08 = 0;
            fp_118.unk_0C = 0;
            fp_118.unk_60 = 0;
            fp_118.unk_64 = 0;
            fp_118.unk_68 = 0;
            fp_118.unk_B0 = var_C->unk_58;
            fp_118.unk_7C = 0;
            fp_118.unk_14 = (RwFrame *)var_C->unk_08;
            q48 = 0;
            fp_118.unk_80 = &q48;
            fp_118.unk_90 = 0;
            fp_118.unk_78 = -1;
            fp_118.unk_38[0] = 1.0f / var_C->unk_50;
            fp_118.unk_38[1] = 1.0f / var_C->unk_54;
            fp_118.unk_38[2] = 1.0f / var_C->unk_50;
            fp_118.unk_48 = var_C->unk_54 * 0.5f;
            var_128 = 0;
            fp_118.unk_50 = &var_128;
            fp_118.unk_10 = arg_8;
            fp_118.unk_58 = 0;
            fp_118.unk_54 = 0;
            fp_118.unk_70 = sub_8F940();
            fp_118.unk_00 = 0;
            fp_118.unk_84 = 0;
            fp_118.unk_88 = 0;
            fp_118.unk_8C = 0;
            fp_118.unk_44 = 0;
            stk_60.unk_00 = &arg_0->t.sphere;
            stk_60.unk_04 = (type_93700 *)&fp_118;
            stk_58 = l1C->vf_084(4, (RpIntersection *)&stk_60, &arg_C, &lv_54);
            if (stk_58 && arg_C < var_C->unk_00 && arg_C >= 0.0f)
            {
                bp_4 = 0;
                lv_10 = 0;
                var_C->unk_04 = fp_118.unk_94;
                var_C->unk_10 = arg_8;
                var_C->unk_00 = arg_C;
                var_C->unk_0C = var_C->unk_10;
                var_C->unk_44 = stk_2C;
                var_C->unk_38 = fp_118.unk_98_v;
                var_C->unk_2C = fp_118.unk_98_v;
                var_C->unk_20 = fp_118.unk_A4_v;
            }
        }
        else
        {
            RpAtomicForAllIntersections(arg_8, arg_0, sub_166950, arg_10);
            if (arg_C < var_C->unk_00 && arg_C >= 0.0f)
            {
                bp_4 = 1;
                lv_10 = 1;
            }
        }
    }
    else if (arg_C < var_C->unk_00 && arg_C >= 0.0f)
    {
        bp_4 = 1;
        if (arg_0->type == rpINTERSECTLINE)
            lv_10 = 1;
    }
    if (bp_4)
    {
        var_C->unk_10 = arg_8;
        var_C->unk_00 = arg_C;
        var_C->unk_0C = var_C->unk_10;
        var_C->unk_20 = var28;
        var_C->unk_44 = stk_2C;
    }
    if (lv_10)
    {
        RwV3dSub(&var_C->unk_2C, &arg_0->t.line.end, &arg_0->t.line.start);
        RwV3dScale(&var_C->unk_20, &var_C->unk_2C, arg_C);
        RwV3dAdd(&var_C->unk_20, &var_C->unk_20, &arg_0->t.line.start);
        if (l1C->unk_58 == 2)
        {
            var_C->unk_2C = var_C->unk_38;
        }
        else
        {
            RwV3dNormalize(&var_C->unk_2C, &var_C->unk_2C);
            RwV3dNegate(&var_C->unk_2C, &var_C->unk_2C);
        }
    }
    return arg_8;
}
// match: ?sub_166950@@YAPAURpCollisionTriangle@@PAURpIntersection@@PAU1@MPAX@Z @ 0x00166950
RpCollisionTriangle *sub_166950(RpIntersection *arg_0, RpCollisionTriangle *arg_4, RwReal arg_8,
                                void *arg_C)
{
    type_161470 *var_4;

    var_4 = (type_161470 *)arg_C;
    if (arg_8 < var_4->unk_00)
    {
        var_4->unk_00 = arg_8;
        var_4->unk_0C = var_4->unk_10;
    }
    return arg_4;
}
