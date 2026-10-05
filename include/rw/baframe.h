/*
 * RwFrame (its start), RwFrameCreate, RwFrameSetIdentity, RwFrameGetMatrix,
 * RwFrameGetLTM, RwFrameTranslate,
 * RwFrameOrthoNormalize, RwFrameUpdateObjects, RwFrameTransform,
 * RwFrameAddChild, RwFrameRemoveChild, RwFrameGetParent and
 * RwFrameForAllChildren and RwFrameForAllObjects (with their callback types and
 * rwObjectSetParent), copied
 * from RenderWare 3.7.2 RWSDK/src/baframe.h (the prototypes only). The game
 * calls the image's _RwFrameGetLTM, _RwFrameTranslate,
 * _RwFrameOrthoNormalize, _RwFrameUpdateObjects and _RwFrameTransform (the
 * database's _RwFrameTranslate_0; config/aliases.txt).
 */
#ifndef RW_BAFRAME_H
#define RW_BAFRAME_H

#include "rw/bamatrix.h"

typedef struct RwFrame RwFrame;

/* RwObject (RWSDK/src/batypes.h): the header every RenderWare object starts
 * with, and its parent accessor (rwObjectGetParent). */
typedef struct RwObject RwObject;
struct RwObject
{
    RwUInt8 type;
    RwUInt8 subType;
    RwUInt8 flags;
    RwUInt8 privateFlags;
    void *parent;
};
#define rwObjectGetParent(object) (((const RwObject *)(object))->parent)
#define rwObjectSetParent(c,p)    (((RwObject *)(c))->parent) = (void *)(p)

/* The start of RwFrame (RWSDK/src/baframe.h): the object header and dirty
 * list link, then the modelling and world (LTM) matrices and
 * the object list and the hierarchy links; the rest is not declared. */
struct RwFrame
{
    RwObject object;
    RwLLLink inDirtyListLink;
    RwMatrix modelling;
    RwMatrix ltm;
    /* The objects attached to the frame (RenderWare Studio's FrameHelper
     * destroys a frame only when it is empty). */
    RwLinkList objectList;
    /* Its first child, next sibling and hierarchy's root (sub_7F3C0 links
     * the root into the dirty list). */
    struct RwFrame *child;
    struct RwFrame *next;
    struct RwFrame *root;
};

#define RwFrameGetMatrix(_f) (&(_f)->modelling)
#define RwFrameGetParent(_f) ((RwFrame *)rwObjectGetParent(_f))

typedef RwFrame *(*RwFrameCallBack)(RwFrame *frame, void *data);
typedef RwObject *(*RwObjectCallBack)(RwObject *object, void *data);

#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

/* RenderWare's pending frame update (the world manager syncs it before
 * and after emptying a world). */
extern RwBool _rwFrameSyncDirty(void);

extern RwFrame *
RwFrameCreate(void);

extern RwBool
RwFrameDestroy(RwFrame * frame);

extern RwBool
RwFrameDestroyHierarchy(RwFrame * frame);

extern RwFrame *
RwFrameSetIdentity(RwFrame * frame);

extern RwMatrix *
RwFrameGetLTM(RwFrame * frame);

/* Whether the frame's hierarchy is waiting for an update (sub_7F3C0). */
extern RwBool
RwFrameDirty(const RwFrame * frame);

extern RwFrame *
RwFrameTranslate(RwFrame * frame,
                 const RwV3d * v, RwOpCombineType combine);

extern RwFrame *
RwFrameOrthoNormalize(RwFrame * frame);

extern RwFrame *
RwFrameUpdateObjects(RwFrame * frame);

extern RwFrame *
RwFrameTransform(RwFrame * frame,
                 const RwMatrix * m, RwOpCombineType combine);

extern RwFrame *
RwFrameAddChild(RwFrame * parent, RwFrame * child);

extern RwFrame *
RwFrameRemoveChild(RwFrame * child);

extern RwFrame *
RwFrameForAllChildren(RwFrame * frame,
                      RwFrameCallBack callBack, void *data);

extern RwFrame *
RwFrameForAllObjects(RwFrame * frame,
                     RwObjectCallBack callBack, void *data);

extern RwFrame *
RwFrameRotate(RwFrame * frame,
              const RwV3d * axis, RwReal angle, RwOpCombineType combine);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

#endif
