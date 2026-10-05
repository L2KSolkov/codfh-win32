/*
 * RpPTank, after RenderWare 3.7.2 RWSDK/plugin/ptank/rpptank.h: the public
 * data (RpPTankData), the lock structure, the prototypes the game calls and
 * the macro forms of the atomic setters the release build maps them to
 * (MACRO_START/MACRO_STOP, visible in the image as `xor r, r; jne`). The
 * atomic's private data (RpPTankAtomicExtPrv) is kept to the fields the game
 * touches: the particle counts, the instancing flags at +0x40 and the public
 * data at +0x9C (the decal system, unit_0EFB70, sets its colour at +0xCC
 * and its blend modes at +0xAC and +0xB0).
 */
#ifndef RW_RPPTANK_H
#define RW_RPPTANK_H

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "rw/bamatrix.h"
#include "rw/batextur.h"
#include "rw/rpatomic.h"
#include "rw/rpmaterial.h"

typedef struct RwTexCoords RwTexCoords;
struct RwTexCoords
{
    RwReal u;
    RwReal v;
};

enum RpPTankDataFlags
{
    rpPTANKDFLAGNONE = 0x00000000,
    rpPTANKDFLAGPOSITION = 0x00000001,
    rpPTANKDFLAGCOLOR = 0x00000002,
    rpPTANKDFLAGSIZE = 0x00000004,
    rpPTANKDFLAGMATRIX = 0x00000008,
    rpPTANKDFLAGNORMAL = 0x00000010,
    rpPTANKDFLAG2DROTATE = 0x00000020,
    rpPTANKDFLAGVTXCOLOR = 0x00000040,
    rpPTANKDFLAGVTX2TEXCOORDS = 0x00000080,
    rpPTANKDFLAGVTX4TEXCOORDS = 0x00000100,
    rpPTANKDFLAGCNSMATRIX = 0x00008000,
    rpPTANKDFLAGCNSNORMAL = 0x00010000,
    rpPTANKDFLAGCNS2DROTATE = 0x00020000,
    rpPTANKDFLAGCNSVTXCOLOR = 0x00040000,
    rpPTANKDFLAGCNSVTX2TEXCOORDS = 0x00080000,
    rpPTANKDFLAGCNSVTX4TEXCOORDS = 0x00100000,
    rpPTANKDFLAGUSECENTER = 0x01000000,
    rpPTANKDFLAGARRAY = 0x10000000,
    rpPTANKDFLAGSTRUCTURE = 0x20000000,
    RPPTANKDATAFLAGSFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};

enum RpPTankInstanceFlags
{
    rpPTANKIFLAGNONE = 0x00000000,
    rpPTANKIFLAGCNSCOLOR = 0x00002000,
    rpPTANKIFLAGACTNUMCHG = 0x00800000,
    rpPTANKIFLAGALPHABLENDING = 0x10000000,
    RPPTANKINSTANCEFLAGSFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};

enum RpPTankLockFlags
{
    rpPTANKLFLAGNONE = 0x00000000,
    rpPTANKLFLAGPOSITION = 0x00000001,
    rpPTANKLFLAGCOLOR = 0x00000002,
    rpPTANKLFLAGSIZE = 0x00000004,
    rpPTANKLFLAGMATRIX = 0x00000008,
    rpPTANKLFLAGNORMAL = 0x00000010,
    rpPTANKLFLAG2DROTATE = 0x00000020,
    rpPTANKLFLAGVTXCOLOR = 0x00000040,
    rpPTANKLFLAGVTX2TEXCOORDS = 0x00000080,
    rpPTANKLFLAGVTX4TEXCOORDS = 0x00000100,
    rpPTANKLOCKWRITE = 0x40000000,
    rpPTANKLOCKREAD = 0x80000000,
    RPPTANKLOCKFLAGSFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};

typedef struct RpPTankLockStruct RpPTankLockStruct;
struct RpPTankLockStruct
{
    RwUInt8 *data;
    RwInt32 stride;
};

typedef struct RpPTankFormatDescriptor RpPTankFormatDescriptor;
struct RpPTankFormatDescriptor
{
    RwInt32 numClusters;
    RwInt32 stride;
    RwInt32 dataFlags;
};

typedef struct RpPTankData RpPTankData;
struct RpPTankData
{
    void *data;
    RpPTankFormatDescriptor format;
    RwUInt32 srcBlend;
    RwUInt32 dstBlend;
    RwBool vertexAlphaBlend;
    RwV2d cCenter;
    RwV2d cSize;
    RwReal cRotate;
    RwRGBA cColor;
    RwRGBA cVtxColor[4];
    RwTexCoords cUV[4];
    RwMatrixTag cMatrix;         /* (RwMatrix is 16-aligned; the image keeps the data at +0x9C) */
};

/* The atomic's private data, kept to the fields the game reaches. */
typedef struct RpPTankAtomicExtPrv RpPTankAtomicExtPrv;
struct RpPTankAtomicExtPrv
{
    RwInt32 maxPCount;
    RwInt32 actPCount;
    RwBool isAStructure;
    void *rawdata;
    RwUInt8 unk_10[0x30];
    RwUInt32 instFlags;
    RwUInt8 unk_44[0x58];
    RpPTankData publicData;
};

#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

extern RwInt32 _rpPTankAtomicDataOffset;

extern RpAtomic *RpPTankAtomicCreate(RwInt32 maxParticleNum, RwUInt32 dataFlags, RwUInt32 platFlags);
extern void RpPTankAtomicDestroy(RpAtomic *ptank);
extern RwBool RpPTankAtomicLock(RpAtomic *atomic, RpPTankLockStruct *dst, RwUInt32 dataFlags,
                                RwUInt32 lockFlags);
extern void *RpPTankAtomicLockByIndex(RpAtomic *atomic, RwInt32 idx, RwUInt32 dataFlags,
                                      RwUInt32 lockFlags);
extern RpAtomic *RpPTankAtomicUnlock(RpAtomic *atomic);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

#define RPPTANKATOMICGETINTERNALDATA(atomic_)                           \
    (*RWPLUGINOFFSET(RpPTankAtomicExtPrv *, atomic_, _rpPTankAtomicDataOffset))

#define RpPTankAtomicSetActiveParticlesCountMacro(atomic_, cnt_)        \
MACRO_START                                                             \
{                                                                       \
    RPPTANKATOMICGETINTERNALDATA(atomic_)->instFlags |= rpPTANKIFLAGACTNUMCHG; \
    RPPTANKATOMICGETINTERNALDATA(atomic_)->actPCount = (cnt_);          \
}                                                                       \
MACRO_STOP
#define RpPTankAtomicSetActiveParticlesCount(atomic_, cnt_)             \
    RpPTankAtomicSetActiveParticlesCountMacro(atomic_, cnt_)

#define RpPTankAtomicSetTextureMacro(atomic_, tex_)                     \
MACRO_START                                                             \
{                                                                       \
    RpMaterialSetTexture(RpGeometryGetMaterial(RpAtomicGetGeometry(atomic_), 0), tex_); \
}                                                                       \
MACRO_STOP
#define RpPTankAtomicSetTexture(atomic_, tex_)                          \
    RpPTankAtomicSetTextureMacro(atomic_, tex_)

#define RpPTankAtomicSetConstantColorMacro(atomic_, color_)             \
MACRO_START                                                             \
{                                                                       \
    RPPTANKATOMICGETINTERNALDATA(atomic_)->publicData.cColor = *(color_); \
    if (RpGeometryGetMaterial(RpAtomicGetGeometry(atomic_), 0))         \
    {                                                                   \
        (RpGeometryGetMaterial(RpAtomicGetGeometry(atomic_), 0))->color = \
            RPPTANKATOMICGETINTERNALDATA(atomic_)->publicData.cColor;   \
    }                                                                   \
    RPPTANKATOMICGETINTERNALDATA(atomic_)->instFlags |= rpPTANKIFLAGCNSCOLOR; \
}                                                                       \
MACRO_STOP
#define RpPTankAtomicSetConstantColor(atomic_, color_)                  \
    RpPTankAtomicSetConstantColorMacro(atomic_, color_)

#define RpPTankAtomicSetVertexAlphaMacro(atomic_, vas_)                 \
MACRO_START                                                             \
{                                                                       \
    RPPTANKATOMICGETINTERNALDATA(atomic_)->publicData.vertexAlphaBlend = (vas_); \
}                                                                       \
MACRO_STOP
#define RpPTankAtomicSetVertexAlpha(atomic_, vas_)                      \
    RpPTankAtomicSetVertexAlphaMacro(atomic_, vas_)

#define RpPTankAtomicSetBlendModesMacro(atomic_, src_, dst_)            \
MACRO_START                                                             \
{                                                                       \
    RPPTANKATOMICGETINTERNALDATA(atomic_)->publicData.srcBlend = (src_); \
    RPPTANKATOMICGETINTERNALDATA(atomic_)->publicData.dstBlend = (dst_); \
    RPPTANKATOMICGETINTERNALDATA(atomic_)->instFlags |= rpPTANKIFLAGALPHABLENDING; \
}                                                                       \
MACRO_STOP
#define RpPTankAtomicSetBlendModes(atomic_, src_, dst_)                 \
    RpPTankAtomicSetBlendModesMacro(atomic_, src_, dst_)

#endif
