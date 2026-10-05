/*
 * codfh-match: RenderWare 3.6's Xbox skin vertex formats, rebuilt from the
 * image; the file name is the image's RCS id string's, names and types the
 * Godfather PDB's. It follows the world's xbvtxfmt.c: a sorted array of
 * formats and their D3D vertex shaders, the skin weights and indices in a
 * second stream.
 */

#include <xtl.h>
#include <string.h>

#include <rwcore.h>
#include <rpworld.h>

#include "skin.h"
#include "skinxbox.h"
#include "xbvtxfmt.h"

/* RenderWare 3.6's RCS id string, which the image keeps (the 3.7.2 tree has none) */
static const char rcsid[] = "@@@@(#)$Id: //RenderWare/RW36Active/rwsdk/plugin/skin2/xbox/skinxboxformat.c#1 $";

typedef struct _rpXboxSkinVtxFmtDescItem _rpXboxSkinVtxFmtDescItem;
struct _rpXboxSkinVtxFmtDescItem
{
    _rpSkinXboxVtxFmt   format;
    DWORD               handle;
};

static _rpXboxSkinVtxFmtDescItem *rpXboxSkinVertexFormatArray;
static RwInt32 rpXboxSkinVertexFormatMaxElems;
static RwInt32 rpXboxSkinVertexFormatNumElems;
static RwBool rpSkinXboxVertexFormatArrayInited;

/* The skin shaders' own vertex registers: position 0, weights 1, indices
 * 2, normal 3, prelight 4, texture coordinates 5 to 8, binormal and tangent
 * 9 and 10. */
#define rpSKINVSDENORMAL    3
#define rpSKINVSDEPRELIT    4
#define rpSKINVSDEBINORMAL  9
#define rpSKINVSDETANGENT   10

/* The vertex registers of the four texture coordinate sets (0x418FD4).
 * Distinct from the world pipeline table named rpWorldVSDETexFlags. */
static const RwUInt32 unk_418FD4[4] = { 5, 6, 7, 8 };

/* The weights' and indices' types by weight count. */
static const RwUInt32 weightFlags[5] =
{
    0,
    D3DVSDT_PBYTE1,
    D3DVSDT_PBYTE2,
    D3DVSDT_PBYTE3,
    D3DVSDT_PBYTE4
};

static const RwUInt32 indexFlags[5] =
{
    0,
    D3DVSDT_SHORT1,
    D3DVSDT_SHORT2,
    D3DVSDT_SHORT3,
    D3DVSDT_SHORT4
};

/* A do-nothing vertex shader program the declarations are created with. */
static DWORD dwDummyshaderVertexShader[] =
{
    0x00012078, 0x00000000, 0x0000001B, 0x0836106C, 0x20700FF9, 0x00000000
};

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: _rcsid @ 0x00418F80
// match: _unk_418FD4 @ 0x00418FD4
// match: _weightFlags @ 0x00418FE4
// match: _indexFlags @ 0x00418FF8
// match: _dwDummyshaderVertexShader @ 0x00436A90

// match: __rpSkinXboxVertexFormatCreate @ 0x002D4320

void
_rpSkinXboxVertexFormatCreate(void)
{
    RwInt32 i;

    rpXboxSkinVertexFormatMaxElems = 32;
    rpXboxSkinVertexFormatArray = (_rpXboxSkinVtxFmtDescItem *)
        RwMalloc(sizeof(_rpXboxSkinVtxFmtDescItem) * rpXboxSkinVertexFormatMaxElems,
                 rwID_SKINPLUGIN | rwMEMHINTDUR_GLOBAL);

    for (i = 0; i < rpXboxSkinVertexFormatMaxElems; i++)
    {
        rpXboxSkinVertexFormatArray[i].handle = 0;
    }

    rpXboxSkinVertexFormatNumElems = 0;
    rpSkinXboxVertexFormatArrayInited = TRUE;
}

// match: __rpSkinXboxVertexFormatDestroy @ 0x002D4370
void
_rpSkinXboxVertexFormatDestroy(void)
{
    RwInt32 i;

    for (i = 0; i < rpXboxSkinVertexFormatNumElems; i++)
    {
        if (rpXboxSkinVertexFormatArray[i].handle)
        {
            D3DDevice_DeleteVertexShader(rpXboxSkinVertexFormatArray[i].handle);
            rpXboxSkinVertexFormatArray[i].handle = 0;
        }
    }

    if (rpXboxSkinVertexFormatArray)
    {
        RwFree(rpXboxSkinVertexFormatArray);
        rpXboxSkinVertexFormatArray = NULL;
    }

    rpXboxSkinVertexFormatNumElems = 0;
    rpXboxSkinVertexFormatMaxElems = 0;
    rpSkinXboxVertexFormatArrayInited = FALSE;
}
/* /OPT:ICF folded this into xbvtxfmt.c's identical BinaryFindVertexFormat,
 * placed at 0x2D43D0 there. */
static RwInt32
SkinBinaryFindVertexFormat(const _rpSkinXboxVtxFmt *value,
                           const _rpXboxSkinVtxFmtDescItem *buffer,
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

/* Local reconstruction inline, not an original symbol. The stores and
 * shader call at 0x2D466B onward retain an element index across the call. */
static __forceinline DWORD
SkinStoreVertexFormat(RwInt32 index, const _rpSkinXboxVtxFmt *desc, DWORD *vertexFormatDecl)
{
    rpXboxSkinVertexFormatArray[index].format = *desc;

    if (D3D_OK != D3DDevice_CreateVertexShader(vertexFormatDecl, dwDummyshaderVertexShader,
                                               &rpXboxSkinVertexFormatArray[index].handle, 0))
    {
        return 0;
    }

    return rpXboxSkinVertexFormatArray[index].handle;
}

// match: __rpSkinXboxGetVertexFormatShader @ 0x002D4440
DWORD
_rpSkinXboxGetVertexFormatShader(const _rpSkinXboxVtxFmt *desc)
{
    RwUInt32 weights;
    RwUInt8 flags;
    RwInt32     index;
    DWORD       vertexFormatDecl[256];
    RwUInt32    v;
    RwUInt32    i;

    index = SkinBinaryFindVertexFormat(desc, rpXboxSkinVertexFormatArray,
                                       rpXboxSkinVertexFormatNumElems);
    if (index >= 0)
    {
        return rpXboxSkinVertexFormatArray[index].handle;
    }

    vertexFormatDecl[0] = D3DVSD_STREAM(0);
    v = 1;

    switch (desc->pos)
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

    switch (desc->norm)
    {
        case rpPACKEDBYTE:
            vertexFormatDecl[v++] = D3DVSD_REG(rpSKINVSDENORMAL, D3DVSDT_PBYTE3);
            break;

        case rpSHORT:
            vertexFormatDecl[v++] = D3DVSD_REG(rpSKINVSDENORMAL, D3DVSDT_SHORT3);
            break;

        case rpNORMALIZEDSHORTS:
            vertexFormatDecl[v++] = D3DVSD_REG(rpSKINVSDENORMAL, D3DVSDT_NORMSHORT3);
            break;

        case rpNORMALIZEDPACKED:
            vertexFormatDecl[v++] = D3DVSD_REG(rpSKINVSDENORMAL, D3DVSDT_NORMPACKED3);
            break;

        case rpFLOAT:
            vertexFormatDecl[v++] = D3DVSD_REG(rpSKINVSDENORMAL, D3DVSDT_FLOAT3);
            break;
    }

    flags = desc->prelit | (desc->numWeights << 1) | (desc->bnt << 7);
    if (flags & 1)
    {
        vertexFormatDecl[v++] = D3DVSD_REG(rpSKINVSDEPRELIT, D3DVSDT_D3DCOLOR);
    }

    for (i = 0; i < 4; i++)
    {
        RpXboxCompType type = (RpXboxCompType)((desc->texCoord >> (4 * i)) & 0xF);

        if (type == rpCOMPTYPENONE)
        {
            break;
        }

        switch (type)
        {
            case rpPACKEDBYTE:
                vertexFormatDecl[v++] = D3DVSD_REG(unk_418FD4[i], D3DVSDT_PBYTE2);
                break;

            case rpSHORT:
                vertexFormatDecl[v++] = D3DVSD_REG(unk_418FD4[i], D3DVSDT_SHORT2);
                break;

            case rpNORMALIZEDSHORTS:
                vertexFormatDecl[v++] = D3DVSD_REG(unk_418FD4[i], D3DVSDT_NORMSHORT2);
                break;

            case rpNORMALIZEDPACKED:
                vertexFormatDecl[v++] = D3DVSD_REG(unk_418FD4[i], D3DVSDT_NORMPACKED3);
                break;

            case rpFLOAT:
                vertexFormatDecl[v++] = D3DVSD_REG(unk_418FD4[i], D3DVSDT_FLOAT2);
                break;
        }
    }

    if (flags & 128)
    {
        vertexFormatDecl[v++] = D3DVSD_REG(rpSKINVSDETANGENT, D3DVSDT_NORMPACKED3);
        vertexFormatDecl[v++] = D3DVSD_REG(rpSKINVSDEBINORMAL, D3DVSDT_NORMPACKED3);
    }

    weights = (flags >> 1) & 63;
    if (weights)
    {
        vertexFormatDecl[v++] = D3DVSD_STREAM(1);
        vertexFormatDecl[v++] = D3DVSD_REG(D3DVSDE_BLENDWEIGHT, weightFlags[weights]);
        vertexFormatDecl[v++] = D3DVSD_REG(2, indexFlags[weights]);
    }

    vertexFormatDecl[v++] = D3DVSD_END();

    index = -(index + 1);

    if (rpXboxSkinVertexFormatNumElems >= rpXboxSkinVertexFormatMaxElems)
    {
        rpXboxSkinVertexFormatMaxElems += 32;
        rpXboxSkinVertexFormatArray = (_rpXboxSkinVtxFmtDescItem *)
            RwRealloc(rpXboxSkinVertexFormatArray,
                      sizeof(_rpXboxSkinVtxFmtDescItem) * rpXboxSkinVertexFormatMaxElems,
                      rwID_SKINPLUGIN | rwMEMHINTDUR_EVENT);

        if (index > rpXboxSkinVertexFormatNumElems)
        {
            index = rpXboxSkinVertexFormatNumElems;
        }
    }
    else if (index < rpXboxSkinVertexFormatNumElems)
    {
        memmove(&rpXboxSkinVertexFormatArray[index + 1], &rpXboxSkinVertexFormatArray[index],
                (rpXboxSkinVertexFormatNumElems - index) * sizeof(_rpXboxSkinVtxFmtDescItem));
    }

    rpXboxSkinVertexFormatNumElems++;

    return SkinStoreVertexFormat(index, desc, vertexFormatDecl);
}
