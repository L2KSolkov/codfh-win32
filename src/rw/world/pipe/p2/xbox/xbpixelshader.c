/*
 * codfh-match: RenderWare 3.6's Xbox material pixel shader plugin, rebuilt
 * from the image; the file name is the image's RCS id string's, names the
 * Godfather PDB's. Only the material plugin is linked: nothing creates
 * pixel shader definitions, so the free list and dummy shader stay NULL.
 * A definition's reference count sits at
 * _RpXboxMaterialPixelShaderRefCountOffset in it; the last release frees
 * it to the list (3.7's RpXboxPixelShaderDestroy, inlined here). The offset
 * is static: SetPixelShader keeps it in a register across the count's store.
 */

#include <xtl.h>

#include <rwcore.h>
#include "bamateri.h"

#include "xbpixelshader.h"

/* RenderWare 3.6's RCS id string, which the image keeps (the 3.7.2 tree has none) */
static const char rcsid[] = "@@@@(#)$Id: //RenderWare/RW36Active/rwsdk/world/pipe/p2/xbox/xbpixelshader.c#1 $";

/* A pixel shader definition (a D3DPIXELSHADERDEF's 60 dwords) that nothing references; the
   Godfather PDB has no name for it either */
static const DWORD unk_419640[60] =
{
    0xD8D41010, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x000000C0, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xC8C40000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x000000C0, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00011101,
    0x00000001, 0x00000000, 0x00000000, 0xFFFFFFFF, 0xFFFFFFFF,
    0x000001FF,
};

#define rpXboxPixelShaderRefCount(_pixelShader)                             \
    (*((RwInt32 *)(((RwUInt8 *)(_pixelShader)) + _RpXboxMaterialPixelShaderRefCountOffset)))

#define rpXboxMaterialPixelShader(_material)                                \
    ((DWORD *)(((RwUInt8 *)(_material)) + _RpXboxMaterialPixelShaderOffset))

static RwFreeList *PixelShaderDefFreeList;
static RwInt32 _RpXboxMaterialPixelShaderRefCountOffset;

DWORD RpXboxMaterialDummyPixelShader;
RwInt32 _RpXboxMaterialPixelShaderOffset;

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: _rcsid @ 0x004195E8
// match: _unk_419640 @ 0x00419640

// match: _rpXboxMaterialPixelShaderConstructor @ 0x002E1AD0
static void *
rpXboxMaterialPixelShaderConstructor(void *object,
                                     RwInt32 offsetInObject __RWUNUSED__,
                                     RwInt32 sizeInObject __RWUNUSED__)
{
    if (object)
    {
        *rpXboxMaterialPixelShader(object) = 0;

        return object;
    }

    return NULL;
}

// match: __rpXboxMaterialPixelShaderClose @ 0x002E1AF0
void
_rpXboxMaterialPixelShaderClose(void)
{
    if (PixelShaderDefFreeList)
    {
        RwFreeListDestroy(PixelShaderDefFreeList);
        PixelShaderDefFreeList = NULL;
    }

    if (RpXboxMaterialDummyPixelShader)
    {
        D3DDevice_DeletePixelShader(RpXboxMaterialDummyPixelShader);
        RpXboxMaterialDummyPixelShader = 0;
    }
}

// match: _RpXboxMaterialSetPixelShader @ 0x002E1B30
void
RpXboxMaterialSetPixelShader(RpMaterial *material, DWORD pixelShader)
{
    DWORD   *pixelShaderMaterial = rpXboxMaterialPixelShader(material);

    if (*pixelShaderMaterial != pixelShader)
    {
        DWORD   oldPixelShader = *pixelShaderMaterial;

        if (oldPixelShader)
        {
            if (--rpXboxPixelShaderRefCount(oldPixelShader) <= 0)
            {
                RwFreeListFree(PixelShaderDefFreeList, (void *)oldPixelShader);
            }

            *pixelShaderMaterial = 0;
        }

        if (pixelShader)
        {
            rpXboxPixelShaderRefCount(pixelShader)++;

            *pixelShaderMaterial = pixelShader;
        }
    }
}

// match: _rpXboxMaterialPixelShaderDestructor @ 0x002E1B90
static void *
rpXboxMaterialPixelShaderDestructor(void *object,
                                    RwInt32 offsetInObject __RWUNUSED__,
                                    RwInt32 sizeInObject __RWUNUSED__)
{
    if (object)
    {
        RpXboxMaterialSetPixelShader((RpMaterial *)object, 0);
    }

    return object;
}

// match: _rpXboxMaterialPixelShaderCopy @ 0x002E1BE0
static void *
rpXboxMaterialPixelShaderCopy(void *dstObject,
                              const void *srcObject,
                              RwInt32 offsetInObject __RWUNUSED__,
                              RwInt32 sizeInObject __RWUNUSED__)
{
    if (dstObject && srcObject)
    {
        RpXboxMaterialSetPixelShader((RpMaterial *)dstObject,
                                     *rpXboxMaterialPixelShader(srcObject));
    }

    return dstObject;
}

// match: __rpXboxMaterialPixelShaderOpen @ 0x002E1C10
RwBool
_rpXboxMaterialPixelShaderOpen(void)
{
    _RpXboxMaterialPixelShaderOffset =
        RpMaterialRegisterPlugin(sizeof(DWORD),
                                 MAKECHUNKID(rwVENDORID_CRITERIONWORLD, 0x01),
                                 rpXboxMaterialPixelShaderConstructor,
                                 rpXboxMaterialPixelShaderDestructor,
                                 rpXboxMaterialPixelShaderCopy);

    return _RpXboxMaterialPixelShaderOffset;
}
