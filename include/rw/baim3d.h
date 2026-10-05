/*
 * RwIm3DVertex (the D3D8 driver's RxObjSpace3DLitVertex: position, normal,
 * colour, u and v, 0x24 bytes), its setters, and RwIm3DTransform,
 * RwIm3DRenderPrimitive and RwIm3DEnd, copied from RenderWare 3.7.2
 * RWSDK/include/d3d8/rwcore.h. The image's layout agrees: the shadows'
 * sub_1279C0 writes each vertex's colour at +0x18 and its u and v at +0x1C
 * and +0x20.
 */
#ifndef RW_BAIM3D_H
#define RW_BAIM3D_H

#include "rw/batypes.h"
#include "rw/bamatrix.h"
#include "rw/badevice.h"

typedef struct RxObjSpace3DLitVertex RxObjSpace3DLitVertex;
struct RxObjSpace3DLitVertex
{
    RwV3d       objVertex;
    RwV3d       objNormal;
    RwUInt32    color;
    RwReal      u;
    RwReal      v;
};
typedef RxObjSpace3DLitVertex RwIm3DVertex;

#define RxObjSpace3DLitVertexSetU(_vert, _imu) \
    ((_vert)->u = (_imu))
#define RxObjSpace3DLitVertexSetV(_vert, _imv) \
    ((_vert)->v = (_imv))
#define RwIm3DVertexSetU   RxObjSpace3DLitVertexSetU
#define RwIm3DVertexSetV   RxObjSpace3DLitVertexSetV

#define RwIm3DVertexSetPos(_vert, _imx, _imy, _imz) \
MACRO_START \
{ \
    (_vert)->objVertex.x = _imx; \
    (_vert)->objVertex.y = _imy; \
    (_vert)->objVertex.z = _imz; \
} \
MACRO_STOP

#define RwIm3DVertexSetRGBA(_vert, _r, _g, _b, _a) \
MACRO_START \
{ \
    ((_vert)->color = ((_a) << 24) | \
                              ((_r) << 16) | \
                              ((_g) << 8) | \
                              ((_b))); \
} \
MACRO_STOP

enum RwIm3DTransformFlags
{
    rwIM3D_VERTEXUV      = 1,
    rwIM3D_ALLOPAQUE     = 2,
    rwIM3D_NOCLIP        = 4,
    rwIM3D_VERTEXXYZ     = 8,
    rwIM3D_VERTEXRGBA    = 16
};

#ifdef    __cplusplus
extern "C"
{
#endif         /* __cplusplus */

extern void *RwIm3DTransform(RwIm3DVertex *pVerts, RwUInt32 numVerts,
                             RwMatrix *ltm, RwUInt32 flags);
extern RwBool RwIm3DEnd(void);
extern RwBool RwIm3DRenderPrimitive(RwPrimitiveType primType);

#ifdef    __cplusplus
}
#endif         /* __cplusplus */

#endif
