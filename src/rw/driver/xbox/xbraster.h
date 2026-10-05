/*
 * codfh-match: RenderWare 3.6's Xbox driver rasters (driver/xbox), written
 * from the image (xbraster.c).
 */
#ifndef XBRASTER_H
#define XBRASTER_H

/* The raster extension (RwRasterRegisterPlugin's 0x18 bytes); the names
   are the Godfather PDB's. */
typedef struct RwXboxRasterExtension RwXboxRasterExtension;
struct RwXboxRasterExtension
{
    D3DBaseTexture         *texture;        /* its D3D texture */
    D3DPalette             *palette;        /* its D3D palette, if palettised */
    void                   *lockedBuffer;   /* a linear copy while locked */
    void                   *lockedBits;     /* the locked level's bits */
    RwUInt8                 lockedMipLevel;
    RwUInt8                 dxtFormat;      /* 0, or the DXT format (D3DFMT_DXT1 = 0x0C) */
    RwUInt8                 alpha;          /* the texture has alpha */
    RwUInt8                 numMipLevels;   /* its mip levels */
    RwUInt8                 cube;           /* a cube texture */
    RwUInt8                 face;           /* the cube face */
    RwInt8                  mipmapLODBias;
    RwUInt8                 reservedByte;
};

#define RASTEREXTFROMRASTER(raster)     ((RwXboxRasterExtension *)(((RwUInt8 *)(raster)) + _RwXbRasterExtOffset))

extern RwInt32 _RwXbRasterExtOffset;

extern RwBool _rwXbRasterPluginAttach(void);
extern RwBool _rwXbRasterOpen(void);
extern void _rwXbRasterClose(void);
extern RwUInt32 _rwXbRasterGetSize(RwRaster *raster, RwUInt8 mipLevel);
extern RwBool _rwXbRasterGetMipLevels(void *mipLevels, void *ras, RwInt32 unused3);
extern RwBool _rwXbTextureSetRaster(void *tex, void *ras, RwInt32 unused3);
extern RwBool _rwXbRasterSubRaster(void *rasterIn, void *parentRasterIn, RwInt32 unused3);
extern RwBool _rwXbGetRasterFormat(RwRaster *raster, RwInt32 flags);
extern RwBool _rwXbRasterCreate(void *unused1, void *rasterIn, RwInt32 flags);
extern RwBool _rwXbRasterDestroy(void *unused1, void *rasterIn, RwInt32 unused3);
extern RwBool _rwXbRasterLock(void *pixelsIn, void *rasterIn, RwInt32 accessMode);
extern RwBool _rwXbRasterUnlock(void *unused1, void *rasterIn, RwInt32 unused3);
extern RwBool _rwXbRasterLockPalette(void *paletteInOut, void *rasterIn, RwInt32 accessMode);
extern RwBool _rwXbRasterUnlockPalette(void *unused1, void *rasterIn, RwInt32 unused3);
extern RwBool _rwXbRasterNativeCreate(RwRaster *raster, D3DFORMAT format, RwInt32 mipmapLevels);
extern RwBool _rwXbCubeRasterNativeCreate(RwRaster *raster, D3DFORMAT format, RwInt32 mipmapLevels);

#endif /* XBRASTER_H */
