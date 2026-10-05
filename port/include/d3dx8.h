/*
 * Win32 port bridge (docs/WIN32_PORT.md W2): stands in for the XDK's d3dx8.h. The game's particle
 * and clone renderers (unit_19E500, unit_122FB0) build their view and projection matrices with
 * D3DXMatrixLookAtRH and D3DXMatrixPerspectiveFovRH; port/xgmath implements them.
 */
#ifndef PORT_D3DX8_H
#define PORT_D3DX8_H

#include <d3d8.h>

#undef D3DXMatrixMultiply   /* xgmath.h's alias, when it came first */

#ifdef __cplusplus
struct D3DXMATRIX : public D3DMATRIX
{
};
struct D3DXVECTOR3 : public D3DVECTOR
{
};
extern "C" {
#else
typedef D3DMATRIX D3DXMATRIX;
typedef D3DVECTOR D3DXVECTOR3;
#endif

D3DXMATRIX *WINAPI D3DXMatrixMultiply(D3DXMATRIX *pOut, const D3DXMATRIX *pM1,
                                      const D3DXMATRIX *pM2);
D3DXMATRIX *WINAPI D3DXMatrixLookAtRH(D3DXMATRIX *pOut, const D3DXVECTOR3 *pEye,
                                      const D3DXVECTOR3 *pAt, const D3DXVECTOR3 *pUp);
D3DXMATRIX *WINAPI D3DXMatrixPerspectiveFovRH(D3DXMATRIX *pOut, float fovy, float Aspect, float zn,
                                              float zf);

#ifdef __cplusplus
}
#endif

#endif
