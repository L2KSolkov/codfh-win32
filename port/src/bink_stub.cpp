/*
 * Bink for the port (docs/WIN32_PORT.md W6): no decoder yet. BinkOpen reports that the movie
 * could not be opened, which the game's movie player (unit_19CB20) handles by skipping it; the
 * other calls are never reached without a movie.
 */
#include <windows.h>

#include "port.h"

extern "C" void *__stdcall BinkOpen(const char *name, unsigned int flags)
{
    plog("movie %s skipped (W6: Bink)", name ? name : "?");
    (void)flags;
    return NULL;
}

extern "C" char *__stdcall BinkGetError(void)
{
    static char err[] = "Bink is not available in this build";
    return err;
}

extern "C" void __stdcall BinkClose(void *) {}
extern "C" int __stdcall BinkDoFrame(void *) { return 0; }
extern "C" void __stdcall BinkNextFrame(void *) {}
extern "C" int __stdcall BinkWait(void *) { return 0; }
extern "C" int __stdcall BinkPause(void *, int) { return 0; }
extern "C" void __stdcall BinkSetSoundTrack(unsigned int, unsigned int *) {}
extern "C" void __stdcall BinkSetVolume(void *, unsigned int, int) {}
extern "C" unsigned int __stdcall BinkGetTrackID(void *, unsigned int) { return 0; }
extern "C" int __stdcall BinkCopyToBuffer(void *, void *, int, unsigned int, unsigned int, unsigned int, unsigned int)
{
    return 0;
}
