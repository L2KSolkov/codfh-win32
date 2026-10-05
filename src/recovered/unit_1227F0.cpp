// The world render pass (game/worldrender.h): the atomics of the sectors in
// view, sorted by their distance from the camera, drawn with their lights.
// The original file name is not in the image, so it is named for its start
// address.

#include <string.h>

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "rw/bamatrix.h"
#include "rw/bavector.h"
#include "rw/baframe.h"
#include "rw/baengine.h"
#include "rw/badevice.h"
#include "rw/rpatomic.h"
#include "rw/rplight.h"
#include "rw/rpskin.h"
#include "rw/rpworld.h"
#include "game/worldrender.h"
#include "game/functions.h"
#include "game/data.h"
#include "types/type_3D3548.h"
#include "types/type_8E670.h"
#include "types/vec4.h"
#include "types/type_10F710.h"
#include "types/RenderTrigger.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x004CEA68
RwInt32 dword_4CEA68;
// 0x004CF7C0
type_128EB0 *dword_4CF7C0;
// End of its data definitions.


// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: __ehhandler$?sub_122DD0@@YAXPAURwCamera@@HH@Z>1>8 @ 0x0041D4F8
// match: __ehhandler$?sub_122DD0@@YAXPAURwCamera@@HH@Z>1 @ 0x0041D500

// match: ?sub_1227F0@@YAXPAURpWorldSector@@@Z @ 0x001227F0

// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_1227F0(RpWorldSector *arg_0)
{
    RwLLLink *var_4;
    RwLLLink *local_8;

    var_4 = arg_0->collAtomicsInWorldSector.link.next;
    local_8 = &arg_0->collAtomicsInWorldSector.link;
    sub_122BC0(var_4, local_8);
}

// match: ?sub_122820@@YAXPAURpAtomic@@PAUtype_3D3548@@H@Z @ 0x00122820
// Sets the lights for the atomic arg_0 of the entity arg_4 (found from the
// atomic when 0): all dark for an unskinned prelit atomic (with the ambient
// light on), else the ambient and up to four point lights from the entity's
// zone (arg_8, a type_8E670, or the entity's own), else the defaults;
// unchanged when the entity is the one last lit the same way.
void sub_122820(RpAtomic *arg_0, type_3D3548 *arg_4, RwInt32 arg_8)
{
    RwInt32 var_4;
    type_3D3548 *var_8;
    RpGeometry *var_C;
    RwUInt32 var_10;
    RpSkin *var_14;
    RwInt32 var_18;
    RwRGBAReal var_28;
    RwInt32 var_2C;
    type_8F210 var_E0;
    RwInt32 var_E4;
    RwInt32 var_E8;

    var_4 = 0;
    var_8 = sub_1745A0(0);
    if (var_8 == arg_4)
    {
        dword_4CEA68++;
    }
    var_C = RpAtomicGetGeometry(arg_0);
    if (var_C && light)
    {
        var_10 = RpGeometryGetFlags(var_C);
        if (var_10 & 8)
        {
            var_14 = 0;
            var_14 = RpSkinGeometryGetSkin(var_C);
            if (!var_14)
            {
                var_4 = 1;
            }
        }
    }
    var_18 = 0;
    if (var_4)
    {
        if (dword_4CF7A4 != 2)
        {
            var_18 = 1;
        }
    }
    else
    {
        if (!arg_4)
        {
            arg_4 = sub_FB960(arg_0);
        }
        if (dword_4CF7A4 == 1)
        {
            if (arg_4 != (type_3D3548 *)dword_4CF7BC)
            {
                var_18 = 1;
            }
        }
        else
        {
            var_18 = 1;
        }
    }
    if (var_18)
    {
        var_28.red = 0.0f;
        var_28.green = 0.0f;
        var_28.blue = 0.0f;
        var_28.alpha = 0.0f;
        if (var_4)
        {
            if (light)
            {
                RpLightSetColor(light, &var_28);
            }
            for (var_2C = 0; var_2C < 4; var_2C++)
            {
                if (result[var_2C])
                {
                    RpLightSetColor(result[var_2C], &var_28);
                }
            }
            dword_4CF7A4 = 2;
            dword_4CF7BC = (RwInt32)arg_4;
        }
        else
        {
            var_E0.unk_00 = 0;
            if (arg_4)
            {
                if (arg_4->unk_28_17)
                {
                    if (arg_8)
                    {
                        ((type_8E670 *)arg_8)->sub_8E870(&var_E0);
                    }
                    else
                    {
                        arg_4->unk_90.sub_8E870(&var_E0);
                    }
                }
                if (var_E0.unk_00)
                {
                    if (light)
                    {
                        RpLightSetColor(light, (RwRGBAReal *)&var_E0.unk_10[0].unk_10);
                    }
                    for (var_E4 = 0; var_E4 < 4; var_E4++)
                    {
                        if (var_E4 < var_E0.unk_00)
                        {
                            RpLightSetColor(result[var_E4],
                                            (RwRGBAReal *)&var_E0.unk_10[var_E4 + 1].unk_10);
                            RwFrameGetLTM(RpLightGetFrame(result[var_E4]))->at =
                                *(RwV3d *)&var_E0.unk_10[var_E4 + 1].unk_00;
                        }
                        else
                        {
                            RpLightSetColor(result[var_E4], &var_28);
                        }
                    }
                }
            }
            if (!var_E0.unk_00)
            {
                if (light)
                {
                    RpLightSetColor(light, &xmmword_4CF7AC);
                }
                for (var_E8 = 0; var_E8 < 4; var_E8++)
                {
                    if (result[var_E8])
                    {
                        RpLightSetColor(result[var_E8], &dword_4CF498[var_E8]);
                        *RwFrameGetLTM(RpLightGetFrame(result[var_E8])) = dword_4CF650[var_E8];
                    }
                }
            }
            dword_4CF7A4 = 1;
            dword_4CF7BC = (RwInt32)arg_4;
        }
    }
}

// match: ?sub_122BC0@@YAXPAURwLLLink@@0@Z @ 0x00122BC0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Sorts the atomics of the ties from arg_0 to arg_4 that are to be drawn,
// in view and not yet seen this frame (and whose entity is not hidden) by
// their squared distance from the camera, marking each entity sorted.
void sub_122BC0(RwLLLink *arg_0, RwLLLink *arg_4)
{
    RwV3d var_3C;
    RwV3d var_30;
    RwReal var_24;
    RwFrame *var_20;
    RwInt32 l1C;
    type_3D3548 *m_18;
    const RwSphere *ebp_14;
    RpTie *lv_10;
    RwMatrix *var_C;
    RpAtomic *bp_8;
    RwCamera *bp_4;

    bp_4 = RwCameraGetCurrentCamera();
    var_C = RwFrameGetMatrix(RwCameraGetFrame(bp_4));
    while (arg_0 != arg_4)
    {
        lv_10 = (RpTie *)arg_0;
        bp_8 = lv_10->apAtom;
        if ((RpAtomicGetFlags(bp_8) & rpATOMICRENDER)
            && bp_8->renderFrame != RWSRCGLOBAL(renderFrame))
        {
            ebp_14 = RpAtomicGetWorldBoundingSphere(bp_8);
            if (RwCameraFrustumTestSphere(bp_4, ebp_14))
            {
                l1C = 1;
                m_18 = sub_FB960(bp_8);
                if (m_18 && (m_18->unk_28 & 0x200000))  // unk_28_21 (hidden); not an address
                {
                    l1C = 0;
                }
                if (l1C)
                {
                    var_20 = RpAtomicGetFrame(bp_8);
                    if (var_20)
                    {
                        var_3C = RwFrameGetLTM(var_20)->pos;
                        var_30.x = var_3C.x - var_C->pos.x;
                        var_30.y = var_3C.y - var_C->pos.y;
                        var_30.z = var_3C.z - var_C->pos.z;
                        var_24 = RwV3dDotProduct(&var_30, &var_30);
                        dword_4CF7C0->sub_128EB0(bp_8, var_24);
                        if (m_18)
                        {
                            m_18->unk_28 |= 0x400;
                        }
                    }
                }
            }
            bp_8->renderFrame = RWSRCGLOBAL(renderFrame);
        }
        arg_0 = arg_0->next;
    }
}

// match: ?sub_122D40@@YAPAURpWorldSector@@PAU1@PAX@Z @ 0x00122D40
// The sector walk's callback: sorts the sector's atomics, if the PVS shows
// it when asked to check.
RpWorldSector *sub_122D40(RpWorldSector *arg_0, void *arg_4)
{
    type_122D90 *var_4;

    var_4 = (type_122D90 *)arg_4;
    if (var_4->unk_08)
    {
        if (RpPVSWorldSectorVisible(arg_0))
        {
            sub_1227F0(arg_0);
        }
    }
    else
    {
        sub_1227F0(arg_0);
    }
    return arg_0;
}

// match: ?sub_122D90@@YAXPAURwCamera@@HH@Z @ 0x00122D90
void sub_122D90(RwCamera *arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    type_122D90 var_C;

    var_C.unk_08 = arg_8;
    var_C.unk_00 = arg_0;
    var_C.unk_04 = arg_4;
    if (dword_4CF760)
    {
        RwCameraForAllSectorsInFrustum(arg_0, sub_122D40, &var_C);
    }
}

// match: ?sub_122DD0@@YAXPAURwCamera@@HH@Z @ 0x00122DD0
// match: __ehhandler$?sub_122DD0@@YAXPAURwCamera@@HH@Z-0xB @ 0x00301580
// match: __ehhandler$?sub_122DD0@@YAXPAURwCamera@@HH@Z @ 0x0030158B
// Draws the world's atomics for the camera arg_0: sorts those in view, then
// draws the trees without fog or culling, the second without the depth test.
void sub_122DD0(RwCamera *arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    if (arg_0 && sub_126E30(arg_0, (RpWorld *)arg_4, 1, 0))
    {
        dword_4CF7A4 = 0;
        dword_4CF7BC = 0;
        type_128EB0 var_191C;
        sub_122D90(arg_0, arg_4, arg_8);
        sub_122F50();
        RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void *)0);
        RwRenderStateSet(rwRENDERSTATECULLMODE, (void *)rwCULLMODECULLNONE);
        var_191C.sub_129010(var_191C.unk_1904[0]);
        RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void *)0);
        var_191C.sub_129010(var_191C.unk_1904[1]);
        RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void *)1);
        var_191C.sub_129010(var_191C.unk_1904[2]);
        sub_127360(arg_0, (RpWorld *)arg_4);
    }
}

// match: ??1type_128EB0@@QAE@XZ @ 0x00122F30
// (In the class.)

// match: ?sub_122F50@@YAXXZ @ 0x00122F50
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_122F50()
{
    type_3D3548 *local_8;
    type_10F710 *var_4;

    local_8 = 0;
    var_4 = (type_10F710 *)sub_1745A0(dword_429EB0);
    if (var_4)
    {
        local_8 = var_4->unk_2110.sub_D4910();
    }
    RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTION, (void *)rwALPHATESTFUNCTIONGREATER);
    RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTIONREF, (void *)0);
}
