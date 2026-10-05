/*
 * RwImageSetPath, RwImage, its accessors' macro forms, RwImageCreate,
 * RwImageDestroy and RwRasterSetFromImage, copied from RenderWare 3.7.2
 * RWSDK/src/plcore/baimage.h. The spline resource handler (0x1304B0) sets
 * the image path to the resource's before reading; kujuUI's textures
 * (unit_1EECE0) build an image over their pixels and a raster from it.
 */
#ifndef RW_BAIMAGE_H
#define RW_BAIMAGE_H

#include "rw/ostypes.h"
#include "rw/baraster.h"

typedef struct RwImage RwImage;
struct RwImage
{
    RwInt32             flags;
    RwInt32             width;  /* Device may have different ideas */
    RwInt32             height; /* internally !! */
    RwInt32             depth;  /* Of referenced image */
    RwInt32             stride;
    RwUInt8            *cpPixels;
    void               *palette;
};

#define RwImageSetStrideMacro(_image, _stride) ((_image)->stride = (_stride), (_image))
#define RwImageSetPixelsMacro(_image, _pixels) ((_image)->cpPixels = (_pixels), (_image))
#define RwImageGetWidthMacro(_image) ((_image)->width)
#define RwImageGetHeightMacro(_image) ((_image)->height)
#define RwImageSetStride(_image, _stride) RwImageSetStrideMacro(_image, _stride)
#define RwImageSetPixels(_image, _pixels) RwImageSetPixelsMacro(_image, _pixels)
#define RwImageGetWidth(_image) RwImageGetWidthMacro(_image)
#define RwImageGetHeight(_image) RwImageGetHeightMacro(_image)

#ifdef    __cplusplus
extern "C"
{
#endif

extern const RwChar *RwImageSetPath(const RwChar * path);
extern RwImage *RwImageCreate(RwInt32 width, RwInt32 height, RwInt32 depth);
extern RwBool RwImageDestroy(RwImage * image);
extern RwRaster *RwRasterSetFromImage(RwRaster *raster, RwImage *image);

#ifdef    __cplusplus
}
#endif

#endif
