#ifndef _SKINNULL_H
#define _SKINNULL_H

/*===========================================================================*
 *--- Include files ---------------------------------------------------------*
 *===========================================================================*/
#include <rwcore.h>
#include <rpworld.h>

#include "rpskin.h"

/*===========================================================================*
 *--- Global Types ----------------------------------------------------------*
 *===========================================================================*/
struct SkinPlatformData
{
#if defined(_XBOX)
    /* codfh-match: the Xbox skin's platform data (0x810 bytes; the
     * Godfather PDB's layout) */
    RwInt32  matrixIndexMap[256];
    RwInt32  vertexIndexMap[256];
    RwInt32  numBonesUsed;
    RwInt32  maxWeightsUsed;
    void    *weightsNindicesVB;
    RwInt32  weightsNindicesVBStride;
#else
    RwV3d *vertices;
    RwV3d *normals;
#endif
};

#if defined(_XBOX)
/* codfh-match: the Xbox skin pipelines (the Godfather PDB's enum) */
enum RpSkinXboxPipeline
{
    rpNASKINXBOXPIPELINE = 0,
    rpSKINXBOXPIPELINEGENERIC = 1,
    rpSKINXBOXPIPELINEMATFX = 2,
    rpSKINXBOXPIPELINETOON = 3,
    rpSKINXBOXPIPELINEMATFXTOON = 4,
    rpSKINXBOXPIPELINEMAX,
    rpSKINXBOXPIPELINEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RpSkinXboxPipeline RpSkinXboxPipeline;

struct SkinGlobalPlatform {
    RxPipeline *pipelines[rpSKINXBOXPIPELINEMAX - 1];
};
#else
struct SkinGlobalPlatform {
    RxPipeline *pipelines[rpSKINNULLPIPELINEMAX - 1];
};
#endif

/*===========================================================================*
 *--- Private Global Variables ----------------------------------------------*
 *===========================================================================*/

/*===========================================================================*
 *--- Private Defines -------------------------------------------------------*
 *===========================================================================*/
#define rpSKINMAXNUMBEROFMATRICES 256

#define _rpSkinPipeline(pipeline)                                       \
    (_rpSkinGlobals.platform.pipelines[pipeline - 1])

/*===========================================================================*
 *--- Private Functions -----------------------------------------------------*
 *===========================================================================*/

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _SKINNULL_H */
