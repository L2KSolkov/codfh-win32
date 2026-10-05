/*
 * codfh-match: RenderWare 3.6's Xbox driver DDS textures
 * (driver/xbox/xbdxttex.c), written from the image.
 */
#ifndef XBDXTTEX_H
#define XBDXTTEX_H

extern RwUInt8 _rwXboxDXT1HasAlpha(RwRaster *raster);
extern RwTexture *RwXboxDDSTextureRead(const RwChar *name, const RwChar *maskname);

#endif /* XBDXTTEX_H */
