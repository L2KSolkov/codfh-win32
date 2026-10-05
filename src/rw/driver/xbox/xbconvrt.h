/*
 * codfh-match: RenderWare 3.6's Xbox driver pixel conversions (xbconvrt.c).
 */
#ifndef XBCONVRT_H
#define XBCONVRT_H

extern RwInt32 _rwXbFindMSB(RwInt32 num);
extern RwBool _rwXbRGBToPixel(void *pixelOut, void *colIn, RwInt32 format);
extern RwBool _rwXbPixelToRGB(void *rgbOut, void *pixel, RwInt32 format);
extern RwBool _rwXbImageGetFromRaster(void *imageIn, void *rasterIn, RwInt32 unused3);
extern RwImage *_rwXboxPalettizeImage(RwImage *srcImage, RwInt32 depth);
extern RwBool _rwXbRasterSetFromImage(void *rasterIn, void *imageIn, RwInt32 unused3);

extern RwBool _rwXbImageFindRasterFormat(void *rasterIn, void *imageIn, RwInt32 flags);

#endif /* XBCONVRT_H */
