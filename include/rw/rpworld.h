/*
 * RpWorldForAllWorldSectors, RwCameraForAllSectorsInFrustum and their
 * callback type, RpTie, RpTriangle, the start of RpWorld (to its render
 * order) and of RpWorldSector (to its atomics), the world's flags, and the
 * world, light and sector functions the game calls, copied from RenderWare
 * 3.7.2 RWSDK/include/null/rpworld.h. The image's layout agrees: sub_1227F0
 * walks a sector's atomics from +0x38, and the main render (unit_125490)
 * sets a world's flags at +8 between RpWorldLock and RpWorldUnlock.
 */
#ifndef RW_RPWORLD_H
#define RW_RPWORLD_H

#include "rw/rpcollis.h"

typedef struct RwCamera RwCamera;
typedef struct RpLight RpLight;
typedef struct RpClump RpClump;
typedef struct RpMaterial RpMaterial;

/* The start of RpWorld: its object header, flags, render order and material
 * list; the rest is not declared. */
struct RpWorld
{
    RwUInt8             object[0x8];
    RwUInt32            flags;
    RwInt32             renderOrder;
    /* Its material list (RpMaterialList): the world line test (sub_91F40)
     * reads a triangle's material through it. */
    struct RpMaterial **materials;
    RwInt32             numMaterials;
    RwInt32             space;
    RwUInt8             unk_1C[0x28];
    RwV3d               worldOrigin;
    RwBBox              boundingBox;    /* the world manager (sub_172C60)
                                         * places a frame by it */
};
/* RenderWare's RpWorldGetFlags as the game's code expands it: through a
 * result local (the world manager's sub_173CE0 reads each world's flags
 * into a temporary of its own), so an inline function, not the macro. */
#ifdef __cplusplus
inline RwUInt32 RpWorldGetFlags(const RpWorld *world)
{
    RwUInt32 r = world->flags;
    return r;
}
#endif
enum RpWorldFlag
{
    rpWORLDTRISTRIP = 0x01,
    rpWORLDTEXTURED = 0x04,
    rpWORLDPRELIT = 0x08,
    rpWORLDNORMALS = 0x10,
    rpWORLDLIGHT = 0x20
};

typedef struct RpTriangle RpTriangle;
struct RpTriangle
{
    RwUInt16            vertIndex[3];
    RwUInt16            matIndex;       /* unsigned in RW 3.6: the world line
                                         * test (sub_91F40) zero-extends it */
};

typedef RpWorldSector *(*RpWorldSectorCallBack)(RpWorldSector *worldSector, void *data);

/* The start of RpWorldSector: to its atomics (linked through their ties'
 * lAtomicInWorldSector); the rest is not declared. */
struct RpWorldSector
{
    RwInt32             type;
    RpTriangle         *triangles;
    RwV3d              *vertices;
    void               *normals;
    void               *texCoords[8];
    RwRGBA             *preLitLum;
    void               *repEntry;
    RwLinkList          collAtomicsInWorldSector;
};

typedef struct RpTie RpTie;
struct RpTie
{
    RwLLLink            lAtomicInWorldSector;
    RpAtomic           *apAtom;
    RwLLLink            lWorldSectorInAtomic;
    RpWorldSector      *worldSector;
};

#ifdef    __cplusplus
extern "C"
{
#endif         /* __cplusplus */

extern RpWorld *
RpWorldForAllWorldSectors(RpWorld *world, RpWorldSectorCallBack fpCallBack, void *pData);
extern RwCamera *RwCameraForAllSectorsInFrustum(RwCamera *camera,
                                                RpWorldSectorCallBack callBack,
                                                void *pData);
extern RpWorld *RpWorldForAllClumps(RpWorld * world,
                                    RpClump *(*fpCallBack)(RpClump *clump, void *data),
                                    void *pData);
extern RpWorld *RpWorldForAllLights(RpWorld * world,
                                    RpLight *(*fpCallBack)(RpLight *light, void *data),
                                    void *pData);
extern RpWorldSector *RpWorldSectorForAllAtomics(RpWorldSector *sector,
                                                 RpAtomic *(*fpCallBack)(RpAtomic *atomic, void *data),
                                                 void *pData);
extern RpWorld *RpWorldLock(RpWorld * world);
extern RpWorld *RpWorldUnlock(RpWorld * world);
extern RpWorld *RpWorldAddLight(RpWorld *world, RpLight *light);
/* The database names it RpWorldAddClump_0 (config/aliases.txt). */
extern RpWorld *RpWorldAddClump(RpWorld *world, RpClump *clump);
extern RpWorld *RpWorldAddAtomic(RpWorld *world, RpAtomic *atomic);
extern RpWorld *RpWorldRemoveLight(RpWorld *world, RpLight *light);
extern RpWorld *RpLightGetWorld(const RpLight *light);
extern RpWorld *RpWorldForAllMaterials(RpWorld * world,
                                       RpMaterial *(*fpCallBack)(RpMaterial *material,
                                                                 void *data),
                                       void *pData);
extern RpWorldSector *RpWorldSectorRender(RpWorldSector *worldSector);
/* The PVS plugin's (rppvs). */
extern RwBool RpPVSWorldSectorVisible(RpWorldSector *sector);
extern RwBool RpPVSQuery(RpWorld *wpWorld);
extern RpWorld *RpWorldRemoveAtomic(RpWorld *world, RpAtomic *atomic);
extern RpWorld *RpWorldRemoveClump(RpWorld *world, RpClump *clump);

/* Makes an empty world of the box (the front end's, sub_1331E0). */
extern RpWorld *RpWorldCreate(RwBBox *boundingBox);

#ifdef    __cplusplus
}
#endif         /* __cplusplus */

#endif
