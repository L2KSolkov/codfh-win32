/*
 * codfh-match: RenderWare 3.6's Xbox multi-texture effect configuration
 * and its streaming, rebuilt from the image; the file name and the names
 * are the Godfather PDB's.
 */

#include <xtl.h>

#include "rpplugin.h"
#include <rpdbgerr.h>
#include <rwcore.h>
#include <rpworld.h>
#include <rpcriter.h>

#include "multiTex.h"
#include "multiTexEffect.h"

#include "multitexxbox.h"

/* RenderWare 3.6's RCS id string, which the image keeps (the 3.7.2 tree has none) */
static const char rcsid[] = "@@@@(#)$Id: //RenderWare/RW36Active/rwsdk/plugin/matfx/xbox/multitexxbox.c#1 $";

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: _rcsid @ 0x0041A8B0

// match: _RpXboxMTEffectGetConfig @ 0x002FC160
RpMatFXXboxMaterial *
RpXboxMTEffectGetConfig(const RpMTEffect *effect)
{
    return (RpMatFXXboxMaterial *)(effect + 1);
}

// match: _RpXboxMTEffectCreate @ 0x002FC170
RpMTEffect *
RpXboxMTEffectCreate(RwUInt32 numStages)
{
    RpMTEffect          *effect;
    RwUInt32            size;
    RpMatFXXboxMaterial *xboxMat;

    size = sizeof(RpMTEffect) + sizeof(RpMatFXXboxMaterial);
    effect = (RpMTEffect *)RwMalloc(size, rwMEMHINTDUR_EVENT | rwID_XBOXMATPLUGIN);
    if (NULL == effect)
    {
        RWERROR((E_RW_NOMEM, size));
        return NULL;
    }

    _rpMTEffectInit(effect, rwID_XBOX);

    xboxMat = RpXboxMTEffectGetConfig(effect);
    xboxMat->nbStages = numStages;

    if (numStages > 0)
    {
        xboxMat->stages = (RpMatFXXboxStage *)
            RwMalloc(numStages * sizeof(RpMatFXXboxStage),
                     rwMEMHINTDUR_EVENT | rwID_XBOXMATPLUGIN);
    }

    return effect;
}

// match: _MatFXXboxMaterialStreamGetSize @ 0x002FC1F0
static RwInt32
MatFXXboxMaterialStreamGetSize(const RpMTEffect *effect)
{
    const RpMatFXXboxMaterial   *xboxMat = RpXboxMTEffectGetConfig(effect);
    RwInt32                     size;
    RwInt32                     i;

    size = sizeof(RwInt32);
    for (i = 0; i < xboxMat->nbStages; i++)
    {
        size += sizeof(RpMatFXXboxStage);
    }

    return size + sizeof(RpMatFXXboxFinalBlend) + sizeof(RpMatFXXboxMiscState);
}

// match: _MatFXXboxMaterialStreamWrite @ 0x002FC210
static const RpMTEffect *
MatFXXboxMaterialStreamWrite(const RpMTEffect *effect, RwStream *stream)
{
    RpMatFXXboxMaterial *xboxMat;
    RwInt32             i;

    if (!RwStreamWriteChunkHeader(stream, rwID_EXTENSION,
                                  MatFXXboxMaterialStreamGetSize(effect)))
    {
        return NULL;
    }

    xboxMat = RpXboxMTEffectGetConfig(effect);

    RwStreamWrite(stream, &xboxMat->nbStages, sizeof(RwInt32));

    for (i = 0; i < xboxMat->nbStages; i++)
    {
        RwStreamWrite(stream, &xboxMat->stages[i], sizeof(RpMatFXXboxStage));
    }

    RwStreamWrite(stream, &xboxMat->blend, sizeof(RpMatFXXboxFinalBlend));
    RwStreamWrite(stream, &xboxMat->miscState, sizeof(RpMatFXXboxMiscState));

    return effect;
}

// match: _MatFXXboxMaterialStreamRead @ 0x002FC2C0
static RpMTEffect *
MatFXXboxMaterialStreamRead(RwStream *stream,
                            RwPlatformID platformID __RWUNUSED__,
                            RwUInt32 version __RWUNUSED__,
                            RwUInt32 length __RWUNUSED__)
{
    RpMTEffect          *effect;
    RpMatFXXboxMaterial *xboxMat;
    RwUInt32            numStages;
    RwInt32             i;

    RwStreamRead(stream, &numStages, sizeof(RwUInt32));

    effect = RpXboxMTEffectCreate(numStages);
    xboxMat = RpXboxMTEffectGetConfig(effect);

    for (i = 0; i < xboxMat->nbStages; i++)
    {
        RwStreamRead(stream, &xboxMat->stages[i], sizeof(RpMatFXXboxStage));
    }

    RwStreamRead(stream, &xboxMat->blend, sizeof(RpMatFXXboxFinalBlend));
    RwStreamRead(stream, &xboxMat->miscState, sizeof(RpMatFXXboxMiscState));

    return effect;
}

// match: __rpMatFXXboxMaterialDestroy @ 0x002FC340
void
_rpMatFXXboxMaterialDestroy(RpMTEffect *effect)
{
    RpMatFXXboxMaterial *xboxMat = RpXboxMTEffectGetConfig(effect);

    if (xboxMat->nbStages)
    {
        RwFree(xboxMat->stages);
    }

    RwFree(effect);
}

// match: __rpMultiTexturePlatformPluginsAttach @ 0x002FC370
RwBool
_rpMultiTexturePlatformPluginsAttach(void)
{
    _rpMultiTexturePluginAttach();

    _rpMTEffectRegisterPlatform(rwID_XBOX,
                                MatFXXboxMaterialStreamRead,
                                MatFXXboxMaterialStreamWrite,
                                MatFXXboxMaterialStreamGetSize,
                                _rpMatFXXboxMaterialDestroy);

    _rpMaterialRegisterMultiTexturePlugin(rwID_XBOX, rwID_XBOXMATPLUGIN, 0);

    return TRUE;
}
