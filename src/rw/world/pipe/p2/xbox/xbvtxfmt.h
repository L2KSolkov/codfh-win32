/*
 * codfh-match: RenderWare 3.6's Xbox vertex formats
 * (world/pipe/p2/xbox/xbvtxfmt.c); the Godfather PDB's types and names.
 */
#ifndef XBVTXFMT_H
#define XBVTXFMT_H

typedef enum RpXboxCompType RpXboxCompType;
enum RpXboxCompType
{
    rpCOMPTYPENONE = 0,
    rpPACKEDBYTE,
    rpSHORT,
    rpNORMALIZEDSHORTS,
    rpNORMALIZEDPACKED,
    rpFLOAT,
    rpCOMPTYPEMAX,
    rpXBOXCOMPFLAGSFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};

/* A geometry's or world's vertex format: component types per element. */
#pragma pack(push, 1)
typedef struct RpXboxVtxFmt RpXboxVtxFmt;
struct RpXboxVtxFmt
{
    RwUInt8             pos : 4;
    RwUInt8             norm : 4;
    RwUInt16            texCoord;       /* four 4-bit types */
    RwUInt8             prelit : 1;
    RwUInt8             bnt : 3;
    RwUInt8             reserved : 4;
};
#pragma pack(pop)

/* A vertex format and its D3D vertex shader. */
typedef struct _rpXboxVtxFmtDescItem _rpXboxVtxFmtDescItem;
struct _rpXboxVtxFmtDescItem
{
    RpXboxVtxFmt        format;
    DWORD               handle;
};

extern RwModuleInfo RpVtxFmtModule;
extern RwInt32 _rpXboxGeomVtxFmtOffset;
extern RwInt32 rpXboxWorldVtxFmtOffset;
extern const RwUInt32 RpXboxCompSize[rpCOMPTYPEMAX];

extern void rwXboxVertexFormatCreate(void);
extern void rwXboxVertexFormatDestroy(void);
extern RwUInt32 _rpXboxVtxFmtGetSize(RpXboxCompType type, RwUInt32 numElems);
extern RwUInt32 _rpXboxVtxFmtGetStride(const RpXboxVtxFmt *fmt);
extern RwBool _rpXboxVtxFmtInstColor(RwUInt8 *dst, const RwRGBA *src,
                                     RwInt32 numVerts, RwUInt32 stride);
extern RwUInt32 _rpXboxVtxFmtInstV3d(RpXboxCompType type, RwUInt8 *mem, const RwV3d *src,
                                     RwInt32 numVerts, RwUInt32 stride);
extern RwUInt32 _rpXboxVtxFmtInstV3dMorph(RpXboxCompType type, RwUInt8 *mem,
                                          const RwV3d *src1, const RwV3d *src2, RwReal scale,
                                          RwInt32 numVerts, RwUInt32 stride);
extern RwUInt32 _rpXboxVtxFmtInstV2d(RpXboxCompType type, RwUInt8 *mem, const RwTexCoords *src,
                                     RwInt32 numVerts, RwUInt32 stride);
extern RwUInt32 _rpXboxVtxFmtInstBNT(RwUInt8 *mem, const RwV3d *pos, const RwV3d *normal,
                                      const RwTexCoords *texCoord,
                                      struct RxXboxResEntryHeader *instancedHeader,
                                      RwInt32 numVerts, RwUInt32 stride);
extern RwBool _rpXboxDefaultInstance(RpXboxVtxFmt *fmt, RwUInt32 flags,
                                     struct RxXboxResEntryHeader *instancedHeader,
                                     const RwV3d *positions, const RwV3d *normals,
                                     const RpVertexNormal *packedNormals, const RwRGBA *color,
                                     RwInt32 numTexCoordSets, const RwTexCoords **texCoordSets,
                                     RwUInt32 lockedSinceLastInst);
extern RpXboxVtxFmt *RpXboxGeometryGetVtxFmt(RpGeometry *geometry);
extern RpXboxVtxFmt *RpXboxWorldGetVtxFmt(RpWorld *world);
extern DWORD RxXboxGetVertexFormatShader(const RpXboxVtxFmt *fmt);
extern void _rpXboxVtxFmtUnInstV3d(RpXboxCompType type, RwV3d *dst, const RwUInt8 *src);
extern void _rpXboxVtxFmtUnInstV2d(RpXboxCompType type, RwV2d *dst, const RwUInt8 *src);
extern void RpXboxVtxFmtInit(RpXboxVtxFmt *fmt, RwUInt32 flags, RwUInt32 numTexCoordSets);
extern const RwUInt32 rpWorldVSDETexFlags[4];
extern RwBool _rpXboxVtxFmtPluginAttach(void);

#endif /* XBVTXFMT_H */
