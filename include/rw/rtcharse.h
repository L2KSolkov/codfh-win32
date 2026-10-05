/*
 * RtCharset (RW 3.7.2's rtcharse.h, as the game uses it): a character set
 * is a raster, described by RtCharsetDesc. _rtCharsetAtariFontGet is the
 * toolkit's internal font description (chrprint.h), which the game's debug
 * text (unit_16BA60) reads directly.
 */
#ifndef RW_RTCHARSE_H
#define RW_RTCHARSE_H

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "rw/baraster.h"

typedef struct RtCharsetDesc RtCharsetDesc;
struct RtCharsetDesc
{
    RwInt32 width;
    RwInt32 height;
    RwInt32 width_internal;
    RwInt32 height_internal;
    RwInt32 count;
    RwInt32 tilewidth;
    RwInt32 tileheight;
};

typedef RwRaster RtCharset;

typedef struct RtGlyphRow RtGlyphRow;

extern "C"
{
RtCharset *RtCharsetCreate(const RwRGBA *foreGround, const RwRGBA *backGround);
RwBool RtCharsetDestroy(RtCharset *charSet);
const RtGlyphRow *_rtCharsetAtariFontGet(RtCharsetDesc *desc, RwInt32 *rasSize);
}

#endif
