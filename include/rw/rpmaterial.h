/*
 * RpMaterial (its texture and colour, with their accessors), RpMaterialSetTexture,
 * RpGeometryForAllMaterials, RpMatFXMaterialGetEffects
 * and the UV animation calls the game makes, copied from RenderWare 3.7.2
 * RWSDK/include/null/rpworld.h, rpmatfx.h and rpuvanim.h (prototypes and the
 * effects enum only).
 */
#ifndef RW_RPMATERIAL_H
#define RW_RPMATERIAL_H

#include "rw/batypes.h"
#include "rw/rpatomic.h"

/* RpMaterial: its texture and colour (with the colour accessors), its
 * pipeline, surface properties and reference count (the animated textures,
 * unit_143CE0, only change materials still referenced). */
typedef struct RwTexture RwTexture;
typedef struct RpMaterial RpMaterial;
struct RpMaterial
{
    RwTexture          *texture;
    RwRGBA              color;
    void               *pipeline;
    RwReal              surfaceProps[3];  /* RwSurfaceProperties */
    RwInt16             refCount;
    RwInt16             pad;
};
#define RpMaterialGetTextureMacro(_material) ((_material)->texture)
#define RpMaterialGetTexture(_material) RpMaterialGetTextureMacro(_material)
#define RwRGBAAssign(_target, _source) ( *(_target) = *(_source) )
#define RpMaterialGetColorMacro(_material) (&((_material)->color))
#define RpMaterialGetColor(_material) RpMaterialGetColorMacro(_material)
#define RpMaterialSetColorMacro(_material, _color)                      \
    (RwRGBAAssign(&((_material)->color), (_color)), (_material))
#define RpMaterialSetColor(_material, _color) RpMaterialSetColorMacro(_material, _color)
typedef RpMaterial *(*RpMaterialCallBack)(RpMaterial *material, void *data);

enum RpMatFXMaterialFlags
{
    rpMATFXEFFECTNULL = 0,
    rpMATFXEFFECTBUMPMAP = 1,
    rpMATFXEFFECTENVMAP = 2,
    rpMATFXEFFECTBUMPENVMAP = 3,
    rpMATFXEFFECTDUAL = 4,
    rpMATFXEFFECTUVTRANSFORM = 5,
    rpMATFXEFFECTDUALUVTRANSFORM = 6
};

#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

extern RpMaterial *RpMaterialSetTexture(RpMaterial *material, RwTexture *texture);
extern RpGeometry *RpGeometryForAllMaterials(RpGeometry *geometry, RpMaterialCallBack fpCallBack,
                                             void *pData);
extern RwInt32 RpMatFXMaterialGetEffects(const RpMaterial *material);
extern RpMaterial *RpMaterialUVAnimAddAnimTime(RpMaterial *material, RwReal deltaTime);
extern RpMaterial *RpMaterialUVAnimApplyUpdate(RpMaterial *material);
extern RwBool RpMaterialUVAnimExists(const RpMaterial *material);
extern RpMaterial *RpMaterialUVAnimSetCurrentTime(RpMaterial *material, RwReal time);
extern RpMaterial *RpMaterialSetUVAnim(RpMaterial *material, struct RtAnimAnimation *anim, RwUInt32 slot);
extern RpMaterial *RpMatFXMaterialSetEffects(RpMaterial *material, enum RpMatFXMaterialFlags flags);
extern struct RpAtomic *RpMatFXAtomicEnableEffects(struct RpAtomic *atomic);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

#endif
