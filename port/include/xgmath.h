/*
 * Win32 port bridge (docs/WIN32_PORT.md W2): stands in for the XDK's xgmath.h. The game's particle
 * and clone renderers (unit_19E500, unit_122FB0) build their shader constants with XGMatrixMultiply
 * and XGMatrixTranspose; port/xgmath implements the two.
 */
#ifndef PORT_XGMATH_H
#define PORT_XGMATH_H

#include <d3d8.h>

#ifdef __cplusplus
struct XGMATRIX : public D3DMATRIX
{
};
extern "C" {
#else
typedef D3DMATRIX XGMATRIX;
#endif

XGMATRIX *WINAPI XGMatrixMultiply(XGMATRIX *pOut, const XGMATRIX *pM1, const XGMATRIX *pM2);
XGMATRIX *WINAPI XGMatrixTranspose(XGMATRIX *pOut, const XGMATRIX *pM);

#ifdef __cplusplus
}
#endif

#endif
