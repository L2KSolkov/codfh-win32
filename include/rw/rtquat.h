/*
 * RtQuat, copied from RenderWare 3.7.2 RWSDK/tool/quat/rtquat.h (the struct
 * and the modulus, reciprocal, multiply and unit-to-matrix macros; the image's
 * animation code, unit_07CA20, uses them as written). Entities take one to set their orientation
 * (the entity vf_0D4 implementations rotate by it: vector part at +0, scalar
 * at +0x0C).
 */
#ifndef RW_RTQUAT_H
#define RW_RTQUAT_H

#include "rw/batypes.h"
#include "rw/bavector.h"
#include "rw/bamatrix.h"

typedef struct RtQuat RtQuat;
struct RtQuat
{
    RwV3d               imag;   /**< The imaginary part(s) */
    RwReal              real;   /**< The real part */
};

#ifdef    __cplusplus
extern "C"
{
#endif
extern RwBool RtQuatConvertFromMatrix(RtQuat *const qpQuat, const RwMatrix *const mpMatrix);
extern RtQuat *RtQuatRotate(RtQuat *quat, const RwV3d *axis, RwReal angle, RwOpCombineType combineOp);
extern RwV3d *RtQuatTransformVectors(RwV3d *vectorsOut, const RwV3d *vectorsIn, const RwInt32 numPoints,
                                     const RtQuat *quat);
#ifdef    __cplusplus
}
#endif

#define RtQuatModulusSquaredMacro(q)                                  \
    ((q)->real * (q)->real + RwV3dDotProductMacro(&(q)->imag, &(q)->imag))

#define RtQuatReciprocalMacro(result, q)                              \
MACRO_START                                                           \
{                                                                     \
    /*                                                                \
     * Assumes result != q                                            \
     */                                                               \
    RwReal val = RtQuatModulusSquaredMacro(q);                        \
                                                                      \
    if (val > (RwReal) 0)                                             \
    {                                                                 \
        val = ((RwReal)1) / val;                                      \
        (result)->real = (q)->real * val;                             \
        val = -val;                                                   \
        RwV3dScaleMacro(&(result)->imag, &(q)->imag, val);            \
    }                                                                 \
}                                                                     \
MACRO_STOP

#define RtQuatMultiplyMacro(qpq, qp, qq)                              \
MACRO_START                                                           \
{                                                                     \
    /*                                                                \
     * Assumes qpq != qp && qpq != qq                                 \
     */                                                               \
    (qpq)->real =                                                     \
        (qp)->real * (qq)->real -                                     \
        RwV3dDotProductMacro(&(qp)->imag, &(qq)->imag);               \
    RwV3dCrossProductMacro(&(qpq)->imag, &(qp)->imag, &(qq)->imag);   \
    RwV3dIncrementScaledMacro(&(qpq)->imag, &(qq)->imag, (qp)->real); \
    RwV3dIncrementScaledMacro(&(qpq)->imag, &(qp)->imag, (qq)->real); \
}                                                                     \
MACRO_STOP

/* RW 3.7.2's RtQuatConvertToMatrix macro (AIData::sub_1ECF0 expands it for
 * a node's orientation). */
#define RtQuatConvertToMatrix(qpQuat, mpMatrix)                       \
MACRO_START                                                           \
{                                                                     \
    RwReal rS;                                                        \
    RwV3d rV;                                                         \
    RwV3d rW;                                                         \
    RwV3d square;                                                     \
    RwV3d cross;                                                      \
                                                                      \
    rS = ((RwReal) 2) / RtQuatModulusSquaredMacro((qpQuat));          \
                                                                      \
    RwV3dScaleMacro(&rV, &(qpQuat)->imag, rS);                        \
    RwV3dScaleMacro(&rW, &rV, (qpQuat)->real);                        \
                                                                      \
    square.x = (qpQuat)->imag.x * rV.x;                               \
    square.y = (qpQuat)->imag.y * rV.y;                               \
    square.z = (qpQuat)->imag.z * rV.z;                               \
                                                                      \
    cross.x = (qpQuat)->imag.y * rV.z;                                \
    cross.y = (qpQuat)->imag.z * rV.x;                                \
    cross.z = (qpQuat)->imag.x * rV.y;                                \
                                                                      \
    (mpMatrix)->right.x = ((RwReal) 1) - (square.y + square.z);       \
    (mpMatrix)->right.y = cross.z + rW.z;                             \
    (mpMatrix)->right.z = cross.y - rW.y;                             \
                                                                      \
    (mpMatrix)->up.x = cross.z - rW.z;                                \
    (mpMatrix)->up.y = ((RwReal) 1) - (square.z + square.x);          \
    (mpMatrix)->up.z = cross.x + rW.x;                                \
                                                                      \
    (mpMatrix)->at.x = cross.y + rW.y;                                \
    (mpMatrix)->at.y = cross.x - rW.x;                                \
    (mpMatrix)->at.z = ((RwReal) 1) - (square.x + square.y);          \
                                                                      \
    (mpMatrix)->pos.x = ((RwReal) 0);                                 \
    (mpMatrix)->pos.y = ((RwReal) 0);                                 \
    (mpMatrix)->pos.z = ((RwReal) 0);                                 \
                                                                      \
    rwMatrixSetFlags((mpMatrix),                                      \
                     (rwMATRIXTYPEORTHONORMAL &                       \
                      ~rwMATRIXINTERNALIDENTITY));                    \
}                                                                     \
MACRO_STOP

#define RtQuatUnitConvertToMatrix(qpQuat,mpMatrix)                    \
MACRO_START                                                           \
{                                                                     \
    const RwReal x = (qpQuat)->imag.x;                                \
    const RwReal y = (qpQuat)->imag.y;                                \
    const RwReal z = (qpQuat)->imag.z;                                \
    const RwReal w = (qpQuat)->real;                                  \
    RwV3d        square;                                              \
    RwV3d        cross;                                               \
    RwV3d        wimag;                                               \
                                                                      \
    square.x = x * x;                                                 \
    square.y = y * y;                                                 \
    square.z = z * z;                                                 \
                                                                      \
    cross.x = y * z;                                                  \
    cross.y = z * x;                                                  \
    cross.z = x * y;                                                  \
                                                                      \
    wimag.x = w * x;                                                  \
    wimag.y = w * y;                                                  \
    wimag.z = w * z;                                                  \
                                                                      \
    (mpMatrix)->right.x = 1 - 2 * (square.y + square.z);              \
    (mpMatrix)->right.y =     2 * (cross.z + wimag.z);                \
    (mpMatrix)->right.z =     2 * (cross.y - wimag.y);                \
                                                                      \
    (mpMatrix)->up.x    =     2 * (cross.z - wimag.z);                \
    (mpMatrix)->up.y    = 1 - 2 * (square.x + square.z);              \
    (mpMatrix)->up.z    =     2 * (cross.x + wimag.x);                \
                                                                      \
    (mpMatrix)->at.x    =     2 * (cross.y + wimag.y);                \
    (mpMatrix)->at.y    =     2 * (cross.x - wimag.x);                \
    (mpMatrix)->at.z    = 1 - 2 * (square.x + square.y);              \
                                                                      \
    (mpMatrix)->pos.x = 0;                                            \
    (mpMatrix)->pos.y = 0;                                            \
    (mpMatrix)->pos.z = 0;                                            \
                                                                      \
    rwMatrixSetFlags((mpMatrix),                                      \
                     rwMATRIXTYPEORTHONORMAL);                        \
}                                                                     \
MACRO_STOP

#endif
