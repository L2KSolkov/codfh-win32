/*
 * codfh-match: RenderWare 3.6's Xbox driver device globals (driver/xbox),
 * written from the image; the layouts are the Godfather PDB's.
 */
#ifndef XBDEVICE_H
#define XBDEVICE_H

/* The device configuration (the Godfather PDB's layout and names). */
typedef struct RwXboxDeviceConfig RwXboxDeviceConfig;
struct RwXboxDeviceConfig
{
    RwUInt32                backBufferWidth;
    RwUInt32                backBufferHeight;
    RwUInt32                backBufferFormat;
    RwUInt32                backBufferCount;
    RwUInt32                multiSampleType;
    RwUInt32                swapEffect;
    RwUInt32                depthStencilFormat;
    RwUInt32                flags;
    RwUInt32                refreshRateInHz;
    RwUInt32                presentationInterval;
};

/* _RwXbDeviceGlobals (0x51F200). */
typedef struct _rxXboxDriverGlobals _rxXboxDriverGlobals;
struct _rxXboxDriverGlobals
{
    Direct3D               *object;
    D3DDevice              *device;
    D3DSurface             *renderSurface;
    D3DSurface             *stencilSurface;
    RwXboxDeviceConfig      config;
    RwInt32                 modeCount;
    RwInt32                 displayDepth;
    RwUInt32                stencilClear;
    RwInt32                 currentModeIndex;
    RwInt32                 zBufferDepth;
    RwChar                  name[80];
};

extern _rxXboxDriverGlobals _RwXbDeviceGlobals;

extern void _rwXbEnsureDefaultRenderTarget(void);

#endif /* XBDEVICE_H */
