/*
 * Win32 port bridge (docs/WIN32_PORT.md W5): stands in for the XDK's dsound.h (Xbox DirectSound:
 * mix bins, I3DL2, HRTF, the DSP effects image). It also hides the Windows SDK's own dsound.h,
 * whose API differs. The bridge implements these names over XAudio2 (port/audiobridge). A stub so
 * far: declarations added as the port build's errors name them (build/port/errors.md).
 */
#ifndef PORT_DSOUND_H
#define PORT_DSOUND_H

#include <xtl.h>

#endif
