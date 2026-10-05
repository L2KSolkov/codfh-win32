/*
 * The Direct3D 11 back end's internals, shared by its files (pd11.cpp: device and frames;
 * pd11_draw.cpp: shaders, textures, state and draws).
 */
#ifndef PORT_PD11_H
#define PORT_PD11_H

#include <d3d11.h>

extern ID3D11Device *pd11_dev;
extern ID3D11DeviceContext *pd11_ctx;

#endif
