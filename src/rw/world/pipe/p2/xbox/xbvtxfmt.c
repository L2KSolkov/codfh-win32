/*
 * codfh-match: RenderWare 3.6's Xbox vertex formats
 * (world/pipe/p2/xbox/xbvtxfmt.c), rebuilt from the image; names from the
 * Godfather PDB's copy of the same file.
 */

#include <xtl.h>
#include <stdlib.h>
#include <string.h>

#include <rwcore.h>
#include "bamateri.h"
#include "baworld.h"
#include "bageomet.h"

#include "xbpipe.h"
#include "xbvtxfmt.h"

/* RenderWare 3.6's RCS id string, which the image keeps (the 3.7.2 tree has none) */
static const char rcsid[] = "@@@@(#)$Id: //RenderWare/RW36Active/rwsdk/world/pipe/p2/xbox/xbvtxfmt.c#1 $";

/****************************************************************************
 Globals
 */

RwModuleInfo RpVtxFmtModule;
RwInt32 _rpXboxGeomVtxFmtOffset = 0;
RwInt32 rpXboxWorldVtxFmtOffset = 0;
/* codfh-match: static here (only this file uses them, and the loops keep
 * the array pointer in a register across stores); public in Godfather's 3.7 */
static _rpXboxVtxFmtDescItem *rwXboxVertexFormatArray = NULL;
static RwInt32 rwXboxVertexFormatMaxElems = 0;
static RwInt32 rwXboxVertexFormatNumElems = 0;
static RwBool rwXboxVertexFormatArrayInited = FALSE;

/* The size of each component type. */
const RwUInt32 RpXboxCompSize[rpCOMPTYPEMAX] =
{
    0,                  /* rpCOMPTYPENONE */
    sizeof(RwUInt8),    /* rpPACKEDBYTE */
    sizeof(RwInt16),    /* rpSHORT */
    sizeof(RwInt16),    /* rpNORMALIZEDSHORTS */
    sizeof(RwUInt32),   /* rpNORMALIZEDPACKED */
    sizeof(RwReal)      /* rpFLOAT */
};

/* The vertex registers of the four texture coordinate sets. */
const RwUInt32 rpWorldVSDETexFlags[4] =
{
    D3DVSDE_TEXCOORD0,
    D3DVSDE_TEXCOORD1,
    D3DVSDE_TEXCOORD2,
    D3DVSDE_TEXCOORD3
};

/* The plugin's constructor and destructor: nothing to do. /OPT:ICF folded it
 * into colldata.c's CollisionDataConstructor (aliased), so it has no place of
 * its own here. */
static void *
rxXboxVertexFmtConst(void *object,
                     RwInt32 offsetInObject __RWUNUSED__,
                     RwInt32 sizeInObject __RWUNUSED__)
{
    return object;
}

/* Finds fmt in the sorted buffer: its index, or -(insertion point + 1).
 * /OPT:ICF kept the skin plugin's identical copy, SkinBinaryFindVertexFormat. */
// match: _BinaryFindVertexFormat @ 0x002D43D0
static RwInt32
BinaryFindVertexFormat(const RpXboxVtxFmt *value,
                       const _rpXboxVtxFmtDescItem *buffer,
                       RwInt32 numElems)
{
    RwInt32     lowerValue = 0;
    RwInt32     higherValue;
    RwInt32     midleValue;

    if (numElems > 0)
    {
        higherValue = numElems - 1;

        do
        {
            if (numElems <= 1)
            {
                if (*(const RwUInt32 *)value == *(const RwUInt32 *)&buffer[lowerValue].format)
                {
                    return lowerValue;
                }

                if (*(const RwUInt32 *)value < *(const RwUInt32 *)&buffer[lowerValue].format)
                {
                    return -(lowerValue + 1);
                }

                return -(lowerValue + 2);
            }

            midleValue = lowerValue + numElems / 2 - (1 - (numElems & 1));

            if (*(const RwUInt32 *)value == *(const RwUInt32 *)&buffer[midleValue].format)
            {
                return midleValue;
            }

            if (*(const RwUInt32 *)value < *(const RwUInt32 *)&buffer[midleValue].format)
            {
                higherValue = midleValue - 1;
            }
            else
            {
                lowerValue = midleValue + 1;
            }

            numElems = higherValue - lowerValue + 1;
        }
        while (numElems > 0);
    }

    return -(lowerValue + 1);
}

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: _rcsid @ 0x00419338
// match: __real@3c000000 @ 0x0040B904
// match: __real@2b8cbccc @ 0x0040FCC4
// match: _RpXboxCompSize @ 0x00419384
// match: _rpWorldVSDETexFlags @ 0x0041939C
// match: __real@3d71979980000000 @ 0x004193B8
// match: __real@3b004020 @ 0x004193C0
// match: __real@3a802008 @ 0x004193C4

// match: _rwXboxVertexFormatCreate @ 0x002DCB70

void
rwXboxVertexFormatCreate(void)
{
    if (!rwXboxVertexFormatArrayInited)
    {
        RwInt32 i;

        rwXboxVertexFormatMaxElems = 128;
        rwXboxVertexFormatArray = (_rpXboxVtxFmtDescItem *)
            RwMalloc(sizeof(_rpXboxVtxFmtDescItem) * rwXboxVertexFormatMaxElems,
                     rwID_WORLDPIPEMODULE | rwMEMHINTDUR_GLOBAL |
                     rwMEMHINTFLAG_RESIZABLE);

        for (i = 0; i < rwXboxVertexFormatMaxElems; i++)
        {
            rwXboxVertexFormatArray[i].handle = 0;
        }

        rwXboxVertexFormatNumElems = 0;
        rwXboxVertexFormatArrayInited = TRUE;
    }
}

// match: _rwXboxVertexFormatDestroy @ 0x002DCBE0
void
rwXboxVertexFormatDestroy(void)
{
    if (rwXboxVertexFormatArrayInited)
    {
        RwInt32 i;

        for (i = 0; i < rwXboxVertexFormatNumElems; i++)
        {
            if (rwXboxVertexFormatArray[i].handle)
            {
                D3DDevice_DeleteVertexShader(rwXboxVertexFormatArray[i].handle);
                rwXboxVertexFormatArray[i].handle = 0;
            }
        }

        RwFree(rwXboxVertexFormatArray);
        rwXboxVertexFormatArray = NULL;

        rwXboxVertexFormatMaxElems = 0;
        rwXboxVertexFormatNumElems = 0;
        rwXboxVertexFormatArrayInited = FALSE;
    }
}

// match: __rpXboxVtxFmtGetSize @ 0x002DCC50
RwUInt32
_rpXboxVtxFmtGetSize(RpXboxCompType type, RwUInt32 numElems)
{
    if (type == rpNORMALIZEDPACKED)
    {
        return 4;
    }

    return RpXboxCompSize[type] * numElems;
}

// match: __rpXboxVtxFmtGetStride @ 0x002DCC70
RwUInt32
_rpXboxVtxFmtGetStride(const RpXboxVtxFmt *fmt)
{
    RwUInt32    stride = 0;

    if (fmt->pos)
    {
        if (fmt->pos == rpNORMALIZEDPACKED)
        {
            stride = 4;
        }
        else
        {
            stride = 3 * RpXboxCompSize[fmt->pos];
        }
    }

    if (fmt->norm)
    {
        if (fmt->norm == rpNORMALIZEDPACKED)
        {
            stride += 4;
        }
        else
        {
            stride += 3 * RpXboxCompSize[fmt->norm];
        }
    }

    if (fmt->prelit)
    {
        stride += 4;
    }

    if (fmt->bnt)
    {
        stride += 8;
    }

    if (fmt->texCoord)
    {
        RwInt32 i;

        for (i = 0; i < 4; i++)
        {
            RpXboxCompType type = (RpXboxCompType)((fmt->texCoord >> (4 * i)) & 0xF);

            if (type == rpCOMPTYPENONE)
            {
                break;
            }

            if (type == rpNORMALIZEDPACKED)
            {
                stride += 4;
            }
            else
            {
                stride += 2 * RpXboxCompSize[type];
            }
        }
    }

    return stride;
}

// match: __rpXboxVtxFmtInstV3d @ 0x002DCD20
RwUInt32
_rpXboxVtxFmtInstV3d(RpXboxCompType type, RwUInt8 *mem, const RwV3d *src,
                     RwInt32 numVerts, RwUInt32 stride)
{
    switch (type)
    {
        case rpPACKEDBYTE:
            {
                RwUInt8 *dstPosition = mem;
                RwInt32 i;

                for (i = 0; i < numVerts; i++)
                {
                    dstPosition[0] = (RwUInt8)RwFastRealToUInt32(src->x * 255.0f);
                    dstPosition[1] = (RwUInt8)RwFastRealToUInt32(src->y * 255.0f);
                    dstPosition[2] = (RwUInt8)RwFastRealToUInt32(src->z * 255.0f);

                    src++;
                    dstPosition += stride;
                }
            }
            break;

        case rpSHORT:
            {
                RwUInt8 *dstPosition = mem;
                RwInt32 i;

                for (i = 0; i < numVerts; i++)
                {
                    ((RwInt16 *)dstPosition)[0] = (RwInt16)RwFastRealToUInt32(src->x);
                    ((RwInt16 *)dstPosition)[1] = (RwInt16)RwFastRealToUInt32(src->y);
                    ((RwInt16 *)dstPosition)[2] = (RwInt16)RwFastRealToUInt32(src->z);

                    src++;
                    dstPosition += stride;
                }
            }
            break;

        case rpNORMALIZEDSHORTS:
            {
                RwUInt8 *dstPosition = mem;
                RwInt32 i;

                for (i = 0; i < numVerts; i++)
                {
                    ((RwInt16 *)dstPosition)[0] = (RwInt16)RwFastRealToUInt32(src->x * 32767.0f);
                    ((RwInt16 *)dstPosition)[1] = (RwInt16)RwFastRealToUInt32(src->y * 32767.0f);
                    ((RwInt16 *)dstPosition)[2] = (RwInt16)RwFastRealToUInt32(src->z * 32767.0f);

                    src++;
                    dstPosition += stride;
                }
            }
            break;

        case rpNORMALIZEDPACKED:
            {
                RwUInt8 *dstPosition = mem;
                RwInt32 i;

                for (i = 0; i < numVerts; i++)
                {
                    RwUInt32    nx, ny, nz;

                    nx = RwFastRealToUInt32(src->x * 1023.0f) & 0x7FF;
                    ny = RwFastRealToUInt32(src->y * 1023.0f) & 0x7FF;
                    nz = RwFastRealToUInt32(src->z * 511.0f) & 0x3FF;

                    *(RwUInt32 *)dstPosition = (nz << 22) | (ny << 11) | nx;

                    src++;
                    dstPosition += stride;
                }
            }
            break;

        case rpFLOAT:
            if (stride == sizeof(RwV3d))
            {
                __asm
                {
                    mov     eax, numVerts
                    lea     eax, [eax + eax * 2]
                    mov     esi, src
                    mov     ecx, eax
                    mov     edi, mem
                    shr     ecx, 1
instv3dcopybegin:
                    movq    mm0, qword ptr [esi]
                    movntq  qword ptr [edi], mm0
                    add     esi, 8
                    add     edi, 8
                    dec     ecx
                    jnz     instv3dcopybegin
                    and     eax, 1
                    jz      instv3dend
                    mov     eax, [esi]
                    mov     [edi], eax
instv3dend:
                    emms
                }
            }
            else
            {
                RwUInt8 *dstPosition = mem;
                RwInt32 i;

                for (i = 0; i < numVerts; i++)
                {
                    *(RwV3d *)dstPosition = *src;

                    src++;
                    dstPosition += stride;
                }
            }
            break;
    }

    if (type == rpNORMALIZEDPACKED)
    {
        return 4;
    }

    return 3 * RpXboxCompSize[type];
}

// match: __rpXboxVtxFmtInstV3dComp @ 0x002DCFA0
RwUInt32
_rpXboxVtxFmtInstV3dComp(RpXboxCompType type, RwUInt8 *mem, const RpVertexNormal *src,
                         RwInt32 numVerts, RwUInt32 stride)
{
    switch (type)
    {
        case rpPACKEDBYTE:
            {
                RwUInt8 *dstPosition = mem;
                RwInt32 i;

                for (i = 0; i < numVerts; i++)
                {
                    RwReal  temp[3];

                    temp[0] = ((RwReal)src->x) * (1.0f / 128.0f);
                    temp[1] = ((RwReal)src->y) * (1.0f / 128.0f);
                    temp[2] = ((RwReal)src->z) * (1.0f / 128.0f);

                    dstPosition[0] = (RwUInt8)RwFastRealToUInt32(temp[0] * 255.0f);
                    dstPosition[1] = (RwUInt8)RwFastRealToUInt32(temp[1] * 255.0f);
                    dstPosition[2] = (RwUInt8)RwFastRealToUInt32(temp[2] * 255.0f);

                    src++;
                    dstPosition += stride;
                }
            }
            break;

        case rpSHORT:
            {
                RwUInt8 *dstPosition = mem;
                RwInt32 i;

                for (i = 0; i < numVerts; i++)
                {
                    RwReal  temp[3];

                    temp[0] = ((RwReal)src->x) * (1.0f / 128.0f);
                    temp[1] = ((RwReal)src->y) * (1.0f / 128.0f);
                    temp[2] = ((RwReal)src->z) * (1.0f / 128.0f);

                    ((RwInt16 *)dstPosition)[0] = (RwInt16)RwFastRealToUInt32(temp[0]);
                    ((RwInt16 *)dstPosition)[1] = (RwInt16)RwFastRealToUInt32(temp[1]);
                    ((RwInt16 *)dstPosition)[2] = (RwInt16)RwFastRealToUInt32(temp[2]);

                    src++;
                    dstPosition += stride;
                }
            }
            break;

        case rpNORMALIZEDSHORTS:
            {
                RwUInt8 *dstPosition = mem;
                RwInt32 i;

                for (i = 0; i < numVerts; i++)
                {
                    RwReal  temp[3];

                    temp[0] = ((RwReal)src->x) * (1.0f / 128.0f);
                    temp[1] = ((RwReal)src->y) * (1.0f / 128.0f);
                    temp[2] = ((RwReal)src->z) * (1.0f / 128.0f);

                    ((RwInt16 *)dstPosition)[0] = (RwInt16)RwFastRealToUInt32(temp[0] * 32767.0f);
                    ((RwInt16 *)dstPosition)[1] = (RwInt16)RwFastRealToUInt32(temp[1] * 32767.0f);
                    ((RwInt16 *)dstPosition)[2] = (RwInt16)RwFastRealToUInt32(temp[2] * 32767.0f);

                    src++;
                    dstPosition += stride;
                }
            }
            break;

        case rpNORMALIZEDPACKED:
            {
                RwUInt8 *dstPosition = mem;
                RwInt32 i;

                for (i = 0; i < numVerts; i++)
                {
                    RwReal      temp[3];
                    RwUInt32    nx, ny, nz;

                    temp[0] = ((RwReal)src->x) * (1.0f / 128.0f);
                    temp[1] = ((RwReal)src->y) * (1.0f / 128.0f);
                    temp[2] = ((RwReal)src->z) * (1.0f / 128.0f);

                    nx = RwFastRealToUInt32(temp[0] * 1023.0f) & 0x7FF;
                    ny = RwFastRealToUInt32(temp[1] * 1023.0f) & 0x7FF;
                    nz = RwFastRealToUInt32(temp[2] * 511.0f) & 0x3FF;

                    *(RwUInt32 *)dstPosition = (nz << 22) | (ny << 11) | nx;

                    src++;
                    dstPosition += stride;
                }
            }
            break;

        case rpFLOAT:
            {
                RwUInt8 *dstPosition = mem;
                RwInt32 i;

                for (i = 0; i < numVerts; i++)
                {
                    ((RwReal *)dstPosition)[0] = ((RwReal)src->x) * (1.0f / 128.0f);
                    ((RwReal *)dstPosition)[1] = ((RwReal)src->y) * (1.0f / 128.0f);
                    ((RwReal *)dstPosition)[2] = ((RwReal)src->z) * (1.0f / 128.0f);

                    src++;
                    dstPosition += stride;
                }
            }
            break;
    }

    if (type == rpNORMALIZEDPACKED)
    {
        return 4;
    }

    return 3 * RpXboxCompSize[type];
}

// match: __rpXboxVtxFmtInstV3dMorph @ 0x002DD3B0
RwUInt32
_rpXboxVtxFmtInstV3dMorph(RpXboxCompType type, RwUInt8 *mem,
                          const RwV3d *src1, const RwV3d *src2, RwReal scale,
                          RwInt32 numVerts, RwUInt32 stride)
{
    switch (type)
    {
        case rpPACKEDBYTE:
            {
                RwReal  minusScale = (1.0f - scale) * 255.0f;
                RwUInt8 *dstPosition = mem;
                RwInt32 i;

                scale *= 255.0f;

                for (i = 0; i < numVerts; i++)
                {
                    dstPosition[0] = (RwUInt8)RwFastRealToUInt32(minusScale * src1->x + scale * src2->x);
                    dstPosition[1] = (RwUInt8)RwFastRealToUInt32(minusScale * src1->y + scale * src2->y);
                    dstPosition[2] = (RwUInt8)RwFastRealToUInt32(minusScale * src1->z + scale * src2->z);

                    src1++;
                    src2++;
                    dstPosition += stride;
                }
            }
            break;

        case rpSHORT:
            {
                RwUInt8 *dstPosition = mem;
                RwInt32 i;

                for (i = 0; i < numVerts; i++)
                {
                    ((RwInt16 *)dstPosition)[0] = (RwInt16)RwFastRealToUInt32((src2->x - src1->x) * scale + src1->x);
                    ((RwInt16 *)dstPosition)[1] = (RwInt16)RwFastRealToUInt32((src2->y - src1->y) * scale + src1->y);
                    ((RwInt16 *)dstPosition)[2] = (RwInt16)RwFastRealToUInt32((src2->z - src1->z) * scale + src1->z);

                    src1++;
                    src2++;
                    dstPosition += stride;
                }
            }
            break;

        case rpNORMALIZEDSHORTS:
            {
                RwReal  minusScale = (1.0f - scale) * 32767.0f;
                RwUInt8 *dstPosition = mem;
                RwInt32 i;

                scale *= 32767.0f;

                for (i = 0; i < numVerts; i++)
                {
                    ((RwInt16 *)dstPosition)[0] = (RwInt16)RwFastRealToUInt32(minusScale * src1->x + scale * src2->x);
                    ((RwInt16 *)dstPosition)[1] = (RwInt16)RwFastRealToUInt32(minusScale * src1->y + scale * src2->y);
                    ((RwInt16 *)dstPosition)[2] = (RwInt16)RwFastRealToUInt32(minusScale * src1->z + scale * src2->z);

                    src1++;
                    src2++;
                    dstPosition += stride;
                }
            }
            break;

        case rpNORMALIZEDPACKED:
            {
                RwReal  minusScale11 = (1.0f - scale) * 1023.0f;
                RwReal  scale11 = scale * 1023.0f;
                RwReal  minusScale10 = (1.0f - scale) * 511.0f;
                RwReal  scale10 = scale * 511.0f;
                RwUInt8 *dstPosition = mem;
                RwInt32 i;

                for (i = 0; i < numVerts; i++)
                {
                    RwUInt32    nx, ny, nz;

                    nx = RwFastRealToUInt32(minusScale11 * src1->x + scale11 * src2->x) & 0x7FF;
                    ny = RwFastRealToUInt32(minusScale11 * src1->y + scale11 * src2->y) & 0x7FF;
                    nz = RwFastRealToUInt32(minusScale10 * src1->z + scale10 * src2->z) & 0x3FF;

                    *(RwUInt32 *)dstPosition = (nz << 22) | (ny << 11) | nx;

                    src1++;
                    src2++;
                    dstPosition += stride;
                }
            }
            break;

        case rpFLOAT:
            {
                RwUInt8 *dstPosition = mem;
                RwInt32 i;

                for (i = 0; i < numVerts; i++)
                {
                    ((RwV3d *)dstPosition)->x = (src2->x - src1->x) * scale + src1->x;
                    ((RwV3d *)dstPosition)->y = (src2->y - src1->y) * scale + src1->y;
                    ((RwV3d *)dstPosition)->z = (src2->z - src1->z) * scale + src1->z;

                    src1++;
                    src2++;
                    dstPosition += stride;
                }
            }
            break;
    }

    if (type == rpNORMALIZEDPACKED)
    {
        return 4;
    }

    return 3 * RpXboxCompSize[type];
}

// match: __rpXboxVtxFmtInstV2d @ 0x002DD8F0
RwUInt32
_rpXboxVtxFmtInstV2d(RpXboxCompType type, RwUInt8 *mem, const RwTexCoords *src,
                     RwInt32 numVerts, RwUInt32 stride)
{
    switch (type)
    {
        case rpPACKEDBYTE:
            {
                RwUInt8 *dstPosition = mem;
                RwInt32 i;

                for (i = 0; i < numVerts; i++)
                {
                    dstPosition[0] = (RwUInt8)RwFastRealToUInt32(src->u * 255.0f);
                    dstPosition[1] = (RwUInt8)RwFastRealToUInt32(src->v * 255.0f);

                    src++;
                    dstPosition += stride;
                }
            }
            break;

        case rpSHORT:
            {
                RwUInt8 *dstPosition = mem;
                RwInt32 i;

                for (i = 0; i < numVerts; i++)
                {
                    ((RwInt16 *)dstPosition)[0] = (RwInt16)RwFastRealToUInt32(src->u);
                    ((RwInt16 *)dstPosition)[1] = (RwInt16)RwFastRealToUInt32(src->v);

                    src++;
                    dstPosition += stride;
                }
            }
            break;

        case rpNORMALIZEDSHORTS:
            {
                RwUInt8 *dstPosition = mem;
                RwInt32 i;

                for (i = 0; i < numVerts; i++)
                {
                    ((RwInt16 *)dstPosition)[0] = (RwInt16)RwFastRealToUInt32(src->u * 32767.0f);
                    ((RwInt16 *)dstPosition)[1] = (RwInt16)RwFastRealToUInt32(src->v * 32767.0f);

                    src++;
                    dstPosition += stride;
                }
            }
            break;

        case rpNORMALIZEDPACKED:
            {
                RwUInt8 *dstPosition = mem;
                RwInt32 i;

                for (i = 0; i < numVerts; i++)
                {
                    RwUInt32    nx, ny;

                    nx = RwFastRealToUInt32(src->u * 1023.0f) & 0x7FF;
                    ny = RwFastRealToUInt32(src->v * 1023.0f) & 0x7FF;

                    *(RwUInt32 *)dstPosition = (ny << 11) | nx;

                    src++;
                    dstPosition += stride;
                }
            }
            break;

        case rpFLOAT:
            {
                RwUInt8 *dstPosition = mem;
                RwInt32 i;

                for (i = 0; i < numVerts; i++)
                {
                    *(RwTexCoords *)dstPosition = *src;

                    src++;
                    dstPosition += stride;
                }
            }
            break;
    }

    if (type == rpNORMALIZEDPACKED)
    {
        return 4;
    }

    return 2 * RpXboxCompSize[type];
}

// match: __rpXboxVtxFmtInstColor @ 0x002DDAF0
RwBool
_rpXboxVtxFmtInstColor(RwUInt8 *dst, const RwRGBA *src,
                       RwInt32 numVerts, RwUInt32 stride)
{
    RwUInt32   *dstColor;
    RwInt32     i;
    RwUInt8     alpha = 0xFF;

    dstColor = (RwUInt32 *)dst;
    for (i = 0; i < numVerts; i++)
    {
        *dstColor = ((RwUInt32)src[i].blue) |
                    ((RwUInt32)src[i].green << 8) |
                    ((RwUInt32)src[i].red << 16) |
                    ((RwUInt32)src[i].alpha << 24);

        alpha &= src[i].alpha;

        dstColor = (RwUInt32 *)(((RwUInt8 *)dstColor) + stride);
    }

    return (alpha != 0xFF);
}

/* Local helper preserves the normal-component reads at 0x2DDFBE and
 * 0x2DDFCC. Qualifiers encode observed load order, not recovered types. */
static __forceinline RwReal
XbVtxFmtCrossZ(const RwV3d *a, const RwV3d *b)
{
    return a->x * ((const volatile RwV3d *)b)->y -
           ((const volatile RwV3d *)b)->x * a->y;
}

#define XbVtxFmtCrossMacro(o, a, b)                         \
MACRO_START                                                     \
{                                                               \
    (o)->x =                                                    \
        (( (((a)->y) * ( (b)->z))) -                            \
         ( (((a)->z) * ( (b)->y))));                            \
    (o)->y =                                                    \
        (( (((a)->z) * ( (b)->x))) -                            \
         ( (((a)->x) * ( (b)->z))));                            \
    (o)->z = XbVtxFmtCrossZ((a), (b)); \
}                                                               \
MACRO_STOP
#define BNT_SMALL_FLOAT 1e-12f
// match: __rpXboxVtxFmtInstBNT @ 0x002DDB50
RwUInt32
_rpXboxVtxFmtInstBNT(RwUInt8 *mem,
                     const RwV3d *pos,
                     const RwV3d *normal,
                     const RwTexCoords *texCoord,
                     RxXboxResEntryHeader *instancedHeader,
                     RwInt32 numVerts,
                     RwUInt32 stride)
{
    RwV3d               *tangent, *binormal;
    RxXboxInstanceData  *mesh;
    RwInt32             n;
    RwReal              unused;

    tangent = (RwV3d *)RwMalloc(sizeof(RwV3d) * instancedHeader->numVertices,
                                rwMEMHINTDUR_FUNCTION | rwID_WORLDPIPEMODULE);
    memset(tangent, 0, sizeof(RwV3d) * instancedHeader->numVertices);

    binormal = (RwV3d *)RwMalloc(sizeof(RwV3d) * instancedHeader->numVertices,
                                 rwMEMHINTDUR_FUNCTION | rwID_WORLDPIPEMODULE);

    for (mesh = instancedHeader->begin; mesh != instancedHeader->end; mesh++)
    {
        const RwUInt16  *indexBuffer = mesh->indexBuffer;
        RwInt32         numIndices = mesh->numIndices;

        if (instancedHeader->primType == D3DPT_TRIANGLESTRIP)
        {
            numIndices -= 2;
        }

        n = 0;
        while (n < numIndices)
        {
            RwUInt32            i1, i2, i3;
            const RwV3d         *vert1, *vert2, *vert3;
            const RwTexCoords   *uv1, *uv2, *uv3;
            RwV3d               *tang1, *tang2, *tang3;
            RwV3d               edge01, edge02, cp;

            if (instancedHeader->primType == D3DPT_TRIANGLELIST)
            {
                i1 = indexBuffer[n + 0];
                i2 = indexBuffer[n + 1];
                i3 = indexBuffer[n + 2];

                n += 3;
            }
            else
            {
                if (n & 0x01)
                {
                    i1 = indexBuffer[n + 2];
                    i2 = indexBuffer[n + 1];
                    i3 = indexBuffer[n + 0];
                }
                else
                {
                    i1 = indexBuffer[n + 0];
                    i2 = indexBuffer[n + 1];
                    i3 = indexBuffer[n + 2];
                }

                ++n;

                if (i1 == i2 || i1 == i3 || i2 == i3)
                {
                    continue;
                }
            }

            vert1 = pos + i1;
            vert2 = pos + i2;
            vert3 = pos + i3;

            uv1 = texCoord + i1;
            uv2 = texCoord + i2;
            uv3 = texCoord + i3;

            tang1 = tangent + i1;
            tang2 = tangent + i2;
            tang3 = tangent + i3;

            /* x, s, t */
            edge01.x = vert2->x - vert1->x;
            edge01.y = uv2->u - uv1->u;
            edge01.z = uv2->v - uv1->v;

            edge02.x = vert3->x - vert1->x;
            edge02.y = uv3->u - uv1->u;
            edge02.z = uv3->v - uv1->v;

            RwV3dCrossProduct(&cp, &edge01, &edge02);
            if ((RwReal)fabs(cp.x) > BNT_SMALL_FLOAT)
            {
                const RwReal    invcpx = 1.0f / cp.x;

                tang1->x -= cp.y * invcpx;
                tang2->x -= cp.y * invcpx;
                tang3->x -= cp.y * invcpx;
            }

            /* y, s, t */
            edge01.x = vert2->y - vert1->y;
            edge02.x = vert3->y - vert1->y;

            RwV3dCrossProduct(&cp, &edge01, &edge02);
            if ((RwReal)fabs(cp.x) > BNT_SMALL_FLOAT)
            {
                const RwReal    invcpx = 1.0f / cp.x;

                tang1->y -= cp.y * invcpx;
                tang2->y -= cp.y * invcpx;
                tang3->y -= cp.y * invcpx;
            }

            /* z, s, t */
            edge01.x = vert2->z - vert1->z;
            edge02.x = vert3->z - vert1->z;

            RwV3dCrossProduct(&cp, &edge01, &edge02);
            if ((RwReal)fabs(cp.x) > BNT_SMALL_FLOAT)
            {
                const RwReal    invcpx = 1.0f / cp.x;

                tang1->z -= cp.y * invcpx;
                tang2->z -= cp.y * invcpx;
                tang3->z -= cp.y * invcpx;
            }
        }
    }

    /* Normalize the tangents and build the binormals */
    for (n = 0; n < instancedHeader->numVertices; n++)
    {
        const RwV3d *currentNormal = normal + n;
        RwV3d *currentTangent = tangent + n;
        RwV3d   *currentBinormal = binormal + n;

        _rwV3dNormalizeMacro(unused, currentTangent, currentTangent);

        XbVtxFmtCrossMacro(currentBinormal, currentTangent, currentNormal);

        {
            RwReal length2 = currentBinormal->y * currentBinormal->y;
            length2 += currentBinormal->x * currentBinormal->x;
            length2 += currentBinormal->z * currentBinormal->z;

            rwInvSqrtMacro(&unused, length2);
            currentBinormal->x = unused * currentBinormal->x;
            currentBinormal->y = unused * currentBinormal->y;
            currentBinormal->z = unused * currentBinormal->z;
        }
    }

    _rpXboxVtxFmtInstV3d(rpNORMALIZEDPACKED, mem, tangent, numVerts, stride);
    _rpXboxVtxFmtInstV3d(rpNORMALIZEDPACKED, mem + 4, binormal, numVerts, stride);

    RwFree(binormal);
    RwFree(tangent);

    return 8;
}

/* Local scale variant preserves the y-component read seen at 0x2DE4F9.
 * This records instruction order, not an original volatile declaration. */
#define XbVtxFmtScaleTangentMacro(o, a, s)                                \
MACRO_START                                                     \
{                                                               \
    (o)->x = (((a)->x) * ( (s)));                               \
    (o)->y = ((((const volatile RwV3d *)(a))->y) * ( (s)));                               \
    (o)->z = (((a)->z) * ( (s)));                               \
}                                                               \
MACRO_STOP
#define BNTCOMP_SMALL_FLOAT 9.999999960041972e-13
// match: __rpXboxVtxFmtInstBNTComp @ 0x002DE0F0
RwUInt32
_rpXboxVtxFmtInstBNTComp(RwUInt8 *mem,
                     const RwV3d *pos,
                     const RpVertexNormal *normal,
                     const RwTexCoords *texCoord,
                     RxXboxResEntryHeader *instancedHeader,
                     RwInt32 numVerts,
                     RwUInt32 stride)
{
    RwV3d               *tangent, *binormal;
    RxXboxInstanceData  *mesh;
    RwInt32             n;
    RwReal              unused;

    tangent = (RwV3d *)RwMalloc(sizeof(RwV3d) * instancedHeader->numVertices,
                                rwMEMHINTDUR_FUNCTION | rwID_WORLDPIPEMODULE);
    memset(tangent, 0, sizeof(RwV3d) * instancedHeader->numVertices);

    binormal = (RwV3d *)RwMalloc(sizeof(RwV3d) * instancedHeader->numVertices,
                                 rwMEMHINTDUR_FUNCTION | rwID_WORLDPIPEMODULE);

    for (mesh = instancedHeader->begin; mesh != instancedHeader->end; mesh++)
    {
        const RwUInt16  *indexBuffer = mesh->indexBuffer;
        RwInt32         numIndices = mesh->numIndices;

        if (instancedHeader->primType == D3DPT_TRIANGLESTRIP)
        {
            numIndices -= 2;
        }

        n = 0;
        while (n < numIndices)
        {
            RwUInt32            i1, i2, i3;
            const RwV3d         *vert1, *vert2, *vert3;
            const RwTexCoords   *uv1, *uv2, *uv3;
            RwV3d               *tang1, *tang2, *tang3;
            RwV3d               edge01, edge02, cp;

            if (instancedHeader->primType == D3DPT_TRIANGLELIST)
            {
                i1 = indexBuffer[n + 0];
                i2 = indexBuffer[n + 1];
                i3 = indexBuffer[n + 2];

                n += 3;
            }
            else
            {
                if (n & 0x01)
                {
                    i1 = indexBuffer[n + 2];
                    i2 = indexBuffer[n + 1];
                    i3 = indexBuffer[n + 0];
                }
                else
                {
                    i1 = indexBuffer[n + 0];
                    i2 = indexBuffer[n + 1];
                    i3 = indexBuffer[n + 2];
                }

                ++n;

                if (i1 == i2 || i1 == i3 || i2 == i3)
                {
                    continue;
                }
            }

            vert1 = pos + i1;
            vert2 = pos + i2;
            vert3 = pos + i3;

            uv1 = texCoord + i1;
            uv2 = texCoord + i2;
            uv3 = texCoord + i3;

            tang1 = tangent + i1;
            tang2 = tangent + i2;
            tang3 = tangent + i3;

            /* x, s, t */
            edge01.x = vert2->x - vert1->x;
            edge01.y = uv2->u - uv1->u;
            edge01.z = uv2->v - uv1->v;

            edge02.x = vert3->x - vert1->x;
            edge02.y = uv3->u - uv1->u;
            edge02.z = uv3->v - uv1->v;

            RwV3dCrossProduct(&cp, &edge01, &edge02);
            if ((RwReal)fabs(cp.x) > BNTCOMP_SMALL_FLOAT)
            {
                const RwReal    invcpx = 1.0f / cp.x;

                tang1->x -= cp.y * invcpx;
                tang2->x -= cp.y * invcpx;
                tang3->x -= cp.y * invcpx;
            }

            /* y, s, t */
            edge01.x = vert2->y - vert1->y;
            edge02.x = vert3->y - vert1->y;

            RwV3dCrossProduct(&cp, &edge01, &edge02);
            if ((RwReal)fabs(cp.x) > BNTCOMP_SMALL_FLOAT)
            {
                const RwReal    invcpx = 1.0f / cp.x;

                tang1->y -= cp.y * invcpx;
                tang2->y -= cp.y * invcpx;
                tang3->y -= cp.y * invcpx;
            }

            /* z, s, t */
            edge01.x = vert2->z - vert1->z;
            edge02.x = vert3->z - vert1->z;

            RwV3dCrossProduct(&cp, &edge01, &edge02);
            if ((RwReal)fabs(cp.x) > BNTCOMP_SMALL_FLOAT)
            {
                const RwReal    invcpx = 1.0f / cp.x;

                tang1->z -= cp.y * invcpx;
                tang2->z -= cp.y * invcpx;
                tang3->z -= cp.y * invcpx;
            }
        }
    }

    /* Normalize the tangents and build the binormals */
    for (n = 0; n < instancedHeader->numVertices; n++)
    {
        RwV3d unpacked;
        RwV3d *currentTangent = tangent + n;
        RwV3d   *currentBinormal = binormal + n;

        {
            RwV3d dotValues;
            dotValues.y = currentTangent->y;
            dotValues.x = currentTangent->x;
            dotValues.z = currentTangent->z;
            {
                RwReal length2 = dotValues.y * dotValues.y;
                length2 += dotValues.x * dotValues.x;
                length2 += dotValues.z * dotValues.z;
                rwInvSqrtMacro(&unused, length2);
                XbVtxFmtScaleTangentMacro(currentTangent, currentTangent, unused);
            }
        }

        unpacked.x = ((RwReal)normal[n].x) * (1.0f / 128.0f);
        unpacked.y = ((RwReal)normal[n].y) * (1.0f / 128.0f);
        unpacked.z = ((RwReal)normal[n].z) * (1.0f / 128.0f);
        RwV3dCrossProduct(currentBinormal, currentTangent, &unpacked);

        { RwReal length2 = RwV3dDotProductMacro(currentBinormal, currentBinormal); rwInvSqrtMacro(&unused, length2); currentBinormal->x = unused * currentBinormal->x; currentBinormal->y = unused * currentBinormal->y; currentBinormal->z = unused * currentBinormal->z; }
    }

    _rpXboxVtxFmtInstV3d(rpNORMALIZEDPACKED, mem, tangent, numVerts, stride);
    _rpXboxVtxFmtInstV3d(rpNORMALIZEDPACKED, mem + 4, binormal, numVerts, stride);

    RwFree(binormal);
    RwFree(tangent);

    return 8;
}

// match: __rpXboxVtxFmtUnInstV3d @ 0x002DE6B0
void
_rpXboxVtxFmtUnInstV3d(RpXboxCompType type, RwV3d *dst, const RwUInt8 *src)
{
    switch (type)
    {
        case rpPACKEDBYTE:
            dst->x = ((RwReal)src[0]) / 255.0f;
            dst->y = ((RwReal)src[1]) / 255.0f;
            dst->z = ((RwReal)src[2]) / 255.0f;
            break;

        case rpSHORT:
            dst->x = (RwReal)((const RwInt16 *)src)[0];
            dst->y = (RwReal)((const RwInt16 *)src)[1];
            dst->z = (RwReal)((const RwInt16 *)src)[2];
            break;

        case rpNORMALIZEDSHORTS:
            dst->x = (RwReal)((const RwInt16 *)src)[0] * (1.0f / 32767.0f);
            dst->y = (RwReal)((const RwInt16 *)src)[1] * (1.0f / 32767.0f);
            dst->z = (RwReal)((const RwInt16 *)src)[2] * (1.0f / 32767.0f);
            break;

        case rpNORMALIZEDPACKED:
            {
                RwUInt32    nx, ny, nz;

                nx = (*(const RwUInt32 *)src) & 0x7FF;
                ny = ((*(const RwUInt32 *)src) >> 11) & 0x7FF;
                nz = (*(const RwUInt32 *)src) >> 22;

                dst->x = ((RwReal)nx) / 1023.0f;
                dst->y = ((RwReal)ny) / 1023.0f;
                dst->z = ((RwReal)nz) / 511.0f;
            }
            break;

        case rpFLOAT:
            *dst = *(const RwV3d *)src;
            break;

        default:
            dst->x = 0.0f;
            dst->y = 0.0f;
            dst->z = 0.0f;
            break;
    }
}

// match: __rpXboxVtxFmtUnInstV2d @ 0x002DE830
void
_rpXboxVtxFmtUnInstV2d(RpXboxCompType type, RwV2d *dst, const RwUInt8 *src)
{
    switch (type)
    {
        case rpPACKEDBYTE:
            dst->x = ((RwReal)src[0]) / 255.0f;
            dst->y = ((RwReal)src[1]) / 255.0f;
            break;

        case rpSHORT:
            dst->x = (RwReal)((const RwInt16 *)src)[0];
            dst->y = (RwReal)((const RwInt16 *)src)[1];
            break;

        case rpNORMALIZEDSHORTS:
            dst->x = (RwReal)((const RwInt16 *)src)[0] * (1.0f / 32767.0f);
            dst->y = (RwReal)((const RwInt16 *)src)[1] * (1.0f / 32767.0f);
            break;

        case rpNORMALIZEDPACKED:
            {
                RwUInt32    nx, ny;

                nx = (*(const RwUInt32 *)src) & 0x7FF;
                ny = ((*(const RwUInt32 *)src) >> 11) & 0x7FF;

                dst->x = ((RwReal)nx) / 1023.0f;
                dst->y = ((RwReal)ny) / 1023.0f;
            }
            break;

        case rpFLOAT:
            *dst = *(const RwV2d *)src;
            break;

        default:
            dst->x = 0.0f;
            dst->y = 0.0f;
            break;
    }
}

// match: _rxXboxVertexFmtCopy @ 0x002DE950
static void *
rxXboxVertexFmtCopy(void *dstObject, const void *srcObject,
                    RwInt32 offsetInObject,
                    RwInt32 sizeInObject __RWUNUSED__)
{
    *(RpXboxVtxFmt *)(((RwUInt8 *)dstObject) + offsetInObject) =
        *(const RpXboxVtxFmt *)(((const RwUInt8 *)srcObject) + offsetInObject);

    return dstObject;
}

// match: _rpXboxVtxFmtOpen @ 0x002DE970
static void *
rpXboxVtxFmtOpen(void *instance,
                 RwInt32 offset __RWUNUSED__,
                 RwInt32 size __RWUNUSED__)
{
    if (++RpVtxFmtModule.numInstances == 1)
    {
        rwXboxVertexFormatCreate();
    }

    return instance;
}

// match: _rpXboxVtxFmtClose @ 0x002DE990
static void *
rpXboxVtxFmtClose(void *instance,
                  RwInt32 offset __RWUNUSED__,
                  RwInt32 size __RWUNUSED__)
{
    if (--RpVtxFmtModule.numInstances == 0)
    {
        rwXboxVertexFormatDestroy();
    }

    return instance;
}

// match: _rxXboxVtxFmtSize @ 0x002DE9B0
static RwInt32
rxXboxVtxFmtSize(const void *object __RWUNUSED__,
                 RwInt32 offsetInObject __RWUNUSED__,
                 RwInt32 sizeInObject __RWUNUSED__)
{
    return sizeof(RpXboxVtxFmt);
}

// match: _rxXboxVtxFmtWrite @ 0x002DE9C0
static RwStream *
rxXboxVtxFmtWrite(RwStream *stream,
                  RwInt32 binaryLength __RWUNUSED__,
                  const void *object,
                  RwInt32 offsetInObject,
                  RwInt32 sizeInObject __RWUNUSED__)
{
    return RwStreamWriteInt32(stream,
                              (const RwInt32 *)(((const RwUInt8 *)object) + offsetInObject),
                              sizeof(RpXboxVtxFmt));
}

// match: _RpXboxVtxFmtInit @ 0x002DE9E0
void
RpXboxVtxFmtInit(RpXboxVtxFmt *fmt, RwUInt32 flags, RwUInt32 numTexCoordSets)
{
    RwUInt32    i;

    fmt->pos = rpFLOAT;

    if (flags & rpGEOMETRYNORMALS)
    {
        fmt->norm = rpNORMALIZEDPACKED;
    }
    else
    {
        fmt->norm = rpCOMPTYPENONE;
    }

    if (flags & (rpGEOMETRYTEXTURED | rpGEOMETRYTEXTURED2))
    {
        for (i = 0; i < numTexCoordSets; i++)
        {
            fmt->texCoord = (RwUInt16)((rpFLOAT << (4 * i)) |
                                       (~(0xF << (4 * i)) & fmt->texCoord));
        }

        for (; i < 4; i++)
        {
            fmt->texCoord = (RwUInt16)((rpCOMPTYPENONE << (4 * i)) |
                                       (~(0xF << (4 * i)) & fmt->texCoord));
        }
    }
    else
    {
        fmt->texCoord = 0;
    }

    if (flags & rpGEOMETRYPRELIT)
    {
        fmt->prelit = TRUE;
    }
    else
    {
        fmt->prelit = FALSE;
    }

    fmt->bnt = 0;
    fmt->reserved = 0;
}

// match: _RpXboxGeometryGetVtxFmt @ 0x002DEAB0
RpXboxVtxFmt *
RpXboxGeometryGetVtxFmt(RpGeometry *geometry)
{
    return (RpXboxVtxFmt *)(((RwUInt8 *)geometry) + _rpXboxGeomVtxFmtOffset);
}

// match: _RpXboxWorldGetVtxFmt @ 0x002DEAC0
RpXboxVtxFmt *
RpXboxWorldGetVtxFmt(RpWorld *world)
{
    return (RpXboxVtxFmt *)(((RwUInt8 *)world) + rpXboxWorldVtxFmtOffset);
}

// match: _RxXboxGetVertexFormatShader @ 0x002DEAD0
DWORD
RxXboxGetVertexFormatShader(const RpXboxVtxFmt *fmt)
{
    RwInt32     index;
    DWORD       vertexFormatDecl[256];
    RwUInt32    v;
    RwUInt32    lastTexCoord;

    index = BinaryFindVertexFormat(fmt, rwXboxVertexFormatArray, rwXboxVertexFormatNumElems);
    if (index >= 0)
    {
        return rwXboxVertexFormatArray[index].handle;
    }

    vertexFormatDecl[0] = D3DVSD_STREAM(0);
    v = 1;

    switch (fmt->pos)
    {
        case rpPACKEDBYTE:
            vertexFormatDecl[v++] = D3DVSD_REG(D3DVSDE_POSITION, D3DVSDT_PBYTE3);
            break;

        case rpSHORT:
            vertexFormatDecl[v++] = D3DVSD_REG(D3DVSDE_POSITION, D3DVSDT_SHORT3);
            break;

        case rpNORMALIZEDSHORTS:
            vertexFormatDecl[v++] = D3DVSD_REG(D3DVSDE_POSITION, D3DVSDT_NORMSHORT3);
            break;

        case rpNORMALIZEDPACKED:
            vertexFormatDecl[v++] = D3DVSD_REG(D3DVSDE_POSITION, D3DVSDT_NORMPACKED3);
            break;

        case rpFLOAT:
            vertexFormatDecl[v++] = D3DVSD_REG(D3DVSDE_POSITION, D3DVSDT_FLOAT3);
            break;
    }

    switch (fmt->norm)
    {
        case rpPACKEDBYTE:
            vertexFormatDecl[v++] = D3DVSD_REG(D3DVSDE_NORMAL, D3DVSDT_PBYTE3);
            break;

        case rpSHORT:
            vertexFormatDecl[v++] = D3DVSD_REG(D3DVSDE_NORMAL, D3DVSDT_SHORT3);
            break;

        case rpNORMALIZEDSHORTS:
            vertexFormatDecl[v++] = D3DVSD_REG(D3DVSDE_NORMAL, D3DVSDT_NORMSHORT3);
            break;

        case rpNORMALIZEDPACKED:
            vertexFormatDecl[v++] = D3DVSD_REG(D3DVSDE_NORMAL, D3DVSDT_NORMPACKED3);
            break;

        case rpFLOAT:
            vertexFormatDecl[v++] = D3DVSD_REG(D3DVSDE_NORMAL, D3DVSDT_FLOAT3);
            break;
    }

    if (fmt->prelit)
    {
        vertexFormatDecl[v++] = D3DVSD_REG(D3DVSDE_DIFFUSE, D3DVSDT_D3DCOLOR);
    }

    lastTexCoord = 0;
    if (fmt->texCoord)
    {
        RwUInt32    i;

        for (i = 0; i < 4; i++)
        {
            RpXboxCompType type = (RpXboxCompType)((fmt->texCoord >> (4 * i)) & 0xF);

            if (type == rpCOMPTYPENONE)
            {
                break;
            }

            switch (type)
            {
                case rpPACKEDBYTE:
                    vertexFormatDecl[v++] = D3DVSD_REG(rpWorldVSDETexFlags[i], D3DVSDT_PBYTE2);
                    break;

                case rpSHORT:
                    vertexFormatDecl[v++] = D3DVSD_REG(rpWorldVSDETexFlags[i], D3DVSDT_SHORT2);
                    break;

                case rpNORMALIZEDSHORTS:
                    vertexFormatDecl[v++] = D3DVSD_REG(rpWorldVSDETexFlags[i], D3DVSDT_NORMSHORT2);
                    break;

                case rpNORMALIZEDPACKED:
                    vertexFormatDecl[v++] = D3DVSD_REG(rpWorldVSDETexFlags[i], D3DVSDT_NORMPACKED3);
                    break;

                case rpFLOAT:
                    vertexFormatDecl[v++] = D3DVSD_REG(rpWorldVSDETexFlags[i], D3DVSDT_FLOAT2);
                    break;
            }
        }

        lastTexCoord = i;
    }

    if (fmt->bnt)
    {
        vertexFormatDecl[v++] = D3DVSD_REG(D3DVSDE_TEXCOORD0 + lastTexCoord, D3DVSDT_NORMPACKED3);
        vertexFormatDecl[v++] = D3DVSD_REG(D3DVSDE_TEXCOORD1 + lastTexCoord, D3DVSDT_NORMPACKED3);
    }

    vertexFormatDecl[v++] = D3DVSD_END();

    index = -(index + 1);

    if (rwXboxVertexFormatNumElems >= rwXboxVertexFormatMaxElems)
    {
        rwXboxVertexFormatMaxElems += 128;
        rwXboxVertexFormatArray = (_rpXboxVtxFmtDescItem *)
            RwRealloc(rwXboxVertexFormatArray,
                      sizeof(_rpXboxVtxFmtDescItem) * rwXboxVertexFormatMaxElems,
                      rwID_WORLDPIPEMODULE | rwMEMHINTDUR_FUNCTION |
                      rwMEMHINTFLAG_RESIZABLE);

        if (index > rwXboxVertexFormatNumElems)
        {
            index = rwXboxVertexFormatNumElems;
        }
    }
    else if (index < rwXboxVertexFormatNumElems)
    {
        memmove(&rwXboxVertexFormatArray[index + 1], &rwXboxVertexFormatArray[index],
                (rwXboxVertexFormatNumElems - index) * sizeof(_rpXboxVtxFmtDescItem));
    }

    rwXboxVertexFormatNumElems++;

    rwXboxVertexFormatArray[index].format = *fmt;

    if (D3D_OK != D3DDevice_CreateVertexShader(vertexFormatDecl, NULL,
                                               &rwXboxVertexFormatArray[index].handle, 0))
    {
        return 0;
    }

    return rwXboxVertexFormatArray[index].handle;
}

// match: __rpXboxDefaultInstance @ 0x002DED60
RwBool
_rpXboxDefaultInstance(RpXboxVtxFmt *fmt,
                       RwUInt32 flags,
                       RxXboxResEntryHeader *instancedHeader,
                       const RwV3d *positions,
                       const RwV3d *normals,
                       const RpVertexNormal *packedNormals,
                       const RwRGBA *color,
                       RwInt32 numTexCoordSets,
                       const RwTexCoords **texCoordSets,
                       RwUInt32 lockedSinceLastInst)
{
    RwInt32             numVertices;
    RwUInt8            *lockedVertexBuffer;
    RwUInt32            vbSize;
    /* Godfather debug _rpXboxDefaultInstance (0xB7B540), frame -0x20:
     * size is signed int. Retain the signed result before advancing the
     * position pointer; VC7.1 otherwise merges the packed/unpacked exits. */
    RwInt32             size;
    RwInt32             i;

    numVertices = instancedHeader->numVertices;

    if (numTexCoordSets > 4)
    {
        numTexCoordSets = 4;
    }

    if (*(RwUInt32 *)fmt == 0)
    {
        RpXboxVtxFmtInit(fmt, flags, numTexCoordSets);
    }

    if (!instancedHeader->vertexBuffer)
    {
        RxXboxInstanceData *instancedData;
        DWORD               shader;

        instancedHeader->stride = _rpXboxVtxFmtGetStride(fmt);

        shader = RxXboxGetVertexFormatShader(fmt);
        for (instancedData = instancedHeader->begin;
             instancedData != instancedHeader->end;
             instancedData++)
        {
            instancedData->vertexShader = shader;
        }

        vbSize = instancedHeader->stride * numVertices;
        instancedHeader->vertexBuffer = RwXbCreateVertexBuffer(vbSize);
        if (!instancedHeader->vertexBuffer)
        {
            return FALSE;
        }

        D3DVertexBuffer_Lock((D3DVertexBuffer *)instancedHeader->vertexBuffer, 0,
                             vbSize, &lockedVertexBuffer, 0);
    }
    else
    {
        D3DVertexBuffer    *currentVertexBuffer = (D3DVertexBuffer *)instancedHeader->vertexBuffer;

        vbSize = instancedHeader->stride * numVertices;

        if (currentVertexBuffer->Lock && D3DDevice_IsFencePending(currentVertexBuffer->Lock))
        {
            lockedVertexBuffer = RwXbVertexBufferLockDiscard(currentVertexBuffer, vbSize);
            lockedSinceLastInst = rpGEOMETRYLOCKALL;
        }
        else
        {
            D3DVertexBuffer_Lock(currentVertexBuffer, 0, vbSize, &lockedVertexBuffer, 0);
        }
    }

    if (positions)
    {
        if (lockedSinceLastInst & rpGEOMETRYLOCKVERTICES)
        {
            size = _rpXboxVtxFmtInstV3d((RpXboxCompType)fmt->pos, lockedVertexBuffer,
                                        positions, numVertices, instancedHeader->stride);
        }
        else
        {
            size = _rpXboxVtxFmtGetSize((RpXboxCompType)fmt->pos, 3);
        }
        lockedVertexBuffer += size;
    }

    if (normals)
    {
        if (lockedSinceLastInst & rpGEOMETRYLOCKNORMALS)
        {
            size = _rpXboxVtxFmtInstV3d((RpXboxCompType)fmt->norm, lockedVertexBuffer,
                                        normals, numVertices, instancedHeader->stride);
        }
        else
        {
            size = _rpXboxVtxFmtGetSize((RpXboxCompType)fmt->norm, 3);
        }

        lockedVertexBuffer += size;
    }

    if (packedNormals)
    {
        if (lockedSinceLastInst & rpGEOMETRYLOCKNORMALS)
        {
            size = _rpXboxVtxFmtInstV3dComp((RpXboxCompType)fmt->norm, lockedVertexBuffer,
                                            packedNormals, numVertices, instancedHeader->stride);
        }
        else
        {
            size = _rpXboxVtxFmtGetSize((RpXboxCompType)fmt->norm, 3);
        }

        lockedVertexBuffer += size;
    }

    if (color)
    {
        if (lockedSinceLastInst & rpGEOMETRYLOCKPRELIGHT)
        {
            instancedHeader->vertexAlpha =
                _rpXboxVtxFmtInstColor(lockedVertexBuffer, color, numVertices,
                                       instancedHeader->stride);
        }

        lockedVertexBuffer += sizeof(RwUInt32);
    }

    for (i = 0; i < numTexCoordSets; i++)
    {
        RpXboxCompType type = (RpXboxCompType)((fmt->texCoord >> (4 * i)) & 0xF);

        if (lockedSinceLastInst & (rpGEOMETRYLOCKTEXCOORDS1 << i))
        {
            size = _rpXboxVtxFmtInstV2d(type, lockedVertexBuffer, (const RwV2d *)texCoordSets[i],
                                        numVertices, instancedHeader->stride);
        }
        else
        {
            size = _rpXboxVtxFmtGetSize(type, 2);
        }

        lockedVertexBuffer += size;
    }

    if (fmt->bnt &&
        (lockedSinceLastInst & (rpGEOMETRYLOCKPOLYGONS | rpGEOMETRYLOCKVERTICES |
                                rpGEOMETRYLOCKNORMALS)))
    {
        if (normals)
        {
            _rpXboxVtxFmtInstBNT(lockedVertexBuffer, positions, normals,
                                 texCoordSets[fmt->bnt - 1], instancedHeader,
                                 numVertices, instancedHeader->stride);
        }
        else
        {
            _rpXboxVtxFmtInstBNTComp(lockedVertexBuffer, positions, packedNormals,
                                     texCoordSets[fmt->bnt - 1], instancedHeader,
                                     numVertices, instancedHeader->stride);
        }
    }

    return TRUE;
}

// match: _rxXboxVtxFmtGeometryRead @ 0x002DF000
static RwStream *
rxXboxVtxFmtGeometryRead(RwStream *stream,
                         RwInt32 binaryLength __RWUNUSED__,
                         void *object,
                         RwInt32 offsetInObject __RWUNUSED__,
                         RwInt32 sizeInObject __RWUNUSED__)
{
    RpGeometry         *geometry = (RpGeometry *)object;
    RpXboxVtxFmt       *fmt;

    fmt = RpXboxGeometryGetVtxFmt(geometry);

    stream = RwStreamReadInt32(stream, (RwInt32 *)fmt, sizeof(RpXboxVtxFmt));
    if (stream)
    {
        RwResEntry *resEntry = geometry->repEntry;

        if (resEntry)
        {
            RxXboxResEntryHeader   *resEntryHeader = (RxXboxResEntryHeader *)(resEntry + 1);
            RxXboxInstanceData     *instancedData;
            DWORD                   shader;

            shader = RxXboxGetVertexFormatShader(fmt);

            for (instancedData = resEntryHeader->begin;
                 instancedData != resEntryHeader->end;
                 instancedData++)
            {
                instancedData->vertexShader = shader;
            }
        }
    }

    return stream;
}

// match: _rxXboxVtxFmtWorldSectorFixVertexShader @ 0x002DF060
static RpWorldSector *
rxXboxVtxFmtWorldSectorFixVertexShader(RpWorldSector *worldSector, void *data)
{
    RwResEntry *resEntry = worldSector->repEntry;

    if (resEntry)
    {
        RxXboxResEntryHeader   *resEntryHeader = (RxXboxResEntryHeader *)(resEntry + 1);
        RxXboxInstanceData     *instancedData;
        DWORD                   shader;

        shader = RxXboxGetVertexFormatShader((const RpXboxVtxFmt *)data);

        for (instancedData = resEntryHeader->begin;
             instancedData != resEntryHeader->end;
             instancedData++)
        {
            instancedData->vertexShader = shader;
        }
    }

    return worldSector;
}

// match: _rxXboxVtxFmtWorldRead @ 0x002DF0A0
static RwStream *
rxXboxVtxFmtWorldRead(RwStream *stream,
                      RwInt32 binaryLength __RWUNUSED__,
                      void *object,
                      RwInt32 offsetInObject __RWUNUSED__,
                      RwInt32 sizeInObject __RWUNUSED__)
{
    RpWorld            *world = (RpWorld *)object;
    RpXboxVtxFmt       *fmt;

    fmt = RpXboxWorldGetVtxFmt(world);

    stream = RwStreamReadInt32(stream, (RwInt32 *)fmt, sizeof(RpXboxVtxFmt));
    if (stream)
    {
        RpWorldForAllWorldSectors(world, rxXboxVtxFmtWorldSectorFixVertexShader, fmt);
    }

    return stream;
}

// match: __rpXboxVtxFmtPluginAttach @ 0x002DF0E0
RwBool
_rpXboxVtxFmtPluginAttach(void)
{
    if (RwEngineRegisterPlugin(0, rwID_VERTEXFMTPLUGIN,
                               rpXboxVtxFmtOpen, rpXboxVtxFmtClose) < 0)
    {
        return FALSE;
    }

    _rpXboxGeomVtxFmtOffset = RpGeometryRegisterPlugin(sizeof(RpXboxVtxFmt),
                                                       rwID_VERTEXFMTPLUGIN,
                                                       rxXboxVertexFmtConst,
                                                       rxXboxVertexFmtConst,
                                                       rxXboxVertexFmtCopy);
    if (_rpXboxGeomVtxFmtOffset < 0)
    {
        return FALSE;
    }

    RpGeometryRegisterPluginStream(rwID_VERTEXFMTPLUGIN,
                                   rxXboxVtxFmtGeometryRead,
                                   rxXboxVtxFmtWrite,
                                   rxXboxVtxFmtSize);

    rpXboxWorldVtxFmtOffset = RpWorldRegisterPlugin(sizeof(RpXboxVtxFmt),
                                                    rwID_VERTEXFMTPLUGIN,
                                                    rxXboxVertexFmtConst,
                                                    rxXboxVertexFmtConst,
                                                    rxXboxVertexFmtCopy);
    if (rpXboxWorldVtxFmtOffset < 0)
    {
        return FALSE;
    }

    RpWorldRegisterPluginStream(rwID_VERTEXFMTPLUGIN,
                                rxXboxVtxFmtWorldRead,
                                rxXboxVtxFmtWrite,
                                rxXboxVtxFmtSize);

    return TRUE;
}
