/*
 * RpSpline, copied from RenderWare 3.7.2 RWSDK/plugin/spline/rpspline.h (the
 * typedef only; the struct stays opaque until its fields are needed) and the
 * prototypes the recovered source calls. The game passes one to
 * _RpSplineGetNumControlPoints and _RpSplineFindPosition; RenderWare
 * Studio's spline resource handler reads and destroys them.
 */
#ifndef RW_RPSPLINE_H
#define RW_RPSPLINE_H

#include "rw/batypes.h"

typedef struct RpSpline RpSpline;

/* The path types (RwSplinePath in RWSDK); only the one the game passes. */
enum RpSplinePath
{
    rpSPLINEPATHSMOOTH = 10
};

/* The spline's chunk id, MAKECHUNKID(rwVENDORID_CORE, 0x0C) (rwplcore.h). */
#define rwID_SPLINE 0x0C

#ifdef    __cplusplus
extern "C"
{
#endif         /* __cplusplus */

struct RwStream;
extern RpSpline *RpSplineStreamRead(struct RwStream *stream);
extern RwBool RpSplineDestroy(RpSpline *spline);
extern RwInt32 RpSplineGetNumControlPoints(const RpSpline *spline);
extern RpSpline *RpSplineFindPosition(RpSpline *spline, RwInt32 path, RwReal where,
                                      RwV3d *pos, RwV3d *tangent);

#ifdef    __cplusplus
}
#endif         /* __cplusplus */

#endif
