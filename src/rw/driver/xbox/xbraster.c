/*
 * codfh-match: RenderWare 3.6's Xbox driver rasters (driver/xbox), which the
 * 3.7.2 tree does not have. Written from the image; the names are the
 * image's (the database took them from the library), the layout of the
 * raster extension only as far as the recovered functions use it.
 */

#include <xtl.h>
#include <xgraphics.h>

#include "batypes.h"
#include "balibtyp.h"
#include "bamemory.h"
#include "baraster.h"
#include "batextur.h"
#include "badebug.h"

#include "xbraster.h"
#include "xbconvrt.h"
#include "xbdevice.h"
#include "xbmemory.h"
#include "xbcache.h"
#include "xbrendst.h"

/* RenderWare 3.6's RCS id string, which the image keeps (the 3.7.2 tree has none) */
static const char rcsid[] = "@@@@(#)$Id: //RenderWare/RW36Active/rwsdk/driver/xbox/xbraster.c#3 $";

/* The raster extension's offset in RwRaster. */
RwInt32 _RwXbRasterExtOffset;

/* The free lists of the textures' and palettes' D3D resource headers. */
static RwFreeList *TextureHeaderFreeList = NULL;
static RwFreeList *PaletteHeaderFreeList = NULL;

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: _rcsid @ 0x004165A0
// match: ??_C@_0BK@CJHGOENE@Failed?5to?5create?5surface?4?$AA@ @ 0x004165E8
// match: ??_C@_0BK@DMLBAFCJ@Failed?5to?5create?5palette?4?$AA@ @ 0x00416604
// match: ??_C@_0CI@JCNFMCNJ@Failed?5to?5create?5depth?5stencil?5s@ @ 0x00416620
// match: ??_C@_0CH@JCNOEHJL@The?5minimun?5pitch?5for?5a?5ZBuffer?5@ @ 0x00416648
// match: ??_C@_0CO@FKBNPEPN@The?5minimun?5pitch?5for?5a?5camera?5t@ @ 0x00416670
// match: __rwRasterConvTable @ 0x00435518
// match: _zRasterConvTab @ 0x004355C8

// match: __rwXbRasterPluginAttach @ 0x002AC710

RwBool
_rwXbRasterPluginAttach(void)
{
    _RwXbRasterExtOffset =
        RwRasterRegisterPlugin(sizeof(RwXboxRasterExtension),
                               rwID_DEVICEMODULE,
                               NULL,
                               NULL,
                               NULL);

    if (0 > _RwXbRasterExtOffset)
    {
        return FALSE;
    }

    return TRUE;
}

// match: __rwXbRasterOpen @ 0x002AC740
RwBool
_rwXbRasterOpen(void)
{
    if (TextureHeaderFreeList == NULL)
    {
        TextureHeaderFreeList =
            RwFreeListCreate(sizeof(D3DTexture), 204, 4,
                             rwID_DRIVERMODULE | rwMEMHINTDUR_GLOBAL);
    }

    if (PaletteHeaderFreeList == NULL)
    {
        PaletteHeaderFreeList =
            RwFreeListCreate(sizeof(D3DPalette), 341, 4,
                             rwID_DRIVERMODULE | rwMEMHINTDUR_GLOBAL);
    }

    if (TextureHeaderFreeList != NULL && PaletteHeaderFreeList != NULL)
    {
        return TRUE;
    }

    return FALSE;
}

// match: __rwXbRasterClose @ 0x002AC7A0
void
_rwXbRasterClose(void)
{
    if (PaletteHeaderFreeList != NULL)
    {
        RwFreeListDestroy(PaletteHeaderFreeList);
        PaletteHeaderFreeList = NULL;
    }

    if (TextureHeaderFreeList != NULL)
    {
        RwFreeListDestroy(TextureHeaderFreeList);
        TextureHeaderFreeList = NULL;
    }
}

/* Locks mip level mipLevel of the (cube) texture of rasExt. */
// match: _XbRasterLockMipLevel @ 0x002AC7E0
static void
XbRasterLockMipLevel(RwRaster *raster, RwXboxRasterExtension *rasExt,
                     RwUInt8 mipLevel, RwUInt8 **pixels, RwInt32 *pitch,
                     RwUInt32 flags)
{
    D3DLOCKED_RECT  lockedRect;

    if (rasExt->cube)
    {
        D3DCubeTexture_LockRect((D3DCubeTexture *)rasExt->texture,
                                (D3DCUBEMAP_FACES)rasExt->face, mipLevel,
                                &lockedRect, NULL, flags);
    }
    else
    {
        D3DTexture_LockRect((D3DTexture *)rasExt->texture, mipLevel,
                            &lockedRect, NULL, flags);
    }

    *pixels = (RwUInt8 *)lockedRect.pBits;
    *pitch = lockedRect.Pitch;
}

// match: __rwXbRasterLock @ 0x002AC830
RwBool
_rwXbRasterLock(void *pixelsIn, void *rasterIn, RwInt32 accessMode)
{
    RwUInt8               **pixels;
    RwRaster               *raster;
    RwRaster               *parentRaster;
    RwUInt32                lockFlags;
    RwUInt8                 mipLevel;
    RwXboxRasterExtension  *rasExt;
    RwUInt8                *lockedPixels;
    RwInt32                 pitch;

    pixels = (RwUInt8 **)pixelsIn;
    raster = (RwRaster *)rasterIn;
    parentRaster = raster->parent;
    lockFlags = 0;

    /* The mip level is in the access mode's second byte */
    mipLevel = (RwUInt8)((accessMode & 0xFF00) >> 8);

    rasExt = RASTEREXTFROMRASTER(parentRaster);

    switch (raster->cType & rwRASTERTYPEMASK)
    {
        case rwRASTERTYPENORMAL:
            if (!(accessMode & rwRASTERLOCKWRITE))
            {
                lockFlags |= D3DLOCK_READONLY | D3DLOCK_NOOVERWRITE;
            }

            XbRasterLockMipLevel(raster, rasExt, mipLevel, &lockedPixels,
                                 &pitch, lockFlags);

            rasExt->lockedBits = lockedPixels;
            raster->stride = pitch;
            raster->cpPixels = (RwUInt8 *)rasExt->lockedBits +
                pitch * raster->nOffsetY +
                raster->nOffsetX * (pitch / parentRaster->width);

            rasExt->lockedMipLevel = mipLevel;

            if (accessMode & rwRASTERLOCKREAD)
            {
                raster->privateFlags |= rwRASTERPIXELLOCKEDREAD;
                parentRaster->privateFlags |= rwRASTERPIXELLOCKEDREAD;
            }

            if (accessMode & rwRASTERLOCKWRITE)
            {
                raster->privateFlags |= rwRASTERPIXELLOCKEDWRITE;
                parentRaster->privateFlags |= rwRASTERPIXELLOCKEDWRITE;
            }
            break;

        case rwRASTERTYPETEXTURE:
        case rwRASTERTYPECAMERATEXTURE:
            {
                RwInt32         width;
                RwInt32         height;

                if (!(accessMode & rwRASTERLOCKWRITE))
                {
                    lockFlags |= D3DLOCK_READONLY;

                    if ((raster->cType & rwRASTERTYPEMASK) != rwRASTERTYPECAMERATEXTURE)
                    {
                        lockFlags |= D3DLOCK_NOOVERWRITE;
                    }
                }

                XbRasterLockMipLevel(raster, rasExt, mipLevel, &lockedPixels,
                                     &pitch, lockFlags);

                width = parentRaster->width >> mipLevel;
                height = parentRaster->height >> mipLevel;
                width = width ? width : 1;
                height = height ? height : 1;

                if (!rasExt->dxtFormat && !(accessMode & rwRASTERLOCKRAW))
                {
                    rasExt->lockedBuffer =
                        RwMalloc(height * pitch,
                                 rwID_DRIVERMODULE | rwMEMHINTDUR_EVENT);
                    if (!rasExt->lockedBuffer)
                    {
                        return FALSE;
                    }
                }

                if (parentRaster == raster)
                {
                    raster->originalWidth = raster->width;
                    raster->originalHeight = raster->height;
                    raster->width = width;
                    raster->height = height;

                    if (rasExt->dxtFormat || (accessMode & rwRASTERLOCKRAW))
                    {
                        raster->cpPixels = lockedPixels;
                    }
                    else
                    {
                        raster->cpPixels = (RwUInt8 *)rasExt->lockedBuffer;
                    }
                }
                else
                {
                    if (rasExt->dxtFormat || (accessMode & rwRASTERLOCKRAW))
                    {
                        RWERROR((E_RW_INVRASTERLOCKREQ));
                        return FALSE;
                    }

                    raster->cpPixels = (RwUInt8 *)rasExt->lockedBuffer +
                        pitch * raster->nOffsetY +
                        raster->nOffsetX * (pitch / parentRaster->width);
                }

                rasExt->lockedBits = lockedPixels;
                raster->stride = pitch;
                rasExt->lockedMipLevel = mipLevel;

                if (accessMode & rwRASTERLOCKREAD)
                {
                    raster->privateFlags |= rwRASTERPIXELLOCKEDREAD;
                    parentRaster->privateFlags |= rwRASTERPIXELLOCKEDREAD;

                    if (!rasExt->dxtFormat && !(accessMode & rwRASTERLOCKRAW))
                    {
                        XGUnswizzleRect(rasExt->lockedBits, width, height, NULL,
                                        rasExt->lockedBuffer, 0, NULL,
                                        raster->depth / 8);
                    }
                }

                if (accessMode & rwRASTERLOCKWRITE)
                {
                    raster->privateFlags |= rwRASTERPIXELLOCKEDWRITE;
                    parentRaster->privateFlags |= rwRASTERPIXELLOCKEDWRITE;
                }

                if (accessMode & rwRASTERLOCKRAW)
                {
                    raster->privateFlags |= rwRASTERPIXELLOCKEDRAW;
                    parentRaster->privateFlags |= rwRASTERPIXELLOCKEDRAW;
                }
            }
            break;

        case rwRASTERTYPEZBUFFER:
        case rwRASTERTYPECAMERA:
            {
                D3DLOCKED_RECT  lockedRect;

                if (rasExt->texture == (D3DBaseTexture *)_RwXbDeviceGlobals.stencilSurface ||
                    rasExt->texture == (D3DBaseTexture *)_RwXbDeviceGlobals.renderSurface)
                {
                    lockFlags |= D3DLOCK_TILED;
                }

                if (accessMode & rwRASTERLOCKREAD)
                {
                    raster->privateFlags |= rwRASTERPIXELLOCKEDREAD;
                    parentRaster->privateFlags |= rwRASTERPIXELLOCKEDREAD;

                    if (!(accessMode & rwRASTERLOCKWRITE))
                    {
                        lockFlags |= D3DLOCK_READONLY;
                    }
                }

                if (accessMode & rwRASTERLOCKWRITE)
                {
                    raster->privateFlags |= rwRASTERPIXELLOCKEDWRITE;
                    parentRaster->privateFlags |= rwRASTERPIXELLOCKEDWRITE;
                }

                D3DSurface_LockRect((D3DSurface *)rasExt->texture, &lockedRect,
                                    NULL, lockFlags);

                rasExt->lockedBits = lockedRect.pBits;
                raster->cpPixels = (RwUInt8 *)rasExt->lockedBits +
                    raster->nOffsetY * lockedRect.Pitch +
                    (lockedRect.Pitch / parentRaster->width) * raster->nOffsetX;
                raster->stride = lockedRect.Pitch;
            }
            break;

        default:
            RWERROR((E_RW_INVRASTERLOCKREQ));
            return FALSE;
    }

    *pixels = raster->cpPixels;

    return TRUE;
}

// match: __rwXbRasterUnlock @ 0x002ACBA0
RwBool
_rwXbRasterUnlock(void *unused1, void *rasterIn, RwInt32 unused3)
{
    RwRaster               *raster;
    RwRaster               *parentRaster;
    RwXboxRasterExtension  *rasExt;

    raster = (RwRaster *)rasterIn;
    parentRaster = raster->parent;
    rasExt = RASTEREXTFROMRASTER(parentRaster);

    switch (raster->cType & rwRASTERTYPEMASK)
    {
        case rwRASTERTYPENORMAL:
            D3DTexture_UnlockRect((D3DTexture *)rasExt->texture, rasExt->lockedMipLevel);

            raster->stride = 0;
            raster->cpPixels = NULL;

            rasExt->lockedMipLevel = (RwUInt8)-1;

            raster->privateFlags &= ~rwRASTERPIXELLOCKED;
            parentRaster->privateFlags &= ~rwRASTERPIXELLOCKED;
            break;

        case rwRASTERTYPETEXTURE:
        case rwRASTERTYPECAMERATEXTURE:
            if (parentRaster == raster)
            {
                raster->width = raster->originalWidth;
                raster->height = raster->originalHeight;
            }

            if ((raster->privateFlags & rwRASTERPIXELLOCKEDWRITE) &&
                !rasExt->dxtFormat &&
                !(raster->privateFlags & rwRASTERPIXELLOCKEDRAW))
            {
                RwInt32         width;
                RwInt32         height;

                width = parentRaster->width >> rasExt->lockedMipLevel;
                height = parentRaster->height >> rasExt->lockedMipLevel;
                width = width ? width : 1;
                height = height ? height : 1;

                XGSwizzleRect(rasExt->lockedBuffer, 0, NULL, rasExt->lockedBits,
                              width, height, NULL, raster->depth / 8);
            }

            if (!rasExt->dxtFormat && !(raster->privateFlags & rwRASTERPIXELLOCKEDRAW))
            {
                RwFree(rasExt->lockedBuffer);
                rasExt->lockedBuffer = NULL;
            }

            D3DTexture_UnlockRect((D3DTexture *)rasExt->texture, rasExt->lockedMipLevel);

            raster->stride = 0;
            raster->cpPixels = NULL;

            if ((raster->privateFlags & rwRASTERPIXELLOCKEDWRITE) &&
                (raster->cFormat & (rwRASTERFORMATAUTOMIPMAP >> 8)) &&
                rasExt->lockedMipLevel == 0)
            {
                rasExt->lockedMipLevel = (RwUInt8)-1;

                raster->privateFlags &= ~(rwRASTERPIXELLOCKED | rwRASTERPIXELLOCKEDRAW);
                parentRaster->privateFlags &= ~(rwRASTERPIXELLOCKED | rwRASTERPIXELLOCKEDRAW);

                RwTextureRasterGenerateMipmaps(raster, NULL);
            }
            else
            {
                rasExt->lockedMipLevel = (RwUInt8)-1;

                raster->privateFlags &= ~(rwRASTERPIXELLOCKED | rwRASTERPIXELLOCKEDRAW);
                parentRaster->privateFlags &= ~(rwRASTERPIXELLOCKED | rwRASTERPIXELLOCKEDRAW);
            }
            break;

        case rwRASTERTYPEZBUFFER:
        case rwRASTERTYPECAMERA:
            D3DSurface_UnlockRect((D3DSurface *)rasExt->texture);

            rasExt->lockedBits = NULL;

            raster->stride = 0;
            raster->cpPixels = NULL;

            rasExt->lockedMipLevel = (RwUInt8)-1;

            raster->privateFlags &= ~rwRASTERPIXELLOCKED;
            parentRaster->privateFlags &= ~rwRASTERPIXELLOCKED;
            break;

        default:
            RWERROR((E_RW_INVRASTERUNLOCKREQ));
            return FALSE;
    }

    return TRUE;
}

// match: __rwXbRasterLockPalette @ 0x002ACD20
RwBool
_rwXbRasterLockPalette(void *paletteInOut, void *rasterIn, RwInt32 accessMode)
{
    RwRaster               *raster;
    RwUInt32                lockFlags;
    RwXboxRasterExtension  *rasExt;

    raster = (RwRaster *)rasterIn;

    /* Only palettised rasters and textures have palettes */
    switch (raster->cType & rwRASTERTYPEMASK)
    {
        case rwRASTERTYPENORMAL:
        case rwRASTERTYPETEXTURE:
        case rwRASTERTYPECAMERATEXTURE:
            break;

        default:
            RWERROR((E_RW_INVRASTERLOCKREQ));
            return FALSE;
    }

    lockFlags = 0;

    if (accessMode & rwRASTERLOCKREAD)
    {
        raster->privateFlags |= rwRASTERPALETTELOCKEDREAD;
        lockFlags |= D3DLOCK_READONLY;
    }

    if (accessMode & rwRASTERLOCKWRITE)
    {
        raster->privateFlags |= rwRASTERPALETTELOCKEDWRITE;
        lockFlags &= ~D3DLOCK_READONLY;
    }

    rasExt = RASTEREXTFROMRASTER(raster);

    D3DPalette_Lock(rasExt->palette, (D3DCOLOR **)&raster->palette, lockFlags);

    *(RwUInt8 **)paletteInOut = raster->palette;

    return TRUE;
}

// match: __rwXbRasterUnlockPalette @ 0x002ACDB0
RwBool
_rwXbRasterUnlockPalette(void *unused1, void *rasterIn, RwInt32 unused3)
{
    RwRaster               *raster;
    RwXboxRasterExtension  *rasExt;

    raster = (RwRaster *)rasterIn;

    /* Only palettised rasters and textures have palettes */
    switch (raster->cType & rwRASTERTYPEMASK)
    {
        case rwRASTERTYPENORMAL:
        case rwRASTERTYPETEXTURE:
        case rwRASTERTYPECAMERATEXTURE:
            break;

        default:
            RWERROR((E_RW_INVRASTERUNLOCKREQ));
            return FALSE;
    }

    rasExt = RASTEREXTFROMRASTER(raster);

    D3DPalette_Unlock(rasExt->palette);

    raster->palette = NULL;
    raster->privateFlags &= ~rwRASTERPALETTELOCKED;

    return TRUE;
}

/* The D3D format, depth and alpha of each RenderWare pixel format: swizzled
   (textures) and linear (normal rasters); the Godfather PDB's names. */
typedef struct _rwRasterConvData _rwRasterConvData;
struct _rwRasterConvData
{
    D3DFORMAT   format;
    RwUInt8     depth;
    RwUInt8     alpha;
};

_rwRasterConvData _rwRasterConvTable[2][11] =
{
    {
        { (D3DFORMAT)-1,       0, 0 },  /* rwRASTERFORMATDEFAULT */
        { D3DFMT_A1R5G5B5,    16, 1 },  /* rwRASTERFORMAT1555 */
        { D3DFMT_R5G6B5,      16, 0 },  /* rwRASTERFORMAT565 */
        { D3DFMT_A4R4G4B4,    16, 1 },  /* rwRASTERFORMAT4444 */
        { D3DFMT_L8,           8, 0 },  /* rwRASTERFORMATLUM8 */
        { D3DFMT_A8R8G8B8,    32, 1 },  /* rwRASTERFORMAT8888 */
        { D3DFMT_X8R8G8B8,    32, 0 },  /* rwRASTERFORMAT888 */
        { D3DFMT_LIN_D16,     16, 0 },  /* rwRASTERFORMAT16 */
        { D3DFMT_LIN_D24S8,   32, 0 },  /* rwRASTERFORMAT24 */
        { D3DFMT_LIN_D24S8,   32, 0 },  /* rwRASTERFORMAT32 */
        { D3DFMT_X1R5G5B5,    16, 0 }   /* rwRASTERFORMAT555 */
    },
    {
        { (D3DFORMAT)-1,           0, 0 },
        { D3DFMT_LIN_A1R5G5B5,    16, 1 },
        { D3DFMT_LIN_R5G6B5,      16, 0 },
        { D3DFMT_LIN_A4R4G4B4,    16, 1 },
        { D3DFMT_LIN_L8,           8, 0 },
        { D3DFMT_LIN_A8R8G8B8,    32, 1 },
        { D3DFMT_LIN_X8R8G8B8,    32, 0 },
        { D3DFMT_LIN_D16,         16, 0 },
        { D3DFMT_LIN_D24S8,       32, 0 },
        { D3DFMT_LIN_D24S8,       32, 0 },
        { D3DFMT_LIN_X1R5G5B5,    16, 0 }
    }
};

// match: __rwXbGetRasterFormat @ 0x002ACE10
RwBool
_rwXbGetRasterFormat(RwRaster *raster, RwInt32 flags)
{
    RwUInt32        format;

    format = flags & rwRASTERFORMATMASK;

    raster->cType = (RwUInt8)(flags & rwRASTERTYPEMASK);
    raster->cFlags = (RwUInt8)(flags & ~rwRASTERTYPEMASK);

    switch (raster->cType)
    {
        case rwRASTERTYPENORMAL:
            if (!(format & rwRASTERFORMATPIXELFORMATMASK))
            {
                format |= rwRASTERFORMAT8888;
                raster->depth = 32;
            }
            else
            {
                raster->depth =
                    _rwRasterConvTable[1][(format & rwRASTERFORMATPIXELFORMATMASK) >> 8].depth;
            }
            break;

        case rwRASTERTYPETEXTURE:
            if (!(format & rwRASTERFORMATPIXELFORMATMASK))
            {
                format |= rwRASTERFORMAT8888;
                raster->depth = 32;
            }
            else if (format & rwRASTERFORMATPAL4)
            {
                raster->depth = 8;
            }
            else if (format & rwRASTERFORMATPAL8)
            {
                raster->depth = 8;
            }
            else
            {
                raster->depth =
                    _rwRasterConvTable[0][(format & rwRASTERFORMATPIXELFORMATMASK) >> 8].depth;
            }
            break;

        case rwRASTERTYPECAMERATEXTURE:
            if (!(format & rwRASTERFORMATPIXELFORMATMASK))
            {
                if (_RwXbDeviceGlobals.zBufferDepth == 16)
                {
                    format |= rwRASTERFORMAT565;
                    raster->depth = 16;
                }
                else if (_RwXbDeviceGlobals.zBufferDepth == 32)
                {
                    format |= rwRASTERFORMAT888;
                    raster->depth = 32;
                }
            }
            else
            {
                raster->depth = _RwXbDeviceGlobals.zBufferDepth;
            }
            break;

        case rwRASTERTYPECAMERA:
            if (!(format & rwRASTERFORMATPIXELFORMATMASK))
            {
                raster->depth = _RwXbDeviceGlobals.displayDepth;

                switch (_RwXbDeviceGlobals.config.backBufferFormat)
                {
                    case D3DFMT_A8R8G8B8:
                    case D3DFMT_LIN_A8R8G8B8:
                        format = rwRASTERFORMAT8888;
                        break;

                    case D3DFMT_X8R8G8B8:
                    case D3DFMT_LIN_X8R8G8B8:
                        format = rwRASTERFORMAT888;
                        break;

                    case D3DFMT_R5G6B5:
                    case D3DFMT_LIN_R5G6B5:
                        format = rwRASTERFORMAT565;
                        break;

                    case D3DFMT_X1R5G5B5:
                    case D3DFMT_LIN_X1R5G5B5:
                        format = rwRASTERFORMAT555;
                        break;

                    case D3DFMT_A1R5G5B5:
                    case D3DFMT_LIN_A1R5G5B5:
                        format = rwRASTERFORMAT1555;
                        break;

                    default:
                        RWERROR((E_RW_INVRASTERFORMAT));
                        break;
                }
            }
            else
            {
                RWERROR((E_RW_INVRASTERFORMAT));
            }
            break;

        case rwRASTERTYPEZBUFFER:
            if (!(format & rwRASTERFORMATPIXELFORMATMASK))
            {
                if (_RwXbDeviceGlobals.zBufferDepth == 16)
                {
                    raster->depth = _RwXbDeviceGlobals.zBufferDepth;
                    format = rwRASTERFORMAT16;
                }
                else if (_RwXbDeviceGlobals.zBufferDepth == 32)
                {
                    raster->depth = _RwXbDeviceGlobals.zBufferDepth;
                    format = rwRASTERFORMAT32;
                }
            }
            else
            {
                RWERROR((E_RW_INVRASTERFORMAT));
            }
            break;

        default:
            RWERROR((E_RW_INVRASTERFORMAT));
            return FALSE;
    }

    raster->cFormat = (RwUInt8)(format >> 8);

    return TRUE;
}

/* Creates the D3D texture header of raster and allocates its bits. */
// match: _XBoxTextureCreate @ 0x002AD150
static D3DTexture *
XBoxTextureCreate(RwRaster *raster, RwXboxRasterExtension *rasExt, D3DFORMAT format)
{
    D3DTexture     *texture;
    RwUInt32        size;
    RwUInt32        n;

    texture = (D3DTexture *)RwFreeListAlloc(TextureHeaderFreeList,
                                            rwID_DRIVERMODULE | rwMEMHINTDUR_EVENT);

    XGSetTextureHeader(raster->width, raster->height, rasExt->numMipLevels, 0,
                       format, 0, texture, 0, 0);

    size = 0;

    if (format == D3DFMT_DXT1 || format == D3DFMT_DXT2 || format == D3DFMT_DXT4)
    {
        RwUInt32        shift;

        if (format == D3DFMT_DXT1)
        {
            shift = 3;
        }
        else
        {
            shift = 4;
        }

        for (n = 0; n < rasExt->numMipLevels; n++)
        {
            RwUInt32        width;
            RwUInt32        height;
            RwUInt32        blocksX;
            RwUInt32        blocksY;

            width = raster->width >> n;
            if (!width)
            {
                width = 1;
            }

            height = raster->height >> n;
            if (!height)
            {
                height = 1;
            }

            blocksX = width >> 2;
            if (!blocksX)
            {
                blocksX = 1;
            }

            blocksY = height >> 2;
            if (!blocksY)
            {
                blocksY = 1;
            }

            size += (blocksY * blocksX) << shift;
        }
    }
    else
    {
        RwUInt32        width;
        RwUInt32        height;
        RwUInt32        bytesPerPixel;

        width = raster->width;
        height = raster->height;
        bytesPerPixel = raster->depth >> 3;

        for (n = 0; n < rasExt->numMipLevels; n++)
        {
            size += bytesPerPixel * height * width;

            width >>= 1;
            if (!width)
            {
                width = 1;
            }

            height >>= 1;
            if (!height)
            {
                height = 1;
            }
        }
    }

    texture->Data = (DWORD)_rwXbMemoryPhysicalAlloc((size + 3) & ~3,
                                                    D3DTEXTURE_ALIGNMENT);
    if (!texture->Data)
    {
        RwFreeListFree(TextureHeaderFreeList, texture);
        return NULL;
    }

    return texture;
}

/* Releases a palette XBoxPaletteCreate made (or one D3D created). */
// match: _XBoxPaletteRelease @ 0x002AD2A0
static void
XBoxPaletteRelease(D3DPalette *palette)
{
    if (palette->Common & D3DCOMMON_D3DCREATED)
    {
        D3DResource_Release((D3DResource *)palette);
    }
    else
    {
        if (palette->Common & D3DCOMMON_INTREFCOUNT_MASK)
        {
            RwUInt32        n;

            for (n = 0; n < RWXB_TEXTURESTAGES; n++)
            {
                D3DDevice_SetPalette(n, NULL);
            }
        }

        D3DResource_BlockUntilNotBusy((D3DResource *)palette);
        _rwXbMemoryPhysicalFree((void *)palette->Data);
        RwFreeListFree(PaletteHeaderFreeList, palette);
    }
}

// match: __rwXbRasterNativeCreate @ 0x002AD2F0
RwBool
_rwXbRasterNativeCreate(RwRaster *raster, D3DFORMAT format, RwInt32 mipmapLevels)
{
    RwXboxRasterExtension  *rasExt;

    rasExt = RASTEREXTFROMRASTER(raster);

    if (RwRasterGetFormat(raster) & rwRASTERFORMATMIPMAP)
    {
        rasExt->numMipLevels = (RwUInt8)mipmapLevels;
    }
    else
    {
        rasExt->numMipLevels = 1;
    }

    rasExt->texture = (D3DBaseTexture *)XBoxTextureCreate(raster, rasExt, format);

    return rasExt->texture != NULL;
}

// match: __rwXbCubeRasterNativeCreate @ 0x002AD330
RwBool
_rwXbCubeRasterNativeCreate(RwRaster *raster, D3DFORMAT format, RwInt32 mipmapLevels)
{
    RwXboxRasterExtension  *rasExt;

    rasExt = RASTEREXTFROMRASTER(raster);

    if (RwRasterGetFormat(raster) & rwRASTERFORMATMIPMAP)
    {
        rasExt->numMipLevels = (RwUInt8)mipmapLevels;
    }
    else
    {
        rasExt->numMipLevels = 1;
    }

    /* Cube faces are square */
    if (raster->width > raster->height)
    {
        raster->height = raster->width;
    }
    else if (raster->width < raster->height)
    {
        raster->width = raster->height;
    }

    D3DDevice_CreateCubeTexture(raster->width, rasExt->numMipLevels, 0, format,
                                D3DPOOL_DEFAULT, (D3DCubeTexture **)&rasExt->texture);
    if (!rasExt->texture)
    {
        return FALSE;
    }

    rasExt->cube = TRUE;
    rasExt->face = 0;

    return TRUE;
}

/* Creates the texture (and palette) of a normal or texture raster. */
// match: _TextureRasterCreate @ 0x002AD3A0
static RwBool
TextureRasterCreate(RwRaster *raster, RwXboxRasterExtension *rasExt, RwInt32 linear)
{
    RwUInt32        rasFormat;
    D3DFORMAT       colorFormat;

    rasFormat = RwRasterGetFormat(raster);

    if ((rasFormat & rwRASTERFORMATPAL4) || (rasFormat & rwRASTERFORMATPAL8))
    {
        D3DPALETTESIZE  paletteSize;
        RwUInt32        size;
        void           *mem;

        paletteSize = (rasFormat & rwRASTERFORMATPAL4) ? D3DPALETTE_32 : D3DPALETTE_256;

        rasExt->palette = (D3DPalette *)RwFreeListAlloc(PaletteHeaderFreeList,
                                                        rwID_DRIVERMODULE | rwMEMHINTDUR_EVENT);

        XGSetPaletteHeader(paletteSize, rasExt->palette, 0);

        size = sizeof(D3DCOLOR) * ((rasFormat & rwRASTERFORMATPAL4) ? 32 : 256);

        mem = _rwXbMemoryPhysicalAlloc(size, D3DPALETTE_ALIGNMENT);
        rasExt->palette->Data = (DWORD)mem;
        if (!mem)
        {
            RwFreeListFree(PaletteHeaderFreeList, rasExt->palette);
            rasExt->palette = NULL;

            RWERROR((E_RW_DEVICEERROR, RWSTRING("Failed to create palette.")));
            return FALSE;
        }

        colorFormat = D3DFMT_P8;
    }
    else
    {
        colorFormat = _rwRasterConvTable[linear][(rasFormat & rwRASTERFORMATPIXELFORMATMASK) >> 8].format;
    }

    rasExt->alpha = _rwRasterConvTable[linear][(rasFormat & rwRASTERFORMATPIXELFORMATMASK) >> 8].alpha;

    rasExt->texture = (D3DBaseTexture *)XBoxTextureCreate(raster, rasExt, colorFormat);
    if (!rasExt->texture)
    {
        if (colorFormat == D3DFMT_P8)
        {
            XBoxPaletteRelease(rasExt->palette);
        }

        RWERROR((E_RW_DEVICEERROR, RWSTRING("Failed to create surface.")));
        return FALSE;
    }

    return TRUE;
}

/* The depth stencil formats of the RenderWare pixel formats. */
static D3DFORMAT zRasterConvTab[11] =
{
    D3DFMT_LIN_D24S8,       /* rwRASTERFORMATDEFAULT */
    (D3DFORMAT)-1,
    (D3DFORMAT)-1,
    (D3DFORMAT)-1,
    (D3DFORMAT)-1,
    (D3DFORMAT)-1,
    (D3DFORMAT)-1,
    D3DFMT_LIN_D16,         /* rwRASTERFORMAT16 */
    (D3DFORMAT)-1,
    D3DFMT_LIN_D24S8,       /* rwRASTERFORMAT32 */
    (D3DFORMAT)-1
};

/* Creates the depth stencil surface of a Z raster. */
// match: _ZRasterCreate @ 0x002AD4F0
static RwBool
ZRasterCreate(RwRaster *raster, D3DSurface **surface)
{
    RwInt32         rasFormat;
    D3DFORMAT       d3dFormat;

    rasFormat = (RwRasterGetFormat(raster) & rwRASTERFORMATPIXELFORMATMASK) >> 8;

    d3dFormat = zRasterConvTab[rasFormat];

    if (D3D_OK != D3DDevice_CreateDepthStencilSurface(raster->width, raster->height,
                                                      d3dFormat, D3DMULTISAMPLE_NONE,
                                                      surface))
    {
        RWERROR((E_RW_DEVICEERROR, RWSTRING("Failed to create depth stencil surface.")));
        return FALSE;
    }

    return TRUE;
}

// match: __rwXbRasterCreate @ 0x002AD560
RwBool
_rwXbRasterCreate(void *unused1, void *rasterIn, RwInt32 flags)
{
    RwRaster               *raster;
    RwXboxRasterExtension  *rasExt;

    raster = (RwRaster *)rasterIn;
    rasExt = RASTEREXTFROMRASTER(raster);

    raster->stride = 0;

    rasExt->texture = NULL;
    rasExt->palette = NULL;
    rasExt->lockedMipLevel = (RwUInt8)-1;
    rasExt->dxtFormat = 0;
    rasExt->alpha = 0;
    rasExt->cube = FALSE;
    rasExt->face = 0;

    if (flags & rwRASTERFORMATMIPMAP)
    {
        RwInt32         width;
        RwInt32         height;

        width = _rwXbFindMSB(raster->width);
        height = _rwXbFindMSB(raster->height);

        rasExt->numMipLevels = (RwUInt8)((width > height) ? (width + 1) : (height + 1));
    }
    else
    {
        rasExt->numMipLevels = 1;
    }

    if (!_rwXbGetRasterFormat(raster, flags))
    {
        return FALSE;
    }

    if (raster->width == 0 || raster->height == 0)
    {
        raster->cFlags = rwRASTERDONTALLOCATE;
        return TRUE;
    }

    switch (raster->cType)
    {
        case rwRASTERTYPENORMAL:
            if (!(raster->cFlags & rwRASTERDONTALLOCATE))
            {
                if (!TextureRasterCreate(raster, rasExt, TRUE))
                {
                    return FALSE;
                }
            }
            break;

        case rwRASTERTYPETEXTURE:
        case rwRASTERTYPECAMERATEXTURE:
            if (!(raster->cFlags & rwRASTERDONTALLOCATE))
            {
                if (raster->cType == rwRASTERTYPECAMERATEXTURE &&
                    raster->width * (raster->depth >> 3) < 64)
                {
                    RWERROR((E_RW_INVRASTERSIZE));
                    RWERROR((E_RW_DEVICEERROR,
                             RWSTRING("The minimun pitch for a camera texture is 64.")));
                    return FALSE;
                }

                if (!TextureRasterCreate(raster, rasExt, FALSE))
                {
                    return FALSE;
                }
            }
            break;

        case rwRASTERTYPEZBUFFER:
            if (!(raster->cFlags & rwRASTERDONTALLOCATE))
            {
                if (raster->width * (raster->depth >> 3) < 64)
                {
                    RWERROR((E_RW_INVRASTERSIZE));
                    RWERROR((E_RW_DEVICEERROR,
                             RWSTRING("The minimun pitch for a ZBuffer is 64.")));
                    return FALSE;
                }

                if (raster->width == _RwXbDeviceGlobals.config.backBufferWidth &&
                    raster->height == _RwXbDeviceGlobals.config.backBufferHeight)
                {
                    rasExt->texture = (D3DBaseTexture *)_RwXbDeviceGlobals.stencilSurface;
                }
                else if (!ZRasterCreate(raster, (D3DSurface **)&rasExt->texture))
                {
                    return FALSE;
                }
            }
            break;

        case rwRASTERTYPECAMERA:
            raster->cFlags = rwRASTERDONTALLOCATE;
            rasExt->texture = (D3DBaseTexture *)_RwXbDeviceGlobals.renderSurface;
            break;

        default:
            RWERROR((E_RW_INVRASTERFORMAT));
            return FALSE;
    }

    return TRUE;
}

// match: __rwXbRasterDestroy @ 0x002AD7B0
RwBool
_rwXbRasterDestroy(void *unused1, void *rasterIn, RwInt32 unused3)
{
    RwRaster               *raster;
    RwXboxRasterExtension  *rasExt;

    raster = (RwRaster *)rasterIn;
    rasExt = RASTEREXTFROMRASTER(raster);

    if (raster->parent == raster && !(raster->cFlags & rwRASTERDONTALLOCATE))
    {
        switch (raster->cType)
        {
            case rwRASTERTYPEZBUFFER:
                if (rasExt->texture != (D3DBaseTexture *)_RwXbDeviceGlobals.stencilSurface)
                {
                    _rwXbEnsureDefaultRenderTarget();
                    D3DSurface_Release((D3DSurface *)rasExt->texture);
                }

                rasExt->texture = NULL;
                break;

            case rwRASTERTYPENORMAL:
            case rwRASTERTYPETEXTURE:
            case rwRASTERTYPECAMERATEXTURE:
                {
                    RwInt32         format;
                    D3DBaseTexture *texture;

                    if (raster->cType == rwRASTERTYPECAMERATEXTURE)
                    {
                        _rwXbEnsureDefaultRenderTarget();
                    }

                    _rwXbRenderStateTextureRasterPurge(raster);

                    format = RwRasterGetFormat(raster);
                    if ((format & rwRASTERFORMATPAL4) || (format & rwRASTERFORMATPAL8))
                    {
                        XBoxPaletteRelease(rasExt->palette);
                        rasExt->palette = NULL;
                    }

                    texture = rasExt->texture;
                    _rwXbTextureRelease(texture);

                    if (!(texture->Common & D3DCOMMON_D3DCREATED))
                    {
                        RwFreeListFree(TextureHeaderFreeList, texture);
                    }

                    rasExt->texture = NULL;
                }
                break;

            case rwRASTERTYPECAMERA:
                break;

            default:
                RWERROR((E_RW_INVRASTERFORMAT));
                return FALSE;
        }
    }

    return TRUE;
}

// match: __rwXbRasterGetMipLevels @ 0x002AD8B0
RwBool
_rwXbRasterGetMipLevels(void *mipLevels, void *ras, RwInt32 unused3)
{
    RwInt32        *numMipLevels = (RwInt32 *)mipLevels;
    RwRaster       *raster = (RwRaster *)ras;

    *numMipLevels = RASTEREXTFROMRASTER(raster)->numMipLevels;

    return TRUE;
}

// match: __rwXbRasterGetSize @ 0x002AD8D0
RwUInt32
_rwXbRasterGetSize(RwRaster *raster, RwUInt8 mipLevel)
{
    RwUInt32        width;
    RwUInt32        height;
    const RwXboxRasterExtension *rasExt = RASTEREXTFROMRASTER(raster);

    width = raster->width >> mipLevel;
    height = raster->height >> mipLevel;
    if (width == 0)
    {
        width = 1;
    }
    if (height == 0)
    {
        height = 1;
    }

    if (rasExt->dxtFormat == 0)
    {
        return (raster->depth >> 3) * height * width;
    }
    else
    {
        RwUInt32        shift = (rasExt->dxtFormat == D3DFMT_DXT1) ? 3 : 4;
        RwUInt32        blocksWidth = width >> 2;
        RwUInt32        blocksHeight = height >> 2;

        if (blocksWidth == 0)
        {
            blocksWidth = 1;
        }
        if (blocksHeight == 0)
        {
            blocksHeight = 1;
        }

        return (blocksHeight * blocksWidth) << shift;
    }
}

// match: __rwXbTextureSetRaster @ 0x002AD940
RwBool
_rwXbTextureSetRaster(void *tex, void *ras, RwInt32 unused3)
{
    RwTexture      *texture = (RwTexture *)tex;
    RwRaster       *raster = (RwRaster *)ras;

    texture->raster = raster;

    return TRUE;
}

// match: __rwXbRasterSubRaster @ 0x002AD950
RwBool
_rwXbRasterSubRaster(void *rasterIn, void *parentRasterIn, RwInt32 unused3)
{
    RwRaster       *raster = (RwRaster *)rasterIn;
    RwRaster       *parentRaster = (RwRaster *)parentRasterIn;

    raster->stride = parentRaster->stride;
    raster->depth = parentRaster->depth;
    raster->cType = parentRaster->cType;
    raster->cFormat = parentRaster->cFormat;

    return TRUE;
}
