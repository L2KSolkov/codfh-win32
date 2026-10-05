/*
 * The audio bridge (docs/WIN32_PORT.md W5): the Xbox DirectSound calls RenderWare Audio's Xbox
 * layer (src/rwa/xbox) and the game make, with the signatures they declare them with.
 *
 * State so far (W0): a silent DirectSound. Buffers keep their data, format, regions and state,
 * and a playing buffer's position advances in real time at its format's byte rate, so RenderWare
 * Audio's streaming refills, loops and ends sounds as it does with output. W5 sends the buffers
 * to XAudio2 (PCM and Xbox ADPCM decoded, mix bins as submix voices, the DSP image's effects
 * rebuilt).
 */
#include <windows.h>
#include <stdlib.h>
#include <string.h>

#include "../port.h"

typedef int RwInt32;
typedef unsigned int RwUInt32;
typedef float RwReal;

enum
{
    DSBPLAY_LOOPING = 1,
    DSBPLAY_FROMSTART = 2,
    DSBSTATUS_PLAYING = 1,
    DSBSTATUS_LOOPING = 4,
};

#pragma pack(push, 1)
struct WaveFormat
{
    WORD formatTag, channels;
    DWORD samplesPerSec, avgBytesPerSec;
    WORD blockAlign, bitsPerSample, size;
};
#pragma pack(pop)

struct BufferDesc
{
    DWORD size, flags, bufferBytes;
    const void *format;
    void *mixBins;
    DWORD inputMixBin;
};

struct SilentBuffer
{
    LONG refs;
    BYTE *data;
    DWORD size;
    DWORD frequency;        /* 0: the format's */
    WaveFormat format;
    DWORD playOffset, playLength, loopOffset, loopLength;
    int playing, looping;
    DWORD startTick;        /* when it started at startPos */
    DWORD startPos;
};

struct SilentDSound
{
    LONG refs;
};

static SilentDSound the_dsound = {1};

static DWORD byte_rate(const SilentBuffer *b)
{
    DWORD rate = b->format.avgBytesPerSec;
    if (b->frequency && b->format.samplesPerSec)
        rate = (DWORD)((unsigned long long)rate * b->frequency / b->format.samplesPerSec);
    return rate ? rate : 44100 * 4;
}

/* The position now; a non-looping buffer that reached its end stops. */
static DWORD position(SilentBuffer *b)
{
    if (!b->playing)
        return b->startPos;
    DWORD elapsed = GetTickCount() - b->startTick;
    unsigned long long pos = b->startPos + (unsigned long long)elapsed * byte_rate(b) / 1000;
    DWORD end = b->playLength ? b->playOffset + b->playLength : b->size;
    if (pos >= end)
    {
        if (b->looping && end)
        {
            DWORD lo = b->loopLength ? b->loopOffset : 0;
            DWORD len = b->loopLength ? b->loopLength : end;
            pos = lo + (pos - lo) % (len ? len : 1);
        }
        else
        {
            b->playing = 0;
            b->startPos = 0;
            return 0;
        }
    }
    return (DWORD)pos;
}

/*
 * The DirectSound object
 */

extern "C" RwInt32 __stdcall DirectSoundCreate(void *, void **dsound, void *)
{
    *dsound = &the_dsound;
    plog("audio: silent output (W5: XAudio2)");
    return S_OK;
}

extern "C" RwInt32 __stdcall DirectSoundUseFullHRTF(void) { return S_OK; }
extern "C" void __stdcall DirectSoundDoWork(void) {}
extern "C" RwUInt32 __stdcall IDirectSound_Release(void *) { return 0; }
extern "C" RwInt32 __stdcall IDirectSound_SetI3DL2Listener(void *, const void *, RwUInt32) { return S_OK; }

extern "C" RwInt32 __stdcall IDirectSound_GetOutputLevels(void *, void *levels, RwInt32)
{
    /* (DSOUTPUTLEVELS: two peaks, six channel levels) */
    memset(levels, 0, 8 * 4);
    return S_OK;
}

extern "C" RwInt32 __stdcall IDirectSound_SetEffectData(void *, RwUInt32, RwUInt32, const void *, RwUInt32, RwUInt32)
{
    return S_OK;
}

extern "C" RwInt32 __stdcall IDirectSound_GetEffectData(void *, RwUInt32, RwUInt32, void *data, RwUInt32 size)
{
    memset(data, 0, size);
    return S_OK;
}

extern "C" RwInt32 __stdcall IDirectSound_CommitEffectData(void *) { return S_OK; }

extern "C" RwInt32 __stdcall IDirectSound_GetSpeakerConfig(void *, RwUInt32 *config)
{
    *config = 0;    /* stereo */
    return S_OK;
}

/* The DSP image: its descriptor lists no effects (the effects are W5's to rebuild). */
static DWORD empty_image_desc[4];

extern "C" RwInt32 __stdcall IDirectSound_DownloadEffectsImage(void *, void *, RwUInt32, void *, void **desc)
{
    if (desc)
        *desc = empty_image_desc;
    return S_OK;
}

extern "C" RwInt32 __stdcall IDirectSound_SetDopplerFactor(void *, RwReal, RwUInt32) { return S_OK; }
extern "C" RwInt32 __stdcall IDirectSound_SetDistanceFactor(void *, RwReal, RwUInt32) { return S_OK; }
extern "C" RwInt32 __stdcall IDirectSound_SetRolloffFactor(void *, RwReal, RwUInt32) { return S_OK; }
extern "C" RwInt32 __stdcall IDirectSound_SetVelocity(void *, RwReal, RwReal, RwReal, RwUInt32) { return S_OK; }
extern "C" RwInt32 __stdcall IDirectSound_SetPosition(void *, RwReal, RwReal, RwReal, RwUInt32) { return S_OK; }
extern "C" RwInt32 __stdcall IDirectSound_SetOrientation(void *, RwReal, RwReal, RwReal, RwReal, RwReal, RwReal,
                                                         RwUInt32)
{
    return S_OK;
}
extern "C" RwInt32 __stdcall IDirectSound_CommitDeferredSettings(void *) { return S_OK; }
extern "C" RwInt32 __stdcall IDirectSound_EnableHeadphones(void *, RwInt32) { return S_OK; }
extern "C" RwInt32 __stdcall IDirectSound_SetMixBinHeadroom(void *, RwUInt32, RwUInt32) { return S_OK; }

/*
 * Buffers
 */

extern "C" RwInt32 __stdcall IDirectSound_CreateSoundBuffer(void *, const BufferDesc *desc, void **buffer, void *)
{
    SilentBuffer *b = (SilentBuffer *)calloc(1, sizeof(SilentBuffer));
    b->refs = 1;
    if (desc->format)
        memcpy(&b->format, desc->format, sizeof(WaveFormat));
    b->size = desc->bufferBytes;
    *buffer = b;
    return S_OK;
}

extern "C" RwUInt32 __stdcall IDirectSoundBuffer_Release(void *buffer)
{
    SilentBuffer *b = (SilentBuffer *)buffer;
    LONG r = InterlockedDecrement(&b->refs);
    if (!r)
        free(b);
    return r;
}

extern "C" RwInt32 __stdcall IDirectSoundBuffer_GetStatus(void *buffer, RwUInt32 *status)
{
    SilentBuffer *b = (SilentBuffer *)buffer;
    position(b);
    *status = (b->playing ? DSBSTATUS_PLAYING : 0) | (b->playing && b->looping ? DSBSTATUS_LOOPING : 0);
    return S_OK;
}

extern "C" RwInt32 __stdcall IDirectSoundBuffer_Play(void *buffer, RwUInt32, RwUInt32, RwUInt32 flags)
{
    SilentBuffer *b = (SilentBuffer *)buffer;
    DWORD pos = (flags & DSBPLAY_FROMSTART) ? b->playOffset : position(b);
    b->looping = (flags & DSBPLAY_LOOPING) != 0;
    b->startPos = pos;
    b->startTick = GetTickCount();
    b->playing = 1;
    return S_OK;
}

extern "C" RwInt32 __stdcall IDirectSoundBuffer_StopEx(void *buffer, RwInt32, RwUInt32, RwUInt32)
{
    SilentBuffer *b = (SilentBuffer *)buffer;
    b->startPos = position(b);
    b->playing = 0;
    return S_OK;
}

extern "C" RwInt32 __stdcall IDirectSoundBuffer_Stop(void *buffer)
{
    return IDirectSoundBuffer_StopEx(buffer, 0, 0, 0);
}

extern "C" RwInt32 __stdcall IDirectSoundBuffer_SetOutputBuffer(void *, void *) { return S_OK; }
extern "C" RwInt32 __stdcall IDirectSoundBuffer_SetRolloffCurve(void *, const RwReal *, RwUInt32, RwUInt32)
{
    return S_OK;
}

extern "C" RwInt32 __stdcall IDirectSoundBuffer_SetFormat(void *buffer, const void *format)
{
    SilentBuffer *b = (SilentBuffer *)buffer;
    if (format)
        memcpy(&b->format, format, sizeof(WaveFormat));
    return S_OK;
}

extern "C" RwInt32 __stdcall IDirectSoundBuffer_SetBufferData(void *buffer, void *data, RwUInt32 size)
{
    SilentBuffer *b = (SilentBuffer *)buffer;
    b->data = (BYTE *)data;
    b->size = size;
    b->playOffset = b->playLength = b->loopOffset = b->loopLength = 0;
    b->startPos = 0;
    return S_OK;
}

extern "C" RwInt32 __stdcall IDirectSoundBuffer_SetMixBins(void *, const void *) { return S_OK; }
extern "C" RwInt32 __stdcall IDirectSoundBuffer_SetMixBinVolumes(void *, const void *) { return S_OK; }

extern "C" RwInt32 __stdcall IDirectSoundBuffer_SetPlayRegion(void *buffer, RwUInt32 offset, RwUInt32 length)
{
    SilentBuffer *b = (SilentBuffer *)buffer;
    b->playOffset = offset;
    b->playLength = length;
    return S_OK;
}

extern "C" RwInt32 __stdcall IDirectSoundBuffer_SetLoopRegion(void *buffer, RwUInt32 offset, RwUInt32 length)
{
    SilentBuffer *b = (SilentBuffer *)buffer;
    b->loopOffset = offset;
    b->loopLength = length;
    return S_OK;
}

extern "C" RwInt32 __stdcall IDirectSoundBuffer_SetCurrentPosition(void *buffer, RwUInt32 pos)
{
    SilentBuffer *b = (SilentBuffer *)buffer;
    b->startPos = pos;
    b->startTick = GetTickCount();
    return S_OK;
}

extern "C" RwInt32 __stdcall IDirectSoundBuffer_GetCurrentPosition(void *buffer, RwUInt32 *play, RwUInt32 *write)
{
    SilentBuffer *b = (SilentBuffer *)buffer;
    DWORD pos = position(b);
    if (play)
        *play = pos;
    if (write)
        *write = pos;
    return S_OK;
}

extern "C" RwInt32 __stdcall IDirectSoundBuffer_SetHeadroom(void *, RwUInt32) { return S_OK; }
extern "C" RwInt32 __stdcall IDirectSoundBuffer_SetAllParameters(void *, const void *, RwUInt32) { return S_OK; }

extern "C" RwInt32 __stdcall IDirectSoundBuffer_SetFrequency(void *buffer, RwUInt32 frequency)
{
    SilentBuffer *b = (SilentBuffer *)buffer;
    b->startPos = position(b);
    b->startTick = GetTickCount();
    b->frequency = frequency;
    return S_OK;
}

extern "C" RwInt32 __stdcall IDirectSoundBuffer_SetVolume(void *, RwInt32) { return S_OK; }
extern "C" RwInt32 __stdcall IDirectSoundBuffer_SetI3DL2Source(void *, const void *, RwUInt32) { return S_OK; }

extern "C" RwInt32 __stdcall IDirectSoundBuffer_Lock(void *buffer, RwUInt32 offset, RwUInt32 bytes, void **p1,
                                                     RwUInt32 *n1, void **p2, RwUInt32 *n2, RwUInt32)
{
    SilentBuffer *b = (SilentBuffer *)buffer;
    *p1 = b->data + offset;
    *n1 = bytes;
    if (p2)
        *p2 = NULL;
    if (n2)
        *n2 = 0;
    return S_OK;
}

extern "C" RwInt32 __stdcall IDirectSoundBuffer_Unlock(void *, void *, RwUInt32, void *, RwUInt32)
{
    return S_OK;
}

/*
 * WMA (the soundtrack streams, W5): no decoder yet; RenderWare Audio drops the source.
 */
extern "C" RwInt32 __stdcall WmaCreateDecoderEx(const char *fileName, void *, RwInt32, RwUInt32, RwUInt32,
                                                RwUInt32, void *, void **decoder)
{
    plog("audio: WMA source %s not played (W5)", fileName ? fileName : "(file)");
    *decoder = NULL;
    return E_FAIL;
}
