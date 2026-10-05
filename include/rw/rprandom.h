/*
 * RpRandom, copied from RenderWare 3.7.2 RWSDK/plugin/random/rprandom.h (the
 * RPRANDMAX define and the RpRandom/RpRandomSeed prototypes only). The game
 * calls the image's _RpRandom; its maximum is RPRANDMAX (2^31 - 1).
 */
#ifndef RPRANDOM_H
#define RPRANDOM_H

#include "rw/ostypes.h"

#define RPRANDMAX (~((~0)<<31))

#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

extern RwUInt32 RpRandom(void);
extern void RpRandomSeed(RwUInt32 seed);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

#endif /* RPRANDOM_H */
