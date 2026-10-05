/*
 * Win32 port bridge (docs/WIN32_PORT.md): stands in for the XDK's xtl.h, the Xbox's master header
 * (Win32 subset, XAPI, Xbox Direct3D 8, Xbox DirectSound). The port's include path puts
 * port/include first and leaves the XDK out, so every Xbox header the sources include resolves
 * here. The platform layer (port/xpal_*) and the bridges implement what these headers declare.
 */
#ifndef PORT_XTL_H
#define PORT_XTL_H

/* The Windows SDK's windows.h, named by a path relative to the SDK's include directories:
   RenderWare's include/rw/sdk/windows.h (first on the RW units' include path) turns <windows.h>
   back into <xtl.h>, as the matching build needs. _WINSOCKAPI_ keeps Winsock 1 out, so that
   Winsock 2 (the Xbox's xtl.h provides the sockets API itself) can follow. */
#ifndef _WINSOCKAPI_
#define _WINSOCKAPI_
#endif
#include <../um/windows.h>
#undef _WINSOCKAPI_
#include <winsock2.h>
#include <ws2tcpip.h>
#include <xnet.h>
#include <xbox.h>

/* The path-taking Win32 calls the sources make, through the platform layer's mapping of the
   Xbox drives (d:\ the disc's data, t:\ u:\ z:\ the user directories; port/src/xpal_core.cpp).
   CreateFile and GetFileAttributes reach these through windows.h's A forms. */
#ifdef __cplusplus
extern "C" {
#endif
HANDLE WINAPI xpal_CreateFileA(LPCSTR name, DWORD access, DWORD share, LPSECURITY_ATTRIBUTES sa,
                               DWORD disposition, DWORD flags, HANDLE templ);
DWORD WINAPI xpal_GetFileAttributesA(LPCSTR name);
BOOL WINAPI xpal_CopyFileA(LPCSTR from, LPCSTR to, BOOL failIfExists);
#ifdef __cplusplus
}
#endif
#define CreateFileA xpal_CreateFileA
#define GetFileAttributesA xpal_GetFileAttributesA
#define CopyFileA xpal_CopyFileA

#include <d3d8.h>
#include <dsound.h>

#endif
