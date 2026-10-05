/*
 * RpLight, RpLightType, RpLightGetType, RpLightSetFlags,
 * RpLightSetFrame, RpLightGetFrame, RpLightDestroy and the light functions the game calls, copied from
 * RenderWare 3.7.2 RWSDK/include/null/rpworld.h (the struct's
 * start only: its object header, whose subType is the light's type and
 * whose flags are its flags; RwObjectHasFrame's link and sync callback stay
 * opaque).
 */
#ifndef RW_RPLIGHT_H
#define RW_RPLIGHT_H

#include "rw/batypes.h"
#include "rw/baframe.h"

enum RpLightType
{
    rpNALIGHTTYPE = 0,
    rpLIGHTDIRECTIONAL,
    rpLIGHTAMBIENT,
    rpLIGHTPOINT = 0x80,
    rpLIGHTSPOT,
    rpLIGHTSPOTSOFT
};
typedef enum RpLightType RpLightType;

enum RpLightFlag
{
    rpLIGHTLIGHTATOMICS = 0x01,
    rpLIGHTLIGHTWORLD = 0x02
};

typedef struct RpLight RpLight;
struct RpLight
{
    RwObject object;
    RwUInt8 objectHasFrameRest[0xC];
    RwReal radius;
    RwRGBAReal color;
};

#define RpLightGetType(_light) ((RpLightType)((_light)->object.subType))
#define RpLightSetFlags(_light, _flags) ((_light)->object.flags = (RwUInt8)(_flags))
#define RpLightSetFrame(_light, _frame) (_rwObjectHasFrameSetFrame((_light), (_frame)))
#define RpLightGetFrame(_light) ((RwFrame *)rwObjectGetParent((_light)))

#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

extern RpLight *RpLightCreate(RwInt32 type);
extern RwBool RpLightDestroy(RpLight *light);
extern RpLight *RpLightSetColor(RpLight *light, const RwRGBAReal *color);
extern RpLight *RpLightSetRadius(RpLight *light, RwReal radius);
extern RpLight *RpLightSetConeAngle(RpLight *light, RwReal angle);
extern void *_rwObjectHasFrameSetFrame(void *object, RwFrame *frame);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

#endif
