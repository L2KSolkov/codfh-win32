/*
 * codfh-match: RenderWare 3.6's Xbox driver DDS textures
 * (driver/xbox/xbdxttex.c), which the 3.7.2 tree does not have. Written from
 * the image after the tree's driver/d3d9/d3d9dxttex.c (the DXT1 alpha checks
 * and the DDS search) and the Godfather debug build's copy of this file (the
 * reader's structure and names).
 */

#include <xtl.h>

#include "batypes.h"
#include "balibtyp.h"
#include "badebug.h"
#include "bamemory.h"
#include "baraster.h"
#include "batextur.h"
#include "baimage.h"
#include "bastream.h"
#include "osintf.h"

#include "fsys36.h"

#include "xbraster.h"
#include "xbdxttex.h"

#include "dds.h"

/* RenderWare 3.6's RCS id string, which the image keeps (the 3.7.2 tree has none) */
static const char rcsid[] = "@@@@(#)$Id: //RenderWare/RW36Active/rwsdk/driver/xbox/xbdxttex.c#2 $";

#define rwSEARCHPATH_SEPARATOR ';' /* Borrowed from baimage.c */

typedef struct DXTColBlock DXTColBlock;
struct DXTColBlock
{
    RwUInt16 col0;
    RwUInt16 col1;

    /* no bit fields - use bytes*/
    RwUInt8 row[4];
};

static __inline RwBool
DXT1BlockHasAlpha(const DXTColBlock *pColorBlock)
{
    /* width is width of image in pixels */
    RwInt32     r,n;

    /* r steps through lines in y */
    for( r=0; r < 4; ++r)
    {
        RwUInt32 bits = pColorBlock->row[r];

        /* n steps through pixels */
        for( n=0; n < 4; ++n )
        {
            if ((bits & 0x3) == 0x3)
            {
                /* this color is the only one with non-255 alpha */
                return TRUE;
            }

            bits >>= 2;
        }
    }

    return FALSE;
}

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: _DDSPF_DXT1 @ 0x00416998
// match: _DDSPF_DXT2 @ 0x004169B8
// match: _DDSPF_DXT3 @ 0x004169D8
// match: _DDSPF_DXT4 @ 0x004169F8
// match: _DDSPF_DXT5 @ 0x00416A18
// match: _DDSPF_A8R8G8B8 @ 0x00416A38
// match: _DDSPF_A1R5G5B5 @ 0x00416A58
// match: _DDSPF_A4R4G4B4 @ 0x00416A78
// match: _DDSPF_R8G8B8 @ 0x00416A98
// match: _DDSPF_R5G6B5 @ 0x00416AB8
// match: _rcsid @ 0x00416AD8

// match: _DXT1BlockNonSquareHasAlpha @ 0x002B2420
// sp-match: _DXT1BlockNonSquareHasAlpha @ 0x001CD840
static __inline RwBool
DXT1BlockNonSquareHasAlpha(const DXTColBlock *pColorBlock, RwInt32 width, RwInt32 height)
{
    /* width is width of image in pixels */
    RwInt32     r,n;

    /* r steps through lines in y */
    for( r=0; r < height; ++r)
    {
        RwUInt32 bits = pColorBlock->row[r];

        /* n steps through pixels */
        for( n=0; n < width; ++n )
        {
            if ((bits & 0x3) == 0x3)
            {
                /* this color is the only one with non-255 alpha */
                return TRUE;
            }

            bits >>= 2;
        }
    }

    return FALSE;
}

// match: __rwXboxDXT1HasAlpha @ 0x002B2470
// sp-match: __rwXboxDXT1HasAlpha @ 0x001CD890
RwUInt8
_rwXboxDXT1HasAlpha(RwRaster *raster)
{
    RwInt32 numMipLevels;
    RwInt32 i;

    /* Load the surfaces */
    numMipLevels = RwRasterGetNumLevels(raster);
    for (i = 0; i < numMipLevels; ++i)
    {
        RwBool              squareBlocks = TRUE;
        RwInt32             sizeblockX, sizeblockY, totalBlocks;
        const DXTColBlock   *pixels;

        pixels = (const DXTColBlock *)RwRasterLock(raster, (RwUInt8)i, rwRASTERLOCKREAD);

        if (raster->width < 4)
        {
            sizeblockX = raster->width;
            totalBlocks = 1;

            squareBlocks = FALSE;
        }
        else
        {
            sizeblockX = 4;
            totalBlocks = raster->width / 4;
        }

        if (raster->height < 4)
        {
            sizeblockY = raster->height;

            squareBlocks = FALSE;
        }
        else
        {
            sizeblockY = 4;
            totalBlocks *= raster->height / 4;
        }

        if (squareBlocks)
        {
            do
            {
                /*
                 * If the first color is greater than the second, it implies that
                 * only opaque texels are defined
                 */
                if (!(pixels->col0 > pixels->col1) &&
                    /* but not all of those have non-opaque alpha */
                    DXT1BlockHasAlpha(pixels))
                {
                    RwRasterUnlock(raster);

                    return TRUE;
                }

                ++pixels;
            }
            while(--totalBlocks);
        }
        else
        {
            do
            {
                /*
                 * If the first color is greater than the second, it implies that
                 * only opaque texels are defined
                 */
                if (!(pixels->col0 > pixels->col1) &&
                    /* but not all of those have non-opaque alpha */
                    DXT1BlockNonSquareHasAlpha(pixels, sizeblockX, sizeblockY))
                {
                    RwRasterUnlock(raster);

                    return TRUE;
                }

                ++pixels;
            }
            while(--totalBlocks);
        }

        RwRasterUnlock(raster);
    }

    return FALSE;
}

/* Reads the DDS file fullPathName into a texture called name. */
// match: _XboxDXTTextureRead @ 0x002B25D0
// sp-match: _XboxDXTTextureRead @ 0x001CD9F0
static RwTexture *
XboxDXTTextureRead(const RwChar *name, const RwChar *fullPathName)
{
    RwRaster               *raster = NULL;
    RwInt32                 rasType = 0;
    RwStream               *stream;
    RwUInt32                magic;
    DDS_HEADER              header;
    RwInt32                 mipMapped;
    RwInt32                 mipMapLevels;
    RwBool                  cubeTexture;
    RwXboxRasterExtension  *rasExt;
    RwInt32                 numMipLevels;
    RwInt32                 i;
    RwTexture              *texture;

    if (!RwFexist(fullPathName))
    {
        return NULL;
    }

    stream = RwStreamOpen(rwSTREAMFILENAME, rwSTREAMREAD, fullPathName);
    if (stream == NULL)
    {
        return NULL;
    }

    /* The magic number */
    if (RwStreamRead(stream, &magic, sizeof(RwUInt32)) != sizeof(RwUInt32))
    {
        RwStreamClose(stream, NULL);
        return NULL;
    }

    if (magic != MAKEFOURCC('D', 'D', 'S', ' '))
    {
        RwStreamClose(stream, NULL);
        return NULL;
    }

    /* The header */
    if (RwStreamRead(stream, &header, sizeof(DDS_HEADER)) != sizeof(DDS_HEADER))
    {
        RwStreamClose(stream, NULL);
        return NULL;
    }

    if (!(header.dwHeaderFlags & DDS_HEADER_FLAGS_TEXTURE))
    {
        RwStreamClose(stream, NULL);
        return NULL;
    }

    mipMapped = (header.dwHeaderFlags & DDS_HEADER_FLAGS_MIPMAP) ? rwRASTERFORMATMIPMAP : 0;

    if (mipMapped)
    {
        mipMapLevels = header.dwMipMapCount;
    }
    else
    {
        mipMapLevels = 1;
    }

    cubeTexture = ((header.dwSurfaceFlags & DDS_SURFACE_FLAGS_CUBEMAP) &&
                   (header.dwCubemapFlags & DDS_CUBEMAP_ALLFACES)) ? TRUE : FALSE;

    if (header.ddspf.dwFlags == DDS_FOURCC)
    {
        raster = RwRasterCreate(header.dwWidth, header.dwHeight, 0,
                                mipMapped | rwRASTERTYPETEXTURE | rwRASTERDONTALLOCATE);
        if (raster == NULL)
        {
            RwStreamClose(stream, NULL);
            return NULL;
        }

        rasExt = RASTEREXTFROMRASTER(raster);

        switch (header.ddspf.dwFourCC)
        {
            case D3DFMT_DXT1:
            case MAKEFOURCC('D', 'X', 'T', '1'):
                rasExt->dxtFormat = D3DFMT_DXT1;
                break;

            case D3DFMT_DXT2:
            case MAKEFOURCC('D', 'X', 'T', '2'):
            case MAKEFOURCC('D', 'X', 'T', '3'):
                rasExt->dxtFormat = D3DFMT_DXT2;
                break;

            case D3DFMT_DXT4:
            case MAKEFOURCC('D', 'X', 'T', '4'):
            case MAKEFOURCC('D', 'X', 'T', '5'):
                rasExt->dxtFormat = D3DFMT_DXT4;
                break;

            default:
                break;
        }

        if (cubeTexture)
        {
            if (!_rwXbCubeRasterNativeCreate(raster, (D3DFORMAT)rasExt->dxtFormat, mipMapLevels))
            {
                RwRasterDestroy(raster);
                RwStreamClose(stream, NULL);
                return NULL;
            }
        }
        else
        {
            if (!_rwXbRasterNativeCreate(raster, (D3DFORMAT)rasExt->dxtFormat, mipMapLevels))
            {
                RwRasterDestroy(raster);
                RwStreamClose(stream, NULL);
                return NULL;
            }
        }

        raster->cFlags &= ~rwRASTERDONTALLOCATE;
    }
    else if (header.ddspf.dwFlags == DDS_RGB)
    {
        if (cubeTexture)
        {
            D3DFORMAT       d3dFormat = (D3DFORMAT)0;

            if (header.ddspf.dwRBitMask == 0x00ff0000)
            {
                rasType = rwRASTERFORMAT888;
                d3dFormat = D3DFMT_X8R8G8B8;
            }
            else if (header.ddspf.dwRBitMask == 0x0000f800)
            {
                rasType = rwRASTERFORMAT565;
                d3dFormat = D3DFMT_R5G6B5;
            }

            raster = RwRasterCreate(header.dwWidth, header.dwHeight, 0,
                                    mipMapped | rasType | rwRASTERTYPETEXTURE |
                                    rwRASTERDONTALLOCATE);

            if (!_rwXbCubeRasterNativeCreate(raster, d3dFormat, mipMapLevels))
            {
                RwRasterDestroy(raster);
                raster = NULL;
            }
            else
            {
                raster->cFlags &= ~rwRASTERDONTALLOCATE;
            }
        }
        else
        {
            if (header.ddspf.dwRBitMask == 0x00ff0000)
            {
                rasType = rwRASTERFORMAT888;
            }
            else if (header.ddspf.dwRBitMask == 0x0000f800)
            {
                rasType = rwRASTERFORMAT565;
            }

            raster = RwRasterCreate(header.dwWidth, header.dwHeight, 0,
                                    mipMapped | rasType | rwRASTERTYPETEXTURE);
        }

        if (raster == NULL)
        {
            RwStreamClose(stream, NULL);
            return NULL;
        }
    }
    else if (header.ddspf.dwFlags == DDS_RGBA)
    {
        if (cubeTexture)
        {
            D3DFORMAT       format = (D3DFORMAT)0;

            if (header.ddspf.dwRBitMask == 0x00ff0000)
            {
                rasType = rwRASTERFORMAT8888;
                format = D3DFMT_A8R8G8B8;
            }
            else if (header.ddspf.dwRBitMask == 0x00007c00)
            {
                rasType = rwRASTERFORMAT1555;
                format = D3DFMT_A1R5G5B5;
            }
            else if (header.ddspf.dwRBitMask == 0x00000f00)
            {
                rasType = rwRASTERFORMAT4444;
                format = D3DFMT_A4R4G4B4;
            }

            raster = RwRasterCreate(header.dwWidth, header.dwHeight, 0,
                                    mipMapped | rasType | rwRASTERTYPETEXTURE |
                                    rwRASTERDONTALLOCATE);

            if (!_rwXbCubeRasterNativeCreate(raster, format, mipMapLevels))
            {
                RwRasterDestroy(raster);
                raster = NULL;
            }
            else
            {
                raster->cFlags &= ~rwRASTERDONTALLOCATE;
            }
        }
        else
        {
            if (header.ddspf.dwRBitMask == 0x00ff0000)
            {
                rasType = rwRASTERFORMAT8888;
            }
            else if (header.ddspf.dwRBitMask == 0x00007c00)
            {
                rasType = rwRASTERFORMAT1555;
            }
            else if (header.ddspf.dwRBitMask == 0x00000f00)
            {
                rasType = rwRASTERFORMAT4444;
            }

            raster = RwRasterCreate(header.dwWidth, header.dwHeight, 0,
                                    mipMapped | rasType | rwRASTERTYPETEXTURE);
        }

        if (raster == NULL)
        {
            RwStreamClose(stream, NULL);
            return NULL;
        }
    }

    rasExt = RASTEREXTFROMRASTER(raster);

    if (mipMapped)
    {
        numMipLevels = header.dwMipMapCount;
    }
    else
    {
        numMipLevels = 1;
    }

    do
    {
        if (cubeTexture)
        {
            if (header.dwCubemapFlags & DDS_CUBEMAP_POSITIVEX)
            {
                rasExt->face = D3DCUBEMAP_FACE_POSITIVE_X;
                header.dwCubemapFlags &= ~DDS_CUBEMAP_POSITIVEX;
            }
            else if (header.dwCubemapFlags & DDS_CUBEMAP_NEGATIVEX)
            {
                rasExt->face = D3DCUBEMAP_FACE_NEGATIVE_X;
                header.dwCubemapFlags &= ~DDS_CUBEMAP_NEGATIVEX;
            }
            else if (header.dwCubemapFlags & DDS_CUBEMAP_POSITIVEY)
            {
                rasExt->face = D3DCUBEMAP_FACE_POSITIVE_Y;
                header.dwCubemapFlags &= ~DDS_CUBEMAP_POSITIVEY;
            }
            else if (header.dwCubemapFlags & DDS_CUBEMAP_NEGATIVEY)
            {
                rasExt->face = D3DCUBEMAP_FACE_NEGATIVE_Y;
                header.dwCubemapFlags &= ~DDS_CUBEMAP_NEGATIVEY;
            }
            else if (header.dwCubemapFlags & DDS_CUBEMAP_POSITIVEZ)
            {
                rasExt->face = D3DCUBEMAP_FACE_POSITIVE_Z;
                header.dwCubemapFlags &= ~DDS_CUBEMAP_POSITIVEZ;
            }
            else if (header.dwCubemapFlags & DDS_CUBEMAP_NEGATIVEZ)
            {
                rasExt->face = D3DCUBEMAP_FACE_NEGATIVE_Z;
                header.dwCubemapFlags = 0;
            }
            else
            {
                break;
            }
        }

        for (i = 0; i < numMipLevels; i++)
        {
            RwUInt32        size;
            RwUInt8        *pixels;

            size = _rwXbRasterGetSize(raster, (RwUInt8)i);

            pixels = RwRasterLock(raster, (RwUInt8)i, rwRASTERLOCKWRITE);

            /* 24 bit files expand to 32 bits */
            if (rasType == rwRASTERFORMAT888)
            {
                size = (3 * size) >> 2;
            }

            if (RwStreamRead(stream, pixels, size) != size)
            {
                RwRasterUnlock(raster);
                RwRasterDestroy(raster);
                RwStreamClose(stream, NULL);
                return NULL;
            }

            if (rasType == rwRASTERFORMAT888)
            {
                RwUInt32       *dstEndPixel = (RwUInt32 *)(pixels + (4 * size) / 3 - 4);
                const RwUInt8  *srcEndPixel = pixels + size - 4;

                while (pixels < (RwUInt8 *)dstEndPixel)
                {
                    const RwUInt32  src = *(const RwUInt32 *)srcEndPixel;

                    *dstEndPixel = ((src & 0x000000ff) << 16) | ((src >> 8) & 0x0000ffff);

                    dstEndPixel--;
                    srcEndPixel -= 3;
                }
            }

            RwRasterUnlock(raster);
        }
    }
    while (cubeTexture && header.dwCubemapFlags);

    RwStreamClose(stream, NULL);

    if (header.ddspf.dwFlags == DDS_FOURCC)
    {
        if (rasExt->dxtFormat == D3DFMT_DXT1)
        {
            rasExt->alpha = _rwXboxDXT1HasAlpha(raster);

            if (!rasExt->alpha)
            {
                const RwInt32   pixelFormat = RwRasterGetFormat(raster) & rwRASTERFORMATPIXELFORMATMASK;

                /* No alpha: the opaque format of the same depth */
                if (pixelFormat == rwRASTERFORMAT8888)
                {
                    raster->cFormat &= ~(rwRASTERFORMAT8888 >> 8);
                    raster->cFormat |= (rwRASTERFORMAT888 >> 8);
                }
                else if (pixelFormat == rwRASTERFORMAT4444)
                {
                    raster->cFormat &= ~(rwRASTERFORMAT4444 >> 8);
                    raster->cFormat |= (rwRASTERFORMAT565 >> 8);
                }
                else if (pixelFormat == rwRASTERFORMAT1555)
                {
                    raster->cFormat &= ~(rwRASTERFORMAT1555 >> 8);
                    raster->cFormat |= (rwRASTERFORMAT565 >> 8);
                }
            }
        }
        else
        {
            rasExt->alpha = TRUE;
        }
    }

    texture = RwTextureCreate(raster);
    if (texture == NULL)
    {
        RwRasterDestroy(raster);
        return NULL;
    }

    if (RwRasterGetFormat(raster) & rwRASTERFORMATMIPMAP)
    {
        RwTextureSetFilterMode(texture, rwFILTERLINEARMIPLINEAR);
    }
    else
    {
        RwTextureSetFilterMode(texture, rwFILTERLINEAR);
    }

    /* Set the textures name */
    RwTextureSetName(texture, name);

    return texture;
}

// match: _RwXboxDDSTextureRead @ 0x002B2C00
// sp-match: _RwXboxDDSTextureRead @ 0x001CE020
RwTexture *
RwXboxDDSTextureRead(const RwChar *name, const RwChar *maskname __RWUNUSED__)
{
    RwChar      fullPathName[256];
    RwChar      *pathElement;

    pathElement = RwImageGetPath();

    if ((_rwpathisabsolute(name) != TRUE) &&
        (pathElement != NULL) &&
        (pathElement[0] != '\0'))
    {
        /* While we have a search path to try */
        while (pathElement && pathElement[0] != '\0')
        {
            RwChar      *nextPathElement = rwstrchr(pathElement, rwSEARCHPATH_SEPARATOR);
            RwInt32     pathElementLength;
            RwTexture   *texture;

            nextPathElement = rwstrchr(pathElement, rwSEARCHPATH_SEPARATOR);
            if (nextPathElement)
            {
                /* Length of pathstring (in bytes) */
                pathElementLength = (RwUInt8 *)nextPathElement - (RwUInt8*)pathElement;
                ++nextPathElement;  /* Skip the separator */
            }
            else
            {
                pathElementLength = rwstrlen(pathElement) * sizeof(RwChar);
            }

            /* Full path + full name */
            memcpy(fullPathName, pathElement, pathElementLength);
            rwstrcpy((RwChar *)(((RwUInt8 *)fullPathName) + pathElementLength), name);
            rwstrcat(fullPathName, ".dds");

            /* Try to load the texture */
            texture = XboxDXTTextureRead(name, fullPathName);
            if (texture)
            {
                return texture;
            }

            /* On to the next path */
            pathElement = nextPathElement;
        }

        return NULL;
    }
    else
    {
        const RwChar    *curChar;

        curChar = name + rwstrlen(name);

        do
        {
            --curChar;
        }
        while (curChar >= name &&
               '\\' != *curChar);

        rwstrcpy(fullPathName, name);
        rwstrcat(fullPathName, ".dds");

        return XboxDXTTextureRead(curChar + 1, fullPathName);
    }
}
