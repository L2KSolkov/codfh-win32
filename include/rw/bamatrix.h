/*
 * RwMatrix, copied from RenderWare 3.7.2 RWSDK/src/plcore/bamatrix.h (the
 * struct and its aligned typedef; see RWALIGN in rw/ostypes.h, the type and
 * flag enums, the flag accessors and RwMatrixSetIdentityMacro, which the
 * release build maps RwMatrixSetIdentity to, and the RwMatrixGet* accessor
 * macros). The game reads pos at +0x30
 * (sub_CD550); AIData's constructor sets its unk_D30 to identity inline.
 */
#ifndef RW_BAMATRIX_H
#define RW_BAMATRIX_H

#include "rw/batypes.h"

struct RwMatrixTag
{
    /* These are padded to be 16 byte quantities per line */
    RwV3d               right;
    RwUInt32            flags;
    RwV3d               up;
    RwUInt32            pad1;
    RwV3d               at;
    RwUInt32            pad2;
    RwV3d               pos;
    RwUInt32            pad3;
};

/*
 * RwMatrix & RwMatrixTag must be different otherwise the alignment
 * directive is ignored when compiling under C++ on Visual C
 */
typedef struct RwMatrixTag RWALIGN(RwMatrix, rwMATRIXALIGNMENT);

/**
 * \ingroup rwmatrix
 * \ref RwMatrixType
 * This type represents different matrix types
 */
enum RwMatrixType
{
    rwMATRIXTYPENORMAL = 0x00000001,
    rwMATRIXTYPEORTHOGONAL = 0x00000002,
    rwMATRIXTYPEORTHONORMAL = 0x00000003,
    rwMATRIXTYPEMASK = 0x00000003,
    rwMATRIXTYPEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwMatrixType RwMatrixType;

enum RwMatrixFlag
{
    rwMATRIXINTERNALIDENTITY = 0x00020000,
    rwMATRIXFLAGFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwMatrixFlag RwMatrixFlag;

#define rwMatrixSetFlags(m, flagsbit)     ((m)->flags = (flagsbit))
#define rwMatrixGetFlags(m)               ((m)->flags)

/* RW 3.7.2's RwMatrixInitialize (type_3DA6C0::sub_75AF0 sets a local's type
 * with it before inverting into it). */
#define RwMatrixInitializeMacro(m, t)\
MACRO_START                                                           \
{                                                                     \
    rwMatrixSetFlags((m), (t));                                       \
}                                                                     \
MACRO_STOP

#define RwMatrixSetIdentityMacro(m)                                   \
MACRO_START                                                           \
{                                                                     \
    (m)->right.x = (m)->up.y    = (m)->at.z    = (RwReal)((1.0));     \
    (m)->right.y = (m)->right.z = (m)->up.x    = (RwReal)((0.0));     \
    (m)->up.z    = (m)->at.x    = (m)->at.y    = (RwReal)((0.0));     \
    (m)->pos.x   = (m)->pos.y   = (m)->pos.z   = (RwReal)((0.0));     \
    rwMatrixSetFlags((m),                                             \
                     rwMatrixGetFlags(m) |                            \
                     (rwMATRIXINTERNALIDENTITY |                      \
                      rwMATRIXTYPEORTHONORMAL));                      \
}                                                                     \
MACRO_STOP

#define RwMatrixSetIdentity(m)   RwMatrixSetIdentityMacro(m)

/* The release build's accessor macros (non-RWDEBUG branch). */
#define RwMatrixGetRight(m)    (&(m)->right)
#define RwMatrixGetUp(m)       (&(m)->up)
#define RwMatrixGetAt(m)       (&(m)->at)
#define RwMatrixGetPos(m)      (&(m)->pos)

/**
 * \ingroup rwmatrix
 * RwOpCombineType
 * This type represents a combination operator which
 * can be applied to frames and matrices.
 */
enum RwOpCombineType
{
    rwCOMBINEREPLACE = 0,   /**<Replace -
                                all previous transformations are lost */
    rwCOMBINEPRECONCAT,     /**<Pre-concatenation -
                                the given transformation is applied
                                before all others */
    rwCOMBINEPOSTCONCAT,    /**<Post-concatenation -
                                the given transformation is applied
                                after all others */
    rwOPCOMBINETYPEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwOpCombineType RwOpCombineType;

#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

extern RwMatrix *RwMatrixCreate(void);
extern RwBool RwMatrixDestroy(RwMatrix *mpMat);
extern RwMatrix *RwMatrixOptimize(RwMatrix *matrix, const struct RwMatrixTolerance *tolerance);
extern RwMatrix *RwMatrixInvert(RwMatrix *dst, const RwMatrix *src);
extern RwMatrix *RwMatrixTranslate(RwMatrix *matrix, const RwV3d *translation,
                                   RwOpCombineType combineOp);
extern RwMatrix *RwMatrixTransform(RwMatrix *matrix, const RwMatrix *transform,
                                   RwOpCombineType combineOp);
extern RwMatrix *RwMatrixRotate(RwMatrix *matrix, const RwV3d *axis, RwReal angle,
                                RwOpCombineType combineOp);
extern RwMatrix *RwMatrixScale(RwMatrix *matrix, const RwV3d *scale, RwOpCombineType combineOp);
extern RwMatrix *RwMatrixOrthoNormalize(RwMatrix *dstMatrix, const RwMatrix *matrix);
extern RwMatrix *RwMatrixUpdate(RwMatrix *matrix);
extern const RwMatrix *RwMatrixQueryRotate(const RwMatrix *matrix, RwV3d *unitAxis, RwReal *angle,
                                           RwV3d *center);
extern RwMatrix *RwMatrixMultiply(RwMatrix *dstMatrix, const RwMatrix *matrixIn1, const RwMatrix *matrixIn2);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

/* RwMatrixCopy (bamatrix.h): a structure copy. */
#define RwMatrixCopy(_target, _source) (*(_target) = *(_source))

#endif
