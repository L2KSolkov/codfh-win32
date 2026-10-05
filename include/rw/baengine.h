/*
 * The engine's start-up and shut-down calls the game's start-up (sub_D99F0,
 * sub_D9BC0) makes, copied from RenderWare 3.7.2 RWSDK/src/baengine.h
 * (RwEngineOpenParams and the prototypes), bacamera.h (RwCameraGetFrame),
 * bamatrix.h (RwMatrixTolerance
 * and RwEngineSetMatrixTolerances), batextur.h, bacamera.h, rpworld.h,
 * rt2d.h and rt2danim.h (the free list parameters, the camera's start and
 * clip planes, the world's cameras, Rt2d's open, close and layer depth). The
 * database names several without the C underscore or under other names
 * (config/aliases.txt).
 */
#ifndef RW_BAENGINE_H
#define RW_BAENGINE_H

#include <math.h>

#include "rw/ostypes.h"
#include "rw/bamemory.h"
#include "rw/batypes.h"
#include "rw/bamatrix.h"
#include "rw/baframe.h"
#include "rw/baraster.h"

typedef struct RwEngineOpenParams RwEngineOpenParams;
struct RwEngineOpenParams
{
    void *displayID;
};

typedef struct RwMatrixTolerance RwMatrixTolerance;
struct RwMatrixTolerance
{
    RwReal Normal;
    RwReal Orthogonal;
    RwReal Identity;
};

/* The start of RwCamera (RWSDK/src/bacamera.h) up to its clip planes, and
 * RwCameraGetNearClipPlane. */
typedef struct RwCamera RwCamera;
struct RwCamera
{
    RwUInt8 object[0x14];
    RwInt32 projectionType;
    void *beginUpdate;
    void *endUpdate;
    RwMatrix viewMatrix;
    RwRaster *frameBuffer;
    RwRaster *zBuffer;
    RwV2d viewWindow;
    RwV2d recipViewWindow;
    RwV2d viewOffset;
    RwReal nearPlane;
    RwReal farPlane;
    RwReal fogPlane;
    RwReal zScale;
    RwReal zShift;
    /* The frustum's planes (the player's vf_064 tests a sphere against
     * them itself). */
    RwFrustumPlane frustumPlanes[6];
};
/* The sphere test (bacamera.h; the particle systems cull with it,
 * sub_F41D0). */
enum RwFrustumTestResult
{
    rwSPHEREOUTSIDE = 0,
    rwSPHEREBOUNDARY = 1,
    rwSPHEREINSIDE = 2,
    RWFRUSTUMTESTRESULTFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwFrustumTestResult RwFrustumTestResult;
#ifdef    __cplusplus
extern "C"
#endif
RwFrustumTestResult RwCameraFrustumTestSphere(const RwCamera *camera, const RwSphere *sphere);
#define RwCameraGetNearClipPlaneMacro(_camera) ((_camera)->nearPlane)
#define RwCameraGetNearClipPlane(_camera) RwCameraGetNearClipPlaneMacro(_camera)
/* RwCameraGetFrame (bacamera.h): the camera's frame, its object's parent. */
#define RwCameraGetFrame(_camera) ((RwFrame *)rwObjectGetParent(_camera))

/* The camera's rasters, frame setter and projection (bacamera.h), and the
 * video modes (badevice.h), as RenderWare Studio's camera helper uses them. */
#define RwCameraGetRaster(_camera) ((_camera)->frameBuffer)
#define RwCameraSetRaster(_camera, _raster) (((_camera)->frameBuffer = (_raster)), (_camera))
#define RwCameraGetZRaster(_camera) ((_camera)->zBuffer)
#define RwCameraSetZRaster(_camera, _raster) (((_camera)->zBuffer = (_raster)), (_camera))
#define RwCameraSetFrame(_camera, _frame) (_rwObjectHasFrameSetFrame((_camera), (_frame)))

enum RwCameraProjection
{
    rwNACAMERAPROJECTION = 0,
    rwPERSPECTIVE = 1,
    rwPARALLEL = 2,
    rwCAMERAPROJECTIONFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwCameraProjection RwCameraProjection;

enum RwVideoModeFlag
{
    rwVIDEOMODEEXCLUSIVE = 0x0001,
    rwVIDEOMODEINTERLACE = 0x0002,
    rwVIDEOMODEFFINTERLACE = 0x0004,
    rwVIDEOMODEFLAGFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwVideoModeFlag RwVideoModeFlag;

typedef struct RwVideoMode RwVideoMode;
struct RwVideoMode
{
    RwInt32 width;
    RwInt32 height;
    RwInt32 depth;
    RwVideoModeFlag flags;
    RwInt32 refRate;
    RwInt32 format;
};

#define RwTan(_x) ((RwReal)tan(_x))

typedef struct RpWorld RpWorld;

#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

extern RwBool RwEngineInit(const RwMemoryFunctions *memFuncs, RwUInt32 initFlags,
                           RwUInt32 resArenaSize);
extern RwBool RwEngineOpen(RwEngineOpenParams *initParams);
extern RwBool RwEngineStart(void);
extern RwBool RwEngineStop(void);
extern RwBool RwEngineClose(void);
extern RwBool RwEngineTerm(void);
extern RwBool RwEngineSetMatrixTolerances(const RwMatrixTolerance *tolerance);

extern void RwTextureSetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc);
extern void Rt2dBrushSetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc);
extern void Rt2dFontSetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc);
extern void Rt2dFontDictNodeSetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc);
extern void Rt2dPathSetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc);
extern void Rt2dObjectSetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc);
extern void Rt2dTriVertSetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc);
extern void Rt2dTriPolySetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc);

extern RwCamera *RwCameraShowRaster(RwCamera *camera, void *dev, RwUInt32 flags);
/* RW 3.7.2's RwCameraClearMode (bacamera.h). */
enum RwCameraClearMode
{
    rwCAMERACLEARIMAGE = 0x1,
    rwCAMERACLEARZ = 0x2,
    rwCAMERACLEARSTENCIL = 0x4
};
extern RwCamera *RwCameraClear(RwCamera *camera, RwRGBA *colour, RwInt32 clearMode);
/* The resource arena (baresour.h) and the LOD atomics' camera (rplodatm.h). */
extern RwBool RwResourcesEmptyArena(void);
extern RwCamera *RpLODAtomicSetCamera(RwCamera *camera);
extern RwCamera *RwCameraBeginUpdate(RwCamera *camera);
extern RwCamera *RwCameraEndUpdate(RwCamera *camera);
extern RwCamera *RwCameraSetNearClipPlane(RwCamera *camera, RwReal nearClip);
extern RwCamera *RwCameraSetFarClipPlane(RwCamera *camera, RwReal farClip);
extern RwCamera *RwCameraCreate(void);
extern RwBool RwCameraDestroy(RwCamera *camera);
extern RwCamera *RwCameraSetProjection(RwCamera *camera, RwCameraProjection projection);
extern RwCamera *RwCameraSetViewWindow(RwCamera *camera, const RwV2d *viewWindow);
extern struct RpWorld *RwCameraGetWorld(const RwCamera *camera);
extern void *_rwObjectHasFrameSetFrame(void *object, RwFrame *frame);
extern RwVideoMode *RwEngineGetVideoModeInfo(RwVideoMode *modeinfo, RwInt32 modeIndex);
extern RwInt32 RwEngineGetCurrentVideoMode(void);
extern RpWorld *RpWorldAddCamera(RpWorld *world, RwCamera *camera);
extern RpWorld *RpWorldRemoveCamera(RpWorld *world, RwCamera *camera);
extern RwBool RpWorldDestroy(RpWorld *world);
extern void Rt2dOpen(RwCamera *cam);
extern void Rt2dClose(void);
extern RwBool Rt2dDeviceSetLayerDepth(RwReal depth);
extern RwBool Rt2dAnimOpen(void);
extern void Rt2dAnimClose(void);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

#endif
