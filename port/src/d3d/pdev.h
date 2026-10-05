/*
 * The D3D bridge's device back end (docs/WIN32_PORT.md W2): what d3d8_bridge.cpp (the Xbox names)
 * asks of the PC's Direct3D, in plain C types. Only pd11.cpp includes d3d11.h; the Xbox and the PC
 * APIs share names with different values, so the two sides never meet in one file.
 *
 * The back end is Direct3D 11 (owner's decision, 2026-10-05: Direct3D 9 has no adapter over
 * Remote Desktop; Direct3D 11 runs on the GPU there, or on WARP).
 */
#ifndef PORT_PDEV_H
#define PORT_PDEV_H

#ifdef __cplusplus
extern "C" {
#endif

/* The device: the 640x480 frame the game draws, presented stretched to the window. Returns 0
   only when nothing can be created at all (the bridge then runs headless). */
int pdev_init(void *hwnd, int width, int height, int windowed, int vsync);
void pdev_shutdown(void);
int pdev_ready(void);

enum
{
    PDEV_CLEAR_TARGET = 1,
    PDEV_CLEAR_DEPTH = 2,
    PDEV_CLEAR_STENCIL = 4
};

/* Clears the current target (color is A8R8G8B8). */
void pdev_clear(unsigned flags, unsigned color, float z, unsigned stencil);
void pdev_begin_scene(void);
void pdev_end_scene(void);
void pdev_present(void);
void pdev_set_viewport(unsigned x, unsigned y, unsigned w, unsigned h, float minz, float maxz);
void pdev_set_gamma(const unsigned char *red, const unsigned char *green, const unsigned char *blue);

#ifdef __cplusplus
}
#endif

#endif
