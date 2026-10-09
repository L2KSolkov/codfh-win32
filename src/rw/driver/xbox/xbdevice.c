/*
 * codfh-match: RenderWare 3.6's Xbox driver device (driver/xbox/xbdevice.c),
 * which the 3.7.2 tree does not have. Written from the image after the tree's
 * driver/d3d8/d3d8device.c (the camera, clear, standards and system request
 * shapes) and the Godfather debug build's copy of this file (the Xbox-only
 * parts and the names).
 */

#include <xtl.h>

#include "batypes.h"
#include "batype.h"
#include "balibtyp.h"
#include "barwtyp.h"
#include "badebug.h"
#include "bamemory.h"
#include "badevice.h"
#include "bamatrix.h"
#include "baframe.h"
#include "bacamera.h"
#include "baraster.h"
#include "batextur.h"
#include "baimmedi.h"

#include "xbraster.h"
#include "xbdevice.h"
#include "xbmemory.h"
#include "xbcache.h"
#include "xbrendst.h"
#include "xbconvrt.h"
#include "xb2drend.h"
#include "xbtexdic.h"
#include "xbsprite.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x0051F2A0
RwRwDeviceGlobals dgGGlobals;
// End of its data definitions.


/* RenderWare 3.6's RCS id string, which the image keeps (the 3.7.2 tree has none) */
static const char rcsid[] = "@@@@(#)$Id: //RenderWare/RW36Active/rwsdk/driver/xbox/xbdevice.c#2 $";

/* The device globals (the Godfather PDB's names). */
_rxXboxDriverGlobals _RwXbDeviceGlobals;

static D3DPRESENT_PARAMETERS present;

/* The material RwXbSetSurfaceProperties sets. */
static D3DMATERIAL8 material =
{
    { 0.0f, 0.0f, 0.0f, 1.0f },     /* Diffuse */
    { 0.0f, 0.0f, 0.0f, 1.0f },     /* Ambient */
    { 0.0f, 0.0f, 0.0f, 1.0f },     /* Specular */
    { 0.0f, 0.0f, 0.0f, 1.0f },     /* Emissive */
    0.0f                            /* Power */
};

static D3DMATRIX projMatrix =
{
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
};

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: _rcsid @ 0x00416BE0
// match: ?clearFlagsConvTable@?1??_rwXbCameraClear@@9@9 @ 0x00416C28
// match: ??_C@_04EPMMMID@Xbox?$AA@ @ 0x00416C48
// match: ??_C@_0BJ@PCHCADDF@Invalid?5subsystem?5number?$AA@ @ 0x00416C50
// match: _material @ 0x00435640
// match: _projMatrix @ 0x00435688
// match: ?rwXbDriverDevice@?1??_rwDeviceGetHandle@@9@9 @ 0x004356C8

// match: _RwXbSetSurfaceProperties @ 0x002B3490
// sp-match: _RwXbSetSurfaceProperties @ 0x001CE8B0

RwBool
RwXbSetSurfaceProperties(const RwRGBA *color, const RwSurfaceProperties *surfaceProps,
                         RwBool modulate)
{
    if (modulate && *((const RwUInt32 *)color) != 0xffffffff)
    {
        const RwReal    diffScale = surfaceProps->diffuse * (1.0f / 255.0f);
        const RwReal    ambScale = surfaceProps->ambient * (1.0f / 255.0f);

        material.Diffuse.r = color->red * diffScale;
        material.Diffuse.g = color->green * diffScale;
        material.Diffuse.b = color->blue * diffScale;
        material.Diffuse.a = color->alpha * (1.0f / 255.0f);

        material.Ambient.r = color->red * ambScale;
        material.Ambient.g = color->green * ambScale;
        material.Ambient.b = color->blue * ambScale;
        material.Ambient.a = color->alpha * (1.0f / 255.0f);
    }
    else
    {
        material.Diffuse.r = surfaceProps->diffuse;
        material.Diffuse.g = surfaceProps->diffuse;
        material.Diffuse.b = surfaceProps->diffuse;
        material.Diffuse.a = 1.0f;

        material.Ambient.r = surfaceProps->ambient;
        material.Ambient.g = surfaceProps->ambient;
        material.Ambient.b = surfaceProps->ambient;
        material.Ambient.a = 1.0f;
    }

    D3DDevice_SetMaterial(&material);

    return TRUE;
}

// match: _XbFindDepth @ 0x002B35E0
// sp-match: _XbFindDepth @ 0x001CEA00
static RwInt32
XbFindDepth(D3DFORMAT format)
{
    RwInt32         depth;

    switch (format)
    {
        case D3DFMT_A8R8G8B8:
        case D3DFMT_X8R8G8B8:
        case D3DFMT_LIN_A8R8G8B8:
        case D3DFMT_LIN_X8R8G8B8:
            depth = 32;
            break;

        case D3DFMT_R5G6B5:
        case D3DFMT_X1R5G5B5:
        case D3DFMT_LIN_R5G6B5:
        case D3DFMT_LIN_X1R5G5B5:
            depth = 16;
            break;

        default:
            depth = 0;
            break;
    }

    return depth;
}

// match: _XbFindRWFormat @ 0x002B3630
// sp-match: _XbFindRWFormat @ 0x001CEA50
static RwInt32
XbFindRWFormat(D3DFORMAT format)
{
    RwInt32         rwformat;

    switch (format)
    {
        case D3DFMT_A8R8G8B8:
        case D3DFMT_LIN_A8R8G8B8:
            rwformat = rwRASTERFORMAT8888;
            break;

        case D3DFMT_X8R8G8B8:
        case D3DFMT_LIN_X8R8G8B8:
            rwformat = rwRASTERFORMAT888;
            break;

        case D3DFMT_R5G6B5:
        case D3DFMT_LIN_R5G6B5:
            rwformat = rwRASTERFORMAT565;
            break;

        case D3DFMT_X1R5G5B5:
        case D3DFMT_LIN_X1R5G5B5:
            rwformat = rwRASTERFORMAT555;
            break;

        case D3DFMT_A1R5G5B5:
        case D3DFMT_LIN_A1R5G5B5:
            rwformat = rwRASTERFORMAT1555;
            break;

        default:
            rwformat = 0;
            break;
    }

    return rwformat;
}

// match: _RwXboxDeviceConfigGetDefaultValues @ 0x002B36A0
// sp-match: _RwXboxDeviceConfigGetDefaultValues @ 0x001CEAC0
void
RwXboxDeviceConfigGetDefaultValues(RwXboxDeviceConfig *deviceConfig)
{
    D3DDISPLAYMODE  mode;

    Direct3D_EnumAdapterModes(0, 0, &mode);

    deviceConfig->backBufferWidth = mode.Width;
    deviceConfig->backBufferHeight = mode.Height;
    deviceConfig->backBufferFormat = mode.Format;
    deviceConfig->backBufferCount = 1;
    deviceConfig->multiSampleType = D3DMULTISAMPLE_NONE;
    deviceConfig->swapEffect = D3DSWAPEFFECT_DISCARD;
    deviceConfig->depthStencilFormat = D3DFMT_D24S8;
    deviceConfig->flags = mode.Flags;
    deviceConfig->refreshRateInHz = mode.RefreshRate;
    deviceConfig->presentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
}

// match: _XbDeviceSystemOpen @ 0x002B3700
// sp-match: _XbDeviceSystemOpen @ 0x001CEB20
static RwBool
XbDeviceSystemOpen(void *in)
{
    const RwXboxDeviceConfig *deviceConfig = *(const RwXboxDeviceConfig **)in;

    memset(&_RwXbDeviceGlobals, 0, sizeof(_RwXbDeviceGlobals));

    _RwXbDeviceGlobals.object = Direct3DCreate8(D3D_SDK_VERSION);
    if (_RwXbDeviceGlobals.object == NULL)
    {
        return FALSE;
    }

    rwstrcpy(_RwXbDeviceGlobals.name, RWSTRING("Xbox"));

    _RwXbDeviceGlobals.modeCount = Direct3D_GetAdapterModeCount(0);
    _RwXbDeviceGlobals.currentModeIndex = 0;

    if (deviceConfig != NULL)
    {
        RwInt32         i;

        _RwXbDeviceGlobals.config = *deviceConfig;

        /* Find the mode the configuration asks for */
        for (i = 0; i < _RwXbDeviceGlobals.modeCount; i++)
        {
            D3DDISPLAYMODE  mode;

            Direct3D_EnumAdapterModes(0, i, &mode);

            if (mode.Width == deviceConfig->backBufferWidth &&
                mode.Height == deviceConfig->backBufferHeight &&
                XbFindRWFormat(mode.Format) == XbFindRWFormat(deviceConfig->backBufferFormat) &&
                (deviceConfig->refreshRateInHz == 0 ||
                 mode.RefreshRate == deviceConfig->refreshRateInHz) &&
                mode.Flags == (deviceConfig->flags & 0x1F0))
            {
                _RwXbDeviceGlobals.currentModeIndex = i;
                break;
            }
        }

        if (i >= _RwXbDeviceGlobals.modeCount)
        {
            Direct3D_Release();
            _RwXbDeviceGlobals.object = NULL;
            return FALSE;
        }
    }
    else
    {
        RwXboxDeviceConfigGetDefaultValues(&_RwXbDeviceGlobals.config);
    }

    _RwXbDeviceGlobals.displayDepth = XbFindDepth(_RwXbDeviceGlobals.config.backBufferFormat);

    if (_RwXbDeviceGlobals.config.depthStencilFormat == D3DFMT_D24S8 ||
        _RwXbDeviceGlobals.config.depthStencilFormat == D3DFMT_F24S8 ||
        _RwXbDeviceGlobals.config.depthStencilFormat == D3DFMT_LIN_D24S8 ||
        _RwXbDeviceGlobals.config.depthStencilFormat == D3DFMT_LIN_F24S8)
    {
        _RwXbDeviceGlobals.zBufferDepth = 32;
    }
    else
    {
        _RwXbDeviceGlobals.zBufferDepth = 16;
    }

    /* Flush denormals to zero */
    _mm_setcsr(_mm_getcsr() | 0x8000);

    return TRUE;
}

// match: _XbDeviceSystemStart @ 0x002B3880
// sp-match: _XbDeviceSystemStart @ 0x001CECA0
static RwBool
XbDeviceSystemStart(void)
{
    memset(&present, 0, sizeof(present));

    present.SwapEffect = (D3DSWAPEFFECT)_RwXbDeviceGlobals.config.swapEffect;
    present.EnableAutoDepthStencil = TRUE;
    present.BackBufferCount = _RwXbDeviceGlobals.config.backBufferCount;
    present.BackBufferWidth = _RwXbDeviceGlobals.config.backBufferWidth;
    present.BackBufferHeight = _RwXbDeviceGlobals.config.backBufferHeight;
    present.BackBufferFormat = (D3DFORMAT)_RwXbDeviceGlobals.config.backBufferFormat;
    present.AutoDepthStencilFormat = (D3DFORMAT)_RwXbDeviceGlobals.config.depthStencilFormat;
    present.MultiSampleType = (D3DMULTISAMPLE_TYPE)_RwXbDeviceGlobals.config.multiSampleType;
    present.FullScreen_RefreshRateInHz = _RwXbDeviceGlobals.config.refreshRateInHz;
    present.Flags = _RwXbDeviceGlobals.config.flags;
    present.FullScreen_PresentationInterval = _RwXbDeviceGlobals.config.presentationInterval;

    if (D3D_OK != Direct3D_CreateDevice(0, D3DDEVTYPE_HAL, NULL,
                                        D3DCREATE_HARDWARE_VERTEXPROCESSING,
                                        &present, &_RwXbDeviceGlobals.device))
    {
        return FALSE;
    }

    D3DDevice_GetRenderTarget(&_RwXbDeviceGlobals.renderSurface);
    D3DSurface_Release(_RwXbDeviceGlobals.renderSurface);

    D3DDevice_GetDepthStencilSurface(&_RwXbDeviceGlobals.stencilSurface);
    D3DSurface_Release(_RwXbDeviceGlobals.stencilSurface);

    _rwXbRenderStateOpen();
    _rwXbMemoryManagerOpen();
    _rwXbRasterOpen();
    _rwXbIm2DRenderOpen();

    return TRUE;
}

// match: __rwDeviceRegisterPlugin @ 0x002B3970
// sp-match: __rwDeviceRegisterPlugin @ 0x001CED90
RwBool
_rwDeviceRegisterPlugin(void)
{
    return _rwXbRasterPluginAttach();
}

// match: __rwXbEnsureDefaultRenderTarget @ 0x002B3980
// sp-match: __rwXbEnsureDefaultRenderTarget @ 0x001CEDA0
void
_rwXbEnsureDefaultRenderTarget(void)
{
    RwXboxSetRenderTarget(_RwXbDeviceGlobals.renderSurface, _RwXbDeviceGlobals.stencilSurface);
}

static RwRaster *
XbGetTopRaster(RwRaster *ra)
{
    if (ra)
    {
        return ra->parent;
    }
    else
    {
        return NULL;
    }
}

/* Sets the camera's raster and Z raster as the render target and viewport. */
// match: _XbCameraToRenderTarget @ 0x002B39A0
// sp-match: _XbCameraToRenderTarget @ 0x001CEDC0
static RwBool
XbCameraToRenderTarget(const RwCamera *camera)
{
    RwRaster               *zRaster;
    RwXboxRasterExtension  *rasExt;
    D3DVIEWPORT8            viewport;
    D3DSurface             *zStencilSurface = NULL;
    D3DSurface             *surfaceLevel = NULL;
    RwRaster               *raster;
    RwBool                  releaseZStencil = FALSE;
    RwXboxRasterExtension  *zRasterExt;

    zRaster = RwCameraGetZRaster(camera);
    if (zRaster)
    {
        zRasterExt = RASTEREXTFROMRASTER(XbGetTopRaster(zRaster));

        if ((RwRasterGetType(zRaster) & rwRASTERTYPEMASK) == rwRASTERTYPEZBUFFER)
        {
            zStencilSurface = (D3DSurface *)zRasterExt->texture;
        }
        else
        {
            D3DTexture_GetSurfaceLevel((D3DTexture *)zRasterExt->texture,
                                       0, &zStencilSurface);
            releaseZStencil = TRUE;
        }
    }
    else
    {
        zStencilSurface = NULL;
    }

    raster = RwCameraGetRaster(camera);
    rasExt = RASTEREXTFROMRASTER(XbGetTopRaster(raster));

    viewport.X = raster->nOffsetX;
    viewport.Y = raster->nOffsetY;
    viewport.Width = raster->width;
    viewport.Height = raster->height;
    viewport.MinZ = 0.0f;
    viewport.MaxZ = 1.0f;

    if (raster->cType == rwRASTERTYPECAMERATEXTURE)
    {
        if (rasExt->cube)
        {
            D3DCubeTexture_GetCubeMapSurface((D3DCubeTexture *)rasExt->texture,
                                             (D3DCUBEMAP_FACES)rasExt->face, 0, &surfaceLevel);
        }
        else
        {
            D3DTexture_GetSurfaceLevel((D3DTexture *)rasExt->texture, 0, &surfaceLevel);
        }

        RwXboxSetRenderTarget(surfaceLevel, zStencilSurface);
        D3DSurface_Release(surfaceLevel);
    }
    else
    {
        RwXboxSetRenderTarget((D3DSurface *)rasExt->texture, zStencilSurface);
    }

    if (releaseZStencil)
    {
        D3DSurface_Release(zStencilSurface);
    }

    D3DDevice_SetViewport(&viewport);

    return TRUE;
}

// match: __rwXbCameraBeginUpdate @ 0x002B3A90
// sp-match: __rwXbCameraBeginUpdate @ 0x001CEEB0
RwBool
_rwXbCameraBeginUpdate(void *out __RWUNUSED__, void *cameraIn, RwInt32 in __RWUNUSED__)
{
    RwCamera       *camera;
    RWALIGN(D3DMATRIX, rwMATRIXALIGNMENT) viewMatrix;

    /*
     * Save the camera pointer
     */
    camera = (RwCamera *)cameraIn;
    dgGGlobals.curCamera = camera;

    /*
     * View matrix - (camera matrix)
     */
    RwMatrixInvert((RwMatrix *)&viewMatrix, RwFrameGetLTM(RwCameraGetFrame(camera)));

    viewMatrix.m[0][0] = -viewMatrix.m[0][0];
    viewMatrix.m[0][3] = 0.0f;

    viewMatrix.m[1][0] = -viewMatrix.m[1][0];
    viewMatrix.m[1][3] = 0.0f;

    viewMatrix.m[2][0] = -viewMatrix.m[2][0];
    viewMatrix.m[2][3] = 0.0f;

    viewMatrix.m[3][0] = -viewMatrix.m[3][0];
    viewMatrix.m[3][3] = 1.0f;

    D3DDevice_SetTransform(D3DTS_VIEW, &viewMatrix);

    /*
     * Projection matrix
     */
    projMatrix.m[0][0] = camera->recipViewWindow.x;
    projMatrix.m[1][1] = camera->recipViewWindow.y;

    /* Shear X, Y by view offset with Z invariant */
    projMatrix.m[2][0] =
        camera->recipViewWindow.x * camera->viewOffset.x;
    projMatrix.m[2][1] =
        camera->recipViewWindow.y * camera->viewOffset.y;

    /* Translate to shear origin */
    projMatrix.m[3][0] =
        -camera->recipViewWindow.x * camera->viewOffset.x;

    projMatrix.m[3][1] =
        -camera->recipViewWindow.y * camera->viewOffset.y;

    /* Projection type */
    if (camera->projectionType == rwPARALLEL)
    {
        projMatrix.m[2][2] =
            1.0f / (camera->farPlane - camera->nearPlane);
        projMatrix.m[2][3] = 0.0f;
        projMatrix.m[3][3] = 1.0f;
    }
    else
    {
        projMatrix.m[2][2] =
            camera->farPlane / (camera->farPlane - camera->nearPlane);
        projMatrix.m[2][3] = 1.0f;
        projMatrix.m[3][3] = 0.0f;
    }

    projMatrix.m[3][2] = -(camera->nearPlane * projMatrix.m[2][2]);

    D3DDevice_SetTransform(D3DTS_PROJECTION, &projMatrix);

    XbCameraToRenderTarget(camera);

    D3DDevice_BeginScene();

    _rwXbTextureStageInit(0, D3DTSS_TEXTURETRANSFORMFLAGS, 0);
    _rwXbTextureStageInit(0, D3DTSS_TEXCOORDINDEX, 0);

    return TRUE;
}

// match: __rwXbCameraEndUpdate @ 0x002B3C60
// sp-match: __rwXbCameraEndUpdate @ 0x001CF080
RwBool
_rwXbCameraEndUpdate(void *out __RWUNUSED__, void *cameraIn __RWUNUSED__,
                     RwInt32 in __RWUNUSED__)
{
    D3DDevice_EndScene();

    dgGGlobals.curCamera = NULL;

    return TRUE;
}

// match: __rwXbRasterShowRaster @ 0x002B3C70
// sp-match: __rwXbRasterShowRaster @ 0x001CF090
RwBool
_rwXbRasterShowRaster(void *raster __RWUNUSED__, void *inOut __RWUNUSED__, RwInt32 flags)
{
    if (flags & rwRASTERFLIPWAITVSYNC)
    {
        if (present.FullScreen_PresentationInterval == D3DPRESENT_INTERVAL_IMMEDIATE)
        {
            present.FullScreen_PresentationInterval = D3DPRESENT_INTERVAL_ONE;
            _rwXbRenderStateInit(D3DRS_PRESENTATIONINTERVAL, D3DPRESENT_INTERVAL_ONE);
        }
    }
    else
    {
        if (present.FullScreen_PresentationInterval != D3DPRESENT_INTERVAL_IMMEDIATE)
        {
            present.FullScreen_PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
            _rwXbRenderStateInit(D3DRS_PRESENTATIONINTERVAL, D3DPRESENT_INTERVAL_IMMEDIATE);
        }
    }

    IDirect3DDevice8_Present(_RwXbDeviceGlobals.device, NULL, NULL, NULL, NULL);

    return TRUE;
}

// match: _RwXboxGetCurrentD3DDevice @ 0x002B3CC0
// sp-match: _RwXboxGetCurrentD3DDevice @ 0x001CF0E0
D3DDevice *
RwXboxGetCurrentD3DDevice(void)
{
    return _RwXbDeviceGlobals.device;
}

/* Clears a sub-raster of a camera texture by drawing a quad over it. */
// match: _XbClearWithQuads @ 0x002B3CD0
// sp-match: _XbClearWithQuads @ 0x001CF0F0
static void
XbClearWithQuads(RwRaster *raster, D3DCOLOR packedColor, RwInt32 clearFlags)
{
    RwRaster       *curRaster;
    RwBool          zTest;
    RwBool          zWrite;
    RwBool          vertexAlpha;
    RwBool          fogEnable;
    RwCullMode      cullmode;
    DWORD           stencilEnable;
    DWORD           stencilfail;
    DWORD           stencilzfail;
    DWORD           stencilpass;
    DWORD           stencilfunc;
    DWORD           stencilref;
    DWORD           stencilmask;
    DWORD           stencilwritemask;
    DWORD          *pPush;
    RwReal         *quadVerts;

    RwXboxSetCurrentVertexShader(D3DFVF_XYZRHW);
    RwXboxSetCurrentPixelShader(0);

    /* Save the render states the quad changes */
    _rwXbGetRenderState(rwRENDERSTATETEXTURERASTER, &curRaster);
    _rwXbGetRenderState(rwRENDERSTATEZTESTENABLE, &zTest);
    _rwXbGetRenderState(rwRENDERSTATEZWRITEENABLE, &zWrite);
    _rwXbGetRenderState(rwRENDERSTATEVERTEXALPHAENABLE, &vertexAlpha);
    _rwXbGetRenderState(rwRENDERSTATEFOGENABLE, &fogEnable);
    _rwXbGetRenderState(rwRENDERSTATECULLMODE, &cullmode);

    _rwXbRenderStateTextureRaster(NULL);
    _rwXbSetRenderState(rwRENDERSTATEVERTEXALPHAENABLE, (void *)FALSE);
    _rwXbSetRenderState(rwRENDERSTATEFOGENABLE, (void *)FALSE);
    _rwXbSetRenderState(rwRENDERSTATEZTESTENABLE, (void *)FALSE);
    _rwXbSetRenderState(rwRENDERSTATECULLMODE, (void *)rwCULLMODECULLNONE);

    if (clearFlags & rwCAMERACLEARSTENCIL)
    {
        RwXboxGetCachedRenderState(D3DRS_STENCILENABLE, &stencilEnable);
        RwXboxGetCachedRenderState(D3DRS_STENCILFAIL, &stencilfail);
        RwXboxGetCachedRenderState(D3DRS_STENCILZFAIL, &stencilzfail);
        RwXboxGetCachedRenderState(D3DRS_STENCILPASS, &stencilpass);
        RwXboxGetCachedRenderState(D3DRS_STENCILFUNC, &stencilfunc);
        RwXboxGetCachedRenderState(D3DRS_STENCILREF, &stencilref);
        RwXboxGetCachedRenderState(D3DRS_STENCILMASK, &stencilmask);
        RwXboxGetCachedRenderState(D3DRS_STENCILWRITEMASK, &stencilwritemask);

        _rwXbRenderStateForce(D3DRS_STENCILENABLE, TRUE);
        _rwXbRenderStateForce(D3DRS_STENCILFAIL, D3DSTENCILOP_REPLACE);
        _rwXbRenderStateForce(D3DRS_STENCILZFAIL, D3DSTENCILOP_REPLACE);
        _rwXbRenderStateForce(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);
        _rwXbRenderStateForce(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
        _rwXbRenderStateForce(D3DRS_STENCILREF, _RwXbDeviceGlobals.stencilClear);
        _rwXbRenderStateForce(D3DRS_STENCILMASK, 0xffffffff);
        _rwXbRenderStateForce(D3DRS_STENCILWRITEMASK, 0xffffffff);
    }

    if (clearFlags & rwCAMERACLEARZ)
    {
        _rwXbSetRenderState(rwRENDERSTATEZWRITEENABLE, (void *)TRUE);
    }
    else
    {
        _rwXbSetRenderState(rwRENDERSTATEZWRITEENABLE, (void *)FALSE);
    }

    if (!(clearFlags & rwCAMERACLEARIMAGE))
    {
        _rwXbRenderStateForce(D3DRS_COLORWRITEENABLE, 0);
    }

    _rwXbRenderStateForce(D3DRS_TEXTUREFACTOR, packedColor);

    _rwXbTextureStageForce(0, D3DTSS_COLOROP, D3DTOP_SELECTARG2);
    _rwXbTextureStageForce(0, D3DTSS_COLORARG2, D3DTA_TFACTOR);
    _rwXbTextureStageForce(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2);
    _rwXbTextureStageForce(0, D3DTSS_ALPHAARG2, D3DTA_TFACTOR);

    _rwXbFlushCacheBuffer();

    /* The quad */
    pPush = D3DDevice_BeginPush(21);

    *pPush++ = D3DPUSH_ENCODE(D3DPUSH_SET_BEGIN_END, 1);
    *pPush++ = D3DPT_QUADLIST;
    *pPush++ = D3DPUSH_ENCODE(D3DPUSH_NOINCREMENT_FLAG | D3DPUSH_INLINE_ARRAY, 16);

    quadVerts = (RwReal *)pPush;

    quadVerts[0] = (RwReal)raster->nOffsetX;
    quadVerts[1] = (RwReal)raster->nOffsetY;
    quadVerts[2] = 1.0f;
    quadVerts[3] = 1000000.0f;

    quadVerts[4] = (RwReal)raster->nOffsetX;
    quadVerts[5] = (RwReal)(raster->nOffsetY + raster->height);
    quadVerts[6] = 1.0f;
    quadVerts[7] = 1000000.0f;

    quadVerts[8] = (RwReal)(raster->nOffsetX + raster->width);
    quadVerts[9] = (RwReal)(raster->nOffsetY + raster->height);
    quadVerts[10] = 1.0f;
    quadVerts[11] = 1000000.0f;

    quadVerts[12] = (RwReal)(raster->nOffsetX + raster->width);
    quadVerts[13] = (RwReal)raster->nOffsetY;
    quadVerts[14] = 1.0f;
    quadVerts[15] = 1000000.0f;

    pPush += 16;

    *pPush++ = D3DPUSH_ENCODE(D3DPUSH_SET_BEGIN_END, 1);
    *pPush++ = 0;

    D3DDevice_EndPush(pPush);

    /* Restore the render states */
    if (clearFlags & rwCAMERACLEARSTENCIL)
    {
        RwXboxSetCachedRenderState(D3DRS_STENCILENABLE, stencilEnable);
        RwXboxSetCachedRenderState(D3DRS_STENCILFAIL, stencilfail);
        RwXboxSetCachedRenderState(D3DRS_STENCILZFAIL, stencilzfail);
        RwXboxSetCachedRenderState(D3DRS_STENCILPASS, stencilpass);
        RwXboxSetCachedRenderState(D3DRS_STENCILFUNC, stencilfunc);
        RwXboxSetCachedRenderState(D3DRS_STENCILREF, stencilref);
        RwXboxSetCachedRenderState(D3DRS_STENCILMASK, stencilmask);
        RwXboxSetCachedRenderState(D3DRS_STENCILWRITEMASK, stencilwritemask);
    }

    if (!(clearFlags & rwCAMERACLEARIMAGE))
    {
        RwXboxSetCachedRenderState(D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_ALL);
    }

    _rwXbSetRenderState(rwRENDERSTATEZTESTENABLE, (void *)zTest);
    _rwXbSetRenderState(rwRENDERSTATEZWRITEENABLE, (void *)zWrite);
    _rwXbSetRenderState(rwRENDERSTATEVERTEXALPHAENABLE, (void *)vertexAlpha);
    _rwXbSetRenderState(rwRENDERSTATEFOGENABLE, (void *)fogEnable);
    _rwXbSetRenderState(rwRENDERSTATECULLMODE, (void *)cullmode);
    _rwXbRenderStateTextureRaster(curRaster);
}

// match: __rwXbCameraClear @ 0x002B4280
// sp-match: __rwXbCameraClear @ 0x001CF6A0
RwBool
_rwXbCameraClear(void *camera, void *color, RwInt32 clearFlags)
{
    D3DCOLOR        packedColor = 0;
    RwRaster       *raster;
    static const DWORD  clearFlagsConvTable[8] = {
        0,                      /* Nothing */
        D3DCLEAR_TARGET,        /* Clear Frame buffer only */
        D3DCLEAR_ZBUFFER,       /* Clear Z buffer only */
        D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, /* Clear Frame & Z buffer */
        D3DCLEAR_STENCIL,       /* Clear Stencil buffer */
        D3DCLEAR_TARGET | D3DCLEAR_STENCIL, /* Clear Frame & Stencil buffer */
        D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, /* Clear Z Buffer & Stencil */
        D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, /* Clear Frame, Z & stencil */
    };

    if (!XbCameraToRenderTarget((RwCamera *)camera))
    {
        return FALSE;
    }

    /* The clear color */
    if (rwCAMERACLEARIMAGE & clearFlags)
    {
        RwRGBA             *col = (RwRGBA *) color;

        /* Pack the clear color */
        packedColor = (D3DCOLOR) (((col->alpha) << 24) |
                                  ((col->red) << 16) |
                                  ((col->green) << 8) | (col->blue));
    }

    raster = RwCameraGetRaster((RwCamera *)camera);

    if (raster->cType != rwRASTERTYPECAMERATEXTURE || raster == RwRasterGetParent(raster))
    {
        /* A 32 bit Z buffer has a stencil buffer too */
        if ((clearFlags & rwCAMERACLEARZ) && _RwXbDeviceGlobals.zBufferDepth == 32)
        {
            clearFlags |= rwCAMERACLEARSTENCIL;
        }

        D3DDevice_Clear(0, NULL, clearFlagsConvTable[clearFlags], packedColor, 1.0f,
                        _RwXbDeviceGlobals.stencilClear);
    }
    else
    {
        XbClearWithQuads(raster, packedColor, clearFlags);
    }

    return TRUE;
}

static RwBool
XbNullStandard(void *pOut __RWUNUSED__,
               void *pInOut __RWUNUSED__, RwInt32 nIn __RWUNUSED__)
{
    return FALSE;
}

// match: _XbDeviceSystemStandards @ 0x002B4320
// sp-match: _XbDeviceSystemStandards @ 0x001CF740
static RwBool
XbDeviceSystemStandards(void *out, void *inOut __RWUNUSED__,
                        RwInt32 numStandardsFunctions)
{
    RwInt32             i;
    RwInt32             numDriverFunctions;
    RwStandardFunc     *standardFunctions;
    RwStandard          rwXbStandards[] = {
        /* Camera ops */
        {rwSTANDARDCAMERABEGINUPDATE, _rwXbCameraBeginUpdate},
        {rwSTANDARDCAMERAENDUPDATE, _rwXbCameraEndUpdate},
        {rwSTANDARDCAMERACLEAR, _rwXbCameraClear},

        /* Raster/Pixel operations */
        {rwSTANDARDRASTERSHOWRASTER, _rwXbRasterShowRaster},
        {rwSTANDARDRGBTOPIXEL, _rwXbRGBToPixel},
        {rwSTANDARDPIXELTORGB, _rwXbPixelToRGB},
        {rwSTANDARDRASTERSETIMAGE, _rwXbRasterSetFromImage},
        {rwSTANDARDIMAGEGETRASTER, _rwXbImageGetFromRaster},

        /* Raster creation and destruction */
        {rwSTANDARDRASTERDESTROY, _rwXbRasterDestroy},
        {rwSTANDARDRASTERCREATE, _rwXbRasterCreate},

        /* Finding about a raster type */
        {rwSTANDARDIMAGEFINDRASTERFORMAT, _rwXbImageFindRasterFormat},

        /* Texture operations */
        {rwSTANDARDTEXTURESETRASTER, _rwXbTextureSetRaster},

        /* Locking and releasing */
        {rwSTANDARDRASTERLOCK, _rwXbRasterLock},
        {rwSTANDARDRASTERUNLOCK, _rwXbRasterUnlock},
        {rwSTANDARDRASTERLOCKPALETTE, _rwXbRasterLockPalette},
        {rwSTANDARDRASTERUNLOCKPALETTE, _rwXbRasterUnlockPalette},

        /* Raster operations */
        {rwSTANDARDRASTERCLEAR, _rwXbRasterClear},
        {rwSTANDARDRASTERCLEARRECT, _rwXbRasterClearRect},

        /* !! */
        {rwSTANDARDRASTERRENDER, _rwXbRasterRender},
        {rwSTANDARDRASTERRENDERSCALED, _rwXbRasterRenderScaled},
        {rwSTANDARDRASTERRENDERFAST, _rwXbRasterRenderFast},

        /* Setting the context */
        {rwSTANDARDSETRASTERCONTEXT, _rwXbSetRasterContext},

        /* Creating sub rasters */
        {rwSTANDARDRASTERSUBRASTER, _rwXbRasterSubRaster},

        /* Native texture serialization */
        {rwSTANDARDNATIVETEXTUREGETSIZE, _rwXbNativeTextureGetSize},
        {rwSTANDARDNATIVETEXTUREWRITE, _rwXbNativeTextureWrite},
        {rwSTANDARDNATIVETEXTUREREAD, _rwXbNativeTextureRead},

        /* Raster Mip Levels */
        {rwSTANDARDRASTERGETMIPLEVELS, _rwXbRasterGetMipLevels}
    };

    standardFunctions = (RwStandardFunc *) out;
    numDriverFunctions = sizeof(rwXbStandards) / sizeof(RwStandard);

    /* Clear out all of the standards initially */
    for (i = 0; i < numStandardsFunctions; i++)
    {
        standardFunctions[i] = XbNullStandard;
    }

    /* Fill in all of the standards */
    while (numDriverFunctions--)
    {
        if ((rwXbStandards->nStandard < numStandardsFunctions) &&
            (rwXbStandards->nStandard >= 0))
        {
            standardFunctions[rwXbStandards[numDriverFunctions].nStandard] =
                rwXbStandards[numDriverFunctions].fpStandard;
        }
    }

    return TRUE;
}

static RwBool
XbDeviceSystemClose(void)
{
    if (_RwXbDeviceGlobals.object)
    {
        Direct3D_Release();
    }

    return TRUE;
}

static RwBool
XbDeviceSystemStop(void)
{
    _rwXbIm2DRenderClose();
    _rwXbRasterClose();
    _rwXbMemoryManagerClose();

    D3DDevice_Release();
    _RwXbDeviceGlobals.device = NULL;

    return TRUE;
}

// match: _XbSystem @ 0x002B4550
// sp-match: _XbSystem @ 0x001CF970
static RwBool
XbSystem(RwInt32 request, void *out, void *inOut, RwInt32 in)
{
    RwBool          result;

    switch (request)
    {
        case rwDEVICESYSTEMUSEMODE:
            if (in >= 0 && in < _RwXbDeviceGlobals.modeCount)
            {
                D3DDISPLAYMODE  mode;

                Direct3D_EnumAdapterModes(0, in, &mode);

                _RwXbDeviceGlobals.config.backBufferWidth = mode.Width;
                _RwXbDeviceGlobals.config.backBufferHeight = mode.Height;
                _RwXbDeviceGlobals.config.backBufferFormat = mode.Format;
                _RwXbDeviceGlobals.config.flags = mode.Flags;
                _RwXbDeviceGlobals.config.refreshRateInHz = mode.RefreshRate;
                _RwXbDeviceGlobals.displayDepth = XbFindDepth(mode.Format);
                _RwXbDeviceGlobals.currentModeIndex = in;

                result = TRUE;
            }
            else
            {
                result = FALSE;
            }
            break;

        case rwDEVICESYSTEMGETNUMMODES:
            *((RwInt32 *)out) = _RwXbDeviceGlobals.modeCount;
            result = TRUE;
            break;

        case rwDEVICESYSTEMGETMODEINFO:
            if (in >= 0 && in < _RwXbDeviceGlobals.modeCount)
            {
                RwVideoMode    *videoMode = (RwVideoMode *)out;
                D3DDISPLAYMODE  mode;

                Direct3D_EnumAdapterModes(0, in, &mode);

                videoMode->width = mode.Width;
                videoMode->height = mode.Height;
                videoMode->depth = XbFindDepth(mode.Format);
                videoMode->flags = rwVIDEOMODEEXCLUSIVE;
                videoMode->refRate = mode.RefreshRate;
                videoMode->format = XbFindRWFormat(mode.Format);

                if (mode.Flags & D3DPRESENTFLAG_INTERLACED)
                {
                    videoMode->flags |= rwVIDEOMODEINTERLACE;
                }

                if (mode.Flags & D3DPRESENTFLAG_PROGRESSIVE)
                {
                    videoMode->flags |= rwVIDEOMODE_XBOX_PROGRESSIVE;
                }

                if (mode.Flags & D3DPRESENTFLAG_WIDESCREEN)
                {
                    videoMode->flags |= rwVIDEOMODE_XBOX_WIDESCREEN;
                }

                if (mode.Flags & D3DPRESENTFLAG_FIELD)
                {
                    videoMode->flags |= rwVIDEOMODE_XBOX_FIELD;
                }

                if (mode.Flags & D3DPRESENTFLAG_10X11PIXELASPECTRATIO)
                {
                    videoMode->flags |= rwVIDEOMODE_XBOX_10X11PIXELASPECT;
                }

                result = TRUE;
            }
            else
            {
                result = FALSE;
            }
            break;

        case rwDEVICESYSTEMGETMODE:
            *((RwInt32 *)out) = _RwXbDeviceGlobals.currentModeIndex;
            result = TRUE;
            break;

        case rwDEVICESYSTEMREGISTER:
            {
                RwDevice   *deviceOut = (RwDevice *)out;

                *deviceOut = *_rwDeviceGetHandle();
                dgGGlobals.memFuncs = (RwMemoryFunctions *)inOut;

                result = TRUE;
            }
            break;

        case rwDEVICESYSTEMOPEN:
            result = XbDeviceSystemOpen(inOut);
            break;

        case rwDEVICESYSTEMGETNUMSUBSYSTEMS:
            *((RwInt32 *)out) = 1;
            result = TRUE;
            break;

        case rwDEVICESYSTEMGETSUBSYSTEMINFO:
            if (in == 0)
            {
                rwstrcpy(((RwSubSystemInfo *)out)->name, _RwXbDeviceGlobals.name);
                result = TRUE;
            }
            else
            {
                RWERROR((E_RW_DEVICEERROR, RWSTRING("Invalid subsystem number")));
                result = FALSE;
            }
            break;

        case rwDEVICESYSTEMGETCURRENTSUBSYSTEM:
            *((RwInt32 *)out) = 0;
            result = TRUE;
            break;

        case rwDEVICESYSTEMSETSUBSYSTEM:
            result = (in == 0);
            break;

        case rwDEVICESYSTEMSTART:
            result = XbDeviceSystemStart();
            break;

        case rwDEVICESYSTEMSTOP:
            result = XbDeviceSystemStop();
            break;

        case rwDEVICESYSTEMSTANDARDS:
            result = XbDeviceSystemStandards(out, inOut, in);
            break;

        case rwDEVICESYSTEMINITIATESTOP:
            D3DDevice_SetVertexShader(0);
            D3DDevice_SetPixelShader(0);
            result = FALSE;
            break;

        case rwDEVICESYSTEMGETMAXTEXTURESIZE:
            *((RwInt32 *)out) = 4096;
            result = TRUE;
            break;

        case rwDEVICESYSTEMGETID:
            *((RwUInt16 *)out) = rwDEVICE_XBOX;
            /* (the image's jump table sends CLOSE and FOCUS to this case's TRUE tail:
               XbDeviceSystemClose is TRUE alone, Direct3D_Release being the XDK's empty
               inline) */
        case rwDEVICESYSTEMCLOSE:
        case rwDEVICESYSTEMFOCUS:
            result = TRUE;
            break;

        default:
            result = FALSE;
            break;
    }

    return result;
}

// match: __rwDeviceGetHandle @ 0x002B4850
// sp-match: __rwDeviceGetHandle @ 0x001CFC70
RwDevice *
_rwDeviceGetHandle(void)
{
    static RwDevice rwXbDriverDevice = {
        1.0f,                   /* default gamma correction */
        XbSystem,
        0.0f, 1.0f,             /* near and far Z buffer limits */

        _rwXbSetRenderState,    /* RwRenderStateSetFunction */
        _rwXbGetRenderState,    /* RwRenderStateGetFunction */

        _rwXbIm2DRenderLine,    /* RwIm2DRenderLineFunction */
        _rwXbIm2DRenderTriangle, /* RwIm2DRenderTriangleFunction */
        _rwXbIm2DRenderPrimitive, /* RwIm2DRenderPrimitiveFunction */
        _rwXbIm2DRenderIndexedPrimitive, /* RwIm2DRenderIndexedPrimitiveFunction */

        NULL, NULL, NULL, NULL  /* These get set up when the 3D Immediate mode module is setup */
    };

    return &rwXbDriverDevice;
}
