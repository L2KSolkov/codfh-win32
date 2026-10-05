/*
 * RpUVAnimCreate and RpUVAnimDestroy, copied from RenderWare 3.7.2
 * RWSDK/plugin/uvanim/rpuvanim.h (the prototypes and the key frame type
 * only). The game calls the image's _RpUVAnimCreate (0x22B840) and
 * _RpUVAnimDestroy (0x22B890); the tracks' "VTrack" animation (sub_159AC0)
 * uses them.
 */
#ifndef RW_RPUVANIM_H
#define RW_RPUVANIM_H

#include "rw/ostypes.h"
#include "rw/rtanim.h"
#include "rw/bamatrix.h"

enum RpUVAnimKeyFrameType
{
    rpUVANIMLINEARKEYFRAMES,
    rpUVANIMPARAMKEYFRAMES,
    rpUVANIMKEYFRAMETYPEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RpUVAnimKeyFrameType RpUVAnimKeyFrameType;

typedef RtAnimAnimation RpUVAnim;

/* A UV animation key frame: the previous frame, its time and its data (for
 * linear key frames, a 2D matrix and a translation). */
typedef struct RpUVAnimKeyFrame RpUVAnimKeyFrame;
struct RpUVAnimKeyFrame
{
    RpUVAnimKeyFrame *prevFrame;
    RwReal time;
    RwReal data[6];
};

#ifdef    __cplusplus
extern "C"
{
#endif

extern RpUVAnim *RpUVAnimCreate(const RwChar *name, RwUInt32 numNodes, RwUInt32 numFrames, RwReal duration,
                                RwUInt32 *nodeIndexToUVChannelMap, RpUVAnimKeyFrameType keyframeType);
extern RwBool RpUVAnimDestroy(RpUVAnim *anim);
extern RpUVAnimKeyFrame *RpUVAnimKeyFrameInit(const RpUVAnim *anim, RpUVAnimKeyFrame *keyFrame,
                                              RpUVAnimKeyFrame *prevFrame, RwReal time, const RwMatrix *matrix);

#ifdef    __cplusplus
}
#endif

#endif
