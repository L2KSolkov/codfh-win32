/*
 * RpMesh, RpMeshHeader, RpMeshCallBack and RpGeometryForAllMeshes, copied
 * from RenderWare 3.7.2 RWSDK/include/null/rpworld.h (RxVertexIndex is
 * rwplcore.h's 16-bit index).
 */
#ifndef RW_RPMESH_H
#define RW_RPMESH_H

#include "rw/batypes.h"
#include "rw/rpatomic.h"

typedef RwUInt16 RxVertexIndex;

typedef struct RpMesh RpMesh;
struct RpMesh
{
    RxVertexIndex      *indices;
    RwUInt32            numIndices;
    RpMaterial         *material;
};

typedef struct RpMeshHeader RpMeshHeader;
struct RpMeshHeader
{
    RwUInt32            flags;
    RwUInt16            numMeshes;
    RwUInt16            serialNum;
    RwUInt32            totalIndicesInMesh;
    RwUInt32            firstMeshOffset;
};

/* The header's first mesh, as RW 3.7.2's _rpMeshHeaderForAllMeshes
 * (world/bamesh.c) computes it; a name of ours for that expression. */
#define rpMeshHeaderGetFirstMesh(_header)                                   ((RpMesh *)((RwUInt8 *)((_header) + 1) + (_header)->firstMeshOffset))

typedef RpMesh *(*RpMeshCallBack) (RpMesh * mesh,
                                   RpMeshHeader * meshHeader,
                                   void *pData);

#ifdef    __cplusplus
extern "C"
{
#endif         /* __cplusplus */

extern const RpGeometry *
RpGeometryForAllMeshes(const RpGeometry *geometry,
                       RpMeshCallBack fpCallBack,
                       void *pData);

#ifdef    __cplusplus
}
#endif         /* __cplusplus */

#endif
