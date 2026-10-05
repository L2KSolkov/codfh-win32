/*
 * Win32 port bridge (docs/WIN32_PORT.md W2): stands in for the XDK's d3d8.h (Xbox Direct3D 8).
 * The bridge keeps the Xbox API's names (D3DDevice_*, D3DTexture_*, D3D__RenderState...) and
 * implements them over Direct3D 9 (port/d3d9bridge). A stub so far: Direct3D 9's types, the
 * Xbox declarations added as the port build's errors name them (build/port/errors.md).
 */
#ifndef PORT_D3D8_H
#define PORT_D3D8_H

#include <xtl.h>
#include <d3d9.h>

#endif
