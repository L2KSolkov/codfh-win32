/*
 * RtAnimAnimation, after RenderWare 3.7.2 RWSDK/tool/anim/rtanim.h (the
 * struct, and the interpolator info's type id), in the layout the image's
 * own animation code (unit_07CA20) builds: a flag byte before the frames.
 */
#ifndef RTANIM_H
#define RTANIM_H

#include "rw/ostypes.h"

typedef struct RtAnimInterpolatorInfo RtAnimInterpolatorInfo;
typedef struct RtAnimAnimation RtAnimAnimation;
// Destroys an animation (RenderWare Studio's resource handler, 0x1327F0; RpHAnimAnimationDestroy is it).
extern "C" RwBool RtAnimAnimationDestroy(RtAnimAnimation *animation);
struct RwStream;

// The interpolation scheme (64 bytes in the image; its type id leads, as in
// RWSDK's, then fifteen callbacks, the game's own set: those at +4 to +0x1C
// an interpolator copies (unit_07CA20's sub_80740), the one at +0x24 reads an
// animation's frames. unit_07CA20's sub_7DE10 registers the only scheme.
struct RtAnimInterpolatorInfo
{
    RwInt32 typeID;
    void *unk_04;
    void *unk_08;
    void *unk_0C;
    void *unk_10;
    void *unk_14;
    void *unk_18;
    void (*unk_1C)(struct type_7CBD0 *arg_0, struct type_7CBD0 *arg_4);
    void *unk_20;
    RtAnimAnimation *(*unk_24)(struct RwStream *arg_0, RtAnimAnimation *arg_4, RwInt32 arg_8);
    void *unk_28;
    void *unk_2C;
    void *unk_30;
    void *unk_34;
    void *unk_38;
    void *unk_3C;
};

struct RtAnimAnimation
{
    RtAnimInterpolatorInfo *interpInfo;
    RwInt32 numFrames;
    RwInt32 flags;
    RwReal duration;
    RwUInt8 unk_10;             // set when it owns its memory (sub_7FE60)
    void *pFrames;              // after the header, 16-aligned (sub_7FF20)
    void *customData;
};

#endif
