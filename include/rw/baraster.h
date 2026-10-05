/*
 * RwRaster, copied from RenderWare 3.7.2 RWSDK/src/baraster.h. The game's
 * font (type_DA580::sub_DBB80) reads a pad texture raster's width (+0xC)
 * and height (+0x10).
 */
#ifndef RW_BARASTER_H
#define RW_BARASTER_H

#include "rw/ostypes.h"
#include "rw/batypes.h"

typedef struct RwRaster RwRaster;
struct RwRaster
{
    RwRaster           *parent; /* Top level raster if a sub raster */
    RwUInt8            *cpPixels; /* Pixel pointer when locked */
    RwUInt8            *palette; /* Raster palette */
    RwInt32             width, height, depth; /* Dimensions of raster */
    RwInt32             stride; /* Lines bytes of raster */
    RwInt16             nOffsetX, nOffsetY; /* Sub raster offset */
    RwUInt8             cType;  /* Type of raster */
    RwUInt8             cFlags; /* Raster flags */
    RwUInt8             privateFlags; /* Raster private flags */
    RwUInt8             cFormat; /* Raster format */

    RwUInt8            *originalPixels;
    RwInt32             originalWidth;
    RwInt32             originalHeight;
    RwInt32             originalStride;
};

enum RwRasterType
{
    rwRASTERTYPENORMAL = 0x00,
    rwRASTERTYPEZBUFFER = 0x01,
    rwRASTERTYPECAMERA = 0x02,
    rwRASTERTYPETEXTURE = 0x04,
    rwRASTERTYPECAMERATEXTURE = 0x05,
    rwRASTERTYPEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwRasterType RwRasterType;

#define RwRasterGetWidth(_raster) ((_raster)->width)
#define RwRasterGetHeight(_raster) ((_raster)->height)

#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

/* Shows the raster (the shell's loading banner, sub_EA560, shows its
 * camera's frame buffer with it). */
extern RwRaster *RwRasterShowRaster(RwRaster *raster, void *dev, RwUInt32 flags);
/* Made and destroyed by RenderWare Studio's camera helper. */
extern RwRaster *RwRasterCreate(RwInt32 width, RwInt32 height, RwInt32 depth, RwInt32 flags);
extern RwBool RwRasterDestroy(RwRaster *raster);
extern RwRaster *RwRasterSubRaster(RwRaster *subRaster, RwRaster *raster, RwRect *rect);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

#endif
