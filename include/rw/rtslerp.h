/*
 * RtSlerp, copied from RenderWare 3.7.2 RWSDK/tool/slerp/rtslerp.h (the
 * struct and the four functions the image links at 0x2E5900 to 0x2E5AE0;
 * the mounted weapon's fire, type_3DA558::vf_018, blends its aim with them).
 */
#ifndef RW_RTSLERP_H
#define RW_RTSLERP_H

#include "rw/batypes.h"
#include "rw/bamatrix.h"

typedef struct RtSlerp RtSlerp;
struct RtSlerp
{
    RwInt32             matRefs;    /**< Which matrices are referenced */
    RwMatrix           *startMat;   /**< The start matrix */
    RwMatrix           *endMat;     /**< The end matrix */
    RwV3d               axis;       /**< The axis of rotation */
    RwReal              angle;      /**< The angle between the matrices */
    RwBool              useLerp;    /**< Whether to interpolate linearly */
};

#ifdef    __cplusplus
extern "C"
{
#endif
extern RtSlerp *RtSlerpCreate(RwInt32 nMatRefMask);
extern void RtSlerpDestroy(RtSlerp *spSlerp);
extern RwMatrix *RtSlerpGetMatrix(RtSlerp *spSlerp, RwMatrix *mpResultMat, RwReal nDelta);
extern RtSlerp *RtSlerpInitialize(RtSlerp *spSlerp, RwMatrix *mpMat1, RwMatrix *mpMat2);
#ifdef    __cplusplus
}
#endif

#endif
