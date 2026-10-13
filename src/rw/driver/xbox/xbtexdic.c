/*
 * codfh-match: RenderWare 3.6's Xbox driver native textures
 * (driver/xbox/xbtexdic.c), rebuilt from the image after d3d8texdic.c;
 * names from the Godfather PDB's copy of the driver.
 */

#include <xtl.h>
#include "batypes.h"
#include "batype.h"
#include "balibtyp.h"
#include "barwtyp.h"
#include "badebug.h"
#include "bamemory.h"
#include "babinary.h"
#include "bastream.h"
#include "badevice.h"
#include "baraster.h"
#include "batextur.h"
#include "xbraster.h"
#include "xbtexdic.h"

/* RenderWare 3.6's RCS id string, which the image keeps (the 3.7.2 tree has none) */
static const char rcsid[] = "@@@@(#)$Id: //RenderWare/RW36Active/rwsdk/driver/xbox/xbtexdic.c#1 $";

typedef struct _rwXbNativeTexture _rwXbNativeTexture;
struct _rwXbNativeTexture
{
    RwInt32             id;                 /* rwID_XBOX */
    RwInt32             filterAndAddress;   /* Same as in babintex.c */
    RwChar              name[rwTEXTUREBASENAMELENGTH];
    RwChar              mask[rwTEXTUREBASENAMELENGTH];
};

typedef struct _rwXbNativeRaster _rwXbNativeRaster;
struct _rwXbNativeRaster
{
    RwInt32             format;
    RwUInt16            alpha;
    RwUInt16            cube;
    RwUInt16            width;
    RwUInt16            height;
    RwUInt8             depth;
    RwUInt8             numMipLevels;
    RwUInt8             type;
    RwUInt8             dxtFormat;
    RwUInt32            size;
};

/* The raster header of streams before 0x34001, without the cube flag and the
   pixel data size (no name survives). */
typedef struct _rwXbNativeRasterOld _rwXbNativeRasterOld;
struct _rwXbNativeRasterOld
{
    RwInt32             format;
    RwUInt32            alpha;
    RwUInt16            width;
    RwUInt16            height;
    RwUInt8             depth;
    RwUInt8             numMipLevels;
    RwUInt8             type;
    RwUInt8             dxtFormat;
};

/* The D3D format of each RenderWare pixel format: swizzled, then linear. */
static const D3DFORMAT convTable[2][11] =
{
    {
        (D3DFORMAT)-1,          /* rwRASTERFORMATDEFAULT */
        D3DFMT_A1R5G5B5,        /* rwRASTERFORMAT1555 */
        D3DFMT_R5G6B5,          /* rwRASTERFORMAT565 */
        D3DFMT_A4R4G4B4,        /* rwRASTERFORMAT4444 */
        D3DFMT_L8,              /* rwRASTERFORMATLUM8 */
        D3DFMT_A8R8G8B8,        /* rwRASTERFORMAT8888 */
        D3DFMT_X8R8G8B8,        /* rwRASTERFORMAT888 */
        (D3DFORMAT)-1,          /* rwRASTERFORMAT16 */
        (D3DFORMAT)-1,          /* rwRASTERFORMAT24 */
        (D3DFORMAT)-1,          /* rwRASTERFORMAT32 */
        D3DFMT_X1R5G5B5         /* rwRASTERFORMAT555 */
    },
    {
        (D3DFORMAT)-1,          /* rwRASTERFORMATDEFAULT */
        D3DFMT_LIN_A1R5G5B5,    /* rwRASTERFORMAT1555 */
        D3DFMT_LIN_R5G6B5,      /* rwRASTERFORMAT565 */
        D3DFMT_LIN_A4R4G4B4,    /* rwRASTERFORMAT4444 */
        D3DFMT_LIN_L8,          /* rwRASTERFORMATLUM8 */
        D3DFMT_LIN_A8R8G8B8,    /* rwRASTERFORMAT8888 */
        D3DFMT_LIN_X8R8G8B8,    /* rwRASTERFORMAT888 */
        (D3DFORMAT)-1,          /* rwRASTERFORMAT16 */
        (D3DFORMAT)-1,          /* rwRASTERFORMAT24 */
        (D3DFORMAT)-1,          /* rwRASTERFORMAT32 */
        D3DFMT_LIN_X1R5G5B5     /* rwRASTERFORMAT555 */
    }
};

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: _rcsid @ 0x00417288
// match: _convTable @ 0x004172D0

// match: __rwXbNativeTextureGetSize @ 0x002B9DB0
// sp-match: __rwXbNativeTextureGetSize @ 0x001D51C0

RwBool
_rwXbNativeTextureGetSize(void *sizeIn, void *textureIn,
                          RwInt32 unused3 __RWUNUSED__)
{
    RwTexture              *texture = (RwTexture *)textureIn;
    RwRaster               *raster;
    RwXboxRasterExtension  *rasExt;
    RwInt32                 numMipLevels;
    RwUInt32                rasFormat;
    RwUInt32                size;
    RwUInt32                rasterSize;

    /* Platform specific ID, filter & addressing modes texture and Mask names */
    size = rwCHUNKHEADERSIZE + sizeof(_rwXbNativeTexture);

    raster = RwTextureGetRaster(texture);
    if (!raster)
    {
        *((RwUInt32 *)sizeIn) = size;

        return TRUE;
    }

    /* Native raster data structure */
    size += sizeof(_rwXbNativeRaster);

    /* Size of the palette if palletized */
    rasFormat = RwRasterGetFormat(raster);
    if (rasFormat & rwRASTERFORMATPAL4)
    {
        size += sizeof(RwUInt32) * 32;
    }
    else if (rasFormat & rwRASTERFORMATPAL8)
    {
        size += sizeof(RwUInt32) * 256;
    }

    rasExt = RASTEREXTFROMRASTER(raster);

    /* Size of pixel data for all mip levels */
    rasterSize = 0;
    numMipLevels = RwRasterGetNumLevels(raster);
    while (numMipLevels--)
    {
        rasterSize += _rwXbRasterGetSize(raster, (RwUInt8)numMipLevels);
    }

    if (rasExt->cube)
    {
        rasterSize *= 6;
    }

    *((RwUInt32 *)sizeIn) = ((rasterSize + 3) & ~3) + size;

    return TRUE;
}

// match: __rwXbNativeTextureWrite @ 0x002B9E50
// sp-match: __rwXbNativeTextureWrite @ 0x001D5260
RwBool
_rwXbNativeTextureWrite(void *streamIn, void *textureIn,
                        RwInt32 unused3 __RWUNUSED__)
{
    RwStream               *stream = (RwStream *)streamIn;
    RwTexture              *texture = (RwTexture *)textureIn;
    RwRaster               *raster;
    RwXboxRasterExtension  *rasExt;
    _rwXbNativeTexture      nativeTexture;
    _rwXbNativeRaster       nativeRaster;
    RwInt32                 bytesLeftToWrite;
    RwInt32                 i;
    RwUInt32                size;
    RwUInt32                rasterSize;

    /* Calc the amount of data to write, excluding the chunk header*/
    _rwXbNativeTextureGetSize((void *)&bytesLeftToWrite, textureIn, 0);
    bytesLeftToWrite -= rwCHUNKHEADERSIZE;

    /* Struct header for _rwXbNativeTexture structure */
    if (!RwStreamWriteChunkHeader(stream, rwID_STRUCT, bytesLeftToWrite))
    {
        return FALSE;
    }

    /* ID, filter & addressing modes */
    nativeTexture.id = rwID_XBOX;
    nativeTexture.filterAndAddress =
        (((RwInt32)RwTextureGetFilterMode(texture)) & 0xFF) |
        ((((RwInt32)RwTextureGetAddressingU(texture)) << 8) & 0x0F00) |
        ((((RwInt32)RwTextureGetAddressingV(texture)) << 12) & 0xF000);

    /* Texture name */
    memcpy(nativeTexture.name, RwTextureGetName(texture),
        sizeof(RwChar) * rwTEXTUREBASENAMELENGTH);

    /* Mask name */
    memcpy(nativeTexture.mask, RwTextureGetMaskName(texture),
        sizeof(RwChar) * rwTEXTUREBASENAMELENGTH);

    if (!RwStreamWrite(stream, (void *)&nativeTexture,
                       sizeof(_rwXbNativeTexture)))
    {
        return FALSE;
    }

    bytesLeftToWrite -= sizeof(_rwXbNativeTexture);

    /*
     * Write the rasters
     */
    raster = RwTextureGetRaster(texture);
    rasExt = RASTEREXTFROMRASTER(raster);

    nativeRaster.width = (RwUInt16)RwRasterGetWidth(raster);
    nativeRaster.height = (RwUInt16)RwRasterGetHeight(raster);
    nativeRaster.format = RwRasterGetFormat(raster);
    nativeRaster.depth = (RwUInt8)RwRasterGetDepth(raster);
    nativeRaster.numMipLevels = (RwUInt8)RwRasterGetNumLevels(raster);
    nativeRaster.type = raster->cType;
    nativeRaster.dxtFormat = rasExt->dxtFormat;
    nativeRaster.alpha = rasExt->alpha;
    nativeRaster.cube = rasExt->cube;

    size = 0;
    for (i = 0; i < nativeRaster.numMipLevels; i++)
    {
        size += _rwXbRasterGetSize(raster, (RwUInt8)i);
    }

    if (rasExt->cube)
    {
        size *= 6;
    }

    nativeRaster.size = (size + 3) & ~3;

    if (!RwStreamWrite(stream, (void *)&nativeRaster,
                       sizeof(_rwXbNativeRaster)))
    {
        return FALSE;
    }

    bytesLeftToWrite -= sizeof(_rwXbNativeRaster);

    /* Palette */
    if (nativeRaster.format & rwRASTERFORMATPAL4)
    {
        RwUInt8    *palette;

        palette = RwRasterLockPalette(raster, rwRASTERLOCKREAD);

        if (!RwStreamWrite(stream, (void *)palette, sizeof(RwUInt32) * 32))
        {
            return FALSE;
        }

        RwRasterUnlockPalette(raster);

        bytesLeftToWrite -= sizeof(RwUInt32) * 32;
    }
    else if (nativeRaster.format & rwRASTERFORMATPAL8)
    {
        RwUInt8    *palette;

        palette = RwRasterLockPalette(raster, rwRASTERLOCKREAD);

        if (!RwStreamWrite(stream, (void *)palette, sizeof(RwUInt32) * 256))
        {
            return FALSE;
        }

        RwRasterUnlockPalette(raster);

        bytesLeftToWrite -= sizeof(RwUInt32) * 256;
    }

    /* Pixels, every face of a cube texture */
    rasterSize = 0;
    rasExt->face = 0;
    do
    {
        for (i = 0; i < nativeRaster.numMipLevels; i++)
        {
            RwUInt8    *pixels;

            size = _rwXbRasterGetSize(raster, (RwUInt8)i);

            pixels = RwRasterLock(raster, (RwUInt8)i, rwRASTERLOCKREAD | rwRASTERLOCKRAW);

            if (!RwStreamWrite(stream, (void *)pixels, size))
            {
                return FALSE;
            }

            RwRasterUnlock(raster);

            bytesLeftToWrite -= size;
            rasterSize += size;
        }

        rasExt->face++;
    }
    while (rasExt->cube && rasExt->face < 6);

    rasExt->face = 0;

    /* Pad to the stored size */
    if (rasterSize < nativeRaster.size)
    {
        i = 0;
        size = nativeRaster.size - rasterSize;

        RwStreamWrite(stream, (void *)&i, size);

        bytesLeftToWrite -= size;
    }

    return TRUE;
}

#ifdef CODFH_WIN32
/* (port/src/d3d/xdraw.cpp: a texture's name with its D3D header, for the port's texture dumps
   and replacements) */
void port_texture_named(const void *pHeader, const char *pszName);
#endif

// match: __rwXbNativeTextureRead @ 0x002BA100
// sp-match: __rwXbNativeTextureRead @ 0x001D5510
RwBool
_rwXbNativeTextureRead(void *streamIn, void *textureIn,
                       RwInt32 unused3 __RWUNUSED__)
{
    RwStream               *stream = (RwStream *)streamIn;
    RwRaster               *raster;
    RwTexture              *texture;
    RwXboxRasterExtension  *rasExt;
    _rwXbNativeTexture      nativeTexture;
    _rwXbNativeRaster       nativeRaster;
    RwUInt32                length, version;
    RwInt32                 i;

    if (!RwStreamFindChunk(stream, rwID_STRUCT, &length, &version))
    {
        return FALSE;
    }

    if (!((version >= rwLIBRARYBASEVERSION) &&
          (version <= rwLIBRARYCURRENTVERSION)))
    {
        return FALSE;
    }

    /* ID, filter & addressing modes */
    if (RwStreamRead(stream, (void *)&nativeTexture,
                     sizeof(_rwXbNativeTexture)) != sizeof(_rwXbNativeTexture))
    {
        return FALSE;
    }

    if (nativeTexture.id != rwID_XBOX)
    {
        return FALSE;
    }

    /* Native raster data structure */
    if (version < 0x34001)
    {
        _rwXbNativeRasterOld oldRaster;

        if (RwStreamRead(stream, (void *)&oldRaster,
                         sizeof(_rwXbNativeRasterOld)) != sizeof(_rwXbNativeRasterOld))
        {
            return FALSE;
        }

        nativeRaster.format = oldRaster.format;
        nativeRaster.alpha = (RwUInt16)oldRaster.alpha;
        nativeRaster.cube = 0;
        nativeRaster.width = oldRaster.width;
        nativeRaster.height = oldRaster.height;
        nativeRaster.depth = oldRaster.depth;
        nativeRaster.numMipLevels = oldRaster.numMipLevels;
        nativeRaster.type = oldRaster.type;
        nativeRaster.dxtFormat = oldRaster.dxtFormat;
        nativeRaster.size = 0;
    }
    else
    {
        if (RwStreamRead(stream, (void *)&nativeRaster,
                         sizeof(_rwXbNativeRaster)) != sizeof(_rwXbNativeRaster))
        {
            return FALSE;
        }
    }

    if (nativeRaster.cube)
    {
        raster = RwRasterCreate(nativeRaster.width, nativeRaster.height,
                                nativeRaster.depth,
                                nativeRaster.type | nativeRaster.format | rwRASTERDONTALLOCATE);
        if (!raster)
        {
            return FALSE;
        }

        if (nativeRaster.dxtFormat)
        {
            if (!_rwXbCubeRasterNativeCreate(raster, (D3DFORMAT)nativeRaster.dxtFormat,
                                             nativeRaster.numMipLevels))
            {
                RwRasterDestroy(raster);

                return FALSE;
            }
        }
        else
        {
            D3DFORMAT   d3dFormat;

            if (nativeRaster.format & (rwRASTERFORMATPAL4 | rwRASTERFORMATPAL8))
            {
                d3dFormat = D3DFMT_P8;
            }
            else
            {
                d3dFormat = convTable[nativeRaster.type == rwRASTERTYPENORMAL]
                                     [(nativeRaster.format & rwRASTERFORMATPIXELFORMATMASK) >> 8];
            }

            if (!_rwXbCubeRasterNativeCreate(raster, d3dFormat, nativeRaster.numMipLevels))
            {
                RwRasterDestroy(raster);

                return FALSE;
            }
        }

        raster->cFlags &= ~rwRASTERDONTALLOCATE;
    }
    else if (nativeRaster.dxtFormat)
    {
        raster = RwRasterCreate(nativeRaster.width, nativeRaster.height,
                                nativeRaster.depth,
                                nativeRaster.type | nativeRaster.format | rwRASTERDONTALLOCATE);
        if (!raster)
        {
            return FALSE;
        }

        if (!_rwXbRasterNativeCreate(raster, (D3DFORMAT)nativeRaster.dxtFormat,
                                     nativeRaster.numMipLevels))
        {
            RwRasterDestroy(raster);

            return FALSE;
        }

        raster->cFlags &= ~rwRASTERDONTALLOCATE;
    }
    else
    {
        raster = RwRasterCreate(nativeRaster.width, nativeRaster.height,
                                nativeRaster.depth,
                                nativeRaster.type | nativeRaster.format);
        if (!raster)
        {
            return FALSE;
        }
    }

    rasExt = RASTEREXTFROMRASTER(raster);
    rasExt->dxtFormat = nativeRaster.dxtFormat;
    rasExt->alpha = (RwUInt8)nativeRaster.alpha;

    /* Palette */
    if (nativeRaster.format & rwRASTERFORMATPAL4)
    {
        RwUInt8    *palette;

        palette = RwRasterLockPalette(raster, rwRASTERLOCKWRITE);

        if (RwStreamRead(stream, (void *)palette,
                         sizeof(RwUInt32) * 32) != sizeof(RwUInt32) * 32)
        {
            return FALSE;
        }

        RwRasterUnlockPalette(raster);
    }
    else if (nativeRaster.format & rwRASTERFORMATPAL8)
    {
        RwUInt8    *palette;

        palette = RwRasterLockPalette(raster, rwRASTERLOCKWRITE);

        if (RwStreamRead(stream, (void *)palette,
                         sizeof(RwUInt32) * 256) != sizeof(RwUInt32) * 256)
        {
            return FALSE;
        }

        RwRasterUnlockPalette(raster);
    }

    /* Pixels */
    if (rasExt->cube)
    {
        rasExt->face = 0;
        do
        {
            for (i = 0; i < nativeRaster.numMipLevels; i++)
            {
                RwUInt32    size;
                RwUInt8    *pixels;

                size = _rwXbRasterGetSize(raster, (RwUInt8)i);

                pixels = RwRasterLock(raster, (RwUInt8)i, rwRASTERLOCKWRITE | rwRASTERLOCKRAW);

                if (!RwStreamRead(stream, (void *)pixels, size))
                {
                    return FALSE;
                }

                RwRasterUnlock(raster);
            }

            rasExt->face++;
        }
        while (rasExt->face < 6);

        rasExt->face = 0;
    }
    else if (version < 0x34001)
    {
        RwUInt8    *pixels;
        RwUInt32    level;

        /* Each level's size, then its pixels, straight into the texture */
        pixels = (RwUInt8 *)(rasExt->texture->Data | 0x80000000);
        for (level = 0; level < nativeRaster.numMipLevels; level++)
        {
            RwUInt32    size;

            if (RwStreamRead(stream, (void *)&size, sizeof(RwUInt32)) != sizeof(RwUInt32))
            {
                return FALSE;
            }

            if (RwStreamRead(stream, (void *)pixels, size) != size)
            {
                return FALSE;
            }

            pixels += size;
        }
    }
    else
    {
        if (RwStreamRead(stream, (void *)(rasExt->texture->Data | 0x80000000),
                         nativeRaster.size) != nativeRaster.size)
        {
            return FALSE;
        }
    }

    texture = RwTextureCreate(raster);
    if (!texture)
    {
        RwRasterDestroy(raster);

        return FALSE;
    }

    RwTextureSetFilterMode(texture, nativeTexture.filterAndAddress & 0xFF);
    RwTextureSetAddressingU(texture, (nativeTexture.filterAndAddress >> 8) & 0x0F);
    RwTextureSetAddressingV(texture, (nativeTexture.filterAndAddress >> 12) & 0x0F);
    RwTextureSetName(texture, nativeTexture.name);
    RwTextureSetMaskName(texture, nativeTexture.mask);
#ifdef CODFH_WIN32
    rasExt = RASTEREXTFROMRASTER(raster);
    if (rasExt && rasExt->texture)
        port_texture_named(rasExt->texture, nativeTexture.name);
#endif

    *((RwTexture **)textureIn) = texture;

    return TRUE;
}
