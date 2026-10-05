/*
 * RwV3d macros and functions, copied from RenderWare 3.7.2
 * RWSDK/src/plcore/bavector.h: RwV3dAddMacro, RwV3dSubMacro, RwV3dScaleMacro,
 * RwV3dIncrementScaledMacro,
 * RwV3dDotProductMacro, RwV3dCrossProductMacro and RwV3dAssignMacro, the
 * release-build names that map onto them (the non-RWDEBUG branch), and the
 * RwV3dNormalize, RwV3dLength and RwV3dTransformPoint prototypes. The game
 * compiles these inline; the do/while(0) of RwV3dSub is visible in its code
 * as `xor eax, eax; jnz`.
 */
#ifndef RW_BAVECTOR_H
#define RW_BAVECTOR_H

#include "rw/batypes.h"
#include "rw/bamatrix.h"

#define RwV3dSubMacro(o, a, b)                                  \
MACRO_START                                                     \
{                                                               \
    (o)->x = (((a)->x) - ( (b)->x));                            \
    (o)->y = (((a)->y) - ( (b)->y));                            \
    (o)->z = (((a)->z) - ( (b)->z));                            \
}                                                               \
MACRO_STOP

#define RwV3dDotProductMacro(a, b)                              \
    ((((( (((a)->x) * ((b)->x))) +                              \
        ( (((a)->y) * ((b)->y))))) +                            \
        ( (((a)->z) * ((b)->z)))))

#define RwV3dAddMacro(o, a, b)                                  \
MACRO_START                                                     \
{                                                               \
    (o)->x = (((a)->x) + ( (b)->x));                            \
    (o)->y = (((a)->y) + ( (b)->y));                            \
    (o)->z = (((a)->z) + ( (b)->z));                            \
}                                                               \
MACRO_STOP

#define RwV3dScaleMacro(o, a, s)                                \
MACRO_START                                                     \
{                                                               \
    (o)->x = (((a)->x) * ( (s)));                               \
    (o)->y = (((a)->y) * ( (s)));                               \
    (o)->z = (((a)->z) * ( (s)));                               \
}                                                               \
MACRO_STOP

#define RwV3dIncrementScaledMacro(o, a, s)                      \
MACRO_START                                                     \
{                                                               \
    (o)->x += (((a)->x) * ( (s)));                              \
    (o)->y += (((a)->y) * ( (s)));                              \
    (o)->z += (((a)->z) * ( (s)));                              \
}                                                               \
MACRO_STOP

#define RwV3dCrossProductMacro(o, a, b)                         \
MACRO_START                                                     \
{                                                               \
    (o)->x =                                                    \
        (( (((a)->y) * ( (b)->z))) -                            \
         ( (((a)->z) * ( (b)->y))));                            \
    (o)->y =                                                    \
        (( (((a)->z) * ( (b)->x))) -                            \
         ( (((a)->x) * ( (b)->z))));                            \
    (o)->z =                                                    \
        (( (((a)->x) * ( (b)->y))) -                            \
         ( (((a)->y) * ( (b)->x))));                            \
}                                                               \
MACRO_STOP

#define RwV3dNegateMacro(o, a)                                  MACRO_START                                                     {                                                                   (o)->x = -(a)->x;                                               (o)->y = -(a)->y;                                               (o)->z = -(a)->z;                                           }                                                               MACRO_STOP

#define RwV3dAssignMacro(_target, _source)                     \
    ( *(_target) = *(_source) )

#define RwV3dAssign(o, a)               RwV3dAssignMacro(o, a)
#define RwV3dAdd(o, a, b)               RwV3dAddMacro(o, a, b)
#define RwV3dScale(o, a, s)             RwV3dScaleMacro(o, a, s)
#define RwV3dSub(o, a, b)               RwV3dSubMacro(o, a, b)
#define RwV3dDotProduct(a, b)           RwV3dDotProductMacro(a, b)
#define RwV3dCrossProduct(o, a, b)      RwV3dCrossProductMacro(o, a, b)
#define RwV3dNegate(o, a)               RwV3dNegateMacro(o, a)

/* Function prototypes (RWSDK/src/plcore/bavector.h). */
#ifdef    __cplusplus
extern "C"
{
#endif         /* __cplusplus */

extern RwReal RwV3dNormalize(RwV3d * out, const RwV3d * in);
extern RwReal RwV3dLength(const RwV3d * in);
extern RwV3d *RwV3dTransformPoint(RwV3d * pointOut,
                                  const RwV3d * pointIn,
                                  const RwMatrix * matrix);
extern RwV3d *RwV3dTransformPoints(RwV3d * pointsOut,
                                   const RwV3d * pointsIn,
                                   RwInt32 numPoints,
                                   const RwMatrix * matrix);
extern RwV3d *RwV3dTransformVector(RwV3d * vectorOut,
                                   const RwV3d * vectorIn,
                                   const RwMatrix * matrix);

#ifdef    __cplusplus
}
#endif         /* __cplusplus */

#endif
