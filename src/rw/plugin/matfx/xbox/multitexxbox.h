/*
 * codfh-match: RenderWare 3.6's Xbox multi-texture effect configuration
 * (plugin/matfx/xbox/multitexxbox.c); the layouts and names are the
 * Godfather PDB's (0x88-byte stages, a 0x18-byte configuration after the
 * 0x30-byte RpMTEffect).
 */
#ifndef MULTITEXXBOX_H
#define MULTITEXXBOX_H

typedef struct RpMatFXXboxStage RpMatFXXboxStage;
struct RpMatFXXboxStage
{
    RwInt32     colorOp;
    RwInt32     colorArg0;
    RwInt32     colorArg1;
    RwInt32     colorArg2;
    RwInt32     alphaOp;
    RwInt32     alphaArg0;
    RwInt32     alphaArg1;
    RwInt32     alphaArg2;
    RwInt32     resultArg;
    RwInt32     textureTransformFlags;
    RwInt32     colorSign;
    RwInt32     alphaKill;
    RwReal      bumpEnvMat00;
    RwReal      bumpEnvMat01;
    RwReal      bumpEnvMat11;
    RwReal      bumpEnvMat10;
    RwInt32     texCoordIndex;
    RwInt32     borderColor;
    D3DMATRIX   texTransformMatrix;
};

typedef struct RpMatFXXboxFinalBlend RpMatFXXboxFinalBlend;
struct RpMatFXXboxFinalBlend
{
    RwInt32     srcBlend;
    RwInt32     dstBlend;
};

typedef struct RpMatFXXboxMiscState RpMatFXXboxMiscState;
struct RpMatFXXboxMiscState
{
    RwInt32     textureFactor;
};

typedef struct RpMatFXXboxMaterial RpMatFXXboxMaterial;
struct RpMatFXXboxMaterial
{
    RwInt32                 nbStages;
    RpMatFXXboxStage        *stages;
    RpMatFXXboxFinalBlend   blend;
    RpMatFXXboxMiscState    miscState;
    void                    *userData;
};

extern RpMatFXXboxMaterial *RpXboxMTEffectGetConfig(const RpMTEffect *effect);
extern RpMTEffect *RpXboxMTEffectCreate(RwUInt32 numStages);
extern void _rpMatFXXboxMaterialDestroy(RpMTEffect *effect);

#endif /* MULTITEXXBOX_H */
