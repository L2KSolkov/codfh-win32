/*
 * RpMTEffectDict (opaque) and RpMTEffectDictDestroy, after RenderWare 3.7.2
 * RWSDK/include/xbox/rpmteffect.h: the Xbox's multi-texture effect
 * dictionary, which RenderWare Studio's resource handler destroys
 * ("rwID_MTEFFECTDICT").
 */
#ifndef RW_RPMTEFFECT_H
#define RW_RPMTEFFECT_H

#include "rw/ostypes.h"

typedef struct RpMTEffectDict RpMTEffectDict;

#ifdef    __cplusplus
extern "C"
{
#endif

extern void RpMTEffectDictDestroy(RpMTEffectDict *dict);

#ifdef    __cplusplus
}
#endif

#endif
