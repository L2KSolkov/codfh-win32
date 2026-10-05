/*
 * The Direct3D 9 side of the D3D bridge (docs/WIN32_PORT.md W2): what d3d8_bridge.cpp (the Xbox
 * names) asks of Direct3D 9, in plain C types. Only pd9*.cpp include d3d9.h; the Xbox and
 * Direct3D 9 share names with different values, so the two sides never meet in one file.
 */
#ifndef PORT_PD9_H
#define PORT_PD9_H

#ifdef __cplusplus
extern "C" {
#endif

/* The device: the 640x480 back buffer the game draws, presented scaled to the window. */
int pd9_init(void *hwnd, int width, int height, int windowed, int vsync);
void pd9_shutdown(void);
int pd9_ready(void);

/* Clears the current target: flags are Direct3D 9's D3DCLEAR_* bits. */
void pd9_clear(unsigned flags, unsigned color, float z, unsigned stencil);
void pd9_begin_scene(void);
void pd9_end_scene(void);
void pd9_present(void);
void pd9_set_viewport(unsigned x, unsigned y, unsigned w, unsigned h, float minz, float maxz);
void pd9_set_gamma(const unsigned char *red, const unsigned char *green, const unsigned char *blue);

#ifdef __cplusplus
}
#endif

#endif
