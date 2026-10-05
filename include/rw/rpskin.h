/*
 * RpSkin, from RenderWare 3.7.2 RWSDK/plugin/skin2/rpskin.h: the opaque skin
 * and the queries the game calls (sub_79270 inverts each bone's
 * skin-to-bone matrix; sub_122820 asks whether a geometry is skinned).
 * RpSkinGeometryGetSkin is 0x2D12E0, which the database calls
 * _RpAtomicGetGeometry: it reads a geometry's plugin data at
 * _rpSkinGlobals.geometryOffset, which is RpSkinGeometryGetSkin
 * (config/aliases.txt).
 */
#ifndef RW_RPSKIN_H
#define RW_RPSKIN_H

#include "rw/bamatrix.h"
#include "rw/rpatomic.h"

typedef struct RpSkin RpSkin;

#ifdef    __cplusplus
extern "C"
{
#endif

extern const RwMatrix *RpSkinGetSkinToBoneMatrices(RpSkin *skin);
extern RpSkin *RpSkinGeometryGetSkin(RpGeometry *geometry);

#ifdef    __cplusplus
}
#endif

#endif
