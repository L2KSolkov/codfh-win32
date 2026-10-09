/*
 * The intersection types, RpCollisionTriangle, the world triangle and sector
 * callback types, and the world, sector and atomic queries, copied from
 * RenderWare 3.7.2
 * RWSDK/include/null/rpcollis.h (with the world, sector and
 * atomic kept opaque), and the collision tree, its bounding-box iterators
 * (with their completion macros) and RtIntersectionBBoxTriangle from
 * rpcollis.h's ctdata.h and ctquery.h and rtintsec.h. The image's layout
 * agrees: AIData::sub_2CE90 stores the type at +0x18 of its RpIntersection,
 * after the line, and the shadows' sub_1283E0 keeps the iterators' 65- and
 * 33-entry stacks (rpWORLDMAXBSPDEPTH 64, rpCOLLTREE_MAXDEPTH 32).
 */
#ifndef RW_RPCOLLIS_H
#define RW_RPCOLLIS_H

#include "rw/batypes.h"

typedef struct RpWorld RpWorld;
typedef struct RpWorldSector RpWorldSector;
typedef struct RpAtomic RpAtomic;

enum RpIntersectType
{
    rpINTERSECTNONE = 0,
    rpINTERSECTLINE,   /**<Line Intersection */
    rpINTERSECTPOINT,  /**<Point Intersection */
    rpINTERSECTSPHERE, /**<Sphere Intersection */
    rpINTERSECTBOX,    /**<Box intersection */
    rpINTERSECTATOMIC, /**<Atomic Intersection based on bounding sphere */
    rpINTERSECTTYPEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RpIntersectType RpIntersectType;

typedef union RpIntersectData RpIntersectData;
union RpIntersectData
{
    RwLine              line;       /**<For type rpINTERSECTLINE */
    RwV3d               point;      /**<For type rpINTERSECTPOINT */
    RwSphere            sphere;     /**<For type rpINTERSECTSPHERE */
    RwBBox              box;        /**<For type rpINTERSECTBOX */
    void               *object;     /**<For type rpINTERSECTATOMIC - this
                                     * should hold a pointer to the atomic */
};

struct RpIntersection
{
    RpIntersectData     t; /**< Intersection data. Union type - one
                            * of line, point, sphere or RW object */
    RpIntersectType     type; /**< Intersection type - see
                               * \ref RpIntersectType */
};
typedef struct RpIntersection RpIntersection;

typedef RpAtomic   *(*RpIntersectionCallBackAtomic)
    (RpIntersection * intersection,
     RpWorldSector * sector, RpAtomic * atomic, RwReal distance, void *data);

typedef struct RpCollisionTriangle RpCollisionTriangle;
struct RpCollisionTriangle
{
    RwV3d   normal;     /**< Triangle normal */
    RwV3d   point;      /**< First triangle vertex */
    RwInt32 index;      /**< Index of triangle in object (if applicable) */
    RwV3d  *vertices[3]; /**< Pointers to three triangle vertices */
};

typedef RpCollisionTriangle *(*RpIntersectionCallBackWorldTriangle)
    (RpIntersection * intersection,
     RpWorldSector * sector,
     RpCollisionTriangle * collTriangle, RwReal distance, void *data);

typedef RpCollisionTriangle *(*RpIntersectionCallBackGeometryTriangle)
    (RpIntersection *intersection, RpCollisionTriangle *collTriangle,
     RwReal distance, void *data);

typedef RpWorldSector *(*RpIntersectionCallBackWorldSector)
    (RpIntersection * intersection, RpWorldSector * worldSector, void *data);

#ifdef    __cplusplus
extern "C"
{
#endif         /* __cplusplus */

extern RpWorld *
RpCollisionWorldForAllIntersections(RpWorld * world,
                                    RpIntersection * intersection,
                                    RpIntersectionCallBackWorldTriangle callBack,
                                    void *data);

extern RpWorld *
RpWorldForAllWorldSectorIntersections(RpWorld * world,
                                      RpIntersection * intersection,
                                      RpIntersectionCallBackWorldSector callBack,
                                      void *data);

extern RpWorld *
RpWorldForAllAtomicIntersections(
    RpWorld                 *world,
    RpIntersection          *intersection,
    RpIntersectionCallBackAtomic callBack,
    void                    *data);

extern RpAtomic *
RpAtomicForAllIntersections(RpAtomic *atomic,
                            RpIntersection *intersection,
                            RpIntersectionCallBackGeometryTriangle callBack,
                            void *data);

#ifdef    __cplusplus
}
#endif         /* __cplusplus */


/* The collision tree (ctdata.h). */
typedef struct RpCollSector RpCollSector;
struct RpCollSector
{
    RwUInt8         type;
    RwUInt8         contents;
    RwUInt16        index;
    RwReal          value;
};

typedef struct RpCollSplit RpCollSplit;
struct RpCollSplit
{
    RpCollSector    leftSector;
    RpCollSector    rightSector;
};

typedef struct RpCollTree RpCollTree;
struct RpCollTree
{
    RwUInt32        flags;
    RwBBox          bbox;
    RwUInt16        numEntries;
    RwUInt16        numSplits;
    RpCollSplit    *splits;
    RwUInt16       *map;
};
#define RpCollTreeGetEntryMapMacro(_tree)  ((_tree)->map)
#define RpCollTreeGetEntryMap(_tree)  RpCollTreeGetEntryMapMacro(_tree)

/* A world sector's collision tree (colldata.h), through the plugin offset
 * the image keeps at 0x509890 (config/aliases.txt). */
typedef struct RpCollisionData RpCollisionData;
struct RpCollisionData
{
    RpCollTree  *tree;
};
#ifdef    __cplusplus
extern "C" RwInt32 _rpCollisionWorldSectorDataOffset;
#else
extern RwInt32 _rpCollisionWorldSectorDataOffset;
#endif
#define _rpCollisionWorldSectorGetDataMacro(_sector)     RWPLUGINOFFSET(RpCollisionData, _sector, _rpCollisionWorldSectorDataOffset)
#define RpCollisionWorldSectorGetCollTree(_sector)     (_rpCollisionWorldSectorGetDataMacro(_sector)->tree)

/* The bounding-box iterators (ctquery.h). */
typedef struct RpSector RpSector;

typedef struct RpSectorBBoxItNodeInfo RpSectorBBoxItNodeInfo;
struct RpSectorBBoxItNodeInfo
{
    RpSector   *sector;
};

typedef struct RpSectorBBoxIt RpSectorBBoxIt;
struct RpSectorBBoxIt
{
    RwBBox                  bbox;
    RpSectorBBoxItNodeInfo  stack[64 + 1];
    RpSectorBBoxItNodeInfo *curr;
};

typedef struct RpCollSectorBBoxItNodeInfo RpCollSectorBBoxItNodeInfo;
struct RpCollSectorBBoxItNodeInfo
{
    RpCollSector   *sector;
    RwUInt32        clipFlags;
};

typedef struct RpCollSectorBBoxIt RpCollSectorBBoxIt;
struct RpCollSectorBBoxIt
{
    RpCollTree                 *tree;
    RwBBox                      bbox;
    RwBBox                      clipBBox;
    RpCollSector                dummy;
    RpCollSectorBBoxItNodeInfo  stack[32 + 1];
    RpCollSectorBBoxItNodeInfo *curr;
};

/* The line iterators (ctquery.h): a node stack of 65 (world) or 33 (collision
 * tree) entries of a sector and its span, the stack top after it. The game's
 * world line test (sub_91F40) keeps them at those sizes: the tops sit 0x30C
 * and 0x18C bytes past the stacks. The fields before the stacks (the line
 * and its clipping) are not established; words, since byte arrays would give
 * the test a /GS cookie. */
typedef struct RpSectorLineItNodeInfo RpSectorLineItNodeInfo;
struct RpSectorLineItNodeInfo
{
    RpSector   *sector;
    RwReal      unk_04;
    RwReal      unk_08;
};

typedef struct RpSectorLineIt RpSectorLineIt;
struct RpSectorLineIt
{
    RwUInt32                unk_00[9];
    RpSectorLineItNodeInfo  stack[64 + 1];
    RpSectorLineItNodeInfo *curr;
#ifndef CODFH_SP // single player's iterator ends at curr: sub_91F40 reads it at the top of its frame (SP 0x73EA0)
    RwUInt32                unk_334;
#endif
};

typedef struct RpCollSectorLineItNodeInfo RpCollSectorLineItNodeInfo;
struct RpCollSectorLineItNodeInfo
{
    RpCollSector   *sector;
    RwReal          unk_04;
    RwReal          unk_08;
};

typedef struct RpCollSectorLineIt RpCollSectorLineIt;
struct RpCollSectorLineIt
{
    RwUInt32                    unk_00[12];
    RpCollSectorLineItNodeInfo  stack[32 + 1];
    RpCollSectorLineItNodeInfo *curr;
};

#define _rpSectorLineItFinishedMacro(_it)     ((_it)->curr <= (_it)->stack)
#define _rpCollSectorLineItFinishedMacro(_it) ((_it)->curr <= (_it)->stack)
#define RpSectorLineItFinished(_it)     _rpSectorLineItFinishedMacro(_it)
#define RpCollSectorLineItFinished(_it) _rpCollSectorLineItFinishedMacro(_it)

#define _rpSectorBBoxItFinishedMacro(_it)     ((_it)->curr <= (_it)->stack)
#define _rpCollSectorBBoxItFinishedMacro(_it) ((_it)->curr <= (_it)->stack)
#define RpSectorBBoxItFinished(_it)     _rpSectorBBoxItFinishedMacro(_it)
#define RpCollSectorBBoxItFinished(_it) _rpCollSectorBBoxItFinishedMacro(_it)

#ifdef    __cplusplus
extern "C"
{
#endif         /* __cplusplus */

extern void
RpSectorBBoxItInit(RpSectorBBoxIt *it, RpWorld *world, RwBBox *bbox);
extern RpWorldSector *
RpSectorBBoxItFindNextWorldSector(RpSectorBBoxIt *it);
extern void
RpCollSectorBBoxItInit(RpCollSectorBBoxIt *it, RpCollTree *tree, RwBBox *outerBBox,
                       RwBBox *innerBBox);
extern void
RpCollSectorBBoxItFindNextEntries(RpCollSectorBBoxIt *it, RwUInt16 *start, RwUInt16 *count,
                                  RwUInt32 *clipFlags);
extern void
RpSectorLineItInit(RpSectorLineIt *it, RpWorld *world, RwLine *line);
extern RpWorldSector *
RpSectorLineItFindNextWorldSector(RpSectorLineIt *it);
extern void
RpSectorLineItSetFarClip(RpSectorLineIt *it, RwReal value);
extern void
RpCollSectorLineItInit(RpCollSectorLineIt *it, RpCollTree *tree, RwLine *line);
extern void
RpCollSectorLineItFindNextEntries(RpCollSectorLineIt *it, RwUInt16 *start, RwUInt16 *count);
extern void
RpCollSectorLineItSetFarClip(RpCollSectorLineIt *it, RwReal value);
extern RwBool
RtIntersectionBBoxTriangle(const RwBBox *bbox, const RwV3d *v0, const RwV3d *v1,
                           const RwV3d *v2);

#ifdef    __cplusplus
}
#endif         /* __cplusplus */

#endif
