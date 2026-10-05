/*
 * RpAtomic's leading fields, RpAtomicGetGeometry, RpAtomicGetFrame and
 * RpClumpGetFrame, RpClumpSetFrame, RpAtomicSetFrame, RpAtomicCreate, RpAtomicSetFlags,
 * RpAtomicGetBoundingSphere,
 * RpGeometry's flags and their accessors, and
 * RpClumpForAllAtomics (with RpAtomicCallBack), from
 * RenderWare 3.7.2
 * RWSDK/include/null/rpworld.h: the frame object (0x14 bytes, kept opaque),
 * repEntry, geometry, the bounding spheres, clump and inClumpLink. The
 * image's layout agrees: the Vision Scheduler's sub_42350 tests +0x18 before
 * testing an atomic's triangles.
 */
#ifndef RW_RPATOMIC_H
#define RW_RPATOMIC_H

#include "rw/batypes.h"
#include "rw/rpcollis.h"
#include "rw/baframe.h"

typedef struct RpGeometry RpGeometry;

/* RpInterpolator's flags (the rest is not declared) and the dirty-sphere
 * flag RpAtomicGetBoundingSphere tests. */
typedef struct RpInterpolator RpInterpolator;
struct RpInterpolator
{
    RwInt32             flags;
    RwInt16             startMorphTarget;
    RwInt16             endMorphTarget;
    RwReal              time;
    RwReal              recipTime;
    RwReal              position;
};
#define rpINTERPOLATORDIRTYSPHERE 0x02
typedef struct RpClump RpClump;

/* The start of RpGeometry: the object header, its flags and its material
 * list, with their accessors; the rest is not declared. */
typedef struct RpMaterial RpMaterial;
typedef struct RpMaterialList RpMaterialList;
struct RpMaterialList
{
    RpMaterial        **materials;
    RwInt32             numMaterials;
    RwInt32             space;
};

struct RpGeometry
{
    RwObject            object;
    RwUInt32            flags;
    RwUInt16            lockedSinceLastInst;
    RwInt16             refCount;
    RwInt32             numTriangles;
    RwInt32             numVertices;
    RwInt32             numMorphTargets;
    RwInt32             numTexCoordSets;
    RpMaterialList      matList;
    void               *triangles;
    RwRGBA             *preLitLum;
    void               *texCoords[8];
    struct RpMeshHeader *mesh;  /* the render parts (unit_16D8C0) read its
                                 * first mesh's material */
    void               *repEntry;
    struct RpMorphTarget *morphTarget; /* the GodAsset models bound their
                                        * first one's vertices (sub_18FC80) */
};
typedef struct RpMorphTarget RpMorphTarget;
struct RpMorphTarget
{
    RpGeometry         *parentGeom;
    RwSphere            boundingSphere;
    RwV3d              *verts;
    RwV3d              *normals;
};
#define RpGeometryGetNumMaterialsMacro(_geometry)                       \
    ((_geometry)->matList.numMaterials)
#define RpGeometryGetNumMaterials(_geometry)                            \
    RpGeometryGetNumMaterialsMacro(_geometry)
#define RpGeometryGetMaterialMacro(_geometry, _num)                     \
    (((_geometry)->matList.materials)[(_num)])
#define RpGeometryGetMaterial(_geometry, _num)                          \
    RpGeometryGetMaterialMacro(_geometry, _num)
#define rpGEOMETRYTEXTURED 0x00000004
#define rpGEOMETRYMODULATEMATERIALCOLOR 0x00000040
#define rpGEOMETRYTEXTURED2 0x00000080
#define RpGeometryGetFlagsMacro(_geometry) ((_geometry)->flags)
#define RpGeometryGetFlags(_geometry) RpGeometryGetFlagsMacro(_geometry)
#define RpGeometrySetFlagsMacro(_geometry, _flags)                      \
    (((_geometry)->flags = (_flags)), (_geometry))
#define RpGeometrySetFlags(_geometry, _flags)                           \
    RpGeometrySetFlagsMacro(_geometry, _flags)

typedef RpAtomic *(*RpAtomicCallBackRender) (RpAtomic * atomic);

struct RpAtomic
{
    RwUInt8             object[0x14];
    void               *repEntry;
    RpGeometry         *geometry;
    RwSphere            boundingSphere;
    RwSphere            worldBoundingSphere;
    RpClump            *clump;
    RwLLLink            inClumpLink;
    RpAtomicCallBackRender renderCallBack;
    RpInterpolator      interpolator;
    /* Counters for checking (the player's weapon render callback,
     * sub_110EC0, draws an atomic once per camera frame). */
    RwUInt16            renderFrame;
    RwUInt16            pad;
    /* Its world sectors and its pipeline (type_3D3548::vf_224 copies an
     * atomic's pipeline to its collision atomic). */
    RwLinkList          llWorldSectorsInAtomic;
    void               *pipeline;
};

/* The start of RpClump: the object header and its list of atomics (linked
 * through their inClumpLink); the rest is not declared. */
struct RpClump
{
    RwObject            object;
    RwLinkList          atomicList;
};
/* The clump's stream chunk (rwID_CLUMP, rwVENDORID_CORE's 0x10). */
#define rwID_CLUMP 0x10

#define RpAtomicGetGeometryMacro(_atomic)  ((_atomic)->geometry)
#define RpAtomicGetGeometry(_atomic)       RpAtomicGetGeometryMacro(_atomic)

#define RpAtomicGetFrameMacro(_atomic)                                  \
    ((RwFrame *) rwObjectGetParent(_atomic))

/* The render (the decal system, sub_F03F0, draws its PTank atomic with it). */
#define RpAtomicRenderMacro(_atomic)                                    \
    ((_atomic)->renderCallBack(_atomic))
#define RpAtomicRender(_atomic) RpAtomicRenderMacro(_atomic)
/* The default render callback (RpAtomicSetRenderCallBack's default). */
#ifdef    __cplusplus
extern "C" RpAtomic *AtomicDefaultRenderCallBack(RpAtomic *atomic);
#else
extern RpAtomic *AtomicDefaultRenderCallBack(RpAtomic *atomic);
#endif
#define RpAtomicGetFrame(_atomic)          RpAtomicGetFrameMacro(_atomic)
/* The render callback's setter (RW 3.7.2's rpworld.h macro form: the default
 * callback replaces a null one). */
#define RpAtomicSetRenderCallBackMacro(_atomic, _callback)              \
MACRO_START                                                           \
{                                                                     \
    (_atomic)->renderCallBack = (_callback);                          \
    if (!(_atomic)->renderCallBack)                                   \
    {                                                                 \
        (_atomic)->renderCallBack = AtomicDefaultRenderCallBack;      \
    }                                                                 \
}                                                                     \
MACRO_STOP
#define RpAtomicSetRenderCallBack(_atomic, _callback)                   \
    RpAtomicSetRenderCallBackMacro(_atomic, _callback)

#define RpClumpGetFrameMacro(_clump)                                    \
    ((RwFrame *) rwObjectGetParent(_clump))
#define RpClumpGetFrame(_clump)            RpClumpGetFrameMacro(_clump)

#define RpClumpSetFrameMacro(_clump, _frame)                                (rwObjectSetParent(_clump, _frame),                                      (_clump))
#define RpClumpSetFrame(_clump, _frame)    RpClumpSetFrameMacro(_clump, _frame)

/* The atomic's flags (RpAtomicFlag), their getter and setter, from RW 3.7.2's
 * rpworld.h and badevice.h (rwObjectSetFlags). */
enum RpAtomicFlag
{
    rpATOMICCOLLISIONTEST = 0x01,
    rpATOMICRENDER = 0x04
};
#define rwObjectSetFlags(o, f) (((RwObject *)(o))->flags = (RwUInt8)(f))
#define rwObjectGetFlags(o) (((const RwObject *)(o))->flags)
#define RpAtomicGetFlagsMacro(_atomic) (rwObjectGetFlags(_atomic))
#define RpAtomicGetFlags(_atomic) RpAtomicGetFlagsMacro(_atomic)
#define RpAtomicSetFlagsMacro(_atomic, _flags)                              (rwObjectSetFlags((_atomic), (_flags)), (_atomic))
#define RpAtomicSetFlags(_atomic, _flags) RpAtomicSetFlagsMacro(_atomic, _flags)

typedef RpAtomic *(*RpAtomicCallBack)(RpAtomic *atomic, void *data);

#define RpAtomicGetBoundingSphereMacro(_atomic)                         ((((_atomic)->interpolator.flags & rpINTERPOLATORDIRTYSPHERE)?            _rpAtomicResyncInterpolatedSphere(_atomic), 0: 0),                      &((_atomic)->boundingSphere))
#define RpAtomicGetBoundingSphere(_atomic)                                  RpAtomicGetBoundingSphereMacro(_atomic)

#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

extern const RwSphere *RpAtomicGetWorldBoundingSphere(RpAtomic * atomic);

extern void _rpAtomicResyncInterpolatedSphere(RpAtomic * atomic);

extern RpAtomic *RpAtomicSetFrame(RpAtomic * atomic, RwFrame * frame);
extern RpAtomic *RpAtomicCreate(void);

extern RpClump *RpClumpForAllAtomics(RpClump * clump,
                                     RpAtomicCallBack callback, void *pData);
extern RwBool RpClumpDestroy(RpClump * clump);
extern RpClump *RpClumpClone(RpClump * clump);
extern struct RpWorld *RpClumpGetWorld(const RpClump * clump);
/* What the object holders (unit_129430) take an atomic, clump or light
 * apart with. */
extern RpClump *RpClumpRemoveAtomic(RpClump * clump, RpAtomic * atomic);
extern RwBool RpAtomicDestroy(RpAtomic * atomic);
extern struct RpWorld *RpAtomicGetWorld(const RpAtomic *atomic);
typedef struct RpLight RpLight;
typedef RpLight *(*RpLightCallBack) (RpLight * light, void *data);
extern RpClump *RpClumpForAllLights(RpClump * clump, RpLightCallBack callback, void *pData);
extern RpClump *RpClumpRemoveLight(RpClump * clump, RpLight * light);
extern RpClump *RpLightGetClump(const RpLight *light);

/* The plugin registration and the clump reader (the game's clump data
 * plugin, unit_0EBF10, registers with it and reads through it), from
 * RWSDK/src/plcore/bapipe.h and rpworld.h. */
typedef void *(*RwPluginObjectConstructor)(void *object, RwInt32 offsetInObject, RwInt32 sizeInObject);
typedef void *(*RwPluginObjectDestructor)(void *object, RwInt32 offsetInObject, RwInt32 sizeInObject);
typedef void *(*RwPluginObjectCopy)(void *dstObject, const void *srcObject, RwInt32 offsetInObject,
                                    RwInt32 sizeInObject);
extern RwInt32 RpClumpRegisterPlugin(RwInt32 size, RwUInt32 pluginID,
                                     RwPluginObjectConstructor constructCB,
                                     RwPluginObjectDestructor destructCB,
                                     RwPluginObjectCopy copyCB);
extern RwInt32 RpAtomicRegisterPlugin(RwInt32 size, RwUInt32 pluginID,
                                      RwPluginObjectConstructor constructCB,
                                      RwPluginObjectDestructor destructCB,
                                      RwPluginObjectCopy copyCB);
struct RwStream;
extern RpClump *RpClumpStreamRead(struct RwStream * stream);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

#endif
