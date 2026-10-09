// The decal system (include/game/decals.h). The original file name is not
// in the image, so it is named for its start address.

#include "rw/ostypes.h"
#include "game/frand.h"
#include "rw/bamatrix.h"
#include "rw/baframe.h"
#include "rw/baraster.h"
#include "rw/badevice.h"
#include "rw/bavector.h"
#include "rw/rprandom.h"
#include "rw/rpptank.h"
#include "game/decals.h"
#include "game/pooledconsts.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003D91B0
extern const RwReal flt_3D91B0 = 16.666666f;
// 0x004296C0
type_4296C0 unk_4296C0 = { 10.0f, 10.0f, 0, 0 };
// 0x004B9E6C
RpAtomic *atomic;
// 0x004B9E70
RwTexCoords *dword_4B9E70;
// 0x004B9E74
RwMatrix *dword_4B9E74;
// 0x004B9E78
RwUInt8 *dword_4B9E78;
// 0x004B9E7C
RwUInt32 dword_4B9E7C;
// 0x004B9E80
RwUInt32 dword_4B9E80;
// 0x004B9E84
RwUInt32 dword_4B9E84;
// 0x004B9E88
RwUInt32 dword_4B9E88;
// End of its data definitions.


// The engine's memory functions' first two slots (include/rw/bamemory.h).

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3D91B0@@3MB @ 0x003D91B0
// match: ??_C@_06FNIEFDBE@decals?$AA@ @ 0x003D91B4
// match: ?unk_4296C0@@3Utype_4296C0@@A @ 0x004296C0

// match: _RpPrtStdEmitterCreatePTank @ 0x000EFBC0
// sp-match: _RpPrtStdEmitterCreatePTank @ 0x000B7550

// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
extern "C" void RpPrtStdEmitterCreatePTank()
{
    RwInt32 slot_C;
    RwFrame *bp_8;
    RwRGBA bp_4;

    atomic = RpPTankAtomicCreate(0x40, rpPTANKDFLAGMATRIX | rpPTANKDFLAGVTX2TEXCOORDS, 0);
    if (!atomic)
    {
        return;
    }
    bp_8 = RwFrameCreate();
    RwMatrixSetIdentity(RwFrameGetMatrix(bp_8));
    RpAtomicSetFrame(atomic, bp_8);
    dword_4B9E74 = (RwMatrix *)RwMalloc(0x1000, 0x34250); // not an address: an allocation tag
    dword_4B9E70 = (RwTexCoords *)RwMalloc(0x200, 0x34250); // not an address: an allocation tag
    dword_4B9E78 = (RwUInt8 *)RwMalloc(0x40, 0x34250); // not an address: an allocation tag
    for (slot_C = 0; slot_C < 0x40; slot_C++)
    {
        RwMatrixSetIdentity(&dword_4B9E74[slot_C]);
        dword_4B9E70[slot_C].u = 0;
        dword_4B9E70[slot_C].v = 0;
        dword_4B9E78[slot_C] = 0;
    }
    dword_4B9E7C = 0;
    dword_4B9E80 = 0;
    dword_4B9E84 = 0;
    dword_4B9E88 = 0;
    bp_4.red = 0xFF;
    bp_4.green = 0xFF;
    bp_4.blue = 0xFF;
    bp_4.alpha = 0xFE;
    RpPTankAtomicSetConstantColor(atomic, &bp_4);
    RpPTankAtomicSetVertexAlpha(atomic, TRUE);
    RpPTankAtomicSetBlendModes(atomic, rwBLENDSRCALPHA, rwBLENDINVSRCALPHA);
}

// match: ?sub_EFF70@@YAXXZ @ 0x000EFF70
// sp-match: ?sub_EFF70@@YAXXZ @ 0x000B77A0
void sub_EFF70()
{
    dword_4B9E7C = 0;
    dword_4B9E80 = 0;
    dword_4B9E84 = 0;
    dword_4B9E88 = 0;
    RpPTankAtomicSetActiveParticlesCount(atomic, dword_4B9E80);
    RpPTankAtomicSetTexture(atomic, 0);
}

// match: ?sub_F0000@@YAXXZ @ 0x000F0000
// sp-match: ?sub_F0000@@YAXXZ @ 0x000B7800
void sub_F0000()
{
    RwFrame *var_4;

    if (atomic)
    {
        RpPTankAtomicSetTexture(atomic, 0);
        var_4 = RpAtomicGetFrameMacro(atomic);
        if (var_4)
        {
            RpAtomicSetFrame(atomic, 0);
            RwFrameDestroy(var_4);
        }
        RpPTankAtomicDestroy(atomic);
        RwFree(dword_4B9E74);
        RwFree(dword_4B9E70);
        RwFree(dword_4B9E78);
    }
    dword_4B9E80 = 0;
    dword_4B9E7C = 0;
}

// match: ?sub_F00C0@@YAXXZ @ 0x000F00C0
// sp-match: ?sub_F00C0@@YAXXZ @ 0x000B7880
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_F00C0()
{
    RwUInt32 t20;
    RwUInt32 l1C;
    RwRaster *m_18;
    RwTexture *ebp_14;
    RpPTankLockStruct lv_10;
    RwUInt8 *bp_8;
    RwUInt8 *bp_4;

    if (!atomic)
    {
        return;
    }
    if (dict && !dword_4B9E84)
    {
        ebp_14 = RwTexDictionaryFindNamedTexture(dict, "decals");
        if (ebp_14)
        {
            RwTextureSetFilterMode(ebp_14, rwFILTERLINEAR);
            RpPTankAtomicSetTexture(atomic, ebp_14);
            if (!dword_4B9E84)
            {
                m_18 = RwTextureGetRaster(ebp_14);
                if (m_18)
                {
                    dword_4B9E84 = m_18->width;
                    dword_4B9E88 = m_18->height;
                }
            }
        }
    }
    if (!dword_4B9E80)
    {
        return;
    }
    RpPTankAtomicSetActiveParticlesCount(atomic, dword_4B9E80);
    RpPTankAtomicLock(atomic, &lv_10, rpPTANKLFLAGVTX2TEXCOORDS, rpPTANKLOCKWRITE);
    bp_4 = lv_10.data;
    for (l1C = 0; l1C < dword_4B9E80; l1C++)
    {
        if (dword_4B9E78[l1C] != 2)
        {
            ((RwTexCoords *)bp_4)[0].u = dword_4B9E70[l1C].u;
            ((RwTexCoords *)bp_4)[0].v = dword_4B9E70[l1C].v;
            ((RwTexCoords *)bp_4)[1].u = dword_4B9E70[l1C].u + 0.25f;
            ((RwTexCoords *)bp_4)[1].v = dword_4B9E70[l1C].v + 0.25f;
        }
        bp_4 += lv_10.stride;
    }
    RpPTankAtomicUnlock(atomic);
    RpPTankAtomicLock(atomic, &lv_10, rpPTANKLFLAGMATRIX, rpPTANKLOCKWRITE);
    bp_8 = lv_10.data;
    for (t20 = 0; t20 < dword_4B9E80; t20++)
    {
        if (dword_4B9E78[t20] != 2)
        {
            ((RwMatrix *)bp_8)->pos.x = dword_4B9E74[t20].pos.x;
            ((RwMatrix *)bp_8)->pos.y = dword_4B9E74[t20].pos.y;
            ((RwMatrix *)bp_8)->pos.z = dword_4B9E74[t20].pos.z;
            ((RwMatrix *)bp_8)->right.x = unk_4296C0.unk_00 * dword_4B9E74[t20].right.x;
            ((RwMatrix *)bp_8)->right.y = unk_4296C0.unk_00 * dword_4B9E74[t20].right.y;
            ((RwMatrix *)bp_8)->right.z = unk_4296C0.unk_00 * dword_4B9E74[t20].right.z;
            ((RwMatrix *)bp_8)->up.x = unk_4296C0.unk_04 * dword_4B9E74[t20].at.x;
            ((RwMatrix *)bp_8)->up.y = unk_4296C0.unk_04 * dword_4B9E74[t20].at.y;
            ((RwMatrix *)bp_8)->up.z = unk_4296C0.unk_04 * dword_4B9E74[t20].at.z;
            dword_4B9E78[t20]++;
        }
        bp_8 += lv_10.stride;
    }
    RpPTankAtomicUnlock(atomic);
}

// match: ?sub_F03F0@@YAXXZ @ 0x000F03F0
// sp-match: ?sub_F03F0@@YAXXZ @ 0x000B7AE0
void sub_F03F0()
{
    if (atomic)
    {
        RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)TRUE);
        RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void *)TRUE);
        RwRenderStateSet(rwRENDERSTATECULLMODE, (void *)rwCULLMODECULLNONE);
        RwRenderStateSet(rwRENDERSTATESRCBLEND, (void *)rwBLENDONE);
        RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void *)rwBLENDONE);
        RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void *)TRUE);
        RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void *)FALSE);
        RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void *)FALSE);
        RpPTankAtomicSetBlendModes(atomic, rwBLENDSRCALPHA, rwBLENDINVSRCALPHA);
        RpAtomicRender(atomic);
    }
}

// match: ?sub_F04E0@@YAXPAURwMatrixTag@@HH@Z @ 0x000F04E0
// sp-match: ?sub_F04E0@@YAXPAURwMatrixTag@@HH@Z @ 0x000B7B90
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_F04E0(RwMatrix *arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    RwReal q28;
    RwMatrix *frm_24;
    RwInt32 t20;
    RwTexCoords *l1C;
    RwInt32 m_18;
    RwV3d ebp_14;
    RwInt32 bp_8;
    RwInt32 bp_4;

    if (!atomic)
    {
        return;
    }
    if (!dword_4B9E84)
    {
        return;
    }
    dword_4B9E74[dword_4B9E7C] = *arg_0;
    dword_4B9E78[dword_4B9E7C] = 0;
    frm_24 = &dword_4B9E74[dword_4B9E7C];
    frm_24->pos.x += frm_24->up.x * 1.0f;
    frm_24->pos.y += frm_24->up.y * 1.0f;
    frm_24->pos.z += frm_24->up.z * 1.0f;
    bp_8 = dword_4B9E84 >> 5;
    m_18 = dword_4B9E88 >> 5;
    t20 = arg_4 % bp_8;
    bp_4 = arg_4 / m_18;
    l1C = &dword_4B9E70[dword_4B9E7C];
    l1C->u = (RwReal)(t20 << 5) / (RwReal)dword_4B9E84;
    l1C->v = (RwReal)(bp_4 << 5) / (RwReal)dword_4B9E88;
    ebp_14 = frm_24->up;
    q28 = (RwReal)RpRandom() * (1.0f / RPRANDMAX);
    sub_140440(frm_24, &ebp_14, lerp(-3.14159f, 3.14159f, q28));
    dword_4B9E7C = (dword_4B9E7C + 1) & 0x3F;
    dword_4B9E80 = dword_4B9E80 + 1 > 0x40 ? 0x40 : dword_4B9E80 + 1;
}
