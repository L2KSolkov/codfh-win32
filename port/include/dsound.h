/*
 * Win32 port bridge (docs/WIN32_PORT.md W5): stands in for the XDK's dsound.h (Xbox DirectSound:
 * mix bins, I3DL2, HRTF, the DSP effects image). It also hides the Windows SDK's own dsound.h,
 * whose API differs. RenderWare Audio's Xbox layer (src/rwa) declares the DirectSound structures
 * and calls it uses itself; this header has what the game's own units use (the voice owner,
 * game/voice.h). The bridge implements these names over XAudio2 (port/audiobridge).
 */
#ifndef PORT_DSOUND_H
#define PORT_DSOUND_H

#include <xtl.h>

/* The DSP effects image the game downloads (voice processing reads its descriptor). */
typedef struct _DSEFFECTIMAGEDESC DSEFFECTIMAGEDESC, *LPDSEFFECTIMAGEDESC;

#define DSFX_IMMEDIATE 0x00000000

typedef struct IDirectSound IDirectSound;
typedef IDirectSound *LPDIRECTSOUND;
typedef IDirectSound *LPDIRECTSOUND8;

#ifdef __cplusplus
extern "C" {
#endif

HRESULT __stdcall IDirectSound_SetEffectData(LPDIRECTSOUND pDirectSound, DWORD dwEffectIndex,
                                             DWORD dwOffset, LPCVOID pvData, DWORD dwDataSize,
                                             DWORD dwApply);

#ifdef __cplusplus
}

struct IDirectSound
{
    HRESULT SetEffectData(DWORD dwEffectIndex, DWORD dwOffset, LPCVOID pvData, DWORD dwDataSize,
                          DWORD dwApply)
    {
        return IDirectSound_SetEffectData(this, dwEffectIndex, dwOffset, pvData, dwDataSize, dwApply);
    }
};
#endif

#endif
