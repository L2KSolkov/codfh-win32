/*
 * codfh-match: RenderWare 3.6's Xbox driver raster rendering and clearing
 * (driver/xbox/xbsprite.c).
 */
#ifndef XBSPRITE_H
#define XBSPRITE_H

extern RwBool _rwXbRasterRender(void *rasterIn, void *rectIn, RwInt32 flags);
extern RwBool _rwXbRasterRenderFast(void *rasterIn, void *rectIn, RwInt32 flags);
extern RwBool _rwXbRasterRenderScaled(void *rasterIn, void *rectIn, RwInt32 flags);
extern RwBool _rwXbRasterClearGeneric(RwRect *rect, RwInt32 packedColor);
extern RwBool _rwXbRasterClearRect(void *unused1, void *rectIn, RwInt32 packedColor);
extern RwBool _rwXbRasterClear(void *unused1, void *unused2, RwInt32 packedColor);
extern RwBool _rwXbSetRasterContext(void *unused1, void *rasIn, RwInt32 unused3);

#endif /* XBSPRITE_H */
