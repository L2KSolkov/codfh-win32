/*
 * RpHAnim, copied from RenderWare 3.7.2 RWSDK/plugin/hanim/rphanim.h (the
 * hierarchy struct, node info and flags, with the interpolator opaque, and the two
 * prototypes the recovered source calls). The game calls the image's _RpHAnimIDGetIndex and
 * _RpHAnimHierarchyGetMatrixArray.
 */
#ifndef RPHANIM_H
#define RPHANIM_H

#include "rw/bamatrix.h"

typedef struct RpHAnimHierarchy RpHAnimHierarchy;
typedef struct RpHAnimNodeInfo RpHAnimNodeInfo;
typedef struct RtAnimInterpolator RtAnimInterpolator;
struct RwFrame;

/* The hierarchy flags (RW 3.7.2's RpHAnimHierarchyFlag); sub_EC310 tests
 * rpHANIMHIERARCHYLOCALSPACEMATRICES. */
enum RpHAnimHierarchyFlag
{
    rpHANIMHIERARCHYSUBHIERARCHY = 0x01,
    rpHANIMHIERARCHYNOMATRICES = 0x02,
    rpHANIMHIERARCHYUPDATEMODELLINGMATRICES = 0x1000,
    rpHANIMHIERARCHYUPDATELTMS = 0x2000,
    rpHANIMHIERARCHYLOCALSPACEMATRICES = 0x4000
};

/* RW 3.7.2's node info, 16 bytes (sub_EC310 indexes it and reads pFrame). */
struct RpHAnimNodeInfo
{
    RwInt32             nodeID;
    RwInt32             nodeIndex;
    RwInt32             flags;
    struct RwFrame     *pFrame;
};

struct RpHAnimHierarchy
{
    RwInt32             flags;
    RwInt32             numNodes;
    RwMatrix           *pMatrixArray;
    void               *pMatrixArrayUnaligned;
    RpHAnimNodeInfo    *pNodeInfo;
    struct RwFrame     *parentFrame;
    RpHAnimHierarchy   *parentHierarchy;
    RwInt32             rootParentOffset;
    RtAnimInterpolator *currentAnim;
};

#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

extern RwInt32 RpHAnimIDGetIndex(RpHAnimHierarchy *hierarchy, RwInt32 ID);
extern RwMatrix *RpHAnimHierarchyGetMatrixArray(RpHAnimHierarchy *hierarchy);
extern RpHAnimHierarchy *RpHAnimHierarchyAttach(RpHAnimHierarchy *hierarchy);
extern RwBool RpHAnimFrameSetHierarchy(struct RwFrame *frame, RpHAnimHierarchy *hierarchy);
extern RwInt32 RpHAnimFrameGetID(struct RwFrame *frame);
extern RpHAnimHierarchy *RpHAnimFrameGetHierarchy(struct RwFrame *frame);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

#endif /* RPHANIM_H */
