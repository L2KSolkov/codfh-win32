/*
 * codfh-match: RenderWare 3.6's Xbox driver 2D immediate mode
 * (driver/xbox/xb2drend.c).
 */
#ifndef XB2DREND_H
#define XB2DREND_H

/* The Xbox 2D vertex (the Godfather PDB's rwXBOXVERTEX, its RwIm2DVertex). */
typedef struct _rwXBOXVERTEX rwXBOXVERTEX;
struct _rwXBOXVERTEX
{
    RwReal                  x;
    RwReal                  y;
    RwReal                  z;
    RwReal                  rhw;
    RwUInt32                emissiveColor;
    RwReal                  u;
    RwReal                  v;
};

extern const D3DPRIMITIVETYPE RwXbPrimConvTable[7];

extern RwBool _rwXbIm2DRenderOpen(void);
extern void _rwXbIm2DRenderClose(void);
extern void _rwXbIm2DRenderSetVertexShader(RwBool diffuse, RwBool texcoords);
extern RwBool _rwXbIm2DRenderLine(rwXBOXVERTEX *verts, RwInt32 numVerts,
                                  RwInt32 vert1, RwInt32 vert2);
extern RwBool _rwXbIm2DRenderTriangle(rwXBOXVERTEX *verts, RwInt32 numVerts,
                                      RwInt32 vert1, RwInt32 vert2, RwInt32 vert3);
extern RwBool _rwXbIm2DRenderPrimitive(RwPrimitiveType primType, rwXBOXVERTEX *verts,
                                       RwInt32 numVerts);
extern RwBool _rwXbIm2DRenderIndexedPrimitive(RwPrimitiveType primType,
                                              rwXBOXVERTEX *verts, RwInt32 numVerts,
                                              RwImVertexIndex *indices, RwInt32 numIndices);

#endif /* XB2DREND_H */
