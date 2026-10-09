/*
 * codfh-match: RenderWare 3.6's Xbox driver 2D immediate mode
 * (driver/xbox/xb2drend.c), rebuilt from the image; names from the
 * Godfather PDB's copy of the driver.
 */

#include <xtl.h>
#include "batypes.h"
#include "batype.h"
#include "balibtyp.h"
#include "barwtyp.h"
#include "badebug.h"
#include "bamemory.h"
#include "badevice.h"
#include "bamatrix.h"
#include "baframe.h"
#include "bacamera.h"
#include "baraster.h"
#include "batextur.h"
#include "baimmedi.h"
#include "xbraster.h"
#include "xbdevice.h"
#include "xbmemory.h"
#include "xbcache.h"
#include "xbrendst.h"
#include "xb2drend.h"

/* The 2D vertex shaders' microcode. */
static const DWORD dw2DVertexShader[17] =
{
    0x00042078, 0x00000000, 0x042c201b, 0x0c3613fc, 0x2e001804, 0x00000000,
    0x0020021b, 0x0836106c, 0x2070f818, 0x00000000, 0x0020041b, 0x0836106c,
    0x2070c848, 0x00000000, 0x008c001a, 0x08341868, 0x1070e801
};

static const DWORD dw2DnotexVertexShader[13] =
{
    0x00032078, 0x00000000, 0x042c201b, 0x0c3613fc, 0x2e001804, 0x00000000,
    0x0020021b, 0x0836106c, 0x2070f818, 0x00000000, 0x008c001a, 0x08341868,
    0x1070e801
};

static const DWORD dw2DnocolorVertexShader[13] =
{
    0x00032078, 0x00000000, 0x042c201b, 0x0c3613fc, 0x2e001804, 0x00000000,
    0x0020021b, 0x0836106c, 0x2070c848, 0x00000000, 0x008c001a, 0x08341868,
    0x1070e801
};

/* RenderWare 3.6's RCS id string, which the image keeps, after the shaders (the 3.7.2 tree has none) */
static const char rcsid[] = "@@@@(#)$Id: //RenderWare/RW36Active/rwsdk/driver/xbox/xb2drend.c#3 $";

const D3DPRIMITIVETYPE RwXbPrimConvTable[7] =
{
    (D3DPRIMITIVETYPE)0,        /* rwPRIMTYPENAPRIMTYPE */
    D3DPT_LINELIST,             /* rwPRIMTYPELINELIST */
    D3DPT_LINESTRIP,            /* rwPRIMTYPEPOLYLINE */
    D3DPT_TRIANGLELIST,         /* rwPRIMTYPETRILIST */
    D3DPT_TRIANGLESTRIP,        /* rwPRIMTYPETRISTRIP */
    D3DPT_TRIANGLEFAN,          /* rwPRIMTYPETRIFAN */
    D3DPT_POINTLIST             /* rwPRIMTYPEPOINTLIST */
};

static const DWORD Xbox2DVertexShaderDecl[5] =
{
    D3DVSD_STREAM(0),
    D3DVSD_REG(0, D3DVSDT_FLOAT4),
    D3DVSD_REG(1, D3DVSDT_D3DCOLOR),
    D3DVSD_REG(2, D3DVSDT_FLOAT2),
    D3DVSD_END()
};

static const DWORD Xbox2DNoTexVertexShaderDecl[4] =
{
    D3DVSD_STREAM(0),
    D3DVSD_REG(0, D3DVSDT_FLOAT4),
    D3DVSD_REG(1, D3DVSDT_D3DCOLOR),
    D3DVSD_END()
};

static const DWORD Xbox2DNoColorVertexShaderDecl[4] =
{
    D3DVSD_STREAM(0),
    D3DVSD_REG(0, D3DVSDT_FLOAT4),
    D3DVSD_REG(1, D3DVSDT_FLOAT2),
    D3DVSD_END()
};

static DWORD Xbox2DVertexShader = 0;
static DWORD Xbox2DNoTexVertexShader = 0;
static DWORD Xbox2DNoColorVertexShader = 0;

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: _rcsid @ 0x004171F0
// match: _dw2DVertexShader @ 0x00417140
// match: _dw2DnotexVertexShader @ 0x00417184
// match: _dw2DnocolorVertexShader @ 0x004171B8
// match: _RwXbPrimConvTable @ 0x00417238
// match: _Xbox2DVertexShaderDecl @ 0x00417254
// match: _Xbox2DNoTexVertexShaderDecl @ 0x00417268
// match: _Xbox2DNoColorVertexShaderDecl @ 0x00417278

// match: __rwXbIm2DRenderOpen @ 0x002B9840
// sp-match: __rwXbIm2DRenderOpen @ 0x001D4C50

RwBool
_rwXbIm2DRenderOpen(void)
{
    if (D3D_OK != D3DDevice_CreateVertexShader(Xbox2DVertexShaderDecl, dw2DVertexShader,
                                               &Xbox2DVertexShader, 0))
    {
        return FALSE;
    }

    if (D3D_OK != D3DDevice_CreateVertexShader(Xbox2DNoTexVertexShaderDecl, dw2DnotexVertexShader,
                                               &Xbox2DNoTexVertexShader, 0))
    {
        return FALSE;
    }

    if (D3D_OK != D3DDevice_CreateVertexShader(Xbox2DNoColorVertexShaderDecl,
                                               dw2DnocolorVertexShader,
                                               &Xbox2DNoColorVertexShader, 0))
    {
        return FALSE;
    }

    return TRUE;
}

// match: __rwXbIm2DRenderClose @ 0x002B98A0
// sp-match: __rwXbIm2DRenderClose @ 0x001D4CB0
void
_rwXbIm2DRenderClose(void)
{
    if (Xbox2DNoColorVertexShader)
    {
        D3DDevice_DeleteVertexShader(Xbox2DNoColorVertexShader);
        Xbox2DNoColorVertexShader = 0;
    }

    if (Xbox2DNoTexVertexShader)
    {
        D3DDevice_DeleteVertexShader(Xbox2DNoTexVertexShader);
        Xbox2DNoTexVertexShader = 0;
    }

    if (Xbox2DVertexShader)
    {
        D3DDevice_DeleteVertexShader(Xbox2DVertexShader);
        Xbox2DVertexShader = 0;
    }
}

// match: __rwXbIm2DRenderSetVertexShader @ 0x002B98F0
// sp-match: __rwXbIm2DRenderSetVertexShader @ 0x001D4D00
void
_rwXbIm2DRenderSetVertexShader(RwBool diffuse, RwBool texcoords)
{
    RWALIGN(RwV4d, 16) offset;
    RWALIGN(RwV4d, 16) scale;

    if (texcoords)
    {
        if (diffuse)
        {
            RwXboxSetCurrentVertexShader(Xbox2DVertexShader);
        }
        else
        {
            RwXboxSetCurrentVertexShader(Xbox2DNoColorVertexShader);
        }
    }
    else
    {
        RwXboxSetCurrentVertexShader(Xbox2DNoTexVertexShader);
    }

    D3DDevice_GetViewportOffsetAndScale((D3DVECTOR4 *)&offset, (D3DVECTOR4 *)&scale);

    offset.x -= scale.x;
    offset.y += scale.y;
    offset.z = 0.0f;
    offset.w = 0.0f;

    D3DDevice_GetBackBufferScale(&scale.x, &scale.y);
    scale.w = 1.0f;

    D3DDevice_SetVertexShaderConstantFast(0, &scale, 1);
    D3DDevice_SetVertexShaderConstantFast(1, &offset, 1);
}

// match: _XbIm2DRenderSetup @ 0x002B99B0
// sp-match: _XbIm2DRenderSetup @ 0x001D4DC0
static void
XbIm2DRenderSetup(void)
{
    RwRaster           *raster;
    RWALIGN(RwV4d, 16) offset;
    RWALIGN(RwV4d, 16) scale;

    RwXboxSetCurrentPixelShader(0);

    _rwXbGetRenderState(rwRENDERSTATETEXTURERASTER, (void *)&raster);
    if (raster)
    {
        _rwXbTextureStageForce(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
        _rwXbTextureStageForce(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
        _rwXbTextureStageForce(0, D3DTSS_COLORARG2, D3DTA_TEXTURE);
        _rwXbTextureStageForce(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
        _rwXbTextureStageForce(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
        _rwXbTextureStageForce(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);

        RwXboxSetCurrentVertexShader(Xbox2DVertexShader);
    }
    else
    {
        _rwXbTextureStageForce(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
        _rwXbTextureStageForce(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
        _rwXbTextureStageForce(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
        _rwXbTextureStageForce(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);

        RwXboxSetCurrentVertexShader(Xbox2DNoTexVertexShader);
    }

    D3DDevice_GetViewportOffsetAndScale((D3DVECTOR4 *)&offset, (D3DVECTOR4 *)&scale);

    offset.x -= scale.x;
    offset.y += scale.y;
    offset.z = 0.0f;
    offset.w = 0.0f;

    D3DDevice_GetBackBufferScale(&scale.x, &scale.y);
    scale.w = 1.0f;

    D3DDevice_SetVertexShaderConstantFast(0, &scale, 1);
    D3DDevice_SetVertexShaderConstantFast(1, &offset, 1);
}

// match: __rwXbIm2DRenderLine @ 0x002B9BE0
// sp-match: __rwXbIm2DRenderLine @ 0x001D4FF0
RwBool
_rwXbIm2DRenderLine(rwXBOXVERTEX *verts, RwInt32 numVerts __RWUNUSED__,
                    RwInt32 vert1, RwInt32 vert2)
{
    rwXBOXVERTEX        vertex[2];

    vertex[0] = verts[vert1];
    vertex[1] = verts[vert2];

    XbIm2DRenderSetup();

    RwXboxDrawVerticesUP(D3DPT_LINELIST, 2, vertex, sizeof(rwXBOXVERTEX));

    return TRUE;
}

// match: __rwXbIm2DRenderTriangle @ 0x002B9C40
// sp-match: __rwXbIm2DRenderTriangle @ 0x001D5050
RwBool
_rwXbIm2DRenderTriangle(rwXBOXVERTEX *verts, RwInt32 numVerts __RWUNUSED__,
                        RwInt32 vert1, RwInt32 vert2, RwInt32 vert3)
{
    rwXBOXVERTEX        vertex[3];

    vertex[0] = verts[vert1];
    vertex[1] = verts[vert2];
    vertex[2] = verts[vert3];

    XbIm2DRenderSetup();

    RwXboxDrawVerticesUP(D3DPT_TRIANGLELIST, 3, vertex, sizeof(rwXBOXVERTEX));

    return TRUE;
}

// match: __rwXbIm2DRenderPrimitive @ 0x002B9CB0
// sp-match: __rwXbIm2DRenderPrimitive @ 0x001D50C0
RwBool
_rwXbIm2DRenderPrimitive(RwPrimitiveType primType, rwXBOXVERTEX *verts, RwInt32 numVerts)
{
    XbIm2DRenderSetup();

    _rwXbFlushCacheBuffer();

    D3DDevice_DrawVerticesUP(RwXbPrimConvTable[primType], numVerts, verts,
                             sizeof(rwXBOXVERTEX));

    return TRUE;
}

// match: __rwXbIm2DRenderIndexedPrimitive @ 0x002B9CE0
// sp-match: __rwXbIm2DRenderIndexedPrimitive @ 0x001D50F0
RwBool
_rwXbIm2DRenderIndexedPrimitive(RwPrimitiveType primType,
                                rwXBOXVERTEX *verts,
                                RwInt32 numVerts,
                                RwImVertexIndex *indices,
                                RwInt32 numIndices)
{
    RwUInt8 *bufferMem;

    bufferMem = RwXboxLockDynamicVertexBuffer(numVerts * sizeof(rwXBOXVERTEX));

    /* Copy the vertices with non-temporal stores, two at a time */
    __asm
    {
        mov     eax, numVerts
        mov     esi, verts
        mov     ecx, eax
        mov     edi, bufferMem
        shr     ecx, 1
        jz      indexedcopy1

indexedcopy2:
        prefetchnta [esi + 64]
        prefetchnta [esi + 96]
        movq    mm0, qword ptr [esi]
        movq    mm1, qword ptr [esi + 8]
        movq    mm2, qword ptr [esi + 16]
        movq    mm3, qword ptr [esi + 24]
        movq    mm4, qword ptr [esi + 32]
        movq    mm5, qword ptr [esi + 40]
        movq    mm6, qword ptr [esi + 48]
        movntq  qword ptr [edi], mm0
        movntq  qword ptr [edi + 8], mm1
        movntq  qword ptr [edi + 16], mm2
        movntq  qword ptr [edi + 24], mm3
        movntq  qword ptr [edi + 32], mm4
        movntq  qword ptr [edi + 40], mm5
        movntq  qword ptr [edi + 48], mm6
        add     esi, 56
        add     edi, 56
        dec     ecx
        jnz     indexedcopy2

indexedcopy1:
        and     eax, 1
        jz      indexedcopyend
        movq    mm0, qword ptr [esi]
        movq    mm1, qword ptr [esi + 8]
        movq    mm2, qword ptr [esi + 16]
        mov     eax, [esi + 24]
        movntq  qword ptr [edi], mm0
        movntq  qword ptr [edi + 8], mm1
        movntq  qword ptr [edi + 16], mm2
        mov     [edi + 24], eax

indexedcopyend:
        emms
    }

    RwXboxSetCurrentStream(sizeof(rwXBOXVERTEX));

    XbIm2DRenderSetup();

    _rwXbFlushCacheBuffer();

    D3DDevice_DrawIndexedVertices(RwXbPrimConvTable[primType], numIndices, indices);

    return TRUE;
}
