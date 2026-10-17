/*
 * The port layer's internal interface (docs/WIN32_PORT.md section 5): the log, the configuration
 * and the Xbox drive mapping that the platform layer (xpal_*) and the bridges share. Plain C
 * types only, so that both the Xbox-named side (sources including port/include) and the Direct3D 11
 * and XAudio2 side can include it.
 */
#ifndef PORT_PORT_H
#define PORT_PORT_H

#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

/* The log: build/port's codfh.log beside the executable, and the debugger. */
void plog(const char *fmt, ...);
/* Logs a call the port does not implement yet, once per name. */
void plog_stub(const char *name);
#define PORT_STUB() plog_stub(__FUNCTION__)
/* The log also goes to the process's console (the server's, or the game's [debug] console). */
void plog_to_console(void);
/* The game's debug prints: formatted safely (a bad argument prints a note), then logged. */
void port_debug_print(const char *fmt, ...);
void port_debug_vprint(const char *fmt, va_list ap);

/* The configuration (codfh.ini beside the executable; defaults otherwise). */
typedef struct PortConfig
{
    char dataRoot[260];     /* what the Xbox's d:\ is: the disc's files (COD.PAK...) */
    char userRoot[260];     /* where the title cache, saves and launch data go */
    int width, height;      /* the window's client size (the game renders 640x480 into it) */
    int windowed;
    int vsync;
    int widescreen;
    int fill;               /* [video] fill: the 4:3 frame stretched to the window's shape, no black
                               bars (widescreen fills too, and tells the game it is 16:9) */
    float mouseSensitivity;
    char adapter[64];       /* [video] adapter: a part of the GPU's name ("" the high-performance one) */
    float renderScale;      /* [video] render_scale: the frame drawn at 640x480 times this (0: as
                               large as the window holds, from 1 to 4) */
    int maxFps;             /* [video] max_fps: the frame rate the frames are paced to (60, as the
                               Xbox's display; 0 uncapped) */
    int console;            /* [debug] console: the log in a console window of its own (1; 0 none;
                               CODFH_CONSOLE overrides) */
    int language;           /* the game's language index (0 English; port_language) */
    char playerName[16];    /* the name a player with no profile plays under ([game] name; the
                               Windows user name by default) */
} PortConfig;

extern PortConfig port_config;
void port_config_load(void);
/* [video] fill set now and kept in codfh.ini (the overlay's Renderer switch). */
void port_config_set_fill(int on);

/* The game's window (created by WinMain, used by the device). */
extern void *port_hwnd;
/* Pumps window messages; returns 0 once the window was closed. */
int port_pump_messages(void);
/* Frames presented so far (scripted input and captures key on it). */
extern volatile unsigned port_frame;

/* Set when the window was closed (the game loop checks it to exit). */
extern volatile int port_quit;

/* Maps an Xbox path (d:\..., t:\..., u:\..., z:\...) to a Win32 one; other paths are returned
   unchanged. out must hold 520 characters. */
const char *port_map_path(const char *xboxPath, char *out);

#ifdef __cplusplus
}
#endif

#endif
