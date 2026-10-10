// The main render (game/render.h): the frame, the passes over the level's
// worlds, their lighting, the character shadows, the motion blur, and the
// fog and far clip fades. The original file name is not in the image, so
// it is named for its start address.

#include <math.h>
#include <string.h>
#include <stddef.h>
#include <xtl.h>

#include "game/render.h"
#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "rw/bamatrix.h"
#include "rw/bavector.h"
#include "rw/baframe.h"
#include "rw/baengine.h"
#include "rw/badevice.h"
#include "rw/batextur.h"
#include "rw/rpatomic.h"
#include "rw/rplight.h"
#include "rw/rpworld.h"
#include "rw/rpcollis.h"
#include "rw/rpmaterial.h"
#include "rw/baim3d.h"
#include "game/worldrender.h"
#include "game/functions.h"
#include "game/gameloop.h"
#include "game/data.h"
#include "game/particles.h"
#include "game/fade.h"
#include "game/decals.h"
#include "game/clones.h"
#include "types/type_4E1B70.h"
#include "types/type_4B8EF0.h"
#include "types/type_3DAFC8.h"

#ifdef CODFH_DRAW_TRIGGERS
// port/src/debug/trigdraw.cpp: the trigger volumes, drawn after the world
void TrigDrawAll(RwCamera *pCamera);
#endif
#include "types/type_3D3548.h"
#include "types/type_3D96F0.h"
#include "types/type_4E5D30.h"
#include "types/type_10F710.h"
#include "types/RenderTrigger.h"
#include "types/animkey.h"
#include "types/type_92430.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x00429BAC
RwInt32 dword_429BAC[4] = { 2, 1, 3, 0 };
// 0x00429BBC
RwReal flt_429BBC = 70.0f;
// 0x00429BC0
RwInt32 dword_429BC0 = 65536;
// 0x00429BC4
RwInt32 dword_429BC4 = 2;
// 0x00429BC8
RwInt32 dword_429BC8 = 196610;
// 0x00429BCC
RwInt32 dword_429BCC = 1;
// 0x00429BD0
RwReal flt_429BD0 = 3000.0f;
// 0x00429BD4
RwReal flt_429BD4 = 5.0f;
// 0x00429BD8
RwReal flt_429BD8 = 1.0f;
// 0x00429BDC
const RwChar *off_429BDC[10] = { "tankshadow", "charactershadow", "", "", "", "", "", "", "", "" };
// 0x004CF434
RwInt32 dword_4CF434;
// 0x004CF438
RwInt32 dword_4CF438;
// 0x004CF43C
RwInt32 dword_4CF43C;
// 0x004CF440
RwInt32 dword_4CF440;
// 0x004CF444
RwInt32 dword_4CF444;
// 0x004CF450
RwInt32 dword_4CF450;
// 0x004CF454
RwInt32 dword_4CF454;
// 0x004CF458
RwReal flt_4CF458;
// 0x004CF45C
RwInt32 dword_4CF45C;
// 0x004CF460
RwInt32 dword_4CF460;
// 0x004CF464
RwInt32 dword_4CF464;
// 0x004CF468
RwInt32 dword_4CF468;
// 0x004CF470
RwReal dword_4CF470;
// 0x004CF474
RwInt32 dword_4CF474;
// 0x004CF478
RwInt32 dword_4CF478;
// 0x004CF47C
RwInt32 dword_4CF47C;
// 0x004CF480
RwInt32 dword_4CF480;
// 0x004CF484
RwInt32 dword_4CF484;
// 0x004CF48C
RwInt32 dword_4CF48C;
// 0x004CF490
RwInt32 dword_4CF490;
// 0x004CF498
RwRGBAReal dword_4CF498[4];
// 0x004CF4D8
RwReal dword_4CF4D8;
// 0x004CF4DC
RwInt32 dword_4CF4DC;
// 0x004CF4E0
RpLight *result[4];
// 0x004CF4F0
RwInt32 dword_4CF4F0;
// 0x004CF4F8
RwReal dword_4CF4F8;
// 0x004CF4FC
RwInt32 dword_4CF4FC;
// 0x004CF500
RwInt32 dword_4CF500;
// 0x004CF504
RwInt32 dword_4CF504;
// 0x004CF50C
RwInt32 dword_4CF50C;
// 0x004CF510
RwInt32 dword_4CF510;
// 0x004CF514
RwReal dword_4CF514;
// 0x004CF518
RwInt32 dword_4CF518;
// 0x004CF51C
RwInt32 dword_4CF51C;
// 0x004CF540
RwInt32 dword_4CF540;
// 0x004CF548
RwIm2DVertex dword_4CF548[4];
// 0x004CF5B8
RwInt32 dword_4CF5B8;
// 0x004CF5BC
RwUInt32 dword_4CF5BC;
// 0x004CF5C0
RwV3d dword_4CF5C0;
// 0x004CF5D0
type_4CF5D0 dword_4CF5D0[10];
// 0x004CF650
RwMatrix dword_4CF650[4];
// 0x004CF750
RwInt32 dword_4CF750;
// 0x004CF754
RwInt32 dword_4CF754;
// 0x004CF758
RwReal dword_4CF758;
// 0x004CF75C
RwInt32 dword_4CF75C;
// 0x004CF760
RwInt32 dword_4CF760;
// 0x004CF76C
RwInt32 dword_4CF76C;
// 0x004CF770
RwReal farClip;
// 0x004CF774
RwReal dword_4CF774;
// 0x004CF778
RwInt32 dword_4CF778;
// 0x004CF780
RwInt32 dword_4CF780;
// 0x004CF784
RwInt32 dword_4CF784;
// 0x004CF788
RwInt32 dword_4CF788;
// 0x004CF78C
RwReal dword_4CF78C;
// 0x004CF790
RwRGBA stru_4CF790;
// 0x004CF794
RwReal dword_4CF794;
// 0x004CF798
RwInt32 dword_4CF798;
// 0x004CF79C
RwInt32 dword_4CF79C;
// 0x004CF7A0
RwInt32 dword_4CF7A0;
// 0x004CF7A4
RwInt32 dword_4CF7A4;
// 0x004CF7A8
RpLight *light;
// 0x004CF7AC
RwRGBAReal xmmword_4CF7AC;
// 0x004CF7BC
RwInt32 dword_4CF7BC;
// 0x004CF7C4
RwInt32 dword_4CF7C4;
// 0x004CF7CC
RwReal flt_4CF7CC;
// 0x004CF7D0
RwUInt8 byte_4CF7D0;
// (Defined after the data: VC7.1 emits a unit's data definitions in reverse order, and
// the image has these constants before the data's texts.)
// 0x003DA7E8
extern const RwReal flt_3DA7E8 = 16.666666f;
#ifndef CODFH_SP // single player writes the literal: its folded 114.59275f (__real@42e52f7d) follows 16.666666f (SP 0x2E6674, read at SP 0xDAF35)
// 0x003DA7EC
// (a named constant: the image has it among the constants, before the table's texts)
extern const RwReal flt_3DA7EC = 57.296375f;
#endif
// End of its data definitions.


// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3DA7E8@@3MB @ 0x003DA7E8
// match: ?flt_3DA7EC@@3MB @ 0x003DA7EC
// match: ??_C@_0BA@DCCGBOJF@charactershadow?$AA@ @ 0x003DA7F0
// match: ??_C@_0L@PHECPMPD@tankshadow?$AA@ @ 0x003DA800
// match: ?dword_429BAC@@3PAHA @ 0x00429BAC
// match: ?flt_429BBC@@3MA @ 0x00429BBC
// match: ?dword_429BC0@@3HA @ 0x00429BC0
// match: ?dword_429BC4@@3HA @ 0x00429BC4
// match: ?dword_429BC8@@3HA @ 0x00429BC8
// match: ?dword_429BCC@@3HA @ 0x00429BCC
// match: ?flt_429BD0@@3MA @ 0x00429BD0
// match: ?flt_429BD4@@3MA @ 0x00429BD4
// match: ?flt_429BD8@@3MA @ 0x00429BD8
// match: ?off_429BDC@@3PAPBDA @ 0x00429BDC

// match: ?sub_125490@@YAPAURwTexture@@PAU1@PAX@Z @ 0x00125490

// Leaves the texture arg_0 as it is (the filtering it once set is gone).
RwTexture *sub_125490(RwTexture *arg_0, void *arg_4)
{
    RwInt32 *var_4;

    var_4 = (RwInt32 *)arg_4;
    return arg_0;
}

// match: ?sub_1254B0@@YAPAURwTexDictionary@@PAU1@PAX@Z @ 0x001254B0
// sp-match: ?sub_1254B0@@YAPAURwTexDictionary@@PAU1@PAX@Z @ 0x000DAE60
RwTexDictionary *sub_1254B0(RwTexDictionary *arg_0, void *arg_4)
{
    RwTexDictionaryForAllTextures(arg_0, sub_125490, arg_4);
    return arg_0;
}

#ifdef CODFH_SP
// Single player only (SP 0xDAE80): whether the level is not level 2; the
// level draw tests it before the second level world (SP 0xDB058), where
// multiplayer calls a function that always returns 1 (sub_31DB0).
// sp-match: ?sp_sub_DAE80@@YAHXZ @ 0x000DAE80
RwInt32 sp_sub_DAE80()
{
    return sub_19B050() != 2;
}
#endif

// match: ?sub_1254D0@@YAXPAURwCamera@@@Z @ 0x001254D0
// sp-match: ?sub_1254D0@@YAXPAURwCamera@@@Z @ 0x000DAF10
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Draws the level for the camera arg_0: the worlds (or a clear screen), the
// level sections' worlds and the clones in two passes, and the world render
// pass's atomics; the view's field of view first (the textures' filtering
// once followed it).
void sub_1254D0(RwCamera *arg_0)
{
    type_3D9718 *var_3C;
    RwInt32 w38;
    RwInt32 ebp_34;
    type_3D9718 *var_30;
    type_3D9718 *v2C;
    type_3D9718 *lcl_28;
    RwInt32 frm_24;
    RwRGBA var_20;
    RwInt32 l1C;
    RwReal m_18;
    type_3D9718 *ebp_14;
    RwInt32 lv_10;
    RwInt32 var_C;
    RpWorld *bp_8;
    type_3D3548 *bp_4;

    if (!arg_0)
    {
        return;
    }
    bp_4 = sub_1745A0(0);
#ifdef CODFH_SP
    // shape: single player's field of view is a block local (it shares the
    // dead camera argument's slot, SP 0xDAF46).
    if (bp_4)
    {
        RwInt32 fov = (RwInt32)((RwReal)atan(((type_10F710 *)bp_4)->get_unk_534()) * 2.0f
                                    * 57.296375f);
        if (fov != dword_4CF7C4)
        {
            dword_4CF7C4 = fov;
            RwTexDictionaryForAllTexDictionaries(sub_1254B0, &fov);
        }
    }
#else
    if (bp_4)
    {
        l1C = (RwInt32)(m_18 = (RwReal)atan(((type_10F710 *)bp_4)->get_unk_534()) * 2.0f
                                    * flt_3DA7EC);
        if (l1C != dword_4CF7C4)
        {
            dword_4CF7C4 = l1C;
            RwTexDictionaryForAllTexDictionaries(sub_1254B0, &l1C);
        }
    }
#endif
    if (world && !dword_4CF440)
    {
        sub_16D7F0(10);
        sub_127530(arg_0, world);
        sub_1290F0(arg_0, world, 0);
        sub_127700(arg_0, world);
        sub_16D850(10);
    }
    else
    {
#ifdef CODFH_SP
        // shape: a block local too (the same dead argument slot, SP 0xDAFB2).
        RwRGBA var_20;

#endif
        var_20.red = 0;
        var_20.green = 0;
        var_20.blue = 0;
        var_20.alpha = 0;
        RwCameraClear(arg_0, &var_20, 3);
    }
    if (dword_4E5C88 && !dword_4CF440)
    {
        sub_16D7F0(10);
        RpWorldForAllMaterials(dword_4E5C88, sub_125A10, 0);
        sub_127530(arg_0, dword_4E5C88);
        RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void *)0);
        sub_1290F0(arg_0, dword_4E5C88, 0);
        RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void *)1);
        sub_127700(arg_0, dword_4E5C88);
        sub_16D850(10);
    }
#ifdef CODFH_SP
    // Single player skips the second level world in level 2 (SP 0xDB058).
    if (dword_4E5C84 && !dword_4CF440 && (frm_24 = sp_sub_DAE80()) != 0)
#else
    if (dword_4E5C84 && !dword_4CF440 && (frm_24 = sub_31DB0()) != 0)
#endif
    {
        sub_16D7F0(10);
        sub_127530(arg_0, dword_4E5C84);
        RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void *)0);
        sub_1290F0(arg_0, dword_4E5C84, 0);
        RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void *)1);
        sub_127700(arg_0, dword_4E5C84);
        sub_16D850(10);
    }
    sub_16D7F0(11);
    var_C = 0;
    if (!dword_4CF434)
    {
        for (lv_10 = 0; lv_10 < 4; lv_10++)
        {
            if (dword_4E5D30[lv_10].get_unk_00())
            {
                bp_8 = dword_4E5D30[lv_10].unk_20;
                if (bp_8)
                {
                    lcl_28 = sub_FC4E0(bp_8);
                    sub_129140(arg_0, bp_8, lcl_28->get_unk_1C(), 0, 0);
                }
            }
        }
    }
    sub_16D850(11);
    sub_1259C0(arg_0, 0);
    sub_16D7F0(11);
    if (!dword_4CF43C)
    {
        for (lv_10 = 0; lv_10 < 4; lv_10++)
        {
            if (dword_4E5D30[lv_10].get_unk_00())
            {
                bp_8 = dword_4E5D30[lv_10].unk_2C;
                if (bp_8)
                {
                    RpWorldForAllMaterials(bp_8, sub_125A10, 0);
                    v2C = sub_FC4E0(bp_8);
                    sub_129140(arg_0, bp_8, v2C->get_unk_1C(), 1, 1);
                }
            }
        }
    }
    if (!dword_4CF438)
    {
        var_C = 0;
        for (lv_10 = 0; lv_10 < 4; lv_10++)
        {
            if (dword_4E5D30[lv_10].get_unk_00())
            {
                bp_8 = dword_4E5D30[lv_10].unk_24;
                if (bp_8)
                {
                    if (!var_C)
                    {
                        var_C = 1;
                    }
                    var_30 = sub_FC4E0(bp_8);
                    sub_129140(arg_0, bp_8, var_30->get_unk_1C(), 1, 2);
                }
            }
        }
    }
    sub_16D850(11);
    sub_16D7F0(12);
    if (!dword_4CF444)
    {
        for (ebp_34 = 0; ebp_34 < 4; ebp_34++)
        {
            w38 = dword_429BAC[ebp_34];
            if (dword_4E5D30[w38].get_unk_00())
            {
                bp_8 = dword_4E5D30[w38].unk_20;
                if (bp_8)
                {
                    var_3C = sub_FC4E0(bp_8);
                    sub_122DD0(arg_0, (RwInt32)bp_8, var_3C->get_unk_1C());
                }
            }
        }
    }
    if (unk_4E5CD8.unk_00)
    {
        bp_8 = (RpWorld *)unk_4E5CD8.unk_20;
        ebp_14 = sub_FC4E0(bp_8);
        sub_122DD0(arg_0, (RwInt32)bp_8, ebp_14->get_unk_1C());
    }
    sub_16D850(12);
    sub_1259C0(arg_0, 1);
}

// match: ?sub_1259C0@@YAXPAURwCamera@@H@Z @ 0x001259C0
// sp-match: ?sub_1259C0@@YAXPAURwCamera@@H@Z @ 0x000DAE90
// Draws the clones of the pass arg_4 in the effects world's pass.
void sub_1259C0(RwCamera *arg_0, RwInt32 arg_4)
{
    sub_16D7F0(0x22);
    sub_126A30(arg_0, dword_4E5C78, 0, 0.0f, 1);
    sub_1234D0(arg_4);
    sub_126D00(arg_0, dword_4E5C78);
    sub_16D850(0x22);
}

// match: ?sub_125A10@@YAPAURpMaterial@@PAU1@PAX@Z @ 0x00125A10
// sp-match: ?sub_125A10@@YAPAURpMaterial@@PAU1@PAX@Z @ 0x000DAEE0
// Runs the UV animation of the material arg_0 by a frame (1/60 s).
RpMaterial *sub_125A10(RpMaterial *arg_0, void *arg_4)
{
    if (RpMatFXMaterialGetEffects(arg_0) == 5)
    {
        RpMaterialUVAnimAddAnimTime(arg_0, 0.016666668f);
        RpMaterialUVAnimApplyUpdate(arg_0);
    }
    return arg_0;
}

// match: ?sub_125A50@@YAXXZ @ 0x00125A50
// sp-match: ?sub_125A50@@YAXXZ @ 0x000DC6B0
// Sets the render settings to their defaults.
void sub_125A50()
{
    RwInt32 var_4;

    var_4 = 0;
    dword_4CF798 = dword_4CF76C = dword_4CF480 = dword_4CF750 = 0;
    dword_4CF7A0 = 0;
    dword_4CF778 = 2;
    dword_4CF4DC = 5;
    dword_4CF780 = 6;
    dword_4CF460 = 1;
    dword_4CF784 = 1;
    dword_4CF45C = 1;
    dword_4CF450 = 0;
    dword_4CF474 = 0;
    dword_4CF454 = 0;
    dword_4CF4F0 = 0;
    stru_4CF790.red = 0;
    stru_4CF790.green = 0;
    stru_4CF790.blue = 0;
    stru_4CF790.alpha = 0;
    dword_4CF5BC = 2;
#ifdef CODFH_SP // shape: both set to 30.0f in one assignment (SP 0xDC74F/0xDC759: two immediate stores, no reload)
    *(RwReal *)&dword_4CF468 = *(RwReal *)&dword_4CF540 = 30.0f;
#else
    *(RwReal *)&dword_4CF540 = 30.0f;
    dword_4CF468 = dword_4CF540;
#endif
    flt_4CF458 = farClip = 20000.0f;
    dword_4CF490 = 1;
    dword_4CF518 = 1;
    dword_4CF5B8 = 0;
    dword_4CF760 = 1;
    dword_4CF4FC = 0;
    dword_4CF50C = 1;
    dword_4CF754 = 1;
    dword_4CF504 = 2;
    dword_4CF7A4 = 0;
    dword_4CF7BC = 0;
    light = 0;
    xmmword_4CF7AC.alpha = 1.0f;
    xmmword_4CF7AC.blue = 0.0f;
    xmmword_4CF7AC.green = 0.0f;
    xmmword_4CF7AC.blue = 0.0f;
    for (var_4 = 0; var_4 < 4; var_4++)
    {
        result[var_4] = 0;
        dword_4CF498[var_4].alpha = 0.0f;
        dword_4CF498[var_4].blue = 0.0f;
        dword_4CF498[var_4].green = 0.0f;
        dword_4CF498[var_4].red = 0.0f;
        RwMatrixSetIdentityMacro(&dword_4CF650[var_4]);
    }
    dword_4CF48C = 0;
    dword_4CF774 = 0.0f;
    dword_4CF514 = 0.0f;
    dword_4CF758 = 0.0f;
    dword_4CF4D8 = 0.0f;
    dword_4CF794 = 0.0f;
    dword_4CF470 = 0.0f;
    dword_4CF4F8 = 0.0f;
    dword_4CF788 = 0;
    dword_4CF7C4 = 0;
    sub_1288F0((RwCamera *)dword_4E5C74);
    dword_4CF79C = 1;
    for (var_4 = 0; var_4 < 10; var_4++)
    {
        dword_4CF5D0[var_4].unk_00 = 0;
        dword_4CF5D0[var_4].unk_04 = 0;
        dword_4CF5D0[var_4].unk_08 = 0;
    }
}

// match: ?sub_125E00@@YAXXZ @ 0x00125E00
// sp-match: ?sub_125E00@@YAXXZ @ 0x000DD6B0
// Clears the screen and frees the shadows' buffers, the motion blur off.
void sub_125E00()
{
    RwCamera *var_4;

    var_4 = (RwCamera *)dword_4E5C74;
    sub_125E60(var_4);
    sub_128770();
    dword_4CF48C = 0;
    dword_4CF774 = 0.0f;
    dword_4CF78C = 0.0f;
}

// match: ?sub_125E40@@YAXXZ @ 0x00125E40
// sp-match: ?sub_125E40@@YAXXZ @ 0x000DCA50
void sub_125E40()
{
    RwCamera *var_4;

    var_4 = (RwCamera *)dword_4E5C74;
    sub_128770();
}

// match: ?sub_125E60@@YAXPAURwCamera@@@Z @ 0x00125E60
// sp-match: ?sub_125E60@@YAXPAURwCamera@@@Z @ 0x000DCA60
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Clears both buffers of the camera arg_0 to black.
void sub_125E60(RwCamera *arg_0)
{
    RwInt32 var_8;
    RwRGBA l4;

    l4.red = 0;
    l4.green = 0;
    l4.blue = 0;
    l4.alpha = 0;
    for (var_8 = 0; var_8 < 2; var_8++)
    {
        RwCameraClear(arg_0, &l4, 3);
        if (RwCameraBeginUpdate(arg_0))
        {
            RwCameraEndUpdate(arg_0);
        }
        sub_126750(arg_0);
    }
}

// match: ?sub_125ED0@@YAXPAURwCamera@@H@Z @ 0x00125ED0
// sp-match: ?sub_125ED0@@YAXPAURwCamera@@H@Z @ 0x000DCAC0
// Shows both buffers of the camera arg_0 as they are.
void sub_125ED0(RwCamera *arg_0, RwInt32 arg_4)
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 2; var_4++)
    {
        if (RwCameraBeginUpdate(arg_0))
        {
            RwCameraEndUpdate(arg_0);
        }
        sub_126750(arg_0);
    }
}

// match: ?sub_125F20@@YAXH@Z @ 0x00125F20
// sp-match: ?sub_125F20@@YAXH@Z @ 0x000DCB00
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Draws a frame: the level, the effects, RenderWare Studio's entities, the
// player's view (its own field of view, lit apart), the fades, the motion
// blur and the HUD (not while arg_0 is set), with the loading thread held.
void sub_125F20(RwInt32 arg_0)
{
    type_4C19C0 *var_24;
    type_4E1B70 *var_20;
    type_3DC9B0 *l1C;
    RwReal m_18;
    type_10F710 *ebp_14;
    RwMatrix *lv_10;
    RpWorld *var_C;
    RwCamera *bp_8;
    RwFrame *bp_4;

    bp_8 = (RwCamera *)dword_4E5C74;
    if (!bp_8)
    {
        return;
    }
    D3DDevice_SetRenderState(D3DRS_ROPZCMPALWAYSREAD, TRUE);
    RwCameraGetFrame(bp_8)->modelling.flags = 3;
    RwMatrixOrthoNormalize(&RwCameraGetFrame(bp_8)->modelling,
                           &RwCameraGetFrame(bp_8)->modelling);
    if (flt_4CF7CC != 0.0f)
    {
        sub_128CD0(flt_4CF7CC, 30.0f);
        flt_4CF7CC = 0.0f;
    }
    sub_16D7F0(1);
    dword_4CF7A0++;
    if (!bp_8)
    {
        return;
    }
    sub_16D7F0(9);
#ifndef CODFH_SP
    sub_19A750((RwInt32)bp_8);
#endif
    sub_16D850(9);
    SuspendThread((HANDLE)dword_44BAD4);
    sub_1254D0(bp_8);
    sub_19D080(bp_8);
    sub_16D7F0(0x1F);
    sub_17D3A0(bp_8);
    sub_16D850(0x1F);
    sub_1277D0(bp_8, world, 1);
    dword_4D51C0.sub_15FB30(bp_8);
    sub_16D7F0(0x1E);
    sub_1287F0();
    sub_16D850(0x1E);
#ifdef CODFH_DRAW_TRIGGERS
    TrigDrawAll(bp_8);
#endif
    sub_16D7F0(0xF);
    sub_F34C0(1, 0);
    sub_16D850(0xF);
    sub_16D7F0(0x20);
    sub_F03F0();
    sub_16D850(0x20);
    sub_127910(bp_8, world);
    dword_4CF7A4 = 0;
    sub_16D7F0(0xD);
    sub_15F390(bp_8);
    sub_16D850(0xD);
    sub_16D7F0(0xE);
    RWS::MainLoop::Render::Poll();
    sub_16D850(0xE);
    sub_16D7F0(0x1C);
    sub_16D850(0x1C);
    ebp_14 = (type_10F710 *)sub_1745A0(dword_429EB0);
    if (ebp_14 && ebp_14->unk_1A3C.get_unk_08())
    {
        var_C = ebp_14->sub_111000();
        sub_16D7F0(0x10);
        RwCameraClear(bp_8, &stru_4CF790, 2);
        if (ebp_14->unk_1B28)
        {
            l1C = (type_3DC9B0 *)ebp_14->unk_210C.sub_D4910();
            if (l1C)
            {
                var_20 = sub_166990(l1C->unk_3B0);
                m_18 = var_20->unk_10;
            }
            else
            {
                m_18 = ebp_14->unk_534;
            }
        }
        else
        {
            var_24 = ebp_14->unk_1A48[ebp_14->unk_1AE4]->get_unk_448();
            m_18 = var_24->unk_324;
        }
        if (!arg_0)
        {
            RWS::CameraHelper::SetFieldOfView(m_18, bp_8);
        }
        if (ebp_14->unk_1B3C && sub_126E30(bp_8, var_C, 0, 1.0f))
        {
            ebp_14->sub_110A60((RwInt32)bp_8);
            sub_F34C0(0, 0x40);
            sub_127360(bp_8, var_C);
        }
        sub_16D850(0x10);
        if (!arg_0)
        {
            RWS::CameraHelper::SetFieldOfView(ebp_14->unk_534, bp_8);
        }
    }
    sub_128B00(bp_8);
    sub_128D30();
    sub_128DB0();
    sub_187150(dword_4E5CBC);
    dword_4B8EF0.sub_E9B50();
#ifdef CODFH_SP
    // single player sets the 2D camera again when not paused for a capture
    // (SP 0xDCDA0) and reads the pad without the input test (SP 0xDCDBC).
    if (!arg_0)
    {
        sub_187150(dword_4E5CBC);
    }
    if (0.0f != unk_4B9308.sub_EE9A0(1, 0x11))
#else
    if (0.0f != unk_4B9308.sub_EE8F0(1, 0x11))
#endif
    {
        dword_429BCC = !dword_429BCC;
    }
    dword_429BCC = 0;
    if (dword_429BCC && !arg_0)
    {
        dword_4CF76C++;
        dword_4CF750 = RWS::Time::GetTime();
        if (dword_4CF750 - dword_4CF480 >= 1000)
        {
            dword_4CF798 = dword_4CF76C;
            dword_4CF76C = 0;
            dword_4CF480 = dword_4CF750;
        }
    }
    sub_124DC0((RwReal)(RwUInt32)RWS::Time::GetTime());
    sub_125060(bp_8);
    if ((dword_4B86F8 >> 4) & 1)
    {
        sub_187150(dword_4E5CBC);
    }
#ifndef CODFH_SP // single player has no second camera update (SP 0xDCE0E)
    RwCameraBeginUpdate(bp_8);
    bp_4 = RwCameraGetFrame(bp_8);
    lv_10 = &bp_4->modelling;
    lv_10->flags = 3;
    RwFrameUpdateObjects(bp_4);
    sub_1A2D00();
    RwCameraEndUpdate(bp_8);
#endif
    if (byte_4CF7D0)
    {
        sub_D8E80();
    }
    if (!arg_0)
    {
        unk_4E73A8.sub_184100(bp_8);
    }
    sub_16D850(1);
    sub_16D7F0(2);
    ResumeThread((HANDLE)dword_44BAD4);
    sub_126750(bp_8);
    sub_16D850(2);
}

// match: ?sub_126750@@YAXPAURwCamera@@@Z @ 0x00126750
// sp-match: ?sub_126750@@YAXPAURwCamera@@@Z @ 0x000DB250
void sub_126750(RwCamera *arg_0)
{
    if (arg_0)
    {
        RwCameraShowRaster(arg_0, 0, 1);
    }
}

// match: ?sub_126770@@YAXXZ @ 0x00126770
// sp-match: ?sub_126770@@YAXXZ @ 0x000DD6F0
// Applies the prelit setting (dword_4CF50C) to the live sections' worlds.
void sub_126770()
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 4; var_4++)
    {
        if (dword_4E5D30[var_4].get_unk_00())
        {
            sub_1267D0(&dword_4E5D30[var_4], dword_4CF50C);
        }
    }
}

// match: ?sub_1267D0@@YAXPAUtype_4E5D30@@H@Z @ 0x001267D0
// sp-match: ?sub_1267D0@@YAXPAUtype_4E5D30@@H@Z @ 0x000DCE70
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_1267D0(type_4E5D30 *arg_0, RwInt32 arg_4)
{
    RpWorld *var_18;
    RwUInt32 var_14;
    RpWorld *lv_10;
    RwUInt32 var_C;
    RpWorld *bp_8;
    RwUInt32 bp_4;

    bp_4 = arg_0->unk_34;
    bp_8 = arg_0->unk_20;
    sub_126850(bp_8, bp_4, arg_4);
    var_C = arg_0->unk_38;
    lv_10 = arg_0->unk_24;
    sub_126850(lv_10, var_C, arg_4);
    var_14 = arg_0->unk_3C;
    var_18 = arg_0->unk_28;
    sub_126850(var_18, var_14, arg_4);
}

// match: ?sub_126850@@YAXPAURpWorld@@IH@Z @ 0x00126850
// sp-match: ?sub_126850@@YAXPAURpWorld@@IH@Z @ 0x000DB270
// Turns the world arg_0's prelit flag on or off (arg_8), where its flags
// arg_4 allow it.
void sub_126850(RpWorld *arg_0, RwUInt32 arg_4, RwInt32 arg_8)
{
    RwUInt32 var_4;

    if (arg_0 && (arg_4 & rpWORLDPRELIT))
    {
        var_4 = arg_0->flags;
        if (arg_8)
        {
            if (var_4 & rpWORLDPRELIT)
            {
                return;
            }
            var_4 |= rpWORLDPRELIT;
        }
        else
        {
            if (!(var_4 & rpWORLDPRELIT))
            {
                return;
            }
            var_4 &= ~rpWORLDPRELIT;
        }
        RpWorldLock(arg_0);
        arg_0->flags = var_4;
        RpWorldUnlock(arg_0);
        RwResourcesEmptyArena();
    }
}

// match: ?sub_1268D0@@YAXXZ @ 0x001268D0
// sp-match: ?sub_1268D0@@YAXXZ @ 0x000DD720
// Applies the lit setting (dword_4CF754) to the live sections' worlds.
void sub_1268D0()
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 4; var_4++)
    {
        if (dword_4E5D30[var_4].get_unk_00())
        {
            sub_126930(&dword_4E5D30[var_4], dword_4CF754);
        }
    }
}

// match: ?sub_126930@@YAXPAUtype_4E5D30@@H@Z @ 0x00126930
// sp-match: ?sub_126930@@YAXPAUtype_4E5D30@@H@Z @ 0x000DCEB0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_126930(type_4E5D30 *arg_0, RwInt32 arg_4)
{
    RpWorld *var_18;
    RwUInt32 var_14;
    RpWorld *lv_10;
    RwUInt32 var_C;
    RpWorld *bp_8;
    RwUInt32 bp_4;

    bp_4 = arg_0->unk_34;
    bp_8 = arg_0->unk_20;
    sub_1269B0(bp_8, bp_4, arg_4);
    var_C = arg_0->unk_38;
    lv_10 = arg_0->unk_24;
    sub_1269B0(lv_10, var_C, arg_4);
    var_14 = arg_0->unk_3C;
    var_18 = arg_0->unk_28;
    sub_1269B0(var_18, var_14, arg_4);
}

// match: ?sub_1269B0@@YAXPAURpWorld@@IH@Z @ 0x001269B0
// sp-match: ?sub_1269B0@@YAXPAURpWorld@@IH@Z @ 0x000DB2C0
// Turns the world arg_0's lit flag on or off (arg_8), where its flags
// arg_4 allow it.
void sub_1269B0(RpWorld *arg_0, RwUInt32 arg_4, RwInt32 arg_8)
{
    RwUInt32 var_4;

    if (arg_0 && (arg_4 & rpWORLDLIGHT))
    {
        var_4 = arg_0->flags;
        if (arg_8)
        {
            if (var_4 & rpWORLDLIGHT)
            {
                return;
            }
            var_4 |= rpWORLDLIGHT;
        }
        else
        {
            if (!(var_4 & rpWORLDLIGHT))
            {
                return;
            }
            var_4 &= ~rpWORLDLIGHT;
        }
        RpWorldLock(arg_0);
        arg_0->flags = var_4;
        RpWorldUnlock(arg_0);
        RwResourcesEmptyArena();
    }
}

// match: ?sub_126A30@@YAPAURwCamera@@PAU1@PAURpWorld@@EMH@Z @ 0x00126A30
// sp-match: ?sub_126A30@@YAPAURwCamera@@PAU1@PAURpWorld@@EMH@Z @ 0x000DB310
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Begins a pass over the world arg_4 for the camera arg_0: the camera and
// the extra lights in the world, the near clip arg_C (the setting's, at
// least 20, without), the far clip, the fog (or none) and the blending
// (vertex alpha from arg_10), the states it changes kept for sub_126D00.
RwCamera *sub_126A30(RwCamera *arg_0, RpWorld *arg_4, RwUInt8 arg_8, RwReal arg_C,
                     RwInt32 arg_10)
{
    RpWorld *var_10;
    type_3D96FC *var_C;
    RpLight *bp_8;
    RwCamera *bp_4;

    bp_4 = 0;
    if (arg_4)
    {
        RpWorldAddCamera(arg_4, arg_0);
        arg_4->renderOrder = dword_4CF504;
        bp_8 = dword_4E5C7C;
        var_C = 0;
        var_10 = 0;
        while (bp_8)
        {
            var_10 = RpLightGetWorld(bp_8);
            if (var_10)
            {
                RpWorldRemoveLight(var_10, bp_8);
            }
            RpWorldAddLight(arg_4, bp_8);
            var_C = (type_3D96FC *)sub_FBDD0(bp_8);
            bp_8 = (RpLight *)var_C->unk_1C;
        }
    }
    if (arg_C > 0.0f)
    {
        RwCameraSetNearClipPlane(arg_0, arg_C);
    }
    else
    {
        RwCameraSetNearClipPlane(arg_0, *(RwReal *)&dword_4CF540 > 20.0f ? *(RwReal *)&dword_4CF540
                                                                          : 20.0f);
    }
    RwCameraSetFarClipPlane(arg_0, farClip);
    if (arg_8)
    {
        sub_19A750(0);
    }
    else
    {
        sub_19A750(dword_4CF490);
    }
    RwCameraGetFrame(arg_0)->modelling.flags = 3;
    arg_0->fogPlane = *(RwReal *)&dword_4CF4F0;
    bp_4 = RwCameraBeginUpdate(arg_0);
    if (bp_4)
    {
        RpLODAtomicSetCamera(arg_0);
        RwRenderStateGet(rwRENDERSTATESRCBLEND, &dword_4CF464);
        RwRenderStateGet(rwRENDERSTATEDESTBLEND, &dword_4CF484);
        RwRenderStateGet(rwRENDERSTATEVERTEXALPHAENABLE, &dword_4CF51C);
        RwRenderStateGet(rwRENDERSTATEZWRITEENABLE, &dword_4CF47C);
        RwRenderStateGet(rwRENDERSTATEZTESTENABLE, &dword_4CF478);
        RwRenderStateGet(rwRENDERSTATECULLMODE, &dword_4CF510);
        RwRenderStateGet(rwRENDERSTATEFOGENABLE, &dword_4CF75C);
        if (arg_10)
        {
            RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)dword_4CF460);
        }
        else
        {
            RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)0);
        }
        RwRenderStateSet(rwRENDERSTATESRCBLEND, (void *)dword_4CF4DC);
        RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void *)dword_4CF780);
        RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void *)dword_4CF784);
        RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void *)dword_4CF45C);
        RwRenderStateSet(rwRENDERSTATECULLMODE, (void *)dword_4CF778);
        if (!dword_4CF450)
        {
            RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void *)0);
        }
        else
        {
            RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void *)1);
            if (!RwRenderStateSet(rwRENDERSTATEFOGTYPE, (void *)dword_4CF450))
            {
                RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void *)0);
            }
            else
            {
                RwRenderStateSet(rwRENDERSTATEFOGCOLOR, (void *)dword_4CF474);
                RwRenderStateSet(rwRENDERSTATEFOGDENSITY, &dword_4CF454);
            }
        }
    }
    return bp_4;
}

// match: ?sub_126D00@@YAXPAURwCamera@@PAURpWorld@@@Z @ 0x00126D00
// sp-match: ?sub_126D00@@YAXPAURwCamera@@PAURpWorld@@@Z @ 0x000DB540
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Ends a pass sub_126A30 began: its states back, the camera and the extra
// lights out of the world, the near clip the setting's.
void sub_126D00(RwCamera *arg_0, RpWorld *arg_4)
{
    RpWorld *var_C;
    type_3D96FC *bp_8;
    RpLight *bp_4;

    RwRenderStateSet(rwRENDERSTATESRCBLEND, (void *)dword_4CF464);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void *)dword_4CF484);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)dword_4CF51C);
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void *)dword_4CF47C);
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void *)dword_4CF478);
    RwRenderStateSet(rwRENDERSTATECULLMODE, (void *)dword_4CF510);
    RwCameraEndUpdate(arg_0);
    if (arg_4)
    {
        RpWorldRemoveCamera(arg_4, arg_0);
        RwCameraSetNearClipPlane(arg_0, *(RwReal *)&dword_4CF540 > 20.0f ? *(RwReal *)&dword_4CF540
                                                                          : 20.0f);
        bp_4 = dword_4E5C7C;
        bp_8 = 0;
        var_C = 0;
        while (bp_4)
        {
            var_C = RpLightGetWorld(bp_4);
            if (var_C)
            {
                RpWorldRemoveLight(var_C, bp_4);
            }
            bp_8 = (type_3D96FC *)sub_FBDD0(bp_4);
            bp_4 = (RpLight *)bp_8->unk_1C;
        }
    }
}

// match: ?sub_126E30@@YAPAURwCamera@@PAU1@PAURpWorld@@EM@Z @ 0x00126E30
// sp-match: ?sub_126E30@@YAPAURwCamera@@PAU1@PAURpWorld@@EM@Z @ 0x000DB620
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Begins a lit pass over the world arg_4 (sub_126A30's, but for the
// lights): the ambient light and the four view lights are put in the world
// and their colours and frames kept for sub_122820 and sub_127360.
RwCamera *sub_126E30(RwCamera *arg_0, RpWorld *arg_4, RwUInt8 arg_8, RwReal arg_C)
{
    RwInt32 var_1C;
    RpWorld *var_18;
    RwCamera *var_14;
    RwRGBAReal lv_10;

    var_14 = 0;
    if (arg_4)
    {
        RpWorldAddCamera(arg_4, arg_0);
        arg_4->renderOrder = dword_4CF504;
    }
    var_18 = 0;
    lv_10.red = 0.0f;
    lv_10.green = 0.0f;
    lv_10.blue = 0.0f;
    lv_10.alpha = 0.0f;
    light = (RpLight *)clump;
    if (light)
    {
        var_18 = RpLightGetWorld(light);
        if (var_18)
        {
            RpWorldRemoveLight(var_18, light);
        }
        if (arg_4)
        {
            RpWorldAddLight(arg_4, light);
        }
        xmmword_4CF7AC = light->color;
    }
    else
    {
        xmmword_4CF7AC = lv_10;
    }
    for (var_1C = 0; var_1C < 4; var_1C++)
    {
        result[var_1C] = get_light(var_1C);
        if (result[var_1C])
        {
            var_18 = RpLightGetWorld(result[var_1C]);
            if (var_18)
            {
                RpWorldRemoveLight(var_18, result[var_1C]);
            }
            if (arg_4)
            {
                RpWorldAddLight(arg_4, result[var_1C]);
            }
            dword_4CF498[var_1C] = result[var_1C]->color;
            dword_4CF650[var_1C] = *RwFrameGetLTM(RpLightGetFrame(result[var_1C]));
        }
        else
        {
            dword_4CF498[var_1C] = lv_10;
            RwMatrixSetIdentityMacro(&dword_4CF650[var_1C]);
        }
    }
    if (arg_C > 0.0f)
    {
        RwCameraSetNearClipPlane(arg_0, arg_C);
    }
    else
    {
        RwCameraSetNearClipPlane(arg_0, *(RwReal *)&dword_4CF540 > 20.0f ? *(RwReal *)&dword_4CF540
                                                                          : 20.0f);
    }
    RwCameraSetFarClipPlane(arg_0, farClip);
    if (arg_8)
    {
        sub_19A750(0);
    }
    else
    {
        sub_19A750(dword_4CF490);
    }
    RwCameraGetFrame(arg_0)->modelling.flags = 3;
    arg_0->fogPlane = *(RwReal *)&dword_4CF4F0;
    var_14 = RwCameraBeginUpdate(arg_0);
    if (var_14)
    {
        RpLODAtomicSetCamera(arg_0);
        RwRenderStateGet(rwRENDERSTATESRCBLEND, &dword_4CF464);
        RwRenderStateGet(rwRENDERSTATEDESTBLEND, &dword_4CF484);
        RwRenderStateGet(rwRENDERSTATEVERTEXALPHAENABLE, &dword_4CF51C);
        RwRenderStateGet(rwRENDERSTATEZWRITEENABLE, &dword_4CF47C);
        RwRenderStateGet(rwRENDERSTATEZTESTENABLE, &dword_4CF478);
        RwRenderStateGet(rwRENDERSTATECULLMODE, &dword_4CF510);
        RwRenderStateGet(rwRENDERSTATEFOGENABLE, &dword_4CF75C);
        RwRenderStateSet(rwRENDERSTATESRCBLEND, (void *)dword_4CF4DC);
        RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void *)dword_4CF780);
        RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)dword_4CF460);
        RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void *)dword_4CF784);
        RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void *)dword_4CF45C);
        RwRenderStateSet(rwRENDERSTATECULLMODE, (void *)dword_4CF778);
        if (!dword_4CF450)
        {
            RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void *)0);
        }
        else
        {
            RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void *)1);
            if (!RwRenderStateSet(rwRENDERSTATEFOGTYPE, (void *)dword_4CF450))
            {
                RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void *)0);
            }
            else
            {
                RwRenderStateSet(rwRENDERSTATEFOGCOLOR, (void *)dword_4CF474);
                RwRenderStateSet(rwRENDERSTATEFOGDENSITY, &dword_4CF454);
            }
        }
    }
    return var_14;
}

// match: ?sub_127360@@YAXPAURwCamera@@PAURpWorld@@@Z @ 0x00127360
// sp-match: ?sub_127360@@YAXPAURwCamera@@PAURpWorld@@@Z @ 0x000DB9F0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Ends a lit pass: its states back, the camera out of the world, and the
// lights out of it with the colours and frames they had.
void sub_127360(RwCamera *arg_0, RpWorld *arg_4)
{
    RwInt32 var_8;
    RpWorld *l4;

    RwRenderStateSet(rwRENDERSTATESRCBLEND, (void *)dword_4CF464);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void *)dword_4CF484);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)dword_4CF51C);
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void *)dword_4CF47C);
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void *)dword_4CF478);
    RwRenderStateSet(rwRENDERSTATECULLMODE, (void *)dword_4CF510);
    RwCameraEndUpdate(arg_0);
    if (arg_4)
    {
        RpWorldRemoveCamera(arg_4, arg_0);
        RwCameraSetNearClipPlane(arg_0, *(RwReal *)&dword_4CF540 > 20.0f ? *(RwReal *)&dword_4CF540
                                                                          : 20.0f);
    }
    l4 = 0;
    if (light)
    {
        l4 = RpLightGetWorld(light);
        if (l4)
        {
            RpWorldRemoveLight(l4, light);
        }
        RpLightSetColor(light, &xmmword_4CF7AC);
    }
    for (var_8 = 0; var_8 < 4; var_8++)
    {
        if (result[var_8])
        {
            l4 = RpLightGetWorld(result[var_8]);
            if (l4)
            {
                RpWorldRemoveLight(l4, result[var_8]);
            }
            RpLightSetColor(result[var_8], &dword_4CF498[var_8]);
            *RwFrameGetLTM(RpLightGetFrame(result[var_8])) = dword_4CF650[var_8];
        }
    }
}

// match: ?sub_127530@@YAPAURwCamera@@PAU1@PAURpWorld@@@Z @ 0x00127530
// sp-match: ?sub_127530@@YAPAURwCamera@@PAU1@PAURpWorld@@@Z @ 0x000DBB50
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Begins the sky pass over the world arg_4: the camera moved to its
// position scaled by dword_4CF500 (the old kept), clipped from 5 to 1e6,
// with plain blending and no fog.
RwCamera *sub_127530(RwCamera *arg_0, RpWorld *arg_4)
{
    RwV3d *var_8;
    RwCamera *l4;

    l4 = 0;
    if (arg_4)
    {
        RpWorldAddCamera(arg_4, arg_0);
        arg_4->renderOrder = dword_4CF504;
    }
    RwCameraSetNearClipPlane(arg_0, 5.0f);
    RwCameraSetFarClipPlane(arg_0, 1000000.0f);
    sub_19A750(1);
    var_8 = &RwCameraGetFrame(arg_0)->modelling.pos;
    dword_4CF5C0 = *var_8;
    var_8->x = *(RwReal *)&dword_4CF500 * var_8->x;
    var_8->y = *(RwReal *)&dword_4CF500 * var_8->y;
    var_8->z = *(RwReal *)&dword_4CF500 * var_8->z;
    RwCameraGetFrame(arg_0)->modelling.flags = 3;
    sub_16D7F0(9);
    l4 = RwCameraBeginUpdate(arg_0);
    sub_16D850(9);
    if (l4)
    {
        RpLODAtomicSetCamera(arg_0);
        RwRenderStateGet(rwRENDERSTATESRCBLEND, &dword_4CF464);
        RwRenderStateGet(rwRENDERSTATEDESTBLEND, &dword_4CF484);
        RwRenderStateGet(rwRENDERSTATEVERTEXALPHAENABLE, &dword_4CF51C);
        RwRenderStateGet(rwRENDERSTATEZWRITEENABLE, &dword_4CF47C);
        RwRenderStateGet(rwRENDERSTATEZTESTENABLE, &dword_4CF478);
        RwRenderStateGet(rwRENDERSTATECULLMODE, &dword_4CF510);
        RwRenderStateGet(rwRENDERSTATEFOGENABLE, &dword_4CF75C);
        RwRenderStateSet(rwRENDERSTATESRCBLEND, (void *)rwBLENDSRCALPHA);
        RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void *)rwBLENDINVSRCALPHA);
        RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)1);
        RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void *)1);
        RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void *)0);
        RwRenderStateSet(rwRENDERSTATECULLMODE, (void *)rwCULLMODECULLNONE);
        RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void *)0);
    }
    return l4;
}

// match: ?sub_127700@@YAXPAURwCamera@@PAURpWorld@@@Z @ 0x00127700
// sp-match: ?sub_127700@@YAXPAURwCamera@@PAURpWorld@@@Z @ 0x000DBCB0
// Ends the sky pass: its states and the camera's position back.
void sub_127700(RwCamera *arg_0, RpWorld *arg_4)
{
    RwV3d *var_4;

    RwRenderStateSet(rwRENDERSTATESRCBLEND, (void *)dword_4CF464);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void *)dword_4CF484);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)dword_4CF51C);
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void *)dword_4CF47C);
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void *)dword_4CF478);
    RwRenderStateSet(rwRENDERSTATECULLMODE, (void *)dword_4CF510);
    RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void *)dword_4CF75C);
    var_4 = &RwCameraGetFrame(arg_0)->modelling.pos;
    *var_4 = dword_4CF5C0;
    RwCameraEndUpdate(arg_0);
    if (arg_4)
    {
        RpWorldRemoveCamera(arg_4, arg_0);
    }
}

// match: ?sub_1277D0@@YAPAURwCamera@@PAU1@PAURpWorld@@E@Z @ 0x001277D0
// sp-match: ?sub_1277D0@@YAPAURwCamera@@PAU1@PAURpWorld@@E@Z @ 0x000DBD60
// Begins the effects pass over the world arg_4 (the clip planes the
// settings' when arg_8 is set), without fog.
RwCamera *sub_1277D0(RwCamera *arg_0, RpWorld *arg_4, RwUInt8 arg_8)
{
    RwCamera *var_4;

    var_4 = 0;
    if (arg_4)
    {
        RpWorldAddCamera(arg_4, arg_0);
        arg_4->renderOrder = dword_4CF504;
    }
    if (arg_8)
    {
        RwCameraSetNearClipPlane(arg_0, *(RwReal *)&dword_4CF540 > 20.0f ? *(RwReal *)&dword_4CF540
                                                                          : 20.0f);
        RwCameraSetFarClipPlane(arg_0, farClip);
    }
    sub_19A750(1);
    RwCameraGetFrame(arg_0)->modelling.flags = 3;
    var_4 = RwCameraBeginUpdate(arg_0);
    if (var_4)
    {
        RpLODAtomicSetCamera(arg_0);
        RwRenderStateGet(rwRENDERSTATESRCBLEND, &dword_4CF464);
        RwRenderStateGet(rwRENDERSTATEDESTBLEND, &dword_4CF484);
        RwRenderStateGet(rwRENDERSTATEVERTEXALPHAENABLE, &dword_4CF51C);
        RwRenderStateGet(rwRENDERSTATEZWRITEENABLE, &dword_4CF47C);
        RwRenderStateGet(rwRENDERSTATEZTESTENABLE, &dword_4CF478);
        RwRenderStateGet(rwRENDERSTATECULLMODE, &dword_4CF510);
        RwRenderStateGet(rwRENDERSTATEFOGENABLE, &dword_4CF75C);
        RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void *)0);
    }
    return var_4;
}

// match: ?sub_127910@@YAXPAURwCamera@@PAURpWorld@@@Z @ 0x00127910
// sp-match: ?sub_127910@@YAXPAURwCamera@@PAURpWorld@@@Z @ 0x000DBE60
void sub_127910(RwCamera *arg_0, RpWorld *arg_4)
{
    RwRenderStateSet(rwRENDERSTATESRCBLEND, (void *)dword_4CF464);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void *)dword_4CF484);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)dword_4CF51C);
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void *)dword_4CF47C);
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void *)dword_4CF478);
    RwRenderStateSet(rwRENDERSTATECULLMODE, (void *)dword_4CF510);
    RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void *)dword_4CF75C);
    RwCameraEndUpdate(arg_0);
    if (arg_4)
    {
        RpWorldRemoveCamera(arg_4, arg_0);
    }
}
