/*
 * codfh-match: RenderWare 3.6's Xbox driver pixel conversions (driver/xbox),
 * which the 3.7.2 tree does not have. Written from the image, with the
 * structure of the 3.7.2 d3d8 driver's d3d8convrt.c; the names are the
 * image's.
 */

#include <xtl.h>

#include "batypes.h"
#include "balibtyp.h"
#include "badebug.h"
#include "baraster.h"

#include "baimage.h"
#include "xbconvrt.h"
#include "xbraster.h"

#include "palquant.h"
#include <string.h>

/* RenderWare 3.6's RCS id string, which the image keeps (the 3.7.2 tree has none) */
static const char rcsid[] = "@@@@(#)$Id: //RenderWare/RW36Active/rwsdk/driver/xbox/xbconvrt.c#1 $";

typedef RwUInt32 (*XbPixConvertFn)(RwRGBA *colIn);
typedef void (*XbPixUnconvertFn)(RwRGBA *pixOut, RwUInt32 pixIn);

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: _rcsid @ 0x00416EA0
// match: ??_C@_0EH@EFINHCBP@Conversion?5from?5non?5palettised?5r@ @ 0x00416EE8
// match: ??_C@_0DI@OGNBGFBB@Conversion?5from?5rasters?5to?54bit?5@ @ 0x00416F30
// match: ??_C@_0DF@IHGHJFBA@Conversion?5from?5compressed?5raste@ @ 0x00416F68
// match: ??_C@_0DD@MEIOGGLH@Conversion?5to?5compressed?5rasters@ @ 0x00416FA0

// match: __rwXbFindMSB @ 0x002B7750
// sp-match: __rwXbFindMSB @ 0x001D2B70

RwInt32
_rwXbFindMSB(RwInt32 num)
{
    RwInt32 pos = -1;

    while (num)
    {
        pos++;
        num >>= 1;
    }

    return pos;
}

// match: _rwXbConvR8G8B8A8ToR5G5B5 @ 0x002B7770
// sp-match: _rwXbConvR8G8B8A8ToR5G5B5 @ 0x001D2B90
static RwUInt32
rwXbConvR8G8B8A8ToR5G5B5(RwRGBA *pixIn)
{
    RwUInt32    pixOut;

    pixOut = (0x00000000) |
             (((RwUInt32)pixIn->red << 7) & 0x7C00) |
             (((RwUInt32)pixIn->green << 2) & 0x03E0) |
             (((RwUInt32)pixIn->blue >> 3) & 0x001F);

    return pixOut;
}

// match: _XbConvR8G8B8A8ToR5G6B5 @ 0x002B77A0
// sp-match: _XbConvR8G8B8A8ToR5G6B5 @ 0x001D2BC0
static RwUInt32
XbConvR8G8B8A8ToR5G6B5(RwRGBA *pixIn)
{
    RwUInt32    pixOut;

    pixOut = (((RwUInt32)pixIn->red << 8) & 0xF800) |
             (((RwUInt32)pixIn->green << 3) & 0x07E0) |
             ((RwUInt32)pixIn->blue >> 3);

    return pixOut;
}

// match: _XbConvR8G8B8A8ToA1R5G5B5 @ 0x002B77D0
// sp-match: _XbConvR8G8B8A8ToA1R5G5B5 @ 0x001D2BF0
static RwUInt32
XbConvR8G8B8A8ToA1R5G5B5(RwRGBA *pixIn)
{
    RwUInt32    pixOut;

    pixOut = (((RwUInt32)pixIn->alpha << 8) & 0x8000) |
             (((RwUInt32)pixIn->red << 7) & 0x7C00) |
             (((RwUInt32)pixIn->green << 2) & 0x03E0) |
             ((RwUInt32)pixIn->blue >> 3);

    return pixOut;
}

// match: _XbConvR8G8B8A8ToA4R4G4B4 @ 0x002B7810
// sp-match: _XbConvR8G8B8A8ToA4R4G4B4 @ 0x001D2C30
static RwUInt32
XbConvR8G8B8A8ToA4R4G4B4(RwRGBA *pixIn)
{
    RwUInt32    pixOut;

    pixOut = (((RwUInt32)pixIn->alpha << 8) & 0xF000) |
             (((RwUInt32)pixIn->red << 4) & 0x0F00) |
             (((RwUInt32)pixIn->green) & 0x00F0) |
             ((RwUInt32)pixIn->blue >> 4);

    return pixOut;
}

// match: _XbConvR8G8B8A8ToX8R8G8B8 @ 0x002B7850
// sp-match: _XbConvR8G8B8A8ToX8R8G8B8 @ 0x001D2C70
static RwUInt32
XbConvR8G8B8A8ToX8R8G8B8(RwRGBA *pixIn)
{
    RwUInt32    pixOut;

    pixOut = (((RwUInt32)0xFF << 24) & 0xFF000000) |
             (((RwUInt32)pixIn->red << 16) & 0x00FF0000) |
             (((RwUInt32)pixIn->green << 8) & 0x0000FF00) |
             ((RwUInt32)pixIn->blue);

    return pixOut;
}

// match: _XbConvR8G8B8A8ToA8R8G8B8 @ 0x002B7870
// sp-match: _XbConvR8G8B8A8ToA8R8G8B8 @ 0x001D2C90
static RwUInt32
XbConvR8G8B8A8ToA8R8G8B8(RwRGBA *pixIn)
{
    RwUInt32    pixOut;

    pixOut = (((RwUInt32)pixIn->alpha << 24) & 0xFF000000) |
             (((RwUInt32)pixIn->red << 16) & 0x00FF0000) |
             (((RwUInt32)pixIn->green << 8) & 0x0000FF00) |
             ((RwUInt32)pixIn->blue);

    return pixOut;
}

/* 3.6: no alpha scaling (3.7.2's scales the luminance by the alpha). */
// match: _XbConvR8G8B8A8ToL8 @ 0x002B7890
// sp-match: _XbConvR8G8B8A8ToL8 @ 0x001D2CB0
static RwUInt32
XbConvR8G8B8A8ToL8(RwRGBA *pixIn)
{
    RwUInt32    pixOut;

    pixOut = ((pixIn->red * 30 +
               pixIn->green * 59 +
               pixIn->blue * 11) / 100);

    return pixOut;
}

// match: __rwXbRGBToPixel @ 0x002B78C0
// sp-match: __rwXbRGBToPixel @ 0x001D2CE0
RwBool
_rwXbRGBToPixel(void *pixelOut, void *colIn, RwInt32 format)
{
    RwRGBA  *rgba = (RwRGBA *)colIn;
    RwInt32 pixVal;

    switch (format & rwRASTERFORMATPIXELFORMATMASK)
    {
        case rwRASTERFORMATDEFAULT:
        {
            /* Default is 8888 */
            if (!_rwXbRGBToPixel(&pixVal, colIn, rwRASTERFORMAT8888))
            {
                return FALSE;
            }
            break;
        }

        case rwRASTERFORMAT555:
            pixVal = rwXbConvR8G8B8A8ToR5G5B5(rgba);
            break;

        case rwRASTERFORMAT1555:
            pixVal = XbConvR8G8B8A8ToA1R5G5B5(rgba);
            break;

        case rwRASTERFORMAT565:
            pixVal = XbConvR8G8B8A8ToR5G6B5(rgba);
            break;

        case rwRASTERFORMAT4444:
            pixVal = XbConvR8G8B8A8ToA4R4G4B4(rgba);
            break;

        case rwRASTERFORMATLUM8:
            pixVal = XbConvR8G8B8A8ToL8(rgba);
            break;

        case rwRASTERFORMAT8888:
            pixVal = XbConvR8G8B8A8ToA8R8G8B8(rgba);
            break;

        case rwRASTERFORMAT888:
            pixVal = XbConvR8G8B8A8ToX8R8G8B8(rgba);
            break;

        default:
        {
            RWERROR((E_RW_INVRASTERFORMAT));
            return FALSE;
        }
    }

    *(RwInt32 *)pixelOut = pixVal;

    return TRUE;
}

// match: _XbConvR5G5B5ToR8G8B8A8 @ 0x002B7A80
// sp-match: _XbConvR5G5B5ToR8G8B8A8 @ 0x001D2EA0
static void
XbConvR5G5B5ToR8G8B8A8(RwRGBA *pixOut, RwUInt32 pixIn)
{
    
    pixOut->alpha = 0xFF;
    pixOut->red   = (RwUInt8)((pixIn >> 7) & 0xF8);
    pixOut->green = (RwUInt8)((pixIn >> 2) & 0xF8);
    pixOut->blue  = (RwUInt8)((pixIn << 3) & 0xF8);

    return;
}

/****************************************************************************
 XbConvR5G6B5ToR8G8B8A8

 On entry : A pointer to a RwRGBA that is the unpacked pixel value.
 On exit  : A RwUInt32 representing the packed pixel value.
 */
// match: _XbConvR5G6B5ToR8G8B8A8 @ 0x002B7AB0
// sp-match: _XbConvR5G6B5ToR8G8B8A8 @ 0x001D2ED0
static void
XbConvR5G6B5ToR8G8B8A8(RwRGBA *pixOut, RwUInt32 pixIn)
{
    
    pixOut->alpha = 0xFF;
    pixOut->red   = (RwUInt8)((pixIn >> 8) & 0xF8);
    pixOut->green = (RwUInt8)((pixIn >> 3) & 0xFC);
    pixOut->blue  = (RwUInt8)((pixIn << 3) & 0xF8);

    return;
}

/****************************************************************************
 XbConvA1R5G5B5ToR8G8B8A8

 On entry : A pointer to a RwRGBA that is the unpacked pixel value.
 On exit  : A RwUInt32 representing the packed pixel value.
 */
// match: _XbConvA1R5G5B5ToR8G8B8A8 @ 0x002B7AE0
// sp-match: _XbConvA1R5G5B5ToR8G8B8A8 @ 0x001D2F00
static void
XbConvA1R5G5B5ToR8G8B8A8(RwRGBA *pixOut, RwUInt32 pixIn)
{
    
    if (pixIn & 0x8000)
    {
        pixOut->alpha = 0xFF;
    }
    else
    {
        pixOut->alpha = 0x00;
    }

    pixOut->red   = (RwUInt8)((pixIn >> 7) & 0xF8);
    pixOut->green = (RwUInt8)((pixIn >> 2) & 0xF8);
    pixOut->blue  = (RwUInt8)((pixIn << 3) & 0xF8);

    return;
}

/****************************************************************************
 XbConvA4R4G4B4ToR8G8B8A8

 On entry : A pointer to a RwRGBA that is the unpacked pixel value.
 On exit  : A RwUInt32 representing the packed pixel value.
 */
// match: _XbConvA4R4G4B4ToR8G8B8A8 @ 0x002B7B20
// sp-match: _XbConvA4R4G4B4ToR8G8B8A8 @ 0x001D2F40
static void
XbConvA4R4G4B4ToR8G8B8A8(RwRGBA *pixOut, RwUInt32 pixIn)
{
    
    /* 3.6: no special case for full alpha */
    pixOut->alpha = (RwUInt8)((pixIn >> 8) & 0xF0);

    pixOut->red   = (RwUInt8)((pixIn >> 4) & 0xF0);
    pixOut->green = (RwUInt8)((pixIn >> 0) & 0xF0);
    pixOut->blue  = (RwUInt8)((pixIn << 4) & 0xF0);

    return;
}

/****************************************************************************
 XbConvX8R8G8B8ToR8G8B8A8

 On entry : A pointer to a RwRGBA that is the unpacked pixel value.
 On exit  : A RwUInt32 representing the packed pixel value.
 */
// match: _XbConvX8R8G8B8ToR8G8B8A8 @ 0x002B7B50
// sp-match: _XbConvX8R8G8B8ToR8G8B8A8 @ 0x001D2F70
static void
XbConvX8R8G8B8ToR8G8B8A8(RwRGBA *pixOut, RwUInt32 pixIn)
{
        
    pixOut->red   = (RwUInt8)((pixIn >> 16) & 0xFF);
    pixOut->green = (RwUInt8)((pixIn >> 8) & 0xFF);
    pixOut->blue  = (RwUInt8)((pixIn) & 0xFF);
    pixOut->alpha = 0xFF;

    return;
}

/****************************************************************************
 XbConvA8R8G8B8ToR8G8B8A8

 On entry : A pointer to a RwRGBA that is the unpacked pixel value.
 On exit  : A RwUInt32 representing the packed pixel value.
 */
// match: _XbConvA8R8G8B8ToR8G8B8A8 @ 0x002B7B70
// sp-match: _XbConvA8R8G8B8ToR8G8B8A8 @ 0x001D2F90
static void
XbConvA8R8G8B8ToR8G8B8A8(RwRGBA *pixOut, RwUInt32 pixIn)
{
        
    pixOut->alpha = (RwUInt8)((pixIn >> 24) & 0xFF);
    pixOut->red   = (RwUInt8)((pixIn >> 16) & 0xFF);
    pixOut->green = (RwUInt8)((pixIn >> 8) & 0xFF);
    pixOut->blue  = (RwUInt8)((pixIn) & 0xFF);
    

    return;
}

/****************************************************************************
 XbConvL8ToR8G8B8A8

 On entry : A pointer to a RwRGBA that is the unpacked pixel value.
 On exit  : A RwUInt32 representing the packed pixel value.
 */
// match: _XbConvL8ToR8G8B8A8 @ 0x002B7BA0
// sp-match: _XbConvL8ToR8G8B8A8 @ 0x001D2FC0
static void
XbConvL8ToR8G8B8A8(RwRGBA *pixOut, RwUInt32 pixIn)
{
        
    pixOut->alpha = 0xFF;
    pixOut->red   = (RwUInt8)(pixIn & 0xFF);
    pixOut->green = (RwUInt8)(pixIn & 0xFF);
    pixOut->blue  = (RwUInt8)(pixIn & 0xFF);
    

    return;
}

/*****************************************************************************
 _rwXbPixelToRGB

 Convert device specific colour to RwRGBA

 On entry   : rgbOut - RwRGBA out
            : pixel - Pixel in
            : Pixel format
 On exit    : TRUE on success
 */
// match: __rwXbPixelToRGB @ 0x002B7BC0
// sp-match: __rwXbPixelToRGB @ 0x001D2FE0
RwBool
_rwXbPixelToRGB(void *rgbOut, void *pixel, RwInt32 format)
{
    RwRGBA  *rgba = (RwRGBA *)rgbOut;

    
    if (format & rwRASTERFORMATPAL8)
    {
        *rgba = *((RwRGBA *)pixel);
    }
    else
    {
        switch (format & rwRASTERFORMATPIXELFORMATMASK)
        {
            case rwRASTERFORMATDEFAULT:
                if (!_rwXbPixelToRGB(rgba, pixel, rwRASTERFORMAT8888))
                {
                    return (FALSE);
                }
                break;

            case rwRASTERFORMAT555:
                XbConvR5G5B5ToR8G8B8A8(rgba, *(RwInt32 *)pixel);
                break;

            case rwRASTERFORMAT1555:
                XbConvA1R5G5B5ToR8G8B8A8(rgba, *(RwInt32 *)pixel);
                break;

            case rwRASTERFORMAT565:
                XbConvR5G6B5ToR8G8B8A8(rgba, *(RwInt32 *)pixel);
                break;

            case rwRASTERFORMAT4444:
                XbConvA4R4G4B4ToR8G8B8A8(rgba, *(RwInt32 *)pixel);
                break;

            case rwRASTERFORMATLUM8:
                XbConvL8ToR8G8B8A8(rgba, *(RwInt32 *)pixel);
                break;

            case rwRASTERFORMAT8888:
                XbConvA8R8G8B8ToR8G8B8A8(rgba, *(RwInt32 *)pixel);
                break;

            case rwRASTERFORMAT888:
                XbConvX8R8G8B8ToR8G8B8A8(rgba, *(RwInt32 *)pixel);
                break;

            default:
            {
                RWERROR((E_RW_INVRASTERFORMAT));
                return (FALSE);
            }
        }
    }

    return (TRUE);
}


/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*
 *                                                                           *
 *                      - Raster to image conversion -                       *
 *                                                                           *
 *!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

/*****************************************************************************
 XbSelectUnconvertFn

 On entry :
 On exit  :
 */
// match: _XbSelectUnconvertFn @ 0x002B7D50
// sp-match: _XbSelectUnconvertFn @ 0x001D3170
static XbPixUnconvertFn
XbSelectUnconvertFn(RwRasterFormat format)
{
    XbPixUnconvertFn    result = NULL;

    switch (format & rwRASTERFORMATPIXELFORMATMASK)
    {
        case rwRASTERFORMAT555:
            result = XbConvR5G5B5ToR8G8B8A8;
            break;

        case rwRASTERFORMAT565:
            result = XbConvR5G6B5ToR8G8B8A8;
            break;

        case rwRASTERFORMAT1555:
            result = XbConvA1R5G5B5ToR8G8B8A8;
            break;

        case rwRASTERFORMAT4444:
            result = XbConvA4R4G4B4ToR8G8B8A8;
            break;

        case rwRASTERFORMATLUM8:
            result = XbConvL8ToR8G8B8A8;
            break;

        case rwRASTERFORMAT888:
            result = XbConvX8R8G8B8ToR8G8B8A8;
            break;

        case rwRASTERFORMAT8888:
        case rwRASTERFORMAT32:
            result = XbConvA8R8G8B8ToR8G8B8A8;
            break;

        default:
            RWERROR((E_RW_INVRASTERFORMAT));
            break;
    }

    return (result);
}


/*****************************************************************************
 XbImage32GetFromRaster
 */
// match: _XbImage32GetFromRaster @ 0x002B7E10
// sp-match: _XbImage32GetFromRaster @ 0x001D3230
static void
XbImage32GetFromRaster(RwImage *image, RwRaster *raster)
{
    RwInt32         format;

    switch (RwRasterGetDepth(raster))
    {
        case 4:
        case 8:
            format = RwRasterGetFormat(raster);
            if (format & (rwRASTERFORMATPAL4 | rwRASTERFORMATPAL8))
            {
                const RwUInt32 *palette = (const RwUInt32 *)raster->palette;
                RwInt32         j;

                for (j = 0; j < raster->height; j++)
                {
                    const RwUInt8  *srcPixel = raster->cpPixels + raster->stride * j;
                    RwRGBA         *dstPixel = (RwRGBA *)(image->cpPixels + image->stride * j);
                    RwInt32         i;

                    for (i = 0; i < raster->width; i++)
                    {
                        RwUInt32        color = palette[*srcPixel];

                        dstPixel->alpha = (RwUInt8)(color >> 24);
                        dstPixel->red = (RwUInt8)(color >> 16);
                        dstPixel->green = (RwUInt8)(color >> 8);
                        dstPixel->blue = (RwUInt8)color;

                        dstPixel++;
                        srcPixel++;
                    }
                }
            }
            else if (format & rwRASTERFORMATLUM8)
            {
                RwInt32         j;

                for (j = 0; j < raster->height; j++)
                {
                    const RwUInt8  *srcPixel = raster->cpPixels + raster->stride * j;
                    RwRGBA         *dstPixel = (RwRGBA *)(image->cpPixels + image->stride * j);
                    RwInt32         i;

                    for (i = 0; i < raster->width; i++)
                    {
                        RwUInt8         grey = *srcPixel;

                        dstPixel->alpha = 0xFF;
                        dstPixel->blue = grey;
                        dstPixel->green = grey;
                        dstPixel->red = grey;

                        dstPixel++;
                        srcPixel++;
                    }
                }
            }
            break;

        case 16:
            {
                XbPixUnconvertFn unconvert = XbSelectUnconvertFn(RwRasterGetFormat(raster));
                RwInt32         j;

                for (j = 0; j < raster->height; j++)
                {
                    const RwUInt16 *srcPixel = (const RwUInt16 *)(raster->cpPixels + raster->stride * j);
                    RwRGBA         *dstPixel = (RwRGBA *)(image->cpPixels + image->stride * j);
                    RwInt32         i;

                    for (i = 0; i < raster->width; i++)
                    {
                        unconvert(dstPixel, *srcPixel);

                        dstPixel++;
                        srcPixel++;
                    }
                }
            }
            break;

        case 24:
        case 32:
            {
                XbPixUnconvertFn unconvert = XbSelectUnconvertFn(RwRasterGetFormat(raster));
                RwInt32         j;

                for (j = 0; j < raster->height; j++)
                {
                    const RwUInt32 *srcPixel = (const RwUInt32 *)(raster->cpPixels + raster->stride * j);
                    RwRGBA         *dstPixel = (RwRGBA *)(image->cpPixels + image->stride * j);
                    RwInt32         i;

                    for (i = 0; i < raster->width; i++)
                    {
                        unconvert(dstPixel, *srcPixel);

                        dstPixel++;
                        srcPixel++;
                    }
                }
            }
            break;

        default:
            RWERROR((E_RW_INVRASTERDEPTH));
            break;
    }
}

/*****************************************************************************
 rwXbImage8GetFromRaster
 */
// match: _rwXbImage8GetFromRaster @ 0x002B8060
// sp-match: _rwXbImage8GetFromRaster @ 0x001D3480
static void
rwXbImage8GetFromRaster(RwImage *image, RwRaster *raster)
{
    switch (RwRasterGetDepth(raster))
    {
        case 8:
            {
                RwInt32         y;

                if (image->stride == raster->stride && raster->width == raster->stride)
                {
                    memcpy(image->cpPixels, raster->cpPixels, raster->height * raster->width);
                }
                else
                {
                    for (y = 0; y < raster->height; y++)
                    {
                        memcpy(image->cpPixels + (image->stride * y),
                               raster->cpPixels + (raster->stride * y),
                               raster->width);
                    }
                }

                if (raster->palette)
                {
                    /* The raster's palette is BGRA */
                    for (y = 0; y < 256; y++)
                    {
                        image->palette[y].red = ((const RwRGBA *)raster->palette)[y].blue;
                        image->palette[y].green = ((const RwRGBA *)raster->palette)[y].green;
                        image->palette[y].blue = ((const RwRGBA *)raster->palette)[y].red;
                        image->palette[y].alpha = ((const RwRGBA *)raster->palette)[y].alpha;
                    }
                }
                else
                {
                    for (y = 0; y < 256; y++)
                    {
                        image->palette[y].red = y;
                        image->palette[y].green = y;
                        image->palette[y].blue = y;
                        image->palette[y].alpha = 0xff;
                    }
                }
            }
            break;

        case 16:
        case 24:
        case 32:
            RWERROR((E_RW_DEVICEERROR,
                     RWSTRING("Conversion from non palettised rasters to 8bit images is not supported")));
            break;

        default:
            RWERROR((E_RW_INVRASTERDEPTH));
            break;
    }
}

// match: __rwXbImageGetFromRaster @ 0x002B82A0
// sp-match: __rwXbImageGetFromRaster @ 0x001D36C0
RwBool
_rwXbImageGetFromRaster(void *imageIn, void *rasterIn, RwInt32 unused3)
{
    RwImage        *image = (RwImage *)imageIn;
    RwRaster       *raster = (RwRaster *)rasterIn;
    RwBool          rasterLocked = FALSE;
    RwBool          paletteLocked = FALSE;
    const RwXboxRasterExtension *rasExt;

    /* Check if raster is compressed and fail */
    rasExt = RASTEREXTFROMRASTER(RwRasterGetParent(raster));
    if (rasExt->dxtFormat)
    {
        RWERROR((E_RW_DEVICEERROR,
                 RWSTRING("Conversion from compressed rasters is not supported.")));
        return FALSE;
    }

    /* Lock the raster if it isn't already locked */
    if (!(raster->privateFlags & rwRASTERPIXELLOCKEDREAD))
    {
        RwRasterLock(raster, 0, rwRASTERLOCKREAD);
        rasterLocked = TRUE;
    }

    /* If the raster is palletized then lock the palette */
    if (RwRasterGetFormat(raster) & (rwRASTERFORMATPAL4 | rwRASTERFORMATPAL8))
    {
        if (!(raster->privateFlags & rwRASTERPALETTELOCKEDREAD))
        {
            RwRasterLockPalette(raster, rwRASTERLOCKREAD);
            paletteLocked = TRUE;
        }
    }

    if (32 == RwImageGetDepth(image))
    {
        XbImage32GetFromRaster(image, raster);
    }
    else if (8 == RwImageGetDepth(image))
    {
        rwXbImage8GetFromRaster(image, raster);
    }
    else
    {
        RWERROR((E_RW_DEVICEERROR,
                 RWSTRING("Conversion from rasters to 4bit images is not supported")));
    }

    if (TRUE == paletteLocked)
    {
        RwRasterUnlockPalette(raster);
    }

    if (TRUE == rasterLocked)
    {
        RwRasterUnlock(raster);
    }

    return TRUE;
}

/*****************************************************************************
 XbSelectConvertFn
 */
// match: _XbSelectConvertFn @ 0x002B83A0
// sp-match: _XbSelectConvertFn @ 0x001D37C0
static XbPixConvertFn
XbSelectConvertFn(RwRasterFormat format)
{
    XbPixConvertFn  result = NULL;

    switch (format & rwRASTERFORMATPIXELFORMATMASK)
    {
        case rwRASTERFORMAT555:
            result = rwXbConvR8G8B8A8ToR5G5B5;
            break;

        case rwRASTERFORMAT565:
            result = XbConvR8G8B8A8ToR5G6B5;
            break;

        case rwRASTERFORMAT1555:
            result = XbConvR8G8B8A8ToA1R5G5B5;
            break;

        case rwRASTERFORMAT4444:
            result = XbConvR8G8B8A8ToA4R4G4B4;
            break;

        case rwRASTERFORMATLUM8:
            result = XbConvR8G8B8A8ToL8;
            break;

        case rwRASTERFORMAT888:
            result = XbConvR8G8B8A8ToX8R8G8B8;
            break;

        case rwRASTERFORMAT8888:
            result = XbConvR8G8B8A8ToA8R8G8B8;
            break;

        default:
            RWERROR((E_RW_INVRASTERFORMAT));
            break;
    }

    return result;
}

// match: __rwXboxPalettizeImage @ 0x002B8450
// sp-match: __rwXboxPalettizeImage @ 0x001D3870
RwImage *
_rwXboxPalettizeImage(RwImage *srcImage, RwInt32 depth)
{
    RwPalQuant      palQuant;
    RwImage        *palImage;

    palImage = RwImageCreate(RwImageGetWidth(srcImage),
                             RwImageGetHeight(srcImage),
                             depth);
    if (!palImage)
    {
        return NULL;
    }

    RwImageAllocatePixels(palImage);

    if (!RwPalQuantInit(&palQuant))
    {
        return NULL;
    }

    RwPalQuantAddImage(&palQuant, srcImage, 1.0f);
    RwPalQuantResolvePalette(RwImageGetPalette(palImage), (1UL << depth), &palQuant);

    RwPalQuantMatchImage(RwImageGetPixels(palImage),
                         RwImageGetStride(palImage),
                         RwImageGetDepth(palImage),
                         FALSE,
                         &palQuant,
                         srcImage);

    RwPalQuantTerm(&palQuant);

    return palImage;
}

/*****************************************************************************
 XbRasterLum8SetFromImage
 */
// match: _XbRasterLum8SetFromImage @ 0x002B8500
// sp-match: _XbRasterLum8SetFromImage @ 0x001D3920
static void
XbRasterLum8SetFromImage(RwRaster *raster, RwImage *image)
{
    RwInt32         y;

    for (y = 0; y < raster->height; y++)
    {
        const RwUInt8  *srcPixel = image->cpPixels + image->stride * y;
        RwUInt8        *dstPixel = raster->cpPixels + raster->stride * y;
        RwInt32         x;

        for (x = 0; x < raster->width; x++)
        {
            *dstPixel = *srcPixel;
            srcPixel++;
            dstPixel++;
        }
    }
}

/*****************************************************************************
 XbRasterPalletizedSetFromImage
 */
// match: _XbRasterPalletizedSetFromImage @ 0x002B8550
// sp-match: _XbRasterPalletizedSetFromImage @ 0x001D3970
static void
XbRasterPalletizedSetFromImage(RwRaster *raster, RwImage *image)
{
    if (image->depth != 4 && image->depth != 8)
    {
        RwImage        *palImage;

        palImage = _rwXboxPalettizeImage(image, RwRasterGetDepth(raster));
        if (palImage)
        {
            XbRasterPalletizedSetFromImage(raster, palImage);
            RwImageDestroy(palImage);
        }
    }
    else
    {
        const RwXboxRasterExtension *rasExt = RASTEREXTFROMRASTER(RwRasterGetParent(raster));
        RwInt32         y;

        for (y = 0; y < raster->height; y++)
        {
            const RwUInt8  *srcPixel = image->cpPixels + image->stride * y;
            RwUInt8        *dstPixel = raster->cpPixels + raster->stride * y;
            RwInt32         x;

            for (x = 0; x < raster->width; x++)
            {
                *dstPixel = *srcPixel;
            srcPixel++;
            dstPixel++;
            }
        }

        /* The palette only with the top level */
        if (rasExt->lockedMipLevel == 0)
        {
            RwUInt32       *palette = (RwUInt32 *)raster->palette;
            const RwRGBA   *srcPal = image->palette;
            RwInt32         i;

            for (i = 0; i < (1 << image->depth); i++)
            {
                *palette = ((RwUInt32)srcPal->alpha << 24) |
                           ((RwUInt32)srcPal->red << 16) |
                           ((RwUInt32)srcPal->green << 8) |
                           (RwUInt32)srcPal->blue;
                palette++;
                srcPal++;
            }
        }
    }
}

/*****************************************************************************
 XbRaster16SetFromImage
 */
// match: _XbRaster16SetFromImage @ 0x002B8650
// sp-match: _XbRaster16SetFromImage @ 0x001D3A70
static void
XbRaster16SetFromImage(RwRaster *raster, RwImage *image)
{
    XbPixConvertFn  convert = XbSelectConvertFn(RwRasterGetFormat(raster));
    RwInt32         y;

    switch (image->depth)
    {
        case 32:
            for (y = 0; y < raster->height; y++)
            {
                const RwRGBA   *srcPixel = (const RwRGBA *)(image->cpPixels + image->stride * y);
                RwUInt16       *dstPixel = (RwUInt16 *)(raster->cpPixels + raster->stride * y);
                RwInt32         x;

                for (x = 0; x < raster->width; x++)
                {
                    *dstPixel = (RwUInt16)convert((RwRGBA *)srcPixel);
                    dstPixel++;
                    srcPixel++;
                }
            }
            break;

        case 4:
        case 8:
            for (y = 0; y < raster->height; y++)
            {
                const RwUInt8  *srcPixel = image->cpPixels + image->stride * y;
                RwUInt16       *dstPixel = (RwUInt16 *)(raster->cpPixels + raster->stride * y);
                RwInt32         x;

                for (x = 0; x < raster->width; x++)
                {
                    *dstPixel = (RwUInt16)convert(&image->palette[*srcPixel]);
                    dstPixel++;
                    srcPixel++;
                }
            }
            break;
    }
}

/*****************************************************************************
 XbRaster24_32SetFromImage
 */
// match: _XbRaster24_32SetFromImage @ 0x002B8750
// sp-match: _XbRaster24_32SetFromImage @ 0x001D3B70
static void
XbRaster24_32SetFromImage(RwRaster *raster, RwImage *image)
{
    XbPixConvertFn  convert = XbSelectConvertFn(RwRasterGetFormat(raster));
    RwInt32         y;

    switch (image->depth)
    {
        case 32:
            for (y = 0; y < raster->height; y++)
            {
                const RwRGBA   *srcPixel = (const RwRGBA *)(image->cpPixels + image->stride * y);
                RwUInt32       *dstPixel = (RwUInt32 *)(raster->cpPixels + raster->stride * y);
                RwInt32         x;

                for (x = 0; x < raster->width; x++)
                {
                    *dstPixel = convert((RwRGBA *)srcPixel);
                    srcPixel++;
                    dstPixel++;
                }
            }
            break;

        case 4:
        case 8:
            for (y = 0; y < raster->height; y++)
            {
                const RwUInt8  *srcPixel = image->cpPixels + image->stride * y;
                RwUInt32       *dstPixel = (RwUInt32 *)(raster->cpPixels + raster->stride * y);
                RwInt32         x;

                for (x = 0; x < raster->width; x++)
                {
                    *dstPixel = convert(&image->palette[srcPixel[x]]);
                    dstPixel++;
                }
            }
            break;
    }
}

// match: __rwXbRasterSetFromImage @ 0x002B8850
// sp-match: __rwXbRasterSetFromImage @ 0x001D3C70
RwBool
_rwXbRasterSetFromImage(void *rasterIn, void *imageIn, RwInt32 unused3)
{
    RwRaster       *raster = (RwRaster *)rasterIn;
    RwImage        *image = (RwImage *)imageIn;
    RwBool          rasterLocked = FALSE;
    RwBool          paletteLocked = FALSE;
    RwInt32         format;
    RwInt32         palettized;

    if (RASTEREXTFROMRASTER(RwRasterGetParent(raster))->dxtFormat)
    {
        RWERROR((E_RW_DEVICEERROR,
                 RWSTRING("Conversion to compressed rasters is not supported.")));
        return FALSE;
    }

    format = RwRasterGetFormat(raster);

    if (raster->privateFlags & rwRASTERPIXELLOCKEDWRITE)
    {
        rasterLocked = TRUE;
    }
    else if (!RwRasterLock(raster, 0, rwRASTERLOCKWRITE | rwRASTERLOCKNOFETCH))
    {
        return FALSE;
    }

    palettized = format & (rwRASTERFORMATPAL4 | rwRASTERFORMATPAL8);
    if (palettized)
    {
        if (raster->privateFlags & rwRASTERPALETTELOCKEDWRITE)
        {
            paletteLocked = TRUE;
        }
        else if (!RwRasterLockPalette(raster, rwRASTERLOCKWRITE | rwRASTERLOCKNOFETCH))
        {
            return FALSE;
        }
    }

    switch (RwRasterGetDepth(raster))
    {
        case 4:
        case 8:
            if (format & (rwRASTERFORMATPAL4 | rwRASTERFORMATPAL8))
            {
                XbRasterPalletizedSetFromImage(raster, image);
            }
            else if (format & rwRASTERFORMATLUM8)
            {
                XbRasterLum8SetFromImage(raster, image);
            }
            break;

        case 16:
            XbRaster16SetFromImage(raster, image);
            break;

        case 24:
        case 32:
            XbRaster24_32SetFromImage(raster, image);
            break;

        default:
            RWERROR((E_RW_INVRASTERDEPTH));
            break;
    }

    if (palettized && !paletteLocked)
    {
        RwRasterUnlockPalette(raster);
    }

    if (!rasterLocked)
    {
        RwRasterUnlock(raster);
    }

    return TRUE;
}

/* The raster format an image converts to: palettised or not, with alpha if
   any pixel is not opaque. */
// match: _XbImageFindFormat @ 0x002B89D0
// sp-match: _XbImageFindFormat @ 0x001D3DF0
static RwUInt32
XbImageFindFormat(RwImage *image)
{
    RwInt32         depth;
    RwUInt32        format;

    depth = RwImageGetDepth(image);

    if ((depth == 4) || (depth == 8))
    {
        RwInt32         width;
        RwInt32         height;
        RwUInt8        *cpIn;
        RwRGBA         *rpPal;
        RwInt32         y;

        width = RwImageGetWidth(image);
        height = RwImageGetHeight(image);
        cpIn = image->cpPixels;
        rpPal = image->palette;

        for (y = 0; y < height; y++)
        {
            RwUInt8        *cpInCur = cpIn;
            RwInt32         x;

            for (x = 0; x < width; x++)
            {
                if (rpPal[*cpInCur].alpha != 0xFF)
                {
                    if (depth == 4)
                    {
                        format = rwRASTERFORMATPAL4 | rwRASTERFORMAT8888;
                    }
                    else
                    {
                        format = rwRASTERFORMATPAL8 | rwRASTERFORMAT8888;
                    }

                    return format;
                }

                cpInCur++;
            }

            cpIn += RwImageGetStride(image);
        }

        if (depth == 4)
        {
            format = rwRASTERFORMATPAL4 | rwRASTERFORMAT888;
        }
        else
        {
            format = rwRASTERFORMATPAL8 | rwRASTERFORMAT888;
        }
    }
    else
    {
        RwInt32         width;
        RwInt32         height;
        RwUInt8        *cpIn;
        RwInt32         y;

        width = RwImageGetWidth(image);
        height = RwImageGetHeight(image);
        cpIn = image->cpPixels;

        for (y = 0; y < height; y++)
        {
            RwRGBA         *rpInCur = (RwRGBA *)cpIn;
            RwInt32         x;

            for (x = 0; x < width; x++)
            {
                if (rpInCur->alpha != 0xFF)
                {
                    format = rwRASTERFORMAT8888;

                    return format;
                }

                rpInCur++;
            }

            cpIn += RwImageGetStride(image);
        }

        format = rwRASTERFORMAT888;
    }

    return format;
}

// match: __rwXbImageFindRasterFormat @ 0x002B8AC0
// sp-match: __rwXbImageFindRasterFormat @ 0x001D3EE0
RwBool
_rwXbImageFindRasterFormat(void *rasterIn, void *imageIn, RwInt32 flags)
{
    RwRaster       *raster;
    RwImage        *image;
    RwUInt32        format;

    raster = (RwRaster *)rasterIn;
    image = (RwImage *)imageIn;

    raster->width = image->width;
    raster->height = image->height;
    raster->depth = 0;

    if (!_rwXbGetRasterFormat(raster, flags))
    {
        return FALSE;
    }

    switch (raster->cType)
    {
        case rwRASTERTYPENORMAL:
            raster->width = (raster->width > 4096) ? 4096 : raster->width;
            raster->height = (raster->height > 4096) ? 4096 : raster->height;

            format = XbImageFindFormat(image);

            raster->cFormat = (RwUInt8)((format |
                (flags & ~(rwRASTERFORMATMIPMAP | rwRASTERFORMATAUTOMIPMAP))) >> 8);
            return TRUE;

        case rwRASTERTYPEZBUFFER:
        case rwRASTERTYPECAMERA:
            return TRUE;

        case rwRASTERTYPETEXTURE:
        case rwRASTERTYPECAMERATEXTURE:
            raster->width = (raster->width > 4096) ? 4096 : raster->width;
            raster->height = (raster->height > 4096) ? 4096 : raster->height;

            /* Textures are powers of two */
            raster->width = 1 << _rwXbFindMSB(raster->width);
            raster->height = 1 << _rwXbFindMSB(raster->height);

            format = XbImageFindFormat(image) |
                (flags & (rwRASTERFORMATMIPMAP | rwRASTERFORMATAUTOMIPMAP));

            raster->cFormat = (RwUInt8)(format >> 8);
            return TRUE;

        default:
            RWERROR((E_RW_INVRASTERFORMAT));
            return FALSE;
    }
}
